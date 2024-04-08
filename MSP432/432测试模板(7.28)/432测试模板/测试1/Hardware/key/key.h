/*
******************************************************************************
*Filename      :key.c
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛：KEY
******************************************************************************
*/

#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "include.h"

//#define KEY1    	P2in(5)
//#define KEY2  	  P2in(7)

#define KEY1    	P4in(6)
#define KEY2  	  P4in(7)
#define KEY3    	P5in(0)
#define KEY4  	  P5in(1)
#define KEY5    	P5in(2)
#define KEY6  	  P5in(3)

#define KEY1_PRES	1		//KEY1
#define KEY2_PRES	2		//KEY2
#define KEY3_PRES	3		//KEY3
#define KEY4_PRES	4		//KEY4
#define KEY5_PRES	5		//KEY5
#define KEY6_PRES	6		//KEY6


//#define KEY1_PORT GPIO_PORT_P2
//#define KEY1_PIN  GPIO_PIN5

//#define KEY2_PORT GPIO_PORT_P2
//#define KEY2_PIN  GPIO_PIN7


#define KEY1_PORT GPIO_PORT_P4
#define KEY1_PIN  GPIO_PIN6

#define KEY2_PORT GPIO_PORT_P4
#define KEY2_PIN  GPIO_PIN7

#define KEY3_PORT GPIO_PORT_P5
#define KEY3_PIN  GPIO_PIN0

#define KEY4_PORT GPIO_PORT_P5
#define KEY4_PIN  GPIO_PIN1

#define KEY5_PORT GPIO_PORT_P5
#define KEY5_PIN  GPIO_PIN2

#define KEY6_PORT GPIO_PORT_P5
#define KEY6_PIN  GPIO_PIN3


void Key_Init(void);         				//按键初始化
u8   KEY_Scan(u8 mode);							//按键扫描（值传递）
void Key_Interrupt_Init(void);			//按键中断
		
#endif

