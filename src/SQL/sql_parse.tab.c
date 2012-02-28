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
#define yyparse sql_parse
#define yylex   sql_lex
#define yyerror sql_error
#define yylval  sql_lval
#define yychar  sql_char
#define yydebug sql_debug
#define yynerrs sql_nerrs
#define yylloc sql_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRING_LITERAL = 258,
     INTEGER_LITERAL = 259,
     IDENTIFIER = 260,
     SELECT_KW = 261,
     DELETE_KW = 262,
     INSERT_KW = 263,
     ALTER_KW = 264,
     COLUMN_KW = 265,
     INTO_KW = 266,
     VALUES_KW = 267,
     GENERATED_KW = 268,
     ALWAYS_KW = 269,
     IDENTITY_KW = 270,
     INCREMENT_KW = 271,
     MAXVALUE_KW = 272,
     XMLEXISTS_KW = 273,
     VALID_KW = 274,
     NULL_KW = 275,
     IS_KW = 276,
     BY_KW = 277,
     NO_KW = 278,
     AS_KW = 279,
     UNDER_KW = 280,
     TYPE_KW = 281,
     DEFAULT_KW = 282,
     START_KW = 283,
     WITH_KW = 284,
     ADD_KW = 285,
     FROM_KW = 286,
     JOIN_KW = 287,
     INNER_KW = 288,
     OUTER_KW = 289,
     LEFT_KW = 290,
     RIGHT_KW = 291,
     FULL_KW = 292,
     ON_KW = 293,
     WHERE_KW = 294,
     TRUE_KW = 295,
     FALSE_KW = 296,
     UNKNOWN_KW = 297,
     OR_KW = 298,
     AND_KW = 299,
     MOD_KW = 300,
     NOT_KW = 301,
     CREATE_KW = 302,
     TABLE_KW = 303,
     SMALLINT_KW = 304,
     INTEGER_KW = 305,
     INT_KW = 306,
     BIGINT_KW = 307,
     CHAR_KW = 308,
     CHARACTER_KW = 309,
     VARYING_KW = 310,
     VARCHAR_KW = 311,
     XML_KW = 312,
     XMLDOCUMENT_KW = 313,
     LEQ = 314,
     GEQ = 315,
     EQUAL = 316,
     NOT_EQUAL = 317,
     predicate = 318
   };
#endif
#define STRING_LITERAL 258
#define INTEGER_LITERAL 259
#define IDENTIFIER 260
#define SELECT_KW 261
#define DELETE_KW 262
#define INSERT_KW 263
#define ALTER_KW 264
#define COLUMN_KW 265
#define INTO_KW 266
#define VALUES_KW 267
#define GENERATED_KW 268
#define ALWAYS_KW 269
#define IDENTITY_KW 270
#define INCREMENT_KW 271
#define MAXVALUE_KW 272
#define XMLEXISTS_KW 273
#define VALID_KW 274
#define NULL_KW 275
#define IS_KW 276
#define BY_KW 277
#define NO_KW 278
#define AS_KW 279
#define UNDER_KW 280
#define TYPE_KW 281
#define DEFAULT_KW 282
#define START_KW 283
#define WITH_KW 284
#define ADD_KW 285
#define FROM_KW 286
#define JOIN_KW 287
#define INNER_KW 288
#define OUTER_KW 289
#define LEFT_KW 290
#define RIGHT_KW 291
#define FULL_KW 292
#define ON_KW 293
#define WHERE_KW 294
#define TRUE_KW 295
#define FALSE_KW 296
#define UNKNOWN_KW 297
#define OR_KW 298
#define AND_KW 299
#define MOD_KW 300
#define NOT_KW 301
#define CREATE_KW 302
#define TABLE_KW 303
#define SMALLINT_KW 304
#define INTEGER_KW 305
#define INT_KW 306
#define BIGINT_KW 307
#define CHAR_KW 308
#define CHARACTER_KW 309
#define VARYING_KW 310
#define VARCHAR_KW 311
#define XML_KW 312
#define XMLDOCUMENT_KW 313
#define LEQ 314
#define GEQ 315
#define EQUAL 316
#define NOT_EQUAL 317
#define predicate 318




/* Copy the first part of user declarations.  */
#line 1 "c:\\mmstudio\\src\\SQL\\sql_parse.y"


#define YYERROR_VERBOSE

int sql_lex();
void sql_error (/*YYLTYPE *llocp,*/ char const *s);

void parse_xpath();

