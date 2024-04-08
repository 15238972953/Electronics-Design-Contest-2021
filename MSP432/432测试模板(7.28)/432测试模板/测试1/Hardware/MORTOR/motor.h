/*
******************************************************************************
*Filename      :Motor.h
*Programmer(s) :�����õö�
*Description   :2020ʡ��
******************************************************************************
*/

#ifndef _MOTOR_H
#define _MOTOR_H

#include "sys.h"

#define Pwm_Er 0       //PWM��������Χ

#define  AIN1  P8out(4)//TB6612 AIN1���ź궨��
#define  AIN2  P8out(5)//TB6612 AIN2���ź궨��
#define  BIN1  P8out(6)//TB6612 BIN1���ź궨��
#define  BIN2  P8out(7)//TB6612 BIN2���ź궨��

#define  CIN1  P7out(2)
#define  CIN2  P6out(1)
#define  DIN1  P4out(2)
#define  DIN2  P4out(3)


#define CYCLE1 0
#define CYCLE2 0
#define CYCLE3 0
#define CYCLE4 0


void Motor_GPIO_Init(void);                 				//������ų�ʼ��
int  myabs(int x);                     				//����ֵ����
int  Limit_Value(int x,int Max,int Min);      //PWM�޷�����
void Motor_SetAB(int speedA,int speedB); 				//����ٶ��趨������Ϊ��ֵ������PID����
void Motor_SetCD(int speedA,int speedB); 				//����ٶ��趨������Ϊ��ֵ������PID����
void PWM_Init(void);                          //PWM��ʼ��
void Motor_Init(void);
void Motor_TEST(void);

void MotorA_Ctrl(int Compare);
void MotorB_Ctrl(int Compare);
void MotorC_Ctrl(int Compare);
void MotorD_Ctrl(int Compare);
#endif
