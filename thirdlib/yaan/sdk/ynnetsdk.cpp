#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include <dirent.h>
#include <sys/stat.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <deque>

#include "ynnetsdk.h"
#include "debug.h"

#include <pthread.h>

/****************************************************************
 * 全局变量
 ****************************************************************/
static int s_s32LoginID = 0;
static std::deque<stLoginInfo> s_UserLoginInfoQueue;

static int set_recv_timeout(int sock, int seconds)
{
	struct timeval tmo;
	tmo.tv_sec = seconds;
	tmo.tv_usec = 0;

	return setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tmo, 
			sizeof(struct timeval));
}

static int CheckElemInQueue(std::deque<stLoginInfo> *pQueue, int s32LoginID)
{
    int IsIn = 0;
    std::deque<stLoginInfo>::iterator i;

    for (i = pQueue->begin(); i < pQueue->end(); i++)
    {
        if (i->s32LoginID == s32LoginID)
        {
            IsIn = 1;
            break;
        }
    }

    if (IsIn)
    {
        return 1;
    }
    else
    {
        LOGWRN("there is no LoginID in queue\n");
        return 0;
    }
}

static int GetQueueElem(std::deque<stLoginInfo> *pQueue, int s32LoginID,
                        stLoginInfo *LoginInfo)
{
    int IsGet = 0;
    std::deque<stLoginInfo>::iterator i;

    for (i = pQueue->begin(); i < pQueue->end(); i++)
    {
        if (i->s32LoginID == s32LoginID)
        {
            *LoginInfo = *i;
            IsGet = 1;
            break;
        }
    }

    if (IsGet)
    {
        return 0;
    }
    else
    {
        LOGERR("there is no LoginID in queue\n");
        return -1;
    }
}

static int PushQueueElem(std::deque<stLoginInfo> *pQueue, int s32LoginID,
                         stLoginInfo *stLogin)
{
    int ret = 0;

    ret = CheckElemInQueue(pQueue, s32LoginID);
    if (ret == 0)
    {
        pQueue->push_back(*stLogin);
    }

    return 0;
}

static int RemoveQueueElem(std::deque<stLoginInfo> *pQueue, int s32LoginID)
{
    int ret;
    std::deque<stLoginInfo>::iterator i;

    ret = CheckElemInQueue(pQueue, s32LoginID);
    if (ret == 1)
    {
        for (i = pQueue->begin(); i < pQueue->end(); i++)
        {
            if (i->s32LoginID == s32LoginID)
            {
                pQueue->erase(i);
                break;
            }
        }
    }

    return 0;
}

/*
 * BuildMsg
 * 构建数据包
 */
static int BuildMsg(StMsgPkg *stMsg, EmCmdCode emCmd, void *pDataBuf,
                     unsigned int u32DataLength)
{
    memcpy(stMsg->u8Brand, "YAAN", sizeof(stMsg->u8Brand));
    stMsg->emCmdCode = emCmd;
    stMsg->emErrCode = _ErrNo;
    stMsg->s32EchRcver = -1;

    if(pDataBuf)
    {
        if (emCmd == _CmdLogin)
        {
            stMsg->stAccount = *((StAccount *)pDataBuf);
        }
        else
        {
            memcpy(stMsg->uoData.u8DataBuffer, pDataBuf, u32DataLength);
            stMsg->u32DataLength = u32DataLength;
        }
    }
    else
    {
        stMsg->u32DataLength = 0;
    }

    stMsg->u32Padding = 0;
    stMsg->u32CheckSum = 0;
    stMsg->u32CheckSum = CheckSum(stMsg, sizeof(StMsgPkg));

    return 0;
}

/*
 * CheckEcho
 * 检验回显的数据包
 */
