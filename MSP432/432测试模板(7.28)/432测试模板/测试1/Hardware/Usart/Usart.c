#include "string.h"
#include "Usart.h"
#include "stdio.h"         //print函数C文件库
#include "sys.h"
#include "openmv.h"
#include "oled.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#define BYTE0(dwTemp)       (*( char *)(&dwTemp))                                              //字分离四字节
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))                                         //字分离四字节
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))                                         //字分离四字节
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))                                         //字分离四字节


void Usart_init(void)
{
	#if USART0_EN
	Uart_A0_Init();
	#endif
	
	#if USART1_EN
	Uart_A1_Init();
	#endif
	
	#if USART2_EN
	Uart_A2_Init();	
	#endif
	
	#if USART3_EN
	Uart_A3_Init();
	#endif
	
//	#if USART2_DMA_EN

//	#endif
}

/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : 变量声明
*Notes       : none
******************************************************************************************************************
*/
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	 



//串口参数设置，波特率设置参考以下地址：
//http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
const eUSCI_UART_Config UartA0Config =      //串口48MHz,波特率115200
{
	EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //选择时钟
	26,                                     // BRDIV
	1,                                       // UCxBRF
	0,                                       // UCxBRS = 0
//	EUSCI_A_UART_NO_PARITY,                  // 无奇偶校验位
	EUSCI_A_UART_ODD_PARITY,                 // 奇校验
//	EUSCI_A_UART_EVEN_PARITY,                // 偶校验
	EUSCI_A_UART_LSB_FIRST,                  // 一位起始位
	EUSCI_A_UART_ONE_STOP_BIT,               // 一位停止位
	EUSCI_A_UART_MODE,                       // UART模式
	EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};


const eUSCI_UART_Config UartA1Config =       //串口48MHz,波特率115200
{
	EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //选择时钟
	26 ,                                     // BRDIV
	1,                                       // UCxBRF
	0,                                       // UCxBRS = 0
	EUSCI_A_UART_NO_PARITY,                  // 无奇偶校验位
//	EUSCI_A_UART_ODD_PARITY,                 // 奇校验
//	EUSCI_A_UART_EVEN_PARITY,                // 偶校验
	EUSCI_A_UART_LSB_FIRST,                  // 一位起始位
	EUSCI_A_UART_ONE_STOP_BIT,               // 一位停止位
	EUSCI_A_UART_MODE,                       // UART模式
	EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};


const eUSCI_UART_Config UartA2Config =       //串口48MHz,波特率115200
{
	EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //选择时钟
	26 ,                                     // BRDIV
	1,                                       // UCxBRF
	0,                                       // UCxBRS = 0
	EUSCI_A_UART_NO_PARITY,                  // 无奇偶校验位
//	EUSCI_A_UART_ODD_PARITY,                 // 奇校验
//	EUSCI_A_UART_EVEN_PARITY,                // 偶校验
	EUSCI_A_UART_LSB_FIRST,                  // 一位起始位
	EUSCI_A_UART_ONE_STOP_BIT,               // 一位停止位
	EUSCI_A_UART_MODE,                       // UART模式
	EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};


const eUSCI_UART_Config UartA3Config =       //串口48MHz,波特率115200
{
	EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //选择时钟
	26 ,                                     // BRDIV
	1,                                       // UCxBRF
	0,                                       // UCxBRS = 0
	EUSCI_A_UART_NO_PARITY,                  // 无奇偶校验位
//	EUSCI_A_UART_ODD_PARITY,                 // 奇校验
//	EUSCI_A_UART_EVEN_PARITY,                // 偶校验
	EUSCI_A_UART_LSB_FIRST,                  // 一位起始位
	EUSCI_A_UART_ONE_STOP_BIT,               // 一位停止位
	EUSCI_A_UART_MODE,                       // UART模式
	EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};


