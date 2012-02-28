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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRING_LITERAL = 258,
     INTEGER_LITERAL = 259,
     identifier = 260,
     OR_KW = 261,
     AND_KW = 262,
     MOD_KW = 263,
     NOT_KW = 264,
     LEQ = 265,
     GEQ = 266,
     EQUAL = 267,
     NOT_EQUAL = 268
   };
#endif
#define STRING_LITERAL 258
#define INTEGER_LITERAL 259
#define identifier 260
#define OR_KW 261
#define AND_KW 262
#define MOD_KW 263
#define NOT_KW 264
#define LEQ 265
#define GEQ 266
#define EQUAL 267
#define NOT_EQUAL 268




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 15 "c:\\mmstudio\\src\\LFC\\formula_parse.y"
typedef union YYSTYPE {
int num;
char* id;
char* string_literal;
A_Exp* exp;
//A_Stm* stm;
//A_IdList* idlist;
} YYSTYPE;
/* Line 1248 of yacc.c.  */
#line 71 "c:\\mmstudio\\src\\LFC\\formula_parse.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE formula_lval;

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

extern YYLTYPE formula_lloc;


