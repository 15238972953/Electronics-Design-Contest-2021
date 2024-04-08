#ifndef __MOTO_H
#define __MOTO_H

#include "sys.h"
//四驱底盘及四轮麦克纳姆轮底盘
//硬件连接说明：
#define GO    0//定义电机状态 前进
#define BACK  1//后退
#define STOP  2//停车

#define Pwm_Er 0       //PWM的允许差错范围

#define AIN2 PEout(9)	// DS0
#define BIN2 PAout(15)	// DS1	 
#define CIN2 PBout(10)
#define DIN2 PDout(11)


void MOTO_GPIO_Init(void);

void MOTO_Left_Front(char state);
void MOTO_Left_Beside(char state);
void MOTO_Right_Front(char state);
void MOTO_Right_Beside(char state);
void Car_Ahead(void);
void Car_Back(void);
void Car_Aleft(void);
void Car_Aright(void);
void Car_Stop(void);

void MotorA_Ctrl(int Compare);
void MotorB_Ctrl(int Compare);
void MotorC_Ctrl(int Compare);
void MotorD_Ctrl(int Compare);
void MotorALL_Ctrl(float Compare1,float Compare2,float Compare3,float Compare4) ;

void start(void);
void turn_F_R(void);
void turn_F_L(void);
void turn_B_L(void);
void turn_B_R(void);
void turn_3_R(void);
void turn_3_L(void);
void turn_3_3(void);
void turn_3_4(void);
void turn_3_5(void);
void turn_3_6(void);
	void turn_3_7(void);
		void turn_3_8(void);
			void turn_3_9(void);
			void turn_3_10(void);
void go_3_5(int a,int b);
void go_3_6(int a,int b);
void go_left(int a,int b);
void go_left_5(int a,int b);
void go_stright_3(int a,int b);
void go_left_3(int a,int b);
void go_back(int a,int b);
void go_stright(int a,int b);
void go_stright_5(int a,int b);
void go_right(int a,int b);
void go_right_5(int a,int b);//
void go_right_3(int a,int b);
void go_B_left(int a,int b);
void go_B_right(int a,int b);
void go_3_3(int a,int b);
void go_3_4(int a,int b);



void turn_1(void);
#endif
