#include "NRF24L01.h"
#include "SpiDrive.h"
#include "led.h"
#include "oled.h"
#include "mpu6050.h"
#include "key.h"
#include "delay.h"
#include "timer.h"
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : 变量定义
*Notes       : none
******************************************************************************************************************
*/
static const uint8_t NRF24L01_TX_ADDRESS[TX_ADR_WIDTH]={0x00,0x43,0x10,0x10,0x01};	//本地地址
static const uint8_t NRF24L01_RX_ADDRESS[RX_ADR_WIDTH]={0x00,0x43,0x10,0x10,0x01};	//接收地址
uint8_t NRF24L01_TxBuf[32]={1,2,3,4,5,6,7,8};																										//发送数组
uint8_t NRF24L01_RxBuf[32]={0};																										//接收数组

int nRF24L01_Mode_Flag = -1 ;            //模式标志位
uint8_t nRF24L01_Receive_Flag = 0 ;        //接收标志位

/******************************************************************************
*                          NRF24L01_Init()
*
*Description : NRF24L01接口初始化
*Arguments   : none
*Returns     : none
*Notes       : 使用硬件SPI
*******************************************************************************
*/
void NRF24L01_Init(void)
{
	GPIO_setAsOutputPin(NRF24L01_CE_GPIO_PORT,  NRF24L01_CE_GPIO_PIN);       //输出
	GPIO_setAsOutputPin(NRF24L01_CSN_GPIO_PORT, NRF24L01_CSN_GPIO_PIN);      //输出
	GPIO_setAsInputPin (NRF24L01_IRQ_GPIO_PORT, NRF24L01_IRQ_GPIO_PIN);      //输入
	GPIO_setOutputHighOnPin(NRF24L01_CE_GPIO_PORT,  NRF24L01_CE_GPIO_PIN);   //输出高电平
	GPIO_setOutputHighOnPin(NRF24L01_CSN_GPIO_PORT, NRF24L01_CSN_GPIO_PIN);  //输出高电平
	SPI_Drive_Init(NRF24L01_SPI_DRIVE_INIT);    		                             //初始化SPI
	NRF24L01_CE_LOW(); 																				                   //使能24L01
	NRF24L01_CSN_HIGH();																				                 //SPI片选取消	 	
}
/******************************************************************************
*                          NRF24L01_Check()
*
*Description : 检测NRF24L01是否初始化成功
*Arguments   : none
*Returns     : 0,成功;	1,失败
*Notes       : none
*******************************************************************************
*/
uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5); //写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5);                //读出写入的地址  
	for(i=0;i<5;i++)
		if(buf[i]!=0XA5)
			break;	 							   
	if(i!=5)
		return 1;                                      //检测24L01错误	
	return 0;		                                     //检测到24L01
}	 	 
/******************************************************************************
*                          NRF24L01_Write_Reg()
*
*Description : 写NRF24L01寄存器
*Arguments   : reg:指定寄存器地址;	value:写入的值
*Returns     : 返回NRF24L01状态值status
*Notes       : none
*******************************************************************************
*/
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;	
	NRF24L01_CSN_LOW();                 //使能SPI传输
	status = SPI_Rd_Wr_Byte(reg, NRF24L01_SPI_DRIVE_SELECT); //发送寄存器号 
	SPI_Rd_Wr_Byte(value,  NRF24L01_SPI_DRIVE_SELECT);        //写入寄存器的值
	NRF24L01_CSN_HIGH();                //禁止SPI传输	   
	return(status);       			        //返回状态值
}
/******************************************************************************
*                          NRF24L01_Read_Reg()
*
*Description : 读NRF24L01寄存器值
*Arguments   : reg,要读的寄存器地址
*Returns     : 返回读取值
*Notes       : none
*******************************************************************************
*/
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;	    
 	NRF24L01_CSN_LOW();                   //使能SPI传输		
	SPI_Rd_Wr_Byte(reg, NRF24L01_SPI_DRIVE_SELECT);            //发送寄存器号
	reg_val=SPI_Rd_Wr_Byte(0xFF,  NRF24L01_SPI_DRIVE_SELECT);   //读取寄存器内容
	NRF24L01_CSN_HIGH();                  //禁止SPI传输		    
	return(reg_val);                      //返回
}
/******************************************************************************
*                          NRF24L01_Read_Buf()
*
*Description : 在指定地址读出指定长度的数据
*Arguments   : reg:寄存器(地址);	pBuf:	数据指针;	len:数据长度
*Returns     : 返回NRF24L01状态值status
*Notes       : none
*******************************************************************************
*/
static uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
	uint8_t status,uint8_t_ctr;	       
	NRF24L01_CSN_LOW();              //使能SPI传输
	status=SPI_Rd_Wr_Byte(reg, NRF24L01_SPI_DRIVE_SELECT);//发送寄存器值(位置),并读取状态值   	   
 	for(uint8_t_ctr=0;uint8_t_ctr<len;uint8_t_ctr++)pBuf[uint8_t_ctr]=SPI_Rd_Wr_Byte(0xFF,  NRF24L01_SPI_DRIVE_SELECT);//读出数据
	NRF24L01_CSN_HIGH();                //关闭SPI传输
	return status;                 //返回读到的状态值
}
/******************************************************************************
*                          NRF24L01_Write_Buf()
*
*Description : 在指定地址写入指定长度的数据
*Arguments   : reg:寄存器(地址);	pBuf:	数据指针;	len:数据长度
*Returns     : 返回NRF24L01状态值status
*Notes       : none
*******************************************************************************
*/
static uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status,uint8_t_ctr;	    
 	NRF24L01_CSN_LOW();                                                              //使能SPI传输
	status = SPI_Rd_Wr_Byte(reg, NRF24L01_SPI_DRIVE_SELECT);                                              //发送寄存器值(位置),并读取状态值
	for(uint8_t_ctr=0; uint8_t_ctr<len; uint8_t_ctr++) SPI_Rd_Wr_Byte(*pBuf++,  NRF24L01_SPI_DRIVE_SELECT); //写入数据	 
	NRF24L01_CSN_HIGH();                                                             //关闭SPI传输
	return status;                                                                   //返回读到的状态值
}			
/******************************************************************************
*                          NRF24L01_TxPacket()
*
*Description : 启动NRF24L01发送一次数据
*Arguments   : txbuf,待发送数据首地址
*Returns     : 0x20,发送完成;		0xff,发送失败
*Notes       : none
*******************************************************************************
*/
uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
	//发送模式
  uint8_t sta;
	NRF24L01_CE_LOW();
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
	NRF24L01_CE_HIGH();                                  //启动发送	   
	while(NRF24L01_IRQ_RD()!=0);                         //等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);                       //读取状态寄存器的值	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta);        //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX)                                       //达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);                 //清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)                                        //发送完成
	{
		return TX_OK;
	}
	return 0xff;                                         //其他原因发送失败
}
/******************************************************************************
*                          NRF24L01_ACK()
*
*Description : 检测应答信号
*Arguments   : none
*Returns     : 0,成功;	1,失败
*Notes       : none
*******************************************************************************
*/
//static uint8_t NRF24L01_ACK(void)
//{  //用于发射
//	uint8_t sta;
//	sta=NRF24L01_Read_Reg(STATUS);                     // 返回状态寄存器
//	if((sta&TX_OK)||(sta&MAX_TX))                      //发送完毕中断
//	{
//	   NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,0xff);  // 清除TX_DS或MAX_RT中断标志
//	   NRF24L01_CSN_LOW();
//	   NRF24L01_Write_Reg(FLUSH_RX,0xff);              //用于清空FIFO 
//     NRF24L01_CSN_HIGH(); 
//	   return(0);
//	}
//	else
//	   return(1);
//}
/******************************************************************************
*                          NRF24L01_RxPacket()
*
*Description : 启动NRF24L01接收一次数据
*Arguments   : txbuf,待发送数据首地址
*Returns     : 0,成功;	1,失败
*Notes       : none
*******************************************************************************
*/
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t sta;		    							   
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	 
	if(sta&RX_OK)//接收到数据
	{
		NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	                   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}	