static int CheckEcho(StMsgPkg *stMsg, EmCmdCode emCmd)
{
    //判断校验和
    if(CheckSum(stMsg, sizeof(StMsgPkg)))
    {
        LOGERR("CheckSum error\n");
        return -1;
    }

    //判断是否为上条命令的回复
    if(emCmd != stMsg->emCmdCode)
    {
        LOGERR("emCmd != staMsg.emCmdCode\n");
        return -1;
    }

    //判断嵌入式端处理消息是否正确
    if(stMsg->emErrCode)
    {
        LOGERR("ErrCode=%#x\n", stMsg->emErrCode);
        return -1;
    }

    return 0;
}

static int TcpConnect(char *pStrIp, unsigned short u16Port,
                      unsigned int u32Timeout)
{
    int sock;
    struct sockaddr_in dest_addr;
    struct timeval timeout;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        LOGERR("socket error\n");
        return -1;
    }

    timeout.tv_sec  = u32Timeout / 1000000;
    timeout.tv_usec = u32Timeout % 1000000;
    //设置套接字选项,接收和发送超时时间1s
    if(setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)) < 0)
    {
        LOGERR("setsockopt error\n");
        close(sock);
        return -1;
    }

    if (set_recv_timeout(sock, 20) == -1) {
	    close(sock);
	    return -1;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(u16Port);
    dest_addr.sin_addr.s_addr = inet_addr(pStrIp);
    memset(&dest_addr.sin_zero, 0, sizeof(dest_addr.sin_zero));

    //连接服务器
    if(connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in)) < 0)
    {
        close(sock);
        return -1;
    }

    return sock;
}

static int TcpSend(int s32Socket, char *pData, unsigned int u32DataSize)
{
    int ret = 0, send_size;
    int data_size = u32DataSize;

    //发送数据体
    while(data_size)
    {
        pData += ret;

        send_size = data_size < TCP_SEND_MAX_SIZE ? data_size : TCP_SEND_MAX_SIZE;
        ret = send(s32Socket, pData, send_size, 0);
        if(ret <= 0)
        {
            LOGERR("send error\n");
            return -1;
        }

        data_size -= ret;

    }

    return u32DataSize;
}

static int TcpReceive(int s32Socket, char *pData, unsigned int u32DataSize)
{
    int ret = 0;
    int data_size = u32DataSize;

    //发送数据体
    while(data_size)
    {
        pData += ret;

        ret = recv(s32Socket, pData, data_size, 0);
        if(ret <= 0)
        {
            LOGERR("recv error, return %d\n", ret);
            return -1;
        }

        data_size -= ret;
    }

    return u32DataSize;
}

/*
static void TcpClose(int u32Socket)
{
    close(u32Socket);
}
*/

static int TcpClientCommServer(char *pStrIp, unsigned short u16Port,
                               char *pSendData, unsigned int u32SendDataSize,
                               unsigned int u32Timeout, bool IsRespond,
                               char *pRecvData, unsigned int u32RecvDataSize)
{
    int ret, sock;

    sock = TcpConnect(pStrIp, u16Port, u32Timeout);
    if (sock < 0)
    {
        LOGERR("TcpConnect error\n");
        return -1;
    }

    ret = TcpSend(sock, pSendData, u32SendDataSize);
    if (ret != (int)u32SendDataSize)
    {
        LOGERR("TcpSend error, ret=%d, u32SendDataSize=%d\n", ret, u32SendDataSize);
        close(sock);
        return -1;
    }

    if (IsRespond == TRUE)
    {
        ret = TcpReceive(sock, pRecvData, u32RecvDataSize);
        if (ret <= 0)
        {
            LOGERR("TcpReceive error\n");
            close(sock);
            return -1;
        }
    }

    return sock;
}

