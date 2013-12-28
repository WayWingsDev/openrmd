#ifndef _SYS_CLIPBOARD_H_
#define _SYS_CLIPBOARD_H_

/* the method that copy the content into sys-clipboard. */
typedef enum {
	SYS_CB_COPY_TRUNC,
	SYS_CB_COPY_APPEND_LINE,
	SYS_CB_COPY_APPEND_CONTENT
} sys_clipboard_copy_method_t;

/**
 * @brief Put content into sys-clipboard(shared memory).
 * 
 * @param *s The content's address.
 * @param size The content's size.
 * @param method The method that copy the content into sys-clipboard.
 * 
 * @return zero if success or -1 if failed.
 */
int sys_clipboard_copy(void *s, int size, sys_clipboard_copy_method_t method);

/**
 * @brief Dump content from sys-clipboard.
 * 
 * @param **s The content's address.
 * @param *size The content's bytes.
 * 
 * @return zero if success or -1 if failed.
 */
int sys_clipboard_paste(char **s, int *size);

#endif	/* _SYS_CLIPBOARD_H_ */
