/******************************定时中断实现数字钟************************
* 数字钟
* 通过控制定时中断实现数字钟
******************************************************************/


#include "timer.h"

/***************************主函数*****************************/
int main()
{
	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	TimerxInit( 9999,7199 ); ////10Khz的计数频率，计数到10000表示1s
	LED_Init();
	LED_SEL = 0;
	
	while(1)
	{
		DisplayDigitalClock();
	}	
}




