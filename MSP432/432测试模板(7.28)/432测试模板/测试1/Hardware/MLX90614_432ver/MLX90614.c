/*************************************************************
//////////////////////////////////////////////////////////////
*Filename      :MLX90614.c
*Programmer(s) :416GZJ
*Description   :2020ʡ��
//////////////////////////////////////////////////////////////
*************************************************************/
#include "Delay.h"
#include "I2C.h"
#include "MLX90614.h"
#include "key.h"
#include "oled.h"

unsigned char Ddata_L,Ddata_H,PEC;

void MLX90614_Init(void)
{
	I2C_init();
}

unsigned int MLX90614_readd(unsigned char addr)
{  
  I2C_start();                                    //��ʼ 
  I2C_write_byte(addr);                         //д�Ĵ�����ַ 
  if(I2C_check_ack())I2C_write_byte(0x07);     
  else return 90;
  if(I2C_check_ack())I2C_start();                 //�ؿ�ʼ
  else return 91; 
  I2C_write_byte(addr+1);                       //д������ַ������ 
  
  if(I2C_check_ack()) 
    Ddata_L=I2C_read_byte();    //����8λ
  else return 92;  
  sent_ack();                   //����Ӧ��
  
  Ddata_H=I2C_read_byte();      //����8λ
  sent_ack();                   //����Ӧ�� 

  PEC=I2C_read_byte();          //��PEC
  sent_noack();                 //����Ӧ��� 
  
  I2C_stop();                   //���� 

  
  return Ddata_H*256+Ddata_L;   //����
}

void MLX90614_PwmToSMBus(void)
{
  I2C_SCL=0;
  Delay_ms(5); //����1.44ms
  I2C_SCL=1;
}

 /*******************************************************************************
 * ������: Substance_Temp
 * ����: ���㲢���������¶�ֵ
 * Return         : SMBus_ReadMemory(0x00, 0x07)*0.02-273.15
*******************************************************************************/
float Substance_Temp(void)
{   
	MLX90614_PwmToSMBus();
	return MLX90614_readd(MLX90614_ADD)*0.02-273.15;
}

 /*******************************************************************************
 * ������: Human_Temp
 * ����: ���㲢���������¶�ֵ
 * Return         : SMBus_ReadMemory(0x00, 0x07)*0.02-273.15+3
*******************************************************************************/
float Human_Temp(void)
{  
	MLX90614_PwmToSMBus();	
	return MLX90614_readd(MLX90614_ADD)*0.02-273.15+3;
}

void MLX90614_TEST(void)
{
	u8 key;
	float temp_Substance=0;
	float temp_Human=0;
	OLED_Clear();
	MLX90614_Init();
	OLED_ShowString(0,16,"Substance_Temp:",12);
	OLED_ShowString(0,32,"Human_Temp:",12);
	while(1)
	{
		key=KEY_Scan(0);
	  temp_Substance=Substance_Temp();
		temp_Human=Human_Temp();
		OLED_Show3FNum(64,16,temp_Substance,3,3,12);
		OLED_Show3FNum(64,32,temp_Human,3,3,12);
		OLED_Refresh_Gram();
		if(key==KEY5_PRES)
		return;
	}
}
