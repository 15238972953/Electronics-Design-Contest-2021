#ifndef __XUNJI_H
#define __XUNJI_H

#include "sys.h"
//�������̼����������ķ�ֵ���
//Ӳ������˵����
#define GO    0//������״̬ ǰ��
#define BACK  1//����
#define STOP  2//ͣ��

//**********************ǰѭ��IO��**********************//


#define xunji_L_2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)
#define xunji_L_1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)
#define xunji_F   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define xunji_R_1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
#define xunji_R_2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)




#define D_AD_VALUE -400 		//ȷ�����Ҵ�������ֵ
#define LEFT_MAX 2927   	//�󴫸�����ֵ
#define RIGHT_MAX 2868  	//�Ҵ�������ֵ
#define LEFT_THERSH 954	//�󴫸�����ֵ
#define RIGHT_THERSH 1258	//�Ҵ�������ֵ
#define LEFT_SPAN 3763		//�����������ƶ���Ծ��ֵ   //790
#define RIGHT_SPAN -2831		//�����������ƶ���Ծ��ֵ   //1023

/****************��������********************/
extern int GetTraceDate(void);
extern void GetParament(void);

int abs(int a);


void XUNJI_Front_GPIO_Init(void);
void XUNJI_Beside_GPIO_Init(void);
void XUNJI_Left_GPIO_Init(void);
void XUNJI_Right_GPIO_Init(void);
void XUNJI_ALL_GPIO_Init(void);

void Read_Front_xunji_Date(void);
void Read_Beside_xunji_Date(void);
void Read_Left_xunji_Date(void);
void Read_Right_xunji_Date(void);

void xunji_Front(void);
#endif
