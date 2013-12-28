/*
 * protocol.h
 * 王冠 2011.05.24 创建
 * 王冠 2011.05.27 修改
 * 李彪 2012.04.26 添加WIFI加密方式
 * v0.1.0.0
 */
#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#define EVT_TIMESLICES                  7
#define TIME_CONFIG_NUMS                5
#define MAX_GPIO_IN_NUM                 1

//产品型号
typedef enum _tagEmMachType
{
	IPC3516_001 = 0,
}EmMachType;

typedef enum _tagEmVideoFormat
{
	_H264 = 0,
	_MJPEG,
	_MPEG2,
	_MPEG4
}EmVideoFormat;

typedef enum _tagEmVideoResolution
{
	_2560x1920 = 0x0, //新增加的5M分辨率,为了兼容之前版本，放在后面
	_2048x1536 = 0x01, //新增加的3M分辨率
	_1920x1080 = 0x02,
	_1280x720,
	_HD_END,
	_960x540,
	_704x576,
	_704x480,
	_640x480,
	_480x272,
	_352x288,
	_352x240,
	_320x240,
	_176x144,
	_176x120,
	_SD_END,

	_1280x960 = 0x1000,	//1.3M分辨率
	_1440x1080			//4:3比例的1080p
}EmVideoResolution;

typedef enum _tagEmVideoRcMode
{
	_CBR = 0,
	_VBR,
	_FIXQP
}EmVideoRcMode;

typedef enum _tagEmTranProto
{
	_udp = 0,
	_tcp,
	_rtp,
	_losock,
	_save,
	_tcpserv,
	_losockmux,
	_loimgw,
}EmTranProto;

typedef enum _tagEmDDNSType
{
	_oray = 0,
}EmDDNSType;

typedef enum _tagEmPtzProto
{
	_PtzPelcoP = 0,
	_PtzPelcoD,
	_PtzGA10,
	_PtzGA00
}EmPtzProto;

typedef enum _tagEmPtzCmd
{
	_transparent,		//透明传输
	_left,				//左转
	_right,				//右转
	_up,				//上倾
	_down,				//下倾
	_leftup,			//左上
	_leftdown,			//左下
	_rightup,			//右上
	_rightdown,			//右下
	_stop,				//停止
	_wide,				//视角变宽
	_tele,				//视角变窄
#ifdef _WIN32
	#if (_MSC_VER >= 1300)
	_near,				//焦距拉近
	_far,				//焦距推远
	#else
	_near_ptz,
	_far_ptz,
	#endif
#elif linux
	_near,
	_far,
#else
	#error unknown platform
#endif
	_open,				//光圈打开
	_close,				//光圈关闭
	_setpreset,			//设置预置位
	_clearpreset,		//清除预置位
	_gotopreset,		//调用预置位
	_3d,				//3d功能
	_patternstart,		//开始记录循迹路线
	_patternstop,		//停止记录循迹路线
	_patternrun,		//按照预设路线循迹
	_auxon,				//辅助开
	_auxoff,			//辅助关
	_patrolrun,			//巡航
	_patroladd,			//添加巡航点
	_patrolremove,		//删除巡航点
	_patrolholdtime,	//设置巡航点停留时间
	_patrolremovegroup,	//删除巡航组
	_patrolremoveall,	//删除全部巡航组
	_patrolspeed,		//设置巡航速度
	_autoscan,			//自动扫描
	_scanleft,			//扫描左边界
	_scanright,			//扫描右边界
	_scanspeed,			//扫描速度
	_figurescan,		//花样扫描
	_figurescanspeed,	//花样扫描速度
	_randomscan,		//随机扫描
	_rotation,			//360度旋转
	_rotationspeed,		//360度旋转速度
	_keepwatchon,		//守望开启
	_keepwatchoff,		//守望关闭
	_keepwatchholdtime, //守望等待时间
	_menucall,			//菜单调用

	_menusetpreset,			//菜单中设置预置位
	_menuclearpreset,		//菜单中清除预置位
	_menugotopreset,		//菜单中调用预置位
	_menupatternstart,		//菜单中停止记录循迹路线
	_menupatternstop,		//菜单中停止记录循迹路线
	_menupatternrun,		//菜单中按照预设路线循迹
	_menuauxon,				//菜单中辅助开
	_menuauxoff,			//菜单中辅助关
	_menupatrolrun,			//菜单中巡航
	_menupatroladd,			//菜单中添加巡航点
	_menupatrolremove,		//菜单中删除巡航点
	_menupatrolholdtime,	//菜单中设置巡航点停留时间
	_menuautoscan,			//菜单中自动扫描
	_menuscanleft,			//菜单中扫描左边界
	_menuscanright,			//菜单中扫描右边界
	_menuscanspeed,			//菜单中扫描速度
	_menufigurescan,		//菜单中花样扫描
	_menufigurescanspeed,	//菜单中花样扫描速度
	_menurandomscan,		//菜单中随机扫描
	_menurotation,			//菜单中360度旋转
	_menurotationspeed,		//菜单中360度旋转速度
	_menukeepwatchon,		//菜单中守望开启
	_menukeepwatchoff,		//菜单中守望关闭
	_menukeepwatchholdtime, //菜单中守望等待时间
	_directpositionpan,		//直接位置控制水平
	_directpositiontilt,	//直接位置控制垂直
	_directpositionzoom,	//直接位置控制变倍
	_directpositionfocus,	//直接位置控制聚焦
	_directctrolintegrazoom,//直接位置控制一体化摄像机变倍
	_angelcotrolpan,		//角度控制水平位置
	_angelcotroltilt,		//角度控制垂直位置
	_angelcotrolzoom,		//角度控制变倍位置
	_angelcotrolfocus,		//角度控制聚焦位置
	_angelcotroliris,		//角度控制光圈位置
	_queryall,				//查询全部
	_querypanposition,		//查询当前水平位置
	_querytiltposition,		//查询当前垂直位置
	_querycamerazoom,		//查询镜头变倍
	_querycamerafocus,		//查询镜头聚焦
	_queryirisswitch,		//查询镜头光圈
	_queryenvvariable,		//查询云台/球机内部温度、湿度、压强
	_queryvoltage,			//查询电源电压是否正常和视频是否丢失
	_querypositionmax,		//查询全部（水平、垂直、镜头）位置最大值
	_querypanmax,			//查询水平最大值
	_querytiltmax,			//查询垂直最大值
	_queryzoommax,			//查询变倍最大值
	_queryfocusmax,			//查询聚焦最大值
	_queryirismax,			//查询光圈最大值
}EmPtzCmd;

typedef enum _tagEmIspMenuCmd
{
	_IspMenuLeft,			//左
	_IspMenuRight,			//右
	_IspMenuUp,				//上
	_IspMenuDown,			//下
	_IspMenuStop,			//停止
	_IspMenuOpen,			//开启菜单/确定
}EmIspMenuCmd;


typedef enum _tagEmMediaProc
{
	_none = 0,
	_file,
	_ftp,
	_email
}EmMediaProc;

typedef enum _tagEmFileOp
{
	_install = 0x100,			//完整安装软件
	_updatefirmware = 0x1000,	//升级固件
	_updatewebpages,			//升级内置网页
	_updateplatformlib,			//升级平台对接库
	_updateLDUpdatefile,        //远程升级ptz设备升级文件

	_queryloglist = 0x2000,		//查询日志文件列表
	_querycfglist,				//查询配置文件列表
	_queryssidlist,				//查询ssid列表

	_uploadcfg = 0x3000,		//上传配置文件
	_uploadmenuxml,				//上传菜单解析XML文件

	_downloadlog = 0x4000,		//下载日志文件
	_downloadcfg,				//下载配置文件
	_downloadfilelist,			//下载文件列表
	_downloadsnap,				//下载抓拍文件
	_downloadrecd,				//下载录像文件

	_getsnapdata,               //获取抓拍图像的数据

	_deletefile = 0x5000,		//删除SD卡文件
}EmFileOp;

