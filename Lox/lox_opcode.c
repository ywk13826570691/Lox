#include "lox_opcode.h"
#include "lox_function.h"
#include "lox_stack.h"

#if 0
int lox_opcode_push_number(long n)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_object *obj = lox_cur_parse_function();

    if (!obj)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_NUMBER;
    cmd.cmd_push.f_number = n;

    return lox_func_push_cmd(&cmd);
}


int lox_opcode_push_arg(char *argname, int reg)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_object *obj = lox_cur_parse_function();

    if (!obj)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_ARG;

    cmd.cmd_push.f_arg_name = argname;
    cmd.cmd_push.f_label_index = reg;

    return lox_func_push_cmd(&cmd);
}
#endif

int lox_opcode_push_number_var(float f, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_NUMBER_VAR;

    cmd.cmd_push.f_f = f;
    cmd.cmd_push.f_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_string_var(char *str, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_STRING_VAR;

    cmd.cmd_push.f_str = str;
    cmd.cmd_push.f_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_var(char *var_name, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_VAR;

    cmd.cmd_push.f_var_name = var_name;
    cmd.cmd_push.f_label_index = label;

    lox_info("----push var:%s %d\n",var_name, label);

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_temp_var(int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_TEMP_VAR;

    cmd.cmd_push.f_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_array_var(int label, long *labels, long label_cnt)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_ARRARY;
    cmd.cmd_args[0] = label_cnt;

    cmd.cmd_push.f_label_index = label;
    for(int i = 0; i < label_cnt; i++)
    {
        cmd.cmd_args[1 + i] = labels[i];
    }

    return lox_func_push_cmd(&cmd);
}

/*
int lox_opcode_get_var(char *var_name, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_GET_VAR;
    cmd.cmd_var_name = var_name;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}
*/

int lox_opcode_add(long r1, long r2, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }
    lox_error("--------------------------------add %p %p %d\n", r1, r2, label);
    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_ADD;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_sub(long r1, long r2, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_SUB;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_mul(long r1, long r2, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_MUL;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_div(long r1, long r2, int label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_DIV;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_move(long r1, long r2)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_MOVE;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_jmp(long r1, int reg)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    struct lox_symbol *sym2 = (struct lox_symbol *)r1;
    int args = sym2->sym_obj->o_value.v_func->func_call_args_index;

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_JMP;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = args;
    cmd.cmd_label_index = reg;

    for(int i = 0; i < args; i++)
    {
        cmd.cmd_args[2 + i] = sym2->sym_obj->o_value.v_func->func_args[i];
    }

    //lox_push_cur_calling_function(r1);
    lox_info("-------------------jmp---%p %d %s %d %d\n", r1, args, sym2->sym_name, args, reg);
    return lox_func_push_cmd(&cmd);
}

int lox_opcode_return(long r1, int has_ret_expr)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_RETURN;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = has_ret_expr;

    //lox_info("-------------------return---%p %s\n", r1, lox_cur_parse_function()->o_name);
    //lox_pop_cur_calling_function();
    return lox_func_push_cmd(&cmd);
}

int lox_opcode_function_end(void)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_END_FUNCTION;

    lox_info("-------------------end function---%s\n", sym->sym_name);
    return lox_func_push_cmd(&cmd);
}

int lox_opcode_function_param_end(void)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;

    cmd.cmd_opcode = LOX_FUNCTION_PARAM_END;

    lox_info("-------------------end function---%s\n", sym->sym_name);
    return lox_func_push_cmd(&cmd);
}
