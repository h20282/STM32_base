/******************************ADCͷ�ļ�************************
* ���ߣ�������
******************************************************************/

#ifndef _ADC_H
#define _ADC_H

#include "sys.h"
#include "led.h"
#include "delay.h"

#define PA0 PAin(0)
#define PA1 PAin(1)

#define V_Ro PCin(4) //���
#define V_Rt PCin(5) //����


void VoltageAdcInit(void); //�˿ڳ�ʼ����ADC1��ʼ����ADC2��ʼ��
void VoltageAdc1Init(void); //��ѹ����ADC1��ʼ��
void VoltageAdc2Init(void); //��ѹ����ADC2��ʼ��
float GetVoltage(u8 adcx, u8 ch); //��ȡ��ѹֵ
void VoltageDisplay(u8 adcx, float vol); //��ʾ��ѹֵ

u16 GetAdc(u8 adcx, u8 ch); //��ȡADC

void UltrasonicAdcInit(void);//����������ADC��ʼ��
u16 GetUltrasonicAdc(u8 ch); 

/******************�¶Ⱥ͹���***********************/
void TemperatureAndLightAdcInit(void); //�˿ڣ�ADC1��ʼ����ͨ��14��15
u16 GetTemperatureAdc(u8 ch);
float GetTemperature(void);
u16 GetLightAdc(u8 ch);

#endif

