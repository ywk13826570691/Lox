#ifndef LOX_ARRAY_H
#define LOX_ARRAY_H
#include "lox_def.h"

long lox_array_parsing_end(void);
long lox_array_push_label(long label);

long lox_set_is_array_element(void);
long lox_get_is_array_element(void);
long lox_set_cur_element_label(long label);
long lox_array_element_index_push_label(long label);
long lox_array_element_end(void);






int lox_array_insert_obj(struct lox_object *arr, struct lox_object *obj);
long lox_array_get_object(struct lox_object *arr, long *indexs, int index_cnt);
long lox_array_set_object(struct lox_object *arr, long *indexs, int index_cnt, struct lox_object *obj_set);
long lox_array_index_value(struct lox_object *arr, long index);

int lox_arrary_equal(struct lox_object *obj1, struct lox_object *obj2);
#endif // LOX_ARRAY_H
