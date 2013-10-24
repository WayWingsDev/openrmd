#ifndef _HISI_SDK_H_
#define _HISI_SDK_H_

#define SERIALNO_LEN  32                   //serial number length
#define HISI_DVR_NOERROR  0                //û�д���
#define HISI_DVR_NETWORK_FAIL_CONNECT  1   //���ӷ�����ʧ��
#define HISI_DVR_PASSWORD_ERROR  2         //�û��������������,��¼ʧ��

#define  HISI_COMM_EXCEPTION 0x11         //ͨ���쳣��Ϣ
#define  HISI_COMM_ALARM 0x12             //ͨ�ñ�����Ϣ
#define  HISI_ALARM_WIRELESS 0x13         //����ģ�鱨����Ϣ
#define  HISI_ALARM_UPS 0x14              //UPS������Ϣ

#define  HISI_EXCEPTION_EXCHANGE   0x8000           //�û�����ʱ�쳣
#define  HISI_EXCEPTION_AUDIOEXCHANGE   0x8001      //�����Խ��쳣
#define  HISI_EXCEPTION_ALARM   0x8002              //�����쳣
#define  HISI_EXCEPTION_PREVIEW   0x8003            //����Ԥ���쳣
#define  HISI_EXCEPTION_ORDERCALL  0x8004;          //����˳�����
#define  HISI_EXCEPTION_RECONNECT   0x8005          //Ԥ��ʱ����
#define  HISI_EXCEPTION_ALARMRECONNECT   0x8006     //����ʱ����
#define  HISI_EXCEPTION_NOTINIT  0x8007;            //δ���ó�ʼ��
#define  HISI_EXCEPTION_GETVIDEOPORT  0x8008;       //��ȡ��Ƶ�˿�ʧ��
#define  HISI_EXCEPTION_GETHTTPPORT  0x8009;        //��ȡHTTP�������˿�ʧ��
#define  HISI_EXCEPTION_PLAYBACK   0x8010           //�ط��쳣
#define  HISI_EXCEPTION_NOPLAYHANDLE  0x8011;       //�޲��������
#define  HISI_EXCEPTION_EXMAXCHANNEL  0x8012;       //�������ͨ����
#define  HISI_EXCEPTION_NETERROR  0x8013;           //�����쳣
#define  HISI_EXCEPTION_ORDER  0x8014;              //��������˳�����
#define  HISI_EXCEPTION_MAXPLAY  0x8015;            //�ﵽ��󲥷���
#define  HISI_EXCEPTION_EXMAXVALUE  0x8016;         //�������ֵ
#define  HISI_EXCEPTION_INVALIDHANDLE  0x8017;      //��Ч�ľ��

#define  HISI_DVR_GET_DEVICECFG	  1	   //��ȡ�豸����
#define  HISI_DVR_GET_ENCODECFG   2    //��ȡ�������
#define  HISI_DVR_GET_MISCCFG     3    //��ȡͨ�ò���
#define  HISI_DVR_GET_NETCFG	  4	   //��ȡ�������
#define  HISI_DVR_GET_SCREENCFG   5    //��ȡ��Ļ����
#define  HISI_DVR_GET_PTZCFG      6    //��ȡ��̨����
#define  HISI_DVR_GET_SENSORCFG   7    //��ȡ��������
#define  HISI_DVR_GET_DETECTIONCFG  8  //��ȡ������
#define  HISI_DVR_GET_SCHEDULECFG   9  //��ȡ¼��ʱ�����

#define  HISI_DVR_SET_ENCODECFG   20     //���ñ������
#define  HISI_DVR_SET_MISCCFG     21     //����ͨ�ò���
#define  HISI_DVR_SET_NETCFG	  22	 //�����������
#define  HISI_DVR_SET_SCREENCFG   23     //������Ļ����
#define  HISI_DVR_SET_PTZCFG      24     //������̨����
#define  HISI_DVR_SET_SENSORCFG   25     //���ñ�������
#define  HISI_DVR_SET_DETECTIONCFG  26   //����������
#define  HISI_DVR_SET_SCHEDULECFG   27   //����¼��ʱ�����

