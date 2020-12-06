#include "lox_opcode.h"
#include "lox_function.h"
#include "lox_stack.h"

int lox_opcode_push_number_var(float f, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_NUMBER_VAR;

    cmd.cmd_push.f_f = f;
    cmd.cmd_push.f_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_string_var(char *str, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_STRING_VAR;

    cmd.cmd_push.f_str = str;
    cmd.cmd_push.f_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_var(char *var_name, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_VAR;

    strcpy(cmd.cmd_push.f_var_name, var_name);
    cmd.cmd_push.f_label_index = label;

    lox_info("----push var:%s %d\n",var_name, label);

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_temp_var(long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_TEMP_VAR;

    cmd.cmd_push.f_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_temp_ptr_var(int label_temp)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_TEMP_PTR_VAR;

    cmd.cmd_push.f_label_index = label_temp;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_bool_var(long label, int v)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_BOOL;

    cmd.cmd_push.f_label_index = label;
    cmd.cmd_args[0] = v;
    lox_info("lox_opcode_push_bool_var++++++++++++++++++++++++++++++++:%d\n", v);

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_push_range_var(long label, long label_min, long label_len)
{

    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_RANGE;

    cmd.cmd_push.f_label_index = label;
    cmd.cmd_args[0] = label_min;
    cmd.cmd_args[1] = label_len;
    lox_info("lox_opcode_push_range_var++++++++++++++++++++++++++++++++ %d %d %d\n", label, label_min, label_len);

    return lox_func_push_cmd(&cmd);

}

int lox_opcode_push_array_var(long label, long *labels, long label_cnt)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_PUSH;
    cmd.cmd_push.p_type =  PUSH_ARRARY;
    cmd.cmd_args[0] = label_cnt;

    cmd.cmd_push.f_label_index = label;
    for(int i = 0; i < label_cnt; i++)
    {
        cmd.cmd_args[1 + i] = labels[i];
    }
    lox_info("---------push array\n");
    return lox_func_push_cmd(&cmd);
}

int lox_opcode_get_array_object(long array_label, long temp_label, long *label_indexs, long index_cnt)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_GET_ARRAY_VALUE;
    cmd.cmd_label_index = array_label;
    cmd.cmd_args[0] = temp_label;
    cmd.cmd_args[1] = index_cnt;


    for(int i = 0; i < index_cnt; i++)
    {
        cmd.cmd_args[2 + i] = label_indexs[i];
    }

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_set_array_object(long array_label, long temp_label, long *label_indexs, long index_cnt)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_SET_ARRAY_VALUE;
    cmd.cmd_label_index = array_label;
    cmd.cmd_args[0] = temp_label;
    cmd.cmd_args[1] = index_cnt;


    for(int i = 0; i < index_cnt; i++)
    {
        cmd.cmd_args[2 + i] = label_indexs[i];
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

int lox_opcode_add(long r1, long r2, long label)
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
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_ADD;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_sub(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_SUB;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_mul(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_MUL;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_div(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_DIV;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_equal(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_EQUAL;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_nequal(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_NEQUAL;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_lt(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_LT;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_gt(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_GT;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_let(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_LET;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_get(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_GET;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_and(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_AND;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;
    cmd.cmd_label_index = label;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_or(long r1, long r2, long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_OR;
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
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_MOVE;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = r2;

    return lox_func_push_cmd(&cmd);
}

int lox_opcode_jmp(long r1, int ret, long f)
{
    int retv = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    struct lox_symbol *sym2 = (struct lox_symbol *)r1;
    struct lox_function_calling *calf = (struct lox_function_calling *)f;
    int argc = calf->argc;

    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  retv;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_JMP;
    cmd.cmd_args[0] = r1;
    cmd.cmd_args[1] = argc;
    cmd.cmd_label_index = ret;

    for(int i = 0; i < argc; i++)
    {
        cmd.cmd_args[2 + i] = calf->args[i];
    }

    //lox_push_cur_calling_function(r1);
    lox_info("-------------------jmp---%p %d %s %d %d\n", r1, argc, sym2->sym_name, argc, ret);
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
    memset(&cmd, 0, sizeof (struct lox_cmd));

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
    memset(&cmd, 0, sizeof (struct lox_cmd));

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
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_FUNCTION_PARAM_END;

    lox_info("-------------------end function---%s\n", sym->sym_name);
    return lox_func_push_cmd(&cmd);
}


int lox_opcode_push_label(char *label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_LABEL;
    strcpy(cmd.cmd_jmp_label, label);

    lox_info("-------------------lox_opcode_push_label:%s\n", label);
    return lox_func_push_cmd(&cmd);
}

int lox_opcode_cmp(long label)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_CMP;
    cmd.cmd_label_index = label;

    lox_info("-------------------lox_opcode_cmp\n");
    return lox_func_push_cmd(&cmd);
}

int lox_opcode_cmp_inrange(long label_range, long label_var)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_CMP_IN_RANGE;
    cmd.cmd_label_index = label_range;
    cmd.cmd_args[0] = label_var;

    lox_info("-------------------lox_opcode_cmp_inrange\n");
    return lox_func_push_cmd(&cmd);
}
/*
 * param:f_b
 * 0-->back
 * 1-->front
*/
int lox_opcode_jmp_label(char *label, int f_b)
{
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_JMP_LABEL;
    strcpy(cmd.cmd_jmp_label, label);
    cmd.cmd_args[0] = f_b;

    lox_info("-------------------lox_opcode_jmp_label:%s\n", label);
    return lox_func_push_cmd(&cmd);
}

//cmp result is zero
int lox_opcode_jmpeq_label(char *label, int f_b)
{lox_info("-------------------1lox_opcode_jmpeq_label: %p\n", label);
    int ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym = lox_get_cur_parsing_function();
    if (!sym)
    {
        lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
        return  ret;
    }

    struct lox_cmd cmd;
    memset(&cmd, 0, sizeof (struct lox_cmd));

    cmd.cmd_opcode = LOX_JMPEQ_LABEL;
    strcpy(cmd.cmd_jmp_label, label);
    cmd.cmd_args[0] = f_b;

    lox_info("-------------------lox_opcode_jmpeq_label:%s\n", label);
    return lox_func_push_cmd(&cmd);
}

int lox_opcode_jmpneq_label(char *label, int f_b)
{
    lox_info("-------------------1lox_opcode_jmpneq_label: %p\n", label);
        int ret = LOX_ERROR(LOX_INVALID);
        struct lox_symbol *sym = lox_get_cur_parsing_function();
        if (!sym)
        {
            lox_error("cur parse funcion is nil %s %d\n", __func__, __LINE__);
            return  ret;
        }

        struct lox_cmd cmd;
        memset(&cmd, 0, sizeof (struct lox_cmd));

        cmd.cmd_opcode = LOX_JMPNEQ_LABEL;
        strcpy(cmd.cmd_jmp_label, label);
        cmd.cmd_args[0] = f_b;

        lox_info("-------------------lox_opcode_jmpneq_label:%s\n", label);
        return lox_func_push_cmd(&cmd);
}
