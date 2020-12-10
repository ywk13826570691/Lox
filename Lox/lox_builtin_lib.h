#ifndef LOX_BUILTIN_LIB_H
#define LOX_BUILTIN_LIB_H
#include "lox_lib.h"

int lox_builtin_lib_init(void);
long lox_run_inner_func(long f, long *argv, int len, long ret);

#endif // LOX_BUILTIN_LIB_H
