#ifndef _READ_FLAG_H_
#define _READ_FLAG_H_

/* max_bytes == 0, unlimited. */
int read_flag(int fd, const void *flag, const int flag_size, 
		const int max_bytes);

#endif	/* _READ_FLAG_H_ */
