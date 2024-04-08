/*
******************************************************************************
*Filename      :uart4_dma.h
*Programmer(s) :国赛秃击队
*Description   :2019国赛
******************************************************************************
*/

#ifndef __USART4_DMA_H
#define __USART4_DMA_H	 
#include "sys.h"


//使用USART3时开启，不用可以注释
#define U4_DATA_LEN  60
#define USART4_REC_LEN  	80  	//定义最大接收字节数 200

extern u8  USART4_RX_BUF[USART4_REC_LEN];		//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART4_RX_STA;  
extern u8 connect_flag;//连接标志
extern u8 rec_data_u4[U4_DATA_LEN];   // 接收数据
extern u8 send_data_u4[U4_DATA_LEN];   
/*
******************************************************************************************************************
*                                                 FUNCTION PROTOTYPES
*                                                   串口3用函数
******************************************************************************************************************
*/
extern void USART4_Init(int Baud);
extern void USART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize);//UASRT DMA发送设置
extern void DMA1_S1_Reset(void);//DMA1_Stream1 接收重置	
void openmv(u8 a);
void USART3_send_byte(uint8_t byte);
void USART3_Send_bytes(uint8_t *Buffer, uint8_t Length);

void DMA1_Stream4_IRQHandler(void);
void DMA1_S2_Reset(void);
void Float2Byte(float *target,unsigned char *buf,unsigned char beg);
void DataScope_Get_Channel_Data(float Data,unsigned char Channel);
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);

void USART4_send_byte(uint8_t byte);
void USART4_Send_bytes(uint8_t *Buffer, uint8_t Length);
void USART4_Send(uint8_t *Buffer, uint8_t Length);

void send_com(u8 data);
	void Read_LaserDis(unsigned char ID, unsigned int *Data) ;

#endif
