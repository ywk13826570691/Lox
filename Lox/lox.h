#ifndef LOX_H
#define LOX_H
#include "lox_def.h"

int lox_vm_init(void);
int lox_vm_run(void);
int lox_cur_line_number(void);

#endif // LOX_H
