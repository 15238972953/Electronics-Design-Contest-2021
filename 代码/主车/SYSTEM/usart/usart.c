#include "sys.h"
#include "usart.h"	
#include "delay.h"	
#include "oled.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F4̽���߿�����
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/6/10
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
 
/*********************��ɫʶ��*/////////////////
//1------��ɫ
//2------��ɫ
//3------��ɫ

//ɨ��ģ��   xxx+xxx  ���Ϻ���
//openmv     xxx+xxx  ���Ϻ���

int sss=0;
int openmv_site=0;
int color_flag=0;
char SendData[8];
char SendData1[8];
char SendData2[8];
u8 saoma[9];
u8 shibie[9];
u8 flag;
u8 flag2=0;
u16 he1;//ɨ��ģ��
u16 he2;//ɨ��ģ��
u16 he3;//��ɫʶ��
u16 he4;//��ɫʶ��
int guocheng=1;
int color_site=0;
extern int Control_AND_Xunji;
extern int llll;
int xerror[10];
int yerror[10];
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

//��ʼ��IO ����1 
//bound:������
/***********************************************************************************��λ��*//////////////////////////////////////////////////////////////////////////////////////////////////////

//// p+=0.1;
////		 	if(p>3.14)  p=-3.14; 
////			DataScope_Get_Channel_Data(500*sin(p), 1 );
////			DataScope_Get_Channel_Data(500* tan(p), 2 );
////			DataScope_Get_Channel_Data( 500*cos(p), 3 ); 
////			DataScope_Get_Channel_Data( 100*p , 4 );   
////			DataScope_Get_Channel_Data(0, 5 );
////			DataScope_Get_Channel_Data(0 , 6 );
////			DataScope_Get_Channel_Data(0, 7 );
////			DataScope_Get_Channel_Data( 0, 8 ); 
////			DataScope_Get_Channel_Data(0, 9 );  
////			DataScope_Get_Channel_Data( 0 , 10);
////			Send_Count = DataScope_Data_Generate(10);
////			for( i = 0 ; i < Send_Count; i++) 
////			{
////			while((USART3->SR&0X40)==0);  
////			USART3->DR = DataScope_OutPut_Buffer[i]; 
////			}
////			delay_ms(50); //20HZ

//unsigned char DataScope_OutPut_Buffer[42] = {0};	   //���ڷ��ͻ�����
//void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
//{
//    unsigned char *point;
//    point = (unsigned char*)target;	  //�õ�float�ĵ�ַ
//    buf[beg]   = point[0];
//    buf[beg+1] = point[1];
//    buf[beg+2] = point[2];
//    buf[beg+3] = point[3];
//}

//void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
//{
//	if ( (Channel > 10) || (Channel == 0) ) return;  //ͨ����������10�����0��ֱ����������ִ�к���
//  else
//  {
//     switch (Channel)
//		{
//      case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
//      case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
//		  case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
//		  case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
//		  case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
//		  case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
//		  case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
//		  case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
//		  case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
//		  case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
//		}
//  }	 
//}


////����˵�������� DataScopeV1.0 ����ȷʶ���֡��ʽ
////Channel_Number����Ҫ���͵�ͨ������
////���ط��ͻ��������ݸ���
////����0��ʾ֡��ʽ����ʧ�� 
//unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
//{
//	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //ͨ����������10�����0��ֱ����������ִ�к���
//  else
//  {	
//	 DataScope_OutPut_Buffer[0] = '$';  //֡ͷ
//		
//	 switch(Channel_Number)   
//   { 
//		 case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;  
//		 case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
//		 case 3:   DataScope_OutPut_Buffer[13] = 13; return 14; 
//		 case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
//		 case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;  
//		 case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
//		 case 7:   DataScope_OutPut_Buffer[29] = 29; return 30; 
//		 case 8:   DataScope_OutPut_Buffer[33] = 33; return 34; 
//		 case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
//     case 10:  DataScope_OutPut_Buffer[41] = 41; return 42; 
//   }	 
//  }
//	return 0;
//}
/***********************************************************************************��λ��*//////////////////////////////////////////////////////////////////////////////////////////////////////

//void uart_init(u32 bound){
//   //GPIO�˿�����
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
// 
//	//����1��Ӧ���Ÿ���ӳ��
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
//	
//	//USART1�˿�����
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

//   //USART1 ��ʼ������
//	USART_InitStructure.USART_BaudRate = bound;//����������
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
//  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
//	
//  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
//	
//	USART_ClearFlag(USART1, USART_FLAG_TC);
//	
//#if EN_USART1_RX	
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

//	//Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

//#endif
//	
//}
#endif	

//void USART1_IRQHandler(void)                	//����1�жϷ������
//	{
//	int16_t Res;
//	static u8 state = 0;	
//	static u8 bit_number=0;
//  u8 i;	
//	static u16 openmv[9];	//��ȡ����
//	

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
//		{ USART_ClearFlag(USART1, USART_FLAG_TC); 
//			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//		  Res=USART_ReceiveData(USART1);	//��ȡ���յ�������
//				
//	GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_3);//GPIOF9,F10���øߣ�����

//			//USART_SendData(USART3,Res);//�ش����յ�������		
//	//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET)
//		//	Delay_ms(100);		
//if((state==0)&&(Res==0xb3))  
//	{	
//		state=1;
//		openmv[bit_number++]=Res;
//	}

