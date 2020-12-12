#include "lox_object.h"
#include "lox_array.h"
#include "lox_string.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


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
    else if (src->o_tag == LOX_FUNCTION)
    {
        dst->o_tag = LOX_FUNCTION;
        dst->o_value.v_func = src->o_value.v_func;
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
    else if (src->o_tag == LOX_FUNCTION)
    {
        dst->o_tag = LOX_FUNCTION;
        dst->o_value.v_func = src->o_value.v_func;
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
    else if (src->o_tag == LOX_FUNCTION)
    {
        dst->o_tag = LOX_FUNCTION;
        dst->o_value.v_func = src->o_value.v_func;
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
    else if (src->o_tag == LOX_FUNCTION)
    {
        dst->o_tag = LOX_FUNCTION;
        dst->o_value.v_func = src->o_value.v_func;
    }
    else
    {
        return LOX_ERROR(LOX_INVALID);
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
    else if (src->o_tag == LOX_FUNCTION)
    {
        dst->o_tag = LOX_FUNCTION;
        dst->o_value.v_func = src->o_value.v_func;
    }
    else
    {
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

int lox_object_copy_to_function(struct lox_object *dst, struct lox_object *src)
{
    if (src->o_tag == LOX_NUMBER)
    {
        dst->o_tag = LOX_NUMBER;
        dst->o_value.v_f = src->o_value.v_f;
        dst->o_value.v_func = NULL;
    }
    else if (src->o_tag == LOX_STRING)
    {
        dst->o_tag = LOX_STRING;
        if (src->o_value.v_str)
        {
            dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
            strcpy(dst->o_value.v_str, src->o_value.v_str);
        }
        dst->o_value.v_func = NULL;
    }
    else if (src->o_tag == LOX_NIL)
    {
        dst->o_tag = LOX_NIL;
        dst->o_value.v_func = NULL;
    }
    else if(src->o_tag == LOX_ARRAY)
    {
        dst->o_tag = LOX_ARRAY;
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
        dst->o_value.v_func = NULL;
    }
    else if (src->o_tag == LOX_BOOL_TRUE)
    {
        dst->o_tag = LOX_BOOL_TRUE;
        dst->o_value.v_func = NULL;
    }
    else if (src->o_tag == LOX_BOOL_FALSE)
    {
        dst->o_tag = LOX_BOOL_FALSE;
        dst->o_value.v_func = NULL;
    }
    else if (src->o_tag == LOX_FUNCTION)
    {
        dst->o_tag = LOX_FUNCTION;
        dst->o_value.v_func = src->o_value.v_func;
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
        if(obj->o_tag == LOX_STRING && obj->o_value.v_str)
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
                    free(o);
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
    case LOX_FUNCTION:
        lox_object_copy_to_function(dst, src);
        break;
    default:
        lox_error("lox_object_copy dst invalid type");
        break;
    }
    return LOX_OK;
}

long lox_object_number_add_number(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_NUMBER;
    dst->o_value.v_f = obj1->o_value.v_f + obj2->o_value.v_f;
    return LOX_OK;
}

long lox_object_number_add_string(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }

    dst->o_tag = LOX_STRING;
    if (obj2->o_value.v_str)
    {
        dst->o_value.v_str = malloc(strlen(obj2->o_value.v_str) + 100);
        sprintf(dst->o_value.v_str, "%s%f", obj2->o_value.v_str, obj1->o_value.v_f);
    }
    else
    {
        dst->o_value.v_str = malloc(100);
        sprintf(dst->o_value.v_str, "%f",obj1->o_value.v_f);
    }

    return LOX_OK;
}

long lox_object_number_add_array(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_ARRAY;

    lox_array_deep_copy(dst, obj2);
    lox_array_insert_obj(dst, obj1);
    return LOX_OK;
}

long lox_object_string_add_string(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_STRING;
    if (obj1->o_value.v_str && obj2->o_value.v_str)
    {
        dst->o_value.v_str = malloc(strlen(obj1->o_value.v_str) + strlen(obj2->o_value.v_str) + 2 );
        sprintf(dst->o_value.v_str, "%s%s", obj1->o_value.v_str, obj2->o_value.v_str);
    }
    return LOX_OK;
}

long lox_object_string_add_array(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_ARRAY;
    lox_array_deep_copy(dst, obj2);
    lox_array_insert_obj(dst, obj1);
    return LOX_OK;
}

long lox_object_array_add_array(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }

    dst->o_tag = LOX_ARRAY;
    struct lox_object *obj_temp = lox_object_new_temp();
    lox_array_deep_copy(dst, obj1);
    lox_array_deep_copy(obj_temp, obj2);
    lox_array_connect_array(dst, obj_temp);
    free(obj_temp);
    return LOX_OK;
}

long lox_object_add(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    lox_info("-------------------lox_object_add");
    long ret = LOX_ERROR(LOX_INVALID);
    if (!obj1 || !obj2 || !dst)
    {
        lox_error("-----lox_object_add error nil object");
        exit(0);
        return ret;
    }
    if (obj1->o_tag == LOX_NUMBER)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_number_add_number(obj1, obj2, dst);
            break;
            case LOX_STRING:
                ret = lox_object_number_add_string(obj1, obj2, dst);
                break;
            case LOX_ARRAY:
                ret = lox_object_number_add_array(obj1, obj2, dst);
                break;
            default:
                lox_error("add not support number with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_STRING)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_number_add_string(obj2, obj1, dst);
            break;
            case LOX_STRING:
                ret = lox_object_string_add_string(obj1, obj2, dst);
                break;
            case LOX_ARRAY:
                ret = lox_object_string_add_array(obj1, obj2, dst);
                break;
            default:
                lox_error("add not support string with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_ARRAY)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_number_add_array(obj2, obj1, dst);
            break;
            case LOX_STRING:
                ret = lox_object_string_add_array(obj2, obj1, dst);
                break;
            case LOX_ARRAY:
                ret = lox_object_array_add_array(obj1, obj2, dst);
                break;
            default:
                lox_error("add not support array with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }
    if (obj1->o_tag == LOX_NIL || obj1->o_tag == LOX_BOOL_TRUE || obj1->o_tag == LOX_BOOL_FALSE
            || obj1->o_tag == LOX_FUNCTION)
    {
        lox_error("lox_object_add invalid type:%d\n", obj1->o_tag);
        exit(0);
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

long lox_object_number_sub_number(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_NUMBER;
    dst->o_value.v_f = obj1->o_value.v_f - obj2->o_value.v_f;
    return LOX_OK;
}

long lox_object_string_sub_string(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    char *ret = NULL;
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_STRING;
    if (obj1->o_value.v_str && obj2->o_value.v_str)
    {
        ret = lox_replace_string(obj1->o_value.v_str, obj2->o_value.v_str, "");
        if (ret == obj1->o_value.v_str)
        {
            lox_object_copy(dst, obj1);
        }
        else
        {
            dst->o_value.v_str = ret;
        }
    }
    return LOX_OK;
}

long lox_object_array_sub_number(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_ARRAY;
    lox_array_deep_copy(dst, obj1);
    lox_array_delete_obj(dst, obj2);
    return LOX_OK;
}

long lox_object_array_sub_string(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_ARRAY;
    lox_array_deep_copy(dst, obj1);
    lox_array_delete_obj(dst, obj2);
    return LOX_OK;
}

long lox_object_array_sub_array(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_ARRAY;
    lox_array_deep_copy(dst, obj1);
    lox_array_delete_obj(dst, obj2);
    return LOX_OK;
}

long lox_object_sub(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    lox_info("-------------------lox_object_sub\n");
    int ret = LOX_ERROR(LOX_INVALID);
    if (!obj1 || !obj2 || !dst)
    {
        lox_error("-----lox_object_sub error nil object");
        exit(0);
        return ret;
    }
    if (obj1->o_tag == LOX_NUMBER)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_number_sub_number(obj1, obj2, dst);
            break;
            default:
                lox_error("sub not support number with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_STRING)
    {
        switch (obj2->o_tag)
        {
            case LOX_STRING:
                ret = lox_object_string_sub_string(obj1, obj2, dst);
                break;
            default:
                lox_error("sub not support string with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_ARRAY)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_array_sub_number(obj1, obj2, dst);
            break;
            case LOX_STRING:
                ret = lox_object_array_sub_string(obj1, obj2, dst);
                break;
            case LOX_ARRAY:
                ret = lox_object_array_sub_array(obj1, obj2, dst);
                break;
            default:
                lox_error("sub not support array with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }
    if (obj1->o_tag == LOX_NIL || obj1->o_tag == LOX_BOOL_TRUE || obj1->o_tag == LOX_BOOL_FALSE
            || obj1->o_tag == LOX_FUNCTION)
    {
        lox_error("lox_object_sub invalid type:%d\n", obj1->o_tag);
        exit(0);
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

long lox_object_mul(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    lox_info("-------------------lox_object_mul\n");
    int ret = LOX_ERROR(LOX_INVALID);
    if (!obj1 || !obj2 || !dst)
    {
        lox_error("-----lox_object_mul error nil object");
        exit(0);
        return ret;
    }
    if (obj1->o_tag == LOX_NUMBER)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_number_mul_number(obj1, obj2, dst);
                break;
            case LOX_STRING:
                ret = lox_object_number_mul_string(obj1, obj2, dst);
                break;
            case LOX_ARRAY:
                ret = lox_object_number_mul_array(obj1, obj2, dst);
                break;
            default:
                lox_error("mul not support number with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_STRING)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_number_mul_string(obj2, obj1, dst);
                break;
            default:
                lox_error("mul not support string with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_ARRAY)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                ret = lox_object_number_mul_array(obj2, obj1, dst);
            break;
                break;
            default:
                lox_error("mul not support array with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }
    if (obj1->o_tag == LOX_NIL || obj1->o_tag == LOX_BOOL_TRUE || obj1->o_tag == LOX_BOOL_FALSE
            || obj1->o_tag == LOX_FUNCTION)
    {
        lox_error("lox_object_mul invalid type:%d\n", obj1->o_tag);
        exit(0);
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}

long lox_object_number_mul_number(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_NUMBER;
    dst->o_value.v_f = obj1->o_value.v_f * obj2->o_value.v_f;
    return LOX_OK;
}

long lox_object_number_mul_string(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_STRING;
    if (obj2->o_value.v_str && strlen(obj2->o_value.v_str))
    {
        if (obj1->o_value.v_f >= 1.0 && lox_is_int_number(obj1->o_value.v_f))
        {
            int k = obj1->o_value.v_f;
            dst->o_value.v_str = lox_string_repeat(obj2->o_value.v_str, k);
        }
        else
        {
            lox_error("string*number must int number >= 1\n");
            dst->o_value.v_str = (char *)malloc(1);
            strcpy(dst->o_value.v_str, "");
        }
    }
    else
    {
        dst->o_value.v_str = (char *)malloc(1);
        strcpy(dst->o_value.v_str, "");
    }
    return  LOX_OK;
}

long lox_object_number_mul_array(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_ARRAY;
    lox_array_deep_copy(dst, obj2);
    lox_array_mul_number(dst, obj1);
    return  LOX_OK;

}

long lox_object_div(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    lox_info("-------------------lox_object_div\n");
    int ret = LOX_ERROR(LOX_INVALID);
    if (!obj1 || !obj2 || !dst)
    {
        lox_error("-----lox_object_div error nil object");
        exit(0);
        return ret;
    }
    if (obj1->o_tag == LOX_NUMBER)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                if (obj2->o_value.v_f == 0)
                {
                    lox_error("div zero error\n");
                    exit(0);
                }
                ret = lox_object_number_div_number(obj1, obj2, dst);
                break;
            default:
                lox_error("div not support number with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_ARRAY)
    {
        switch (obj2->o_tag)
        {
            case LOX_NUMBER:
                if (obj2->o_value.v_f == 0)
                {
                    lox_error("div zero error\n");
                    exit(0);
                }
                ret = lox_object_array_div_number(obj1, obj2, dst);
                break;
            default:
                lox_error("div not support array with:%d\n", obj2->o_tag);
                exit(0);
                break;
        }
    }

    if (obj1->o_tag == LOX_NIL || obj1->o_tag == LOX_BOOL_TRUE || obj1->o_tag == LOX_BOOL_FALSE
            || obj1->o_tag == LOX_FUNCTION || obj1->o_tag == LOX_STRING)
    {
        lox_error("lox_object_div invalid type:%d\n", obj1->o_tag);
        exit(0);
        return LOX_ERROR(LOX_INVALID);
    }
    return LOX_OK;
}


long lox_object_number_div_number(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_NUMBER;
    dst->o_value.v_f = obj1->o_value.v_f / obj2->o_value.v_f;
    return LOX_OK;
}

long lox_object_array_div_number(struct lox_object *obj1, struct lox_object *obj2, struct lox_object *dst)
{
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_ARRAY;
    lox_array_deep_copy(dst, obj1);
    lox_array_div_number(dst, obj2);
    return  LOX_OK;
}

long lox_object_plus(struct lox_object *obj1,  struct lox_object *dst)
{
    if(obj1->o_tag != LOX_NUMBER)
    {
        lox_error("+ plus must number\n");
        exit(0);
    }
    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }
    dst->o_tag = LOX_NUMBER;
    lox_object_copy(dst, obj1);
    return  LOX_OK;
}

long lox_object_minus(struct lox_object *obj1, struct lox_object *dst)
{
    if(obj1->o_tag != LOX_NUMBER)
    {
        if (obj1->o_tag != LOX_STRING)
        {
            lox_error("- minus must number or string:%d\n", obj1->o_tag);
            exit(0);
        }
    }

    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }

    if (obj1->o_tag == LOX_NUMBER)
    {
        dst->o_tag = LOX_NUMBER;
        lox_object_copy(dst, obj1);
        dst->o_value.v_f = dst->o_value.v_f*(-1);
    }

    if(obj1->o_tag == LOX_STRING)
    {
        dst->o_tag = LOX_STRING;
        if (obj1->o_value.v_str)
        {
            lox_object_copy(dst, obj1);
            lox_string_tolower(dst->o_value.v_str);
        }
    }

    return  LOX_OK;
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
        case LOX_FUNCTION:
            if (obj1->o_value.v_func == obj2->o_value.v_func)
            {
                obj_new.o_tag = LOX_BOOL_TRUE;
            }
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
        case LOX_FUNCTION:
            if (obj1->o_value.v_func != obj2->o_value.v_func)
            {
                obj_new.o_tag = LOX_BOOL_TRUE;
            }
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

    lox_info("lox_object_logical_operation_lt-----------[-------------------:%d %f %f\n\n", obj1->o_tag, obj1->o_value.v_f, obj2->o_value.v_f);
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
        case LOX_ARRAY:
        case LOX_BOOL_TRUE:
        case LOX_BOOL_FALSE:
        case LOX_FUNCTION:
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
        case LOX_ARRAY:
        case LOX_BOOL_TRUE:
        case LOX_BOOL_FALSE:
        case LOX_FUNCTION:
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
        case LOX_ARRAY:
            {
                int ret = lox_arrary_equal(obj1, obj2);
                if (!ret)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_NIL:
        case LOX_BOOL_TRUE:
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_TRUE;
            break;
        case LOX_FUNCTION:
            if (obj1->o_value.v_func == obj2->o_value.v_func)
            {
                obj_new.o_tag = LOX_BOOL_TRUE;
            }
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

        case LOX_ARRAY:
            {
                int ret = lox_arrary_equal(obj1, obj2);
                if (!ret)
                {
                    obj_new.o_tag = LOX_BOOL_TRUE;
                }
            }
            break;
        case LOX_NIL:
        case LOX_BOOL_TRUE:
        case LOX_BOOL_FALSE:
            obj_new.o_tag = LOX_BOOL_TRUE;
            break;
        case LOX_FUNCTION:
            if (obj1->o_value.v_func == obj2->o_value.v_func)
            {
                obj_new.o_tag = LOX_BOOL_TRUE;
            }
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

long lox_object_not(struct lox_object *obj1, struct lox_object *dst)
{
    struct lox_object obj_new;
    obj_new.o_tag = LOX_BOOL_FALSE;
    if (!dst)
    {
        lox_info("---------lox_object_not nil dst\n");
        exit(0);
    }

    if (!obj1)
    {
        obj_new.o_tag = LOX_BOOL_FALSE;
        lox_object_copy(dst, &obj_new);
        return LOX_OK;
    }

    if (obj1->o_tag == LOX_NIL)
    {
        obj_new.o_tag = LOX_BOOL_TRUE;
    }

    if (obj1->o_tag == LOX_BOOL_FALSE)
    {
        obj_new.o_tag = LOX_BOOL_TRUE;
    }

    lox_object_copy(dst, &obj_new);
    return LOX_OK;
}


char *lox_object_name(int type)
{
    static char obj_name[LOX_OBJ_END][20] =
    {
        "invalid", "number", "string", "table", "nil", "true", "false", "function", "range"
    };
    if (type < LOX_OBJ_END)
        return obj_name[type];
    return NULL;
}
