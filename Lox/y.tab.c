/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "vkang.y" /* yacc.c:339  */

	#include<ctype.h>
	#include<stdio.h>
    #include "lox_function.h"
    #include "lox_opcode.h"
    #include "lox_register.h"
    #include "lox_array.h"
    #include "lox_if.h"
    extern int lox_linenumber;
    extern unsigned int lox_var_label_index;
    extern int lox_function_parsing;
    
    char lox_var_name[50];
    char lox_var_name2[50];

#line 82 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 18 "vkang.y" /* yacc.c:355  */

 long   vLong;
 float vFloat;
 char *vChar;

#line 192 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 209 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    34,    32,    43,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
      31,    45,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    79,    79,    82,    83,    84,    87,    87,    87,    90,
      91,    94,   108,   129,   132,   133,   136,   139,   139,   142,
     149,   142,   159,   160,   161,   199,   205,   206,   210,   211,
     211,   213,   217,   212,   219,   221,   231,   232,   234,   236,
     238,   241,   244,   246,   267,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   286,   287,   288,
     289,   290,   302,   303,   304,   305,   313,   316,   317,   321,
     322,   325,   333,   334,   337,   338,   341,   367,   395,   398
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "THEN", "ELSE", "ELSEIF", "WHILE",
  "DO", "REPEAT", "UNTIL", "FUNCTION", "END", "RETURN", "GLOBAL", "LOCAL",
  "NIL", "AND", "OR", "NOT", "EQ", "NE", "LE", "GE", "CONC", "LOX_TRUE",
  "LOX_FALSE", "STRING", "NUMBER", "NAME", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'/'", "'['", "']'", "LEFT_BRACKETS", "RIGHT_BRACKETS", "UMINUS",
  "'('", "')'", "','", "';'", "'='", "$accept", "program", "function_list",
  "function", "$@1", "$@2", "parlist", "parlist1", "block", "statlist",
  "stat", "sc", "stat1", "$@3", "$@4", "elsepart", "$@5", "$@6", "$@7",
  "ret", "retlist", "var_decalre", "var_create", "varlist1", "varlist",
  "PrepJump", "expr", "array", "arraylist", "arraylist1", "functioncall",
  "function_parlistlist", "function_parlistlist1", "functionvalue", "var",
  "varlist2", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      62,    60,    43,    45,    42,    47,    91,    93,   285,   286,
     287,    40,    41,    44,    59,    61
};
# endif