extern Stm* g_stm;



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
#line 17 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
typedef union YYSTYPE {
int num;
char* id;
char* string_literal;
Exp* exp;
ExpList* explist;
Stm* stm;
IdList* idlist;
TableElementList* table_element_list;
ColumnDef* column_def;
DataType* data_type;
FromConstructor* from_constructor;
Identity* identity;
SequenceGeneratorOptionList* seq_gen_options;
SequenceGeneratorOption* seq_gen_option;
AlterTableAction* alter_table_action;
QualifiedName* qname;
XMLTypeModifier* XML_type_modifier;
PrimaryXMLTypeModifier primary_XML_type_modifier;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 244 "c:\\mmstudio\\src\\SQL\\sql_parse.tab.c"
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
#line 268 "c:\\mmstudio\\src\\SQL\\sql_parse.tab.c"

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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   234

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  99
/* YYNRULES -- Number of rules. */
#define YYNRULES  163
/* YYNRULES -- Number of states. */
#define YYNSTATES  261

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      65,    66,    70,    68,    67,    69,    64,    71,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    25,    27,    31,    32,    34,    37,    38,    40,    43,
      45,    49,    51,    55,    57,    60,    65,    69,    70,    72,
      77,    81,    83,    87,    89,    93,    94,    96,    98,   100,
     106,   107,   109,   113,   115,   118,   120,   122,   124,   128,
     132,   135,   138,   140,   142,   144,   146,   148,   150,   155,
     157,   162,   164,   166,   171,   176,   182,   188,   193,   195,
     197,   199,   201,   206,   211,   214,   216,   220,   222,   224,
     226,   228,   230,   232,   236,   238,   240,   242,   244,   246,
     250,   254,   256,   260,   264,   266,   269,   272,   274,   276,
     278,   280,   282,   284,   286,   288,   290,   294,   300,   305,
     308,   310,   314,   315,   318,   320,   324,   326,   328,   330,
     332,   338,   340,   343,   346,   349,   350,   352,   354,   357,
     359,   362,   364,   368,   370,   374,   376,   379,   381,   386,
     388,   390,   392,   394,   396,   398,   400,   404,   408,   409,
     411,   413,   415,   417,   419,   420,   422,   427,   428,   430,
     431,   436,   438,   440
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      73,     0,    -1,    74,    -1,   135,    -1,   113,    -1,   136,
      -1,    89,    -1,    86,    -1,    76,    -1,     5,    -1,    47,
      26,    77,    78,    80,    -1,    75,    -1,    77,    64,    75,
      -1,    -1,    79,    -1,    25,    77,    -1,    -1,    81,    -1,
      24,    82,    -1,   106,    -1,    65,    83,    66,    -1,    84,
      -1,    83,    67,    84,    -1,    85,    -1,    75,   105,    -1,
       9,    48,    75,    87,    -1,    30,    88,    93,    -1,    -1,
      10,    -1,    47,    48,    75,    90,    -1,    65,    91,    66,
      -1,    92,    -1,    91,    67,    92,    -1,    93,    -1,    75,
     105,    94,    -1,    -1,    95,    -1,   104,    -1,    96,    -1,
      13,    14,    24,    15,    97,    -1,    -1,    98,    -1,    65,
      99,    66,    -1,   100,    -1,    99,   100,    -1,   101,    -1,
     102,    -1,   103,    -1,    28,    29,     4,    -1,    16,    22,
       4,    -1,    17,     4,    -1,    23,    17,    -1,    27,    -1,
     106,    -1,   111,    -1,   112,    -1,   107,    -1,    57,    -1,
      57,    65,   108,    66,    -1,   109,    -1,   109,    65,   110,
      66,    -1,     5,    -1,     5,    -1,    53,    65,     4,    66,
      -1,    54,    65,     4,    66,    -1,    53,    55,    65,     4,
      66,    -1,    54,    55,    65,     4,    66,    -1,    56,    65,
       4,    66,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,     8,    11,    75,   114,    -1,    65,   134,    66,   115,
      -1,    12,   116,    -1,   117,    -1,   116,    67,   117,    -1,
     118,    -1,   119,    -1,   128,    -1,   123,    -1,   121,    -1,
     128,    -1,    65,   122,    66,    -1,   123,    -1,   151,    -1,
     124,    -1,   169,    -1,   125,    -1,   124,    68,   125,    -1,
     124,    69,   125,    -1,   126,    -1,   125,    70,   126,    -1,
     125,    71,   126,    -1,   127,    -1,    69,   127,    -1,    68,
     127,    -1,   120,    -1,   129,    -1,   130,    -1,   132,    -1,
     131,    -1,   133,    -1,     4,    -1,     3,    -1,    75,    -1,
     134,    67,    75,    -1,     6,   138,    31,   140,   159,    -1,
       7,    31,    75,   159,    -1,    75,   139,    -1,   137,    -1,
     138,    67,   137,    -1,    -1,    24,    75,    -1,   141,    -1,
     140,    67,   141,    -1,   142,    -1,   143,    -1,    75,    -1,
     144,    -1,   141,   145,    32,   141,   147,    -1,    33,    -1,
      35,   146,    -1,    36,   146,    -1,    37,   146,    -1,    -1,
      34,    -1,   148,    -1,    38,   149,    -1,   151,    -1,    39,
     149,    -1,   152,    -1,   151,    43,   152,    -1,   153,    -1,
     152,    44,   153,    -1,   154,    -1,    46,   154,    -1,   156,
      -1,   156,    21,   163,   155,    -1,    40,    -1,    41,    -1,
      42,    -1,   157,    -1,   160,    -1,   158,    -1,   128,    -1,
     157,   161,   162,    -1,    65,   151,    66,    -1,    -1,   150,
      -1,   164,    -1,    61,    -1,    62,    -1,   128,    -1,    -1,
      46,    -1,    18,    65,   165,    66,    -1,    -1,   167,    -1,
      -1,    58,    65,   168,    66,    -1,   170,    -1,   120,    -1,
     166,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   184,   184,   187,   188,   189,   190,   191,   192,   195,
     198,   207,   208,   220,   221,   224,   227,   228,   231,   234,
     235,   238,   239,   242,   245,   248,   251,   254,   255,   258,
     265,   268,   269,   272,   275,   280,   281,   284,   285,   289,
     294,   295,   298,   301,   302,   305,   306,   307,   310,   314,
     318,   319,   322,   325,   328,   329,   330,   333,   334,   337,
     338,   341,   360,   367,   368,   369,   370,   371,   374,   375,
     376,   377,   380,   383,   386,   389,   390,   393,   394,   397,
     400,   404,   405,   408,   411,   412,   417,   419,   422,   423,
     424,   427,   428,   429,   432,   433,   434,   437,   441,   444,
     447,   448,   451,   454,   457,   460,   461,   464,   472,   480,
     483,   484,   487,   488,   491,   492,   495,   496,   499,   502,
     505,   508,   509,   510,   511,   514,   515,   518,   522,   525,
     576,   579,   580,   583,   584,   587,   588,   591,   592,   595,
     596,   597,   601,   602,   605,   606,   609,   614,   617,   618,
     645,   656,   657,   667,   686,   687,   690,   697,   700,   703,
     703,   707,   710,   711
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING_LITERAL", "INTEGER_LITERAL", 
  "IDENTIFIER", "SELECT_KW", "DELETE_KW", "INSERT_KW", "ALTER_KW", 
  "COLUMN_KW", "INTO_KW", "VALUES_KW", "GENERATED_KW", "ALWAYS_KW", 
  "IDENTITY_KW", "INCREMENT_KW", "MAXVALUE_KW", "XMLEXISTS_KW", 
  "VALID_KW", "NULL_KW", "IS_KW", "BY_KW", "NO_KW", "AS_KW", "UNDER_KW", 
  "TYPE_KW", "DEFAULT_KW", "START_KW", "WITH_KW", "ADD_KW", "FROM_KW", 
  "JOIN_KW", "INNER_KW", "OUTER_KW", "LEFT_KW", "RIGHT_KW", "FULL_KW", 
  "ON_KW", "WHERE_KW", "TRUE_KW", "FALSE_KW", "UNKNOWN_KW", "OR_KW", 
  "AND_KW", "MOD_KW", "NOT_KW", "CREATE_KW", "TABLE_KW", "SMALLINT_KW", 
  "INTEGER_KW", "INT_KW", "BIGINT_KW", "CHAR_KW", "CHARACTER_KW", 
  "VARYING_KW", "VARCHAR_KW", "XML_KW", "XMLDOCUMENT_KW", "LEQ", "GEQ", 
  "EQUAL", "NOT_EQUAL", "predicate", "'.'", "'('", "')'", "','", "'+'", 
  "'-'", "'*'", "'/'", "$accept", "stm", "statement", "identifier", 
  "user_defined_type_definition", "user_defined_type_name", 
  "subtype_clause_opt", "subtype_clause", "as_representation_opt", 
  "as_representation", "representation", "member_list", "member", 
  "attribute_definition", "alter_table_statement", "alter_table_action", 
  "COLUMN_opt", "table_definition", "table_contents_source", 
  "table_element_list", "table_element", "column_definition", 
  "column_definition_clause_opt", "column_definition_clause", 
  "identity_column_specification", "sequence_generator_options_opt", 
  "sequence_generator_options", "common_sequence_generator_options", 
  "common_sequence_generator_option", 
  "sequence_generator_start_with_option", 
  "sequence_generator_increment_by_option", 
  "sequence_generator_maxvalue_option", "default_clause", "data_type", 
  "predefined_type", "XML_type", "XML_type_modifier", 
  "primary_XML_type_modifier", "secondary_XML_type_modifier", 
  "character_string_type", "exact_numeric_type", "insert_statement", 
  "from_constructor", "contextually_typed_table_value_constructor", 
  "contextually_typed_row_value_expression_list", 
  "contextually_typed_row_value_expression", "row_value_special_case", 
  "contextually_typed_row_value_constructor", "value_expression_primary", 
  "parenthesized_value_expression", "value_expression", 
  "common_value_expression", "numeric_value_expression", "term", "factor", 
  "numeric_primary", "nonparenthesized_value_expression_primary", 
  "unsigned_value_specification", "unsigned_literal", "general_literal", 
  "unsigned_numeric_literal", "character_string_literal", 
  "column_name_list", "select_statement", "delete_statement", 
  "select_item", "select_item_seq", "as_opt", "table_reference_seq", 
  "table_reference", "table_factor", "joined_table", "qualified_join", 
  "join_type", "OUTER_opt", "join_specification", "join_condition", 
  "search_condition", "where_criteria", "boolean_value_expression", 
  "boolean_term", "boolean_factor", "boolean_test", "truth_value", 
  "boolean_primary", "boolean_predicand", 
  "parenthesized_boolean_value_expression", "where_criteria_opt", 
  "XML_predicate", "comp_op", "row_value_predicand", "NOT_opt", 
  "XML_exists_predicate", "XQuery_expression", "XML_value_function", 
  "XML_document", "@1", "XML_value_expression", "XML_primary", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,    46,    40,    41,    44,    43,    45,
      42,    47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    72,    73,    74,    74,    74,    74,    74,    74,    75,
      76,    77,    77,    78,    78,    79,    80,    80,    81,    82,
      82,    83,    83,    84,    85,    86,    87,    88,    88,    89,
      90,    91,    91,    92,    93,    94,    94,    95,    95,    96,
      97,    97,    98,    99,    99,   100,   100,   100,   101,   102,
     103,   103,   104,   105,   106,   106,   106,   107,   107,   108,
     108,   109,   110,   111,   111,   111,   111,   111,   112,   112,
     112,   112,   113,   114,   115,   116,   116,   117,   117,   118,
     119,   120,   120,   121,   122,   122,   123,   123,   124,   124,
     124,   125,   125,   125,   126,   126,   126,   127,   128,   129,
     130,   130,   131,   132,   133,   134,   134,   135,   136,   137,
     138,   138,   139,   139,   140,   140,   141,   141,   142,   143,
     144,   145,   145,   145,   145,   146,   146,   147,   148,   149,
     150,   151,   151,   152,   152,   153,   153,   154,   154,   155,
     155,   155,   156,   156,   157,   157,   157,   158,   159,   159,
     160,   161,   161,   162,   163,   163,   164,   165,   166,   168,
     167,   169,   170,   170
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     0,     1,     2,     0,     1,     2,     1,
       3,     1,     3,     1,     2,     4,     3,     0,     1,     4,
       3,     1,     3,     1,     3,     0,     1,     1,     1,     5,
       0,     1,     3,     1,     2,     1,     1,     1,     3,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     4,     1,
       4,     1,     1,     4,     4,     5,     5,     4,     1,     1,
       1,     1,     4,     4,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     3,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     4,     2,
       1,     3,     0,     2,     1,     3,     1,     1,     1,     1,
       5,     1,     2,     2,     2,     0,     1,     1,     2,     1,
       2,     1,     3,     1,     3,     1,     2,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     0,     1,
       1,     1,     1,     1,     0,     1,     4,     0,     1,     0,
       4,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     2,     8,     7,
       6,     4,     3,     5,     9,   112,   110,     0,     0,     0,
       0,     0,     0,     1,     0,   109,     0,     0,   148,     0,
       0,    11,    13,     0,   113,   118,   148,   114,   116,   117,
     119,   111,     0,   149,   108,     0,    72,    27,    25,     0,
       0,    16,    14,     0,    29,     0,   107,   121,   125,   125,
     125,     0,   104,   103,     0,     0,     0,   145,    98,    99,
     101,   100,   102,   130,   129,   131,   133,   135,   137,   142,
     144,   143,   150,   105,     0,    28,     0,    15,    12,     0,
      10,    17,     0,     0,    31,    33,   115,   126,   122,   123,
     124,     0,   157,   136,     0,     0,     0,   154,   151,   152,
       0,     0,     0,    26,    68,    69,    70,    71,     0,     0,
       0,    57,     0,    18,    19,    56,    54,    55,    35,    53,
      30,     0,     0,     0,   147,   132,   134,   155,     0,   153,
     146,     0,    73,   106,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    23,     0,    52,    34,    36,    38,    37,
      32,     0,   120,   127,   156,   139,   140,   141,   138,     0,
       0,     0,     0,    74,    75,    77,    78,    97,    81,    80,
      86,    88,    91,    94,    82,   163,   158,    87,   161,     0,
       0,     0,     0,     0,    61,     0,    59,    24,    20,     0,
       0,   128,   159,     0,     0,    84,    82,    85,    97,    96,
      82,    95,     0,     0,     0,     0,     0,     0,    63,     0,
      64,    67,    58,     0,    22,     0,     0,     0,    83,    76,
      89,    90,    92,    93,    65,    66,    62,     0,    40,   160,
      60,     0,    39,    41,     0,     0,     0,     0,     0,    43,
      45,    46,    47,     0,    50,    51,     0,    42,    44,    49,
      48
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     6,     7,    35,     8,    32,    51,    52,    90,    91,
     123,   151,   152,   153,     9,    48,    86,    10,    54,    93,
      94,    95,   156,   157,   158,   242,   243,   248,   249,   250,
     251,   252,   159,   128,   129,   125,   195,   196,   237,   126,
     127,    11,    46,   142,   173,   174,   175,   176,   208,   178,
     204,   179,   180,   181,   182,   183,    67,    68,    69,    70,
      71,    72,    84,    12,    13,    16,    17,    25,    36,    37,
      38,    39,    40,    61,    98,   162,   163,    73,    43,    74,
      75,    76,    77,   168,    78,    79,    80,    44,    81,   110,
     140,   138,    82,   133,   185,   186,   226,   187,   188
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -149
static const short yypact[] =
{
      53,     1,    19,    43,    34,    45,    87,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,    75,  -149,   -24,     1,     1,
       1,     1,     1,  -149,     1,  -149,     1,     1,    73,    60,
     104,  -149,   -22,    80,  -149,  -149,   -10,   100,  -149,  -149,
    -149,  -149,     7,  -149,  -149,     1,  -149,   144,  -149,     1,
       1,   134,  -149,     1,  -149,     1,  -149,  -149,   129,   129,
     129,   138,  -149,  -149,   106,    27,     7,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,   130,   128,  -149,  -149,   153,    40,
    -149,  -149,  -149,  -149,    37,  -149,     1,   111,  -149,    90,
    -149,  -149,    66,    82,  -149,  -149,   100,  -149,  -149,  -149,
    -149,     1,  -149,  -149,   -19,     7,     7,   131,  -149,  -149,
     147,   164,     1,  -149,  -149,  -149,  -149,  -149,    31,    33,
     113,   114,     1,  -149,  -149,  -149,  -149,  -149,    14,  -149,
    -149,     1,    91,   115,  -149,   128,  -149,  -149,    -4,  -149,
    -149,     5,  -149,  -149,   117,   176,   118,   180,   181,   182,
      66,    86,  -149,  -149,   172,  -149,  -149,  -149,  -149,  -149,
    -149,     7,  -149,  -149,  -149,  -149,  -149,  -149,  -149,   123,
      10,    29,    29,   122,  -149,  -149,  -149,  -149,  -149,  -149,
      88,    89,  -149,  -149,     2,  -149,  -149,  -149,  -149,   186,
     125,   188,   127,   133,  -149,   135,   132,  -149,  -149,     1,
     170,  -149,  -149,    10,   136,  -149,    70,   130,  -149,  -149,
    -149,  -149,     5,    12,    12,    12,    12,   137,  -149,   139,
    -149,  -149,  -149,   190,  -149,   185,   140,   -19,  -149,  -149,
      89,    89,  -149,  -149,  -149,  -149,  -149,   141,   143,  -149,
    -149,    67,  -149,  -149,   174,   200,   192,   183,    23,  -149,
    -149,  -149,  -149,   206,  -149,  -149,   207,  -149,  -149,  -149,
    -149
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -149,  -149,  -149,    -1,  -149,   165,  -149,  -149,  -149,  -149,
    -149,  -149,    16,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
      85,   142,  -149,  -149,  -149,  -149,  -149,  -149,   -35,  -149,
    -149,  -149,  -149,    68,   145,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,     8,  -149,  -149,  -136,  -149,
    -149,  -148,  -149,   -52,   -51,    -5,  -106,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,   194,  -149,  -149,  -149,   -43,
    -149,  -149,  -149,  -149,   109,  -149,  -149,    56,  -149,   -65,
     119,   116,   154,  -149,  -149,  -149,  -149,   187,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -146
static const short yytable[] =
{
      15,   104,   -79,    49,   139,   177,    14,    26,    62,    63,
      62,    63,    96,    62,    63,    62,    63,    28,    29,    30,
      31,    33,   205,    34,   105,    64,    15,   154,    64,    42,
      62,    63,    62,    63,   177,   184,   165,   166,   167,   244,
     245,   155,    50,    27,    83,    64,   246,   134,    31,    88,
      18,   247,    92,    65,    19,   205,    65,    55,   132,     1,
       2,     3,     4,   169,   206,   210,   210,   177,   169,   -79,
     170,    21,    66,   171,   172,   203,   177,   170,   171,   172,
     171,   172,    20,   244,   245,    92,   144,    23,   146,   257,
     246,  -145,    66,    22,   170,   247,   145,   206,   147,    24,
       5,   108,   109,   111,   112,   207,   184,   210,   210,   210,
     210,   143,    42,  -145,  -145,   114,   115,   116,   117,   118,
     119,   150,   120,   121,    57,    45,    58,    59,    60,   161,
      92,  -145,  -145,    57,    47,    58,    59,    60,   227,   114,
     115,   116,   117,   118,   119,    53,   120,   121,   130,   131,
      62,    63,   198,   199,    85,   122,   213,   214,    89,   215,
     216,   230,   231,    97,   232,   233,   209,   211,    99,   100,
     101,   102,   106,   105,   107,    50,   141,   137,   148,   149,
     190,   164,   189,   191,   192,   193,   200,   194,   202,   212,
     217,   218,   219,   220,   225,   236,   253,   223,   150,   221,
     238,   222,   228,   234,   254,   235,   239,   240,   241,   255,
     259,   260,   256,   258,    87,   224,   160,   201,   197,   103,
     229,    41,   136,    56,   135,     0,     0,     0,   113,     0,
       0,     0,     0,     0,   124
};

static const short yycheck[] =
{
       1,    66,     0,    25,   110,   141,     5,    31,     3,     4,
       3,     4,    55,     3,     4,     3,     4,    18,    19,    20,
      21,    22,   170,    24,    43,    18,    27,    13,    18,    39,
       3,     4,     3,     4,   170,   141,    40,    41,    42,    16,
      17,    27,    64,    67,    45,    18,    23,    66,    49,    50,
      31,    28,    53,    46,    11,   203,    46,    67,   101,     6,
       7,     8,     9,    58,   170,   171,   172,   203,    58,    67,
      65,    26,    65,    68,    69,    65,   212,    65,    68,    69,
      68,    69,    48,    16,    17,    86,    55,     0,    55,    66,
      23,    21,    65,    48,    65,    28,    65,   203,    65,    24,
      47,    61,    62,    66,    67,   170,   212,   213,   214,   215,
     216,   112,    39,    43,    44,    49,    50,    51,    52,    53,
      54,   122,    56,    57,    33,    65,    35,    36,    37,    38,
     131,    61,    62,    33,    30,    35,    36,    37,   203,    49,
      50,    51,    52,    53,    54,    65,    56,    57,    66,    67,
       3,     4,    66,    67,    10,    65,    68,    69,    24,    70,
      71,   213,   214,    34,   215,   216,   171,   172,    59,    60,
      32,    65,    44,    43,    21,    64,    12,    46,    65,    65,
       4,    66,    65,    65,     4,     4,    14,     5,    65,    67,
       4,    66,     4,    66,    24,     5,    22,    65,   199,    66,
      15,    66,    66,    66,     4,    66,    66,    66,    65,    17,
       4,     4,    29,   248,    49,   199,   131,   161,   150,    65,
     212,    27,   106,    36,   105,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    89
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     6,     7,     8,     9,    47,    73,    74,    76,    86,
      89,   113,   135,   136,     5,    75,   137,   138,    31,    11,
      48,    26,    48,     0,    24,   139,    31,    67,    75,    75,
      75,    75,    77,    75,    75,    75,   140,   141,   142,   143,
     144,   137,    39,   150,   159,    65,   114,    30,    87,    25,
      64,    78,    79,    65,    90,    67,   159,    33,    35,    36,
      37,   145,     3,     4,    18,    46,    65,   128,   129,   130,
     131,   132,   133,   149,   151,   152,   153,   154,   156,   157,
     158,   160,   164,    75,   134,    10,    88,    77,    75,    24,
      80,    81,    75,    91,    92,    93,   141,    34,   146,   146,
     146,    32,    65,   154,   151,    43,    44,    21,    61,    62,
     161,    66,    67,    93,    49,    50,    51,    52,    53,    54,
      56,    57,    65,    82,   106,   107,   111,   112,   105,   106,
      66,    67,   141,   165,    66,   152,   153,    46,   163,   128,
     162,    12,   115,    75,    55,    65,    55,    65,    65,    65,
      75,    83,    84,    85,    13,    27,    94,    95,    96,   104,
      92,    38,   147,   148,    66,    40,    41,    42,   155,    58,
      65,    68,    69,   116,   117,   118,   119,   120,   121,   123,
     124,   125,   126,   127,   128,   166,   167,   169,   170,    65,
       4,    65,     4,     4,     5,   108,   109,   105,    66,    67,
      14,   149,    65,    65,   122,   123,   128,   151,   120,   127,
     128,   127,    67,    68,    69,    70,    71,     4,    66,     4,
      66,    66,    66,    65,    84,    24,   168,   151,    66,   117,
     125,   125,   126,   126,    66,    66,     5,   110,    15,    66,
      66,    65,    97,    98,    16,    17,    23,    28,    99,   100,
     101,   102,   103,    22,     4,    17,    29,    66,   100,     4,
       4
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
#line 184 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.stm = yyvsp[0].stm; g_stm = yyval.stm ;}
    break;

  case 10:
#line 202 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    {
									yyval.stm = new UserDefinedTypeDefStm(yyvsp[-2].qname, yyvsp[-1].qname)
								;}
    break;

  case 11:
#line 207 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.qname = new QualifiedName(NULL, yyvsp[0].id) ;}
    break;

  case 12:
#line 208 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.qname = new QualifiedName(yyvsp[-2].qname, yyvsp[0].id) ;}
    break;

  case 13:
#line 220 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.qname = NULL ;}
    break;

  case 15:
#line 224 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.qname = yyvsp[0].qname ;}
    break;

  case 25:
#line 248 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.stm = new AlterTableStm(yyvsp[-1].id, yyvsp[0].alter_table_action) ;}
    break;

  case 26:
#line 251 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.alter_table_action = new AddColumnAlterTableAction(yyvsp[0].column_def) ;}
    break;

  case 29:
#line 260 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    {
		yyval.stm = new TableDefStm(yyvsp[-1].id, yyvsp[0].table_element_list)
	;}
    break;

  case 30:
#line 265 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.table_element_list = Reverse(yyvsp[-1].table_element_list) ;}
    break;

  case 31:
#line 268 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.table_element_list = new TableElementList(yyvsp[0].column_def, NULL) ;}
    break;

  case 32:
#line 269 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.table_element_list = new TableElementList(yyvsp[0].column_def, yyvsp[-2].table_element_list) ;}
    break;

  case 34:
#line 277 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.column_def = new ColumnDef(yyvsp[-2].id, yyvsp[-1].data_type, yyvsp[0].identity) ;}
    break;

  case 35:
#line 280 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.identity = NULL ;}
    break;

  case 39:
#line 291 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.identity = new Identity(yyvsp[0].seq_gen_options) ;}
    break;

  case 40:
#line 294 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_options = NULL ;}
    break;

  case 42:
#line 298 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_options = yyvsp[-1].seq_gen_options ;}
    break;

  case 43:
#line 301 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_options = new SequenceGeneratorOptionList(yyvsp[0].seq_gen_option, NULL) ;}
    break;

  case 44:
#line 302 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_options = new SequenceGeneratorOptionList(yyvsp[0].seq_gen_option, yyvsp[-1].seq_gen_options) ;}
    break;

  case 48:
#line 311 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_option = new StartWithSequenceGeneratorOption(yyvsp[0].num) ;}
    break;

  case 49:
#line 315 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_option = new IncrementBySequenceGeneratorOption(yyvsp[0].num) ;}
    break;

  case 50:
#line 318 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_option = new MaxValueSequenceGeneratorOption(yyvsp[0].num) ;}
    break;

  case 51:
#line 319 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.seq_gen_option = new NoMaxValueSequenceGeneratorOption() ;}
    break;

  case 57:
#line 333 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new XMLDataType(NULL) ;}
    break;

  case 58:
#line 334 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new XMLDataType(yyvsp[-1].XML_type_modifier) ;}
    break;

  case 59:
#line 337 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.XML_type_modifier = new XMLTypeModifier(yyvsp[0].primary_XML_type_modifier) ;}
    break;

  case 60:
#line 338 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.XML_type_modifier = new XMLTypeModifier(yyvsp[-3].primary_XML_type_modifier) ;}
    break;

  case 61:
#line 348 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    {
										if (!stricmp(yyvsp[0].id, "DOCUMENT"))
											yyval.primary_XML_type_modifier = MODIFIER_DOCUMENT;
										else if (!stricmp(yyvsp[0].id, "CONTENT"))
											yyval.primary_XML_type_modifier = MODIFIER_CONTENT;
										else if (!stricmp(yyvsp[0].id, "SEQUENCE"))
											yyval.primary_XML_type_modifier = MODIFIER_SEQUENCE;
										else
											YYERROR;
									;}
    break;

  case 63:
#line 367 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new CharDataType(yyvsp[-1].num) ;}
    break;

  case 64:
#line 368 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new CharDataType(yyvsp[-1].num) ;}
    break;

  case 65:
#line 369 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new CharVaryingDataType(yyvsp[-1].num) ;}
    break;

  case 66:
#line 370 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new CharVaryingDataType(yyvsp[-1].num) ;}
    break;

  case 67:
#line 371 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new VarCharDataType(yyvsp[-1].num) ;}
    break;

  case 68:
#line 374 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new NumericDataType() ;}
    break;

  case 69:
#line 375 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new NumericDataType() ;}
    break;

  case 70:
#line 376 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new NumericDataType() ;}
    break;

  case 71:
#line 377 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.data_type = new NumericDataType() ;}
    break;

  case 72:
#line 380 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.stm = new InsertStm(yyvsp[-1].id, yyvsp[0].from_constructor) ;}
    break;

  case 73:
#line 383 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.from_constructor = new FromConstructor(Reverse(yyvsp[-2].idlist), Reverse(yyvsp[0].explist)) ;}
    break;

  case 74:
#line 386 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.explist = yyvsp[0].explist ;}
    break;

  case 75:
#line 389 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.explist = new ExpList(yyvsp[0].exp, NULL) ;}
    break;

  case 76:
