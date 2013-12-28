#include <openssl/md5.h>

#include "hbnetsdk.h"
#include "syshdr.h"
#include "tcpconn.h"
#include "recvn.h"
#include "dlist.h"
#include "set_recv_timeout.h"
#include "set_send_timeout.h"
#include "split_day.h"
#include "read_flag.h"

////////////////////////////////////////////////////////////////////
// DVR's structure and variables (internal)
////////////////////////////////////////////////////////////////////

/* command define */
typedef enum {
	NET_CMD_LOGIN		= 0x00, 	/* login device */
	NET_CMD_LOGOUT		= 0x01,		/* logout from device */
	NET_CMD_REALPLAY	= 0x02,		/* start realplay */
	NET_CMD_STOP_REALPLAY	= 0x03,		/* stop realplay */
	NET_CMD_KEYFRAME	= 0x06,		/* keyframe request */
	NET_CMD_GET_MD5ID	= 0x40,		/* get MD5 code (login use) */
	NET_CMD_QUERY_RECFILE	= 0x45,		/* record files query */
	NET_CMD_VOD_RECFILE	= 0x49,   	/* file download (begin-) */
	NET_CMD_VOD_RECFILE_EX	= 0x4A,		/* file download (begin-end) */	
	NET_CMD_VOD_RECFILE_CTL	= 0x4C,		/* record file VOD control */
	NET_CMD_VOD_RECFILE_END	= 0x4F,   	/* record file VOD stop */
	NET_CMD_GET_DVRTYPE	= 0x71,		/* get device type */
	NET_CMD_HEARTBEAT	= 0xFF		/* heartbeat */
} NET_CMD;

#define CMDFLAG			1381385299	/* command flag: "RVDS"*/
#define CMDBUFF_LEN		(1024 * 8)
#define FRAME_SIZE		(1024 * 200)
#define MEDIA_HEADER_LEN	64
#define MEDIA_HEADER		1
#define MEDIA_DATA		2
#define HEARTBEAT_DELAY		10	/* seconds */
#define RECV_TIMEOUT		10
#define SEND_TIMEOUT		10

/* command header */
typedef struct {
	DWORD	flag;		/* fixed "SDVR" */
	DWORD	user_id;
	USHORT	cmd_id;
	USHORT	cmd_buff_len;
	USHORT	result;		/* 0:failed 1:success */
	union {
		short error_code;
		USHORT heigh_len;
	} u;
} NET_CMD_HEAD;
#define NET_CMD_HEAD_LEN	sizeof(NET_CMD_HEAD)

/* login information */
typedef struct {
	char	user[32];	
	char	pwd[16];
	DWORD	user_len;
	DWORD	pwd_len;
} NET_LOGUSER;

/* device information */
typedef struct {
	DWORD	dvr_type;	/* 7004, 8004, 2201, 2004, NVRs */
	WORD	device_type;	/* enum NET_DEV_TYPE */
	WORD	memory_size;
	DWORD	reserve;
} NET_DEV_INFO;

/* device type */
typedef enum {
	NET_DEVTYPE_7000T = 0,
	NET_DEVTYPE_8000T,
	NET_DEVTYPE_8200T
} NET_DEV_TYPE;

/* time info */
#pragma pack(1)
typedef struct {
	unsigned int sec : 6;	/* [0,59] */
	unsigned int min : 6;	/* [0,59] */
	unsigned int hour: 5;	/* [0,23] */
	unsigned int day : 5;	/* [1,31] */
	unsigned int mon : 4;	/* [1,12] */
	unsigned int year: 6; 	/* [2000,2063] */
} NET_TIME;
#pragma pack()

/* record file find */
typedef struct {
	BYTE	byChannel;
	BYTE	byType;		/* HB_NET_RECFILE_TYPE */
	NET_TIME bgn;
	NET_TIME end;
	WORD	dwStart;	/* start 0 */
	WORD	dwNum;		/* files number in per query. In protocol 1, 
				   it define 100; in protocol 2, it is 
				   reserve. */
} NET_REC_FIND;

