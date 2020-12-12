#include "lox_array.h"
#include "lox_def.h"
#include "lox_object.h"
#include "lox_string.h"
#include <stdlib.h>
#include <string.h>

/*
 * For parsing array
 * Ex: a = [1,2,3,4]
 * lox_array_index cnt
 * lox_array_label--> 1,2,3,4
*/
long  lox_array_index = 0;
long  lox_array_label[1000] = { 0 };

/*
 * For parsing array[x][y]
 * lox_is_array_element: tell if is a[1][2]
 * Ex: a[1][2][3]
 * lox_array_ele_index:indx cnt
 * lox_arrary_ele_labels--> 1,2,3
*/
long lox_is_array_element = 0;
long lox_arrary_ele_cur_label = 0;

long lox_array_ele_index = 0;
long lox_arrary_ele_labels[50] = { 0 };

long lox_array_parsing_end(void)
{
    lox_array_index = 0;
    memset((void *)lox_array_label, 0, 1000*sizeof (long));
    return LOX_OK;
}

long lox_array_push_label(long label)
{
    lox_array_label[lox_array_index] = label;
    lox_array_index++;
    return lox_array_index;
}

long lox_set_is_array_element(void)
{
    lox_is_array_element = 1;
    return lox_is_array_element;
}

long lox_get_is_array_element(void)
{
    return lox_is_array_element;
}

long lox_set_cur_element_label(long label)
{
    lox_arrary_ele_cur_label = label;
    return lox_arrary_ele_cur_label;
}

long lox_array_element_index_push_label(long label)
{
    lox_arrary_ele_labels[lox_array_ele_index] = label;
    lox_array_ele_index++;
    return LOX_OK;
}

long lox_array_element_end(void)
{
    lox_is_array_element = 0;
    lox_arrary_ele_cur_label = 0;

    lox_array_ele_index = 0;
    memset(lox_arrary_ele_labels, 0, 50*sizeof (long));
    return LOX_OK;
}

int lox_array_deep_copy(struct lox_object *dst, struct lox_object *src)
{
    int ret = LOX_ERROR(LOX_INVALID);
    if (!dst || !src)
    {
        lox_error("lox_array_deep_copy nil\n");
        return ret;
    }

    struct lox_vector *vec = src->o_value.v_vec;
    if (!vec)
    {
        lox_error("lox_array_deep_copy src nil\n");
        return ret;
    }

    if (dst->o_tag == LOX_ARRAY)
    {
        lox_object_destroy_array(dst);
    }
    else
    {
        lox_object_destroy(dst);
    }

    struct lox_vector_value *v = vec->vec_head.next;
    struct lox_vector *dstvec = malloc(sizeof (struct lox_vector));
    memset(dstvec, 0, sizeof (struct lox_vector));

    dst->o_tag = LOX_ARRAY;
    dst->o_value.v_vec = dstvec;

    while(v)
    {
        if (v->vec_v)
        {
            struct lox_object *obj = lox_object_new_temp();
            if (v->vec_v->o_tag != LOX_ARRAY)
            {
                lox_object_copy(obj, v->vec_v);
                lox_array_insert_obj(dst, obj);
            }
            else
            {
                lox_array_deep_copy(obj, v->vec_v);
                lox_array_insert_obj(dst, obj);
            }
        }
        v = v->next;
    }

    return LOX_OK;
}

int lox_array_insert_obj(struct lox_object *arr, struct lox_object *obj)
{
    if (!arr || !obj)
    {
        lox_debug("lox_array_insert_obj nil\n");
    }

    struct lox_vector_value *v = malloc(sizeof (struct lox_vector_value));
    memset(v, 0, sizeof(struct lox_vector_value));
    struct lox_object *new_obj = lox_object_new_temp();
    lox_object_copy(new_obj, obj);
    v->vec_v = new_obj;

    struct lox_vector_value *vec = arr->o_value.v_vec->vec_head.next;
    if (!vec)
    {
        arr->o_value.v_vec->vec_head.next = v;
        arr->o_value.v_vec->len += 1;
        return LOX_OK;
    }
    while (vec->next)
    {
        vec = vec->next;
    }
    vec->next = v;
    arr->o_value.v_vec->len += 1;
    return  LOX_OK;
}

