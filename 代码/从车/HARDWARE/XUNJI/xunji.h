#ifndef __XUNJI_H
#define __XUNJI_H

#include "sys.h"
//四驱底盘及四轮麦克纳姆轮底盘
//硬件连接说明：
#define GO    0//定义电机状态 前进
#define BACK  1//后退
#define STOP  2//停车

//**********************前循迹IO口**********************//


#define xunji_L_2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)
#define xunji_L_1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)
#define xunji_F   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define xunji_R_1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
#define xunji_R_2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)




#define D_AD_VALUE -400 		//确定左右传感器差值
#define LEFT_MAX 2927   	//左传感器峰值
#define RIGHT_MAX 2868  	//右传感器峰值
#define LEFT_THERSH 954	//左传感器阈值
#define RIGHT_THERSH 1258	//右传感器阈值
#define LEFT_SPAN 3763		//传感器向左移动跳跃差值   //790
#define RIGHT_SPAN -2831		//传感器向右移动跳跃差值   //1023

/****************函数声明********************/
extern int GetTraceDate(void);
extern void GetParament(void);

int abs(int a);


void XUNJI_Front_GPIO_Init(void);
void XUNJI_Beside_GPIO_Init(void);
void XUNJI_Left_GPIO_Init(void);
void XUNJI_Right_GPIO_Init(void);
void XUNJI_ALL_GPIO_Init(void);

void Read_Front_xunji_Date(void);
void Read_Beside_xunji_Date(void);
void Read_Left_xunji_Date(void);
void Read_Right_xunji_Date(void);

void xunji_Front(void);
#endif
