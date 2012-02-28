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
#define yyparse cpp_parse
#define yylex   cpp_lex
#define yyerror cpp_error
#define yylval  cpp_lval
#define yychar  cpp_char
#define yydebug cpp_debug
#define yynerrs cpp_nerrs
#define yylloc cpp_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     identifier = 258,
     identifier_lparen = 259,
     PLUSPLUS = 260,
     MINUSMINUS = 261,
     ARROW = 262,
     EQUAL = 263,
     NOT_EQUAL = 264,
     ASSIGN_PLUS = 265,
     ASSIGN_MINUS = 266,
     ASSIGN_OR = 267,
     ASSIGN_XOR = 268,
     ASSIGN_AND = 269,
     ASSIGN_MUL = 270,
     ASSIGN_DIV = 271,
     ASSIGN_MOD = 272,
     ASSIGN_LSHIFT = 273,
     ASSIGN_RSHIFT = 274,
     LEQ = 275,
     GEQ = 276,
     STAR = 277,
     BITAND = 278,
     BITOR = 279,
     LAND = 280,
     LOR = 281,
     DOT_STAR = 282,
     ARROW_STAR = 283,
     NAMESPACE_KW = 284,
     USING_KW = 285,
     EXTERN_KW = 286,
     IF_KW = 287,
     ELSE_KW = 288,
     SWITCH_KW = 289,
     CASE_KW = 290,
     DEFAULT_KW = 291,
     GOTO_KW = 292,
     BREAK_KW = 293,
     CONTINUE_KW = 294,
     FOR_KW = 295,
     DO_KW = 296,
     WHILE_KW = 297,
     CONST_KW = 298,
     VOLATILE_KW = 299,
     TYPEDEF_KW = 300,
     TYPENAME_KW = 301,
     ENUM_KW = 302,
     CLASS_KW = 303,
     STRUCT_KW = 304,
     UNION_KW = 305,
     PRIVATE_KW = 306,
     PROTECTED_KW = 307,
     PUBLIC_KW = 308,
     AUTO_KW = 309,
     REGISTER_KW = 310,
     STATIC_KW = 311,
     MUTABLE_KW = 312,
     INLINE_KW = 313,
     VIRTUAL_KW = 314,
     EXPLICIT_KW = 315,
     FRIEND_KW = 316,
     FALSE_KW = 317,
     TRUE_KW = 318,
     STATIC_CAST_KW = 319,
     REINTERPRET_CAST_KW = 320,
     DYNAMIC_CAST_KW = 321,
     CONST_CAST_KW = 322,
     RETURN_KW = 323,
     TRY_KW = 324,
     THROW_KW = 325,
     CATCH_KW = 326,
     CHAR_KW = 327,
     WCHAR_T_KW = 328,
     BOOL_KW = 329,
     SHORT_KW = 330,
     INT_KW = 331,
     LONG_KW = 332,
     SIGNED_KW = 333,
     UNSIGNED_KW = 334,
     FLOAT_KW = 335,
     DOUBLE_KW = 336,
     VOID_KW = 337,
     TEMPLATE_KW = 338,
     EXPORT_KW = 339,
     __INT64_KW = 340,
     __CDECL_KW = 341,
     __STDCALL_KW = 342,
     __DECLSPEC_KW = 343,
     __ASM_KW = 344,
     __SAVEDS_KW = 345,
     __INTERRUPT_KW = 346,
     __CHIP_KW = 347,
     LSHIFT = 348,
     RSHIFT = 349,
     TWO_COLON = 350,
     THREE_DOTS = 351,
     NEW_KW = 352,
     DELETE_KW = 353,
     OPERATOR_KW = 354,
     SIZEOF_KW = 355,
     STRING_LITERAL = 356,
     LSTRING_LITERAL = 357,
     INTEGER_LITERAL = 358,
     DOUBLE_LITERAL = 359,
     THIS_KW = 360
   };
#endif
#define identifier 258
#define identifier_lparen 259
#define PLUSPLUS 260
#define MINUSMINUS 261
#define ARROW 262
#define EQUAL 263
#define NOT_EQUAL 264
#define ASSIGN_PLUS 265
#define ASSIGN_MINUS 266
#define ASSIGN_OR 267
#define ASSIGN_XOR 268
#define ASSIGN_AND 269
#define ASSIGN_MUL 270
#define ASSIGN_DIV 271
#define ASSIGN_MOD 272
#define ASSIGN_LSHIFT 273
#define ASSIGN_RSHIFT 274
#define LEQ 275
#define GEQ 276
#define STAR 277
#define BITAND 278
#define BITOR 279
#define LAND 280
#define LOR 281
#define DOT_STAR 282
#define ARROW_STAR 283
#define NAMESPACE_KW 284
#define USING_KW 285
#define EXTERN_KW 286
#define IF_KW 287
#define ELSE_KW 288
#define SWITCH_KW 289
#define CASE_KW 290
#define DEFAULT_KW 291
#define GOTO_KW 292
#define BREAK_KW 293
#define CONTINUE_KW 294
#define FOR_KW 295
#define DO_KW 296
#define WHILE_KW 297
#define CONST_KW 298
#define VOLATILE_KW 299
#define TYPEDEF_KW 300
#define TYPENAME_KW 301
#define ENUM_KW 302
#define CLASS_KW 303
#define STRUCT_KW 304
#define UNION_KW 305
#define PRIVATE_KW 306
#define PROTECTED_KW 307
#define PUBLIC_KW 308
#define AUTO_KW 309
#define REGISTER_KW 310
#define STATIC_KW 311
#define MUTABLE_KW 312
#define INLINE_KW 313
#define VIRTUAL_KW 314
#define EXPLICIT_KW 315
#define FRIEND_KW 316
#define FALSE_KW 317
#define TRUE_KW 318
#define STATIC_CAST_KW 319
#define REINTERPRET_CAST_KW 320
#define DYNAMIC_CAST_KW 321
#define CONST_CAST_KW 322
#define RETURN_KW 323
#define TRY_KW 324
#define THROW_KW 325
#define CATCH_KW 326
#define CHAR_KW 327
#define WCHAR_T_KW 328
#define BOOL_KW 329
#define SHORT_KW 330
#define INT_KW 331
#define LONG_KW 332
#define SIGNED_KW 333
#define UNSIGNED_KW 334
#define FLOAT_KW 335
#define DOUBLE_KW 336
#define VOID_KW 337
#define TEMPLATE_KW 338
#define EXPORT_KW 339
#define __INT64_KW 340
#define __CDECL_KW 341
#define __STDCALL_KW 342
#define __DECLSPEC_KW 343
#define __ASM_KW 344
#define __SAVEDS_KW 345
#define __INTERRUPT_KW 346
#define __CHIP_KW 347
#define LSHIFT 348
#define RSHIFT 349
#define TWO_COLON 350
#define THREE_DOTS 351
#define NEW_KW 352
#define DELETE_KW 353
#define OPERATOR_KW 354
#define SIZEOF_KW 355
#define STRING_LITERAL 356
#define LSTRING_LITERAL 357
#define INTEGER_LITERAL 358
#define DOUBLE_LITERAL 359
#define THIS_KW 360




/* Copy the first part of user declarations.  */
#line 1 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"


#define YYMAXDEPTH	80000

struct PP_TokenList;

extern PP_TokenList* tlist;

BOOL bLastTok = FALSE;