/******************************************************************************
*                          NRF24L01_RX_Mode()
*
*Description : 初始化NRF24L01到RX模式
*Arguments   : none
*Returns     : none
*Notes       : 注意选择RF频道,波特率和LNA HCURR
*******************************************************************************
*/	   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE_LOW();	  
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)NRF24L01_RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    	//使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);	//使能通道0的接收地址  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	    	//设置RF通信频率		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);		//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	NRF24L01_CE_HIGH(); //CE为高,进入接收模式 
}				
/******************************************************************************
*                          NRF24L01_TX_Mode()
*
*Description : 初始化NRF24L01到TX模式
*Arguments   : none
*Returns     : none
*Notes       : 注意选择RF频道,波特率和LNA HCURR
*******************************************************************************
*/
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE_LOW();	    
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(uint8_t*)NRF24L01_TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)NRF24L01_RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF24L01_CE_HIGH();                               //CE为高,10us后启动发送
}

s16 Rece_pitch=0;
s16 Rece_roll=0;
s16 Rece_yaw=0;
int Send_pitch=0;
int Send_roll=0;
int Send_yaw=0;
float mpu_pitch=0;
float mpu_roll=0;
float mpu_yaw=0;

void NRF24L01_Rece_mpu(void)
{
	if(NRF24L01_RxPacket(NRF24L01_RxBuf)==0) //接收到信息
	{
		LED1=!LED1;
		if(NRF24L01_RxBuf[0]==0xAA&&NRF24L01_RxBuf[7]==0xBB)
		{

			Rece_pitch=NRF24L01_RxBuf[2]<<8|NRF24L01_RxBuf[1];			
			Rece_roll=(NRF24L01_RxBuf[3])|(NRF24L01_RxBuf[4]<<8);
			Rece_yaw=(NRF24L01_RxBuf[5])|(NRF24L01_RxBuf[6]<<8);

			mpu_pitch=Rece_pitch/100.0;
			mpu_roll=Rece_roll/100.0;
			mpu_yaw=Rece_yaw/100.0;
			
      OLED_Show3FNum(32,0,mpu_pitch,3,3,12);
      OLED_Show3FNum(32,16,mpu_roll,3,3,12);
      OLED_Show3FNum(32,32,mpu_yaw,3,3,12);

			OLED_Refresh_Gram();//更新显示到OLED	
		}
	}
}

