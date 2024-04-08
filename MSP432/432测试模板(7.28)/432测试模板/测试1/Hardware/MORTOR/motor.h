/*
******************************************************************************
*Filename      :Motor.h
*Programmer(s) :代码敲得队
*Description   :2020省赛
******************************************************************************
*/

#ifndef _MOTOR_H
#define _MOTOR_H

#include "sys.h"

#define Pwm_Er 0       //PWM的允许差错范围

#define  AIN1  P8out(4)//TB6612 AIN1引脚宏定义
#define  AIN2  P8out(5)//TB6612 AIN2引脚宏定义
#define  BIN1  P8out(6)//TB6612 BIN1引脚宏定义
#define  BIN2  P8out(7)//TB6612 BIN2引脚宏定义

#define  CIN1  P7out(2)
#define  CIN2  P6out(1)
#define  DIN1  P4out(2)
#define  DIN2  P4out(3)


#define CYCLE1 0
#define CYCLE2 0
#define CYCLE3 0
#define CYCLE4 0


void Motor_GPIO_Init(void);                 				//电机引脚初始化
int  myabs(int x);                     				//绝对值函数
int  Limit_Value(int x,int Max,int Min);      //PWM限幅函数
void Motor_SetAB(int speedA,int speedB); 				//电机速度设定，可以为负值，便于PID调节
void Motor_SetCD(int speedA,int speedB); 				//电机速度设定，可以为负值，便于PID调节
void PWM_Init(void);                          //PWM初始化
void Motor_Init(void);
void Motor_TEST(void);

void MotorA_Ctrl(int Compare);
void MotorB_Ctrl(int Compare);
void MotorC_Ctrl(int Compare);
void MotorD_Ctrl(int Compare);
#endif
