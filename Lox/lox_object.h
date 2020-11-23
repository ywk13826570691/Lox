#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include "lox_def.h"

struct lox_object* lox_object_new_number(float f);
struct lox_object* lox_object_new_string(char *str);
struct lox_object* lox_object_new_temp(void);

struct lox_object* lox_object_new_func(void);


int lox_object_copy(struct lox_object *dst, struct lox_object *src);
long lox_object_add(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);

long lox_object_destroy(struct lox_object *obj);


#endif // LOX_OBJECT_H
