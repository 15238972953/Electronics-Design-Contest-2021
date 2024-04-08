/*************************************************************
55555555555555555555555555555555555555555555555
  *
  * @Filename            oled.c
  * @Programmer          Landlord_BZ  LAB416
  * @date                2020-10-xx
  * @brief               将定时器TIME2的通道1234配置成
  *	                     20kg舵机（500us--2500us）的工作模式
  *
55555555555555555555555555555555555555555555555
*************************************************************/

/* $ PAGE*/
#include "sys.h"
#include "delay.h"
#include "steer.h"
#include "oled.h"
#include "key.h"

Timer_A_PWMConfig steer1_init =
{
	      TIMER_A_CLOCKSOURCE_SMCLK,              //低频子系统时钟
        TIMER_A_CLOCKSOURCE_DIVIDER_48,         //48分频 1us脉冲
        20000,                                  //周期20ms
        TIMER_A_CAPTURECOMPARE_REGISTER_1,      //寄存器（通道）1
        TIMER_A_OUTPUTMODE_RESET_SET,           //Reset/Set MODE （Guide P607）
        1500,                                   //初值1500us，0°位置
};

Timer_A_PWMConfig steer2_init =
{
	      TIMER_A_CLOCKSOURCE_SMCLK,              //低频子系统时钟
        TIMER_A_CLOCKSOURCE_DIVIDER_48,         //48分频 1us脉冲
        20000,                                  //周期20ms
        TIMER_A_CAPTURECOMPARE_REGISTER_2,      //寄存器（通道）2
        TIMER_A_OUTPUTMODE_RESET_SET,           //Reset/Set MODE （Guide P607）
        1500,                                   //初值1500us，0°位置
};

Timer_A_PWMConfig steer3_init =
{
	      TIMER_A_CLOCKSOURCE_SMCLK,              //低频子系统时钟
        TIMER_A_CLOCKSOURCE_DIVIDER_48,         //48分频 1us脉冲
        20000,                                  //周期20ms
        TIMER_A_CAPTURECOMPARE_REGISTER_3,      //寄存器（通道）2
        TIMER_A_OUTPUTMODE_RESET_SET,           //Reset/Set MODE （Guide P607）
        1500,                                   //初值1500us，0°位置
};

Timer_A_PWMConfig steer4_init =
{
	      TIMER_A_CLOCKSOURCE_SMCLK,              //低频子系统时钟
        TIMER_A_CLOCKSOURCE_DIVIDER_48,         //48分频 1us脉冲
        20000,                                  //周期20ms
        TIMER_A_CAPTURECOMPARE_REGISTER_4,      //寄存器（通道）2
        TIMER_A_OUTPUTMODE_RESET_SET,           //Reset/Set MODE （Guide P607）
        1500,                                   //初值1500us，0°位置
};

/******************************************************************************
*              void STEER_Init(void)
*
*Description : 舵机PWM初始化
*Arguments   : none		
*Returns     : none
*Notes       : none
******************************************************************************/
void STEER_Init(void)
{
	GPIO_setAsPeripheralModuleFunctionOutputPin
	(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);//P5.6（STEER1）PRIMARY复用
	GPIO_setAsPeripheralModuleFunctionOutputPin
	(GPIO_PORT_P5, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);//P5.7（STEER2）PRIMARY复用
	GPIO_setAsPeripheralModuleFunctionOutputPin
	(GPIO_PORT_P6, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);//P6.6（STEER3）PRIMARY复用
	GPIO_setAsPeripheralModuleFunctionOutputPin
	(GPIO_PORT_P6, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);//P6.7（STEER4）PRIMARY复用	
	Timer_A_generatePWM(TIMER_A2_MODULE, &steer1_init);
  Timer_A_generatePWM(TIMER_A2_MODULE, &steer2_init);
	Timer_A_generatePWM(TIMER_A2_MODULE, &steer3_init);
  Timer_A_generatePWM(TIMER_A2_MODULE, &steer4_init);		
	Timer_A_enableInterrupt(TIMER_A2_MODULE);
	Interrupt_enableMaster();
}

/******************************************************************************
*              void Steer_Angle_Control(u8 CHX,int Steer_Angle)
*
*Description : 舵机角度控制
*Arguments   : Which：1 2 3 4
							 Steer_Angle:舵机旋转角度：-90-90
*Returns     : none
*Notes       : none
******************************************************************************/
void Steer_Angle_Control(u8 Which,int Steer_Angle)
{
	int Steer_PWM;
	Steer_PWM = (u32)(Steer_Angle*1000/90)+1500;
	switch(Which)
	{
		case 1:Timer_A_setCompareValue(TIMER_A2_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1,Steer_PWM);
					 break;
		case 2:Timer_A_setCompareValue(TIMER_A2_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2,Steer_PWM);
					 break;
		case 3:Timer_A_setCompareValue(TIMER_A2_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3,Steer_PWM);
					 break;
		case 4:Timer_A_setCompareValue(TIMER_A2_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4,Steer_PWM);
					 break;
		default:break;
	}
}
/******************************************************************************
*              void Steer_Test(void)
*
*Description : 自己按需修改
*Arguments   : none
*Returns     : none
*Notes       : none
******************************************************************************/
void Steer_Test(void)
{
	u8 key;
	int angle=0;
	
	OLED_Clear();
	STEER_Init();
	
	  OLED_ShowString(0,0,"key1-REST",12);
	  OLED_ShowString(0,16,"key2-run",12);
	  OLED_ShowString(0,32,"key3:a+,key4:a-",12);
	  OLED_ShowString(0,48,"angle=",12);
	
	while(1)
	{	    	
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
		{			
	    angle=0;
		}
		else if(key==KEY2_PRES)
		{
			Steer_Angle_Control(1, angle);
    	Steer_Angle_Control(2, angle);
      Steer_Angle_Control(3, angle);
    	Steer_Angle_Control(4, angle);
		}
		else if(key==KEY3_PRES)
		{
      angle=angle+10;
		}
		else if(key==KEY4_PRES)
		{
      angle=angle-10;
		}
		else if(key==KEY5_PRES)
			return ;
		OLED_ShowIntNum(36,48,angle,3,12);
	}
}