static int ClientSendCommand(EmCmdCode emCmdCode, void *pDataBuf,
                             unsigned int u32DataSize, int s32LoginID,
                             bool boIsRespond,  bool boIsEcho, bool boIsReturnSock)
{
    int ret, sock;
    StMsgPkg stMsg, stEchoMsg;
    stLoginInfo Login;
    unsigned short port;

    ret = GetQueueElem(&s_UserLoginInfoQueue, s32LoginID, &Login);
    if (ret < 0)
    {
        LOGERR("please login\n");
        return -1;
    }

    memset(&stMsg, 0, sizeof(StMsgPkg));
    stMsg.stAccount = Login.stUserAccount;

    //给u8DataBuffer字段复制，并计算校验值
    BuildMsg(&stMsg, emCmdCode, pDataBuf, u32DataSize);

    if (emCmdCode == _CmdPlayCtrl)
    {
        port = STREAM_SERVER_DEFAULT_PORT;
    }
    else
    {
        port = Login.u16DevPort;
    }

    //发送数据到服务器，并接收服务器返回的数据
    sock = TcpClientCommServer(Login.pDevIP, port, (char *)&stMsg,
                               sizeof(StMsgPkg), 3000000, boIsRespond,
                               (char *)&stEchoMsg, sizeof(StMsgPkg));
    if (sock < 0)
    {
        LOGERR("TcpClientCommServer error\n");
        return -1;
    }


    if (boIsRespond == TRUE)
    {
        //判断echo是否正确
        if(CheckEcho(&stEchoMsg, emCmdCode))
        {
            LOGERR("CheckEcho error\n");
            return -1;
        }

        if (boIsEcho == TRUE)
        {
            if(u32DataSize == stEchoMsg.u32DataLength)
            {
                memcpy(pDataBuf, stEchoMsg.uoData.u8DataBuffer, u32DataSize);
            }
            else
            {
                LOGERR("receive message data length error\n");
                return -1;
            }
        }
    }

    if (boIsReturnSock == TRUE)
    {
        return sock;
    }
    else
    {
        close(sock);
        return 0;
    }
}

static int ClientSendCommandByIp(EmCmdCode emCmdCode, void *pDataBuf,
                             unsigned int u32DataSize, char *pDevIP,
                             unsigned short u16DevPort,
                             bool boIsRespond,  bool boIsEcho,
                             bool boIsReturnSock)
{
    int sock;
    StMsgPkg stMsg, stEchoMsg;

    //给u8DataBuffer字段复制，并计算校验值
    BuildMsg(&stMsg, emCmdCode, pDataBuf, u32DataSize);

    //发送数据到服务器，并接收服务器返回的数据
    sock = TcpClientCommServer(pDevIP, u16DevPort, (char *)&stMsg,
                               sizeof(StMsgPkg), 3000000, boIsRespond,
                               (char *)&stEchoMsg, sizeof(StMsgPkg));
    if (sock < 0)
    {
        LOGERR("TcpClientCommServer error\n");
        return -1;
    }


    if (boIsRespond == TRUE)
    {
        //判断echo是否正确
        if(CheckEcho(&stEchoMsg, emCmdCode))
        {
            LOGERR("CheckEcho error\n");
            return -1;
        }

        if (boIsEcho == TRUE)
        {
            if(u32DataSize == stEchoMsg.u32DataLength)
            {
                memcpy(pDataBuf, stEchoMsg.uoData.u8DataBuffer, u32DataSize);
            }
            else
            {
                LOGERR("receive message data length error\n");
                return -1;
            }
        }
    }

    if (boIsReturnSock == TRUE)
    {
        return sock;
    }
    else
    {
        close(sock);
        return 0;
    }
}

static int ClientSetCmd(EmCmdCode emCmdCode, void *pDataBuf,
                        unsigned int u32DataSize, int s32LoginID)
{
    int ret;

    ret = ClientSendCommand(emCmdCode, pDataBuf, u32DataSize, s32LoginID, TRUE,
                      FALSE, FALSE);
    if (ret < 0)
    {
        LOGERR("ClientSendCommand error, return %d\n", ret);
        return -1;
    }

    return 0;
}

