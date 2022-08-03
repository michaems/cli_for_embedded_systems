#include <cli_custom_commands.h>

cmd_t cmd_tbl[] =
{
    { .cmd = "help", .func = help_func },
    { .cmd = "blink", .func = blink_func },
    { .cmd ="set_msg_type", .func = set_msgtype },
    { .cmd = "unset_msg_type", .func = unset_msgtype }
};

cli_t cli =
{
    .println = user_uart_println,
    .cmd_tbl = cmd_tbl,
    .cmd_cnt = sizeof(cmd_tbl) / sizeof(cmd_t)
};

void user_uart_println(const char *string)
{
    HAL_UART_Transmit(&huart3, (const uint8_t*) string, strlen(string), 1000);
}

void user_uart_println_1(const char *string)
{
    HAL_UART_Transmit(&huart1, (const uint8_t*) string, strlen(string), 1000);
}

cli_status_t help_func(int argc, char **argv)
{
    cli.println(CMD_LINEFEED);
    cli.println("HELP function executed ...");
    log_print_msg(MSG_TYPE_TRACE, MSG_SUBTYPE_1, "In the heart of HELP function");
    return CLI_OK;
}

cli_status_t set_msgtype(int argc, char **argv)
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

cli_status_t unset_msgtype(int argc, char **argv)
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
        log_print_msg(MSG_TYPE_DEBUG, MSG_SUBTYPE_1, "BLINK executed without any argument ...");
    }
    return CLI_OK;
}