/* record file info */
typedef struct {
	NET_TIME bgn;
	NET_TIME end;
	DWORD	dwFileSize;
	BYTE	byChannel;
	BYTE	byType;		/* HB_NET_RECFILE_TYPE */
	char	reserve1;
	char	reserve2;
} NET_FILEINFO;

/* the file record set return by query */
typedef struct {
	DWORD	files_num;
	NET_FILEINFO files[FILES_NUM_PER_QUERY];
} NET_FILES_SET;

/* VOD info */
typedef struct {
	BYTE	byChannel;
	BYTE	byType;
	NET_TIME bgn;
	BYTE	reserve1;
	BYTE	reserve2;
} NET_VOD;

/* VOD control info */
typedef struct {
	DWORD	playback_id;
	BYTE	ctl_code;	/* 0:normal 1:pause 2:faster 3:slower 4:frame */
	BYTE	speed;
	BYTE	seekflag;
	BYTE	percent;
} NET_VOD_CTL;

////////////////////////////////////////////////////////////////////
// personal structure and variables
////////////////////////////////////////////////////////////////////

/* login handle info */
typedef struct {
	int	login_fd;
	int	user_id;
	char	dvr_ip[32];
	int	dvr_port;
	char	dvr_user[32];	
	char	dvr_pwd[16];
	char	media_header[MEDIA_HEADER_LEN];
	int	logout;

	dlist_t	*realplay_handles;	/* realplay handle list */
	pthread_mutex_t mtx;
} login_handle_t;

/* realplay handle info */
typedef struct {
	login_handle_t *login_handle;
	int	realplay_fd;
	HB_NET_REALPLAY info;
	HB_NET_RealDataCallBack realdata_cb;
	void	*param;
	int	stop;
} realplay_handle_t;

/* record find handle info */
typedef struct {
	login_handle_t *login_handle;
	int channel;
	int file_type;
	int no_find;
	split_handle_t *split_handle;
	NET_FILES_SET files_set;
	int files_set_index;
} find_handle_t;

/* playback handle info */
typedef struct {
	login_handle_t *login_handle;
	int	playback_fd;
	int	playback_id;
	HB_NET_PlayBackDataCallBack playback_cb;
	void	*param;
	int	stop;
} playback_handle_t;

static int send_cmd(int sock, int user_id, int cmd_id, void *cmd_buff, 
		int cmd_buff_len)
{
	char buff[CMDBUFF_LEN];
	NET_CMD_HEAD *hdr;

	assert(cmd_buff_len <= (CMDBUFF_LEN - NET_CMD_HEAD_LEN));

	hdr = (NET_CMD_HEAD *)buff;
	hdr->flag = CMDFLAG;
	hdr->user_id = user_id;
	hdr->cmd_id = cmd_id;
	hdr->cmd_buff_len = cmd_buff_len;

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

	if (hdr.flag != CMDFLAG) {	/* invalid command */
		printf("--> command flag error\n");
		goto err;
	}
	if (hdr.result == 0) {		/* failed */
		printf("--> receive error code: %d\n", hdr.u.error_code);
		goto err;
	}

	if (user_id)
		*user_id = hdr.user_id;
	if (cmd_id)
		*cmd_id = hdr.cmd_id;
	if (cmd_buff_len)
		*cmd_buff_len = hdr.cmd_buff_len;

	if (hdr.cmd_buff_len < 0 || hdr.cmd_buff_len > cmd_buff_size) {
		printf("--> command buffer length error\n");
		goto err;
	}

	/* receive command body */
	if (hdr.cmd_buff_len > 0) {
		bytes = recvn(sock, cmd_buff, hdr.cmd_buff_len, 0);
		if (bytes <= 0) {
			printf("--> receive command body error\n");
			goto err;
		}
	}

	return 0;

err:
	return -1;
}

static void MD5_enc(char id, char *pwd_orig, unsigned char *pwd_md5)
{
	unsigned char data[] = {
		0x50, 0xfd, 0xfd, 0x87, 0x1c, 0x1b, 0xd1, 0x44,
		0x9b, 0x67, 0xdb, 0x0d, 0x7e, 0xed, 0xd9, 0x1e
	};

	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, &id, sizeof(char));
	MD5_Update(&ctx, pwd_orig, strlen(pwd_orig));
	MD5_Update(&ctx, data, sizeof(data));
	MD5_Final((unsigned char *)pwd_md5, &ctx);
}

