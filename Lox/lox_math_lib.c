#include <math.h>
#include "lox_math_lib.h"
#include "lox_string.h"
#define TORAD(a)    ((a)*3.14159/180.0)
#define TODEGREE(a) ((a)*180.0/3.14159)

static void lox_math_abs(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("abs must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = obj->o_value.v_f;
        result.o_tag = LOX_NUMBER;
        if (obj->o_value.v_f < 0)
            result.o_value.v_f = obj->o_value.v_f * -1;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_sin(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("sin must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = sin(TORAD(obj->o_value.v_f));
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_cos(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("cos must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = cos(TORAD(obj->o_value.v_f));
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_tan(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("tan must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = tan(TORAD(obj->o_value.v_f));
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_asin(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("asin must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = TODEGREE(asin(obj->o_value.v_f));
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_acos(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("acos must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = TODEGREE(acos(obj->o_value.v_f));
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_atan(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("atan must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = TODEGREE(atan(obj->o_value.v_f));
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_ceil(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("ceil must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = ceil(obj->o_value.v_f);
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_floor(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("floor must number\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = floor(obj->o_value.v_f);
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static void lox_math_sqrt(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj = (struct lox_object *)argv[0];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj->o_tag != LOX_NUMBER)
    {
        lox_error("sqrt must number\n");
        return;
    }

    if (obj->o_value.v_f < 0)
    {
        lox_error("sqrt number must >= 0\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = sqrt(obj->o_value.v_f);
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}


static void lox_math_pow(struct lox_symbol * sym, long *argv, int len, long ret)
{
    struct lox_object *obj1 = (struct lox_object *)argv[0];
    struct lox_object *obj2 = (struct lox_object *)argv[1];
    struct lox_symbol *re = (struct lox_symbol *)ret;

    if (obj1->o_tag != LOX_NUMBER || obj2->o_tag != LOX_NUMBER)
    {
        lox_error("pow must number\n");
        return;
    }

    if (obj1->o_value.v_f == 0.0 && obj2->o_value.v_f <= 0.0)
    {
        lox_error("sqrt zero error\n");
        return;
    }

    if (obj1->o_value.v_f < 0.0 && !lox_is_int_number(obj2->o_value.v_f))
    {
        lox_error("sqrt zero error\n");
        return;
    }

    if (re && re->sym_obj)
    {
        struct lox_object result;
        result.o_value.v_f = pow(obj1->o_value.v_f, obj2->o_value.v_f);
        result.o_tag = LOX_NUMBER;
        lox_object_copy(re->sym_obj, &result);
    }
}

static struct lox_lib math_lib_table[] =
{
    {"math", "abs",     lox_math_abs ,  1, NULL},
    {"math", "sin",     lox_math_sin ,  1, NULL},
    {"math", "cos",     lox_math_cos,   1, NULL},
    {"math", "tan",     lox_math_tan,   1, NULL},
    {"math", "asin",    lox_math_asin,  1, NULL},
    {"math", "acos",    lox_math_acos,  1, NULL},
    {"math", "atan",    lox_math_atan,  1, NULL},
    {"math", "ceil",    lox_math_ceil,  1, NULL},
    {"math", "floor",   lox_math_floor, 1, NULL},
    {"math", "sqrt",    lox_math_sqrt,  1, NULL},
    {"math", "pow",     lox_math_pow,   2, NULL}
};

#define MATH_FUNC_COUNT (sizeof(math_lib_table)/sizeof(math_lib_table[0]))

int lox_math_lib_int(void)
{
    unsigned int i = 0;
    for (i = 0; i < MATH_FUNC_COUNT; i++)
    {
        lox_lib_register(&math_lib_table[i]);
    }
}

