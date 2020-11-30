#include "lox.h"
#include "lox_def.h"
#include "lox_stack.h"
#include "lox_function.h"
#include "lox_register.h"
#include "lox_handle.h"
int lox_linenumber = 0;
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

        case LOX_SET_ARRAY_VALUE:
            lox_handle_set_array_value(cmd);
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
    lox_machine_run();
    return LOX_OK;
}


int lox_cur_line_number(void)
{
    return lox_linenumber + 1;
}