//	else if(state==1)
//	{
//		openmv[1]=Res;
//			
//		 state=2;
//	}
//	else if(state==2)
//	{ 
//		openmv[2]=Res;

//		state=3;
//	}
//	else if(state==3)
//	{ 
//		openmv[3]=Res;
//				
//		state=4;
//	}
//	
//	else if(state==4)
//	{
//		openmv[4]=Res;
//		
//		 state=5;
//	}
//	else if(state==5)
//	{ 
//		openmv[5]=Res;
//			
//		state=6;
//	}
//	else if(state==6)
//	{ 
//		openmv[6]=Res;
//	          OLED_ShowNum(40,12,openmv[1],4,12);
//						OLED_ShowNum(40,24,openmv[2],4,12);
//						OLED_ShowNum(40,36,openmv[3],4,12);
//						OLED_ShowNum(40,48,openmv[4],4,12);
//						OLED_ShowNum(80,12,openmv[5],4,12);
//						OLED_Refresh_Gram();
//		state=7;
//	}
//					else if(state==7)		//����Ƿ���ܵ�������־
//	      {
//        	if(Res == 0x5b)
//        	{	

//						state = 0;
//            		openmv[7]=Res;
//        	}
//        	else if(Res != 0x5b)
//        	{
//           		 state = 0;
//            		for(i=0;i<8;i++)
//            		{
//               			 openmv[i]=0x00;
//            		}           
//        	}
//				}
//						

//				USART_RX_STA=0;
//		}}


	void uart_init2(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
	

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

}

//unsigned char ReceiveData;    //���ܴ洢����
//int16_t Res;
//int16_t Res_1;
//extern u16 openmv2[9];
//void USART2_IRQHandler(void)                	//����1�жϷ������
//	{
//	int16_t Res;
//	static u8 state = 0;	
//	static u8 bit_number=0;
//  u8 i;	
//			int t;
//	static uint8_t Uart2_Rec_Len = 0;
//	static u16 hmi_num[6];	//��ȡ���
//	static u16 openmv[9];	//��ȡ����
//	

//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�
//		{ USART_ClearFlag(USART2, USART_FLAG_TC); 
//			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//		  Res=USART_ReceiveData(USART2);	//��ȡ���յ�������
//				USART_SendData(USART2,Res);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_3);//GPIOF9,F10���øߣ�����
//if(state==0&&Res==0x01)
//	
//	{		hmi_num[0]=Res; 
//		state=1;
//	
//		
//	}

//	else if(state==1)
//	{
//		hmi_num[1]=Res;	
//		openmv2[1]=hmi_num[1];
//		state=2;	
//	}
//	else if(state==2)
//	{ 
//		hmi_num[2]=Res;	
//		openmv2[2]=hmi_num[2];
//		 state=3;
//	}
//		else if(state==3)
//	{ 
//		hmi_num[3]=Res;	
//		openmv2[3]=hmi_num[3];
//		 state=4;
//	}
//			else if(state==4)
//	{ 
//		hmi_num[4]=Res;	
//		openmv2[4]=hmi_num[4];
//		 state=5;
//	}
//	else if(state==5)
//	{
//		hmi_num[5]=Res;	
//		openmv2[5]=hmi_num[5];
//		state=6;	
//	}
//	else if(state==6)
//	{ 
//		hmi_num[6]=Res;	
//		openmv2[6]=hmi_num[6];
//		 state=7;
//	}
//		else if(state==7)
//	{ 
//		hmi_num[7]=Res;	
//		openmv2[7]=hmi_num[7];
//		 state=8;
//	}
//			else if(state==8)
//	{ 
//		hmi_num[8]=Res;	
//		openmv2[8]=hmi_num[8];
//		 state=9;
//	}
//	else if(state==9)
//	{ 
//        	if(Res == 0x02)
//        	{	

//						state = 0;
//							for(i=0;i<10;i++)
//            		{
//               			 hmi_num[i]=0x00;
//            		}     
////            hmi_num[2]=Res;
//        	}
//        	else if(Res!= 0x02)
//        	{
//           		 state = 0;
//            		for(i=0;i<10;i++)
//            		{
//               			 hmi_num[i]=0x00;
//            		}           
//        	}
//				}
//						

//						

//				USART_RX_STA=0;
//		}}


//void HMISendstart(void)
//{
//	 	delay_ms(200);
//		HMISendb(0xff);
//		delay_ms(200);
//}
//void HMISends(char *buf1)		  //�ַ������ͺ���
//{
//	 u8 i=0;
//	 while(1)
//	{
//	    if(buf1[i]!=0)
//	 	 {
//			   USART_SendData(USART2,buf1[i]);  //����һ���ֽ�
//			   while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
//		   	 i++;
//		 }
//	    else 
//	       return ;
//	}
//}
//void HMISendb(u8 k)		         //�ֽڷ��ͺ���
//{		 
//	  u8 i;
//	  for(i=0;i<3;i++)
//	 {
//	     if(k!=0)
//	 	  {
//			    USART_SendData(USART2,k);  //����һ���ֽ�
//			    while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
//		  }
//	     else 
//	        return ;
//	 } 
//} 


