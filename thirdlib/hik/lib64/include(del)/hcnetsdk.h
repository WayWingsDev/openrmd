/***************************************************************************
 *            HCNetSDK.h
 *
 *  Wed Dec  8 15:11:16 2004
 *  Copyright  2004  Hikvision
 *  Email
 ****************************************************************************/

#ifndef _HCNETSDK_H_
#define _HCNETSDK_H_


#ifdef __cpluscplus
#define NET_DVR_API extern
#else
#define NET_DVR_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//2005-03-15
#define SDK_V12
//2005-04-13
#define SDK_V13
//2005-07-11
#define SDK_V14
//2005-12-28
#define SDK_V15
//2006-04-27
#define SDK_V20
//2006-08-18
#define SDK_V21

typedef unsigned int  BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#define FALSE false
#define TRUE true


#define NET_DVR_NOERROR 					0  //没有错误
#define NET_DVR_PASSWORD_ERROR 				1  //用户名密码错误
#define NET_DVR_NOENOUGHPRI 				2  //权限不足
#define NET_DVR_NOINIT 						3  //没有初始化
#define NET_DVR_CHANNEL_ERROR 				4  //通道号错误
#define NET_DVR_OVER_MAXLINK 				5  //连接到DVR的客户端个数超过最大
#define NET_DVR_VERSIONNOMATCH				6  //版本不匹配
#define NET_DVR_NETWORK_FAIL_CONNECT		7 //连接服务器失败
#define NET_DVR_NETWORK_SEND_ERROR			8 //向服务器发送失败
#define NET_DVR_NETWORK_RECV_ERROR			9 //从服务器接收数据失败
#define NET_DVR_NETWORK_RECV_TIMEOUT		10 //从服务器接收数据超时
#define NET_DVR_NETWORK_ERRORDATA			11 //传送的数据有误
#define NET_DVR_ORDER_ERROR					12 //调用次序错误
#define NET_DVR_OPERNOPERMIT				13 //无此权限
#define NET_DVR_COMMANDTIMEOUT				14 //DVR命令执行超时
#define NET_DVR_ERRORSERIALPORT				15 //串口号错误
#define NET_DVR_ERRORALARMPORT				16 //报警端口错误
#define NET_DVR_PARAMETER_ERROR 			17  //参数错误
#define NET_DVR_CHAN_EXCEPTION				18	//服务器通道处于错误状态
#define NET_DVR_NODISK						19	//没有硬盘
#define NET_DVR_ERRORDISKNUM				20	//硬盘号错误
#define NET_DVR_DISK_FULL					21	//服务器硬盘满
#define NET_DVR_DISK_ERROR					22	//服务器硬盘出错
#define NET_DVR_NOSUPPORT					23	//服务器不支持
#define NET_DVR_BUSY						24	//服务器忙
#define NET_DVR_MODIFY_FAIL					25	//服务器修改不成功
#define NET_DVR_PASSWORD_FORMAT_ERROR		26	//密码输入格式不正确
#define NET_DVR_DISK_FORMATING				27	//硬盘正在格式化，不能启动操作
#define NET_DVR_DVRNORESOURCE				28	//DVR资源不足
#define	NET_DVR_DVROPRATEFAILED				29  //DVR操作失败
#define NET_DVR_OPENHOSTSOUND_FAIL 			30  //打开PC声音失败
#define NET_DVR_DVRVOICEOPENED 				31  //服务器语音对讲被占用
#define	NET_DVR_TIMEINPUTERROR				32  //时间输入不正确
#define	NET_DVR_NOSPECFILE					33  //回放时服务器没有指定的文件
#define NET_DVR_CREATEFILE_ERROR			34	//创建文件出错
#define	NET_DVR_FILEOPENFAIL				35  //打开文件出错
#define	NET_DVR_OPERNOTFINISH				36  //上次的操作还没有完成
#define	NET_DVR_GETPLAYTIMEFAIL				37  //获取当前播放的时间出错
#define	NET_DVR_PLAYFAIL					38  //播放出错
#define NET_DVR_FILEFORMAT_ERROR			39  //文件格式不正确
#define NET_DVR_DIR_ERROR					40	//路径错误
#define NET_DVR_ALLOC_RESOURCE_ERROR		41  //资源分配错误
#define NET_DVR_AUDIO_MODE_ERROR			42	//声卡模式错误
#define NET_DVR_NOENOUGH_BUF				43	//缓冲区太小
#define NET_DVR_CREATESOCKET_ERROR		 	44	//创建int出错
#define NET_DVR_SETSOCKET_ERROR				45	//设置int出错
#define NET_DVR_MAX_NUM						46	//个数达到最大
#define NET_DVR_USERNOTEXIST				47	//用户不存在
#define NET_DVR_WRITEFLASHERROR				48  //写FLASH出错
#define NET_DVR_UPGRADEFAIL					49  //DVR升级失败
#define NET_DVR_MAX_MSGNUM					50  //消息队列达到最大
#define NET_DVR_PLAYERFAILED				51	//播放器中错误
#define NET_DVR_MAX_USERNUM					52  //设备端用户数达到最大
#define NET_DVR_GETLOCALIPANDMACFAIL		53  //获得客户端的IP地址或物理地址失败
#define NET_DVR_NOENCODEING					54	//该通道没有编码
#define NET_DVR_IPMISMATCH					55	//IP地址不匹配
#define NET_DVR_MACMISMATCH					56	//MAC地址不匹配
#define NET_DVR_UPGRADELANGMISMATCH			57 	//升级文件语言版本不匹配
#define NET_DVR_UNKNOWN						99	//

//一些网络错误码
#define   NET_DVR_TCP_SERVICES_ERROR       -7150         /*获取端口出错*/
#define   NET_DVR_TCP_BIND_ERROR           -7152         /*绑定套接字出错*/
#define   NET_DVR_TCP_ACCEPT_ERROR         -7153        /*接收连接请求出错*/
#define   NET_DVR_TCP_HOST_ERROR           -7155         /*获取主机名出错*/
#define   NET_DVR_TCP_SOCKFD_ERROR         -7157        /*套接字描述符值非法*/
#define   NET_DVR_TCP_REMOTE_CLOSE         -7158        /*远程端连接已关闭*/
#define   NET_DVR_TCP_READ_ERROR           -7159         /*读数据出错*/
#define   NET_DVR_TCP_LISTEN_ERROR         -7161			/*监听出错*/
#define   NET_DVR_TCP_WOULDBLOCK           -7164          /* 网络拥堵*/

//查找文件和日志函数返回值
#define NET_DVR_FILE_SUCCESS				1000	//获得文件信息
#define NET_DVR_FILE_NOFIND					1001	//没有文件
#define NET_DVR_ISFINDING					1002	//正在查找文件
#define	NET_DVR_NOMOREFILE					1003	//查找文件时没有更多的文件
#define	NET_DVR_FILE_EXCEPTION				1004	//查找文件时异常

//NET_DVR_IsSupport()返回值，1－9位分别表示以下信息（位与是TRUE)表示支持；
#define NET_DVR_SUPPORT_DDRAW			0x01//支持DIRECTDRAW，如果不支持，则播放器不能工作；
#define NET_DVR_SUPPORT_BLT				0x02//显卡支持BLT操作，如果不支持，则播放器不能工作；
#define NET_DVR_SUPPORT_BLTFOURCC		0x04//显卡BLT支持颜色转换，如果不支持，播放器会用软件方法作RGB转换；
#define NET_DVR_SUPPORT_BLTSHRINKX		0x08//显卡BLT支持X轴缩小；如果不支持，系统会用软件方法转换；
#define NET_DVR_SUPPORT_BLTSHRINKY		0x10//显卡BLT支持Y轴缩小；如果不支持，系统会用软件方法转换；
#define NET_DVR_SUPPORT_BLTSTRETCHX		0x20//显卡BLT支持X轴放大；如果不支持，系统会用软件方法转换；
#define NET_DVR_SUPPORT_BLTSTRETCHY		0x40//显卡BLT支持Y轴放大；如果不支持，系统会用软件方法转换；
#define NET_DVR_SUPPORT_SSE				0x80//CPU支持SSE指令，Intel Pentium3以上支持SSE指令；
#define NET_DVR_SUPPORT_MMX				0x100//CPU支持MMX指令集，Intel Pentium3以上支持SSE指令；

#define SET_PRESET		8	/* 设置预置点 */
#define CLE_PRESET		9	/* 清除预置点 */
#define GOTO_PRESET		39	/* 转到预置点 */

#define LIGHT_PWRON		2	/* 接通灯光电源 */
#define WIPER_PWRON		3	/* 接通雨刷开关 */
#define FAN_PWRON		4	/* 接通风扇开关 */
#define HEATER_PWRON		5	/* 接通加热器开关 */
#define AUX_PWRON		6	/* 接通辅助设备开关 */

#define ZOOM_IN			11	/* 焦距以速度SS变大(倍率变大) */
#define ZOOM_OUT		12	/* 焦距以速度SS变小(倍率变小) */
#define FOCUS_NEAR		13	/* 焦点以速度SS前调 */
#define FOCUS_FAR		14	/* 焦点以速度SS后调 */
#define IRIS_OPEN		15	/* 光圈以速度SS扩大 */
#define IRIS_CLOSE		16	/* 光圈以速度SS缩小 */
#define TILT_UP			21	/* 云台以SS的速度上仰 */
#define TILT_DOWN		22	/* 云台以SS的速度下俯 */
#define PAN_LEFT		23	/* 云台以SS的速度左转 */
#define PAN_RIGHT		24	/* 云台以SS的速度右转 */

#define UP_LEFT			25	/* 云台以SS的速度上仰和左转 */
#define UP_RIGHT		26	/* 云台以SS的速度上仰和右转 */
#define DOWN_LEFT		27	/* 云台以SS的速度下俯和左转 */
#define DOWN_RIGHT		28	/* 云台以SS的速度下俯和右转 */

#define PAN_AUTO		29	/* 云台以SS的速度左右自动扫描 */

#define STA_MEM_CRUISE	34	/* 开始记录轨迹 */
#define STO_MEM_CRUISE	35	/* 停止记录轨迹 */
#define RUN_CRUISE	36	/* 开始轨迹 */

#define FILL_PRE_SEQ	30	/* 将预置点加入巡航序列 */
#define SET_SEQ_DWELL	31	/* 设置巡航点停顿时间 */
#define SET_SEQ_SPEED	32	/* 设置巡航速度 */
#define CLE_PRE_SEQ	33	/* 将预置点从巡航序列中删除 */
#define RUN_SEQ		37	/* 开始巡航 */
#define STOP_SEQ	38	/* 停止巡航 */

//显示模式
enum{NORMALMODE = 0,OVERLAYMODE};
//发送模式
enum{PTOPTCPMODE = 0,PTOPUDPMODE,MULTIMODE,PTOPRTPMODE,AUDIODETACH,NOUSEMODE};

#define NET_DVR_SYSHEAD 1		//系统头数据
#define NET_DVR_STREAMDATA 2	//流数据
#define NET_DVR_RECVKEYDATA		90	//SETPOS后接收发过来的是关键帧数据（往前找I帧）
#define NET_DVR_RECVSETPOSDATA	91	//SETPOS后接收改变位置后具体的数据

#define NET_DVR_PLAYBACKOVER	101	//回放数据播放完毕
#define NET_DVR_PLAYBACKNETCLOSE	103	//回放时候连接断开
#define NET_DVR_PLAYBACK5SNODATA	104	//回放5s没有收到数据
#define NET_DVR_REALPLAYEXCEPTION	111	//预览异常


#define NET_DVR_FILE_SUCCESS    1000 // 获得文件信息
#define NET_DVR_FILE_NOFIND    1001 // 没有文件
#define NET_DVR_ISFINDING     1002 // 正在查找文件
#define NET_DVR_NOMOREFILE   1003 // 查找文件时没有更多文件
#define NET_DVR_FILE_EXCEPTION  1004 // 查找文件时异常