//传感器/相机类型
typedef enum _emViDevType
{
    APTINA_9P031_DC_1080P_CONTINUES = 0,
    APTINA_9P031_DC_1080P_DEFAULT,
    APTINA_9P031_DC_2560_1920_8FPS,				//JJW 为展会添加 20121107
    ALTASENS_DC_1080P,
    OV_2715_DC_1080P,
    OV_10630_DC_800P,
    PANASONIC_34041_1080P,
    PANASONIC_34041_1080P_60FPS,
    SONY_IMX036_DC_1080P,
    SONY_IMX122_DC_1080P,
    APTINA_9M034_DC_720P_CONTINUES,
    APTINA_AR0331_DC_1080P_30FPS,
    APTINA_AR0331_DC_1080P_60FPS,
    APTINA_AR0331_DC_2048_1536_15FPS,          //JJW 为展会添加  20121107
    APTINA_AR0331_DC_1440_1080_30FPS,          //JJW 为展会添加  20121107

    OV_2715_BT601_1080P,
    BT656_D1P,
    BT1120_720P,

    //自定义传感器

    //自定义相机
    SONY_CH6300_CAM_VIDEV0_1080P_25 = 0x2000,
    SONY_CH6300_CAM_VIDEV0_1080P_30,
    SONY_CH4300_CAM_VIDEV0_1080P_25,
    SONY_CH4300_CAM_VIDEV0_1080P_30,

    NONAME001_BT1120_VIDEV0_1080P_25,
    NONAME001_BT1120_VIDEV0_1080P_30,
    NONAME001_BT1120_VIDEV0_720P_25,
    NONAME001_BT1120_VIDEV0_720P_30,

    NONAME001_ISP_BT1120_VIDEV0_1080P_25,
    NONAME001_ISP_BT1120_VIDEV0_1080P_30,
    NONAME001_ISP_BT1120_VIDEV0_720P_25,
    NONAME001_ISP_BT1120_VIDEV0_720P_30,

    YAAN_HDC7301K_D130_VIDEV0_720P_25,
    YAAN_HDC7301K_D130_VIDEV0_960P_12,

    BDM_S532_CAM_VIDEV0_720P_25,
    BDM_S532_CAM_VIDEV0_720P_30,

    SC110_VIDEV0_720P_25,
    SC110_VIDEV0_720P_30,

    BDM_S642_CAM_VIDEV0_1080P_25,
    BDM_S642_CAM_VIDEV0_1080P_30,

    SONY_CH3400_CAM_VIDEV0_720P_25_INTER,
    SONY_CH3400_CAM_VIDEV0_720P_30_INTER,
    SONY_CH3400_CAM_VIDEV0_720P_25_EXTER,
    SONY_CH3400_CAM_VIDEV0_720P_30_EXTER,

}EmViDevType;

//wifi加密方式
typedef enum _tagEmWifiEncryption
{
	_wep = 0,
	_wpatkip,
	_wpaaes,
	_wpa2tkip,
	_wpa2aes,
	_wpatkipaes,
	_wpa2tkipaes,
	_wpa1wpa2tkip,
	_wpa1wpa2aes,
	_wpa1wpa2tkipaes,
}EmWifiEncryption;

//3G类型
typedef enum _tagEm3GType
{
	_UnicomWcdma,
	_TelcomCdma2000,
	_MobcomTdcdma,
}Em3GType;

//3G连接状态
typedef enum _tagEm3GStatus
{
	_connecting,
	_connected,
	_disconnected,
}Em3GStatus;

typedef struct _tagStTransBuffer
{
	unsigned int u32DataSize;
	unsigned char u8DataBuffer[64];
}StTransBuffer;

typedef struct _tagSt3DParam
{
	char s8Pan;			//左上为正向
	char s8Tilt;		//左上为正向
	char s8Multi;		//正数为放大，负数为缩小
}St3DParam;

typedef struct _tagStPositionDCDir
{
	bool boAbsolute;
	bool boPositive;
}StPositionDCDir;

typedef struct _tagStGrpPtr
{
	unsigned char u8Grp;
	unsigned short u16Ptr;
}StGrpPtr;

typedef struct _tagStAutoScan
{
	unsigned char u8ScanId;
	unsigned char u8ScanSpeed;
}StAutoScan;

typedef struct _tagStMenuCall
{
	unsigned char u8MenuCmd;
	unsigned char u8MenuData1;
	unsigned char u8MenuData2;
	unsigned char u8MenuData3;
}StMenuCall;

typedef struct _tagStPanTilt
{
	unsigned char u8PanSpeed;
	unsigned char u8TiltSpeed;
}StPanTilt;

typedef union _tagUoPtzArgs
{
	StTransBuffer stTransBuffer;
	St3DParam st3DParam;
	StPositionDCDir stPositionDCDir;
	StPanTilt stPanTilt;
	StGrpPtr stGrpPtr;
	StAutoScan stAutoScan;
	StMenuCall stMenuCall;
	unsigned int u32Value;
}UoPtzArgs;

#ifndef _WIN32
typedef struct _tagStThrdObj
{
	const char	*pThrdName;
	void		*(*pThrdFxn)(void *);		//线程函数
	int			u32ThrdPrio;				//线程优先级
	/*      thread 1       :        thread 2
	 *                     :
	 * s32MsgQueNextSend ----> s32MsgQuePrevRecv
	 *                     :           |
	 *                     :           V
	 * s32MsgQueNextEcho <---- s32MsgQuePrevEcho
	 *                     :
	 *                     :
	 */
	int			s32MsgQuePrevRecv;			//用于接收“前一个线程传送过来的消息”的队列
	int			s32MsgQuePrevEcho;			//用于回应“前一个线程传送过来的消息”的队列
	int			s32MsgQueNextSend;			//用于发送“后一个线程传送过来的消息”的队列
	int			s32MsgQueNextEcho;			//用于接收“后一个线程传送过来的应答”的队列
	pthread_t	stThrd;						//线程数据结构(句柄)
}StThrdObj;
#endif

typedef struct _tagStMediaChan
{
	char	s8ChanName[20];
	int		s32Chans;
}StMediaChan;

typedef struct _tagStDeviceBasicInfo
{
	char			s8Manufacturer[8];		//设备生产厂家YAAN
	unsigned int	u32DeviceType;			//设备类型 0: IPC, 1:DVS,2:DVR 3:NVR
	char			s8Serialno[32];			//序列号
	char			s8DeviceName[32];		//设备名字
	char			s8DeviceID[32];			//设备ID, 一般为平台分配，出厂设备赋值为NULL；
	char			s8TypeName[32];			//设备型号，HDH2045-R21
	char			s8FirmVersion[32];		//固件版本号
	char			s8WebVersion[32];		//网页版本号
	char			s8PlatformVersion[32];	//平台版本号
	int				s32VinCount;			//视频输入数量
	int				s32AinCount;			//音频输入数量
	int				s32AoutCount;			//音频输出数量
	int				s32GPioInCount;			//报警器输入数量
	int				s32GPioOutCount;		//报警输出数量
	int				s32ComCount;			//串口数
}StDeviceBasicInfo;

typedef struct _tagStMachInfo
{
	EmMachType		emMachType;
	unsigned int	u32FirmwareVersion;
}StMachInfo;

typedef struct _tagStPtzWebInfo
{
	unsigned int	u32PtzVersion;
	unsigned int	u32WebpagesVersion;
}StPtzWebInfo;

