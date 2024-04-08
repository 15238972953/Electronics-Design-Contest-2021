#include "Ultrasonic.h"
#include "oled.h"
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : 变量定义
*Notes       : none
******************************************************************************************************************
*/
Ultrasonic_Stru Ultrasoni_Data = 
{0,0,0,0,0,0};
u32 	temp1=0;
float 	 	TEMP1=0;

/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : 定时器A3 捕获参数初始化
*Notes       : none
******************************************************************************************************************
*/
const Timer_A_ContinuousModeConfig TimerA3_continuousModeConfig =
{
	TIMER_A_CLOCKSOURCE_SMCLK,                            // 使用SMCLK时钟
	TIMER_A_CLOCKSOURCE_DIVIDER_48,                       // SMCLK应该是48M，所以使用48分频
	TIMER_A_TAIE_INTERRUPT_ENABLE,                        // 使能中断
	TIMER_A_DO_CLEAR                                      // 值清零
};
/* Timer_A Capture Mode Configuration Parameter */
const Timer_A_CaptureModeConfig TimerA3_captureModeConfig =
{
	TIMER_A_CAPTURECOMPARE_REGISTER_0,                    // 通道0
	TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE,          // 上升沿和下降沿触发
	TIMER_A_CAPTURE_INPUTSELECT_CCIxA,                    // CCIxA
	TIMER_A_CAPTURE_SYNCHRONOUS,                          // 同步捕获
	TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,              // 使能中断
	TIMER_A_OUTPUTMODE_OUTBITVALUE                        // 捕获模式必须配置成这个参数
};
/******************************************************************************************************************
*                                               Ultrasonic_Init()
*
*Description : 超声波初始化
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void Ultrasonic_Init(void)
{
	GPIO_setAsOutputPin(Ultrasonic_Trig_PORT, Ultrasonic_Trig_PIN);            //设置输出模式
	Ultrasonic_OFF();
	TimerA3_Cap_Init();
}
/******************************************************************************************************************
*                                              TimerA3_Cap_Init() 
*
*Description : 定时器A3 捕获初始化
*Arguments   : none
*Returns     : none
*Notes       : 设置P10.4口捕获模式
*******************************************************************************************************************
*/
void TimerA3_Cap_Init(void)
{
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10,GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); //输入功能引脚
	MAP_Timer_A_initCapture(TIMER_A3_MODULE, &TimerA3_captureModeConfig);                               //定时器3 捕获初始化
	MAP_Timer_A_configureContinuousMode(TIMER_A3_MODULE, &TimerA3_continuousModeConfig);                //定时器3 设置为连续模式
	//MAP_Interrupt_enableInterrupt(INT_TA3_0);                                                           //使能定时器通道0中断
	MAP_Interrupt_enableInterrupt(INT_TA3_N);
	//Timer_A_enableInterrupt(TIMER_A3_MODULE); 
	MAP_Timer_A_startCounter(TIMER_A3_MODULE, TIMER_A_CONTINUOUS_MODE);
	MAP_Interrupt_enableMaster();                                                                       //开总中断
}
/******************************************************************************************************************
*                                             TA3_N_IRQHandler()  
*
*Description : 定时器A3 中断服务函数
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void TA3_N_IRQHandler(void)
{
	uint8_t status;
	
	//捕获中断判断
	status = Timer_A_getInterruptStatus(TIMER_A3_MODULE);
	if(status & 0x01)  //更新中断
	{
		if(Ultrasoni_Data.Status & 0x80)          //已经捕获到上升沿
		{
			if(Ultrasoni_Data.OverFlowCnt == 0xFF)  //计数到最大
			{
				Ultrasoni_Data.Measure_Complete = 1;  //捕获完成
				Ultrasoni_Data.Status           = 0;  //清除状态标志位
			}else Ultrasoni_Data.OverFlowCnt ++;
		}
	}
	status = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
	if(status & TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)             //捕获中断
	{
		//捕获到上升沿
		//if(TIMER_A_CAPTURECOMPARE_INPUT_LOW == Timer_A_getSynchronizedCaptureCompareInput(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0, TIMER_A_READ_SYNCHRONIZED_CAPTURECOMPAREINPUT))
		if(TIMER_A_CAPTURECOMPARE_INPUT_HIGH == GPIO_getInputPinValue(GPIO_PORT_P10,GPIO_PIN4))
		{
			Ultrasoni_Data.Capture_Val_Last = Timer_A_getCaptureCompareCount(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0); 
			Ultrasoni_Data.OverFlowCnt = 0;         //清除计数器
			Ultrasoni_Data.Status      = 0;         //清除状态标志位
			Ultrasoni_Data.Status     |= 0x80;      //标记捕获到上升沿
		}else                                     //捕获到下降沿
		{
			if(Ultrasoni_Data.Status & 0x80)        //已经捕获到上升沿
			{
				Ultrasoni_Data.Capture_Val_Now  = Timer_A_getCaptureCompareCount(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
				Ultrasoni_Data.High = 1 * (Ultrasoni_Data.OverFlowCnt * 65536 + Ultrasoni_Data.Capture_Val_Now - Ultrasoni_Data.Capture_Val_Last);
				Ultrasoni_Data.Measure_Complete = 1;         //捕获完成
				Ultrasoni_Data.Status           = 0;         //清除状态标志位
			}
		}
	}
	Timer_A_clearCaptureCompareInterrupt(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0);  //清除中断标志位
	MAP_Timer_A_clearInterruptFlag(TIMER_A3_MODULE);                                           //清除中断标志位
}
/******************************************************************************************************************
*                                             TA3_N_IRQHandler()  
*
*Description : 定时器A3 通道计时中断服务函数
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
//void TA3_0_IRQHandler(void)
//{
//	MAP_Timer_A_clearInterruptFlag(TIMER_A3_MODULE);      //清除中断标志位
//	if(Ultrasoni_Data.Status & 0x80)          //已经捕获到上升沿
//	{
//		if(Ultrasoni_Data.OverFlowCnt == 0xFF)  //计数到最大
//		{
//			Ultrasoni_Data.Measure_Complete = 1;  //捕获完成
//			
//		}else Ultrasoni_Data.OverFlowCnt ++;
//	}
//}

void Ultrasonic_Get_Distance(void)
{
	uint8_t status;
	TRIG_out
	
	status=Timer_A_getInterruptStatus(TIMER_A3_MODULE);
//	if(status& 0x80)
//	{
		temp1=status&0X3F; 
				temp1*=Ultrasoni_Data.OverFlowCnt;         	//溢出时间总和
				temp1+=Ultrasoni_Data.Capture_Val_Now;				//得到总的高电平时间
			OLED_Show3FNum(40,40,temp1 ,3,3,12);
		   OLED_Refresh_Gram();//更新显示到OLED	
				Ultrasoni_Data.Status=0;     				//开启下一次捕获
//	}
}
