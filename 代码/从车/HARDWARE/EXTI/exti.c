#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "xunji.h"
#include "stdio.h"
#include "usart.h"
#include "oled.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

////�ⲿ�ж�0�������
//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);	//����
//	if(WK_UP==1)	 
//	{
//		BEEP=!BEEP; //��������ת 
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
//}	
//�ⲿ�ж�2�������

int Front_cishu=1;
int Left_cishu=100;

int First_count=0;
int Second_count=0;

int First_count2=0;
int Second_count2=0;

int First_count3=0;
int Second_count3=0;

int First_count4=0;
int Second_count4=0;

int First_count5=0;
int Second_count5=0;

int First_count6=0;
int Second_count6=0;

int First_count7=0;
int First_count8=0;
int First_count9=0;
int First_count10=0;
int First_count11=0;
int First_count12=0;
int First_count13=0;
int First_count14=0;
int First_count15=0;
int First_count16=0;
int First_count17=0;
int First_count18=0;
int First_count19=0;
int First_count20=0;
int First_count21=0;
int First_count22=0;
int First_count23=0;
int First_count24=0;
int First_count25=0;
int First_count26=0;
int First_count27=0;
int First_count28=0;
int First_count29=0;
int First_count30=0;
int First_count31=0;
int First_count32=0;
int First_count33=0;
int First_count34=0;
int First_count35=0;
int First_count36=0;
int First_count37=0;
int First_count38=0;
int First_count39=0;
int First_count40=0;


int Second_count7=0;

extern int Control_AND_Xunji;
extern int zd_site;
//void EXTI2_IRQHandler(void)
//{
//	delay_ms(10);	//����
//	if(KEY4==0)	  
//	{				 
//   GPIO_ResetBits(GPIOE,GPIO_Pin_6) ;//��λF9 ����D1
//	 delay_ms(1000);	
//	 GPIO_SetBits(GPIOE,GPIO_Pin_6) ;//��λF9 ����D1
//	 delay_ms(1000);	
//		
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
//}
////�ⲿ�ж�3�������


//void EXTI9_5_IRQHandler(void)
//{
//		static int flag1=0;
//    delay_ms(10);	//����
//	  if(flag1==1)
//	{
//	   gezi=1;
//	}
//	 flag1++;
//	 EXTI_ClearITPendingBit(EXTI_Line9); //���LINE0�ϵ��жϱ�־λ 
//}	


