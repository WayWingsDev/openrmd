#ifndef _HSNNETSDK_H_
#define _HSNNETSDK_H_

#define TRUE	1
#define FALSE	0

typedef int		BOOL;
typedef unsigned long	LONG;
typedef unsigned short 	WORD;
typedef unsigned long	DWORD;
typedef unsigned char	BYTE;
typedef unsigned short  USHORT;

/* realplay info */
typedef struct {
	unsigned char byType;		/* 0: main video 2: sound 3: talk */
	unsigned char byChannel;	/* normal: 0 */
	unsigned char byStatus;		/* 1: apply 0: stop */
	unsigned char byProtol;		/* normal: 1(TCP) */
	unsigned int  dev_id;		/* normal: 1234 */
	unsigned short res;		/* reserved */
	unsigned short media_port;	/* not used */
	unsigned int  media_addr;	/* not used */
} HSN_NET_REALPLAY;

typedef void (*HSN_NET_RealDataCallBack)(LONG handle, int type, 
		char *buff, int bytes, void *param);

BOOL HSN_NET_Init();

BOOL HSN_NET_Cleanup();

LONG HSN_NET_GetLastError();

LONG HSN_NET_Login(char *ip, WORD ctl_port, WORD media_port, 
		char *user, char *pwd);

BOOL HSN_NET_Logout(LONG login_handle);

LONG HSN_NET_RealPlay(LONG login_handle, HSN_NET_REALPLAY *info, 
		HSN_NET_RealDataCallBack callback, void *param);

BOOL HSN_NET_StopRealPlay(LONG realplay_handle);

#endif	/* _HSNNETSDK_H_ */
