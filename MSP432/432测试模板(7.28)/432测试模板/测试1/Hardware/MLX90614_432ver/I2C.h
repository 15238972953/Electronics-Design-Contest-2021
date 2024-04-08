/*************************************************************
//////////////////////////////////////////////////////////////
*Filename      :I2C.h
*Programmer(s) :416
*Description   :2020ʡ��
//////////////////////////////////////////////////////////////
*************************************************************/
#ifndef __I2C_H
#define __I2C_H
#include "sys.h"

#define I2C_SDA  P10out(2)//P10.2���
#define I2C_SCL  P10out(3)//P10.3���

#define I2C_SDA_IN    GPIO_setAsInputPin(GPIO_PORT_P10,GPIO_PIN2);//����SDA����ģʽ
#define I2C_SDA_OUT   GPIO_setAsOutputPin(GPIO_PORT_P10,GPIO_PIN2);//����SDA���ģʽ

#define I2C_SCL_IN    GPIO_setAsInputPin(GPIO_PORT_P10,GPIO_PIN3);//����SCL����ģʽ
#define I2C_SCL_OUT	  GPIO_setAsOutputPin(GPIO_PORT_P10,GPIO_PIN3);//����SCL���ģʽ

#define I2C_SDA_VAL 	P10in(2)//��ȡ���ŵ�ƽ

void I2C_init(void); 
void I2C_start(void);
void I2C_stop(void);
void I2C_write_byte(unsigned char I2C_byte);
unsigned char I2C_read_byte(void);

unsigned char I2C_check_ack(void);
void sent_noack(void);
void sent_ack(void);

#endif





