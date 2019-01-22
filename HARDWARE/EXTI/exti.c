#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "dac.h"
#include "lcd.h"
#include "adc.h"

u8 m=0;
u8 voltage;
extern u8 key;
extern u8 swith;
extern u16 dac_get;
extern u16 dacval;
extern u16 dacx;
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	//	�����˿ڳ�ʼ��
	SWITCH_Init();
	Voltage_Init();

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	//GPIOC.4 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOC.5 �ж����Լ��жϳ�ʼ������  �����ƽ����
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//Switch 001
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOC.6	  �ж����Լ��жϳ�ʼ������ �����ƽ���� //Swith 010
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;		
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOC.7	  �ж����Լ��жϳ�ʼ������   �����ƽ����	//Swith 100
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	//GPIOC.1	�ж����Լ��жϳ�ʼ������		�����ƽ����	//Ƿѹ����
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_Init(&EXTI_InitStructure);
  //GPIOC.10	  �ж����Լ��жϳ�ʼ������   �����ƽ����	//key1����΢��
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource10);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���   
	//GPIOC.11	  �ж����Լ��жϳ�ʼ������   �����ƽ����	//key2����΢��
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource11);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���		
		
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���Swith���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
		

		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���key���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�1�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);		
		
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���Swith���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�1�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
		
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�3�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
}	

		
 
//�ⲿ�ж�5-9�������
void EXTI9_5_IRQHandler(void)
{LED0=1;
u16 dacval=0;
swith=Swith_Scan(0);
if 		 (swith==Swith_OFF)  			 {dacval=0;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}	//0mA��
else if(swith==Swith0_ON)  			 {dacval=505;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}  //100mA�� 124
else if(swith==Swith1_ON) 			 {dacval=1011;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}	//200mA 248
else if(swith==Swith2_ON) 			 {dacval=1517;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}	//300mA 372
else if(swith==Swith0_Swith2_ON) {dacval=2023;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}	//400mA 496
else if(swith==Swith1_Swith2_ON) {dacval=2528;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}	//500mA 621
else if(swith==Swith_Fall) 			 {dacval=dacval;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}//

dac_get=dacval;//��ȡǰ������DAC��ֵ
delay_ms(10);
EXTI_ClearFlag(EXTI_Line5);
EXTI_ClearITPendingBit(EXTI_Line5);  
EXTI_ClearFlag(EXTI_Line6);
EXTI_ClearITPendingBit(EXTI_Line6);
EXTI_ClearFlag(EXTI_Line7);
EXTI_ClearITPendingBit(EXTI_Line7);//���LINE2�ϵ��жϱ�־λ  

return;
} 
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);
	key=KEY_Scan(0);			  
if(key==KEY1_PRES)
{		 
if			(dac_get<4000)							{
	
		dac_get+=50;
		DAC_SetChannel1Data(DAC_Align_12b_R, dac_get);}//����DACֵ	
}
else if (key==KEY2_PRES)					{
	  if(dac_get>50)									{			

		dac_get-=50;}
		else dac_get=0;
		DAC_SetChannel1Data(DAC_Align_12b_R, dac_get);//����DACֵ
}		
	delay_ms(10);
	EXTI_ClearFlag(EXTI_Line10);
	EXTI_ClearITPendingBit(EXTI_Line10);
	EXTI_ClearFlag(EXTI_Line11);
	EXTI_ClearITPendingBit(EXTI_Line11);
	
}

