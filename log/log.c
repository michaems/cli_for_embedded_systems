#include "log.h"


static msg_obj_st msg_object =
{
    .msg_type = MSG_TYPE_INFO,
    .msg_subtype = MSG_SUBTYPE_1,
    .print_to_terminal = NULL
};

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

    va_list args;

    va_start(args, msg);

    vsprintf(formated_str, msg, args);

    va_end(args);

    if (msg_object.print_to_terminal != NULL)
    {
        msg_object.print_to_terminal(formated_str);
    }
}
