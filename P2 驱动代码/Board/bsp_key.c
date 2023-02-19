#include <stdio.h>
#include <string.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "bsp_key.h"
#include "FreeRTOS.h"
#include "task.h"

#define ENUM_TO_STR(e) (#e)

static char *enum_event_string[] = {
    ENUM_TO_STR(FLEX_BTN_PRESS_DOWN),
    ENUM_TO_STR(FLEX_BTN_PRESS_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_DOUBLE_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_REPEAT_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_MAX),
    ENUM_TO_STR(FLEX_BTN_PRESS_NONE),
};

static char *enum_btn_id_string[] = {
    ENUM_TO_STR(USER_BUTTON_1),
    ENUM_TO_STR(USER_BUTTON_2),
    ENUM_TO_STR(USER_BUTTON_3),
    ENUM_TO_STR(USER_BUTTON_MAX),
};

static ButtonCallback user_button_callback = NULL;

static flex_button_t user_button[USER_BUTTON_MAX];

static uint8_t common_btn_read(void *arg)
{
    uint8_t value = 0;

    flex_button_t *btn = (flex_button_t *)arg;

    switch (btn->id)
    {
    case USER_BUTTON_1:
        value = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4);
        break;
    case USER_BUTTON_2:
        value = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3);
        break;
    case USER_BUTTON_3:
        value = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2);
        break;
    default:
        break;
    }

    return value;
}

static void common_btn_evt_cb(void *arg)
{
    flex_button_t *btn = (flex_button_t *)arg;

    printf("id: [%d - %s]  event: [%d - %30s]  repeat: %d\r\n", 
        btn->id, enum_btn_id_string[btn->id],
        btn->event, enum_event_string[btn->event],
        btn->click_cnt);
    
    if (user_button_callback) {
        user_button_callback((UserButton_t)(btn->id), (flex_button_event_t)(btn->event));
    }
}

static void button_scan(void *arg)
{
    while(1) {
        flex_button_scan();
        vTaskDelay(20 / portTICK_PERIOD_MS); // 20 ms
    }
}

void Button_Config(void)
{
    int i;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    memset(&user_button[0], 0x0, sizeof(user_button));

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(GPIOE, &GPIO_InitStructure);

    for (i = 0; i < USER_BUTTON_MAX; i++) {
        user_button[i].id = i;
        user_button[i].usr_button_read = common_btn_read;
        user_button[i].cb = common_btn_evt_cb;
        user_button[i].pressed_logic_level = 0;
        user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(1500);
        user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(3000);
        user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(4500);

        flex_button_register(&user_button[i]);
    }

    xTaskCreate(button_scan, "button_scan", 1024, NULL, 0, NULL);
}

void Button_RegisterCallback(ButtonCallback btn_cb)
{
    user_button_callback = btn_cb;
}