int lox_array_delete_obj(struct lox_object *arr, struct lox_object *obj)
{
    if (!arr || !obj)
    {
        lox_debug("lox_array_delete_obj nil\n");
    }

    struct lox_vector_value *vec = arr->o_value.v_vec->vec_head.next;
    if (!vec)
    {
        return LOX_OK;
    }
    struct lox_vector_value *vec_p = &arr->o_value.v_vec->vec_head;
    while (vec)
    {
        int obj_del = 0;
        if (vec->vec_v && vec->vec_v->o_tag == obj->o_tag)
        {
            struct lox_object *v = vec->vec_v;
            if (obj->o_tag == LOX_NUMBER)
            {
                if (obj->o_value.v_f - v->o_value.v_f < 1e-10)
                {
                    obj_del = 1;
                }
            }
            if (obj->o_tag == LOX_STRING)
            {
                if (obj->o_value.v_str && v->o_value.v_str)
                {
                    if (strcmp(obj->o_value.v_str, v->o_value.v_str) == 0)
                    {
                        obj_del = 1;
                    }
                }
            }
            if (obj->o_tag == LOX_ARRAY)
            {
                if (lox_arrary_equal(obj, v) == 0)
                {
                    obj_del = 1;
                }
            }
            if (obj->o_tag == LOX_NIL || obj->o_tag == LOX_BOOL_TRUE || obj->o_tag == LOX_BOOL_FALSE)
            {
                obj_del = 1;
            }

            if (obj_del)
            {
                vec_p->next = vec->next;
                if (v->o_tag == LOX_ARRAY)
                {
                    lox_object_destroy_array(v);
                }
                else
                {
                    lox_object_destroy(v);
                }
                free(v);
                free(vec);
                arr->o_value.v_vec->len--;
            }
        }
        vec_p = vec;
        vec =  vec->next;
    }
    return  LOX_OK;
}

int lox_array_connect_array(struct lox_object *arr1, struct lox_object *arr2)
{
    int ret = LOX_ERROR(LOX_INVALID);
    if (!arr1 || !arr2)
    {
        return ret;
    }

    struct lox_vector *vec = arr1->o_value.v_vec;
    struct lox_vector *vec2 = arr2->o_value.v_vec;

    if (!vec->vec_head.next)
    {
        vec->vec_head.next = vec2->vec_head.next;
        return LOX_OK;
    }

    if (vec && vec2)
    {
        while (vec)
        {
            if (vec->vec_head.next == NULL)
            {
                vec->vec_head.next = vec->vec_head.next;
                break;
            }
        }
    }
    return ret;
}

int lox_array_mul_number(struct lox_object *arr1, struct lox_object *obj)
{
    int ret = LOX_ERROR(LOX_INVALID);
    if (!arr1 || !obj)
    {
        return ret;
    }

    struct lox_vector *vec = arr1->o_value.v_vec;
    struct lox_vector_value *v = vec->vec_head.next;

    if (!vec->vec_head.next)
    {
        return LOX_OK;
    }

    while(v)
    {
        if (v->vec_v)
        {
            if (v->vec_v->o_tag == LOX_NUMBER)
            {
                v->vec_v->o_value.v_f = v->vec_v->o_value.v_f * obj->o_value.v_f;
            }

            if (v->vec_v->o_tag == LOX_STRING)
            {
                struct lox_object *tmp_obj = v->vec_v;
                if (tmp_obj->o_value.v_str && strlen(tmp_obj->o_value.v_str))
                {
                    if (obj->o_value.v_f >= 1.0 && lox_is_int_number(obj->o_value.v_f))
                    {
                        int k = obj->o_value.v_f;
                        tmp_obj->o_value.v_str = lox_string_repeat(tmp_obj->o_value.v_str, k);
                    }
                    else
                    {
                        lox_error("string*number must int number >= 1\n");
                        tmp_obj->o_value.v_str = (char *)malloc(1);
                        strcpy(tmp_obj->o_value.v_str, "");
                    }
                }
                else
                {
                    tmp_obj->o_value.v_str = (char *)malloc(1);
                    strcpy(tmp_obj->o_value.v_str, "");
                }
            }

            if(v->vec_v->o_tag == LOX_ARRAY)
            {
                lox_array_mul_number(v->vec_v, obj);
            }
        }
        v= v->next;
    }
    return LOX_OK;
}