/******************************************************************************************************************
*                                               Uart_A0_Init()
*
*Description : 串口A0初始化
*Arguments   : none
*Returns     : none
*Notes       : P1.2 P1.3
*******************************************************************************************************************
*/
void Uart_A0_Init(void)
{
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);//设置DCO时钟必须有，否则串口无法使用 48Mhz
	/* Configuring UART Module */
	MAP_UART_initModule(EUSCI_A0_MODULE, &UartA0Config);
	/* Enable UART module */
	MAP_UART_enableModule(EUSCI_A0_MODULE);                                      //启动串口
	MAP_UART_enableInterrupt(EUSCI_A0_MODULE, EUSCI_A_UART_RECEIVE_INTERRUPT);   //启动串口接受中断
	MAP_Interrupt_enableInterrupt(INT_EUSCIA0);                                  //启动串口中断
	MAP_Interrupt_enableMaster();                                                //开总中断  
}


/******************************************************************************************************************
*                                               Uart_A1_Init()
*
*Description : 串口A1初始化
*Arguments   : none
*Returns     : none
*Notes       : P2.2 P2.3
*******************************************************************************************************************
*/
void Uart_A1_Init(void)
{
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);//设置DCO时钟必须有，否则串口无法使用 48Mhz
	/* Configuring UART Module */
	MAP_UART_initModule(EUSCI_A1_MODULE, &UartA1Config);
	/* Enable UART module */
	MAP_UART_enableModule(EUSCI_A1_MODULE);                                      //启动串口
	MAP_UART_enableInterrupt(EUSCI_A1_MODULE, EUSCI_A_UART_RECEIVE_INTERRUPT);   //启动串口接受中断
	MAP_Interrupt_enableInterrupt(INT_EUSCIA1);                                  //启动串口中断
	MAP_Interrupt_enableMaster();                                                //开总中断  
}


/******************************************************************************************************************
*                                               Uart_A2_Init()
*
*Description : 串口A2初始化
*Arguments   : none
*Returns     : none
*Notes       : P3.2 P3.3
*******************************************************************************************************************
*/
void Uart_A2_Init(void)
{
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3,GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);//设置DCO时钟必须有，否则串口无法使用 48Mhz
	/* Configuring UART Module */
	MAP_UART_initModule(EUSCI_A2_MODULE, &UartA2Config);
	/* Enable UART module */
	MAP_UART_enableModule(EUSCI_A2_MODULE);                                      //启动串口
	MAP_UART_enableInterrupt(EUSCI_A2_MODULE, EUSCI_A_UART_RECEIVE_INTERRUPT);   //启动串口接受中断
	MAP_Interrupt_enableInterrupt(INT_EUSCIA2);                                  //启动串口中断
	MAP_Interrupt_enableMaster();                                                //开总中断  
}


/******************************************************************************************************************
*                                               Uart_A3_Init()
*
*Description : 串口A3初始化
*Arguments   : none
*Returns     : none
*Notes       : P9.6 P9.7
*******************************************************************************************************************
*/
void Uart_A3_Init(void)
{
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9,GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9,GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);//设置DCO时钟必须有，否则串口无法使用 48Mhz
	/* Configuring UART Module */
	MAP_UART_initModule(EUSCI_A3_MODULE, &UartA3Config);
	/* Enable UART module */
	MAP_UART_enableModule(EUSCI_A3_MODULE);                                      //启动串口
	MAP_UART_enableInterrupt(EUSCI_A3_MODULE, EUSCI_A_UART_RECEIVE_INTERRUPT);   //启动串口接受中断
	MAP_Interrupt_enableInterrupt(INT_EUSCIA3);                                  //启动串口中断
	MAP_Interrupt_enableMaster();                                                //开总中断  
}


/******************************************************************************
*                          Uart_A0_Send()
*
*Description : 串口A0发送一个字节数据
*Arguments   : 发送的字节数据
*Returns     : none
*Notes       : none
*******************************************************************************
*/


