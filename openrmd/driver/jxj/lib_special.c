#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "tcpconn.h"
#include "specialipc.h"

#define PROXY_IP	"127.0.0.1"
#define PROXY_PORT	7008
#define PROXY_USER	"proxy"
#define PROXY_PWD	"proxy"

NORMAL_H264_SDP_CONTENT_FUNC

static int login(char *ip, int port, char *user, char *pwd)
{
	int login_id = tcpconn(ip, port, CONN_TIMEOUT);
	if (login_id == -1)
		return -1;
	syslog(LOG_DEBUG, "connect JXJ proxy success[%s:%d]", ip, port);

	return login_id;
}

static int logout(int login_id)
{
	if (login_id == -1)
		return -1;

	close(login_id);
	syslog(LOG_DEBUG, "logout %s", DEV_NAME);
	return 0;
}

static int realplay_start(void *info)
{
	realplay_info_t *p = (realplay_info_t *)info;
//	char buff[1024];

	/* connect */
	p->login_id = login(PROXY_IP, PROXY_PORT, PROXY_USER, PROXY_PWD);
	if (p->login_id == -1)
		return -1;

//	snprintf(buff, sizeof(buff), "", p->ip, p->port, p->user, p->pwd);
			
	/* send command */
	send(p->login_id, "hello", 5, 0);

	return 0;
}

static int realplay_stop(void *info)
{
	realplay_info_t *p = (realplay_info_t *)info;
	logout(p->login_id);
	p->login_id = -1;
	return 0;
}

static int ptz_ctl(unsigned long handle, ptz_ctl_info_t *info)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1 || p == NULL)
		return -1;

	//send(p->login_id, NULL, 0, 0);
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
	info->pkt_cb = rtp_packetization_h264;
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

int special_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return ptz_ctl(handle, info);
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	return ptz_ctl(handle, info);
}
