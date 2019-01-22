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
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	//	按键端口初始；
	SWITCH_Init();
	Voltage_Init();

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	//GPIOC.4 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOC.5 中断线以及中断初始化配置  任意电平触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//Switch 001
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOC.6	  中断线以及中断初始化配置 任意电平触发 //Swith 010
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;		
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOC.7	  中断线以及中断初始化配置   任意电平触发	//Swith 100
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	//GPIOC.1	中断线以及中断初始化配置		任意电平触发	//欠压保护
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_Init(&EXTI_InitStructure);
  //GPIOC.10	  中断线以及中断初始化配置   任意电平触发	//key1按键微调
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource10);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器   
	//GPIOC.11	  中断线以及中断初始化配置   任意电平触发	//key2按键微调
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource11);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器		
		
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键Swith所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
		

		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键key所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级1， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);		
		
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键Swith所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级1， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
		
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}	

		
 
//外部中断5-9服务程序
void EXTI9_5_IRQHandler(void)
{LED0=1;
u16 dacval=0;
swith=Swith_Scan(0);
if 		 (swith==Swith_OFF)  			 {dacval=0;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}	//0mA档
else if(swith==Swith0_ON)  			 {dacval=505;
DAC_SetChannel1Data(DAC_Align_12b_R, dacval);}  //100mA档 124
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

dac_get=dacval;//读取前面设置DAC的值
delay_ms(10);
EXTI_ClearFlag(EXTI_Line5);
EXTI_ClearITPendingBit(EXTI_Line5);  
EXTI_ClearFlag(EXTI_Line6);
EXTI_ClearITPendingBit(EXTI_Line6);
EXTI_ClearFlag(EXTI_Line7);
EXTI_ClearITPendingBit(EXTI_Line7);//清除LINE2上的中断标志位  

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
		DAC_SetChannel1Data(DAC_Align_12b_R, dac_get);}//设置DAC值	
}
else if (key==KEY2_PRES)					{
	  if(dac_get>50)									{			

		dac_get-=50;}
		else dac_get=0;
		DAC_SetChannel1Data(DAC_Align_12b_R, dac_get);//设置DAC值
}		
	delay_ms(10);
	EXTI_ClearFlag(EXTI_Line10);
	EXTI_ClearITPendingBit(EXTI_Line10);
	EXTI_ClearFlag(EXTI_Line11);
	EXTI_ClearITPendingBit(EXTI_Line11);
	
}

void EXTI1_IRQHandler(void)//欠压保护
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
   DAC_SetChannel1Data(DAC_Align_12b_R, 0);          //使dac输出为零
			dacx2=DAC_GetDataOutputValue(DAC_Channel_1);			
						LCD_ShowxNum(124,150,dacx2,4,16,0);     	//显示DAC寄存器值

			temp1=(float)dacx2*(3.3/4096);			//得到DAC电压值
			dacx2=temp1;
 			LCD_ShowxNum(124,170,temp1,1,16,0);     	//显示电压值整数部分
 			temp1-=dacx2;
			temp1*=1000;
			LCD_ShowxNum(140,170,temp1,3,16,0X80); 	//显示电压值的小数部分
 			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值	  
			temp1=(float)adcx1*(3.3/4096);			//得到ADC电压值
			adcx1=temp1;
 			LCD_ShowxNum(124,190,temp1,1,16,0);     	//显示电压值整数部分
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,190,temp1,3,16,0X80); 	//显示电压值的小数部分
			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值	  
			temp1=(float)adcx1*(3.3/4096);			//得到ADC电压值
			adcx1=temp1;
 			LCD_ShowxNum(124,210,temp1,1,16,0);     	//显示电压值整数部分
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,210,temp1,3,16,0X80); 	//显示电压值的小数部分			

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
		delay_ms(1000);//延时0.5s
		LED1=!LED1;//加上彩屏后去掉
    //LED0=0;		
 		LCD_ShowxNum(124,230,11-n,2,16,0);     				//显示秒数         
			if(n==11)
		{  
			//dac_get=0;
			DAC_SetChannel1Data(DAC_Align_12b_R, 0);          //使dac输出为零
			dacx2=DAC_GetDataOutputValue(DAC_Channel_1);			
						LCD_ShowxNum(124,150,dacx2,4,16,0);     	//显示DAC寄存器值

			temp1=(float)dacx2*(3.3/4096);			//得到DAC电压值
			dacx2=temp1;
 			LCD_ShowxNum(124,170,temp1,1,16,0);     	//显示电压值整数部分
 			temp1-=dacx2;
			temp1*=1000;
			LCD_ShowxNum(140,170,temp1,3,16,0X80); 	//显示电压值的小数部分
 			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值	  
			temp1=(float)adcx1*(3.3/4096);			//得到ADC电压值
			adcx1=temp1;
 			LCD_ShowxNum(124,190,temp1,1,16,0);     	//显示电压值整数部分
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,190,temp1,3,16,0X80); 	//显示电压值的小数部分
			adcx1=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值	  
			temp1=(float)adcx1*(3.3/4096);			//得到ADC电压值
			adcx1=temp1;
 			LCD_ShowxNum(124,210,temp1,1,16,0);     	//显示电压值整数部分
 			temp1-=adcx1;
			temp1*=1000;
			LCD_ShowxNum(140,210,temp1,3,16,0X80); 	//显示电压值的小数部分
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
			LED1=1;//加上彩屏后去掉
			//DAC_SetChannel1Data(DAC_Align_12b_R, dacval);
			m=0;
			DAC_SetChannel1Data(DAC_Align_12b_R, dac_get);	
			EXTI_ClearFlag(EXTI_Line4);
			EXTI_ClearITPendingBit(EXTI_Line4);
		//清除LINE4上的中断标志
		}
}	

	}
