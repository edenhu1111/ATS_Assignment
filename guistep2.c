#include <ansi_c.h>
#include "gui.h"
//#include "edencvi.h"

#define DISPDATALEN 250
#define HYSTERETIC 10 //滞回电压差
#define TRIGDEPTH  50
#define HEADLENTH  1
#define USE_DSO5012  //
#define UIR
#include <userint.h>
#include <ansi_c.h>
#include <visa.h>
#include <stdio.h>
#include "visaudpcom.h"
#include <utility.h>

static int panelHandle;

#define RESOURCE "TCPIP0::192.168.10.108::inst0::INSTR"
#define DELAYTIME 5
ViStatus   status;	  //定义状态变量
ViSession  defRM;	  //定义系统资源会话变量
ViSession  instr;	  //定义仪器会话变量


int cnt; //定义计数器变量
//char inbuf[128];  //定义输入缓冲区
//char outbuf[128]; //定义输出缓冲区
ViSession defaultRM;	//定义系统默认资源
ViSession vi;	//定义仪器会话

void Initialize(void);
int pool_handle;
int Plotting_id;
float XData[DISPDATALEN];	
int YData[DISPDATALEN + HEADLENTH];	
int refresh;
float Ts; //采样时间
double AMP;
double Freq;
int GetAmplitude(double* amplitude);
//程控示波器，测量信号周期
int  GetFreq(double* Freq);
int   CVICALLBACK MainCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int CVICALLBACK Plotting ();
void mydelay(int ms);
//double VPP(int* wvfm,int num);
//double Period(int* wvfm,int num,double TrigLevel); 
int main(int argc, char *argv[])   
{
	int hpanel;

    int i;
    if ((hpanel = LoadPanel (0, "gui.uir", PANEL)) < 0)
        return -1;
	
   	/* Display the panel and run the UI -- the menubar was attached to the   */
    /* panel already in the UIR Editor.                                      */
    DisplayPanel (hpanel);  
	InstallMainCallback (MainCallback, 0, 0); 
	CmtNewThreadPool(3,&pool_handle);
	CmtScheduleThreadPoolFunction (pool_handle, Plotting, NULL, &Plotting_id);
	RunUserInterface ();                                                        
   	/* Free resources and return */
	CmtDiscardThreadPool (pool_handle);
	DiscardPanel (hpanel);
  	return 0;
}
int   CVICALLBACK MainCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{	

    switch (event)
    {
        case EVENT_CLOSE :
            QuitUserInterface(0); 	/* 退出程序			*/                     
			break;
        case EVENT_COMMIT:
             break;
        case EVENT_IDLE:

			break;
	}
	return 0;
}



//清除波形按钮处理函数
int  CVICALLBACK ClearWaveProc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	int i;
	if(event == EVENT_COMMIT)
	{
		refresh=0;
	 	SetCtrlAttribute(PANEL, PANEL_GRAPH,ATTR_REFRESH_GRAPH,0);  //将绘图空间设置为刷新方式
		DeleteGraphPlot (PANEL, PANEL_GRAPH, -1, VAL_DELAYED_DRAW); //清屏
		i = RefreshGraph( PANEL, PANEL_GRAPH);//更新绘图控件并显示
		SetCtrlVal(PANEL,PANEL_TEXT_VPP,"VAMP:*** V");
		SetCtrlVal(PANEL,PANEL_TEXT_PERIOD,"Freq:*** KHz"); 
	}
	return 0;
}
//波形刷新按钮处理函数
int  CVICALLBACK RefreshWaveProc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	int i;
	float fvalue;
	float fstart;
	if(event == EVENT_COMMIT)
	{
	
		   refresh=1;
		   CmtScheduleThreadPoolFunction (pool_handle, Plotting, NULL, &Plotting_id);
	/*	SetCtrlAttribute(PANEL, PANEL_GRAPH,ATTR_REFRESH_GRAPH,0); //将绘图空间设置为刷新方式   
		DeleteGraphPlot (PANEL, PANEL_GRAPH, -1, VAL_DELAYED_DRAW); //清屏      
		fstart =istart*3.14/60;
		for(i=0;i<DISPDATALEN;i++)
		{
			fvalue = i;
			fvalue = fvalue/50;
			YData[i]=100+80*sin(fvalue+fstart);  //求波形样点的y坐标
			PlotPoint (PANEL, PANEL_GRAPH, XData[i],YData[i],  VAL_SMALL_SOLID_SQUARE,  VAL_RED);  //画点
		}
		i = RefreshGraph( PANEL, PANEL_GRAPH); //更新绘图控件并显示   
		istart++;
	*/	
	
	}
	  return 0;
}
/*
double VPP(int* wvfm,int num)
{
	 static double max=0,min=0; //定义静态变量max min
	 max=wvfm[0];  //初始化max min
	 min=wvfm[0];
	 for(int i=1;i<num;i++)
	 {
	 	if(wvfm[i]>max)
			max=wvfm[i];
		else if(wvfm[i]<min)
			min=wvfm[i];
	 }//求出VPP
	 return (max-min); //return VPP
	 
}
 //notice:trigdepth should be a number between 0~99
double Period(int* wvfm,int num,double TrigLevel)
{
	  char latch=0;
	  int counter_f=0;
	  int start=0,end=0;
	  for(int i =1;i<num;i++)
	  {
#ifdef   HYSTERETIC
	     if(wvfm[i]>TrigLevel+HYSTERETIC/2 && latch==0)
		 {
			 latch=1;
			 counter_f++;
			 if(counter_f==1)
				 start = i;
			 end=i;
			 
		 }
		 else if(wvfm[i]<TrigLevel-HYSTERETIC/2 && latch==1)
		 {
		 	 latch=0;
		 }
#else
	     if(wvfm[i-1]<TrigLevel+5 && wvfm[i]>TrigLevel+5 && latch==0)
		 {
			 latch=1;
			 counter_f++;
			 if(counter_f==1)
				 start = i;
			 end=i;
			 
		 }
		 else if(wvfm[i-1]>TrigLevel-5 && wvfm[i]<TrigLevel-5 && latch==1)
		 {
		 	 latch=0;
		 }
#endif
	  }
	  double period = (end-start)/Fs/counter_f;		//测周法
	  double frequency =	counter_f/Ts;			//测频法
	  if(period*period > (Ts/Fs))
		  return period;
	  else
		  return 1/frequency;
	  
}
*/
void Initialize(void)
{
	viPrintf(vi,":AUTOSCALE\n");
}

