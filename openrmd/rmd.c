/*
 * Author: Fangxm
 * Date:   Tue Jul 12 15:27:28 CST 2011
 */

#include "rmd.h"
#include "rmd_devmgr.h"
#include "rmd_sessmgr.h"
#include "getcfg.h"
#include "get_absolute_filename.h"
#include "localip.h"
#include "proc_runtime.h"

#ifdef RMD_HAS_RTSPSVR
#include "access/rmd_rtspsvr.h"
#endif

#ifdef RMD_HAS_SIPUAS
#include "access/rmd_sipuas.h"
#endif

#ifdef RMD_HAS_UDPSVR
#include "access/rmd_udpsvr.h"
#endif

#ifdef RMD_HAS_UDS
#include "access/rmd_uds.h"
#endif

#ifdef RMD_HAS_REC
#include "rmd_rec.h"
#endif

static int logid = LOG_VARLOG;
static int device_initilized = 0;

static void get_opt(int argc, char **argv);
static void init(char **argv);
static void uninit(int sig);

int main(int argc, char **argv)
{
	get_opt(argc, argv);
	init(argv);

	while (1)
		pause();

	return 0;
}

static void get_opt(int argc, char **argv)
{
	int opt, debug = 0, exit_code = 0;

	while ((opt = getopt(argc, argv, "dvh")) != -1) {
		switch (opt) {
			case 'd':
				debug = 1;
				logid = LOG_CONSOLE;
				break;
			case 'v':
				if (argc != 2) {
					exit_code = -1;
					goto usage;
				}
				printf("%s version %s build:%s %s\n", argv[0], 
						RMDVER, __DATE__, __TIME__);
				exit(0);
			case 'h':
				if (argc != 2)
					exit_code = -1;
				goto usage;
			default:
				exit_code = -1;
				goto usage;
		}
	}

	if (!debug)
		daemon(1, 0);
	return;

usage:
	printf("Usage: %s [options]\n"
			"\t-d: print debug message on console\n"
			"\t-v: print version\n"
			"\t-h: show help\n", argv[0]);
	exit(exit_code);
}

time_t get_runtime()
{
	return proc_runtime_get();
}

static void init(char **argv)
{
	/* set config file name */
	get_absolute_filename(CFGFILE, cfg_file, sizeof(cfg_file));

	/* open syslog */
	openlog(argv[0], LOG_CONS | LOG_PID, logid);
	int logmask;
	if (getcfg(cfg_file, "logmask", &logmask, GETCFG_INT32) == 0) {
		if (logmask >= LOG_EMERG && logmask <= LOG_DEBUG)
			setlogmask(LOG_UPTO(logmask));
	}

	syslog(LOG_INFO, "openrmd start ...");
	syslog(LOG_INFO, "version %s build:%s %s", RMDVER, __DATE__, __TIME__);

	/* set some signal handling */
	signal(SIGTERM, uninit);
	signal(SIGINT, uninit);
	signal(SIGPIPE, SIG_IGN);

	/* get local IP address */
	char interface[64];
	if (getcfg(cfg_file, "interface", interface, GETCFG_STR) != 0) {
		syslog(LOG_INFO, "can't get network interface, use eth0");
		snprintf(interface, sizeof(interface), "eth0");
	}
	if (localip(interface, local_ip, sizeof(local_ip)) != 0) {
		syslog(LOG_ERR, "get %s ip address error", interface);
		exit(1);
	}

#ifndef RMD_DYNAMIC_DEVICES
	/* execute the update device config file process if need */
	char device_cfg_proc[PATH_MAX], cmd[PATH_MAX];
	if (getcfg(cfg_file, "device_cfg_proc", device_cfg_proc, 
				GETCFG_STR) != 0) {
		syslog(LOG_INFO, "skip update device config process");
	} else {
		syslog(LOG_INFO, "exec %s to update device config", 
				device_cfg_proc);
		snprintf(cmd, sizeof(cmd), "./%s %s", 
				device_cfg_proc, cfg_file);
		if (system(cmd) != 0) {
			syslog(LOG_ERR, "execute %s error", device_cfg_proc);
			exit(1);
		}
	}
#endif

	if (proc_runtime_init() != 0) {
		syslog(LOG_ERR, "initialize process run time failed.");
		exit(1);
	}

	if (rmd_devmgr_init() != 0) {
		syslog(LOG_ERR, "initialize device error.");
		exit(1);
	}
	device_initilized = 1;

	if (rmd_sessmgr_init() != 0) {
		syslog(LOG_ERR, "initialize session error.");
		exit(1);
	}

#ifdef RMD_HAS_RTSPSVR
	if (rmd_rtspsvr_start() != 0) {
		syslog(LOG_ERR, "start rtsp server error.");
		exit(1);
	}
	usleep(1000);
#endif

#ifdef RMD_HAS_SIPUAS
	if (rmd_sipuas_start() != 0) {
		syslog(LOG_ERR, "start sip uas error.");
		exit(1);
	}
	usleep(1000);
#endif

#ifdef RMD_HAS_UDPSVR
	if (rmd_udpsvr_start() != 0) {
		syslog(LOG_ERR, "start udp server error.");
		exit(1);
	}
	usleep(1000);
#endif

#ifdef RMD_HAS_UDS
	if (rmd_uds_start() != 0) {
		syslog(LOG_ERR, "start UNIX domain socket server error");
		exit(1);
	}
	usleep(1000);
#endif

#ifdef RMD_HAS_REC
	rmd_rec_start();
	usleep(1000);
#endif
}

static void uninit(int sig)
{
	if (device_initilized != 1)
		goto out;

#ifdef RMD_HAS_RTSPSVR
	rmd_rtspsvr_stop();
#endif

#ifdef RMD_HAS_SIPUAS
	rmd_sipuas_stop();
#endif

#ifdef RMD_HAS_UDPSVR
	rmd_udpsvr_stop();
#endif

#ifdef RMD_HAS_UDS
	rmd_uds_stop();
#endif

#ifdef RMD_HAS_REC
	rmd_rec_stop();
#endif

out:
	syslog(LOG_INFO, "openrmd closed");
	closelog();
	exit(0);
}
