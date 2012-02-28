/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for GLR parsing with Bison,
   Copyright (C) 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* This is the parser code for GLR (Generalized LR) parser. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <setjmp.h>

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse pp_parse
#define yylex   pp_lex
#define yyerror pp_error
#define yylval  pp_lval
#define yychar  pp_char
#define yydebug pp_debug
#define yynerrs pp_nerrs
#define yylloc pp_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     identifier = 258,
     identifier_lparen = 259,
     cv_qualifier = 14,
     TWO_HASH = 260,
     PLUSPLUS = 261,
     MINUSMINUS = 262,
     ARROW = 263,
     PPINCLUDE_KW = 264,
     PPIF_KW = 265,
     PPELSE_KW = 266,
     PPIFDEF_KW = 267,
     PPIFNDEF_KW = 268,
     PPELIF_KW = 269,
     PPENDIF_KW = 270,
     PPDEFINE_KW = 271,
     PPUNDEF_KW = 272,
     PPLINE_KW = 273,
     PPERROR_KW = 274,
     PPPRAGMA_KW = 275,
     TWO_COLON = 276,
     THREE_DOTS = 277,
     SIZEOF = 278,
     STRING_LITERAL = 279,
     LSTRING_LITERAL = 280,
     INTEGER_LITERAL = 281
   };
#endif
#define identifier 258
#define identifier_lparen 259
#define cv_qualifier 14
#define TWO_HASH 260
#define PLUSPLUS 261
#define MINUSMINUS 262
#define ARROW 263
#define PPINCLUDE_KW 264
#define PPIF_KW 265
#define PPELSE_KW 266
#define PPIFDEF_KW 267
#define PPIFNDEF_KW 268
#define PPELIF_KW 269
#define PPENDIF_KW 270
#define PPDEFINE_KW 271
#define PPUNDEF_KW 272
#define PPLINE_KW 273
#define PPERROR_KW 274
#define PPPRAGMA_KW 275
#define TWO_COLON 276
#define THREE_DOTS 277
#define SIZEOF 278
#define STRING_LITERAL 279
#define LSTRING_LITERAL 280
#define INTEGER_LITERAL 281




/* Copy the first part of user declarations.  */
#line 1 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"


int pp2_lex();

int pp_lex()
{
	int c = pp2_lex();
	while (c == ' ')
		c = pp2_lex();

	return c;
}

void pp_error (char const *s);
#define YYERROR_VERBOSE

#define yyfalse	0
#define yytrue		1

extern PP_Group* pp_file;

     

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 28 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
typedef union YYSTYPE {
int num;
char* id;
char* string_literal;
A_Exp* exp;
PP_Group *group;
PP_GroupPart *groupPart;
PP_Directive *directive;
PP_IfGroup* ifGroup;
PP_ElifGroups* elifGroups;
PP_Token token;
PP_TokenList* tokenList;
PP_IdentifierList* identifierList;
} YYSTYPE;
/* Line 188 of glr.c.  */
#line 169 "c:\\mmstudio\\extras\\ljavac\\pp_parse.tab.c"
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Default (constant) values used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template,
   here we set the default values of $$ and $@ to zeroed-out
   values.  Since the default value of these quantities is undefined,
   this behavior is technically correct. */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default;

/* Copy the second part of user declarations.  */


/* Line 216 of glr.c.  */
#line 198 "c:\\mmstudio\\extras\\ljavac\\pp_parse.tab.c"

#if ! defined (__cplusplus)
   typedef char bool;
#  define yytrue 1
#  define yyfalse 0
#endif

/*-----------------.
| GCC extensions.  |
`-----------------*/

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if !defined (__GNUC__) || __GNUC__ < 2 || \
(__GNUC__ == 2 && __GNUC_MINOR__ < 5) || __STRICT_ANSI__
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef ATTRIBUTE_UNUSED
# define ATTRIBUTE_UNUSED __attribute__ ((__unused__))
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   470

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  24
/* YYNRULES -- Number of rules. */
#define YYNRULES  65
/* YYNRULES -- Number of states. */
#define YYNSTATES  100
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule. */
#define YYMAXRHS 8

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX) 						\
  ((YYX <= 0) ? YYEOF :							\
   (unsigned)(YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,     2,     2,     2,     5,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    29,    45,     2,    30,     2,    42,    43,     2,
      33,    31,    40,    38,    32,    39,    49,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      47,    46,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,    44,    37,     2,     2,     2,     2,
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
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    13,    15,    17,
      19,    22,    23,    25,    28,    30,    32,    37,    44,    51,
      58,    60,    63,    64,    66,    73,    79,    80,    82,    87,
      93,   100,   109,   115,   119,   121,   125,   126,   128,   130,
     132,   134,   136,   138,   140,   142,   144,   146,   148,   150,
     152,   154,   156,   158,   160,   162,   164,   166,   168,   170,
     172,   174,   176,   178,   181,   182
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const signed char yyrhs[] =
{
      52,     0,    -1,    55,    -1,    27,    -1,    59,    -1,    59,
      54,    -1,    -1,    54,    -1,    28,    -1,    29,    -1,    57,
      29,    -1,    -1,    57,    -1,    74,    56,    -1,    60,    -1,
      68,    -1,    61,    63,    66,    67,    -1,    30,    58,    11,
      53,    56,    55,    -1,    30,    58,    13,     3,    56,    55,
      -1,    30,    58,    14,     3,    56,    55,    -1,    64,    -1,
      62,    64,    -1,    -1,    62,    -1,    30,    58,    15,    53,
      56,    55,    -1,    30,    58,    12,    56,    55,    -1,    -1,
      65,    -1,    30,    58,    16,    56,    -1,    30,    58,    10,
      73,    56,    -1,    30,    58,    17,     3,    72,    56,    -1,
      30,    58,    17,     4,    70,    31,    72,    56,    -1,    30,
      58,    18,     3,    56,    -1,    30,    58,    56,    -1,     3,
      -1,    69,    32,     3,    -1,    -1,    69,    -1,    33,    -1,
      31,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,     6,    -1,    27,    -1,
       3,    -1,    74,    -1,     4,    -1,    71,    -1,    73,    71,
      -1,    -1,    73,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    93,    93,    96,    99,   100,   103,   104,   107,   110,
     111,   113,   114,   117,   118,   119,   122,   125,   126,   127,
     130,   131,   134,   135,   138,   141,   144,   145,   148,   152,
     153,   154,   155,   161,   164,   165,   168,   169,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     197,   200,   201,   204,   210,   211
};
#endif

#if (YYDEBUG) || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "identifier", "identifier_lparen", 
  "cv_qualifier", "TWO_HASH", "PLUSPLUS", "MINUSMINUS", "ARROW", 
  "PPINCLUDE_KW", "PPIF_KW", "PPELSE_KW", "PPIFDEF_KW", "PPIFNDEF_KW", 
  "PPELIF_KW", "PPENDIF_KW", "PPDEFINE_KW", "PPUNDEF_KW", "PPLINE_KW", 
  "PPERROR_KW", "PPPRAGMA_KW", "TWO_COLON", "THREE_DOTS", "SIZEOF", 
  "STRING_LITERAL", "LSTRING_LITERAL", "INTEGER_LITERAL", "'\\n'", "' '", 
  "'#'", "')'", "','", "'('", "'['", "']'", "'{'", "'}'", "'+'", "'-'", 
  "'*'", "'/'", "'%'", "'&'", "'|'", "'!'", "'='", "'<'", "'>'", "'.'", 
  "';'", "$accept", "preprocessing_file", "pp_constant_expression", 
  "group", "group_opt", "new_line", "ws", "ws_opt", "group_part", 
  "if_section", "if_group", "elif_groups", "elif_groups_opt", 
  "elif_group", "else_group", "else_group_opt", "endif_line", 
  "control_line", "identifier_list", "identifier_list_opt", 
  "preprocessing_token", "replacement_list", "pp_tokens", "pp_tokens_opt", 0
};

#define yytname_size ((int) (sizeof (yytname) / sizeof (yytname[0])))
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    51,    52,    53,    54,    54,    55,    55,    56,    57,
      57,    58,    58,    59,    59,    59,    60,    61,    61,    61,
      62,    62,    63,    63,    64,    65,    66,    66,    67,    68,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      72,    73,    73,    73,    74,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     2,     0,     1,     1,     1,
       2,     0,     1,     2,     1,     1,     4,     6,     6,     6,
       1,     2,     0,     1,     6,     5,     0,     1,     4,     5,
       6,     8,     5,     3,     1,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     1
};

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none). */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM. */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
static const unsigned char yydefact[] =
{
       6,    59,    61,    57,    58,    11,    39,    38,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,     0,     7,     2,     4,    14,
       0,    15,    62,    65,     0,     9,    12,     0,     1,     5,
      11,     0,     0,    20,    63,     8,    13,    10,     0,     0,
       0,     0,     0,     0,    33,     0,    21,    11,    27,     0,
       0,     3,     0,     0,     0,    64,    36,     0,     0,     0,
      11,    16,    29,    64,    64,    64,     0,    60,    34,    37,
       0,    32,     0,     0,     0,    17,    18,    19,    30,     0,
      64,    64,    64,     0,    35,     0,    24,    25,    28,    31
};