void Uart_A0_Send(uint8_t TxData)
{
	MAP_UART_transmitData(EUSCI_A0_MODULE, TxData);
	while(MAP_UART_queryStatusFlags(EUSCI_A0_MODULE, EUSCI_A_UART_BUSY));        //等待发送完成
}
/******************************************************************************
*                          Uart_A1_Send()
*
*Description : 串口A1发送一个字节数据
*Arguments   : 发送的字节数据
*Returns     : none
*Notes       : none
*******************************************************************************
*/


void Uart_A1_Send(uint8_t TxData)
{
	MAP_UART_transmitData(EUSCI_A1_MODULE, TxData);
	while(MAP_UART_queryStatusFlags(EUSCI_A1_MODULE, EUSCI_A_UART_BUSY));        //等待发送完成
}
/******************************************************************************
*                          Uart_A2_Send()
*
*Description : 串口A2发送一个字节数据
*Arguments   : 发送的字节数据
*Returns     : none
*Notes       : none
*******************************************************************************
*/

u8 data_to_send[50]={0};
void Uart_A2_Send(unsigned char length)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		MAP_UART_transmitData(EUSCI_A2_MODULE, data_to_send[i]);
		while(MAP_UART_queryStatusFlags(EUSCI_A2_MODULE, EUSCI_A_UART_BUSY));        //等待发送完成

	}
}
/******************************************************************************
*                          Uart_A1_Send()
*
*Description : 串口A1发送一个字节数据
*Arguments   : 发送的字节数据
*Returns     : none
*Notes       : none
*******************************************************************************
*/


void Uart_A3_Send(uint8_t TxData)
{
	MAP_UART_transmitData(EUSCI_A3_MODULE, TxData);
	while(MAP_UART_queryStatusFlags(EUSCI_A3_MODULE, EUSCI_A_UART_BUSY));        //等待发送完成
}





/******************************************************************************************************************
*                                               EUSCIA0_IRQHandler()
*
*Description : 串口中断服务函数
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/


void EUSCIA0_IRQHandler(void)
{
	uint8_t  RxData;
	uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_MODULE);   //得到中断标志位
	MAP_UART_clearInterruptFlag(EUSCI_A0_MODULE, status);                    //清除标志位

	if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)                              //判断是否为接受中断
	{
		RxData = MAP_UART_receiveData(EUSCI_A0_MODULE);                      //串口A1接受数据
		MAP_UART_transmitData(EUSCI_A0_MODULE, RxData);
	}
}


/******************************************************************************************************************
*                                               EUSCIA1_IRQHandler()
*
*Description : 串口中断服务函数
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void EUSCIA1_IRQHandler(void)
{
	uint8_t  RxData;
	uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A1_MODULE);   //得到中断标志位
	MAP_UART_clearInterruptFlag(EUSCI_A1_MODULE, status);                    //清除标志位

	if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)                              //判断是否为接受中断
	{
		RxData = MAP_UART_receiveData(EUSCI_A1_MODULE);                      //串口A1接受数据
		MAP_UART_transmitData(EUSCI_A1_MODULE, RxData);
	}
}


/******************************************************************************************************************
*                                               EUSCIA2_IRQHandler()
*
*Description : 串口中断服务函数
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
int TEST_X=0;
int TEST_Y=0;
void EUSCIA2_IRQHandler(void)
{
	uint8_t  RxData;
	static uint8_t flag_uart=0;
	
	
	uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_MODULE);   //得到中断标志位
	MAP_UART_clearInterruptFlag(EUSCI_A2_MODULE, status);                    //清除标志位

	if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)                              //判断是否为接受中断
	{ 
		LED0=!LED0;		  
		RxData = MAP_UART_receiveData(EUSCI_A2_MODULE);                      //串口A1接受数据
		if(RxData==0XAA||flag_uart)
		{
			USART_RX_BUF[flag_uart]=RxData;	
			flag_ov=USART_RX_BUF[4];
			TEST_X=USART_RX_BUF[1];
			TEST_Y=USART_RX_BUF[2]*256+USART_RX_BUF[3];//摄像头中的Y
			flag_uart++;			
		}
	}	
	flag_uart=(flag_uart==5) ? 0 : flag_uart;
}



/******************************************************************************************************************
*                                               fputc()
*
*Description : 重新定义print函数
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式  

void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 
#ifdef USE_EUSCI_A0_MODULE	
	 MAP_UART_transmitData(EUSCI_A0_MODULE, (uint8_t)ch);
#endif
	
#ifdef USE_EUSCI_A1_MODULE	
	 MAP_UART_transmitData(EUSCI_A1_MODULE, (uint8_t)ch);
#endif
	
#ifdef USE_EUSCI_A2_MODULE	
	 MAP_UART_transmitData(EUSCI_A2_MODULE, (uint8_t)ch);
#endif
	
#ifdef USE_EUSCI_A3_MODULE	
	 MAP_UART_transmitData(EUSCI_A3_MODULE, (uint8_t)ch);
#endif
	
	 return ch;			
}
#endif


/*
****************************************************************************************************************************
***************************************匿名2.0数据传输协议******************************************************************
****************************************************************************************************************************
*/
void usart3_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//最多28字节数据 
	send_buf[len+3]=0;	//校验数置零
	send_buf[0]=0X88;	//帧头
	send_buf[1]=fun;	//功能字
	send_buf[2]=len;	//数据长度
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//复制数据
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//计算校验和	
	for(i=0;i<len+4;i++)Uart_A3_Send(send_buf[i]);	//发送数据到串口3
}


