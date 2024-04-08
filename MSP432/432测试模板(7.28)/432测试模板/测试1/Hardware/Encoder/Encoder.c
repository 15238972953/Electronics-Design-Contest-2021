/**************************************************
对于一个编码器的接线只需要把AB相引出接入D触发器，再任选一相借入输入捕获计数
Q输出端接一个freepin读引脚电平判断转向。

初始化调用Encoder_Cap_Init();

速度值保存Speed_1(int型)
					Speed_2
I**************************************************/

#include "Encoder.h"
#include "oled.h"
#include "key.h"
#include "led.h"
#include "timer.h"
#include "motor.h"
volatile int Encoder_1_SUM=0;
volatile int Encoder_2_SUM=0;
volatile int Encoder_3_SUM=0;
volatile int Encoder_4_SUM=0;
volatile int Speed_1=0;
volatile int Speed_2=0;
volatile int Speed_3=0;
volatile int Speed_4=0;
volatile int distance_1=0;
volatile int distance_2=0;
volatile int distance_3=0;
volatile int distance_4=0;
volatile int Encoder_Flag=0;
volatile int Overflow[3]={0,0,0};
volatile int f=0;
const Timer_A_ContinuousModeConfig continuousModeConfig_Encoder1 =
{
        TIMER_A_CLOCKSOURCE_SMCLK,         

        TIMER_A_CLOCKSOURCE_DIVIDER_16,    //1M 
        TIMER_A_TAIE_INTERRUPT_ENABLE,
        TIMER_A_SKIP_CLEAR                    
};
const Timer_A_ContinuousModeConfig continuousModeConfig_Encoder2 =
{
        TIMER_A_CLOCKSOURCE_SMCLK,         
        TIMER_A_CLOCKSOURCE_DIVIDER_16,    //1M 
        TIMER_A_TAIE_INTERRUPT_ENABLE,
        TIMER_A_SKIP_CLEAR                    
};

const Timer_A_CaptureModeConfig captureModeConfig_Encoder1 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,       
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, // up and down
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA  
        TIMER_A_CAPTURE_SYNCHRONOUS,              // 同步捕获
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

const Timer_A_CaptureModeConfig captureModeConfig_Encoder2 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_2,       
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, // up and down
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA  
        TIMER_A_CAPTURE_SYNCHRONOUS,              // 同步捕获
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

const Timer_A_CaptureModeConfig captureModeConfig_Encoder3 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_3,       
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, // up and down
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA  
        TIMER_A_CAPTURE_SYNCHRONOUS,              // 同步捕获
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

const Timer_A_CaptureModeConfig captureModeConfig_Encoder4 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_4,       
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, // up and down
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA  
        TIMER_A_CAPTURE_SYNCHRONOUS,              // 同步捕获
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

/*********************************************
判断转向 返回1和-1
***********************************************/
int cc(int a){
	if(a==0x00)
		return 1;
	else 
		return -1;
}
/******************************************************************************************************************
*                                              Encoder_Cap_Init() 
*
*Description : 定时器A3 捕获初始化
*Arguments   : none
*Returns     : none
*Notes       : 设置P10.5口捕获模式（编码器捕获计数）
*******************************************************************************************************************
*/
void Encoder_Cap_Init(void)
{	
	GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN0); //输入模式  为D触发器Q输出端的信号输入口
	GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN4); //输入模式  为D触发器Q输出端的信号输入口
	GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN5); //输入模式  为D触发器Q输出端的信号输入口
	GPIO_setAsInputPin(GPIO_PORT_P4,GPIO_PIN0); //输入模式  为D触发器Q输出端的信号输入口
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); //输入捕获功能引脚 对应T3C1
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION); //输入捕获功能引脚 对应T3C1
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION); //输入捕获功能引脚 对应T3C1
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION); //输入捕获功能引脚 对应T3C1
	//通道1
	MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //定时器0 设置为连续模?                            //定时器3 捕获初始化
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder1);                               //定时器0 捕获初始化

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1);    //通道1 即编码器1的捕获通道
	
	Timer_A_enableInterrupt(TIMER_A0_MODULE);

	
	
	MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //定时器0 设置为连续模?                            //定时器3 捕获初始化
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder2);                               //定时器0 捕获初始化

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2);    //通道1 即编码器1的捕获通道
	
	Timer_A_enableInterrupt(TIMER_A0_MODULE);
	


	MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //定时器0 设置为连续模?                            //定时器3 捕获初始化
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder3);                               //定时器0 捕获初始化

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3);    //通道1 即编码器1的捕获通道
	
	Timer_A_enableInterrupt(TIMER_A0_MODULE);
	
	
	
		MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //定时器0 设置为连续模?                            //定时器3 捕获初始化
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder4);                               //定时器0 捕获初始化

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4);    //通道1 即编码器1的捕获通道
	
	Timer_A_enableInterrupt(TIMER_A0_MODULE);
	
	
	MAP_Interrupt_enableInterrupt(INT_TA0_N);
	
  MAP_Interrupt_enableMaster();
}







void TA0_N_IRQHandler(void)
{
	 uint32_t status1=0;
	 uint32_t status2=0;
	 uint32_t status3=0;
	 uint32_t status4=0;
	//捕获中断判断
 	status1 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1);
	status2 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
	status3 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3);
	status4 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4);
	//捕获中断 
		if(status1 & TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)
		{
			Encoder_1_SUM=Encoder_1_SUM+1;
		}
		
		if(status2 & TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)
		{
			Encoder_2_SUM=Encoder_2_SUM+1;
		}
		
		if(status3 & TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)
		{
			Encoder_3_SUM=Encoder_3_SUM+1;
		}
		if(status4 & TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)
		{
			Encoder_4_SUM=Encoder_4_SUM+1;
		}
		Timer_A_clearInterruptFlag(TIMER_A0_MODULE);                                           //清除中断标志位
		
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_1);  //清除中断标志位
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_2);  //清除中断标志位
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_3);  //清除中断标志位
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_4);  //清除中断标志位
}


//void Encoder_Cap_Init(void)
//{
//		Encoder1_Cap_Init();
////		Encoder3_Cap_Init();
//		Encoder2_Cap_Init();
//}

void Encoder_TEST(void)
{	
	OLED_Clear();
	Encoder_Cap_Init();
	TimerA2_Tim_Init();
	while(1)
	{

		OLED_ShowIntNum(32,0,Speed_1,4,12);
		OLED_ShowIntNum(32,16,Speed_2,4,12);
		OLED_ShowIntNum(32,32,Speed_3,4,12);
		OLED_ShowIntNum(32,48,Speed_4,4,12);
		
		OLED_ShowIntNum(64,0,distance_1,4,12);
		OLED_ShowIntNum(64,16,distance_2,4,12);
		OLED_ShowIntNum(64,32,distance_3,4,12);
		OLED_ShowIntNum(64,48,distance_4,4,12);
		
		OLED_Refresh_Gram();
	}
}
