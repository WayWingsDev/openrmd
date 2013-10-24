#ifndef _SPECIALIPC_H_
#define _SPECIALIPC_H_

#include "lib_frame_realplay.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned long specialipc_start_realplay(realplay_info_t *info);

int specialipc_stop_realplay(unsigned long handle);

#ifdef __cplusplus
}
#endif

#endif	/* _SPECIALIPC_H_ */
