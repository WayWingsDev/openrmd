#ifndef _RMD_DEVMGR_H_
#define _RMD_DEVMGR_H_

#include "dlist.h"
#include "rmd_driver_interface.h"

#define PLAT_SIZE	32		/* platform code length */

/* channel info */
typedef struct {
	pthread_mutex_t mtx;
	int	id;			/* channel ID */
	int	ref;			/* reference count */

	/* for realplay */
	unsigned long realplay_handle;	/* handle of realplay */
	char	*hdr_buff;		/* media header buffer */
	int	hdr_length;		/* actual media header length */

	dlist_t	*tcp_clients;		/* the tcp client list */
	dlist_t	*rtp_clients;		/* the rtp client list */

	int	is_rtp_packet;		/* 0: not rtp packet 1: rtp packet */
	int	payload_type;
	int	camera_state;		/* To avoid the delay when client 
					   apply a bad camera. 
					   0 - have problem, 1 - no problem */

#ifdef RMD_HAS_REC
	int	rec;			/* 0: not record 1: record */
	int	storage_type;		/* storge device type */
	void	*rec_driver;		/* record driver */
	void	*pdriver;		/* channel's driver */
	void	*pdevice;		/* channel's device */
	char	rec_name[64];		/* record name */
	int	rec_state;
	int	rec_loginid;
	unsigned long rec_handle;
	time_t	bgn_time, end_time;
	char	storage_ip[32];
	int	storage_port;
	char	storage_user[20];
	char	storage_pwd[20];
	int	storage_disk;
	int	rec_error;
	time_t	last_data_time;
#endif

#ifdef RMD_HAS_PTZ
	int	baud_rate;
	int	ptz_loginid;
	int	cam_loginid;
#endif
} channel_t;

/* device info */
typedef struct {
	int	id;			/* device ID */
	char	ip[32];			/* IP address */
	int	port;			/* port */
	char	user[20];		/* user name for login */
	char	pwd[20];		/* passwod for login */

	dlist_t	*channels;		/* the channel's list */
} device_t;

/* driver info */
typedef struct {
	int type;			/* device type */
	int hdr_len_max;		/* media header's max length */
	dlist_t *devices;		/* actual device */

	/* driver interfac function pointer */
	rmd_di_init_t		rmd_di_init;
	rmd_di_uninit_t		rmd_di_uninit;
	rmd_di_get_info_t	rmd_di_get_info;
	rmd_di_get_describe_t	rmd_di_get_describe;
	rmd_di_start_realplay_t	rmd_di_start_realplay;
	rmd_di_stop_realplay_t	rmd_di_stop_realplay;
	rmd_di_make_key_frame_t	rmd_di_make_key_frame;
#ifdef RMD_HAS_PTZ
	rmd_di_ctl_ptz_t	rmd_di_ctl_ptz;
	rmd_di_ctl_cam_t	rmd_di_ctl_cam;
#endif
} driver_t;

/* initialize device table */
int rmd_devmgr_init();

int rmd_devmgr_lookup_channel(int driver_type, int device_id, int channel_id,
		driver_t **driver, device_t **device, channel_t **channel);

int rmd_devmgr_lookup_channel_dynamic(int driver_type, int device_id, 
		int channel_id, driver_t **driver, device_t **device, 
		channel_t **channel, device_t *dev);

driver_t *rmd_devmgr_get_driver(int type);

int rmd_devmgr_remove_channel(driver_t *driver, device_t *device, 
		channel_t *channel);
int rmd_devmgr_free_channel(channel_t *p);

typedef int (*travel_callback_t)(void* data, void *param);
int rmd_devmgr_travel_channel(travel_callback_t cb, void *param);

#endif	/* _RMD_DEVMGR_H_ */
