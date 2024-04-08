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
extern unsigned int Temp_Data[3] ;       //数据缓存区
//***************************陀螺仪参量***************************************//
  float pitch,roll,yaw; 		//欧拉角
	float yaw_C;
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度		
  float speed_angle ;

//***************************编码器参量***************************************//
int ENA,ENB;
int TagetA, TagetB, TagetC, TagetD;
extern int Encoder_Distance_model;
int ENA1,ENB1,ENC1;
int Fab_ENA,Fab_ENB,Fab_ENC;
int b;
extern int Encoder_Fabs_L1,Encoder_Fabs_L2,Encoder_Fabs_R1,Encoder_Fabs_R2;
//**************************循迹位置环参量************************************//
int F_SITE;
int B_SITE;
int L_SITE;
int R_SITE;
int OUTPUT,OUTPUT1,OUTPUT2;
int PID_value=0;                     //舵机PID控制器的PWM输出值
int PID_sd=0;                        //小车差速PID控制器的PWM输出值
int PID_jc=0;                        //小车基础速度PID控制器的PWM输出值
int error=0;                         //小车的位置偏移量 误差(error),位置偏移越大，误差越大，偏移越小，误差越小
int a=0;                             //小车基础速度的标志变量，a越小时，基础速度越大
int stopconfig=0;                    //检测终点线的标志变量  //当检测到终点线时，该变量的数值会改变

//**************************编码器速度环参量************************************//
int Encoder_Left_Front,Encoder_Left_Beside,Encoder_Right_Front,Encoder_Right_Beside;
int Left_t,Right_t,Encoder_R_Front,Encoder_L_Front,Encoder_R_Beside,Encoder_L_Beside;
int Moto_Left_Front,Moto_Right_Front,Moto_Left_Beside,Moto_Right_Beside; 
int para_L_Front,para_R_Front,para_L_Beside,para_R_Beside;//增量
int SetPoint=15;//设置目标值单位RPM
////使用减速比是1：120的减速箱
#define SetPointL_Front SetPoint*6240/600//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量
#define SetPointR_Front SetPoint*6240/600//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量
#define SetPointL_Beside SetPoint*6240/600//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量
#define SetPointR_Beside SetPoint*6240/600//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量
int flag_inc=0;
extern int ENA;
extern int a222;
extern float Expectation_Angle;
extern float yaw_2;
int c1,c2,c3,c4;
int speed;




//*********************************小车走直线陀螺仪******************************************////

float	Limit_Pwm_float(float pwm,float pwm_min,float pwm_max)
{
	if(pwm > pwm_max)			 
    pwm =  pwm_max;
	if(pwm < pwm_min)	
    pwm =  pwm_min;
	return pwm;   //返回
}
extern long long TEMPA_5;
extern long long TEMPA_2;
extern int ao,bo,co;
int setspeed;
extern unsigned char i;          //计数变量
extern unsigned char Send_Count; //串口需要发送的数据个数
extern unsigned char DataScope_OutPut_Buffer[42] ;
int ss=0;

extern int key;

int angle_ex=0;

int speed1;//循迹
int speed2;
int speed3;
int speed4;

int speed_Y1;//陀螺仪

int start_site=0;
int start_flag=0;

int speed_bais=0;
int speed_A1=0;
int speed_B1=0;
int speed_C1=0;
int speed_D1=0;
int velocity_decrease=0;

extern u8 t1x[1];
extern u8 r1x[2];
void read_Front_sensor(void)
{
			  Read_Front_xunji_Date();

        if((xunji_L_2==0&&xunji_L_1==0)&&xunji_F==1&&(xunji_R_1==0)&&(xunji_R_2==0))//00100
				{	/*识别到黑线在中间*/	
				 F_SITE=0;
					speed1=0;
					speed2=0;
					speed3=0;
					speed4=0;
					angle_ex=0;
				}
	      if((xunji_L_2==0&&xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==0)&&(xunji_R_2==0))//00000
				{	/*识别到黑线在中间*/	
				 F_SITE=0;
					speed1=0;
					//speed2=0;
					speed3=0;
					//speed4=0;
					angle_ex=0;
				}
				if((xunji_L_2==1&&xunji_L_1==1)&&xunji_F==1&&(xunji_R_1==1)&&(xunji_R_2==0))//11111
				{	/*识别到黑线在中间*/	
				 F_SITE=0;
					speed1=0;
					//speed2=0;
					speed3=0;
					//speed4=0;
					angle_ex=0;
				}			
				else if((xunji_L_2==0&&xunji_L_1==1)&&xunji_F==0&&(xunji_R_1==0)&&(xunji_R_2==0))//01000
				{
					 F_SITE=3;
//						speed1=-1000;
//						speed2=-1000;//
//						speed3=1000;
//						speed4=1000;//
					angle_ex=4;
				}
				
				else if((xunji_L_2==0&&xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==1)&&(xunji_R_2==0))//00010
				{
					 F_SITE=4;			
//						speed1=1000;
//						speed2=1000;
//						speed3=-1000;
//						speed4=-1000;
					angle_ex=-4;
				}
				else if((xunji_L_2==1&&xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==0)&&(xunji_R_2==0))//00010
				{
					 F_SITE=4;			
//						speed1=-2000;
//						speed2=-2000;
//						speed3=+2000;
//						speed4=+2000;
					angle_ex=8;
				}
								else if((xunji_L_2==0&&xunji_L_1==0)&&xunji_F==0&&(xunji_R_1==0)&&(xunji_R_2==1))//00010
				{
					 F_SITE=4;			
//						speed1=2000;
//						speed2=2000;
//						speed3=-2000;
//						speed4=-2000;
					angle_ex=-8;
				}
}
extern int send_chuan;
extern int mode;
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
if(flag_inc==20)		//后退
{   
		 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	   speed_Y1=PID_Control7(&PID_weizhi,0,yaw);
	   MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
}

