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
u8 rec_data_u3[U3_DATA_LEN];   // ½ÓÊÕÊý¾Ý
u8 send_data_u3[U3_DATA_LEN]/*="{\"RGB_blocks\":\"find_R\"}"*/;

u8 angle_1,angle_2;
short angle_z;
float yaw_2;
/*
********************************************************************************************************************
*                  void  USART3_Init(void)
*
*Description : ´®¿Ú3µÄ³õÊ¼»¯ 
							 USART3_RX---PD9
							 USART3_TX---PD8
*Arguments   : Baud£º²¨ÌØÂÊÅäÖÃ
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
//void USART3_Init(int Baud)
//{
//	NVIC_InitTypeDef NVIC_InitStructure ;//¶¨ÒåÖÐ¶Ï½á¹¹Ìå
// 	GPIO_InitTypeDef GPIO_InitStructure;//¶¨ÒåIO³õÊ¼»¯½á¹¹Ìå
//	USART_InitTypeDef USART_InitStructure;//¶¨Òå´®¿Ú½á¹¹Ìå
//	DMA_InitTypeDef DMA_InitStructure;//¶¨ÒåDMA½á¹¹Ìå

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);//´ò¿ª´®¿Ú¶ÔÓ¦µÄÍâÉèÊ±ÖÓ

//	//**********************´®¿Ú ·¢ËÍ DMA ÉèÖÃ£¨DMA1_Stream6£©**************************
//	// 0 Æô¶¯DMAÊ±ÖÓ
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

//	// 1 DMA·¢ËÍÖÐ¶ÏÉèÖÃ
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	// 2 DMAÍ¨µÀÅäÖÃ
//	DMA_DeInit(DMA1_Stream3);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);//ÍâÉèµØÖ·
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_data_u3;//ÄÚ´æµØÖ·
//	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//dma´«Êä·½Ïò
//	DMA_InitStructure.DMA_BufferSize = U3_DATA_LEN;//ÉèÖÃDMAÔÚ´«ÊäÊ±»º³åÇøµÄ³¤¶È
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//ÉèÖÃDMAµÄÍâÉèµÝÔöÄ£Ê½£¬Ò»¸öÍâÉè
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//ÉèÖÃDMAµÄÄÚ´æµÝÔöÄ£Ê½

//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//ÍâÉèÊý¾Ý×Ö³¤
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//ÄÚ´æÊý¾Ý×Ö³¤
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//ÉèÖÃDMAµÄ´«ÊäÄ£Ê½
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//ÉèÖÃDMAµÄÓÅÏÈ¼¶±ð
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    //Ö¸¶¨Èç¹ûFIFOÄ£Ê½»òÖ±½ÓÄ£Ê½½«ÓÃÓÚÖ¸¶¨µÄÁ÷ £º ²»Ê¹ÄÜFIFOÄ£Ê½
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;  	//Ö¸¶¨ÁËFIFOãÐÖµË®Æ½
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; //Ö¸¶¨µÄBurst×ªÒÆÅäÖÃÄÚ´æ´«Êä
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //Ö¸¶¨µÄBurst×ªÒÆÅäÖÃÍâÎ§×ªÒÆ */

//	// 3 ÅäÖÃDMA1µÄÍ¨µÀ
//	DMA_Init(DMA1_Stream3, &DMA_InitStructure);
//	// 4 Ê¹ÄÜÖÐ¶Ï
//	DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,ENABLE);


//	/* 5.Ê¹ÄÜ´®¿ÚµÄDMA·¢ËÍ½Ó¿Ú */
//    USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
//	// 6 ¹Ø±ÕÍ¨µÀ
//	DMA_Cmd(DMA1_Stream3,DISABLE);//ÏÈ¹Ø±Õ

//	//**********************´®¿Ú ½ÓÊÜ DMA ÉèÖÃ**************************
//	// 0 Æô¶¯DMAÊ±ÖÓ
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//DMAÍ¨µÀÅäÖÃ
//	
//	// 2 DMAÍ¨µÀÅäÖÃ
//	DMA_DeInit(DMA1_Stream1);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);//ÍâÉèµØÖ·
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rec_data_u3;//ÄÚ´æµØÖ·
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//dma´«Êä·½Ïò
//	DMA_InitStructure.DMA_BufferSize = U3_DATA_LEN;//ÉèÖÃDMAÔÚ´«ÊäÊ±»º³åÇøµÄ³¤¶È
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//ÉèÖÃDMAµÄÍâÉèµÝÔöÄ£Ê½£¬Ò»¸öÍâÉè
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//ÉèÖÃDMAµÄÄÚ´æµÝÔöÄ£Ê½
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//ÍâÉèÊý¾Ý×Ö³¤
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//ÄÚ´æÊý¾Ý×Ö³¤
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ÉèÖÃDMAµÄ´«ÊäÄ£Ê½
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//ÉèÖÃDMAµÄÓÅÏÈ¼¶±ð

