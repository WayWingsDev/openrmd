#ifndef _RMD_RTSPSVR_H_
#define _RMD_RTSPSVR_H_

/* start rtsp server */
int rmd_rtspsvr_start();

/* stop rtsp server */
int rmd_rtspsvr_stop();

/* trigger epoll server read zero on this socket */
void rmd_rtspsvr_trigger_hangup(int sock);

#endif	/* _RMD_RTSPSVR_H_ */
