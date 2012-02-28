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
/* Line 1985 of glr.c.  */
#line 100 "c:\\mmstudio\\extras\\ljavac\\pp_parse.tab.h"
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE pp_lval;

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

extern YYLTYPE pp_lloc;


