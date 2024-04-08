/*
******************************************************************************
*Filename      :time.c
*Programmer(s) :代码敲得队
*Description   :2020省赛
******************************************************************************
*/


#include "timer.h"
#include "sys.h"
#include "step_cnt.h"
#include "mpu6050.h"
#include "key.h"
#include "oled.h"
#include "led.h"
#include "NRF24L01.h"
#include "xunji.h"
#include "motor.h"
#include "Encoder.h"

/*************************************************************
  * @brief   定时器A0参数	     	 	用于检测
*************************************************************/
const Timer_A_UpModeConfig TimerA0_upConfig = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_48,        	  //  48MHZ/48=1MHZ     1000 000/ 1000 =1000Hz
	1000,                                	  		// 	最多65535
	TIMER_A_TAIE_INTERRUPT_DISABLE,       	  //  定时器中断失能
	TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,  	 	//  定时器通道0中断使能
	TIMER_A_DO_CLEAR                      	  //	值清0
};


/*************************************************************
  * @brief   定时器A1参数					motor	
*************************************************************/
const Timer_A_PWMConfig TimerA1_PWM1Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_2,        	  //  48MHZ/2=24MHZ      24000 000 /10000=2400Hz
	10000,                                	  // 	最多65535
	TIMER_A_CAPTURECOMPARE_REGISTER_1,				//此处只初始化了通道一，motor.c中将所有通道重新初始化了
	TIMER_A_OUTPUTMODE_RESET_SET,
	0
};

const Timer_A_PWMConfig TimerA1_PWM2Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_2,        	  //  48MHZ/2=24MHZ      24000 000 /10000=2400Hz
	10000,                                	  // 	最多65535
	TIMER_A_CAPTURECOMPARE_REGISTER_2,				//此处只初始化了通道一，motor.c中将所有通道重新初始化了
	TIMER_A_OUTPUTMODE_RESET_SET,
	0
};

const Timer_A_PWMConfig TimerA1_PWM3Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_2,        	  //  48MHZ/2=24MHZ      24000 000 /10000=2400Hz
	10000,                                	  // 	最多65535
	TIMER_A_CAPTURECOMPARE_REGISTER_3,				//此处只初始化了通道一，motor.c中将所有通道重新初始化了
	TIMER_A_OUTPUTMODE_RESET_SET,
	0
};

const Timer_A_PWMConfig TimerA1_PWM4Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_2,        	  //  48MHZ/2=24MHZ      24000 000 /10000=2400Hz
	10000,                                	  // 	最多65535
	TIMER_A_CAPTURECOMPARE_REGISTER_4,				//此处只初始化了通道一，motor.c中将所有通道重新初始化了
	TIMER_A_OUTPUTMODE_RESET_SET,
	0
};


/*************************************************************
  * @brief   定时器A2参数					steer
*************************************************************/
const Timer_A_UpModeConfig TimerA2_upConfig = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_48,        	  //  48MHZ/48=1MHZ     1000 000/ 1000 =1000Hz
	1000,                                	  		// 	最多65535
	TIMER_A_TAIE_INTERRUPT_DISABLE,       	  //  定时器中断失能
	TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,  	 	//  定时器通道0中断使能
	TIMER_A_DO_CLEAR                      	  //	值清0
};

