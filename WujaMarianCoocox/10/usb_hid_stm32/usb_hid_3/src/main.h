
#ifndef __STM32F4_DISCOVERY_USB_HID_H
#define __STM32F4_DISCOVERY_USB_HID_H

#include "stm32f4_discovery.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "codec.h"
#include "sound.h"
#include "music.h"

#define ABS(x)         (x < 0) ? (-x) : x
#define MAX(a,b)       (a < b) ? (b) : a

void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);
void Fail_Handler(void);

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ; // struktura timerów
NVIC_InitTypeDef NVIC_InitStructure ; // struktura przerwañ
EXTI_InitTypeDef EXTI_InitStructure; // struktura przerwañ
GPIO_InitTypeDef GPIO_InitStructure; // struktura gpio

volatile uint32_t sampleCounter = 0;
volatile int16_t sample = 0;


#endif
