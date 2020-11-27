#include "lox_lib.h"
int lox_is_int_number(float f)
{
    float f1 = f;
    int f2 = f;
    float f3 = f - f2;
    if (f3 == 0)
    {
        return 1;
    }
    return 0;
}
