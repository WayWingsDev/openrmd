#ifndef _RMD_UDS_H_
#define _RMD_UDS_H_

#define REC_NONE	0
#define REC_SUCC	1
#define REC_FAILED	2

#define RMD_RESTART	"[RMD_RESTART]"
#define RMD_RECSTAT	"[RMD_RECSTAT]"
#define RMD_RECSTAT_REQ	"[RMD_RECSTAT_REQ]"

/* start UNIX domain socket server */
int rmd_uds_start();

int rmd_uds_sendmsg(char *buff, int bytes);

/* stop UNIX domain socket server */
int rmd_uds_stop();

#endif	/* _RMD_UDS_H_ */