void niming_send_data(short u_a,short u_b,short u_c,short u_d,short u_e,short u_f,short u_g,short u_h,short u_i,short u_j)//short型变量
{
	u8 tbuf[28]; 
	tbuf[0]=(u_a>>8)&0XFF;
	tbuf[1]=u_a&0XFF;
	tbuf[2]=(u_b>>8)&0XFF;
	tbuf[3]=u_b&0XFF;
	tbuf[4]=(u_c>>8)&0XFF;
	tbuf[5]=u_c&0XFF; 
	tbuf[6]=(u_d>>8)&0XFF;
	tbuf[7]=u_d&0XFF;
	tbuf[8]=(u_e>>8)&0XFF;
	tbuf[9]=u_e&0XFF;
	tbuf[10]=(u_f>>8)&0XFF;
	tbuf[11]=u_f&0XFF;
	tbuf[12]=(u_g>>8)&0XFF;
	tbuf[13]=u_g&0XFF;
	tbuf[14]=(u_h>>8)&0XFF;
	tbuf[15]=u_h&0XFF;
	tbuf[16]=(u_i>>8)&0XFF;
	tbuf[17]=u_i&0XFF;
	tbuf[18]=(u_j>>8)&0XFF;
	tbuf[19]=u_j&0XFF;
	usart3_niming_report(0XA1,tbuf,28);//自定义帧,0XA1
}	

void FDC2214_send_data(uint32_t ch0,uint32_t ch1,uint32_t ch2,uint32_t ch3)//整型变量
{
	u8 tbuf[16]; 
	tbuf[0]=(ch0>>24)&0XFF;
	tbuf[1]=(ch0>>16)&0XFF;
	tbuf[2]=(ch0>>8)&0XFF;
	tbuf[3]=ch0&0XFF;
	tbuf[4]=(ch1>>24)&0XFF;
	tbuf[5]=(ch1>>16)&0XFF;
	tbuf[6]=(ch1>>8)&0XFF;
	tbuf[7]=ch1&0XFF;
	tbuf[8]=(ch2>>24)&0XFF;
	tbuf[9]=(ch2>>16)&0XFF;
	tbuf[10]=(ch2>>8)&0XFF;
	tbuf[11]=ch2&0XFF;
	tbuf[12]=(ch3>>24)&0XFF;
	tbuf[13]=(ch3>>16)&0XFF;
	tbuf[14]=(ch3>>8)&0XFF;
	tbuf[15]=ch3&0XFF;	
	usart3_niming_report(0XA1,tbuf,16);//自定义帧,0XA1
}

