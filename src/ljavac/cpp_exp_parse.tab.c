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
#define yyparse cpp_exp_parse
#define yylex   cpp_exp_lex
#define yyerror cpp_exp_error
#define yylval  cpp_exp_lval
#define yychar  cpp_exp_char
#define yydebug cpp_exp_debug
#define yynerrs cpp_exp_nerrs
#define yylloc cpp_exp_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     identifier = 258,
     PLUSPLUS = 259,
     MINUSMINUS = 260,
     ARROW = 261,
     EXTERN_KW = 262,
     IF_KW = 263,
     ELSE_KW = 264,
     SWITCH_KW = 265,
     CASE_KW = 266,
     DEFAULT_KW = 267,
     GOTO_KW = 268,
     BREAK_KW = 269,
     CONTINUE_KW = 270,
     FOR_KW = 271,
     DO_KW = 272,
     WHILE_KW = 273,
     CONST_KW = 274,
     VOLATILE_KW = 275,
     TYPEDEF_KW = 276,
     TYPENAME_KW = 277,
     ENUM_KW = 278,
     CLASS_KW = 279,
     STRUCT_KW = 280,
     UNION_KW = 281,
     PRIVATE_KW = 282,
     PROTECTED_KW = 283,
     PUBLIC_KW = 284,
     AUTO_KW = 285,
     REGISTER_KW = 286,
     STATIC_KW = 287,
     MUTABLE_KW = 288,
     INLINE_KW = 289,
     VIRTUAL_KW = 290,
     EXPLICIT_KW = 291,
     FRIEND_KW = 292,
     FALSE_KW = 293,
     TRUE_KW = 294,
     STATIC_CAST_KW = 295,
     REINTERPRET_CAST_KW = 296,
     DYNAMIC_CAST_KW = 297,
     CONST_CAST_KW = 298,
     RETURN_KW = 299,
     TRY_KW = 300,
     THROW_KW = 301,
     CATCH_KW = 302,
     CHAR_KW = 303,
     WCHAR_T_KW = 304,
     BOOL_KW = 305,
     SHORT_KW = 306,
     INT_KW = 307,
     LONG_KW = 308,
     SIGNED_KW = 309,
     UNSIGNED_KW = 310,
     FLOAT_KW = 311,
     DOUBLE_KW = 312,
     VOID_KW = 313,
     __INT64_KW = 314,
     __CDECL_KW = 315,
     __STDCALL_KW = 316,
     __DECLSPEC_KW = 317,
     __ASM_KW = 318,
     __SAVEDS_KW = 319,
     __INTERRUPT_KW = 320,
     __CHIP_KW = 321,
     LSHIFT = 322,
     RSHIFT = 323,
     TWO_COLON = 324,
     THREE_DOTS = 325,
     NEW_KW = 326,
     DELETE_KW = 327,
     OPERATOR_KW = 328,
     SIZEOF_KW = 329,
     STRING_LITERAL = 330,
     LSTRING_LITERAL = 331,
     INTEGER_LITERAL = 332,
     THIS_KW = 333
   };
#endif
#define identifier 258
#define PLUSPLUS 259
#define MINUSMINUS 260
#define ARROW 261
#define EXTERN_KW 262
#define IF_KW 263
#define ELSE_KW 264
#define SWITCH_KW 265
#define CASE_KW 266
#define DEFAULT_KW 267
#define GOTO_KW 268
#define BREAK_KW 269
#define CONTINUE_KW 270
#define FOR_KW 271
#define DO_KW 272
#define WHILE_KW 273
#define CONST_KW 274
#define VOLATILE_KW 275
#define TYPEDEF_KW 276
#define TYPENAME_KW 277
#define ENUM_KW 278
#define CLASS_KW 279
#define STRUCT_KW 280
#define UNION_KW 281
#define PRIVATE_KW 282
#define PROTECTED_KW 283
#define PUBLIC_KW 284
#define AUTO_KW 285
#define REGISTER_KW 286
#define STATIC_KW 287
#define MUTABLE_KW 288
#define INLINE_KW 289
#define VIRTUAL_KW 290
#define EXPLICIT_KW 291
#define FRIEND_KW 292
#define FALSE_KW 293
#define TRUE_KW 294
#define STATIC_CAST_KW 295
#define REINTERPRET_CAST_KW 296
#define DYNAMIC_CAST_KW 297
#define CONST_CAST_KW 298
#define RETURN_KW 299
#define TRY_KW 300
#define THROW_KW 301
#define CATCH_KW 302
#define CHAR_KW 303
#define WCHAR_T_KW 304
#define BOOL_KW 305
#define SHORT_KW 306
#define INT_KW 307
#define LONG_KW 308
#define SIGNED_KW 309
#define UNSIGNED_KW 310
#define FLOAT_KW 311
#define DOUBLE_KW 312
#define VOID_KW 313
#define __INT64_KW 314
#define __CDECL_KW 315
#define __STDCALL_KW 316
#define __DECLSPEC_KW 317
#define __ASM_KW 318
#define __SAVEDS_KW 319
#define __INTERRUPT_KW 320
#define __CHIP_KW 321
#define LSHIFT 322
#define RSHIFT 323
#define TWO_COLON 324
#define THREE_DOTS 325
#define NEW_KW 326
#define DELETE_KW 327
#define OPERATOR_KW 328
#define SIZEOF_KW 329
#define STRING_LITERAL 330
#define LSTRING_LITERAL 331
#define INTEGER_LITERAL 332
#define THIS_KW 333




/* Copy the first part of user declarations.  */
#line 1 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"


//struct PP_TokenList;

//extern PP_TokenList* tlist;

//extern PP::CPreprocessor* pPP2;
extern kwmap kwm;

extern A_Exp* g_exp;

//BOOL bLastTok = FALSE;

int GetString(int delimiter, bool bWide/*, CToken& token*/);
#if 0
{
	int line = pPP2->m_pFile->m_line;

	std::string str;

	int c2;
	while (!pPP2->_eof())
	{
		//PP::CToken* ptok = pPP->GetToken4();
		c2 = pPP2->_getc();

		if (c2 == '\\')
		{
			int c3 = pPP2->_getc();
			if (c3 == '\\')
			{
				c2 = '\\';
			}
			else if (c3 == 'n')
			{
				c2 = '\n';
			}
			else if (c3 == 'r')
			{
				c2 = '\r';
			}
			else if (c3 == 't')
			{
				c2 = '\t';
			}
			else if (c3 == '?')
			{
				c2 = '\?';
			}
			else if (c3 == '\'')
			{
				c2 = '\'';
			}
			else if (c3 == '0')
			{
				c2 = '\0';
			}
			else
			{
				printf("Unrecognized string sequence\n");
			}
		}
		else if (c2 == delimiter)
		{
		//	ungetc(c2, fpin);
			break;
		}
		str += c2;
	}

	if (c2 != delimiter)
	{
		char msg[256];
		sprintf(msg, "expected end of string, started on line(%d)", line);
		printf(msg);
	}

/*
	if (bWide)
	{
		token.type = CToken::tok_wstring;
	}
	else
	{
		token.type = CToken::tok_string;
	}
	*/

//	token.stringlen = str.length();
	cpp_lval.string_literal = strdup(str.c_str());

//	*curtok = token;

	return STRING_LITERAL;
}
#endif

int cpp_exp_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/);

