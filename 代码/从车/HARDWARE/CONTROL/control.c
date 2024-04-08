#include "control.h"
#include "encoder.h"
#include "pid.h"
#include "stdio.h"
#include "usart.h"
#include "led.h"
#include "motor.h"
#include "xunji.h"
#include "delay.h"
#include "math.h"
#include "mpu9250.h"
#include "oled.h"
#include "inv_mpu.h"
#include "key.h"
#include "bujin.h"
#include "sonic.h"
#include "filter.h"
#include "timer.h"
#include "adc.h"
#include "usart4dma.h"
#include "nrf24l01.h"
int flag7;
extern int Left_cishu;
extern int Calcarr[8];
 int ins=0;											
int Control_AND_Xunji;
int Control_AND_Xunji2;
extern unsigned int Temp_Data[3] ;       //���ݻ�����
//***************************�����ǲ���***************************************//
  float pitch,roll,yaw; 		//ŷ����
	float yaw_C;
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;					//�¶�		
  float speed_angle ;

//***************************����������***************************************//
int ENA,ENB;
int TagetA, TagetB, TagetC, TagetD;
extern int Encoder_Distance_model;
int ENA1,ENB1,ENC1;
int Fab_ENA,Fab_ENB,Fab_ENC;
int b;
extern int Encoder_Fabs_L1,Encoder_Fabs_L2,Encoder_Fabs_R1,Encoder_Fabs_R2;
//**************************ѭ��λ�û�����************************************//
int F_SITE;
int B_SITE;
int L_SITE;
int R_SITE;
int OUTPUT,OUTPUT1,OUTPUT2;
int PID_value=0;                     //���PID��������PWM���ֵ
int PID_sd=0;                        //С������PID��������PWM���ֵ
int PID_jc=0;                        //С�������ٶ�PID��������PWM���ֵ
int error=0;                         //С����λ��ƫ���� ���(error),λ��ƫ��Խ�����Խ��ƫ��ԽС�����ԽС
int a=0;                             //С�������ٶȵı�־������aԽСʱ�������ٶ�Խ��
int stopconfig=0;                    //����յ��ߵı�־����  //����⵽�յ���ʱ���ñ�������ֵ��ı�

//**************************�������ٶȻ�����************************************//
int Encoder_Left_Front,Encoder_Left_Beside,Encoder_Right_Front,Encoder_Right_Beside;
int Left_t,Right_t,Encoder_R_Front,Encoder_L_Front,Encoder_R_Beside,Encoder_L_Beside;
int Moto_Left_Front,Moto_Right_Front,Moto_Left_Beside,Moto_Right_Beside; 
int para_L_Front,para_R_Front,para_L_Beside,para_R_Beside;//����
int SetPoint=15;//����Ŀ��ֵ��λRPM
////ʹ�ü��ٱ���1��120�ļ�����
#define SetPointL_Front SetPoint*6240/600//����ɱ������ٶȣ���Ϊ����pid���Ƶ��Ǳ���������������
#define SetPointR_Front SetPoint*6240/600//����ɱ������ٶȣ���Ϊ����pid���Ƶ��Ǳ���������������
#define SetPointL_Beside SetPoint*6240/600//����ɱ������ٶȣ���Ϊ����pid���Ƶ��Ǳ���������������
#define SetPointR_Beside SetPoint*6240/600//����ɱ������ٶȣ���Ϊ����pid���Ƶ��Ǳ���������������
int flag_inc=0;
extern int ENA;
extern int a222;
extern float Expectation_Angle;
extern float yaw_2;
int c1,c2,c3,c4;
int speed;




//*********************************С����ֱ��������******************************************////

float	Limit_Pwm_float(float pwm,float pwm_min,float pwm_max)
{
	if(pwm > pwm_max)			 
    pwm =  pwm_max;
	if(pwm < pwm_min)	
    pwm =  pwm_min;
	return pwm;   //����
}
int xunji_zhi=0;
extern long long TEMPA_5;
extern long long TEMPA_2;
extern int ao,bo,co;
int setspeed;
extern unsigned char i;          //��������
extern unsigned char Send_Count; //������Ҫ���͵����ݸ���
extern unsigned char DataScope_OutPut_Buffer[42] ;
int ss=0;

extern int key;

int angle_ex=0;

int speed1;//ѭ��
int speed2;
int speed3;
int speed4;

int speed_Y1;//������

int start_site=0;
int start_flag=0;

int speed_bais=0;
int speed_A1=0;
int speed_B1=0;
int speed_C1=0;
int speed_D1=0;
int velocity_decrease=0;


