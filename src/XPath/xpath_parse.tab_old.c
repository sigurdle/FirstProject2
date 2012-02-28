/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse xpath_parse
#define yylex   xpath_lex
#define yyerror xpath_error
#define yylval  xpath_lval
#define yychar  xpath_char
#define yydebug xpath_debug
#define yynerrs xpath_nerrs
#define yylloc xpath_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER_LITERAL = 258,
     STRING_LITERAL = 259,
     identifier = 260,
     TWO_COLON = 261,
     TWO_PUNCT = 262,
     TWO_SLASH = 263,
     NCName = 264,
     AxisName = 265,
     OR = 266,
     AND = 267,
     EQ = 268,
     NEQ = 269,
     LTEQ = 270,
     GTEQ = 271,
     DIV = 272,
     IDIV = 273,
     MOD = 274,
     ELEMENT_KW = 275,
     INSTANCE_KW = 276,
     OF_KW = 277,
     EMPTY_SEQUENCE_KW = 278,
     EMPTY_ELEMENT = 279,
     ELEMENT_END = 280
   };
#endif
#define INTEGER_LITERAL 258
#define STRING_LITERAL 259
#define identifier 260
#define TWO_COLON 261
#define TWO_PUNCT 262
#define TWO_SLASH 263
#define NCName 264
#define AxisName 265
#define OR 266
#define AND 267
#define EQ 268
#define NEQ 269
#define LTEQ 270
#define GTEQ 271
#define DIV 272
#define IDIV 273
#define MOD 274
#define ELEMENT_KW 275
#define INSTANCE_KW 276
#define OF_KW 277
#define EMPTY_SEQUENCE_KW 278
#define EMPTY_ELEMENT 279
#define ELEMENT_END 280




/* Copy the first part of user declarations.  */
#line 1 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"


void xpath_error (/*YYLTYPE *llocp,*/ char const *s);
int xpath_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/);

extern Exp* g_exp;

#define YYERROR_VERBOSE

#define yyfalse	0
#define yytrue		1

