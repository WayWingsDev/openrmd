//#ifdef __cplusplus 
//extern "C" 
//{ 
//#endif 

#ifndef ALK_MANAGER_H
#define ALK_MANAGER_H

#define MAX_LEN 32U
#define DATETIME_LEN 8U
#define MAX_PATH 256U

#define ALK_SUCCESS						0
#define ALK_ERR_INVALID_ARG		-1
#define ALK_ERR_RTSP_FAILED		-2
#define ALK_ERR_DEV_NOTACTIVE	-3
#define ALK_ERR_DEV_ACTIVE		-4
#define ALK_ERR_STM_NOTACTIVE	-5
#define ALK_ERR_STM_ACTIVE		-6
#define ALK_ERR_DSP_NOTACTIVE	-7
#define ALK_ERR_DSP_ACTIVE		-8
#define ALK_LOGIN_IPWRONG							-101
#define ALK_LOGIN_PROXYIPWRONG				-102
#define ALK_LOGIN_ALLOCDEVWRONG				-103
#define ALK_LOGIN_ALLOCCLNWRONG				-104
#define ALK_LOGIN_CONNECTCLNERR				-105
#define ALK_LOGIN_ALLOCCTLWRONG				-106
#define ALK_LOGIN_CONNECTCTLERR				-107
#define ALK_LOGIN_REQUESTSETUPFAIL		-108
#define ALK_LOGOUT_DOWNLOADING				-111
#define ALK_OS_ALLOCSTREAMFAIL				-121
#define ALK_OS_GETVIDEOMRLFAIL				-122
#define ALK_OS_PLAYVIDEOFAIL					-123
#define ALK_OS_PLAYAUDIOFAIL					-124
#define ALK_OS_REQUESTFAIL						-125
#define ALK_CS_STREAMUSED							-141
#define ALK_RP_ALLOCFAILED						-161
#define ALK_SRP_ALLOCFAILED						-181
#define ALK_SR_RECORDING							-201
#define ALK_SR_OPENAVIFAILED					-202
#define ALK_STR_NOTRECORDING					-221
#define ALK_SNP_VIDEOCONTROLNULL			-241
#define ALK_SNP_SETCONFIGFAILE				-242
#define ALK_IVD_NEWDECODERFAILED			-251
#define ALK_IVD_DECODERINITFAILED			-252
#define ALK_IVD_DECODEFAILED					-253
#define ALK_SPB_NEWDISPLAYFAILED			-261
#define ALK_SPB_NEWCONTROLFAILED			-262
#define ALK_PB_PLAYFAILED							-271
#define ALK_DL_NOTINITIAL							-281
#define ALK_DL_HASDOWNLOAD						-282
#define ALK_DL_GETCONFIGFAILED				-283
#define ALK_DL_INITSOCKFAILED					-284
#define ALK_DL_BINDSOCKFAILED					-285
#define ALK_DL_LISTENSOCKFAILED				-286
#define ALK_DL_NOTALLOWDOWN						-287
#define ALK_CDL_NOFILEDOWN						-301
#define ALK_CDL_CANCELDOWNFAILED			-302

#define SDK_VERSION "2.1.1"

typedef enum {
	REALPLAY_TYPE   =  0, //REAL VIEW
	MULTIPLAY_TYPE  =  1  //PLAYBACK
}REAL_TYPE_E;

typedef enum {
	CONNECT_TYPE_NONE    =0,
	CONNECT_TYPE_UDP     =1,
	CONNECT_TYPE_TCP     =2,
}CONNECT_TYPE_E;

typedef enum {
	NODATA_TYPE = 0,	//NULL
	RGBDATA_TYPE,			//RGB Data
	H264DATA_TYPE,		//H264 Data
	YUVDATA_TYPE,			//YUV Data
	PCMDATA_TYPE,			//PCM Data
	MJPEGDATA_TYPE,
	AACDATA_TYPE,
	G711DATA_TYPE,
	G726DATA_TYPE,
	G29DATA_TYPE
}DATA_TYPE_E;

typedef enum {
	I_FRAME = 0,
	B_FRAME,
	P_FRAME
}FRAME_TYPE_E;

typedef enum {
	NET_CONFIG_TYPE  =  0,
	DATETIME_CONFIG_TYPE  =  1,
	MD_CONFIG_TYPE  =  2,
	OSD_CONFIG_TYPE  =  3,
	PTZ_CONFIG_TYPE  =  4,
	CHANNEL_CONFIG_TYPE  =  5,
	COM_CONFIG_TYPE  =  6
}CONFIG_TYPE_E;