if(flag_inc==21)		//直走
{
		 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	   speed_Y1=PID_Control7(&PID_weizhi,0-angle_ex,yaw);
	 // MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
    MotorALL_Ctrl(speed_bais-speed_Y1-speed_A1,speed_bais-speed_Y1-speed_B1,speed_bais+speed_Y1-speed_C1,speed_bais+speed_Y1-speed_D1); 

}
if(flag_inc==22)		//右拐后直行
{
			 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,90-angle_ex,yaw);
	  MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
}
if(flag_inc==23)		//左拐后直行
{
			 speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,-90-angle_ex,yaw);
	  MotorALL_Ctrl(speed_bais+speed1-speed_Y1-speed_A1,speed_bais+speed2-speed_Y1-speed_B1,speed_bais+speed3+speed_Y1-speed_C1,speed_bais+speed4+speed_Y1-speed_D1); 
}
if(flag_inc==24)		//右拐后直行，然后返回向左退
{
		speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,90,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}
if(flag_inc==25)		//返回时直行，此时yaw 要经过处理 变为yaw_C
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
if(flag_inc==26)		//左拐后直行，然后返回向右退
{
			speed_A1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L1);
		 speed_B1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_L2);
		 speed_C1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R1);
		 speed_D1=PID_Control4(&PID_velocity,velocity_decrease,Encoder_Fabs_R2);
	  speed_Y1=PID_Control7(&PID_weizhi,-90,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}
if(flag_inc==27)		//第三次，右拐，再右拐，然后直行
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

if(flag_inc==28)		//第三次，右拐，再右拐，然后直行
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
if(flag_inc==29)		//第三次，右拐，再左拐，然后直行，现在后退
	{
	  speed_Y1=PID_Control7(&PID_weizhi,0-angle_ex,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}
if(flag_inc==41)		//第三次，右拐，再左拐，然后直行，现在后退
	{
	  speed_Y1=PID_Control7(&PID_weizhi,0,yaw);
	  MotorALL_Ctrl(-speed_bais-speed_Y1-speed_A1,-speed_bais-speed_Y1-speed_B1,-speed_bais+speed_Y1-speed_C1,-speed_bais+speed_Y1-speed_D1); 
}



if(flag_inc==31)		//右转
{
speed=PID_Control7(&PID_weizhi2,90,yaw);		
}
if(flag_inc==32)		//左转	
{
speed=PID_Control7(&PID_weizhi2,-90,yaw);	
}
if(flag_inc==34)		//先向左，后返回的左转
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==35)		//先向右，后返回的右转
{
speed=PID_Control7(&PID_weizhi2,180,yaw);	
}
if(flag_inc==36)		//先向右，后返回的右转
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==37)		//最后一段，先右转，再右转
{
speed=PID_Control7(&PID_weizhi2,180,yaw);	
}
if(flag_inc==38)		//这一段开环了
{
speed=PID_Control7(&PID_weizhi2,-90,yaw);	
}
if(flag_inc==39)		//开环结束后，然后要左转，然后循迹开环跑回去
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
if(flag_inc==54)		//第三段左转进去。然后右转准备回来
{
speed=PID_Control7(&PID_weizhi2,180,yaw);	
}
if(flag_inc==55)		//第三段左转进去。然后右转准备回来
{
speed=PID_Control7(&PID_weizhi2,0,yaw);	
}
if(flag_inc==56)		//第三段左转进去。然后右转准备回来
{
speed=PID_Control7(&PID_weizhi2,-180,yaw);	
}
if(flag_inc==57)		//第三段左转进去。然后右转准备回来
{
speed=PID_Control7(&PID_weizhi2,90,yaw);	
}



  MS20=0;
	}	 
		 
	  if(MS6>=2)
		 { 		 
			 OLED_Show3FNum(50,0,yaw ,3,3,12);		
		   OLED_Refresh_Gram();//更新显示到OLED	

       MS6=0;
	   }	 
			  if(MS8>=2)
		 { 
		 if(mpu_mpl_get_data(&pitch,&roll,&yaw)==0)
		{	
		} 

       MS8=0;
	   }	
		 
		  if(MS7>=5)//读取循迹值
		 { 
       read_Front_sensor(); 
			 
       MS7=0;
	   }
		 
		 
		 		  if(MS23>=10)//编码器参数计算
		 { 
       Encoder_Fabs();			
			 c1=c1+ Encoder_Fabs_L1;//单位mm
			 c2=c2+ Encoder_Fabs_L2; 
			 c3=c3+ Encoder_Fabs_R1;//单位mm//矫正
			 c4=c4+ Encoder_Fabs_R2; 	 
			 TIM2->CNT=30000;
			 TIM3->CNT=30000;
			 TIM4->CNT=30000;
			 TIM8->CNT=30000;		 
       MS23=0;
	   }
		 
		 
		 
		 
	
		   if(MS30>=2)//读取循迹值
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
		OLED_Refresh_Gram();//更新显示到OLED	
	}
	if(mode==2)
	{
	  	NRF24L01_RxPacket(r1x);						
		OLED_Show3FNum(50,0,r1x[0] ,3,3,12);	
	  OLED_ShowString( 0,0,(void*)"Rx OK",12);		
		OLED_Refresh_Gram();//更新显示到OLED	
	}	
	tt=0;
}
      
		 
		 
		 
		  TIM_ClearITPendingBit(TIM7,TIM_IT_Update);        
	 }
		
}

