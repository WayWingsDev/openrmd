#ifndef _RMD_RTCPSVR_H_
#define _RMD_RTCPSVR_H_

#include "rmd_sessmgr.h"

unsigned long rmd_rtcp_start_session(rmd_session_t *sess);
int rmd_rtcp_stop_session(unsigned long handle);

#endif	/* _RMD_RTCPSVR_H_ */