#if 0
static int cpp_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/)
{
	if (!bLastTok)
		pPP2->GetToken();
	else
		bLastTok = FALSE;

	while (pPP2->curtokpp->type == PP::CToken::tok_space ||
		(pPP2->curtokpp->type == PP::CToken::tok_symbol && pPP2->curtokpp->symbol == '\n'))
	{
		pPP2->GetToken();
	}

	if (pPP2->curtokpp->type == PP::CToken::tok_ident)
	{
	//	kwmap::iterator i = kwm.find(pPP2->curtokpp->ident);
	//	if (i != kwm.end())
	//		return (*i).second;
		int kw;
		if (kwm.Lookup(ckw(pPP2->curtokpp->ident), kw))
			return kw;

	#if 0
		if (!strcmp(pPP2->curtokpp->ident, "void"))
		{
			return VOID_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "char"))
		{
			return CHAR_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "int"))
		{
			return INT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "float"))
		{
			return FLOAT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "double"))
		{
			return DOUBLE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "short"))
		{
			return SHORT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "long"))
		{
			return LONG_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__int64"))
		{
			return __INT64_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "signed"))
		{
			return SIGNED_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "unsigned"))
		{
			return UNSIGNED_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "const"))
		{
			return CONST_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "volatile"))
		{
			return VOLATILE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "extern"))
		{
			return EXTERN_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "static"))
		{
			return STATIC_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "auto"))
		{
			return AUTO_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "register"))
		{
			return REGISTER_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "enum"))
		{
			return ENUM_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "class"))
		{
			return CLASS_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "struct"))
		{
			return STRUCT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "union"))
		{
			return UNION_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "typedef"))
		{
			return TYPEDEF_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "inline"))
		{
			return INLINE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "virtual"))
		{
			return VIRTUAL_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__cdecl"))
		{
			return __CDECL_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__stdcall"))
		{
			return __STDCALL_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__declspec"))
		{
			return __DECLSPEC_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__asm"))
		{
			return __ASM_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "if"))
		{
			return IF_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "else"))
		{
			return ELSE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "while"))
		{
			return WHILE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "typename"))
		{
			return TYPENAME_KW;
		}
		#endif
		else
		{
			cpp_lval.id = pPP2->curtokpp->ident;
			return identifier;
		}
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_integer)
	{
		cpp_lval.num = pPP2->curtokpp->int32;
		return INTEGER_LITERAL;
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_char ||
				pPP2->curtokpp->type == PP::CToken::tok_symbol)
	{
		int c = pPP2->curtokpp->symbol;

		if (c == '\'')
		{
			ASSERT(0);
		//	return GetCharacter(c, FALSE, token);
		}
		else if (c == '\"')
		{
			return GetString(c, FALSE/*, token*/);
		}
		else if (pPP2->curtokpp->symbol == '<<')
		{
			return LSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '>>')
		{
			return RSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '...')
		{
			return THREE_DOTS;
		}
		else
		{
		//	ASSERT(pPP2->curtokpp->symbol < 256);
			return pPP2->curtokpp->symbol;
		}
	}
	else
		ASSERT(0);

#if 0
	if (tlist == NULL)
		return -1;

   while (tlist->head.kind == ' ')
		tlist = tlist->tail;

	PP_Token& pptok = tlist->head;
	tlist = tlist->tail;

	cpp_lloc.first_line = pptok.line_pos;

	if (pptok.kind == PP_Token::PP_CHAR)
	{
		return pptok.c;
	}
	else if (pptok.kind == PP_Token::PP_INT32)
	{
		cpp_lval.num = pptok.int32;
		return INTEGER_LITERAL;
	}
	else if (pptok.kind == PP_Token::PP_IDENTIFIER)
	{
		if (!strcmp(pptok.id, "void"))
		{
			return VOID_KW;
		}
		else if (!strcmp(pptok.id, "int"))
		{
			return INT_KW;
		}
		else if (!strcmp(pptok.id, "long"))
		{
			return LONG_KW;
		}
		else if (!strcmp(pptok.id, "if"))
		{
			return IF_KW;
		}
		else if (!strcmp(pptok.id, "else"))
		{
			return ELSE_KW;
		}
		else
		{
			cpp_lval.id = pptok.id;
			return identifier;
		}
	}
	else
		ASSERT(0);
#endif

	return -1;
}
#endif

void cpp_exp_error (/*YYLTYPE *llocp,*/ char const *s);
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
#line 366 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
typedef union YYSTYPE {
int num;
char* id;
char* string_literal;
A_ClassKey classKey;
A_AccessSpec accessSpec;
A_DeclSpecifierKeyword declSpecifierKeyword;
A_MemberSpec* memberSpec;
A_Condition* cond;
A_Exp* exp;
A_ExpList* expList;
A_Stm* stm;
A_StmList* stmList;
A_Declarator* declarator;
A_DirectDeclarator* directDeclarator;
A_Declaration* declaration;
A_DeclarationList* declarationList;
A_DeclaratorList* declaratorList;
//A_TypeSpec* typespec;
A_TypeId* typeId;
A_TypeIdList* typeIdList;
A_DeclSpec* declspec;
A_DeclSpec* typespec;
A_DeclSpecList* declspecList;
A_ParameterDeclarations* paramDecls;
} YYSTYPE;
/* Line 188 of glr.c.  */
#line 621 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.tab.c"
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
#line 650 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.tab.c"

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
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   850

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  87
/* YYNRULES -- Number of rules. */
#define YYNRULES  219
/* YYNRULES -- Number of states. */
#define YYNSTATES  309
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule. */
#define YYMAXRHS 5

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

