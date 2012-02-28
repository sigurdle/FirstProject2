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
/* Line 1248 of yacc.c.  */
#line 183 "c:\\mmstudio\\src\\SQL\\sql_parse.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE sql_lval;

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

extern YYLTYPE sql_lloc;


