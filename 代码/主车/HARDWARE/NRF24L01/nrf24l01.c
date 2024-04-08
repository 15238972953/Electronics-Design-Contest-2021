/*
******************************************************************************************************************
*Filename      :NRF24L01.c
*Programmer(s) :416GZJ
*Description   :2020������
								CE--PD4
								CSN--PD1
								SCK--PB3
								MOSI--PB5
								MISO--PB4
								IRQ--PD0
								
******************************************************************************************************************
*/

#include "NRF24L01.h"
#include "spi3.h" 
#include "key.h" 
#include "oled.h" 
#include "delay.h" 
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
******************************************************************************************************************
*/
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //����?����??��
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};

u8 t;
u8 NRF_Flag=0;
u8 tmp_buf[33];


#define NRF_BYTE0(dwTemp)       (*(char *)(&dwTemp))   
#define NRF_BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define NRF_BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define NRF_BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
	

void NRF24L01_Init(void)
{
	u8 key;
	NRF24L01_IO_Init();
	NRF_SPI3_Init();
//	while(1)
		NRF24L01_Check();
	while(NRF24L01_Check())
	{
		OLED_ShowString(0,0,(void *)"NRF24L01 Error!",12);
		OLED_ShowString(0,20,(void *)"Press Back to Break!",12);
		OLED_Refresh_Gram();
		key=KEY_Scan(0);
		if(key==1)	break;
	}
	delay_ms(200);
	OLED_Clear();
	OLED_Refresh_Gram();
}


