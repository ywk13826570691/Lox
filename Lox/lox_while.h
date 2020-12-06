#ifndef LOX_WHILE_H
#define LOX_WHILE_H
int lox_while_index_increase(void);
int lox_while_index_push(long index);
int lox_while_index_pop(void);

char *lox_while_label(void);
char *lox_while_end_label(void);


int lox_while_get_cur_index(void);
#endif // LOX_WHILE_H
