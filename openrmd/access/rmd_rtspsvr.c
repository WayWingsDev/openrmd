#include "rmd_rtspsvr.h"
#include "rmd.h"
#include "rmd_devmgr.h"
#include "rmd_sessmgr.h"
#include "rtspsvr.h"
#include "getcfg.h"

#define DEFAULT_CLIENTS		256

static int parse_url(const char *url, rmd_session_t *sess)
{
	char plat[PLAT_SIZE];
	if (sscanf(url, "real/%[^-]-%d-%d-%d-%[^.].%s", 
				plat, &sess->driver_type, 
				&sess->device_id, &sess->channel_id, 
				sess->stream_opt, sess->stream_fmt) != 6)
		return -1;
	return 0;
}

#ifdef RMD_DYNAMIC_DEVICES
static int parse_url_dynamic(const char *url, rmd_session_t *sess, 
		device_t *tmp_device, device_t **device)
{
	char plat[PLAT_SIZE];

	if (sscanf(url, "real/%[^-]-%d-%d-%d-%[^.].%[^-]"
				"-%[^:]:%d:%[^:]:%[^-]"
				"-%s", 
				plat, 
				&sess->driver_type, 
				&sess->device_id, 
				&sess->channel_id, 
				sess->stream_opt, 
				sess->stream_fmt,
				tmp_device->ip, 
				&tmp_device->port, 
				tmp_device->user, 
				tmp_device->pwd, 
				sess->user) != 11)
		return -1;

	tmp_device->id = sess->device_id;
	*device = tmp_device;
	return 0;
}
#endif

static int lookup_device(const char *url, rmd_session_t *sess,
		driver_t **driver, device_t **device, channel_t **channel)
{
	if (parse_url(url, sess) != 0)
		return -1;
	if (rmd_devmgr_lookup_channel(sess->driver_type, sess->device_id, 
				sess->channel_id, driver, device, 
				channel) != 0) {
		syslog(LOG_DEBUG, "channel not exist[%s]", url);
		return -1;
	}
	return 0;
}

#ifdef RMD_DYNAMIC_DEVICES
static int lookup_device_dynamic(const char *url, rmd_session_t *sess,
		device_t *tmp_device,
		driver_t **driver, device_t **device, channel_t **channel)
{
	if (parse_url_dynamic(url, sess, tmp_device, device) == 0) {
		*driver = rmd_devmgr_get_driver(sess->driver_type);
		if (*driver == NULL)
			return -1;
		return 0;
	}

	return lookup_device(url, sess, driver, device, channel);
}
#endif

static int describe_callback(rtspsvr_cbp_t *cbp)
{
	realplay_info_t info;
	rmd_session_t sess;
	driver_t *driver = NULL;
	device_t *device = NULL;
	channel_t *channel = NULL;

#ifndef RMD_DYNAMIC_DEVICES
	if (lookup_device(cbp->url, &sess, &driver, &device, &channel) != 0)
		return -1;
#else
	device_t tmp_device;
	if (lookup_device_dynamic(cbp->url, &sess, &tmp_device, 
				&driver, &device, &channel) != 0)
		return -1;
#endif

	snprintf(info.ip, sizeof(info.ip), device->ip);
	info.port = device->port;
	snprintf(info.user, sizeof(info.user), device->user);
	snprintf(info.pwd, sizeof(info.pwd), device->pwd);
	info.channel_id = sess.channel_id;
	info.hdr_cb = NULL;
	info.data_cb = NULL;

	return driver->rmd_di_get_describe(&info, &cbp->sdp);
}

static int setup_callback(rtspsvr_cbp_t *cbp)
{
	rmd_session_t sess;
	device_t *new_device = NULL;

	if (rmd_sessmgr_is_valid_sid(cbp->sid) != 0)
		return -1;

	memset(&sess, 0, sizeof(sess));

#ifndef RMD_DYNAMIC_DEVICES
	if (parse_url(cbp->url, &sess) != 0)
		return -1;
#else
	device_t tmp_device;
	driver_t *driver = NULL;
	device_t *device = NULL;
	channel_t *channel = NULL;
	if (parse_url_dynamic(cbp->url, &sess, &tmp_device, 
				&new_device) != 0) {
		if (lookup_device(cbp->url, &sess, &driver, &device, 
					&channel) != 0)
			return -1;
		new_device = device;
	}
#endif

	if (rtsp_istcp(cbp->trans))
		sess.trans_method = TRANS_VIA_TCP;
	else
		sess.trans_method = TRANS_VIA_UDP;

	snprintf(sess.sid, sizeof(sess.sid), cbp->sid);
	return rmd_sessmgr_add(&sess, new_device, cbp->client_fd, cbp->cliip, 
		cbp->cli_rtp_port, cbp->cli_rtcp_port, &cbp->svr_rtp_port);
}

static int play_callback(char *sid, rtspsvr_play_succ_callback_t succ_cb,
		void *param)
{
	return rmd_sessmgr_play(sid, succ_cb, param);
}

static int teardown_callback(char *sid)
{
	return rmd_sessmgr_del(sid);
}

static rtspsvr_callback_t callback = {
	describe_callback,
	setup_callback,
	play_callback,
	NULL,
	teardown_callback
};

int rmd_rtspsvr_start()
{
	int lsnport, max_clients;

	if (getcfg(cfg_file, "rtsp_port", &lsnport, GETCFG_INT32) != 0)
		lsnport = RTSP_PORT;
	if (getcfg(cfg_file, "max_clients", &max_clients, GETCFG_INT32) != 0)
		max_clients = DEFAULT_CLIENTS;
	syslog(LOG_INFO, "max clients: %d", max_clients);

	return rtspsvr_start(lsnport, max_clients, &callback);
}

int rmd_rtspsvr_stop()
{
	return rtspsvr_stop();
}

void rmd_rtspsvr_trigger_hangup(int sock)
{
	shutdown(sock, SHUT_RD);
}
