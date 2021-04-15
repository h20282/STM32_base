#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�ⲿ�ж� ��������			   
////////////////////////////////////////////////////////////////////////////////// 	  
 //int show_w0,show_w1,show_w2,show_w3,show_w4,show_w5,show_w6,show_w7;
 int status0=0,status1=0,status2=0;
u32 xuehao[] = {0,5,0,4,0,2,1,3};
//u32 xuehao[] = {1,8,0,5,0,4,0,2,1,3};

//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	int n=1;	 
	delay_ms(10);//����
	
	if(KEY3==0)	 //����3
	{
		while(n--)
		{
			int i,k;
			///*
			for(i=0;i<8;i++)
			{
				SetLed(i, xuehao[i]);
				delay_ms(500);
			}
			//*/
			//status0=(status0+1)%8;
			
		}		 
		EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
	}
}

//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{
	int n=3;
	delay_ms(10);//����
	if(KEY2==0)	 //����2
	{
		while(n--)
		{
			int i;
			for(i=0;i<8;i++)
			{
				SetLed(7-i, xuehao[7-i]);
				delay_ms(300);
			}
			//status1=(status1+1)%8;
		}		 
		EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
	}
}

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����2
	{
	
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
			 
		EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
	}
}

//�ⲿ�жϳ�ʼ������
//��ʼ��PC0-2Ϊ�ж�����.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<4;	   //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFFF000;//PC0-2���ó�����	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,1,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,2,FTIR);//�½��ش���

	MY_NVIC_Init(3,2,EXTI0_IRQChannel,2);//��ռ2�������ȼ�2����2
	MY_NVIC_Init(2,2,EXTI1_IRQChannel,2);//��ռ2�������ȼ�1����2	   
	MY_NVIC_Init(1,2,EXTI2_IRQChannel,2);//��ռ2�������ȼ�1����2
}
//void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)
//NVIC_PreemptionPriority:��ռ���ȼ�
//NVIC_SubPriority       :��Ӧ���ȼ�
//NVIC_Channel           :�жϱ��
//NVIC_Group             :�жϷ��� 0~4
//ע�����ȼ����ܳ����趨����ķ�Χ!����������벻���Ĵ���
//�黮��:
//��0:0λ��ռ���ȼ�,4λ��Ӧ���ȼ�
//��1:1λ��ռ���ȼ�,3λ��Ӧ���ȼ�
//��2:2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
//��3:3λ��ռ���ȼ�,1λ��Ӧ���ȼ�
//��4:4λ��ռ���ȼ�,0λ��Ӧ���ȼ�
//NVIC_SubPriority��NVIC_PreemptionPriority��ԭ����,��ֵԽС,Խ����











