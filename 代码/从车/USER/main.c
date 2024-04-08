#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "mpu9250.h"
#include "inv_mpu.h"
#include "stdio.h"
#include "oled.h"
#include "motor.h"
#include "pwm.h"
#include "control.h"
#include "pid.h"
#include "encoder.h"
#include "xunji.h"
#include "timer.h"
#include "exti.h"
#include "duoji.h"
#include "dongzuo.h"
#include "math.h"
#include "bujin.h"
#include "usartdma.h"
#include "usart3DMA.h"
#include "usart2dma.h"
#include "usart4dma.h"
#include "sonic.h"
#include "adc.h"
#include "nrf24l01.h"
float p;
int num_site=0;
extern float pitch,roll,yaw; 		//ŷ����
	int llll=0;
		extern short temp;	
		int mmmm=0;
		float fmmm=0;
		int show_mmmm=0;
int Encoder_Distance_model;
int key;
extern int Left_cishu;
extern int Second_count2;
extern int Control_AND_Xunji;
extern int Control_AND_Xunji2;
extern int First_count;
extern int color_site;
extern int wuliao_fangcar_m;
extern int wuliao_fangcar_l;
extern int wuliao_fangcar_r;
extern int wuliao_shoucar_m;
extern int wuliao_shoucar_l;
extern int wuliao_shoucar_r;
extern int openmv_site;
extern int guocheng;
extern int taicar;
extern int xerror[10];
extern int yerror[10];
extern int16_t Res_1;

int steppingmotor1_angle=0;
int steppingmotor2_angle=0;
int steppingmotor3_angle=0;
int steppingmotor4_angle=0;

int steppingmotor1_speed=0;//��Ƶ�ʷ�Ӧ�ٶ�,ԽСԽ�죬������400us
int steppingmotor2_speed=0;
int steppingmotor3_speed=0;
int steppingmotor4_speed=0;
u16 openmv2[9];
u16 openmv3[9];
int pwm;
extern int16_t Res_2;
extern float yaw_2;
float Expectation_Angle;
unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
extern int a222;
int ll=0;
extern int speed;
extern unsigned char DataScope_OutPut_Buffer[42];
int iii=0;
u16 value=0;
float vol;
unsigned int Temp_Data[3] = { 0 };       //���ݻ�����
unsigned char out[10] = "0";      //��ʾ����
extern int flag_inc;
extern int flag7;
extern int16_t Res_2;
int ao,bo,co;
extern int speed_A1;
extern int speed_B1;
extern int speed_C1;
extern int speed_D1;
extern int start_site;
extern int start_flag;
extern u8 tx[24];
extern	u8 rx[24];
extern int16_t Res_4;
extern int num[4];
extern int num_4[4];
extern int task_set;
	extern int16_t Res_3;
	extern	int num_3[4];
	extern int flagg;