/*
typedef enum eCOMMAND_ID
{
   ID_COMMAND_NONE				= 0,
   ID_COMMAND_REBOOT			= 1,
   ID_COMMAND_SAVESETTINGS		= 2,
   ID_COMMAND_LOADDEFAULT		= 3,
   ID_COMMAND_SEND_KEYFRAME		= 4,
   ID_COMMAND_SWITCH_PTZ_PROTOCAL = 5,
   ID_COMMAND_PTZ_UP			= 10,
   ID_COMMAND_PTZ_DOWN          = 11,
   ID_COMMAND_PTZ_LEFT          = 12,
   ID_COMMAND_PTZ_RIGHT         = 13,
   ID_COMMAND_PTZ_IRIS_OPEN     = 14,
   ID_COMMAND_PTZ_IRIS_CLOSE    = 15,
   ID_COMMAND_PTZ_ZOOM_IN       = 16,
   ID_COMMAND_PTZ_ZOOM_OUT      = 17,
   ID_COMMAND_PTZ_FOCUS_NEAR    = 18,
   ID_COMMAND_PTZ_FOCUS_FAR     = 19,
   ID_COMMAND_PTZ_AUTOPAN       = 20,
   ID_COMMAND_PTZ_BRUSH         = 21,
   ID_COMMAND_PTZ_PRESET        = 22,
   ID_COMMAND_PTZ_RECALL        = 23,
   ID_COMMAND_PTZ_CRUISE        = 24,
   ID_COMMAND_PTZ_CLEARPRESET   = 25,
   ID_COMMAND_PTZ_LEFTUP        = 26,
   ID_COMMAND_PTZ_LEFTDOWN      = 27,
   ID_COMMAND_PTZ_RIGHTUP       = 28,
   ID_COMMAND_PTZ_RIGHTDOWN		= 29,
   ID_COMMAND_PTZ_STOP			= 30,
   ID_COMMAND_PTZ_SPEED		    = 31,
   ID_COMMAND_PTZ_ADDRESS		= 32,
   ID_COMMAND_PTZ_AUTOPAN_SPEED0 = 33,
   ID_COMMAND_PTZ_AUTOPAN_LIMIT0 = 34,
   ID_COMMAND_PTZ_AUTOPAN_START0 = 35,
   ID_COMMAND_SERIALPORT		= 40,
   ID_COMMAND_VIDEO_OUTPUT		= 41,
   ID_COMMAND_OSD_INITIALIZE	= 50,
   ID_COMMAND_OSD_SHOW_LOGO		= 51,
   ID_COMMAND_OSD_SHOW_TIME		= 52,
   ID_COMMAND_OSD_SHOW_TEXT		= 53,
   ID_COMMAND_OSD_HIDE_LOGO		= 54,
   ID_COMMAND_OSD_HIDE_TIME		= 55,
   ID_COMMAND_OSD_HIDE_TEXT		= 56,
   ID_COMMAND_MD_INITIALIZE		= 60,
   ID_COMMAND_MD_ENABLE			= 61,
   ID_COMMAND_MD_DISABLE		= 62,
   ID_COMMAND_SNAP				= 63,
   ID_COMMAND_PTZ_COMPOSE		= 64,
   ID_COMMAND_PTZ_START_RECORD_PATTERN0 = 70,
   ID_COMMAND_PTZ_START_RECORD_PATTERN1 = 71,
   ID_COMMAND_PTZ_START_RECORD_PATTERN2 = 72,
   ID_COMMAND_PTZ_START_RECORD_PATTERN3 = 73,
   ID_COMMAND_PTZ_RUN_PATTERN   = 74,
   ID_COMMAND_PTZ_PRESET_DELETE = 75,
   ID_COMMAND_PTZ_PRESET_ADD_TO_CRUISE0 = 76,
   ID_COMMAND_PTZ_PRESET_ADD_TO_CRUISE1 = 77,
   ID_COMMAND_PTZ_PRESET_ADD_TO_CRUISE2 = 78,
   ID_COMMAND_PTZ_PRESET_ADD_TO_CRUISE3 = 79,
   ID_COMMAND_PTZ_PRESET_DEL_FROM_CRUISE0 = 80,
   ID_COMMAND_PTZ_PRESET_DEL_FROM_CRUISE1 = 81,
   ID_COMMAND_PTZ_PRESET_DEL_FROM_CRUISE2 = 82,
   ID_COMMAND_PTZ_PRESET_DEL_FROM_CRUISE3 = 83,
   ID_COMMAND_PTZ_CRUISE0_DWELL_TIME = 84,
   ID_COMMAND_PTZ_CRUISE1_DWELL_TIME = 85,
   ID_COMMAND_PTZ_CRUISE2_DWELL_TIME = 86,
   ID_COMMAND_PTZ_CRUISE3_DWELL_TIME = 87,
   ID_COMMAND_NOTIFY_START      = 99,	
   ID_COMMAND_RMFILE			= 100,
   ID_COMMAND_ADDFILE			= 101,
   ID_COMMAND_IOALARMABLE		= 102,
   ID_COMMAND_BROWSE_SEREVERLOG		= 103,
   ID_COMMAND_SAVE_ALLSERVERCONFIG		= 104,
   ID_COMMAND_VIDEO_RECCHN_ENABLE		= 105,
   ID_COMMAND_VIDEO_RECCHN_DISABLE		= 106,   
   ID_COMMAND_PTZ_AUTOPAN_SPEED1	=107,
   ID_COMMAND_PTZ_AUTOPAN_LIMIT1	=108,
   ID_COMMAND_PTZ_AUTOPAN_START1	=109,
   ID_COMMAND_PTZ_AUTOPAN_SPEED2	=110,
   ID_COMMAND_PTZ_AUTOPAN_LIMIT2	=111,
   ID_COMMAND_PTZ_AUTOPAN_START2	=112,
   ID_COMMAND_PTZ_AUTOPAN_SPEED3	=113,
   ID_COMMAND_PTZ_AUTOPAN_LIMIT3	=114,
   ID_COMMAND_PTZ_AUTOPAN_START3	=115,
   ID_COMMAND_PTZ_AUX_CONTROL_OPEN  =116,
   ID_COMMAND_PTZ_AUX_CONTROL_CLOSE =117,
   ID_COMMAND_FACTORY_DEFAULT       = 118,
};
*/

typedef enum {
	SCENEMODE_OFF	= 0,
	SCENEMODE_NA	= 1,
	SCENEMODE_NB	= 2,
	SCENEMODE_AUTO	= 3,
	SCENEMODE_WDR	= 4,
	SCENEMODE_HCT	= 5,
}CAMERA_PARAM_SCENEMODE;

#define  CAMERA_PARAM_HUE_MIN	-2
#define  CAMERA_PARAM_HUE_MAX	2

typedef enum {
	CHROMA_HIGH = 0,
	CHROMA_MIDDLE = 1,
	CHROMA_LOW = 2,
}CAMERA_PARAM_CHROMA;

typedef enum {
	NOISEREDUCTION_HIGH		= 0,
	NOISEREDUCTION_MIDDLE	= 1,
	NOISEREDUCTION_LOW		= 2,
	NOISEREDUCTION_OFF		= 3,
}CAMERA_PARAM_NOISEREDUCTION;

typedef enum {
	SHARPNESS_HIGH		= 0, 
	SHARPNESS_MIDDLE	= 1,
	SHARPNESS_LOW		= 2,
}CAMERA_PARAM_SHARPNESS;

typedef enum {
	NEARLIMITSETUP_3DOT7CM	= 0,
	NEARLIMITSETUP_6DOT3CM	= 1,
	NEARLIMITSETUP_13CM		= 2,
	NEARLIMITSETUP_20CM		= 3,
	NEARLIMITSETUP_50CM		= 4,
	NEARLIMITSETUP_70CM		= 5,
	NEARLIMITSETUP_90CM		= 6,
	NEARLIMITSETUP_1M		= 7,
	NEARLIMITSETUP_2M		= 8,
	NEARLIMITSETUP_4DOT5M	= 9,
}CAMERA_PARAM_SHARPNESS_NEARLIMITSETUP;

