#include "SpiDrive.H"
#include "Delay.h"
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : SPI A1参数初始话
*Notes       : none
******************************************************************************************************************
*/
const eUSCI_SPI_MasterConfig SPI_A1_MasterConfig =
{
	EUSCI_SPI_CLOCKSOURCE_SMCLK,                              // SMCLK Clock Source
	48000000,                                                 // 48MHz
	16000000,                                                 // SPICLK
	EUSCI_A_SPI_MSB_FIRST,                                    // MSB First
	EUSCI_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,    // Phase EUSCI_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT
	EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,                  // HIGH polarity
	EUSCI_A_SPI_3PIN                                          // 3Wire SPI Mode
};
/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : SPI A3参数初始话
*Notes       : none
******************************************************************************************************************
*/
const eUSCI_SPI_MasterConfig SPI_A3_MasterConfig =
{
	EUSCI_SPI_CLOCKSOURCE_SMCLK,                              // SMCLK Clock Source
	48000000,                                                 // 48MHz
	9000000,                                                  // SPICLK
	EUSCI_A_SPI_MSB_FIRST,                                    // MSB First
	EUSCI_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,    // Phase EUSCI_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT
	EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_LOW,                   // LOW polarity
	EUSCI_A_SPI_3PIN                                          // 3Wire SPI Mode
};


/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
*Description : SPI B1参数初始话
*Notes       : none
******************************************************************************************************************
*/
const eUSCI_SPI_MasterConfig SPI_B1_MasterConfig =
{
	EUSCI_SPI_CLOCKSOURCE_SMCLK,                              // SMCLK Clock Source
	48000000,                                                 // 48MHz
	9000000,                                                  // SPICLK
	EUSCI_B_SPI_MSB_FIRST,                                    // MSB First
	EUSCI_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,    // Phase EUSCI_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT
	EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_LOW,                   // LOW polarity
	EUSCI_B_SPI_3PIN                                          // 3Wire SPI Mode
};


/******************************************************************************************************************
*                                               SPI_Drive_Init()
*
*Description : SPI初始化
*Arguments   : 函数指针
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void SPI_Drive_Init(void (*SPI_MOUDLE_Init)(void))
{
	SPI_MOUDLE_Init();
}
/******************************************************************************************************************
*                                               SPI_A1_Init()
*
*Description : SPI A1初始化
*Arguments   : none
*Returns     : none
*Notes       : SPI引脚
*              P2.3|-> Data Out         (UCA1SIMO)
*              P2.2|<- Data In          (UCA1SOMI)
*              P2.1|-> Serial Clock Out (UCA1CLK)
*******************************************************************************************************************
*/
void SPI_A1_Init(void)
{
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
	SPI_initMaster(EUSCI_A1_MODULE, &SPI_A1_MasterConfig);  //初始化SPI A1
	SPI_enableModule(EUSCI_A1_MODULE);                      //使能SPI
}
/******************************************************************************************************************
*                                               SPI_A3_Init()
*
*Description : SPI A3初始化
*Arguments   : none
*Returns     : none
*Notes       : SPI引脚
*              P9.7|-> Data Out         (UCA3SIMO)
*              P9.6|<- Data In          (UCA3SOMI)
*              P9.5|-> Serial Clock Out (UCA3CLK)
*******************************************************************************************************************
*/
void SPI_A3_Init(void)
{
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
	SPI_initMaster(EUSCI_A3_MODULE, &SPI_A3_MasterConfig);  //初始化SPI A3
	SPI_enableModule(EUSCI_A3_MODULE);                      //使能SPI
}

/******************************************************************************************************************
*                                               SPI_A3_Init()
*
*Description : SPI A3初始化
*Arguments   : none
*Returns     : none
*Notes       : SPI引脚
*              P9.7|-> Data Out         (UCA3SIMO)
*              P9.6|<- Data In          (UCA3SOMI)
*              P9.5|-> Serial Clock Out (UCA3CLK)
*******************************************************************************************************************
*/
void SPI_B1_Init(void)
{
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
	SPI_initMaster(EUSCI_B1_MODULE, &SPI_B1_MasterConfig);  //初始化SPI B1
	SPI_enableModule(EUSCI_B1_MODULE);                      //使能SPI
}


