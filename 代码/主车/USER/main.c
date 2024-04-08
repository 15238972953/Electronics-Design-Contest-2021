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
#include "spi3.h"
#include "math.h"
float p;
int num_site=0;
extern float pitch,roll,yaw;//ŷ����
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
extern int Encoder_Fabs_L1,Encoder_Fabs_L2,Encoder_Fabs_R1,Encoder_Fabs_R2;
extern int16_t Res_4;
extern int num[5];
extern int num_4[5];
extern int task_set;
u8 t1x[1]={0};
u8 r1x[2]={0};
int mode=0;
int xx=0;
int rgb_C=0;//1�Ǻ�ƣ�2���̵ơ�3�ǻƵ�
int aaa,bbb,aaa1,aaa2,aaa3;
int iiii=0;
int ppp,qq;

int main(void)
{  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);//��ʼ����ʱ����
	KEY_Init();     //������ʼ��
	LED_Init();	    //LED��ʼ��
	OLED_Init();    //OLED��ʼ��
  XUNJI_Front_GPIO_Init();//ѭ�����ų�ʼ��
  
	MPU9250_Init(); //�����ǳ�ʼ��
	mpu_dmp_init(); //�����ǳ�ʼ��

	NRF24L01_Init();   //����ͨ��ģ���ʼ��                  
	NRF24L01_TX_Mode();//����ͨ��ģ���ʼ��          
	MOTO_GPIO_Init();  //������ų�ʼ��
	TIM1_Pwm_Init(7200-1,168);//���pwm��ʼ��	
	TIM2_Encoder_Init(60000-1,0);	       //������A
	TIM3_Encoder_Init(60000-1,0);	       //������B
	TIM4_Encoder_Init(60000-1,0);        //������C
	TIM8_Encoder_Init(60000-1,0);        //������Dcz;

	USART4_Init(9600);   //openmv        ������9600
	USART2_Init(9600);   //������ͨ��    ������9600
	PID_Init(&PID_weizhi,300.0f,2.0f,2.5f);   //ת��pid
	PID_Init(&PID_weizhi2,400.0f,1.0f,2.0f);  //ת��pid
  TIM7_Cnt_Init(1000-1,84-1);            //������ʱ�� 1ms��һ���ж� 
  //HMISendstart();                      //��������������
  start_flag=1;

  while(1)//���°���6��ʼ����
	{	
		Task_set();
		if(key==KEY6_PRES)
			{	  				
				break;
			}
	} 
