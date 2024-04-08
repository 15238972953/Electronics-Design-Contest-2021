#include "menu.h"
#include "key.h"
#include "led.h"
#include "include.h"
#include "oled.h"
#include "delay.h"
#include "mpu6050.h"
#include "NRF24L01.h"
#include "steer.h"
#include "adc.h"
#include "motor.h"
#include "openmv.h"
#include "Gesture.h"
#include "timer.h"
#include "Usart.h"
#include "Track.h"
#include "MLX90614.h"
#include "xunji.h"
#include "Encoder.h"

void menu_main(void)
{
	u8 key;
	while(1)
	{
		key=KEY_Scan(0);
	
	OLED_ShowString(0,0,"key1-basic test",12);
	OLED_ShowString(0,16,"key2-sensor test",12);
	OLED_ShowString(0,32,"key3-Mechanics test",12);
	OLED_ShowString(0,48,"key4-project test",12);
		
//	OLED_ShowString(0,64,"key5-return",12);
	OLED_Refresh_Gram();
		
	switch (key)
	{
		case KEY1_PRES: basic_menu(); break;		//基础测试
		case KEY2_PRES: sensor_menu(); break;		//传感器测试
		case KEY3_PRES: Mechanics_menu(); break;//电机测试	
		case KEY4_PRES: project_menu(); break;	//工程菜单
		case KEY6_PRES: xunji();break;
	}
	 if(key==KEY5_PRES)
	 {
		OLED_Clear();
		OLED_ShowString(0,0,"return",12);		
	  OLED_Refresh_Gram();
		Delay_ms(500);
		break;
	 }
	 Delay_ms(200);

	}
	
}

void Usart_TEST(void)
{
	
	u8 key;
	OLED_Clear();
  OLED_ShowString(16,16,"KEY1->Openmv test",12);
  OLED_ShowString(16,32,"KEY2->UsartA2 test",12);
	OLED_Refresh_Gram();
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
			Openmv_TEST();
		else if(key==KEY2_PRES)
			UsartA2_TEST();
		else if(key==KEY5_PRES)
			break;
	}
}

void basic_menu(void)
{
	u8 key;
	OLED_Clear();
	OLED_ShowString(0,0,"basic test success",12);
	Delay_ms(1000);
	OLED_Clear();

	while(1)
	{
		OLED_ShowString(0,0,"key1-LED test",12);
	OLED_ShowString(0,16,"key2-usart test",12);
	OLED_ShowString(0,32,"key3-TIMER test",12);
	OLED_ShowString(0,48,"key4-24L01 test",12);
	OLED_Refresh_Gram();
		key=KEY_Scan(0);
		
		switch (key)
	{
		case KEY1_PRES: LED_TEST(); break;
		case KEY2_PRES: Usart_TEST(); break;
		case KEY3_PRES: TA_TEST(); break;
		case KEY4_PRES: NRF24L01_TEST(); break;
	}
		
  if(key==KEY5_PRES)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"return",12);		
	  OLED_Refresh_Gram();
		Delay_ms(500);
		break;
	}
	}

}

void sensor_menu(void)
{
	u8 key;
	OLED_Clear();
	OLED_ShowString(0,0,"sensor test success",12);
	Delay_ms(1000);
	OLED_Clear();

	while(1)
	{
		OLED_ShowString(0,0,"key1-mpu6050 test",12);
	  OLED_ShowString(0,16,"key2-Ultrasonic test",12);
	  OLED_ShowString(0,32,"key3-ADC_Temp test",12);
	  OLED_ShowString(0,48,"key4-mlx90614 test",12);
	  OLED_Refresh_Gram();
		key=KEY_Scan(0);
		
		switch (key)
	{
		case KEY1_PRES: mpu6050_TEST(); break;
		case KEY2_PRES: sensor_menu(); break;
		case KEY3_PRES: ADC_Temp_TEST(); break;
		case KEY4_PRES: MLX90614_TEST(); break;
	}
		
  if(key==KEY5_PRES)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"return",12);		
	  OLED_Refresh_Gram();
		Delay_ms(500);
		break;
	}
	OLED_Refresh_Gram();
	}

}

void Mechanics_menu(void)
{
	u8 key;
	OLED_Clear();
	OLED_ShowString(0,0,"Mechanics test success",12);
	Delay_ms(1000);
	OLED_Clear();

	while(1)
	{
	 OLED_ShowString(0,0,"key1-steer test",12);
	 OLED_ShowString(0,16,"key2-step test",12);
	 OLED_ShowString(0,32,"key3-motor test",12);
	 OLED_ShowString(0,48,"key4-encoder test",12);
	 OLED_Refresh_Gram();
		key=KEY_Scan(0);
		
		switch (key)
	{
		case KEY1_PRES: Steer_Test(); break;
//		case KEY2_PRES: Step_menu(); break;
		case KEY3_PRES: Motor_TEST(); break;
		case KEY4_PRES: Encoder_TEST(); break;
	}
		
  if(key==KEY5_PRES)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"return",12);		
	  OLED_Refresh_Gram();
		Delay_ms(500);
		break;
	}
}
}

void project_menu(void)
{
	u8 key;
	OLED_Clear();
	OLED_ShowString(0,0,"Mechanics test success",12);
	Delay_ms(1000);
	OLED_Clear();
	
	while(1)
	{
		key=KEY_Scan(0);
	   OLED_ShowString(0,0,"key1-Gesture_Select",12);
	   OLED_ShowString(0,16,"key2-Openmv Control",12);
	   OLED_ShowString(0,32,"key3-     ",12);
	   OLED_ShowString(0,48,"key4-     ",12);
		 OLED_Refresh_Gram();
		switch (key)
	{
		case KEY1_PRES: Gesture_Select(); break;
		case KEY2_PRES: Track_Realize(); break;
		case KEY3_PRES: Motor_TEST(); break;
//		case KEY4_PRES: Encoder_menu(); break;
	}
	}
}


