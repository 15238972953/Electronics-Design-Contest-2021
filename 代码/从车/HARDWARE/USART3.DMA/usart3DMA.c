/*
******************************************************************************************************************
*Filename      :usart3_dma.c
*Programmer(s) :chu
*Description   :Design for usart3_dma

							 USART3_RX---PD9
							 USART3_TX---PD8
******************************************************************************************************************
*/
#include "usart3dma.h"
#include "oled.h"
#include "led.h"
u8 rec_data_u3[U3_DATA_LEN];   // ��������
u8 send_data_u3[U3_DATA_LEN]/*="{\"RGB_blocks\":\"find_R\"}"*/;

u8 angle_1,angle_2;
short angle_z;
float yaw_2;
/*
********************************************************************************************************************
*                  void  USART3_Init(void)
*
*Description : ����3�ĳ�ʼ�� 
							 USART3_RX---PD9
							 USART3_TX---PD8
*Arguments   : Baud������������
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
//void USART3_Init(int Baud)
//{
//	NVIC_InitTypeDef NVIC_InitStructure ;//�����жϽṹ��
// 	GPIO_InitTypeDef GPIO_InitStructure;//����IO��ʼ���ṹ��
//	USART_InitTypeDef USART_InitStructure;//���崮�ڽṹ��
//	DMA_InitTypeDef DMA_InitStructure;//����DMA�ṹ��

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);//�򿪴��ڶ�Ӧ������ʱ��

//	//**********************���� ���� DMA ���ã�DMA1_Stream6��**************************
//	// 0 ����DMAʱ��
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

//	// 1 DMA�����ж�����
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	// 2 DMAͨ������
//	DMA_DeInit(DMA1_Stream3);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);//�����ַ
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_data_u3;//�ڴ��ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//dma���䷽��
//	DMA_InitStructure.DMA_BufferSize = U3_DATA_LEN;//����DMA�ڴ���ʱ�������ĳ���
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����DMA���������ģʽ��һ������
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ

//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���������ֳ�
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//�ڴ������ֳ�
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//����DMA�Ĵ���ģʽ
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//����DMA�����ȼ���
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;  	//ָ����FIFO��ֵˮƽ
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; //ָ����Burstת�������ڴ洫��
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //ָ����Burstת��������Χת�� */

//	// 3 ����DMA1��ͨ��
//	DMA_Init(DMA1_Stream3, &DMA_InitStructure);
//	// 4 ʹ���ж�
//	DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,ENABLE);


//	/* 5.ʹ�ܴ��ڵ�DMA���ͽӿ� */
//    USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
//	// 6 �ر�ͨ��
//	DMA_Cmd(DMA1_Stream3,DISABLE);//�ȹر�

//	//**********************���� ���� DMA ����**************************
//	// 0 ����DMAʱ��
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//DMAͨ������
//	
//	// 2 DMAͨ������
//	DMA_DeInit(DMA1_Stream1);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);//�����ַ
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rec_data_u3;//�ڴ��ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//dma���䷽��
//	DMA_InitStructure.DMA_BufferSize = U3_DATA_LEN;//����DMA�ڴ���ʱ�������ĳ���
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����DMA���������ģʽ��һ������
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���������ֳ�
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�ڴ������ֳ�
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//����DMA�Ĵ���ģʽ
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//����DMA�����ȼ���

//	// 3 ����DMA1��ͨ��
//	DMA_Init(DMA1_Stream1, &DMA_InitStructure);
//	// 4 ʹ��ͨ��
//	DMA_Cmd(DMA1_Stream1,ENABLE);

//	/* 5.ʹ�ܴ��ڵ�DMA���� */
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);


//    //��ʼ�����ڲ���
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_InitStructure.USART_BaudRate = Baud;
//	//��ʼ������
//    USART_Init(USART3,&USART_InitStructure);


//	//�����ж�
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;               //ͨ������Ϊ�����ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //�ж�ռ�ȵȼ�
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�ж���Ӧ���ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�
//    NVIC_Init(&NVIC_InitStructure);

//	//����DMA��ʽ����
//	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
//	//����DMA��ʽ����
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);

//	//�ж�����
//	USART_ITConfig(USART3,USART_IT_TC,DISABLE);
//	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);
//	USART_ITConfig(USART3,USART_IT_TXE,DISABLE);
//	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);


