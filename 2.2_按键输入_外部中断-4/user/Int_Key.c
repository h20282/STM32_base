#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"	 	 

//�ⲿ�ж�ʵ��

//ע��,�˴��뻹���޷�����SWD����!��Ϊʹ�����ж�,û������ͨ�ķ��������Ǽ�Ъ����SWD��! 
int main(void)
{			
 	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	LED_Init();	         //��ʼ����LED���ӵ�Ӳ���ӿ�
	LED_SEL=0;
	EXTIX_Init();	       //�ⲿ�жϳ�ʼ��
	while(1)
	{	    
		delay_ms(100);	  
	}	 
}
