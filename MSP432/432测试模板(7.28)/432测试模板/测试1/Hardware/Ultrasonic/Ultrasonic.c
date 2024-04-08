#include "Ultrasonic.h"
#include "oled.h"
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : ��������
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
*Description : ��ʱ��A3 ���������ʼ��
*Notes       : none
******************************************************************************************************************
*/
const Timer_A_ContinuousModeConfig TimerA3_continuousModeConfig =
{
	TIMER_A_CLOCKSOURCE_SMCLK,                            // ʹ��SMCLKʱ��
	TIMER_A_CLOCKSOURCE_DIVIDER_48,                       // SMCLKӦ����48M������ʹ��48��Ƶ
	TIMER_A_TAIE_INTERRUPT_ENABLE,                        // ʹ���ж�
	TIMER_A_DO_CLEAR                                      // ֵ����
};
/* Timer_A Capture Mode Configuration Parameter */
const Timer_A_CaptureModeConfig TimerA3_captureModeConfig =
{
	TIMER_A_CAPTURECOMPARE_REGISTER_0,                    // ͨ��0
	TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE,          // �����غ��½��ش���
	TIMER_A_CAPTURE_INPUTSELECT_CCIxA,                    // CCIxA
	TIMER_A_CAPTURE_SYNCHRONOUS,                          // ͬ������
	TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,              // ʹ���ж�
	TIMER_A_OUTPUTMODE_OUTBITVALUE                        // ����ģʽ�������ó��������
};
/******************************************************************************************************************
*                                               Ultrasonic_Init()
*
*Description : ��������ʼ��
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void Ultrasonic_Init(void)
{
	GPIO_setAsOutputPin(Ultrasonic_Trig_PORT, Ultrasonic_Trig_PIN);            //�������ģʽ
	Ultrasonic_OFF();
	TimerA3_Cap_Init();
}
/******************************************************************************************************************
*                                              TimerA3_Cap_Init() 
*
*Description : ��ʱ��A3 �����ʼ��
*Arguments   : none
*Returns     : none
*Notes       : ����P10.4�ڲ���ģʽ
*******************************************************************************************************************
*/
void TimerA3_Cap_Init(void)
{
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10,GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); //���빦������
	MAP_Timer_A_initCapture(TIMER_A3_MODULE, &TimerA3_captureModeConfig);                               //��ʱ��3 �����ʼ��
	MAP_Timer_A_configureContinuousMode(TIMER_A3_MODULE, &TimerA3_continuousModeConfig);                //��ʱ��3 ����Ϊ����ģʽ
	//MAP_Interrupt_enableInterrupt(INT_TA3_0);                                                           //ʹ�ܶ�ʱ��ͨ��0�ж�
	MAP_Interrupt_enableInterrupt(INT_TA3_N);
	//Timer_A_enableInterrupt(TIMER_A3_MODULE); 
	MAP_Timer_A_startCounter(TIMER_A3_MODULE, TIMER_A_CONTINUOUS_MODE);
	MAP_Interrupt_enableMaster();                                                                       //�����ж�
}
/******************************************************************************************************************
*                                             TA3_N_IRQHandler()  
*
*Description : ��ʱ��A3 �жϷ�����
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void TA3_N_IRQHandler(void)
{
	uint8_t status;
	
	//�����ж��ж�
	status = Timer_A_getInterruptStatus(TIMER_A3_MODULE);
	if(status & 0x01)  //�����ж�
	{
		if(Ultrasoni_Data.Status & 0x80)          //�Ѿ�����������
		{
			if(Ultrasoni_Data.OverFlowCnt == 0xFF)  //���������
			{
				Ultrasoni_Data.Measure_Complete = 1;  //�������
				Ultrasoni_Data.Status           = 0;  //���״̬��־λ
			}else Ultrasoni_Data.OverFlowCnt ++;
		}
	}
	status = Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
	if(status & TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)             //�����ж�
	{
		//����������
		//if(TIMER_A_CAPTURECOMPARE_INPUT_LOW == Timer_A_getSynchronizedCaptureCompareInput(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0, TIMER_A_READ_SYNCHRONIZED_CAPTURECOMPAREINPUT))
		if(TIMER_A_CAPTURECOMPARE_INPUT_HIGH == GPIO_getInputPinValue(GPIO_PORT_P10,GPIO_PIN4))
		{
			Ultrasoni_Data.Capture_Val_Last = Timer_A_getCaptureCompareCount(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0); 
			Ultrasoni_Data.OverFlowCnt = 0;         //���������
			Ultrasoni_Data.Status      = 0;         //���״̬��־λ
			Ultrasoni_Data.Status     |= 0x80;      //��ǲ���������
		}else                                     //�����½���
		{
			if(Ultrasoni_Data.Status & 0x80)        //�Ѿ�����������
			{
				Ultrasoni_Data.Capture_Val_Now  = Timer_A_getCaptureCompareCount(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
				Ultrasoni_Data.High = 1 * (Ultrasoni_Data.OverFlowCnt * 65536 + Ultrasoni_Data.Capture_Val_Now - Ultrasoni_Data.Capture_Val_Last);
				Ultrasoni_Data.Measure_Complete = 1;         //�������
				Ultrasoni_Data.Status           = 0;         //���״̬��־λ
			}
		}
	}
	Timer_A_clearCaptureCompareInterrupt(TIMER_A3_MODULE, TIMER_A_CAPTURECOMPARE_REGISTER_0);  //����жϱ�־λ
	MAP_Timer_A_clearInterruptFlag(TIMER_A3_MODULE);                                           //����жϱ�־λ
}
/******************************************************************************************************************
*                                             TA3_N_IRQHandler()  
*
*Description : ��ʱ��A3 ͨ����ʱ�жϷ�����
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
//void TA3_0_IRQHandler(void)
//{
//	MAP_Timer_A_clearInterruptFlag(TIMER_A3_MODULE);      //����жϱ�־λ
//	if(Ultrasoni_Data.Status & 0x80)          //�Ѿ�����������
//	{
//		if(Ultrasoni_Data.OverFlowCnt == 0xFF)  //���������
//		{
//			Ultrasoni_Data.Measure_Complete = 1;  //�������
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
				temp1*=Ultrasoni_Data.OverFlowCnt;         	//���ʱ���ܺ�
				temp1+=Ultrasoni_Data.Capture_Val_Now;				//�õ��ܵĸߵ�ƽʱ��
			OLED_Show3FNum(40,40,temp1 ,3,3,12);
		   OLED_Refresh_Gram();//������ʾ��OLED	
				Ultrasoni_Data.Status=0;     				//������һ�β���
//	}
}
