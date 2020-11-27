#include "lox.h"
#include "lox_def.h"
#include "lox_stack.h"
#include "lox_function.h"
#include "lox_register.h"
#include "lox_handle.h"
int lox_linenumber = 0;

#if 0
int lox_object_copy(lox_symbol *dst, lox_symbol *src)
{
    //lox_info("--------------------------1---------------------------------------:%d %d\n", dst->o_tag, src->o_tag);
    if ( dst->o_tag == LOX_NUMBER)
    {
        if (src->o_tag == LOX_NUMBER)
        {
            dst->o_value.v_f = src->o_value.v_f;
        }
        if (src->o_tag == LOX_STRING)
        {
            dst->o_tag = LOX_STRING;
            dst->o_value.v_str =  src->o_value.v_str;
        }
    }

    if (dst->o_tag == LOX_STRING)
    {
        if (src->o_tag == LOX_STRING)
        {
            dst->o_value.v_str = src->o_value.v_str;
        }

        if (src->o_tag == LOX_NUMBER)
        {
            dst->o_tag = LOX_NUMBER;
            dst->o_value.v_f = src->o_value.v_f;
            dst->o_value.v_str = NULL;
        }
    }

    if (dst->o_tag == LOX_NIL)
    {
        dst->o_tag = src->o_tag;
        if (src->o_tag == LOX_STRING)
        {
            dst->o_value.v_str = src->o_value.v_str;
        }

        if (src->o_tag == LOX_NUMBER)
        {
            dst->o_tag = LOX_NUMBER;
            dst->o_value.v_f = src->o_value.v_f;
            dst->o_value.v_str = NULL;
        }
    }

    return LOX_OK;
}

int lox_object_add(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (obj1->o_tag == LOX_NUMBER && obj2->o_tag == LOX_NUMBER)
    {
        dst->o_tag = LOX_NUMBER;
        dst->o_value.v_f = obj1->o_value.v_f + obj2->o_value.v_f;
    }
    return LOX_OK;
}

int lox_setup_stack(void)
{
    struct lox_object *obj = lox_main_function();

    SP = 0;

    PC = (long)&obj->o_value.v_func->func_code[0];
    FP = SP;

    return LOX_OK;
}

int lox_get_var(char *name)
{
    long i = FP;
    struct lox_stack_element *stack = lox_get_stack();
    extern int lox_sp_index;
    /*
    for(i = 0; i < lox_sp_index; i++)
    {
        lox_info("scan-------stack:%d\n", stack[i].s_index_label);
    }
    */
    for(i = SP; i >= FP; i--)
    {
        if(stack[i].s_type == LOX_STACK_OBJ && strcmp(stack[i].s_v.o_name, name) == 0)
        {
            return &stack[i];
        }
    }

    return NULL;
}

