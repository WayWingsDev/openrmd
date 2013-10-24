#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "sys_clipboard.h"

#define SHMNAME		"sys_clipboard_shm"
#define FILE_MODE 	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define BYTES_PLACE	sizeof(uint32_t)
#define LINE_PLACE	sizeof(uint32_t)
#define LINE_LEN_PLACE	sizeof(uint32_t)
#define ADDTION_LEN	(BYTES_PLACE + LINE_PLACE)

/*
 *  shared memory structure:
 *  ------------------------------------------------------------------------
 *  | bytes | last L pos | L1 len | L2 content | ... | Ln len | Ln content |
 *  ------------------------------------------------------------------------
 *                                                   ^last line pos
 *  |--- ADDTION_LEN ----|-------------------- bytes ----------------------|
 */

int sys_clipboard_copy(void *s, int size, sys_clipboard_copy_method_t method)
{
	int fd, shm_len, bytes, last_line_pos, new_bytes;
	struct stat stat;
	void *ptr;

	if (size < 0)
		return -1;

	if (s == NULL && size > 0)
		return -1;

	/* open shared memory */
	if ((fd = shm_open(SHMNAME, O_RDWR | O_CREAT, FILE_MODE)) == -1)
		return -1;

	if (fstat(fd, &stat) == -1)
		goto copy_err;

	/* adjust the shared memory size */
	bytes = 0;
	if ((method == SYS_CB_COPY_APPEND_CONTENT || 
				method == SYS_CB_COPY_APPEND_LINE) && 
			stat.st_size >= BYTES_PLACE) {
		if ((ptr = mmap(NULL, ADDTION_LEN, PROT_READ, MAP_SHARED, 
						fd, 0)) == MAP_FAILED)
			goto copy_err;

		if ((bytes = *((uint32_t *)ptr)) < 0) {
			bytes = 0;
		}
		if ((last_line_pos = *((uint32_t *)(ptr + BYTES_PLACE))) < 0)
			last_line_pos = ADDTION_LEN;
	}
	if (bytes == 0 && method == SYS_CB_COPY_APPEND_CONTENT)
		method = SYS_CB_COPY_TRUNC;

	if (method == SYS_CB_COPY_APPEND_CONTENT)
		shm_len = ADDTION_LEN + bytes + size;
	else
		shm_len = ADDTION_LEN + bytes + LINE_LEN_PLACE + size;

	if (stat.st_size < shm_len) {
		if (ftruncate(fd, shm_len) == -1)
			goto copy_err;
	}

	/* map file into memory */
	if ((ptr = mmap(NULL, shm_len, PROT_READ | PROT_WRITE, MAP_SHARED, 
					fd, 0)) == MAP_FAILED)
		goto copy_err;
	close(fd);

	/* modify the content's size, and copy file content to shared memory */
	if (method == SYS_CB_COPY_TRUNC || method == SYS_CB_COPY_APPEND_LINE) {
		new_bytes = bytes + LINE_LEN_PLACE + size;
		last_line_pos = ADDTION_LEN + bytes;

		memcpy(ptr, (void *)&new_bytes, BYTES_PLACE);
		memcpy(ptr + BYTES_PLACE, (void *)&last_line_pos, LINE_PLACE);
		memcpy(ptr + last_line_pos, (void *)&size, LINE_LEN_PLACE);
		if (size > 0)
			memcpy(ptr + last_line_pos + LINE_LEN_PLACE, s, size);
	} else if (method == SYS_CB_COPY_APPEND_CONTENT) {
		new_bytes = bytes + size;
		int new_size = ADDTION_LEN + new_bytes - last_line_pos - 
			LINE_LEN_PLACE;

		memcpy(ptr, (void *)&new_bytes, BYTES_PLACE);
		memcpy(ptr + last_line_pos, (void *)&new_size, LINE_LEN_PLACE);
		memcpy(ptr + ADDTION_LEN + bytes, s, size);
	}

	return 0;

copy_err:
	close(fd);
	return -1;
}

int sys_clipboard_paste(char **s, int *size)
{
	int fd, bytes;
	struct stat stat;
	void *ptr;

	*size = 0;

	if ((fd = shm_open(SHMNAME, O_RDONLY, FILE_MODE)) == -1)
		return -1;

	if (fstat(fd, &stat) == -1 || stat.st_size < BYTES_PLACE)
		goto paste_err;

	if ((ptr = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, 
					fd, 0)) == MAP_FAILED)
		goto paste_err;

	close(fd);

	if ((bytes = *((uint32_t *)ptr)) <= 0)
		goto paste_err;

	*size = bytes;
	*s = (char *)ptr + ADDTION_LEN;

	return 0;

paste_err:
	close(fd);
	return -1;
}
