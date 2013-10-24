#ifndef _LIB_SPECIAL_H_
#define _LIB_SPECIAL_H_

#define DEV_TYPE	TYPE_ELEC
#define DEV_NAME	"ELEC"
#define DEV_VER		2.01
#define HDR_LEN_MAX	0

#define CMDSYN		0xAA55A55A	/* command's synchronous verify value */
#define CMDBUFF		(1024 * 4)	/* TCP recv and send buffer's size */
#define PLAT_LEN	32		/* platform code length */

/* command defines */
#define CMD_REALPLAY	0x1000		/* realplay */
#define CMD_REPLY	0x2000		/* reply to client */

/* command info */
typedef struct {
	int	syn_flag;		/* synchronous header flag */
	int	cmdid;			/* command ID */
	int     buff_length;		/* buffer length */
	char	buff[CMDBUFF];		/* command buffer */
} cmd_t;

/* command header length */
#define CMDHEAD (sizeof(cmd_t) - CMDBUFF)

/* stream option */
#define STREAM_MAIN	1
#define STREAM_SUB	2

/* realplay data apply info */
typedef struct {
	char	plat[PLAT_LEN];
	int	dev_type;
	int	dev_id;
	int	cnl_id;
	int	stream_opt;
} apply_t;

/* the server's reply code */
#define R_SUCCESS	0x0000
#define R_ERROR		0x0001

#endif	/* _LIB_SPECIAL_H_ */
