#include <stdlib.h>
#include <string.h>
#include "base64_encode.h"

char *base64_encode(const uint8_t *src, size_t size)
{
    static const char b64[] =
           "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *ret = malloc((size + 4) * 4 / 3);
    char *dst = ret;

    if (dst == NULL)
        return NULL;

    while (size > 0) {
        /* pops (up to) 3 bytes of input, push 4 bytes */
        uint32_t v;

        /* 1/3 -> 1/4 */
        v = *src++ << 24;
        *dst++ = b64[v >> 26];
        v = v << 6;

        /* 2/3 -> 2/4 */
        if (size >= 2)
            v |= *src++ << 22;
        *dst++ = b64[v >> 26];
        v = v << 6;

        /* 3/3 -> 3/4 */
        if (size >= 3)
            v |= *src++ << 20;		/* 3/3 */
        *dst++ = (size >= 2) ? b64[v >> 26] : '=';	/* 3/4 */
        v = v << 6;

        /* -> 4/4 */
        *dst++ = (size >= 3) ? b64[v >> 26] : '='; /* 4/4 */

        if (size <= 3)
            break;
        size -= 3;
    }

    *dst = '\0';
    return ret;		/* NOTE: you should free it after use it. */
}
