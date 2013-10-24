#ifndef _ELEC_CONV_H_
#define _ELEC_CONV_H_

#include "rmd_sessmgr.h"

int elec_conv_init();
int elec_conv_channel(const char *code, rmd_session_t *sess);
int elec_conv_cleanup();

#endif	/* _ELEC_CONV_H_ */
