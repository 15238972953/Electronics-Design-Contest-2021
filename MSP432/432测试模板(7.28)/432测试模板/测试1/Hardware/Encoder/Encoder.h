#ifndef __ENCODER_H
#define __ENCODER_H

#include "sys.h"

extern volatile int Encoder_1_SUM;
extern volatile int Encoder_2_SUM;
extern volatile int Encoder_3_SUM;
extern volatile int Encoder_4_SUM;
extern volatile int Encoder_Flag;
extern volatile int Overflow[3];
extern volatile int Speed_1;
extern volatile int Speed_2;
extern volatile int Speed_3;
extern volatile int Speed_4;
extern volatile int distance_1;
extern volatile int distance_2;
extern volatile int distance_3;
extern volatile int distance_4;
#define getDrv_Encoder1()  (GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN0)) //D触发器 D信号 输入脚 
#define getDrv_Encoder2()  (GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN4))//D触发器 D信号 输入脚 
#define getDrv_Encoder3()  (GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN5)) //D触发器 D信号 输入脚 
#define getDrv_Encoder4()  (GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN0))//D触发器 D信号 输入脚 
void Encoder_Cap_Init(void);
int cc(int a);
void Encoder_TEST(void);
#endif