#line 390 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.explist = new ExpList(yyvsp[0].exp, yyvsp[-2].explist) ;}
    break;

  case 103:
#line 454 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.exp = sql_A_Const(yyvsp[0].num) ;}
    break;

  case 104:
#line 457 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.exp = new CharLiteralExp(yyvsp[0].string_literal) ;}
    break;

  case 105:
#line 460 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.idlist = new IdList(yyvsp[0].id, NULL) ;}
    break;

  case 106:
#line 461 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.idlist = new IdList(yyvsp[0].id, yyvsp[-2].idlist) ;}
    break;

  case 107:
#line 467 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    {
						yyval.stm = new SelectStm(Reverse(yyvsp[-3].idlist), Reverse(yyvsp[-1].idlist), yyvsp[0].exp)
						;}
    break;

  case 108:
#line 475 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    {
						yyval.stm = new DeleteStm(yyvsp[-1].id, yyvsp[0].exp)
						;}
    break;

  case 110:
#line 483 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.idlist = new IdList(yyvsp[0].id, NULL) ;}
    break;

  case 111:
#line 484 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.idlist = new IdList(yyvsp[0].id, yyvsp[-2].idlist) ;}
    break;

  case 114:
#line 491 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.idlist = new IdList(yyvsp[0].id, NULL) ;}
    break;

  case 115:
#line 492 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.idlist = new IdList(yyvsp[0].id, yyvsp[-2].idlist) ;}
    break;

  case 130:
#line 576 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.exp = NULL/*$2*/ ;}
    break;

  case 148:
#line 617 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { yyval.exp = NULL ;}
    break;

  case 159:
#line 703 "c:\\mmstudio\\src\\SQL\\sql_parse.y"
    { parse_xpath() ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1742 "c:\\mmstudio\\src\\SQL\\sql_parse.tab.c"

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


#line 714 "c:\\mmstudio\\src\\SQL\\sql_parse.y"


