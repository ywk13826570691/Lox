#include "lox_array.h"
#include "lox_def.h"
#include <stdlib.h>

long  lox_array_index = 0;
long  lox_array_label[1000] = { 0 };

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

int lox_array_insert_obj(struct lox_object *arr, struct lox_object *obj)
{
    if (!arr || !obj)
    {
        lox_debug("lox_array_insert_obj nil\n");
    }

    struct lox_vector_value *v = malloc(sizeof (struct lox_vector_value));
    v->vec_v = obj;
    obj->o_is_array_object = 1;
    obj->o_array_object_counter++;
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
