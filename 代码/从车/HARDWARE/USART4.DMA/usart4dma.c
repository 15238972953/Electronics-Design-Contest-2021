/*
******************************************************************************
*Filename      :uart4_dma.c
*Programmer(s) :����ͺ����
*Description   :2019����
******************************************************************************
*/

#include "usart4dma.h"
#include "oled.h"
#include "led.h"
#include "delay.h"
/************************************************** MINI Balance��λ�� *//////////////////////////////////////////////////////////////

// p+=0.1;
//		 	if(p>3.14)  p=-3.14; 
//			DataScope_Get_Channel_Data(500*sin(p), 1 );
//			DataScope_Get_Channel_Data(500* tan(p), 2 );
//			DataScope_Get_Channel_Data( 500*cos(p), 3 ); 
//			DataScope_Get_Channel_Data( 100*p , 4 );   
//			DataScope_Get_Channel_Data(0, 5 );
//			DataScope_Get_Channel_Data(0 , 6 );
//			DataScope_Get_Channel_Data(0, 7 );
//			DataScope_Get_Channel_Data( 0, 8 ); 
//			DataScope_Get_Channel_Data(0, 9 );  
//			DataScope_Get_Channel_Data( 0 , 10);
//			Send_Count = DataScope_Data_Generate(10);
//			for( i = 0 ; i < Send_Count; i++) 
//			{
//			while((USART3->SR&0X40)==0);  
//			USART3->DR = DataScope_OutPut_Buffer[i]; 
//			}
//			delay_ms(50); //20HZ
extern unsigned int Temp_Data[3] ;       //���ݻ�����
unsigned char DataScope_OutPut_Buffer[42] = {0};	   //���ڷ��ͻ�����
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //�õ�float�ĵ�ַ
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}

void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
	if ( (Channel > 10) || (Channel == 0) ) return;  //ͨ����������10�����0��ֱ����������ִ�к���
  else
  {
     switch (Channel)
		{
      case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
      case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
		  case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
		  case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
		  case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
		  case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
		  case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
		  case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
		  case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
		  case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
		}
  }	 
}


//����˵�������� DataScopeV1.0 ����ȷʶ���֡��ʽ
//Channel_Number����Ҫ���͵�ͨ������
//���ط��ͻ��������ݸ���
//����0��ʾ֡��ʽ����ʧ�� 
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //ͨ����������10�����0��ֱ����������ִ�к���
  else
  {	
	 DataScope_OutPut_Buffer[0] = '$';  //֡ͷ
		
	 switch(Channel_Number)   
   { 
		 case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;  
		 case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
		 case 3:   DataScope_OutPut_Buffer[13] = 13; return 14; 
		 case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
		 case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;  
		 case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
		 case 7:   DataScope_OutPut_Buffer[29] = 29; return 30; 
		 case 8:   DataScope_OutPut_Buffer[33] = 33; return 34; 
		 case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
     case 10:  DataScope_OutPut_Buffer[41] = 41; return 42; 
   }	 
  }
	return 0;
}

/************************************************** MINI Balance��λ�� *//////////////////////////////////////////////////////////////




u8 rec_data_u4[U4_DATA_LEN];      // �������ݵ�ַ
u8 send_data_u4[U4_DATA_LEN];     // �������ݵ�ַ

