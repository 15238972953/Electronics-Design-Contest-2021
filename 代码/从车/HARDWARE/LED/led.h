#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define LED1 PCout(13)	// DS0
#define LED2 PCout(4)	// DS1	 
#define LED3 PCout(5)

#define rgb1 PAout(2)	// DS0
#define rgb2 PEout(12)	// DS1	 
#define rgb3 PEout(13)
#define led1 PAout(2)	// DS0
#define led2 PEout(6)	// DS1	 
#define led3 PEout(5)

void rgb_red(void);

void rgb_green(void);

void rgb_out(void);


void LED_Init(void);//��ʼ��		 				    
#endif