typedef enum {
	FOCUSMODE_AUTO		= 0,
	FOCUSMODE_MANUAL	= 1,
}CAMERA_PARAM_SHARPNESS_FOCUSMODE;

typedef enum {
	MANUALFOCUS_NEAR	= 0,
	MANUALFOCUS_FAR		= 1,
	MANUALFOCUS_STOP	= 2,
}CAMERA_PARAM_SHARPNESS_MANUALFOCUS;

typedef enum {
	EXPOSUREMODESETUP_AUTO		= 0,
	EXPOSUREMODESETUP_MANUAL	= 1,
	EXPOSUREMODESETUP_APERTURE_PRIORITY	= 2,
	EXPOSUREMODESETUP_SHUTTER_PRIORITY	= 3,
}CAMERA_PARAM_SHARPNESS_EXPOSUREMODESETUP;

typedef enum {
	APERTURESETUP_F1DOT8	= 0, 
	APERTURESETUP_F2DOT0	= 1,
	APERTURESETUP_F2DOT8	= 2, 
	APERTURESETUP_F4DOT0	= 3, 
	APERTURESETUP_F5DOT6	= 4,
	APERTURESETUP_F8DOT0	= 5,
	APERTURESETUP_F11		= 6
}CAMERA_PARAM_SHARPNESS_APERTURESETUP;

typedef enum {
	SHUTTERSPEEDSETUP_1DIV5		= 0,
	SHUTTERSPEEDSETUP_1DIV6		= 1,
	SHUTTERSPEEDSETUP_1DIV8		= 2,
	SHUTTERSPEEDSETUP_1DIV10	= 3,
	SHUTTERSPEEDSETUP_1DIV12	= 4,
	SHUTTERSPEEDSETUP_1DIV15	= 5,
	SHUTTERSPEEDSETUP_1DIV24	= 6,
	SHUTTERSPEEDSETUP_1DIV25	= 7,
	SHUTTERSPEEDSETUP_1DIV30	= 8,
	SHUTTERSPEEDSETUP_1DIV48	= 9,
	SHUTTERSPEEDSETUP_1DIV50	= 10,
	SHUTTERSPEEDSETUP_1DIV60	= 11,
	SHUTTERSPEEDSETUP_1DIV100	= 12,
	SHUTTERSPEEDSETUP_1DIV125	= 13,
	SHUTTERSPEEDSETUP_1DIV250	= 14,
	SHUTTERSPEEDSETUP_1DIV500	= 15,
	SHUTTERSPEEDSETUP_1DIV1000	= 16,
	SHUTTERSPEEDSETUP_1DIV2000	=17,
	SHUTTERSPEEDSETUP_1DIV4000	=18,
}CAMERA_PARAM_SHARPNESS_SHUTTERSPEEDSETUP;

typedef enum {
	DOWNEVENTTYPE_GETCONFIG = 0,
	DOWNEVENTTYPE_GETFILESIZE = 1,
	DOWNEVENTTYPE_BEGIN = 2,
	DOWNEVENTTYPE_INPROGRESS = 3,
	DOWNEVENTTYPE_FINISH = 4,
}DOWNLOAD_EVENT_TYPE;

typedef enum {
	DOWNEVENTERR_NOERROR = 0,
	DOWNEVENTERR_INITFAILED = 1,
	DOWNEVENTERR_REQUESTFAILED = 2,
	DOWNEVENTERR_ACCEPTFAILED = 3,
	DOWNEVENTERR_CREATETEMPFAILED = 4,
	DOWNEVENTERR_SOCKETCLOSE = 5,
	DOWNEVENTERR_SOCKETERROR = 6,
}DOWNLOAD_EVENT_ERROR;

typedef struct 
{
	DOWNLOAD_EVENT_TYPE nType;		// Event Type
	long lDowned;
	long lFileSize;
	DOWNLOAD_EVENT_ERROR nError;	// 
} DOWNLOAD_EVENTARG;

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

typedef void (*pStreamCallback)     (int sock, short ev, int streamid,void *arg);
typedef void (*fRealDataCallBack)   (DATA_TYPE_E eDataType, FRAME_TYPE_E eFrameType,unsigned char *pBuffer,unsigned long dwBufsize,unsigned long dwUser);
typedef void (*fDisplayDataCallBack)(long lStreamID, DATA_TYPE_E eDataType,long nWidth,long nHeight, unsigned char*pBuf,unsigned long dwUser);
typedef void (*fMJPEGCallBack)      (long lStreamID, DATA_TYPE_E eDataType, unsigned char *pBuf, unsigned long nBufLen, unsigned long dwUser);
typedef void (*fAudioCallBack)		(long lStreamID, DATA_TYPE_E eDataType, unsigned char *pBuf, unsigned long nBufLen, unsigned long dwUser);
typedef void (*fAudioCallBackDecode)(long lStreamID, DATA_TYPE_E eDataType, unsigned char *pBuf, unsigned long nBufLen, unsigned long dwUser);

typedef void (*fStreamActiveCallBack)(long lStreamID,int active, int canconnect, unsigned long dwUser);
typedef void (*fRecordCallBack)(long lStreamID, long writed, int success, void * reserved);
typedef void (*fDownloadCallBack)(long lDeviceID, DOWNLOAD_EVENTARG *pArg);

struct DOWNLOAD_CMD
{
	char szFileName[MAX_PATH];
	int nOption;
	fDownloadCallBack pNotify;
};


struct NET_DOWN_PARAM
{
	int nEnable;
	int nLinkOutputEnable;
	int nLinkOutputMode;
	int nLinkOutputKeepTime;
	int nLinkOutputEmailEnable;
	int nLinkLocalRecordEnable;
	int nLinkLocalRecordStreamNumber;
	int nLinkLocalRecordFramerate;
	int nLinkLocalRecordKeepTime;
	int nLinkLocalRecordFtpEnable;
	int nLinkLocalRecordEmailEnable;
	int nLinkLocalSnapEnable;
	int nLinkLocalSnapJpegQuantity;
	int nLinkLocalSnapIntervalTime;
	int nLinkLocalSnapJpegQuality;
	int nLinkLocalSnapFtpEnable;
	int nLinkLocalSnapEmailEnable;
};

