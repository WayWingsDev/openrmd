#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "rmd_sdk.h"
#include "rolling_sign.h"

static char *rtsp_url = NULL;
static int trans = /*2*/1;
static int pure_tcp_data = 1;
static char *save_file = NULL;
static int fd = -1;

static void get_opt(int argc, char **argv)
{
	int opt, exit_code = 0;

	while ((opt = getopt(argc, argv, "u:t:f:d:ch")) != -1) {
		switch (opt) {
			case 'u':
				rtsp_url = optarg;
				break;
			case 't':
				trans = atoi(optarg);
				if (trans != 1 && trans != 2) {
					printf("transmit method error\n");
					exit(1);
				}
				break;
			case 'f':
				save_file = optarg;
				break;
			case 'h':
				if (argc != 2)
					exit_code = -1;
				goto usage;
			default:
				exit_code = -1;
				goto usage;
		}
	}

	if (rtsp_url == NULL) {
		printf("RTSP url not specify\n");
		exit_code = -1;
		goto usage;
	}

	return;

usage:
	printf("Usage: %s [options]\n"
			"\t-u <url>\n"
			"\t-f <save data to file>\n"
			"\t-h show help\n\n"
			"eg: %s -u rtsp://SVRIP:SVRPORT/real/"
			"1001-DEVTYPE-DEVID-CHANNEL-main.h264> "
			"-f /tmp/abc.264\n",
			argv[0], argv[0]);
	exit(exit_code);
}

static void write_file(char *buff, int bytes)
{
	if (save_file) {
		if (fd == -1) {
			fd = open(save_file, O_WRONLY | O_CREAT, 644);
			if (fd == -1) {
				printf("create file error:[%d]\n", errno);
				exit(1);
			}
		}

		if (write(fd, buff, bytes) != bytes) {
			printf("write error:%d %s\n", errno, strerror(errno));
			exit(1);
		}
	}
}

static void hdr_callback(unsigned long handle, 
		char *sdp, int sdp_bytes, 
		char *sps_encode, int sps_encode_bytes, 
		char *sps_decoded, int sps_decoded_bytes,
		void *param)
{
	int i;

	printf("[");
	for (i = 0; i < sps_encode_bytes; i++)
		printf("%c", sps_encode[i]);
	printf("]\n\n");

	write_file(sps_decoded, sps_decoded_bytes);
}

static void data_callback(unsigned long handle, char *buff, int bytes, 
		void *param)
{
	rolling_sign();
	write_file(buff, bytes);
}

int main(int argc, char **argv)
{
	unsigned long handle;

	get_opt(argc, argv);
	setvbuf(stdout, (char *)NULL, _IONBF, 0);

	/* initialize sdk */
	if (rmd_sdk_init() != 0) {
		printf("rmd_sdk_init() failed\n");
		exit(1);
	}
	printf("rmd_sdk_init() succ\n");

	/* call real data */
	handle = rmd_realplay_start(rtsp_url, trans, hdr_callback, NULL, 
			data_callback, NULL, pure_tcp_data);
	if (handle == -1) {
		printf("rmd_realplay_start() failed\n");
		return -1;
	}
	printf("rmd_realplay_start() succ\n");

	while (1)
		sleep(1);

	/* stop call real data */
	if (rmd_realplay_stop(handle) != 0)
		printf("rmd_realplay_stop() failed\n");
	else
		printf("rmd_realplay_stop() succ\n");
	printf("----------------------------------------\n\n");

	/* cleanup sdk */
	rmd_sdk_cleanup();

	return 0;
}