static int ClientGetCmd(EmCmdCode emCmdCode, void *pDataBuf,
                        unsigned int u32DataSize, int s32LoginID)
{
    int ret;

    ret = ClientSendCommand(emCmdCode, pDataBuf, u32DataSize, s32LoginID, TRUE,
                            TRUE, FALSE);
    if (ret < 0)
    {
        LOGERR("ClientSendCommand error\n");
        return -1;
    }

    return 0;
}

static int ClientSetCmdByIp(EmCmdCode emCmdCode, void *pDataBuf,
                            unsigned int u32DataSize, char *pDevIP,
                            unsigned short u16DevPort)
{
    int ret;

    ret = ClientSendCommandByIp(emCmdCode, pDataBuf, u32DataSize, pDevIP,
                                u16DevPort, TRUE, FALSE, FALSE);
    if (ret < 0)
    {
        LOGERR("ClientSendCommandByIp error, return %d\n", ret);
        return -1;
    }

    return 0;
}

static int RecvFrameSyncHead(int s32Socket)
{
    const char s8Sync[] = {'Y', 'A', 'A', 'N'};
    int ret, index = 0, syn_buf[3] = { 0 };
    char ch;
    bool boSync = false;

    /*接收同步字段"YAAN"*/
    while(1)
    {
        ret = recv(s32Socket, &ch, sizeof(char), 0);
        if(ret < 0)
        {
            LOGERR("recv error\n");
            return -1;
        }
        else if(ret == 0)
        {
            continue;
        }

        if(s8Sync[index] == ch)
        {
            index ++;
        }
        else
        {
            index = 0;
        }

        if(index == sizeof(s8Sync))
        {
            boSync = true;
            break;
        }
    }

    if(boSync == false)
    {
        LOGERR("OH, My God!\n");
        return -1;
    }
    else
    {
        memcpy(&syn_buf[0], s8Sync, sizeof(int));
    }

    if (TcpReceive(s32Socket, (char *)&(syn_buf[1]), sizeof(syn_buf) - sizeof(syn_buf[0])) \
                   != sizeof(syn_buf) - sizeof(syn_buf[0]))
    {
        LOGERR("TcpReceive error\n");
        return -1;
    }
    else
    {
        if(CheckSum((void *)syn_buf, sizeof(syn_buf)))
        {
            LOGERR("CheckSum error\n");
            return -1;
        }
        else
        {
            return syn_buf[1];
        }
    }
}

static int ReceiveFrameData(int s32Socket, stFrameDataInfo *pFrameData,
                            int s32TimeOut)
{
    char *pData = NULL;
    unsigned int data_size;

    //接收同步头
    data_size = RecvFrameSyncHead(s32Socket);
    //LOGDBG("data_size=%d\n", data_size);
    if(data_size < 0)
    {
        LOGERR("RecvFrameSynHead error, return %d\n", data_size);
        return -1;
    }

    //分配内存
    pData = (char *)malloc(data_size);
    if(!pData)
    {
        LOGERR("malloc error\n");
        return -1;
    }

    //接收数据
    if(TcpReceive(s32Socket, pData, data_size) != (int)data_size)
    {
        LOGERR("TcpReceive error\n");
        free(pData);
        return -1;
    }

    pFrameData->pData = pData;
    pFrameData->DataSize = data_size;

    return 0;
}

static int ClientRequestMedia(int s32LoginID, unsigned int u32Timeout,
                              emMediaType MediaType, char s8ChanNum)
{
    StPlayCtrl stPlayCtrl;
    int sock;

    stPlayCtrl.emTranProto = _tcpserv;

    if (MediaType == _VIDEO)
    {
        stPlayCtrl.u8IsPlayingVideo = 1;
        stPlayCtrl.u8IsPlayingAudio = 0;
    }
    else if (MediaType == _AUDIO)
    {
        stPlayCtrl.u8IsPlayingVideo = 0;
        stPlayCtrl.u8IsPlayingAudio = 1;
    }
    else if (MediaType == _VIDEO_AND_AUDIO)
    {
        stPlayCtrl.u8IsPlayingVideo = 1;
        stPlayCtrl.u8IsPlayingAudio = 1;
    }
    else
    {
        LOGERR("MediaType is error\n");
        return -1;
    }

    stPlayCtrl.s8ChanNum = s8ChanNum;

    sock = ClientSendCommand(_CmdPlayCtrl, &stPlayCtrl, sizeof(stPlayCtrl),
                              s32LoginID, FALSE, FALSE, TRUE);
    if (sock < 0)
    {
        LOGERR("ClientSendCommand error\n");
        return -1;
    }

    return sock;
}

