#ifndef _LIB_FRAME_REC_H_
#define _LIB_FRAME_REC_H_

#include "syshdr.h"
#include "rmd_driver_interface.h"

#ifdef NONE_BLOCKING
typedef int (*record_callback_t)(unsigned int handle, char *buff, int bytes, 
		unsigned int bgn_time, unsigned int end_time);
typedef int (*stop_record_callback_t)(unsigned long handle);

unsigned long nb_start_record(unsigned long handle, 
		record_callback_t record_cbk,
		stop_record_callback_t stop_record_cbk);
int nb_record(unsigned long record_handle, char *buff, int bytes, 
		unsigned int bgn_time, unsigned int end_time);
int nb_stop_record(unsigned long handle);
#endif	/* NONE_BLOCKING */

#endif	/* _LIB_FRAME_REC_H_ */
