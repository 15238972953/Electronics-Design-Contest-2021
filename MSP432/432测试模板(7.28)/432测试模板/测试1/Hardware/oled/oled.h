/*
******************************************************************************
*Filename      :oled.h
*Programmer(s) :Lab 416 In Jiangsu University/Zhu Yaming
*Description   :2018江苏省电子设计竞赛：OLED
******************************************************************************
*/

#ifndef __OLED_H
#define __OLED_H			  	 

#include "sys.h"  
#include "gpio.h"  
#include "include.h"   

//D0--P1.1,D1--P1.3,DC--P1.2,CS--P1.0，RST--复位(P1.4)

#define OLED_CS 	                       P1out(0)			//OLED的CS
#define OLED_CS_PIN                      GPIO_PIN0
#define OLED_CS_PORT                     GPIO_PORT_P1

#define OLED_DC	                         P1out(2)   	//OLED的DC
#define OLED_DC_PIN                      GPIO_PIN2
#define OLED_DC_PORT                     GPIO_PORT_P1

#define OLED_D0 	                       P1out(1)  	  //OLED的D0
#define OLED_D1	                         P1out(3)  	  //OLED的D1
#define OLED_D0_PIN                      GPIO_PIN1
#define OLED_D1_PIN                      GPIO_PIN3
#define OLED_D0_D1_PORT                  GPIO_PORT_P1

#define OLED_RST 	                       P1out(4)			//OLED的CS
#define OLED_RST_PIN                     GPIO_PIN4
#define OLED_RST_PORT                    GPIO_PORT_P1

#define OLED_CMD  	                       0  				//写命令
#define OLED_DATA 	                       1   				//写数据


void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);//开启OLED显示  
void OLED_Display_Off(void);//关闭OLED显示  
void OLED_Refresh_Gram(void);//更新显存到OLED		   
							   		    
void OLED_Init(void);//OLED初始化函数
void OLED_Clear(void);//清屏函数
void OLED_DrawPoint(u8 x,u8 y,u8 t);//画点函数
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//填充
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//显示字符
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//显示数字
void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size);//显示有符号数字
void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size);//显示有符号浮点数字
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//显示字符串 
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
//void fun0(void);
//void fun1(void);
//void fun2(void);
//void fun3(void);
//void fun4(void);
//void fun4_fill(void);
//void fun5(void);
//void fun5_fill(void);
//void fun6(void);
//void fun6_fill(void);
//void fun7(void);
//void fun7_fill(void);


#endif  
	 

