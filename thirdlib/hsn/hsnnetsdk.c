#include "hsnnetsdk.h"
#include "syshdr.h"
#include "tcpconn.h"
#include "recvn.h"
#include "dlist.h"
#include "set_recv_timeout.h"
#include "set_send_timeout.h"

////////////////////////////////////////////////////////////////////
// device's structure and variables (internal)
////////////////////////////////////////////////////////////////////

/* command define */
typedef enum {
	NET_CMD_LOGIN		= 0x0101, 	/* login device */
	NET_CMD_LOGIN_REP	= 0x8101,	/* login response */

	NET_CMD_REALPLAY	= 0x0201,	/* start realplay */
	NET_CMD_REALPLAY_REP	= 0x8201,	/* realplay response */

	NET_CMD_STREAM_NOTIFY	= 0x0202,	/* stream notify */

	NET_CMD_LOGOUT		= 0x0102,	/* logout from device */
	NET_CMD_LOGOUT_REP	= 0x8102,	/* logout response */

	NET_CMD_HEARTBEAT	= 0x0103,	/* heartbeat */
	NET_CMD_HEARTBEAT_REP	= 0x8103,	/* heartbeat response */
} NET_CMD;

#define MESSAGE_VERSION		0x11
#define CMDBUFF_LEN		(1024 * 4)
#define FRAME_SIZE		(1024 * 200)
#define MEDIA_HEADER		1
#define MEDIA_DATA		2
#define HEARTBEAT_DELAY		5	/* seconds */
#define RECV_TIMEOUT		10
#define SEND_TIMEOUT		10

/* error code */
#define ERR_SUCCESS		0
#define ERR_NO_ENOUGH_MEMORY	1
#define ERR_NO_SUPPORT_DEV_TYPE	2
#define ERR_DEV_NOT_EXIST	3
#define ERR_DEV_ID_NO_EXIST	4
#define ERR_SESSION_ID		5
#define ERR_USER_RNAME		6
#define ERR_TIME_OUT_WAIT_REP	7

/* command header */
typedef struct {
	unsigned char  version;
	unsigned char  hdr_len;
	unsigned short cmd_id;
	unsigned short user_id;
	unsigned short message_len;
} NET_CMD_HEAD;

#define NET_CMD_HEAD_LEN	sizeof(NET_CMD_HEAD)

/* login information */
typedef struct {
	unsigned int  dev_id;	/* device id (normal: 1234) */
	unsigned char chan_num;	/* channel number (normal: 0) */
	unsigned char dev_type;	/* device type (normal: 2) */
	unsigned short res;	/* reserved */
	char          user[8];	/* user name (normal: admin) */
	char	      pwd[8];	/* password (normal: admin) */
} NET_LOGUSER;

typedef struct {
	unsigned short result;
	unsigned short reserved;
} NET_GENERAL_RESPONSE;

typedef struct {
	unsigned char byVideoType;	/* 0:MPEG4 1:H264 */
	unsigned char byChanID;		/* channel ID */
	unsigned char byVideoMode;	/* 1:D1 2:CIF 3:QCIF */
	unsigned char res;		/* reserved */
	unsigned char byFrameType;	/* 1/5/6/7/8 */
	unsigned char byIsAskFlag;	/* 0:not need 1:need */
	unsigned char byPackIndex;	/* packet's index */
	unsigned char byPackCount;	/* packets in current frame */
	unsigned int  dwFrameID;	/* frame ID */
	unsigned int  dwFrameLength;	/* frame length */
	unsigned int  sec_TimeStamp;	/* timestamp (second) */
	unsigned short mili_TimeStamp;	/* timestamp (mili-second) */
	unsigned short nDataLen;	/* data length (follow the head) */
} NET_VIDEODATA_HEAD;

////////////////////////////////////////////////////////////////////
// personal structure and variables
////////////////////////////////////////////////////////////////////

/* login handle info */
typedef struct {
	int	login_fd;
	int	user_id;
	char	dev_ip[32];
	int	ctl_port;
	int	media_port;
	char	dev_user[32];	
	char	dev_pwd[16];
	int	logout;

	dlist_t	*realplay_handles;	/* realplay handle list */
	pthread_mutex_t cmd_mtx;
	pthread_mutex_t hdl_mtx;
} login_handle_t;

/* realplay handle info */
typedef struct {
	login_handle_t *login_handle;
	int	realplay_fd;
	HSN_NET_REALPLAY info;
	HSN_NET_RealDataCallBack realdata_cb;
	void	*param;
	int	stop;
} realplay_handle_t;

/* stream notify info */
typedef struct {
	unsigned int dev_id;	/* get from NET_GENERAL_RESPONSE.reserved via 
				   NET_CMD_REALPLAY */
} stream_notify_t;

