/*
********************************************************************************************************
�ļ�����xunji.c
��  �ܣ�С��ѭ������
��  ע��	
��  ����
��  �ߣ�huamo
��  ��: 
*********************************************************************************************************
*/

#include "xunji.h"
#include "delay.h"
#include "stm32f4xx_gpio.h"
#include "adc.h"

//**********************************ǰѭ����ʼ��*************************************//
void XUNJI_Front_GPIO_Init(void)
{		
  
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//??GPIOF??
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//??GPIOF??
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//??GPIOF??
  //GPIOF9,F10?????
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??	
	GPIO_Init(GPIOE, &GPIO_InitStructure);//???	
	
	  //GPIOF9,F10?????
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??	
	GPIO_Init(GPIOC, &GPIO_InitStructure);//???	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//???	
	
}

//********************************��ȡǰѭ��ֵ***************************************//
void Read_Front_xunji_Date(void)
{
 xunji_R_1 ;
 xunji_R_2 ;
 xunji_F ;  
 xunji_L_2; 
 xunji_L_1 ;
}


