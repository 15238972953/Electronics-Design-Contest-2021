#ifndef __SYS_H
#define __SYS_H
/*************************************************************
//////////////////////////////////////////////////////////////

  *
  * @file    sys.h
  * @author  Xsq IN LAB416
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   sys init				
  *													
  *************************************
  
//////////////////////////////////////////////////////////////
*************************************************************/
/* $ PAGE*/
#include "driverlib.h"

/*************************************************************
//////////////////////////////////////////////////////////////
         
	@Macro
				 
//////////////////////////////////////////////////////////////
*************************************************************/
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr) (HWREG8(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIO1_OUT_ADDR    (0x40004C02)  //0x40004C02
#define GPIO2_OUT_ADDR    (0x40004C03)  //0x40004C03 
#define GPIO3_OUT_ADDR    (0x40004C22)  //0x40004C22 
#define GPIO4_OUT_ADDR    (0x40004C23)  //0x40004C23 
#define GPIO5_OUT_ADDR    (0x40004C42)  //0x40004C42 
#define GPIO6_OUT_ADDR    (0x40004C43)  //0x40004C43    
#define GPIO7_OUT_ADDR    (0x40004C62)  //0x40004C62   
#define GPIO8_OUT_ADDR    (0x40004C63)  //0x40004C63    
#define GPIO9_OUT_ADDR    (0x40004C82)  //0x40004C82     
#define GPIO10_OUT_ADDR   (0x40004C83) //0x40004C83     

#define GPIO1_IN_ADDR    (0x40004C00)    //0x40004C00 
#define GPIO2_IN_ADDR    (0x40004C01)    //0x40004C01 
#define GPIO3_IN_ADDR    (0x40004C20)    //0x40004C20 
#define GPIO4_IN_ADDR    (0x40004C21) 	 //0x40004C21 
#define GPIO5_IN_ADDR    (0x40004C40)	   //0x40004C40 
#define GPIO6_IN_ADDR    (0x40004C41) 	 //0x40004C41 
#define GPIO7_IN_ADDR    (0x40021810) 	 //0x40021810 
#define GPIO8_IN_ADDR    (0x40021C10) 	 //0x40021C10 
#define GPIO9_IN_ADDR    (0x40004C80) 	 //0x40004C80 
#define GPIO10_IN_ADDR   (0x40004C81) 	 //0x40004C81 
 
//IO口操作,只对单一的IO口!
//确保n的值小于8!
#define P1out(n)   BIT_ADDR(GPIO1_OUT_ADDR,n)  //输出 
#define P1in(n)    BIT_ADDR(GPIO1_IN_ADDR,n)  //输入 

#define P2out(n)   BIT_ADDR(GPIO2_OUT_ADDR,n)  //输出 
#define P2in(n)    BIT_ADDR(GPIO2_IN_ADDR,n)  //输入 

#define P3out(n)   BIT_ADDR(GPIO3_OUT_ADDR,n)  //输出 
#define P3in(n)    BIT_ADDR(GPIO3_IN_ADDR,n)  //输入 

#define P4out(n)   BIT_ADDR(GPIO4_OUT_ADDR,n)  //输出 
#define P4in(n)    BIT_ADDR(GPIO4_IN_ADDR,n)  //输入 

#define P5out(n)   BIT_ADDR(GPIO5_OUT_ADDR,n)  //输出 
#define P5in(n)    BIT_ADDR(GPIO5_IN_ADDR,n)  //输入

#define P6out(n)   BIT_ADDR(GPIO6_OUT_ADDR,n)  //输出 
#define P6in(n)    BIT_ADDR(GPIO6_IN_ADDR,n)  //输入

#define P7out(n)   BIT_ADDR(GPIO7_OUT_ADDR,n)  //输出 
#define P7in(n)    BIT_ADDR(GPIO7_IN_ADDR,n)  //输入

#define P8out(n)   BIT_ADDR(GPIO8_OUT_ADDR,n)  //输出 
#define P8in(n)    BIT_ADDR(GPIO8_IN_ADDR,n)  //输入

#define P9out(n)   BIT_ADDR(GPIO9_OUT_ADDR,n)  //输出 
#define P9in(n)    BIT_ADDR(GPIO9_IN_ADDR,n)  //输入

#define P10out(n)   BIT_ADDR(GPIO10_OUT_ADDR,n)  //输出 
#define P10in(n)    BIT_ADDR(GPIO10_IN_ADDR,n)  //输入

/*************************************************************
//////////////////////////////////////////////////////////////
         
	@Function
				 
//////////////////////////////////////////////////////////////
*************************************************************/
void System_Init(void);



#endif




