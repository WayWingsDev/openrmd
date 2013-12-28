#include "lib_special.h"
#include "lib_frame_realplay.h"
#include "set_recv_timeout.h"

#define NOACT	10001
#define PARA1	10002
#define PARA2	10003
#define PARA3	10004

#define RECVCMD_TIMEOUT	4
#define P1	10	/* param1 */
#define P1P2	12	/* param1 && param2 */

typedef struct {
	int baud_rate;
	int index;
} baud_rate_t;

static baud_rate_t baud_rate_table[] = {
	{2400,   1},
	{4800,   2},
	{9600,   3},
	{19200,  4},
	{38400,  5},
	{115200, 6}
};

typedef struct {
	int ori_cmd;
	int dst_cmd, dst_param[3];
} proto_table_t;

static proto_table_t proto_table[] = {
	{IRIS_CLOSE_STOP, 	NOACT, 	{0, 0, 0}},
	{IRIS_CLOSE_START, 	4, 	{2, PARA1, 0}},
	{IRIS_OPEN_START, 	4, 	{2, PARA1, 0}},
	{IRIS_OPEN_STOP, 	NOACT, 	{0, 0, 0}},
	{FOCUS_NEAR_STOP, 	NOACT, 	{0, 0, 0}},
	{FOCUS_NEAR_START, 	2, 	{3, 2, 0}},
	{FOCUS_FAR_STOP, 	NOACT, 	{0, 0, 0}},
	{FOCUS_FAR_START, 	2, 	{2, 2, 0}},
	{ZOOM_OUT_STOP, 	1, 	{3, 0, 0}},
	{ZOOM_OUT_START, 	1, 	{2, 0, 0}},
	{ZOOM_IN_STOP, 		1, 	{3, 0, 0}},
	{ZOOM_IN_START, 	1, 	{1, 0, 0}},
	{TILT_UP_STOP, 		2, 	{0, 0, 0}},	/* turn stop */
	{TILT_UP_START, 	1, 	{1, 0, 0}},	/* up */
	{TILT_DOWN_STOP, 	2, 	{2, 0, 0}},
	{TILT_DOWN_START, 	1, 	{2, 0, 0}},	/* down */
	{PAN_RIGHT_STOP,	2, 	{0, 0, 0}},
	{PAN_RIGHT_START, 	1, 	{4, 0, 0}},	/* right */
	{PAN_LEFT_STOP, 	2, 	{0, 0, 0}},
	{PAN_LEFT_START, 	1, 	{3, 0, 0}},	/* left */
	{SET_PRESET_STOP, 	3, 	{PARA1, 0, 0}},	/* save preset */
	{GOTO_PRESET_STOP, 	5, 	{PARA1, 0, 0}},	/* goto preset */
	{CLE_PRESET_STOP, 	4, 	{PARA1, 0, 0}},	/* delete preset */
	{UP_LEFT_STOP, 		2, 	{0, 0, 0}},
	{UP_LEFT_START, 	1, 	{5, 0, 0}},	/* left-up */
	{DOWN_LEFT_STOP, 	2, 	{0, 0, 0}},
	{DOWN_LEFT_START, 	1, 	{6, 0, 0}},	/* left-down */
	{UP_RIGHT_STOP, 	2, 	{0, 0, 0}},
	{UP_RIGHT_START, 	1, 	{7, 0, 0}},	/* right-up */
	{DOWN_RIGHT_STOP, 	2, 	{0, 0, 0}},
	{DOWN_RIGHT_START, 	1, 	{8, 0, 0}},	/* right-down */
	{CURR_ACTION_STOP, 	2, 	{0, 0, 0}},

	/*
	{WIPER_START, 		0, 	{0, 0, 0}},
	{WIPER_STOP, 		0, 	{0, 0, 0}},
	{LIGHT_START, 		0, 	{0, 0, 0}},
	{LIGHT_STOP, 		0, 	{0, 0, 0}},
	{HEATER_START, 		0, 	{0, 0, 0}},
	{HEATER_STOP, 		0, 	{0, 0, 0}},
	{INFRARED_START, 	0, 	{0, 0, 0}},
	{INFRARED_STOP, 	0, 	{0, 0, 0}},
	*/
	{LINEAR_SCAN_START, 	1, 	{9, 0, 0}},	/* auto scan */
	{LINEAR_SCAN_STOP, 	2, 	{0, 0, 0}},
	/*
	{CRUISE_START, 		0, 	{0, 0, 0}},
	{CRUISE_STOP, 		0,	{0, 0, 0}},
	{SEQ_START, 		0, 	{0, 0, 0}},
	{SEQ_STOP, 		0, 	{0, 0, 0}},
	{PTZ_LOCK, 		0, 	{0, 0, 0}},
	{PTZ_UNLOCK, 		0, 	{0, 0, 0}}
	*/
};

static int baud_rate_trans(const int baud_rate)
{
	int i;
	for (i = 0; i < sizeof(baud_rate_table) / sizeof(baud_rate_t); i++) {
		if (baud_rate_table[i].baud_rate == baud_rate)
			return baud_rate_table[i].index;
	}
	return 3;	/* default: 9600 */
}