OLED_Clear();	
	while(1) 
{			
if(task_set==1)	//��������1--���˲���
{
   if(num_4[0]==1)
	 {
        if(start_site==1)		
        {	
            go_stright(4000,1800);  //С��ֱ��
            turn_F_L();             //С����ת
            go_left(2700,500);
            //	rgb_red();
                start_site=100;
            start_flag=2;
        }	
        if(start_site==100)
        {
        rgb_red();
        }
        if(start_site==2)		
        {
            rgb_out();
            go_B_right(2300,700);
            start();
            turn_B_L()	;
            go_back(3200,1500);	 
            rgb_green();
            OLED_2();
            while(1);
         }
    }
	 
   if(num_4[0]==2)
	 {
if(start_site==1)		
{		 
go_stright(4000,1800);
turn_F_R();
go_right(2700,500);
	//rgb_red();
start_site=100;
start_flag=2;
}	
if(start_site==100)
{
rgb_red();
}
if(start_site==2)		
{
  rgb_out();
go_B_left(2200,750);
start();
turn_B_R();
go_back(3400,1500);
		rgb_green();
		OLED_1();
		 while(1);
}
	 } 
}		
	 


if(task_set==2)	//��������2--�ж˲���
{
	if(start_site==1)		
{	
 go_stright_5(5800,0);
	num_site=1;
	start_flag=2;
	go_stright(3000,3500);			
}	
	
		if(num[1]==1&&xx==0)
		{
		turn_F_L();
		go_left(2900,700);
			start_flag=2;
			start_site=100;
			xx=1;
		}		
		if(start_site==100)
{
rgb_red();
}
		if(num[1]==1&&start_site==2)		
{	
	rgb_out();
		go_B_right(2600,700);
		start();
		turn_B_L()	;
		go_back_5(4000,1600);	
		go_back_5(4000,1500);
	rgb_green();
	 OLED_4();
	while(1);		
}		
		
		if(num_4[1]==1&&xx==0)
		{
    turn_F_R();
		go_right(2900,700);
			start_flag=2;
			start_site=100;
		xx=1;	
		}
		if(start_site==100)
{
rgb_red();
}
		if(num_4[1]==1&&start_site==2)		
{	
	rgb_out();
		go_B_left(2700,600);
		start();
		turn_B_R();
		go_back_5(4000,1600);		
		go_back_5(4000,1500);		
	rgb_green();
	OLED_3();
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
			go_left_3(2200,2500);	
			if(num[3]==1)
			{
			start();
turn_3_10();
go_3_3(2000,1300);//��ת
			
				while(1)
				{	rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
go_3_4(1000,1900);//����
start();		
turn_3_7();		
go_right(5000,2000);
start();
turn_3_8()	;
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(3800,1500);	
				rgb_green();
				OLED_7();
			}	
if(num_4[3]==1)
			{
start();
turn_3_6();			
go_stright_3(2000,1300);
				
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
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(3800,1500);	
				rgb_green();
				OLED_8();
			}				
		while(1);				
		}
		
			if((num_4[2]==1||num[2]==0)&&(num_site==2)	)
		{
			start_site=100;
			start();
			turn_F_R();
go_right(1000,1000);
			num_site=3;
go_right(1700,3000);
			if(num_4[3]==1||num[3]==0)
			{
			start();
turn_3_R();
go_3_3(2000,1300);//��ת
				
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
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(3800,1500);		
				rgb_green();
				OLED_5();
			}	
	if(num[3]==1)
			{
			start();
turn_3_L();
go_stright_3(2000,1300);
				
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
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(3800,1500);	
rgb_green();		
OLED_6();				
			}					
		while(1);				
		}			
	}

if(task_set==4)	
{
	if(start_site==1)		
{	
  go_stright_5(5800,0);
	num_site=1;
	start_flag=2;
	go_stright(3000,3500);			
}	
		if(num[1]==1&&xx==0)
		{
		turn_F_L();
		go_left(2800,700);
			start_flag=2;
			start_site=100;
			xx=1;
		}	
if(start_site==100)
{
rgb_red();
}		
		if(num[1]==1&&start_site==2)		
{	
	  rgb_out();
	  t1x[0]=1;		
		mode=1;
	  delay_ms(500);
		go_B_right(2600,700);
		start();
		turn_B_L()	;
		go_back(4000,1600);	
		go_back(4000,1700);
	rgb_green();
	OLED_4();
	while(1);		
}		
		
		if(num_4[1]==1&&xx==0)
		{
    turn_F_R();
		go_right(2800,700);
			start_flag=2;
			start_site=100;
		xx=1;	
		}
		if(start_site==100)
{
rgb_red();
}
		if(num_4[1]==1&&start_site==2)		
{	
	  rgb_out();
	t1x[0]=1;		
	  mode=1;
 delay_ms(500);
		go_B_left(2700,600);
		start();
		turn_B_R();
		go_back(4000,1600);		
		go_back(4000,1700);		
	rgb_green();
	OLED_3();
	while(1);				
		}
}
if(task_set==5)	
{
if(start_site==1)		
{	
go_stright_5(4800,0);
go_stright_5(5800,0);
num_site=2;	
go_stright(2000,3800);	
start_flag=500;		
}
if(num[2]==1)
{
			start_site=100;
			start();
			turn_F_L();
      go_left(2000,0);	
			num_site=3;
			go_left_3(2200,2500);	
			if(num[3]==1)
			{
			start();
turn_3_10();
go_3_3(2000,1300);//��ת
			
				while(1)
				{	rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
t1x[0]=1;		
mode=1;
delay_ms(500);
go_3_4(1000,1900);//����
start();		
turn_3_7();		
go_right(2000,1000);
NRF24L01_RX_Mode();				
			while(1)
				{	
					mode=2;
				if(r1x[0]==1)
				break;
				}	
go_right(2000,1900);				
start();
turn_3_8()	;
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(4000,1500);		
rgb_green();
				OLED_7();
				while(1);
			}	
if(num_4[3]==1)
			{
start();
turn_3_6();			
go_stright_3(2000,1300);
				
        while(1)
				{
				rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}		
rgb_out();
t1x[0]=1;		
mode=1;
delay_ms(500);				
go_3_6(1000,2100);		
start();			
turn_F_R();	
go_right(2000,1000);
				NRF24L01_RX_Mode();				
			while(1)
				{	
					mode=2;
				if(r1x[0]==1)
				break;
				}	
				go_right(2000,1900);	
				start();
				turn_3_8()	;
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(4000,1500);	
				rgb_green();
				OLED_8();
			}				
		while(1);				
}
//////
	if((num_4[2]==1||num[2]==0)&&(num_site==2))
		{
			start_site=100;
			start();
			turn_F_R();
go_right(2000,0);
			num_site=3;
go_right(2700,2000);
			if(num_4[3]==1||num[3]==0)
			{
			start();
turn_3_R();
go_3_3(2000,1300);//��ת
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
t1x[0]=2;		
mode=1;
delay_ms(500);
			
go_3_4(1000,2100);//����   ��ǰ����һ��  ֵ����ȶ
start();
turn_3_3()	;	
go_left_3(2000,1000);	
				NRF24L01_RX_Mode();				
			while(1)
				{	
					mode=2;
				if(r1x[0]==1)
				break;
				}	
go_left_3(2000,1900);	
start();
turn_3_4()	;	
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(4000,1500);	
				rgb_green();
				OLED_5();
			}	
	if(num[3]==1)
			{
			start();
turn_3_L();
go_stright_3(2000,1300);
				
				while(1)
				{rgb_red();
				start_flag=2;	
				if(start_site==2)
				break;
				}
				rgb_out();
t1x[0]=2;		
mode=1;
delay_ms(500);
go_3_5(1000,2100);//����
start();
turn_3_5();
go_left(2000,1000);
NRF24L01_RX_Mode();				
			while(1)
				{	
					mode=2;
				if(r1x[0]==1)
				break;
				}	
go_left(2000,1900);				
start();
turn_3_4()	;	
go_back_5(6000,0);	
go_back_5(6000,0);	
go_back_5(4000,1500);	
rgb_green();
OLED_6();				
			}					
		while(1);				
		}			
}				
  }
}