int GetString(int delimiter, bool bWide/*, CToken& token*/)
{
	int line = pPP2->m_pFile->m_line;

	StringA str;

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

static int cpp_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/)
{
	if (!bLastTok)
		pPP2->_GetToken();
	else
		bLastTok = FALSE;

	yylloc.first_line = pPP2->m_pFile->m_line;

	yylloc.first_line = pPP2->m_pFile->m_line;

#if 0
	while (pPP2->curtokpp->type == PP::CToken::tok_space ||
		(pPP2->curtokpp->type == PP::CToken::tok_symbol && pPP2->curtokpp->symbol == '\n'))
	{
		yylloc.first_line = pPP2->m_pFile->m_line;
		pPP2->GetToken();
	//	yylpos.first_line = pPP2->m_location.m_line;
	}
#endif

	if (pPP2->curtokpp->type == PP::CToken::tok_ident)
	{
	//	kwmap::iterator i = kwm.find(pPP2->curtokpp->ident);
	//	if (i != kwm.end())
	//		return (*i).second;
		int kw;
		if (kwm.Lookup(ckw(pPP2->curtokpp->ident.ident), kw))
			return kw;
		else
		{
			cpp_lval.id = pPP2->curtokpp->ident.ident;
			return identifier;
		}
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_integer)
	{
		cpp_lval.num = pPP2->curtokpp->int32;
		return INTEGER_LITERAL;
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_double)
	{
		cpp_lval.num = pPP2->curtokpp->double64;
		return DOUBLE_LITERAL;
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_string)
	{
		cpp_lval.string_literal = strdup(pPP2->curtokpp->string.string);
		return STRING_LITERAL;
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_char ||
				pPP2->curtokpp->type == PP::CToken::tok_symbol)
	{
		int c = pPP2->curtokpp->symbol;

#if 0
		if (c == '\'')
		{
			return GetString(c, FALSE/*, token*/);
		}
		else if (c == '\"')
		{
			return GetString(c, FALSE/*, token*/);
		}
#endif
		if (pPP2->curtokpp->symbol == '*')
		{
			return STAR;
		}
		else if (pPP2->curtokpp->symbol == '&')
		{
			return BITAND;
		}
		else if (pPP2->curtokpp->symbol == '|')
		{
			return BITOR;
		}
		else if (pPP2->curtokpp->symbol == '<<')
		{
			return LSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '>>')
		{
			return RSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '==')
		{
			return EQUAL;
		}
		else if (pPP2->curtokpp->symbol == '|=')
		{
			return ASSIGN_OR;
		}
		else if (pPP2->curtokpp->symbol == '&=')
		{
			return ASSIGN_AND;
		}
		else if (pPP2->curtokpp->symbol == '^=')
		{
			return ASSIGN_XOR;
		}
		else if (pPP2->curtokpp->symbol == '!=')
		{
			return NOT_EQUAL;
		}
		else if (pPP2->curtokpp->symbol == '+=')
		{
			return ASSIGN_PLUS;
		}
		else if (pPP2->curtokpp->symbol == '-=')
		{
			return ASSIGN_MINUS;
		}
		else if (pPP2->curtokpp->symbol == '*=')
		{
			return ASSIGN_MUL;
		}
		else if (pPP2->curtokpp->symbol == '/=')
		{
			return ASSIGN_DIV;
		}
		else if (pPP2->curtokpp->symbol == '%=')
		{
			return ASSIGN_MOD;
		}
		else if (pPP2->curtokpp->symbol == '>>=')
		{
			return ASSIGN_RSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '<<=')
		{
			return ASSIGN_LSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '...')
		{
			return THREE_DOTS;
		}
		else if (pPP2->curtokpp->symbol == '->')
		{
			return ARROW;
		}
		else if (pPP2->curtokpp->symbol == '++')
		{
			return PLUSPLUS;
		}
		else if (pPP2->curtokpp->symbol == '--')
		{
			return MINUSMINUS;
		}
		else if (pPP2->curtokpp->symbol == '::')
		{
			return TWO_COLON;
		}
		else if (pPP2->curtokpp->symbol == '<=')
		{
			return LEQ;
		}
		else if (pPP2->curtokpp->symbol == '>=')
		{
			return GEQ;
		}
		else if (pPP2->curtokpp->symbol == '&&')
		{
			return LAND;
		}
		else if (pPP2->curtokpp->symbol == '||')
		{
			return LOR;
		}
		else if (pPP2->curtokpp->symbol == '.*')
		{
			return DOT_STAR;
		}
		else if (pPP2->curtokpp->symbol == '->*')
		{
			return ARROW_STAR;
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

void cpp_error (/*YYLTYPE *llocp,*/ char const *s);
/*#define YYERROR_VERBOSE*/

#define yyfalse	0
#define yytrue		1

union YYSTYPE;

A_Stm* stmtMerge (YYSTYPE& x0, YYSTYPE& x1);
//A_Declaration* Merge (YYSTYPE& x0, YYSTYPE& x1);

A_DeclarationList* translation_unit;

//A_Type* gType;


     

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
#line 357 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
typedef union YYSTYPE {
int num;
char* id;
char* string_literal;
A_ClassKey classKey;
A_ClassHead* classHead;
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
/*A_TypeSpecList* typespecList;*/
A_DeclSpec* declspec;
A_DeclSpec* typespec;
A_DeclSpecList* declspecList;
A_ParameterDeclarations* paramDecls;
A_EnumDefinition* enumDef;
A_EnumDefList* enumList;
A_BaseSpecifierList* baseSpecifierList;
} YYSTYPE;
/* Line 188 of glr.c.  */
#line 671 "c:\\mmstudio\\src\\ljavac\\cpp_parse.tab.c"
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
#line 700 "c:\\mmstudio\\src\\ljavac\\cpp_parse.tab.c"

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
#define YYFINAL  154
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7374

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  164
/* YYNRULES -- Number of rules. */
#define YYNRULES  453
/* YYNRULES -- Number of states. */
#define YYNSTATES  737
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule. */
#define YYMAXRHS 8

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   360

#define YYTRANSLATE(YYX) 						\
  ((YYX <= 0) ? YYEOF :							\
   (unsigned)(YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   110,     2,     2,     2,   116,     2,     2,
     106,   107,     2,   113,   120,   114,   119,   115,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   123,   124,
     112,   109,   111,   122,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   117,     2,   118,   121,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   125,     2,   126,   108,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    25,    27,    29,    31,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    54,    56,    58,    60,
      62,    64,    66,    68,    70,    72,    74,    76,    78,    80,
      82,    84,    86,    88,    90,    93,    96,    97,    99,   101,
     103,   105,   108,   110,   114,   117,   120,   121,   123,   126,
     129,   132,   133,   135,   139,   140,   142,   144,   149,   154,
     159,   162,   165,   169,   173,   175,   179,   180,   182,   184,
     187,   190,   193,   196,   199,   202,   205,   208,   211,   216,
     218,   220,   226,   234,   238,   239,   241,   244,   247,   249,
     250,   252,   256,   261,   265,   266,   268,   272,   278,   280,
     285,   287,   291,   295,   297,   301,   305,   309,   311,   315,
     319,   321,   325,   329,   331,   335,   339,   343,   347,   349,
     353,   357,   359,   363,   365,   369,   371,   375,   377,   381,
     383,   387,   389,   395,   397,   399,   401,   403,   405,   407,
     409,   411,   413,   415,   417,   419,   423,   425,   426,   428,
     431,   433,   437,   438,   440,   442,   443,   445,   447,   449,
     451,   453,   455,   457,   459,   461,   466,   470,   474,   476,
     479,   485,   488,   492,   495,   499,   501,   504,   506,   509,
     512,   514,   516,   519,   521,   524,   530,   538,   544,   546,
     547,   549,   555,   563,   572,   574,   576,   579,   583,   585,
     587,   590,   591,   593,   595,   597,   599,   601,   603,   605,
     606,   608,   615,   617,   621,   623,   625,   628,   633,   636,
     641,   648,   657,   662,   664,   666,   670,   671,   673,   675,
     677,   679,   684,   690,   694,   696,   702,   704,   706,   708,
     709,   711,   718,   724,   729,   731,   733,   736,   738,   741,
     745,   750,   756,   763,   771,   780,   782,   785,   787,   789,
     791,   793,   795,   797,   799,   801,   803,   805,   810,   812,
     814,   816,   818,   820,   822,   824,   826,   828,   830,   832,
     834,   836,   838,   840,   842,   844,   846,   848,   850,   852,
     854,   856,   858,   860,   863,   867,   872,   875,   881,   882,
     884,   886,   889,   893,   894,   896,   898,   902,   905,   907,
     911,   916,   919,   920,   922,   924,   928,   933,   939,   946,
     954,   956,   960,   961,   963,   968,   969,   971,   973,   976,
     980,   982,   986,   988,   991,   994,   998,   999,  1001,  1003,
    1008,  1011,  1013,  1017,  1019,  1022,  1024,  1026,  1033,  1038,
    1042,  1044,  1047,  1050,  1054,  1059,  1065,  1067,  1070,  1071,
    1073,  1080,  1085,  1089,  1090,  1092,  1094,  1097,  1101,  1103,
    1107,  1108,  1110,  1112,  1116,  1118,  1122,  1124,  1127,  1131,
    1136,  1142,  1144,  1147,  1151,  1156,  1162,  1165,  1167,  1170,
    1175,  1177,  1179,  1181,  1183,  1185,  1188,  1189,  1191,  1193,
    1195,  1200,  1202,  1204,  1206,  1208,  1210,  1212,  1213,  1215,
    1217,  1221,  1226,  1231,  1234,  1238,  1240,  1243,  1247,  1252,
    1258,  1265,  1267,  1269,  1271,  1273,  1277,  1278,  1280,  1283,
    1287,  1288,  1291,  1292,  1294,  1297,  1298,  1300,  1302,  1306,
    1309,  1314,  1319,  1320
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     128,     0,    -1,   197,    -1,    62,    -1,    63,    -1,   103,
      -1,   104,    -1,   101,    -1,   102,    -1,   129,    -1,   105,
      -1,   106,   175,   107,    -1,   131,    -1,   135,    -1,   136,
      -1,    99,   133,    -1,   108,    -1,    97,    -1,    98,    -1,
     109,    -1,   110,    -1,   111,    -1,   112,    -1,   113,    -1,
     114,    -1,    22,    -1,   115,    -1,   116,    -1,     8,    -1,
       9,    -1,    20,    -1,    21,    -1,     5,    -1,     6,    -1,
      93,    -1,    94,    -1,    10,    -1,    11,    -1,    15,    -1,
      16,    -1,    17,    -1,    18,    -1,    19,    -1,     7,    -1,
     117,   118,    -1,   106,   107,    -1,    -1,    83,    -1,     3,
      -1,   132,    -1,   138,    -1,   108,   272,    -1,   204,    -1,
     142,   134,   135,    -1,    95,     3,    -1,    95,   132,    -1,
      -1,    95,    -1,    99,   139,    -1,   226,   141,    -1,   267,
     141,    -1,    -1,   140,    -1,   223,    95,   143,    -1,    -1,
     142,    -1,   130,    -1,   144,   117,   175,   118,    -1,   144,
     106,   146,   107,    -1,   224,   106,   146,   107,    -1,   144,
       5,    -1,   144,     6,    -1,   144,   119,   131,    -1,   144,
       7,   131,    -1,   172,    -1,   145,   120,   172,    -1,    -1,
     145,    -1,   144,    -1,     5,   158,    -1,     6,   158,    -1,
      22,   158,    -1,    23,   158,    -1,   113,   158,    -1,   114,
     158,    -1,   110,   158,    -1,   108,   158,    -1,   100,   147,
      -1,   100,   106,   256,   107,    -1,   148,    -1,   157,    -1,
     137,    97,   150,   151,   156,    -1,   137,    97,   150,   106,
     256,   107,   156,    -1,   106,   145,   107,    -1,    -1,   149,
      -1,   226,   153,    -1,   267,   153,    -1,   154,    -1,    -1,
     152,    -1,   117,   175,   118,    -1,   154,   117,   177,   118,
      -1,   106,   146,   107,    -1,    -1,   155,    -1,   137,    98,
     158,    -1,   137,    98,   117,   118,   158,    -1,   147,    -1,
     106,   256,   107,   158,    -1,   158,    -1,   159,    27,   158,
      -1,   159,    28,   158,    -1,   159,    -1,   160,    22,   159,
      -1,   160,   115,   159,    -1,   160,   116,   159,    -1,   160,
      -1,   161,   113,   160,    -1,   161,   114,   160,    -1,   161,
      -1,   162,    93,   161,    -1,   162,    94,   161,    -1,   162,
      -1,   163,   112,   162,    -1,   163,   111,   162,    -1,   163,
      20,   162,    -1,   163,    21,   162,    -1,   163,    -1,   164,
       8,   163,    -1,   164,     9,   163,    -1,   164,    -1,   165,
      23,   164,    -1,   165,    -1,   166,   121,   165,    -1,   166,
      -1,   167,    24,   166,    -1,   167,    -1,   168,    25,   167,
      -1,   168,    -1,   169,    26,   168,    -1,   169,    -1,   169,
     122,   175,   123,   172,    -1,   109,    -1,    10,    -1,    11,
      -1,    12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,
      -1,    17,    -1,    18,    -1,    19,    -1,   170,    -1,   169,
     171,   172,    -1,   174,    -1,    -1,   172,    -1,    70,   173,
      -1,   172,    -1,   175,   120,   172,    -1,    -1,   175,    -1,
     170,    -1,    -1,   170,    -1,   186,    -1,   180,    -1,   245,
      -1,   189,    -1,   192,    -1,   185,    -1,   194,    -1,   181,
      -1,    35,   177,   123,   179,    -1,    36,   123,   179,    -1,
      69,   245,   182,    -1,   183,    -1,   183,   182,    -1,    71,
     106,   184,   107,   245,    -1,   225,   252,    -1,   225,   225,
     252,    -1,   225,   257,    -1,   225,   225,   257,    -1,   225,
      -1,   225,   225,    -1,    96,    -1,    39,   124,    -1,    38,
     124,    -1,   195,    -1,   187,    -1,   175,   124,    -1,   179,
      -1,   179,   188,    -1,    32,   106,   190,   107,   179,    -1,
      32,   106,   190,   107,   179,    33,   179,    -1,    34,   106,
     190,   107,   179,    -1,   175,    -1,    -1,   190,    -1,    42,
     106,   190,   107,   179,    -1,    41,   179,    42,   106,   175,
     107,   124,    -1,    40,   106,   193,   191,   124,   176,   107,
     179,    -1,   187,    -1,   216,    -1,    68,   124,    -1,    68,
     175,   124,    -1,   213,    -1,   198,    -1,   198,   196,    -1,
      -1,   196,    -1,   213,    -1,   238,    -1,   210,    -1,   209,
      -1,   211,    -1,   200,    -1,    -1,    84,    -1,   199,    83,
     112,   201,   111,   198,    -1,   202,    -1,   201,   120,   202,
      -1,   203,    -1,   264,    -1,    48,   229,    -1,    48,   229,
     109,   256,    -1,    46,   229,    -1,    46,   229,   109,   256,
      -1,    83,   112,   201,   111,    48,   229,    -1,    83,   112,
     201,   111,    48,   229,   109,   131,    -1,   205,   112,   207,
     111,    -1,     3,    -1,   208,    -1,   206,   120,   208,    -1,
      -1,   206,    -1,   172,    -1,   256,    -1,   131,    -1,    83,
     112,   111,   198,    -1,    31,   101,   125,   197,   126,    -1,
      31,   101,   198,    -1,   212,    -1,    29,     3,   125,   197,
     126,    -1,   216,    -1,   215,    -1,    89,    -1,    -1,    46,
      -1,    30,   214,    95,   142,   135,   124,    -1,    30,   214,
     142,   135,   124,    -1,    30,    95,   135,   124,    -1,   217,
      -1,   124,    -1,   219,   124,    -1,   218,    -1,   246,   124,
      -1,   220,   246,   124,    -1,   220,   220,   246,   124,    -1,
     220,   220,   220,   246,   124,    -1,   220,   220,   220,   220,
     246,   124,    -1,   220,   220,   220,   220,   220,   246,   124,
      -1,   220,   220,   220,   220,   220,   220,   246,   124,    -1,
     220,    -1,   219,   220,    -1,   221,    -1,   225,    -1,   222,
      -1,    61,    -1,    45,    -1,    54,    -1,    55,    -1,    56,
      -1,    31,    -1,    57,    -1,    88,   106,     3,   107,    -1,
      58,    -1,    59,    -1,    60,    -1,     3,    -1,   204,    -1,
     223,    -1,    95,    -1,    72,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    85,    -1,    77,    -1,    78,    -1,
      79,    -1,    80,    -1,    81,    -1,    82,    -1,   224,    -1,
     227,    -1,   273,    -1,   228,    -1,   269,    -1,   225,    -1,
     226,   225,    -1,   274,   143,     3,    -1,   274,   143,   134,
     204,    -1,    46,     3,    -1,    47,   229,   125,   231,   126,
      -1,    -1,     3,    -1,   232,    -1,   230,   120,    -1,   230,
     120,   232,    -1,    -1,   230,    -1,     3,    -1,     3,   109,
     177,    -1,   123,   234,    -1,   235,    -1,   235,   120,   234,
      -1,   236,   106,   146,   107,    -1,   143,   272,    -1,    -1,
     233,    -1,   239,    -1,   252,   237,   244,    -1,   220,   252,
     237,   244,    -1,   220,   220,   252,   237,   244,    -1,   220,
     220,   220,   252,   237,   244,    -1,   220,   220,   220,   220,
     252,   237,   244,    -1,   256,    -1,   240,   120,   256,    -1,
      -1,   240,    -1,    70,   106,   241,   107,    -1,    -1,   242,
      -1,   245,    -1,   125,   126,    -1,   125,   188,   126,    -1,
     247,    -1,   246,   120,   247,    -1,   252,    -1,   252,   248,
      -1,   109,   250,    -1,   106,   145,   107,    -1,    -1,   120,
      -1,   172,    -1,   125,   251,   249,   126,    -1,   125,   126,
      -1,   250,    -1,   251,   120,   250,    -1,   253,    -1,   267,
     252,    -1,   254,    -1,   255,    -1,   253,   106,   261,   107,
     271,   243,    -1,   253,   117,   178,   118,    -1,   106,   252,
     107,    -1,   131,    -1,    95,   142,    -1,   225,   258,    -1,
     225,   225,   258,    -1,   225,   225,   225,   258,    -1,   225,
     225,   225,   225,   258,    -1,   259,    -1,   267,   258,    -1,
      -1,   257,    -1,   260,   106,   261,   107,   271,   243,    -1,
     260,   117,   178,   118,    -1,   106,   257,   107,    -1,    -1,
     259,    -1,   263,    -1,   263,    96,    -1,   262,   120,    96,
      -1,   264,    -1,   262,   120,   264,    -1,    -1,   262,    -1,
     265,    -1,   265,   109,   172,    -1,   266,    -1,   266,   109,
     172,    -1,   219,    -1,   220,   252,    -1,   220,   220,   252,
      -1,   220,   220,   220,   252,    -1,   220,   220,   220,   220,
     252,    -1,   219,    -1,   220,   257,    -1,   220,   220,   257,
      -1,   220,   220,   220,   257,    -1,   220,   220,   220,   220,
     257,    -1,    22,   271,    -1,    23,    -1,   268,   271,    -1,
     137,   142,    22,   271,    -1,    87,    -1,    86,    -1,    43,
      -1,    44,    -1,   269,    -1,   269,   270,    -1,    -1,   270,
      -1,     3,    -1,   204,    -1,   277,   125,   285,   126,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    -1,   275,    -1,   274,    -1,   274,     3,   287,
      -1,   274,   142,     3,   287,    -1,   274,   143,   204,   287,
      -1,   280,   285,    -1,   275,   123,   285,    -1,   124,    -1,
     281,   124,    -1,   220,   282,   124,    -1,   220,   220,   282,
     124,    -1,   220,   220,   220,   282,   124,    -1,   220,   220,
     220,   220,   282,   124,    -1,   279,    -1,   238,    -1,   200,
      -1,   283,    -1,   281,   120,   283,    -1,    -1,   281,    -1,
     252,   284,    -1,   229,   123,   177,    -1,    -1,   109,   177,
      -1,    -1,   278,    -1,   123,   288,    -1,    -1,   286,    -1,
     289,    -1,   288,   120,   289,    -1,   143,   272,    -1,    59,
     276,   143,   272,    -1,   275,   290,   143,   272,    -1,    -1,
      59,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   647,   647,   655,   656,   657,   658,   659,   660,   663,
     664,   665,   666,   669,   670,   673,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   688,   689,   690,
     691,   692,   693,   694,   695,   696,   697,   698,   699,   700,
     701,   702,   703,   704,   705,   706,   709,   710,   713,   714,
     715,   716,   717,   722,   723,   724,   736,   737,   740,   743,
     746,   749,   750,   759,   763,   764,   767,   768,   769,   770,
     771,   772,   773,   774,   778,   779,   782,   783,   786,   787,
     788,   789,   790,   791,   792,   793,   794,   795,   796,   797,
     798,   801,   802,   805,   808,   809,   812,   814,   815,   818,
     819,   822,   823,   825,   828,   829,   832,   833,   836,   837,
     840,   841,   842,   845,   846,   847,   848,   851,   852,   853,
     856,   857,   858,   861,   862,   863,   864,   865,   868,   869,
     870,   873,   874,   877,   878,   881,   882,   885,   886,   889,
     890,   893,   894,   897,   898,   899,   900,   901,   902,   903,
     904,   905,   906,   907,   910,   911,   912,   915,   916,   919,
     923,   924,   927,   928,   931,   934,   935,   939,   940,   941,
     942,   943,   944,   945,   946,   949,   950,   953,   956,   957,
     960,   963,   964,   965,   966,   967,   968,   969,   976,   977,
     980,   981,   984,   987,   988,   992,   993,   994,   997,  1001,
    1002,  1005,  1006,  1007,  1011,  1012,  1015,  1016,  1020,  1026,
    1027,  1036,  1037,  1040,  1041,  1042,  1043,  1044,  1045,  1048,
    1049,  1052,  1055,  1056,  1059,  1060,  1063,  1064,  1065,  1066,
    1067,  1068,  1071,  1074,  1077,  1078,  1081,  1082,  1085,  1086,
    1087,  1095,  1098,  1099,  1102,  1106,  1112,  1113,  1114,  1154,
    1155,  1158,  1159,  1160,  1163,  1176,  1177,  1181,  1184,  1185,
    1186,  1187,  1188,  1189,  1190,  1193,  1194,  1203,  1204,  1205,
    1206,  1207,  1266,  1267,  1268,  1269,  1270,  1271,  1274,  1275,
    1276,  1307,  1308,  1311,  1312,  1319,  1320,  1321,  1322,  1323,
    1324,  1325,  1326,  1327,  1328,  1329,  1330,  1338,  1339,  1340,
    1341,  1342,  1348,  1349,  1359,  1360,  1361,  1364,  1367,  1368,
    1371,  1372,  1373,  1376,  1377,  1380,  1381,  1384,  1387,  1388,
    1391,  1394,  1397,  1398,  1401,  1408,  1409,  1410,  1411,  1412,
    1418,  1419,  1422,  1423,  1426,  1429,  1430,  1450,  1453,  1454,
    1459,  1460,  1467,  1468,  1475,  1476,  1479,  1480,  1483,  1484,
    1485,  1488,  1489,  1492,  1493,  1497,  1502,  1503,  1504,  1505,
    1526,  1530,  1533,  1534,  1535,  1536,  1556,  1557,  1560,  1561,
    1564,  1565,  1566,  1569,  1570,  1573,  1574,  1575,  1582,  1583,
    1586,  1587,  1593,  1594,  1595,  1596,  1609,  1610,  1611,  1612,
    1613,  1616,  1617,  1618,  1619,  1620,  1623,  1624,  1625,  1626,
    1629,  1630,  1633,  1634,  1637,  1638,  1641,  1642,  1647,  1648,
    1652,  1655,  1656,  1657,  1660,  1661,  1662,  1665,  1666,  1669,
    1670,  1671,  1672,  1675,  1676,  1679,  1680,  1681,  1682,  1683,
    1684,  1697,  1699,  1704,  1707,  1708,  1711,  1712,  1716,  1717,
    1729,  1730,  1739,  1740,  1745,  1748,  1749,  1752,  1753,  1756,
    1757,  1758,  1761,  1762
};
#endif

#if (YYDEBUG) || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "identifier", "identifier_lparen", 
  "PLUSPLUS", "MINUSMINUS", "ARROW", "EQUAL", "NOT_EQUAL", "ASSIGN_PLUS", 
  "ASSIGN_MINUS", "ASSIGN_OR", "ASSIGN_XOR", "ASSIGN_AND", "ASSIGN_MUL", 
  "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_LSHIFT", "ASSIGN_RSHIFT", "LEQ", 
  "GEQ", "STAR", "BITAND", "BITOR", "LAND", "LOR", "DOT_STAR", 
  "ARROW_STAR", "NAMESPACE_KW", "USING_KW", "EXTERN_KW", "IF_KW", 
  "ELSE_KW", "SWITCH_KW", "CASE_KW", "DEFAULT_KW", "GOTO_KW", "BREAK_KW", 
  "CONTINUE_KW", "FOR_KW", "DO_KW", "WHILE_KW", "CONST_KW", "VOLATILE_KW", 
  "TYPEDEF_KW", "TYPENAME_KW", "ENUM_KW", "CLASS_KW", "STRUCT_KW", 
  "UNION_KW", "PRIVATE_KW", "PROTECTED_KW", "PUBLIC_KW", "AUTO_KW", 
  "REGISTER_KW", "STATIC_KW", "MUTABLE_KW", "INLINE_KW", "VIRTUAL_KW", 
  "EXPLICIT_KW", "FRIEND_KW", "FALSE_KW", "TRUE_KW", "STATIC_CAST_KW", 
  "REINTERPRET_CAST_KW", "DYNAMIC_CAST_KW", "CONST_CAST_KW", "RETURN_KW", 
  "TRY_KW", "THROW_KW", "CATCH_KW", "CHAR_KW", "WCHAR_T_KW", "BOOL_KW", 
  "SHORT_KW", "INT_KW", "LONG_KW", "SIGNED_KW", "UNSIGNED_KW", "FLOAT_KW", 
  "DOUBLE_KW", "VOID_KW", "TEMPLATE_KW", "EXPORT_KW", "__INT64_KW", 
  "__CDECL_KW", "__STDCALL_KW", "__DECLSPEC_KW", "__ASM_KW", 
  "__SAVEDS_KW", "__INTERRUPT_KW", "__CHIP_KW", "LSHIFT", "RSHIFT", 
  "TWO_COLON", "THREE_DOTS", "NEW_KW", "DELETE_KW", "OPERATOR_KW", 
  "SIZEOF_KW", "STRING_LITERAL", "LSTRING_LITERAL", "INTEGER_LITERAL", 
  "DOUBLE_LITERAL", "THIS_KW", "'('", "')'", "'~'", "'='", "'!'", "'>'", 
  "'<'", "'+'", "'-'", "'/'", "'%'", "'['", "']'", "'.'", "','", "'^'", 
  "'?'", "':'", "';'", "'{'", "'}'", "$accept", "translation_unit", 
  "literal", "primary_expression", "id_expression", 
  "operator_function_id", "_operator", "template_opt", "unqualified_id", 
  "qualified_id", "TWO_COLON_opt", "conversion_function_id", 
  "conversion_type_id", "conversion_declarator", 
  "conversion_declarator_opt", "nested_name_specifier", 
  "nested_name_specifier_opt", "postfix_expression", "expression_list", 
  "expression_list_opt", "unary_expression", "new_expression", 
  "new_placement", "new_placement_opt", "new_type_id", "new_declarator", 
  "new_declarator_opt", "direct_new_declarator", "new_initializer", 
  "new_initializer_opt", "delete_expression", "cast_expression", 
  "pm_expression", "multiplicative_expression", "additive_expression", 
  "shift_expression", "relational_expression", "equality_expression", 
  "and_expression", "exclusive_or_expression", "inclusive_or_expression", 
  "logical_and_expression", "logical_or_expression", 
  "conditional_expression", "assignment_operator", 
  "assignment_expression", "assignment_expression_opt", 
  "throw_expression", "expression", "expression_opt", 
  "constant_expression", "constant_expression_opt", "statement", 
  "labeled_statement", "try_block", "handler_seq", "handler", 
  "exception_declaration", "jump_statement", "expression_or_declaration", 
  "expression_statement", "statement_seq", "selection_statement", 
  "condition", "condition_opt", "iteration_statement", 
  "for_init_statement", "return_statement", "declaration_statement", 
  "declaration_seq", "declaration_seq_opt", "declaration", "export_opt", 
  "template_declaration", "template_parameter_list", "template_parameter", 
  "type_parameter", "template_id", "template_name", 
  "template_argument_list", "template_argument_list_opt", 
  "template_argument", "explicit_specialization", "linkage_specification", 
  "namespace_definition", "named_namespace_definition", 
  "block_declaration", "typename_opt", "using_declaration", 
  "simple_declaration", "simple_declaration1", "simple_declaration2", 
  "decl_specifier_seq", "decl_specifier", "storage_class_specifier", 
  "function_specifier", "type_name", "simple_type_specifier", 
  "type_specifier", "type_specifier_seq", "elaborated_type_specifier", 
  "enum_specifier", "identifier_opt", "enumerator_list", 
  "enumerator_list_opt", "enumerator_definition", "ctor_initializer", 
  "mem_initializer_list", "mem_initializer", "mem_initializer_id", 
  "ctor_initializer_opt", "function_definition", "function_definition1", 
  "type_id_list", "type_id_list_opt", "exception_specification", 
  "exception_specification_opt", "function_body", "compound_statement", 
  "init_declarator_list", "init_declarator", "initializer", "COMMA_opt", 
  "initializer_clause", "initializer_list", "declarator", 
  "direct_declarator", "direct_declarator1", "declarator_id", "type_id", 
  "abstract_declarator", "abstract_declarator_opt", 
  "direct_abstract_declarator", "direct_abstract_declarator_opt", 
  "parameter_declaration_clause", "parameter_declaration_list", 
  "parameter_declaration_list_opt", "parameter_declaration", 
  "parameter_declaration1", "parameter_declaration2", "ptr_operator", 
  "cc_qualifier", "cv_qualifier", "cv_qualifier_seq", 
  "cv_qualifier_seq_opt", "class_name", "class_specifier", "class_key", 
  "access_specifier", "access_specifier_opt", "class_head", 
  "member_specification", "member_declaration_decl", "member_declaration", 
  "member_declarator_list", "member_declarator_list_opt", 
  "member_declarator", "constant_initializer_opt", 
  "member_specification_opt", "base_clause", "base_clause_opt", 
  "base_specifier_list", "base_specifier", "virtual_opt", 0
};

#define yytname_size ((int) (sizeof (yytname) / sizeof (yytname[0])))
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short yyr1[] =
{
       0,   127,   128,   129,   129,   129,   129,   129,   129,   130,
     130,   130,   130,   131,   131,   132,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   134,   134,   135,   135,
     135,   135,   135,   136,   136,   136,   137,   137,   138,   139,
     140,   141,   141,   142,   143,   143,   144,   144,   144,   144,
     144,   144,   144,   144,   145,   145,   146,   146,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   148,   148,   149,   150,   150,   151,   152,   152,   153,
     153,   154,   154,   155,   156,   156,   157,   157,   158,   158,
     159,   159,   159,   160,   160,   160,   160,   161,   161,   161,
     162,   162,   162,   163,   163,   163,   163,   163,   164,   164,
     164,   165,   165,   166,   166,   167,   167,   168,   168,   169,
     169,   170,   170,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   172,   172,   172,   173,   173,   174,
     175,   175,   176,   176,   177,   178,   178,   179,   179,   179,
     179,   179,   179,   179,   179,   180,   180,   181,   182,   182,
     183,   184,   184,   184,   184,   184,   184,   184,   185,   185,
     186,   186,   187,   188,   188,   189,   189,   189,   190,   191,
     191,   192,   192,   192,   193,   193,   194,   194,   195,   196,
     196,   197,   197,   198,   198,   198,   198,   198,   198,   199,
     199,   200,   201,   201,   202,   202,   203,   203,   203,   203,
     203,   203,   204,   205,   206,   206,   207,   207,   208,   208,
     208,   209,   210,   210,   211,   212,   213,   213,   213,   214,
     214,   215,   215,   215,   216,   217,   217,   217,   218,   218,
     218,   218,   218,   218,   218,   219,   219,   220,   220,   220,
     220,   220,   221,   221,   221,   221,   221,   221,   222,   222,
     222,   223,   223,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   225,   225,   225,
     225,   225,   226,   226,   227,   227,   227,   228,   229,   229,
     230,   230,   230,   231,   231,   232,   232,   233,   234,   234,
     235,   236,   237,   237,   238,   239,   239,   239,   239,   239,
     240,   240,   241,   241,   242,   243,   243,   244,   245,   245,
     246,   246,   247,   247,   248,   248,   249,   249,   250,   250,
     250,   251,   251,   252,   252,   253,   254,   254,   254,   254,
     255,   255,   256,   256,   256,   256,   257,   257,   258,   258,
     259,   259,   259,   260,   260,   261,   261,   261,   262,   262,
     263,   263,   264,   264,   264,   264,   265,   265,   265,   265,
     265,   266,   266,   266,   266,   266,   267,   267,   267,   267,
     268,   268,   269,   269,   270,   270,   271,   271,   272,   272,
     273,   274,   274,   274,   275,   275,   275,   276,   276,   277,
     277,   277,   277,   278,   278,   279,   279,   279,   279,   279,
     279,   280,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   287,   287,   288,   288,   289,
     289,   289,   290,   290
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     0,     1,     1,     1,
       1,     2,     1,     3,     2,     2,     0,     1,     2,     2,
       2,     0,     1,     3,     0,     1,     1,     4,     4,     4,
       2,     2,     3,     3,     1,     3,     0,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     1,
       1,     5,     7,     3,     0,     1,     2,     2,     1,     0,
       1,     3,     4,     3,     0,     1,     3,     5,     1,     4,
       1,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     1,     2,
       1,     3,     0,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     3,     1,     2,
       5,     2,     3,     2,     3,     1,     2,     1,     2,     2,
       1,     1,     2,     1,     2,     5,     7,     5,     1,     0,
       1,     5,     7,     8,     1,     1,     2,     3,     1,     1,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     6,     1,     3,     1,     1,     2,     4,     2,     4,
       6,     8,     4,     1,     1,     3,     0,     1,     1,     1,
       1,     4,     5,     3,     1,     5,     1,     1,     1,     0,
       1,     6,     5,     4,     1,     1,     2,     1,     2,     3,
       4,     5,     6,     7,     8,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     4,     2,     5,     0,     1,
       1,     2,     3,     0,     1,     1,     3,     2,     1,     3,
       4,     2,     0,     1,     1,     3,     4,     5,     6,     7,
       1,     3,     0,     1,     4,     0,     1,     1,     2,     3,
       1,     3,     1,     2,     2,     3,     0,     1,     1,     4,
       2,     1,     3,     1,     2,     1,     1,     6,     4,     3,
       1,     2,     2,     3,     4,     5,     1,     2,     0,     1,
       6,     4,     3,     0,     1,     1,     2,     3,     1,     3,
       0,     1,     1,     3,     1,     3,     1,     2,     3,     4,
       5,     1,     2,     3,     4,     5,     2,     1,     2,     4,
       1,     1,     1,     1,     1,     2,     0,     1,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       3,     4,     4,     2,     3,     1,     2,     3,     4,     5,
       6,     1,     1,     1,     1,     3,     0,     1,     2,     3,
       0,     2,     0,     1,     2,     0,     1,     1,     3,     2,
       4,     4,     0,     1
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
       0,     0,     0,     1,     0,     0,     0,     0,     1,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     0,
       0,     0,     0,     0,     0,     0,     1,     1,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       0,     0,     0,     1,     2,     2,     2,     1,     2,     2,
       0,     0,     0,     1,     2,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     0,     0,     0,
       1,     2,     0,     0,     0,     1,     2,     0,     0,     0,
       0,     0,     0,     0,     1,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     2,     1,     2,
       3,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     1,
       0,     0,     0,     0,     0,     1,     2,     3,     4,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     1,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     1,
       0,     0,     1,     1,     2,     2,     0,     1,     2,     3,
       4,     0,     1,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     2,     3,     4,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
static const unsigned short yydefact[] =
{
     211,    48,   406,   397,     0,   249,   275,   402,   403,   271,
       0,   308,   411,   412,   413,   272,   273,   274,   276,   278,
     279,   280,   270,   285,   286,   287,   288,   289,   291,   292,
     293,   294,   295,   296,     0,   220,   290,   401,   400,     0,
     248,   284,     0,     0,     0,   255,     0,   360,    49,    13,
      14,     0,    50,    46,   212,     2,   209,     0,   218,    52,
       0,   216,   215,   217,   244,   213,   247,   246,   254,   257,
       0,   265,   267,   269,   283,   297,   268,   298,   300,   214,
     324,     0,   340,   342,   353,   355,   356,     0,   406,   301,
     299,    64,     0,   404,   407,   396,     0,   250,     0,     0,
       0,   306,   309,     0,     0,     0,    54,     0,    55,   361,
     282,     0,   281,    32,    33,    43,    28,    29,    36,    37,
      38,    39,    40,    41,    42,    30,    31,    25,    34,    35,
     284,    17,    18,     0,    16,    19,    20,    21,    22,    23,
      24,    26,    27,     0,    15,    58,   283,   302,    61,     0,
       0,   408,   409,    51,     1,     0,    47,     0,   210,     0,
      56,   275,   256,   266,     0,     0,   342,    64,     0,   258,
      56,    56,     0,   323,     0,   343,   380,    56,   354,   398,
     233,    65,     0,   219,   405,   211,    48,     0,    52,     0,
       0,   211,   243,   313,     0,     0,    45,    44,   284,    62,
      59,   303,    61,   359,   406,    53,     0,    56,    56,    56,
      56,     3,     4,   157,   284,    56,     7,     8,     5,     6,
      10,    56,    56,    56,    56,    56,     9,    66,    12,     0,
      78,   108,    89,    90,   110,   113,   117,   120,   123,   128,
     131,   133,   135,   137,   139,   141,   154,   238,   156,   237,
       0,   234,   297,   368,   239,     0,     0,   342,   259,     0,
      65,    63,   341,   342,    12,     0,    74,     0,    56,   348,
     344,     0,   317,   318,     0,    56,   325,   337,   386,   265,
       0,   381,   375,   378,   382,   384,   141,   166,     0,     0,
     446,   420,   445,   304,     0,   445,   281,   414,   415,   416,
     425,   433,   308,     0,   432,   440,     0,   443,   431,   219,
       0,   434,     0,     0,   253,     0,     0,     0,   315,   314,
       0,   310,   241,   277,    57,    60,   399,   308,   308,     0,
       0,   222,   224,   225,    79,    80,    81,    82,   158,   159,
      54,    56,    87,   160,     0,     0,    48,    86,    52,    85,
      83,    84,    94,    56,    70,    71,     0,    56,    56,     0,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,    56,
     143,    56,    56,    56,   232,    56,    56,   368,   369,   362,
     366,     0,   368,     0,     0,   342,   260,     0,   326,   345,
      56,   350,   351,   346,   321,     0,    56,    56,    56,     0,
       0,    56,     0,     0,     0,     0,    56,     0,    56,     0,
      56,   338,    12,     0,     0,    56,   168,   174,   172,   167,
     191,     0,   170,   171,   173,   190,   208,   265,   169,   373,
     373,   387,   392,   368,   406,     0,   376,    56,    56,   358,
     417,     0,   452,   444,   447,   421,   233,   305,   422,   308,
     440,   437,     0,    56,    56,   438,   219,   423,   308,   426,
     410,   245,     0,   252,   242,    56,   311,   307,   306,   228,
     226,     0,     0,     0,     0,    11,    56,    56,    56,    95,
       0,     0,   106,     0,    73,    77,     0,     0,    72,   111,
     112,   114,   115,   116,   118,   119,   121,   122,   126,   127,
     125,   124,   129,   130,   132,   134,   136,   138,   140,     0,
     155,   235,     0,     0,   368,   363,   380,    56,   367,     0,
       0,   342,   261,     0,   327,    75,    56,     0,   319,     0,
      56,    56,   164,     0,    56,   189,   188,    56,     0,    56,
     206,     0,     0,   192,   194,   339,     0,   373,   388,   393,
     335,   377,   379,   383,   385,   418,     0,   449,   453,     0,
       0,   308,   440,     0,   427,   439,   441,   424,   440,   435,
     251,   316,   312,     0,     0,     0,   221,   223,    88,   161,
     109,     0,     0,   104,    99,    56,    68,    67,    56,    69,
     372,   368,   364,     0,     0,     0,     0,   262,     0,   328,
     352,   349,   320,   198,     0,     0,    56,   176,   204,    56,
     205,     0,     0,   207,     0,   177,   178,     0,   373,   389,
     394,     0,   336,   357,     0,     0,   448,   308,   440,     0,
     428,   229,   227,     0,    93,     0,    56,   105,    91,    56,
     100,    96,    98,    99,   107,   142,   365,   406,   371,     0,
     263,   329,    56,    56,   175,   200,     0,    56,    56,     0,
     179,     0,   390,   395,   332,   450,   451,   440,     0,   429,
     308,   104,     0,     0,    56,    97,   335,   264,   195,   197,
      56,     0,   201,   187,     0,   185,   333,     0,   330,   430,
     230,    92,   103,   101,     0,   370,    56,   163,     0,     0,
       0,   186,   181,   183,     0,   334,     0,   102,   196,    56,
     202,   180,   182,   184,   331,   231,   203
};

/* YYPDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    46,   226,   227,   264,    48,   144,   157,    49,    50,
     229,    52,   145,   199,   200,    53,   271,   230,   505,   506,
     231,   232,   499,   500,   603,   660,   661,   662,   657,   658,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   392,   343,   339,   248,   434,   718,
     553,   288,   435,   436,   437,   635,   636,   704,   438,   439,
     440,   441,   442,   624,   676,   443,   629,   444,   445,    54,
      55,    56,    57,    58,   330,   331,   332,    59,    60,   249,
     250,   251,    61,    62,    63,    64,   446,    99,    66,    67,
      68,    69,    70,   447,    72,    73,    74,   267,    76,   148,
      77,    78,   303,   319,   320,   321,   173,   272,   273,   274,
     174,    79,    80,   706,   707,   642,   643,   276,   448,    81,
      82,   175,   547,   270,   413,   263,    84,    85,    86,   254,
     398,   538,   400,   401,   280,   281,   282,   333,   284,   285,
      87,    88,    89,    94,    95,   153,    90,    91,   306,   576,
      92,   307,   308,   309,   471,   472,   311,   475,   312,   290,
     291,   463,   464,   579
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -519
static const short yypact[] =
{
    3399,  3486,   184,  -519,    59,    -6,   -44,  -519,  -519,  -519,
     156,   185,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,    37,  -519,  -519,  -519,  -519,    89,
    -519,    72,  4804,   905,   219,  -519,    90,  -519,  -519,  -519,
    -519,   233,  -519,   155,  -519,  -519,  3585,   169,  -519,  3672,
     162,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    4570,  6261,  -519,  -519,   174,  -519,  -519,  -519,  -519,  -519,
    -519,   -66,  -519,   -46,    38,  -519,  -519,   930,   184,  -519,
    -519,    18,   -17,   184,  -519,  -519,   160,  -519,    34,    43,
    2947,  -519,  -519,   166,   171,   298,   -47,  4404,  -519,  -519,
    -519,   221,   194,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,   214,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  -519,  -519,   205,  -519,  -519,  -519,  -519,  7229,    28,
     223,   224,  -519,  -519,  -519,   311,  -519,    34,  -519,   254,
    5466,  -519,  -519,  -519,  6328,    42,   -46,   374,   971,  -519,
    5989,  3034,   395,  -519,   276,  -519,  7168,  4690,  -519,  -519,
     -45,   399,    52,  1347,  -519,  3771,   292,   283,  -519,   233,
      34,  3858,  -519,   414,  3945,   313,  -519,  -519,   418,  -519,
    -519,  -519,   787,  -519,   184,  -519,  7109,  6050,  6050,  6050,
    6050,  -519,  -519,  5745,   189,  6111,  -519,  -519,  -519,  -519,
    -519,  5578,  6172,  6050,  6050,  6050,  -519,  -519,   -59,   163,
      67,  -519,  -519,  -519,  -519,   271,    66,   240,   265,   100,
     377,   401,   310,   421,   409,   642,  -519,  -519,  -519,   322,
     338,  -519,   348,  5116,  -519,  6395,   105,   -46,  -519,   276,
    -519,  -519,  -519,    17,  -519,   -56,  -519,   352,  1552,  -519,
    -519,   219,  -519,   347,   362,  1728,  -519,  -519,  4629,  4900,
     364,   353,   381,  -519,   369,   370,     2,  -519,   366,   190,
    -519,  -519,   359,   373,   483,   359,   630,  -519,  -519,  -519,
    -519,  -519,  4119,   367,  -519,   -41,   372,  -519,  -519,  1461,
     120,  -519,   361,   363,  -519,    34,   382,   383,   389,   388,
     385,  -519,  -519,  -519,  -519,  -519,  -519,   509,    27,   402,
      76,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,
    -519,  5578,  -519,  -519,   -16,   408,  3260,  -519,  3294,  -519,
    -519,  -519,   416,  4961,  -519,  -519,    33,  5806,  5989,    33,
    6050,  6050,  6050,  6050,  6050,  6050,  6050,  6050,  6050,  6050,
    6050,  6050,  6050,  6050,  6050,  6050,  6050,  6050,  6050,  -519,
    -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  -519,  6050,
    -519,  5989,  5989,  5578,  -519,  5806,   323,  5177,  -519,  -519,
      73,   103,    44,  6462,   126,   -46,  -519,   276,  -519,  -519,
    5989,  -519,  -519,   406,  -519,   527,  5806,  5684,  5867,   426,
     427,  6050,   417,   428,   429,   439,  2116,   449,  4380,   276,
    5360,  -519,   267,    20,   146,  1834,  -519,  -519,  -519,  -519,
    -519,   430,  -519,  -519,  -519,  -519,  -519,  6529,  -519,  1040,
    6596,  -519,  -519,   131,   184,  7050,  -519,  5989,  5989,  -519,
     360,   219,   499,   440,  -519,  -519,  -519,  -519,  -519,  4206,
     -41,   442,   435,  6050,  6050,  -519,  1923,  -519,  1130,  -519,
    -519,  -519,   441,  -519,  -519,  6050,   414,  -519,   -26,   459,
     460,  7109,  4032,  7109,   464,  -519,  5989,  6050,  5989,  -519,
    6997,   457,  -519,    41,  -519,   456,   471,    -4,  -519,  -519,
    -519,   271,   271,   271,    66,    66,   240,   240,   265,   265,
     265,   265,   147,   252,   377,   401,   310,   421,   409,    80,
    -519,  -519,   473,   476,  5238,  -519,  7168,  4690,  -519,  6663,
     157,   -46,  -519,   276,  -519,  -519,  2010,   463,  -519,   479,
    5989,  5989,  -519,   467,  2222,  -519,  -519,  3140,   557,  5989,
    -519,   176,   530,  -519,  -519,  -519,  6730,  6797,  -519,  -519,
     533,  -519,  -519,  -519,  -519,  -519,   605,  -519,  -519,   606,
     212,  4293,   -41,   487,  -519,  -519,  -519,  -519,   503,  -519,
    -519,  -519,  -519,  7279,  7279,   112,  -519,  -519,  -519,  -519,
    -519,   -14,  7279,   507,  5299,  6050,  -519,  -519,  5989,  -519,
    -519,   624,  -519,   515,   506,  1175,   211,  -519,   276,  -519,
    -519,  -519,  -519,   505,   523,   524,  2328,  -519,  -519,  4486,
    -519,   532,   534,  -519,   538,  -519,   530,  6864,  1192,  -519,
    -519,   543,  -519,  -519,   219,   219,  -519,   357,   -41,   512,
    -519,  -519,  -519,   592,  -519,   544,  5806,  -519,  -519,  5989,
    -519,  -519,   546,   528,  -519,  -519,  -519,   184,  -519,   218,
    -519,  -519,  2434,  2540,  -519,  -519,   545,  5989,  2646,  1645,
    -519,  6931,  -519,  -519,  7279,  -519,  -519,   -41,   550,  -519,
     185,   507,   569,    54,  6050,  -519,   533,  -519,   650,  -519,
    5928,    -5,  -519,  -519,   578,  5050,   566,   581,  -519,  -519,
     582,  -519,  -519,  -519,   572,  -519,  2752,   505,   585,   576,
     276,   830,  -519,  -519,  7279,  -519,    33,  -519,  -519,  2858,
    -519,  -519,  -519,  -519,  -519,  -519,  -519
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -519,  -519,  -519,  -519,   529,   -37,  -519,   519,   -81,  -519,
     268,  -519,  -519,  -519,   500,     8,   -38,  -519,  -155,  -373,
     489,  -519,  -519,  -519,  -519,  -519,    46,  -519,  -519,    16,
    -519,   410,    75,    23,    47,   -22,    87,   350,   337,   349,
     354,   339,  -159,  -145,  -519,   707,  -519,  -519,   116,  -519,
    -447,   201,  -321,  -519,  -519,    95,  -519,  -519,  -519,  -519,
     183,   317,  -519,  -518,  -519,  -519,  -519,  -519,  -519,   700,
     -99,   -93,  -519,  -164,   257,   264,  -519,  1070,  -519,  -519,
    -519,   365,  -519,  -519,  -519,  -519,    13,  -519,  -519,   202,
    -519,  -519,  -171,    25,  -519,  -519,   692,     0,     3,   261,
    -519,  -519,   -10,  -519,  -519,   279,  -519,   351,  -519,  -519,
    -160,  -163,  -519,  -519,  -519,  -519,    71,  -251,  -172,   -42,
     608,  -519,  -519,  -252,  -519,   319,  -519,  -519,  -519,   -74,
    -142,  -239,  -519,  -519,   237,  -519,  -519,  -166,  -519,  -519,
     246,  -519,    10,   681,   -85,  -262,  -519,  -519,  -255,  -519,
    -519,  -519,  -519,  -519,  -144,  -445,   299,  -519,  -298,  -519,
      -2,  -519,   198,  -519
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -446
static const short yytable[] =
{
      75,   103,   277,   179,   108,   278,   259,   192,   408,   414,
     283,   477,    93,    65,   399,   265,   412,   187,   286,   301,
     304,   180,   532,   112,   583,    71,   585,   586,   389,   165,
     102,   106,   287,   625,   462,   278,     1,   186,   591,   310,
      97,   632,    75,   549,   340,   147,   112,   -56,  -281,   109,
    -281,   409,   -12,   182,   168,   293,    75,   100,   169,   155,
     170,   -12,    96,   171,   410,   -54,     2,     3,   474,    65,
      75,    75,   354,   355,   356,   106,   205,   172,   289,  -322,
    -445,    71,   172,  -306,  -322,  -306,   313,   277,   362,    98,
     154,   495,   317,   654,  -306,   163,   164,   407,    93,   181,
      75,   322,   719,    93,   496,   558,   410,   190,   183,   316,
    -411,   675,   108,    65,   607,   496,   496,   352,   353,   326,
     369,   370,   256,   170,   391,    71,   171,   107,   503,   261,
      37,    38,    42,    42,     1,   156,   649,   452,   189,   324,
     107,    44,    44,  -419,   176,   301,   304,   345,    75,   104,
     396,   201,  -411,     2,     3,   177,   544,   109,   535,   101,
     252,  -373,   168,   253,    75,   310,   258,   369,   370,   -57,
     -57,   107,   713,   357,   496,   260,    75,   108,   587,  -374,
     260,   363,   364,    75,   358,    75,   359,   492,   102,   255,
    -374,    75,   340,   112,    75,   105,   493,   315,    65,   577,
     496,   279,   688,   608,    65,   575,    75,    65,   302,   536,
      71,   371,   372,   404,    93,   112,    71,    37,    38,    71,
     537,   252,   151,   653,   253,   168,   149,     7,     8,   406,
      42,   279,   493,   627,   482,   277,   112,   449,   156,    44,
     478,   297,   298,   299,   479,   543,   168,   714,  -373,   460,
     542,   461,   159,    75,   533,    75,   397,   562,   371,   372,
     352,   353,   286,   297,   298,   299,   496,   494,    51,   167,
     563,   460,   369,   370,   160,   252,   552,   168,    75,    75,
     403,   617,   194,   692,   278,   185,   -57,   -57,   107,   572,
     465,   193,   619,   468,   620,   612,   496,   260,   360,   361,
     633,   195,    75,   163,   450,   674,  -233,   533,   569,    75,
     259,    51,   301,   304,   286,   286,   167,   489,   490,    83,
     278,   196,   278,   197,    51,   462,   286,   469,   552,   552,
     203,   168,   310,   204,   302,   670,  -233,   344,   168,    51,
     552,   252,   697,   601,   253,     2,     3,   518,   519,   520,
     521,   698,   699,   365,   366,    51,   345,   702,   367,   368,
     296,   540,   150,   371,   372,   278,   206,   671,    51,   570,
     283,   277,   666,   -12,   -12,    83,   -12,   112,   286,     2,
       3,   618,   685,   686,   -12,   373,   374,   -12,   514,   515,
     166,   -12,   287,   252,   202,   728,   253,    75,   112,   596,
     534,   275,   292,    75,   -48,   165,   178,   314,   736,    37,
      38,   297,   298,   299,   516,   517,    51,   318,   324,    83,
     323,   -57,   407,   260,   375,   640,   252,    93,   539,   396,
     252,   376,    51,   253,   378,   252,    51,   511,   512,   513,
    -373,   155,   393,    37,    38,   377,   277,    75,   202,   394,
      75,    51,   149,    51,   395,    75,    42,   344,   395,    51,
     522,   523,    51,    43,    93,    44,   108,   415,   416,    75,
      51,   454,   566,   455,   507,   567,    75,   456,   457,   458,
     279,  -436,   289,   257,   459,  -233,   466,   480,   543,   481,
     473,    75,    75,    75,   581,   476,   683,   616,   485,   402,
      75,   302,   305,   147,    83,    65,   483,   529,   486,   484,
      83,   487,   488,    83,   491,   497,   279,    71,   279,   651,
     652,    51,   498,    51,   256,   453,   546,   618,   655,    47,
     112,   -56,   550,   551,    75,   286,    75,   611,   644,    75,
     554,   645,   461,   433,   561,   557,   344,    51,   731,   552,
       2,     3,   555,   556,   252,   559,   565,   252,   578,   584,
     580,   279,   478,   723,   615,   590,    75,    75,   593,   594,
      51,   598,    47,   669,   405,   605,   410,    51,   606,   733,
     609,    75,   696,   610,   260,    47,   622,   260,   260,   621,
     626,   637,   638,    75,    75,   404,   253,   253,   451,   631,
      47,   634,    75,   641,    75,   253,   647,   201,   112,   112,
     708,   650,   474,   656,    37,    38,    47,   334,   335,   336,
     337,   470,   667,   324,   668,   496,   252,   -56,   305,    47,
     672,   673,   347,   349,   350,   351,   689,    75,   677,   540,
     690,   678,   402,   402,   679,   659,     2,     3,   402,   684,
     734,   691,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   681,   694,    51,    51,   623,   623,   389,   700,
      51,    51,   252,   252,   709,   623,   712,    93,   252,    75,
     710,    75,   705,   716,    75,   720,   724,   253,   725,   228,
     727,   726,   729,    47,   433,   453,   453,    47,   433,   453,
     730,   294,   325,   433,   342,    75,   539,   711,   721,   695,
      37,    38,    47,   525,    47,    51,   252,    51,    51,   324,
      47,    51,   541,    47,    75,   524,   526,   253,   528,   252,
     396,   680,   527,   111,   146,   111,   -48,    51,   614,   -48,
     628,  -373,  -233,   111,    51,   623,    51,   -48,   595,   150,
     -48,   390,   564,   -48,   -48,   -48,   158,   597,   531,   630,
      51,   604,   146,   502,   391,   592,   548,   715,   150,   568,
     509,   510,   178,   613,   184,   693,   262,   589,   646,   111,
     402,     0,     0,   111,    47,     0,     0,     0,   582,     0,
     -56,   111,     0,   701,     0,   305,     0,   588,     0,     0,
       0,     0,    51,     0,   432,     0,     0,    51,    47,     2,
       3,    83,     0,   453,     0,     0,   717,     0,     0,     0,
       0,     0,   433,     0,     0,   433,     0,   336,   337,     0,
       0,    47,     0,     1,    51,    51,     0,     0,    47,     0,
     146,   111,     0,     0,     0,     0,     0,     0,     0,    51,
     663,     0,     2,     3,     0,     0,     0,   402,     0,   111,
     111,     0,     0,     0,   111,     0,     0,   247,   146,     0,
       0,     0,    51,    37,    38,     0,     0,   266,   269,    51,
       0,   111,   324,    51,   453,   504,   639,     0,   508,     0,
       0,     0,     0,     0,   433,     0,     0,     0,   146,     0,
     648,     0,     0,     0,     0,    51,    51,   600,     1,   663,
       0,     0,     0,     0,     0,    51,    37,    38,     0,     0,
     338,     0,   228,     0,     0,   149,     0,     2,     3,    42,
       0,    51,    47,     1,     0,     0,   449,     0,    44,     0,
     433,   433,     0,     0,     0,   146,   433,  -373,     0,    51,
       0,   453,     2,     3,     0,   432,     0,   682,     0,   432,
       0,     0,     0,     0,   432,     0,   687,   453,     0,     0,
     146,     0,     0,    51,     1,   269,    47,     0,    47,    47,
       0,   111,    47,     0,   433,     0,     0,     0,     0,    51,
       0,    37,    38,     2,     3,     0,     0,   433,    47,     0,
     149,     0,     0,     0,    42,    47,     0,    47,     0,     0,
       0,    43,     0,    44,     0,   664,    37,    38,     0,     0,
       0,    47,     0,     0,   722,   149,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,    43,     0,    44,     0,
     732,     0,     0,     1,     0,     0,     0,     0,   111,     0,
       0,   111,     0,     0,     0,     0,     0,    37,    38,     0,
       0,     0,     2,     3,   266,     0,   149,     0,    47,     0,
      42,     0,     0,     0,     0,     0,     0,    43,     0,    44,
       0,     0,     0,   432,     0,     0,   432,     0,     0,   146,
       0,     0,     0,     0,     0,    47,    47,     0,     0,   530,
     247,     0,   266,     0,     0,     0,     0,   111,     0,     0,
      47,   110,   110,     0,   152,     0,     0,   545,     0,     0,
       0,   110,     0,   266,     0,   111,    37,    38,     0,     0,
       0,     0,     0,   296,     0,   149,     0,     0,     0,    42,
     110,   111,     0,     0,    47,   111,   449,   146,    44,     0,
       0,     0,     2,     3,     0,   432,     0,     0,     0,     0,
       0,   110,     0,     0,   573,   574,    47,    47,   188,   110,
     111,     0,     0,     0,     0,     0,    47,     0,     1,     0,
       0,     0,     0,   146,     0,   146,     0,     0,     0,     0,
       0,     0,   146,     0,     0,     1,     0,     2,     3,     0,
       0,   432,   432,   599,     0,   266,     0,   432,     0,     0,
      47,     0,     0,     0,     2,     3,    37,    38,   110,   110,
       0,     0,     0,     0,     0,   149,   146,   188,   146,    42,
       0,     0,     0,     0,    47,     0,    43,   110,    44,     0,
       0,     0,   110,     0,     0,   432,   110,     0,     0,     0,
      47,     0,   295,   269,     0,   735,     0,     0,   432,   110,
     188,    37,    38,     0,     0,     0,     0,     0,   111,     0,
     149,   111,   111,     0,    42,     0,   110,     0,    37,    38,
       0,    43,     0,    44,     0,   146,   146,   149,     0,     0,
       0,    42,   348,     0,   146,     0,   146,     0,   449,     0,
      44,     0,     0,     0,     0,     0,     0,   111,     0,     0,
       0,     0,     0,     0,     0,   665,     0,     0,     0,     0,
       0,     0,     0,   110,     0,     0,     0,     0,     0,     0,
     111,     0,     0,     0,     0,     0,     0,     0,     0,   111,
       0,   152,     0,     0,     0,     0,     0,     0,   110,     0,
     296,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,     0,     0,   266,   467,     0,     0,     0,     0,     2,
       3,   146,     0,     0,     0,     0,   146,     0,   161,     0,
       0,     0,     0,     0,     0,   188,     0,     0,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   297,   298,
     299,    15,    16,    17,    18,    19,    20,    21,    22,     0,
       0,     0,     0,   111,     0,     0,   146,     0,   111,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,    35,    36,    37,    38,    39,     0,     0,     0,     0,
       0,     0,    41,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,   296,     0,     0,   110,     0,     0,
    -308,   300,     0,  -442,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     3,   110,     0,     0,     0,     0,
       0,     0,   161,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     7,     8,     9,    10,    11,    12,
      13,    14,   297,   298,   299,    15,    16,    17,    18,    19,
      20,    21,    22,     0,     0,   110,     0,     0,     0,     0,
       0,   152,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     0,    35,    36,    37,    38,    39,
       0,     0,     0,     0,     0,     1,    41,   207,   208,     0,
      42,   110,     0,   110,     0,     0,     0,    43,     0,    44,
     110,     0,     0,     0,   209,   210,     0,     0,     0,     0,
       0,     0,     0,     0,  -308,   300,     0,  -442,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,   110,     0,     0,     0,
       0,     0,     0,     0,   211,   212,     0,     0,     0,     0,
       0,     0,   213,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   214,   112,   110,
     110,    42,   215,   216,   217,   218,   219,   220,   221,     0,
     222,     0,   223,   110,   110,   224,   225,     0,     0,     0,
       0,     0,   110,     0,   110,     0,     0,   268,   411,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     8,
       0,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,   152,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,     0,
      36,     1,     0,   207,   208,     0,     0,     0,     0,     0,
     130,   703,     0,     0,     0,     0,     0,     0,     0,   110,
     417,   418,     0,     0,   110,     0,     0,     0,     5,   161,
     419,     0,   420,   421,   422,     0,   423,   424,   425,   426,
     427,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
     211,   212,     0,     0,   110,     0,   428,   429,   213,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,    41,     0,     0,     0,    42,   215,   216,
     217,   218,   219,   220,   430,     0,   222,     1,   223,   207,
     208,   224,   225,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,   275,   431,     0,   417,   418,     0,     0,
       0,     0,     0,     0,     5,   161,   419,     0,   420,   421,
     422,     0,   423,   424,   425,   426,   427,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,   211,   212,     0,     0,
       0,     0,   428,   429,   213,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,    36,
      37,    38,    39,    40,     0,     0,   296,     0,     0,    41,
       0,     0,     0,    42,   215,   216,   217,   218,   219,   220,
     430,     0,   222,     0,   223,     2,     3,   224,   225,     0,
       0,     0,     0,     0,   161,     0,     0,     0,    45,   275,
    -193,     0,     0,     0,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   297,   298,   299,    15,    16,    17,
      18,    19,    20,    21,    22,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,    35,    36,    37,
      38,    39,     0,     1,     0,   207,   208,     0,    41,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,    44,   209,   210,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -308,   300,     0,  -442,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   211,   212,     0,     0,     0,     0,     0,     0,
     213,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   214,     0,     0,     0,    42,
     215,   216,   217,   218,   219,   220,   221,     0,   222,     1,
     223,   207,   208,   224,   225,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,  -347,     0,   417,   418,
       0,     0,     0,     0,     0,     0,     5,   161,   419,     0,
     420,   421,   422,     0,   423,   424,   425,   426,   427,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,   211,   212,
       0,     0,     0,     0,   428,   429,   213,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,    41,     0,     0,     0,    42,   215,   216,   217,   218,
     219,   220,   430,     0,   222,     1,   223,   207,   208,   224,
     225,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,   275,     0,     0,   417,   418,     0,     0,     0,     0,
       0,     0,     5,   161,   419,     0,   420,   421,   422,     0,
     423,   424,   425,   426,   427,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,   211,   212,     0,     0,     0,     0,
     428,   429,   213,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,    36,    37,    38,
      39,    40,     0,     0,     0,     0,     0,    41,     0,     0,
       0,    42,   215,   216,   217,   218,   219,   220,   430,     0,
     222,     1,   223,   207,   208,   224,   225,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,   275,     0,     0,
     417,   418,     0,     0,     0,     0,     0,     0,     5,   161,
     419,     0,   420,   421,   422,     0,   423,   424,   425,   426,
     427,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
     211,   212,     0,     0,     0,     0,   428,   429,   213,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,    41,     0,     0,     0,    42,   215,   216,
     217,   218,   219,   220,   430,     0,   222,     1,   223,   207,
     208,   224,   225,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,   275,     0,     0,   417,   418,     0,     0,
       0,     0,     0,     0,     5,   161,   419,     0,   420,   421,
     422,     0,   423,   424,   425,   426,   427,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,   211,   212,     0,     0,
       0,     0,   428,   429,   213,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,    36,
      37,    38,    39,    40,     0,     0,     0,     0,     0,    41,
       0,     0,     0,    42,   215,   216,   217,   218,   219,   220,
     430,     0,   222,     1,   223,   207,   208,   224,   225,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,   275,
       0,     0,   417,   418,     0,     0,     0,     0,     0,     0,
       5,   161,   419,     0,   420,   421,   422,     0,   423,   424,
     425,   426,   427,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,   211,   212,     0,     0,     0,     0,   428,   429,
     213,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,    37,    38,    39,    40,
       0,     0,     0,     0,     0,    41,     0,     0,     0,    42,
     215,   216,   217,   218,   219,   220,   430,     0,   222,     1,
     223,   207,   208,   224,   225,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,   275,     0,     0,   417,   418,
       0,     0,     0,     0,     0,     0,     5,   161,   419,     0,
     420,   421,   422,     0,   423,   424,   425,   426,   427,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,   211,   212,
       0,     0,     0,     0,   428,   429,   213,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,    41,     0,     0,     0,    42,   215,   216,   217,   218,
     219,   220,   430,     0,   222,     1,   223,   207,   208,   224,
     225,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,   275,     0,     0,   417,   418,     0,     0,     0,     0,
       0,     0,     5,   161,   419,     0,   420,   421,   422,     0,
     423,   424,   425,   426,   427,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,   211,   212,     0,     0,     0,     0,
     428,   429,   213,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,    36,    37,    38,
      39,    40,     0,     0,     0,     0,     0,    41,     0,     0,
       0,    42,   215,   216,   217,   218,   219,   220,   430,     0,
     222,     1,   223,   207,   208,   224,   225,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,   275,     0,     0,
     417,   418,     0,     0,     0,     0,     0,     0,     5,   161,
     419,     0,   420,   421,   422,     0,   423,   424,   425,   426,
     427,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
     211,   212,     0,     0,     0,     0,   428,   429,   213,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,    36,    37,    38,    39,    40,     0,     0,
       1,     0,     0,    41,     0,     0,     0,    42,   215,   216,
     217,   218,   219,   220,   430,     0,   222,     0,   223,     2,
       3,   224,   225,     0,     0,     0,     4,     5,     6,     0,
       0,     0,    45,   275,     0,     0,     0,     0,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,    15,    16,    17,    18,    19,    20,    21,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     1,     0,   207,
     208,     0,    41,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,    43,     0,    44,   209,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   211,   212,     0,     0,
       0,     0,     0,     0,   213,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   214,
       0,     0,     0,    42,   215,   216,   217,   218,   219,   220,
     221,     0,   222,     1,   223,   207,   208,   224,   225,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
       0,     0,   417,   418,     0,     0,     0,     0,     0,     0,
       0,   161,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,   211,   212,     0,     0,     0,     0,     0,     0,
     213,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,    37,    38,    39,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,    42,
     215,   216,   217,   218,   219,   220,   430,     0,   222,     0,
     223,     0,     0,   224,   225,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -48,   -48,  -281,   -48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -48,   -48,     0,   -48,
       0,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,     0,   -48,   -52,   -52,  -282,
     -52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -52,   -52,     1,   -52,     0,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,     0,
     -52,     2,     3,     0,     0,     0,     0,     0,     4,     5,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,  -281,
       0,     0,     0,     0,    41,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,    43,     0,    44,   -48,   -48,
       0,     0,     0,     0,     0,     0,     0,  -281,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,     0,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,     0,     0,     0,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,     0,
       0,  -281,  -281,  -281,  -281,     0,     0,     0,     0,     0,
       0,  -281,     0,     0,     0,  -281,     0,     0,     1,     0,
       0,     0,   -48,   -48,  -281,     0,     0,   -48,   -48,     0,
       0,     0,     0,   -48,     0,     0,   -48,     2,     3,     0,
     -48,     0,     0,     0,     4,     5,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,  -282,     0,     0,     0,     0,
      41,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    43,     0,    44,   -52,   -52,     0,     0,     0,     0,
       0,     0,     0,  -282,     0,     0,     0,     0,     0,    45,
       0,     0,     0,     0,     0,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,     0,     0,     0,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,     0,     0,  -282,  -282,  -282,
    -282,     0,     0,     0,     0,     0,     0,  -282,     0,     0,
       0,  -282,     0,     0,     1,     0,     0,     0,   -52,   -52,
    -282,     0,     0,   -52,     0,     0,     0,     0,     0,   -52,
       0,     0,   -52,     2,     3,   -52,   -52,     0,     0,     0,
       4,     5,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     1,     0,     0,     0,     0,    41,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,    43,     0,    44,
       2,     3,     0,     0,     0,     0,     0,     4,     5,     6,
       0,     0,     0,     0,     0,    45,     0,     0,     0,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     1,     0,
       0,     0,     0,    41,     0,     0,     0,    42,     0,     0,
       0,     0,     0,     0,    43,     0,    44,     2,     3,     0,
       0,     0,     0,     0,     4,     5,     6,     0,     0,     0,
       0,     0,    45,     0,     0,     0,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     1,     0,     0,     0,     0,
      41,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    43,     0,    44,     2,     3,     0,     0,     0,     0,
       0,     4,     5,     6,     0,     0,     0,     0,     0,    45,
       0,     0,     0,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,   296,     0,     0,     0,     0,    41,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,    43,     0,
      44,     2,     3,     0,     0,     0,     0,     0,     0,     0,
     161,     0,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,    36,    37,    38,    39,     0,   296,
       0,     0,     0,     0,    41,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,    43,     0,    44,     2,     3,
       0,     0,     0,     0,     0,     0,     0,   161,     0,     0,
       0,     0,     0,  -436,     0,     0,     0,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,    36,    37,    38,    39,     0,   296,     0,     0,     0,
       0,    41,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,    43,     0,    44,     2,     3,     0,     0,     0,
       0,     0,     0,     0,   161,     0,     0,     0,     0,     0,
    -436,     0,     0,     0,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,     0,    36,    37,
      38,    39,     0,     1,     0,   207,   208,     0,    41,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,    44,   209,   210,     0,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,   119,     0,  -436,     0,   120,
     121,   122,   123,   124,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   211,   212,     0,     0,     0,     0,     0,     0,
     213,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   214,     0,     0,     0,    42,
     215,   216,   217,   218,   219,   220,   221,     0,   222,     1,
     223,   207,   208,   224,   225,     0,     0,   128,   129,     0,
       0,   131,   132,     0,   560,     0,     0,     0,   209,   210,
     133,     0,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   211,   212,
       0,     0,     0,     0,     0,     0,   213,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,    36,     0,   112,     0,     0,     0,     0,     0,     0,
       0,   214,     0,     0,     0,    42,   215,   216,   217,   218,
     219,   220,   221,     0,   222,     0,   223,     0,     0,   224,
     225,   161,     0,     0,     0,     0,     0,     0,     0,     0,
    -199,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,     0,     0,    39,     0,
     161,     0,     0,     0,     0,   130,     0,     0,     0,     0,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,     0,     0,     1,   162,   207,   208,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   209,   210,    36,     0,     0,    39,     0,     0,
       0,     0,     0,     0,   130,  -386,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -386,     0,  -386,     0,
    -386,     0,     0,     0,     0,     0,     0,     0,     0,  -386,
       0,     0,   211,   212,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   214,     0,     0,     0,    42,
     215,   216,   217,   218,   219,   220,   221,     0,   222,     0,
     223,     0,     0,   224,   225,     0,     0,   112,  -165,   113,
     114,   115,   116,   117,   118,   119,     0,     0,     0,   120,
     121,   122,   123,   124,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     0,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
       0,   131,   132,     1,     0,     0,     0,     0,     0,     0,
     133,     0,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,     2,     3,     0,     0,     0,     0,     0,     0,
       0,   161,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,     0,     0,     1,     0,   207,   208,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,   209,   210,    36,    37,    38,    39,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,   449,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,  -373,     0,     0,
       0,     0,     0,   211,   212,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     1,     0,     0,   214,     0,     0,     0,
      42,   215,   216,   217,   218,   219,   220,   221,     0,   222,
       0,   223,     2,     3,   224,   225,     0,     0,   501,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     0,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,    37,    38,     2,     3,
       0,     0,     0,     0,     0,    41,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,   449,     0,    44,     7,
       8,     0,    10,    11,    12,    13,    14,  -373,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     2,
       3,    36,    37,    38,     0,     0,     0,     0,     0,     0,
       0,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     8,   396,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,  -373,     0,     0,     0,     0,     0,     0,
       0,   112,     0,     0,     0,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       2,     3,    36,    37,    38,     0,     0,     0,     0,     0,
       0,     0,   198,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,   396,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,  -373,     0,     0,     0,     0,     0,
       0,     0,   112,     0,     0,     0,     0,     0,     0,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     2,     3,    36,    37,    38,     0,     0,     0,     0,
       0,     0,     0,   198,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,   396,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,  -373,     0,     0,     0,     0,
       0,     0,     0,     1,     0,   207,   208,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   417,   418,    36,    37,    38,     0,     0,     0,
       0,     0,     0,     0,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     0,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,   659,     0,     0,     0,
       0,     0,   211,   212,     0,     0,     0,     0,     0,     0,
     213,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,    37,    38,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,    42,
     215,   216,   217,   218,   219,   220,   430,     0,   222,     1,
     223,   207,   208,   224,   225,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   209,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     0,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   211,   212,
       0,     0,     0,     0,     0,     0,   213,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   214,     0,     0,     0,    42,   215,   216,   217,   218,
     219,   220,   221,     0,   222,     0,   223,  -236,     0,   224,
     225,     1,     0,   207,   208,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     209,   210,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,     0,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     211,   212,     0,     0,     0,     0,     0,     0,   213,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   214,     0,     0,     0,    42,   215,   216,
     217,   218,   219,   220,   221,     0,   222,     1,   223,   207,
     208,   224,   225,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   209,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   211,   212,     1,     0,
     207,   208,     0,     0,     0,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,   209,   210,    36,
    -406,  -406,     0,     0,     0,     0,     0,     0,     0,   214,
       0,     0,     0,    42,   215,   216,   217,   218,   219,   220,
     221,     0,   222,     0,   223,     0,     0,   224,   225,     0,
       0,     0,     0,     0,     0,     0,     0,   211,   212,     1,
       0,   207,   208,     0,     0,   213,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,   209,   210,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     214,     0,   -56,   -56,    42,   215,   216,   217,   218,   219,
     220,   221,     0,   222,     0,   223,     0,     0,   224,   225,
       0,     0,     0,     0,     0,     0,     0,     0,   211,   212,
       1,     0,   207,   208,     0,     0,   213,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,   209,
     210,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   214,     0,     0,     0,    42,   215,   216,   217,   218,
     219,   220,   221,   -76,   222,     0,   223,     0,     0,   224,
     225,     0,     0,     0,     0,     0,     0,     0,     0,   211,
     212,     1,     0,   207,   208,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
     209,   210,    36,  -397,  -397,     0,     0,     0,     0,     0,
       0,     0,   214,     0,     0,     0,    42,   215,   216,   217,
     218,   219,   220,   221,     0,   222,     0,   223,     0,     0,
     224,   225,     0,     0,     0,     0,     0,     0,     0,     0,
     211,   212,     1,     0,   207,   208,     0,     0,   213,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,   209,   210,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   214,     0,     0,     0,    42,   215,   216,
     217,   218,   219,   220,   221,  -162,   222,     0,   223,     0,
       0,   224,   225,     0,     0,     0,     0,     0,     0,     0,
       0,   211,   212,     1,     0,   207,   208,     0,     0,   213,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   209,   210,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   214,     0,     0,     0,    42,   215,
     216,   217,   218,   219,   220,   221,     0,   222,     0,   223,
       0,     0,   224,   225,     0,     0,     0,     0,     0,     0,
       0,     0,   211,   212,     1,     0,   207,   208,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,   209,   210,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   214,     0,     0,     0,    42,
     215,   216,   217,   218,   219,   220,   221,     0,   222,     0,
     223,     0,     0,   224,   225,     0,     0,     0,     0,     0,
       0,     0,     0,   211,   212,   346,     0,   207,   208,     0,
       0,     0,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,   209,   210,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   214,     0,     0,     0,
      42,   215,   216,   217,   218,   219,   220,   341,     0,   222,
       0,   223,     0,     0,   224,   225,     0,     0,     0,     0,
       0,     0,     0,     0,   211,   212,     0,     0,     0,     0,
       0,     0,     0,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     1,     0,     0,   214,     0,     0,
       0,    42,   215,   216,   217,   218,   219,   220,   221,     0,
     222,     0,   223,     2,     3,   224,   225,     0,     0,     0,
       0,     0,   161,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     0,     0,    36,    37,    38,    39,
       2,     3,     0,     0,     0,     0,    41,     0,     0,   161,
      42,     0,     0,     0,     0,     0,     0,    43,     0,    44,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,    36,    37,    38,    39,     2,     3,     0,
       0,     0,     0,    41,     0,     0,   161,    42,     0,     0,
       0,     0,     0,     0,    43,     0,    44,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,     0,
      36,    37,    38,    39,     2,     3,     0,     0,     0,     0,
      41,     0,     0,   161,    42,     0,     0,     0,     0,     0,
       0,    43,     0,    44,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,    36,    37,    38,
      39,     2,     3,     0,     0,     0,     0,    41,     0,     0,
     161,    42,     0,     0,     0,     0,     0,     0,    43,     0,
      44,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,    36,    37,    38,    39,     2,     3,
       0,     0,     0,     0,    41,     0,     0,   161,    42,     0,
       0,     0,     0,     0,     0,    43,     0,    44,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,    36,    37,    38,    39,     2,     3,     0,     0,     0,
       0,    41,     0,     0,   161,    42,     0,     0,     0,     0,
       0,     0,   449,     0,    44,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,     0,    36,    37,
      38,    39,     2,     3,     0,     0,     0,     0,    41,     0,
       0,   161,    42,     0,     0,     0,     0,     0,     0,    43,
       0,    44,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,    37,    38,    39,     2,
       3,     0,     0,     0,     0,    41,     0,     0,   161,    42,
       0,     0,     0,     0,     0,     0,    43,     0,    44,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,    15,    16,    17,    18,    19,    20,    21,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,     0,    36,    37,    38,    39,     2,     3,     0,     0,
       0,     0,    41,     0,     0,   161,    42,     0,     0,     0,
       0,     0,     0,   449,     0,    44,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,    36,
      37,    38,    39,     2,     3,     0,     0,     0,     0,    41,
       0,     0,   161,    42,     0,     0,     0,     0,     0,     0,
      43,     0,    44,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
     112,     0,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     0,     0,    36,    37,    38,    39,
       0,     0,     0,     0,     0,     0,    41,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,    43,     0,    44,
       7,     8,     0,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,   161,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,   602,    15,    16,    17,    18,    19,    20,
      21,    22,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    36,     0,     0,    39,     0,
     161,     0,     0,     0,     0,   130,   571,     0,     0,     0,
       0,     0,     7,     8,     9,   327,    11,   328,    13,    14,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,   112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   329,     0,    36,     0,     0,    39,     0,   161,
       0,     0,     0,     0,   130,     0,     0,     0,     0,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,    15,    16,    17,    18,    19,    20,    21,    22,
       0,     0,   112,     0,     0,     0,     0,     0,     0,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     2,     3,    36,     0,     0,    39,     0,     0,     0,
       0,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     0,    10,    11,    12,    13,    14,
       0,     0,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,    36,    37,    38,     0,     0,     0,
       0,     0,     7,     8,   198,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned short yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   125,     0,     0,     0,     0,     0,     0,     0,     0,
     289,   141,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   181,     0,     0,   155,     0,     0,     0,     0,
       0,   183,     0,     0,     0,   131,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,     0,     0,     0,     0,
       0,     0,     0,   617,     0,   619,     0,     0,     0,    23,
       0,     0,     0,     0,   621,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   607,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,     0,     0,     0,     0,     0,
     482,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,   274,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   185,     0,     0,     0,   651,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   609,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   627,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   119,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     673,     0,     0,   629,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   520,   522,     0,   524,   147,     0,     0,
       0,     0,     0,     0,   526,     0,     0,   528,     0,     0,
       0,   530,     0,     0,     0,     0,     0,     0,   151,     0,
       0,     0,   153,     0,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   173,     0,     0,     0,     0,     0,     0,     0,   476,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   187,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   474,     0,     0,     0,     0,     0,     0,     0,
     486,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     675,   677,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   647,   649,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   687,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     661,     0,     0,     0,     0,     0,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   280,   283,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175,
     177,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   695,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,     0,     0,   697,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   599,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   615,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   601,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   663,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   669,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   671,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,   287,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   195,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   532,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   613,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,   516,
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
       0,     0,     0,     0,     0,   637,     0,     0,     0,     0,
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
       0,   665,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   679,     0,     0,
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
       0,     0,     0,   681,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   683,
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
       0,     0,     0,     0,     0,   693,     0,     0,     0,     0,
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
       0,   699,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,   639,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,   291,   293,   295,   297,   299,
     301,   303,   305,   307,   309,   311,   313,   315,   317,   319,
     321,   323,   325,   327,   329,   331,   333,   335,   337,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   383,
     385,   387,   389,   391,   393,   395,   397,   399,   401,   403,
     405,   407,   409,   411,   413,   415,   417,   419,   421,   423,
     425,   427,   429,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   339,   341,     0,   343,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   345,   348,     0,   350,
       0,   352,   354,   357,   359,   361,   363,   365,   367,   369,
     371,   373,   375,   377,   379,     0,   381,   431,   433,     0,
     435,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     437,   440,     1,   442,     0,   444,   446,   448,   450,   452,
     454,   456,   458,   460,   462,   464,   466,   468,   470,     0,
     472,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     9,    11,     0,     0,     0,    13,    15,     0,
       0,     0,     0,    17,     0,     0,    19,     0,     0,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,     0,     0,     0,    40,    42,
       0,     0,     0,    44,     0,     0,     0,     0,     0,    46,
       0,     0,    48,     0,     0,    50,    52,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   161,     0,     0,     0,     0,     0,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   167,     0,     0,     0,     0,     0,     0,   169,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   171,     0,
       0,     0,     0,     0,     0,   623,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   625,     0,     0,     0,     0,
       0,     0,   285,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   611,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   653,     0,     0,     0,
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
       0,     0,     0,     0,     0,   197,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   199,     0,   201,     0,
     203,     0,     0,     0,     0,     0,     0,     0,     0,   205,
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
       0,     0,     0,   207,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   210,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   212,   214,   216,   218,   220,   222,   224,
     226,     0,     0,     0,   228,   230,   232,   234,   236,   238,
     240,   242,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   244,   246,   248,   250,   252,   254,   256,   258,
     260,   262,   264,     0,     0,   266,     0,     0,   268,     0,
       0,     0,     0,     0,     0,   270,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   272,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   689,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   691,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     478,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   631,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   480,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   655,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   657,   659,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   633,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   518,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,   488,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   490,   492,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   494,
       0,     0,     0,   496,     0,     0,     0,     0,     0,     0,
     498,     0,   500,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     502,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   504,
     506,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   508,     0,     0,     0,   510,     0,     0,     0,
       0,     0,     0,   512,     0,   514,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    61,    63,    65,    67,    69,
      71,    73,     0,     0,     0,    75,    77,    79,    81,    83,
      85,    87,    89,     0,     0,     0,     0,     0,     0,     0,
       0,   145,     0,    91,    93,    95,    97,    99,   101,   103,
     105,   107,   109,   111,     0,     0,   113,     0,     0,   115,
       0,     0,     0,     0,     0,     0,   117,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   484,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   534,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     537,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   539,   541,   543,   545,   547,   549,   551,   553,
       0,     0,     0,   555,   557,   559,   561,   563,   565,   567,
     569,     0,     0,     0,     0,     0,     0,     0,     0,   603,
       0,   571,   573,   575,   577,   579,   581,   583,   585,   587,
     589,   591,     0,     0,   593,     0,     0,   595,     0,     0,
       0,     0,     0,     0,   597,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   635,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   605,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   641,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     643,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   667,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   645,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   685,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   137,   139,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,    56,     0,   219,     0,   281,     0,   281,     0,   281,
       0,   281,     0,   281,     0,   233,     0,   281,     0,   281,
       0,   281,     0,   249,     0,    57,   284,     0,   284,     0,
      56,     0,    56,     0,   219,     0,   282,     0,   282,     0,
     282,     0,   282,     0,   282,     0,   282,     0,   282,     0,
     282,     0,   282,     0,    56,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   283,
       0,   353,     0,    56,     0,    64,     0,    56,     0,   219,
       0,   233,     0,   281,     0,    56,     0,    61,     0,    61,
       0,    57,     0,   408,     0,    56,     0,    64,     0,    56,
       0,    64,     0,    65,     0,    46,     0,    56,     0,    56,
       0,   219,     0,   233,     0,    56,     0,   219,     0,    56,
       0,   219,     0,   284,     0,    61,     0,    61,     0,   284,
       0,   240,     0,   240,     0,   128,     0,   297,     0,    56,
       0,   373,     0,    56,     0,    56,     0,   391,     0,   391,
       0,   391,     0,   391,     0,   391,     0,    56,   265,     0,
     265,     0,   265,     0,   265,     0,   265,     0,   265,     0,
     265,     0,   265,     0,   265,     0,   265,     0,   265,     0,
     265,     0,   265,     0,   265,     0,   265,     0,   265,     0,
     265,     0,   265,     0,   265,     0,   265,     0,   265,     0,
     265,     0,   265,     0,   265,     0,   265,     0,   265,     0,
     265,     0,   265,     0,   265,     0,   265,     0,   265,     0,
     265,     0,   373,     0,    64,     0,   304,     0,   281,     0,
     281,   309,     0,   281,     0,    56,     0,    56,     0,   411,
       0,   408,     0,   408,     0,   408,     0,   408,     0,   408,
       0,   408,     0,   408,     0,   408,     0,   408,     0,   408,
       0,   408,     0,   408,     0,   408,     0,   408,     0,   408,
       0,   408,     0,   408,     0,   408,     0,   408,     0,   408,
       0,   408,     0,   408,     0,   408,     0,   408,     0,   408,
       0,   408,     0,   408,     0,   281,   408,     0,   408,     0,
     408,     0,   408,     0,   233,   408,     0,   408,     0,   408,
       0,   408,     0,   408,     0,   408,     0,   408,     0,   408,
       0,   408,     0,   408,     0,   408,     0,   408,     0,   408,
       0,   408,     0,   409,     0,   409,     0,   409,     0,   409,
       0,   409,     0,   409,     0,   409,     0,   409,     0,   409,
       0,   409,     0,   409,     0,   409,     0,   409,     0,   409,
       0,   409,     0,   409,     0,   409,     0,   409,     0,   409,
       0,   409,     0,   409,     0,   409,     0,   409,     0,   409,
       0,   409,     0,   409,     0,   409,     0,   282,   409,     0,
     409,     0,   409,     0,   409,     0,   409,     0,   409,     0,
     409,     0,   409,     0,   409,     0,   409,     0,   409,     0,
     409,     0,   409,     0,   409,     0,   409,     0,   409,     0,
     409,     0,   409,     0,    94,     0,   373,     0,    56,     0,
     373,     0,   373,     0,    56,     0,    64,     0,   406,     0,
     406,     0,   406,     0,   406,     0,   406,     0,   406,     0,
     406,     0,   397,     0,   397,     0,   397,     0,   397,     0,
     397,     0,   397,     0,   397,     0,    56,     0,    56,     0,
     360,     0,   360,     0,   360,     0,   360,     0,   360,     0,
     360,     0,    56,     0,    56,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,   265,
       0,   265,     0,   265,     0,   265,     0,   265,     0,    56,
       0,   373,     0,    56,     0,   373,     0,    56,     0,   373,
       0,    56,     0,    56,     0,    56,     0,   309,     0,   309,
       0,   309,     0,    56,     0,   219,     0,   129,     0,   130,
       0,    56,     0,   373,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,   373,     0,    64,     0,    64,
       0,    64,     0,    56,     0,    56,     0,    99,     0,    99,
       0,   373,     0,    56,     0,    56,     0,    56,     0,    56,
       0,   373,     0,    56,     0,    99,     0,    99,     0,    56,
       0,    56,     0,    56,     0,    56,     0,   195,     0,    56,
       0,   373,     0,    56,     0,    56,     0,   373,     0,    56,
       0
};

static const short yycheck[] =
{
       0,    11,   174,    88,    41,   176,   166,   100,   259,   271,
     176,   309,     2,     0,   253,   170,   268,    98,   177,   183,
     183,     3,   395,     3,   469,     0,   473,   474,    26,    71,
       3,     3,   177,   551,   289,   206,     3,     3,   485,   183,
      46,   559,    42,   416,     3,    42,     3,     3,    95,    41,
      95,   107,   111,    91,   120,     3,    56,   101,   124,    51,
     106,   120,     3,   109,   120,   112,    22,    23,   109,    56,
      70,    71,     5,     6,     7,     3,   157,   123,   123,   125,
     125,    56,   123,   109,   125,   111,   185,   259,    22,    95,
       0,   107,   191,   107,   120,    70,    71,   257,    88,    91,
     100,   194,   107,    93,   120,   426,   120,    99,   125,   190,
      83,   629,   149,   100,   118,   120,   120,    97,    98,   204,
      20,    21,   164,   106,   122,   100,   109,    99,    95,   167,
      86,    87,    99,    99,     3,    83,   581,   279,    95,    95,
      99,   108,   108,   125,   106,   309,   309,   221,   148,   112,
     106,   148,   125,    22,    23,   117,   407,   149,   397,     3,
     160,   117,   120,   160,   164,   309,   124,    20,    21,    97,
      98,    99,   118,   106,   120,   167,   176,   214,   476,   106,
     172,   115,   116,   183,   117,   185,   119,   111,     3,   164,
     117,   191,     3,     3,   194,   106,   120,   189,   185,   461,
     120,   176,   647,   123,   191,   460,   206,   194,   183,   106,
     185,   111,   112,   255,   204,     3,   191,    86,    87,   194,
     117,   221,     3,   111,   221,   120,    95,    43,    44,   124,
      99,   206,   120,   554,   315,   407,     3,   106,    83,   108,
     120,    51,    52,    53,   124,   405,   120,   694,   117,    59,
     124,   289,    83,   253,   396,   255,   253,   429,   111,   112,
      97,    98,   421,    51,    52,    53,   120,   341,     0,    95,
     124,    59,    20,    21,   112,   275,   421,   120,   278,   279,
     255,   124,   111,   656,   455,   125,    97,    98,    99,   455,
     292,   125,   543,   295,   546,   534,   120,   289,    27,    28,
     124,     3,   302,   278,   279,   626,   112,   449,   450,   309,
     470,    43,   476,   476,   473,   474,    95,   327,   328,     0,
     491,   107,   493,   118,    56,   580,   485,   302,   473,   474,
     107,   120,   476,    22,   309,   124,   112,   221,   120,    71,
     485,   341,   124,   498,   341,    22,    23,   369,   370,   371,
     372,   672,   673,   113,   114,    87,   430,   678,    93,    94,
       3,   403,    43,   111,   112,   536,   112,   618,   100,   454,
     536,   543,   611,   106,   107,    56,   109,     3,   537,    22,
      23,   541,   644,   645,   117,     8,     9,   120,   365,   366,
      71,   124,   537,   393,   148,   716,   393,   397,     3,   492,
     397,   125,     3,   403,   112,   447,    87,   124,   729,    86,
      87,    51,    52,    53,   367,   368,   148,     3,    95,   100,
     107,     3,   582,   415,    23,   567,   426,   417,   403,   106,
     430,   121,   164,   430,    25,   435,   168,   362,   363,   364,
     117,   433,   120,    86,    87,    24,   618,   447,   202,   111,
     450,   183,    95,   185,   106,   455,    99,   341,   106,   191,
     373,   374,   194,   106,   454,   108,   503,   120,   106,   469,
     202,   107,   447,   120,   358,   450,   476,    96,   109,   109,
     455,   124,   123,   164,   118,   112,     3,   126,   648,   126,
     123,   491,   492,   493,   469,   123,   638,   539,   109,   253,
     500,   476,   183,   500,   185,   492,   124,   391,   120,   126,
     191,   126,     3,   194,   112,   107,   491,   492,   493,   593,
     594,   253,   106,   255,   566,   279,   120,   687,   602,     0,
       3,     3,   106,   106,   534,   694,   536,   534,   576,   539,
     123,   579,   580,   275,   428,   106,   430,   279,   720,   694,
      22,    23,   124,   124,   554,   106,   126,   557,    59,   124,
     120,   536,   120,   705,   539,   124,   566,   567,   109,   109,
     302,   107,    43,   615,   255,   118,   120,   309,   107,   721,
     107,   581,   667,   107,   576,    56,   107,   579,   580,   126,
     123,   566,   567,   593,   594,   637,   593,   594,   279,    42,
      71,    71,   602,    70,   604,   602,   581,   604,     3,     3,
     684,   124,   109,   106,    86,    87,    87,   207,   208,   209,
     210,   302,   107,    95,   118,   120,   626,     3,   309,   100,
     107,   107,   222,   223,   224,   225,   124,   637,   106,   681,
      48,   107,   396,   397,   106,   117,    22,    23,   402,   106,
     724,   107,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   637,   117,   396,   397,   550,   551,    26,   124,
     402,   403,   672,   673,   124,   559,   107,   667,   678,   679,
     690,   681,   679,    33,   684,   107,   120,   684,   107,   160,
     118,   109,   107,   164,   426,   449,   450,   168,   430,   453,
     124,   182,   202,   435,   215,   705,   681,   691,   705,   663,
      86,    87,   183,   376,   185,   447,   716,   449,   450,    95,
     191,   453,   403,   194,   724,   375,   377,   724,   389,   729,
     106,   636,   378,    41,    42,    43,   106,   469,   537,   109,
     557,   117,   112,    51,   476,   629,   478,   117,   491,   430,
     120,   109,   435,   123,   124,   125,    56,   493,   393,   557,
     492,   500,    70,   353,   122,   486,   415,   696,   449,   450,
     360,   361,   453,   536,    93,   659,   168,   478,   580,    87,
     534,    -1,    -1,    91,   255,    -1,    -1,    -1,   469,    -1,
       3,    99,    -1,   677,    -1,   476,    -1,   478,    -1,    -1,
      -1,    -1,   534,    -1,   275,    -1,    -1,   539,   279,    22,
      23,   492,    -1,   567,    -1,    -1,   700,    -1,    -1,    -1,
      -1,    -1,   554,    -1,    -1,   557,    -1,   417,   418,    -1,
      -1,   302,    -1,     3,   566,   567,    -1,    -1,   309,    -1,
     148,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   581,
     604,    -1,    22,    23,    -1,    -1,    -1,   611,    -1,   167,
     168,    -1,    -1,    -1,   172,    -1,    -1,   160,   176,    -1,
      -1,    -1,   604,    86,    87,    -1,    -1,   170,   171,   611,
      -1,   189,    95,   615,   638,   356,   567,    -1,   359,    -1,
      -1,    -1,    -1,    -1,   626,    -1,    -1,    -1,   206,    -1,
     581,    -1,    -1,    -1,    -1,   637,   638,   497,     3,   663,
      -1,    -1,    -1,    -1,    -1,   647,    86,    87,    -1,    -1,
     213,    -1,   393,    -1,    -1,    95,    -1,    22,    23,    99,
      -1,   663,   403,     3,    -1,    -1,   106,    -1,   108,    -1,
     672,   673,    -1,    -1,    -1,   253,   678,   117,    -1,   681,
      -1,   705,    22,    23,    -1,   426,    -1,   638,    -1,   430,
      -1,    -1,    -1,    -1,   435,    -1,   647,   721,    -1,    -1,
     278,    -1,    -1,   705,     3,   268,   447,    -1,   449,   450,
      -1,   289,   453,    -1,   716,    -1,    -1,    -1,    -1,   721,
      -1,    86,    87,    22,    23,    -1,    -1,   729,   469,    -1,
      95,    -1,    -1,    -1,    99,   476,    -1,   478,    -1,    -1,
      -1,   106,    -1,   108,    -1,   605,    86,    87,    -1,    -1,
      -1,   492,    -1,    -1,   705,    95,    -1,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,
     721,    -1,    -1,     3,    -1,    -1,    -1,    -1,   356,    -1,
      -1,   359,    -1,    -1,    -1,    -1,    -1,    86,    87,    -1,
      -1,    -1,    22,    23,   357,    -1,    95,    -1,   539,    -1,
      99,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,
      -1,    -1,    -1,   554,    -1,    -1,   557,    -1,    -1,   397,
      -1,    -1,    -1,    -1,    -1,   566,   567,    -1,    -1,   392,
     393,    -1,   395,    -1,    -1,    -1,    -1,   415,    -1,    -1,
     581,    41,    42,    -1,    44,    -1,    -1,   410,    -1,    -1,
      -1,    51,    -1,   416,    -1,   433,    86,    87,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    95,    -1,    -1,    -1,    99,
      70,   449,    -1,    -1,   615,   453,   106,   455,   108,    -1,
      -1,    -1,    22,    23,    -1,   626,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,   457,   458,   637,   638,    98,    99,
     478,    -1,    -1,    -1,    -1,    -1,   647,    -1,     3,    -1,
      -1,    -1,    -1,   491,    -1,   493,    -1,    -1,    -1,    -1,
      -1,    -1,   500,    -1,    -1,     3,    -1,    22,    23,    -1,
      -1,   672,   673,   496,    -1,   498,    -1,   678,    -1,    -1,
     681,    -1,    -1,    -1,    22,    23,    86,    87,   148,   149,
      -1,    -1,    -1,    -1,    -1,    95,   534,   157,   536,    99,
      -1,    -1,    -1,    -1,   705,    -1,   106,   167,   108,    -1,
      -1,    -1,   172,    -1,    -1,   716,   176,    -1,    -1,    -1,
     721,    -1,   182,   546,    -1,   726,    -1,    -1,   729,   189,
     190,    86,    87,    -1,    -1,    -1,    -1,    -1,   576,    -1,
      95,   579,   580,    -1,    99,    -1,   206,    -1,    86,    87,
      -1,   106,    -1,   108,    -1,   593,   594,    95,    -1,    -1,
      -1,    99,   222,    -1,   602,    -1,   604,    -1,   106,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    -1,   615,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   608,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   253,    -1,    -1,    -1,    -1,    -1,    -1,
     638,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   647,
      -1,   271,    -1,    -1,    -1,    -1,    -1,    -1,   278,    -1,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   289,
      -1,    -1,    -1,   656,   294,    -1,    -1,    -1,    -1,    22,
      23,   679,    -1,    -1,    -1,    -1,   684,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,   721,    -1,    -1,   724,    -1,   726,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    -1,   397,    -1,    -1,
     123,   124,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,   415,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   433,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,   455,    -1,    -1,    -1,    -1,
      -1,   461,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    84,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    -1,     3,    95,     5,     6,    -1,
      99,   491,    -1,   493,    -1,    -1,    -1,   106,    -1,   108,
     500,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   123,   124,    -1,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   534,    -1,   536,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   576,    95,     3,   579,
     580,    99,   100,   101,   102,   103,   104,   105,   106,    -1,
     108,    -1,   110,   593,   594,   113,   114,    -1,    -1,    -1,
      -1,    -1,   602,    -1,   604,    -1,    -1,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   644,   645,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    -1,
      85,     3,    -1,     5,     6,    -1,    -1,    -1,    -1,    -1,
      95,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   679,
      22,    23,    -1,    -1,   684,    -1,    -1,    -1,    30,    31,
      32,    -1,    34,    35,    36,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,   724,    -1,    68,    69,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,   105,   106,    -1,   108,     3,   110,     5,
       6,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,   126,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    69,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      86,    87,    88,    89,    -1,    -1,     3,    -1,    -1,    95,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,    -1,   108,    -1,   110,    22,    23,   113,   114,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,   124,   125,
     126,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    84,    85,    86,
      87,    88,    -1,     3,    -1,     5,     6,    -1,    95,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,   106,
      -1,   108,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   123,   124,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,     3,
     110,     5,     6,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,   126,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    69,    70,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,    -1,   108,     3,   110,     5,     6,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   125,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      68,    69,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,    -1,
     108,     3,   110,     5,     6,   113,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   125,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    -1,    34,    35,    36,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    68,    69,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,   105,   106,    -1,   108,     3,   110,     5,
       6,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    69,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    95,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,    -1,   108,     3,   110,     5,     6,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    -1,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    69,
      70,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,     3,
     110,     5,     6,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   125,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    69,    70,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,    -1,   108,     3,   110,     5,     6,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   125,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      68,    69,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,    -1,
     108,     3,   110,     5,     6,   113,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   125,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    -1,    34,    35,    36,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    68,    69,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    85,    86,    87,    88,    89,    -1,    -1,
       3,    -1,    -1,    95,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,   105,   106,    -1,   108,    -1,   110,    22,
      23,   113,   114,    -1,    -1,    -1,    29,    30,    31,    -1,
      -1,    -1,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,     3,    -1,     5,
       6,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,    -1,   108,     3,   110,     5,     6,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,    -1,
     110,    -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    94,    95,    96,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,    -1,   109,
      -1,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,    -1,   126,    93,    94,    95,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,     3,   109,    -1,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,    -1,
     126,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     3,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,     3,    -1,
      -1,    -1,   106,   107,   108,    -1,    -1,   111,   112,    -1,
      -1,    -1,    -1,   117,    -1,    -1,   120,    22,    23,    -1,
     124,    -1,    -1,    -1,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     3,    -1,    -1,    -1,    -1,
      95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,   106,    -1,   108,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,     3,    -1,    -1,    -1,   106,   107,
     108,    -1,    -1,   111,    -1,    -1,    -1,    -1,    -1,   117,
      -1,    -1,   120,    22,    23,   123,   124,    -1,    -1,    -1,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     3,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      99,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,
      22,    23,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     3,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,   108,    22,    23,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     3,    -1,    -1,    -1,    -1,
      95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,   106,    -1,   108,    22,    23,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     3,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,
     108,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    86,    87,    88,    -1,     3,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    86,    87,    88,    -1,     3,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,   108,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    85,    86,
      87,    88,    -1,     3,    -1,     5,     6,    -1,    95,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,   106,
      -1,   108,    22,    23,    -1,    -1,    -1,    -1,    -1,     5,
       6,     7,     8,     9,    10,    11,    -1,   124,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,     3,
     110,     5,     6,   113,   114,    -1,    -1,    93,    94,    -1,
      -1,    97,    98,    -1,   124,    -1,    -1,    -1,    22,    23,
     106,    -1,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,
     114,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    -1,    -1,    88,    -1,
      31,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,     3,   124,     5,     6,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    22,    23,    85,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    96,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,   109,    -1,
     111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,    -1,
     110,    -1,    -1,   113,   114,    -1,    -1,     3,   118,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    95,
      -1,    97,    98,     3,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,     3,    -1,     5,     6,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    22,    23,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,    -1,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    95,    -1,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,   106,    -1,   108,
      -1,   110,    22,    23,   113,   114,    -1,    -1,   117,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    22,    23,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    43,
      44,    -1,    46,    47,    48,    49,    50,   117,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    22,
      23,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,   106,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      22,    23,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,   106,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    22,    23,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,   106,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,     5,     6,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    22,    23,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,     3,
     110,     5,     6,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,    -1,   108,    -1,   110,   111,    -1,   113,
     114,     3,    -1,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,   105,   106,    -1,   108,     3,   110,     5,
       6,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,     3,    -1,
       5,     6,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    22,    23,    85,
      86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,    -1,   108,    -1,   110,    -1,    -1,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,     3,
      -1,     5,     6,    -1,    -1,    70,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    22,    23,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
       3,    -1,     5,     6,    -1,    -1,    70,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    22,
      23,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,   110,    -1,    -1,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,     3,    -1,     5,     6,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      22,    23,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,   106,    -1,   108,    -1,   110,    -1,    -1,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,     3,    -1,     5,     6,    -1,    -1,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    22,    23,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,    -1,   110,    -1,
      -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,     3,    -1,     5,     6,    -1,    -1,    70,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    22,    23,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,   100,
     101,   102,   103,   104,   105,   106,    -1,   108,    -1,   110,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,     3,    -1,     5,     6,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    22,    23,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,    -1,
     110,    -1,    -1,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,     3,    -1,     5,     6,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    22,    23,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,   106,    -1,   108,
      -1,   110,    -1,    -1,   113,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    95,    -1,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,    -1,
     108,    -1,   110,    22,    23,   113,   114,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    87,    88,
      22,    23,    -1,    -1,    -1,    -1,    95,    -1,    -1,    31,
      99,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    85,    86,    87,    88,    22,    23,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    31,    99,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    -1,
      85,    86,    87,    88,    22,    23,    -1,    -1,    -1,    -1,
      95,    -1,    -1,    31,    99,    -1,    -1,    -1,    -1,    -1,
      -1,   106,    -1,   108,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    86,    87,
      88,    22,    23,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      31,    99,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,
     108,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    86,    87,    88,    22,    23,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    31,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    86,    87,    88,    22,    23,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    31,    99,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,   108,    -1,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    85,    86,
      87,    88,    22,    23,    -1,    -1,    -1,    -1,    95,    -1,
      -1,    31,    99,    -1,    -1,    -1,    -1,    -1,    -1,   106,
      -1,   108,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    88,    22,
      23,    -1,    -1,    -1,    -1,    95,    -1,    -1,    31,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    85,    86,    87,    88,    22,    23,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    31,    99,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      86,    87,    88,    22,    23,    -1,    -1,    -1,    -1,    95,
      -1,    -1,    31,    99,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,   108,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      99,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,
      43,    44,    -1,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    31,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,   106,    54,    55,    56,    57,    58,    59,
      60,    61,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    -1,    -1,    88,    -1,
      31,    -1,    -1,    -1,    -1,    95,    96,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    85,    -1,    -1,    88,    -1,    31,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    22,    23,    85,    -1,    -1,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46,    47,    48,    49,    50,
      -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    43,    44,    95,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short yystos[] =
{
       0,     3,    22,    23,    29,    30,    31,    43,    44,    45,
      46,    47,    48,    49,    50,    54,    55,    56,    57,    58,
      59,    60,    61,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    95,    99,   106,   108,   124,   128,   131,   132,   135,
     136,   137,   138,   142,   196,   197,   198,   199,   200,   204,
     205,   209,   210,   211,   212,   213,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   227,   228,   238,
     239,   246,   247,   252,   253,   254,   255,   267,   268,   269,
     273,   274,   277,   269,   270,   271,     3,    46,    95,   214,
     101,     3,     3,   229,   112,   106,     3,    99,   132,   142,
     204,   223,     3,     5,     6,     7,     8,     9,    10,    11,
      15,    16,    17,    18,    19,    20,    21,    22,    93,    94,
      95,    97,    98,   106,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   133,   139,   223,   225,   226,    95,
     252,     3,   204,   272,     0,   142,    83,   134,   196,    83,
     112,    31,   124,   220,   220,   246,   252,    95,   120,   124,
     106,   109,   123,   233,   237,   248,   106,   117,   252,   271,
       3,   142,   143,   125,   270,   125,     3,   135,   204,    95,
     142,   125,   198,   125,   111,     3,   107,   118,    95,   140,
     141,   225,   267,   107,    22,   135,   112,     5,     6,    22,
      23,    62,    63,    70,    95,   100,   101,   102,   103,   104,
     105,   106,   108,   110,   113,   114,   129,   130,   131,   137,
     144,   147,   148,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   172,   174,   206,
     207,   208,   224,   225,   256,   220,   246,   252,   124,   237,
     142,   143,   247,   252,   131,   145,   172,   224,   125,   172,
     250,   143,   234,   235,   236,   125,   244,   245,   219,   220,
     261,   262,   263,   264,   265,   266,   169,   170,   178,   123,
     286,   287,     3,     3,   134,   204,     3,    51,    52,    53,
     124,   200,   220,   229,   238,   252,   275,   278,   279,   280,
     281,   283,   285,   197,   124,   142,   135,   197,     3,   230,
     231,   232,   198,   107,    95,   141,   271,    46,    48,    83,
     201,   202,   203,   264,   158,   158,   158,   158,   172,   173,
       3,   106,   147,   172,   175,   256,     3,   158,   204,   158,
     158,   158,    97,    98,     5,     6,     7,   106,   117,   119,
      27,    28,    22,   115,   116,   113,   114,    93,    94,    20,
      21,   111,   112,     8,     9,    23,   121,    24,    25,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    26,
     109,   122,   171,   120,   111,   106,   106,   225,   257,   258,
     259,   260,   267,   220,   246,   252,   124,   237,   244,   107,
     120,   126,   250,   251,   272,   120,   106,    22,    23,    32,
      34,    35,    36,    38,    39,    40,    41,    42,    68,    69,
     106,   126,   131,   137,   175,   179,   180,   181,   185,   186,
     187,   188,   189,   192,   194,   195,   213,   220,   245,   106,
     220,   252,   257,   267,   107,   120,    96,   109,   109,   118,
      59,   143,   275,   288,   289,   287,     3,   204,   287,   220,
     252,   281,   282,   123,   109,   284,   123,   285,   120,   124,
     126,   126,   135,   124,   126,   109,   120,   126,     3,   229,
     229,   112,   111,   120,   256,   107,   120,   107,   106,   149,
     150,   117,   158,    95,   131,   145,   146,   175,   131,   158,
     158,   159,   159,   159,   160,   160,   161,   161,   162,   162,
     162,   162,   163,   163,   164,   165,   166,   167,   168,   175,
     172,   208,   146,   257,   225,   258,   106,   117,   258,   220,
     246,   252,   124,   237,   244,   172,   120,   249,   234,   146,
     106,   106,   170,   177,   123,   124,   124,   106,   179,   106,
     124,   175,   245,   124,   188,   126,   220,   220,   252,   257,
     271,    96,   264,   172,   172,   275,   276,   272,    59,   290,
     120,   220,   252,   282,   124,   177,   177,   285,   252,   283,
     124,   177,   232,   109,   109,   201,   198,   202,   107,   172,
     158,   145,   106,   151,   226,   118,   107,   118,   123,   107,
     107,   225,   258,   261,   178,   220,   246,   124,   237,   244,
     250,   126,   107,   175,   190,   190,   123,   179,   187,   193,
     216,    42,   190,   124,    71,   182,   183,   220,   220,   252,
     257,    70,   242,   243,   143,   143,   289,   220,   252,   282,
     124,   256,   256,   111,   107,   256,   106,   155,   156,   117,
     152,   153,   154,   267,   158,   172,   258,   107,   118,   246,
     124,   244,   107,   107,   179,   190,   191,   106,   107,   106,
     182,   220,   252,   257,   106,   272,   272,   252,   282,   124,
      48,   107,   146,   175,   117,   153,   271,   124,   179,   179,
     124,   175,   179,    96,   184,   225,   240,   241,   256,   124,
     229,   156,   107,   118,   177,   243,    33,   175,   176,   107,
     107,   225,   252,   257,   120,   107,   109,   118,   179,   107,
     124,   245,   252,   257,   256,   131,   179
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
#line 647 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {
	(*yyvalp).declarationList = yyvsp[0].yystate.yysemantics.yysval.declarationList; translation_unit = (*yyvalp).declarationList;
	/*YYACCEPT*/
	;}
    break;

  case 3:
#line 655 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BoolExp(0) ;}
    break;

  case 4:
#line 656 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BoolExp(1) ;}
    break;

  case 5:
#line 657 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_Int32Exp(yyvsp[0].yystate.yysemantics.yysval.num) ;}
    break;

  case 7:
#line 659 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_StringExp(yyvsp[0].yystate.yysemantics.yysval.string_literal) ;}
    break;

  case 8:
#line 660 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_LStringExp(yyvsp[0].yystate.yysemantics.yysval.string_literal) ;}
    break;

  case 11:
#line 665 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = yyvsp[-1].yystate.yysemantics.yysval.exp;}
    break;

  case 13:
#line 669 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_IdExp($1)*/ ;}
    break;

  case 48:
#line 713 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_IdExp($1)*/ ;}
    break;

  case 51:
#line 716 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_UnopExp('~', A_IdExp(@2,$2))*/ ;}
    break;

  case 52:
#line 717 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {;}
    break;

  case 53:
#line 722 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = $1*/ ;}
    break;

  case 54:
#line 723 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {;}
    break;

  case 55:
#line 724 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {;}
    break;

  case 67:
#line 768 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {  ;}
    break;

  case 68:
#line 769 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_CallExp(yyvsp[-3].yystate.yyloc, yyvsp[-3].yystate.yysemantics.yysval.exp, yyvsp[-1].yystate.yysemantics.yysval.expList) ;}
    break;

  case 70:
#line 771 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = NULL ;}
    break;

  case 71:
#line 772 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = NULL ;}
    break;

  case 72:
#line 773 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '.', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 73:
#line 774 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '->', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 74:
#line 778 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).expList = new A_ExpList(yyvsp[0].yystate.yysemantics.yysval.exp, NULL) ;}
    break;

  case 75:
#line 779 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).expList = new A_ExpList(yyvsp[0].yystate.yysemantics.yysval.exp, yyvsp[-2].yystate.yysemantics.yysval.expList) ;}
    break;

  case 76:
#line 782 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).expList = NULL ;}
    break;

  case 79:
#line 787 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '++', yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 80:
#line 788 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '--', yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 81:
#line 789 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '*', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 82:
#line 790 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '&', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 83:
#line 791 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '+', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 84:
#line 792 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '-', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 85:
#line 793 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '!', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 86:
#line 794 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_UnopExp(yyvsp[-1].yystate.yyloc, '~', yyvsp[0].yystate.yysemantics.yysval.exp);}
    break;

  case 87:
#line 795 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {;}
    break;

  case 88:
#line 796 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {;}
    break;

  case 109:
#line 837 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_CastExp(yyvsp[-2].yystate.yysemantics.yysval.typeId, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 114:
#line 846 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '*', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 115:
#line 847 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '/', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 116:
#line 848 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '%', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 118:
#line 852 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '+', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 119:
#line 853 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '-', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 121:
#line 857 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '<<', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 122:
#line 858 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '>>', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 124:
#line 862 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '<', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 125:
#line 863 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '>', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 126:
#line 864 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '<=', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 127:
#line 865 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '>=', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 129:
#line 869 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '==', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 130:
#line 870 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '!=', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 132:
#line 874 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '&', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 134:
#line 878 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '^', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 136:
#line 882 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '|', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 142:
#line 894 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-4].yystate.yyloc, '?', yyvsp[-4].yystate.yysemantics.yysval.exp, A_BinopExp(yyvsp[-2].yystate.yyloc, ':', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp)) ;}
    break;

  case 155:
#line 911 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, '=', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 161:
#line 924 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = A_BinopExp(yyvsp[-2].yystate.yyloc, ',', yyvsp[-2].yystate.yysemantics.yysval.exp, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 165:
#line 934 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).exp = NULL ;}
    break;

  case 192:
#line 984 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_ExpStm(yyvsp[-1].yystate.yysemantics.yysval.exp) ;}
    break;

  case 193:
#line 987 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stmList = new A_StmList(yyvsp[0].yystate.yysemantics.yysval.stm, NULL) ;}
    break;

  case 194:
#line 988 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stmList = new A_StmList(yyvsp[-1].yystate.yysemantics.yysval.stm, yyvsp[0].yystate.yysemantics.yysval.stmList) ;}
    break;

  case 195:
#line 992 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_IfStm(yyvsp[-2].yystate.yysemantics.yysval.cond, yyvsp[0].yystate.yysemantics.yysval.stm, NULL) ;}
    break;

  case 196:
#line 993 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { A_IfStm(yyvsp[-4].yystate.yysemantics.yysval.cond, yyvsp[-2].yystate.yysemantics.yysval.stm, yyvsp[0].yystate.yysemantics.yysval.stm) ;}
    break;

  case 197:
#line 994 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_SwitchStm(yyvsp[-2].yystate.yysemantics.yysval.cond, yyvsp[0].yystate.yysemantics.yysval.stm) ;}
    break;

  case 198:
#line 997 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).cond = new A_Condition ;}
    break;

  case 201:
#line 1005 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_WhileStm(yyvsp[-2].yystate.yysemantics.yysval.cond, yyvsp[0].yystate.yysemantics.yysval.stm) ;}
    break;

  case 202:
#line 1006 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_DoWhileStm(yyvsp[-5].yystate.yysemantics.yysval.stm, yyvsp[-2].yystate.yysemantics.yysval.exp) ;}
    break;

  case 206:
#line 1015 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_ReturnStm(NULL) ;}
    break;

  case 207:
#line 1016 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_ReturnStm(yyvsp[-1].yystate.yysemantics.yysval.exp) ;}
    break;

  case 208:
#line 1020 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_DeclarationStm(yyvsp[0].yystate.yysemantics.yysval.declaration) ;}
    break;

  case 209:
#line 1026 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarationList = new A_DeclarationList(yyvsp[0].yystate.yysemantics.yysval.declaration, NULL) ;}
    break;

  case 210:
#line 1027 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarationList = new A_DeclarationList(yyvsp[-1].yystate.yysemantics.yysval.declaration, yyvsp[0].yystate.yysemantics.yysval.declarationList) ;}
    break;

  case 211:
#line 1036 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarationList = NULL ;}
    break;

  case 212:
#line 1037 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarationList = yyvsp[0].yystate.yysemantics.yysval.declarationList ;}
    break;

  case 221:
#line 1052 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 241:
#line 1095 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 242:
#line 1098 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = A_LinkageDeclaration(yyvsp[-3].yystate.yysemantics.yysval.string_literal, yyvsp[-1].yystate.yysemantics.yysval.declarationList) ;}
    break;

  case 243:
#line 1099 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = A_LinkageDeclaration(yyvsp[-1].yystate.yysemantics.yysval.string_literal, new A_DeclarationList(yyvsp[0].yystate.yysemantics.yysval.declaration, NULL)) ;}
    break;

  case 245:
#line 1106 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = A_NamespaceDefinition(yyvsp[-3].yystate.yysemantics.yysval.id, yyvsp[-1].yystate.yysemantics.yysval.declarationList) ;}
    break;

  case 248:
#line 1114 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {
										pPP2->GetToken();

										if ((pPP2->curtokpp->type == PP::CToken::tok_char || pPP2->curtokpp->type == PP::CToken::tok_symbol) && pPP2->curtokpp->symbol == '{')
										{
											pPP2->GetToken();

											while (!pPP2->_eof())
											{
												if ((pPP2->curtokpp->type == PP::CToken::tok_char || pPP2->curtokpp->type == PP::CToken::tok_symbol) && pPP2->curtokpp->symbol == '}')
													break;

												pPP2->GetToken();
											}
											pPP2->EatSymbol('}');
										}
										else
										{
											while (!pPP2->_eof())
											{
												if ((pPP2->curtokpp->type == PP::CToken::tok_symbol || pPP2->curtokpp->type == PP::CToken::tok_char) && pPP2->curtokpp->symbol == '}')
												{
													bLastTok = TRUE;
													break;
												}

												if ((pPP2->curtokpp->type == PP::CToken::tok_symbol || pPP2->curtokpp->type == PP::CToken::tok_char) && pPP2->curtokpp->symbol == ';')
													break;

												if (pPP2->curtokpp->type == PP::CToken::tok_symbol && pPP2->curtokpp->symbol == '\n')
													break;

												pPP2->GetToken();
											}
										}

										(*yyvalp).declaration = NULL;
									;}
    break;

  case 251:
#line 1158 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 252:
#line 1159 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 253:
#line 1160 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 255:
#line 1176 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 256:
#line 1178 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {
						(*yyvalp).declaration = A_SimpleDeclaration(yyvsp[-1].yystate.yysemantics.yysval.declspecList, NULL);
						;}
    break;

  case 258:
#line 1184 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 259:
#line 1185 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 260:
#line 1186 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 261:
#line 1187 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 262:
#line 1188 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 263:
#line 1189 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 264:
#line 1190 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL ;}
    break;

  case 265:
#line 1193 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.declspec, NULL) ;}
    break;

  case 266:
#line 1194 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declspecList = new A_DeclSpecList(yyvsp[0].yystate.yysemantics.yysval.declspec, yyvsp[-1].yystate.yysemantics.yysval.declspecList) ;}
    break;

  case 267:
#line 1203 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declspec = NULL ;}
    break;

  case 269:
#line 1205 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declspec = NULL ;}
    break;

  case 270:
#line 1206 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declspec = NULL ;}
    break;

  case 271:
#line 1207 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declspec = NULL ;}
    break;

  case 272:
#line 1266 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_AUTO ;}
    break;

  case 273:
#line 1267 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_REGISTER ;}
    break;

  case 274:
#line 1268 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_STATIC ;}
    break;

  case 275:
#line 1269 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_EXTERN ;}
    break;

  case 276:
#line 1270 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_MUTABLE ;}
    break;

  case 277:
#line 1271 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*TODO*/(*yyvalp).declSpecifierKeyword = A_DECLSPEC ;}
    break;

  case 278:
#line 1274 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_INLINE ;}
    break;

  case 279:
#line 1275 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_VIRTUAL ;}
    break;

  case 280:
#line 1276 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declSpecifierKeyword = A_EXPLICIT ;}
    break;

  case 285:
#line 1319 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_CHAR) ;}
    break;

  case 286:
#line 1320 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_WCHAR_T) ;}
    break;

  case 287:
#line 1321 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_BOOL) ;}
    break;

  case 288:
#line 1322 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_SHORT) ;}
    break;

  case 289:
#line 1323 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_INT) ;}
    break;

  case 290:
#line 1324 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A___INT64) ;}
    break;

  case 291:
#line 1325 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_LONG) ;}
    break;

  case 292:
#line 1326 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_SIGNED) ;}
    break;

  case 293:
#line 1327 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_UNSIGNED) ;}
    break;

  case 294:
#line 1328 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_FLOAT) ;}
    break;

  case 295:
#line 1329 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_DOUBLE) ;}
    break;

  case 296:
#line 1330 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_VOID) ;}
    break;

  case 297:
#line 1338 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = NULL ;}
    break;

  case 298:
#line 1339 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = NULL ;}
    break;

  case 299:
#line 1340 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = yyvsp[0].yystate.yysemantics.yysval.typespec ;}
    break;

  case 300:
#line 1341 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = NULL ;}
    break;

  case 301:
#line 1342 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = NULL ;}
    break;

  case 306:
#line 1361 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { ASSERT(0) ;}
    break;

  case 307:
#line 1364 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_Enum(yyvsp[-3].yystate.yysemantics.yysval.id, yyvsp[-1].yystate.yysemantics.yysval.enumList) ;}
    break;

  case 308:
#line 1367 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).id = NULL ;}
    break;

  case 310:
#line 1371 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).enumList = new A_EnumDefList(yyvsp[0].yystate.yysemantics.yysval.enumDef, NULL) ;}
    break;

  case 311:
#line 1372 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).enumList = yyvsp[-1].yystate.yysemantics.yysval.enumList ;}
    break;

  case 312:
#line 1373 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).enumList = new A_EnumDefList(yyvsp[0].yystate.yysemantics.yysval.enumDef, yyvsp[-2].yystate.yysemantics.yysval.enumList) ;}
    break;

  case 313:
#line 1376 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).enumList = NULL ;}
    break;

  case 314:
#line 1377 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).enumList = yyvsp[0].yystate.yysemantics.yysval.enumList ;}
    break;

  case 315:
#line 1380 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).enumDef = A_EnumDef(yyvsp[0].yystate.yysemantics.yysval.id, NULL) ;}
    break;

  case 316:
#line 1381 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).enumDef = A_EnumDef(yyvsp[-2].yystate.yysemantics.yysval.id, yyvsp[0].yystate.yysemantics.yysval.exp) ;}
    break;

  case 324:
#line 1401 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = yyvsp[0].yystate.yysemantics.yysval.declaration; /*printf("function_definition1\n")*/ ;}
    break;

  case 325:
#line 1408 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL/*$$ = A_FunDef(@2, $1, $2, $3)*/ ;}
    break;

  case 326:
#line 1409 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL/*$$ = A_FunDef(@2, $1, $2, $3)*/ ;}
    break;

  case 327:
#line 1410 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL/*$$ = A_FunDef(@2, $1, $2, $3)*/ ;}
    break;

  case 328:
#line 1411 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL/*$$ = A_FunDef(@2, $1, $2, $3)*/ ;}
    break;

  case 329:
#line 1412 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaration = NULL/*$$ = A_FunDef(@2, $1, $2, $3)*/ ;}
    break;

  case 338:
#line 1453 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = NULL ;}
    break;

  case 339:
#line 1454 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).stm = A_CompoundStm(yyvsp[-1].yystate.yysemantics.yysval.stmList) ;}
    break;

  case 340:
#line 1459 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaratorList = new A_DeclaratorList(yyvsp[0].yystate.yysemantics.yysval.declarator, NULL) ;}
    break;

  case 341:
#line 1460 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaratorList = new A_DeclaratorList(yyvsp[0].yystate.yysemantics.yysval.declarator, yyvsp[-2].yystate.yysemantics.yysval.declaratorList) ;}
    break;

  case 353:
#line 1492 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {(*yyvalp).declarator = A_DirectDeclaratorDeclarator(yyvsp[0].yystate.yysemantics.yysval.directDeclarator) ;}
    break;

  case 354:
#line 1493 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarator = A_PtrDeclarator(yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 356:
#line 1502 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_DirectDeclaratorId(@1, $1)*/ ;}
    break;

  case 357:
#line 1503 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorParen(yyvsp[-5].yystate.yysemantics.yysval.directDeclarator, yyvsp[-3].yystate.yysemantics.yysval.paramDecls) ;}
    break;

  case 358:
#line 1504 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorArray(yyvsp[-3].yystate.yysemantics.yysval.directDeclarator, yyvsp[-1].yystate.yysemantics.yysval.exp) ;}
    break;

  case 359:
#line 1505 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorDeclarator(yyvsp[-1].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 360:
#line 1526 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {
(*yyvalp).exp = yyvsp[0].yystate.yysemantics.yysval.exp
;}
    break;

  case 361:
#line 1530 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {;}
    break;

  case 362:
#line 1533 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = new A_TypeId($1, $2)*/ ;}
    break;

  case 363:
#line 1534 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = new A_TypeId($1, $2)*/ ;}
    break;

  case 364:
#line 1535 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = new A_TypeId($1, $2)*/ ;}
    break;

  case 365:
#line 1536 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = new A_TypeId($1, $2)*/ ;}
    break;

  case 366:
#line 1556 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {(*yyvalp).declarator = A_DirectDeclaratorDeclarator(yyvsp[0].yystate.yysemantics.yysval.directDeclarator) ;}
    break;

  case 367:
#line 1557 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarator = A_PtrDeclarator(yyvsp[0].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 368:
#line 1560 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarator = NULL ;}
    break;

  case 370:
#line 1564 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorParen(yyvsp[-5].yystate.yysemantics.yysval.directDeclarator, yyvsp[-3].yystate.yysemantics.yysval.paramDecls) ;}
    break;

  case 371:
#line 1565 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    {  ;}
    break;

  case 372:
#line 1566 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).directDeclarator = A_DirectDeclaratorDeclarator(yyvsp[-1].yystate.yysemantics.yysval.declarator) ;}
    break;

  case 373:
#line 1569 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).directDeclarator = NULL ;}
    break;

  case 375:
#line 1573 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).paramDecls = new A_ParameterDeclarations(yyvsp[0].yystate.yysemantics.yysval.typeIdList, false) ;}
    break;

  case 376:
#line 1574 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).paramDecls = new A_ParameterDeclarations(yyvsp[-1].yystate.yysemantics.yysval.typeIdList, true) ;}
    break;

  case 377:
#line 1575 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).paramDecls = new A_ParameterDeclarations(yyvsp[-2].yystate.yysemantics.yysval.typeIdList, true) ;}
    break;

  case 378:
#line 1582 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typeIdList = new A_TypeIdList(yyvsp[0].yystate.yysemantics.yysval.typeId, NULL) ;}
    break;

  case 379:
#line 1583 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typeIdList = new A_TypeIdList(yyvsp[0].yystate.yysemantics.yysval.typeId, yyvsp[-2].yystate.yysemantics.yysval.typeIdList) ;}
    break;

  case 380:
#line 1586 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typeIdList = NULL ;}
    break;

  case 402:
#line 1633 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_CONST) ;}
    break;

  case 403:
#line 1634 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_SimpleType(A_VOLATILE) ;}
    break;

  case 410:
#line 1652 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).typespec = A_ClassDef(yyvsp[-3].yystate.yyloc, yyvsp[-3].yystate.yysemantics.yysval.classHead) ;}
    break;

  case 411:
#line 1655 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).classKey = A_CLASSKEY_CLASS ;}
    break;

  case 412:
#line 1656 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).classKey = A_CLASSKEY_STRUCT ;}
    break;

  case 413:
#line 1657 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).classKey = A_CLASSKEY_UNION ;}
    break;

  case 414:
#line 1660 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PRIVATE ;}
    break;

  case 415:
#line 1661 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PROTECTED ;}
    break;

  case 416:
#line 1662 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PUBLIC ;}
    break;

  case 417:
#line 1665 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).accessSpec = A_ACCESS_PROTECTED ;}
    break;

  case 419:
#line 1669 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).classHead = new A_ClassHead(yyvsp[0].yystate.yyloc, yyvsp[0].yystate.yysemantics.yysval.classKey, NULL, NULL) ;}
    break;

  case 420:
#line 1670 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).classHead = new A_ClassHead(yyvsp[-2].yystate.yyloc, yyvsp[-2].yystate.yysemantics.yysval.classKey, yyvsp[-1].yystate.yysemantics.yysval.id, yyvsp[0].yystate.yysemantics.yysval.baseSpecifierList) ;}
    break;

  case 423:
#line 1675 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).memberSpec = A_MemberDecl(yyvsp[-1].yystate.yysemantics.yysval.declaration, yyvsp[0].yystate.yysemantics.yysval.memberSpec) ;}
    break;

  case 424:
