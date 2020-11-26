#include "lox_object.h"
#include <stdlib.h>
#include <string.h>


struct lox_object* lox_object_new_number(float f)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_NUMBER;
    obj->o_is_array_object = 0;
    obj->o_value.v_f = f;

    return obj;
}

struct lox_object* lox_object_new_string(char *str)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_STRING;
    obj->o_is_array_object = 0;
    obj->o_value.v_str = (char *)malloc(strlen(str)+1);
    strcpy(obj->o_value.v_str, str);
    obj->o_value.v_str = str;
    return obj;
}

struct lox_object* lox_object_new_temp(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_NIL;
    obj->o_is_array_object = 0;
    return obj;
}

struct lox_object* lox_object_new_array(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_value.v_vec = malloc(sizeof(struct lox_vector));
    obj->o_tag = LOX_ARRAY;
    obj->o_is_array_object = 0;
    obj->o_value.v_vec->len = 0;
    return obj;
}

struct lox_object* lox_object_new_func(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_FUNCTION;
    obj->o_is_array_object = 0;
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
        dst->o_value.v_str = NULL;
    }
    else if(src->o_tag == LOX_ARRAY)
    {
        dst->o_tag = LOX_ARRAY;
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
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
        dst->o_tag = LOX_ARRAY;
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
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
        dst->o_value.v_vec = malloc(sizeof (struct lox_vector));
        dst->o_value.v_vec = src->o_value.v_vec;
        src->o_value.v_vec->counter++;
    }
    else if(src->o_tag == LOX_NIL)
    {
        dst->o_tag = LOX_NIL;
    }
    return LOX_OK;
}

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
                if (v->vec_v && v->vec_v->o_tag != LOX_ARRAY)
                {
                    free(v->vec_v);
                }
                else
                {
                    lox_object_destroy_array(v->vec_v);
                }

                free(v);
                v = v_next;
            }
            free(obj->o_value.v_vec);
            obj->o_value.v_vec = NULL;
        }
    }
    return ret;
}

int lox_object_copy(struct lox_object *dst, struct lox_object *src)
{
    if (!dst || !src)
    {
        lox_info("lox_object_copy null value!!!\n");
        return LOX_ERROR(LOX_INVALID);
    }
    else if ( dst->o_tag == LOX_NUMBER)
    {
        lox_object_copy_to_number(dst, src);
    }
    else if (dst->o_tag == LOX_STRING)
    {
        lox_object_copy_to_string(dst, src);
    }
    else if (dst->o_tag == LOX_NIL)
    {
        lox_object_copy_to_nil(dst, src);
    }
    else if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_copy_to_array(dst, src);
    }
    else
    {
        lox_debug("copy invalid\n");
        return LOX_ERROR(LOX_INVALID);
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

long lox_object_destroy(struct lox_object *obj)
{
    if (obj)
    {
        if(obj->o_tag == LOX_STRING)
        {
            free(obj->o_value.v_str);
        }
    }
    return LOX_OK;
}
