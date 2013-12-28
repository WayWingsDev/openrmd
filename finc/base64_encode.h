#ifndef _BASE64_ENCODE_H_
#define _BASE64_ENCODE_H_

#include <stdint.h>

/* Base64 encoding */
char *base64_encode(const uint8_t *src, size_t size);

#endif	/* _BASE64_ENCODE_H_ */
