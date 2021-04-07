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

//��ʼ��������
#define Start_Task_PRIO          4   //���ȼ�
#define Start_STK_Size            64	//�����ջ��С
OS_STK Start_Task_STK[Start_STK_Size];//�����ջ�ռ��С
static void start_task(void *p_arg); 				//����ӿں���


//LED��������
#define LED_Task_PRIO          5
#define LED_STK_Size            64
OS_STK LED_Task_STK[LED_STK_Size];
static void led_task(void *pdata);



static void systick_init(void) 
{ 
	RCC_ClocksTypeDef  rcc_clocks; 
	RCC_GetClocksFreq(&rcc_clocks);   //���ñ�׼�⺯������ȡϵͳʱ�ӡ�
	SysTick_Config(rcc_clocks.HCLK_Frequency / OS_TICKS_PER_SEC); //��ʼ����ʹ��SysTick
											//OS_TICKS_PER_SEC����os_cfg.h�ж����
}

static void led_task(void *p_arg)
{   
	p_arg=p_arg;      //��ֹ��������������
	for(;;)
	{	 
		/*LED��2sƵ����˸*/
		LED_ON();
		OSTimeDlyHMSM(0,0,0,400);  //1s��ʱ���ͷ�CPU����Ȩ 
		LED_OFF();
		OSTimeDlyHMSM(0,0,0,100); 	//1s��ʱ���ͷ�CPU����Ȩ
	}
}

static void start_task(void *p_arg) 
{ 
	systick_init();     /* Initialize the SysTick. ��ʼ��ϵͳ����*/
	p_arg=p_arg;
	OS_ENTER_CRITICAL();                                 //�����ٽ������޷����жϴ��
	OSTaskCreate(led_task, (void *)0, 
						(OS_STK *)&LED_Task_STK[LED_STK_Size-1], 
						LED_Task_PRIO);                               //����LED����
	OSTaskSuspend(Start_Task_PRIO);                         //������ʼ����
	OS_EXIT_CRITICAL();  //�˳��ٽ��������Ա��жϴ��
}

int main(void)
{	
	SystemInit();
	LED_init();			//��ʼ��LED,ϵͳʱ��
	OSInit();//ucos��ʼ��
	OSTaskCreate(start_task, (void *)0, (OS_STK *)&Start_Task_STK[Start_STK_Size-1], Start_Task_PRIO);  //������ʼ����
	OSStart();  //ucos����
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
