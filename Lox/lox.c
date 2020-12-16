#include "lox.h"
#include "lox_def.h"
#include "lox_stack.h"
#include "lox_function.h"
#include "lox_register.h"
#include "lox_handle.h"
int lox_linenumber = 0;

int lox_vm_machine_run(void)
{
    struct lox_cmd *cmd = (struct lox_cmd *)PC;
    int cmd_add = 0;
    while (cmd && cmd->cmd_opcode != LOX_NOP)
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
            case LOX_SUB:
            case LOX_MUL:
            case LOX_DIV:
            case LOX_MOD:
            case LOX_PLUS:
            case LOX_MINUS:
                lox_handle_operator(cmd);
                break;

            case LOX_JMP:
                {
                    struct lox_symbol * sym = lox_find_symbol_by_label(cmd->cmd_args[0]);
                    if (!sym)
                    {
                        lox_error("calling an null function\n");
                        exit(0);
                    }
                    struct lox_function *func = sym->sym_obj->o_value.v_func;
                    if (!func)
                    {
                        lox_error("calling an null function2\n");
                        exit(0);
                    }
                    struct lox_symbol * sym2 = lox_find_function_by_addr(func);

                    lox_info("calling function:%s %s\n", sym->sym_name, sym2->sym_name);

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

        case LOX_SET_ARRAY_VALUE:
            lox_handle_set_array_value(cmd);
            break;
        case LOX_CMP:
            lox_handle_cmp(cmd);
            break;
        case LOX_LABEL:
            break;
        case LOX_JMP_LABEL:
            lox_handle_jmp_label(cmd);
            cmd_add = 0;
            break;
        case LOX_JMPEQ_LABEL:
            {
                int ret = lox_handle_jmpeq_label(cmd);
                if (ret == 0)
                    cmd_add = 0;
            }
            break;
        case LOX_JMPNEQ_LABEL:
        {
            int ret = lox_handle_jmpneq_label(cmd);
            if (ret == 1)
                cmd_add = 0;
        }
            break;
        case LOX_EQUAL:
        case LOX_NEQUAL:
        case LOX_LT:
        case LOX_GT:
        case LOX_LET:
        case LOX_GET:
            lox_handle_logical_operation(cmd);
            break;
        case LOX_AND:
            lox_handle_and(cmd);
            break;
        case LOX_OR:
            lox_handle_or(cmd);
            break;
        case LOX_CMP_IN_RANGE:
            lox_handle_cmp_inrange(cmd);
            break;
        case LOX_NOT:
            lox_handle_not(cmd);
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

int lox_vm_init(void)
{
    lox_register_init();
    lox_stack_init();
    lox_function_init();
    return LOX_OK;
}

int lox_vm_run(void)
{
    lox_setup_stack();
    lox_vm_machine_run();
    return LOX_OK;
}

int lox_cur_line_number(void)
{
    return lox_linenumber + 1;
}
