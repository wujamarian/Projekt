
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "codec.h"
#include "sound.h"
#include "music.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ; // struktura timer�w
NVIC_InitTypeDef NVIC_InitStructure ; // struktura przerwa�
EXTI_InitTypeDef EXTI_InitStructure; // struktura przerwa�
GPIO_InitTypeDef GPIO_InitStructure; // struktura gpio

volatile uint32_t sampleCounter = 0;
volatile int16_t sample = 0;
