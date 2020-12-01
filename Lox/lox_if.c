#include "lox_if.h"
#include <stdio.h>

static int lox_if_index = 0;

static int lox_if_stack_index = -1;
static int lox_if_stack[1000] = { 0 };

int lox_if_get_cur_index(void)
{
    return lox_if_stack[lox_if_stack_index];
}

int lox_if_index_increase(void)
{
    int ret = lox_if_index;
    lox_if_index++;
    return ret;
}

int lox_if_index_push(int index)
{
    lox_if_stack[lox_if_stack_index + 1 ] = index;
    lox_if_stack_index++;
    return lox_if_stack_index;
}

int lox_if_index_pop(void)
{
    lox_if_stack_index--;
    return lox_if_stack_index;
}

char *lox_if_label(void)
{
    char *if_label = (char*)malloc(50);
    sprintf(if_label, "if_%d", lox_if_get_cur_index());
    return if_label;
}

char *lox_else_label(void)
{
    char *else_label = (char*)malloc(50);
    sprintf(else_label, "else_%d", lox_if_get_cur_index());
    return else_label;
}

char *lox_elseif_label(void)
{
    char *elseif_label = (char*)malloc(50);
    sprintf(elseif_label, "elseif_%d", lox_if_get_cur_index());
    return elseif_label;
}

char *lox_if_end_label(void)
{
    char *if_end = (char*)malloc(50);
    sprintf(if_end, "if_end_%d", lox_if_get_cur_index());
    return if_end;
}

