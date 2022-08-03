#ifndef INC_CLI_CUSTOM_COMMANDS_H_
#define INC_CLI_CUSTOM_COMMANDS_H_

#include "cli_defs.h"
#include "cli.h"
#include "log.h"
#include "string.h"
#include "usart.h"


cli_status_t help_func(int argc, char **argv);
cli_status_t blink_func(int argc, char **argv);
void user_uart_println(const char *string);
void user_uart_println_1(const char *string);

cli_status_t set_msgtype(int argc, char **argv);
cli_status_t unset_msgtype(int argc, char **argv);

#endif /* INC_CLI_CUSTOM_COMMANDS_H_ */
