#ifndef __PID_H
#define __PID_H

#include "sys.h"




typedef struct
{
	float P;
	float pout;
	float I;
	float iout;
	float D;
	float dout;
	float integral;		   //������
	float err;       	   //ƫ��ֵ
	float last_err;  	   //�ϴ�ƫ��ֵ
	float Expected;  	   //����ֵ
	float PMAX;			   //P����޷�ֵ
	float IMAX;			   //I����޷�ֵ
	float DMAX;			   //D����޷�ֵ
	float PIDOUT;    	   //���ֵ
} PIDStru;

typedef struct
{
	float Angle;
	int   Distance;
	
} Expect;


extern PIDStru PID_Inner;//�ڻ�PID�ṹ��
extern PIDStru PID_outer;//�⻷PID�ṹ��
extern PIDStru PID_steer;//����ͷ��̨�ṹ��
extern PIDStru PID_weizhi;
extern PIDStru PID_weizhi2;
extern Expect  Expectation;//�����ṹ��
extern PIDStru PID_velocity;

void PID_Init(PIDStru *PID,float P,float I,float D);
int  PID_Control(PIDStru *PID,float Expected,float observe_value);
int PID_Control7(PIDStru *PID,float Expected,float observe_value);
int PID_Control4(PIDStru *PID,float Expected,float observe_value);
int PID_Calc_Left(int NextPoint,int Setpoint);
int PID_Calc_Right(int NextPoint,int Setpoint);
int Position_P (int Encoder,int Target);
int Position_PID (int Encoder,int Target);
int Encoder_Distance_control(int Encoder,int Target);
int Encoder_Distance_control2(int Encoder,int Target);
float Limit_Pwm_float(float pwm,float pwm_min,float pwm_max);
int PID_Control5(PIDStru *PID,float Expected,float observe_value);
#endif
/***************�ٶȻ�*////////////////////////
//			 OLED_ShowString( 0,0,(void*)"ENA",12);	
//			 OLED_ShowNum(40,0,Encoder_Fabs_L1,6,12);	 
//			 Encoder_Fabs();
//			 TIM2->CNT=30000;
//       TIM3->CNT=30000;	 
//			 TIM4->CNT=30000;	
//			 TIM8->CNT=30000;	
//		 // Read_LaserDis(0x00, Temp_Data);
//			 speed=PID_Control4(&PID_velocity,203,Encoder_Fabs_L1);
//			 OLED_Show3FNum(40,40,speed,3,3,12);
//			 OLED_Refresh_Gram();//������ʾ��OLED	 
//			       if(speed>3500)speed=3500;//�޷�
//			       if(speed<-3500)speed=-3500;//�޷�
//			 setspeed=3000;
//			
//		 
//			 MotorA_Ctrl(setspeed);
