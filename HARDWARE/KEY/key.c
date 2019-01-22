#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;//KEY1-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC


}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
void SWITCH_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//Enable PORTC

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4;//Swith0-2&定时关断（PC.4）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC5,6,7

}

void Voltage_Init(void)
{GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//Enable PORTC

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//Voltage 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC 10
}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
	}else if(KEY1==1&&KEY2==1) key_up=1; 	    
 // 无按键按下
}

u8 Swith_Scan(u8 mode)
{static u8 swith_on=1;
	if(mode)swith_on=1;
	if			(Swith0==1 && Swith1==1 && Swith2==1)	return Swith_OFF;
	else if (Swith0==0 && Swith1==1 && Swith2==1)	return Swith0_ON;
	else if (Swith0==1 && Swith1==0 && Swith2==1) return Swith1_ON;
	else if (Swith0==1 && Swith1==1 && Swith2==0) return Swith2_ON;
	else if (Swith0==0 && Swith1==1 && Swith2==0) return Swith0_Swith2_ON;
	else if (Swith0==1 && Swith1==0 && Swith2==0) return Swith1_Swith2_ON;
	else if (Swith0==1 && Swith1==0 && Swith2==0) return Swith_Fall;
	else if (Swith0==0 && Swith1==0 && Swith2==0) return Swith_Fall;

}
u8 Voltage_Scan(u8 mode)
{static u8 voltage_dect=1;
	delay_ms(10);
	if(mode) voltage_dect=1;
	if(Voltage==1) return Voltage_High;
	else if (Voltage==0) return Voltage_Low;
}
	 u8 SWITCH1_Scan(u8 mode)
{	
	
 if(SWITCH3==0)return SWITCH6_PRES;
else if(SWITCH3==1)return SWITCH7_PRES;

}