struct PLAY_OPTION
{
	int nDecodeList;
	int nPlayList;
};

struct SNAP_CONFIG
{	
	char szFile[MAX_PATH];
	int nCount;
};

struct DVS_INFO
{
	char cSerialNumber[MAX_LEN];
	char cDeviceName[MAX_LEN];
	int nDVSType;
	int nChannelNum;
	int nComNum;
	int nAlarmInNum;
	int nAlarmOutNum;
};

struct PTZ_CONFIG
{
	unsigned int ProtocolType;
	unsigned int DomeID;
};


typedef struct 
{
	int nFunction;
	int nMode;
	int nPara1;
	int nPara2;
}PTMODULE_CONFIG;

struct WATCHDOG_CONFIG
{
	int nEanble;
};


typedef struct MULTI_VIDEO_CHANNEL
{
	int nD1;						// D1.	  0-OFF, 1-ON
	int nCIF;						// CIF.	  0-OFF, 1-ON
	int nMJPEG;					// MJPEG. 0-OFF, 1-ON	
	int SubD1;
}* PMUTIL_VIDEO_CHANNEL;

typedef struct HOME_FUNCTION
{
	int HomeFunction;
	int HomeFunctionMode;
	int HomeFunctionIndex;
	int HomeFunctionIdle;
}*PHOME_FUNCTION;

typedef struct VIDEO_ATTRIBUTE
{
	int ChannelIndex;	//1			1 to 5 最多支持5码流,分别代表HD,D1,CIF,SubD1 MJPG
	int ResolutionX;	//720, 576	176, 144 | 352, 288 | 704, 576 | 720, 576 | 1280, 720 | 1920, 1080
	int ResolutionY;
	int EncodeBitRate;	//2000		384 to 16384  k
	int FrameRate;			//25		1 to 60
	int GOP;						//50		1 to 200
	int gopStructure;		//0 1 2 3   IP IBP IBBP IBBRBP
	int EncBitRateControl;//0 1		CBR,VBR
	int EncBitRateMaxQP;	//25		1 - 50
	int EncBitRateMinQP;	//25		1 - 50
}*PVIDEO_ATTRIBUTE;

struct AUDIO_ATTRIBUTE
{
	int nEnable;						// 0-OFF, 1-ON
	int nSampleRate;				// 8000 --8000，32000，48000 
	int nEncodeType;				// 0-AAC, 1-G711, 2-G729 
	int nBitRate;						// 64000 
	int nIn;								// 0-OFF, 1-ON
	int nInVolume;					//: 24 -- 0-31 
	int nOut;								// 0-OFF, 1-ON
	int nOutVolume;					// 16 
};

struct HDMI_CONFIG
{
	int nEnable;						// 0-OFF, 1-ON	
};

struct DATETIME_CONFIG
{
	int nNtpMode;									// NTP模式 0, 1 0 OFF 1 ON
	char szNtpServer[MAX_LEN];		// NTP服务器IP, 192.168.0.200
	int nDstMode;									// 时间模式1 --1-24
	char szDstTime[MAX_LEN];			// 时间 2009-10-09 11:50:18
};

struct SERIALPORT_CONFIG
{
	int nProtocol;		// 协议0:SAE,1:PELCO_P, 2:PELCO_D
	int nDomeId;			// 摄像机ID 1 to 254
	int nBaudRate;		// 波特率 2400, 4800,9600, 19200
	int nCharLen;			// 字符长 7,8
	int nParityBit;		// 奇偶位0:none,1:odd,2:even
	int nStopBit;			// 停止位 1,2
};

struct FONT_COLOR
{
	char Font[MAX_LEN];
	unsigned int uTextColor;
	unsigned int uBgColor;
};

#define MAX_OSD_TITLE_LEN 24U
struct OSD_REGION
{
	char title[MAX_OSD_TITLE_LEN]; // 标题字符
	int  titledisplay;	 					// 标题是否显示1为显示 0为不显示
	char titlecolor[MAX_LEN]; 		// 标题颜色(White, Black, Gray)
	int  titleh;		 // 标题水平位置0-100
	int  titlev;		 // 标题垂直位置0-100
	int  timedisplay;	 // 时间是否显示(0不显示1显示)
	int  timeformat;	 //0,1,2分别为YYMMDD、DDMMYY、MMDDYY
	int  timemode;		 //1,2分别为分1行显示2行显示
	char timecolor[MAX_LEN]; // 时间颜色(White, Black, Gray)
	int  timeh;		 // 时间水平位置0-100
	int  timev;		 // 时间垂直位置0-100
};

struct PPPOE_CONFIG
{
	int nEnable;							// Enable. 0-OFF, 1-ON
	char szUser[MAX_LEN];			// User name
	char szPassword[MAX_LEN];	// Password
};

struct FTP_CONFIG
{
	int nClientMode;					// FTP client mode. if 1(ON) mean client upload file to ftp server, otherwise not.
	char szServerIP[MAX_LEN];	// FTP server. e.g. 192.168.1.1 
	int nServerPort;					// FTP port, e.g. 21 
	char szUsername[MAX_LEN];	// FTP user name. 
	char szPassword[MAX_LEN];	// FTP user password. 
	char szFilePath[MAX_PATH];	// Upload file path.
	char szServerIP2[MAX_LEN];	// FTP server 2. e.g. 192.168.1.1 
	int nServerPort2;						// FTP port 2, e.g. 21 
	char szUsername2[MAX_LEN];	// FTP user name 2.
	char szPassword2[MAX_LEN];	// FTP user password 2.
	char szFilePath2[MAX_PATH];	// Upload file path 2.
};

struct WIFI_CONFIG
{
	int nEnable;					// ON, OFF无线网开关
	char szIP[MAX_LEN];
	char szSubmask[MAX_LEN];
	char szGateway[MAX_LEN];
	char szOperationMode[MAX_LEN];            //模式
	char szChannelNumber[MAX_LEN];            //频道
	char szSSID[MAX_LEN];							//SSID
	char szPassword[MAX_LEN];
};

struct SMTP_CONFIG
{
	char szServerIP[MAX_LEN];
	int nServerPort;
	int nAuth;
	char szUsername[MAX_LEN];
	char szPassword[MAX_LEN];
	char szFromEmail[MAX_LEN];
};

