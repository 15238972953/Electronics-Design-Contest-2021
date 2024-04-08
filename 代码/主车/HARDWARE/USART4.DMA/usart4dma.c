/*
******************************************************************************
*Filename      :uart4_dma.c
*Programmer(s) :¹úÈüÍº»÷¶Ó
*Description   :2019¹úÈü
******************************************************************************
*/

#include "usart4dma.h"
#include "oled.h"
#include "led.h"
#include "delay.h"
/************************************************** MINI BalanceÉÏÎ»»ú *//////////////////////////////////////////////////////////////

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
extern unsigned int Temp_Data[3] ;       //Êý¾Ý»º´æÇø
unsigned char DataScope_OutPut_Buffer[42] = {0};	   //´®¿Ú·¢ËÍ»º³åÇø
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //µÃµ½floatµÄµØÖ·
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}

void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
	if ( (Channel > 10) || (Channel == 0) ) return;  //Í¨µÀ¸öÊý´óÓÚ10»òµÈÓÚ0£¬Ö±½ÓÌø³ö£¬²»Ö´ÐÐº¯Êý
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


//º¯ÊýËµÃ÷£ºÉú³É DataScopeV1.0 ÄÜÕýÈ·Ê¶±ðµÄÖ¡¸ñÊ½
//Channel_Number£¬ÐèÒª·¢ËÍµÄÍ¨µÀ¸öÊý
//·µ»Ø·¢ËÍ»º³åÇøÊý¾Ý¸öÊý
//·µ»Ø0±íÊ¾Ö¡¸ñÊ½Éú³ÉÊ§°Ü 
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //Í¨µÀ¸öÊý´óÓÚ10»òµÈÓÚ0£¬Ö±½ÓÌø³ö£¬²»Ö´ÐÐº¯Êý
  else
  {	
	 DataScope_OutPut_Buffer[0] = '$';  //Ö¡Í·
		
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

/************************************************** MINI BalanceÉÏÎ»»ú *//////////////////////////////////////////////////////////////




u8 rec_data_u4[U4_DATA_LEN];      // ½ÓÊÕÊý¾ÝµØÖ·
u8 send_data_u4[U4_DATA_LEN];     // ·¢ËÍÊý¾ÝµØÖ·

/*
********************************************************************************************************************
*                  void  UART4_Init(void)
*
*Description : ´®¿Ú4µÄ³õÊ¼»¯ 
							 UART4_RX---PC11
							 UART4_TX---PC10
*Arguments   : Baud£º²¨ÌØÂÊÅäÖÃ
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART4_Init(int Baud)
{
	NVIC_InitTypeDef NVIC_InitStructure ;//¶¨ÒåÖÐ¶Ï½á¹¹Ìå
	GPIO_InitTypeDef GPIO_InitStructure;//¶¨ÒåIO³õÊ¼»¯½á¹¹Ìå
	USART_InitTypeDef USART_InitStructure;//¶¨Òå´®¿Ú½á¹¹Ìå
	DMA_InitTypeDef DMA_InitStructure;//¶¨ÒåDMA½á¹¹Ìå

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);//´ò¿ª´®¿Ú¶ÔÓ¦µÄÍâÉèÊ±ÖÓ
	//**********************´®¿Ú ·¢ËÍ DMA ÉèÖÃ£¨DMA1_Stream6£©**************************
	// 0 Æô¶¯DMAÊ±ÖÓ
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	// 1 DMA·¢ËÍÖÐ¶ÏÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// 2 DMAÍ¨µÀÅäÖÃ
	DMA_DeInit(DMA1_Stream4);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);//ÍâÉèµØÖ·
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_data_u4;//ÄÚ´æµØÖ·
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//dma´«Êä·½Ïò
	DMA_InitStructure.DMA_BufferSize = U4_DATA_LEN;//ÉèÖÃDMAÔÚ´«ÊäÊ±»º³åÇøµÄ³¤¶È
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//ÉèÖÃDMAµÄÍâÉèµÝÔöÄ£Ê½£¬Ò»¸öÍâÉè
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//ÉèÖÃDMAµÄÄÚ´æµÝÔöÄ£Ê½

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//ÍâÉèÊý¾Ý×Ö³¤
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//ÄÚ´æÊý¾Ý×Ö³¤
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//ÉèÖÃDMAµÄ´«ÊäÄ£Ê½
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//ÉèÖÃDMAµÄÓÅÏÈ¼¶±ð
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    //Ö¸¶¨Èç¹ûFIFOÄ£Ê½»òÖ±½ÓÄ£Ê½½«ÓÃÓÚÖ¸¶¨µÄÁ÷ £º ²»Ê¹ÄÜFIFOÄ£Ê½
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;  	//Ö¸¶¨ÁËFIFOãÐÖµË®Æ½
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; //Ö¸¶¨µÄBurst×ªÒÆÅäÖÃÄÚ´æ´«Êä
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //Ö¸¶¨µÄBurst×ªÒÆÅäÖÃÍâÎ§×ªÒÆ */
	// 3 ÅäÖÃDMA1µÄÍ¨µÀ
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);
	// 4 Ê¹ÄÜÖÐ¶Ï
	DMA_ITConfig(DMA1_Stream4,DMA_IT_TC,ENABLE);
	/* 5.Ê¹ÄÜ´®¿ÚµÄDMA·¢ËÍ½Ó¿Ú */
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);
	// 6 ¹Ø±ÕÍ¨µÀ
	DMA_Cmd(DMA1_Stream4,DISABLE);//ÏÈ¹Ø±Õ
	//**********************´®¿Ú ½ÓÊÜ DMA ÉèÖÃ**************************
	// 0 Æô¶¯DMAÊ±ÖÓ
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//DMAÍ¨µÀÅäÖÃ
	// 2 DMAÍ¨µÀÅäÖÃ
	DMA_DeInit(DMA1_Stream2);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);//ÍâÉèµØÖ·
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rec_data_u4;//ÄÚ´æµØÖ·
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//dma´«Êä·½Ïò
	DMA_InitStructure.DMA_BufferSize = U4_DATA_LEN;//ÉèÖÃDMAÔÚ´«ÊäÊ±»º³åÇøµÄ³¤¶È
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//ÉèÖÃDMAµÄÍâÉèµÝÔöÄ£Ê½£¬Ò»¸öÍâÉè
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//ÉèÖÃDMAµÄÄÚ´æµÝÔöÄ£Ê½
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//ÍâÉèÊý¾Ý×Ö³¤
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//ÄÚ´æÊý¾Ý×Ö³¤
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ÉèÖÃDMAµÄ´«ÊäÄ£Ê½
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//ÉèÖÃDMAµÄÓÅÏÈ¼¶±ð
	// 3 ÅäÖÃDMA1µÄÍ¨µÀ
	DMA_Init(DMA1_Stream2, &DMA_InitStructure);
	// 4 Ê¹ÄÜÍ¨µÀ
	DMA_Cmd(DMA1_Stream2,ENABLE);
	/* 5.Ê¹ÄÜ´®¿ÚµÄDMA½ÓÊÕ */
	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
	//³õÊ¼»¯´®¿Ú²ÎÊý
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate = Baud;
	//³õÊ¼»¯´®¿Ú
	USART_Init(UART4,&USART_InitStructure);
	//ÅäÖÃÖÐ¶Ï
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;               //Í¨µÀÉèÖÃÎª´®¿ÚÖÐ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //ÖÐ¶ÏÕ¼ÏÈµÈ¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //ÖÐ¶ÏÏìÓ¦ÓÅÏÈ¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //´ò¿ªÖÐ¶Ï
	NVIC_Init(&NVIC_InitStructure);
	//²ÉÓÃDMA·½Ê½·¢ËÍ
	USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
	//²ÉÓÃDMA·½Ê½½ÓÊÕ
	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
	//ÖÐ¶ÏÅäÖÃ
	USART_ITConfig(UART4,USART_IT_TC,DISABLE);
	USART_ITConfig(UART4,USART_IT_RXNE,DISABLE);
	USART_ITConfig(UART4,USART_IT_TXE,DISABLE);
	USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);
	//Æô¶¯´®¿Ú
	USART_Cmd(UART4, ENABLE);
	//ÉèÖÃIO¿ÚÊ±ÖÓ
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //¹Ü½ÅÄ£Ê½:Êä³ö¿Ú
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //ÀàÐÍ:ÍÆÍìÄ£Ê½
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //ÉÏÀ­ÏÂÀ­ÉèÖÃ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO¿ÚËÙ¶È
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  //¹Ü½ÅÖ¸¶¨
	GPIO_Init(GPIOC, &GPIO_InitStructure);//³õÊ¼»¯

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//¹Ü½ÅÄ£Ê½:ÊäÈë¿Ú
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //ÉÏÀ­ÏÂÀ­ÉèÖÃ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    //¹Ü½ÅÖ¸¶¨
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //³õÊ¼»¯
//	send_com(0x45);

}

