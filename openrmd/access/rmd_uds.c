#include "rmd_uds.h"
#include "rmd.h"
#include "rmd_sessmgr.h"
#include "uudpsock.h"
#include "getcfg.h"

static char unix_domain_path[100] = "";
static int uds_sock = -1;
static struct sockaddr_un uds_addr;

int rmd_uds_start()
{
	if (getcfg(cfg_file, "unix_domain_path", unix_domain_path, 
				GETCFG_STR) != 0) {
		syslog(LOG_ERR, "get UNIX domain sock path error");
		return -1;
	}

	uds_sock = uudpsock(unix_domain_path, &uds_addr);

	rmd_uds_sendmsg(RMD_RESTART, strlen(RMD_RESTART));

	if (uds_sock == -1)
		return -1;

	return 0;
}

int rmd_uds_sendmsg(char *buff, int bytes)
{
	int ret;

	ret = sendto(uds_sock, buff, bytes, 0, 
			(const struct sockaddr *)&uds_addr, 
			(socklen_t)sizeof(struct sockaddr_un));
	if (ret == -1)
		return -1;
	return 0;
}

int rmd_uds_stop()
{
	close(uds_sock);
	return 0;
}
