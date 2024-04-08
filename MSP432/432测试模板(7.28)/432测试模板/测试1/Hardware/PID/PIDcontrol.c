/*
******************************************************************************
*Filename      :PIDcontrol.c
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛：PID
******************************************************************************
*/
#include "PIDcontrol.h"	
#include "math.h"
#include "include.h"  

PID PID_1;
PID PID_2;

/******************************************************************************************************************
*                            void PID_regulator(void)
*Description : PID参数调节
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
*Description : PID参数初始化
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/	    
void PIDstandard_Init(void)
{   
/*
*************************************
*   			PID_1参数初始化
*************************************
*/	
	PID_1.P = 0;          //比例
	PID_1.I = 0;          //积分
	PID_1.D = 0;          //微分
	
	PID_1.Expected = 0;	  //期望值
	
	PID_1.err = 0;        //偏差
	PID_1.last_err = 0;   //上一次偏差
	PID_1.integral=0;     //偏差总和（积分值）
	
	PID_1.umax=0;					//抗积分饱和上限
	PID_1.umin=0;					//抗积分饱和下限
	PID_1.I_sep = 0;			//积分分离限值
	PID_1.I_Max = 0;      //积分最大值(积分限幅)
	
	PID_1.out=0;					//输出

/*
************************************
*					PID_2参数初始化
************************************
*/
	PID_2.P = 0;          //比例
	PID_2.I = 0;          //积分
	PID_2.D = 0;          //微分
	
	PID_2.Expected = 0; 	//期望值
	
	PID_2.err = 0;        //偏差
	PID_2.last_err = 0;   //上一次偏差
	PID_2.integral=0;     //偏差总和（积分值）
	
	PID_2.umax=0;					//抗积分饱和上限
	PID_2.umin=0;					//抗积分饱和下限
	PID_2.I_sep = 0;			//积分分离限值
	PID_2.I_Max=0;        //积分最大值(积分限幅)

	PID_2.out=0;					//输出
}


/*
******************************************************************************************************************
*                                void PID1(float Actual)
*作    用: PID_1控制
*入口参数: Actual(实测值)
*返 回 值: PID_1.out(s16)
*******************************************************************************************************************
*/
s16 PID1(float Actual)
{
	u8 index=0;
  PID_1.err=PID_1.Expected-Actual;

	if(Actual>PID_1.umax)       				  //大于上限值的积分饱和
		{
			//积分分离
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
	else if(Actual<PID_1.umin)						//小于下限值的积分饱和
				{
						//积分分离
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
						//积分分离
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
				
			//积分限幅
			if(PID_1.integral>PID_1.I_Max)
				PID_1.integral=PID_1.I_Max;             					
			if(PID_1.integral< -PID_1.I_Max)	
				PID_1.integral= (-PID_1.I_Max);              					
	
	//位置式PID控制
	PID_1.out = PID_1.P*PID_1.err		+		index*PID_1.I*PID_1.integral		+		PID_1.D*(PID_1.err-PID_1.last_err);

	PID_1.last_err = PID_1.err;								//用本次偏差值替换上次偏差值
			
	return PID_1.out;
}

/*
*******************************************************）**********************************************************
*                                void PID2(float Actual)
*作    用: PID_2控制
*入口参数: Actual(实测值)
*返 回 值: PID_2.out(s16)
*******************************************************************************************************************
*/
s16 PID2(float Actual)
{
	u8 index=0;
  PID_2.err=PID_2.Expected-Actual;

	if(Actual>PID_2.umax)         //抗积分饱和
		{
			//积分分离
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
						//积分分离
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
						//积分分离
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
			
			//积分限幅
			if(PID_2.integral>PID_2.I_Max)
				PID_2.integral=PID_2.I_Max;             					
			if(PID_2.integral< -PID_2.I_Max)	
				PID_2.integral= (-PID_2.I_Max);              					
	
	//位置式PID控制
	PID_2.out = PID_2.P*PID_2.err		+		index*PID_2.I*PID_2.integral		+		PID_2.D*(PID_2.err-PID_2.last_err);

	PID_2.last_err = PID_2.err;								//用本次偏差值替换上次偏差值
	
	return PID_2.out;
}