#define YYTRANSLATE(YYX) 						\
  ((YYX <= 0) ? YYEOF :							\
   (unsigned)(YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,     2,     2,     2,    90,    84,     2,
      79,    80,    83,    85,    82,    86,    81,    89,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   100,   101,
      91,    95,    92,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    98,     2,    99,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    96,    94,    97,    88,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    93,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    25,    27,    29,    31,    33,    35,    37,    41,
      43,    48,    51,    54,    58,    62,    64,    68,    69,    71,
      73,    76,    79,    82,    85,    88,    91,    94,    97,   100,
     105,   107,   112,   114,   116,   120,   124,   128,   130,   134,
     138,   140,   144,   148,   150,   154,   158,   160,   162,   166,
     168,   172,   174,   178,   180,   182,   184,   186,   190,   192,
     193,   195,   197,   199,   201,   203,   205,   207,   209,   211,
     213,   215,   217,   219,   221,   223,   225,   230,   232,   234,
     236,   238,   241,   243,   246,   247,   249,   251,   253,   255,
     257,   259,   261,   263,   265,   267,   269,   271,   273,   275,
     277,   279,   281,   283,   285,   288,   294,   295,   297,   299,
     302,   306,   307,   309,   311,   315,   317,   319,   322,   324,
     329,   334,   338,   340,   343,   346,   350,   352,   355,   357,
     360,   361,   363,   365,   368,   369,   371,   377,   382,   386,
     387,   389,   391,   394,   398,   400,   404,   405,   407,   409,
     413,   416,   418,   422,   425,   430,   433,   438,   440,   443,
     445,   448,   450,   452,   454,   456,   458,   461,   462,   464,
     466,   468,   471,   476,   478,   480,   482,   484,   486,   488,
     489,   491,   493,   497,   500,   504,   506,   509,   513,   519,
     521,   523,   527,   530,   534,   535,   538,   539,   541,   544,
     545,   547,   549,   553,   555,   559,   563,   564,   566,   570
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     103,     0,    -1,   104,    -1,   126,    -1,    38,    -1,    39,
      -1,    77,    -1,    75,    -1,    76,    -1,   105,    -1,    78,
      -1,    79,   103,    80,    -1,   107,    -1,   108,    -1,   109,
      -1,   187,    -1,   110,    -1,     3,    -1,   110,    69,     3,
      -1,   106,    -1,   111,    79,   113,    80,    -1,   111,     4,
      -1,   111,     5,    -1,   111,    81,   107,    -1,   111,     6,
     107,    -1,   128,    -1,   112,    82,   128,    -1,    -1,   112,
      -1,   111,    -1,     4,   115,    -1,     5,   115,    -1,    83,
     115,    -1,    84,   115,    -1,    85,   115,    -1,    86,   115,
      -1,    87,   115,    -1,    88,   115,    -1,    74,   114,    -1,
      74,    79,   151,    80,    -1,   114,    -1,    79,   151,    80,
     115,    -1,   115,    -1,   116,    -1,   117,    83,   116,    -1,
     117,    89,   116,    -1,   117,    90,   116,    -1,   117,    -1,
     118,    85,   117,    -1,   118,    86,   117,    -1,   118,    -1,
     119,    67,   118,    -1,   119,    68,   118,    -1,   119,    -1,
     120,    91,   119,    -1,   120,    92,   119,    -1,   120,    -1,
     121,    -1,   122,    84,   121,    -1,   122,    -1,   123,    93,
     122,    -1,   123,    -1,   124,    94,   123,    -1,   124,    -1,
     125,    -1,    95,    -1,   104,    -1,   126,   127,   128,    -1,
     104,    -1,    -1,   104,    -1,    37,    -1,    21,    -1,   133,
      -1,   134,    -1,   139,    -1,    37,    -1,    21,    -1,   133,
      -1,   134,    -1,   140,    -1,    30,    -1,    31,    -1,    32,
      -1,     7,    -1,    33,    -1,    62,    79,     3,    80,    -1,
      34,    -1,    35,    -1,    36,    -1,   131,    -1,   135,   131,
      -1,   132,    -1,   136,   132,    -1,    -1,   136,    -1,    48,
      -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,    59,
      -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,
      -1,    58,    -1,   138,    -1,   141,    -1,   170,    -1,   142,
      -1,   166,    -1,   166,    -1,    22,     3,    -1,    23,   143,
      96,   145,    97,    -1,    -1,     3,    -1,   146,    -1,   144,
      82,    -1,   144,    82,   146,    -1,    -1,   144,    -1,   147,
      -1,   147,    95,   129,    -1,     3,    -1,   149,    -1,   164,
     148,    -1,   150,    -1,   149,    79,   159,    80,    -1,   149,
      98,   130,    99,    -1,    79,   148,    80,    -1,   107,    -1,
      69,   110,    -1,   152,   156,    -1,   110,   154,   156,    -1,
     139,    -1,   152,   139,    -1,   140,    -1,   153,   140,    -1,
      -1,   153,    -1,   157,    -1,   164,   156,    -1,    -1,   155,
      -1,   158,    79,   159,    80,   168,    -1,   158,    98,   130,
      99,    -1,    79,   155,    80,    -1,    -1,   157,    -1,   161,
      -1,   161,    70,    -1,   160,    82,    70,    -1,   163,    -1,
     160,    82,   163,    -1,    -1,   160,    -1,   135,    -1,   136,
       3,   137,    -1,     3,   137,    -1,   162,    -1,   162,    95,
     128,    -1,   162,   148,    -1,   162,   148,    95,   128,    -1,
     162,   155,    -1,   162,   155,    95,   128,    -1,    83,    -1,
      83,   167,    -1,   165,    -1,   165,   167,    -1,    61,    -1,
      60,    -1,    19,    -1,    20,    -1,   166,    -1,   166,   167,
      -1,    -1,   167,    -1,     3,    -1,   187,    -1,   171,     3,
      -1,   174,    96,   181,    97,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    28,    -1,    29,    -1,    -1,   172,
      -1,   171,    -1,   171,     3,   183,    -1,   177,   181,    -1,
     172,   100,   181,    -1,   101,    -1,   135,   101,    -1,   135,
     178,   101,    -1,   137,     3,   137,   178,   101,    -1,   176,
      -1,   179,    -1,   178,    82,   179,    -1,   148,   180,    -1,
     143,   100,   129,    -1,    -1,    95,   129,    -1,    -1,   175,
      -1,   100,   184,    -1,    -1,   182,    -1,   185,    -1,   184,
      82,   185,    -1,   169,    -1,    35,   173,   169,    -1,   172,
     186,   169,    -1,    -1,    35,    -1,   188,    91,    92,    -1,
       3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   565,   565,   568,   572,   573,   574,   575,   576,   579,
     580,   581,   582,   585,   586,   594,   606,   614,   615,   621,
     622,   623,   624,   625,   626,   630,   631,   634,   635,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   659,
     666,   667,   671,   677,   678,   679,   680,   683,   684,   685,
     688,   689,   690,   693,   694,   695,   703,   709,   710,   713,
     714,   717,   718,   721,   725,   728,   731,   732,   742,   745,
     746,   752,   753,   754,   755,   756,   760,   761,   762,   763,
     764,   767,   768,   769,   770,   771,   772,   775,   779,   780,
     783,   784,   787,   788,   795,   796,   799,   800,   801,   802,
     803,   804,   805,   806,   807,   808,   809,   810,   818,   819,
     820,   821,   822,   827,   832,   835,   838,   839,   842,   843,
     844,   847,   848,   851,   852,   855,   871,   872,   875,   876,
     877,   878,   881,   883,   886,   887,   890,   891,   894,   895,
     898,   899,   902,   903,   906,   907,   910,   911,   912,   915,
     916,   919,   920,   921,   928,   929,   932,   933,   936,   937,
     952,   955,   956,   957,   958,   959,   960,   967,   968,   969,
     970,   973,   974,   977,   978,   981,   982,   985,   986,   990,
     991,   994,   995,   998,   999,  1000,  1003,  1004,  1005,  1008,
    1009,  1012,  1013,  1020,  1021,  1024,  1025,  1026,  1030,  1034,
    1044,  1045,  1053,  1054,  1066,  1067,  1076,  1077,  1082,  1085,
    1086,  1089,  1090,  1094,  1095,  1096,  1099,  1100,  1105,  1108
};
#endif

#if (YYDEBUG) || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "identifier", "PLUSPLUS", "MINUSMINUS", 
  "ARROW", "EXTERN_KW", "IF_KW", "ELSE_KW", "SWITCH_KW", "CASE_KW", 
  "DEFAULT_KW", "GOTO_KW", "BREAK_KW", "CONTINUE_KW", "FOR_KW", "DO_KW", 
  "WHILE_KW", "CONST_KW", "VOLATILE_KW", "TYPEDEF_KW", "TYPENAME_KW", 
  "ENUM_KW", "CLASS_KW", "STRUCT_KW", "UNION_KW", "PRIVATE_KW", 
  "PROTECTED_KW", "PUBLIC_KW", "AUTO_KW", "REGISTER_KW", "STATIC_KW", 
  "MUTABLE_KW", "INLINE_KW", "VIRTUAL_KW", "EXPLICIT_KW", "FRIEND_KW", 
  "FALSE_KW", "TRUE_KW", "STATIC_CAST_KW", "REINTERPRET_CAST_KW", 
  "DYNAMIC_CAST_KW", "CONST_CAST_KW", "RETURN_KW", "TRY_KW", "THROW_KW", 
  "CATCH_KW", "CHAR_KW", "WCHAR_T_KW", "BOOL_KW", "SHORT_KW", "INT_KW", 
  "LONG_KW", "SIGNED_KW", "UNSIGNED_KW", "FLOAT_KW", "DOUBLE_KW", 
  "VOID_KW", "__INT64_KW", "__CDECL_KW", "__STDCALL_KW", "__DECLSPEC_KW", 
  "__ASM_KW", "__SAVEDS_KW", "__INTERRUPT_KW", "__CHIP_KW", "LSHIFT", 
  "RSHIFT", "TWO_COLON", "THREE_DOTS", "NEW_KW", "DELETE_KW", 
  "OPERATOR_KW", "SIZEOF_KW", "STRING_LITERAL", "LSTRING_LITERAL", 
  "INTEGER_LITERAL", "THIS_KW", "'('", "')'", "'.'", "','", "'*'", "'&'", 
  "'+'", "'-'", "'!'", "'~'", "'/'", "'%'", "'<'", "'>'", "'\\210'", 
  "'|'", "'='", "'{'", "'}'", "'['", "']'", "':'", "';'", "$accept", 
  "expression", "conditional_expression", "literal", "primary_expression", 
  "id_expression", "unqualified_id", "qualified_id", 
  "nested_name_specifier", "postfix_expression", "expression_list", 
  "expression_list_opt", "unary_expression", "cast_expression", 
  "pm_expression", "multiplicative_expression", "additive_expression", 
  "shift_expression", "relational_expression", "equality_expression", 
  "and_expression", "exclusive_or_expression", "inclusive_or_expression", 
  "logical_and_expression", "logical_or_expression", 
  "assignment_operator", "assignment_expression", "constant_expression", 
  "constant_expression_opt", "decl_specifier", "decl_specifier2", 
  "storage_class_specifier", "function_specifier", "decl_specifier_seq", 
  "decl_specifier_seq2", "decl_specifier_seq2_opt", 
  "simple_type_specifier", "type_specifier", "type_specifier2", 
  "elaborated_type_specifier", "enum_specifier", "identifier_opt", 
  "enumerator_list", "enumerator_list_opt", "enumerator_definition", 
  "enumerator", "declarator", "direct_declarator", "declarator_id", 
  "type_id", "type_specifier_seq", "type_specifier_seq2", 
  "type_specifier_seq2_opt", "abstract_declarator", 
  "abstract_declarator_opt", "direct_abstract_declarator", 
  "direct_abstract_declarator_opt", "parameter_declaration_clause", 
  "parameter_declaration_list", "parameter_declaration_list_opt", 
  "parameter_declaration_decl", "parameter_declaration", "ptr_operator", 
  "cc_qualifier", "cv_qualifier", "cv_qualifier_seq", 
  "cv_qualifier_seq_opt", "class_name", "class_specifier", "class_key", 
  "access_specifier", "access_specifier_opt", "class_head", 
  "member_specification", "member_declaration_decl", "member_declaration", 
  "member_declarator_list", "member_declarator", 
  "constant_initializer_opt", "member_specification_opt", "base_clause", 
  "base_clause_opt", "base_specifier_list", "base_specifier", 
  "virtual_opt", "template_id", "template_name", 0
};

