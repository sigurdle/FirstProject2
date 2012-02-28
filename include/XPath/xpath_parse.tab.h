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
/* Line 1248 of yacc.c.  */
#line 98 "c:\\mmstudio\\src\\XPath\\xpath_parse.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE xpath_lval;

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

extern YYLTYPE xpath_lloc;


