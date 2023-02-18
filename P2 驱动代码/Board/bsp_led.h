#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f4xx.h"

typedef enum
{
    USER_LED_1,
    USER_LED_2,
    USER_LED_3,
    USER_LED_AMX
} UserLed_t;

extern void LED_Config(void);
extern void LED_ON(UserLed_t led);
extern void LED_OFF(UserLed_t led);

#endif /* __BSP_LED_H__ */