void NRF24L01_Send_mpu(void)
{

	  if(NRF24L01_TxPacket(NRF24L01_TxBuf)==TX_OK)
		{
			//GESTURE test//
//			Send_pitch=MPUData.pitch*100;
//		  Send_roll=MPUData.roll*100;
//		  Send_yaw=MPUData.yaw*100;
			//NRF24L01 TEST//
//			Send_pitch=10.5*100;
//		  Send_roll=11.7*100;
//		  Send_yaw=12*100;	
//		NRF24L01_TxBuf[0]=0xAA;
//		NRF24L01_TxBuf[1]=Send_pitch  & 0xFF;
//		NRF24L01_TxBuf[2]=(Send_pitch>>8) & 0xFF;
//		NRF24L01_TxBuf[3]=Send_roll  & 0xFF;
//		NRF24L01_TxBuf[4]=(Send_roll)>>8 & 0xFF;
//		NRF24L01_TxBuf[5]=Send_yaw  & 0xFF;
//		NRF24L01_TxBuf[6]=(Send_yaw)>>8 & 0xFF;
//		NRF24L01_TxBuf[7]=0xBB;
			OLED_ShowString(0,0,"tx_ok",12);
			OLED_Refresh_Gram();
			Delay_ms(200);	 
		}
	else 
	{
			OLED_Clear();
			OLED_Refresh_Gram();		
			LED1=!LED1;
			Delay_ms(200);	
	}
}

void NRF24L01_TEST(void)
{
	
	u8 key,mode;
	NRF24L01_Init();
	Delay_ms(100);
	while(NRF24L01_Check())
	{
		BEEP=!BEEP;
		Delay_ms(200);
	}
	OLED_Clear();
	OLED_ShowString(16,16,"key1 - RX",12);
	OLED_ShowString(16,32,"key2 - TX",12);
  OLED_Refresh_Gram();
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
		{
			mode=0;			
			break;
		}else if(key==KEY2_PRES)
		{
			mode=1;
			break;
		}		
		Delay_ms(5);	  
	}
	
	if(mode==0)//RX模式
	{
	  OLED_Clear();
 		OLED_ShowString(16,0,"mode  RX",12);
	 OLED_ShowString(0,16,"Pitch          C",12);
	 OLED_ShowString(0,32,"Roll           C",12);
	 OLED_ShowString(0,48,"Yaw            C",12);
		OLED_Refresh_Gram();
		NRF24L01_RX_Mode();
		TimerA0_Tim_Init();
		while(1);
	}
	else 
	{
	  OLED_Clear();		
		OLED_ShowString(16,16," TX",12);
		OLED_Refresh_Gram();
		NRF24L01_TX_Mode();
    while(1)
		{
			NRF24L01_Send_mpu();
		}			
	}
}