/***********************************************************************
 * 设备注册
 ***********************************************************************/

void YN_Init()
{
    static int IsInit = 0;

    if (IsInit == 0)
    {
        s_UserLoginInfoQueue.clear();
        IsInit = 1;
        s_s32LoginID = 0;
    }
}

/*
 * NvsLogin
 * 登录，登录后才能使用相应权限的命令
 */
int YN_Login(char *pDevIp, unsigned short u16DevPort, StAccount *stAccount)
{
    int ret;
    stLoginInfo Login;

    ret = ClientSetCmdByIp(_CmdLogin, stAccount, sizeof(StAccount), pDevIp, u16DevPort);
    if(ret < 0)
    {
        LOGERR("ClientSetCmdByIp error\n");
        return -1;
    }

    strcpy(Login.pDevIP, pDevIp);
    Login.u16DevPort = u16DevPort;
    Login.stUserAccount = *stAccount;
    Login.s32LoginID = s_s32LoginID;

    PushQueueElem(&s_UserLoginInfoQueue, s_s32LoginID, &Login);

    s_s32LoginID++;

    LOGDBG("LoginID=%d\n", s_s32LoginID -1);

    return (s_s32LoginID - 1);
}

/*
 * NvsLogout
 * 注销
 */
void YN_Logout(int s32LoginID)
{
    RemoveQueueElem(&s_UserLoginInfoQueue, s32LoginID);
}

/***********************************************************************
 * 获取音视频流
 ***********************************************************************/

int YN_StartVideo(int s32LoginID, char s8ChanNum)
{
    int sock;

    sock = ClientRequestMedia(s32LoginID, 1000000, _VIDEO, s8ChanNum);
    if (sock < 0)
    {
        LOGERR("ClientRequestMedia error\n");
        return -1;
    }

    return sock;
}

void YN_StopVideo(int s32Socket)
{
    close(s32Socket);
}

int YN_GetVideo(int s32Socket, stFrameDataInfo *pFrameData)
{
    int ret;

    ret = ReceiveFrameData(s32Socket, pFrameData, 3000000);
    if (ret < 0)
    {
        LOGERR("ReceiveFrameData error\n");
        return -1;
    }

    return 0;
}

void YN_RealseVideo(stFrameDataInfo pFrameData)
{
    free(pFrameData.pData);
}

/*********************************************************************
 * 数据保存
 *********************************************************************/

int YN_SaveRealDate(int s32Socket, char *pFileName)
{
    return 0;
}

/*********************************************************************
 *云台控制
 *********************************************************************/

/*
 * NvsPtzCtrl
 * 发送云台控制命令
 */
int YN_PtzCtrl(int s32LoginID, StPtzCtrl *stPtzCtrl)
{
    int ret;

    ret = ClientSetCmd(_CmdPtzCtrl, stPtzCtrl, sizeof(StPtzCtrl), s32LoginID);
    if (ret < 0)
    {
        LOGERR("ClientSetCmd error\n");
    }

    return ret;
}

/*
 * NvsSetPtzAttr
 * 设置云台控制接口参数，例如用于云台控制的串口波特率等
 */
int YN_SetPtzAttr(int s32LoginID, StPtzAttr *stPtzAttr)
{
    int ret;

    ret = ClientSetCmd(_CmdSetPtzAttr, stPtzAttr, sizeof(StPtzAttr), s32LoginID);
    if (ret < 0)
    {
        LOGERR("ClientSetCmd error\n");
    }

    return ret;
}

