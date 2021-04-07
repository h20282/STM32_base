#include "led.h"
#include "delay.h"
#include "sys.h"

//跑马灯实验  
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	   //初始化与LED连接的硬件接口
	while(1)
	{
		LED0 = 0;
		//GPIO_ResetBits(GPIOE,GPIO_Pin_8);  //LED0输出低
		GPIO_ResetBits(GPIOE,GPIO_Pin_9);  //LED1输出低
		GPIO_ResetBits(GPIOE,GPIO_Pin_10); //LED2输出低
		GPIO_ResetBits(GPIOE,GPIO_Pin_11); //LED3输出低
		GPIO_ResetBits(GPIOE,GPIO_Pin_12); //LED4输出低
		GPIO_ResetBits(GPIOE,GPIO_Pin_13); //LED5输出低
		GPIO_ResetBits(GPIOE,GPIO_Pin_14); //LED6输出低
		GPIO_ResetBits(GPIOE,GPIO_Pin_15); //LED7输出低
		delay_ms(1000);
		LED0 = 1;
		//GPIO_SetBits(GPIOE,GPIO_Pin_8);//LED0输出高
		GPIO_SetBits(GPIOE,GPIO_Pin_9);  //LED1输出低
		GPIO_SetBits(GPIOE,GPIO_Pin_10); //LED2输出低
		GPIO_SetBits(GPIOE,GPIO_Pin_11); //LED3输出低
		GPIO_SetBits(GPIOE,GPIO_Pin_12); //LED4输出低
		GPIO_SetBits(GPIOE,GPIO_Pin_13); //LED5输出低
		GPIO_SetBits(GPIOE,GPIO_Pin_14); //LED6输出低
		GPIO_SetBits(GPIOE,GPIO_Pin_15); //LED7输出低
		delay_ms(1000);
	}
 }

