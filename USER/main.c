#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 	 
#include "dac.h"
#include "adc.h"
#include "usmart.h"
#include "exti.h"
#include "beep.h"

 u8 key;
 u8 swith;
 u16 dacval=0;
 u16 dac_get=0;
 u16 dacx=0;
 u16 dacx1;


 int main(void)
 {	 
	u16 adcx=0;

	float temp;
  	
	u8 t=0;

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	KEY_Init();	 //��ʼ����������
 	SWITCH_Init();
	BEEP_Init(); 
	EXTIX_Init();
	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			 	 //LCD��ʼ��
	usmart_dev.init(72);	//��ʼ��USMART	
 	Adc_Init();		  		//ADC��ʼ��
	Dac1_Init();				//DAC��ʼ��

	POINT_COLOR=RED;//��������Ϊ��ɫ 
	//��ʾ��ʾ��Ϣ		 
	LCD_ShowString(70,30,400,16,16,"BJTU");
	LCD_ShowString(62,90,200,16,16,"Zhao Gong");	
	LCD_ShowString(64,110,200,16,16,"Yupeng Cui");
	LCD_ShowString(64,130,200,16,16,"Xueying Zhou");	
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(60,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(60,190,200,16,16,"ADC VOL:0.000V");
	LCD_ShowString(60,210,200,16,16,"CURRENT:0.000A");
	LCD_ShowString(60,230,200,16,16,"  TIME :0 s");	
	 DAC_SetChannel1Data(DAC_Align_12b_R, dacval);//��ʼֵΪ0	    	      
		while(1)
	{
		LED1=0;
		//delay_ms(10);
//LED0=0;
//		t++;
dacx=DAC_GetDataOutputValue(DAC_Channel_1);
adcx=Get_Adc_Average(ADC_Channel_1,20);		


			if(adcx<=8)
			{
				LED0=0;
			}
				else if(adcx>8)
				{
					LED0=1;
				}
		
			

			LCD_ShowxNum(124,150,dacx,4,16,0);     	//��ʾDAC�Ĵ���ֵ
			temp=(float)dacx*(3.3/4096);			//�õ�DAC��ѹֵ
			dacx1=temp;
 			LCD_ShowxNum(124,170,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=dacx1;
			temp*=1000;
			LCD_ShowxNum(140,170,temp,3,16,0X80); 	//��ʾ��ѹֵ��С������
 			//adcx1=Get_Adc_Average(ADC_Channel_1,10);		//�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(124,190,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(140,190,temp,3,16,0X80); 	//��ʾ��ѹֵ��С������
			adcx=Get_Adc_Average(ADC_Channel_1,10);		//�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			//�õ�����ֵ
			adcx=temp;
 			LCD_ShowxNum(124,210,temp,1,16,0);     	//��ʾ����ֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(140,210,temp,3,16,0X80); 	//��ʾ����ֵС������
  
		}
	}

