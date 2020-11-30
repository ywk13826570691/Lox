#ifndef LOX_FUNCTION_H
#define LOX_FUNCTION_H

#include "lox_def.h"

struct lox_function_calling
{
    char name[100];
    long func;

    long args[1000];
    int argc;
};

int lox_function_init(void);

struct lox_symbol *lox_new_function(char *name);
int lox_register_func(struct lox_symbol *f);
long lox_find_function(char *name);

struct lox_symbol * lox_get_cur_parsing_function(void);
int lox_cur_parsing_function_end(void);
int lox_set_cur_parsing_function(long f);

int lox_set_cur_calling_function(long f);
struct lox_function_calling *lox_get_cur_calling_function(void);


int lox_push_cur_calling_function(long f);
int lox_pop_cur_calling_function(void);


struct lox_symbol *lox_get_main_function(void);


int lox_func_push_cmd(struct lox_cmd *cmd);

int lox_func_add_arg_name(char *name);


int lox_func_push_arg_label(long label);


int lox_func_check_args(long f);

int lox_func_before_call(long f);


long lox_add_local_symbol(char *name, long label);
void lox_local_symbol_destory(void);
int lox_find_local_symbol(char *name);


int lox_func_has_arg(char *arg_name, long f);
int lox_func_clear(long f);






void lox_func_scan(long f);
















// inner function
typedef void (*func_inner)(struct lox_symbol *s, long *, int, long);
struct lox_inner_function
{
    char name[LOX_VAR_MAX_NAME_LEN];
    func_inner func;
    int func_args_define;
};

int lox_inner_func_init(void);
long lox_run_inner_func(long f, long *argv, int len, long ret);



#endif // LOX_H