static int get_md5id(char *ip, uint16_t port, char *pwd_orig, 
		unsigned char *pwd_md5)
{
	int sock;
	int cmd_id;
	char buff[CMDBUFF_LEN];

	sock = tcpconn(ip, port, 3);
	if (sock == -1)
		goto err;

	set_recv_timeout(sock, RECV_TIMEOUT);
	set_send_timeout(sock, SEND_TIMEOUT);

	if (send_cmd(sock, -1, NET_CMD_GET_MD5ID, NULL, 0) == -1)
		goto err;
	if (recv_cmd(sock, NULL, &cmd_id, buff, sizeof(buff), NULL) == -1)
		goto err;
	if (cmd_id != NET_CMD_GET_MD5ID)
		goto err;

	MD5_enc(buff[0], pwd_orig, pwd_md5);
	close(sock);
	return 0;

err:
	if (sock != -1)
		close(sock);
	return -1;
}

static int login_dvr(char *ip, int port, char *user, char *pwd, 
		HB_NET_DEVICEINFO *dev_info, int *user_id)
{
	int sock = -1;
	unsigned char pwd_md5[16] = {0};
	int cmd_id;
	NET_LOGUSER login_info;
	HB_NET_DEVICEINFO dev;

	/* get MD5 password */
	if (get_md5id(ip, port, pwd, pwd_md5) != 0)
		goto err;

	snprintf(login_info.user, sizeof(login_info.user), "%s", user);
	strcpy((char *)login_info.pwd, (const char *)&pwd_md5);
	login_info.user_len = strlen(user);
	login_info.pwd_len = sizeof(pwd_md5);

	sock = tcpconn(ip, port, 3);
	if (sock == -1)
		goto err;

	set_recv_timeout(sock, RECV_TIMEOUT);
	set_send_timeout(sock, SEND_TIMEOUT);

	if (send_cmd(sock, -1, NET_CMD_LOGIN, &login_info, 
				sizeof(NET_LOGUSER)) == -1)
		goto err;
	if (recv_cmd(sock, user_id, &cmd_id, &dev, sizeof(dev), NULL) == -1)
		goto err;
	if (cmd_id != NET_CMD_LOGIN)
		goto err;

	if (dev_info)
		memcpy(dev_info, &dev, sizeof(dev));
	return sock;

err:
	if (sock != -1)
		close(sock);
	return -1;
}

static int get_media_header(int login_fd, int user_id, char *media_header, 
		const int media_buff_size)
{
	NET_DEV_INFO info;
	int cmd_id;

	if (send_cmd(login_fd, user_id, NET_CMD_GET_DVRTYPE, NULL, 0) == -1)
		return -1;
	if (recv_cmd(login_fd, NULL, &cmd_id, &info, sizeof(info), NULL) == -1)
		return -1;
	if (cmd_id != NET_CMD_GET_DVRTYPE)
		return -1;

	if (info.dvr_type == 1030) {
		memcpy(media_header, "HBGKIPCA", 8);
		goto fin;
	}

	sprintf(media_header, "%c%c", (char)(info.dvr_type & 0x000000FF), 
			(char)(info.dvr_type>>8 & 0x000000FF));
	if (strcmp(media_header, "7T") == 0 || 
			strcmp(media_header, "8T") == 0) {
		memcpy(media_header, "HBGK7KT", 7);
		media_header[7] = 0x20;
		media_header[8] = 0x01;
	} else {
		memcpy(media_header, "HBGKBMW", 7);
		media_header[7] = 0x20;
		media_header[8] = 0x01;
	}

fin:
	return 0;
}