static int send_cmd(int sock, int user_id, int cmd_id, void *cmd_buff, 
		int cmd_buff_len)
{
	char buff[CMDBUFF_LEN];
	NET_CMD_HEAD *hdr;

	assert(cmd_buff_len <= (CMDBUFF_LEN - NET_CMD_HEAD_LEN));

	hdr = (NET_CMD_HEAD *)buff;
	hdr->version = MESSAGE_VERSION;
	hdr->hdr_len = MESSAGE_VERSION;
	hdr->cmd_id = cmd_id;
	hdr->user_id = user_id;
	hdr->message_len = cmd_buff_len;

	if (cmd_buff)
		memcpy(&buff[NET_CMD_HEAD_LEN], cmd_buff, cmd_buff_len);
	if (send(sock, buff, NET_CMD_HEAD_LEN + cmd_buff_len, 0) == -1)
		return -1;

	return 0;
}

static int recv_cmd(int sock, int *user_id, int *cmd_id, void *cmd_buff, 
		const int cmd_buff_size, int *cmd_buff_len)
{
	NET_CMD_HEAD hdr;
	int bytes;

	/* receive command header */
	bytes = recvn(sock, &hdr, NET_CMD_HEAD_LEN, 0);
	if (bytes <= 0) {
		printf("--> receive command header error\n");
		goto err;
	}

	if (hdr.version != MESSAGE_VERSION || 
			hdr.hdr_len != MESSAGE_VERSION) { /* invalid command */
		printf("--> command version error\n");
		goto err;
	}

	if (user_id)
		*user_id = hdr.user_id;
	if (cmd_id)
		*cmd_id = hdr.cmd_id;
	if (cmd_buff_len)
		*cmd_buff_len = hdr.message_len;

	if (hdr.message_len < 0 || hdr.message_len > cmd_buff_size) {
		printf("--> command buffer length error\n");
		goto err;
	}

	/* receive command body */
	if (hdr.message_len > 0) {
		bytes = recvn(sock, cmd_buff, hdr.message_len, 0);
		if (bytes <= 0) {
			printf("--> receive command body error\n");
			goto err;
		}
	}

	return 0;

err:
	return -1;
}

static int login_dev(char *ip, int port, char *user, char *pwd, int *user_id)
{
	int sock = -1;
	int cmd_id;
	NET_LOGUSER login_info;
	char buff[512];
	NET_GENERAL_RESPONSE *resp = (NET_GENERAL_RESPONSE *)buff;

	login_info.dev_id = 1234;
	login_info.chan_num = 0;
	login_info.dev_type = 2;
	snprintf(login_info.user, sizeof(login_info.user), "%s", user);
	snprintf(login_info.pwd, sizeof(login_info.pwd), "%s", pwd);

	sock = tcpconn(ip, port, 3);
	if (sock == -1)
		goto err;

	set_recv_timeout(sock, RECV_TIMEOUT);
	set_send_timeout(sock, SEND_TIMEOUT);

	if (send_cmd(sock, -1, NET_CMD_LOGIN, &login_info, 
				sizeof(NET_LOGUSER)) == -1)
		goto err;
	if (recv_cmd(sock, user_id, &cmd_id, buff, sizeof(buff), NULL) == -1)
		goto err;

//	if (cmd_id != NET_CMD_LOGIN_REP)
//		goto err;
	if (resp->result != ERR_SUCCESS)
		goto err;

	return sock;

err:
	if (sock != -1)
		close(sock);
	return -1;
}

static int realplay(login_handle_t *handle, HSN_NET_REALPLAY *info)
{
	int login_sock;
	int media_sock = -1;
	NET_GENERAL_RESPONSE resp;
	stream_notify_t notify;

	login_sock = handle->login_fd;
	int cmd_id;

	/* send realmedia apply */
	pthread_mutex_lock(&handle->cmd_mtx);
	if (send_cmd(login_sock, handle->user_id, NET_CMD_REALPLAY, info, 
				sizeof(HSN_NET_REALPLAY)) == -1) {
		pthread_mutex_unlock(&handle->cmd_mtx);
		goto err;
	}
	if (recv_cmd(login_sock, NULL, &cmd_id, &resp, sizeof(resp), 
				NULL) == -1) {
		pthread_mutex_unlock(&handle->cmd_mtx);
		goto err;
	}
	pthread_mutex_unlock(&handle->cmd_mtx);

	if (cmd_id != NET_CMD_REALPLAY_REP)
		goto err;
	if (resp.result != ERR_SUCCESS)
		goto err;

	/* send stream notify */
	media_sock = tcpconn(handle->dev_ip, handle->media_port, 3);
	if (media_sock == -1)
		goto err;

	set_recv_timeout(media_sock, RECV_TIMEOUT);
	set_send_timeout(media_sock, SEND_TIMEOUT);

	notify.dev_id = resp.reserved;

	if (send_cmd(media_sock, -1, NET_CMD_STREAM_NOTIFY, &notify, 
				sizeof(notify)) == -1)
		goto err;

	return media_sock;

err:
	if (media_sock != -1)
		close(media_sock);
	return -1;
}

