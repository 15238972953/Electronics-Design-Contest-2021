/*
******************************************************************************************************************
*                            MuChun Electron
*                        ZhenJiang,Jiangsu,China
*              (c) Copyright 2016,MuChun Electron,Zhenjiang,China
*                          All Rights Reserved
*
*
*
*Filename      :Uart.h
*Programmer(s) :Song Muchun
*Description   :Uart Driver correlation function
******************************************************************************************************************
*/
/* $ PAGE*/
#ifndef __X_Uart_H
#define __X_Uart_H

#include "sys.h"
#include "Delay.h"

/*
******************************************************************************************************************
*                                            FUNCTION PROTOTYPES
******************************************************************************************************************
*/
void Uart1_Init(void);               //串口1初始化
void Uart1_Send(uint8_t TxData);
void Upper_Computer(float data1,float data2,float data3,float data4);

#endif

