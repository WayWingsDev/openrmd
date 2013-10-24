#ifndef _LOOKUP_SO_H_
#define _LOOKUP_SO_H_

/**
 * @brief lookup .so file's names.
 * 
 * @param *path absolute path of the directory
 * @param *prefix_name prefix name
 * 
 * @return return a string("rmd_so1.so\nrmd_so2.so\n") if success or NULL if
 * failed. Note, you need to free the return pointer if it's not NULL.
 */
char *lookup_so(char *path, char *prefix_name);

#endif	/* _LOOKUP_SO_H_ */