int lox_array_div_number(struct lox_object *arr1, struct lox_object *obj)
{
    int ret = LOX_ERROR(LOX_INVALID);
    if (!arr1 || !obj)
    {
        return ret;
    }

    struct lox_vector *vec = arr1->o_value.v_vec;
    struct lox_vector_value *v = vec->vec_head.next;

    if (!vec->vec_head.next)
    {
        return LOX_OK;
    }

    while(v)
    {
        if (v->vec_v)
        {
            if (v->vec_v->o_tag == LOX_NUMBER)
            {
                v->vec_v->o_value.v_f = v->vec_v->o_value.v_f / obj->o_value.v_f;
            }

            if(v->vec_v->o_tag == LOX_ARRAY)
            {
                lox_array_div_number(v->vec_v, obj);
            }
        }
        v= v->next;
    }
    return LOX_OK;
}

long lox_array_get_object(struct lox_object *arr, long *indexs, int index_cnt)
{
    struct lox_object *obj = arr;
    int index = 0;

    while(1)
    {
        if (!obj || obj->o_tag != LOX_ARRAY)
        {
            lox_error("array object is not a array\n");
            exit(0);
        }
        obj = (struct lox_object *)lox_array_index_value(obj, indexs[index]);
        index++;
        if (index == index_cnt)
        {
            break;
        }
    }
    return (long)obj;
}

long lox_array_set_object(struct lox_object *arr, long *indexs, int index_cnt, struct lox_object *obj_set)
{
    struct lox_object *obj = arr;
    int index = 0;

    while(1)
    {
        if (!obj || obj->o_tag != LOX_ARRAY)
        {
            lox_error("array object is not a array\n");
            exit(0);
        }
        obj = (struct lox_object *)lox_array_index_value(obj, indexs[index]);
        index++;
        if (index == index_cnt)
        {
            break;
        }
    }
    if (obj_set)
        lox_object_copy(obj, obj_set);
    return LOX_OK;
}

long lox_array_index_value(struct lox_object *arr, long index)
{
    int i = 0;
    int arr_len = arr->o_value.v_vec->len;
    if (index >= arr_len)
    {
        lox_error("Out ot array range\n");
        exit(0);
    }
    struct lox_vector_value *v = arr->o_value.v_vec->vec_head.next;
    for (i = 0; i < index;i++)
    {
        v = v->next;
    }
    return  (long)v->vec_v;
}

int lox_arrary_equal(struct lox_object *obj1, struct lox_object *obj2)
{
    int ret = LOX_ERROR(LOX_INVALID);
    if (!obj1 || !obj2)
    {
        return ret;
    }

    if (!obj1->o_value.v_vec || !obj2->o_value.v_vec)
    {
        return ret;
    }

    if (obj1->o_value.v_vec->len != obj2->o_value.v_vec->len)
    {
        return ret;
    }

    if (obj1->o_value.v_vec->len == 0 && obj2->o_value.v_vec->len == 0)
    {
        ret = LOX_OK;
        return ret;
    }

    struct lox_vector *v1 = obj1->o_value.v_vec;
    struct lox_vector *v2 = obj2->o_value.v_vec;

    if (v1 == v2)
    {
        ret = LOX_OK;
        return ret;
    }

    struct lox_vector_value *value1 = v1->vec_head.next;
    struct lox_vector_value *value2 = v2->vec_head.next;
    while (value1 && value2)
    {
        if (!value1->vec_v && !value2->vec_v)
        {
            value1 = value1->next;
            value2 = value2->next;
            continue;
        }

        if ((value1->vec_v && !value2->vec_v) || (!value1->vec_v && value2->vec_v))
        {
            return LOX_ERROR(LOX_INVALID);
        }

        if (value1->vec_v->o_tag != value2->vec_v->o_tag)
        {
            return LOX_ERROR(LOX_INVALID);
        }

        if (value1->vec_v->o_tag == LOX_NUMBER)
        {
            if (fabs(value1->vec_v->o_value.v_f - value2->vec_v->o_value.v_f) > 1e-10)
            {
                return LOX_ERROR(LOX_INVALID);
            }
        }
        else if (value1->vec_v->o_tag == LOX_STRING)
        {
            if (strcmp(value1->vec_v->o_value.v_str, value2->vec_v->o_value.v_str))
            {
                return LOX_ERROR(LOX_INVALID);
            }
        }
        else if (value1->vec_v->o_tag == LOX_ARRAY)
        {
            int ret = lox_arrary_equal(value1->vec_v->o_value.v_vec, value2->vec_v->o_value.v_vec);
            if (ret < 0)
            {
                return LOX_ERROR(LOX_INVALID);
            }
        }
        value1 = value1->next;
        value2 = value2->next;
    }
    return LOX_OK;
}

