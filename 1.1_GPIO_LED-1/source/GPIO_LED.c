typedef unsigned long  u32;

#define RCC_APB2ENR ((u32 *)0x40021018)  //����APB2ENR�Ĵ���    ��ַ
#define AFIO_MAPR   ((u32 *)0x40010004)  //����APIO��MAPR�Ĵ���

#define GPIOB_CRL (*(u32 *)0x40010C00)    //����GPIOB_CRL�Ĵ���  ֵ
#define GPIOB_ODR (*(u32 *)0x40010C0C)    //����GPIOB_ODR�Ĵ���
#define GPIOE_CRH (*(u32 *)0x40011804)    //����GPIOE_CRH�Ĵ���
#define GPIOE_ODR (*(u32 *)0x4001180C)    //����GPIOE_ODR�Ĵ���
u32 *gpio_odr=((u32 *)0x4001180c);        //����ɵ�ַ����
	
u32 *PEO8 = (u32 *)(0x42000000 +(0x4001180C-0x40000000)*32 + 8*4);  //λ������PE08
u32 *PEO9 = (u32 *)(0x42000000 +(0x4001180C-0x40000000)*32 + 9*4);  //λ������PE09

int delay(int Time)
{ //����ʱ����
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
	*RCC_APB2ENR|=1<<0;	//ʹ��AFIO
	*RCC_APB2ENR|=1<<3; //ʹ��PORTBʱ��
	*RCC_APB2ENR|=1<<6;	//ʹ��PORTEʱ��

	*AFIO_MAPR |= 0x02000000; //����PB.3ΪI/O�ڿ��ã��ҿ���SW����

	GPIOB_CRL &= 0xFFFF0FFF; //���PB.3ԭ������
	GPIOB_CRL = GPIOB_CRL | 0x00003000; //PB.3����Ϊ�������
	GPIOB_ODR |= 0x00000008; //PB.3����ߣ�ѡ�����LED��
	
	GPIOE_CRH &=0X00000000;  //���PE.8-15ԭ������
	GPIOE_CRH |= 0X33333333; //PE.8-15����Ϊ�������
	//GPIOE_ODR |= 0x0000FF00; //PE.8-15����ߣ��˸�LED��ȫ��
	GPIOE_ODR = 0x00000000; //PE.8-15����ͣ��˸�LED��ȫ��
	
	delay(2);
	
	while(1)
	{
		for(i=0; i<8; i++) {
			set_by_bit(&GPIOE_ODR, 8+i, 1);
			delay(100*(i+1));
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

		// GPIOE_ODR = 0x00000100; //��LED1������������
		// delay(2);
		// *PEO8 = 0;  //LED1��
		// delay(2);
		// *PEO8 = 1;  //LED1��
		// delay(2);
		// *PEO9 = 1;  //LED2��
		// delay(2);
		// GPIOE_ODR = 0x00000400; //��LED3������������
		// delay(2);
		// GPIOE_ODR = 0x00000800; //��LED4������������
		// delay(2);
		// GPIOE_ODR = 0x00001000; //��LED5������������
		// delay(2);
		// GPIOE_ODR = 0x00002000; //��LED6������������
		// delay(2);
		// (*(u32 *)0x4001180C) = 0x00004000; //��LED7������������
		// delay(2);
		// *gpio_odr = 0x00008000; //��LED8������������
		// delay(2);
	}
	//��Զ����ִ�е���
	return 0;
}

