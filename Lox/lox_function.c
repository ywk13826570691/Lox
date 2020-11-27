#include "lox_function.h"
#include "lox.h"
#include "lox_def.h"
#include "lox_opcode.h"
#include "lox_register.h"
#include "lox_config.h"
#include "lox_object.h"
#include <stdlib.h>
#include <string.h>

struct lox_symbol *cur_parsing_function = NULL;
struct lox_symbol *cur_calling_function = NULL;
struct lox_symbol *main_function = NULL;

int lox_function_index = 0;
int lox_function_total = 0;
long *lox_function_table;

int lox_function_parsing = 0;

int cur_calling_function_index = -1;
long cur_calling_function_table[100];


int lox_function_init(void)
{
    lox_function_table = (long *)malloc(LOX_FUNCTION_TABLE_STEP * sizeof (long));
    lox_function_total += LOX_FUNCTION_TABLE_STEP;
    main_function = lox_new_function("main");
    lox_set_cur_calling_function((long)main_function);
    lox_inner_func_init();
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
    cur_calling_function = (struct lox_symbol *)f;
    return LOX_OK;
}

struct lox_symbol * lox_get_cur_calling_function()
{
    return cur_calling_function;
}

int lox_push_cur_calling_function(long f)
{
    cur_calling_function_table[cur_calling_function_index + 1] = f;
    cur_calling_function_index++;
    lox_set_cur_calling_function(f);
    return LOX_OK;
}

int lox_pop_cur_calling_function(void)
{
    cur_calling_function_index--;
    lox_set_cur_calling_function(cur_calling_function_table[cur_calling_function_index]);
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

    //strcpy(func->func_code[func->func_code_index].cmd_var_name, cmd->cmd_var_name);
    //strcpy(func->func_code[func->func_code_index].cmd_jmp_label, cmd->cmd_jmp_label);

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
    struct lox_symbol *sym = lox_get_cur_calling_function();
    struct lox_function *func = sym->sym_obj->o_value.v_func;

    func->func_args[func->func_call_args_index] = label;
    func->func_call_args_index++;
    lox_info("----func push arg:%s %d\n", sym->sym_name, func->func_call_args_index);

    return LOX_OK;
}

int lox_func_check_args(long f)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = (struct lox_symbol *)f;
    struct lox_function *func = sym->sym_obj->o_value.v_func;

    if (func->is_inner_function)
    {
        if (func->func_def_args_cnt != 1000)
        {
            if (func->func_def_args_cnt != func->func_call_args_index )
            {
                lox_error("----function %s args not equal line:%d %d %d\n", sym->sym_name, lox_cur_line_number(), func->func_def_args_cnt
                          ,func->func_call_args_index);
                exit(0);
            }
        }
    }
    else
    {
        if (func->func_def_args_cnt != func->func_call_args_index)
        {
            lox_error("----function %s args not equal line:%d %d %d\n", sym->sym_name, lox_cur_line_number(), func->func_def_args_cnt
                      ,func->func_call_args_index);
            exit(0);
        }
    }
    ret = LOX_OK;
    return ret;
}

int lox_func_before_call(long f)
{
    int ret = LOX_OK;
    struct lox_symbol *sym = (struct lox_symbol *)f;
    struct lox_function *func = sym->sym_obj->o_value.v_func;

    //lox_info("----func before call:%s %d %d\n", sym->sym_name, func->func_call_args_cnt, func->func_def_args_cnt);
    func->func_call_args_index = 0;
    memset(func->func_args, 0, 100);
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
    struct lox_symbol *sym = (struct lox_symbol *)f;
    struct lox_function *func = sym->sym_obj->o_value.v_func;
    func->func_call_args_index = 0;
    memset(func->func_args, 0, 100);
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

int lox_find_local_symbol(char *name)
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



















static void lox_inner_printf(struct lox_symbol * sym, long *argv, int len, long ret)
{
    int i = 0;
    for(i = 0; i < len; i++)
    {
        struct lox_object *obj = (struct lox_object *)argv[i];
        if (obj)
        {
            if (obj->o_tag == LOX_NUMBER)
            {
                printf("%f\n", obj->o_value.v_f);
            }
            if (obj->o_tag == LOX_STRING)
            {
                printf("%s\n", obj->o_value.v_str);
            }
        }
    }
    lox_info("calling print\n");
}

static void lox_inner_type(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;
    struct lox_object *r_v = NULL;
    if (re)
        r_v = (struct lox_object*)re->sym_obj;

    char type[50] = "nil";
    strcpy(type, "nil");
    if (obj->o_tag == LOX_NUMBER)
    {
        strcpy(type, "number");
    }
    if (obj->o_tag == LOX_STRING)
    {
        strcpy(type, "string");
    }
    if (r_v)
    {
        struct lox_object *result = lox_object_new_string(type);
        lox_info("calling type:%d %d\n", r_v->o_tag, result->o_tag);
        lox_object_copy(r_v, result);
        lox_info("calling type:%d %d %s\n", r_v->o_tag, result->o_tag, r_v->o_value.v_str);
    }
    //lox_info("calling type:%s %d\n", result->o_value.v_str, obj->o_tag);
}

static struct lox_inner_function inner_func_table[] =
{
    {"print", lox_inner_printf , 1000},
    {"type", lox_inner_type , 1}
};

#define INNER_FUNC_COUNT (sizeof(inner_func_table)/sizeof(inner_func_table[0]))

int lox_inner_func_init(void)
{
    unsigned int i = 0;
    for (i = 0; i < INNER_FUNC_COUNT; i++)
    {
        struct lox_symbol *sym = (struct lox_symbol*)malloc(sizeof (struct lox_symbol));
        memset(sym, 0, sizeof (struct lox_symbol));

        struct lox_object *obj = lox_object_new_func();
        sym->sym_obj = obj;

        struct lox_function *func;

        func = (struct lox_function*)malloc(sizeof (struct lox_function));
        sym->sym_obj->o_value.v_func = func;

        func->is_inner_function = 1;
        func->func_def_args_cnt = inner_func_table[i].func_args_define;
        strcpy(sym->sym_name, inner_func_table[i].name);
        lox_register_func(sym);
    }
    return LOX_OK;
}

long lox_run_inner_func(long f, long *argv, int len, long ret)
{
    struct lox_symbol *sym = (struct lox_symbol*)f;
    struct lox_symbol *re = (struct lox_symbol *)ret;
    for (unsigned int i = 0 ; i < INNER_FUNC_COUNT; i++)
    {
        if (strcmp(inner_func_table[i].name, sym->sym_name) == 0)
        {
            inner_func_table[i].func(sym, argv, len, re);
            break;
        }
    }
    return LOX_OK;
}