typedef struct _tagStCbrAttr
{
	unsigned int u32BitRate;			     //码率，单位kbps
	unsigned int u32MinQp;                               //CBR最小QP值
	unsigned int u32MaxQp;                               //CBR最大QP值
}StCbrAttr;

typedef struct _tagStFixQpAttr
{
	unsigned int u32Qp;					//质量
}StFixQpAttr;

typedef struct _tagStH264VbrAttr
{
	unsigned int u32MaxBitRate;		/* 编码器输出最大码率，以kbps 为单位; 可用取值范围：[16, 40960] */
	unsigned int u32MaxQp;			/* 编码器支持图像最大QP, 取值范围：[u32MinQp, 51] */
	unsigned int u32MinQp;			/* 编码器支持图像最小QP, 取值范围：[0, 51] */
}StH264VbrAttr;

typedef struct _tagStMjpegVbrAttr
{
	unsigned int u32MaxBitRate;		/* 最大bitrate，以kbps 为单位; 可用取值范围：[16, 40960] */
	unsigned int u32MaxQfactor;		/* 最大量化因子，取值范围：[1, 99] */
	unsigned int u32MinQfactor;		/* 最小量化因子，取值范围：[1, u32MaxQfactor) */
}StMjpegVbrAttr;

typedef union _tagUoVbrAttr
{
	StH264VbrAttr stH264VbrAttr;
	StMjpegVbrAttr stMjpegVbrAttr;
}UoVbrAttr;

//音频参数
typedef enum _tagEmAiDevice
{
	//_MUTE,		//静音
	_MICIN,		//MIC
	_LINEIN,	//线性输入
}EmAiDevice;

typedef struct _tagStAudioAttr
{
	EmAiDevice			emAiDevice;			//音频输入设备
	unsigned int		u32AoVolume;		//音频输出音量,取值范围：[0, 100]
	bool				boSoftMute;			//软静音，true软静音使能，false软静音关闭
}StAudioAttr;

//视频参数
typedef struct _tagStVideoAttr
{
	char				s8Chn;				//视频通道，'0'为主码流，'1'为预览码流
	EmVideoFormat		emVideoFormat;		//视频格式
	EmVideoResolution	emVideoResolution;	//视频分辨率
	EmVideoRcMode		emVideoRcMode;		//视频码率调整模式
	unsigned int		u32FPS;				//视频帧率
	unsigned int		u32IFrameIntv;		//I帧间隔
	StCbrAttr			stCbrAttr;
	StFixQpAttr			stFixQpAttr;
	UoVbrAttr			uoVbrAttr;
}StVideoAttr;

//图像质量参数
typedef struct _tagStCscAttr
{
	int s32Luma;		//亮度
	int s32Contr;		//对比度
	int s32Hue;			//色调
	int s32Satu;		//饱和度
	int s32Sharpen;		//锐度
	unsigned char u8AntiFlickerFreq;	//抗闪烁频率
}StCscAttr;

//视频传感器参数
typedef struct _tagStCCDAttr
{
//	EmViDevType emViDevType;
	bool boMirror;
	bool boFlip;
	bool boAEG;
	int	s32Exposure;
	int s32AnalogGain;			//0-8
	int s32DigitalGain;			//0-8
	bool boAWB;
	unsigned short u16RGain;	//0-4095
	unsigned short u16BGain;	//0-4095
}StCCDAttr;

typedef struct _tagStVppAttr
{
	char s8Chn;				/* 视频通道，'0'为主码流，'1'为预览码流 */
	bool boVppEn;			/* Vpp硬件功能总开关 */
	bool boDnEn;			/* 图像去噪功能（Denoise）开关（包含空域滤波和时域滤波的图像去噪功能） */
	bool boSpEn;			/* 图像锐化（Sharpen）功能开关 */
	bool boIencEn;			/* 图像噪声检测功能开关 */

	int s32SpSth; 			/* 图像锐化的强度值，取值范围为[-4, 5] */
	int s32DnSfCosSth; 		/* 空域去噪强度1，取值范围为[0, 3] */
	int s32DnSfIncSth; 		/* 空域去噪强度2，取值范围为[0, 255] */
	int s32DnTfSth; 		/* 时域去噪强度，取值范围为[0, 4] */
}StVppAttr;

//播放控制参数
typedef struct _tagStPlayCtrl
{
	EmTranProto		emTranProto;
	unsigned int	u32DestIP;			//目标IP
	unsigned int	u32DestPort;		//目标端口
	unsigned char	u8IsPlayingVideo;	//视频播放状态
	unsigned char	u8IsPlayingAudio;	//音频播放状态
	char			s8ChanNum;			//视频通道号，ascii码字符
}StPlayCtrl;

//菜单控制参数
typedef struct _tagStMenuCtrl
{
	char s8OpCode[64];
	/*
	 * "UP"		-光标移动到上一条目
	 * "DOWN"	-光标移动到下一条目
	 * "NEXT"	-进入下级菜单
	 * "PREV"	-返回上级菜单
	 * "SHOW"	-显示菜单
	 * "HIDE"	-隐藏菜单
	 */
}StMenuCtrl;

typedef enum _tagEmIPAddrType
{
	_FIXIP,				//固定IP
	_DHCP,				//自动分配IP
	_PPPoE,				//pppoe拨号
}EmIPAddrType;

//网络参数
typedef struct _tagStNetworkAttr
{
	EmIPAddrType	emIPAddrType;		//IP获取方式
	unsigned int	u32FixIP;			//本地固定IP
	unsigned int	u32TmpDHCPIp;		//DHCP获得的临时IP
	unsigned int	u32TmpPPPoEIp;		//PPPoE获得的临时IP
	unsigned int	u32Mask;			//子网掩码
	unsigned int	u32Gateway;			//网关IP
	unsigned char	u8Mac[6];			//MAC地址
	unsigned int	u32DNS[2];			//dns
	unsigned int	u32RtspPort;		//rtsp端口号
	unsigned int	u32FilePort;		//文件操作端口
}StNetworkAttr;

//隐私遮挡参数
typedef struct _tagStPrivacyAttr
{
	int				s32X;				//位置X
	int				s32Y;				//位置Y
	int				s32Width;			//宽度
	int				s32Height;			//高度
	unsigned int	u32Color;			//颜色A-R-G-B格式
	bool			boIsShow;			//是否显示
}StPrivacyAttr;

//字符显示参数
typedef struct _tagStStringAttr
{
	unsigned short	u32X;						//位置X
	unsigned short	u32Y;						//位置Y
	bool			boIsShow;					//是否显示
}StStringAttr;

typedef struct _tagStString
{
	StStringAttr	stStringAttr;
	char			s8Content[32];
}StString;

//字符叠加属性
typedef struct _tagStOsdAttr
{
	unsigned int	u32CharColor;			//字符颜色1-5-5-5格式
	StStringAttr	stDateTime;				//时间日期
	StStringAttr	stBitRate;				//码率
	StString		stContent1;				//自定义内容1
	StString		stContent2;				//自定义内容2
}StOsdAttr;

//等待串口响应延时类型
typedef enum _tagEmDelayType
{
	_HighDelay,
	_MidDelay,		/* 网板设置相机参数时，使用该模式 */
	_LowDelay,		/* 网板与A板直接通信时使用该模式 */
}EmDelayType;

typedef struct _tagStPtzEcho
{
	bool boIsEcho;						/* 是否有响应码 */
	EmDelayType emDelayType;
	unsigned int u32DataSize;			/* 接收到响应码的长度 */
	unsigned char u8DataBuffer[64];		/* 响应码 */
}StPtzEcho;