/*
********************************************************************************************************************
*                  void UART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)
*
*Description : ´®¿Ú4·¢ËÍº¯Êý 
*Arguments   : BufferSRC:·¢ËÍÊý¾Ý´æ·ÅµØÖ·£»BufferSize:·¢ËÍÊý¾Ý×Ö½ÚÊý
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void UART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)//UASRT DMA·¢ËÍÉèÖÃ
{
	DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
	DMA1_Stream4->NDTR = BufferSize;    //ÅäÖÃBUFFER´óÐ¡
	DMA1_Stream4->M0AR = (uint32_t)BufferSRC;   //ÅäÖÃµØÖ·
	DMA1_Stream4->CR |= DMA_SxCR_EN;	//´ò¿ªDMA,¿ªÊ¼·¢ËÍ
}

/*
********************************************************************************************************************
*                  void  UART4_IRQHandler(void)
*
*Description : ´®¿Ú4½ÓÊÕº¯Êý 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
u8 Receive_ok=0;
extern int num_site;;
int num_4[5];
int16_t Res_4;
void UART4_IRQHandler(void)
{
	static uint8_t Uart4_Rec_Len = 0;
	int t;
	static uint8_t i=0;
	uint8_t sum=0;
	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //½ÓÊÕÖÐ¶Ï
	{
		Res_4= USART_ReceiveData(UART4);//¶ÁÈ¡Êý¾Ý ×¢Òâ£ºÕâ¾ä±ØÐëÒª£¬·ñÔò²»ÄÜ¹»Çå³ýÖÐ¶Ï±êÖ¾Î»¡£
		Uart4_Rec_Len = U4_DATA_LEN - DMA1_Stream2->NDTR;	//Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶È
		uint16_t distance=0;
   
		if(num_site==0)
		{
		    num_4[0]=Res_4;	
				OLED_ShowNum(35,20,num_4[0],3,12);
    OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
		}
				if(num_site==1)
		{
		    num_4[1]=Res_4;	
				OLED_ShowNum(35,30,num_4[1],3,12);
    OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
		}
			if(num_site==2)
		{
		   num_4[2]=Res_4;	
				OLED_ShowNum(35,40,num_4[2],3,12);
    OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
		}
		if(num_site==3)
		{
		    num_4[3]=Res_4;	
				OLED_ShowNum(35,50,num_4[3],3,12);
    OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
		} 
		
		
		
		//***********Ö¡Êý¾Ý´¦Àíº¯Êý************//
		DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
		DMA1_S2_Reset();                                       //»Ö¸´DMAÖ¸Õë£¬µÈ´ýÏÂÒ»´ÎµÄ½ÓÊÕ
    }
	else if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_TC);
		DMA1_Stream2->CR &= (uint32_t)(~DMA_SxCR_EN);   //¹Ø±ÕDMA,·¢ËÍÍê³É
	}
}






