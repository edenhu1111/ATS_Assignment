//程控示波器初始化
void Initialize(void);
//程控示波器，测量信号幅度
int GetAmplitude(double* amplitude);
//程控示波器，测量信号峰峰值
int  GetPTPeak(double* VPP);
//程控示波器，测量信号周期
int  GetPeriod(double* Period);
//延时函数，保证不会串数据
void mydelay(int ms);
double VPP(double* wvfm,int num);
double Period(double* wvfm,int num,double trigdepth); 
