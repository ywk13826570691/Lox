#ifndef LOX_STACK_H
#define LOX_STACK_H
#include "lox_def.h"

#define LOX_STACK_STEP 1000
#define LOX_STACK_TOP  5
int lox_stack_init(void);
int lox_stack_increase(void);
int lox_stack_push(struct lox_symbol *s);

long * lox_get_stack(void);

long lox_stack_push_number_var(float f, long label);
long lox_stack_push_string_var(char *str, long label);
long lox_stack_push_var(char *name, long label);
long lox_stack_push_temp_var(long label);
long lox_stack_push_temp_ptr_var(long label_temp);
long lox_stack_push_array_var(long label, long *labels, long label_cnt);

long lox_find_symbol_by_name(char *s_name);
long lox_find_symbol_by_label(unsigned long label);

long lox_stack_push_value(long v);

void lox_stack_print(void);

void lox_stack_clear_and_return(void);

#endif // STACK_H
