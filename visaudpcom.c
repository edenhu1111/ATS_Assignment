
#include <cvirte.h>	
#include <udpsupp.h>
#include <ansi_c.h>
#include <userint.h> 
#include "windows.h" 
#include "winsock2.h"
#include "toolbox.h" 
#include "visaUDPCom.h" 
//#include "Pulse Parameter Test.h"
//#define debug
#define BUFFERLEN	1100
unsigned char writedata[BUFFERLEN];
unsigned char recievedata[BUFFERLEN];
static recievedatalen = 0;
int recieveflag; //标志是否需要接受数据
int recieveinfo;//recieveinfo:0 ok, 1超时

 ConfigInfo SelfComAddress; 
extern  int panelHandle;    
//-----------------------------------------------------------------------------
// UDP callback function                                                
//-----------------------------------------------------------------------------
/// HIFN This function is called when data arrives on the UDP channel. It is up
/// HIFN  to this function to read the waiting data.
/// HIPAR channel/The channel that has waiting data.
/// HIPAR eventType/The type of UDP event. UDP_DATAREADY is the only event type.
/// HIPAR errCode/Non-zero indicates an error that occurred with the event.
/// HIPAR callbackData/Callback data (if any) that was assigned on the channel.
 int ConfigIni(unsigned int port)
 {
	 int				error = 0; 
	 strcpy(SelfComAddress.selfip,"127.0.0.1");
	 SelfComAddress.selfConfigPort=port;
	 errChk (CreateUDPChannelConfig(SelfComAddress.selfConfigPort, UDP_ANY_ADDRESS, 0, UDPCallbackFromConfig, NULL, &SelfComAddress.Configchannel)); 
	    
	Error:															   
//	if (error < 0)
	
	
		return 0;

 }
//配置口输入响应，完成其他口的配置,建立本机的配置信息SelfComAddress，
//并创建编程口，输入口，输入出口的通信通道，并为编程口和输入口设置回掉函数
int CVICALLBACK UDPCallbackFromConfig (unsigned channel, int eventType, int errCode, void *callbackData)
{

	return 0;

}
//可编程接口的输入响应，
int CVICALLBACK UDPCallbackFromProg (unsigned channel, int eventType, int errCode, void *callbackData)
{
	int	error = 0;
	int size;
	unsigned char * recievedatalxi;
	
	if (eventType == UDP_DATAREADY)
	{
		char			srcAddr[16];
		unsigned int	srcPort;

		
		// Pass NULL as the input buffer to determine the size of the arrived data.
		errChk (size = UDPRead(channel, NULL, 0, UDP_DO_NOT_WAIT, NULL, NULL));
		
		nullChk (recievedatalxi = malloc(size+1));
		
		// Read the waiting message into the allocated buffer.
		errChk (size = UDPRead(channel, recievedatalxi, size, UDP_DO_NOT_WAIT, &srcPort, srcAddr));
		recievedatalxi[size]='\0';
		#ifdef debug
		errChk (SetCtrlVal(panelHandle, PANEL_TEXTBOX, recievedatalxi));
		#endif
		strcpy(writedata,recievedatalxi);
		
		SetEvent(getdataevent);  
	
	}
	Error:															   
	if (error < 0)
		MessagePopup("Error", GetGeneralErrorString(error));
	if(recievedatalxi)
		free(recievedatalxi);   
	return  0;
/*	int				error = 0,
					size;
//	unsigned char	*msg = NULL;
	int icode;
	if (eventType == UDP_DATAREADY)
	{
		char			srcAddr[16];
		unsigned int	srcPort;

		
		// Pass NULL as the input buffer to determine the size of the arrived data.
		errChk (size = UDPRead(channel, NULL, 0, UDP_DO_NOT_WAIT, NULL, NULL));
		
		nullChk (scpimsg = malloc(size+1));
		
		// Read the waiting message into the allocated buffer.
		errChk (size = UDPRead(channel, scpimsg, size, UDP_DO_NOT_WAIT, &srcPort, srcAddr));
		scpimsg[size]='\0';
		#ifdef debug
		errChk (SetCtrlVal(panelHandle, PANEL_TEXTBOX, scpimsg));
		#endif
		IbWriteBuf(scpimsg, size );
		ParserProc();
//		getscpi();
	}
	Error:															   
	if (error < 0)
		MessagePopup("Error", GetGeneralErrorString(error));;
	if (scpimsg)
		free(scpimsg);	   */
	return 0;
	
}