//云台控制命令
typedef struct _tagStPtzCtrl
{
	EmPtzCmd		emCmd;
	UoPtzArgs		uoArgs;
	StPtzEcho		stPtzEcho;		/* 增加控制方式 zhangpengfei*/
}StPtzCtrl;

//云台控制命令
typedef struct _tagStIspMenuCtrl
{
	EmIspMenuCmd		emCmd;
}StIspMenuCtrl;

//云台控制参数
typedef struct _tagStPtzAttr
{
	EmPtzProto	emProto;
	unsigned short	u16Addr;
	unsigned int u32BaudRate;
	unsigned int u32DataBits;
	unsigned int u32StopBits;
	char s8Parity;
	char s8FlowCtrl;
	unsigned int u32Reserved;
}StPtzAttr;

//ISP菜单控制参数
typedef struct _tagStIspMenuAttr
{
	unsigned short	u16Addr;
	unsigned int u32BaudRate;
	unsigned int u32Reserved;
}StIspMenuAttr;

//账户信息
typedef struct _tagStAccount
{
	char s8UserName[16];	//用户名
	char s8Password[16];	//密码
	unsigned short u16WebExPort;		//网页端口号
}StAccount;

typedef struct _tagStPrivilAttr
{
	StAccount stSuperAdmin;	//超级管理员，具有更新系统软件权限
	StAccount stAdmin;		//管理员用户，具有改变相机设置权限
	StAccount stUser0;		//普通用户0，具有浏览相机权限
	StAccount stUser1;		//普通用户1，具有浏览相机权限
}StPrivilAttr;

typedef struct _tagStDate
{
	unsigned int u12Year:12;
	unsigned int u4Mon:4;
	unsigned int u5Day:5;
	unsigned int u5Hour:5;
	unsigned int u6Min:6;
	unsigned int u6Sec:6;
}StDate;

typedef struct _tagStSntpAttr
{
	unsigned int	u32SntpEnable;		//网络校时使能
	unsigned int	u32SntpServIP;		//校时服务器IP
	unsigned int	u32SntpServPort;	//校时服务器端口
	int				s32TimeZone;		//时区东区为+，西区为-
}StSntpAttr;

typedef enum _tagEmAlarmSrc
{
	_noalarmsrc = 0,
	_manual,
	_timer,
	_motion,
	_overlap,
	_ioin,
	_netunlink,		//2013.2.20 添加by何松 网络断开报警

	_nosdcard = 0x1000,		//找不到SD卡
	_sdcarderr,				//SD卡不可用
	_sdlackspce,			//空间不足
	_sdReachthreshold,		//到达设定报警阈值

	_videoframeraterr = 0x2000,		//视频帧率错误
}EmAlarmSrc;

/*报警队列中的报警信息结构体*/
typedef struct _tagStAlarmSrcPkg
{
	unsigned int u32Type;
	EmAlarmSrc	emAlarmSrc;
}StAlarmSrcPkg;



typedef struct _tagStPostProc
{
	unsigned int u1File:1;
	unsigned int u1Ftp:1;
	unsigned int u1Email:1;
}StPostProc;

typedef struct _tagStSnapCmd
{
	StPostProc stPostProc;
	EmAlarmSrc emAlarmSrc;
}StSnapCmd;

typedef struct _tagStRecdAttr
{
	unsigned char u8IsPreRecd;			/* 是否打开预录 */
	unsigned int u32PreDuration;		/* 预录时长 单位为秒 */
	unsigned int u32AlarmDuration;		/* 如果为报警事件（IO报警、移动侦测报警、遮挡侦测报警）的话，在一次事件中固定录的时长, 单位为秒 */
}StRecdAttr;

typedef struct _tagStRecdCmd
{
	unsigned char u8IsOpen;
}StRecdCmd;

typedef struct _tagStAuxSnap
{
	unsigned char	u8ShootNums;		//抓拍次数，1--16
}StAuxSnap;
typedef struct _tagStAlarmProc
{
	unsigned int u1Snap:1;	//抓拍
	unsigned int u1Recd:1;	//录像
	unsigned int u1IO:1;	//io输出
	unsigned int u1Ptz:1;	//云台联动
	unsigned int u28Reserve:28;		//保留,不加该成员的话由于gcc编译器的优化使得与vc下得到的结构体大小不同
	StAuxSnap stAuxSnap;	//抓拍辅助参数
}StAlarmProc;

typedef struct _tagStTimeSlice
{
	unsigned short u16StartMin;
	unsigned short u16EndMin;
	unsigned char u8ValidDays;	//0 - 关闭; 1 << n - 星期n;
}StTimeSlice;

typedef struct _tagStTimeSnapAttr
{
	unsigned int	u32Enabled;
	StTimeSlice		stTimeSlice[EVT_TIMESLICES];
	StPostProc		stSnapProc;
	unsigned int	u32SnapInterval;
}StTimeSnapAttr;

typedef struct _tagStTimeRecdAttr
{
	unsigned int	u32Enabled;
	StTimeSlice		stTimeSlice[EVT_TIMESLICES];
}StTimeRecdAttr;

typedef struct _tagStTimeEvt
{
	StAlarmProc		stAlarmProc;
	StPostProc		stPostProc[4];
	StTimeSlice		stTimeSlice[EVT_TIMESLICES];
}StTimeEvt;

typedef struct _tagStTimeConfigAttr
{
	int	s32Index;
	struct _tagStTimeAttr
	{
		unsigned int u32Enabled;
		StTimeSlice	stTimeSlice;
		StCscAttr	stCscAttr;
	}	stTimeAttr;
}StTimeConfigAttr;

//视频侦测参数
typedef struct _tagStVdaAttr
{
	unsigned int	u1Enabled:1;
	unsigned int	u1Reserved:1;
	unsigned int	u32VdaSens;
}StVdaAttr;

//遮挡侦测参数
typedef struct _tagStOdAttr
{
	StVdaAttr	stVdaAttr;
	StTimeEvt	stTimeEvt;
}StOdAttr;

//移动侦测参数
typedef struct _tagStMdAttr
{
	StVdaAttr	stVdaAttr;
	StTimeEvt	stTimeEvt;
	unsigned char	u8MBMask[17][2];
}StMdAttr;

//IO报警输入参数
typedef struct _tagStIOINAttr
{
	unsigned int	u1Enabled:1;
	unsigned int 	u1TriggerMod:1;//常开常闭触发：1为常开触发，0为常闭触发
	StTimeEvt		stTimeEvt;
}StIOINAttr;

//断网录像参数
typedef struct _tagStNetUnlinkAttr
{
	bool u1Enabled;
}StNetUnlinkAttr;

typedef struct _tagStTimeRebootAttr
{
	unsigned int u1Enabled:1;
	struct _tagTimeSlice
	{
		unsigned int u32RebootSeconds;
		unsigned char u8ValidDays;
	}stTimeSlice[EVT_TIMESLICES];
}StTimeRebootAttr;

//smtp服务器信息
typedef struct _tagStSmtpServer
{
	char			s8Server[64];
	unsigned int	u1Enabled:1;
	unsigned int	u2Priority:2;
	unsigned int	u16Port:16;
}StSmtpServer;

//smtp发件人信息
typedef struct _tagStSmtpSender
{
	char	s8UserName[32];		//服务器登录用户名
	char	s8Password[32];		//服务器登录密码
	char	s8SenderName[32];	//发送者姓名
	char	s8SenderMail[32];	//发送者地址
}StSmtpSender;

//smtp收件人信息
typedef struct _tagStSmtpRecver
{
	char	s8RecverName[32];	//收件人姓名
	char	s8RecverMail[32];	//收件人地址
}StSmtpRecver;

