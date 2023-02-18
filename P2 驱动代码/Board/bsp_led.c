#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "bsp_led.h"

void LED_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_WriteBit(GPIOF, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10, Bit_SET);
}

void LED_ON(UserLed_t led)
{
    switch (led)
    {
    case USER_LED_1:
        GPIO_WriteBit(GPIOF, GPIO_Pin_8, Bit_RESET);
        break;
    case USER_LED_2:
        GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_RESET);
        break;
    case USER_LED_3:
        GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_RESET);
        break;
    case USER_LED_AMX:
        GPIO_WriteBit(GPIOF, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10, Bit_RESET);
        break;
    default:
        break;
    }
}

void LED_OFF(UserLed_t led)
{
    switch (led)
    {
    case USER_LED_1:
        GPIO_WriteBit(GPIOF, GPIO_Pin_8, Bit_SET);
        break;
    case USER_LED_2:
        GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_SET);
        break;
    case USER_LED_3:
        GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_SET);
        break;
    case USER_LED_AMX:
        GPIO_WriteBit(GPIOF, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10, Bit_SET);
        break;
    default:
        break;
    }
}
