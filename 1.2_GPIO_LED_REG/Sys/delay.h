#ifndef __DELAY_H
#define __DELAY_H 			   
#include <stm32f10x_map.h>
#include <stm32f10x_nvic.h>
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//********************************************************************************
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!
////////////////////////////////////////////////////////////////////////////////// 
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif




























