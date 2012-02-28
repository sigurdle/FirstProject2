
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         ecmascriptparse
#define yylex           ecmascriptlex
#define yyerror         ecmascripterror
#define yylval          ecmascriptlval
#define yychar          ecmascriptchar
#define yydebug         ecmascriptdebug
#define yynerrs         ecmascriptnerrs
#define yylloc          ecmascriptlloc

/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"


#include "lfc/lfc.h"
#include "ecmascript_ast.h"

#define YYERROR_VERBOSE

int ecmascriptlex();
void ecmascripterror (/*YYLTYPE *llocp,*/ char const *s);

extern A_ElemList* g_program;



/* Line 189 of yacc.c  */
#line 96 "ecmascript_parse.tab.cc"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRING_LITERAL = 258,
     INTEGER_LITERAL = 259,
     FLOAT_LITERAL = 260,
     IDENTIFIER = 261,
     NULL_KW = 262,
     TRUE_KW = 263,
     FALSE_KW = 264,
     THIS_KW = 265,
     NEW_KW = 266,
     DELETE_KW = 267,
     FUNCTION_KW = 268,
     RETURN_KW = 269,
     VOID_KW = 270,
     IF_KW = 271,
     ELSE_KW = 272,
     VAR_KW = 273,
     DO_KW = 274,
     WHILE_KW = 275,
     FOR_KW = 276,
     BREAK_KW = 277,
     CONTINUE_KW = 278,
     IN_KW = 279,
     TYPEOF_KW = 280,
     TRY_KW = 281,
     CATCH_KW = 282,
     THROW_KW = 283,
     PLUSPLUS = 284,
     MINUSMINUS = 285,
     LOGICAL_OR = 286,
     LOGICAL_AND = 287,
     EQUALEQUAL = 288,
     LEQ = 289,
     GEQ = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 22 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"

int int_literal;
double float64_literal;
char* id;
char* string_literal;
A_Exp* exp;
A_Stm* stm;
A_StmList* stm_list;
A_Function* fun;
A_Elem* elem;
A_ElemList* elem_list;
A_VarDecl* vardecl;
A_VarDeclList* vardecl_list;
A_ExpList* exp_list;
A_IdentifierList* id_list;



/* Line 214 of yacc.c  */
#line 186 "ecmascript_parse.tab.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
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


