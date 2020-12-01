#include "lox_handle.h"
#include "lox_def.h"
#include "lox_function.h"
#include "lox_register.h"
#include "lox_stack.h"
#include "lox_object.h"
#include "lox_lib.h"
#include "lox_array.h"


/*
SP
FP
LR
argc

RET---->return label -100 will not return

arg1->label only label
argx->label  only label

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
    //extern int lox_sp_index;
    //lox_sp_index = 5;
    SP = 5;

    return LOX_OK;
}

long lox_handle_push_cmd(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_cmd_push *push_type = &cmd->cmd_push;

    lox_info("+++++++++++++handle push cmd+++++++++++++:%d %d %ld\n", push_type->f_label_index, push_type->p_type, SP);


    if (push_type->p_type == PUSH_NUMBER_VAR)
    {
        ret = lox_stack_push_number_var(push_type->f_f, push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_STRING_VAR)
    {
        ret = lox_stack_push_string_var(push_type->f_str, push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_VAR)
    {
        lox_info("handle push var----------------:%s %d\n", push_type->f_var_name, push_type->f_label_index);
        ret = lox_stack_push_var(push_type->f_var_name, push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_TEMP_VAR)
    {
        ret = lox_stack_push_temp_var(push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_TEMP_PTR_VAR)
    {
        ret = lox_stack_push_temp_ptr_var(push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_ARRARY)
    {
        lox_info("---------------------handle push array:%d\n", cmd->cmd_args[0]);
        ret = lox_stack_push_array_var(push_type->f_label_index, &cmd->cmd_args[1], cmd->cmd_args[0]);
    }
    else if (push_type->p_type == PUSH_BOOL)
    {
        ret =  lox_stack_push_bool_var(push_type->f_label_index, cmd->cmd_args[0]);
    }
    else
    {
        lox_error("finding an invalid push cmd:%d\n", push_type->p_type);
        exit(0);
    }

    lox_info("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++:%d\n", SP);

    return ret;
}

long lox_handle_move(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol *sym1 = (struct lox_symbol *)lox_find_symbol_by_label((unsigned long)cmd->cmd_args[0]);
    struct lox_symbol *sym2 = (struct lox_symbol *)lox_find_symbol_by_label((unsigned long)cmd->cmd_args[1]);

    lox_info("--------lox_handle_move-------------%ld %ld\n", cmd->cmd_args[0], cmd->cmd_args[1]);

    lox_info("--------lox_handle_move-------------%f %f\n", sym2->sym_obj->o_value.v_f, sym2->sym_obj->o_value.v_f);

    if (!sym1 || !sym2)
    {

        lox_debug("lox move can handle invalid label %ld %ld\n", cmd->cmd_args[0], cmd->cmd_args[1]);
        exit(0);
        return  ret;
    }

    lox_object_copy(sym1->sym_obj, sym2->sym_obj);

    lox_info("--------lox_handle_move-------------%f %f\n", sym1->sym_obj->o_value.v_f, sym1->sym_obj->o_value.v_f);

    return LOX_OK;
}


long lox_handle_add(struct lox_cmd *cmd)
{
    long ret = LOX_ERROR(LOX_INVALID);
    struct lox_symbol * s1 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol * s2 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_args[1]);
    struct lox_symbol * s3 = (struct lox_symbol *)lox_find_symbol_by_label(cmd->cmd_label_index);
    struct lox_object *obj1, *obj2, *obj3;
    lox_info("-------------lox_handle_add:%ld %ld\n",cmd->cmd_args[0], cmd->cmd_args[1]);
    if (!s1 || !s2 || !s3)
    {
        lox_error("add invalid symbold %d %d %d\n", cmd->cmd_args[0], cmd->cmd_args[1],cmd->cmd_label_index);
        exit(0);
        return  ret;
    }

    obj1 = s1->sym_obj;
    obj2 = s2->sym_obj;
    obj3 = s3->sym_obj;
    ret = lox_object_add(obj1, obj2, obj3);

    lox_info("------lox_handle_add---------add %f %f %f\n", obj1->o_value.v_f, obj2->o_value.v_f, obj3->o_value.v_f);

    return ret;
}


long lox_handle_jmp_inner(struct lox_cmd *cmd)
{
    struct lox_symbol *sym = (struct lox_symbol *)cmd->cmd_args[0];
    struct lox_function *func = sym->sym_obj->o_value.v_func;

    if (!sym || !func)
    {
        lox_error("jump to an nill function\n");
        exit(0);
    }
    long argc = cmd->cmd_args[1];

    lox_info("callinng inner function:%s %d\n", sym->sym_name, argc);
    int i = 0;
    long len = argc;
    long *argv = (long *)malloc(len * sizeof (long));
#if 1
    for(i = 0 ; i < argc; i++)
    {
        struct lox_symbol *s = lox_find_symbol_by_label(cmd->cmd_args[2+i]);
        struct lox_object *obj2 = s->sym_obj;
        struct lox_object *obj3 = lox_object_new_temp();
lox_info("------------vvvv---1-__4444444444444444444:%d %f\n", obj2->o_tag, obj2->o_value.v_f);
        if (!obj2)
        {
            lox_error("func invalid param nil\n");
            exit(0);
        }

        lox_object_copy(obj3, obj2);

        if (obj2->o_tag == LOX_NUMBER)
            lox_info("----------------2__4444444444444444444:%f %d\n", obj3->o_value.v_f, obj3->o_tag);
        if (obj2->o_tag == LOX_STRING)
                    lox_info("----------------3__4444444444444444444:%s %d %s\n", obj3->o_value.v_str, obj3->o_tag, obj3->o_value.v_str);

        argv[i] = (long)obj3;

    }

    struct lox_symbol *ret = lox_find_symbol_by_label(cmd->cmd_label_index);
    if (ret)
        lox_info("--------will return -------:\n");
    else
        lox_info("will not return %d %s\n", cmd->cmd_label_index, sym->sym_name);
#endif

    lox_run_inner_func((long)sym, argv, len, (long)ret);
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

    lox_info("---------jmp sp------------------:%ld \n", SP);
    struct lox_symbol *sym = (struct lox_symbol *)cmd->cmd_args[0];
    struct lox_function *func;
    long *stack = lox_get_stack();

    if (sym->sym_obj)
    {
        func = sym->sym_obj->o_value.v_func;
        lox_info("----------------jump to function:%s\n", sym->sym_name);
    }
    else
    {
        lox_error("----------------jumping an nil function????\n");
        exit(0);
    }

    struct lox_symbol *sym_ret = lox_find_symbol_by_label(cmd->cmd_label_index);

    long last_sp = SP;
    long ret;
    int argc = cmd->cmd_args[1];
    lox_info("---------------1:%d\n",argc);
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
        lox_info("----------------jumping:%d %f\n", sym_arg->sym_obj->o_tag,sym_arg->sym_obj->o_value.v_f);
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
    lox_info("------------------lox_handle_function_param_end:%d %ld %ld\n", argc, SP, FP);
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
        lox_info("No return to handle return;");
        return LOX_OK;
    }

    struct lox_symbol *sym_ret = lox_find_symbol_by_label(cmd->cmd_args[0]);
    struct lox_symbol *s = (struct lox_symbol *)(stack[FP + 4]);
    if (sym_ret)
    {
        if (sym_ret->sym_obj->o_tag == LOX_NUMBER)
            lox_info("--------------lox_handle_return:%f\n", sym_ret->sym_obj->o_value.v_f);
        if (sym_ret->sym_obj->o_tag == LOX_STRING)
            lox_info("--------------lox_handle_return:%s\n", sym_ret->sym_obj->o_value.v_str);
    }


    if (s && s->sym_obj)
    { 
        lox_object_copy(s->sym_obj, sym_ret->sym_obj);
        lox_info("----------------------------lox_handle_return will return %f\n", s->sym_obj->o_value.v_f);
    }
    else
    {
        lox_info("----------------------------lox_handle_return will not has return value\n");
    }
#if 0
    long sp = stack[FP];
    long fp = stack[FP + 1];
    long lr = stack[FP + 2];
    long argc = stack[FP + 3];

    SP = sp;
    PC = lr;
    FP = fp;
#endif
    lox_stack_clear_and_return();

    //lox_stack_print();
    lox_info("---------return sp------------------:%ld \n", SP);

    return LOX_OK;
}


long lox_handle_function_end(struct lox_cmd *cmd)
{
    lox_stack_clear_and_return();

    //lox_stack_print();
    lox_info("---------return sp------------------:%ld \n", SP);

    return LOX_OK;
}

long lox_handle_get_array_value(struct lox_cmd *cmd)
{
    lox_info("lox_handle_get_array_value \n");
    struct lox_symbol *sym = lox_find_symbol_by_label(cmd->cmd_label_index);
    struct lox_symbol *sym_temp = lox_find_symbol_by_label(cmd->cmd_args[0]);
    if (sym)
    {
        lox_info("lox_handle_get_array_value array:%s\n", sym->sym_name);
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
            lox_info("lox_handle_get_array_value handle index:%f\n", res->sym_obj->o_value.v_f);
            index_array[i] = (int)res->sym_obj->o_value.v_f;

        }

        if (sym_temp)
        {
            struct lox_object *get_res = lox_array_get_object(sym->sym_obj, index_array, index_cnt);
            if (get_res)
            {
                lox_info("lox_handle_get_array_value get element value:%f\n", get_res->o_value.v_f);
                lox_object_copy(sym_temp->sym_obj, get_res);
            }
        }
    }

    return LOX_OK;
}


long lox_handle_set_array_value(struct lox_cmd *cmd)
{
    lox_info("-----------------lox_handle_set_array_value \n");
    struct lox_symbol *sym = lox_find_symbol_by_label(cmd->cmd_label_index);
    struct lox_symbol *sym_set = lox_find_symbol_by_label(cmd->cmd_args[0]);
    if (sym)
    {
        lox_info("lox_handle_set_array_value array:%s\n", sym->sym_name);
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
            lox_info("lox_handle_set_array_value handle index:%f\n", res->sym_obj->o_value.v_f);
            index_array[i] = (int)res->sym_obj->o_value.v_f;

        }

        if (sym_set)
        {
            lox_array_set_object(sym->sym_obj, index_array, index_cnt, sym_set->sym_obj);

        }
    }

    return LOX_OK;
}

long lox_find_label(char *label)
{
    long ret = 0;
    if (!label)
    {
        lox_error("We are finding an nil label to jmp!!!!\n");
        exit(0);
    }

    struct lox_cmd *cmd = (struct lox_cmd *)(PC + sizeof (struct lox_cmd));

    while(cmd->cmd_opcode != LOX_NOP)
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

long lox_handle_cmp(struct lox_cmd *cmd)
{
    lox_info("-----------xxx------lox_handle_cmp\n");
    struct lox_symbol * sym = lox_find_symbol_by_label(cmd->cmd_label_index);

    if (sym && sym->sym_obj)
    {
        struct lox_object *obj = sym->sym_obj;
        lox_info("-----------xxx2------lox_handle_cmp:%d\n",obj->o_tag);
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

long lox_handle_jmp_label(struct lox_cmd *cmd)
{
    lox_info("-----------------lox_handle_jmp_label:%s\n", cmd->cmd_jmp_label);
    long ret = lox_find_label(cmd->cmd_jmp_label);
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
    lox_info("-----------------lox_handle_jmpeq_label:%s %d\n", cmd->cmd_jmp_label, SPR);
    if (SPR == 0)
    {
        lox_handle_jmp_label(cmd);
    }
    return ret;
}

