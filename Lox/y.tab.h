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
    LOX_IN = 267,
    FUNCTION = 268,
    END = 269,
    RETURN = 270,
    GLOBAL = 271,
    LOCAL = 272,
    NIL = 273,
    AND = 274,
    OR = 275,
    NOT = 276,
    EQ = 277,
    NE = 278,
    LE = 279,
    GE = 280,
    CONC = 281,
    LOX_TRUE = 282,
    LOX_FALSE = 283,
    STRING = 284,
    NUMBER = 285,
    NAME = 286,
    LEFT_BRACKETS = 287,
    RIGHT_BRACKETS = 288,
    UMINUS = 289
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
#define LOX_IN 267
#define FUNCTION 268
#define END 269
#define RETURN 270
#define GLOBAL 271
#define LOCAL 272
#define NIL 273
#define AND 274
#define OR 275
#define NOT 276
#define EQ 277
#define NE 278
#define LE 279
#define GE 280
#define CONC 281
#define LOX_TRUE 282
#define LOX_FALSE 283
#define STRING 284
#define NUMBER 285
#define NAME 286
#define LEFT_BRACKETS 287
#define RIGHT_BRACKETS 288
#define UMINUS 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "vkang.y" /* yacc.c:1909  */

 long   vLong;
 float vFloat;
 char *vChar;

#line 128 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
