#ifndef _HC_NET_SDK_H_
#define _HC_NET_SDK_H_

#ifdef __cpluscplus
#define NET_DVR_API extern
#else
#define NET_DVR_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __PLAYRECT_defined
#define __PLAYRECT_defined
typedef struct __PLAYRECT
{
	int x;                               
	int y;                                  
	int uWidth;                            
	int uHeight;                            
}PLAYRECT;
#endif

/*#if (defined(_WIN32))
#include <windows.h>
#define NET_DVR_API  extern "C"__declspec(dllimport)
#elif defined(__linux__)*/

typedef int32_t			LONG ;
typedef uint32_t  		DWORD ;

typedef unsigned char	BYTE ;
typedef int 			BOOL;
typedef unsigned int   	UINT;
typedef void* 			LPVOID;
typedef void* 			HANDLE;

#ifndef  	TRUE
#define  	TRUE	1
#endif

#ifndef 	FALSE
#define		FALSE	0
#endif

#define __stdcall 
#define CALLBACK   
#ifndef __HWND_defined
#define __HWND_defined
typedef PLAYRECT HWND;
#endif
//#define NET_DVR_API extern "C"
typedef unsigned int   COLORKEY;
typedef unsigned int    COLORREF;

#ifndef __HDC_defined
#define __HDC_defined
typedef struct __DC
{
	void*   surface;                        // SDL窗口的Surface
	HWND    hWnd;                           // HDC所在的窗口句柄
}DC;
#endif

typedef DC* HDC;
#endif

typedef struct tagInitInfo
{
	int uWidth;
	int uHeight;
}INITINFO;


//Macro definition 
#define MAX_NAMELEN			    16		//DVR's local Username
#define MAX_RIGHT			    32		//Authority permitted by Device(1-12 for local authority, 13-32 for remote authority)
#define NAME_LEN			    32      //Username length
#define PASSWD_LEN			    16      //Password length
#define SERIALNO_LEN		    48      //SN length
#define MACADDR_LEN			    6       //Length of MAC address
#define MAX_ETHERNET		    2       //Configurable Ethernet of device
#define PATHNAME_LEN		    128     //length of path name
#define MAX_PRESET_V13          16      //Preset number

#define MAX_TIMESEGMENT_V30	    8       //Maximum number of time segments in 9000 DVR's guard schedule
#define MAX_TIMESEGMENT		    4       //Maximum number of time segments in 8000 DVR's guard schedule
#define MAX_SHELTERNUM			4       //Maximum number of mask areas in 8000 DVR
#define MAX_DAYS				7       //The number of days in a week
#define PHONENUMBER_LEN			32      //Maximum length of PPPOE number

#define MAX_DISKNUM_V30			33		//Maximum disk number in 9000 DVR, including 16 internal SATA disks, 1 eSTAT disk and 16 NFS disks
#define MAX_DISKNUM		        16      //Maximum disk number in 8000 DVR
#define MAX_DISKNUM_V10		    8       //used in 1.2 or earlier version

#define MAX_WINDOW_V30			32      //9000 maximum number of local display windows
#define MAX_WINDOW				16      //8000 maximum number of local display windows
#define MAX_VGA_V30				4       //9000 maximum number of VGA
#define MAX_VGA			    	1       //8000 maximum number of VGA

#define MAX_USERNUM_V30			32      //Maximum number of 9000 DVR users
#define MAX_USERNUM			    16      //Maximum number of 8000 DVR users
#define MAX_EXCEPTIONNUM_V30	32      //Maximum number of exceptions handled by 9000 DVR
#define MAX_EXCEPTIONNUM		16      //Maximum number of exceptions handled by 8000 DVR
#define MAX_LINK				6       //Maximum number of video connections to 8000's single channel

#define MAX_DECPOOLNUM			4       //Maximum loop decoding number supported by each decoding channel of single channel decoder
#define MAX_DECNUM				4       //Maximum decoding channel number of single channel decoder(only has one channel, others are reserved)
#define MAX_TRANSPARENTNUM		2       //Maximum number of Transparent channel in single channel decoder
#define MAX_CYCLE_CHAN			16      //Maximum number of loop channels in single channel decoder
#define MAX_CYCLE_CHAN_V30      64      //Maximum number of loop channels in single channel decoder(extend)
#define MAX_DIRNAME_LENGTH		80      //Maximum number of directory name
#define MAX_WINDOWS				16      //Maximum number of windows

#define MAX_STRINGNUM_V30		8		//Maximum number of OSD lines in 9000 DVR
#define MAX_STRINGNUM			4       //Maximum number of OSD lines in 8000 DVR
#define MAX_STRINGNUM_EX		8       //8000 customized extensions
#define MAX_AUXOUT_V30			16      //9000 maximum number of AUX output ports
#define MAX_AUXOUT			    4       //8000 maximum number of AUX output ports
#define MAX_HD_GROUP			16      //9000 maximum number of hard disk groups
#define MAX_NFS_DISK			8       //8000 maximum number of NFS disks

#define IW_ESSID_MAX_SIZE	    32      //SSID length of WIFI
#define IW_ENCODING_TOKEN_MAX	32      //Maximum bytes of WIFI security Key
#define MAX_SERIAL_NUM			64	    //Maximum number of Transparent channel
#define MAX_DDNS_NUMS	        10      //Maximum number of DDNS in 9000
#define MAX_DOMAIN_NAME		    64		//Maximum Domain Name length
#define MAX_EMAIL_ADDR_LEN		48		//Maximum Email Address length
#define MAX_EMAIL_PWD_LEN	    32      //Maximun Email password length

#define MAXPROGRESS		        100     //Maximum percent while playing back
#define MAX_SERIALNUM	        2       //Serial Port supported by 8000 DVR, 1-232, 2-485
#define CARDNUM_LEN		        20      //Card number length
#define MAX_VIDEOOUT_V30        4       //9000 DVR analog video output number. 
#define MAX_VIDEOOUT	        2       //8000 DVR analog video output number

#define MAX_PRESET_V30			    256		/* 9000 Preset number of PTZ  */
#define MAX_TRACK_V30			    256		/* 9000 Track number of PTZ   */
#define MAX_CRUISE_V30			    256		/* 9000 Cruise number of PTZ  */
#define MAX_PRESET				    128		/* 8000 Preset number of PTZ  */
#define MAX_TRACK				    128		/* 8000 Track number of PTZ   */
#define MAX_CRUISE				    128		/* 8000 Cruise number of PTZ  */

#define CRUISE_MAX_PRESET_NUMS	    32 	    /* Maximum number of Cruise points in one Cruise */

#define MAX_SERIAL_PORT             8       // Maximum number of RS232 supported by 9000 DVR
#define MAX_PREVIEW_MODE            8       /* Maximum number of display layout mode; single windows/4 windows/9 windows/16 windows/... */
#define MAX_MATRIXOUT               16      /* Maximum number of analog matrix output */
#define LOG_INFO_LEN                11840   /* Additional information of Log */
#define DESC_LEN                    16      /* String length of PTZ description */
#define PTZ_PROTOCOL_NUM            200     /* Maximum number of PTZ protocols in 9000 DVR */
#define IPC_PROTOCOL_NUM            50     /* Maximum number of ipc protocols in 9000 DVR */

#define MAX_AUDIO			        1       //Number of talk channels in 8000 DVR
#define MAX_AUDIO_V30			    2       //Number of talk channels in 9000 DVR
#define MAX_CHANNUM			        16      //Maximum number of video/audio channels in 8000 DVR
#define MAX_ALARMIN			        16      //Maximum number of alarm input channels in 8000 DVR
#define MAX_ALARMOUT		        4       //Maximum number of alarm output channels in 8000 DVR
//9000 IP Camera
#define MAX_ANALOG_CHANNUM          32      //32 analog channels in total
#define MAX_ANALOG_ALARMOUT         32      //32 analog alarm output channels intotal
#define MAX_ANALOG_ALARMIN          32      //32 analog alarm input channels intotal
#define MAX_IP_DEVICE               32      //9000 DVR can connect 32 IP devices
#define MAX_IP_CHANNEL              32      //9000 DVR can connect 32 IP channels
#define MAX_IP_ALARMIN              128     //Maximum number of alarm input channels that can be added
#define MAX_IP_ALARMOUT             64      //Maximum number of alarm output channels that can be added

//SDK_V31 ATM
#define MAX_ACTION_TYPE	        12	    //Maximum action number of the transactions added  
#define MAX_ATM_PROTOCOL_NUM    256     //Maximum protocol number of each input sort
#define ATM_CUSTOM_PROTO       1025     //user-defined protocol
#define ATM_PROTOCOL_SORT       4       //number of ATM protocol segment 
#define ATM_DESC_LEN            32      //Length of the ATM description string
// SDK_V31 ATM

/*Maximum channels number including analog channels and IP channels */
#define MAX_CHANNUM_V30               ( MAX_ANALOG_CHANNUM + MAX_IP_CHANNEL )//64
#define MAX_ALARMOUT_V30              ( MAX_ANALOG_ALARMOUT + MAX_IP_ALARMOUT )//96
#define MAX_ALARMIN_V30               ( MAX_ANALOG_ALARMIN + MAX_IP_ALARMIN )//160

/*******************Global Error Code**********************/	
#define NET_DVR_NOERROR 					0	//No Error
#define NET_DVR_PASSWORD_ERROR 				1	//Username or Password error
#define NET_DVR_NOENOUGHPRI 				2	//Don't have enough authority 
#define NET_DVR_NOINIT 						3	//have not Initialized
#define NET_DVR_CHANNEL_ERROR 				4	//Channel number error
#define NET_DVR_OVER_MAXLINK 				5	//Number of clients connecting to DVR beyonds the Maximum
#define NET_DVR_VERSIONNOMATCH				6	//Version is not matched
#define NET_DVR_NETWORK_FAIL_CONNECT		7	//Connect to server failed
#define NET_DVR_NETWORK_SEND_ERROR			8	//Send data to server failed
#define NET_DVR_NETWORK_RECV_ERROR			9	//Receive data from server failed
#define NET_DVR_NETWORK_RECV_TIMEOUT		10	//Receive data from server timeout
#define NET_DVR_NETWORK_ERRORDATA			11	//Transfered data has error
#define NET_DVR_ORDER_ERROR					12	//Wrong Sequence of invoking API
#define NET_DVR_OPERNOPERMIT				13	//No such authority. 
#define NET_DVR_COMMANDTIMEOUT				14	//Execute command timeout
#define NET_DVR_ERRORSERIALPORT				15	//Serial port number error
#define NET_DVR_ERRORALARMPORT				16	//Alarm port error
#define NET_DVR_PARAMETER_ERROR 			17  //Parameters error
#define NET_DVR_CHAN_EXCEPTION				18	//Server channel in error status
#define NET_DVR_NODISK						19	//No hard disk
#define NET_DVR_ERRORDISKNUM				20	//Hard disk number error
#define NET_DVR_DISK_FULL					21	//Server's hard disk is full
#define NET_DVR_DISK_ERROR					22	//Server's hard disk error
#define NET_DVR_NOSUPPORT					23	//Server doesn't support
#define NET_DVR_BUSY						24	//Server is busy
#define NET_DVR_MODIFY_FAIL					25	//Server modification failed
#define NET_DVR_PASSWORD_FORMAT_ERROR		26	//Input format of Password error
#define NET_DVR_DISK_FORMATING				27	//Hard disk is formating, cannot execute.  
#define NET_DVR_DVRNORESOURCE				28	//DVR don't have enough resource
#define	NET_DVR_DVROPRATEFAILED				29  //DVR Operation failed
#define NET_DVR_OPENHOSTSOUND_FAIL 			30  //Open PC audio failed
#define NET_DVR_DVRVOICEOPENED 				31  //Server's talk channel is occupied 
#define	NET_DVR_TIMEINPUTERROR				32  //Time input is not correct
#define	NET_DVR_NOSPECFILE					33  //Can't playback the file that does not exist in Server
#define NET_DVR_CREATEFILE_ERROR			34	//Create file error
#define	NET_DVR_FILEOPENFAIL				35  //Open file error
#define	NET_DVR_OPERNOTFINISH				36  //The previous operation is not finished yet
#define	NET_DVR_GETPLAYTIMEFAIL				37  //Get current playing time error
#define	NET_DVR_PLAYFAIL					38  //Playback error
#define NET_DVR_FILEFORMAT_ERROR			39  //Wrong file format
#define NET_DVR_DIR_ERROR					40	//Wrong directory 
#define NET_DVR_ALLOC_RESOURCE_ERROR		41  //Assign resource error
#define NET_DVR_AUDIO_MODE_ERROR			42	//Audio card mode error
#define NET_DVR_NOENOUGH_BUF				43	//Buffer is too small
#define NET_DVR_CREATESOCKET_ERROR		 	44	//Create SOCKET error
#define NET_DVR_SETSOCKET_ERROR				45	//Setup SOCKET error
#define NET_DVR_MAX_NUM						46	//Reach the maximum number
#define NET_DVR_USERNOTEXIST				47	//User does not exist
#define NET_DVR_WRITEFLASHERROR				48  //Write to FLASH error
#define NET_DVR_UPGRADEFAIL					49  //DVR update failed 
#define NET_DVR_CARDHAVEINIT				50  //Decoding Card has been initialized already
#define NET_DVR_PLAYERFAILED				51	//Invoke API of player library error
#define NET_DVR_MAX_USERNUM					52  //Reach the maximum number of DVR Users
#define NET_DVR_GETLOCALIPANDMACFAIL		53  //Failed to get Client software's IP or MAC address
#define NET_DVR_NOENCODEING					54	//No encoding on this channel
#define NET_DVR_IPMISMATCH					55	//IP address is not matched
#define NET_DVR_MACMISMATCH					56	//MAC address is not matched
#define NET_DVR_UPGRADELANGMISMATCH			57	//Update file has wrong language
#define NET_DVR_MAX_PLAYERPORT				58	//Reach the maximum player number
#define NET_DVR_NOSPACEBACKUP				59	//There is no enough space on the backup device
#define NET_DVR_NODEVICEBACKUP				60	//Failed to find the specified backup device 
#define NET_DVR_PICTURE_BITS_ERROR			61	//Image has wrong color bit, 24 color only
#define NET_DVR_PICTURE_DIMENSION_ERROR		62	//Image size exceeds the maximum value; smaller than 128*256
#define NET_DVR_PICTURE_SIZ_ERROR			63	//Image file exceeds the maximum size; smaller than 100K
#define NET_DVR_LOADPLAYERSDKFAILED			64	//Failed to load the player SDK from current directory
#define NET_DVR_LOADPLAYERSDKPROC_ERROR		65	//Failed to find the API's entry in player SDK
#define NET_DVR_LOADDSSDKFAILED				66	//Failed to load the DSsdk from current directory
#define NET_DVR_LOADDSSDKPROC_ERROR		    67	//Failed to find the API's entry in DSsDK
#define NET_DVR_DSSDK_ERROR					68	//Failed to invole the API of DSsDK.dll
#define NET_DVR_VOICEMONOPOLIZE				69	//Audio card has been occupied exclusively
#define NET_DVR_JOINMULTICASTFAILED			70	//Join to multicast group error
#define NET_DVR_CREATEDIR_ERROR				71	//Failed to create log directory
#define NET_DVR_BINDSOCKET_ERROR			72	//Failed to bind socked error. 
#define NET_DVR_SOCKETCLOSE_ERROR			73	//socket is disconnected, that caused by network disconnected or unreachable destination mostly
#define NET_DVR_USERID_ISUSING			    74	//User ID is using when logout
#define NET_DVR_SOCKETLISTEN_ERROR			75	//Socket listen error
#define NET_DVR_PROGRAM_EXCEPTION			76	//Application error
#define NET_DVR_WRITEFILE_FAILED			77	//Failed to write file
#define NET_DVR_FORMAT_READONLY				78  //Forbidden to format read only disk
#define NET_DVR_WITHSAMEUSERNAME		    79  //Same user name already exists.
#define NET_DVR_DEVICETYPE_ERROR            80  //Device Model is not matched when import parameters
#define NET_DVR_LANGUAGE_ERROR              81  //Audio is not matched when import parameters
#define NET_DVR_PARAVERSION_ERROR           82  //Software version is not matched when import parameters
#define NET_DVR_IPCHAN_NOTALIVE             83  //IP Channels is off line when
#define NET_DVR_RTSP_SDK_ERROR				84	//Failed to load IPC communication library
#define NET_DVR_CONVERT_SDK_ERROR			85	//Failed to load stream format convertion library
#define NET_DVR_IPC_COUNT_OVERFLOW			86  //ip count overflow
#define NET_DVR_EMAIL_TEST_FAILED			87  //email test failed
#define NET_DVR_PARAMMODE_ERROR             88 //Param Mode Error

#define  NET_PLAYM4_NOERROR					    500	//no error
#define	 NET_PLAYM4_PARA_OVER				    501	//input parameter is invalid;
#define  NET_PLAYM4_ORDER_ERROR				    502	//The order of the function to be called is error.
#define	 NET_PLAYM4_TIMER_ERROR				    503	//Create multimedia clock failed;
#define  NET_PLAYM4_DEC_VIDEO_ERROR			    504	//Decode video data failed.
#define  NET_PLAYM4_DEC_AUDIO_ERROR			    505	//Decode audio data failed.
#define	 NET_PLAYM4_ALLOC_MEMORY_ERROR		    506	//Allocate memory failed.
#define  NET_PLAYM4_OPEN_FILE_ERROR			    507	//Open the file failed.
#define  NET_PLAYM4_CREATE_OBJ_ERROR		    508	//Create thread or event failed
#define  NET_PLAYM4_CREATE_DDRAW_ERROR		    509	//Create DirectDraw object failed.
#define  NET_PLAYM4_CREATE_OFFSCREEN_ERROR      510	//failed when creating off-screen surface.
#define  NET_PLAYM4_BUF_OVER			        511	//buffer is overflow
#define  NET_PLAYM4_CREATE_SOUND_ERROR	        512	//failed when creating audio device.	
#define	 NET_PLAYM4_SET_VOLUME_ERROR	        513	//Set volume failed
#define  NET_PLAYM4_SUPPORT_FILE_ONLY	        514	//The function only support play file.
#define  NET_PLAYM4_SUPPORT_STREAM_ONLY	        515	//The function only support play stream.
#define  NET_PLAYM4_SYS_NOT_SUPPORT		        516	//System not support.
#define  NET_PLAYM4_FILEHEADER_UNKNOWN          517	//No file header.
#define  NET_PLAYM4_VERSION_INCORRECT	        518	//The version of decoder and encoder is not adapted.  
#define  NET_PALYM4_INIT_DECODER_ERROR          519	//Initialize decoder failed.
#define  NET_PLAYM4_CHECK_FILE_ERROR	        520	//The file data is unknown.
#define  NET_PLAYM4_INIT_TIMER_ERROR	        521	//Initialize multimedia clock failed.
#define	 NET_PLAYM4_BLT_ERROR			        522	//Blt failed.
#define  NET_PLAYM4_UPDATE_ERROR		        523	//Update failed.
#define  NET_PLAYM4_OPEN_FILE_ERROR_MULTI       524 //openfile error, streamtype is multi
#define  NET_PLAYM4_OPEN_FILE_ERROR_VIDEO       525 //openfile error, streamtype is video
#define  NET_PLAYM4_JPEG_COMPRESS_ERROR         526 //JPEG compress error
#define  NET_PLAYM4_EXTRACT_NOT_SUPPORT         527	//Don't support the version of this file.
#define  NET_PLAYM4_EXTRACT_DATA_ERROR          528	//extract video data failed.

/*******************Global Error Code end**********************/

/*************************************************
Return value of NET_DVR_IsSupport(), 
the definition of bit 1 to bit 9 is below and TRUE means support
**************************************************/
#define NET_DVR_SUPPORT_DDRAW			0x01//Support DIRECTDRAW, otherwise Player can't work
#define NET_DVR_SUPPORT_BLT				0x02//Display adapter supports BLT, otherwise Player can't work
#define NET_DVR_SUPPORT_BLTFOURCC		0x04//BLT supports color conversion, otherwise, Player will do RGB conversion in software mode；
#define NET_DVR_SUPPORT_BLTSHRINKX		0x08//BLT supports X-coordinate shrink, otherwise, Player will do it in software mode；
#define NET_DVR_SUPPORT_BLTSHRINKY		0x10//BLT supports Y-coordinate shrink, otherwise, Player will do it in software mode；
#define NET_DVR_SUPPORT_BLTSTRETCHX		0x20//BLT supports X-coordinate expand, otherwise, Player will do it in software mode；
#define NET_DVR_SUPPORT_BLTSTRETCHY		0x40//BLT supports Y-coordinate expand, otherwise, Player will do it in software mode；
#define NET_DVR_SUPPORT_SSE				0x80//CPU supports SSE commands，Intel Pentium3 or higher version supports SSE；
#define NET_DVR_SUPPORT_MMX				0x100//CPU supports MMX commands，Intel Pentium3 or higher version supports MMX

/**********************PTZ Commands begin*************************/	
#define LIGHT_PWRON		2	/* Switch on light */
#define WIPER_PWRON		3	/* Switch on Wiper */
#define FAN_PWRON		4	/* Switch on Fan */
#define HEATER_PWRON	5	/* Switch on Heater */
#define AUX_PWRON1		6	/* Switch on auxiliary equipment 1*/
#define AUX_PWRON2		7	/* Switch on auxiliary equipment 2*/
#define SET_PRESET		8	/* Configure Preset */
#define CLE_PRESET		9	/* Clean Preset */

#define ZOOM_IN			11	/* Zoom in*/
#define ZOOM_OUT		12	/* Zoom out */
#define FOCUS_NEAR      13  /* Focus in */
#define FOCUS_FAR       14  /* Focus out*/
#define IRIS_OPEN       15  /* Iris open */
#define IRIS_CLOSE      16  /* Iris close */

#define TILT_UP			21	/* PTZ tilt up */
#define TILT_DOWN		22	/* PTZ tilt down*/
#define PAN_LEFT		23	/* PTZ pan left */
#define PAN_RIGHT		24	/* PTZ pan right*/
#define UP_LEFT			25	/* PTZ turn up and left */
#define UP_RIGHT		26	/* PTZ turn up and right */
#define DOWN_LEFT		27	/* PTZ turn down and left */
#define DOWN_RIGHT		28	/* PTZ turn down and right */
#define PAN_AUTO		29	/* PTZ auto pan */

#define FILL_PRE_SEQ	30	/* Add preset to sequence */
#define SET_SEQ_DWELL	31	/* Set cruise point's residence time */
#define SET_SEQ_SPEED	32	/* Set cruise point */
#define CLE_PRE_SEQ		33	/* Delete preset from sequence */
#define STA_MEM_CRUISE	34	/* Start recording trace */
#define STO_MEM_CRUISE	35	/* Stop recoding trace  */
#define RUN_CRUISE		36	/* Start Cruise */
#define RUN_SEQ			37	/* Start Sequence */
#define STOP_SEQ		38	/* Stop Sequence */
#define GOTO_PRESET		39	/* Go to preset */

/**********************PTZ Commands end*************************/	

/*************************************************
Play Control Commands
Macro Definition
NET_DVR_PlayBackControl
NET_DVR_PlayControlLocDisplay
NET_DVR_DecPlayBackCtrl
**************************************************/	
#define NET_DVR_PLAYSTART		1//Start Play
#define NET_DVR_PLAYSTOP		2//Stop Play
#define NET_DVR_PLAYPAUSE		3//Pause Play
#define NET_DVR_PLAYRESTART		4//Restore Play
#define NET_DVR_PLAYFAST		5//Play faster
#define NET_DVR_PLAYSLOW		6//Play slower
#define NET_DVR_PLAYNORMAL		7//Normal Speed
#define NET_DVR_PLAYFRAME		8//Play frame by frame
#define NET_DVR_PLAYSTARTAUDIO	9//Open audio
#define NET_DVR_PLAYSTOPAUDIO	10//Close audio
#define NET_DVR_PLAYAUDIOVOLUME	11//Adjust volume 
#define NET_DVR_PLAYSETPOS		12//change the playback progress 
#define NET_DVR_PLAYGETPOS		13//Get the playback progress
#define NET_DVR_PLAYGETTIME		14//Get the played time(available when playback by time)
#define NET_DVR_PLAYGETFRAME	15//Get the played frame number(available when playback by file)
#define NET_DVR_GETTOTALFRAMES  16//Get total frame number of current file(available when playback by file)
#define NET_DVR_GETTOTALTIME    17//Get total time of current file(available when playback by file)
#define NET_DVR_THROWBFRAME		20//Discard B frame
#define NET_DVR_SETSPEED		24//Setup stream speed
#define NET_DVR_KEEPALIVE		25//Keep connection with server(if callback is blocked, send it every 2 second)

//Remote Key//
/* key value send to CONFIG program */
#define KEY_CODE_1 1
#define KEY_CODE_2 2
#define KEY_CODE_3 3
#define KEY_CODE_4 4
#define KEY_CODE_5 5
#define KEY_CODE_6 6
#define KEY_CODE_7 7
#define KEY_CODE_8 8
#define KEY_CODE_9 9
#define KEY_CODE_0 10
#define KEY_CODE_POWER 11
#define KEY_CODE_MENU 12
#define KEY_CODE_ENTER 13
#define KEY_CODE_CANCEL 14
#define KEY_CODE_UP 15
#define KEY_CODE_DOWN 16
#define KEY_CODE_LEFT 17
#define KEY_CODE_RIGHT 18
#define KEY_CODE_EDIT 19
#define KEY_CODE_ADD 20
#define KEY_CODE_MINUS 21
#define KEY_CODE_PLAY 22
#define KEY_CODE_REC 23
#define KEY_CODE_PAN 24
#define KEY_CODE_M 25
#define KEY_CODE_A 26
#define KEY_CODE_F1 27
#define KEY_CODE_F2 28

/* for PTZ control */
#define KEY_PTZ_UP_START KEY_CODE_UP
#define KEY_PTZ_UP_STOP 32

#define KEY_PTZ_DOWN_START KEY_CODE_DOWN
#define KEY_PTZ_DOWN_STOP 33

#define KEY_PTZ_LEFT_START KEY_CODE_LEFT
#define KEY_PTZ_LEFT_STOP 34

#define KEY_PTZ_RIGHT_START KEY_CODE_RIGHT
#define KEY_PTZ_RIGHT_STOP 35

#define KEY_PTZ_AP1_START KEY_CODE_EDIT /* Iris+ */
#define KEY_PTZ_AP1_STOP 36

#define KEY_PTZ_AP2_START KEY_CODE_PAN /* Iris- */
#define KEY_PTZ_AP2_STOP 37

#define KEY_PTZ_FOCUS1_START KEY_CODE_A /* Focus+ */
#define KEY_PTZ_FOCUS1_STOP 38

#define KEY_PTZ_FOCUS2_START KEY_CODE_M /* Focus- */
#define KEY_PTZ_FOCUS2_STOP 39

#define KEY_PTZ_B1_START 40 /* Zoom+ */
#define KEY_PTZ_B1_STOP 41

#define KEY_PTZ_B2_START 42 /* Zoom- */
#define KEY_PTZ_B2_STOP 43

//New in 9000
#define KEY_CODE_11 44
#define KEY_CODE_12 45
#define KEY_CODE_13 46
#define KEY_CODE_14 47
#define KEY_CODE_15 48
#define KEY_CODE_16 49

/*************************Parameter Configure Commands begin*******************************/
//Used for NET_DVR_SetDVRConfig and NET_DVR_GetDVRConfig, pay attention to corresponding Structure

#define NET_DVR_GET_DEVICECFG		100		//Get DVR Parameters
#define NET_DVR_SET_DEVICECFG		101		//Set DVR Parameters
#define NET_DVR_GET_NETCFG			102		//Get Network Parameters
#define NET_DVR_SET_NETCFG			103		//Set Network Parameters
#define NET_DVR_GET_PICCFG			104		//Get Image Parameters
#define NET_DVR_SET_PICCFG			105		//Set Image Parameters
#define NET_DVR_GET_COMPRESSCFG		106		//Get Compression Parameters
#define NET_DVR_SET_COMPRESSCFG		107		//Set Compression Parameters
#define NET_DVR_GET_RECORDCFG		108		//Get Record Parameters
#define NET_DVR_SET_RECORDCFG		109		//Set Record Parameters
#define NET_DVR_GET_DECODERCFG		110		//Get PTZ Parameters
#define NET_DVR_SET_DECODERCFG		111		//Set PTZ Parameters
#define NET_DVR_GET_RS232CFG 		112		//Get RS232 Parameters
#define NET_DVR_SET_RS232CFG		113		//Set RS232 Parameters
#define NET_DVR_GET_ALARMINCFG 		114		//Get Alarm In Parameters
#define NET_DVR_SET_ALARMINCFG		115		//Set Alarm In Parameters
#define NET_DVR_GET_ALARMOUTCFG 	116		//Get Alarm Out Parameters
#define NET_DVR_SET_ALARMOUTCFG		117		//Set Alarm Out Parameters
#define NET_DVR_GET_TIMECFG 		118		//Get DVR time
#define NET_DVR_SET_TIMECFG			119		//Set DVR time
#define NET_DVR_GET_PREVIEWCFG 		120		//Get Local Preview Parameters
#define NET_DVR_SET_PREVIEWCFG		121		//Set Local Preview Parameters
#define NET_DVR_GET_VIDEOOUTCFG 	122		//Get Video Output Parameters
#define NET_DVR_SET_VIDEOOUTCFG		123		//Set Video Output Parameters
#define NET_DVR_GET_USERCFG 		124		//Get User Parameters
#define NET_DVR_SET_USERCFG			125		//Set User Parameters
#define NET_DVR_GET_EXCEPTIONCFG 	126		//Get Exception Parameters
#define NET_DVR_SET_EXCEPTIONCFG	127		//Set Exception Parameters
#define NET_DVR_GET_ZONEANDDST		128		//Get Time Zone & DST Parameters
#define NET_DVR_SET_ZONEANDDST		129		//Set Time Zone & DST Parameters
#define NET_DVR_GET_SHOWSTRING		130		//Get OSD Parameters
#define NET_DVR_SET_SHOWSTRING		131		//Set OSD Parameters
#define NET_DVR_GET_EVENTCOMPCFG	132		//Get Event Record Parameters
#define NET_DVR_SET_EVENTCOMPCFG	133		//Set Event Record  Parameters

#define NET_DVR_GET_AUXOUTCFG		140		//Get External Alarm Configuration
#define NET_DVR_SET_AUXOUTCFG		141		//Set External Alarm Configuration
#define NET_DVR_GET_PREVIEWCFG_AUX 	142		//Get -S device dual output parameters
#define NET_DVR_SET_PREVIEWCFG_AUX	143		//Set -S device dual output parameters

#define NET_DVR_GET_PICCFG_EX		200		//Get Image Parameters (Extended)
#define NET_DVR_SET_PICCFG_EX		201		//Set Image Parameters (Extended)
#define NET_DVR_GET_USERCFG_EX 		202		//Get User Parameters(Extended)
#define NET_DVR_SET_USERCFG_EX		203		//Set User Parameters(Extended)
#define NET_DVR_GET_COMPRESSCFG_EX	204		//Get Compression Parameters (Extended)
#define NET_DVR_SET_COMPRESSCFG_EX	205		//Set Compression Parameters (Extended)


#define NET_DVR_GET_NETAPPCFG		222		//Get Network Application Parameters NTP/DDNS/EMAIL
#define NET_DVR_SET_NETAPPCFG		223		//Set Network Application Parameters NTP/DDNS/EMAIL
#define NET_DVR_GET_NTPCFG			224		//Get Network Application Parameters NTP
#define NET_DVR_SET_NTPCFG			225		//Set Network Application Parameters NTP
#define NET_DVR_GET_DDNSCFG			226		//Get Network Application Parameters DDNS
#define NET_DVR_SET_DDNSCFG			227		//Set Network Application Parameters DDNS

//Corresponding with NET_DVR_EMAILPARA
#define NET_DVR_GET_EMAILCFG		228		//Get EMAIL Configuration
#define NET_DVR_SET_EMAILCFG		229		//Set EMAIL Configuration

#define NET_DVR_GET_NFSCFG			230		/* NFS disk config */
#define NET_DVR_SET_NFSCFG			231		/* NFS disk config */

#define NET_DVR_GET_SHOWSTRING_EX	238		//Get Extended OSD Parameters 
#define NET_DVR_SET_SHOWSTRING_EX	239		//Set Extended OSD Parameters
#define NET_DVR_GET_NETCFG_OTHER	244		//Get Network Parameters
#define NET_DVR_SET_NETCFG_OTHER	245		//Set Network Parameters 

//NET_DVR_EMAILCFG
#define NET_DVR_GET_EMAILPARACFG	250		//Get EMAIL parameters
#define NET_DVR_SET_EMAILPARACFG	251		//Setup EMAIL parameters


#define NET_DVR_GET_DDNSCFG_EX		274		//Get Extended DDNS Parameters
#define NET_DVR_SET_DDNSCFG_EX		275		//Set Extended DDNS Parameters


#define	NET_DVR_SET_PTZPOS			292		//Set PTZ Position
#define	NET_DVR_GET_PTZPOS			293		//Get PTZ Position
#define	NET_DVR_GET_PTZSCOPE		294		//Get PTZ Scope


/***************************DS9000 New Commands(_V30) begin *****************************/
//Network(NET_DVR_NETCFG_V30)
#define NET_DVR_GET_NETCFG_V30		    1000		//Get  Network  Parameters
#define NET_DVR_SET_NETCFG_V30		    1001		//Set  Network  Parameters

//Image(NET_DVR_PICCFG_V30)
#define NET_DVR_GET_PICCFG_V30		    1002		//Get Image Parameters
#define NET_DVR_SET_PICCFG_V30		    1003		//Set Image Parameters

//Record(NET_DVR_RECORD_V30)
#define NET_DVR_GET_RECORDCFG_V30	    1004		//Get Record Parameters
#define NET_DVR_SET_RECORDCFG_V30	    1005		//Set Record Parameters

//User(NET_DVR_USER_V30)
#define NET_DVR_GET_USERCFG_V30 	    1006		//Get User Parameters
#define NET_DVR_SET_USERCFG_V30		    1007		//Set User Parameters

//9000DDNS Config(NET_DVR_DDNSPARA_V30)
#define     NET_DVR_GET_DDNSCFG_V30		1010		//Get DDNS (9000Extended)
#define     NET_DVR_SET_DDNSCFG_V30		1011		//Set DDNS (9000Extended)

//EMAIL (NET_DVR_EMAILCFG_V30)
#define NET_DVR_GET_EMAILCFG_V30		1012		//Get EMAIL Configuration
#define NET_DVR_SET_EMAILCFG_V30		1013		//Set EMAIL Configuration

//Cruise (NET_DVR_CRUISE_PARA)
#define 	NET_DVR_GET_CRUISE			1020		
#define 	NET_DVR_SET_CRUISE			1021		


//Alarm input  (NET_DVR_ALARMINCFG_V30)
#define 	NET_DVR_GET_ALARMINCFG_V30			1024		
#define 	NET_DVR_SET_ALARMINCFG_V30			1025

//Alarm output  (NET_DVR_ALARMOUTCFG_V30)
#define 	NET_DVR_GET_ALARMOUTCFG_V30			1026		
#define 	NET_DVR_SET_ALARMOUTCFG_V30			1027

//Video output  (NET_DVR_VIDEOOUT_V30)
#define 	NET_DVR_GET_VIDEOOUTCFG_V30			1028		
#define 	NET_DVR_SET_VIDEOOUTCFG_V30			1029	

//OSD  (NET_DVR_SHOWSTRING_V30)
#define 	NET_DVR_GET_SHOWSTRING_V30			1030		
#define 	NET_DVR_SET_SHOWSTRING_V30			1031

//Exception  (NET_DVR_EXCEPTION_V30)
#define 	NET_DVR_GET_EXCEPTIONCFG_V30		1034		
#define 	NET_DVR_SET_EXCEPTIONCFG_V30		1035

//RS232  (NET_DVR_RS232CFG_V30)
#define 	NET_DVR_GET_RS232CFG_V30			1036		
#define 	NET_DVR_SET_RS232CFG_V30			1037

//Encoding  (NET_DVR_COMPRESSIONCFG_V30)
#define     NET_DVR_GET_COMPRESSCFG_V30	        1040		
#define     NET_DVR_SET_COMPRESSCFG_V30	        1041		

//RS485  (NET_DVR_DECODERCFG_V30)
#define     NET_DVR_GET_DECODERCFG_V30		    1042		//Get Decoder Parameters
#define     NET_DVR_SET_DECODERCFG_V30		    1043		//Set Decoder parameters