/***************************************************±±ÐÑ*////////////////////////////////////////////////
//u8 Receive_ok=0;

//void UART4_IRQHandler(void)
//{
//	static uint8_t Uart4_Rec_Len = 0;
//	int t;
//	static uint8_t i=0;
//	uint8_t sum=0;
//	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //½ÓÊÕÖÐ¶Ï
//	{
//		t= USART_ReceiveData(UART4);//¶ÁÈ¡Êý¾Ý ×¢Òâ£ºÕâ¾ä±ØÐëÒª£¬·ñÔò²»ÄÜ¹»Çå³ýÖÐ¶Ï±êÖ¾Î»¡£
//		Uart4_Rec_Len = U4_DATA_LEN - DMA1_Stream2->NDTR;	//Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶È
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
//		   Receive_ok=0;//´¦ÀíÊý¾ÝÍê±Ï±êÖ¾
//			OLED_Show3FNum(0,15,distance,4,2,12);			
//		  OLED_Refresh_Gram();
//			 
//			}
//		}
//		//***********Ö¡Êý¾Ý´¦Àíº¯Êý************//
//		DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
//		DMA1_S2_Reset();                                       //»Ö¸´DMAÖ¸Õë£¬µÈ´ýÏÂÒ»´ÎµÄ½ÓÊÕ
//    }
//	else if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
//	{
//		USART_ClearITPendingBit(UART4, USART_IT_TC);
//		DMA1_Stream2->CR &= (uint32_t)(~DMA_SxCR_EN);   //¹Ø±ÕDMA,·¢ËÍÍê³É
//	}
//}





