#ifndef _BASE64_DECODE_H_
#define _BASE64_DECODE_H_

#include <stdint.h>
#include <stdlib.h>

/* Base64 decoding */
size_t base64_decode(uint8_t *dst, size_t i_dst, const char *src);

#endif	/* _BASE64_DECODE_H_ */
