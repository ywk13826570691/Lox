#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lox_while.h"
#include "lox_if.h"

static int lox_while_index = 0;

static long lox_while_stack_index = -1;
static long lox_while_stack[1000] = { 0 };

int lox_while_get_cur_index(void)
{
    return lox_while_stack[lox_while_stack_index];
}

int lox_while_index_increase(void)
{
    int ret = lox_while_index;
    lox_while_index++;
    return ret;
}

int lox_while_index_push(long index)
{
    lox_while_stack[lox_while_stack_index + 1 ] = index;
    lox_while_stack_index++;
    return lox_while_stack_index;
}

int lox_while_index_pop(void)
{
    lox_while_stack_index--;
    return lox_while_stack_index;
}

inline char *lox_while_label(void)
{
    char *while_label = (char*)malloc(50);
    sprintf(while_label, "while_%d", lox_while_get_cur_index());
    return while_label;
}

inline char *lox_while_end_label(void)
{
    char *while_end = (char*)malloc(50);
    sprintf(while_end, "while_end_%d", lox_while_get_cur_index());
    return while_end;
}
