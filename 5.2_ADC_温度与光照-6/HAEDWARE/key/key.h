/*********************��ͨ�����Լ���������ͷ�ļ�********************
* ���ߣ�������
******************************************************************/

#ifndef _KEY_H
#define _KEY_H

#include "sys.h"
#include "delay.h"

//�����˿ڶ���
#define key3 PCin(0)
#define key2 PCin(1)
#define key1 PCin(2)

#define keyCountMax 10

/****************��������*******************/
// extern u8 keyCountTotal; //���ð���������
// extern u8 keyCount3; //����3���¹����ж����Ĵ���
// extern u8 keyCount2; //����2���¹����ж����Ĵ���
// extern u8 keyCount1; //����1���¹����ж����Ĵ���
// extern u8 keyC3; //key3��ǰ״̬
// extern u8 keyP3; //key3ǰһ��״̬
// extern u8 keyC2; //key2��ǰ״̬
// extern u8 keyP2; //key2ǰһ��״̬
// extern u8 keyC1; //key1��ǰ״̬
// extern u8 keyP1; //key1ǰһ��״̬

/****************��������******************/
void KeyInit(void); //����IO��ʼ��
u8 KeyScan(void);  //����ɨ�躯��

void KeyNavInit(void); //����������ʼ��
u16 GetNavAdc(u8 ch); //��ȡADC
u8 ScanNavKey(u8 ch); //ɨ���жϵ�������


#endif
