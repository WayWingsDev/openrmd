#ifndef _RMD_H
#define _RMD_H

#include "syshdr.h"

#define RMDVER		"2.0.12"	/* rmd server version */
#define CFGFILE		"rmd.conf"	/* config file name */

/* global variants */
char cfg_file[PATH_MAX];		/* config file */
char local_ip[32];			/* local IP address */

/* get program's runed time */
time_t get_runtime();

#endif	/* _RMD_H */
