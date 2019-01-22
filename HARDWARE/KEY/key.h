#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
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


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//��ȡ����2

 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	2		//KEY1����
#define KEY2_PRES	3		//KEY2����
#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��

#define Swith0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����5
#define Swith1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//��ȡ����6
#define Swith2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//��ȡ����7
#define Voltage GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//��ȡ����10
#define SWITCH3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//��ȡ����4

#define Swith_OFF 1
#define Swith0_ON 2
#define Swith1_ON 3
#define Swith2_ON 4
#define Swith0_Swith2_ON 5
#define Swith1_Swith2_ON 6
#define Swith_Fall 7
#define Voltage_High 1
#define Voltage_Low 0
#define SWITCH6_PRES	1
#define SWITCH7_PRES	2

void SWITCH_Init(void);
u8 Swith_Scan(u8);

void Voltage_Init(void);
u8 Voltage_Scan(u8);
u8 SWITCH1_Scan(u8); 
#endif