/* YYPDEFGOTO[NTERM-NUM]. */
static const signed char yydefgoto[] =
{
      -1,    25,    62,    26,    27,    46,    36,    37,    28,    29,
      30,    41,    42,    43,    58,    59,    71,    31,    79,    80,
      32,    76,    33,    34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -63
static const short yypact[] =
{
      32,   -63,   -63,   -63,   -63,   -23,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,    13,   -63,   -63,    80,   -63,
     -13,   -63,   -63,   420,    -9,   -63,    -8,    -6,   -63,   -63,
     -23,   -10,     4,   -63,   -63,   -63,   -63,   -63,   368,    -3,
      34,    37,     6,    38,   -63,    27,   -63,   -23,   -63,    14,
     394,   -63,    -9,    -9,    -9,   368,    40,    -9,    -3,    35,
     -23,   -63,   -63,   128,   176,   224,    -9,   -63,   -63,    16,
      18,   -63,    -9,    -9,    36,   -63,   -63,   -63,   -63,    47,
     368,   272,   320,    -9,   -63,    -9,   -63,   -63,   -63,   -63
};

/* YYPGOTO[NTERM-NUM].  */
static const signed char yypgoto[] =
{
     -63,   -63,   -17,    25,   -59,   -37,   -63,   -39,   -63,   -63,
     -63,   -63,   -63,    20,   -63,   -63,   -63,   -63,   -63,   -63,
     -31,   -36,     7,   -62
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -65
static const signed char yytable[] =
{
      54,    55,    44,    77,    48,    49,    35,    50,    51,    65,
      66,    52,    53,    38,    85,    86,    87,    40,    69,    45,
      40,    47,    45,    72,    61,    73,    74,    75,    77,    44,
      81,    84,    96,    97,    57,     1,     2,    63,     3,    88,
      64,    67,    68,    78,    70,    91,    92,    83,    89,    90,
      94,    82,    93,    39,    95,    60,    98,     0,    99,     4,
     -64,    56,     5,     6,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     1,     2,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,   -64,     0,
       5,     6,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     1,     2,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     4,     0,     0,     5,     6,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     1,
       2,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     0,     0,     5,     6,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     1,     2,     0,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     4,     0,     0,     5,     6,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     1,     2,     0,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       0,     0,     5,     6,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     1,     2,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       5,     6,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     1,     2,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     4,     0,     1,     0,     6,
       3,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
       0,     4,    45,     1,     0,     6,     3,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,     0,     4,     0,     0,
       0,     6,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,     4,     0,    22,     0,    23,     0,    26,     0,     6,
       0,     6,     0,     6,     0,     6,     0,     6,     0
};

static const signed char yycheck[] =
{
      37,    40,    33,    65,    10,    11,    29,    13,    14,     3,
       4,    17,    18,     0,    73,    74,    75,    30,    57,    28,
      30,    29,    28,    60,    27,    62,    63,    64,    90,    60,
      67,    70,    91,    92,    30,     3,     4,     3,     6,    76,
       3,     3,    15,     3,    30,    82,    83,    12,    32,    31,
       3,    68,    16,    28,    90,    48,    93,    -1,    95,    27,
      28,    41,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    30,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     3,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,     3,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    -1,     3,    -1,    31,
       6,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    27,    28,     3,    -1,    31,     6,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    27,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     6,    27,    30,    31,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    52,    54,    55,    59,    60,
      61,    68,    71,    73,    74,    29,    57,    58,     0,    54,
      30,    62,    63,    64,    71,    28,    56,    29,    10,    11,
      13,    14,    17,    18,    56,    58,    64,    30,    65,    66,
      73,    27,    53,     3,     3,     3,     4,     3,    15,    58,
      30,    67,    56,    56,    56,    56,    72,    74,     3,    69,
      70,    56,    53,    12,    58,    55,    55,    55,    56,    32,
      31,    56,    56,    16,     3,    72,    55,    55,    56,    56
};


/* Prevent warning if -Wmissing-prototypes.  */
int yyparse (void);

/* Error token number */
#define YYTERROR 1

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#define YYRHSLOC(yyRhs,YYK) (yyRhs[YYK].yystate.yyloc)

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(yyCurrent, yyRhs, YYN)			\
  yyCurrent.first_line   = YYRHSLOC(yyRhs,1).first_line;	\
  yyCurrent.first_column = YYRHSLOC(yyRhs,1).first_column;	\
  yyCurrent.last_line    = YYRHSLOC(yyRhs,YYN).last_line;	\
  yyCurrent.last_column  = YYRHSLOC(yyRhs,YYN).last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */
#define YYLEX yylex ()

YYSTYPE yylval;

YYLTYPE yylloc;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)							     \
   do { YYRESULTTAG yyflag = YYE; if (yyflag != yyok) return yyflag; } 	     \
   while (0)

#if YYDEBUG

#if ! defined (YYFPRINTF)
#  define YYFPRINTF fprintf
#endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}


# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

#else /* !YYDEBUG */

  /* Avoid empty `if' bodies.  */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call expandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data. */
#define YYHEADROOM 2

#if (! defined (YYSTACKEXPANDABLE) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))
#define YYSTACKEXPANDABLE 1
#else
#define YYSTACKEXPANDABLE 0
#endif

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef short yySymbol;

/** Item references, as in LALR(1) machine */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;
typedef struct yyGLRStateSet yyGLRStateSet;

struct yyGLRState {
  bool yyisState;
  bool yyresolved;
  yyStateNum yylrState;
  yyGLRState* yypred;
  size_t yyposn;
  union {
    yySemanticOption* yyfirstVal;
    YYSTYPE yysval;
  } yysemantics;
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  bool yyisState;
  yyRuleNum yyrule;
  yyGLRState* yystate;
  yySemanticOption* yynext;
};

union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrflag;
  int yyerrState;

  yySymbol* yytokenp;
  jmp_buf yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  int yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

static void yyinitGLRStack (yyGLRStack* yystack, size_t yysize);
static void yyexpandGLRStack (yyGLRStack* yystack);
static void yyfreeGLRStack (yyGLRStack* yystack);

static void
yyFail (yyGLRStack* yystack, const char* yyformat, ...)
{
  yystack->yyerrflag = 1;
  if (yyformat != NULL)
    {
      char yymsg[256];
      va_list yyap;
      va_start (yyap, yyformat);
      vsprintf (yymsg, yyformat, yyap);
      yyerror (yymsg);
    }
  longjmp (yystack->yyexception_buffer, 1);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  Valid until next call to
 *  tokenName. */
static inline const char*
yytokenName (yySymbol yytoken)
{
  return yytname[yytoken];
}
#endif

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$). Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT. */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
	      YYSTYPE* yyvalp, YYLTYPE* yylocp, yyGLRStack* yystack
              )
{
  /* Avoid `unused' warnings in there are no $n. */
  (void) yystack;

  if (yyrhslen == 0)
    {
      *yyvalp = yyval_default;
      *yylocp = yyloc_default;
    }
  else
    {
      *yyvalp = yyvsp[1-yyrhslen].yystate.yysemantics.yysval;
      *yylocp = yyvsp[1-yyrhslen].yystate.yyloc;
    }
# undef yyerrok
# define yyerrok (yystack->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerr
# undef YYRECOVERING
# define YYRECOVERING (yystack->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = *(yystack->yytokenp) = YYEMPTY)
# undef YYBACKUP
# define YYBACKUP(Token, Value)						     \
  do {									     \
    yyerror ("syntax error: cannot back up");		     \
    YYERROR;								     \
  } while (0)


   switch (yyn)
     {
         case 2:
#line 93 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { pp_file = yyvsp[0].yystate.yysemantics.yysval.group ;}
    break;

  case 3:
#line 96 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).exp = A_Int32Exp(yyvsp[0].yystate.yysemantics.yysval.num) ;}
    break;

  case 4:
#line 99 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).group = new PP_Group(yyvsp[0].yystate.yysemantics.yysval.groupPart, NULL) ;}
    break;

  case 5:
#line 100 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).group = new PP_Group(yyvsp[-1].yystate.yysemantics.yysval.groupPart, yyvsp[0].yystate.yysemantics.yysval.group) ;}
    break;

  case 6:
#line 103 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).group = NULL ;}
    break;

  case 13:
#line 117 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).groupPart = PP_Tokens(yyvsp[-1].yystate.yysemantics.yysval.tokenList) ;}
    break;

  case 14:
#line 118 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).groupPart = yyvsp[0].yystate.yysemantics.yysval.groupPart ;}
    break;

  case 15:
#line 119 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).groupPart = yyvsp[0].yystate.yysemantics.yysval.groupPart ;}
    break;

  case 16:
#line 122 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).groupPart = PP_IfSection(yyvsp[-3].yystate.yysemantics.yysval.ifGroup, yyvsp[-2].yystate.yysemantics.yysval.elifGroups, yyvsp[-1].yystate.yysemantics.yysval.group) ;}
    break;

  case 17:
#line 125 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).ifGroup = PP_If_Group(yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.group) ;}
    break;

  case 18:
#line 126 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).ifGroup = PP_IfDefGroup(yyvsp[-2].yystate.yysemantics.yysval.id, yyvsp[0].yystate.yysemantics.yysval.group) ;}
    break;

  case 19:
#line 127 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).ifGroup = PP_IfNDefGroup(yyvsp[-2].yystate.yysemantics.yysval.id, yyvsp[0].yystate.yysemantics.yysval.group) ;}
    break;

  case 20:
#line 130 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).elifGroups = new PP_ElifGroups(yyvsp[0].yystate.yysemantics.yysval.directive, NULL) ;}
    break;

  case 21:
#line 131 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).elifGroups = new PP_ElifGroups(yyvsp[0].yystate.yysemantics.yysval.directive, yyvsp[-1].yystate.yysemantics.yysval.elifGroups) ;}
    break;

  case 22:
#line 134 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).elifGroups = NULL ;}
    break;

  case 24:
#line 138 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).directive = PP_ElifGroup(yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.group) ;}
    break;

  case 25:
#line 141 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).group = yyvsp[0].yystate.yysemantics.yysval.group ;}
    break;

  case 26:
#line 144 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).group = NULL ;}
    break;

  case 29:
#line 152 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { ;}
    break;

  case 30:
#line 153 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).groupPart = PP_Define(yyvsp[-2].yystate.yysemantics.yysval.id, false, NULL, yyvsp[-1].yystate.yysemantics.yysval.tokenList) ;}
    break;

  case 31:
#line 154 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).groupPart = PP_Define(yyvsp[-4].yystate.yysemantics.yysval.id, true, yyvsp[-3].yystate.yysemantics.yysval.identifierList, yyvsp[-1].yystate.yysemantics.yysval.tokenList) ;}
    break;

  case 32:
#line 155 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).groupPart = PP_Undef(yyvsp[-1].yystate.yysemantics.yysval.id) ;}
    break;

  case 33:
#line 161 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    {;}
    break;

  case 34:
#line 164 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).identifierList = new PP_IdentifierList(yyvsp[0].yystate.yysemantics.yysval.id, NULL) ;}
    break;

  case 35:
#line 165 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).identifierList = new PP_IdentifierList(yyvsp[0].yystate.yysemantics.yysval.id, yyvsp[-2].yystate.yysemantics.yysval.identifierList) ;}
    break;

  case 36:
#line 168 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).identifierList = NULL ;}
    break;

  case 38:
#line 173 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '(') ;}
    break;

  case 39:
#line 174 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, ')') ;}
    break;

  case 40:
#line 175 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '[') ;}
    break;

  case 41:
#line 176 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, ']') ;}
    break;

  case 42:
#line 177 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '{') ;}
    break;

  case 43:
#line 178 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '}') ;}
    break;

  case 44:
#line 179 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '+') ;}
    break;

  case 45:
#line 180 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '-') ;}
    break;

  case 46:
#line 181 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '*') ;}
    break;

  case 47:
#line 182 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '/') ;}
    break;

  case 48:
#line 183 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '%') ;}
    break;

  case 49:
#line 184 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '&') ;}
    break;

  case 50:
#line 185 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '|') ;}
    break;

  case 51:
#line 186 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '!') ;}
    break;

  case 52:
#line 187 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '=') ;}
    break;

  case 53:
#line 188 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '<') ;}
    break;

  case 54:
#line 189 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '>') ;}
    break;

  case 55:
#line 190 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '.') ;}
    break;

  case 56:
#line 191 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, ';') ;}
    break;

  case 57:
#line 192 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Char(yyvsp[0].yystate.yyloc, '##') ;}
    break;

  case 58:
#line 193 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Int32(yyvsp[0].yystate.yyloc, yyvsp[0].yystate.yysemantics.yysval.num) ;}
    break;

  case 59:
#line 194 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).token = PP_Identifier(yyvsp[0].yystate.yyloc, yyvsp[0].yystate.yysemantics.yysval.id) ;}
    break;

  case 61:
#line 200 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).tokenList = new PP_TokenList(PP_Identifier(yyvsp[0].yystate.yyloc, yyvsp[0].yystate.yysemantics.yysval.id), new PP_TokenList(PP_Char(yyvsp[0].yystate.yyloc, '('), NULL)) ;}
    break;

  case 62:
#line 201 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    {
			(*yyvalp).tokenList = new PP_TokenList(yyvsp[0].yystate.yysemantics.yysval.token, NULL)
			 ;}
    break;

  case 63:
#line 204 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    {
			
			(*yyvalp).tokenList = new PP_TokenList(yyvsp[0].yystate.yysemantics.yysval.token, yyvsp[-1].yystate.yysemantics.yysval.tokenList);
			 ;}
    break;

  case 64:
#line 210 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"
    { (*yyvalp).tokenList = NULL ;}
    break;


     }

   return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
/* Line 671 of glr.c.  */
#line 1201 "c:\\mmstudio\\extras\\ljavac\\pp_parse.tab.c"
}


static YYSTYPE
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYSTYPE yyval = *yy0;
  /* `Use' the arguments.  */
  (void) yy0;
  (void) yy1;

  switch (yyn)
    {
      
    }
  return yyval;
}

			      /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {

      default:
        break;
    }
}

/** Number of symbols composing the right hand side of rule #RULE. */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

/** Left-hand-side symbol for rule #RULE. */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yyis_pact_ninf(yystate) \
  ((yystate) == YYPACT_NINF)

/** True iff LR state STATE has only a default reduction (regardless
 *  of token). */
static inline bool
yyisDefaultedState (yyStateNum yystate)
{
  return yyis_pact_ninf (yypact[yystate]);
}

/** The default reduction for STATE, assuming it has one. */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yyis_table_ninf(yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *CONFLICTS to a pointer into yyconfl to 0-terminated list of
 *  conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
	        int* yyaction, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yyis_table_ninf (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yylhs)
{
  int yyr;
  yyr = yypgoto[yylhs - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yylhs - YYNTOKENS];
}

static inline bool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline bool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

				/* GLRStates */

static void
yyaddDeferredAction (yyGLRStack* yystack, yyGLRState* yystate,
		     yyGLRState* rhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewItem;
  yynewItem = &yystack->yynextFree->yyoption;
  yystack->yyspaceLeft -= 1;
  yystack->yynextFree += 1;
  yynewItem->yyisState = yyfalse;
  yynewItem->yystate = rhs;
  yynewItem->yyrule = yyrule;
  yynewItem->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewItem;
  if (yystack->yyspaceLeft < YYHEADROOM)
    yyexpandGLRStack (yystack);
}

				/* GLRStacks */

/** Initialize SET to a singleton set containing an empty stack. */
static void
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) malloc (16 * sizeof (yyset->yystates[0]));
  yyset->yystates[0] = NULL;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  free (yyset->yystates);
}