#define MAX_SMTP_SUBJECT 256
struct SMTP_NOTIFY
{
	int nIndex;
	char szToEmail[MAX_LEN];
	char szCcEmail[MAX_LEN];
	char szSubject[MAX_SMTP_SUBJECT];
};

struct FTP_SINGLEFILE
{
	char szFileName[MAX_PATH];
	int nFileOption;					// 0-Delete 1-Remain
};

struct FTP_BATCHFILES
{
	int nFileType;				// 0-AVI, 1-JPEG
	int nMode;						// 0-Normal, 1-Alarm 
	int nAlarmType;				// 0-All,1- IO,2-MD 
	char szStartTime[MAX_LEN];	// Start time: 20091210_13:18:26
	char szEndTime[MAX_LEN];		// End time:  20091210_15:18:26
	int nFileOption;						// 0-Delete 1-Remain
};

struct FTP_DELETEFILE
{	
	char szFileName[MAX_PATH];
};

struct QUERY_FILE
{
	int nFileType;						// 0- AVI, 1-JPEG 
	int nMode;								// 0-Normal, 1-Alarm 
	int nAlarmType;						// 0-- All, 1-IO, 2-MD 
	char szStartTime[MAX_LEN];// Start time: 20091210_131826 
	char szEndTime[MAX_LEN];	// End time: 20091210_151826
};

struct REMOTE_SNAP
{
	char szJpegFileName[MAX_PATH];	// Cam001_20100105_180000.jpg.
	int nJpegNum;						//1-3 抓拍张数; 
	int nJpegQuality;				//1-100 
};

struct ALARM_LINK_RECORD
{
	int nEnable;							// 0-OFF, 1-ON
	int nNumber;							// 联动录像的视频流编号, 1 to 3 
	int nFrameRate;						// 帧率 
	int nKeepTime;						//5 to 300,单位为秒; 
};

struct ALARM_LINK_SNAP
{
	int nEnable;								// 0-OFF, 1-ON
	int nQuality;								// 质量, 1 to 100 
};

struct DDNS_CONFIG
{
	int nEnable;							// DDNS enable. 0-OFF, 1-ON
	char szServer[MAX_LEN];		// DDNS server name.
	char szDomain[MAX_LEN];		// DDNS domain.
	char szUsername[MAX_LEN];	// DDNS user name.
	char szPassword[MAX_LEN];	// DDNS user password.
};

struct NET_CONFIG
{
	char szIP[MAX_LEN];					// IP address
	char szNetMask[MAX_LEN];		// IP net mask
  char szGateway[MAX_LEN];		// IP Gateway
	int nDHCPMode;							// Enable DHCP Mode. 0-OFF, 1-ON
	char szMainDNS[MAX_LEN];		// Main DNS. e.g 202.96.134.133
	char szSubDNS[MAX_LEN];			// Sub DNS. e.g 210.21.196.6 
};

struct WLAN_CONFIG
{
	int  nEnable;             //无线使能
	char szSSID[MAX_LEN];			//SSID
	int  nLinkMode;						//连接模式；0：auto，1：adhoc，2：Infrastructure
	int  nEncryption;					//加密; 0：off，2：WEP64bit，3：WEP128bit
	int  nKeyType;						//0：Hex，1：ASCII
	int  nKeyID;             	//序号
	char szKeys[4][MAX_LEN];	//四组密码 
	int  nKeyFlag;						//加密类型
	char reserved[MAX_LEN];		//保留
};

struct VERSION_INFO
{
	char szHardWareVersion[MAX_LEN];		// 硬件版本信息
	char szFirmWareVersion[MAX_PATH];		// 软件版本信息
	char szCamModule[MAX_LEN];					// 摄像机型号
};

struct MD_CONFIG
{
	int nEnable;					// 0-OFF 1-ON
	int nSensitivity;			//移动侦测灵敏度,1 to 100
	int nAreaX;						//移动侦测区域水平位置
	int nAreaY;						//移动侦测区域垂直位置
	int nAreaWidth;				//移动侦测区域宽度
	int nAreaHeight;			//移动侦测区域高度
};

struct MD_LINK_CONFIG
{
	int nEnable;                //ON, OFF
	char szScheduleStartTime[MAX_LEN];
	char szScheduleEndTime[MAX_LEN];
	char szScheduleStartTime2[MAX_LEN];
	char szScheduleEndTime2[MAX_LEN];
	int nLinkOutputEnable;            //ON, OFF联动输出
	int nLinkOutputMode;        			// N.O, N.C联动输出方式
	int nLinkOutputKeepTime;        	// 1 to 24*60*60,单位为秒联动输出持续时间
	int nLinkOutputEmailEnable;   		//发送email
	int nLinkLocalRecordEnable;    		// ON, OFF联动录像
	int nLinkLocalRecordStreamNumber;    // 联动录像的视频流编号, 1 to 3
	int nLinkLocalRecordFramerate;       // 帧率
	int nLinkLocalRecordKeepTime;        // 5 to 300,单位为秒;                
	int nLinkLocalRecordFtpEnable;       //录像Ftp上传使能
	int nLinkLocalRecordEmailEnable;     //发送email
	int nLinkLocalSnapEnable;            // ON, OFF本地抓拍
	int nLinkLocalSnapJpegQuantity;      // 1-5本地抓拍数量
	int nLinkLocalSnapIntervalTime;      // 1-6000本地抓拍间隔时间
	int nLinkLocalSnapJpegQuality;       // 1 to 100本地抓拍质量
	int nLinkLocalSnapFtpEnable;         //录像Ftp上传使能
	int nLinkLocalSnapEmailEnable;       //发送email
};

struct DOWNLOAD_CONFIG
{
	int nEnable;				// 是否有效
	int nPort;					// 端口
};

