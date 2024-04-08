#ifndef __Ultrasonic_H
#define __Ultrasonic_H

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "include.h"
#include "delay.h"

#define SOUND_SPEED   0.034f        //声速：0.034 cm/us

typedef struct Ultrasonic_Stru
{
	float    High;                    //超声测的高度数据
	uint8_t  Measure_Complete;        //超声波数据测量完成
	int      OverFlowCnt;             //捕获溢出次数     
	uint16_t Capture_Val_Last;	      //上一次捕获值
	uint16_t Capture_Val_Now;	        //当前捕获值
	uint8_t  Status;                  //状态标志位
}Ultrasonic_Stru;

#define Ultrasonic_Trig_PORT   (GPIO_PORT_P9)           //超声波Trig触发信号
#define Ultrasonic_Trig_PIN    (GPIO_PIN0)
 

#define Ultrasonic_ON()  (MAP_GPIO_setOutputHighOnPin(Ultrasonic_Trig_PORT,Ultrasonic_Trig_PIN))
#define Ultrasonic_OFF() (MAP_GPIO_setOutputLowOnPin(Ultrasonic_Trig_PORT,Ultrasonic_Trig_PIN))

#define TRIG_out {Ultrasonic_ON();Delay_us(20);Ultrasonic_OFF();}

extern Ultrasonic_Stru Ultrasoni_Data;

void TimerA3_Cap_Init(void);
void Ultrasonic_Init(void);
void Ultrasonic_Get_Distance(void);


#endif












