ʵ������:
	̽����STM32F4������
	
ʵ��Ŀ��:
	ѧϰMPU9250 ���ᴫ����(������ٶ�+����������+���������)��ʹ��.
	
Ӳ����Դ:
	1,DS0(������PF9)
	2,����1(������:115200,PA9/PA10�����ڰ���USBת����оƬCH340����)
	3,ALIENTEK 2.8/3.5/4.3/7��TFTLCDģ��(ͨ��FSMC����,FSMC_NE4��LCDƬѡ/A6��RS)
	4,MPU9250������(������PB6(SCL),PB7(SDA)����).

ʵ������:
	��ʵ�鿪�����ȳ�ʼ��MPU9250��Ȼ������MPL�⣬��ʼ��MPU9250��ʹ��DMP���������ѭ�����治ͣ
	��ȡ���¶ȴ����������ٶȴ������������ǡ�DMP��̬������ŷ���ǵ����ݡ�����LCDģ��������ʾ�ɼ�
	������Ϣ��DS0��ָʾ�����������С�
	
	


//				temp=yaw*10;
//			  if(temp<0)
//				{
////					OLED_ShowString(45,30,"-",12);		
////					 OLED_Refresh_Gram();
//					temp=-temp;		//תΪ����
//				}
//       else 
//				OLED_ShowString(35,30," ",12);	
//					
//				  OLED_ShowNum(60,30,temp/10,3 ,12);	
//			  
//				  OLED_ShowNum(80,30,temp%10,3 ,12);	
//				  OLED_Refresh_Gram();



//		if(MS6==6) 
//		{
//		     GPIO_ResetBits(GPIOE,GPIO_Pin_6) ;//��λF9 ����D1
//		
//					if(mpu_mpl_get_data(&pitch,&roll,&yaw)==0)
//		{	
//			    temp=MPU_Get_Temperature();	//�õ��¶�ֵ
//			    MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//		     	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//				temp=yaw*10;
//			  if(temp<0)
//				{
//					OLED_ShowString(45,30,"-",12);		
//					 OLED_Refresh_Gram();
//					temp=-temp;		//תΪ����
//				}
//        else OLED_ShowString(35,30," ",12);	
//					
//				  OLED_ShowNum(60,30,temp/10,3 ,12);	
//			  
//				  OLED_ShowNum(80,30,temp%10,3 ,12);	
//				  OLED_Refresh_Gram();
//				  

//				speed_angle = PID_Control(&PID_Inner,Expectation_Angle,yaw);
//      
//        MS6=0;  
//		}	 
//			} 
					
					
	


		
void EXTI15_10_IRQHandler(void)
{
	static int flag2=0;
	
	if(flag2==1)
	{
	 GEZI=0;
	 GPIO_ResetBits(GPIOE,GPIO_Pin_3) ;//��λF9 ����D1		 
	}
	if(flag2==3)
	{
	 GEZI=1;
	 GPIO_ResetBits(GPIOE,GPIO_Pin_5) ;//��λF9 ����D1
	    		
	}
	if(flag2==5)
	{
	 GEZI=2;
	 GPIO_ResetBits(GPIOE,GPIO_Pin_6) ;//��λF9 ����D1
	   		
	}
	 flag2++;

	 EXTI_ClearITPendingBit(EXTI_Line14); //���LINE0�ϵ��жϱ�־λ 
}	
	

//void EXTI9_5_IRQHandler(void)
//{
//	
//    
//	 EXTI_ClearITPendingBit(EXTI_Line9); //���LINE0�ϵ��жϱ�־λ 
//}	

//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX1_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
//	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
  XUNJI_Front_GPIO_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource14);//PA0 ���ӵ��ж���0

	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����

}


//void EXTIX2_Init(FunctionalState NewState)
//{
//	NVIC_InitTypeDef   NVIC_InitStructure;
//	EXTI_InitTypeDef   EXTI_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure;
//  XUNJI_Front_GPIO_Init();
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 ���ӵ��ж���0
// 
//	/* ����EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
//  EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
//}


			
					
					
					
					
					