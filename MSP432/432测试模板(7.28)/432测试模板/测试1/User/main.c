/*************************************************************
//////////////////////////////////////////////////////////////

  *
  * @file    main.c
  * @author  Xsq IN LAB416
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   LED\FLASH					
  *													
  *************************************
  
//////////////////////////////////////////////////////////////
*************************************************************/

/* $ PAGE*/
#include "sys.h"
#include "include.h"
#include "led.h"
#include "X_Uart.h"
#include "delay.h"
#include "oled.h"
#include "key.h"
#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "menu.h"
#include "encoder.h"
#include "motor.h"
#include "Ultrasonic.h"
/*************************************************************
//////////////////////////////////////////////////////////////

  * @brief   主函数
  * @param   无
  *	@arg     无
  * @retval  无
	
//////////////////////////////////////////////////////////////
*************************************************************/

int main(void)
{

	System_Init(); 	//系统初始化
	LED_Init();
	Key_Init();
	Delay_Init();					//延时初始化
  OLED_Init();					//OLED初始化	 
//	//menu_main();
//	Motor_Init();
	Ultrasonic_Init();
	while(1)
	{
//OLED_ShowIntNum(64,48,111,4,12);
//		
//		OLED_Refresh_Gram();
Ultrasonic_Get_Distance();

		
	}
}