//    //��������
//    USART_Cmd(USART3, ENABLE);

//    //����IO��ʱ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);

//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //�ܽ�ģʽ:�����
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //����:����ģʽ
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //������������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO���ٶ�
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //�ܽ�ָ��
//	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��


//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//�ܽ�ģʽ:�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //������������
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    //�ܽ�ָ��
//	GPIO_Init(GPIOD, &GPIO_InitStructure);      //��ʼ��
//}
void USART3_Init(u32 bound){
 GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	
	//USART3�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //GPIOB10��GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PB10��PB11

   //USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART3, &USART_InitStructure); //��ʼ������3
		
		//Usart1 NVIC ����
   NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����3�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		
  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3 
	
//	USART_ClearFlag(USART3, USART_FLAG_TC);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�	
	
}
/*
********************************************************************************************************************
*                  void  USART3_IRQHandler(void)
*
*Description : ����3���ͺ��� 
*Arguments   : BufferSRC:�������ݴ�ŵ�ַ��BufferSize:���������ֽ���
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART3_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)//UASRT DMA��������
{
	DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);
	DMA1_Stream3->NDTR = BufferSize;    //����BUFFER��С
	DMA1_Stream3->M0AR = (uint32_t)BufferSRC;   //���õ�ַ
	DMA1_Stream3->CR |= DMA_SxCR_EN;	//��DMA,��ʼ����
}



/*
********************************************************************************************************************
*                  void  USART3_IRQHandler(void)
*
*Description : ����3���պ��� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
//void USART3_IRQHandler(void)
//{
//	static uint8_t Uart3_Rec_Len = 0;
//	int t;
//	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //�����ж�
//	{
//		t= USART_ReceiveData(USART3);//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ��
//		Uart3_Rec_Len = U3_DATA_LEN - DMA1_Stream3->NDTR;	//����ӱ�֡���ݳ���

//		//***********֡���ݴ�����************//
////if((rec_data_u3[0]==0X55)&&(rec_data_u3[1]==0X53))//
////		{
//		
// //   }
//		  angle_1=rec_data_u3[7];
//			angle_2=rec_data_u3[6];
//			angle_z=(angle_1<<8)|angle_2;
//			yaw_2=angle_z/32768.0f*180.0f;

//		//*************************************//
//		USART_ClearITPendingBit(USART3, USART_IT_IDLE);         //����жϱ�־
//		DMA1_S1_Reset();                                       //�ָ�DMAָ�룬�ȴ���һ�εĽ���
//		
//  }

//		
//	else if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	{
//		USART_ClearITPendingBit(USART3, USART_IT_TC);

//		DMA1_Stream3->CR &= (uint32_t)(~DMA_SxCR_EN);   //�ر�DMA,�������
//	}
//	
//	
//}
extern u16 USART_RX_STA;
	int16_t Res_3;
	int num_3[4];
	int flagg=0;
void USART3_IRQHandler(void)                	//����1�жϷ������
	{

	static u8 state = 0;	
	static u8 bit_number=0;
  u8 i;	
	static u16 openmv[9];	//��ȡ����
	

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
		{ USART_ClearFlag(USART3, USART_FLAG_TC); 
			USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		  Res_3=USART_ReceiveData(USART3);	//��ȡ���յ�������
	LED1=!LED1;

	num_3[0]=Res_3;		
 OLED_ShowNum(50,40,num_3[0] ,3,12);		
	OLED_Refresh_Gram();//������ʾ��OLED					
			
		}
	}



/*
********************************************************************************************************************
*                  void DMA1_Stream3_IRQHandler(void)
*
*Description : ����3�����жϺ��� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void DMA1_Stream3_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream3,DMA_IT_TCIF3) != RESET)
    {
        /* �����־λ */
        DMA_ClearFlag(DMA1_Stream3,DMA_IT_TCIF3);
        /* �ر�DMA */
        DMA_Cmd(DMA1_Stream3,DISABLE);
        /* �򿪷�������ж�,ȷ�����һ���ֽڷ��ͳɹ� */
        USART_ITConfig(USART3,USART_IT_TC,ENABLE);
    }
}

