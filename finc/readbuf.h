#ifndef _READBUF_H_
#define _READBUF_H_

/* buffer info */
typedef struct buf_t buf_t;

buf_t *openbuf(const char *buf, const int buf_size);
char *readbuf(buf_t *pb, const char *delim);
int closebuf(buf_t *pb);

#endif	/* _READBUF_H_ */