//NET_DVR_PlayBackControl,NET_DVR_PlayControlLocDisplay的宏定义
#define NET_DVR_PLAYSTART		1//开始播放
#define NET_DVR_PLAYSTOP		2//停止播放
#define NET_DVR_PLAYPAUSE		3//暂停播放
#define NET_DVR_PLAYRESTART		4//恢复播放
#define NET_DVR_PLAYFAST		5//快放
#define NET_DVR_PLAYSLOW		6//慢放
#define NET_DVR_PLAYNORMAL		7//正常速度
#define NET_DVR_PLAYFRAME		8//单帧放
#define NET_DVR_PLAYSTARTAUDIO	9//打开声音
#define NET_DVR_PLAYSTOPAUDIO	10//关闭声音
#define NET_DVR_PLAYAUDIOVOLUME	11//调节音量
#define NET_DVR_PLAYSETPOS		12//改变文件回放的进度
#define NET_DVR_PLAYGETPOS		13//获取文件回放的进度
#define NET_DVR_PLAYGETTIME		14//获取当前已经播放的时间
#define NET_DVR_PLAYGETFRAME	15//获取当前已经播放的帧数
#define NET_DVR_GETTOTALFRAMES  16//获取当前播放文件总的帧数
#define NET_DVR_GETTOTALTIME    17//获取当前播放文件总的时间
#define NET_DVR_THROWBFRAME		20//丢B帧


//NET_DVR_GetDVRConfig,NET_DVR_GetDVRConfig的命令定义
#define NET_DVR_GET_DEVICECFG		100		//获取设备参数
#define NET_DVR_SET_DEVICECFG		101		//设置设备参数
#define NET_DVR_GET_NETCFG			102		//获取网络参数
#define NET_DVR_SET_NETCFG			103		//设置网络参数
#define NET_DVR_GET_PICCFG			104		//获取图象参数
#define NET_DVR_SET_PICCFG			105		//设置图象参数
#define NET_DVR_GET_COMPRESSCFG		106		//获取压缩参数
#define NET_DVR_SET_COMPRESSCFG		107		//设置压缩参数
#define NET_DVR_GET_RECORDCFG		108		//获取录像时间参数
#define NET_DVR_SET_RECORDCFG		109		//设置录像时间参数
#define NET_DVR_GET_DECODERCFG		110		//获取解码器参数
#define NET_DVR_SET_DECODERCFG		111		//设置解码器参数
#define NET_DVR_GET_RS232CFG 		112		//获取232串口参数
#define NET_DVR_SET_RS232CFG		113		//设置232串口参数
#define NET_DVR_GET_ALARMINCFG 		114		//获取报警输入参数
#define NET_DVR_SET_ALARMINCFG		115		//设置报警输入参数
#define NET_DVR_GET_ALARMOUTCFG 	116		//获取报警输出参数
#define NET_DVR_SET_ALARMOUTCFG		117		//设置报警输出参数
#define NET_DVR_GET_TIMECFG 		118		//获取DVR时间
#define NET_DVR_SET_TIMECFG			119		//设置DVR时间
#define NET_DVR_GET_PREVIEWCFG 		120		//获取预览参数
#define NET_DVR_SET_PREVIEWCFG		121		//设置预览参数
#define NET_DVR_GET_VIDEOOUTCFG 	122		//获取视频输出参数
#define NET_DVR_SET_VIDEOOUTCFG		123		//设置视频输出参数
#define NET_DVR_GET_USERCFG 		124		//获取用户参数
#define NET_DVR_SET_USERCFG			125		//设置用户参数
#define NET_DVR_GET_EXCEPTIONCFG 	126		//获取异常参数
#define NET_DVR_SET_EXCEPTIONCFG	127		//设置异常参数
//Cybasec
#define NET_DVR_GET_ZONEANDDST		128		//获取时区和夏时制参数
#define NET_DVR_SET_ZONEANDDST		129		//设置时区和夏时制参数
//叠加字符
#define NET_DVR_GET_SHOWSTRING		130		//获取叠加字符参数
#define NET_DVR_SET_SHOWSTRING		131		//设置叠加字符参数

#define NET_DVR_GET_AUXOUTCFG		140		//获取报警触发辅助输出设置
#define NET_DVR_SET_AUXOUTCFG		141		//设置报警触发辅助输出设置

#define NET_DVR_GET_PREVIEWCFG_AUX 	142		//获取-s系列双输出预览参数
#define NET_DVR_SET_PREVIEWCFG_AUX	143		//设置-s系列双输出预览参数

#define NET_DVR_GET_NTPCFG			224		//获取网络应用参数 NTP
#define NET_DVR_SET_NTPCFG			225		//设置网络应用参数 NTP
#define NET_DVR_GET_DDNSCFG			226		//获取网络应用参数 DDNS
#define NET_DVR_SET_DDNSCFG			227		//设置网络应用参数 DDNS
#define NET_DVR_GET_EMAILCFG		228		//获取网络应用参数 EMAIL
#define NET_DVR_SET_EMAILCFG		229		//设置网络应用参数 EMAIL
#define NET_DVR_GET_NETAPPCFG		198		//获取网络应用参数 NTP/DDNS/EMAIL
#define NET_DVR_SET_NETAPPCFG		199		//设置网络应用参数 NTP/DDNS/EMAIL

//SDK_V14
#define NET_DVR_GET_PICCFG_EX		200		//获取图象参数
#define NET_DVR_SET_PICCFG_EX		201		//设置图象参数
//SDK_V15 扩展命令
#define NET_DVR_GET_USERCFG_EX 		202		//获取用户参数
#define NET_DVR_SET_USERCFG_EX		203		//设置用户参数
#define NET_DVR_GET_COMPRESSCFG_EX	204		//获取压缩参数（扩展）
#define NET_DVR_SET_COMPRESSCFG_EX	205		//设置压缩参数（扩展）

//回调函数类型
#define COMM_ALARM		 0x1100	//报警信息
#define	COMM_TRADEINFO	 0x1500 //ATMDVR主动上传交易信息

//异常类型
#define EXCEPTION_EXCHANGE			0x8000	//探询设备时网络异常
#define EXCEPTION_AUDIOEXCHANGE			0x8001	//语音对讲异常
#define EXCEPTION_ALARM				0x8002	//报警异常
#define EXCEPTION_PREVIEW			0x8003	//预览异常
#define EXCEPTION_SERIAL			0x8004	//透明通道异常

/*解码设备控制码定义 NET_DVR_DecCtrlDec()*/
#define NET_DEC_STARTDEC		1
#define NET_DEC_STOPDEC			2
#define NET_DEC_STOPCYCLE		3
#define NET_DEC_CONTINUECYCLE	4

#define MAX_NAMELEN		16		//DVR本地登陆名
#define MAX_RIGHT	32			//权限
#define NAME_LEN 32
#define SERIALNO_LEN 48
#define MACADDR_LEN 6
#define MAX_ETHERNET 2
#define PATHNAME_LEN 128
#define PASSWD_LEN 16
#define MAX_CHANNUM 16
#define MAX_ALARMOUT 4
#define MAX_TIMESEGMENT	4
#define MAX_PRESET	128
//SDK_V14
#define MAX_SHELTERNUM		4
#define MAX_DAYS 7
#define PHONENUMBER_LEN	32
#define MAX_DISKNUM 16
#define MAX_WINDOW 16
#define MAX_VGA 1
#define MAX_USERNUM 16
#define MAX_EXCEPTIONNUM 16
#define MAX_LINK 6
#define MAX_ALARMIN 16
#define MAX_DECPOOLNUM		4
#define MAX_DECNUM			4
#define MAX_TRANSPARENTNUM	2
#define MAX_STRINGNUM		4


#define WATCH_NUM	512
#define SERVER_NUM	512
#define ALARM_NUM	512
#define MAX_SERVERNUM	512

#define MAXCARD_NUM 40
#define COMMANDLEN 1024
#define MAXPROGRESS 100
#define MAX_SERIALNUM 2
#define MAX_CASTNUM	100
#define CARDNUM_LEN 20
#define MAX_VIDEOOUT 2

#define MAX_STRINGNUM		4
#define MAX_AUXOUT			4
#define MAX_HD_COUNT		24
#define MAX_CYCLE_CHAN		4
#define MAX_NFS_DISK    8

//DVR TYPE
#define DVR			1
#define ATMDVR		2
#define DVS			3
#define DEC			4
#define ENC_DEC		5
#define DVR_HC		6
#define DVR_HT		7
#define DVR_HF		8
#define DVR_HS		9
#define DVR_HTS		10
#define DVR_HB		11
#define DVR_HCS		12
#define DVS_A		13
#define DVR_HC_S	14
#define DVR_HT_S	15
#define DVR_HF_S	16
#define DVR_HS_S	17
#define ATMDVR_S	18
#define LOWCOST_DVR 19
#define DEC_MAT		20	//多路解码器

typedef struct tagRect
{
	int x;
	int y;
	int uWidth;
	int uHeight;
}PLAYRECT;

typedef struct tagInitInfo
{
	int	uWidth;
	int uHeight;
}INITINFO;

typedef struct  {
	BYTE sSerialNumber[SERIALNO_LEN];  //序列号
	BYTE byAlarmInPortNum;		//DVR报警输入个数
	BYTE byAlarmOutPortNum;		//DVR报警输出个数
	BYTE byDiskNum;				//DVR 硬盘个数
	BYTE byDVRType;				//DVR类型, 1:DVR 2:ATM DVR 3:DVS
	BYTE byChanNum;				//DVR 通道个数
	BYTE byStartChan;			//起始通道号,例如DVS-1,DVR - 1
}NET_DVR_DEVICEINFO, *LPNET_DVR_DEVICEINFO;

enum{
    TCP_MODE,
    UDP_MODE,
    MULTICAST_MODE,
    RTP_MODE
};

typedef struct{
	int lChannel;//通道号
	int lLinkMode;//最高位(31)为0表示主码流，为1表示子，0－31位表示码流连接方式: 0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-音视频分开(TCP)
	PLAYRECT hPlayWnd;//播放窗口的句柄,为NULL表示不播放图象
	char* sMultiCastIP;//多播组地址
#ifdef NJLC_VER
	char mediaSrvIp[16];
	DWORD mediaSrvPort;
#endif
}NET_DVR_CLIENTINFO,*LPNET_DVR_CLIENTINFO;

//预览参数
typedef struct{
	int bToScreen;
	int bToVideoOut;
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
	int nReserved;
}NET_DVR_DISPLAY_PARA,*LPNET_DVR_DISPLAY_PARA;

typedef struct{
	int lChannel;//通道号
	int lLinkMode; //最高位(31)为0表示主码流，为1表示子，0－31位表示码流连接方式:0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-电话线，5－128k宽带，6－256k宽带，7－384k宽带，8－512k宽带；
	char* sMultiCastIP;
	NET_DVR_DISPLAY_PARA struDisplayPara;
}NET_DVR_CARDINFO,*LPNET_DVR_CARDINFO;

typedef struct{
	DWORD dwYear;		//年
	DWORD dwMonth;		//月
	DWORD dwDay;		//日
	DWORD dwHour;		//时
	DWORD dwMinute;		//分
	DWORD dwSecond;		//秒
}NET_DVR_TIME,*LPNET_DVR_TIME;

typedef struct{
	//开始时间
    BYTE byStartHour;
	BYTE byStartMin;
	//结束时间
	BYTE byStopHour;
	BYTE byStopMin;
}NET_DVR_SCHEDTIME,*LPNET_DVR_SCHEDTIME;

/*处理方式*/
#define NOACTION			0x0				/*无响应*/
#define WARNONMONITOR		0x1				/*监视器上警告*/
#define WARNONAUDIOOUT		0x2				/*声音警告*/
#define UPTOCENTER			0x4				/*上传中心*/
#define TRIGGERALARMOUT		0x8				/*触发报警输出*/
#define TRIGGERCATPIC	0x20	/* trigger catch picture */

typedef struct
{
	DWORD	dwHandleType;			/*处理方式,处理方式的"或"结果*/
									/*0x00: 无响应*/
									/*0x01: 监视器上警告*/
									/*0x02: 声音警告*/
									/*0x04: 上传触发报警输出中心*/
									/*0x08: 触发报警输出*/
									/*0x20: 触发抓图*/
	BYTE byRelAlarmOut[MAX_ALARMOUT];  //报警触发的输出通道,报警触发的输出,为1表示触发该输出
}NET_DVR_HANDLEEXCEPTION;