static int add_realplay(realplay_handle_t *handle)
{
	login_handle_t *lp = handle->login_handle;
	if (lp == NULL)
		return -1;

	int ret = 0;
	pthread_mutex_lock(&lp->hdl_mtx);
	if (dlist_add(&lp->realplay_handles, (void *)handle) == -1)
		ret = -1;
	pthread_mutex_unlock(&lp->hdl_mtx);

	return ret;
}

static inline int cmp_realplay_fd(void *a, void *b)
{
	realplay_handle_t *handle = (realplay_handle_t *)a;
	return (handle->realplay_fd == (int)b) ? 0 : -1;
}

static int del_realplay(realplay_handle_t *handle)
{
	login_handle_t *lp = handle->login_handle;
	if (lp == NULL)
		return -1;

	pthread_mutex_lock(&lp->hdl_mtx);
	dlist_del(&lp->realplay_handles, cmp_realplay_fd,
			(void *)handle->realplay_fd, ds_none_callback, NULL);
	pthread_mutex_unlock(&lp->hdl_mtx);

	return 0;
}

static int heartbeat(login_handle_t *handle)
{
	NET_CMD_HEAD hdr;
	int bytes;

	pthread_mutex_lock(&handle->cmd_mtx);

	if (send_cmd(handle->login_fd, handle->user_id, NET_CMD_HEARTBEAT, 
				NULL, 0) == -1)
		goto err;

	bytes = recvn(handle->login_fd, &hdr, NET_CMD_HEAD_LEN, 0);
	if (bytes <= 0) {
		printf("--> receive command header error\n");
		goto err;
	}

	pthread_mutex_unlock(&handle->cmd_mtx);
	return 0;

err:
	pthread_mutex_unlock(&handle->cmd_mtx);
	return -1;
}

static int re_login_dev(login_handle_t *handle)
{
	int new_fd;

	while (handle->logout == 0) {
		new_fd = login_dev(handle->dev_ip, handle->ctl_port, 
				handle->dev_user, handle->dev_pwd, 
				&handle->user_id);
		if (new_fd != -1) {
			printf("re-login device success\n");
			close(handle->login_fd);
			handle->login_fd = new_fd;
			return 0;
		}
		sleep(5);
	}

	return -1;
}

static int resume_realplay(void *data, void *ret)
{
	int *pret = (int *)ret;

	if (*pret == -1)
		return -1;

	realplay_handle_t *handle = (realplay_handle_t *)data;
	int realplay_fd;

	realplay_fd = realplay(handle->login_handle, &handle->info);
	if (realplay_fd == -1) {
		*pret = -1;	/* error */
		return -1;
	}
	if (handle->realplay_fd != -1)
		close(handle->realplay_fd);
	handle->realplay_fd = realplay_fd;
	*pret = 0;

	return 0;
}

static int stop_realplay(void *data, void *param)
{
	realplay_handle_t *handle = (realplay_handle_t *)data;
	handle->stop = 1;
	return 0;
}

static void resume_all_realplay(login_handle_t *handle)
{
	int ret = 0;

	pthread_mutex_lock(&handle->hdl_mtx);
	dlist_for_each(handle->realplay_handles, resume_realplay, &ret);
	pthread_mutex_unlock(&handle->hdl_mtx);
}

static void remove_all_realplay(login_handle_t *handle)
{
	pthread_mutex_lock(&handle->hdl_mtx);
	dlist_for_each(handle->realplay_handles, stop_realplay, NULL);
	dlist_clear(&handle->realplay_handles, ds_none_callback, NULL);
	pthread_mutex_unlock(&handle->hdl_mtx);
}

static void *heartbeat_thread(void *arg)
{
	login_handle_t *handle = (login_handle_t *)arg;

	while (handle->logout == 0) {
		if (heartbeat(handle) == -1) {
			if (re_login_dev(handle) == -1)
				break;
			resume_all_realplay(handle);
			sleep(1);
			continue;
		}
		sleep(HEARTBEAT_DELAY);
	}

	/* stop and remove all realplay if there have */
	remove_all_realplay(handle);

	if (handle->login_fd != -1)
		close(handle->login_fd);
	pthread_mutex_destroy(&handle->cmd_mtx);
	pthread_mutex_destroy(&handle->hdl_mtx);

	free(handle);
	return NULL;
}

