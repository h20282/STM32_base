#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"	 	 
//��������ʵ��
int main(void)
{								  
	u8 t;	  
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ�� 
	LED_Init();	
	KEY_Init();   
	LED_SEL=0;       //��ʼ���밴�����ӵ�Ӳ���ӿ�
	while(1)
	{
		t=KEY_Scan();//�õ���ֵ
	   	if(t)
		{						   
			switch(t)
			{				 
				case 1:
				while(1){
					SetLed(7,0);
					delay_ms(200);
					SetLed(6,3);
					delay_ms(200);
					SetLed(5,1);
					delay_ms(200);
					SetLed(4,0);
					delay_ms(200);
					SetLed(3,3);
					delay_ms(200);
					SetLed(2,0);
					delay_ms(200);
					SetLed(1,5);
					delay_ms(200);
					SetLed(0,0);
					}
					break;
				case 2:
					SetLed(0,0);
					delay_ms(100);
					SetLed(1,5);
					delay_ms(100);
					SetLed(2,0);
					delay_ms(100);
					SetLed(3,3);
					delay_ms(100);
					SetLed(4,0);
					delay_ms(100);
					SetLed(5,1);
					delay_ms(100);
					SetLed(6,3);
					delay_ms(100);
					SetLed(7,0);
					break;
				case 3:				
					SetLed(3,0);
					delay_ms(20);
					SetLed(4,0);
					delay_ms(50);
					SetLed(2,0);
					delay_ms(20);
					SetLed(5,0);
					delay_ms(50);
					SetLed(1,0);
					delay_ms(20);
					SetLed(6,0);
					delay_ms(50);
					SetLed(0,0);
					delay_ms(20);
					SetLed(7,0);
					break;
			}
		}else delay_ms(10); 
	}	 
}

