#define YYPACT_NINF -79

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define YYTABLE_NINF -77

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -79,     6,    54,   -79,   142,   142,   -79,    -6,   142,    33,
     -79,   -15,   -79,   -79,   -79,   -17,    -3,   -79,    -9,   -79,
     -79,   -79,   -79,   -79,    18,   142,    72,   -79,   -79,     1,
     112,    28,    57,   -79,   -15,   199,   -79,   -79,   -79,   -14,
     142,   142,   131,   -79,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   -79,   142,
     -15,    27,   -79,   142,   -79,   199,   -79,   157,   199,    29,
      30,   -79,   -79,   215,   215,   -16,   -16,   -16,   -16,    47,
     -16,   -16,   -30,   -30,   -79,   -79,   178,   -79,   199,   -79,
      43,   199,    38,    41,   -79,   -79,   142,   -79,   -79,   -79,
     -79,   -79,    45,    42,   -79,   142,   199,    20,    76,   -79,
      70,   199,   -79,   142,    97,   -79,   -79,   -79,   -79,    93,
     -79,   100,   -79,   -79,   -79,   -79,   -79,    20,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,    14,     0,    36,    17,
       5,    17,    16,    27,    26,     0,    39,    25,     0,    60,
      65,    64,    59,    58,    78,     0,     0,    61,    57,    77,
       0,     0,    13,     6,    17,    37,    18,    38,     4,     0,
       0,    72,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    44,     0,
      17,     0,    35,    67,    24,    42,    43,     0,    74,     0,
      73,    45,    14,    62,    63,    46,    49,    50,    51,    56,
      48,    47,    52,    53,    54,    55,     0,    14,    44,    15,
       9,    69,     0,    68,    41,    71,     0,    20,    79,    44,
      23,    11,     0,    10,    66,     0,    75,    28,     0,     7,
       0,    70,    29,     0,     0,    22,    14,    12,    14,     0,
      21,     0,    30,    31,     8,    14,    32,    28,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -63,   -79,
      86,    -4,   -79,   -79,   -79,    -8,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -78,    -5,   -79,   -79,   -79,
      -1,   -79,   -79,   -79,   -79,   -79
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    10,    61,   116,   102,   103,    31,    32,
      11,    37,    12,    72,   107,   114,   118,   125,   127,    13,
      34,    14,    15,    16,    64,    87,    26,    66,    92,    93,
      27,    69,    70,    18,    28,    29
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,    17,    19,    35,    55,    56,     3,    38,    50,    97,
     100,    20,    21,    22,    23,    24,    53,    54,    55,    56,
      42,   108,    63,    33,    99,   112,   113,    25,    39,    36,
      62,    17,    41,    40,    65,    67,    68,    57,    59,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,   121,    88,   122,    89,     4,    91,   -76,
       4,     5,   126,     6,     5,     7,     6,     8,    90,   -40,
       8,    95,   101,    96,   -76,   104,    43,    36,   -40,    53,
      54,    55,    56,     9,   105,   110,     9,   109,   115,    44,
      45,   106,    46,    47,    48,    49,    50,   123,   -34,   117,
     111,   -34,    51,    52,    53,    54,    55,    56,   119,   120,
      44,    45,   124,    46,    47,    48,    49,    50,    60,   128,
      58,     0,     0,    51,    52,    53,    54,    55,    56,    44,
      45,     0,    46,    47,    48,    49,    50,     0,     0,     0,
       0,     0,    51,    52,    53,    54,    55,    56,    44,    45,
       0,    46,    47,    48,    49,    50,     0,     0,    19,     0,
       0,    51,    52,    53,    54,    55,    56,    20,    21,    22,
      23,    24,     0,    71,    44,    45,     0,    46,    47,    48,
      49,    50,     0,    25,     0,     0,     0,    51,    52,    53,
      54,    55,    56,     0,    94,    44,    45,     0,    46,    47,
      48,    49,    50,     0,     0,     0,     0,     0,    51,    52,
      53,    54,    55,    56,     0,    98,    44,    45,     0,    46,
      47,    48,    49,    50,     0,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    56,    46,    47,    48,    49,    50,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
      56
};

