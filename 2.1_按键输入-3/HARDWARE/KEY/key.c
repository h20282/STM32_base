#include "key.h"
#include "delay.h"
//�������� ��������		   
//PC0.1.2 ���ó�����
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFFF000; //PC0-2���ó�����	  
	GPIOC->CRL|=0X00000444; //������������߸������붼���ԣ�ģ�����벻�С�
	//GPIOC->ODR|=0x7;        //��������//ODR��λֵΪ0��ȱʡΪ�������롣
} 
//����������
//���ذ���ֵ
//0��û���κΰ�������
//1��KEY1����
//2��KEY2����
//3��KEY3����
//ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3!!
u8 KEY_Scan(void)
{
	
	static u8 key_up=1;//�������ɿ���־
	//return (KEY1==0)*1+(KEY2==0)*2+(KEY3==0)*3;
	if(key_up && (KEY1==0 || KEY2==0 || KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)
		{
			return 1;
		}
		else if(KEY2==0)
		{
			return 2;
		}
		else if(KEY3==0)
		{
			return 3;
		}
	}
	else if(KEY1==1 && KEY2==1 && KEY3==1)
		key_up=1;
	
	return 0;// �ް�������
}




















