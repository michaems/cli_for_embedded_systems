/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"
#include "cli.h"
#include "cli_defs.h"
#include "log.h"

void SystemClock_Config(void);

char rx_buf[1] = { 0 };

static cli_status_t help_func(int argc, char **argv);
static cli_status_t blink_func(int argc, char **argv);
static void user_uart_println(const char *string);

static cli_status_t set_msgtype(int argc, char **argv);
static cli_status_t unset_msgtype(int argc, char **argv);

cmd_t cmd_tbl[] =
{
    { .cmd = "help", .func = help_func },
    { .cmd = "blink", .func = blink_func },
    { .cmd = "set_msg_type", .func = set_msgtype },
    { .cmd = "unset_msg_type", .func = unset_msgtype }
};

cli_t cli;

int main(void)
{
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART3_UART_Init();

    cli.println = user_uart_println;
    cli.cmd_tbl = cmd_tbl;
    cli.cmd_cnt = sizeof(cmd_tbl) / sizeof(cmd_t);

    cli_init(&cli);

    /* log init */
    log_set_msg_print_fn(user_uart_println);

    while (1)
    {
        HAL_UART_Receive_IT(&huart3, (uint8_t*) rx_buf, 1);
        cli_process(&cli);
        rx_buf[0] = 0;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    cli_put(&cli, rx_buf[0]);
}

void user_uart_println(const char *string)
{
    HAL_UART_Transmit(&huart3, (const uint8_t*) string, strlen(string), 1000);
}

cli_status_t help_func(int argc, char **argv)
{
    cli.println(CMD_LINEFEED);
    cli.println("HELP function executed");
    log_print_msg(MSG_TYPE_TRACE, MSG_SUBTYPE_1, "In the heart of HELP function");
    return CLI_OK;
}

static cli_status_t set_msgtype(int argc, char **argv)
{
    cli_status_t status = CLI_OK;
    bool type_set = true;
    if (argc > 1)
    {
        if (((strcmp(argv[2], "false") == 0) || (strcmp(argv[2], "FALSE") == 0)))
        {
            type_set = false;
        }

        if (strcmp(argv[1], "INFO") == 0)
        {
            log_set_msg_type(MSG_TYPE_INFO, type_set);
        }
        else if (strcmp(argv[1], "TRACE") == 0)
        {
            log_set_msg_type(MSG_TYPE_TRACE, type_set);
        }
        else if (strcmp(argv[1], "DEBUG") == 0)
        {
            log_set_msg_type(MSG_TYPE_DEBUG, type_set);
        }
        else if (strcmp(argv[1], "WARNING") == 0)
        {
            log_set_msg_type(MSG_TYPE_WARNING, type_set);
        }
        else if (strcmp(argv[1], "ERROR") == 0)
        {
            log_set_msg_type(MSG_TYPE_ERROR, type_set);
        }
        else if (strcmp(argv[1], "FATAL") == 0)
        {
            log_set_msg_type(MSG_TYPE_FATAL, type_set);
        }
        else
        {
            status = CLI_E_INVALID_ARGS;
        }
    }

    return status;
}

static cli_status_t unset_msgtype(int argc, char **argv)
{
    cli_status_t status = CLI_OK;

    if (argc > 1)
    {
        if (strcmp(argv[1], "INFO") == 0)
        {
            log_set_msg_type(MSG_TYPE_INFO, false);
        }
        else if (strcmp(argv[1], "TRACE") == 0)
        {
            log_set_msg_type(MSG_TYPE_TRACE, false);
        }
        else if (strcmp(argv[1], "DEBUG") == 0)
        {
            log_set_msg_type(MSG_TYPE_DEBUG, false);
        }
        else if (strcmp(argv[1], "WARNING") == 0)
        {
            log_set_msg_type(MSG_TYPE_WARNING, false);
        }
        else if (strcmp(argv[1], "ERROR") == 0)
        {
            log_set_msg_type(MSG_TYPE_ERROR, false);
        }
        else if (strcmp(argv[1], "FATAL") == 0)
        {
            log_set_msg_type(MSG_TYPE_FATAL, false);
        }
        else
        {
            status = CLI_E_INVALID_ARGS;
        }
    }

    return status;
}

cli_status_t blink_func(int argc, char **argv)
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "-help") == 0)
        {
            cli.println(CMD_LINEFEED);
            cli.println("BLINK help menu");
            log_print_msg(MSG_TYPE_DEBUG, MSG_SUBTYPE_1, "BLINK executed with args. AGRC = %d",
                          argc);
        }
        else
        {
            return CLI_E_INVALID_ARGS;
        }
    }
    else
    {
        cli.println(CMD_LINEFEED);
        cli.println("BLINK function executed");
        log_print_msg(MSG_TYPE_DEBUG, MSG_SUBTYPE_1, "BLINK executed WITHOUT any arg ...");
    }
    return CLI_OK;
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
                                  | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART3;
    PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