//	// 3 ÅäÖÃDMA1µÄÍ¨µÀ
//	DMA_Init(DMA1_Stream1, &DMA_InitStructure);
//	// 4 Ê¹ÄÜÍ¨µÀ
//	DMA_Cmd(DMA1_Stream1,ENABLE);

//	/* 5.Ê¹ÄÜ´®¿ÚµÄDMA½ÓÊÕ */
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);


//    //³õÊ¼»¯´®¿Ú²ÎÊý
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_InitStructure.USART_BaudRate = Baud;
//	//³õÊ¼»¯´®¿Ú
//    USART_Init(USART3,&USART_InitStructure);


//	//ÅäÖÃÖÐ¶Ï
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;               //Í¨µÀÉèÖÃÎª´®¿ÚÖÐ¶Ï
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //ÖÐ¶ÏÕ¼ÏÈµÈ¼¶
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //ÖÐ¶ÏÏìÓ¦ÓÅÏÈ¼¶
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //´ò¿ªÖÐ¶Ï
//    NVIC_Init(&NVIC_InitStructure);

//	//²ÉÓÃDMA·½Ê½·¢ËÍ
//	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
//	//²ÉÓÃDMA·½Ê½½ÓÊÕ
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);

//	//ÖÐ¶ÏÅäÖÃ
//	USART_ITConfig(USART3,USART_IT_TC,DISABLE);
//	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);
//	USART_ITConfig(USART3,USART_IT_TXE,DISABLE);
//	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);


//    //Æô¶¯´®¿Ú
//    USART_Cmd(USART3, ENABLE);

//    //ÉèÖÃIO¿ÚÊ±ÖÓ
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);

//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //¹Ü½ÅÄ£Ê½:Êä³ö¿Ú
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //ÀàÐÍ:ÍÆÍìÄ£Ê½
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //ÉÏÀ­ÏÂÀ­ÉèÖÃ
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO¿ÚËÙ¶È
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //¹Ü½ÅÖ¸¶¨
//	GPIO_Init(GPIOD, &GPIO_InitStructure);//³õÊ¼»¯


//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//¹Ü½ÅÄ£Ê½:ÊäÈë¿Ú
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //ÉÏÀ­ÏÂÀ­ÉèÖÃ
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    //¹Ü½ÅÖ¸¶¨
//	GPIO_Init(GPIOD, &GPIO_InitStructure);      //³õÊ¼»¯
//}
void USART3_Init(u32 bound){
 GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //Ê¹ÄÜGPIOBÊ±ÖÓ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//Ê¹ÄÜUSART3Ê±ÖÓ
 
	//´®¿Ú1¶ÔÓ¦Òý½Å¸´ÓÃÓ³Éä
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); //GPIOB10¸´ÓÃÎªUSART3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); //GPIOB11¸´ÓÃÎªUSART3
	
	//USART3¶Ë¿ÚÅäÖÃ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //GPIOB10ÓëGPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//ËÙ¶È50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //ÉÏÀ­
	GPIO_Init(GPIOD,&GPIO_InitStructure); //³õÊ¼»¯PB10£¬PB11

   //USART3 ³õÊ¼»¯ÉèÖÃ
	USART_InitStructure.USART_BaudRate = bound;//²¨ÌØÂÊÉèÖÃ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//×Ö³¤Îª8Î»Êý¾Ý¸ñÊ½
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//Ò»¸öÍ£Ö¹Î»
	USART_InitStructure.USART_Parity = USART_Parity_No;//ÎÞÆæÅ¼Ð£ÑéÎ»
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ÎÞÓ²¼þÊý¾ÝÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ÊÕ·¢Ä£Ê½
  USART_Init(USART3, &USART_InitStructure); //³õÊ¼»¯´®¿Ú3
		
		//Usart1 NVIC ÅäÖÃ
   NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//´®¿Ú3ÖÐ¶ÏÍ¨µÀ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//ÇÀÕ¼ÓÅÏÈ¼¶2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//×ÓÓÅÏÈ¼¶2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷
		
  USART_Cmd(USART3, ENABLE);  //Ê¹ÄÜ´®¿Ú3 
	
