#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#define LED_ON_LEVEL    Bit_RESET
#define LED_OFF_LEVEL   Bit_SET

typedef enum {
    LED1,
    LED2,
    LED3,
    LED_ALL,
    LED_MAX = LED_ALL
} LED_Typedef;

void LED_Config(void);
void LED_ON(LED_Typedef led);
void LED_OFF(LED_Typedef led);

#endif  /* __BSP_LED_H__ */
