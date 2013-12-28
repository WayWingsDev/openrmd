#ifndef _RMD_DATA_CALLBACK_H_
#define _RMD_DATA_CALLBACK_H_

/* media header data callback */
void rmd_data_callback_hdr(char *buff, int bytes, void *param);

/* real data callback */
void rmd_data_callback_real(unsigned long handle, char *buff, 
		int bytes, void *param);

/* error callback when realplay */
void realplay_state_callback(int state, void *param);

#endif	/* _RMD_DATA_CALLBACK_H_ */
