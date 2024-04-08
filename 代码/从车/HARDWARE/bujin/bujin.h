#ifndef __BUJIN_H
#define __BUJIN_H
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