//Preview  (NET_DVR_PREVIEWCFG_V30)
#define     NET_DVR_GET_PREVIEWCFG_V30		    1044		//Get Preview Parameters
#define     NET_DVR_SET_PREVIEWCFG_V30		    1045		//Set Preview Parameters

//AUX Preview (NET_DVR_PREVIEWCFG_AUX_V30)
#define     NET_DVR_GET_PREVIEWCFG_AUX_V30		1046		//Get AUX Preview Parameters
#define     NET_DVR_SET_PREVIEWCFG_AUX_V30		1047		//Set AUX Preview Parameters

//IP Channel Configuration (NET_DVR_IPPARACFG)
#define     NET_DVR_GET_IPPARACFG               1048        //Get IP Channel Configuration info 
#define     NET_DVR_SET_IPPARACFG               1049        //Set IP Channel Configuration info 

//IP Alarm In Configuration (NET_DVR_IPALARMINCFG)
#define     NET_DVR_GET_IPALARMINCFG            1050        //Get IP Alarm In Configuration info
#define     NET_DVR_SET_IPALARMINCFG            1051        //Set IP Alarm In Configuration info

//IP Alarm Out Configuration (NET_DVR_IPALARMOUTCFG)
#define     NET_DVR_GET_IPALARMOUTCFG           1052        //Get IP Alarm Out Configuration info  
#define     NET_DVR_SET_IPALARMOUTCFG           1053        //Set IP Alarm Out Configuration info 

//HD management Configuration (NET_DVR_HDCFG)
#define     NET_DVR_GET_HDCFG			        1054	    //Get HD management Configuration
#define     NET_DVR_SET_HDCFG			        1055	    //Get HD management Configuration

//HD Group Configuration (NET_DVR_HDGROUP_CFG)
#define     NET_DVR_GET_HDGROUP_CFG			    1056	    //Get HD Group Configuration Parameters
#define     NET_DVR_SET_HDGROUP_CFG			    1057	    //Set HD Group Configuration Parameters

//Device AudioTalk Configuration(NET_DVR_COMPRESSION_AUDIO)
#define     NET_DVR_GET_COMPRESSCFG_AUD                1058        //Get AudioTalk Configuration Parameters
#define     NET_DVR_SET_COMPRESSCFG_AUD                1059        //Set AudioTalk Configuration Parameters
/***************************DS9000 New Commands(_V30) end *****************************/

/*************************Parameter Configure Commands end*******************************/


/*******************Return Value of File&Log Query API*************************/
#define NET_DVR_FILE_SUCCESS		1000	//Get log information
#define NET_DVR_FILE_NOFIND			1001	//no log
#define NET_DVR_ISFINDING			1002	//on searching
#define	NET_DVR_NOMOREFILE			1003	//no more files
#define	NET_DVR_FILE_EXCEPTION		1004	//Error on log query

/*********************Callback Function Type begin************************/
#define COMM_ALARM					0x1100	//8000 Upload alarm message
#define	COMM_TRADEINFO				0x1500  //ATM DVR transaction information 

#define COMM_ALARM_V30				0x4000	//9000 upload alarm message
#define COMM_IPCCFG			        0x4001	//9000 IPC configuration changed, upload with push mode


/*************Operation Exception**********************/
#define EXCEPTION_EXCHANGE			0x8000	//Network user exception
#define EXCEPTION_AUDIOEXCHANGE		0x8001	//Network voice talk exception
#define EXCEPTION_ALARM				0x8002	//Alarm exception
#define EXCEPTION_PREVIEW			0x8003	//Network preview exception
#define EXCEPTION_SERIAL			0x8004	//Transparent channel exception
#define EXCEPTION_RECONNECT			0x8005	//Network preview reconnected
#define EXCEPTION_ALARMRECONNECT	0x8006	//Alarm reconnected
#define EXCEPTION_SERIALRECONNECT	0x8007	//Transparent channel reconnected
#define EXCEPTION_PLAYBACK	        0x8010	//Playback exception
#define EXCEPTION_DISKFMT	        0x8011	//Hard Disk format exception
#define EXCEPTION_PASSIVEDECODE     0x8012  //Passive decode exception
/********************Preview Callback Function*********************/
#define NET_DVR_SYSHEAD			1	//System header
#define NET_DVR_STREAMDATA		2	//stream data
#define NET_DVR_AUDIOSTREAMDATA	3	//Audio Stream data
#define NET_DVR_STD_VIDEODATA	4	//Standard video stream data
#define NET_DVR_STD_AUDIODATA	5	//Standard audio stream data 

/* Device model*/
#define DVR							1				/*Undefined DVR*/
#define ATMDVR						2				/*atm dvr*/
#define DVS							3				/*DVS*/
#define DEC							4				/* 6001D */
#define ENC_DEC						5				/* 6001F */
#define DVR_HC						6				/*8000HC*/
#define DVR_HT						7				/*8000HT*/
#define DVR_HF						8				/*8000HF*/
#define DVR_HS						9				/* 8000HS DVR(no audio) */
#define DVR_HTS						10              /* 8016HTS DVR(no audio) */
#define DVR_HB						11              /* HB DVR(SATA HD) */
#define DVR_HCS						12              /* 8000HCS DVR */
#define DVS_A						13              /* DVS with ATA Hard disk */
#define DVR_HC_S					14              /* 8000HC-S */
#define DVR_HT_S					15              /* 8000HT-S */
#define DVR_HF_S					16              /* 8000HF-S */
#define DVR_HS_S					17              /* 8000HS-S */
#define ATMDVR_S					18              /* ATM-S */
#define LOWCOST_DVR					19				/*7000H Series*/
#define DEC_MAT						20              /*Multichannel Decoder*/
#define DVR_MOBILE					21				/* mobile DVR */                 
#define DVR_HD_S					22              /* 8000HD-S */
#define DVR_HD_SL					23				/* 8000HD-SL */
#define DVR_HC_SL					24				/* 8000HC-SL */
#define DVR_HS_ST					25				/* 8000HS_ST */
#define DVS_HW						26              /* 6000HW */
#define DS630X_D					27				/*DS630X_D*/
#define IPCAM						30				/*IP Camera*/
#define MEGA_IPCAM					31				/*Mega Pixels IP Camera*/
#define IPCAM_X62MF					32				/*862MF IP Camera*/
#define IPDOME                      40     			/*IP Speed Dome*/
#define IPDOME_MEGA200              41     			/*Mega Pixels IP Dome(2 million)*/
#define IPDOME_MEGA130              42     			/*Mega Pixels IP Dome(1.3 million)*/
#define IPMOD						50				/*IP Model*/
#define DS71XX_H					71				/* DS71XXH_S */
#define DS72XX_H_S					72				/* DS72XXH_S */
#define DS73XX_H_S					73				/* DS73XXH_S */
#define DS76XX_H_S					76				/* DVR,e.g. DS7604_HI_S */
#define DS76XX_N_S					77				/* NVR,e.g. DS7604_NI_S */
#define DS81XX_HS_S					81				/* DS81XX_HS_S */
#define DS81XX_HL_S					82				/* DS81XX_HL_S */
#define DS81XX_HC_S					83				/* DS81XX_HC_S */
#define DS81XX_HD_S					84				/* DS81XX_HD_S */
#define DS81XX_HE_S					85				/* DS81XX_HE_S */
#define DS81XX_HF_S					86				/* DS81XX_HF_S */
#define DS81XX_AH_S					87				/* DS81XX_AH_S */
#define DS81XX_AHF_S				88				/* DS81XX_AHF_S */
#define DS90XX_HF_S		            90              /*DS90XX_HF_S*/
#define DS91XX_HF_S					91              /*DS91XX_HF_S*/
#define DS91XX_HD_S					92              /*91XXHD-S(MD)*/
#define DS_B10_XY                   100             /*视频综合平台设备型号(X:编码板片数，Y:解码板片数)*/
#define DS_6504HF_B10               101             /*视频综合平台内部编码器*/
#define DS_6504D_B10                102             /*视频综合平台内部解码器*/

#define DS_65XXHC					105				//65XXHC DVS
#define DS_65XXHC_S					106				//65XXHC-SATA DVS
#define DS_65XXHF					107				//65XXHF DVS
#define DS_65XXHF_S					108				//65XXHF-SATA DVS
/**********************Device model end***********************/

/*************************************************
Parameters configuration structure(_V30 is for 9000)
**************************************************/

/////////////////////////////////////////////////////////////////////////
//Time correction structure
typedef struct
{
	unsigned int dwYear;		//Year
	unsigned int dwMonth;		//Month
	unsigned int dwDay;		//Day
	unsigned int dwHour;		//Hour
	unsigned int dwMinute;		//Minute
	unsigned int dwSecond;		//Second
}NET_DVR_TIME, *LPNET_DVR_TIME;

//Time Segment(Sub structure)
typedef struct
{
	//Start
    unsigned char byStartHour;
	unsigned char byStartMin;
	//End
	unsigned char byStopHour;
	unsigned char byStopMin;
}NET_DVR_SCHEDTIME, *LPNET_DVR_SCHEDTIME;

/*Handling way of Alarm & Exception*/
#define NOACTION			0x0				/*Don't Respond*/
#define WARNONMONITOR		0x1				/*Warning on Monitor*/
#define WARNONAUDIOOUT		0x2				/*Audio Warning*/
#define UPTOCENTER			0x4				/*Upload to center*/
#define TRIGGERALARMOUT		0x8				/*Trigger Alarm Output*/

//Handle Alarm & Exception
typedef struct
{
	unsigned int	dwHandleType;	/*Way to handle, result of operation OR*/
	/*0x00: No response*/
	/*0x01: Alarm on monitor*/
	/*0x02: Audio Alarm*/
	/*0x04: Upload to center*/
	/*0x08: Trigger alarm output*/
	/*0x10: Grab Jpeg image and EMail it*/
	unsigned char byRelAlarmOut[MAX_ALARMOUT_V30];
    //Alarm out channel, 1 means trigger this channel
}NET_DVR_HANDLEEXCEPTION_V30, *LPNET_DVR_HANDLEEXCEPTION_V30;

//Handle Alarm & Exception (sub structure)
typedef struct
{
	unsigned int	dwHandleType;			/*Way to handle, result of operation OR*/
	/*0x00: No response*/
	/*0x01: Alarm on monitor*/
	/*0x02: Audio Alarm*/
	/*0x04: Upload to center*/
	/*0x08: Trigger alarm output*/
	/*0x10: Grab Jpeg image and EMail it*/
	unsigned char byRelAlarmOut[MAX_ALARMOUT]; //Alarm out channel, 1 means trigger this channel
}NET_DVR_HANDLEEXCEPTION, *LPNET_DVR_HANDLEEXCEPTION;

//DVR Device Parameters
typedef struct
{
	unsigned int dwSize;
	unsigned char sDVRName[NAME_LEN];     //DVR Name
	unsigned int dwDVRID;				//DVR ID for IR Control //V1.4(0-99), V1.5(0-255)
	unsigned int dwRecycleRecord;		//cycle Record,0:No cycle; 1:cycle
	//The variable below is read only
	unsigned char sSerialNumber[SERIALNO_LEN];	//SN
	unsigned int dwSoftwareVersion;			//software version,high 16 bits is main version, low 16 bits is hypo-version
	unsigned int dwSoftwareBuildDate;			//build date,0xYYYYMMDD
	unsigned int dwDSPSoftwareVersion;		    //DSP software version, high 16 bits is main version, low 16 bits is hypo-version
	unsigned int dwDSPSoftwareBuildDate;		// DSP software build date,0xYYYYMMDD
	unsigned int dwPanelVersion;				// Front panel version, high 16 bits is main version, low 16 bits is hypo-version
	unsigned int dwHardwareVersion;	// Hardware version, high 16 bits is main version, low 16 bits is hypo-version
	unsigned char byAlarmInPortNum;		//Number of alarm input
	unsigned char byAlarmOutPortNum;		//Number of alarm output
	unsigned char byRS232Num;			//Number of DVR RS232 ports
	unsigned char byRS485Num;			//Number of DVR RS485 ports
	unsigned char byNetworkPortNum;		//Number of network ports
	unsigned char byDiskCtrlNum;			//Number of DVR hardware controllers
	unsigned char byDiskNum;				//DVR Hard disk number
	unsigned char byDVRType;				//DVR Model, 1:DVR 2:ATM DVR 3:DVS ......
	unsigned char byChanNum;				//DVR channel number
	unsigned char byStartChan;			//First channel's No. e.g., DVS-1,DVR - 1
	unsigned char byDecordChans;			//Number of decoding channels
	unsigned char byVGANum;				//Number of VGA ports
	unsigned char byUSBNum;				//Number of USB ports
    unsigned char byAuxoutNum;			//Number of AUX ports
    unsigned char byAudioNum;			//Number of audio ports
    unsigned char byIPChanNum;			//Maximum number of IP channels
}NET_DVR_DEVICECFG, *LPNET_DVR_DEVICECFG;

/*
IP Address
*/
typedef struct
{		
	char	sIpV4[16];						/* IPv4 Address */
	unsigned char	byRes[128];						/* Reserved */
}NET_DVR_IPADDR, *LPNET_DVR_IPADDR;


/*
Network structure (9000)
*/
typedef struct 
{
	NET_DVR_IPADDR	struDVRIP;          					//DVR IP address
	NET_DVR_IPADDR	struDVRIPMask;							//DVR IP Mask
	unsigned int	dwNetInterface;   								//Network port, 1-10MBase-T 2-10MBase-T full duplex  3-100MBase-TX 4-100M full duplex  5-10M/100M adaptive
	unsigned short	wDVRPort;										//Port
	unsigned short	wMTU;											//MTU, 1500 by default。
	unsigned char	byMACAddr[MACADDR_LEN];							//MAC address
}NET_DVR_ETHERNET_V30, *LPNET_DVR_ETHERNET_V30;

/*
Network data structure(Sub structure)
*/
typedef struct
{
	char sDVRIP[16];          //DVR IP address
	char sDVRIPMask[16];      //DVR IP Mask
	unsigned int dwNetInterface;     //Network interface 1-10MBase-T 2-10MBase-T full duplex 3-100MBase-TX 4-100M full duplex 5-10M/100M adaptive
	unsigned short wDVRPort;		      //Port
	unsigned char byMACAddr[MACADDR_LEN]; //Mac address
}NET_DVR_ETHERNET;

//pppoe structure
typedef struct 
{
	unsigned int	dwPPPOE;										//0-disable,1-enable
	unsigned char	sPPPoEUser[NAME_LEN];							//PPPoE user name
	char	sPPPoEPassword[PASSWD_LEN];						// PPPoE password
	NET_DVR_IPADDR	struPPPoEIP;							//PPPoE IP address
}NET_DVR_PPPOECFG, *LPNET_DVR_PPPOECFG;

//Network Configure Structure (9000DVR extended)
typedef struct
{	
	unsigned int dwSize;
	NET_DVR_ETHERNET_V30	struEtherNet[MAX_ETHERNET];		//Network Port
	NET_DVR_IPADDR	struRes1[2];							/*Reserved*/
	NET_DVR_IPADDR	struAlarmHostIpAddr;					/*IP address of Alarm Host */
	unsigned short	wRes2[2];										/* Reserved */
	unsigned short	wAlarmHostIpPort;								/* Port of Alarm Host */
	unsigned char    byUseDhcp;                                      /* Enable DHCP or not 0xff-invalid 0-disable 1-enable*/
	unsigned char	byRes3;
	NET_DVR_IPADDR	struDnsServer1IpAddr;					/* IP address of DNS 1 */
	NET_DVR_IPADDR	struDnsServer2IpAddr;					/* IP address of DNS 2 */
	unsigned char	byIpResolver[MAX_DOMAIN_NAME];					/* IP address or domain name of analysis server*/
	unsigned short	wIpResolverPort;								/* Port of IP analysis server*/
	unsigned short	wHttpPortNo;									/* HTTP port */
	NET_DVR_IPADDR	struMulticastIpAddr;					/* Multicast group address */
	NET_DVR_IPADDR	struGatewayIpAddr;						/* Gateway address */
	NET_DVR_PPPOECFG struPPPoE;	
    unsigned char    byRes[64];
} NET_DVR_NETCFG_V30, *LPNET_DVR_NETCFG_V30;

//Network Configure Structure
typedef struct
{
	unsigned int dwSize;
	NET_DVR_ETHERNET struEtherNet[MAX_ETHERNET];		/* etwork Port */
	char sManageHostIP[16];		//IP address of remote management host
	unsigned short wManageHostPort;		//Port of remote management Host
	char sIPServerIP[16];       //Address of IPServer
	char sMultiCastIP[16];     //Multicast group address
	char sGatewayIP[16];       	//Gateway address
	char sNFSIP[16];			//IP address of NFS host
	unsigned char sNFSDirectory[PATHNAME_LEN];//NFS directory
	unsigned int dwPPPOE;				//0-disable,1-enable
	unsigned char sPPPoEUser[NAME_LEN];	//PPPoE username
	char sPPPoEPassword[PASSWD_LEN];// PPPoE password
	char sPPPoEIP[16];			//PPPoE IP address (read only)
	unsigned short wHttpPort;				//HTTP port
}NET_DVR_NETCFG, *LPNET_DVR_NETCFG;

//Channel Image structure
//Motion detection structure(sub structure)(9000 extended)
typedef struct 
{
	unsigned char byMotionScope[64][96];									/*Motion detection area,0-96 bits stand for 64 lines and there are 96*64 small areas, 1--it is motion detection area,0--not*/
	unsigned char byMotionSensitive;										/*sensitive grade of motion detection, 0 - 5(5 is most sensitive), oxff turn off*/
	unsigned char byEnableHandleMotion;									/* Process motion alarm  0－No 1－Yes*/
	unsigned char byPrecision;											/* the precision of motion detection : 0--16*16, 1--32*32, 2--64*64 ... */
	char reservedData;	
	NET_DVR_HANDLEEXCEPTION_V30 struMotionHandleType;				/* The way to process */
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]; /*Guard time*/
	unsigned char byRelRecordChan[MAX_CHANNUM_V30];									/* Channel triggered to record*/
}NET_DVR_MOTION_V30, *LPNET_DVR_MOTION_V30;

//Motion detection structure(sub structure)
typedef struct 
{
	unsigned char byMotionScope[18][22];	/*motion detection area, 22*18 blocks in total, 1--it's motion detection area, 0--not*/
	unsigned char byMotionSensitive;		/*sensitive grade of motion detection, 0 - 5(5 is most sensitive), oxff turn off*/
	unsigned char byEnableHandleMotion;	/* process motion detection or not */
	char reservedData[2];
	NET_DVR_HANDLEEXCEPTION strMotionHandleType;	/* methoder to process alarm */
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//Guard time
	unsigned char byRelRecordChan[MAX_CHANNUM];				//Channel triggered to record*/
}NET_DVR_MOTION, *LPNET_DVR_MOTION;

//Tamper Alarm (sub structure)(9000 extended)  area size: 704*576
typedef struct 
{
	unsigned int dwEnableHideAlarm;				/* Enable tamper alarm or not ,0-disable,1-low sensitivity 2-Middle 3-High*/
	unsigned short wHideAlarmAreaTopLeftX;			/* X-coordinate of tamper area */
	unsigned short wHideAlarmAreaTopLeftY;			/* Y-coordinate of tamper area */
	unsigned short wHideAlarmAreaWidth;				/* Width of tampered area */
	unsigned short wHideAlarmAreaHeight;				/* Height of tampered area*/
	NET_DVR_HANDLEEXCEPTION_V30 strHideAlarmHandleType;	/* Way to handle alarm */
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30];//Guard time
}NET_DVR_HIDEALARM_V30, *LPNET_DVR_HIDEALARM_V30;

//Tamper Alarm (sub structure) area size: 704*576
typedef struct 
{
	unsigned int dwEnableHideAlarm;				/* Enable tamper alarm or not ,0-disable,1-low sensitivity 2-Middle 3-High*/
	unsigned short wHideAlarmAreaTopLeftX;			/* X-coordinate of tamper area */
	unsigned short wHideAlarmAreaTopLeftY;			/* Y-coordinate of tamper area */
	unsigned short wHideAlarmAreaWidth;				/* Width of tampered area */
	unsigned short wHideAlarmAreaHeight;				/* Height of tampered area*/
	NET_DVR_HANDLEEXCEPTION strHideAlarmHandleType;	/* Way to handle the alarm */
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//Guard time
}NET_DVR_HIDEALARM, *LPNET_DVR_HIDEALARM;

//Signal Lost Alarm(sub structure)(9000 extended)
typedef struct 
{
	unsigned char byEnableHandleVILost;	/* Respond the alarm or not */
	NET_DVR_HANDLEEXCEPTION_V30 strVILostHandleType;	/* Way to respond*/
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30];//Guard time
}NET_DVR_VILOST_V30, *LPNET_DVR_VILOST_V30;

//Signal Lost Alarm(sub structure)
typedef struct 
{
	unsigned char byEnableHandleVILost;	/* Respond the alarm or not */
	NET_DVR_HANDLEEXCEPTION strVILostHandleType;	/* Way to respond*/
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//Guard time
}NET_DVR_VILOST, *LPNET_DVR_VILOST;

//Tampered Area(sub structure)
typedef struct 
{
	unsigned short wHideAreaTopLeftX;				/* X-coordinate of tamper area */
	unsigned short wHideAreaTopLeftY;				/* Y-coordinate of tamper area */
	unsigned short wHideAreaWidth;				/* Width of tampered area */
	unsigned short wHideAreaHeight;				/* Height of tampered area*/
}NET_DVR_SHELTER, *LPNET_DVR_SHELTER;

typedef struct
{
	unsigned char byBrightness;  	/*Brightness,0-255*/
	unsigned char byContrast;    	/*contrast,0-255*/
	unsigned char bySaturation;  	/*Saturation,0-255*/
	unsigned char byHue;    			/*Hue,0-255*/
}NET_DVR_COLOR, *LPNET_DVR_COLOR;


//Video Structure(9000 extended)
typedef struct
{
	unsigned int dwSize;
	unsigned char sChanName[NAME_LEN];
	unsigned int dwVideoFormat;	/* Read only, Video Standard 1-NTSC 2-PAL*/
	NET_DVR_COLOR struColor;//	image parameter
	char reservedData [60];/*Reserved*/
	//Display Channel Name
	unsigned int dwShowChanName; // Display channel name or not,0-no,1-display size = 704*576
	unsigned short wShowNameTopLeftX;				/* X-coordinate of display position */
	unsigned short wShowNameTopLeftY;				/* Y-coordinate of display position  */
	//Signal lost Alarm
	NET_DVR_VILOST_V30 struVILost;
	NET_DVR_VILOST_V30 struRes;		/*Reserved*/
	//Motion detection
	NET_DVR_MOTION_V30 struMotion;
	//Tamper alarm
	NET_DVR_HIDEALARM_V30 struHideAlarm;
	//Tampered Area 704*576
	unsigned int dwEnableHide;		/* Enable Tamper Alarm ,0-disable,1-enable*/
	NET_DVR_SHELTER struShelter[MAX_SHELTERNUM];
	//OSD
	unsigned int dwShowOsd;		// Display OSD or not,0-No OSD,1-Display Area for display: 704*576
	unsigned short wOSDTopLeftX;				/* X-coordinate of OSD */
	unsigned short wOSDTopLeftY;				/* Y-coordinate of OSD*/
	unsigned char byOSDType;					/* OSD Type (format of Year/Month/Day) */
	/* 0: XXXX-XX-XX Year Month Day */
	/* 1: XX-XX-XXXX Month Day Year */
	/* 2: XXXXYearXXNonthXXDay */
	/* 3: XXMonthXXDayXXXXYear */
	/* 4: XX-XX-XXXX Day Month Year*/
	/* 5: XXDayXXMonthXXXXYear */
	unsigned char byDispWeek;				/* display Week */
	unsigned char byOSDAttrib;				/* OSD attribute: Transparent，Flash */
	/* 0: No OSD */
	/* 1: Transparent,Flash */
	/* 2: Transparent,not Flash */
	/* 3: Flash,not Transparent */
	/* 4: not Transparent, not Flash */
    unsigned char byHourOSDType;				/* :24-Hour system,12-Hour system */
	unsigned char byRes[64];
}NET_DVR_PICCFG_V30, *LPNET_DVR_PICCFG_V30;

//Video Structure(SDK_V14 extended)
typedef struct 
{
	unsigned int dwSize;
	unsigned char sChanName[NAME_LEN];
	unsigned int dwVideoFormat;	/* Read only, Video Standard 1-NTSC 2-PAL*/
	unsigned char byBrightness;  	/*Brightness,0-255*/
	unsigned char byContrast;    	/*contrast,0-255*/
	unsigned char bySaturation;  	/*Saturation,0-255*/
	unsigned char byHue;    			/*Hue,0-255*/
	//Display Channel Name
	unsigned int dwShowChanName; // Display channel name or not,0-no,1-display size = 704*576
	unsigned short wShowNameTopLeftX;				/* X-coordinate of display position */
	unsigned short wShowNameTopLeftY;				/* Y-coordinate of display position  */
	//Signal lost Alarm
	NET_DVR_VILOST struVILost;
	//Motion Detection
	NET_DVR_MOTION struMotion;
	//Tamper Alarm
	NET_DVR_HIDEALARM struHideAlarm;
	//Tamper Area size: 704*576
	unsigned int dwEnableHide;		/* Enable Tamper Alarm ,0-disable,1-enable**/
	NET_DVR_SHELTER struShelter[MAX_SHELTERNUM];
	//OSD
	unsigned int dwShowOsd;				// Display OSD or not,0-No OSD,1-Display Area for display: 704*576
	unsigned short wOSDTopLeftX;				/* X-coordinate of OSD */
	unsigned short wOSDTopLeftY;				/* Y-coordinate of OSD*/
	unsigned char byOSDType;					/* OSD Type (format of Year/Month/Day) */
	/* 0: XXXX-XX-XX Year/Month/Day */
	/* 1: XX-XX-XXXX Month/Day/Year */
	/* 2: XXXXYearXXNonthXXDay */
	/* 3: XXMonthXXDayXXXXYear */
	/* 4: XX-XX-XXXX Day Month Year*/
	/* 5: XXDayXXMonthXXXXYear */
	unsigned char byDispWeek;				/* display Week */
	unsigned char byOSDAttrib;				/* OSD attribute: Transparent，Flash */
	/* 0: No OSD */
	/* 1: Transparent,Flash */
	/* 2: Transparent,not Flash */
	/* 3: Flash,not Transparent */
	/* 4: not Transparent, not Flash */
	unsigned char byHourOsdType;	//hour：0-24 hours，1-am/pm
}NET_DVR_PICCFG_EX, *LPNET_DVR_PICCFG_EX;

//Video Structure(SDK_V14 extended)
typedef struct 
{
	unsigned int dwSize;
	unsigned char sChanName[NAME_LEN];
	unsigned int dwVideoFormat;	/* Read only, Video Standard 1-NTSC 2-PAL*/
	unsigned char byBrightness;  	/*Brightness,0-255*/
	unsigned char byContrast;    	/*contrast,0-255*/
	unsigned char bySaturation;  	/*Saturation,0-255*/
	unsigned char byHue;    			/*Hue,0-255*/
	//Display Channel Name
	unsigned int dwShowChanName; // Display channel name or not,0-no,1-display size = 704*576
	unsigned short wShowNameTopLeftX;				/* X-coordinate of display position */
	unsigned short wShowNameTopLeftY;				/* Y-coordinate of display position  */
	//Signal lost Alarm
	NET_DVR_VILOST struVILost;
	//Motion Detection
	NET_DVR_MOTION struMotion;
	//Tamper Alarm
	NET_DVR_HIDEALARM struHideAlarm;
	//Tamper Area size: 704*576
	unsigned int dwEnableHide;		/* Enable Tamper Alarm ,0-disable,1-enable*/
	unsigned short wHideAreaTopLeftX;				/* X-coordinate of tampered area*/
	unsigned short wHideAreaTopLeftY;				/* Y-coordinate of tampered area */
	unsigned short wHideAreaWidth;				/* Width of tampered area */
	unsigned short wHideAreaHeight;				/* Height of tampered area */
	//OSD
	unsigned int dwShowOsd;				// Display OSD or not,0-No OSD,1-Display Area for display: 704*576
	unsigned short wOSDTopLeftX;				/* X-coordinate of OSD */
	unsigned short wOSDTopLeftY;				/* Y-coordinate of OSD*/
	unsigned char byOSDType;					/* OSD Type (format of Year/Month/Day) */
	/* 0: XXXX-XX-XX Year/Month/Day */
	/* 1: XX-XX-XXXX Month/Day/Year */
	/* 2: XXXXYearXXNonthXXDay */
	/* 3: XXMonthXXDayXXXXYear */
	/* 4: XX-XX-XXXX Day Month Year*/
	/* 5: XXDayXXMonthXXXXYear */
	unsigned char byDispWeek;				/* display Week */
	unsigned char byOSDAttrib;				/* OSD attribute: Transparent，Flash */
	/* 0: No OSD */
	/* 1: Transparent,Flash */
	/* 2: Transparent,not Flash */
	/* 3: Flash,not Transparent */
	/* 4: not Transparent, not Flash */
	char reservedData2;
}NET_DVR_PICCFG, *LPNET_DVR_PICCFG;

//Encoding Parameters(Sub Strut)(9000 extended)
typedef struct 
{
	unsigned char byStreamType;		//Stream type 0-video, 1-video&aduio, when it stands for compression parameters, the hightest bit stands for whether adopt encoding parameters
	unsigned char byResolution;  	//Resolution 0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF 5(reserved) 16-VGA(640*480) 17-UXGA(1600*1200) 18-SVGA (800*600)19-HD720p(1280*720)20-XVGA  21-HD900p
	unsigned char byBitrateType;		//Bitrate Type 0:VBR，1:CBR
	unsigned char byPicQuality;		//Image Quality 0-best 1-much better 2-better 3-Normal 4-worse 5-worst
	unsigned int dwVideoBitrate; 	//video bit rate 0-reserved 1-16K 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
	// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
	//if The highest bit(31 bit) is 1, it stands for user defined bit rate, 0-30 is the value of bit rate
	unsigned int dwVideoFrameRate;	//Frame rate 0-full; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;14-15; 15-18; 16-22;
	unsigned short  wIntervalFrameI;  //interval of I frame
	//2006-08-11 Add single P frame
	unsigned char  byIntervalBPFrame;//0-BBP frame; 1-BP frame; 2-P frame only.
	unsigned char  byres1;        //reserve
	unsigned char  byVideoEncType;   //Video Code Type: 0-hik 264;1-standard H264;2-standard MPEG4
	unsigned char  byAudioEncType;   //Audio Code Type: 0-OggVorbis
	unsigned char  byres[10];//reserve
}NET_DVR_COMPRESSION_INFO_V30, *LPNET_DVR_COMPRESSION_INFO_V30;

//Encoding Parameters (9000 extended)
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_COMPRESSION_INFO_V30 struNormHighRecordPara;    //Record, corresponding to 8000's nomal
	NET_DVR_COMPRESSION_INFO_V30 struRes;					//Reserved char reserveData[28];
    NET_DVR_COMPRESSION_INFO_V30 struEventRecordPara;       //Encoding parameters tiggered by Events
	NET_DVR_COMPRESSION_INFO_V30 struNetPara;               //network transfer
}NET_DVR_COMPRESSIONCFG_V30, *LPNET_DVR_COMPRESSIONCFG_V30;

//Encoding Parameters(Sub Strut)
typedef struct 
{
	unsigned char byStreamType;		//Stream type 0-video, 1-video&aduio, when it stands for compression parameters, the hightest bit stands for whether adopt encoding parameters
	unsigned char byResolution;  	//Resolution 0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF, 5-2QCIF(352X144)(for Mobile DVR)
	unsigned char byBitrateType;		//Bit rate type 0:VBR，1:CBR
	unsigned char  byPicQuality;		//Image Quality 0-best 1-much better 2-better 3-Normal 4-worse 5-worst
	unsigned int dwVideoBitrate; 	//video bit rate 0-reserved 1-16K(reserved) 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
							// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
							//if The highest bit(31 bit) is 1, it stands for user defined bit rate, 0-30 is the value of bit rate(MIN-32K MAX-8192K)。
	unsigned int dwVideoFrameRate;	//Frame rate 0-full; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
}NET_DVR_COMPRESSION_INFO, *LPNET_DVR_COMPRESSION_INFO;

//Encoding Parameters
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_COMPRESSION_INFO struRecordPara; //Record triggered by events
	NET_DVR_COMPRESSION_INFO struNetPara;	//Network transfer(reserved)
}NET_DVR_COMPRESSIONCFG, *LPNET_DVR_COMPRESSIONCFG;

//Encoding Parameters(Sub Strut)(extended) Add I Frame interval
typedef struct 
{
	unsigned char byStreamType;		//Stream type 0-video, 1-video&aduio,
	unsigned char byResolution; 		//Resolution 0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF, 5-2QCIF(352X144)(for Mobile DVR)
	unsigned char byBitrateType;		//Bit rate type 0:VBR，1:CBR
	unsigned char  byPicQuality;		//Image Quality 0-best 1-much better 2-better 3-Normal 4-worse 5-worst
	unsigned int dwVideoBitrate; 	//video bit rate 0-reserved 1-16K(reserved) 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
	// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
							//if The highest bit(31 bit) is 1, it stands for user defined bit rate, 0-30 is the value of bit rate(MIN-32K MAX-8192K)。
	unsigned int dwVideoFrameRate;	//Frame rate 0-full; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20,14-15, 15-18, 16-22;
	unsigned short  wIntervalFrameI;  //I Frame interval
	//2006-08-11 Add single P frame
	unsigned char  byIntervalBPFrame;//0-BBP frame; 1-BP frame; 2-P frame only.
	unsigned char  byRes;
}NET_DVR_COMPRESSION_INFO_EX, *LPNET_DVR_COMPRESSION_INFO_EX;

//Encoding Parameters (extended)
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_COMPRESSION_INFO_EX struRecordPara; //Record
	NET_DVR_COMPRESSION_INFO_EX struNetPara;	//Netword Transfer
}NET_DVR_COMPRESSIONCFG_EX, *LPNET_DVR_COMPRESSIONCFG_EX;


//Parameters Configure of Recording in Time segment (Sub Strut)
typedef struct 
{
	NET_DVR_SCHEDTIME struRecordTime;
	unsigned char byRecordType;	//0:Time Record，1:Motion detection，2:Alarm record，3:Motion|alarm，4:Motion&Alarm, 5:Triggered by Commands, 6: Intelligent Record
	char reservedData[3];
}NET_DVR_RECORDSCHED, *LPNET_DVR_RECORDSCHED;

//Record All-day 
typedef struct 
{
	unsigned short wAllDayRecord;				/* Enable record all-day or not;0-disable,1-enable*/
	unsigned char byRecordType;				//0:Time Record，1:Motion detection，2:Alarm record，3:Motion|alarm，4:Motion&Alarm, 5:Triggered by Commands, 6: Intelligent Record
	char reservedData;
}NET_DVR_RECORDDAY, *LPNET_DVR_RECORDDAY;

//Recording Parameters (9000 extended)
typedef struct 
{
	unsigned int	dwSize;
	unsigned int	dwRecord;  						/*Record or not 0-not 1-Record*/
	NET_DVR_RECORDDAY	struRecAllDay[MAX_DAYS];
	NET_DVR_RECORDSCHED	struRecordSched[MAX_DAYS][MAX_TIMESEGMENT_V30];
	unsigned int	dwRecordTime;					/* post record time  0-5Seconds， 1-20Seconds， 2-30Seconds， 3-1 Minutes， 4-2Minutes，， 5-5Minutes，， 6-10Minutes，*/
	unsigned int	dwPreRecordTime;				/* Pre-record time 0-disable 1-5Seconds 2-10Seconds 3-15Seconds 4-20Seconds 5-25Seconds 6-30Seconds 7-0xffffffff */
	unsigned int	dwRecorderDuration;				/*  */
	unsigned char	byRedundancyRec;				/*Redundancy record to backup important data：0/1*/
	unsigned char	byAudioRec;						/*Record audio or not*/
	unsigned char	byReserve[10];
}NET_DVR_RECORD_V30, *LPNET_DVR_RECORD_V30;

//Recording Parameters
typedef struct 
{
	unsigned int dwSize;
	unsigned int dwRecord;  	/*Record or not 0-not 1-Record*/
	NET_DVR_RECORDDAY struRecAllDay[MAX_DAYS];
	NET_DVR_RECORDSCHED struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
	unsigned int dwRecordTime;		/* Pre-record time*/
	unsigned int dwPreRecordTime;	/* Pre-record time 0-disable 1-5Seconds 2-10Seconds 3-15Seconds 4-20Seconds 5-25Seconds 6-30Seconds 7-0xffffffff (A.F.A.P)*/
}NET_DVR_RECORD, *LPNET_DVR_RECORD;