/** Initialize STACK to a single empty stack, with total maximum
 *  capacity for all stacks of SIZE. */
static void
yyinitGLRStack (yyGLRStack* yystack, size_t yysize)
{
  yystack->yyerrflag = 0;
  yystack->yyerrState = 0;
  yynerrs = 0;
  yystack->yyspaceLeft = yysize;
  yystack->yynextFree = yystack->yyitems =
    (yyGLRStackItem*) malloc (yysize * sizeof (yystack->yynextFree[0]));
  yystack->yysplitPoint = NULL;
  yystack->yylastDeleted = NULL;
  yyinitStateSet (&yystack->yytops);
}

#define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If STACK is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation. */
static void
yyexpandGLRStack (yyGLRStack* yystack)
{
#if YYSTACKEXPANDABLE
  yyGLRStack yynewStack;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yysize, yynewSize;
  size_t yyn;
  yysize = yystack->yynextFree - yystack->yyitems;
  if (YYMAXDEPTH <= yysize)
    yyFail (yystack, "parser stack overflow");
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yyinitGLRStack (&yynewStack, yynewSize);
  for (yyp0 = yystack->yyitems, yyp1 = yynewStack.yyitems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(bool*) yyp0)
	{
	  yyGLRState* yys0 = &yyp0->yystate;
	  yyGLRState* yys1 = &yyp1->yystate;
	  if (yys0->yypred != NULL)
	    yys1->yypred =
	      YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
	  if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != NULL)
	    yys1->yysemantics.yyfirstVal =
	      YYRELOC(yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
	}
      else
	{
	  yySemanticOption* yyv0 = &yyp0->yyoption;
	  yySemanticOption* yyv1 = &yyp1->yyoption;
	  if (yyv0->yystate != NULL)
	    yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
	  if (yyv0->yynext != NULL)
	    yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
	}
    }
  if (yystack->yysplitPoint != NULL)
    yystack->yysplitPoint = YYRELOC (yystack->yyitems, yynewStack.yyitems,
				 yystack->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystack->yytops.yysize; yyn += 1)
    if (yystack->yytops.yystates[yyn] != NULL)
      yystack->yytops.yystates[yyn] =
	YYRELOC (yystack->yyitems, yynewStack.yyitems,
		 yystack->yytops.yystates[yyn], yystate);
  free (yystack->yyitems);
  yystack->yyitems = yynewStack.yyitems;
  yystack->yynextFree = yynewStack.yynextFree + yysize;
  yystack->yyspaceLeft = yynewStack.yyspaceLeft - yysize;

#else

  yyFail (yystack, "parser stack overflow");
#endif
}

static void
yyfreeGLRStack (yyGLRStack* yystack)
{
  free (yystack->yyitems);
  yyfreeStateSet (&yystack->yytops);
}

/** Assuming that S is a GLRState somewhere on STACK, update the
 *  splitpoint of STACK, if needed, so that it is at least as deep as
 *  S. */
static inline void
yyupdateSplit (yyGLRStack* yystack, yyGLRState* yys)
{
  if (yystack->yysplitPoint != NULL && yystack->yysplitPoint > yys)
    yystack->yysplitPoint = yys;
}

/** Invalidate stack #K in STACK. */
static inline void
yymarkStackDeleted (yyGLRStack* yystack, int yyk)
{
  if (yystack->yytops.yystates[yyk] != NULL)
    yystack->yylastDeleted = yystack->yytops.yystates[yyk];
  yystack->yytops.yystates[yyk] = NULL;
}