void read_Front_sensor(void)
{
			  Read_Front_xunji_Date();

        if((xunji_L_2==0&&xunji_L_1==0)&&xunji_F==1&&(xunji_R_1==0))//00100
				{	/*ʶ�𵽺������м�*/	
				 F_SITE=0;
					speed1=0;
					speed2=0;
					speed3=0;
					speed4=0;
					angle_ex=0;
				}
	      if((xunji_L_2==0&&xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==0))//00000
				{	/*ʶ�𵽺������м�*/	
				 F_SITE=0;
					speed1=0;
					//speed2=0;
					speed3=0;
					//speed4=0;
					angle_ex=0;
				}
				if((xunji_L_2==1&&xunji_L_1==1)&&xunji_F==1&&(xunji_R_1==1)&&(xunji_R_2==0))//11111
				{	/*ʶ�𵽺������м�*/	
				 F_SITE=0;
					speed1=0;
					//speed2=0;
					speed3=0;
					//speed4=0;
					angle_ex=0;
				}			
				else if((xunji_L_1==1)&&xunji_F==0&&(xunji_R_1==0))//01000
				{
					 F_SITE=3;
//						speed1=-1000;
//						speed2=-1000;//
//						speed3=1000;
//						speed4=1000;//
					angle_ex=4;
				}
				
				else if((xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==1))//00010
				{
					 F_SITE=4;			
//						speed1=1000;
//						speed2=1000;
//						speed3=-1000;
//						speed4=-1000;
					angle_ex=-4;
				}
				else if((xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==0))//00010
				{
					 F_SITE=4;			
//						speed1=-2000;
//						speed2=-2000;
//						speed3=+2000;
//						speed4=+2000;
					angle_ex=0;
				}
								else if((xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==0))//00010
				{
					 F_SITE=4;			
//						speed1=2000;
//						speed2=2000;
//						speed3=-2000;
//						speed4=-2000;
					angle_ex=-0;
				}
}

