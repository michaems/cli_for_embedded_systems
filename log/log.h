#ifndef _LOG_H_
#define _LOG_H_

#include "stdbool.h"
#include "stddef.h"

typedef enum msg_type_
{
    MSG_TYPE_INFO    = 0x01,
    MSG_TYPE_TRACE   = 0x02,
    MSG_TYPE_DEBUG   = 0x04,
    MSG_TYPE_WARNING = 0x08,
    MSG_TYPE_ERROR   = 0x10,
    MSG_TYPE_FATAL   = 0x20,
    MSG_TYPE_NONE    = 0x40
}msg_type_t;

typedef enum msg_subtype_
{
    MSG_SUBTYPE_1 = 0x01,
    MSG_SUBTYPE_2 = 0x02,
    MSG_SUBTYPE_3 = 0x04,
    MSG_SUBTYPE_4 = 0x08,
    MSG_SUBTYPE_5 = 0x10,
    MSG_SUBTYPE_6 = 0x20,
    MSG_SUBTYPE_7 = 0x40,
    MSG_SUBTYPE_8 = 0x80,
    MSG_SUBTYPE_9 = 0x100,
    MSG_SUBTYPE_10 = 0x200,
    MSG_SUBTYPE_11 = 0x400,
    MSG_SUBTYPE_12 = 0x800,
    MSG_SUBTYPE_13 = 0x1000,
    MSG_SUBTYPE_14 = 0x2000,
    MSG_SUBTYPE_15 = 0x4000,
    MSG_SUBTYPE_16 = 0x8000
}msg_subtype_t;

typedef void (*println_ptr_t)(const char *msg);

typedef struct msg_obj_
{
    uint16_t msg_type;
    uint16_t msg_subtype;
    println_ptr_t print_to_terminal;
}msg_obj_st;

void set_msg_type(msg_type_t msg_type, bool set);
void set_msg_subtype(msg_subtype_t msg_subtype, bool set);
void set_msg_print_fn(println_ptr_t print_fn);

void print_msg(char *msg, args...);

#endif /*_LOG_H_*/
