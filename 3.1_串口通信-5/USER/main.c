#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"



void print(u32 num, u32 time){
	// ��8λ���������ʾ����v
	u32 i,t,v;
	for (t=0; t<time; t++){
		v = num;		
		for ( i = 0; i < 8; ++i ) {
			SetLed(7-i, v % 10);
			//SetLed(7-i, i);
			delay_ms(1);
			v = v / 10;
		}
	}	
}

int main( void )
{
	/*u8 i = 1;
	Stm32_Clock_Init( 6 );  //9��Ƶ
	delay_init( 72 ); //12M�ⲿ����
	uart_init( 72, 9600 );
	while( 1 )
	{
		//printf( "i = %d\r\n", i );
		i++;
		delay_ms( 500 );
	}
	*/
	u8 t;
	u8 len;	
	u16 times=0;  
	Stm32_Clock_Init(6); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ�� 
	uart_init(72,9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�    
	LED_SEL = 1;
	while(1)
	{
		if(USART_RX_STA&0x80)
		{					   
			u32 num = 0;
			len=USART_RX_STA&0x3f;//�õ��˴ν��յ������ݳ���
			printf("\n Your MSG: \n");

			for(t=0;t<len;t++)
			{
				num *= 10;
				num += USART_RX_BUF[t]-'0';
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			print(num, 100);
			printf("\n\n");//���뻻��
			USART_RX_STA=0;
		}
		else
		{
			times++;
			if(times%5000==0)
			{
				printf("\nSTM32A Usart\n");
			}
			if(times%200==0) printf("Please Input end with return\n");  
			if(times%30==0) LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}	
}
