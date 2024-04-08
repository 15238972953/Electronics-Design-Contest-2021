/*
******************************************************************************
*Filename      :main.c
*Programmer(s) :����ͺ����
*Description   :2019����
******************************************************************************
*/
#include "adc.h"
#include "filter.h"
#include "delay.h"
FilterStruct ADCStruct = {{0.0},0};
float power_vol;
float ch11_Vol;
float ch12_Vol;
/*
********************************************************************************************************************
*                  void  Adc_Init(void)
*
*Description    :Adc�ĳ�ʼ��    �˿�ΪPA0    ʹ��ADC1 channel_0
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void  Adc_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//ʹ��ADC1ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��  

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	//ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4; 
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_Cmd(ADC1, ENABLE);//����ADת����	 
}
/*
********************************************************************************************************************
*                  u16 Get_Adc()
*
*Description    :�õ�ADC����ֵ								������Ĭ��ͨ��Ϊ  ADC_Channel_0  ��������������
*Returns     :ADC�Ĳ���ֵ(ʮ����)
*Notes       : none
********************************************************************************************************************
*/
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	    
  
	ADC_SoftwareStartConv(ADC1);
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));

	return ADC_GetConversionValue(ADC1);
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
/*
********************************************************************************************************************
*                  u16 Get_Vol(u16 AdcVal)
*
*Description :�õ���ѹֵ
*Arguments   :AdcVal:  ADC�Ĳ���ֵ
*Returns     :��صĵ�ѹֵ
*Notes       : none
********************************************************************************************************************
*/
float Get_Vol(u8 ch)
{
	u8 t;
	u32 temp_val;
	float vol;
	for(t=0;t<20;t++)
	{
	temp_val+=Get_Adc(ch);
	delay_ms(2);
	}
	vol=(temp_val/20)*(3.3/4096);
	return vol;

}


/*
********************************************************************************************************************
*                  u16 Get_Vol(u16 AdcVal)
*
*Description :�õ���ѹֵ
*Arguments   :AdcVal:  ADC�Ĳ���ֵ
*Returns     :��صĵ�ѹֵ
*Notes       : none
********************************************************************************************************************
*/
void Get_power_Vol(void)
{
	u32 temp_val;
	float vol;
	temp_val=Get_Adc(10);
	vol=temp_val*(3.3/4096);
	vol=vol*3.98f;
	power_vol=meanFilter(&ADCStruct,vol,10);
}

void Get_ch11_Vol(void)
{
	u8 t;
	u32 temp_val;
	float vol;
	for(t=0;t<2;t++)
	{
	temp_val+=Get_Adc(12);
	delay_ms(2);
	}
	vol=(temp_val/2)*(3.3/4096);
	ch11_Vol=meanFilter(&ADCStruct,vol,8);
}

void Get_ch12_Vol(void)
{
	u8 t;
	u32 temp_val;
	float vol;
	for(t=0;t<2;t++)
	{
	temp_val+=Get_Adc(12);
	delay_ms(2);
	}
	vol=(temp_val/2)*(3.3/4096);
	ch12_Vol=meanFilter(&ADCStruct,vol,8);
}






