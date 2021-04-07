#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//LED驱动代码	   
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB3和PE8-15为输出口.并使能这两个口的时钟	    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //使能PE,PB端口时,而且打开复用时钟

	//改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能 否则PB3口不能使用
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;		 //PB.3 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.3
 GPIO_SetBits(GPIOB,GPIO_Pin_3);						     //PB.3 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	  //PE.8-15 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 						    //PB.8-15 输出高 
}
 
