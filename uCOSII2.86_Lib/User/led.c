#include "stm32f10x.h"
#include "led.h"

void LED_init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��PE,PB�˿�ʱ,���Ҵ򿪸���ʱ��

	//�ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ�� ����PB3�ڲ���ʹ��
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;		 //PB.3 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.3
 GPIO_SetBits(GPIOB,GPIO_Pin_3);						     //PB.3 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	  //PE.8-15 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 						    //PB.8-15 ����� 
}


void LED_ON(void)
{
	GPIO_ResetBits(LED_PORT, LED_PIN);
}

void LED_OFF(void)
{
	GPIO_SetBits(LED_PORT, LED_PIN);
}
