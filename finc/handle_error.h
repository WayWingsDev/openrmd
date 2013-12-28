#ifndef _HANDLE_ERROR_H_
#define _HANDLE_ERROR_H_

#include <stdio.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#endif	/* _HANDLE_ERROR_H_ */
