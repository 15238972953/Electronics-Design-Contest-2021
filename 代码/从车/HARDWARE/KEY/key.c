#include "key.h"
#include "delay.h" 
#include "oled.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//*********************************************************************************����ʾ������*********************************************************************************************�//
//	   OLED_ShowString(16,4,"LED_TEST",12);
//	   OLED_Refresh_Gram();//������ʾ��OLED	
//		key=KEY_Scan(0);	//�õ���ֵ
//		if(key)
//		{						   
//			switch(key)
//			{				 
//							case KEY1_PRES:									
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);							
//							break;
//						 
//						 case KEY2_PRES:	
//						  LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);
//						 break;
//						 
//						 case KEY3_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	  
//						 delay_ms(100);
//						 break;
//						 
//						 case KEY4_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);
//							break;
//						 
//						 case KEY5_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 	delay_ms(100);
//							break;
//						 
//						 case KEY6_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);
//							break;
//						 
//			}
//			}

extern  int16_t Res_2;
extern int key;
int Mod=0;
void mode_set(void)
{

while(1)	
	{ 

		if(Res_2=='a')
		{
		  OLED_ShowCHinese( 16, 0,0);//����
		OLED_ShowCHinese( 32, 0,1);
		OLED_ShowNum(48,16,1,3,16);			
		OLED_Refresh_Gram();	
			Mod=1;
			Res_2='z';
		}
		if(Res_2=='b')
		{
		  OLED_ShowCHinese( 16, 0,0);//����
		OLED_ShowCHinese( 32, 0,1);
		OLED_ShowNum(48,16,2,3,16);			
		OLED_Refresh_Gram();	
				Mod=2;
			Res_2='z';
		}
	  if(Res_2=='c')
		{
		  OLED_ShowCHinese( 16, 0,0);//����
		OLED_ShowCHinese( 32, 0,1);
		OLED_ShowNum(48,16,3,3,16);			
		OLED_Refresh_Gram();
	Mod=3;			
			Res_2='z';
		}
		if(Res_2=='d')
		{
		 OLED_ShowCHinese( 16, 0,0);//����
		OLED_ShowCHinese( 32, 0,1);
		OLED_ShowNum(48,16,4,3,16);			
		OLED_Refresh_Gram();
	Mod=4;			
			Res_2='z';
		}
	  if(Res_2=='e')
		{
    OLED_ShowCHinese( 16,16,2);//��������
		OLED_ShowCHinese( 32,16,3);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
		OLED_ShowNum(80,16,1,3,16);			
		OLED_Refresh_Gram();
				Mod=5;
			Res_2='z';
		}
		if(Res_2=='f')
		{
		  OLED_ShowCHinese( 16,16,2);//��������
		OLED_ShowCHinese( 32,16,3);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
		OLED_ShowNum(80,16,2,3,16);	
OLED_Refresh_Gram();
	Mod=6;			
			Res_2='z';
		}
	  if(Res_2=='g')
		{
		  OLED_ShowCHinese( 16,16,2);//��������
		OLED_ShowCHinese( 32,16,3);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
		OLED_ShowNum(80,16,3,3,16);	
OLED_Refresh_Gram();
	Mod=7;			
			Res_2='z';
		}
		if(Res_2=='h')
		{
		  OLED_ShowCHinese( 16,16,2);//��������
		OLED_ShowCHinese( 32,16,3);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
		OLED_ShowNum(80,16,4,3,16);
OLED_Refresh_Gram();			
				Mod=8;
			Res_2='z';
		}
		if(Res_2=='i')
		{
		  OLED_ShowCHinese( 16,16,4);//���Ӳ���
		OLED_ShowCHinese( 32,16,5);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,1,3,16);
OLED_Refresh_Gram();			
				Mod=9;
			Res_2='z';
		}
		if(Res_2=='j')
		{
		 		  OLED_ShowCHinese( 16,16,4);//���Ӳ���
		OLED_ShowCHinese( 32,16,5);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,2,3,16);
OLED_Refresh_Gram();
	Mod=10;			
			Res_2='z';
		}
	  if(Res_2=='k')
		{
		  		  OLED_ShowCHinese( 16,16,4);//���Ӳ���
		OLED_ShowCHinese( 32,16,5);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,3,3,16);
