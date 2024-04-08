/*
******************************************************************************************************************
*Filename      :usart3_dma.h
*Programmer(s) :chu
*Description   :Design for usart3_dma

							 USART3_RX---PD9
							 USART3_TX---PD8
******************************************************************************************************************
*/
#ifndef __USART3_DMA_H
#define __USART3_DMA_H	 
#include "sys.h"


//使用USART3时开启，不用可以注释
#define U3_DATA_LEN  60
#define USART3_REC_LEN  	80  	//定义最大接收字节数 200

extern u8  USART3_RX_BUF[USART3_REC_LEN];		//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART3_RX_STA;  
extern u8 connect_flag;//连接标志
extern u8 rec_data_u3[U3_DATA_LEN];   // 接收数据
extern u8 send_data_u3[U3_DATA_LEN];   
/*
******************************************************************************************************************
*                                                 FUNCTION PROTOTYPES
*                                                   串口3用函数
******************************************************************************************************************
*/
void USART3_Init(u32 bound);
extern void USART3_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);//UASRT DMA发送设置
extern void DMA1_S1_Reset(void);//DMA1_Stream1 接收重置	
void openmv(u8 a);
void uart_init(u32 bound);
void Mea_dis(void);
void Read_LaserDis(unsigned char ID, unsigned int *Data);  
void Set_LaserDis(unsigned char ID, unsigned char Fun,unsigned char Par);

#endif
