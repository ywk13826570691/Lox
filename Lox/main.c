#include <stdio.h>
#include "lox.h"

//#define LOX_SCAN_STRING
int main(int argc, char **argv)
{
    lox_vm_init();
#ifndef LOX_SCAN_STRING
    extern FILE *yyin;
    yyin = fopen("b.txt","r");
#else
    yy_scan_string("print(100000)");
#endif
    yyparse();
    lox_vm_run();
    return 0;
}
