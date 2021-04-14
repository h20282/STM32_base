#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "exti.h"

//外部中断实验

//注意,此代码还是无法进行SWD仿真!因为使用了中断,没法用普通的方法来考虑间歇复用SWD口! 
int main(void)
{
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	LED_Init();	         //初始化与LED连接的硬件接口
	LED_SEL=0;
	EXTIX_Init();	       //外部中断初始化
	while(1)
	{
		delay_ms(100);
	}	 
}