//smtp参数
typedef struct _tagStSmtpAttr
{
	StSmtpServer	stServer;
	StSmtpSender	stSender;
	StSmtpRecver	stRecver[3];
}StSmtpAttr;

//ftp服务器参数
typedef struct _tagStFtpServer
{
	char s8HostName[32];		//FTP服务器IP    ip:port 若不写port则默认为25
	char s8UserName[16];		//登录名
	char s8Password[16];		//密码
}StFtpServer;

//ftp参数
typedef struct _tagStFtpAttr
{
	StFtpServer stFtpServer;
}StFtpAttr;

//PTZ联动报警设置参数
typedef struct _tagStPtzAlarmAttr
{
	unsigned int u1Enable:1;
	StPtzCtrl stPtzCtrl;
}StPtzAlarmAttr;

typedef struct _tagStAlarmStatAttr
{
	unsigned int 	u1IOAlarmStat:1;//IO报警是否触发
	StDate			stIOAlarmTime;	//IO报警产生的时间
	unsigned int 	u1ODAlarmStat:1;//遮挡侦测是否触发
	StDate			stODAlarmTime;	//遮挡侦测报警产生的时间
	unsigned int 	u1MDAlarmStat:1;//移动侦测是否触发
	StDate			stMDAlarmTime;	//移动侦测报警产生的时间
}StAlarmStatAttr;

typedef struct _tagStFileOp
{
	EmFileOp emFileOp;
	unsigned int u32FileBytes;
	char s8FileName[128];
}StFileOp;

typedef struct _tagStSpeakerAttr
{
	unsigned int u32Port;
	unsigned int u32DataSize;
}StSpeakerAttr;

typedef struct _tagStPPPoEAttr
{
	unsigned char u8UserName[64];
	unsigned char u8Password[64];
}StPPPoEAttr;

typedef struct _tagStSDCardInfo
{
#ifdef _WIN32
	#if (_MSC_VER >= 1300)
	unsigned long long u64TotalBytes;
	unsigned long long u64UsedBytes;
	unsigned long long u64FreeBytes;
	#else
	unsigned _int64 u64TotalBytes;
	unsigned _int64 u64UsedBytes;
	unsigned _int64 u64FreeBytes;
	#endif
#elif linux
	unsigned long long u64TotalBytes;
	unsigned long long u64UsedBytes;
	unsigned long long u64FreeBytes;
#else
	#error unknown platform	
#endif
}StSDCardInfo;

typedef enum _tagEmCardPolicy
{
	_SdCycleUse,			//循环覆盖
	_SdSpillAlarm			//满报警
}EmCardPolicy;

typedef struct _tagStSDCardAttr
{
	EmCardPolicy emCardPolicy;
	unsigned char u8Threshold;			//报警阈值，百分比
	StSDCardInfo stSDCardInfo;
}StSDCardAttr;

typedef struct _tagStDDNSAttr
{
	bool			boEnabled;
	EmDDNSType		emDDNSType;
	unsigned char	u8UserName[32];
	unsigned char	u8Password[32];
	unsigned char	u8ServerURL[128];
}StDDNSAttr;

typedef enum _tagEmPortType
{
	_WebServer,					//Web服务端口
	_CtrlServer,				//控制服务端口
	_MediaStream,				//媒体流端口
	_RtspServer,				//rtsp服务端口
	_FileTrans,					//文件传输端口
	_OnvifServer,				//Onvif服务端口
	_SpeakerServer,				//对讲中的嵌入式端播放音频服务端口
}EmPortType;

typedef struct _tagStUPnPCfgAttr
{
	bool boEnabled;						//是否打开UPnp
	unsigned short u16WebExPort;		//网页服务映射到的外网端口
}StUPnPCfgAttr;

typedef struct _tagStPortPair
{
	bool boTcp;							//映射的连接类型 TCP/UDP
	bool boRedirStatus;					//映射的状态
	EmPortType emPortType;				//端口服务类型
	unsigned short u16LanPort;
	unsigned short u16WanPort;
}StPortPair;

typedef struct _tagStUPnPAttr
{
	StUPnPCfgAttr stUPnPCfgAttr;
	char s8ExIPAddress[16];
	StPortPair stPortPair[7];
}StUPnPAttr;

typedef struct _tagStWifiAttr
{
	bool	boEnabled;
	EmWifiEncryption emWifiEncryption;
	char	s8SSID[64];
	char	s8Password[64];
	EmIPAddrType	emIPAddrType;		//IP获取方式
	unsigned int	u32LocalIP;			//本地IP
	unsigned char	u8Mac[6];			//MAC地址
	unsigned int	u32Mask;			//子网掩码
	unsigned int	u32Gateway;			//网关IP
	unsigned int	u32DNS[2];			//dns
}StWifiAttr;

typedef struct _tagSt3GAttr
{
	bool boEnabled;
	Em3GType em3GType;
	Em3GStatus em3GStatus;
	unsigned int u32LocalIP;			//本地IP
}St3GAttr;

typedef struct _tagStVOAttr
{
	bool boEnabled;
	bool boPal;
}StVOAttr;

typedef struct _tagStMacAttr
{
	char s8Mac[18];		/* 目标MAC地址，必须为“00：00：00：00：00：00”形式的字符串，以'\0'结尾 */
}StMacAttr;

typedef struct _tagStUnmodAttr
{
	EmViDevType emViDevType;
}StUnmodAttr;

/*
 * 互信互通连接平台参数
 * */
typedef struct
{
    unsigned char    platform_srv_ip[16];    //注册服务器IP
    unsigned short   platform_srv_port;      //注册服务器端口
    unsigned char    platform_devid[32];     //设备ID
    unsigned short   max_conn;               //每一路视频的最大连接数
    unsigned short   link_type;              //链路类型 0-WAN 1-ADSL 2-LAN（内网映射方式）
    unsigned short   msg_port;               //消息端口（平台用来控制设备的端口）
    unsigned short   video_port;             //视频端口（客户用来连接视频的端口）
    unsigned short   audio_call_port;        //语音呼叫端口
    unsigned short   update_image_port;      //更新程序端口
}PLATFORM_HXHT_CONPARAM;    //互信互通连接平台参数

//国标平台
typedef struct
{
	unsigned char			m_AlarmInID[32];
	unsigned char			m_AlarmInName[32];
	unsigned char			m_AlarmInAddress[50];
}GBonline_ALARMIN_T;

typedef struct
{
    unsigned char			m_DeviceID[32];		//设备ID
    unsigned char			m_DevicePassword[32];		//连接 密码(可能需要MD5加密)
    unsigned char			m_DeviceAddress[50];		//设备所在地址
    unsigned char			m_DeviceOwner[50];		//所属
    double					m_DeviceLongitude;            //经度（可选）
    double					m_DeviceLatitude;             //纬度（可选)
    unsigned short			m_DeviceMsgPort;	//SIP端口
    unsigned short			m_DeviceVideoPort;	//视频端口
    unsigned short			m_DeviceAudioPort;	//音频端口
    unsigned short			m_DeviceAlarmPort;	//告警端口
    unsigned char			m_DevicePBK[50];	//本地公钥
    unsigned char			m_DeviceModR[50];	//本地模数

    unsigned char 			m_ServerID[32];
    unsigned char			m_ServerIP[16];		//连接 地址，可能叫做注册地址，或初始化地址
    unsigned short			m_ServerPort;		//连接 端口
    unsigned char			m_ServerPBK[50];	//公钥
    unsigned char			m_ServerModR[50];	//模数

    int             		m_CuralarmIn;		//当前通道号
    GBonline_ALARMIN_T		m_alarmIn[MAX_GPIO_IN_NUM];
}PLATFORM_GBonline_CONPARAM;	// GBonline 上平台需要配置的参数