struct ALARM_CONFIG
{
	int nEnable;											// 0-OFF,1-ON
	int nMode;												//N.O,N.C报警输入方式
	char szStartTime[MAX_LEN];				// 08:00:00
	char szEndTime[MAX_LEN];					// 18:30:00
	char szStartTime2[MAX_LEN];				// 18:00:00
	char szEndTime2[MAX_LEN];					// 20:30:00
	int nLinkOutputEnable;						// ON, OFF联动输出
	int nLinkOutputMode;							// N.O, N.C联动输出方式
	int nLinkOutputKeepTime;					// 1 to 24*60*60,单位为秒联动输出持续时间
	int nLinkOutputEmailEnable;				// 是否发送email
	int nLinkLocalRecordEnable;				// ON, OFF联动录像
	int nLinkLocalRecordStreamNumber;	// 联动录像的视频流编号, 1 to 3
	int nLinkLocalRecordFramerate;		// 帧率
	int nLinkLocalRecordKeepTime;			// 5 to 300,单位为秒;
	int nLinkLocalRecordFtpEnable;		// 录像Ftp上传使能
	int nLinkLocalRecordEmailEnable;	// 发送email
	int nLinkLocalSnapEnable;					// ON, OFF本地抓拍
	int nLinkLocalSnapJpegQuantity;		// 1-5本地抓拍数量
	int nLinkLocalSnapIntervalTime;		// 1-6000本地抓拍间隔时间
	int nLinkLocalSnapJpegQuality;		// 1 to 100本地抓拍质量
	int nLinkLocalSnapFtpEnable;			// 抓拍Ftp上传使能
	int nLinkLocalSnapEmailEnable;		// 是否发送抓拍邮件  
};

struct ALARMIN_CONFIG
{
	int nInputMode;				// 输入模式 0:N.O, 1:N.C
};

struct ALARMOUT_CONFIG
{	
	int nMode;						// 输出模式 N.O, N.C
};

struct ALARMOUT_ENABLE
{	
	int nEnable;					// 是否启用 0-OFF, 1-ON
};

struct CAMERA_PARAM
{
	int nBacklightCorrection;	//背光纠正1:ON, 0:OFF
	int nVerticalFlip;				//垂直翻转1:ON, 0:OFF
	int nHorizontalFlip;			//水平翻转1:ON, 0:OFF
	int nMotionImagestabilizer;	//动态图像稳定1:ON, 0:OFF
	int nFlickerReduction;			//颤动缩减1:ON, 0:OFF
	int nAutoSlowShutter;				//自动慢速遮光1:ON, 0:OFF
	int nSceneMode;							//场景模式0:OFF, 1:NA, 2:NB, 3:AUTO, 4:WDR, 5:HCT
	int nHue;										//色调-2~2
	int nChroma;								//色度 0:High, 1:Middle, 2:Low
	int nNoiseReduction;				//噪点缩减 0:High, 1:Middle, 2:Low, 3:OFF
	int nSharpness;							//锐利 0:High, 1:Middle, 2:Low
	int nNearLimitSetup;
	int nFocusMode;							//聚焦模式 0:Auto, 1:Manual
	int nManualFocus;						//手动聚焦 0:Near, 1:Far, 2:Stop
	int nExposureModeSetup;
	int nApertureSetup;
	int nShutterSpeedSetup;
};

struct STORAGE_DEVICE_CONTROL
{
	int nControl;			// Control, 0-Format, 1-Plug-In, 2-Un-Plug
};

struct STORAGE_DEVICE_INFO
{
	char szStatus[MAX_LEN];					// Storage status
	char szDescription[MAX_PATH];		// Storage description
	long lCapability;								// Storage capability in MB
	long lFree;											// Storage free in MB
};

struct STORAGE_DEVICE_MODE
{
	int nEnable;										// Enable storage, 0-Disable, 1-Enable
	int nSequenceMode;							// Storage sequence mode, 0-recycle, 1-once
};

struct LOCAL_RECORD_PARAM
{	
	int nEnable;										// Whether record. 0-Disable, 1-Enable
	char szStartTime[MAX_LEN];			// Time range start. e.g 08:00:00
	char szEndTime[MAX_LEN];				// Time range end. e.g 18:30:00
	int nEnable2;										// Whether record 2. 0-Disable, 1-Enable
	char szStartTime2[MAX_LEN];			// Time range start 2. e.g 08:00:00
	char szEndTime2[MAX_LEN];				// Time range end 2. e.g 18:30:00
	int nEmailEnable;								// EMail Enable
};

struct LOCAL_SCHEDULE_SNAP_PARAM
{	
	int nEnable;										//0-OFF, 1-ON
	char szStartTime[MAX_LEN];			//时间段1开始录像时间
	char szEndTime[MAX_LEN];				//时间段1停止录像时间
	int nEnable2;										//0-OFF, 1-ON
	char szStartTime2[MAX_LEN];			//时间段2开始录像时间
	char szEndTime2[MAX_LEN];				//时间段2停止录像时间
	int nInterval;									// 抓拍间隔(秒)1-6000本地抓拍间隔时间
	int nQuality;										// 1 to 100本地抓拍质量
	int nFtpEnable;									//录像Ftp上传使能
	int nEmailEnable;								//发送email
};

struct NETFAIL_RECORD_PARAM
{
	int nEnable;											//ON, OFF
	int nLinkOutputEnable;						//ON, OFF联动输出
	int nLinkOutputMode;							// N.O, N.C联动输出方式
	int nLinkOutputKeepTime;					// 1 to 24*60*60,单位为秒联动输出持续时间
	int nLinkOutputEmailEnable;				//发送email
	int nLinkLocalRecordEnable;				// ON, OFF联动录像
	int nLinkLocalRecordStreamNumber; // 联动录像的视频流编号, 1 to 3
	int nLinkLocalRecordFramerate;		// 帧率
	int nLinkLocalRecordKeepTime;			// 5 to 300,单位为秒;                
	int nLinkLocalRecordFtpEnable;    //录像Ftp上传使能
	int nLinkLocalRecordEmailEnable;  //发送email
	int nLinkLocalSnapEnable;		  // ON, OFF本地抓拍
	int nLinkLocalSnapJpegQuantity;   // 1-5本地抓拍数量
	int nLinkLocalSnapIntervalTime;   // 1-6000本地抓拍间隔时间
	int nLinkLocalSnapJpegQuality;    // 1 to 100本地抓拍质量
	int nLinkLocalSnapFtpEnable;	  //录像Ftp上传使能
	int nLinkLocalSnapEmailEnable;    //发送email
};

struct REMOTE_RECORD_CONFIG
{
	char szRemoteRecordFileName[MAX_PATH];// Remote record file name. e.g. Cam001_20100105_180000.avi  -- avi文件名.
	int nRemoteRecordCmd;									// Remote record cmd.: 0(OFF) Stop record, 1(ON) start record.
};

