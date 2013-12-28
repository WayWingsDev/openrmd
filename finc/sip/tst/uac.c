#include <unistd.h>
#include "sipua.h"

static sipua_callback sipua_cbk;

static void on_reg_state(sipua_acc_id acc_id, sipua_reg_info *info)
{
	int code;

	code = info->cbparam->code;
	if (code == PJSIP_SC_OK)
		printf("register success\n");
	else
		printf("register return code: %d\n", code);
}

void on_call_state(sipua_call_id call_id, sipua_event *e)
{
	sipua_call_info ci;

	sipua_call_get_info(call_id, &ci);

	switch (ci.state) {
		case PJSIP_INV_STATE_CONNECTING:    /* After 2xx is received */
			printf("call [%d] success\n", call_id);
			break;
		case PJSIP_INV_STATE_DISCONNECTED: /* Session is terminated */
			printf("call [%d] terminated\n", call_id);
			break;
		default:
			return;
	}
}

void on_pager(sipua_call_id call_id, const sipua_str_t *from,
		const sipua_str_t *to, const sipua_str_t *contact,
		const sipua_str_t *mime_type, const sipua_str_t *body)
{
	printf("--------> on_pager\n");
}

int main(int argc, char **argv)
{
	int ret;
	char *user, *pwd, *domain, *call_url;
	int port, reg, log_level;

	if (argc != 8) {
		printf("Usage: %s <user> <pwd> <domain> <port> "
				" <call url> <reg (0:not reg 1: reg)> "
				"<log level (0:none 7:all)>\n", 
				argv[0]);
		printf("e.g. : %s user1 user1 192.168.100.100 5060 "
				"sip:user2@192.168.100.100 1 0\n", argv[0]);
		exit(1);
	}
	user = argv[1];
	pwd = argv[2];
	domain = argv[3];
	port = atoi(argv[4]);
	call_url = argv[5];
	reg = atoi(argv[6]);
	log_level = atoi(argv[7]);

	/* 1. initialize */
	memset(&sipua_cbk, 0, sizeof(sipua_callback));
	sipua_cbk.on_reg_state = on_reg_state;
	sipua_cbk.on_call_state = on_call_state;
	sipua_cbk.on_pager = on_pager;

	ret = sipua_init(user, pwd, domain, port, &sipua_cbk, 8, reg, 
			log_level);
	if (ret != 0) {
		printf("sipua_init() failed\n");
		exit(1);
	}
	printf("sipua_init() success\n");

	/* 2. make a call */
	char *sdp = "v=0\r\n"
		"o=adapter 0 0 IN IP4 0.0.0.0\r\n"
		"s=-\r\n"
		"c=IN IP4 192.168.1.10\r\n"
		"m=video 10002 RTP/AVP 96\r\n"
		"a=rtpmap:96 H264/9600\r\n"
		"a=ResID:301001-0035\r\n"
		"a=rtype:0\r\n"
		"a=rip:192.168.1.10\r\n"
		"a=rport:7000\r\n"
		"a=ruser:test\r\n"
		"a=rpwd:test\r\n"
		"a=recvonly\r\n"
		"\r\n";

//	char *sdp = "v=0\r\n"
//		"o=user2 1669 3137 IN IP4 192.168.1.10\r\n"
//		"s=Talk\r\n"
//		"c=IN IP4 192.168.1.10\r\n"
//		"t=0 0\r\n"
//		"m=audio 7078 RTP/AVP 112 111 110 3 0 8 101\r\n"
//		"a=rtpmap:112 speex/32000\r\n"
//		"a=fmtp:112 vbr=on\r\n"
//		"a=rtpmap:111 speex/16000\r\n"
//		"a=fmtp:111 vbr=on\r\n"
//		"a=rtpmap:110 speex/8000\r\n"
//		"a=fmtp:110 vbr=on\r\n"
//		"a=rtpmap:101 telephone-event/8000\r\n"
//		"a=fmtp:101 0-11\r\n"
//		"m=video 9078 RTP/AVP 103 99 97 98\r\n"
//		"a=rtpmap:103 VP8/90000\r\n"
//		"a=rtpmap:99 MP4V-ES/90000\r\n"
//		"a=fmtp:99 profile-level-id=3\r\n"
//		"a=rtpmap:97 theora/90000\r\n"
//		"a=rtpmap:98 H263-1998/90000\r\n"
//		"a=fmtp:98 CIF=1;QCIF=1\r\n"
//		"a=recvonly\r\n"
//		"\r\n";

	ret = sipua_call_invite(call_url, "application/sdp", sdp);
	if (ret != 0) {
		printf("sipua_call_invite() failed\n");
		exit(1);
	}

	for (;;)
		sleep(5);

	return 0;
}
