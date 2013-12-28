#include "jxj_proxy.h"
#include "dp_interface.h"

#include <stdio.h>

#define LSN_PORT	7008

static int init()
{
	printf("call init()\n");
	return 0;
}

static unsigned long get_last_error()
{
	return 0;
}

static int login(char *ip, int port, char *user, char *pwd)
{
	return 0;
}

static int realplay()
{
	return 0;
}

static int stop_realplay()
{
	return 0;
}

static int ptzctl()
{
	return 0;
}

static int search_file()
{
	return 0;
}

static int playback()
{
	return 0;
}

static int stop_playback()
{
	return 0;
}

static int logout()
{
	return 0;
}

static int cleanup()
{
	return 0;
}

static struct dp_t jxj_dp = {
	LSN_PORT,
	init,
	get_last_error,
	login,
	realplay,
	stop_realplay,
	ptzctl,
	search_file,
	playback,
	stop_playback,
	logout,
	cleanup
};

struct dp_t *dp_get()
{
	return &jxj_dp;
}