struct VIDEO_FLIP
{	
	int nVerticalFlip;			//垂直翻转1:ON, 0:OFF
	int nHorizontalFlip;		//水平翻转1:ON, 0:OFF	
};

struct ALARM_SERVICE_CONFIG
{	
	int nAlarmService;					// Alarm service enable. 0-OFF, 1-ON
	char szIPAddr[MAX_LEN];			    // Alarm service ip address. e.g. 192.168.0.105
	int nPort;							// Alarm service port. e.g. 10000
	int nKeepaliveTimer;				// Keep alive time.
};


//1 base function
long Alk_SDKInit(void);
long Alk_SDKUnInit(void);

long Alk_Login(const char *pUrl, unsigned short nPort, 
		const char *pProxyServerIP);
int Alk_Logout(long lDeviceID);

//stream control
long Alk_OpenStream(long lDeviceID,int nChannel,long lStreamType,	
	long lStreamMode,long ConnectType, long lBufPoolSize);
long Alk_CloseStream(long lStreamID);

//call back
long Alk_SetRealDataCallBack (long lStreamID,DATA_TYPE_E eDataType,fRealDataCallBack cbRealDataFunc,unsigned long dwUser);
long Alk_SetDisplayDataCallBack(long lStreamID, DATA_TYPE_E eDataType,fDisplayDataCallBack cbDisplayDataFunc,unsigned long dwUser);
long Alk_SetMJPEGCallBack(long lStreamID, fMJPEGCallBack cbMJPEGDataFunc, unsigned long dwUser);

long Alk_SetAudioCallBack(long lStreamID, fAudioCallBack cbAudioDataFunc, unsigned long dwUser);


long Alk_SetVideoWnd(long lStreamID, unsigned long hWnd);
long Alk_StartDecode(long lStreamID);
long Alk_StopDecode(long lStreamID);

//2 PTZ control
long Alk_PTZControl (long lStreamID, int nChannel,long lCommandID,long lParameter);
long Alk_GetPTModuleConfig (long lDeviceID, int nChannel, PTMODULE_CONFIG *pConfig);
long Alk_SetPTModuleConfig (long lDeviceID, int nChannel, PTMODULE_CONFIG *pConfig);
long Alk_TransparentTransfer(long lDeviceID, int nChannel, unsigned char* pBuf, int len);

//3 Channel attribute

long Alk_GetChannelAttribute(long lDeviceID, struct VIDEO_ATTRIBUTE *pParam);
long Alk_SetChannelAttribute(long lDeviceID, struct VIDEO_ATTRIBUTE *pParam);

long Alk_GetMultiVideoChannel(long lDeviceID, struct MULTI_VIDEO_CHANNEL *pVideoChannel);
long Alk_SetMultiVideoChannel(long lDeviceID, struct MULTI_VIDEO_CHANNEL *pVideoChannel);

long Alk_GetHomeFunction(long lDeviceID, struct HOME_FUNCTION *pHomeFunction);
long Alk_SetHomeFunction(long lDeviceID, struct HOME_FUNCTION *pHomeFunction);

long Alk_GetAudioAttribute(long lDeviceID,int nChannel, struct AUDIO_ATTRIBUTE *pAudio);
long Alk_SetAudioAttribute(long lDeviceID,int nChannel, struct AUDIO_ATTRIBUTE *pAudio);
long Alk_GetSerialPortConfig(long lDeviceID,int nComID,
										 struct SERIALPORT_CONFIG *pSerialConfig);
long Alk_SetSerialPortConfig (long lDeviceID,int nComID,
										  struct SERIALPORT_CONFIG *pSerialConfig);
//4 camera param
long Alk_GetDayNightMode(long lDeviceID,int nChannel,char *DayNightMode);
long Alk_SetDayNightMode(long lDeviceID,int nChannel,char *DayNightMode);

long Alk_GetDayNightOnOFF(long lDeviceID,int nChannel,char *DayNightOnOFF);
long Alk_SetDayNightOnOFF(long lDeviceID,int nChannel,char *DayNightOnOFF);

long Alk_GetExposureMode(long lDeviceID,int nChannel,char *ExposureMode);
long Alk_SetExposureMode(long lDeviceID,int nChannel,char *ExposureMode);

long Alk_GetShutterSpeed(long lDeviceID,int nChannel,char *ShutterSpeed);
long Alk_SetShutterSpeed(long lDeviceID,int nChannel,char *ShutterSpeed);

long Alk_GetApertureSetup(long lDeviceID,int nChannel,char *ApertureSetup);
long Alk_SetApertureSetup(long lDeviceID,int nChannel,char *ApertureSetup);

long Alk_GetNearLimitSetup(long lDeviceID,int nChannel,char *NearLimit);
long Alk_SetNearLimitSetup(long lDeviceID,int nChannel,char *NearLimit);

long Alk_GetWhiteBalanceMode(long lDeviceID,int nChannel,char *WhiteBalanceMode);
long Alk_SetWhiteBalanceMode(long lDeviceID,int nChannel,char *WhiteBalanceMode);

long Alk_GetNoiseReduction(long lDeviceID,int nChannel,char *NoiseReduction);
long Alk_SetNoiseReduction(long lDeviceID,int nChannel,char *NoiseReduction);

long Alk_GetAGCSetup(long lDeviceID,int nChannel,int* pAGC);
long Alk_SetAGCSetup(long lDeviceID,int nChannel,int AGC);

long Alk_GetHDMIConfig(long lDeviceID,int nChannel,struct HDMI_CONFIG *pConfig);
long Alk_SetHDMIConfig(long lDeviceID,int nChannel,struct HDMI_CONFIG *pConfig);

long Alk_GetVideoFlip(long lDeviceID, struct VIDEO_FLIP *pFlip);
long Alk_SetVideoFlip(long lDeviceID, struct VIDEO_FLIP *pFlip);

//5 date and time
long Alk_GetDateTime(long lDeviceID,struct DATETIME_CONFIG *pDateTime);
long Alk_SetDateTime (long lDeviceID,struct DATETIME_CONFIG *pDateTime);

//6 OSD
long Alk_GetOSDRegion(long lDeviceID,int nChannel,int nOsdType,struct OSD_REGION *pOsdRegion);
long Alk_SetOSDRegion(long lDeviceID,int nChannel,int nOsdType,struct OSD_REGION *pOsdRegion);

