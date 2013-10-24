#include "syshdr.h"
#include "code_conv.h"
#include <iconv.h>

#define ENC_GB2312	"gb2312"
#define ENC_UTF8	"utf-8"

static int code_conv(char *fromcode, char *tocode, char *inbuf, size_t inlen,
		char *outbuf, size_t outlen)
{
	iconv_t cd;

	cd = iconv_open(tocode, fromcode);
	if (cd == (iconv_t)-1)
		return -1;

	if (iconv(cd, &inbuf, &inlen, &outbuf, &outlen) == -1) {
		printf("%s (%d)\n", strerror(errno), errno);
		iconv_close(cd);
		return -1;
	}

	iconv_close(cd);
	return 0;
}

char *code_conv_g2u(char *inbuf)
{
	size_t inlen;
	size_t outlen;
	char *outbuf;
	int ret;

	inlen = strlen(inbuf);
	if (inlen == 0)
		return NULL;

	outlen = inlen * 2 - 1;
	outbuf = calloc(1, outlen);
	if (outbuf == NULL)
		return NULL;

	ret = code_conv(ENC_GB2312, ENC_UTF8, inbuf, inlen, outbuf, outlen);
	if (ret == -1) {
		free(outbuf);
		return NULL;
	}

	return outbuf;
}

char *code_conv_u2g(char *inbuf)
{
	size_t inlen;
	size_t outlen;
	char *outbuf;
	int ret;

	inlen = strlen(inbuf);
	if (inlen == 0)
		return NULL;

	outlen = inlen * 2 + 1;
	outbuf = calloc(1, outlen);
	if (outbuf == NULL)
		return NULL;

	ret = code_conv(ENC_UTF8, ENC_GB2312, inbuf, inlen, outbuf, outlen);
	if (ret == -1) {
		free(outbuf);
		return NULL;
	}

	return outbuf;
}
