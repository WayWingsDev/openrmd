#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readbuf.h"

struct buf_t {
	char *buf_cur_addr;
	char *p_alloc;
	int p_alloc_size;
};

buf_t *openbuf(const char *buf, const int buf_size)
{
	buf_t *pb;

	if (buf == NULL || buf_size <= 0)
		return NULL;
	
	pb = malloc(sizeof(buf_t));
	if (pb == NULL)
		return NULL;

	pb->buf_cur_addr = (char *)buf;
	pb->p_alloc = NULL;
	pb->p_alloc_size = 0;
	return pb;
}

char *readbuf(buf_t *pb, const char *delim)
{
	if (pb == NULL || delim == NULL)
		return NULL;

	char *p;
	int len;

	p = strstr(pb->buf_cur_addr, delim);
	if (p == NULL)
		return NULL;

	len = p - pb->buf_cur_addr;
	if (len > pb->p_alloc_size || (len == 0 && pb->p_alloc == NULL)) {
		pb->p_alloc = realloc(pb->p_alloc, len + 1);
		if (pb == NULL)
			return NULL;
	}
	memcpy(pb->p_alloc, pb->buf_cur_addr, len);
	pb->p_alloc[len] = '\0';
	pb->buf_cur_addr = p + strlen(delim);

	return pb->p_alloc;
}

int closebuf(buf_t *pb)
{
	if (pb == NULL)
		return -1;

	free(pb->p_alloc);
	pb->p_alloc = NULL;
	pb->p_alloc_size = 0;

	free(pb);
	pb = NULL;

	return 0;
}
