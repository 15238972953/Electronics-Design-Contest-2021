#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)
#define KEY3 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define KEY4 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEY5 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY6 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)
#define KEY7 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)

/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/

#define KEY1_PRES 	1
#define KEY2_PRES	  2
#define KEY3_PRES	  3
#define KEY4_PRES	  4
#define KEY5_PRES	  5
#define KEY6_PRES	  6
#define KEY7_PRES	  7
void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	
void mode_set(void);
#endif


