#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "stm32f4xx.h"
#include "flexible_button.h"

typedef enum {
    USER_BUTTON_1,
    USER_BUTTON_2,
    USER_BUTTON_3,
    USER_BUTTON_MAX
} UserButton_t;

void Button_Config(void);

#endif  /* __BSP_KEY_H__ */
