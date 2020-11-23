#include "lox_object.h"
#include <stdlib.h>
#include <string.h>


struct lox_object* lox_object_new_number(float f)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_NUMBER;
    obj->o_value.v_f = f;

    return obj;
}

struct lox_object* lox_object_new_string(char *str)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_STRING;
    obj->o_value.v_str = (char *)malloc(strlen(str)+1);
    strcpy(obj->o_value.v_str, str);
    obj->o_value.v_str = str;
    return obj;
}

struct lox_object* lox_object_new_temp(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_NIL;
    return obj;
}

struct lox_object* lox_object_new_func(void)
{
    struct lox_object *obj = (struct lox_object *)malloc(sizeof (struct lox_object));
    obj->o_tag = LOX_FUNCTION;
    return obj;
}

int lox_object_copy(struct lox_object *dst, struct lox_object *src)
{
    if (!dst || !src)
    {
        lox_info("lox_object_copy null value!!!\n");
        return LOX_ERROR(LOX_INVALID);
    }

    if ( dst->o_tag == LOX_NUMBER)
    {
        if (src->o_tag == LOX_NUMBER)
        {
            dst->o_value.v_f = src->o_value.v_f;
        }

        if (src->o_tag == LOX_STRING)
        {
            dst->o_tag = LOX_STRING;
            dst->o_value.v_f = 0.0;
            if (src->o_value.v_str)
            {
                dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
                strcpy(dst->o_value.v_str, src->o_value.v_str);
            }
        }
    }

    if (dst->o_tag == LOX_STRING)
    {
        if (src->o_tag == LOX_STRING)
        {
            if (src->o_value.v_str)
            {
                if(dst->o_value.v_str)
                {
                    free(dst->o_value.v_str);
                }
                dst->o_value.v_str = malloc(strlen(src->o_value.v_str) + 1);
                strcpy(dst->o_value.v_str, src->o_value.v_str);
            }
        }

        if (src->o_tag == LOX_NUMBER)
        {
            dst->o_tag = LOX_NUMBER;
            dst->o_value.v_f = src->o_value.v_f;
            dst->o_value.v_str = NULL;
        }
    }

    if (dst->o_tag == LOX_NIL)
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

        if (src->o_tag == LOX_NUMBER)
        {
            dst->o_value.v_f = src->o_value.v_f;
            if (dst->o_value.v_str)
            {
                free(dst->o_value.v_str);
                dst->o_value.v_str = NULL;
            }
        }
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