OLED_Refresh_Gram();
	Mod=11;			
			Res_2='z';
		}
		if(Res_2=='l')
		{
				  OLED_ShowCHinese( 16,16,4);//���Ӳ���
		OLED_ShowCHinese( 32,16,5);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,4,3,16);
OLED_Refresh_Gram();
	Mod=12;			
			Res_2='z';
		}
		if(Res_2=='m')
		{
		OLED_ShowCHinese( 16,16,6);//��չ����
		OLED_ShowCHinese( 32,16,7);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,1,3,16);
OLED_Refresh_Gram();
	Mod=13;			
			Res_2='z';
		}
		if(Res_2=='n')
		{
		 OLED_ShowCHinese( 16,16,6);//��չ����
		OLED_ShowCHinese( 32,16,7);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,2,3,16);
OLED_Refresh_Gram();
	Mod=14;			
			Res_2='z';
		}
	  if(Res_2=='o')
		{
		 OLED_ShowCHinese( 16,16,6);//��չ����
		OLED_ShowCHinese( 32,16,7);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,3,3,16);
OLED_Refresh_Gram();
	Mod=15	;		
			Res_2='z';
		}
		if(Res_2=='p')
		{
		OLED_ShowCHinese( 16,16,6);//��չ����
		OLED_ShowCHinese( 32,16,7);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
			OLED_ShowNum(80,16,4,3,16);
OLED_Refresh_Gram();		  
				Mod=16;
			Res_2='z';
		}
	key=KEY_Scan(0);	//�õ���ֵ	
		if(key==KEY6_PRES)
			{	  
				break;
			}	
		
	}

OLED_Clear( );


}




