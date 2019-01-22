#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;//KEY1-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC


}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
void SWITCH_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//Enable PORTC

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4;//Swith0-2&��ʱ�ضϣ�PC.4��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC5,6,7

}

void Voltage_Init(void)
{GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//Enable PORTC

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//Voltage 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC 10
}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
	}else if(KEY1==1&&KEY2==1) key_up=1; 	    
 // �ް�������
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
