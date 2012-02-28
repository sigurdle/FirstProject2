/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     TOKEN_OBRACE = 258,
     TOKEN_CBRACE = 259,
     TOKEN_OBRACKET = 260,
     TOKEN_CBRACKET = 261,
     TOKEN_OPAREN = 262,
     TOKEN_CPAREN = 263,
     TOKEN_CHAR = 264,
     TOKEN_UCHAR = 265,
     TOKEN_WORD = 266,
     TOKEN_DWORD = 267,
     TOKEN_SWORD = 268,
     TOKEN_SDWORD = 269,
     TOKEN_FLOAT = 270,
     TOKEN_DOUBLE = 271,
     TOKEN_CSTRING = 272,
     TOKEN_LPSTR = 273,
     TOKEN_GUID = 274,
     TOKEN_TEMPLATE = 275,
     TOKEN_ARRAY = 276,
     TOKEN_SEMICOLON = 277,
     TOKEN_COMMA = 278,
     TOKEN_DOT = 279,
     TOKEN_FNUM = 280,
     TOKEN_INTEGER = 281,
     TOKEN_NAME = 282,
     TOKEN_STRING = 283
   };
#endif
/* Tokens.  */
#define TOKEN_OBRACE 258
#define TOKEN_CBRACE 259
#define TOKEN_OBRACKET 260
#define TOKEN_CBRACKET 261
#define TOKEN_OPAREN 262
#define TOKEN_CPAREN 263
#define TOKEN_CHAR 264
#define TOKEN_UCHAR 265
#define TOKEN_WORD 266
#define TOKEN_DWORD 267
#define TOKEN_SWORD 268
#define TOKEN_SDWORD 269
#define TOKEN_FLOAT 270
#define TOKEN_DOUBLE 271
#define TOKEN_CSTRING 272
#define TOKEN_LPSTR 273
#define TOKEN_GUID 274
#define TOKEN_TEMPLATE 275
#define TOKEN_ARRAY 276
#define TOKEN_SEMICOLON 277
#define TOKEN_COMMA 278
#define TOKEN_DOT 279
#define TOKEN_FNUM 280
#define TOKEN_INTEGER 281
#define TOKEN_NAME 282
#define TOKEN_STRING 283




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 13 "c:\\mmstudio\\src\\Browser\\xfile_parse.y"
typedef union YYSTYPE {
int intValue;
float floatValue;
StringA* pName;
Member* pMember;
DataType* pDatatype;
Template* pTemplate;
Dimension* pDimension;
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 104 "../../src/Browser/xfile_parse.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE xfile_lval;

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

extern YYLTYPE xfile_lloc;


