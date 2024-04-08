/*
******************************************************************************
*Filename      :Motor.c
*Programmer(s) :代码敲得队
*Description   :2020省赛
******************************************************************************
*/

#include "motor.h"
#include "oled.h"
#include "key.h"
#include "timer.h"
#include "delay.h"

#define  SPEED_BASEA  0
#define  SPEED_BASEB  0
#define  SPEED_BASEC  0
#define  SPEED_BASED  0
/******************* void Motor_Init(void)电机初始化 **********************/

void Motor_Init(void)
{
	Motor_GPIO_Init();
	PWM_Init();
  TimerA1_Tim_Init();
}
/*************************************************************
  * @brief   通道1参数初始化	
*************************************************************/
const Timer_A_CompareModeConfig compareConfig_PWM1 = 
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR1
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,            // Toggle output but
        CYCLE1                                			//  Duty Cycle
};

/*************************************************************
  * @brief   通道2参数初始化	
*************************************************************/
const Timer_A_CompareModeConfig compareConfig_PWM2 = 
{
        TIMER_A_CAPTURECOMPARE_REGISTER_2,          // Use CCR2
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,            // Toggle output but
        CYCLE2                                			//  Duty Cycle
};

/*************************************************************
  * @brief   通道3参数初始化	
*************************************************************/
const Timer_A_CompareModeConfig compareConfig_PWM3 = 
{
        TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CCR3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,            // Toggle output but
        CYCLE3                                			//  Duty Cycle
};

/*************************************************************
  * @brief   通道4参数初始化	
*************************************************************/
const Timer_A_CompareModeConfig compareConfig_PWM4 = 
{
        TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR4
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,            // Toggle output but
        CYCLE4                                			//  Duty Cycle
};


/***********************定时器A1引脚复用**********************/
void PWM_Init(void)
{
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7,         //	初始化P7.4-P7.7
  GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7, 
	GPIO_PRIMARY_MODULE_FUNCTION);
  Timer_A_startCounter(TIMER_A1_MODULE, TIMER_A_UP_MODE);
  Timer_A_initCompare(TIMER_A1_MODULE, &compareConfig_PWM1);
  Timer_A_initCompare(TIMER_A1_MODULE, &compareConfig_PWM2);
  Timer_A_initCompare(TIMER_A1_MODULE, &compareConfig_PWM3);
  Timer_A_initCompare(TIMER_A1_MODULE, &compareConfig_PWM4);
}







/******************* void Motor_GPIO_Init(void)电机引脚初始化 **********************
P8.5	AIN2			P6.2	CIN2			P7.7	PWMA
    			                			P7.6	PWMB
P8.7	BIN2			P4.3	DIN2			P7.5	PWMC
                          			P7.4	PWMD
*******************************************************************************/
void Motor_GPIO_Init(void)
{
  MAP_GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN4+GPIO_PIN5);
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN6+GPIO_PIN7);
	
  MAP_GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN2);
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN1);
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2+GPIO_PIN3);
	
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN4+GPIO_PIN3);
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN5+GPIO_PIN6);
		
	GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN4+GPIO_PIN5);
  GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN6+GPIO_PIN7);
	
	GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_PIN2+GPIO_PIN3);
	GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2+GPIO_PIN3);
	
	GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN4+GPIO_PIN3);
	GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN6+GPIO_PIN5);	
}




/******************* int  myabs(int x)绝对值函数 ***********************/
int  myabs(int x)
{
  int temp;
	if(x < 0)  temp=-x;  
	else       temp= x;
	return     temp;
}	


/*
**************************************************************************
**		int  Limit_Value(int x,int Max,int Min)限幅函数
**		Max:幅值上限；Min：幅值下限
**************************************************************************
*/
int  Limit_Value(int x,int Max,int Min)
{
	 if (x>Max)   x = Max;
   if (x<Min)   x = Min;
	 return x;
}

/*
**************************************************************************
**	void Motor_Set(u16 speedA,u16 speedB)电机速度设定，可以为负值，便于PID调节
**	speedA :PWMA初始输入；speedB ：PWMB初始输入（不能保持两个电机转速相等，若要相等要加相应的初值SPEED_BASE）
**************************************************************************
*/

void MotorA_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{
	  AIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1,Compare );
	}
	else if(Compare<-Pwm_Er)
	{
	  AIN2 = 0;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1,10000+Compare );
	}
	else 
	{
	 AIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1,0 );
	}
}

void MotorB_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{
	  BIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2,Compare );
	}
	else if(Compare<-Pwm_Er)
	{
	  BIN2 = 0;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2,10000+Compare );
	}
	else 
	{
	 BIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2,0 );
	}
}

void MotorC_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{
	  CIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3,Compare );
	}
	else if(Compare<-Pwm_Er)
	{
	  CIN2 = 0;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3,10000+Compare );
	}
	else 
	{
	 CIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3,0 );
	}
}

void MotorD_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{
	  DIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4,Compare );
	}
	else if(Compare<-Pwm_Er)
	{
	  DIN2 = 0;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4,10000+Compare );
	}
	else 
	{
	 DIN2 = 1;
		Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4,0 );
	}
}