/** Undelete the last stack that was marked as deleted.  Can only be
    done once after a deletion, and only when all other stacks have
    been deleted. */
static void
yyundeleteLastStack (yyGLRStack* yystack)
{
  if (yystack->yylastDeleted == NULL || yystack->yytops.yysize != 0)
    return;
  yystack->yytops.yystates[0] = yystack->yylastDeleted;
  yystack->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystack->yylastDeleted = NULL;
}

static inline void
yyremoveDeletes (yyGLRStack* yystack)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystack->yytops.yysize)
    {
      if (yystack->yytops.yystates[yyi] == NULL)
	{
	  if (yyi == yyj)
	    {
	      YYDPRINTF ((stderr, "Removing dead stacks.\n"));
	    }
	  yystack->yytops.yysize -= 1;
	}
      else
	{
	  yystack->yytops.yystates[yyj] = yystack->yytops.yystates[yyi];
	  if (yyj != yyi)
	    {
	      YYDPRINTF ((stderr, "Rename stack %d -> %d.\n", yyi, yyj));
	    }
	  yyj += 1;
	}
      yyi += 1;
    }
}

/** Shift to a new state on stack #K of STACK, corresponding to LR state
 * LRSTATE, at input position POSN, with (resolved) semantic value SVAL. */
static inline void
yyglrShift (yyGLRStack* yystack, int yyk, yyStateNum yylrState, size_t yyposn,
	    YYSTYPE yysval, YYLTYPE* yylocp)
{
  yyGLRStackItem* yynewItem;

  yynewItem = yystack->yynextFree;
  yystack->yynextFree += 1;
  yystack->yyspaceLeft -= 1;
  yynewItem->yystate.yyisState = yytrue;
  yynewItem->yystate.yylrState = yylrState;
  yynewItem->yystate.yyposn = yyposn;
  yynewItem->yystate.yyresolved = yytrue;
  yynewItem->yystate.yypred = yystack->yytops.yystates[yyk];
  yystack->yytops.yystates[yyk] = &yynewItem->yystate;
  yynewItem->yystate.yysemantics.yysval = yysval;
  yynewItem->yystate.yyloc = *yylocp;
  if (yystack->yyspaceLeft < YYHEADROOM)
    yyexpandGLRStack (yystack);
}

/** Shift to a new state on stack #K of STACK, to a new state
 *  corresponding to LR state LRSTATE, at input position POSN, with
 * the (unresolved) semantic value of RHS under the action for RULE. */
static inline void
yyglrShiftDefer (yyGLRStack* yystack, int yyk, yyStateNum yylrState,
		 size_t yyposn, yyGLRState* rhs, yyRuleNum yyrule)
{
  yyGLRStackItem* yynewItem;

  yynewItem = yystack->yynextFree;
  yynewItem->yystate.yyisState = yytrue;
  yynewItem->yystate.yylrState = yylrState;
  yynewItem->yystate.yyposn = yyposn;
  yynewItem->yystate.yyresolved = yyfalse;
  yynewItem->yystate.yypred = yystack->yytops.yystates[yyk];
  yynewItem->yystate.yysemantics.yyfirstVal = NULL;
  yystack->yytops.yystates[yyk] = &yynewItem->yystate;
  yystack->yynextFree += 1;
  yystack->yyspaceLeft -= 1;
  yyaddDeferredAction (yystack, &yynewItem->yystate, rhs, yyrule);
}

/** Pop the symbols consumed by reduction #RULE from the top of stack
 *  #K of STACK, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved. Set *VALP to the resulting value,
 *  and *LOCP to the computed location (if any).  Return value is as
 *  for userAction. */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystack, int yyk, yyRuleNum yyrule,
 	    YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystack->yysplitPoint == NULL)
    {
      /* Standard special case: single stack. */
      yyGLRStackItem* rhs = (yyGLRStackItem*) yystack->yytops.yystates[yyk];
      if (yyk != 0)
	abort ();
      yystack->yynextFree -= yynrhs;
      yystack->yyspaceLeft += yynrhs;
      yystack->yytops.yystates[0] = & yystack->yynextFree[-1].yystate;
      if (yynrhs == 0)
	{
	  *yyvalp = yyval_default;
	  *yylocp = yyloc_default;
	}
      else
	{
	  *yyvalp = rhs[1-yynrhs].yystate.yysemantics.yysval;
	  *yylocp = rhs[1-yynrhs].yystate.yyloc;
	}
      return yyuserAction (yyrule, yynrhs, rhs,
			   yyvalp, yylocp, yystack);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS];
      for (yyi = yynrhs-1, yys = yystack->yytops.yystates[yyk]; 0 <= yyi;
	   yyi -= 1, yys = yys->yypred)
	{
	  if (! yys->yypred)
	    abort ();
	  yyrhsVals[yyi].yystate.yyresolved = yytrue;
	  yyrhsVals[yyi].yystate.yysemantics.yysval = yys->yysemantics.yysval;
	  yyrhsVals[yyi].yystate.yyloc = yys->yyloc;
	}
      yyupdateSplit (yystack, yys);
      yystack->yytops.yystates[yyk] = yys;
      if (yynrhs == 0)
	{
	  *yyvalp = yyval_default;
	  *yylocp = yyloc_default;
	}
      else
	{
	  *yyvalp = yyrhsVals[0].yystate.yysemantics.yysval;
	  *yylocp = yyrhsVals[0].yystate.yyloc;
	}
      return yyuserAction (yyrule, yynrhs, yyrhsVals + (yynrhs-1),
			   yyvalp, yylocp, yystack);
    }
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(K, Rule)
#else
# define YY_REDUCE_PRINT(K, Rule)	\
do {					\
  if (yydebug)				\
    yy_reduce_print (K, Rule);		\
} while (0)

/*----------------------------------------------------------.
| Report that the RULE is going to be reduced on stack #K.  |
`----------------------------------------------------------*/

static inline void
yy_reduce_print (size_t yyk, yyRuleNum yyrule)
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack %d by rule %d (line %u), ",
	     yyk, yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytokenName (yyrhs[yyi]));
  YYFPRINTF (stderr, "-> %s\n", yytokenName (yyr1[yyrule]));
}
#endif