//DVR设备参数
typedef struct{
	DWORD dwSize;
	BYTE sDVRName[NAME_LEN];     //DVR名称
	DWORD dwDVRID;				//DVR ID,用于遥控器
	DWORD dwRecycleRecord;		//是否循环录像,0:不是; 1:是
//以下不能更改
	BYTE sSerialNumber[SERIALNO_LEN];  //序列号
	DWORD dwSoftwareVersion;			//软件版本号,高16位是主版本,低16位是次版本
	DWORD dwSoftwareBuildDate;			//软件生成日期,0xYYYYMMDD
	DWORD dwDSPSoftwareVersion;		//DSP软件版本,高16位是主版本,低16位是次版本
	DWORD dwDSPSoftwareBuildDate;		// DSP软件生成日期,0xYYYYMMDD
	DWORD dwPanelVersion;				// 前面板版本,高16位是主版本,低16位是次版本
	DWORD dwHardwareVersion;	// 硬件版本,高16位是主版本,低16位是次版本
	BYTE byAlarmInPortNum;		//DVR报警输入个数
	BYTE byAlarmOutPortNum;		//DVR报警输出个数
	BYTE byRS232Num;			//DVR 232串口个数
	BYTE byRS485Num;			//DVR 485串口个数
	BYTE byNetworkPortNum;		//网络口个数
	BYTE byDiskCtrlNum;			//DVR 硬盘控制器个数
	BYTE byDiskNum;				//DVR 硬盘个数
	BYTE byDVRType;				//DVR类型, 1:DVR 2:ATM DVR 3:DVS
	BYTE byChanNum;				//DVR 通道个数
	BYTE byStartChan;			//起始通道号,例如DVS-1,DVR - 1
	BYTE byDecordChans;			//DVR 解码路数
	BYTE byVGANum;				//VGA口的个数
	BYTE byUSBNum;				//USB口的个数
	char reservedData[3];		//保留
}NET_DVR_DEVICECFG,*LPNET_DVR_DEVICECFG;

typedef struct {
	char sDVRIP[16];          //DVR IP地址
	char sDVRIPMask[16];      // DVR IP地址掩码
	DWORD dwNetInterface;   //网络接口 1-10MBase-T 2-10MBase-T全双工 3-100MBase-TX 4-100M全双工 5-10M/100M自适应
	WORD wDVRPort;		//端口号
	BYTE byMACAddr[MACADDR_LEN];		//服务器的物理地址
}NET_DVR_ETHERNET;

//网络配置结构
typedef struct{
	DWORD dwSize;
	NET_DVR_ETHERNET struEtherNet[MAX_ETHERNET];		/* 以太网口 */
	char sManageHostIP[16];		//远程管理主机地址
	WORD wManageHostPort; //远程管理主机端口号
	char sIPServerIP[16];            //IP Server服务器地址
	char sMultiCastIP[16];     //多播组地址
	char sGatewayIP[16];       	//网关地址
	char sNFSIP[16];			//NFS主机IP地址
	BYTE sNFSDirectory[PATHNAME_LEN];//NFS目录
	DWORD dwPPPOE;				//0-不启用,1-启用
	BYTE sPPPoEUser[NAME_LEN];	//PPPoE用户名
	char sPPPoEPassword[PASSWD_LEN];// PPPoE密码
	char sPPPoEIP[16];                      //PPPoE IP地址(只读)
#ifdef SDK_V14
	WORD wHttpPort;				//HTTP端口号
#endif
}NET_DVR_NETCFG,*LPNET_DVR_NETCFG;

//移动侦测
typedef struct{
	BYTE byMotionScope[18][22];	/*侦测区域,共有22*18个小宏块,为1表示该宏块是移动侦测区域,0-表示不是*/
	BYTE byMotionSensitive;		/*移动侦测灵敏度, 0 - 5,越高越灵敏,0xff关闭*/
	BYTE byEnableHandleMotion;	/* 是否处理移动侦测 */
	NET_DVR_HANDLEEXCEPTION struMotionHandleType;	/* 处理方式 */
#ifdef SDK_V13
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];
#endif
	BYTE byRelRecordChan[MAX_CHANNUM]; //报警触发的录象通道,为1表示触发该通道
}NET_DVR_MOTION,*LPNET_DVR_MOTION;

//遮挡报警  区域大小704*576
typedef struct{
	DWORD dwEnableHideAlarm;				/* 是否启动遮挡报警 ,0-否,1-低灵敏度 2-中灵敏度 3-高灵敏度 */
	WORD wHideAlarmAreaTopLeftX;			/* 遮挡区域的x坐标 */
	WORD wHideAlarmAreaTopLeftY;			/* 遮挡区域的y坐标 */
	WORD wHideAlarmAreaWidth;				/* 遮挡区域的宽 */
	WORD wHideAlarmAreaHeight;				/*遮挡区域的高*/
	NET_DVR_HANDLEEXCEPTION struHideAlarmHandleType;	/* 处理方式 */
#ifdef SDK_V13
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];
#endif
}NET_DVR_HIDEALARM,*LPNET_DVR_HIDEALARM;

//信号丢失报警
typedef struct{
	BYTE byEnableHandleVILost;	/* 是否处理信号丢失报警 */
	NET_DVR_HANDLEEXCEPTION struVILostHandleType;	/* 处理方式 */
#ifdef SDK_V13
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];
#endif
}NET_DVR_VILOST,*LPNET_DVR_VILOST;

//通道图象结构
typedef struct
{
	DWORD dwSize;
	BYTE sChanName[NAME_LEN];
	DWORD dwVideoFormat;	/* 只读 视频制式 1-NTSC 2-PAL*/
	BYTE byBrightness;  	/*亮度,0-255*/
	BYTE byContrast;    	/*对比度,0-255*/
	BYTE bySaturation;  	/*饱和度,0-255 */
	BYTE byHue;    			/*色调,0-255*/
	//显示通道名
	DWORD dwShowChanName; // 预览的图象上是否显示通道名称,0-不显示,1-显示 区域大小704*576
	WORD wShowNameTopLeftX;				/* 通道名称显示位置的x坐标 */
	WORD wShowNameTopLeftY;				/* 通道名称显示位置的y坐标 */
    //信号丢失报警
    NET_DVR_VILOST struVILost;
	//移动侦测
	NET_DVR_MOTION struMotion;
	//遮挡报警
	NET_DVR_HIDEALARM struHideAlarm;
	//遮挡  区域大小704*576
	DWORD dwEnableHide;		/* 是否启动遮挡 ,0-否,1-是*/
	WORD wHideAreaTopLeftX;				/* 遮挡区域的x坐标 */
	WORD wHideAreaTopLeftY;				/* 遮挡区域的y坐标 */
	WORD wHideAreaWidth;				/* 遮挡区域的宽 */
	WORD wHideAreaHeight;				/*遮挡区域的高*/
	//OSD
	DWORD dwShowOsd;// 预览的图象上是否显示OSD,0-不显示,1-显示 区域大小704*576
	WORD wOSDTopLeftX;				/* OSD的x坐标 */
	WORD wOSDTopLeftY;				/* OSD的y坐标 */
	BYTE byOSDType;					/* OSD类型(主要是年月日格式) */
							/* 0: XXXX-XX-XX 年月日 */
							/* 1: XX-XX-XXXX 月日年 */
							/* 2: XXXX年XX月XX日 */
							/* 3: XX月XX日XXXX年 */
							/* 4: XX-XX-XXXX 日月年*/
							/* 5: XX日XX月XXXX年 */
	BYTE byDispWeek;				/* 是否显示星期 */
	BYTE byOSDAttrib;				/* OSD属性:透明，闪烁 */
									/* 1: 透明,闪烁 */
									/* 2: 透明,不闪烁 */
									/* 3: 闪烁,不透明 */
									/* 4: 不透明,不闪烁 */
}NET_DVR_PICCFG,*LPNET_DVR_PICCFG;

typedef struct{
	WORD wHideAreaTopLeftX;				/* 遮挡区域的x坐标 */
	WORD wHideAreaTopLeftY;				/* 遮挡区域的y坐标 */
	WORD wHideAreaWidth;				/* 遮挡区域的宽 */
	WORD wHideAreaHeight;				/*遮挡区域的高*/
}NET_DVR_SHELTER,*LPNET_DVR_SHELTER;

//SDK_V14
typedef struct
{
	DWORD dwSize;
	BYTE sChanName[NAME_LEN];
	DWORD dwVideoFormat;	/* 只读 视频制式 1-NTSC 2-PAL*/
	BYTE byBrightness;  	/*亮度,0-255*/
	BYTE byContrast;    	/*对比度,0-255*/
	BYTE bySaturation;  	/*饱和度,0-255 */
	BYTE byHue;    			/*色调,0-255*/
	//显示通道名
	DWORD dwShowChanName; // 预览的图象上是否显示通道名称,0-不显示,1-显示 区域大小704*576
	WORD wShowNameTopLeftX;				/* 通道名称显示位置的x坐标 */
	WORD wShowNameTopLeftY;				/* 通道名称显示位置的y坐标 */
    //信号丢失报警
    NET_DVR_VILOST struVILost;
	//移动侦测
	NET_DVR_MOTION struMotion;
	//遮挡报警
	NET_DVR_HIDEALARM struHideAlarm;
	//遮挡  区域大小704*576
	DWORD dwEnableHide;		/* 是否启动遮挡 ,0-否,1-是*/
	NET_DVR_SHELTER struShelter[MAX_SHELTERNUM];
	//OSD
	DWORD dwShowOsd;// 预览的图象上是否显示OSD,0-不显示,1-显示 区域大小704*576
	WORD wOSDTopLeftX;				/* OSD的x坐标 */
	WORD wOSDTopLeftY;				/* OSD的y坐标 */
	BYTE byOSDType;					/* OSD类型(主要是年月日格式) */
							/* 0: XXXX-XX-XX 年月日 */
							/* 1: XX-XX-XXXX 月日年 */
							/* 2: XXXX年XX月XX日 */
							/* 3: XX月XX日XXXX年 */
	BYTE byDispWeek;				/* 是否显示星期 */
	BYTE byOSDAttrib;				/* OSD属性:透明，闪烁 */
									/* 1: 透明,闪烁 */
									/* 2: 透明,不闪烁 */
									/* 3: 闪烁,不透明 */
									/* 4: 不透明,不闪烁 */
}NET_DVR_PICCFG_EX,*LPNET_DVR_PICCFG_EX;

//压缩参数
typedef struct{
	BYTE byStreamType;		//码流类型0-视频流,1-复合流
	BYTE byResolution;  	//分辨率0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
	BYTE byBitrateType;		//码率类型0:变码率，1:定码率
	BYTE  byPicQuality;		//图象质量 0-最好 1-次好 2-较好 3-一般 4-较差 5-差
	DWORD dwVideoBitrate; 	//视频码率0-保留 1-保留 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
							// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
							//最高位(32位)置成1表示是自定义码流, 0-31位表示码流值。MIN-32k MAX-8192k
	DWORD dwVideoFrameRate;	//帧率 0-全部; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
}NET_DVR_COMPRESSION_INFO,*LPNET_DVR_COMPRESSION_INFO;

typedef struct{
	DWORD dwSize;
	NET_DVR_COMPRESSION_INFO struRecordPara; //录像
	NET_DVR_COMPRESSION_INFO struNetPara;	//网传
}NET_DVR_COMPRESSIONCFG,*LPNET_DVR_COMPRESSIONCFG;

//压缩参数(扩展)
typedef struct{
	BYTE byStreamType;		//码流类型0-视频流,1-复合流
	BYTE byResolution;  	//分辨率0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
	BYTE byBitrateType;		//码率类型0:变码率，1:定码率
	BYTE  byPicQuality;		//图象质量 0-最好 1-次好 2-较好 3-一般 4-较差 5-差
	DWORD dwVideoBitrate; 	//视频码率0-保留 1-保留 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
							// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
							//最高位(32位)置成1表示是自定义码流, 0-31位表示码流值。MIN-32k MAX-8192k
	DWORD dwVideoFrameRate;	//帧率 0-全部; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
	WORD wIntervalFrameI;		//I帧间隔
	BYTE  byIntervalBPFrame;//0-BBP帧; 1-BP帧; 2-单P帧
	BYTE  byENumber;//E帧数量
}NET_DVR_COMPRESSION_INFO_EX,*LPNET_DVR_COMPRESSION_INFO_EX;

