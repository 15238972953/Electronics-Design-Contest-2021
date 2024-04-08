/*
******************************************************************************
*Filename      :step_cnt.c
*Programmer(s) :Lab416
*Description   :2020ʡ�� �����������
******************************************************************************
*/
#include "step_cnt.h"
#include "math.h"
/**********************  readme  ****************************
��Ҫ���岢ʹ�õ�ȫ�ֱ���
int step_cnt;               
int step_speed=0;
int step_pulse=0;
int step_dir=0;
double now_angle=0;      //��¼���ڵĽǶ�
double step_angle=0;

�ڶ�ʱ���жϷ������м������´��룬�Զ�ʱ��2Ϊ����
void TA2_0_IRQHandler(void)
{
	static int flag_step=0;
	step_dir>0	?	(dir1=1) : (dir1=0);		
	flag_step++;

	if(flag_step>=step_speed)
	{
		if(step_pulse!=0)
		{
			step_pulse--;
			pulse1=!pulse1;
			if(pulse1==1)
				now_angle+=(step_dir*0.1125);
		}
		flag_step=0;
	}
	MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_0);//���־λ
}


��ʼ����
����step_Init()������ʼ������������ʹ�õĶ�ʱ��


���ƽӿڣ�
Step_Control(float angle,u16 speed)	//angle->Ŀ��Ƕȣ�speed->�ٶȣ�ʱ������ԽСת��Խ�죩


*************************************************************/

int step_cnt;               
int step_speed=0;
int step_pulse=0;
int step_dir=0;
double now_angle=0;      //��¼���ڵĽǶ�
double step_angle=0;
/*
********************************************************************************************************************
*                  void step_Init(void)
*
*Description : �������ƽǳ�ʼ��
*Arguments   : none
*Returns     : none
*Notes       :dir1 		P10.0
              dir2 		P10.1
              pulse1 	P10.4    	T3C0
              pulse2 	P10.5			T3C1

********************************************************************************************************************
*/
void Step_Init(void)
{    	 
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN0);//LED1��ʼ��
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN1);//LED1��ʼ��
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN4);//LED1��ʼ��
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN5);//LED1��ʼ��
	
	dir1=0;//ȫ����ʼ�õ�
	pulse1=0;
	dir2=0;
	pulse2=0;
}

void Step_Control(float angle,u16 speed)                 	//Ŀ��Ƕȣ��ٶȣ�ʱ������ԽСԽ�죩
{
	float angle_err;
	Interrupt_disableInterrupt(INT_TA3_0);
	step_speed=speed;
	angle_err=angle-now_angle;
	step_pulse=2*(fabs(angle_err/0.1125f));
	pulse1=0;
	angle_err<0	?	(step_dir=-1) : (step_dir=1);
	Interrupt_enableInterrupt(INT_TA3_0); 
}




