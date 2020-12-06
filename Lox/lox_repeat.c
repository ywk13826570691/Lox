#include "lox_repeat.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

static int lox_repeat_index = 0;

static long lox_repeat_stack_index = -1;
static long lox_repeat_stack[1000] = { 0 };

int lox_repeat_get_cur_index(void)
{
    return lox_repeat_stack[lox_repeat_stack_index];
}

int lox_repeat_index_increase(void)
{
    int ret = lox_repeat_index;
    lox_repeat_index++;
    return ret;
}

int lox_repeat_index_push(long index)
{
    lox_repeat_stack[lox_repeat_stack_index + 1 ] = index;
    lox_repeat_stack_index++;
    return lox_repeat_stack_index;
}

int lox_repeat_index_pop(void)
{
    lox_repeat_stack_index--;
    return lox_repeat_stack_index;
}

inline char *lox_repeat_label(void)
{
    char *repeat_label = (char*)malloc(50);
    sprintf(repeat_label, "repeat_%d", lox_repeat_get_cur_index());
    return repeat_label;
}

inline char *lox_repeat_end_label(void)
{
    char *repeat_end = (char*)malloc(50);
    sprintf(repeat_end, "repeat_end_%d", lox_repeat_get_cur_index());
    return repeat_end;
}
