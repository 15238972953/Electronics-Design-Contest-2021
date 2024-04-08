/*
******************************************************************************************************************
*Filename      :usart2_dma.c
*Programmer(s) :chu
*Description   :Design for usart2_dma

							 USART2_RX---PD6
							 USART2_TX---PD5
******************************************************************************************************************
*/
#include "usart2dma.h"
#include "oled.h"
#include "delay.h"
#include "string.h"
u8 rec_data_u2[U2_DATA_LEN];   // ��������
u8 send_data_u2[42];  // ��������


/************************************************************************************����������*/////////////////////////////////////////////////////////////////////////////////////
//		OLED_ShowNum(20,2,openmv2[1],4,12);
//		OLED_ShowNum(20,12,openmv2[2],4,12);
//		OLED_ShowNum(20,22,openmv2[3],4,12);
//		OLED_ShowNum(20,32,openmv2[4],4,12);
//		OLED_ShowNum(20,42,openmv2[2]*256+openmv2[1],4,12);
//		OLED_ShowNum(50,2,openmv2[5],4,12);
//		OLED_ShowNum(50,12,openmv2[6],4,12);
//		OLED_ShowNum(50,22,openmv2[7],4,12);
//		OLED_ShowNum(50,32,openmv2[8],4,12);
//		OLED_ShowNum(50,42,openmv2[6]*256+openmv2[5],4,12);	
//		OLED_Refresh_Gram();
/************************************************************************************����������*/////////////////////////////////////////////////////////////////////////////////////

/*
********************************************************************************************************************
*                  void  USART2_Init(void)
*
*Description : ����2�ĳ�ʼ�� 
							 USART2_RX---PD6
							 USART2_TX---PD5
*Arguments   : Baud������������
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART2_Init(int Baud)
{
	NVIC_InitTypeDef NVIC_InitStructure ;//�����жϽṹ��
 	GPIO_InitTypeDef GPIO_InitStructure;//����IO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;//���崮�ڽṹ��
	DMA_InitTypeDef DMA_InitStructure;//����DMA�ṹ��

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//�򿪴��ڶ�Ӧ������ʱ��

	//**********************���� ���� DMA ���ã�DMA1_Stream6��**************************
	// 0 ����DMAʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	// 1 DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// 2 DMAͨ������
	DMA_DeInit(DMA1_Stream6);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_data_u2;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//dma���䷽��
	DMA_InitStructure.DMA_BufferSize = U2_DATA_LEN;//����DMA�ڴ���ʱ�������ĳ���
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
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);
	// 4 ʹ���ж�
	DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,ENABLE);


	/* 5.ʹ�ܴ��ڵ�DMA���ͽӿ� */
    USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	// 6 �ر�ͨ��
	DMA_Cmd(DMA1_Stream6,DISABLE);//�ȹر�

	//**********************���� ���� DMA ����**************************
	// 0 ����DMAʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//DMAͨ������
	
	// 2 DMAͨ������
	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rec_data_u2;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//dma���䷽��
	DMA_InitStructure.DMA_BufferSize = U2_DATA_LEN;//����DMA�ڴ���ʱ�������ĳ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//����DMA�Ĵ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//����DMA�����ȼ���

	// 3 ����DMA1��ͨ��
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);
	// 4 ʹ��ͨ��
	DMA_Cmd(DMA1_Stream5,ENABLE);

	/* 5.ʹ�ܴ��ڵ�DMA���� */
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);


    //��ʼ�����ڲ���
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_BaudRate = Baud;
	//��ʼ������
    USART_Init(USART2,&USART_InitStructure);


	//�����ж�
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //ͨ������Ϊ�����ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //�ж�ռ�ȵȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //�ж���Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�
    NVIC_Init(&NVIC_InitStructure);

	//����DMA��ʽ����
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
	//����DMA��ʽ����
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);

	//�ж�����
	USART_ITConfig(USART2,USART_IT_TC,DISABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART2,USART_IT_TXE,DISABLE);
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);


    //��������
    USART_Cmd(USART2, ENABLE);

    //����IO��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //�ܽ�ģʽ:�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //����:����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO���ٶ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  //�ܽ�ָ��
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��


  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//�ܽ�ģʽ:�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;    //�ܽ�ָ��
	GPIO_Init(GPIOD, &GPIO_InitStructure);      //��ʼ��
}

