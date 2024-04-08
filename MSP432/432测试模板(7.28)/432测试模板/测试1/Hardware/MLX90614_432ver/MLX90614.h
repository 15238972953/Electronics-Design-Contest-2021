/*************************************************************
//////////////////////////////////////////////////////////////
*Filename      :MLX90614.h
*Programmer(s) :416GZJ
*Description   :2020省赛
//////////////////////////////////////////////////////////////
*************************************************************/
#ifndef __MLX90614_H
#define __MLX90614_H
#include "sys.h"

#define MLX90614_ADD 0x00  //单个MLX90614通信地址 多个：0x5A

void  MLX90614_Init(void);//MLX90614初始化
unsigned char MLX90614_write(unsigned char reg_address,unsigned int data);//写RDA5820寄存器
unsigned int MLX90614_read(unsigned char reg_address);            //读RDA5820寄存器
unsigned int MLX90614_readd(unsigned char addr);//读90614传回的数据
void MLX90614_PwmToSMBus(void);		//切换MLX90614通信模式:PWM->IIC
float Substance_Temp(void);				//获取物体的温度值 即物体测温模式
float Human_Temp(void);						//获取人体的温度值 即人体测温模式
void MLX90614_TEST(void);

#endif