/* receive real data thread */
static void *recv_real_data_thread(void *arg)
{
	realplay_handle_t *handle = (realplay_handle_t *)arg;
	char head[sizeof(NET_CMD_HEAD) + sizeof(NET_VIDEODATA_HEAD)];
	char data[FRAME_SIZE];
	NET_VIDEODATA_HEAD *phead;
	int bytes;

	/* receive and send media data */
	phead = (NET_VIDEODATA_HEAD *)(&head[sizeof(NET_CMD_HEAD)]);
	while (handle->stop == 0) {
		/* receive media data head */
		bytes = recvn(handle->realplay_fd, head, sizeof(head), 0);
		if (bytes <= 0) {
			sleep(1);
			continue;
		}

		/* receive media data */
		bytes = recvn(handle->realplay_fd, data, phead->nDataLen, 0);
		if (bytes <= 0) {
			sleep(1);
			continue;
		}

		handle->realdata_cb((LONG)handle, MEDIA_DATA, data, bytes, 
				handle->param);
	}

	if (handle->realplay_fd != -1)
		close(handle->realplay_fd);
	free(handle);
	return NULL;
}

BOOL HSN_NET_Init()
{
	return TRUE;
}

BOOL HSN_NET_Cleanup()
{
	return TRUE;
}

LONG HSN_NET_GetLastError()
{
	return 0;
}

LONG HSN_NET_Login(char *ip, WORD ctl_port, WORD media_port, 
		char *user, char *pwd)
{
	int login_fd = -1;
	int user_id;
	login_handle_t *handle;
	pthread_t tid;

	/* login on device */
	login_fd = login_dev(ip, ctl_port, user, pwd, &user_id);

	if (login_fd == -1)
		goto err;

	handle = malloc(sizeof(login_handle_t));
	if (handle == NULL)
		goto err;
	handle->login_fd = login_fd;
	handle->user_id = user_id;
	snprintf(handle->dev_ip, sizeof(handle->dev_ip), "%s", ip);
	handle->ctl_port = ctl_port;
	handle->media_port = media_port;
	snprintf(handle->dev_user, sizeof(handle->dev_user), "%s", user);
	snprintf(handle->dev_pwd, sizeof(handle->dev_pwd), "%s", pwd);
	handle->logout = 0;
	handle->realplay_handles = dlist_init();
	pthread_mutex_init(&handle->cmd_mtx, NULL);
	pthread_mutex_init(&handle->hdl_mtx, NULL);

	/* create heartbeat thread */
	if (pthread_create(&tid, NULL, heartbeat_thread, handle) != 0) {
		free(handle);
		goto err;
	}
	pthread_detach(tid);

	return (LONG)handle;

err:
	if (login_fd != -1)
		close(login_fd);
	return -1;
}

BOOL HSN_NET_Logout(LONG login_handle)
{
	login_handle_t *handle;
	
	handle = (login_handle_t *)login_handle;
	if (login_handle == -1 || handle == NULL)
		return FALSE;

	/* stop heartbeat thread */
	handle->logout = 1;

	return TRUE;
}

LONG HSN_NET_RealPlay(LONG login_handle, HSN_NET_REALPLAY *info, 
		HSN_NET_RealDataCallBack callback, void *param)
{
	login_handle_t *handle;
	int realplay_fd;
	realplay_handle_t *realplay_handle;
	pthread_t tid;

	handle = (login_handle_t *)login_handle;
	if (login_handle == -1 || handle == NULL)
		return -1;

	realplay_fd = realplay(handle, info);
	if (realplay_fd == -1)
		goto err;

	realplay_handle = malloc(sizeof(realplay_handle_t));
	if (realplay_handle == NULL)
		goto err;
	realplay_handle->login_handle = handle;
	realplay_handle->realplay_fd = realplay_fd;
	realplay_handle->info = *info;
	realplay_handle->realdata_cb = callback;
	realplay_handle->param = param;
	realplay_handle->stop = 0;

	if (pthread_create(&tid, NULL, recv_real_data_thread, 
				realplay_handle) != 0) {
		free(realplay_handle);
		goto err;
	}
	pthread_detach(tid);

	if (add_realplay(realplay_handle) != 0) {
		realplay_handle->stop = 1;
		goto err;
	}

	return (LONG)realplay_handle;

err:
	if (realplay_fd != -1)
		close(realplay_fd);
	return -1;
}

BOOL HSN_NET_StopRealPlay(LONG realplay_handle)
{
	realplay_handle_t *p = (realplay_handle_t *)realplay_handle;
	if (realplay_handle == -1 || p == NULL)
		return FALSE;

	del_realplay(p);
	p->stop = 1;
	return TRUE;
}
