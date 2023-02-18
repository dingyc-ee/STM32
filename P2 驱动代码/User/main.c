/**
 ******************************************************************************
 * @file    Project/STM32F4xx_StdPeriph_Templates/main.c
 * @author  MCD Application Team
 * @version V1.8.1
 * @date    27-January-2022
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Template_Project
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TaskHandle_t led_task_hd;
TaskHandle_t terminal_task_hd;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void led_task( void * pv)
{
    while (1) {
        LED_ON(LED_1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        LED_OFF(LED_1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void terminal_task( void * pv)
{
    char str[128];

    while (1) {
        printf("Input:");
        scanf("%s", str);
        printf("\r\nOutput:%s\r\n", str);
    }
}

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
    LED_Config();
    USART_Config();

    printf("This is stm32f407 + freertos + lwip project!\r\n");
    
    xTaskCreate( led_task, "led_task", 2 * 1024, NULL, configMAX_PRIORITIES - 1, &led_task_hd );
    xTaskCreate( terminal_task, "terminal_task", 2 * 1024, NULL, configMAX_PRIORITIES - 1, &terminal_task_hd );

    vTaskStartScheduler();
    return 0;
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
 * @}
 */