#define  HISI_DVR_PLAYSTART     1    //��ʼ����
#define  HISI_DVR_PLAYPAUSE     2    //��ͣ����
#define  HISI_DVR_PLAYRESTART   3    //�ָ�����
#define  HISI_DVR_PLAYSTOP      4    //ֹͣ����
#define  HISI_DVR_PLAYFAST      5    //���
#define  HISI_DVR_PLAYSLOW      6    //����
#define  HISI_DVR_PLAYNORMAL    7    //�����ٶ�
#define  HISI_DVR_PLAYSTARTAUDIO  9  //������
#define  HISI_DVR_PLAYSTOPAUDIO  10  //�ر�����
#define  HISI_DVR_PLAYGETPOS     11  //��ȡ�ļ����ؽ���

#define  HISI_PTZ_UP            0    //��
#define  HISI_PTZ_DOWN          1    //��
#define  HISI_PTZ_LEFT          2    //��
#define  HISI_PTZ_RIGHT         3    //��
#define  HISI_PTZ_AUTO          4    //�Զ�
#define  HISI_PTZ_FOCUSFAR      5    //�۽�-
#define  HISI_PTZ_FOCUSNEAR     6    //�۽�+
#define  HISI_PTZ_ZOOMIN        7    //��С
#define  HISI_PTZ_ZOOMOUT       8    //�Ŵ�
#define  HISI_PTZ_IRISOPEN      9    //��Ȧ��
#define  HISI_PTZ_IRISCLOSE    10    //��Ȧ��
#define  HISI_PTZ_AUX1         11    //��������1
#define  HISI_PTZ_AUX2         12    //��������2
#define  HISI_PTZ_CNT          13

#define  HISI_DVR_FILE_SUCCESS  1000    //��ȡ�ļ���Ϣ�ɹ�
#define  HISI_DVR_FILE_NOFIND  1001     //δ���ҵ��ļ�
#define  HISI_DVR_ISFINDING  1002       //���ڲ�����ȴ�
#define  HISI_DVR_NOMOREFILE  1003      //û�и�����ļ������ҽ���
#define  HISI_DVR_FILE_EXCEPTION  1004 //�����ļ�ʱ�쳣

typedef struct
{
	char sIP[15];           //DVR IP��ַ
    int nVideoPort;         //DVR��Ƶ�˿�
    int nHttpPort;          //DVR,http�������˿�
}HISI_DEVCONNECTINFO, *PHISI_DEVCONNECTINFO;

typedef struct
{
    BYTE sSerialNumber[SERIALNO_LEN];     //88888167,ID��
    BYTE AlarmInPortNum;                  //����������
    BYTE AlarmOutPortNum;                 //���������
    BYTE DiskNum;                         //Ӳ�̸���
    BYTE DVRType;                         //DVR�豸����
    BYTE ChanNum;                         //��Ƶ�� 
    BYTE AudioChanNum;                    //��Ƶ��
    BYTE Res[24];                         //�����ֽ�
}HISI_DEVCEINFO, *PHISI_DEVCEINFO;

typedef struct
{
    LONG Channel;                    //ͨ����,��1��ʼ
    LONG LinkMode;                   //���ӷ�ʽ
    HWND PlayWnd;                    //��Ƶ���Ŵ���
}HISI_DEV_CLIENTINFO, *PHISI_DEV_CLIENTINFO;


typedef struct
{
    char name[20];         //�豸����
    char model[20];            //�豸�ͺ�
    char hwver[15];        //Ӳ���汾
    char swver[15];        //����汾
    char reldatetime[20];  //����ʱ��
    int camcnt;          //ͨ����
    int audcnt;          //��Ƶ��
    int sensorcnt;       //����������
    int alarmcnt;        //���������
}PHISI_DEVINFO, *HISI_DEVINFO;

typedef struct
{
    int mode;            //����ģʽ
    int fmt;             //�����ʽ
    int piclv;           //ͼ������
    int bitmode;         //��������
    int bitvalue;        //��������
    int framerate;       //��Ƶ֡��
}HISI_ENCODEINFO, *PHISI_ENCODEINFO;

