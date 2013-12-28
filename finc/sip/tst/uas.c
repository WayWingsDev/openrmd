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

static void on_incoming_call(sipua_acc_id acc_id, sipua_call_id call_id,
		sipua_rx_data *rdata)
{
	printf("----> on_incoming_call: %d\n", call_id);

	sipua_rdata_sdp_info *sdp_info = sipua_rdata_get_sdp_info(rdata);

	if (sdp_info->sdp_err != 0)	/* no valid SDP body */
		return;

	char *sdp = sdp_info->body.ptr;
	printf("[%s]\n", sdp);

	/* send 200 OK or terminated the call */
	sipua_call_answer(call_id, 200, NULL, NULL);
	//sipua_call_hangup(call_id, 400, NULL, NULL);
}

void on_call_state(sipua_call_id call_id, sipua_event *e)
{
	sipua_call_info ci;

	sipua_call_get_info(call_id, &ci);
	switch (ci.state) {
		case PJSIP_INV_STATE_CONFIRMED:    /* After ACK is received */
			printf("call [%d] ACK received\n", call_id);
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
	printf("----> on_pager\n");
}

int main(int argc, char **argv)
{
	int ret;
	char *user, *pwd, *domain;
	int port, reg, log_level;

	if (argc != 7) {
		printf("Usage: %s <user> <pwd> <domain> <port> "
				"<reg (0:not reg 1:reg)> "
				"<log level (0:none 7:all)>\n", argv[0]);
		printf("e.g. : %s user1 user1 192.168.100.100 5060 1 0\n", 
				argv[0]);
		exit(1);
	}
	user = argv[1];
	pwd = argv[2];
	domain = argv[3];
	port = atoi(argv[4]);
	reg = atoi(argv[5]);
	log_level = atoi(argv[6]);

	/* initialize */
	memset(&sipua_cbk, 0, sizeof(sipua_callback));
	sipua_cbk.on_reg_state = on_reg_state;
	sipua_cbk.on_incoming_call = on_incoming_call;
	sipua_cbk.on_call_state = on_call_state;
	sipua_cbk.on_pager = on_pager;

	ret = sipua_init(user, pwd, domain, port, &sipua_cbk, 8, reg, 
			log_level);
	if (ret != 0) {
		printf("sipua_init() failed\n");
		exit(1);
	}
	printf("sipua_init() success\n");

	for (;;)
		sleep(5);
	sipua_cleanup();

	return 0;
}
