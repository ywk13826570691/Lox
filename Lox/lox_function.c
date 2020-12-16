#include <stdlib.h>
#include <string.h>
#include "lox_function.h"
#include "lox.h"
#include "lox_def.h"
#include "lox_opcode.h"
#include "lox_register.h"
#include "lox_config.h"
#include "lox_object.h"
#include "lox_lib.h"


struct lox_symbol *cur_parsing_function = NULL;
struct lox_function_calling *cur_calling_function = NULL;
struct lox_symbol *main_function = NULL;

int lox_function_index = 0;
int lox_function_total = 0;
long *lox_function_table;

int lox_function_parsing = 0;

int cur_calling_function_index = -1;
//long cur_calling_function_table[100];
struct lox_function_calling cur_calling_function_table[100];


int lox_function_init(void)
{
    lox_function_table = (long *)malloc(LOX_FUNCTION_TABLE_STEP * sizeof (long));
    lox_function_total += LOX_FUNCTION_TABLE_STEP;
    main_function = lox_new_function("main");
    lox_push_cur_calling_function((long)main_function);
    lox_lib_init();
    return LOX_OK;
}

int lox_register_func(struct lox_symbol *f)
{
    if (lox_function_index == lox_function_total)
    {
        lox_function_total += LOX_FUNCTION_TABLE_STEP;
        lox_function_table = realloc(lox_function_table, lox_function_total * sizeof (long));
    }
    lox_function_table[lox_function_index++] = (long)f;
    return LOX_OK;
}

long lox_find_function(char *name)
{
    int i = 0;
    long ret = LOX_ERROR(LOX_INVALID);
    for (i = 0; i < lox_function_index; i++)
    {
        struct lox_symbol *sym = (struct lox_symbol *)lox_function_table[i];
        if (strcmp(sym->sym_name, name) == 0)
        {
            ret = (long)sym;
            break;
        }
    }

    return ret;
}

long lox_find_function_by_addr(long f)
{
    int i = 0;
    long ret = LOX_ERROR(LOX_INVALID);
    for (i = 0; i < lox_function_index; i++)
    {
        struct lox_symbol *sym = (struct lox_symbol *)lox_function_table[i];
        if ((long)sym->sym_obj->o_value.v_func == f)
        {
            ret = (long)sym;
            break;
        }
    }

    return ret;
}

struct lox_symbol * lox_new_function(char *name)
{

    if (lox_find_function(name) > 0)
    {
        lox_error("Redefine function:%s\n", name);
        exit(0);
    }

    struct lox_symbol *sym = (struct lox_symbol *)malloc(sizeof (struct lox_symbol));
    struct lox_object *obj = lox_object_new_func();
    struct lox_function *fun = (struct lox_function *)malloc(sizeof (struct lox_function));

    memset(sym, 0, sizeof (struct lox_symbol));
    memset(fun, 0, sizeof (struct lox_function));

    sym->sym_obj = obj;

    strcpy(sym->sym_name, name);
    sym->sym_obj->o_value.v_func = fun;


    fun->is_inner_function = 0;
    fun->func_code = (struct lox_cmd *)malloc(LOX_FUNCTION_CODE_STEP * sizeof (struct lox_cmd));
    fun->func_code_len += LOX_FUNCTION_CODE_STEP;
    memset(fun->func_code, 0, LOX_FUNCTION_CODE_STEP * sizeof (struct lox_cmd));

    lox_set_cur_parsing_function((long)sym);

    lox_register_func(sym);
    return  sym;
}

struct lox_symbol * lox_get_cur_parsing_function()
{
    return cur_parsing_function;
}

int lox_cur_parsing_function_end(void)
{
    cur_parsing_function = main_function;
    lox_local_symbol_destory();
    return  LOX_OK;
}

int lox_set_cur_parsing_function(long f)
{
    cur_parsing_function = (struct lox_symbol *)f;
    return LOX_OK;
}

int lox_set_cur_calling_function(long f)
{
    cur_calling_function = (struct lox_function_calling *)f;
    return LOX_OK;
}

struct lox_function_calling *lox_get_cur_calling_function()
{
    return cur_calling_function;
}

int lox_push_cur_calling_function(long f)
{
    struct lox_function_calling *call_f = &cur_calling_function_table[cur_calling_function_index + 1 ];
    call_f->func = f;
    cur_calling_function_index++;
    lox_set_cur_calling_function((long)call_f);
    return LOX_OK;
}

int lox_pop_cur_calling_function(void)
{
    struct lox_function_calling *call_f = &cur_calling_function_table[cur_calling_function_index];
    call_f->argc = 0;
    call_f->func = 0;
    memset(call_f->args, 0, 1000*sizeof (long));
    memset(call_f->name, 0, 100);

    cur_calling_function_index--;
    lox_set_cur_calling_function((long)&cur_calling_function_table[cur_calling_function_index]);
    lox_info("****************************************:%d\n", cur_calling_function_index);
    return LOX_OK;
}

struct lox_symbol * lox_get_main_function(void)
{
    return  main_function;
}

int lox_func_push_cmd(struct lox_cmd *cmd)
{
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    struct lox_function *func = sym->sym_obj->o_value.v_func;

    if (func->func_code_index == func->func_code_len)
    {
        func->func_code_len += LOX_FUNCTION_CODE_STEP;
        func->func_code = realloc(func->func_code, func->func_code_len * sizeof (struct lox_cmd));
    }

    memcpy(&func->func_code[func->func_code_index], cmd, sizeof (struct lox_cmd));

    func->func_code_index++;
    return LOX_OK;
}