union YYSTYPE;

     

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 21 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
typedef union YYSTYPE {
int num;
System::StringW* id;
System::StringW* string_literal;
Exp* exp;
Step* step;
StepList* steps;
ExpList* expList;
QName* qname;
NodeTest* nodetest;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 162 "c:\\mmstudio\\src\\XPath\\xpath_parse.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
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
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 186 "c:\\mmstudio\\src\\XPath\\xpath_parse.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   133

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  51
/* YYNRULES -- Number of rules. */
#define YYNRULES  94
/* YYNRULES -- Number of states. */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      30,    31,    32,    38,    26,    39,    28,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,     2,
      36,     2,    37,    40,    29,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,    11,    13,    15,    17,    21,
      23,    25,    29,    32,    34,    37,    38,    40,    42,    44,
      48,    53,    60,    62,    64,    66,    68,    70,    74,    78,
      80,    84,    88,    90,    92,    96,    98,   100,   102,   104,
     106,   110,   115,   117,   119,   121,   126,   135,   136,   138,
     140,   143,   147,   149,   152,   154,   156,   160,   162,   166,
     168,   172,   176,   178,   182,   186,   190,   194,   196,   200,
     204,   206,   210,   214,   218,   222,   224,   227,   230,   232,
     234,   236,   238,   240,   242,   244,   246,   251,   255,   257,
     260,   262,   264,   266,   268
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      42,     0,    -1,    43,    -1,    44,    -1,    43,    26,    44,
      -1,    73,    -1,    46,    -1,    47,    -1,    47,    27,    46,
      -1,    48,    -1,    91,    -1,    49,    52,    51,    -1,    10,
       6,    -1,    58,    -1,    50,    58,    -1,    -1,    50,    -1,
      54,    -1,    53,    -1,    20,    30,    31,    -1,    20,    30,
      55,    31,    -1,    20,    30,    55,    26,    57,    31,    -1,
      56,    -1,    57,    -1,    32,    -1,    57,    -1,    32,    -1,
       9,    33,    32,    -1,    32,    33,     9,    -1,     9,    -1,
       9,    33,     9,    -1,    34,    59,    35,    -1,    43,    -1,
       3,    -1,    30,    43,    31,    -1,    60,    -1,    64,    -1,
      63,    -1,    65,    -1,    44,    -1,    62,    26,    44,    -1,
      57,    30,    62,    31,    -1,    28,    -1,    66,    -1,    67,
      -1,    36,    57,    68,    24,    -1,    36,    57,    68,    37,
      71,    25,    57,    37,    -1,    -1,    69,    -1,    70,    -1,
      69,    70,    -1,    57,    13,     4,    -1,    72,    -1,    71,
      72,    -1,    66,    -1,    74,    -1,    73,    11,    74,    -1,
      75,    -1,    74,    12,    75,    -1,    76,    -1,    75,    13,
      76,    -1,    75,    14,    76,    -1,    77,    -1,    76,    36,
      77,    -1,    76,    37,    77,    -1,    76,    15,    77,    -1,
      76,    16,    77,    -1,    78,    -1,    77,    38,    78,    -1,
      77,    39,    78,    -1,    81,    -1,    78,    32,    81,    -1,
      78,    17,    81,    -1,    78,    18,    81,    -1,    78,    19,
      81,    -1,    80,    -1,    39,    79,    -1,    38,    79,    -1,
      83,    -1,    82,    -1,    87,    -1,    45,    -1,    79,    -1,
      84,    -1,    85,    -1,    86,    -1,    86,    21,    22,    88,
      -1,    23,    30,    31,    -1,    89,    -1,    89,    90,    -1,
      53,    -1,    40,    -1,    32,    -1,    38,    -1,    61,    51,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   105,   105,   109,   110,   113,   116,   124,   125,   149,
     150,   153,   157,   160,   161,   164,   165,   168,   169,   176,
     177,   178,   181,   182,   185,   186,   189,   190,   191,   194,
     195,   198,   201,   204,   208,   210,   211,   212,   213,   216,
     217,   220,   222,   225,   228,   234,   235,   238,   239,   242,
     243,   246,   249,   250,   253,   256,   257,   260,   261,   264,
     265,   266,   268,   269,   270,   271,   272,   275,   276,   277,
     280,   281,   282,   283,   284,   287,   288,   289,   292,   301,
     305,   308,   315,   318,   321,   324,   325,   328,   329,   330,
     333,   336,   337,   338,   344
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_LITERAL", "STRING_LITERAL", 
  "identifier", "TWO_COLON", "TWO_PUNCT", "TWO_SLASH", "NCName", 
  "AxisName", "OR", "AND", "EQ", "NEQ", "LTEQ", "GTEQ", "DIV", "IDIV", 
  "MOD", "ELEMENT_KW", "INSTANCE_KW", "OF_KW", "EMPTY_SEQUENCE_KW", 
  "EMPTY_ELEMENT", "ELEMENT_END", "','", "'/'", "'.'", "'@'", "'('", 
  "')'", "'*'", "':'", "'['", "']'", "'<'", "'>'", "'+'", "'-'", "'?'", 
  "$accept", "XPath", "Expr", "ExprSingle", "LocationPath", 
  "RelativeLocationPath", "StepExpr", "AxisStep", "AxisSpecifier", 
  "Predicates", "Predicates_opt", "NodeTest", "KindTest", "NameTest", 
  "QNameOrWildcard", "Wildcard", "QName", "Predicate", "PredicateExpr", 
  "Number", "PrimaryExpr", "ExprList", "FunctionCall", "ContextItemExpr", 
  "Constructor", "DirectConstructor", "DirElemConstructor", 
  "DirAttributeList_opt", "DirAttributeList", "DirAttribute", 
  "DirElemContents", "DirElemContent", "OrExpr", "AndExpr", 
  "EqualityExpr", "RelationalExpr", "AdditiveExpr", "MultiplicativeExpr", 
  "UnaryExpr", "ValueExpr", "UnionExpr", "IntersectExceptExpr", 
  "PathExpr", "CastExpr", "CastableExpr", "TreatExpr", "InstanceofExpr", 
  "SequenceType", "ItemType", "OccurrenceIndicator", "FilterExpr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    44,    47,    46,    64,
      40,    41,    42,    58,    91,    93,    60,    62,    43,    45,
      63
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    46,    46,    47,
      47,    48,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    53,    54,    54,    55,    55,    56,    56,    56,    57,
      57,    58,    59,    60,    61,    61,    61,    61,    61,    62,
      62,    63,    64,    65,    66,    67,    67,    68,    68,    69,
      69,    70,    71,    71,    72,    73,    73,    74,    74,    75,
      75,    75,    76,    76,    76,    76,    76,    77,    77,    77,
      78,    78,    78,    78,    78,    79,    79,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    87,    88,    88,    88,
      89,    90,    90,    90,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     3,     2,     1,     2,     0,     1,     1,     1,     3,
       4,     6,     1,     1,     1,     1,     1,     3,     3,     1,
       3,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     4,     1,     1,     1,     4,     8,     0,     1,     1,
       2,     3,     1,     2,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     1,     2,
       1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,    33,    29,     0,    42,     0,     0,     0,     0,     0,
       2,     3,    81,     6,     7,     9,     0,     0,    35,    15,
      37,    36,    38,    43,    44,     5,    55,    57,    59,    62,
      67,    82,    75,    70,    79,    78,    83,    84,    85,    80,
      10,     0,    12,     0,    47,    77,    76,     1,     0,     0,
      29,     0,    26,    15,    18,    17,    22,    23,     0,     0,
      16,    94,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    34,
       0,     0,    48,    49,     4,     8,     0,     0,     0,    11,
      39,     0,    32,     0,    14,    56,    58,    60,    61,    65,
      66,    63,    64,    68,    69,    72,    73,    74,    71,     0,
       0,    45,     0,    50,    27,    19,    24,     0,    25,    28,
       0,    41,    31,     0,    90,    86,    88,    51,    54,     0,
      52,     0,    20,    40,     0,    92,    93,    91,    89,     0,
      53,     0,    87,     0,    21,    46
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    60,
      61,    53,    54,    55,   117,    56,    17,    62,    93,    18,
      19,    91,    20,    21,    22,    23,    24,    81,    82,    83,
     129,   130,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,   125,   126,   138,
      40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -110
static const yysigned_char yypact[] =
{
       3,  -110,   -14,    10,  -110,     3,    14,     3,     3,    26,
       6,  -110,  -110,  -110,     7,  -110,    -5,    35,  -110,    18,
    -110,  -110,  -110,  -110,  -110,    38,    47,    50,    21,    32,
      29,  -110,  -110,  -110,  -110,  -110,  -110,  -110,    51,  -110,
    -110,    77,  -110,   -17,    14,  -110,  -110,  -110,     3,    15,
      54,    58,    56,    18,  -110,  -110,  -110,  -110,     3,     3,
      18,  -110,  -110,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,    68,  -110,  -110,
      78,   -16,    14,  -110,  -110,  -110,    -4,    -2,    83,  -110,
    -110,    -9,     6,    59,  -110,    47,    50,    21,    21,    32,
      32,    32,    32,    29,    29,  -110,  -110,  -110,  -110,    30,
      89,  -110,    60,  -110,  -110,  -110,  -110,     9,  -110,  -110,
       3,  -110,  -110,    65,  -110,  -110,    22,  -110,  -110,    19,
    -110,    14,  -110,  -110,    66,  -110,  -110,  -110,  -110,    14,
    -110,    69,  -110,    61,  -110,  -110
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -110,  -110,    -3,   -47,  -110,    52,  -110,  -110,  -110,  -110,
      46,  -110,    -7,  -110,  -110,  -110,    -6,    43,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,  -109,  -110,  -110,  -110,    23,
    -110,   -25,  -110,    44,    42,    17,    -1,    13,    67,  -110,
       4,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      44,    84,    43,   128,    50,    78,     1,     2,   111,    48,
      57,    90,     2,     3,    79,    51,    42,   120,     1,    41,
     128,   112,   121,     2,     2,     3,    47,    52,   114,   115,
     116,     4,    48,     5,    49,   131,    67,    68,    80,     6,
     132,     7,     8,     4,   139,     5,    73,    74,    75,    63,
      51,     6,    59,   123,   135,     6,    92,    69,    70,    64,
     136,    76,   137,    65,    66,    58,    99,   100,   101,   102,
      71,    72,    77,   133,    45,    46,    80,   105,   106,   107,
     108,   118,    97,    98,   103,   104,    78,    86,    87,    88,
     109,   110,   119,   127,   122,   134,     6,   142,   145,    89,
     144,    85,   124,    94,   140,   113,    96,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141,     0,     0,     0,     0,
       0,     0,     0,   143
};

static const short yycheck[] =
{
       6,    48,     5,   112,     9,     9,     3,     9,    24,    26,
      16,    58,     9,    10,    31,    20,     6,    26,     3,    33,
     129,    37,    31,     9,     9,    10,     0,    32,    32,    31,
      32,    28,    26,    30,    27,    26,    15,    16,    44,    36,
      31,    38,    39,    28,    25,    30,    17,    18,    19,    11,
      20,    36,    34,    23,    32,    36,    59,    36,    37,    12,
      38,    32,    40,    13,    14,    30,    67,    68,    69,    70,
      38,    39,    21,   120,     7,     8,    82,    73,    74,    75,
      76,    87,    65,    66,    71,    72,     9,    33,    30,    33,
      22,    13,     9,     4,    35,    30,    36,    31,    37,    53,
      31,    49,   109,    60,   129,    82,    64,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     9,    10,    28,    30,    36,    38,    39,    42,
      43,    44,    45,    46,    47,    48,    49,    57,    60,    61,
      63,    64,    65,    66,    67,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      91,    33,     6,    43,    57,    79,    79,     0,    26,    27,
       9,    20,    32,    52,    53,    54,    56,    57,    30,    34,
      50,    51,    58,    11,    12,    13,    14,    15,    16,    36,
      37,    38,    39,    17,    18,    19,    32,    21,     9,    31,
      57,    68,    69,    70,    44,    46,    33,    30,    33,    51,
      44,    62,    43,    59,    58,    74,    75,    76,    76,    77,
      77,    77,    77,    78,    78,    81,    81,    81,    81,    22,
      13,    24,    37,    70,    32,    31,    32,    55,    57,     9,
      26,    31,    35,    23,    53,    88,    89,     4,    66,    71,
      72,    26,    31,    44,    30,    32,    38,    40,    90,    25,
      72,    57,    31,    57,    31,    37
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

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

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
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

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
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


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE *yylerrsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 105 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = yyvsp[0].exp; g_exp = yyval.exp; YYACCEPT ;}
    break;

  case 3:
#line 109 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = yyvsp[0].exp ;}
    break;

  case 4:
#line 110 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, ',', yyvsp[0].exp) ;}
    break;

  case 7:
#line 124 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.steps = new StepList(yyvsp[0].step, NULL) ;}
    break;

  case 8:
#line 125 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.steps = new StepList(yyvsp[-2].step, yyvsp[0].steps) ;}
    break;

  case 11:
#line 153 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.step = new AxisStep(yyvsp[-2].num, yyvsp[-1].nodetest, Reverse(yyvsp[0].expList)) ;}
    break;

  case 13:
#line 160 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.expList = new ExpList(yyvsp[0].exp, NULL) ;}
    break;

  case 14:
#line 161 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.expList = new ExpList(yyvsp[0].exp, yyvsp[-1].expList) ;}
    break;

  case 15:
#line 164 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.expList = NULL ;}
    break;

  case 19:
#line 176 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.nodetest = new NodeTest(NULL, NULL) ;}
    break;

  case 20:
#line 177 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.nodetest = new NodeTest(yyvsp[-1].qname, NULL) ;}
    break;

  case 21:
#line 178 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.nodetest = new NodeTest(yyvsp[-3].qname, yyvsp[-1].qname) ;}
    break;

  case 22:
#line 181 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.nodetest = new NodeTest(yyvsp[0].qname) ;}
    break;

  case 23:
#line 182 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.nodetest = new NodeTest(yyvsp[0].qname) ;}
    break;

  case 24:
#line 185 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.qname = NULL ;}
    break;

  case 26:
#line 189 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.qname = NULL ;}
    break;

  case 27:
#line 190 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.qname = new QName(yyvsp[-2].id, star_str) ;}
    break;

  case 28:
#line 191 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.qname = new QName(star_str, yyvsp[0].id) ;}
    break;

  case 29:
#line 194 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.qname = new QName(NULL, yyvsp[0].id) ;}
    break;

  case 30:
#line 195 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.qname = new QName(yyvsp[-2].id, yyvsp[0].id) ;}
    break;

  case 31:
#line 198 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = yyvsp[-1].exp ;}
    break;

  case 33:
#line 204 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = NumberExp(yyvsp[0].num) ;}
    break;

  case 34:
#line 208 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = yyvsp[-1].exp ;}
    break;

  case 39:
#line 216 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.expList = new ExpList(yyvsp[0].exp, NULL) ;}
    break;

  case 40:
#line 217 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.expList = new ExpList(yyvsp[0].exp, yyvsp[-2].expList) ;}
    break;

  case 41:
#line 220 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new FunctionCallExp(yyvsp[-3].qname, Reverse(yyvsp[-1].expList)) ;}
    break;

  case 42:
#line 222 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new ContextItemExp() ;}
    break;

  case 57:
#line 260 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = yyvsp[0].exp ;}
    break;

  case 58:
#line 261 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, 'AND', yyvsp[0].exp) ;}
    break;

  case 60:
#line 265 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '=', yyvsp[0].exp) ;}
    break;

  case 61:
#line 266 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '!=', yyvsp[0].exp) ;}
    break;

  case 63:
#line 269 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '<', yyvsp[0].exp) ;}
    break;

  case 64:
#line 270 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '>', yyvsp[0].exp) ;}
    break;

  case 65:
#line 271 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '<=', yyvsp[0].exp) ;}
    break;

  case 66:
#line 272 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '>=', yyvsp[0].exp) ;}
    break;

  case 68:
#line 276 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '+', yyvsp[0].exp) ;}
    break;

  case 69:
#line 277 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '-', yyvsp[0].exp) ;}
    break;

  case 71:
#line 281 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, '*', yyvsp[0].exp) ;}
    break;

  case 72:
#line 282 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, 'div', yyvsp[0].exp) ;}
    break;

  case 73:
#line 283 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, 'idiv', yyvsp[0].exp) ;}
    break;

  case 74:
#line 284 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new BinopExp(yyvsp[-2].exp, 'mod', yyvsp[0].exp) ;}
    break;

  case 76:
#line 288 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new UnopExp(yyvsp[0].exp, '-') ;}
    break;

  case 77:
#line 289 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new UnopExp(yyvsp[0].exp, '+') ;}
    break;

  case 81:
#line 308 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new PathExp(yyvsp[0].steps);}
    break;

  case 86:
#line 325 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.exp = new InstanceOfExp(yyvsp[-3].exp, yyvsp[0].nodetest) ;}
    break;

  case 87:
#line 328 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.nodetest = NULL ;}
    break;

  case 89:
#line 330 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { ASSERT(0) ;}
    break;

  case 94:
#line 344 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"
    { yyval.step = new FilterStep(yyvsp[-1].exp, Reverse(yyvsp[0].expList)) ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1462 "c:\\mmstudio\\src\\XPath\\xpath_parse.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }

  yylerrsp = yylsp;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp, yylsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval, &yylloc);
      yychar = YYEMPTY;
      *++yylerrsp = yylloc;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif

  yylerrsp = yylsp;
  *++yylerrsp = yyloc;
  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp, yylsp);
      yyvsp--;
      yystate = *--yyssp;
      yylsp--;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, (yylerrsp - yylsp));
  *++yylsp = yyloc;

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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 347 "c:\\mmstudio\\src\\XPath\\xpath_parse.y"


