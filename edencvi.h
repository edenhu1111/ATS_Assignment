//�̿�ʾ������ʼ��
void Initialize(void);
//�̿�ʾ�����������źŷ���
int GetAmplitude(double* amplitude);
//�̿�ʾ�����������źŷ��ֵ
int  GetPTPeak(double* VPP);
//�̿�ʾ�����������ź�����
int  GetPeriod(double* Period);
//��ʱ��������֤���ᴮ����
void mydelay(int ms);
double VPP(double* wvfm,int num);
double Period(double* wvfm,int num,double trigdepth); 