//信号口1输入响应，
int CVICALLBACK UDPCallbackFromSig_1 (unsigned channel, int eventType, int errCode, void *callbackData)
{
	int				error = 0,
					size;

	char strtimes[10];
	static int i=0;
	
	if (eventType == UDP_DATAREADY)
	{
		
		
	}
	Error:															   
/*	if (error < 0)
		MessagePopup("Error", GetGeneralErrorString(error));;
	if (msg)
		free(msg); */
	return 0;
}

int CVICALLBACK UDPCallbackFromSig_2(unsigned channel, int eventType, int errCode, void *callbackData)
{
}
int CVICALLBACK UDPCallbackFromSig_3(unsigned channel, int eventType, int errCode, void *callbackData)
{
}
int CVICALLBACK UDPCallbackFromSig_4(unsigned channel, int eventType, int errCode, void *callbackData)
{
}
int CVICALLBACK UDPCallbackFromSig_5(unsigned channel, int eventType, int errCode, void *callbackData)
{
}
int CVICALLBACK UDPCallbackFromSig_6(unsigned channel, int eventType, int errCode, void *callbackData)
{
}
int CVICALLBACK UDPCallbackFromSig_7(unsigned channel, int eventType, int errCode, void *callbackData)
{
}
int CVICALLBACK UDPCallbackFromSig_8(unsigned channel, int eventType, int errCode, void *callbackData)
{
}
//程控口输出
int ProgWriteInfo(char *msg, ConfigInfo configinfo,int ilen)//程控口输出
{
	 UDPWrite(configinfo.LXIchannel, configinfo.LXIProg.PCPort, configinfo.LXIProg.PCip, msg, ilen);  
	 return 0;
	
}
//信号输出口输出

int Sig_1WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_1channel, configinfo.Sig_1.PCPort, configinfo.Sig_1.PCip, msg, ilen);     
	
}
int Sig_2WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_2channel, configinfo.Sig_2.PCPort, configinfo.Sig_2.PCip, msg, ilen);  
	
}
int Sig_3WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_3channel, configinfo.Sig_3.PCPort, configinfo.Sig_3.PCip, msg, ilen);   
	
}
int Sig_4WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_4channel, configinfo.Sig_4.PCPort, configinfo.Sig_4.PCip, msg, ilen);  
	
}
int Sig_5WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_5channel, configinfo.Sig_5.PCPort, configinfo.Sig_5.PCip, msg, ilen);   
	
}
int Sig_6WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_6channel, configinfo.Sig_6.PCPort, configinfo.Sig_6.PCip, msg, ilen);   
	
}
int Sig_7WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_7channel, configinfo.Sig_7.PCPort, configinfo.Sig_7.PCip, msg, ilen);  
	
}
int Sig_8WriteInfo(char *msg, ConfigInfo configinfo,int ilen)//信号口输出
{
	 UDPWrite(configinfo.Sig_8channel, configinfo.Sig_8.PCPort, configinfo.Sig_8.PCip, msg,ilen);  
	
}
 ///////////////////////////////////////////////////////////////
