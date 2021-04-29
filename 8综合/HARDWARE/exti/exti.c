#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�ⲿ�ж� ��������			   
////////////////////////////////////////////////////////////////////////////////// 	  

//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY3==0)	 //����3
	{
		LED7=!LED7;
	}		 
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}

//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0)	 //����2
	{
		LED3=!LED3;
	}		 
	EXTI->PR=1<<1;  //���LINE1�ϵ��жϱ�־λ  
}

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����1
	{
		LED0=!LED0;
	}		 
	EXTI->PR=1<<2;  //���LINE2�ϵ��жϱ�־λ  
}

//�ⲿ�жϳ�ʼ������
//��ʼ��PC0-2Ϊ�ж�����.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFFF000;//PC0-2���ó�����	   
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,1,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,2,FTIR);//�½��ش���

	MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);//��ռ2�������ȼ�2����2
	MY_NVIC_Init(2,1,EXTI1_IRQChannel,2);//��ռ2�������ȼ�1����2	   
	MY_NVIC_Init(2,0,EXTI2_IRQChannel,2);//��ռ2�������ȼ�1����2
}