//PTZ protocol structure configuration
typedef struct
{ 
    unsigned int dwType;               /*Type value of decoder, increase from 1 by degrees*/
    unsigned char  byDescribe[DESC_LEN]; /*Description of decoder, same with 8000*/
}NET_DVR_PTZ_PROTOCOL;

typedef struct
{    
    unsigned int   dwSize;
    NET_DVR_PTZ_PROTOCOL struPtz[PTZ_PROTOCOL_NUM];/*200 PTZ protocols in total*/    
    unsigned int   dwPtzNum;           /*Number of valid ptz protocol，Start from 0*/
    unsigned char    byRes[8];
}NET_DVR_PTZCFG, *LPNET_DVR_PTZCFG;

#define IPC_PROTOCOL_NUM      50   //max number of ip camera protocol

//PTZ protocol structure configuration
typedef struct tagNET_DVR_PROTO_TYPE
{ 
    unsigned int dwType;               /*Type value of ip camera protocol, increase from 0 by degrees*/
    unsigned char  byDescribe[DESC_LEN]; /*Description of ip camera protocol, same with 8000*/
}NET_DVR_PROTO_TYPE;

typedef struct
{    
    unsigned int   dwSize;
    NET_DVR_PROTO_TYPE struProto[IPC_PROTOCOL_NUM];/*200 PTZ protocols in total*/    
    unsigned int   dwProtoNum;           /*Number of valid ptz protocol，Start from 0*/
    unsigned char    byRes[8];
}NET_DVR_IPC_PROTO_LIST, *LPNET_DVR_IPC_PROTO_LIST;
NET_DVR_API BOOL __stdcall NET_DVR_GetIPCProtoList(int lUserID, NET_DVR_IPC_PROTO_LIST *pProtoList);
/***************************PTZ Protocol(end)******************************/

//PTZ configuration (9000 extended)
typedef struct 
{
	unsigned int dwSize;
	unsigned int dwBaudRate;//Baud rate(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;
	unsigned char byDataBit;// Data bit 0－5Seconds，1－6bit，2－7bit，3－8bit;
	unsigned char byStopBit;// Stop bit 0－1bit，1－2bit;
	unsigned char byParity;// Parity 0－No parity，1－odd，2－even;
	unsigned char byFlowcontrol;// flow control: 0－None，1－software ,2-Hardware
	unsigned short wDecoderType;//Decoder Type, corresponding to PTZ list
	unsigned short wDecoderAddress;	/*Decoder address:0 - 255*/
	unsigned char bySetPreset[MAX_PRESET_V30];		/* Configure Preset or not,0-No,1-Yes*/
	unsigned char bySetCruise[MAX_CRUISE_V30];		/* Configure Cruise or not: 0-No,1-Yes */
	unsigned char bySetTrack[MAX_TRACK_V30];		    /* Configure Track or not,0-No,1-Yes*/
}NET_DVR_DECODERCFG_V30, *LPNET_DVR_DECODERCFG_V30;

//PTZ decoder configuration
typedef struct 
{
	unsigned int dwSize;
	unsigned int dwBaudRate;//Baud rate(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;
	unsigned char byDataBit;// Data bit 0－5bit，1－6bit，2－7bit，3－8bit;
	unsigned char byStopBit;// Stop bit 0－1bit，1－2bit;
	unsigned char byParity;// Parity 0－No parity，1－odd，2－even;
	unsigned char byFlowcontrol;// Flow control: 0－None，1－software ,2-Hardware

	unsigned short wDecoderType;      //Decoder Type, 0－YouLi，1－LiLin-1016，2－LiLin-820，3－Pelco-p，4－DM DynaColor，5－HD600，6－JC-4116，7－Pelco-d WX，8－Pelco-d PICO
	unsigned short wDecoderAddress;	/*Decoder Address:0 - 255*/
	unsigned char bySetPreset[MAX_PRESET];		/* Configure Preset or not,0-No,1-Yes*/
	unsigned char bySetCruise[MAX_CRUISE];		/* Configure Cruise or not: 0-No,1-Yes */
	unsigned char bySetTrack[MAX_TRACK];			 /* Configure Track or not,0-No,1-Yes*/
}NET_DVR_DECODERCFG, *LPNET_DVR_DECODERCFG;

//ppp parameters configuration(Sub Struct)
typedef struct 
{
	NET_DVR_IPADDR struRemoteIP;	//Remote IP
	NET_DVR_IPADDR struLocalIP;		//Local IP
	char sLocalIPMask[16];			//Local Mask
	unsigned char sUsername[NAME_LEN];		/* Username */
	unsigned char sPassword[PASSWD_LEN];		/* Password */
	unsigned char byPPPMode;					//PPP mode, 0－active，1－passive
	unsigned char byRedial;					//Callback or not ：0-No,1-Yes
	unsigned char byRedialMode;				//Callback,0-user specified,1-preseted number
	unsigned char byDataEncrypt;				//Encrypt Data ,0-No,1-Yes
	unsigned int dwMTU;					//MTU
	char sTelephoneNumber[PHONENUMBER_LEN];   //Telephone number
}NET_DVR_PPPCFG_V30, *LPNET_DVR_PPPCFG_V30;

//ppp parameters configuration(Sub Struct)
typedef struct 
{
	char sRemoteIP[16];				//Remote IP
	char sLocalIP[16];				//Local IP
	char sLocalIPMask[16];			//Local Mask
	unsigned char sUsername[NAME_LEN];		/* Username */
	unsigned char sPassword[PASSWD_LEN];		/* Password */
	unsigned char byPPPMode;					//PPP mode, 0－active，1－passive
	unsigned char byRedial;					//Callback or not ：0-No,1-Yes
	unsigned char byRedialMode;				//Callback,0-user specified,1-preseted number
	unsigned char byDataEncrypt;				//Encrypt Data ,0-No,1-Yes
	unsigned int dwMTU;					//MTU
	char sTelephoneNumber[PHONENUMBER_LEN];   //Telephone number
}NET_DVR_PPPCFG, *LPNET_DVR_PPPCFG;

//RS232 Configuration(9000 extended)
typedef struct
{
 	unsigned int dwBaudRate;//Baud rate(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;
	unsigned char byDataBit;// Data bit 0－5bit，1－6bit，2－7bit，3－8bit;
	unsigned char byStopBit;// Stop bit 0－1bit，1－2bit;
	unsigned char byParity;// Parity 0－No parity，1－odd，2－even;
	unsigned char byFlowcontrol;// Flow control: 0－None，1－software ,2-Hardware
    unsigned int dwWorkMode;   /* unsigned short mode，0－232 for PPP dial，1－232 for parameter control，2－for transparent channel */
}NET_DVR_SINGLE_RS232;

//RS232 Configuration(9000 extended)
typedef struct 
{
	unsigned int dwSize;
    NET_DVR_SINGLE_RS232 struRs232;
	unsigned char byRes[84];
	NET_DVR_PPPCFG_V30 struPPPConfig;
}NET_DVR_RS232CFG_V30, *LPNET_DVR_RS232CFG_V30;

//RS232 Configuration
typedef struct 
{
	unsigned int dwSize;
	unsigned int dwBaudRate;//Baud rate(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;
	unsigned char byDataBit;// Data bit 0－5bit，1－6bit，2－7bit，3－8bit;
	unsigned char byStopBit;// Stop bit 0－1bit，1－2bit;
	unsigned char byParity;// Parity 0－No parity，1－odd，2－even;
	unsigned char byFlowcontrol;// Flow control: 0－None，1－software ,2-Hardware
	unsigned int dwWorkMode;   /* unsigned short mode，0－232 for PPP dial，1－232 for parameter control，2－for transparent channel */
	NET_DVR_PPPCFG struPPPConfig;
}NET_DVR_RS232CFG, *LPNET_DVR_RS232CFG;

//Alarm Input Configuration(9000 extended)
typedef struct 
{
	unsigned int dwSize;
	unsigned char sAlarmInName[NAME_LEN];	/* Name */
	unsigned char byAlarmType;	            //Alarm Type,0:normally open,1:normally close
	unsigned char byAlarmInHandle;	        /* Handle alarm or not 0-No 1-Yes*/
    unsigned char byRes1[2];
	NET_DVR_HANDLEEXCEPTION_V30 struAlarmHandleType;	/* the Way to handle alarm  */
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30];//Guard time
	unsigned char byRelRecordChan[MAX_CHANNUM_V30];		//Channel triggered to record, 1--trigger
	unsigned char byEnablePreset[MAX_CHANNUM_V30];		/* Call preset or not 0-No,1-Yes*/
	unsigned char byPresetNo[MAX_CHANNUM_V30];			/* Preset No. One alarm input can trigger several presets, 0xff-disable。*/
	unsigned char byRes2[192];							/*Reserved*/
	unsigned char byEnableCruise[MAX_CHANNUM_V30];		/* Call Cruise or not 0-No,1-Yes*/
	unsigned char byCruiseNo[MAX_CHANNUM_V30];			/* Cruise No.*/
	unsigned char byEnablePtzTrack[MAX_CHANNUM_V30];		/* Call Track or not 0-No,1-Yes*/
	unsigned char byPTZTrack[MAX_CHANNUM_V30];			/* Track No. */
    unsigned char byRes3[16];
}NET_DVR_ALARMINCFG_V30, *LPNET_DVR_ALARMINCFG_V30;

//Alarm Input Configuration
typedef struct 
{
	unsigned int dwSize;
	unsigned char sAlarmInName[NAME_LEN];	/* Name */
	unsigned char byAlarmType;				//Alarm Type,0:normally open,1:normally close
	unsigned char byAlarmInHandle;			/* Handle alarm or not 0-No 1-Yes*/
	NET_DVR_HANDLEEXCEPTION struAlarmHandleType;	/* the Way to handle alarm  */
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//Guard time
	unsigned char byRelRecordChan[MAX_CHANNUM];		//Channel triggered to record, 1--trigger
	unsigned char byEnablePreset[MAX_CHANNUM];		/* Call preset or not 0-No,1-Yes*/
	unsigned char byPresetNo[MAX_CHANNUM];			/* Preset No. One alarm input can trigger several presets, set 0xff to disable。*/
	unsigned char byEnableCruise[MAX_CHANNUM];		/* Call Cruise or not 0-No,1-Yes*/
	unsigned char byCruiseNo[MAX_CHANNUM];			/* Cruise No.*/
	unsigned char byEnablePtzTrack[MAX_CHANNUM];		/* Call Track or not 0-No,1-Yes*/
	unsigned char byPTZTrack[MAX_CHANNUM];			/* Track No. */
}NET_DVR_ALARMINCFG, *LPNET_DVR_ALARMINCFG;


//Upload Alarm Information (9000 extended)
typedef struct 
{
	unsigned int dwAlarmType;/*0-sensor alarm;1-hard disk full;2-video lost;3-motion detection;4-hard disk unformatted;5-hard disk error;6-tampering detection;7-unmatched video output standard;8-illegal operation;9-video exception;0xa-record exception*/
	unsigned int dwAlarmInputNumber;/*Alarm input Port*/
	unsigned char byAlarmOutputNumber[MAX_ALARMOUT_V30];/*State of Alarm output channel，1--Triggered*/
	unsigned char byAlarmRelateChannel[MAX_CHANNUM_V30];/*channels triggered to record，1-recording, dwAlarmRelateChannel[0] is the first channel*/
	unsigned char byChannel[MAX_CHANNUM_V30];/*If the dwAlarmType is 2,3 or 6，it stands for channel，dwChannel[0] is the first channel*/
	unsigned char byDiskNumber[MAX_DISKNUM_V30];/*When dwAlarmType is 1,4 or 5, it stands for Hard Disk, dwDiskNumber[0] is the first disk*/
}NET_DVR_ALARMINFO_V30, *LPNET_DVR_ALARMINFO_V30;

typedef struct 
{
	unsigned int dwAlarmType;/*0-sensor alarm;1-hard disk full;2-video lost;3-motion detection;4-hard disk unformatted;5-hard disk error;6-tampering detection;7-unmatched video output standard;8-illegal operation;9-serial port status;0xa-GPS information(for mobile DVR)*/
	unsigned int dwAlarmInputNumber;/*/*Alarm input Port, When the dwAlarmType is 9, it stands for states of Serail port, 0-normal, -1-error*/
	unsigned int dwAlarmOutputNumber[MAX_ALARMOUT];/*State of Alarm output channel，1--Triggered*/
	unsigned int dwAlarmRelateChannel[MAX_CHANNUM];/*channels triggered to record，1-recording, dwAlarmRelateChannel[0] is the first channel*/
	unsigned int dwChannel[MAX_CHANNUM];/*If the dwAlarmType is 2,3 or 6，it stands for channel，dwChannel[0] is the first channel*/
	unsigned int dwDiskNumber[MAX_DISKNUM];/*When dwAlarmType is 1,4 or 5, it stands for Hard Disk, dwDiskNumber[0] is the first disk*/
}NET_DVR_ALARMINFO, *LPNET_DVR_ALARMINFO;




//////////////////////////////////////////////////////////////////////////////////////
//IP Camera Parameter
/* IP Device */
typedef struct 
{
    unsigned int dwEnable;				    /* Enable this device */
    unsigned char sUserName[NAME_LEN];		/* Username */
    unsigned char sPassword[PASSWD_LEN];	    /* Password */
    NET_DVR_IPADDR struIP;			/* IP address */
    unsigned short wDVRPort;			 	    /* Port */
    unsigned char byRes[34];					/* Reserved */
}NET_DVR_IPDEVINFO, *LPNET_DVR_IPDEVINFO;

/* IP Channel parameters */
typedef struct 
{
    unsigned char byEnable;					/* 0-Failed to connect IP device；1-Successfully；*/
    unsigned char byIPID;					/* ID of IP device, the range: 1 to MAX_IP_DEVICE */
    unsigned char byChannel;					/* Channel No. */
	unsigned char byres[33];					//reserved
} NET_DVR_IPCHANINFO, *LPNET_DVR_IPCHANINFO;

/* Struct of connecting IP device*/
typedef struct 
{
    unsigned int dwSize;			                            /* Struct Size */
    NET_DVR_IPDEVINFO  struIPDevInfo[MAX_IP_DEVICE];    /* IP Device */
    unsigned char byAnalogChanEnable[MAX_ANALOG_CHANNUM];        /* Enable analog channel or not，channel 1(low bit) to channel 32(high bit)，0-invalid; 1-valid */
    NET_DVR_IPCHANINFO struIPChanInfo[MAX_IP_CHANNEL];	/* IP Channel */    
}NET_DVR_IPPARACFG, *LPNET_DVR_IPPARACFG;

/* Alarm output channel */
typedef struct 
{
    unsigned char byIPID;					/* ID of IP device, the range: 1 to MAX_IP_DEVICE */
    unsigned char byAlarmOut;				/* Alarm output NO. */
    unsigned char byRes[18];					/* Reserved */
}NET_DVR_IPALARMOUTINFO, *LPNET_DVR_IPALARMOUTINFO;

/* IP Alarm output configuration */
typedef struct 
{
    unsigned int dwSize;												/*struct size */
	NET_DVR_IPALARMOUTINFO struIPAlarmOutInfo[MAX_IP_ALARMOUT];	/* IP alarm output */
}NET_DVR_IPALARMOUTCFG, *LPNET_DVR_IPALARMOUTCFG;

/* Alarm input parameters */
typedef struct 
{
    unsigned char byIPID;					/* ID of IP device, the range: 1 to MAX_IP_DEVICE */
    unsigned char byAlarmIn;					/* Alarm input NO. */
    unsigned char byRes[18];					/* Reserved */
}NET_DVR_IPALARMININFO, *LPNET_DVR_IPALARMININFO;

/* IP Alarm input configuration */
typedef struct 
{
    unsigned int dwSize;											 /*struct size */
    NET_DVR_IPALARMININFO struIPAlarmInInfo[MAX_IP_ALARMIN]; /* IP alarm input */
}NET_DVR_IPALARMINCFG, *LPNET_DVR_IPALARMINCFG;

//IP Camera alarm info
typedef struct 
{
    NET_DVR_IPDEVINFO  struIPDevInfo[MAX_IP_DEVICE];            /* IP Device */
    unsigned char byAnalogChanEnable[MAX_ANALOG_CHANNUM];                /* Enable analog channel or not，0-Enable; 1-Disable */
    NET_DVR_IPCHANINFO struIPChanInfo[MAX_IP_CHANNEL];	        /* IP Channel */
    NET_DVR_IPALARMININFO struIPAlarmInInfo[MAX_IP_ALARMIN];    /* IP Alarm input */
    NET_DVR_IPALARMOUTINFO struIPAlarmOutInfo[MAX_IP_ALARMOUT]; /* IP Alarm output */
}NET_DVR_IPALARMINFO, *LPNET_DVR_IPALARMINFO;

typedef enum _HD_STAT_
{
	HD_STAT_OK					=	0,  /* Normal */
	HD_STAT_UNFORMATTED			=	1,  /* Raw */
	HD_STAT_ERROR           	=	2,  /* Error */
	HD_STAT_SMART_FAILED    	=	3,  /* SMART State */
	HD_STAT_MISMATCH        	=	4,  /* Unmatched */
	HD_STAT_IDLE            	=	5,  /* Sleep*/
	NET_HD_STAT_OFFLINE     	=	6   /* Net Disk is off line */	
}HD_STAT;

//Configuration of local Hard Disk
typedef struct
{
    unsigned int dwHDNo;         /*Hard Disk No. (0~MAX_DISKNUM_V30-1) */
    unsigned int dwCapacity;     /*Capacity(Read only)*/
    unsigned int dwFreeSpace;    /*Free space(Read only)*/
    unsigned int dwHdStatus;     /*Disk status(Read only) 0-Normal, 1-Raw, 2-Error, 3-SMART State, 4-Unmatched, 5-Sleep*/
    unsigned char  byHDAttr;       /*0-Defaulty, 1-Redundancy; 2-Read only*/
    unsigned char  byHDType;		  /*0-本地硬盘,1-ESATA硬盘,2-NAS硬盘*/
    unsigned char  byRes1[2];
    unsigned int dwHdGroup;      /*Disk Group (1-MAX_HD_GROUP)*/
    unsigned char  byRes2[120];
}NET_DVR_SINGLE_HD, *LPNET_DVR_SINGLE_HD;

typedef struct
{
    unsigned int dwSize;
    unsigned int dwHDCount;          /*Number of Disk(Read only)*/
    NET_DVR_SINGLE_HD struHDInfo[MAX_DISKNUM_V30];//Reboot Device to take effect
}NET_DVR_HDCFG, *LPNET_DVR_HDCFG;

//Local Disk Group Configuration
typedef struct
{
    unsigned int dwHDGroupNo;       /*Group NO.(Read only) 1-MAX_HD_GROUP*/
    unsigned char byHDGroupChans[64]; /*Corresponding Channel of HD Group, 0-Not record in this group，1-Record in this group*/
    unsigned char byRes[8];
}NET_DVR_SINGLE_HDGROUP, *LPNET_DVR_SINGLE_HDGROUP;

typedef struct
{
    unsigned int dwSize;
    unsigned int dwHDGroupCount;        /*Total groups(Read only)*/
    NET_DVR_SINGLE_HDGROUP struHDGroupAttr[MAX_HD_GROUP];//Reboot Device to take effect
}NET_DVR_HDGROUP_CFG, *LPNET_DVR_HDGROUP_CFG;
                                       

//Display Scale Configuration
typedef struct
{
    unsigned int dwSize;
    unsigned int dwMajorScale;    /* Main Screen  0-No Scale，1-Scale*/
    unsigned int dwMinorScale;    /* AUX Screen   0-No Scale，1-Scale*/
    unsigned int dwRes[2];
}NET_DVR_SCALECFG, *LPNET_DVR_SCALECFG;



//DVR Alarm output(9000 extended)
typedef struct 
{
	unsigned int dwSize;
	unsigned char sAlarmOutName[NAME_LEN];	/* Name */
	unsigned int dwAlarmOutDelay;			/* Alarm Duration(-1--Stop manually) */
	//0-5 Sec,1-10Sec,2-30Sec,3-1Min,4-2Min,5-5Min,6-10Min,7-Stop Manually
	NET_DVR_SCHEDTIME struAlarmOutTime[MAX_DAYS][MAX_TIMESEGMENT_V30];/* Time Segment for Alarm output */
    unsigned char byRes[16];
}NET_DVR_ALARMOUTCFG_V30, *LPNET_DVR_ALARMOUTCFG_V30;

//DVR Alarm output
typedef struct 
{
	unsigned int dwSize;
	unsigned char sAlarmOutName[NAME_LEN];	/* Name */
	unsigned int dwAlarmOutDelay;	/* Alarm Duration(-1--Stop manually) */
	//0-5Sec,1-10Sec,2-30Sec,3-1Min,4-2Min,5-5Min,6-10Min,7-Stop Manually
	NET_DVR_SCHEDTIME struAlarmOutTime[MAX_DAYS][MAX_TIMESEGMENT]; /* Time Segment for Alarm output */
}NET_DVR_ALARMOUTCFG, *LPNET_DVR_ALARMOUTCFG;

//DVR Local Preview(9000 extended)
typedef struct 
{
    unsigned int dwSize;
    unsigned char byPreviewNumber;//Number of preview channels,0-1 window,1-4 windows,2-9 windows,3-16 windows,0xff: largest
    unsigned char byEnableAudio;//Preview audio,0-No,1-Yes
    unsigned short wSwitchTime;//duration to switch,0-disable,1-5s,2-10s,3-20s,4-30s,5-60s,6-120s,7-300s
    unsigned char bySwitchSeq[MAX_PREVIEW_MODE][MAX_WINDOW_V30];//Order to switch, lSwitchSeq[i]==0xff-not used
    unsigned char byRes[24];
}NET_DVR_PREVIEWCFG_V30, *LPNET_DVR_PREVIEWCFG_V30;
//DVR Local Preview 
typedef struct 
{
	unsigned int dwSize;
	unsigned char byPreviewNumber;//Number of preview channels,0-1 window,1-4 windows,2-9 windows,3-16 windows,0xff: largest
	unsigned char byEnableAudio;//Preview audio,0-No,1-Yes
	unsigned short wSwitchTime;//duration to switch,0-disable,1-5s,2-10s,3-20s,4-30s,5-60s,6-120s,7-300s
	unsigned char bySwitchSeq[MAX_WINDOW];//Order to switch, lSwitchSeq[i] 0xff-not used
}NET_DVR_PREVIEWCFG, *LPNET_DVR_PREVIEWCFG;

//DVR video output
typedef struct 
{
	unsigned short wResolution;							/* Resolution */
	unsigned short wFreq;									/* Refresh rate */
	unsigned int dwBrightness;							/* Brightness */
}NET_DVR_VGAPARA;

/*
* MATRIX Output Configuration
*/
typedef struct
{		
	unsigned short	wOrder[MAX_ANALOG_CHANNUM];		/* Preview order, 0xff means this channel is disabled */
	unsigned short	wSwitchTime;					/* Time to witch */
	unsigned char	res[14];
}NET_DVR_MATRIXPARA_V30, *LPNET_DVR_MATRIXPARA_V30;

typedef struct 
{
	unsigned short wDisplayLogo;						/* Display Channel No. */
	unsigned short wDisplayOsd;						/* Display Time */
}NET_DVR_MATRIXPARA;

typedef struct 
{
	unsigned char byVideoFormat;						/* Video Standard,0-PAL,1-NTSC */
	unsigned char byMenuAlphaValue;					/* the contrast between Menu and background image */
	unsigned short wScreenSaveTime;					/* Screen Saver 0-Never,1-1Min,2-2Min,3-5Min,4-10Min,5-20Min,6-30Min */
	unsigned short wVOffset;							/* Offset of video output */
	unsigned short wBrightness;						/* Brightness*/
	unsigned char byStartMode;						/* Video output mode(0:Menu,1:Preview)*/
	unsigned char byEnableScaler;                    /* Enable Scale (0-Disable, 1-Enable)*/
}NET_DVR_VOOUT;

//DVR Video output (9000 extended)
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_VOOUT struVOOut[MAX_VIDEOOUT_V30];
	NET_DVR_VGAPARA struVGAPara[MAX_VGA_V30];					/* VGA Parameter */
	NET_DVR_MATRIXPARA_V30 struMatrixPara[MAX_MATRIXOUT];		/* MATRIX Parameter */
    unsigned char byRes[16];
}NET_DVR_VIDEOOUT_V30, *LPNET_DVR_VIDEOOUT_V30;

//DVR Video Output
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_VOOUT struVOOut[MAX_VIDEOOUT];
	NET_DVR_VGAPARA struVGAPara[MAX_VGA];	/* VGA Parameter */
	NET_DVR_MATRIXPARA struMatrixPara;		/* MATRIX Parameter */
}NET_DVR_VIDEOOUT, *LPNET_DVR_VIDEOOUT;

//Single User Parameters(Sub Struct)(9000 extended)
typedef struct
{
	unsigned char sUserName[NAME_LEN];		/* Username */
	unsigned char sPassword[PASSWD_LEN];		/* Password */
	unsigned char byLocalRight[MAX_RIGHT];	/* Local privilege */
	/*   
	array 0: local PTZ control
    array 1: local manual record
	array 2: local playback
    array 3: local configuration 
	array 4: local log & status query 
    array 5: local advanced settings (upgrade, format, reboot, shut down)
    array 6: local parameter check
    array 7: local analog & IP camera management 
    array 8: local backup
    array 9: local shut down/reboot
	*/

	unsigned char byRemoteRight[MAX_RIGHT];/* remote privilege settings */
	/* 
       array 0: remote PTZ control
       array 1: remote manual record
       array 2: remote playback
       array 3: remote configuration 
       array 4: remote log & status query
       array 5: remote advanced settings (upgrade, format, reboot, shut down)
       array 6: remote start voice talk
       array 7: remote preview
	   array 8-remote alarm upload to center, alarm output
       array 9-remote control local output
       array 10-remote serial port control
       array 11: remote parameter query
       array 12: remote analog & IP camera management
       array 13: remote shut down/reboot
	*/
	unsigned char byNetPreviewRight[MAX_CHANNUM_V30];		/* remote preview channel , 0-enable, 1-disable*/
	unsigned char byLocalPlaybackRight[MAX_CHANNUM_V30];		/* local playback channel , 0-enable, 1-disable*/
	unsigned char byNetPlaybackRight[MAX_CHANNUM_V30];		/* remote playback channel , 0-enable, 1-disable*/
	unsigned char byLocalRecordRight[MAX_CHANNUM_V30];		/* local record channel , 0-enable, 1-disable*/
	unsigned char byNetRecordRight[MAX_CHANNUM_V30];		/* remote record channel , 0-enable, 1-disable*/
	unsigned char byLocalPTZRight[MAX_CHANNUM_V30];		/* local PTZ channel , 0-enable, 1-disable*/
	unsigned char byNetPTZRight[MAX_CHANNUM_V30];			/* remote PTZ channel , 0-enable, 1-disable*/
	unsigned char byLocalBackupRight[MAX_CHANNUM_V30];		/* local backup channel , 0-enable, 1-disable*/
	NET_DVR_IPADDR struUserIP;		/* User IP (0 stands for no IP restriction) */
	unsigned char byMACAddr[MACADDR_LEN];	/* MAC */
	unsigned char byPriority;				/* Prioroty settings , 0xff- disable , 0-low, 1-Mid, 2-High */
     /*
     Low……Default privileges including local/remote playback, log & status query, reboot/shut down.
	 Mid……Include local/remote PTZ control, manual record, voice talk, playback, log & status query, reboot/shut down, log backup and remote preview. 
	 High……Administrator
     */
	unsigned char byRes[17];
}NET_DVR_USER_INFO_V30, *LPNET_DVR_USER_INFO_V30;

//Single User Parameters(SDK_V15extended)(Sub Struct)
typedef struct 
{
	unsigned char sUserName[NAME_LEN];		/* Username */
	unsigned char sPassword[PASSWD_LEN];		/* Password */
	unsigned int dwLocalRight[MAX_RIGHT];	/* privilege */
	/*
	array 0-local PTZ control
	array 1-local manual record
	array 2-local playback
	array 3-local configuration
	array 4-local log & status query
	array 5-local advanced settings (upgrade, format, reboot, shut down)
	*/
	unsigned int dwLocalPlaybackRight;		/*  local playback channel. 1 bit0 -- channel 1*/
	unsigned int dwRemoteRight[MAX_RIGHT];	/* privilege */
	/*
	array 0-remote  PTZ control
	array 1-remote manual record
	array 2-remote playback
	array 3-remote configuration
	array 4-remote log & status query
	array 5-remote advanced settings (upgrade, format, reboot, shut down)
	array 6-remote start voice talk
	array 7-remote preview
	array 8-remote alarm upload to center, alarm output
	array 9-remote control local output
	array 10-remote serial port control
	*/
	unsigned int dwNetPreviewRight;		/* remote preview channel number, bit0 -- channel 1*/
	unsigned int dwNetPlaybackRight;		/* remote playback channel number, bit0 -- channel 1*/
	char sUserIP[16];				/* User IP (0 stands for no IP restriction) */
	unsigned char byMACAddr[MACADDR_LEN];	/* MAC */
}NET_DVR_USER_INFO_EX, *LPNET_DVR_USER_INFO_EX;

//Single User Parameters(Sub Struct)
typedef struct 
{
	unsigned char sUserName[NAME_LEN];		/* Username */
	unsigned char sPassword[PASSWD_LEN];		/* Password */
	unsigned int dwLocalRight[MAX_RIGHT];	/* privilege */
	/*
	array 0-local PTZ control
	array 1-local manual record
	array 2-local playback
	array 3-local configuration
	array 4-local log & status query
	array 5-local advanced settings (upgrade, format, reboot, shut down)
	*/
	unsigned int dwRemoteRight[MAX_RIGHT];	/* privilege */
	/*
	array 0-remote  PTZ control
	array 1-remote manual record
	array 2-remote playback
	array 3-remote configuration
	array 4-remote log & status query
	array 5-remote advanced settings (upgrade, format, reboot, shut down)
	array 6-remote start voice talk
	array 7-remote preview
	array 8-remote alarm upload to center, alarm output
	array 9-remote control local output
	array 10-remote serial port control
	*/
	char sUserIP[16];				/* User IP (0 stands for no IP restriction) */
	unsigned char byMACAddr[MACADDR_LEN];	/* MAC */
}NET_DVR_USER_INFO, *LPNET_DVR_USER_INFO;


//DVR User Parameters(9000extended)
typedef struct
{
	unsigned int dwSize;
	NET_DVR_USER_INFO_V30 struUser[MAX_USERNUM_V30];
}NET_DVR_USER_V30, *LPNET_DVR_USER_V30;

//DVR User Parameters(SDK_V15extended)
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_USER_INFO_EX struUser[MAX_USERNUM];
}NET_DVR_USER_EX, *LPNET_DVR_USER_EX;

//DVR User Parameters
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_USER_INFO struUser[MAX_USERNUM];
}NET_DVR_USER, *LPNET_DVR_USER;

//DVR Exception Parameters(9000extended)
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_HANDLEEXCEPTION_V30 struExceptionHandleType[MAX_EXCEPTIONNUM_V30];
	/*array 0- hard disk is full, 1- hard disk error, 2- signal lost, 3- network link is broken, 4-illegal access, 5- input/output video standard not match, 6-overspeed Car(for mobile DVR), 7-record exception*/
}NET_DVR_EXCEPTION_V30, *LPNET_DVR_EXCEPTION_V30;

//DVR Exception Parameters
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_HANDLEEXCEPTION struExceptionHandleType[MAX_EXCEPTIONNUM];
	/*array 0- hard disk is full, 1- hard disk error, 2- signal lost, 3- network link is broken, 4-illegal access, 5- input/output video standard not match, 6-overspeed Car(for mobile DVR)*/
}NET_DVR_EXCEPTION, *LPNET_DVR_EXCEPTION;

//Channel State(9000 extended)
typedef struct 
{
	unsigned char byRecordStatic; //whether the channel is in recording, 0- no, 1- yes
	unsigned char bySignalStatic; //video signal status, 0- normal, 1- lost
	unsigned char byHardwareStatic;//the channel hardware status, 0- normal, 1- abnormal, e.g. DSP is not work
	unsigned char byRes1;		//Reserved
	unsigned int dwBitRate;	//actual bit rate
	unsigned int dwLinkNum;	//connected client number
	NET_DVR_IPADDR struClientIP[MAX_LINK];//client IP referred to NET_DVR_IPADDR
    unsigned int dwIPLinkNum;//if the current channel is set as IPC channel, then this parameter represents the current connected IP channel number.
	unsigned char byRes[12];
}NET_DVR_CHANNELSTATE_V30, *LPNET_DVR_CHANNELSTATE_V30;

//Channel State
typedef struct 
{
	unsigned char byRecordStatic; //whether the channel is in recording, 0- no, 1- yes
	unsigned char bySignalStatic; //video signal status, 0- normal, 1- lost
	unsigned char byHardwareStatic;//the channel hardware status, 0- normal, 1- abnormal, e.g. DSP is not work
	char reservedData;		//Reserved
	unsigned int dwBitRate;	//actual bit rate
	unsigned int dwLinkNum;	//connected client number
	unsigned int dwClientIP[MAX_LINK];//client IP
}NET_DVR_CHANNELSTATE, *LPNET_DVR_CHANNELSTATE;

//Hard Disk Status
typedef struct 
{
	unsigned int dwVolume;//Capacity
	unsigned int dwFreeSpace;//Free Space
	unsigned int dwHardDiskStatic; //HD status：0-active;1-sleep mode;2-abnormal; 3- sleep mode error
}NET_DVR_DISKSTATE, *LPNET_DVR_DISKSTATE;

//DVR Work State(9000 extended)
typedef struct 
{
	unsigned int dwDeviceStatic; 	//the device’s status, 0- normal, 1- the occupancy of CPU is too high, more than 85%, 2-hardware error, e.g. the serial ports do not work
	NET_DVR_DISKSTATE  struHardDiskStatic[MAX_DISKNUM_V30]; 
	NET_DVR_CHANNELSTATE_V30 struChanStatic[MAX_CHANNUM_V30];//channel status  as NET_DVR_CHANNELSTATE
	unsigned char  byAlarmInStatic[MAX_ALARMIN_V30]; //alarm input status, 0- no alarm, 1-alarm
	unsigned char  byAlarmOutStatic[MAX_ALARMOUT_V30]; //alarm output status, 0-no output, 1-alarm output
	unsigned int  dwLocalDisplay;//Local display status, 0- normal, 1-abnormal
    unsigned char  byAudioChanStatus[MAX_AUDIO_V30];//Audio channel status, 0-unused; 1-on using；0xff-invalid
    unsigned char  byRes[10];
}NET_DVR_WORKSTATE_V30, *LPNET_DVR_WORKSTATE_V30;

//DVR Status Structure 
typedef struct 
{
	unsigned int dwDeviceStatic; 	//the device’s status, 0- normal, 1- the occupancy of CPU is too high, more than 85%, 2-hardware error, e.g. the serial ports do not work
	NET_DVR_DISKSTATE  struHardDiskStatic[MAX_DISKNUM];
	NET_DVR_CHANNELSTATE struChanStatic[MAX_CHANNUM];//channel status  as NET_DVR_CHANNELSTATE
	unsigned char  byAlarmInStatic[MAX_ALARMIN];			//alarm input status, 0- no alarm, 1-alarm
	unsigned char  byAlarmOutStatic[MAX_ALARMOUT];		//alarm output status, 0-no output, 1-alarm output
	unsigned int  dwLocalDisplay;						//Local display status, 0- normal, 1-abnormal
}NET_DVR_WORKSTATE, *LPNET_DVR_WORKSTATE;

/************************DVR Log begin***************************/

/* Alarm */
//Main Type
#define MAJOR_ALARM					0x1
//Hypo-Type
#define MINOR_ALARM_IN					0x1  /* alarm input */
#define MINOR_ALARM_OUT					0x2  /* alarm output*/
#define MINOR_MOTDET_START				0x3  /*	motion detection alarm start */
#define MINOR_MOTDET_STOP				0x4  /* motion detection alarm stop*/
#define MINOR_HIDE_ALARM_START			0x5  /* mask alarm start */
#define MINOR_HIDE_ALARM_STOP			0x6  /* mask alarm stop */
#define MINOR_VCA_ALARM_START			0x7  /* vca alarm start */
#define MINOR_VCA_ALARM_STOP				0x8  /*vca alarm stop*/


