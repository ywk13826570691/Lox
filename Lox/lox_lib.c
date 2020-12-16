#include "lox_lib.h"
#include "lox_object.h"

static struct lox_lib **lox_lib_table;
static long lox_lib_index = 0;
static long lox_lib_cnt = 0;

extern int lox_builtin_lib_init(void);

int lox_lib_init(void)
{
    lox_lib_cnt = 500;
    lox_lib_table = malloc(lox_lib_cnt * sizeof (struct lox_lib *));
    lox_lib_index = 0;

    lox_builtin_lib_init();
    return LOX_OK;
}

int lox_lib_register(struct lox_lib *lib)
{
    if (lox_lib_index == lox_lib_cnt)
    {
        lox_lib_cnt += 500;
        lox_lib_table = realloc(lox_lib_table, lox_lib_cnt * sizeof (struct lox_lib *));
    }
    lox_lib_table[lox_lib_index] = lib;
    lox_lib_index++;

    struct lox_symbol *sym = (struct lox_symbol*)malloc(sizeof (struct lox_symbol));
    memset(sym, 0, sizeof (struct lox_symbol));

    struct lox_object *obj = lox_object_new_func();
    sym->sym_obj = obj;

    struct lox_function *func;

    func = (struct lox_function*)malloc(sizeof (struct lox_function));
    sym->sym_obj->o_value.v_func = func;

    func->is_inner_function = 1;
    func->func_def_args_cnt = lib->func_argc;
    strcpy(sym->sym_name, lib->name);

    lib->s = sym;
    lox_register_func(sym);

    return lox_lib_index;
}


long lox_run_lib_func(long f, long *argv, int len, long ret)
{
    struct lox_symbol *sym = (struct lox_symbol*)f;
    struct lox_symbol *re = (struct lox_symbol *)ret;
    for (unsigned int i = 0 ; i < lox_lib_index; i++)
    {
        struct lox_symbol *s_func = lox_lib_table[i]->s;
        if (strcmp(s_func->sym_name, sym->sym_name) == 0)
        {
            lox_lib_table[i]->func(sym, argv, len, re);
            break;
        }
    }
    return LOX_OK;
}

int lox_is_lib_func(char *name)
{
    int ret = 0;
    for (unsigned int i = 0 ; i < lox_lib_index; i++)
    {
        struct lox_symbol *s_func = lox_lib_table[i]->s;
        if (strcmp(s_func->sym_name, name) == 0)
        {
            ret = 1;
            break;
        }
    }
    return ret;
}