/***********************************************************************Å£±Æ¼¤¹â*////////////////////////////////////////////////////////////////////////////////
/***********************************************************************²¨ÌØÂÊ9600*//////////////////////////////////////////////////////////////////////////////
u8 Num = 0;              //½ÓÊÕÊý¾ÝµÄµ±Ç°Î»ÖÃ
int a222=0;
	void Read_LaserDis(unsigned char ID, unsigned int *Data)       
{	
	unsigned char y=0;
	unsigned int Receive_data [3] = { 0 };       //Êý¾Ý»º´æÇø

	Num = 0;
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, 0x57);		
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, ID);																  //IDÄ£¿é±àºÅ

  while(1)
  {
		if(rec_data_u4[0] != 0x75) { Num = 0; }  //ÅÐ¶ÏÖ¡Í·0x75,·ñÕßÖØÐÂ½ÓÊÕ
		if(Num == 8)
		{
			Num = 0;
			if(rec_data_u4[7] == 0x07)  //ÅÐ¶ÏÖ¡Î²0x07,·ñÕß²»¸³Öµ
			{
				Receive_data[0] = rec_data_u4[1];
				Receive_data[0] <<= 8;
				Receive_data[0] |= rec_data_u4[2];        
				*Data = Receive_data[0];          //¾àÀë
				
				Receive_data[1] = rec_data_u4[3];
				Receive_data[1] <<= 8;
				Receive_data[1] |= rec_data_u4[4];
				*(Data+1) = Receive_data[1];          //»·¾³ÖÊÁ¿
				
				Receive_data[2] = rec_data_u4[5];
				Receive_data[2] <<= 8;
				Receive_data[2] |= rec_data_u4[6];
				*(Data+2) = Receive_data[2];         //»·¾³¹âÇ¿        
				
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
///////////////////////////¶ÁÈ¡¾àÀë¡¢»·¾³ÖÊÁ¿¡¢»·¾³¹âÇ¿ÊýÖµ///////////////////////////////
}
//extern u16 openmv3[9];
//void UART4_IRQHandler(void)
//{
//	static uint8_t Uart4_Rec_Len = 0;
//	int t;
//	static uint8_t i=0;
//	uint8_t sum=0;
//	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //½ÓÊÕÖÐ¶Ï
//	{
//		t= USART_ReceiveData(UART4);//¶ÁÈ¡Êý¾Ý ×¢Òâ£ºÕâ¾ä±ØÐëÒª£¬·ñÔò²»ÄÜ¹»Çå³ýÖÐ¶Ï±êÖ¾Î»¡£
//		Uart4_Rec_Len = U4_DATA_LEN - DMA1_Stream2->NDTR;	//Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶È
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
//		//***********Ö¡Êý¾Ý´¦Àíº¯Êý************//
//		DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
//		DMA1_S2_Reset();                                       //»Ö¸´DMAÖ¸Õë£¬µÈ´ýÏÂÒ»´ÎµÄ½ÓÊÕ
//    }
//	else if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
//	{
//		USART_ClearITPendingBit(UART4, USART_IT_TC);
//		DMA1_Stream2->CR &= (uint32_t)(~DMA_SxCR_EN);   //¹Ø±ÕDMA,·¢ËÍÍê³É
//	}
//}


void Set_LaserDis(unsigned char ID, unsigned char Fun,unsigned char Par)	       
{	
 ///////////////////////////ÉèÖÃ¹¦ÄÜ²ÎÊý///////////////////////////////	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, 0x4C);																//ÃüÁîÆðÊ¼ÐÅºÅ
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, ID);																  //IDÄ£¿é±àºÅ
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, Fun);																//¹¦ÄÜÏî
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	USART_SendData(UART4, Par);																//²ÎÊý
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
}
/////////////////////////////ÉèÖÃ¹¦ÄÜ²ÎÊý///////////////////////////////		
//}
//extern u16 openmv3[9];
//void USART3_IRQHandler(void)
//{
//	static uint8_t Uart3_Rec_Len = 0;
//   u8 Res;
//	
//	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //½ÓÊÕÖÐ¶Ï
//	{
//		 Res= USART_ReceiveData(USART3);//¶ÁÈ¡Êý¾Ý ×¢Òâ£ºÕâ¾ä±ØÐëÒª£¬·ñÔò²»ÄÜ¹»Çå³ýÖÐ¶Ï±êÖ¾Î»¡	
//		 Uart3_Rec_Len = U3_DATA_LEN - DMA1_Stream3->NDTR;	//Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶
//	   GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_3);//GPIOF9,F10ÉèÖÃ¸ß£¬µÆÃð
//     
//   		openmv3[1]=rec_data_u3[1];
//      openmv3[2]=rec_data_u3[2];
//      openmv3[3]=rec_data_u3[3];
//      openmv3[4]=rec_data_u3[4];
//			openmv3[5]=rec_data_u3[5];
//      openmv3[6]=rec_data_u3[6];
//			openmv3[7]=rec_data_u3[7];

