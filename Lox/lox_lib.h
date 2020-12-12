#ifndef LOX_LIB_H
#define LOX_LIB_H
#include "lox_config.h"
#include "lox_def.h"

typedef void (*lox_lib_func)(struct lox_symbol *s, long *argv, int argc, long ret);

struct lox_lib
{
    char lib_name[LOX_VAR_MAX_NAME_LEN];
    char name[LOX_VAR_MAX_NAME_LEN];
    lox_lib_func func;
    int func_argc;
    struct lox_symbol *s;
};

int lox_lib_init(void);
int lox_lib_register( struct lox_lib *lib);
long lox_run_lib_func(long f, long *argv, int len, long ret);

int lox_is_lib_func(char *name);

#endif // LOX_LIB_H
