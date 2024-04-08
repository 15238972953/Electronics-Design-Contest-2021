/*
******************************************************************************
*Filename      :oled.c
*Programmer(s) :416GZJ
*Description   :2020???
******************************************************************************
*/

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "sys.h"
#include "key.h"
#include "delay.h"
//void OLED_WR_Byte(u8 dat,u8 cmd);	    
//void OLED_Display_On(void);//??OLED??  
//void OLED_Display_Off(void);//??OLED??  
//void OLED_Refresh_Gram(void);//?????OLED	(?????????????,????,?????????????)	   
//							   		    
//void OLED_Init(void);//OLED?????
//void OLED_Clear(void);//????
//void OLED_DrawPoint(u8 x,u8 y,u8 t);//????
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//??
//void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//????
//void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//????
//void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size);//???????
//void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size);//?????????
//void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//????? 
//void OLED_ShowCHinese(u8 x,u8 y,u8 no);//????

//OLED???
//??????.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
u8 OLED_GRAM[128][8];	 

/*
********************************************************************************************************************
*                  void OLED_Refresh_Gram(void)
*
*Description : ?????OLED
               ?????????????,????,?????????????
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte(0xb0+i,OLED_CMD);//?????(0~7)
		OLED_WR_Byte(0x00,OLED_CMD);//??????—????
		OLED_WR_Byte(0x10,OLED_CMD);//??????—????   
		for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}

/*
********************************************************************************************************************
*                  void OLED_WR_Byte(u8 dat,u8 cmd)
*
*Description : ?SSD1306???????
*Arguments   : dat  ??????/??    
               cmd  ??/???? 0,????;1,????;
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	OLED_DC=cmd; //??? 
	OLED_CS=0;		  
	for(i=0;i<8;i++)
	{			  
		OLED_D0=0;
		if(dat&0x80)OLED_D1=1;
		else OLED_D1=0;
		OLED_D0=1;
		dat<<=1;   
	}				 
	OLED_CS=1;		  
	OLED_DC=1;   	  
} 

/*
********************************************************************************************************************
*                  void OLED_Display_On(void)
*
*Description : ??OLED??    
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC??
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/*
********************************************************************************************************************
*                  void OLED_Display_Off(void)
*
*Description    :??OLED??    
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC??
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   	

/*
********************************************************************************************************************
*                  void OLED_Clear(void)  
*
*Description    :????,???,????????!??????!!!	  
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//????
}

/*
********************************************************************************************************************
*                  void OLED_DrawPoint(u8 x,u8 y,u8 t) 
*
*Description    :????
*Arguments   : x:0~127    y:0~63    t:1 ??,0  ??	
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/	   
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;							//?????.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
/*
********************************************************************************************************************
*                  void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
*
*Description    :????
*Arguments   : x1,y1,x2,y2 ?????????  
                           ??x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63   
                           dot:0,??;1,??	  
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/	   
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//????
}

/*
********************************************************************************************************************
*                  void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
*
*Description    :???????????
*Arguments   : x:0~127   y:0~63
                           mode:0,????;1,????				 
                           size:???? 12/16/24
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/	   
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);//???????????????????
	chr=chr-' ';//???????		 
    for(t=0;t<csize;t++)
    {   
		if(size==12)temp=asc2_1206[chr][t];//??1206??
		else if(size==16)temp=asc2_1608[chr][t];//??1608??
		else if(size==24)temp=asc2_2412[chr][t];//??2412??
		else return;//?????
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }  	
}

/*
********************************************************************************************************************
*                  u32 mypow(u8 m,u8 n)
*
*Description    :m^n??
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/	  
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result; 
}		

/*
********************************************************************************************************************
*                  void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
*
*Description    :?????????
*Arguments   : x,y :????   x:0~127  y:0~63	
                           len :?????   size:????
                           mode:??	0,????;1,????
                           num:??(0~4294967295);	 	
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1;  
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
//	OLED_Refresh_Gram();//????
} 

/*
********************************************************************************************************************
*                  void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size)
*
*Description    :?????????????
*Arguments   : x,y :????   x:0~127  y:0~63	
								len :?????   
								size:????
								num:??(-4294967296~4294967295);	 	
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void OLED_ShowIntNum(u8 x,u8 y,int32_t num,u8 len,u8 size)
{
	if(num<0)
	{
		OLED_ShowString(x,y,(void *)"-",size);
		OLED_ShowNum(x+5,y,-num,len,size);
	}
	else
	{
		OLED_ShowString(x,y,(void *)" ",size);
		OLED_ShowNum(x+5,y,num,len,size);
	}
//	OLED_Refresh_Gram();//????
}


/*
********************************************************************************************************************
*                  void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size)
*
*Description    :?????????????? ????3????
*Arguments   : x,y :????   x:0~127  y:0~63	
							 lenf :???????  
							 lenb :???????
							 size:????
							 num:??;	 	
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void OLED_Show3FNum(u8 x,u8 y,float num,u8 lenf,u8 lenb,u8 size)
{
	u8 front=0,back=0,dot=0;
	
	front=7+x;
	dot=front+(size/2)*lenf+1;
	back=dot+(size/2);
	
	if(num<0)
	{
		OLED_ShowString(x,y,(void *)"-",size);
		num = -num*1000;
	}
	else
	{
		OLED_ShowString(x,y,(void *)" ",size);
		num = num*1000;
	}
	
	OLED_ShowNum(front,y,num/1000,lenf,size);
	
	OLED_ShowString(dot,y,(void *)".",size);
		switch (lenb)
	{
		case 1: OLED_ShowNum(back,y,(int)num/100 %10,lenb,size); break;
		
		case 2: 
			{
				if(((int)num/10%100)<10)
				{
					OLED_ShowNum(dot+(size/2),y,0,1,size); 
					OLED_ShowNum(dot+2*(size/2),y,(int)num/10%100,lenb-1,size); 
				}
				else
				OLED_ShowNum(back,y,(int)num/10 %100,lenb,size); 
				break;
			}
		
		case 3: 
			{
				if(((int)num%1000)<10)
				{
					OLED_ShowNum(dot+(size/2),y,0,1,size);
					OLED_ShowNum(dot+2*(size/2),y,0,1,size);   
					OLED_ShowNum(dot+3*(size/2),y,(int)num%1000,lenb-2,size); 
				}
				else if(((int)num%1000)<100)
				{
					OLED_ShowNum(dot+(size/2),y,0,1,size);
					OLED_ShowNum(dot+2*(size/2),y,(int)num%1000,lenb-1,size); 
				}
				else 
					OLED_ShowNum(back,y,(int)num%1000,lenb,size); 	            
				break;
		  }
	}
//	OLED_Refresh_Gram();//????
}
/*
********************************************************************************************************************
*                  void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size)
*
*Description    :??????????
*Arguments   :   x,y :????   x:0~127  y:0~63	
                            *p:???????  size:????
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/		
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size)
{	
    while((*p<='~')&&(*p>=' '))//?????????!
    {       
        if(x>(128-(size/2))){x=0;y+=size;}
        if(y>(64-size)){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,size,1);	 
        x+=size/2;
        p++;
    }  
//	OLED_Refresh_Gram();//????		
}	

/*
********************************************************************************************************************
*                  void OLED_ShowCHinese(u8 x,u8 y,u8 no)
*
*Description    :?????,?????? 
*Arguments   :  x,y:?????  no:??????
                            fnum:????(??????????)   
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/		
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{     
	u8 temp,t,t1;
	u16 y0=y;
	u8 *dzk;   
	u8 csize=32;	//16*16?32??,??24*24???72??
	dzk=(u8*)Chinese[no];	//???????????? 
	for(t=0;t<csize;t++)
	{   												   
		temp=dzk[t];//??????                          
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,1);
			else OLED_DrawPoint(x,y,0); 
			temp<<=1;
			y++;
			if((y-y0)==16)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}
//	OLED_Refresh_Gram();//????	
}

/*
********************************************************************************************************************
*                  void OLED_Init(void)
*
*Description    :???OLED	
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/				    
void OLED_Init(void)
{ 	 		 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(OLED_RCC, ENABLE);//????

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??

	GPIO_InitStructure.GPIO_Pin = OLED_D0_PIN|OLED_D1_PIN|OLED_DC_PIN|OLED_CS_PIN;
	GPIO_Init(OLED_PORT, &GPIO_InitStructure);

	OLED_D0=1;
	OLED_D1=1;
	OLED_CS=1;
	OLED_DC=1;
				  
	OLED_WR_Byte(0xAE,OLED_CMD); //????
	OLED_WR_Byte(0xD5,OLED_CMD); //????????,????
	OLED_WR_Byte(0x80,OLED_CMD);   //[3:0],????;[7:4],????
	OLED_WR_Byte(0xA8,OLED_CMD); //??????
	OLED_WR_Byte(0X3F,OLED_CMD); //??0X3F(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD); //??????
	OLED_WR_Byte(0X00,OLED_CMD); //???0

	OLED_WR_Byte(0x40,OLED_CMD); //??????? [5:0],??.
														
	OLED_WR_Byte(0x8D,OLED_CMD); //?????
	OLED_WR_Byte(0x14,OLED_CMD); //bit2,??/??
	OLED_WR_Byte(0x20,OLED_CMD); //????????
	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00,?????;01,?????;10,?????;??10;
	OLED_WR_Byte(0xA1,OLED_CMD); //??????,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD); //??COM????;bit3:0,????;1,????? COM[N-1]->COM0;N:????
	OLED_WR_Byte(0xDA,OLED_CMD); //??COM??????
	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]??
		 
	OLED_WR_Byte(0x81,OLED_CMD); //?????
	OLED_WR_Byte(0xEF,OLED_CMD); //1~255;??0X7F (????,????)
	OLED_WR_Byte(0xD9,OLED_CMD); //???????
	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); //??VCOMH ????
	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4,OLED_CMD); //??????;bit0:1,??;0,??;(??/??)
	OLED_WR_Byte(0xA6,OLED_CMD); //??????;bit0:1,????;0,????	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); //????	 
	OLED_Clear();
}  

//void OLED_TEST(void)
//{
//	OLED_ShowString(12,0,(void *)"Test_4 OLED",12);
//	OLED_Refresh_Gram();
//	
//	while(test_flag)
//	{
//		OLED_ShowString(0,16,(void *)"OLED OK",12);
//		OLED_ShowIntNum(0,32,886688,4,12);
//		OLED_Refresh_Gram();
//	}
//}
 
extern int key;
int task_set=0;
//void Task_set(void)
//{
//key=KEY_Scan(0);	//µÃµ½¼üÖµ
//		if(key)
//		{						   
//			 switch(key)
//			{	
//			  case KEY1_PRES:	
//				OLED_Show3FNum(0,0,1 ,3,3,12);		
//		    OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
//        task_set=1; 				
//				delay_ms(100);	   	
//				break;	
//								
//			 case KEY2_PRES:	
//				OLED_Show3FNum(0,0,2 ,3,3,12);		
//		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
//			 task_set=2; 	
//				delay_ms(100);	   	
//				break;
//						 
//			 case KEY3_PRES:						
//       OLED_Show3FNum(0,0,3 ,3,3,12);		
//		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
//			 task_set=3; 	
//				delay_ms(100);	   				
//			break;
//				
//				case KEY4_PRES:	
//					OLED_Show3FNum(0,0,4 ,3,3,12);		
//		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
//				task_set=4; 	
//				delay_ms(100);	   								
//				break;
//				
//				case KEY5_PRES:	
//					OLED_Show3FNum(0,0,5,3,3,12);		
//		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
//				task_set=5; 	
//				delay_ms(100);	   								
//				break;
//				
//			}
//		}
//}


void Task_set(void)
{
while(1)
{key=KEY_Scan(0);
			   if(key==KEY1_PRES)
				 {OLED_Show3FNum(0,0,1 ,3,3,12);		
		    OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
        task_set=1; 				
				delay_ms(100);
         break;					 
				 }
								
			 if(key==KEY2_PRES)	
			 {OLED_Show3FNum(0,0,2 ,3,3,12);		
		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
			 task_set=2; 	
				delay_ms(100);
 break;					 
			 }
						 
			 if(key==KEY3_PRES)							
       {OLED_Show3FNum(0,0,3 ,3,3,12);		
		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
			 task_set=3; 	
				delay_ms(100);
 break;					 
			 }
				
				if(key==KEY4_PRES)	
				{	OLED_Show3FNum(0,0,4 ,3,3,12);		
		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
				task_set=4; 	
				delay_ms(100);
 break;						
				}
				
				if(key==KEY5_PRES)	
				{		OLED_Show3FNum(0,0,5,3,3,12);		
		   OLED_Refresh_Gram();//¸üÐÂÏÔÊ¾µ½OLED	
				task_set=5; 	
				delay_ms(100);
 break;						
				}
				
			}
		}











