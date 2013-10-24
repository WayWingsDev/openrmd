#include "launet.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct {
	LONG userid;
	char ip[32];
	int  port;
	char user[128];
	char pwd[128];
	int  channel_id;
	data_callback_t cbk;
	void *param;
	int  succ;
	int  stop;
	sem_t succ_sem;
	sem_t stop_sem;
	sem_t conn_sem;
	pthread_t tid;
} realplay_handle_t;

/*
static void show_errmsg(int wParam, int lParam)
{
	switch (wParam) {
	case LAUMSG_LINKMSG: {
		if (lParam == 0) {
			printf("connect successful\n");
		} else if (lParam == 1) {
			printf("user stop connect\n");
		} else if (lParam == 2) {
			printf("connect failed\n");
		} else if (lParam == 3) {
			printf("connect dislinked\n");
		} else if (lParam == 4) {
			printf("port assert\n");
		} else if (lParam == 5) {
			printf("memory assign failed\n");
		} else if (lParam == 6) {
			printf("connect dns failed\n");
		} else if (lParam == -102) {
			printf("username or password wrong\n");
		} else if (lParam == -103) {
			printf("system user full\n");
		} else if (lParam == -105) {
			printf("channel user full\n");
		} else if (lParam == -106) {
			printf("no such channel\n");
		} else if (lParam == -112) {
			printf("not find server\n");
		}

		break;
	     }

	case LAUMSG_VIDEOMOTION:
		printf("video motion alarm\n");
		break;
	case LAUMSG_VIDEOLOST:
		printf("video lost alarm\n");
		break;
	case LAUMSG_ALARM:
		printf("sensor alarm\n");
		break;
	case LAUMSG_OUTPUTSTATUS:
		printf("alarmout status\n");
		break;
	case LAUMSG_CURSWITCHCHAN:
		printf("curswitch\n");
		break;
	case LAUMSG_HIDEALARM:
		printf("video hiden alarm\n");
		break;

	default:
		break;
	}
}
*/

static void video_data_callback(char *buff, int head_size, int data_size,
		int timetick, int biskeyframe, void *context)
{
	realplay_handle_t *p = (realplay_handle_t *)context;
	p->cbk((unsigned long)p, VSNET_VIDEO_DATA, buff, data_size, p->param);
}

static void audio_data_callback(char *buff, int head_size, int data_size,
		int timetick, int biskeyframe, void *context)
{
}

static void free_handle(realplay_handle_t *p)
{
	if (p == NULL)
		return;

	sem_destroy(&p->succ_sem);
	sem_destroy(&p->stop_sem);
	sem_destroy(&p->conn_sem);

	if (p->userid > 0) {
		VSNET_ClientStopNomalCap(p->userid);
		VSNET_ClientStop(p->userid);
	}

	free(p);
}

static void msg_callback(LONG hHandle, int wParam, int lParam, void *context)
{
	realplay_handle_t *p = (realplay_handle_t *)context;

	if (wParam == LAUMSG_LINKMSG && lParam == 0) {	/* connect success */
		sem_post(&p->conn_sem);
	} else if (wParam == LAUMSG_LINKMSG && lParam == 3) {
		printf("connect dislinked\n");
		sem_post(&p->stop_sem);
	} else if (wParam == LAUMSG_LINKMSG && lParam == 2 && p->succ == 0) {
		printf("connect failed\n");
		sem_post(&p->stop_sem);
	} else {
		; //show_errmsg(wParam, lParam);
	}
}

