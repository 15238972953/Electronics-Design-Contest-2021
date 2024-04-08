/*
******************************************************************************
*Filename      :adc.h
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛：LED and BEEP
******************************************************************************
*/

#ifndef __ADC_H
#define __ADC_H
#include  "sys.h"

void ADC_Init(void);
float ADC_get10times(void);
float TEMP_Get(void);
void ADC_Temp_TEST(void);
#endif