/*
********************************************************************************************************************
*                  void  UART4_Init(void)
*
*Description : ����4�ĳ�ʼ�� 
							 UART4_RX---PC11
							 UART4_TX---PC10
*Arguments   : Baud������������
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART4_Init(int Baud)
{
	NVIC_InitTypeDef NVIC_InitStructure ;//�����жϽṹ��
	GPIO_InitTypeDef GPIO_InitStructure;//����IO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;//���崮�ڽṹ��
	DMA_InitTypeDef DMA_InitStructure;//����DMA�ṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);//�򿪴��ڶ�Ӧ������ʱ��
	//**********************���� ���� DMA ���ã�DMA1_Stream6��**************************
	// 0 ����DMAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	// 1 DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// 2 DMAͨ������
	DMA_DeInit(DMA1_Stream4);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_data_u4;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//dma���䷽��
	DMA_InitStructure.DMA_BufferSize = U4_DATA_LEN;//����DMA�ڴ���ʱ�������ĳ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//����DMA�Ĵ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//����DMA�����ȼ���
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;  	//ָ����FIFO��ֵˮƽ
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; //ָ����Burstת�������ڴ洫��
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //ָ����Burstת��������Χת�� */
	// 3 ����DMA1��ͨ��
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);
	// 4 ʹ���ж�
	DMA_ITConfig(DMA1_Stream4,DMA_IT_TC,ENABLE);
	/* 5.ʹ�ܴ��ڵ�DMA���ͽӿ� */
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);
	// 6 �ر�ͨ��
	DMA_Cmd(DMA1_Stream4,DISABLE);//�ȹر�
	//**********************���� ���� DMA ����**************************
	// 0 ����DMAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//DMAͨ������
	// 2 DMAͨ������
	DMA_DeInit(DMA1_Stream2);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rec_data_u4;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//dma���䷽��
	DMA_InitStructure.DMA_BufferSize = U4_DATA_LEN;//����DMA�ڴ���ʱ�������ĳ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//����DMA�Ĵ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//����DMA�����ȼ���
	// 3 ����DMA1��ͨ��
	DMA_Init(DMA1_Stream2, &DMA_InitStructure);
	// 4 ʹ��ͨ��
	DMA_Cmd(DMA1_Stream2,ENABLE);
	/* 5.ʹ�ܴ��ڵ�DMA���� */
	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
	//��ʼ�����ڲ���
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate = Baud;
	//��ʼ������
	USART_Init(UART4,&USART_InitStructure);
	//�����ж�
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;               //ͨ������Ϊ�����ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //�ж�ռ�ȵȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //�ж���Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�
	NVIC_Init(&NVIC_InitStructure);
	//����DMA��ʽ����
	USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
	//����DMA��ʽ����
	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
	//�ж�����
	USART_ITConfig(UART4,USART_IT_TC,DISABLE);
	USART_ITConfig(UART4,USART_IT_RXNE,DISABLE);
	USART_ITConfig(UART4,USART_IT_TXE,DISABLE);
	USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);
	//��������
	USART_Cmd(UART4, ENABLE);
	//����IO��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //�ܽ�ģʽ:�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //����:����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO���ٶ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  //�ܽ�ָ��
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//�ܽ�ģʽ:�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    //�ܽ�ָ��
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //��ʼ��
//	send_com(0x45);

}

/*
********************************************************************************************************************
*                  void UART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)
*
*Description : ����4���ͺ��� 
*Arguments   : BufferSRC:�������ݴ�ŵ�ַ��BufferSize:���������ֽ���
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void UART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)//UASRT DMA��������
{
	DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
	DMA1_Stream4->NDTR = BufferSize;    //����BUFFER��С
	DMA1_Stream4->M0AR = (uint32_t)BufferSRC;   //���õ�ַ
	DMA1_Stream4->CR |= DMA_SxCR_EN;	//��DMA,��ʼ����
}

/*
********************************************************************************************************************
*                  void  UART4_IRQHandler(void)
*
*Description : ����4���պ��� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
u8 Receive_ok=0;
extern int num_site;;
int num_4[4];
int16_t Res_4;
void UART4_IRQHandler(void)
{
	static uint8_t Uart4_Rec_Len = 0;
	int t;
	static uint8_t i=0;
	uint8_t sum=0;
	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //�����ж�
	{
		Res_4= USART_ReceiveData(UART4);//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ��
		Uart4_Rec_Len = U4_DATA_LEN - DMA1_Stream2->NDTR;	//����ӱ�֡���ݳ���
		uint16_t distance=0;
   
		if(num_site==0)
		{
		    num_4[0]=Res_4;	
				OLED_ShowNum(35,20,num_4[0],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		}
				if(num_site==1)
		{
		    num_4[1]=Res_4;	
				OLED_ShowNum(35,30,num_4[1],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		}
			if(num_site==2)
		{
		   num_4[2]=Res_4;	
				OLED_ShowNum(35,40,num_4[2],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		}
		if(num_site==3)
		{
		    num_4[3]=Res_4;	
				OLED_ShowNum(35,50,num_4[3],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		} 
		
		
		
		
		
		
		//***********֡���ݴ�����************//
		DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
		DMA1_S2_Reset();                                       //�ָ�DMAָ�룬�ȴ���һ�εĽ���
    }
	else if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_TC);
		DMA1_Stream2->CR &= (uint32_t)(~DMA_SxCR_EN);   //�ر�DMA,�������
	}
}






