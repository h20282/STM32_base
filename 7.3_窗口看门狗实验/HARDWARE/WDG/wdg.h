#ifndef __WDG_H
#define __WDG_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//���Ź� ��������		   
////////////////////////////////////////////////////////////////////////////////// 	  

void IWDG_Init(u8 prer,u16 rlr);	 //��ʼ��IWDG
void IWDG_Feed(void);				 //IWDGι��
void WWDG_Init(u8 tr,u8 wr,u8 fprer);//��ʼ��WWDG
void WWDG_Set_Counter(u8 cnt);       //����WWDG�ļ�����
#endif




























