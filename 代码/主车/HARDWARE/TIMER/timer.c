#include "timer.h"
#include "exti.h"
#include "bujin.h"

int zd_site=0;

void TIM7_Cnt_Init(u16 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/***********************Clock initial****************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE); //??TIM5??
	
	/***********************Timer initial****************************************/	 
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//???TIM5
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //?????5????0.................................................
	TIM_Cmd(TIM7,ENABLE); //?????6
	
	 /***********************NVIC initial****************************************/
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //???5??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/*******************************************步进调速2，不分频，不用专属定时器*/////////////////////////////////////////////
/*******************************************不调速就很简单，同思路  400转一圈*/////////////////////////////////////////////
//int count2=80;
//int Num=0;
//int t=0;
//int m=0;
//void bujin_action(int dianping,int pulse)
//{ 	
//  
//  	  dir1=dianping;
//	    t++;
//	    m++;
//	
//	if(Num<pulse*4/5)
//	{		
//		if(m==60&&(count2>=20&&count2<=80))
//			{
//				count2=count2-2;
//				m=0;
//			}

//  if(t>=count2)
//	{	 ena1=1;		
//		Num++;											
//												
//		pul1=!pul1;
//    t=0;		
//   }
// }	
//	
//		if(Num>=pulse*4/5&&Num<pulse)
//		   {
//			   
//			if(m==60&&count2<=80)
//			{ 
//				count2=count2+2;		
//          m=0;				
//			}		
//			
//			if(t>=count2)
//			{	
//				Num++;											
//				ena1=1;												
//				pul1=!pul1; 
//        t=0;					
//			 }
//	  }		 
//}
/*******************************************步进调速3，不分频，用专属定时器*14       */////////////////////////////////////////////
int aa;
int bb=600;
int c;
int d=200;
int site=0;
int pulse;
int count;
//void bujin_action(int dianping,int pulse)
//{		
//  	dir1=dianping;
//    count++;	
//       aa++;
//			if((aa>8)&&(bb>=200))
//			{bb--;
//				aa=0;
//			}
//		if(count<pulse*4/5)
//		   {		
//				  TIM14_PWM_Init(bb,83);
//					 Motor(bb/2);   
//       }
//		if(count>pulse*4/5)
//		   {
//			c++;
//			if((c>=1)&&(d<=600))
//			{
//			d++;
//			c=0;	
//			}	
//			TIM14_PWM_Init(d,83);
//		  Motor(d/2);  	 
//       }
//		if(count>=pulse)
//		   {	
//				 Motor(0);  							
//       }	 
//}

//void TIM1_BRK_TIM14_IRQHandler(void)       
//{
//        if(TIM_GetITStatus(TIM14,TIM_IT_Update)==RESET) //????
//        {
//					GPIO_ResetBits(GPIOE,GPIO_Pin_4 );//GPIOF9,F10设置高，灯灭
//		        bujin_action(1,800);
//        }
//        TIM_ClearITPendingBit(TIM14,TIM_IT_Update);  //???????
//}
// int count3=0;



//void TIM7_IRQHandler(void)       
//{
//        if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //????
//   {  
//		 
////	   count3++;
////		 if(Num<1000)
////		 {
////			 if(count3==20)	//X轴正方向   步进电机转一圈 为32mm
////					{						
////						Num++;	
////						dir1=1;									
////						ena1=1;												
////						pul1=!pul1; 							
////						count3=0;		
////				   }						
////		 }
//		 GPIO_ResetBits(GPIOE,GPIO_Pin_4 );//GPIOF9,F10设置高，灯灭
//		 bujin_action(1,800);
//			 
//	}	 
//		 TIM_ClearITPendingBit(TIM7,TIM_IT_Update);        
//}





//void TIM6_Cnt_Init(u16 arr,u32 psc)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	/***********************Clock initial****************************************/
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //??TIM5??
//	
//	/***********************Timer initial****************************************/	 
//  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
//	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
//	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//???TIM5
//	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //?????5????0.................................................
//	TIM_Cmd(TIM6,DISABLE); //?????6
//	
//	 /***********************NVIC initial****************************************/
//	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; //???5??
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //?????1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);	
//}


//void TIM6_DAC_IRQHandler(void)          
//{
//	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET)   //时间到了
//	{ 
////		if(zd_site==3)
////		{	
////     EXTIX3_Init(ENABLE);
////		 TIM_Cmd(TIM6,DISABLE);
////		zd_site=0;
////		}
//		if(zd_site==5)
//		{	
//     EXTIX5_Init(ENABLE);
//		 TIM_Cmd(TIM6,DISABLE);
//		 zd_site=0;
//		}
//	}
//		TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);//清中断
//			

//	
//}
//void TIM9_Cnt_Init(u16 arr,u16 psc)
//{
//        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//        NVIC_InitTypeDef NVIC_InitStructure;

//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  ///??TIM9??       
//        TIM_TimeBaseInitStructure.TIM_Period = arr;         //??????
//        TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
//        TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
//        TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//        TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStructure);//???TIM9
//        TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE); //?????9????
//        TIM_Cmd(TIM9,ENABLE); //?????9

//        NVIC_InitStructure.NVIC_IRQChannel=TIM1_BRK_TIM9_IRQn; //???9??
//        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //?????0
//        NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
//        NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//        NVIC_Init(&NVIC_InitStructure);       
//}

//???9??????