typedef struct _tagPlatformBasicParam
{
	union
	{
		PLATFORM_GBonline_CONPARAM stGBonlineParam;
		PLATFORM_HXHT_CONPARAM        stHXHTParam;
	}uoPlatformParam;
	unsigned short u16PlatformType;
	//0x01 国标平台   0x02 互信私有平台

}StPlatformBasicParam;

typedef enum _tagEmMediaType
{
	_MEDIA_TYPE_G711_U = 0,
	_MEDIA_TYPE_G711_A,
	_MEDIA_TYPE_MJPEG = 0x1A,
	_MEDIA_TYPE_H264 = 0x62,
}EmMediaType;

typedef enum _tagEmFrameType
{
	_H264_I_FRAME = 0x2,
	_H264_P_FRAME,
	_H264_B_FRAME
}EmFrameType;

typedef struct _tagStVMAttr
{
	EmVideoResolution		emVideoResolution;	//分辨率
	EmFrameType    			emFrameType;   		//具体媒体类型.如u32MediaType为H264时。该字段表示I，P，B帧
}StVMAttr;
typedef struct _tagStAMAttr
{
	unsigned int u32Sample;						//音频采样率
}StAMAttr;

typedef union _tagUoMAttr
{
	StVMAttr stVMAttr;
	StAMAttr stAMAttr;
}UoMediaAttr;

typedef struct _tagStYaanIpcFrameHead
{
	unsigned int    		u32StartCode;		//固定为0X000001B3
	unsigned char			u8Brand[4];			//固定YAAN四个字母
#ifdef _WIN32
	#if (_MSC_VER >= 1300)
	unsigned long long    	u64TimeTick;    	//时间戳,相对时间,微秒为单位
	#else
	unsigned _int64 u64TimeTick;				//时间戳,相对时间,微秒为单位
	#endif
#elif linux
	unsigned long long    	u64TimeTick;    	//时间戳,相对时间,微秒为单位
#else
	#error unknown platform
#endif
	unsigned char			u8SeparativeSign1;	//赋值为0xFF,避免出现H264的分隔符
	unsigned int    		u32GMTTime;     	//绝对时间,自1970年1月1日 00:00:00 开始的秒数,时区按GMT时区计算.
	EmMediaType    			emMediaType;   		//H264，MJPEG，G711A，G722U等
	UoMediaAttr				uoMediaAttr;		//媒体数据参数
	EmAlarmSrc				emAlarmSrc;			//报警信息
	unsigned char			u8SeparativeSign2;	//赋值为0xFF,避免出现H264的分隔符
	unsigned int			u32FrameCount;		//帧序号
	unsigned char			u8SeparativeSign3;	//赋值为0xFF,避免出现H264的分隔符
	unsigned int    		u32MediaSize;   	//媒体数据长度
	unsigned char			u8SeparativeSign4;	//赋值为0xFF,避免出现H264的分隔符
	unsigned int			u32CheckSum;		//校验和
}StYaanIpcFrameHead;

//搜索软件专用结构体，通过组播搜索和修改网络参数
typedef struct _tagStSearchNetAttr
{
        bool             boEthernetEnalbe;    //有线参数使能
        bool             boWifiEnable;        //无线参数使能
        unsigned int     u32OldIP;            //旧IP，当通过搜索软件修改网络属性时才有效。
    	char	         s8DeviceName[32];    //设备名字
        StNetworkAttr    stNetworkAttr;       //有线网络参数，boEthernetEnalbe为真时有效
        StWifiAttr       stWifiAttr;          //无线网络参数，boWifiEnable为真时有效
}StSearchNetAttr;

//远程升级文件包代码长度
typedef enum _tagEmFlashPackageLen
{
	_256B = 0x01,
	_512B,
	_1KB,
	_4KB,
	_16KB,
}EmFlashPackageLen;

//升级目标类型1:水平；2：垂直；3：镜头；
typedef enum _tagEmUpdateType
{
	_HorizontalDriver = 1, //水平
	_VerticalDriver , //垂直
	_CamDriver, //镜头
}EmUpdateType;

//当前升级状态
typedef enum _tagEmLDUpdateStat
{
	_DoNothing,
	_Updating,
	_UpdateErr,
	_UpdateOK,
}EmLDUpdateStat;

typedef enum _tagEmLDUpdateErrType
{
	_NoErr = 0x1,
	_CheckSumErr,		//检验错误
	_ChipIDErr,			//CHIP/ID错误
	_BootIDErr,			//BOOTID错误
	_FlashErr,			//FLASH写数据错误
	_TimeOutErr,		//接收数据超时
	_BitErr,			//误码超过15次

	_UpdatFileErr = 0x100,		//升级文件错误
	_UpdateCommandErr,
	_ChangeBRateErr,
	_HandShakeErr,
	_MemLack,					//内存不足
	_SendDataErr,
	_RecvDataErr,
	_IdentificateRecvData,
}EmLDUpdateErrType;

typedef struct _tagStLDUpdateStat
{
	float u16UpStepPer;				//升级进度百分比
	EmLDUpdateStat emLDUpdateStat;
	EmLDUpdateErrType emLDUpdateErrType;
}StLDUpdateStat;

typedef struct _tagStLDUpdateAttr
{
	EmFlashPackageLen emFlashPackageLen;
	EmUpdateType emUpdateType;
	StLDUpdateStat stLDUpdateStat;
}StLDUpdateAttr;

//错误码定义
typedef enum _emErrCode
{
	/*正确，无错误*/
	_ErrNo			= 0x0000,	//正确无错误

	/*数据包错误*/
	_ErrInvBrand	= 0x1000,	//错误的商标
	_ErrInvAccount,				//错误的账户信息
	_ErrInvCmd,					//命令不存在
	_ErrInvArgs,				//错误的参数
	_ErrInvLen,					//错误的数据长度
	_ErrCheckSum,				//校验和错误

	/*通用错误*/
	_ErrTimeOut		= 0x2000,	//超时
	_ErrPrivil,					//权限错误
	_ErrExec,					//执行错误

	/*设备错误*/
	_ErrInvDev		= 0x3000,	//无效的设备
	_ErrSetDevAttr,				//设置设备参数失败
	_ErrGetDevAttr,				//获取设备参数失败
	_ErrDevInUse,				//设备被占用

	/*文件系统错误*/
	_ErrInvFile		= 0x4000,	//文件不存在
	_ErrReadWrite,				//文件读写错误
	_ErrMemLack,				//内存不足

	/*通讯错误*/
	_ErrBadSock		= 0x5000,	//socket错误
	_ErrBadPeer,				//无法与对方通信
	_ErrSendFail,				//发送失败
	_ErrRecvFail,				//接受失败
}EmErrCode;

