#include <string.h>
#include <stdlib.h>
#include "lox_handle.h"
#include "lox_def.h"
#include "lox_function.h"
#include "lox_register.h"
#include "lox_stack.h"
#include "lox_object.h"
#include "lox_string.h"
#include "lox_array.h"


/*
0:SP
1:FP
2:LR
3:argc
4:RET---->return symbol -100 will not return
5:arg1-> symbol
.....
6:argx-> symbol

function param created
arg1 symbol
argx symbol
*/
int lox_setup_stack(void)
{
    struct lox_symbol *sym = lox_get_main_function();
    long *stack = lox_get_stack();

    SP = 0;

    PC = (long)&sym->sym_obj->o_value.v_func->func_code[0];
    FP = SP;
    stack[0] = 0;
    stack[1] = 0;
    stack[2] = 0;
    stack[3] = 0;
    stack[4] = -100;
    SP = 5;
    return LOX_OK;
}

long lox_handle_push_cmd(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_cmd_push *push_type = &cmd->cmd_push;

    lox_debug("handle push cmd:%d %d %ld\n", push_type->f_label_index, push_type->p_type, SP);

    switch (push_type->p_type)
    {
        case PUSH_NUMBER_VAR:
            ret = lox_stack_push_number_var(push_type->f_f, push_type->f_label_index);
            break;
        case PUSH_STRING_VAR:
            ret = lox_stack_push_string_var(push_type->f_str, push_type->f_label_index);
            break;
        case PUSH_VAR:
            ret = lox_stack_push_var(push_type->f_var_name, push_type->f_label_index);
            break;
        case PUSH_TEMP_VAR:
            ret = lox_stack_push_temp_var(push_type->f_label_index);
            break;
        case PUSH_TEMP_PTR_VAR:
            ret = lox_stack_push_temp_ptr_var(push_type->f_label_index);
            break;
        case PUSH_ARRARY:
            ret = lox_stack_push_array_var(push_type->f_label_index, &cmd->cmd_args[1], cmd->cmd_args[0]);
            break;
        case PUSH_BOOL:
            ret = lox_stack_push_bool_var(push_type->f_label_index, cmd->cmd_args[0]);
            break;
        case PUSH_RANGE:
            ret = lox_stack_push_range_var(push_type->f_label_index, cmd->cmd_args[0], cmd->cmd_args[1]);
            break;
        case PUSH_FUNCTION:
            ret = lox_stack_push_function_var(push_type->f_label_index, cmd->cmd_args[0]);
            break;
        default:
            lox_error("invalid push cmd:%d\n", push_type->p_type);
            exit(0);
    }
    return ret;
}

long lox_handle_move(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym1 = (struct lox_symbol *)lox_find_symbol_by_label((unsigned long)cmd->cmd_args[0]);
    struct lox_symbol *sym2 = (struct lox_symbol *)lox_find_symbol_by_label((unsigned long)cmd->cmd_args[1]);

    if (!sym1 || !sym2)
    {

        lox_error("lox_handle_move invalid label %ld %ld\n", cmd->cmd_args[0], cmd->cmd_args[1]);
        exit(0);
        return  ret;
    }

    lox_object_copy(sym1->sym_obj, sym2->sym_obj);

    lox_debug("lox_handle_move:%f %f\n", sym1->sym_obj->o_value.v_f, sym1->sym_obj->o_value.v_f);

    return LOX_OK;
}

