#ifndef __UART_H_
#define __UART_H_
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_usart.h"

void uart_init(void);

#endif // __UART_H_