typedef struct{
	DWORD dwSize;
	NET_DVR_COMPRESSION_INFO_EX struRecordPara; //录像
	NET_DVR_COMPRESSION_INFO_EX struNetPara;	//网传
}NET_DVR_COMPRESSIONCFG_EX,*LPNET_DVR_COMPRESSIONCFG_EX;

//录像
typedef struct{
	NET_DVR_SCHEDTIME struRecordTime;
	BYTE byRecordType;	//0:定时录像，1:移动侦测，2:报警录像，3:动测|报警，4:动测&报警, 5:命令触发, 6: 手动录像
	char reservedData[3];
}NET_DVR_RECORDSCHED,*LPNET_DVR_RECORDSCHED;

typedef struct {
	WORD wAllDayRecord;				/* 是否全天录像 0-否 1-是*/
	BYTE byRecordType;				/* 录象类型 0:定时录像，1:移动侦测，2:报警录像，3:动测|报警，4:动测&报警 5:命令触发, 6: 手动录像*/
	char reservedData;
}NET_DVR_RECORDDAY;

typedef struct {
	DWORD dwSize;
	DWORD dwRecord;  /*是否录像 0-否 1-是*/
	NET_DVR_RECORDDAY struRecAllDay[MAX_DAYS];
	NET_DVR_RECORDSCHED struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
	DWORD dwRecordTime;	/* 录象时间长度 */
	DWORD dwPreRecordTime;  /* 预录时间 0-不预录 1-5秒 2-10秒 3-15秒 4-20秒 5-25秒 6-30秒 7-0xffffffff(尽可能预录) */
}NET_DVR_RECORD,*LPNET_DVR_RECORD;



/* PTZ type */
#define YOULI						0
#define LILIN_1016					1
#define LILIN_820					2
#define PELCO_P						3
#define DM_DynaColor				4
#define HD600						5
#define JC4116						6
#define PELCO_DWX					7
#define PELCO_D						8
#define VCOM_VC_2000				9
#define NETSTREAMER					10
#define SAE_YAAN					11
#define SAMSUNG						12
#define Kalatel_312		 			13
#define CELOTEX						14
#define TLPELCO_P					15
#define TL_HHX2000					16
#define BBV							17
#define RM110						18
#define KC3360S						19
#define ACES						20
#define ALSON						21
#define INV3609HD					22
#define HOWELL						23
#define TC_PELCO_P					24
#define TC_PELCO_D					25
#define AUTO_M						26
#define AUTO_H						27
#define ANTEN						28
#define CHANGLIN					29
#define DELTADOME					30
#define XYM_12						31
#define ADR8060						32
#define EVI_D30						33
#define Demo_Speed					34
#define DM_PELCO_D					35
#define ST_832						36
#define LC_D2104					37
#define HUNTER						38
#define A01							39
#define TECHWIN						40
#define WEIHAN						41
#define LG							42
#define D_MAX						43
#define PANASONIC					44
#define KTD_348						45
#define INFINOVA					46
#define PIH_7625					47
#define LCU 						48
#define DENNARD_DOME    			49
#define PHLIPS						50
#define SAMPLE						51
#define PLD							52
#define PARCO						53
#define HY							54
#define NAIJIE						55
#define CAT_KING					56
#define YH_06						57
#define SP9096X						58
#define M_PANEL						59
#define M_MV2050					60
#define SAE_QUICK					61
#define PEARMAIN					62
#define NKO8G						63
#define DH_CC440					64
#define TX_CONTROL_232				65
#define	VCL_SPEED_DOME				66
#define	ST_2C160					67
#define TDWY						68
#define TWHC						69
#define USNT						70
#define KLT_NVD2200PS				71
#define VIDO_B01                    72
#define LG_MULTIX                  	73
#define ENKEL                       74
#define YT_PELCOD                   75
#define  HIKVISION				    76
#define  PE60						77
#define  LiAo						78
#define  NK16                       79
#define  DaLi                       80
#define  HN_4304                    81
#define  VIDEOTEC                   82
#define  HNDCB                      83
#define  Lion_2007                  84
#define  LG_LVC_C372                85
#define  Gold_Video                 86
#define  NVD1600PS                  87

//解码器
typedef struct{
	DWORD dwSize;
	DWORD dwBaudRate;//波特率(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;
	BYTE byDataBit;// 数据有几位 0－5位，1－6位，2－7位，3－8位;
	BYTE byStopBit;// 停止位 0－1位，1－2位;
	BYTE byParity;// 校验 0－无校验，1－奇校验，2－偶校验;
	BYTE byFlowcontrol;// 0－无，1－软流控,2-硬流控
	WORD wDecoderType;//解码器类型, 0－YouLi，1－LiLin-1016，2－LiLin-820，3－Pelco-p，4－DM DynaColor，5－HD600，6－JC-4116，7－Pelco-d WX，8－Pelco-d PICO
	WORD wDecoderAddress;	/*解码器地址:0 - 255*/
	BYTE bySetPreset[MAX_PRESET];		/* 预置点是否设置,0-没有设置,1-设置*/
	BYTE bySetCruise[MAX_PRESET];		/* 巡航是否设置: 0-没有设置,1-设置 */
	BYTE bySetTrack[MAX_PRESET];			/* 轨迹是否设置,0-没有设置,1-设置*/
}NET_DVR_DECODERCFG,*LPNET_DVR_DECODERCFG;

//RS232串口
typedef struct{
	char sRemoteIP[16];            //远端IP地址
	char sLocalIP[16];             //本地IP地址
	char sLocalIPMask[16];         //本地IP地址掩码
	BYTE sUsername[NAME_LEN];		/* 用户名 */
	BYTE sPassword[PASSWD_LEN];		/* 密码 */
	BYTE byPPPMode;            //PPP模式, 0－主动，1－被动
	BYTE byRedial;            //是否回拨 ：0-否,1-是
	BYTE byRedialMode;        //回拨模式,0-由拨入者指定,1-预置回拨号码
	BYTE byDataEncrypt;	     //数据加密,0-否,1-是
	DWORD dwMTU;              //MTU
	char sTelephoneNumber[PHONENUMBER_LEN];   //电话号码
}NET_DVR_PPPCFG,*LPNET_DVR_PPPCFG;

typedef struct{
	DWORD dwSize;
	DWORD dwBaudRate;//波特率(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;
	BYTE byDataBit;// 数据有几位 0－5位，1－6位，2－7位，3－8位;
	BYTE byStopBit;// 停止位 0－1位，1－2位;
	BYTE byParity;// 校验 0－无校验，1－奇校验，2－偶校验;
	BYTE byFlowcontrol;// 0－无，1－软流控,2-硬流控
	DWORD dwWorkMode;// 工作模式，0－窄带传输(232串口用于PPP拨号)，1－控制台(232串口用于参数控制)，2－透明通道
	NET_DVR_PPPCFG struPPPConfig;
}NET_DVR_RS232CFG,*LPNET_DVR_RS232CFG;

//报警输入
typedef struct{
	DWORD dwSize;
	BYTE sAlarmInName[NAME_LEN];	/* 名称 */
	BYTE byAlarmType;	//报警器类型,0：常开,1：常闭
	BYTE byAlarmInHandle;	/* 是否处理 0-不处理 1-处理*/
	BYTE byRes[2];
	NET_DVR_HANDLEEXCEPTION struAlarmHandleType;	/* 处理方式 */
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//布防时间
	BYTE byRelRecordChan[MAX_CHANNUM]; //报警触发的录象通道,为1表示触发该通道
	BYTE byEnablePreset[MAX_CHANNUM];		/* 是否调用预置点 0-否,1-是*/
	BYTE byPresetNo[MAX_CHANNUM];			/* 调用的云台预置点序号,一个报警输入可以调用多个通道的云台预置点, 0xff表示不调用预置点。*/
	BYTE byEnableCruise[MAX_CHANNUM];		/* 是否调用巡航 0-否,1-是*/
	BYTE byCruiseNo[MAX_CHANNUM];			/* 巡航 */
	BYTE byEnablePtzTrack[MAX_CHANNUM];		/* 是否调用轨迹 0-否,1-是*/
	BYTE byPTZTrack[MAX_CHANNUM];			/* 调用的云台的轨迹序号 */
}NET_DVR_ALARMINCFG,*LPNET_DVR_ALARMINCFG;

//上传报警信息
typedef struct{
	DWORD dwAlarmType;/*0-信号量报警,1-硬盘满,2-信号丢失,3－移动侦测,4－硬盘未格式化,5-读写硬盘出错,6-遮挡报警*/
	DWORD dwAlarmInputNumber;/*报警输入端口*/
	DWORD dwAlarmOutputNumber[MAX_ALARMOUT];/*报警输入端口对应的输出端口，哪一位为1表示对应哪一个输出*/
	DWORD dwAlarmRelateChannel[MAX_CHANNUM];/*报警输入端口对应的录像通道，哪一位为1表示对应哪一路录像,dwAlarmRelateChannel[0]对应第1个通道*/
	DWORD dwChannel[MAX_CHANNUM];/*dwAlarmType为2或3,6时，表示哪个通道，dwChannel[0]位对应第0个通道*/
	DWORD dwDiskNumber[MAX_DISKNUM];/*dwAlarmType为1,4,5时,表示哪个硬盘*/
}NET_DVR_ALARMINFO,*LPNET_DVR_ALARMINFO;

//DVR报警输出
typedef struct{
	DWORD dwSize;
	BYTE sAlarmOutName[NAME_LEN];	/* 名称 */
	DWORD dwAlarmOutDelay;	/* 输出保持时间(-1为无限，手动关闭) */
	NET_DVR_SCHEDTIME struAlarmOutTime[MAX_DAYS][MAX_TIMESEGMENT];/* 报警输出激活时间段 */
}NET_DVR_ALARMOUTCFG,*LPNET_DVR_ALARMOUTCFG;

//DVR本地预览参数
typedef struct{
	DWORD dwSize;
	BYTE byPreviewNumber;//预览数目,0-1画面,1-4画面,2-9画面,3-16画面,0xff:最大画面
	BYTE byEnableAudio;//是否声音预览,0-不预览,1-预览
	WORD wSwitchTime;//切换时间,0-不切换,1-5s,2-10s,3-20s,4-60s,5-120s,6-300s
	BYTE bySwitchSeq[MAX_WINDOW];//切换顺序,如果lSwitchSeq[i]为 0xff表示不用
}NET_DVR_PREVIEWCFG,*LPNET_DVR_PREVIEWCFG;

//DVR视频输出
typedef struct {
	WORD wResolution;							/* 分辨率 */
	WORD wFreq;									/* 刷新频率 */
	DWORD dwBrightness;							/* 亮度 */
}NET_DVR_VGAPARA;

typedef struct{
	WORD wDisplayLogo;						/* 显示视频通道号 */
	WORD wDisplayOsd;						/* 显示时间 */
}NET_DVR_MATRIXPARA;

typedef struct{
	BYTE byVideoFormat;						/* 输出制式,0-PAL,1-NTSC	*/
	BYTE byMenuAlphaValue;					/* 菜单与背景图象对比度 */
	WORD wScreenSaveTime;					/* 屏幕保护时间 */
	WORD wVOffset;							/* 视频输出偏移 */
	WORD wBrightness;						/* 视频输出亮度 */
	BYTE byStartMode;						/* 启动后视频输出模式(0:菜单,1:预览)*/
	char reservedData;
}NET_DVR_VOOUT;

typedef struct {
	DWORD dwSize;
	NET_DVR_VOOUT struVOOut[MAX_VIDEOOUT];
	NET_DVR_VGAPARA struVGAPara[MAX_VGA];	/* VGA参数 */
	NET_DVR_MATRIXPARA struMatrixPara;		/* MATRIX参数 */
}NET_DVR_VIDEOOUT,*LPNET_DVR_VIDEOOUT;

