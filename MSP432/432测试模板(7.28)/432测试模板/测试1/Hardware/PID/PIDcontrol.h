/*
******************************************************************************************************************
*Filename      :PIDcontrol.h
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛：PID
******************************************************************************************************************
*/

#ifndef __PIDcontrol_H
#define __PIDcontrol_H
#include "sys.h"
#include "include.h"  
/*
******************************************************************************************************************
*Description : 变量及宏定义声明
*Notes       : none
******************************************************************************************************************
*/ 
typedef struct
{
	float P;								
	float I;
	float D;
	float err;
	float last_err;
	float integral;
	float I_sep;
	float I_Max;
	float umax;
	float umin;	
	float Expected;
	s16   out;
}PID;

extern PID PID_1;
extern PID PID_2;


void PID_regulator(void);
void PIDstandard_Init(void);
s16 PID1(float Actual);
s16 PID2(float Actual);






#endif

