#ifndef _LIB_SPECIAL_H_
#define _LIB_SPECIAL_H_

#define DEV_TYPE	TYPE_AERO
#define DEV_NAME	"AERO"
#define DEV_VER		2.01
#define HDR_LEN_MAX	0

#define CMDBUFF_LEN	25	/* command buffer length */
#define VAL		*(unsigned short *)&buff
#define LEN_POS		4

int send_cmd(int login_id, char *buff, int cmd_len);
int recv_cmd(int login_id, char *buff);
int login(char *ip, int port, char *user, char *pwd);
int logout(int login_id);

#endif	/* _LIB_SPECIAL_H_ */
