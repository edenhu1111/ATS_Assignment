#include <visa.h>
#include <ansi_c.h>
#include "edencvi.h"

//��ʱ����
void mydelay(int ms)
{
	for(int i=0;i<=ms*1000;i++)
		for(int j=0;j<110;j++);
}

//��ʼ����������
void Initialize(void)
{
	viPrintf(vi,":AUTOSCALE\n");
}
//�̿�ʾ�����������źŷ���
int GetAmplitude (double* amplitude)
{
	int result=-1;

	viOpenDefaultRM(&defaultRM);
	viOpen(defaultRM,RESOURCE,VI_NULL,VI_NULL,&vi);
	viClear(vi);
	Initialize();
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

//�̿�ʾ�����������źŷ��ֵ
int  GetPTPeak (double* VPP)
{
	int result=-1;

	viOpenDefaultRM(&defaultRM);
	viOpen(defaultRM,RESOURCE,VI_NULL,VI_NULL,&vi);
	viClear(vi);
	Initialize();
//	while(!viScanf(vi,"%lf",VPP));
	result = viPrintf(vi,":MEASURE:VPP? \n"); 
	if(result == 0)
	{
#ifdef DELAYTIME
		mydelay(DELAYTIME);
#else
		mydelay(1000);
#endif
		viScanf(vi,"%lf",VPP);
#ifndef UIR 
		printf("VPP =%f\n",*VPP);
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
//�̿�ʾ�����������ź�����
int  GetPeriod (double* Period)
{
	
	int result=-1;
//	uviPrintf(vi,"*CLS\n"); 
	viOpenDefaultRM(&defaultRM);
	viOpen(defaultRM,RESOURCE,VI_NULL,VI_NULL,&vi);
	viClear(vi);
	Initialize();
//	while(!viScanf(vi,"%lf",Period));
	result = viPrintf(vi,":MEASURE:PER?\n"); 
	if(result == 0)
	{
#ifdef DELAYTIME
		mydelay(DELAYTIME);
#else
		mydelay(1000);
#endif
		viScanf(vi,"%lf",Period);
#ifndef UIR
		printf("Period =%f\n",*Period);
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

double VPP(double* wvfm,int num)
{
	 static double max=0,min=0; //���徲̬����max min
	 max=wvfm[0];  //��ʼ��max min
	 min=wvfm[0];
	 for(int i=1;i<num;i++)
	 {
	 	if(wvfm[i]>max)
			max=wvfm[i];
		else if(wvfm[i]<min)
			min=wvfm[i];
	 }//���VPP
	 return (max-min); //return VPP
	 
}
 //notice:trigdepth should be a number between 0~99
double Period(double* wvfm,int num,double trigdepth)
{
	
}