/***************************************************����*////////////////////////////////////////////////
//u8 Receive_ok=0;

//void UART4_IRQHandler(void)
//{
//	static uint8_t Uart4_Rec_Len = 0;
//	int t;
//	static uint8_t i=0;
//	uint8_t sum=0;
//	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //�����ж�
//	{
//		t= USART_ReceiveData(UART4);//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ��
//		Uart4_Rec_Len = U4_DATA_LEN - DMA1_Stream2->NDTR;	//����ӱ�֡���ݳ���
//		uint16_t distance=0;
//    if(rec_data_u4[0]==0x59)
//		{
//			LED1=!LED1;
//			if(rec_data_u4[1]==0x59)
//			{
//				for(i=0;i<Uart4_Rec_Len-1;i++)	
//				{	
//					sum+=rec_data_u4[i];
//				}
//				distance=(rec_data_u4[3]<<8)|rec_data_u4[2];
//		   Receive_ok=0;//����������ϱ�־
//			OLED_Show3FNum(0,15,distance,4,2,12);			
//		  OLED_Refresh_Gram();
//			 
//			}
//		}
//		//***********֡���ݴ�����************//
//		DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
//		DMA1_S2_Reset();                                       //�ָ�DMAָ�룬�ȴ���һ�εĽ���
//    }
//	else if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
//	{
//		USART_ClearITPendingBit(UART4, USART_IT_TC);
//		DMA1_Stream2->CR &= (uint32_t)(~DMA_SxCR_EN);   //�ر�DMA,�������
//	}
//}





/***********************************************************************ţ�Ƽ���*////////////////////////////////////////////////////////////////////////////////
/***********************************************************************������9600*//////////////////////////////////////////////////////////////////////////////
u8 Num = 0;              //�������ݵĵ�ǰλ��
int a222=0;
	void Read_LaserDis(unsigned char ID, unsigned int *Data)       
{	
	unsigned char y=0;
	unsigned int Receive_data [3] = { 0 };       //���ݻ�����

	Num = 0;
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, 0x57);		
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, ID);																  //IDģ����

  while(1)
  {
		if(rec_data_u4[0] != 0x75) { Num = 0; }  //�ж�֡ͷ0x75,�������½���
		if(Num == 8)
		{
			Num = 0;
			if(rec_data_u4[7] == 0x07)  //�ж�֡β0x07,���߲���ֵ
			{
				Receive_data[0] = rec_data_u4[1];
				Receive_data[0] <<= 8;
				Receive_data[0] |= rec_data_u4[2];        
				*Data = Receive_data[0];          //����
				
				Receive_data[1] = rec_data_u4[3];
				Receive_data[1] <<= 8;
				Receive_data[1] |= rec_data_u4[4];
				*(Data+1) = Receive_data[1];          //��������
				
				Receive_data[2] = rec_data_u4[5];
				Receive_data[2] <<= 8;
				Receive_data[2] |= rec_data_u4[6];
				*(Data+2) = Receive_data[2];         //������ǿ        
				
				break;
			}        
			break;
		}
//    else
//    {
//      delay_ms(1);y++;
//      if(y==10) { Num = 0;break; }
//    }
  }
