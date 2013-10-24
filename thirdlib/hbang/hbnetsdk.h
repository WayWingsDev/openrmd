#ifndef _HBNETSDK_H_
#define _HBNETSDK_H_

#define TRUE	1
#define FALSE	0

typedef int		BOOL;
typedef unsigned long	LONG;
typedef unsigned short 	WORD;
typedef unsigned long	DWORD;
typedef unsigned char	BYTE;
typedef unsigned short  USHORT;

#define CHANNEL_NUM_MAX		128 
#define CARD_NUM_MAX		32
#define FILES_NUM_PER_QUERY	100

/* device info */
typedef struct {
	BYTE	sSerialNumber[48];
	BYTE	byAlarmInPortNum;
	BYTE	byAlarmOutPortNum;
	BYTE	byDiskNum;
	BYTE	byProtocol;
	BYTE	byChanNum;
	BYTE	byEncodeType;		/* 1:ANSI 2:UTF8 */
	BYTE	sDvrName[32];
	BYTE	sChanName[CHANNEL_NUM_MAX][32];
} HB_NET_DEVICEINFO;

/* realplay info */
typedef struct {
	BYTE	byChannel;
	BYTE	byLinkMode;
	BYTE	byMultiCast;
	char	sMultiCastIP[16];
	WORD	wPort;
} HB_NET_REALPLAY;

/* time info */
typedef struct {
	int year, mon, day, hour, min, sec;
} HB_NET_TIME;

/* record file type */
typedef enum {
	HB_NET_REC_MANUAL	= 0x01,
	HB_NET_REC_SCHEDULE	= 0x02,
	HB_NET_REC_MOTION	= 0x04,
	HB_NET_REC_ALARM	= 0x08,
	HB_NET_REC_ALL		= 0xFF
} HB_NET_RECFILE_TYPE;

/* record file search condition */
typedef struct {
	DWORD	dwSize;
	DWORD	dwChannel;
	BYTE	byType;		/* HB_NET_RECFILE_TYPE */
	DWORD	dwUseCardNo;
	HB_NET_TIME bgn;
	HB_NET_TIME end;
	BYTE	sCardNo[CARD_NUM_MAX];
	DWORD	reserve;
} HB_NET_FILEFIND_COND;

/* file information */
typedef struct {
	HB_NET_TIME bgn;
	HB_NET_TIME end;
	DWORD	dwFileSize;	/* file size (KB) */
	BYTE	byChannel;
	BYTE	byType;		/* HB_NET_RECFILE_TYPE */
} HB_NET_FILEINFO;

/* playback condition */
typedef struct {
	DWORD dwChannel;
	HB_NET_TIME bgn;
	HB_NET_TIME end;
} HB_NET_PLAYBACK_COND;

/* the return value by HB_NET_FindNextFile() */
#define HB_NET_FILE_SUCCESS	1000
#define HB_NET_FILE_NOFIND	1001
#define HB_NET_FILE_ISFINDING	1002
#define HB_NET_FILE_NOMOFILE	1003
#define HB_NET_FILE_EXCEPTION	1004

typedef void (*HB_NET_RealDataCallBack)(LONG handle, int type, 
		char *buff, int bytes, void *param);

typedef void (*HB_NET_PlayBackDataCallBack)(LONG handle, int type, 
		char *buff, int bytes, void *param);

BOOL HB_NET_Init();

BOOL HB_NET_Cleanup();

LONG HB_NET_GetLastError();

LONG HB_NET_Login(char *ip, WORD port, char *user, char *pwd, 
		HB_NET_DEVICEINFO *dev_info);

BOOL HB_NET_Logout(LONG login_handle);

LONG HB_NET_RealPlay(LONG login_handle, HB_NET_REALPLAY *info, 
		HB_NET_RealDataCallBack callback, void *param);

BOOL HB_NET_StopRealPlay(LONG realplay_handle);

LONG HB_NET_FindFile(LONG login_handle, HB_NET_FILEFIND_COND *cond);

LONG HB_NET_FindNextFile(LONG find_handle, HB_NET_FILEINFO *file_info);

BOOL HB_NET_FindClose(LONG find_handle);

LONG HB_NET_PlayBack(LONG login_handle, HB_NET_PLAYBACK_COND *cond,
		HB_NET_PlayBackDataCallBack callback, void *param);

BOOL HB_NET_PlayBackControl(LONG playback_handle, DWORD dwControlCode, 
	DWORD dwInValue, DWORD *lpOutValue);

BOOL HB_NET_StopPlayBack(LONG playback_handle);

#endif	/* _HBNETSDK_H_ */
