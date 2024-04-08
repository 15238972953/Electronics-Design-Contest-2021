/*
******************************************************************************
*Filename      :step_cnt.h
*Programmer(s) :Lab416
*Description   :2020省赛
******************************************************************************
*/
#ifndef __STEP_CNT_H
#define __STEP_CNT_H

#include "sys.h"

#define dir1 	P10out(0)
#define pulse1	P10out(4)
#define dir2 	P10out(1)
#define pulse2	P10out(5)

void Step_Init(void);
void Step_Control(float angle,u16 speed);

extern int step_cnt;               
extern int step_speed;
extern int step_pulse;
extern int step_dir;
extern double now_angle;      //记录现在的角度
extern double step_angle;

#endif



