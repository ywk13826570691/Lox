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
    FUNCTION = 266,
    END = 267,
    RETURN = 268,
    GLOBAL = 269,
    LOCAL = 270,
    NIL = 271,
    AND = 272,
    OR = 273,
    NOT = 274,
    EQ = 275,
    NE = 276,
    LE = 277,
    GE = 278,
    CONC = 279,
    LOX_TRUE = 280,
    LOX_FALSE = 281,
    STRING = 282,
    NUMBER = 283,
    NAME = 284,
    LEFT_BRACKETS = 285,
    RIGHT_BRACKETS = 286,
    UMINUS = 287
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
#define FUNCTION 266
#define END 267
#define RETURN 268
#define GLOBAL 269
#define LOCAL 270
#define NIL 271
#define AND 272
#define OR 273
#define NOT 274
#define EQ 275
#define NE 276
#define LE 277
#define GE 278
#define CONC 279
#define LOX_TRUE 280
#define LOX_FALSE 281
#define STRING 282
#define NUMBER 283
#define NAME 284
#define LEFT_BRACKETS 285
#define RIGHT_BRACKETS 286
#define UMINUS 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "vkang.y" /* yacc.c:1909  */

 long   vLong;
 float vFloat;
 char *vChar;

#line 124 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
