#ifndef _XUNJI_H
#define _XUNJI_H

#include "sys.h"
#define SpeedA_BASIC  3000
#define SpeedB_BASIC  3000
#define SpeedC_BASIC  3000
#define SpeedD_BASIC  3000	

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;
	float set_angel;
	float actual_angle;
	float err;
	float err_last;
	float integral;
	float integral_Max;
	float differ;
}PID_Stru;

extern  int  Speed_A;
extern	int  Speed_B;
extern	int  Speed_C;
extern	int  Speed_D;

void MPUPID_set(void);
void xunji(void);
#endif
