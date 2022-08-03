#include "freertos_tasks.h"

extern char rx_buf[1];

extern cli_t cli;

void os_create_required_tasks(void)
{
    /* create task_one */
    BaseType_t ret_val = xTaskCreate(task_one, "task_one", 256,
                                     NULL, tskIDLE_PRIORITY + 2, NULL);
    assert_param(ret_val);

    ret_val = xTaskCreate(task_two, "task_two", 128,
                          NULL, tskIDLE_PRIORITY + 1, NULL);
    assert_param(ret_val);

    (void)ret_val;
}

void task_one(void *arg)
{
    for( ;; )
    {
        HAL_UART_Receive_IT(&huart3, (uint8_t*) rx_buf, 1);
        cli_process(&cli);
        rx_buf[0] = 0;
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void task_two(void *arg)
{
    for( ;; )
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //cli.println(".");
    }
}


