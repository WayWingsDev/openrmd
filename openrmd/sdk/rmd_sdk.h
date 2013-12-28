#ifndef _RMD_SDK_H_
#define _RMD_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32_)
#define RMD_DLLPORT __declspec(dllexport)
#else
#define RMD_DLLPORT
#endif

/* callback function typedef */
typedef void (*rmd_hdr_callback_t)(unsigned long handle, 
		char *sdp, int sdp_bytes, 
		char *sps_encode, int sps_encode_bytes, 
		char *sps_decoded, int sps_decoded_bytes,
		void *param);
typedef void (*rmd_data_callback_t)(unsigned long handle, 
		char *buff, int bytes, void *param);

/**
 * @brief get sdk version
 * 
 * @param *ver_buff the buffer where hold version info (should more than 64 
 * bytes)
 * @param buff_size the ver_buff's actual size
 * 
 * @return return 0 if success or -1 if failed
 */
int rmd_sdk_version(char *ver_buff, const int buff_size);

/**
 * @brief initialize rmd SDK.
 * 
 * @return return 0 if success or -1 if failed
 */
RMD_DLLPORT int rmd_sdk_init(void);

/**
 * @brief cleanup rmd SDK.
 * 
 * @return return 0 if success or -1 if failed
 */
RMD_DLLPORT int rmd_sdk_cleanup(void);

/**
 * @brief start to get the device's real data
 * 
 * @param *url RTSP url
 * @param trans_method trans method (1:TCP 2:RTP)
 * @param hdr_cbk media header callback function
 * @param *param_hdr user parameter for media header callback function
 * @param data_cbk real data callback function
 * @param *param_data user parameter for real data callback function
 * @param pure_tcp_data (1: pure tcp data over RTSP 0: RTP over TCP)
 * 
 * @return return the handle if success or -1 if failed
 */
RMD_DLLPORT unsigned long rmd_realplay_start(char *url, int trans_method,
		rmd_hdr_callback_t hdr_cbk, void *param_hdr,
		rmd_data_callback_t data_cbk, void *param_data,
		int pure_tcp_data);

/**
 * @brief stop to get the device's real data
 * 
 * @param handle return by rmd_realplay_start()
 * 
 * @return return 0 if success or -1 if failed
 */
RMD_DLLPORT int rmd_realplay_stop(unsigned long handle);

/**
 * @brief prepare for control a device's ptz
 * 
 * @param *svr_ip the server which receive the command
 * @param svr_port the server's listen port
 * @param *plat the device's platform code
 * @param dev_type the device's type
 * @param dev_id the device's ID
 * @param channel_id the channel's ID on this device
 * 
 * @return return the handle if success or -1 if failed
 */
RMD_DLLPORT unsigned long rmd_ptz_start(char *svr_ip, int svr_port, 
		char *plat, int dev_type, int dev_id, int channel_id);

/**
 * @brief send a ptz command
 * 
 * @param handle return by rmd_ptz_start()
 * @param command ptz command code
 * @param param1 command parameter 1
 * @param param2 command parameter 2
 * @param param3 command parameter 3 (optional, set to 0)
 * 
 * @return return 0 if success or -1 if failed
 */
RMD_DLLPORT int rmd_ptz_send(unsigned long handle, int command, 
		int param1, int param2, int param3);

/**
 * @brief stop for control a device's ptz
 * 
 * @param handle return by rmd_ptz_start()
 * 
 * @return return 0 if success or -1 if failed
 */
RMD_DLLPORT int rmd_ptz_stop(unsigned long handle);

#ifdef __cplusplus
}
#endif

#endif	/* _RMD_SDK_H_ */
