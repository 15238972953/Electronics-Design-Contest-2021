/*************************************************************
//////////////////////////////////////////////////////////////
*Filename      :MLX90614.h
*Programmer(s) :416GZJ
*Description   :2020ʡ��
//////////////////////////////////////////////////////////////
*************************************************************/
#ifndef __MLX90614_H
#define __MLX90614_H
#include "sys.h"

#define MLX90614_ADD 0x00  //����MLX90614ͨ�ŵ�ַ �����0x5A

void  MLX90614_Init(void);//MLX90614��ʼ��
unsigned char MLX90614_write(unsigned char reg_address,unsigned int data);//дRDA5820�Ĵ���
unsigned int MLX90614_read(unsigned char reg_address);            //��RDA5820�Ĵ���
unsigned int MLX90614_readd(unsigned char addr);//��90614���ص�����
void MLX90614_PwmToSMBus(void);		//�л�MLX90614ͨ��ģʽ:PWM->IIC
float Substance_Temp(void);				//��ȡ������¶�ֵ ���������ģʽ
float Human_Temp(void);						//��ȡ������¶�ֵ ���������ģʽ
void MLX90614_TEST(void);

#endif