long lox_handle_operator(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol * s1 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol * s2 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[1]);
    struct lox_symbol * s3 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_label_index);
    struct lox_object *obj1, *obj2, *obj3;
    lox_debug("lox_handle_operator:%ld %ld\n",cmd->cmd_args[0], cmd->cmd_args[1]);
    if (!s1 || !s3 )
    {

        lox_error("add invalid symbold %d %d %d\n", cmd->cmd_args[0], cmd->cmd_args[1],cmd->cmd_label_index);
        exit(0);
    }

    if (cmd->cmd_opcode != LOX_PLUS && cmd->cmd_opcode != LOX_MINUS && !s2)
    {
        lox_error("add invalid symbold2 %d %d %d\n", cmd->cmd_args[0], cmd->cmd_args[1],cmd->cmd_label_index);
        exit(0);
    }
    obj1 = s1->sym_obj;
    if (s2)
    {
        obj2 = s2->sym_obj;
    }
    obj3 = s3->sym_obj;
    switch (cmd->cmd_opcode)
    {
        case LOX_ADD:
            ret = lox_object_add(obj1, obj2, obj3);
            break;
        case LOX_SUB:
            ret = lox_object_sub(obj1, obj2, obj3);
            break;
        case LOX_MUL:
            ret = lox_object_mul(obj1, obj2, obj3);
            break;
        case LOX_DIV:
            ret = lox_object_div(obj1, obj2, obj3);
            break;
        case LOX_MOD:
            ret = lox_object_mod(obj1, obj2, obj3);
            break;
        case LOX_PLUS:
            lox_object_plus(obj1, obj3);
            break;
        case LOX_MINUS:
            lox_object_minus(obj1, obj3);
            break;
        default:
            lox_error("invalid lox operator\n", cmd->cmd_opcode);
            exit(0);
            break;
    }
    return LOX_OK;
}

long lox_handle_logical_operation(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol * s1 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol * s2 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[1]);
    struct lox_symbol * s3 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_label_index);

    if (!s1 || !s2 || !s3)
    {
        lox_error("logical operation invalid symbold %d %d %d\n", cmd->cmd_args[0], cmd->cmd_args[1],cmd->cmd_label_index);
        exit(0);
        return  ret;
    }
    struct lox_object *obj1, *obj2, *obj3;

    obj1 = s1->sym_obj;
    obj2 = s2->sym_obj;
    obj3 = s3->sym_obj;

    ret = lox_object_logical_operation(obj1, obj2, obj3, cmd->cmd_opcode);
    return ret;
}

long lox_handle_and(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol * s1 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol * s2 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[1]);
    struct lox_symbol * s3 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_label_index);

    if (!s1 || !s2 || !s3)
    {
        lox_error("lox_handle_and invalid symbold %d %d %d\n", cmd->cmd_args[0], cmd->cmd_args[1],cmd->cmd_label_index);
        exit(0);
        return  ret;
    }
    struct lox_object *obj1, *obj2, *obj3;

    obj1 = s1->sym_obj;
    obj2 = s2->sym_obj;
    obj3 = s3->sym_obj;

    ret = lox_object_and(obj1, obj2, obj3);
    return ret;
}

long lox_handle_or(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol * s1 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol * s2 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[1]);
    struct lox_symbol * s3 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_label_index);

    if (!s1 || !s2 || !s3)
    {
        lox_error("lox_handle_or invalid symbold %d %d %d\n", cmd->cmd_args[0], cmd->cmd_args[1],cmd->cmd_label_index);
        exit(0);
        return  ret;
    }
    struct lox_object *obj1, *obj2, *obj3;

    obj1 = s1->sym_obj;
    obj2 = s2->sym_obj;
    obj3 = s3->sym_obj;

    ret = lox_object_or(obj1, obj2, obj3);
    return ret;
}

long lox_handle_not(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol * s1 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol * s2 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_label_index);

    if (!s1 || !s2)
    {
        lox_error("lox_handle_not invalid symbold %d %d\n", cmd->cmd_args[0],cmd->cmd_label_index);
        exit(0);
        return  ret;
    }

    struct lox_object *obj1, *obj2;

    obj1 = s1->sym_obj;
    obj2 = s2->sym_obj;

    ret = lox_object_not(obj1, obj2);
    return ret;
}

long lox_handle_jmp_inner(struct lox_cmd *cmd)
{
    struct lox_symbol *sym = lox_find_symbol_by_label(cmd->cmd_args[0]);;
    struct lox_function *func = sym->sym_obj->o_value.v_func;
    struct lox_symbol * sym2 = lox_find_function_by_addr(func);

    long argc = cmd->cmd_args[1];

    lox_debug("callinng inner function:%s %d\n", sym2->sym_name, argc);
    int i = 0;
    long len = argc;
    long *argv = (long *)malloc(len * sizeof (long));
#if 1
    for(i = 0 ; i < argc; i++)
    {
        struct lox_symbol *s = lox_find_symbol_by_label(cmd->cmd_args[2+i]);
        struct lox_object *obj2 = s->sym_obj;
        struct lox_object *obj3 = lox_object_new_temp();
        if (!obj2)
        {
            lox_error("func invalid param nil\n");
            exit(0);
        }
        lox_object_copy(obj3, obj2);
        argv[i] = (long)obj3;
    }

    struct lox_symbol *ret = lox_find_symbol_by_label(cmd->cmd_label_index);
    if (ret)
        lox_debug("function will return\n");
    else
        lox_debug("function will not return %d %s\n", cmd->cmd_label_index, sym->sym_name);
#endif

    lox_run_lib_func((long)sym2, argv, len, (long)ret);
    for(i = 0; i < len; i++)
    {
        free(argv[i]);
    }
    free(argv);
    return LOX_OK;
}