const Timer_A_PWMConfig  TimerA2_PWM1Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_48,        	  //  48MHZ/48=1MHZ
	20000,                                	  		// 	最多65535      1000000/20000=50Hz      20ms
	
	TIMER_A_CAPTURECOMPARE_REGISTER_1,					
	TIMER_A_OUTPUTMODE_RESET_SET,
	1500//舵机初始化角度
};
const Timer_A_PWMConfig  TimerA2_PWM2Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_48,        	  //  48MHZ/48=1MHZ
	20000,                                	  		// 	最多65535      1000000/20000=50Hz      20ms
	
	TIMER_A_CAPTURECOMPARE_REGISTER_2,					
	TIMER_A_OUTPUTMODE_RESET_SET,
	1500//舵机初始化角度
};
const Timer_A_PWMConfig  TimerA2_PWM3Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_48,        	  //  48MHZ/48=1MHZ
	20000,                                	  		// 	最多65535      1000000/20000=50Hz      20ms
	
	TIMER_A_CAPTURECOMPARE_REGISTER_3,					
	TIMER_A_OUTPUTMODE_RESET_SET,
	1500//舵机初始化角度
};
const Timer_A_PWMConfig  TimerA2_PWM4Config = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_48,        	  //  48MHZ/48=1MHZ
	20000,                                	  		// 	最多65535      1000000/20000=50Hz      20ms
	
	TIMER_A_CAPTURECOMPARE_REGISTER_4,					
	TIMER_A_OUTPUTMODE_RESET_SET,
	1500//舵机初始化角度
};


/*************************************************************
  * @brief   定时器A3参数
*************************************************************/
const Timer_A_UpModeConfig TimerA3_upConfig = 
{
	TIMER_A_CLOCKSOURCE_SMCLK,              	//  时钟源选择，ACLK/SMCLK
	TIMER_A_CLOCKSOURCE_DIVIDER_48,        	  //  48MHZ/48=1MHZ
	20,                                	  		// 	最多65535      1000 000/20=50kHz  0.02ms   
	TIMER_A_TAIE_INTERRUPT_DISABLE,       	  //  定时器中断失能
	TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,  	 	//  定时器通道3中断使能
	TIMER_A_DO_CLEAR                      	  //	值清0
	
};




/*
************************************************************
  * @brief   定时器A0初始化
  * @param   none
  *	@arg     none
  * @retval  none
************************************************************
*/

void TimerA0_Tim_Init(void)
{
	Timer_A_configureUpMode(TIMER_A0_MODULE, &TimerA0_upConfig);      // 定时器A0参数初始化
	Interrupt_enableInterrupt(INT_TA0_0);                             // 使能中断
	//MAP_Interrupt_enableInterrupt(INT_TA0_N);                       // 使能溢出中断
	Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_UP_MODE);           // 开启计数器
	Interrupt_enableMaster();                                         // 使能总中断
}

/*
************************************************************
  * @brief   定时器A1初始化
  * @param   none
  *	@arg     none
  * @retval  none
************************************************************
*/
void TimerA1_Tim_Init(void)
{
	
  MAP_Timer_A_generatePWM(TIMER_A1_MODULE, &TimerA1_PWM1Config);
	MAP_Timer_A_generatePWM(TIMER_A1_MODULE, &TimerA1_PWM2Config);
	MAP_Timer_A_generatePWM(TIMER_A1_MODULE, &TimerA1_PWM3Config);
	MAP_Timer_A_generatePWM(TIMER_A1_MODULE, &TimerA1_PWM4Config);
	
}


/*
************************************************************
  * @brief   定时器A2初始化
  * @param   none
  *	@arg     none
  * @retval  none
************************************************************
*/
//void TimerA2_Tim_Init(void)
//{
//	MAP_Timer_A_generatePWM(TIMER_A2_MODULE, &TimerA2_PWM1Config);
//	MAP_Timer_A_generatePWM(TIMER_A2_MODULE, &TimerA2_PWM2Config);
//	MAP_Timer_A_generatePWM(TIMER_A2_MODULE, &TimerA2_PWM3Config);
//	MAP_Timer_A_generatePWM(TIMER_A2_MODULE, &TimerA2_PWM4Config);
//}
void TimerA2_Tim_Init(void)
{
	Timer_A_configureUpMode(TIMER_A2_MODULE, &TimerA2_upConfig);      // 定时器A0参数初始化
	Interrupt_enableInterrupt(INT_TA2_0);                             // 使能中断
	//MAP_Interrupt_enableInterrupt(INT_TA0_N);                       // 使能溢出中断
	Timer_A_startCounter(TIMER_A2_MODULE, TIMER_A_UP_MODE);           // 开启计数器
	Interrupt_enableMaster();    
}