//	USART_ClearFlag(USART3, USART_FLAG_TC);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//¿ªÆôÏà¹ØÖÐ¶Ï	
	
}
/*
********************************************************************************************************************
*                  void  USART3_IRQHandler(void)
*
*Description : ´®¿Ú3·¢ËÍº¯Êý 
*Arguments   : BufferSRC:·¢ËÍÊý¾Ý´æ·ÅµØÖ·£»BufferSize:·¢ËÍÊý¾Ý×Ö½ÚÊý
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART3_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)//UASRT DMA·¢ËÍÉèÖÃ
{
	DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);
	DMA1_Stream3->NDTR = BufferSize;    //ÅäÖÃBUFFER´óÐ¡
	DMA1_Stream3->M0AR = (uint32_t)BufferSRC;   //ÅäÖÃµØÖ·
	DMA1_Stream3->CR |= DMA_SxCR_EN;	//´ò¿ªDMA,¿ªÊ¼·¢ËÍ
}



/*
********************************************************************************************************************
*                  void  USART3_IRQHandler(void)
*
*Description : ´®¿Ú3½ÓÊÕº¯Êý 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
//void USART3_IRQHandler(void)
//{
//	static uint8_t Uart3_Rec_Len = 0;
//	int t;
//	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //½ÓÊÕÖÐ¶Ï
//	{
//		t= USART_ReceiveData(USART3);//¶ÁÈ¡Êý¾Ý ×¢Òâ£ºÕâ¾ä±ØÐëÒª£¬·ñÔò²»ÄÜ¹»Çå³ýÖÐ¶Ï±êÖ¾Î»¡£
//		Uart3_Rec_Len = U3_DATA_LEN - DMA1_Stream3->NDTR;	//Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶È

//		//***********Ö¡Êý¾Ý´¦Àíº¯Êý************//
////if((rec_data_u3[0]==0X55)&&(rec_data_u3[1]==0X53))//
////		{
//		
// //   }
//		  angle_1=rec_data_u3[7];
//			angle_2=rec_data_u3[6];
//			angle_z=(angle_1<<8)|angle_2;
//			yaw_2=angle_z/32768.0f*180.0f;

//		//*************************************//
//		USART_ClearITPendingBit(USART3, USART_IT_IDLE);         //Çå³ýÖÐ¶Ï±êÖ¾
//		DMA1_S1_Reset();                                       //»Ö¸´DMAÖ¸Õë£¬µÈ´ýÏÂÒ»´ÎµÄ½ÓÊÕ
//		
//  }

//		
//	else if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	{
//		USART_ClearITPendingBit(USART3, USART_IT_TC);

//		DMA1_Stream3->CR &= (uint32_t)(~DMA_SxCR_EN);   //¹Ø±ÕDMA,·¢ËÍÍê³É
//	}
//	
//	
//}
extern u16 USART_RX_STA;

void USART3_IRQHandler(void)                	//´®¿Ú1ÖÐ¶Ï·þÎñ³ÌÐò
	{
	int16_t Res;
	static u8 state = 0;	
	static u8 bit_number=0;
  u8 i;	
	static u16 openmv[9];	//´æÈ¡Êý¾Ý
	

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶Ï
		{ USART_ClearFlag(USART3, USART_FLAG_TC); 
			USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		  Res=USART_ReceiveData(USART3);	//¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
			
			
//	LED1=!LED1;
//if(state==0&&Res==0x55) 
//	{	
//		state=1;
//		openmv[bit_number++]=Res;
//	}

//	else if(state==1&&Res==0x53)
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
//		state=7;
//	}
//		else if(state==7)
//	{ 
//		  openmv[7]=Res;
//      angle_1=openmv[7];
//			angle_2=openmv[6];
//			angle_z=(angle_1<<8)|angle_2;
//			yaw_2=angle_z/32768.0f*180.0f;
//		
//		state=8;
//	}
//					else if(state==8)		//¼ì²âÊÇ·ñ½ÓÊÜµ½½áÊø±êÖ¾
//	      {
//        	

//						state = 0;

//       
//            		for(i=0;i<8;i++)
//            		{
//               			 openmv[i]=0x00;
//            		}           
//				}
//						

//				USART_RX_STA=0;
		}
	}



/*
********************************************************************************************************************
*                  void DMA1_Stream3_IRQHandler(void)
*
*Description : ´®¿Ú3·¢ËÍÖÐ¶Ïº¯Êý 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void DMA1_Stream3_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream3,DMA_IT_TCIF3) != RESET)
    {
        /* Çå³ý±êÖ¾Î» */
        DMA_ClearFlag(DMA1_Stream3,DMA_IT_TCIF3);
        /* ¹Ø±ÕDMA */
        DMA_Cmd(DMA1_Stream3,DISABLE);
        /* ´ò¿ª·¢ËÍÍê³ÉÖÐ¶Ï,È·±£×îºóÒ»¸ö×Ö½Ú·¢ËÍ³É¹¦ */
        USART_ITConfig(USART3,USART_IT_TC,ENABLE);
    }
}

