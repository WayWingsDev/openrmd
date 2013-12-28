/* md5.c - RSA Data Security, Inc., MD5 message-digest algorithm

   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All 
   rights reserved.

   License to copy and use this software is granted provided that it 
   is identified as the "RSA Data Security, Inc. MD5 Message-Digest 
   Algorithm" in all material mentioning or referencing this software 
   or this function.

   License is also granted to make and use derivative works provided 
   that such works are identified as "derived from the RSA Data
   Security, Inc. MD5 Message-Digest Algorithm" in all material
   mentioning or referencing the derived work.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

/* MD5 context */
typedef struct {  
	unsigned int state[4];		/* state (ABCD) */
	unsigned int count[2];		/* number of bits, modulo 2^64 */
	unsigned char buff[64];		/* input buffer */
} md5_ctx;

/* constants for md5_transform routine */
#define S11	7
#define S12	12
#define S13	17
#define S14 	22
#define S21 	5
#define S22 	9
#define S23 	14
#define S24 	20
#define S31 	4
#define S32 	11
#define S33 	16
#define S34 	23
#define S41 	6
#define S42 	10
#define S43 	15
#define S44 	21

/* F, G, H and I are basic MD5 functions */
#define F(x, y, z)	(((x) & (y)) | ((~x) & (z)))
#define G(x, y, z)	(((x) & (z)) | ((y) & (~z)))
#define H(x, y, z)	((x) ^ (y) ^ (z))
#define I(x, y, z)	((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n)	(((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4. 
   Rotation is separate from addition to prevent recomputation. */
#define FF(a, b, c, d, x, s, ac) { \
	(a) += F((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
	(a) += G((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
	(a) += H((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT((a), (s)); \
	(a) += (b); \
}

#define II(a, b, c, d, x, s, ac) { \
	(a) += I((b), (c), (d)) + (x) + (unsigned int)(ac); \
	(a) = ROTATE_LEFT((a), (s)); \
	(a) += (b); \
}  

static unsigned char padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* Encodes input into output. Assumes len is a multiple of 4. */  
static void encode(unsigned char *out, unsigned int *in, unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) {
		out[j] = (unsigned char)(in[i] & 0xff);
		out[j+1] = (unsigned char)((in[i] >> 8) & 0xff);
		out[j+2] = (unsigned char)((in[i] >> 16) & 0xff);
		out[j+3] = (unsigned char)((in[i] >> 24) & 0xff);
	}
}

/* Decodes input into output. Assumes len is a multiple of 4. */
static void decode(unsigned int *out, unsigned char *in, unsigned int len)  
{  
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		out[i] = ((unsigned int)in[j]) | 
			(((unsigned int)in[j+1]) << 8) |  
			(((unsigned int)in[j+2]) << 16) |
			(((unsigned int)in[j+3]) << 24);
}  

/* MD5 basic transformation. Transforms state based on block. */
static void md5_transform(unsigned int state[4], unsigned char block[64])
{
	unsigned int a = state[0];
	unsigned int b = state[1];
	unsigned int c = state[2];
	unsigned int d = state[3];
	unsigned int x[16];

	decode(x, block, 64);

	/* round 1 */
	FF(a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
	FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
	FF(c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
	FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
	FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
	FF(d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
	FF(c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
	FF(b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
	FF(a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
	FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
	FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

	/* round 2 */
	GG(a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
	GG(d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
	GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG(a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
	GG(d, a, b, c, x[10], S22,  0x2441453); /* 22 */
	GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
	GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
	GG(b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
	GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
	GG(c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
	GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

	/* round 3 */
	HH(a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
	HH(d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
	HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH(a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
	HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
	HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
	HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
	HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
	HH(b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
	HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
	HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

	/* round 4 */
	II(a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
	II(d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
	II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II(b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
	II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
	II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II(b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
	II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
	II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II(c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
	II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II(a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
	II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	II(b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	/* zeroize sensitive information */
	memset(x, 0, sizeof(x));
}  

/* MD5 initialization. Begins an MD5 operation, writing a new context. */
static void md5_init(md5_ctx *ctx)
{
	ctx->count[0] = ctx->count[1] = 0;
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest operation, 
 * processing another message block, and updating the context. */
static void md5_update(md5_ctx *ctx, unsigned char *input, unsigned int len)
{  
	unsigned int i;
	unsigned int index;
	unsigned int part_len;

	/* compute number of bytes mod 64 */
	index = (unsigned int)((ctx->count[0] >> 3) & 0x3F);

	/* update number of bits */
	if ((ctx->count[0] += (len << 3)) < (len << 3))
		ctx->count[1]++;
	ctx->count[1] += (len >> 29);
	part_len = 64 - index;

	/* transform as many times as possible */
	if (len >= part_len) {
		memcpy(&ctx->buff[index], input, part_len);
		md5_transform(ctx->state, ctx->buff);

		for (i = part_len; i + 63 < len; i += 64)
			md5_transform(ctx->state, &input[i]);
		index = 0;
	} else {
		i = 0;
	}

	/* buffer remaining input */
	memcpy(&ctx->buff[index], &input[i], len - i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the 
 * message digest and zeroizing the ctx. */
static void md5_final(md5_ctx *ctx, unsigned char digest[16])
{  
	unsigned char bits[8];
	unsigned int index;
	unsigned int pad_len;

	/* save number of bits */
	encode(bits, ctx->count, 8);

	/* pad out to 56 mod 64 */
	index = (unsigned int)((ctx->count[0] >> 3) & 0x3f);
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(ctx, padding, pad_len);

	/* append length (before padding) */
	md5_update(ctx, bits, 8);

	/* store state in digest */
	encode(digest, ctx->state, 16);

	/* zeroize sensitive information */
	memset(ctx, 0, sizeof(md5_ctx));
}  

void md5_string(char *in, char out[33])
{
	md5_ctx ctx;
	unsigned char digest[16];
	unsigned int len;
	int i;
	
	len = (unsigned int)strlen(in);
	md5_init(&ctx);
	md5_update(&ctx, (unsigned char *)in, len);
	md5_final(&ctx, digest);

	for (i = 0; i < 16; i++)
		sprintf(&out[i * 2], "%02x", digest[i]);
}  

int md5_file(char *filename, char out[33])
{
	FILE *file;
	md5_ctx ctx;
	unsigned char digest[16];
	int len;
	unsigned char buff[1024];
	int i;

	file = fopen(filename, "rb");
	if (file == NULL)
		return -1;

	md5_init(&ctx);
	while ((len = fread(buff, 1, sizeof(buff), file)) > 0)
		md5_update(&ctx, buff, len);
	md5_final(&ctx, digest);
	fclose(file);

	if (len < 0)
		return -1;

	for (i = 0; i < 16; i++)
		sprintf(&out[i * 2], "%02x", digest[i]);

	return 0;
}
