#ifndef _RMD_REC_H_
#define _RMD_REC_H_

#include "rmd_driver_interface.h"

/* record callback function typedef */
typedef int (*record_callback_t)(char *buff, int bytes, void *param);

typedef struct {
	int type;		/* storage device type */
	rmd_di_rec_get_info_t	  rmd_di_rec_get_info;
	rmd_di_rec_init_t  	  rmd_di_rec_init;
	rmd_di_rec_geterror_t	  rmd_di_rec_geterror;
	rmd_di_rec_login_t	  rmd_di_rec_login;
	rmd_di_rec_logout_t	  rmd_di_rec_logout;
	rmd_di_rec_start_record_t rmd_di_rec_start_record;
	rmd_di_rec_record_t	  rmd_di_rec_record;
	rmd_di_rec_stop_record_t  rmd_di_rec_stop_record;

	record_callback_t	  record_callback;
} rec_driver_t;

int rmd_rec_start();
int rmd_rec_stop();

#endif	/* _RMD_REC_H_ */