/* Line 264 of yacc.c  */
#line 211 "ecmascript_parse.tab.cc"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   354

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNRULES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,     2,     2,     2,     2,     2,
      36,    37,    47,    43,    42,    44,    41,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    51,
      49,    38,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    53,    45,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    37,    39,
      41,    43,    45,    47,    52,    56,    60,    62,    65,    68,
      71,    76,    80,    83,    87,    89,    93,    95,    98,   101,
     103,   106,   109,   112,   115,   118,   121,   124,   127,   130,
     132,   136,   140,   142,   146,   150,   152,   156,   160,   164,
     168,   170,   172,   176,   178,   180,   184,   186,   190,   191,
     193,   195,   197,   199,   201,   203,   205,   208,   216,   222,
     230,   236,   246,   250,   254,   255,   257,   259,   262,   266,
     268,   272,   275,   276,   278,   281,   290,   298,   299,   301,
     303,   307,   309,   311,   314,   316
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    99,    -1,     6,    -1,    58,    -1,    59,
      -1,    60,    -1,    61,    -1,     7,    -1,     8,    -1,     9,
      -1,     4,    -1,     5,    -1,     3,    -1,    10,    -1,    56,
      -1,    57,    -1,    36,    79,    37,    -1,    38,    -1,    66,
      -1,    67,    -1,    62,    -1,    95,    -1,    65,    39,    79,
      40,    -1,    65,    41,    56,    -1,    11,    65,    68,    -1,
      65,    -1,    11,    66,    -1,    65,    68,    -1,    67,    68,
      -1,    67,    39,    79,    40,    -1,    67,    41,    56,    -1,
      36,    37,    -1,    36,    69,    37,    -1,    78,    -1,    69,
      42,    78,    -1,    64,    -1,    64,    29,    -1,    64,    30,
      -1,    70,    -1,    12,    71,    -1,    15,    71,    -1,    25,
      71,    -1,    29,    71,    -1,    30,    71,    -1,    43,    71,
      -1,    44,    71,    -1,    45,    71,    -1,    46,    71,    -1,
      71,    -1,    72,    47,    71,    -1,    72,    48,    71,    -1,
      72,    -1,    73,    43,    72,    -1,    73,    44,    72,    -1,
      73,    -1,    74,    49,    73,    -1,    74,    50,    73,    -1,
      74,    34,    73,    -1,    74,    35,    73,    -1,    74,    -1,
      75,    -1,    76,    31,    75,    -1,    76,    -1,    77,    -1,
      64,    63,    78,    -1,    78,    -1,    79,    42,    78,    -1,
      -1,    79,    -1,    86,    -1,    89,    -1,    82,    -1,    83,
      -1,    84,    -1,    85,    -1,    79,    51,    -1,    16,    36,
      79,    37,    81,    17,    81,    -1,    16,    36,    79,    37,
      81,    -1,    19,    81,    20,    36,    79,    37,    51,    -1,
      20,    36,    79,    37,    81,    -1,    21,    36,    79,    51,
      80,    51,    80,    37,    81,    -1,    14,    80,    51,    -1,
      52,    87,    53,    -1,    -1,    88,    -1,    81,    -1,    88,
      81,    -1,    18,    90,    51,    -1,    91,    -1,    90,    42,
      91,    -1,    56,    92,    -1,    -1,    93,    -1,    38,    78,
      -1,    13,    56,    36,    96,    37,    52,    98,    53,    -1,
      13,    36,    96,    37,    52,    98,    53,    -1,    -1,    97,
      -1,    56,    -1,    97,    42,    56,    -1,    99,    -1,   100,
      -1,    99,   100,    -1,    81,    -1,    94,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   131,   134,   135,   136,   137,   140,   143,
     144,   147,   148,   158,   160,   161,   162,   165,   168,   171,
     172,   175,   176,   180,   184,   188,   191,   192,   195,   196,
     197,   198,   201,   202,   205,   206,   209,   210,   211,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   226,
     227,   228,   231,   232,   233,   236,   237,   238,   239,   240,
     243,   246,   247,   250,   253,   254,   257,   258,   261,   262,
     267,   268,   272,   273,   274,   279,   289,   292,   293,   296,
     297,   298,   309,   312,   315,   316,   319,   320,   323,   326,
     327,   330,   333,   334,   337,   345,   348,   351,   352,   355,
     356,   359,   362,   363,   366,   367
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING_LITERAL", "INTEGER_LITERAL",
  "FLOAT_LITERAL", "IDENTIFIER", "NULL_KW", "TRUE_KW", "FALSE_KW",
  "THIS_KW", "NEW_KW", "DELETE_KW", "FUNCTION_KW", "RETURN_KW", "VOID_KW",
  "IF_KW", "ELSE_KW", "VAR_KW", "DO_KW", "WHILE_KW", "FOR_KW", "BREAK_KW",
  "CONTINUE_KW", "IN_KW", "TYPEOF_KW", "TRY_KW", "CATCH_KW", "THROW_KW",
  "PLUSPLUS", "MINUSMINUS", "LOGICAL_OR", "LOGICAL_AND", "EQUALEQUAL",
  "LEQ", "GEQ", "'('", "')'", "'='", "'['", "']'", "'.'", "','", "'+'",
  "'-'", "'~'", "'!'", "'*'", "'/'", "'<'", "'>'", "';'", "'{'", "'}'",
  "$accept", "Program", "Identifier", "Literal", "NullLiteral",
  "BooleanLiteral", "NumericLiteral", "StringLiteral", "PrimaryExpression",
  "AssignmentOperator", "LeftHandSideExpression", "MemberExpression",
  "NewExpression", "CallExpression", "Arguments", "ArgumentList",
  "PostfixExpression", "UnaryExpression", "MultiplicativeExpression",
  "AdditiveExpression", "RelationalExpression", "LogicalANDExpression",
  "LogicalORExpression", "ConditionalExpression", "AssignmentExpression",
  "Expression", "Expression_opt", "Statement", "ExpressionStatement",
  "IfStatement", "IterationStatement", "ReturnStatement", "Block",
  "StatementList_opt", "StatementList", "VariableStatement",
  "VariableDeclarationList", "VariableDeclaration", "Initialiser_opt",
  "Initialiser", "FunctionDeclaration", "FunctionExpression",
  "FormalParameterList_opt", "FormalParameterList", "FunctionBody",
  "SourceElements", "SourceElement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    40,    41,    61,    91,
      93,    46,    44,    43,    45,   126,    33,    42,    47,    60,
      62,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    57,    57,    57,    57,    58,    59,
      59,    60,    60,    61,    62,    62,    62,    62,    63,    64,
      64,    65,    65,    65,    65,    65,    66,    66,    67,    67,
      67,    67,    68,    68,    69,    69,    70,    70,    70,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      75,    76,    76,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    82,    83,    83,    84,
      84,    84,    85,    86,    87,    87,    88,    88,    89,    90,
      90,    91,    92,    92,    93,    94,    95,    96,    96,    97,
      97,    98,    99,    99,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     4,     3,     3,     1,     2,     2,     2,
       4,     3,     2,     3,     1,     3,     1,     2,     2,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     1,     3,     1,     1,     3,     1,     3,     0,     1,
       1,     1,     1,     1,     1,     1,     2,     7,     5,     7,
       5,     9,     3,     3,     0,     1,     1,     2,     3,     1,
       3,     2,     0,     1,     2,     8,     7,     0,     1,     1,
       3,     1,     1,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    13,    11,    12,     3,     8,     9,    10,    14,     0,
       0,     0,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    84,     0,    15,
      16,     4,     5,     6,     7,    21,    36,    26,    19,    20,
      39,    49,    52,    55,    60,    61,    63,    64,    66,     0,
     104,    72,    73,    74,    75,    70,    71,   105,    22,     2,
     102,     0,    26,    27,    36,    40,    97,     0,    69,     0,
      41,     0,    92,     0,    89,     0,     0,     0,    42,    43,
      44,     0,    45,    46,    47,    48,    86,     0,    85,     1,
      37,    38,    18,     0,     0,     0,     0,    28,     0,     0,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,   103,    25,    99,     0,    98,    97,    82,     0,
       0,    91,    93,     0,    88,     0,     0,     0,    17,    83,
      87,    65,    32,     0,    34,     0,    24,     0,    31,    50,
      51,    53,    54,    58,    59,    56,    57,    62,    67,     0,
       0,     0,     0,    94,    90,     0,     0,    68,    33,     0,
      23,    30,     0,   100,     0,    78,     0,    80,     0,    35,
       0,   101,     0,     0,     0,    68,    96,     0,    77,    79,
       0,    95,     0,    81
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    93,
      36,    37,    38,    39,    97,   133,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    69,    50,    51,    52,
      53,    54,    55,    87,    88,    56,    73,    74,   121,   122,
      57,    58,   115,   116,   170,   171,    60
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -151
static const yytype_int16 yypact[] =
{
     164,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,    38,
     308,    -1,   308,   308,   -33,     4,   214,   -18,    -8,   308,
     308,   308,   308,   308,   308,   308,   308,   214,    58,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,    26,    24,  -151,    42,
    -151,  -151,    29,    78,    19,  -151,     0,  -151,  -151,    20,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,   164,
    -151,    34,    24,  -151,    94,  -151,     4,    44,    45,    57,
    -151,   308,    55,    31,  -151,    92,   308,   308,  -151,  -151,
    -151,   -13,  -151,  -151,  -151,  -151,  -151,    74,   214,  -151,
    -151,  -151,  -151,   308,   264,   308,     4,  -151,   308,     4,
    -151,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,  -151,  -151,  -151,  -151,    91,    87,     4,  -151,    15,
     308,  -151,  -151,     4,  -151,    95,    49,    33,  -151,  -151,
    -151,  -151,  -151,    53,  -151,    54,  -151,    67,  -151,  -151,
    -151,    29,    29,    78,    78,    78,    78,  -151,  -151,    80,
       4,    93,   214,  -151,  -151,   308,   214,   308,  -151,   308,
    -151,  -151,   164,  -151,    81,   117,    69,  -151,    84,  -151,
      85,   164,   164,   214,    86,   308,  -151,    88,  -151,  -151,
     102,  -151,   214,  -151
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,    -7,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
      -4,   133,   135,  -151,   -12,  -151,  -151,    13,    22,    12,
    -151,    37,  -151,  -151,   -80,   -10,  -150,   -16,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,    25,  -151,  -151,
    -151,  -151,    32,  -151,   -22,   151,   -58
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      75,   112,    68,    71,    67,     4,    64,   168,    72,    64,
       4,    86,    81,   131,   134,    64,    64,    64,    76,    64,
      64,    64,    64,    65,   128,   180,    70,   100,    77,   110,
     148,   109,    78,    79,    80,    66,    82,    83,    84,    85,
     153,     1,     2,     3,     4,     5,     6,     7,     8,     9,
     113,    61,   152,   105,   106,    90,    91,   110,    89,   114,
      94,   119,   110,    95,    92,    96,   126,   127,   107,   108,
      66,   111,   130,   123,    22,   110,   101,   102,    94,   169,
     117,    98,   124,    99,   157,   135,   156,   110,   137,   136,
     158,   110,   138,   120,   160,   159,   110,    64,    64,    64,
      64,    64,    64,    64,    64,    64,   174,   161,   118,   110,
     114,   110,   125,   112,   139,   140,    72,   143,   144,   145,
     146,   103,   104,    90,    91,   141,   142,   129,   149,   150,
     164,   155,   162,   172,   173,   175,   165,   179,   176,   182,
     167,   181,    62,   163,    63,   166,   147,    68,   154,   151,
     177,    59,     0,     0,     0,     0,     0,   178,     0,     0,
       0,     0,     0,     0,     0,    68,   183,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,     0,    15,    16,    17,    18,     0,     0,     0,    19,
       0,     0,     0,    20,    21,     0,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,     0,    23,    24,    25,
      26,     0,     0,     0,     0,     0,    27,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    61,    12,    13,
      14,     0,    15,    16,    17,    18,     0,     0,     0,    19,
       0,     0,     0,    20,    21,     0,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,     0,    23,    24,    25,
      26,     0,     0,     0,     0,     0,    27,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    61,     0,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,     0,    20,    21,     0,     0,     0,     0,     0,
      22,   132,     0,     0,     0,     0,     0,    23,    24,    25,
      26,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    61,     0,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,    20,    21,     0,
       0,     0,     0,     0,    22,     0,     0,     0,     0,     0,
       0,    23,    24,    25,    26
};

