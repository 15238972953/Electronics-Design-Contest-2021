/*
********************************************************************************************************************
*Filename              :UltrasonicWave.h
*Programmer(s)    :Lab 416
*Description          :UltrasonicWave function
********************************************************************************************************************
*/

#ifndef __sonic_H
#define	__sonic_H

#include "sys.h"

//#define TRIGF   PBout(10) 
//#define TRIGB    PBout(10) 
////#define TRIGL_1  PEout(0) 
////#define TRIGL_2  PBout(8) 
//#define TRIGL_1  PBout(10) 
//#define TRIGR_1  PBout(10)  
//#define TRIGR_2  PBout(10) 

#define U1_DATA_LEN  20

extern u8 rec_data_u1[U1_DATA_LEN];


//#define TRIGALL do{TRIGF=1;TRIGL_1=1;for(i=0;i<750;i++);TRIGF=0;TRIGL_1=0;for(i=0;i<1500;i++);TRIGB=1;TRIGR_1=1;for(i=0;i<750;i++);TRIGB=0;TRIGR_1=0;}while(0);
////#define TRIG_A do{TIM_ITConfig(TIM5,TIM_IT_CC4,ENABLE);TIM_ITConfig(TIM5,TIM_IT_CC2,ENABLE);TIM_ITConfig(TIM2,TIM_IT_CC3,ENABLE);\
////	                TIM_ITConfig(TIM5,TIM_IT_CC1,DISABLE);TIM_ITConfig(TIM5,TIM_IT_CC3,DISABLE);TIM_ITConfig(TIM2,TIM_IT_CC4,DISABLE);\
////                  TRIGF=1;TRIGL_1=1;TRIGR_2=1;for(i=0;i<750;i++);TRIGF=0;TRIGL_1=0;TRIGR_2=0;}while(0);//?
////#define TRIG_B do{TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);TIM_ITConfig(TIM5,TIM_IT_CC3,ENABLE);TIM_ITConfig(TIM2,TIM_IT_CC4,ENABLE);\
////	                TIM_ITConfig(TIM5,TIM_IT_CC4,DISABLE);TIM_ITConfig(TIM5,TIM_IT_CC2,DISABLE);TIM_ITConfig(TIM2,TIM_IT_CC3,DISABLE);\
////                  TRIGB=1;TRIGR_1=1;TRIGL_2=1;for(i=0;i<750;i++);TRIGB=0;TRIGR_1=0;TRIGL_2=0;}while(0);
////	
//inline void TRIG_A (void){int i=0;do{TIM_ITConfig(TIM5,TIM_IT_CC4,ENABLE);TIM_ITConfig(TIM5,TIM_IT_CC2,ENABLE);TIM_ITConfig(TIM2,TIM_IT_CC3,ENABLE);
//	                TIM_ITConfig(TIM5,TIM_IT_CC1,DISABLE);TIM_ITConfig(TIM5,TIM_IT_CC3,DISABLE);TIM_ITConfig(TIM2,TIM_IT_CC4,DISABLE);
//                  TRIGF=1;TRIGL_1=1;TRIGR_2=1;for(i=0;i<750;i++);TRIGF=0;TRIGL_1=0;TRIGR_2=0;}while(0);}
//inline void  TRIG_B(void) {int i=0;do{TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);TIM_ITConfig(TIM5,TIM_IT_CC3,ENABLE);TIM_ITConfig(TIM2,TIM_IT_CC4,ENABLE);\
//	                TIM_ITConfig(TIM5,TIM_IT_CC4,DISABLE);TIM_ITConfig(TIM5,TIM_IT_CC2,DISABLE);TIM_ITConfig(TIM2,TIM_IT_CC3,DISABLE);\
//                  TRIGB=1;TRIGR_1=1;TRIGL_2=1;for(i=0;i<750;i++);TRIGB=0;TRIGR_1=0;TRIGL_2=0;}while(0);}
//		


#define TIME_OUT 10000        //???????????

//#define Trig1_on()  (GPIO_SetBits(GPIOB,GPIO_Pin_9))             //??Front_Trig  F_Right_Trig_on()
//#define Trig1_off() (GPIO_ResetBits(GPIOB,GPIO_Pin_9))           //??Front_Trig  F_Right_Trig_off()

//#define Trig2_on()  (GPIO_SetBits(GPIOB,GPIO_Pin_9))             //??Front_Trig
//#define Trig2_off() (GPIO_ResetBits(GPIOB,GPIO_Pin_9))  

#define Trig3_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_12))             //??Front_Trig
#define Trig3_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_12)) 

#define Trig4_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_13))             //??Front_Trig
#define Trig4_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_13)) 
//				  
//#define Trig5_on()  (GPIO_SetBits(GPIOB,GPIO_Pin_9))             //??Front_Trig
//#define Trig5_off() (GPIO_ResetBits(GPIOB,GPIO_Pin_9)) 
//	
//#define Trig6_on()  (GPIO_SetBits(GPIOB,GPIO_Pin_9))             //??Front_Trig
//#define Trig6_off() (GPIO_ResetBits(GPIOB,GPIO_Pin_9)) 

typedef struct 
{
	
  int A_1;
  int A_2;
	int A_3;
	int A_4;

  int B_1;
  int B_2;
  int B_3;
  int B_4;
  int B_5;

}SonicDis;

extern SonicDis Sonic_Dis;


/*
******************************************************************************************************************
*                                            FUNCTION PROTOTYPES
******************************************************************************************************************
*/

void Ultra_Init(void);//???IO??????
void Ultrasonic_Trig_Start(void);
void Sonic_Get_Distance(void);//????
void Ultra_Test1(void);
void Ultra_Test2(void);
void TIM5_Sonic_Cap_Init(u32 arr,u16 psc);
void TIM2_Sonic_Cap_Init(u32 arr,u16 psc);
void TIM5_IRQHandler(void);
int Sonic_Length(float l1,float l2);
int Sonic_Length_l(float l1,float l2);
void TRIG_A (void);
void  TRIG_B(void);
void Mea_dis_B(void);
#endif 



