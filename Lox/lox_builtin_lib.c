#include <stdlib.h>
#include <string.h>
#include "lox_builtin_lib.h"
#include "lox_object.h"



void lox_print_array(struct lox_object *obj)
{
    if (!obj->o_value.v_vec)
    {
        return;
    }

    if(!obj->o_value.v_vec->len)
    {
        printf("[,]\n");
        return;
    }

    struct lox_vector *vec = obj->o_value.v_vec;
    struct lox_vector_value *v = vec->vec_head.next;

    printf("[ ");

    while(v)
    {
        if (v->vec_v)
        {
            switch (v->vec_v->o_tag)
            {
             case LOX_NUMBER:
                printf("%f ", v->vec_v->o_value.v_f);
                break;
            case LOX_STRING:
                printf("%s ", v->vec_v->o_value.v_str);
                break;
            case LOX_ARRAY:
                lox_print_array(v->vec_v);
                break;
            default:
                printf("''");
                break;
            }
        }
        v = v->next;
    }
    printf("]");
}

static void lox_inner_printf(struct lox_symbol * sym, long *argv, int len, long ret)
{
    int i = 0;
    for(i = 0; i < len; i++)
    {
        struct lox_object *obj = (struct lox_object *)argv[i];
        if (obj)
        {
            switch (obj->o_tag)
            {
                case LOX_NUMBER:
                    printf("%f ", obj->o_value.v_f);
                    break;
                case LOX_STRING:
                    printf("%s ", obj->o_value.v_str);
                    break;
                case LOX_ARRAY:
                    lox_print_array(obj);
                    break;
                default:
                    printf("%s ", lox_object_name(obj->o_tag));
                    break;
            }
        }
    }
    printf("\n");
    lox_info("calling print\n");
}

static void lox_inner_type(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    char type[50] = "nil";
    strcpy(type, "nil");

    strcpy(type, lox_object_name(obj->o_tag));

    if (re && re->sym_obj)
    {
        struct lox_object *result = lox_object_new_string(type);
        lox_object_copy(re->sym_obj, result);
        free(result);
    }
}

static void lox_inner_len(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;
    int ret_v = -1;
    if (obj && len == 1)
    {
        if(obj->o_tag == LOX_STRING && obj->o_value.v_str)
        {
            ret_v = strlen(obj->o_value.v_str);
        }

        if(obj->o_tag == LOX_ARRAY && obj->o_value.v_vec)
        {
            ret_v = obj->o_value.v_vec->len;
        }
    }

    if (re && re->sym_obj)
    {
        struct lox_object *result = lox_object_new_number((float)ret_v);
        lox_object_copy(re->sym_obj, result);
        free(result);
    }
}

static struct lox_lib builtin_func_table[] =
{
    {"builtin", "print", lox_inner_printf , 1000, NULL},
    {"builtin", "type",  lox_inner_type , 1, NULL},
    {"builtin", "len",   lox_inner_len, 1, NULL}
};

#define INNER_FUNC_COUNT (sizeof(builtin_func_table)/sizeof(builtin_func_table[0]))

int lox_builtin_lib_init(void)
{
    unsigned int i = 0;
    for (i = 0; i < INNER_FUNC_COUNT; i++)
    {
#if 0
        struct lox_symbol *sym = (struct lox_symbol*)malloc(sizeof (struct lox_symbol));
        memset(sym, 0, sizeof (struct lox_symbol));

        struct lox_object *obj = lox_object_new_func();
        sym->sym_obj = obj;

        struct lox_function *func;

        func = (struct lox_function*)malloc(sizeof (struct lox_function));
        sym->sym_obj->o_value.v_func = func;

        func->is_inner_function = 1;
        func->func_def_args_cnt = builtin_func_table[i].func_argc;
        strcpy(sym->sym_name, builtin_func_table[i].name);

        builtin_func_table[i].s = sym;
        lox_register_func(sym);
#endif
        lox_lib_register(&builtin_func_table[i]);
    }
    return LOX_OK;
}

long lox_run_inner_func(long f, long *argv, int len, long ret)
{
    struct lox_symbol *sym = (struct lox_symbol*)f;
    struct lox_symbol *re = (struct lox_symbol *)ret;
    for (unsigned int i = 0 ; i < INNER_FUNC_COUNT; i++)
    {
        if (strcmp(builtin_func_table[i].name, sym->sym_name) == 0)
        {
            builtin_func_table[i].func(sym, argv, len, re);
            break;
        }
    }
    return LOX_OK;
}