/*
********************************************************************************************************************
*                  void  USART2_IRQHandler(void)
*
*Description : ����2���ͺ��� 
*Arguments   : BufferSRC:�������ݴ�ŵ�ַ��BufferSize:���������ֽ���
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART2_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)//UASRT DMA��������
{
	DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);
	DMA1_Stream6->NDTR = BufferSize;    //����BUFFER��С
	DMA1_Stream6->M0AR = (uint32_t)BufferSRC;   //���õ�ַ
	DMA1_Stream6->CR |= DMA_SxCR_EN;	//��DMA,��ʼ����
}



/*
********************************************************************************************************************
*                  void  USART2_IRQHandler(void)
*
*Description : ����2���պ��� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
unsigned char ReceiveData;    //���ܴ洢����
extern u16 openmv2[9];
int16_t Res;
int16_t Res_2;
extern int num_site;
int num[4];
void USART2_IRQHandler(void)
{
	static uint8_t Uart2_Rec_Len = 0;
	static u8 bit_number=0;
	static u8 state = 0;
	char res[10];
	int t;
	u8 i;
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)  //�����ж�
	{
		Res_2= USART_ReceiveData(USART2);//��ȡ���� ע�⣺������Ҫ�������ܹ�����жϱ�־λ��
		USART_SendData(USART2,Res_2);
		Uart2_Rec_Len = U2_DATA_LEN - DMA1_Stream5->NDTR;	//����ӱ�֡���ݳ���
		if(num_site==0)
		{
		    num[0]=Res_2;	
				OLED_ShowNum(0,20,num[0],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		}
				if(num_site==1)
		{
		    num[1]=Res_2;	
				OLED_ShowNum(0,30,num[1],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		}
			if(num_site==2)
		{
		    num[2]=Res_2;	
				OLED_ShowNum(0,40,num[2],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		}
		if(num_site==3)
		{
		    num[3]=Res_2;	
				OLED_ShowNum(0,50,num[3],3,12);
    OLED_Refresh_Gram();//������ʾ��OLED	
		}
		
//      openmv2[1]=rec_data_u2[1];
//      openmv2[2]=rec_data_u2[2];
//      openmv2[3]=rec_data_u2[3];
//      openmv2[4]=rec_data_u2[4];
//			openmv2[5]=rec_data_u2[5];
//      openmv2[6]=rec_data_u2[6];
//			openmv2[7]=rec_data_u2[7];
//      openmv2[8]=rec_data_u2[8];

		USART_ClearITPendingBit(USART2, USART_IT_IDLE);         //����жϱ�־
		DMA1_S5_Reset();                                       //�ָ�DMAָ�룬�ȴ���һ�εĽ���
    }

	else if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TC);

		DMA1_Stream6->CR &= (uint32_t)(~DMA_SxCR_EN);   //�ر�DMA,�������
	}
}

/*
********************************************************************************************************************
*                  void DMA1_Stream6_IRQHandler(void)
*
*Description : ����2�����жϺ��� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void DMA1_Stream6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream6,DMA_IT_TCIF6) != RESET)
    {
        /* �����־λ */
        DMA_ClearFlag(DMA1_Stream6,DMA_IT_TCIF6);
        /* �ر�DMA */
        DMA_Cmd(DMA1_Stream6,DISABLE);
        /* �򿪷�������ж�,ȷ�����һ���ֽڷ��ͳɹ� */
        USART_ITConfig(USART2,USART_IT_TC,ENABLE);
    }
}

/*
********************************************************************************************************************
*                  void DMA1_S5_Reset(void)
*
*Description : ����2�������� 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void DMA1_S5_Reset(void)//DMA1_Stream6 ��������
{ 
	DMA_ClearFlag(DMA1_Stream5,DMA_IT_TCIF5|DMA_FLAG_HTIF5|DMA_FLAG_TEIF5|DMA_FLAG_DMEIF5|DMA_FLAG_FEIF5);  
	
	DMA_Cmd(DMA1_Stream5,DISABLE); //�ر�USART2 TX DMA1 ��ָʾ��ͨ��

 	//DMA_SetCurrDataCounter(DMA1_Channel5,Uart1_DMA_Len);//DMAͨ����DMA����Ĵ�С
	DMA1_Stream5->NDTR = U2_DATA_LEN;
 	//DMA_Cmd(DMA1_Channel5, ENABLE);                    
	DMA_Cmd(DMA1_Stream5,ENABLE); //ʹ��USART2 TX DMA1 ��ָʾ��ͨ��
	/* �����־λ */
   
}


void HMISendstart(void)
{
	 	delay_ms(200);
		HMISendb(0xff);
		delay_ms(200);
}
void HMISends(char *buf1)		  //�ַ������ͺ���
{
	 u8 i=0;
	 while(1)
	{
	    if(buf1[i]!=0)
	 	 {
			   USART_SendData(USART2,buf1[i]);  //����һ���ֽ�
			   while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
		   	 i++;
		 }
	    else 
	       return ;
	}
}
void HMISendb(u8 k)		         //�ֽڷ��ͺ���
{		 
	  u8 i;
	  for(i=0;i<3;i++)
	 {
	     if(k!=0)
	 	  {
			    USART_SendData(USART2,k);  //����һ���ֽ�
			    while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
		  }
	     else 
	        return ;
	 } 
} 

