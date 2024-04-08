#ifndef __BUJIN_H
#define __BUJIN_H
#include "sys.h"

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


//LED端口定义

#define dir1 PEout(8)//  bujin1   
#define ena1 PEout(9)//
#define pul1 PAout(8)// 

#define dir2 PAout(12)// bujin2
#define ena2 PAout(15)// 
#define pul2 PAout(9)// 

#define dir3 PBout(11)// bujin3
#define ena3 PBout(10)//
#define pul3 PAout(10)//

#define dir4 PDout(10)// bujin4
#define ena4 PDout(11)//
#define pul4 PAout(11)//


void BUJIN_Init(void);	
void TIM14_PWM_Init(u16 per,u16 psc);
void TIM1_Step_Init(u16 per,u16 psc);

void Step_Angle_Control(u8 Which,int dir,int Angle);
void bujin_A_control(int dir,int angle);
void bujin_B_control(int dir,int angle);

#endif
