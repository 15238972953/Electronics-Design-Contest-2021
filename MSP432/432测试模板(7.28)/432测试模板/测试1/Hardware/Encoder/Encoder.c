/**************************************************
����һ���������Ľ���ֻ��Ҫ��AB����������D������������ѡһ��������벶�����
Q����˽�һ��freepin�����ŵ�ƽ�ж�ת��

��ʼ������Encoder_Cap_Init();

�ٶ�ֵ����Speed_1(int��)
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
        TIMER_A_CAPTURE_SYNCHRONOUS,              // ͬ������
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

const Timer_A_CaptureModeConfig captureModeConfig_Encoder2 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_2,       
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, // up and down
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA  
        TIMER_A_CAPTURE_SYNCHRONOUS,              // ͬ������
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

const Timer_A_CaptureModeConfig captureModeConfig_Encoder3 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_3,       
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, // up and down
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA  
        TIMER_A_CAPTURE_SYNCHRONOUS,              // ͬ������
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

const Timer_A_CaptureModeConfig captureModeConfig_Encoder4 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_4,       
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, // up and down
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA  
        TIMER_A_CAPTURE_SYNCHRONOUS,              // ͬ������
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  
        TIMER_A_OUTPUTMODE_OUTBITVALUE          
};

/*********************************************
�ж�ת�� ����1��-1
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
*Description : ��ʱ��A3 �����ʼ��
*Arguments   : none
*Returns     : none
*Notes       : ����P10.5�ڲ���ģʽ�����������������
*******************************************************************************************************************
*/
void Encoder_Cap_Init(void)
{	
	GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN0); //����ģʽ  ΪD������Q����˵��ź������
	GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN4); //����ģʽ  ΪD������Q����˵��ź������
	GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN5); //����ģʽ  ΪD������Q����˵��ź������
	GPIO_setAsInputPin(GPIO_PORT_P4,GPIO_PIN0); //����ģʽ  ΪD������Q����˵��ź������
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); //���벶�������� ��ӦT3C1
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION); //���벶�������� ��ӦT3C1
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION); //���벶�������� ��ӦT3C1
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION); //���벶�������� ��ӦT3C1
	//ͨ��1
	MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //��ʱ��0 ����Ϊ����ģ?                            //��ʱ��3 �����ʼ��
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder1);                               //��ʱ��0 �����ʼ��

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1);    //ͨ��1 ��������1�Ĳ���ͨ��
	
	Timer_A_enableInterrupt(TIMER_A0_MODULE);

	
	
	MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //��ʱ��0 ����Ϊ����ģ?                            //��ʱ��3 �����ʼ��
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder2);                               //��ʱ��0 �����ʼ��

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2);    //ͨ��1 ��������1�Ĳ���ͨ��
	
	Timer_A_enableInterrupt(TIMER_A0_MODULE);
	


	MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //��ʱ��0 ����Ϊ����ģ?                            //��ʱ��3 �����ʼ��
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder3);                               //��ʱ��0 �����ʼ��

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3);    //ͨ��1 ��������1�Ĳ���ͨ��
	
	Timer_A_enableInterrupt(TIMER_A0_MODULE);
	
	
	
		MAP_Timer_A_configureContinuousMode(TIMER_A0_MODULE, &continuousModeConfig_Encoder1);                //��ʱ��0 ����Ϊ����ģ?                            //��ʱ��3 �����ʼ��
	MAP_Timer_A_initCapture(TIMER_A0_MODULE, &captureModeConfig_Encoder4);                               //��ʱ��0 �����ʼ��

  MAP_Timer_A_startCounter(TIMER_A0_MODULE, TIMER_A_CONTINUOUS_MODE);  //
	Timer_A_enableCaptureCompareInterrupt(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4);    //ͨ��1 ��������1�Ĳ���ͨ��
	
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
	//�����ж��ж�
 	status1 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1);
	status2 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
	status3 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3);
	status4 = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A0_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4);
	//�����ж� 
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
		Timer_A_clearInterruptFlag(TIMER_A0_MODULE);                                           //����жϱ�־λ
		
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_1);  //����жϱ�־λ
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_2);  //����жϱ�־λ
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_3);  //����жϱ�־λ
		Timer_A_clearCaptureCompareInterrupt(TIMER_A0_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_4);  //����жϱ�־λ
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
