#ifndef LOX_ARRAY_H
#define LOX_ARRAY_H
#include "lox_def.h"

long lox_array_parsing_end(void);
long lox_array_push_label(long label);





int lox_array_insert_obj(struct lox_object *arr, struct lox_object *obj);

#endif // LOX_ARRAY_H
