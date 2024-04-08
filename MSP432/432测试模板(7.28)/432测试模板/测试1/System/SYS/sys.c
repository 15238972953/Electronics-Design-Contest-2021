/*************************************************************
//////////////////////////////////////////////////////////////

  *
  * @file    sys.c
  * @author  Xsq IN LAB416
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   sys init				
  *													
  *************************************
  
//////////////////////////////////////////////////////////////
*************************************************************/
/* $ PAGE*/
#include "sys.h"

/*************************************************************
//////////////////////////////////////////////////////////////

  * @brief   系统初始化，包括对时钟和开门狗的设置
  * @param   无
  *	@arg     无
  * @retval  无
	
//////////////////////////////////////////////////////////////
*************************************************************/
void System_Init(void)
{
	WDT_A_holdTimer();                                  
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
	CS_setExternalClockSourceFrequency(32768, CS_48MHZ);
	PCM_setCoreVoltageLevel(PCM_VCORE1);                 
  FlashCtl_setWaitState(FLASH_BANK0, 2);               
  FlashCtl_setWaitState(FLASH_BANK1, 2);               
  CS_startHFXT(false);
	CS_initClockSignal(CS_ACLK,   CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_BCLK,   CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_SMCLK,  CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); 
  CS_initClockSignal(CS_MCLK,   CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); 
}