/*Exception */
//Main Type
#define MAJOR_EXCEPTION				0x2
//Hypo-Type
#define MINOR_VI_LOST					0x21 /* Video loss */
#define MINOR_ILLEGAL_ACCESS			0x22 /* Illegal access */
#define MINOR_HD_FULL					0x23 /* HD full */
#define MINOR_HD_ERROR					0x24 /* HD error */
#define MINOR_DCD_LOST					0x25 /* MODEM  off-line(Reserved) */
#define MINOR_IP_CONFLICT				0x26 /* IP conflict */
#define MINOR_NET_BROKEN				0x27 /* Network disconnected */
#define MINOR_REC_ERROR                 0x28 /* Record error */
#define MINOR_IPC_NO_LINK               0x29 /* IPC connection failed */
#define MINOR_VI_EXCEPTION              0x2a /* Video input error (for analog channel only) */
#define MINOR_IPC_IP_CONFLICT           0x2b /*ipc ip conflict*/

//2009-12-16 增加视频综合平台日志类型
#define MINOR_FANABNORMAL				0x31 /* 视频综合平台：风扇状态异常 */
#define MINOR_FANRESUME					0x32 /* 视频综合平台：风扇状态恢复正常 */
#define MINOR_SUBSYSTEM_ABNORMALREBOOT	0x33 /* 视频综合平台：6467异常重启 */
#define MINOR_MATRIX_STARTBUZZER		0x34 /* 视频综合平台：dm6467异常，启动蜂鸣器 */

/* Operation */
//Main Type
#define MAJOR_OPERATION				0x3
//Hypo-Type
#define MINOR_START_DVR					0x41 /* Power On */
#define MINOR_STOP_DVR					0x42 /* Power off */
#define MINOR_STOP_ABNORMAL				0x43 /* Illegal shut down */
#define MINOR_REBOOT_DVR                0x44    /*Local reboot DVR*/

#define MINOR_LOCAL_LOGIN				0x50 /* Login (local) */
#define MINOR_LOCAL_LOGOUT				0x51 /* Logout (local)*/
#define MINOR_LOCAL_CFG_PARM			0x52 /* Configuration (local) */
#define MINOR_LOCAL_PLAYBYFILE			0x53 /* Playback (local) */
#define MINOR_LOCAL_PLAYBYTIME			0x54 /* Playback or downlaod by time (local)*/
#define MINOR_LOCAL_START_REC			0x55 /* Start record (local) */
#define MINOR_LOCAL_STOP_REC			0x56 /* Stop record (local)*/
#define MINOR_LOCAL_PTZCTRL				0x57 /* PTZ control (local) */
#define MINOR_LOCAL_PREVIEW				0x58 /* Preview (local)(Reserved)*/
#define MINOR_LOCAL_MODIFY_TIME         0x59 /* Change time (local)(Reserved) */
#define MINOR_LOCAL_UPGRADE				0x5a /* Upgrade (local) */
#define MINOR_LOCAL_RECFILE_OUTPUT      0x5b    /* Backup (local) */
#define MINOR_LOCAL_FORMAT_HDD          0x5c    /* HD format(local) */
#define MINOR_LOCAL_CFGFILE_OUTPUT      0x5d    /* Export Configuration (local) */
#define MINOR_LOCAL_CFGFILE_INPUT       0x5e    /* Import Configuration (local) */
#define MINOR_LOCAL_COPYFILE            0x5f    /* Backup file (local) */
#define MINOR_LOCAL_LOCKFILE            0x60    /* File lockup (local)Reboot IPC (local) */
#define MINOR_LOCAL_UNLOCKFILE          0x61    /* File unlock (local) */
#define MINOR_LOCAL_DVR_ALARM           0x62    /* Clear/Trigger Alarm (Local)*/
#define MINOR_IPC_ADD                   0x63    /* Add IPC (local) */
#define MINOR_IPC_DEL                   0x64    /* Delete IPC (local)*/
#define MINOR_IPC_SET                   0x65    /* Set IPC (local) */
#define MINOR_LOCAL_START_BACKUP		0x66	/* local start backup file */
#define MINOR_LOCAL_STOP_BACKUP			0x67	/* local stop backup file*/
#define MINOR_LOCAL_COPYFILE_START_TIME 0x68	/* local backup:file start time*/
#define MINOR_LOCAL_COPYFILE_END_TIME	0x69	/* local backup:file end time*/

#define MINOR_REMOTE_LOGIN				0x70 /* Login (remote)*/
#define MINOR_REMOTE_LOGOUT				0x71 /* Logout  (remote) */
#define MINOR_REMOTE_START_REC			0x72 /* Start record (remote)*/
#define MINOR_REMOTE_STOP_REC			0x73 /* Stop record  (remote) */
#define MINOR_START_TRANS_CHAN			0x74 /* Start transparent channel (remote) */
#define MINOR_STOP_TRANS_CHAN			0x75 /* Stop transparent channel (remote) */
#define MINOR_REMOTE_GET_PARM			0x76 /* Get parameter (remote)*/
#define MINOR_REMOTE_CFG_PARM			0x77 /* configuration (remote)*/
#define MINOR_REMOTE_GET_STATUS         0x78 /* Get status (remote) */
#define MINOR_REMOTE_ARM				0x79 /* On guard  (remote) */
#define MINOR_REMOTE_DISARM				0x7a /* Disarm  (remote) */
#define MINOR_REMOTE_REBOOT				0x7b /* Reboot  (remote) */
#define MINOR_START_VT					0x7c /* Start voice talk */
#define MINOR_STOP_VT					0x7d /* Stop voice talk */
#define MINOR_REMOTE_UPGRADE			0x7e /* upgrade (remote) */
#define MINOR_REMOTE_PLAYBYFILE         0x7f /* Playback by file name (remote) */
#define MINOR_REMOTE_PLAYBYTIME         0x80 /* Playback by time (remote) */
#define MINOR_REMOTE_PTZCTRL			0x81 /* PTZ control (remote) */
#define MINOR_REMOTE_FORMAT_HDD         0x82 /*Format hard disk(remote) */
#define MINOR_REMOTE_STOP               0x83 /*Shut Down (remote) */
#define MINOR_REMOTE_LOCKFILE			0x84 /* File lockup (remote) */
#define MINOR_REMOTE_UNLOCKFILE         0x85 /* File unlock (remote */
#define MINOR_REMOTE_CFGFILE_OUTPUT     0x86 /* Export Configuration  (remote) */
#define MINOR_REMOTE_CFGFILE_INTPUT     0x87 /* Import Configuration (remote) */
#define MINOR_REMOTE_RECFILE_OUTPUT     0x88 /* Backup recording files (remote) */
#define MINOR_REMOTE_DVR_ALARM          0x89 /* Trigger/clear alarm (remote)*/
#define MINOR_REMOTE_IPC_ADD			0x8a /* Add IPC (remote)*/
#define MINOR_REMOTE_IPC_DEL			0x8b /* Delete IPC (remote)*/
#define MINOR_REMOTE_IPC_SET			0x8c /*Set  IPC (remote)*/
#define MINOR_REBOOT_VCA_LIB            0x8d /*reboot vca library*/
#define MINOR_REMOTE_ADD_NAS            0x8e	/* 远程添加nas盘*/
#define MINOR_REMOTE_DEL_NAS            0x8f	/* 远程删除nas盘*/
#define MINOR_REMOTE_SET_NAS            0x90	/* 远程设置nas盘*/

//2009-12-16 增加视频综合平台日志类型
#define MINOR_SUBSYSTEMREBOOT           0xa0	/*视频综合平台：dm6467 正常重启*/
#define MINOR_MATRIX_STARTTRANSFERVIDEO 0xa1	/*视频综合平台：矩阵切换开始传输图像*/
#define MINOR_MATRIX_STOPTRANSFERVIDEO	0xa2	/*视频综合平台：矩阵切换停止传输图像*/
#define MINOR_REMOTE_SET_ALLSUBSYSTEM   0xa3	/*视频综合平台：设置所有6467子系统信息*/
#define MINOR_REMOTE_GET_ALLSUBSYSTEM   0xa4	/*视频综合平台：获取所有6467子系统信息*/
#define MINOR_REMOTE_SET_PLANARRAY      0xa5	/*视频综合平台：设置计划轮询组*/
#define MINOR_REMOTE_GET_PLANARRAY      0xa6	/*视频综合平台：获取计划轮询组*/
#define MINOR_MATRIX_STARTTRANSFERAUDIO 0xa7	/*视频综合平台：矩阵切换开始传输音频*/
#define MINOR_MATRIX_STOPRANSFERAUDIO   0xa8	/*视频综合平台：矩阵切换停止传输音频*/
#define MINOR_LOGON_CODESPITTER         0xa9	/*视频综合平台：登陆码分器*/
#define MINOR_LOGOFF_CODESPITTER        0xaa	/*视频综合平台：退出码分器*/

/*Additional Log Info*/
//Main Type
#define MAJOR_INFORMATION			0x4     /*Extra Info*/
//Hypo-Type
#define MINOR_HDD_INFO                  0xa1 /*HD info*/
#define MINOR_SMART_INFO                0xa2 /*SMART info*/
#define MINOR_REC_START                 0xa3 /*Start record*/
#define MINOR_REC_STOP                  0xa4 /*Stop record */
#define MINOR_REC_OVERDUE				0xa5 /*Record overdue*/
#define MINOR_LINK_START				0xa6 //start to link device
#define MINOR_LINK_STOP					0xa7 //stop to link device


/*
If the main type of the log is MAJOR_OPERATION=03(Operation)And Sub type is
MINOR_LOCAL_CFG_PARM=0x52(local configuration)
MINOR_REMOTE_GET_PARM=0x76(remote get configuration)
MINOR_REMOTE_CFG_PARM=0x77(remote set configuration)
dwParaType: is valid, and the relative definition is listed as below:
*/
#define PARA_VIDEOOUT	0x1
#define PARA_IMAGE		0x2
#define PARA_ENCODE		0x4
#define PARA_NETWORK	0x8
#define PARA_ALARM		0x10
#define PARA_EXCEPTION	0x20
#define PARA_DECODER	0x40    /*Decoder*/
#define PARA_RS232		0x80
#define PARA_PREVIEW	0x100
#define PARA_SECURITY	0x200
#define PARA_DATETIME	0x400
#define PARA_FRAMETYPE	0x800    /*Frame Type*/
#define PARA_VCA_RULE   0x1001  //行为规则 
#define PARA_VCA_CTRL   0x1002  //配置智能控制信息
#define PARA_VCA_PLATE      0x1003 //  车牌识别


#define PARA_CODESPLITTER 0x2000 /*码分器参数*/
//Log Info(9000extended)
typedef struct 
{
	NET_DVR_TIME strLogTime;
	unsigned int	dwMajorType;	//Main type 1-alarm; 2-abnormal; 3-operation; 0xff-all
	unsigned int	dwMinorType;	//Hypo-Type 0-all;
	unsigned char	sPanelUser[MAX_NAMELEN]; //user ID for local panel operation
	unsigned char	sNetUser[MAX_NAMELEN];//user ID for network operation
	NET_DVR_IPADDR	struRemoteHostAddr;//remote host IP
	unsigned int	dwParaType;//parameter type, for 9000 series MINOR_START_VT/MINOR_STOP_VT, channel of the voice talking
	unsigned int	dwChannel;//channel number
	unsigned int	dwDiskNumber;//HD number
	unsigned int	dwAlarmInPort;//alarm input port
	unsigned int	dwAlarmOutPort;//alarm output port
    unsigned int   dwInfoLen;
    char    sInfo[LOG_INFO_LEN];
}NET_DVR_LOG_V30, *LPNET_DVR_LOG_V30;

//Log Info
typedef struct 
{
	NET_DVR_TIME strLogTime;
	unsigned int	dwMajorType;	//MMain type 1-alarm; 2-abnormal; 3-operation; 0xff-all
	unsigned int	dwMinorType;//Hypo-Type 0-all;
	unsigned char	sPanelUser[MAX_NAMELEN]; //user ID for local panel operation
	unsigned char	sNetUser[MAX_NAMELEN];//user ID for network operation
	char	sRemoteHostAddr[16];//remote host IP
	unsigned int	dwParaType;//parameter type
	unsigned int	dwChannel;//channel number
	unsigned int	dwDiskNumber;//HD number
	unsigned int	dwAlarmInPort;//alarm input port
	unsigned int	dwAlarmOutPort;//alarm output port
}NET_DVR_LOG, *LPNET_DVR_LOG;

/************************DVR Log end***************************/


//Alarm output state(9000 extended)
typedef struct 
{
	unsigned char Output[MAX_ALARMOUT_V30];
}NET_DVR_ALARMOUTSTATUS_V30, *LPNET_DVR_ALARMOUTSTATUS_V30;

//Alarm output state
typedef struct 
{
	unsigned char Output[MAX_ALARMOUT];
}NET_DVR_ALARMOUTSTATUS, *LPNET_DVR_ALARMOUTSTATUS;

//Transaction Info
typedef struct 
{
	unsigned short m_Year;
	unsigned short m_Month;
	unsigned short m_Day;
	unsigned short m_Hour;
	unsigned short m_Minute;
	unsigned short m_Second;
	unsigned char DeviceName[24];	//Device name
	unsigned int dwChannelNumer;	//Channel name
	unsigned char CardNumber[32];	//Credit Card No.
	char cTradeType[12];	//Transaction type	
	unsigned int dwCash;			//Transaction money
}NET_DVR_TRADEINFO, *LPNET_DVR_TRADEINFO;


//Special for ATM
/****************************ATM(begin)***************************/
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
#define DRS918	21
#define KALATEL	22
#define NCR_2	23	
#define NXS		24


/*Frame Type*/
typedef struct 
{
	unsigned char code[12];		/* code */
}NET_DVR_FRAMETYPECODE;

//ATM Parameters
typedef struct 
{
	unsigned int dwSize;
	char sATMIP[16];						/* ATM IP */
	unsigned int dwATMType;						/* ATM Type*/
	unsigned int	dwInputMode;						/* 0- network listening 1-network receive 2- directly input via serial port 3- input ATM command via serial port*/
	unsigned int	dwFrameSignBeginPos;				/* the start position of Message flag*/
	unsigned int	dwFrameSignLength;					/* the length of Message flag */
	unsigned char	byFrameSignContent[12];				/* the content of Message flag */
	unsigned int	dwCardLengthInfoBeginPos;			/* offset of credit card No. length information */
	unsigned int	dwCardLengthInfoLength;				/* the length of the card length information */
	unsigned int	dwCardNumberInfoBeginPos;			/* Start position of the card number information */
	unsigned int	dwCardNumberInfoLength;				/* Length of the card number information */
	unsigned int	dwBusinessTypeBeginPos;				/* the offset of operation type information */
	unsigned int	dwBusinessTypeLength;				/* the length of the operation type */
	NET_DVR_FRAMETYPECODE	frameTypeCode[10];	/* type */
}NET_DVR_FRAMEFORMAT, *LPNET_DVR_FRAMEFORMAT;

//SDK_V31 ATM
/*1.1.1.18	Structure of package filter*/
typedef struct	tagNET_DVR_FILTER
{	
	unsigned char			        byEnable;			//0, disable; 1, enable
	unsigned char					byMode;				//0,ASCII;1,HEX
    unsigned char                    byFrameBeginPos;    //begin position of target text
	unsigned char					byRes[1];           //Reserved
	unsigned char 					byFilterText[16];	//filter text
	unsigned char					byRes2[12];         //Reserved
}NET_DVR_FILTER, *LPNET_DVR_FILTER;

//Package structure of starting flag
typedef struct	tagNET_DVR_IDENTIFICAT
{	
	unsigned char					byStartMode;		//start mode:0,ASCII;1,HEX
	unsigned char					byEndMode;			//end mode: 0,ASCII;1,HEX
	unsigned char					byRes[2];           //Reserved
	NET_DVR_FRAMETYPECODE	struStartCode;		//start code
	NET_DVR_FRAMETYPECODE	struEndCode;		//end code
	unsigned char					byRes1[12];         //Reserved
}NET_DVR_IDENTIFICAT, *LPNET_DVR_IDENTIFICAT;

typedef struct	tagNET_DVR_PACKAGE_LOCATION/* package information position*/
{	
	unsigned char 					byOffsetMode;			/* 0,token(character flag mode);1,fix（fix mode）*/
    unsigned char                    byRes1[3];				// Reserved
	unsigned int  				    dwOffsetPos;			/*Used when mode is 1, offset size*/
	NET_DVR_FRAMETYPECODE	struTokenCode;			/*Flag bit*/
	unsigned char					byMultiplierValue;		/*number of Flags*/
	unsigned char					byEternOffset;			/*extern offset*/
	unsigned char					byCodeMode;			    /*0,ASCII;1,HEX*/
	unsigned char 					byRes2[9];			    //Reserved
}NET_DVR_PACKAGE_LOCATION, *LPNET_DVR_PACKAGE_LOCATION;


typedef struct	tagNET_DVR_PACKAGE_LENGTH//package length
{	
	unsigned char					byLengthMode;			//length mode: 0, variable; 1, fixed ;2,gotten from package(Used when setting the card number length )
    unsigned char                    byRes1[3];              // Reserved
	unsigned int  			    	dwFixLength;			//Used when mode is 1, fixed length
	unsigned int					dwMaxLength;            //Maximum length  byLengthMode is 0
	unsigned int					dwMinLength;            //Minimum length  byLengthMode is 1
	unsigned char					byEndMode;			    //Terminator: 0,ASCII;1,HEX
    unsigned char                    byRes2[3];              //Reserved
	NET_DVR_FRAMETYPECODE	struEndCode;			//Terminator with variable length
	unsigned int					dwLengthPos;			//Used when length mode is 2, card length position in the package
	unsigned int					dwLengthLen;			//Used when length mode is 2, length of the card number length
	unsigned char					byRes3[8];              // Reserved
}NET_DVR_PACKAGE_LENGTH,* LPNET_DVR_PACKAGE_LENGTH;
 
typedef struct	tagNET_DVR_OSD_POSITION//OSD overlay position
{	
	unsigned char					byPositionMode;		//Mode, 0: not display, 1:Custom
    unsigned char                    byRes1[3];          // Reserved
	unsigned int 					dwPosX;				//X-coordinater, used when position mode is custom
	unsigned int					dwPosY;				//Y-coordinater, used when position mode is custom
	unsigned char					byRes2[8];          //Reserved
}NET_DVR_OSD_POSITION, *LPNET_DVR_OSD_POSITION;

typedef struct	tagNET_DVR_DATE_FORMAT//date display format
{	
	unsigned char					byMonth;			    //Month,0.mm;1.mmm;2.mmmm
	unsigned char 					byDay;				    //Day,0.dd;
	unsigned char 					byYear;				    //Year,0.yy;1.yyyy
	unsigned char					byDateForm;			    //0~5, permutations and combinations of year,month,day
	unsigned char					byRes[20];              // Reserved
	char					chSeprator[4];		    //separator
	char	    			chDisplaySeprator[4];	//display separator
    unsigned char	    			byDisplayForm;			//0~5，permutations and combinations of 3 items
	unsigned char					res[27];                // Reserved
}NET_DVR_DATE_FORMAT, *LPNET_DVR_DATE_FORMAT;
typedef struct	tagNET_DVRT_TIME_FORMAT//time display format
{	
	unsigned char					byTimeForm;				//1. HH MM SS;0. HH MM
	unsigned char 					byRes1[23];             // Reserved
    unsigned char                    byHourMode;             //0,12;1,24
    unsigned char                    byRes2[3];              // Reserved
	char					chSeprator[4]; 			//package separator, reserved
	char					chDisplaySeprator[4];	//display separator
	unsigned char	    			byDisplayForm;			//0~5, permutations and combinations  of 3 items
    unsigned char                    byRes3[3];              // Reserved
	unsigned char					byDisplayHourMode;		//0,12;1,24
	unsigned char					byRes4[19];             // Reserved
}NET_DVR_TIME_FORMAT, *LPNET_DVR_TIME_FORMAT;

typedef struct tagNET_DVR_OVERLAY_CHANNEL
{	
	unsigned char                    byChannel[64];//overlay channel, Set 1 to display, set 0 to hide
	unsigned int					dwDelayTime;			//overlay delay time
	unsigned char					byEnableDelayTime;		//enable or disable. Overlay delay is enabled, in the absence of withdrawal card command
	unsigned char					byRes[11];          // Reserved
}NET_DVR_OVERLAY_CHANNEL, *LPNET_DVR_OVERLAY_CHANNEL;

// Structure of Trading action
typedef struct tagNET_DVR_ATM_PACKAGE_ACTION
{	
	NET_DVR_PACKAGE_LOCATION	struPackageLocation;// location of package
	NET_DVR_OSD_POSITION		struOsdPosition;    // OSD overlay position
	NET_DVR_FRAMETYPECODE		struActionCode;		//codes of trading type
	NET_DVR_FRAMETYPECODE		struPreCode;		//character before overlaying
	unsigned char					byActionCodeMode;		//codes of trading type. 0,ASCII;1,HEX
	unsigned char					byRes[7];               // Reserved
}NET_DVR_ATM_PACKAGE_ACTION, *LPNET_DVR_ATM_PACKAGE_ACTION;

//  Date info of ATM package
typedef struct tagNET_DVR_ATM_PACKAGE_DATE
{	
	NET_DVR_PACKAGE_LOCATION	struPackageLocation;// Position of date
	NET_DVR_DATE_FORMAT		    struDateForm;		//date display mode
	NET_DVR_OSD_POSITION		struOsdPosition;	// OSD overly position
	unsigned char				    	res[8]; 			// Reserved
}NET_DVR_ATM_PACKAGE_DATE, *LPNET_DVR_ATM_PACKAGE_DATE;


//Time info of ATM package
typedef struct tagNET_DVR_ATM_PACKAGE_TIME
{	
	NET_DVR_PACKAGE_LOCATION	location;		// Position of time
	NET_DVR_TIME_FORMAT		    struTimeForm;	//display mode
	NET_DVR_OSD_POSITION		struOsdPosition;// OSD overly position
	unsigned char					    byRes[8];		// Reserved
}NET_DVR_ATM_PACKAGE_TIME, *LPNET_DVR_ATM_PACKAGE_TIME;


//other info of  ATM package(Card SN., Transaction amount, Transaction SN.)
typedef struct tagNET_DVR_ATM_PACKAGE_OTHERS
{	
	NET_DVR_PACKAGE_LOCATION	struPackageLocation; //Position info
	NET_DVR_PACKAGE_LENGTH	struPackageLength;		//length Info
	NET_DVR_OSD_POSITION		struOsdPosition;	//overlay position
	NET_DVR_FRAMETYPECODE		struPreCode;		//character before overlaying
	unsigned char					res[8];					//Reserved
}NET_DVR_ATM_PACKAGE_OTHERS, *LPNET_DVR_ATM_PACKAGE_OTHERS;


//User-defined Protocol
typedef struct tagNET_DVR_ATM_USER_DEFINE_PROTOCOL
{
    NET_DVR_IDENTIFICAT        struIdentification;  //Package Flag
    NET_DVR_FILTER             struFilter; //Filter settings
    NET_DVR_ATM_PACKAGE_OTHERS struCardNoPara; // Settings of overlay card number 
    NET_DVR_ATM_PACKAGE_ACTION struTradeActionPara[MAX_ACTION_TYPE]; //Settings of overlay trade action,0-9:InCard, OutCard, OverLay, SetTime, GetStatus, Query, WithDraw, Deposit, ChanPass, Transfer
    NET_DVR_ATM_PACKAGE_OTHERS struAmountPara; //Settings of overlay Transaction amount
    NET_DVR_ATM_PACKAGE_OTHERS struSerialNoPara; //Settings of overlay trade SN
    NET_DVR_OVERLAY_CHANNEL    struOverlayChan; //Settings of overlay channel
    NET_DVR_ATM_PACKAGE_DATE   struRes1; //Settings of overlay data, reserved
    NET_DVR_ATM_PACKAGE_TIME   struRes2; //Settings of overlay time, reserved
    unsigned char                       byRes3[124];        //Reserved
}NET_DVR_ATM_USER_DEFINE_PROTOCOL, *LPNET_DVR_ATM_USER_DEFINE_PROTOCOL;

typedef struct tagNET_DVR_ATM_FRAMEFORMAT_V30
{		
    unsigned int                        dwSize;                //structure size
    unsigned char					    byEnable;				/*0: Enable, 1: Disable*/
    unsigned char					    byInputMode;			/*Input mode: 0-Network Listen, 1-Network Protocol, 2-Serial Listen, 3-Serial Protocol*/
    unsigned char					    byRes1[34];             //Reserved
    NET_DVR_IPADDR		    	struAtmIp;				/*ATM IP, used in network listen mode */
    unsigned short					    wAtmPort;				/* Get port by card number, Network Protocol mode or Serial server port mode*/
    unsigned char					    byRes2[2];              // Reserved
    unsigned int					    dwAtmType;				/*ATM protocol type, get from NET_DVR_ATM_PROTOCOL, using user-defined protocol when the type is user_defined*/
    NET_DVR_ATM_USER_DEFINE_PROTOCOL   struAtmUserDefineProtocol; //User-defined protocol, using this definition when the ATM protocol is user-defined.
    unsigned char					    byRes3[8];
}NET_DVR_ATM_FRAMEFORMAT_V30, *LPNET_DVR_ATM_FRAMEFORMAT_V30;


typedef struct  tagNET_DVR_ATM_PROTO_TYPE
{
    unsigned int dwAtmType; //ATM protocol type, index SN, and 1025 is for user-defined.
    char chDesc[ATM_DESC_LEN]; //Simple description of ATM protocol
}NET_DVR_ATM_PROTO_TYPE, *LPNET_DVR_ATM_PROTO_TYPE; //Data structure of protocol information

typedef struct tagNET_DVR_ATM_PROTO_LIST    //ATM Protocol List
{
    unsigned int                  dwAtmProtoNum;   // Number of protocol
    NET_DVR_ATM_PROTO_TYPE struAtmProtoType[MAX_ATM_PROTOCOL_NUM]; //protocol list info
}NET_DVR_ATM_PROTO_LIST, *LPNET_DVR_ATM_PROTO_LIST;

typedef struct tagNET_DVR_ATM_PROTOCOL
{
    unsigned int dwSize;
    NET_DVR_ATM_PROTO_LIST struNetListenList; // Description of Network Listen protocol
    NET_DVR_ATM_PROTO_LIST struSerialListenList; //Description of Serial Listen protocol
    NET_DVR_ATM_PROTO_LIST struNetProtoList;     //Description of Network protocol
    NET_DVR_ATM_PROTO_LIST struSerialProtoList;   //Description of Serial Protocol
    NET_DVR_ATM_PROTO_TYPE struCustomProto;        //User-defined protocol
}NET_DVR_ATM_PROTOCOL, *LPNET_DVR_ATM_PROTOCOL;
//SDK_V31

/*****************************DS-6001D/F(begin)***************************/
//DS-6001D Decoder
typedef struct 
{
	unsigned char byEncoderIP[16];		//Server IP that decoder connected
	unsigned char byEncoderUser[16];		//Server Username that decoder connected
	unsigned char byEncoderPasswd[16];	//Server Password that decoder connected
	unsigned char bySendMode;			//Server Connection Mode that decoder connected
	unsigned char byEncoderChannel;		//Server Channel No. that decoder connected
	unsigned short wEncoderPort;			//Server Port that decoder connected
	unsigned char reservedData[4];		//Reserved
}NET_DVR_DECODERINFO, *LPNET_DVR_DECODERINFO;

typedef struct 
{
	unsigned char byEncoderIP[16];		//Server IP that decoder connected
	unsigned char byEncoderUser[16];		//Server Username that decoder connected
	unsigned char byEncoderPasswd[16];	//Server Password that decoder connected
	unsigned char byEncoderChannel;		//Server Channel No. that decoder connected
	unsigned char bySendMode;			//Server Connection Mode that decoder connected
	unsigned short wEncoderPort;			//Server Port that decoder connected
	unsigned int dwConnectState;		//Server State that decoder connected
	unsigned char reservedData[4];		//Reserved
}NET_DVR_DECODERSTATE, *LPNET_DVR_DECODERSTATE;

/*Definition of Decoder Control Code */
#define NET_DEC_STARTDEC		1
#define NET_DEC_STOPDEC			2
#define NET_DEC_STOPCYCLE		3
#define NET_DEC_CONTINUECYCLE	4

/*Channel Connected Configuration*/
typedef struct 
{
	char sDVRIP[16];				/* DVR IP Address */
	unsigned short wDVRPort;			 		/* Ports */
	unsigned char sUserName[NAME_LEN];		/* Username */
	unsigned char sPassword[PASSWD_LEN];		/* Password */
	unsigned char byChannel;					/* Channel No. */
	unsigned char byLinkMode;				/* Connection Mode */
	unsigned char byLinkType;				/* Stream for Connection  0－Main Stream 1－Sub Stream */
}NET_DVR_DECCHANINFO, *LPNET_DVR_DECCHANINFO;

/*Configuration of Each Decoding Channel*/
typedef struct 
{
	unsigned char	byPoolChans;			/*Switch channel number on each decoder channel, range from 0-4*/
	NET_DVR_DECCHANINFO struchanConInfo[MAX_DECPOOLNUM];
	unsigned char	byEnablePoll;			/*enable switching or not: 0- disable 1- enable*/
	unsigned char	byPoolTime;				/*switching interval: 1-10 sec; 2- 15 sec; 3- 20 sec; 4- 30 sec;  5- 45 sec; 6- 1min; 7- 2min; 8- 5min */
}NET_DVR_DECINFO, *LPNET_DVR_DECINFO;

/*Decoder Configuration*/
typedef struct 
{
	unsigned int	dwSize;
	unsigned int	dwDecChanNum; 		/*Number of decoding channels*/
	NET_DVR_DECINFO struDecInfo[MAX_DECNUM];
}NET_DVR_DECCFG, *LPNET_DVR_DECCFG;

//2005-08-01
/* Transparent Channel of Decoder */
typedef struct 
{
	unsigned int dwEnableTransPort;	/* Enable transparent channel or not: 0- disable; 1- enable*/
	char sDecoderIP[16];		/* DVR IP */
	unsigned short wDecoderPort;			/* Port number */
	unsigned short wDVRTransPort;			/* Configuration DVR output serial port: 1- 232; 2- 485 */
	char cReserve[4];
}NET_DVR_PORTINFO, *LPNET_DVR_PORTINFO;

typedef struct 
{
	unsigned int dwSize;
	NET_DVR_PORTINFO struTransPortInfo[MAX_TRANSPARENTNUM]; /* Array 0--232; Array 1--485 */
}NET_DVR_PORTCFG, *LPNET_DVR_PORTCFG;

/* Remote Playback */
typedef struct 
{
	unsigned int dwSize;
	char sDecoderIP[16];		/* DVR IP*/
	unsigned short wDecoderPort;			/* Port */
	unsigned short wLoadMode;				/* Playback Mode 1－by name 2－by time */
	union
	{
		unsigned char byFile[100];		/* File Name */
		struct
		{
			unsigned int dwChannel;
			unsigned char sUserName[NAME_LEN];	/* Username for playback*/
			unsigned char sPassword[PASSWD_LEN];	/* Password */
			NET_DVR_TIME struStartTime;	/* Start time of playback by time mode*/
			NET_DVR_TIME struStopTime;	/* End time */
		}bytime;
	}mode_size;
}NET_DVR_PLAYREMOTEFILE, *LPNET_DVR_PLAYREMOTEFILE;

/*Decoder Channel Status Structure */
typedef struct 
{
	unsigned int dwWorkType;		/*Work mode: 1- switching; 2- dynamic connect to decoder; 3- playback by file; 4- playback by time*/
	char sDVRIP[16];		/*Connected device IP*/
	unsigned short wDVRPort;			/*Connected port number*/
	unsigned char byChannel;			/*Channel number */
	unsigned char byLinkMode;		/*Connection mode */
	unsigned int	dwLinkType;		/*Connection stream type: 0- main stream; 1- sub stream*/
	union
	{
		struct
		{
			unsigned char sUserName[NAME_LEN];	/*Username*/
			unsigned char sPassword[PASSWD_LEN];	/* Password */
			char cReserve[52];
		}userInfo;
		struct
		{
			unsigned char   fileName[100];
		}fileInfo;
		struct
		{
			unsigned int	dwChannel;
			unsigned char	sUserName[NAME_LEN];	/*Username*/
			unsigned char	sPassword[PASSWD_LEN];	/* Password */
			NET_DVR_TIME struStartTime;		/* Start position for playback by time */
			NET_DVR_TIME struStopTime;		/* End position for playback by time */
		}timeInfo;
	}objectInfo;
}NET_DVR_DECCHANSTATUS, *LPNET_DVR_DECCHANSTATUS;

typedef struct 
{
	unsigned int   dwSize;
	NET_DVR_DECCHANSTATUS struDecState[MAX_DECNUM];
}NET_DVR_DECSTATUS, *LPNET_DVR_DECSTATUS;
/*****************************DS-6001D/F(end)***************************/

//Single Character Struct (Sub Struct)
typedef struct 
{
	unsigned short wShowString;				//enable text overlay on preview image: 0-disable; 1-enable. The display area ranges totally 704*576 , with single character size as 32*32
	unsigned short wStringSize;				/* text length, no more than 44 text character */
	unsigned short wShowStringTopLeftX;		/* top left X axis position for text overlay*/
	unsigned short wShowStringTopLeftY;		/* top left Y axis position for text overlay */
	char sString[44];				/* overlay text content*/
}NET_DVR_SHOWSTRINGINFO, *LPNET_DVR_SHOWSTRINGINFO;

//Text Overlay (9000extended)
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_SHOWSTRINGINFO struStringInfo[MAX_STRINGNUM_V30];				/* Content for display */
}NET_DVR_SHOWSTRING_V30, *LPNET_DVR_SHOWSTRING_V30;

//Text Overlay extended(8 lines)
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_SHOWSTRINGINFO struStringInfo[MAX_STRINGNUM_EX];				/* Content for display  */
}NET_DVR_SHOWSTRING_EX, *LPNET_DVR_SHOWSTRING_EX;

//Text Overlay 
typedef struct 
{
	unsigned int dwSize;
	NET_DVR_SHOWSTRINGINFO struStringInfo[MAX_STRINGNUM];				/* Content for display  */
}NET_DVR_SHOWSTRING, *LPNET_DVR_SHOWSTRING;

/****************************DS9000 added Structure(begin)******************************/

/*
EMAIL Parameters Struct
*/
typedef struct
{		
	unsigned int		dwSize;
	unsigned char		sAccount[NAME_LEN];				/* Email Account*/
	unsigned char		sPassword[MAX_EMAIL_PWD_LEN];			/*Password */
	struct
	{
		unsigned char	sName[NAME_LEN];				/* sender name */
		unsigned char	sAddress[MAX_EMAIL_ADDR_LEN];		/* sender address */
	}struSender;
	unsigned char		sSmtpServer[MAX_EMAIL_ADDR_LEN];	/* SMTP server */
	unsigned char		sPop3Server[MAX_EMAIL_ADDR_LEN];	/* POP3 server */
	struct
	{
		unsigned char	sName[NAME_LEN];				/* receiver Name */
		unsigned char	sAddress[MAX_EMAIL_ADDR_LEN];		/* receiver address */
	}struReceiver[3];							/* support up to 3 receivers */
	unsigned char		byAttachment;					/* with attached snapshot or not */
	unsigned char		bySmtpServerVerify;				/* Enable Email server authentication: 1-enable; 0-disable */
    unsigned char        byMailInterval;                 /* mail interval 0-2s, 1-3s, 2-4s. 3-5s*/
	unsigned char        byEnableSSL;					//enalbe ssl
	unsigned short        wSmtpPort;						//gmail default 465, else default 25
	unsigned char        byRes[74];						//reserve
} NET_DVR_EMAILCFG_V30, *LPNET_DVR_EMAILCFG_V30;

/*
DVR Cruise Structure
*/
typedef struct
{	
	unsigned int 	dwSize;
	unsigned char	byPresetNo[CRUISE_MAX_PRESET_NUMS];		/* Preset No. */
	unsigned char 	byCruiseSpeed[CRUISE_MAX_PRESET_NUMS];	/* Cruise Speed */
	unsigned short	wDwellTime[CRUISE_MAX_PRESET_NUMS];		/* Dwell time */
	unsigned char	byEnableThisCruise;						/* Enable this cruise */
	unsigned char	res[15];
}NET_DVR_CRUISE_PARA, *LPNET_DVR_CRUISE_PARA; 
/****************************DS9000 Added(end)******************************/


//Time
typedef struct 
{
	unsigned int dwMonth;		//Month 0-11 for 1-12 month
	unsigned int dwWeekNo;		//Week 0－First Week 1－Second Week 2－Third Week 3－Fourth Week 4－last Week
	unsigned int dwWeekDate;	//Day 0－Sun 1－Mon 2－Tue 3－Wed 4－Thu 5－Fri 6－Sat
	unsigned int dwHour;		//begin/end hour, begin hour ranges from 0-23, and end hour ranges from 1-23
	unsigned int dwMin;		//begin/stop minutes ranges from 0-59
}NET_DVR_TIMEPOINT;

//Time Zone & DST 
typedef struct 
{
	unsigned int dwSize;
	unsigned char byRes1[16];			//Reserved
	unsigned int dwEnableDST;		//enable DST, 0-dsiable; 1-enable
	unsigned char byDSTBias;			//DST bias; 30min, 60min, 90min, 120min, count with minute
	unsigned char byRes2[3];
	NET_DVR_TIMEPOINT struBeginPoint;	//DST start time
	NET_DVR_TIMEPOINT struEndPoint;		//DST stop time
}NET_DVR_ZONEANDDST, *LPNET_DVR_ZONEANDDST;



//Image Quality
typedef struct 
{
	/*Note: If encoding resolution is VGA，it supports grabbing 0=CIF, 1=QCIF, 2=D1 image.
	But if encoding resolution is 3=UXGA(1600x1200), 4=SVGA(800x600), 5=HD720p(1280x720), 6=VGA, 7=XVGA, and 8=HD900p it only support grabbing image with current resolution*/
	unsigned short	wPicSize;				/* 0=CIF; 1=QCIF; 2=D1; for IPCAM {3=UXGA(1600x1200), 4=SVGA(800x600), 5=HD720p(1280x720),6=VGA, 7=XVGA, 8=HD900p}*/
	unsigned short	wPicQuality;			/* 0 - the best, 1 - better, 2 - average; */
}NET_DVR_JPEGPARA, *LPNET_DVR_JPEGPARA;

/* aux video out parameter */
//AUX Output Parameter
typedef struct 
{
	unsigned int dwSize;
	unsigned int dwAlarmOutChan;                       /* 0–main video output; 1–aux1 video output; 2–aux2 video output; 3–aux3 video output; 4–aux4 video output*/
	unsigned int dwAlarmChanSwitchTime;                /* :1Sec - 10:10Sec */
	unsigned int dwAuxSwitchTime[MAX_AUXOUT];			/* aux output switch time：0- no switch; 1-5sec；2-10sec；3-20sec；4-30sec；5-60sec；6-120sec；7-300sec*/
	unsigned char  byAuxOrder[MAX_AUXOUT][MAX_WINDOW];	/* aux output preview sequence, 0xff means not preview the camera */
}NET_DVR_AUXOUTCFG, *LPNET_DVR_AUXOUTCFG;


//ntp
typedef struct 
{
	unsigned char sNTPServer[64];   /* Domain Name or IP addr of NTP server */
	unsigned short wInterval;		 /* adjust time interval(hours) */
	unsigned char byEnableNTP;    /* enable NPT client 0-no，1-yes*/
	signed char cTimeDifferenceH; /* Difference with Standard Time (Hour): ranges from -12 ... +13 */
	signed char cTimeDifferenceM;/* Difference with Standard Time (Minute)*/
	unsigned char res1;
    unsigned short wNtpPort;         /* ntp server port(9000 added), 123 is defaulty*/
    unsigned char res2[8];
}NET_DVR_NTPPARA, *LPNET_DVR_NTPPARA;

//DDNS
typedef struct 
{
	unsigned char sUsername[NAME_LEN];  /* DDNS Username*/
	unsigned char sPassword[PASSWD_LEN];/*Password */
	unsigned char sDomainName[64];       /* Domain name */
	unsigned char byEnableDDNS;			/*Enable DDNS 0-disable，1-enable*/
	unsigned char res[15];
}NET_DVR_DDNSPARA, *LPNET_DVR_DDNSPARA;


typedef struct
{
	unsigned char byHostIndex;					/* 0-Hikvision DNS(Reserved) 1－Dyndns 2－PeanutHull 3-xw3322  */
	unsigned char byEnableDDNS;					/*enable DDNS: 0-disable; 1-enable*/
	unsigned short wDDNSPort;						/* DDNS port */
	unsigned char sUsername[NAME_LEN];			/* DDNS Username*/
	unsigned char sPassword[PASSWD_LEN];			/* DDNS Password */
	unsigned char sDomainName[MAX_DOMAIN_NAME];	/* DVR domain name*/
	unsigned char sServerName[MAX_DOMAIN_NAME];	/* DDNS server domain name or IP */
	unsigned char byRes[16];
}NET_DVR_DDNSPARA_EX, *LPNET_DVR_DDNSPARA_EX;

//9000extended
typedef struct
{
    unsigned char byEnableDDNS;
    unsigned char byHostIndex;/* 0-Hikvision DNS(Reserved) 1－Dyndns 2－PeanutHull 3-xw3322 */
    unsigned char byRes1[2];
    struct
    {    
        unsigned char sUsername[NAME_LEN];			/* DDNS Username*/
        unsigned char sPassword[PASSWD_LEN];			/* Password */
        unsigned char sDomainName[MAX_DOMAIN_NAME];	/* DVR domain name */
        unsigned char sServerName[MAX_DOMAIN_NAME];	/* DDNS server domain name or IP*/
        unsigned short wDDNSPort;						/* Port */
        unsigned char byRes[10];
    } struDDNS[MAX_DDNS_NUMS];
    unsigned char byRes2[16];
}NET_DVR_DDNSPARA_V30, *LPNET_DVR_DDNSPARA_V30;

//email
typedef struct 
{
	unsigned char sUsername[64];  /* Email Account */
	unsigned char sPassword[64];
	unsigned char sSmtpServer[64];
	unsigned char sPop3Server[64];
	unsigned char sMailAddr[64];   /* email */
	unsigned char sEventMailAddr1[64];  /* email for upload Alarm/Exception */
	unsigned char sEventMailAddr2[64];
	unsigned char res[16];
}NET_DVR_EMAILPARA, *LPNET_DVR_EMAILPARA;

//Network Parameter
typedef struct 
{
	unsigned int  dwSize;
	char  sDNSIp[16];                /* DNS Server IP */
	NET_DVR_NTPPARA  struNtpClientParam;      /* NTP Parameters */
	NET_DVR_DDNSPARA struDDNSClientParam;     /* DDNS Parameters */
	unsigned char res[464];			/* Reserved */
}NET_DVR_NETAPPCFG, *LPNET_DVR_NETAPPCFG;

//nfs Structure Configuration
typedef struct
{
    char sNfsHostIPAddr[16];
    unsigned char sNfsDirectory[PATHNAME_LEN];        // PATHNAME_LEN = 128
}NET_DVR_SINGLE_NFS, *LPNET_DVR_SINGLE_NFS;

typedef struct 
{
	unsigned int  dwSize;
	NET_DVR_SINGLE_NFS struNfsDiskParam[MAX_NFS_DISK];
}NET_DVR_NFSCFG, *LPNET_DVR_NFSCFG;

//Cruise Point Configuration(for HIK IP Speed Dome)
typedef struct
{
    unsigned char	PresetNum;	//Preset
    unsigned char	Dwell;		//Dwell time
    unsigned char	Speed;		//Speed
    unsigned char	Reserve;	//Reserved
}NET_DVR_CRUISE_POINT, *LPNET_DVR_CRUISE_POINT;

typedef struct 
{
	NET_DVR_CRUISE_POINT struCruisePoint[32];			//32 pints in total
}NET_DVR_CRUISE_RET, *LPNET_DVR_CRUISE_RET;

/************************************Multi-Channel Decoder(begin)***************************************/
typedef struct 
{
	unsigned int	dwSize;
	char	sFirstDNSIP[16];
	char	sSecondDNSIP[16];
	char	sRes[32];
}NET_DVR_NETCFG_OTHER, *LPNET_DVR_NETCFG_OTHER;

typedef struct 
{
	char 	sDVRIP[16];				/* DVR IP */
	unsigned short 	wDVRPort;			 	/* Port */
	unsigned char 	byChannel;				/* Channel No. */
	unsigned char	byTransProtocol;			/* Network Protocol 0-TCP, 1-UDP */
	unsigned char	byTransMode;				/* Stream Type 0 - Main Stream 1 - Sub Stream*/
	unsigned char	byRes[3];
	unsigned char	sUserName[NAME_LEN];			/* DVR login user name */
	unsigned char	sPassword[PASSWD_LEN];			/* DVR login Password */
}NET_DVR_MATRIX_DECINFO, *LPNET_DVR_MATRIX_DECINFO;

//Dynamic Decoding
typedef struct 
{
	unsigned int	dwSize;
	NET_DVR_MATRIX_DECINFO struDecChanInfo;		/*Info of Dynamic Decoding Channel*/
}NET_DVR_MATRIX_DYNAMIC_DEC, *LPNET_DVR_MATRIX_DYNAMIC_DEC;

typedef struct  
{
    unsigned int 	dwSize;
    unsigned int   dwIsLinked;         /* Network link status tag, 0: Sleep, 1: linking, 2: linked, 3: decoding */
    unsigned int   dwStreamCpRate;     /* Stream copy rate, X kbits/second */
    char    cRes[64];		/* Reserved */
}NET_DVR_MATRIX_DEC_CHAN_STATUS, *LPNET_DVR_MATRIX_DEC_CHAN_STATUS;

typedef struct 
{
	unsigned int	dwSize;
	NET_DVR_MATRIX_DECINFO struDecChanInfo;		/* Decode channel information  */
	unsigned int	dwDecState;	/* 0-dynamic decode 1- switch decode 2-playback by time 3-playback by file */
	NET_DVR_TIME StartTime;		/* start time for playback by time mode, */
	NET_DVR_TIME StopTime;		/* stop time for playback by time mode */
	char    sFileName[128];		/* file name for playback by file mode */
}NET_DVR_MATRIX_DEC_CHAN_INFO, *LPNET_DVR_MATRIX_DEC_CHAN_INFO;

//Channel Connected Configuration 2007-11-05
typedef struct 
{
	unsigned int dwEnable;					/*0-Disable 1-Enable*/
	NET_DVR_MATRIX_DECINFO struDecChanInfo;		/* Info of switching decoding channel */
}NET_DVR_MATRIX_DECCHANINFO, *LPNET_DVR_MATRIX_DECCHANINFO;

//2007-11-05 Configuration for each channel
typedef struct 
{
	unsigned int	dwSize;
	unsigned int	dwPoolTime;			/*Switch interval */
	NET_DVR_MATRIX_DECCHANINFO struchanConInfo[MAX_CYCLE_CHAN];
}NET_DVR_MATRIX_LOOP_DECINFO, *LPNET_DVR_MATRIX_LOOP_DECINFO;

//2007-12-22
typedef struct 
{
	unsigned char	baudrate; 		/* baud rate */
	unsigned char	databits;		/* Data bit */
	unsigned char	stopbits;		/* Stop bit*/
	unsigned char	parity;			/* Parity digit */
	unsigned char	flowcontrol;	/* Flow control */
	unsigned char	res[3];
}TTY_CONFIG, *LPTTY_CONFIG;

typedef struct  
{					
	unsigned char byTranChanEnable;	/* Open current transparent channel or not 0: close 1: open */
	/*
		There is a 232 interface and a 485 interface on the decoder, which can all be set as transparent channel, device number can be distributed as below:
		0 - RS485;1 - RS232 Console
	 */
	unsigned char	byLocalSerialDevice;			/* Local serial device */
	/*
	 *	Remote output serial device
	 *	1-RS232
	 *	2-RS485
	 */
	unsigned char	byRemoteSerialDevice;			/* Remote output serial device */
	unsigned char	res1;							/* Reserved */
	char	sRemoteDevIP[16];				/* Remote Device IP */
	unsigned short	wRemoteDevPort;					/* Remote Net Communication Port */
	unsigned char	res2[2];						/* Reserved */
	TTY_CONFIG RemoteSerialDevCfg;
}NET_DVR_MATRIX_TRAN_CHAN_INFO, *LPNET_DVR_MATRIX_TRAN_CHAN_INFO;

typedef struct  
{
	unsigned int dwSize;
	unsigned char 	by232IsDualChan; /* Set full-duplex 232 transparent channel, set value ranges from 1 to MAX_SERIAL_NUM */
	unsigned char	by485IsDualChan; /* Set full-duplex 485 transparent channel, set value ranges from 1 to MAX_SERIAL_NUM */
	unsigned char	res[2];	/* Reserved */
	NET_DVR_MATRIX_TRAN_CHAN_INFO struTranInfo[MAX_SERIAL_NUM];/*Support to create transparent channel number up to MAX_SERIAL_NUM*/
}NET_DVR_MATRIX_TRAN_CHAN_CONFIG, *LPNET_DVR_MATRIX_TRAN_CHAN_CONFIG;

//2007-12-24 Merry Christmas Eve...
typedef struct 
{
	unsigned int	dwSize;
	char	sDVRIP[16];			/* DVR IP */	
	unsigned short	wDVRPort;			/* Port */
	unsigned char	byChannel;			/* Channel Port */
	unsigned char 	byReserve;
	unsigned char	sUserName[NAME_LEN];		/* Username */
	unsigned char	sPassword[PASSWD_LEN];		/* Password */
	unsigned int	dwPlayMode;   	/* 0-by file 1- by time*/
	NET_DVR_TIME StartTime;
	NET_DVR_TIME StopTime;
	char    sFileName[128];
}NET_DVR_MATRIX_DEC_REMOTE_PLAY, *LPNET_DVR_MATRIX_DEC_REMOTE_PLAY;

/* Commands for playing file*/
#define NET_DVR_PLAYSTART		1//Start play
#define NET_DVR_PLAYSTOP		2//Stop play
#define NET_DVR_PLAYPAUSE		3//Pause
#define NET_DVR_PLAYRESTART		4//Restore
#define NET_DVR_PLAYFAST		5//Play Faster
#define NET_DVR_PLAYSLOW		6//Play Slower
#define NET_DVR_PLAYNORMAL		7//Normal Speed
#define NET_DVR_PLAYSTARTAUDIO	9//Open Audio
#define NET_DVR_PLAYSTOPAUDIO	10//Close Audio
#define NET_DVR_PLAYSETPOS		12//Change playing progress

typedef struct 
{
	unsigned int	dwSize;
	unsigned int	dwPlayCmd;		/* Command of Play*/
	unsigned int	dwCmdParam;		/* Parameter of Command*/
}NET_DVR_MATRIX_DEC_REMOTE_PLAY_CONTROL, *LPNET_DVR_MATRIX_DEC_REMOTE_PLAY_CONTROL;

typedef struct  
{
	unsigned int dwSize;
	unsigned int dwCurMediaFileLen;		/* Current file length  */
	unsigned int dwCurMediaFilePosition;	/* Current file position */
	unsigned int dwCurMediaFileDuration;	/* Current file duration */
	unsigned int dwCurPlayTime;			/* Current playback time  */
	unsigned int dwCurMediaFIleFrames;		/* Current playback frame number  */
	unsigned int dwCurDataType;			/* Current strean type, 19-file header, 20- stream data, 21-end */
	unsigned char res[72];
}NET_DVR_MATRIX_DEC_REMOTE_PLAY_STATUS, *LPNET_DVR_MATRIX_DEC_REMOTE_PLAY_STATUS;


//Multi-channels Decoder new
typedef struct tagNET_MATRIX_PASSIVEMODE
{
    unsigned short	wTransProtol;		//Transfer Protocol,0-TCP, 1-UDP, 2-MCAST
    unsigned short	wPassivePort;		//UDP port. When TCP, use default value
    NET_DVR_IPADDR  struMcastIP;//Multicast address, invalid when using TCP or UDP,
    unsigned char	byStreamType;/* playmode:REAL_TIME_STREAM(1)realtime,RECORD_STREAM(2)record */
    unsigned char	byRes[7];
}NET_DVR_MATRIX_PASSIVEMODE, *LPNET_DVR_MATRIX_PASSIVEMODE;

typedef struct tagDEV_CHAN_INFO
{
    NET_DVR_IPADDR struIP;				/*DVR IP address  */
    unsigned short 	wDVRPort;			 	/* Port  */
    unsigned char 	byChannel;				/* Channel Number */
    unsigned char	byTransProtocol;		/* Transfer Protocol: 0-TCP,1-UDP */
    unsigned char	byTransMode;			/* Transfer Mode: 0-Main Stream, 1-Sub Stream*/
    unsigned char	byRes[71];
    unsigned char	sUserName[NAME_LEN];	/* User name of surveillance host */
    unsigned char	sPassword[PASSWD_LEN];	/* Password of surveillance host */
} NET_DVR_DEV_CHAN_INFO,*LPNET_DVR_DEV_CHAN_INFO;

typedef struct tagMATRIX_TRAN_CHAN_INFO 
{					
	unsigned char byTranChanEnable;	/*Transparent Channel State: 0-Close, 1-Open */
							/*
							*	Multi-channel Decoder has 1 RS485 port and 1 RS232 Port, both of them can be transparent channel. Device Number is :
							*	0 - RS485
							*	1 - RS232 Console
	*/
	unsigned char	byLocalSerialDevice;			/* Local serial device */
											/*
											*	Remote Serial Output Port: one RS232 and one RS485
											*	1 - RS232
											*	2 - RS485
	*/
	unsigned char	byRemoteSerialDevice;			/* Remote output serial device */
	unsigned char	res1;							/* Reserved */
	// char	sRemoteDevIP[16];				/* Remote Device IP */
    NET_DVR_IPADDR  struRemoteDevIP;
	unsigned short    wRemoteDevPort;				/* Remote Net Communication Port */
    unsigned char  byIsEstablished;	/* Establish Transparent channel:0-Failure, 1-Success*/
    unsigned char	res2[1];					/* Reserved */
	TTY_CONFIG RemoteSerialDevCfg;
	unsigned char  	byUsername[NAME_LEN]; 		/* 32BYTES */
	unsigned char   	byPassword[PASSWD_LEN]; 	/* 16BYTES */
	unsigned char 	res3[16];					/* Reserved */
} NET_DVR_MATRIX_TRAN_CHAN_INFO_V30,*LPNET_DVR_MATRIX_TRAN_CHAN_INFO_V30;

typedef struct tagMATRIX_TRAN_CHAN_CONFIG 
{
	unsigned int   dwSize;
	unsigned char 	by232IsDualChan; /* Set this RS232 transparent channel as Duplex:1 ~ MAX_SERIAL_NUM*/
	unsigned char	by485IsDualChan; /* Set this RS485 transparent channel as Duplex:1 ~ MAX_SERIAL_NUM */
	unsigned char	vyRes[2];	/* Reserved */
	NET_DVR_MATRIX_TRAN_CHAN_INFO_V30 struTranInfo[MAX_SERIAL_NUM];/*Support MAX_SERIAL_NUM Transparent channels simultaneously*/
}NET_DVR_MATRIX_TRAN_CHAN_CONFIG_V30,*LPNET_DVR_MATRIX_TRAN_CHAN_CONFIG_V30;

/*Streaming Media Server Config*/
typedef struct
{
    unsigned char	byValid;	/*Enable Streaming Media Server to get stream: 0-disable, others - Enable*/
    unsigned char	byRes1[3];
    NET_DVR_IPADDR  struDevIP;
    unsigned short	wDevPort;		/*Port of Streaming Media Server*/
    unsigned char	byTransmitType;		/*Transfer Protocol of Streaming Media Server 0-TCP,1-UDP*/
    unsigned char	byRes2[69];
}NET_DVR_STREAM_MEDIA_SERVER_CFG,*LPNET_DVR_STREAM_MEDIA_SERVER_CFG;

typedef struct
{
    unsigned int								dwSize;
    NET_DVR_STREAM_MEDIA_SERVER_CFG	struStreamMediaSvrCfg;
    NET_DVR_DEV_CHAN_INFO			struDevChanInfo;
}NET_DVR_PU_STREAM_CFG,*LPNET_DVR_PU_STREAM_CFG;

typedef struct  
{
    unsigned int								dwEnable;	/*0-Disable, 1-Enable*/
    NET_DVR_STREAM_MEDIA_SERVER_CFG	streamMediaServerCfg;	
    NET_DVR_DEV_CHAN_INFO 		struDevChanInfo;		/* Loop Decoding channel info */
}NET_DVR_MATRIX_CHAN_INFO_V30,*LPNET_DVR_CYC_SUR_CHAN_ELE_V30;

typedef struct  tagMATRIX_LOOP_DECINFO_V30
{
    unsigned int							dwSize;
    unsigned int							dwPoolTime;		/*Loop Interval*/
    NET_DVR_MATRIX_CHAN_INFO_V30	struchanConInfo[MAX_CYCLE_CHAN_V30];
    unsigned char               				byRes[16];
} NET_DVR_MATRIX_LOOP_DECINFO_V30,*LPNET_DVR_MATRIX_LOOP_DECINFO_V30;


typedef struct tagDEC_MATRIX_CHAN_INFO
{
    unsigned int	dwSize;
    NET_DVR_STREAM_MEDIA_SERVER_CFG streamMediaServerCfg;	/*Streaming Media Server Config*/
    NET_DVR_DEV_CHAN_INFO 			  struDevChanInfo;		/*Decoding Channel Info  */
    unsigned int	dwDecState;		/*  0-Dynamic Decoding, 1-Loop Decoding 2-Playback by time, 3-Playback by file */
    NET_DVR_TIME StartTime;		/* Start time of playback by time */
    NET_DVR_TIME StopTime;			/* End time of playback by time */
    char    sFileName[128];		/* File name for playback by file */
    unsigned int   dwGetStreamMode;	/*Fetch Stream Mode:1-Positive,2-Passive*/
    NET_DVR_MATRIX_PASSIVEMODE      struPassiveMode;
    unsigned char	byRes[32];
}NET_DVR_MATRIX_DEC_CHAN_INFO_V30,*LPNET_DVR_MATRIX_DEC_CHAN_INFO_V30;


typedef struct tagNET_DVR_MATRIX_ABILITY
{
    unsigned int dwSize;
    unsigned char  byDecNums;
    unsigned char  byStartChan;
    unsigned char  byVGANums;
    unsigned char  byBNCNums;
    unsigned char  byVGAWindowMode[8][12];     /*Window Mode of VGA*/
    unsigned char  byBNCWindowMode[4];       	/*Window Mode of BNC*/
    unsigned char  byDspNums;
	unsigned char  byRes1[15];
	unsigned char  bySupportResolution[32];//按照上面的枚举定义,一个字节代表一个分辨率是//否支持，1：支持，0：不支持
	unsigned char  byRes2[120];
}NET_DVR_MATRIX_ABILITY, *LPNET_DVR_MATRIX_ABILITY;/* Video Output Info of decoder */
//Upload Logo
typedef struct tagNET_DVR_DISP_LOGOCFG
{
    unsigned int		dwCorordinateX;	//X-coordinate for logo display
    unsigned int		dwCorordinateY;	//Y-coordinate for logo display
    unsigned char        byRes1[8];
    unsigned char        byFlash;  //Flash or not: 1-Flash, 0-Not flash
    unsigned char        byTranslucent; //Translucence or not: 1-Yes, 0-NO
    unsigned char		byRes2[6];				//Reserved
    unsigned int		dwLogoSize;//LOGO size including BMP file head
}NET_DVR_DISP_LOGOCFG,*LPNET_DVR_DISP_LOGOCFG;

/*Encoding Format*/
#define NET_DVR_ENCODER_UNKOWN 0 /*Unknown Format*/
#define NET_DVR_ENCODER_H264   1 /*HIK 264*/
#define NET_DVR_ENCODER_S264  2 /*Standard H264*/
#define NET_DVR_ENCODER_MPEG4  3 /*MPEG4*/
/* Encapsulation Format */
#define NET_DVR_STREAM_TYPE_UNKOWN   0     /*Unknown Format*/
#define NET_DVR_STREAM_TYPE_HIKPRIVT   1     /*Hikvision Format*/
#define NET_DVR_STREAM_TYPE_TS    7   /* TS */
#define NET_DVR_STREAM_TYPE_PS   8   /* PS */
#define NET_DVR_STREAM_TYPE_RTP  9    /* RTP */

/*State of decoding channel*/
typedef struct
{
	unsigned char  byDecodeStatus;	/*Status: 0-Disabled, 1-Enabled*/
    unsigned char  byStreamType;     /*Stream Type*/
    unsigned char  byPacketType;     /*Encapsulation Type*/
    unsigned char  byRecvBufUsage;	/*Usage of receiving buffer*/
    unsigned char  byDecBufUsage;	/*Usage of decoding buffer*/
    unsigned char  byFpsDecV;		/*video decoding frame*/
    unsigned char  byFpsDecA;		/*audio decoding frame*/
    unsigned char  byCpuLoad;		/*DSP CPU usage*/
	unsigned char  byRes1[4];		//Reserved
    unsigned int dwDecodedV;		/*Decoded Video Frame*/
    unsigned int dwDecodedA;		/*Decoded Audio Frame*/
    unsigned short wImgW;				/*Current Image size*/
    unsigned short wImgH;
    unsigned char byVideoFormat; /*inputted Video standard: 1-PAL, 2-NTSC*/
    unsigned char byRes2[27];
}NET_DVR_MATRIX_CHAN_STATUS, *LPNET_DVR_MATRIX_CHAN_STATUS;

/*Status of Display Channel*/
#define NET_DVR_MAX_DISPREGION 16         /*Maximum display regions of each display channel*/

//Available VGA resolution: VGA_THS8200_MODE_XGA_60HZ,VGA_THS8200_MODE_SXGA_60HZ,
typedef enum
{
    VGA_NOT_AVALIABLE,
    VGA_THS8200_MODE_SVGA_60HZ,    //（800*600）
    VGA_THS8200_MODE_SVGA_75HZ,    //（800*600）
    VGA_THS8200_MODE_XGA_60HZ,      //（1024*768）
    VGA_THS8200_MODE_XGA_70HZ,       //（1024*768）
    VGA_THS8200_MODE_SXGA_60HZ,     //（1280*1024）
    VGA_THS8200_MODE_720P_60HZ,      //（1280*720 ）
    VGA_THS8200_MODE_1080i_60HZ,       //（1920*1080）
    VGA_THS8200_MODE_1080P_30HZ,      //（1920*1080）
    VGA_THS8200_MODE_1080P_25HZ,      //（1920*1080）
    VGA_THS8200_MODE_UXGA_30HZ        //（1600*1200）
}VGA_MODE;

//低帧率定义
#define           LOW_DEC_FPS_1_2                51
#define           LOW_DEC_FPS_1_4                52
#define           LOW_DEC_FPS_1_8                53
#define           LOW_DEC_FPS_1_16               54

/*Video Standard*/
typedef enum
{
    VS_NON = 0,
    VS_NTSC = 1,
    VS_PAL = 2
}VIDEO_STANDARD;

typedef struct tagNET_DVR_VGA_DISP_CHAN_CFG
{        
    unsigned int	dwSize;
    unsigned char	byAudio;			/*Enable Audio,0-No,1-Yes*/
    unsigned char    byAudioWindowIdx;      /*child window of enabled audio*/
    unsigned char 	byVgaResolution;      /*VGA resolution*/
    unsigned char	byVedioFormat;         /*Video Standard, 1:NTSC,2:PAL,0-NON*/
    unsigned int	dwWindowMode;		/*Windows layout mode gotten from Capability Set: 1,2,4,9,16 windows*/
    unsigned char	byJoinDecChan[MAX_WINDOWS];/*Decoding channel associated by each display window*/
    unsigned char	byEnlargeStatus;          /*0：Enlarge，1：not enlarge*/
    unsigned char    byEnlargeSubWindowIndex;//Sub WindowIndex
    unsigned char	byRes[18];
}NET_DVR_VGA_DISP_CHAN_CFG,*LPNET_DVR_VGA_DISP_CHAN_CFG;

/*Status of Display Channel*/
#define NET_DVR_MAX_DISPREGION 16 /*Maximum display regions of each display channel*/
typedef struct
{
    unsigned char  byDispStatus;          /*Display Status:0-No Display,1-Enabled*/
    unsigned char  byBVGA;                /*VGA/BNC*/
    unsigned char  byVideoFormat;        /*Video Standard:1-PAL, 2-NTSC*/
    unsigned char  byWindowMode;        /*Current window Layout*/
    unsigned char  byJoinDecChan[MAX_WINDOWS];        /*Decoding channel of each region*/
    unsigned char  byFpsDisp[NET_DVR_MAX_DISPREGION]; /*Display frame rate of each region*/
    unsigned char  byRes2[32];
}NET_DVR_DISP_CHAN_STATUS, *LPNET_DVR_DISP_CHAN_STATUS;

#define MAX_DECODECHANNUM   32//Maximum number of decoding channel
#define MAX_DISPCHANNUM   24//Maximum number of display channel
/*Decoder Status*/
typedef struct tagNET_DVR__DECODER_WORK_STATUS
{
    unsigned int dwSize;
    NET_DVR_MATRIX_CHAN_STATUS struDecChanStatus[MAX_DECODECHANNUM]; /*Status of decoding channel*/
    NET_DVR_DISP_CHAN_STATUS   struDispChanStatus[MAX_DISPCHANNUM];  /*Status of display channel*/
    unsigned char byAlarmInStatus[MAX_ANALOG_ALARMIN];         /*Status of Alarm input*/
    unsigned char byAalarmOutStatus[MAX_ANALOG_ALARMOUT];       /*Status of Alarm output*/
    unsigned char byAudioInChanStatus;          /*Status of intercom*/
    unsigned char byRes[127];
}NET_DVR_DECODER_WORK_STATUS,*LPNET_DVR_DECODER_WORK_STATUS;

//2009-12-1 增加被动解码播放控制
typedef struct tagNET_DVR_PASSIVEDECODE_CONTROL
{
    unsigned int	dwSize;
    unsigned int	dwPlayCmd;		/* 播放命令 见文件播放命令*/
    unsigned int	dwCmdParam;		/* 播放命令参数 */
    unsigned char	byRes[16];//Reverse
}NET_DVR_PASSIVEDECODE_CONTROL,*LPNET_DVR_PASSIVEDECODE_CONTROL;

