

/*
********************************************************************************************************************
*Filename        :Ultrasonic.c
*Programmer(s)   :Lab 416
*Description     :2017????:UltrasonicWave??

									TRIG--PB10
									ECHO--PB11
							
	TIM5_Sonic_Cap_Init(0XFFFFFFFF,84-1);
	TIM2_Sonic_Cap_Init(0XFFFFFFFF,84-1);		
********************************************************************************************************************
*/

/*
F T5C3
B T2C4
R1 T5C4
R2 T2C3
L1 T5C2
L2 T5C1
*/
#include "sonic.h"
#include "delay.h"
#include "filter.h"
#include "oled.h"
#include "math.h"
#include "usartdma.h"

/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
******************************************************************************************************************
*/


u8     TIM5CH1_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH1_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)
u8     TIM5CH2_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH2_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)
u8     TIM5CH3_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH3_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)
u8     TIM5CH4_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH4_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)




long long tempF=0;//?
long long tempB=0;//?
long long tempL_1=0;
long long tempL_2=0;
long long tempR_1=0;
long long tempR_2=0;

int TEMPA_1=0;
int TEMPA_2=0;
int TEMPA_3=0;
int TEMPA_4=0;
int TEMPA_5=0;
int TEMPA_6=0;

SonicDis Sonic_Dis={0,0,0,0,0,0};





Filter_Struct SonicA1_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA2_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA3_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA4_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA5_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA6_Filter = {0,0,0,0,{0}};


/*
********************************************************************************************************************
*                  void  Uitra_Init(void)
*
*Description    :??????
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
//void Ultra_Init(void)
//{
//  GPIO_InitTypeDef    GPIO_InitStructure;	
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//??TRIG3??
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
//	 /***********************GPIO initial****************************************/
//		 
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//TRIG3(PB8)
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
//  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//??????
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//????100MHz        
//  GPIO_Init(GPIOE, &GPIO_InitStructure);//???GPIOE
//  GPIO_ResetBits(GPIOE, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);//TRIG3=0??(PB8)
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;//TRIG3(PB10)
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
//  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//??????
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//????100MHz        
//  GPIO_Init(GPIOB, &GPIO_InitStructure);//???GPIOB
//  GPIO_ResetBits(GPIOB, GPIO_Pin_8);//TRIG3=0(PB10)
//	
//}
void Ultra_Init(void)
{
  GPIO_InitTypeDef    GPIO_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//??TRIG3??
	 /***********************GPIO initial****************************************/
		 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;//TRIG3(PB8)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//??????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//????100MHz        
  GPIO_Init(GPIOE, &GPIO_InitStructure);//???GPIOE
	
  GPIO_ResetBits(GPIOE,GPIO_Pin_12|GPIO_Pin_13);//TRIG3=0??(PB8)
	
}

/***************************************************************************************
F  T5C3   5??
B  T2C4   1
R2 T2C3   3
L2 T5C1   2
R1 T5C4   4
L1 T5C2
***************************************************************************************/

