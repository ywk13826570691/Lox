#include "lox_register.h"
#include "lox_def.h"
long lox_register[LOX_REGISTER_CNT] = { 0 };

int lox_register_init()
{
    SP = 0;
    FP = SP;
    return LOX_OK;
}
