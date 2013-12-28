#ifndef _YNNETSDK_H
#define _YNNETSDK_H

#include "protocol.h"

/**************************************************************
 * 基本数据类型
 **************************************************************/

typedef unsigned char           U8;
typedef unsigned short          U16;
typedef unsigned int            U32;

typedef signed char             S8;
typedef short                   S16;
typedef int                     S32;

#ifndef _M_IX86
    typedef unsigned long long  U64;
    typedef long long           S64;
#else
    typedef __int64             U64;
    typedef __int64             S64;
#endif

typedef char                    CHAR;
#define VOID                    void

/*********************************************************************
 * 常量定义
 *********************************************************************/

/*TCP发送的最大长度*/
#define TCP_SEND_MAX_SIZE               4096
/*前端设备控制命令的监听端口*/
#define CONTROL_SERVER_DEFAULT_PORT     7887
/*前端设备音视频流请求的监听端口*/
#define STREAM_SERVER_DEFAULT_PORT      7888

/*********************************************************************
 * 枚举定义
 *********************************************************************/

/*布尔类型*/
typedef enum
{
    FALSE = 0,
    TRUE  = 1,
}BOOL;

/*设置命令的类型*/
typedef enum
{
    _SET_COMMAND = 0,
    _GET_COMMAND,
}emCommandType;

typedef enum
{
    _VIDEO = 0,
    _AUDIO,
    _VIDEO_AND_AUDIO,
}emMediaType;

/*********************************************************************
 * 结构体定义
 *********************************************************************/

typedef struct
{
    char *pData;
    unsigned int DataSize;
}stFrameDataInfo;

typedef struct
{
    char pDevIP[16];
    unsigned short u16DevPort;
    int s32LoginID;
    StAccount stUserAccount;
}stLoginInfo;

/*********************************************************************
 * 接口定义
 *********************************************************************/

/*SDK初始化*/
void YN_Init();

/*设备注册*/
int YN_Login(char *pDevIp, unsigned short u16DevPort, StAccount *stAccount);
void YN_Logout(int s32LoginID);

/*获取音视频流*/
int YN_StartVideo(int s32LoginID, char s8ChanNum);
void YN_StopVideo(int s32Socket);
int YN_GetVideo(int s32Socket, stFrameDataInfo *pFrameData);
void YN_RealseVideo(stFrameDataInfo pFrameData);

/*云台控制*/
int YN_PtzCtrl(int s32LoginID, StPtzCtrl *stPtzCtrl);
int YN_SetPtzAttr(int s32LoginID, StPtzAttr *stPtzAttr);
int YN_GetPtzAttr(int s32LoginID, StPtzAttr *stPtzAttr);

/* Add by Fangxm */
typedef struct YN_real_handle_t YN_real_handle_t;

typedef void (*YN_RealDataCallBack)(unsigned long handle, int type, 
		char *buff, int bytes, void *param);

YN_real_handle_t *YN_My_StartVideo(char *ip, int port, char *user, char *pwd,
		int channel, YN_RealDataCallBack callback, void *param);
void YN_My_StopVideo(YN_real_handle_t *handle);

#endif
