/*
******************************************************************************************************************
*                            MuChun Electron
*                        ZhenJiang,Jiangsu,China
*              (c) Copyright 2016,MuChun Electron,Zhenjiang,China
*                          All Rights Reserved
*
*
*
*Filename      :Delay.h
*Programmer(s) :Song Muchun
*Description   :Delay Driver correlation function
******************************************************************************************************************
*/
/* $ PAGE*/
#ifndef __Delay_H
#define __Delay_H

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "include.h"

/*
******************************************************************************************************************
*                                            FUNCTION PROTOTYPES
******************************************************************************************************************
*/
void Delay_Init(void);            //延时初始化
void Delay_ms(u32 nms);           //毫秒延时，最大值8947849
void Delay_us(u32 nus);           //微秒延时

#endif