void EXTI3_IRQHandler(void)/////////////ǰ��222
{
	static int flag2=0;
	delay_ms(20);	//����
  if(Left_cishu==1) 
	 {if(flag2==1)
			{
			  Second_count=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
	 }
	 }
	 
	if(Left_cishu==2)
	{	if(flag2==1)
			{
				Second_count4=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}	
	
	if(Left_cishu==6)
	{	if(flag2==1)
			{
				First_count10=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}
		if(Left_cishu==8)
	{
		if(flag2==1)
			{
				First_count13=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}
		if(Left_cishu==11)
	{
		if(flag2==1)
			{
				First_count24=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}

		
	
		
   flag2++;	
	 EXTI_ClearITPendingBit(EXTI_Line3); //���LINE0�ϵ��жϱ�־λ 
}	
	
void EXTI0_IRQHandler(void)//////////////////ǰ��111
{
	static int flag1=0;
	static int FLAG1=0;
	delay_ms(20);	//����
 
	
	 
		
	
		if(Left_cishu==14)
		{
			if(flag1==1)
					{
						First_count37=0;
					}		
			if(flag1==3)
					{
						First_count37=1;
					}	
			if(flag1==5)
					{
						First_count37=2;
					}	
					if(flag1==7)
					{
						First_count37=3;
						EXTIX1_Init(DISABLE);
						flag1=0;
					}	
				}
		
//		if(Left_cishu==15)
//		{
//			if(flag1==1)
//					{
//						First_count39=0;
//					}		
//			if(flag1==3)
//					{
//						First_count39=1;
//					}	
//			if(flag1==5)
//					{
//						First_count39=2;
//					}	
//					if(flag1==7)
//					{
//						First_count39=3;
//					}	
//					if(flag1==9)
//					{
//						First_count39=4;
//					}	
//					if(flag1==11)
//					{
//						First_count39=5;
//						EXTIX1_Init(DISABLE);
//						flag1=0;
//					}	
//				}
				
				
				flag1++;	
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	

void EXTI2_IRQHandler(void)/////////////////////��ǰ333
{
	static int flag3=0;
	delay_ms(20);	//����
		if(Left_cishu==1)
		{
			if(flag3==1)
					{
						Second_count2=1;
						EXTIX3_Init(DISABLE);
						flag3=0;				
					}		
		}
if(Left_cishu==6)	
		{
		
			if(flag3==1)
			{
				First_count18=1;
				EXTIX3_Init(DISABLE);
				flag3=0;
			}
		}
		 if(Left_cishu==8)	
		{
			
			if(flag3==1)
			{
				First_count20=1;
					EXTIX3_Init(DISABLE);
				flag3=0;
			}
		}
			if(Left_cishu==10)	
		{
			
			if(flag3==1)
			{
				First_count22=1;
				EXTIX3_Init(DISABLE);
				flag3=0;
			}
		} 			
		

		
		
   flag3++;	
	 EXTI_ClearITPendingBit(EXTI_Line2); //���LINE0�ϵ��жϱ�־λ 
}	

void EXTI9_5_IRQHandler(void)//////////////////����444
{
	static int flag4=0;
	delay_ms(20);	//����
if(Left_cishu==1)	
{
		if(flag4==1)
			{
				Second_count3=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}	
if(Left_cishu==2)	
{
		if(flag4==1)
			{
				Second_count5=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}	
if(Left_cishu==4)	
{
		if(flag4==1)
			{
				First_count31=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}

if(Left_cishu==12)	
{
		if(flag4==1)
			{
				First_count26=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}	

if(Left_cishu==14)
		{
			if(flag4==1)
					{		
						First_count38=1;
						EXTIX4_Init(DISABLE);
						flag4=0;
					}		
				}
if(Left_cishu==15)
		{
			if(flag4==1)
					{		
						First_count40=1;
						EXTIX4_Init(DISABLE);
						flag4=0;
					}		
				}		
   flag4++;	
	 EXTI_ClearITPendingBit(EXTI_Line9); //���LINE0�ϵ��жϱ�־λ 
	
}


void EXTI15_10_IRQHandler(void)////////////////���555
{
	static int flag5=0;
	delay_ms(20);	//����
  if(Left_cishu==1)	
		{if(flag5==1)
			{
				First_count3=1;
				EXTIX5_Init(DISABLE);
				EXTIX4_Init(ENABLE);
				flag5=0;
			}
		}
		
		if(Left_cishu==2)
		{
			if(flag5==1)
					{
						Second_count4=0;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						Second_count4=1;
						EXTIX5_Init(DISABLE);
							zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						Second_count4=2;
						EXTIX5_Init(DISABLE);
							zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==7)
			{
				Second_count4=3;
				EXTIX5_Init(DISABLE);
					zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
			}	
			if(flag5==9)
			{
				Second_count4=4;
				EXTIX5_Init(DISABLE);
					zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
			}
			if(flag5==11)
			{
			Second_count4=5;
				EXTIX5_Init(DISABLE);
					zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
			}
			if(flag5==13)
			{
				Second_count4=6;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}		
		}	
		
		if(Left_cishu==4)
		{
			if(flag5==1)
					{
						First_count6=0;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						First_count6=1;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						First_count6=2;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==7)
			{
				First_count6=3;
				EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
			}	
			if(flag5==9)
			{
			  First_count6=4;
				EXTIX5_Init(DISABLE);
				EXTIX4_Init(ENABLE);
				flag5=0;
			}
			
		}	
		
		 if(Left_cishu==5)	
		{if(flag5==1)
			{
				First_count17=1;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}
		}	
		 
		  if(Left_cishu==7)	
		{
			if(flag5==1)
			{
				First_count19=1;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}
		}
		
		 if(Left_cishu==9)	
		{
			if(flag5==1)
			{
				First_count21=1;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}			
		}
		
		
	
			if(Left_cishu==12)
		{
			if(flag5==1)
					{
						First_count25=0;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						First_count25=1;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						First_count25=2;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==7)
			{
				First_count25=3;
				EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
			}	
			if(flag5==9)
			{
				First_count25=4;
				EXTIX5_Init(DISABLE);
				flag5=0;	
			}	
		}	
		
			if(Left_cishu==100)
		{
			if(flag5==1)
					{
						First_count36=0;
					}		
			if(flag5==3)
					{
						First_count36=1;
						EXTIX5_Init(DISABLE);
						flag5=0;	
					}	
		}	
		
			if(Left_cishu==15)
		{
			if(flag5==1)
					{
						First_count39=0;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						First_count39=1;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						First_count39=2;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}	
					if(flag5==7)
					{
						First_count39=3;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}	
					if(flag5==9)
					{
						First_count39=4;
					EXTIX5_Init(DISABLE);
						EXTIX4_Init(ENABLE);
						flag5=0;
					}	
					
				}
		
   flag5++;	
	 EXTI_ClearITPendingBit(EXTI_Line11); //���LINE0�ϵ��жϱ�־λ 
}	

void EXTI1_IRQHandler(void)/////////////////����666
{
	static int flag6=0;
	delay_ms(20);	//����
	
		if(Left_cishu==1)
		{if(flag6==1)
		    {
			    First_count=0;
					GPIO_SetBits(GPIOE,GPIO_Pin_1) ;//��λF9 ����D1
		    }
		if(flag6==3)
				{
					First_count=1;
				}
		if(flag6==5)
				{
					First_count=3;
						
				}		
	  if(flag6==7)
				{
					First_count=4;
				
				}		
				if(flag6==9)
				{
					First_count=5;
				
				}	
					if(flag6==11)
				{
					First_count=6;
					//First_count=6;
					EXTIX6_Init(DISABLE);
					//EXTIX2_Init(ENABLE);
					flag6=0;
				}		  	
			}	
	
	
	
	
	
	
	if(Left_cishu==2)	
	{	
	   
			if(flag6==1)
			{
				First_count4=0;
			}
		
			if(flag6==3)
			{
				First_count4=1;
				EXTIX6_Init(DISABLE);
				EXTIX2_Init(ENABLE);
				flag6=0;
			}
	}
	if(Left_cishu==3)	
		{
			if(flag6==1)
			{
				First_count5=0;
			}
		
			if(flag6==3)
			{
				First_count5=1;
			}
				if(flag6==5)
			{
				First_count5=2;
				EXTIX6_Init(DISABLE);
				//EXTIX2_Init(ENABLE);
				flag6=0;
			}
	 	}
	if(Left_cishu==11)	
		{
			if(flag6==1)
			{
				First_count23=0;
			}
		
			if(flag6==3)
			{
				First_count23=1;
				EXTIX6_Init(DISABLE);
				EXTIX2_Init(ENABLE);
				flag6=0;
			}

	 	}

	 	
   flag6++;	
	 EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ 
}	

//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX1_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
  XUNJI_Front_GPIO_Init();
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 ���ӵ��ж���0
// 
//	/* ����EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
//  EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);//PA0 ���ӵ��ж���0
 
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}


void EXTIX2_Init(FunctionalState NewState)
{
	
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
//	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
  XUNJI_Front_GPIO_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource2);//PE2 ���ӵ��ж���2
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource3);//PE3 ���ӵ��ж���3
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource4);//PE4 ���ӵ��ж���4

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);//PA0 ���ӵ��ж���0
  /* ����EXTI_Line0 */
//  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
//  EXTI_Init(&EXTI_InitStructure);//����
	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
//	
//	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	

//	
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
}

void EXTIX3_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
  XUNJI_Front_GPIO_Init();
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 ���ӵ��ж���0
// 
//	/* ����EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
//  EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2);//PA0 ���ӵ��ж���0
 
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}

void EXTIX4_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
  XUNJI_Front_GPIO_Init();
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 ���ӵ��ж���0
// 
//	/* ����EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
//  EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 ���ӵ��ж���0
 
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}

void EXTIX5_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
  XUNJI_Front_GPIO_Init();
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 ���ӵ��ж���0
// 
//	/* ����EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
//  EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);//PA0 ���ӵ��ж���0
 
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}

void EXTIX6_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
  XUNJI_Front_GPIO_Init();
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 ���ӵ��ж���0
// 
//	/* ����EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
//  EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);//PA0 ���ӵ��ж���0
 
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}