long lox_handle_jmp(struct lox_cmd *cmd)
{
    //lox_stack_print();

    lox_debug("lox_handle_jmp:%ld \n", SP);
    struct lox_symbol *sym = lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_function *func;
    long *stack = lox_get_stack();

    if (sym->sym_obj)
    {
        func = sym->sym_obj->o_value.v_func;
        lox_debug("jmp to function:%s\n", sym->sym_name);
    }
    else
    {
        lox_error("jmp an nil function?\n");
        exit(0);
    }

    struct lox_symbol *sym_ret = lox_find_symbol_by_label(cmd->cmd_label_index);

    long last_sp = SP;
    long ret;
    int argc = cmd->cmd_args[1];
    /*
    extern unsigned int lox_var_label_index;
    stack[SP] = SP;
    stack[SP + 1] = FP;
    stack[SP + 2] = PC + sizeof (struct lox_cmd);
    stack[SP + 3] = argc;
    stack[SP + 4] = cmd->cmd_label_index;
    */
    lox_stack_push_value(SP);
    lox_stack_push_value(FP);
    lox_stack_push_value(PC + sizeof (struct lox_cmd));
    lox_stack_push_value(argc);
    lox_stack_push_value((long)sym_ret);

    for(int i = 0; i < argc; i++)
    {
        struct lox_symbol *sym_arg = lox_find_symbol_by_label(cmd->cmd_args[2 + i]);
        //stack[SP + 5 + i] = (long)sym_arg;
        lox_stack_push_value((long)sym_arg);
        lox_debug("----------------jumping:%d\n", sym_arg->sym_obj->o_tag);
    }

    FP = last_sp;
    LR = PC + sizeof (struct lox_cmd);
    PC = &func->func_code[0];
    return LOX_OK;
}


long lox_handle_function_param_end(struct lox_cmd *cmd)
{
    long *stack = lox_get_stack();

    int i = 0;
    int argc = stack[FP + 3];
    lox_debug("lox_handle_function_param_end:%d %ld %ld\n", argc, SP, FP);
    for (i = 0; i < argc; i++)
    {
        struct lox_symbol *s = stack[FP + LOX_STACK_TOP + i];
        struct lox_symbol *s2 = stack[FP + LOX_STACK_TOP + i + argc];

        if (s && s->sym_obj)
        {
            lox_object_copy(s2->sym_obj, s->sym_obj);
        }
    }
    return LOX_OK;
}

long lox_handle_return(struct lox_cmd *cmd)
{
    long *stack = lox_get_stack();
    if (cmd->cmd_args[0] == 0 && cmd->cmd_args[1] == 0)
    {
        lox_debug("No return to handle return;");
        return LOX_OK;
    }

    struct lox_symbol *sym_ret = lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol *s = (struct lox_symbol *)(stack[FP + 4]);

    if (s && s->sym_obj)
    { 
        lox_object_copy(s->sym_obj, sym_ret->sym_obj);
        lox_debug("lox_handle_return will return\n");
    }
    else
    {
        lox_debug("lox_handle_return will not has return value\n");
    }

    lox_stack_clear_and_return();

    //lox_stack_print();
    lox_debug("---------lox_handle_return------------------:%ld \n", SP);

    return LOX_OK;
}


long lox_handle_function_end(struct lox_cmd *cmd)
{
    lox_stack_clear_and_return();

    return LOX_OK;
}