static int realplay(realplay_handle_t *p)
{
	CHANNEL_CLIENTINFO cli;
	struct timespec ts;
	BOOL ret;

	cli.m_sername = p->ip;
	cli.m_username = p->user;
	cli.m_password = p->pwd;
	cli.m_tranType = 3; 	/* TCP */
	cli.m_playstart = FALSE;
	cli.m_ch = p->channel_id;
	cli.m_hVideohWnd = NULL;
	cli.m_hChMsgWnd = NULL;
	cli.m_nChmsgid = 0;
	cli.m_buffnum = 30;
	cli.m_useoverlay = FALSE;
	cli.nColorKey = 0x00FF00FF;
	cli.m_messagecallback = msg_callback;
	cli.context = (void *)p;

	if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
		return -1;
	ts.tv_sec += 5;

	p->userid = VSNET_ClientStart(p->ip, &cli, p->port, 0);
	if (p->userid == -1)
		return -1;
	while ((ret = sem_timedwait(&p->conn_sem, &ts)) == -1 && errno == EINTR)
		continue;
	if (ret == -1) {
		VSNET_ClientStop(p->userid);
		return -1;
	}

	ret = VSNET_ClientStartNomalCap(p->userid, video_data_callback, p, 
			audio_data_callback, p);
	if (ret != TRUE) {
		VSNET_ClientStop(p->userid);
		return -1;
	}

	return 0;
}

static void *realplay_thread(void *arg)
{
	realplay_handle_t *p = (realplay_handle_t *)arg;
	int first = 0;
	int ret;
	struct timespec ts;

	while (1) {
		p->succ = realplay(p);
		if (first == 0) {
			first = 1;
			sem_post(&p->succ_sem);
			if (p->succ == -1)
				break;
		}

		if (p->succ == -1) {
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec += 5;
			while ((ret = sem_timedwait(&p->stop_sem, &ts)) == -1 
					&& errno == EINTR)
				continue;
		} else {
			while (sem_wait(&p->stop_sem) == -1 && errno == EINTR)
				continue;
			VSNET_ClientStopNomalCap(p->userid);
			VSNET_ClientStop(p->userid);
		}

		if (p->stop == 1)
			break;
	}

	return NULL;
}

BOOL VSNET_My_SDK_Init()
{
	if (VSNET_ClientStartup(0, NULL, NULL, NULL, NULL) != TRUE) {
		printf("VSNET_ClientStartup() failed\n");
		return FALSE;
	}

	if (VSNET_ClientWaitTime(5, 3) != TRUE) {
		printf("VSNET_ClientWaitTime() failed\n");
		return FALSE;
	}

	return TRUE;
}

BOOL VSNET_My_SDK_Cleanup()
{
	return VSNET_ClientCleanup();
}

LONG VSNET_My_StartVideo(char *ip, int port, char *user, char *pwd,
		int channel_id, data_callback_t cbk, void *param)
{
	realplay_handle_t *p;
	struct timespec ts;
	int ret;

	p = (realplay_handle_t *)calloc(1, sizeof(realplay_handle_t));
	if (p == NULL)
		return -1;

	if (sem_init(&p->succ_sem, 0, 0) != 0 ||
			sem_init(&p->stop_sem, 0, 0) != 0 ||
			sem_init(&p->conn_sem, 0, 0) != 0)
		goto err;

	snprintf(p->ip, sizeof(p->ip), ip);
	p->port = port;
	snprintf(p->user, sizeof(p->user), user);
	snprintf(p->pwd, sizeof(p->pwd), pwd);
	p->channel_id = channel_id - 1;		/* channel count start 0 */
	p->cbk = cbk;
	p->param = param;
	p->succ = -1;
	p->stop = 0;

	ret = pthread_create(&p->tid, NULL, realplay_thread, p);
	if (ret != 0)
		goto err;

	if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
		goto err;
	ts.tv_sec += 5;
	while (sem_timedwait(&p->succ_sem, &ts) == -1 && errno == EINTR)
		continue;
	if (p->succ != 0) {
		pthread_join(p->tid, NULL);
		goto err;
	}

	return (LONG)p;

err:
	p->userid = 0;
	free_handle(p);
	return -1;
}

BOOL VSNET_My_StopVideo(LONG handle)
{
	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1 || handle == 0)
		return FALSE;

	p->stop = 1;
	sem_post(&p->stop_sem);
	pthread_join(p->tid, NULL);
	free_handle(p);

	return TRUE;
}

int VSNET_My_ClientPTZCtrl(LONG handle, int type, int value)
{
	int ret;

	realplay_handle_t *p = (realplay_handle_t *)handle;
	if (handle == -1 || handle == 0)
		return -1;

	ret = VSNET_ClientPTZCtrl(p->userid, type, value, 0, NULL, 0);
	if (ret == FALSE)
		return -1;
	return 0;
}
