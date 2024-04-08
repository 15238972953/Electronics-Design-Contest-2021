
#ifndef __TRACK_H
#define __TRACK_H

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "include.h"
#include "delay.h"
//QVGA//
#define middle_x 120
#define middle_y 160

#define Y_max_up    -50
#define Y_max_down   10
#define X_max_left   80						
#define X_max_right 0

void Track_Init(void);

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;
	float set_angle;
	float actual_angle;
	float err;
	float err_last;
	float integral;
	float integral_Max;
	float increase;
}PIDX_Stru;

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;
	float set_angle;
	float actual_angle;
	float err;
	float err_last;
	float integral;
	float integral_Max;
}PIDY_Stru;
void Track_Realize(void);
#endif