//DVR用户参数
typedef struct{
	BYTE sUserName[NAME_LEN];		/* 用户名 */
	BYTE sPassword[PASSWD_LEN];		/* 密码 */
	DWORD dwLocalRight[MAX_RIGHT];	/* 权限 */
									/*数组0: 本地控制云台*/
									/*数组1: 本地手动录象*/
									/*数组2: 本地回放*/
									/*数组3: 本地设置参数*/
									/*数组4: 本地查看状态、日志*/
									/*数组5: 本地高级操作(升级，格式化，重启，关机)*/
	DWORD dwRemoteRight[MAX_RIGHT];	/* 权限 */
									/*数组0: 远程控制云台*/
									/*数组1: 远程手动录象*/
									/*数组2: 远程回放*/
									/*数组3: 远程设置参数*/
									/*数组4: 远程查看状态、日志*/
									/*数组5: 远程高级操作(升级，格式化，重启，关机)*/
									/*数组6: 远程发起语音对讲*/
									/*数组7: 远程预览*/
									/*数组8: 远程请求报警上传、报警输出*/
									/*数组9: 远程控制，本地输出*/
									/*数组10: 远程控制串口*/
	char sUserIP[16];					/* 用户IP地址(为0时表示允许任何地址) */
	BYTE byMACAddr[MACADDR_LEN];		/* 物理地址 */
}NET_DVR_USER_INFO,*LPNET_DVR_USER_INFO;

typedef struct{
	DWORD dwSize;
	NET_DVR_USER_INFO struUser[MAX_USERNUM];
}NET_DVR_USER,*LPNET_DVR_USER;

//DVR用户参数扩展
typedef struct{
	BYTE sUserName[NAME_LEN];		/* 用户名 */
	BYTE sPassword[PASSWD_LEN];		/* 密码 */
	DWORD dwLocalRight[MAX_RIGHT];	/* 权限 */
									/*数组0: 本地控制云台*/
									/*数组1: 本地手动录象*/
									/*数组2: 本地回放*/
									/*数组3: 本地设置参数*/
									/*数组4: 本地查看状态、日志*/
									/*数组5: 本地高级操作(升级，格式化，重启，关机)*/
	DWORD dwLocalPlaybackRight;		/* 本地可以回放的通道 bit0 -- channel 1*/
	DWORD dwRemoteRight[MAX_RIGHT];	/* 权限 */
									/*数组0: 远程控制云台*/
									/*数组1: 远程手动录象*/
									/*数组2: 远程回放 */
									/*数组3: 远程设置参数*/
									/*数组4: 远程查看状态、日志*/
									/*数组5: 远程高级操作(升级，格式化，重启，关机)*/
									/*数组6: 远程发起语音对讲*/
									/*数组7: 远程预览*/
									/*数组8: 远程请求报警上传、报警输出*/
									/*数组9: 远程控制，本地输出*/
									/*数组10: 远程控制串口*/
	DWORD dwNetPreviewRight;		/* 远程可以预览的通道 bit0 -- channel 1*/
	DWORD dwNetPlaybackRight;		/* 远程可以回放的通道 bit0 -- channel 1*/
	char sUserIP[16];				/* 用户IP地址(为0时表示允许任何地址) */
	BYTE byMACAddr[MACADDR_LEN];	/* 物理地址 */
}NET_DVR_USER_INFO_EX,*LPNET_DVR_USER_INFO_EX;

typedef struct{
	DWORD dwSize;
	NET_DVR_USER_INFO_EX struUser[MAX_USERNUM];
}NET_DVR_USER_EX,*LPNET_DVR_USER_EX;

//DVR异常参数
typedef struct{
	DWORD dwSize;
	NET_DVR_HANDLEEXCEPTION struExceptionHandleType[MAX_EXCEPTIONNUM];
 	/*数组0-盘满,1- 硬盘出错,2-网线断,3-局域网内IP 地址冲突,4-非法访问, 9-输入/输出视频制式不匹配*/
}NET_DVR_EXCEPTION,*LPNET_DVR_EXCEPTION;

typedef struct
{
	char sFileName[100];//文件名
	NET_DVR_TIME struStartTime;//文件的开始时间
	NET_DVR_TIME struStopTime;//文件的结束时间
	DWORD dwFileSize;//文件的大小
}NET_DVR_FIND_DATA,*LPNET_DVR_FIND_DATA;

typedef struct tagFINDDATA_INTER
{
	char sFileName[100];//文件名
	NET_DVR_TIME struStartTime;//文件的开始时间
	NET_DVR_TIME struStopTime;//文件的结束时间
	DWORD dwFileSize;//文件的大小
	char sCardNum[32];
}NET_DVR_FINDDATA_INTER,*LPNET_DVR_FINDDATA_INTER;

typedef struct {
	BYTE byRecordStatic; //通道是否在录像,0-不录像,1-录像
	BYTE bySignalStatic; //连接的信号状态,0-正常,1-异常
	BYTE byHardwareStatic;//通道硬件状态,0-正常,1-异常,例如DSP死掉
	char reservedData;
	DWORD dwBitRate;//实际码率
	DWORD dwLinkNum;//客户端连接的个数
	DWORD dwClientIP[MAX_LINK];//客户端的IP地址
}NET_DVR_CHANNELSTATE,*LPNET_DVR_CHANNELSTATE;

typedef struct {
	DWORD dwVolume;//硬盘的容量
	DWORD dwFreeSpace;//硬盘的剩余空间
	DWORD dwHardDiskStatic; //硬盘的状态,按位:1-休眠,2-不正常
}NET_DVR_DISKSTATE,*LPNET_DVR_DISKSTATE;

typedef struct{
	DWORD dwDeviceStatic; 	//设备的状态,0-正常,1-CPU占用率太高,超过85%,2-硬件错误,例如串口死掉
	NET_DVR_DISKSTATE  struHardDiskStatic[MAX_DISKNUM];
	NET_DVR_CHANNELSTATE struChanStatic[MAX_CHANNUM];//通道的状态
	BYTE  byAlarmInStatic[MAX_ALARMIN]; //报警端口的状态,0-没有报警,1-有报警
	BYTE  byAlarmOutStatic[MAX_ALARMOUT]; //报警输出端口的状态,0-没有输出,1-有报警输出
	DWORD  dwLocalDisplay;//本地显示状态,0-正常,1-不正常
}NET_DVR_WORKSTATE,*LPNET_DVR_WORKSTATE;

//DVR日志
/* 报警 */
//主类型
#define MAJOR_ALARM				0x1
//次类型
#define MINOR_ALARM_IN			0x1		/* 报警输入 */
#define MINOR_ALARM_OUT			0x2		/* 报警输出 */
#define MINOR_MOTDET_START		0x3		/* 移动侦测报警开始 */
#define MINOR_MOTDET_STOP		0x4		/* 移动侦测报警结束 */
#define MINOR_HIDE_ALARM_START	0x5		/* 遮挡报警开始 */
#define MINOR_HIDE_ALARM_STOP	0x6		/* 遮挡报警结束 */

/* 异常 */
//主类型
#define MAJOR_EXCEPTION			0x2
//次类型
#define MINOR_VI_LOST			0x21	/* 信号丢失 */
#define MINOR_ILLEGAL_ACCESS	0x22	/* 非法访问 */
#define MINOR_HD_FULL			0x23	/* 硬盘满 */
#define MINOR_HD_ERROR		    0x24	/* 硬盘错误 */
#define MINOR_DCD_LOST			0x25	/* MODEM 掉线 */
#define MINOR_IP_CONFLICT		0x26	/* IP地址冲突 */
#define MINOR_NET_BROKEN		0x27	/* 网线断 */

/* 操作 */
//主类型
#define MAJOR_OPERATION			0x3
//次类型
#define MINOR_START_DVR			0x41	/* 开机 */
#define MINOR_STOP_DVR			0x42	/* 关机 */
#define MINOR_STOP_ABNORMAL		0x43	/* 非法关机 */

#define MINOR_LOCAL_LOGIN		0x50	/* 本地登陆 */
#define MINOR_LOCAL_LOGOUT		0x51	/* 本地注销登陆 */
#define MINOR_LOCAL_CFG_PARM	0x52	/* 本地配置参数 */
#define MINOR_LOCAL_PLAYBYFILE	0x53	/* 本地按文件回放 */
#define MINOR_LOCAL_PLAYBYTIME	0x54	/* 本地按时间回放 */
#define MINOR_LOCAL_START_REC	0x55	/* 本地开始录像 */
#define MINOR_LOCAL_STOP_REC	0x56	/* 本地停止录像 */
#define MINOR_LOCAL_PTZCTRL		0x57	/* 本地云台控制 */
#define MINOR_LOCAL_PREVIEW		0x58	/* 本地预览 */
#define MINOR_LOCAL_MODIFY_TIME	0x59	/* 本地修改时间 */
#define MINOR_LOCAL_UPGRADE		0x5a	/* 本地升级 */
#define MINOR_LOCAL_COPYFILE	0x5b	/* 本地备份文件 */

#define MINOR_REMOTE_LOGIN		0x70	/* 远程登录 */
#define MINOR_REMOTE_LOGOUT		0x71	/* 远程注销登陆 */
#define MINOR_REMOTE_START_REC	0x72	/* 远程开始录像 */
#define MINOR_REMOTE_STOP_REC	0x73	/* 远程停止录像 */
#define MINOR_START_TRANS_CHAN	0x74	/* 开始透明传输 */
#define MINOR_STOP_TRANS_CHAN	0x75	/* 停止透明传输 */
#define MINOR_REMOTE_GET_PARM	0x76	/* 远程获得参数 */
#define MINOR_REMOTE_CFG_PARM	0x77	/* 远程配置参数 */
#define MINOR_REMOTE_GET_STATUS 0x78	/* 远程获得状态 */
#define MINOR_REMOTE_ARM		0x79	/* 远程布防 */
#define MINOR_REMOTE_DISARM		0x7a	/* 远程撤防 */
#define MINOR_REMOTE_REBOOT		0x7b	/* 远程重启 */
#define MINOR_START_VT			0x7c	/* 开始语音对讲 */
#define MINOR_STOP_VT			0x7d	/* 停止语音对讲 */
#define MINOR_REMOTE_UPGRADE	0x7e	/* 远程升级 */
#define MINOR_REMOTE_PLAYBYFILE	0x7f	/* 远程按文件回放 */
#define MINOR_REMOTE_PLAYBYTIME	0x80	/* 远程按时间回放 */
#define MINOR_REMOTE_PTZCTRL	0x81	/* 远程云台控制 */

typedef struct {
	NET_DVR_TIME strLogTime;
	DWORD	dwMajorType;	//主类型 1-报警; 2-异常; 3-操作; 0xff-全部
	DWORD	dwMinorType;//次类型 0xff-全部;
	BYTE	sPanelUser[MAX_NAMELEN]; //操作面板的用户名
	BYTE	sNetUser[MAX_NAMELEN];//网络操作的用户名
	char	sRemoteHostAddr[16];//远程主机地址
	DWORD	dwParaType;//参数类型
	DWORD	dwChannel;//通道号
	DWORD	dwDiskNumber;//硬盘号
	DWORD	dwAlarmInPort;//报警输入端口
	DWORD	dwAlarmOutPort;//报警输出端口
}NET_DVR_LOG,*LPNET_DVR_LOG;

typedef struct {
	char sRedirectorIP[16];	// 转发服务器IP地址
	WORD wRedirectorPort;	//端口号
}NET_DVR_REDIRECTORINFO, *LPNET_DVR_REDIRECTORINFO;

typedef struct{
	char Output[MAX_ALARMOUT];
}NET_DVR_ALARMOUTSTATUS,*LPNET_DVR_ALARMOUTSTATUS;

typedef struct{
	DWORD dwSize;
	DWORD dwYear;
	DWORD dwMonth;
	DWORD dwDay;
	DWORD dwHour;
	DWORD dwMinute;
	DWORD dwSecond;
	BYTE DeviceName[24];
	DWORD dwChannelNumer;
	BYTE CardNumber[32];
	char cTradeType[12];
	DWORD dwCash;
}NET_DVR_TRADEINFO,*LPNET_DVR_TRADEINFO;

//ATM TYPE
#define NCR		0
#define DIEBOLD	1
#define WINCOR_NIXDORF	2
#define SIEMENS	3
#define OLIVETTI	4
#define FUJITSU	5
#define HITACHI	6
#define SMI		7
#define IBM		8
#define BULL	9
#define YiHua	10
#define LiDe	11
#define GDYT	12
#define Mini_Banl	13
#define GuangLi	14
#define DongXin	15
#define ChenTong	16
#define NanTian	17
#define XiaoXing	18
#define GZYY	19
#define QHTLT	20

/*帧格式*/
typedef struct{
	BYTE code[12];		/* 代码 */
}NET_DVR_FRAMETYPECODE;