void Sonic_Get_Distance()
{
		if(TIM5CH4_CAPTURE_STA&0X80)//???????????
		{
				tempF=TIM5CH4_CAPTURE_STA&0X3F;
//				tempF*=0XFFFFFFFF;         //??????
				tempF+=TIM5CH4_CAPTURE_VAL;//?????????
				TIM5CH4_CAPTURE_STA=0;     //???????
		}
		 TEMPA_5=(tempF*340/200)/100; //??????cm
		 Enaverage_Filter(&SonicA5_Filter,TEMPA_5,9, &Sonic_Dis.A_4);

//		if(TIM5CH1_CAPTURE_STA&0X80)//???????????
//		{
//				tempB=TIM5CH1_CAPTURE_STA&0X3F; 
////				tempB*=0XFFFFFFFF;         //??????
//				tempB+=TIM5CH1_CAPTURE_VAL;//?????????
//				TIM5CH1_CAPTURE_STA=0;     //???????
//		}
//		TEMPA_1=(tempB*340/200)/100; //??????cm
//		Enaverage_Filter(&SonicA1_Filter,TEMPA_1,7, &Sonic_Dis.A_1);

//		if(TIM5CH2_CAPTURE_STA&0X80)//???????????
//		{
//				tempL_1=TIM5CH2_CAPTURE_STA&0X3F; 
////				tempB*=0XFFFFFFFF;         //??????
//				tempL_1+=TIM5CH2_CAPTURE_VAL;//?????????
//				TIM5CH2_CAPTURE_STA=0;     //???????
//		}
//		TEMPA_4=(tempL_1*340/200)/100; //??????cm
//		Enaverage_Filter(&SonicA4_Filter,TEMPA_4,7, &Sonic_Dis.A_4);
//			
    if(TIM5CH3_CAPTURE_STA&0X80)//???????????
		{
				tempL_2=TIM5CH3_CAPTURE_STA&0X3F; 
//				tempB*=0XFFFFFFFF;         //??????
				tempL_2+=TIM5CH3_CAPTURE_VAL;//?????????
				TIM5CH3_CAPTURE_STA=0;     //???????
		}
		TEMPA_2=(tempL_2*340/200)/100; //??????cm
		Enaverage_Filter(&SonicA2_Filter,TEMPA_2,5, &Sonic_Dis.A_2);
			
//		if(TIM2CH4_CAPTURE_STA&0X80)//???????????
//		{
//				tempR_1=TIM2CH4_CAPTURE_STA&0X3F; 
////				tempB*=0XFFFFFFFF;         //??????
//				tempR_1+=TIM2CH4_CAPTURE_VAL;//?????????
//				TIM2CH4_CAPTURE_STA=0;     //???????
//		}
//		TEMPA_3=(tempR_1*340/200)/100; //??????cm
//		Enaverage_Filter(&SonicA3_Filter,TEMPA_3,5, &Sonic_Dis.A_3);
//			
//		if(TIM2CH3_CAPTURE_STA&0X80)//???????????
//		{
//				tempR_2=TIM2CH3_CAPTURE_STA&0X3F; 
////				tempB*=0XFFFFFFFF;         //??????
//				tempR_2+=TIM2CH3_CAPTURE_VAL;//?????????
//				TIM2CH3_CAPTURE_STA=0;     //???????
//		}
//		TEMPB_3=(tempR_1*340/200)/100; //??????cm
//		Enaverage_Filter(&SonicB3_Filter,TEMPB_3,7, &Sonic_Dis.B_3);
//		if(Sonic_Dis.A_1>255)
//			Sonic_Dis.A_1=255;
//		else
//			Sonic_Dis.A_1=Sonic_Dis.A_1;
//		
//		if(Sonic_Dis.A_2>255)
//			Sonic_Dis.A_2=255;
//		else
//			Sonic_Dis.A_2=Sonic_Dis.A_2;
//		
//		if(Sonic_Dis.A_3>255)
//			Sonic_Dis.A_3=255;
//		else
//			Sonic_Dis.A_3=Sonic_Dis.A_3;
//		
//		if(Sonic_Dis.A_4>255)
//			Sonic_Dis.A_4=255;
//		else
//			Sonic_Dis.A_4=Sonic_Dis.A_4;
//		
//		if(Sonic_Dis.A_5>255)
//			Sonic_Dis.A_5=255;
//		else
//			Sonic_Dis.A_5=Sonic_Dis.A_5;
//		
//		Sonic_Dis.B_1=rec_data_u1[0];
//		Sonic_Dis.B_2=rec_data_u1[1];
//		Sonic_Dis.B_3=rec_data_u1[2];
//		Sonic_Dis.B_4=rec_data_u1[3];
//		Sonic_Dis.B_5=rec_data_u1[4];


}



/******************************************************************************************************************
*                                 TIM5_Tim_Init(u32 arr,u16 psc)
*
*Description : ???5???,???1ms
*Arguments   : arr:????   psc:?????
*Returns     : none
*Notes       : ???????????:Tout=((arr+1)*(psc+1))/Ft us.  
               Ft=???????,??:Mhz
*******************************************************************************************************************
*/


void TIM5_Sonic_Cap_Init(u32 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM5_ICInitStructure;
	
	/***********************Clock initial****************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);      
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/***********************GPIO initial****************************************/	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2|GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//????????
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;//????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//????100MHz 
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
	
	 /***********************Timer initial****************************************/	 
	TIM_TimeBaseStructure.TIM_Prescaler=psc;//?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//??????
	TIM_TimeBaseStructure.TIM_Period=arr;//??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	
	
	//???TIM2??????
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;//CC1S=04,????? IC4???TI1?
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//?????
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//???TI1?
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//??????,??? 
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ??????? ???
    TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//?????? ,??CC4IE????		
	TIM_ITConfig(TIM5,TIM_IT_CC3,ENABLE);						// ?????? ,??CC2IE????	
	TIM_ITConfig(TIM5,TIM_IT_CC4,ENABLE);						// ?????? ,??CC2IE????	
	
    TIM_Cmd(TIM5,ENABLE );//?????5
	
  /***********************NVIC initial****************************************/
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;//????2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ????
	NVIC_Init(&NVIC_InitStructure);//??????????VIC???	
}