void EXTI1_IRQHandler(void)//Ƿѹ����
{
delay_ms(100);
	 u16 dacx2;
	 u16 adcx1;
	float temp1;	
	voltage=Voltage_Scan(0);
	if (voltage==Voltage_Low)
		{	
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);
	LED1=1;
	LED0=0;
	BEEP=1;
   DAC_SetChannel1Data(DAC_Align_12b_R, 0);          //ʹdac���Ϊ��
			dacx2=DAC_GetDataOutputValue(DAC_Channel_1);			
						LCD_ShowxNum(124,150,dacx2,4,16,0);     	//��ʾDAC�Ĵ���ֵ

			temp1=(float)dacx2*(3.3/4096);			//�õ�DAC��ѹֵ
			dacx2=temp1;
 			LCD_ShowxNum(124,170,temp1,1,16,0);     	//��ʾ��ѹֵ��������
 			temp1-=dacx2;
			temp1*=1000;
			LCD_ShowxNum(140,170,temp1,3,16,0X80); 	//��ʾ��ѹֵ��С������
 			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//�õ�ADCת��ֵ	  
			temp1=(float)adcx1*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx1=temp1;
 			LCD_ShowxNum(124,190,temp1,1,16,0);     	//��ʾ��ѹֵ��������
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,190,temp1,3,16,0X80); 	//��ʾ��ѹֵ��С������
			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//�õ�ADCת��ֵ	  
			temp1=(float)adcx1*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx1=temp1;
 			LCD_ShowxNum(124,210,temp1,1,16,0);     	//��ʾ��ѹֵ��������
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,210,temp1,3,16,0X80); 	//��ʾ��ѹֵ��С������			

}
	else if(voltage==Voltage_High)
	{
	BEEP=0;
	LED1=0;
	//LED0=0;
	DAC_SetChannel1Data(DAC_Align_12b_R, dac_get);	
	EXTI_ClearFlag(EXTI_Line1);
	EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
 void EXTI4_IRQHandler(void)
{
	 u16 dacx2;
	 u16 adcx1;
	float temp1;
	  u8 n=0;
		u8 countdown;
	  delay_ms(10);
    countdown=SWITCH1_Scan(0);
	if(m==0&&countdown==SWITCH6_PRES)
	{
		//if(countdown==SWITCH6_PRES)
//{
		while(1)
	{
		n++;
		delay_ms(1000);//��ʱ0.5s
		LED1=!LED1;//���ϲ�����ȥ��
    //LED0=0;		
 		LCD_ShowxNum(124,230,11-n,2,16,0);     				//��ʾ����         
			if(n==11)
		{  
			//dac_get=0;
			DAC_SetChannel1Data(DAC_Align_12b_R, 0);          //ʹdac���Ϊ��
			dacx2=DAC_GetDataOutputValue(DAC_Channel_1);			
						LCD_ShowxNum(124,150,dacx2,4,16,0);     	//��ʾDAC�Ĵ���ֵ

			temp1=(float)dacx2*(3.3/4096);			//�õ�DAC��ѹֵ
			dacx2=temp1;
 			LCD_ShowxNum(124,170,temp1,1,16,0);     	//��ʾ��ѹֵ��������
 			temp1-=dacx2;
			temp1*=1000;
			LCD_ShowxNum(140,170,temp1,3,16,0X80); 	//��ʾ��ѹֵ��С������
 			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//�õ�ADCת��ֵ	  
			temp1=(float)adcx1*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx1=temp1;
 			LCD_ShowxNum(124,190,temp1,1,16,0);     	//��ʾ��ѹֵ��������
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,190,temp1,3,16,0X80); 	//��ʾ��ѹֵ��С������
			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//�õ�ADCת��ֵ	  
			temp1=(float)adcx1*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx1=temp1;
 			LCD_ShowxNum(124,210,temp1,1,16,0);     	//��ʾ��ѹֵ��������
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,210,temp1,3,16,0X80); 	//��ʾ��ѹֵ��С������
      LED0=0;
			m++;			
      break;
		}
	}

}
//}
	else if(m!=0)
	{
 if(countdown==SWITCH7_PRES)
		{
			LED1=1;//���ϲ�����ȥ��
			//DAC_SetChannel1Data(DAC_Align_12b_R, dacval);
			m=0;
			DAC_SetChannel1Data(DAC_Align_12b_R, dac_get);	
			EXTI_ClearFlag(EXTI_Line4);
			EXTI_ClearITPendingBit(EXTI_Line4);
		//���LINE4�ϵ��жϱ�־
		}
}	

	}