typedef struct{
	DWORD dwSize;
	char sATMIP[16];						/* ATM IP地址 */
	DWORD dwATMType;						/* ATM类型 */
	DWORD dwInputMode;						/* 输入方式*/
									/*0-网络侦听 1-网络接收 2-串口直接输入 3-串口ATM命令输入*/
	DWORD dwFrameSignBeginPos;              /* 报文标志位的起始位置*/
	DWORD dwFrameSignLength;				/* 报文标志位的长度 */
	BYTE  byFrameSignContent[12];			/* 报文标志位的内容 */
	DWORD dwCardLengthInfoBeginPos;			/* 卡号长度信息的起始位置 */
	DWORD dwCardLengthInfoLength;			/* 卡号长度信息的长度 */
	DWORD dwCardNumberInfoBeginPos;			/* 卡号信息的起始位置 */
	DWORD dwCardNumberInfoLength;			/* 卡号信息的长度 */
	DWORD dwBusinessTypeBeginPos;           /* 交易类型的起始位置 */
	DWORD dwBusinessTypeLength;				/* 交易类型的长度 */
	NET_DVR_FRAMETYPECODE frameTypeCode[10];/* 类型 */
}NET_DVR_FRAMEFORMAT,*LPNET_DVR_FRAMEFORMAT;

//时区和夏时制
typedef struct
{
	DWORD dwMonth;		//月
	DWORD dwWeekNo;		//第几周
	DWORD dwWeekDate;	//星期几
	DWORD dwHour;		//小时
	DWORD dwMin;		//分
}NET_DVR_TIMEPOINT;

typedef struct
{
	DWORD dwSize;
	DWORD dwZoneIndex;			//0-PST; 1-MST; 2-CST; 3-EST; 4-HST; 5-AST; 6-AKST;
	char csZone[12];			//时区
	DWORD dwEnableDST;		//是否启用夏时制 0－不启用 1－启用
	DWORD dwReserve;		//保留(选择按星期还是按月)
	NET_DVR_TIMEPOINT struBeginPoint;	//夏时制开始时间
	NET_DVR_TIMEPOINT struEndPoint;	//夏时制停止时间
}NET_DVR_ZONEANDDST, *LPNET_DVR_ZONEANDDST;

//DS-6001D/F 2005-06-29
/*解码设备控制码定义*/
#define NET_DEC_STARTDEC		1
#define NET_DEC_STOPDEC			2
#define NET_DEC_STOPCYCLE		3
#define NET_DEC_CONTINUECYCLE	4
/*连接的通道配置*/
typedef struct {
	char sDVRIP[16];				/* DVR IP地址 */
	WORD wDVRPort;			 		/* 端口号 */
	BYTE sUserName[NAME_LEN];		/* 用户名 */
	BYTE sPassword[PASSWD_LEN];		/* 密码 */
	BYTE byChannel;					/* 通道号 */
	BYTE byLinkMode;				/* 连接模式 */
	BYTE byLinkType;				/* 连接类型 0－主码流 1－子码流 */
}NET_DVR_DECCHANINFO, *LPNET_DVR_DECCHANINFO;

/*每个解码通道的配置*/
typedef struct {
	BYTE	byPoolChans;			/*每路解码通道上的循环通道数量, 最多4通道 0表示没有解码*/
	NET_DVR_DECCHANINFO struchanConInfo[MAX_DECPOOLNUM];
	BYTE	byEnablePoll;			/*是否轮巡 0-否 1-是*/
	BYTE	byPoolTime;				/*轮巡时间 0-保留 1-10秒 2-15秒 3-20秒 4-30秒 5-45秒 6-1分钟 7-2分钟 8-5分钟 */
}NET_DVR_DECINFO, *LPNET_DVR_DECINFO;

/*整个设备解码配置*/
typedef struct {
	DWORD	dwSize;
	DWORD	dwDecChanNum; 		/*解码通道的数量*/
	NET_DVR_DECINFO struDecInfo[MAX_DECNUM];
}NET_DVR_DECCFG, *LPNET_DVR_DECCFG;
//2005-08-01
/* 解码设备透明通道设置 */
typedef struct {
	DWORD dwEnableTransPort;	/* 是否启动透明通道 0－不启用 1－启用*/
	char sDecoderIP[16];		/* DVR IP地址 */
	WORD wDecoderPort;			/* 端口号 */
	WORD wDVRTransPort;			/* 配置前端DVR是从485/232输出，1表示232串口,2表示485串口 */
	char cReserve[4];
}NET_DVR_PORTINFO, *LPNET_DVR_PORTINFO;

typedef struct {
	DWORD dwSize;
	NET_DVR_PORTINFO struTransPortInfo[MAX_TRANSPARENTNUM]; /* 数组0表示232 数组1表示485 */
}NET_DVR_PORTCFG, *LPNET_DVR_PORTCFG;

/* 控制网络文件回放 */
typedef struct {
	DWORD dwSize;
	char sDecoderIP[16];		/* DVR IP地址 */
	WORD wDecoderPort;			/* 端口号 */
	WORD wLoadMode;				/* 回放下载模式 1－按名字 2－按时间 */
	union
	{
		BYTE byFile[100];		/* 回放的文件名 */
		struct
		{
			DWORD dwChannel;
			BYTE sUserName[NAME_LEN];	/*请求视频用户名*/
			BYTE sPassword[PASSWD_LEN];	/* 密码 */
			NET_DVR_TIME struStartTime;	/* 按时间回放的开始时间 */
			NET_DVR_TIME struStopTime;	/* 按时间回放的结束时间 */
		}bytime;
	}mode_size;
}NET_DVR_PLAYREMOTEFILE,*LPNET_DVR_PLAYREMOTEFILE;

/*当前设备解码连接状态*/
typedef struct {
	DWORD dwWorkType;		/*工作方式：1：轮巡、2：动态连接解码、3：文件回放下载 4：按时间回放下载*/
	char sDVRIP[16];		/*连接的设备ip*/
	WORD wDVRPort;			/*连接端口号*/
	BYTE byChannel;			/* 通道号 */
	BYTE byLinkMode;		/* 连接模式 */
	DWORD	dwLinkType;		/*连接类型 0－主码流 1－子码流*/
	union
	{
		struct
		{
			BYTE sUserName[NAME_LEN];	/*请求视频用户名*/
			BYTE sPassword[PASSWD_LEN];	/* 密码 */
			char cReserve[52];
		}userInfo;
		struct
		{
			BYTE   fileName[100];
		}fileInfo;
		struct
		{
			DWORD	dwChannel;
			BYTE	sUserName[NAME_LEN];	/*请求视频用户名*/
			BYTE	sPassword[PASSWD_LEN];	/* 密码 */
			NET_DVR_TIME struStartTime;		/* 按时间回放的开始时间 */
			NET_DVR_TIME struStopTime;		/* 按时间回放的结束时间 */
		}timeInfo;
	}objectInfo;
}NET_DVR_DECCHANSTATUS, *LPNET_DVR_DECCHANSTATUS;

typedef struct {
	DWORD   dwSize;
	NET_DVR_DECCHANSTATUS struDecState[MAX_DECNUM];
}NET_DVR_DECSTATUS, *LPNET_DVR_DECSTATUS;

//叠加字符
typedef struct
{
	WORD wShowString;				// 预览的图象上是否显示字符,0-不显示,1-显示 区域大小704*576,单个字符的大小为32*32
	WORD wStringSize;				/* 该行字符的长度，不能大于44个字符 */
	WORD wShowStringTopLeftX;		/* 字符显示位置的x坐标 */
	WORD wShowStringTopLeftY;		/* 字符名称显示位置的y坐标 */
	char sString[44];				/* 要显示的字符内容 */
}NET_DVR_SHOWSTRINGINFO, *LPNET_DVR_SHOWSTRINGINFO;

//叠加字符
typedef struct
{
	DWORD dwSize;
	NET_DVR_SHOWSTRINGINFO struStringInfo[MAX_STRINGNUM];				/* 要显示的字符内容 */
}NET_DVR_SHOWSTRING, *LPNET_DVR_SHOWSTRING;

/* ftp 上传参数*/
typedef struct tagFTPCFG
{
	DWORD	dwSize;
	DWORD	dwEnableFTP;			/*是否启动ftp上传功能*/
	char	sFTPIP[16];				/*ftp 服务器*/
	DWORD	dwFTPPort;				/*ftp端口*/
	BYTE	sUserName[NAME_LEN];	/*用户名*/
	BYTE	sPassword[PASSWD_LEN];	/*密码*/
	DWORD	dwDirLevel;	/*0 = 不使用目录结构，直接保存在根目录,1 = 使用1级目录,2=使用2级目录*/
	WORD 	wTopDirMode;	/* 0x1 = 使用设备名,0x2 = 使用设备号,0x3 = 使用设备ip地址*/
	WORD 	wSubDirMode;	/* 0x4 = 使用通道名,0x5 = 使用通道号*/
	BYTE 	reservedData[24];
}NET_DVR_FTPCFG, *LPNET_DVR_FTPCFG;

/*可用来命名图片的相关元素 */
#define PICNAME_ITEM_DEV_NAME 	1
#define PICNAME_ITEM_DEV_NO 	2
#define PICNAME_ITEM_DEV_IP 	3
#define PICNAME_ITEM_CHAN_NAME 	4
#define PICNAME_ITEM_CHAN_NO 	5
#define PICNAME_ITEM_TIME 		6
#define PICNAME_ITEM_CARDNO		7
#define PICNAME_MAXITEM 		15

typedef struct tagPICNAME
{
	BYTE 	byItemOrder[PICNAME_MAXITEM];	/*	桉数组定义文件命名的规则 */
	BYTE 	byDelimiter;		/*分隔符，一般为'_'*/
}NET_DVR_PICTURE_NAME, *LPNET_DVR_PICTURE_NAME;
//图片质量
typedef struct tagJPEGPARA
{
	WORD	wPicSize;				/* 0=CIF, 1=QCIF, 2=D1 */
	WORD	wPicQuality;			/* 图片质量系数 0-最好 1-较好 2-一般 */
}NET_DVR_JPEGPARA, *LPNET_DVR_JPEGPARA;

/* 串口抓图设置*/
typedef struct tagSERIALCAPPARA
{
	BYTE	byStrFlag;	/*串口数据开始符*/
	BYTE 	byEndFlag;	/*结束符*/
	WORD	wCardIdx;	/*卡号相对起始位*/
	DWORD 	dwCardLen;	/*卡号长度*/
	DWORD   dwTriggerPicChans;	/*所触发的通道号，按位，从第1位开始计，即0x2表示第一通道*/
}NET_DVR_SERIAL_CATCHPIC_PARA, *LPNET_DVR_SERIAL_CATCHPIC_PARA;

typedef struct tagJPEGCFG
{
	DWORD	dwSize;
	NET_DVR_JPEGPARA struJpegPara[MAX_CHANNUM];	/*每个通道的图像参数*/
	WORD	wBurstMode;							/*抓图方式,按位设置.0x1=报警输入触发，0x2=移动侦测触发 0x4=232触发，0x8=485触发，0x10=网络触发*/
	WORD	wUploadInterval;					/*图片上传间隔(秒)[0,65535]*/
	NET_DVR_PICTURE_NAME 	struPicNameRule;	/* 图片命名规则 */
	BYTE	bySaveToHD;		/*是否保存到硬盘*/
	BYTE	res1;
	WORD	wCatchInterval;		/*抓图间隔(毫秒)[0,65535]*/
	BYTE	res2[12];
	NET_DVR_SERIAL_CATCHPIC_PARA struRs232Cfg;
	NET_DVR_SERIAL_CATCHPIC_PARA struRs485Cfg;
	DWORD dwTriggerPicTimes[MAX_CHANNUM];	/* 每个通道一次触发拍照次数 */
	DWORD dwAlarmInPicChanTriggered[MAX_ALARMIN]; /*报警触发抓拍通道,按位设置，从第1位开始*/
}NET_DVR_JPEGCFG, *LPNET_DVR_JPEGCFG;

typedef struct tagGetJpeg
{
	DWORD dwReturn;		/*是否直接返回图片数据*/
	DWORD dwUploadFtp;	/*是否上传Ftp服务器*/
	DWORD dwSaveHd;		/*是否保存到设备硬盘*/
	char sImageName[PATHNAME_LEN];	/*自定义的生成图片文件名*/
	char sOsdStr[16];	/*需要叠加在图片上的OSD字符串*/
	WORD wOsdLen;		/*OSD字符串长度*/
}NET_DVR_GETJPEG, *LPNET_DVR_GETJPEG;