/*
****************************************************************************************************************************
*****************************************匿名4.0数据传输协议****************************************************************
****************************************************************************************************************************
*/
//u8 data_to_send[50]={0};
//void Usart2_Send_User(uint32_t d1,uint32_t d2,uint32_t d3,uint32_t d4,uint32_t d5,uint32_t d6,uint32_t d7,uint32_t d8)
//{
//	u8 _cnt=0;
//	u8 sum = 0;
//	u8 i;

//	data_to_send[_cnt++]=0xAA;
//	data_to_send[_cnt++]=0xAA;
//	data_to_send[_cnt++]=0xF1;
//	data_to_send[_cnt++]=0;
//	
//	data_to_send[_cnt++]=BYTE3(d1);
//	data_to_send[_cnt++]=BYTE2(d1);
//	data_to_send[_cnt++]=BYTE1(d1);
//	data_to_send[_cnt++]=BYTE0(d1);
//	
//	data_to_send[_cnt++]=BYTE3(d2);
//	data_to_send[_cnt++]=BYTE2(d2);
//	data_to_send[_cnt++]=BYTE1(d2);
//	data_to_send[_cnt++]=BYTE0(d2);
//	
//	data_to_send[_cnt++]=BYTE3(d3);
//	data_to_send[_cnt++]=BYTE2(d3);
//	data_to_send[_cnt++]=BYTE1(d3);
//	data_to_send[_cnt++]=BYTE0(d3);
//	
//	data_to_send[_cnt++]=BYTE3(d4);
//	data_to_send[_cnt++]=BYTE2(d4);
//	data_to_send[_cnt++]=BYTE1(d4);
//	data_to_send[_cnt++]=BYTE0(d4);
//	
//	data_to_send[_cnt++]=BYTE3(d5);
//	data_to_send[_cnt++]=BYTE2(d5);
//	data_to_send[_cnt++]=BYTE1(d5);
//	data_to_send[_cnt++]=BYTE0(d5);
//	
//	data_to_send[_cnt++]=BYTE3(d6);
//	data_to_send[_cnt++]=BYTE2(d6);
//	data_to_send[_cnt++]=BYTE1(d6);
//	data_to_send[_cnt++]=BYTE0(d6);
//	
//	data_to_send[_cnt++]=BYTE3(d7);
//	data_to_send[_cnt++]=BYTE2(d7);
//	data_to_send[_cnt++]=BYTE1(d7);
//	data_to_send[_cnt++]=BYTE0(d7);
//	
//	data_to_send[_cnt++]=BYTE3(d8);
//	data_to_send[_cnt++]=BYTE2(d8);
//	data_to_send[_cnt++]=BYTE1(d8);
//	data_to_send[_cnt++]=BYTE0(d8);
//	
//	data_to_send[3] = _cnt-4;
//	
//	for(i=0;i<_cnt;i++)
//		sum += data_to_send[i];
//	
//	data_to_send[_cnt++]=sum;
//	
//	Usart2_Send(_cnt);
//}



//void Usart2_Send(unsigned char length)
//{
//	unsigned char i;
//	for(i=0;i<length;i++)
//	{
//		
//		Uart_A2_Send( data_to_send[i] );
//	}
//}


#if Niming4
/*
****************************************************************************************************************
*****************************************匿名4.34数据传输协议****************************************************
****************************************************************************************************************
*/



