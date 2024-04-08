#ifndef __CAR_H
#define __CAR_H


#include "sys.h"

void TIM6_DAC_IRQHandler(void);
void Encoder_Fabs(void);
void Encoder_Counting(void);
void Encoder_Incremental_value(void);
void Encoder_Minimum_adjustment(void);
//void PWM_Limiting(void);
void Update_pwm(void);

void xunjiPID_F_PWM_OUT(void);
void xunjiPID_B_PWM_OUT(void);
void Xianfu_PID(void);
void read_Front_sensor(void);
void read_Beside_sensor(void);
void read_Left_sensor(void);
void read_Right_sensor(void);

void Motor_Distance_Y_Move2(int Move_Distance);
void Encoder_DeInit(void);
void Encoder_Distance_X(int pwm,int distance);
void Encoder_Distance_Y(int pwm,int distance);
float	Limit_Pwm_float(float pwm,float pwm_min,float pwm_max);
void dingdian(void);
void angle_start(void);
float Limit_Pwm_float(float pwm,float pwm_min,float pwm_max);
#endif
