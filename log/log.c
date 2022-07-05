#include "log.h"


static msg_obj_st msg_object =
{
    .msg_type = MSG_TYPE_INFO,
    .msg_subtype = MSG_SUBTYPE_1,
    .print_to_terminal = NULL
};

static char *msg_type_str[] =
{
    "INFO",
    "TRACE",
    "DEBUG",
    "WARNING",
    "ERROR",
    "FATAL",
    "NONE"
};

static bool get_msgtype_as_str(msg_type_t msg_type, char *msgtype_str)
{
    bool msgtype_found = false;

    switch (msg_type)
    {
        case MSG_TYPE_INFO:
            strcpy(msgtype_str, msg_type_str[0]);
            msgtype_found = true;
            break;
        case MSG_TYPE_TRACE:
            strcpy(msgtype_str, msg_type_str[1]);
            msgtype_found = true;
            break;
        case MSG_TYPE_DEBUG:
            strcpy(msgtype_str, msg_type_str[2]);
            msgtype_found = true;
            break;
        case MSG_TYPE_WARNING:
            strcpy(msgtype_str, msg_type_str[3]);
            msgtype_found = true;
            break;
        case MSG_TYPE_ERROR:
            strcpy(msgtype_str, msg_type_str[4]);
            msgtype_found = true;
            break;
        case MSG_TYPE_FATAL:
            strcpy(msgtype_str, msg_type_str[5]);
            msgtype_found = true;
            break;
        default:
            break;
    }

    return msgtype_found;
}

void log_set_msg_type(msg_type_t msg_type, bool set)
{
    if ((msg_type < MSG_TYPE_INFO) || (msg_type > MSG_TYPE_NONE))
    {
        return;
    }

    if (set)
    {
        msg_object.msg_type |= msg_type;
    }
    else
    {
       msg_object.msg_type &= ~(msg_type);
    }
}

void log_set_msg_subtype(msg_subtype_t msg_subtype, bool set)
{
    if ((msg_subtype < MSG_SUBTYPE_1) || (msg_subtype > MSG_SUBTYPE_16))
    {
        return;
    }

    if (set)
    {
        msg_object.msg_subtype |= msg_subtype;
    }
    else
    {
       msg_object.msg_subtype &= ~(msg_subtype);
    }
}

void log_set_msg_print_fn(println_ptr_t print_fn)
{
    if (print_fn != NULL)
    {
        msg_object.print_to_terminal = print_fn;
    }
}

void log_print_msg(msg_type_t msg_type, msg_subtype_t msg_subtype, char *msg, ...)
{
    if (!(msg_object.msg_type & msg_type))
    {
        return;
    }

    if (!(msg_object.msg_subtype & msg_subtype))
    {
        return;
    }

    char formated_str[128] = {0};
    char final_str_to_print[150] = {0};
    va_list args;

    va_start(args, msg);

    vsprintf(formated_str, msg, args);

    va_end(args);
    char msg_type_str[10] = {0};
    bool msgtype_found = get_msgtype_as_str(msg_type, msg_type_str);
    strcpy(final_str_to_print, "\r\n");
    if (msgtype_found)
    {
        strcat(final_str_to_print, msg_type_str);
        strcat(final_str_to_print, ": ");
        strcat(final_str_to_print, formated_str);
    }
    else
    {
        strcat(final_str_to_print, formated_str);
    }

    if (msg_object.print_to_terminal != NULL)
    {
        msg_object.print_to_terminal(final_str_to_print);
    }
}
