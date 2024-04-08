#ifndef _oled_H
#define _oled_H



#include "sys.h"
#include "stdlib.h"	



//OLED模式设置
//0:4线串行SPI模式
//1:并行8080模式
//2:IIC模式
#define OLED_MODE 0


#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64


#if OLED_MODE==0
//OLDE-SPI4线控制管脚定义
#define OLED_CS   PBout(14)		
#define OLED_RST  PFout(4)
#define OLED_DC   PBout(12)
/*
******************************************************************************
*Filename      :oled.h
*Programmer(s) :?????
*Description   :2019??
******************************************************************************
*/

#ifndef __OLED_H
#define __OLED_H			  	 

#include "sys.h"
#include "stdlib.h"	    

extern u8 ErrorWords[10];  						  
//-----------------OLED????------------------------------------------------------- 		
//D0--PE0,D1--PE1,RST--PE2,CS--PE3,DC--PE4

#define OLED_RCC            	RCC_AHB1Periph_GPIOB

#define OLED_D0 	         	PBout(13)  //OLED?D0?
#define OLED_D1	              	PBout(15)  //OLED?D1
#define OLED_DC	              	PBout(12)  //OLED?DC?
#define OLED_CS 	            PBout(14)  //OLED?CS

#define OLED_D0_PIN           	GPIO_Pin_13
#define OLED_D1_PIN           	GPIO_Pin_15
#define OLED_DC_PIN           	GPIO_Pin_12
#define OLED_CS_PIN           	GPIO_Pin_14

#define OLED_PORT          	  	GPIOB

#define OLED_CMD  	          	0		//???
#define OLED_DATA 	          	1		//???

/*
******************************************************************************************************************
*                        OLED??????
******************************************************************************************************************
*/
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);//??OLED??  
void OLED_Display_Off(void);//??OLED??  
void OLED_Refresh_Gram(void);//?????OLED	(?????????????,????,?????????????)	   
							   		    
void OLED_Init(void);//OLED?????
void OLED_Clear(void);//????
void OLED_DrawPoint(u8 x,u8 y,u8 t);//????
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//??
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//????
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//????
void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size);//???????
void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size);//?????????
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//????? 
void OLED_ShowCHinese(u8 x,u8 y,u8 no);//????
void OLED_TEST(void);
void Task_set(void);
void OLED_1(void);
	void OLED_2(void);
		void OLED_3(void);
			void OLED_4(void);
				void OLED_5(void);
					void OLED_6(void);
						void OLED_7(void);
							void OLED_8(void);
#endif  
	 



#define OLED_SCL  PBout(13)
#define OLED_SDA  PBout(15)
#endif


#if OLED_MODE==1
//OLDE-8080总线控制管脚定义
#define OLED_CS   PBout(14)		
#define OLED_RST  PFout(4)
#define OLED_DC   PBout(12)
#define OLED_SCL  PBout(13)
#define OLED_SDA  PBout(15)

#define OLED_DATA_OUT(x) GPIO_Write(GPIOC,x);//输出
#endif


#if OLED_MODE==2
//OLDE-IIC总线控制管脚定义


#endif


 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据		    						  



//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);	   							   		    
void OLED_Init(void);
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size); 
void OLED_ShowFontHZ(u8 x,u8 y,u8 pos,u8 size,u8 mode);
void OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[]);

void OLED_Display_Num(u8 x,u8 y,double Number,u8 N1,u8 N2) ;
uint16_t Power(u8 n);
void OLED_ShowString2(u8 x,u8 y,u8 *chr);
void OLED_ShowChar3(u8 x,u8 y,u8 chr);
void OLED_Showdecimal(u8 x,u8 y,float num,u8 z_len,u8 f_len,u8 size2);

void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size);

void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size);



#endif
