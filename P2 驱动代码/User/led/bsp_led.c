#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "bsp_led.h"

void LED_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOF, &GPIO_InitStructure);
    LED_OFF(LED_ALL);
}

void LED_ON(LED_Typedef led)
{
    switch (led) {
        case LED1:
            GPIO_WriteBit(GPIOF, GPIO_Pin_8, LED_ON_LEVEL);
            break;
        case LED2:
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, LED_ON_LEVEL);
            break;
        case LED3:
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, LED_ON_LEVEL);
            break;
        case LED_ALL:
            GPIO_WriteBit(GPIOF, GPIO_Pin_8, LED_ON_LEVEL);
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, LED_ON_LEVEL);
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, LED_ON_LEVEL);
            break;
        default:
            break;
    }
}

void LED_OFF(LED_Typedef led)
{
    switch (led) {
        case LED1:
            GPIO_WriteBit(GPIOF, GPIO_Pin_8, LED_OFF_LEVEL);
            break;
        case LED2:
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, LED_OFF_LEVEL);
            break;
        case LED3:
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, LED_OFF_LEVEL);
            break;
        case LED_ALL:
            GPIO_WriteBit(GPIOF, GPIO_Pin_8, LED_OFF_LEVEL);
            GPIO_WriteBit(GPIOF, GPIO_Pin_9, LED_OFF_LEVEL);
            GPIO_WriteBit(GPIOF, GPIO_Pin_10, LED_OFF_LEVEL);
            break;
        default:
            break;
    }
}
