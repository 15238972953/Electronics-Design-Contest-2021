/*************************************************************
//////////////////////////////////////////////////////////////
*Filename      :I2C.h
*Programmer(s) :416
*Description   :2020省赛
//////////////////////////////////////////////////////////////
*************************************************************/
#ifndef __I2C_H
#define __I2C_H
#include "sys.h"

#define I2C_SDA  P10out(2)//P10.2输出
#define I2C_SCL  P10out(3)//P10.3输出

#define I2C_SDA_IN    GPIO_setAsInputPin(GPIO_PORT_P10,GPIO_PIN2);//设置SDA输入模式
#define I2C_SDA_OUT   GPIO_setAsOutputPin(GPIO_PORT_P10,GPIO_PIN2);//设置SDA输出模式

#define I2C_SCL_IN    GPIO_setAsInputPin(GPIO_PORT_P10,GPIO_PIN3);//设置SCL输入模式
#define I2C_SCL_OUT	  GPIO_setAsOutputPin(GPIO_PORT_P10,GPIO_PIN3);//设置SCL输出模式

#define I2C_SDA_VAL 	P10in(2)//读取引脚电平

void I2C_init(void); 
void I2C_start(void);
void I2C_stop(void);
void I2C_write_byte(unsigned char I2C_byte);
unsigned char I2C_read_byte(void);

unsigned char I2C_check_ack(void);
void sent_noack(void);
void sent_ack(void);

#endif





