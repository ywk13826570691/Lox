#include "lox_array.h"
#include "lox_def.h"
#include <stdlib.h>

long  lox_array_index = 0;
long  lox_array_label[1000] = { 0 };

long lox_array_parsing_end(void)
{
    lox_array_index = 0;
    memset((void *)lox_array_label, 0, 1000);
    return LOX_OK;
}

long lox_array_push_label(long label)
{
    lox_array_label[lox_array_index] = label;
    lox_array_index++;
    return lox_array_index;
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
        return LOX_OK;
    }

    while (vec->next)
    {
        vec = vec->next;
    }
    vec->next = v;
    obj->o_value.v_vec->len += 1;
    return  LOX_OK;
}
