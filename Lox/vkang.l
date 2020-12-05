%{
#include <stdlib.h>
#include <string.h>
extern int lox_linenumber;
#include "y.tab.h"
%}


%%
[ \t]*					;
\n						{ lox_linenumber ++; }
"@".*					;
"if"					return IF;
"then"					return THEN;
"else"					return ELSE;
"elseif"				return ELSEIF;
"while"					return WHILE;
"do"					return DO;
"repeat"				return REPEAT;
"until"					return UNTIL;
"foreach"               return FOREACH;
"in"                    return LOX_IN;
"function"				{
                            return FUNCTION;
						}
"end"					return END;
"return" 				return RETURN;
"global"				return GLOBAL;
"local"					return LOCAL;
"nil"					return NIL;
"and"					return AND;
"or"					return OR;
"not"					return NOT;
"=="					return EQ;
"~="					return NE;
"<="					return LE;
">="					return GE;
".."					return CONC;
"true"					return LOX_TRUE;
"false"					return LOX_FALSE;
\"[^\"]*\" 			| 
\'[^\']*\'			      {
                       yylval.vChar = (char*)malloc(strlen(yytext));
                       strcpy(yylval.vChar, yytext);
				       return STRING;
				      }
[0-9]+("."[0-9]*)?	|
([0-9]+)?"."[0-9]+	|
[0-9]+("."[0-9]*)?[dDeEgG][+-]?[0-9]+ |
([0-9]+)?"."[0-9]+[dDeEgG][+-]?[0-9]+ |
0[xX][0-9a-fA-F]+					{
                        yylval.vFloat = atof(yytext);
				        return NUMBER;
				       }
[a-zA-Z_][a-zA-Z0-9_]*  	       {
                    yylval.vChar = (char*)malloc(strlen(yytext));
                    strcpy(yylval.vChar, yytext);
					return NAME;
				       }
.					return  *yytext;

