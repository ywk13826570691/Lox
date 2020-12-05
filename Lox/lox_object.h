#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include "lox_def.h"

struct lox_object* lox_object_new_number(float f);
struct lox_object* lox_object_new_string(char *str);
struct lox_object* lox_object_new_temp(void);
struct lox_object* lox_object_new_bool(int v);
struct lox_object* lox_object_new_array(void);
struct lox_object* lox_object_new_range(int min, int len);

struct lox_object* lox_object_new_func(void);

int lox_object_increase(struct lox_object *obj);
int lox_object_decrease(struct lox_object *obj);
int lox_object_copy(struct lox_object *dst, struct lox_object *src);
int lox_object_copy_to_number(struct lox_object *dst, struct lox_object *src);
int lox_object_copy_to_string(struct lox_object *dst, struct lox_object *src);
int lox_object_copy_to_nil(struct lox_object *dst, struct lox_object *src);
int lox_object_copy_to_array(struct lox_object *dst, struct lox_object *src);
int lox_object_copy_to_bool(struct lox_object *dst, struct lox_object *src);
int lox_object_destroy_array(struct lox_object *obj);
long lox_object_destroy(struct lox_object *obj1);

long lox_object_add(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_logical_operation(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst, int opcode);
long lox_object_logical_operation_eq(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_logical_operation_neq(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_logical_operation_lt(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_logical_operation_gt(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_logical_operation_let(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_logical_operation_get(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_and(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);
long lox_object_or(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst);



#endif // LOX_OBJECT_H
