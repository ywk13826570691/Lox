#ifndef LOX_IF_H
#define LOX_IF_H

int lox_if_index_increase(void);
int lox_if_index_push(int index);
int lox_if_index_pop(void);

char *lox_if_label(void);
char *lox_else_label(void);
char *lox_elseif_label(void);
char *lox_if_end_label(void);

int lox_if_get_cur_index(void);



#endif // LOX_IF_H