typedef struct tagFIND_PICTURE
{
	char sFileName[100];//图片名
	NET_DVR_TIME struTime;//图片的时间
	DWORD dwFileSize;//图片的大小
	char sCardNum[32];	//卡号
}NET_DVR_FIND_PICTURE,*LPNET_DVR_FIND_PICTURE;


typedef struct tagNTPPARA{
	BYTE sNTPServer[64];   /* Domain Name or IP addr of NTP server */
	WORD wInterval;		 /* adjust time interval(hours) */
	BYTE byEnableNTP;    /* enable NPT client 0-no，1-yes*/
	signed char cTimeDifferenceH; /* 与国际标准时间的时差 -12 ... +13 */
	signed char cTimeDifferenceM;
	BYTE res[11];
}NET_DVR_NTPPARA, *LPNET_DVR_NTPPARA;

typedef struct tagDDNSPARA{
	BYTE sUsername[NAME_LEN];  /* DDNS账号用户名/密码 */
	BYTE sPassword[PASSWD_LEN];
	BYTE sDomainName[64];       /* 域名 */
	BYTE byEnableDDNS;			/*是否应用 0-否，1-是*/
	BYTE res[15];
}NET_DVR_DDNSPARA, *LPNET_DVR_DDNSPARA;

typedef struct tagEMAILPARA{
	BYTE sUsername[64];  /* 邮件账号/密码 */
	BYTE sPassword[64];
	BYTE sSmtpServer[64];
	BYTE sPop3Server[64];
	BYTE sMailAddr[64];   /* email */
	BYTE sEventMailAddr1[64];  /* 上传报警/异常等的email */
	BYTE sEventMailAddr2[64];
	BYTE res[16];
}NET_DVR_EMAILPARA, *LPNET_DVR_EMAILPARA;

typedef struct tagNETAPPCFG{
	DWORD  dwSize;
	char  sDNSIp[16];                /* DNS服务器地址 */
	NET_DVR_NTPPARA  struNtpClientParam;      /* NTP参数 */
	NET_DVR_DDNSPARA struDDNSClientParam;     /* DDNS参数 */
	NET_DVR_EMAILPARA struEmailParam;         /* EMAIL参数 */
}NET_DVR_NETAPPCFG, *LPNET_DVR_NETAPPCFG;

typedef struct tagAUXOUT{
	DWORD dwSize;
	DWORD dwAlarmOutChan;                       	/* 选择报警弹出大画面的输出通道: 0:主输出/1:辅1/2:辅2/3:辅3/4:辅4 */
	DWORD dwAlarmChanSwitchTime;                	/* 报警通道切换时间：1:1秒 - 10:10秒 */
	DWORD dwAuxSwitchTime[MAX_AUXOUT];		/* 辅助输出切换时间: 0-不切换,1-5s,2-10s,3-20s,4-30s,5-60s,6-120s,7-300s */
	BYTE  byAuxOrder[MAX_AUXOUT][MAX_WINDOW];	/* 辅助输出预览顺序, 0xff表示相应的窗口不预览 */
}NET_DVR_AUXOUTCFG, *LPNET_DVR_AUXOUTCFG;

typedef struct tag_NFSCFG{
	DWORD  dwSize;
	struct{
		char sNfsHostIPAddr[16];
		BYTE sNfsDirectory[PATHNAME_LEN];        // PATHNAME_LEN = 128
	}struNfsDiskParam[MAX_NFS_DISK];
}NET_DVR_NFSCFG, *LPNET_DVR_NFSCFG;


//上海优网通 2006-12-19  by cxh  前端参数设置
typedef struct tagMANAGECFGEX{
	DWORD dwSize;
	BYTE sFrontID[NAME_LEN]; /* 前端ID */
	BYTE sRegPass[PASSWD_LEN]; /* 注册密码 */
	char sHBHostIp[16]; /* 心跳管理主机网络地址 */
	WORD wHeartBeatPort; /* 管理主机心跳倾听端口 */
	DWORD dwAroundNum; /* 连接的外围设备数量，不超过24*/
	BYTE sAroundID[24][NAME_LEN]; /* 外围设备ID */
	BYTE sChanID[MAX_CHANNUM][NAME_LEN]; /* 通道ID */
	BYTE byChanEnable[MAX_CHANNUM]; /* 通道是否接入 */
}NET_DVR_MANAGECFG_EX, *LPNET_DVR_MANAGECFG_EX;

typedef struct tagPOINT_FRAME
{
      int xTop; // 方框起始点的x坐标
      int yTop; // 方框结束点的y坐标
      int xBottom; // 方框结束点的x坐标
      int yBottom; //方框结束点的y坐标
      int bCounter; //保留
}NET_DVR_POINT_FRAME, *LPNET_DVR_POINT_FRAME;


typedef struct tagCRUISE_RET{
	struct{
		BYTE	PresetNum;	//预置点
		BYTE	Dwell;		//停留时间
		BYTE	Speed;		//速度
		BYTE	Reserve;	//保留
	}struCruisePoint[32];			//最大支持32个巡航点
}NET_DVR_CRUISE_RET, *LPNET_DVR_CRUISE_RET;

NET_DVR_API BOOL   NET_DVR_Init();
NET_DVR_API BOOL   NET_DVR_Cleanup();
NET_DVR_API BOOL   NET_DVR_SetDVRMessCallBack(BOOL (  *fMessCallBack)(int lCommand,char *sDVRIP,char *pBuf,DWORD dwBufLen));
NET_DVR_API BOOL   NET_DVR_SetDVRMessageCallBack(BOOL (  *fMessageCallBack)(int lCommand,char *sDVRIP,char *pBuf,DWORD dwBufLen, void* lpUser), void* lpUser);
NET_DVR_API BOOL   NET_DVR_SetDVRMessCallBack_EX(BOOL (  *fMessCallBack_EX)(int lCommand,int lUserID,char *pBuf,DWORD dwBufLen));
NET_DVR_API BOOL   NET_DVR_SetConnectTime(DWORD dwWaitTime,DWORD dwTryTimes);
NET_DVR_API DWORD   NET_DVR_GetSDKVersion();
NET_DVR_API BOOL   NET_DVR_StartListen(char *sLocalIP,WORD wLocalPort);
NET_DVR_API BOOL   NET_DVR_StopListen();
NET_DVR_API int   NET_DVR_Login(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_DVR_DEVICEINFO lpDeviceInfo);
NET_DVR_API BOOL   NET_DVR_Logout(int lUserID);
NET_DVR_API DWORD   NET_DVR_GetLastError();
NET_DVR_API BOOL   NET_DVR_GetDVRIPByResolveSvr(char *sServerIP, WORD wServerPort, BYTE *sDVRName,WORD wDVRNameLen,BYTE *sDVRSerialNumber,WORD wDVRSerialLen,char* sGetIP);
//图像预览
NET_DVR_API int   NET_DVR_RealPlay(int lUserID,LPNET_DVR_CLIENTINFO lpClientInfo);
NET_DVR_API BOOL   NET_DVR_StopRealPlay(int lRealHandle);
NET_DVR_API BOOL   NET_DVR_RealPlayPause(int lRealHandle);
NET_DVR_API BOOL   NET_DVR_RealPlayRestart(int lRealHandle, PLAYRECT *hPlayWnd);
//视频参数是索引值 1-10
NET_DVR_API BOOL   NET_DVR_ClientSetVideoEffect(int lRealHandle,DWORD dwBrightValue,DWORD dwContrastValue, DWORD dwSaturationValue,DWORD dwHueValue);
NET_DVR_API BOOL   NET_DVR_ClientGetVideoEffect(int lRealHandle,DWORD *pBrightValue,DWORD *pContrastValue, DWORD *pSaturationValue,DWORD *pHueValue);
NET_DVR_API BOOL   NET_DVR_SetPlayerBufNumber(int lRealHandle,DWORD dwBufNum);
NET_DVR_API BOOL   NET_DVR_ThrowBFrame(int lRealHandle,DWORD dwNum);
NET_DVR_API BOOL   NET_DVR_OpenSound(int lRealHandle);
NET_DVR_API BOOL   NET_DVR_CloseSound();
NET_DVR_API BOOL   NET_DVR_Volume(int lRealHandle,WORD wVolume);
NET_DVR_API BOOL   NET_DVR_SaveRealData(int lRealHandle,char *sFileName);
NET_DVR_API BOOL   NET_DVR_StopSaveRealData(int lRealHandle);
NET_DVR_API BOOL   NET_DVR_SetRealDataCallBack(int lRealHandle,void(  *fRealDataCallBack) (int lRealHandle, DWORD dwDataType, char *pBuffer,DWORD dwBufSize,void* pUser),void* pUser);
NET_DVR_API BOOL   NET_DVR_CapturePicture(int lRealHandle,char *sPicFileName);
//云台控制
NET_DVR_API BOOL   NET_DVR_GetPTZCtrl(int lRealHandle);
NET_DVR_API BOOL   NET_DVR_GetPTZCtrl_Other(int lUserID,int lChannel);
NET_DVR_API BOOL   NET_DVR_PTZControl(int lRealHandle,DWORD dwPTZCommand,DWORD dwStop);
NET_DVR_API BOOL   NET_DVR_PTZControl_Other(int lUserID,int lChannel,DWORD dwPTZCommand,DWORD dwStop);
NET_DVR_API BOOL   NET_DVR_TransPTZ(int lRealHandle,char *pPTZCodeBuf,DWORD dwBufSize);
NET_DVR_API BOOL   NET_DVR_TransPTZ_Other(int lUserID,int lChannel,char *pPTZCodeBuf,DWORD dwBufSize);
NET_DVR_API BOOL   NET_DVR_PTZPreset(int lRealHandle,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);
NET_DVR_API BOOL   NET_DVR_PTZPreset_Other(int lUserID,int lChannel,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);
NET_DVR_API BOOL   NET_DVR_PTZControlWithSpeed(int lRealHandle,DWORD dwPTZCommand, DWORD dwStop, DWORD dwSpeed);
NET_DVR_API BOOL   NET_DVR_PTZControlWithSpeed_Other(int lUserID,int lChannel,DWORD dwPTZCommand, DWORD dwStop, DWORD dwSpeed);
NET_DVR_API BOOL   NET_DVR_PTZControlWithSpeed_EX(int lRealHandle,DWORD dwPTZCommand, DWORD dwStop, DWORD dwSpeed);
NET_DVR_API BOOL   NET_DVR_PTZCruise(int lRealHandle,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);
NET_DVR_API BOOL   NET_DVR_PTZCruise_Other(int lUserID,int lChannel,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);
NET_DVR_API BOOL   NET_DVR_PTZCruise_EX(int lRealHandle,int dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);
NET_DVR_API BOOL   NET_DVR_PTZTrack(int lRealHandle,DWORD dwPTZTrackCmd);
NET_DVR_API BOOL   NET_DVR_PTZTrack_Other(int lUserID,int lChannel,DWORD dwPTZTrackCmd);
NET_DVR_API BOOL   NET_DVR_PTZTrack_EX(int lRealHandle,DWORD dwPTZTrackCmd);