#line 1676 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).memberSpec = A_MemberAccessSpec(yyvsp[-2].yystate.yysemantics.yysval.accessSpec, yyvsp[0].yystate.yysemantics.yysval.memberSpec) ;}
    break;

  case 427:
#line 1681 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_SimpleDeclaration(NULL, $1)*/ ;}
    break;

  case 428:
#line 1682 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_SimpleDeclaration(NULL, $1)*/ ;}
    break;

  case 429:
#line 1683 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_SimpleDeclaration(NULL, $1)*/ ;}
    break;

  case 430:
#line 1684 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { /*$$ = A_SimpleDeclaration(NULL, $1)*/ ;}
    break;

  case 434:
#line 1707 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaratorList = new A_DeclaratorList(yyvsp[0].yystate.yysemantics.yysval.declarator, NULL) ;}
    break;

  case 435:
#line 1708 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declaratorList = new A_DeclaratorList(yyvsp[0].yystate.yysemantics.yysval.declarator, yyvsp[-2].yystate.yysemantics.yysval.declaratorList) ;}
    break;

  case 439:
#line 1717 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).declarator = NULL ;}
    break;

  case 442:
#line 1739 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).memberSpec = NULL ;}
    break;

  case 444:
#line 1745 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).baseSpecifierList = yyvsp[0].yystate.yysemantics.yysval.baseSpecifierList ;}
    break;

  case 445:
