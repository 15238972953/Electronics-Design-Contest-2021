#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2011/6/14
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX 			1

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬��
#define USART2_MAX_RECV_LEN		400				//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		400				//����ͻ����ֽ���
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void uart_init3(u32 bound);
void uart_init2(u32 bound);
void xiezi(void);
void color_shibie(void);
void HMISends(char *buf1);
void HMISendb(u8 k);		
void HMISendstart(void);
void uart_oled_show(void);

unsigned char DataScope_Data_Generate(unsigned char Channel_Number);
void DataScope_Get_Channel_Data(float Data,unsigned char Channel);
void Float2Byte(float *target,unsigned char *buf,unsigned char beg);

extern u8 connect_flag;//���ӱ�־


void USART2_send_byte(uint8_t byte);
void USART2_Send_bytes(uint8_t *Buffer, uint8_t Length);
void USART2_Send(uint8_t *Buffer, uint8_t Length);
void send_com(u8 data);
void Mea_dis(void);

#endif