int uviOpenDefaultRM (int * Rsrc_Manager_Handle)
{
	 //*Rsrc_Manager_Handle = 1;
	 //ConfigIni(CONFIGPORT);
	static int istart = 0;
	int id =1;
	void *ptr=NULL; 
	if(istart ==0)
	{
	getdataevent =CreateEvent(NULL,FALSE,FALSE,NULL);
	senddataevent =CreateEvent(NULL,FALSE,FALSE,NULL);
	senddataoverevent =CreateEvent(NULL,FALSE,FALSE,NULL); 
	
	 threadgetdataHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadGetDataProc, ptr,0,&id);   // 创建接收数据线程		
	 istart = 1;
	}
	 return 0;
}
int uviOpen(int Rsrc_Manager_Handle,char * Instrument_Descriptor,int Access_Mode,int Open_Timeout,int * Instrument_Handle)
{
	int				error = 0;     
	uvisarespflag = 0;

 
	
/*	SelfComAddress.LXIProg.selfPort = LOCALLXIPORT;
	SelfComAddress.LXIProg.PCPort = REMOTELXIPORT;  
	strcpy(SelfComAddress.LXIProg.PCip,"127.0.0.1");
	errChk(CreateUDPChannel(SelfComAddress.LXIProg.selfPort,&SelfComAddress.LXIchannel));//程控口是双向口    
	Error:															   
//	if (error < 0)
	
*/
		return 0;

}
int uviPrintf(int Instrument_Handle,char*  Write_Format_String,...)
{
	int ilen;
	char *p;
    TypeVLxiFlag writeflag;
    writeflag.flag = 0;
	writeflag.bits.write = 1;
	memset(writedata,0, BUFFERLEN);
	p = strstr(Write_Format_String,"?");
	/*if(p==NULL)				 //recieveflag标记是否需要读数据
	{
		recieveflag = 0;   //通知线程不接收数据
	}
	else
	{
		//recieveflag	 = 1;
		recieveflag	 = 0;
	}*/
	recieveflag	 = 0; 
	
	 writedata[0] = writeflag.flag;
	strcpy(&writedata[1], Write_Format_String);
	recievedatalen = 0;
	SetEvent(senddataevent);
	 Sleep(100);
	 WaitForSingleObject(senddataoverevent,50);  
	 ResetEvent(senddataoverevent); 
	//可变参数处理
	 /*va_list argp;
	 int argno = 0;
	 int i;
	 char *para;
	 va_start(argp,msg);
	 while(1)
	 {
		 i = va_arg(argp,int );
		 if(strcmp(para,"/0")==0)  break;
		 printf("parameter #%d is :%s/n",argno,para);
		 argno++;
	 }
	 va_end(argp);
	*/
//	ilen =strlen(Write_Format_String);  
//	ProgWriteInfo( Write_Format_String, SelfComAddress,ilen);//程控口输出
	

//	Delay(2);          
	return 0;
}
//0 ok; -1 timeout
int uviScanf(int Instrument_Handle,char * Read_Format_String,...)   
{
	int line; 
	int len;
	len= strlen( writedata);
	memset(writedata,0,len);
	TypeVLxiFlag writeflag;
	writeflag.flag = 0;
	writeflag.bits.read = 1;
	writedata[0] = writeflag.flag;
	strcat(&writedata[1],"\n"); 
	recieveflag = 1;        
	recievedatalen = 0;
	SetEvent(senddataevent);
	Sleep(100);
	
	WaitForSingleObject(getdataevent,50);  
	ResetEvent(getdataevent);
	if(recieveinfo == 1)//超时
	{
		return -1;
	}
	else
	{
		      
		  //InsertTextBoxLine (panelHandle, PANEL_TEXTBOX, -1, recievedata);
		  //GetNumTextBoxLines(panelHandle,PANEL_TEXTBOX,&line);
		 //if(line>8) SetCtrlAttribute(panelHandle,PANEL_TEXTBOX,ATTR_FIRST_VISIBLE_LINE,line-8);
	}
//	strcpy(c,recievedata);
	 //可变参数处理
	 int i;
	 int ioffset;
	 va_list argp;
	 int argno = 0;
	 float * pfvalue;
	 float fvalue;
	 double * pdvalue;
	 char *p;
	 int *pdatalen;
	 unsigned char  *pstr;
	 char headstr[256];
	 int itype;
	 p = strstr(Read_Format_String,"%s");
	 if(p!= NULL)
	 {
		 itype = 1;
	 }
	 else if(strstr(Read_Format_String,"%lf")!=NULL)
	 {
		 itype = 2;
	 }
	 else if(strstr(Read_Format_String,"%f")!=NULL)
	 {
		 itype = 3;
	 }
	  else if(strstr(Read_Format_String,"%#b")!=NULL)
	 {
		 itype = 4;
	 }
	 
	 else 
	 {
		 itype  =5;
	 }
	
	 va_start(argp,Read_Format_String);
	 do
	 {
		 switch(itype)
		 {
			 case 1:
				 p = va_arg(argp,char * );
				 strcpy(p,recievedata);
				 break;
			 case 2:
				 pdvalue = va_arg(argp, double *) ;
				fvalue = atof(recievedata);		   
				 *pdvalue =(double)fvalue;
				 break;
			 case 3:
				 pfvalue = va_arg(argp,float * );
				  *pfvalue = atof(recievedata);    
				 break;
			case 4:
				
				 pdatalen = va_arg(argp,int * );
				 pstr = va_arg(argp,unsigned char  * );
			
				 if(recievedata[0]=='#')
				 {
					 ioffset = recievedata[1]-'0';
					 for(i=0;i<ioffset;i++)
					 {
						 headstr[i]=recievedata[i+2];
					 }
					 headstr[i]='\0';
					 *pdatalen = atoi(headstr);
					 ioffset = *pdatalen;
					memcpy(pstr, &recievedata[i+2],ioffset);             
					 
				 }
				 break;
				 
			 case 5:
				 pstr = va_arg(argp,void * );  
				 memcpy(pstr, recievedata,recievedatalen);
				 break;
			 
		 }
		 
		 argno++;
	 }while(0);
	 va_end(argp);
	 
	

	return 0;
}
 DWORD WINAPI   ThreadGetDataProc(PVOID pParam)
 {
	 SOCKET socket1;
	int i;
	DWORD dw;
	InitWinsock();
	struct sockaddr_in local;
	struct sockaddr_in from;
	int fromlen =sizeof(from);
	local.sin_family=AF_INET;
	local.sin_port=htons(LOCALLXIPORT);             ///监听端口
	local.sin_addr.s_addr=inet_addr("127.0.0.1");       ///本机
	
	from.sin_family=AF_INET;
	from.sin_port=htons(REMOTELXIPORT);             ///监听端口
	from.sin_addr.s_addr=inet_addr("127.0.0.1");       ///本机
	
	

	socket1=socket(AF_INET,SOCK_DGRAM,0);//1创建socket
	// 设置超时
    struct timeval timeout;
    timeout.tv_sec = 1;//秒
    timeout.tv_usec = 0;//微秒
    if (setsockopt(socket1, SOL_SOCKET, SO_RCVTIMEO,(const char *)&timeout, sizeof(timeout)) == -1) 
	{
        printf("setsockopt failed:");
    }

	bind(socket1,(struct sockaddr*)&local,sizeof local);//绑定

	while (1)//数据收发
	{
		WaitForSingleObject(senddataevent,INFINITE);
		ResetEvent(senddataevent);
		sendto(socket1,writedata,sizeof writedata,0,(struct sockaddr*)&from,fromlen);
		
		SetEvent(senddataoverevent);   
		
		i =0;  
		while(recieveflag==1)   //recieveflag = 0 则不读取数据
		{
		
			 Sleep(100);  
			if((recievedatalen=recvfrom(socket1,recievedata,sizeof recievedata,0,(struct sockaddr*)&from,&fromlen))!=SOCKET_ERROR)
			{
				
		
				recievedata[recievedatalen]='\0';
				SetEvent(getdataevent);
				recieveflag = 0;
				recieveinfo = 0;
		
			
			}
			else
			{
				i++;
				if(i==3)
				{
					recieveinfo = 1;//超时
					recieveflag = 0;         
					SetEvent(getdataevent);   
					break;
				}
			}
		}
		
		
		
	/*	char buffer[1024]="\0";
	//	printf("waiting for message from others-------------\n");
		if (recvfrom(socket1,buffer,sizeof buffer,0,(struct sockaddr*)&from,&fromlen)!=SOCKET_ERROR)
		{
			printf("Received datagram from %s--%s\n",inet_ntoa(from.sin_addr),buffer);
			////给cilent发信息
			sendto(socket1,buffer,sizeof buffer,0,(struct sockaddr*)&from,fromlen);

		}
		//Sleep(500);*/
	}

	closesocket(socket1);
	

 }
