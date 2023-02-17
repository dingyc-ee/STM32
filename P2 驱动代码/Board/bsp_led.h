#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f4xx.h"

typedef enum
{
    LED_1,
    LED_2,
    LED_3,
    LED_MAX
} LED_Typedef;

extern void LED_Init(void);
extern void LED_ON(LED_Typedef led);
extern void LED_OFF(LED_Typedef led);

#endif /* __BSP_LED_H__ */
