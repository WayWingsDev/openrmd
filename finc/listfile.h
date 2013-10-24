#ifndef _LISTFILE_H_
#define _LISTFILE_H_

typedef int (*listfile_callback_t)(char *filename, void *param);

void listfile(char *path, char *suffix, listfile_callback_t fn, void *param);

#endif	/* _LISTFILE_H_ */