#define yytname_size ((int) (sizeof (yytname) / sizeof (yytname[0])))
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   102,   103,   104,   105,   105,   105,   105,   105,   106,
     106,   106,   106,   107,   107,   108,   109,   110,   110,   111,
     111,   111,   111,   111,   111,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     115,   115,   116,   117,   117,   117,   117,   118,   118,   118,
     119,   119,   119,   120,   120,   120,   121,   122,   122,   123,
     123,   124,   124,   125,   126,   127,   128,   128,   129,   130,
     130,   131,   131,   131,   131,   131,   132,   132,   132,   132,
     132,   133,   133,   133,   133,   133,   133,   134,   134,   134,
     135,   135,   136,   136,   137,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   139,   139,
     139,   139,   139,   140,   141,   142,   143,   143,   144,   144,
     144,   145,   145,   146,   146,   147,   148,   148,   149,   149,
     149,   149,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   156,   156,   157,   157,   157,   158,
     158,   159,   159,   159,   160,   160,   161,   161,   162,   162,
     162,   163,   163,   163,   163,   163,   163,   164,   164,   164,
     164,   165,   165,   166,   166,   167,   167,   168,   168,   169,
     169,   170,   170,   171,   171,   171,   172,   172,   172,   173,
     173,   174,   174,   175,   175,   176,   176,   176,   176,   177,
     178,   178,   179,   179,   180,   180,   181,   181,   182,   183,
     183,   184,   184,   185,   185,   185,   186,   186,   187,   188
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       4,     2,     2,     3,     3,     1,     3,     0,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       1,     4,     1,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     3,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       1,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     5,     0,     1,     1,     2,
       3,     0,     1,     1,     3,     1,     1,     2,     1,     4,
       4,     3,     1,     2,     2,     3,     1,     2,     1,     2,
       0,     1,     1,     2,     0,     1,     5,     4,     3,     0,
       1,     1,     2,     3,     1,     3,     0,     1,     1,     3,
       2,     1,     3,     2,     4,     2,     4,     1,     2,     1,
       2,     1,     1,     1,     1,     1,     2,     0,     1,     1,
       1,     2,     4,     1,     1,     1,     1,     1,     1,     0,
       1,     1,     3,     2,     3,     1,     2,     3,     5,     1,
       1,     3,     2,     3,     0,     2,     0,     1,     2,     0,
       1,     1,     3,     1,     3,     3,     0,     1,     3,     1
};

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none). */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     2,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
static const unsigned char yydefact[] =
{
       0,    17,     0,     0,     4,     5,     0,     7,     8,     6,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       9,    19,    12,    13,    14,    16,    29,    40,    42,    43,
      47,    50,    53,    56,    57,    59,    61,    63,    64,     3,
      15,     0,    30,    31,     0,    38,   173,   174,     0,   116,
     183,   184,   185,    96,    97,    98,    99,   100,   102,   103,
     104,   105,   106,   107,   101,     0,    16,   108,   136,   109,
     111,     0,   144,   112,   110,   191,     0,    32,    33,    34,
      35,    36,    37,     1,     0,    21,    22,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,   117,     0,    11,   138,   141,
     144,   113,     0,   172,   171,   149,   167,   137,   145,   134,
     142,     0,   144,   169,   181,    94,    18,    24,    66,    28,
       0,     3,    25,    23,    44,    45,    46,    48,    49,    51,
      52,    54,    55,    58,    60,    62,   218,    39,   121,   139,
     135,    41,     0,   175,   168,   156,    69,   143,   170,     0,
     210,   192,    84,    72,   186,   187,   188,    81,    82,    83,
      85,    87,    88,    89,    71,     0,   195,    90,    92,    73,
      74,   116,    95,     0,    75,    80,   112,     0,   207,   199,
      94,     0,     0,    20,    65,     0,   125,   122,     0,   118,
     123,   148,   176,    94,   158,     0,     0,   157,   151,   161,
     154,    70,     0,   179,   189,   213,   216,   208,   211,   180,
       0,    17,    72,    71,     0,     0,   196,   132,    91,    73,
      74,     0,   204,   126,   128,     0,     0,   200,    77,    76,
      93,    78,    79,    94,    94,   193,   182,    26,    67,   119,
     115,     0,   160,    94,   177,     0,   152,   149,     0,   163,
     165,   144,   147,   190,     0,   217,     0,     0,     0,    17,
     133,     0,     0,     0,   202,   156,    69,   127,   116,   197,
     116,   194,   120,    68,   124,   159,   178,   146,   153,   155,
     162,     0,     0,   214,   215,   212,    86,   131,   203,   205,
       0,     0,   201,     0,   164,   166,   129,   130,   198
};

/* YYPDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    65,   128,    20,    21,    22,    23,    24,    25,    26,
     129,   130,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,   195,   132,   284,   212,   177,
     178,   179,   180,   181,   182,   183,    67,   184,   185,    69,
      70,   231,   197,   198,   199,   200,   232,   233,   234,    71,
      72,   109,   110,   118,   157,   120,   121,   206,   207,   208,
     209,   210,   235,   123,   111,   154,   287,   215,    74,    75,
     187,   264,    76,   188,   189,   190,   236,   237,   274,   191,
     160,   161,   217,   218,   266,    40,    41
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -177
static const short yypact[] =
{
     145,   -51,   145,   145,  -177,  -177,   426,  -177,  -177,  -177,
    -177,   402,   145,   145,   145,   145,   145,   145,    43,  -177,
    -177,  -177,  -177,  -177,  -177,   -18,    14,  -177,  -177,  -177,
      31,    42,    36,    39,  -177,   -26,   -24,   -31,  -177,  -177,
    -177,   -14,  -177,  -177,   402,  -177,  -177,  -177,    91,    97,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,    37,   488,  -177,  -177,  -177,
    -177,    54,   472,  -177,  -177,   116,    50,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,   148,  -177,  -177,   152,   145,   152,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,    78,    95,  -177,  -177,    81,  -177,  -177,   118,
       7,  -177,   145,  -177,  -177,    93,   118,  -177,  -177,  -177,
     -42,   -37,   384,   118,   -12,   342,  -177,  -177,  -177,   111,
     120,   103,  -177,  -177,  -177,  -177,  -177,    31,    31,    42,
      42,    36,    36,  -177,   -26,   -24,  -177,  -177,   198,  -177,
    -177,  -177,   128,   118,  -177,   614,   145,  -177,  -177,   176,
    -177,  -177,  -177,   267,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,   320,   131,  -177,  -177,  -177,   622,
     671,   259,   788,   211,  -177,  -177,   679,   126,  -177,  -177,
     342,   121,   145,  -177,  -177,   145,  -177,   154,   141,  -177,
     151,  -177,  -177,   788,   735,   715,   163,   165,   178,    13,
    -177,  -177,   153,   158,   140,  -177,   215,   171,  -177,  -177,
     251,   -45,  -177,  -177,   252,   130,  -177,  -177,  -177,  -177,
    -177,   157,   161,   -32,  -177,   130,   -30,  -177,  -177,  -177,
    -177,  -177,  -177,   788,   342,  -177,  -177,  -177,  -177,   198,
    -177,   145,  -177,   788,   118,   557,  -177,   156,   145,   164,
     166,    18,  -177,  -177,   255,  -177,   255,   176,   180,  -177,
     -18,   183,   145,   145,  -177,   614,   145,  -177,   264,  -177,
     264,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,   145,   145,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
     184,   169,  -177,   -29,  -177,  -177,  -177,  -177,  -177
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -177,   269,     0,  -177,  -177,   -83,  -177,  -177,    -9,  -177,
    -177,  -177,   265,    11,   150,    64,    65,    84,  -177,   206,
     175,   205,  -177,  -177,   -85,  -177,  -156,   -87,     1,  -150,
    -141,   -41,   -16,  -146,  -143,  -173,  -177,     4,   -34,  -177,
    -177,   273,  -177,  -177,    77,  -177,  -176,  -177,  -177,   286,
    -177,  -177,  -177,  -110,   -50,  -177,  -177,    56,  -177,  -177,
    -177,    79,   -65,  -177,   -10,  -115,  -177,  -175,  -177,  -177,
    -149,  -177,  -177,  -177,  -177,  -177,    52,    57,  -177,  -161,
    -177,  -177,  -177,    69,  -177,  -142,  -177
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -220
static const short yytable[] =
{
      19,    73,    66,   131,   127,   152,   133,   122,   158,   204,
     216,    19,   205,    42,    43,    68,     1,   219,    85,    86,
      87,     1,   119,    77,    78,    79,    80,    81,    82,   245,
     252,   228,   108,   259,    73,    66,   247,  -150,   202,   248,
     -17,   240,   155,    83,    19,   122,  -219,   275,    68,   271,
     122,    84,   278,   278,   228,  -117,  -150,   122,    99,   277,
     150,   156,    73,   101,   240,   263,   276,   113,   114,   100,
     280,   279,   308,   113,   114,   149,   117,   102,   113,   114,
     285,   271,   224,   281,  -209,   277,   115,   224,   159,   293,
     116,   294,   257,    88,   104,    89,   116,   257,   227,   260,
     105,   116,   290,    95,    96,  -149,   153,   131,   258,   204,
     131,  -149,   205,   153,    90,   186,  -149,   107,   216,   124,
      91,    92,   219,   151,   219,   219,   227,    93,    94,   204,
      97,    98,   205,     1,   112,   304,   305,    46,    47,   286,
     229,   241,   227,   153,   261,   186,   125,   152,     1,     2,
       3,   126,   227,   113,   114,     1,   211,   137,   138,     1,
     139,   140,   241,   229,   241,   230,   242,   164,   165,   166,
     146,    73,   115,   131,   227,   147,   116,   148,   227,   213,
     186,   141,   142,     4,     5,   298,   299,   242,   230,   242,
     113,   114,   261,   192,    73,   227,   261,   227,   194,   224,
     193,   196,   241,   164,   165,   166,   131,   131,   201,   225,
     220,   214,   241,   116,   243,   270,   113,   114,   246,     6,
       7,     8,     9,    10,    11,   224,   244,   242,    12,    13,
      14,    15,    16,    17,   186,   257,   249,   242,   250,   116,
     134,   135,   136,   254,   153,   186,   251,   255,   256,  -219,
     265,   283,   262,   267,   268,   269,   273,   272,   213,   291,
     296,   292,   221,   297,   306,   186,   162,   221,   307,    18,
     -72,    45,   283,   283,   -72,   144,   211,   301,    46,    47,
     222,    48,    49,    50,    51,    52,   -72,   -72,   -72,   167,
     168,   169,   170,   171,   172,   173,   223,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   143,   145,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,   113,
     114,   175,   106,   -71,   113,   114,   282,   -71,   224,   -72,
     103,   300,   303,   224,   289,   302,   295,     0,   225,   -71,
     -71,   -71,   116,   225,     0,     0,     0,   116,     0,   162,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,     0,     0,
     226,    46,    47,   163,    48,    49,    50,    51,    52,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,   -71,     0,     0,     0,     0,     0,     0,     0,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,     0,     0,   175,     1,     2,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,    47,     0,    48,    49,    50,    51,    52,     1,
       2,     3,     0,     0,     0,     0,     0,     0,     0,  -206,
       4,     5,     0,   176,   113,   114,     0,     0,     0,     0,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,     0,   115,     4,     5,     0,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     7,     8,     9,
      10,    11,  -149,     0,     0,    12,    13,    14,    15,    16,
      17,    46,    47,     0,    48,    49,    50,    51,    52,     0,
       6,     7,     8,     9,    10,    44,     0,    46,    47,    12,
      13,    14,    15,    16,    17,     0,     0,     0,     0,     0,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -140,  -140,
       0,   115,     0,     0,     0,   116,     0,    84,     0,     0,
     203,     0,     0,     0,   162,     0,     0,   -16,   -16,     0,
    -149,   -16,     0,     0,     0,     0,    46,    47,   163,    48,
      49,    50,    51,    52,     0,     0,  -140,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,   203,     0,   175,
       0,   162,     0,     0,     0,   -73,     0,   288,     0,   -73,
       0,     0,     0,    46,    47,   163,    48,    49,    50,    51,
      52,   -73,   -73,   -73,   167,   168,   169,   170,   171,   172,
     173,   174,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
       0,     0,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,   -74,     0,   175,     0,   -74,     0,
       0,     0,  -112,     0,   -73,     0,  -112,     0,     0,     0,
     -74,   -74,   -74,     0,     0,     0,     0,     0,  -112,  -112,
    -112,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,     0,   253,     0,
       0,     0,   162,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -74,    46,    47,   238,     0,     0,     0,
       0,  -112,   162,     0,     0,   167,   168,   169,   170,   171,
     172,   173,   239,     0,    46,    47,   222,    48,    49,    50,
      51,    52,     0,     0,     0,   167,   168,   169,   170,   171,
     172,   173,   223,     0,     0,     0,     0,   175,     0,     0,
       0,     0,     0,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,   162,     0,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,    47,   238,
       0,     0,     0,     0,     0,     0,     0,     0,   167,   168,
     169,   170,   171,   172,   173,   239,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     175
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,     0,    17,     0,
       0,     0,   159,     0,     0,     0,     0,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   161,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,     0,     0,     0,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    25,    27,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    31,    33,
      35,    37,    39,    41,    43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    47,     0,     0,     0,    49,     0,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      53,    55,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    59,    61,    63,    65,    67,    69,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     5,     0,
       0,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,     0,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    79,    81,    83,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    87,    89,    91,    93,    95,    97,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   103,     0,     0,     0,   105,     0,
       0,     0,   131,     0,   101,     0,   133,     0,     0,     0,
     107,   109,   111,     0,     0,     0,     0,     0,   135,   137,
     139,   113,   115,   117,   119,   121,   123,   125,   127,   141,
     143,   145,   147,   149,   151,   153,   155,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,     0,     0,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,   219,     0,   140,     0,   140,     0,   140,     0,   149,
       0,   149,     0,   149,     0,   149,     0,   181,     0,    77,
       0,    77,     0,    77,     0,    77,     0,    77,     0,    77,
       0,    77,     0,    77,     0,    77,     0,    77,     0,    77,
       0,    77,     0,    77,     0,    77,     0,    76,     0,    76,
       0,    76,     0,    76,     0,    76,     0,    76,     0,    76,
       0,    76,     0,    76,     0,    76,     0,    76,     0,    76,
       0,    76,     0,    76,     0,    78,     0,    78,     0,    78,
       0,    78,     0,    78,     0,    78,     0,    78,     0,    78,
       0,    78,     0,    78,     0,    78,     0,    78,     0,    78,
       0,    78,     0,    79,     0,    79,     0,    79,     0,    79,
       0,    79,     0,    79,     0,    79,     0,    79,     0,    79,
       0,    79,     0,    79,     0,    79,     0,    79,     0,    79,
       0,   113,     0,   113,     0,   113,     0,   113,     0,   113,
       0,   113,     0,   113,     0,   113,     0,   113,     0,   113,
       0,   113,     0,   113,     0,   113,     0,   113,     0,   149,
       0,   149,     0,   149,     0
};

static const short yycheck[] =
{
       0,    11,    11,    88,    87,   115,    89,    72,   123,   155,
     159,    11,   155,     2,     3,    11,     3,   159,     4,     5,
       6,     3,    72,    12,    13,    14,    15,    16,    17,   190,
     203,   181,    66,   209,    44,    44,   192,    79,   153,   195,
      91,   182,    79,     0,    44,   110,    91,    79,    44,   225,
     115,    69,    82,    82,   204,   100,    98,   122,    84,   235,
     110,    98,    72,    94,   205,   214,    98,    60,    61,    93,
     243,   101,   101,    60,    61,   109,    72,    91,    60,    61,
     253,   257,    69,   244,    96,   261,    79,    69,   100,   264,
      83,   266,    79,    79,     3,    81,    83,    79,   181,   209,
       3,    83,   258,    67,    68,    98,   116,   192,    95,   255,
     195,    98,   255,   123,    83,   125,    98,    80,   267,     3,
      89,    90,   264,   112,   266,   267,   209,    85,    86,   275,
      91,    92,   275,     3,    80,   291,   292,    19,    20,   254,
     181,   182,   225,   153,   209,   155,    96,   257,     3,     4,
       5,     3,   235,    60,    61,     3,   156,    93,    94,     3,
      95,    96,   203,   204,   205,   181,   182,    27,    28,    29,
      92,   181,    79,   258,   257,    80,    83,    96,   261,     3,
     190,    97,    98,    38,    39,   272,   273,   203,   204,   205,
      60,    61,   257,    82,   204,   278,   261,   280,    95,    69,
      80,     3,   243,    27,    28,    29,   291,   292,    80,    79,
      79,    35,   253,    83,     3,   224,    60,    61,    97,    74,
      75,    76,    77,    78,    79,    69,   100,   243,    83,    84,
      85,    86,    87,    88,   244,    79,    82,   253,    97,    83,
      90,    91,    92,    80,   254,   255,    95,    82,    70,    91,
      35,   251,    99,    82,     3,     3,    95,   100,     3,    95,
      80,    95,     3,    80,    80,   275,     7,     3,    99,     0,
       3,     6,   272,   273,     7,   100,   276,   276,    19,    20,
      21,    22,    23,    24,    25,    26,    19,    20,    21,    30,
      31,    32,    33,    34,    35,    36,    37,    30,    31,    32,
      33,    34,    35,    36,    37,    99,   101,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    49,     3,    60,    61,   249,     7,    69,    62,
      44,   275,   280,    69,   255,   278,   267,    -1,    79,    19,
      20,    21,    83,    79,    -1,    -1,    -1,    83,    -1,     7,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
     101,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,     3,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    -1,    22,    23,    24,    25,    26,     3,
       4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,
      38,    39,    -1,   101,    60,    61,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    79,    38,    39,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    79,    98,    -1,    -1,    83,    84,    85,    86,    87,
      88,    19,    20,    -1,    22,    23,    24,    25,    26,    -1,
      74,    75,    76,    77,    78,    79,    -1,    19,    20,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    79,    -1,    -1,    -1,    83,    -1,    69,    -1,    -1,
       3,    -1,    -1,    -1,     7,    -1,    -1,    79,    80,    -1,
      98,    83,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    98,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,     3,    -1,    62,
      -1,     7,    -1,    -1,    -1,     3,    -1,    70,    -1,     7,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    19,    20,    21,    30,    31,    32,    33,    34,    35,
      36,    37,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     3,    -1,    62,    -1,     7,    -1,
      -1,    -1,     3,    -1,    62,    -1,     7,    -1,    -1,    -1,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    30,    31,    32,    33,    34,    35,    36,    37,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,     3,    -1,
      -1,    -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    19,    20,    21,    -1,    -1,    -1,
      -1,    62,     7,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     7,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    38,    39,    74,    75,    76,    77,
      78,    79,    83,    84,    85,    86,    87,    88,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     187,   188,   115,   115,    79,   114,    19,    20,    22,    23,
      24,    25,    26,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,   103,   110,   138,   139,   141,
     142,   151,   152,   166,   170,   171,   174,   115,   115,   115,
     115,   115,   115,     0,    69,     4,     5,     6,    79,    81,
      83,    89,    90,    85,    86,    67,    68,    91,    92,    84,
      93,    94,    91,   151,     3,     3,   143,    80,   140,   153,
     154,   166,    80,    60,    61,    79,    83,   139,   155,   156,
     157,   158,   164,   165,     3,    96,     3,   107,   104,   112,
     113,   126,   128,   107,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   121,   122,   123,    92,    80,    96,   140,
     156,   115,   155,   166,   167,    79,    98,   156,   167,   100,
     182,   183,     7,    21,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    62,   101,   131,   132,   133,
     134,   135,   136,   137,   139,   140,   166,   172,   175,   176,
     177,   181,    82,    80,    95,   127,     3,   144,   145,   146,
     147,    80,   167,     3,   135,   136,   159,   160,   161,   162,
     163,   104,   130,     3,    35,   169,   172,   184,   185,   187,
      79,     3,    21,    37,    69,    79,   101,   107,   131,   133,
     134,   143,   148,   149,   150,   164,   178,   179,    21,    37,
     132,   133,   134,     3,   100,   181,    97,   128,   128,    82,
      97,    95,   137,     3,    80,    82,    70,    79,    95,   148,
     155,   164,    99,   172,   173,    35,   186,    82,     3,     3,
     110,   148,   100,    95,   180,    79,    98,   148,    82,   101,
     137,   181,   146,   104,   129,   137,   167,   168,    70,   163,
     128,    95,    95,   169,   169,   185,    80,    80,   129,   129,
     159,   130,   179,   178,   128,   128,    80,    99,   101
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
#line 565 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { g_exp = yyvsp[0].yystate.yysemantics.yysval.exp ;}
    break;

  case 4:
#line 572 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BoolExp(0) ;}
    break;

  case 5:
#line 573 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BoolExp(1) ;}
    break;

  case 6:
#line 574 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_Int32Exp(yyvsp[0].yystate.yysemantics.yysval.num) ;}
    break;

  case 7:
#line 575 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_StringExp(yyvsp[0].yystate.yysemantics.yysval.string_literal) ;}
    break;

  case 8:
#line 576 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_LStringExp(yyvsp[0].yystate.yysemantics.yysval.string_literal) ;}
    break;

  case 11:
#line 581 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = yyvsp[-1].yystate.yysemantics.yysval.exp;}
    break;

  case 15:
#line 594 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {;}
    break;

  case 16:
#line 606 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {;}
    break;

  case 17:
#line 614 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_IdExp(yyvsp[0].yystate.yyloc, yyvsp[0].yystate.yysemantics.yysval.id) ;}
    break;

  case 18:
#line 615 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '::', yyvsp[-2].yystate.yysemantics.yysval.exp, A_IdExp(yyvsp[0].yystate.yyloc, yyvsp[0].yystate.yysemantics.yysval.id)) ;}
    break;

  case 20:
#line 622 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_CallExp(yyvsp[-3].yystate.yyloc, yyvsp[-3].yystate.yysemantics.yysval.exp, yyvsp[-1].yystate.yysemantics.yysval.expList) ;}
    break;

  case 21:
#line 623 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 22:
#line 624 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 23:
#line 625 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '.', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 24:
#line 626 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '->', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 25:
#line 630 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).expList = new A_ExpList(yyvsp[0].yystate.yysemantics.yysval.exp, NULL) ;}
    break;

  case 26:
#line 631 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).expList = new A_ExpList(yyvsp[0].yystate.yysemantics.yysval.exp, yyvsp[-2].yystate.yysemantics.yysval.expList) ;}
    break;

  case 27:
#line 634 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).expList = NULL ;}
    break;

  case 30:
#line 650 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '++', yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 31:
#line 651 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '--', yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 32:
#line 652 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '*', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 33:
#line 653 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '&', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 34:
#line 654 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '+', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 35:
#line 655 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '-', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 36:
#line 656 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '!', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 37:
#line 657 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '~', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 38:
#line 658 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {ASSERT(0);}
    break;

  case 39:
#line 659 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {ASSERT(0);}
    break;

  case 41:
#line 667 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_CastExp(yyvsp[-2].yystate.yysemantics.yysval.typeId, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 44:
#line 678 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '*', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 45:
#line 679 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '/', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 46:
#line 680 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '%', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 48:
#line 684 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '+', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 49:
#line 685 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '-', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 51:
#line 689 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '<<', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 52:
#line 690 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '>>', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 54:
#line 694 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '<', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 55:
#line 695 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '>', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 58:
#line 710 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '&', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 60:
#line 714 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '^', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 62:
#line 718 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '|', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 67:
#line 732 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-1].yystate.yyloc, '=', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 69:
#line 745 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = NULL ;}
    break;

  case 71:
#line 752 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(A_FRIEND) ;}
    break;

  case 72:
#line 753 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(A_TYPEDEF) ;}
    break;

  case 73:
#line 754 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(yyvsp[0].yystate.yysemantics.yysval.declSpecifierKeyword) ;}
    break;

  case 74:
#line 755 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(yyvsp[0].yystate.yysemantics.yysval.declSpecifierKeyword) ;}
    break;

  case 75:
#line 756 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 76:
#line 760 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(A_FRIEND) ;}
    break;

  case 77:
#line 761 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(A_TYPEDEF) ;}
    break;

  case 78:
#line 762 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(yyvsp[0].yystate.yysemantics.yysval.declSpecifierKeyword) ;}
    break;

  case 79:
#line 763 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspec = A_DeclSpecifier(yyvsp[0].yystate.yysemantics.yysval.declSpecifierKeyword) ;}
    break;

  case 80:
#line 764 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {(*yyvalp).declspec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 81:
#line 767 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_AUTO ;}
    break;

  case 82:
#line 768 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_REGISTER ;}
    break;

  case 83:
#line 769 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_STATIC ;}
    break;

  case 84:
#line 770 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_EXTERN ;}
    break;

  case 85:
#line 771 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_MUTABLE ;}
    break;

  case 86:
#line 772 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { /*TODO*/(*yyvalp).declSpecifierKeyword = A_DECLSPEC ;}
    break;

  case 87:
