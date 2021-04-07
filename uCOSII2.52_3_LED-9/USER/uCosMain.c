#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"	
#include "includes.h"	 
//Mini STM32开发板扩展实例 8
//ucos 实验
//正点原子@ALIENTEK
//技术支持：www.openedv.com

 
//设置任务堆栈大小
#define LED0_STK_SIZE    64
#define LED1_STK_SIZE    64
#define LED2_STK_SIZE    64
#define START_STK_SIZE   128

//设置任务优先级
#define LED0_TASK_Prio   9
#define LED1_TASK_Prio   5
#define LED2_TASK_Prio   7
#define START_TASK_Prio  10

//任务堆栈
OS_STK  TASK_LED2_STK[LED2_STK_SIZE];
OS_STK  TASK_LED1_STK[LED1_STK_SIZE];
OS_STK  TASK_LED0_STK[LED0_STK_SIZE];
OS_STK  TASK_START_STK[START_STK_SIZE];
//任务申明
void TaskStart(void *pdata);
void TaskLed0(void *pdata);
void TaskLed1(void *pdata);
void TaskLed2(void *pdata);

//系统时钟配置函数
void SysTick_Configuration(void);

INT32U segi = 0;	 
//Mini STM32开发板ucos范例
//基于ucos2.52内核.
//正点原子@ALIENTEK
//www.openedv.com
//2010.12.15			 
int main(void)
{			 	   
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化 
	uart_init(72,9600);	 //串口初始化为9600
	LED_Init();		  	   //初始化与LED连接的硬件接口  
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
//开始任务
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
//任务1
//在八段数码管上显示“0”.
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
//任务2
//在八段数码管上显示“1”.
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
//任务3
//在八段数码管上显示“2”.
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
//系统时钟中断服务函数
void SysTick_Handler(void)
{
	OS_ENTER_CRITICAL();   /* Tell uC/OS-II that we are starting an ISR  */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    OSTimeTick();        /* Call uC/OS-II's OSTimeTick()               */

    OSIntExit();         /* Tell uC/OS-II that we are leaving the ISR  */
}
//系统时钟配置，设计1ms产生一次中断
void SysTick_Configuration(void)
{
 	SysTick->CTRL&=~(1<<2);//SYSTICK使用外部时钟源
	SysTick->CTRL|=1<<1;   //开启SYSTICK中断
	SysTick->LOAD=9000;    //产生1ms中断
	//bit2清空,选择外部时钟  HCLK/8
	//MY_NVIC_Init(3,3,SystemHandler_SysTick,2);//组2，最低优先级 
	SysTick->CTRL|=1<<0;   //开启SYSTICK
}