#define		PASSIVE_DEC_PAUSE				1	/*被动解码暂停*/
#define		PASSIVE_DEC_RESUME				2	/*恢复被动解码*/
#define 	PASSIVE_DEC_FAST          	    3   /*快速被动解码*/
#define 	PASSIVE_DEC_SLOW			    4   /*慢速被动解码*/
#define 	PASSIVE_DEC_NORMAL      	    5   /*正常被动解码*/
#define 	PASSIVE_DEC_ONEBYONE      	    6   /*被动解码单帧播放*/
#define 	PASSIVE_DEC_AUDIO_ON 		    7   /*音频开启*/
#define 	PASSIVE_DEC_AUDIO_OFF		    8  	 /*音频关闭*/
//2009-12-16 增加控制解码器解码通道缩放
typedef struct tagNET_DVR_MATRIX_DECCHAN_CONTROL
{        
	unsigned int	dwSize;
	unsigned char	byDecChanScaleStatus;/*解码通道显示缩放控制,1表示缩放显示，0表示真实显示*/
	unsigned char	byRes[67];//Reverse
}NET_DVR_MATRIX_DECCHAN_CONTROL,*LPNET_DVR_MATRIX_DECCHAN_CONTROL;
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetDecChanCfg(int lUserID, unsigned int dwDecChan, LPNET_DVR_MATRIX_DECCHAN_CONTROL lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetDecChanCfg(int lUserID, unsigned int dwDecChan, LPNET_DVR_MATRIX_DECCHAN_CONTROL lpInter);
/************************************Decoder(end)***************************************/

typedef struct 
{	/* 12 bytes */
	unsigned int	dwSize;
	char	sUserName[32];
	char 	sPassWord[32];
	char 	sFromName[32];			/* Sender */
	char 	sFromAddr[48];			/* Sender address */
	char 	sToName1[32];			/* Receiver1 */
	char 	sToName2[32];			/* Receiver2 */
	char 	sToAddr1[48];			/* Receiver address1 */
	char 	sToAddr2[48];			/* Receiver address2 */
	char	sEmailServer[32];		/* Email server address */
	unsigned char	byServerType;			/* Email server type: 0-SMTP, 1-POP, 2-IMTP…*/
	unsigned char	byUseAuthen;			/* Email server authentication method: 1-enable, 0-disable */
	unsigned char	byAttachment;			/* enable attachment */
	unsigned char	byMailinterval;			/* mail interval 0-2s, 1-3s, 2-4s. 3-5s*/
} NET_DVR_EMAILCFG, *LPNET_DVR_EMAILCFG;

typedef struct 
{
	unsigned int dwSize;
	NET_DVR_COMPRESSION_INFO_EX  struLowCompression;	// Time Record
	NET_DVR_COMPRESSION_INFO_EX  struEventCompression;	//  Triggered by events
}NET_DVR_COMPRESSIONCFG_NEW, *LPNET_DVR_COMPRESSIONCFG_NEW;

//Posistion info of Speed Dome
typedef struct
{
    unsigned short wAction;//invalid
    unsigned short wPanPos;//pan position
    unsigned short wTiltPos;//tilt position
    unsigned short wZoomPos;//zoom position
}NET_DVR_PTZPOS, *LPNET_DVR_PTZPOS;

//PTZ Scope Structure 
typedef struct
{
    unsigned short wPanPosMin;//min pan position
    unsigned short wPanPosMax;//max pan position
    unsigned short wTiltPosMin;//min tilt position
    unsigned short wTiltPosMax;//max tilt position
    unsigned short wZoomPosMin;//min zoom factor
    unsigned short wZoomPosMax;//max zoom factor
}NET_DVR_PTZSCOPE, *LPNET_DVR_PTZSCOPE;

//rtsp Configuration(Special for IP camera)
typedef struct
{
    unsigned int dwSize;         //Length
    unsigned short  wPort;          //rtsp Port
    unsigned char  byReserve[54];  //Reserved
}NET_DVR_RTSPCFG, *LPNET_DVR_RTSPCFG;


/********************************Interface Parameters Structure(begin)*********************************/

//NET_DVR_Login()
typedef struct
{
	unsigned char sSerialNumber[SERIALNO_LEN];   //SN
	unsigned char byAlarmInPortNum;		        //DVR Alarm input
	unsigned char byAlarmOutPortNum;		        //DVR Alarm Output
	unsigned char byDiskNum;				        //DVR Number of Hard Disk
	unsigned char byDVRType;				        //DVR Type, 1:DVR 2:ATM DVR 3:DVS ......
	unsigned char byChanNum;				        //DVR Number of Channel
	unsigned char byStartChan;			        //The first Channel No. E.g. DVS-1,DVR-1
}NET_DVR_DEVICEINFO, *LPNET_DVR_DEVICEINFO;

//NET_DVR_Login_V30()
typedef struct
{
    unsigned char sSerialNumber[SERIALNO_LEN];   //SN
    unsigned char byAlarmInPortNum;		        //Number of Alarm input
    unsigned char byAlarmOutPortNum;		        //Number of Alarm Output
    unsigned char byDiskNum;						//Number of Hard Disk
    unsigned char byDVRType;						//DVR Type, 1:DVR 2:ATM DVR 3:DVS ......
    unsigned char byChanNum;						//Number of Analog Channel
    unsigned char byStartChan;			        //The first Channel No. E.g. DVS-1,DVR-1
    unsigned char byAudioChanNum;                //Number of Audio Channel
    unsigned char byIPChanNum;					//Maximum number of IP Channel
	unsigned char byRes1[24];					//Reserved
}NET_DVR_DEVICEINFO_V30, *LPNET_DVR_DEVICEINFO_V30;

//sdk Network environment, for update
typedef enum _SDK_NET_ENV
{
    LOCAL_AREA_NETWORK = 0,
        WIDE_AREA_NETWORK
}SDK_NETWORK_ENVIRONMENT;

//Display Mode
typedef enum
{
	NORMALMODE = 0,
	OVERLAYMODE
}DISPLAY_MODE;

//Send Mode
typedef enum
{
	PTOPTCPMODE = 0,
	PTOPUDPMODE,
	MULTIMODE,
	RTPMODE,
	RESERVEDMODE
}SEND_MODE;

//Grub Mode
typedef enum 
{
	BMP_MODE = 0,		//BMP Mode
	JPEG_MODE = 1		//JPEG Mode 
}CAPTURE_MODE;

//Real time Audio mode
typedef enum
{
	MONOPOLIZE_MODE = 1,//exclusive mode
	SHARE_MODE = 2		//shared mode
}REALSOUND_MODE;

//Preview via software decoding
typedef struct
{
	int lChannel;//channel no.
	int lLinkMode;//If 31st bit is 0, it means connect main stream, is 1 means sub stream. Bit 0~bit 30 are used for link mode: 0: TCP mode, 1: UDP mode, 2: Multi-play mode, 3: RTP mode, 4: audio, video separated mode; 3-RTP mode
	HWND hPlayWnd;// the play window's handle; set NULL to disable preview
	char* sMultiCastIP; //Multicast group
}NET_DVR_CLIENTINFO, *LPNET_DVR_CLIENTINFO;

//SDK infromation(9000 added)
typedef struct 
{
    unsigned int dwTotalLoginNum;		//current login user operation number
    unsigned int dwTotalRealPlayNum;	//current realplay operation number
    unsigned int dwTotalPlayBackNum;	//current playback or download operation number
    unsigned int dwTotalAlarmChanNum;	//current alarm channel operation number
    unsigned int dwTotalFormatNum;		//current HDD format operation number
    unsigned int dwTotalFileSearchNum;	//current files search operation number
    unsigned int dwTotalLogSearchNum;	//current logs search operation number
    unsigned int dwTotalSerialNum;	    //current transparent series port operation number
    unsigned int dwTotalUpgradeNum;	//current upgrading operation number
    unsigned int dwTotalVoiceComNum;	//current network voice communication operation number
    unsigned int dwTotalBroadCastNum;	//current network broadcast voice communication operation number
    unsigned int dwRes[10];
}NET_DVR_SDKSTATE, *LPNET_DVR_SDKSTATE;

//SDK Ability Information (9000 added)
typedef struct 
{
    unsigned int dwMaxLoginNum;		//maximum login user operation number MAX_LOGIN_USERS
    unsigned int dwMaxRealPlayNum;		//maximum realplay operation number WATCH_NUM
    unsigned int dwMaxPlayBackNum;		//maximum playback or download operation number WATCH_NUM
    unsigned int dwMaxAlarmChanNum;	//maximum alarm channel operation number ALARM_NUM
    unsigned int dwMaxFormatNum;		//maximum HDD format operation number SERVER_NUM
    unsigned int dwMaxFileSearchNum;	//maximum files search operation number SERVER_NUM
    unsigned int dwMaxLogSearchNum;	//maximum logs search operation number SERVER_NUM
    unsigned int dwMaxSerialNum;	    //maximum transparent series port operation number SERVER_NUM
    unsigned int dwMaxUpgradeNum;	    //maximum current upgrading operation number SERVER_NUM
    unsigned int dwMaxVoiceComNum;		//maximum network voice communication operation number SERVER_NUM
    unsigned int dwMaxBroadCastNum;	//maximum network broadcast voice communication operation number MAX_CASTNUM
    unsigned int dwRes[10];
}NET_DVR_SDKABL, *LPNET_DVR_SDKABL;

//Alarm Device Infor
typedef struct
{   
    unsigned char byUserIDValid;                 /* Whether userid is valid, 0-invalid 1-valid. */
    unsigned char bySerialValid;                 /* Whether serial number is valid, 0-invalid 1-valid.  */
    unsigned char byVersionValid;                /* Whether version number is valid, 0-invalid 1-valid. */
    unsigned char byDeviceNameValid;             /* Whether device name is valid, 0-invalid 1-valid. */
    unsigned char byMacAddrValid;                /* Whether MAC address is valid, 0-invalid 1-valid. */
    unsigned char byLinkPortValid;               /* Whether login port number is valid, 0-invalid 1-valid. */
    unsigned char byDeviceIPValid;               /* Whether device IP is valid, 0-invalid 1-valid.*/
    unsigned char bySocketIPValid;               /* Whether socket IP is valid, 0-invalid 1-valid. */
    int lUserID;                       /* NET_DVR_Login()effective when establishing alarm upload channel*/
    unsigned char sSerialNumber[SERIALNO_LEN];	/* Serial number. */
    unsigned int dwDeviceVersion;			    /* Version number, 2 high unsigned char means the major version, 2 low unsigned char means the minor version*/
    char sDeviceName[NAME_LEN];		    /* Device name. */
    unsigned char byMacAddr[MACADDR_LEN];		/* MAC address */
    unsigned short wLinkPort;                     /* link port */
    char sDeviceIP[128];    			/* IP address */
    char sSocketIP[128];    			/* alarm push-mode socket IP address. */
    unsigned char byIpProtocol;                  /* IP protocol: 0-IPV4; 1-IPV6. */
    unsigned char byRes2[11];
}NET_DVR_ALARMER, *LPNET_DVR_ALARMER;

//Dispaly Area Parameter of Hardware Decoding(Sub Struct)
typedef struct
{
	int bToScreen;
	int bToVideoOut;
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
	int nReserved;
}NET_DVR_DISPLAY_PARA, *LPNET_DVR_DISPLAY_PARA;

//Preview Parameter of Hardware Decoding
typedef struct
{
	int lChannel;// Channel No.
	int lLinkMode; //0- TCP; 1- UDP; 2- Multicast; 3- RTP; 4- PPPoE; 5- 128k; 6- 256k; 7- 384k; 8- 512k
	char* sMultiCastIP;
	NET_DVR_DISPLAY_PARA struDisplayPara;
}NET_DVR_CARDINFO, *LPNET_DVR_CARDINFO;

//Record Parameters
typedef struct 
{
	char sFileName[100];// File Name
	NET_DVR_TIME struStartTime;//Start time of the file
	NET_DVR_TIME struStopTime;//End time of the file
	unsigned int dwFileSize;//File size
}NET_DVR_FIND_DATA, *LPNET_DVR_FIND_DATA;

//Record Parameters(9000)
typedef struct 
{
    char sFileName[100];//File Name
    NET_DVR_TIME struStartTime;//Start time of the file
    NET_DVR_TIME struStopTime;//End time of the file
    unsigned int dwFileSize;//File size
    char sCardNum[32];
    unsigned char byLocked;//9000 DVR supports this,1-file is locked,0-file is Normal
    unsigned char byRes[3];
}NET_DVR_FINDDATA_V30, *LPNET_DVR_FINDDATA_V30;

//Record Parameters(with Card No.)
typedef struct 
{
	char sFileName[100];//File Name
	NET_DVR_TIME struStartTime;//Start time of the file
	NET_DVR_TIME struStopTime;//End time of the file
	unsigned int dwFileSize;//File size
	char sCardNum[32];
}NET_DVR_FINDDATA_CARD, *LPNET_DVR_FINDDATA_CARD;


//Record Query Condition
typedef struct 
{
    int lChannel;//channel number
    unsigned int dwFileType;/*file record mode oxff: all, 0: scheduled record, 1: Motion detection, 2: alarm record, 3: motion detection| alarm, 4: motion detection & alarm 5: command trigger, 6: manually record*/
    unsigned int dwIsLocked;//whether file is locked, 0-normal; 1-locked;, 0xff-all
    unsigned int dwUseCardNo;//whether card no. is used
    unsigned char sCardNumber[32];//card no.
    NET_DVR_TIME struStartTime;//start time
    NET_DVR_TIME struStopTime;//end time
}NET_DVR_FILECOND, *LPNET_DVR_FILECOND;


// PTZ Image Zooming (Special for HIKVISION Speed dome)
typedef struct 
{
	int xTop;     //x coordinate of the origination point of the pane
	int yTop;     //y coordinate of the origination point of the pane
	int xBottom;  //x coordinate of the end point of the pane
	int yBottom;  //y coordinate of the end point of the pane
	int bCounter; //reserve
}NET_DVR_POINT_FRAME, *LPNET_DVR_POINT_FRAME;

//audio encode type
typedef struct tagNET_DVR_COMPRESSION_AUDIO
{
	unsigned char  byAudioEncType;   //AudioTalk Code Type 0-G722; 1-G711
	unsigned char  byres[7];   //reserve
}NET_DVR_COMPRESSION_AUDIO, *LPNET_DVR_COMPRESSION_AUDIO;
/********************************Interface Parameter Struct(end)*********************************/


/********************************SDK API Definition*********************************/
NET_DVR_API BOOL __stdcall NET_DVR_Init();
NET_DVR_API BOOL __stdcall NET_DVR_Cleanup();

//NET_DVR_SetDVRMessage的extended
#ifdef _WIN32
NET_DVR_API BOOL __stdcall NET_DVR_SetDVRMessage(UINT nMessage,HWND hWnd);
NET_DVR_API BOOL __stdcall NET_DVR_SetExceptionCallBack_V30(UINT nMessage, HWND hWnd, void (CALLBACK* fExceptionCallBack)(unsigned int dwType, int lUserID, int lHandle, void *pUser), void *pUser);
#elif defined(__linux__)
NET_DVR_API BOOL __stdcall NET_DVR_SetExceptionCallBack_V30(UINT reserved1, void* reserved2, void (CALLBACK* fExceptionCallBack)(unsigned int dwType, int lUserID, int lHandle, void *pUser), void *pUser);

/*2005.01.11 增加两个接口,Linux专有 */
NET_DVR_API BOOL NET_DVR_DrawAreaInit( INITINFO InitInfo );
NET_DVR_API BOOL NET_DVR_DrawAreaRelease();
#endif


NET_DVR_API BOOL __stdcall NET_DVR_SetDVRMessCallBack(BOOL (CALLBACK *fMessCallBack)(int lCommand,char *sDVRIP,char *pBuf,unsigned int dwBufLen));
NET_DVR_API BOOL __stdcall NET_DVR_SetDVRMessCallBack_EX(BOOL (CALLBACK *fMessCallBack_EX)(int lCommand,int lUserID,char *pBuf,unsigned int dwBufLen));
NET_DVR_API BOOL __stdcall NET_DVR_SetDVRMessCallBack_NEW(BOOL (CALLBACK *fMessCallBack_NEW)(int lCommand,char *sDVRIP,char *pBuf,unsigned int dwBufLen, unsigned short dwLinkDVRPort));
NET_DVR_API BOOL __stdcall NET_DVR_SetDVRMessageCallBack(BOOL (CALLBACK *fMessageCallBack)(int lCommand,char *sDVRIP,char *pBuf,unsigned int dwBufLen, unsigned int dwUser), unsigned int dwUser);
typedef void (CALLBACK *MSGCallBack)(int lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, unsigned int dwBufLen, void* pUser);
NET_DVR_API BOOL __stdcall NET_DVR_SetDVRMessageCallBack_V30(MSGCallBack fMessageCallBack, void* pUser);

NET_DVR_API BOOL __stdcall NET_DVR_SetConnectTime(unsigned int dwWaitTime /*= 5000*/, unsigned int dwTryTimes /*= 3*/);
NET_DVR_API BOOL __stdcall NET_DVR_SetReconnect(unsigned int dwInterval /*= 30000*/, BOOL bEnableRecon /*= TRUE*/);
NET_DVR_API unsigned int __stdcall NET_DVR_GetSDKVersion();
NET_DVR_API unsigned int __stdcall NET_DVR_GetSDKBuildVersion();
NET_DVR_API int __stdcall NET_DVR_IsSupport();
NET_DVR_API BOOL __stdcall NET_DVR_StartListen(char *sLocalIP,unsigned short wLocalPort);
NET_DVR_API BOOL __stdcall NET_DVR_StopListen();

NET_DVR_API int __stdcall NET_DVR_StartListen_V30(char *sLocalIP, unsigned short wLocalPort, MSGCallBack DataCallback, void* pUserData /*= NULL*/);
NET_DVR_API BOOL __stdcall NET_DVR_StopListen_V30(int lListenHandle);
NET_DVR_API int __stdcall NET_DVR_Login(char *sDVRIP,unsigned short wDVRPort,char *sUserName,char *sPassword,LPNET_DVR_DEVICEINFO lpDeviceInfo);
NET_DVR_API int __stdcall NET_DVR_Login_V30(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo);
NET_DVR_API BOOL __stdcall NET_DVR_Logout(int lUserID);
NET_DVR_API BOOL __stdcall NET_DVR_Logout_V30(int lUserID);
NET_DVR_API unsigned int __stdcall NET_DVR_GetLastError();
NET_DVR_API char* __stdcall NET_DVR_GetErrorMsg(int *pErrorNo /*= NULL*/);
NET_DVR_API BOOL __stdcall NET_DVR_SetShowMode(unsigned int dwShowType,COLORREF colorKey);
NET_DVR_API BOOL __stdcall NET_DVR_GetDVRIPByResolveSvr(char *sServerIP, unsigned short wServerPort, unsigned char *sDVRName,unsigned short wDVRNameLen,unsigned char *sDVRSerialNumber,unsigned short wDVRSerialLen,char* sGetIP);
NET_DVR_API BOOL  __stdcall NET_DVR_GetDVRIPByResolveSvr_EX(char *sServerIP, unsigned short wServerPort, unsigned char *sDVRName, unsigned short wDVRNameLen, unsigned char *sDVRSerialNumber, unsigned short wDVRSerialLen, char* sGetIP, unsigned int *dwPort);

//Preview
NET_DVR_API int __stdcall NET_DVR_RealPlay(int lUserID,LPNET_DVR_CLIENTINFO lpClientInfo);
NET_DVR_API int __stdcall NET_DVR_RealPlay_V30(int lUserID, LPNET_DVR_CLIENTINFO lpClientInfo, void(CALLBACK *fRealDataCallBack_V30) (int lRealHandle, unsigned int dwDataType, unsigned char *pBuffer, unsigned int dwBufSize, void* pUser) /*= NULL*/, void* pUser /*= NULL*/, BOOL bBlocked /*= FALSE*/);
NET_DVR_API BOOL __stdcall NET_DVR_StopRealPlay(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_RigisterDrawFun(int lRealHandle,void (CALLBACK* fDrawFun)(int lRealHandle,HDC hDc,unsigned int dwUser),unsigned int dwUser);
NET_DVR_API BOOL __stdcall NET_DVR_SetPlayerBufNumber(int lRealHandle,unsigned int dwBufNum);
NET_DVR_API BOOL __stdcall NET_DVR_ThrowBFrame(int lRealHandle,unsigned int dwNum);
NET_DVR_API BOOL __stdcall NET_DVR_SetAudioMode(unsigned int dwMode);
NET_DVR_API BOOL __stdcall NET_DVR_OpenSound(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_CloseSound();
NET_DVR_API BOOL __stdcall NET_DVR_OpenSoundShare(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_CloseSoundShare(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_Volume(int lRealHandle,unsigned short wVolume);
NET_DVR_API BOOL __stdcall NET_DVR_SaveRealData(int lRealHandle,char *sFileName);
NET_DVR_API BOOL __stdcall NET_DVR_StopSaveRealData(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_SetRealDataCallBack(int lRealHandle,void(CALLBACK *fRealDataCallBack) (int lRealHandle, unsigned int dwDataType, unsigned char *pBuffer,unsigned int dwBufSize,unsigned int dwUser),unsigned int dwUser);
NET_DVR_API BOOL __stdcall NET_DVR_SetStandardDataCallBack(int lRealHandle,void(CALLBACK *fStdDataCallBack) (int lRealHandle, unsigned int dwDataType, unsigned char *pBuffer,unsigned int dwBufSize,unsigned int dwUser),unsigned int dwUser);
NET_DVR_API BOOL __stdcall NET_DVR_CapturePicture(int lRealHandle,char *sPicFileName);//bmp

//Create I Frame Manually
NET_DVR_API BOOL __stdcall NET_DVR_MakeKeyFrame(int lUserID, int lChannel);//Main Stream
NET_DVR_API BOOL __stdcall NET_DVR_MakeKeyFrameSub(int lUserID, int lChannel);//Sub Stream

//PTZ
NET_DVR_API BOOL __stdcall NET_DVR_PTZControl(int lRealHandle,unsigned int dwPTZCommand,unsigned int dwStop);
NET_DVR_API BOOL __stdcall NET_DVR_PTZControl_Other(int lUserID,int lChannel,unsigned int dwPTZCommand,unsigned int dwStop);
NET_DVR_API BOOL __stdcall NET_DVR_TransPTZ(int lRealHandle,char *pPTZCodeBuf,unsigned int dwBufSize);
NET_DVR_API BOOL __stdcall NET_DVR_TransPTZ_Other(int lUserID,int lChannel,char *pPTZCodeBuf,unsigned int dwBufSize);
NET_DVR_API BOOL __stdcall NET_DVR_PTZPreset(int lRealHandle,unsigned int dwPTZPresetCmd,unsigned int dwPresetIndex);
NET_DVR_API BOOL __stdcall NET_DVR_PTZPreset_Other(int lUserID,int lChannel,unsigned int dwPTZPresetCmd,unsigned int dwPresetIndex);
NET_DVR_API BOOL __stdcall NET_DVR_TransPTZ_EX(int lRealHandle,char *pPTZCodeBuf,unsigned int dwBufSize);
NET_DVR_API BOOL __stdcall NET_DVR_PTZControl_EX(int lRealHandle,unsigned int dwPTZCommand,unsigned int dwStop);
NET_DVR_API BOOL __stdcall NET_DVR_PTZPreset_EX(int lRealHandle,unsigned int dwPTZPresetCmd,unsigned int dwPresetIndex);
NET_DVR_API BOOL __stdcall NET_DVR_PTZCruise(int lRealHandle,unsigned int dwPTZCruiseCmd,unsigned char byCruiseRoute, unsigned char byCruisePoint, unsigned short wInput);
NET_DVR_API BOOL __stdcall NET_DVR_PTZCruise_Other(int lUserID,int lChannel,unsigned int dwPTZCruiseCmd,unsigned char byCruiseRoute, unsigned char byCruisePoint, unsigned short wInput);
NET_DVR_API BOOL __stdcall NET_DVR_PTZCruise_EX(int lRealHandle,unsigned int dwPTZCruiseCmd,unsigned char byCruiseRoute, unsigned char byCruisePoint, unsigned short wInput);
NET_DVR_API BOOL __stdcall NET_DVR_PTZTrack(int lRealHandle, unsigned int dwPTZTrackCmd);
NET_DVR_API BOOL __stdcall NET_DVR_PTZTrack_Other(int lUserID, int lChannel, unsigned int dwPTZTrackCmd);
NET_DVR_API BOOL __stdcall NET_DVR_PTZTrack_EX(int lRealHandle, unsigned int dwPTZTrackCmd);
NET_DVR_API BOOL __stdcall NET_DVR_PTZControlWithSpeed(int lRealHandle, unsigned int dwPTZCommand, unsigned int dwStop, unsigned int dwSpeed);
NET_DVR_API BOOL __stdcall NET_DVR_PTZControlWithSpeed_Other(int lUserID, int lChannel, unsigned int dwPTZCommand, unsigned int dwStop, unsigned int dwSpeed);
NET_DVR_API BOOL __stdcall NET_DVR_PTZControlWithSpeed_EX(int lRealHandle, unsigned int dwPTZCommand, unsigned int dwStop, unsigned int dwSpeed);
NET_DVR_API BOOL __stdcall NET_DVR_GetPTZCruise(int lUserID,int lChannel,int lCruiseRoute, LPNET_DVR_CRUISE_RET lpCruiseRet);
NET_DVR_API BOOL __stdcall NET_DVR_PTZMltTrack(int lRealHandle,unsigned int dwPTZTrackCmd, unsigned int dwTrackIndex);
NET_DVR_API BOOL __stdcall NET_DVR_PTZMltTrack_Other(int lUserID,int lChannel,unsigned int dwPTZTrackCmd, unsigned int dwTrackIndex);
NET_DVR_API BOOL __stdcall NET_DVR_PTZMltTrack_EX(int lRealHandle,unsigned int dwPTZTrackCmd, unsigned int dwTrackIndex);

//Record Query & Playback
NET_DVR_API int __stdcall NET_DVR_FindFile(int lUserID,int lChannel,unsigned int dwFileType, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);
NET_DVR_API int __stdcall NET_DVR_FindNextFile(int lFindHandle,LPNET_DVR_FIND_DATA lpFindData);
NET_DVR_API BOOL __stdcall NET_DVR_FindClose(int lFindHandle);
NET_DVR_API int __stdcall NET_DVR_FindNextFile_V30(int lFindHandle, LPNET_DVR_FINDDATA_V30 lpFindData);
NET_DVR_API int __stdcall NET_DVR_FindFile_V30(int lUserID, LPNET_DVR_FILECOND pFindCond);
NET_DVR_API BOOL __stdcall NET_DVR_FindClose_V30(int lFindHandle);
//2007-04-16 added to query files with Card No.
NET_DVR_API int __stdcall NET_DVR_FindNextFile_Card(int lFindHandle, LPNET_DVR_FINDDATA_CARD lpFindData);
NET_DVR_API int __stdcall NET_DVR_FindFile_Card(int lUserID, int lChannel, unsigned int dwFileType, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);
NET_DVR_API BOOL __stdcall NET_DVR_LockFileByName(int lUserID, char *sLockFileName);
NET_DVR_API BOOL __stdcall NET_DVR_UnlockFileByName(int lUserID, char *sUnlockFileName);
NET_DVR_API int __stdcall NET_DVR_PlayBackByName(int lUserID,char *sPlayBackFileName, HWND hWnd);
NET_DVR_API int __stdcall NET_DVR_PlayBackByTime(int lUserID,int lChannel, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime, HWND hWnd);
NET_DVR_API BOOL __stdcall NET_DVR_PlayBackControl(int lPlayHandle,unsigned int dwControlCode,unsigned int dwInValue,unsigned int *LPOutValue);
NET_DVR_API BOOL __stdcall NET_DVR_StopPlayBack(int lPlayHandle);
NET_DVR_API BOOL __stdcall NET_DVR_SetPlayDataCallBack(int lPlayHandle,void(CALLBACK *fPlayDataCallBack) (int lPlayHandle, unsigned int dwDataType, unsigned char *pBuffer,unsigned int dwBufSize,unsigned int dwUser),unsigned int dwUser);
NET_DVR_API BOOL __stdcall NET_DVR_PlayBackSaveData(int lPlayHandle,char *sFileName);
NET_DVR_API BOOL __stdcall NET_DVR_StopPlayBackSave(int lPlayHandle);
NET_DVR_API BOOL __stdcall NET_DVR_GetPlayBackOsdTime(int lPlayHandle, LPNET_DVR_TIME lpOsdTime);
NET_DVR_API BOOL __stdcall NET_DVR_PlayBackCaptureFile(int lPlayHandle,char *sFileName);
NET_DVR_API int __stdcall NET_DVR_GetFileByName(int lUserID,char *sDVRFileName,char *sSavedFileName);
NET_DVR_API int __stdcall NET_DVR_GetFileByTime(int lUserID,int lChannel, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime, char *sSavedFileName);
NET_DVR_API BOOL __stdcall NET_DVR_StopGetFile(int lFileHandle);
NET_DVR_API int __stdcall NET_DVR_GetDownloadPos(int lFileHandle);
NET_DVR_API int	__stdcall NET_DVR_GetPlayBackPos(int lPlayHandle);

//Upgrade
NET_DVR_API int __stdcall NET_DVR_Upgrade(int lUserID, char *sFileName);
NET_DVR_API int __stdcall NET_DVR_GetUpgradeState(int lUpgradeHandle);
NET_DVR_API int __stdcall NET_DVR_GetUpgradeProgress(int lUpgradeHandle);
NET_DVR_API BOOL __stdcall NET_DVR_CloseUpgradeHandle(int lUpgradeHandle);
NET_DVR_API BOOL __stdcall NET_DVR_SetNetworkEnvironment(unsigned int dwEnvironmentLevel);
//Format HD Remotely
NET_DVR_API int __stdcall NET_DVR_FormatDisk(int lUserID,int lDiskNumber);
NET_DVR_API BOOL __stdcall NET_DVR_GetFormatProgress(int lFormatHandle, int *pCurrentFormatDisk,int *pCurrentDiskPos,int *pFormatStatic);
NET_DVR_API BOOL __stdcall NET_DVR_CloseFormatHandle(int lFormatHandle);
//Alarm
NET_DVR_API int __stdcall NET_DVR_SetupAlarmChan(int lUserID);
NET_DVR_API BOOL __stdcall NET_DVR_CloseAlarmChan(int lAlarmHandle);
NET_DVR_API int __stdcall NET_DVR_SetupAlarmChan_V30(int lUserID);
NET_DVR_API BOOL __stdcall NET_DVR_CloseAlarmChan_V30(int lAlarmHandle);
//Voice Talk
NET_DVR_API int __stdcall NET_DVR_StartVoiceCom(int lUserID, void(CALLBACK *fVoiceDataCallBack)(int lVoiceComHandle, char *pRecvDataBuffer, unsigned int dwBufSize, unsigned char byAudioFlag, unsigned int dwUser), unsigned int dwUser);
NET_DVR_API int __stdcall NET_DVR_StartVoiceCom_V30(int lUserID, unsigned int dwVoiceChan, BOOL bNeedCBNoEncData, void(CALLBACK *fVoiceDataCallBack)(int lVoiceComHandle, char *pRecvDataBuffer, unsigned int dwBufSize, unsigned char byAudioFlag, void* pUser), void* pUser);
NET_DVR_API BOOL __stdcall NET_DVR_SetVoiceComClientVolume(int lVoiceComHandle, unsigned short wVolume);
NET_DVR_API BOOL __stdcall NET_DVR_StopVoiceCom(int lVoiceComHandle);
//Forward Voice
NET_DVR_API int __stdcall NET_DVR_StartVoiceCom_MR(int lUserID, void(CALLBACK *fVoiceDataCallBack)(int lVoiceComHandle, char *pRecvDataBuffer, unsigned int dwBufSize, unsigned char byAudioFlag, unsigned int dwUser), unsigned int dwUser);
NET_DVR_API int __stdcall NET_DVR_StartVoiceCom_MR_V30(int lUserID, unsigned int dwVoiceChan, void(CALLBACK *fVoiceDataCallBack)(int lVoiceComHandle, char *pRecvDataBuffer, unsigned int dwBufSize, unsigned char byAudioFlag, void* pUser), void* pUser);
NET_DVR_API BOOL __stdcall NET_DVR_VoiceComSendData(int lVoiceComHandle, char *pSendBuf, unsigned int dwBufSize);

//Voice Broadcast
NET_DVR_API BOOL __stdcall NET_DVR_ClientAudioStart();
NET_DVR_API BOOL __stdcall NET_DVR_ClientAudioStart_V30(void(CALLBACK *fVoiceDataCallBack)(char *pRecvDataBuffer, unsigned int dwBufSize, void * pUser), void *pUser);
NET_DVR_API BOOL __stdcall NET_DVR_ClientAudioStop();
NET_DVR_API BOOL __stdcall NET_DVR_AddDVR(int lUserID);
NET_DVR_API int __stdcall NET_DVR_AddDVR_V30(int lUserID, unsigned int dwVoiceChan);
NET_DVR_API BOOL __stdcall NET_DVR_DelDVR(int lUserID);
NET_DVR_API BOOL __stdcall NET_DVR_DelDVR_V30(int lVoiceHandle);
////////////////////////////////////////////////////////////
//Transparent Channel
NET_DVR_API int __stdcall NET_DVR_SerialStart(int lUserID,int lSerialPort,void(CALLBACK *fSerialDataCallBack)(int lSerialHandle,char *pRecvDataBuffer,unsigned int dwBufSize,unsigned int dwUser),unsigned int dwUser);
//If RS485 is used as transparent channel, please specify the channel No. And different channels can have different RS485 parameters
NET_DVR_API BOOL __stdcall NET_DVR_SerialSend(int lSerialHandle, int lChannel, char *pSendBuf,unsigned int dwBufSize);
NET_DVR_API BOOL __stdcall NET_DVR_SerialStop(int lSerialHandle);
NET_DVR_API BOOL __stdcall NET_DVR_SendTo232Port(int lUserID, char *pSendBuf, unsigned int dwBufSize);
NET_DVR_API BOOL __stdcall NET_DVR_SendToSerialPort(int lUserID, unsigned int dwSerialPort, unsigned int dwSerialIndex, char *pSendBuf, unsigned int dwBufSize);

//decoding nBitrate = 16000
NET_DVR_API void* __stdcall NET_DVR_InitG722Decoder(int nBitrate /*= 16000*/);
NET_DVR_API void __stdcall NET_DVR_ReleaseG722Decoder(void *pDecHandle);
NET_DVR_API BOOL __stdcall NET_DVR_DecodeG722Frame(void *pDecHandle, unsigned char* pInBuffer, unsigned char* pOutBuffer);
//encoding
NET_DVR_API void* __stdcall NET_DVR_InitG722Encoder();
NET_DVR_API BOOL __stdcall NET_DVR_EncodeG722Frame(void *pEncodeHandle,unsigned char* pInBuffer, unsigned char* pOutBuffer);
NET_DVR_API void __stdcall NET_DVR_ReleaseG722Encoder(void *pEncodeHandle);

//Control the local preview remotely
NET_DVR_API BOOL __stdcall NET_DVR_ClickKey(int lUserID, int lKeyIndex);
//Control the manual record remotely
NET_DVR_API BOOL __stdcall NET_DVR_StartDVRRecord(int lUserID,int lChannel,int lRecordType);
NET_DVR_API BOOL __stdcall NET_DVR_StopDVRRecord(int lUserID,int lChannel);
//Decoding Card
NET_DVR_API BOOL __stdcall NET_DVR_InitDevice_Card(int *pDeviceTotalChan);
NET_DVR_API BOOL __stdcall NET_DVR_ReleaseDevice_Card();
NET_DVR_API BOOL __stdcall NET_DVR_InitDDraw_Card(HWND hParent,COLORREF colorKey);
NET_DVR_API BOOL __stdcall NET_DVR_ReleaseDDraw_Card();
NET_DVR_API int __stdcall NET_DVR_RealPlay_Card(int lUserID,LPNET_DVR_CARDINFO lpCardInfo,int lChannelNum);
NET_DVR_API BOOL __stdcall NET_DVR_ResetPara_Card(int lRealHandle,LPNET_DVR_DISPLAY_PARA lpDisplayPara);
NET_DVR_API BOOL __stdcall NET_DVR_RefreshSurface_Card();
NET_DVR_API BOOL __stdcall NET_DVR_ClearSurface_Card();
NET_DVR_API BOOL __stdcall NET_DVR_RestoreSurface_Card();
NET_DVR_API BOOL __stdcall NET_DVR_OpenSound_Card(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_CloseSound_Card(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_SetVolume_Card(int lRealHandle,unsigned short wVolume);
NET_DVR_API BOOL __stdcall NET_DVR_AudioPreview_Card(int lRealHandle,BOOL bEnable);
NET_DVR_API int __stdcall NET_DVR_GetCardLastError_Card();
NET_DVR_API HANDLE __stdcall NET_DVR_GetChanHandle_Card(int lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_CapturePicture_Card(int lRealHandle, char *sPicFileName);
//NET_DVR_GetSerialNum_Card is invalid, Call GetBoardDetail instead.
NET_DVR_API BOOL __stdcall NET_DVR_GetSerialNum_Card(int lChannelNum,unsigned int *pDeviceSerialNo);
//Log
NET_DVR_API int __stdcall NET_DVR_FindDVRLog(int lUserID, int lSelectMode, unsigned int dwMajorType,unsigned int dwMinorType, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);
NET_DVR_API int __stdcall NET_DVR_FindNextLog(int lLogHandle, LPNET_DVR_LOG lpLogData);
NET_DVR_API BOOL __stdcall NET_DVR_FindLogClose(int lLogHandle);
NET_DVR_API int __stdcall NET_DVR_FindDVRLog_V30(int lUserID, int lSelectMode, unsigned int dwMajorType,unsigned int dwMinorType, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime, BOOL bOnlySmart /*= FALSE*/);
NET_DVR_API int __stdcall NET_DVR_FindNextLog_V30(int lLogHandle, LPNET_DVR_LOG_V30 lpLogData);
NET_DVR_API BOOL __stdcall NET_DVR_FindLogClose_V30(int lLogHandle);

//ATM DVR
NET_DVR_API int __stdcall NET_DVR_FindFileByCard(int lUserID,int lChannel,unsigned int dwFileType, int nFindType, unsigned char *sCardNumber, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);


//Encoding
NET_DVR_API void* __stdcall NET_DVR_InitG722Encoder();
NET_DVR_API BOOL __stdcall NET_DVR_EncodeG722Frame(void *pEncodeHandle,unsigned char* pInBuffer, unsigned char* pOutBuffer);
NET_DVR_API void __stdcall NET_DVR_ReleaseG722Encoder(void *pEncodeHandle);
//2005-09-15
NET_DVR_API BOOL __stdcall NET_DVR_CaptureJPEGPicture(int lUserID, int lChannel, LPNET_DVR_JPEGPARA lpJpegPara, char *sPicFileName);
//Grab JPEG and save to RAM
NET_DVR_API BOOL __stdcall NET_DVR_CaptureJPEGPicture_NEW(int lUserID, int lChannel, LPNET_DVR_JPEGPARA lpJpegPara, char *sJpegPicBuffer, unsigned int dwPicSize,  unsigned int* lpSizeReturned);


//2006-02-16
NET_DVR_API int __stdcall NET_DVR_GetRealPlayerIndex(int lRealHandle);
NET_DVR_API int __stdcall NET_DVR_GetPlayBackPlayerIndex(int lPlayHandle);

//2006-08-28 704-640 Scale
NET_DVR_API BOOL __stdcall NET_DVR_SetScaleCFG(int lUserID, unsigned int dwScale);
NET_DVR_API BOOL __stdcall NET_DVR_GetScaleCFG(int lUserID, unsigned int *lpOutScale);
NET_DVR_API BOOL __stdcall NET_DVR_SetScaleCFG_V30(int lUserID, LPNET_DVR_SCALECFG pScalecfg);
NET_DVR_API BOOL __stdcall NET_DVR_GetScaleCFG_V30(int lUserID, LPNET_DVR_SCALECFG pScalecfg);
//2006-08-28 Port of ATM 
NET_DVR_API BOOL __stdcall NET_DVR_SetATMPortCFG(int lUserID, unsigned short wATMPort);
NET_DVR_API BOOL __stdcall NET_DVR_GetATMPortCFG(int lUserID, unsigned short *LPOutATMPort);

//2006-11-10 Display on Multi displayer
NET_DVR_API BOOL __stdcall NET_DVR_InitDDrawDevice();
NET_DVR_API BOOL __stdcall NET_DVR_ReleaseDDrawDevice();
NET_DVR_API int __stdcall NET_DVR_GetDDrawDeviceTotalNums();
NET_DVR_API BOOL __stdcall NET_DVR_SetDDrawDevice(int lPlayPort, unsigned int nDeviceNum);

NET_DVR_API BOOL __stdcall NET_DVR_PTZSelZoomIn(int lRealHandle, LPNET_DVR_POINT_FRAME pStruPointFrame);
NET_DVR_API BOOL __stdcall NET_DVR_PTZSelZoomIn_EX(int lUserID, int lChannel, LPNET_DVR_POINT_FRAME pStruPointFrame);



//Decoder DS-6001D/DS-6001F
NET_DVR_API BOOL __stdcall NET_DVR_StartDecode(int lUserID, int lChannel, LPNET_DVR_DECODERINFO lpDecoderinfo);
NET_DVR_API BOOL __stdcall NET_DVR_StopDecode(int lUserID, int lChannel);
NET_DVR_API BOOL __stdcall NET_DVR_GetDecoderState(int lUserID, int lChannel, LPNET_DVR_DECODERSTATE lpDecoderState);
//2005-08-01
NET_DVR_API BOOL __stdcall NET_DVR_SetDecInfo(int lUserID, int lChannel, LPNET_DVR_DECCFG lpDecoderinfo);
NET_DVR_API BOOL __stdcall NET_DVR_GetDecInfo(int lUserID, int lChannel, LPNET_DVR_DECCFG lpDecoderinfo);
NET_DVR_API BOOL __stdcall NET_DVR_SetDecTransPort(int lUserID, LPNET_DVR_PORTCFG lpTransPort);
NET_DVR_API BOOL __stdcall NET_DVR_GetDecTransPort(int lUserID, LPNET_DVR_PORTCFG lpTransPort);
NET_DVR_API BOOL __stdcall NET_DVR_DecPlayBackCtrl(int lUserID, int lChannel, unsigned int dwControlCode, unsigned int dwInValue,unsigned int *LPOutValue, LPNET_DVR_PLAYREMOTEFILE lpRemoteFileInfo);
NET_DVR_API BOOL __stdcall NET_DVR_StartDecSpecialCon(int lUserID, int lChannel, LPNET_DVR_DECCHANINFO lpDecChanInfo);
NET_DVR_API BOOL __stdcall NET_DVR_StopDecSpecialCon(int lUserID, int lChannel, LPNET_DVR_DECCHANINFO lpDecChanInfo);
NET_DVR_API BOOL __stdcall NET_DVR_DecCtrlDec(int lUserID, int lChannel, unsigned int dwControlCode);
NET_DVR_API BOOL __stdcall NET_DVR_DecCtrlScreen(int lUserID, int lChannel, unsigned int dwControl);
NET_DVR_API BOOL __stdcall NET_DVR_GetDecCurLinkStatus(int lUserID, int lChannel, LPNET_DVR_DECSTATUS lpDecStatus);

//Multi-channel decoder
//2007-11-30 V211 support the API below //11
NET_DVR_API BOOL __stdcall NET_DVR_MatrixStartDynamic(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_DYNAMIC_DEC lpDynamicInfo);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixStopDynamic(int lUserID, unsigned int dwDecChanNum);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetDecChanInfo(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_DEC_CHAN_INFO lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetLoopDecChanInfo(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_LOOP_DECINFO lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetLoopDecChanInfo(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_LOOP_DECINFO lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetLoopDecChanEnable(int lUserID, unsigned int dwDecChanNum, unsigned int dwEnable);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetLoopDecChanEnable(int lUserID, unsigned int dwDecChanNum, unsigned int* lpdwEnable);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetLoopDecEnable(int lUserID, unsigned int* lpdwEnable);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetDecChanEnable(int lUserID, unsigned int dwDecChanNum, unsigned int dwEnable);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetDecChanEnable(int lUserID, unsigned int dwDecChanNum, unsigned int* lpdwEnable);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetDecChanStatus(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_DEC_CHAN_STATUS lpInter);
//2007-12-22  //18
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetTranInfo(int lUserID, LPNET_DVR_MATRIX_TRAN_CHAN_CONFIG lpTranInfo);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetTranInfo(int lUserID, LPNET_DVR_MATRIX_TRAN_CHAN_CONFIG lpTranInfo);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetRemotePlay(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_DEC_REMOTE_PLAY lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetRemotePlayControl(int lUserID, unsigned int dwDecChanNum, unsigned int dwControlCode, unsigned int dwInValue, unsigned int *LPOutValue);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetRemotePlayStatus(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_DEC_REMOTE_PLAY_STATUS lpOuter);
//end
NET_DVR_API BOOL __stdcall NET_DVR_RefreshPlay(int lPlayHandle);
//Restore default configuration
NET_DVR_API BOOL __stdcall NET_DVR_RestoreConfig(int lUserID);
//Save configuration
NET_DVR_API BOOL __stdcall NET_DVR_SaveConfig(int lUserID);
//Reboot
NET_DVR_API BOOL __stdcall NET_DVR_RebootDVR(int lUserID);
//Shutdown DVR
NET_DVR_API BOOL __stdcall NET_DVR_ShutDownDVR(int lUserID);



//config parameter begin
NET_DVR_API BOOL __stdcall NET_DVR_GetDVRConfig(int lUserID, unsigned int dwCommand,int lChannel, LPVOID lpOutBuffer, unsigned int dwOutBufferSize, unsigned int* lpBytesReturned);
NET_DVR_API BOOL __stdcall NET_DVR_SetDVRConfig(int lUserID, unsigned int dwCommand,int lChannel, LPVOID lpInBuffer, unsigned int dwInBufferSize);
NET_DVR_API BOOL __stdcall NET_DVR_GetDVRWorkState_V30(int lUserID, LPNET_DVR_WORKSTATE_V30 lpWorkState);
NET_DVR_API BOOL __stdcall NET_DVR_GetDVRWorkState(int lUserID, LPNET_DVR_WORKSTATE lpWorkState);
NET_DVR_API BOOL __stdcall NET_DVR_SetVideoEffect(int lUserID, int lChannel, unsigned int dwBrightValue, unsigned int dwContrastValue, unsigned int dwSaturationValue, unsigned int dwHueValue);
NET_DVR_API BOOL __stdcall NET_DVR_GetVideoEffect(int lUserID, int lChannel, unsigned int *pBrightValue, unsigned int *pContrastValue, unsigned int *pSaturationValue, unsigned int *pHueValue);
NET_DVR_API BOOL __stdcall NET_DVR_ClientGetframeformat(int lUserID, LPNET_DVR_FRAMEFORMAT lpFrameFormat);
NET_DVR_API BOOL __stdcall NET_DVR_ClientSetframeformat(int lUserID, LPNET_DVR_FRAMEFORMAT lpFrameFormat);
NET_DVR_API BOOL __stdcall NET_DVR_GetAtmFrameFormat_V30(int lUserID, int lAtmChannel, LPNET_DVR_ATM_FRAMEFORMAT_V30 lpFrameFormat);
NET_DVR_API BOOL __stdcall NET_DVR_SetAtmFrameFormat_V30(int lUserID, int lAtmChannel, LPNET_DVR_ATM_FRAMEFORMAT_V30 lpFrameFormat);
NET_DVR_API BOOL __stdcall NET_DVR_GetAtmProtocol(int lUserID, LPNET_DVR_ATM_PROTOCOL lpAtmProtocol);
NET_DVR_API BOOL __stdcall NET_DVR_GetAlarmOut_V30(int lUserID, LPNET_DVR_ALARMOUTSTATUS_V30 lpAlarmOutState);
NET_DVR_API BOOL __stdcall NET_DVR_GetAlarmOut(int lUserID, LPNET_DVR_ALARMOUTSTATUS lpAlarmOutState);
NET_DVR_API BOOL __stdcall NET_DVR_SetAlarmOut(int lUserID, int lAlarmOutPort,int lAlarmOutStatic);

//Adjust video paramters
NET_DVR_API BOOL __stdcall NET_DVR_ClientSetVideoEffect(int lRealHandle,unsigned int dwBrightValue,unsigned int dwContrastValue, unsigned int dwSaturationValue,unsigned int dwHueValue);
NET_DVR_API BOOL __stdcall NET_DVR_ClientGetVideoEffect(int lRealHandle,unsigned int *pBrightValue,unsigned int *pContrastValue, unsigned int *pSaturationValue,unsigned int *pHueValue);

//Configuration File
NET_DVR_API BOOL __stdcall NET_DVR_GetConfigFile(int lUserID, char *sFileName);
NET_DVR_API BOOL __stdcall NET_DVR_SetConfigFile(int lUserID, char *sFileName);
NET_DVR_API BOOL __stdcall NET_DVR_GetConfigFile_V30(int lUserID, char *sOutBuffer, unsigned int dwOutSize, unsigned int *pReturnSize);

NET_DVR_API BOOL __stdcall NET_DVR_GetConfigFile_EX(int lUserID, char *sOutBuffer, unsigned int dwOutSize);
NET_DVR_API BOOL __stdcall NET_DVR_SetConfigFile_EX(int lUserID, char *sInBuffer, unsigned int dwInSize);

//write log file
NET_DVR_API BOOL __stdcall NET_DVR_SetLogToFile(BOOL bLogEnable /*= FALSE*/, char * strLogDir /*= NULL*/, BOOL bAutoDel /*= TRUE*/);
NET_DVR_API BOOL __stdcall NET_DVR_GetSDKState(LPNET_DVR_SDKSTATE pSDKState);
NET_DVR_API BOOL __stdcall NET_DVR_GetSDKAbility(LPNET_DVR_SDKABL pSDKAbl);
NET_DVR_API BOOL __stdcall NET_DVR_GetPTZProtocol(int lUserID, NET_DVR_PTZCFG *pPtzcfg);
//Lock Front Panel
NET_DVR_API BOOL __stdcall NET_DVR_LockPanel(int lUserID);
NET_DVR_API BOOL __stdcall NET_DVR_UnLockPanel(int lUserID);

NET_DVR_API BOOL __stdcall NET_DVR_SetRtspConfig(int lUserID, unsigned int dwCommand, LPNET_DVR_RTSPCFG lpInBuffer, unsigned int dwInBufferSize);
NET_DVR_API BOOL __stdcall NET_DVR_GetRtspConfig(int lUserID, unsigned int dwCommand, LPNET_DVR_RTSPCFG lpOutBuffer, unsigned int dwOutBufferSize);

//SDK_V222
//智能设备类型
#define  IDS6002_HF_B     62//tracked by two camera: iDS6002-HF/B
#define  IDS6101_HF_B	 63//Behavior Analysis: iDS6101-HF/B
#define  IDS52XX		 64//Intelligent Analysis: IVMS
//IVMS 设备  
// SDK_V35
#define  IVMS_6400      110 // IVMS-6400 
#define IDS8104_AHL_S_HX  66// 海鑫人脸识别 ATM
// SDK_V35

//Get Ability Set
#define VCA_DEV_ABILITY 	 0x100 //Intelligent Analysis Ability
#define VCA_CHAN_ABILITY     0x110 //Behavior Analysis Ability
#define MATRIXDECODER_ABILITY 0x200 //Decoding and Display Ability of Multichannel Decoder

//Get/Set API Parameters Commands
//Vehicle license plate recognition（NET_VCA_PLATE_CFG）
#define 	NET_DVR_SET_PLATECFG	150		//Set parameter of Vehicle license plate recognition
#define 	NET_DVR_GET_PLATECFG	151		//Get parameter of Vehicle license plate recognition
//Behavior Analysis (NET_VCA_RULECFG)
#define 	NET_DVR_SET_RULECFG		152	//Set rule of Behavior Analysis
#define 	NET_DVR_GET_RULECFG	    153	//Get rule of Behavior Analysis
//Track parameters of Speed dome(NET_DVR_TRACK_CFG)
#define  	NET_DVR_SET_TRACK_CFG  160//Set Speed dome config 
#define  	NET_DVR_GET_TRACK_CFG  161//Get Speed dome config

//Config Commands for Getting Stream
#define 	NET_DVR_SET_IVMS_STREAMCFG		162		//Set IVMS Parameter for getting stream
#define 	NET_DVR_GET_IVMS_STREAMCFG		163		//Get IVMS Parameter

//Intelligent control parameter
#define 	NET_DVR_SET_VCA_CTRLCFG			164	 //Set intelligent control parameter
#define 	NET_DVR_GET_VCA_CTRLCFG			165	 //Get intelligent control parameter

//Mask Area, NET_VCA_MASK_REGION_LIST
#define 	NET_DVR_SET_VCA_MASK_REGION		166	 //Set Mask Area 
#define 	NET_DVR_GET_VCA_MASK_REGION		167	 //Get Mask Area 

//Get/Set Enter ATM Region Commands, NET_VCA_ENTER_REGION
#define 	NET_DVR_SET_VCA_ENTER_REGION	168	 //Set region parameter
#define 	NET_DVR_GET_VCA_ENTER_REGION	169	 //Get region parameter

//config calibration line, NET_VCA_LINE_SEGMENT_LIST
#define 	NET_DVR_SET_VCA_LINE_SEGMENT	170	 //Set calibration line
#define 	NET_DVR_GET_VCA_LINE_SEGMENT	171	 //Get calibration line

// ivms mask region, NET_IVMS_MASK_REGION_LIST
#define 	NET_DVR_SET_IVMS_MASK_REGION	172	 //SetIVMS mask region parameter 
#define 	NET_DVR_GET_IVMS_MASK_REGION	173	 //GetIVMS mask region parameter 
// ivms enter detecting region, NET_IVMS_ENTER_REGION
#define 	NET_DVR_SET_IVMS_ENTER_REGION	174	 //Set IVMS enter region parameter 
#define 	NET_DVR_GET_IVMS_ENTER_REGION	175	 //Get IVMS enter region parameter 

//IVMS Behavior Analysis Config Commands
#define 	NET_DVR_SET_IVMS_BEHAVIORCFG	176	//Set IVMS Behavior Analysis rule 
#define 	NET_DVR_GET_IVMS_BEHAVIORCFG	177	//Get IVMS Behavior Analysis rule 

// IVMS Playback Search
#define NET_DVR_IVMS_SET_SEARCHCFG		178	//SetIVMS Playback Search parameter 
#define NET_DVR_IVMS_GET_SEARCHCFG			179	//GetIVMS Playback Search parameter 

// SDK_V35
#define NET_DVR_SET_POSITION_RULE   180  // 设置场景位置行为分析规则
#define NET_DVR_GET_POSITION_RULE   181  // 获取场景位置行为分析规则

#define NET_DVR_SET_CALIBRATION         182    // 设置标定信息
#define NET_DVR_GET_CALIBRATION         183    // 获取标定信息

#define NET_DVR_SET_PDC_RULECFG         184    // 设置人流量统计规则
#define NET_DVR_GET_PDC_RULECFG         185    // 获取人流量统计规则

#define NET_DVR_SET_PU_STREAMCFG        186     // 设置前段取流设备信息
#define NET_DVR_GET_PU_STREAMCFG        187     // 获取前段取流设备信息

#define NET_DVR_SET_DETECT_RULECFG          190 ////  设置ATM异物监测规则
#define NET_DVR_GET_DETECT_RULECFG          191 ////  获取ATM异物监测规则
//SDK_V35

//Alarm callback 
//NET_VCA_PLATE_RESULT
#define  COMM_ALARM_PLATE				0x1101	//Vehicle license plate recognition alarm info
//NET_VCA_RULE_ALARM
#define  COMM_ALARM_RULE				0x1102	//Behavior Analysis alarm info

//Macro Definition of Struct parameter 
#define VCA_MAX_POLYGON_POINT_NUM		10		//support rectangle with maximum 10 vertexes
#define MAX_RULE_NUM					8		//maximum number of rules
#define MAX_TARGET_NUM    				30		//maximum number of targets 
#define MAX_CALIB_PT 					6		//maximum number of calibration point
#define MIN_CALIB_PT 					4		//minimum number of calibration point
#define MAX_TIMESEGMENT_2	    		2		//maximum time segment
#define MAX_LICENSE_LEN					16		//maximum length of license number
#define MAX_PLATE_NUM					3		//number of license plate
#define MAX_MASK_REGION_NUM				4       //maximum number of mask region
#define MAX_SEGMENT_NUM					6       //maximum number of camera calibration sample line. 
#define MIN_SEGMENT_NUM					3       //minimum number of camera calibration sample line. 


//Intelligent control info
#define MAX_VCA_CHAN  16//maximum number of intelligent channels
typedef struct tagNET_VCA_CTRLINFO
{
	unsigned char   byVCAEnable;		//enable VCA
	unsigned char   byVCAType;	    //VCA_CHAN_ABILITY_TYPE
	unsigned char   byStreamWithVCA; //embedded VCA info in Stream
    unsigned char   byMode;			//VCA_CHAN_MODE_TYPE for ATM
	unsigned char   byRes[4]; 		//Reserved，Set 0
}NET_VCA_CTRLINFO, * LPNET_VCA_CTRLINFO;

//Intelligent control info 
typedef struct tagNET_VCA_CTRLCFG
{
	unsigned int dwSize;
	NET_VCA_CTRLINFO  struCtrlInfo[MAX_VCA_CHAN]; 	//struCtrlInfo[0] for first channel
	unsigned char byRes[16];
}NET_VCA_CTRLCFG, * LPNET_VCA_CTRLCFG;

//Intelligent Device ability
typedef struct tagNET_VCA_DEV_ABILITY
{
	unsigned int dwSize;			//struct size
	unsigned char byVCAChanNum;		//number of intelligent channels
	unsigned char byPlateChanNum; 	//number of license plate channels
	unsigned char byBBaseChanNum;	//number of Behavior basic version
	unsigned char byBAdvanceChanNum; //number of Behavior professional version
	unsigned char byBFullChanNum;    //number of Behavior full version
	unsigned char byATMChanNum;		//number of Intelligent ATM
	unsigned char byRes[34];
}NET_VCA_DEV_ABILITY, *LPNET_VCA_DEV_ABILITY;


//Behavior Analysis ability
typedef enum _VCA_ABILITY_TYPE_
{
    TRAVERSE_PLANE_ABILITY           = 0x01,  //cross alarm surface
    ENTER_AREA_ABILITY          = 0x02,      //enter region
    EXIT_AREA_ABILITY           = 0x04,      //exit region
    INTRUSION_ABILITY           = 0x08,      //intrusion
    LOITER_ABILITY               = 0x10,     //loiter
    LEFT_TAKE_ABILITY            = 0x20,     //left or take package
    PARKING_ABILITY              = 0x40,     //park
    RUN_ABILITY                  = 0x80,    //run
	HIGH_DENSITY_ABILITY         = 0x100,    //density
	LF_TRACK_ABILITY			 = 0x200,    //Speed dome Track
	STICK_UP_ABILITY             = 0x40000000,  //stick paper on ATM
	INSTALL_SCANNER_ABILITY      = 0x80000000   //install scanner on ATM
}VCA_ABILITY_TYPE;


//Intelligent Channel Type
typedef enum _VCA_CHAN_ABILITY_TYPE_
{
	VCA_BEHAVIOR_BASE     =  1,   //Behavior Analysis Basic version
	VCA_BEHAVIOR_ADVANCE  =  2,   //Behavior Analysis Professional version
	VCA_BEHAVIOR_FULL     =  3,   //Behavior Analysis Full version
    VCA_PLATE     		  =  4,   //Vehicle license plate
	VCA_ATM               =  5,    //ATM DVR ability
    VCA_PDC               =  6      // 人流量统计
}VCA_CHAN_ABILITY_TYPE;

//Intelligent ATM DVR
typedef enum _VCA_CHAN_MODE_TYPE_
{
    VCA_ATM_PANEL     =  0, //ATM Panel
    VCA_ATM_SURROUND  =  1,  //ATM Environment
    VCA_ATM_FACE		= 2		//ATM 海鑫人脸识别
}VCA_CHAN_MODE_TYPE;


//input parameter of channel ability
typedef struct tagNET_VCA_CHAN_IN_PARAM
{
	unsigned char byVCAType;	    //VCA_CHAN_ABILITY_TYPE enum value
	unsigned char byMode;		//VCA_CHAN_MODE_TYPE for ATM DVR
	unsigned char byRes[2]; 	    //Reserved，Set to 0
}NET_VCA_CHAN_IN_PARAM, *LPNET_VCA_CHAN_IN_PARAM;


//Behavior Analysis ability set struct
typedef struct tagNET_VCA_BEHAVIOR_ABILITY
{
	unsigned int dwSize;		 //struct size
	unsigned int dwAbilityType; //VCA_ABILITY_TYPE
	unsigned char byMaxRuleNum;	 //Maximum rule number
	unsigned char byMaxTargetNum; //Maximum target number
	unsigned char byRes[10];      //Reserved，Set to 0
}NET_VCA_BEHAVIOR_ABILITY, *LPNET_VCA_BEHAVIOR_ABILITY;

NET_DVR_API BOOL __stdcall NET_DVR_GetDeviceAbility(int lUserID, unsigned int dwAbilityType, char* pInBuf, unsigned int dwInLength, char* pOutBuf, unsigned int dwOutLength);


// Intelligent global struct
//coordinate normalized,float value is the percent of current image size, which is accurate to 0.001
//Point Structure 
typedef struct tagNET_VCA_POINT
{	
	float fX;								// X-coordinate, normalized to [0.001~1]
	float fY;								//Y-coordinate, normalized to [0.001~1]

}NET_VCA_POINT, *LPNET_VCA_POINT;

//Rectangle struct
typedef struct tagNET_VCA_RECT
{
	float fX;               //X axis coordinate for the top left position of the rectangle, normalized to [0.001~1]
	float fY;               //Y axis coordinate for the top left position of the rectangle, normalized to [0.001~1]
	float fWidth;           //Rectangle width, normalized to [0.001~1]
	float fHeight;          // Rectangle width, normalized to [0.001~1]
}NET_VCA_RECT, *LPNET_VCA_RECT;

//Behavior Analysis Event Type
typedef enum _VCA_EVENT_TYPE_
{
	VCA_TRAVERSE_PLANE		= 0x1,    //cross alert surface
	VCA_ENTER_AREA		= 0x2,    //enter alert area, support region rule	
	VCA_EXIT_AREA		= 0x4,    //Target left alert area, support region rule
	VCA_INTRUSION		= 0x8,    //Perimeter Intrusion, support region rule
	VCA_LOITER			= 0x10,   //Loiter,support region rule
	VCA_LEFT_TAKE		= 0x20,   //Left or pick up luggage ,support region rule
	VCA_PARKING			= 0x40,   //parking,support region rule
	VCA_RUN				= 0x80,   //run,support region rule
	VCA_HIGH_DENSITY	= 0x100,  //density of people,support region rule
    VCA_STICK_UP        = 0x40000000,  //stick message,support region rule
    VCA_INSTALL_SCANNER = 0x80000000 //install scanner,support region rule
}VCA_EVENT_TYPE;

//direction of crossing alert surface
typedef enum _VCA_CROSS_DIRECTION_
{
	VCA_BOTH_DIRECTION,  // bidirection
	VCA_LEFT_GO_RIGHT,   // left to right
	VCA_RIGHT_GO_LEFT    // right to left
}VCA_CROSS_DIRECTION;

//line  struct
typedef struct tagNET_VCA_LINE
{
	NET_VCA_POINT struStart;    //start point  
	NET_VCA_POINT struEnd;      //end point 
}NET_VCA_LINE, *LPNET_VCA_LINE;

//polygon struct
typedef struct tagNET_VCA_POLYGON
{
	unsigned int dwPointNum;                                  //valid point>=3. If 3 points is in one line or two lines is crossed, the polygon is invalid
	NET_VCA_POINT  struPos[VCA_MAX_POLYGON_POINT_NUM]; //vertexes, 10 is maximum 
}NET_VCA_POLYGON, *LPNET_VCA_POLYGON;

// alert surface  parameter 
typedef struct tagNET_VCA_TRAVERSE_PLANE
{	
    NET_VCA_LINE struPlaneBottom;  // alert surface bottom
    VCA_CROSS_DIRECTION dwCrossDirection; //direction: 0-bi-direction,1-left to right, 2-right to left
    unsigned char byRes1;					//Reserved
    unsigned char byPlaneHeight;				// alert surface height
    unsigned char byRes2[38];				//Reserved
}NET_VCA_TRAVERSE_PLANE, *LPNET_VCA_TRAVERSE_PLANE;

//enter or exit region parameter 
typedef struct tagNET_VCA_AREA
{
    NET_VCA_POLYGON struRegion;//region
    unsigned char byRes[8];
}NET_VCA_AREA, *LPNET_VCA_AREA;

//According to the alarm duration to attach image, duration is same with I/O alarm, send 1 per second.
//Intrusion parameter 
typedef struct tagNET_VCA_INTRUSION
{
    NET_VCA_POLYGON struRegion;//region
    unsigned short wDuration;    //alarm duration: 1-120 seconds, 5 is recommended, in this duration, all alarms will be treated as one alarm
    unsigned char byRes[6];
}NET_VCA_INTRUSION, *LPNET_VCA_INTRUSION;

//Loiter parameter 
typedef struct tagNET_VCA_PARAM_LOITER
{
    NET_VCA_POLYGON struRegion;//Region
    unsigned short wDuration; //Loiter duration to trigger alarm: 1-120 seconds, 10 is recommended
    unsigned char byRes[6];
}NET_VCA_LOITER, *LPNET_VCA_LOITER;

//drop luggage/pick up luggage parameter 
typedef struct tagNET_VCA_TAKE_LEFT
{
    NET_VCA_POLYGON struRegion;//Region
    unsigned short wDuration; //duration to trigger alarm: 1-120 seconds, 10 is recommended
    unsigned char byRes[6];
}NET_VCA_TAKE_LEFT, *LPNET_VCA_TAKE_LEFT;

//Parking parameter 
typedef struct tagNET_VCA_PARKING
{
    NET_VCA_POLYGON struRegion;	//Region
    unsigned short wDuration;				//parking duration to trigger alarm: 1-120 seconds, 10 is recommended
    unsigned char byRes[6];
}NET_VCA_PARKING, *LPNET_VCA_PARKING;

//Run parameter 
typedef struct tagNET_VCA_RUN
{
	NET_VCA_POLYGON struRegion;	//Region
    float  fRunDistance;		//Maximum distance to run: [0.1, 1.00]
    unsigned char byRes[4];
}NET_VCA_RUN, *LPNET_VCA_RUN;

//High density parameter 
typedef struct tagNET_VCA_HIGH_DENSITY
{
    NET_VCA_POLYGON struRegion;//Region
    float fDensity;     //density: [0.1, 1.0]
    unsigned char byRes[4];
}NET_VCA_HIGH_DENSITY, *LPNET_VCA_HIGH_DENSITY; 

//stick message parameter 
typedef struct tagNET_VCA_STICK_UP
{
    NET_VCA_POLYGON struRegion;//Region
    unsigned short wDuration; //alarm duration: 10-60 seconds,10 is recommended
    unsigned char  bySensitivity;       //Sensitivity parameter: [1,5]
    unsigned char byRes[5];
}NET_VCA_STICK_UP, *LPNET_VCA_STICK_UP; 

//Scanner parameter 
typedef struct tagNET_VCA_SCANNER
{
    NET_VCA_POLYGON struRegion;//Region
    unsigned short wDuration; // duration to trigger: 10-60 seconds
    unsigned char  bySensitivity;    //Sensitivity parameter: [1,5]
    unsigned char byRes[5];
}NET_VCA_SCANNER, *LPNET_VCA_SCANNER; 


//Alert event parameter 
typedef union tagNET_VCA_EVENT_UNION
{
	unsigned int                uLen[23];			// parameter
	NET_VCA_TRAVERSE_PLANE    struTraversePlane;	//cross alert surface parameter  
	NET_VCA_AREA    	 struArea;			//enter/ leave area  parameter 
	NET_VCA_INTRUSION    struIntrusion;		//intrusion parameter 
	NET_VCA_LOITER       struLoiter;		//loiter parameter 
	NET_VCA_TAKE_LEFT    struTakeTeft;		//drop luggage / pick up luggage parameter 
	NET_VCA_PARKING      struParking;		//parking parameter 
	NET_VCA_RUN          struRun;			//run parameter 
	NET_VCA_HIGH_DENSITY struHighDensity;	//People density parameter   
    NET_VCA_STICK_UP 	struStickUp;		//stick message
    NET_VCA_SCANNER 	struScanner;		//install scanner parameter  	
}NET_VCA_EVENT_UNION, *LPNET_VCA_EVENT_UNION;

// size filter type
typedef enum _VCA_SIZE_FILTER_MODE_
{
	IMAGE_PIX_MODE, //according to pixel size
	REAL_WORLD_MODE //according to actual size
}SIZE_FILTER_MODE;
//size filter
typedef struct tagNET_VCA_SIZE_FILTER
{
	unsigned char    byActive;			//Enable size filter: 0-disable 1-enable
    unsigned char    byMode;		 //SIZE_FILTER_MODE
	unsigned char    byRes[2];        //Reserved, set to 0
	NET_VCA_RECT struMiniRect;    //Minimum target size rectangle, and 0 stands for no restriction
	NET_VCA_RECT struMaxRect;	  //Maximum target size rectangle, and 0 stands for no restriction
}NET_VCA_SIZE_FILTER, *LPNET_VCA_SIZE_FILTER;

//alert rule struct
typedef struct tagNET_VCA_ONE_RULE
{
	unsigned char   byActive;					//activate alarm rule setting: 0-disable, 1-enable
	unsigned char   byRes[7];         			//Reserved，set as 0
    unsigned char   byRuleName[NAME_LEN];		//Rule name
	VCA_EVENT_TYPE dwEventType;			//Behavior Analysis event type,
    NET_VCA_EVENT_UNION uEventParam;	//Behavior Analysis event parameter 
    NET_VCA_SIZE_FILTER  struSizeFilter;  //Size filter
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_2];//On guard schedule
	NET_DVR_HANDLEEXCEPTION_V30 struHandleType;	  //Alarm handle mode 
	unsigned char byRelRecordChan[MAX_CHANNUM_V30];			//Alarm recording channel,set 1 to record
}NET_VCA_ONE_RULE, *LPNET_VCA_ONE_RULE;

//Behavior Analysis config struct
typedef struct tagNET_VCA_RULECFG
{
	unsigned int  dwSize;			//struct size
	unsigned char    byPicProType;	//upload iamge: 0-No, None 0-uplaod
	unsigned char    byRes[3];
	NET_DVR_JPEGPARA struPictureParam; 		//Image struct
	NET_VCA_ONE_RULE  struRule[MAX_RULE_NUM];  //rule array
}NET_VCA_RULECFG, *LPNET_VCA_RULECFG;

//predigest target  struct
typedef struct tagNET_VCA_TARGET_INFO
{
	unsigned int    dwID;				//Target ID, this parameter should be 0 for high density detection
	NET_VCA_RECT struRect;      //target Brim 
    unsigned char      byRes[4];			//Reserved
}NET_VCA_TARGET_INFO, *LPNET_VCA_TARGET_INFO;

//predigest rule info
typedef struct tagNET_VCA_RULE_INFO
{
	unsigned char   byRuleID;		    //Rule ID, ranges from 0-7
	unsigned char   byRes[3];			//Reserved
    unsigned char   byRuleName[NAME_LEN]; //Rule Name
	VCA_EVENT_TYPE  dwEventType; //Event Type
    NET_VCA_EVENT_UNION uEventParam;//Event parameter 
}NET_VCA_RULE_INFO, *LPNET_VCA_RULE_INFO;

//Device address info. It's front-end device's Address for IVMS and local address for other decices
typedef struct tagNET_VCA_DEV_INFO
{
	NET_DVR_IPADDR  struDevIP; //Device IP， 
	unsigned short wPort; 			//Device port number，
	unsigned char byChannel;  		//Device channel number
    unsigned char byRes;		// Reserved
} NET_VCA_DEV_INFO, *LPNET_VCA_DEV_INFO;

//upload behavior Analysis resule struct
typedef struct  tagNET_VCA_RULE_ALARM
{
	unsigned int    dwSize;						//struct size
	unsigned int    dwRelativeTime;				//Relative time stamp
	unsigned int    dwAbsTime;						//Absolute time stamp
	NET_VCA_RULE_INFO     struRuleInfo;		//Alarm rule info
	NET_VCA_TARGET_INFO  struTargetInfo;	//Alarm target info
	NET_VCA_DEV_INFO  	 struDevInfo;		//Device info
	unsigned int dwPicDataLen;						//Snapshot length: 0- no snapshot; >0: snapshot data length after the structure
	unsigned int dwRes[4];							//Reserved，Set to 0
	unsigned char  *pImage;   						//Pointer to the snapshot
}NET_VCA_RULE_ALARM, *LPNET_VCA_RULE_ALARM;

//Behavior Analysis rule, DSP add info struct
typedef struct tagNET_VCA_DRAW_MODE
{ 
	unsigned int  dwSize;
	unsigned char	byDspAddTarget;			//Add target in media stream
 	unsigned char    byDspAddRule;			//Add rule in stream
	unsigned char	byDspPicAddTarget;		//Add target in snapshot
	unsigned char	byDspPicAddRule;		//Add rule in snapshot
	unsigned char	byRes[4];
}NET_VCA_DRAW_MODE, *LPNET_VCA_DRAW_MODE;

// set/get vca behavior param key
NET_DVR_API BOOL __stdcall NET_DVR_SetBehaviorParamKey(int lUserID, int lChannel, unsigned int dwParameterKey,int nValue);
NET_DVR_API BOOL __stdcall NET_DVR_GetBehaviorParamKey(int lUserID, int lChannel, unsigned int dwParameterKey,int *pValue);

//add target API for Get/SetBehavior Analysis
NET_DVR_API BOOL __stdcall NET_DVR_GetVCADrawMode(int lUserID, int lChannel, LPNET_VCA_DRAW_MODE lpDrawMode);
NET_DVR_API BOOL __stdcall NET_DVR_SetVCADrawMode(int lUserID, int lChannel, LPNET_VCA_DRAW_MODE lpDrawMode);

// calibration point sub struct
typedef struct tagNET_DVR_CB_POINT
{
 	NET_VCA_POINT struPoint;     // calibration point, Main camera (fixed camera)
 	NET_DVR_PTZPOS struPtzPos;  //PTZ coordination of Speed dome
	unsigned char	byRes[8];
}NET_DVR_CB_POINT, LPNET_DVR_CB_POINT;

// calibration  parameter config struct
typedef struct tagNET_DVR_TRACK_CALIBRATION_PARAM
{	
	unsigned char byPointNum;			//effective calibration point number
	unsigned char byRes[3];
	NET_DVR_CB_POINT  struCBPoint[MAX_CALIB_PT]; // calibration point array
}NET_DVR_TRACK_CALIBRATION_PARAM, *LPNET_DVR_TRACK_CALIBRATION_PARAM;

//Double Camera Configuration struct
typedef struct tagNET_DVR_TRACK_CFG 
{	
	unsigned int dwSize;				//struct size
    unsigned char byEnable;				// Enable calibration
    unsigned char byFollowChan;          // sub camera
    unsigned char byDomeCalibrate;			//设置智能跟踪球机标定，1设置 0不设置
    unsigned char byRes;					// 保留字节
	NET_DVR_TRACK_CALIBRATION_PARAM  struCalParam; // calibration point
}NET_DVR_TRACK_CFG, *LPNET_DVR_TRACK_CFG;

//Track mode
typedef enum _TRACK_MODE_
{
     MANUAL_CTRL = 0,  //manual
     ALARM_TRACK   ,  //Triggered by alarm
     TARGET_TRACK     //目标跟踪
}TRACK_MODE;

//manual control struct
typedef struct tagNET_DVR_MANUAL_CTRL_INFO 
{
	NET_VCA_POINT struCtrlPoint;
	unsigned char  byRes[8];
}NET_DVR_MANUAL_CTRL_INFO , *LPNET_DVR_MANUAL_CTRL_INFO ;

//Track target struct
typedef struct tagNET_DVR_TRACK_TARGET_INFO
{
	unsigned int dwTargetID;
	unsigned char  byRes[8];
}NET_DVR_TRACK_TARGET_INFO,*LPNET_DVR_TRACK_TARGET_INFO;

typedef struct tagNET_DVR_TRACK_MODE
{
	unsigned int dwSize;		//struct size
	unsigned char byTrackMode;   //Track mode
	unsigned char byRes[3];      //Reserved，set to 0
	union
	{
		unsigned int dwULen[4];
		NET_DVR_MANUAL_CTRL_INFO  struManualCtrl;//manual track struct
	}uModeParam;
}NET_DVR_TRACK_MODE,*LPNET_DVR_TRACK_MODE;

//Track mode configuration interface

NET_DVR_API BOOL __stdcall NET_DVR_SetTrackMode(int lUserID, int lChannel, LPNET_DVR_TRACK_MODE lpTrackMode);
NET_DVR_API BOOL __stdcall NET_DVR_GetTrackMode(int lUserID, int lChannel, LPNET_DVR_TRACK_MODE lpTrackMode);

//Behavior Analysis rule of IVMS
//alert rule struct
typedef struct tagNET_IVMS_ONE_RULE_
{
	unsigned char    byActive;           /*  Enable rule: 0 - No, None 0 - Yes  */
	unsigned char	byRes1[7];	//Reserved，Set to 0
	unsigned char   byRuleName[NAME_LEN]; //Rule name
	VCA_EVENT_TYPE dwEventType;   //Event type of behavior analysis
    NET_VCA_EVENT_UNION uEventParam;//Event parameters of behavior analysis
    NET_VCA_SIZE_FILTER  struSizeFilter;  //Size filter
    unsigned char byRes2[68]; /*Reserved，Set为0*/
}NET_IVMS_ONE_RULE, *LPNET_IVMS_ONE_RULE;

// IVMS Rule Struct
typedef struct tagNET_IVMS_RULECFG
{
	NET_IVMS_ONE_RULE  struRule[MAX_RULE_NUM];   //Rule Array
}NET_IVMS_RULECFG, *LPNET_IVMS_RULECFG;

 // IVMS Behavior Analysis Config Struct
typedef struct tagNET_IVMS_BEHAVIORCFG
{
    unsigned int dwSize;
	unsigned char    byPicProType;	    //Upload image when alarming, 0-No, Non 0- Yes
	unsigned char    byRes[3];
	NET_DVR_JPEGPARA struPicParam; 				//Jpeg Image Strut
	NET_IVMS_RULECFG struRuleCfg[MAX_DAYS][MAX_TIMESEGMENT];//Rules for each time segment 
} NET_IVMS_BEHAVIORCFG, *LPNET_IVMS_BEHAVIORCFG;

// Schedule of getting stream (sub struct)
typedef struct tagNET_IVMS_DEVSCHED
{
	NET_DVR_SCHEDTIME 	struTime;       //Time Parameter 
	NET_DVR_PU_STREAM_CFG struPUStream; //Get Stream 
}NET_IVMS_DEVSCHED, *LPNET_IVMS_DEVSCHED;

//Config struct of IVMS
typedef struct tagNET_IVMS_STREAMCFG
{
    unsigned int dwSize;
	NET_IVMS_DEVSCHED	struDevSched[MAX_DAYS][MAX_TIMESEGMENT];//Config getting stream and rules by time segment.
} NET_IVMS_STREAMCFG, *LPNET_IVMS_STREAMCFG;

// mask region
typedef struct tagNET_VCA_MASK_REGION
{
    unsigned char byEnable;			// Enable: 0 - No, None 0 - Yes
	unsigned char byRes[3];         //Reserved
	NET_VCA_POLYGON  struPolygon; //polygon to mask
}NET_VCA_MASK_REGION, * LPNET_VCA_MASK_REGION;

// mask region linked list
typedef struct tagNET_VCA_MASK_REGION_LIST
{
	unsigned int dwSize;     //struct size
	unsigned char byRes[4];     //Reserved, 0
	NET_VCA_MASK_REGION  struMask[MAX_MASK_REGION_NUM]; // mask region array
}NET_VCA_MASK_REGION_LIST, *LPNET_VCA_MASK_REGION_LIST;


//ATM alert area parameter 
typedef struct tagNET_VCA_ENTER_REGION//ignore people in area to prevent disturbing ATM DVR detection
{
	unsigned int dwSize;
    unsigned char byEnable;			//Enable: 0 - No, None 0 - Yes
	unsigned char byRes1[3];
	NET_VCA_POLYGON  struPolygon; //polygon
	unsigned char byRes2[16];
}NET_VCA_ENTER_REGION, * LPNET_VCA_ENTER_REGION;

//	reboot Intelligent lib
NET_DVR_API BOOL __stdcall NET_VCA_RestartLib(int lUserID, int lChannel);

//IVMS mask region linked list
typedef struct tagNET_IVMS_MASK_REGION_LIST
{
	unsigned int dwSize;    //struct size
	NET_VCA_MASK_REGION_LIST struList[MAX_DAYS][ MAX_TIMESEGMENT];
}NET_IVMS_MASK_REGION_LIST, *LPNET_IVMS_MASK_REGION_LIST;

//Enter ATM Region (Struct of IVMS)
typedef struct tagNET_IVMS_ENTER_REGION
{
	unsigned int dwSize;
	NET_VCA_ENTER_REGION  struEnter[MAX_DAYS][ MAX_TIMESEGMENT]; //Enter ATM Region
}NET_IVMS_ENTER_REGION, *LPNET_IVMS_ENTER_REGION;

// Upload image (IVMS)
typedef struct tagNET_IVMS_ALARM_JPEG
{
    unsigned char                byPicProType;
    unsigned char                byRes[3];
    NET_DVR_JPEGPARA      struPicParam;     
}NET_IVMS_ALARM_JPEG, *LPNET_IVMS_ALARM_JPEG;

// IVMS search config
typedef struct tagNET_IVMS_SEARCHCFG
{
    unsigned int                        dwSize;
    NET_DVR_MATRIX_DEC_REMOTE_PLAY struRemotePlay;// remote playback
    NET_IVMS_ALARM_JPEG         struAlarmJpeg; // config image
    NET_IVMS_RULECFG           struRuleCfg;   //config IVMS behavior analysis rule
}NET_IVMS_SEARCHCFG, *LPNET_IVMS_SEARCHCFG;

//2009-7-22
#define NET_DVR_GET_AP_INFO_LIST	305	//Get AP info list
#define NET_DVR_SET_WIFI_CFG		306	//Set Wifi of surveillance device
#define NET_DVR_GET_WIFI_CFG		307	//Get Wifi config of surveillance device
#define NET_DVR_SET_WIFI_WORKMODE	308	//Set work mode of Network Port 
#define NET_DVR_GET_WIFI_WORKMODE	309	//Get Work mode of Network Port

#define IW_ESSID_MAX_SIZE						 32
#define WIFI_WEP_MAX_KEY_COUNT					 4
#define WIFI_WEP_MAX_KEY_LENGTH					 33
#define WIFI_WPA_PSK_MAX_KEY_LENGTH				 63
#define WIFI_WPA_PSK_MIN_KEY_LENGTH				 8
#define WIFI_MAX_AP_COUNT						 20

typedef struct tagNET_DVR_AP_INFO
{
	char  sSsid[IW_ESSID_MAX_SIZE];
	unsigned int  dwMode;		    /* 0-mange,1-ad-hoc mode(refer to NICMODE) */
	unsigned int  dwSecurity;           /*0 - No encryption, 1 - wep;2 - wpa-psk,3 - wpa-Enterprise(refer to WIFISECURITY)*/
	unsigned int  dwChannel;            /*1-11 for 11 channels*/
	unsigned int  dwSignalStrength;    /*Signal Strength: 0(week)-100(strong)*/
	unsigned int  dwSpeed;				/*Bitrate(Unit: 0.01mbps)*/
}NET_DVR_AP_INFO,*LPNET_DVR_AP_INFO;

typedef struct tagNET_DVR_AP_INFO_LIST
{
	unsigned int dwSize;
	unsigned int dwCount;        /*Number of wireless AP, maximum is 20*/
	NET_DVR_AP_INFO struApInfo[WIFI_MAX_AP_COUNT];
}NET_DVR_AP_INFO_LIST,*LPNET_DVR_AP_INFO_LIST;

typedef struct tagNET_DVR_WIFIETHERNET
{	
	char sIpAddress[16];				/*IP address*/
	char sIpMask[16];					/*Mask*/	
	unsigned char	byMACAddr[MACADDR_LEN];		/*MAC, read only*/
	unsigned char	bRes[2];
	unsigned int	dwEnableDhcp;			/*Enable dhcp  0-disable, 1-enable*/
	unsigned int	dwAutoDns;			/*If gets DNS automatically after enabling DHCP:0-NO 1-Yes.(Wire network will get DNS automatically after enabling DHCP*/
	char sFirstDns[16];				 /*First DNS domain name*/
	char sSecondDns[16];				/*Second DNS domain name*/
	char sGatewayIpAddr[16]; 			/* Gateway address*/
	unsigned char   bRes2[8];
}NET_DVR_WIFIETHERNET,*LPNET_DVR_WIFIETHERNET;

typedef struct tagNET_DVR__WIFI_CFG_EX
{
	NET_DVR_WIFIETHERNET struEtherNet;        /*wifi网口*/
	char sEssid[IW_ESSID_MAX_SIZE];	 /*SSID*/
	unsigned int dwMode;      /* 0 mange 模式;1 ad-hoc模式，参见*/
	unsigned int dwSecurity; /*0 不加密；1 wep加密；2 wpa-psk; */
	union 
	{
		struct 
		{
			unsigned int dwAuthentication;/*0 -Open Mode 1-Shared mode*/
			unsigned int dwKeyLength;/*  0 -64 bits;1- 128 bits;2-152 bits*/
			unsigned int dwKeyType;/*0-Hex mode; 1-ASCI*/
			unsigned int dwActive;/*Key Index:0---3 stands for actived key*/
			char sKeyInfo[WIFI_WEP_MAX_KEY_COUNT][WIFI_WEP_MAX_KEY_LENGTH];
		}wep;
		struct 
		{
			unsigned int dwKeyLength;/*key Length: 8-63 ASCII characters*/
			char sKeyInfo[WIFI_WPA_PSK_MAX_KEY_LENGTH];
			char sRes;
		}wpa_psk;
		
	}key;	
}NET_DVR_WIFI_CFG_EX,*LPNET_DVR_WIFI_CFG_EX;

//wifi config struct
typedef struct tagNET_DVR_WIFI_CFG
{
	unsigned int dwSize;
	NET_DVR_WIFI_CFG_EX struWifiCfg;
}NET_DVR_WIFI_CFG,*LPNET_DVR_WIFI_CFG;

//wifi work mode
typedef struct tagNET_DVR_WIFI_WORKMODE
{
	unsigned int dwSize;
	unsigned int dwNetworkInterfaceMode; /*0-Automatically switch mode 1- wire mode*/
}NET_DVR_WIFI_WORKMODE,*LPNET_DVR_WIFI_WORKMODE;

NET_DVR_API BOOL __stdcall NET_DVR_SaveRealData_V30(int lRealHandle, unsigned int dwTransType, char *sFileName);
NET_DVR_API BOOL __stdcall NET_DVR_EncodeG711Frame(unsigned int iType, unsigned char *pInBuffer, unsigned char *pOutBuffer);
NET_DVR_API BOOL __stdcall NET_DVR_DecodeG711Frame(unsigned int iType, unsigned char *pInBuffer, unsigned char *pOutBuffer);
//2009-7-22 end

//Structure of Adding Network Hard Disk Drive
typedef struct tagNET_DVR_SINGLE_NET_DISK_INFO
{
	unsigned char byRes1[4];							//Reserved
    NET_DVR_IPADDR struNetDiskAddr;			//IP Address of the net disk
    unsigned char sDirectory[PATHNAME_LEN];			// PATHNAME_LEN = 128
	unsigned char byRes2[68];							//Reserved
}NET_DVR_SINGLE_NET_DISK_INFO, *LPNET_DVR_SINGLE_NET_DISK_INFO;

#define MAX_NET_DISK	16//The network hard disk number.

typedef struct tagNET_DVR_NET_DISKCFG 
{
    unsigned int  dwSize;
    NET_DVR_SINGLE_NET_DISK_INFO struNetDiskParam[MAX_NET_DISK];
}NET_DVR_NET_DISKCFG, *LPNET_DVR_NET_DISKCFG;

//Event type
//Major type 
typedef enum _MAIN_EVENT_TYPE_
{
	EVENT_MOT_DET = 0,		// motion detection
	EVENT_ALARM_IN = 1,		// alarm input
	EVENT_VCA_BEHAVIOR = 2	//Behavior Analysis
}MAIN_EVENT_TYPE;

//Behavior Analysis's sub type， 0xffff stands for all type
typedef enum _BEHAVIOR_MINOR_TYPE_
{
	EVENT_TRAVERSE_PLANE     = 0,    // cross alert surface ,
	EVENT_ENTER_AREA,				//enter area,support region rule
	EVENT_EXIT_AREA,				//leave area,support region rule
	EVENT_INTRUSION,				 //perimeter intrusion,support region rule
	EVENT_LOITER,				 //loiter,support region rule
	EVENT_LEFT_TAKE,				//drop/pick up luggage,support region rule
	EVENT_PARKING,					//parking,support region rule
	EVENT_RUN,					//run,support region rule
	EVENT_HIGH_DENSITY,				 //density of people,support region rule
    EVENT_OBJECT_PASTE	    =20		// 异物粘贴区域
}BEHAVIOR_MINOR_TYPE;


#define SEARCH_EVENT_INFO_LEN 300	//length of event info

//Search Conditions
typedef struct tagNET_DVR_SEARCH_EVENT_PARAM
{
	unsigned short wMajorType;			//0-Motion Detection，1-Sensor Alarm, 2-Intelligent Event
	unsigned short wMinorType;			//sub types, it's different according to major type, 0xffff means all the sub types.
	NET_DVR_TIME struStartTime;	//The start time and end time of the search; if both of them are 0, it means it will search the first 4000 events from the start time to the end time.
	NET_DVR_TIME struEndTime;	//
	unsigned char byRes[132];			//Reserved
	union	
	{
		unsigned char byLen[SEARCH_EVENT_INFO_LEN];
		struct//Sensor Alarm
		{
			unsigned char byAlarmInNo[MAX_ALARMIN_V30];    //he nubmer of Sensor Alarm，byAlarmInNo[0], if it is 1, it means searching the events triggered by Sensor Alarm1.
			unsigned char byRes[SEARCH_EVENT_INFO_LEN - MAX_ALARMIN_V30];
		}struAlarmParam;
		struct//Motion Detection
		{
			unsigned char byMotDetChanNo[MAX_CHANNUM_V30];//The channel number of Motion Detection, byMotDetChanNo[0], if it is 1, it means searching the events triggered by Motion Detection of channel 1.
			unsigned char byRes[SEARCH_EVENT_INFO_LEN - MAX_CHANNUM_V30];
		}struMotionParam;
		struct//Behavior Analysis
		{
			unsigned char byChanNo[MAX_CHANNUM_V30];	//The channel that triggerd Event
			unsigned char byRuleID;					//Rules ID, 0xff means all the rules
			unsigned char byRes1[43];				//Reserved
		}struVcaParam;
	}uSeniorParam;
}NET_DVR_SEARCH_EVENT_PARAM, *LPNET_DVR_SEARCH_EVENT_PARAM;

//The result of event search
typedef struct tagNET_DVR_SEARCH_EVENT_RET
{
	unsigned short wMajorType;			//Major type
	unsigned short wMinorType;			//sub type
	NET_DVR_TIME struStartTime;	//Start time of the event 
	NET_DVR_TIME struEndTime;   //End time of the event; Start time and end time of a pulse event are the same.
	unsigned char byChan[MAX_CHANNUM_V30];
	unsigned char byRes[36];
	union		
	{
		struct//Sensor Alarm result
		{
			unsigned int dwAlarmInNo;     //Sensor Alarm number
			unsigned char byRes[SEARCH_EVENT_INFO_LEN];
		}struAlarmRet;
		struct//Motion Detection result
		{
			unsigned int dwMotDetNo;	//Channel number of Motion Detection
			unsigned char byRes[SEARCH_EVENT_INFO_LEN];
		}struMotionRet;
		struct//Behavior Analysis result  
		{
			unsigned int dwChanNo;					//The channel that triggered the event
			unsigned char byRuleID;					//rules ID
			unsigned char byRes1[3];					//Reserved
			unsigned char byRuleName[NAME_LEN];		// rules name
			NET_VCA_EVENT_UNION uEvent;     //Parameters of behavior event，wMinorType = VCA_EVENT_TYPE decide the event type
		}struVcaRet;
	}uSeniorRet;
}NET_DVR_SEARCH_EVENT_RET, *LPNET_DVR_SEARCH_EVENT_RET;

NET_DVR_API int __stdcall NET_DVR_FindFileByEvent(int lUserID, LPNET_DVR_SEARCH_EVENT_PARAM  lpSearchEventParam);
NET_DVR_API int __stdcall NET_DVR_FindNextEvent(int lSearchHandle, LPNET_DVR_SEARCH_EVENT_RET lpSearchEventRet);
//NET_DVR_FindClose is invalid

//2008-08-25
//IP Camera parameter(NET_DVR_IPPARACFG_V31 struct)
#define     NET_DVR_GET_IPPARACFG_V31            1060        //Get IP device parameter 
#define     NET_DVR_SET_IPPARACFG_V31            1061        //Set IP device parameter 

//IP device Information-extension. Support adding IP device by their domain name
typedef struct tagNET_DVR_IPDEVINFO_V31
{
    unsigned char byEnable;				    //Enable or not
	unsigned char byProType;					// Protocol Type, 0-Hikvision(default), 1-Panasonic, 2-Sony
	unsigned char byRes1[2];					//Reserved, set to 0
    unsigned char sUserName[NAME_LEN];		//User name
    unsigned char sPassword[PASSWD_LEN];	    //Password
    unsigned char byDomain[MAX_DOMAIN_NAME];	//device domain name
    NET_DVR_IPADDR struIP;			//IP address	
    unsigned short wDVRPort;			 	    // port
	unsigned char byRes2[34];				//Reserved, set to 0
}NET_DVR_IPDEVINFO_V31, *LPNET_DVR_IPDEVINFO_V31;

/* IP Parameters Configurations -extension */
typedef struct tagNET_DVR_IPPARACFG_V31
{
    unsigned int dwSize;			                            /*  struct size */
    NET_DVR_IPDEVINFO_V31  struIPDevInfo[MAX_IP_DEVICE];    /* IP device */
    unsigned char byAnalogChanEnable[MAX_ANALOG_CHANNUM];        /* Analogue channels are enabled or disabled. 0 means disabled, while 1 means enabled. The array means different channels, from 1 to 32.  */
    NET_DVR_IPCHANINFO struIPChanInfo[MAX_IP_CHANNEL];	/*  IP channels */    
}NET_DVR_IPPARACFG_V31, *LPNET_DVR_IPPARACFG_V31;

//ipc alarm info (extended)
typedef struct tagNET_DVR_IPALARMINFO_V31
{
    NET_DVR_IPDEVINFO_V31  struIPDevInfo[MAX_IP_DEVICE];            /* IP device information */
    unsigned char byAnalogChanEnable[MAX_ANALOG_CHANNUM];                /* enable analog channels or not, 0-disabled, 1-enabled */
    NET_DVR_IPCHANINFO struIPChanInfo[MAX_IP_CHANNEL];	        /* IP channel  */
    NET_DVR_IPALARMININFO struIPAlarmInInfo[MAX_IP_ALARMIN];    /* IP Sensor Alarm  */
    NET_DVR_IPALARMOUTINFO struIPAlarmOutInfo[MAX_IP_ALARMOUT]; /* IP Relay output */   
}NET_DVR_IPALARMINFO_V31, *LPNET_DVR_IPALARMINFO_V31;

#define COMM_IPCCFG_V31			    0x4002	//DS-9000 Hybrid DVR's alarm output parameter, which has been extended because of connection with IP Camera.

#define MINOR_NET_DISK_INFO				0xa8   //net disk information
#define MINOR_LOCAL_ADD_NAS             0x6a /* Local add NAS hard disk (nfs、iscsi)*/
#define MINOR_LOCAL_DEL_NAS             0x6b /* Local delete NAS hard disk (nfs、iscsi)*/
#define MINOR_LOCAL_SET_NAS             0x6c /* Local setup NAS hard disk (nfs、iscsi)*/
#define MINOR_REMOTE_ADD_NAS            0x8e  /* Remote add NAS hard disk (nfs、iscsi)*/
#define MINOR_REMOTE_DEL_NAS            0x8f  /* Remote delete NAS hard disk (nfs、iscsi) */
#define MINOR_REMOTE_SET_NAS            0x90  /* Remote set NAS hard disk (nfs、iscsi)*/



//Structure of Setting Network Hard Disk Drive  (NET_DVR_NET_DISKCFG struct)
#define		NET_DVR_GET_NET_DISKCFG				1038		//Get the configuration of Network Hard Disk Drive	
#define		NET_DVR_SET_NET_DISKCFG				1039		//Set the configuration of Configuring Network Hard Disk Drive

//2009-4-13 Added
NET_DVR_API BOOL __stdcall NET_DVR_MatrixStartDynamic_V30(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_PU_STREAM_CFG lpDynamicInfo);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetLoopDecChanInfo_V30(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_LOOP_DECINFO_V30 lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetLoopDecChanInfo_V30(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_LOOP_DECINFO_V30 lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetDecChanInfo_V30(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_DEC_CHAN_INFO_V30 lpInter);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetTranInfo_V30(int lUserID, LPNET_DVR_MATRIX_TRAN_CHAN_CONFIG_V30 lpTranInfo);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetTranInfo_V30(int lUserID, LPNET_DVR_MATRIX_TRAN_CHAN_CONFIG_V30 lpTranInfo);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetDisplayCfg(int lUserID, unsigned int dwDispChanNum, LPNET_DVR_VGA_DISP_CHAN_CFG lpDisplayCfg);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSetDisplayCfg(int lUserID, unsigned int dwDispChanNum, LPNET_DVR_VGA_DISP_CHAN_CFG lpDisplayCfg);

NET_DVR_API int __stdcall NET_DVR_MatrixStartPassiveDecode(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_MATRIX_PASSIVEMODE lpPassiveMode /*, void(CALLBACK *fPassiveDataCallBack)(int lPassiveHandle, char * pSendBuf, unsigned int dwBufSize, unsigned int dwStatus, unsigned int dwUser), unsigned int dwUser*/);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixSendData(int lPassiveHandle, char *pSendBuf, unsigned int dwBufSize);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixStopPassiveDecode(int lPassiveHandle);
NET_DVR_API BOOL __stdcall NET_DVR_UploadLogo(int lUserID, unsigned int dwDispChanNum, LPNET_DVR_DISP_LOGOCFG lpDispLogoCfg, char *sLogoBuffer);
#define	NET_DVR_SHOWLOGO			1		/* Show LOGO*/
#define	NET_DVR_HIDELOGO			2		/* Hide LOGO*/   
NET_DVR_API BOOL __stdcall NET_DVR_LogoSwitch(int lUserID, unsigned int dwDecChan, unsigned int dwLogoSwitch);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixGetDeviceStatus(int lUserID,  LPNET_DVR_DECODER_WORK_STATUS lpDecoderCfg);

/*Commands definition of display channel */
#define	DISP_CMD_ENLARGE_WINDOW				1	/*Enlarge some region*/
#define	DISP_CMD_RENEW_WINDOW				2	/*restore the region*/

NET_DVR_API BOOL __stdcall NET_DVR_MatrixDiaplayControl(int lUserID, unsigned int dwDispChanNum, unsigned int dwDispChanCmd, unsigned int dwCmdParam);
NET_DVR_API BOOL __stdcall NET_DVR_MatrixPassiveDecodeControl(int lUserID, unsigned int dwDecChanNum, LPNET_DVR_PASSIVEDECODE_CONTROL lpInter);
NET_DVR_API int __stdcall NET_DVR_MatrixGetPassiveDecodeStatus(int lPassiveHandle);
//end Multi-channel decoder.

//回放画图回调注册
NET_DVR_API BOOL __stdcall NET_DVR_RigisterPlayBackDrawFun(int lPlayHandle, void (CALLBACK* fDrawFun)(int lPlayHandle, HDC hDc, unsigned int dwUser), unsigned int dwUser);


//图像增强仪
//图像增强去燥区域配置
typedef struct tagIMAGEREGION
{
    unsigned int dwSize ;//总的结构长度
    unsigned short wImageRegionTopLeftX;			/* 图像增强去燥的左上x坐标 */
    unsigned short wImageRegionTopLeftY;			/* 图像增强去燥的左上y坐标 */
    unsigned short wImageRegionWidth;			/* 图像增强去燥区域的宽 */
    unsigned short wImageRegionHeight;			/*图像增强去燥区域的高*/
    unsigned char  byRes[16] ;
} NET_DVR_IMAGEREGION, *LPNET_DVR_IMAGEREGION;

//图像增强、去噪级别及稳定性使能配置
typedef struct tagIMAGESUBPARAM
{
    NET_DVR_SCHEDTIME	struImageStatusTime;//图像状态时间段
    unsigned char	byImageEnhancementLevel ;//图像增强的级别，0-9，0表示关闭
    unsigned char	byImageDenoiseLevel ;//图像去噪的级别，0-9，0表示关闭
    unsigned char	byImageStableEnable;//图像稳定性使能，0表示关闭，1表示打开
    unsigned char    byRes[9] ;
} NET_DVR_IMAGESUBPARAM, *LPNET_DVR_IMAGESUBPARAM;
#define     NET_DVR_GET_IMAGEREGION              1062       //图像增强仪图像增强去燥区域获取
#define     NET_DVR_SET_IMAGEREGION              1063       //图像增强仪图像增强去燥区域获取
#define     NET_DVR_GET_IMAGEPARAM               1064       // 图像增强仪图像参数(去噪、增强级别，稳定性使能)获取
#define     NET_DVR_SET_IMAGEPARAM               1065       // 图像增强仪图像参数(去噪、增强级别，稳定性使能)设置
typedef struct tagIMAGEPARAM
{
    unsigned int	 dwSize;
    //图像增强时间段参数配置，周日开始	   	
    NET_DVR_IMAGESUBPARAM struImageParamSched[MAX_DAYS][MAX_TIMESEGMENT];
    unsigned char  byRes[16] ;
} NET_DVR_IMAGEPARAM, *LPNET_DVR_IMAGEPARAM;
NET_DVR_API BOOL __stdcall NET_DVR_GetParamSetMode(int lUserID, unsigned int *dwParamSetMode);

//SDK_V35  2009-10-26
// 异物监测规则配置
typedef enum 
{
    DETECTION_AREA = 0, // 检测区域
    ENTER_AREA  = 1     //进入区域
}DETECT_TYPE;
typedef struct tagNET_DVR_DETECT_RECT
{
    NET_VCA_RECT  struVcaRect; // 监视区域
    unsigned char            byDetectType;  //监视类型 详见DETECT_TYPE
    unsigned char            byRes1[7];		// 保留字节
}NET_DVR_DETECT_RECT, *LPNET_DVR_DETECT_RECT;
#define MAX_DETECT_RECT 8  // 最大检测区域个数
typedef struct tagNET_DVR_DETECT_RECT_LIST
{	
    unsigned char    byDetectNum;    // 监测区域个数
    unsigned char    byRes1[3];      //保留字节
    NET_DVR_DETECT_RECT struDetectRect[MAX_DETECT_RECT]; // 检测区域列表
}NET_DVR_DETECT_RECT_LIST, *LPNET_DVR_DETECT_RECT_LIST;

typedef struct tagNET_DVR_ALARM_JPEG
{
    unsigned char    byPicProType;	    /*报警时图片处理方式 0-不处理 1-上传*/
    unsigned char    byRes[3];           //保留字节
    NET_DVR_JPEGPARA struPicParam; 				/*图片规格结构*/
}NET_DVR_ALARM_JPEG, *LPNET_DVR_ALARM_JPEG;
typedef struct tagNET_DVR_DETECT_RULECFG
{
    unsigned int dwSize;       // 结构大小
    NET_DVR_DETECT_RECT_LIST struDetectRectList;
    NET_DVR_ALARM_JPEG struAlarmJpeg;	// 报警上传图片
    unsigned char byRelRecordChan[MAX_CHANNUM_V30];			//报警触发的录象通道,为1表示触发该通道
    NET_DVR_HANDLEEXCEPTION_V30 struHandleType;//处理方式
    NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_2];//布防时间
    unsigned char byRes2[40];
}NET_DVR_DETECT_RULECFG, *LPNET_DVR_DETECT_RULECFG;


// 设置人脸识别内部参数关键字
typedef enum _FACE_PARAM_KEY_
{
    MAX_FACE_SIZE = 20, // 最大人脸大小
        MINI_FACE_SIZE = 21	// 最小人脸大小
}FACE_PARAM_KEY;  // 人脸识别内部参数

// 标定配置类型
typedef enum tagCALIBRATE_TYPE
{
    PDC_CALIBRATE  = 0x01  // PDC 标定
}CALIBRATE_TYPE;



#define MAX_RECT_NUM  6
typedef struct tagNET_DVR_RECT_LIST
{	
    unsigned char    byRectNum;    // 矩形框的个数
    unsigned char    byRes1[11];  //保留字节
    NET_VCA_RECT struVcaRect[MAX_RECT_NUM]; // 最大为6个Rect 
}NET_DVR_RECT_LIST, *LPNET_DVR_RECT_LIST;

// PDC 标定参数
typedef struct tagNET_DVR_PDC_CALIBRATION
{
    NET_DVR_RECT_LIST struRectList;       // 标定矩形框列表
    unsigned char           byRes[120];       // 保留字节
}NET_DVR_PDC_CALIBRATION, *LPNET_DVR_PDC_CALIBRATION;

// 标定参数联合体
// 后续的相关标定参数可以放在该结构里面
typedef union tagNET_DVR_CALIBRATION_PRARM_UNION
{
    unsigned char byRes[240];                    //联合体结构大小
    NET_DVR_PDC_CALIBRATION struPDCCalibration;  //PDC 标定参数
}NET_DVR_CALIBRATION_PRARM_UNION, *LPNET_DVR_CALIBRATION_PRARM_UNION;

// 标定配置结构
typedef struct tagNET_DVR_CALIBRATION_CFG
{
    unsigned int   dwSize;               //标定结构大小
    unsigned char    byEnable;           // 是否启用标定
    unsigned char    byCalibrationType;    // 标定类型 根据不同类型在联合体类选择不同的标定 参考CALIBRATE_TYPE
    unsigned char    byRes1[2];
    NET_DVR_CALIBRATION_PRARM_UNION uCalibrateParam;  // 标定参数联合体
    unsigned char    byRes2[12];
}NET_DVR_CALIBRATION_CFG, *LPNET_DVR_CALIBRATION_CFG; 

//流量统计方向结构体
typedef struct  tagNET_DVR_PDC_ENTER_DIRECTION
{
    NET_VCA_POINT struStartPoint; //流量统计方向起始点
    NET_VCA_POINT struEndPoint;    // 流量统计方向结束点 
}NET_DVR_PDC_ENTER_DIRECTION, *LPNET_DVR_PDC_ENTER_DIRECTION;

typedef struct tagNET_DVR_PDC_RULE_CFG
{
    unsigned int           dwSize;              //结构大小
    unsigned char            byEnable;             // 是否激活规则;
    unsigned char            byRes1[23];       // 保留字节
    NET_VCA_POLYGON          struPolygon;            // 多边形
    NET_DVR_PDC_ENTER_DIRECTION  struEnterDirection;    // 流量进入方向
} NET_DVR_PDC_RULE_CFG, *LPNET_DVR_PDC_RULE_CFG;

//设置人流量统计参数  复用行为内部关键字参数 
typedef enum tagPDC_PARAM_KEY
{
    HUMAN_GENERATE_RATE = 50,              //目标生成速度 从50开始
    DETECT_SENSITIVE    = 51                  //检测灵敏度
}PDC_PARAM_KEY;

#define  COMM_ALARM_PDC				0x1103	//人流量量报警上传
typedef struct tagNET_DVR_PDC_TARGET_INFO
{
    unsigned int       dwTargetID;                 // 目标id
    NET_VCA_RECT struTargetRect;               // 目标框
    unsigned char      byRes1[8];        // 保留字节
}NET_DVR_PDC_TARGET_INFO, *LPNET_DVR_PDC_TARGET_INFO;

typedef struct tagNET_DVR_PDC_TARGET_IN_FRAME
{
    unsigned char           byTargetNum;                   //目标个数
    unsigned char            byRes1[3];
        NET_DVR_PDC_TARGET_INFO  struTargetInfo[MAX_TARGET_NUM];   //目标信息数组
    unsigned char    byRes2[8];                  // 保留字节
}NET_DVR_PDC_TARGET_IN_FRAME, *LPNET_DVR_PDC_TARGET_IN_FRAME;

typedef struct tagNET_DVR_PDC_ALRAM_INFO
{
    unsigned int                       dwSize;           // PDC人流量报警上传结构体大小
    unsigned char                        byMode;            // 0 单帧统计结果 1最小时间段统计结果
    unsigned char                        byChannel;           // 报警上传通道号
    unsigned char                        byRes1[2];         // 保留字节
    NET_VCA_DEV_INFO  	 struDevInfo;		        //前端设备信息
    union		
    {
        struct   // 单帧统计结果时使用
        {
            unsigned int   dwRelativeTime;     // 相对时标
            unsigned int   dwAbsTime;          // 绝对时标
            unsigned char    byRes[92];
        }struStatFrame;
        struct
        {
            NET_DVR_TIME                      tmStart; // 统计起始时间 
            NET_DVR_TIME                      tmEnd;  //  统计结束时间 
            unsigned char byRes[92];
        }struStatTime;
    }uStatModeParam;  // 作为一个联合体 单帧的时候才有帧内目标信息 最小时间段统计结果需要统计时间 参数
    unsigned int                       dwLeaveNum;        // 离开人数
    unsigned int                       dwEnterNum;        // 进入人数
    unsigned char                        byRes2[40];           // 保留字节
}NET_DVR_PDC_ALRAM_INFO, *LPNET_DVR_PDC_ALRAM_INFO;


//  人流量信息查询 
typedef struct tagNET_DVR_PDC_QUERY
{
    NET_DVR_TIME tmStart;
    NET_DVR_TIME tmEnd;
    unsigned int       dwLeaveNum;
    unsigned int        dwEnterNum;
    unsigned char        byRes1[256];

}NET_DVR_PDC_QUERY, *LPNET_DVR_PDC_QUERY;

NET_DVR_API int __stdcall NET_DVR_FindPDCInfo(int lUserID, int lChannel, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);
NET_DVR_API int __stdcall NET_DVR_FindNextPDCInfo(int lFindHandle,LPNET_DVR_PDC_QUERY lpFindData);
NET_DVR_API BOOL __stdcall NET_DVR_FindPDCClose(int lFindHandle);

// 标定校验 
#define NET_DVR_PDC_VERIFY_CALIBRATION  1  //当值为1是为PDC标定校验 pdc传入值为NET_VCA_POINT   传出值为 NET_VCA_RECT结构
NET_DVR_API BOOL __stdcall NET_DVR_VerifyCalibration(int lUserID, unsigned int dwCommand, int lChannel, LPVOID lpInBuffer, unsigned int dwInBufferSize, LPVOID lpOuterBuffer, unsigned int dwOuterBufferSize);

NET_DVR_API BOOL __stdcall  NET_DVR_ResetCounter(int lUserID,int lChannel);

typedef struct    tagNET_DVR_PTZ_POSITION
{
    unsigned char byVcaPtzId; //ptz场景规则配置 ID
    unsigned char byRes1[3];  //保留
    unsigned char byPtzPositionName[NAME_LEN]; //场景位置名称
    NET_DVR_PTZPOS struPtzPos; //ptz 坐标
    unsigned char byRes2[40];
}NET_DVR_PTZ_POSITION, *LPNET_DVR_PTZ_POSITION;

typedef struct tagNET_DVR_VCA_POSITON_RULE_CFG
{
    unsigned int                   dwSize;             // 结构大小
    NET_DVR_PTZ_POSITION    struPtzPosition;    // 场景位置信息
    NET_VCA_RULECFG         struVcaRuleCfg;     //行为规则配置
    unsigned char                    byRes2[80];         // 保留字节
}NET_DVR_POSITON_RULE_CFG, *LPNET_DVR_POSITON_RULE_CFG;
// SDK_V35

//09-11-21
typedef struct 
{
    NET_DVR_TIME strLogTime;
    unsigned int	dwMajorType;	//Main type 1-alarm; 2-abnormal; 3-operation; 0xff-all
    unsigned int	dwMinorType;	//Hypo-Type 0-all;
    unsigned char	sPanelUser[MAX_NAMELEN]; //user ID for local panel operation
    unsigned char	sNetUser[MAX_NAMELEN];//user ID for network operation
    NET_DVR_IPADDR	struRemoteHostAddr;//remote host IP
    unsigned int	dwParaType;//parameter type
    unsigned int	dwChannel;//channel number
    unsigned int	dwDiskNumber;//HD number
    unsigned int	dwAlarmInPort;//alarm input port
    unsigned int	dwAlarmOutPort;//alarm output port
    unsigned int   dwInfoLen;
    unsigned char  byDevSequence;//槽位号
    unsigned char  byMacAddr[MACADDR_LEN];//MAC地址,6
    unsigned char  sSerialNumber[SERIALNO_LEN];//序列号，48
    char  sInfo[LOG_INFO_LEN - SERIALNO_LEN - MACADDR_LEN - 1 ];
}NET_DVR_LOG_MATRIX, *LPNET_DVR_LOG_MATRIX;
NET_DVR_API int __stdcall NET_DVR_FindNextLog_MATRIX(int lLogHandle, LPNET_DVR_LOG_MATRIX lpLogData);
//2009-11-21 视频综合平台
typedef struct tagVEDIOPLATLOG
{
    unsigned char bySearchCondition;//搜索条件，0-按槽位号搜索，1-按序列号搜索，                          							//2-按MAC地址进行搜索
    unsigned char byDevSequence;//槽位号，0-79：对应子系统的槽位号；
    //0xff：表示搜索所有的日志，包括78K和所有6467；
    //0xfe：表示搜索78K上的日志。
    unsigned char  sSerialNumber[SERIALNO_LEN];//序列号，48
    unsigned char  byMacAddr[MACADDR_LEN];//MAC地址,6
} NET_DVR_VEDIOPLATLOG, *LPNET_DVR_VEDIOPLATLOG;
//2009-11-21
NET_DVR_API int __stdcall NET_DVR_FindDVRLog_Matrix(int lUserID, int lSelectMode, unsigned int dwMajorType, unsigned int dwMinorType, LPNET_DVR_VEDIOPLATLOG lpVedioPlatLog, LPNET_DVR_TIME lpStartTime, LPNET_DVR_TIME lpStopTime);
//2009-12-17 增加视频综合平台编码子系统能力集
#define VIDEOPLATFORM_SBUCODESYSTEM_ABILITY          0x211 //视频综合平台编码子系统能力集
typedef struct tagNET_DVR_CODESYSTEMABILITY
{
    unsigned int dwSize;
    unsigned int dwAbilityVersion;//能力集版本号，高16位表示主版本，低16位表示次版本
    unsigned int dwSupportMaxVideoFrameRate;//单位(K)
	/*按位:
	0:定时录像；
	1:定时|事件触发录像 
	2:移动侦测录像；
	3:网络开关量报警录像；
	4:移动侦测|网络开关量报警录像；
	5:移动侦测&网络开关量报警录像；
	6:周界防范触发录像；
	7:人脸检测触发录像；
	8:车牌识别触发录像；
	9:手动录像*/
    unsigned int dwSupportRecordType;
    unsigned char  bySupportLinkMode;//按位:第0位:表示主码流，第1位:表示子码流
    unsigned char  byRes[71];//保留
}NET_DVR_CODESYSTEMABILITY, *LPNET_DVR_CODESYSTEMABILITY;

//2009-12-22 增加视频综合平台按通道获取PTZ协议接口
NET_DVR_API BOOL __stdcall NET_DVR_GetPTZProtocol_Ex(int lUserID, int lChannel, NET_DVR_PTZCFG *pPtzcfg);

#ifdef __cplusplus
}
#endif