extern int mode;
extern u8 t1x[1];
extern u8 r1x[2];
void TIM7_IRQHandler(void)       
{ 
	static unsigned int MS6=0,MS20=0,MS7=0,MS8=0,MS23=0,MS30=0,tt=0;
    
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //????
   {  
		 
	
	  MS6++;
	  MS20++;
	  MS7++;
		 MS8++;
	  MS23++;
	MS30++;
		 tt++;
  if(MS20>=2)
		 { 
			
		
if(flag_inc==100)		
{
MotorALL_Ctrl(-1,-1,-1,-1); 
}
if(flag_inc==101)		
{
MotorALL_Ctrl(0,0,0,0); 
}		

if(flag_inc==220)		//����
{   
	   MotorALL_Ctrl(speed_bais+speed1,speed_bais+speed2,speed_bais+speed3,speed_bais+speed4); 
}

if(flag_inc==20)		//����
{   
		 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	   speed_Y1=PID_Control7(&PID_weizhi,0,yaw);
	   MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
}

if(flag_inc==21)		//ֱ��
{
		 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	   speed_Y1=PID_Control7(&PID_weizhi,0-angle_ex,yaw);
	 // MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
    MotorALL_Ctrl(speed_bais-speed_Y1-speed_A1,speed_bais-speed_Y1-speed_B1,speed_bais+speed_Y1-speed_C1,speed_bais+speed_Y1-speed_D1); 

}
if(flag_inc==22)		//�ҹպ�ֱ��
{
			 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,90-angle_ex,yaw);
	  MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
}
if(flag_inc==23)		//��պ�ֱ��
{
			 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,-90-angle_ex,yaw);
	  MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
}
if(flag_inc==24)		//�ҹպ�ֱ�У�Ȼ�󷵻�������
{
		speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,90,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}
if(flag_inc==25)		//����ʱֱ�У���ʱyaw Ҫ�������� ��Ϊyaw_C
{
 

if(yaw<0)
	{
	yaw_C=yaw+180;	
	}
	if(yaw>=0)
	{
	yaw_C=yaw-180;	
	}
	  speed_Y1=PID_Control7(&PID_weizhi,0-angle_ex,yaw_C);
	
    MotorALL_Ctrl(speed_bais-speed_Y1-speed_A1,speed_bais-speed_Y1-speed_B1,speed_bais+speed_Y1-speed_C1,speed_bais+speed_Y1-speed_D1);
	
}
if(flag_inc==26)		//��պ�ֱ�У�Ȼ�󷵻�������
{
			speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,-90,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}
if(flag_inc==27)		//�����Σ��ҹգ����ҹգ�Ȼ��ֱ��
	{
	if(yaw<0)
	{
	yaw_C=yaw+180;	
	}
	if(yaw>=0)
	{
	yaw_C=yaw-180;	
	}
	  speed_Y1=PID_Control7(&PID_weizhi,0-angle_ex,yaw_C);
	  MotorALL_Ctrl(speed_bais-speed_Y1-speed_A1,speed_bais-speed_Y1-speed_B1,speed_bais+speed_Y1-speed_C1,speed_bais+speed_Y1-speed_D1); 
}

if(flag_inc==28)		//�����Σ��ҹգ����ҹգ�Ȼ��ֱ��
	{
	if(yaw<0)
	{
	yaw_C=yaw+180;	
	}
	if(yaw>=0)
	{
	yaw_C=yaw-180;	
	}
	  speed_Y1=PID_Control7(&PID_weizhi,0-angle_ex,yaw_C);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}
if(flag_inc==29)		//�����Σ��ҹգ�����գ�Ȼ��ֱ�У����ں���
	{
	  speed_Y1=PID_Control7(&PID_weizhi,0-angle_ex,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}
if(flag_inc==41)		//�����Σ��ҹգ�����գ�Ȼ��ֱ�У����ں���
	{
	  speed_Y1=PID_Control7(&PID_weizhi,0,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}



if(flag_inc==31)		//��ת
{
speed=PID_Control7(&PID_weizhi2,90,yaw);		
}
if(flag_inc==32)		//��ת	
{
speed=PID_Control7(&PID_weizhi2,-90,yaw);	
}
if(flag_inc==34)		//�����󣬺󷵻ص���ת
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==35)		//�����ң��󷵻ص���ת
{
speed=PID_Control7(&PID_weizhi2,180,yaw);	
}
if(flag_inc==36)		//�����ң��󷵻ص���ת
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==37)		//���һ�Σ�����ת������ת
{
speed=PID_Control7(&PID_weizhi2,180,yaw);	
}
if(flag_inc==38)		//��һ�ο�����
{
speed=PID_Control7(&PID_weizhi2,-90,yaw);	
}
if(flag_inc==39)		//����������Ȼ��Ҫ��ת��Ȼ��ѭ�������ܻ�ȥ
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==51)		
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==52)	
{
speed=PID_Control7(&PID_weizhi2,-90,yaw);	
}
if(flag_inc==53)	
{
speed=PID_Control7(&PID_weizhi2,0,yaw);	
}
if(flag_inc==54)		//��������ת��ȥ��Ȼ����ת׼������
{
speed=PID_Control7(&PID_weizhi2,180,yaw);	
}
if(flag_inc==55)		//��������ת��ȥ��Ȼ����ת׼������
{
speed=PID_Control7(&PID_weizhi2,0,yaw);	
}
if(flag_inc==56)		//��������ת��ȥ��Ȼ����ת׼������
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==57)		//��������ת��ȥ��Ȼ����ת׼������
{
speed=PID_Control7(&PID_weizhi2,90,yaw);	
}



  MS20=0;
	}	 
		 
	  if(MS6>=2)
		 { 		 
			 OLED_Show3FNum(50,0,yaw ,3,3,12);		
		   OLED_Refresh_Gram();//������ʾ��OLED	

       MS6=0;
	   }	 
			  if(MS8>=2)
		 { 
		 if(mpu_mpl_get_data(&pitch,&roll,&yaw)==0)
		{	
		} 

       MS8=0;
	   }	
		 
		  if(MS7>=5)//��ȡѭ��ֵ
		 { 
       read_Front_sensor(); 
			 
       MS7=0;
	   }
		 
		 
		 		  if(MS23>=10)//��������������
		 { 
       Encoder_Fabs();			
			 c1=c1+ Encoder_Fabs_L1;//��λmm
			 c2=c2+ Encoder_Fabs_L2; 
			 c3=c3+ Encoder_Fabs_R1;//��λmm//����
			 c4=c4+ Encoder_Fabs_R2; 	 
			 TIM2->CNT=30000;
			 TIM3->CNT=30000;
			 TIM4->CNT=30000;
			 TIM8->CNT=30000;		 
       MS23=0;
	   }

		   if(MS30>=2)//��ȡѭ��ֵ
		 { 
		if(KEY7==0&&start_flag==1)
			{	  
				start_site=1;
			}
		if(KEY7==1&&start_flag==2)
			{	  
				start_site=2;
				start_flag=3;
			}

			
       MS30=0;
	   }		 
	if(tt>=10)
{
	
	if(mode==1)
	{
		NRF24L01_TxPacket(t1x);						
		OLED_Show3FNum(50,0,t1x[0] ,3,3,12);		
		 OLED_ShowString( 0,0,(void*)"Tx OK",12);		
		OLED_Refresh_Gram();//������ʾ��OLED	
	}
	if(mode==2)
	{
	 NRF24L01_RxPacket(r1x); 
		OLED_Show3FNum(50,0,r1x[0] ,3,3,12);		
		 OLED_ShowString( 0,0,(void*)"Rx OK",12);		
		OLED_Refresh_Gram();//������ʾ��OLED	
	}	
	tt=0;
}		 
		 
		  TIM_ClearITPendingBit(TIM7,TIM_IT_Update);        
	 }
		
}

