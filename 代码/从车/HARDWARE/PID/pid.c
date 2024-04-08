
#include "pid.h"

PIDStru PID_Inner;//�ڻ�PID�ṹ��
PIDStru PID_Inner2;//�ڻ�PID�ṹ��
PIDStru PID_velocity;//�����ṹ��
PIDStru PID_xunji;//�����ṹ��
PIDStru PID_xunji2;//�����ṹ��
PIDStru PID_xunji3;//�����ṹ��
PIDStru PID_weizhi;//�����ṹ��
PIDStru PID_weizhi2;
Expect  Expectation;//�����ṹ��PIDStru PID_velocity;//�����ṹ��




//float Limit_Pwm_float(float pwm,float pwm_min,float pwm_max)
//{
//	if(pwm > pwm_max)			 
//    pwm =  pwm_max;
//	if(pwm < pwm_min)	
//    pwm =  pwm_min;
//	return pwm;   //����
//}

int PID_Control4(PIDStru *PID,float Expected,float observe_value)
{
	PID->Expected = Expected;
	PID->err      = observe_value - PID->Expected;
	PID->pout     = PID->P * PID->err;
	PID->integral = 0.8f*PID->integral;//һ�׵�ͨ�˲�
	PID->integral+= PID->err;
	PID->integral = Limit_Pwm_float(PID->integral,-80,80);//�������޷�(��ֹ�˱�����)
	PID->iout     = PID->I * PID->integral;
	PID->iout     = Limit_Pwm_float(PID->iout,-300,300);   //�޷�(��ֹ�˱�����)
	PID->dout	    = PID->D * (PID->err - PID->last_err);
	PID->last_err = PID->err;
	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
	PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-500,500);
	return (int)PID->PIDOUT;
}

int PID_Control5(PIDStru *PID,float Expected,float observe_value)
{
PID->Expected = Expected;
	PID->err      = observe_value - PID->Expected;
	PID->pout     = PID->P * PID->err;
	PID->integral+= PID->err;
	PID->integral = Limit_Pwm_float(PID->integral,-PID->IMAX,PID->IMAX);//�������޷�(��ֹ�˱�����)
	PID->iout     = PID->I * PID->integral;
	PID->dout	    = PID->D * (PID->err - PID->last_err);
	PID->last_err = PID->err;
	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
  PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-300,300);
	return (int)PID->PIDOUT;
}




//**************************************�������ٶȻ�***********************************************//
//1.����ʽpid

    //int      SetPoint;                                 //�趨Ŀ�� Desired Value

//����PID��غ�
// �����������趨�Ե������Ӱ��ǳ���
/*************************************/
//#define  P_DATA      0.6                             //P����
//#define  I_DATA      0.1                              //I����
//#define  D_DATA      0                            //D����
	static double   Proportion_L=8;                               //�������� Proportional Const
	static double   Integral_L=0.2;                                 //���ֳ��� Integral Const
	static double   Derivative_L=0;  

/********************����ʽPID�������************************************/
//NextPoint��ǰ���ֵ
//SetPoint�趨ֵ
//��ǰ�ٶȵ�λΪrad/s  ��ʱ50ms
//3.14159*encoder/156 rad/s


//*************************************************************ѭ��λ�û�*********************************************************************//

//**************************************************************����������ʽpid*****************************************************************//

		
#define Motor_MAX 7200

#define Motor_MAX_Distance 4000





#define Distance_Kp2 2
#define Distance_Ki2 0
#define Distance_Kd2 0


//**************************************************************����������ʽpid*****************************************************************//

//**************************************************************������pid*****************************************************************//


//PIDStru PID_Inner;//�ڻ�PID�ṹ��
//PIDStru PID_outer;//�⻷PID�ṹ��
//PIDStru PID_steer;//�����ṹ��
//PIDStru PID_steer2;//�����ṹ��
//PIDStru PID_velocity;//�����ṹ��
//Expect  Expectation;//�����ṹ��


//void PID_Init(PIDStru *PID,float P,float I,float D)
//{
//	PID->P 			= P;
//	PID->I 			= I;
//	PID->D 			= D;
//	PID->integral   = 0.0f;
//	PID->pout 		= 0.0f;
//	PID->iout 		= 0.0f;
//	PID->dout 		= 0.0f;
//	PID->IMAX   	= 200.0f;//�����Ǳջ�
//	PID->PMAX   	= 200.0f;//
//	PID->DMAX   	= 200.0f;//
//	PID->Expected 	= 0.0f;
//	PID->err		= 0.0f;
//	PID->last_err	= 0.0f;
//}



//int PID_Control(PIDStru *PID,float Expected,float observe_value)
//{
//	PID->Expected = Expected;
//	PID->err      = observe_value - PID->Expected;
//	PID->pout     = PID->P * PID->err;
//	PID->integral+= PID->err;
//	PID->integral = Limit_Pwm_float(PID->integral,-PID->IMAX,PID->IMAX);//�������޷�(��ֹ�˱�����)
//	PID->iout     = PID->I * PID->integral;
//	PID->dout	  = PID->D * (PID->err - PID->last_err);
//	PID->last_err = PID->err;
//	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
//	PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-PID->IMAX,PID->IMAX);
//	return (int)PID->PIDOUT;
//}



