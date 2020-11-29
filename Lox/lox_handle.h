#ifndef LOX_HANDLE_H
#define LOX_HANDLE_H
#include "lox_def.h"

int lox_setup_stack(void);

long lox_handle_push_cmd(struct lox_cmd *cmd);
long lox_handle_move(struct lox_cmd *cmd);
long lox_handle_add(struct lox_cmd *cmd);

long lox_handle_jmp_inner(struct lox_cmd *cmd);
long lox_handle_jmp(struct lox_cmd *cmd);

long lox_handle_function_param_end(struct lox_cmd *cmd);
long lox_handle_return(struct lox_cmd *cmd);
long lox_handle_function_end(struct lox_cmd *cmd);

long lox_handle_get_array_value(struct lox_cmd *cmd);
long lox_handle_set_array_value(struct lox_cmd *cmd);

#endif // LOX_HANDLE_H