/** Pop items off stack #K of STACK according to grammar rule RULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with RULE and store its value with the
 *  newly pushed state, if FORCEEVAL or if STACK is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #K from
 *  the STACK. In this case, the (necessarily deferred) semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystack, size_t yyk, yyRuleNum yyrule,
             bool yyforceEval)
{
  size_t yyposn = yystack->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystack->yysplitPoint == NULL)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YY_REDUCE_PRINT (yyk, yyrule);
      YYCHK (yydoAction (yystack, yyk, yyrule, &yysval, &yyloc));
      yyglrShift (yystack, yyk,
		  yyLRgotoState (yystack->yytops.yystates[yyk]->yylrState,
				 yylhsNonterm (yyrule)),
		  yyposn, yysval, &yyloc);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystack->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystack->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
	   0 < yyn; yyn -= 1)
	{
	  yys = yys->yypred;
	  if (! yys)
	    abort ();
	}
      yyupdateSplit (yystack, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
		  "Reduced stack %d by rule #%d; action deferred. "
		  "Now in state %d.\n",
		  yyk, yyrule-1, yynewLRState));
      for (yyi = 0; yyi < yystack->yytops.yysize; yyi += 1)
	if (yyi != yyk && yystack->yytops.yystates[yyi] != NULL)
	  {
	    yyGLRState* yyp, *yysplit = yystack->yysplitPoint;
	    yyp = yystack->yytops.yystates[yyi];
	    while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
	      {
		if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
		  {
		    yyaddDeferredAction (yystack, yyp, yys0, yyrule);
		    yymarkStackDeleted (yystack, yyk);
		    YYDPRINTF ((stderr, "Merging stack %d into stack %d.\n",
				yyk, yyi));
		    return yyok;
		  }
		yyp = yyp->yypred;
	      }
	  }
      yystack->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystack, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static int
yysplitStack (yyGLRStack* yystack, int yyk)
{
  if (yystack->yysplitPoint == NULL)
    {
      if (yyk != 0)
	abort ();
      yystack->yysplitPoint = yystack->yytops.yystates[yyk];
    }
  if (yystack->yytops.yysize >= yystack->yytops.yycapacity)
    {
      yystack->yytops.yycapacity *= 2;
      yystack->yytops.yystates =
	(yyGLRState**) realloc (yystack->yytops.yystates,
				yystack->yytops.yycapacity
				* sizeof (yyGLRState*));
    }
  yystack->yytops.yystates[yystack->yytops.yysize]
    = yystack->yytops.yystates[yyk];
  yystack->yytops.yysize += 1;
  return yystack->yytops.yysize-1;
}

/** True iff Y0 and Y1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols. */
static bool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
	   yyn = yyrhsLength (yyy0->yyrule);
	   yyn > 0;
	   yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
	if (yys0->yyposn != yys1->yyposn)
	  return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (Y0,Y1), (destructively) merge the
 *  alternative semantic values for the RHS-symbols of Y1 into the
 *  corresponding semantic value sets of the symbols of Y0. */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    if (yys0 == yys1)
      break;
    else if (! yys0->yyresolved && ! yys1->yyresolved)
      {
	yySemanticOption* yyz;
	for (yyz = yys0->yysemantics.yyfirstVal; yyz->yynext != NULL;
	     yyz = yyz->yynext)
	  continue;
	yyz->yynext = yys1->yysemantics.yyfirstVal;
      }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred. */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
	return 0;
      else
	return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yySemanticOption* yyoptionList,
				   yyGLRStack* yystack, YYSTYPE* yyvalp,
				   YYLTYPE* yylocp);

static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn, yyGLRStack* yystack)
{
  YYRESULTTAG yyflag;
  if (0 < yyn)
    {
      if (! yys->yypred)
	abort ();
      yyflag = yyresolveStates (yys->yypred, yyn-1, yystack);
      if (yyflag != yyok)
	return yyflag;
      if (! yys->yyresolved)
	{
	  yyflag = yyresolveValue (yys->yysemantics.yyfirstVal, yystack,
				   &yys->yysemantics.yysval, &yys->yyloc
				  );
	  if (yyflag != yyok)
	    return yyflag;
	  yys->yyresolved = yytrue;
	}
    }
  return yyok;
}

static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystack,
	         YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS];
  int yynrhs, yyi;
  yyGLRState* yys;

  yynrhs = yyrhsLength (yyopt->yyrule);
  YYCHK (yyresolveStates (yyopt->yystate, yynrhs, yystack));
  for (yyi = yynrhs-1, yys = yyopt->yystate; 0 <= yyi;
       yyi -= 1, yys = yys->yypred)
    {
      if (! yys->yypred)
	abort ();
      yyrhsVals[yyi].yystate.yyresolved = yytrue;
      yyrhsVals[yyi].yystate.yysemantics.yysval = yys->yysemantics.yysval;
      yyrhsVals[yyi].yystate.yyloc = yys->yyloc;
    }
  return yyuserAction (yyopt->yyrule, yynrhs, yyrhsVals + (yynrhs-1),
		       yyvalp, yylocp, yystack);
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == NULL)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %d .. %d>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule, yys->yyposn+1, yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
	{
	  if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
	    YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]));
	  else
	    YYFPRINTF (stderr, "%*s%s <tokens %d .. %d>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]),
		       yystates[yyi-1]->yyposn+1, yystates[yyi]->yyposn);
	}
      else
	yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static void
yyreportAmbiguity (yySemanticOption* yyx0, yySemanticOption* yyx1,
		   yyGLRStack* yystack)
{
  /* `Unused' warnings.  */
  (void) yyx0;
  (void) yyx1;

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif
  yyFail (yystack, "ambiguity detected");
}


/** Resolve the ambiguity represented by OPTIONLIST, perform the indicated
 *  actions, and return the result. */