long lox_handle_get_array_value(struct lox_cmd *cmd)
{
    lox_debug("lox_handle_get_array_value \n");
    struct lox_symbol *sym = lox_find_symbol_by_label(cmd->cmd_label_index);
    struct lox_symbol *sym_temp = lox_find_symbol_by_label(cmd->cmd_args[0]);
    if (sym)
    {
        lox_debug("lox_handle_get_array_value array:%s\n", sym->sym_name);
        if (sym->sym_obj->o_tag != LOX_ARRAY)
        {
            lox_error("lox_handle_get_array_value %s is not an array\n", sym->sym_name);
            exit(0);
        }
        int index_cnt = cmd->cmd_args[1];
        long index_array[100] = { 0 };
        for(int i = 0; i < index_cnt; i++)
        {
            long index_label = cmd->cmd_args[2 + i];
            struct lox_symbol *res = lox_find_symbol_by_label(index_label);
            if (!res || !res->sym_obj)
            {
                lox_error("lox_handle_get_array_value nil index\n");
                exit(0);
            }
            if (res->sym_obj->o_tag != LOX_NUMBER)
            {
                lox_error("lox_handle_get_array_value  index must number\n");
                exit(0);
            }
            if (!lox_is_int_number(res->sym_obj->o_value.v_f))
            {
                lox_error("lox_handle_get_array_value  index must int number\n");
                exit(0);
            }
            lox_debug("lox_handle_get_array_value handle index:%f\n", res->sym_obj->o_value.v_f);
            index_array[i] = (int)res->sym_obj->o_value.v_f;

        }

        if (sym_temp)
        {
            struct lox_object *get_res = lox_array_get_object(sym->sym_obj, index_array, index_cnt);
            if (get_res)
            {
                lox_debug("lox_handle_get_array_value get element value:%f\n", get_res->o_value.v_f);
                lox_object_copy(sym_temp->sym_obj, get_res);
            }
        }
    }

    return LOX_OK;
}


long lox_handle_set_array_value(struct lox_cmd *cmd)
{
    lox_debug("lox_handle_set_array_value \n");
    struct lox_symbol *sym = lox_find_symbol_by_label(cmd->cmd_label_index);
    struct lox_symbol *sym_set = lox_find_symbol_by_label(cmd->cmd_args[0]);
    if (sym)
    {
        lox_debug("lox_handle_set_array_value array:%s\n", sym->sym_name);
        if (sym->sym_obj->o_tag != LOX_ARRAY)
        {
            lox_error("lox_handle_set_array_value %s is not an array\n", sym->sym_name);
            exit(0);
        }
        long index_cnt = cmd->cmd_args[1];
        long index_array[100] = { 0 };
        for(int i = 0; i < index_cnt; i++)
        {
            long index_label = cmd->cmd_args[2 + i];
            struct lox_symbol *res = lox_find_symbol_by_label(index_label);
            if (!res || !res->sym_obj)
            {
                lox_error("lox_handle_get_array_value nil index\n");
                exit(0);
            }
            if (res->sym_obj->o_tag != LOX_NUMBER)
            {
                lox_error("lox_handle_get_array_value index must number\n");
                exit(0);
            }
            if (!lox_is_int_number(res->sym_obj->o_value.v_f))
            {
                lox_error("lox_handle_get_array_value  index must int number\n");
                exit(0);
            }
            lox_debug("lox_handle_set_array_value handle index:%f\n", res->sym_obj->o_value.v_f);
            index_array[i] = (int)res->sym_obj->o_value.v_f;

        }

        if (sym_set)
        {
            lox_array_set_object(sym->sym_obj, index_array, index_cnt, sym_set->sym_obj);
        }
    }

    return LOX_OK;
}

long lox_find_label_back(char *label)
{
    long ret = 0;
    if (!label)
    {
        lox_error("We are finding an nil label to jmp!!!!\n");
        exit(0);
    }

    struct lox_cmd *cmd = (struct lox_cmd *)(PC + sizeof (struct lox_cmd));

    while(cmd && cmd->cmd_opcode != LOX_NOP)
    {
        if (cmd->cmd_opcode == LOX_LABEL && strcmp(cmd->cmd_jmp_label, label) == 0)
        {
            ret =  (long)cmd;
            break;
        }
        cmd++;
    }
    return ret;
}

