/*
******************************************************************************
*                            MuChun Electron
*                        ZhenJiang,Jiangsu,China
*              (c) Copyright 2016,MuChun Electron,Zhenjiang,China
*                          All Rights Reserved
*
*
*
*Filename      :SPI.H
*Programmer(s) :Song Muchun
*Description   :SPI correlation function
******************************************************************************
*/
/* $ PAGE*/
#ifndef __SPI_H
#define __SPI_H

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "Delay.h"

/*
******************************************************************************
*                           FUNCTION PROTOTYPES
******************************************************************************
*/
void     SPI_Drive_Init(void (*SPI_MOUDLE_Init)(void));      //SPI初始化，外部函数通过调用此函数
void     SPI_A1_Init(void);			                             //初始化SPI口
void     SPI_A3_Init(void);			                             //初始化SPI口
void     SPI_B1_Init(void);			                             //初始化SPI口
uint8_t  SPI_Rd_Wr_Byte(uint8_t TxData, uint8_t (*SPI_MODULE_Select)(uint8_t));  //SPI发送接收函数
uint8_t  SPI_A1_ReadWriteByte(uint8_t TxData); //SPI总线读写一个字节
uint8_t  SPI_A3_ReadWriteByte(uint8_t TxData); //SPI总线读写一个字节
uint8_t  SPI_B1_ReadWriteByte(uint8_t TxData);//SPI总线读写一个字节
#endif



