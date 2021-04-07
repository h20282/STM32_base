#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//外部中断 驱动代码			   
////////////////////////////////////////////////////////////////////////////////// 	  
 //int show_w0,show_w1,show_w2,show_w3,show_w4,show_w5,show_w6,show_w7;
 int status0=0,status1=0,status2=0;

//外部中断0服务程序
void EXTI0_IRQHandler(void)
{	 
	delay_ms(10);//消抖
	
	if(KEY3==0)	 //按键3
	{
	while(1){
		int i;
		for(i=0;i<100;i++)
		{
		switch(status0)
		{
		case 7:
			 SetLed(7,0);
		     delay_ms(1);
			 
	    case 6:
			 SetLed(6,3);
		     delay_ms(1);		   
	   case 5:
					SetLed(5,1);
					delay_ms(1);
	   case 4:
					SetLed(4,0);
					delay_ms(1);
	   case 3:
					SetLed(3,3);
					delay_ms(1);
	   case 2:
					SetLed(2,0);
					delay_ms(1);
	   case 1:
					SetLed(1,5);
					delay_ms(1);

	   default:
					SetLed(0,0);
					delay_ms(1);

	}
	}
	status0=(status0+1)%8;
	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}
}

//外部中断1服务程序
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY2==0)	 //按键2
	{
	while(1){
		int i;
		for(i=0;i<100;i++)
		{
		switch(status1)
		{
		case 7:
			 SetLed(0,0);
		     delay_ms(1);
			 
	    case 6:
			 SetLed(1,5);
		     delay_ms(1);
	   case 5:
					SetLed(2,0);
					delay_ms(1);
	   case 4:
					SetLed(3,3);
					delay_ms(1);
	   case 3:
					SetLed(4,0);
					delay_ms(1);
	   case 2:
					SetLed(5,1);
					delay_ms(1);
	   case 1:
					SetLed(6,3);
					delay_ms(1);

	   default:
					SetLed(7,0);
					delay_ms(1);

	}
	}
	status1=(status1+1)%8;
	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}
}

//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0)	 //按键2
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
			 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}
}

//外部中断初始化程序
//初始化PC0-2为中断输入.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
	GPIOC->CRL&=0XFFFFF000;//PC0-2设置成输入	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,1,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,2,FTIR);//下降沿触发

	MY_NVIC_Init(3,2,EXTI0_IRQChannel,2);//抢占2，子优先级2，组2
	MY_NVIC_Init(2,2,EXTI1_IRQChannel,2);//抢占2，子优先级1，组2	   
	MY_NVIC_Init(1,2,EXTI2_IRQChannel,2);//抢占2，子优先级1，组2
}












