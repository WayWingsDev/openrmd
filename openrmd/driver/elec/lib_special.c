#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "tcpconn.h"
#include "recvn.h"
#include "set_recv_timeout.h"
#include "specialipc.h"

#define HIK_HDR_LEN	40

/* device type */
#define ELEC_HIK	1
#define ELEC_DAHUA	2

#define ELEC_PAYLOAD	160

/* sps flag */
#define SPS_FLAG_HIK	"0001"
#define SPS_FLAG_DAHUA	"0002"

/* for example: in_hdr[] = {0x1A, 0x56} => out_hdr[] = {'1', 'A', '5', '6'} */
static void conv_sps_for_nari(unsigned char *in_hdr, const int in_len, 
		char *out_hdr)
{
	int i, j;
	int val;

	for (i = 0; i < in_len; i++) {
		for (j = 0; j < 2; j++) {
			val = (j == 0 ? in_hdr[i] >> 4 : in_hdr[i] & 0x0F);

			if (val >= 0 && val <= 9)
				val += 48;
			else
				val += 55;
			out_hdr[i * 2 + j] = val;
		}
	}
}

static int realplay_start(void *info)
{
	realplay_info_t *p = (realplay_info_t *)info;

	/* connect */
	p->login_id = tcpconn(p->ip, p->port, CONN_TIMEOUT);
	if (p->login_id == -1) {
		printf("connect server error\n");
		return -1;
	}
	set_recv_timeout(p->login_id, RECV_TIMEOUT);

	/* apply */
	apply_t app;
	cmd_t cmd;

	snprintf(app.plat, sizeof(app.plat), p->plat);
	app.dev_type = p->device_type;
	app.dev_id = p->device_id;
	app.cnl_id = p->channel_id;
	app.stream_opt = STREAM_MAIN;

	cmd.syn_flag = CMDSYN;
	cmd.cmdid = CMD_REALPLAY;
	cmd.buff_length = sizeof(app);
	memcpy(cmd.buff, &app, sizeof(app));

	if (send(p->login_id, &cmd, CMDHEAD + cmd.buff_length, 0) == -1) {
		printf("Send command error.\n");
		goto err;
	}
	if (recv(p->login_id, &cmd, CMDHEAD + 4, 0) < CMDHEAD + 4)
		goto err;

	if (cmd.syn_flag != CMDSYN || cmd.cmdid != CMD_REPLY)
		goto err;

	int ret = (int)*cmd.buff;
	if (ret != R_SUCCESS) {
		printf("realplay error[%s %d %d %d]\n",
				p->plat, p->device_type,
				p->device_id, p->channel_id);
		goto err;
	}

	return 0;

err:
	close(p->login_id);
	return -1;
}

static int realplay_stop(void *info)
{
	realplay_info_t *p = (realplay_info_t *)info;
	if (p->login_id != -1)
		close(p->login_id);
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
	char *buff = NULL;
	const int sdp_size = 512;
	buff = malloc(sdp_size);
	if (buff == NULL)
		return -1;

	if (info->device_type == ELEC_HIK) {
		unsigned char hdr[HIK_HDR_LEN];
		char sps[HIK_HDR_LEN * 2 + 1];

		if (realplay_start(info) != 0)
			goto err;

		/* receive the media header (the first HIK_HDR_LEN bytes) */
		if (recvn(info->login_id, hdr, sizeof(hdr), 0) != sizeof(hdr))
			goto err;

		realplay_stop(info);

		conv_sps_for_nari(hdr, HIK_HDR_LEN, sps);
		sps[sizeof(sps) - 1] = '\0';

		snprintf(buff, sdp_size, 
				"v=0\r\n"
				"o=- 0 0 IN IP4 %s\r\n"
				"s=-\r\n"
				"c=IN IP4 %s\r\n"
				"m=video %d RTP/AVP %d\r\n"
				"a=rtpmap:%d HIK264/90000\r\n"
				"a=fmtp:%d CIF=1\r\n"
				"a=fmtp:%d profile-level-id=420028;"
				"sprop-parameter-sets=%s%s\r\n"
				"a=sendonly\r\n\r\n",
				info->local_ip,
				info->local_ip,
				info->svr_rtp_port, ELEC_PAYLOAD,
				ELEC_PAYLOAD,
				ELEC_PAYLOAD,
				ELEC_PAYLOAD,
				sps, SPS_FLAG_HIK);
	} else if (info->device_type == ELEC_DAHUA) {
		char sps[40 * 2 + 1];

		memset(sps, '0', sizeof(sps));
		sps[sizeof(sps) - 1] = '\0';

		snprintf(buff, sdp_size, 
				"v=0\r\n"
				"o=- 0 0 IN IP4 %s\r\n"
				"s=-\r\n"
				"c=IN IP4 %s\r\n"
				"m=video %d RTP/AVP %d\r\n"
				"a=rtpmap:%d DAHUA264/90000\r\n"
				"a=fmtp:%d CIF=1\r\n"
				"a=fmtp:%d profile-level-id=420028;"
				"sprop-parameter-sets=%s%s\r\n"
				"a=sendonly\r\n\r\n",
				info->local_ip,
				info->local_ip,
				info->svr_rtp_port, ELEC_PAYLOAD,
				ELEC_PAYLOAD,
				ELEC_PAYLOAD,
				ELEC_PAYLOAD,
				sps, SPS_FLAG_DAHUA);
	} else {
		goto err;
	}

	*sdp = buff;
	return 0;

err:
	if (buff != NULL)
		free(buff);
	realplay_stop(info);
	return -1;
}

unsigned long special_start_realplay(realplay_info_t *info)
{
	info->pkt_cb = rtp_packetization_h264_simple;
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
	return 0;
}

int special_ctl_cam(int *login_id, unsigned long handle,
		ptz_ctl_info_t *info)
{
	return 0;
}
