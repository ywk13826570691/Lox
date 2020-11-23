#include "lox_keywords.h"
#include <string.h>
#define KEYWORDS_CNT 18

static char lox_keywords[KEYWORDS_CNT][100] =
{
    "if",
    "else",
    "elseif",
    "while",
    "do",
    "repeat",
    "until",
    "function",
    "end",
    "return",
    "gloabl",
    "local",
    "nil",
    "and",
    "or",
    "not",
    "true",
    "false"
};

int lox_is_keyword(char *name)
{
    for(int i =0 ; i < KEYWORDS_CNT; i++)
    {
        if(strcmp(name, lox_keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