typedef struct
{
    int datefmt;          //���ڸ�ʽ
    int keylock;          //��������
    int keybuzzer;        //��������
    int lang;             //����
    int standard;         //��Ƶ��ʽ
    int dvrid;            //ң�������
    int hddoverwrite;     //�Զ�����
    int alpha;            //osd͸��
    int autoswi;          //�Զ���ѵ
    int autoswiinterval;  //��ѵ���
    int autoswimode;      //��ѵ��ʽ
}HISI_MISCINFO, *PHISI_MISCINFO;

typedef struct
{
    int dhcp;                 //����DHCP
    char mac[20];             //MAC��ַ
    char ip[20];              //IP��ַ
    char submask[20];         //��������
    char gateway[20];         //���ص�ַ
    char dns[20];             //DNS��ַ
    int httpport;             //WEB�˿�
    int clientport;           //�ͻ��˶˿�
    int mobileport;           //�ֻ��˿�
    DWORD enetid;             //������ID
    int ddns;                 //����DDNS
    int ddnsprovider[20];     //�ṩ��
    int ddnsurl[20];          //����
    char ddnsusr[20];         //�û���
    char ddnspwd[20];         //����
    int pppoe;                //����PPPoE
    char pppoeusr[20];        //�û���
    char pppoepwd[20];        //����
}HISI_NETWORKINFO, *PHISI_NETWORKINFO;

typedef struct
{
    char title[40];   //����
}HISI_SCREENINFO, *PHISI_SCREENINFO;

typedef struct
{
    int id;               //�豸��ַ
    int protocal;         //Э��
    int baudrate;         //������
    int databit;          //����λ
    int stopbit;          //ֹͣλ
    int parity;           //��żУ��
}HISI_PTZINFO, *PHISI_PTZINFO;

typedef struct
{
    int mode;               //����
    int alarmduration;      //������ʱ
    int alarm;              //����
    int buzzer;             //������
}HISI_SENSORINFO, *PHISI_SENSORINFO;

typedef struct
{
    int sens;               //������
    int mdalarmduration;    //�ƶ�������ʱ��
    int mdalarm;            //�ƶ�����
    int mdbuzzer;           //�ƶ�����
    int vlalarmduration;    //��Ƶ��ʧ����ʱ��
    int vlalarm;            //��ʧ����
    int vlbuzzer;           //��ʧ����
}HISI_DETECTIONINFO, *PHISI_DETECTIONINFO;

//typedef struct
//{
//} HISI_SCHEDULEINFO, *PHISI_SCHEDULEINFO;

typedef struct
{
    DWORD dwYear;          //��
    DWORD dwMonth;         //��
    DWORD dwDay;           //��
    DWORD dwHour;          //Сʱ
    DWORD dwMinute;        //��
    DWORD dwSecond;        //��
}HISI_DVR_TIME, *PHISI_DVR_TIME;

typedef enum _RecotdType_t
{
	rt_timing=0,
	rt_motion=1,
	rt_alarm=2,
	rt_manual=3,
	rt_all=4,
}HISI_DVR_RECORDTYPE;

typedef struct
{
	char sFileName[100];
	int nChannel;
    HISI_DVR_TIME struStartTime;
	HISI_DVR_TIME struStopTime;
    DWORD dwFileSize;  
}HISI_DVR_FIND_DATA, *PHISI_DVR_FIND_DATA;

//¼��ط�ʱ��֡ͷ�ṹ
typedef	enum
{
	AVENC_AUDIO = 0,
	AVENC_IDR,
	AVENC_PSLICE,
	AVENC_FRAME_TYPE_CNT,
}AVENC_FRAME_TYPE;

typedef enum
{
	REC_TYPE_NONE = 0,
	REC_TYPE_TIMER = 1,
	REC_TYPE_MOTION = 2,
	REC_TYPE_SENSOR = 4,
	REC_TYPE_MANUAL = 8,
}REC_TYPE;