#line 776 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {
								(*yyvalp).declSpecifierKeyword = A_INLINE
								;}
    break;

  case 88:
#line 779 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_VIRTUAL ;}
    break;

  case 89:
#line 780 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_EXPLICIT ;}
    break;

  case 90:
#line 783 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.declspec, NULL) ;}
    break;

  case 91:
#line 784 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.declspec, yyvsp[-1].yystate.yysemantics.yysval.declspecList) ;}
    break;

  case 92:
#line 787 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.declspec, NULL) ;}
    break;

  case 93:
#line 788 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.declspec, yyvsp[-1].yystate.yysemantics.yysval.declspecList) ;}
    break;

  case 94:
#line 795 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = NULL ;}
    break;

  case 96:
#line 799 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_CHAR) ;}
    break;

  case 97:
#line 800 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_WCHAR_T) ;}
    break;

  case 98:
#line 801 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_BOOL) ;}
    break;

  case 99:
#line 802 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_SHORT) ;}
    break;

  case 100:
#line 803 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_INT) ;}
    break;

  case 101:
#line 804 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A___INT64) ;}
    break;

  case 102:
#line 805 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_LONG) ;}
    break;

  case 103:
#line 806 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_SIGNED) ;}
    break;

  case 104:
#line 807 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_UNSIGNED) ;}
    break;

  case 105:
