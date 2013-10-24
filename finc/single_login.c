#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "single_login.h"
#include "dlist.h"
#include "tcpconn.h"

/* sigle login structure */
struct single_login_t {
	dlist_t *list;
	pthread_mutex_t mtx;
};

/* login infomation */
typedef struct {
	char ip_port[32];  /* format: "ip:port", e.g, "192.168.1.10:5544" */
	int  loginid;
	int  user_num;
	void *param;
} single_login_info_t;

static inline int cmp_ipport(void *data, void *param)
{
	single_login_info_t *node = (single_login_info_t *)data;
	return strcmp((char *)node->ip_port, (char *)param);
}

static int default_login_func(char *ip, int port, char *user, char *pwd, 
		void *param)
{
	return tcpconn(ip, port, 5);
}

static int default_logout_func(void *data, void *param)
{
	single_login_info_t *info = (single_login_info_t *)data;
	if (info->loginid == 0)
		return -1;

	close(info->loginid);
	return 0;
}

single_login_t *single_login_init()
{
	single_login_t *sl;

	sl = calloc(1, sizeof(single_login_t));
	if (sl == NULL)
		return NULL;

	sl->list = dlist_init();
	pthread_mutex_init(&sl->mtx, NULL);

	return sl;
}

int single_login(single_login_t *sl, single_login_func_t cb, char *ip, 
		int port, char *user, char *pwd, void *param)
{
	if (sl == NULL || ip == NULL || port <= 0 || port >= 65535)
		return -1;

	int loginid = -1;
	char ip_port[32] = "";
	single_login_info_t *node;

	snprintf(ip_port, sizeof(ip_port), "%s:%d", ip, port);
	single_login_func_t login_func = 
		(cb == NULL) ? default_login_func : cb;

	pthread_mutex_lock(&sl->mtx);

	/* lookup ip:port, if exist, return the loginid directly */
	if (dlist_entry(sl->list, cmp_ipport, (void *)ip_port, 
				(void **)&node) == 0) {
		loginid = node->loginid;
		node->user_num++;
		pthread_mutex_unlock(&sl->mtx);
		return loginid;
	}

	/* login */
	loginid = login_func(ip, port, user, pwd, param);
	if (loginid == -1) {
		pthread_mutex_unlock(&sl->mtx);
		return -1;
	}

	node = calloc(1, sizeof(single_login_info_t));
	if (node == NULL) {
		close(loginid);
		pthread_mutex_unlock(&sl->mtx);
		return -1;
	}

	snprintf(node->ip_port, sizeof(node->ip_port), "%s:%d", ip, port);
	node->loginid = loginid;
	node->user_num = 1;
	node->param = param;

	if (dlist_add(&sl->list, (void *)node) == -1) {
		close(loginid);
		free(node);
		pthread_mutex_unlock(&sl->mtx);
		return -1;
	}

	pthread_mutex_unlock(&sl->mtx);
	return loginid;
}

int single_logout(single_login_t *sl, single_logout_func_t cb, char *ip, 
		int port, void *param)
{
	if (sl == NULL)
		return -1;

	char ip_port[32];
	single_login_info_t *node;

	snprintf(ip_port, sizeof(ip_port), "%s:%d", ip, port);
	single_logout_func_t logout_func = 
		(cb == NULL) ? default_logout_func : cb;

	pthread_mutex_lock(&sl->mtx);

	if (dlist_entry(sl->list, cmp_ipport, (void *)ip_port, 
				(void **)&node) == -1) {
		pthread_mutex_unlock(&sl->mtx);
		return -1;
	}
	if (--node->user_num <= 0)
		dlist_del(&sl->list, cmp_ipport, (void *)ip_port, logout_func, 
				param);

	pthread_mutex_unlock(&sl->mtx);
	return 0;
}