#pragma pack(4)
typedef struct
{
	union
	{
		struct
		{
			unsigned int magic; //ͷ���
			int session_rnd;    //�������
			int frame_width; //�ֱ��� ��
			int frame_height; //�ֱ��� ��
			int frame_rate; //֡�� ��25fps
			int audio_sample_rate; //��Ƶ������
			char audio_format[8]; //��Ƶ��ʽ
			int audio_data_width; //��Ƶ���ݿ�� 8bit/16bit
			AVENC_FRAME_TYPE frame_type; //֡���ͣ�I/P/��Ƶ��
			int session_id; //��ID
			int channel; //ͨ����
			REC_TYPE rec_type; //¼�����ͣ����ֶ�����ʱ��
			LARGE_INTEGER frame_index; //֡�ڶ��е�����
			unsigned int nSize; //֡��С��������֡ͷ
			LARGE_INTEGER u64TSP;
			unsigned long nGenTime;
		};
		struct
		{
			unsigned int reserved[32-1];
			unsigned int magic2; //β���
		};
	};
}Frame_Head_t;
#pragma pack()

typedef struct
 {
    byte Channel[4];
 }HISI_WIRELESSMODULE;

typedef struct
{
    HISI_WIRELESSMODULE  Module[4];
}HISI_WIRELESSINFO, *PHISI_WIRELESSINFO;
  
