/*
******************************************************************************
*Filename      :oledmenu.c
*Programmer(s) :416GZJ
*Description   :2020������
******************************************************************************
*/
#include "oledmenu.h"
/****************һ���ܲ˵�*********************/
void Oledmenu_1(void)
{
	OLED_Clear();
	u8 key=0;
	static signed char flag=1;
	while(1)
	{
		OLED_ShowCHinese( 16, 0,0);//����
		OLED_ShowCHinese( 32, 0,1);
		
		OLED_ShowCHinese( 16,16,2);//��������
		OLED_ShowCHinese( 32,16,3);
		OLED_ShowCHinese( 48,16,8);
		OLED_ShowCHinese( 64,16,9);
		
		OLED_ShowCHinese( 16,32,4);//���Ӳ���
		OLED_ShowCHinese( 32,32,5);
		OLED_ShowCHinese( 48,32,8);
		OLED_ShowCHinese( 64,32,9);
		
		OLED_ShowCHinese( 16,48,6);//��չ����
		OLED_ShowCHinese( 32,48,7);
		OLED_ShowCHinese( 48,48,8);
		OLED_ShowCHinese( 64,48,9);
		
		OLED_Show3FNum(70,0,mpu_yaw,2,2,12);
		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
			switch(flag)
			{				 
				case 1:Oledmenu_2_1();break;
				case 2:Oledmenu_2_2();break;
				case 3:Oledmenu_2_3();break;
				case 4:Oledmenu_2_4();break;
				default:break;
			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}

/****************�����˵�--���Բ���*********************/
void Oledmenu_2_1(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==2)
	{
		OLED_ShowCHinese(16, 0, 0);//���������
		OLED_ShowCHinese(32, 0, 1);
		OLED_ShowCHinese(48, 0,10);
		OLED_ShowCHinese(64, 0,11);
		OLED_ShowCHinese(80, 0,14);
		
		OLED_ShowCHinese(16,16, 0);//���������
		OLED_ShowCHinese(32,16, 1);
		OLED_ShowCHinese(48,16,10);
		OLED_ShowCHinese(64,16,11);
		OLED_ShowCHinese(80,16,15);
		
		OLED_ShowCHinese(16,32, 0);//���������
		OLED_ShowCHinese(32,32, 1);
		OLED_ShowCHinese(48,32,10);
		OLED_ShowCHinese(64,32,11);
		OLED_ShowCHinese(80,32,16);
		
		OLED_ShowCHinese(16,48, 0);//���������
		OLED_ShowCHinese(32,48, 1);
		OLED_ShowCHinese(48,48,10);
		OLED_ShowCHinese(64,48,11);
		OLED_ShowCHinese(80,48,17);

		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
			switch(flag)
			{		 
				case 1:Oledmenu_3_1();break;
				case 2:Oledmenu_3_2();break;
				case 3:Oledmenu_3_3();break;
				case 4:Oledmenu_3_4();break;
				default:break;
			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}

/****************�����˵�--���Բ���1*********************/
void Oledmenu_3_1(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==3)
	{
		OLED_ShowString(16,4,"LED_TEST",12);
		OLED_ShowString(16,20,"BEEP_TEST",12);
		OLED_ShowString(16,36,"KEY_TEST",12);
		OLED_ShowString(16,52,"OLED_TEST",12);
		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
			switch(flag)
			{		 
				case 1:LED_TEST();break;
				case 2:BEEP_TEST();break;
				case 3:KEY_TEST();break;
				case 4:OLED_TEST();break;
				default:break;
			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}

/****************�����˵�--���Բ���2*********************/
void Oledmenu_3_2(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==3)
	{
		OLED_ShowString(16,4,"mpu6050_TEST",12);
		OLED_ShowString(16,20,"NRF24L01_TEST",12);
		OLED_ShowString(16,36,"Sonic_TEST",12);
		OLED_ShowString(16,52,"motor_TEST",12);
		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
			switch(flag)
			{		 
				case 1:MPU9250_TEST();break;
				case 2:NRF24L01_Test();break;
				case 3:Ultrasonic_TEST();break;
				case 4:Motor_TEST();break;
				default:break;
			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}

/****************�����˵�--���Բ���3*********************/
void Oledmenu_3_3(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==3)
	{
		OLED_ShowString(16,4,"Encoder_TEST",12);
		OLED_ShowString(16,20,"Step_TEST",12);
		OLED_ShowString(16,36,"Sonic_TEST",12);
		OLED_ShowString(16,52,"motor_TEST",12);

		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
			switch(flag)
			{		 
				case 1:Encoder_TEST();break;
				case 2:Step_TEST();break;
				case 3:Test_11();break;
				case 4:Test_12();break;
				default:break;
			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}

/****************�����˵�--���Բ���4*********************/
void Oledmenu_3_4(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==3)
	{
		OLED_ShowCHinese(16,0, 20);//����ʮ��
		OLED_ShowCHinese(32,0, 21);
		OLED_ShowCHinese(48,0, 31);
		OLED_ShowCHinese(64,0, 24);
		
		OLED_ShowCHinese(16,16, 20);//����ʮ��
		OLED_ShowCHinese(32,16, 21);
		OLED_ShowCHinese(48,16, 31);
		OLED_ShowCHinese(64,16, 25);
		
		OLED_ShowCHinese(16,32, 20);//����ʮ��
		OLED_ShowCHinese(32,32, 21);
		OLED_ShowCHinese(48,32, 31);
		OLED_ShowCHinese(64,32, 26);
		
		OLED_ShowCHinese(16,48, 20);//����ʮ��
		OLED_ShowCHinese(32,48, 21);
		OLED_ShowCHinese(48,48, 31);
		OLED_ShowCHinese(64,48, 27);

		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
			switch(flag)
			{		 
				case 1:Test_13();break;
				case 2:Test_14();break;
				case 3:Test_15();break;
				case 4:Test_16();break;
				default:break;
			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}

/****************�����˵�--��������*********************/
void Oledmenu_2_2(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==2)
	{
		OLED_ShowCHinese(16, 0, 2);//���������
		OLED_ShowCHinese(32, 0, 3);
		OLED_ShowCHinese(48, 0,10);
		OLED_ShowCHinese(64, 0,11);
		OLED_ShowCHinese(80, 0,14);
		
		OLED_ShowCHinese(16,16, 2);//���������
		OLED_ShowCHinese(32,16, 3);
		OLED_ShowCHinese(48,16,10);
		OLED_ShowCHinese(64,16,11);
		OLED_ShowCHinese(80,16,15);
		
		OLED_ShowCHinese(16,32, 2);//���������
		OLED_ShowCHinese(32,32, 3);
		OLED_ShowCHinese(48,32,10);
		OLED_ShowCHinese(64,32,11);
		OLED_ShowCHinese(80,32,16);
		
		OLED_ShowCHinese(16,48, 2);//���������
		OLED_ShowCHinese(32,48, 3);
		OLED_ShowCHinese(48,48,10);
		OLED_ShowCHinese(64,48,11);
		OLED_ShowCHinese(80,48,17);
		
		
		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
//			switch(flag)
//			{
//				case 1:Task_a_1();break;
//				case 2:Task_a_2();break;
//				case 3:Task_a_3();break;
//				case 4:Task_a_4();break;
//				default:break;
//			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}



/****************�����˵�--���Ӳ���*********************/
void Oledmenu_2_3(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==2)
	{
		OLED_ShowCHinese(16, 0, 4);//���������
		OLED_ShowCHinese(32, 0, 5);
		OLED_ShowCHinese(48, 0,10);
		OLED_ShowCHinese(64, 0,11);
		OLED_ShowCHinese(80, 0,14);
		
		OLED_ShowCHinese(16,16, 4);//���������
		OLED_ShowCHinese(32,16, 5);
		OLED_ShowCHinese(48,16,10);
		OLED_ShowCHinese(64,16,11);
		OLED_ShowCHinese(80,16,15);
		
		OLED_ShowCHinese(16,32, 4);//���������
		OLED_ShowCHinese(32,32, 5);
		OLED_ShowCHinese(48,32,10);
		OLED_ShowCHinese(64,32,11);
		OLED_ShowCHinese(80,32,16);
		
		OLED_ShowCHinese(16,48, 4);//���������
		OLED_ShowCHinese(32,48, 5);
		OLED_ShowCHinese(48,48,10);
		OLED_ShowCHinese(64,48,11);
		OLED_ShowCHinese(80,48,17);

		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
//			switch(flag)
//			{				 
//				case 1:Task_b_1();break;
//				case 2:Task_b_2();break;
//				case 3:Task_b_3();break;
//				case 4:Task_b_4();break;
//				default:break;
//			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}

/****************�����˵�--��չ����*********************/
void Oledmenu_2_4(void)
{
	u8 key=0;
	signed char flag=1;
	while(menu_level==2)
	{
		OLED_ShowCHinese(16, 0, 6);//���������
		OLED_ShowCHinese(32, 0, 7);
		OLED_ShowCHinese(48, 0,10);
		OLED_ShowCHinese(64, 0,11);
		OLED_ShowCHinese(80, 0,14);
		
		OLED_ShowCHinese(16,16, 6);//���������
		OLED_ShowCHinese(32,16, 7);
		OLED_ShowCHinese(48,16,10);
		OLED_ShowCHinese(64,16,11);
		OLED_ShowCHinese(80,16,15);
		
		OLED_ShowCHinese(16,32, 6);//���������
		OLED_ShowCHinese(32,32, 7);
		OLED_ShowCHinese(48,32,10);
		OLED_ShowCHinese(64,32,11);
		OLED_ShowCHinese(80,32,16);
		
		OLED_ShowCHinese(16,48, 6);//���������
		OLED_ShowCHinese(32,48, 7);
		OLED_ShowCHinese(48,48,10);
		OLED_ShowCHinese(64,48,11);
		OLED_ShowCHinese(80,48,17);

		key=KEY_Scan(0);
		if(key!=0)
		{
			OLED_ShowString(0,16*(flag-1),(void *)"  ",16);
			if(key==ku)	flag--;
			if(key==kd)	flag++;
			if(flag>4) 	flag=1;
			if(flag<1) 	flag=4;
		}
		OLED_ShowString(0,16*(flag-1),(void *)"->",16);
		if(key==kc)
		{
			OLED_Clear();
			menu_level++;
//			switch(flag)
//			{				 
//				case 1:Task_c_1();break;
//				case 2:Task_c_2();break;
//				case 3:Task_c_3();break;
//				case 4:Task_c_4();break;
//				default:break;
//			}
			OLED_Clear();
		}
		OLED_Refresh_Gram();
	}
}













