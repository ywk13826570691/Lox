#ifndef LOX_REPEAT_H
#define LOX_REPEAT_H

int lox_repeat_index_increase(void);
int lox_repeat_index_push(long index);
int lox_repeat_index_pop(void);

char *lox_repeat_label(void);
char *lox_repeat_end_label(void);


int lox_repeat_get_cur_index(void);

#endif // LOX_REPEAT_H
