#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "http.h"
#include "freads.h"
#include "recvn.h"

#define _DEBUG_		1

static void http_set_field(http_hdr_t *hdr, char *buff, int bytes)
{
	int i, fld_len;

#if _DEBUG_
	for (i = 0; i < bytes; i++)
		printf("%c", buff[i]);
	printf("\n");
#endif

	/* status line */
	if (strncmp(buff, HTTP_VER, strlen(HTTP_VER)) == 0 ||
			strncmp(buff, HTTP_VER10, strlen(HTTP_VER10)) == 0) {
		snprintf(hdr->status_line, STATUS_LINE_LEN, buff, bytes);
		return;
	}

	/* header field */
	for (i = 0; i < HDR_FLD_COUNT; i++) {
		fld_len = strlen(http_fld[i]);
		if (strncmp(buff, http_fld[i], fld_len) == 0) {
			if (bytes - fld_len > 0)
				strncpy(hdr->fld[i], &buff[fld_len + 1], 
						bytes - fld_len);
			break;
		}
	}
}

int http_recv(int fd, http_hdr_t *hdr, char **body, int *body_len)
{
	char buff[FLD_LEN + FLD_CON_LEN + 4], *p;
	int bytes, content_length;

	memset(hdr, 0, sizeof(http_hdr_t));
	*body = NULL;
	*body_len = 0;

	while (1) {
		p = freads(fd, buff, sizeof(buff), &bytes);
		if (p == NULL)
			return -1;

		http_set_field(hdr, buff, bytes - HTTP_CRLF_LEN + 1);
		
		if (p != buff)
			free(p);

		/* header finish */
		if (strncmp(buff, HTTP_CRLF, HTTP_CRLF_LEN) == 0) {
			/* recv http body */
			content_length = atoi(hdr->fld[CONTENT_LENGTH]);
			if (content_length > 0) {
				if ((p = malloc(content_length)) == NULL) {
					printf("allocate content buff error\n");
					return -1;
				}
				if (recvn(fd, p, content_length, 0) <= 0) {
					printf("recv content error\n");
					free(p);
					return -1;
				}
			}
			
			*body = p;
			*body_len = content_length;
			return 0;
		}
	}

	return 0;
}

int http_send(int fd, char *buff, int len)
{
	return 0;
}

int http_reply(int fd, char *status)
{
	char send_buff[STATUS_LINE_LEN];

	snprintf(send_buff, STATUS_LINE_LEN, "%s %s\r\n", HTTP_VER, status);
	send(fd, send_buff, strlen(send_buff), 0);
	return 0;
}
