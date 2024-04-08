#ifndef __Ultrasonic_H
#define __Ultrasonic_H

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "include.h"
#include "delay.h"

#define SOUND_SPEED   0.034f        //���٣�0.034 cm/us

typedef struct Ultrasonic_Stru
{
	float    High;                    //������ĸ߶�����
	uint8_t  Measure_Complete;        //���������ݲ������
	int      OverFlowCnt;             //�����������     
	uint16_t Capture_Val_Last;	      //��һ�β���ֵ
	uint16_t Capture_Val_Now;	        //��ǰ����ֵ
	uint8_t  Status;                  //״̬��־λ
}Ultrasonic_Stru;

#define Ultrasonic_Trig_PORT   (GPIO_PORT_P9)           //������Trig�����ź�
#define Ultrasonic_Trig_PIN    (GPIO_PIN0)
 

#define Ultrasonic_ON()  (MAP_GPIO_setOutputHighOnPin(Ultrasonic_Trig_PORT,Ultrasonic_Trig_PIN))
#define Ultrasonic_OFF() (MAP_GPIO_setOutputLowOnPin(Ultrasonic_Trig_PORT,Ultrasonic_Trig_PIN))

#define TRIG_out {Ultrasonic_ON();Delay_us(20);Ultrasonic_OFF();}

extern Ultrasonic_Stru Ultrasoni_Data;

void TimerA3_Cap_Init(void);
void Ultrasonic_Init(void);
void Ultrasonic_Get_Distance(void);


#endif












