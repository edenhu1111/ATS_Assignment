#ifndef UDP_COM_H
#define UDP_COM_H
#include <winsock2.h>
#define CONFIGPORT				58010  	// arbitrarily chosen from the Dynamic/Private port range (49152-65535)
#define LOCALLXIPORT			58011
#define REMOTELXIPORT			58021
#define MULTICAST_ADDRESS	"228.0.1.1"	// arbitrarily selected from the multicast address range (224.0.0.0-239.255.255.255)

#define MAX_IP4_STRING_LENGTH		15

typedef unsigned char IPAddr[MAX_IP4_STRING_LENGTH + 1];
typedef union
{
  unsigned char flag;
  struct bs
  {
     char end :1;
     char write:1;
     char read:1;
     char x:5;
  }bits;
}TypeVLxiFlag;
typedef struct
{
	unsigned int selfPort;//������Ӧ�˿�
	IPAddr	PCip;  //���ӶԷ�IP
	unsigned int PCPort;//���ӶԷ��˿�
	
}P2PAddress;
typedef struct
{
	IPAddr	selfip;  //����ip
	unsigned int selfConfigPort; //�������ö˿�
	unsigned int Configchannel;//���ÿ�udpͨ��
	
	
	P2PAddress LXIProg;//�������ӵĽӿ��ƻ��ı�̿�
	unsigned int LXIchannel;//��̿�udpͨ��
	
	P2PAddress Sig_1;//�����źſ�1			   
	unsigned int Sig_1channel;//�źſ�2udpͨ��
	
	P2PAddress Sig_2;//�����źſ�2
	unsigned int Sig_2channel;//�źſ�2udpͨ��
	
	P2PAddress Sig_3;//�����źſ�3
	unsigned int Sig_3channel;//�źſ�3udpͨ��
	
	P2PAddress Sig_4;//�����źſ�4
	unsigned int Sig_4channel;//�źſ�4udpͨ��
	
	P2PAddress Sig_5;//�����źſ�5
	unsigned int Sig_5channel;//�źſ�5udpͨ��
	
	P2PAddress Sig_6;//�����źſ�6
	unsigned int Sig_6channel;//�źſ�6udpͨ��
	
	P2PAddress Sig_7;//�����źſ�7
	unsigned int Sig_7channel;//�źſ�7udpͨ��
	
	P2PAddress Sig_8;//�����źſ�8
	unsigned int Sig_8channel;//�źſ�8udpͨ��
	
	
	
}ConfigInfo;

int ConfigIni(unsigned int port);
int CVICALLBACK UDPCallbackFromConfig (unsigned channel, int eventType, int errCode, void *callbackData);   
int CVICALLBACK UDPCallbackFromProg(unsigned channel, int eventType, int errCode, void *callbackData);
int CVICALLBACK UDPCallbackFromSig_1(unsigned channel, int eventType, int errCode, void *callbackData);
int CVICALLBACK UDPCallbackFromSig_2(unsigned channel, int eventType, int errCode, void *callbackData);    
int CVICALLBACK UDPCallbackFromSig_3(unsigned channel, int eventType, int errCode, void *callbackData);    
int CVICALLBACK UDPCallbackFromSig_4(unsigned channel, int eventType, int errCode, void *callbackData);    
int CVICALLBACK UDPCallbackFromSig_5(unsigned channel, int eventType, int errCode, void *callbackData);    
int CVICALLBACK UDPCallbackFromSig_6(unsigned channel, int eventType, int errCode, void *callbackData);    
int CVICALLBACK UDPCallbackFromSig_7(unsigned channel, int eventType, int errCode, void *callbackData);
int CVICALLBACK UDPCallbackFromSig_8(unsigned channel, int eventType, int errCode, void *callbackData);    


int ProgWriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�̿ؿ���� 
int Sig_1WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�1���
int Sig_2WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�2���
int Sig_3WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�3���
int Sig_4WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�4���
int Sig_5WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�5���
int Sig_6WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�6���
int Sig_7WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�7���
int Sig_8WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//�źſ�8���

int uvisarespflag;//visa poll token
HANDLE senddataevent;
HANDLE senddataoverevent;

HANDLE getdataevent;  

HANDLE threadgetdataHandle;   
BOOL InitWinsock();
DWORD WINAPI   ThreadGetDataProc(PVOID pParam);
#define  viOpenDefaultRM  uviOpenDefaultRM   
int uviOpenDefaultRM (int * Rsrc_Manager_Handle);
#define viOpen uviOpen
int uviOpen(int Rsrc_Manager_Handle,char * Instrument_Descriptor,int Access_Mode,int Open_Timeout,int * Instrument_Handle);
#define viPrintf uviPrintf
int uviPrintf(int Instrument_Handle,char*  Write_Format_String,...);
#define viScanf uviScanf 
int uviScanf(int Instrument_Handle,char * Read_Format_String,...);
#define viQueryf  uviQueryf
int uviQueryf (int Instrument_Handle,char * Write_Format_String,char * Read_Format_String, ...);
#define viWrite  uviWrite
int uviWrite (int Instrument_Handle, char * Buffer,int Count, int * Return_Count);
#define viRead  uviRead
 int uviRead (int Instrument_Handle,unsigned char Buffer[], int Count,int * Return_Count);

#define  viClose uviClose   
int uviClose (int * Rsrc_Manager_Handle);

#define  viClear  uviClear   
int  uviClear (int Instrument_Handle);
#endif
