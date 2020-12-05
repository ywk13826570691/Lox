#ifndef LOX_FOREACH_H
#define LOX_FOREACH_H
int lox_foreach_index_increase(void);
int lox_foreach_index_push(long index);
int lox_foreach_index_pop(void);

char *lox_foreach_label(void);
char *lox_foreach_end_label(void);


int lox_freach_get_cur_index(void);

#endif // LOX_FOREACH_H
