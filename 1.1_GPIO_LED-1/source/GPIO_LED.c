typedef unsigned long  u32;

#define RCC_APB2ENR ((u32 *)0x40021018)  //定义APB2ENR寄存器    地址
#define AFIO_MAPR   ((u32 *)0x40010004)  //定义APIO的MAPR寄存器

#define GPIOB_CRL (*(u32 *)0x40010C00)    //定义GPIOB_CRL寄存器  值
#define GPIOB_ODR (*(u32 *)0x40010C0C)    //定义GPIOB_ODR寄存器
#define GPIOE_CRH (*(u32 *)0x40011804)    //定义GPIOE_CRH寄存器
#define GPIOE_ODR (*(u32 *)0x4001180C)    //定义GPIOE_ODR寄存器
u32 *gpio_odr=((u32 *)0x4001180c);        //定义成地址变量
	
u32 *PEO8 = (u32 *)(0x42000000 +(0x4001180C-0x40000000)*32 + 8*4);  //位带定义PE08
u32 *PEO9 = (u32 *)(0x42000000 +(0x4001180C-0x40000000)*32 + 9*4);  //位带定义PE09

int delay(int Time)
{ //简单延时程序
	unsigned short t,i,j;
	for(t=0;t<Time;t++)
		// for(i=0;i<1000;i++)
			for(j=0;j<1000;j++)
				;
	return 0;
}

void set_by_bit(u32* base, u32 idx, u32 value) {
	if (value==1)
		(*base) = (*base) | (1 << idx);
	else
		(*base) = (*base) & (~(1 << idx));
}


int  main(void)
{
	u32 i;
	*RCC_APB2ENR|=1<<0;	//使能AFIO
	*RCC_APB2ENR|=1<<3; //使能PORTB时钟
	*RCC_APB2ENR|=1<<6;	//使能PORTE时钟

	*AFIO_MAPR |= 0x02000000; //设置PB.3为I/O口可用，且可以SW仿真

	GPIOB_CRL &= 0xFFFF0FFF; //清除PB.3原先配置
	GPIOB_CRL = GPIOB_CRL | 0x00003000; //PB.3配置为推挽输出
	GPIOB_ODR |= 0x00000008; //PB.3输出高，选择控制LED灯
	
	GPIOE_CRH &=0X00000000;  //清除PE.8-15原先配置
	GPIOE_CRH |= 0X33333333; //PE.8-15配置为推挽输出
	GPIOE_ODR |= 0x0000FF00; //PE.8-15输出高，八个LED灯全亮

	delay(2);

	while(1)
	{
		for(i=0; i<8; i++) {
			set_by_bit(&GPIOE_ODR, 8+i, 1);
			delay(1);
			set_by_bit(&GPIOE_ODR, 8+i, 0);
			// GPIOE_ODR = 1<<(i+8);
			// delay(1);
		}
		// for(i=0; i<8; i++) {
		// 	set_by_bit(&GPIOE_ODR, 8+i, 0);delay(1);
		// 	// GPIOE_ODR = 1<<(i+8);
		// 	// delay(1);
		// }
		// set_by_bit(&GPIOE_ODR, 8, 1);delay(5);
		// set_by_bit(&GPIOE_ODR, 9, 1);delay(2);
		// set_by_bit(&GPIOE_ODR, 10, 1);delay(2);
		// set_by_bit(&GPIOE_ODR, 11, 1);delay(2);
		// set_by_bit(&GPIOE_ODR, 12, 1);delay(2);
		// set_by_bit(&GPIOE_ODR, 13, 1);delay(2);
		// set_by_bit(&GPIOE_ODR, 14, 1);delay(2);
		// set_by_bit(&GPIOE_ODR, 15, 1);delay(2);

		// GPIOE_ODR = 0x00000100; //仅LED1亮，其他灯灭
		// delay(2);
		// *PEO8 = 0;  //LED1灭
		// delay(2);
		// *PEO8 = 1;  //LED1亮
		// delay(2);
		// *PEO9 = 1;  //LED2亮
		// delay(2);
		// GPIOE_ODR = 0x00000400; //仅LED3亮，其他灯灭
		// delay(2);
		// GPIOE_ODR = 0x00000800; //仅LED4亮，其他灯灭
		// delay(2);
		// GPIOE_ODR = 0x00001000; //仅LED5亮，其他灯灭
		// delay(2);
		// GPIOE_ODR = 0x00002000; //仅LED6亮，其他灯灭
		// delay(2);
		// (*(u32 *)0x4001180C) = 0x00004000; //仅LED7亮，其他灯灭
		// delay(2);
		// *gpio_odr = 0x00008000; //仅LED8亮，其他灯灭
		// delay(2);
	}
	//永远不会执行到这
	return 0;
}