long lox_find_label_front(char *label)
{
    long ret = 0;
    if (!label)
    {
        lox_error("We are finding an nil label to jmp!!!!\n");
        exit(0);
    }

    struct lox_cmd *cmd = (struct lox_cmd *)(PC - sizeof (struct lox_cmd));

    while(cmd && cmd->cmd_opcode != LOX_NOP)
    {
        if (cmd->cmd_opcode == LOX_LABEL && strcmp(cmd->cmd_jmp_label, label) == 0)
        {
            ret =  (long)cmd;
            break;
        }
        cmd--;
    }
    return ret;
}

long lox_handle_cmp(struct lox_cmd *cmd)
{
    lox_debug("lox_handle_cmp\n");
    struct lox_symbol * sym = lox_find_symbol_by_label(cmd->cmd_label_index);

    if (sym && sym->sym_obj)
    {
        struct lox_object *obj = sym->sym_obj;
        switch (obj->o_tag)
        {
            case LOX_NUMBER:
                SPR = obj->o_value.v_f == 0.0 ? 0 : 1;
                break;
            case LOX_STRING:
                if (!obj->o_value.v_str)
                {
                    SPR = 0;
                }
                else
                {
                    SPR = strlen(obj->o_value.v_str) ? 1 : 0;
                }
                break;
            case LOX_NIL:
                SPR = 0;
                break;
            case LOX_ARRAY:
                if (!obj->o_value.v_vec)
                {
                    SPR = 0;
                }
                else
                {
                    SPR = obj->o_value.v_vec->len ? 1 : 0;
                }
                break;
            case LOX_BOOL_FALSE:
                SPR = 0;
                break;
            case LOX_BOOL_TRUE:
            case LOX_FUNCTION:
                SPR = 1;
                break;
            default:
                SPR = 0;
                break;
         }
    }
    else
    {
        SPR = 0;
    }
    return LOX_OK;
}

long lox_handle_cmp_inrange(struct lox_cmd *cmd)
{
    lox_debug("lox_handle_cmp_inrange\n");
    struct lox_symbol * sym_range = lox_find_symbol_by_label(cmd->cmd_label_index);
    struct lox_symbol * sym_var = lox_find_symbol_by_label(cmd->cmd_args[0]);

    if (sym_range && sym_range->sym_obj && sym_var && sym_var->sym_obj)
    {
        struct lox_object *obj = sym_range->sym_obj;
        if (obj->o_tag != LOX_RANGE)
        {
            SPR = 0;
        }
        else
        {
            int v = obj->o_value.v_range.min + obj->o_value.v_range.len;
            lox_debug("lox_handle_cmp_inrange:%d\n",obj->o_value.v_range.index);
            if (obj->o_value.v_range.index < v)
            {

                struct lox_object new_obj;
                new_obj.o_tag = LOX_NUMBER;
                new_obj.o_value.v_f = obj->o_value.v_range.index * 1.0;
                obj->o_value.v_range.index++;
                lox_object_copy(sym_var->sym_obj, &new_obj);
                SPR = 1;
            }
            else
            {
                SPR = 0;
            }
        }
    }
    else
    {
        SPR = 0;
    }
    return LOX_OK;
}

long lox_handle_jmp_label(struct lox_cmd *cmd)
{
    int flag = cmd->cmd_args[0];
    lox_debug("lox_handle_jmp_label:%s %d\n", cmd->cmd_jmp_label, flag);
    long ret = 0;
    if (flag == 0)
    {
        ret = lox_find_label_back(cmd->cmd_jmp_label);
    }
    else
    {
        ret = lox_find_label_front(cmd->cmd_jmp_label);
    }
    if (ret)
    {
        struct lox_cmd *cmd2 = (struct lox_cmd *)ret;
        PC = (long)cmd2;
    }
    return LOX_OK;
}

long lox_handle_jmpeq_label(struct lox_cmd *cmd)
{
    int ret = 0;
    ret = SPR;
    lox_debug("lox_handle_jmpeq_label:%s %d\n", cmd->cmd_jmp_label, SPR);
    if (SPR == 0)
    {
        lox_handle_jmp_label(cmd);
    }
    return ret;
}

long lox_handle_jmpneq_label(struct lox_cmd *cmd)
{
    int ret = 0;
    ret = SPR;
    lox_debug("lox_handle_jmpneq_label:%s %d\n", cmd->cmd_jmp_label, SPR);
    if (SPR == 1)
    {
        lox_handle_jmp_label(cmd);
    }
    return ret;
}

