#ifndef _FREERTOS_TASKS_H_
#define _FREERTOS_TASKS_H_

#include "cli_custom_commands.h"
#include "usart.h"

#include "FreeRTOS.h"
#include "task.h"


void task_one(void *arg);
void task_two(void *arg);

void os_create_required_tasks(void);

#endif /* _FREERTOS_TASKS_H_ */
