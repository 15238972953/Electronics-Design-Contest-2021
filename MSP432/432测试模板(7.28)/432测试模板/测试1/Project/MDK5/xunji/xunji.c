#include "xunji.h"
#include "oled.h"
#include "key.h"
#include "motor.h"
#include "led.h"
#include "mpu6050.h"
#include "timer.h"
#include "delay.h"
#include "inv_mpu.h"

 PID_Stru PID_MPU;

int Speed_A=0;
int Speed_B=0;
int Speed_C=0;
int Speed_D=0;

	void MPUPID_Init(void)
{
	PID_MPU.Kp=50;
	PID_MPU.Kd=0;
	PID_MPU.Ki=1;
	PID_MPU.set_angel=0;
	PID_MPU.err=0;
	PID_MPU.err_last=0;
	PID_MPU.integral=0;
	PID_MPU.differ=0; 	
}

void xunji_Init(void)	
{
	Motor_Init();	
	while(MPU_Init())//MPU初始化
	{
		Delay_ms(50);
		BEEP=!BEEP;
	}
	mpu_dmp_init();
  Delay_ms(50);	
	MPUPID_Init();
	TimerA0_Tim_Init();
}



void MPUPID_set(void)
{	
	
	 PID_MPU.err =PID_MPU.set_angel-MPUData.yaw;  //位于中心点左边是正，位于中心点右边是负
   PID_MPU.integral+=PID_MPU.err;
	 PID_MPU.differ=PID_MPU.Kp*PID_MPU.err+PID_MPU.Ki*PID_MPU.integral+PID_MPU.Kd*(PID_MPU.err-PID_MPU.err_last);//位置型PID算法	 
   Speed_A=SpeedA_BASIC- PID_MPU.differ;
	 Speed_B=SpeedB_BASIC- PID_MPU.differ;
	 Speed_C=SpeedC_BASIC+ PID_MPU.differ;
	 Speed_D=SpeedD_BASIC+ PID_MPU.differ;
	
}


void xunji(void)
{ 
	u8 key;
	OLED_Clear();
	xunji_Init();
	while(1)
	{		

		   OLED_ShowIntNum(0,0,Speed_A,4,12);
		   OLED_ShowIntNum(0,16,Speed_B,4,12);
			 OLED_ShowIntNum(64,0,Speed_C,4,12);
		   OLED_ShowIntNum(64,16,Speed_D,4,12);
			 OLED_Show3FNum(32,32,MPUData.yaw,3,2,12);
		   OLED_Show3FNum(0,48,PID_MPU.Kp,3,2,12);
		   OLED_Show3FNum(32,48,PID_MPU.Kd,3,2,12);
		   OLED_Show3FNum(64,48,PID_MPU.Ki,3,2,12);
			 OLED_Refresh_Gram();
       Motor_SetAB(Speed_A,Speed_B);
       Motor_SetCD(Speed_C,Speed_D);
	     key=KEY_Scan(0);
		if(key==KEY1_PRES)
		{
			PID_MPU.Kp=PID_MPU.Kp+1;
			Delay_ms(1000);
		}
		else if(key==KEY2_PRES)
		{
			PID_MPU.Kp=PID_MPU.Kp-1;
			Delay_ms(1000);
		}
		else if(key==KEY3_PRES)
		{
			PID_MPU.Kd=PID_MPU.Kd+0.1;
			Delay_ms(1000);
		}
		else if(key==KEY4_PRES)
		{
			PID_MPU.Kd=PID_MPU.Kd-0.1;
			Delay_ms(1000);
		}
		else if(key==KEY5_PRES)
		{
			PID_MPU.Ki=PID_MPU.Ki+0.1;
			Delay_ms(1000);
		}
		else if(key==KEY6_PRES)
		{
			PID_MPU.Ki=PID_MPU.Ki-0.1;
			Delay_ms(1000);
		}
	}
	
}
