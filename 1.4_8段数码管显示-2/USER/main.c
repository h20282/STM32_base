/******************************8位数码管动态扫描************************
* 8位数码管动态扫描
* 每位数码管显示的数字从0加到9
***********************************************************************/

#include "sys.h"
#include "delay.h"
#include "led.h"

 
#define uchar unsigned char

// uchar show_w1,show_w2,show_w3,show_w4,show_w5,show_w6,show_w7,show_w8,flag,count;
uchar show_w[8];
u32 i=0,cnt;

/***************************主函数*****************************/

void print(u32 num){
	// 在8位数码管上显示数字num
	u32 i,t,v;
	for (t=0; t<100; t++){
		v = num;		
		for ( i = 0; i < 8; ++i ) {
			SetLed(7-i, v % 10);
			//SetLed(7-i, i);
			delay_ms(1);
			v = v / 10;
		}
	}
	
	
}
int main()
{

	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	LED_Init();
	LED_SEL = 0;
	for ( i=0; i<8; i++) {
		show_w[i] = i;
	}
	// show_w1=0;
	// show_w2=1;
	// show_w3=2;
	// show_w4=3;
	// show_w5=4;
	// show_w6=5;
	// show_w7=6;
	// show_w8=7;
	cnt = 0;
	while(1)
	{
		print(cnt);
		cnt++;
		/*
		if (++cnt%300==0){
			for ( i=0; i<8; i++) {
				show_w[i]++;
				show_w[i]%=10;
			}
		}
		for ( i=0; i<8; i++) {
			SetLed(i, show_w[i]%10);
			delay_ms(1);
		}*/
	/******/	
		// SetLed(0, show_w1%10);
		// delay_ms(100);
		// SetLed(1, show_w2%10);
		// delay_ms(100);
		// SetLed(2, show_w3%10);
		// delay_ms(100);
		// SetLed(3, show_w4%10);
		// delay_ms(100);
		// SetLed(4, show_w5%10);
		// delay_ms(100);
		// SetLed(5, show_w6%10);
		// delay_ms(100);
		// SetLed(6, show_w7%10);
		// delay_ms(100);
		// SetLed(7, show_w8%10);
		// delay_ms(100);
/*
		show_w1++;
		show_w2++;
		show_w3++;
		show_w4++;
		show_w5++;
		show_w6++;
		show_w7++;
		show_w8++;	 
		LED_SEL=1;
        LED0=1;
		delay_ms(100);
		LED0=0;
		LED1=1;
		delay_ms(100);
		LED1=0;


					  */



	}
}
