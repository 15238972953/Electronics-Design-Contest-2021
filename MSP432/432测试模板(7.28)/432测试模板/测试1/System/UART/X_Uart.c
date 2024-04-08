/*
******************************************************************************************************************
*                            MuChun Electron
*                        ZhenJiang,Jiangsu,China
*              (c) Copyright 2016,MuChun Electron,Zhenjiang,China
*                          All Rights Reserved
*
*
*
*Filename      :Uart.c
*Programmer(s) :Song Muchun
*Description   :Uart Driver correlation function
******************************************************************************************************************
*/
/* $ PAGE*/
#include "X_Uart.h"
#include "stdio.h"         //print函数C文件库

#define BYTE0(dwTemp)       (*( char *)(&dwTemp))     //字分离四字节
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))//字分离四字节
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))//字分离四字节
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))//字分离四字节
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : 变量声明
*Notes       : none
******************************************************************************************************************
*/
//串口参数设置，波特率设置参考以下地址：
//http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
const eUSCI_UART_Config Uart1Config =      //串口48MHz,波特率115200
{
	EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //选择时钟
	26 ,                                     // BRDIV
	1,                                       // UCxBRF
	0,                                       // UCxBRS = 0
	EUSCI_A_UART_NO_PARITY,                  // 无奇偶校验位
	EUSCI_A_UART_LSB_FIRST,                  // 一位起始位
	EUSCI_A_UART_ONE_STOP_BIT,               // 一位停止位
	EUSCI_A_UART_MODE,                       // UART模式
	EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};
/******************************************************************************************************************
*                                               Uart1_Init()
*
*Description : 串口1初始化
*Arguments   : none
*Returns     : none
*Notes       : P1.2 P1.3
*******************************************************************************************************************
*/
void Uart1_Init(void)
{
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);//设置DCO时钟必须有，否则串口无法使用 48Mhz
	/* Configuring UART Module */
	MAP_UART_initModule(EUSCI_A0_MODULE, &Uart1Config);
	/* Enable UART module */
	MAP_UART_enableModule(EUSCI_A0_MODULE);                                      //启动串口
	MAP_UART_enableInterrupt(EUSCI_A0_MODULE, EUSCI_A_UART_RECEIVE_INTERRUPT);   //启动串口接受中断
	MAP_Interrupt_enableInterrupt(INT_EUSCIA0);                                  //启动串口中断
	// MAP_Interrupt_enableSleepOnIsrExit();
	MAP_Interrupt_enableMaster();                                                //开总中断  
}
/******************************************************************************
*                          Uart1_Send()
*
*Description : 串口1发送一个字节数据
*Arguments   : 发送的字节数据
*Returns     : none
*Notes       : none
*******************************************************************************
*/
void Uart1_Send(uint8_t TxData)
{
	MAP_UART_transmitData(EUSCI_A0_MODULE, TxData);
	while(MAP_UART_queryStatusFlags(EUSCI_A0_MODULE,EUSCI_A_UART_BUSY));        //等待发送完成
}
/******************************************************************************
*                          Upper_Computer()
*
*Description : 匿名上微机通信查看数据波形
*Arguments   : 上位机查看波形数据参数,data1,data2,data3,data4
*Returns     : none
*Notes       : none
*******************************************************************************
*/
void Upper_Computer(float data1,float data2,float data3,float data4)
{
	uint8_t Send_DATA[21];         //发送缓冲数据	
  uint8_t i,sum;
	Send_DATA[0]  = 0xAA;     //帧头
	Send_DATA[1]  = 0xAA;			//帧头
	Send_DATA[2]  = 0xF1;     //功能字 
	Send_DATA[3]  = 16;       //数据长度
	
	Send_DATA[4]  = BYTE3(data1);  
	Send_DATA[5]  = BYTE2(data1);
	Send_DATA[6]  = BYTE1(data1);
	Send_DATA[7]  = BYTE0(data1);
	
	Send_DATA[4]  = BYTE3(data1);  
	Send_DATA[5]  = BYTE2(data1);
	Send_DATA[6]  = BYTE1(data1);
	Send_DATA[7]  = BYTE0(data1);
	
	Send_DATA[8]  = BYTE3(data2);
	Send_DATA[9]  = BYTE2(data2);
	Send_DATA[10] = BYTE1(data2);
	Send_DATA[11] = BYTE0(data2);
	
	Send_DATA[12] = BYTE3(data3);
	Send_DATA[13] = BYTE2(data3);
	Send_DATA[14] = BYTE1(data3);
	Send_DATA[15] = BYTE0(data3);
	
	Send_DATA[16] = BYTE3(data4);
	Send_DATA[17] = BYTE2(data4);
	Send_DATA[18] = BYTE1(data4);
	Send_DATA[19] = BYTE0(data4);
	
	sum = 0;
	for(i = 0;i < 20;i++)
		sum += Send_DATA[i];
	
	Send_DATA[20] = sum;
	for(i = 0;i < 21;i++)  Uart1_Send(Send_DATA[i]);
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
	uint8_t RxData;
	uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_MODULE);   //得到中断标志位
	MAP_UART_clearInterruptFlag(EUSCI_A0_MODULE, status);                    //清除标志位

	if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)                              //判断是否为接受中断
	{
		RxData = MAP_UART_receiveData(EUSCI_A0_MODULE);                        //串口1接受数据
		MAP_UART_transmitData(EUSCI_A0_MODULE, RxData);
	}
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

_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	// if (!BITBAND_PERI(EUSCI_A_CMSIS(EUSCI_A0_MODULE)->rIE.r, UCTXIE_OFS))
     //   while (!BITBAND_PERI(EUSCI_A_CMSIS(EUSCI_A0_MODULE)->rIFG.r, UCTXIFG_OFS));
   //while(!(UCA0IFG&0X01));    
	// UCA0TXBUF=(uint8_t)ch;
	 MAP_UART_transmitData(EUSCI_A0_MODULE, (uint8_t)ch);
	 return ch;			
}
#endif