//文件回放
NET_DVR_API int   NET_DVR_FindFile(int lUserID,int lChannel,DWORD dwFileType, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);
NET_DVR_API int   NET_DVR_FindNextFile(int lFindHandle,LPNET_DVR_FIND_DATA lpFindData);
NET_DVR_API BOOL   NET_DVR_FindClose(int lFindHandle);
NET_DVR_API int   NET_DVR_PlayBackByName(int lUserID,char *sPlayBackFileName, PLAYRECT *hWnd);
NET_DVR_API int   NET_DVR_PlayBackByTime(int lUserID,int lChannel, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime, PLAYRECT *hWnd);
NET_DVR_API BOOL   NET_DVR_PlayBackControl(int lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *lpOutValue);
NET_DVR_API BOOL   NET_DVR_StopPlayBack(int lPlayHandle);
NET_DVR_API BOOL   NET_DVR_SetPlayDataCallBack(int lPlayHandle,void(  *fPlayDataCallBack) (int lPlayHandle, DWORD dwDataType, char *pBuffer,DWORD dwBufSize,void* pUser),void* pUser);
NET_DVR_API BOOL   NET_DVR_PlayBackSaveData(int lPlayHandle,char *sFileName);
NET_DVR_API BOOL   NET_DVR_StopPlayBackSave(int lPlayHandle);
NET_DVR_API BOOL  NET_DVR_GetPlayBackOsdTime(int lPlayHandle, LPNET_DVR_TIME lpOsdTime);
NET_DVR_API BOOL   NET_DVR_PlayBackCaptureFile(int lPlayHandle,char *sFileName);
NET_DVR_API int   NET_DVR_GetFileByName(int lUserID,char *sDVRFileName,char *sSavedFileName);
NET_DVR_API int   NET_DVR_GetFileByTime(int lUserID,int lChannel, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime, char *sSavedFileName);
NET_DVR_API BOOL   NET_DVR_StopGetFile(int lFileHandle);
NET_DVR_API int   NET_DVR_GetDownloadPos(int lFileHandle);
//恢复默认值
NET_DVR_API BOOL   NET_DVR_RestoreConfig(int lUserID);
//保存参数
NET_DVR_API BOOL   NET_DVR_SaveConfig(int lUserID);
//重启
NET_DVR_API BOOL   NET_DVR_RebootDVR(int lUserID);
//关闭DVR
NET_DVR_API BOOL   NET_DVR_ShutDownDVR(int lUserID);
//升级
NET_DVR_API int   NET_DVR_Upgrade(int lUserID,char *sFileName);
NET_DVR_API int   NET_DVR_GetUpgradeState(int lUpgradeHandle);
NET_DVR_API BOOL   NET_DVR_CloseUpgradeHandle(int lUpgradeHandle);
//远程格式化硬盘
NET_DVR_API int   NET_DVR_FormatDisk(int lUserID,int lDiskNumber);
NET_DVR_API BOOL   NET_DVR_GetFormatProgress(int lFormatHandle,int *pCurrentFormatDisk,int *pCurrentDiskPos,int *pFormatStatic);
NET_DVR_API BOOL   NET_DVR_CloseFormatHandle(int lFormatHandle);
//报警
NET_DVR_API int   NET_DVR_SetupAlarmChan(int lUserID);
NET_DVR_API BOOL   NET_DVR_CloseAlarmChan(int lAlarmHandle);
NET_DVR_API BOOL   NET_DVR_GetAlarmOut(int lUserID,LPNET_DVR_ALARMOUTSTATUS lpAlarmOutState);
NET_DVR_API BOOL   NET_DVR_SetAlarmOut(int lUserID,int lAlarmOutPort,int lAlarmOutStatic);
//语音转发
NET_DVR_API int NET_DVR_StartVoiceCom(int lUserID, void( *fVoiceDataCallBack)(int lVoiceComHandle,char *pRecvDataBuffer,DWORD dwBufSize,void* pUser), void* pUser);
NET_DVR_API BOOL NET_DVR_VoiceComSendData(int lVoiceComHandle,char *pSendBuf,DWORD dwBufSize);
NET_DVR_API BOOL NET_DVR_StopVoiceCom(int lVoiceComHandle);
////////////////////////////////////////////////////////////
//透明通道设置
NET_DVR_API int   NET_DVR_SerialStart(int lUserID,int lSerialPort,void(  *fSerialDataCallBack)(int lSerialHandle,char *pRecvDataBuffer,DWORD dwBufSize,void* pUser),void* pUser);
NET_DVR_API BOOL   NET_DVR_SerialSend(int lSerialHandle, int lChannel, char *pSendBuf,DWORD dwBufSize);
NET_DVR_API BOOL   NET_DVR_SerialStop(int lSerialHandle);
NET_DVR_API BOOL   NET_DVR_SendTo232Port(int lUserID,char *pSendBuf,DWORD dwBufSize);
//远程控制本地显示
NET_DVR_API BOOL   NET_DVR_ClickKey(int lUserID,int lKeyIndex);
//远程控制设备端手动录像
NET_DVR_API BOOL   NET_DVR_StartDVRRecord(int lUserID,int lChannel,int lRecordType);
NET_DVR_API BOOL   NET_DVR_StopDVRRecord(int lUserID,int lChannel);

//服务器状态
NET_DVR_API BOOL   NET_DVR_GetDVRWorkState(int lUserID,LPNET_DVR_WORKSTATE lpWorkState);
//日志
NET_DVR_API int   NET_DVR_FindDVRLog(int lUserID,int lSelectMode, DWORD dwMajorType,DWORD dwMinorType, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);
NET_DVR_API int   NET_DVR_FindNextLog(int lLogHandle,LPNET_DVR_LOG lpLogData);
NET_DVR_API BOOL   NET_DVR_FindLogClose(int lLogHandle);
//参数设置
NET_DVR_API BOOL   NET_DVR_GetDVRConfig(int lUserID, DWORD dwCommand,int lChannel, void * lpOutBuffer,DWORD dwOutBufferSize,DWORD * lpBytesReturned);
NET_DVR_API BOOL   NET_DVR_SetDVRConfig(int lUserID, DWORD dwCommand,int lChannel, void * lpInBuffer,DWORD dwInBufferSize);
//以下为ATM专用
NET_DVR_API BOOL   NET_DVR_ClientGetframeformat(int lUserID, LPNET_DVR_FRAMEFORMAT lpFrameFormat);
NET_DVR_API BOOL   NET_DVR_ClientSetframeformat(int lUserID, LPNET_DVR_FRAMEFORMAT lpFrameFormat);
NET_DVR_API int   NET_DVR_FindFileByCard(int lUserID,int lChannel,DWORD dwFileType, BOOL bNeedCardNum, BYTE *sCardNumber, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);

/*2005.01.11 增加两个接口,Linux专有 */
NET_DVR_API BOOL NET_DVR_DrawAreaInit( INITINFO InitInfo );
NET_DVR_API BOOL NET_DVR_DrawAreaRelease( void );
NET_DVR_API BOOL NET_DVR_GetExceptionState( DWORD *dwState );
//2005-03-16 //cybasec
NET_DVR_API int NET_DVR_GetBMPByTime(int lUserID,int lChannel, LPNET_DVR_TIME lpTime, char *sFilename);
NET_DVR_API BOOL  NET_DVR_DisableLinkedClient(int lUserID,int lChannel, char *pClientIP);
NET_DVR_API BOOL  NET_DVR_EnableLinkedClient(int lUserID,int lChannel, char *pClientIP);
NET_DVR_API BOOL  NET_DVR_SetOEMInfo(int lUserID,void* lpOEMInfoBuf,DWORD dwOEMInfolen);
NET_DVR_API BOOL  NET_DVR_GetOEMInfo(int lUserID,void* lpOEMOutInfoBuf,DWORD dwOEMOutInfolen, DWORD* lpBytesReturned);
NET_DVR_API BOOL  NET_DVR_StartPanelKey(int lUserID);
NET_DVR_API BOOL  NET_DVR_StopPanelKey(int lUserID);
NET_DVR_API BOOL  NET_DVR_GetSerialNo(char *sDVRIP,WORD wDVRPort,char *sOEMInfo,DWORD dwInBufSize,char *sSerialNo,DWORD dwOutBufSize,DWORD* lpBytesReturned);
NET_DVR_API BOOL  NET_DVR_ResetPassword(char *sDVRIP,WORD wDVRPort,char *sInBuf,DWORD dwInBufSize);

//北京讯飞
NET_DVR_API BOOL  NET_DVR_MakeKeyFrame(int lUserID, int lChannel);
//SDK_V14
NET_DVR_API BOOL  NET_DVR_TransPTZ_EX(int lRealHandle,char *pPTZCodeBuf,DWORD dwBufSize);
NET_DVR_API BOOL  NET_DVR_PTZControl_EX(int lRealHandle,DWORD dwPTZCommand,DWORD dwStop);
NET_DVR_API BOOL  NET_DVR_PTZPreset_EX(int lRealHandle,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);
NET_DVR_API BOOL  NET_DVR_GetConfigFile(int lUserID, char *sFileName);
NET_DVR_API BOOL  NET_DVR_SetConfigFile(int lUserID, char *sFileName);
NET_DVR_API BOOL  NET_DVR_GetConfigFile_EX(int lUserID, char *sOutBuffer, DWORD dwOutSize);
NET_DVR_API BOOL  NET_DVR_SetConfigFile_EX(int lUserID, char *sInBuffer, DWORD dwInSize);

//6001D/F
NET_DVR_API BOOL  NET_DVR_SetDecInfo(int lUserID, int lChannel, LPNET_DVR_DECCFG lpDecoderinfo);
NET_DVR_API BOOL  NET_DVR_GetDecInfo(int lUserID, int lChannel, LPNET_DVR_DECCFG lpDecoderinfo);
NET_DVR_API BOOL  NET_DVR_SetDecTransPort(int lUserID, LPNET_DVR_PORTCFG lpTransPort);
NET_DVR_API BOOL  NET_DVR_GetDecTransPort(int lUserID, LPNET_DVR_PORTCFG lpTransPort);
NET_DVR_API BOOL  NET_DVR_DecPlayBackCtrl(int lUserID, int lChannel, DWORD dwControlCode, DWORD dwInValue,void *lpOutValue, LPNET_DVR_PLAYREMOTEFILE lpRemoteFileInfo);
NET_DVR_API BOOL  NET_DVR_StartDecSpecialCon(int lUserID, int lChannel, LPNET_DVR_DECCHANINFO lpDecChanInfo);
NET_DVR_API BOOL  NET_DVR_StopDecSpecialCon(int lUserID, int lChannel, LPNET_DVR_DECCHANINFO lpDecChanInfo);
NET_DVR_API BOOL  NET_DVR_DecCtrlDec(int lUserID, int lChannel, DWORD dwControlCode);
NET_DVR_API BOOL  NET_DVR_DecCtrlScreen(int lUserID, int lChannel, DWORD dwControl);
NET_DVR_API BOOL  NET_DVR_GetDecCurLinkStatus(int lUserID, int lChannel, LPNET_DVR_DECSTATUS lpDecStatus);
//capture jpeg file
NET_DVR_API BOOL  NET_DVR_CaptureJPEGPicture(int lUserID, int lChannel, LPNET_DVR_JPEGPARA lpJpegPara, char *sPicFileName);
NET_DVR_API BOOL  NET_DVR_CaptureJPEGPicture_EX(int lUserID, int lChannel, LPNET_DVR_GETJPEG lpGetJpeg,char *sJpegPicBuffer, DWORD dwPicSize,  DWORD *lpSizeReturned);

NET_DVR_API BOOL NET_DVR_SetValidIP(DWORD dwIPIndex);
NET_DVR_API BOOL NET_DVR_GetLocalIP(char IPstring[16][16], DWORD *pValidNum );

NET_DVR_API BOOL  NET_DVR_SetPIPMode(int lUserID, DWORD dwPIPMode);

NET_DVR_API BOOL  NET_DVR_SetATMPortCFG(int lUserID, WORD wATMPort);
NET_DVR_API BOOL  NET_DVR_GetATMPortCFG(int lUserID, WORD *lpOutATMPort);

NET_DVR_API BOOL  NET_DVR_SetScaleCFG(int lUserID, DWORD dwScale);
NET_DVR_API BOOL  NET_DVR_GetScaleCFG(int lUserID, DWORD *lpOutScale);

NET_DVR_API BOOL  NET_DVR_MakeKeyFrameSub(int lUserID, int lChannel);
NET_DVR_API BOOL  NET_DVR_TestDVRAlive(int lUserID);
NET_DVR_API BOOL  NET_DVR_CaptureJPEGPicture_NEW(int lUserID, int lChannel, LPNET_DVR_JPEGPARA lpJpegPara, char *sJpegPicBuffer, DWORD dwPicSize,  DWORD* lpSizeReturned);
NET_DVR_API BOOL  NET_DVR_PTZSelZoomIn(int lRealHandle, LPNET_DVR_POINT_FRAME pStruPointFrame);
NET_DVR_API BOOL  NET_DVR_GetPTZCruise(int lUserID,int lChannel,int lCruiseRoute, LPNET_DVR_CRUISE_RET lpCruiseRet);

#ifdef __cplusplus
}
#endif
#endif /* _HCNETSDK_H_ */
