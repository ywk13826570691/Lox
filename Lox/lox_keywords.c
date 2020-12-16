#include <string.h>
#include "lox_keywords.h"

#define KEYWORDS_CNT 30

static char lox_keywords[KEYWORDS_CNT][100] =
{
    "if",       "then",     "else",     "elseif",   "while",    "do",
    "repeat",   "until",    "foreach",  "break",    "continue", "in",
    "function", "end",      "return",   "gloabl",   "local",    "nil",
    "and",      "or",       "not",      "true",     "false",    "var",
    "class",    "vitual",   "private",  "protect",  "public",   "protected"
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
