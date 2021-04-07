/*********************LED��ͷ�ļ�********************
* ���ߣ�������
******************************************************************/
#ifndef __LED_H
#define __LED_H
	 
#include "sys.h"

//LED�˿ڶ���
#define LED_SEL PBout(3) //PB3 ��ʾλ��ѡ��

//λѡ
#define SEL0 PBout(0)
#define SEL1 PBout(1)
#define SEL2 PBout(2)

//��ѡ
#define LED0 PEout(8)
#define LED1 PEout(9)
#define LED2 PEout(10)
#define LED3 PEout(11)
#define LED4 PEout(12)
#define LED5 PEout(13)
#define LED6 PEout(14)
#define LED7 PEout(15)

void LED_Init(void);//��ʼ��
void LedValue( u8 value ); //���������E-A��ֵ����ˮ��L7-L0��ֵ	
void SetLed(u8 w, u8 value); //�����������λ��ʾʲô����
void PortationDisplay(u8 w, u8 value); //�������ʾ��С�������ֵ

#endif