/*
********************************************************************************************************************
*                  void DMA1_S1_Reset(void)
*
*Description : ´®¿Ú3½ÓÊÕÖØÖÃ 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void DMA1_S1_Reset(void)//DMA1_Stream6 ½ÓÊÕÖØÖÃ
{ 
	DMA_ClearFlag(DMA1_Stream1,DMA_IT_TCIF1|DMA_FLAG_HTIF1|DMA_FLAG_TEIF1|DMA_FLAG_DMEIF1|DMA_FLAG_FEIF1);  
	
	DMA_Cmd(DMA1_Stream1,DISABLE); //¹Ø±ÕUSART2 TX DMA1 ËùÖ¸Ê¾µÄÍ¨µÀ

 	//DMA_SetCurrDataCounter(DMA1_Channel5,Uart1_DMA_Len);//DMAÍ¨µÀµÄDMA»º´æµÄ´óÐ¡
	DMA1_Stream1->NDTR = U3_DATA_LEN;
 	//DMA_Cmd(DMA1_Channel5, ENABLE);                    
	DMA_Cmd(DMA1_Stream1,ENABLE); //Ê¹ÄÜUSART2 TX DMA1 ËùÖ¸Ê¾µÄÍ¨µÀ
	/* Çå³ý±êÖ¾Î» */
   
}



/*****************************************************±±ÐÑ TF mini plus*//////////////////////////////////////////////////
/*****************************************************±±ÐÑ TF luna*//////////////////////////////////////////////////
/*****************************************************²¨ÌØÂÊ115200*//////////////////////////////////////////////////

//u8 Receive_ok=0;

//void USART3_IRQHandler(void)
//{
//	static uint8_t Uart3_Rec_Len = 0;
//	static uint8_t i=0;
//	int t;
//	uint8_t sum=0;
//	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //½ÓÊÕÖÐ¶Ï
//	{
//		t= USART_ReceiveData(USART3);//¶ÁÈ¡Êý¾Ý ×¢Òâ£ºÕâ¾ä±ØÐëÒª£¬·ñÔò²»ÄÜ¹»Çå³ýÖÐ¶Ï±êÖ¾Î»¡£
//		Uart3_Rec_Len = U3_DATA_LEN - DMA1_Stream3->NDTR;	//Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶
//		GPIO_ResetBits(GPIOE,GPIO_Pin_4 );//GPIOF9,F10ÉèÖÃ¸ß£¬µÆÃð
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
//		   Receive_ok=0;//´¦ÀíÊý¾ÝÍê±Ï±êÖ¾
//			OLED_Show3FNum(0,15,distance,4,2,12);			
//		  OLED_Refresh_Gram();
//			 
//			}
//		}
//     USART_ClearITPendingBit(USART3, USART_IT_IDLE);         //Çå³ýÖÐ¶Ï±êÖ¾
//		DMA1_S1_Reset();                                       //»Ö¸´DMAÖ¸Õë£¬µÈ´ýÏÂÒ»´ÎµÄ½ÓÊÕ
//    }
//	else if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	{
//	
//		USART_ClearITPendingBit(USART3, USART_IT_TC);
//		DMA1_Stream3->CR &= (uint32_t)(~DMA_SxCR_EN);   //¹Ø±ÕDMA,·¢ËÍÍê³É

//	}
//}


/****************************************************Å£±Æ¼¤¹â*//////////////////////////////////////////////////////////////////////////
/*****************************************************²¨ÌØÂÊ9600*//////////////////////////////////////////////////
/*****************************************************ÏÔÊ¾·ÅÖÐ¶Ï»áÌø*////////////////////////////////////////////////// 
//u8 Num = 0;              //½ÓÊÕÊý¾ÝµÄµ±Ç°Î»ÖÃ
//int a222=0;
//void Read_LaserDis(unsigned char ID, unsigned int *Data)       
//{	
//	unsigned char y=0;
//	unsigned int Receive_data [3] = { 0 };       //Êý¾Ý»º´æÇø

//	Num = 0; 
/////////////////////////////¶ÁÈ¡¾àÀë¡¢»·¾³ÖÊÁ¿¡¢»·¾³¹âÇ¿ÊýÖµ///////////////////////////////
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, 0x57);		

//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, ID);																  //IDÄ£¿é±àºÅ
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
//	delay_ms(2);

