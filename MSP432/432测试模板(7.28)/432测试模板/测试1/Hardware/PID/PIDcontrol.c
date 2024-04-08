/*
******************************************************************************
*Filename      :PIDcontrol.c
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018����ʡ������ƾ�����PID
******************************************************************************
*/
#include "PIDcontrol.h"	
#include "math.h"
#include "include.h"  

PID PID_1;
PID PID_2;

/******************************************************************************************************************
*                            void PID_regulator(void)
*Description : PID��������
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/	
void PID_regulator(void)
{
	s16 flag;
	switch(flag)
	{
		case 1:		;break;
		case 2:		;break;
		case 3:		;break;
		case 4:		;break;
		case 5:		;break;
		case 6:		;break;
	}
}


/******************************************************************************************************************
*                            PID_Init() 
*Description : PID������ʼ��
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/	    
void PIDstandard_Init(void)
{   
/*
*************************************
*   			PID_1������ʼ��
*************************************
*/	
	PID_1.P = 0;          //����
	PID_1.I = 0;          //����
	PID_1.D = 0;          //΢��
	
	PID_1.Expected = 0;	  //����ֵ
	
	PID_1.err = 0;        //ƫ��
	PID_1.last_err = 0;   //��һ��ƫ��
	PID_1.integral=0;     //ƫ���ܺͣ�����ֵ��
	
	PID_1.umax=0;					//�����ֱ�������
	PID_1.umin=0;					//�����ֱ�������
	PID_1.I_sep = 0;			//���ַ�����ֵ
	PID_1.I_Max = 0;      //�������ֵ(�����޷�)
	
	PID_1.out=0;					//���

/*
************************************
*					PID_2������ʼ��
************************************
*/
	PID_2.P = 0;          //����
	PID_2.I = 0;          //����
	PID_2.D = 0;          //΢��
	
	PID_2.Expected = 0; 	//����ֵ
	
	PID_2.err = 0;        //ƫ��
	PID_2.last_err = 0;   //��һ��ƫ��
	PID_2.integral=0;     //ƫ���ܺͣ�����ֵ��
	
	PID_2.umax=0;					//�����ֱ�������
	PID_2.umin=0;					//�����ֱ�������
	PID_2.I_sep = 0;			//���ַ�����ֵ
	PID_2.I_Max=0;        //�������ֵ(�����޷�)

	PID_2.out=0;					//���
}


/*
******************************************************************************************************************
*                                void PID1(float Actual)
*��    ��: PID_1����
*��ڲ���: Actual(ʵ��ֵ)
*�� �� ֵ: PID_1.out(s16)
*******************************************************************************************************************
*/
s16 PID1(float Actual)
{
	u8 index=0;
  PID_1.err=PID_1.Expected-Actual;

	if(Actual>PID_1.umax)       				  //��������ֵ�Ļ��ֱ���
		{
			//���ַ���
			if(fabs(PID_1.err)>=PID_1.I_sep)
				{
					index = 0;
					PID_1.integral=0;
				}
			else
				{
					index = 1;
					if(PID_1.err<0)
					PID_1.integral += PID_1.err;
				}
		}
	else if(Actual<PID_1.umin)						//С������ֵ�Ļ��ֱ���
				{
						//���ַ���
						if(fabs(PID_1.err)>=PID_1.I_sep)
							{
								index = 0;
								PID_1.integral=0;
							}
						else
							{
								index = 1;
								if(PID_1.err>0)
								PID_1.integral += PID_1.err;
							}	
				}
			else
				{
						//���ַ���
						if(fabs(PID_1.err)>=PID_1.I_sep)
							{
								index = 0;
								PID_1.integral=0;
							}
						else
							{
								index = 1;
								PID_1.integral += PID_1.err;
							}		
				}	
				
			//�����޷�
			if(PID_1.integral>PID_1.I_Max)
				PID_1.integral=PID_1.I_Max;             					
			if(PID_1.integral< -PID_1.I_Max)	
				PID_1.integral= (-PID_1.I_Max);              					
	
	//λ��ʽPID����
	PID_1.out = PID_1.P*PID_1.err		+		index*PID_1.I*PID_1.integral		+		PID_1.D*(PID_1.err-PID_1.last_err);

	PID_1.last_err = PID_1.err;								//�ñ���ƫ��ֵ�滻�ϴ�ƫ��ֵ
			
	return PID_1.out;
}

/*
*******************************************************��**********************************************************
*                                void PID2(float Actual)
*��    ��: PID_2����
*��ڲ���: Actual(ʵ��ֵ)
*�� �� ֵ: PID_2.out(s16)
*******************************************************************************************************************
*/
s16 PID2(float Actual)
{
	u8 index=0;
  PID_2.err=PID_2.Expected-Actual;

	if(Actual>PID_2.umax)         //�����ֱ���
		{
			//���ַ���
			if(fabs(PID_2.err)>=PID_2.I_sep)
				{
					index = 0;
					PID_2.integral=0;
				}
			else
				{
					index = 1;
					if(PID_2.err<0)
					PID_2.integral += PID_2.err;
				}
		}
	else if(Actual<PID_2.umin)
				{
						//���ַ���
						if(fabs(PID_2.err)>=PID_2.I_sep)
							{
								index = 0;
								PID_2.integral=0;
							}
						else
							{
								index = 1;
								if(PID_2.err>0)
								PID_2.integral += PID_2.err;
							}	
				}
			else
				{
						//���ַ���
						if(fabs(PID_2.err)>=PID_2.I_sep)
							{
								index = 0;
								PID_2.integral=0;
							}
						else
							{
								index = 1;
								PID_2.integral += PID_2.err;
							}
				}	
			
			//�����޷�
			if(PID_2.integral>PID_2.I_Max)
				PID_2.integral=PID_2.I_Max;             					
			if(PID_2.integral< -PID_2.I_Max)	
				PID_2.integral= (-PID_2.I_Max);              					
	
	//λ��ʽPID����
	PID_2.out = PID_2.P*PID_2.err		+		index*PID_2.I*PID_2.integral		+		PID_2.D*(PID_2.err-PID_2.last_err);

	PID_2.last_err = PID_2.err;								//�ñ���ƫ��ֵ�滻�ϴ�ƫ��ֵ
	
	return PID_2.out;
}








