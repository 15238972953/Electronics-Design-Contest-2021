/*************************************************************
//////////////////////////////////////////////////////////////

  *
  * @file    led.c
  * @author  Xsq IN LAB416
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   led/flash			
  *													
  *************************************
  
//////////////////////////////////////////////////////////////
*************************************************************/
/* $ PAGE*/
#include "led.h"
#include "oled.h"
#include "key.h"
#include "delay.h"

void LED_Init(void)
{
	GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4);            
	GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN5);
	GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0);//BEEP初始化
	
	LED0=0;//全部初始置低
	LED1=0;
	BEEP=0;
}

void LED_TEST(void)
{
	u8 key;
	OLED_Clear();
	OLED_ShowString(0,0,"basic test success",12);
	Delay_ms(500);
	OLED_Clear();
	OLED_ShowString(0,0,"key1-LED0 on",12);
	OLED_ShowString(0,16,"key2-LED0 off",12);
	OLED_ShowString(0,32,"key3-LED1 on",12);
	OLED_ShowString(0,48,"key4-LED0 off",12);
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
		{
			LED0=1;
			LED1=0;
			BEEP=1;
		}
		else if(key==KEY2_PRES)
		{
			LED0=0;
			LED1=1;
			BEEP=0;
		}
		else if(key==KEY3_PRES)
		{
			LED1=1;
			BEEP=1;
		}
		else if(key==KEY4_PRES)
		{
			LED1=0;
			BEEP=0;
		}
		else if(key==KEY5_PRES)
			break;
	}
}

	


