#include "dp.h"
#include "dp_cmd.h"
#include "tcplsn.h"
#include "set_keepalive.h"

#define KEEPALIVE_IDEL	60	/* start keeplives after period(sec) */
#define KEEPALIVE_CNT	6	/* number of keepalives before death */
#define KEEPALIVE_INTV	10	/* interval between keepalives */

typedef struct dp_t *(*func_dp_getentry_t)();
static struct dp_t *dp = NULL;
func_dp_getentry_t func_dp_getentry;

/*static void *client_thread(void *arg)
{
	int sock = (int)arg;
	char buff[1024];
	int bytes;

	set_keepalive(sock, KEEPALIVE_IDEL, KEEPALIVE_CNT, KEEPALIVE_INTV);

	while (1) {
		bytes = recv(sock, buff, sizeof(buff), 0);
		if (bytes == 0 || (bytes < 0 && errno != EINVAL)) {
			printf("recv() error: %d\n", errno);
			break;
		}

		if (bytes > 0) {
			cmd_process(sock, buff);
		}
	}

	close(sock);

	return NULL;
}

static void dp_loop()
{
	int svr_sock;
	int sock;
	struct sockaddr_in addr;
	socklen_t len;
	pthread_t tid;

	svr_sock = tcplsn(dp->lsn_port);
	if (svr_sock == -1) {
		printf("listen on port (%d) error\n", dp->lsn_port);
		return;
	}

	len = sizeof(addr);

	while (1) {
		sock = accept(svr_sock, (struct sockaddr *)&addr, &len);
		if (sock == -1) {
			printf("accept error\n");
			continue;
		}

		if (pthread_create(&tid, NULL, client_thread, 
					(void *)sock) != 0) {
			printf("create client_thread error\n");
			continue;
		}
		pthread_detach(tid);
	}
}
*/

int main(int argc, char **argv)
{
	void *dll;

	/* initialize */
	signal(SIGPIPE, SIG_IGN);

#ifdef _WIN32_
	if (wsa_startup() != 0) {
		syslog(LOG_ERR, "wsa_startup() error");
		exit(1);
	}
#endif

	/* load library */
	dll = LoadLibrary("libproxy_jxj.dll");
	if (dll == NULL) {
		syslog(LOG_ERR, "open dymic linkd library failed");
		exit(1);
	}

	func_dp_getentry = (func_dp_getentry_t)dlsym(dll, "dp_get");
	if (func_dp_getentry == NULL) {
		syslog(LOG_ERR, "can not find 'dp_get' in the .dll");
		exit(1);
	}


	dp = func_dp_getentry();
	if (dp == NULL) {
		syslog(LOG_ERR, "func_dp_getentry() failed");
		exit(1);
	}

	if (dp->init() != 0) {
		printf("dp->init() failed: %lu\n", ERRNO);
		exit(1);
	}

//	dp_loop();

	dp->cleanup();

	return 0;
}