int GetAmplitude (double* amplitude)
{
	int result=-1;

	viOpenDefaultRM(&defaultRM);
	viOpen(defaultRM,RESOURCE,VI_NULL,VI_NULL,&vi);
	viClear(vi);
	//Initialize();
//	while(!uviScanf(vi,"%lf",amplitude));
	result = uviPrintf(vi,":MEASURE:VAMPLITUDE?\n"); 
	
	
	if(result == 0)
	{
#ifdef DELAYTIME
		mydelay(DELAYTIME);
#else
		mydelay(1000);
#endif
		uviScanf(vi,"%lf",amplitude);
#ifndef UIR 
		printf("amplitude =%f\n",(*amplitude));
#endif
	
	}
	else
	{
		printf("error ,time out \n");
		viClose(vi);
		viClose(defaultRM);
		return -1;
				//error timeout 
	}
	viClose(vi);
	viClose(defaultRM);
	return 0;
	

}

int  GetFreq(double* Freq)
{
	
	int result=-1;
//	uviPrintf(vi,"*CLS\n"); 
	viOpenDefaultRM(&defaultRM);
	viOpen(defaultRM,RESOURCE,VI_NULL,VI_NULL,&vi);
	viClear(vi);
	//Initialize();
//	while(!viScanf(vi,"%lf",Period));
	result = viPrintf(vi,":MEASURE:FREQ?\n"); 
	if(result == 0)
	{
#ifdef DELAYTIME
		mydelay(DELAYTIME);
#else
		mydelay(1000);
#endif
		viScanf(vi,"%lf",Freq);
#ifndef UIR
		printf("Freq =%f\n",*Freq);
#endif	
	}
	else
	{
		printf("error ,time out \n");
				//error timeout 
		viClose(vi);
		viClose(defaultRM);		
		return -1;
	}
	viClose(vi);
	viClose(defaultRM);
	return 0;
}


void mydelay(int ms)
{
	for(int i=0;i<=ms*1000;i++)
		for(int j=0;j<110;j++);
}

int CVICALLBACK Plotting ()
{
		int y=0;
		int i=0;
		int counter;
		float fvalue;
		float fstart;
//		int head[6];
		char* string2disp = malloc(40*sizeof(char));
		while(1)
		{
			if(refresh ==1)
			{
			SetCtrlAttribute(PANEL, PANEL_GRAPH,ATTR_REFRESH_GRAPH,0); //将绘图空间设置为刷新方式   
			DeleteGraphPlot (PANEL, PANEL_GRAPH, -1, VAL_DELAYED_DRAW); //清屏      
		
			viOpenDefaultRM(&defaultRM);
			viOpen(defaultRM,RESOURCE,VI_NULL,VI_NULL,&vi);
			viClear(vi);
			//uviPrintf(vi,":TIM:SCAL?\n"); 
			//uviScanf(vi,"%e",&Ts);
			Ts=2.0/100.0;
			uviPrintf(vi,":WAV:DATA?\n");
//			uviRead(vi,head,6,&counter) ; 
			uviRead(vi,YData,1000,&counter) ;
			//uviScanf(vi,"%d",YData); 
    		y=YData[0]; 


			viClose(vi);
			viClose(defaultRM);
			if(refresh ==1)
			{
			for(int j=HEADLENTH;j<DISPDATALEN+HEADLENTH;j++)
			{
				XData[j-HEADLENTH]=(j-HEADLENTH)*Ts;
				
				PlotPoint (PANEL, PANEL_GRAPH, XData[j-HEADLENTH],YData[j]*0.0000000008,  VAL_SMALL_SOLID_SQUARE,  VAL_YELLOW);
			}
				i = RefreshGraph( PANEL, PANEL_GRAPH); //更新绘图控件并显示
			 //基于demo2添加的测量+显示结果代码
			 	GetAmplitude(&AMP);
			 	GetFreq(&Freq);
				 sprintf(string2disp,"VAMP:%-7.2lf V",AMP);
				 SetCtrlVal(PANEL,PANEL_TEXT_VPP,string2disp);
				 sprintf(string2disp,"Freq:%-7.2lfKHz",Freq/1000);
				 SetCtrlVal(PANEL,PANEL_TEXT_PERIOD,string2disp);
			 }
		  }
		}
	return 0;
}
