#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"	 	 
//��������ʵ��


void print(u32 num, u32 time){
	// ��8λ���������ʾ����v
	u32 i,t,v;
	for (t=0; t<time; t++){
		v = num;		
		for ( i = 0; i < 8; ++i ) {
			SetLed(7-i, v % 10);
			//SetLed(7-i, i);
			delay_ms(1);
			v = v / 10;
		}
	}	
}

int main(void)
{								  
	u8 t;	  
	u32 cnt = 0;
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ�� 
	LED_Init();	
	KEY_Init();   
	LED_SEL=0;       //��ʼ���밴�����ӵ�Ӳ���ӿ�
/*	
	while(1){
		print(12345678, 100);
	}	*/
	while(1)
	{
		t=KEY_Scan();//�õ���ֵ
	   	if(t)
		{						   
			switch(t)
			{				 
				case 1:
				cnt++;
				/*
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
				}*/
					break;
				case 2:
					cnt--;
					break;
					/*
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
					break;*/
				case 3:
					cnt = 0;
					break;
					/*
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
					break;*/
			}
		}else {
			
		}
		print(cnt, 1);	
	}	 
}

