//7 network
long Alk_GetNetConfig (long lDeviceID,struct NET_CONFIG *pNetConfig);
long Alk_SetNetConfig (long lDeviceID,struct NET_CONFIG *pNetConfig);
long Alk_GetDDNSConfig (long lDeviceID,struct DDNS_CONFIG *pDDNSConfig);
long Alk_SetDDNSConfig (long lDeviceID,struct DDNS_CONFIG *pDDNSConfig);
long Alk_GetPPPoEConfig(long lDeviceID, struct PPPOE_CONFIG *pConfig);
long Alk_SetPPPoEConfig(long lDeviceID, struct PPPOE_CONFIG *pConfig);
long Alk_GetFTPConfig(long lDeviceID, struct FTP_CONFIG *pConfig);
long Alk_SetFTPConfig(long lDeviceID, struct FTP_CONFIG *pConfig);
long Alk_GetWiFiConfig(long lDeviceID, struct WIFI_CONFIG *pConfig);
long Alk_SetWiFiConfig(long lDeviceID, struct WIFI_CONFIG *pConfig);
long Alk_GetSMTPConfig(long lDeviceID, struct SMTP_CONFIG *pConfig);
long Alk_SetSMTPConfig(long lDeviceID, struct SMTP_CONFIG *pConfig);
long Alk_GetSMTPNotify(long lDeviceID, struct SMTP_NOTIFY *pNotify);
long Alk_SetSMTPNotify(long lDeviceID, struct SMTP_NOTIFY *pNotify);

//8 storage card
long Alk_GetStorageControl(long lDeviceID, struct STORAGE_DEVICE_CONTROL * pControl);
long Alk_SetStorageControl(long lDeviceID, struct STORAGE_DEVICE_CONTROL * pControl);
long Alk_GetStorageInfo(long lDeviceID, struct STORAGE_DEVICE_INFO * pInfo);
long Alk_GetStorageMode(long lDeviceID, struct STORAGE_DEVICE_MODE * pMode);
long Alk_SetStorageMode(long lDeviceID, struct STORAGE_DEVICE_MODE * pMode);
long Alk_GetLocalRecordParam(long lDeviceID, struct LOCAL_RECORD_PARAM * pParam);
long Alk_SetLocalRecordParam(long lDeviceID, struct LOCAL_RECORD_PARAM * pParam);
long Alk_GetLocalScheduleSnapParam(long lDeviceID, struct LOCAL_SCHEDULE_SNAP_PARAM * pParam);
long Alk_SetLocalScheduleSnapParam(long lDeviceID, struct LOCAL_SCHEDULE_SNAP_PARAM * pParam);
long Alk_GetNetDownConfig(long lDeviceID, struct NET_DOWN_PARAM * pParam);
long Alk_SetNetDownConfig(long lDeviceID, struct NET_DOWN_PARAM * pParam);
long Alk_SetRemoteRecordConfig(long lDeviceID, struct REMOTE_RECORD_CONFIG * pConfig);
long Alk_RemoteSnap(long lDeviceID, struct REMOTE_SNAP * pSnap);
long Alk_UploadSingleFile(long lDeviceID, struct FTP_SINGLEFILE * pFile);
long Alk_UploadBatchFiles(long lDeviceID, struct FTP_BATCHFILES * pFiles);
long Alk_DeleteFile(long lDeviceID, struct FTP_DELETEFILE * pDelete);
long Alk_QueryFile(long lDeviceID, struct QUERY_FILE * pFile);
long Alk_QueryFileList(long lDeviceID, int* count, char*** filelist);
long Alk_GetDownloadConfig (long lDeviceID, struct DOWNLOAD_CONFIG * pConfig);
long Alk_SetDownloadConfig (long lDeviceID, struct DOWNLOAD_CONFIG * pConfig);

//9 alarm
long Alk_GetAlarmConfig (long lDeviceID, struct ALARM_CONFIG *pAlarmConfig);
long Alk_SetAlarmConfig (long lDeviceID, struct ALARM_CONFIG *pAlarmConfig);
long Alk_GetAlarmInConfig (long lDeviceID,int nAlarmIn_no, struct ALARMIN_CONFIG *pAlarmInConfig);
long Alk_SetAlarmInConfig (long lDeviceID,int nAlarmIn_no, struct ALARMIN_CONFIG *pAlarmInConfig);
long Alk_GetAlarmOutConfig (long lDeviceID,int nAlarmOut_no, struct ALARMOUT_CONFIG *pAlarmOutConfig);
long Alk_SetAlarmOutConfig (long lDeviceID,int nAlarmOut_no, struct ALARMOUT_CONFIG *pAlarmOutConfig);
long Alk_GetAlarmServiceConfig(long lDeviceID, struct ALARM_SERVICE_CONFIG *pConfig);
long Alk_SetAlarmServiceConfig(long lDeviceID, struct ALARM_SERVICE_CONFIG *pConfig);

//10 move detect
long Alk_GetMDConfig (long lDeviceID,int nChannel,int area_no, struct MD_CONFIG *pMDConfig);
long Alk_SetMDConfig (long lDeviceID,int nChannel,int area_no, struct MD_CONFIG *pMDConfig);
long Alk_GetMDLinkConfig (long lDeviceID,int nChannel, struct MD_LINK_CONFIG *pConfig);
long Alk_SetMDLinkConfig (long lDeviceID,int nChannel, struct MD_LINK_CONFIG *pConfig);

//11 Auxil Control
long Alk_AuxilControl(long lDeviceID, long lCommandID, char* pszMode, long lValue);
long Alk_RebootDevice (long lDeviceID);
long Alk_GetWatchdogConfig (long lDeviceID, int nChannel, struct WATCHDOG_CONFIG *pConfig);
long Alk_SetWatchdogConfig (long lDeviceID, int nChannel, struct WATCHDOG_CONFIG *pConfig);

//12 maintain manage
long Alk_GetProductSN(long lDeviceID, char* szSN);
long Alk_GetVersionInfo(long lDeviceID, struct VERSION_INFO *pVersionInfo);

void GetSDKVersion(char* str);

#endif

//#ifdef __cplusplus 
//} 
//#endif 