BOOL InitWinsock()
{
	int Error;
	WORD VersionRequested;
	WSADATA WsaData;
	VersionRequested=MAKEWORD(2,2);
	Error=WSAStartup(VersionRequested,&WsaData); //启动WinSock2
	if(Error!=0)
	{
		return FALSE;
	}
	else
	{
		if(LOBYTE(WsaData.wVersion)!=2||HIBYTE(WsaData.wHighVersion)!=2)
		{
			WSACleanup();
			return FALSE;
		}
		
	}
	return TRUE;
}
  //0 ok, -1 timeout
int uviQueryf (int Instrument_Handle,char * Write_Format_String,char * Read_Format_String, ...)
{
	int i;
	i = uviPrintf(Instrument_Handle,Write_Format_String);
	
	 va_list argp;
	 int argno = 0;
	 float * pfvalue;
	 double * pdvalue;
	 char *p;
	 void *pstr;
	 int itype;
	 p = strstr(Read_Format_String,"%s");
	 if(p!= NULL)
	 {
		 itype = 1;
	 }
	 else if(strstr(Read_Format_String,"%lf")!=NULL)
	 {
		 itype = 2;
	 }
	 else if(strstr(Read_Format_String,"%f")!=NULL)
	 {
		 itype = 3;
	 }
	 else
	 {
		 itype =4;
	 }
	 
	
	 va_start(argp,Read_Format_String);
	 do
	 {
		
				 
		
		 switch(itype)
		 {
			 case 1:
				 p = va_arg(argp,char * );
				 
				 i = uviScanf(Instrument_Handle,Read_Format_String,p); 
				 
				 break;
			 case 2:
				 pdvalue = va_arg(argp, double *) ;
				i = uviScanf(Instrument_Handle,Read_Format_String,pdvalue); 						   
				
				  break;
			 case 3:
				 pfvalue = va_arg(argp,float * );
				 i = uviScanf(Instrument_Handle,Read_Format_String,pfvalue); 
				
				 break;
			 case 4:
				pstr  = va_arg(argp,void * ); 
				 i = uviScanf(Instrument_Handle,Read_Format_String,pstr);    
				 break;
			 
		 }
	
		 
		 argno++;
	 }while(0);
	 va_end(argp);
	 
	
	
	return i;
	
}

