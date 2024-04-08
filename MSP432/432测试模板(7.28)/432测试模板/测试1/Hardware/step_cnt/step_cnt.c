/*
******************************************************************************
*Filename      :step_cnt.c
*Programmer(s) :Lab416
*Description   :2020省赛 步进电机驱动
******************************************************************************
*/
#include "step_cnt.h"
#include "math.h"
/**********************  readme  ****************************
需要定义并使用的全局变量
int step_cnt;               
int step_speed=0;
int step_pulse=0;
int step_dir=0;
double now_angle=0;      //记录现在的角度
double step_angle=0;

在定时器中断服务函数中加入以下代码，以定时器2为例：
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
	MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_0);//清标志位
}


初始化：
调用step_Init()；并初始化上述代码所使用的定时器


控制接口：
Step_Control(float angle,u16 speed)	//angle->目标角度，speed->速度（时间间隔，越小转的越快）


*************************************************************/

int step_cnt;               
int step_speed=0;
int step_pulse=0;
int step_dir=0;
double now_angle=0;      //记录现在的角度
double step_angle=0;
/*
********************************************************************************************************************
*                  void step_Init(void)
*
*Description : 步进控制角初始化
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
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN0);//LED1初始化
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN1);//LED1初始化
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN4);//LED1初始化
	GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN5);//LED1初始化
	
	dir1=0;//全部初始置低
	pulse1=0;
	dir2=0;
	pulse2=0;
}

void Step_Control(float angle,u16 speed)                 	//目标角度，速度（时间间隔，越小越快）
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




