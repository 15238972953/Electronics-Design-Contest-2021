/*
******************************************************************************************************************
*Filename      :usart2_dma.h
*Programmer(s) :chu
*Description   :Design for usart2_dma

							 USART2_RX---PD6
							 USART2_TX---PD5
******************************************************************************************************************
*/
#ifndef __USART2_DMA_H
#define __USART2_DMA_H	 
#include "sys.h"


//使用USART2时开启，不用可以注释
#define U2_DATA_LEN  42

extern u8 rec_data_u2[U2_DATA_LEN];   // 接收数据
extern u8 send_data_u2[42];   // 接收数据

/*
******************************************************************************************************************
*                                                 FUNCTION PROTOTYPES
*                                                   串口2用函数
******************************************************************************************************************
*/
extern void USART2_Init(int Baud);
extern void USART2_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);//UASRT DMA发送设置
extern void DMA1_S5_Reset(void);//DMA1_Stream6 接收重置	
void HMISendb(u8 k);
void HMISends(char *buf1);
void HMISendstart(void);
int zh(char s[]);
#endif