static YYRESULTTAG
yyresolveValue (yySemanticOption* yyoptionList, yyGLRStack* yystack,
		YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yySemanticOption* yybest;
  yySemanticOption* yyp;
  int yymerge;

  yybest = yyoptionList;
  yymerge = 0;
  for (yyp = yyoptionList->yynext; yyp != NULL; yyp = yyp->yynext)
    {
      if (yyidenticalOptions (yybest, yyp))
	yymergeOptionSets (yybest, yyp);
      else
	switch (yypreference (yybest, yyp))
	  {
	  case 0:
	    yyreportAmbiguity (yybest, yyp, yystack);
	    break;
	  case 1:
	    yymerge = 1;
	    break;
	  case 2:
	    break;
	  case 3:
	    yybest = yyp;
	    yymerge = 0;
	    break;
	  }
    }

  if (yymerge)
    {
      int yyprec = yydprec[yybest->yyrule];
      YYCHK (yyresolveAction (yybest, yystack, yyvalp, yylocp));
      for (yyp = yybest->yynext; yyp != NULL; yyp = yyp->yynext)
	{
	  if (yyprec == yydprec[yyp->yyrule])
	    {
	      YYSTYPE yyval1;
	      YYLTYPE yydummy;
	      YYCHK (yyresolveAction (yyp, yystack, &yyval1, &yydummy));
	      *yyvalp = yyuserMerge (yymerger[yyp->yyrule], yyvalp, &yyval1);
	    }
	}
      return yyok;
    }
  else
    return yyresolveAction (yybest, yystack, yyvalp, yylocp);
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystack)
{
  if (yystack->yysplitPoint != NULL)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystack->yytops.yystates[0];
	   yys != yystack->yysplitPoint;
	   yys = yys->yypred, yyn += 1)
	continue;
      YYCHK (yyresolveStates (yystack->yytops.yystates[0], yyn, yystack
			     ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystack)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystack->yytops.yysize != 1 || yystack->yysplitPoint == NULL)
    return;

  for (yyp = yystack->yytops.yystates[0], yyq = yyp->yypred, yyr = NULL;
       yyp != yystack->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystack->yyspaceLeft += yystack->yynextFree - yystack->yyitems;
  yystack->yynextFree = ((yyGLRStackItem*) yystack->yysplitPoint) + 1;
  yystack->yyspaceLeft -= yystack->yynextFree - yystack->yyitems;
  yystack->yysplitPoint = NULL;
  yystack->yylastDeleted = NULL;

  while (yyr != NULL)
    {
      yystack->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystack->yynextFree->yystate.yypred = & yystack->yynextFree[-1].yystate;
      yystack->yytops.yystates[0] = &yystack->yynextFree->yystate;
      yystack->yynextFree += 1;
      yystack->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystack, int yyk,
	           size_t yyposn, YYSTYPE* yylvalp, YYLTYPE* yyllocp
		  )
{
  int yyaction;
  const short* yyconflicts;
  yyRuleNum yyrule;
  yySymbol* const yytokenp = yystack->yytokenp;

  while (yystack->yytops.yystates[yyk] != NULL)
    {
      yyStateNum yystate = yystack->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %d Entering state %d\n", yyk, yystate));

      if (yystate == YYFINAL)
	abort ();
      if (yyisDefaultedState (yystate))
	{
	  yyrule = yydefaultAction (yystate);
	  if (yyrule == 0)
	    {
	      YYDPRINTF ((stderr, "Stack %d dies.\n", yyk));
	      yymarkStackDeleted (yystack, yyk);
	      return yyok;
	    }
	  YYCHK (yyglrReduce (yystack, yyk, yyrule, yyfalse));
	}
      else
	{
	  if (*yytokenp == YYEMPTY)
	    {
	      YYDPRINTF ((stderr, "Reading a token: "));
	      yychar = YYLEX;
	      *yytokenp = YYTRANSLATE (yychar);
	      YYDSYMPRINTF ("Next token is", *yytokenp, yylvalp, yyllocp);
	    }
	  yygetLRActions (yystate, *yytokenp, &yyaction, &yyconflicts);

	  while (*yyconflicts != 0)
	    {
	      int yynewStack = yysplitStack (yystack, yyk);
	      YYDPRINTF ((stderr, "Splitting off stack %d from %d.\n",
			  yynewStack, yyk));
	      YYCHK (yyglrReduce (yystack, yynewStack,
				  *yyconflicts, yyfalse));
	      YYCHK (yyprocessOneStack (yystack, yynewStack, yyposn,
					yylvalp, yyllocp));
	      yyconflicts += 1;
	    }

	  if (yyisShiftAction (yyaction))
	    {
	      YYDPRINTF ((stderr, "Shifting token %s on stack %d, ",
			  yytokenName (*yytokenp), yyk));
	      yyglrShift (yystack, yyk, yyaction, yyposn+1,
			  *yylvalp, yyllocp);
	      YYDPRINTF ((stderr, "which is now in state #%d\n",
			  yystack->yytops.yystates[yyk]->yylrState));
	      break;
	    }
	  else if (yyisErrorAction (yyaction))
	    {
	      YYDPRINTF ((stderr, "Stack %d dies.\n", yyk));
	      yymarkStackDeleted (yystack, yyk);
	      break;
	    }
	  else
	    YYCHK (yyglrReduce (yystack, yyk, -yyaction, yyfalse));
	}
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystack,
		     YYSTYPE* yylvalp, YYLTYPE* yyllocp)
{
  /* `Unused' warnings. */
  (void) yylvalp;
  (void) yyllocp;

  if (yystack->yyerrState == 0)
    {
#if YYERROR_VERBOSE
      yySymbol* const yytokenp = yystack->yytokenp;
      int yyn, yyx, yycount;
      size_t yysize;
      const char* yyprefix;
      char* yyp;
      char* yymsg;
      yyn = yypact[yystack->yytops.yystates[0]->yylrState];
      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  yysize = sizeof ("syntax error, unexpected ")
	    + strlen (yytokenName (*yytokenp));
	  yyprefix = ", expecting ";
	  for (yyx = yyn < 0 ? -yyn : 0; yyx < yytname_size && yycount <= 5;
	       yyx += 1)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += strlen (yytokenName (yyx)) + strlen (yyprefix),
		yycount += 1, yyprefix = " or ";
	  yymsg = yyp = (char*) malloc (yysize);
	  sprintf (yyp, "syntax error, unexpected %s",
		   yytokenName (*yytokenp));
	  yyp += strlen (yyp);
	  if (yycount < 5)
	    {
	      yyprefix = ", expecting ";
	      for (yyx = yyn < 0 ? -yyn : 0; yyx < yytname_size; yyx += 1)
		if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		  {
		    sprintf (yyp, "%s%s", yyprefix, yytokenName (yyx));
		    yyp += strlen (yyp);
		    yyprefix = " or ";
		  }
	    }
	  yyerror (yymsg);
	  free (yymsg);
	}
      else
#endif
	yyerror ("syntax error");
      yynerrs += 1;
    }
}

/* Recover from a syntax error on YYSTACK, assuming that YYTOKENP,
   YYLVALP, and YYLLOCP point to the syntactic category, semantic
   value, and location of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystack,
		      YYSTYPE* yylvalp, YYLTYPE* yyllocp)
{
  yySymbol* const yytokenp = yystack->yytokenp;
  size_t yyk;
  int yyj;

  if (yystack->yyerrState == 0)
    yystack->yyerrState = 3;
  else if (yystack->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
	if (*yytokenp == YYEOF)
	  {
	    /* Now pop stack until we find a state that shifts the
	       error token.  */
	    while (yystack->yytops.yystates[0] != NULL)
	      {
		yyGLRState *yys = yystack->yytops.yystates[0];
		YYDSYMPRINTF ("Error: popping",
			      yystos[yys->yylrState],
			      &yys->yysemantics.yysval, &yys->yyloc);
		yydestruct (yystos[yys->yylrState],
			    &yys->yysemantics.yysval, &yys->yyloc);
		yystack->yytops.yystates[0] = yys->yypred;
		yystack->yynextFree -= 1;
		yystack->yyspaceLeft += 1;
	      }
	    yyFail (yystack, NULL);
	  }
	if (*yytokenp != YYEMPTY)
	  {
	    YYDSYMPRINTF ("Error: discarding", *yytokenp, yylvalp, yyllocp);
	    yydestruct (*yytokenp, yylvalp, yyllocp);
	  }
	YYDPRINTF ((stderr, "Reading a token: "));
	yychar = YYLEX;
	*yytokenp = YYTRANSLATE (yychar);
	YYDSYMPRINTF ("Next token is", *yytokenp, yylvalp, yyllocp);
	yyj = yypact[yystack->yytops.yystates[0]->yylrState];
	if (yyis_pact_ninf (yyj))
	  /* Something's not right; we shouldn't be here.  */
	  yyFail (yystack, NULL);
	yyj += *yytokenp;
	if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != *yytokenp)
	  {
	    if (yydefact[yystack->yytops.yystates[0]->yylrState] != 0)
	      return;
	  }
	else if (yytable[yyj] != 0 && ! yyis_table_ninf (yytable[yyj]))
	  return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystack->yytops.yysize; yyk += 1)
    if (yystack->yytops.yystates[yyk] != NULL)
      break;
  if (yyk >= yystack->yytops.yysize)
    yyFail (yystack, NULL);
  for (yyk += 1; yyk < yystack->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystack, yyk);
  yyremoveDeletes (yystack);
  yycompressStack (yystack);

  /* Now pop stack until we find a state that shifts the error token. */
  while (yystack->yytops.yystates[0] != NULL)
    {
      yyGLRState *yys = yystack->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yyis_pact_ninf (yyj))
	{
	  yyj += YYTERROR;
	  if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
	      && yyisShiftAction (yytable[yyj]))
	    {
	      YYDPRINTF ((stderr, "Shifting error token, "));
	      yyglrShift (yystack, 0, yytable[yyj],
			  yys->yyposn, *yylvalp, yyllocp);
	      break;
	    }
	}
      YYDSYMPRINTF ("Error: popping",
 		    yystos[yys->yylrState],
 		    &yys->yysemantics.yysval, &yys->yyloc);
      yydestruct (yystos[yys->yylrState],
 	          &yys->yysemantics.yysval, &yys->yyloc);
      yystack->yytops.yystates[0] = yys->yypred;
      yystack->yynextFree -= 1;
      yystack->yyspaceLeft += 1;
    }
  if (yystack->yytops.yystates[0] == NULL)
    yyFail (yystack, NULL);
}