static int realplay(login_handle_t *handle, HB_NET_REALPLAY *info)
{
	int sock;
	int cmd_id;
	char buff[CMDBUFF_LEN];

	sock = tcpconn(handle->dvr_ip, handle->dvr_port, 3);
	if (sock == -1)
		goto err;

	set_recv_timeout(sock, RECV_TIMEOUT);
	set_send_timeout(sock, SEND_TIMEOUT);

	if (send_cmd(sock, handle->user_id, NET_CMD_REALPLAY, info, 
				sizeof(HB_NET_REALPLAY)) == -1)
		goto err;
	if (recv_cmd(sock, NULL, &cmd_id, buff, sizeof(buff), NULL) == -1)
		goto err;
	if (cmd_id != NET_CMD_REALPLAY)
		goto err;

	return sock;

err:
	if (sock != -1)
		close(sock);
	return -1;
}

static int add_realplay(realplay_handle_t *handle)
{
	login_handle_t *lp = handle->login_handle;
	if (lp == NULL)
		return -1;

	int ret = 0;
	pthread_mutex_lock(&lp->mtx);
	if (dlist_add(&lp->realplay_handles, (void *)handle) == -1)
		ret = -1;
	pthread_mutex_unlock(&lp->mtx);

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

	pthread_mutex_lock(&lp->mtx);
	dlist_del(&lp->realplay_handles, cmp_realplay_fd,
			(void *)handle->realplay_fd, ds_none_callback, NULL);
	pthread_mutex_unlock(&lp->mtx);

	return 0;
}

static int heartbeat(login_handle_t *handle)
{
	int cmd_id;
	char buff[CMDBUFF_LEN];

	pthread_mutex_lock(&handle->mtx);

	if (send_cmd(handle->login_fd, handle->user_id, NET_CMD_HEARTBEAT, 
				NULL, 0) == -1)
		goto err;
	if (recv_cmd(handle->login_fd, NULL, &cmd_id, buff, sizeof(buff), 
				NULL) == -1)
		goto err;
	if (cmd_id != NET_CMD_HEARTBEAT)
		goto err;

	pthread_mutex_unlock(&handle->mtx);
	return 0;

err:
	pthread_mutex_unlock(&handle->mtx);
	return -1;
}

