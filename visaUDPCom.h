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
	unsigned int selfPort;//本机对应端口
	IPAddr	PCip;  //连接对方IP
	unsigned int PCPort;//连接对方端口
	
}P2PAddress;
typedef struct
{
	IPAddr	selfip;  //本机ip
	unsigned int selfConfigPort; //本机配置端口
	unsigned int Configchannel;//配置口udp通道
	
	
	P2PAddress LXIProg;//本机连接的接控制机的编程口
	unsigned int LXIchannel;//编程口udp通道
	
	P2PAddress Sig_1;//本机信号口1			   
	unsigned int Sig_1channel;//信号口2udp通道
	
	P2PAddress Sig_2;//本机信号口2
	unsigned int Sig_2channel;//信号口2udp通道
	
	P2PAddress Sig_3;//本机信号口3
	unsigned int Sig_3channel;//信号口3udp通道
	
	P2PAddress Sig_4;//本机信号口4
	unsigned int Sig_4channel;//信号口4udp通道
	
	P2PAddress Sig_5;//本机信号口5
	unsigned int Sig_5channel;//信号口5udp通道
	
	P2PAddress Sig_6;//本机信号口6
	unsigned int Sig_6channel;//信号口6udp通道
	
	P2PAddress Sig_7;//本机信号口7
	unsigned int Sig_7channel;//信号口7udp通道
	
	P2PAddress Sig_8;//本机信号口8
	unsigned int Sig_8channel;//信号口8udp通道
	
	
	
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


int ProgWriteInfo(char *msg, ConfigInfo configinfo,int ilen);//程控口输出 
int Sig_1WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口1输出
int Sig_2WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口2输出
int Sig_3WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口3输出
int Sig_4WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口4输出
int Sig_5WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口5输出
int Sig_6WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口6输出
int Sig_7WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口7输出
int Sig_8WriteInfo(char *msg, ConfigInfo configinfo,int ilen);//信号口8输出

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
