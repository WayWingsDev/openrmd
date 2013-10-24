#ifndef _FREADS_H_
#define _FREADS_H_

/**
 * @brief read one line from a file descriptor.
 * 
 * @param fd file descriptor.
 * @param *buff read buffer.
 * @param size the read buffer's size.
 * @param bytes NOTE: when out, the length not contain the line end flag.
 * 
 * @return If success, return a buffer. If the return buffer's address not 
 * equal the parameter 'buff', you should free it. Return NULL if error.
 */
char *freads(int fd, char *buff, int size, int *bytes);

#endif	/* _FREADS_H_ */