static int re_login_dvr(login_handle_t *handle)
{
	int new_fd;

	while (handle->logout == 0) {
		new_fd = login_dvr(handle->dvr_ip, handle->dvr_port, 
				handle->dvr_user, handle->dvr_pwd, NULL, 
				&handle->user_id);
		if (new_fd != -1) {
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

	pthread_mutex_lock(&handle->mtx);
	dlist_for_each(handle->realplay_handles, resume_realplay, &ret);
	pthread_mutex_unlock(&handle->mtx);
}

static void remove_all_realplay(login_handle_t *handle)
{
	pthread_mutex_lock(&handle->mtx);
	dlist_for_each(handle->realplay_handles, stop_realplay, NULL);
	dlist_clear(&handle->realplay_handles, ds_none_callback, NULL);
	pthread_mutex_unlock(&handle->mtx);
}

static void *heartbeat_thread(void *arg)
{
	login_handle_t *handle = (login_handle_t *)arg;

	while (handle->logout == 0) {
		if (heartbeat(handle) == -1) {
			if (re_login_dvr(handle) == -1)
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
	pthread_mutex_destroy(&handle->mtx);

	free(handle);
	return NULL;
}

/* receive real data thread */
static void *recv_real_data_thread(void *arg)
{
	realplay_handle_t *handle = (realplay_handle_t *)arg;
	char buff[FRAME_SIZE];
	int bytes;

	/* send media header */
	handle->realdata_cb((LONG)handle, MEDIA_HEADER, 
			handle->login_handle->media_header, MEDIA_HEADER_LEN, 
			handle->param);

	/* receive and send media data */
	while (handle->stop == 0) {
		bytes = recv(handle->realplay_fd, buff, sizeof(buff), 0);
		if (bytes <= 0) {
			sleep(1);
			continue;
		}
		handle->realdata_cb((LONG)handle, MEDIA_DATA, buff, bytes, 
				handle->param);
	}

	if (handle->realplay_fd != -1)
		close(handle->realplay_fd);
	free(handle);
	return NULL;
}

static find_handle_t *convert_find_handle(login_handle_t *login_handle, 
		HB_NET_FILEFIND_COND *cond)
{
	find_handle_t *handle;
	split_time_t bgn, end;

	handle = malloc(sizeof(find_handle_t));
	if (handle == NULL)
		return NULL;

	handle->login_handle = login_handle;
	handle->channel = cond->dwChannel;
	handle->file_type = cond->byType;
	handle->no_find = 1;

	bgn.year = cond->bgn.year;
	bgn.mon  = cond->bgn.mon;
	bgn.day  = cond->bgn.day;
	bgn.hour = cond->bgn.hour;
	bgn.min  = cond->bgn.min;
	bgn.sec  = cond->bgn.sec;
	end.year = cond->end.year;
	end.mon  = cond->end.mon;
	end.day  = cond->end.day;
	end.hour = cond->end.hour;
	end.min  = cond->end.min;
	end.sec  = cond->end.sec;
	handle->split_handle = split_day_init(&bgn, &end);
	if (handle->split_handle == NULL) {
		free(handle);
		return NULL;
	}
	handle->files_set.files_num = 0;
	handle->files_set_index = 0;

	return handle;
}

static int find_file(find_handle_t *handle, split_time_t *bgn, 
		split_time_t *end, int start_num)
{
	login_handle_t *login_handle;
	int cmd_id;
	NET_REC_FIND find;

	handle->files_set_index = 0;

	login_handle = handle->login_handle;
	find.byChannel = handle->channel;
	find.byType = handle->file_type;
	find.bgn.year = bgn->year - 2000;
	find.bgn.mon  = bgn->mon;
	find.bgn.day  = bgn->day;
	find.bgn.hour = bgn->hour;
	find.bgn.min  = bgn->min;
	find.bgn.sec  = bgn->sec;
	find.end.year = end->year - 2000;
	find.end.mon  = end->mon;
	find.end.day  = end->day;
	find.end.hour = end->hour;
	find.end.min  = end->min;
	find.end.sec  = end->sec;
	find.dwStart = start_num;
	find.dwNum = FILES_NUM_PER_QUERY;

	pthread_mutex_lock(&login_handle->mtx);
	if (send_cmd(login_handle->login_fd, login_handle->user_id, 
				NET_CMD_QUERY_RECFILE, &find, 
				sizeof(NET_REC_FIND)) == -1)
		goto err;
	if (recv_cmd(login_handle->login_fd, NULL, &cmd_id, &handle->files_set, 
				sizeof(NET_FILES_SET), NULL) == -1)
		goto err;
	if (cmd_id != NET_CMD_QUERY_RECFILE)
		goto err;

	pthread_mutex_unlock(&login_handle->mtx);
	return 0;

err:
	pthread_mutex_unlock(&login_handle->mtx);
	return -1;
}

static int recv_playback_id(int sock, int *playback_id)
{
	const char flag[] = {0x53, 0x44, 0x56, 0x52};
	DWORD userid;
	USHORT cmdid;
	USHORT cmd_buff_len;
	USHORT result;
	USHORT u_ignore;

	/* receive command header flag */
	if (read_flag(sock, flag, sizeof(flag), 1024 * 100) != 0)
		goto err;

	/* receive user id (ignore it) */
	if (recvn(sock, &userid, sizeof(userid), 0) != sizeof(userid))
		goto err;

	/* receive command id */
	if (recvn(sock, &cmdid, sizeof(cmdid), 0) != sizeof(cmdid))
		goto err;

	/* receive command buffer length */
	if (recvn(sock, &cmd_buff_len, sizeof(cmd_buff_len), 0) != 
			sizeof(cmd_buff_len))
		goto err;
	if (cmd_buff_len != 4)	/* only hold playback_id */
		goto err;

	/* receive result */
	if (recvn(sock, &result, sizeof(result), 0) != sizeof(result))
		goto err;
	if (result == 0)	/* failed */
		goto err;

	/* ignore 2 bytes */
	if (recvn(sock, &u_ignore, sizeof(u_ignore), 0) != sizeof(u_ignore))
		goto err;

	/* receive playback_id */
	if (recvn(sock, playback_id, sizeof(int), 0) != sizeof(int))
		goto err;
	printf("playback_id: %d\n", *playback_id);

	return 0;

err:
	printf("receive playback_id error\n");
	return -1;
}

static int send_playback_cmd(login_handle_t *handle, int cmdid, 
		void *cmd_buff, int cmd_buff_len, int *playback_fd, 
		int *playback_id)
{
	int sock;

	sock = tcpconn(handle->dvr_ip, handle->dvr_port, 3);
	if (sock == -1)
		return -1;

	set_recv_timeout(sock, RECV_TIMEOUT);
	set_send_timeout(sock, SEND_TIMEOUT);

	if (send_cmd(sock, handle->user_id, cmdid, cmd_buff, 
				cmd_buff_len) == -1)
		goto err;

	if (recv_playback_id(sock, playback_id) == -1)
		goto err;

	if (playback_fd)
		*playback_fd = sock;

	return 0;

err:
	if (sock != -1)
		close(sock);
	return -1;
}

static void *recv_playback_data_thread(void *arg)
{
	playback_handle_t *handle;
	char buff[FRAME_SIZE];
	int bytes;

	handle = (playback_handle_t *)arg;

	/* send media header */
	/*
	handle->playback_cb((LONG)handle, MEDIA_HEADER, 
			handle->login_handle->media_header, MEDIA_HEADER_LEN, 
			handle->param);
			*/

	while (handle->stop == 0) {
		bytes = recv(handle->playback_fd, buff, sizeof(buff), 0);
		if (bytes <= 0) {
			sleep(3);
			continue;
		}
		handle->playback_cb((LONG)handle, MEDIA_DATA, buff, bytes, 
				handle->param);
	}

	if (handle->playback_fd != -1)
		close(handle->playback_fd);
	free(handle);
	return NULL;
}

static playback_handle_t *playback(LONG login_handle, int cmdid, 
		void *cmd_buff, int cmd_buff_len,
		HB_NET_PlayBackDataCallBack callback, void *param)
{
	playback_handle_t *playback_handle = NULL;
	login_handle_t *handle;
	int playback_fd = -1;
	int playback_id = -1;
	pthread_t tid;

	handle = (login_handle_t *)login_handle;
	if (login_handle == -1 || handle == NULL)
		goto err;

	playback_handle = malloc(sizeof(playback_handle_t));
	if (playback_handle == NULL)
		goto err;

	if (send_playback_cmd(handle, cmdid, cmd_buff, cmd_buff_len, 
				&playback_fd, &playback_id) != 0)
		goto err;

	playback_handle->login_handle = (login_handle_t *)login_handle;
	playback_handle->playback_fd = playback_fd;
	playback_handle->playback_id = playback_id;
	playback_handle->playback_cb = callback;
	playback_handle->param = param;
	playback_handle->stop = 0;

	if (pthread_create(&tid, NULL, recv_playback_data_thread, 
				playback_handle) != 0)
		goto err;
	pthread_detach(tid);

	return playback_handle;

err:
	if (playback_fd != -1)
		close(playback_fd);
	if (playback_handle)
		free(playback_handle);
	return NULL;
}

static int playback_ctl(playback_handle_t *handle, const DWORD ctl_code, 
		const DWORD in_val, DWORD *out_val)
{
	login_handle_t *login_handle;
	NET_VOD_CTL ctl;
	int cmd_id;

	login_handle = handle->login_handle;
	ctl.playback_id = handle->playback_id;
	ctl.ctl_code = ctl_code;

	/* in_val = speed * 1000000 + seekflag * 10000 + percent * 100 */
	ctl.speed = in_val / 1000000;
	ctl.seekflag = (in_val - ctl.speed * 1000000) / 10000;
	ctl.percent = (in_val - ctl.speed * 1000000 - ctl.seekflag * 10000) 
		/ 100;
	printf("playback_ctl: %ld %d %d %d\n", 
			ctl_code, ctl.speed, ctl.seekflag, ctl.percent);

	pthread_mutex_lock(&login_handle->mtx);
	if (send_cmd(login_handle->login_fd, login_handle->user_id, 
				NET_CMD_VOD_RECFILE_CTL, &ctl, 
				sizeof(ctl)) == -1)
		goto err;
	if (recv_cmd(login_handle->login_fd, NULL, &cmd_id, NULL, 0, 
				NULL) == -1)
		goto err;
	if (cmd_id != NET_CMD_VOD_RECFILE_CTL)
		goto err;

	pthread_mutex_unlock(&login_handle->mtx);
	return 0;

err:
	pthread_mutex_unlock(&login_handle->mtx);
	return -1;
}

static int playback_stop(playback_handle_t *handle)
{
	login_handle_t *login_handle = (login_handle_t *)handle->login_handle;
	int playback_id = handle->playback_id;
	int cmd_id;

	/* stop receive data thread */
	handle->stop = 1;

	/* send stop playback command */
	pthread_mutex_lock(&login_handle->mtx);
	if (send_cmd(login_handle->login_fd, login_handle->user_id, 
				NET_CMD_VOD_RECFILE_END, &playback_id, 
				sizeof(playback_id)) == -1)
		goto err;
	if (recv_cmd(login_handle->login_fd, NULL, &cmd_id, NULL, 0, 
				NULL) == -1)
		goto err;
	if (cmd_id != NET_CMD_VOD_RECFILE_END)
		goto err;

	pthread_mutex_unlock(&login_handle->mtx);
	return 0;

err:
	pthread_mutex_unlock(&login_handle->mtx);
	return -1;
}

BOOL HB_NET_Init()
{
	return TRUE;
}

BOOL HB_NET_Cleanup()
{
	return TRUE;
}

LONG HB_NET_GetLastError()
{
	return 0;
}

LONG HB_NET_Login(char *ip, WORD port, char *user, char *pwd, 
		HB_NET_DEVICEINFO *dev_info)
{
	int login_fd = -1;
	int user_id;
	char media_header[MEDIA_HEADER_LEN];
	login_handle_t *handle;
	pthread_t tid;

	/* login DVR */
	login_fd = login_dvr(ip, port, user, pwd, dev_info, &user_id);
	if (login_fd == -1)
		goto err;

	/* get device type */
	if (get_media_header(login_fd, user_id, media_header, 
				sizeof(media_header)) == -1)
		goto err;

	handle = malloc(sizeof(login_handle_t));
	if (handle == NULL)
		goto err;
	handle->login_fd = login_fd;
	handle->user_id = user_id;
	snprintf(handle->dvr_ip, sizeof(handle->dvr_ip), "%s", ip);
	handle->dvr_port = port;
	snprintf(handle->dvr_user, sizeof(handle->dvr_user), "%s", user);
	snprintf(handle->dvr_pwd, sizeof(handle->dvr_pwd), "%s", pwd);
	memcpy(handle->media_header, media_header, sizeof(media_header));
	handle->logout = 0;
	handle->realplay_handles = dlist_init();
	pthread_mutex_init(&handle->mtx, NULL);

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

BOOL HB_NET_Logout(LONG login_handle)
{
	login_handle_t *handle;
	
	handle = (login_handle_t *)login_handle;
	if (login_handle == -1 || handle == NULL)
		return FALSE;

	/* stop heartbeat thread */
	handle->logout = 1;

	return TRUE;
}

LONG HB_NET_RealPlay(LONG login_handle, HB_NET_REALPLAY *info, 
		HB_NET_RealDataCallBack callback, void *param)
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

BOOL HB_NET_StopRealPlay(LONG realplay_handle)
{
	realplay_handle_t *p = (realplay_handle_t *)realplay_handle;
	if (realplay_handle == -1 || p == NULL)
		return FALSE;

	del_realplay(p);
	p->stop = 1;
	return TRUE;
}

LONG HB_NET_FindFile(LONG login_handle, HB_NET_FILEFIND_COND *cond)
{
	login_handle_t *p;
	find_handle_t *find_handle;

	p = (login_handle_t *)login_handle;
	if (login_handle == -1 || p == NULL)
		return -1;

	if (cond == NULL)
		return -1;

	find_handle = convert_find_handle(p, cond);
	if (find_handle == NULL)
		return -1;

	return (LONG)find_handle;
}

LONG HB_NET_FindNextFile(LONG find_handle, HB_NET_FILEINFO *file)
{
	find_handle_t *handle;
	split_time_t bgn, end;
	NET_FILEINFO *pfi;

	handle = (find_handle_t *)find_handle;
	if (find_handle == -1 || handle == NULL || file == NULL)
		return HB_NET_FILE_EXCEPTION;

	if (handle->files_set_index == handle->files_set.files_num) {
next:
		if (split_day_next(handle->split_handle, &bgn, &end) == -1)
			return (handle->no_find) ?  
				HB_NET_FILE_NOFIND : HB_NET_FILE_NOMOFILE;
		if (find_file(handle, &bgn, &end, 0) == -1)
			return HB_NET_FILE_EXCEPTION;
		if (handle->files_set.files_num == 0)
			goto next;

		/*
		printf("----> %04d-%02d-%02d %02d:%02d:%02d "
				"%04d-%02d-%02d %02d:%02d:%02d %ld\n", 
				bgn.year, bgn.mon, bgn.day, bgn.hour, bgn.min,
				bgn.sec,
				end.year, end.mon, end.day, end.hour, end.min,
				end.sec,
				handle->files_set.files_num);
				*/

		handle->no_find = 0;
	}

	pfi = &handle->files_set.files[handle->files_set_index];
	file->bgn.year = pfi->bgn.year + 2000;
	file->bgn.mon  = pfi->bgn.mon;
	file->bgn.day  = pfi->bgn.day;
	file->bgn.hour = pfi->bgn.hour;
	file->bgn.min  = pfi->bgn.min;
	file->bgn.sec  = pfi->bgn.sec;
	file->end.year = pfi->end.year + 2000;
	file->end.mon  = pfi->end.mon;
	file->end.day  = pfi->end.day;
	file->end.hour = pfi->end.hour;
	file->end.min  = pfi->end.min;
	file->end.sec  = pfi->end.sec;
	file->dwFileSize = pfi->dwFileSize;
	file->byChannel = pfi->byChannel;
	file->byType = pfi->byType;

	handle->files_set_index++;
	return HB_NET_FILE_SUCCESS;
}

BOOL HB_NET_FindClose(LONG find_handle)
{
	find_handle_t *handle;

	handle = (find_handle_t *)find_handle;
	if (find_handle == -1 || handle == NULL)
		return FALSE;

	split_day_destory(handle->split_handle);
	free((void *)handle);

	return TRUE;
}

LONG HB_NET_PlayBack(LONG login_handle, HB_NET_PLAYBACK_COND *cond,
		HB_NET_PlayBackDataCallBack callback, void *param)
{
	NET_VOD vod;
	playback_handle_t *playback_handle;

	vod.byChannel= cond->dwChannel;
	vod.byType   = HB_NET_REC_ALL;
	vod.bgn.year = cond->bgn.year - 2000;
	vod.bgn.mon  = cond->bgn.mon;
	vod.bgn.day  = cond->bgn.day;
	vod.bgn.hour = cond->bgn.hour;
	vod.bgn.min  = cond->bgn.min;
	vod.bgn.sec  = cond->bgn.sec;

	playback_handle = playback(login_handle, NET_CMD_VOD_RECFILE, 
			(void *)&vod, sizeof(NET_VOD), callback, param);
	if (playback_handle == NULL)
		return -1;

	return (LONG)playback_handle;
}

BOOL HB_NET_PlayBackControl(LONG playback_handle, DWORD dwControlCode, 
	DWORD dwInValue, DWORD *lpOutValue)
{
	playback_handle_t *handle = (playback_handle_t *)playback_handle;
	if (playback_handle == -1 || handle == NULL)
		return FALSE;

	if (playback_ctl(handle, dwControlCode, dwInValue, lpOutValue) != 0)
		return FALSE;
	return TRUE;
}

BOOL HB_NET_StopPlayBack(LONG playback_handle)
{
	playback_handle_t *handle = (playback_handle_t *)playback_handle;
	if (playback_handle == -1 || handle == NULL)
		return FALSE;

	playback_stop(handle);
	return TRUE;
}
