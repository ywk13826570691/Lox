#include "lox_foreach.h"

#include "lox_if.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

static int lox_foreach_index = 0;

static long lox_foreach_stack_index = -1;
static long lox_foreach_stack[1000] = { 0 };

int lox_foreach_get_cur_index(void)
{
    return lox_foreach_stack[lox_foreach_stack_index];
}

int lox_foreach_index_increase(void)
{
    int ret = lox_foreach_index;
    lox_foreach_index++;
    return ret;
}

int lox_foreach_index_push(long index)
{
    lox_foreach_stack[lox_foreach_stack_index + 1 ] = index;
    lox_foreach_stack_index++;
    return lox_foreach_stack_index;
}

int lox_foreach_index_pop(void)
{
    lox_foreach_stack_index--;
    return lox_foreach_stack_index;
}

inline char *lox_foreach_label(void)
{
    char *foreach_label = (char*)malloc(50);
    sprintf(foreach_label, "foreach_%d", lox_foreach_get_cur_index());
    return foreach_label;
}

inline char *lox_foreach_end_label(void)
{
    char *foreach_end = (char*)malloc(50);
    sprintf(foreach_end, "foreach_end_%d", lox_foreach_get_cur_index());
    return foreach_end;
}