/*
********************************************************************************************************************
*                  void DMA1_S1_Reset(void)
*
*Description : ����3�������� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void DMA1_S1_Reset(void)//DMA1_Stream6 ��������
{ 
	DMA_ClearFlag(DMA1_Stream1,DMA_IT_TCIF1|DMA_FLAG_HTIF1|DMA_FLAG_TEIF1|DMA_FLAG_DMEIF1|DMA_FLAG_FEIF1);  
	
	DMA_Cmd(DMA1_Stream1,DISABLE); //�ر�USART2 TX DMA1 ��ָʾ��ͨ��

 	//DMA_SetCurrDataCounter(DMA1_Channel5,Uart1_DMA_Len);//DMAͨ����DMA����Ĵ�С
	DMA1_Stream1->NDTR = U3_DATA_LEN;
 	//DMA_Cmd(DMA1_Channel5, ENABLE);                    
	DMA_Cmd(DMA1_Stream1,ENABLE); //ʹ��USART2 TX DMA1 ��ָʾ��ͨ��
	/* �����־λ */
   
}



/*****************************************************���� TF mini plus*//////////////////////////////////////////////////
/*****************************************************���� TF luna*//////////////////////////////////////////////////
/*****************************************************������115200*//////////////////////////////////////////////////

//u8 Receive_ok=0;

//void USART3_IRQHandler(void)
//{
//	static uint8_t Uart3_Rec_Len = 0;
//	static uint8_t i=0;
//	int t;
//	uint8_t sum=0;
//	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //�����ж�
//	{
//		t= USART_ReceiveData(USART3);//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ��
//		Uart3_Rec_Len = U3_DATA_LEN - DMA1_Stream3->NDTR;	//����ӱ�֡���ݳ��
//		GPIO_ResetBits(GPIOE,GPIO_Pin_4 );//GPIOF9,F10���øߣ�����
//     uint16_t distance=0;
//   if(rec_data_u3[0]==0x59)
//		{
//			GPIO_ResetBits(GPIOE,GPIO_Pin_3 );
//			if(rec_data_u3[1]==0x59)
//			{
//				for(i=0;i<Uart3_Rec_Len-1;i++)	
//				{	
//					sum+=rec_data_u3[i];
//				}
//				distance=(rec_data_u3[3]<<8)|rec_data_u3[2];
//		   Receive_ok=0;//����������ϱ�־
//			OLED_Show3FNum(0,15,distance,4,2,12);			
//		  OLED_Refresh_Gram();
//			 
//			}
//		}
//     USART_ClearITPendingBit(USART3, USART_IT_IDLE);         //����жϱ�־
//		DMA1_S1_Reset();                                       //�ָ�DMAָ�룬�ȴ���һ�εĽ���
//    }
//	else if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	{
//	
//		USART_ClearITPendingBit(USART3, USART_IT_TC);
//		DMA1_Stream3->CR &= (uint32_t)(~DMA_SxCR_EN);   //�ر�DMA,�������

//	}
//}


/****************************************************ţ�Ƽ���*//////////////////////////////////////////////////////////////////////////
/*****************************************************������9600*//////////////////////////////////////////////////
/*****************************************************��ʾ���жϻ���*////////////////////////////////////////////////// 
//u8 Num = 0;              //�������ݵĵ�ǰλ��
//int a222=0;
//void Read_LaserDis(unsigned char ID, unsigned int *Data)       
//{	
//	unsigned char y=0;
//	unsigned int Receive_data [3] = { 0 };       //���ݻ�����

//	Num = 0; 
/////////////////////////////��ȡ���롢����������������ǿ��ֵ///////////////////////////////
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, 0x57);		

//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, ID);																  //IDģ����
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
//	delay_ms(2);