//命令码定义
typedef enum _emCmdCode
{
	/*广播查询指令*/
	_CmdSearch				= 0x0001,
	/*保存当前配置*/
	_CmdSaveSetting			= 0x0002,
	/*关闭所有发送线程*/
	_CmdClearQueue			= 0x0003,
	/*查询视频队列长度*/
	_CmdQueryVideoChannels	= 0x0004,
	/*查询音频队列长度*/
	_CmdQueryAudioChannels,
	/*查询视频播放通道信息*/
	_CmdQueryVideoChannelName,
	/*查询音频播放通道信息*/
	_CmdQueryAudioChannelName,
	/*云台控制命令*/
	_CmdPtzCtrl,
	/*ISP菜单控制命令*/
	_CmdIspMenuCtrl,
	/*登录*/
	_CmdLogin,
	/*登出*/
	_CmdLogout,
	/*重启相机*/
	_CmdReset,
	/*抓拍*/
	_CmdSnap,
	/*录像*/
	_CmdRecd,
	/*测试邮件*/
	_CmdMail,
	/*文件操作*/
	_CmdFile,
	/*查询本机信息*/
	_CmdQueryMach,
	/*回复默认设置*/
	_CmdRestore,
	/*播放控制*/
	_CmdPlayCtrl,
	/*菜单控制*/
	_CmdMenuCtrl,
	/*格式化SD卡*/
	_CmdFormatSD,
	/*强制生成I帧*/
	_CmdRequestIDR,
	/*搜索软件专用指令，通过组播修改网络参数*/
	_CmdSetSearchNetAttr,
	/*自动匹配相机类型*/
	_CmdMatchCamDevType,

	/*单播指令*/
	//无响应值指令
	_CmdSetCscAttr		= 0x1000,
	_CmdSetPrivacyAttr,
	_CmdSetVideoAttr,
	_CmdSetAudioAttr,
	_CmdSetPreviewAttr,
	_CmdSetOsdAttr,
	_CmdSetNetworkAttr,
	_CmdSetPtzAttr,
	_CmdSetIspMenuAttr,
	_CmdSetPrivilAttr,
	_CmdSetDate,
	_CmdSetSntpAttr,
	_CmdSetSnapAttr,
	_CmdSetRecdAttr,
	_CmdSetTimeSnapAttr,
	_CmdSetTimeRecdAttr,
	_CmdSetOdAttr,
	_CmdSetMdAttr,
	_CmdSetIOINAttr,
	_CmdSetSmtpAttr,
	_CmdSetSmtpServ,
	_CmdSetSmtpSndr,
	_CmdSetSmtpRcvr,
	_CmdSetCCDAttr,
	_CmdSetFtpAttr,
	_CmdSetPtzAlarmAttr,
	_CmdSetSpeakerAttr,
	_CmdSetPPPoEAttr,
	_CmdSetTimeRebootAttr,
	_CmdSetDDNSAttr,
	_CmdSetUPnPAttr,
	_CmdSetTimeConfigAttr,
	_CmdSetWifiAttr,
	_CmdSet3GAttr,
	_CmdSetVOAttr,
	_CmdSetSDCardAttr,
	_CmdSetMacAttr,
	_CmdSetUnmodAttr,
	_CmdSetDeviceBasicInfo,
	_CmdSetPlatformBasicParam,
	_CmdSetMnVppAttr,
	_CmdSetPreVppAttr,
	_CmdSetLDUpdateAttr,
	/*新增命令*/
	_CmdSetAlarmStatAttr,

	/*保存VPP默认配置*/
	/*保存CSC默认配置*/
    _CmdSaveDefVppAttr,
    _CmdSaveDefCscAttr,


    /*设置断网录像参数*/
    _CmdSetNetUnlinkAttr,


	//有响应值指令
	_CmdGetCscAttr		= 0x2000,
	_CmdGetPrivacyAttr,
	_CmdGetVideoAttr,
	_CmdGetAudioAttr,
	_CmdGetPreviewAttr,
	_CmdGetOsdAttr,
	_CmdGetNetworkAttr,
	_CmdGetPtzAttr,
	_CmdGetIspMenuAttr,
	_CmdGetPrivilAttr,
	_CmdGetDate,
	_CmdGetSntpAttr,
	_CmdGetSnapAttr,
	_CmdGetRecdAttr,
	_CmdGetTimeSnapAttr,
	_CmdGetTimeRecdAttr,
	_CmdGetOdAttr,
	_CmdGetMdAttr,
	_CmdGetIOINAttr,
	_CmdGetSmtpAttr,
	_CmdGetSmtpServ,
	_CmdGetSmtpSndr,
	_CmdGetSmtpRcvr,
	_CmdGetCCDAttr,
	_CmdGetFtpAttr,
	_CmdGetPtzAlarmAttr,
	_CmdGetSpeakerAttr,
	_CmdGetPPPoEAttr,
	_CmdGetTimeRebootAttr,
	_CmdGetDDNSAttr,
	_CmdGetUPnPAttr,
	_CmdGetTimeConfigAttr,
	_CmdGetWifiAttr,
	_CmdGet3GAttr,
	_CmdGetVOAttr,
	_CmdGetSDCardAttr,
	/* 查询网页及ptz的版本 */
	_CmdGetPtzWebInfo,
	_CmdGetUnmodAttr,
	_CmdGetDeviceBasicInfo,
	_CmdGetPlatformBasicParam,
	_CmdGetMnVppAttr,
	_CmdGetPreVppAttr,
	_CmdGetCurRecFileName,
	_CmdGetLastSnapFilePath,
	_CmdGetLDUpdateAttr,
	/*新增命令*/
	_CmdGetAlarmStatAttr,

	/*获得CSC默认配置*/
	_CmdGetDefCscAttr,
	/*获得VPP默认配置*/
	_CmdGetDefVppAttr,
    /*获取断网录像参数*/
    _CmdGetNetUnlinkAttr,


	//保留命令码
	_CmdReserved		= 0x3000,
	_EvtBoot,
	_EvtMdDetected,
	_EvtOdDetected,
	_EvtIODetected,
	_EvtPostMail,
	_EvtUploadFtp,
	_EvtIOOutput,
	_EvtNetUnlink,		//网络断开
}EmCmdCode;

#define MSG_PKG_DATA_LEN	928		/* 与包头组成1024个字节的StMsgPkg */
//#define MSG_PKG_DATA_LEN	256
#define MAX_PRIVACY_CNT		4

