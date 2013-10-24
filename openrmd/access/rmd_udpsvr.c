#include "rmd_udpsvr.h"
#include "rmd.h"
#include "rmd_ptz.h"
#include "udplsn.h"
#include "getcfg.h"
#include "rmd_event.h"

static int udp_sock = -1;

static void *work_thread(void *arg)
{
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buff[512];
	int bytes;

	while (1) {
		bytes = recvfrom(udp_sock, buff, sizeof(buff) - 1, 0, 
				(struct sockaddr *)&addr, &addrlen);
		if (bytes > 0) {
			buff[bytes] = '\0';
			rmd_event_message_incoming(0, buff);
		}
	}

	return NULL;
}

int rmd_udpsvr_start()
{
	pthread_t tid;
	int udp_port;

	if (getcfg(cfg_file, "udp_port", &udp_port, GETCFG_INT32) != 0) {
		syslog(LOG_ERR, "get udp listen port error");
		return -1;
	}

	udp_sock = udplsn(udp_port);
	if (udp_sock == -1)
		return -1;

	if (pthread_create(&tid, NULL, work_thread, NULL) != 0) {
		syslog(LOG_ERR, "create udp work thread error");
		return -1;
	}

	pthread_detach(tid);

	syslog(LOG_DEBUG, "udpsvr listen on: %d", udp_port);
	return 0;
}

int rmd_udpsvr_stop()
{
	close(udp_sock);
	return 0;
}
