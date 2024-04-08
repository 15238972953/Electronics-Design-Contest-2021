/*
******************************************************************************
*Filename      :key.c
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛：KEY
******************************************************************************
*/

#include "key.h"
#include "led.h"
#include "include.h"
#include "delay.h"

/*
********************************************************************************************************************
*                  void Key_Init(void)
*Description : 按键初始化
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void Key_Init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(KEY1_PORT, KEY1_PIN);   
		GPIO_setAsInputPinWithPullUpResistor(KEY2_PORT, KEY2_PIN);
		GPIO_setAsInputPinWithPullUpResistor(KEY3_PORT, KEY3_PIN);
		GPIO_setAsInputPinWithPullUpResistor(KEY4_PORT, KEY4_PIN);
		GPIO_setAsInputPinWithPullUpResistor(KEY5_PORT, KEY5_PIN);
		GPIO_setAsInputPinWithPullUpResistor(KEY6_PORT, KEY6_PIN);
}
/*
********************************************************************************************************************
*                  u8 KEY_Scan(u8 mode)
*Description : 按键值传递
*Arguments   : none
*Returns     : 按键值
*Notes       : none
********************************************************************************************************************
*/
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0))
	{
		Delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
		else if(KEY5==0)return KEY5_PRES;
		else if(KEY6==0)return KEY6_PRES;
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1)
	key_up=1; 
	return 0;// 无按键按下
}



/*
********************************************************************************************************************
*                  void Key_Interrupt_Init(void)
*Description : 按键中断的初始化
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void Key_Interrupt_Init(void)
{
	GPIO_setAsInputPinWithPullUpResistor(KEY1_PORT, KEY1_PIN);//KEY1->P4.6
  GPIO_clearInterruptFlag(KEY1_PORT, KEY1_PIN);							
  GPIO_enableInterrupt(KEY1_PORT, KEY1_PIN);	
	GPIO_interruptEdgeSelect(KEY1_PORT,KEY1_PIN,GPIO_HIGH_TO_LOW_TRANSITION);	
																																
	GPIO_setAsInputPinWithPullUpResistor(KEY2_PORT, KEY2_PIN);//KEY2->P4.7
  GPIO_clearInterruptFlag(KEY2_PORT, KEY2_PIN);							
  GPIO_enableInterrupt(KEY2_PORT, KEY2_PIN);
	GPIO_interruptEdgeSelect(KEY2_PORT,KEY2_PIN,GPIO_HIGH_TO_LOW_TRANSITION);	
	
	GPIO_setAsInputPinWithPullUpResistor(KEY3_PORT, KEY3_PIN);//KEY3->P5.0
  GPIO_clearInterruptFlag(KEY3_PORT, KEY3_PIN);
  GPIO_enableInterrupt(KEY3_PORT, KEY3_PIN);
	GPIO_interruptEdgeSelect(KEY3_PORT,KEY3_PIN,GPIO_HIGH_TO_LOW_TRANSITION);	
	
	GPIO_setAsInputPinWithPullUpResistor(KEY4_PORT, KEY4_PIN);//KEY4->P5.1
  GPIO_clearInterruptFlag(KEY4_PORT, KEY4_PIN);							
  GPIO_enableInterrupt(KEY4_PORT, KEY4_PIN);
	GPIO_interruptEdgeSelect(KEY4_PORT,KEY4_PIN,GPIO_HIGH_TO_LOW_TRANSITION);	
	
	GPIO_setAsInputPinWithPullUpResistor(KEY5_PORT, KEY5_PIN);//KEY5->P5.2
  GPIO_clearInterruptFlag(KEY5_PORT, KEY5_PIN);							
  GPIO_enableInterrupt(KEY5_PORT, KEY5_PIN);
	GPIO_interruptEdgeSelect(KEY5_PORT,KEY5_PIN,GPIO_HIGH_TO_LOW_TRANSITION);	
	
	GPIO_setAsInputPinWithPullUpResistor(KEY6_PORT, KEY6_PIN);//KEY6->P5.3
  GPIO_clearInterruptFlag(KEY6_PORT, KEY6_PIN);							
  GPIO_enableInterrupt(KEY6_PORT, KEY6_PIN);
	GPIO_interruptEdgeSelect(KEY6_PORT,KEY6_PIN,GPIO_HIGH_TO_LOW_TRANSITION);	
	
  Interrupt_enableInterrupt(INT_PORT4);
  Interrupt_enableInterrupt(INT_PORT5);
	Interrupt_enableMaster(); 
}
void PORT4_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
	
    if(status & GPIO_PIN6)					//KEY0功能，亮灯1，蜂鸣器响，持续0.5秒
    {
			LED1 = 1;
			BEEP = 1;
			Delay_ms(500);
			LED1 = 0;
			BEEP = 0;
    }
		else 
		{	
			LED1 = 0;
			BEEP = 0;
		}
		
    if(status & GPIO_PIN7)						//KEY1功能，亮灯2，蜂鸣器响，持续0.5秒
		{
			LED1 = 1;
			BEEP = 1;
			Delay_ms(500);
			LED1 = 0;
			BEEP = 0;
		}
		else
		{
			LED1 = 0;
			BEEP = 0;
		}
		GPIO_clearInterruptFlag(GPIO_PORT_P4, status);
}


void PORT5_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
	
	if(status & GPIO_PIN0)							//KEY2功能，亮灯1和2，蜂鸣器响，持续1秒，灯不灭
    {
			LED1 = 1;
			BEEP = 1;
			Delay_ms(500);
			LED1 = 0;
			BEEP = 0;
    }
		else 
		{	
			LED1 = 0;
			BEEP = 0;
		}
		
	if(status & GPIO_PIN1)							//KEY3功能，亮灯1和2，蜂鸣器响，持续1秒
    {
			LED1 = 1;
			BEEP = 1;
			Delay_ms(500);
			LED1 = 0;
			BEEP = 0;
    }
		else 
		{	
			LED1 = 0;
			BEEP = 0;
		}
		
		if(status & GPIO_PIN2)						//KEY4功能，蜂鸣器响，持续1秒
    {
			LED1 = 1;
			BEEP = 1;
			Delay_ms(500);
			LED1 = 0;
			BEEP = 0;
    }
		else 
		{	
			LED1 = 0;
			BEEP = 0;
		}

		if(status & GPIO_PIN3)						//KEY5功能，蜂鸣器响，持续1秒
    {
			LED1 = 1;
			BEEP = 1;
			Delay_ms(500);
			LED1 = 0;
			BEEP = 0;
    }
		else 
		{	
			LED1 = 0;
			BEEP = 0;
		}
		GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
}


