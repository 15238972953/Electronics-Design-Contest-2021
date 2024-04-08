#include "bujin.h" 
#include "oled.h" 
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void BUJIN_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOF时钟

  //PUL引脚 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_15|GPIO_Pin_12;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO

	GPIO_SetBits(GPIOA, GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_15|GPIO_Pin_12);//GPIOF9,F10设置高，灯灭
	
	//ENA引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10|GPIO_Pin_11);//GPIOF9,F10设置高，灯

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOE, GPIO_Pin_8|GPIO_Pin_9);//GPIOF9,F10设置高，灯
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOD, GPIO_Pin_10|GPIO_Pin_11);//GPIOF9,F10设置高，灯
	
}

int SPULA;
int SPULB;
int SPULC;
int SPULD;

int flagA;//启动标志位
int flagB;
int flagC;
int flagD;

int SpeedA=50;
int SpeedB=50;
int SpeedC=50;
int SpeedD=50;

int countA=0;
int countB;
int countC;
int countD;

void Step_Angle_Control(u8 Which,int dir,int Angle)
{
	switch(Which)
	{
		case 1:bujin_A_control(dir,Angle);
					 break;	
		case 2:bujin_B_control(dir,Angle);
					 break;	
		default:break;
	}	
}


/////////////////////////////////////////定时器1每10us进一次中断*///////////////////////////////////////////////
void bujin_A_control(int dir,int angle)//四分频，一个脉冲0.45°
{  
	 countA=0;
	 flagA=1;
	 ena1=1;
	 dir1=dir;
	 SPULA=angle/0.45;	
}
void bujin_B_control(int dir,int angle)//四分频，一个脉冲0.45°
{  
	 countB=0;
	 flagB=1;
	 ena2=1;
	 dir2=dir;
	 SPULB=angle/0.45;	
}



//void TIM1_Step_Init(u16 per,u16 psc)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecture;
//NVIC_InitTypeDef NVIC_InitStructure;
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);/*?????1???*/


//NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;/*???1???????*/
//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;/*???1???????*/
//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;/*?????*/
//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;/*?????*/
//NVIC_Init(&NVIC_InitStructure);/*??????,?????*/

//TIM_TimeBaseInitStrecture.TIM_Period = per;/*??????*/
//TIM_TimeBaseInitStrecture.TIM_Prescaler = psc;/*???*/
//TIM_TimeBaseInitStrecture.TIM_ClockDivision = TIM_CKD_DIV1;/*????*/
//TIM_TimeBaseInitStrecture.TIM_CounterMode = TIM_CounterMode_Up;/*????*/
//TIM_TimeBaseInitStrecture.TIM_RepetitionCounter = 0;/*???????*/
//TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrecture);/*???*/

//TIM_ClearFlag(TIM1,TIM_FLAG_Update);/*??????*/
//TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);/*????*/
//TIM_Cmd(TIM1,ENABLE);/*????*/
//}


////void TIM1_UP_TIM10_IRQHandler(void)
////{
////	static unsigned int MS6=0,MS7=0,MS8=0,MS9=0;
////	if (TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)
////	{
////		if(flagA==1)
////		{   
////			if(countA<=2*SPULA*SpeedA)
////    	{		
////				MS6++;
////        countA++;	
////       				
////				if(MS6>=SpeedA)
////					 { 
////					 LED1=!LED1;
////					 pul1=!pul1;
////					 MS6=0;
////					 }
////		  }		 
////	  }
////		if(flagB==1)
////		{   
////			if(countB<=2*SPULB*SpeedB)
////    	{		
////				MS7++;
////        countB++;	
////       				
////				if(MS7>=SpeedB)
////					 { 
////					 LED2=!LED2;
////					 pul2=!pul2;
////					 MS7=0;
////					 }
////		  }		 
////	  }
////		
////		
//// TIM_ClearFlag(TIM1,TIM_FLAG_Update);/*?????*/
////}
////  
////}


void TIM6_Cnt_Init(u16 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/***********************Clock initial****************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //??TIM5??
	
	/***********************Timer initial****************************************/	 
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//???TIM5
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //?????5????0.................................................
	TIM_Cmd(TIM6,ENABLE); //?????6
	
	 /***********************NVIC initial****************************************/
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; //???5??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

void TIM6_DAC_IRQHandler(void)          
{
	static unsigned int MS6=0,MS7=0,MS8=0,MS9=0;
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET)   //时间到了
	{ 
		if(flagA==1)
		{   
			if(countA<=2*SPULA*SpeedA)
    	{		
				MS6++;
        countA++;	
       				
				if(MS6>=SpeedA)
					 { 
					 LED1=!LED1;
					 pul1=!pul1;
					 MS6=0;
					 }
		  }		 
	  }
		if(flagB==1)
		{   
			if(countB<=2*SPULB*SpeedB)
    	{		
				MS7++;
        countB++;	
       				
				if(MS7>=SpeedB)
					 { 
					 LED2=!LED2;
					 pul2=!pul2;
					 MS7=0;
					 }
		  }		 
	  }
		TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);//清中断	
}

}
