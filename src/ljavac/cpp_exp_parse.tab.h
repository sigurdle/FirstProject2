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
/* Line 1985 of glr.c.  */
#line 214 "c:\\mmstudio\\src\\ljavac\\cpp_exp_parse.tab.h"
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE cpp_exp_lval;

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

extern YYLTYPE cpp_exp_lloc;


