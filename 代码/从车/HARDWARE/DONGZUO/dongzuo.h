#ifndef __DONGZUO_H
#define __DONGZUO_H
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

void saoma_shibie_duoji_low(void);
void saoma_shibie_duoji_high(void);

void shouqu_First_high(void);
void tai_First_high(void);

void jiaqu_First_high(void);
void jiaqu_Third_high(void);
void jiaqu_Second_high(void);

void fang_First_high(void);
void fang_Second_high(void);
void fang_Third_high(void);

void jiaqu_Third_low(void);
void jiaqu_First_low(void);
void jiaqu_Second_low(void);
void fang_Third_low(void);
void fang_Second_low(void);
void fang_First_low(void);
#endif