//  while(1)
//  {
//		if(rec_data_u3[0] != 0x75) { Num = 0; }  //ÅÐ¶ÏÖ¡Í·0x75,·ñÕßÖØÐÂ½ÓÊÕ
//		if(Num == 8)
//		{
//			Num = 0;
//			if(rec_data_u3[7] == 0x07)  //ÅÐ¶ÏÖ¡Î²0x07,·ñÕß²»¸³Öµ
//			{
//				Receive_data[0] = rec_data_u3[1];
//				Receive_data[0] <<= 8;
//				Receive_data[0] |= rec_data_u3[2];        
//				*Data = Receive_data[0];          //¾àÀë
////				a222=rec_data_u3[1]*256+rec_data_u3[2];
////        OLED_ShowNum(50,42,a222,4,12);	
////    		OLED_Refresh_Gram();
////				
//				Receive_data[1] = rec_data_u3[3];
//				Receive_data[1] <<= 8;
//				Receive_data[1] |= rec_data_u3[4];
//				*(Data+1) = Receive_data[1];          //»·¾³ÖÊÁ¿
//				
//				Receive_data[2] = rec_data_u3[5];
//				Receive_data[2] <<= 8;
//				Receive_data[2] |= rec_data_u3[6];
//				*(Data+2) = Receive_data[2];         //»·¾³¹âÇ¿        
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
/////////////////////////////¶ÁÈ¡¾àÀë¡¢»·¾³ÖÊÁ¿¡¢»·¾³¹âÇ¿ÊýÖµ///////////////////////////////
//}

//void Set_LaserDis(unsigned char ID, unsigned char Fun,unsigned char Par)	       
//{	
// ///////////////////////////ÉèÖÃ¹¦ÄÜ²ÎÊý///////////////////////////////	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, 0x4C);																//ÃüÁîÆðÊ¼ÐÅºÅ
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	
//	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, ID);																  //IDÄ£¿é±àºÅ
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
//	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, Fun);																//¹¦ÄÜÏî
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	
//	
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//	USART_SendData(USART3, Par);																//²ÎÊý
//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

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

void USART3_send_byte(uint8_t byte)
{
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);//µÈ´ý·¢ËÍÍê³É
	USART3->DR=byte;	
}

//·¢ËÍ¶à×Ö½ÚÊý¾Ý
void USART3_Send_bytes(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		USART3_send_byte(Buffer[i++]);
	}
}
//·¢ËÍ¶à×Ö½ÚÊý¾Ý+Ð£ÑéºÍ
void USART3_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//ÀÛ¼ÓLength-1Ç°µÄÊý¾Ý
		USART3_send_byte(Buffer[i++]);
	}
}

//void send_com(u8 data)
//{
//	u8 bytes[3]={0};
//	bytes[0]=0xa5;
//	bytes[1]=data;//¹¦ÄÜ×Ö½Ú
//	USART3_Send(bytes,3);//·¢ËÍÖ¡Í·¡¢¹¦ÄÜ×Ö½Ú¡¢Ð£ÑéºÍ
//}


///************************************************************
//*  ²â¾àº¯Êý 
//*  ×¢Òâ£ºÔÚ³õÊ¼»¯Íê³É±ØÐëÒªÌí¼ÓÐ´ÃüÁî Èç£ºsend_com(0x45);
//*   0x45: Á¬ÐøÊä³ö¾àÀëÊý¾Ý      
//*   0x50: ³¤¾àÀë²âÁ¿Ä£Ê½
//*   0x51£º¿ìËÙ²âÁ¿Ä£Ê½
//*   0x52£º¸ß¾«¶È²âÁ¿Ä£Ê½
//*   0x53: Ò»°ã²âÁ¿Ä£Ê½
//************************************************************/
//void Mea_dis(void)
//{
//	u8 sum=0,i=0;
//	uint16_t distance=0;
//	uint16_t Strength=0;
//	double dis=0.0;
//	if(Receive_ok)//´®¿Ú½ÓÊÕÍê±Ï
//		{
//			distance=(rec_data_u3[3]<<8)|rec_data_u3[2];
//		   Receive_ok=0;//´¦ÀíÊý¾ÝÍê±Ï±êÖ¾
//			OLED_Show3FNum(0,15,distance,4,2,12);			
//		  OLED_Refresh_Gram();
//			
//	 }
//}
/***************************************************************±±ÐÑ TF mini plus*/////////////////////////////////////////////////////////////////////////


/*
********************************************************************************************************************
*                  void DMA1_Stream3_IRQHandler(void)
*
*Description : ´®¿Ú3·¢ËÍÖÐ¶Ïº¯Êý 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/