int xx=0;
int lll=0;
u8 t1x[1]={1};
u8 r1x[2]={0};
extern int Encoder_Fabs_L1,Encoder_Fabs_L2,Encoder_Fabs_R1,Encoder_Fabs_R2;
int mode=0;
 int main(void)
{  
	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	KEY_Init();       	
	LED_Init();	
	OLED_Init();
  XUNJI_Front_GPIO_Init();
	USART3_Init(115200);
//// while(1)
////	{	
////		OLED_ShowString( 0,0,(void*)"Press KEY2 to Start!",12);
////		OLED_Refresh_Gram();
////		key=KEY_Scan(0);
////		if(key==KEY2_PRES)
////			{	 
////        LED1=!LED1;				
////				break;
////			}	
////	}
	OLED_Clear( );
  
	MPU9250_Init();                         //mpu9250
	mpu_dmp_init();
	
NRF24L01_Init();
NRF24L01_RX_Mode();
	
MOTO_GPIO_Init();                      //���
TIM1_Pwm_Init(7200-1,168);	
TIM2_Encoder_Init(60000-1,0);	       //������A
TIM3_Encoder_Init(60000-1,0);	       //������B
TIM4_Encoder_Init(60000-1,0);        //������C
TIM8_Encoder_Init(60000-1,0);        //������Dcz;

USART4_Init(9600);   //openmv 9600
USART2_Init(9600);   //openmv 9600

//PID_Init(&PID_weizhi,150.0f,2.0f,1.5f);//
PID_Init(&PID_weizhi,300.0f,2.0f,2.5f);//
PID_Init(&PID_weizhi2,400.0f,1.0f,2.0f);//	
//PID_Init(&PID_velocity,12.0f,5.01f,1.0f);//
TIM7_Cnt_Init(1000-1,84-1);            //������ʱ�� 1ms��һ���ж� 
start_flag=1;

//while(1)
//	{	
		Task_set();
//		if(key==KEY6_PRES)
//			{	  				
//				break;
//			}
//	} 
OLED_Clear();	
	
	while(1) 
{			

	
//	OLED_Show3FNum(50,0,xunji_L_2 ,3,3,12);		
//OLED_Show3FNum(50,10,xunji_L_1 ,3,3,12);		
//	OLED_Show3FNum(50,20,xunji_F ,3,3,12);		
//	OLED_Show3FNum(50,30,xunji_R_1 ,3,3,12);		
//	OLED_Show3FNum(50,40,xunji_R_2  ,3,3,12);		
//		   OLED_Refresh_Gram();//������ʾ��OLED	
////	
//	
	
	
	
	
	
if(task_set==1)	//��������1--���˲���
{
   if(num_4[0]==1)
	 {
if(start_site==1)		
{	
go_stright(4000,1800);
turn_F_L();
	rgb_red();
go_left(3000,700);
	start_site=100;
start_flag=2;
}	
if(start_site==2)		
{
  rgb_out();
go_B_right(2600,700);
start();
turn_B_L()	;
go_back(5000,1500);	 
	rgb_green();
		 while(1);
	 }
 }
	 
   if(num_4[0]==2)
	 {
if(start_site==1)		
{		 
go_stright(4000,1800);
turn_F_R();
go_right(3000,700);
	rgb_red();
start_site=100;
start_flag=2;
}	
if(start_site==2)		
{
  rgb_out();
go_B_left(2700,850);
start();
turn_B_R();
go_back(5000,1500);
		rgb_green();
		 while(1);
}
	 } 
}		
	 


if(task_set==2)	//��������2--�ж˲���
{
	if(start_site==1)		
{	
 go_stright(5000,800);
	num_site=1;
	start_flag=2;
	go_stright(3000,3500);			
}	
	
		if(num[1]==1&&xx==0)
		{
		turn_F_L();
		go_left(3000,700);
			rgb_red();
			start_flag=2;
			start_site=100;
			xx=1;
		}		
		if(num[1]==1&&start_site==2)		
{	
	rgb_out();
		go_B_right(2600,700);
		start();
		turn_B_L()	;
		go_back(5000,1500);	
		go_back(5000,1500);
	rgb_green();
	while(1);		
}		
		
		if(num_4[1]==1&&xx==0)
		{
    turn_F_R();
		go_right(3000,700);
			rgb_red();
			start_flag=2;
			start_site=100;
		xx=1;	
		}
		if(num_4[1]==1&&start_site==2)		
{	
	rgb_out();
		go_B_left(2700,600);
		start();
		turn_B_R();
		go_back(5000,1500);		
		go_back(5000,1500);		
	rgb_green();
	while(1);				
		}
}
		
if(task_set==3)	//��������3--Զ�˲���
{
		if(start_site==1)		
{	
go_stright_5(4800,0);
go_stright_5(5800,0);
num_site=2;	
go_stright(3000,2800);	
start_flag=500;		
}
if(num[2]==1)
		{
			start_site=100;
			start();
			turn_F_L();
      go_left(2000,0);	
			num_site=3;
			go_left_3(2200,2200);	
			if(num[3]==1)
			{
			start();
turn_3_10();
go_3_3(2000,1500);//��ת
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
go_3_4(1000,2100);//����
start();		
turn_3_7();		
go_right(5000,2000);
start();
turn_3_8()	;
go_back(6000,500);	
go_back(6000,500);	
go_back(6000,500);	
				rgb_green();
			}	
if(num_4[3]==1||num_4[3]==0)
			{
start();
turn_3_6();			
go_stright_3(2000,1500);
				
while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}		
rgb_out();				
go_3_6(1000,2100);		
start();			
turn_F_R();	
go_right(5000,2000);
start();
turn_3_8()	;
go_back(5000,1500);	
go_back(5000,1500);	
go_back(5000,1500);
				rgb_green();
			}				
		while(1);				
		}
		
			if((num_4[2]==1||num[2]==0)&&num_site==2)
		{
			start_site=100;
			start();
			turn_F_R();
go_right(1000,1000);
			num_site=3;
go_right(1000,3700);
			if(num_4[3]==1)
			{
			start();
turn_3_R();
go_3_3(2000,1500);//��ת
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
go_3_4(1000,2100);//����   ��ǰ����һ��  ֵ����ȶ
start();
turn_3_3()	;	
go_left_3(5000,2000);	
start();
turn_3_4()	;	
	go_back(6000,500);
		go_back(6000,500);
	go_back(6000,500);	
				rgb_green();
			}	
	if(num[3]==1||num_4[3]==0)
			{
			start();
turn_3_L();
go_stright_3(2000,1500);
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
go_3_5(1000,2100);//����
start();
turn_3_5();
go_left(5000,2000);	
start();
turn_3_4()	;	
	go_back(6000,500);
		go_back(6000,500);
	go_back(6000,500);
rgb_green();				
			}					
		while(1);				
		}			
	}	
if(task_set==4)	
{	
	if(start_site==1&&lll==0)		
{	
 go_stright_5(5800,0);
	num_site=1;
	start_flag=2;
	go_stright(3000,3500);
  lll=1;	
}	
	
if(num[1]==1&&lll==1)
		{
turn_F_L();
go_B_right(1600,1800);			
	while(1)		
	{
		led3=0;
		mode=2;
  	MotorALL_Ctrl(0,0,0,0); 
	 if(r1x[0]==1)
		 break;
	}	
	led3=1;
go_left(400,200);
TIM_Cmd(TIM7,DISABLE);
MotorALL_Ctrl(0,0,0,0);
delay_ms(1000);	
	delay_ms(1000);
	delay_ms(1000);
	TIM_Cmd(TIM7,ENABLE);
go_left(5500,0);
led2=0;	
	while(1);
}	
if(num[1]==0&&lll==1)
		{
turn_F_R();
go_B_left(1600,1800);
led3=0;				
   while(1)		
	{led3=0;
		mode=2;
  	MotorALL_Ctrl(0,0,0,0); 
	 if(r1x[0]==1)
		 break;
	}	
	led3=1;	
	go_right(400,200);
TIM_Cmd(TIM7,DISABLE);
MotorALL_Ctrl(0,0,0,0);
delay_ms(1000);	
	delay_ms(1000);
	delay_ms(1000);
	TIM_Cmd(TIM7,ENABLE);
go_right(5500,0);
led2=0;		
	while(1);
	}		
}
	
if(task_set==5)
{
	mode=2;
	
		if(r1x[0]==1||r1x[0]==2)		
{	
go_stright_5(4800,0);
go_stright_5(5800,0);
num_site=2;	
go_stright(3000,2800);	
start_flag=500;		
}

if(num[2]==1&&r1x[0]==1)
		{
turn_F_L();
NRF24L01_TX_Mode();				
t1x[0]=1;
mode=1;		
go_B_right(4000,1500);			
go_left(4000,1500);	
go_left_5(1000,1000);	
			num_site=3;
			go_left_3(0,4700);	
			if(num[3]==1)
			{
			start();
      turn_3_10();
      go_3_3(2000,1500);//��ת		
			}
      if(num_4[3]==1)
			{
		start();
    turn_3_6();			
    go_stright_3(2000,1500);
				led2=0;
			}
			
			while(1);
    }	
if(num[2]==1&&r1x[0]==2)
		{
start_site=100;
			start();
			turn_F_L();
      go_left(2000,0);
			NRF24L01_TX_Mode();				
			t1x[0]=1;
			mode=1;				
			num_site=3;
			go_left_3(2200,2200);	
			if(num[3]==1)
			{
			start();
turn_3_10();
go_3_3(2000,1500);//��ת
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
			}	
if(num_4[3]==1)
			{
start();
turn_3_6();			
go_stright_3(2000,1500);
		led2=0;			
while(1)
				{
				start_flag=2;	
				if(start_site==2)
				break;
				}		
rgb_out();				
			}								
			while(1);
    }


if((num_4[2]==1||num[2]==0)&&r1x[0]==1&&num_site==2)
{
			start_site=100;
			start();
			turn_F_R();
  go_right(1000,1000);
	NRF24L01_TX_Mode();				
			t1x[0]=1;
			mode=1;		
			num_site=3;
go_right(1000,3700);
			if(num_4[3]==1)
			{
			start();
turn_3_R();
go_3_3(2000,1500);//��ת
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
			while(1);		
			}	
	if(num[3]==1)
			{
			start();
turn_3_L();
go_stright_3(2000,1500);
				led2=0;	
				while(1)
				{
				start_flag=2;	
				if(start_site==2)
				break;
				}
		
		
		while(1);	
}	
}			

if((num_4[2]==1||num[2]==0)&&r1x[0]==2&&num_site==2)
{		
turn_F_R();
NRF24L01_TX_Mode();				
t1x[0]=1;
mode=1;		
go_B_left(4000,1500);				
go_right(4000,1500);	
go_right_5(1000,1000);
			num_site=3;
go_right(1000,3700);
			if(num_4[3]==1||num[3]==0)
			{
			start();
turn_3_R();
go_3_3(2000,1500);//��ת
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
			}	
	if(num[3]==1)
			{
			start();
turn_3_L();
go_stright_3(2000,1500);
				led2=0;	
				while(1)
				{
				start_flag=2;	
				if(start_site==2)
				break;
				}			
			}					
		while(1);					
}		

}

		
		
/****��ת  Ȼ�����  ��һ��*/////	
//if(start_site==1)		
//{	
//	delay_ms(1000);
//	go_stright(5000,1500);
//		turn_F_R();
//		go_right(3000,700);
//	start_site=100;
//start_flag=2;}
//if(start_site==2)		
//{
//		go_B_left(2700,850);
//		start();
//		turn_B_R();
//		go_back(5000,1500);
//	while(1);
//}

//	go_stright(4500,1500);
//	turn_F_R();
//	go_right(3000,700);

//		go_B_left(2500,1000);
//		start();
//		turn_B_R();
//		go_back(5000,1500);
/****��ת  Ȼ�����  ��һ��*/////		
		
		
/****��ת  Ȼ�����  ��һ��*/////			
//turn_F_L();
//	go_stright(4500,1500);
//turn_F_L();
//go_left(3000,700);
//go_B_right(2700,1200);
//start();
//turn_B_L()	;
//go_back(5000,1500);	
/****��ת  Ȼ�����  ��һ��*/////	

/****��ת  Ȼ�����  �ڶ���*/////	
//		go_stright(5000,1500);
//		go_stright(5000,1500);
//		turn_F_R();
//		go_right(3000,700);
//		go_B_left(2700,600);
//		start();
//		turn_B_R();
//		go_back(5000,1500);		
//		go_back(5000,1500);		
/****��ת  Ȼ�����  �ڶ���*/////

/****��ת  Ȼ�����  �ڶ���*/////		
//go_stright(5000,1500);
//go_stright(5000,1600);
//turn_F_L();
//go_left(3000,700);
//go_B_right(2600,1200);
//start();
//turn_B_L()	;
//go_back(5000,1500);	
//go_back(5000,1500);	
/****��ת  Ȼ�����  �ڶ���*/////	


/****��ת  Ȼ�����  ������*/////
//		go_stright(5000,1500);
//		go_stright(5000,1500);
//		go_stright(5000,1500);	
//		turn_F_R();
//		go_right(3000,700);
//		go_B_left(2700,850);
//		start();
//		turn_B_R();
//		go_back(5000,1500);		
//		go_back(5000,1500);		
//    go_back(5000,1500);	
/****��ת  Ȼ�����  ������*/////	

/****��ת  Ȼ�����  ������*/////		
//go_stright(4500,1300);
//go_stright(5000,1600);
//go_stright(5000,1600);
//turn_F_L();
//go_left(3000,700);
//go_B_right(2600,700);
//start();
//turn_B_L()	;
//go_back(5000,1500);	
//go_back(5000,1500);	
//go_back(5000,1500);	
/****��ת  Ȼ�����  ������*/////	

/******�����ˣ��ң���*//////////
//	go_stright(5000,1500);
//turn_F_R();
//go_right_3(5000,2000);
//start();
//turn_3_R();
//go_3_3(2000,1500);//��ת
//MotorALL_Ctrl(-1,-1,-1,-1); 		
//		delay_ms(1000);
//go_3_4(1000,2100);//����   ��ǰ����һ��  ֵ����ȶ
//start();
//turn_3_3()	;	
//go_left_3(5000,2000);	
//start();
//turn_3_4()	;	
//	go_back(6000,500);
//		go_back(6000,500);
//	go_back(6000,500);
		
/******�����ˣ��ң���*//////////

/******�����ˣ��ң���*//////////
//	go_stright(5000,1500);
//turn_F_R();
//go_right(5000,2000);
//start();
//turn_3_L();
//go_stright_3(2000,1500);
//go_3_5(1000,2100);//����
//start();
//turn_3_5();

//start();go_left(5000,2000);	
//turn_3_4();	
//	go_back(5000,1500);
//		go_back(5000,1500);
//	go_back(5000,1500);	
/******�����ˣ��ң���*//////////

/******�����ˣ�����*//////////
//go_stright(5000,1500);
//turn_F_L();
//go_left(5000,1700);
//start();
//turn_3_10();
//go_3_3(2000,1500);//��ת
//go_3_4(1000,2100);//����
//start();		
//turn_3_7();		
//go_right(5000,2000);
//start();
//turn_3_8()	;
//go_back(6000,500);	
//go_back(6000,500);	
//go_back(6000,500);	
/******�����ˣ�����*//////////


/******�����ˣ�����*//////////
//go_stright(5000,1500);
//turn_F_L();
//go_left(5000,1700);
//start();
//turn_3_10();
//go_3_3(2000,1500);//��ת
//go_3_4(1000,2100);//����
//start();		
//turn_3_7();		
//go_right(5000,2000);
//start();
//turn_3_8()	;
//go_back(6000,500);	
//go_back(6000,500);	
//go_back(6000,500);
/******�����ˣ�����*//////////
//while(1);

//	while(1);
//			  OLED_ShowNum(50,0,Encoder_Fabs_L1 ,3,12);	
//				OLED_ShowNum(50,10,Encoder_Fabs_L2 ,3,12);					 
//				OLED_ShowNum(50,20,Encoder_Fabs_R1,3,12);	
//				OLED_ShowNum(50,30,Encoder_Fabs_R2,3,12);	
//		    OLED_Show3FNum(0,0,speed_A1 ,4,3,12);	
//				OLED_Show3FNum(0,10,speed_B1 ,4,3,12);					 
//				OLED_Show3FNum(0,20,speed_C1,4,3,12);	
//				OLED_Show3FNum(0,30,speed_D1,4,3,12);	
//				OLED_Refresh_Gram();//������ʾ��OLED	
		
//	turn_R();
			

		
  }
}
