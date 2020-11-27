#ifndef LOX_DEF_H
#define LOX_DEF_H
#include <stdio.h>
#include "lox_opcode.h"

enum lox_error_code
{
    LOX_OK,
    LOX_NO_MEM,
    LOX_INVALID,
    LOX_NO_EXIST,
    LOX_EXIST,
};
#define LOX_ERROR(err) (-err)

#define lox_error(...) printf("[Error]:" __VA_ARGS__)
#define lox_info(...)  printf("[Info]:" __VA_ARGS__)
#define lox_debug(...)  printf("[Debug]:" __VA_ARGS__)

enum lox_tag_type
{
    LOX_TYPE_INVALID,
    LOX_NUMBER,
    LOX_STRING,
    LOX_ARRAY,
    LOX_NIL,
    LOX_TRUE,
    LOX_FALSE,
    LOX_FUNCTION,
};

struct lox_vector_value
{
    struct lox_vector_value *next;
    struct lox_object *vec_v;
};

struct lox_vector
{
    int counter;
    int len;
    struct lox_vector_value vec_head;
};


struct lox_function
{
    int  is_inner_function;

    int func_def_args_cnt;
    int func_call_args_index;
    char func_args_names[100][LOX_VAR_MAX_NAME_LEN];
    long func_args[100];

    int  func_code_len;
    int  func_code_index;

    struct lox_cmd *func_code;
};

struct lox_object_value
{
    float v_f;
    char *v_str;
    struct lox_vector *v_vec;
    struct lox_function *v_func;
};

struct lox_object
{
    int o_tag;
    int o_is_array_object;
    int o_array_object_counter;
    int o_counter;
    struct lox_object_value o_value;
};

struct lox_symbol
{
    unsigned long sym_label_value;
    char sym_name[LOX_VAR_MAX_NAME_LEN];
    struct lox_object *sym_obj;
};


#endif // LOX_TYPE_H
