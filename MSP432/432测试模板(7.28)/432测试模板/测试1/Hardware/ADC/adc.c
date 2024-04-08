/*
******************************************************************************
*Filename      :adc.c
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛
******************************************************************************
*/

#include "adc.h"
#include "delay.h"
#include "oled.h"
#include "key.h"
/*
********************************************************************************************************************
*                  void ADC_Init(void)
*
*Description : ADC初始化
*Returns     : none
*Notes       : 暂时只能实现单通道连续采样，多通道时始终干扰，只能采取最后初始化的值
********************************************************************************************************************
*/
void ADC_Init(void)
{
	ADC14_enableModule();                                                                // 使能ADC模块
	
	
	ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4,0);           // ADC时钟4.1 a12

/*A8   P4.5   POWER_ADC*/
//	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,GPIO_PIN5,GPIO_TERTIARY_MODULE_FUNCTION);
//	ADC14_configureSingleSampleMode(ADC_MEM8, true);                										 // 设置单通道采样，数据保存在MEM0
//	ADC14_configureConversionMemory(ADC_MEM8,ADC_VREFPOS_AVCC_VREFNEG_VSS,ADC_INPUT_A12, false);// 初始化AD/DA存储器MEM0 , 采用标准参考电压3.3V, 接口为A12
//	ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);   																 // 使能采样定时器，自动循环采样
//	ADC14_enableInterrupt(ADC_INT12);																										 // 使能接口为A12的ADC中断 

///*A12   P4.1   ADC*/
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,GPIO_PIN1,GPIO_TERTIARY_MODULE_FUNCTION);
	ADC14_configureSingleSampleMode(ADC_MEM12, true);                										 // 设置单通道采样，数据保存在MEM0
	ADC14_configureConversionMemory(ADC_MEM12,ADC_VREFPOS_AVCC_VREFNEG_VSS,ADC_INPUT_A12, false);// 初始化AD/DA存储器MEM0 , 采用标准参考电压3.3V, 接口为A8
	ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);   																 // 使能采样定时器，自动循环采样
	ADC14_enableInterrupt(ADC_INT12);																										 // 使能ADC中断

///*A13   P4.0   ADC*/	
//	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,GPIO_PIN0,GPIO_TERTIARY_MODULE_FUNCTION);
//	ADC14_configureSingleSampleMode(ADC_MEM13, true);                										 // 设置单通道采样，数据保存在MEM0
//	ADC14_configureConversionMemory(ADC_MEM13,ADC_VREFPOS_AVCC_VREFNEG_VSS,ADC_INPUT_A13, false);// 初始化AD/DA存储器MEM0 , 采用标准参考电压3.3V, 接口为A8
//	ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);   																 // 使能采样定时器，自动循环采样
//	ADC14_enableInterrupt(ADC_INT13);																										 // 使能ADC中断
	
	ADC14_enableConversion();																														 // 开启转换
	ADC14_toggleConversionTrigger();
}


float ADC_get10times(void)
{
	int i=0;
	float sumtemp=0;
	float adcResult=0;
	for(i=0;i<10;i++)
	{
		  adcResult = ADC14_getResult(ADC_MEM12);
			
      adcResult=adcResult*(3.34/16384); //转换为所测得电压
			sumtemp= adcResult+sumtemp;
			Delay_ms(10);
	}
	adcResult=sumtemp/10;
	return  adcResult;
//			if(i<10)
//		{
//		
//			i++;
//	  }
//		else
//		{
//			adcResult=sumtemp/10;
//			return  adcResult;
//		}
}

float TEMP_Get(void)
{
	float adcResult=0;
	float tem;
	adcResult=ADC_get10times();
	adcResult=adcResult+0.036f;//温度检测模块校准
	tem=2.084f*adcResult*adcResult*adcResult-12.14f*adcResult*adcResult-174.9f*adcResult+204;//计算出温度值
  return tem;	
}

void ADC_Temp_TEST(void)
{ 
	float temp;
	u8 key;
	OLED_Clear();
	ADC_Init();
	OLED_ShowString(16,16,"Temp:",12);
	while(1)
	{
		temp=TEMP_Get();
	  OLED_Show3FNum(76,16,temp,3,3,12);
		key=KEY_Scan(0);
		if(key==KEY5_PRES)
			break;
	}
	
}