///////////////////////////��ȡ���롢����������������ǿ��ֵ///////////////////////////////
}
//extern u16 openmv3[9];
//void UART4_IRQHandler(void)
//{
//	static uint8_t Uart4_Rec_Len = 0;
//	int t;
//	static uint8_t i=0;
//	uint8_t sum=0;
//	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //�����ж�
//	{
//		t= USART_ReceiveData(UART4);//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ��
//		Uart4_Rec_Len = U4_DATA_LEN - DMA1_Stream2->NDTR;	//����ӱ�֡���ݳ���
//		uint16_t distance=0;
//		   
//// 				a222=rec_data_u4[1]*256+rec_data_u4[2];
////        OLED_ShowNum(50,42,a222,4,12);	
////    		OLED_Refresh_Gram();

//		  openmv3[1]=rec_data_u4[1];
//      openmv3[2]=rec_data_u4[2];
//      openmv3[3]=rec_data_u4[3];
//      openmv3[4]=rec_data_u4[4];
//			openmv3[5]=rec_data_u4[5];
//      openmv3[6]=rec_data_u4[6];
//			openmv3[7]=rec_data_u4[7];
//		  a222=openmv3[1]*256+openmv3[2];
//		//***********֡���ݴ�����************//
//		DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
//		DMA1_S2_Reset();                                       //�ָ�DMAָ�룬�ȴ���һ�εĽ���
//    }
//	else if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
//	{
//		USART_ClearITPendingBit(UART4, USART_IT_TC);
//		DMA1_Stream2->CR &= (uint32_t)(~DMA_SxCR_EN);   //�ر�DMA,�������
//	}
//}


void Set_LaserDis(unsigned char ID, unsigned char Fun,unsigned char Par)	       
{	
 ///////////////////////////���ù��ܲ���///////////////////////////////	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, 0x4C);																//������ʼ�ź�
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, ID);																  //IDģ����
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, Fun);																//������
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, Par);																//����
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
}
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

/*
********************************************************************************************************************
*                  void DMA1_Stream4_IRQHandler(void)
*
*Description : ����4�����жϺ��� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void USART4_send_byte(uint8_t byte)
{
	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);//�ȴ��������
	UART4->DR=byte;	
}

//���Ͷ��ֽ�����
void USART4_Send_bytes(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		USART4_send_byte(Buffer[i++]);
	}
}
//���Ͷ��ֽ�����+У���
void USART4_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//�ۼ�Length-1ǰ������
		USART4_send_byte(Buffer[i++]);
	}
}

void send_com(u8 data)
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=data;//�����ֽ�
	USART4_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}


void DMA1_Stream4_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream4,DMA_IT_TCIF4) != RESET)
    {
        DMA_ClearFlag(DMA1_Stream4,DMA_IT_TCIF4);	//�����־λ
        DMA_Cmd(DMA1_Stream4,DISABLE);				//�ر�DMA
        USART_ITConfig(UART4,USART_IT_TC,ENABLE);	//�򿪷�������ж�,ȷ�����һ���ֽڷ��ͳɹ�
    }
}

/*
********************************************************************************************************************
*                  void DMA1_S2_Reset(void)
*
*Description : ����4�������� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void DMA1_S2_Reset(void)//DMA1_Stream2 ��������
{ 
	DMA_ClearFlag(DMA1_Stream2,DMA_IT_TCIF2|DMA_FLAG_HTIF2|DMA_FLAG_TEIF2|DMA_FLAG_DMEIF2|DMA_FLAG_FEIF2);  
	DMA_Cmd(DMA1_Stream2,DISABLE);		//�ر�USART2 TX DMA1 ��ָʾ��ͨ��
	DMA1_Stream2->NDTR = U4_DATA_LEN;                   
	DMA_Cmd(DMA1_Stream2,ENABLE);		//ʹ��USART2 TX DMA1 ��ָʾ��ͨ��
}