void Motor_SetAB(int speedA,int speedB)
{
//	int PWMA;
//	int PWMB;
//	speedA = Limit_Value(speedA,10000,-10000);
//	speedB = Limit_Value(speedB,10000,-10000);
//	if(speedA>=0)
//	{
//	   AIN1 = 1;
//		 AIN2 = 0;
//		 PWMA = myabs(speedA) + SPEED_BASEA;
//	}
//	else if(speedA<0)
//	{
//	   AIN1 = 0;
//		 AIN2 = 1;
//		 PWMA = myabs(speedA) + SPEED_BASEA;
//	}
//	
//	if(speedB>=0)
//	{
//	   BIN1 = 1;
//		 BIN2 = 0;
//		 PWMB = myabs(speedB) + SPEED_BASEB;
//	}
//	else if(speedB<0)
//	{
//	   BIN1 = 0;
//		 BIN2 = 1;
//		 PWMB = myabs(speedB) + SPEED_BASEB;
//	}
//	
//	
//	Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_1,PWMA );
//	Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_2,PWMB );
//	
}
///*
//**************************************************************************
//**	void Motor_Set(u16 speedA,u16 speedB)电机速度设定，可以为负值，便于PID调节
//**	speedA :PWMA初始输入；speedB ：PWMB初始输入（不能保持两个电机转速相等，若要相等要加相应的初值SPEED_BASE）
//**************************************************************************
//*/
void Motor_SetCD(int speedC,int speedD)
{
//	int PWMC;
//	int PWMD;
//	speedC=-speedC;
//	speedD=-speedD;
//	speedC = Limit_Value(speedC,10000,-10000);
//	speedD = Limit_Value(speedD,10000,-10000);
//	if(speedC>=0)
//	{
//	   CIN1 = 1;
//		 CIN2 = 0;
//		 PWMC = myabs(speedC) + SPEED_BASEC;
//	}
//	else if(speedC<0)
//	{
//	   CIN1 = 0;
//		 CIN2 = 1;
//		 PWMC = myabs(speedC) + SPEED_BASEC;
//	}
//	
//	
//	if(speedD>=0)
//	{
//	   DIN1 = 1;
//		 DIN2 = 0;
//		 PWMD = myabs(speedD) + SPEED_BASED;
//	}
//	else if(speedD<0)
//	{
//	   DIN1 = 0;
//		 DIN2 = 1;
//		 PWMD = myabs(speedD) + SPEED_BASED;
//	}
//	Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_3,PWMC );
//	Timer_A_setCompareValue(TIMER_A1_MODULE,TIMER_A_CAPTURECOMPARE_REGISTER_4,PWMD );
//	
}

void Motor_TEST(void)
{
//	u8 key;
//	int SpeedA=0;
//	int SpeedB=0;
//	int SpeedC=0;
//	int SpeedD=0;
//	Motor_Init();
//	OLED_Clear();
//	OLED_ShowString(0,0,"key1-STOP",12);
//  OLED_ShowString(0,16,"key2-run",12);
//	OLED_ShowString(0,32,"key3:V+,key4:V-",12);
//  OLED_ShowString(0,48,"V=",12);
//	while(1)
//	{
//		key=KEY_Scan(0);
//		if(key==KEY1_PRES)
//		{
//			 SpeedA=0;
//	     SpeedB=0;
//	     SpeedC=0;
//	     SpeedD=0;			
//			Motor_SetAB(SpeedA,SpeedB);
//			Motor_SetCD(SpeedC,SpeedD);	
//			
//		}
//		else if(key==KEY2_PRES)
//		{
//			Motor_SetAB(SpeedA,SpeedB);
//			Motor_SetCD(SpeedC,SpeedD);	
//      Delay_ms(2000);
//			SpeedA=0;
//	    SpeedB=0;
//	     SpeedC=0;
//	     SpeedD=0;			
//			Motor_SetAB(SpeedA,SpeedB);
//			Motor_SetCD(SpeedC,SpeedD);	
//		}
//		else if(key==KEY3_PRES)
//		{
//			SpeedA=SpeedA+500;
//	    SpeedB=SpeedB+500;
//	    SpeedC=SpeedC+500;
//	    SpeedD=SpeedD+500;
//		}
//		else if(key==KEY4_PRES)
//		{
//			SpeedA=SpeedA-500;
//	    SpeedB=SpeedB-500;
//	    SpeedC=SpeedC-500;
//	    SpeedD=SpeedD-500;
//		}
//		else if(key==KEY5_PRES)
//		{			
//			 SpeedA=0;
//	     SpeedB=0;
//	     SpeedC=0;
//	     SpeedD=0;			
//			Motor_SetAB(SpeedA,SpeedB);
//			Motor_SetCD(SpeedC,SpeedD);	
//			return;
//		}
//		else if(key==KEY6_PRES)
//		{

//		}
//		OLED_ShowIntNum(16,48,SpeedA,5,12);
//		OLED_Refresh_Gram();
//	}
}