//  while(1)
//  {
//		if(rec_data_u3[0] != 0x75) { Num = 0; }  //�ж�֡ͷ0x75,�������½���
//		if(Num == 8)
//		{
//			Num = 0;
//			if(rec_data_u3[7] == 0x07)  //�ж�֡β0x07,���߲���ֵ
//			{
//				Receive_data[0] = rec_data_u3[1];
//				Receive_data[0] <<= 8;
//				Receive_data[0] |= rec_data_u3[2];        
//				*Data = Receive_data[0];          //����
////				a222=rec_data_u3[1]*256+rec_data_u3[2];
////        OLED_ShowNum(50,42,a222,4,12);	
////    		OLED_Refresh_Gram();
////				
//				Receive_data[1] = rec_data_u3[3];
//				Receive_data[1] <<= 8;
//				Receive_data[1] |= rec_data_u3[4];
//				*(Data+1) = Receive_data[1];          //��������
//				
//				Receive_data[2] = rec_data_u3[5];
//				Receive_data[2] <<= 8;
//				Receive_data[2] |= rec_data_u3[6];
//				*(Data+2) = Receive_data[2];         //������ǿ        
//				
//				break;
//			}        
//			break;
//		}
//    else
//    {
//      delay_ms(1);y++;
//      if(y==10) { Num = 0;break; }
//    }
//  }
/////////////////////////////��ȡ���롢����������������ǿ��ֵ///////////////////////////////
//}

//void Set_LaserDis(unsigned char ID, unsigned char Fun,unsigned char Par)	       
//{	
// ///////////////////////////���ù��ܲ���///////////////////////////////	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, 0x4C);																//������ʼ�ź�
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	
//	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, ID);																  //IDģ����
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
//	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, Fun);																//������
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	
//	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, Par);																//����
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

/////////////////////////////���ù��ܲ���///////////////////////////////		
//}
//extern u16 openmv3[9];
//void USART3_IRQHandler(void)
//{
//	static uint8_t Uart3_Rec_Len = 0;
//   u8 Res;
//	
//	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //�����ж�
//	{
//		 Res= USART_ReceiveData(USART3);//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ�	
//		 Uart3_Rec_Len = U3_DATA_LEN - DMA1_Stream3->NDTR;	//����ӱ�֡���ݳ��
//	   GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_3);//GPIOF9,F10���øߣ�����
//     
//   		openmv3[1]=rec_data_u3[1];
//      openmv3[2]=rec_data_u3[2];
//      openmv3[3]=rec_data_u3[3];
//      openmv3[4]=rec_data_u3[4];
//			openmv3[5]=rec_data_u3[5];
//      openmv3[6]=rec_data_u3[6];
//			openmv3[7]=rec_data_u3[7];

//     USART_ClearITPendingBit(USART3, USART_IT_IDLE);         //����жϱ�־
//		 DMA1_S1_Reset();                                       //�ָ�DMAָ�룬�ȴ���һ�εĽ���
//    }
//	else if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	{
//	
//		USART_ClearITPendingBit(USART3, USART_IT_TC);
//		DMA1_Stream3->CR &= (uint32_t)(~DMA_SxCR_EN);   //�ر�DMA,�������

//	}
//}

void USART3_send_byte(uint8_t byte)
{
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);//�ȴ��������
	USART3->DR=byte;	
}

//���Ͷ��ֽ�����
void USART3_Send_bytes(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		USART3_send_byte(Buffer[i++]);
	}
}
//���Ͷ��ֽ�����+У���
void USART3_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//�ۼ�Length-1ǰ������
		USART3_send_byte(Buffer[i++]);
	}
}

//void send_com(u8 data)
//{
//	u8 bytes[3]={0};
//	bytes[0]=0xa5;
//	bytes[1]=data;//�����ֽ�
//	USART3_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
//}


///************************************************************
//*  ��ຯ�� 
//*  ע�⣺�ڳ�ʼ����ɱ���Ҫ���д���� �磺send_com(0x45);
//*   0x45: ���������������      
//*   0x50: ���������ģʽ
//*   0x51�����ٲ���ģʽ
//*   0x52���߾��Ȳ���ģʽ
//*   0x53: һ�����ģʽ
//************************************************************/
//void Mea_dis(void)
//{
//	u8 sum=0,i=0;
//	uint16_t distance=0;
//	uint16_t Strength=0;
//	double dis=0.0;
//	if(Receive_ok)//���ڽ������
//		{
//			distance=(rec_data_u3[3]<<8)|rec_data_u3[2];
//		   Receive_ok=0;//����������ϱ�־
//			OLED_Show3FNum(0,15,distance,4,2,12);			
//		  OLED_Refresh_Gram();
//			
//	 }
//}
/***************************************************************���� TF mini plus*/////////////////////////////////////////////////////////////////////////


/*
********************************************************************************************************************
*                  void DMA1_Stream3_IRQHandler(void)
*
*Description : ����3�����жϺ��� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/


