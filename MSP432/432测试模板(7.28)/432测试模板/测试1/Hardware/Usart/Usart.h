#ifndef _Uart_H
#define _Uart_H

#include "sys.h"
#include "Delay.h"

#define USART0_EN 			0
#define USART1_EN 			0
#define USART2_EN 			1
#define USART3_EN 			1


#define USART2_DMA_EN 		0


#define Niming2 			0
#define Niming4 			1
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : none
*Notes       : none
******************************************************************************************************************
*/
#define UART_SELECT 2                //选择模块1作为串口输出

#if UART_SELECT == 0
#define USE_EUSCI_A0_MODULE           //使用EUSCI_A0_MODULE打印串口输出
#endif

#if UART_SELECT == 1
#define USE_EUSCI_A1_MODULE           //使用EUSCI_A1_MODULE打印串口输出
#endif

#if UART_SELECT == 2
#define USE_EUSCI_A2_MODULE           //使用EUSCI_A2_MODULE打印串口输出
#endif

#if UART_SELECT == 3
#define USE_EUSCI_A3_MODULE           //使用EUSCI_A3_MODULE打印串口输出
#endif






#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 				1			//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         				//接收状态标记	
/*
******************************************************************************************************************
*                  FUNCTION PROTOTYPES
******************************************************************************************************************
*/
void Usart_init(void);
void Uart_A0_Init(void);               //串口A0初始化
void Uart_A1_Init(void);               //串口A1初始化
void Uart_A2_Init(void);               //串口A2初始化
void Uart_A3_Init(void);               //串口A3初始化
void Uart_A0_Send(uint8_t TxData);     //串口A0发送一个字节
void Uart_A1_Send(uint8_t TxData);     //串口A1发送一个字节
void Uart_A2_Send(uint8_t TxData);     //串口A2发送一个字节
void Uart_A3_Send(uint8_t TxData);     //串口A3发送一个字节
void Upper_Computer(float data1,float data2,float data3,float data4);
void usart3_niming_report(u8 fun,u8*data,u8 len);
void niming_send_data(short u_a,short u_b,short u_c,short u_d,short u_e,short u_f,short u_g,short u_h,short u_i,short u_j);//short型变量
void FDC2214_send_data(uint32_t ch0,uint32_t ch1,uint32_t ch2,uint32_t ch3);

void Usart_Send(unsigned char length);
void Usart_Send_User(s32 d1,s32 d2,s32 d3,s32 d4,s32 d5,s32 d6,s32 d7,s32 d8);
void Usart_Send_float(float d1,float d2,float d3,float d4);
void UsartA2_TEST(void);
#endif

