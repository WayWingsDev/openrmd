
#ifndef LIBMODEL_H_
#define LIBMODEL_H_

#ifndef Int32
typedef int Int32;
typedef unsigned int UInt32;
typedef unsigned int * LPUInt32;
typedef short Int16;
typedef unsigned short UInt16;
#endif

#ifndef DWORD
typedef unsigned long	DWORD;
typedef DWORD*			LPDWORD;
#endif

#ifndef LONG
typedef long			LONG;
#endif

#ifndef WIN32
#define WORD	unsigned short
#define BOOL	int
#define TRUE	0x01
#define FALSE	0x00
#define BYTE	unsigned char
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
#ifndef NULL
#define NULL	0
#endif
#ifndef bool
#define bool (int)
#endif

#ifndef RECT
typedef struct  _RECT
{
	int left;
	int top;
	int right;
	int bottom;
} RECT;
#endif

#endif

#ifndef NAMESPACE_BEGIN
#define NAMESPACE_BEGIN
#define NAMESPACE_END
#endif

NAMESPACE_BEGIN

#ifdef WIN32

#ifdef RVNETSDK_EXPORTS
#define CLIENT_API  __declspec(dllexport) 
#else	
#define CLIENT_API  __declspec(dllimport)
#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#else	//linux

#define CLIENT_API	extern //"C"
#define CALL_METHOD
#define CALLBACK

#endif


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** constant define  [常量定义]
***********************************************************************/
#define RV_SERIALNO_LEN 		48		//max size of device serial number [设备序列号字符长度]
#define RV_MAX_DISKNUM 			32		//max number of disk [最大硬盘个数]
#define RV_MAX_SDCARDNUM		32		//max number of SD card [最大SD卡个数]
#define RV_MAX_BURNING_DEV_NUM	32		//max number of imprinting device [最大刻录设备个数]
#define RV_BURNING_DEV_NAMELEN	32		//max size of device name [刻录设备名字最大长度]
#define RV_MAX_LINK 			6		
#define RV_MAX_CHANNUM 			32		//max number of channel [最大通道个数]
#define RV_MAX_ALARMIN 			128		//max number of alarm-in [最大报警输入个数]
#define RV_MAX_ALARMOUT 		64		//max number of alarm-out [最大报警输出个数]

#define RV_MAX_RIGHT_NUM		256		//max number of usr authority [用户权限个数上限]
#define RV_MAX_GROUP_NUM		20		//max number of user group [用户组个数上限]
#define RV_MAX_USER_NUM			200		//max number of user [用户个数上限]
#define RV_RIGHT_NAME_LENGTH	32		//max size of authority name [权限名长度]
#define RV_USER_NAME_LENGTH		8		//max size of user name [用户名长度]
#define RV_USER_PSW_LENGTH		8		//max size of user password [用户密码长度]
#define RV_MEMO_LENGTH			32		//max size of memo [备注长度]
#define RV_N_SYS_CH				16
#define RV_N_SYS_CH_32			32

#define RV_MAX_STRING_LEN		128
#define RV_DEF_REALPLAY_BUF_NUM (3) 
#define RV_MIN_REALPLAY_BUF_NUM (1) 
#define RV_MAX_REALPLAY_BUF_NUM (50) 

//callback type of listen from device [侦听设备回调类型]
#define RV_DVR_SERIAL_RETURN 1   //the callback of sending serial number by device [设备发送序列号回调]
#define RV_DVR_DISCONNECT -1     //the callback of disconnect from device during verify period [验证期间设备断线回调]

//constant for overprint character on picture [通道画面字符叠加相关常量]
#define RV_MAX_STRING_LINE_LEN	6		//max six lines [最多六行]
#define RV_MAX_PER_STRING_LEN  20		//max length per line [每行最大长度]

//number of DDNS [DDNS数目定义]
#define MAX_DDNS_COUNT 16

//the types of alarm message callbacked, corresponding SDK_StartListen [回调报警信息类型，对应SDK_StartListen]
#define RV_COMM_ALARM			0x1100	//common alarm infomation (include:out-alarm, video lost, motion detect) [常规报警信息(包括外部报警，视频丢失，动态检测)]
#define RV_SHELTER_ALARM		0x1101	//video shelter alarm [视频遮挡报警]
#define RV_DISK_FULL_ALARM		0x1102	//disk full alarm [硬盘满报警]
#define RV_DISK_ERROR_ALARM		0x1103	//disk error alarm [硬盘故障报警]
#define RV_SOUND_DETECT_ALARM	0x1104	//audio detect alarm [音频检测报警]
#define RV_ALARM_DECODER_ALARM	0x1105	//decoder alarm [报警解码器报警]
#define RV_ALARM_NET_ALARM_IN	0x110E	//网络报警输入报警

//extended types of alarm message callabcked, corresponding SDK_StartListenEx [扩展回调报警信息类型，对应SDK_StartListenEx]
//seperate alarm types detailly [各报警类型详细分开]
#define RV_ALARM_ALARM_EX			0x2101	//out-alarm [外部报警]
#define RV_MOTION_ALARM_EX			0x2102	//motion detect alarm [动态检测报警]
#define RV_VIDEOLOST_ALARM_EX		0x2103	//video lost alarm [视频丢失报警]
#define RV_SHELTER_ALARM_EX			0x2104	//shelter alarm [遮挡报警]
#define RV_SOUND_DETECT_ALARM_EX	0x2105	//audio detect alarm [音频检测报警]
#define RV_DISKFULL_ALARM_EX		0x2106	//disk full alarm [硬盘满报警]
#define RV_DISKERROR_ALARM_EX		0x2107	//disk error alarm [坏硬盘报警]
#define RV_ENCODER_ALARM_EX			0x210A	//coder alarm [编码器报警]
#define RV_URGENCY_ALARM_EX			0x210B	//urgent alarm [紧急报警]
#define RV_WIRELESS_ALARM_EX		0x210C	//wireless alarm [无线报警]
#define RV_NEW_SOUND_DETECT_ALARM_EX 0x210D //new audio detect alarm, the struct reference to RV_NEW_SOUND_ALARM_STATE [新音频检测报警报警信息的结构体见RV_NEW_SOUND_ALARM_STATE]
#define RV_DECODER_ALARM_EX			0x210E	//decoder alarm [解码器报警]

#define RV_SAVIA_ALARM_TRACK		0x210F	//intelligent:track arithmatic alarm [智能：跟踪算法报警]
#define RV_SAVIA_ALARM_CROSSLINE	0x2110	//intelligent:cross-line arithmatic alarm [智能：越线算法报警]
#define RV_SAVIA_ALARM_CROSSNET		0x2111	//intelligent:invade arithmatic alarm [智能：入侵算法报警]
#define RV_SAVIA_ALARM_WANDER		0x2112	//intelligent:wander arithmatic alarm [智能：徘徊算法报警]
#define RV_SAVIA_ALARM_CONVERSE		0x2113	//intelligent:thrash arithmatic alarm [智能：逆行算法报警]
#define RV_SAVIA_ALARM_STATIC		0x2114	//intelligent:left alone arithmatic alarm [智能：遗留算法报警]
#define RV_SAVIA_ALARM_LOST			0x2115	//intelligent:lost arithmatic alarm [智能：遗失算法报警]
#define RV_SAVIA_ALARM_DAMAGE		0x2116	//intelligent:spray finishing arithmatic alarm [智能：喷涂算法报警]
#define RV_INTE_ALARM_SMOKEFIRE		0x2117	//intelligent:fireworks arithmatic alarm [智能：烟火算法报警]

#define RV_INTE_ALARM_RED_LEVEL_1	0x2118	//intelligent:red detect level-1 [智能：智能红色检测告警1档]
#define RV_INTE_ALARM_RED_LEVEL_2	0x2119	//intelligent:red detect level-2 [智能：智能红色检测告警2档]
#define RV_INTE_ALARM_RED_LEVEL_3	0x211a	//intelligent:red detect level-3 [智能：智能红色检测告警3档]
#define RV_INTE_ALARM_RED_LEVEL_4	0x211b	//intelligent:red detect level-4 [智能：智能红色检测告警4档]
#define RV_INTE_ALARM_RED_LEVEL_5	0x211c	//intelligent:red detect level-5 [智能：智能红色检测告警5档]
#define RV_INTE_ALARM_RED_LEVEL_6	0x211d	//intelligent:red detect level-6 [智能：智能红色检测告警6档]


#define RV_CONFIG_RESULT_EVENT_EX	0X3000  //the returned value code for modify configure, reference to RVDEV_SET_RESULT [修改配置的返回码返回结构见RVDEV_SET_RESULT]
#define RV_REBOOT_EVENT_EX			0x3001	//event of device reboot [设备重启事件]
#define RV_AUTO_TALK_START_EX		0x3002  //device start talk [设备主动开始语音对讲]
#define RV_AUTO_TALK_STOP_EX		0x3003  //device stop talk [设备主动停止语音对讲]

//interface params of query device status : query type used in SDK_QueryDevState [查询设备状态接口参数：查询类型 用于SDK_QueryDevState参数]
#define RV_DEVSTATE_COMM_ALARM		0x0001	//query common alarm (include:out-alarm, video lost, motion detect) [查询普通报警(包括外部报警，视频丢失，动态检测)]
#define RV_DEVSTATE_SHELTER_ALARM	0x0002	//query shelter alarm [查询遮挡报警]
#define RV_DEVSTATE_RECORDING		0x0003	//query record status [查询录象状态]
#define RV_DEVSTATE_DISK			0x0004	//query disk status [查询硬盘状态]
#define RV_DEVSTATE_RESOURCE		0x0005	//system resource status [系统资源状态]
#define RV_DEVSTATE_BITRATE			0x0006	//get channel bit-stream [获取通道码流]
#define RV_DEVSTATE_CONN			0x0007	//get connection status to device [获取设备连接状态]
#define RV_DEVSTATE_PROTOCAL_VER	0x0008	//get version of network protocal, pBuf = int* [获取网络协议版本号,	pBuf = int*]
#define RV_DEVSTATE_TALK_ECTYPE		0x0009	//get format list of audio talk supported by device, reference to struct RVDEV_TALKFORMAT_LIST [获取设备支持的语音对讲格式列表，见结构体RVDEV_TALKFORMAT_LIST]
#define RV_DEVSTATE_SD_CARD			0x000A	//get SD card infomation(products as IPC,etc...) [获取SD卡信息（IPC类产品）]
#define RV_DEVSTATE_BURNING_DEV			0x000B	//query infomation of imprinting machine[查询刻录机信息]
#define RV_DEVSTATE_BURNING_PROGRESS	0x000C	//query imprinting process [查询刻录进度]
#define RV_DEVSTATE_PLATFORM		0x000D	//get supported platform [获取设备支持的接入平台]
#define RV_DEVSTATE_CAMERA			0x000E	//get attributes of cameral, pBuf = RVDEV_CAMERA_INFO *, can have many bojects [获取摄像头属性信息，pBuf = RVDEV_CAMERA_INFO *，可以有多个结构体]
#define RV_DEVSTATE_SOFTWARE		0x000F	//software version infomation of device [设备软件版本信息]
#define RV_DEVSTATE_LANGUAGE        0x0010  //audio types supported by device [设备支持的语音种类]
#define RV_DEVSTATE_DSP				0x0011	//ability description of DSP [DSP能力描述]
#define	RV_DEVSTATE_OEM				0x0012	//OEM
#define	RV_DEVSTATE_NET				0x0013  //running infomation of network [网络运行状态信息]
#define RV_DEVSTATE_TYPE			0x0014  //devive type [设备类型]
#define RV_DEVSTATE_SNAP			0x0015	 //query ability of snapshot function [抓图功能能力查询]

//snapshot and video code mode type [抓图视频编码类型]
#define RV_CODE_TYPE_MPEG4   0
#define RV_CODE_TYPE_H264    1
#define RV_CODE_TYPE_JPG     2

//error type code, returned by SDK_GetLastError [错误类型代号，SDK_GetLastError函数的返回]
#define _EC(x)						(0x80000000|x)
#define RV_ET_NOERROR 				0				//no error [没有错误]
#define RV_ET_ERROR					-1				//unknown error [未知错误]
#define RV_ET_SYSTEM_ERROR			_EC(1)			//error in Windows system [Windows系统出错]
#define RV_ET_NETWORK_ERROR			_EC(2)			//net error, maybe because net timeout [网络错误，可能是因为网络超时]
#define RV_ET_DEV_VER_NOMATCH		_EC(3)			//device protocal not mathched [设备协议不匹配]
#define RV_ET_INVALID_HANDLE		_EC(4)			//invalid handle [句柄无效]
#define RV_ET_OPEN_CHANNEL_ERROR	_EC(5)			//fail to open channel [打开通道失败]
#define RV_ET_CLOSE_CHANNEL			_EC(6)			//fail to close channel [关闭通道失败]
#define RV_ET_ILLEGAL_PARAM			_EC(7)			//user params not valid [用户参数不合法]
#define RV_ET_SDK_INIT_ERROR		_EC(8)			//error occur while initializing SDK [SDK初始化出错]
#define RV_ET_SDK_UNINIT_ERROR		_EC(9)			//error occur while cleanuping SDK [SDK清理出错]
#define RV_ET_RENDER_OPEN_ERROR		_EC(10)			//error occur while applying render resource [申请render资源出错]
#define RV_ET_DEC_OPEN_ERROR		_EC(11)			//error occur while opening decode library [打开解码库出错]
#define RV_ET_DEC_CLOSE_ERROR		_EC(12)			//error occur while closing decode library [关闭解码库出错]
#define RV_ET_MULTIPLAY_NOCHANNEL	_EC(13)			//detect that the channel number is 0 in multi-view previewing [多画面预览中检测到通道数为0]
#define RV_ET_TALK_INIT_ERROR		_EC(14)			//fail to initialize audio record library [录音库初始化失败]
#define RV_ET_TALK_NOT_INIT			_EC(15)			//audio record library not inialized [录音库未经初始化]
#define	RV_ET_TALK_SENDDATA_ERROR	_EC(16)			//error occur while sending audio data [发送音频数据出错]
#define RV_ET_REAL_ALREADY_SAVING	_EC(17)			//real-time data is in saving status [实时数据已经处于保存状态]
#define RV_ET_NOT_SAVING			_EC(18)			//not saved real-time data [未保存实时数据]
#define RV_ET_OPEN_FILE_ERROR		_EC(19)			//open file fail [打开文件出错]
#define RV_ET_PTZ_SET_TIMER_ERROR	_EC(20)			//fail to lauch PTZ control timer [启动云台控制定时器失败]
#define RV_ET_RETURN_DATA_ERROR		_EC(21)			//check returned value unvalid [对返回数据的校验出错]
#define RV_ET_INSUFFICIENT_BUFFER	_EC(22)			//not enough buffer [没有足够的缓存]
#define RV_ET_NOT_SUPPORTED			_EC(23)			//not support the function in this SDK [当前SDK未支持该功能]
#define RV_ET_NO_RECORD_FOUND		_EC(24)			//can't find out the record [查询不到录象]
#define RV_ET_NOT_AUTHORIZED		_EC(25)			//don't have operation authority [无操作权限]
#define RV_ET_NOT_NOW				_EC(26)			//can't comit now [暂时无法执行]
#define RV_ET_NO_TALK_CHANNEL		_EC(27)			//don't find out talk channel [未发现对讲通道]
#define RV_ET_NO_AUDIO				_EC(28)			//don't find out audio [未发现音频]
#define RV_ET_NO_INIT				_EC(29)			//CLientSDK not initialize [CLientSDK未经初始化]
#define RV_ET_DOWNLOAD_END			_EC(30)			//download over [下载已结束]
#define RV_ET_EMPTY_LIST			_EC(31)			//the result list of query is empty [查询结果为空]
#define RV_ET_GETCFG_SYSATTR	_EC(32)			//fail position while getting configure : system attributes [获取配置失败位置：系统属性]
#define RV_ET_GETCFG_SERIAL		_EC(33)			//fail position while getting configure : serial number [获取配置失败位置：序列号]
#define RV_ET_GETCFG_GENERAL	_EC(34)			//fail position while getting configure : common attributes [获取配置失败位置：常规属性]
#define RV_ET_GETCFG_DSPCAP		_EC(35)			//fail position while getting configure : ability description of DSP [获取配置失败位置：DSP能力描述]
#define RV_ET_GETCFG_NETCFG		_EC(36)			//fail position while getting configure : network attributes [获取配置失败位置：网络属性]
#define RV_ET_GETCFG_CHANNAME	_EC(37)			//fail position while getting configure : channel name [获取配置失败位置：通道名称]
#define RV_ET_GETCFG_VIDEO		_EC(38)			//fail position while getting configure : video attributes [获取配置失败位置：视频属性]
#define RV_ET_GETCFG_RECORD		_EC(39)			//fail position while getting configure : configure of timer record [获取配置失败位置：录象定时配置]
#define RV_ET_GETCFG_PRONAME	_EC(40)			//fail position while getting configure : protocal name of decoder [获取配置失败位置：解码器协议名称]
#define RV_ET_GETCFG_FUNCNAME	_EC(41)			//fail position while getting configure : function name of 232 serial port [获取配置失败位置：232串口功能名称]
#define RV_ET_GETCFG_485DECODER	_EC(42)			//fail position while getting configure : attributes of decoder [获取配置失败位置：解码器属性]
#define RV_ET_GETCFG_232COM		_EC(43)			//fail position while getting configure : attributes of 232 serial port [获取配置失败位置：232串口属性]
#define RV_ET_GETCFG_ALARMIN	_EC(44)			//fail position while getting configure : attributes of alarm-in [获取配置失败位置：外部报警输入属性]
#define RV_ET_GETCFG_ALARMDET	_EC(45)			//fail position while getting configure : attributes of picture detect [获取配置失败位置：图像检测报警属性]
#define RV_ET_GETCFG_SYSTIME	_EC(46)			//fail position while getting configure : device time [获取配置失败位置：设备时间]
#define RV_ET_GETCFG_PREVIEW	_EC(47)			//fail position while getting configure : params of preview [获取配置失败位置：预览参数]
#define RV_ET_GETCFG_AUTOMT		_EC(48)			//fail position while getting configure : configure of auto-mantance [获取配置失败位置：自动维护配置]
#define RV_ET_GETCFG_VIDEOMTRX	_EC(49)			//fail position while getting configure : configure of video matrix [获取配置失败位置：视频矩阵配置]
#define RV_ET_GETCFG_COVER		_EC(50)			//fail position while getting configure : video area shelter [获取配置失败位置：视频区域遮挡]
#define RV_ET_GETCFG_WATERMAKE	_EC(51)			//fail position while getting configure : configure of watermask [获取配置失败位置：图象水印配置]
#define RV_ET_SETCFG_GENERAL	_EC(55)			//fail position while setting configure : common attributes [设置配置失败位置：常规属性]
#define RV_ET_SETCFG_NETCFG		_EC(56)			//fail position while setting configure : network attributes [设置配置失败位置：网络属性]
#define RV_ET_SETCFG_CHANNAME	_EC(57)			//fail position while setting configure : channel name [设置配置失败位置：通道名称]
#define RV_ET_SETCFG_VIDEO		_EC(58)			//fail position while setting configure : video attributes [设置配置失败位置：视频属性]
#define RV_ET_SETCFG_RECORD		_EC(59)			//fail position while setting configure : configure of timer record [设置配置失败位置：录象定时配置]
#define RV_ET_SETCFG_485DECODER	_EC(60)			//fail position while setting configure : attributes of decoder [设置配置失败位置：解码器属性]
#define RV_ET_SETCFG_232COM		_EC(61)			//fail position while setting configure : attributes of 232 serial port [设置配置失败位置：232串口属性]
#define RV_ET_SETCFG_ALARMIN	_EC(62)			//fail position while setting configure : attributes of alarm-in [设置配置失败位置：外部报警输入属性]
#define RV_ET_SETCFG_ALARMDET	_EC(63)			//fail position while setting configure : attributes of picture detect [设置配置失败位置：图像检测报警属性]
#define RV_ET_SETCFG_SYSTIME	_EC(64)			//fail position while setting configure : device time [设置配置失败位置：设备时间]
#define RV_ET_SETCFG_PREVIEW	_EC(65)			//fail position while setting configure : preview params [设置配置失败位置：预览参数]
#define RV_ET_SETCFG_AUTOMT		_EC(66)			//fail position while setting configure : configure of auto-mantance [设置配置失败位置：自动维护配置]
#define RV_ET_SETCFG_VIDEOMTRX	_EC(67)			//fail position while setting configure : configure of video matrix [设置配置失败位置：视频矩阵配置]
#define RV_ET_SETCFG_COVER		_EC(69)			//fail position while setting configure : video area shelter [设置配置失败位置：视频区域遮挡]
#define RV_ET_SETCFG_WATERMAKE	_EC(60)			//fail position while setting configure : configure of picture watermark [设置配置失败位置：图象水印配置]
#define RV_ET_SETCFG_WLAN		_EC(61)			//fail position while setting configure : wireless network information [设置配置失败位置：无线网络信息]
#define RV_ET_SETCFG_WLANDEV	_EC(62)			//fail position while setting configure : select wireless network device [设置配置失败位置：选择无线网络设备]
#define RV_ET_SETCFG_REGISTER	_EC(63)			//fail position while setting configure : configure of auto-register params [设置配置失败位置：主动注册参数配置]
#define RV_ET_SETCFG_CAMERA		_EC(64)			//fail position while setting configure : configure of cameral attributes [设置配置失败位置：摄像头属性配置]
#define RV_ET_SETCFG_INFRARED	_EC(65)			//fail position while setting configure : configure of infrared ray alarm [设置配置失败位置：红外报警配置]
#define RV_ET_SETCFG_SOUNDALARM	_EC(66)			//fail position while setting configure : configure of audio alarm [设置配置失败位置：音频报警配置]
#define RV_ET_SETCFG_STORAGE    _EC(67)			//fail position while setting configure : configure of store position [设置配置失败位置：存储位置配置]

#define RV_ET_AUDIOENCODE_NOTINIT		_EC(70)			//interface of audio code not initialized success [音频编码接口没有成功初始化]
#define RV_ET_DATA_TOOLONGH				_EC(71)			//data too long [数据过长]
#define RV_ET_UNSUPPORTED				_EC(72)			//device don't support this operation [设备不支持该操作]
#define RV_ET_DEVICE_BUSY				_EC(73)			//resource of device not enough [设备资源不足]
#define RV_ET_SERVER_STARTED			_EC(74)			//server had been lauched [服务器已经启动]
#define RV_ET_SERVER_STOPPED			_EC(75)			//server had not been lauched [服务器尚未成功启动]

#define RV_ET_LISTER_INCORRECT_SERIAL	_EC(80)			//inputed serial number is incorrect [输入序列号有误]
#define RV_ET_QUERY_DISKINFO_FAILED		_EC(81)			//fail to get disk infomation [获取硬盘信息失败]

#define RV_ET_LOGIN_ERROR_PASSWORD		_EC(100)		//passwork not correct [密码不正确]
#define RV_ET_LOGIN_ERROR_USER			_EC(101)		//account not exist [帐户不存在]
#define RV_ET_LOGIN_ERROR_TIMEOUT		_EC(102)		//wait to login timeout [等待登录返回超时]
#define RV_ET_LOGIN_ERROR_RELOGGIN		_EC(103)		//account had logined [帐号已登录]
#define RV_ET_LOGIN_ERROR_LOCKED		_EC(104)		//account had been locked [帐号已被锁定]
#define RV_ET_LOGIN_ERROR_BLACKLIST		_EC(105)		//account had been add to black ip list [帐号已被列为黑名单]
#define RV_ET_LOGIN_ERROR_BUSY			_EC(106)		//resource is not enough, system is busy [资源不足，系统忙]
#define RV_ET_LOGIN_ERROR_CONNECT		_EC(107)		//fail to connect to host [连接主机失败"]
#define RV_ET_LOGIN_ERROR_NETWORK		_EC(108)		//fail to connect to network [网络连接失败"]

#define RV_ET_RENDER_SOUND_ON_ERROR		_EC(120)		//Render Library open audio error [Render库打开音频出错]
#define RV_ET_RENDER_SOUND_OFF_ERROR	_EC(121)		//Render Library close audio error [Render库关闭音频出错]
#define RV_ET_RENDER_SET_VOLUME_ERROR	_EC(122)		//Render Library control volumn error [Render库控制音量出错]
#define RV_ET_RENDER_ADJUST_ERROR		_EC(123)		//Render Library set picture param error [Render库设置画面参数出错]
#define RV_ET_RENDER_PAUSE_ERROR		_EC(124)		//Render Library pause error [Render库暂停播放出错]
#define RV_ET_RENDER_SNAP_ERROR			_EC(125)		//Render Library snapshot error [Render库抓图出错]
#define RV_ET_RENDER_STEP_ERROR			_EC(126)		//Render Library step error [Render库步进出错]
#define RV_ET_RENDER_FRAMERATE_ERROR	_EC(127)		//Render Library set frame rate error [Render库设置帧率出错]

#define RV_ET_GROUP_EXIST				_EC(140)		//group name is exist already [组名已存在]
#define	RV_ET_GROUP_NOEXIST				_EC(141)		//group name is not exist [组名不存在]
#define RV_ET_GROUP_RIGHTOVER			_EC(142)		//authorities of the group exceed range of the authority list [组的权限超出权限列表范围]
#define RV_ET_GROUP_HAVEUSER			_EC(143)		//can't delete the group because there are users belong to this group [组下有用户，不能删除]
#define RV_ET_GROUP_RIGHTUSE			_EC(144)		//some authority of the group is using by some user [组的某个权限被用户使用，不能出除]
#define RV_ET_GROUP_SAMENAME			_EC(145)		//new group name is duplicate to some exist group name [新组名同已有组名重复]
#define	RV_ET_USER_EXIST				_EC(146)		//user exist [用户已存在]
#define RV_ET_USER_NOEXIST				_EC(147)		//user not exist [用户不存在]
#define RV_ET_USER_RIGHTOVER			_EC(148)		//the authorities of user excceed to the authorities of group [用户权限超出组权限]
#define RV_ET_USER_PWD					_EC(149)		//reserved account, can't be modified [保留帐号，不容许修改密码]
#define RV_ET_USER_FLASEPWD				_EC(150)		//incorrect password [密码不正确]
#define RV_ET_USER_NOMATCHING			_EC(151)		//password not matched [密码不匹配]

#define RV_ET_GETCFG_ETHERNET	_EC(300)		//fail position while getting configure : network card configure [获取配置失败位置：网卡配置]
#define RV_ET_GETCFG_WLAN		_EC(301)		//fail position while getting configure : wireless card infomation [获取配置失败位置：无线网络信息]
#define RV_ET_GETCFG_WLANDEV	_EC(302)		//fail position while getting configure : search wireless network device [获取配置失败位置：搜索无线网络设备]
#define RV_ET_GETCFG_REGISTER	_EC(303)		//fail position while getting configure : configure of auto-register params [获取配置失败位置：主动注册参数配置]
#define RV_ET_GETCFG_CAMERA		_EC(304)		//fail position while getting configure : configure of cameral attributes [获取配置失败位置：摄像头属性配置]
#define RV_ET_GETCFG_INFRARED	_EC(305)		//fail position while getting configure : configure of infrared ray alarm [获取配置失败位置：红外报警配置]
#define RV_ET_GETCFG_SOUNDALARM	_EC(306)		//fail position while getting configure : configure of audio alarm [获取配置失败位置：音频报警配置]
#define RV_ET_GETCFG_STORAGE    _EC(307)		//fail position while getting configure : configure of store position [获取配置失败位置：存储位置配置]
#define RV_ET_GETCFG_MAIL		_EC(308)		//fail to get email configure [获取邮件配置失败]

#define RV_ET_CONFIG_DEVBUSY			_EC(999)		//can't set now [暂时无法设置]
#define RV_ET_CONFIG_DATAILLEGAL		_EC(1000)		//data for configure is invalid [配置数据不合法]

//interface for remote configure : SDK_GetDEVConfig,SDK_GetDEVConfig, their params and commands define [远程配置接口SDK_GetDEVConfig,SDK_GetDEVConfig参数：命令定义]
#define RV_DEV_DEVICECFG			1		//get device params [获取设备参数]
#define RV_DEV_NETCFG				2		//get network params [获取网络参数]
#define RV_DEV_CHANNELCFG			3		//get channel configure - picture and compress params, etc... [获取通道配置－图像及压缩参数等]
#define RV_DEV_PREVIEWCFG 			4		//get preview params [获取预览参数]
#define RV_DEV_RECORDCFG			5		//get record time params [获取录像时间参数]
#define RV_DEV_COMMCFG				6		//get serial port params [获取串口参数]
#define RV_DEV_ALARMCFG 			7		//get alarm params [获取报警参数]
#define RV_DEV_TIMECFG 				8		//get DVR time [获取DVR时间]
#define RV_DEV_TALKCFG				9		//talk params [对讲参数]
#define RV_DEV_AUTOMTCFG			10		//auto-mantance configure [自动维护配置]		
#define	RV_DEV_VEDIO_MARTIX			11		//configure of local matrix control plot [本机矩阵控制策略配置]	
#define RV_DEV_MULTI_DDNS			12		//configure of multi-DDNS server [多ddns服务器配置]
#define RV_DEV_SNAP_CFG				13		//configure about snapshot [抓图相关配置]
#define RV_DEV_WEB_URL_CFG			14		//configure of HTTP path [HTTP路径配置]
#define RV_DEV_FTP_PROTO_CFG		15		//configure of FTP [FTP上传配置]
#define RV_DEV_INTERVIDEO_CFG		16		//configure of platform connection, param channel means platform type now [平台接入配置，此时channel参数代表平台类型，]
#define RV_DEV_VIDEO_COVER			17		//configure of area shelter [区域遮挡配置]
#define RV_DEV_TRANS_STRATEGY		18		//configure of transport plot, picture quality first / fluency first [传输策略配置，画质优先\流畅性优先]
#define RV_DEV_DOWNLOAD_STRATEGY	19		//configure of record download plot, high download / common download [录象下载策略配置，高速下载\普通下载]
#define RV_DEV_WATERMAKE_CFG		20		//configure of picture watermark [图象水印配置]
#define RV_DEV_WLAN_CFG				21		//configure of wireless network [无线网络配置]
#define RV_DEV_WLAN_DEVICE_CFG		22		//configure of search wireless device [搜索无线设备配置]
#define RV_DEV_REGISTER_CFG			23		//configure of auto-register params [主动注册参数配置]
#define RV_DEV_CAMERA_CFG			24		//configure of cameral attributes [摄像头属性配置]
#define RV_DEV_INFRARED_CFG 		25		//get infrared ray alarm params [获取红外报警参数]
#define RV_DEV_SNIFFER_CFG			26		//configure of capture packet by Sniffer [Sniffer抓包配置]
#define RV_DEV_MAIL_CFG				27		//configure of email, recommend to use this type of configure [邮件配置,建议以后采用此类型配置]
#define RV_DEV_DNS_CFG				28		//configure of DNS server [DNS服务器配置]
#define RV_DEV_NTP_CFG				29		//configure of NTP [NTP配置]
#define RV_DEV_AUDIO_DETECT_CFG		30		//configure of audio detect [音频检测配置]
#define RV_DEV_STORAGE_STATION_CFG  31      //configure of store position [存储位置配置]
#define RV_DEV_PTZ_OPT_CFG			32		//attributes of PTZ operation [云台操作属性]
#define RV_DEV_DDNS_CFG				33		//configure of DDNS [DDNS配置]
#define RV_DEV_UPNP_CFG				34		//configure of UPNP [UPNP配置]
#define RV_DEV_SAVIA_ALARM_CFG		35		//configure of SAVIA alarm params [SAVIA报警参数配置]
#define RV_DEV_SAVIA_COUNT_CFG		36		//SAVIA count [SAVIA数目]
#define RV_DEV_BLACKWHITE_CFG		37		//params of black and white ip list [黑白名单参数]
#define RV_DEV_DDNS_CFG_EX			38		//configure of DDNS [DDNS配置]
#define RV_DEV_DECODER_CFG			39		//configure of decoder [解码器配置]
#define RV_DEV_REG_SERVER_CFG		40		//configure of auto-register [主动注册配置]
#define RV_DEV_DISPLAY_SPLIT		41		//configure of views combine and split [画面分割通道组合配置]
#define RV_DEV_DISPLAY_TOUR			42		//configure of tour [轮巡配置]
#define RV_DEV_DISPLAY_SPLITTOUR	43		//configure of views combine adn split tour [画面分割通道组合轮巡配置]
#define RV_DEV_SNAP_CFG_NEW			44		//configure of snapshot [抓图相关配置]
#define RV_DEV_DECODER_ALARM_CFG	45		//configure of decoder alarm [解码器告警配置]
#define RV_DEV_MARGIN_CFG			46		//configure of TV adjust [TV调节配置]
#define RV_DEV_IPCONFLICT_CFG		47		//configure of IP conflict [IP冲突配置]
#define RV_DEV_MAIL_CFG_EX			48		//new configure of email [新邮箱配置]
#define RV_DEV_DEV_CFG				49		//device name (use new protocal) [设备信息(使用TLV协议)]
#define RV_DEV_CHANNEL_ENC_CFG		50		//code infomation of channel (use new protocal) [设备通道编码信息(使用TLV协议)]
#define RV_DEV_NET_BASE_CFG			51		//basic network configure (use new protocal) [基本网络配置(使用TLV协议)]
#define RV_DEV_NET_APP_CFG			52		//application network configure (use new protocal) [应用网络配置(使用TLV协议)]
#define RV_DEV_ALARM_CFG			53		//get all alarm configure (use new protocal) [获取所有报警配置(使用TLV协议)]
#define RV_DEV_ALARM_IN_CFG			54		//set alarm-in alarm configure (use new protocal) [设置报警输入报警配置(使用TLV协议)]
#define RV_DEV_ALARM_MOTION_CFG		55		//set video detect alarm configure (use new protocal) [设置视频动检报警配置(使用TLV协议)]
#define RV_DEV_ALARM_LOSS_CFG		56		//set video lost alarm configure (use new protocal) [设置视频视频丢失报警配置(使用TLV协议)]
#define RV_DEV_ALARM_BIND_CFG		57		//set video shelter alarm configure (use new protocal) [设置视频视频遮挡报警配置(使用TLV协议)]
#define RV_DEV_ALARM_NODISK_CFG		58		//set no disk alarm configure (use new protocal) [设置无硬盘报警配置(使用TLV协议)]
#define RV_DEV_ALARM_ERRDISK_CFG	59		//set disk error alarm configure (use new protocal) [设置硬盘错误报警配置(使用TLV协议)]
#define RV_DEV_ALARM_FULLDISK_CFG	60		//set disk full alarm configure (use new protocal) [设置硬盘满报警配置(使用TLV协议)]
#define RV_DEV_ALARM_NETBROKEN_CFG	61		//set network disconnect alarm configure (use new protocal) [设置断网报警配置(使用TLV协议)]
#define RV_DEV_ALARM_IPCONFLICT_CFG	62		//set IP conflict alarm configure (use new protocal) [设置IP冲突报警配置(使用TLV协议)]

#define RV_DEV_INTERVIDEO_MEGA_CFG	65		//configure of HXHT platform connection [互信互通平台接入配置]
#define RV_DEV_INTERVIDEO_VS300_CFG	66		//configure of VS300 platform connection [VS300平台接入配置]
#define RV_DEV_INTERVIDEO_ZXSHENYAN_CFG	67	//configure of SHENYAN platform connection [神眼平台接入配置]

#define RV_DEV_DISK_CFG				80		//configure of disk (use new protocal) [磁盘配置(使用TLV协议)]
#define RV_DEV_NET_COMM_CFG			81		//network common configure (use new protocal) [网络通用配置(使用TLV协议)]--RV_CONFIG_NET_COMM
#define RV_DEV_EMAIL_CFG			82		//email configure (use new protocal) [EMAIL配置(使用TLV协议)]
#define RV_DEV_DNS_CFG_TLV			83		//dns configure (use new protocal) [dns配置(使用TLV协议)]
#define RV_DEV_UPNP_CFG_TLV			84		//upnp cpnfigure (use new protocal) [upnp配置(使用TLV协议)]
#define RV_DEV_PPPOE_CFG			85		//pppoe configure (use new protocal) [pppoe配置(使用TLV协议)]
#define RV_DEV_MDDNS_CFG			86		//ddns configure (use new protocal) [DDNS配置(使用TLV协议)]
#define RV_DEV_CODE_CFG				87		//code configure (use new protocal) [编码配置(使用TLV协议)]
#define RV_DEV_NTP_CFG_TLV			88		//NTP configure (use new protocal) [NTP配置(使用TLV协议)]
#define RV_DEV_OUT_MODE_CFG			89		//output mode configure (use new protocal) [输出模式配置(使用TLV协议)]
#define	RV_DEV_PRESET_CFG			90		//configure of PTZ preset [云台预置点配置]
#define RV_DEV_TOUR_CFG				91		//configure of PTZ tour in prestes [云台点间巡航配置]--
#define RV_DEV_ADDPRESET_CFG		92		//add preset operation [增加预置点操作]
#define RV_DEV_DELETEPRESET_CFG		93		//delete preset operation [删除预置点操作]
#define	RV_DEV_ADDTOURPRESET_CFG	94		//add preset to tour operation [增加巡航预置点操作]
#define RV_DEV_DELTOURPRESET_CFG	95		//delete preset from tour operation [删除巡航预置点操作]
#define	RV_DEV_CLEARTOUR_CFG		96		//delete tour [删除巡航线路]
#define	RV_DEV_FTP_CFG				97		//FTP configure [FTP设置]
#define	RV_DEV_RTSP_CFG				98		//RTSP configure [RTSP设置]
#define	RV_DEV_INTERED_CFG			99		//configure of intelligent red detect alarm [智能红色检测报警设置]
#define RV_DEV_NETCFG_RHEX			100		//get network params (not 98 serial device remotehost's legth is 64 bytes) [获取网络参数(非98设备remotehost长度64字节)]
#define	RV_DEV_RECCTL_CFG			101		//record control params (use new protocal) [录像控制参数(使用TLV协议)]---RV_RECCTL
#define RV_DEV_COMMCFG_EX			102		//get serial port params (more than 16 channels) [获取串口参数(超过16通道)]
#define RV_DEV_CHANNEL_NAME			103		//get channel name (use new protocal) [获取通道名(使用TLV协议)]
#define RV_DEV_AUDIO_T				104		//audio configure (use new protocal) [音频配置(使用TLV协议)]
#define RV_DEV_DIGICHAN_TOUR		105		//digital channel tour configure (use new protocal) [数字通道轮训配置(使用TLV协议)]
#define RV_DEV_KBD					106		//protocal of control key-board (use new protocal) [控制键盘协议(使用TLV协议)]
#define RV_DEV_MATRIX_XINGHUO		107		//matrix (for XINGHUO Corp.) configure (use new protocal) [矩阵(星火)配置(使用TLV协议)]
#define RV_DEV_RTSP_CFGEX			108		//get RTSP infomation (not use new protocal) [获取RTSP信息(使用非TLV协议)]
#define RV_DEV_NTP_CFGEX			109		//get NTP infomation (not use new protocal) [获取NTP信息(使用非TLV协议)]
#define RV_DEV_OSDZOOM_CFG			110		//Get OSD zoom infomation(use new protocal)	[获取OSD zoom信息(使用TLV协议)]
#define RV_DEV_MATRIX_CIDPID        111     //Get the CID and PID relation (use new protocol)[获取矩阵配置中通道与矩阵号的对应关系]
#define RV_DEV_USER_END_CFG			1000

////////////////constant abount remote configure struct [远程配置结构体相关常量]///////////////////////
#define RV_MAX_MAIL_ADDR_LEN		128	//max length of email sender's or receiver's address [邮件发(收)人地址最大长度]
#define RV_MAX_MAIL_SUBJECT_LEN		64	//max length of email title [邮件主题最大长度]
#define RV_MAX_IPADDR_LEN			16	//max length of IP address [IP地址字符串长度]
#define RV_MACADDR_LEN				40	//max length of MAC address [MAC地址字符串长度]
#define RV_MAX_URL_LEN				128	//max length of URL [URL字符串长度]
#define RV_MAX_DEV_ID_LEN			48	//max length of code number of machine [机器编号最大长度]
#define	RV_MAX_HOST_NAMELEN			64  //max length of host name [主机名字符串长度]
#define RV_MAX_HOST_PSWLEN			32	//max length of password [长度]
#define RV_MAX_HOST_PSWLEN_EX		64	//max length of password extend [长度]
#define RV_MAX_NAME_LEN				16	//max length of common name [通用名字字符串长度]
#define RV_MAX_NAME_LEN_EX			32	//max length of email user name [邮箱用户名字符串长度]	
#define RV_MAX_ETHERNET_NUM			2	//max number of ethernet interface 以太网口最大个数]
#define	RV_DEV_SERIALNO_LEN			48	//max length of serial number string [序列号字符串长度]
#define RV_DEV_TYPE_LEN				32	//max length of device type string [设备类型字符串长度]
#define RV_N_WEEKS					7	//number of days per week [一周的天数]
#define RV_N_TSECT					6	//number of common time slice [通用时间段个数]
#define RV_N_REC_TSECT				6	//number of record time slice [录像时间段个数]
#define RV_N_COL_TSECT				2	//number of color time slice [颜色时间段个数]	
#define RV_CHAN_NAME_LEN			64	//channel name length, limit to dvr DSP ability, max 32 bytes [通道名长度,dvr DSP能力限制，最多32字节]		
#define RV_N_ENCODE_AUX				3	//number of assist bit-stream [扩展码流个数]
#define RV_N_TALK					1	//max talk channel number [最多对讲通道个数]
#define RV_N_COVERS					1	//number of shelter area [遮挡区域个数]	
#define RV_N_CHANNEL				16	//max number of channel [最大通道个数]	
#define RV_N_ALARM_TSECT			2	//number of alarm prompt time slice [报警提示时间段个数]
#define RV_MAX_ALARMOUT_NUM			16	//upper limit of number of alarm-out interface [报警输出口个数上限]
#define RV_MAX_VIDEO_IN_NUM			16	//upper limit of number of video input interface [视频输入口个数上限]
#define RV_MAX_ALARM_IN_NUM			16	//upper limit of number of alarm-in interface [报警输入口个数上限]
#define RV_MAX_DISK_NUM				16	//upper limit of number of disk, be 16 now[硬盘个数上限，暂定为16]
#define RV_MAX_DECODER_NUM			16	//upper limit of number of decoder(485) [解码器（485）个数上限]	
#define RV_MAX_DECODER_NUM_EX		32	//upper limit of number of decoder [解码器个数上限]	
#define RV_MAX_232FUNCS				10	//upper limit of number of function of 232 serial port [232串口功能个数上限]
#define RV_MAX_232_NUM				2	//upper limit of number of 232 serial port [232串口个数上限]
#define RV_MAX_DECPRO_LIST_SIZE		100	//upper limit of number of protocal of decoder [解码器协议列表个数上限]
#define RV_FTP_MAXDIRLEN			240	//max length of FTP file path [FTP文件目录最大长度]
#define RV_MATRIX_MAXOUT			16	//upper limit of number of matrix output interface [矩阵输出口最大个数]
#define RV_TOUR_GROUP_NUM			6	//upper limit of number of matrix output group [矩阵输出组最大个数]
#define RV_MAX_DDNS_NUM				10	//upper limit of number of ddns server supported by device [设备支持的ddns服务器最大个数]
#define RV_MAX_SERVER_TYPE_LEN		32	//max length of ddns server type string [ddns服务器类型 最大字符串长度]
#define RV_MAX_DOMAIN_NAME_LEN		256	//max length of ddns server domain [ddns域名 最大字符串长度]
#define RV_MAX_DDNS_ALIAS_LEN		32	//max length of ddns server other name [ddns服务器别名 最大字符串长度]
#define RV_MOTION_ROW				32	//row number of motion detect [动态检测区域的行数]
#define RV_MOTION_COL				32	//collumn number of moton detect [动态检测区域的列数]
#define	RV_FTP_USERNAME_LEN			64  //FTP configure : max size of user name [FTP配置，用户名最大长度]
#define	RV_FTP_PASSWORD_LEN			64  //FTP configure : max size of password [FTP配置，密码最大长度]
#define	RV_TIME_SECTION				2	//FTP configure : max size of time slice per day [FTP配置，每天时间段个数]
#define RV_FTP_MAX_PATH				240	//FTP configure : max size of file path name [FTP配置，文件路径名最大长度]
#define RV_INTERVIDEO_UCOM_CHANID	32	//platform connection configure : U WANGTONG channel ID [平台接入配置，U网通通道ID]
#define RV_INTERVIDEO_UCOM_DEVID	32	//platform connection configure : U WANGTONG device ID [平台接入配置，U网通设备ID]
#define RV_INTERVIDEO_UCOM_REGPSW	16	//platform connection configure : U WANGTONG password of registration [平台接入配置，U网通注册密码]
#define RV_INTERVIDEO_UCOM_USERNAME	32	//platform connection configure : U WANGTONG user name [平台接入配置，U网通用户名]
#define RV_INTERVIDEO_UCOM_USERPSW	32	//platform connection configure : U WANGTONG password [平台接入配置，U网通密码]
#define RV_INTERVIDEO_NSS_IP		32	//platform connection configure : ZHONGXINGLIWEI IP [平台接入配置，中兴力维IP]
#define RV_INTERVIDEO_NSS_SERIAL	32	//platform connection configure : ZHONGXINGLIWEI serial [平台接入配置，中兴力维serial]
#define RV_INTERVIDEO_NSS_USER		32	//platform connection configure : ZHONGXINGLIWEI user [平台接入配置，中兴力维user]
#define RV_INTERVIDEO_NSS_PWD		50	//platform connection configure : ZHONGXINGLIWEI password [平台接入配置，中兴力维password]

#define RV_MAX_VIDEO_COVER_NUM		16	//max number of area shelter [遮挡区域最大个数]
#define RV_MAX_WATERMAKE_DATA		4096//max length of watermark picture data [水印图片数据最大长度]
#define RV_MAX_WATERMAKE_LETTER		128	//max length of watermark text [水印文字最大长度]
#define RV_MAX_WLANDEVICE_NUM		10	//max number of searched wireless device [最多搜索出的无线设备个数]
#define RV_MAX_ALARM_NAME			64	//address length [地址长度]
#define RV_MAX_REGISTER_SERVER_NUM	10	//number of auto-register sever [主动注册服务器个数]
#define RV_SNIFFER_FRAMEID_NUM		6   //6 FRAME ID options [6个FRAME ID 选项]
#define RV_SNIFFER_CONTENT_NUM		4   //4 captured package content per FRAME [每个FRAME对应的4个抓包内容]
#define RV_MAX_PROTOCOL_NAME_LENGTH 20
#define RV_SNIFFER_GROUP_NUM		4   //4 groups capture package configure [4组抓包设置]
#define MAX_PATH_STOR				240 //length of remnote folder [远程目录的长度]
#define MAX_HHCHANNELNAME_LEN		32	//digital channel name length [数字通道名称长度]
#define RV_MAX_SAVIA_NUM			16	//max number of savia count [savia数目最大值]
#define RV_MAX_BLACK_IP_NUM			128	//max number of black ip [黑名单数目最大值]
#define RV_MAX_WHITE_IP_NUM			128	//max number of white ip [白名单数目最大值]
#define RV_MAX_DECODER_CHAN_NUM		32	//max number of dcoder channel [解码器通道数目最大值]

//广东红日
#define RV_KOTI_FLOOR_TYPE			650 // 楼层参数 
#define RV_KOTI_ROOM_TYPE			651 // 房间参数 
#define RV_KOTI_IP_CAM_NAME_TYPE	652 // 摄像头参数 
#define RV_KOTI_APARTMENT_CFG_TYPE  653 // 防区位置参数 
#define RV_KOTI_ALARM_AREA_TYPE		654 // 防区设置参数 
#define RV_KOTI_MOBILE_NUM_TYPE		655 // 报警电话参数 
#define RV_KOTI_SYSINFO_TYPE		656 // 系统参数 
#define RV_KOTI_ALARM_TIME_TYPE		657 // 安防参数 
#define RV_KOTI_PASSWORD_TYPE		658 // 安防密码参数 
#define RV_KOTI_RTSP_CONG_TYPE		659	// 平台对接参数 

#define RV_CONFIG_TYPE_AUTOREG_EX	230	//主动注册协议扩展 
#define RV_INTERVIDEO_TYPE_BELL_NETCOM 555	//北京BELL网通平台
#define RV_CFG_CAMERA				231	//视频采集参数
#define RV_ENCODE_OSD_WATERMARK		421	//数字水印
#define RV_DEV_SYSTEM_QUERYLOG		0x0010003B	//系统日志查询
#define RV_DEV_SYSTEM_OPRLOG		0x0010003C	//前端日志操作规则
#define RV_DEV_MANUAL_SNAP			422	//设备手动抓图
#define RV_DEV_SYSTEM_QUERY_REC_PIC	0x0010003D	//录像图片查询操作
#define RV_DEV_CONIFG_CARD_RECORD	660		//卡号录像
#define RV_DEV_CONFIG_CAMERA_EXT	232			//视频采集配置扩展信息--手动白平衡
#define RV_MJ_CAMERA_TYPE			0x80000259	// 明景球机参数配置--CONFIG_MJ_CAMERA
#define RV_MJ_CAMERA_ADVANCE_TYPE	0x8000025A	// 高级明景球机参数配置--CONFIG_MJ_ADV_CAMERA
#define RV_MJ_CAMERA_AUTOHOME_TYPE 	0x8000025B	// 参数配置--CONFIG_MJ_AUTO_HOME
#define RV_MJ_CAMERA_BLIND_TYPE		0x8000025C	// 参数配置--CONFIG_MJ_BLIND 
#define RV_MJ_CAMERA_POSTION_TYPE	0x8000025D	// 参数配置--CONFIG_MJ_POSTION 
#define RV_MJ_CAMERA_PTZ_CFG		0x8000025E	// 参数配置--CONFIG_MJ_PTZ 

#define RV_DEV_ENCODE_MAIN_CFG		0x8000019B
#define RV_DEV_ENCODE_SUB_CFG		0x8000019C
#define RV_DEV_ENCODE_3IRD_CFG		0x800002A8
#define RV_DEV_ENCODE_4RTH_CFG		0x8000026A
#define RV_DEV_ENCODE_5FTH_CFG		0x800002AA

//////////////////////////////////////////////////////////////////////////
//华雁电力配置
#define RV_DEV_CONIFG_YY_INTERVIDEO_COM 0x00010661		//主串口配置
#define RV_DEV_CONIFG_YY_INTERVIDEO_EXCOM 0x00020661	//扩展串口配置
#define RV_DEV_CONIFG_YY_INTERVIDEO_EVN 0x00030661		//环境设备配置
#define RV_DEV_CONIFG_YY_INTERVIDEO_EVN_ADD 0x0040661	//环境设备配置--增加一个
#define RV_DEV_CONIFG_YY_INTERVIDEO_EVN_DEL 0x00050661	//环境设备配置--删除一个
#define RV_DEV_CONIFG_YY_INTERVIDEO_EVN_ALARM 0x00060661//环境设备报警配置
#define RV_DEV_CONIFG_YY_INTERVIDEO_EVN_STATE 0x00070661//环境设备状态查询
//////////////////////////////////////////////////////////////////////////
#define RV_RECORD_MULTI_STREAM_CFG	706	// 配置录像时编码类型--CONFIG_RECORD_MULTI_STREAM
#define RV_DEV_ENCODER_DETECT_CFG  707	// 无码流检测功能--ENCODER_DETCETE
#define RV_DEV_NET_ALARM_IN_CFG		0x8036	//设置网络报警输入报警配置--参数与本地报警输入一致
#define RV_DEV_CONFIG_TYPE_ETHERNET_MTU	731		// MTU配置--MTU_SET

///////////////////平台接入配置命令字定义//////////////////////////////////
//平台接入配置以后统一在这儿，以后中星BELL，以别的方式接入暂时不管
//配置命令字为RV_PLAT_CFG，子类型EPlayCfgType中定义，
//在SDK_GetDevConfig或SDK_SetDevConfig的lChannel中传入
#define RV_PLAT_CFG					219	//平台配置
typedef enum _EPlayCfgType
{
// 	EPLAY_TYPE_ZXBELL = 550 ,	// 中星BELL--RVDEV_INTERVIDEO_BELL_CFG  
// 	EPLAY_TYPE_MEGA = 551 ,		// 互信--
// 	EPLAY_TYPE_VS300 = 552,		// VS300
// 	EPLAY_TYPE_SHENYAN = 553,	// 神眼
// 	EPLAY_TYPE_KOTI = 554,		// KOTI
// 	EPLAY_TYPE_BJUN = 555 ,		// 北京网通
	EPLAY_TYPE_GAYS = 556,		// 公安一所--SPlatGAYSCfg
	EPLAY_TYPE_VISS = 557,		// VISS平台--SPlatCfgViss
	EPLAY_TYPE_BELL30 = 558,	// BELL3.0平台--SPlatCfgViss
	EPLAY_TYPE_BLUESTAR = 559,	// Blue star平台--CONFIG_NET_BLUESTAR 
	EPLAY_TYPE_HAOWEI = 560,	// 豪威--CONFIG_NET_HW
	EPLAY_TYPE_HUAYAN = 561,	// 华雁--CONFIG_NET_SZYUANYANG
	EPLAY_TYPE_SHSS =   562,		// SH_REG_CONFIG
	EPLAY_TYPE_CHINAMOBILE = 563,	// ChinaMoblie--CONFIG_NET_CHINAMOBILE
	EPLAY_TYPE_ZXBELL2 = 564,		// 中星bell同时接入2个服务器--RVDEV_INTERVIDEO_BELL_CFG 
	EPLAY_TYPE_XMWST = 565,			// 厦门威思通--CONFIG_WST_NET
}EPlayCfgType;

#define SUVA_ALARM_ENABLE		0x8000015E	// SUVA使能配置--NET_Enable    
#define SUVA_AREA_CONFIG		0x800002BD	// SUVA配置区域--NET_SUVA_EREA
#define SUVA_CONFIG_TYPE		700			// SUVA配置区域--SSUVACfgs

#define RV_CONFIG_TYPE_WEIELESS	691			// 无线配置--NET_WRIELESS_CONFIG
#define ENCODE_COLOR_TYPE_EX	0x800001A7	// 图像风格设置扩展--NET_VIDEOCOLOR_EX
#define ENCODE_COLOR_TYPE_EX_TABLE	424		// 每种风格的值--COLOR_TYPE_EX_TABLE  
#define CAMERA_RESOLUTION_TYPE  0x8000025F	// 视频采集信息--CONFIG_SENSOR
#define CAMERA_DRC_TYPE			0x80000260	// 视频采集信息--CAMERA_DRC_TYPE
#define CAMERA_SUPPER_CONFIG_TYPE 0x80000261 // 超级用户配置--CONFIG_SUPPER
#define CAMERA_BADPIXEL_DETECT	0x80000262	// 坏点检测
#define ENCODE_COLOR_TYPE_CFG	0x8000019F	// 视频颜色配置--RV_NET_VIDEOCOLOR
#define ENCODE_CHANNEL_MUTILE_TITLE 0x800001A9	// 多行OSD叠加--MUTILE_TITLE 
#define DEV_CONFIG_TYPE_ETHERNET_IPV6	730		// IPv6配置--CONFIG_NET_ETH_IPV6 
#define DEV_INTERVIDEO_LOG_LENTH		720		// 平台日志长度查询--INTERVIDEO_LOG_LENTH_T
#define DEV_INTERVIDEO_LOG_DATA			721		// 平台日志内容查询--INTERVIDEO_LOG_DATA_T
#define DEV_INTERVIDEO_LOG_DELETE		722		// 平台日志清除操作--INTERVIDEO_LOG_DELETE_T


//////////////////////////////////////////////////////////////////////////
//resolve list, be used to very bit-mask with resolve mask value [分辨率列表，用于与分辨率掩码进行与、或操作]
#define	RV_CAPTURE_SIZE_D1			0x00000001
#define RV_CAPTURE_SIZE_HD1			0x00000002
#define RV_CAPTURE_SIZE_BCIF		0x00000004
#define RV_CAPTURE_SIZE_CIF			0x00000008
#define RV_CAPTURE_SIZE_QCIF		0x00000010	
#define RV_CAPTURE_SIZE_VGA			0x00000020	
#define RV_CAPTURE_SIZE_QVGA		0x00000040
#define RV_CAPTURE_SIZE_SVCD		0x00000080
#define RV_CAPTURE_SIZE_QQVGA		0x00000100
#define RV_CAPTURE_SIZE_SVGA		0x00000200
#define RV_CAPTURE_SIZE_XVGA		0x00000400
#define RV_CAPTURE_SIZE_WXGA		0x00000800
#define RV_CAPTURE_SIZE_SXGA		0x00001000
#define RV_CAPTURE_SIZE_WSXGA		0x00002000   
#define RV_CAPTURE_SIZE_UXGA		0x00004000
#define RV_CAPTURE_SIZE_WUXGA       0x00008000

//attributes of PTZ [云台属性列表]
//lowMask
#define RV_PTZ_DIRECTION			0x00000001				//direction [/*!< 方向 */]
#define RV_PTZ_ZOOM					0x00000002	   			//zoom [/*!< 变倍 */]
#define RV_PTZ_FOCUS				0x00000004				//focus [/*!< 聚焦 */]
#define RV_PTZ_IRIS					0x00000008				//aperture [/*!< 光圈 */]
#define RV_PTZ_ALARM				0x00000010				//alarm function [/*!< 报警功能 */]
#define RV_PTZ_LIGHT				0x00000020				//lamp [/*!< 灯光 */]
#define RV_PTZ_SETPRESET			0x00000040				//set preset [/*!< 设置预置点 */]
#define RV_PTZ_CLEARPRESET			0x00000080				//clear preset [/*!< 清除预置点 */]
#define RV_PTZ_GOTOPRESET			0x00000100				//move to preset [/*!< 转至预置点 */]
#define RV_PTZ_AUTOPANON			0x00000200				//horizontal start [/*!< 水平开始 */]
#define RV_PTZ_AUTOPANOFF			0x00000400				//horizontal stop [/*!< 水平结束 */]
#define RV_PTZ_SETLIMIT				0x00000800				//set bound [/*!< 设置边界 */]
#define RV_PTZ_AUTOSCANON			0x00001000				//auto scan start [/*!< 自动扫描开始 */]
#define RV_PTZ_AUTOSCANOFF			0x00002000				//auto scan stop [/*!< 自动扫描开停止 */]
#define RV_PTZ_ADDTOUR				0x00004000				//add preset to tour [/*!< 增加巡航点 */]
#define RV_PTZ_DELETETOUR			0x00008000				//delete preset from tour [/*!< 删除巡航点 */]
#define RV_PTZ_STARTTOUR			0x00010000				//start tour [/*!< 开始巡航 */]
#define RV_PTZ_STOPTOUR				0x00020000				//end tour [/*!< 结束巡航 */]
#define RV_PTZ_CLEARTOUR			0x00040000				//clear tour [/*!< 删除巡航 */]
#define RV_PTZ_SETPATTERN			0x00080000				//set mode [/*!< 设置模式 */]
#define RV_PTZ_STARTPATTERN			0x00100000				//start mode [/*!< 开始模式 */]
#define RV_PTZ_STOPPATTERN			0x00200000				//stop mode [/*!< 停止模式 */]
#define RV_PTZ_CLEARPATTERN			0x00400000				//clear mode [/*!< 清除模式 */]
#define RV_PTZ_POSITION				0x00800000				//fast locate [/*!< 快速定位 */]
#define RV_PTZ_AUX					0x01000000				//assist switch [/*!< 辅助开关 */]
#define RV_PTZ_MENU					0x02000000				//menu of PTZ cameral [/*!< 球机菜单 */]
#define RV_PTZ_EXIT					0x04000000				//exit from menu of PTZ cameral [/*!< 退出球机菜单 */]
#define RV_PTZ_ENTER				0x08000000				//confirm [/*!< 确认 */]
#define RV_PTZ_ESC					0x10000000				//cancel [/*!< 取消 */]
#define RV_PTZ_MENUUPDOWN			0x20000000				//up and down menu [/*!< 菜单上下操作 */]
#define RV_PTZ_MENULEFTRIGHT		0x40000000				//left and right operation of menu [/*!< 菜单左右操作 */]
#define RV_PTZ_OPT_NUM				0x80000000				//number of operation [/*< 操作的个数 */]

//hiMask
#define RV_PTZ_DEV						0x00000001				//PTZ control [/*!< 云台控制 */]
#define RV_PTZ_MATRIX					0x00000002				//matrix control [/*!< 矩阵控制 */]

//code mode list, can be used to very bit-mask with code mode mask value [编码模式列表，用于与编码模式掩码进行与、或操作]
#define RV_CAPTURE_COMP_DIVX_MPEG4	0x00000001
#define RV_CAPTURE_COMP_MS_MPEG4 	0x00000002
#define RV_CAPTURE_COMP_MPEG2		0x00000004
#define RV_CAPTURE_COMP_MPEG1		0x00000008
#define RV_CAPTURE_COMP_H263		0x00000010
#define RV_CAPTURE_COMP_MJPG		0x00000020
#define RV_CAPTURE_COMP_FCC_MPEG4	0x00000040
#define RV_CAPTURE_COMP_H264		0x00000080

//bit-stream control list [码流控制列表]
#define RV_CAPTURE_BRC_CBR			0
#define RV_CAPTURE_BRC_VBR			1
//#define RV_CAPTURE_BRC_MBR			2

//alarm linkage, be used to very bit-mask with linkage mask value [报警联动动作，用于与报警联动动作掩码进行与、或操作]
#define RV_ALARM_UPLOAD		0x00000001
#define RV_ALARM_RECORD		0x00000002
#define RV_ALARM_PTZ		0x00000004
#define RV_ALARM_MAIL		0x00000008
#define RV_ALARM_TOUR		0x00000010
#define RV_ALARM_TIP		0x00000020
#define RV_ALARM_OUT		0x00000040
#define RV_ALARM_FTP_UL		0x00000080
#define RV_ALARM_BEEP		0x00000100
#define RV_ALARM_VOICE		0x00000200
#define RV_ALARM_SNAP		0x00000400

//"restore default configure" mask, several value can or ["恢复默认设置"掩码，多个设置可用或操作]
#define RV_RESTORE_COMMON			0x00000001	//common configure [普通设置]
#define RV_RESTORE_CODING			0x00000002	//code configure [编码设置]
#define RV_RESTORE_VIDEO			0x00000004	//record configure [录像设置]
#define RV_RESTORE_COMM				0x00000008	//serial port configure [串口设置]
#define RV_RESTORE_NETWORK			0x00000010	//network configure [网络设置]
#define RV_RESTORE_ALARM			0x00000020	//alarm configure [报警设置]
#define RV_RESTORE_VIDEODETECT		0x00000040	//video detect [视频检测]
#define RV_RESTORE_PTZ				0x00000080	//PTZ control [云台控制]
#define RV_RESTORE_OUTPUTMODE		0x00000100	//output mode [输出模式]
#define RV_RESTORE_CHANNELNAME		0x00000200	//channel name [通道名称]
#define RV_RESTORE_ALL				0x80000000	//all reset [全部重置]


////////////////end of constant abount remote configure struct [end of远程配置结构体相关常量]///////////////////////
#define RV_MAX_IPADDR_LEN			16			//max size of IP address string [IP地址字符串长度]
#define RV_MACADDR_LEN				40			//max size of MAC address string [MAC地址字符串长度]
#define RV_DEV_TYPE_LEN				32			//max size of device type string [设备类型字符串长度]

//////////////////////////////////////////////////////////////////////////
//	type for query [查询类型]
typedef enum
{
	EABILITY_WATERMARK_CFG = 17,			//ability of configure watermark [水印配置能力]
	EABILITY_WIRELESS_CFG = 18,			//ability of configure wireless [wireless配置能力]
	EABILITY_DEVALL_INFO = 26,			//abblities of device [设备的能力列表]
	EABILITY_CARD_QUERY = 0x0100,		//ability of query by card No. [卡号查询能力]
	EABILITY_MULTIPLAY = 0x0101,			//ability of multi-view preview [多画面预览能力]
	EABILITY_INFRARED = 0X0121,			//ability of wireless alarm [无线报警能力]
	EABILITY_TRIGGER_MODE = 0x0131,
	EABILITY_SAVIA_COUNT = 33,			//number of SAVIA [SAVIA数目]
	EABILITY_STR_LEN_EN = 35,			//length of string (not 98 serial device) [字符串长度(非98设备)]
	ABBI_TLV = 40,				//using new network protocal ? [是否使用新网络协议]
	ABBI_DECODER,				//ability of decoder [解码器能力--返回结果RV_DECODE_EN]
	ABBI_AUTOREGISTER,			//ability of auto-register [主动注册能力]
	ABBI_SAVIA,					//ability of SAVIA [SAVIA能力]
	ABBI_AUDIOIN,				//ability of audio input [音频输入]
	ABBI_PTZTOUR,				//ability of PTZ soft tour [云台软巡航能力]
	ABBI_TALK,					//ability of talk [对讲能力]
	ABBI_MVIEW,					//ability of combining and spliting views for multi-view preview [多画面预览画面分割组合能力]
	ABBI_SNAP,					//ability of snapshot [抓拍能力]
	ABBI_DEVID,					//device ID [设备ID]
	ABBI_VERSION,				//software version [软件版本]
	ABBI_AUTH_LIST,				//previleges of the current logined user [当前登录用户权限]
	ABBI_SYS_ATTR_EX,			//device attributes [设备属性]
	ABBI_ISTLVPROTOCAL,			//using new network protocal ? [是否使用新网络协议]
	ABBI_IVIDEO,				//ability of platform connection [平台接入能力]
	ABBI_ENCODE,				//ability of code [编码能力]
	ABBI_TIME,					//ability of time [时间能力]
	ABBI_FTP,					//ability of ftp [ftp能力]
	ABBI_WHITEBLACK,			//ability of black and white ip list [黑白名单能力]
	ABBI_DEVTYPE,				//device type [设备类型]
	ABBI_RTSP,					//ability of RTSP [RTSP能力]
	ABBI_AUDIOVALUE,			//ability of audio volumn adjusting [音频音量调节]
	ABBI_RECORD,				//ability of recording [录像能力]---RV_RECORD_EN
	ABBI_KBD,					//ability of key-board for control [控制键盘能力]
	ABBI_MATRIX_XINGHUO,		//ability of matrix(for XINGHUO Corp.) [矩阵(星火)能力]
	ABBI_OSD_ZOOM,				//ability of OSD FONT ZOOM [OSD字体大小]
	ABILITY_AlarmLink = 112,	//报警联动能力
	ABILITY_CAMERA = 129,		//视频采集能力
	ABILITY_OSD_WATERMARK = 125,//数字水印功能
	ABILITY_NEW_NET_OPR	= 130,	//整理新的网络控制操作能力集，
	RV_DEV_ABILITY_ENCODE2 = 131, // 支持码流的能力级--RVENCODE_CAPS_NET2
	DEV_ABILITY_OEM_FUN = 132,	// OEM厂商特殊功能--ABILITY_OEM_FUN_T
	DEV_ABILITY_OSD_MULINE = 135,//多行OSD叠加--ABILITY_MUTILETITLE_T
	DEV_ABILITY_SUPPORT_ALARM = 136,//设备支持的告警类型--ALARM_SUPPORT_ABILITY 
	DEV_ABILITY_INTERVIDEO_LOG = 137,// 平台接入日志查询--ABILITY_INTERVIDEO_LOG_T
	DEV_ABILITY_IPV6 = 138,		//是否支持IPV6--ABILITY_IPV6_T
	DEV_ABILITY_MTU = 139,		// 是否支持MTU设置--ABILITY_MTU_T
	DEV_ABILITY_SUVA = 702,		// 智能能力集-- SUVA_ABILITY
	DEV_ABILITY_3G = 105,		// 3G能力级--NET_WRIELESS
	DEV_ABILITY_SUPPORT_COLOR_TYPE = 703, // 图像颜色风格能力集--COLOR_ABILITY
	ABILITY_PTZ_TOUR = 108,		// 云台软巡航--RV_PTZ_TOUR_EN
	DEV_ABILITY_SUPPORT_SENSOR_TYPE = 704,// 支持分辨率和制式-SENSOR_ABILITY
	DEV_SYSTEM_INFO_SUPERUSER_AUTH = 150,	// 超级用户权限--SUPER_USER_AUTH_LIST
	DEV_ABILITY_SUPERPWD = 0x30000000,		// 是不是超级密码登录--返回int值
} RV_SYS_ABILITY;

//////////////////////////////////////////////////////////////////////////
//	function list supported by device [设备支持功能列表]
enum 
{
	ERV_FTP = 0,						//FTP by bit, 1:send record file 2:send picture file [FTP 按位，1：传送录像文件 2：传送抓图文件]
	ERV_SMTP,							//SMTP by bit, 1:send text e-mail for alarm 2:send picture e-mail for alarm [SMTP 按位，1：报警传送文本邮件 2：报警传送图片]
	ERV_NTP,							//NTP by bit, 1:adjust system time [NTP	按位：1：调整系统时间]
	ERV_AUTO_MAINTAIN,					//auto mantance by bit, 1:reboot 2:shutdown 3:delete files [自动维护 按位：1：重启 2：关闭 3:删除文件]
	ERV_VIDEO_COVER,					//area shelter by bit, 1:multi-area shelter [区域遮挡 按位：1：多区域遮挡]
	ERV_AUTO_REGISTER,					//auto register by bit, 1:sdk login device by initiative after registration [主动注册	按位：1：注册后sdk主动登陆]
	ERV_DHCP,							//DHCP by bit, 1:DHCP [DHCP	按位：1：DHCP]
	ERV_UPNP,							//UPNP by bit, 1:UPNP [UPNP	按位：1：UPNP]
	ERV_COMM_SNIFFER,					//serial port capture package by bit, 1:CommATM [串口抓包 按位：1:CommATM]
	ERV_NET_SNIFFER,					//network capture package by bit, 1:NetSniffer [网络抓包 按位： 1：NetSniffer]
	ERV_BURN,							//function of imprinting by bit, 1:query status of recording [刻录功能 按位：1：查询刻录状态]
	ERV_VIDEO_MATRIX,					//video matrix by bit, 1:surport video matrix ? [视频矩阵 按位：1：是否支持视频矩阵]
	ERV_AUDIO_DETECT,					//audio detect by bit, 1:support audio detect ? [音频检测 按位：1：是否支持音频检测]
	ERV_STORAGE_STATION,				//store position by bit, 1:Ftp server(Ips) 2:Usb storage 3:NFS 4:DISK 5:SBM [存储位置 按位：1：Ftp服务器(Ips) 2：U盘 3：NFS 4：DISK 5：SBM]
	ERV_IPSSEARCH,						//IPS store query by bit, 1:IPS store query [IPS存储查询 按位：1：IPS存储查询]
	ERV_SNAP,							//snapshot by bit, 1:resolve 2:frame rate 3:snapshot method 4:file format of snapshot 5:quality of picture [抓图  按位：1：分辨率2：帧率3：抓图方式4：抓图文件格式5：图画质量]
	ERV_DEFAULTNIC,						//query for default net card supported by bit, 1:support [支持默认网卡查询 按位 1：支持]
	ERV_SHOWQUALITY,					//configure item of picture's display quality under CBR mode, 1:support  [CBR模式下显示画质配置项 按位 1:支持]
	ERV_RTSP,							//RTSP [RTSP]
};

typedef union _IPADDR//IP addr
{	
	unsigned char	c[4];
	unsigned short	s[2];
	unsigned int	l;
}IPADDR;

typedef struct 
{
	UInt32 IsFucEnable[512];				//abbility array of function, and subscript corresponding to enum value above, and sub functions are flags by bits [功能列表能力集,下标对应上述的枚举值,按位表示子功能]
} RV_DEV_ENABLE_INFO;

//////////////////////////////////////////////////////////////////////////
//	ability struct of query by card No. [卡号查询能力结构体]
typedef struct 
{
	char		IsCardQueryEnable;
	char		iRev[3];
} RV_CARD_QUERY_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of configure wireless [wireless能力结构体]
typedef struct 
{
	char		IsWirelessEnable;
	char		iRev[3];
} RV_WIRELESS_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of configure watermark [图象水印能力结构体]
typedef struct 
{
	char		isSupportWM;	//1:support 0:not support [1 支持；0 不支持]
	char		supportWhat;	//0:text watermark 1:picture watermark 2:surport both text and picture watermark [0：文字水印；1：图片水印；2：同时支持文字水印和图片水印]
	char		reserved[2];
} RV_WATERMAKE_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of multi-view preview [多画面预览能力结构体]
typedef struct  
{
	int			nEnable;			//1:support 0:not support [1 支持；0 不支持]
	UInt32		dwMultiPlayMask;	//reserved [保留]
	char		reserved[4];
} RV_MULTIPLAY_EN;

//////////////////////////////////////////////////////////////////////////
//	number of SAVIA struct [SAVIA数目能力结构体]
typedef struct 
{
	UInt32		dwCount;
} RV_SAVIA_COUNT;

typedef struct  
{
	BOOL bSupport;			//support ? [是否支持]
	int	 nAlarmInCount;		//number of alarm in [输入个数]
	int  nAlarmOutCount;	//number of alarm out [输出个数]
	int  nRemoteAddrCount;	//number of remote-control unit [遥控器个数]
	BYTE reserved[32];
}RV_WIRELESS_ALARM_INFO;

//////////////////////////////////////////////////////////////////////////
//	ability struct of PTZ soft tour [云台软巡航能力结构体]--ABILITY_PTZ_TOUR
typedef  struct
{
	unsigned short usPresetNums ;	//max number of presets for every channel [每个通道预置点最大个数]
	unsigned short usTourNums;		//max number of tours for every channel [每个通道最大巡航轨迹个数]
    int iRes [4];					//reserved [保留]
}RV_PTZ_TOUR_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of auto-register [主动注册能力结构体]
typedef  struct
{
	unsigned short usRegServerNums ;	//number of auto-regiser server, just one now [主动注册服务器个数 现有实现为1个]
	unsigned short usNetMode;			//auto-register mode [主动注册模式]
										//support multiple network mode, every bit flags support : 1:support 0:not support [支持多种网络模式 每一位标识是否支持 0标识不支持，1标识支持]
										//bit 0 : single connection of video and commands [第0位 视频和信令单连接]
										//bit 1 : multi-connection(multi-connection of multimedia, support that device connects server to send video data forwardly) [第1位 多连接（媒体多连接，支持设备主动连接服务器发送视频）]
    int iRes [4];						//reserved [保留]
}RV_AUTO_REGISTER_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of decoder [解码器能力结构体]
typedef  struct
{
	unsigned short usDecoderNums ;  //max number of channles [解码器最大路数]
	unsigned short usNetMode;		//support multiple network mode, every bit flags support : 1:support 0:not support [支持多种网络模式 每一位标识是否支持 0标识不支持，1标识支持]
									//bit 0 : common network vs100,vs200, default setted to 1 [第0位 通用网络vs100，vs200；默认此为支持 置1]
									//bit 1 : support rtsp Client [第1位 支持rtsp Client]
									//bit 2 : support vs300  [第2位 支持vs300；]
									//第3位 : sony rtsp
									//第4位 : 黄河rtsp
									//第5位 : 中星贝尔接入
									// 第6位: VIVOTEK接入 
									// 第7位: 三洋接入    
									// 第8位: 三星接入
									// 第9位: 星网锐捷接入    
									// 第10位: 郎驰接入(亚安)
									// 第11位: 亚安YAAN200W

	int iAbilityMask;				//decode abbility for every channel, max 16 channels now, so every 2 bits mark 1 channel in 32 bits [每路解码器解码能力 ，现有最大16通道，32位每2位标识一个通道]
									//00:max support to CIF, 01:max support to D1, 10:max support to 720p, 11:more [00 最大支持CIF，01 最大支持D1，10，最大支持720p, 11 更高]
	unsigned char ucDecoderType; 	//type of decoder [解码器形式]
									//0:mixed type of DVR (both contain analog channels and digital channels), 1:pure decoder(only digital channels) [0混合dvr（既有模拟也可以数字），1纯解码器（只有数字）]
	unsigned char ucModeAblity;		//bit 0 : support multi-connection tour ? [第0位 是否支持多连接轮巡的方式]
	unsigned short  usMaxChNum;		//max number of channels for every supported tour when support multi-connection tour [支持多连接方式时,每路支持的轮巡列表的通道的最大数目]
	unsigned int  uiNetMode2;		//用掉一个保留位，便于扩展接入类型
    char    ucNewType;				// 第0位置1时表示配置采用新的数据结构REMOTE_CH_CFG_2
    char iRes[7];					//保留
}RV_DECODE_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of snapshot [抓拍能力结构体]
typedef struct
{	
    unsigned int type_mask;			//flag by bits : 0-trigger to snapshot 1-timer to snapshot 2-alarm to snapshot [按位表示 0-触发抓拍, 1-定时抓拍, 2-告警抓拍]
	unsigned int uiSnapMaxCount;		//max number of snapshot per second supported [最大支持抓拍张数]
	unsigned int uiCountsPerSecond;	/*how many pictures per second, flag by bits	[1s几张图片，按位表示]
										bit0:1 picture per second [第0位 1s1张]
										bit1:2 picture per second [第1位 1s2张]
										bit2:3 picture per second [第2位 1s3张]
										bit3:4 picture per second [第3位 1s4张]
										bit4:5 picture per second [第4位 1s5张]
										*/					
	unsigned int uiMaxSeconds;			/*max number of seconds per picture supported [最大支持几秒1张]*/
	unsigned int uiMinSeconds;			//最小值几秒一张，如果是0，则默认为最小2秒一张	
	unsigned int uiRes[27];
}RV_ABILITY_SNAP_T;

//////////////////////////////////////////////////////////////////////////
//	ability struct of intelligent [智能模块能力结构体]
typedef struct
{
	unsigned char ucSaviaNums ;		//number of savia [savia数目]
	unsigned char ucSurportAl;		//surpported arithmetics [支持的算法]
	unsigned char ucRes[22];		//reserved [保留]
}RV_SAVIA_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of talk(audio in and audio out) [对讲（对讲音频输入+音频输出）能力结构体]
typedef struct
{
	unsigned char ucSurportTalkIn ;  	//audio input for talk (device has individual audio capture) 
										//[对讲音频输入（设备存在单独的音频采集） 1:支持：0：不支持]
	unsigned char ucTalkInMask;     	//code type of audio input supported, flag by bits 
										//[设备音频输入编码格式类型  按位标识是否支持编码格式]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... 
										//[第0位 是否支持g711a， 第1位 pcm8k16b 第2位 g711u等]
	unsigned char ucSurportTalkOut;		//audio output for talk, 1:support,0:not support 
										//[对讲音频输出   1:支持：0：不支持]
	unsigned char ucTalkOutMask;     	//decode type of audio supported, flag by bits 
										//[设备音频解码格式类型  按位标识是否支持解码格式]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... 
										//[第0位 是否支持g711a， 第1位 pcm8k16b  第2位 g711u等]
}RV_TALK_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of audio input [音频输入能力结构体]
typedef struct
{
	unsigned int uiAudio ;				//bit 0~31 : flag that there are audio input in channel 1~32, 1:input 0:no input [0~31为依次表示通道1~通道32有音频输入 1标识有，0标识]
	unsigned int uiAudioMask ;  		//code type of accompanying sound input, flag by bits [设备伴音编码格式类型  按位标识是否支持编码格式]
										//bit 0 : g711a, 1:pcm8k16b, 2:g711u, etc... [第0位 是否支持g711a， 第1位 pcm8k16b  第2位 g711u等]
}RV_AUDIO_IN_EN;

//////////////////////////////////////////////////////////////////////////
//	ability of combining and spliting views [画面分割组合能力结构体]
#define MAX_SPLIT_COMINE_NUMS 32
#define MAX_SPLITCOMBINE_NUMBER 32
typedef struct
{
	unsigned int iChMask;		 //channel mask, flag by bits, total 32 bits (4 byts)(max 32 types) [通道掩码，按位标识，总32位4字节,最大32种形式]
								 /*for example : 4 views, support mode (1,2,3,4channel)(1,3,4,5channel) [4画面 ，支持 模式（1，2，3，4通道）（1，3，4，5）]
								 corresponding mask is 0000 0000 0000 0000 0000 0000 0000 1111=0x0F [对应的掩码为  0000 0000 0000 0000 0000 0000 0000 1111=0x0F]
								 0000 0000 0000 0000 0000 0000 0001 1101=0x1D [0000 0000 0000 0000 0000 0000 0001 1101=0x1D]
								 if 9 views, support mode (1,2,4,5,6,7,8,9,10channel) [如果9画面 支持（1，2，4，5，6，7，8，9，10通道）]
								 corresponding mask is 0000 0000 0000 0000 0000 0011 1111 1011=0x3FB [对应的掩码为0000 0000 0000 0000 0000 0011 1111 1011=0x3FB]
								 the mask content here, need to decide by uiSplitType in  SPLIT_MODE, and there has include or exclude relation now [此处掩码内容，是需要根据 SPLIT_MODE中uiSplitType来定，现有制定是包含关系还是排除关系]
								 */
	unsigned char ucSpecialCh;	 /*special channel (restrict to be show in the first view or the biggest view) [特殊通道（约束为自动排在最前或者大窗口显示）]*/
	unsigned char ucRes[3];
}RV_SPLIT_COMBINE_CH;
typedef struct
{
	unsigned char ucSplitMode;	/*mode of multi-view preview, reference to enum split_combine_t [多画面预览模式，参考枚举split_combine_t]*/
	unsigned char ucSplitType;  /*supported split views type, every two bits corresponding one bit in iSplitMode [支持分屏组合的类型 ，每两位对应画面预览模式iSplitMode一位]
								0 : all random combine [0 全部任意组合， ]
								if random [如果为任意]
								1 : include relation, just some combines supported, limit to max 64 now [1 包含关系，只有少部分组合组合满足，现有约束最大64个；]
								2 : exclude relation, max 64 combines to exclude [2 排除关系，最大64个排除组合；]
								if it is include or exclude method, the subscript of SPLIT_COMBINE array flag detail infomation [如果是包含或者排除方式，SPLIT_COMBINE数组标示具体信息]
								other : not defined now, reserved [其他 暂无定义，后续扩展使用]
								*/
	unsigned char ucCombinNums;	/*the total number of combine, max to N_SPLIT_COMINE_NUMS 32 now [组合中总个数，现有最大N_SPLIT_COMINE_NUMS 32个]*/
	unsigned char ucRes;
	RV_SPLIT_COMBINE_CH stCombineCh[MAX_SPLIT_COMINE_NUMS];
}RV_SPLIT_COMBINE;

typedef struct
{
	unsigned int iSplitMode;	//supported types of multi-view preview, flag by bits, reference to enum split_combine_t [支持多种画面预览模式，按位标识，参考枚举split_combine_t]
	//bit 0 : SPLIT1 , this is single view and full screen, default supported by all devices [第0位 SPLIT1 此默认都支持，此为单画面，全屏]
	//bit 1 : SPLIT2 [第1位 SPLIT2] 
	//bit 2 : SPLIT4 [第2位 SPLIT4]
	//bit 3 : SPLIT8 [第3位 SPLIT8] 
	//bit 4 : SPLIT9 [第4位 SPLIT9]
	//bit 5 : SPLIT16 [第5位 SPLIT16] 
	//bit 6 : SPLITIP [第6位 SPLITIP]
	//bit 7 : SPLIT6 [第7位 SPLIT6]
	//bit 8 : SPLIT12 [第8位 SPLIT12]
	//bit 9 : SPLIT13
	//bit 10 : SPLIT20
	//bit 11 : SPLIT25
	//bit 12 : SPLIT33
	// bit13 : SPLIT5
	int lCount;				//number of SPLIT_COMBINE [SPLIT_COMBINE的数目]
	RV_SPLIT_COMBINE m_stSplitCombi[MAX_SPLITCOMBINE_NUMBER];//SPLIT_COMBINE数组
}RV_SPLIT_EN;

//////////////////////////////////////////////////////////////////////////
//	the authorities returned by success login [登陆返回的用户权限]
typedef struct
{
	unsigned int uiMonitorMask;
	unsigned int uiPlayMask;
	unsigned int uiNetPreviewMask;
	unsigned int uiControlConfigMask;
	unsigned int uiReserved[4];
}RV_USER_AUTH_LIST;

//////////////////////////////////////////////////////////////////////////
//	attributes of device returned by success login [登陆返回的设备属性]
typedef struct
{
	unsigned char iVideoInCaps;			//number of video input [视频输入接口数量]
	unsigned char iVideoOutCaps;		//number of video output [视频输出接口数量]
	unsigned char iAudioInCaps;			//number of audio input  [音频输入接口数量]
	unsigned char iAudioOutCaps;		//number of video output  [音频输出接口数量]	
	unsigned char iAlarmInCaps;			//number of alarm input  [报警输入接口数] 
	unsigned char iAlarmOutCaps;		//number of alarm output  [报警输出接口数]
	unsigned char iDiskNum;				//number of used disk  [实际使用硬盘数]
	unsigned char iAetherNetPortNum;	//number of network interface [网络接口数]	
	unsigned char iUsbPortNum;          //number of USB interface [USB接口数]
	unsigned char iDecodeChanNum;		//number of local decode(replay) [本地解码(回放)路数] 
	unsigned char iComPortNum;			//number of serial port [串口数]
	unsigned char iParallelPortNum;		//number of parallel port [并口口数]	
	unsigned char iSpeechInCaps;		//number of talk input [对讲输入接口数量]
	unsigned char iSpeechOutCaps;		//number of talk output [对讲输出接口数量]
	unsigned char bRes[2];				//reserved [保留]
}RV_SYSATTR_EX_T;

//////////////////////////////////////////////////////////////////////////
//ability struct of platform connection [平台接入能力结构体]
typedef struct
{
	int iIVideoMask;//mask of supported platform[支持平台的掩码]
					//bit0：[BELL]
					//bit1：[HXHT]
					//bit2：[VS300]
					//bit3：[神眼平台]
					//bit4：[BELL网通平台]
					//bit5：[公安一所]
					//bit6：[神眼]
					//bit7：[VISS]
					//bit8: [BELL30]
					//bit9: [蓝色星际]
					//bit10:[豪威]
	int iRes[3];
}RV_IVIDEO_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of code [编码能力结构体]
typedef struct
{
	unsigned int	uiMaxEncodePower;				//highest code ability supported [产品支持的最高编码能力]
	unsigned short	usSupportChannel;				//max number of video input supported per DSP [每块 DSP 支持最多输入视频通道数 ]
	unsigned short	usChannelSetSync;				//congiure of max code is or isn't be sync per DSP, 0-not be sync, 1-be sync [DSP 每通道的最大编码设置是否同步 0-不同步, 1-同步]
													//bit-stream situation supported per channel [每一通道支持码流情况]
	unsigned char	ucVideoStandardMask;			//video standard mask, flag by bits that it supports which standard, bit0-PAL, bit1-NTSC [视频制式掩码，按位表示设备能够支持的视频制式 0 PAL 1 NTSC]
	unsigned char	ucEncodeModeMask;				//mask of code mode, flag by bits that the code modes device supported, 0-VBR,1-CBR [编码模式掩码，按位表示设备能够支持的编码模式设置 ，0 VBR，1 CBR]
	unsigned short	usStreamCap;					//flag by bits that the media functions device supported [按位表示设备支持的多媒体功能，]
													//bit0 : support main stream [第一位表示支持主码流]
													//bit1 : support assist stream-1 [第二位表示支持辅码流1]
													//bit2 : support snapshot jpg file, and the snapshot function is defined in other place, so not add it here [第三位表示支持jpg抓图，捉图功能另外定义，在此不加入]
	unsigned int	uiImageSizeMask;				//mask of main stream, the enum reference to capture_size_t [主码流编码掩码 枚举按照capture_size_t ]
	unsigned int	uiImageSizeMask_Assi[32];		//code modes supported by assist stream while main stream is diffrent code mode, for example [主码流取不同的编码时候，辅码流支持的编码格式，例如, ]
													//uiImageSizeMask_Assi【0】is that, the code modes supported by assist stream when code mode of main stream is CAPTURE_SIZE_D1 [uiImageSizeMask_Assi【0】表示主码流是CAPTURE_SIZE_D1时，辅码流支持的编码格式，]
													//uiImageSizeMask_Assi【1】is that, the code modes supported by assist stream when code mode of main stream is CAPTURE_SIZE_HD1 [uiImageSizeMask_Assi【1】表示主码流是CAPTURE_SIZE_HD1时，辅码流支持的编码格式。。。]
	unsigned char	ucSupportPolicy;				//if support special code mode, 0-not support 1-support [是否支持特殊编码策略 0 不支持 1 支持]
	unsigned char	ucCompression;					//按位表示，第0位表示是否支持264，第1位表示是否支持svac
	unsigned char   ucRebootType;					//如果等于1时，配置主码流HD1，辅码流CIF需要重启设备
	unsigned char   ucEncoderDetect;				// 码流检查  0 不支持 1 支持(自动维护中无码流重启功能)
	unsigned char	ucRes[8];						// 保留
}RV_ENCODE_CAPS_NET_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of time [时间能力结构体]
typedef struct
{
	unsigned char ucSupTimeAdjust;  //if support timing function [是否支持校时功能]
									//operate by bits [按位操作]
									//bit0 : Dst support daylight saving time [第0位 Dst 支持夏令时]
									//bit1 : SNTP(udp:123), default is this ntp now [第一位 SNTP（udp ：123）， 现在默认是此ntp]
									//bit2 : NTP(udp:37,tcp:37) [第二位 NTP（udp：37，tcp：37）]
	unsigned char ucRes[11];		//reserved [保留]
}RV_TIME_EN;

//////////////////////////////////////////////////////////////////////////
//	ability struct of ftp [ftp能力结构体]
typedef struct
{
	unsigned char ucSupFtp; //operate by bits [按位操作]
							//bit0 : support upload record file by ftp [支持ftp录像上传]
							//bit1 : support upload picture file by ftp [支持ftp图片上传]							
	unsigned char ucRes[15];//reserved [保留]
}RV_FTP_EN;

//////////////////////////////////////////////////////////////////////////
//ability struct of black and white ip list [黑白名单能力结构体]
typedef struct  
{
	unsigned short	usMaxBlackNums;	//max number of black ip [最大黑名单数目]
	unsigned short	usMaxWhiteNums;	//max number of white ip [最大白名单数目]
	unsigned int	res[12];		//reserved [保留]
}RV_WHITEBLACK_EN;

//////////////////////////////////////////////////////////////////////////
//   ability struct of audio volumn [音量能力结构体]
typedef struct
{	
    unsigned int uiAudioVolumn ;   //bit 0~31 flag that if the channel support audio volumn adjust, and the ability of if the channel has audio input reference to AUDIO_IN_ABILITY [0~31为依次表示通道~通道音频输入支持音量控制,音频输入"有无"能力集参考AUDIO_IN_ABILITY]
    unsigned char ucTalk;           //bit0 flag that if audio input of talk support volumn adjust, and the ability of if audio input of talk reference to TALK_ABILITY [第0位表示对讲输入音频支持音量控制,对讲音频输入"有无"能力集参考TALK_ABILITY]
									//bit1 flag that if audio output of talk support volumn adjust, and the ability of if audio output of talk reference to TALK_ABILITY [第1位表示对讲输出音频支持音量控制和静音,对讲音频输出"有无"能力集参考TALK_ABILITY]
									//bit2 flag that if audio input of talk support input by MIC [第2位表示对讲输入音频支持MIC输入]
									//bit3 flag that if audio input of talk support input by Liner [第3位表示对讲输入音频支持Liner输入]
    unsigned char ucAudioChannel;   //the channels of audio input, 1-single 2-double [音频输入的声道，1：单声道；2：双声道 ]
    unsigned char ucRes;			
    unsigned char ucAudioOutChannel;//the channels of audio output of talk, 1-single 2-double [音频输出(对讲输出)的声道，1：单声道；2：双声道] 
    unsigned int uiRes[14];	
}RV_AUDIOVALUE_EN;

/////////////////////////////////////////////////////////////////////////
//	ability struct of rtsp [rtsp能力结构体]
typedef struct  
{
	unsigned char ucAbilty;//bit0:if support real-time watch by rtsp; bit1:if support record replay by rtsp [第1位表示是否支持rtsp实时监视，第2位表示是否支持rtsp录像回放]
	unsigned char Res[31] ;//reserved [保留]
}RV_RTSP_EN;

/////////////////////////////////////////////////////////////////////////
//	length of string struct (not 98 serial device) [非98设备字符串长度能力结构体]
typedef struct  
{
	unsigned short usPPPoeNameLen;	//user name length (contain null character) [用户名长度（包括null字符）]
	unsigned short usPPPoePwdLen;	//password length (contain null character) [密码长度（包括null字符）]
	unsigned short usRes[30] ;		//reserved [保留]
}RV_STR_LEN_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of recording [录像相关能力结构体]
typedef struct
{
    unsigned int dwFlag;//第0位表示支持新的“录像控制”协议    第1位表示是否上报最长 预录时间
    unsigned char ucSupportCardRecord;//支持卡号录像，0不支持，1支持
    unsigned char ucRes1[1];
    unsigned short usPreRecordTime;;//预录时间，单位秒
    unsigned char ucRes2[12];
}RV_RECORD_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of key-board for control [控制键盘能力结构体]
enum
{
	KBDFunc_PTZ_RAW_DATA_IN = 0,	//clarity serial port, clarity tranport PTZ commands [透明串口,云台控制命令的透明传输]
	KBDFunc_RVKBD = 1,				//key-board protocal of visiondigi [威乾键盘协议]
	KBDFunc_HK = 2,					// 海康键盘协议
};
typedef  struct
{
	unsigned char ucAbilty;		//if support key-board control [是否支持控制键盘]
	unsigned char ucSupport;	//supported protocals : bit0-PTZ clarity channel, bit1-key-board protocal of visiondigi, reference to KBDFunc [支持的协议:第0位表示云台透明通道,第1位表示威乾控制键盘,参考KBDFunc]
	unsigned char ucRes[14] ;	//reserved [保留]
}RV_KBD_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of matrix(for XINGHUO Corp.) [矩阵(星火)能力结构体]
typedef struct 
{
	unsigned int uiMatrixInNum;//max matrix input number, 128 now, if device not support maxtrix for XINGHUO, this value is 0 [支持矩阵输入路数，目前为128，不支持星火矩阵的设备，该值为0]
	unsigned int reserve[3];
}RV_MATRIX_XINGHUO_EN;

//////////////////////////////////////////////////////////////////////////
//      ability struct of OSD Zoom [OSD字体大小能力结构体]
typedef struct  
{
	unsigned char ucZoomAbility;  //1表示最大支持1倍缩放，2表示最大支持2倍缩放，以此类推，便于扩展。目前720P设备为2，其他设备为1
	unsigned char ucRes[3];
}RV_OSD_ZOOM_EN;

typedef struct _SABILITY_AlarmLink
{
	/* 消息处理方式,可以同时多种处理方式,包括
	* 0x00000001 - 网络:上传管理服务器
	* 0x00000002 - 录像:触发
	* 0x00000004 - 云台联动
	* 0x00000008 - 发送邮件
	* 0x00000010 - 设备本地报警轮巡
	* 0x00000020 - 设备提示使能
	* 0x00000040 - 设备报警输出使能
	* 0x00000080 - Ftp上传使能
	* 0x00000100 - 蜂鸣
	* 0x00000200 - 语音提示
    * 0x00000400 - 抓图使能*/
	
    /*当前报警所支持的处理方式，按位掩码表示*/
    unsigned int dwActionMask;
    unsigned int reserve[31];
}SABILITY_AlarmLink;

//configure file type, for SDK_ExportConfigFile interface [配置文件类型，供SDK_ExportConfigFile接口使用]
typedef enum __RV_CONFIG_FILE_TYPE
{
	RV_CONFIGFILE_ALL = 0,						//all configure file [全部配置文件]
	RV_CONFIGFILE_LOCAL,						//local configure file [本地配置文件]
	RV_CONFIGFILE_NETWORK,						//network configure file [网络配置文件]
	RV_CONFIGFILE_USER,							//user configure file [用户配置文件]
} RV_CONFIG_FILE_TYPE;

//网络信息结构：
typedef struct _SDeviceNetInfo 
{ 
	char szIPAddr[128];           // 本机IP地址,例如：192.168.1.100 
	char szInetMask[64];          // 子网掩码 
	char szGateway[64];           // 网关 
	char szMajorDns[64];          // 主DNS 
	char szMinorDns[64];          // 辅助DNS 
	unsigned short  nCfgPort;        //配置端口,对应我们的TCP端口
	unsigned short  nDataPort;       //数据端口，对应我们的UDP端口
	unsigned short  nWebport;        //WEB端口
	unsigned char   reserved[62];    //保留字段，作字节对齐用
}SDeviceNetInfo;

//corresponding SDK_SearchDevices interface [对应SDK_SearchDevices接口]
typedef struct 
{
	char				szIP[RV_MAX_IPADDR_LEN];		//IP [IP]
	int					nPort;							//port [端口]
	char				szSubmask[RV_MAX_IPADDR_LEN];	//sub net mask [子网掩码]
	char				szGateway[RV_MAX_IPADDR_LEN];	//gateway [网关]
	char				szMac[RV_MACADDR_LEN];			//MAC address [MAC地址]
	char				szDeviceType[RV_DEV_TYPE_LEN];	//device type [设备类型]
	BYTE				bReserved[32];					//reserved [保留字节]
} RVDEVICE_NET_INFO;

//set params on logining [设置登入时的相关参数]
typedef struct  
{
	int					nWaittime;				//wait time-out time (unit:millisecond), 0 means default 500ms [等待超时时间(毫秒为单位)，为0默认5000ms]
	int					nConnectTime;			//connect time-out time (unit:millisecond), 0 means default 1500ms [连接超时时间(毫秒为单位)，为0默认1500ms]
	int					nConnectTryNum;			//try to connect times, 0 means 1 time [连接尝试次数，为0默认1次]
	int					nSubConnectSpaceTime;	//wait time between sub connection (unit:millisecond), 0 means default 10ms [子连接之间的等待时间(毫秒为单位),为0默认10ms]
	int					nGetDevInfoTime;		//get device info time-out time (unit:millisecond), 0 means default 500ms [获取设备信息超时时间，为0默认500ms.]
	int					nConnectBufSize;		//buffer size per connection (unit:byte), 0 means default 250*1024 [每个连接接收数据缓冲大小(字节为单位)，为0默认250*1024]
	BYTE				bReserved[28];			//reserved [保留字段]
} RVNET_PARAM;

//common PTZ control commands [通用云台控制命令]
typedef enum
{
	RV_PTZ_UP_CONTROL = 0,			//up [上]
	RV_PTZ_DOWN_CONTROL,			//down [下]
	RV_PTZ_LEFT_CONTROL,			//left [左]
	RV_PTZ_RIGHT_CONTROL,			//right [右]
	RV_PTZ_ZOOM_ADD_CONTROL,		//zoom+ [变倍+]
	RV_PTZ_ZOOM_DEC_CONTROL,		//zoom- [变倍-]
	RV_PTZ_FOCUS_ADD_CONTROL,		//focus+ [调焦+]
	RV_PTZ_FOCUS_DEC_CONTROL,		//focus- [调焦-]
	RV_PTZ_APERTURE_ADD_CONTROL,	//aperture+ [光圈+]
	RV_PTZ_APERTURE_DEC_CONTROL,    //aperture- [光圈-]
	RV_PTZ_POINT_MOVE_CONTROL,      //move to preset [转至预置点]
	RV_PTZ_POINT_SET_CONTROL,       //set [设置]
	RV_PTZ_POINT_DEL_CONTROL,       //delete [删除]
	RV_PTZ_POINT_LOOP_CONTROL,      //tour in presets [点间巡航]
	RV_PTZ_LAMP_CONTROL             //lamp and wiper [灯光雨刷]
}RV_PTZ_ControlType;

//common PTZ control extended commands [云台控制扩展命令]
typedef enum
{
	RV_EXTPTZ_LEFTTOP = 0X20,		//left-up [左上]
	RV_EXTPTZ_RIGHTTOP ,			//right-up [右上]
	RV_EXTPTZ_LEFTDOWN ,			//left-down [左下]
	RV_EXTPTZ_RIGHTDOWN,			//right-down [右下]
	RV_EXTPTZ_ADDTOLOOP,			//add preset to tour : tour : preset [加入预置点到巡航	巡航线路	预置点值]	
	RV_EXTPTZ_DELFROMLOOP,			//delete preset from tour : tour : preset [删除巡航中预置点	巡航线路	预置点值]	
	RV_EXTPTZ_CLOSELOOP,			//cleat tour : tour [清除巡航	巡航线路]
	RV_EXTPTZ_STARTPANCRUISE,		//start horizontal rotate [开始水平旋转]			
	RV_EXTPTZ_STOPPANCRUISE,		//stop horizontal rotate [停止水平旋转]			
	RV_EXTPTZ_SETLEFTBORDER,		//set left bound [设置左边界]			
	RV_EXTPTZ_SETRIGHTBORDER,		//set right bound [设置右边界]			
	RV_EXTPTZ_STARTLINESCAN,		//start line scan [开始线扫]			
	RV_EXTPTZ_CLOSELINESCAN,		//stop line scan [停止线扫]			
	RV_EXTPTZ_SETMODESTART,			//start set mode : mode [设置模式开始	模式线路]		
	RV_EXTPTZ_SETMODESTOP,			//stop set mode : mode [设置模式结束	模式线路]		
	RV_EXTPTZ_RUNMODE,				//run mode : mode [运行模式	模式线路]		
	RV_EXTPTZ_STOPMODE,				//stop mode : mode [停止模式	模式线路]		
	RV_EXTPTZ_DELETEMODE,			//cleat mode : mode [清除模式	模式线路]		
	RV_EXTPTZ_REVERSECOMM,			//overturn command [翻转命令]			
	RV_EXTPTZ_FASTGOTO,				//fast locate : horizontal coordinate (8192) : vertical coordinate (8192) : zoom (4) [快速定位	水平坐标(8192)	垂直坐标(8192)	变倍(4)]
	RV_EXTPTZ_AUXIOPEN,				//assist switch open : assist point [辅助开关开	辅助点]	
	RV_EXTPTZ_AUXICLOSE,			//assist switch close : assist point [辅助开关关	辅助点]
	RV_EXTPTZ_OPENMENU = 0X36,		//open menu of PTZ cameral [打开球机菜单]
	RV_EXTPTZ_CLOSEMENU ,			//close menu [关闭菜单]
	RV_EXTPTZ_MENUOK,				//confirm on menu [菜单确定]
	RV_EXTPTZ_MENUCANCEL,			//cancel on menu [菜单取消]
	RV_EXTPTZ_MENUUP,				//up on menu [菜单上]
	RV_EXTPTZ_MENUDOWN,				//down on menu [菜单下]
	RV_EXTPTZ_MENULEFT,				//left on menu [菜单左]
	RV_EXTPTZ_MENURIGHT,			//right on menu [菜单右]
	RV_EXTPTZ_ALARMHANDLE = 0x40,	//alarm linkage PTZ, param1:alarm-in channel, param2:alarm linkage type, 1-preset,2-line scan,3-tour, param3:linkage value, for example:preset number [报警联动云台 parm1:报警输入通道 parm2:报警联动类型1-预置点2-线扫3-巡航 parm3:联动值，如预置点号]
	RV_EXTPTZ_MATRIXSWITCH = 0x41,	//matrix switch, patam1:watcher number(video out number), param2:(video in number), param3:matrix number [矩阵切换 parm1:监视器号(视频输出号) parm2:(视频输入号) parm3:矩阵号]
	RV_EXTPTZ_LIGHTCONTROL,			//lamp controler [灯光控制器]
	RV_EXTPTZ_UP_TELE = 0x70,		//up + TELE, param1=speed(1-8), the same as next [上 + TELE，param1=速度（1-8），下同]
	RV_EXTPTZ_DOWN_TELE,			//down + TELE [下 + TELE]
	RV_EXTPTZ_LEFT_TELE,			//left + TELE [左 + TELE]
	RV_EXTPTZ_RIGHT_TELE,			//right + TELE [右 + TELE]
	RV_EXTPTZ_LEFTUP_TELE,			//left-up + TELE [左上 + TELE]
	RV_EXTPTZ_LEFTDOWN_TELE,		//left-down + TELE [左下 + TELE]
	RV_EXTPTZ_TIGHTUP_TELE,			//right-up + TELE [右上 + TELE]
	RV_EXTPTZ_RIGHTDOWN_TELE,		//right-down + TELE [右下 + TELE]
	RV_EXTPTZ_UP_WIDE,				//up + WIDE,param1=speed(1-8), the same as next [上 + WIDE，param1=速度（1-8），下同]
	RV_EXTPTZ_DOWN_WIDE,			//down + WIDE [下 + WIDE]
	RV_EXTPTZ_LEFT_WIDE,			//left + WIDE [左 + WIDE]
	RV_EXTPTZ_RIGHT_WIDE,			//right + WIDE [右 + WIDE]
	RV_EXTPTZ_LEFTUP_WIDE,			//left-up + WIDE [左上 + WIDE]
	RV_EXTPTZ_LEFTDOWN_WIDE,		//left-down + WIDE [左下 + WIDE]
	RV_EXTPTZ_TIGHTUP_WIDE,			//right-up + WIDE [右上 + WIDE]
	RV_EXTPTZ_RIGHTDOWN_WIDE,		//right-down + WIDE [右下 + WIDE]
	RV_EXTPTZ_TOTAL,				//max command value [最大命令值]
	RV_EXTPTZ_RESET,				//reset [复位]
}RV_EXTPTZ_ControlType;

//IO control command [IO控制命令]
typedef enum
{
	RV_ALARMINPUT = 1,			//alarm input [报警输入]
	RV_ALARMOUTPUT = 2,			//alarm output [报警输出]

	RV_DECODER_ALARMOUT = 3,	//alarm decoder output [报警解码器输出]
	RV_WIRELESS_ALARMOUT =5,    //wireless alarm output [无线报警输出]
	RV_ALARM_TRIGGER_MODE = 7,
}RV_IOTYPE;

//params of extended interface for query log : log type [查询日志扩展接口参数：设备日志类型]
typedef enum _RV_LOG_QUERY_TYPE
{
	RVLOG_ALL = 0,		//all log [所有日志]
	RVLOG_SYSTEM,		//system log [系统日志]
	RVLOG_CONFIG,		//configure log [配置日志]
	RVLOG_STORAGE,		//store log [存储相关]
	RVLOG_ALARM,		//alarm log [报警日志]
	RVLOG_RECORD,		//record log [录象相关]
	RVLOG_ACCOUNT,		//account log [帐号相关]
	RVLOG_CLEAR,		//clear log [清除日志]
	RVLOG_PLAYBACK		//replay log [回放相关]
}RV_LOG_QUERY_TYPE;

//log infomation struct returned - log type [返回的日志信息结构体－日志类型]
typedef enum _RV_LOG_TYPE
{
	//system logs
	RV_LOG_REBOOT = 0x0000,
	RV_LOG_SHUT,
	//config logs
	RV_LOG_CONFSAVE = 0x0100,
	RV_LOG_CONFLOAD,
	//fs logs
	RV_LOG_FSERROR = 0x0200,   //error in file system [文件系统错误]
	RV_LOG_HDD_WERR,           //error in disk writing [硬盘写错误]
	RV_LOG_HDD_RERR,           //error in disk reading[硬盘读错误]
	RV_LOG_HDD_TYPE,           //set disk type [设置硬盘类型]
	RV_LOG_HDD_FORMAT,         //format disk [格式化硬盘]
	//alarm logs
	RV_LOG_ALM_IN = 0x0300,
	RV_LOG_ALM_END = 0x0302,
	RV_LOG_INFRAREDALM_IN = 0x03a0, //wireless alarm input [无线报警输入]
	RV_LOG_INFRAREDALM_END,			//wireless alarm end [无线报警结束]
	//record
	RV_LOG_MANUAL_RECORD = 0x0401,
	RV_LOG_CLOSED_RECORD,
	//user manager
	RV_LOG_LOGIN = 0x0500,
	RV_LOG_LOGOUT,
	RV_LOG_ADD_USER,
	RV_LOG_DELETE_USER,
	RV_LOG_MODIFY_USER,
	RV_LOG_ADD_GROUP,
	RV_LOG_DELETE_GROUP,
	RV_LOG_MODIFY_GROUP,
	//clear
	RV_LOG_CLEAR = 0x0600,
	RV_LOG_TYPE_NR = 7,
}RV_LOG_TYPE;

typedef enum _RV_RESET_TYPE
{	
	DEFAULT_CFG_GENERAL = 0,		
	DEFAULT_CFG_ENCODE,
	DEFAULT_CFG_RECORD,		
	DEFAULT_CFG_COMM,		
	DEFAULT_CFG_NET,		
	DEFAULT_CFG_ALARM = 5,		
	DEFAULT_CFG_DETECT,		
	DEFAULT_CFG_PTZ,		
	DEFAULT_CFG_AUT,		
	DEFAULT_CFG_CHANTITLE = 9,		
	DEFAULT_CFG_EXCEP,		
	DEFAULT_CFG_IVIDEO,
	DEFAULT_CFG_ALL = 31,		
	DEFAULT_CFG_END,		
}_RV_RESET_TYPE;

//log infomation struct returned by interface SDK_QueryLogEx - log type [接口SDK_QueryLogEx返回的日志信息结构体－日志类型]
//condition:int nType = 1;param reserved = &nType. [条件：int nType = 1;参数reserved = &nType.]
typedef enum _RV_NEWLOG_TYPE
{
	//system logs
	RV_NEWLOG_REBOOT	 = 0x0000,		//system reboot [系统重启]
	RV_NEWLOG_SHUT,						//system shutdown [系统关机]

	//config logs
	RV_NEWLOG_CONFSAVE = 0x0100,
	RV_NEWLOG_CONFLOAD,

	//fs logs
	RV_NEWLOG_FSERROR	 = 0x0200,		//error in file system [文件系统错误]
	RV_NEWLOG_HDD_WERR,					//error in disk writing [硬盘写错误]
	RV_NEWLOG_HDD_RERR,					//error in disk reading [硬盘读错误]
	RV_NEWLOG_HDD_TYPE,					//set disk type [设置硬盘类型]
	RV_NEWLOG_HDD_FORMAT,				//format disk [格式化硬盘]
	RV_NEWLOG_HDD_NOSPACE,				//current work space not enough [当前工作盘空间不足]

	//alarm logs
	RV_NEWLOG_ALM_IN	 = 0x0300,
	RV_NEWLOG_NETALM_IN,
	RV_NEWLOG_ALM_END,
	RV_NEWLOG_LOSS_IN,
	RV_NEWLOG_LOSS_END,

	//record
	RV_NEWLOG_AUTOMATIC_RECORD = 0x0400,
	RV_NEWLOG_MANUAL_RECORD,
	RV_NEWLOG_CLOSED_RECORD,

	//user manager
	RV_NEWLOG_LOGIN    = 0x0500,
	RV_NEWLOG_LOGOUT,
	RV_NEWLOG_ADD_USER,
	RV_NEWLOG_DELETE_USER,
	RV_NEWLOG_MODIFY_USER,
	RV_NEWLOG_ADD_GROUP,
	RV_NEWLOG_DELETE_GROUP,
	RV_NEWLOG_MODIFY_GROUP,

	//clear
	RV_NEWLOG_CLEAR    = 0x0600,
	RV_NEWLOG_SEARCHLOG,				//query log [查询日志]

	//record operation
	RV_NEWLOG_SEARCH	 = 0x0700,		//record query [录像查询]
	RV_NEWLOG_DOWNLOAD,					//record download [录像下载]
	RV_NEWLOG_PLAYBACK,					//record replay [录像回放]
	RV_NEWLOG_BACKUP,					//backup record file [/*!< 备份录像文件 */]
	RV_NEWLOG_BACKUPERROR,				//backup record file fail [/*!< 备份录像文件失败 */]

	RV_NEWLOG_TYPE_NR = 8,		
}RV_NEWLOG_TYPE;


//added params of extended interface for real-time preview : preview type [实时预览扩展接口增加的参数：预览类型]
typedef enum
{
	RV_RType_Realplay = 0,	//real-time preview [实时预览]
	RV_RType_Multiplay,		//multi-views preview [多画面预览]

	RV_RType_Realplay_0,	//real-time watch - main stream, the same as RV_RType_Realplay [实时监视-主码流，等同于RV_RType_Realplay]
	RV_RType_Realplay_1,	//real-time watch - assist stream1 [实时监视-从码流1]
	RV_RType_Realplay_2,	//real-time watch - assist stream2 [实时监视-从码流2]
	RV_RType_Realplay_3,	//real-time watch - assist stream3 [实时监视-从码流3]

	RV_RType_Multiplay_1,	//multi-views preview : 1 view[多画面预览－1画面]
	RV_RType_Multiplay_4,	//multi-views preview : 4 view[多画面预览－4画面]
	RV_RType_Multiplay_8,	//multi-views preview : 8 view[多画面预览－8画面]
	RV_RType_Multiplay_9,	//multi-views preview : 6 view[多画面预览－9画面]
	RV_RType_Multiplay_16,	//multi-views preview : 16 view[多画面预览－16画面]

	RV_RType_Multiplay_6,	//multi-views preview : 6 view[多画面预览－6画面]
	RV_RType_Multiplay_12,	//multi-views preview : 12 view[多画面预览－12画面]
} RV_RealPlayType;

//params of interface for device control : control type define [设备控制接口参数：控制类型定义]
typedef enum
{
	RV_CTRL_REBOOT = 0,	//reboot device [重启设备]
	RV_CTRL_SHUTDOWN,	//shutdown device [关闭设备]
	RV_CTRL_DISK,		//disk manage [硬盘管理]
	//network key-board [网络键盘]
	RV_KEYBOARD_POWER = 3,
	RV_KEYBOARD_ENTER,
	RV_KEYBOARD_ESC,
	RV_KEYBOARD_UP,
	RV_KEYBOARD_DOWN,
	RV_KEYBOARD_LEFT,
	RV_KEYBOARD_RIGHT,
	RV_KEYBOARD_BTN0,
	RV_KEYBOARD_BTN1,
	RV_KEYBOARD_BTN2,
	RV_KEYBOARD_BTN3,
	RV_KEYBOARD_BTN4,
	RV_KEYBOARD_BTN5,
	RV_KEYBOARD_BTN6,
	RV_KEYBOARD_BTN7,
	RV_KEYBOARD_BTN8,
	RV_KEYBOARD_BTN9,
	RV_KEYBOARD_BTN10,
	RV_KEYBOARD_BTN11,
	RV_KEYBOARD_BTN12,
	RV_KEYBOARD_BTN13,
	RV_KEYBOARD_BTN14,
	RV_KEYBOARD_BTN15,
	RV_KEYBOARD_BTN16,
	RV_KEYBOARD_SPLIT,
	RV_KEYBOARD_ONE,
	RV_KEYBOARD_NINE,
	RV_KEYBOARD_ADDR,
	RV_KEYBOARD_INFO,
	RV_KEYBOARD_REC,
	RV_KEYBOARD_FN1,
	RV_KEYBOARD_FN2,
	RV_KEYBOARD_PLAY,
	RV_KEYBOARD_STOP,
	RV_KEYBOARD_SLOW,
	RV_KEYBOARD_FAST,
	RV_KEYBOARD_PREW,
	RV_KEYBOARD_NEXT,
	RV_KEYBOARD_JMPDOWN,
	RV_KEYBOARD_JMPUP,
	RV_TRIGGER_ALARM_IN = 100,	//trigger alarm [触发报警]
	RV_TRIGGER_ALARM_OUT,
	RV_CTRL_MATRIX,				//matrix control [矩阵控制]
	//SD card control(ipc products), params are same as disk control [SD卡控制（ipc产品）参数同硬盘控制]
	RV_CTRL_SDCARD,

	//imprinting control [刻录机控制]
	RV_BURNING_START,		//start imprinting [开始刻录]
	RV_BURNING_STOP,		//stop imprinting [结束刻录]

	RV_BURNING_ADDPWD,	//overprint password (string end with 0, max size 8 bytes) [叠加密码(以0为结尾的字符串,最大长度8位)]
	RV_BURNING_ADDHEAD,	//overprint head leader (string end with 0, max size 1024 bytes, support multi-lines, line seperator is '\n') [叠加片头(以0为结尾的字符串,最大长度1024字节,支持分行,行分隔符'\n')，]
	RV_BURNING_ADDSIGN,	//overprint dot to imprinting (no params) [叠加打点到刻录信息(参数无)]
	RV_BURNING_ADDCURSTOMINFO,	//self define overprint (string end with 0, max size 1024 bytes, support multi-lines, line seperator is '\n') [自定义叠加(以0为结尾的字符串,最大长度1024字节,支持分行,行分隔符'\n')]

	
	RV_CTRL_RESTOREDEFAULT,	//restore device's efault configure [恢复设备的默认设置]

	//device tigger DSP snapshot [设备触发DSP抓图]
	RV_CTRL_CAPTURE_START,		//trigger device snapshot [触发设备抓图]

	//cleat log [清除日志]
	RV_CTRL_CLEARLOG,

	RV_CTRL_REV_SNAP_PICTURE,	// 参数为int*按位表示需要接收的定时抓图的回传---SCtrlRevSnap

	//wireless alarm [无线报警]
	RV_TRIGGER_ALARM_WIRELESS = 200,
}RVCtrlType;

//configure type, the interface which using this enum has been die out, not use please [配置类型，目前使用该枚举的接口已淘汰，请不要使用]
typedef enum
{
	ECFG_GENERAL =  0,		//common [普通]
	ECFG_COMM   		,		//serial port [串口]
	ECFG_NET    		,		//network [网络]
	ECFG_RECORD 		,		//record [录像]
	ECFG_CAPTURE		,		//picture configure [图像设置]
	ECFG_PTZ    		,		//PTZ [云台]
	ECFG_DETECT 		,		//motion detect [动态检测]
	ECFG_ALARM  		,		//alarm [报警]
	ECFG_DISPLAY		,		//display [显示]
	ECFG_RESERVED	,		//reserved,  for continuity [保留，使类型连贯]
	ECFG_TITLE  		=10,	//channel title [通道标题]
	ECFG_MAIL  		=11,	//emial function [邮件功能]
	ECFG_EXCAPTURE	=12,	//preview picture configure [预览图像设置]
	ECFG_PPPOE		=13,	//pppoe configure [pppoe设置]
	ECFG_DDNS		=14,	//DDNS configure [DDNS设置]
	ECFG_SNIFFER		=15,	//network watch capture configure [网络监视捕获设置]
	ECFG_DSPINFO		=16,	//code ability infomation [编码能力信息]
	ECFG_COLOR		=126,	//color cofigure infomation [颜色配置信息]
	ECFG_ALL,				//reserved [保留]
} ECFG_INDEX;

typedef enum
{
	ESNAP_TYP_TIMING = 0,
	ESNAP_TYP_ALARM,
	ESNAP_TYP_NUM,
} ESNAP_TYPE;

//resolve enum, for RV_DSP_ENCODECAP using [分辨率枚举，供RV_DSP_ENCODECAP使用]
typedef enum
{
	ECAPTURE_SIZE_D1,				// <  704*576(PAL)  704*480(NTSC)
	ECAPTURE_SIZE_HD1,				// <  704*288(PAL)  704*240(NTSC)
	ECAPTURE_SIZE_BCIF,				// <  352*576(PAL)  352*480(NTSC)
	ECAPTURE_SIZE_CIF,				// <  352*288(PAL)  352*240(NTSC)
	ECAPTURE_SIZE_QCIF,				// <  176*144(PAL)  176*120(NTSC)
	ECAPTURE_SIZE_VGA,				// <  640*480
	ECAPTURE_SIZE_QVGA,				// <  320*240
	ECAPTURE_SIZE_SVCD,				// <  480*480
	ECAPTURE_SIZE_QQVGA,			// <  160*128
	ECAPTURE_SIZE_720P	= 9,		// <  1280*720	720P
	ECAPTURE_SIZE_1080P	= 10,		// <  1920*1080	1080P
	ECAPTURE_SIZE_SVGA,				// <  800*592
	ECAPTURE_SIZE_XVGA,				// <  1024*768	VGA input code, 2800 serial device need [VGA输入编码，2800需要]
	ECAPTURE_SIZE_WXGA,				// <  1280*800
	ECAPTURE_SIZE_SXGA,				// <  1280*1024  
	ECAPTURE_SIZE_WSXGA,			// <  1600*1024  
	ECAPTURE_SIZE_UXGA,				// <  1600*1200
	ECAPTURE_SIZE_WUXGA,			// <  1920*1200
	ECAPTURE_SIZE_NR  
} ECAPTURE_SIZE;

typedef enum 
{
	RV_TALK_CLIENT_MODE,		//set the type of client to start talk [设置客户端方式进行语音对讲]
	RV_TALK_SERVER_MODE,		//set the type of server to start talk [设置服务器方式进行语音对讲]
	RV_TALK_ENCODE_TYPE,		//set the code format of audio talk [设置语音对讲编码格式]
	RV_ALARM_LISTEN_MODE        //set the type of alarm information subscibe [设置报警订阅方式]
} ERVM_USEDEV_MODE;

typedef enum
{
	RV_UPGRADE_BIOS_TYPE=1,		//BIOS upgrade [BIOS升级]
	RV_UPGRADE_WEB_TYPE,		//WEB upgrade [WEB升级]
	RV_UPGRADE_BOOT_YPE,		//BOOT upgrade [BOOT升级]
	RV_UPGRADE_CHARACTER_TYPE,	//the library of Chinese characters [汉字库]
	RV_UPGRADE_LOGO_TYPE,		//LOGO
	RV_UPGRADE_EXE_TYPE,		//EXE eg. player etc... [EXE 例如播放器等]
} ERVM_UPGRADE_TYPE;

//types of language [语言种类]
typedef enum
{
	RV_LANGUAGE_ENGLISH,				//English [英文]	
	RV_LANGUAGE_CHINESE_SIMPLIFIED,		//Simplified Chinese [简体中文]	
	RV_LANGUAGE_CHINESE_TRADITIONAL,	//Chinese-traditional [繁体中文]	
	RV_LANGUAGE_ITALIAN,				//Italian [意大利文]	
	RV_LANGUAGE_SPANISH,				//Spanish [西班牙文]
	RV_LANGUAGE_JAPANESE,				//Japanese [日文版]	
	RV_LANGUAGE_RUSSIAN,				//Russian [俄文版]		
	RV_LANGUAGE_FRENCH,					//French [法文版]		
	RV_LANGUAGE_GERMAN, 				//German [德文版]		
	RV_LANGUAGE_PORTUGUESE,				//Portuguese [葡萄牙语]	
	RV_LANGUAGE_TURKEY,					//Turkey [土尔其语]	
	RV_LANGUAGE_POLISH,					//Polish [波兰语]	
	RV_LANGUAGE_ROMANIAN,				//Romanian [罗马尼亚]	
	RV_LANGUAGE_HUNGARIAN,              //Hungarian [匈牙利语]	
	RV_LANGUAGE_FINNISH,				//Finnish [芬兰语]	
	RV_LANGUAGE_ESTONIAN,				//Estonian [爱沙尼亚语]	
	RV_LANGUAGE_KOREAN,					//Korean [韩语]	
	RV_LANGUAGE_FARSI,					//Bosnian [波斯语]	
	RV_LANGUAGE_DANSK,					//Denish [丹麦语]
	RV_LANGUAGE_CZECHISH,				//Czech [捷克文]
	RV_LANGUAGE_BULGARIA,				//Bulgarian [保加利亚文]
} RV_LANGUAGE_TYPE;

//audio data format of audio talk [语音对讲格式]
typedef enum 
{
	RV_TALK_DEFAULT = 0,
	RV_TALK_PCM = 1,					//PCM
	RV_TALK_G711a,						//G711a
	RV_TALK_AMR,						//AMR
	RV_TALK_G711u,						//G711u
	RV_TALK_G726,						//G726
}RV_TALK_CODING_TYPE;


/// 画面组合类型
enum
{
	/// 只输出一个通道，组合序号对应的就是输出的通道号。
	ESPLIT1,
	
	/// 同时输出两个通道，组合序号0输出0-1通道，组合序号1输出2-3通道，依次类推。
	///	\n 示意图（矩形内数字表示视屏输入通道号）:
	/// \code
	/// +-------------+
	/// |------+------|
	/// | 1    |   2  |
	/// |------+------|
	/// +-------------+
	/// \endcode
	ESPLIT2,	
	
	/// 同时输出2*2四个通道，组合序号0输出0-3通道，组合序号1输出4-7通道，依次类推。
	ESPLIT4,
	
	/// 同时输出八个通道，组合序号0-7都是输出0-7通道，只是组合序号对应的通道大
	/// 画面显示，其余的小画面显示。组合序号8-15都是输出8-15通道，只是组合序号
	/// 减8对应的通道大画面显示，其余的小画面显示，依次类推。
	///	\n 示意图（矩形内数字表示视屏输入通道号）:
	/// \code
	/// +--------------------+------+
	/// |                    |  2   |
	/// |                    |------|
	/// |         1          |  3   |
	/// |                    |------|
	/// |                    |  4   |
	/// |------+------+------|------|
	/// |  8   |  7   |  6   |  5   |
	/// +------+------+------+------+
	/// \endcode
	ESPLIT8,
	
	/// 同时输出3*3九个通道，画面上九个网格中央的那个保留，组合序号0输出0-7通道，
	/// 组合序号1输出8-15通道，依次类推。
	ESPLIT9,	
	
	/// 同时输出4*4十六个通道，组合序号0输出0-15通道，组合序号1输出16-31通道，依次
	/// 类推。
	ESPLIT16,
	
	/// 画中画模式，一个全屏大画面，加一个小画面窗口。
	///	\n 示意图（矩形内数字表示视屏输入通道号）:
	/// \code
	/// +-------------+
	/// | 1           |
	/// |      +------|
	/// |      |   2  |
	/// +------+------+
	/// \endcode
	ESPLITPIP,
	
	/// 同时输出6个画面，一个大画面，5个小画面。参考8画面示意图
	ESPLIT6,
	
	ESPLIT12,
	
	//2010-9-25 luhj add
	ESPLIT13, 
	ESPLIT20,
	ESPLIT25,
	ESPLIT33,
	ESPLIT5,
	//end
	
	/// 枚举的分割方式数目。
	ESPLIT_NR,		
};

/************************************************************************
** definition of struct [结构体定义]
***********************************************************************/
typedef struct
{	
	BOOL	bEnable;
	int		dwWebPort;
	int		dwTCPPort;
	UInt32	dwReserved;	
}NET_UPNP;

//time [时间]
typedef struct 
{
	UInt32 dwYear;		//year [年]
	UInt32 dwMonth;		//month [月]
	UInt32 dwDay;		//day [日]
	UInt32 dwHour;		//hour [时]
	UInt32 dwMinute;		//minute [分]
	UInt32 dwSecond;		//second [秒]
} RVNET_TIME,*LPRVNET_TIME;

typedef enum
{ 
	EDEVICE_TYPE_DVR	 = 100,
	EDEVICE_TYPE_IPC	 = 101,
	EDEVICE_TYPE_DVS	 = 102,
	EDEVICE_TYPE_DECODER = 103,
	EDEVICE_TYPE_DOME    = 104
}RVDEV_DEVICE_TYPE;

//information of device [设备信息]
typedef struct {
	BYTE sSerialNumber[RV_SERIALNO_LEN];	//serial number [序列号]
	BYTE byAlarmInPortNum;					//alarm input number of DVR [DVR报警输入个数]
	BYTE byAlarmOutPortNum;					//alarm output number of DVR [DVR报警输出个数]
	BYTE byDiskNum;							//disk number of DVR [DVR 硬盘个数]
	BYTE byDVRType;							//DVR type, reference to enum RVDEV_DEVICE_TYPE [DVR类型, 见枚举RVDEV_DEVICE_TYPE]
	BYTE byChanNum;							//channel number of DVR [DVR 通道个数]
} RVNetDeviceInfo, *LPRVNetDeviceInfo;

//common alarm information [普通报警信息]
typedef struct {
	int channelcount;
	int alarminputcount;
	unsigned char alarm[16];			//out alarm [外部报警]
	unsigned char motiondection[16];	//motion detect [动态检测]
	unsigned char videolost[16];		//video lost [视频丢失]
} RVNET_CLIENT_STATE;

//query disk information of device in working state [查询设备工作状态硬盘信息]
typedef struct {
	UInt32		dwVolume;		//space of disk [硬盘的容量]
	UInt32		dwFreeSpace;	//left space of disk [硬盘的剩余空间]
	BYTE		dwStatus;		//state of disk, 0-dormancy, 1-activity, 2-error; seperate UInt32 to 4 parts [硬盘的状态,0-休眠,1-活动,2-故障等；将UInt32拆成四个BYTE]
	BYTE		bDiskNum;		//disk index [硬盘号]
	BYTE		bSubareaNum;	//partion index [分区号]
	BYTE		bSignal;		//flag, 0-local, 1-remote [标识，0为本地 1为远程]
}RVNET_DEV_DISKSTATE,*LPRVNET_DEV_DISKSTATE;

//query disk type of device [查询设备硬盘类型]
typedef struct {
	int Type[32];
}NET_DEV_DISKTYPE;

//record file information [录像文件信息]
typedef struct {
	unsigned int     ch;              //channel index [通道号]
	char             filename[128];   //file name [文件名]
	unsigned int     size;            //file length [文件长度]
	RVNET_TIME         starttime;       //start time [开始时间]
	RVNET_TIME         endtime;         //end time [结束时间]
	unsigned int     driveno;         //disk index [磁盘号]
	unsigned int     startcluster;    //start cluster index [起始簇号]
	int				 nRecordFileType; //record file type, 0-common record; 1-alarm record; 2-motion detect; 3-record for card [录象文件类型  0：普通录象；1：报警录象；2：移动检测；3：卡号录象]
	unsigned int	 partno;		  //partion index [分区号]
	unsigned int	 hint;			  
} RVNET_RECORDFILE_INFO, *LPRVNET_RECORDFILE_INFO;

//alarm IO control [报警IO控制]
typedef struct 
{
	unsigned short index;	//port index [端口序号]
	unsigned short state;	//port state [端口状态]
}RVALARM_CONTROL;

typedef struct
{
	unsigned short		index;					//port index [端口序号]
	unsigned short		mode;					//port mode [端口模式]
	BYTE				bReserved[28];			
} RVTRIGGER_MODE_CONTROL;

typedef struct 
{
	int	decoderNo;					//alarming decoder index, start with 0 [报警解码器号,从0开始]
	unsigned short  alarmChn;		//alarming output channel, start with 0 [报警输出口,从0开始]
	unsigned short  alarmState;		//alarming output state, 1-opened, 0-closed [报警输出状态,1-打开　0-关闭]
}RVDECODER_ALARM_CONTROL;

///////////////////structs of user account management [用户帐号管理相关结构体]/////////////////////////////////
typedef struct 
{
	UInt32		dwID;
	char		name[RV_RIGHT_NAME_LENGTH];
	char		memo[RV_MEMO_LENGTH];
}RVOPR_RIGHT;

typedef struct
{
	UInt32		dwID;
	UInt32		dwGroupID;
	char		name[RV_USER_NAME_LENGTH];
	char		passWord[RV_USER_PSW_LENGTH];
	UInt32		dwRightNum;
	UInt32		rights[RV_MAX_RIGHT_NUM];
	char		memo[RV_MEMO_LENGTH];
	UInt32		dwReusable;		//if this account can be used duplicated, 1-allow, 0-forbid [本用户是否允许复用 1-复用，0-不复用]

}RVUSER_INFO;

typedef struct 
{
	UInt32		dwID;
	char		name[RV_USER_NAME_LENGTH];
	UInt32		dwRightNum;
	UInt32		rights[RV_MAX_RIGHT_NUM];
	char		memo[RV_MEMO_LENGTH];
}RVUSER_GROUP_INFO;

//struct of user information configure [用户信息配置结构]
typedef struct 
{
	UInt32				dwRightNum;
	RVOPR_RIGHT			rightList[RV_MAX_RIGHT_NUM];
	UInt32				dwGroupNum;
	RVUSER_GROUP_INFO		groupList[RV_MAX_GROUP_NUM];
	UInt32				dwUserNum;
	RVUSER_INFO			userList[RV_MAX_USER_NUM];
	UInt32				dwSpecial; //special information, 1-support account be used duplicated, 1-not support account be used duplicated [特殊信息， 1-支持用户复用，　0-不支持用户复用]
}RVUSER_MANAGE_INFO;

//////////////////////////////////////////////////////////////////////////////
///////////////////extened structs of user account management [用户帐号管理扩展相关结构体]/////////////////////////////////
#define RV_USER_NAME_LENGTH_EX  16  //user name length [用户名长度]
#define RV_USER_PSW_LENGTH_EX   16  //password length [密码]
typedef struct 
{
	UInt32  dwID;
	char  name[RV_RIGHT_NAME_LENGTH];
	char  memo[RV_MEMO_LENGTH];
}RVOPR_RIGHT_EX;

typedef struct 
{
	UInt32  dwID;
	UInt32  dwGroupID;
	char  name[96];
	char  passWord[96];
	UInt32  dwRightNum;
	UInt32  rights[RV_MAX_RIGHT_NUM];
	char  memo[RV_MEMO_LENGTH];
	/* mask code, include [掩码,包括]
	* 0x00000001 - support account be used duplicated [支持用户复用]
	*/
	UInt32   dwFouctionMask;//mask code [掩码]
	BYTE  byReserve[32];
}RVUSER_INFO_EX;

typedef struct 
{
	UInt32  dwID;
	char  name[RV_USER_NAME_LENGTH_EX];
	UInt32  dwRightNum;
	UInt32  rights[RV_MAX_RIGHT_NUM];
	char  memo[RV_MEMO_LENGTH];
}RVUSER_GROUP_INFO_EX;

//struct user information configure [用户信息配置结构]
typedef struct 
{
	UInt32				dwRightNum;
	RVOPR_RIGHT_EX		rightList[RV_MAX_RIGHT_NUM];
	UInt32				dwGroupNum;
	RVUSER_GROUP_INFO_EX  groupList[RV_MAX_GROUP_NUM];
	UInt32				dwUserNum;
	RVUSER_INFO_EX		userList[RV_MAX_USER_NUM];
	UInt32				dwFouctionMask;//mask code [掩码]    
	/* mask code, include [掩码,包括]
	* 0x00000001 - support account be used dupliceted [支持用户复用]
	* 0x00000002 - password modify need verify [密码修改需要校验]
	*/
	BYTE  byNameMaxLength;			//max length of user name supported [支持用户名的最大长度]
	BYTE  byPSWMaxLength;			//max length of password supported [支持的密码最大长度]
	BYTE  byReserve[254];
}RVUSER_MANAGE_INFO_EX;
///////////////////end of extened structs of user account management [end of 用户帐号管理扩展相关结构体]////////////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////structs of log [日志结构体相关]///////////////////////////
//struct of log time [日志时间结构]
typedef struct 
{
	UInt32 second		:6;					//second 1-60 [秒 1-60]		
	UInt32 minute		:6;					//minute 1-60 [分 1-60]		
	UInt32 hour			:5;					//hour 1-24	[时 1-24]		
	UInt32 day			:5;					//day 1-31 [日 1-31]		
	UInt32 month			:4;					//month 1-12 [月 1-12]		
	UInt32 year			:6;					//year 2000-2063 [年 2000-2063]	
}RVDEVTIME, *LPRVDEVTIME;

typedef struct 
{
	RVDEVTIME time;					//date [日期]
	unsigned short type;			//type [类型]
	unsigned char reserved;			//reserved [保留]
	unsigned char data;				//data [数据]
	unsigned char context[8];		//content [内容]
}RV_LOG_ITEM, *LPRV_LOG_ITEM;

//log information structs returned by interface SDK_QueryLogEx [接口SDK_QueryLogEx返回的日志信息结构体]
//situation : int nType = 1; param : reserved = &nType. [条件：int nType = 1;参数reserved = &nType.]
typedef struct _RV_NEWLOG_ITEM
{
	RVDEVTIME	time; 				//date [日期]
	WORD	type;					//type [类型]
	WORD	data;					//data [数据]
	char  	szOperator[8]; 			//user name [用户名]
	BYTE	context[16];		    //content [内容]	
}RV_NEWLOG_ITEM, *LPRV_NEWLOG_ITEM;

typedef struct 
{
	RVDEVTIME	time;		//time [时间]
	BYTE	channel;		//channel [通道]
	BYTE	type;			//record type [录像类型]
	BYTE	reserved[2];
}RVLOG_ITEM_RECORD, *LPRVLOG_ITEM_RECORD;
////////////////////end of structs of log [end of 日志结构体相关]///////////////////////////

//frame param struct on video data fram callback [回调视频数据帧的帧参数结构体]
typedef struct
{
	unsigned char* pHeader;		// 包含私头的数据指针
	unsigned char* pContent;	// 真正数据的偏移
	unsigned long nLength;		// 数据长度(包括私有头数据长度)
	unsigned long nFrameLength; // 数据长度.
	unsigned int nType;			// 帧类型；音频、视频、私有数据等，详见EFRAMETYPE定义
	unsigned int nSubType;		// 视频帧类型：I帧、B帧、P帧等，详见EFRAMESUBTYPE定义
	unsigned int nEncodeType;	// 编码类型：MPEG4、H264、PCM、MJPEG等；详见定义
	
	// 只有I帧才有的数据
	unsigned long nYear;
	unsigned long nMonth;
	unsigned long nDay;
	unsigned long nHour;
	unsigned long nMinute;
	unsigned long nSecond;
	unsigned long nTimeStamp;

	unsigned int  nFrameRate;	//帧率
	int			  nWidth;  //图象宽度
	int			  nHeight; //图象高度
	unsigned long nRequence; //序列号
	// 音频才有的数据
	unsigned int nChannels;
	unsigned int nBitsPerSample;
	unsigned int nSamplesPerSecond;

	unsigned long nParam1;		// 扩展用
	unsigned long nParam2;		// 扩展用
}RVFrameParam;

//frame param struct on audio data frame callback [回调音频数据帧的帧参数结构体]
typedef struct 
{
	BYTE channels;		//audio channel number [声道数]
	BYTE samples;		//sample 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000 [采样 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000]
	BYTE depth;			//sample depth, 8 or 16, directly show [采样深度 取值8或者16等。直接表示]
	BYTE param1;		//0-indicate no symbol, 1-indicate has symbol [0 - 指示无符号，1-指示有符号]
	UInt32 reserved;		//reserved [保留]
}RVCBPCMDataParam;

//data struct for channel picture title overprinting [通道画面字幕叠加的数据结构]
typedef struct 
{
	BOOL bEnable;												//enable [使能]
	UInt32 dwPosition[RV_MAX_STRING_LINE_LEN];						//position of every character line, use 1-9, corresponding to little key-board position [各行字符的位置　用1-9整数表示，与小键盘位置对应]
																//7 left-up		8 up		9 right-up		[7左上	8上		9右上]
																//4 left		5 middle	6 right			[4左	5中		6右]
																//1 left-down	2 down		3 right-down	[1左下	2下		3右下]
	char szStrings[RV_MAX_STRING_LINE_LEN][RV_MAX_PER_STRING_LEN];	//max 6 character lines, max 20 bytes per line [最多六行字符，每行最多20个字节]
}RV_CHANNEL_OSDSTRING;

////////////////////control param definition for device control interface [设备控制接口的控制参数定义]//////////////////////
typedef struct 
{
	UInt32 dwSize;		//size of this structure, for version control
	int nIndex;			//index of stDisks array of disk information struct RV_HARDDISK_STATE, start with 0 [为硬盘信息结构体RV_HARDDISK_STATE里的数组stDisks下标，从0开始]
	int ctrlType;		//control type.
						//0-clear data, 1-set read-write disk, 2-set read-only disk [0 - 清除数据,	1 - 设为读写盘, 2 - 设为只读盘]
						//3-set redundancy disk, 4-error restore, 5-set snapshot disk [3 - 设为冗余盘, 4 - 恢复错误,	5 - 设为快照盘]
}RVDISKCTRL_PARAM;

typedef struct 
{
	UInt32 dwSize;
	int nAlarmNo;		//alarm channel index, start with 0 [报警通道号，从0开始]
	int nAction;		//0-triggrt to alarm, 1-stop alarm [0-触发报警，1-停止报警]
}RVALARMCTRL_PARAM;

typedef struct 
{
	UInt32 dwSize;
	int nChannelNo;		//video input index, start with 0 [视频输入号，从0开始]
	int nMatrixNo;		//matrix output index, start with 0 [矩阵输出号，从0开始]
}RVMATRIXCTRL_PARAM;

typedef struct 
{
	int channelMask;	//channel index mask, flag one channel per bit [通道号掩码，每位表示一个通道]
	int	devMask;		//device mask, flag one device per bit [设备掩码，每位表示一台设备]
}RVBURNNG_PARM;

////////////////////end of control param definition for device control interface [end of设备控制接口的控制参数定义]//////////////////////

////////////////////params definition of query device state [查询设备状态的参数定义]////////////////////////////////
typedef struct 
{
	UInt32	dwDiskNum;								//number [个数]
	RVNET_DEV_DISKSTATE	stDisks[RV_MAX_DISKNUM];	//every disk or partion information [各硬盘或分区信息]
}RV_HARDDISK_STATE,*LPRV_HARDDISK_STATE;

typedef RV_HARDDISK_STATE  RV_SDCARD_STATE;	//SD card, data struct is the same as disk information [SD卡，数据结构同硬盘信息]

typedef struct 
{
	UInt32 dwDriverType;							//imprinting driver type, 0-RVFS, 1-DISK, 2-CDRW [刻录驱动器类型 0 -	RVFS, 1 - DISK, 2- CDRW]
	UInt32 dwBusType;							//bus type, 0-USB, 1-1394, 2-IDE [总线类型　0- USB, 1-1394, 2-IDE]
	UInt32 dwTotalSpace;							//total space(KB) [总容量(KB)]
	UInt32 dwRemainSpace;						//left space(KB) [剩余容量(KB)]
	BYTE  dwDriverName[RV_BURNING_DEV_NAMELEN]; //imprinting driver name [刻录驱动器名称]
}RVNET_DEV_BURNING,*LPRVNET_DEV_BURNING;

typedef struct 
{
	UInt32	dwDevNum;								//imprinting device number [刻录设备个数]
	RVNET_DEV_BURNING	stDevs[RV_MAX_BURNING_DEV_NUM]; //every imprinting device information [各刻录设备信息]
}RV_BURNING_DEVINFO, *LPRV_BURNING_DEVINFO;

typedef struct 
{
	BYTE	bBurning;		//old impriting means if it is imprintinging now [旧刻录机表示是否正在刻录]
	/*
	* new imprinting values : [新刻录机的值：]
	*0; can imprinting [0;   可以刻录]
	*1; not CD device, device type incorrect [1;   非光盘设备,设备类型不正确]
	*2; no valid device, namely left space is 0 [2;   没有有效的设备,即剩余空间为0]
	*3; there is other CD imprintinging now [3;   有其他光盘在刻录]
	*4; device is not idle, namely it is backuping, imprintinging or relaying now [4;   设备为非空闲状态,即在备份、刻录或回放中]
	*/
	BYTE	bRomType;		//CD type(new imprinting has this value)(0:RV file system; 1:removable disk or U disk; 2:CD) [才有盘片类型(新刻录机才有这个值)(0:RV文件系统；1：移动硬盘或u盘；2：光盘)]
	BYTE	bOperateType;   //operation type(new imprinting has this value)(0:idle; 1:back uping; 2:imprintinging; 3:replaying in CD) [操作类型(新刻录机才有这个值)(0：空闲；1：正在备份中；2：正在刻录中；3：正在进行光盘回放)]
	BYTE	bType;			//state of back up or imprinting(new imprinting has this value)(0:stop or end; 1:start; 2:error; 3:full; 4:initializing) [备份或刻录得过程状态(新刻录机才有这个值)(0：停止或结束 ；1：开始；2：出错；3：满;4：正在初始化)	]
	//**************************
	RVNET_TIME stTimeStart;	//start time [开始时间]
	UInt32	dwTimeElapse;	//already imprintinged time(second) [已刻录时间(秒)]
	UInt32	dwTotalSpace;	//CD total space [光盘总容量]
	UInt32	dwRemainSpace;	//CD left space [光盘剩余容量]
	UInt32	dwBurned;		//already imprintinged space [已刻录容量]
	UInt32	dwStatus;		/*
							for compatible old device, resered, new imprinting has no real using [为了兼容老设备，保留起来的，新刻录机没有实际用处]
							-1:flag new imprinting device. if it is not -1, flag old imprinting device [-1：表示新刻录机。如果不为-1，表示旧刻录机]
							down is imprinting state of old device(old device using) if it is not -1, flag old imprinting device [下面是老设备的刻录状态（老设备用的）如果不为-1，表示旧刻录机：]
							0-initializing [0-正在初始化，]
							1-imprintinging, variables above are valid [1-正在刻录，以上各变量有效]
							2-imprinting error [2-刻录出错]
							3-stoped because CD was full [3-盘满停止]
							*/
}RV_BURNING_PROGRESS, *LPRV_BURNING_PROGRESS;

//language structs device supported [设备支持语言结构体]
typedef struct 
{
	UInt32	dwLanguageNum;		    //number of language type supported [支持语言个数]
	BYTE    byLanguageType[252];    //enum valus, detail to RV_LANGUAGE_TYPE [枚举值,详见RV_LANGUAGE_TYPE]
}RV_DEV_LANGUAGE_INFO, *LPRV_DEV_LANGUAGE_INFO;


typedef struct  
{
	RV_TALK_CODING_TYPE		encodeType;		//code type [编码类型]
	int						nAudioBit;		//using real value, eg. fill it with 8 if 8 bits [用实际的值表示，如8位 则填值为8]
	UInt32					dwSampleRate;	//sample rate, eg. fill it with 16000 if 16k [采样率，如16k 则填值为16000]
	char					reserved[64];
}RVDEV_TALKDECODE_INFO;

//audio talk format device supported [设备支持的语音对讲格式]
typedef struct 
{
	int						nSupportNum;	//number [个数]
	RVDEV_TALKDECODE_INFO	type[64];		//code format [编码格式]
	char					reserved[64];
}RVDEV_TALKFORMAT_LIST;

////////////////////end of params definition of query device state [end of 查询设备状态的参数定义]////////////////////////////////

//DDNS configure [DDNS 配置]
typedef struct 
{
	BOOL	enable;
	int		DDNSKey;
	char	ServerName[64];
	int		ip;
	int		Port;
	char	UserName[64];
	char	Password[64];
	BOOL	Anonymity;
}DDNS;

typedef struct
{
	DDNS Ddns[2];
}NET_DEV_DDNS;

typedef struct
{
	int	 Count;
	DDNS Ddns[MAX_DDNS_COUNT];
}NET_DEV_DDNS_EX;

//struct of GPS information [GPS信息结构体]
typedef struct 
{
	RVNET_TIME revTime;        //locate time [定位时间]
	char DvrSerial[50];      //device serial number [设备序列号]
	double longitude;        //longitude [经度]
	double latidude;         //latitude [纬度]
	double height;           //height(minute) [高度（米）]
	double angle;            //direction angle(north direction is origin point, clockwise is positive) [方向角（正北方向为原点，顺时针为正）]
	double speed;            //speed(kilometers per hour) [速度（公里/小时）]
	WORD starCount;          //locate star number [定位星数]
	BOOL antennaState;       //antenna state(true good, false bad) [天线状态(true 好，false 坏)]
	BOOL orientationState;   //locate state(true good, false bad) [定位状态（true 定位，false 不定位）]
}RVGPS_Info,*LPRVGPS_Info;

//snapshot struct for network trigger device [网络触发设备抓图结构体]
typedef struct  
{
	char			szCardInfo[16];		//card information [卡号信息]
	char			reserved[64];		//reserved [保留]
} RVNET_SNAP_COMMANDINFO, LPRVNET_SNAP_COMMANDINFO;

//protocal information [协议信息]
typedef struct 
{
	char            protocolname[12]; //protocal name [协议名]
	unsigned int	baudbase;	      //baudrate [波特率]
	unsigned char	databits; 	      //data bit [数据位]
	unsigned char	stopbits;	      //stop bit [停止位]
	unsigned char	parity;		      //veryfy bit [校验位]
	unsigned char   reserve;
} RVPROTOCOL_INFO, *LPRVPROTOCOL_INFO;

//audio format information [音频格式信息]
typedef struct {
	BYTE	byFormatTag;			//code type, 0-PCM [编码类型，如0-PCM]
	WORD	nChannels;				//audio channel number [声道数]
	WORD	wBitsPerSample;			//sample depth [采样深度]			
	UInt32	nSamplesPerSec;			//sample rate [采样率]
} RV_AUDIO_FORMAT, *LPRV_AUDIO_FORMAT;

//query device work state channel information:interface is invalid now, don't use it [查询设备工作状态通道信息:相关接口已淘汰，请不要使用]
typedef struct {
	BYTE byRecordStatic;			//channel is recrding, 0-no record, 1-manual record, 2-auto record [通道是否在录像,0-不录像,1-手动录像，2-自动录象]
	BYTE bySignalStatic;			//signal state of connection, 0-normal, 1-signal lost [连接的信号状态,0-正常,1-信号丢失]
	BYTE byHardwareStatic;			//hardware state of channel, 0-normal, 1-except, eg.DSP is dead [通道硬件状态,0-正常,1-异常,例如DSP死掉]
	char reserve;
	UInt32 dwBitRate;				//real bit-rate [实际码率]
	UInt32 dwLinkNum;				//cnnection number of client [客户端连接的个数]
	UInt32 dwClientIP[RV_MAX_LINK];	//IP address of client [客户端的IP地址]
}RVNET_DEV_CHANNELSTATE,*LPRVNET_DEV_CHANNELSTATE;

//auery device work state:interface is invalid now, don't use it [查询设备工作状态:相关接口已淘汰，请不要使用]
typedef struct{
	UInt32 dwDeviceStatic; 									//device state, 0x00 noamal, 0x01 CPU usage is high, 0x02 hardware error [设备的状态,0x00 正常,0x01 CPU占用过高,0x02 硬件错误]
	RVNET_DEV_DISKSTATE  stHardDiskStatic[RV_MAX_DISKNUM]; 
	RVNET_DEV_CHANNELSTATE stChanStatic[RV_MAX_CHANNUM];		//channel state [通道的状态]
	BYTE  byAlarmInStatic[RV_MAX_ALARMIN];					//alarm port state, 0-no alarm, 1-alarm [报警端口的状态,0-没有报警,1-有报警]
	BYTE  byAlarmOutStatic[RV_MAX_ALARMOUT];				//state of alarm output port, 0-no output, 1-output [报警输出端口的状态,0-没有输出,1-有报警输出]
	UInt32  dwLocalDisplay;									//local display status, 0-normal, 1-unnormal [本地显示状态,0-正常,1-不正常]
} RVNET_DEV_WORKSTATE,*LPRVNET_DEV_WORKSTATE;

//add params of keyboard value 常用网络键盘键值
typedef enum _RVKeyboard
{
	// 数字0~9
	RV_NET_KEY_0, RV_NET_KEY_1, RV_NET_KEY_2, RV_NET_KEY_3, RV_NET_KEY_4, RV_NET_KEY_5, RV_NET_KEY_6, RV_NET_KEY_7, RV_NET_KEY_8, RV_NET_KEY_9,
	RV_NET_KEY_UP = 0x0A,		// 上或者云台向上
	RV_NET_KEY_DOWN,			// 下或者云台向下
	RV_NET_KEY_LEFT,			// 左或者云台向左
	RV_NET_KEY_RIGHT,			// 左或者云台向左
	RV_NET_KEY_ESC,				// 取消或退出
	RV_NET_KEY_RET,				// 确认
	RV_NET_KEY_PLAY,			// 播放/暂停
	RV_NET_KEY_STOP,			// 停止
	RV_NET_KEY_FAST,			// 快放
	RV_NET_KEY_SLOW,			// 慢放
	RV_NET_KEY_PREV,			// 上一个文件
	RV_NET_KEY_NEXT,			// 下一个文件
	RV_NET_KEY_BACK,			// 倒放
	RV_NET_KEY_FRAME,			// 逐帧
	RV_NET_KEY_FASTBACK,		// 快退
	RV_NET_KEY_REC,				// 录像
	RV_NET_KEY_SPLIT,       // 画面分割模式切换，每按一次切换到下一个风格模式
	RV_NET_KEY_SPLIT1,      // 单画面
	RV_NET_KEY_SPLIT4,      // 四画面
	RV_NET_KEY_SPLIT8,      // 八画面
	RV_NET_KEY_SPLIT9,      // 九画面
	RV_NET_KEY_SPLIT16,     // 16画面
	
	RV_NET_KEY_FUNC1 = 0X1F,// 功能1
	RV_NET_KEY_FUNC2,		// 功能2（Shift）
	
	RV_NET_KEY_PTZ,			// 进入云台控制模式
	RV_NET_KEY_TELE,        // 变倍减
	RV_NET_KEY_WIDE,        // 变倍加
	RV_NET_KEY_IRIS_SMALL,  // 光圈增
	RV_NET_KEY_IRIS_LARGE,  // 光圈减
	RV_NET_KEY_FOCUS_NEAR,  // 聚焦远
	RV_NET_KEY_FOCUS_FAR,   // 聚焦近
	RV_NET_KEY_BRUSH,       // 雨刷
	RV_NET_KEY_LIGHT,       // 灯光
	RV_NET_KEY_AUTOTOUR,    // 自动巡航
	RV_NET_KEY_TOUR,		// 巡航
	
	RV_NET_KEY_PATTERN,     // 模式
	RV_NET_KEY_SPRESET,     // 设置预置点,预置点号由参数1传入
	RV_NET_KEY_GPRESET,     // 转至预置点,预置点号由参数1传入
	RV_NET_KEY_DPRESET,     // 清除预置点 
	RV_NET_KEY_MENU,        // 球机菜单
	RV_NET_KEY_PREPAGE,	    // 上一页
	RV_NET_KEY_NEXTPAG,	    // 下一页
	
	RV_NET_KEY_ROCUP = 0x41, // 摇杆-上、下、左、右
	RV_NET_KEY_ROCDOWN,
	RV_NET_KEY_ROCLEFT,
	RV_NET_KEY_ROCRIGHT,
	RV_NET_KEY_LEFTUP,		 // 摇杆-左上、左下、右上、右下
	RV_NET_KEY_LEFTDOWN,
	RV_NET_KEY_RIGHTUP,
	RV_NET_KEY_RIGHTDOWN,
}RVKeyboard;

typedef struct _RV_MANUAL_SNAP
{
	int nChannel;		//指定抓拍通道 从0开始
	int  nCount;
	char acTransferNet; //是否即时附带图片数据给网络，1需要设备端返回捉图数据 0不需要设备端返回捉图数据
	char acRes[15];		//保留
}RV_MANUAL_SNAP;

/************************************************************************
** callback function prototype of listen server [侦听服务器回调原形]
***********************************************************************/
typedef int (CALLBACK *PFServiceCallBack)(LONG lHandle, char *pIp, WORD wPort, LONG lCommand, void *pParam, DWORD dwParamLen, DWORD dwUserData);

/************************************************************************
**callback function prototype of disconnect from server [服务器断开回调原形]
***********************************************************************/
typedef void (CALLBACK *PFDisConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

//	callback function prototype of reconnect to server after disconnection [断线重连成功回调函数]
typedef void (CALLBACK *PFHaveReConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

/************************************************************************
** callback function prototype of real-time preview [实时预览回调原形]
***********************************************************************/
typedef void(CALLBACK *FRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of origin data [原始数据回调原形]
***********************************************************************/
typedef int(CALLBACK *PFDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of messasge(alarm) [消息（报警）回调原形]
***********************************************************************/
typedef BOOL (CALLBACK *PFMessCallBack)(LONG lCommand, LONG lLoginID, char *pBuf,
	DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

/************************************************************************
** callback function prototype of screen overprint [屏幕叠加回调原形]
***********************************************************************/
typedef void (CALLBACK *PFDrawCallBack)(LONG lLoginID, LONG lPlayHandle, HDC hDC, DWORD dwUser);

typedef void (CALLBACK *PFDrawItemCallBack)(LONG lPlayHandle, HDC hDc, LONG nUser);

/************************************************************************
** callback function prototype of real-time preview extend [实时预览回调原形-扩展]
***********************************************************************/
typedef void(CALLBACK *PFRealDataCallBackEx) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, DWORD dwUser);

/************************************************************************
** callback function prototype of replay process [回放录像进度回调原形]
***********************************************************************/
typedef void(CALLBACK *PFDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);

/************************************************************************
** callback function prototype of downloading process by time [通过时间下载录像进度回调原形]
not used now, using callback function prototype of replay process [现在按时间下载没有使用这个回调函数，使用的是回放录像进度回调原形. ]
***********************************************************************/
typedef void(CALLBACK *PFTimeDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, RVNET_RECORDFILE_INFO recordfileinfo, DWORD dwUser);

/************************************************************************
** callback function prototype of query device log data [查询设备日志数据回调原形]
***********************************************************************/
typedef void(CALLBACK *PFLogDataCallBack) (LONG lLoginID, char *pBuffer, DWORD dwBufSize, DWORD nTotalSize, BOOL bEnd, DWORD dwUser);

/************************************************************************
** callback function prototype of clarity serial port [透明串口回调原形]
***********************************************************************/
typedef void(CALLBACK *PFTransComCallBack) (LONG lLoginID, LONG lTransComChannel, char *pBuffer, DWORD dwBufSize, DWORD dwUser);

/************************************************************************
** callback function prototype of upgrade device [升级设备程序回调原形]
***********************************************************************/
typedef void(CALLBACK *PFUpgradeCallBack) (LONG lLoginID, LONG lUpgradechannel, int nTotalSize, int nSendSize, DWORD dwUser);

/************************************************************************
** callback function prototype of audio data of audio talk [语音对讲的音频数据回调原形]
***********************************************************************/
typedef void(CALLBACK *PFAudioDataCallBack) (LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);

/***********************************************************************
** callback function prototype of snapshot [抓图回调原形]
***********************************************************************/
typedef void(CALLBACK *PFSnapRev)(LONG lLoginID, LONG nChannel, BYTE *pBuf, UINT RevLen, RVNET_TIME *pCapTime, UINT nEncodeType, DWORD dwUser);

/************************************************************************
** SDK initialization [SDK初始化]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_Init(PFDisConnect cbDisConnect, DWORD dwUser);

/************************************************************************
** SDK cleanup [SDK退出清理]
***********************************************************************/
CLIENT_API void CALL_METHOD SDK_Cleanup();

/************************************************************************
** set the callback function of successfulllu reconnection to server after disconnection, SDK will auto reconnect to server after disconnected from server [设置断线重连成功回调函数，设置后SDK内部断线自动重连]
***********************************************************************/
CLIENT_API void CALL_METHOD SDK_SetAutoReconnect(PFHaveReConnect cbAutoConnect, DWORD dwUser);

/************************************************************************
** return error code for function comminting failed [返回函数执行失败代码]
***********************************************************************/
CLIENT_API DWORD CALL_METHOD SDK_GetLastError(void);

/************************************************************************
** set the timeout and try-times of conncting to server [设置连接服务器超时时间和尝试次数]
***********************************************************************/
CLIENT_API void CALL_METHOD SDK_SetConnectTime(int nWaitTime, int nTryTimes);

/************************************************************************
** get version info of SDK [获取SDK的版本信息]
***********************************************************************/
CLIENT_API DWORD CALL_METHOD SDK_GetSDKVersion();

/************************************************************************
** register to device [向设备注册]
***********************************************************************/
//	nSpecCap = 0 is login by TCP; nSpecCap = 2 is login by auto-register; nSpecCap = 3 is login by group cast; nSpecCap = 4 is login by UDP [nSpecCap = 0为TCP方式下的登入；nSpecCap = 2为主动注册的登入；nSpecCap = 3为组播方式下的登入；nSpecCap = 4为UDP方式下的登入]////0113
CLIENT_API LONG CALL_METHOD SDK_Login(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, LPRVNetDeviceInfo lpDeviceInfo, int *error /*= 0*/, int nSpecCap/* = 0*/, void* pCapParam/* = NULL*/);

/************************************************************************
** logout from device [向设备注销]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_Logout(LONG lLoginID);

/************************************************************************
** 
***********************************************************************/
CLIENT_API void CALL_METHOD SDK_SetDVRMessCallBack(PFMessCallBack cbMessage, DWORD dwUser);

/************************************************************************
** set audio talk mode [设置语音对讲模式]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetDeviceMode(LONG lLoginID, ERVM_USEDEV_MODE emType, void* pValue);

/************************************************************************
** start listen to device [开始帧听设备]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StartListen(LONG lLoginID);

//corresponding to LB device's software version [对应LB设备程序版本]
CLIENT_API BOOL CALL_METHOD SDK_StartListenEx(LONG lLoginID);

/************************************************************************
** stop listrn to device [停止帧听设备]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopListen(LONG lLoginID);

/************************************************************************
** start to listrn to server, listen mobile DVR connection [开始侦听服务器]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_ListenServer(char* ip, WORD port, int nTimeout, PFServiceCallBack cbListen, DWORD dwUserData);

/************************************************************************
** stop listen server, stop listen mobile DVR connection [停止侦听服务器]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopListenServer(LONG lServerHandle);

/************************************************************************
** respond to register device request [响应设备的注册请求]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_ResponseDevReg(char *devSerial, char* ip, WORD port, BOOL bAccept);

/************************************************************************
** start service port [启动服务端口]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_StartService(WORD wPort, char *pIp/* = NULL*/, PFServiceCallBack pfscb/* = NULL*/, 
	DWORD dwTimeOut/* = 0xffffffff*/, DWORD dwUserData/* = 0*/);

/************************************************************************
** stop service port [停止服务端口]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopService(LONG lHandle);

/************************************************************************
** set screen overprint callback [设置屏幕叠加回调]
***********************************************************************/
CLIENT_API void CALL_METHOD SDK_RigisterDrawFun(PFDrawCallBack cbDraw, DWORD dwUser);
CLIENT_API BOOL CALL_METHOD SDK_RigisterItemDrawFun(LONG lRealHandle, PFDrawItemCallBack cbDraw, DWORD dwUser);
CLIENT_API BOOL CALL_METHOD SDK_SetDisplayRegion(LONG lRealHandle, DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
CLIENT_API BOOL CALL_METHOD SDK_GetPictureSize(LONG lRealHandle,LONG *pWidth,LONG *pHeight);

CLIENT_API LONG CALL_METHOD SDK_RealPlay(LONG lLoginID, int nChannelID, HWND hWnd, RV_RealPlayType rType/* = RV_RType_Realplay*/, int nNetType/* = 0*/);

CLIENT_API BOOL	CALL_METHOD SDK_AdjustFluency(LONG lRealHandle, int nLevel);

/************************************************************************
** stop real-time preview [停止实时预览]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopRealPlay(LONG lRealHandle);

/************************************************************************
** save data to file [保存数据为文件]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SaveRealData(LONG lRealHandle, const char *pchFileName);

/************************************************************************
** stop saving data to file [结束保存数据为文件]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopSaveRealData(LONG lRealHandle);

/************************************************************************
** set picture attributes [设置图像属性]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_ClientSetVideoEffect(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

/************************************************************************
** get picture attributes [获取图像属性]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_ClientGetVideoEffect(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

/************************************************************************
** open audio [打开声音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_OpenSound(LONG hPlayHandle);

/************************************************************************
** close audio [关闭声音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_CloseSound();

/************************************************************************
** open audio talk [打开语音对讲]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_StartTalk(LONG lLoginID, PFAudioDataCallBack pfcb, DWORD dwUser);//0113

/************************************************************************
** set the volumn of audio talk [设置语音对讲的音量]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetAudioClientVolume(LONG lTalkHandle, WORD wVolume);

/************************************************************************
** send audio dta to device [发送语音数据到设备]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize);

/************************************************************************
** start audio recording on PC [开始PC端录音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_RecordStart();

/************************************************************************
** stop audio recording on PC [结束PC端录音]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_RecordStop();

/************************************************************************
** decode audio data [解码音频数据]
***********************************************************************/
CLIENT_API void CALL_METHOD SDK_AudioDec(char *pAudioDataBuf, DWORD dwBufSize);

/************************************************************************
** stop audio talk [停止语音对讲]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopTalk(LONG lTalkHandle);

/************************************************************************
** add device to broadcast group [添加设备到广播组]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_AudioBroadcastAddDev(LONG lLoginID);

/************************************************************************
** delete device from broadcast group [从广播组中删除设备]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_AudioBroadcastDelDev(LONG lLoginID);

/************************************************************************
** set the volumn [设置音量]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetVolume(LONG lPlayHandle, int nVolume);

/************************************************************************
** audio code--initialize (specal standard format->RV format) [音频编码--初始化(特定标准格式->RV格式)]
***********************************************************************/
CLIENT_API int  CALL_METHOD SDK_InitAudioEncode(RV_AUDIO_FORMAT aft);

/************************************************************************
** audio code--data code [音频编码--数据编码]
***********************************************************************/
CLIENT_API int	CALL_METHOD	SDK_AudioEncode(LONG lTalkHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);

/************************************************************************
** audio code--quit after complete [音频编码--完成退出]
***********************************************************************/
CLIENT_API int	CALL_METHOD	SDK_ReleaseAudioEncode();

/************************************************************************
** set the callback function of real-time preview [设置实时预览回调]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetRealDataCallBack(LONG lRealHandle, FRealDataCallBack cbRealData, DWORD dwUser);

/************************************************************************
** set the callback function of real-time preview extend [设置实时预览回调-扩展]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetRealDataCallBackEx(LONG lRealHandle, PFRealDataCallBackEx cbRealData, DWORD dwUser, DWORD dwFlag);

/************************************************************************
** snapshot [抓图]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_CapturePicture(LONG hPlayHandle, const char *pchPicFileName);

/************************************************************************
** query that if it has record in some time slice [查询某段时间内是否有录像]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryRecordTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPRVNET_TIME tmStart, LPRVNET_TIME tmEnd, char* pchCardid, BOOL *bResult, int waittime/*=1000*/);

/************************************************************************
** query record file by time [通过时间查询录像文件]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryRecordFile(LONG lLoginID, int nChannelId, int nRecordFileType, LPRVNET_TIME tmStart, LPRVNET_TIME tmEnd, char* pchCardid, LPRVNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime/*=1000*/, BOOL bTime/* = FALSE*/);

/************************************************************************
** replay record file extend, added dta callback params [回放录像文件扩展_增加了数据回调参数]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_PlayBackByRecordFile(LONG lLoginID, LPRVNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, PFDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, PFDataCallBack fDownLoadDataCallBack /*= NULL*/, DWORD dwDataUser/* = 0*/);//0113

/************************************************************************
** pause record replay [暂停录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_PausePlayBack(LONG lPlayHandle, BOOL bPause);

/************************************************************************
** locate record replay start point [定位录像回放起始点]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SeekPlayBack(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

/************************************************************************
** stop record replay [停止录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopPlayBack(LONG lPlayHandle);

/************************************************************************
** step record replay [步进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StepPlayBack(LONG lPlayHandle, BOOL bStop);

/************************************************************************
** fast record replay [快进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_FastPlayBack(LONG lPlayHandle);

/************************************************************************
** slow record replay [慢进录像回放]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SlowPlayBack(LONG lPlayHandle);

/************************************************************************
** restore normal replay speed [恢复正常回放速度]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_NormalPlayBack(LONG lPlayHandle);

/************************************************************************
** set the replay frame rate [设置回放帧速]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetFramePlayBack(LONG lPlayHandle, int framerate);

/************************************************************************
** get the replay frame rate [获取回放帧速]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_GetFramePlayBack(LONG lPlayHandle, int *fileframerate, int *playframerate);

/************************************************************************
** get replay OSD time [获取回放OSD时间]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_GetPlayBackOsdTime(LONG lPlayHandle, LPRVNET_TIME lpOsdTime, LPRVNET_TIME lpStartTime, LPRVNET_TIME lpEndTime);

/************************************************************************
** download record file [下载录像文件]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_DownloadByRecordFile(LONG lLoginID, LPRVNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, PFDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

/************************************************************************
** download record by time [通过时间下载录像]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_DownloadByTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPRVNET_TIME tmStart, LPRVNET_TIME tmEnd, char *sSavedFileName, PFTimeDownLoadPosCallBack cbTimeDownLoadPos, DWORD dwUserData);

/************************************************************************
** stop downloading record [停止录像下载]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopDownload(LONG lFileHandle);

/************************************************************************
** query process of downloading record [查询录像下载进度]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_GetDownloadPos(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

/************************************************************************
** multi-views real-time preview [多画面实时预览]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_MultiPlay(LONG lLoginID, HWND hWnd);

/************************************************************************
** stop multi-views real-time preview [停止多画面实时预览]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopMultiPlay(LONG lMultiHandle);

/************************************************************************
** query device channel name [查询设备通道名称]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryChannelName(LONG lLoginID, char *pChannelName, int maxlen, int *nChannelCount, int waittime/*=1000*/);

/************************************************************************
** set device channel name [设置设备通道名称]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD SDK_SetupChannelName(LONG lLoginID,char *pbuf, int nbuflen);

/************************************************************************
** set device channel charater overprint [设置设备通道字符叠加]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD SDK_SetupChannelOsdString(LONG lLoginID, int nChannelNo, RV_CHANNEL_OSDSTRING* struOsdString, int nbuflen);

/************************************************************************
** common PTZ control [通用云台控制]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_PTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, DWORD dwStep, BOOL dwStop);

/************************************************************************
** RV PTZ control [RV云台控制]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_PTZControlEx(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, 
	unsigned char param1, unsigned char param2, unsigned char param3, BOOL dwStop);

/************************************************************************
** query device log asynchronously [异步查询设备日志]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryLogCallback(LONG lLoginID, PFLogDataCallBack cbLogData, DWORD dwUser);


CLIENT_API BOOL CALL_METHOD SDK_QueryLog(LONG lLoginID, RV_LOG_QUERY_TYPE logType, char *pLogBuffer, int maxlen, int *nLogBufferlen, void* reserved, int waittime/*=3000*/);

/************************************************************************
** create clarity serial port channel [创建透明串口通道]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_CreateTransComChannel(LONG lLoginID, int TransComType, 
	unsigned int baudrate, unsigned int databits,
	unsigned int stopbits, unsigned int parity,
	PFTransComCallBack cbTransCom, DWORD dwUser);

/************************************************************************
** send data by clarity serial port [透明串口发送数据, pBuffer使用RV_PTZ_RAW_DATA_H结构体, 最多发送32个字节]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SendTransComData(LONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

/************************************************************************
** send data by clarity serial port [透明串口发送数据扩展, pBuffer使用RV_PTZ_RAW_DATA_H_EX结构体, 可以发送任意长度字节]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SendTransComDataEx(LONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

/************************************************************************
** release clarity serial port channel [释放通明串口通道]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_DestroyTransComChannel(LONG lTransComChannel);


// set the network evironment for login  [设置登陆网络环境]
CLIENT_API void CALL_METHOD SDK_SetNetworkParam(RVNET_PARAM *pNetParam);

// import configure file [导入配置文件]
CLIENT_API LONG CALL_METHOD SDK_ImportConfigFile(LONG lLoginID, char *szFileName, PFDownLoadPosCallBack cbUploadPos, DWORD dwUserData, DWORD param/*=0*/);

// stop importing configure file [停止导入配置文件]
CLIENT_API BOOL CALL_METHOD SDK_StopImportCfgFile(LONG lImportHandle);

// outport configure file [导出配置文件]
CLIENT_API LONG CALL_METHOD SDK_ExportConfigFile(LONG lLoginID, RV_CONFIG_FILE_TYPE emConfigFileType, char *szSavedFilePath, PFDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

// stop outputing configure file [停止导出配置文件]
CLIENT_API BOOL CALL_METHOD SDK_StopExportCfgFile(LONG lExportHandle);

// search IPC, NVS, etc... devices in local network [搜索局域网内IPC、NVS等设备]
CLIENT_API BOOL CALL_METHOD SDK_SearchDevices(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime);

// 通过广播的方式修改设备信息(不需要登录设备,但需要验证用户名和密码)
// pUserName：设备的登录用户名
// pPassword：设备的密码
// pMacAddr：修改设备的MAC地址
// pDeviceInfo：修改的内容，成功后返回最新的配置信息。说明：不需要修改的请赋置空或0。比如不修改IP，则szIPAddr赋值为""; 不需要修改nCfgPort则赋值为0.
// 返回值：0：表示成功，-1：表示参数错误；-6：端口监听失败；-10：查找设备超时，请检查对应MAC地址的设备是否在线
CLIENT_API int CALL_METHOD SDK_ModifyDeviceByBroadcast(const char *pUserName, const char *pPassword, const char *pMacAddr, SDeviceNetInfo *pDeviceInfo, DWORD dwTimeout /*= 5000*/);

CLIENT_API BOOL CALL_METHOD SDK_GetDiskType(LONG lLoginID, NET_DEV_DISKTYPE* Type, DWORD dwSearchTime /*= 2000*/);

/************************************************************************
** start to upgrade software of device [开始升级设备程序]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_StartUpgrade(LONG lLoginID, char *pchFileName, PFUpgradeCallBack cbUpgrade, DWORD dwUser);

/************************************************************************
** start to upgrade software of device [开始升级设备程序]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_StartUpgradeEx(LONG lLoginID, ERVM_UPGRADE_TYPE emType, char *pchFileName, PFUpgradeCallBack cbUpgrade, DWORD dwUser);

/************************************************************************
** send data [发送数据]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SendUpgrade(LONG lUpgradeID);

/************************************************************************
** end upgrading software of device [结束升级设备程序]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopUpgrade(LONG lUpgradeID);

/************************************************************************
** query record state of channel [查道通道录像状态]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryRecordState(LONG lLoginID, char *pRSBuffer, int maxlen, int *nRSBufferlen, int waittime/*=1000*/);

/************************************************************************
** set record state of channel [设置通道录像状态]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetupRecordState(LONG lLoginID, char *pRSBuffer, int nRSBufferlen);

/************************************************************************
** query current time of device [查询设备当前时间]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryDeviceTime(LONG lLoginID, LPRVNET_TIME pDeviceTime, int waittime/*=1000*/);

/************************************************************************
** set current time of device [设置设备当前时间]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetupDeviceTime(LONG lLoginID, LPRVNET_TIME pDeviceTime);

/************************************************************************
** set serial port protocal [查询系统信息]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QuerySystemInfo(LONG lLoginID, int nSystemType, char *pSysInfoBuffer, int maxlen, int *nSysInfolen, int waittime/*=1000*/);

/************************************************************************
auery lock state of account [查询用户锁定状态]
*************************************************************************/
//CLIENT_API BOOL CALL_METHOD SDK_GetUserLockState(LONG lLoginID, char* UserName, bool *bstate);

/************************************************************************
release lock state of account [解除用户锁定状态]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_UnlockUserLockState(LONG lLoginID, char* UserName);

/************************************************************************
recommend to use extended interface(the max length of user name of some devices is 16 bytes) from now on[建议以后用扩展接口(有些设备用户名最大长度是16个字节的)]
*************************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryUserInfoEx(LONG lLoginID, RVUSER_MANAGE_INFO_EX *info, int waittime/*=1000*/);

/************************************************************************
** query device user (old interface, support 8 bit user name length) [查询设备用户(老接口。支持8位用户名长度。)]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryUserInfo(LONG lLoginID, RVUSER_MANAGE_INFO *info, int waittime/*=1000*/);

/************************************************************************
** operate account of device [操作设备用户]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_OperateUserInfo(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime/*=1000*/);
/************************************************************************
** operate account of device (interface, support 8 bits and 16 bits user name and password) [操作设备用户（新接口，支持8位和16位的用户名密码长度）。]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_OperateUserInfoEx(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime/*=1000*/);


/************************************************************************
** stop talk - invalid now, please use SDK_StopTalkEx [结束对讲 － 该接口已淘汰，请使用SDK_StopTalkEx]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopTalk(LONG lRealHandle);


/************************************************************************
** get channel bit-stream [获取通道码流]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_GetStatiscFlux(LONG lLoginID, LONG lPlayHandle);

/************************************************************************
** query IO state [查询IO状态]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_QueryIOControlState(LONG lLoginID, RV_IOTYPE emType, 
	void *pState, int maxlen, int *nIOCount, int waittime/*=1000*/);

/************************************************************************
** IO control [IO控制]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_IOControl(LONG lLoginID, RV_IOTYPE emType, void *pState, int maxlen);


/************************************************************************
** force I Frame [强制I帧]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_MakeKeyFrame(LONG lLoginID, int nChannelID, int nChannelType/*=0*/);

/************************************************************************
** qury device IP from DDNS server by device name or device serial number [通过设备名字或者设备序列号向DDNS服务器查询设备IP]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_GetDVRIPByResolveSvr(char *pchDVRIP, WORD wDVRPort, 
	BYTE *sDVRName, WORD wDVRNameLen, 
	BYTE *sDVRSerialNumber, WORD wDVRSerialLen, 
	char* sGetIP);

/************************************************************************
** replay record by time extend, added data callback params [通过时间回放录像扩展_增加了数据回调参数]
***********************************************************************/
CLIENT_API LONG CALL_METHOD SDK_PlayBackByTime(LONG lLoginID, int nChannelID, 
	LPRVNET_TIME lpStartTime, LPRVNET_TIME lpStopTime, HWND hWnd, PFDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser,
	PFDataCallBack fDownLoadDataCallBack/* = NULL*/, DWORD dwDataUser/* = 0*/, int nRecordType/* = 0*/);

/************************************************************************
** start to find record files [开始查找录像文件]
***********************************************************************/
CLIENT_API LONG	CALL_METHOD SDK_FindFile(LONG lLoginID,
	int nChannelId,
	int nRecordFileType, 
	char* cardid, 
	LPRVNET_TIME time_start,
	LPRVNET_TIME time_end,
	BOOL bTime, 
	int waittime);

/************************************************************************
** find record file [查找录像文件]
***********************************************************************/
CLIENT_API int	CALL_METHOD SDK_FindNextFile(LONG lFindHandle,LPRVNET_RECORDFILE_INFO lpFindData);

/************************************************************************
** end finding record file [结束录像文件查找]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_FindClose(LONG lFindHandle);

/************************************************************************
** reboot device : returned TRUE success, FALSE fail [重启设备：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_RebootDev(LONG lLoginID);

/************************************************************************
** reset : returned TRUE success, FALSE fail,_RV_RESET_TYPE [恢复出厂设置：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_ResetDeafault(LONG lLoginID, unsigned int type);

/************************************************************************
** shutdown device : returned TRUE success, FALSE fail [关闭设备：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_ShutDownDev(LONG lLoginID);

/************************************************************************
** control device : returned TRUE success, FALSE fail [设备控制：返回值 TRUE 成功， FALSE 失败]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_ControlDevice(LONG lLoginID, RVCtrlType type, void *param, int waittime/* = 1000*/);

/************************************************************************
** auto query device state, include alarm, disk, record state, etc... [主动查询设备状态，包括报警、硬盘、录象状态等。]
***********************************************************************/
//if nType  = RV_DEVSTATE_BURNING_PROGRESS, *pRetLen means query device's ID No. The reason of dealing as this is that there is no other suction parameter to use [当 nType  = RV_DEVSTATE_BURNING_PROGRESS 时,*pRetLen表示查询设备的id号.这样做的原因是没有其它可以使用的入口参数。]
CLIENT_API BOOL CALL_METHOD SDK_QueryDevState(LONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime/*=1000*/);

/************************************************************************
** set the callback function for snapshot [设置定时抓图回调函数]
定时回传，子连接对像不会被删除会一直保持接收状态
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetSnapRevCallBack(LONG lLoginID, int nChannel, PFSnapRev pCallBackFun, DWORD dwUser);

/************************************************************************
** snapshot request [远程手动抓图]
pCallBackFun：回调函数；如果已经通过SDK_StartRevPicture或SDK_SetSnapRevCallBack设置则可为空。
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SnapPicture(LONG lLoginID, RV_MANUAL_SNAP *pSnapParam, PFSnapRev pCallBackFun/* = NULL*/, DWORD dwUser/* = 0*/);

/************************************************************************
** 开始接收定时抓图回调
定时回传，子连接对像不会被删除会一直保持接收状态
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StartRevPicture(LONG lLoginID, unsigned int nChannel, PFSnapRev pCallBackFun, DWORD dwUser);

/************************************************************************
** 停止接收定时抓图回调
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_StopRevPicture(LONG lLoginID, unsigned int nChannel);

///////////////it is function interfaces for dvr on vehicle bellow [以下是车载dvr相关的功能接口] /////////////////////////
/************************************************************************
** callback function prototype of GPS information subscription [GPS信息订阅回调]
***********************************************************************/
typedef void( CALLBACK *PFGPSRev)(LONG lLoginID,           //device handle [设备句柄]
	RVGPS_Info  GpsInfo,       //GPS information [GPS信息]
	DWORD dwUserData);       //user data [用户数据]

/************************************************************************
** set tje callback function of GPS information subscription [设置GPS订阅回调函数]
***********************************************************************/
CLIENT_API void CALL_METHOD SDK_SetSubcribeGPSCallBack(PFGPSRev OnGPSMessage, DWORD dwUser);

/************************************************************************
** GPS information subscription [GPS信息订阅]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SubcribeGPS (
	LONG lLoginID,        //device handle [设备句柄]
	BOOL bStart,		  //if lauch [是否启动]
	LONG KeepTime,        //subscription duration (unit:second) [订阅持续时间（单位秒）]
	LONG InterTime);      //subscription GPS send frequency in duration (unit:second) [订阅时间内GPS发送频率（单位秒）]  

/////////////////////////end of function interfaces for dvr on vehicle [end of 车载dvr相关的功能] ///////////////////////////////


/////////////////////////unfulfilment [未实现]//////////////////////////
/************************************************************************
** set the huffer size of real-time preview [设置实时预览缓冲大小]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetPlayerBufNumber(LONG lRealHandle, DWORD dwBufNum);

//////////////////////////end of unfulfilment [end of 未实现]//////////////////////

/************************************************************************
** device interfaces of remote configure, configure type showed in the MACRO RV_DEV_DEVICECFG [远程配置设备接口 配置类型见RV_DEV_DEVICECFG 各宏]
waittime<=0表示采用程序的默认值，程序默认值可以通过SDK_SetNetworkParam函数指定,初值为2000毫秒
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD SDK_GetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime/* = -1*/, LPVOID lpParamBuffer/* = NULL*/, DWORD dwParamLen/* = 0*/);
CLIENT_API BOOL  CALL_METHOD SDK_SetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime/* = -1*/);


/************************************************************************
** platform connection interfaces [平台接入接口]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD SDK_GetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime/*=500*/);
CLIENT_API BOOL  CALL_METHOD SDK_SetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime/*=500*/);

/************************************************************************
**  get PTZ information [获取云台信息]	
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD SDK_GetPtzOptAttr(LONG lLoginID,DWORD dwProtocolIndex,LPVOID lpOutBuffer,DWORD dwBufLen,DWORD *lpBytesReturned,int waittime/*=500*/);

/************************************************************************
**  get decode handle of remote replay [获取远程回放解码句柄]
***********************************************************************/
CLIENT_API BOOL  CALL_METHOD SDK_GetPlayBackPlayerIndex(LONG lPlayHandle);

/************************************************************************
**  get decode handle of preview [获取预览解码句柄]
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_GetRealPlayerIndex(LONG lPlayHandle);

/************************************************************************
**  get decode handle of preview [配置播放参数]
*lPlayHandle 打开时返回的值
*lPlayType 1：表示实现播放 2：表示回放
*lType 类型，比较10，SVAC窗口
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_SetPlayParamByHandle(LONG lPlayHandle, LONG lPlayType, LONG lType, void * pParam); 

//开启本地Rtsp服务器
//pIP：本地RTSP服务的IP
//iPort：Rtsp监听端口
CLIENT_API BOOL CALL_METHOD SDK_StartRtspserver(const char *pIP, int iPort);

//开始某一解码器视频--与SDK_StopDecVideo成对使用
//lDecoder：解码器的登录句柄--解码器SDK_Login的返回值
//lChannel：通道号，从零开始
//成功返回一个大于零的值，可以操作SDK_PushVideoData,SDK_StopDecVideo
//返回：-2：表示配置解码器失败，-1：表示等待解码器连接超时
CLIENT_API LONG CALL_METHOD SDK_StartDecVideo(LONG lDecoder, LONG lChannel);

//发送数据到解码器
//lHandle：SDK_StartDecVideor返回的值
//pRtpData：RTP数据
//nDataLen：数据长度
CLIENT_API LONG CALL_METHOD SDK_PushVideoData(LONG lHandle, const char*pRtpData, int nDataLen);

#define RV_SAMPLE_FREQ_4000		1
#define RV_SAMPLE_FREQ_8000		2
#define RV_SAMPLE_FREQ_11025	3
#define RV_SAMPLE_FREQ_16000	4
#define RV_SAMPLE_FREQ_20000	5
#define RV_SAMPLE_FREQ_22050	6
#define RV_SAMPLE_FREQ_32000	7
#define RV_SAMPLE_FREQ_44100	8
#define RV_SAMPLE_FREQ_48000	9

// 帧类型
typedef enum _EFRAMETYPE
{
	EFRAME_TYPE_UNKNOWN	= 0,
	EFRAME_TYPE_VIDEO		= 1,
	EFRAME_TYPE_AUDIO		= 2,
	EFRAME_TYPE_DATA		= 3,
}EFRAMETYPE;

// 视频帧类型
typedef enum _EFRAMESUBTYPE
{
	EFRAME_TYPE_VIDEO_I_FRAME	= 0,
	EFRAME_TYPE_VIDEO_P_FRAME	= 1,
	EFRAME_TYPE_VIDEO_B_FRAME	= 2,
	EFRAME_TYPE_VIDEO_S_FRAME	= 3,
	EFRAME_TYPE_DATA_TEXT		= 5,
	EFRAME_TYPE_DATA_INTL		= 6,
}EFRAMESUBTYPE;

// 帧编码类型
typedef enum _EENCODETYPE
{
	EENCODE_UNKNOWN			= 0,
	EENCODE_VIDEO_MPEG4		= 1,
	EENCODE_VIDEO_H264		= 2,
	EENCODE_VIDEO_JPEG      = 3,
	EENCODE_VIDEO_SVAC      = 5,
	EENCODE_VIDEO_SVAC_NEW  = 6,
	EENCODE_AUDIO_PCM8		= 7,	// 8BITS,8K
	EENCODE_AUDIO_G729		= 8,
	EENCODE_AUDIO_IMA		= 9,
	EENCODE_AUDIO_PCM_MULAW	= 10,
	EENCODE_AUDIO_G721		= 11,
	EENCODE_AUDIO_PCM8_VWIS	= 12,	// 16BITS,8K
	EENCODE_AUDIO_ADPCM		= 13,	// 16BITS,8K/16K
	EENCODE_AUDIO_G711A		= 14,	// 16BITS,8K
	EENCODE_AUDIO_TALK      = 30,
	EENCODE_VIDEO_YUV		= 60,	// YUV数据
}EENCODETYPE;

//frame param struct on video data fram callback [回调视频数据帧的帧参数结构体]
typedef struct _SFrameInfo
{
	unsigned char* pHeader;		// 包含私头的数据指针
	unsigned char* pContent;	// 真正数据的偏移
	unsigned long nLength;		// 数据长度(包括私有头数据长度)
	unsigned long nFrameLength; // 数据长度.
	unsigned int nType;			// 帧类型；音频、视频、私有数据等，详见EFRAMETYPE定义
	unsigned int nSubType;		// 视频帧类型：I帧、B帧、P帧等，详见EFRAMESUBTYPE定义
	unsigned int nEncodeType;	// 编码类型：MPEG4、H264、PCM、MJPEG等；详见定义
	// 只有I帧才有的数据
	unsigned long nYear;
	unsigned long nMonth;
	unsigned long nDay;
	unsigned long nHour;
	unsigned long nMinute;
	unsigned long nSecond;
	unsigned long nTimeStamp;

	unsigned int  nFrameRate;	// 帧率
	int			  nWidth;		// 图象宽度
	int			  nHeight;		// 图象高度
	unsigned long nRequence;	// 序列号

	// 音频才有的数据
	unsigned int nChannels;
	unsigned int nBitsPerSample;
	unsigned int nSamplesPerSecond;

	unsigned long nParam1;		// 扩展用
	unsigned long nParam2;		// 扩展用
}SFrameInfo;

//发送数据到解码器
//lHandle：SDK_StartDecVideor返回的值
//pRtpData：标准的H264数据(以00000001或以000001开头的一帧数据，即一个完整的I帧或P帧或B帧)
//nDataLen：数据长度
CLIENT_API LONG CALL_METHOD SDK_PushStdMediaData(LONG lHandle, SFrameInfo *pFrameInfo);

//关闭解码器解码--与SDK_StartDecVideo成对使用
//lHandle：SDK_StartDecVideor返回的值
CLIENT_API LONG CALL_METHOD SDK_StopDecVideo(LONG lHandle);

//停止RtspServer
CLIENT_API void CALL_METHOD SDK_StopRtspserver();

/************************************************************************
** callback function prototype of real-time preview [以Rtsp客户端数据回调]
lHandle：		SDK_RtspPlay返回值
pBuffer：		指向媒体数据（带私有头）
nParam > 0	 ：	正常的媒体数据pBuffer的长度;
nParam == -1 ：	网络异常，连接断开
nUser：			用户传入值
***********************************************************************/
typedef void(CALLBACK *FRtspCallBack) (LONG lHandle, unsigned char *pBuffer, int nParam, int nUser);

/************************************************************************
** start real-time preview [以Rtsp客户端的方式开始实时预览]
pUrl：			Rtsp的URL比如：rtsp://192.168.1.153:554/user=admin&password=123456&id=1&type=0
nError：		当返回值为NULL时，返回错误号：-1：参数错误；-2表示网络连接失败；-100：超时，有可能URL不合法或用户名密码错误，没有数据返回导致时间；
hWnd：			Window系统中的窗口句柄：
nNetType：		媒体网络类型(0：TCP；1：UDP)
pCallBackFun：	数据或状态返回句柄
nUser：			用户自定义回调函数参数
返回值：成功返回一个大于0的操作句柄，否则返回0
***********************************************************************/
//CLIENT_API LONG CALL_METHOD SDK_RtspPlay(const char *pUrl, int &nError, HWND hWnd, int nNetType/* = 0*/, FRtspCallBack pCallBackFun/* = NULL*/, int nUser/* = 0*/);

/************************************************************************
** start real-time preview [暂停以Rtsp客户端的方式打开的实时预览]
lHandle：		SDK_RtspPlay返回值
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_RtspPause(LONG lHandle);

/************************************************************************
** start real-time preview [停止以Rtsp客户端的方式打开的实时预览]
lHandle：		SDK_RtspPlay返回值
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_RtspStop(LONG lHandle);

/************************************************************************
** 创建媒体文件，文件的类型使用后续名标识
*.dav	:	表示私有格式媒体文件
*.avi	:	表示AVI格式的媒体文件
pFileName：	文件名称（注意：若AVI格式文件已经存在内容会被清零）
pParam：	打开参数，暂时无效
nError：	错误返回值，
返回值：	成功返回不等于0的值
***********************************************************************/
//CLIENT_API LONG CALL_METHOD SDK_CreateFile(const char *pFileName, int &nError, void *pParam/* = NULL*/);

/************************************************************************
** 写入媒体文件媒体数据
lHandle：	操作句柄，SDK_CreateFile返回值
pData：		媒体数据(必需是本公司格式媒体数据，AVI文件要求所有数据的分辨率必需一致)
uiSize：	媒体数据长度
nSource:	数据来源(同一通道的数据，用同一个值表示即可)
返回值：	大于0：成功；
***********************************************************************/
CLIENT_API int CALL_METHOD SDK_WirteData(LONG lHandle, const unsigned char *pData, unsigned int uiSize, int nSource/* = 0*/);

/************************************************************************
** 关闭媒体文件
lHandle：	操作句柄，SDK_CreateFile返回值
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_CloseFile(LONG lHandle);

/************************************************************************
** 网络键盘
lLoginID：	设备操作句柄，SDK_Login返回值
keyboardNO：DVR等设备的物理地址号；
keyValue：按键键值；常用值见枚举RVKeyboard，详细见帮助文档
keyState：按键状态；0x01: 键被按下  0x00： 键松开
keyNO：键盘号；为网络键盘编号，默认为0，多级级连时代表控制优先级，0为最高
param1：保留1；平时控制为0，在摇杆控制代表速度
param2：保留2；暂时没有用到
***********************************************************************/
CLIENT_API BOOL CALL_METHOD SDK_NetKeyboard(LONG lLoginID, unsigned char keyboardNO, unsigned char keyValue, unsigned char keyState, 
											unsigned char keyNO/* = 0*/, unsigned char param1/* = 0*/, unsigned char param2/* = 0*/);
/******************************************************************************
** configure structs [以下是各部分配置结构体]
*****************************************************************************/

/************************************************************************
*	system information [系统信息]
************************************************************************/

/*version information:the high 16 bits is main version number, the low 16 bits is minor version number [版本信息:高16位表示主版本号，低16位表示次版本号]
*data format of time : yyyymmdd [关于时间的数据组织是：yyyymmdd] */
typedef struct 
{
	UInt32	dwSoftwareVersion;
	UInt32	dwSoftwareBuildDate;
	UInt32	dwDspSoftwareVersion;
	UInt32	dwDspSoftwareBuildDate;
	UInt32	dwPanelVersion;
	UInt32	dwPanelSoftwareBuildDate;
	UInt32	dwHardwareVersion;
	UInt32	dwHardwareDate;
	UInt32	dwWebVersion;
	UInt32	dwWebBuildDate;
} RV_VERSION_INFO, *LPRV_VERSION_INFO;

/* ability description of DSP (in SDK_GetDevConfig), recommend to use SDK_QueryDevState [DSP能力描述(SDK_GetDevConfig里的)，以后建议用SDK_QueryDevState接口] */
typedef struct 
{
	UInt32	dwVideoStandardMask;	//mask of video standard, flag device supported standard by bits [视频制式掩码，按位表示设备能够支持的视频制式]
	UInt32	dwImageSizeMask;		//mask of resolver, flag device supported resolve configure by bits [分辨率掩码，按位表示设备能够支持的分辨率设置]
	UInt32	dwEncodeModeMask;		//mask of code mode, flag device supported code mode by bits [编码模式掩码，按位表示设备能够支持的编码模式设置]	

	UInt32	dwStreamCap;			//flag device supported multimedia function by bits [按位表示设备支持的多媒体功能，]
									//bit0:support main stream [第一位表示支持主码流]
									//bit1:support assist stream1 [第二位表示支持辅码流1]
									//bit2:support assist stream2 [第三位表示支持辅码流2]
									//bit4:support jpg snapshot [第五位表示支持jpg抓图]
	UInt32	dwImageSizeMask_Assi[8];//flag resolve mask of assisit stream according to main stream's reslove [表示主码流为各分辨率时，支持的辅码流分辨率掩码。]

	UInt32	dwMaxEncodePower;		//the highest code ability of DSP [DSP 支持的最高编码能力 ]
	WORD	wMaxSupportChannel;		//the max video input channel number per DSP [每块 DSP 支持最多输入视频通道数 ]
	WORD	wChannelMaxSetSync;		//if the max code configure per DSP channel is synchonous, 0-not be synchonous, 1-be synchonous [DSP 每通道的最大编码设置是否同步 0-不同步, 1-同步]
} RV_DSP_ENCODECAP, *LPRV_DSP_ENCODECAP;

/* struct of device information configure [设备信息配置结构] */
typedef struct 
{
	UInt32 dwSize;
	/*these are read-only of device bellow [下面是设备的只读部分]*/
	RV_VERSION_INFO			stVersion;
	RV_DSP_ENCODECAP		stDspEncodeCap;		//ability description of DSP [DSP能力描述]
	BYTE	szDevSerialNo[RV_DEV_SERIALNO_LEN];	//serial number [序列号]
	BYTE	byDevType;							//device type, reference to enum RVDEV_DEVICE_TYPE [设备类型，见枚举RVDEV_DEVICE_TYPE]
	BYTE	szDevType[RV_DEV_TYPE_LEN];			//device's detail types, string format, maybe null [设备详细型号，字符串格式，可能为空]
	BYTE	byVideoCaptureNum;					//video port number [视频口数量]
	BYTE	byAudioCaptureNum;					//audio port number [音频口数量]
	BYTE	byTalkInChanNum;					//NSP
	BYTE	byTalkOutChanNum;					//NSP
	BYTE	byDecodeChanNum;					//NSP
	BYTE	byAlarmInNum;						//alarm input port number [报警输入口数]
	BYTE	byAlarmOutNum;						//alarm output port number [报警输出口数]
	BYTE	byNetIONum;							//network port number [网络口数]
	BYTE	byUsbIONum;							//USB port number [USB口数量]
	BYTE	byIdeIONum;							//IDE number [IDE数量]
	BYTE	byComIONum;							//serial port number [串口数量]
	BYTE	byLPTIONum;							//parallel port number [并口数量]
	BYTE	byVgaIONum;							//NSP
	BYTE	byIdeControlNum;					//NSP
	BYTE	byIdeControlType;					//NSP
	BYTE	byCapability;						//NSP, extended description [NSP，扩展描述]
	BYTE	byMatrixOutNum;						//output-port number of video matrix [视频矩阵输出口数]

	/*these are writable parts bellow of device [下面是设备的可写部分]*/
	BYTE	byOverWrite;						//deal method on disk full (overwrite, stop) [硬盘满处理方式（覆盖、停止）]
	BYTE	byRecordLen;						//package size of record [录象打包长度]
	BYTE	byStartChanNo;						//NSP
	WORD	wDevNo;								//device No. for remote control [设备编号，用于遥控]
	BYTE	byVideoStandard;					//video sandard [视频制式]
	BYTE	byDateFormat;						//date format [日期格式]
	BYTE	byDateSprtr;						//date seperate (0-"."， 1-"-"， 2-"/") [日期分割符(0-"."， 1-"-"， 2-"/")]
	BYTE	byTimeFmt;							//time format (0-24 hours, 1-12 hours) [时间格式 (0-24小时，1－12小时)]
	BYTE	byLanguage;						    //enum values, detail in RV_LANGUAGE_TYPE [枚举值详见RV_LANGUAGE_TYPE]
} RVDEV_SYSTEM_ATTR_CFG, *LPRVDEV_SYSTEM_ATTR_CFG;

/************************************************************************
*	picture channel [图像通道]
************************************************************************/

/* record type - timer, motion detect, alarm [录象类型－定时、动态检测、报警] */
typedef enum 
{
	RV_REC_TYPE_TIM = 0,
	RV_REC_TYPE_MTD,
	RV_REC_TYPE_ALM,
	RV_REC_TYPE_NUM,
}RVREC_TYPE;

/* struct of time slice [时间段结构] */															    
typedef struct 
{
	BOOL	bEnable;	//if it is meaning record time slice, flag three enable by bits, they are motion detect record, alarm record, common record from low bit to high bit [当表示录像时间段时，按位表示三个使能，从低位到高位分别表示动检录象、报警录象、普通录象]
	int		iBeginHour;
	int		iBeginMin;
	int		iBeginSec;
	int		iEndHour;
	int		iEndMin;
	int		iEndSec;
} RV_TSECT, *LPRV_TSECT;

/* area:every edge by 8192 rate [区域:各边距按整长8192的比例] */
typedef struct {
	int		left;
	int		top;
	int		right;
	int		bottom;
} RV_RECT,*LPRV_RECT;

/* attributes struct of OSD [OSD属性结构] */
typedef struct  
{
	UInt32		rgbaFrontground;		/*!< object's fore RGB and transparency [物件的前景RGB，和透明度] */
	UInt32		rgbaBackground;			/*!< object's back RGB and transparency [物件的后景RGB，和透明度] */
	RV_RECT		rcRect;					/*!< position [位置] */
	BYTE		bShow;					/*!< show object [物件显示] */
	BYTE		byReserved[3];
} RV_ENCODE_WIDGET, *LPRV_ENCODE_WIDGET;

/* attributes of channel's audio and video [通道音视频属性] */
typedef struct 
{
	//video params [视频参数]
	BYTE	byVideoEnable;				/* videl enable : 1-open; 0-close [视频使能:1－打开，0－关闭] */
	BYTE	byBitRateControl;			/* bit-stream control, reference to constant definition [码流控制,参照常量定义] */
	BYTE	byFramesPerSec;				/* frame rate [帧率] */
	BYTE	byEncodeMode;				/* code mode, reference to constant definition [编码模式,参照常量定义] */
	BYTE	byImageSize;				/* resolve params, reference to constant definition [分辨率参,参照常量定义] */
	BYTE	byImageQlty;				/* level 1-6 [档次1-6] */
	WORD	wLimitStream;				/* limit stream params, range: 50~4*1024 (k) [限码流参数, 范围：50~4*1024 (k)] */

	//audio params [音频参数]
	BYTE	byAudioEnable;				/* audio enable : 1-open, 0-close [音频使能:1－打开，0－关闭] */
	BYTE	wFormatTag;					/* code type, eg. PCM [编码类型，如PCM] */
	WORD	nChannels;					/* audio channel number [声道数] */
	WORD	wBitsPerSample;				/* sample depth [采样深度] */		
	UInt32	nSamplesPerSec;				/* sample rate [采样率] */

	BYTE	bIFrameInterval;			/* frame number between I Frame, descripte the P frame number between two I frame, 0-149 [I帧间隔帧数量，描述两个I帧之间的P帧个数，0-149]*/
	char	reserved;
} RV_VIDEOENC_OPT, *LPRV_VIDEOENC_OPT;

/* attributes of picture color [画面颜色属性] */
typedef struct 
{
	RV_TSECT	stSect;
	BYTE		byBrightness;			/*! brightness 0-100 [亮度	0-100]*/
	BYTE		byContrast;				/*! contrast 0-100 [对比度	0-100]*/
	BYTE		bySaturation;			/*!	saturation 0-100 [饱和度	0-100]*/
	BYTE		byHue;					/*!	hue 0-100 [色度	0-100]*/
	BYTE		byGainEn;				/*! gain enable [增益使能]	 */ 
	BYTE		byGain;					/*! gain 0-100 [增益	0-100]*/
	BYTE		byReserved[2];
} RV_COLOR_CFG, *LPRV_COLOR_CFG;

/* attibutes struct of picture channel [图像通道属性结构体] */
typedef struct 
{
	UInt32				dwSize;
	char				szChannelName[RV_CHAN_NAME_LEN];
	RV_VIDEOENC_OPT		stMainVideoEncOpt[RV_REC_TYPE_NUM];
	RV_VIDEOENC_OPT		stAssiVideoEncOpt[RV_N_ENCODE_AUX];		
	RV_COLOR_CFG		stColorCfg[RV_N_COL_TSECT];
	RV_ENCODE_WIDGET	stTimeOSD;
	RV_ENCODE_WIDGET	stChannelOSD;
	RV_ENCODE_WIDGET	stBlindCover[RV_N_COVERS];
	BYTE				byBlindEnable;			/*! switch of area shelter 0x00 not enable shelter, 0x01 only shlter device local preview, 0x10 only shelter record(and network preview), 0x11 both shelter [区域遮盖开关　0x00不使能遮盖，0x01仅遮盖设备本地预览，0x10仅遮盖录像（及网络预览），0x11都遮盖]	*/
	BYTE				byBlindMask;			/*! mask of area shelter bit0:device local preview, bit1:record(and network preview) [区域遮盖掩码  第一位：设备本地预览；第二位：录像(及网络预览)] */
	BYTE				byReserved[2];
} RVDEV_CHANNEL_CFG, *LPRVDEV_CHANNEL_CFG;


/************************************************************************
*	configure of area shelter [区域遮挡配置]
************************************************************************/
typedef struct 
{
	RV_RECT				rcBlock;			// overwritten area coordinate [覆盖的区域坐标]
	int					nColor;				// overwritten color [覆盖的颜色]
	BYTE				bBlockType;			// overwritten method:0-black block,1-mosaic [覆盖方式：0-黑块，1-马赛克]
	BYTE				bEncode;			// shelter in code level,1-valid,0-invalid [编码级遮挡, 1—生效, 0—不生郊]
	BYTE				bPriview;           // preview shelter,1-valid,0-invalid [预览遮挡, 1—生效, 0—不生效]
	char				reserved[29];		// reserved [保留]
}RVVIDEO_COVER_ATTR;

typedef struct  
{
	UInt32				dwSize;
	char				szChannelName[RV_CHAN_NAME_LEN];		//read-only [只读]
	BYTE				bTotalBlocks;							//supported shelter block number [支持的遮挡块数]
	BYTE				bCoverCount;							//setted shelter block number [已设置的遮挡块数]
	RVVIDEO_COVER_ATTR	CoverBlock[RV_MAX_VIDEO_COVER_NUM];		//overwritten area [覆盖的区域]	
	char				reserved[30];							//reserved [保留]
}RVDEV_VIDEOCOVER_CFG;


/************************************************************************
*	preview picture params [预览图像参数]
************************************************************************/

/* preview picture params [预览图像参数] */
typedef struct 
{
	UInt32 dwSize;
	RV_VIDEOENC_OPT	stPreView;
	RV_COLOR_CFG  stColorCfg[RV_N_COL_TSECT];
}RVDEV_PREVIEW_CFG;

/************************************************************************
* audio attributes struct of audio talk - invalid, wait to be extended [语音对讲音频属性结构体－未实现，待扩展] *
************************************************************************/

typedef struct 
{
	//params for audio input [音频输入参数]
	BYTE	byInFormatTag;					//code type, eg.PCM [编码类型，如PCM]
	BYTE	byInChannels;					//audio channel number [声道数]
	WORD	wInBitsPerSample;				//sample depth [采样深度]					
	UInt32	dwInSamplesPerSec;				//sample rate [采样率]

	//params for audio output [音频输出参数]
	BYTE	byOutFormatTag;					//code type, eg.PCM [编码类型，如PCM]
	BYTE	byOutChannels;					//audio channel number [声道数]
	WORD	wOutBitsPerSample;				//sample depth [采样深度]				
	UInt32	dwOutSamplesPerSec;				//sample rate [采样率]
} RVDEV_TALK_CFG, *LPRVDEV_TALK_CFG;

/************************************************************************
*	timer record [定时录象]
************************************************************************/

typedef struct 
{
	UInt32		dwSize;
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];
	BYTE		byPreRecordLen;					/*! pre-record time, unit is second, 0 means not pre-record [预录时间,单位是s,0表示不预录]*/
	BYTE		byRedundancyEn;					/*! record redundancy switch [录像冗余开关]*/
	BYTE		byRecordTime;					//录像时间，单位分钟
	BYTE		byReserved[1];
} RVDEV_RECORD_CFG, *LPRV_RECORD_CFG;

/************************************************************************
*	alarm configure [报警配置]
************************************************************************/

typedef struct 
{
	int iType;
	int iValue;
} RV_PTZ_LINK, LPRV_PTZ_LINK;

typedef struct 
{
	/******************************************************************************
	** configure of message trigger [消息触发配置]
	**
	** if device occur messages, eg. occuer one input-alarm message, or video lost message, need to deal it [当设备产生消息,譬如产生一个输入报警,或者视频丢失时,需要做相应的处理.]
	** here we define how to deal with one message [此处定义如何处理一个消息]
	*****************************************************************************/

	/* deal method for messages, can combine these values, include [消息处理方式,可以同时多种处理方式,包括]
	* 0x00000001 - network:send to manage server [网络:上传管理服务器]
	* 0x00000002 - record:trigger [录像:触发]
	* 0x00000004 - PTZ lingage [云台联动]
	* 0x00000008 - send email [发送邮件]
	* 0x00000010 - device local alarm tour [设备本地报警轮巡]
	* 0x00000020 - device prompt enable [设备提示使能]
	* 0x00000040 - device alarm output enable [设备报警输出使能]
	* 0x00000080 - Ftp upload enable [Ftp上传使能]
	* 0x00000100 - beep [蜂鸣]
	* 0x00000200 - audio prompt [语音提示]
	* 0x00000400 - snapshot enable [抓图使能]*/

	/*supported deal method for current alarm message, mark by bits [当前报警所支持的处理方式，按位掩码表示]*/
	UInt32		dwActionMask;

	/*trigger action, by bit mask, real action needed params stored in every configure [触发动作，按位掩码表示，具体动作所需要的参数在各自的配置中体现]*/
	UInt32		dwActionFlag;

	/*triggered output ports, alarm message triggered output, 1 means trigger this output [报警触发的输出通道,报警触发的输出,为 1 表示触发该输出]  */ 
	BYTE		byRelAlarmOut[RV_MAX_ALARMOUT_NUM];
	UInt32		dwDuration;		/* alarm duration [报警持续时间] */

	/*linage to record [联动录象]*/
	BYTE		byRecordChannel[RV_MAX_VIDEO_IN_NUM];		/*alarm triggered record channel, 1 means trigger this channel [报警触发的录象通道,为1表示触发该通道] */
	UInt32		dwRecLatch;		/*record duration [录象持续时间] */

	/*snapshot channels [抓图通道]*/
	BYTE		bySnap[RV_MAX_VIDEO_IN_NUM];
	/*tour channels [轮巡通道]*/
	BYTE		byTour[RV_MAX_VIDEO_IN_NUM];

	/*PTZ linkage [云台联动]*/
	RV_PTZ_LINK	struPtzLink[RV_MAX_VIDEO_IN_NUM];
	UInt32		dwEventLatch;   /*!<linkage started delay time, unit is second, range is 0-15, default is 0 [联动开始延时时间，s为单位 范围是0－－15 默认值是0]*/
	/*alarm message triggered wireless output channel, alarm triggered output, 1 means triggered this output [报警触发的无线输出通道,报警触发的输出,为 1 表示触发该输出]  */ 
	BYTE		byRelWIAlarmOut[RV_MAX_ALARMOUT_NUM];
	BYTE		bMessageToNet;	//message upload network enable [消息上传给网络使能]
	BYTE		byReserved[111];       
} RV_MSG_HANDLE;

/* out-alarm [外部报警] */
typedef struct
{
	BYTE		byAlarmType;							/*alarm type, 0:always closed;1:always opened [报警器类型,0：常闭,1：常开]  */
	BYTE		byAlarmEn;								/*alarm enable [报警使能]*/
	BYTE		byReserved[2];						
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;							/*deal method [处理方式]  */
} RV_ALARMIN_CFG,*LPRVDEV_ALARMIN_CFG; 

/* motion detect alarm [动态检测报警] */
typedef struct 
{
	BYTE			byMotionEn;									/*motin detect alarm enable [动态检测报警使能]*/
	BYTE			byReserved;
	WORD			wSenseLevel;								/*sensitivity [灵敏度]*/
	WORD			wMotionRow;									/*line number of motion detect [动态检测区域的行数] */
	WORD			wMotionCol;									/*column number of motion detect [动态检测区域的列数] */
	BYTE			byDetected[RV_MOTION_ROW][RV_MOTION_COL];	/*detect area, max 32*32 areas [检测区域，最多32*32块区域]*/
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];			//NSP
	RV_MSG_HANDLE	struHandle;									/*deal method [处理方式]*/
}RV_MOTION_DETECT_CFG;

/*video lost alarm [视频丢失报警] */
typedef struct
{
	BYTE			byAlarmEn;								/*video lost alarm enable [视频丢失报警使能]*/
	BYTE			byReserved[3];
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;								/*deal method [处理方式]  */
} RV_VIDEO_LOST_CFG;

/*picture shelter alarm [图像遮挡报警] */
typedef struct
{
	BYTE			byBlindEnable;						/*enable [使能] */
	BYTE			byBlindLevel;						/*sensitivity 1-6 [灵敏度1-6] */
	BYTE			byReserved[2];
	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;							/*deal method [处理方式]  */
} RV_BLIND_CFG;

/*disk message(inner alarm) [硬盘消息(内部报警)] */
typedef struct 
{
	BYTE				byNoDiskEn;									/*alarm on no disk [无硬盘时报警] */
	BYTE				byReserved_1[3];
	RV_TSECT			stNDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struNDHandle;								/*deal method [处理方式]  */

	BYTE				byLowCapEn;									/*alarm on low disk space [硬盘低容量时报警]*/
	BYTE				byLowerLimit;								/*space threshold value [容量阀值 0-99]*/
	BYTE				byReserved_2[2];
	RV_TSECT			stLCSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struLCHandle;								/*deal method [处理方式]  */

	BYTE				byDiskErrEn;								/*alarm on disk error [硬盘故障报警]*/
	BYTE				byReserved_3[3];
	RV_TSECT			stEDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE		struEDHandle;								/*deal method [处理方式]  */

} RV_DISK_ALARM_CFG;

typedef struct
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	RV_MSG_HANDLE		struHandle;
} RV_NETBROKEN_ALARM_CFG;

//struct of IP conflict [IP冲突报警结构体]
typedef struct  
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	RV_MSG_HANDLE		struHandle;
}RV_IPCONFLICT_ALARM_CFG;

/*alarm guard [报警布防] */
typedef struct
{
	UInt32 dwSize;

	RV_ALARMIN_CFG 		struLocalAlmIn[RV_MAX_ALARM_IN_NUM];
	RV_ALARMIN_CFG		struNetAlmIn[RV_MAX_ALARM_IN_NUM];
	RV_MOTION_DETECT_CFG struMotion[RV_MAX_VIDEO_IN_NUM];
	RV_VIDEO_LOST_CFG	struVideoLost[RV_MAX_VIDEO_IN_NUM];
	RV_BLIND_CFG		struBlind[RV_MAX_VIDEO_IN_NUM];
	RV_DISK_ALARM_CFG	struDiskAlarm;
	RV_NETBROKEN_ALARM_CFG	struNetBrokenAlarm;
	//	RV_SOUND_ALARM_CFG	struSoundAlarm[RV_MAX_VIDEO_IN_NUM];
	//maybe there are other device exceptions [可能还有设备异常]
} RVDEV_ALARM_SCHEDULE;

typedef struct  
{
	UInt32 dwSize;
	RV_IPCONFLICT_ALARM_CFG	struIPConflict;
} RVDEV_ALARM_IPCONFLICT;

/*intelligent DVR SAVIA alarm [智能DVR SAVIA报警] */
typedef struct
{
	int			iIntelEnable;							/*enable [使能] */
	unsigned int	iIntelIPaddr;							/*ip address [ip地址] */
	BYTE			byReserved[4];
	RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	RV_MSG_HANDLE	struHandle;								/*deal method [处理方式]  */
} RV_SAVIA_ALARM;
typedef struct
{
	int			iSaviaNum;							//Savia number [Savia数目]
	RV_SAVIA_ALARM	stSaviaAlarm[RV_MAX_SAVIA_NUM];		//Savia alarm configure [Savia报警设置]
} RV_SAVIA_ALARM_SCHEDULE;

/*nlack and white ip list [黑白名单] */
typedef struct
{
	UInt32			dwSize;								//size of struct [结构体大小]
	BOOL			bEnable;							//IP authority configure enable [IP权限设置使能]
	Int32			iBlackCount;						//black IP number [黑名单数目]
	UInt32			dwBlackIP[RV_MAX_BLACK_IP_NUM];		//black IPs [黑名单IP]
	Int32			iWhiteCount;						//white IP number [白名单数目]
	UInt32			dwWhiteIP[RV_MAX_WHITE_IP_NUM];		//white IPs [白名单IP]
} RV_BLACKWHITE_CFG;

typedef enum RV_NET_CLI_PROTO_TYPE
{
	RV_NCPT_Dahua_II=0,		// 大华二代协议
	RV_NCPT_Dahua_XTJC=1,	// 系统集成协议
	RV_NCPT_Dahua_DSS=2,
	RV_NCPT_Dahua_RTSP=3,	// rtsp协议
	RV_NCPT_VS300=4,		// VS300协议
	RV_NCPT_Sony_RTSP=5,	// sony rtsp接入
	RV_NCPT_Sony_PDT=6,		// sony 协议接入
	RV_NCPT_BELL=7,			// 中星贝尔接入
	RV_NCPT_Huanghe_RTSP=8,	// 黄河IPC接入
	RV_NCPT_General_RTSP=9,	// 通用rtsp   
    RV_NCPT_Sunell_RTSP=10,	// 景阳rtsp 云台控制采用特殊
    RV_NCPT_Vivotek_RTSP=11,		//vivotek   rtsp接入
    RV_NCPT_ShangYang_RTSP = 12,	// 三洋rtsp
    RV_NCPT_SAMSUNG_RTSP = 13,		// 三星rtsp
	RV_NCPT_XWRJ_RTSP = 14,			// 星网锐捷
	RV_NCPT_YAAN = 15,
	RV_NCPT_YAAN200W = 16,
	RV_NCPT_V8 = 17,
	RV_NCPT_Onvif = 18,
	RV_NCPT_EXPAND = 19, 
	RV_NCPT_ZKTeco = 20,
	RV_NCPT_NUM
}RV_NET_CLI_PROTO_TYPE_E;

/*decoder configure [解码器配置] */
typedef struct
{
	int				channel;					//local decode channel index, start with 0 [本地解码通道号, 从0开始]
	unsigned short	device_type;				// [见RV_NET_CLI_PROTO_TYPE_E]
	unsigned short	device_port;				//front device's port [连接前端设备端口]
	unsigned int	device_ip;					//front device's ip, stored in network bytes storage [网络字节序储存, 连接的前端设备ip]
	unsigned int	device_channel;				//remote channel index [远程通道号]
	unsigned int	enable;						//enable switch [使能开关]
	unsigned int	stream_type;				//type of connection type, 0-main stream [连接码流类型,0-主码流]
	char			username[128];				//front device's user name [连接前端用户名]
	char			password[128];				//connection password [连接密码]
	//
	unsigned char	ucAVEnable;					//0:only decode video, 1:only decode audio, 2:decode audio and video, decode none is not allowed [0,只解视频 1，只解音频 ，2 解音视频 ，不允许什么都不解]
	unsigned char	ucRemotePtzPreset;			//remote preset [远程预置点]
	unsigned char	ucRemotePtzPresetEnable;	//if set remote preset on connected [是否一连接上就设置远程预置点]   
	unsigned char	ucRes;
	unsigned char	ucUrl[256];					//this is valid in rtsp mode, eg. rtsp://ip:port/user=xxx&password=xxx&id=xx&type=xx [rtsp模式下此配置有效,格式如：rtsp://ip:port/user=xxx&password=xxx&id=xx&type=xx]
	int				iDecodePolicy;				//decode plot (-2:most real-time; -1:real-time; 0:default; 1:fluency; 2:most fluency) it will extend to self define delay time [解码策略 	(-2, 最实时 -1 实时 0 默认情况 1 流畅 2,	最流畅 ) 以后可能扩展到自定义具体的延时时间]
	unsigned char	ucConType;					//协议类型，1 TCP 2 UDP
	unsigned char	BPTZLocal;					// 本地云台
	unsigned char	ucRes2[122];				// 保留
}RV_CFG_DECODE_T;
typedef struct
{
	UInt32			dwSize;
	int			iDecoderNumber;
	RV_CFG_DECODE_T	struDecoder[RV_MAX_DECODER_CHAN_NUM];
}RV_DECODER_CFG;

/************************************************************************
*	network configure [网络配置]
************************************************************************/
/*                                                                      */
/*ethernet configure [以太网配置]*/
typedef struct 
{
	char	sDevIPAddr[RV_MAX_IPADDR_LEN];			/* DVR IP address [DVR IP 地址]  */ 
	char	sDevIPMask[RV_MAX_IPADDR_LEN];			/* DVR IP address mask [DVR IP 地址掩码]  */ 
	char	sGatewayIP[RV_MAX_IPADDR_LEN];			/* gateway address [网关地址]  */ 

	/* 10M/100M [10M/100M self adapting, index [自适应,索引] 
	* 1-10MBase - T [1-10MBase - T]
	* 2-10MBase-T FDX [2-10MBase-T 全双工] 
	* 3-100MBase - TX [3-100MBase - TX]
	* 4-100M  FDX [4-100M 全双工]
	* 5-10M/100M self adapting [5-10M/100M  自适应] 
	*/
	//seperate UInt32 to four for extend [为了扩展将UInt32拆成四个]
	BYTE	dwNetInterface;							/* NSP */
	BYTE	bTranMedia;								/* 0:wired;1:wireless [0：有线 1：无线] */
	BYTE	bValid;									/* flag by bits, bit0:valid; 0:invalid, bit1:0:DHCP closed;1:DHCP enable, bit2:0:not support DHCP;1:support DHCP [按位表示，第一位：1：有效 0：无效；第二位：0：DHCP关闭 1：DHCP使能；第三位：0：不支持DHCP 1：支持DHCP] */
	BYTE	bDefaultEth;							/* if treat it as the default net-card, 1:default;0:not default [是否作为默认的网卡 1：默认 0：非默认] */
	char	byMACAddr[RV_MACADDR_LEN];				/* MAC address, read-only [MAC地址，只读] */
} RV_ETHERNET; 

/* remote host configure [远程主机配置] */
typedef struct 
{
	BYTE	byEnable;								/* connection enable [连接使能]  */
	BYTE	byReserved;
	WORD	wHostPort;								/* remote host : port [远程主机 端口]  */
	char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* remote host : IP address [远程主机 IP 地址]  */ 		
	char	sHostUser[RV_MAX_HOST_NAMELEN];			/* remote host : user name [远程主机 用户名] */ 
	char	sHostPassword[RV_MAX_HOST_PSWLEN];		/* remote host : password [远程主机 密码] */ 
}RV_REMOTE_HOST;

/* remote host configure (length of password is 64 bytes) [远程主机配置(密码64字节)] */
typedef struct 
{
	BYTE	byEnable;								/* connection enable [连接使能]  */
	BYTE	byReserved;
	WORD	wHostPort;								/* remote host : port [远程主机 端口]  */
	char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* remote host : IP address [远程主机 IP 地址]  */ 		
	char	sHostUser[RV_MAX_HOST_NAMELEN];			/* remote host : user name [远程主机 用户名] */ 
	char	sHostPassword[RV_MAX_HOST_PSWLEN_EX];	/* remote host : password [远程主机 密码] */ 
}RV_REMOTE_HOST_EX;

/* email configure [邮件配置] */
typedef struct 
{
	char	sMailIPAddr[RV_MAX_IPADDR_LEN];			/*IP address of email server [邮件服务器IP地址]*/
	WORD	wMailPort;								/*port of email server [邮件服务器端口]*/
	WORD	wReserved;								/*reserved [保留]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender address [发送地址]*/
	char	sUserName[RV_MAX_NAME_LEN];				/*user name [用户名]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user password [用户密码]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*Dest address [目的地址]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*Cc address [抄送地址]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*Bcc address [暗抄地址]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*title [标题]*/
}RV_MAIL_CFG;

/*struct of network configure [网络配置结构体]*/
typedef struct
{ 
	UInt32				dwSize; 

	char				sDevName[RV_MAX_NAME_LEN];				/* device host name [设备主机名]*/

	WORD				wTcpMaxConnectNum;						/* max TCP connection number (generaly means video data request number) [TCP最大连接数(一般指视频数据请求数)]*/
	WORD				wTcpPort;								/* TCP listen port [TCP帧听端口]*/
	WORD				wUdpPort;								/* UDP listen port [UDP侦听端口]*/
	WORD				wHttpPort;								/* HTTP port [HTTP端口号]*/
	WORD				wHttpsPort;								/* HTTPS port [HTTPS端口号]*/
	WORD				wSslPort;								/* SSL port [SSL端口号]*/
	RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];		/* ethernet port [以太网口]*/ 

	RV_REMOTE_HOST		struAlarmHost;							/* alarm server [报警服务器]*/
	RV_REMOTE_HOST		struLogHost;							/* log server [日志服务器]*/
	RV_REMOTE_HOST		struSmtpHost;							/* SMTP server [SMTP服务器]*/
	RV_REMOTE_HOST		struMultiCast;							/* multicast group [多播组]*/
	RV_REMOTE_HOST		struNfs;								/* NFS server [NFS服务器]*/
	RV_REMOTE_HOST		struPppoe;								/* PPPoE server [PPPoE服务器]*/
	char				sPppoeIP[RV_MAX_IPADDR_LEN];			/* returned IP by PPPOE register [PPPoE注册返回的IP]*/
	RV_REMOTE_HOST		struDdns;								/* DDNS server [DDNS服务器]*/
	char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS host [DDNS主机名]*/
	RV_REMOTE_HOST		struDns;								/* DNS server [DNS服务器]*/
	RV_MAIL_CFG			struMail;								/* email configure [邮件配置] */
} RVDEV_NET_CFG;

/*struct of network configure [网络配置结构体]*/
typedef struct
{ 
	UInt32				dwSize; 
	
	char				sDevName[RV_MAX_NAME_LEN];				/* device host name [设备主机名] */
	
	WORD				wTcpMaxConnectNum;						/* max TCP connection number (generaly means video data request number) [TCP最大连接数(一般指视频数据请求数)] */
	WORD				wTcpPort;								/* TCP listen port [TCP帧听端口] */
	WORD				wUdpPort;								/* UDP listen port [UDP侦听端口] */
	WORD				wHttpPort;								/* HTTP port [HTTP端口号] */
	WORD				wHttpsPort;								/* HTTPS port [HTTPS端口号] */
	WORD				wSslPort;								/* SSL port [SSL端口号]*/
	RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];		/* ethernet port [以太网口]  */ 
	
	RV_REMOTE_HOST_EX		struAlarmHost;						/* alarm server [报警服务器] */
	RV_REMOTE_HOST_EX		struLogHost;						/* log server [日志服务器] */
	RV_REMOTE_HOST_EX		struSmtpHost;						/* SMTP server [SMTP服务器] */
	RV_REMOTE_HOST_EX		struMultiCast;						/* multicast group [多播组] */
	RV_REMOTE_HOST_EX		struNfs;							/* NFS server [NFS服务器] */
	RV_REMOTE_HOST_EX		struPppoe;							/* PPPPoE server [PPPoE服务器] */
	char				sPppoeIP[RV_MAX_IPADDR_LEN];			/* returned IP by PPPOE register [PPPoE注册返回的IP] */
	RV_REMOTE_HOST_EX		struDdns;							/* DDNS server [DDNS服务器] */
	char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS host [DDNS主机名]*/
	RV_REMOTE_HOST_EX		struDns;							/* DNS server [DNS服务器]*/
	RV_MAIL_CFG			struMail;								/* email configure [邮件配置] */
} RVDEV_NET_CFG_RHEX;

/************************************************************************
*	serial port configure [串口配置]
************************************************************************/

/* basic attributs of serial port [串口基本属性] */
typedef struct
{
	BYTE	byDataBit;		//data bit 0-5,1-6,2-7,3-8 [数据位 0-5,1-6,2-7,3-8]
	BYTE	byStopBit;		//stop bit 0-1bit, 1-1.5bits, 2-2bits [停止位 0-1位, 1-1.5位, 2-2位] 
	BYTE	byParity;		//verify bit 0-no, 1-odd, 2-even [校验位 0-no, 1-odd, 2-even] 
	BYTE	byBaudRate;		//{0-300,1-600,2-1200,3-2400,4-4800
							// 5-9600,6-19200,7-38400,8-57600,9-115200} 
} RV_COMM_PROP;

/* 485 decoder configure [485串口配置] */
typedef struct
{ 
	RV_COMM_PROP	struComm;

	BYTE			wProtocol;			/*protocal type, save the index of protocal, dynamicly change [协议类型 保存协议的下标，动态变化] */
	BYTE			byReserved;			/*reserved [保留]  */	
	BYTE			wDecoderAddress;	/*decoder address : 0 - 255 [地址:0 - 255]*/ 
	BYTE 			byMartixID;			/*matrix No. [矩阵号]*/
} RV_485_CFG; 

/* 232 seial port configure [232串口配置] */
typedef struct
{
	RV_COMM_PROP	struComm;
	BYTE			byFunction;/*serial port function, corresponding function name list got from serial port configure [串口功能，对应串口配置取到的功能名列表]*/
	BYTE			byReserved[3];
} RV_RS232_CFG;

/* struct of serial port configure [串口配置结构体] */
typedef struct
{
	UInt32			dwSize;
	//decoder protocal [解码器协议]
	UInt32			dwDecProListNum;										//number of protocal [协议个数]
	char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN];	//protocal name list [协议名列表]
	RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM];							//current attributs of every decoder [各解码器当前属性]

	UInt32			dw232FuncNameNum;										//number of 232 function [232功能个数]
	char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];			//function name list [功能名列表]
	RV_RS232_CFG	st232[RV_MAX_232_NUM];									//current attributs of every 232 serial port [各232串口当前属性]
} RVDEV_COMM_CFG;


/************************************************************************
*	auto mantance configure [自动维护配置]
***********************************************************************/
/* attributes of auto mantance [自动维护属性] */
typedef struct
{
	UInt32 dwSize;

	//auto reboot [自动重启]
	BYTE byAutoRebootDay;		// 0-never, 1-every day, 2-every sunday, 3-every monday, etc... [0-从不, 1-每天, 2-每星期日, 3-每星期一,.....]
	BYTE byAutoRebootTime;		// 0-0:00 1-1:00,........23-:23:00 */
	//autoly delete files [自动删除文件]
	BYTE byAutoDeleteFilesTime; // 0-never, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH [0-从不, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH] */

	BYTE reserved[13];			// reserved [保留位]
} RVDEV_AUTOMT_CFG;

/************************************************************************
* configure of local machine's matrix control plot [本机矩阵控制策略配置]
************************************************************************/

typedef struct
{
	BOOL		bTourEnable;			//	tour enable [轮巡使能]
	int			nTourPeriod;			//	tour time slice, unit is second, 5-300 [轮巡间隔，单位秒, 5-300] 
	UInt32		dwChannelMask;			//	tour channel, by mask [轮巡的通道，掩码形式表示]
	char		reserved[64];
}RV_VIDEOGROUP_CFG;

typedef struct
{
	UInt32	dwSize;
	int		nMatrixNum;									//matrix number (read-only) [矩阵个数(注：不允许修改)]
	RV_VIDEOGROUP_CFG struVideoGroup[RV_MATRIX_MAXOUT];
	char	reserved[32];
}RVDEV_VIDEO_MATRIX_CFG;   

/************************************************************************
*	multi DDNS configure struct [多ddns配置结构体]
************************************************************************/

typedef struct
{
	UInt32	dwId;									//ddns server's id No. [ddns服务器id号]
	BOOL	bEnable;								//enable, only one ddns server can be enabled in the same time [使能，同一时间只能有一个ddns服务器处于使能状态]
	char	szServerType[RV_MAX_SERVER_TYPE_LEN];	//server type [服务器类型，希网..]
	char	szServerIp[RV_MAX_DOMAIN_NAME_LEN];		//server ip or domain [服务器ip或者域名]
	UInt32	dwServerPort;							//server port [服务器端口]
	char	szDomainName[RV_MAX_DOMAIN_NAME_LEN];	//dvr domain, eg. jeckean.3322.org [dvr域名，如jeckean.3322.org]
	char	szUserName[RV_MAX_HOST_NAMELEN];		//user name [用户名]
	char	szUserPsw[RV_MAX_HOST_PSWLEN];			//password [密码]
	char	szAlias[RV_MAX_DDNS_ALIAS_LEN];			//server's other name, eg. "RV inter ddns" [服务器别名，如"RV inter ddns"]
	UInt32	dwAlivePeriod;							//DDNS alive time slice [DDNS 保活时间]
	char	reserved[256];
}RV_DDNS_SERVER_CFG;

typedef struct
{
	UInt32	dwSize;
	UInt32	dwDdnsServerNum;	
	RV_DDNS_SERVER_CFG struDdnsServer[RV_MAX_DDNS_NUM];	
}RVDEV_MULTI_DDNS_CFG;

/************************************************************************
*   struct of email [邮件配置结构体]
************************************************************************/
typedef struct 
{
	char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*email server address (IP or domain) [邮件服务器地址(IP或者域名)]*/
	char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
	WORD	wMailPort;								/*email server port [邮件服务器端口]*/
	WORD	wSubMailPort;
	WORD	wReserved;								/*reserved [保留]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender's address [发送地址]*/
	char	sUserName[RV_MAX_NAME_LEN];				/*user name [用户名]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user's password [用户密码]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*dest address [目的地址]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*cc address [抄送地址]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*bcc address [暗抄地址]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*subject [标题]*/
	BYTE	bEnable;//使能0:false,	1:true
	char	reserved[255];
} RVDEV_MAIL_CFG;

/************************************************************************
*   extend struct of email [邮件配置结构体扩展]
************************************************************************/
typedef struct 
{
	char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*email server address (IP or domain) [邮件服务器地址(IP或者域名)]*/
	char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
	WORD	wMailPort;								/*emial server's port [邮件服务器端口]*/
	WORD	wSubMailPort;
	WORD	wReserved;								/*reserved [保留]*/
	char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*sender's address [发送地址]*/
	char	sUserName[RV_MAX_NAME_LEN_EX];			/*user name [用户名]*/
	char	sUserPsw[RV_MAX_NAME_LEN];				/*user's password [用户密码]*/
	char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*dest address [目的地址]*/
	char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*cc address [抄送地址]*/
	char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*bcc address [暗抄地址]*/
	char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*subject [标题]*/
	BYTE	bEnable;								//enalbe, 0:dalse, 1:true [使能0:false,	1:true]
	char	reserved[255];
} RVDEV_MAIL_CFG_EX;

/************************************************************************
*   version information of device's software [设备软件版本信息]
************************************************************************/
typedef struct  
{
	char	szDevSerialNo[RV_DEV_SERIALNO_LEN];		//serial number [序列号]
	char	byDevType;								//device type, reference to enum RVDEV_DEVICE_TYPE [设备类型，见枚举RVDEV_DEVICE_TYPE]
	char	szDevType[RV_DEV_TYPE_LEN];				//device's detail type, string fromat, maybe null [设备详细型号，字符串格式，可能为空]
	int		nProtocalVer;							//protocal version [协议版本号]
	char	szSoftWareVersion[RV_MAX_URL_LEN];
	UInt32	dwSoftwareBuildDate;
	char	szDspSoftwareVersion[RV_MAX_URL_LEN];
	UInt32	dwDspSoftwareBuildDate;
	char	szPanelVersion[RV_MAX_URL_LEN];
	UInt32	dwPanelSoftwareBuildDate;
	char	szHardwareVersion[RV_MAX_URL_LEN];
	UInt32	dwHardwareDate;
	char	szWebVersion[RV_MAX_URL_LEN];
	UInt32	dwWebBuildDate;
	char	reserved[256];
} RVDEV_VERSION_INFO;


/************************************************************************
*   ability description of DSP [DSP能力描述]
************************************************************************/
typedef struct 
{
	UInt32	dwVideoStandardMask;		//mask of video sandard, flag supported video standard by bits [视频制式掩码，按位表示设备能够支持的视频制式]
	UInt32	dwImageSizeMask;			//mask of resolve, flag supported resolve by bits [分辨率掩码，按位表示设备能够支持的分辨率设置]
	UInt32	dwEncodeModeMask;			//mask of code mode, flag supported code mode by bits [编码模式掩码，按位表示设备能够支持的编码模式设置	]

	UInt32	dwStreamCap;				//flag supported multivideo by bits [按位表示设备支持的多媒体功能，]
										//bit0:support main stream [第一位表示支持主码流]
										//bit1:support assist stream1 [第二位表示支持辅码流1]
										//bit2:support assist stream2 [第三位表示支持辅码流2]
										//bit4:support snapshot by jpg [第五位表示支持jpg抓图]
	UInt32	dwImageSizeMask_Assi[32];	//mask of assist stream's supported resolve, corresponding every resolve of main stream [表示主码流为各分辨率时，支持的辅码流分辨率掩码。]

	UInt32	dwMaxEncodePower;			//max code ability of DSP [DSP 支持的最高编码能力 ]
	WORD	wMaxSupportChannel;			//max video channel number of every DSP [每块 DSP 支持最多输入视频通道数 ]
	WORD	wChannelMaxSetSync;			//if the max code configure be synchonous, 0-be not synchonous, 1-be synchonous [DSP 每通道的最大编码设置是否同步 0-不同步, 1-同步]

	BYTE	bMaxFrameOfImageSize[32];	//max sample rate in every resolve, corresponding dwVideoStandardMask by bits [不同分辨率下的最大采集帧率，与dwVideoStandardMask按位对应]
	BYTE	bEncodeCap;					//0:code ability of main stream + code ability of assist stream <= code ability of device [0：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力；]
										//1:code ability of main stream + code ability of assist stream <= code ability of device [1：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，]
										//code ability of assist stream <= code ability of main stream [辅码流的编码能力 <= 主码流的编码能力，]
										//resolve of assist stream < resolve of main stream [辅码流的分辨率 <= 主码流的分辨率，]
										//frame rate of main stream and assist stream <= sample rate of front device [主码流和辅码流的帧率 <= 前端视频采集帧率]

	char	reserved[95];
} RVDEV_DSP_ENCODECAP, *LPRVDEV_DSP_ENCODECAP;


/************************************************************************
*   configure of snapshot fucntion [抓图功能配置]
************************************************************************/
typedef struct 
{
	UInt32	dwSize;
	BOOL	bTimingEnable;						//switch of timer snapshot (switch of timer snapshot for alarm is showed in alarm linkage) [定时抓图开关（报警抓图开关在各报警联动配置中体现）]
	RV_VIDEOENC_OPT struSnapEnc[ESNAP_TYP_NUM];	//snapshot code configure, support it's resolve, picture quality, frame rate is negtive here to mean how many pictures snapshoted once [抓图编码配置，现支持其中的分辨率、画质、帧率设置，帧率在这里是负数，表示一秒抓图的次数。]
}RVDEV_SNAP_CFG;

/************************************************************************
*   web path configure [web路径配置]
************************************************************************/
typedef struct 
{
	UInt32	dwSize;
	BOOL	bSnapEnable;					//if snapshot [是否抓图]
	int		iSnapInterval;					//snapshot timer [抓图周期]
	char	szHostIp[RV_MAX_IPADDR_LEN];	//HTTP host's IP [HTTP主机IP]
	WORD	wHostPort;
	int		iMsgInterval;					//state messgae sending time slice [状态消息发送间隔]
	char	szUrlState[RV_MAX_URL_LEN];		//state message upload URL [状态消息上传URL]
	char	szUrlImage[RV_MAX_URL_LEN];		//picture upload Url [图片上传Url]
	char	szDevId[RV_MAX_DEV_ID_LEN];		//local machine's web No. [机器的web编号]
	BYTE	byReserved[2];
}RVDEV_URL_CFG;

/************************************************************************
*   picture watermark configure [图象水印配置]
************************************************************************/
typedef struct  
{
	UInt32				dwSize;
	int					nEnable;								//	enable [使能]
	int					nStream;								//	bit stream (1~n) 0-all stream [码流（1～n）0-所有码流]
	int					nKey;									//	data type (1-text, 2-picture) [数据类型(1-文字，2-图片)]
	char				szLetterData[RV_MAX_WATERMAKE_LETTER];	//	text [文字]
	char				szData[RV_MAX_WATERMAKE_DATA];			//	picture data [图片数据]
	BYTE				bReserved[512];							//	reserved [保留]
} RVDEV_WATERMAKE_CFG;

/************************************************************************
*   FTP upload configure [FTP上传配置]
************************************************************************/
typedef struct
{
	struct
	{
		RV_TSECT	struSect;	//"enable" is invalid in this time slice, can be ignored [该时间段内的“使能”无效，可忽略]
		BOOL		bMdEn;		//upload motion detect record [上传动态检测录象]
		BOOL		bAlarmEn;	//upload out-alarm record [上传外部报警录象]
		BOOL		bTimerEn;	//upload common timer record [上传普通定时录像]
		UInt32		dwRev[4];
	} struPeriod[RV_TIME_SECTION];
}RV_FTP_UPLOAD_CFG;

typedef struct
{
	UInt32				dwSize;
	BOOL				bEnable;									//enable [是否启用]
	char				szHostIp[RV_MAX_IPADDR_LEN];				//host's IP [主机IP]
	WORD				wHostPort;									//host's port [主机端口]
	char				szDirName[RV_FTP_MAX_PATH];					//FTP folder path [FTP目录路径]
	char				szUserName[RV_FTP_USERNAME_LEN];			//usr name [用户名]
	char				szPassword[RV_FTP_PASSWORD_LEN];			//password [密码]
	int					iFileLen;									//file length [文件长度]
	int					iInterval;									//time slice between files [相邻文件时间间隔]
	RV_FTP_UPLOAD_CFG	struUploadCfg[RV_MAX_CHANNUM][RV_N_WEEKS];
	char 				protocol;									//0-FTP 1-SMB
	char				NASVer;										//version of network store server, 0-old FTP(show time slice in UI), 1-NAS store(hidden time slice in UI) [网络存储服务器版本0=老的FTP（界面上显示时间段）,1=NAS存储（界面上屏蔽时间段）]
	BYTE 				reserved[128];
}RVDEV_FTP_PROTO_CFG;

// DNS server configure [DNS服务器配置]
typedef struct  
{
	char				szPrimaryIp[RV_MAX_IPADDR_LEN];
	char				szSecondaryIp[RV_MAX_IPADDR_LEN];
	char				reserved[256];
}RVDEV_DNS_CFG;


/************************************************************************
*   record download plot configure [录象下载策略配置]
************************************************************************/
typedef struct
{
	UInt32 dwSize;

	BOOL bEnable;	//TRUE - high speed download, FALSE - common download [TRUE－高速下载，FALSE-普通下载]
}RVDEV_DOWNLOAD_STRATEGY_CFG;

/************************************************************************
*   network transport plot configure [网络传输策略配置]
************************************************************************/
typedef struct
{
	UInt32 dwSize;

	BOOL bEnable;
	int  iStrategy;	//picture quality first, 1-fluency first, 2-auto [0-画质优先， 1-流畅性优先， 2-自动。]
}RVDEV_TRANSFER_STRATEGY_CFG;


/************************************************************************
*	configure of IPC [IPC的一些配置]
************************************************************************/
//	configure of wireless network [配置无线网络信息]
typedef struct 
{
	int					nEnable;			// enable wireless [无线使能]
	char				szSSID[36];			// SSID
	int					nLinkMode;			// connection mode 0:adhoc 1:Infrastructure [连接模式 0:auto 1:adhoc 2:Infrastructure]
	int					nEncryption;		// encrypt 0: off  2:WEP64bit 3: WEP128bit [加密 0: off 2:WEP64bit 3: WEP128bit]
	int					nKeyType;			// 0:Hex 1:ASCII
	int					nKeyID;				// serial number [序号]
	char				szKeys[4][32];		// four group password [四组密码]
	int					nKeyFlag;
	char				reserved[12];
} RVDEV_WLAN_INFO;

//	select some wireless device [选择使用某个无线设备]
typedef struct  
{
	char				szSSID[36];
	int					nLinkMode;			// connection mode 0:adhoc 1:Infrastructure [连接模式 0:adhoc 1:Infrastructure]
	int 				nEncryption;		// encrypt 0: off  2:WEP64bit 3: WEP128bit [加密 0: off  2:WEP64bit 3: WEP128bit]
	char				reserved[48];
} RVDEV_WLAN_DEVICE;

//	found wireless device list [搜索到的无线设备列表]
typedef struct  
{
	UInt32				dwSize;
	BYTE				bWlanDevCount;		// number of found wireless device [搜索到的无线设备个数]
	RVDEV_WLAN_DEVICE	lstWlanDev[RV_MAX_WLANDEVICE_NUM];
	char				reserved[255];
} RVDEV_WLAN_DEVICE_LIST;

//	configure params of auto registration [主动注册参数配置]
typedef struct  
{
	char				szServerIp[32];		//auto register server's IP [注册服务器IP]
	int					nServerPort;		//port [端口号]
	char				reserved[64];
} RVDEV_SERVER_INFO;

typedef struct  
{
	UInt32				dwSize;
	BYTE				bServerNum;         //supported max ip number [支持的最大ip数]
	RVDEV_SERVER_INFO	lstServer[RV_MAX_REGISTER_SERVER_NUM];
	BYTE				bEnable;			//enable [使能]
	char				szDeviceID[32];		//device's id [设备id。]
	char				reserved[94];
} RVDEV_REGISTER_SERVER;

//	attributs of cameral [摄像头属性]
typedef struct 
{
	BYTE				bBrightnessEn;		// if brightness can be adjusted, 1:can, 0:can't [亮度可调 1：可；0：不可]
	BYTE				bContrastEn;		// if contrast can be adjusted[对比度可调]
	BYTE				bColorEn;			// if hue can be adjusted[色度可调]
	BYTE				bGainEn;			// if gain can be adjusted[增益可调]
	BYTE				bSaturationEn;		// if saturation can be adjusted[饱和度可调]
	BYTE				bBacklightEn;		// if backlight compensation can be adjusted[背光补偿可调]
	BYTE				bExposureEn;		// if exposure selection can be adjusted[曝光选择可调]
	BYTE				bColorConvEn;		// if auto transform between "multi color" and "black and white"  can be adjusted[自动彩黑转换可调]
	BYTE				bAttrEn;			// attributs option, 1:can, 0:can't [属性选项 1：可；0：不可]
	BYTE				bMirrorEn;			// mirrorimage, 1:support, 0:not support [镜像 1：支持；0：不支持]
	BYTE				bFlipEn;			// reversal, 1:support, 0:not support [翻转 1：支持；0：不支持]
	BYTE				bRev[125];			// reserved [保留]
} RVDEV_CAMERA_INFO;

//	attributes configure of cameral [摄像头属性配置]
typedef struct  
{
	UInt32				dwSize;
	BYTE				bExposure;			//exposure mode 1-9:manual exposure level; 0:auto exposure [曝光模式 1-9:手动曝光等级; 0:自动曝光]
	BYTE				bBacklight;			//backlight compensation 3:hard, 2:middle, 1:weak, 0:closed [背光补偿 3:强；2：中；1：弱； 0:关]
	BYTE				bAutoColor2BW;		//day/night mode 2:opened, 1:auto, 0:closed [日/夜模式 2:开；1：自动; 0:关]
	BYTE				bMirror;			//mirrorimage, 1:opened, 0:closed [镜像  1 开， 0关]
	BYTE				bFlip;				//reversal, 1:opened, 0:closed [翻转  1 开， 0关]
	char				bRev[123];			//reserved [保留]
} RVDEV_CAMERA_CFG;

#define ALARM_MAX_NAME 64
//(wireless) infrayed alarm configure [(无线)红外报警配置]
typedef struct
{
	BOOL				bEnable;							//alarm input enable [报警输入使能]
	char				szAlarmName[RV_MAX_ALARM_NAME];		//alarm input name [报警输入名称]
	int					nAlarmInPattern;					//alarm input wave [报警器输入波形]
	int					nAlarmOutPattern;					//alarm output wave [报警输出波形]
	char				szAlarmInAddress[RV_MAX_ALARM_NAME];//alarm input address [报警输入地址]
	int					nSensorType;						//out device's sensor type : always opened or always closed [外部设备传感器类型常开 or 常闭]
	int					nDefendEfectTime;					//ally delay time, alarm input is valid after this time [布撤防延时时间，在此时间后该报警输入有效]
	int					nDefendAreaType;					//area type [防区类型 ]
	int					nAlarmSmoothTime;					//alarm smooth time, means, if there are two alarm input occured in this time, ignored the second [报警平滑时间，即在此时间内如果只有一个报警输入连续输入两次则忽略掉后面一次]
	char				reserved[128];

	RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];
	RV_MSG_HANDLE		struHandle;							//deal method [处理方式]
} RV_INFRARED_INFO;

//wireless remote control configure [无线遥控器配置]
typedef struct 
{
	BYTE  address[ALARM_MAX_NAME];							// address of remote control [遥控器地址]
	BYTE  name[ALARM_MAX_NAME];								// name of remote control [遥控器名称]
	BYTE  reserved[32];										// reserved [保留字段]
}RV_WI_CONFIG_ROBOT;

//wireless alarm output configure [无线报警输出配置]
typedef struct 
{
	BYTE  address[ALARM_MAX_NAME];							//alarm output address [报警输出地址]
	BYTE  name[ALARM_MAX_NAME];								//alarm output name [报警输出名称]
	BYTE  reserved[32];										//reserved [保留字段]
}RV_WI_CONFIG_ALARM_OUT;

typedef struct  
{
	UInt32				dwSize;
	BYTE				bAlarmInNum;						//number wireless alarm input [无线报警输入数]
	BYTE				bAlarmOutNum;						//number of wireless alarm out [无线报警输出数]
	RV_WI_CONFIG_ALARM_OUT AlarmOutAddr[16];				//address of alarm output [报警输出地址]
	BYTE				bRobotNum;							//number of remote control [遥控器个数]
	RV_WI_CONFIG_ROBOT RobotAddr[16];						//address of remote control [遥控器地址]
	RV_INFRARED_INFO	InfraredAlarm[16];
	char				reserved[256];
} RV_INFRARED_CFG;

//new audio detect alarm information [新音频检测报警信息]
typedef struct {
	int channel;						//alarm channel No. [报警通道号]
	int alarmType;						//alarm type,0-audio value low, 1-audio value high [报警类型0--音频值过低 1---音频值过高]
	unsigned int volume;				//audio value [音量值]
	char 	reserved[256];
} RVNET_NEW_SOUND_ALARM_STATE;

typedef struct  
{
	int channelcount;                   //channel number of alarm [报警的通道个数]
	RVNET_NEW_SOUND_ALARM_STATE  SoundAlarmInfo[RV_MAX_ALARM_IN_NUM];
}RV_NEW_SOUND_ALARM_STATE;

//new audio detect alarm configure [新音频检测报警配置]
typedef struct
{
	BOOL				bEnable;							//alarm input enable [报警输入使能]
	int					Volume_min;							//min audio volumn [音量的最小值]
	int					Volume_max;							//max audio volumn [音量的最大值]
	char				reserved[128];	
	RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];	
	RV_MSG_HANDLE		struHandle;							//deal method [处理方式]
} RV_AUDIO_DETECT_INFO;

typedef struct  
{
	UInt32					dwSize;
	int						AlarmNum;
	RV_AUDIO_DETECT_INFO	AudioDetectAlarm[RV_MAX_ALARM_IN_NUM];
	char					reserved[256];
} RV_AUDIO_DETECT_CFG;

//struct of store position, set stand alone per channel, every channel can select every store type, include local, removable, remote store, now [存储位置设置结构体，每通道独立设置,每通道可以选择各种存储类型, 目前包括本地, 可移动, 远程存储.]
typedef struct 
{
	UInt32 	dwSize;
	UInt32 	dwLocalMask;					//mask of local store, flag by bits : [本地存储掩码  按位表示：]
											//bit0:system pre-record [第一位	系统预录]
											//bit1:timer record [第二位	定时录像]
											//bit2:motion detect record [第三位	动检录像]
											//bit3:alarm record [第四位	报警录像]
											//bit4:card record [第五位	卡号录像]
											//bit5:manual record [第六位	手动录像]

	UInt32 	dwMobileMask;					//mask of removable store, store mask eg. local store mask [可移动存储掩码 存储掩码如本地存储掩码]
	int  	RemoteType;						//remote store type, 0:Ftp, 1:Smb [远程存储类型 0: Ftp  1: Smb ]
	UInt32 	dwRemoteMask;					//remote store mask, store mask eg. local store mask [远程存储掩码 存储掩码如本地存储掩码]
	UInt32 	dwRemoteSecondSelLocal;			//local store mask on remote exception [远程异常时本地存储掩码]
	UInt32 	dwRemoteSecondSelMobile;		//removable store mask on remote exception [远程异常时可移动存储掩码]
	char 	SubRemotePath[MAX_PATH_STOR];	//remote folder, the length is 260 [远程目录, 其中长度为260]
	char	reserved[128];
}RV_STORAGE_STATION_CFG;

/************************************************************************
*   network snapshot configure [网络抓包配置]
************************************************************************/
typedef struct
{
	int					Offset;			//bit offset of flag bit [标志位的位偏移]
	int					Length;			//length of flag bit [标志位的长度]
	char				Key[16];		//value of flag bit [标志位的值]
} RV_SNIFFER_FRAMEID;

typedef struct 
{
	int					Offset;			//bit offset of flag bit [标志位的位偏移]
	int					Offset2;		//invalid now [目前没有应用]
	int					Length;			//length of flag bit [标志位的长度]
	int					Length2;		//invalid now [目前没有应用]
	char				KeyTitle[24];	//value of title [标题的值]
} RV_SNIFFER_CONTENT;

typedef struct 
{
	RV_SNIFFER_FRAMEID	snifferFrameId;								//every FRAME's ID option [每个FRAME ID 选项]
	RV_SNIFFER_CONTENT	snifferContent[RV_SNIFFER_CONTENT_NUM];		//every FRAME's four capture package content [每个FRAME对应的4个抓包内容]
} RV_SNIFFER_FRAME;

//every captrue package corresponding configure struct [每组抓包对应的配置结构]
typedef struct
{
	char				SnifferSrcIP[RV_MAX_IPADDR_LEN];			//src IP address of sniffer [抓包源地址]		
	int					SnifferSrcPort;								//src port of sniffer [抓包源端口]
	char				SnifferDestIP[RV_MAX_IPADDR_LEN]; 			//dest IP address of sniffer [抓包目标地址]
	int					SnifferDestPort;							//dest port of sniffer [抓包目标端口]
	char				reserved[28];								//reserved [保留字段]
	RV_SNIFFER_FRAME	snifferFrame[RV_SNIFFER_FRAMEID_NUM];		//6 FRAME options [6个FRAME 选项]
	int					displayPosition;							//display position [显示位置]
	int					recdChannelMask;							//channel mask [通道掩码]
} RV_ATM_SNIFFER_CFG;

typedef struct  
{
	UInt32 dwSize;
	RV_ATM_SNIFFER_CFG SnifferConfig[4];
	char	reserved[256];											//reserved [保留字段]
}RVDEV_SNIFFER_CFG;


/************************************************************************
*   OEM query [OEM查询]
************************************************************************/
typedef struct  
{
	char				szVendor[RV_MAX_STRING_LEN];
	char				szType[RV_MAX_STRING_LEN];
	char				reserved[128];
}RVDEV_OEM_INFO;


/************************************************************************
*   NTP configure [NTP配置]
************************************************************************/

typedef enum __RV_TIME_ZONE_TYPE
{
	RV_TIME_ZONE_0,				// {0, 0*3600,"GMT+00:00"}
	RV_TIME_ZONE_1,				// {1, 1*3600,"GMT+01:00"}
	RV_TIME_ZONE_2,				// {2, 2*3600,"GMT+02:00"}
	RV_TIME_ZONE_3,				// {3, 3*3600,"GMT+03:00"}
	RV_TIME_ZONE_4,				// {4, 3*3600+1800,"GMT+03:30"}
	RV_TIME_ZONE_5,				// {5, 4*3600,"GMT+04:00"}
	RV_TIME_ZONE_6,				// {6, 4*3600+1800,"GMT+04:30"}
	RV_TIME_ZONE_7,				// {7, 5*3600,"GMT+05:00"}
	RV_TIME_ZONE_8,				// {8, 5*3600+1800,"GMT+05:30"}
	RV_TIME_ZONE_9,				// {9, 5*3600+1800+900,"GMT+05:45"}
	RV_TIME_ZONE_10,			// {10, 6*3600,"GMT+06:00"}
	RV_TIME_ZONE_11,			// {11, 6*3600+1800,"GMT+06:30"}
	RV_TIME_ZONE_12,			// {12, 7*3600,"GMT+07:00"}
	RV_TIME_ZONE_13,			// {13, 8*3600,"GMT+08:00"}
	RV_TIME_ZONE_14,			// {14, 9*3600,"GMT+09:00"}
	RV_TIME_ZONE_15,			// {15, 9*3600+1800,"GMT+09:30"}
	RV_TIME_ZONE_16,			// {16, 10*3600,"GMT+10:00"}
	RV_TIME_ZONE_17,			// {17, 11*3600,"GMT+11:00"}
	RV_TIME_ZONE_18,			// {18, 12*3600,"GMT+12:00"}
	RV_TIME_ZONE_19,			// {19, 13*3600,"GMT+13:00"}
	RV_TIME_ZONE_20,			// {20, -1*3600,"GMT-01:00"}
	RV_TIME_ZONE_21,			// {21, -2*3600,"GMT-02:00"}
	RV_TIME_ZONE_22,			// {22, -3*3600,"GMT-03:00"}
	RV_TIME_ZONE_23,			// {23, -3*3600-1800,"GMT-03:30"}
	RV_TIME_ZONE_24,			// {24, -4*3600,"GMT-04:00"}
	RV_TIME_ZONE_25,			// {25, -5*3600,"GMT-05:00"}
	RV_TIME_ZONE_26,			// {26, -6*3600,"GMT-06:00"}
	RV_TIME_ZONE_27,			// {27, -7*3600,"GMT-07:00"}
	RV_TIME_ZONE_28,			// {28, -8*3600,"GMT-08:00"}
	RV_TIME_ZONE_29,			// {29, -9*3600,"GMT-09:00"}
	RV_TIME_ZONE_30,			// {30, -10*3600,"GMT-10:00"}
	RV_TIME_ZONE_31,			// {31, -11*3600,"GMT-11:00"}
	RV_TIME_ZONE_32,			// {32, -12*3600,"GMT-12:00"}
}RV_TIME_ZONE_TYPE;

typedef struct  
{
	BOOL				bEnable;			//	enable [是否启用]
	int					nHostPort;			//	NTP server's default port is 123 [NTP服务器默认端口为123]
	char				szHostIp[32];		//	host's IP [主机IP]
	char				szDomainName[128];	//	domain [域名]
	int					nType;				//	can't set, 0:IP, 1:domain, 2:IP and domain [不可设置 0：表示IP，1：表示域名，2：表示IP和域名]
	int					nUpdateInterval;	//	update time (minute) [更新时间(分钟)]
	int					nTimeZone;			//	reference to RV_TIME_ZONE_TYPE [见RV_TIME_ZONE_TYPE]
	char				reserved[128];
}RVDEV_NTP_CFG;


/************************************************************************
*   platform connection configure - U WANAG TONG [平台接入配置 － U网通]
************************************************************************/
typedef struct
{
	BOOL bChnEn;
	char szChnId[RV_INTERVIDEO_UCOM_CHANID];
}RV_INTERVIDEO_UCOM_CHN_CFG;

typedef struct
{
	UInt32 dwSize;
	BOOL bFuncEnable;										//function enable 0 - enable [接入功能使能与否 0 - 使能]
	BOOL bAliveEnable;										//alive enable [心跳使能与否]
	UInt32 dwAlivePeriod;									//heart cycle, unit is second 0-3600 [心跳周期，单位秒，0-3600]
	char szServerIp[RV_MAX_IPADDR_LEN];						//CMS's IP [CMS的IP]
	WORD wServerPort;										//CMS's port [CMS的Port]
	char szRegPwd[RV_INTERVIDEO_UCOM_REGPSW];				//regiter password [注册密码]
	char szDeviceId[RV_INTERVIDEO_UCOM_DEVID];				//device's id [设备id]
	char szUserName[RV_INTERVIDEO_UCOM_USERNAME];
	char szPassWord[RV_INTERVIDEO_UCOM_USERPSW];
	RV_INTERVIDEO_UCOM_CHN_CFG  struChnInfo[RV_MAX_CHANNUM];//channel id,en [通道id,en]
}RVDEV_INTERVIDEO_UCOM_CFG;

/************************************************************************
*   platform connection configure - alcater [平台接入配置 － 阿尔卡特]
************************************************************************/
typedef struct
{
	UInt32 dwSize;
	unsigned short usCompanyID[2];		/* Corp. ID, value, different three part service Corp. consider 4 bytes justification, only use the first in array now [公司ID,数值,不同的第三方服务公司,考虑4字节对齐,目前只用数组第一个] */
	char szDeviceNO[32];				/* serial number of front device, string, conrain '\0' total 32 bytes [前端设备序列号，字符串, 包括'\0'结束符共32byte] */
	char szVSName[32];					/* front device, string, contain '\0' total 16 bytes [前端设备名称，字符串, 包括'\0'结束符共16byte] */
	char szVapPath[32];					/* VAP path [VAP路径] */
	unsigned short usTcpPort;			/* TCP port, value : 1~65535 [TCP 端口,数值: 数值 1~65535] */    
	unsigned short usUdpPort;			/* UDP port, value : 1~65535 [UDP 端口,数值: 数值 1~65535] */    
	//bool bCsEnable[4];					/* enable of center server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [中心服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szCsIP[16];					/* IP address of center server, string, contain '\0' total 16 bytes [中心服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usCsPort[2];			/* port of center server, value : 1~65535, consider 4 bytes justification, only use the first in array now [中心服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */    
//	bool bHsEnable[4];					/* enable of heart beat server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [心跳服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szHsIP[16];					/* IP address of heart beat server, string, contain '\0' total 16 bytes [心跳服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usHsPort[2];			/* port of heart beat server, value : 1~65535, consider 4 bytes justification, only use the first in array now [心跳服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */ 
	int iHsIntervalTime;				/* time slice of heart beat server, value (unit:second) [心跳服务器间隔周期,数值(单位:秒)] */ 
//	bool bRsEnable[4];					/* enable of registration server, value : true enable, false not enable, consider 4 bytes justification, only use the first in array now [注册服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szRsIP[16];					/* IP address of registration server, string, contain '\0' total 16 bytes [注册服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usRsPort[2];			/* port of registration server, value : 1~65535, consider 4 bytes justification, only use the first in array now [注册服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */
	int iRsAgedTime;					/* valid time of registration server, value (unit:hour) [注册服务器有效时间,数值(单位:小时)] */
	char szAuthorizeServerIp[16];		/* IP address of authority server [鉴权服务器IP] */
	unsigned short usAuthorizePort[2];  /* port of authority server, value : 1~65535, consider 4 bytes justification, only use the first in array now [鉴权服务器端口,考虑4字节对齐,目前只用数组第一个] */
	char szAuthorizeUsername[32];		/* account of authority server [鉴权服务器帐号] */
	char szAuthorizePassword[36];		/* password of authority server [鉴权服务器密码] */

	char szIpACS[16];					/* ACS (auto registration server) IP [ACS(自动注册服务器) IP] */
	unsigned short usPortACS[2];		/* ACS port, consider 4 bytes justification, only use the first in array now [ACS Port,考虑4字节对齐,目前只用数组第一个] */
	char szUsernameACS[32];				/* ACS user name [ACS用户名] */
	char szPasswordACS[36];				/* ACS password [ACS密码] */
	//bool bVideoMonitorEnabled[4];		/* if DVS timer to up-send message of fornt video signal watch, value : true enable, false not enable [DVS是否定期上报前端视频信号监控信息, 数值: true使能, false不使能] */
	int iVideoMonitorInterval;			/* up-send timer slice (minute) [上报周期（分钟）] */

	char szCoordinateGPS[64];			/* GPS coordinate [GPS坐标] */
	char szPosition[32];				/* device position [设备位置] */
	char szConnPass[36];				/* device connection passport [设备接入码] */
}RVDEV_INTERVIDEO_BELL_CFG;

//威思通配置结构--EPLAY_TYPE_XMWST
typedef struct tagCONFIG_WST_NET
{
	int   bEnable; //使能
	char  acSeverName[128];//服务器域名
	int   iServerPort;//服务器侦听端口
	int   iType;//协议类型 0 tcp 1 udp
	char  acDVRID[32];//DVR设备ID号
	int   acReserve;//保留位
}CONFIG_WST_NET;

// IPv6配置结构体DEV_CONFIG_TYPE_ETHERNET_IPV6
typedef struct _CONFIG_NET_ETH_IPV6
{
	char strEthName[16];/*网卡名字*/
	char IP[48]; //!主机IP    
	int iPrefix; //!子网掩码
	char Gateway[48]; //!网关IP
	unsigned char dhcpEnable;/*dhcp使能标志*/
	unsigned char  ucRes1[3];/*保留*/
	char dns1[48]; //!dns    
	char dns2[48]; //!备用dns
	unsigned char  ucRes2[16]; //保留字
} CONFIG_NET_ETH_IPV6;

// 平台日志长度查询--DEV_INTERVIDEO_LOG_LENTH
typedef struct _INTERVIDEO_LOG_LENTH_T
{
	int iInterVideoType;	// 平台编号 
	int iLenth;				// 日志长度，请求时这个值填0 
}INTERVIDEO_LOG_LENTH_T;

// 平台日志内容查询--DEV_INTERVIDEO_LOG_DATA
// 当日志内容发生变化，请求的内容不存在时，返回iLen按照实际返回，0表示没有 
typedef struct _INTERVIDEO_LOG_DATA_T
{
	int iInterVideoType;	// 平台编号 
	int iLen;				// 请求的日志内容的长度
	int iStart;				// 日志内容起始位置
	int iEnd;				// 日志内容结束位置
}INTERVIDEO_LOG_DATA_T;

// 平台日志清除操作--DEV_INTERVIDEO_LOG_DELETE
typedef struct _INTERVIDEO_LOG_DELETE_T
{
	int iInterVideoType;	// 平台编号
	int iRet;				// 结果
}INTERVIDEO_LOG_DELETE_T;

/************************************************************************
*   configure of plartform connection - ZHONGXINGLIWEI [平台接入配置 － 中兴力维]
************************************************************************/
typedef struct  
{
	UInt32 dwSize;
	unsigned short		nSevPort;								//server port, value 1~65535 [服务器端口, 数值, 数值1~65535]
	char				szSevIp[RV_INTERVIDEO_NSS_IP];			//server IP address, string, contain '\0', total 32 bytes [服务器IP地址, 字符串, 包括'\0'结束符共32byte]
	char				szDevSerial[RV_INTERVIDEO_NSS_SERIAL];	//serial number of front device, string, contain '\0', total 32 bytes [前端设备序列号，字符串,包括'\0'结束符共32byte]
	char				szUserName[RV_INTERVIDEO_NSS_USER];
	char				szPwd[RV_INTERVIDEO_NSS_PWD];
}RVDEV_INTERVIDEO_NSS_CFG;

/************************************************************************
*   state information of network running [网络运行状态信息]
************************************************************************/

typedef struct
{
	int					nChannelNum;	//channel No. [通道号]
	char				szUseType[32];	//channel usage [通道用途]
	UInt32				dwStreamSize;	//flow rate (unit is kb/s) [流量大小(单位:kb/s)]
	char				reserved[32];	//reserved [保留]
}RVDEV_USE_CHANNEL_STATE;

typedef struct 
{
	char						szUserName[32];				//user name [用户名]
	char						szUserGroup[32];			//user group [用户组]
	RVNET_TIME					time;						//logined time [登入时间]
	int							nOpenedChannelNum;			//opened channel number [开启的通道个数]
	RVDEV_USE_CHANNEL_STATE		channelInfo[RV_MAX_CHANNUM];
	char						reserved[64];
}RVDEV_USER_NET_INFO;

typedef	struct 
{
	int							nUserCount;		//user count [用户数量]
	RVDEV_USER_NET_INFO			stuUserInfo[32];
	char						reserved[256];
}RVDEV_TOTAL_NET_STATE;
/************************************************************************
*   attributes of PTZ [云台属性信息]
************************************************************************/
#define  NAME_MAX_LEN 16
typedef struct 
{
	UInt32		dwHighMask;				/*!< high bits of operation's mask [操作的掩码高位] */
	UInt32		dwLowMask;				/*!< low bits of operation's mask [操作的掩码低位] */
	char		szName[NAME_MAX_LEN];	/*!< operation's protocal name, NAME_MAX_LEN=16 [操作的协议名NAME_MAX_LEN=16] */
	WORD		wCamAddrMin;			/*!< channel address's min value [通道地址的最小值] */
	WORD		wCamAddrMax;			/*!< channel address's max value [通道地址的最大值] */
	WORD		wMonAddrMin;			/*!< watch address's min value [监视地址的最小值] */
	WORD		wMonAddrMax;			/*!< watch address's max value [监视地址的最大值] */
	BYTE		bPresetMin;				/*!< preset's min value [预置点的最小值] */
	BYTE		bPresetMax;				/*!< preset's max value [预置点的最大值] */
	BYTE		bTourMin;				/*!< auto tour's min value [自动巡航线路的最小值] */
	BYTE		bTourMax;				/*!< auto tour's max value [自动巡航线路的最大值] */
	BYTE		bPatternMin;			/*!< tour's min value [轨迹线路的最小值] */
	BYTE		bPatternMax;			/*!< tour's max value [轨迹线路的最大值] */
	BYTE		bTileSpeedMin;			/*!< vertical speed's min value [垂直速度的最小值] */
	BYTE		bTileSpeedMax;			/*!< vertical speed's max value [垂直速度的最大值] */
	BYTE		bPanSpeedMin;			/*!< horizontal speed's min value [水平速度的最小值] */
	BYTE		bPanSpeedMax;			/*!< horizontal speed's max value [水平速度的最大值] */
	BYTE		bAuxMin;				/*!< assist function's min value [辅助功能的最小值] */
	BYTE		bAuxMax;				/*!< assist function's max value [辅助功能的最大值] */
	int			nInternal;				/*!< send command's time slice [发送命令的时间间隔] */
	char		cType;					/*!< protocal's type [协议的类型] */
	char		Reserved[7];
}RVPTZ_OPT_ATTR;
/************************************************************************
*   returned information of setting device [设置设备返信息]
************************************************************************/
typedef struct
{
	UInt32		dwType;			//type, the same as type of GetDevConfig SetDevConfig [类型(即GetDevConfig SetDevConfig的类型)]
	UInt16		wResultCode;	//recturned code [返回码：]
								/*		0:success [成功]
								*		1:fail [失败]
								*		2:data invalid [数据不合法]
								*		3:can't set now [暂时无法设置]	
								*		4:no authority [没有权限]
								*/

	UInt16   	wRebootSign;	//reboot flag [重启标志：]
								/*
								*	0:no need to reboot, 1:need to reboot to make it valid [0:不需要重启 1:需要重启才生效]
								*/
	Int32		dwReserved[2];	//reserved [保留]	
}RVDEV_SET_RESULT;

/******************************************************************************
* attributes struct of snapshot function [抓图功能属性结构体]
*****************************************************************************/

typedef struct 
{
	int			nChannelNum;			//channel index [通道号]

	UInt32		dwVideoStandardMask	;	//resolve (by bit) detail reference to enum CAPTURE_SIZE [分辨率(按位) 具体查看枚举 CAPTURE_SIZE]
	int			nFramesCount;			//valid length of [Frequence[128] array [Frequence[128]数组的有效长度]
	char 		Frames[128];			//frame rate (by value) [帧率（按数值）]
										//-25:25 seconds per frame [-25:25秒1帧]
										//-24:24 seconds per frame [-24:24秒1帧]
										//-23:23 seconds per frame [-23:23秒1帧]
										//-22:22 seconds per frame [-22:22秒1帧]
										//……
										//0:valid [0:无效]
										//1:1 frames per second [1：1秒1帧]
										//2:2 frames per second [2：1秒2帧]
										//3:3 frames per second [3：1秒3帧]
										//4:4 frames per second [4：1秒4帧]
										//5:5 frames per second [5：1秒5帧]
										//17:17 frames per second [17：1秒17帧]
										//18:18 frames per second [18：1秒18帧]
										//19:19 frames per second [19：1秒19帧]
										//20:20 frames per second [20：1秒20帧]
										//……
										//25:25 frames per second [25: 1秒25帧]
	int			nSnapModeCount;			//valid length of SnapMode[16] array [SnapMode[16]数组的有效长度]
	char		SnapMode[16];			//(by value) 0:timer snapshot 1:manual triggered snapshot [（按数值） 0：定时触发抓图 1：手动触发抓图]
	int			nPicFormatCount;		//valid length of Format[16] array [Format[16]数组的有效长度]
	char 		PictureFormat[16];		//by value 0:BMP format 1:JPG format [（按数值）0:BMP格式 1:JPG格式]
	int			nPicQualityCount;		//valid length of Quality[32] array [Quality[32]数组的有效长度]
	char 		PictureQuality[32];		//(by value) [（按数值）]
										//100:picture quality 100% [100:图象质量100%]
										//80:picture quality 80% [80:图象质量80%]
										//60:picture quality 60% [60:图象质量60%]
										//50:picture quality 50% [50:图象质量50%]
										//30:picture quality 30% [30:图象质量30%]
										//10:picture quality 10% [10:图象质量10%]
	char 		nReserved[128];			//reserved [保留]
} RV_QUERY_SNAP_INFO;

typedef struct 
{
	int			nChannelCount;					//channel number [通道个数]
	RV_QUERY_SNAP_INFO  stuSnap[RV_MAX_CHANNUM];
}RV_SNAP_ATTR_EN;

typedef struct  
{
	int	iLen;			//real data lenght [实际数据长度]
	int iChannel;		//channel index [通道号]
	char acData[32];	//real data [实际数据]
}RV_PTZ_RAW_DATA_H;

typedef struct  
{
	int	iLen;			//real data lenght [实际数据长度]
	int iChannel;		//channel index [通道号]
	char *pData;
}RV_PTZ_RAW_DATA_H_EX;
/******************************************************************************
* attributes struct of auto registration function [主动注册功能属性结构体]
*****************************************************************************/
typedef struct
{
	UInt32	 dwSize;
	Int32     iEnable;			//enable [使能]
	Int32     iConnectType;		//connection method, 0:single connection(using old command media single connection mode), 1:multi connections (commands auto register to server, media need to dynamicly reconnect to server under command control eg. case of video request) [连接方式，0：单连接（使用原有的信令媒体单一连接模式） 1：多连接 （采取信令为主动注册连接，媒体需要在信令控制如视频请求情况下进行新的动态连接方式）
	char	 strServerIp[16];	//ip of registration server [注册服务器ip]	
	Int32     iServerPort;		//port of registration server [注册服务器端口]
	char     strUsr[64];		//user name [用户名]
	char     strPwd[64];		//password [密码]
	char     strPuId[32];		//device identify, 32bits, recording to platform server definition [设备统一标识，32位标识，由平台服务器约定]
								/*
								rule of identify device [设备统一标识规则] 
								using 32 bytes now, details recording to platform server definition [现有使用了32字节，具体信息安排，由平台服务器约定规则]
								
								Xx							yy						zz											a      								b						cccccccc cccccccc ccccccccc
								2 bytes	[2字节]				2 bytes	[2字节]			2 bytes	[2字节]								1 byte [1字节]     					1 byte [1字节]			24 bytes [24字节] 
								No. in province [省级编号]	No. in city [市级编号]	reserved for No. in city [市级编号保留字]	front 0,client1 [前端 0，客户端1]	device type [设备类型]	device serial number [设备序号]
								
								values of device type : 01:DVR 02:IPC 03:NVS 04:decoder 05:DVR on vehicle [其中设备类型 01： DVR； 02 ：IPC ；03：NVS ； 04 ：解码器；05：车载DVR]
								*/
}RV_CONFIG_REG_SERVER;

//主动注册服务器
typedef struct {
	int      iEnable;   //使能
	int      iConnectType; //连接方式，0：单连接（使用原有的信令媒体单一连接模式）
	//1：多连接 （采取信令为主动注册连接，媒体需要在信令控制如视频请求情况下进行新的动态连接方式）
	char strServerIp[128]; //注册服务器ip，修改为128字节的长度，域名要求不超过128字节
	int     iServerPort;   //注册服务器端口
	char     strUsr[64];    //用户名
	char     strPwd[64];   //密码
	char     strPuId[32];   //设备统一标识，32位标识，由平台服务器约定
							/*
							设备统一标识规则
							现有使用了32字节，具体信息安排，由平台服务器约定规则
							Xx          yy          zz                    a       b
							2字节 2字节       2字节 1字节      1字节
							省级编号    市级编号     市级级别编号保留字     前端 0，客户端1 设备类型
							cccccccc cccccccc ccccccccc
							24字节 设备序号
							其中设备类型 01： DVR； 02 ：IPC ；03：NVS ； 04 ：解码器；05：车载DVR
	*/
	char strRes[128];//保留字，方便后续扩展使用
}RV_CONFIG_REG_SERVER_EX;

// 主动注册服务器回调函数返回结果结构体
typedef struct _SRegDevInfo
{
	int      iEnable;			//使能
	int      iConnectType;		//连接方式，0：单连接（使用原有的信令媒体单一连接模式） 1：多连接 （采取信令为主动注册连接，媒体需要在信令控制如视频请求情况下进行新的动态连接方式）
	char	 strServerIp[16];	//注册服务器ip		
	int      iServerPort;		//注册服务器端口
	char     strUsr[64];		//用户名
	char     strPwd[64];		//密码
	char     strPuId[32];		//设备统一标识，32位标识，由平台服务器约定
								/*
								设备统一标识规则 
								现有使用了32字节，具体信息安排，由平台服务器约定规则
								Xx          yy          zz                    a      				b     
								2字节		2字节       2字节					1字节     			1字节
								省级编号    市级编号     市级级别编号保留字     前端 0，客户端1		设备类型
								cccccccc cccccccc ccccccccc
								24字节 设备序号
								
								  其中设备类型 01： DVR； 02 ：IPC ；03：NVS ； 04 ：解码器；05：车载DVR
								*/
}SRegDevInfo;

/******************************************************************************
* attributes struct of tour function [轮巡功能属性结构体]
*****************************************************************************/
#define V_TOUR_COMBINE_NUM 10
typedef struct
{
	unsigned int iSplitMode;	//support many multi-views preview mode, flag by bits, reference to enum split_combine_t [支持多种画面预览模式，按位标识，参考枚举split_combine_t]
								//bit0 : SPLIT1, this is default in all devices, this is sinlg view and full screen [第0位 SPLIT1 此默认都支持，此为单画面，全屏]
								//bit1 : SPLIT2 [第1位 SPLIT2] 
								//bit2 : SPLIT4 [第2位 SPLIT4]
								//bit3 : SPLIT8 [第3位 SPLIT8] 
								//bit4 : SPLIT9 [第4位 SPLIT9]
								//bit5 : SPLIT16 [第5位 SPLIT16] 
								//bit6 : SPLITIP [第6位 SPLITIP]
								//bit7 : SPLIT6 [第7位 SPLIT6] 
								//bit8 : SPLIT12 [第8位 SPLIT12]
}RV_SPLIT_MODE;
typedef struct
{
	unsigned char bTourEnable;		//enable [使能]
	unsigned char ucRes;	
	unsigned short usIntervalTime;	//tour time slice [轮巡时间间隔]
}RV_DISPLAY_TOUR_CFG;
typedef struct
{
	UInt32	 dwSize;
	RV_DISPLAY_TOUR_CFG stDisplayTour;
	RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
}RV_DISPLAY_TOUR;

/******************************************************************************
* struct of views split function [画面分割功能属性结构体]
*****************************************************************************/
typedef struct
{
	RV_SPLIT_MODE stSplitMode;		//mode [模式]
	RV_SPLIT_COMBINE_CH stCombineCH;//channel combine [通道组合]
}RV_DISPLAY_SPLIT_CFG;

/******************************************************************************
* channel combine and tour struct of decoder views group [解码器画面分组通道组合以及轮询结构体]
*****************************************************************************/
typedef struct
{
	UInt32	 dwSize;
	RV_DISPLAY_SPLIT_CFG stSplitCfg;
	RV_DISPLAY_TOUR_CFG stTourCfg;
	Int32 iCombineNum;
	RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
}RV_WSCC;

/******************************************************************************
* struct of snapshot [抓图配置结构体]
*****************************************************************************/
#define MAX_SNAP_COUNT 32
typedef struct
{   	    	
	int iChannel;
	int Enable;					/*enable of timer snapshot [定时抓拍使能]*/
	int SnapQuality;			/*picture quality of snapshot, 6 levels, 1:bad, 2:not bad, 3:common, 4:good, 5:better, 6:best [抓拍图像质量，初步分6档， 1 差 2 一般 3普通， 4好， 5很好， 6最好]*/
								/*snap plot [抓图策略]
								 usSnapMode : snapshot mode, 0 means mode of how many pictures per second [usSnapMode 抓拍模式， 0 表示1秒几张模式]
															 1 means mode of how many seconds per picture [1 表示几秒1张模式]
															 2 means mode of how many minutes per picture [2 表示几分钟1张模式]
								 usCounts : value corresponding snapshot mode [usCounts 对应抓拍模式下的数值]
								*/
	unsigned short usSnapMode;
	unsigned short usCounts;	/*snapshot picture number (under mode of how many pictures per second) or snapshot time (mode of how many seconds per picture) [抓拍张数（1秒几张模式）或者抓拍时间（几秒1张模式）]*/
	int SnapCount;
}RV_CONFIG_SNAP;
typedef struct
{
	UInt32 dwSize;
	UInt32 dwCount;								//on setting:==channel count is all, >=0&&<channel count is which channel configure [设置时：==通道数为所有，>=0&&<通道数为哪个通道配置]
												//on getting:returned number [读取时：返回个数]
	RV_CONFIG_SNAP stSnapCfg[MAX_SNAP_COUNT];
}RV_SNAP;

typedef struct
{
	unsigned short usTotal;  //total channel number [总通道数目]
	unsigned short usIndex;  //which channel's information [第几个通道信息]
}RV_DEV_CHANNEL;

/******************************************************************************
* struct of decoder [解码器报警配置结构体]
*****************************************************************************/
#define RV_N_UI_TSECT					6
#define RV_N_WEEKS						7
typedef struct
{
	int				enable;		    //enable [使能]
	unsigned char	startHour; 		//start time : hour [开始时间:小时]		
	unsigned char	startMinute;	//start time : minute [开始时间:分钟]		
	unsigned char	startSecond; 	//start time : second [开始时间:秒钟]		
	unsigned char	endHour;		//end time : hour [结束时间:小时]		
	unsigned char	endMinute; 		//end time : minute [结束时间:分钟]		
	unsigned char	endSecond; 		//end time : second [结束时间:秒钟]		
	unsigned char   ucReserved[2];  //reserved [保留]
}RV_NETSECTION;		
typedef struct
{
	int				iName;
	RV_NETSECTION	tsSchedule[RV_N_WEEKS][RV_N_UI_TSECT];	/*time slice [时间段]*/
}RV_NET_WORKSHEET;
#define RV_N_SYS_CH 16
typedef struct
{		
	unsigned int		dwRecord;				/* record mask [录象掩码] */
	int					iRecordLatch;			/* record delay : 10~300 second [录像延时：10～300 sec] */ 	
	unsigned int		dwTour;					/* tour mask [轮巡掩码] */	
	unsigned int		dwSnapShot;				/* snapshot mask [抓图掩码] */
	unsigned int		dwAlarmOut;				/* alarm output channel mask [报警输出通道掩码] */
	int					iAOLatch;				/* alarm output delay : 10~300 second [报警输出延时：10～300 sec] */ 
	RV_PTZ_LINK			PtzLink[RV_N_SYS_CH];	/* PTZ linkage items [云台联动项] */		
	int					bRecordEn;				/* record enable [录像使能] */
	int					bTourEn;				/* tour enable [轮巡使能] */
	int					bSnapEn;				/* snapshot enable [抓图使能] */	
	int					bAlarmOutEn;			/* alarm enable [报警使能] */
	int					bPtzEn;					/* PTZ linkage enable [云台联动使能] */
	int					bTip;					/* screen prompt enable [屏幕提示使能] */	
	int					bMail;					/* send email [发送邮件] */	
	int					bMessage;				/* send message to alarm center [发送消息到报警中心] */	
	int					bBeep;					/* beep [蜂鸣] */	
	int					bVoice;					/* audio prompt [语音提示] */		
	int					bFTP;					/* lauch FTP transport [启动FTP传输] */		
	int					iWsName;				/* time table selection, because it is using number as index in time table, and will not be changed [时间表的选择，由于时间表里使用数字做索引，且不会更改] */
	unsigned int		dwMatrix;				/* matrix mask [矩阵掩码] */
	int					bMatrixEn;				/* matrix enable [矩阵使能] */
	int					bLog;					/* log enable, it is just be using in WTN motion detect [日志使能，目前只有在WTN动态检测中使用] */
	int					iEventLatch;			/* linkage start delay time, second is unit [联动开始延时时间，s为单位] */
	int					bMessagetoNet;			/* send message to network enable [消息上传给网络使能] */
	unsigned int		wiAlarmOut; 		/*!< 无线报警输出 */
	unsigned int		dwReserved[6]; 			/* reserved [保留字节] */
}RV_EVENT_HANDLER;
typedef struct
{
	int iEnable;	//alarm guard enable, 0:disable, 1:enable [告警布防撤防 0撤防，1布防]
	int iReserved;	//common configure, details as bellow [通用配置信息，具体定义如下]
					//in alarm input, this means sensor type, 0:always opened, 1:always closed [告警输入标识传感器类型常开 or 常闭；0常开，1常闭]
					//in video lost and motion detect, this means sensitivity : 0~6 levels, level 6 is most sensitivity [视频丢失和动检为灵敏度；0~6档次，6档次为最灵敏]
					//in disk, this means the lowest limit of left space in disk, percent [磁盘为硬盘剩余容量下限, 百分数]
					//in intelligent red alarm, this means sensitivity : 0~6 levels, level 6 is most sensitivity [智能红色报警为灵敏度；0~6档次，6档次为最灵敏]
}RV_ALARM_GUARD;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
} RV_DECODER_ALARM,*LPRV_DECODER_ALARM;
 
typedef struct
{
	UInt32 dwSize;		
	RV_DECODER_ALARM 		struDecoderAlarm[RV_MAX_DECODER_CHAN_NUM]; //16-32 最大通道数目 zb
}RV_DECODER_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//	other alarm structs [其他报警结构]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
} RV_GEN_ALARM; 
#define RV_MD_REGION_ROW	32
typedef struct
{
	int iRowNum;
	int iColNum;
	BYTE byRegion[32][32];
}RV_REGION;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_REGION				stRegion;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
} RV_MOTION_ALARM; 
typedef struct
{
	UInt32 dwSize;		
	RV_GEN_ALARM 		struLocalAlarmIn[RV_MAX_CHANNUM];	// 本地输入报警联动配置
	RV_MOTION_ALARM		struMotionAlarm[RV_MAX_CHANNUM];	// 动态检测报警联动配置
	RV_GEN_ALARM 		struVideoLossAlarm[RV_MAX_CHANNUM]; // 视频丢失报警联动配置
	RV_GEN_ALARM 		struVideoBindAlarm[RV_MAX_CHANNUM]; // 视频遮挡报警联动配置
	RV_GEN_ALARM 		struNoDiskAlarm;	// 无硬盘报警联动配置
	RV_GEN_ALARM 		struDiskErrAlarm;	// 硬盘错误报警联动配置
	RV_GEN_ALARM 		struDiskFullAlarm;	// 硬盘满报警联动配置
	RV_GEN_ALARM 		struNetBrokenAlarm;	// 网络异常报警联动配置
	RV_GEN_ALARM 		struIPConflictAlarm;// IP冲突报警联动配置
}RV_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//	TV adjuest struct [TV调节结构]
//////////////////////////////////////////////////////////////////////
typedef struct 
{
	int left;	//[0,100]
	int top;	//[0,100]
	int right;	//[0,100]
	int bottom;	//[0,100]
}RV_VD_RECT;
//TV adjust configure [TV调节设置]
typedef struct
{
	UInt32 dwSize;
	RV_VD_RECT rctMargin;		//TV zoom out rate, every value's range are the same [0,100] [TV缩小比率，各分量取值相同   [0,100]]		
	int iBrightness;			//brightness [0,100] [亮度[0,100]]		
	int iContrast;				//contrast [0,100] [对比度[0,100]]	
	int iAntiDither;			//antidither [0,100] [去抖动[0,100]]
}RV_TVADJUST;

//////////////////////////////////////////////////////////////////////
//	common configure [普通配置]
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//	struct of daylight saving time [夏令时结构体]
typedef struct
{
	int Hour;
	int Minute;
}RV_DSTTIMES;
typedef struct
{
	int iYear;			//year [2000,2037]
	int iMonth;			//month from January=1 [1,12]
	int iWeek;			//week1:first  to2 3 4 -1:last one   0:calculate method by days [-1,4] [周1:first  to2 3 4 -1:last one   0:表示使用按日计算的方法[-1,4]]
	union
	{
		int iWeekDay;	//weekday from sunday=0 [0, 6]
		int iDays;		//day from one=1[0, 31]
	};	
	RV_DSTTIMES time;
}RV_DST_POINT;
//week mode selection [周模式选择]
//iMonth，iWeek(-1,1,2,3,4)， iWeekDay，Hour，Min
//day mode selection, iWeek=0 [日模式选择 iWeek=0]
//iYear ,iMonth,iDays，Hour，Min
typedef struct
{
	RV_DST_POINT iDST[2];
	unsigned char ucEnable;//0:disable, 1:enable [0,不使能，1使能]
	unsigned char ucRes[3];//reserved [保留] 
}RV_DST_TIME;
typedef struct
{ 		
	int  iCtrlMask;						/*flag by bit mask [按位掩码形式]
										0 : deal on disk full, 1:OverWrite, 0:StopRecord [0 硬盘满时处理 1覆盖"OverWrite", 0停止"StopRecord"] 
										1 : if mute [1 是否静音]
										2 : LCD screen auto close [2 LCD屏幕自动关闭]
										3 : if TV output [3 是否TV输出]
										4 : if VGA output [4 是否VGA输出]
										5 : if HDMI output [5 是否HDMI输出]
										*/		
	int iLocalNo;						//local machine No. : [0,?998]? [本机编号:[0,?998]? ]
	unsigned short usScreenSaveTime;	//screen protection (minute) [0,120] [屏保时间(分钟) [0, 120]	]
	unsigned short usAutoLogout;		//local menu auto logout (minute) [0, 120] [本地菜单自动注销(分钟) [0, 120]]
	unsigned char ucDateFormat;			//date format :"YYMMDD","MMDDYY","DDMMYY" [日期格式:“YYMMDD”, “MMDDYY”, “DDMMYY” ]
	unsigned char ucDateSprtr;			//date seperate : ".","-","/" [日期分割符:“.”, “-”, “/”] 
	unsigned char ucTimeFmt;			//time format : 1:12, 0:24 [时间格式:1：“12”, 0：“24”] 
	unsigned char ucRes;
	unsigned char ucSupportVideoFmt;	//device supported video standard, bit0:PAL, bit1:NTSC, bit2:SECAM [设备可以支持的制式 ， 第0位 PAL ，第1位 NTSC， 第2位 SECAM]
	unsigned char ucCurVideoFmt;		//device used video standard, 0:PAL, 1:NTSC, 2:SECAM [设备使用的制式 ，0 PAL ，1 NTSC， 2 SECAM]
	unsigned char ucRes1[2];
	unsigned int uiSupportLanguage;		//device supported languages [设备可以支持的语言 ， ]
										//bit0:English, bit1:SimpChinese, bit2:TradChinese [第0位 English，第1位 SimpChinese， 第2位 TradChinese，]
										//bit3:Italian, bit4:Spanish, bit5:Japanese, bit6:Russian, bit7:French, bit8:German [第3位 “Italian”,4 “Spanish”, 5“Japanese”, 6“Russian”, 7“French”, 8“German” ]
	unsigned int uiCurLanguage;			//device used languages [设备使用的语言 ，]
										//0:English, 1:SimpChinese, 2:TradChinese, 3:Italian, 4:Spanish [0 English，1 SimpChinese，2 TradChinese，3“Italian”,4 “Spanish”,] 
										//5:Japanese, 6:Russian, 7:French, 8:German [5“Japanese”, 6“Russian”, 7“French”, 8“German”] 
	unsigned int uiRes[3];				//reserved [保留字节]						
}RV_NET_GENERAL;

//2010-10-12 luhj add
typedef struct  
{
	char	cSize;						//字体大小，1表示标准倍数，2表示2倍大小  该值取值范围在1到ucZoomAbility之间
	char	cRes[3];					//保留
}RV_OSDZOOM_PARAM;
//end
// system time struct [系统时间结构]
typedef struct
{
	int  year;	//year [2000,2037] [年。[2000,2037]]   
	int  month;	//month January = 1, February = 2, and so on. [月，January = 1, February = 2, and so on. ]  
	int  day;	//day [日。]   
	int  wday;	//week, Sunday = 0, Monday = 1, and so on [星期，Sunday = 0, Monday = 1, and so on]   
	int  hour;	//hour [时。]   
	int  minute;//minute [分。]  
	int  second;//second [秒。]   
	int  isdst;	//flag daylight saving time [夏令时标识。]   
}RV_SYSTEM_TIME;
#define RV_MAX_DRIVERINFO 64
typedef  struct
{
	UInt32 dwSize;
	RV_NET_GENERAL stGeneral;
	RV_SYSTEM_TIME stCurTime;
	RV_DST_TIME stDst;
}RV_COMM_CFG;
//////////////////////////////////////////////////////////////////////
//	platform connection configure [平台接入配置]
//////////////////////////////////////////////////////////////////////
//platform of HUXINGHUTONG [互信互通平台接入配置]
typedef struct
{
	UInt32 dwSize;
	BOOL			Enable;			//enable [使能]
	int				MaxConn;		//max connection number of video connection [视频最大连接数]	
	char			ServerIp[40];	//server IP [服务器IP]	
	unsigned short	ServerPort;		//server Port [服务器端口]
	unsigned short	MegaPort;		//listen port [监听端口]	
	char			DeviceId[32];	//device ID [设备ID]	
	char			UserName[32];	//user name [用户名]
	char			PassWords[32];	//password [密码]
	unsigned short	DownLoadMode;	//record download method by bits, 0:TCP, 1:HTXT [录像下载方式按位0 TCP 1 HTXT]
	unsigned short	FunMask;		/*function mask, operate by bits [功能掩码，按位操作]
									bit0:if support prediction scheme [第0位是否支持预案]
									bit1:if support network management [第1位是否支持网管]
									bit2:if support pre-record [第2位是否支持预录]
									bit3:if support NAT [第3位是否支持NAT]
									*/	
	unsigned short	AlarmInterVal;	//alarm time slice [报警间隔]
	unsigned short	Reserve;
}RV_CONFIG_NET_MEGA;
/************************************************************************
*   platform of ALCATEL [平台接入配置 － 阿尔卡特]
************************************************************************/
typedef struct
{
	unsigned short usCompanyID[2];		/* Corp.ID, value, different three part service Corp. consider 4 bytes justification, using the first of the array [公司ID,数值,不同的第三方服务公司,考虑4字节对齐,目前只用数组第一个] */
	char szDeviceNO[32];				/* serial number of front device, string, contain '\0', total 32 bytes [前端设备序列号，字符串, 包括'\0'结束符共32byte] */
	char szVSName[32];					/* name of front device, string, contain '\0', total 16 bytes [前端设备名称，字符串, 包括'\0'结束符共16byte] */
	char szVapPath[32];					/* VAP path [VAP路径] */
	unsigned short usTcpPort;			/* TCP port, value : 1~65535 [TCP 端口,数值: 数值 1~65535] */    
	unsigned short usUdpPort;			/* UDP port, value : 1~65535 [UDP 端口,数值: 数值 1~65535] */    
	//bool bCsEnable[4];					/* enable flag of center server, consider 4 bytes justification, using the first of the array [中心服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szCsIP[64];					/* IP of center server, string, contain '\0', total 16 bytes [中心服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usCsPort[2];			/* port of center server, consider 4 bytes justification, using the first of the array [中心服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */    
//	bool bHsEnable[4];					/* enable flag of heart beat server, consider 4 bytes justification, using the first of the array [心跳服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szHsIP[64];					/* IP of heart beat server, string, contain '\0', total 16 bytes [心跳服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usHsPort[2];			/* port of heart beat server, consider 4 bytes justification, using the first of the array [心跳服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */ 
	int iHsIntervalTime;				/* time slice of heart beat server, value (unit : second) [心跳服务器间隔周期,数值(单位:秒)] */ 
	//bool bRsEnable[4];					/* enable flag of registration server, consider 4 bytes justification, using the first of the array [注册服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个] */
	char szRsIP[64];					/* IP of registration server, string, contain '\0', total 16 bytes [注册服务器IP地址, 字符串, 包括'\0'结束符共16byte] */
	unsigned short usRsPort[2];			/* port of registratin server, value : 1~65535, consider 4 bytes justification, using the first of the array [注册服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个] */
	int iRsAgedTime;					/* valid time of registration server, value (unit:hour) [注册服务器有效时间,数值(单位:小时)] */
	char szAuthorizeServerIp[64];		/* IP of authority server [鉴权服务器IP] */
	unsigned short usAuthorizePort[2];  /* port of authority server, consider 4 bytes justification, using the first of the array [鉴权服务器端口,考虑4字节对齐,目前只用数组第一个] */
	char szAuthorizeUsername[32];		/* account of authority server [鉴权服务器帐号] */
	char szAuthorizePassword[36];		/* passsword of authority server [鉴权服务器密码] */

	char szIpACS[64];					/* ACS (auto registration server) IP [ACS(自动注册服务器) IP] */
	unsigned short usPortACS[2];		/* ACS port, consider 4 bytes justification, using the first of the array [ACS Port,考虑4字节对齐,目前只用数组第一个] */
	char szUsernameACS[32];				/* ACS user name [ACS用户名] */
	char szPasswordACS[36];				/* ACS password [ACS密码] */
	//bool bVideoMonitorEnabled[4];		/* if DVS timer to upload the watch information of front video signal, value: true enable, false disable [DVS是否定期上报前端视频信号监控信息, 数值: true使能, false不使能] */
	int iVideoMonitorInterval;			/* upload timer slice (minute) [上报周期（分钟）] */

	char szCoordinateGPS[64];			/* GPS coordinate [GPS坐标] */
	char szPosition[32];				/* device position [设备位置] */
	char szConnPass[36];				/* device connection passport [设备接入码] */
}RV_INTERVIDEO_BELL_CFG;
//platform of VS300 [VS300平台配置]
typedef struct
{
	UInt32 dwSize;
	BOOL    BEnalbe;		//enable, 4 bytes, 0:disable, 1:enable [使能 4字节 0 不使能 1 使能]
	char    acServerIp[32];	//server ip [服务器ip]
	int	iServerPort;	//listen port of server [服务器侦听端口]
	char    acUserName[32];	//user name [用户名]
	char    acPassWords[32];//password [密码]
	int	iType;			//protocal type, 0:tcp, 1:udp [协议类型 0 tcp 1 udp]
	char    acReserve[80];	//reserved [保留位]
}RV_CONFIG_VS300_NET;
//platform of SHENYAN [神眼平台接入配置]
typedef struct
{ 	
	UInt32 dwSize;
	BOOL Enable;		//enable [是否开启]
	char ServerIp[64];	//IP of SHENYAN Sserver [神眼服务器IP]
	int ServerPort;		//port on SHENYAN server [神眼服务器端口号]
	char PUId[32];		//device ID [设备ID]
	int  usTcpPort;		/*TCP port, value:1~65535 [对外的TCP 端口,数值: 数值 1~65535] */    
	int  usUdpPort;		/*UDP port, value:1~65535 [对外的UDP 端口,数值: 数值 1~65535] */    
	char strUsr[16];
	char strPwd[16];    
	char strVer[16];
	char Reserved[16];
}RV_CONFIG_ZXSHENYAN_NET;
//////////////////////////////////////////////////////////////////////
//	disk configure [磁盘配置]
//////////////////////////////////////////////////////////////////////
typedef struct
{	
	unsigned char ucUse;			//enable [此分区是否有效]	
	unsigned char ucPartion;		//partion index [分区号；]	
	unsigned char ucFSType;			//partion supported file systems [分区支持的文件系统]	
									//0:WFS file system, max support 2 partions, and the partion is restrict to 3 types as bellow [0 WFS文件系统  现有最大支持2分区，且分区又约束如下三种方式]	
									//if WFS2 partion, default is that, the first partion is for snapshot, and the second is for recording [WFS2分区的话，默认第1分区为快照分区，第2分区为录像分区]	
									//if it is only one partion under WFS file system, it is decided by ucPartType [如果是WFS 1分区的话，根据ucPartType决定]	
									//ucPartType==0,record partion; ucPartType==1,snapshot partion [ucPartType==0，录像分区；ucPartType==1快照分区]	
									//now snapshot (store pictures) and the next record, device can only save one type of media [此时快照（存储图片）后者录像，设备只能进行一种媒体的存储]	
									//WFS file system only can be used as percet 2 partion mode [WFS文件系统约束只作百分比2分区模式]	
									//1 FAT32	
									//2 EXT3	
	unsigned char ucPartType;		//this is used by WFS file system pnly, 0:record partion, 1:snapshot partion, standard file system, not need, no limit [WFS文件系统分区专用 0 录像分区  1快照分区；标准文件系统，不需要，无限制]	
	unsigned int uiTotalSpace;		//< total space, it's unit reference to ucSpaceType introduction [< 总容量，其单位参考ucSpaceType说明]	
	unsigned int uiRemainSpace;		//< left space, it's unit reference to ucSpaceType introduction [< 剩余容量，其单位参考ucSpaceType说明]	
	unsigned char ucSpaceType;		//identify disk space unit, convenient to more correct statistic [标识硬盘容量单位，方便比较准确的统计]	
									//the next 4 bits (7 6 5 4) total space unit 0 KB，1MB，2GB，3TB [后4位（7  6 5 4 ） 总大小单位  0 KB，1MB，2GB，3TB]								
									//the first 4 bits (3 2 1 0) left space unit 0 KB，1MB，2GB，3TB [前4位（3 2 1 0） 剩余大小单位  0 KB，1MB，2GB，3TB]
	unsigned char ucReserve[3];
}RV_DISK_PARTION_INFO;
typedef struct
{
	unsigned char ucDiskNo;				//disk No. max 255 [盘符,第几个硬盘 最多255个]
	unsigned char ucCurrentUse;			//if currently using work disk [是否当前使用工作盘]
	unsigned char ucLocalStorage;		//local store or remote store media, 0:local, 1:remote [本地存储还是远程存储介质 0本地 1远程]
	unsigned char ucDiskType;			//disk media type,0:sata disk, 1:U disk, 3:sd card, 4:removable disk, 5:dvd CD [硬盘介质类型 0 sata硬盘 1，U盘，3 sd卡，4，移动硬盘，5，dvd光盘]
	unsigned char ucErrorFlag;			//flag work disk error [工作盘错误标志]
	unsigned char ucPartMethod;			//supported partion mode [支持分区模式]
										//bit0: if support partion 0 not support 1 support [第0位表示是否支持分区 0 不支持 1支持]
										//next seven bits flag supported partion type [后七位 按位标识支持分区方式] 
										//bit1: partion by percent 0 not support 1 support [第1位 按照百分比分区 0 不支持 1支持]
										//bit2: partion by space MB 0 not support 1 support [第2位 按照容量分区 MB  0 不支持 1支持]
										//bit3:	partion by space GB 0 not support 1 support [第3位 按照容量分区 GB  0 不支持 1支持]
										//bit4: partion by space TB 0 not support 1 support [第4位 按照容量分区 TB 0 不支持 1支持]
	unsigned char ucSupportPartionMax;  //supported max partion number of disk [支持硬盘最大分区个数]
	unsigned char ucSupportFileSystem;  //supported file systems, 0:WFS, 1:FAT32, 2:EXT3 [支持的文件系统0 WFS 1 FAT32 2 EXT3]
	unsigned int uiTotalSpace;			//< total space, it's unit reference to ucSpaceType introduction [< 总容量，其单位参考ucSpaceType说明]
	unsigned int uiRemainSpace;			//< left space, it's unit reference to ucSpaceType introduction [< 剩余容量，其单位参考ucSpaceType说明]
	unsigned char ucSpaceType;			//identify disk space unit, convenient to more correct statistic [标识硬盘容量单位，方便比较准确的统计]
										//the next 4 bits (7 6 5 4) total space unit 0 KB，1MB，2GB，3TB [后4位（7  6 5 4 ） 总大小单位  0 KB，1MB，2GB，3TB]
										//the first 4 bits (3 2 1 0) left space unit 0 KB，1MB，2GB，3TB [前4位（3 2 1 0） 剩余大小单位  0 KB，1MB，2GB，3TB]
	unsigned char ucAttr;				//0 read-write(default), 1:read-only, 2:redundancy back-up [0 可读写 （默认），1只读， 2 冗余备份]
	unsigned char ucRes1[2];			//reserved [保留]
	RV_DISK_PARTION_INFO szPartion[4];
	unsigned char ucRes2[64];			//reserved [保留]
}RV_DISK_INFO;
#define RV_MAX_DISK_NUM	16
typedef struct
{
	UInt32 dwSize;
	UInt32 dwCount;
	RV_DISK_INFO stDiskInfo[RV_MAX_DISK_NUM];
}RV_DISKS;
//disk operation [硬盘操作]
typedef struct
{
	unsigned char ucDiskNo;         //disk No. max 255 [盘符,第几个硬盘 最多255个]
	unsigned char ucCtrlType;       //0:read-write(default), 1:read-only, 2:redundancy back-up, 3:format [0 可读写 （默认），1只读， 2 冗余备份 ，3 格式化] 
									//4:sector error detect and restore [4 扇区检测错误恢复]
									//5:repartion, data bellow is valid after disk repartion [5重新分区，重新分区后面数据才有效]
	unsigned char ucRes[2];  

	/////valid data after repartion [重新分区有效数据]----------------------
	unsigned char ucFSType;		//0:WFS file system, max support 2 partions, and the partion is restrict to 3 types as bellow [0 WFS文件系统  现有最大支持2分区，且分区又约束如下三种方式]
								//if WFS2 partion, default is that, the first partion is for snapshot, and the second is for recording [WFS2分区的话，默认第1分区为快照分区，第2分区为录像分区]
								//if it is only one partion under WFS file system, it is decided by ucPartType [如果是WFS 1分区的话，ucPartType标示录像分区和快照（存储图片）]
								//now the next one record, device can only save one type od media [此时后者录像，设备只能进行一种媒体的存储]
								//WFS file system is restrict to seperate 2 partion by percent [WFS文件系统约束只作百分比2分区模式]
								//1 FAT32
								//2 EXT3
	unsigned char ucPartType;	//this is only used by WFS file system, and used when only one partion, 0:record partion, 1:snapshot partion [WFS文件系统分区专用 只有一个分区的时候才使用 0 录像分区  1快照分区]
								//when it is seperate to 2 partions, default is that, the first is snapshot partion, the second is record partion, this value is invalid [WFS  两分区时候，默认第1分区为快照分区，第2分区为录像分区，此值无效]
	unsigned char ucPartNum;	//partion number [分区个数]
	unsigned char ucPartMethod;	//disk partion method, 0:percent, 1:KB, 2:MB, 3:GB, 4:TB [硬盘分区方式， 0 百分比，1 KB 2MB 3 GB 4 TB]
	unsigned int uiPartSpace[4];//every partion used spaces by partion method [按照分区方式，依次分区所使用的容量]
								//if by percent, eg. 50%-50% 2 partions [如果按照百分比，例如 50%-50% 2分区， ]
								//inner fill : 50，50, 0, 0；ucPartCtrlType== 2 ，ucPartNo ==2 [内部填充50，50, 0, 0；ucPartCtrlType== 2 ，ucPartNo ==2]
								//if fill by space MB partion method, eg. 1G disk, 200MB-300MB-100MB-400MB [如果按照容量MB分区方式，例如1G的硬盘，200MB-300MB-100MB-400MB，]
								//fill : 200，300，100，400；ucPartCtrlType== 2 ，ucPartNo ==4 [那么依次填充 200，300，100，400；ucPartCtrlType== 2 ，ucPartNo ==4]
	unsigned int uiRes[6];  
}RV_CTRL_DISK_INFO;
//disk partion , format and error correct operation [硬盘分区进行格式化以及修复操作]
typedef struct
{
	unsigned char ucDiskNo;				//disk No. max 255 [盘符,第几个硬盘 最多255个]
	unsigned char ucPartCtrlType;		//0:format, 1 partion sector detect error correct [0 格式化，1分区扇区检测修复]
	unsigned char ucPartNo;				//ucPartCtrlType==0,1 do format, sector detect restore with the ucPartNo partion [ucPartCtrlType==0、1，对第ucPartNo个分区进行格式化、扇区检测修复；]
	unsigned char ucRes;	
	unsigned int uiRes[7];				//reserved [保留]
}RV_CTRL_DISK_PARTION_INFO;
typedef struct
{
	UInt32 dwSize;
	RV_CTRL_DISK_INFO stDiskInfo;
}RV_CTRL_DISK_OP;
typedef struct
{
	UInt32 dwSize;
	RV_CTRL_DISK_PARTION_INFO stDiskPartionInfo;
}RV_CTRL_DISK_PARTION_OP;
//////////////////////////////////////////////////////////////////////
//	channel configure [通道配置]
//////////////////////////////////////////////////////////////////////
typedef struct
{
	int enable;		//enable [使能]
	int startHour;	//start time : hour [开始时间:小时]
	int	startMinute;//start time : minute [开始时间:分钟]
	int	startSecond;//start time : second [开始时间:秒钟]
	int	endHour;	//end time : hour [结束时间:小时]
	int	endMinute;	//end time : minute [结束时间:分钟]
	int	endSecond;	//end time : second [结束时间:秒钟]
}RV_TIMESECTION;
//////////////////////////////////////////////////////////////////////
//	network configure [网络配置]
//////////////////////////////////////////////////////////////////////
#define RV_NAME_PASSWORD_LEN		64	
#define RV_EMAIL_ADDR_LEN  32
#define RV_N_MIN_TSECT 2
typedef struct
{
	char HostName[RV_NAME_PASSWORD_LEN];	//device name [设备名]	
	int HttpPort;							//HTTP server port [HTTP服务端口]	
	int TCPPort;							//TCP listen port [TCP侦听端口]		
	int SSLPort;							//SSL listen port [SSL侦听端口]	
	int UDPPort;							//UDP listen port [UDP侦听端口]	
	int MaxConn;							//max connection number [最大连接数]	
	unsigned char ucMonMode;				//watch protocal {"TCP","UDP","MCAST",…}  0|1|2 [监视协议 {"TCP","UDP","MCAST",…}  0|1|2]	
	unsigned char ucUseTransPlan;			//if enable network transport plot [是否启用网络传输策略]
	unsigned char ucTransPlan;				//transport plot 2 auto 1 fluency first 0 quality first, default 1 [传输策略 2自动 1流畅性优先 0质量优先，默认1]
	unsigned char ucHighSpeedDownload;		//if enable high speed download [是否启用高速录像下载测率]
	int iRes[3];
}RV_CONFIG_NET_APP;
typedef struct
{
	char strEthName[16];			//different net card name, show by string "eth0", this can not be changed [不同网卡名称，以字符串标示"eth0"; 此不可以改]
	char strMacAddr[32];			//xx.xx.xx.xx.xx.xx (string format) [xx.xx.xx.xx.xx.xx(字符串形式)]
	char HostIP[20];				//host's IP [主机IP]
	char Submask[20];				//sub net mask [子网掩码]
	char Gateway[20];				//gateway IP [网关IP]
	unsigned char  ucTranMedia;		//0:wired net, 1:wireless net [0：有线，1：无线]
	unsigned char  ucDefaultEth;	//if it is default net card, 1:default, 0:not default [是否作为默认的网卡, 1：默认 0：非默认]
	unsigned char  ucValid;			//by bit, bit0 1:valid, 0:invalid [按位表示，第一位：1：有效 0：无效；]
									//bit1 0:DHCP closed, 1:DHCP enable [第二位：0：DHCP关闭 1：DHCP使能；]
									//bit2 0:not support DHCP, 1:support DHCP [第三位：0：不支持DHCP 1：支持DHCP]
	unsigned char  ucReserve;	
	unsigned char  ucRes[16];		//reserved [保留字]
}RV_CONFIG_NET_ETH;
typedef struct
{
	UInt32 dwSize;
	RV_CONFIG_NET_APP stNetApp;
	RV_CONFIG_NET_ETH stNetEth;
}RV_CONFIG_NET_COMM;
//server struct definition [服务器结构定义]
typedef struct
{	
	char ServerName[RV_NAME_PASSWORD_LEN];	//service name, ip domain format or xxx.xxx.xxx.xxx format, max 64 bytes [!服务名,ip域名形式或者是xxx.xxx.xxx.xxx形式，最长64字节]
	int iReserved;							//origin IP address, save this field for extend [!原始为IP地址，为了扩展保留此字段；]	
	int Port;								//port [!端口号]
	char UserName[RV_NAME_PASSWORD_LEN];	//uer name [!用户名]	
	char Password[RV_NAME_PASSWORD_LEN];	//password [!密码]	
	int  Anonymity;							//if anonimity [!是否匿名登录]
}RV_REMOTE_SERVER;
typedef struct
{
	int Enable;								//enale [!是否开启 0 不开启，1开启]	
	int iKey;								//type name, if it is ddns, corresponding ddnskey, can extend server type for using [!类型名称，如果是ddns，对应ddnskey;可以扩展服务类型使用]
	RV_REMOTE_SERVER Server;				//server information [!服务器 信息]
}RV_IPADDR_SERVER;
#define  RV_MAX_EMAIL_TITLE_LEN 64
#define  RV_MAX_EMAIL_RECIEVERS  5
//email configure [EMAIL设置]
typedef struct
{
	//can fill with ip, and can fill with domain [可以填ip,也可以填域名]
	RV_IPADDR_SERVER Server;
	int bUseSSL;		
	char SendAddr[RV_EMAIL_ADDR_LEN];							//sender address [发送地址]		
	char Recievers[RV_MAX_EMAIL_RECIEVERS][RV_EMAIL_ADDR_LEN];	//receiver address [接收人地址]		
	char Title[RV_MAX_EMAIL_TITLE_LEN];							//emial title [邮件主题]
	RV_TIMESECTION Schedule;					//emial valid time [email有效时间]	
	unsigned int uiPicturesChs;					//发email带图片附件通道，按照通道掩码来处理
	unsigned int uiRes[6];
}RV_CONFIG_EMAIL;
typedef struct
{
	UInt32 dwSize;
	RV_CONFIG_EMAIL stEmail;
}RV_EMAIL;
//DNS
typedef struct
{
	char strPrimaryIp[16]; //xxx. xxx. xxx. xxx (string format) [xxx. xxx. xxx. xxx (字符串形式)]
	char strSecondIp[16];
}RV_DNS_IP_LIST;
typedef struct
{
	UInt32 dwSize;
	RV_DNS_IP_LIST stDNSIpList;
}RV_DNS;
//UPNP
typedef struct
{	
	int Enable;		//enable [是否开启]	
	int WebPort;	//web port [web端口]	
	int TCPPort;	//tcp port [tcp端口]	
	int iRervered;
}RV_CONFIG_UPNP;
typedef struct
{
	UInt32 dwSize;
	RV_CONFIG_UPNP stUpnp;
}RV_UPNP;
//PPPOE
typedef struct 
{
	int iEnable;		//0:disable, 1:enable [0 不使能，1 使能]
	char strip[32];
	char strUser[64];
	char strPwd[64];
}RV_PPPOE_IP_SRV;		//remarks : only enable, ip(dial ip), user name, password are valid when dial to get configure [注明：其中，拨号获取设置的时候只有使能，ip（拨号ip），用户名密码有效；]
						//when setting, only enable, user name, password are valid [设置的时候，只有使能，用户名密码有效；]
typedef struct
{
	UInt32 dwSize;
	RV_PPPOE_IP_SRV stPppoe;
}RV_PPPOE;
//DDNS
#define RV_MAX_DDNS_SERVER_NUM 16
typedef struct
{
	UInt32 dwSize;
	int iCount;
	RV_IPADDR_SERVER stDDNSServer[RV_MAX_DDNS_SERVER_NUM];
}RV_MDDNS;

//////////////////////////////////////////////////////////////////////
//	code configure [编码配置]
//////////////////////////////////////////////////////////////////////
typedef enum _ECOMPRESSION_MODE {
	ECOMPRESSION_MODE_DIVX_MPEG4,	///< DIVX MPEG4。
	ECOMPRESSION_MODE_MS_MPEG4,		///< MS MPEG4。
	ECOMPRESSION_MODE_MPEG2,		///< MPEG2。
	ECOMPRESSION_MODE_MPEG1,		///< MPEG1。
	ECOMPRESSION_MODE_H263,			///< H.263
	ECOMPRESSION_MODE_MJPG,			///< MJPG
	ECOMPRESSION_MODE_FCC_MPEG4,	///< FCC MPEG4
	ECOMPRESSION_MODE_H264,			///< H.264
	ECOMPRESSION_MODE_SVAC,			///< SVAC
	ECOMPRESSION_MODE_NR			///< 枚举的压缩模式数目。
}ECOMPRESSION_MODE;

typedef struct
{
	int		iCompression;			/*!< compression mode [压缩模式] 见ECOMPRESSION_MODE*/
	int		iResolution;			/*!< resolve, reference to enum capture_size_t(DVRAPI.H) [分辨率 参照枚举capture_size_t(DVRAPI.H)] */	
	int		iBitRateControl;		/*!< bit-stream control, reference to enum capture_brc_t(DVRAPI.H) [码流控制 参照枚举capture_brc_t(DVRAPI.H)] */	
	int		iQuality;				/*!< picture quality, level 1~6 (corresponding worst,bad,common,good,better,best) [码流的画质 档次1-6（对应的是最差，差，一般，好，很好，最好]*/	
	int		nFPS;					/*!< frame rate (0~30 ), (-n~0) means how many seconds per frame, NTSC and PAL are the same [帧率值（0~30）（-n~0）负数表示多秒一帧，NTSC/PAL不区分] */	
	int		nBitRate;				/*!< 0-4096k */
	int		iGOP;					/*!< descript time slice between two I frame, unit is second, 2-12 [描述两个I帧之间的间隔时间s，2-12] */
}RV_VIDEO_FORMAT;
typedef struct
{
	int		nBitRate;				/*!< bit-stream kbps [码流kbps]*/	
	int		nFrequency;				/*!< sample rate [采样频率]*/	
	//int		nMaxVolume;			/*!< max volume value [最大音量阈值]*/
	unsigned char	ucLAudioVolumn;	//left audio channel volumn [左声道音量]
	unsigned char	ucRAudioVolumn;	//right audio channel volumn [右声道音量]
	unsigned char	ucRes[2];		//reserved [保留]
}RV_AUDIO_FORMAT_T;
//media format [媒体格式]
typedef struct
{
	RV_VIDEO_FORMAT vfFormat;		/*!< video format definition [视频格式定义] */			
	RV_AUDIO_FORMAT_T afFormat;		/*!< audeo format definition [音频格式定义] */
	int	bVideoEnable;				/*!< open video code [开启视频编码] */
	int	bAudioEnable;				/*!< open audio code [开启音频编码] */	
}RV_MEDIA_FORMAT;
//code configure [编码设置]
typedef struct _RV_NET_ENCODE
{
	int iSteamIndex;				/*!<bit-stream format [码流格式] 
										main bit-stream, reference to enum ENCODE_TYPE_BY_RECORD, default to only have one main stream, fill it to 0 [主码流 参考枚举参考ENCODE_TYPE_BY_RECORD ，现有产品默认只有一个主码流，填充为0；]
										assist bit-stream, reference to enum ENCODE_TYPE_BY_SUBSTREAM, max 4 assist bit-stream, max support one assist bit-stream now, fill it to 0 [副码流 参考 ENCODE_TYPE_BY_SUBSTREAM，最多4种子码流，现在产品最多支持一种副码流，填充为0；]
										snapshot bit-stream, reference to enum ENCODE_TYPE_BY_SUBSTREAM, config snapshot from max 4 assist bit-stream [捉图码流 参考 ENCODE_TYPE_BY_SUBSTREAM，最多从4种码流中进行捉图配置]
									*/	
	RV_MEDIA_FORMAT dstFmt;			/*!<bit-stream format [码流格式] */	
}RV_NET_ENCODE;
//
#define RV_N_COLOR_SECTION 2
//video color struct [视频颜色结构]
typedef struct
{
	int	nBrightness;				/*!< brightness 0-100 [亮度	0-100] */
	int	nContrast;					/*!< conrast 0-100 [对比度	0-100] */
	int	nSaturation;				/*!< saturation 0-100 [饱和度	0-100] */
	int	nHue;						/*!< hue 0-100 [色度	0-100] */
	int	mGain;						/*!< gain, 0-100, bit6 means auto gain [增益	0-100 第７位置1表示自动增益]　*/		
	int	mWhitebalance;				/*!< auto white level control, bit7 means open auto control, 0x0,0x1,0x2 means low,middle,high level [自动白电平控制，bit7置位表示开启自动控制.0x0,0x1,0x2分别代表低,中,高等级]*/
}RV_VIDEOCOLOR_PARAM; 
typedef struct
{
	RV_TIMESECTION		TimeSection;		/*!< time slice [时间段] */
	RV_VIDEOCOLOR_PARAM	dstColor;			/*!< color definition [颜色定义] */
	int					iEnable;            /*!< enable, there is no definition in sdk now, default is enable [使能定义 现有sdk暂时没有此部分，默认使能]*/
}RV_VIDEOCOLOR;
typedef struct
{
	RV_VIDEOCOLOR dstVideoColor[RV_N_COLOR_SECTION];
}RV_CONFIG_VIDEOCOLOR;
typedef struct
{
    int iChannel;
	RV_CONFIG_VIDEOCOLOR stVideoColor;
}RV_NET_VIDEOCOLOR;

// 多行OSD叠加配置结构体：ENCODE_CHANNEL_MUTILE_TITL
#define MUTLINT_TITLE_SIZE       320 
typedef struct _MutlineTitle_
{
    int iChannel;
    char strMutlineTitle[MUTLINT_TITLE_SIZE]; 
}MUTILE_TITLE;


//query video area shelter information [查询视频区域遮挡属性信息]
//video object struct [视频物件结构]
typedef struct
{
	unsigned int rgbaFrontground;		/*!< object's front RGB and transparency [物件的前景RGB，和透明度] */	
	unsigned int rgbaBackground;			/*!< object's background RGB and transparency [物件的后景RGB，和透明度]*/	
	RV_VD_RECT	rcRelativePos;			/*!< object's edge distance / total length * 8191 [物件边距与整长的比例*8191] */	
	BOOL	bPreviewBlend;				/*!< overprint in preview [预览叠加] */	
	BOOL	bEncodeBlend;				/*!< overprint in code [编码叠加] */
}RV_VIDEO_WIDGET;
//area shelter [区域遮挡]
#define RV_COVERNUM 8
typedef struct
{
	unsigned int	uiCoverNum;			//how many overprint areas in current channel [当前该通道有几个叠加的区域]
	RV_VIDEO_WIDGET	dstCovers[RV_COVERNUM];
}RV_NET_VIDEO_COVER;
//
typedef struct  
{
	unsigned int  cSize;		//字体大小，1表示标准倍数，2表示2倍大小  该值取值范围在1到ucZoomAbility之间
	unsigned int  index;
	unsigned int  res[2];		//保留
}RV_OSD_ZOOM_PARAM;

typedef struct  
{
	UInt32	dwSize;
	RV_OSD_ZOOM_PARAM	stOSDZoom;
}RV_OSD_ZOOM_CFG;

#define RV_CHANNEL_NAME_SIZE 32
typedef struct
{
	UInt32 dwSize;	
	char cName[RV_MAX_CHANNUM][RV_CHANNEL_NAME_SIZE];
	RV_NET_ENCODE stEncodeMain[RV_MAX_CHANNUM];
	RV_NET_ENCODE stEncodeAssist[RV_MAX_CHANNUM];
	RV_CONFIG_VIDEOCOLOR stColorCfg[RV_MAX_CHANNUM];
	RV_VIDEO_WIDGET stTimeOSD[RV_MAX_CHANNUM];
	RV_VIDEO_WIDGET stTitleOSD[RV_MAX_CHANNUM];
	RV_NET_VIDEO_COVER stCovor[RV_MAX_CHANNUM];
	RV_NET_GENERAL stGeneral;
	RV_OSD_ZOOM_PARAM stOSDZoom;
}RV_CODE_CFG;

typedef struct
{
	unsigned short 	iChannel;		//channel, start with 0 [通道 从0开始]
	unsigned short	iIndex;			//preset or locus index , start with 1 [预置点或者轨迹下标号 从1开始]
}RV_PTZ_CHANNEL;

#define NAME_LEN			32		
#define PTZ_PRESETNUM		256
#define PTZ_CHANNELS		8

typedef struct 
{
	unsigned char 	ucChannel;					//channel [通道]
	unsigned char 	ucPresetID;					//preset No. [预置点号]
	unsigned char	iSpeed;						//preset speed speed 1~15 level [预置点速度 速度1~15等级]
	unsigned char	iDWellTime;					//preset delay time 1~255 [预置点停留时间 1~255s]
	unsigned char	szPresetName[NAME_LEN];		//preset name [预置点名称]
}RV_PRESET_INFO;

typedef struct
{
	unsigned char 	ucChannel;					//channel [通道]
	unsigned char	ucTourIndex;				//tour No. [巡航号]
	unsigned char	ucPresetCnt;				//number of presets in one tour [一个巡航组中的预置点数 0~128]
	unsigned char	uRes;						//reserved [保留]
	unsigned char	uiPresetNum[64];			//preset No. in tour [巡航组中的预置点号]
}RV_TOUR_INFO;

typedef struct  
{
	UInt32 dwSize;
	UInt32 dwCount;
	RV_PRESET_INFO	struPreset[PTZ_PRESETNUM];
}RV_PTZ_PRESET_SCHEDULE;

typedef struct  
{
	UInt32 dwsize;
	UInt32 dwCount;
	RV_TOUR_INFO	struTour[PTZ_CHANNELS];
}RV_PTZ_TOUR_SCHEDULE;

typedef struct  
{
	RV_PTZ_CHANNEL struChannel;
	RV_PRESET_INFO	struPreset;
}RV_PTZ_TOUR_PRESET;
//NTP struct [NTP结构体]
typedef struct
{	
	RV_IPADDR_SERVER szNtpServer;	//server [服务器]	
	int UpdatePeriod;				//update time slice [更新周期]	
	int TimeZone;					//time zone [时区]
}RV_CONFIG_NTP;
typedef struct
{
	UInt32 dwSize;
	RV_CONFIG_NTP stNtp;
}RV_NTP;

//////////////////////////////////////////////////////////////////////////
//	struct of output mode [输出模式结构体]
typedef struct
{
	unsigned char ucOSDShow;
	//0位 是否显示时间标题显示使能(保留和原来功能一样）
	//1位 通道标题显示使能 (保留和原来功能一样）
	//2位 报警状态显示使能（新增加）
	//3位 录像状态显示使能（新增加）
	//4位 是否显示数字通道时间标题显示使能（新增加，有数字通道才显示否则不显示）
	//5位 数字通道通道标题显示使能（新增加，有数字通道才显示否则不显示）      
	//6位 数字通道报警状态显示使能（新增加，有数字通道才显示否则不显示）     
    //7位 数字通道录像状态显示使能（新增加，有数字通道才显示否则不显示）

	unsigned char ucRes[15];//reserved [保留]
}RV_OUT_MODE_OSD_CFG;
typedef struct
{
	UInt32 dwSize;
	RV_OUT_MODE_OSD_CFG stOSD;
}RV_OUT_MODE_CFG;

//////////////////////////////////////////////////////////////////////////
//	ftp struct [ftp结构体]
typedef struct
{
	RV_IPADDR_SERVER	stServer;				//ftp server [ftp服务器]
	char            cDirName[RV_FTP_MAX_PATH];  //FTP folder path, 240[FTP目录路径 240]
	int             iReserved;                   
	int             iFileLen;                   //file length, unit is M [文件长度 M为单位]
	int             iInterval;                  //time slice between files, unit is second [相邻文件时间间隔    秒为单位]
	char            cRev[128];
}RV_CONFIG_FTP_SERVER_SET;
typedef struct
{
	RV_TSECT				stSect[RV_N_WEEKS][RV_TIME_SECTION];
}RV_FTP_APP_TIME_SET;
typedef struct
{
	RV_CONFIG_FTP_SERVER_SET	stFtpServerSet;	
	RV_FTP_APP_TIME_SET			stFtpAppTimeSet[RV_MAX_CHANNUM];
}RV_FTP_SERVER;
typedef struct
{
	UInt32 dwSize;
	RV_FTP_SERVER stFtpRecord;	//record [录像]
	RV_FTP_SERVER stFtpPicture;	//picture [图片]
}RV_FTP;

/////////////////////////////////////////////////////////////////////////
//	rtsp struct [rtsp结构体]
typedef struct
{
	unsigned short    usEnable;       //enable [使能] 
	unsigned short    usListernPort;  //RTSP listen port [RTSP侦听端口]
	unsigned short    usUdpStartPort; //UDP start port [UDP起始端口]
	unsigned short    usUdpPortNum;   //UDP port number [UDP端口数量]
	IPADDR			  stMulticastIp;	//组播地址，用掉4字节保留位
	unsigned short    usPort;			//组播端口，用掉2字节保留位
	unsigned short    usReserve[33];  //reserved [保留]
}RV_CONFIG_RTSP_SET;
typedef struct
{
	UInt32 dwSize;
	RV_CONFIG_RTSP_SET stRTSP;
}RV_RTSP;

//////////////////////////////////////////////////////////////////////
//	alarm struct of intelligent red [能红色报警结构]
//////////////////////////////////////////////////////////////////////
//area shelter [区域遮挡]
#define RV_REDREGIONNUM 8
typedef struct
{
	int lX;
	int lY;
}RV_POINT;
typedef struct
{
	int				iRectNum;							//how many areas in current channel [当前该通道有几个区域]
	RV_POINT		szPointArray[RV_REDREGIONNUM][4];
}RV_REDON_RECT;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
	RV_REDON_RECT			stRedonRect;
} RV_INTERED_ALARM; 
typedef struct
{
	UInt32 dwSize;		
	RV_INTERED_ALARM		struInteRedAlarm[RV_MAX_CHANNUM];
}RV_INTERED_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//record control [录像控制]
typedef struct
{
	unsigned char ucChannelCount;	//channel number [通道数目]
	unsigned char ucRes[3];
	unsigned char ucState[128];		//0~127 flag channel 1~128 (0:not record, 1:manual record, 2:auto record) [第0个到第127个依次为第1到第128通道（0: 为不录像;1: 手动录像;2: 为自动录像）]
}RV_RECCTL; 
typedef struct
{
	UInt32 dwSize;  
	RV_RECCTL struRecCtl;
}RV_RECCTL_CFG;

/* configure struct of serial port, more than 16 channnels [串口配置结构体 超过16通道] */
typedef struct
{
	UInt32			dwSize;
	UInt32			dwDecProListNum;										//number of protocal [协议个数]
	char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN];	//protocal list [协议名列表]
	RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM_EX];						//current attributes of every decoder [各解码器当前属性]

	UInt32			dw232FuncNameNum;										//number of 232 function [232功能个数]
	char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];			//function name list [功能名列表]
	RV_RS232_CFG	st232[RV_MAX_232_NUM];									//current attrributes of every 232 serial port [各232串口当前属性]
} RVDEV_COMM_CFG_EX;

typedef struct  
{
	int iChannel;
	char strChannelName[MAX_HHCHANNELNAME_LEN]; 
}RV_CHANNEL_NAME;

typedef struct  
{
	UInt32 dwSize;
	RV_CHANNEL_NAME stChannelName[RV_MAX_DECODER_NUM_EX];		
}RV_CHANNELNAME_CFG;

//////////////////////////////////////////////////////////////////////////
//audio config [音频配置]
typedef struct
{
	unsigned int uiTalkAudioSourceType; //audio source method, 0:liner input, 1:mic [声音源方式，0为线性输入，1为mic]
	unsigned int uiOutSilence;			//mute, 0:not mute, 1-mute [静音 0--非静音 1--静音]
	unsigned int uiOutLAudioVolumn;		//left audio channel volume [左声道音量]
	unsigned int uiOutRAudioVolumn;		//right audio channel volume, left and right channel' value are the same for single audio channel device [右声道音量，单声道的设备左右值一样]
	unsigned int uiLongtimeBeepEnable;    ///蜂鸣器常鸣 0 响一次 1 周期常鸣 
	unsigned int uiReserverd[31];//保留
}RV_DEV_AUDIO;
typedef struct  
{
	UInt32			dwSize;
	RV_DEV_AUDIO	stDevAudio;		
}RV_DEV_AUDIO_CFG;

//////////////////////////////////////////////////////////////////////////
// tour confgure for digital channel [数字通道轮训配置]
typedef struct
{
    int     BEnable;					// 使能开关
    char    cChName[32];				// 远程配置名称
    char    cDeviceIP[48];				// 待连接设备的ip地址
    int     iDevicePort;				// 待连接设备的端口号
	char	cDeviceUserName[32];	    // user name [用户名]
	char	cDevicePassword[32];	    // password [密码]    
    int     iDevType;					// 设备类型，按枚举表示，即协议类型,0表示tcp直连，3 rtsp+udp 4 vs300
    int     iRemoteChannelNo;			// 远程通道号,从0开始算起  
    int     iStreamType;				// 要连接的码流类G停?0:主码流， 1:辅码流
    int     iRemotePtzPreset;			// 远程预置点
    int     iRemotePtzPresetEnable;		// 是否一连接上就设置远程预置点 
    int     iConType;					// 用掉一个保留位，1tcp 2udp
    char	ucUrl[256];					// 增加设备的URL设置
    int     reserverd[32];				// 保留字节
}RV_REMOTE_CH_CFG;
typedef struct
{
	BOOL			BEnable;			//enable [使能开关]
	Int32			iDeviceChannelType; //channel type, 0:digital channel, 1:analog channel, default is digital channel, can't switch now [通道类型，0表示数字通道，1表示模拟通道，默认为数字通道,暂时不可以切换]
	Int32			iMode;				//0:single connection, 1:multi connection [0 单连接 1 多连接]
	unsigned int   uiTourTime;			//multi connection tour time [多连接轮巡时间]
	unsigned int   uiNotTourCfgIndex;	//channel configure on single connection, position in the tour list [单连接时的采用的通道配置,在轮巡列表中的位置]
	Int32			iDecodePolicy;		//decode plot (-2:most real-time, -1:real-time, 0:default, 1:fluency, 2:most fluency) mayby extend to self definition [解码策略     (-2, 最实时 -1 实时 0 默认情况 1 流畅 2,    最流畅 ) 以后可能扩展到自定义具体的延时时间]
	Int32			iAVEnable;			//0:only decode video, 1:only decode audio, 2:decode audio and video [0,只解视频 1，只解音频 ，2 解音视频 ]
	Int32			BAutoNet;			// 自动组网功能
	Int32			BPTZLocal;			// 用掉4个字节，表示该通道数字通道 云台控制接NVR还是发到IPC前端 
	Int32			iReserverd[3];		// 保留字节
}RV_LOCAL_CH_CFG;
typedef struct
{
	RV_LOCAL_CH_CFG		stLocalChCfg;			//channel configure [通道配置]
	UInt32				dwRemoteChanCount;		//remote channel number [远程通道数目]
	RV_REMOTE_CH_CFG	stRemoteChanCfg[32];	//remote channel config [远程通道配置]
}RV_LOCAL_CH;
typedef struct
{
	UInt32 dwSize;
	RV_LOCAL_CH stLocalChan[32];
}RV_DIGI_CH_TOUR_CFG;

//////////////////////////////////////////////////////////////////////////
// key-board control configure [控制键盘配置]
typedef struct 
{
	unsigned char Com_Version[8];	/*!< version number [版本号] */
	unsigned char Function;			/*!< serial port function, reference to enum KBDFunc [串口功能 参照枚举KBDFunc]*/
	unsigned char DataBits;			/*!< data bit, values are 5,6,7,8 [数据位 取值为5,6,7,8] */
	unsigned char StopBits;			/*!< stop bit, reference to enum comm_stopbits_t(DVRAPI.H) [停止位 参照comm_stopbits_t(DVRAPI.H)] */
	unsigned char Parity;			/*!< verify bit, reference to enum comm_parity_t(DVRAPI.H) [校验位 参照comm_parity_t(DVRAPI.H)] */
	unsigned int  BaudBase;			/*!< baudrate {300,600,1200,2400,4800,9600,19200,38400,57600,115200} [波特率 {300,600,1200,2400,4800,9600,19200,38400,57600,115200}]　*/
}RV_KBD;
typedef struct
{
	UInt32 dwSize;
	RV_KBD stKBD;
}RV_KBD_CFG;
//////////////////////////////////////////////////////////////////////////
// configure of matrix (XINGHUO Corp.) [矩阵(星火)配置]
typedef struct
{
	unsigned int uiMap[16];//channel of visiondigi device corresponding channel of matrix input, 0xffffffff means not use matrix input of XINGHUO, eg. uiMap[0] = 100, means channel 1 use the channel 101 of XINGHUO matrix [威乾设备的通道对应的矩阵输入的通道号，0xffffffff表示不使用星火的矩阵输入，比如uiMap[0] = 100，表示第1通道使用星火的第101路输入]
	unsigned int uiRes[20];
}RV_MATRIX_XINGHUO;

typedef struct
{
	UInt32				dwSize;
	RV_MATRIX_XINGHUO	stMatrixXingHuo;
}RV_MATRIX_CFG;

typedef struct  
{
	int iMatrixInput;
	int iChannel;//通道号
	int iVideoEnable;
}RV_MATRIX_INPUT;

typedef struct  
{
	UInt32			dwSize;
	RV_MATRIX_INPUT	stMatrixInput[16];
}RV_MATRIX_CFG_EX;

//added by zhubo,CID-PID对应
typedef struct
{

int Cid0;//请求通道的老的CID，没有时置-1
int Pid0;//请求通道的老的PID，没有时置-1
int iRes1[2];

int Cid1;//请求通道的新的CID
int Pid1;//请求通道的新的PID，请求时置-1
int iRes2[2];
}RV_MATRIX_PIDCID;

//广东红日设备用

//房间参数
typedef struct 
{
	int  iSupportNum;			//支持的楼层数目，读取时有效，配置无效
	int  iNum;					//配置的楼层数目
	char acFloorName[32][12];	//最多按照32层保留
} RV_KOTI_FLOOR;

typedef struct 
{
	int  iSupportNum;			//支持的最大房间数目，读取时有效，配置无效
	int  iNum;					//配置的房间数目
	char acRoomName[32][12];	//最多按照32个房间保留
} KOTI_ROOM;

typedef struct 
{
	char acCam_IP[20];		//摄像头IP
	char cCam_ID;			//摄像头ID
	char cCam_Port;			//视频端口，我们设备即通道号
	char acRes[2];			//保留
	char acFloor[12];		//楼层
	char acRoom[12];		//房间
	//char acIPCamName[64];//摄像头名字，这里不提供了，显示时自己合成
} KOTI_IP_CAM;

// 摄像头参数 
typedef struct 
{
	int  iSupportNum;		//支持的最大数目，读取时有效，配置无效
	int  iNum;				//摄像头数目
	KOTI_IP_CAM stIPCam[32];//这里最多先按照32路设备实现
} KOTI_IP_CAM_CFG;

typedef struct 
{
	char acFloorName[12];	//楼层
	char acRoomName[12];	//房间
	//char acName[20]; //名字自己拼起来
} KOTI_APARTMENT;

// 防区位置参数 
typedef struct _KOTI_APARTMENT_CFG
{
	int  iSupportNum;		//支持的最大防区数目，读取时有效，配置无效
	int  iNum;				//配置的防区数目
	KOTI_APARTMENT  stApartment[32];//最多按照32个防区保留
} KOTI_APARTMENT_CFG;

typedef struct _KOTI_ALARM_AREA
{
	char acName[20];	//防区名字
	char acAltp[20];	//探头类型
	char acAlppt[20];	//性质
	char acCamIP[20];	//摄像头iP
	int  iCamID1;		//摄像头ID
} KOTI_ALARM_AREA;
/*
typedef struct _KOTI_ALARM_AREA_CONF
{
	int  iSupportNum;			//支持的最大数目，读取时有效，配置无效
	int  iNum;					//摄像头数目
	char acSupportAltp [96];	//支持的探头类型，目前为："红外探头|门磁|窗磁|烟感探头|煤气探头|紧急按钮|红外对射|红外光栅",不同类型用'|'区分
	char acSupportAlppt[96];	//支持的防区性质，目前为："立即|延时|停用|24小时|联动立即|联动延时",不同类型用'|'区分
	
	_KOTI_ALARM_AREA stAlarmArea[32];//这里最多先按照32个防区实现
} KOTI_ALARM_AREA_CONF;

typedef struct _KOTI_MOBILE_NUM
{
	char acMobileNum[20];	//电话号码
	char cVoice;			//电话语音0 不使能1 使能
	char cSMS;				//短信 0 不使能1 使能
	char cMMS;				//彩信 0 不使能1 使能
} KOTI_MOBILE_NUM;

// 报警电话参数 
typedef struct _KOTI_MOBILE_NUM_CONF
{
	int  iSupportNum;					//支持的最大数目，读取时有效，配置无效
	int  iNum;							//配置数目
	
	_KOTI_MOBILE_NUM stMobileNum[32];	//这里最多先按照32个电话实现
} KOTI_MOBILE_NUM_CONF;
*/
typedef struct _KOTI_SYSINFO
{
	char acProductType[16];			//产品型号，前端上报字符串
	char acMac[6];					//有线MAC
	char acWireMac[6];				//无线MAC
	char acUID[20];					//16位UID,后几位置0
	char acVer[20];					//版本号，小于20位字符串
	char acBuildTime[20];			//编译时间，小于20位字符串
} KOTI_SYSINFO;

typedef struct _KOTI_ALARM_TIME
{
	char acServerip[16];				//服务器IP
	unsigned char ucDelayZoneTime;		//延时防区时间1-255s 
	unsigned char ucEnalbeDelaytime;	//布防延时时间1-255s 
	unsigned short usAlarmTime;		//警铃鸣响时间1-30000s*/
	unsigned char ucRingTime;		//振铃次数,1-10次
	unsigned char ucKeepDay;		//续传保持天数,1-30次
	unsigned char ucKeepCmd;		//续传最大次数,1-100次
	char          cMatrix;			//矩阵的类型，-1 空，1，AVS1 其它未知
	unsigned char ucLineCheck;		//电话线检测，0，不使能，1使能
	unsigned char ucCheckPower;		//备用电源检测报警，0，不使能，1使能
	unsigned char ucMMS;			//布撤防短信通知，0，不使能，1使能
	char acPhone1[16];				//接警中心电话1
	char acPhone2[16];				//接警中心电话2
	char acPhone3[16];				//接警中心电话3
	char acPhone4[16];				//接警中心电话4
	char acRes[32];					//保留
} KOTI_ALARM_TIME;

typedef struct _KOTI_PASSWORD
{
	char acPWD1[8];				//两个密码一致才保存成功，密码最长8位
	char acPWD2[8];
}KOTI_PASSWORD;

typedef struct _KOTI_RTSP_CONG
{
	//rtsp服务器配置
	int iRtspServerEnable;	//是否启用RTSP服务器
	int iRtspListenPort;	//RTSP服务器端口
	
	//rtsp客户端配置
	int iRtspClientEnable;		//是否启用RTSP服务器 0,不使能 1 使能
	int iRtspServerPort;		//远程RTSP服务器端口
	char acRtspServerIP[16];	//远程RTSP服务器IP
}KOTI_RTSP_CONG;

typedef struct _RV_BELL_NetComCfg
{
    int bVSEnable;					//使能开关 0不使能，1使能
    char szVSIP[64];				//初始化服务器IP地址
    unsigned short usVSPort;		//初始化服务器端口
    char szworkOrderNo[64];			//工单号
    char szModel[32];				//设备型号
    char szRes[64];					//保留字
}RV_BELL_NETCOM_CFG;

typedef struct _RV_VIDEOIN_CAPS{
	unsigned int uiCamAbility;  //按位处理（总32项目） 
	//第0位 支持HorReverse水平翻转，1为支持该项功能，0为不支持该项功能
	//第1位 支持竖直翻转VerReverse，1为支持该项功能，0为不支持该项功能
	//第2位 支持曝光模式设置Exposure，1为支持该项功能，0为不支持该项功能
	//第3位 支持感光度设置AESensitivity，1为支持该项功能，0为不支持该项功能
	//第4位 支持背光补偿Backlight，1为支持该项功能，0为不支持该项功能
	//第5位 支持白平衡模式WhiteBalance，1为支持该功能，0为不支持该项功能。
	//第6位 支持阴影修正ShadeCorr，1为支持该功能，0为不支持该项功能。
	//第7位 支持坏点修正BadCorr，1为支持该功能，0为不支持该项功能。
	//第8位 支持防闪烁Anti-Flicker，1为支持该功能，0为不支持该项功能
	//第9位 支持色调调节，1为支持该功能，0为不支持该功能
	//第10位支持YUV输出范围控制，1为支持该功能，0为不支持该功能
	//第11位支持IR-CUR控制，1为支持该功能，0为不支持该功能
	//第12位支持去噪控制，1为支持该功能，0为不支持该功能
	//第13位支持黑白/彩色/自动转换，1为支持该功能，0为不支持该功能
	//第14位支持光敏电阻检查
	//第15位 DRC 宽动态 
	//第16位多帧采集
	//第17位WDR功能
	//第18位背光补偿
    //第19位开关标清回环输出功能
	//第20位帧累积, 参考EnFRAME_ACCUMULATE_MODE
	//第21位超宽动态, 参考EnULTRA_DYNAMIC_RANGE_MODE
	//第22位图像冻结, 参考EnFROZEN_IMAGE_MODE
	//第23位最短对焦距离, 参考EnMIN_FOCUS_DISTANCE
	//第24位GAMMA校正模式: 参考EnGAMMA_ADJUST_MODE
    //第25位强光抑制

	unsigned int uiExposure;//爆光模式不支持能力级，1~3分别表示，自动曝光，手动曝光，交通模式
	unsigned int uiSenSpan; //感光度范围最大值 如值255，则标识范围为0~255
	unsigned int uiBLightSpan;//背光补偿支持上限Backlight,如值15，则范围0~15
	unsigned int uiShutterL;//手动曝光 若值为6000则支持最小曝光时间为1/6000秒
	unsigned int uiShutterH; //手动曝光，若值为50则支持最小曝光时间为1/50秒
	unsigned int uiAntiFlicker;	//如果支持防闪烁支持模式，此项有效，按位处理
	//第0位 是否支持50Hz indoor模式
    //第1位 是否支持50Hz outdoor模式
    //第2位 是否支持50Hz auto模式
    //第3位 是否支持60Hz indoor模式
    //第4位 是否支持60Hz outdoor模式
	//第5位 是否支持60Hz auto模式
	//第6位 是否支持50Hz Theater模式
	//第7位 是否支持50Hz Fast模式
	//第8位 是否支持60Hz Theater模式
    //第9位 是否支持60Hz Fast模式
	unsigned int uiWhiteBlance; //如果支持白平衡模式，此项有效，按位表示白平衡支持的模式
    //每一位对应WHITE_BALANCE_MODE枚举中的相应位，比如0xc0表示支持色温4650k和色温6500k两种模式
	
	unsigned int uiRes2[2];//保留
	
}RV_VIDEOIN_CAPS;

enum COLOR_TEMP_MODE
{
	COLD_COLOR_TEMP,  //冷色调
	NEUTRUAL_COLOR_TEMP, //中性色调
	WARM_COLOR_TEMP,  //暖色调
};

//若支持IR-CUT，其取值为如下枚举
enum IR_CUT_MODE
{
	IR_CUT_AUTO,  //IR-CUT自动
	IR_CUT_OPEN,  //IR-CUT开
	IR_CUT_CLOSE,  //IR-CUT关
};

//若支持YUV输出范围控制，其取值为如下枚举
enum YUV_RANGE_MODE
{
	YUV_RANGE_0_255, //采集从0到255
	YUV_RANGE_16_235, //采集从16到235
};

typedef struct _RV_CONFIG_CAMERA_
{
	unsigned char HorReverse; //支持水平翻转时取值范围为枚举IMAGE_MODE_MIRROE中的值
	unsigned char VerReverse; //支持竖直翻转时取值范围为枚举IMAGE_MODE_MIRROE中的值
	unsigned char ExposureType; //支持曝光模式时取值范围为枚举EXPOSURE_MODE中的值
	unsigned char AESensitivity; //支持感光度设置时取值范围为0到ABILITY_CAMERA_T.uiSenSpan
	unsigned char Backlight; //支持背光补偿时取值范围为0到ABILITY_CAMERA_T.uiBLightSpan
	unsigned char WhiteBalanceMode; //支持白平衡时取值范围为枚举WHITE_BALANCE_MODE中的值
	unsigned char ShadeCorr; //暂不支持，取值范围未知
	unsigned char BadCorr;  //暂不支持，取值范围未知
	unsigned int shutter;  //曝光模式设为手动时取值范围为uiShutterL到uiShutterH之间
	unsigned char AntiFlicker; //支持防闪烁时，取值范围为能力集ABILITY_CAMERA_T.uiAntiFlicker中按位表示的值
	unsigned char ColorTemp; //支持色调调节时，取值范围为枚举COLOR_TEMP_MODE 中的值
	unsigned char YUVCut;	//支持yuv输出范围控制时，取值范围为枚举YUV_RANGE_MODE 中的值
	unsigned char IRCut;	//支持IR-CUT时，取值范围为枚举IR_CUT_MODE中的值
	unsigned char PAA;		//支持去噪功能时，取值范围为枚举PAA_MODE中的值
	unsigned char Color2WhiteBlack; //支持黑白/彩色/自动转换时，取值范围为枚举COLOR_2_WHITEBLACK_MODE中的值
	unsigned char SensorType;		//光敏电阻 高电平有效低电平有效 1 高电平 0低电平  
	unsigned char WDRenbale;            //支持WDR功能时，值为枚举WDR_SET_ENABLE中的值
    unsigned char BackLightCompensate;  //支持背光补偿时，取值范围为枚举BACKLIGHT_COMPENSATION中的值
    unsigned char D1_loopback_output;   //支持开关标清回环输出功能        
    unsigned char LightInhibition;      //强光抑制
    unsigned char res1;
}RV_CONFIG_CAMERA;

enum RV_IMAGE_MODE_MIRROE
{
	MIRROE_OFF,
	MIRROE_ON,
};

enum RV_EXPOSURE_MODE
{
	EXPOSURE_AUTO = 1,  //自动曝光
	EXPOSURE_MANUAL = 2, //手动曝光
};

enum RV_WHITE_BALANCE_MODE
{
	WHITE_BALANCE_OFF, //关闭white balance
	WHITE_BALANCE_AUTO,  //自动white balance
	WHITE_BALANCE_DAYTIME, //室外白天
	WHITE_BALANCE_EVENING, //室外黄昏
	WHITE_BALANCE_CLOUDY, //室外多云
	WHITE_BALANCE_OFFICE, //室内办公室
	WHITE_BALANCE_FLUORESCENT,//荧光灯
	WHITE_BALANCE_INCANDESCENT,// 白炽灯
	WHITE_BALANCE_HAND,  //手动白平衡
	WHITE_BALANCE_NR,
};

typedef struct _CONFIG_WHITEBALANCE_  //手动设置白平衡是的RGB
{
	unsigned char WhiteBalanceMode; // WHITE_BALANCE_MODE支持白平衡时取值范围为能力
	unsigned char wbr; //自动白平衡R分量0-255
	unsigned char wbg; //自动白平衡G分量0-255
	unsigned char wbb; //自动白平衡B分量0-255
	unsigned char res[4];
}CONFIG_WHITEBALANCE;
typedef struct _RV_ABILITY_WATERMARK
{
    //!按位表示 标识每个通道的能力
    unsigned int uiChMask;
    unsigned int uiRes[3];/*保留字，便以后扩展*/
    unsigned char ucMaxCounts[16];/*!<每个最大叠加张数*/
    unsigned char ucRes[16];/*!<保留字，便以后扩展*/ 
}RV_ABILITY_WATERMARK_T;
//////////////////////////////////////////////////////////////////////////
//      录像相关能力结构体
typedef struct _RECORD_ABILITY
{
	unsigned int dwFlag;				//第0位表示支持新的“录像控制”协议，支持32通道以上的录像控制网络协议
	unsigned char ucSupportCardRecord;	//支持卡号录像，0不支持，1支持
	unsigned char ucRes[15];
}RECORD_ABILITY;

typedef  struct _RV_NEW_NET_OPR_CAPS     
{
	unsigned int uiNetOprAbilty;//按位来标识
	//第 0位 是否支持录像和图片查询网络新操作协议 1 支持 0 不支持
	//第1位 是否支持查询日志网络新操作协议 1支持，0不支持
	
	unsigned int ucRes[3] ;//保留
}RV_NEW_NET_OPR_CAPS;

typedef struct _RV_NET_QUERY_SYSYTEM_LOG{
	unsigned char ucQueryType;	//查询方式
	//0 使用原有方式查询，1后续考虑新的方式吧，暂时先不实现
	
	unsigned char ucLogType;	//日志类型
	//使用原有方式查询
	//0 全部1 系统操作2 配置操作3 数据管理
	//4 报警事件5 录像操作6 用户管理7 日志清楚8 文件操作
	
	unsigned char ucRes[2];
	RV_SYSTEM_TIME stStartTime;
	RV_SYSTEM_TIME stEndTime;
	unsigned char ucRes1[16];
}RV_NET_QUERY_SYSYTEM_LOG;

typedef struct _RV_NetLogInfo{
	unsigned short ucType;          //日志类型
	unsigned char ucFlag;			//标记, 0x00 正常，0x01 扩展，0x02 数据
	unsigned char ucData;			//数据
	RV_SYSTEM_TIME stTime;			//日志时间
	unsigned char ucContext[8];		//内容
	unsigned char ucRes1[16];
}RV_NET_LOG_INFO;

typedef struct _RV_NET_OPR_SYSYTEM_LOG
{
	unsigned char ucOprType;
	//0 日志（一次性）清除 
	//1 日志规则查询		  
	//2 日志规则设置			

	unsigned char ucFullPolicy; //日志满覆盖还是停止 1满覆盖 0满停止
	unsigned char ucRes[2];
	unsigned int uiIfRegLog[8];	//是否记录log,类型与查询时对应
	unsigned int uiRes[3];
}RV_NET_OPR_SYSYTEM_LOG;

typedef struct _RV_NetFileInfo
{	
	unsigned char ucFileType;	// 0 录像  1 图片
	unsigned char ucSubType;	// 子类型
	// 0 全部									 
	// 1 外部报警								   
	// 2 动检（包括视频遮挡视频丢失动态检测）
	// 3 所有报警（包括1，2类型外还包括异常报警，硬盘满等）
	// 4 手动录像
	// 5 定时录像（普通录像）
	// 6 卡号录像
	
	unsigned char ucChannel;	//录像通道 					  
	unsigned char ucRes;				  				  				  
	RV_SYSTEM_TIME stStartTime;			  
	RV_SYSTEM_TIME stEndTime;			  		  		  
	unsigned char ucFileName[80];	// 文件名格式:	  
	//通道号_开始时间(yyyy-MM-dd-HH-mm-ss)_结束时间(yyyy-MM-dd-HH-mm-ss)_盘号_分区号_簇号_文件序号_文件类型(00录像 01图片)_子类型_文件长度	  
	
	unsigned char ucRes1[16];					  
}RV_NET_FILEINFO;

#define  N_ATM_FRAME 6
#define  N_ATM_NODE  4
typedef struct tagCONFIG_ATM_POS
{
	int  iStartPosition;                 
	int iLength;                          
	char szTitle[32];                   
} CONFIG_ATM_POS;

typedef struct tagCONFIG_ATM
{
	IPADDR SourceIp;                 /*源IP*/
	int SourcePort;                            
	IPADDR DesIp;                    /*目的ip*/
	int DesPort;                  
	unsigned int  dwRecord;                          /*!< 录象掩码最多32通道 */  
	CONFIG_ATM_POS     stCfgPos[N_ATM_FRAME];
	char Reserved[32];
} CONFIG_ATM;

typedef struct tagCONFIG_ATM_FIELD
{
	int Displaylayer;       
	CONFIG_ATM_POS     stCfgPos[N_ATM_NODE];                 
	char Reserved[32];
} CONFIG_ATM_FIELD;

//卡号录像配置项--RV_DEV_CONIFG_CARD_RECORD--
typedef struct _SCardRecordCfg
{
	CONFIG_ATM atmCfg;
	CONFIG_ATM_FIELD atmFiled[6];
}SCardRecordCfg;

//////////////////////////////////////////////////////////////////////////
//华雁项目网络协议

//串口配置，对应该配置时的通道号为1(配置函数的通道参数)
typedef struct tag_COMATTR
{
	int    nBaudBase;	//实际波特率   
	int    nDataBits;	//数据位 取值为4,5,6,7,8 
	int    iStopBits;	//停止位 参照comm_stopbits_t
	int    iParity;		//校验位 参照comm_parity_t
	int  iControl;		//流量控制none, Xon/Xoff, 硬件>
} CONFIG_COMATTR;

//扩展串口配置，对应该配置时的通道号为2(配置函数的通道参数)
typedef struct tag_ExtCOMATTR
{
	int iComID;	//串口ID
	int iMode;	//0  RS232, 1 RS485 主2 RS485从
	int iDeviceNo;  //从机地址
	int iSendLen;
	int iRevLen;
	CONFIG_COMATTR ExtComAttr;
} CONFIG_ExtCOMATTR;

//环境设备类型枚举
typedef enum tagEnuPgDevType
{
	PG_DEVTYPE_IPC=0,    //RPU设备本身
	PG_DEVTYPE_VIDEO,   //视频监控设备
	PG_DEVTYPE_ENVDATA,   //环境量采集设备
	PG_DEVTYPE_AIDDEV,    //站端辅助设备
	PG_DEVTYPE_NETWORK=6,   //网络设备
	PG_DEVTYPE_STORAGE=8,   //存储设备
}PG_DEVTYPE;

//环境设备名称枚举
typedef enum tagEnuPgDevName
{
	PG_DEVNAME_TEMPERATURE_SENSOR=0,  //温度变送器
	PG_DEVNAME_HUMIDITY_SENSOR=1,   //湿度变送器
	PG_DEVNAME_SF6,   //SF6浓度检测设备
	PG_DEVNAME_WINDSPEED,   //风速传感器
	PG_DEVNAME_WATER_DETECT,   //水浸探头
	PG_DEVNAME_INFRARED,     //红外对射
	PG_DEVNAME_DOORGUARD,   //门禁控制器
}PG_DEVNAME;

//环境变量结构体，对应该配置的通道号为3(配置函数的通道参数), 最大先限制为32个，现在设备默认8个
typedef struct tagEnvBaseInfo
{
	unsigned char nodeId;        // 设备编号流水号
    unsigned char iRPU;          /*0 主RPU 1从RPU*/
    unsigned char iDevType;      //设备类型,详见PG_DEVTYPE
	unsigned char iDevSubTyep;   //设备名称,详见PG_DEVNAME
	
	unsigned char ucEnable;      //使能
	unsigned char uiOsdPosition; //联动叠加osd位置，0左上，1右上，2左下 3 右下；
	unsigned char iSimZero;      //环境量归零值
	unsigned char iSimCos;       //环境量系数
	
	unsigned char uiSwitch;  
	unsigned char ucAlmName[15];  //名称，状态显示用
	
								  /*
								  变化阀值的检测间隔，单位为秒
								  表示当在检测间隔内环境量的值变化大于等于1时，则上报数据。
    */
	int iInterval; 
    
	int iChangeThresholdPercent; //变化阀值，百分比。当为0.0时，表示有变化就上报。
	int uiOsdMask;               //联动叠加osd到通道掩码；
	
	int uiAlarmTopLimit;
	int uiAlarmBottonLimit;       
	
	/*1-超下限1告警，2-超上限1告警，3-超下限2告警，4-超上限2告警，如果设备只支持上下限告警，
	则只用1和2表示，其他值为0
	*/
	unsigned char iAlmFlag[4];
	int uiTopMeasure;              // 量程上限
	int uiBottomMeasure;           // 量程下限
}ENV_BASE_INFO;

typedef struct _SENVState
{
	unsigned char iSignNo;	//序号
	unsigned char iType;	//类型//温度等见PG_DEVNAME
	unsigned char iState;	//状态//0、1、2正常、一级告警、二级告警
	unsigned char iAction;  //0,报警开始、1,报警停止
	int iValue;		//数值
	int iTime;		//时间time_t
}SENVState;
//////////////////////////////////////////////////////////////////////////

///////////////////平台接入配置结构体定义//////////////////////////////////
//北京一所平台接入配置结构体定义
typedef struct _SPlatGAYSCfg
{
    char szDeviceNO[32];  // 前端设备序列号，字符串, 包括'\0'结束符共32byte
    char szServerNo[32];  // SIP服务器序列号，包括'\0'结束符共16byte
	char szServerDn[32];  // SIP服务器域名，包括'\0'结束符共16byte
 
    int bCsEnable;		// 中心服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个
    char szCsIP[64];	// 中心服务器IP地址, 字符串, 包括'\0'结束符共16byte
    int usCsPort;		// 中心服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个 
    int iRsAgedTime;    // 注册服务器有效时间,   数值(单位:小时)
	int iHsIntervalTime;// 心跳服务器间隔周期,   数值(单位:秒) 
	int usUdpPort;		// 本地端口: 数值 1~65535,考虑4字节对齐,目前只用数组第一个 

	char Camreaid[RV_N_SYS_CH_32][32];	// 通道ID号
	int CamreaLevel[RV_N_SYS_CH_32];	// 通道报警级别
	char Alarmid[RV_N_SYS_CH_32][32];	// 报警ID号
	int AlarmLevel[RV_N_SYS_CH_32];	// 通道级别
    char szConnPass[36];			// 设备接入码
}SPlatGAYSCfg;
//////////////////////////////////////////////////////////////////////////

//!总大小1024
typedef struct  _RVENCODE_CAPS_NET2
{
	//!坐标索引为enum capture_size_t，每个分辨率支持的辅助码流(接位表示),
	//!bit:0 -CHL_2END_T
	//!bit:1 -CHL_3IRD_T
	//!bit:2 -CHL_4RTH_T
	//!bit:3 -CHL_5FTH_T
	unsigned int ImageSizeMask_Stream[64];
	unsigned char rev[768]; //!保留1008个保留位
 }RVENCODE_CAPS_NET2;

//明景像机参数配置
typedef struct _CONFIG_MJ_CAMERA_
{
	//没有说明的默认为 2:开启 3:关闭
	char DigitalZoom ;		// 数字变倍   
	char CameraOSD;			// 摄像机OSD
	char CameraMenu;		// 摄像机菜单
	char Illlumination;		// 低照度--2:开启 1:关闭 3:自动
	char WideDynamic;		// 宽动态
	char DigitReduceNoise;	// 数字降噪
	char AutoFocus;			// 自动聚焦
	char Backlight;			// 背光补偿
	char SharpAdjust;		// 锐度调节--0-15
	char ExposureComp;		// 曝光补偿
	char ExposureValue;		// 补偿值--0-14
	char ExposureMode;		// 曝光模式--0:自动1:手动2:快门优先3:光圈优先 
	char ApertureAdjust;	// 光圈调节--0-17
	char AutoShutter;		// 自动慢快门     
	char ShutterAdjust;		// 快门调节--0-21	
	char Frequency;			// 前端输入频率--50Hz/60Hz --需要重启
	char WhiteBalance;		// 白平衡 0:手动1:自动2:室内3:室外4:ATW 5:ONE PUSH 
	unsigned char TempEnable;	// 温度显示使能
	unsigned char SiteEnable;   // 云台坐标使能
	unsigned char BlindEnable;	// 遮挡是能
	unsigned int WhiteBalanceR; // 白平衡：红--0-255
	unsigned int WhiteBalanceB; // 白平衡：蓝--0-255
	unsigned char res1[64];		// 保留
}CONFIG_MJ_CAMERA;

//明景球机高级参数设置
typedef struct _CONFIG_MJ_ADV_CAMERA_   
{
	//没有说明的默认为 2:开启 3:关闭
	unsigned char AutoReverse;		// 自动翻转
	unsigned char TelephootSpeed;	// 长焦限速
	unsigned char PrescanFreeze;	// 预置位画面冻结
	unsigned char ShortCutMode;		// 快捷模式		开/关
	unsigned char NorthSet;			// 北位设置
	unsigned char WarmCtrl;			// 温度控制 0:自动  1:加热  2:散热 3:关闭
	unsigned char Time;				// 加热或散热的时间时长 秒为单位 0 表示一直加热
	unsigned char Limit;			// 上限0: 25 1:40  2:50 3:60
	unsigned char Lower;			// 下限 0:-10  1:0  2:10
	char res[63];
}CONFIG_MJ_ADV_CAMERA;

//明景云台参数设置
typedef struct _CONFIG_MJ_PTZ   
{
	unsigned char WiperCtrl;		// 雨刷控制        2:连续运行3:停止4:刮一次
	unsigned char InfraredCtrl;		// 夜视频设备      2:自动3:打开4:关闭
	unsigned char Demist;			// 除雾控制
	unsigned char LowPower;			// 低功耗
	unsigned char res[64];			// 保留
}CONFIG_MJ_PTZ ;

typedef struct _CONFIG_MJ_AUTO_HOME_   //自动归位
{
	//没有说明的默认为 2:开启 3:关闭
	unsigned char Enable;		// 自动翻转 2 3
	unsigned char PtzLink;		// 归位联动设置
	unsigned char LinkNum;		// 联动 值 250
	unsigned char PowRetset;	// 电板复位
	unsigned int Time;			// 归位等待时间
	char res[8];
}CONFIG_MJ_AUTO_HOME;

typedef struct _CONFIG_MJ_BLIND_   
{
	//没有说明的默认为 2:开启 3:关闭
	unsigned char bEnable;	// 使能	所有遮挡使用同一个是能
	unsigned char Index;
	char res0[2];
	int iColor;				// 遮挡颜色
	int iHight;				// 高度
	int iWight;				// 宽度
	char res1[16];
}CONFIG_MJ_BLIND;

typedef struct _CONFIG_MJ_POSTION_   //缩放命令
{
	unsigned int  Zoom ;		// 2 放大 3 缩小
	unsigned int Left;			// 左
	unsigned int Top;			// 右
	unsigned int Right;			// 高度
	unsigned int Bottom;		// 宽度
	char res[4];
}CONFIG_MJ_POSTION;

//!按位表示 标识Oem厂商的能力
typedef struct _ABILITY_OEM_FUN_
{
	unsigned int uiOemMask;		// 1位标示明景 bitmsk(0)
	unsigned int uiProduct;		// 表示产品类型 明景	1 高速球	5 云台TC26   	8 TC35
	unsigned int uiRes[3];		// 保留字,便以后扩展
}ABILITY_OEM_FUN_T;

// 智能检测能力集
typedef  struct _suva_ability_   
{
	unsigned char ucAbilty;	// 第1位表示是否支持SUVA智能
	unsigned char Res[31] ;	// 保留	
}SUVA_ABILITY;

typedef struct UC_RECT
{
	unsigned char left;
	unsigned char top;
	unsigned char right;
	unsigned char bottom;
}UC_RECT;

typedef struct UC_LINE
{
	unsigned char	A_X;	
	unsigned char	A_Y;	
	unsigned char   B_X;
	unsigned char   B_Y;
}UC_LINE;

typedef enum ERECTTYPE 
{
	EVA_RL_NOT_USED,
	EVA_RL_RECT,
	EVA_RL_REV_RECT,
	EVA_RL_LINE,
	EVA_RL_REV_LINE
}ERECTTYPE;

typedef struct UC_RECT_LINE
{
	unsigned char state;//RECTTYPE	
	union
	{
		UC_RECT mrect;
		UC_LINE mline;
	}type_t;
} UC_RECT_LINE;

typedef struct tagCONFIG_SUVA
{
	UC_RECT_LINE stSUVACFG[16];
	unsigned char rev[48];
}CONFIG_SUVA;

typedef struct tag_NET_SUVA_EREA
{
	int iChnIndex;
	CONFIG_SUVA cfg;
}NET_SUVA_EREA;

typedef struct tag_NET_Enable
{
	int iChnIndex;
	BOOL bEnable;
	int iLevel;
}NET_Enable;

typedef struct _SSUVACfg
{
	int iChnIndex;
	RV_ALARM_GUARD			stGuard;
	CONFIG_SUVA             stErea;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;		//deal method [处理方式]
}SSUVACfg;

// SUVA配置命令字--SUVA_CONFIG_TYPE
typedef struct _SSUVACfgs
{
	UInt32 dwSize;
	SSUVACfg cfg[RV_MAX_CHANNUM];
}SSUVACfgs;

//3G配置能力集--DEV_ABILITY_3G=105
typedef struct _NET_WRIELESS{
	int iWrielessMask;
	//设置1支持3G，0不支持
	int iRes[3];
}NET_WRIELESS;

//3G配置结构体--DEV_CONFIG_TYPE_WEIELESS = 691,  //无线配置 
typedef struct NET_WRIELESS_CONFIG
{
	int enable;
	char username[64];
	char password[64];
	char ip[16];
	int type;			// 类型(不可配) 0:EC1261, 1:EC1260
	int signal;			// 信号强度(不可配) 范围(0~100)
}NET_WRIELESS_CONFIG;

//VISS平台接入
typedef struct _SPlatCfgViss
{
	unsigned short usCompanyID[2];  /* 公司ID,数值,不同的第三方服务公司,考虑4字节对齐,目前只用数组第一个 */
	char szDeviceNO[32];  /* 前端设备序列号，字符串, 包括'\0'结束符共32byte */
	char szVSName[32];  /* 前端设备名称，字符串, 包括'\0'结束符共16byte */
	char szVapPath[32];  /* VAP路径 */
	unsigned short usTcpPort;  /* TCP 端口,数值: 数值 1~65535 */    
	unsigned short usUdpPort;  /* UDP 端口,数值: 数值 1~65535 */    
	////bool bCsEnable[4];  /* 中心服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个 */
	char szCsIP[64];  /* 中心服务器IP地址, 字符串, 包括'\0'结束符共16byte */
	unsigned short usCsPort[2];  /* 中心服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个 */    
	//bool bHsEnable[4];  /* 心跳服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个 */
	char szHsIP[64];  /* 心跳服务器IP地址, 字符串, 包括'\0'结束符共16byte */
	unsigned short usHsPort[2];  /* 心跳服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个 */ 
	int iHsIntervalTime;  /* 心跳服务器间隔周期,数值(单位:秒) */ 
	//bool bRsEnable[4];  /* 注册服务器使能标志, 数值: true使能, false不使能,考虑4字节对齐,目前只用数组第一个 */
	char szRsIP[64];  /* 注册服务器IP地址, 字符串, 包括'\0'结束符共16byte */
	unsigned short usRsPort[2];  /* 注册服务器端口,数值: 数值 1~65535,考虑4字节对齐,目前只用数组第一个 */
	int iRsAgedTime;  /* 注册服务器有效时间,数值(单位:小时) */
	char szAuthorizeServerIp[64];  /* 鉴权服务器IP */
	unsigned short usAuthorizePort[2];  /* 鉴权服务器端口,考虑4字节对齐,目前只用数组第一个 */
	char szAuthorizeUsername[32];  /* 鉴权服务器帐号 */
	char szAuthorizePassword[36];  /* 鉴权服务器密码 */
	
	char szIpACS[64];  /* ACS(自动注册服务器) IP */
	unsigned short usPortACS[2];  /* ACS Port,考虑4字节对齐,目前只用数组第一个 */
	char szUsernameACS[32];  /* ACS用户名 */
	char szPasswordACS[36];  /* ACS密码 */
	//bool bVideoMonitorEnabled[4];  /* DVS是否定期上报前端视频信号监控信息, 数值: true使能, false不使能 */
	int iVideoMonitorInterval;  /* 上报周期（分钟） */
	
	char szCoordinateGPS[64];  /* GPS坐标 */
	char szPosition[32];  /* 设备位置 */
	char szConnPass[36];  /* 设备接入码 */
}SPlatCfgViss;

typedef struct _CONFIG_NET_BLUESTAR
{ 
	BOOL Enable;		// 是否开启	
	char  ServerIp[32];	// 神眼服务器IP
	int ServerPort;		// 服务器端口号
	int key;				// 服务器验证码
	unsigned int retries;	// 失败重试次数
	int  usTcpPort;			// 对外的TCP 端口,数值: 数值 1~65535 */      
	int  usUdpPort;			// 对外的UDP 端口,数值: 数值 1~65535 */    
	char Reserved[16];
}CONFIG_NET_BLUESTAR;

typedef struct tagCONFIG_NET_HW
{ 
    BOOL Enable;			// 是否开启
    char  FtpServerIp[32];	// Ftp服务器
    int FtpServerPort;
    char FtpUsr[16];
    char FtpPwd[16];    
    char FtpPathName[RV_FTP_MAXDIRLEN];   
	int DownloadPeriod;		// 下载周期(10 -3000, 缺省设置为30秒)
    char  HWServerIp[32];	// 豪威服务器
    int HWServerPort;
	unsigned short KeepLiveTime;
	unsigned char Reserved1[2];
	int VideoNo; //
    char Reserved2[56];
}CONFIG_NET_HW;

typedef struct tagCONFIG_NET_SZYUANYANG
{
    BOOL Enable;
    char svrname[128];
    char acRpuId[20];
    char connpass[128]; //注册时需要此信息
    char ServerIp[32];
    int ServerPort;
    unsigned short usListernTcpPort;
    unsigned short usListernUdpPort;
    int iRpuMajorType; //主类型， 当前为1
    int iRpuMinorType; //子类型， 当前为1
    char szRpuModel[32];
    char szRpuSerialId[64];
    char szRpuVersion[64];
    int iSubDevIdNum; //内部数据量，只读，设置时为0，查询时返回具体数量
    int iHeartBeatInterval; //心跳间隔，秒
    unsigned char RtspType;
	unsigned char res[3];
}CONFIG_NET_SZYUANYANG;

typedef struct _SHRegConfig
{
	BOOL Enable;
	char ServerIP[32];
	int ServerPort;
	char AngentID[16];
	char Reserved[64];
}SH_REG_CONFIG;

// chinamoble--EPLAY_TYPE_CHINAMOBILE
typedef struct tagCONFIG_NET_CHINAMOBILE
{
    BOOL Enable;
    char SIP_ServIpAddress[32];    /*服务器IP地址*/
    int SIP_ServPort;    /*业务平台服务器端口*/
    char SIP_ServDomainName[64];   /*业务平台服务器域名*/
    char SIP_PuID[64];   /*业务平台帐号*/
    char SIP_PuPW[64];  /*业务平台密码*/ 
    char CWMP_AcsUrl[128]; /*网管平台服务器URL*/
    char CWMP_AcsUserName[32];     /*网管平台帐号*/
    char CWMP_AcsPassword[32];     /*网管平台密码*/
    int CWMP_InformPeriodic;   /*网管平台心跳周期*/
	char Reserved[32];
}CONFIG_NET_CHINAMOBILE;

enum _ENUM_COLOR_TYPE_ 
{
    ENUM_COLOR_RUILI,		//锐利
	ENUM_COLOR_YANLI,		//艳丽
	ENUM_COLOR_BIAOZHUN,	//标准
	ENUM_COLOR_ROUHE,		//柔和
	ENUM_COLOR_ZHENGCHANG,	//正常
	ENUM_COLOR_ZIDINGYI		//自定义
};

//支持的图像风格能力级--DEV_ABILITY_SUPPORT_COLOR_TYPE 
typedef  struct _COLOR_ABILITY_
{
	unsigned short usSupportColorType;	// 支持的风格,按位表示，参考枚举_ENUM_COLOR_TYPE_
	unsigned char ucSupportSharpness;	// 是否支持锐度
	unsigned char Res[29];				// 保留
}COLOR_ABILITY;

// 视频颜色结构--ENCODE_COLOR_TYPE_EX
typedef struct tagVIDEOCOLOR_PARAM_EX
{
    int iSharpness;
    int iType;
    int iRes[5];
}VIDEOCOLOR_PARAM_EX;

// 支持分辨率和制式能力级-DEV_ABILITY_SUPPORT_SENSOR_TYPE 
typedef  struct _SENSOR_ABILITY   
{
	unsigned int iMskList;	// 0 1080P@30fps、1:1080P@25fps、720P@30fps、720P@25fps   按位表示
	unsigned int iMskFun;	// 1：表示不支持区域遮挡功能
	unsigned int Res[2] ;	// 
}SENSOR_ABILITY;


typedef enum _VD_SENSOR_TYPE_E
{
	APTINA_9P031_DC_1080P_CONTINUES = 0,
	APTINA_9P031_DC_1080P_DEFAULT =1,
	ALTASENS_DC_1080P = 2,
	OV_2715_DC_1080P = 3,
	OV_10630_DC_800P = 4,
	PANASONIC_34041_1080P = 5,
	SONY_IMX036_DC_1080P = 6,
	APTINA_9M034_DC_720P_CONTINUES = 7,
	OV_2715_BT601_1080P = 8,
	BT656_D1P = 9,
	BT1120_720P = 10,
	VISIONDIGI_HITACHI_110_720P25 = 11,
	VISIONDIGI_HITACHI_110_720P30 = 12,
	VISIONDIGI_HITACHI_110_960P20 = 13,
	VISIONDIGI_SONY_EH4300_1080P = 14,
	VISIONDIGI_SONY_EH4300_720P = 15,
	VISIONDIGI_SONY_EH4300_1080I = 16,
	VISIONDIGI_SAMSUNG_5190_SXGA = 17,
	ANASONIC_34041_1080P_60FPS =18,
	SONY_IMX122_DC_1080P =19,
	APTINA_AR0331_DC_1080P_30FPS = 20,
	APTINA_AR0331_DC_3M_20FPS = 21,
	APTINA_AR0331_DC_1080P_60FPS =22, 
	VISIONDIGI_CS_110_720P30 =23,
	BT1120_1080P=24,   
	VISIONDIGI_SAMSUNG_6200 = 25,    
	PANASONIC_34041_720P = 26, 
	VISIONDIGI_SAMSUNG_5190_720P = 27,
	SENSOR_S532_720P = 28,   
	VISIONDIGI_LG_2810=29,
	APTINA_9M034 =30,
	VISIONDIGI_HITACHI_220_1080P = 31,
	VISIONDIGI_NUM,
}VD_SENSOR_TYPE_E;

// 瓒呯骇鐢ㄦ埛鏉冮檺 DEV_SYSTEM_INFO_SUPERUSER_AUTH
typedef struct _SUPER_USER_AUTH_LIST
{
	/*按位表示支持的功能
	0 : 支持多种机芯设置 
	1 : 多种编码类型
	2 : 支持设置坏点检查
	*/
	unsigned int uiFunMask;   //
	
	unsigned int uiSensorTypeL;  // 机芯类型掩码低32位, 详见EVD_SENSOR_TYPE_E
	unsigned int uiSensorTypeH; 
	unsigned char ucProfileType;  // 掩码表示2 hp  1 M   0  Baseline
	unsigned char uiReserved[63];
} SUPER_USER_AUTH_LIST;

// 多行OSD叠加--DEV_ABILITY_OSD_MULINE
typedef struct _ABILITY_MUTILETITLE
{
    //是否支持多行osd叠加，1表示支持
    unsigned int uiMutlineAbility;
    unsigned int uiRes[3];/*保留字，便以后扩展*/
}ABILITY_MUTILETITLE_T;

//设备支持的告警类型--DEV_ABILITY_SUPPORT_ALARM 
typedef  struct _alarm_support_ability_     
{
	//按位来标识设备支出的报警类型 ，为了对以前兼容 0 表示支持 1 表示不支持
	// 0  alarmin  1 动检 2 丢失 3 遮挡 4 解码 5 网络报警 6
	unsigned int uiAlarmAbilty;
	unsigned int ucRes[3] ;//保留
}ALARM_SUPPORT_ABILITY;

// IPv6能力集--DEV_ABILITY_IPV6
typedef struct _ABILITY_IPV6_T
{
	unsigned int uiSupport;/*第0位表示是否支持IPV6，第1位表示是否支持IPV6 DHCP,其他暂时保留*/
	unsigned int reserve[7];
}ABILITY_IPV6_T;

// 平台接入日志查询能力集 
typedef struct _ABILITY_INTERVIDEO_LOG_T
{
	unsigned int  uiSupport;
	unsigned int uiMask;		// 参考IVIDEO_ABILITY.iIVideoMask 的定义，表示支持的平台接入日志类型*/
	unsigned int reserve[3];	// 保留 
}ABILITY_INTERVIDEO_LOG_T;

// MTU设置能力级--DEV_ABILITY_MTU
typedef struct _ABILITY_MTU_T
{
	unsigned int uiSupport;		// 第0位表示是否支持MTU设置
	unsigned short usMtuMin;
	unsigned short usMtuMax;    
	unsigned int reserve[6];
}ABILITY_MTU_T;

typedef struct tagCONFIG_VIDEOCOLOR_EX
{
    VIDEOCOLOR_PARAM_EX dstColorParam[2];
}CONFIG_VIDEOCOLOR_EX;

typedef struct tagNET_VIDEOCOLOR_EX
{
    int iChannel;
    VIDEOCOLOR_PARAM_EX dstColorParam[2];
}NET_VIDEOCOLOR_EX;

// 各种风格对应的显示值--ENCODE_COLOR_TYPE_EX_TABLE
typedef  struct _COLOR_TYPE_SHOW_VALUE_
{
    unsigned short usType;
    unsigned char ucBrightness;
    unsigned char ucContrast;
    unsigned char ucSaturation;
    unsigned char ucHue;
    unsigned char ucsharpness;
    unsigned char ucRes[5];
}COLOR_TYPE_SHOW_VALUE;

typedef  struct COLOR_TYPE_EX_TABLE_
{
    int  SupportNum;
    COLOR_TYPE_SHOW_VALUE       stShowValue[16];
}COLOR_TYPE_EX_TABLE;

// 视频采集配置信息--CAMERA_RESOLUTION_TYPE
typedef struct tagCONFIG_SENSOR
{
	int iResolution; //0 1080P@30fps、1:1080P@25fps、720P@30fps、720P@25fps    数值表示
	int Res[3];
} CONFIG_SENSOR;

// 视频采集配置信息-宽动态--CAMERA_DRC_TYPE
typedef struct _CAMERA_DRC
{
	unsigned int enable;    //
	unsigned int Strength;  // 0 - 255
	unsigned char SlowFrameRate;		// 1-15 多帧采集  低照度情况提升图像质量
	unsigned char res[15];
}CAMERA_DRC;

// 超级用户配置--CAMERA_SUPPER_CONFIG_TYPE
typedef struct _CONFIG_SUPPER
{
	unsigned char bProfile;
	unsigned char bSensortype;
	char res[32];
}CONFIG_SUPPER;

typedef struct _CONFIG_RECORD_MULTI_STREAM
{
	unsigned int streammain;	// 主辅码录像标志，取32位便于日后扩展 ，按位表示相应通道的录像是否打开		
	unsigned int stream2snd;    // 辅辅码录像标志，取32位便于日后扩展 ，按位表示相应通道的录像是否打开
	char res[32];				// 保留
}CONFIG_RECORD_MULTI_STREAM;

// 无码检测（无码流设备自动重启使能），能力级：RV_ENCODE_CAPS_NET_EN：ucEncoderDetect；配置--DEV_ENCODER_DETECT_CFG 
typedef  struct _encoder_detecte_   
{
	unsigned char bEnable;
	unsigned char Res[15] ;
}ENCODER_DETCETE;

// MTU配置--DEV_CONFIG_TYPE_ETHERNET_MTU
typedef struct _MTU_SET
{
	unsigned short usMtu; 
	unsigned short usReserve[15];   //保留
} MTU_SET;
/******************************************************************************
* end of configure struct [end of 配置结构体]
*****************************************************************************/
#ifdef __cplusplus
}
#endif

NAMESPACE_END
#endif
