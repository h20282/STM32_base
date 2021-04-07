/******************************�¶�����ղ���************************
* �¶������
* �¶���ʾ����ߣ�������ʾ���ұ�
******************************************************************/

#include "sys.h"
#include "led.h"
#include "delay.h"
#include "adc.h"

/***************************������*****************************/
int main()
{
 	float adcx = 0.0;
	u16 adcValue = 0;
	u8 i = 0;
	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	TemperatureAndLightAdcInit();
	LED_Init();
	LED_SEL = 0;
	adcx = GetTemperature();        //ʹ��PC5 ADC1, ͨ��15
			adcValue = GetLightAdc(14); //ʹ��PC4 ADC1, ͨ��14
	while(1)
	{		
		i++;
		if( i > 50 )                  //��Լÿ��100��ѭ����������ɨ��һ��ADC��ֵ
		{
			adcx = GetTemperature();    //ʹ��PC5 ADC1, ͨ��15
			adcValue = GetLightAdc(14); //ʹ��PC4 ADC1, ͨ��14
			i = 0;
		}
		//�¶�
		SetLed(0, adcx/10);
		delay_ms(1);
		PortationDisplay(1,(u8)adcx%10);
		delay_ms(1);
		SetLed(2, (u8)(adcx*10)%10);
		delay_ms(1);
		
		//����
		SetLed(4, adcValue/1000);
		delay_ms(1);
		SetLed(5, adcValue%1000/100);
		delay_ms(1);
		SetLed(6, adcValue%100/10);
		delay_ms(1);
		SetLed(7, adcValue%10);
		delay_ms(1);
	}	
}

