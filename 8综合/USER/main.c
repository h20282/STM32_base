#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "adc.h"


u8 buf_led[8] = {1,0,1,0,1,0,1,0};
u8 buf_digital[8] = {0};

u8 is_led = 1;

//////////////////////////////////////////////////////////////////////////////////
//看门狗 驱动代码
//////////////////////////////////////////////////////////////////////////////////


//初始化独立看门狗
//prer:分频数:0~7(只有低3位有效!)
//分频因子=4*2^prer.但最大值只能是256!
//rlr:重装载寄存器值:低11位有效.
//时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
void IWDG_Init(u8 prer,u16 rlr)
{
    IWDG->KR=0X5555;//使能对IWDG->PR和IWDG->RLR的写
    IWDG->PR=prer;  //设置分频系数
    IWDG->RLR=rlr;  //从加载寄存器 IWDG->RLR
    IWDG->KR=0XAAAA;//reload
    IWDG->KR=0XCCCC;//使能看门狗
}
//喂独立看门狗
void IWDG_Feed(void)
{
    IWDG->KR=0XAAAA;//reload
}


	
void updata_led_digital(u16 time_ms){
	int i,j;
	LED_SEL = is_led;
	for (i=0; i<time_ms*1000; i++){
		for (j=0; j<8; j++){
			if (is_led) {
				PEout((8+j)) = buf_led[j];
			} else {
				SetLed(j, buf_digital[j]);
			}
			delay_us(1);
			i++;
		}
	}
}

void LED_Init_digit()
{
	RCC->APB2ENR|=1<<0;
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<6;
	
	AFIO->MAPR |= 0x02000000;
	   	 
	GPIOB->CRL &= 0xFFFF0000;
	GPIOB->CRL |= 0x00003333;
	GPIOB->ODR |= 0x0000000F;
  
	GPIOE->CRH&=0X00000000; 
	GPIOE->CRH|=0X33333333; 
	GPIOE->ODR|=0x0000FF00; 
}

void print(u32 num){
	// 在8位数码管上显示数字num
	// LED_SEL = 0;
	u32 i,t,v;
	for (t=0; t<10; t++){
		v = num;		
		for ( i = 0; i < 8; ++i ) {
			SetLed(7-i, v % 10);
			//printf("%d_ ", (int)v % 10);
			//SetLed(7-i, i);
			delay_ms(1);
			v = v / 10;
		}
	}
}

int main( void )
{
	/*variables*/
	float adcx = 0.0;
	u16 adcValue = 0;
	
	
	u8 t;
	u8 len;	
	u16 times=0;

	u32 i;
	
	u8 led_idx = 0;
	u32 cnt = 0;
	u32 tem_cnt = 0;
	
	u8 mode = 1;
	u32 counter = 0;
		
	
	
	/*inite*/
	
	Stm32_Clock_Init(6);  //系统时钟设置
	delay_init(72);	      //延时初始化 
	uart_init(72,115200);	 //串口初始化为115200
	LED_Init_digit();		  	   //初始化与LED连接的硬件接口    
	TemperatureAndLightAdcInit();
	KEY_Init();
	IWDG_Init(7,3000/256*40);
	LED_SEL = 0;

	for ( i = 0; i<2; ++i){
		LED_SEL = 0;
		print(0);
		LED_SEL = 1;
		print(0);
	}
	LED_SEL = 0;
	printf("here\n");
	printf("mode = %d|\n", mode);
	/*main loop*/
	u8 key =  0;
	while (1) {
		
		
		key = KEY_Scan();
		// IWDG_Feed();
		
		// updata_led_digital(50);
		if (key) {
			IWDG_Feed();
			// printf("KEY_Scan() = %d", key);
			if (key == 1) {
				counter++;
			} else if (key == 2) {
				counter--;
			} else if (key == 3) {
				mode++;
				mode %= 4;
			}
		}
		/***********/
		

		// if (key == 1) {
		// 	LED_SEL = !LED_SEL;
		// }
		// if (LED_SEL==0){ // digital
		// 	print(cnt++);
		// 	printf("%d ", (int)cnt);
		// 	delay_ms(10);
		// } else 
		if (mode == 0) {
			LED_SEL = 0;
			print(counter);
		} else if (mode == 1) {
			IWDG_Feed();
			if (tem_cnt++>100){
				adcx = GetTemperature();
				adcValue = GetLightAdc(14);
				tem_cnt = 0;
			}
			
			LED_SEL = 0;
			// printf("%f, %d   \n", adcx, adcValue);
			
			//温度
			SetLed(0, adcx/10);
			delay_ms(1);
			PortationDisplay(1,(u8)adcx%10);
			delay_ms(1);
			SetLed(2, (u8)(adcx*10)%10);
			delay_ms(1);
			
			//光照
			SetLed(4, adcValue/1000);
			delay_ms(1);
			SetLed(5, adcValue%1000/100);
			delay_ms(1);
			SetLed(6, adcValue%100/10);
			delay_ms(1);
			SetLed(7, adcValue%10);
			delay_ms(1);
		} else if (mode == 2) {
			// LED_SEL = 1;
			IWDG_Feed();
			updata_led_digital(10);
			if(USART_RX_STA&0x80) {//接收数据成功
				u8 ch;
				len=USART_RX_STA&0x3f;//得到此次接收到的数据长度
				
				printf("\n Your MSG: \n");
				
				for ( t=0; t<len; t++) {
					ch = USART_RX_BUF[t];
					if (ch>='0' && ch<='9'){
						buf_led[ch-'0'] = !buf_led[ch-'0'];
						// LED_SEL = 1;
						// PEout((8+led_idx)) = !PEout((8+led_idx));
						// led_idx += 1;
						// led_idx %= 8; 
					} else if (ch>='a' && ch<='h') {

						buf_digital[ch-'a'] += 1;
						buf_digital[ch-'a'] %= 10;
						// buf_digital[0] %= 10;
						
					} else if (ch=='.') {
						for ( i = 0; i < 8; ++i){
							buf_digital[i] = 0;
						}
					} else if ( ch=='*' ) {
						for ( i = 0; i < 8; ++i){
							buf_led[i] = 0;
						}
					} else if (ch=='/') {
						is_led = !is_led;
					}

					USART1->DR=USART_RX_BUF[t];
					while((USART1->SR&0X40)==0);//等待发送结束
				}
				
				printf("\n\n");//插入换行
				USART_RX_STA=0;
			} else {
				
				times++;
				if(times%5000==0) {
					printf("\nSTM32A Usart\n");
				}
				//if(times%200==0) printf("Please Input end with return\n"); //提示加回车 
				if(times%30==0) {
					// LED_SEL = 1;
					// LED0=!LED0;//闪烁LED,提示系统正在运行.
					
				} 
				// delay_ms(10);   
			}
		} else if (mode==3){
			IWDG_Feed();
			LED_SEL = 0;
			print(cnt++);
		}
	}	
}
