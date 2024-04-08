#include "duoji.h" 
#include "delay.h" 

//舵机的pwm初始化在pwm.c中

u16  Steer_PWM;              //舵机控制脉宽
int  Steer_Angle;            //舵机旋转角度

void Steer_Angle_Control(u8 Which,int Steer_Angle)
{

 	Steer_PWM =Steer_Angle*80/9+1200;
	switch(Which)
	{
		case 1:TIM_SetCompare1(TIM9,Steer_PWM);
					 break;
		case 2:TIM_SetCompare2(TIM9,Steer_PWM);
					 break;
		default:break;
	}	
}