#line 808 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_FLOAT) ;}
    break;

  case 106:
#line 809 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_DOUBLE) ;}
    break;

  case 107:
#line 810 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_VOID) ;}
    break;

  case 108:
#line 818 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 109:
#line 819 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 110:
#line 820 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 111:
#line 821 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 112:
#line 822 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 113:
#line 827 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 114:
#line 832 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 115:
#line 835 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_Enum(yyvsp[-3].yystate.yysemantics.yysval.id, NULL) ;}
    break;

  case 116:
#line 838 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).id = NULL ;}
    break;

  case 126:
#line 871 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {(*yyvalp).declarator = A_DirectDeclaratorDeclarator(yyvsp[0].yystate.yysemantics.yysval.directDeclarator) ;}
    break;

  case 127:
#line 872 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declarator = A_PtrDeclarator(yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 128:
#line 875 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorId(yyvsp[0].yystate.yyloc, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 129:
#line 876 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorParen(yyvsp[-3].yystate.yysemantics.yysval.directDeclarator, yyvsp[-1].yystate.yysemantics.yysval.paramDecls) ;}
    break;

  case 130:
#line 877 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorArray(yyvsp[-3].yystate.yysemantics.yysval.directDeclarator, yyvsp[-1].yystate.yysemantics.yysval.exp) ;}
    break;

  case 131:
