/*
******************************************************************************
*Filename      :adc.h
*Programmer(s) :����ͺ����
*Description   :2019����
******************************************************************************
*/

#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 

typedef struct ADC_Stru
{
	u8		Complete;
	u8		Filter_Cnt;
	u16		Get_Now;		//��ǰ����ֵ
	u16		Get_Last;		//��һ�β���ֵ
	u16		Dis_Last;		//��һ����ʾֵ
	u16		Dis_Cache;		//������ʾֵ
	u16		Dis_Now;		//��ǰ��ʾֵ
	u16		Dis_His[15];	//������ʷֵ
}Adc_Stru;

extern Adc_Stru AdcData;
extern float power_vol;
extern float ch11_Vol;
extern float ch12_Vol;	

void Adc_Init(void);
u16  Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);
float Get_Vol(u8 ch);
void Get_power_Vol(void);
void Get_ch11_Vol(void);
void Get_ch12_Vol(void);
#endif 