/*
 * NvsGetPtzAttr
 * 获取云台控制接口参数，例如用于云台控制的串口波特率等
 */
int YN_GetPtzAttr(int s32LoginID, StPtzAttr *stPtzAttr)
{
    int ret;

    ret = ClientGetCmd(_CmdGetPtzAttr, stPtzAttr, sizeof(StPtzAttr), s32LoginID);
    if (ret < 0)
    {
        LOGERR("ClientSetCmd error\n");
    }

    return ret;
}

/* Add by Fangxm */
struct YN_real_handle_t {
	char ip[24];
	int port;
	char user[24];
	char pwd[24];
	int channel;
	int login_id;
	int realplay_id;
	YN_RealDataCallBack cbk;
	void *param;
	int stop;
};

static int realplay(YN_real_handle_t *handle)
{
	int login_id;
	int realplay_id;
	StAccount acco;

	/* login */
	snprintf(acco.s8UserName, sizeof(acco.s8UserName), handle->user);
	snprintf(acco.s8Password, sizeof(acco.s8Password), handle->pwd);
	acco.u16WebExPort = 80;
	login_id = YN_Login(handle->ip, handle->port, &acco);
	if (login_id == -1)
		return -1;
	handle->login_id = login_id;

	/* start realplay */
	/* channel: '0'(main), '1'(sub) */
	realplay_id = YN_StartVideo(login_id, (handle->channel - 1) + 48);
	if (realplay_id < 0) {
		YN_Logout(login_id);
		return -1;
	}
	handle->realplay_id = realplay_id;
	return 0;
}

static int re_connect(YN_real_handle_t *handle)
{
	while (handle->stop == 0) {
		if (realplay(handle) == 0)
			return 0;
		sleep(5);
	}

	return -1;
}

static void *recv_data_thread(void *arg)
{
	YN_real_handle_t *handle = (YN_real_handle_t *)arg;
	stFrameDataInfo frame;

	while (handle->stop == 0) {
		if (YN_GetVideo(handle->realplay_id, &frame) == -1) {
			YN_StopVideo(handle->realplay_id);
			YN_Logout(handle->login_id);
			if (re_connect(handle) == -1)
				break;
			continue;
		}
		handle->cbk((unsigned long)handle, 0, frame.pData, 
				frame.DataSize, handle->param);
		YN_RealseVideo(frame);
	}

	if (handle->realplay_id)
		YN_StopVideo(handle->realplay_id);
	if (handle->login_id)
		YN_Logout(handle->login_id);
	free(handle);
	return NULL;
}

YN_real_handle_t *YN_My_StartVideo(char *ip, int port, char *user, char *pwd,
		int channel, YN_RealDataCallBack callback, void *param)
{
	YN_real_handle_t *handle;
	pthread_t tid;

	handle = (YN_real_handle_t *)calloc(1, sizeof(YN_real_handle_t));
	if (handle == NULL)
		return NULL;

	snprintf(handle->ip, sizeof(handle->ip), ip);
	handle->port = port;
	snprintf(handle->user, sizeof(handle->user), user);
	snprintf(handle->pwd, sizeof(handle->pwd), pwd);
	handle->channel = channel;
	handle->cbk = callback;
	handle->param = param;
	handle->stop = 0;

	if (realplay(handle) != 0) {
		free(handle);
		return NULL;
	}

	if (pthread_create(&tid, NULL, recv_data_thread, handle) != 0) {
		YN_StopVideo(handle->realplay_id);
		YN_Logout(handle->login_id);
		free(handle);
		return NULL;
	}
	pthread_detach(tid);

	return handle;
}

void YN_My_StopVideo(YN_real_handle_t *handle)
{
	if (handle == NULL)
		return;
	handle->stop = 1;
}
