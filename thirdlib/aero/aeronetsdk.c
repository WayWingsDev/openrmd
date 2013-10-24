#include "aeronetsdk.h"
#include "syshdr.h"
#include "tcpconn.h"
#include "recvn.h"
#include "set_recv_timeout.h"
#include "set_send_timeout.h"

#define CONN_TIMEOUT	3
#define RECV_TIMEOUT	20
#define SEND_TIMEOUT	5
#define CMDBUFF_LEN	25		/* command buffer length */
#define VAL		*(unsigned short *)&buff
#define LEN_POS		4
#define FRAME_SIZE	(1024 * 200)	/* frame buffer size */

#define DATA_SIZE	(1024 * 300)
#define FLAG_SIZE	4		/* {0xAA, 0xBB, 0xCC, 0xDD} */

typedef struct {
	unsigned char hdr_buff[HDR_SIZE]; /* buffer to hold header */
	int  hdr_bytes;			/* the bytes used of header buffer */
	int  data_len;			/* actual length of data flow header */
	int  timestamp;			/* time stamp */

	char data_buff[DATA_SIZE];	/* buffer to hold data */
	int  data_bytes;		/* the bytes used of data buffer */
} hdr_t;

/* login handle info */
typedef struct {
	int	login_fd;
	char	ip[32];
	int	port;
	char	user[32];	
	char	pwd[16];
} login_handle_t;

/* realplay handle info */
typedef struct {
	login_handle_t *login_handle;
	int channel_id;
	aero_net_realdata_callback_t data_cbk;
	void	*data_param;
	aero_net_state_callback_t state_cbk;
	void	*state_param;
	hdr_t	hdr;
	int	stop;
} realplay_handle_t;

static int is_valid_flag(unsigned char *buff, int bytes)
{
	static unsigned char flag[] = {0xAA, 0xBB, 0xCC, 0xDD};
	int i;

	if (bytes > HDR_SIZE)
		return -1;

	for (i = 0; i < bytes; i++)
		if (flag[i] != buff[i])
			return -1;
	return 0;
}

/* process flag */
static int read_flag(unsigned char *buff, int bytes, hdr_t *hdr, int *left)
{
	int len;
	int i = 0;

	if (buff == NULL || bytes <= 0 || left == NULL)
		return -1;

	/* the header already ready */
	if (hdr->hdr_bytes == HDR_SIZE) {
		//printf("- return directly\n");
		return 0;
	}

	/* lookup the start of flag */
	if (hdr->hdr_bytes == 0) {
		for (i = 0; i < bytes - FLAG_SIZE; i++) {
			if (is_valid_flag(&buff[i], FLAG_SIZE) == 0)
				break;
		}

		/* interceptd flag */
		if ((bytes - i) < FLAG_SIZE) {
			if (is_valid_flag(&buff[i], bytes - i) != 0)
				return -1;
		}
	}

	/* copy some bytes into header buffer */
	len = HDR_SIZE - hdr->hdr_bytes;
	if (len > bytes)
		len = bytes;
	//printf("- i=%d %2X %2X %2X %2X\n", 
	//		i, buff[i], buff[i+1], buff[i+2], buff[i+3]);
	memcpy(&hdr->hdr_buff[hdr->hdr_bytes], &buff[i], len);
	hdr->hdr_bytes += len;

	if (hdr->hdr_bytes != HDR_SIZE)
		return -1;

	//printf("- hdr_bytes=%d\n", hdr->hdr_bytes);

	/* flag now is ready, verify it again, and get data length */
	if (is_valid_flag(hdr->hdr_buff, FLAG_SIZE) != 0) {
		hdr->hdr_bytes = 0;
		//printf("- invalid flag\n");
		return -1;
	}

	memcpy(&hdr->data_len, &hdr->hdr_buff[4], sizeof(int));
	if (hdr->data_len <= 0 || hdr->data_len > DATA_SIZE) {
		/* invalid media length */
		hdr->data_len = 0;
		hdr->hdr_bytes = 0;
		//printf("- invalid data length\n");
		return -1;
	}

	*left -= (i + len);
	assert(*left >= 0);
	//printf("- bytes:%6d data_len:%6d left:%d\n", 
	//		bytes, hdr->data_len, *left);
	return 0;
}

