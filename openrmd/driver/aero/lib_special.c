#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "tcpconn.h"
#include "recvn.h"
#include "set_recv_timeout.h"
#include "specialipc.h"

/*
main 461670124 byte 23:11 - 37:51  880s  524,625 byte/s  4,197,000 bit/s
sub   35043122 byte 04:46 - 08:15  209s  167,670 byte/s  1,341,363 bit/s
*/

NORMAL_H264_SDP_CONTENT_FUNC

int send_cmd(int login_id, char *buff, int cmd_len)
{
	unsigned short parity = 0;
	int i;

	for(i = 0; i < cmd_len; i++)
		parity += (unsigned char)buff[i];
	*(unsigned short*)&buff[cmd_len] = parity;

	if (send(login_id, buff, CMDBUFF_LEN, 0) < 0)
		return -1;

	return 0;
}

int recv_cmd(int login_id, char *buff)
{
	if (recvn(login_id, buff, CMDBUFF_LEN, 0) <= 0)
		return -1;

	return 0;
}

int login(char *ip, int port, char *user, char *pwd)
{
	int login_id;

	login_id = tcpconn(ip, port, CONN_TIMEOUT);
	if (login_id == -1)
		return -1;

	//syslog(LOG_DEBUG, "connect camera success[%s:%d %d]", 
	//		ip, port, login_id);
	return login_id;
}

int logout(int login_id)
{
	if (login_id == -1)
		return -1;

	close(login_id);
	//syslog(LOG_DEBUG, "logout %s %d", DEV_NAME, login_id);
	return 0;
}

static int realplay_start(void *info)
{
	realplay_info_t *p = (realplay_info_t *)info;

	p->login_id = login(p->ip, p->port, p->user, p->pwd);
	if (p->login_id == -1)
		return -1;

	set_recv_timeout(p->login_id, RECV_TIMEOUT);

	char buff[CMDBUFF_LEN] = {0x40, 0xF0};
	VAL[2] = 1;
	VAL[6]  = (p->channel_id == 1 ? 1 : 2);  /* 1:main 2:sub */

	/* set resolving capability */
	VAL[8]  = 3;	/* resolving */
	//VAL[10] = (p->channel_id == 1 ? 1 : 3); /* 1:1920x1080 3:704x576 */
	VAL[10] = p->channel_id; /* 1:1920x1080 2:1280x720 3:704x576 */
	VAL[LEN_POS] = 12;
	if (send_cmd(p->login_id, buff, VAL[LEN_POS]) != 0)
		goto err;
	if (recv_cmd(p->login_id, buff) != 0)
		goto err;

	/* set rate */
	VAL[8]  = 5;	/* rate */
	VAL[10] = 2;	/* fixed rate */
	VAL[12]  = (p->channel_id == 1 ? 6000 : 2000);
	VAL[LEN_POS] = 14;
	if (send_cmd(p->login_id, buff, VAL[LEN_POS]) != 0)
		goto err;
	if (recv_cmd(p->login_id, buff) != 0)
		goto err;

	/* set encoder */
	VAL[8]  = 1;	/* encoder */
	VAL[10] = 1;	/* 1:H.264 2:MJPEG */
	VAL[12] = 1;
	VAL[14] = 0;
	VAL[16] = 0;
	VAL[18] = 0;
	VAL[LEN_POS] = 20;
	if (send_cmd(p->login_id, buff, VAL[LEN_POS]) != 0)
		goto err;
	if (recv_cmd(p->login_id, buff) != 0)
		goto err;

	return 0;

err:
	logout(p->login_id);
	p->login_id = -1;
	return -1;
}

static int realplay_stop(void *info)
{
	realplay_info_t *p = (realplay_info_t *)info;
	logout(p->login_id);
	p->login_id = -1;
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// special implementation
////////////////////////////////////////////////////////////////////////////

int special_init()
{
	return 0;
}

int special_uninit()
{
	return 0;
}

int special_get_describe(realplay_info_t *info, char **sdp)
{
	return normal_h264_sdp_content(info, sdp, "", DEFAULT_FPS);
}

unsigned long special_start_realplay(realplay_info_t *info)
{
	info->fp_realplay_start = realplay_start;
	info->fp_realplay_stop = realplay_stop;
	return specialipc_start_realplay(info);
}

int special_stop_realplay(unsigned long handle)
{
	specialipc_stop_realplay(handle);
	syslog(LOG_DEBUG, "stop_realplay %s success.", DEV_NAME);
	return 0;
}

int special_make_key_frame(unsigned long handle)
{
	return 0;
}
