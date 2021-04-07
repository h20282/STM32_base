#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"	
#include "includes.h"	 
//Mini STM32��������չʵ�� 8
//ucos ʵ��
//����ԭ��@ALIENTEK
//����֧�֣�www.openedv.com

 
//���������ջ��С
#define LED0_STK_SIZE    64
#define LED1_STK_SIZE    64
#define LED2_STK_SIZE    64
#define START_STK_SIZE   128

//�����������ȼ�
#define LED0_TASK_Prio   9
#define LED1_TASK_Prio   5
#define LED2_TASK_Prio   7
#define START_TASK_Prio  10

//�����ջ
OS_STK  TASK_LED2_STK[LED2_STK_SIZE];
OS_STK  TASK_LED1_STK[LED1_STK_SIZE];
OS_STK  TASK_LED0_STK[LED0_STK_SIZE];
OS_STK  TASK_START_STK[START_STK_SIZE];
//��������
void TaskStart(void *pdata);
void TaskLed0(void *pdata);
void TaskLed1(void *pdata);
void TaskLed2(void *pdata);

//ϵͳʱ�����ú���
void SysTick_Configuration(void);

INT32U segi = 0;	 
//Mini STM32������ucos����
//����ucos2.52�ں�.
//����ԭ��@ALIENTEK
//www.openedv.com
//2010.12.15			 
int main(void)
{			 	   
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ�� 
	uart_init(72,9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	   //��ʼ����LED���ӵ�Ӳ���ӿ�  
	LED_SEL = 0;
	SysTick_Configuration();
	OSInit();
	OSTaskCreate( TaskStart,	   //task pointer
					(void *)0,	         //parameter
					(OS_STK *)&TASK_START_STK[START_STK_SIZE-1],	//task stack top pointer
					START_TASK_Prio );	 //task priority
	
	OSStart();
	return 0;	   
}
//��ʼ����
void TaskStart(void * pdata)
{
	pdata = pdata; 
	OS_ENTER_CRITICAL();   
	OSTaskCreate(TaskLed0, (void * )0, (OS_STK *)&TASK_LED0_STK[LED0_STK_SIZE-1], LED0_TASK_Prio);
	OSTaskCreate(TaskLed1, (void * )0, (OS_STK *)&TASK_LED1_STK[LED1_STK_SIZE-1], LED1_TASK_Prio);
	OSTaskCreate(TaskLed2, (void * )0, (OS_STK *)&TASK_LED2_STK[LED2_STK_SIZE-1], LED2_TASK_Prio);
	OSTaskSuspend(START_TASK_Prio);	//suspend but not delete
	OS_EXIT_CRITICAL();
}
//����1
//�ڰ˶����������ʾ��0��.
void TaskLed0(void *pdata)
{
	while(1)
	{
		SetLed(segi,0);
		GPIOB->ODR = segi;
		segi ++;
		if(segi>7) segi=0;
		OSTimeDlyHMSM(0,0,0,900);	
	}
}
//����2
//�ڰ˶����������ʾ��1��.
void TaskLed1(void *pdata)
{
	while(1)
	{
		SetLed(segi,1);
		GPIOB->ODR = segi;		
		segi ++;
		if(segi>7) segi=0;
		OSTimeDlyHMSM(0,0,0,600);	
	}
}
//����3
//�ڰ˶����������ʾ��2��.
void TaskLed2(void *pdata)
{
	while(1)
	{
		SetLed(segi,2);
		GPIOB->ODR = segi;		
		segi ++;
		if(segi>7) segi=0;
		OSTimeDlyHMSM(0,0,0,700);	
	}
}
//ϵͳʱ���жϷ�����
void SysTick_Handler(void)
{
	OS_ENTER_CRITICAL();   /* Tell uC/OS-II that we are starting an ISR  */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    OSTimeTick();        /* Call uC/OS-II's OSTimeTick()               */

    OSIntExit();         /* Tell uC/OS-II that we are leaving the ISR  */
}
//ϵͳʱ�����ã����1ms����һ���ж�
void SysTick_Configuration(void)
{
 	SysTick->CTRL&=~(1<<2);//SYSTICKʹ���ⲿʱ��Դ
	SysTick->CTRL|=1<<1;   //����SYSTICK�ж�
	SysTick->LOAD=9000;    //����1ms�ж�
	//bit2���,ѡ���ⲿʱ��  HCLK/8
	//MY_NVIC_Init(3,3,SystemHandler_SysTick,2);//��2��������ȼ� 
	SysTick->CTRL|=1<<0;   //����SYSTICK
}
