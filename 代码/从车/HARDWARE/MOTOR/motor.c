/*
********************************************************************************************************
文件名：moto.c
功  能：直流减速电机控制
备  注：	
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "oled.h"
#include "stm32f4xx_gpio.h"
#include "motor.h"
#include "pid.h"
#include "xunji.h"
/*
********************************************************************************************************
文件名：moto.c
功  能：直流减速电机控制
备  注：	
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "motor.h"
#include "stm32f4xx_gpio.h"

void MOTO_GPIO_Init(void)
{		
  
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOF时钟
  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉	
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟
  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉	
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOF时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOF时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉	
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化	
}

void MotorA_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_8);
	  GPIO_ResetBits(GPIOE,GPIO_Pin_9);
		TIM_SetCompare1(TIM1,Compare);
	}
	else if(Compare<-Pwm_Er)
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	  GPIO_SetBits(GPIOE,GPIO_Pin_9);
		TIM_SetCompare1(TIM1,-Compare);
	}
	else 
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	  GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	}
}

void MotorB_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{	
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_15);
		TIM_SetCompare2(TIM1,Compare);
	}
	else if(Compare<-Pwm_Er)
	{
			GPIO_SetBits(GPIOA,GPIO_Pin_15);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare2(TIM1,-Compare);
	}
	else 
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	}
} 

void MotorC_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	  GPIO_SetBits(GPIOB,GPIO_Pin_10);
		TIM_SetCompare3(TIM1,Compare);
	}
	else if(Compare<-Pwm_Er)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_11);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		TIM_SetCompare3(TIM1,-Compare);
	}
	else 
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	}
} 

void MotorD_Ctrl(int Compare)
{
	if(Compare>Pwm_Er)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
	  GPIO_SetBits(GPIOD,GPIO_Pin_11);
		TIM_SetCompare4(TIM1,Compare);
	}
	else if(Compare<-Pwm_Er)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
	  GPIO_ResetBits(GPIOD,GPIO_Pin_11);
		TIM_SetCompare4(TIM1,-Compare);
	}
	else 
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
	  GPIO_ResetBits(GPIOD,GPIO_Pin_10);
	}
} 
void MotorALL_Ctrl(float Compare1,float Compare2,float Compare3,float Compare4) 
{
		MotorA_Ctrl(Compare1);	
		MotorB_Ctrl(Compare2);
		MotorC_Ctrl(Compare3);
		MotorD_Ctrl(Compare4);
}
extern float  yaw;
extern float  expect_yaw;
extern int speed;
extern int flag_inc;
int pp=0;

void start(void)
{
pp=0;

}


void turn_1(void)
{	
		while(1)
	{


				 MotorALL_Ctrl(-3000*1.5,-3000*1.5,3000,3000); 
				if(yaw<=-85)
				{ 					
	   flag_inc=100;
			break; 		
}
  }

}








void turn_F_R(void)
{
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	flag_inc=101;	
	while(1)
	{
		if(pp==0)
	{
if(yaw<=90)
				{ 
					flag_inc=31;
				 MotorALL_Ctrl(-1.2*speed,-1.2*speed,+1*speed,+1*speed); 
				}	
if(yaw>90)
{ 
    flag_inc=100;						
			pp=1;		
}
  }
	if(pp==1)
{
break; 	
}	
}
}
void turn_3_R(void)//第三次  向右转
{
	       PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	flag_inc=101;	
	while(1)
	{
		if(pp==0)
	{
if(yaw<=180&&yaw>0)
				{ 
					flag_inc=37;
				 MotorALL_Ctrl(-1*speed,-1*speed,+1.2*speed,+1.2*speed); 
				}	
if(yaw<0)
{ 
    flag_inc=100;						
			pp=1;		
}
  }
	if(pp==1)
{
break; 	
}	
}
}
void turn_3_L(void)//第三次  
{
	       PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	flag_inc=101;	
	while(1)
	{
		if(pp==0)
	{
if(yaw>=0)
				{ 
					flag_inc=51;
				 MotorALL_Ctrl(-1.2*speed,-1.2*speed,+1*speed,+1*speed); 
				}	
if(yaw<0)
{ 
    flag_inc=100;						
			pp=1;		
}
  }
	if(pp==1)
{
break; 	
}	
}
}
void turn_B_R(void)
{
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
flag_inc=101;		
	while(1)
	{
		if(pp==0)
	{
if(yaw<=180&&yaw>0)
				{ 
					flag_inc=35;
				 MotorALL_Ctrl(-speed,-speed,+1.2*speed,+1.2*speed); 
				}	
if(yaw<0)
{ 
    flag_inc=100;						
			pp=1;		
}
  }
	if(pp==1)
{
break; 	
}	
}
}



void turn_F_L(void)
{
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
flag_inc=101;		
		while(1)
	{
		if(pp==0)
	{
if(yaw>-90)
				{ 
				flag_inc=32;
				 MotorALL_Ctrl(-1.2*speed,-1.2*speed,+1*speed,+1*speed); 
				}
				if(yaw<=-90)
				{ 					
	   flag_inc=100;						
			pp=1;		
}
  }
	if(pp==1)
{
break; 	
}	
}
}
//void turn_F_L(void)
//{
//	flag_inc=5000;	
//		while(1)
//	{
//				 MotorALL_Ctrl(-3000,-3000,1800,1800); 
//				
//				if(yaw<=-90)
//				{ 					
//	   flag_inc=100;	
//      break;					
//        }
//  }
//}









void turn_B_L(void)
{
	       PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;
flag_inc=101;	
	while(1)
	{
		if(pp==0)
	{
if(yaw>-180&&yaw<=0)
				{ 
				flag_inc=34;
				 MotorALL_Ctrl(-speed,-speed,+1.2*speed,+1.2*speed); 
				}
if(yaw>0)
				{ 					
	   flag_inc=100;						
			pp=1;		
        }
  }
	if(pp==1)
{
break; 	
}	
}
}

void turn_3_3(void)//第三段开始返回。后退到定点，然后向右转
{
flag_inc=5000;	
flag_inc=101;	
		while(1)
		{

if(yaw>0)

	{		
MotorALL_Ctrl(2400,2400,-2400,-2400); 
	}	
if(yaw<-90)

	{		
			flag_inc=38;
				 MotorALL_Ctrl(-1*speed,-1*speed,+1.2*speed,+1.2*speed); 
		
	}		
	
if(yaw>=-90&&yaw<0)
				{ 					
	   flag_inc=100;						
					break; 		
        }				
  }

}

void turn_3_4(void)//第三段开始返回。后退到定点，然后向右转,前进一段，然后向左转
{
	 PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
flag_inc=101;		
	while(1)
	{
		if(pp==0)
	{
if(yaw>-180)
				{ 
				flag_inc=39;
				 MotorALL_Ctrl(-1.2*speed,-1.2*speed,+1*speed,+1*speed); 
				}
if(yaw>0)
				{ 					
	   flag_inc=100;						
			pp=1;		
        }
  }
	if(pp==1)
{
break; 	
}	
}
	
}
void turn_3_5(void)//第三段开始返回。后退到定点，然后向左转/****右，左  第二次
{
	 PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;
flag_inc=101;		
	while(1)
	{
		if(pp==0)
	{
if(yaw>=-90)
				{ 
				flag_inc=52;
				 MotorALL_Ctrl(-1.2*speed,-1.2*speed,+1*speed,+1*speed); 
				}
if(yaw<-90)
				{ 					
	   flag_inc=100;						
			pp=1;		
        }
  }
	if(pp==1)
{
break; 	
}	
}
	
}
void turn_3_6(void)//第三段，左转，第二次you转
{
	 PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
flag_inc=101;		
	while(1)
	{
		if(pp==0)
	{
if(yaw<=0)
				{ 
				flag_inc=53;
				 MotorALL_Ctrl(-speed,-speed,+1.2*speed,+1.2*speed); 
				}
if(yaw>0)
				{ 					
	   flag_inc=100;						
			pp=1;		
        }
  }
	if(pp==1)
{
break; 	
}	
}
}
void turn_3_7(void)//第三段开始返回。后退到定点，然后向左
{
	 PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
	flag_inc=101;	
flag_inc=5000;	

		while(1)
		{
if(yaw<0)			
{
	MotorALL_Ctrl(-2400,-2400,2400,2400); 
}
if(yaw>=90)
				{ 					
	   flag_inc=57;	
MotorALL_Ctrl(-1.2*speed,-1.2*speed,+1*speed,+1*speed); 					
        }		
if(yaw<90&&yaw>0)
				{ 					
	   flag_inc=100;						
					break; 		
        }				
  }	
}
void turn_3_8(void)//第三段，左转，第二次左转
{
	 PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
flag_inc=101;		
	while(1)
	{
		if(pp==0)
	{
if(yaw>0)
				{ 
				flag_inc=54;
				 MotorALL_Ctrl(-speed,-1*speed,+1.2*speed,+1.2*speed); 
				}
if(yaw<=0)
				{ 					
	   flag_inc=100;						
			pp=1;		
        }
  }
	if(pp==1)
{
break; 	
}	
}
}

void turn_3_9(void)//第三段，左转，第二次子要
{
	 PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
flag_inc=101;		
	while(1)
	{
		if(pp==0)
	{
if(yaw>0)
				{ 
				flag_inc=55;
				 MotorALL_Ctrl(-1.2*speed,-1.2*speed,+speed,+speed); 
				}
if(yaw<=0)
				{ 					
	   flag_inc=100;						
			pp=1;		
        }
  }
	if(pp==1)
{
break; 	
}	
}
}

void turn_3_10(void)//
{
	 PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;	
flag_inc=101;		
	while(1)
	{
		if(pp==0)
	{
if(yaw>-180&&yaw<0)
				{ 
				flag_inc=56;
				 MotorALL_Ctrl(-1.2*speed,-1.2*speed,+speed,+speed); 
				}
if(yaw>0)
				{ 					
	   flag_inc=100;						
			pp=1;		
        }
  }
	if(pp==1)
{
break; 	
}	
}
}
extern int xunji_zhi;
extern int c1,c2,c3,c4;
int distance_average;
extern int velocity_decrease;
extern int speed_bais;

void go_stright_5(int a,int b)//向前直行
{     
      speed_bais=5000;
	    velocity_decrease=160;
       PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	PID_velocity.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=21;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					xunji_zhi=1;
					flag_inc=21;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
				  break;}
			  }
				
}

void go_stright(int a,int b)//向前直行
{     
      speed_bais=4000;
	    velocity_decrease=160;
       PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	PID_velocity.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=21;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					xunji_zhi=1;
					flag_inc=21;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(xunji_L_1==1&&xunji_L_2==1&&xunji_F==1)
		    { 
//					flag_inc=100;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
				  break;}
			  }
				while(1)
				{	
				MotorALL_Ctrl(1500,1500,1500,1500) 	;
				distance_average=(c1+c2+c3+c4)/4;
				if(distance_average>750)
		    { 
					flag_inc=100;
					xunji_zhi=0;
				  break;}
				}
				
}

void go_stright_3(int a,int b)//向前直行
{     
      speed_bais=3000;
	    velocity_decrease=160;
       PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	PID_velocity.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=21;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=21;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1000;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
				
}


void go_back(int a,int b)//向后直行
{     
      speed_bais=4000;
	    velocity_decrease=160;	
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=25;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=25;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1500;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
}
void go_3_3(int a,int b)//第三段，向右，再向右
{     
      speed_bais=2500;
	    velocity_decrease=160;	
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=27;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=27;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1500;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
}

void go_3_4(int a,int b)//第三段，向右，再向右,返回不掉头
{     
      speed_bais=1500;
	    velocity_decrease=160;	
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=28;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=28;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1500;
				  break;}
			  }
		while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }		
				
}

void go_3_5(int a,int b)//第三段，向右，再向左,后退
{     
      speed_bais=2500;
	    velocity_decrease=160;	
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=29;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=29;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1500;
				  break;}
			  }
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }		

}

void go_3_6(int a,int b)//第三段，向右，再向左,后退
{     
      speed_bais=2500;
	    velocity_decrease=160;	
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
	    c1=0;
			c2=0;
			c3=0;
			c4=0;
	    flag_inc=29;
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=29;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1500;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
}

void go_right_5(int a,int b)//向右直行
{     
      speed_bais=2500;
	    velocity_decrease=160;
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=22;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=22;
					c1=0;
					c2=0;
					c3=0;
					c4=0;	
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}

void go_right(int a,int b)//向右直行
{     
      speed_bais=2500;
	    velocity_decrease=160;
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=22;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=22;
					c1=0;
					c2=0;
					c3=0;
					c4=0;	
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}

void go_right_3(int a,int b)//向右直行
{     
      speed_bais=2500;
	    velocity_decrease=160;
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=22;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=22;
					c1=0;
					c2=0;
					c3=0;
					c4=0;	
					velocity_decrease=90;	
					speed_bais=1500;
				  break;}
			  }
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
					
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
				
}



void go_B_right(int a,int b)//返回时，向右直行  
{     
      speed_bais=2500;
	    velocity_decrease=160;
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=26;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=26;
					c1=0;
					c2=0;
					c3=0;
					c4=0;	
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
					
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}


void go_B_left(int a,int b)//  <------
{     
      speed_bais=2500;
	    velocity_decrease=160;
	PID_weizhi.integral=0;	
	PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=24;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=24;
					c1=0;
					c2=0;
					c3=0;
					c4=0;
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}

void go_left_5(int a,int b)//??,????
{     
      speed_bais=4000;
	    velocity_decrease=160;
	PID_weizhi.integral=0;
PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=23;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=23;
					c1=0;
					c2=0;
					c3=0;
					c4=0;	
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}

void go_left(int a,int b)//??,????
{     
      speed_bais=2500;
	    velocity_decrease=160;
	PID_weizhi.integral=0;
PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=23;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=23;
					c1=0;
					c2=0;
					c3=0;
					c4=0;	
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}
void go_left_3(int a,int b)//??,????
{     
      speed_bais=2500;
	    velocity_decrease=160;
	PID_weizhi.integral=0;
PID_weizhi2.integral=0;		
      c1=0;
			c2=0;
			c3=0;
			c4=0;	
	    flag_inc=23;		
				while(1)
		   	{

//        OLED_Show3FNum(0,40, c1 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c2 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//				OLED_Refresh_Gram();//更新显示到OLED		
			  if(distance_average>a)
		    { 
					flag_inc=23;
					c1=0;
					c2=0;
					c3=0;
					c4=0;	
					velocity_decrease=90;	
					speed_bais=1200;
				  break;}
			  }
				
				while(1)
				{
//				OLED_Show3FNum(0,40, c2 ,4,2,12);		//  C2 C1      
//				OLED_Show3FNum(60,40,c1 ,4,2,12);	  //  C3 C4
//				OLED_Show3FNum(0,50, c3 ,4,2,12);		      
//				OLED_Show3FNum(60,50,c4 ,4,2,12);	
				distance_average=(c1+c2+c3+c4)/4;
//				OLED_Show3FNum(0,0,distance_average ,4,2,12);	
//					OLED_Refresh_Gram();//更新显示到OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }			
}