void lox_handle_push_cmd(struct lox_cmd *cmd)
{
    long ret;
    struct lox_cmd_push *push_type = &cmd->cmd_push;

    lox_info("++++++++++++++++++++++++++:%d %d\n", push_type->f_label_index, push_type->p_type);

    if (push_type->p_type == PUSH_NUMBER)
    {
        lox_stack_push_numbe(push_type->f_number, push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_ARG)
    {
        lox_stack_push_arg(push_type->f_arg_name, push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_NUMBER_VAR)
    {
        ret = lox_stack_push_number_var(push_type->f_f, push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_STRING_VAR)
    {
        ret = lox_stack_push_string_var(push_type->f_str, push_type->f_label_index);
    }
    else if (push_type->p_type == PUSH_VAR)
    {
        //if (!lox_get_var(push_type->f_var_name))
        {
            ret = lox_stack_push_var(push_type->f_var_name, push_type->f_label_index);
        }
    }
    else if (push_type->p_type == PUSH_TEMP_VAR)
    {
        ret = lox_stack_push_temp_var(push_type->f_label_index);
    }
    else
    {
        lox_error("finding an invalid push cmd:%d\n", push_type->p_type);
        exit(0);
    }
    /*
    extern int lox_sp_index;
    for(int i = 0; i < lox_sp_index; i++)
    {struct lox_stack_element *stack = lox_get_stack();
        lox_info("scan----1---stack:%d\n", stack[i].s_index_label);
    }
    */
}

struct lox_stack_element *lox_find_element(long label)
{
    long i = FP;
    struct lox_stack_element *stack = lox_get_stack();
    extern int lox_sp_index;
    /*
    for(i = 0; i < lox_sp_index; i++)
    {
        lox_info("scan-------stack:%d\n", stack[i].s_index_label);
    }
    */
    for(i = SP; i >= FP; i--)
    {
        if(stack[i].s_index_label == label)
        {
            return &stack[i];
        }
    }

    return NULL;
}

void lox_handle_get_var(struct lox_cmd *cmd)
{
    long i = FP;
    struct lox_stack_element *stack = lox_get_stack();
    int find_var = 0;
    int find_var_index = 0;
    for(i = SP; i >= FP; i--)
    {
        if (stack[i].s_type == LOX_STACK_ARG)
        {
            if (strcmp(stack[i].s_name, cmd->cmd_var_name) == 0)
            {
                find_var = 1;
                find_var_index = i;
            }
        }

        if (stack[i].s_type == LOX_STACK_OBJ)
        {
            if (strcmp(stack[i].s_v.o_name, cmd->cmd_var_name) == 0)
            {
                lox_info("get var:%s\n", cmd->cmd_var_name);
                if (stack[i].s_v.o_tag == LOX_NUMBER)
                {
                    lox_info("get var:%s v:%f\n", stack[i].s_v.o_name, stack[i].s_v.o_value.v_f);
                }
                find_var_index = i;
                find_var = 1;
            }
        }
    }

    if (!find_var)
    {
        lox_error("Can not find var :%s\n", cmd->cmd_var_name);
        exit(0);
    }

    for(i = SP; i >= FP ; i--)
    {
        if (stack[i].s_index_label == cmd->cmd_reg_index)
        {
            //stack[i] = stack[find_var_index];
            struct lox_object *obj1, *obj2;
            if (stack[i].s_type == LOX_STACK_OBJ)
            {
                obj1 = &stack[i].s_v;
            }
            else
            {
                obj1 = (struct lox_object *)(stack[i].s_long);
            }

            if (stack[find_var_index].s_type == LOX_STACK_OBJ)
            {
                obj2 = &stack[find_var_index].s_v;
            }
            else
            {
                obj2 = (struct lox_object *)(stack[find_var_index].s_long);
            }

            lox_object_copy(obj1, obj2);
            break;
        }
    }
}

void lox_handle_move(struct lox_cmd *cmd)
{
    struct lox_stack_element *e1 = lox_find_element(cmd->cmd_r[0]);
    struct lox_stack_element *e2 = lox_find_element(cmd->cmd_r[1]);

    lox_info("move-------------%d %d\n", cmd->cmd_r[0], cmd->cmd_r[1]);

    struct lox_object *obj1, *obj2;

    if (e1->s_type == LOX_STACK_ARG)
    {
        obj1 = (struct lox_object *)e1->s_long;
    }
    else
    {
        obj1 = &e1->s_v;
    }
    if (e2->s_type == LOX_STACK_ARG)
    {
        obj2 = (struct lox_object *)e2->s_long;
    }
    else
    {
        obj2 = &e2->s_v;
    }
    lox_object_copy(obj1, obj2);
    lox_info("move-------------%s %f\n", obj1->o_name, obj1->o_value.v_f);
}

void lox_handle_add(struct lox_cmd *cmd)
{

    struct lox_stack_element * e1 = lox_find_element(cmd->cmd_r[0]);
    struct lox_stack_element * e2 = lox_find_element(cmd->cmd_r[1]);
    struct lox_stack_element * e3 = lox_find_element(cmd->cmd_reg_index);
    struct lox_object *obj1, *obj2, *obj3;
lox_info("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk:%d %d\n",cmd->cmd_r[0], cmd->cmd_r[1]);
    if (e1->s_type == LOX_STACK_ARG)
    {
        obj1 = (struct lox_object *)e1->s_long;
    }
    else
    {
        obj1 = &e1->s_v;
    }

    if (e2->s_type == LOX_STACK_ARG)
    {
        obj2 = (struct lox_object *)e2->s_long;
    }
    else
    {
        obj2 = &e2->s_v;
    }

    if (e3->s_type == LOX_STACK_ARG)
    {
        obj3 = (struct lox_object *)e3->s_long;
    }
    else
    {
        obj3 = &e3->s_v;
    }
    lox_info("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n");
    lox_object_add(obj1, obj2, obj3);

    lox_info("---------------add %f %f %f\n", obj1->o_value.v_f, obj2->o_value.v_f, obj3->o_value.v_f);

}

void lox_handle_jmp(struct lox_cmd *cmd)
{
    struct lox_object *obj = (struct lox_object *)cmd->cmd_r[0];
    struct lox_function *func = obj->o_value.v_func;

    struct lox_stack_element *stack = lox_get_stack();
    struct lox_stack_element *e_ret = lox_find_element(cmd->cmd_reg_index);
    struct lox_stack_element *e2;
    long last_sp = SP;
    long ret;
    int argc = cmd->cmd_r[1];
    func->func_call_args_cnt = argc;
lox_info("---------------1:%d\n",argc);
    extern unsigned int lox_var_label_index;

    lox_stack_push_numbe(last_sp, lox_var_label_index++);
    lox_stack_push_numbe(PC + sizeof (struct lox_cmd), lox_var_label_index++);
    lox_stack_push_numbe(FP, lox_var_label_index++);

    ret = lox_stack_push_arg("return", lox_var_label_index++);
    e2 = (struct lox_stack_element *)ret;
    e2->s_long = &e_ret->s_v;
    e2->s_type = LOX_STACK_RETURN;

    SP = last_sp;
lox_info("---------------3:%d %d %s\n", FP,SP, obj->o_name);
    for(int i = 0; i < func->func_def_args_cnt; i++)
    {
        struct lox_stack_element *e = lox_find_element(cmd->cmd_r[2+i]);
        struct lox_object *obj;
        if (e->s_type == LOX_STACK_ARG)
        {
            obj = (struct lox_object *)e->s_long;
        }
        else
        {
            obj = &(e->s_v);
        }

        //ret = lox_stack_push_arg(func->func_args_names[i], lox_var_label_index++);
        ret = lox_stack_push_arg(func->func_args_names[i], func->func_args[i]);
        e2 = (struct lox_stack_element *)ret;
        e2->s_long = obj;

        lox_info("---------------9:%s %f %d\n", func->func_args_names[i], obj->o_value.v_f, e->s_index_label);
    }
lox_info("---------------2\n");
    FP = last_sp;
    //SP = SP + 3;
    LR = PC + sizeof (struct lox_cmd);
    PC = &func->func_code[0];
}

void lox_handle_jmp_inner(struct lox_cmd *cmd)
{
    struct lox_object *obj = (struct lox_object *)cmd->cmd_r[0];
    struct lox_function *func = obj->o_value.v_func;
    int argc = cmd->cmd_r[1];
    func->func_call_args_cnt = argc;
    lox_info("callinng inner function:%s %d\n", obj->o_name, argc);
    int i = 0;
    for(i = 0 ; i < obj->o_value.v_func->func_call_args_cnt; i++)
    {
        struct lox_stack_element *e = lox_find_element(cmd->cmd_r[2+i]);
        struct lox_object *obj2;
        if (e->s_type == LOX_STACK_ARG)
        {
            obj2 = (struct lox_object *)e->s_long;
        }
        else
        {
            obj2 = &(e->s_v);
        }
        func->func_args_inner[i] = (long)obj2;
        lox_info("----------------__4444444444444444444:%f\n", obj2->o_value.v_f);
    }
    lox_run_inner_func((long)obj);
}

void lox_handle_return(struct lox_cmd *cmd)
{
    struct lox_stack_element *e_ret = lox_find_element(cmd->cmd_reg_index);
    struct lox_stack_element *stack = lox_get_stack();
    struct lox_stack_element *f_ret = &stack[FP + 3];

    //memcpy(f_ret, e_ret, sizeof (struct lox_stack_element));

    struct lox_object *obj1, *obj2;

    if (e_ret->s_type == LOX_STACK_ARG)
    {
        obj1 = (struct lox_object *)e_ret->s_long;
    }
    else
    {
        obj1 = &e_ret->s_v;
    }

    if (f_ret->s_type == LOX_STACK_ARG || f_ret->s_type == LOX_STACK_RETURN)
    {
        obj2 = (struct lox_object *)f_ret->s_long;
    }
    else
    {
        obj2 = &f_ret->s_v;
    }
    lox_info("-----------------------------------------------------------------:%d %d %d\n", obj1->o_tag, obj2->o_tag, f_ret->s_type);
    lox_object_copy(obj2, obj1);

    SP = stack[FP + 0].s_long;
    PC = stack[FP + 1].s_long;
    FP = stack[FP + 2].s_long;
    lox_info("------------handle return %d %d %f %d %d\n", SP, FP, e_ret->s_v.o_value.v_f, obj1->o_tag, obj2->o_tag);
}
#endif
int lox_machine_run(void)
{
    struct lox_cmd *cmd = (struct lox_cmd *)PC;
    int cmd_add = 0;
    while (cmd->cmd_opcode != LOX_NOP)
    {
        cmd_add = 1;
        lox_info("---------vm handle cmd------:%d %p %d\n",cmd->cmd_opcode, PC, SP);
        switch (cmd->cmd_opcode)
        {
            case LOX_PUSH:
                lox_handle_push_cmd(cmd);
                break;

            case LOX_MOVE:
                lox_handle_move(cmd);
                break;

            case LOX_ADD:
                lox_handle_add(cmd);
                break;

            case LOX_JMP:
                {
                    struct lox_symbol *sym = (struct lox_symbol *)cmd->cmd_args[0];
                    struct lox_function *func = sym->sym_obj->o_value.v_func;
                    if (!sym || !func)
                    {
                        lox_info("calling an null function\n");
                        exit(0);
                    }
                    if (func->is_inner_function)
                    {
                        lox_handle_jmp_inner(cmd);
                    }
                    else
                    {
                        lox_handle_jmp(cmd);
                        cmd_add = 0;
                    }
                }
            break;
        case LOX_FUNCTION_PARAM_END:
            {
                lox_handle_function_param_end(cmd);
            }
            break;

        case LOX_RETURN:
            cmd_add = 0;
            lox_handle_return(cmd);
            break;
        case LOX_END_FUNCTION:
            cmd_add = 0;
            lox_handle_function_end(cmd);
            break;

        case LOX_GET_ARRAY_VALUE:
            lox_handle_get_array_value(cmd);
            break;
        default:
            break;
        }
        if (cmd_add)
        {
            cmd++;
            PC = (long)cmd;
            cmd = (struct lox_cmd *)PC;
        }
        else
        {
            cmd = (struct lox_cmd *)PC;
        }
    }
    return LOX_OK;
}

int lox_main(void)
{
    lox_register_init();
    lox_stack_init();
    lox_function_init();
    return LOX_OK;
}

int lox_run(void)
{
    lox_setup_stack();
    lox_info("-------------------------------------------------%d\n", SP);
    lox_machine_run();
    return LOX_OK;
}


int lox_cur_line_number(void)
{
    return lox_linenumber + 1;
}
