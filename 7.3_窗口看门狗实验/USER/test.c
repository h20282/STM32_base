#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "wdg.h"	 	 
//���ڿ��Ź�ʵ��
   
int main(void)
{	
  Stm32_Clock_Init(9);   //ϵͳʱ������
	delay_init(72);	       //��ʱ��ʼ��
	uart_init(72,9600);    //���ڳ�ʼ�� 
	LED_Init();		  	     //��ʼ����LED���ӵ�Ӳ���ӿ�
	LED0=1;
	delay_ms(500);	  
	WWDG_Init(0X7F,0X5F,3);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
 	while(1)
	{
		LED0=0;
		delay_ms(20);
	}	 
}
