/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "led.h"

#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */ 
    OS_CPU_SR     cpu_sr; 
#endif

//起始任务配置
#define Start_Task_PRIO          4   //优先级
#define Start_STK_Size            64	//任务堆栈大小
OS_STK Start_Task_STK[Start_STK_Size];//任务堆栈空间大小
static void start_task(void *p_arg); 				//任务接口函数


//LED任务配置
#define LED_Task_PRIO          5
#define LED_STK_Size            64
OS_STK LED_Task_STK[LED_STK_Size];
static void led_task(void *pdata);



static void systick_init(void) 
{ 
	RCC_ClocksTypeDef  rcc_clocks; 
	RCC_GetClocksFreq(&rcc_clocks);   //调用标准库函数，获取系统时钟。
	SysTick_Config(rcc_clocks.HCLK_Frequency / OS_TICKS_PER_SEC); //初始化并使能SysTick
											//OS_TICKS_PER_SEC是在os_cfg.h中定义的
}

static void led_task(void *p_arg)
{   
	p_arg=p_arg;      //防止编译器产生警告
	for(;;)
	{	 
		/*LED以2s频率闪烁*/
		LED_ON();
		OSTimeDlyHMSM(0,0,0,400);  //1s延时，释放CPU控制权 
		LED_OFF();
		OSTimeDlyHMSM(0,0,0,100); 	//1s延时，释放CPU控制权
	}
}

static void start_task(void *p_arg) 
{ 
	systick_init();     /* Initialize the SysTick. 初始化系统心跳*/
	p_arg=p_arg;
	OS_ENTER_CRITICAL();                                 //进入临界区，无法被中断打断
	OSTaskCreate(led_task, (void *)0, 
						(OS_STK *)&LED_Task_STK[LED_STK_Size-1], 
						LED_Task_PRIO);                               //创建LED任务
	OSTaskSuspend(Start_Task_PRIO);                         //挂起起始任务
	OS_EXIT_CRITICAL();  //退出临界区，可以被中断打断
}

int main(void)
{	
	SystemInit();
	LED_init();			//初始化LED,系统时钟
	OSInit();//ucos初始化
	OSTaskCreate(start_task, (void *)0, (OS_STK *)&Start_Task_STK[Start_STK_Size-1], Start_Task_PRIO);  //创建起始任务
	OSStart();  //ucos启动
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