/* process media */
static int read_data(unsigned char *buff, int bytes, 
		aero_net_pure_data_callback_t cbk, void *param, 
		hdr_t *hdr, int *left)
{
	int len;

	len = hdr->data_len - hdr->data_bytes;
	if (len > bytes)
		len = bytes;
	//printf("+ bytes:%6d data_len:%6d data: %6d need_copy :%6d\n", 
	//		bytes, hdr->data_len, hdr->data_bytes, len);
	memcpy(&hdr->data_buff[hdr->data_bytes], buff, len);
	hdr->data_bytes += len;
	*left -= len;

	if (hdr->data_bytes >= hdr->data_len) {
		if (cbk)
			cbk(hdr->data_buff, hdr->data_len, param);

		//printf("+ reset\n");
		hdr->data_bytes = 0;
		hdr->hdr_bytes = 0;	/* reset it */
		hdr->data_len = 0;
	}
	return 0;
}

static void show_cmd(char *buff)
{
	int i;

	for (i = 0; i < CMDBUFF_LEN; i++)
		printf("%02X ", (unsigned char)buff[i]);
	printf("\n");
}

static int send_cmd(int login_id, char *buff, int cmd_len)
{
	unsigned short parity = 0;
	int i;

	for(i = 0; i < cmd_len; i++)
		parity += (unsigned char)buff[i];
	*(unsigned short*)&buff[cmd_len] = parity;

	show_cmd(buff);

	if (send(login_id, buff, CMDBUFF_LEN, 0) < 0)
		return -1;

	return 0;
}

static int recv_cmd(int login_id, char *buff)
{
	if (recvn(login_id, buff, CMDBUFF_LEN, 0) <= 0)
		return -1;

	show_cmd(buff);

	return 0;
}

static int realplay(int login_fd, int channel_id)
{
	char buff[CMDBUFF_LEN] = {0x40, 0xF0};
	VAL[2] = 1;
	VAL[6]  = (channel_id == 1 ? 1 : 2);  /* 1:main 2:sub */

	/* set resolving capability */
	VAL[8]  = 3;	/* resolving */
	VAL[10] = (channel_id == 1 ? 1 : 3); /* 1:1920x1080 3:704x576 */
	VAL[LEN_POS] = 12;

	if (send_cmd(login_fd, buff, VAL[LEN_POS]) != 0)
		return -1;
	if (recv_cmd(login_fd, buff) != 0)
		return -1;

	/* set rate */
	VAL[8]  = 5;	/* rate */
	VAL[10] = 2;	/* fixed rate */
	VAL[12]  = (channel_id == 1 ? 5000 : 2000);
	VAL[LEN_POS] = 14;

	if (send_cmd(login_fd, buff, VAL[LEN_POS]) != 0)
		return -1;
	if (recv_cmd(login_fd, buff) != 0)
		return -1;

	/* set encoder */
	VAL[8]  = 1;	/* encoder */
	VAL[10] = 1;	/* 1:H.264 2:MJPEG */
	VAL[12] = 1;
	VAL[14] = 0;
	VAL[16] = 0;
	VAL[18] = 0;
	VAL[LEN_POS] = 20;
	if (send_cmd(login_fd, buff, VAL[LEN_POS]) != 0)
		return -1;
	if (recv_cmd(login_fd, buff) != 0)
		return -1;

	return 0;
}

/* re-connect until success, return 0 if success, otherwise, return -1 */
static int re_connect(realplay_handle_t *info)
{
	login_handle_t *login_handle = info->login_handle;
	int fd;

	while (info->stop == 0) {
		fd = tcpconn(login_handle->ip, login_handle->port, 20);
		if (fd == -1) {
			sleep(10);
			continue;
		}
		set_recv_timeout(fd, RECV_TIMEOUT);
		set_send_timeout(fd, SEND_TIMEOUT);

		if (realplay(fd, info->channel_id) == -1) {
			sleep(10);
			close(fd);
			continue;
		}

		login_handle->login_fd = fd;
		return 0;
	}

	return -1;
}

