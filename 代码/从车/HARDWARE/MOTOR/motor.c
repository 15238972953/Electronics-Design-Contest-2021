/*
********************************************************************************************************
�ļ�����moto.c
��  �ܣ�ֱ�����ٵ������
��  ע��	
��  ����https://shop60670850.taobao.com
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/

#include "oled.h"
#include "stm32f4xx_gpio.h"
#include "motor.h"
#include "pid.h"
#include "xunji.h"
/*
********************************************************************************************************
�ļ�����moto.c
��  �ܣ�ֱ�����ٵ������
��  ע��	
��  ����https://shop60670850.taobao.com
��  �ߣ�lilianhe
��  ��: 2017-2-6
*********************************************************************************************************
*/

#include "motor.h"
#include "stm32f4xx_gpio.h"

void MOTO_GPIO_Init(void)
{		
  
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOFʱ��
  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����	
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOFʱ��
  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����	
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOFʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOFʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����	
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��	
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
void turn_3_R(void)//������  ����ת
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
void turn_3_L(void)//������  
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

void turn_3_3(void)//�����ο�ʼ���ء����˵����㣬Ȼ������ת
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

void turn_3_4(void)//�����ο�ʼ���ء����˵����㣬Ȼ������ת,ǰ��һ�Σ�Ȼ������ת
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
void turn_3_5(void)//�����ο�ʼ���ء����˵����㣬Ȼ������ת/****�ң���  �ڶ���
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
void turn_3_6(void)//�����Σ���ת���ڶ���youת
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
void turn_3_7(void)//�����ο�ʼ���ء����˵����㣬Ȼ������
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
void turn_3_8(void)//�����Σ���ת���ڶ�����ת
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

void turn_3_9(void)//�����Σ���ת���ڶ�����Ҫ
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

void go_stright_5(int a,int b)//��ǰֱ��
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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

void go_stright(int a,int b)//��ǰֱ��
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
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

void go_stright_3(int a,int b)//��ǰֱ��
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
				
}


void go_back(int a,int b)//���ֱ��
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
}
void go_3_3(int a,int b)//�����Σ����ң�������
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
}

void go_3_4(int a,int b)//�����Σ����ң�������,���ز���ͷ
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }		
				
}

void go_3_5(int a,int b)//�����Σ����ң�������,����
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }		

}

void go_3_6(int a,int b)//�����Σ����ң�������,����
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
}

void go_right_5(int a,int b)//����ֱ��
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}

void go_right(int a,int b)//����ֱ��
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
//				while(1);
}

void go_right_3(int a,int b)//����ֱ��
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }
				
}



void go_B_right(int a,int b)//����ʱ������ֱ��  
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
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
//				OLED_Refresh_Gram();//������ʾ��OLED		
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
//					OLED_Refresh_Gram();//������ʾ��OLED	
				if(distance_average>b)
		    { 
					flag_inc=100;
				  break;}
			  }			
}