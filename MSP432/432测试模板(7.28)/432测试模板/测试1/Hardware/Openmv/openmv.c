#include "openmv.h"
#include "Usart.h"
#include "key.h"
#include "oled.h"
#include "led.h"

u16 pos_x=120;
u16 pos_y=160;
u8 flag_ov=0;
void Openmv_TEST(void)
{
	
	u8 key;
	Usart_init();
	Uart_A3_Init();
	OLED_Clear();
	
	while(1)
	{
		key=KEY_Scan(0);
		 OLED_ShowNum(16,16,pos_x,3,12);
	   OLED_ShowNum(16,32,pos_y,3,12);
		OLED_Refresh_Gram();
		if(key==KEY5_PRES)
		 return;
	}
 
}
	
/******************************************************************************************************************
*                                               EUSCIA3_IRQHandler()
*
*Description : 串口中断服务函数
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
//void EUSCIA3_IRQHandler(void)
//{
//	uint8_t  Res;
//	uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A3_MODULE);   //得到中断标志位
//	MAP_UART_clearInterruptFlag(EUSCI_A3_MODULE, status);                    //清除标志位

//	if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)                              //判断是否为接受中断
//	{
////		LED0=!LED0;		
////		memset(USART_RX_BUF,0,sizeof(USART_RX_BUF));//清空数组
//		Res = MAP_UART_receiveData(EUSCI_A3_MODULE);                      //串口A0接受数据
////		MAP_UART_transmitData(EUSCI_A3_MODULE, Res);
//		
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//		{
//			  
//					LED0=!LED0;
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//			{
//				if(Res != 0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else 
//					{
//					USART_RX_STA|=0x8000;							//接收完成了 
//					if(USART_RX_BUF[0]==0xAA&&USART_RX_BUF[1]==0xBB)
//					{
//						LED0=!LED0;
//						pos_x=USART_RX_BUF[2]*256+USART_RX_BUF[3];//摄像头中的X
//						pos_y=USART_RX_BUF[4]*256+USART_RX_BUF[5];//摄像头中的Y
//					}
//					USART_RX_STA=0;
//				}
//			}
//			else //还没收到0X0D
//			{	
//				if(Res == 0x0d)  {LED1=!LED1;USART_RX_STA|=0x4000;}
//				else
//				{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//				}		 
//			}
//		}   		 
//		
//	}
//}

void EUSCIA3_IRQHandler(void)
{
	uint8_t  RxData;
	static uint8_t flag_uart=0;
//	static uint8_t flag=1;
//	static uint8_t sum=0;

	uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A3_MODULE);   //得到中断标志位
	MAP_UART_clearInterruptFlag(EUSCI_A3_MODULE, status);                    //清除标志位
	
	if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)                              //判断是否为接受中断
	{		  
		RxData = MAP_UART_receiveData(EUSCI_A3_MODULE);                      //串口A1接受数据
		if(RxData==0XAA||flag_uart)
		{
			USART_RX_BUF[flag_uart]=RxData;	
			flag_ov=USART_RX_BUF[4];
			pos_x=USART_RX_BUF[1];
			pos_y=USART_RX_BUF[2]*256+USART_RX_BUF[3];//摄像头中的Y
//			sum+=RxData;
//			flag=(flag_uart==3) ? (sum*0x00ff==USART_RX_BUF[flag_uart] ? 1 : 0) : 1;
			flag_uart++;			
		}
	}	
	flag_uart=(flag_uart==5) ? 0 : flag_uart;
}


