#include "lox_object.h"
#include "lox_array.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct lox_object* lox_object_new_number(float f)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    memset(obj, 0, sizeof (struct lox_object));
    obj->o_tag = LOX_NUMBER;
    obj->o_value.v_f = f;
    return obj;
}

struct lox_object* lox_object_new_string(char *str)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    memset(obj, 0, sizeof (struct lox_object));
    obj->o_tag = LOX_STRING;
    obj->o_value.v_str = (char *)malloc(strlen(str)+1);
    strcpy(obj->o_value.v_str, str);
    return obj;
}

struct lox_object* lox_object_new_temp(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    memset(obj, 0, sizeof (struct lox_object));
    obj->o_tag = LOX_NIL;
    return obj;
}

struct lox_object* lox_object_new_bool(int v)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    memset(obj, 0, sizeof (struct lox_object));
    if (v)
        obj->o_tag = LOX_BOOL_TRUE;
    else
        obj->o_tag = LOX_BOOL_FALSE;
    return obj;
}

struct lox_object* lox_object_new_array(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    memset(obj, 0, sizeof (struct lox_object));
    obj->o_value.v_vec = malloc(sizeof(struct lox_vector));
    obj->o_tag = LOX_ARRAY;
    obj->o_value.v_vec->len = 0;
    obj->o_value.v_vec->vec_head.next = NULL;
    return obj;
}

struct lox_object* lox_object_new_range(int min, int len)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    memset(obj, 0, sizeof (struct lox_object));
    obj->o_tag = LOX_RANGE;
    obj->o_value.v_range.min = min;
    obj->o_value.v_range.len = len;
    obj->o_value.v_range.index = min;
    return obj;
}

struct lox_object* lox_object_new_func(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    memset(obj, 0, sizeof (struct lox_object));
    obj->o_tag = LOX_FUNCTION;
    return obj;
}

