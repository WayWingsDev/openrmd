#ifndef _RTSPCLI_H_
#define _RTSPCLI_H_

#include "rtsp.h"
#include <time.h>

/* rtsp client callback function typedef */
typedef void (*rtspcli_sdp_callback_t)(unsigned long sess, 
		char *sdp, int sdp_bytes, 
		char *sps_encode, int sps_encode_bytes, 
		char *sps_decoded, int sps_decoded_bytes,
		void *param);
typedef void (*rtspcli_data_callback_t)(unsigned long sess, 
		char *buff, int bytes, void *param);

typedef time_t (*rtspcli_get_runtime_t)(void);

/* start a rtsp client session */
unsigned long rtspcli_play(char *url, char *trans, 
		rtspcli_sdp_callback_t sdp_cbk, void *sdp_param,
		rtspcli_data_callback_t data_cbk, void *data_param,
		int pure_tcp_data, rtspcli_get_runtime_t get_runtime_func);

/* stop a rtsp client session */
int rtspcli_stop(unsigned long sess);

/* send SET_PARAMETER to server */
int rtspcli_set_parameter(unsigned long sess, char *content, 
		int content_length);

#endif	/* _RTSPCLI_H_ */