static const yytype_int16 yycheck[] =
{
      16,    59,    12,    36,    11,     6,    10,   157,    15,    13,
       6,    27,    22,    93,    94,    19,    20,    21,    36,    23,
      24,    25,    26,    10,    37,   175,    13,    39,    36,    42,
     110,    31,    19,    20,    21,    36,    23,    24,    25,    26,
     120,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      62,    13,    37,    34,    35,    29,    30,    42,     0,    66,
      36,    71,    42,    39,    38,    41,    76,    77,    49,    50,
      36,    51,    88,    42,    36,    42,    47,    48,    36,   159,
      36,    39,    51,    41,    51,    95,    37,    42,    98,    96,
      37,    42,    99,    38,    40,    42,    42,   101,   102,   103,
     104,   105,   106,   107,   108,   109,    37,    40,    51,    42,
     117,    42,    20,   171,   101,   102,   123,   105,   106,   107,
     108,    43,    44,    29,    30,   103,   104,    53,    37,    42,
      37,    36,    52,    52,    17,    51,   152,    51,    53,    37,
     156,    53,     9,   150,     9,   155,   109,   157,   123,   117,
     172,     0,    -1,    -1,    -1,    -1,    -1,   173,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,   182,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    18,    19,    20,    21,    25,
      29,    30,    36,    43,    44,    45,    46,    52,    55,    56,
      57,    58,    59,    60,    61,    62,    64,    65,    66,    67,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      81,    82,    83,    84,    85,    86,    89,    94,    95,    99,
     100,    13,    65,    66,    64,    71,    36,    56,    79,    80,
      71,    36,    56,    90,    91,    81,    36,    36,    71,    71,
      71,    79,    71,    71,    71,    71,    81,    87,    88,     0,
      29,    30,    38,    63,    36,    39,    41,    68,    39,    41,
      68,    47,    48,    43,    44,    34,    35,    49,    50,    31,
      42,    51,   100,    68,    56,    96,    97,    36,    51,    79,
      38,    92,    93,    42,    51,    20,    79,    79,    37,    53,
      81,    78,    37,    69,    78,    79,    56,    79,    56,    71,
      71,    72,    72,    73,    73,    73,    73,    75,    78,    37,
      42,    96,    37,    78,    91,    36,    37,    51,    37,    42,
      40,    40,    52,    56,    37,    81,    79,    81,    80,    78,
      98,    99,    52,    17,    37,    51,    53,    98,    81,    51,
      80,    53,    37,    81
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 128 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.elem_list) = (yyvsp[(1) - (1)].elem_list); g_program = (yyvsp[(1) - (1)].elem_list) ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 140 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_NullExp() ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 143 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BoolExp(true) ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 144 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BoolExp(false) ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 147 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_Int32Exp((yyvsp[(1) - (1)].int_literal)) ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 148 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = new Float64Exp((yyvsp[(1) - (1)].float64_literal)) ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 158 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    {	(yyval.exp) = new A_StringExp((yyvsp[(1) - (1)].string_literal));	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 160 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_IdExp("this") ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 161 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    {	(yyval.exp) = A_IdExp((yyvsp[(1) - (1)].id))	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 165 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp) ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 168 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.int_literal) = '=' ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 177 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    {
						(yyval.exp) = new FunctionExp((yyvsp[(1) - (1)].fun))
					;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 181 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    {
						ASSERT(0)
					;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 185 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    {
						(yyval.exp) = new A_MemberExp((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].id))
					;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 188 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = new A_NewExp((yyvsp[(2) - (3)].exp), (yyvsp[(3) - (3)].exp_list)) ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 192 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('new', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 195 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = new A_CallExp((yyvsp[(1) - (2)].exp), (yyvsp[(2) - (2)].exp_list)) ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 196 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = new A_CallExp((yyvsp[(1) - (2)].exp), (yyvsp[(2) - (2)].exp_list)) ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 197 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { ASSERT(0) ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 198 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = new A_MemberExp((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].id)) ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 201 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp_list) = NULL ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 202 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp_list) = Reverse((yyvsp[(2) - (3)].exp_list)) ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 205 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp_list) = new A_ExpList((yyvsp[(1) - (1)].exp), NULL) ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 206 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp_list) = new A_ExpList((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].exp_list)) ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 210 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('_++', (yyvsp[(1) - (2)].exp)) ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 211 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('_--', (yyvsp[(1) - (2)].exp)) ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 215 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('dele', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 216 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('void', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 217 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('type', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 218 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('++', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 219 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('--', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 220 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('+', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 221 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('-', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 222 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('~', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 223 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_UnopExp('!', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 227 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('*', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 228 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('/', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 232 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('+', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 233 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('-', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 237 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('<', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 238 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('>', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 239 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('<=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 240 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('>=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 247 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp('||', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 250 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp) ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 254 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = A_BinopExp((yyvsp[(2) - (3)].int_literal), (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 261 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = NULL ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 289 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm) = new A_ExpStm((yyvsp[(1) - (2)].exp)) ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 292 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm) = new A_IfStm((yyvsp[(3) - (7)].exp), (yyvsp[(5) - (7)].stm), (yyvsp[(7) - (7)].stm)) ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 293 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm) = new A_IfStm((yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].stm), NULL) ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 299 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    {
							(yyval.stm) = new A_ForStm((yyvsp[(3) - (9)].exp), (yyvsp[(5) - (9)].exp), (yyvsp[(7) - (9)].exp), (yyvsp[(9) - (9)].stm));
						;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 309 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm) = new A_ReturnStm((yyvsp[(2) - (3)].exp)) ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 312 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm) = new A_CompoundStm((yyvsp[(2) - (3)].stm_list)) ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 315 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm_list) = NULL ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 319 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm_list) = new A_StmList((yyvsp[(1) - (1)].stm), NULL) ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 320 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm_list) = new A_StmList((yyvsp[(2) - (2)].stm), (yyvsp[(1) - (2)].stm_list)) ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 323 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.stm) = new A_VarStm((yyvsp[(2) - (3)].vardecl_list)) ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 326 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.vardecl_list) = new A_VarDeclList((yyvsp[(1) - (1)].vardecl), NULL) ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 327 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.vardecl_list) = new A_VarDeclList((yyvsp[(3) - (3)].vardecl), (yyvsp[(1) - (3)].vardecl_list)) ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 330 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.vardecl) = new A_VarDecl((yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 333 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = NULL ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 337 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp) ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 345 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.fun) = new A_Function((yyvsp[(2) - (8)].id), Reverse((yyvsp[(4) - (8)].id_list)), (yyvsp[(7) - (8)].elem_list)) ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 348 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.fun) = new A_Function(nullptr, Reverse((yyvsp[(3) - (7)].id_list)), (yyvsp[(6) - (7)].elem_list)) ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 351 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.id_list) = NULL ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 355 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.id_list) = new A_IdentifierList((yyvsp[(1) - (1)].id), NULL) ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 356 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.id_list) = new A_IdentifierList((yyvsp[(3) - (3)].id), (yyvsp[(1) - (3)].id_list)) ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 362 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.elem_list) = new A_ElemList((yyvsp[(1) - (1)].elem), NULL) ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 363 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.elem_list) = new A_ElemList((yyvsp[(2) - (2)].elem), (yyvsp[(1) - (2)].elem_list)) ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 366 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.elem) = A_StatementElem((yyvsp[(1) - (1)].stm)) ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 367 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"
    { (yyval.elem) = A_FunctionElem((yyvsp[(1) - (1)].fun)) ;}
    break;



/* Line 1455 of yacc.c  */
#line 2162 "ecmascript_parse.tab.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 370 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\EcmaScript\\ecmascript_parse.yy"