//int PID_Control2(PIDStru *PID,float Expected1,float Expected2,float observe_value)//7-9
//{
//	if(observe_value<Expected1)
//	{
//	PID->err      = observe_value - (Expected1+Expected2)/2;
//	PID->pout     = PID->P * PID->err;
//	PID->integral+= PID->err;
//	PID->integral = Limit_Pwm_float(PID->integral,-PID->IMAX,PID->IMAX);//�������޷�(��ֹ�˱�����)
//	PID->iout     = PID->I * PID->integral;
//  PID->dout	  = PID->D * (PID->err - PID->last_err);
//	PID->last_err = PID->err;
//	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
//	PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-PID->PMAX,PID->PMAX);
//	return (int)PID->PIDOUT;
//	}
//	
//	if(observe_value>Expected2)
//	{PID->err      = observe_value -(Expected1+Expected2)/2 ;
//	PID->pout     = PID->P * PID->err;
//	PID->integral+= PID->err;
//	PID->integral = Limit_Pwm_float(PID->integral,-PID->IMAX,PID->IMAX);//�������޷�(��ֹ�˱�����)
//	PID->iout     = PID->I * PID->integral;
//  PID->dout	  = PID->D * (PID->err - PID->last_err);
//	PID->last_err = PID->err;
//	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
//	PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-PID->PMAX,PID->PMAX);
//	return (int)PID->PIDOUT;}
//	
//	if(observe_value<=Expected2|observe_value>=Expected1)
//	{
//	PID->err      = observe_value - (Expected1+Expected2)/2;
//	PID->pout     = PID->P * PID->err;
//	PID->integral+= PID->err;
//	PID->integral = Limit_Pwm_float(PID->integral,-PID->IMAX,PID->IMAX);//�������޷�(��ֹ�˱�����)
//	PID->iout     = PID->I * PID->integral;
//  PID->dout	  = PID->D * (PID->err - PID->last_err);
//	PID->last_err = PID->err;
//	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
//	PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-PID->PMAX,PID->PMAX);
//	return 0;
//	}
	
//}



/******************************************************************************************************************
*                              void PID_Init(PIDStru *PID,float P,float I,float D)
*
*Author      : Jianfeng Zhang 
*Description : PID��ʼ������
*Arguments   : PIDStru *PID            ��Ҫ��ʼ����PID�ṹ���ָ��
               float P          	   ����ϵ��
			   float I     			   ����ϵ��
			   float D				   ΢��ϵ��
*Returns     : none                  
*Notes       : Lab416 for 2019����
*******************************************************************************************************************
*/	
void PID_Init(PIDStru *PID,float P,float I,float D)
{
	PID->P 			= P;
	PID->I 			= I;
	PID->D 			= D;
	PID->integral   = 0.0f;
	PID->pout 		= 0.0f;
	PID->iout 		= 0.0f;
	PID->dout 		= 0.0f;
	PID->IMAX   	= 1000.0f;
	PID->PMAX   	= 10000.0f;
	PID->DMAX   	= 10000.0f;
	PID->Expected 	= 0.0f;
	PID->err		= 0.0f;
	PID->last_err	= 0.0f;
}


/****�������ٶȻ�*///////
int PID_Control7(PIDStru *PID,float Expected,float observe_value)
{
	PID->Expected = Expected;
	PID->err      = observe_value - PID->Expected;
	PID->pout     = PID->P * PID->err;
	PID->integral = 0.8f*PID->integral;//һ�׵�ͨ�˲�
	PID->integral+= PID->err;
	PID->integral = Limit_Pwm_float(PID->integral,-80,80);//�������޷�(��ֹ�˱�����)
	PID->iout     = PID->I * PID->integral;
	PID->iout     = Limit_Pwm_float(PID->iout,-300,300);   //�޷�(��ֹ�˱�����)
	PID->dout	    = PID->D * (PID->err - PID->last_err);
	PID->last_err = PID->err;
	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
  PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-2500,2500);
	return (int)PID->PIDOUT;
}

//int PID_Control7(PIDStru *PID,float Expected,float observe_value)
//{
//PID->Expected = Expected;
//	PID->err      = observe_value - PID->Expected;
//	PID->pout     = PID->P * PID->err;
//	PID->integral+= PID->err;
//	PID->integral = Limit_Pwm_float(PID->integral,-PID->IMAX,PID->IMAX);//�������޷�(��ֹ�˱�����)
//	PID->iout     = PID->I * PID->integral;
//	PID->dout	    = PID->D * (PID->err - PID->last_err);
//	PID->last_err = PID->err;
//	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
//  PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-1500,1500);
//	return (int)PID->PIDOUT;
//}










