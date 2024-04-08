#include "Track.h"
#include "oled.h"
#include "led.h"
#include "steer.h"
#include "key.h"
#include "openmv.h"
#include "Usart.h"

PIDX_Stru PIDX;
PIDX_Stru PIDY;
 int angle_X;
 int angle_Y;
void Track_Init(void)
{
	
	STEER_Init();
	Usart_init();
	Uart_A3_Init();
	OLED_Clear();
}



void PID_Init(void)
{
	PIDX.Kp=0.03;//0.244.0.063
	PIDX.Kd=0;
	PIDX.Ki=0;
	PIDX.err=0;
	PIDX.err_last=0;
	PIDX.integral=0;
	PIDX.increase=0; 
	
	PIDY.Kp=0.03;//0.06
	PIDY.Kd=0;
	PIDY.Ki=0;
	PIDY.err=0;
	PIDY.err_last=0;
	PIDY.integral=0;
	PIDY.increase=0; 
}


void PIDX_set(void)
{	
   PIDX.err=middle_x-pos_x;  //位于中心点左边是正，位于中心点右边是负
   PIDX.integral+=PIDX.err;
	 PIDX.increase=PIDX.Kp*PIDX.err+PIDX.Ki*PIDX.integral+PIDX.Kd*(PIDX.err-PIDX.err_last);//位置型PID算法
   PIDX.err_last=PIDX.err;
	 angle_X=angle_X+PIDX.increase;
	 if(angle_X<X_max_right) angle_X=X_max_right;
	 else if(angle_X>X_max_left) angle_X=X_max_left;
}

void PIDY_set(void)
{	
   PIDY.err=middle_y-pos_y;  //位于中心点上边是负，位于中心点下边是正
   PIDY.integral+=PIDY.err;
	 PIDY.increase=PIDY.Kp*PIDY.err+PIDY.Ki*PIDY.integral+PIDY.Kd*(PIDY.err-PIDY.err_last);//位置型PID算法
   PIDY.err_last=PIDY.err;
	 angle_Y=angle_Y+PIDY.increase;
	 if(angle_Y<Y_max_up) angle_Y=Y_max_up;
	 else if(angle_Y>Y_max_down) angle_Y=Y_max_down;
}

//舵机向左移动是正，向上移动是负
void Track_Realize(void)
{
	u8 key;
	float Xp_change=0.001;
	float Xd_change=0.001;
	float Yp_change=0.001;
	float Yd_change=0.001;
	OLED_Clear();
	Track_Init();
	PID_Init();
	PIDX_set();
	
	while(1)
	{
		key=KEY_Scan(0);
		switch (key)
	{
		case KEY1_PRES: PIDY.Kp=PIDY.Kp+Yp_change; break;
		case KEY2_PRES: PIDY.Kp=PIDY.Kp-Yp_change; break;
		case KEY3_PRES: PIDX.Kp=PIDX.Kp+Xp_change; break;
		case KEY4_PRES: PIDX.Kp=PIDX.Kp-Xp_change; break;
	}
		OLED_ShowNum(0,0,pos_y,3,12);	
	  OLED_Show3FNum(16,16,PIDY.Kp,1,3,12);
	  OLED_Show3FNum(16,32,PIDX.Kp,1,3,12);
	  OLED_Refresh_Gram();
//  	OLED_Show3FNum(80,16,PIDX.Kd,1,3,12);
//	  OLED_Show3FNum(16,32,Xp_change,2,3,12);
//  	OLED_Show3FNum(80,32,Xd_change,2,3,12);
	  if(flag_ov==1)
		{
			PIDX_set();
			PIDY_set();
			flag_ov=0;
		}
		Steer_Angle_Control(1, angle_X);
    Steer_Angle_Control(2, angle_Y);
	}
}

