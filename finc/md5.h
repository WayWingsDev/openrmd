#ifndef _MD5_H_
#define _MD5_H_

/* digests a string */
void md5_string(char *in, char out[33]);

/* digests a file */
int md5_file(char *filename, char out[33]);

#endif	/* _MD5_H_ */
