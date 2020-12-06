#ifndef LOX_LOOP_H
#define LOX_LOOP_H

int lox_is_loop_parsing(void);
int lox_push_loop_index(void);
int lox_pop_loop_index(void);

int lox_push_loop_end_label(char *label);
int lox_pop_loop_end_label(void);
char * lox_get_cur_loop_end_label(void);





int lox_push_loop_start_label(char *label);
int lox_pop_loop_start_label(void);
char * lox_get_cur_loop_start_label(void);

#endif // LOX_LOOP_H
