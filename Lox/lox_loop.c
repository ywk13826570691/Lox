#include "lox_loop.h"
#include <stdlib.h>

int lox_loop_index = 0;

int lox_is_loop_parsing(void)
{
    return lox_loop_index;
}

int lox_push_loop_index(void)
{
    return lox_loop_index++;
}

int lox_pop_loop_index(void)
{
   return  lox_loop_index--;
}

static int lox_loop_end_label_index = -1;
static char *lox_loop_end_label[1000];
int lox_push_loop_end_label(char *label)
{
    lox_loop_end_label_index++;
    lox_loop_end_label[lox_loop_end_label_index] = label;
    return lox_loop_end_label_index;
}

int lox_pop_loop_end_label(void)
{
    lox_loop_end_label[lox_loop_end_label_index] = NULL;
    lox_loop_end_label_index--;
    return lox_loop_end_label_index;
}

char * lox_get_cur_loop_end_label(void)
{
    return  lox_loop_end_label[lox_loop_end_label_index];
}

static int lox_loop_start_label_index = -1;
static char *lox_loop_start_label[1000];
int lox_push_loop_start_label(char *label)
{
    lox_loop_start_label_index++;
    lox_loop_start_label[lox_loop_start_label_index] = label;
    return lox_loop_start_label_index;
}

int lox_pop_loop_start_label(void)
{
    return  lox_loop_start_label_index--;
}

char * lox_get_cur_loop_start_label(void)
{
    return lox_loop_start_label[lox_loop_start_label_index];
}