/* receive real data thread */
static void *recv_real_data_thread(void *arg)
{
	realplay_handle_t *info = (realplay_handle_t *)arg;
	int *fd = &(info->login_handle->login_fd);
	char buff[FRAME_SIZE];
	int bytes;

	while (info->stop == 0) {
		bytes = recv(*fd, buff, sizeof(buff), 0);
		if (bytes <= 0) {
			if (info->state_cbk)
				info->state_cbk(0, info->state_param);
			close(*fd);
			*fd = -1;

			if (re_connect(info) == -1)
				break;
			if (info->state_cbk)
				info->state_cbk(1, info->state_param);
			continue;
		}

		info->data_cbk((unsigned long)arg, buff, bytes, 
				info->data_param);
	}

	if (*fd != -1)
		close(*fd);
	free(info);
	return NULL;
}

int aero_net_init()
{
	return 0;
}

int aero_net_cleanup()
{
	return 0;
}

long aero_net_get_lasterror()
{
	return 0;
}

unsigned long aero_net_login(char *ip, int port, char *user, char *pwd)
{
	login_handle_t *handle;
	int fd;

	handle = malloc(sizeof(login_handle_t));
	if (handle == NULL)
		return -1;

	fd = tcpconn(ip, port, CONN_TIMEOUT);
	if (fd == -1) {
		free(handle);
		return -1;
	}

	set_recv_timeout(fd, RECV_TIMEOUT);
	set_send_timeout(fd, SEND_TIMEOUT);

	handle->login_fd = fd;
	snprintf(handle->ip, sizeof(handle->ip), ip);
	handle->port = port;
	snprintf(handle->user, sizeof(handle->user), user);
	snprintf(handle->pwd, sizeof(handle->pwd), pwd);

	return (unsigned long)handle;
}

int aero_net_logout(unsigned long login_handle)
{
	login_handle_t *p = (login_handle_t *)login_handle;
	if (login_handle == -1 || p == NULL)
		return -1;

	if (p->login_fd)
		close(p->login_fd);
	free(p);
	return 0;
}

unsigned long aero_net_realplay(unsigned long login_handle, int channel_id,
		aero_net_realdata_callback_t data_cbk, void *data_param,
		aero_net_state_callback_t state_cbk, void *state_param)
{
	realplay_handle_t *realplay_handle = NULL;
	login_handle_t *handle = NULL;
	pthread_t tid;

	handle = (login_handle_t *)login_handle;
	if (login_handle == -1 || handle == NULL)
		return -1;

	if (realplay(handle->login_fd, channel_id) == -1)
		goto err;

	realplay_handle = calloc(1, sizeof(realplay_handle_t));
	if (realplay_handle == NULL)
		goto err;
	realplay_handle->login_handle = handle;
	realplay_handle->channel_id = channel_id;
	realplay_handle->data_cbk = data_cbk;
	realplay_handle->data_param = data_param;
	realplay_handle->state_cbk = state_cbk;
	realplay_handle->state_param = state_param;
	realplay_handle->stop = 0;

	if (pthread_create(&tid, NULL, recv_real_data_thread, 
				realplay_handle) != 0)
		goto err;
	pthread_detach(tid);

	return (unsigned long)realplay_handle;

err:
	if (realplay_handle)
		free(realplay_handle);
	return -1;
}

void aero_net_extract_pure_data(unsigned long realplay_handle, 
		unsigned char *buff, int bytes, 
		aero_net_pure_data_callback_t cbk, void *param)
{
	//printf("---> bytes: %d\n", bytes);

	realplay_handle_t *p = (realplay_handle_t *)realplay_handle;
	int left = bytes;

	if (realplay_handle == -1 || p == NULL)
		return;

	if (read_flag(buff, bytes, &p->hdr, &left) != 0)
		return;

	if (read_data(&buff[bytes - left], left, cbk, param, &p->hdr, 
				&left) != 0)
		return;

	if (left > 0)
		aero_net_extract_pure_data(realplay_handle, 
				&buff[bytes - left], left, cbk, param);
}

