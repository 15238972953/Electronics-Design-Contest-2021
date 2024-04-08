#include "Gesture.h"
#include "NRF24L01.h"
#include "mpu6050.h"
#include "motor.h"
#include "delay.h"
#include "led.h"
#include "inv_mpu.h"
#include "oled.h"
#include "key.h"
#include "math.h"
#include "timer.h"

int speedA=0;
int speedB=0;
int speedC=0;
int speedD=0;

void Gesture_RX_Init(void)
{
	Motor_Init();
	NRF24L01_Init();
	Delay_ms(100);
	while(NRF24L01_Check())
	{
		BEEP=!BEEP;
		Delay_ms(200);
	}
	
}

void Gesture_TX_Init(void)
{
	
	NRF24L01_Init();
	Delay_ms(100);
	while(NRF24L01_Check())
	{
		BEEP=!BEEP;
		Delay_ms(200);
	}
	
	while(MPU_Init())//MPU≥ı ºªØ
	{
		Delay_ms(50);
		BEEP=!BEEP;
	}
	mpu_dmp_init();
  Delay_ms(50);	
}



void Gesture_Select(void)
{
	u8 key;
	OLED_Clear();
  OLED_ShowString(16,16,"key1 - RX",12);
	OLED_ShowString(16,32,"key2 - TX",12);	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
		  Gesture_RX();
		else if(key==KEY2_PRES)
			Gesture_TX();
		else if(key==KEY5_PRES)
			break;
	}
}



void Gesture_MotorSet(void)
{	
	int Symbol=0;
	int err=0;
	if(mpu_pitch<=0)
	Symbol=-1;
else if(mpu_pitch>=0)
	Symbol=1;

if(mpu_pitch<15&&mpu_pitch>-15)
{
	speedA=0;speedB=0;speedC=0;speedD=0;
}
else if(mpu_pitch>65)
{
	speedA=8000;
  speedB=8000;
  speedC=8000;
  speedD=8000;
}
else if(mpu_pitch<-65)
	{
	speedA=-8000;
  speedB=-8000;
  speedC=-8000;
  speedD=-8000;
	}	

else 
{
	speedA=(fabs(mpu_pitch)-15)*160*Symbol;
  speedB=(fabs(mpu_pitch)-15)*160*Symbol;
  speedC=(fabs(mpu_pitch)-15)*160*Symbol;
  speedD=(fabs(mpu_pitch)-15)*160*Symbol;	
}

 if(mpu_yaw>70)
	 mpu_yaw=70;
 else if(mpu_yaw<-70)
	 mpu_yaw=-70;
 if(mpu_yaw>10||mpu_yaw<-10)
 {
//	 err=mpu_yaw*(fabs(mpu_pitch)-15)/5;
	 err=mpu_yaw*50;
   speedA = speedA-err;
   speedB = speedB-err;
	 speedC = speedC+err;
	 speedD = speedD+err;
 }
OLED_ShowIntNum(0,48,speedA,4,12);
 OLED_ShowIntNum(32,48,speedB,4,12);
OLED_ShowIntNum(64,48,speedC,4,12);
 OLED_ShowIntNum(96,48,speedD,4,12);
 OLED_ShowIntNum(96,0,err,4,12);
}

void Gesture_RX(void)
{
	u8 key;
	OLED_Clear();	
	Gesture_RX_Init();
	
	OLED_ShowString(0,0,"Pitch          C",12);
	OLED_ShowString(0,16,"Roll           C",12);
	OLED_ShowString(0,32,"Yaw            C",12);
		OLED_Refresh_Gram();
		NRF24L01_RX_Mode();
	  TimerA0_Tim_Init();
		while(1)
		{
			key=KEY_Scan(0);
			Gesture_MotorSet();
			Motor_SetAB(speedA,speedB);
			Motor_SetCD(speedC,speedD);
      if(key==KEY5_PRES)
		    break;						
		}	
}

void Gesture_TX(void)
{
	u8 key;
	OLED_Clear();	
	Gesture_TX_Init();
	
	while(1)
	{
		key=KEY_Scan(0);
		NRF24L01_TX_Mode();
		if(mpu_dmp_get_data(&MPUData.pitch,&MPUData.roll,&MPUData.yaw)==0)
		{		
		OLED_Show3FNum(20,10,MPUData.pitch,3,3,12);
		OLED_Show3FNum(20,26,MPUData.roll,3,3,12);
		OLED_Show3FNum(20,42,MPUData.yaw,3,3,12);
		OLED_Refresh_Gram();
		LED0=0;
	  }
		else  LED0=1;
		
		NRF24L01_Send_mpu();
		Delay_ms(10);	
    if(key==KEY5_PRES)
		break;			
	}
	
}