/*
************************************************************
  * @brief   定时器A3初始化
  * @param   none
  *	@arg     none
  * @retval  none
************************************************************
*/
void TimerA3_Tim_Init(void)
{
	Timer_A_configureUpMode(TIMER_A3_MODULE, &TimerA3_upConfig);      // 定时器A3参数初始化
	Interrupt_enableInterrupt(INT_TA3_0);                             // 使能中断
	//MAP_Interrupt_enableInterrupt(INT_TA0_N);                       // 使能溢出中断
	Timer_A_startCounter(TIMER_A3_MODULE, TIMER_A_UP_MODE);           // 开启计数器
	Interrupt_enableMaster();                                         // 使能总中断
}








/*************************************************************
  * @brief   定时器A0中断服务函数
*************************************************************/
void TA0_0_IRQHandler(void)
{	
	static u16 ms_2=0,ms_5=0,ms_20=0,ms_1000=0;
	ms_2++;
	ms_5++;
	ms_20++;
  ms_1000++;
	if(ms_2 >= 2)
	{
		ms_2=0; 
	}
	
	if(ms_5 >= 5)
	{
		ms_5=0;
		
	}
	if(ms_20>=20)
	{
		ms_20=0;
//		mpu_dmp_get_data(&MPUData.pitch,&MPUData.roll,&MPUData.yaw);
		MPUPID_set();
		LED0=!LED0;
	}
	if(ms_1000>=1000)
	{
		ms_1000=0;
		LED0=!LED0;
	}
	Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_0);//清标志位
}

/*************************************************************
  * @brief   定时器A1中断服务函数
*************************************************************/
void TA1_0_IRQHandler(void)
{	
	Timer_A_clearCaptureCompareInterrupt(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_0);//清标志位
}

/*************************************************************
  * @brief   定时器A2中断服务函数
*************************************************************/
void TA2_0_IRQHandler(void)
{
	static u16 ms_10=0;

	ms_10++;   //10ms中断标志位

	if(ms_10 >= 10)
	{
		distance_1 = distance_1 + cc(getDrv_Encoder1())*Encoder_1_SUM;
		distance_2 = distance_2 + cc(getDrv_Encoder2())*Encoder_2_SUM;
		distance_3 = distance_3 + cc(getDrv_Encoder3())*Encoder_3_SUM;
		distance_4 = distance_4 + cc(getDrv_Encoder4())*Encoder_4_SUM;
		Speed_1 = Encoder_1_SUM;
		Speed_2 = Encoder_2_SUM;
		Speed_3 = Encoder_3_SUM;
		Speed_4 = Encoder_4_SUM;
		
		Encoder_1_SUM = 0;
		Encoder_2_SUM = 0;
		Encoder_3_SUM = 0;
		Encoder_4_SUM = 0;
		ms_10=0;
	}
	Timer_A_clearCaptureCompareInterrupt(TIMER_A2_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_0);//清标志位
}

/*************************************************************
  * @brief   定时器A3中断服务函数
*************************************************************/
void TA3_0_IRQHandler(void)
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

	MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_0);//清标志位
}

void TA_TEST(void)
{
	u8 key;
	OLED_Clear();
	OLED_ShowString(0,0,"key1-TA0_TEST",12);
	OLED_ShowString(0,16,"key2-TA0_TEST",12);
	OLED_ShowString(0,32,"key3-TA0_TEST",12);
	OLED_ShowString(0,48,"key4-TA0_TEST",12);
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
		{
			OLED_Clear();
			OLED_ShowString(0,32,"TA0_TEST",12);
			TimerA0_Tim_Init();			
		}
		else if(key==KEY5_PRES)
			return;
	}
}


