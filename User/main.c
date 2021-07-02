#include "delay.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "pwm.h"
#include "stm32f4xx.h"
#include "timer.h"
#include "uart.h"

#define lab7 0

int key1 = 0, key2 = 0, key3 = 0;

void lab1() {
  GPIO_ResetBits(GPIOE, LED1_PIN);
  GPIO_ResetBits(GPIOE, LED2_PIN);
  GPIO_ResetBits(GPIOE, LED3_PIN);
}

void lab2() {
  GPIO_SetBits(GPIOE, LED3_PIN);
  GPIO_ResetBits(GPIOE, LED1_PIN);
  delay_ms(1500);
  GPIO_ResetBits(GPIOE, LED2_PIN);
  GPIO_SetBits(GPIOE, LED1_PIN);
  delay_ms(1500);
  GPIO_ResetBits(GPIOE, LED3_PIN);
  GPIO_SetBits(GPIOE, LED2_PIN);
  delay_ms(1500);
}

void lab3() {
  GPIO_SetBits(GPIOE, LED3_PIN);
  GPIO_ResetBits(GPIOE, LED1_PIN);
  GPIO_SetBits(GPIOB, BEEP_PIN);
  delay_ms(1500);
  GPIO_ResetBits(GPIOB, BEEP_PIN);
  delay_ms(1500);
  GPIO_ResetBits(GPIOE, LED2_PIN);
  GPIO_SetBits(GPIOE, LED1_PIN);
  GPIO_SetBits(GPIOB, BEEP_PIN);
  delay_ms(1500);
  GPIO_ResetBits(GPIOB, BEEP_PIN);
  delay_ms(1500);
  GPIO_ResetBits(GPIOE, LED3_PIN);
  GPIO_SetBits(GPIOE, LED2_PIN);
  GPIO_SetBits(GPIOB, BEEP_PIN);
  delay_ms(1500);
  GPIO_ResetBits(GPIOB, BEEP_PIN);
  delay_ms(1500);
}

void lab4() {
  if (!GPIO_ReadInputDataBit(GPIOE, KEY1_PIN)) {
    delay_ms(1500);
    GPIO_ResetBits(GPIOE, LED1_PIN);
    delay_ms(1500);
    GPIO_SetBits(GPIOE, LED1_PIN);
  }
  if (!GPIO_ReadInputDataBit(GPIOE, KEY2_PIN)) {
    delay_ms(1500);
    GPIO_ResetBits(GPIOE, LED2_PIN);
    delay_ms(1500);
    GPIO_SetBits(GPIOE, LED2_PIN);
  }
  if (!GPIO_ReadInputDataBit(GPIOE, KEY3_PIN)) {
    delay_ms(1500);
    GPIO_ResetBits(GPIOE, LED3_PIN);
    delay_ms(1500);
    GPIO_SetBits(GPIOE, LED3_PIN);
  }
  delay_ms(1500);
}

void lab5() {
  if (!GPIO_ReadInputDataBit(GPIOE, KEY1_PIN)) {
    delay_ms(1500);
    if (!key1) {
      GPIO_ResetBits(GPIOE, LED1_PIN);
      GPIO_SetBits(GPIOB, BEEP_PIN);
      key1 = 1;
    } else {
      GPIO_SetBits(GPIOE, LED1_PIN);
      GPIO_ResetBits(GPIOB, BEEP_PIN);
      key1 = 0;
    }
  }
  if (!GPIO_ReadInputDataBit(GPIOE, KEY2_PIN)) {
    delay_ms(1500);
    if (!key2) {
      GPIO_ResetBits(GPIOE, LED2_PIN);
      GPIO_SetBits(GPIOB, BEEP_PIN);
      key2 = 1;
    } else {
      GPIO_SetBits(GPIOE, LED2_PIN);
      GPIO_ResetBits(GPIOB, BEEP_PIN);
      key2 = 0;
    }
  }
  if (!GPIO_ReadInputDataBit(GPIOE, KEY3_PIN)) {
    delay_ms(1500);
    if (!key3) {
      GPIO_ResetBits(GPIOE, LED3_PIN);
      GPIO_SetBits(GPIOB, BEEP_PIN);
      key3 = 1;
    } else {
      GPIO_SetBits(GPIOE, LED3_PIN);
      GPIO_ResetBits(GPIOB, BEEP_PIN);
      key3 = 0;
    }
  }
  delay_ms(1500);
}

void lab6() {
  delay_ms(250);
  GPIO_ResetBits(GPIOE, LED1_PIN);
  delay_ms(250);
  GPIO_SetBits(GPIOE, LED1_PIN);
}

int main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
#if lab7
  u16 led0pwmval = 0;
  u8 dir = 1;
#endif
  // Init_LED();
  // Init_KEY();
  // Init_BEEP();
  // EXTI_Config();
  delay_init(168);
  // uart_init();

  //这里时钟选择为APB1的2倍，而APB1为36M
  // tim2_init(4999, 7199); // 10Khz的计数频率，计数到5000为500ms
  // tim3_init(4999, 7199);
  // tim4_init(4999, 7199);

  // TIM1_PWM_Init(500 - 1, 84 - 1);
  // TIM2_PWM_Init(500 - 1, 84 - 1);
	TIM4_PWM_Init(200 - 1, 8400 - 1);

  while (1) {
		delay_ms(10);	 
		TIM_SetCompare1(TIM4, 175);	//修改比较值，修改占空比对应180度
		
		delay_ms(10);	 
		TIM_SetCompare1(TIM4, 180);	//修改比较值，修改占空比对应180度
		
		delay_ms(10);	 
		TIM_SetCompare1(TIM4, 185);	//修改比较值，修改占空比对应180度
		
		delay_ms(10);	 
		TIM_SetCompare1(TIM4, 190);	//修改比较值，修改占空比对应180度
		delay_ms(10);	 
		TIM_SetCompare1(TIM4, 195);	//修改比较值，修改占空比对应180度
    // lab7(led0pwmval, dir);
    //  LED1 = !LED1;
    //   delay_ms(500);
    // lab1();
    // lab2();
    // lab3();
    // lab4();
    // lab5();
    // lab6();
		
#if lab7
    delay_ms(10);
    // dir==1 led0pwmval递增
    if (dir)
      led0pwmval++;
    else // dir==0 led0pwmval递减
      led0pwmval--;
    // led0pwmval到达300后，方向为递减
    if (led0pwmval > 450)
      dir = 0;
    // led0pwmval递减到0后，方向改为递增
    if (led0pwmval == 0)
      dir = 1;
    //修改比较值，修改占空比
    TIM_SetCompare1(TIM1, led0pwmval);
    // TIM_SetCompare3(TIM2, led0pwmval);
#endif
  }
}
