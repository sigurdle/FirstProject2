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
/* Line 1985 of glr.c.  */
#line 273 "c:\\mmstudio\\src\\ljavac\\cpp_parse.tab.h"
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE cpp_lval;

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

extern YYLTYPE cpp_lloc;


