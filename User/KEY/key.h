#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define KEY1_PIN GPIO_Pin_4
#define KEY2_PIN GPIO_Pin_5
#define KEY3_PIN GPIO_Pin_6

void Init_LED(void);
void Init_KEY(void);
void Init_BEEP(void);

#endif //__KEY_H_
