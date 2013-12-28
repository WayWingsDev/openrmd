#ifndef _SINGLE_LOGIN_H_
#define _SINGLE_LOGIN_H_

typedef struct single_login_t single_login_t;
typedef int (*single_login_func_t)(char *ip, int port, char *user, 
		char *pwd, void *param);
typedef int (*single_logout_func_t)(void *data, void *param);

single_login_t *single_login_init();
int single_login(single_login_t *sl, single_login_func_t cb, char *ip, 
		int port, char *user, char *pwd, void *param);
int single_logout(single_login_t *sl, single_logout_func_t cb, char *ip, 
		int port, void *param);

#endif	/* _SINGLE_LOGIN_H_ */