int uviWrite (int Instrument_Handle, char * Buffer,int Count, int * Return_Count)
{
	int ilen;
 	TypeVLxiFlag writeflag;
    writeflag.flag = 0;
	writeflag.bits.write = 1;
	
	recievedatalen = 0;       
	memset(writedata,0, BUFFERLEN);
	writedata[0] = writeflag.flag;
	
	Buffer[Count]='/0';
	strcpy(&writedata[0], Buffer);
	
	recieveflag = 0;        
	recievedatalen = 0;
	
	SetEvent(senddataevent);
	*Return_Count = Count;
	WaitForSingleObject(getdataevent,50);  
	
}

 int uviRead (int Instrument_Handle,unsigned char Buffer[], int Count,int * Return_Count)
 {
	static  int iremainlen=0;
	static int icurpos = 0;
	int istart;
	int ilen;
	
	TypeVLxiFlag writeflag;
	writeflag.flag = 0;
	writeflag.bits.read = 1;
	writedata[0] = writeflag.flag;
	strcat(&writedata[1],"\n"); 
	recieveflag = 1;        
	recievedatalen = 0;
	SetEvent(senddataevent);         
	
	WaitForSingleObject(getdataevent,INFINITE);  
	ResetEvent(getdataevent);
	if(recievedatalen !=0)
	{
		iremainlen = recievedatalen ;
		if(iremainlen<=Count)
		{
			for(int i=0;i<iremainlen;i++)
			{
				Buffer[i]= recievedata[i];
				
			}
			recievedatalen =0;
			iremainlen = 0;
			icurpos = 0;
			*Return_Count = recievedatalen;
			
		}
		else
		{
			icurpos = Count;
			iremainlen = recievedatalen-Count;
			for(int i = 0;i<Count;i++)
			{
				Buffer[i]= recievedata[i];  
			}
			* Return_Count= Count;	
		}
	}
	else
	{
		if(iremainlen <Count)
		{
			istart = icurpos;
			ilen = iremainlen;
			 * Return_Count = iremainlen;
			 icurpos = 0;
			 iremainlen = 0;
			
		}
		else
		{
			istart = icurpos;
			ilen = Count;
			 * Return_Count = Count;
			 icurpos += Count;
			iremainlen = iremainlen - Count;
			
			
		}
		
		for(int i = istart; i<ilen;i++)
		{
			Buffer[i]= recievedata[i];               
		}
		
		
	}
	 return 0;
//	strcpy(c,recievedata);
	 
 }
int uviClose (int * Rsrc_Manager_Handle)
{
	return 0;
}


int  uviClear (int Instrument_Handle)
{
	return 0;
}