static inline int protocol_trans(int *ctl_code, int *param1, int *param2, 
		int *param3)
{
	int i, j;
	int p1 = *param1, p2 = *param2, p3 = *param3;
	int p;
	int out[3];

	for (i = 0; i < sizeof(proto_table) / sizeof(proto_table_t); i++) {
		if (proto_table[i].ori_cmd != *ctl_code)
			continue;
		
		if (proto_table[i].dst_cmd == NOACT)
			return NOACT;

		*ctl_code = proto_table[i].dst_cmd;
		for (j = 0; j < 3; j++) {
			p = proto_table[i].dst_param[j];
			if (p == PARA1) {
				out[j] = p1;
			} else if (p == PARA2) {
				out[j] = p2;
			} else if (p == PARA3) {
				out[j] = p3;
			} else {
				out[j] = p;
			}
		}
		*param1 = out[0];
		*param2 = out[1];
		*param3 = out[2];

		printf("--> %d %d %d %d\n", 
				*ctl_code, *param1, *param2, *param3);
		return 0;
	}

	return -1;
}

static int ptz_init(int login_id, int baud_rate)
{
	char buff[CMDBUFF_LEN] = {0x20, 0xF0};

	VAL[2]  = 4;
	VAL[LEN_POS] = 8;
	VAL[6]  = 1;
	if (send_cmd(login_id, buff, VAL[LEN_POS]) != 0)
		return -1;
	if (recv_cmd(login_id, buff) != 0)
		return -1;

	VAL[2]  = 1;
	VAL[LEN_POS] = 22;
	VAL[6]  = 1;		/* RS232 */
	VAL[8]  = baud_rate_trans(baud_rate);
	VAL[10] = 4;		/* 8 */
	VAL[12] = 3;
	VAL[14] = 1;
	VAL[16] = 3;
	VAL[18] = 1;
	VAL[20] = 1;

	if (send_cmd(login_id, buff, VAL[LEN_POS]) != 0)
		return -1;
	if (recv_cmd(login_id, buff) != 0)
		return -1;
	return 0;
}

int special_ctl_ptz(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	int ret;

	ret = protocol_trans(&info->ctl_code, &info->param1, &info->param2, 
			&info->param3);
	if (ret == NOACT)
		return 0;
	else if (ret == -1)
		return -1;

	/* if not login yet, login it and initialize ptz first */
	if (*login_id == -1) {
		*login_id = login(info->ip, info->port, info->user, info->pwd);
		if (*login_id == -1)
			return -1;
		if (ptz_init(*login_id, info->baud_rate) == -1)
			goto err;
	}
	set_recv_timeout(*login_id, RECVCMD_TIMEOUT);

	char buff[CMDBUFF_LEN] = {0x20, 0xF0};
	VAL[2]   = 3;
	VAL[LEN_POS] = 14;
	VAL[6]   = info->ctl_code;
	VAL[8]   = info->param1;
	VAL[10]  = info->param2;
	VAL[12]  = info->param3;

	if (send_cmd(*login_id, buff, VAL[LEN_POS]) != 0)
		goto err;
	if (recv_cmd(*login_id, buff) != 0)
		goto err;
	return 0;

err:
	close(*login_id);
	*login_id = -1;
	return -1;
}

int special_ctl_cam(int *login_id, unsigned long handle, ptz_ctl_info_t *info)
{
	int ret;

	ret = protocol_trans(&info->ctl_code, &info->param1, &info->param2, 
			&info->param3);
	if (ret == NOACT)
		return 0;
	else if (ret == -1)
		return -1;

	/* if not login yet, login it and initialize ptz first */
	if (*login_id == -1) {
		*login_id = login(info->ip, info->port, info->user, info->pwd);
		if (*login_id == -1)
			return -1;
	}
	set_recv_timeout(*login_id, RECVCMD_TIMEOUT);

	char buff[CMDBUFF_LEN] = {0x30, 0xF0};
	VAL[2]   = 1;
	VAL[6]   = info->ctl_code;
	VAL[8]   = info->param1;
	VAL[10]  = info->param2;
	VAL[12]  = info->param3;

	if (info->ctl_code == 1) {		/* zoom */
		if (info->param1 >= 0 && info->param1 <= 3)
			VAL[LEN_POS] = P1;
		else
			VAL[LEN_POS] = P1P2;
	} else if (info->ctl_code == 2) {	/* focus */
		VAL[LEN_POS] = P1P2;
	} else if (info->ctl_code == 3) {
	} else if (info->ctl_code == 4) {	/* aperture */
		VAL[LEN_POS] = P1P2;
	} else {
		/* TODO */
		return -1;
	}

	if (send_cmd(*login_id, buff, VAL[LEN_POS]) != 0)
		goto err;
	if (recv_cmd(*login_id, buff) != 0)
		goto err;
	return 0;

err:
	close(*login_id);
	*login_id = -1;
	return -1;
}