//????
//[7]:0,???????;1,???????.
//[6]:0,????????;1,?????????.
//[5:0]:???????????(??32??????,1us????1,????:4294?)



/*
********************************************************************************************************************
*                  void TIM5_IRQHandler(void)
*
*Description    :???5?????? 
*Arguments   : none
*Returns     : TRIGx  ???x
*Notes       : none
*F  T5C3   5??
 B  T2C4   1
 R2 T2C3   3
 L2 T5C1   2
 R1 T5C4   4
 L1 T5C2
********************************************************************************************************************
*/

void TIM5_IRQHandler(void)
{
//----------------------------------------------------------------------------------------------------------------- 
//	if((TIM5CH1_CAPTURE_STA&0X80)==0)//??????	
//	{
//		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
//		{
//			if(TIM5CH1_CAPTURE_STA&0X40)        //?????????
//			{
//				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//??????
//				{
//					TIM5CH1_CAPTURE_STA|=0X80;	      //?????????
//					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
//				}else TIM5CH1_CAPTURE_STA++;
//			}
//		}
//		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//????4??????
//		{
//			if(TIM5CH1_CAPTURE_STA&0X40)//???????? 		
//			{
//				TIM5CH1_CAPTURE_STA|=0X80;	//??????????????
//				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//????????.
//				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
//			}else //????,????????
//			{
//				TIM5CH1_CAPTURE_STA=0;	//??
//				TIM5CH1_CAPTURE_VAL=0;
//				TIM5CH1_CAPTURE_STA|=0X40;		//?????????
//				TIM_Cmd(TIM5,DISABLE); 	//?????2
//				TIM_SetCounter(TIM5,0);
//				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
//				TIM_Cmd(TIM5,ENABLE ); 	//?????2
//			}
//		}
//	}
//----------------------------------------------------------------------------------------------------------------- 
	
//	if((TIM5CH2_CAPTURE_STA&0X80)==0)//??????	
//	{
//		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
//		{
//			if(TIM5CH2_CAPTURE_STA&0X40)        //?????????
//			{
//				if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//??????
//				{
//					TIM5CH2_CAPTURE_STA|=0X80;	      //?????????
//					TIM5CH2_CAPTURE_VAL=0XFFFFFFFF;
//				}else TIM5CH2_CAPTURE_STA++;
//			}
//		}
//		if(TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//????4??????
//		{
//			if(TIM5CH2_CAPTURE_STA&0X40)//???????? 		
//			{
//				TIM5CH2_CAPTURE_STA|=0X80;	//??????????????
//				TIM5CH2_CAPTURE_VAL=TIM_GetCapture2(TIM5);//????????.
//				TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
//			}else //????,????????
//			{
//				TIM5CH2_CAPTURE_STA=0;	//??
//				TIM5CH2_CAPTURE_VAL=0;
//				TIM5CH2_CAPTURE_STA|=0X40;		//?????????
//				TIM_Cmd(TIM5,DISABLE ); 	//?????2
//				TIM_SetCounter(TIM5,0);
//				TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
//				TIM_Cmd(TIM5,ENABLE ); 	//?????2
//			}
//		}
//	}
	
	if((TIM5CH3_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
		{
			if(TIM5CH3_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM5CH3_CAPTURE_STA|=0X80;	      //?????????
					TIM5CH3_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH3_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//????4??????
		{
			if(TIM5CH3_CAPTURE_STA&0X40)//???????? 		
			{
				TIM5CH3_CAPTURE_STA|=0X80;	//??????????????
				TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);//????????.
				TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM5CH3_CAPTURE_STA=0;	//??
				TIM5CH3_CAPTURE_VAL=0;
				TIM5CH3_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM5,DISABLE ); 	//?????2
				TIM_SetCounter(TIM5,0);
				TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM5,ENABLE ); 	//?????2
			}
		}
	}
	
	if((TIM5CH4_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
		{
			if(TIM5CH4_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM5CH4_CAPTURE_STA|=0X80;	      //?????????
					TIM5CH4_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH4_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)//????4??????
		{
			if(TIM5CH4_CAPTURE_STA&0X40)//???????? 		
			{
				TIM5CH4_CAPTURE_STA|=0X80;	//??????????????
				TIM5CH4_CAPTURE_VAL=TIM_GetCapture4(TIM5);//????????.
				TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM5CH4_CAPTURE_STA=0;	//??
				TIM5CH4_CAPTURE_VAL=0;
				TIM5CH4_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM5,DISABLE); 	//?????2
				TIM_SetCounter(TIM5,0);
				TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM5,ENABLE ); 	//?????2
			}
		}
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //???????
}

void Ultrasonic_Trig_Start(void)
{
//	 Trig1_on(); //F_Right_Trig_on()
//	 delay_us(20);  //??10us??
//	 Trig1_off(); //F_Right_Trig_off()
//	 Trig2_on(); //F_Right_Trig_on()
//	 delay_us(20); //??10us??
//	 Trig2_off(); //F_Right_Trig_off()
//	
	 Trig3_on(); //F_Right_Trig_on()
	 delay_us(20);  //??10us??
	 Trig3_off(); //F_Right_Trig_off()
	
	 Trig4_on(); //F_Right_Trig_on()
	 delay_us(20);  //??10us??
	 Trig4_off(); //F_Right_Trig_off()
//     Trig5_on(); //F_Right_Trig_on()
//	 delay_us(20);  //??10us??
//	 Trig5_off(); //F_Right_Trig_off()
//	 Trig6_on(); //F_Right_Trig_on()
//	 delay_us(20);  //??10us??
//	 Trig6_off(); //F_Right_Trig_off()
}


int Sonic_Length(float L1,float L2)
{	
	float ang,L3,L4,L_b=136,d_L;//10.9
	int Length;
	d_L=fabs(L1-L2);
	if(d_L>=1300.0f)//???
  {
		if(L1>=L2)Length=L2;
		else Length=L1;
		return Length;
	}	
	if(d_L>=80.0f)d_L=80.0f;
	else d_L=d_L;
	ang=atan(L_b/d_L);//????
	L3=L1*sin(ang);
	L4=L2*sin(ang);
	Length=(L3+L4)/2.0f;	
  return Length;
}


int Sonic_Length_l(float L1,float L2)
{	
	float ang,L3,L4,L_b=61.0f,d_L;//10.9
	int Length;
	d_L=fabs(L1-L2);
	if(d_L>=130.0f)
  {
		if(L1>=L2)Length=L2;
		else Length=L1;
		return Length;
	}	
	if(d_L>=80.0f)d_L=80.0f;
	else d_L=d_L;
	ang=atan(L_b/d_L);//????
	L3=L1*sin(ang);
	L4=L2*sin(ang);
	Length=(L3+L4)/2.0f;	
  return Length;
}


void Ultra_Test1(void)
{	
	  OLED_ShowNum(0,0,Sonic_Dis.A_1 ,3,12);
	  OLED_ShowNum(50,0,Sonic_Dis.A_2,3,12);
	  OLED_ShowNum(0,15,Sonic_Dis.A_3 ,3,12);
	  OLED_ShowNum(50,15,Sonic_Dis.A_4,3,12);



}


void Ultra_Test2(void)
{	
	  OLED_ShowNum(0,0, TEMPA_1,3,12);
	  OLED_ShowNum(50,0,TEMPA_2,3,12);
	  OLED_ShowNum(0,15,TEMPA_3 ,3,12);
	  OLED_ShowNum(50,15,TEMPA_4,3,12);
	  OLED_ShowNum(0,30,TEMPA_5 ,3,12);
	  OLED_ShowNum(50,30,TEMPA_6 ,3,12);
	
	
	
//	  delay_ms(1000);	
//	  OLED_ShowNum(0,0,Sonic_Dis.B_1,3,12);
//	  OLED_ShowNum(50,0,Sonic_Dis.B_2,3,12);
//	  OLED_ShowNum(0,15,Sonic_Dis.B_3 ,3,12);
//	  OLED_ShowNum(50,15,Sonic_Dis.B_4,3,12);
//	  OLED_ShowNum(0,30,Sonic_Dis.B_5 ,3,12);
//	  delay_ms(1000);
//	 OLED_ShowNum(50,30,Sonic_Dis.B_5 ,3,12);

}

