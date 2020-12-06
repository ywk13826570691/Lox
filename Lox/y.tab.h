/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    THEN = 259,
    ELSE = 260,
    ELSEIF = 261,
    WHILE = 262,
    DO = 263,
    REPEAT = 264,
    UNTIL = 265,
    FOREACH = 266,
    BREAK = 267,
    CONTINUE = 268,
    LOX_IN = 269,
    FUNCTION = 270,
    END = 271,
    RETURN = 272,
    GLOBAL = 273,
    LOCAL = 274,
    NIL = 275,
    AND = 276,
    OR = 277,
    NOT = 278,
    EQ = 279,
    NE = 280,
    LE = 281,
    GE = 282,
    CONC = 283,
    LOX_TRUE = 284,
    LOX_FALSE = 285,
    STRING = 286,
    NUMBER = 287,
    NAME = 288,
    LEFT_BRACKETS = 289,
    RIGHT_BRACKETS = 290,
    UMINUS = 291
  };
#endif
/* Tokens.  */
#define IF 258
#define THEN 259
#define ELSE 260
#define ELSEIF 261
#define WHILE 262
#define DO 263
#define REPEAT 264
#define UNTIL 265
#define FOREACH 266
#define BREAK 267
#define CONTINUE 268
#define LOX_IN 269
#define FUNCTION 270
#define END 271
#define RETURN 272
#define GLOBAL 273
#define LOCAL 274
#define NIL 275
#define AND 276
#define OR 277
#define NOT 278
#define EQ 279
#define NE 280
#define LE 281
#define GE 282
#define CONC 283
#define LOX_TRUE 284
#define LOX_FALSE 285
#define STRING 286
#define NUMBER 287
#define NAME 288
#define LEFT_BRACKETS 289
#define RIGHT_BRACKETS 290
#define UMINUS 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "vkang.y" /* yacc.c:1909  */

 long   vLong;
 float vFloat;
 char *vChar;

#line 132 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