int aero_net_stop_realplay(unsigned long realplay_handle)
{
	realplay_handle_t *p = (realplay_handle_t *)realplay_handle;
	if (realplay_handle == -1 || p == NULL)
		return -1;
	p->stop = 1;
	return 0;
}

/////////////////////////
// PTZ

//typedef struct {
//	int baud_rate;
//	int index;
//} baud_rate_t;
//
//static baud_rate_t baud_rate_table[] = {
//	{2400,   1},
//	{4800,   2},
//	{9600,   3},
//	{19200,  4},
//	{38400,  5},
//	{115200, 6}
//};

//static int baud_rate_trans(const int baud_rate)
//{
//	int i;
//	for (i = 0; i < sizeof(baud_rate_table) / sizeof(baud_rate_t); i++) {
//		if (baud_rate_table[i].baud_rate == baud_rate)
//			return baud_rate_table[i].index;
//	}
//	return 3;	/* default: 9600 */
//}

//static int ptz_init(int login_id, int baud_rate)
//{
//	char buff[CMDBUFF_LEN] = {0x20, 0xF0};
//
//	VAL[2]  = 4;
//	VAL[LEN_POS] = 8;
//	VAL[6]  = 1;
//	if (send_cmd(login_id, buff, VAL[LEN_POS]) != 0)
//		return -1;
//	if (recv_cmd(login_id, buff) != 0)
//		return -1;
//
//	VAL[2]  = 1;
//	VAL[LEN_POS] = 22;
//	VAL[6]  = 1;		/* RS232 */
//	VAL[8]  = baud_rate_trans(baud_rate);
//	VAL[10] = 4;		/* 8 */
//	VAL[12] = 3;
//	VAL[14] = 1;
//	VAL[16] = 3;
//	VAL[18] = 1;
//	VAL[20] = 1;
//
//	if (send_cmd(login_id, buff, VAL[LEN_POS]) != 0)
//		return -1;
//	if (recv_cmd(login_id, buff) != 0)
//		return -1;
//	return 0;
//}

//int _ctl_ptz(int *login_id, ptz_ctl_info_t *info)
//{
//	char buff[CMDBUFF_LEN] = {0x20, 0xF0};
//	VAL[2]   = 3;
//	VAL[LEN_POS] = 14;
//	VAL[6]   = info->ctl_code;
//	VAL[8]   = info->param1;
//	VAL[10]  = info->param2;
//	VAL[12]  = info->param3;
//
//	if (send_cmd(*login_id, buff, VAL[LEN_POS]) != 0)
//		goto err;
//	if (recv_cmd(*login_id, buff) != 0)
//		goto err;
//	return 0;
//
//err:
//	return -1;
//}

//int special_ctl_cam(int *login_id, ptz_ctl_info_t *info)
//{
//	char buff[CMDBUFF_LEN] = {0x30, 0xF0};
//	VAL[2]   = 1;
//	VAL[6]   = info->ctl_code;
//	VAL[8]   = info->param1;
//	VAL[10]  = info->param2;
//	VAL[12]  = info->param3;
//
//	if (info->ctl_code == 1) {		/* zoom */
//		if (info->param1 >= 0 && info->param1 <= 3)
//			VAL[LEN_POS] = P1;
//		else
//			VAL[LEN_POS] = P1P2;
//	} else if (info->ctl_code == 2) {	/* focus */
//		VAL[LEN_POS] = P1P2;
//	} else if (info->ctl_code == 3) {
//	} else if (info->ctl_code == 4) {	/* aperture */
//		VAL[LEN_POS] = P1P2;
//	} else {
//		/* TODO */
//		return -1;
//	}
//
//	if (send_cmd(*login_id, buff, VAL[LEN_POS]) != 0)
//		goto err;
//	if (recv_cmd(*login_id, buff) != 0)
//		goto err;
//	return 0;
//
//err:
//	return -1;
//}