//     USART_ClearITPendingBit(USART3, USART_IT_IDLE);         //Çå³ýÖÐ¶Ï±êÖ¾
//		 DMA1_S1_Reset();                                       //»Ö¸´DMAÖ¸Õë£¬µÈ´ýÏÂÒ»´ÎµÄ½ÓÊÕ
//    }
//	else if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	{
//	
//		USART_ClearITPendingBit(USART3, USART_IT_TC);
//		DMA1_Stream3->CR &= (uint32_t)(~DMA_SxCR_EN);   //¹Ø±ÕDMA,·¢ËÍÍê³É

//	}
//}

/*
********************************************************************************************************************
*                  void DMA1_Stream4_IRQHandler(void)
*
*Description : ´®¿Ú4·¢ËÍÖÐ¶Ïº¯Êý 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void USART4_send_byte(uint8_t byte)
{
	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);//µÈ´ý·¢ËÍÍê³É
	UART4->DR=byte;	
}

//·¢ËÍ¶à×Ö½ÚÊý¾Ý
void USART4_Send_bytes(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		USART4_send_byte(Buffer[i++]);
	}
}
//·¢ËÍ¶à×Ö½ÚÊý¾Ý+Ð£ÑéºÍ
void USART4_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//ÀÛ¼ÓLength-1Ç°µÄÊý¾Ý
		USART4_send_byte(Buffer[i++]);
	}
}

void send_com(u8 data)
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=data;//¹¦ÄÜ×Ö½Ú
	USART4_Send(bytes,3);//·¢ËÍÖ¡Í·¡¢¹¦ÄÜ×Ö½Ú¡¢Ð£ÑéºÍ
}


void DMA1_Stream4_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream4,DMA_IT_TCIF4) != RESET)
    {
        DMA_ClearFlag(DMA1_Stream4,DMA_IT_TCIF4);	//Çå³ý±êÖ¾Î»
        DMA_Cmd(DMA1_Stream4,DISABLE);				//¹Ø±ÕDMA
        USART_ITConfig(UART4,USART_IT_TC,ENABLE);	//´ò¿ª·¢ËÍÍê³ÉÖÐ¶Ï,È·±£×îºóÒ»¸ö×Ö½Ú·¢ËÍ³É¹¦
    }
}

/*
********************************************************************************************************************
*                  void DMA1_S2_Reset(void)
*
*Description : ´®¿Ú4½ÓÊÕÖØÖÃ 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void DMA1_S2_Reset(void)//DMA1_Stream2 ½ÓÊÕÖØÖÃ
{ 
	DMA_ClearFlag(DMA1_Stream2,DMA_IT_TCIF2|DMA_FLAG_HTIF2|DMA_FLAG_TEIF2|DMA_FLAG_DMEIF2|DMA_FLAG_FEIF2);  
	DMA_Cmd(DMA1_Stream2,DISABLE);		//¹Ø±ÕUSART2 TX DMA1 ËùÖ¸Ê¾µÄÍ¨µÀ
	DMA1_Stream2->NDTR = U4_DATA_LEN;                   
	DMA_Cmd(DMA1_Stream2,ENABLE);		//Ê¹ÄÜUSART2 TX DMA1 ËùÖ¸Ê¾µÄÍ¨µÀ
}