/*
***************************************************************************************************************
*   void Usart_Send_float(float d1,float d2,float d3,float d4)
*
*Description : 发送8个 int型 （32位）给匿名上位机
*Arguments   : none
*Returns     : none
*Notes       : 数据最多32位(其实只有28位)
***************************************************************************************************************
*/
void Usart_Send_float(float d1,float d2,float d3,float d4)
{
	u8 _cnt=0;
	u8 sum = 0;
	u8 i;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF1;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=BYTE3(d1);
	data_to_send[_cnt++]=BYTE2(d1);
	data_to_send[_cnt++]=BYTE1(d1);
	data_to_send[_cnt++]=BYTE0(d1);
	
	data_to_send[_cnt++]=BYTE3(d2);
	data_to_send[_cnt++]=BYTE2(d2);
	data_to_send[_cnt++]=BYTE1(d2);
	data_to_send[_cnt++]=BYTE0(d2);
	
	data_to_send[_cnt++]=BYTE3(d3);
	data_to_send[_cnt++]=BYTE2(d3);
	data_to_send[_cnt++]=BYTE1(d3);
	data_to_send[_cnt++]=BYTE0(d3);
	
	data_to_send[_cnt++]=BYTE3(d4);
	data_to_send[_cnt++]=BYTE2(d4);
	data_to_send[_cnt++]=BYTE1(d4);
	data_to_send[_cnt++]=BYTE0(d4);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Uart_A2_Send(_cnt);
}




/*
***************************************************************************************************************
*    void Usart_Send_User(s32 d1,s32 d2,s32 d3,s32 d4,s32 d5,s32 d6,s32 d7,s32 d8)
*
*Description : 发送8个 int型 （32位）给匿名上位机
*Arguments   : none
*Returns     : none
*Notes       : 数据最多32位(其实只有28位)
***************************************************************************************************************
*/
void Usart_Send_User(s32 d1,s32 d2,s32 d3,s32 d4,s32 d5,s32 d6,s32 d7,s32 d8)
{
	u8 _cnt=0;
	u8 sum = 0;
	u8 i;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF1;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=BYTE3(d1);
	data_to_send[_cnt++]=BYTE2(d1);
	data_to_send[_cnt++]=BYTE1(d1);
	data_to_send[_cnt++]=BYTE0(d1);
	
	data_to_send[_cnt++]=BYTE3(d2);
	data_to_send[_cnt++]=BYTE2(d2);
	data_to_send[_cnt++]=BYTE1(d2);
	data_to_send[_cnt++]=BYTE0(d2);
	
	data_to_send[_cnt++]=BYTE3(d3);
	data_to_send[_cnt++]=BYTE2(d3);
	data_to_send[_cnt++]=BYTE1(d3);
	data_to_send[_cnt++]=BYTE0(d3);
	
	data_to_send[_cnt++]=BYTE3(d4);
	data_to_send[_cnt++]=BYTE2(d4);
	data_to_send[_cnt++]=BYTE1(d4);
	data_to_send[_cnt++]=BYTE0(d4);
	
	data_to_send[_cnt++]=BYTE3(d5);
	data_to_send[_cnt++]=BYTE2(d5);
	data_to_send[_cnt++]=BYTE1(d5);
	data_to_send[_cnt++]=BYTE0(d5);
	
	data_to_send[_cnt++]=BYTE3(d6);
	data_to_send[_cnt++]=BYTE2(d6);
	data_to_send[_cnt++]=BYTE1(d6);
	data_to_send[_cnt++]=BYTE0(d6);
	
	data_to_send[_cnt++]=BYTE3(d7);
	data_to_send[_cnt++]=BYTE2(d7);
	data_to_send[_cnt++]=BYTE1(d7);
	data_to_send[_cnt++]=BYTE0(d7);
	
	data_to_send[_cnt++]=BYTE3(d8);
	data_to_send[_cnt++]=BYTE2(d8);
	data_to_send[_cnt++]=BYTE1(d8);
	data_to_send[_cnt++]=BYTE0(d8);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Uart_A2_Send(_cnt);
}
#endif


void UsartA2_TEST(void)
{
	u8 key;
	int i;
	OLED_Clear();
	Usart_init();
	Uart_A2_Init();
	while(1)
	{
		key=KEY_Scan(0);
		OLED_ShowIntNum(16,16,TEST_X,3,12);
		OLED_ShowIntNum(16,32,TEST_Y,3,12);
		OLED_Refresh_Gram();
//		Uart_A2_Send(50);
//		Delay_ms(100);
		if(key==KEY5_PRES)
		 return;
	}
}