/*
*****************************************************************************************************************
*                                     void Motor_24L01_Init(void) 
*
*Description : �˶����ư�24L01ͨѶ��ʼ��
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void NRF24L01_IO_Init(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,  ENABLE);//Motor_24L01_CE(PD4)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��

	GPIO_InitStructure.GPIO_Pin = NRF24L01_CSN_Pin;//PD1�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(NRF24L01_CSN_Port, &GPIO_InitStructure);//��ʼ��PD1

	GPIO_InitStructure.GPIO_Pin = NRF24L01_CE_Pin;	//PD4�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(NRF24L01_CE_Port, &GPIO_InitStructure);//��ʼ��PD4

	GPIO_InitStructure.GPIO_Pin = NRF24L01_IRQ_Pin;	//PD0��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(NRF24L01_IRQ_Port, &GPIO_InitStructure);//��ʼ��PD0
	
	
//	GPIO_SetBits(GPIOD,GPIO_Pin_1);//PD1���1,��ֹSPI FLASH����NRF��ͨ�� 

	NRF24L01_CE=0;//ʹ��Motor_24L01 Ƭѡ�ź�
	NRF24L01_CSN=1;//Motor_SPIƬѡȡ��	 		 	 SPIƬѡ�ź�
}


/*
*****************************************************************************************************************
*                                     u8 Motor_24L01_Check(void)
*
*Description : ���Motor_24L01�Ƿ����
*Arguments   : none
*Returns     : ����ֵ:0���ɹ�;1��ʧ��	
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	NRF_SPI3_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ10.5Mhz��24L01�����SPIʱ��Ϊ10Mhz��   	 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++) 		 if(buf[i]!=0XA5)  break;	 							   
	if(i!=5)   return 1;//���24L01����	
	return 0;		 //��⵽24L01
}	 	 

/*
*****************************************************************************************************************
*                                     u8 Motor_24L01_Write_Reg(u8 reg,u8 value)
*
*Description : Motor_SPIд�Ĵ���
*Arguments   : reg:ָ���Ĵ�����ַ; value:д���ֵ
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
	NRF24L01_CSN=0;                 //ʹ��SPI����
	status =NRF_SPI3_ReadWriteByte(reg);//���ͼĴ����� 
	NRF_SPI3_ReadWriteByte(value);      //д��Ĵ�����ֵ
	NRF24L01_CSN=1;                 //��ֹSPI����	   
	return(status);       			//����״ֵ̬
}

/*
*****************************************************************************************************************
*                                     u8 Motor_24L01_Read_Reg(u8 reg)
*
*Description : ��ȡMotor_SPI�Ĵ���ֵ
*Arguments   : reg:Ҫ���ļĴ���
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
	NRF24L01_CSN = 0;          //ʹ��SPI����		
	NRF_SPI3_ReadWriteByte(reg);   //���ͼĴ�����
	reg_val=NRF_SPI3_ReadWriteByte(0xff);//��ȡ�Ĵ�������
	NRF24L01_CSN = 1;          //��ֹSPI����		    
	return(reg_val);           //����״ֵ̬
}	

/*
*****************************************************************************************************************
*                                    u8 Motor_24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
*
*Description : ��ָ��λ�ö���ָ�����ȵ�����
*Arguments   : reg:�Ĵ���(λ��); *pBuf:����ָ��; len:���ݳ���
*Returns     : �˴ζ�����״̬�Ĵ���ֵ 
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
	NRF24L01_CSN = 0;//ʹ��SPI����
	status=NRF_SPI3_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=NRF_SPI3_ReadWriteByte(0xff);//��������
	NRF24L01_CSN=1;//�ر�SPI����
	return status;//���ض�����״ֵ̬
}

/*
*****************************************************************************************************************
*                                    u8 Motor_24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
*
*Description : ��ָ��λ��дָ�����ȵ�����
*Arguments   : reg:�Ĵ���(λ��); *pBuf:����ָ��; len:���ݳ���
*Returns     : �˴ζ�����״̬�Ĵ���ֵ 
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
	NRF24L01_CSN = 0;//ʹ��SPI����
	status = NRF_SPI3_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
	for(u8_ctr=0; u8_ctr<len; u8_ctr++)NRF_SPI3_ReadWriteByte(*pBuf++); //д������	 
	NRF24L01_CSN = 1; //�ر�SPI����
	return status;  //���ض�����״ֵ̬
}				

/*
*****************************************************************************************************************
*                                   u8 Motor_24L01_TxPacket(u8 *txbuf)
*
*Description : ����Motor_24L01����һ������
*Arguments   : txbuf:�����������׵�ַ
*Returns     : TX_OK:�������״��; 0xff:����ʧ��
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
	NRF_SPI3_SetSpeed(SPI_BaudRatePrescaler_8);//spi�ٶ�Ϊ10.5Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
	NRF24L01_CE=1;//��������	   
	while(NRF24L01_IRQ!=0);//�ȴ��������
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}


/*
*****************************************************************************************************************
*                                   u8 Motor_24L01_RxPacket(u8 *rxbuf)
*
*Description : ����NRF24L01����һ������
*Arguments   : rxbuf:�����������׵�ַ
*Returns     : 0:�������״�����������������
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
	NRF_SPI3_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ10.5Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&RX_OK)//���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}			


/*
*****************************************************************************************************************
*                                   void Motor_24L01_RX_Mode(void)
*
*Description : �ú�����ʼ��Motor_24L01��RXģʽ
*Arguments   : ����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
*                          ��CE��ߺ�,������RXģʽ,�����Խ���������		
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	NRF24L01_CE = 1; //CEΪ��,�������ģʽ 
}

/*
*****************************************************************************************************************
*                                   void Motor_24L01_TX_Mode(void)
*
*Description : �ú�����ʼ��Motor_24L01��TXģʽ
*Arguments   : ����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
*                          PWR_UP,CRCʹ��;��CE��ߺ�,������RXģʽ,�����Խ���������		   
*                          CEΪ�ߴ���10us,����������.	 
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void NRF24L01_TX_Mode(void)
{
	NRF24L01_CE=0;	    
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;//CEΪ��,10us����������
}



/*
*****************************************************************************************************************
*                                     void NRF24L01_Com_RX(void)
*
*Description : NRF24L01ͨѶ���պ���
*Arguments   : none                         
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
u32 Rece_Data;

void NRF24L01_Com_RX(void)
{
	u8 Sum;
	OLED_ShowString(0,0,(void *)"NRF24L01 RX_Mode",12);
	OLED_Refresh_Gram();
	
	NRF24L01_RX_Mode();	
	
	OLED_ShowNum(55,10,Rece_Data,4,16);//��ʾ����
	OLED_Refresh_Gram();
	
	if(NRF24L01_RxPacket(tmp_buf)==0) //���յ���Ϣ
	{
		Sum = 0;
		for(t=0;t<7;t++) Sum+=tmp_buf[t];
		if(tmp_buf[7]==Sum)
		{
			Rece_Data=tmp_buf[2];
			if((tmp_buf[0] == 0xAA)&(tmp_buf[1] == 0xBB))
			OLED_ShowNum(55,10,Rece_Data,4,16);//��ʾ����
			OLED_Refresh_Gram();
		}
	}
}

/*
*****************************************************************************************************************
*                                     void NRF24L01_Com_TX(u32 data)
*
*Description : NRF24L01ͨѶ���ͺ���
*Arguments   : data ��Ҫ���͵�����                        
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void NRF24L01_Com_TX(u32 data)
{
	u8 Sum,t;	
// 
//	OLED_ShowString(0,0,(void *)"NRF24L01 TX_Mode",12);
//	OLED_Refresh_Gram();
	NRF24L01_TX_Mode();
	
	tmp_buf[0] = 0xAA;
	tmp_buf[1] = 0xBB;
	tmp_buf[2] = NRF_BYTE0(data);
	tmp_buf[3] = NRF_BYTE1(data);
	tmp_buf[4] = NRF_BYTE2(data);
	tmp_buf[5] = NRF_BYTE3(data);
	tmp_buf[6] = NRF_Flag;	
	
	Sum = 0;
	for(t=0;t<7;t++)	Sum+=tmp_buf[t];//У�����
	tmp_buf[7]  = Sum;
	NRF24L01_TxPacket(tmp_buf);	      //��ʼ����
}


/*
*****************************************************************************************************************
*                                     void NRF24L01_Rece_mpu(void)
*
*Description : NRF24L01ͨѶ���պ���
*Arguments   : none                         
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void NRF24L01_Rece_mpu(void)
{
	NRF24L01_RX_Mode();

	if(NRF24L01_RxPacket(tmp_buf)==0) //���յ���Ϣ
	{
		if(tmp_buf[0]==0xAA&&tmp_buf[7]==0xBB)
		{
//			Rece_pitch=(tmp_buf[1])|(tmp_buf[2]<<8);
//			Rece_roll=(tmp_buf[3])|(tmp_buf[4]<<8);
//			Rece_yaw=(tmp_buf[5])|(tmp_buf[6]<<8);
//			mpu_pitch=Rece_pitch/100.0;
//			mpu_roll=Rece_roll/100.0;
//			mpu_yaw=Rece_yaw/100.0;
		}
	}
}

void NRF_ReceiveData(void)
{
  NRF24L01_Init();
  u8 rx[1]={1};
  NRF24L01_RX_Mode();
	while(1)
			{
				if(NRF24L01_RxPacket(rx)==0)
				{
					OLED_ShowNum(0,16,rx[0],2,12);			
					OLED_Refresh_Gram();
					delay_ms(200);
				}
			}	
}

//void NRF24L01_Test(void)
//{
//	NRF24L01_Init();
//	u8 key;
//	u8 tx[24]={1,2,3,4};
//	u8 rx[24]={0};
//	
//	
//	
//	while(1)
//	{
//			
//			NRF24L01_RX_Mode();
//			OLED_Clear();
//			OLED_ShowString(12,0,(void *)"RX MODE",12);
//			OLED_ShowString(12,16,(void *)"RXING",12);
//			OLED_Refresh_Gram();
//			delay_ms(1000);
//			OLED_Clear();
//			while(1)
//			{
//				if(NRF24L01_RxPacket(rx)==0)
//				{
//					OLED_ShowString(12,0,(void *)"RX_OK",12);
//					OLED_ShowNum(0,12,rx[0],4,12);
//					OLED_ShowNum(0,24,rx[1],4,12);
//					OLED_ShowNum(0,36,rx[2],4,12);
//					OLED_ShowNum(0,48,rx[3],4,12);
//					OLED_Refresh_Gram();
//					delay_ms(1000);
//					OLED_ShowString(12,0,(void *)"RXING",12);
//					OLED_Refresh_Gram();
//				}
//		  }
//		}	
//	}

void NRF24L01_Test(void)
{
	NRF24L01_Init();
	u8 key;
	u8 i=0;
	u8 tx[24]={1,2,3,4};
	u8 rx[24]={0};
	OLED_ShowString(12,0,(void *)"Test_6 24L01",12);
	OLED_ShowString(12,16,(void *)"->K1 TX",12);
	OLED_ShowString(12,32,(void *)"->K2 RX",12);
	OLED_Refresh_Gram();
	
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
		{
			NRF24L01_TX_Mode();
			OLED_Clear();
			OLED_ShowString(12,0,(void *)"TX MODE",12);
			OLED_ShowString(12,16,(void *)"TXING",12);
			OLED_Refresh_Gram();
			delay_ms(1000);
			OLED_Clear();
			while(1)
			{
				if(NRF24L01_TxPacket(tx)==TX_OK)
				{
					OLED_ShowString(0,0,(void *)"TX_OK",12);
					i++;
					i = i%4;
					tx[0] = i+1;
					tx[1] = i+2;
					tx[2] = i+3;
					tx[3] = i+4;
					OLED_ShowNum(0,16,tx[0],2,12);
					OLED_ShowNum(64,16,tx[1],2,12);
					OLED_ShowNum(0,32,tx[2],2,12);
					OLED_ShowNum(64,32,tx[3],2,12);
					OLED_Refresh_Gram();
					delay_ms(200);
				}
				else
				{
					OLED_Clear();
					OLED_ShowString(0,0,(void *)"TX_NO",12);
					OLED_Refresh_Gram();
					delay_ms(20);
				}

			}
		}
		
		if(key==KEY2_PRES)
		{
			NRF24L01_RX_Mode();
			OLED_Clear();
			OLED_ShowString(12,0,(void *)"RX MODE",12);
			OLED_ShowString(12,16,(void *)"RXING",12);
			OLED_Refresh_Gram();
			delay_ms(1000);
			OLED_Clear();
			while(1)
			{
				if(NRF24L01_RxPacket(rx)==0)
				{
					OLED_ShowString(12,0,(void *)"RX_OK",12);
					OLED_ShowNum(0,12,rx[0],4,12);
					OLED_ShowNum(0,24,rx[1],4,12);
					OLED_ShowNum(0,36,rx[2],4,12);
					OLED_ShowNum(0,48,rx[3],4,12);
					OLED_Refresh_Gram();
					delay_ms(100);
				}
				
		  }
		}	
	}
	
}