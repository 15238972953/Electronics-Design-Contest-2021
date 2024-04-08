/*
******************************************************************************
*Filename      :mpuiic.h
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛：MPUIIC
******************************************************************************
*/

#ifndef __IIC_H
#define __IIC_H

#include "include.h"
#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>

/*
******************************************************************************************************************
*                                            移植相关
*Description : 移植者需要关心的部分
*Notes       : none
******************************************************************************************************************
*/
#define IIC_SDA_GPIO_PORT      (GPIO_PORT_P1)       //IIC的数据线SDA端口号
#define IIC_SDA_GPIO_PIN       (GPIO_PIN6)          //IIC的数据线SDA引脚号

#define IIC_SCL_GPIO_PORT      (GPIO_PORT_P1)       //IIC的数据线SCL端口号
#define IIC_SCL_GPIO_PIN       (GPIO_PIN7)          //IIC的数据线SCL引脚号

/*
******************************************************************************************************************
*                                            移植无关
*Description : 移植无关
*Notes       : none
******************************************************************************************************************
*/
#define SDA_IN()         (GPIO_setAsInputPin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN))            //设置SDA输入
#define SDA_OUT()        (GPIO_setAsOutputPin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN))           //设置SDA输出
	 
#define IIC_SCL_SET()    (GPIO_setOutputHighOnPin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN))       //SDA输出1
#define IIC_SCL_CLR()    (GPIO_setOutputLowOnPin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN))        //SDA输出0
#define IIC_SDA_SET()    (GPIO_setOutputHighOnPin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN))       //SDA输出1
#define IIC_SDA_CLR()    (GPIO_setOutputLowOnPin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN))        //SDA输出0 
#define READ_SDA         (GPIO_getInputPinValue(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN))         //输入SDA
/*
******************************************************************************************************************
*                                            FUNCTION PROTOTYPES
******************************************************************************************************************
*/
//IIC所有操作函数
void IIC_Init(void);                   //初始化IIC的IO口				 
void IIC_Start(void);			   	         //发送IIC开始信号
void IIC_Stop(void);	  			         //发送IIC停止信号
void IIC_Send_Byte(u8 txd);			       //IIC发送一个字节
u8   IIC_Read_Byte(unsigned char ack); //IIC读取一个字节
u8   IIC_Wait_Ack(void); 				       //IIC等待ACK信号
void IIC_Ack(void);					           //IIC发送ACK信号
void IIC_NAck(void);				           //IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC_Read_One_Byte(u8 daddr,u8 addr);	 
u8   I2C_Readkey(unsigned char I2C_Addr);
u8   I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
u8   IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
u8   IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data);
u8   IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data);
u8   IICwriteBit(u8 dev,u8 reg,u8 bitNum,u8 data);
u8   IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data);

#endif

//*************************************************************************************