typedef struct _stMsgPkg
{
	unsigned char	u8Brand[4];			//商标，永远为"YAAN"四个大写字母
	EmCmdCode		emCmdCode;			//命令码，EmCmdCode类型
	EmErrCode		emErrCode;			//错误码，应答时表明命令执行结果
	int				s32EchRcver;		//接收响应的消息队列id
	unsigned int	u32DataLength;		//数据长度
	StAccount		stAccount;			//登录账户
	unsigned int	u32PeerIP;			//对方IP
	unsigned char	u8Reserved[28];		//保留字段，供将来扩展使用
	union
	{
		char				s8DataBuffer[MSG_PKG_DATA_LEN];
		short				s16DataBuffer[MSG_PKG_DATA_LEN / sizeof(short)];
		int					s32DataBuffer[MSG_PKG_DATA_LEN / sizeof(int)];
#ifdef _WIN32
	#if _MSC_VER >= 1300
		long long			s64DataBuffer[MSG_PKG_DATA_LEN / sizeof(long long)];
	#else
		_int64				s64DataBuffer[MSG_PKG_DATA_LEN / sizeof(_int64)];
	#endif
#elif linux
		long long			s64DataBuffer[MSG_PKG_DATA_LEN / sizeof(long long)];
#else
	#error unknown platform
#endif
		unsigned char		u8DataBuffer[MSG_PKG_DATA_LEN];
		unsigned short		u16DataBuffer[MSG_PKG_DATA_LEN / sizeof(unsigned short)];
		unsigned int		u32DataBuffer[MSG_PKG_DATA_LEN / sizeof(unsigned int)];
#ifdef _WIN32
	#if _MSC_VER >= 1300
		unsigned long long	u64DataBuffer[MSG_PKG_DATA_LEN / sizeof(unsigned long long)];
	#else
		unsigned _int64		u64DataBuffer[MSG_PKG_DATA_LEN / sizeof(unsigned _int64)];
	#endif
#elif linux
		unsigned long long	u64DataBuffer[MSG_PKG_DATA_LEN / sizeof(unsigned long long)];
#else
	#error unknown platform
#endif
		StPlayCtrl			stPlayCtrl;
		StCscAttr			stCscAttr;
		StPrivacyAttr		stPrivacyAttr[4];
		StVideoAttr			stVideoAttr;
		StAudioAttr			stAudioAttr;
		StOsdAttr			stOsdAttr;
		StNetworkAttr		stNetworkAttr;
		StMediaChan			stMediaChan;
		StPtzAttr			stPtzAttr;
		StPtzCtrl			stPtzCtrl;
		StIspMenuAttr		stIspMenuAttr;
		StIspMenuCtrl		stIspMenuCtrl;
		StMenuCtrl			stMenuCtrl;
		StPrivilAttr		stPrivilAttr;
		StDate				stDate;
		StSntpAttr			stSntpAttr;
		StSnapCmd			stSnapCmd;
		StRecdCmd			stRecdCmd;
		StRecdAttr  		stRecdAttr;
		StTimeSnapAttr		stTimeSnapAttr;
		StTimeRecdAttr		stTimeRecdAttr;
		StOdAttr			stOdAttr;
		StMdAttr			stMdAttr;
		StIOINAttr			stIOINAttr;
		StSmtpAttr			stSmtpAttr;
		StSmtpServer		stServer;
		StSmtpSender		stSender;
		StSmtpRecver		stRecver[3];
		StCCDAttr			stCCDAttr;
		StFtpAttr			stFtpAttr;
		StPtzAlarmAttr		stPtzAlarmAttr;
		StFileOp			stFileOp;
		StSpeakerAttr		stSpeakerAttr;
		StMachInfo			stMachInfo;
		StPtzWebInfo		stPtzWebInfo;
		StPPPoEAttr			stPPPoEAttr;
		StSDCardAttr		stSDCardAttr;
		StTimeRebootAttr	stTimeRebootAttr;
		StDDNSAttr			stDDNSAttr;
		StUPnPAttr			stUPnPAttr;
		StTimeConfigAttr	stTimeConfigAttr;
		StWifiAttr			stWifiAttr;
		St3GAttr			st3GAttr;
		StVOAttr			stVOAttr;
		StMacAttr			stMacAttr;
		StUnmodAttr			stUnmodAttr;
		StDeviceBasicInfo	stDeviceBasicInfo;
		StPlatformBasicParam 		stPlatformBasicParam;
		StVppAttr 					stVppAttr;
		StSearchNetAttr                 stSearchNetAttr;
		StLDUpdateAttr				stLDUpdateAttr;
		StAlarmStatAttr				stAlarmStatAttr;
		StNetUnlinkAttr stNetUnlinkAttr;
	}				uoData;		//数据缓冲区
	unsigned int    u32Padding;
	unsigned int	u32CheckSum;		//32位校验和值
}StMsgPkg;

#define GBL_ATTR_VERSION 20130221	//只有在StGblAttr有变化时才更改

typedef struct _tagStFileHeader
{
	unsigned int	u32CheckSum;
	unsigned int	u32FileSizeInBytes;
	unsigned int	u32Version;
	unsigned int	u32Reserved[5];
}StFileHeader;


//全局参数
typedef struct _tagStGblAttr
{
	//文件头
	StFileHeader	stFileHeader;
	//网络参数
	StNetworkAttr	stNetworkAttr;
	//视频流参数
	StVideoAttr		stVideoAttr;
	//预览码流参数
	StVideoAttr		stPreviewAttr;
	//音频流参数
	StAudioAttr		stAudioAttr;
	//画质参数
	StCscAttr		stCscAttr;
	//主编码通道视频前处理参数
	StVppAttr 		stMnChnVencVppAttr;
	//预览编码通道视频前处理参数
	StVppAttr 		stPreChnVencVppAttr;
	//隐私遮挡块参数
	StPrivacyAttr	stPrivacyAttr[MAX_PRIVACY_CNT];
	//字符叠加属性
	StOsdAttr		stOsdAttr;
	//云台控制属性
	StPtzAttr		stPtzAttr;
	//ISP菜单控制属性
	StIspMenuAttr	stIspMenuAttr;
	//sntp校时服务属性
	StSntpAttr		stSntpAttr;
	//抓拍图片Q fact
	unsigned int	u32QFact;
	//定时抓拍属性
	StTimeSnapAttr	stTimeSnapAttr;
	//前端录像属性
	StRecdAttr		stRecdAttr;
	//定时录像属性
	StTimeRecdAttr	stTimeRecdAttr;
	//遮挡侦测属性
	StOdAttr		stOdAttr;
	//移动侦测属性
	StMdAttr		stMdAttr;
	//IO报警输入属性
	StIOINAttr		stIOINAttr;
	//邮件服务器属性
	StSmtpAttr		stSmtpAttr;
	//ftp属性
	StFtpAttr		stFtpAttr;
	//CCD属性
	StCCDAttr		stCCDAttr;
	//报警联动云台属性
	StPtzAlarmAttr	stPtzAlarmAttr;
	//扬声器属性
	StSpeakerAttr	stSpeakerAttr;
	//PPPoE属性
	StPPPoEAttr		stPPPoEAttr;
	//定时重启属性
	StTimeRebootAttr stTimeRebootAttr;
	//ddns属性
	StDDNSAttr		stDDNSAttr;
	//UPnP属性
	StUPnPAttr		stUPnPAttr;
	//定时配置
	StTimeConfigAttr	stTimeConfigAttr[TIME_CONFIG_NUMS];
	//WIFI配置
	StWifiAttr		stWifiAttr;
	//3G配置
	St3GAttr		st3GAttr;
	//VO配置
	StVOAttr		stVOAttr;
	//SD卡配置参数
	StSDCardAttr	stSDCardAttr;
	//出厂后不可更改的超级参数,只通过“一键测试“等公司内部软件修改，恢复出厂设置时不修改此参数
	StUnmodAttr		stUnmodAttr;
	//设备基本信息参数
	StDeviceBasicInfo stDeviceBasicInfo;
	//远程升级参数
	StLDUpdateAttr				stLDUpdateAttr;
	StAlarmStatAttr		stAlarmStatAttr;
	//断网录像参数
	StNetUnlinkAttr     stNetUnlinkAttr;
}StGblAttr;

typedef struct _tagStPlatformCfg
{
	StFileHeader			stFileHeader;
	StPlatformBasicParam	stPlatformBasicParam;	//全局参数
}StPlatformCfg;

/*
 * CheckSum
 * 校验和值生成函数
 * 生成校验和时，将StMsgObj中的u32CheckSum字段置0，调用该函数，将返回值赋给u32CheckSum
 * 例：
 * 	StMsgPkg stMsg = {……};
 * 	stMsg.u32CheckSum = 0;
 * 	stMsg.u32CheckSum = CheckSum(&stMsg, sizeof(stMsg));
 *
 * 校验校验和时，调用该函数，将返回值与StMsgObj中的u32CheckSum比较，相等则校验正确，不等则校验错误
 * 例：
 * 	if(stMsg.u32CheckSum == CheckSum(&stMsg, sizeof(stMsg)))
 * 	{
 * 		printf("校验正确\n");
 * 	}
 * 	else
 * 	{
 * 		printf("校验错误\n");
 * 	}
 */
inline unsigned int CheckSum(void *pData, unsigned int u32Bytes)
{
	unsigned int u32CheckSum = 0;
	unsigned int *pBuffer;

	//防止空指针
	if(NULL == pData)
	{
		return 0;
	}

	pBuffer = (unsigned int *)pData;

	//计算有多少个unsigned int类型
	u32Bytes >>= 2;
	for(unsigned int i = 0; i < u32Bytes; i ++)
	{
		//相加计算校验和
		u32CheckSum += pBuffer[i];
	}

	return (~u32CheckSum) + 1;
}

#endif /* _PROTOCOL_H */