int lox_func_add_arg_name(char *name)
{
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    struct lox_function *func = sym->sym_obj->o_value.v_func;
    strcpy(func->func_args_names[func->func_def_args_cnt], name);
    func->func_def_args_cnt++;
    lox_info("----func add args:%s %d %s\n", sym->sym_name, func->func_def_args_cnt, name);
    return LOX_OK;
}

int lox_func_push_arg_label(long label)
{
    struct lox_function_calling *cur_calling_func = lox_get_cur_calling_function();
    cur_calling_func->args[cur_calling_func->argc] = label;
    cur_calling_func->argc++;
    return LOX_OK;
}

int lox_func_check_args(long f)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_function_calling *call_f = (struct lox_function_calling *)f;
    struct lox_symbol *sym = (struct lox_symbol *)call_f->func;
    struct lox_function *func = sym->sym_obj->o_value.v_func;

    if (func->is_inner_function)
    {
        if (func->func_def_args_cnt != 1000)
        {
            if (func->func_def_args_cnt != call_f->argc )
            {
                lox_error("----function %s args not equal line:%d %d %d\n", sym->sym_name, lox_cur_line_number(), func->func_def_args_cnt
                          ,func->func_call_args_index);
                exit(0);
            }
        }
    }
    else
    {
        if (func->func_def_args_cnt != call_f->argc)
        {
            lox_error("----function %s args not equal line:%d %d %d\n", sym->sym_name, lox_cur_line_number(), func->func_def_args_cnt
                      ,func->func_call_args_index);
            exit(0);
        }
    }
    ret = LOX_OK;
    return ret;
}

int lox_func_has_arg(char *arg_name, long f)
{
    //struct lox_symbol *sym = lox_get_cur_parsing_function();
    struct lox_symbol *sym = (struct lox_symbol *)f;
    struct lox_function *func = sym->sym_obj->o_value.v_func;
    for(int i = 0; i < func->func_def_args_cnt; i++)
    {
        if (strcmp(func->func_args_names[i], arg_name) == 0)
        {
            return LOX_OK;
        }
    }
    return LOX_ERROR(LOX_INVALID);
}

int lox_func_clear(long f)
{
    struct lox_function_calling *calf = (struct lox_function_calling *)f;
    //struct lox_symbol *sym = (struct lox_symbol *)calf->func;
    lox_info("-------lox_func_clear:\n");
    calf->argc = 0;
    calf->func = 0;
    memset(calf->args, 0, 1000*sizeof (long));
    memset(calf->name, 0, 100);
    return LOX_OK;
}

struct lox_local_symbol
{
    int flag;//0 is invalid 1 is valid
    char local_name[50];
    long local_label;
};

struct lox_local_symbol local_lable_table[1000] = { 0 };

long lox_add_local_symbol(char *name, long label)
{
    int i = 0;
    for(i = 0; i < 1000; i++)
    {
        if (local_lable_table[i].flag == 1)
        {
            if (strcmp(local_lable_table[i].local_name, name) == 0)
            {
                return local_lable_table[i].local_label;
            }
        }
    }

    for(i = 0; i < 1000; i++)
    {
        if (local_lable_table[i].flag == 0)
        {
            local_lable_table[i].flag = 1;
            strcpy(local_lable_table[i].local_name, name);
            local_lable_table[i].local_label = label;
            break;
        }
    }
    return LOX_ERROR(LOX_NO_EXIST);
}

long lox_find_local_symbol(char *name)
{
    int i = 0;
    for(i = 0; i < 1000; i++)
    {
        if (local_lable_table[i].flag == 1)
        {
            if (strcmp(local_lable_table[i].local_name, name) == 0)
            {
                return local_lable_table[i].local_label;
            }
        }
    }
    return LOX_ERROR(LOX_NO_EXIST);
}

void lox_local_symbol_destory(void)
{
    memset(local_lable_table, 0, 1000*sizeof (struct lox_local_symbol));
}

void lox_func_scan(long f)
{
#if 0
    struct lox_object *obj = (struct lox_object *)f;

    lox_info("xxxxxxxxxxxxxxxxxx scan func:%s code_len:%d code_index:%d\n",
             obj->o_name, obj->o_value.v_func->func_code_len, obj->o_value.v_func->func_code_index);

    for(int i = 0; i < obj->o_value.v_func->func_code_index; i++)
    {
        struct lox_cmd *cmd = &obj->o_value.v_func->func_code[i];
        lox_info("==============:%d\n", cmd->cmd_opcode);
        if (cmd->cmd_opcode == LOX_PUSH)
        {
            if (cmd->cmd_push.p_type == PUSH_NUMBER)
            {
                lox_info("==push number:%f\n", cmd->cmd_push.f_number);
            }
            if (cmd->cmd_push.p_type == PUSH_ARG)
            {
                lox_info("==push arg:%s\n", cmd->cmd_push.f_arg_name);
            }

            if (cmd->cmd_push.p_type == PUSH_NUMBER_VAR)
            {
                lox_info("==push number var:%f\n", cmd->cmd_push.f_f);
            }

            if (cmd->cmd_push.p_type == PUSH_STRING_VAR)
            {
                lox_info("==push string var:%s\n", cmd->cmd_push.f_str);
            }

            if (cmd->cmd_push.p_type == PUSH_VAR)
            {
                lox_info("==push var:%s\n", cmd->cmd_push.f_var_name);
            }
        }

        if (cmd->cmd_opcode == LOX_GET_VAR)
        {

        }
    }
#endif
}
