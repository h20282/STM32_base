#ifndef __LED_H
#define __LED_H

#define  LED_PORT         GPIOE        //LED�˿�
#define  LED_PIN          GPIO_Pin_8   //LEDλ


void LED_init(void);
void LED_ON(void);
void LED_OFF(void);

#endif