/******************************************************************************************************************
*                                               SPI_Rd_Wr_Byte()
*
*Description : SPI读写一个字节
*Arguments   : 发送数据TxData，函数指针SPI_MODULE_Select
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
uint8_t SPI_Rd_Wr_Byte(uint8_t TxData, uint8_t (*SPI_MODULE_Select)(uint8_t))
{
	uint8_t RxData;
	RxData = SPI_MODULE_Select(TxData);
	return RxData;
}
/********************************************************************************************************************
*                                             SPI_A1_ReadWriteByte()
*
*Description : SPI 读写一个字节
*Arguments   : TxData，要写入的字节
*Returns     : 读取到的字节
*Notes       : none
********************************************************************************************************************
*/
uint8_t SPI_A1_ReadWriteByte(uint8_t TxData)
{
	uint8_t retry=0;
	while(true == EUSCI_A_SPI_isBusy (EUSCI_A1_MODULE))                               //等待发送缓存寄存器为空
	{
		retry++;
		if(retry>200)
			return 0;
	}	
	SPI_transmitData(EUSCI_A1_MODULE, TxData);                                         //通过外设SPIx发送一个数据
	//while(SPI_isBusy(EUSCI_A1_MODULE) == EUSCI_SPI_BUSY);//函数好像有错
	retry = 0;
	while(true == EUSCI_A_SPI_isBusy (EUSCI_A1_MODULE))                                //等待发送缓存寄存器为空
	{
		retry++;
		if(retry>200)
			return 0;
	}	  						    
	return SPI_receiveData(EUSCI_A1_MODULE);                                           //返回通过SPIx最近接收的数据					    
}
/********************************************************************************************************************
*                                             SPI_A3_ReadWriteByte()
*
*Description : SPI 读写一个字节
*Arguments   : TxData，要写入的字节
*Returns     : 读取到的字节
*Notes       : none
********************************************************************************************************************
*/
uint8_t SPI_A3_ReadWriteByte(uint8_t TxData)
{
	uint8_t retry=0;
	while(true == EUSCI_A_SPI_isBusy (EUSCI_A3_MODULE))                               //等待发送缓存寄存器为空
	{
		retry++;
		if(retry>200)
			return 0;
	}	
	SPI_transmitData(EUSCI_A3_MODULE, TxData);                                         //通过外设SPIx发送一个数据
	//while(SPI_isBusy(EUSCI_A3_MODULE) == EUSCI_SPI_BUSY);//函数好像有错
	retry = 0;
	while(true == EUSCI_A_SPI_isBusy (EUSCI_A3_MODULE))                                //等待发送缓存寄存器为空
	{
		retry++;
		if(retry>200)
			return 0;
	}	 	
	return SPI_receiveData(EUSCI_A3_MODULE);                                           //返回通过SPIx最近接收的数据					    
}


/********************************************************************************************************************
*                                             SPI_B1_ReadWriteByte()
*
*Description : SPI 读写一个字节
*Arguments   : TxData，要写入的字节
*Returns     : 读取到的字节
*Notes       : none
********************************************************************************************************************
*/
uint8_t SPI_B1_ReadWriteByte(uint8_t TxData)
{
	uint8_t retry=0;
	while(true == EUSCI_B_SPI_isBusy (EUSCI_B1_MODULE))                               //等待发送缓存寄存器为空
	{
		retry++;
		if(retry>200)
			return 0;
	}	
	SPI_transmitData(EUSCI_B1_MODULE, TxData);                                         //通过外设SPIx发送一个数据
	//while(SPI_isBusy(EUSCI_A3_MODULE) == EUSCI_SPI_BUSY);//函数好像有错
	retry = 0;
	while(true == EUSCI_B_SPI_isBusy (EUSCI_B1_MODULE))                                //等待发送缓存寄存器为空
	{
		retry++;
		if(retry>200)
			return 0;
	}	 	
	return SPI_receiveData(EUSCI_B1_MODULE);                                           //返回通过SPIx最近接收的数据					    
}