//��ʼ��
BOOL __stdcall HISI_DVR_Init();
BOOL __stdcall HISI_DVR_Cleanup();
//ȡ�汾��Ϣ
DWORD __stdcall HISI_DVR_GetSDKVersion();
//ȡ������
DWORD __stdcall HISI_DVR_GetLastError();
//ע���쳣��Ϣ�ص�
BOOL __stdcall HISI_DVR_SetDVRMessage(void (CALLBACK* fExceptionCallBack)(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser),void *pUser);
//ͨ��ESeeID��ȡDVR��IP�Ͷ˿�
BOOL __stdcall HISI_DVR_GetConnectInfoByID(char *eSeeID, PHISI_DEVCONNECTINFO connectInfo);
//�û�ע��
LONG __stdcall HISI_DVR_Login(char *sDVRIP,WORD wDVRPort,WORD wHttpPort, char *sUserName,char *sPassword,PHISI_DEVCEINFO lpDeviceInfo);
BOOL __stdcall HISI_DVR_Logout(LONG lUserID);
//ʵʱԤ��
LONG __stdcall HISI_DVR_RealPlay(LONG lUserID,PHISI_DEV_CLIENTINFO lpClientInfo);
BOOL __stdcall HISI_DVR_StopRealPlay(LONG lRealHandle);
//��������
BOOL __stdcall HISI_DVR_OpenSound(LONG lRealHandle);
BOOL __stdcall HISI_DVR_CloseSound();
//ץͼ
BOOL __stdcall HISI_DVR_CapturePicture(LONG lRealHandle,char *sPicFileName);//bmp
BOOL __stdcall HISI_DVR_SetRealDataCallBack(LONG lRealHandle,void(CALLBACK *fRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
//ʵʱԤ����������
BOOL __stdcall HISI_DVR_SaveRealData(LONG lRealHandle,char *sFileName);
BOOL __stdcall HISI_DVR_StopSaveRealData(LONG lRealHandle);
//����
LONG __stdcall HISI_DVR_SetupAlarmChan(char *pServerIP,WORD wServerPort,char *pUserName,char *pUserPassword);
BOOL __stdcall HISI_DVR_CloseAlarmChan(LONG lAlarmHandle);
BOOL __stdcall HISI_DVR_SetDVRMessageCallBack(BOOL (CALLBACK *fMessageCallBack)(LONG lCommand,char *sDVRIP,char *pBuf,DWORD dwBufLen, DWORD dwUser), DWORD dwUser);
//��̨������ؽӿ�
BOOL __stdcall HISI_DVR_PTZControl(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwStop);
//�������� 
BOOL __stdcall HISI_DVR_GetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
BOOL __stdcall HISI_DVR_SetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize);
//¼���ļ�����
LONG HISI_DVR_FindFile(LONG lUserID,LONG lChannel,HISI_DVR_RECORDTYPE dwFileType,PHISI_DVR_TIME lpStartTime,PHISI_DVR_TIME lpStopTime);
LONG HISI_DVR_FindNextFile(LONG lFindHandle,PHISI_DVR_FIND_DATA lpFindData);
BOOL HISI_DVR_FindClose(LONG lFindHandle);
//¼��ط�
LONG __stdcall HISI_DVR_PlayBackByTime(LONG lUserID,LONG lChannel, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime, HWND hWnd);
BOOL __stdcall HISI_DVR_PlayBackControl(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *LPOutValue);
BOOL __stdcall HISI_DVR_StopPlayBack(LONG lPlayHandle);
LONG HISI_DVR_PlayBackByName(LONG lUserID,char *sPlayBackFileName,HWND hWnd);
//¼�����ݲ���
BOOL __stdcall HISI_DVR_SetPlayDataCallBack(LONG lPlayHandle,void(CALLBACK *fPlayDataCallBack) (LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
int __stdcall HISI_DVR_GetFileByTime(int lUserID, int lChannel, PHISI_DVR_TIME lpStartTime, PHISI_DVR_TIME lpStopTime, char *sSavedFileName);
LONG __stdcall HISI_DVR_GetFileByName(LONG lUserID,char *sDVRFileName,char *sSavedFileName);
BOOL __stdcall HISI_DVR_StopGetFile(int lFileHandle);
//¼������
BOOL __stdcall HISI_DVR_PlayBackSaveData(LONG lPlayHandle,char *sFileName);
BOOL __stdcall HISI_DVR_StopPlayBackSave(LONG lPlayHandle);
//¼��ط�ץͼ
BOOL __stdcall HISI_DVR_PlayBackCaptureFile(LONG lPlayHandle,char *sFileName);
//�����㲥
BOOL __stdcall HISI_DVR_ClientAudioStart();
BOOL __stdcall HISI_DVR_ClientAudioStop();
BOOL __stdcall HISI_DVR_AddDVR(LONG lUserID);
BOOL __stdcall HISI_DVR_DelDVR(LONG lUserID);
int __stdcall HISI_BroadcastStart();
int __stdcall HISI_BroadcastAddClient(
	char *pServerIP,
	WORD wServerPort,
	char *pDeviceName,
	char *pUserName,
	char *pUserPassword,
         HANDLE	*hBrdClient);
int __stdcall HISI_BroadcastDelClient(HANDLE hBrdClient);
int __stdcall HISI_BroadcastStop();
//�ļ�����
//��ʼ��
BOOL __stdcall HISI_Play_Init();
BOOL __stdcall HISI_Play_Realese();
//��������
BOOL  __stdcall HISI_Play_GetPort(LONG* nPort);
BOOL  __stdcall HISI_Play_FreePort(LONG nPort);
//�ļ�����
BOOL  __stdcall HISI_Play_OpenFile(LONG nPort,LPSTR sFileName);
BOOL  __stdcall HISI_Play_CloseFile(LONG nPort);
//���ſ���
BOOL  __stdcall HISI_Play_Play(LONG nPort, HWND hWnd);
BOOL  __stdcall HISI_Play_Stop(LONG nPort);
BOOL  __stdcall HISI_Play_Pause(LONG nPort,DWORD nPause);
BOOL  __stdcall HISI_Play_Fast(LONG nPort);
BOOL  __stdcall HISI_Play_Slow(LONG nPort);
BOOL  __stdcall HISI_Play_OneByOne(LONG nPort);
BOOL  __stdcall HISI_Play_SetPlayPos(LONG nPort,LONG nRelativePos);
LONG  __stdcall HISI_PLAY_GetPlayPos(LONG nPort);
BOOL  __stdcall HISI_Play_SetVolume(LONG nPort,WORD nVolume);
BOOL  __stdcall HISI_Play_PlaySound(LONG nPort);
BOOL  __stdcall HISI_Play_StopSound();
//������
BOOL  __stdcall HISI_Play_OpenStream(LONG nPort);
BOOL  __stdcall HISI_Play_CloseStream(LONG nPort);
BOOL  __stdcall HISI_Play_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
//��ȡ������Ϣ
DWORD  __stdcall HISI_Play_GetFileTime(LONG nPort);
DWORD  __stdcall HISI_Play_GetPlayedTime(LONG nPort);
//ץͼ
BOOL HISI_Play_CapturePicture(LONG nPort, char *sPicFileName);

#endif //