#line 878 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorDeclarator(yyvsp[-1].yystate.yysemantics.yysval.declarator)/* printf("(declarator)")*/ ;}
    break;

  case 132:
#line 881 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).exp = yyvsp[0].yystate.yysemantics.yysval.exp;}
    break;

  case 133:
#line 883 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {;}
    break;

  case 134:
#line 886 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeId = new A_TypeId(yyvsp[-1].yystate.yysemantics.yysval.declspecList, yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 135:
#line 887 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeId = new A_TypeId(new A_DeclSpecList(A_NameType(yyvsp[-2].yystate.yysemantics.yysval.exp), yyvsp[-1].yystate.yysemantics.yysval.declspecList), yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 136:
#line 890 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.typespec, NULL) ;}
    break;

  case 137:
#line 891 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.typespec, yyvsp[-1].yystate.yysemantics.yysval.declspecList) ;}
    break;

  case 138:
#line 894 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.typespec, NULL) ;}
    break;

  case 139:
#line 895 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.typespec, yyvsp[-1].yystate.yysemantics.yysval.declspecList) ;}
    break;

  case 142:
#line 902 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    {(*yyvalp).declarator = A_DirectDeclaratorDeclarator(yyvsp[0].yystate.yysemantics.yysval.directDeclarator) ;}
    break;

  case 143:
#line 903 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declarator = A_PtrDeclarator(yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 144:
#line 906 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declarator = NULL ;}
    break;

  case 146:
#line 910 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorParen(yyvsp[-4].yystate.yysemantics.yysval.directDeclarator, yyvsp[-2].yystate.yysemantics.yysval.paramDecls) ;}
    break;

  case 147:
#line 911 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 148:
#line 912 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorDeclarator(yyvsp[-1].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 149:
#line 915 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).directDeclarator = NULL ;}
    break;

  case 151:
#line 919 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).paramDecls = new A_ParameterDeclarations(yyvsp[0].yystate.yysemantics.yysval.typeIdList, false) ;}
    break;

  case 152:
#line 920 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).paramDecls = new A_ParameterDeclarations(yyvsp[-1].yystate.yysemantics.yysval.typeIdList, true) ;}
    break;

  case 153:
#line 921 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).paramDecls = new A_ParameterDeclarations(yyvsp[-2].yystate.yysemantics.yysval.typeIdList, true) ;}
    break;

  case 154:
#line 928 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeIdList = new A_TypeIdList(yyvsp[0].yystate.yysemantics.yysval.typeId, NULL) ;}
    break;

  case 155:
#line 929 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeIdList = new A_TypeIdList(yyvsp[0].yystate.yysemantics.yysval.typeId, yyvsp[-2].yystate.yysemantics.yysval.typeIdList) ;}
    break;

  case 156:
#line 932 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeIdList = NULL ;}
    break;

  case 160:
#line 952 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { /*$$ = new A_DeclSpecList(A_TypeSpecifier(A_NameType($1)), $2)*/ ;}
    break;

  case 161:
#line 955 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeId = new A_TypeId(yyvsp[0].yystate.yysemantics.yysval.declspecList, NULL) ;}
    break;

  case 162:
#line 956 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 163:
#line 957 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeId = new A_TypeId(yyvsp[-1].yystate.yysemantics.yysval.declspecList, yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 164:
#line 958 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 165:
#line 959 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typeId = new A_TypeId(yyvsp[-1].yystate.yysemantics.yysval.declspecList, yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 166:
#line 960 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 173:
#line 977 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_CONST) ;}
    break;

  case 174:
#line 978 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_VOLATILE) ;}
    break;

  case 180:
#line 991 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 181:
#line 994 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = A_Class(yyvsp[-1].yystate.yyloc, yyvsp[-1].yystate.yysemantics.yysval.classKey, yyvsp[0].yystate.yysemantics.yysval.id) ;}
    break;

  case 182:
#line 995 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).typespec = yyvsp[-3].yystate.yysemantics.yysval.typespec; (*yyvalp).typespec->CLASSDEF.memberSpec = yyvsp[-1].yystate.yysemantics.yysval.memberSpec ;}
    break;

  case 183:
#line 998 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).classKey = A_CLASSKEY_CLASS ;}
    break;

  case 184:
#line 999 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).classKey = A_CLASSKEY_STRUCT ;}
    break;

  case 185:
#line 1000 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).classKey = A_CLASSKEY_UNION ;}
    break;

  case 186:
#line 1003 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PRIVATE ;}
    break;

  case 187:
#line 1004 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PROTECTED ;}
    break;

  case 188:
#line 1005 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PUBLIC ;}
    break;

  case 189:
#line 1008 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PROTECTED ;}
    break;

  case 191:
#line 1012 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { /*$$ = A_ClassDef(@1, $1, NULL)*/ ;}
    break;

  case 192:
#line 1013 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { /*$$ = A_ClassDef(@1, $1, $2)*/ ;}
    break;

  case 193:
#line 1020 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).memberSpec = A_MemberDecl(yyvsp[-1].yystate.yysemantics.yysval.declaration, yyvsp[0].yystate.yysemantics.yysval.memberSpec) ;}
    break;

  case 194:
#line 1021 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).memberSpec = A_MemberAccessSpec(yyvsp[-2].yystate.yysemantics.yysval.accessSpec, yyvsp[0].yystate.yysemantics.yysval.memberSpec) ;}
    break;

  case 195:
#line 1024 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { ASSERT(0) ;}
    break;

  case 196:
#line 1025 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declaration = A_SimpleDeclaration(yyvsp[-1].yystate.yysemantics.yysval.declspecList, NULL) ;}
    break;

  case 197:
#line 1026 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declaration = A_SimpleDeclaration(yyvsp[-2].yystate.yysemantics.yysval.declspecList, yyvsp[-1].yystate.yysemantics.yysval.declaratorList) ;}
    break;

  case 200:
#line 1044 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declaratorList = new A_DeclaratorList(yyvsp[0].yystate.yysemantics.yysval.declarator, NULL) ;}
    break;

  case 201:
#line 1045 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declaratorList = new A_DeclaratorList(yyvsp[0].yystate.yysemantics.yysval.declarator, yyvsp[-2].yystate.yysemantics.yysval.declaratorList) ;}
    break;

  case 203:
#line 1054 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).declarator = NULL ;}
    break;

  case 206:
#line 1076 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"
    { (*yyvalp).memberSpec = NULL ;}
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
#line 2492 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.tab.c"
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


#line 1111 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.y"