// dst is number
int lox_object_copy_to_number(struct lox_object *dst, struct lox_object *src)
{
    if (src->o_tag == LOX_NUMBER)
    {
        dst->o_value.v_f = src->o_value.v_f;
    }
    else if (src->o_tag == LOX_STRING)
    {
        dst->o_tag = LOX_STRING;
        dst->o_value.v_f = 0.0;
        if (src->o_value.v_str)
        {
            dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
            strcpy(dst->o_value.v_str, src->o_value.v_str);
        }
    }
    else if (src->o_tag == LOX_NIL)
    {
        dst->o_tag = LOX_NIL;
        dst->o_value.v_f = 0;
    }
    else if(src->o_tag == LOX_ARRAY)
    {
        dst->o_tag = LOX_ARRAY;
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
        dst->o_value.v_f = 0.0;
    }
    else if (src->o_tag == LOX_BOOL_TRUE)
    {
        dst->o_tag = LOX_BOOL_TRUE;
        dst->o_value.v_f = 0.0;
    }
    else if (src->o_tag == LOX_BOOL_FALSE)
    {
        dst->o_tag = LOX_BOOL_FALSE;
        dst->o_value.v_f = 0.0;
    }
    else
    {
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

// dst is string
int lox_object_copy_to_string(struct lox_object *dst, struct lox_object *src)
{
    if (dst->o_value.v_str)
    {
        free(dst->o_value.v_str);
        dst->o_value.v_str = NULL;
    }
    if (src->o_tag == LOX_STRING)
    {
        if (src->o_value.v_str)
        {
            dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
            strcpy(dst->o_value.v_str, src->o_value.v_str);
        }
    }
    else if (src->o_tag == LOX_NUMBER)
    {
        dst->o_tag = LOX_NUMBER;
        dst->o_value.v_f = src->o_value.v_f;
        dst->o_value.v_str = NULL;
    }
    else if(src->o_tag == LOX_NIL)
    {
        dst->o_tag = LOX_NIL;
    }
    else if(src->o_tag == LOX_ARRAY)
    {
        dst->o_tag = LOX_ARRAY;
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
    }
    else if (src->o_tag == LOX_BOOL_TRUE)
    {
        dst->o_tag = LOX_BOOL_TRUE;
    }
    else if (src->o_tag == LOX_BOOL_FALSE)
    {
        dst->o_tag = LOX_BOOL_FALSE;
    }
    else
    {
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

// dst is nil
int lox_object_copy_to_nil(struct lox_object *dst, struct lox_object *src)
{
    dst->o_tag = src->o_tag;
    if (src->o_tag == LOX_STRING)
    {
        if (src->o_value.v_str)
        {
            dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
            strcpy(dst->o_value.v_str, src->o_value.v_str);
        }
    }
    else if (src->o_tag == LOX_NUMBER)
    {
        dst->o_value.v_f = src->o_value.v_f;
    }
    else if(src->o_tag == LOX_ARRAY)
    {
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
    }
    else if (src->o_tag == LOX_BOOL_TRUE)
    {
        dst->o_tag = LOX_BOOL_TRUE;
    }
    else if (src->o_tag == LOX_BOOL_FALSE)
    {
        dst->o_tag = LOX_BOOL_FALSE;
    }
    else
    {
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

// dst is array
int lox_object_copy_to_array(struct lox_object *dst, struct lox_object *src)
{
    lox_object_destroy_array(dst);
    dst->o_tag = src->o_tag;
    if (src->o_tag == LOX_STRING)
    {
        if (src->o_value.v_str)
        {
            dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
            strcpy(dst->o_value.v_str, src->o_value.v_str);
        }
    }
    else if (src->o_tag == LOX_NUMBER)
    {
        dst->o_value.v_f = src->o_value.v_f;
    }
    else if(src->o_tag == LOX_ARRAY)
    {
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
    }
    else if(src->o_tag == LOX_NIL)
    {
        dst->o_tag = LOX_NIL;
    }
    else if (src->o_tag == LOX_BOOL_TRUE)
    {
        dst->o_tag = LOX_BOOL_TRUE;
    }
    else if (src->o_tag == LOX_BOOL_FALSE)
    {
        dst->o_tag = LOX_BOOL_FALSE;
    }
    return LOX_OK;
}

int lox_object_copy_to_bool(struct lox_object *dst, struct lox_object *src)
{
    if (src->o_tag == LOX_NUMBER)
    {
        dst->o_tag = LOX_NUMBER;
        dst->o_value.v_f = src->o_value.v_f;
    }
    else if (src->o_tag == LOX_STRING)
    {
        dst->o_tag = LOX_STRING;
        if (src->o_value.v_str)
        {
            dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
            strcpy(dst->o_value.v_str, src->o_value.v_str);
        }
    }
    else if (src->o_tag == LOX_NIL)
    {
        dst->o_tag = LOX_NIL;
    }
    else if(src->o_tag == LOX_ARRAY)
    {
        dst->o_tag = LOX_ARRAY;
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
    }
    else if (src->o_tag == LOX_BOOL_TRUE)
    {
        dst->o_tag = LOX_BOOL_TRUE;
    }
    else if (src->o_tag == LOX_BOOL_FALSE)
    {
        dst->o_tag = LOX_BOOL_FALSE;
    }
    else
    {
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

long lox_object_destroy(struct lox_object *obj1)
{
    struct lox_object *obj = obj1;
    if (obj)
    {
        if(obj->o_tag == LOX_STRING)
        {
            free(obj->o_value.v_str);
        }
    }
    return LOX_OK;
}

// counter is zero of arr
int lox_object_destroy_array(struct lox_object *obj)
{

    int ret = LOX_OK;

    if (obj && obj->o_value.v_vec)
    {
        obj->o_value.v_vec->counter--;
        if (obj->o_value.v_vec->counter == 0)
        {
            struct lox_vector_value *v = obj->o_value.v_vec->vec_head.next;
            while(v)
            {
                struct lox_vector_value *v_next = v->next;
                struct lox_object *o = v->vec_v;
                if (o->o_tag == LOX_ARRAY)
                {
                    lox_object_destroy_array(o);
                }
                else
                {
                    lox_object_destroy(o);
                    free(o);
                }
                free(v);
                v = v_next;
            }
            free(obj->o_value.v_vec);
        }
    }
    return ret;
}

int lox_object_increase(struct lox_object *obj)
{
    if (obj && obj->o_counter > 0)
    {
        obj->o_counter--;
    }
    return LOX_OK;
}

int lox_object_decrease(struct lox_object *obj)
{
    if (obj)
    {
        obj->o_counter++;
    }
    return LOX_OK;
}

int lox_object_copy(struct lox_object *dst, struct lox_object *src)
{
    if (!dst || !src)
    {
        lox_info("lox_object_copy null value!!!\n");
        return LOX_ERROR(LOX_INVALID);
    }

    switch (dst->o_tag) {
    case LOX_NUMBER:
        lox_object_copy_to_number(dst, src);
        break;
    case LOX_STRING:
        lox_object_copy_to_string(dst, src);
        break;
    case LOX_NIL:
        lox_object_copy_to_nil(dst, src);
        break;
    case LOX_ARRAY:
        lox_object_copy_to_array(dst, src);
        break;
    case LOX_BOOL_TRUE:
    case LOX_BOOL_FALSE:
        lox_object_copy_to_bool(dst, src);
        break;
    default:
        lox_error("lox_object_copy dst invalid type");
        break;
    }
    return LOX_OK;
}

long lox_object_add(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (obj1->o_tag == LOX_NUMBER && obj2->o_tag == LOX_NUMBER)
    {
        dst->o_tag = LOX_NUMBER;
        dst->o_value.v_f = obj1->o_value.v_f + obj2->o_value.v_f;
    }
    return LOX_OK;
}

long lox_object_logical_operation(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst, int opcode)
{
    if (!obj1 || !obj2 || !dst)
    {
        lox_error("---------logical opearation nil obj\n");
        exit(0);
    }
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    switch (opcode)
    {
        case LOX_EQUAL:
            lox_object_logical_operation_eq(obj1, obj2, dst);
            break;
        case LOX_NEQUAL:
            lox_object_logical_operation_neq(obj1, obj2, dst);
            break;
        case LOX_LT:
            lox_object_logical_operation_lt(obj1, obj2, dst);
            break;
        case LOX_GT:
            lox_object_logical_operation_gt(obj1, obj2, dst);
            break;
        case LOX_LET:
            lox_object_logical_operation_let(obj1, obj2, dst);
            break;
        case LOX_GET:
            lox_object_logical_operation_get(obj1, obj2, dst);
            break;
        default:
            lox_object_copy(dst, &obj_new);
            break;
    }

    return LOX_OK;
}

long lox_object_logical_operation_eq(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if (obj1->o_tag != obj2->o_tag)
    {
        lox_info("---------logical opearation eq type not equal:%d %d\n", obj1->o_tag, obj2->o_tag);
        lox_object_copy(dst, &obj_new);
        return  LOX_OK;
    }
    switch (obj1->o_tag)
    {
        case LOX_NUMBER:
            {
                if (fabs(obj1->o_value.v_f - obj2->o_value.v_f) < 1e-10)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_STRING:
            {
                if (obj1->o_value.v_str && obj2->o_value.v_str)
                {
                    if (strcmp(obj1->o_value.v_str, obj2->o_value.v_str) == 0)
                    {
                        obj_new.o_tag = LOX_BOOL_TRUE;
                    }
                }
            }
            break;
        case LOX_NIL:
            obj_new.o_tag = LOX_BOOL_TRUE;
            break;
        case LOX_ARRAY:
            if(obj1->o_value.v_vec && obj2->o_value.v_vec)
            {
                if (obj1->o_value.v_vec == obj2->o_value.v_vec)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
                else
                {
                    if (obj1->o_value.v_vec->len == obj2->o_value.v_vec->len)
                    {
                        int ret = lox_arrary_equal(obj1, obj2);
                        if (ret == 0)
                        {
                            obj_new.o_tag = LOX_BOOL_TRUE;
                        }
                    }
                }
            }
            break;
        case LOX_BOOL_TRUE:
            obj_new.o_tag = LOX_BOOL_TRUE;
            break;
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_TRUE;
            break;
        default:
            break;
    }
    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}

long lox_object_logical_operation_neq(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if (obj1->o_tag != obj2->o_tag)
    {
        lox_info("---------logical opearation neq type not equal:%d %d\n", obj1->o_tag, obj2->o_tag);
        obj_new.o_tag = LOX_BOOL_TRUE;
        lox_object_copy(dst, &obj_new);
        return  LOX_OK;
    }
    switch (obj1->o_tag)
    {
        case LOX_NUMBER:
            {
                if (fabs(obj1->o_value.v_f - obj2->o_value.v_f) > 1e-10)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_STRING:
            {
                if (obj1->o_value.v_str && obj2->o_value.v_str)
                {
                    if (strcmp(obj1->o_value.v_str, obj2->o_value.v_str))
                    {
                        obj_new.o_tag = LOX_BOOL_TRUE;
                    }
                }
                else
                {
                    if (!obj1->o_value.v_str && obj2->o_value.v_str)
                        obj_new.o_tag = LOX_BOOL_TRUE;
                    if (obj1->o_value.v_str && !obj2->o_value.v_str)
                        obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_NIL:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_ARRAY:
            if(obj1->o_value.v_vec && obj2->o_value.v_vec)
            {
                if (obj1->o_value.v_vec != obj2->o_value.v_vec)
                {
                    int ret = lox_arrary_equal(obj1, obj2);
                    if (ret < 0)
                        obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            else
            {
                if(!obj1->o_value.v_vec && obj2->o_value.v_vec)
                    obj_new.o_tag = LOX_BOOL_TRUE;
                if(obj1->o_value.v_vec && !obj2->o_value.v_vec)
                    obj_new.o_tag = LOX_BOOL_TRUE;
            }
            break;
        case LOX_BOOL_TRUE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        default:
            break;
    }
    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}

long lox_object_logical_operation_lt(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if ((obj1->o_tag != obj2->o_tag))
    {
        lox_info("---------logical opearation lt type not equal:%d %d\n", obj1->o_tag, obj2->o_tag);
        lox_object_copy(dst, &obj_new);
        return  LOX_OK;
    }

    switch (obj1->o_tag)
    {
        case LOX_NUMBER:
            {
                if (obj1->o_value.v_f - obj2->o_value.v_f < 0)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_STRING:
            {
                if (obj1->o_value.v_str && obj2->o_value.v_str)
                {
                    if (strcmp(obj1->o_value.v_str, obj2->o_value.v_str) < 0)
                    {
                        obj_new.o_tag = LOX_BOOL_TRUE;
                    }
                }
            }
            break;
        case LOX_NIL:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_ARRAY:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_TRUE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        default:
            break;
    }
    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}

long lox_object_logical_operation_gt(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if ((obj1->o_tag != obj2->o_tag))
    {
        lox_info("---------logical opearation gt type not equal:%d %d\n", obj1->o_tag, obj2->o_tag);
        lox_object_copy(dst, &obj_new);
        return  LOX_OK;
    }

    switch (obj1->o_tag)
    {
        case LOX_NUMBER:
            {
                if (obj1->o_value.v_f - obj2->o_value.v_f > 0)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_STRING:
            {
                if (obj1->o_value.v_str && obj2->o_value.v_str)
                {
                    if (strcmp(obj1->o_value.v_str, obj2->o_value.v_str) > 0)
                    {
                        obj_new.o_tag = LOX_BOOL_TRUE;
                    }
                }
            }
            break;
        case LOX_NIL:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_ARRAY:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_TRUE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        default:
            break;
    }
    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}

long lox_object_logical_operation_let(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if ((obj1->o_tag != obj2->o_tag))
    {
        lox_info("---------logical opearation let type not equal:%d %d\n", obj1->o_tag, obj2->o_tag);
        lox_object_copy(dst, &obj_new);
        return  LOX_OK;
    }

    switch (obj1->o_tag)
    {
        case LOX_NUMBER:
            {
                if (obj1->o_value.v_f - obj2->o_value.v_f < 0 || fabs(obj1->o_value.v_f - obj2->o_value.v_f) < 1e-10)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_STRING:
            {
                if (obj1->o_value.v_str && obj2->o_value.v_str)
                {
                    if (strcmp(obj1->o_value.v_str, obj2->o_value.v_str) < 0 || strcmp(obj1->o_value.v_str, obj2->o_value.v_str) == 0)
                    {
                        obj_new.o_tag = LOX_BOOL_TRUE;
                    }
                }
            }
            break;
        case LOX_NIL:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_ARRAY:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_TRUE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        default:
            break;
    }
    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}

long lox_object_logical_operation_get(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if ((obj1->o_tag != obj2->o_tag))
    {
        lox_info("---------logical opearation get type not equal:%d %d\n", obj1->o_tag, obj2->o_tag);
        lox_object_copy(dst, &obj_new);
        return  LOX_OK;
    }

    switch (obj1->o_tag)
    {
        case LOX_NUMBER:
            {
                if (obj1->o_value.v_f - obj2->o_value.v_f > 0 || fabs(obj1->o_value.v_f - obj2->o_value.v_f) < 1e-10)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_STRING:
            {
                if (obj1->o_value.v_str && obj2->o_value.v_str)
                {
                    if (strcmp(obj1->o_value.v_str, obj2->o_value.v_str) > 0 || strcmp(obj1->o_value.v_str, obj2->o_value.v_str) == 0)
                    {
                        obj_new.o_tag = LOX_BOOL_TRUE;
                    }
                }
            }
            break;
        case LOX_NIL:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_ARRAY:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_TRUE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_FALSE;
            break;
        default:
            break;
    }
    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}

long lox_object_and(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if (!dst)
    {
        lox_info("---------lox_object_and nil dst\n");
        exit(0);
    }
    if (!obj1 || !obj2)
    {
        lox_object_copy(dst, &obj_new);
        return LOX_OK;
    }

    if (obj1->o_tag != LOX_NIL && obj2->o_tag != LOX_NIL)
    {
        if (obj1->o_tag != LOX_BOOL_FALSE && obj2->o_tag != LOX_BOOL_FALSE)
        {
            obj_new.o_tag = LOX_BOOL_TRUE;
        }
    }
    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}

long lox_object_or(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_TRUE;
    if (!dst)
    {
        lox_info("---------lox_object_or nil dst\n");
        exit(0);
    }
    if (!obj1 || !obj2)
    {
        obj_new.o_tag = LOX_BOOL_FALSE;
        lox_object_copy(dst, &obj_new);
        return LOX_OK;
    }

    if (obj1->o_tag == LOX_NIL && obj2->o_tag == LOX_NIL)
    {
        obj_new.o_tag = LOX_BOOL_FALSE;
    }

    if (obj1->o_tag == LOX_BOOL_FALSE && obj2->o_tag == LOX_BOOL_FALSE)
    {
        obj_new.o_tag = LOX_BOOL_FALSE;
    }

    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}
