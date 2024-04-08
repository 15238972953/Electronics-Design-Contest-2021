#ifndef _PWM_H
#define _PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//������������ʹ�ܿ���io�ڶ���
//DIR_1,ENA_1 ----���ߵ������
//DIR_2,ENA_2 ----�԰ڵ������
//DIR_1,DIR_2 ----Ϊ0ʱ�����������Ϊ1ʱ���������
//ENA_1,ENA_2 ----Ϊ0ʱ�����ʧ�ܿ���ת����Ϊ1ʱ�����ʹ�ܲ���ת��

//#define DIR_1 PBout(12)	  
//#define DIR_2 PAout(9)	 
//#define ENA_1 PBout(13)	 
//#define ENA_2 PAout(10)	

//void DIR_Init(void);


#define ES08_X_(yuntai) TIM_SetCompare2(TIM2,yuntai);    ///�ı����������ֵ�Ϳ��Ըı��������     //*��̨��ת      min--1750       max--1950
#define ES08_Z_(zhijia) TIM_SetCompare4(TIM3,zhijia);    ///�ı����������ֵ�Ϳ��Ըı��������     //*֧��ת��      min--1747   max--1947

void TIM9_PWM_Init(u32 arr,u32 psc);
void TIM10_PWM_Init(u32 arr,u32 psc);
void TIM2_PWM_Init(u32 arr,u32 psc);
void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM8_Steer_Init(u32 arr,u32 psc);
void TIM1_Pwm_Init(u32 arr,u32 psc);
#endif