#line 1748 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).baseSpecifierList = NULL ;}
    break;

  case 447:
#line 1752 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).baseSpecifierList = new A_BaseSpecifierList(yyvsp[0].yystate.yysemantics.yysval.id, NULL) ;}
    break;

  case 448:
#line 1753 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).baseSpecifierList = new A_BaseSpecifierList(yyvsp[0].yystate.yysemantics.yysval.id, yyvsp[-2].yystate.yysemantics.yysval.baseSpecifierList) ;}
    break;

  case 449:
#line 1756 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).id = yyvsp[0].yystate.yysemantics.yysval.id ;}
    break;

  case 450:
#line 1757 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).id = yyvsp[0].yystate.yysemantics.yysval.id ;}
    break;

  case 451:
#line 1758 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"
    { (*yyvalp).id = yyvsp[0].yystate.yysemantics.yysval.id ;}
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
#line 5232 "c:\\mmstudio\\src\\ljavac\\cpp_parse.tab.c"
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


#line 1766 "c:\\mmstudio\\src\\ljavac\\cpp_parse.y"


static A_Declaration* Merge (YYSTYPE& x0, YYSTYPE& x1)
{
	return A_Declaration2(x0.declaration, x1.declaration);
}

static A_Stm*
     stmtMerge (YYSTYPE& x0, YYSTYPE& x1)
     {
	  //YYSTYPE ytype;
     //  printf ("<OR> ");
      // return ytype;

		A_Stm* p = new A_Stm;
		p->kind = A_Stm::A_EXP_OR_DECLARATION;
		p->EXP_OR_DECL.exp = x1.exp;
		p->EXP_OR_DECL.declaration = x0.declaration;
		 return p;
     }

