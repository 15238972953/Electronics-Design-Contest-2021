/*************************************************************
//////////////////////////////////////////////////////////////
*Filename      :I2C.c
*Programmer(s) :416GZJ
*Description   :2020省赛
//////////////////////////////////////////////////////////////
*************************************************************/
#include "I2C.h"
#include "Delay.h"

void I2C_init()
{
  I2C_SCL=1;
  I2C_SDA=1;
  I2C_SDA_OUT;
  I2C_SCL_OUT;
}

void I2C_start()
{
  I2C_SDA=1;
  I2C_SDA_OUT; 
  Delay_us(15);
  I2C_SCL=1;
  Delay_us(15);
  I2C_SDA=0;
  Delay_us(15);
  I2C_SCL=0;
  Delay_us(15);
}

void I2C_stop()
{  
  I2C_SDA=0;
  I2C_SDA_OUT;  
  Delay_us(15);
  I2C_SCL=1;
  Delay_us(15);
  I2C_SDA=1;
  Delay_us(15);
  I2C_SCL=0;
  Delay_us(15);
}

void I2C_write_byte(unsigned char I2C_byte)
{
	unsigned char temp_data,i;
  I2C_SDA_OUT;
  Delay_us(15);
  temp_data=I2C_byte;
  for(i=0;i<8;i++)
  {
    if(temp_data & 0x80)I2C_SDA=1;else I2C_SDA=0;    
    Delay_us(15);
    
    I2C_SCL=1;
    Delay_us(15);
    
    I2C_SCL=0;
    Delay_us(15);
    
    temp_data<<=1;
  }
}

unsigned char I2C_read_byte()
{
  unsigned char temp_read=0,i;
  I2C_SDA_IN;
  Delay_us(15); 
  for(i=0;i<8;i++)
  {
    temp_read<<=1;
    I2C_SCL=1;
    Delay_us(15);
    
    if(I2C_SDA_VAL)temp_read |= 0x01;

    I2C_SCL=0;
    Delay_us(15);   
  }

  return temp_read;
}

unsigned char I2C_check_ack()
{
  unsigned char slaveack;
  
  I2C_SDA_IN;
  Delay_us(15);
  
  slaveack = I2C_SDA_VAL;   //读入SDA数值
  
  I2C_SCL=1;
  Delay_us(15);
  
  I2C_SCL=0;   
  Delay_us(15);
  
  if(slaveack)    return 0;
  else            return 1; 
}


void sent_noack()
{
  I2C_SDA=1;
  I2C_SDA_OUT; 
  Delay_us(15);
  I2C_SCL=1;
  Delay_us(15);
  I2C_SCL=0;
}

void sent_ack()
{
  I2C_SDA=0;
  I2C_SDA_OUT; 
  Delay_us(15);
  I2C_SCL=1;
  Delay_us(15);
  I2C_SCL=0;
}













