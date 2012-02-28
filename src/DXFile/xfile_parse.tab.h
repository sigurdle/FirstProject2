
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 13 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\DXFile\\xfile_parse.y"

int intValue;
float floatValue;
StringA* pName;
Member* pMember;
DataType* pDatatype;
Template* pTemplate;
Dimension* pDimension;



/* Line 1676 of yacc.c  */
#line 92 "xfile_parse.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE xfile_lval;

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

extern YYLTYPE xfile_lloc;

