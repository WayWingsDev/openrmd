#ifndef _AERONETSDK_H_
#define _AERONETSDK_H_

#define HDR_SIZE	8		/* flag + data len */

typedef void (*aero_net_realdata_callback_t)(unsigned long realplay_handle, 
		char *buff, int bytes, void *param);

/* when the device's state changed, this callback function will be call.
 * state: 0-bad 1-ok. */
typedef void (*aero_net_state_callback_t)(int state, void *param);

typedef void (*aero_net_pure_data_callback_t)(char *buff, int bytes, 
		void *param);

int aero_net_init();

int aero_net_cleanup();

long aero_net_get_lasterror();

unsigned long aero_net_login(char *ip, int port, char *user, char *pwd);

int aero_net_logout(unsigned long login_handle);

/* channel_id: 1-main 2-sub */
unsigned long aero_net_realplay(unsigned long login_handle, int channel_id,
		aero_net_realdata_callback_t data_cbk, void *data_param,
		aero_net_state_callback_t state_cbk, void *state_param);

void aero_net_extract_pure_data(unsigned long realplay_handle, 
		unsigned char *buff, int bytes, 
		aero_net_pure_data_callback_t cbk, void *param);

int aero_net_stop_realplay(unsigned long realplay_handle);

#endif	/* _AERONETSDK_H_ */