#define YYCHK1(YYE)							     \
  do {									     \
    switch (YYE) {							     \
    default:								     \
      break;								     \
    case yyabort:							     \
      yystack.yyerrflag = 1;						     \
      goto yyDone;							     \
    case yyaccept:							     \
      yystack.yyerrflag = 0;						     \
      goto yyDone;							     \
    case yyerr:								     \
      goto yyuser_error;						     \
    }									     \
  } while (0)


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  yySymbol yytoken;
  yyGLRStack yystack;
  size_t yyposn;


  YYSTYPE* const yylvalp = &yylval;
  YYLTYPE* const yyllocp = &yylloc;

  yyinitGLRStack (&yystack, YYINITDEPTH);
  yystack.yytokenp = &yytoken;

  YYDPRINTF ((stderr, "Starting parse\n"));

  if (setjmp (yystack.yyexception_buffer) != 0)
    goto yyDone;

  yyglrShift (&yystack, 0, 0, 0, yyval_default, &yyloc_default);
  yytoken = YYEMPTY;
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
	 specialized to deterministic operation (single stack, no
	 potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
	{
	  yyRuleNum yyrule;
	  int yyaction;
	  const short* yyconflicts;

	  yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
	  if (yystate == YYFINAL)
	    goto yyDone;
	  if (yyisDefaultedState (yystate))
	    {
	      yyrule = yydefaultAction (yystate);
	      if (yyrule == 0)
		{
		  yyreportSyntaxError (&yystack, yylvalp, yyllocp);
		  goto yyuser_error;
		}
	      YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
	    }
	  else
	    {
	      if (yytoken == YYEMPTY)
		{
		  YYDPRINTF ((stderr, "Reading a token: "));
		  yychar = YYLEX;
		  yytoken = YYTRANSLATE (yychar);
                  YYDSYMPRINTF ("Next token is", yytoken, yylvalp, yyllocp);
		}
	      yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
	      if (*yyconflicts != 0)
		break;
	      if (yyisShiftAction (yyaction))
		{
		  YYDPRINTF ((stderr, "Shifting token %s, ",
			      yytokenName (yytoken)));
		  if (yytoken != YYEOF)
		    yytoken = YYEMPTY;
		  yyposn += 1;
		  yyglrShift (&yystack, 0, yyaction, yyposn,
		              yylval, yyllocp);
		  if (0 < yystack.yyerrState)
		    yystack.yyerrState -= 1;
		}
	      else if (yyisErrorAction (yyaction))
		{
		  yyreportSyntaxError (&yystack, yylvalp, yyllocp);
		  goto yyuser_error;
		}
	      else
		YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
	    }
	}

      while (yytrue)
	{
	  int yys;
	  int yyn = yystack.yytops.yysize;
	  for (yys = 0; yys < yyn; yys += 1)
	    YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn,
				       yylvalp, yyllocp));
	  yytoken = YYEMPTY;
	  yyposn += 1;
	  yyremoveDeletes (&yystack);
	  if (yystack.yytops.yysize == 0)
	    {
	      yyundeleteLastStack (&yystack);
	      if (yystack.yytops.yysize == 0)
		yyFail (&yystack, "syntax error");
	      YYCHK1 (yyresolveStack (&yystack));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
	      yyreportSyntaxError (&yystack, yylvalp, yyllocp);
	      goto yyuser_error;
	    }
	  else if (yystack.yytops.yysize == 1)
	    {
	      YYCHK1 (yyresolveStack (&yystack));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
	      yycompressStack (&yystack);
	      break;
	    }
	}
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, yylvalp, yyllocp);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }
 yyDone:
  ;

  yyfreeGLRStack (&yystack);
  return yystack.yyerrflag;
}

/* DEBUGGING ONLY */
static void yypstack (yyGLRStack* yystack, int yyk) ATTRIBUTE_UNUSED;
static void yypdumpstack (yyGLRStack* yystack) ATTRIBUTE_UNUSED;

static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      fprintf (stderr, " -> ");
    }
  fprintf (stderr, "%d@%lu", yys->yylrState, (unsigned long) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == NULL)
    fprintf (stderr, "<null>");
  else
    yy_yypstack (yyst);
  fprintf (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystack, int yyk)
{
  yypstates (yystack->yytops.yystates[yyk]);
}

#define YYINDEX(YYX) 							     \
    ((YYX) == NULL ? -1 : (yyGLRStackItem*) (YYX) - yystack->yyitems)


static void
yypdumpstack (yyGLRStack* yystack)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystack->yyitems; yyp < yystack->yynextFree; yyp += 1)
    {
      fprintf (stderr, "%3lu. ", (unsigned long) (yyp - yystack->yyitems));
      if (*(bool*) yyp)
	{
	  fprintf (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
		   yyp->yystate.yyresolved, yyp->yystate.yylrState,
		   (unsigned long) yyp->yystate.yyposn,
		   (long) YYINDEX (yyp->yystate.yypred));
	  if (! yyp->yystate.yyresolved)
	    fprintf (stderr, ", firstVal: %ld",
		     (long) YYINDEX (yyp->yystate.yysemantics.yyfirstVal));
	}
      else
	{
	  fprintf (stderr, "Option. rule: %d, state: %ld, next: %ld",
		   yyp->yyoption.yyrule,
		   (long) YYINDEX (yyp->yyoption.yystate),
		   (long) YYINDEX (yyp->yyoption.yynext));
	}
      fprintf (stderr, "\n");
    }
  fprintf (stderr, "Tops:");
  for (yyi = 0; yyi < yystack->yytops.yysize; yyi += 1)
    fprintf (stderr, "%lu: %ld; ", (unsigned long) yyi,
	     (long) YYINDEX (yystack->yytops.yystates[yyi]));
  fprintf (stderr, "\n");
}


#line 214 "c:\\mmstudio\\extras\\ljavac\\pp_parse.y"