static const yytype_int8 yycheck[] =
{
       5,     2,    16,     8,    34,    35,     0,    11,    24,    72,
      88,    25,    26,    27,    28,    29,    32,    33,    34,    35,
      25,    99,    36,    29,    87,     5,     6,    41,    45,    44,
      34,    32,    41,    36,    39,    40,    41,    36,    10,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,   116,    59,   118,    60,     3,    63,    41,
       3,     7,   125,     9,     7,    11,     9,    13,    41,    36,
      13,    42,    29,    43,    41,    37,     4,    44,    45,    32,
      33,    34,    35,    29,    43,    43,    29,    42,    12,    17,
      18,    96,    20,    21,    22,    23,    24,     4,    44,    29,
     105,    44,    30,    31,    32,    33,    34,    35,   113,    12,
      17,    18,    12,    20,    21,    22,    23,    24,    32,   127,
       8,    -1,    -1,    30,    31,    32,    33,    34,    35,    17,
      18,    -1,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    17,    18,
      -1,    20,    21,    22,    23,    24,    -1,    -1,    16,    -1,
      -1,    30,    31,    32,    33,    34,    35,    25,    26,    27,
      28,    29,    -1,    42,    17,    18,    -1,    20,    21,    22,
      23,    24,    -1,    41,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    37,    17,    18,    -1,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    37,    17,    18,    -1,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    48,     0,     3,     7,     9,    11,    13,    29,
      49,    56,    58,    65,    67,    68,    69,    76,    79,    16,
      25,    26,    27,    28,    29,    41,    72,    76,    80,    81,
      72,    54,    55,    29,    66,    72,    44,    57,    57,    45,
      36,    41,    72,     4,    17,    18,    20,    21,    22,    23,
      24,    30,    31,    32,    33,    34,    35,    36,     8,    10,
      56,    50,    57,    36,    70,    72,    73,    72,    72,    77,
      78,    42,    59,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    71,    72,    57,
      41,    72,    74,    75,    37,    42,    43,    54,    37,    54,
      71,    29,    52,    53,    37,    43,    72,    60,    71,    42,
      43,    72,     5,     6,    61,    12,    51,    29,    62,    72,
      12,    54,    54,     4,    12,    63,    54,    64,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    50,    51,    49,    52,
      52,    53,    53,    54,    55,    55,    56,    57,    57,    59,
      60,    58,    58,    58,    58,    58,    58,    58,    61,    62,
      61,    63,    64,    61,    65,    65,    66,    66,    67,    68,
      69,    69,    70,    70,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    73,    74,    74,    75,
      75,    76,    77,    77,    78,    78,    79,    80,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     3,     2,     0,     0,     9,     0,
       1,     1,     3,     1,     0,     3,     1,     0,     1,     0,
       0,     8,     7,     5,     3,     1,     1,     1,     0,     0,
       3,     0,     0,     7,     0,     3,     0,     1,     2,     1,
       1,     4,     1,     1,     0,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     3,     0,     1,     1,
       3,     4,     0,     1,     1,     3,     1,     1,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 87 "vkang.y" /* yacc.c:1646  */
    { lox_new_function((yyvsp[0].vChar)); lox_function_parsing = 1;}
#line 1404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 87 "vkang.y" /* yacc.c:1646  */
    { lox_opcode_function_param_end(); }
#line 1410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 87 "vkang.y" /* yacc.c:1646  */
    { lox_opcode_function_end();lox_cur_parsing_function_end(); lox_function_parsing = 0;}
#line 1416 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 94 "vkang.y" /* yacc.c:1646  */
    { 
					lox_func_add_arg_name((yyvsp[0].vChar)); 
					int ret = lox_add_local_symbol((yyvsp[0].vChar), lox_var_label_index);
					if (ret > 0)
					{
						lox_error("Defined function find an same var same with param???:%s\n", (yyvsp[0].vChar));
						exit(0);
					}
					else
					{
						lox_opcode_push_var((yyvsp[0].vChar), lox_var_label_index);
						lox_var_label_index++;
					}
				}
#line 1435 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 108 "vkang.y" /* yacc.c:1646  */
    {
      						lox_func_add_arg_name((yyvsp[0].vChar)); 
      
      						int ret = lox_add_local_symbol((yyvsp[0].vChar), lox_var_label_index);
							if (ret > 0)
							{
								lox_error("Define function find an same var same with param:%s\n", (yyvsp[0].vChar));
								exit(0);
							}
							else
							{
								lox_opcode_push_var((yyvsp[0].vChar), lox_var_label_index);
								lox_var_label_index++;
							}
      					}
#line 1455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 142 "vkang.y" /* yacc.c:1646  */
    {
            int ret = lox_if_index_increase();
            lox_if_index_push(ret);
            lox_info("-------------1---------:%d\n", ret);
            lox_opcode_cmp((yyvsp[-1].vLong));
            lox_opcode_jmpeq_label(lox_else_label());
            }
#line 1467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 149 "vkang.y" /* yacc.c:1646  */
    {
                        lox_info("-------------3---------:%d\n",lox_if_get_cur_index());
                        lox_opcode_jmp_label(lox_if_end_label());
                   }
#line 1476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 153 "vkang.y" /* yacc.c:1646  */
    {
            				lox_opcode_push_label(lox_else_label());
                            lox_opcode_push_label(lox_if_end_label());
                            lox_info("-------------2---------:%d\n", lox_if_get_cur_index());
                            lox_if_index_pop();
                         }
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 162 "vkang.y" /* yacc.c:1646  */
    {
				if (lox_get_is_array_element())
				{
					int ret = lox_find_local_symbol(lox_var_name);
					if (ret < 0)
					{
						lox_error("Using an invalid array:%s\n", lox_var_name);
						exit(0);
					}
					else
					{
						lox_info("Using array elememt:%s\n", lox_var_name);
					}
					extern long lox_array_ele_index;
					extern long lox_arrary_ele_labels[50];
					lox_opcode_set_array_object(ret, (yyvsp[0].vLong), lox_arrary_ele_labels, lox_array_ele_index);
					lox_array_element_end();
                    memset(lox_var_name, 0, 50);
				}
				else
				{
					int ret = lox_add_local_symbol(lox_var_name, lox_var_label_index);
                    long label = 0;
					if (ret > 0)
					{
		                lox_info("find same var:%s\n", lox_var_name);
						label = ret;
					}
					else
					{
						lox_opcode_push_var(lox_var_name, lox_var_label_index);
						label = lox_var_label_index;
						lox_var_label_index++;
					}
                    lox_opcode_move(label, (yyvsp[0].vLong));
				}
			}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 199 "vkang.y" /* yacc.c:1646  */
    {
                       struct lox_function_calling *call_f = lox_get_cur_calling_function();
                       lox_opcode_jmp((yyvsp[0].vLong), -100, (long)call_f);
                       lox_func_clear((long)call_f);
                       lox_pop_cur_calling_function();
    				}
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 211 "vkang.y" /* yacc.c:1646  */
    { lox_opcode_push_label(lox_else_label()); }
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 213 "vkang.y" /* yacc.c:1646  */
    { 
     	lox_opcode_push_label(lox_else_label()); 
     	lox_opcode_cmp((yyvsp[-1].vLong)); 
     	lox_opcode_jmpeq_label(lox_else_label());
     }
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 217 "vkang.y" /* yacc.c:1646  */
    { lox_opcode_jmp_label(lox_if_end_label()); }
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 222 "vkang.y" /* yacc.c:1646  */
    {
            if (!lox_function_parsing)
            {
                lox_info("return must in function\n");
                exit(0);
            }
        }
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 231 "vkang.y" /* yacc.c:1646  */
    { lox_opcode_return(0, 0);}
#line 1580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 232 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = (yyvsp[0].vLong); lox_opcode_return((yyvsp[0].vLong), 1);}
#line 1586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 238 "vkang.y" /* yacc.c:1646  */
    { 
					strcpy(lox_var_name, (yyvsp[0].vChar));
				 }
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 241 "vkang.y" /* yacc.c:1646  */
    { lox_set_is_array_element(); lox_array_element_index_push_label((yyvsp[-1].vLong)); }
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 244 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = (yyvsp[0].vLong); }
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 246 "vkang.y" /* yacc.c:1646  */
    {
                    extern long  lox_array_index;
                    extern long  lox_array_label[1000];
                    (yyval.vLong) = lox_var_label_index;
                    lox_opcode_push_array_var(lox_var_label_index, lox_array_label, lox_array_index);
                    lox_var_label_index++;
                    lox_array_parsing_end();
                }
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 270 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = (yyvsp[-1].vLong); }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 271 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_equal((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 272 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_lt((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 273 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_gt((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 274 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_nequal((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 275 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_let((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 276 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_get((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 277 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_add((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 278 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_sub((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index); lox_var_label_index++;}
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 279 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_mul((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index); lox_var_label_index++;}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 280 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_div((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index); lox_var_label_index++;}
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 286 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = (yyvsp[0].vLong); }
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 287 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index; lox_opcode_push_number_var((yyvsp[0].vFloat), lox_var_label_index);lox_var_label_index++; }
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 288 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index; lox_opcode_push_string_var((yyvsp[0].vChar), lox_var_label_index);lox_var_label_index++; }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 289 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index; lox_opcode_push_temp_var(lox_var_label_index);lox_var_label_index++;       }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 290 "vkang.y" /* yacc.c:1646  */
    {
                       struct lox_function_calling *call_f = lox_get_cur_calling_function();
                       struct lox_symbol *sym = (struct lox_symbol *)call_f->func;
     				   (yyval.vLong) = lox_var_label_index;
     				   lox_opcode_push_temp_var(lox_var_label_index);
                       lox_opcode_jmp((yyvsp[0].vLong), lox_var_label_index, (long)call_f);
                       lox_func_clear(call_f);
                       lox_pop_cur_calling_function();
                       lox_var_label_index++;
                       lox_info("---------------------function call end2:%s\n", sym->sym_name);
                     }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 302 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index; lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_and((yyvsp[-2].vLong), (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 303 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index; lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_or((yyvsp[-2].vLong),  (yyvsp[0].vLong), lox_var_label_index);lox_var_label_index++;}
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 304 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index; lox_opcode_push_bool_var(lox_var_label_index, 0);lox_var_label_index++;  }
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 305 "vkang.y" /* yacc.c:1646  */
    { (yyval.vLong) = lox_var_label_index; lox_opcode_push_bool_var(lox_var_label_index, 1);lox_var_label_index++;  }
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 321 "vkang.y" /* yacc.c:1646  */
    {   lox_array_push_label((yyvsp[0].vLong)); }
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 322 "vkang.y" /* yacc.c:1646  */
    { lox_array_push_label((yyvsp[0].vLong));}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 325 "vkang.y" /* yacc.c:1646  */
    { 
									(yyval.vLong) = (yyvsp[-3].vLong); 
                                    struct lox_function_calling *call_f = lox_get_cur_calling_function();
                                    struct lox_symbol *sym = (struct lox_symbol *)call_f->func;
                                    lox_func_check_args((long)call_f);
								}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 337 "vkang.y" /* yacc.c:1646  */
    { lox_func_push_arg_label((yyvsp[0].vLong)); }
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 338 "vkang.y" /* yacc.c:1646  */
    { lox_func_push_arg_label((yyvsp[0].vLong)); }
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 341 "vkang.y" /* yacc.c:1646  */
    {
            (yyval.vLong) = lox_find_function((yyvsp[0].vChar));
            lox_info("calling function:%s\n", (yyvsp[0].vChar));
            lox_push_cur_calling_function((yyval.vLong));
            if ((yyval.vLong) < 0)
            {
                lox_info("Call invalid function at line:%d %s\n", lox_linenumber, (yyvsp[0].vChar));
                exit(0);
            }
          }
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 368 "vkang.y" /* yacc.c:1646  */
    {
				int ret = lox_find_local_symbol(lox_var_name2);
				
				if (ret <= 0)
				{
					lox_error("Using an invalid var:%s %d\n", lox_var_name2, lox_cur_line_number());
					exit(0);
				}
				
				if (lox_get_is_array_element())
				{
					extern long lox_array_ele_index;
					extern long lox_arrary_ele_labels[50];
					(yyval.vLong) = lox_var_label_index;
					lox_opcode_push_temp_var(lox_var_label_index);
					lox_opcode_get_array_object(ret, lox_var_label_index, lox_arrary_ele_labels, lox_array_ele_index);
					lox_var_label_index++;
					lox_array_element_end();
                    memset(lox_var_name2, 0, 50);
				}
				else
				{
					(yyval.vLong) = ret;
				}
			}
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 395 "vkang.y" /* yacc.c:1646  */
    { 
					strcpy(lox_var_name2, (yyvsp[0].vChar));
				 }
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 398 "vkang.y" /* yacc.c:1646  */
    { lox_set_is_array_element(); lox_array_element_index_push_label((yyvsp[-1].vLong)); }
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1847 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 401 "vkang.y" /* yacc.c:1906  */


#if 0
int  main()
{
	extern FILE *yyin;
	yyin=fopen("b.txt","r");
	yyparse();
	return 0;
}
#endif

int yywrap (void)
{
 return 1;
}
int yyerror(char *s)
{
    printf("%s %d error!\n",s, yyget_lineno());
}
