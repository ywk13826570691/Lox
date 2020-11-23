#include <stdio.h>
#include "lox.h"

int main()
{
    lox_main();
    extern FILE *yyin;
    yyin=fopen("b.txt","r");
    yyparse();
    lox_run();
    return 0;
}
