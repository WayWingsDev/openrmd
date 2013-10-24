#include "syshdr.h"
#include "rmd_sdk.h"
#include "rtspcli.h"
#include "udpsock.h"
#include "proc_runtime.h"

#define VERSION		"2.0.4"

int rmd_sdk_version(char *ver_buff, const int buff_size)
{
	snprintf(ver_buff, buff_size, "version: "VERSION" build: %s %s",
			__DATE__, __TIME__);
	return 0;
}

int rmd_sdk_init(void)
{
	signal(SIGPIPE, SIG_IGN);

	if (proc_runtime_init() != 0)
		return -1;
	return 0;
}

int rmd_sdk_cleanup(void)
{
	return 0;
}

unsigned long rmd_realplay_start(char *url, int trans_method,
		rmd_hdr_callback_t hdr_cbk, void *param_hdr,
		rmd_data_callback_t data_cbk, void *param_data,
		int pure_tcp_data)
{
	return rtspcli_play(url, trans_method == 1 ? 
			RTSP_TRANS_TCP : RTSP_TRANS_AVP,
			hdr_cbk, param_hdr, data_cbk, param_data, 
			pure_tcp_data, proc_runtime_get);
}

int rmd_realplay_stop(unsigned long handle)
{
	return rtspcli_stop(handle);
}

////////////////////////////////////
// PTZ

/* the handle of ptz control */
typedef struct {
	int  sock;
	struct sockaddr_in addr;

	char plat[32];
	int  dev_type;
	int  dev_id;
	int  channel_id;
} ptz_handle_t;

unsigned long rmd_ptz_start(char *svr_ip, int svr_port, 
		char *plat, int dev_type, int dev_id, int channel_id)
{
	ptz_handle_t *handle;
	
	handle = malloc(sizeof(ptz_handle_t));
	if (handle == NULL)
		return -1;

	handle->sock = udpsock(svr_ip, svr_port, &handle->addr, -1);
	if (handle->sock == -1) {
		free(handle);
		return -1;
	}

	snprintf(handle->plat, sizeof(handle->plat), plat);
	handle->dev_type = dev_type;
	handle->dev_id = dev_id;
	handle->channel_id = channel_id;

	return (unsigned long)handle;
}

int rmd_ptz_send(unsigned long handle, int command, 
		int param1, int param2, int param3)
{
	if (handle == -1 || handle == 0)
		return -1;

	ptz_handle_t *p = (ptz_handle_t *)handle;
	char buff[256];

	snprintf(buff, sizeof(buff), "<EventType=\"Control_Camera\">\r\n"
			"<Item Code=\"%s-%d-%d-%d\""
			" Command=\"0x%04x\""
			" CommandPara1=\"%d\""
			" CommandPara2=\"%d\""
			" CommandPara3=\"%d\">", 
			p->plat, p->dev_type, p->dev_id, p->channel_id,
			command, param1, param2, param3);
	int ret = sendto(p->sock, buff, strlen(buff), 0, 
			(const struct sockaddr *)&p->addr,
			(socklen_t)sizeof(struct sockaddr_in));
	return ret == -1 ? -1 : 0;
}

int rmd_ptz_stop(unsigned long handle)
{
	if (handle == -1 || handle == 0)
		return -1;

	ptz_handle_t *p = (ptz_handle_t *)handle;
	close(p->sock);
	free(p);

	return 0;
}
