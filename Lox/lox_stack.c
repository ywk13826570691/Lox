#include "lox_stack.h"
#include "lox_register.h"
#include "lox_object.h"
#include "lox_array.h"
#include <stdlib.h>
#include <string.h>

int lox_sp_index = 0;
static int lox_stack_len = 0;
unsigned int lox_symbol_label_index = 10;

static long *lox_stack = NULL;
long lox_var_label_index = 10;


long * lox_get_stack(void)
{
    return lox_stack;
}

int lox_stack_init(void)
{
    lox_stack =  (long *)malloc(sizeof (long) * LOX_STACK_STEP);
    lox_sp_index = 0;
    lox_stack_len = LOX_STACK_STEP;
    SP = lox_sp_index;
    return LOX_OK;
}

int lox_stack_increase(void)
{
    int ret = 0;
    if (SP == lox_stack_len - 50)
    {
        lox_stack_len += LOX_STACK_STEP;
        lox_stack = realloc(lox_stack, sizeof (long) * lox_stack_len);
    }

    ret = SP;
    SP = SP+1;

    return ret;
}

int lox_stack_push(struct lox_symbol *s)
{
    lox_stack[SP] = (long)s;
    return lox_stack_increase();
}

long lox_stack_push_number_var(float f, long label)
{
    struct lox_symbol *s = (struct lox_symbol *)malloc(sizeof (struct lox_symbol));
    struct lox_object *obj = lox_object_new_number(f);
    memset(s, 0, sizeof (struct lox_symbol));
    s->sym_obj = obj;
    s->sym_label_value = label;
    return lox_stack_push(s);
}

long lox_stack_push_string_var(char *str, long label)
{
    struct lox_symbol *s = (struct lox_symbol *)malloc(sizeof (struct lox_symbol));
    struct lox_object *obj = lox_object_new_string(str);
    memset(s, 0, sizeof (struct lox_symbol));
    s->sym_obj = obj;
    s->sym_label_value = label;

    return lox_stack_push(s);
}

long lox_stack_push_var(char *name, long label)
{
    struct lox_symbol *s = (struct lox_symbol *)malloc(sizeof (struct lox_symbol));
    struct lox_object *obj = lox_object_new_temp();
    memset(s, 0, sizeof (struct lox_symbol));
    s->sym_obj = obj;
    strcpy(s->sym_name, name);
    s->sym_label_value = label;
    return lox_stack_push(s);
}

long lox_stack_push_temp_var(long label)
{
    struct lox_symbol *s = (struct lox_symbol *)malloc(sizeof (struct lox_symbol));
    struct lox_object *obj = lox_object_new_temp();
    memset(s, 0, sizeof (struct lox_symbol));
    s->sym_obj = obj;
    s->sym_label_value = label;
    return lox_stack_push(s);
}

long lox_stack_push_array_var(long label, long *labels, long label_cnt)
{
    struct lox_symbol *s = (struct lox_symbol *)malloc(sizeof (struct lox_symbol));
    struct lox_object *obj = lox_object_new_array();
    memset(s, 0, sizeof (struct lox_symbol));
    s->sym_obj = obj;
    s->sym_label_value = label;

    for(int i = 0; i < label_cnt; i++)
    {
        long label_index = labels[i];
        struct lox_symbol *sym = lox_find_symbol_by_label(label_index);
        if (!sym)
        {
            lox_error("stack push array can not find var\n");
            exit(0);
        }
        else
        {
            if (sym->sym_obj->o_tag == LOX_NUMBER)
                lox_info("stack push array can find var %f\n", sym->sym_obj->o_value.v_f);
            if (sym->sym_obj->o_tag == LOX_STRING)
                lox_info("stack push array can find var %s\n", sym->sym_obj->o_value.v_str);

            lox_array_insert_obj(obj, sym->sym_obj);
        }
    }
    return  lox_stack_push(s);
}

long lox_find_symbol_by_name(char *s_name)
{
    if (!s_name)
    {
        lox_error("can not find  invalid var:%s\n", s_name);
        return LOX_OK;
    }
    long i = 0;
    long *stack = lox_get_stack();
    long argc = stack[FP + 3];
    long step = LOX_STACK_TOP + argc;
    for (i = FP + step; i < SP; i++)
    {
        struct lox_symbol *s = (struct lox_symbol *)lox_stack[i];
        if (s)
        {
            if (strcmp(s->sym_name, s_name) == 0)
            {
                return lox_stack[i];
            }
        }
    }

    return (long)NULL;
}

long lox_find_symbol_by_label(unsigned long label)
{

    long i = 0;
    long *stack = lox_get_stack();
    long argc = stack[FP + 3];
    long step = LOX_STACK_TOP + argc;
    for (i = FP + step; i < SP; i++)
    {
        struct lox_symbol *s = (struct lox_symbol *)lox_stack[i];
        if (s && s->sym_label_value == label)
        {
            return (long)lox_stack[i];
        }
    }

    return LOX_OK;
}

long lox_stack_push_value(long v)
{
    lox_stack[SP] = v;
    return lox_stack_increase();
}

void lox_stack_print()
{
    for (int i = 0; i < SP; i++)
    {
        lox_info("-----------stack----------:%ld\n", lox_stack[i]);
    }
}

void lox_stack_clear_and_return(void)
{
    long sp = lox_stack[FP];
    long fp = lox_stack[FP + 1];
    long lr = lox_stack[FP + 2];
    long argc = lox_stack[FP + 3];

    lox_stack[FP] = 0;
    lox_stack[FP + 1] = 0;
    lox_stack[FP + 2] = 0;
    lox_stack[FP + 3] = 0;
    if (lox_stack[FP + 4] < 0)
    {
        lox_stack[FP + 4] = 0;
    }
#if 1
    for (int i = 0; i < argc; i++)
    {
        lox_stack[FP + LOX_STACK_TOP + i] = 0;
    }
#endif
#if 0
    for (int i = FP + LOX_STACK_TOP + argc ; i < SP ; i++ )
    {
        struct lox_symbol *s = lox_stack[i];
        if (s && s->sym_obj)
            free(s->sym_obj);
        if (s)
            free(s);
        lox_stack[i] = 0;
    }
#endif
    for (long i = SP; i >= FP + LOX_STACK_TOP + argc; i--)
    {
        struct lox_symbol *s = lox_stack[i];
        if (s && s->sym_obj)
            free(s->sym_obj);
        if (s)
            free(s);
        lox_stack[i] = 0;
    }

    SP = sp;
    PC = lr;
    FP = fp;
}
