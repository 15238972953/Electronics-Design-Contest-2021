/*
******************************************************************************************************************
*                            MuChun Electron
*                        ZhenJiang,Jiangsu,China
*              (c) Copyright 2016,MuChun Electron,Zhenjiang,China
*                          All Rights Reserved
*
*
*
*Filename      :Delay.c
*Programmer(s) :Song Muchun
*Description   :Delay Driver correlation function
******************************************************************************************************************
*/
/* $ PAGE*/
#include "Delay.h"

/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : 变量定义
*Notes       : none
******************************************************************************************************************
*/
static u8  Fac_us=0;            //us延时倍乘数 
static u32 Fac_ms=0;            //ms延时倍乘数
/******************************************************************************************************************
*                                               Delay_Init()
*
*Description : 延时函数初始化
*Arguments   : none
*Returns     : none
*Notes       : 利用系统滴答定时器定时以达到延时目的
*******************************************************************************************************************
*/
void Delay_Init(void)
{
	MAP_Timer32_initModule(TIMER32_1_MODULE, TIMER32_PRESCALER_1, TIMER32_32BIT,TIMER32_PERIODIC_MODE);//32位定时器模块1初始化
	                                                                                                   //1分频，32位计数，自动重装载模式
	Timer32_disableInterrupt(TIMER32_1_MODULE);                           //关闭中断
	Fac_us = 48;     	                                                    //时钟为48Mhz 
	Fac_ms = 48000;                                                       //代表每个ms需要的时钟数   
}
/******************************************************************************************************************
*                                               Delay_ms()
*
*Description : ms延时
*Arguments   : none
*Returns     : none
*Notes       : 最大延时8947849ms(89秒)
*******************************************************************************************************************
*/
void Delay_ms(u32 nms)
{
	MAP_Timer32_setCount(TIMER32_1_MODULE, nms*Fac_ms);          //设置定时器装载值
	MAP_Timer32_startTimer(TIMER32_1_MODULE, true);              //定时器开始工作一次
	while(MAP_Timer32_getValue(TIMER32_1_MODULE));               //等待计时结束
}
/******************************************************************************************************************
*                                               Delay_us()
*
*Description : us延时
*Arguments   : none
*Returns     : none
*Notes       : 利用系统滴答定时器定时以达到延时目的
*******************************************************************************************************************
*/
void Delay_us(u32 nus)
{
	MAP_Timer32_setCount(TIMER32_1_MODULE, nus*Fac_us);          //设置定时器装载值
	MAP_Timer32_startTimer(TIMER32_1_MODULE, true);              //定时器开始工作一次
	while(MAP_Timer32_getValue(TIMER32_1_MODULE));               //等待计时结束 
}