//while(1)	
//	{ 
//		
//		OLED_ShowString(0,12,"bujin1",12);
//	  OLED_ShowString(0,24,"bujin2",12);
//	  OLED_ShowString(0,36,"bujin3",12);
//	  OLED_ShowString(0,48,"bujin4",12);
//	  OLED_ShowString(40,0,"angle",12);
//		OLED_ShowString(80,0,"speed",12);
//		OLED_Refresh_Gram();//������ʾ��OLED	
//		OLED_ShowNum(40,12,steppingmotor1_angle,4,12);
//		OLED_ShowNum(40,24,steppingmotor2_angle,4,12);
//		OLED_ShowNum(40,36,steppingmotor3_angle,4,12);
//		OLED_ShowNum(40,48,steppingmotor4_angle,4,12);
//		OLED_ShowNum(80,12,steppingmotor1_speed,4,12);
//		OLED_ShowNum(80,24,steppingmotor2_speed,4,12);
//		OLED_ShowNum(80,36,steppingmotor3_speed,4,12);
//		OLED_ShowNum(80,48,steppingmotor4_speed,4,12);
//		if(Res_1=='a')
//		{
//		  steppingmotor1_speed=steppingmotor1_speed+10;
//			Res_1='z';
//		}
//		if(Res_1=='b')
//		{
//		  steppingmotor1_speed=steppingmotor1_speed-10;
//			Res_1='z';
//		}
//	  if(Res_1=='c')
//		{
//		  steppingmotor1_angle=steppingmotor1_angle+10;
//			Res_1='z';
//		}
//		if(Res_1=='d')
//		{
//		  steppingmotor1_angle=steppingmotor1_angle-10;
//			Res_1='z';
//		}
//	  if(Res_1=='e')
//		{
//		  steppingmotor2_speed=steppingmotor2_speed+10;
//			Res_1='z';
//		}
//		if(Res_1=='f')
//		{
//		  steppingmotor2_speed=steppingmotor2_speed-10;
//			Res_1='z';
//		}
//	  if(Res_1=='g')
//		{
//		  steppingmotor2_angle=steppingmotor2_angle+10;
//			Res_1='z';
//		}
//		if(Res_1=='h')
//		{
//		  steppingmotor2_angle=steppingmotor2_angle-10;
//			Res_1='z';
//		}
//		if(Res_1=='i')
//		{
//		  steppingmotor3_speed=steppingmotor3_speed+10;
//			Res_1='z';
//		}
//		if(Res_1=='j')
//		{
//		  steppingmotor3_speed=steppingmotor3_speed-10;
//			Res_1='z';
//		}
//	  if(Res_1=='k')
//		{
//		  steppingmotor3_angle=steppingmotor3_angle+10;
//			Res_1='z';
//		}
//		if(Res_1=='l')
//		{
//		  steppingmotor3_angle=steppingmotor3_angle-10;
//			Res_1='z';
//		}
//		if(Res_1=='m')
//		{
//		  steppingmotor4_speed=steppingmotor4_speed+10;
//			Res_1='z';
//		}
//		if(Res_1=='n')
//		{
//		  steppingmotor4_speed=steppingmotor4_speed-10;
//			Res_1='z';
//		}
//	  if(Res_1=='o')
//		{
//		  steppingmotor4_angle=steppingmotor4_angle+10;
//			Res_1='z';
//		}
//		if(Res_1=='p')
//		{
//		  steppingmotor4_angle=steppingmotor4_angle-10;
//			Res_1='z';
//		}
//	key=KEY_Scan(0);	//�õ���ֵ	
//		if(key==KEY2_PRES)
//			{	  
//				break;
//			}	
//		
//	}
//	 OLED_Clear( );
//	while(1)	
//	{ 
//		
//		OLED_ShowString(0,12,"pwm",12);
//		OLED_Refresh_Gram();//������ʾ��OLED	
//		OLED_ShowNum(40,12,pwm,4,12);
//		if(Res_1=='q')
//		{
//		  pwm=pwm+100;
//			Res_1='z';
//		}
//		if(Res_1=='r')
//		{
//		  pwm=pwm-100;
//			Res_1='z';
//		}
//		if(Res_1=='s')
//		{
//		  OLED_ShowString(40,36,"Front ",12);
//			Res_1='z';
//		}
//		if(Res_1=='t')
//		{
//		  OLED_ShowString(40,36,"Beside",12);
//			Res_1='z';
//		}
//		if(Res_1=='u')
//		{
//		  OLED_ShowString(40,36,"Left  ",12);
//			Res_1='z';
//		}
//		if(Res_1=='v')
//		{
//		  OLED_ShowString(40,36,"Right ",12);
//			Res_1='z';
//		}
//	  key=KEY_Scan(0);	//�õ���ֵ	
//		if(key==KEY2_PRES)
//			{	  
//				break;
//			}	
//    			
//	}
//	 OLED_ShowString( 0,0,(void*)"Init Finished",12);	
//	 OLED_Refresh_Gram();
//	 OLED_Clear( );








//������ʼ������
void KEY_Init(void)
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0|KEY7==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3;
		else if(KEY4==0)return 4;
		else if(KEY5==0)return 5;
		else if(KEY6==0)return 6;
		else if(KEY7==0)return 7;
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1&&KEY2==1)key_up=1; 	    
 	return 0;// �ް�������
}

//	key=KEY_Scan(0);	//�õ���ֵ
//		if(key)
//		{						   
//			 switch(key)
//			{	
//			 case KEY2_PRES:	
//					
//				GPIO_ResetBits(GPIOE, GPIO_Pin_0);
//			 
//			 USART_SendData(USART3,'1');
//				delay_ms(100);	   	
//				break;
//						 
//			 case KEY3_PRES:	
//					
//				GPIO_ResetBits(GPIOE, GPIO_Pin_1);
//        USART_SendData(USART3,'2');
//				delay_ms(100);	   
//				
//				
//				break;
//				
//				case KEY4_PRES:	
//					
//				GPIO_ResetBits(GPIOE, GPIO_Pin_3);
//        USART_SendData(USART3,'3');
//				delay_ms(100);	   
//								
//				break;
//			}
//		}