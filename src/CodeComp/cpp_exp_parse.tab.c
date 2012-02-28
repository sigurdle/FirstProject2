
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         cpp_exp_parse
#define yylex           cpp_exp_lex
#define yyerror         cpp_exp_error
#define yylval          cpp_exp_lval
#define yychar          cpp_exp_char
#define yydebug         cpp_exp_debug
#define yynerrs         cpp_exp_nerrs
#define yylloc          cpp_exp_lloc

/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"


//#define LOG(x,...)

//#define LOG DebugTrace
#define LOG(x)

#define YYERROR_VERBOSE

#define YYMAXDEPTH	80000

//struct PP_TokenList;

extern TemplateParams* /*Array<System::TemplateParameter*, System::__gc_allocator>*/ templateParams;

Scope* g_lastScope;

ClassType* g_pClass2 = NULL;

stack<ClassType*> g_pClassStack;

stack<ast::A_ClassDef*> g_classes;
stack<ast::Declaration*> g_templates;

//extern PP_TokenList* tlist;

//bool bLastTok = false;

ast::Expression2List* ptoken;

extern CGlobal* g_pGlobal;

//Type* GetNestedType(CGlobal* pGlobal, Scope* pGlobalScope, Scope* pScope, ast::Expression* exp);

Scope* parse_LookupScopeName(Scope* pScope, StringIn name);
Scope* parse_LookupScopeNameRecurse(Scope* pScope, StringIn name);

Type* parse_LookupTypeName(Scope* pScope, StringIn name);
Type* parse_LookupTypeNameRecurse(Scope* pScope, StringIn name);

extern ClassType* g_pClass;

stack<int> g_tokstack;

//stack<Scope*> g_cur_scopeStack;

//int nscopestack = 0;
stack<Scope*> g_scopeStack;
stack<Scope*> g_scopeStack2;

stack<stack<Scope*> > g_scopeStack2Stack;
Scope* g_pScope;
//Scope* g_pScope1;
Scope* g_pScope2;
//Scope* g_pLastScope;

//StringA* test_name;

void DoImport(StringA* filename);

void Do(ast::ExpressionList* attribute_spec, ast::Declaration* d);
void DoTp(ast::TemplateDeclaration* td);
void Do_class_specifier_head(ast::A_ClassHead* head);
void Do(ast::A_ClassDef* classdef);
//void Do_elaborated_class(ast::A_Class* elaborated_class);
void Do_TParam(ast::TemplateParameter* typeparam, ast::Expression* initexp = nullptr);

extern int cpp2_lex();
extern bool is_parse_exp;
extern bool use_cpp_lex;

static int cpp_exp_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/)
{
	if (ptoken == NULL && use_cpp_lex)
	{
	//	ASSERT(cpp_exp_lloc.filename != (StringA*)0xcccccccc);
		return cpp2_lex();
}

	if (!g_tokstack.empty())
	{
		int token = g_tokstack.top();
		g_tokstack.pop();
		return token;

	/*if (g_exp_lasttok != -1)
	{
		int token = g_exp_lasttok;
		g_exp_lasttok = -1;
		return token;
	}
	*/
	}

	if (ptoken)
	{
		int token = ptoken->head->m_token;

		if (ptoken->head->m_token == /*PP::CToken::tok_symbol && token->symbol ==*/ '@')
		{
		MessageBeep(-1);
		}

		cpp_exp_lloc.first_line = ptoken->head->m_linepos;
		cpp_exp_lloc.first_column = ptoken->head->m_column;

		cpp_exp_lloc.filename = ptoken->head->m_filename.m_stringObject;
		/*
		cpp_exp_lloc.filename = dynamic_cast<StringA*>(ptoken->head->m_filename.m_stringObject);
		if (cpp_exp_lloc.filename == nullptr)
			cpp_exp_lloc.filename = dynamic_cast<StringW*>(ptoken->head->m_filename.m_stringObject);
		*/
		if (cpp_exp_lloc.filename) cpp_exp_lloc.filename->IncRef();

		if (token == YTY)
		{
			cpp_exp_lval.pScope = ptoken->head->m_pScope;
			LOG("YTY ");
		//	g_scopeStack.clear();
		}
		else if (token == YTT)
		{
		//	cpp_exp_lval.pScope = ptoken->head->m_pScope;
			LOG("YTT ");
		}
		else if (token == STRING_LITERAL)
		{
			cpp_exp_lval.string_literal = ptoken->head->m_string;
			LOG("\"" << String(ptoken->head->m_string) << "\"");
		}
		else if (token == CHAR_LITERAL)
		{
			cpp_exp_lval.num = ptoken->head->u.m_int32;
		//	LOG("\"%s\"", ptoken->head->m_string->c_str());
		}
		else if (token == INTEGER_LITERAL)
		{
			cpp_exp_lval.num = ptoken->head->u.m_int32;
			LOG((int)ptoken->head->u.m_int32);
		}
		else if (token == DOUBLE_LITERAL)
		{
			cpp_exp_lval.doubleValue = ptoken->head->u.m_double;
			//LOG("%f", ptoken->head->u.m_double);
		}
		else if (token == IMPORT_KW)
		{
			cpp_exp_lval.string_literal = ptoken->head->m_string;
			//LOG("%f", ptoken->head->u.m_double);
		}
		else if (token == TWO_COLON)
		{
			LOG("::");
		//	g_pScope2 = g_pLastScope;
		}
		else if (token == IDENTIFIER)
		{
			cpp_exp_lval.id = ptoken->head->m_string;
			LOG(CString(ptoken->head->m_string) << " ");
			ptoken = ptoken->tail;
			return IDENTIFIER;
		}
		
		ptoken = ptoken->tail;
		return token;
	}
	else
	{
		return -1;
	}
}

void cpp_exp_error (/*YYLTYPE *llocp,*/ char const *s);
/*#define YYERROR_VERBOSE*/

#define yyfalse	0
#define yytrue		1

union YYSTYPE;

ast::A_Stm* stmtMerge (YYSTYPE& x0, YYSTYPE& x1);
//ast::A_Declaration* Merge (YYSTYPE& x0, YYSTYPE& x1);

//ast::A_TemplateArgument* template_argument_merge (YYSTYPE& x0, YYSTYPE& x1);

ast::A_ExpOrDecl* m_g_exp_or_decl;

extern ast::DeclarationList* translation_unit;
extern ast::Expression* g_exp;

     

/* Line 189 of yacc.c  */
#line 274 "cpp_exp_parse.tab.c"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EXP_TOKEN = 258,
     DECLS_TOKEN = 259,
     IDENTIFIER = 260,
     identifier_lparen = 261,
     PLUSPLUS = 262,
     MINUSMINUS = 263,
     ARROW = 264,
     EQUAL = 265,
     NOT_EQUAL = 266,
     ASSIGN_PLUS = 267,
     ASSIGN_MINUS = 268,
     ASSIGN_OR = 269,
     ASSIGN_XOR = 270,
     ASSIGN_AND = 271,
     ASSIGN_MUL = 272,
     ASSIGN_DIV = 273,
     ASSIGN_MOD = 274,
     ASSIGN_LSHIFT = 275,
     ASSIGN_RSHIFT = 276,
     LEQ = 277,
     GEQ = 278,
     STAR = 279,
     BITAND = 280,
     BITOR = 281,
     BITXOR = 282,
     LAND = 283,
     LOR = 284,
     DOT_STAR = 285,
     ARROW_STAR = 286,
     NAMESPACE_KW = 287,
     USING_KW = 288,
     EXTERN_KW = 289,
     IF_KW = 290,
     ELSE_KW = 291,
     SWITCH_KW = 292,
     CASE_KW = 293,
     DEFAULT_KW = 294,
     GOTO_KW = 295,
     BREAK_KW = 296,
     CONTINUE_KW = 297,
     FOR_KW = 298,
     DO_KW = 299,
     WHILE_KW = 300,
     CONST_KW = 301,
     VOLATILE_KW = 302,
     TYPEDEF_KW = 303,
     TYPENAME_KW = 304,
     ENUM_KW = 305,
     CLASS_KW = 306,
     STRUCT_KW = 307,
     UNION_KW = 308,
     PRIVATE_KW = 309,
     PROTECTED_KW = 310,
     PUBLIC_KW = 311,
     AUTO_KW = 312,
     REGISTER_KW = 313,
     STATIC_KW = 314,
     MUTABLE_KW = 315,
     INLINE_KW = 316,
     VIRTUAL_KW = 317,
     EXPLICIT_KW = 318,
     FRIEND_KW = 319,
     FALSE_KW = 320,
     TRUE_KW = 321,
     STATIC_ASSERT_KW = 322,
     STATIC_CAST_KW = 323,
     REINTERPRET_CAST_KW = 324,
     DYNAMIC_CAST_KW = 325,
     CONST_CAST_KW = 326,
     RETURN_KW = 327,
     TRY_KW = 328,
     THROW_KW = 329,
     CATCH_KW = 330,
     CHAR_KW = 331,
     WCHAR_T_KW = 332,
     BOOL_KW = 333,
     SHORT_KW = 334,
     INT_KW = 335,
     INTERFACE_KW = 336,
     LONG_KW = 337,
     SIGNED_KW = 338,
     UNSIGNED_KW = 339,
     FLOAT_KW = 340,
     DOUBLE_KW = 341,
     VOID_KW = 342,
     TEMPLATE_KW = 343,
     EXPORT_KW = 344,
     NULLPTR_KW = 345,
     CONSTEXPR_KW = 346,
     DECLTYPE_KW = 347,
     __FLOAT32_KW = 348,
     __FLOAT64_KW = 349,
     __INT8_KW = 350,
     __INT16_KW = 351,
     __INT32_KW = 352,
     __INT64_KW = 353,
     __INT128_KW = 354,
     __CDECL_KW = 355,
     __STDCALL_KW = 356,
     __FASTCALL_KW = 357,
     __DECLSPEC_KW = 358,
     __ASM_KW = 359,
     LSHIFT = 360,
     RSHIFT = 361,
     TWO_COLON = 362,
     THREE_DOTS = 363,
     NEW_KW = 364,
     DELETE_KW = 365,
     OPERATOR_KW = 366,
     SIZEOF_KW = 367,
     TYPEID_KW = 368,
     STRING_LITERAL = 369,
     LSTRING_LITERAL = 370,
     CHAR_LITERAL = 371,
     INTEGER_LITERAL = 372,
     DOUBLE_LITERAL = 373,
     IMPORT_KW = 374,
     TEMPLATE_NAME = 375,
     ATTRIBUTE_KW = 376,
     THIS_KW = 377,
     NTA = 378,
     YTA = 379,
     YTT = 380,
     NTY = 381,
     YTY = 382,
     CTORN = 383,
     SHIFT_THERE = 384
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 197 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"

LONGLONG num;
double doubleValue;
System::StringA* id;
System::StringA* string_literal;
ast::A_ClassKey classKey;
ast::A_ClassHead* classHead;
AccessSpec accessSpec;
ast::DeclSpecifierKeyword declSpecifierKeyword;
ast::A_MemberSpec* memberSpec;
ast::Condition* cond;
ast::Expression* exp;
ast::ExpressionList* expList;

ast::Expression2* exp2;
ast::Expression2List* exp2List;

ast::A_ExpOrDecl* exp_or_decl;

ast::Initializer* initializer;

ast::InitDeclarator* initDeclarator;
ast::InitDeclaratorList* initDeclaratorList;

ast::A_Stm* stm;
ast::CompoundStm* compoundstm;
ast::A_StmList* stmList;
ast::A_Declarator* declarator;
ast::A_DirectDeclarator* directDeclarator;
ast::Declaration* declaration;
ast::DeclarationList* declarationList;
ast::A_DeclaratorList* declaratorList;
ast::A_TypeId* typeId;
ast::A_TypeIdList* typeIdList;

ast::TemplateParameter* templateParameter;
ast::TemplateParameterList* templateParameterList;

ast::A_TemplateArgument* templateArgument;
ast::A_TemplateArgumentList* templateArgumentList;

Scope* pScope;

ast::A_DeclSpecExt* declspecExt;
ast::A_DeclSpecExtList* declspecExtList;

ast::A_DeclSpec* declspec;
ast::A_DeclSpec* typespec;
ast::DeclSpecList* declspecList;
ast::ParameterDeclarations* paramDecls;
ast::EnumDefinition* enumDef;
ast::EnumDefList* enumList;
ast::A_BaseSpecifier* baseSpecifier;
ast::A_BaseSpecifierList* baseSpecifierList;
ast::BasicTypeSpecifier simpleTypeSpec;



/* Line 214 of yacc.c  */
#line 498 "cpp_exp_parse.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 523 "cpp_exp_parse.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  187
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3930

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  151
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  216
/* YYNRULES -- Number of rules.  */
#define YYNRULES  622
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1049

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   384

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   147,     2,   134,     2,   146,     2,     2,
     130,   132,     2,   143,   131,   144,   149,   145,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   148,   133,
     137,   139,   138,   150,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   140,     2,   141,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   135,     2,   136,   142,     2,     2,     2,
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
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    15,    16,    18,
      19,    21,    29,    31,    34,    38,    41,    44,    46,    48,
      50,    56,    60,    62,    64,    65,    72,    73,    74,    83,
      84,    85,    94,    96,   100,   102,   104,   108,   111,   116,
     119,   124,   131,   134,   137,   139,   142,   144,   147,   149,
     152,   154,   158,   159,   167,   172,   174,   176,   180,   187,
     192,   194,   197,   198,   203,   205,   207,   211,   218,   223,
     225,   228,   229,   234,   236,   238,   242,   249,   254,   256,
     260,   261,   263,   268,   269,   271,   273,   275,   278,   280,
     282,   284,   286,   288,   290,   292,   294,   297,   298,   300,
     302,   306,   308,   312,   313,   315,   318,   323,   326,   331,
     334,   337,   339,   342,   344,   346,   349,   355,   357,   360,
     362,   365,   368,   370,   372,   375,   378,   380,   382,   384,
     387,   388,   390,   397,   402,   408,   412,   416,   418,   420,
     422,   424,   426,   428,   430,   432,   434,   436,   440,   442,
     447,   449,   452,   453,   460,   461,   468,   471,   474,   476,
     479,   482,   484,   487,   490,   492,   494,   498,   502,   506,
     510,   515,   520,   525,   527,   531,   533,   536,   538,   542,
     544,   548,   551,   555,   557,   561,   563,   565,   569,   573,
     575,   577,   579,   581,   583,   585,   587,   589,   591,   593,
     595,   597,   599,   602,   605,   607,   609,   611,   613,   615,
     617,   619,   621,   623,   625,   627,   629,   631,   633,   635,
     637,   639,   641,   643,   646,   648,   652,   654,   657,   661,
     663,   666,   668,   670,   673,   675,   678,   679,   684,   687,
     689,   692,   694,   696,   699,   701,   704,   707,   708,   710,
     713,   714,   724,   729,   734,   739,   743,   748,   753,   758,
     762,   772,   781,   784,   786,   790,   795,   797,   799,   800,
     802,   803,   804,   810,   814,   815,   817,   819,   826,   830,
     834,   838,   842,   846,   850,   853,   861,   868,   870,   873,
     875,   878,   880,   883,   885,   888,   889,   891,   893,   895,
     897,   899,   901,   903,   905,   907,   909,   911,   916,   919,
     922,   925,   928,   931,   934,   937,   940,   943,   946,   952,
     954,   959,   961,   964,   965,   967,   970,   973,   976,   979,
     982,   985,   988,   990,   993,   995,   997,  1000,  1003,  1006,
    1009,  1012,  1015,  1017,  1020,  1022,  1024,  1027,  1029,  1032,
    1036,  1038,  1040,  1042,  1045,  1047,  1051,  1052,  1054,  1057,
    1061,  1065,  1066,  1068,  1069,  1072,  1073,  1075,  1077,  1081,
    1084,  1086,  1088,  1092,  1093,  1095,  1097,  1100,  1103,  1108,
    1109,  1111,  1113,  1118,  1121,  1123,  1127,  1129,  1131,  1135,
    1139,  1140,  1142,  1144,  1147,  1152,  1156,  1157,  1159,  1161,
    1164,  1165,  1172,  1173,  1179,  1181,  1183,  1185,  1187,  1189,
    1191,  1193,  1194,  1196,  1202,  1210,  1212,  1215,  1219,  1220,
    1222,  1224,  1228,  1230,  1232,  1234,  1236,  1238,  1240,  1242,
    1244,  1246,  1248,  1250,  1252,  1254,  1256,  1258,  1260,  1262,
    1264,  1269,  1274,  1279,  1284,  1287,  1290,  1294,  1298,  1302,
    1306,  1314,  1322,  1330,  1338,  1343,  1348,  1350,  1354,  1355,
    1357,  1358,  1360,  1362,  1364,  1368,  1370,  1373,  1376,  1379,
    1382,  1385,  1388,  1391,  1394,  1397,  1402,  1404,  1407,  1409,
    1412,  1417,  1421,  1422,  1424,  1426,  1430,  1431,  1433,  1436,
    1441,  1443,  1448,  1450,  1454,  1458,  1460,  1464,  1468,  1472,
    1474,  1478,  1482,  1484,  1488,  1492,  1494,  1498,  1502,  1506,
    1510,  1512,  1516,  1520,  1522,  1526,  1528,  1532,  1534,  1538,
    1540,  1544,  1546,  1550,  1552,  1558,  1560,  1562,  1564,  1566,
    1568,  1570,  1572,  1574,  1576,  1578,  1580,  1582,  1586,  1588,
    1589,  1591,  1594,  1596,  1600,  1601,  1603,  1605,  1606,  1608,
    1610,  1614,  1618,  1622,  1624,  1628,  1632,  1634,  1638,  1640,
    1644,  1646,  1650,  1652,  1656,  1658,  1662,  1664,  1670,  1672,
    1674,  1678,  1679,  1681,  1683,  1685,  1686,  1688,  1691,  1692,
    1694,  1696,  1700,  1702,  1704,  1707,  1711,  1715,  1717,  1719,
    1721,  1723,  1725,  1727,  1729,  1731,  1733,  1739,  1744,  1748,
    1749,  1755,  1756,  1762,  1765,  1768,  1772,  1778,  1786,  1792,
    1794,  1799,  1805,  1813,  1822,  1832,  1843,  1847,  1849,  1852,
    1855,  1859,  1861
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     152,     0,    -1,   332,    -1,     4,   153,    -1,   155,    -1,
     158,    -1,   154,   158,    -1,    -1,   154,    -1,    -1,    89,
      -1,    67,   130,   332,   131,   114,   132,   133,    -1,   119,
      -1,   134,   114,    -1,   289,   253,   133,    -1,   289,   239,
      -1,   289,   159,    -1,   160,    -1,   164,    -1,   157,    -1,
      34,   114,   135,   155,   136,    -1,    34,   114,   158,    -1,
     162,    -1,     5,    -1,    -1,    32,   161,   163,   135,   155,
     136,    -1,    -1,    -1,   156,    88,   137,   165,   170,   138,
     166,   158,    -1,    -1,    -1,   156,    88,   137,   168,   170,
     138,   169,   266,    -1,   171,    -1,   170,   131,   171,    -1,
     172,    -1,   173,    -1,   173,   139,   206,    -1,    51,   348,
      -1,    51,   348,   139,   238,    -1,    49,   348,    -1,    49,
     348,   139,   238,    -1,    88,   137,   170,   138,    51,   348,
      -1,   174,   176,    -1,    46,   174,    -1,   301,    -1,   301,
     175,    -1,   301,    -1,   301,   175,    -1,   177,    -1,   191,
     176,    -1,   221,    -1,   130,   176,   132,    -1,    -1,   177,
     130,   178,   196,   132,   195,   190,    -1,   177,   140,   335,
     141,    -1,   180,    -1,   222,    -1,   130,   179,   132,    -1,
     180,   130,   196,   132,   195,   190,    -1,   180,   140,   335,
     141,    -1,   183,    -1,   191,   181,    -1,    -1,   227,    24,
     182,   181,    -1,   223,    -1,   227,    -1,   130,   181,   132,
      -1,   183,   252,   196,   132,   195,   190,    -1,   183,   140,
     335,   141,    -1,   186,    -1,   191,   184,    -1,    -1,   227,
      24,   185,   184,    -1,   223,    -1,   227,    -1,   130,   184,
     132,    -1,   186,   130,   196,   132,   195,   190,    -1,   186,
     140,   335,   141,    -1,   238,    -1,   187,   131,   238,    -1,
      -1,   187,    -1,    74,   130,   188,   132,    -1,    -1,   189,
      -1,   192,    -1,    24,    -1,    24,    46,    -1,    25,    -1,
      28,    -1,   100,    -1,   101,    -1,   102,    -1,    46,    -1,
      47,    -1,   193,    -1,   193,   194,    -1,    -1,   194,    -1,
     198,    -1,   197,   131,   108,    -1,   199,    -1,   197,   131,
     199,    -1,    -1,   197,    -1,   200,   204,    -1,   200,   204,
     139,   329,    -1,   200,   176,    -1,   200,   176,   139,   329,
      -1,    46,   200,    -1,    47,   200,    -1,   301,    -1,   301,
     201,    -1,   264,    -1,   229,    -1,   229,   202,    -1,   103,
     130,   261,   132,   200,    -1,   208,    -1,   301,   201,    -1,
     301,    -1,    46,   201,    -1,    47,   201,    -1,    46,    -1,
      47,    -1,    46,   202,    -1,    47,   202,    -1,    46,    -1,
      47,    -1,   205,    -1,   191,   204,    -1,    -1,   203,    -1,
     205,   130,   196,   132,   195,   190,    -1,   205,   140,   335,
     141,    -1,   130,   196,   132,   195,   190,    -1,   140,   335,
     141,    -1,   130,   203,   132,    -1,    65,    -1,    66,    -1,
     117,    -1,   118,    -1,   114,    -1,   115,    -1,   116,    -1,
      90,    -1,   206,    -1,   122,    -1,   130,   332,   132,    -1,
     230,    -1,    92,   130,   332,   132,    -1,     5,    -1,   209,
     128,    -1,    -1,   209,   125,   137,   212,   346,   138,    -1,
      -1,   210,   125,   137,   213,   346,   138,    -1,   209,   125,
      -1,   210,   125,    -1,   211,    -1,   209,   127,    -1,   210,
     127,    -1,   214,    -1,   209,   127,    -1,   210,   127,    -1,
     214,    -1,   216,    -1,   215,   107,   226,    -1,   142,   209,
     126,    -1,   142,   209,   127,    -1,   142,   209,   125,    -1,
     142,   209,   128,   126,    -1,   142,   209,   128,   127,    -1,
     142,   209,   128,   125,    -1,   218,    -1,   215,   107,   219,
      -1,   219,    -1,   209,   126,    -1,   225,    -1,   215,   107,
     221,    -1,   232,    -1,   215,   107,   222,    -1,   209,   126,
      -1,   142,   209,   126,    -1,   225,    -1,   215,   107,   223,
      -1,   109,    -1,   110,    -1,   109,   140,   141,    -1,   110,
     140,   141,    -1,   139,    -1,   137,    -1,   138,    -1,   143,
      -1,   144,    -1,   145,    -1,   146,    -1,   147,    -1,   142,
      -1,    10,    -1,    11,    -1,    22,    -1,    23,    -1,   130,
     132,    -1,   140,   141,    -1,     7,    -1,     8,    -1,    26,
      -1,    27,    -1,    25,    -1,    24,    -1,     9,    -1,   105,
      -1,   106,    -1,    14,    -1,    15,    -1,    16,    -1,    20,
      -1,    21,    -1,    12,    -1,    13,    -1,    17,    -1,    18,
      -1,    19,    -1,   111,   224,    -1,   215,    -1,   215,   107,
     226,    -1,   215,    -1,   215,   107,    -1,   215,   107,   226,
      -1,   226,    -1,   107,   226,    -1,   217,    -1,   221,    -1,
     107,   221,    -1,   223,    -1,   107,   223,    -1,    -1,   111,
     233,   234,   237,    -1,    46,   234,    -1,   301,    -1,   301,
     235,    -1,   228,    -1,    46,    -1,    46,   235,    -1,   301,
      -1,   301,   235,    -1,   191,   237,    -1,    -1,   236,    -1,
     262,   204,    -1,    -1,   257,   231,   252,   196,   132,   190,
     246,   240,   247,    -1,   257,   255,   181,   247,    -1,   257,
     264,   181,   247,    -1,   257,   228,   181,   247,    -1,   257,
     179,   247,    -1,   257,   255,   184,   247,    -1,   257,   264,
     184,   247,    -1,   257,   229,   184,   247,    -1,   257,   179,
     247,    -1,   257,   137,   229,   130,   196,   132,   190,   246,
     247,    -1,   257,   220,   130,   196,   132,   190,   246,   247,
      -1,   148,   243,    -1,   244,    -1,   243,   131,   244,    -1,
     245,   130,   304,   132,    -1,   230,    -1,   228,    -1,    -1,
     242,    -1,    -1,    -1,   135,   248,   251,   136,   249,    -1,
     135,   251,   136,    -1,    -1,   366,    -1,   130,    -1,   257,
     231,   252,   196,   132,   190,    -1,   257,   255,   277,    -1,
     257,   264,   277,    -1,   257,   228,   277,    -1,   257,   255,
     268,    -1,   257,   264,   269,    -1,   257,   229,   268,    -1,
     257,   179,    -1,   257,   137,   229,   130,   196,   132,   190,
      -1,   257,   220,   130,   196,   132,   190,    -1,   301,    -1,
     301,   256,    -1,   301,    -1,   301,   256,    -1,    46,    -1,
      46,   256,    -1,    47,    -1,    47,   256,    -1,    -1,   258,
      -1,    46,    -1,    47,    -1,    61,    -1,    62,    -1,    59,
      -1,    48,    -1,    91,    -1,    34,    -1,    63,    -1,    64,
      -1,   103,   130,   261,   132,    -1,   258,    46,    -1,   258,
      47,    -1,   258,    61,    -1,   258,    62,    -1,   258,    59,
      -1,   258,    48,    -1,   258,    91,    -1,   258,    34,    -1,
     258,    63,    -1,   258,    64,    -1,   258,   103,   130,   261,
     132,    -1,     5,    -1,     5,   130,   117,   132,    -1,   259,
      -1,   260,   259,    -1,    -1,   260,    -1,    46,   262,    -1,
      47,   262,    -1,    48,   262,    -1,    91,   262,    -1,    61,
     262,    -1,    34,   262,    -1,    59,   262,    -1,   301,    -1,
     301,   263,    -1,   264,    -1,   228,    -1,    46,   263,    -1,
      47,   263,    -1,    48,   263,    -1,    61,   263,    -1,    34,
     263,    -1,    59,   263,    -1,   301,    -1,   301,   263,    -1,
     291,    -1,   297,    -1,    49,   283,    -1,   284,    -1,   266,
     271,    -1,   295,   148,   271,    -1,   267,    -1,   241,    -1,
     167,    -1,   254,   133,    -1,   270,    -1,   268,   131,   270,
      -1,    -1,   268,    -1,   184,   272,    -1,   221,   148,   334,
      -1,   226,   148,   334,    -1,    -1,   265,    -1,    -1,   139,
     334,    -1,    -1,   274,    -1,   275,    -1,   274,   131,   275,
      -1,   184,   279,    -1,   184,    -1,   278,    -1,   276,   131,
     278,    -1,    -1,   276,    -1,   181,    -1,   181,   279,    -1,
     139,   281,    -1,    25,   130,   303,   132,    -1,    -1,   131,
      -1,   329,    -1,   135,   282,   280,   136,    -1,   135,   136,
      -1,   281,    -1,   282,   131,   281,    -1,   228,    -1,   230,
      -1,   294,   285,   230,    -1,   294,   285,   229,    -1,    -1,
     286,    -1,   287,    -1,   286,   287,    -1,   103,   130,   261,
     132,    -1,   140,   244,   141,    -1,    -1,   290,    -1,   288,
      -1,   290,   288,    -1,    -1,   284,   350,   135,   292,   271,
     136,    -1,    -1,   294,   135,   293,   271,   136,    -1,    51,
      -1,    52,    -1,    53,    -1,    81,    -1,    54,    -1,    55,
      -1,    56,    -1,    -1,   295,    -1,    50,   348,   135,   299,
     136,    -1,    50,   348,   148,   255,   135,   299,   136,    -1,
     300,    -1,   298,   131,    -1,   298,   131,   300,    -1,    -1,
     298,    -1,     5,    -1,     5,   139,   334,    -1,    87,    -1,
      78,    -1,    76,    -1,    77,    -1,    80,    -1,    79,    -1,
      82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,    -1,
      95,    -1,    96,    -1,    97,    -1,    98,    -1,    93,    -1,
      94,    -1,   207,    -1,   302,   140,   332,   141,    -1,   302,
     130,   305,   132,    -1,   228,   130,   304,   132,    -1,   301,
     130,   304,   132,    -1,   302,     7,    -1,   302,     8,    -1,
     302,   149,   283,    -1,   302,     9,   283,    -1,   302,   149,
     219,    -1,   302,     9,   219,    -1,    68,   137,   238,   138,
     130,   332,   132,    -1,    70,   137,   238,   138,   130,   332,
     132,    -1,    71,   137,   238,   138,   130,   332,   132,    -1,
      69,   137,   238,   138,   130,   332,   132,    -1,   113,   130,
     332,   132,    -1,   113,   130,   238,   132,    -1,   329,    -1,
     303,   131,   329,    -1,    -1,   303,    -1,    -1,   306,    -1,
     329,    -1,   238,    -1,   303,   131,   329,    -1,   302,    -1,
       7,   315,    -1,     8,   315,    -1,    24,   315,    -1,    25,
     315,    -1,   143,   315,    -1,   144,   315,    -1,   147,   315,
      -1,   142,   315,    -1,   112,   307,    -1,   112,   130,   238,
     132,    -1,   308,    -1,   107,   308,    -1,   314,    -1,   107,
     314,    -1,   109,   310,   311,   313,    -1,   130,   303,   132,
      -1,    -1,   309,    -1,   262,    -1,   130,   304,   132,    -1,
      -1,   312,    -1,   110,   315,    -1,   110,   140,   141,   315,
      -1,   307,    -1,   130,   238,   132,   315,    -1,   315,    -1,
     316,    30,   315,    -1,   316,    31,   315,    -1,   316,    -1,
     317,    24,   316,    -1,   317,   145,   316,    -1,   317,   146,
     316,    -1,   317,    -1,   318,   143,   317,    -1,   318,   144,
     317,    -1,   318,    -1,   319,   105,   318,    -1,   319,   106,
     318,    -1,   319,    -1,   320,   137,   319,    -1,   320,   138,
     319,    -1,   320,    22,   319,    -1,   320,    23,   319,    -1,
     320,    -1,   321,    10,   320,    -1,   321,    11,   320,    -1,
     321,    -1,   322,    25,   321,    -1,   322,    -1,   323,    27,
     322,    -1,   323,    -1,   324,    26,   323,    -1,   324,    -1,
     325,    28,   324,    -1,   325,    -1,   326,    29,   325,    -1,
     326,    -1,   326,   150,   332,   148,   329,    -1,   139,    -1,
      12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,
     327,    -1,   326,   328,   329,    -1,   331,    -1,    -1,   329,
      -1,    74,   330,    -1,   329,    -1,   332,   131,   329,    -1,
      -1,   332,    -1,   327,    -1,    -1,   327,    -1,   319,    -1,
     336,   137,   319,    -1,   336,    22,   319,    -1,   336,    23,
     319,    -1,   336,    -1,   337,    10,   336,    -1,   337,    11,
     336,    -1,   337,    -1,   338,    25,   337,    -1,   338,    -1,
     339,    27,   338,    -1,   339,    -1,   340,    26,   339,    -1,
     340,    -1,   341,    28,   340,    -1,   341,    -1,   342,    29,
     341,    -1,   342,    -1,   342,   150,   332,   148,   344,    -1,
     343,    -1,   347,    -1,   345,   131,   347,    -1,    -1,   345,
      -1,   344,    -1,   238,    -1,    -1,     5,    -1,   148,   351,
      -1,    -1,   349,    -1,   353,    -1,   351,   131,   353,    -1,
     229,    -1,   352,    -1,   295,   352,    -1,    62,   296,   352,
      -1,   295,    62,   352,    -1,   133,    -1,   364,    -1,   363,
      -1,   356,    -1,   250,    -1,   360,    -1,   362,    -1,   359,
      -1,   365,    -1,   104,   130,   114,   132,   133,    -1,    38,
     334,   148,   354,    -1,    39,   148,   354,    -1,    -1,   209,
     126,   148,   357,   354,    -1,    -1,   209,   127,   148,   358,
     354,    -1,    42,   133,    -1,    41,   133,    -1,    40,     5,
     133,    -1,    35,   130,   361,   132,   354,    -1,    35,   130,
     361,   132,   354,    36,   354,    -1,    37,   130,   361,   132,
     354,    -1,   332,    -1,   262,   176,   139,   329,    -1,    45,
     130,   361,   132,   354,    -1,    44,   354,    45,   130,   332,
     132,   133,    -1,    43,   130,   133,   333,   133,   333,   132,
     354,    -1,    43,   130,   332,   133,   333,   133,   333,   132,
     354,    -1,    43,   130,   262,   273,   133,   333,   133,   333,
     132,   354,    -1,   262,   273,   133,    -1,   355,    -1,   332,
     133,    -1,    72,   133,    -1,    72,   332,   133,    -1,   354,
      -1,   354,   366,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   682,   682,   684,   705,   722,   723,   726,   727,   730,
     731,   734,   737,   742,   743,   744,   745,   746,   747,   748,
     751,   752,   755,   759,   765,   764,   799,   808,   798,   838,
     847,   837,   879,   880,   883,   884,   885,   888,   889,   890,
     891,   892,   895,   898,   899,   900,   903,   904,   907,   908,
     911,   912,   914,   913,   959,   973,   976,   977,   978,   979,
     982,   983,   984,   984,   990,   991,   992,   993,  1009,  1012,
    1013,  1014,  1014,  1020,  1021,  1022,  1023,  1024,  1027,  1028,
    1031,  1032,  1035,  1038,  1039,  1042,  1043,  1044,  1045,  1046,
    1049,  1050,  1051,  1054,  1055,  1058,  1059,  1062,  1063,  1066,
    1067,  1070,  1071,  1074,  1075,  1078,  1079,  1080,  1081,  1084,
    1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,  1095,  1096,
    1097,  1098,  1099,  1100,  1103,  1104,  1105,  1106,  1109,  1110,
    1113,  1114,  1117,  1118,  1119,  1120,  1121,  1126,  1127,  1128,
    1129,  1130,  1131,  1132,  1133,  1136,  1137,  1138,  1139,  1156,
    1158,  1268,  1272,  1271,  1286,  1285,  1300,  1301,  1302,  1319,
    1320,  1321,  1332,  1333,  1334,  1337,  1341,  1360,  1361,  1362,
    1363,  1364,  1365,  1368,  1372,  1386,  1410,  1413,  1415,  1429,
    1430,  1444,  1445,  1447,  1450,  1470,  1471,  1472,  1473,  1474,
    1475,  1476,  1477,  1478,  1479,  1480,  1481,  1482,  1483,  1484,
    1485,  1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,  1494,
    1495,  1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,  1504,
    1505,  1506,  1507,  1510,  1515,  1519,  1531,  1535,  1539,  1569,
    1574,  1583,  1593,  1598,  1607,  1612,  1630,  1629,  1643,  1644,
    1645,  1646,  1649,  1650,  1651,  1652,  1661,  1664,  1665,  1668,
    1672,  1671,  1687,  1692,  1697,  1702,  1723,  1728,  1733,  1738,
    1743,  1750,  1770,  1773,  1774,  1777,  1779,  1780,  1783,  1784,
    1788,  1809,  1787,  1819,  1822,  1823,  1830,  1860,  1876,  1881,
    1886,  1905,  1910,  1915,  1920,  1924,  1929,  1950,  1951,  1954,
    1955,  1956,  1957,  1958,  1959,  1962,  1963,  1966,  1967,  1968,
    1969,  1970,  1971,  1972,  1973,  1974,  1975,  1976,  1977,  1978,
    1979,  1980,  1981,  1982,  1983,  1984,  1985,  1986,  1987,  1990,
    1991,  1993,  1994,  1997,  1998,  2030,  2031,  2032,  2033,  2034,
    2035,  2036,  2037,  2038,  2039,  2042,  2046,  2047,  2048,  2049,
    2050,  2051,  2052,  2053,  2057,  2058,  2059,  2063,  2071,  2072,
    2075,  2076,  2077,  2080,  2096,  2097,  2100,  2101,  2104,  2105,
    2106,  2109,  2110,  2113,  2114,  2119,  2120,  2123,  2124,  2139,
    2140,  2143,  2144,  2147,  2148,  2151,  2152,  2155,  2156,  2159,
    2160,  2163,  2164,  2165,  2168,  2169,  2172,  2173,  2182,  2183,
    2196,  2197,  2200,  2201,  2204,  2207,  2210,  2211,  2214,  2215,
    2219,  2218,  2257,  2256,  2299,  2300,  2301,  2302,  2305,  2306,
    2307,  2310,  2311,  2314,  2315,  2328,  2329,  2330,  2333,  2334,
    2337,  2338,  2341,  2342,  2343,  2344,  2345,  2346,  2347,  2348,
    2349,  2350,  2351,  2352,  2353,  2354,  2355,  2356,  2357,  2360,
    2362,  2365,  2373,  2374,  2376,  2377,  2379,  2380,  2382,  2383,
    2385,  2386,  2387,  2388,  2389,  2390,  2393,  2394,  2397,  2398,
    2401,  2402,  2405,  2406,  2407,  2410,  2411,  2412,  2413,  2414,
    2415,  2416,  2417,  2418,  2420,  2421,  2422,  2423,  2424,  2425,
    2428,  2432,  2435,  2436,  2439,  2455,  2458,  2459,  2462,  2463,
    2466,  2467,  2470,  2471,  2472,  2475,  2476,  2477,  2478,  2481,
    2482,  2483,  2486,  2487,  2488,  2491,  2492,  2493,  2494,  2495,
    2498,  2499,  2500,  2503,  2504,  2507,  2508,  2511,  2512,  2515,
    2516,  2519,  2520,  2523,  2524,  2527,  2528,  2529,  2530,  2531,
    2532,  2533,  2534,  2535,  2536,  2537,  2540,  2541,  2542,  2545,
    2546,  2549,  2552,  2553,  2556,  2557,  2560,  2563,  2564,  2569,
    2570,  2572,  2573,  2576,  2577,  2578,  2581,  2582,  2585,  2586,
    2589,  2590,  2593,  2594,  2597,  2598,  2601,  2602,  2605,  2608,
    2609,  2612,  2613,  2616,  2617,  2620,  2621,  2627,  2630,  2631,
    2634,  2635,  2638,  2642,  2643,  2644,  2645,  2650,  2651,  2652,
    2653,  2654,  2655,  2656,  2657,  2658,  2664,  2667,  2668,  2669,
    2669,  2670,  2670,  2673,  2674,  2675,  2679,  2680,  2681,  2684,
    2685,  2688,  2689,  2690,  2691,  2692,  2695,  2696,  2700,  2703,
    2704,  2707,  2708
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EXP_TOKEN", "DECLS_TOKEN", "IDENTIFIER",
  "identifier_lparen", "PLUSPLUS", "MINUSMINUS", "ARROW", "EQUAL",
  "NOT_EQUAL", "ASSIGN_PLUS", "ASSIGN_MINUS", "ASSIGN_OR", "ASSIGN_XOR",
  "ASSIGN_AND", "ASSIGN_MUL", "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_LSHIFT",
  "ASSIGN_RSHIFT", "LEQ", "GEQ", "STAR", "BITAND", "BITOR", "BITXOR",
  "LAND", "LOR", "DOT_STAR", "ARROW_STAR", "NAMESPACE_KW", "USING_KW",
  "EXTERN_KW", "IF_KW", "ELSE_KW", "SWITCH_KW", "CASE_KW", "DEFAULT_KW",
  "GOTO_KW", "BREAK_KW", "CONTINUE_KW", "FOR_KW", "DO_KW", "WHILE_KW",
  "CONST_KW", "VOLATILE_KW", "TYPEDEF_KW", "TYPENAME_KW", "ENUM_KW",
  "CLASS_KW", "STRUCT_KW", "UNION_KW", "PRIVATE_KW", "PROTECTED_KW",
  "PUBLIC_KW", "AUTO_KW", "REGISTER_KW", "STATIC_KW", "MUTABLE_KW",
  "INLINE_KW", "VIRTUAL_KW", "EXPLICIT_KW", "FRIEND_KW", "FALSE_KW",
  "TRUE_KW", "STATIC_ASSERT_KW", "STATIC_CAST_KW", "REINTERPRET_CAST_KW",
  "DYNAMIC_CAST_KW", "CONST_CAST_KW", "RETURN_KW", "TRY_KW", "THROW_KW",
  "CATCH_KW", "CHAR_KW", "WCHAR_T_KW", "BOOL_KW", "SHORT_KW", "INT_KW",
  "INTERFACE_KW", "LONG_KW", "SIGNED_KW", "UNSIGNED_KW", "FLOAT_KW",
  "DOUBLE_KW", "VOID_KW", "TEMPLATE_KW", "EXPORT_KW", "NULLPTR_KW",
  "CONSTEXPR_KW", "DECLTYPE_KW", "__FLOAT32_KW", "__FLOAT64_KW",
  "__INT8_KW", "__INT16_KW", "__INT32_KW", "__INT64_KW", "__INT128_KW",
  "__CDECL_KW", "__STDCALL_KW", "__FASTCALL_KW", "__DECLSPEC_KW",
  "__ASM_KW", "LSHIFT", "RSHIFT", "TWO_COLON", "THREE_DOTS", "NEW_KW",
  "DELETE_KW", "OPERATOR_KW", "SIZEOF_KW", "TYPEID_KW", "STRING_LITERAL",
  "LSTRING_LITERAL", "CHAR_LITERAL", "INTEGER_LITERAL", "DOUBLE_LITERAL",
  "IMPORT_KW", "TEMPLATE_NAME", "ATTRIBUTE_KW", "THIS_KW", "NTA", "YTA",
  "YTT", "NTY", "YTY", "CTORN", "SHIFT_THERE", "'('", "','", "')'", "';'",
  "'#'", "'{'", "'}'", "'<'", "'>'", "'='", "'['", "']'", "'~'", "'+'",
  "'-'", "'/'", "'%'", "'!'", "':'", "'.'", "'?'", "$accept", "start",
  "translation_unit", "declaration_seq", "declaration_seq_opt",
  "export_opt", "static_assert_declaration", "declaration",
  "linkage_specification", "namespace_definition", "identifier",
  "named_namespace_definition", "$@1", "template_declaration", "@2", "$@3",
  "member_template_declaration", "@4", "$@5", "template_parameter_list",
  "template_parameter", "type_parameter", "template_parameter_declaration",
  "template_parameter_declaration1", "template_parameter_declaration2",
  "declarator", "direct_declarator", "$@6",
  "conversion_function_declarator",
  "direct_conversion_function_declarator", "q_declarator", "$@7",
  "q_direct_declarator", "_q_member_declarator", "$@8",
  "q_member_direct_declarator", "type_id_list", "type_id_list_opt",
  "exception_specification", "exception_specification_opt", "ptr_operator",
  "cc_qualifier", "cv_qualifier", "cv_qualifier_seq",
  "cv_qualifier_seq_opt", "parameter_declaration_clause",
  "parameter_declaration_list", "parameter_declaration_list_opt",
  "parameter_declaration", "parameter_declaration1",
  "parameter_declaration3", "parameter_declaration4",
  "abstract_declarator", "abstract_declarator_opt",
  "direct_abstract_declarator", "literal", "primary_expression",
  "decltype_specifier", "id", "id_ctor", "template_id_with_args", "$@9",
  "$@10", "q_template_id", "typename_id", "q_typename_id",
  "q_type_nested_id", "dtor_id", "dtor_nested_id", "dtor_scoped_id",
  "non_type_nested_id", "conversion_nested_id", "p_non_type_nested_id",
  "operator", "operator_function_id", "type_nested_id",
  "declarator_nested_id", "type_scoped_id", "q_type_scoped_id",
  "non_type_scoped_id", "p_non_type_scoped_id", "conversion_function_id",
  "$@11", "conversion_type_id", "conversion_type_id2",
  "conversion_declarator", "conversion_declarator_opt", "type_id",
  "function_definition", "$@12", "member_function_definition",
  "ctor_initializer", "mem_initializer_list", "mem_initializer",
  "mem_initializer_id", "ctor_initializer_opt", "function_body", "$@13",
  "$@14", "compound_statement", "statement_seq_opt", "here",
  "_simple_declaration", "_member_declaration", "basic_type_seq",
  "basic_type_seq2", "q_simple_declaration2_opt", "q_simple_declaration2",
  "declspec_item", "declspeclist", "declspeclist_opt",
  "simple_declaration2", "simple_declaration3",
  "elaborated_type_specifier", "member_specification",
  "member_declaration", "member_declaration_decl",
  "q_member_declarator_list", "q_member_declarator_list_opt",
  "q_member_declarator", "member_specification_opt",
  "constant_initializer_opt", "statement_declarator_list_opt",
  "statement_declarator_list", "statement_declarator",
  "q_init_declarator_list", "q_init_declarator_list_opt",
  "q_init_declarator", "initializer", "COMMA_opt", "initializer_clause",
  "initializer_list", "scoped_id", "class_head",
  "class_specifier_ext_list_opt", "class_specifier_ext_list",
  "class_specifier_ext", "attribute_specification",
  "attribute_specification_list_opt", "attribute_specification_list",
  "class_specifier", "$@15", "$@16", "class_key", "access_specifier",
  "access_specifier_opt", "enum_specifier", "enumerator_list",
  "enumerator_list_opt", "enumerator_definition", "basic_type",
  "postfix_expression", "expression_list", "expression_list_opt",
  "expression_or_type_list_opt", "expression_or_type_list",
  "unary_expression", "new_expression", "new_placement",
  "new_placement_opt", "new_type_id", "new_initializer",
  "new_initializer_opt", "delete_expression", "cast_expression",
  "pm_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_operator", "assignment_expression",
  "assignment_expression_opt", "throw_expression", "expression",
  "expression_opt", "constant_expression", "constant_expression_opt",
  "template_argument_relational_expression",
  "template_argument_equality_expression",
  "template_argument_and_expression",
  "template_argument_exclusive_or_expression",
  "template_argument_inclusive_or_expression",
  "template_argument_logical_and_expression",
  "template_argument_logical_or_expression",
  "template_argument_conditional_expression",
  "template_argument_constant_expression", "template_argument_list",
  "template_argument_list_opt", "template_argument", "identifier_opt",
  "base_clause", "base_clause_opt", "base_specifier_list",
  "base_class_name", "base_specifier", "statement", "asm_definition",
  "labeled_statement", "$@17", "$@18", "jump_statement",
  "selection_statement", "condition", "iteration_statement",
  "declaration_statement", "expression_statement", "return_statement",
  "statement_seq", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
      40,    44,    41,    59,    35,   123,   125,    60,    62,    61,
      91,    93,   126,    43,    45,    47,    37,    33,    58,    46,
      63
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   151,   152,   152,   153,   154,   154,   155,   155,   156,
     156,   157,   158,   158,   158,   158,   158,   158,   158,   158,
     159,   159,   160,   161,   163,   162,   165,   166,   164,   168,
     169,   167,   170,   170,   171,   171,   171,   172,   172,   172,
     172,   172,   173,   174,   174,   174,   175,   175,   176,   176,
     177,   177,   178,   177,   177,   179,   180,   180,   180,   180,
     181,   181,   182,   181,   183,   183,   183,   183,   183,   184,
     184,   185,   184,   186,   186,   186,   186,   186,   187,   187,
     188,   188,   189,   190,   190,   191,   191,   191,   191,   191,
     192,   192,   192,   193,   193,   194,   194,   195,   195,   196,
     196,   197,   197,   198,   198,   199,   199,   199,   199,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   201,   201,
     201,   201,   201,   201,   202,   202,   202,   202,   203,   203,
     204,   204,   205,   205,   205,   205,   205,   206,   206,   206,
     206,   206,   206,   206,   206,   207,   207,   207,   207,   208,
     209,   210,   212,   211,   213,   211,   214,   214,   214,   215,
     215,   215,   216,   216,   216,   217,   217,   218,   218,   218,
     218,   218,   218,   219,   219,   220,   221,   221,   221,   222,
     222,   223,   223,   223,   223,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   225,   226,   226,   227,   227,   227,   228,
     228,   229,   230,   230,   231,   231,   233,   232,   234,   234,
     234,   234,   235,   235,   235,   235,   236,   237,   237,   238,
     240,   239,   239,   239,   239,   239,   241,   241,   241,   241,
     241,   241,   242,   243,   243,   244,   245,   245,   246,   246,
     248,   249,   247,   250,   251,   251,   252,   253,   253,   253,
     253,   254,   254,   254,   254,   254,   254,   255,   255,   256,
     256,   256,   256,   256,   256,   257,   257,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   259,
     259,   260,   260,   261,   261,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   263,   263,   263,   263,
     263,   263,   263,   263,   264,   264,   264,   264,   265,   265,
     266,   266,   266,   267,   268,   268,   269,   269,   270,   270,
     270,   271,   271,   272,   272,   273,   273,   274,   274,   275,
     275,   276,   276,   277,   277,   278,   278,   279,   279,   280,
     280,   281,   281,   281,   282,   282,   283,   283,   284,   284,
     285,   285,   286,   286,   287,   288,   289,   289,   290,   290,
     292,   291,   293,   291,   294,   294,   294,   294,   295,   295,
     295,   296,   296,   297,   297,   298,   298,   298,   299,   299,
     300,   300,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   303,   303,   304,   304,
     305,   305,   306,   306,   306,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     308,   309,   310,   310,   311,   312,   313,   313,   314,   314,
     315,   315,   316,   316,   316,   317,   317,   317,   317,   318,
     318,   318,   319,   319,   319,   320,   320,   320,   320,   320,
     321,   321,   321,   322,   322,   323,   323,   324,   324,   325,
     325,   326,   326,   327,   327,   328,   328,   328,   328,   328,
     328,   328,   328,   328,   328,   328,   329,   329,   329,   330,
     330,   331,   332,   332,   333,   333,   334,   335,   335,   336,
     336,   336,   336,   337,   337,   337,   338,   338,   339,   339,
     340,   340,   341,   341,   342,   342,   343,   343,   344,   345,
     345,   346,   346,   347,   347,   348,   348,   349,   350,   350,
     351,   351,   352,   353,   353,   353,   353,   354,   354,   354,
     354,   354,   354,   354,   354,   354,   355,   356,   356,   357,
     356,   358,   356,   359,   359,   359,   360,   360,   360,   361,
     361,   362,   362,   362,   362,   362,   363,   363,   364,   365,
     365,   366,   366
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     0,     1,     0,
       1,     7,     1,     2,     3,     2,     2,     1,     1,     1,
       5,     3,     1,     1,     0,     6,     0,     0,     8,     0,
       0,     8,     1,     3,     1,     1,     3,     2,     4,     2,
       4,     6,     2,     2,     1,     2,     1,     2,     1,     2,
       1,     3,     0,     7,     4,     1,     1,     3,     6,     4,
       1,     2,     0,     4,     1,     1,     3,     6,     4,     1,
       2,     0,     4,     1,     1,     3,     6,     4,     1,     3,
       0,     1,     4,     0,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     1,     1,
       3,     1,     3,     0,     1,     2,     4,     2,     4,     2,
       2,     1,     2,     1,     1,     2,     5,     1,     2,     1,
       2,     2,     1,     1,     2,     2,     1,     1,     1,     2,
       0,     1,     6,     4,     5,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     4,
       1,     2,     0,     6,     0,     6,     2,     2,     1,     2,
       2,     1,     2,     2,     1,     1,     3,     3,     3,     3,
       4,     4,     4,     1,     3,     1,     2,     1,     3,     1,
       3,     2,     3,     1,     3,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     3,     1,     2,     3,     1,
       2,     1,     1,     2,     1,     2,     0,     4,     2,     1,
       2,     1,     1,     2,     1,     2,     2,     0,     1,     2,
       0,     9,     4,     4,     4,     3,     4,     4,     4,     3,
       9,     8,     2,     1,     3,     4,     1,     1,     0,     1,
       0,     0,     5,     3,     0,     1,     1,     6,     3,     3,
       3,     3,     3,     3,     2,     7,     6,     1,     2,     1,
       2,     1,     2,     1,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     5,     1,
       4,     1,     2,     0,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     1,     2,     1,     1,     2,     1,     2,     3,
       1,     1,     1,     2,     1,     3,     0,     1,     2,     3,
       3,     0,     1,     0,     2,     0,     1,     1,     3,     2,
       1,     1,     3,     0,     1,     1,     2,     2,     4,     0,
       1,     1,     4,     2,     1,     3,     1,     1,     3,     3,
       0,     1,     1,     2,     4,     3,     0,     1,     1,     2,
       0,     6,     0,     5,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     5,     7,     1,     2,     3,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     4,     2,     2,     3,     3,     3,     3,
       7,     7,     7,     7,     4,     4,     1,     3,     0,     1,
       0,     1,     1,     1,     3,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     4,     1,     2,     1,     2,
       4,     3,     0,     1,     1,     3,     0,     1,     2,     4,
       1,     4,     1,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       1,     2,     1,     3,     0,     1,     1,     0,     1,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     5,     1,     1,
       3,     0,     1,     1,     1,     0,     1,     2,     0,     1,
       1,     3,     1,     1,     2,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     4,     3,     0,
       5,     0,     5,     2,     2,     3,     5,     7,     5,     1,
       4,     5,     7,     8,     9,    10,     3,     1,     2,     2,
       3,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   396,   150,     0,     0,     0,     0,   137,   138,     0,
       0,     0,     0,   539,   424,   425,   423,   427,   426,   428,
     429,   430,   431,   432,   422,   144,   437,   438,   433,   434,
     435,   436,     0,   482,     0,     0,     0,     0,   141,   142,
     143,   139,   140,   146,     0,     0,     0,     0,     0,     0,
     145,   439,     0,     0,   158,   161,   224,   232,   177,   229,
       0,   148,     0,   465,   490,   476,   478,   492,   495,   499,
     502,   505,   510,   513,   515,   517,   519,   521,   523,   536,
     542,   538,     2,     0,     0,    10,    12,     0,     0,     3,
     396,     4,     0,    19,     5,    17,    22,    18,   398,   295,
     397,   466,   467,   468,   469,     0,     0,     0,     0,   540,
     541,   233,   230,   477,   479,     0,   483,     0,     0,   488,
     204,   205,   210,   198,   199,   218,   219,   213,   214,   215,
     220,   221,   222,   216,   217,   200,   201,   209,   208,   206,
     207,   211,   212,   185,   186,     0,   190,   191,   189,     0,
     197,   192,   193,   194,   195,   196,   223,     0,   474,     0,
       0,     0,     0,     0,     0,   575,   404,   405,   406,     0,
       0,   407,     0,   335,     0,   130,   334,   347,   344,   390,
     345,   332,     0,   473,   470,   471,   472,     1,   156,   176,
     159,   151,   157,   160,     0,   458,   458,   444,   445,     0,
     460,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,     0,   525,     0,     0,     0,    23,    24,     0,
      13,     0,   267,   266,     0,     0,     6,     0,   304,   297,
     298,   302,   301,   299,   300,   305,   306,   303,     0,    16,
      15,     0,     0,   296,   399,     0,     0,   224,   335,     0,
     332,     0,     0,     0,     0,   456,   484,   486,     0,     0,
       0,   202,   203,     0,     0,     0,   330,   325,   326,   327,
     386,   387,   346,   576,     0,   331,   329,   328,     0,    86,
      88,    89,    90,    91,    92,   103,   547,   130,    85,   131,
     249,   128,     0,   579,     0,     0,   402,     0,   391,   392,
       0,     0,     0,     0,     0,     0,   333,   342,   147,   152,
     154,   178,   225,   459,     0,     0,     0,   224,   173,   449,
     447,   463,     0,     0,   461,   456,     0,   448,   446,   493,
     494,   496,   497,   498,   500,   501,   503,   504,   508,   509,
     506,   507,   511,   512,   514,   516,   518,   520,   522,     0,
     537,   543,     0,     0,   395,   458,    26,   396,   323,    14,
       0,   236,     0,     0,     0,    55,     0,   224,    56,   234,
     183,   373,     0,   179,   373,   373,   287,   315,   308,   309,
     313,   312,   310,   311,   316,   317,   314,     0,     0,     0,
       0,     0,     0,     0,   481,   458,   487,   480,   489,   187,
     188,   475,   455,   454,   418,     0,   491,    87,     0,     0,
       0,     0,     0,   104,    99,   101,   130,     0,   117,     0,
       0,   164,     0,   165,   231,   114,   113,   111,   523,   548,
       0,   129,   103,   547,   408,   409,   410,   411,   582,     0,
     577,   583,   580,   400,   323,   295,     0,     0,     0,   389,
     388,   393,   340,   336,   337,   338,   341,   339,   343,   571,
     571,   442,   443,     0,     0,     0,   441,   440,     0,   396,
       0,     0,     0,   396,    21,   319,   321,   324,     0,   224,
     235,     0,   236,     0,     0,     0,   270,   255,   103,   547,
     181,     0,     0,   375,    60,     0,   226,    64,    65,   374,
     280,   371,   276,   103,   375,   278,   375,   279,   291,   293,
     288,   289,   323,     0,     0,     0,     0,   457,     0,   420,
     419,     0,   415,     0,   109,   110,     0,   323,    97,     0,
     103,   107,    48,   130,   105,     0,    50,   136,   162,   163,
       0,   126,   127,   115,   122,   123,   112,   119,   135,     0,
       0,   412,     0,     0,   584,     0,   295,     0,   304,     0,
     352,   351,     0,     0,   362,   295,   350,     0,     0,     0,
     574,   549,   553,   556,   558,   560,   562,   564,   566,   568,
     573,   572,     0,   569,     0,   169,   167,   168,     0,   174,
     457,   524,     0,   141,   265,     0,   575,   575,     0,     0,
      32,    34,    35,     0,    44,     0,     0,   322,   307,     0,
       0,   241,   247,   239,    57,     0,   182,   274,     0,     0,
     180,   184,     0,     0,     0,   254,   376,   547,   103,    61,
     227,    62,     0,     0,   252,   253,   292,   294,   290,     0,
       0,     0,     0,     0,   485,     0,   416,   413,   418,     0,
       0,    93,    94,    95,    98,    83,   100,   102,     0,     0,
      52,   547,    49,     0,     0,   166,   124,   125,   120,   121,
     118,    97,   133,   585,   586,   581,     0,   394,     0,   353,
       0,   284,     0,   175,     0,     0,     0,   356,   348,   403,
     295,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,   155,   172,   170,   171,    25,     0,
      43,    39,    37,     0,     0,    27,     0,     0,    42,     0,
      45,    46,    20,     0,   238,   247,   248,   237,   242,   240,
     244,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   587,   274,     0,   591,     0,   365,     0,
     621,   617,   590,   594,   592,   593,   589,   588,   595,   275,
      97,    59,    66,     0,     0,   377,   381,     0,     0,   228,
       0,   375,   372,    83,   318,   450,   453,   451,   452,   546,
     421,   417,     0,   149,     0,    96,     0,    84,   134,    51,
     108,   103,     0,   106,    83,   401,    29,     0,   259,     0,
     103,     0,   363,    69,     0,     0,   226,     0,    73,   183,
       0,    74,   283,   354,   363,   281,   363,   357,   282,   349,
     551,   552,   550,   554,   555,   557,   559,   561,   563,   565,
       0,   570,    11,     0,     0,     0,    33,   396,    36,    47,
     320,   246,   243,   245,     0,     0,     0,     0,     0,   604,
     603,     0,     0,     0,   619,     0,     0,     0,   176,   159,
     271,   370,     0,   366,   367,   618,   622,    83,     0,   383,
     384,   379,    68,    97,    63,   268,   414,   116,    80,     0,
      54,   132,     0,   103,   224,     0,     0,     0,   258,   358,
     103,   547,    70,   181,   227,     0,     0,    71,     0,   256,
     257,     0,    40,    38,     0,    28,     0,   609,     0,     0,
       0,   598,   605,   544,   365,     0,     0,     0,   620,     0,
     273,   599,   601,   272,   369,   616,     0,    58,   378,   380,
       0,    83,     0,   269,   250,    81,     0,    78,    97,     0,
       0,     0,    83,    75,   364,     0,     0,   224,   228,   359,
     360,     0,   363,   355,   567,   575,     0,     0,     0,   597,
     545,     0,     0,   544,     0,     0,     0,     0,     0,   368,
     385,   382,    67,   262,   263,     0,     0,    82,    83,    30,
      83,   268,    97,    77,     0,    72,    41,     0,   606,   608,
     544,   544,     0,     0,   611,   596,   600,   602,     0,   251,
      79,    53,   295,   268,     0,    83,   610,     0,     0,     0,
     544,     0,   264,    31,     0,   261,    76,   607,     0,   544,
       0,   612,   260,   613,     0,     0,     0,   614,   615
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    49,    89,    90,    91,    92,    93,    94,   259,    95,
     238,    96,   372,    97,   492,   857,   580,   902,  1022,   619,
     620,   621,   622,   623,   740,   678,   552,   811,   384,   385,
     513,   790,   514,   881,   971,   823,   955,   956,   807,   808,
     824,   308,   673,   674,   675,   432,   433,   434,   435,   436,
     566,   563,   309,   451,   311,    50,    51,   438,    52,    53,
      54,   479,   480,    55,    56,   443,   444,   338,   609,   704,
      57,   640,   828,   156,    58,    59,   831,    60,   445,    61,
     392,   393,   501,   632,   749,   746,   747,   590,   260,   995,
     581,   953,   993,   244,   245,   954,   507,   637,   943,   766,
     767,   523,   261,   582,   394,   530,   583,   263,   496,   497,
     498,   175,   326,   176,   584,   585,   586,   832,   838,   833,
     587,   909,   882,   883,   884,   519,   520,   521,   646,   950,
     785,   891,   292,   177,   317,   318,   319,    98,    99,   100,
     178,   576,   465,   179,   588,   572,   180,   540,   541,   542,
      62,    63,   333,   334,   343,   344,    64,    65,   116,   117,
     277,   416,   417,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,   235,    80,   110,
      81,   769,   981,   800,   450,   592,   593,   594,   595,   596,
     597,   598,   599,   600,   601,   602,   603,   294,   313,   314,
     460,   461,   462,   770,   771,   772,   987,   988,   773,   774,
     928,   775,   776,   777,   778,   779
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -941
static const yytype_int16 yypact[] =
{
    2031,   262,  -941,  3127,  3127,  3127,  3127,  -941,  -941,  -101,
     -77,   -43,   -29,  2937,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,   211,    -5,  1902,  1924,  3222,    15,  -941,  -941,
    -941,  -941,  -941,  -941,  2441,  3127,  3127,  3127,  3127,   168,
    -941,  -941,   252,   282,  -941,  -941,   118,  -941,  -941,  -941,
     113,  -941,   136,    31,  -941,  -941,  -941,  -941,   354,    10,
     256,   422,   209,   532,   263,   266,   272,   287,  1075,  -941,
    -941,  -941,   179,   325,   207,  -941,  -941,   230,   157,  -941,
     668,  -941,   269,  -941,  -941,  -941,  -941,  -941,  -941,  1006,
     231,  -941,  -941,  -941,  -941,  3536,  3536,  3536,  3536,  -941,
    -941,  -941,  -941,  -941,  -941,  2937,  -941,  3536,   248,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,   264,   271,   286,  -941,  -941,  -941,   302,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  2441,  -941,  2441,
    3536,  3536,  3536,  3536,   157,   442,  -941,  -941,  -941,  3536,
    3536,  -941,  3536,   113,   320,   369,  -941,   112,  -941,   -30,
    -941,  3643,   416,  -941,  -941,  -941,  -941,  -941,   324,  -941,
    -941,  -941,   330,  -941,    54,  2937,  2937,  -941,  -941,   102,
    2441,  2937,   102,  3127,  3127,  3127,  3127,  3127,  3127,  3127,
    3127,  3127,  3127,  3127,  3127,  3127,  3127,  3127,  3127,  3127,
    3127,  3127,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  3127,  -941,  2937,  2937,  2937,  -941,  -941,  2937,
    -941,    54,  -941,  -941,   336,   350,  -941,   356,   388,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   381,  -941,
    -941,   387,  1468,  1242,  -941,   519,   233,   424,  -941,   421,
    3698,   434,   455,   460,   444,  -941,  -941,   466,  3127,   464,
     475,  -941,  -941,   490,   492,   469,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   141,  -941,  -941,  -941,  3127,   585,
    -941,  -941,  -941,  -941,  -941,  3406,  3127,   369,  -941,  -941,
    -941,   167,   365,  -941,   502,   511,  -941,   232,   544,  -941,
    3698,  3698,  3698,  3698,  3698,  3698,  -941,  3698,  -941,  -941,
    -941,  -941,  -941,   520,   521,   523,   519,   562,  -941,  -941,
    -941,  -941,   543,   531,  -941,   547,   178,  -941,  -941,  -941,
    -941,   354,   354,   354,    10,    10,   256,   256,   422,   422,
     422,   422,   209,   209,   532,   263,   266,   272,   287,   -55,
    -941,  -941,   550,   566,  -941,  2937,  -941,   478,   685,  -941,
      91,  1924,    36,   519,   570,   201,   289,   600,  -941,  -941,
    -941,   618,   579,  -941,   618,   618,  3721,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,   584,   519,   586,
     604,   613,   615,  2937,  -941,  2937,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   725,  3832,  -941,  -941,  3589,  3589,
     617,   625,   626,   637,  -941,  -941,   344,   645,  -941,   298,
     314,   673,   677,  -941,  -941,   568,  -941,  3763,    -9,  -941,
     644,  -941,  3589,  3127,  -941,  -941,  -941,   402,  -941,    38,
     655,  -941,  -941,  -941,   685,  1276,    54,   436,   682,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  2557,
    2557,  -941,  -941,   458,   119,  2937,  -941,  -941,  2937,   831,
    3032,   658,  2114,   831,  -941,   661,  -941,   685,   662,   686,
    -941,  1171,  -941,   663,   689,   671,  -941,  -941,  3589,  3127,
    -941,   144,   618,    42,   208,   618,   691,  -941,   777,   672,
    -941,  -941,  -941,  3589,    42,  -941,    42,  -941,  3721,  3721,
    -941,  3721,   685,  2937,  2937,  2937,  2937,  -941,   675,   666,
     678,   674,  -941,   679,  -941,  -941,  2937,   685,   593,  3471,
    3321,   676,   215,   344,   680,   706,  -941,  -941,   709,   710,
     519,   568,   568,  -941,  3763,  3763,  -941,  3763,  -941,   688,
     683,  -941,   519,   519,  -941,   365,  1276,   694,  -941,   730,
    -941,  -941,   697,  1783,  -941,  1276,  -941,   696,   687,    54,
    -941,   422,    35,   634,   796,   809,   811,   812,    -2,  -941,
    -941,   711,   705,  -941,   708,  -941,  -941,  -941,   412,  -941,
     712,  -941,   713,   716,  -941,  3786,   442,   442,   714,   -25,
    -941,  -941,   715,  1031,  3832,   717,   733,  -941,  -941,    91,
    1171,  -941,   404,  3809,  -941,   213,  -941,  2209,   720,   718,
    -941,  -941,   723,   727,  2747,  -941,  -941,  3127,  3589,  -941,
      91,  -941,   618,   726,  -941,  -941,  -941,  -941,  -941,   734,
     530,   534,   556,   580,  -941,  3127,   725,  -941,   725,   592,
     735,  -941,  -941,   593,  -941,   788,  -941,  -941,   737,  2937,
    -941,  3127,  -941,  2937,    54,  -941,  -941,  -941,  -941,  -941,
    -941,   593,  -941,  -941,  -941,  -941,   742,  -941,   743,  -941,
     519,   570,   763,  -941,   751,  1023,  1023,  1023,  -941,  -941,
    1276,  3127,  3127,  3127,  3127,  3127,  3127,  3127,  3127,  3127,
    3127,  2937,  2557,  -941,  -941,  -941,  -941,  -941,  -941,   749,
    -941,   744,   745,  2114,  2114,  -941,   512,  1031,  -941,  1031,
    -941,  3832,  -941,   753,  -941,   404,  -941,  -941,  3809,  -941,
    3809,   757,   759,  3127,   747,   886,   760,   764,   762,  2209,
     766,  2842,   775,  -941,  2209,   482,  -941,   771,  1023,   352,
    2209,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     593,  -941,  -941,  2937,  2652,  -941,  -941,   768,   779,  -941,
     618,     1,  -941,   788,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,   778,  -941,  3589,  -941,   783,  -941,  -941,  -941,
    -941,  3589,   776,  -941,   788,  -941,  -941,   786,  -941,   158,
    3589,  1023,   106,   222,  1023,   576,   -53,   770,  -941,   773,
     774,   899,   793,  -941,   106,   793,   106,   793,  -941,  -941,
     422,   422,   422,    35,    35,   634,   796,   809,   811,   812,
     -32,  -941,  -941,  3536,  3536,   134,  -941,   606,  -941,  -941,
    -941,  -941,  -941,  -941,  2441,  2441,   792,  2209,   794,  -941,
    -941,  2325,   880,  2441,  -941,   357,   820,   806,   799,   801,
    -941,     1,   822,   825,  -941,  -941,  -941,   788,   595,  -941,
    -941,   826,  -941,   593,  -941,   -62,  -941,  -941,  3536,   821,
    -941,  -941,  2114,  3589,   851,   828,   832,  3127,  -941,  -941,
    3589,  3127,  -941,   815,    91,  3127,  3127,  -941,  1023,  -941,
    -941,  3127,  -941,  -941,   915,  -941,  1031,   179,   836,   837,
    2209,  -941,  -941,  2937,  1023,   367,   842,   841,  -941,   843,
    -941,  -941,  -941,  -941,  -941,  -941,  1023,  -941,  -941,  2747,
     840,   788,   157,  -941,  -941,   846,   847,  -941,   593,   146,
     850,   158,   788,  -941,  -941,   854,   848,   881,   839,  -941,
    -941,  1023,   852,  -941,  -941,   442,   855,  2209,  2209,  -941,
     179,   857,   860,  2937,  2937,  2209,   864,  2209,  2209,  -941,
    -941,  -941,  -941,   867,  -941,   570,  3536,  -941,   788,  -941,
     788,   -61,   593,  -941,    91,  -941,  -941,  2937,   963,  -941,
    2937,  2937,   869,   605,  -941,  -941,  -941,  -941,   157,  -941,
    -941,  -941,  1389,   105,   570,   788,  -941,  2209,   868,   872,
    2937,   875,  -941,  -941,   570,  -941,  -941,  -941,  2209,  2937,
     885,  -941,  -941,  -941,   890,  2209,  2209,  -941,  -941
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -941,  -941,  -941,  -941,  -415,  -453,  -941,   -87,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -705,
     284,  -941,  -941,   401,   283,  -431,  -941,  -941,  -369,  -941,
    -326,  -941,  -941,  -595,  -941,  -941,  -941,  -941,  -941,  -758,
    -120,  -941,  -941,   360,  -666,  -438,  -941,  -941,   474,  -406,
    -116,   188,  -294,  -166,  -941,   293,  -941,  -941,   769,   598,
    -941,  -941,  -941,   884,  1269,  -941,  -941,  -941,  -192,  -941,
     -24,  -256,  -216,  -941,   719,    60,  -293,   -26,  -208,    -4,
    -941,  -941,  -941,   395,  -180,  -941,   290,    46,  -941,  -941,
    -941,  -941,  -941,  -921,  -941,  -940,  -494,  -941,  -941,  -941,
     268,   524,  -941,  -941,  -377,    61,   938,  -941,   546,  -941,
    -274,   142,   194,  -217,  -941,    19,  -941,    45,  -941,   126,
    -543,  -941,   111,  -941,   100,  -941,   359,   397,   177,  -941,
    -767,  -941,   154,  -941,  -941,  -941,   748,   960,  -941,  -941,
    -941,  -941,  -941,  -941,  -288,  -941,  -941,  -941,   393,   396,
     -42,  -941,  -111,  -167,  -941,  -941,  1027,  1039,  -941,  -941,
    -941,  -941,  -941,  1041,   630,   374,   555,   563,  -162,   559,
     858,   856,   859,   861,   845,  -259,  -257,  -941,   -12,  -941,
    -941,     0,  -548,  -716,  -432,    68,   362,   363,   366,   364,
     378,  -941,  -941,   164,  -941,   620,   379,  -601,  -941,  -941,
    -941,  -238,   527,  -246,  -941,  -941,  -941,  -941,  -941,  -941,
    -723,  -941,  -941,  -941,  -941,   333
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -579
static const yytype_int16 yytable[] =
{
      82,   109,   181,   246,   274,   551,   388,   339,   111,   310,
     347,   437,   579,   503,   569,   731,   732,   890,   173,   645,
     232,   570,   544,   545,   459,   814,   643,   720,   855,   335,
     654,   994,   655,   696,   205,   895,   105,   866,   197,   198,
     199,     2,   708,     2,   182,   395,   389,   448,   543,   449,
     358,   359,   360,   361,   914,   307,   901,   711,   712,     2,
     106,  1024,   242,   270,   270,   270,   270,   643,   524,   526,
     638,  -277,  -286,   315,   612,   270,   236,   639,   625,   268,
     268,   268,   268,  1034,   243,   653,   952,   952,   446,   342,
     174,   268,   112,   488,   107,  -224,     2,  1032,   518,   236,
     573,   518,   518,   275,   458,   316,   734,     2,   108,   469,
     822,   834,   836,   735,   887,   181,   921,   181,   270,   270,
     270,   270,   682,   579,     2,   115,   388,   270,   270,   947,
     270,   173,   579,   173,   268,   268,   268,   268,   290,   327,
     644,   234,   929,   268,   268,   159,   268,   502,   721,     2,
     937,   269,   271,   272,   273,   206,   207,   182,   181,   285,
     291,   200,     2,     2,   500,    35,   382,   839,   187,   571,
     331,   201,   713,   290,   173,   517,   290,   506,   517,   517,
     202,   644,   990,   275,   275,   307,   642,   307,   345,   649,
     577,   964,   738,   992,   448,   291,   449,   959,   291,   969,
     970,   346,    35,   283,  1001,   284,   706,   818,   491,   241,
     788,   446,   446,    35,   701,   787,     2,   111,     2,   518,
     396,   574,   518,   370,   371,   194,   906,   951,   327,   912,
      35,   212,   213,   383,   369,   446,   391,     2,  -285,   373,
    1021,   506,  1023,   195,   336,   907,   341,  -578,   538,   812,
     448,   458,   449,   952,   332,   381,   437,   579,   659,   276,
     312,   336,    -7,   447,   241,   734,   196,  1036,    35,   502,
     554,   515,   924,   670,   515,   515,   424,   734,   327,   327,
     327,   327,   327,   327,   999,   327,   383,   459,   218,   425,
     494,   446,   998,   219,    83,   641,   517,   452,   220,   517,
     336,   112,   286,   287,   288,   289,   446,   453,   682,   236,
     236,   295,   296,   470,   297,   221,   553,   591,   591,   487,
      33,    34,    35,   972,   502,   112,   791,   388,   908,    84,
     237,   508,   446,   446,   693,   694,  1025,   239,   522,   466,
     919,   509,   920,    35,   240,   680,   214,   215,   647,     2,
      -9,    85,   910,   340,   531,   681,   348,   247,   188,   518,
     190,   191,   911,   275,   458,   458,   707,   458,   299,   300,
       2,    88,   301,   899,  1006,   705,  1005,   188,   189,   190,
     191,    86,   905,   396,   203,   204,   447,   447,   448,   278,
     449,   703,   515,   299,   300,   515,    87,   301,   897,   208,
     209,   537,    88,   275,   279,   567,   448,   192,   799,   193,
     447,   280,   556,   641,   188,   510,   190,   191,   281,   454,
     455,   456,   448,   188,   449,   558,   191,   457,   299,   300,
     553,   446,   301,   553,   641,  1012,   517,   181,   181,   192,
     112,   559,   111,   282,   302,   303,   304,   293,   688,   689,
     624,   690,   298,   173,   173,    35,   454,   455,   456,   633,
     331,   329,  1028,  1029,   894,   960,   447,   330,   332,   302,
     303,   304,   965,   610,   550,   631,   611,   374,   371,   966,
     375,   447,  1040,   236,   306,   885,   531,   531,   236,   531,
     938,  1044,   817,   376,   448,   976,   799,   518,   236,   305,
     983,  1019,   377,   739,   302,   303,   304,   447,   447,   306,
      83,   378,   745,   872,   472,   473,   474,   475,   476,   477,
     379,   478,   567,   567,     2,   567,   556,   210,   211,   556,
    1035,   408,   515,   660,   661,   662,   663,   725,   726,   727,
    1042,   396,   216,   217,   332,    84,   669,   236,   328,   840,
     841,   842,   591,   591,   591,   591,   591,   591,   591,   409,
     591,   188,   189,   558,   191,   331,    -9,    85,   862,   579,
     863,   332,   410,   624,   517,   413,   414,     7,     8,   351,
     352,   353,   741,   605,   606,   607,   608,   446,   633,   656,
     657,   750,   658,   411,   446,   181,   415,    86,   412,   556,
     236,   423,    25,   446,   631,   419,   447,   188,   878,   879,
     191,   173,    87,   493,   561,   562,   420,   739,    88,   739,
     685,   931,   421,     2,   422,   745,    38,    39,    40,    41,
      42,   427,   786,   101,   102,   103,   104,   463,    83,   671,
     672,   464,   299,   300,   714,   715,   301,   315,   448,   685,
     799,   413,   448,   481,   449,   482,   448,   448,   799,   799,
     331,   236,   795,   486,   119,   236,   796,   810,    -8,   484,
     515,   813,   888,    84,   485,   183,   184,   185,   186,  -462,
     181,   827,   827,   827,   979,   489,   446,   236,   797,   332,
     495,   624,   624,   446,    -9,    85,   173,   490,   641,   741,
      83,   188,   913,   190,   191,   506,   750,   511,   750,   522,
     789,   236,   798,   556,   532,   556,   533,   181,   302,   303,
     304,   850,   181,   236,   803,    86,   413,   948,   181,    35,
     539,  1008,  1009,   173,   534,    84,   236,  1031,   173,  1014,
      87,  1016,  1017,   535,   173,   536,    88,   546,   512,   686,
     687,   835,   837,   525,   527,   547,    -9,    85,   548,   591,
     383,   875,   447,   354,   355,   830,   830,   830,   549,   447,
     925,   275,   786,   356,   357,   362,   363,   557,   447,   768,
    -161,  1037,   843,   844,   560,   568,   575,    86,   641,   589,
     614,   626,  1043,   629,   628,   634,   635,   636,   650,  1047,
    1048,   651,    87,   652,    -8,   665,   739,   664,    88,   666,
     667,   270,   270,   684,   668,   679,  -159,  -160,   698,   683,
     691,   716,   181,   181,   692,   181,   697,   268,   268,   181,
     699,   181,   709,   349,   350,   710,   717,   718,   173,   173,
     719,   173,   722,   723,  -464,   173,   724,   173,   729,   728,
     743,   733,   780,   742,   736,   782,   270,   783,   793,   781,
     624,   447,   806,    83,   927,   927,   794,   804,   447,   809,
     819,   935,   268,   927,   266,   266,   266,   266,   815,   685,
     816,   820,   852,   853,   854,   860,   266,   864,   181,   865,
     331,   868,   871,   869,   827,   867,   873,   870,    84,   922,
     923,   768,   556,   440,   173,   876,   768,   880,   418,   892,
     440,   893,   768,   898,   896,   440,   903,   900,   915,    -9,
      85,  -177,   916,   917,   918,   936,   242,   932,   426,   266,
     266,   266,   266,   980,   939,   181,   181,   786,   266,   266,
     930,   266,   940,   181,   957,   181,   181,   941,   243,   942,
      86,   173,   173,   958,   270,   945,   946,   949,   961,   173,
     962,   173,   173,  -176,   963,    87,   975,    -7,   977,   978,
     268,    88,   984,   985,   968,   986,   991,   996,   830,   997,
     331,   390,  1000,   980,  1013,   181,  1002,  -225,  1004,  1003,
    1010,   907,   242,  1011,  1007,  1026,   181,  1015,  1018,  1027,
    1038,   173,  1030,   181,   181,  1039,   926,   926,  1041,   768,
     980,   980,   173,   934,   243,   926,   730,  1045,   856,   173,
     173,   332,  1046,   677,   859,   744,   440,   440,     2,   858,
     980,   386,   877,   805,   266,   861,     2,   262,   648,   980,
     248,  1033,  1020,   627,   973,   982,   989,   299,   300,   792,
     440,   301,   249,   250,   251,   299,   300,   440,   944,   301,
     264,   802,   801,   158,   332,   252,   471,   253,   254,   255,
     256,   113,   768,   114,   439,   365,   364,   368,   845,   366,
     846,   439,   367,   848,   847,   974,   467,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   257,   849,   390,
     604,   851,   695,   886,   232,   483,   440,     0,     0,   258,
     390,     0,     0,   390,   390,     0,     0,     0,     0,   768,
     768,   440,     0,   302,   303,   304,     0,   768,     0,   768,
     768,   302,   303,   304,    35,     0,     0,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,   440,   440,   386,
       0,   266,   505,   821,     0,     0,     0,     0,     0,     0,
     386,   737,     0,   386,   386,   383,     0,     0,     0,   768,
     440,   440,     0,   440,     0,     0,     2,   266,     0,     0,
     768,   440,     0,     0,     0,     0,     0,   768,   768,   441,
       0,     0,     0,     0,     0,     0,   441,   439,   439,     0,
       0,   441,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   233,     0,     0,   630,     0,     0,
       0,   439,     0,     0,     0,   234,     0,     0,   439,     0,
     390,   390,     0,     0,   390,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   440,    14,    15,    16,
      17,    18,     0,    19,    20,    21,    22,    23,    24,     0,
       0,     0,     0,     0,    26,    27,    28,    29,    30,    31,
     266,     0,     0,     0,     0,     0,   397,   439,   265,     0,
     386,   386,     0,     0,   386,     0,     0,     0,   398,   399,
     400,     0,   439,     0,     0,     0,     0,     0,   440,     0,
       0,   401,     0,   402,   403,   404,   405,     0,     0,     0,
     578,     0,   441,   441,     0,     0,     0,     0,   439,   467,
       0,     0,   249,   250,   251,     0,     0,     0,     0,   266,
     454,   455,   456,   406,     0,   252,   441,   253,   254,   255,
     256,   439,   439,   441,   439,   407,     0,     0,   390,     0,
       0,     0,   439,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    -9,    85,     0,   257,     0,   390,
       0,   390,     0,     0,   267,   267,   267,   267,     0,   258,
       0,     0,     0,     0,     0,     0,   267,     0,     0,     0,
       0,     0,   441,     0,     0,     0,     0,     0,   386,   266,
       0,     0,   440,     0,   266,     0,   765,   441,     0,   440,
       0,     0,  -361,     0,     0,     0,     0,   439,   440,   386,
       0,   386,     0,   578,   829,   829,   829,     0,     0,   267,
     267,   267,   267,   441,   441,   249,   250,   251,   267,   267,
       0,   267,     0,     0,     0,     0,     0,     0,   252,     0,
     253,   254,   255,   256,     0,     0,   441,   441,     0,   441,
       0,     0,     0,     0,     0,     0,     0,   441,   337,   439,
       0,   337,     0,     2,   825,   825,   825,    -9,    85,     0,
     257,     0,     0,     0,     0,     0,     0,   390,     0,     0,
       0,     0,   258,     0,     0,     0,     0,     0,     0,     0,
       0,   440,     0,     0,     0,     0,     0,     0,   440,   390,
       0,     0,     0,     0,     0,     0,     0,   164,   165,   166,
     167,   168,     0,     0,     0,     0,     0,     0,   765,     0,
       0,   387,   441,   765,   267,     0,     0,   386,     0,   765,
     390,     0,     0,   390,    14,    15,    16,    17,    18,   171,
      19,    20,    21,    22,    23,    24,     0,     0,     0,   386,
       0,    26,    27,    28,    29,    30,    31,     0,     0,     0,
       0,     0,     0,   439,   442,   380,     0,     0,     0,   381,
     439,   442,     0,     0,   441,     0,   468,     0,   266,   439,
     386,     0,     0,   386,     0,     0,     0,     0,   382,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     383,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   266,   266,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   829,     0,     0,   765,   829,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   499,
       0,   504,     0,   390,     0,     0,     0,     0,     0,     0,
     516,     0,     0,   516,   516,   390,     0,   266,     0,     0,
       0,     0,   439,     0,     0,     0,     0,   267,     0,   439,
       0,     0,     0,   825,     0,     0,     0,   825,   441,     0,
     390,     0,     0,     0,     0,   441,     0,   442,   442,   765,
       0,     0,     0,   386,   441,   555,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   386,     0,     0,     0,     0,
       0,   442,     0,   829,     0,     0,     0,     0,   442,     0,
     266,     0,     0,     0,     0,   555,     0,     0,     0,     0,
     386,     0,     0,     0,     0,     0,   765,   765,     0,     0,
       0,     0,     0,   337,   765,     0,   765,   765,     0,     0,
       0,     0,     0,     0,     0,   266,     0,     0,     0,     0,
     267,     0,     0,   825,     0,     0,     0,   442,     0,     0,
     387,   516,     0,     0,   516,     0,     0,   441,     2,     0,
       0,     0,   442,     0,   441,     0,   765,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   765,     0,     0,
       0,     0,     0,     0,   765,   765,     0,     0,   442,   468,
       0,     0,   555,     0,     0,     0,     0,     0,     0,   267,
       0,     0,   164,   165,   166,   167,   168,     0,     0,     0,
       0,   442,   442,     0,   442,     0,     0,     0,     0,     0,
       0,     0,   702,     0,     0,     0,     0,     0,     0,    14,
      15,    16,    17,    18,   171,    19,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,    26,    27,    28,    29,
      30,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   555,     0,   502,     0,     0,     0,   499,   267,
       0,     0,     0,     0,   504,     0,     0,     2,     0,     3,
       4,     0,     0,   382,     0,     0,     0,   442,     0,   499,
     700,   516,     0,     0,     0,   336,     5,     6,     0,     0,
       0,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,   555,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,   442,
       9,    10,    11,    12,   826,   826,   826,     0,    14,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,    25,     0,     0,    26,    27,    28,    29,    30,
      31,     0,     0,     0,     0,     0,   555,     0,   555,    32,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     0,     0,     0,    43,     0,     0,     0,     0,   141,
     142,     0,    44,   143,   144,     1,     2,   516,     3,     4,
       0,     0,   118,     0,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,   145,     5,     6,     0,     0,   516,
       0,   146,   147,   148,   149,     0,   150,   151,   152,   153,
     154,   155,     0,   442,     0,     0,     0,     0,     0,     0,
     442,     0,     0,     0,     0,     0,     0,     0,   904,   442,
     516,     0,     0,   516,     0,     0,     7,     8,     0,     9,
      10,    11,    12,     0,     0,    13,     0,    14,    15,    16,
      17,    18,     0,    19,    20,    21,    22,    23,    24,     0,
       0,    25,   267,   267,    26,    27,    28,    29,    30,    31,
       0,     0,     0,     0,     0,     0,     0,     0,    32,     0,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       0,     0,     0,    43,     0,     0,     0,     0,     0,     0,
     615,    44,     0,   616,     0,   617,     0,   267,     0,     0,
       0,     0,   442,    45,    46,    47,     0,     0,    48,   442,
       0,     0,     0,   967,     0,     0,     0,   826,     0,     0,
      14,    15,    16,    17,    18,   555,    19,    20,    21,    22,
      23,    24,   618,   516,     0,     0,     0,    26,    27,    28,
      29,    30,    31,     0,     2,   516,     3,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     904,     0,     0,     5,     6,     0,     0,     0,     0,     0,
     516,     0,     0,   160,   751,     0,   752,   753,   754,   755,
     756,   757,   758,   759,   760,   161,   162,   163,   164,   165,
     166,   167,   168,     0,     0,   267,     0,     0,   169,     0,
     170,     0,     0,   967,     7,     8,     0,     9,    10,    11,
      12,   761,     0,    13,     0,    14,    15,    16,    17,    18,
     171,    19,    20,    21,    22,    23,    24,     0,     0,    25,
     172,     0,    26,    27,    28,    29,    30,    31,     0,     0,
       0,     0,     0,   762,     0,     0,    32,     0,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     0,     0,
       2,    43,     3,     4,     0,     0,     0,     0,     0,    44,
       0,     0,   763,     0,   764,     0,     0,     0,     0,     5,
       6,    45,    46,    47,     0,     0,    48,     0,     0,   160,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   161,   162,   163,   164,   165,   166,   167,   168,     0,
       0,     0,     0,     0,   169,     0,   170,     0,     0,     0,
       7,     8,     0,     9,    10,    11,    12,     0,     0,    13,
       0,    14,    15,    16,    17,    18,   171,    19,    20,    21,
      22,    23,    24,     0,     0,    25,   172,     0,    26,    27,
      28,    29,    30,    31,     0,     0,     0,     0,     0,     0,
       0,     0,    32,     0,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     0,     0,     2,    43,     3,     4,
       0,     0,     0,     0,     0,    44,     0,     0,   933,     0,
       0,     0,     0,     0,     0,     5,     6,    45,    46,    47,
       0,     0,    48,     0,     0,   160,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
     169,     0,   170,     0,     0,     0,     7,     8,     0,     9,
      10,    11,    12,     0,     0,    13,     0,    14,    15,    16,
      17,    18,   171,    19,    20,    21,    22,    23,    24,     0,
       0,    25,   172,     0,    26,    27,    28,    29,    30,    31,
       0,     0,     0,     0,     0,     0,     0,     0,    32,     0,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       0,     0,     2,    43,     3,     4,     0,     0,     0,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,    45,    46,    47,     0,     0,    48,     0,
       0,   160,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   161,   162,   163,   164,   165,   166,   167,
     168,     0,     0,     0,     0,     0,   169,     0,   170,     0,
       0,     0,     7,     8,     0,     9,    10,    11,    12,     0,
       0,     0,     0,    14,    15,    16,    17,    18,   171,    19,
      20,    21,    22,    23,    24,     0,     0,    25,   172,     0,
      26,    27,    28,    29,    30,    31,     0,     2,     0,     3,
       4,     0,     0,     0,    32,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     5,     6,     0,    43,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     0,
       9,    10,    11,    12,     0,     0,    13,     0,    14,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,    25,     0,     0,    26,    27,    28,    29,    30,
      31,     0,     2,     0,     3,     4,     0,     0,     0,    32,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     5,     6,     0,    43,     0,     0,     0,     0,     0,
       0,     0,    44,     0,     0,     0,     0,   784,   889,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     0,     9,    10,    11,    12,     0,
       0,    13,     0,    14,    15,    16,    17,    18,     0,    19,
      20,    21,    22,    23,    24,     0,     0,    25,     0,     0,
      26,    27,    28,    29,    30,    31,     0,     2,     0,     3,
       4,     0,     0,     0,    32,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     5,     6,     0,    43,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
       0,     0,   784,     0,     0,     0,     0,     0,     0,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     0,
       9,    10,    11,    12,     0,     0,    13,     0,    14,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,    25,     0,     0,    26,    27,    28,    29,    30,
      31,     0,     2,     0,     3,     4,     0,     0,     0,    32,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     5,     6,     0,    43,     0,     0,     0,     0,     0,
       0,     0,    44,     0,     0,   874,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     0,     9,    10,    11,    12,     0,
       0,    13,     0,    14,    15,    16,    17,    18,     0,    19,
      20,    21,    22,    23,    24,     0,     0,    25,     0,     0,
      26,    27,    28,    29,    30,    31,     0,     2,     0,     3,
       4,     0,     0,     0,    32,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     5,     6,     0,    43,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     0,
       9,    10,    11,    12,     0,     0,    13,     0,    14,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,    25,     0,     0,    26,    27,    28,    29,    30,
      31,     0,     2,     0,     3,     4,     0,     0,     0,    32,
       0,    33,    34,    35,    36,    37,   613,    39,    40,    41,
      42,     5,     6,     0,    43,     0,     0,     0,     0,     0,
       0,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     0,     9,    10,    11,    12,     0,
       0,     0,     0,    14,    15,    16,    17,    18,     0,    19,
      20,    21,    22,    23,    24,     0,     0,    25,     0,     0,
      26,    27,    28,    29,    30,    31,     0,     2,     0,     3,
       4,     0,     0,     0,    32,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     5,     6,     0,    43,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     0,
       9,    10,    11,    12,     0,     0,     0,     0,    14,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,    25,     0,     0,    26,    27,    28,    29,    30,
      31,     0,     0,     0,     0,     0,     2,     0,     0,    32,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     0,     0,     0,    43,   299,   300,     0,     0,   301,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    46,    47,   428,   429,    48,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,   171,    19,    20,    21,    22,    23,    24,     0,
       0,     2,     0,   430,    26,    27,    28,    29,    30,    31,
       0,   302,   303,   304,   431,     0,     0,     0,     0,     0,
     299,   300,    35,     0,   301,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   550,   428,   429,     0,   164,   165,   166,   167,   168,
       0,   306,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,     0,    14,    15,    16,    17,    18,   171,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,   430,    26,
      27,    28,    29,    30,    31,     0,   302,   303,   304,   431,
       0,     0,     0,     0,     0,     0,     0,   428,   429,     0,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   305,     0,     0,     0,
       0,     2,     0,     0,     0,     0,   306,    14,    15,    16,
      17,    18,   171,    19,    20,    21,    22,    23,    24,     0,
       0,     0,     0,   430,    26,    27,    28,    29,    30,    31,
     160,     0,     0,     0,   431,     0,     0,     0,     0,   676,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     2,   169,     0,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,    15,    16,    17,    18,   171,    19,    20,
      21,    22,    23,    24,     0,     0,     0,   172,     0,    26,
      27,    28,    29,    30,    31,   428,   429,     0,   164,   165,
     166,   167,   168,   265,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    15,    16,    17,    18,
     171,    19,    20,    21,    22,    23,    24,   320,     0,     0,
       0,   430,    26,    27,    28,    29,    30,    31,     0,   321,
     322,   323,   431,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   324,     0,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      15,    16,    17,    18,     0,    19,    20,    21,    22,    23,
      24,     0,   320,     0,     0,     0,    26,    27,    28,    29,
      30,    31,     0,     0,   321,   322,   323,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   324,     0,   325,
       0,     0,     0,     0,     0,     0,     0,   528,   529,     0,
       0,     0,     0,   196,    14,    15,    16,    17,    18,     0,
      19,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,    26,    27,    28,    29,    30,    31,    14,    15,    16,
      17,    18,     0,    19,    20,    21,    22,    23,    24,   564,
     565,     0,     0,     0,    26,    27,    28,    29,    30,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   615,     0,     0,     0,     0,     0,     0,    14,
      15,    16,    17,    18,     0,    19,    20,    21,    22,    23,
      24,     0,     0,     0,     0,   748,    26,    27,    28,    29,
      30,    31,    14,    15,    16,    17,    18,     0,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,    26,
      27,    28,    29,    30,    31,    14,    15,    16,    17,    18,
       0,    19,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,    26,    27,    28,    29,    30,    31,    14,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     0,     0,    26,    27,    28,    29,    30,
      31
};

static const yytype_int16 yycheck[] =
{
       0,    13,    44,    90,   115,   436,   262,   199,    32,   175,
     202,   305,   465,   382,   452,   616,   617,   784,    44,   513,
      29,   453,   428,   429,   312,   691,    25,    29,   733,   196,
     524,   952,   526,   576,    24,   793,   137,   753,     7,     8,
       9,     5,   585,     5,    44,   262,   262,   306,   425,   306,
     212,   213,   214,   215,   107,   175,   814,    22,    23,     5,
     137,  1001,    88,   105,   106,   107,   108,    25,   394,   395,
     508,   133,   133,   103,   489,   117,   131,   509,   493,   105,
     106,   107,   108,  1023,    88,   523,   148,   148,   305,   200,
      44,   117,    32,   148,   137,   148,     5,  1018,   391,   131,
      62,   394,   395,   115,   312,   135,   131,     5,   137,   317,
     705,   706,   707,   138,   780,   157,   148,   159,   160,   161,
     162,   163,   553,   576,     5,   130,   382,   169,   170,   887,
     172,   157,   585,   159,   160,   161,   162,   163,   164,   181,
     139,   150,   865,   169,   170,   130,   172,   111,   150,     5,
     873,   105,   106,   107,   108,   145,   146,   157,   200,   159,
     164,   130,     5,     5,   380,   111,   130,   710,     0,   457,
     194,   140,   137,   199,   200,   391,   202,   135,   394,   395,
     149,   139,   949,   195,   196,   305,   512,   307,   200,   515,
     464,   907,   623,   951,   453,   199,   453,   902,   202,   915,
     916,   201,   111,   157,   962,   159,   583,   701,   375,   107,
     648,   428,   429,   111,   583,   647,     5,   241,     5,   512,
     262,   459,   515,   235,   236,   107,   821,   893,   270,   824,
     111,    22,    23,   142,   234,   452,   262,     5,   133,   239,
     998,   135,  1000,   130,   142,   139,   200,   135,   415,   681,
     509,   459,   509,   148,   194,   111,   550,   710,   532,   117,
     148,   142,     0,   305,   107,   131,   130,  1025,   111,   111,
     436,   391,   138,   547,   394,   395,   135,   131,   320,   321,
     322,   323,   324,   325,   138,   327,   142,   575,    25,   148,
     377,   508,   958,    27,    32,   511,   512,   130,    26,   515,
     142,   241,   160,   161,   162,   163,   523,   140,   739,   131,
     131,   169,   170,   317,   172,    28,   436,   479,   480,   141,
     109,   110,   111,   918,   111,   265,   652,   583,   822,    67,
       5,   130,   549,   550,   572,   573,  1002,   130,   130,   107,
     834,   140,   836,   111,   114,   130,   137,   138,   140,     5,
      88,    89,   130,   199,   396,   140,   202,    88,   125,   652,
     127,   128,   140,   375,   572,   573,   583,   575,    24,    25,
       5,   140,    28,   811,   975,   583,   971,   125,   126,   127,
     128,   119,   820,   425,    30,    31,   428,   429,   647,   141,
     647,   583,   512,    24,    25,   515,   134,    28,   804,   143,
     144,   413,   140,   415,   140,   447,   665,   125,   665,   127,
     452,   140,   436,   629,   125,   126,   127,   128,   132,    54,
      55,    56,   681,   125,   681,   127,   128,    62,    24,    25,
     550,   648,    28,   553,   650,   983,   652,   479,   480,   125,
     380,   127,   466,   141,   100,   101,   102,     5,   564,   565,
     492,   567,   132,   479,   480,   111,    54,    55,    56,   501,
     484,   137,  1010,  1011,   790,   903,   508,   137,   408,   100,
     101,   102,   910,   485,   130,   501,   488,   141,   490,   911,
     130,   523,  1030,   131,   140,   133,   528,   529,   131,   531,
     133,  1039,   700,   137,   753,   926,   753,   790,   131,   130,
     133,   995,   114,   623,   100,   101,   102,   549,   550,   140,
      32,   130,   632,   759,   320,   321,   322,   323,   324,   325,
     133,   327,   564,   565,     5,   567,   550,   105,   106,   553,
    1024,   107,   652,   533,   534,   535,   536,   125,   126,   127,
    1034,   583,    10,    11,   484,    67,   546,   131,   132,   711,
     712,   713,   714,   715,   716,   717,   718,   719,   720,   138,
     722,   125,   126,   127,   128,   589,    88,    89,   748,  1022,
     750,   511,   138,   615,   790,   131,   132,    65,    66,   205,
     206,   207,   624,   125,   126,   127,   128,   804,   630,   528,
     529,   633,   531,   138,   811,   637,   130,   119,   138,   623,
     131,   132,    90,   820,   630,   141,   648,   125,   126,   127,
     128,   637,   134,   135,    46,    47,   141,   737,   140,   739,
     560,   867,   132,     5,   132,   745,   114,   115,   116,   117,
     118,    46,   644,     3,     4,     5,     6,   135,    32,    46,
      47,   130,    24,    25,    10,    11,    28,   103,   907,   589,
     907,   131,   911,   132,   911,   132,   915,   916,   915,   916,
     684,   131,   132,   132,    34,   131,   132,   679,     0,   107,
     790,   683,   783,    67,   131,    45,    46,    47,    48,   132,
     722,   705,   706,   707,   930,   135,   903,   131,   132,   629,
       5,   733,   734,   910,    88,    89,   722,   131,   914,   741,
      32,   125,   126,   127,   128,   135,   748,   107,   750,   130,
     650,   131,   132,   737,   130,   739,   130,   759,   100,   101,
     102,   721,   764,   131,   132,   119,   131,   132,   770,   111,
       5,   977,   978,   759,   130,    67,   131,   132,   764,   985,
     134,   987,   988,   130,   770,   130,   140,   130,   130,   561,
     562,   706,   707,   394,   395,   130,    88,    89,   132,   921,
     142,   761,   804,   208,   209,   705,   706,   707,   131,   811,
     857,   783,   784,   210,   211,   216,   217,   132,   820,   637,
     107,  1027,   714,   715,   107,   141,   131,   119,  1004,   107,
     132,   130,  1038,   107,   132,   132,   107,   126,   107,  1045,
    1046,    24,   134,   131,   136,   139,   926,   132,   140,   131,
     136,   853,   854,   107,   135,   139,   107,   107,    88,   139,
     132,    25,   864,   865,   141,   867,   132,   853,   854,   871,
     133,   873,   136,   203,   204,   148,    27,    26,   864,   865,
      28,   867,   131,   138,   132,   871,   138,   873,   132,   136,
     117,   137,   132,   136,   139,   132,   898,   130,   132,   141,
     902,   903,    74,    32,   864,   865,   132,   132,   910,   132,
     107,   871,   898,   873,   105,   106,   107,   108,   136,   819,
     137,   130,   133,   139,   139,   132,   117,   130,   930,   130,
     914,     5,   130,   133,   918,   148,   130,   133,    67,   853,
     854,   759,   926,   305,   930,   130,   764,   136,   278,   141,
     312,   132,   770,   130,   136,   317,   130,   141,   148,    88,
      89,   148,   148,    24,   131,    45,   952,   133,   298,   160,
     161,   162,   163,   933,   114,   977,   978,   949,   169,   170,
     148,   172,   136,   985,   898,   987,   988,   148,   952,   148,
     119,   977,   978,   132,   996,   133,   131,   131,   107,   985,
     132,   987,   988,   148,   132,   134,    51,   136,   132,   132,
     996,   140,   130,   132,   914,   132,   136,   131,   918,   132,
    1004,   262,   132,   983,   984,  1027,   132,   148,   107,   141,
     133,   139,  1018,   133,   139,  1007,  1038,   133,   131,    36,
     132,  1027,   133,  1045,  1046,   133,   864,   865,   133,   867,
    1010,  1011,  1038,   871,  1018,   873,   615,   132,   734,  1045,
    1046,   961,   132,   549,   741,   630,   428,   429,     5,   736,
    1030,   262,   764,   673,   265,   745,     5,    99,   514,  1039,
      34,  1022,   996,   497,   918,   934,   946,    24,    25,   652,
     452,    28,    46,    47,    48,    24,    25,   459,   881,    28,
     100,   668,   666,    36,  1004,    59,   318,    61,    62,    63,
      64,    32,   930,    32,   305,   219,   218,   232,   716,   220,
     717,   312,   221,   719,   718,   921,   317,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    91,   720,   380,
     480,   722,   575,   770,    29,   336,   508,    -1,    -1,   103,
     391,    -1,    -1,   394,   395,    -1,    -1,    -1,    -1,   977,
     978,   523,    -1,   100,   101,   102,    -1,   985,    -1,   987,
     988,   100,   101,   102,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,    -1,    -1,    -1,    -1,   549,   550,   380,
      -1,   382,   383,   130,    -1,    -1,    -1,    -1,    -1,    -1,
     391,   130,    -1,   394,   395,   142,    -1,    -1,    -1,  1027,
     572,   573,    -1,   575,    -1,    -1,     5,   408,    -1,    -1,
    1038,   583,    -1,    -1,    -1,    -1,    -1,  1045,  1046,   305,
      -1,    -1,    -1,    -1,    -1,    -1,   312,   428,   429,    -1,
      -1,   317,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,    -1,    46,    -1,    -1,
      -1,   452,    -1,    -1,    -1,   150,    -1,    -1,   459,    -1,
     511,   512,    -1,    -1,   515,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   648,    76,    77,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    93,    94,    95,    96,    97,    98,
     501,    -1,    -1,    -1,    -1,    -1,    34,   508,   107,    -1,
     511,   512,    -1,    -1,   515,    -1,    -1,    -1,    46,    47,
      48,    -1,   523,    -1,    -1,    -1,    -1,    -1,   700,    -1,
      -1,    59,    -1,    61,    62,    63,    64,    -1,    -1,    -1,
      34,    -1,   428,   429,    -1,    -1,    -1,    -1,   549,   550,
      -1,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,   560,
      54,    55,    56,    91,    -1,    59,   452,    61,    62,    63,
      64,   572,   573,   459,   575,   103,    -1,    -1,   629,    -1,
      -1,    -1,   583,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    -1,    91,    -1,   650,
      -1,   652,    -1,    -1,   105,   106,   107,   108,    -1,   103,
      -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,
      -1,    -1,   508,    -1,    -1,    -1,    -1,    -1,   629,   630,
      -1,    -1,   804,    -1,   635,    -1,   637,   523,    -1,   811,
      -1,    -1,   136,    -1,    -1,    -1,    -1,   648,   820,   650,
      -1,   652,    -1,    34,   705,   706,   707,    -1,    -1,   160,
     161,   162,   163,   549,   550,    46,    47,    48,   169,   170,
      -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      61,    62,    63,    64,    -1,    -1,   572,   573,    -1,   575,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   583,   199,   700,
      -1,   202,    -1,     5,   705,   706,   707,    88,    89,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,   768,    -1,    -1,
      -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   903,    -1,    -1,    -1,    -1,    -1,    -1,   910,   790,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,   759,    -1,
      -1,   262,   648,   764,   265,    -1,    -1,   768,    -1,   770,
     821,    -1,    -1,   824,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,   790,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,   804,   305,   107,    -1,    -1,    -1,   111,
     811,   312,    -1,    -1,   700,    -1,   317,    -1,   819,   820,
     821,    -1,    -1,   824,    -1,    -1,    -1,    -1,   130,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   853,   854,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   914,    -1,    -1,   867,   918,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   380,
      -1,   382,    -1,   934,    -1,    -1,    -1,    -1,    -1,    -1,
     391,    -1,    -1,   394,   395,   946,    -1,   898,    -1,    -1,
      -1,    -1,   903,    -1,    -1,    -1,    -1,   408,    -1,   910,
      -1,    -1,    -1,   914,    -1,    -1,    -1,   918,   804,    -1,
     971,    -1,    -1,    -1,    -1,   811,    -1,   428,   429,   930,
      -1,    -1,    -1,   934,   820,   436,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   946,    -1,    -1,    -1,    -1,
      -1,   452,    -1,  1004,    -1,    -1,    -1,    -1,   459,    -1,
     961,    -1,    -1,    -1,    -1,   466,    -1,    -1,    -1,    -1,
     971,    -1,    -1,    -1,    -1,    -1,   977,   978,    -1,    -1,
      -1,    -1,    -1,   484,   985,    -1,   987,   988,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   996,    -1,    -1,    -1,    -1,
     501,    -1,    -1,  1004,    -1,    -1,    -1,   508,    -1,    -1,
     511,   512,    -1,    -1,   515,    -1,    -1,   903,     5,    -1,
      -1,    -1,   523,    -1,   910,    -1,  1027,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1038,    -1,    -1,
      -1,    -1,    -1,    -1,  1045,  1046,    -1,    -1,   549,   550,
      -1,    -1,   553,    -1,    -1,    -1,    -1,    -1,    -1,   560,
      -1,    -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      -1,   572,   573,    -1,   575,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   583,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   623,    -1,   111,    -1,    -1,    -1,   629,   630,
      -1,    -1,    -1,    -1,   635,    -1,    -1,     5,    -1,     7,
       8,    -1,    -1,   130,    -1,    -1,    -1,   648,    -1,   650,
     137,   652,    -1,    -1,    -1,   142,    24,    25,    -1,    -1,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,   684,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,   700,
      68,    69,    70,    71,   705,   706,   707,    -1,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      -1,    -1,    90,    -1,    -1,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,   737,    -1,   739,   107,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,    -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,   105,
     106,    -1,   130,   109,   110,     4,     5,   768,     7,     8,
      -1,    -1,   140,    -1,   142,   143,   144,    -1,    -1,   147,
      -1,    -1,    -1,    -1,   130,    24,    25,    -1,    -1,   790,
      -1,   137,   138,   139,   140,    -1,   142,   143,   144,   145,
     146,   147,    -1,   804,    -1,    -1,    -1,    -1,    -1,    -1,
     811,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   819,   820,
     821,    -1,    -1,   824,    -1,    -1,    65,    66,    -1,    68,
      69,    70,    71,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    87,    -1,
      -1,    90,   853,   854,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
      -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,
      46,   130,    -1,    49,    -1,    51,    -1,   898,    -1,    -1,
      -1,    -1,   903,   142,   143,   144,    -1,    -1,   147,   910,
      -1,    -1,    -1,   914,    -1,    -1,    -1,   918,    -1,    -1,
      76,    77,    78,    79,    80,   926,    82,    83,    84,    85,
      86,    87,    88,   934,    -1,    -1,    -1,    93,    94,    95,
      96,    97,    98,    -1,     5,   946,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     961,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,
     971,    -1,    -1,    34,    35,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,   996,    -1,    -1,    59,    -1,
      61,    -1,    -1,  1004,    65,    66,    -1,    68,    69,    70,
      71,    72,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    -1,    -1,    90,
      91,    -1,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,   104,    -1,    -1,   107,    -1,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,    -1,    -1,
       5,   122,     7,     8,    -1,    -1,    -1,    -1,    -1,   130,
      -1,    -1,   133,    -1,   135,    -1,    -1,    -1,    -1,    24,
      25,   142,   143,   144,    -1,    -1,   147,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    61,    -1,    -1,    -1,
      65,    66,    -1,    68,    69,    70,    71,    -1,    -1,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    -1,    -1,    90,    91,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,    -1,    -1,     5,   122,     7,     8,
      -1,    -1,    -1,    -1,    -1,   130,    -1,    -1,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,   142,   143,   144,
      -1,    -1,   147,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      59,    -1,    61,    -1,    -1,    -1,    65,    66,    -1,    68,
      69,    70,    71,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    -1,
      -1,    90,    91,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
      -1,    -1,     5,   122,     7,     8,    -1,    -1,    -1,    -1,
      -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,   142,   143,   144,    -1,    -1,   147,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    -1,    -1,    59,    -1,    61,    -1,
      -1,    -1,    65,    66,    -1,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    -1,    -1,    90,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,     5,    -1,     7,
       8,    -1,    -1,    -1,   107,    -1,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    24,    25,    -1,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
     143,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
      68,    69,    70,    71,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      -1,    -1,    90,    -1,    -1,    93,    94,    95,    96,    97,
      98,    -1,     5,    -1,     7,     8,    -1,    -1,    -1,   107,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,    24,    25,    -1,   122,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   130,    -1,    -1,    -1,    -1,   135,   136,    -1,
      -1,    -1,    -1,    -1,   142,   143,   144,    -1,    -1,   147,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    -1,    68,    69,    70,    71,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    -1,    -1,    90,    -1,    -1,
      93,    94,    95,    96,    97,    98,    -1,     5,    -1,     7,
       8,    -1,    -1,    -1,   107,    -1,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    24,    25,    -1,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,   135,    -1,    -1,    -1,    -1,    -1,    -1,   142,
     143,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
      68,    69,    70,    71,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      -1,    -1,    90,    -1,    -1,    93,    94,    95,    96,    97,
      98,    -1,     5,    -1,     7,     8,    -1,    -1,    -1,   107,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,    24,    25,    -1,   122,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   142,   143,   144,    -1,    -1,   147,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    -1,    68,    69,    70,    71,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    -1,    -1,    90,    -1,    -1,
      93,    94,    95,    96,    97,    98,    -1,     5,    -1,     7,
       8,    -1,    -1,    -1,   107,    -1,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    24,    25,    -1,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
     143,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
      68,    69,    70,    71,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      -1,    -1,    90,    -1,    -1,    93,    94,    95,    96,    97,
      98,    -1,     5,    -1,     7,     8,    -1,    -1,    -1,   107,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,    24,    25,    -1,   122,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   142,   143,   144,    -1,    -1,   147,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    -1,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    -1,    -1,    90,    -1,    -1,
      93,    94,    95,    96,    97,    98,    -1,     5,    -1,     7,
       8,    -1,    -1,    -1,   107,    -1,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    24,    25,    -1,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
     143,   144,    -1,    -1,   147,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
      68,    69,    70,    71,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      -1,    -1,    90,    -1,    -1,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,   107,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,    -1,    -1,    -1,   122,    24,    25,    -1,    -1,    28,
      -1,    -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   142,   143,   144,    46,    47,   147,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    -1,
      -1,     5,    -1,    92,    93,    94,    95,    96,    97,    98,
      -1,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      24,    25,   111,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   130,    46,    47,    -1,    49,    50,    51,    52,    53,
      -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    97,    98,    -1,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   130,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,    -1,   140,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    92,    93,    94,    95,    96,    97,    98,
      34,    -1,    -1,    -1,   103,    -1,    -1,    -1,    -1,   108,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,     5,    59,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    -1,    -1,    -1,    91,    -1,    93,
      94,    95,    96,    97,    98,    46,    47,    -1,    49,    50,
      51,    52,    53,   107,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    34,    -1,    -1,
      -1,    92,    93,    94,    95,    96,    97,    98,    -1,    46,
      47,    48,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    -1,    82,    83,    84,    85,    86,
      87,    -1,    34,    -1,    -1,    -1,    93,    94,    95,    96,
      97,    98,    -1,    -1,    46,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,
      -1,    -1,    -1,   130,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    93,    94,    95,    96,    97,    98,    76,    77,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    87,    46,
      47,    -1,    -1,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    -1,    82,    83,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    46,    93,    94,    95,    96,
      97,    98,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,    93,
      94,    95,    96,    97,    98,    76,    77,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    93,    94,    95,    96,    97,    98,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      -1,    -1,    -1,    -1,    -1,    93,    94,    95,    96,    97,
      98
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     4,     5,     7,     8,    24,    25,    65,    66,    68,
      69,    70,    71,    74,    76,    77,    78,    79,    80,    82,
      83,    84,    85,    86,    87,    90,    93,    94,    95,    96,
      97,    98,   107,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   122,   130,   142,   143,   144,   147,   152,
     206,   207,   209,   210,   211,   214,   215,   221,   225,   226,
     228,   230,   301,   302,   307,   308,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     329,   331,   332,    32,    67,    89,   119,   134,   140,   153,
     154,   155,   156,   157,   158,   160,   162,   164,   288,   289,
     290,   315,   315,   315,   315,   137,   137,   137,   137,   329,
     330,   221,   226,   308,   314,   130,   309,   310,   140,   315,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,   105,   106,   109,   110,   130,   137,   138,   139,   140,
     142,   143,   144,   145,   146,   147,   224,   130,   307,   130,
      34,    46,    47,    48,    49,    50,    51,    52,    53,    59,
      61,    81,    91,   228,   238,   262,   264,   284,   291,   294,
     297,   301,   332,   315,   315,   315,   315,     0,   125,   126,
     127,   128,   125,   127,   107,   130,   130,     7,     8,     9,
     130,   140,   149,    30,    31,    24,   145,   146,   143,   144,
     105,   106,    22,    23,   137,   138,    10,    11,    25,    27,
      26,    28,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    29,   139,   150,   328,   131,     5,   161,   130,
     114,   107,   228,   230,   244,   245,   158,    88,    34,    46,
      47,    48,    59,    61,    62,    63,    64,    91,   103,   159,
     239,   253,   257,   258,   288,   107,   209,   215,   228,   238,
     301,   238,   238,   238,   303,   329,   262,   311,   141,   140,
     140,   132,   141,   238,   238,   332,   262,   262,   262,   262,
     228,   230,   283,     5,   348,   262,   262,   262,   132,    24,
      25,    28,   100,   101,   102,   130,   140,   191,   192,   203,
     204,   205,   148,   349,   350,   103,   135,   285,   286,   287,
      34,    46,    47,    48,    59,    61,   263,   301,   132,   137,
     137,   221,   226,   303,   304,   304,   142,   215,   218,   219,
     283,   238,   303,   305,   306,   329,   332,   219,   283,   315,
     315,   316,   316,   316,   317,   317,   318,   318,   319,   319,
     319,   319,   320,   320,   321,   322,   323,   324,   325,   332,
     329,   329,   163,   332,   141,   130,   137,   114,   130,   133,
     107,   111,   130,   142,   179,   180,   209,   215,   222,   223,
     225,   228,   231,   232,   255,   264,   301,    34,    46,    47,
      48,    59,    61,    62,    63,    64,    91,   103,   107,   138,
     138,   138,   138,   131,   132,   130,   312,   313,   315,   141,
     141,   132,   132,   132,   135,   148,   315,    46,    46,    47,
      92,   103,   196,   197,   198,   199,   200,   203,   208,   209,
     210,   214,   215,   216,   217,   229,   264,   301,   326,   327,
     335,   204,   130,   140,    54,    55,    56,    62,   229,   295,
     351,   352,   353,   135,   130,   293,   107,   209,   215,   229,
     230,   287,   263,   263,   263,   263,   263,   263,   263,   212,
     213,   132,   132,   209,   107,   131,   132,   141,   148,   135,
     131,   304,   165,   135,   158,     5,   259,   260,   261,   215,
     223,   233,   111,   179,   215,   209,   135,   247,   130,   140,
     126,   107,   130,   181,   183,   191,   215,   223,   227,   276,
     277,   278,   130,   252,   181,   277,   181,   277,    46,    47,
     256,   301,   130,   130,   130,   130,   130,   329,   304,     5,
     298,   299,   300,   255,   200,   200,   130,   130,   132,   131,
     130,   176,   177,   191,   204,   215,   221,   132,   127,   127,
     107,    46,    47,   202,    46,    47,   201,   301,   141,   196,
     335,   295,   296,    62,   352,   131,   292,   261,    34,   156,
     167,   241,   254,   257,   265,   266,   267,   271,   295,   107,
     238,   319,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   346,   125,   126,   127,   128,   219,
     329,   329,   155,   114,   132,    46,    49,    51,    88,   170,
     171,   172,   173,   174,   301,   155,   130,   259,   132,   107,
      46,   228,   234,   301,   132,   107,   126,   248,   196,   335,
     222,   223,   181,    25,   139,   247,   279,   140,   252,   181,
     107,    24,   131,   196,   247,   247,   256,   256,   256,   261,
     332,   332,   332,   332,   132,   139,   131,   136,   135,   332,
     261,    46,    47,   193,   194,   195,   108,   199,   176,   139,
     130,   140,   176,   139,   107,   226,   202,   202,   201,   201,
     201,   132,   141,   352,   352,   353,   271,   132,    88,   133,
     137,   179,   215,   219,   220,   229,   255,   264,   271,   136,
     148,    22,    23,   137,    10,    11,    25,    27,    26,    28,
      29,   150,   131,   138,   138,   125,   126,   127,   136,   132,
     174,   348,   348,   137,   131,   138,   139,   130,   176,   191,
     175,   301,   136,   117,   234,   191,   236,   237,    46,   235,
     301,    35,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    72,   104,   133,   135,   209,   250,   251,   262,   332,
     354,   355,   356,   359,   360,   362,   363,   364,   365,   366,
     132,   141,   132,   130,   135,   281,   329,   335,   196,   226,
     182,   181,   278,   132,   132,   132,   132,   132,   132,   327,
     334,   300,   299,   132,   132,   194,    74,   189,   190,   132,
     329,   178,   335,   329,   195,   136,   137,   229,   247,   107,
     130,   130,   184,   186,   191,   209,   215,   221,   223,   225,
     226,   227,   268,   270,   184,   268,   184,   268,   269,   271,
     319,   319,   319,   336,   336,   337,   338,   339,   340,   341,
     332,   347,   133,   139,   139,   170,   171,   166,   206,   175,
     132,   237,   235,   235,   130,   130,   334,   148,     5,   133,
     133,   130,   354,   130,   133,   332,   130,   251,   126,   127,
     136,   184,   273,   274,   275,   133,   366,   195,   303,   136,
     281,   282,   141,   132,   181,   190,   136,   200,   130,   196,
     141,   190,   168,   130,   215,   196,   184,   139,   247,   272,
     130,   140,   184,   126,   107,   148,   148,    24,   131,   247,
     247,   148,   238,   238,   138,   158,   262,   332,   361,   361,
     148,   354,   133,   133,   262,   332,    45,   361,   133,   114,
     136,   148,   148,   249,   279,   133,   131,   190,   132,   131,
     280,   195,   148,   242,   246,   187,   188,   238,   132,   170,
     196,   107,   132,   132,   334,   196,   335,   215,   226,   334,
     334,   185,   184,   270,   344,    51,   176,   132,   132,   354,
     332,   333,   273,   133,   130,   132,   132,   357,   358,   275,
     281,   136,   190,   243,   244,   240,   131,   132,   195,   138,
     132,   190,   132,   141,   107,   184,   348,   139,   354,   354,
     133,   133,   333,   332,   354,   133,   354,   354,   131,   247,
     238,   190,   169,   190,   246,   195,   329,    36,   333,   333,
     133,   132,   244,   266,   246,   247,   190,   354,   132,   133,
     333,   133,   247,   354,   333,   132,   132,   354,   354
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 682 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { g_exp = (yyvsp[(1) - (1)].exp) ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 684 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { translation_unit = (yyvsp[(2) - (2)].declarationList); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 705 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {	(yyval.declarationList) = (yyvsp[(1) - (1)].declarationList); 	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 722 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarationList) = new ast::DeclarationList((yyvsp[(1) - (1)].declaration), NULL) ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 723 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarationList) = new ast::DeclarationList((yyvsp[(2) - (2)].declaration), (yyvsp[(1) - (2)].declarationList)) ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 726 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarationList) = NULL ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 734 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = new StaticAssertDeclaration((yylsp[(1) - (7)]), (yyvsp[(3) - (7)].exp), (yyvsp[(5) - (7)].string_literal)) ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 738 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
		DoImport((yyvsp[(1) - (1)].string_literal));
	 (yyval.declaration) = new ImportDeclaration((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].string_literal))
	 ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 742 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = new PragmaDeclaration((yylsp[(1) - (2)]), (yyvsp[(2) - (2)].string_literal)) ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 743 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = (yyvsp[(2) - (3)].declaration); Do((yyvsp[(1) - (3)].expList), (yyval.declaration)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 744 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = (yyvsp[(2) - (2)].declaration); Do((yyvsp[(1) - (2)].expList), (yyval.declaration)) ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 745 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = (yyvsp[(2) - (2)].declaration); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 746 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = (yyvsp[(1) - (1)].declaration); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 747 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = (yyvsp[(1) - (1)].declaration); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 751 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = new ast::LinkageDeclaration((yylsp[(1) - (5)]), (yyvsp[(2) - (5)].string_literal), (yyvsp[(4) - (5)].declarationList)) ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 752 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = new ast::LinkageDeclaration((yylsp[(1) - (3)]), (yyvsp[(2) - (3)].string_literal), new ast::DeclarationList((yyvsp[(3) - (3)].declaration), NULL)) ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 765 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
		ast::NamespaceDefinition* nsdef = new ast::NamespaceDefinition((yylsp[(1) - (2)]), (yyvsp[(2) - (2)].id), NULL);
		g_templates.push(nsdef);

		g_scopeStack.push(g_pScope);
	//	g_scopeStack.push(g_pScope2);

		Do(NULL, nsdef);
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 775 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
		ast::NamespaceDefinition* nsdef = (ast::NamespaceDefinition*)g_templates.top();

		g_templates.pop();
		nsdef->m_declarationList = Reverse((yyvsp[(5) - (6)].declarationList));

	//	g_pScope2 = g_scopeStack.top();
	//	ASSERT(g_pScope2);
	//	g_scopeStack.pop();

		g_pScope = g_scopeStack.top();
		ASSERT(g_pScope);
		g_scopeStack.pop();

		g_pScope2 = g_pScope;

		(yyval.declaration) = nsdef;
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 799 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	(yyval.declaration) = new ast::TemplateDeclaration((yylsp[(2) - (3)]), NULL, NULL);
	g_templates.push((yyval.declaration));
	DoTp((ast::TemplateDeclaration*)(yyval.declaration));

	g_scopeStack.push(g_pScope);
	g_scopeStack.push(g_pScope2);
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 808 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	ast::TemplateDeclaration* td = (ast::TemplateDeclaration*)g_templates.top();
	td->m_params = Reverse((yyvsp[(5) - (6)].templateParameterList));
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 813 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	ast::TemplateDeclaration* td = (ast::TemplateDeclaration*)g_templates.top();
	g_templates.pop();
//	ASSERT(g_pScope);

	g_pScope2 = g_scopeStack.top();
	g_scopeStack.pop();
	templateParams = NULL;//.clear();

	g_pScope = g_scopeStack.top();
	g_scopeStack.pop();

/*
		if (g_pScope2->m_name == NULL)
			LOG("here scope ---------------------- global scope\n");
		else
			LOG("here scope ---------------------- %s\n", g_pScope2->m_name->c_str());
*/

	td->m_decl = (yyvsp[(8) - (8)].declaration);
	(yyval.declaration) = td;
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 838 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	(yyval.declaration) = new ast::TemplateDeclaration((yylsp[(2) - (3)]), NULL, NULL);
	g_templates.push((yyval.declaration));
	DoTp((ast::TemplateDeclaration*)(yyval.declaration));

	g_scopeStack.push(g_pScope);
	g_scopeStack.push(g_pScope2);
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 847 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	ast::TemplateDeclaration* td = (ast::TemplateDeclaration*)g_templates.top();
	td->m_params = Reverse((yyvsp[(5) - (6)].templateParameterList));
/*
	$$ = new ast::A_TemplateDeclaration($4, NULL);
	g_templates.push($$);

	g_scopeStack.push(g_pScope2);

	DoTp((ast::TemplateDeclaration*)$$)
	*/
;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 860 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	ast::TemplateDeclaration* td = (ast::TemplateDeclaration*)g_templates.top();
	g_templates.pop();
//	ASSERT(g_pScope);

	g_pScope2 = g_scopeStack.top();
	g_scopeStack.pop();
	templateParams = NULL;//.clear();

//	g_pScope = g_pScope2;

	g_pScope = g_scopeStack.top();
	g_scopeStack.pop();

	td->m_decl = (yyvsp[(8) - (8)].declaration);
	(yyval.declaration) = td;
;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 879 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameterList) = new ast::TemplateParameterList((yyvsp[(1) - (1)].templateParameter), NULL) ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 880 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameterList) = new ast::TemplateParameterList((yyvsp[(3) - (3)].templateParameter), (yyvsp[(1) - (3)].templateParameterList)) ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 883 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = (yyvsp[(1) - (1)].templateParameter); Do_TParam((yyval.templateParameter)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 884 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = (yyvsp[(1) - (1)].templateParameter); Do_TParam((yyval.templateParameter)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 885 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = (yyvsp[(1) - (3)].templateParameter); Do_TParam((yyval.templateParameter), (yyvsp[(3) - (3)].exp)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 888 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = new ast::TypeTemplateParameter((yyvsp[(2) - (2)].id), NULL) ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 889 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = new ast::TypeTemplateParameter((yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].typeId)) ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 890 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = new ast::TypeTemplateParameter((yyvsp[(2) - (2)].id), NULL) ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 891 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = new ast::TypeTemplateParameter((yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].typeId)) ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 895 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateParameter) = new ast::DeclaratorTemplateParameter((yyvsp[(1) - (2)].declspecList), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 898 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 899 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 900 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 903 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 904 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 907 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {(yyval.declarator) = new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].directDeclarator)) ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 908 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = new ast::A_PtrDeclarator((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 911 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorId((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)); g_scopeStack2.pop() ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 912 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DeclaratorDirectDeclarator((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].declarator)) ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 914 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_scopeStack.push(g_pScope);

							g_scopeStack.push(g_pScope2);
							
							ASSERT(g_lastScope);
							if (g_lastScope->m_pNamespace->AsClass())
							{
								ASSERT(g_lastScope->m_pNamespace->AsClass());

								/* Either :
								classname::func(...

								or
								void memfun(void (*fun)(..))

								*/

								// If first case
								if (g_pScope2 != g_lastScope)
								{
									ASSERT(g_pScope2 != g_lastScope);
									g_lastScope->m_pParentScope = g_pScope2;
									g_pScope2 = g_lastScope;
								}
							}

							g_scopeStack.push(g_lastScope);
						;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 945 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_lastScope = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

						//	g_pScope2 = g_pScope;

							(yyval.directDeclarator) = ast::A_DirectDeclaratorParen((yyvsp[(1) - (7)].directDeclarator), (yyvsp[(4) - (7)].paramDecls), (yyvsp[(6) - (7)].declspecList));
						;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 959 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorArray((yyvsp[(1) - (4)].directDeclarator), (yyvsp[(3) - (4)].exp)) ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 973 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {(yyval.declarator) = new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].directDeclarator)) ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 976 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorId((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)); g_scopeStack2.pop() ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 977 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DeclaratorDirectDeclarator((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].declarator)) ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 978 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorParen((yyvsp[(1) - (6)].directDeclarator), (yyvsp[(3) - (6)].paramDecls), (yyvsp[(5) - (6)].declspecList)) ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 979 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorArray((yyvsp[(1) - (4)].directDeclarator), (yyvsp[(3) - (4)].exp)) ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 982 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {(yyval.declarator) = new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].directDeclarator)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 983 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = new ast::A_PtrDeclarator((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 984 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { g_scopeStack2.pop(); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 985 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
					(yyval.declarator) = new ast::A_PtrDeclarator((yylsp[(1) - (4)]), '.*', (yyvsp[(4) - (4)].declarator), (yyvsp[(1) - (4)].exp));
				;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 990 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorId((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)); g_scopeStack2.pop() ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 991 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorId((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)); g_scopeStack2.pop() ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 992 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DeclaratorDirectDeclarator((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].declarator)) ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 995 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_lastScope = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

						//	g_pScope2 = g_pScope;

							(yyval.directDeclarator) = ast::A_DirectDeclaratorParen((yyvsp[(1) - (6)].directDeclarator), (yyvsp[(3) - (6)].paramDecls), (yyvsp[(5) - (6)].declspecList));
						;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1009 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorArray((yyvsp[(1) - (4)].directDeclarator), (yyvsp[(3) - (4)].exp)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1012 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {(yyval.declarator) = new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].directDeclarator)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1013 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = new ast::A_PtrDeclarator((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1014 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { g_scopeStack2.pop(); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1015 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declarator) = new ast::A_PtrDeclarator((yylsp[(1) - (4)]), '.*', (yyvsp[(4) - (4)].declarator), (yyvsp[(1) - (4)].exp));
							;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1020 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorId((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)); g_scopeStack2.pop() ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1021 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorId((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)); g_scopeStack2.pop() ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1022 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DeclaratorDirectDeclarator((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].declarator)) ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1023 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorParen((yyvsp[(1) - (6)].directDeclarator), (yyvsp[(3) - (6)].paramDecls), (yyvsp[(5) - (6)].declspecList)); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1024 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorArray((yyvsp[(1) - (4)].directDeclarator), (yyvsp[(3) - (4)].exp)); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1043 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '*' ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1044 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '*' ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1045 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '&' ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1046 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '&&' ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1049 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = 'c'; ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1050 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = 's'; ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1051 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = 'f'; ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1054 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typespec) = new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONST) ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1055 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typespec) = new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_VOLATILE) ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1058 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList((yyvsp[(1) - (1)].typespec), NULL) ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1059 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList((yyvsp[(1) - (2)].typespec), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1062 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = NULL ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1066 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.paramDecls) = new ast::ParameterDeclarations((yyvsp[(1) - (1)].typeIdList), false) ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1067 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.paramDecls) = new ast::ParameterDeclarations((yyvsp[(1) - (3)].typeIdList), true) ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1070 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeIdList) = new ast::A_TypeIdList((yyvsp[(1) - (1)].typeId), NULL) ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1071 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeIdList) = new ast::A_TypeIdList((yyvsp[(3) - (3)].typeId), (yyvsp[(1) - (3)].typeIdList)) ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1074 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeIdList) = NULL ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1078 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeId) = new ast::A_TypeId((yyvsp[(1) - (2)].declspecList), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1079 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeId) = new ast::A_TypeId((yyvsp[(1) - (4)].declspecList), (yyvsp[(2) - (4)].declarator)) ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1080 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeId) = new ast::A_TypeId((yyvsp[(1) - (2)].declspecList), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1081 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeId) = new ast::A_TypeId((yyvsp[(1) - (4)].declspecList), (yyvsp[(2) - (4)].declarator), (yyvsp[(4) - (4)].exp)) ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1084 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1085 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_VOLATILE), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1086 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1087 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1088 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList((yyvsp[(1) - (1)].declspec), NULL) ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1089 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_NameType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)), NULL) ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1090 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_NameType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].exp)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1091 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecExtModifier((yylsp[(1) - (5)]), Reverse((yyvsp[(3) - (5)].declspecExtList))), (yyvsp[(5) - (5)].declspecList)) ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1092 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList((yyvsp[(1) - (1)].declspec), NULL) ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1095 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1096 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1097 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1098 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1099 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONST), NULL) ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1100 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONST), NULL) ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1103 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1104 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_VOLATILE), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1105 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONST), NULL) ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1106 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_VOLATILE), NULL) ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1109 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].directDeclarator)) ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1110 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = new ast::A_PtrDeclarator((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1113 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = NULL ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1117 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorParen((yyvsp[(1) - (6)].directDeclarator), (yyvsp[(3) - (6)].paramDecls), (yyvsp[(5) - (6)].declspecList)) ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1118 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorArray((yyvsp[(1) - (4)].directDeclarator), (yyvsp[(3) - (4)].exp)) ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1119 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { ast::A_DirectDeclaratorParen(NULL, (yyvsp[(2) - (5)].paramDecls), (yyvsp[(4) - (5)].declspecList)) ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1120 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DirectDeclaratorArray(NULL, (yyvsp[(2) - (3)].exp)) ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1121 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.directDeclarator) = ast::A_DeclaratorDirectDeclarator((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].declarator)) ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1126 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BoolExp(0) ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1127 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BoolExp(1) ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1128 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_Int32Exp((yyvsp[(1) - (1)].num)) ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1129 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_DoubleExp((yyvsp[(1) - (1)].doubleValue)) ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1130 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_StringExp((yyvsp[(1) - (1)].string_literal)) ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1131 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_LStringExp((yyvsp[(1) - (1)].string_literal)) ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1132 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::CharLiteralExp((yyvsp[(1) - (1)].num)) ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1133 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::NullLiteralExp() ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1137 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_ThisExp() ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1138 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp);}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1156 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspec) = new ast::DeclType((yylsp[(1) - (4)]), (yyvsp[(3) - (4)].exp)) ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1159 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
			StringA* identifier = (yyvsp[(1) - (1)].id);

			g_lastScope = g_pScope;

			if (g_scopeStack2.cont.size() == 0)
			{
				Scope* pScope = parse_LookupScopeNameRecurse(g_pScope2, identifier);
				if (pScope)
				{
					if (pScope->m_pNamespace->AsClass() && pScope->m_pNamespace->AsClass()->m_pInstantiatedFromArgs)
					{
						ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTY, pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pScope), ptoken);
						g_scopeStack2.push(pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pScope);
					}
					else
					{
						if (pScope->m_pNamespace->AsClass() && pScope->m_pNamespace->AsClass()->m_pTemplateParams)
						{
							ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTT, pScope), ptoken);
							g_scopeStack2.push(pScope);
						}
						else
						{
							ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTY, pScope), ptoken);
							g_scopeStack2.push(pScope);
						}
					}
				}
				else
				{
					Type* pType = parse_LookupTypeNameRecurse(g_pScope2, identifier);
					if (pType)
					{
						ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTY), ptoken);
						g_scopeStack2.push(NULL);
					}
					else
					{
						ptoken = new ast::Expression2List(new ast::Expression2((yylsp[(1) - (1)])/*cpp_exp_lloc*/, NTY), ptoken);
						g_scopeStack2.push(NULL);
					}
				}
			}
			else
			{
				if (g_scopeStack2.top() == NULL)
				{
					ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, NTY), ptoken);
					g_scopeStack2.push(NULL);
				}
				else
				{
					Scope* pScope = parse_LookupScopeName(g_scopeStack2.top(), identifier);
					if (pScope)
					{
						if (pScope->m_pNamespace->AsClass() && pScope->m_pNamespace->AsClass()->m_pInstantiatedFromArgs)
						{
							ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTY, pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pScope), ptoken);
							ASSERT(pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pScope);
							g_scopeStack2.push(pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pScope);
						}
						else
						{
							if (pScope->m_pNamespace->AsClass() && pScope->m_pNamespace->AsClass()->m_pTemplateParams)
							{
								ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTT, pScope), ptoken);
								ASSERT(pScope);
								g_scopeStack2.push(pScope);
							}
							else
							{
								ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTY, pScope), ptoken);
								ASSERT(pScope);
								g_scopeStack2.push(pScope);
							}
						}
					}
					else
					{
						Type* pType = parse_LookupTypeName(g_scopeStack2.top(), identifier);

						if (pType)
						{
							ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, YTY), ptoken);
							g_scopeStack2.push(NULL);
						}
						else
						{
							ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, NTY), ptoken);
							g_scopeStack2.push(NULL);
						}
					}
				}
			}

			if (g_pClass2)
			{
				if (*(yyval.id) == *g_pClass2->m_name)
				{
					ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, CTORN), ptoken);
				//	g_scopeStack2.pop();
				}
			}

			(yyval.id) = identifier;
		;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1272 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
		g_scopeStack2Stack.push(g_scopeStack2);
		g_scopeStack2.cont.clear();
		;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1278 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
		g_scopeStack2 = g_scopeStack2Stack.top();
		g_scopeStack2Stack.pop();

		(yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (6)].id), (yyvsp[(5) - (6)].templateArgumentList));
		;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1286 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
		g_scopeStack2Stack.push(g_scopeStack2);
		g_scopeStack2.cont.clear();
		;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1292 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
		g_scopeStack2 = g_scopeStack2Stack.top();
		g_scopeStack2Stack.pop();

		(yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (6)].id), (yyvsp[(5) - (6)].templateArgumentList));
		;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1300 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (2)].id), nullptr); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1301 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (2)].id), nullptr); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1319 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (2)].id), nullptr); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1320 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (2)].id), nullptr); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1332 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (2)].id), NULL); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1333 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_TemplateId((yyvsp[(1) - (2)].id), NULL); ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1338 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (1)]), '::', (yyvsp[(1) - (1)].exp), NULL)
						;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1342 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_lastScope = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1360 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (3)]), '~', ast::A_TemplateId((yyvsp[(2) - (3)].id), nullptr)); ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1361 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (3)]), '~', ast::A_TemplateId((yyvsp[(2) - (3)].id), nullptr)); ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1362 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (3)]), '~', ast::A_TemplateId((yyvsp[(2) - (3)].id), nullptr)); ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1363 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (4)]), '~', ast::A_TemplateId((yyvsp[(2) - (4)].id), nullptr)); ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1364 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (4)]), '~', ast::A_TemplateId((yyvsp[(2) - (4)].id), nullptr)); ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1365 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (4)]), '~', ast::A_TemplateId((yyvsp[(2) - (4)].id), nullptr)); ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1369 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (1)]), '::', (yyvsp[(1) - (1)].exp), nullptr)
						;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1373 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_lastScope = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1387 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
				g_scopeStack2.pop();
				;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1410 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (2)]), '::', ast::A_TemplateId((yyvsp[(1) - (2)].id), NULL), NULL); ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1413 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (1)]), '::', (yyvsp[(1) - (1)].exp), NULL); ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1416 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
					(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));

					Scope* top = g_scopeStack2.top();
					g_scopeStack2.pop();

					g_lastScope = g_scopeStack2.top();
					g_scopeStack2.pop();

					g_scopeStack2.push(top);
				;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1429 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (1)]), '::', (yyvsp[(1) - (1)].exp), NULL); ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1431 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
									(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));

									Scope* top = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_lastScope = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_scopeStack2.push(top);
								;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1444 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (2)]), '::', ast::A_TemplateId((yyvsp[(1) - (2)].id), NULL), NULL); ;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1445 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', ast::A_UnopExp((yylsp[(1) - (3)]), '~', ast::A_TemplateId((yyvsp[(2) - (3)].id), NULL)), NULL); ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1447 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (1)]), '::', (yyvsp[(1) - (1)].exp), NULL); ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1451 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
									(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));

									Scope* top = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_lastScope = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_scopeStack2.push(top);
								;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1470 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = 'new' ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1471 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = 'del' ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1472 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = 'new[' ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1473 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = 'del[' ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1474 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '=' ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1475 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '<' ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1476 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '>' ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1477 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '+' ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1478 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '-' ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1479 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '/' ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1480 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '%' ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1481 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '!' ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1482 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '~' ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1483 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '==' ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1484 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '!=' ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1485 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '<=' ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1486 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '>=' ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1487 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '()' ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1488 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '[]' ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1489 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '++' ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1490 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '--' ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1491 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '|' ;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1492 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '^' ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1493 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '&' ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1494 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '*' ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1495 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '->' ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1496 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '<<' ;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1497 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '>>' ;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1498 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '|=' ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1499 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '^=' ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1500 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '&=' ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1501 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '<<=' ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1502 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '>>=' ;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1503 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '+=' ;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1504 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '-=' ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1505 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '*=' ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1506 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '/=' ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1507 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '%=' ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1510 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_OperatorExp((yylsp[(1) - (2)]), (yyvsp[(2) - (2)].num)); g_scopeStack2.push(NULL); ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1516 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (1)]), '::', (yyvsp[(1) - (1)].exp), NULL)
						;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1520 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1532 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (1)]), '::', (yyvsp[(1) - (1)].exp), NULL)
						;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1536 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (2)]), '::', (yyvsp[(1) - (2)].exp), ast::A_BinopExp((yylsp[(2) - (2)]), '::', NULL, NULL));
						;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1540 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '::', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1570 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
						(yyval.exp) = (yyvsp[(1) - (1)].exp);
						g_scopeStack2.pop();
					;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1575 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
						ASSERT(0);
						(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (2)]), '::', NULL, (yyvsp[(2) - (2)].exp))
					;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1584 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
						(yyval.exp) = (yyvsp[(1) - (1)].exp);
						g_scopeStack2.pop();
					;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1594 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.exp) = (yyvsp[(1) - (1)].exp);
								g_scopeStack2.pop();
							;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1599 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (2)]), '::', NULL, (yyvsp[(2) - (2)].exp));
								g_scopeStack2.pop();
							;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1608 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.exp) = (yyvsp[(1) - (1)].exp);
								g_scopeStack2.pop();
							;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1613 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.exp) = ast::A_BinopExp((yylsp[(1) - (2)]), '::', NULL, (yyvsp[(2) - (2)].exp));
								g_scopeStack2.pop();
							;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1630 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	g_scopeStack2Stack.push(g_scopeStack2);
	g_scopeStack2.cont.clear();
;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1635 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
	g_scopeStack2 = g_scopeStack2Stack.top();
	g_scopeStack2Stack.pop();

	(yyval.exp) = new ast::ConversionExp(new ast::A_TypeId((yyvsp[(3) - (4)].declspecList), (yyvsp[(4) - (4)].declarator))); g_scopeStack2.push(NULL);
;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1643 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1644 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1645 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1646 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_NameType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)), NULL) ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1649 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONST), NULL) ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1650 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), NULL) ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1651 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1652 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), NULL) ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1661 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = new ast::A_PtrDeclarator((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1664 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declarator) = NULL ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1668 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeId) = new ast::A_TypeId((yyvsp[(1) - (2)].declspecList), (yyvsp[(2) - (2)].declarator)) ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1672 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								g_lastScope = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope2 = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope = g_scopeStack.top();
								g_scopeStack.pop();
;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1683 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(1) - (9)]), (yyvsp[(1) - (9)].declspecList), new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (9)]), ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId((yylsp[(2) - (9)]), (yyvsp[(2) - (9)].exp)), (yyvsp[(4) - (9)].paramDecls), NULL)), (yyvsp[(7) - (9)].expList), (yyvsp[(9) - (9)].compoundstm));
							//	LOG("ctor/dtor\n");
							;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1688 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(3) - (4)]), Reverse((yyvsp[(1) - (4)].declspecList), (yyvsp[(2) - (4)].declspecList)), (yyvsp[(3) - (4)].declarator), NULL, (yyvsp[(4) - (4)].compoundstm));
							//	LOG("basic_type\n");
							;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1693 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(3) - (4)]), Reverse((yyvsp[(1) - (4)].declspecList), new ast::DeclSpecList((yyvsp[(2) - (4)].declspec), NULL)), (yyvsp[(3) - (4)].declarator), NULL, (yyvsp[(4) - (4)].compoundstm));
							//	LOG("elaborated\n");
							;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1698 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(3) - (4)]), Reverse((yyvsp[(1) - (4)].declspecList), new ast::DeclSpecList(new ast::A_NameType((yylsp[(2) - (4)]), (yyvsp[(2) - (4)].exp)), NULL)), (yyvsp[(3) - (4)].declarator), NULL, (yyvsp[(4) - (4)].compoundstm));
							//	LOG("type\n");
							;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1703 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(2) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList)), (yyvsp[(2) - (3)].declarator), NULL, (yyvsp[(3) - (3)].compoundstm));
							;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1724 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(1) - (4)]), Reverse((yyvsp[(1) - (4)].declspecList), (yyvsp[(2) - (4)].declspecList)), (yyvsp[(3) - (4)].declarator), NULL, (yyvsp[(4) - (4)].compoundstm));
							//	LOG("basic_type\n");
							;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1729 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(1) - (4)]), Reverse((yyvsp[(1) - (4)].declspecList), new ast::DeclSpecList((yyvsp[(2) - (4)].declspec), NULL)), (yyvsp[(3) - (4)].declarator), NULL, (yyvsp[(4) - (4)].compoundstm));
							//	LOG("elaborated\n");
							;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1734 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(1) - (4)]), Reverse((yyvsp[(1) - (4)].declspecList), new ast::DeclSpecList(new ast::A_NameType((yylsp[(2) - (4)]), (yyvsp[(2) - (4)].exp)), NULL)), (yyvsp[(3) - (4)].declarator), NULL, (yyvsp[(4) - (4)].compoundstm));
							//	LOG("type\n");
							;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1739 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(1) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList)), (yyvsp[(2) - (3)].declarator), NULL, (yyvsp[(3) - (3)].compoundstm));
							//	LOG("type\n");
							;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1744 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(2) - (9)]), (yyvsp[(1) - (9)].declspecList), new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (9)]), ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId((yylsp[(3) - (9)]), (yyvsp[(3) - (9)].exp)), (yyvsp[(5) - (9)].paramDecls), NULL)), (yyvsp[(8) - (9)].expList), (yyvsp[(9) - (9)].compoundstm));
							//	LOG("ctor\n");
								ASSERT(g_scopeStack2.cont.size() == 0);
								
							;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1751 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::FunDefDecl((yylsp[(1) - (8)]), (yyvsp[(1) - (8)].declspecList), new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (8)]), ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId((yylsp[(2) - (8)]), (yyvsp[(2) - (8)].exp)), (yyvsp[(4) - (8)].paramDecls), NULL)), (yyvsp[(7) - (8)].expList), (yyvsp[(8) - (8)].compoundstm));
							//	LOG("ctor\n");
							;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1770 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = (yyvsp[(2) - (2)].expList) ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1773 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(1) - (1)].exp), nullptr); ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1774 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].expList)); ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1777 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::CallExp((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].expList)) ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1783 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = nullptr ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1788 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
						g_scopeStack.push(g_pScope);
						g_scopeStack.push(g_pScope2);

						Scope* pFunctionScope = new Scope;

						ASSERT(g_lastScope);

						if (g_lastScope->m_pNamespace && g_lastScope->m_pNamespace->AsClass())
						{
							pFunctionScope->m_pParentScope = g_lastScope;
						}
						else
						{
							pFunctionScope->m_pParentScope = g_pScope2;
						}

						g_pScope = pFunctionScope;
						g_pScope2 = pFunctionScope;
					;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1809 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
						g_pScope2 = g_scopeStack.top();
						g_scopeStack.pop();

						g_pScope = g_scopeStack.top();
						g_scopeStack.pop();
					;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1816 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.compoundstm) = new ast::CompoundStm((yylsp[(1) - (5)]), (yylsp[(4) - (5)]), (yyvsp[(3) - (5)].stmList)) ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1819 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.compoundstm) = new ast::CompoundStm((yylsp[(1) - (3)]), (yylsp[(3) - (3)]), (yyvsp[(2) - (3)].stmList)) ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1822 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stmList) = NULL ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1831 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_scopeStack.push(g_pScope);
							g_scopeStack.push(g_pScope2);
							g_scopeStack.push(g_lastScope);

/*

Below is for:

sometype classtype::memfun(sometype2 x);

sometype2 looks up in classtype scope


*/

							ASSERT(g_lastScope);
							if (g_lastScope->m_pNamespace && g_lastScope->m_pNamespace->AsClass())
							{
								ASSERT(g_lastScope->m_pNamespace->AsClass());

								ASSERT(g_pScope2 != g_lastScope);
								g_lastScope->m_pParentScope = g_pScope2;
								g_pScope2 = g_lastScope;
							}

						;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1861 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								g_lastScope = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope2 = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope = g_scopeStack.top();
								g_scopeStack.pop();

								//g_pScope2 = g_pScope;

								(yyval.declaration) = new ast::A_SimpleDeclaration((yyvsp[(1) - (6)].declspecList)? (yylsp[(1) - (6)]): (yylsp[(2) - (6)]), (yyvsp[(1) - (6)].declspecList), new ast::InitDeclaratorList(new ast::InitDeclarator(new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (6)]), ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].exp)), (yyvsp[(4) - (6)].paramDecls), NULL))), NULL));
								LOG("ctor/dtor\n");
							;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1877 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yyvsp[(1) - (3)].declspecList)? (yylsp[(1) - (3)]): (yylsp[(2) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList), (yyvsp[(2) - (3)].declspecList)), (yyvsp[(3) - (3)].initDeclaratorList));
							//	LOG("basic_type\n");
							;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1882 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yyvsp[(1) - (3)].declspecList)? (yylsp[(1) - (3)]): (yylsp[(2) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList), new ast::DeclSpecList((yyvsp[(2) - (3)].declspec), NULL)), (yyvsp[(3) - (3)].initDeclaratorList));
							//	LOG("elaborated\n");
							;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1887 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yyvsp[(1) - (3)].declspecList)? (yylsp[(1) - (3)]): (yylsp[(2) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList), new ast::DeclSpecList(new ast::A_NameType((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].exp)), NULL)), (yyvsp[(3) - (3)].initDeclaratorList));
							//	LOG("type\n");
							;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1906 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yylsp[(1) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList), (yyvsp[(2) - (3)].declspecList)), Reverse((yyvsp[(3) - (3)].initDeclaratorList)));
							//	LOG("basic_type\n");
							;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1911 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yylsp[(1) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList), new ast::DeclSpecList((yyvsp[(2) - (3)].declspec), NULL)), Reverse((yyvsp[(3) - (3)].initDeclaratorList)));
							//	LOG("elaborated\n");
							;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1916 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yylsp[(1) - (3)]), Reverse((yyvsp[(1) - (3)].declspecList), new ast::DeclSpecList(new ast::A_NameType((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].exp)), NULL)), Reverse((yyvsp[(3) - (3)].initDeclaratorList)));
							//	LOG("type\n");
							;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1921 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yylsp[(1) - (2)]), Reverse((yyvsp[(1) - (2)].declspecList)), new ast::InitDeclaratorList(new ast::InitDeclarator((yyvsp[(2) - (2)].declarator)), NULL));
							;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1925 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yylsp[(1) - (7)]), (yyvsp[(1) - (7)].declspecList), new ast::InitDeclaratorList(new ast::InitDeclarator(new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (7)]), ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId((yylsp[(2) - (7)]), (yyvsp[(3) - (7)].exp)), (yyvsp[(5) - (7)].paramDecls), NULL))), NULL));
							//	LOG("ctor\n");
							;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1930 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
								(yyval.declaration) = new ast::A_SimpleDeclaration((yylsp[(1) - (6)]), (yyvsp[(1) - (6)].declspecList), new ast::InitDeclaratorList(new ast::InitDeclarator(new ast::A_DirectDeclaratorDeclarator((yylsp[(1) - (6)]), ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].exp)), (yyvsp[(4) - (6)].paramDecls), NULL))), NULL));
							//	LOG("ctor\n");
							;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1950 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1951 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1954 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), NULL) ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 1955 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 1956 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONST), NULL) ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 1957 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 1958 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_VOLATILE), NULL) ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 1959 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_VOLATILE), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 1962 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = nullptr ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 1966 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONST), NULL) ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 1967 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_VOLATILE), NULL) ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 1968 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_INLINE), NULL) ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 1969 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_VIRTUAL), NULL) ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 1970 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_STATIC), NULL) ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 1971 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_TYPEDEF), NULL) ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 1972 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_CONSTEXPR), NULL) ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 1973 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_EXTERN), NULL) ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 1974 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_EXPLICIT), NULL) ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 1975 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (1)]), ast::A_FRIEND), NULL) ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 1976 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecExtModifier((yylsp[(1) - (4)]), Reverse((yyvsp[(3) - (4)].declspecExtList))), NULL) ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 1977 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 1978 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_VOLATILE), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 1979 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_INLINE), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 1980 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_VIRTUAL), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 1981 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_STATIC), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 1982 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_TYPEDEF), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 1983 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONSTEXPR), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 1984 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_EXTERN), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 1985 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_EXPLICIT), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 1986 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_FRIEND), (yyvsp[(1) - (2)].declspecList)) ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 1987 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecExtModifier((yylsp[(1) - (5)]), Reverse((yyvsp[(4) - (5)].declspecExtList))), (yyvsp[(1) - (5)].declspecList)) ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 1990 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecExt) = new ast::A_DeclSpecExt((yyvsp[(1) - (1)].id)) ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 1991 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecExt) = new ast::A_DeclSpecExt((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].num)) ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 1993 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecExtList) = new ast::A_DeclSpecExtList((yyvsp[(1) - (1)].declspecExt), nullptr); ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 1994 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecExtList) = new ast::A_DeclSpecExtList((yyvsp[(2) - (2)].declspecExt), (yyvsp[(1) - (2)].declspecExtList)); ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 1997 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecExtList) = nullptr ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2030 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2031 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_VOLATILE), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2032 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_TYPEDEF), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2033 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONSTEXPR), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 2034 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_INLINE), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2035 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_EXTERN), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2036 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_STATIC), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2037 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), nullptr) ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2038 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2039 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList((yyvsp[(1) - (1)].declspec), nullptr) ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2042 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_NameType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].exp)), nullptr) ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2046 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_CONST), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2047 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_VOLATILE), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2048 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_TYPEDEF), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2049 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_INLINE), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2050 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_EXTERN), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2051 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecModifier((yylsp[(1) - (2)]), ast::A_STATIC), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2052 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].simpleTypeSpec)), nullptr) ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2053 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList(new ast::A_DeclSpecBasicType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].simpleTypeSpec)), (yyvsp[(2) - (2)].declspecList)) ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2060 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.declspec) = new ast::A_NameType((yylsp[(1) - (2)]), (yyvsp[(2) - (2)].exp));
						;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2064 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							(yyval.declspec) = new ast::A_Class((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].classHead));
							g_pClass = nullptr;	// ??
						//	Do_elaborated_class((ast::A_Class*)$$)
						;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2071 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.memberSpec) = new ast::A_MemberDecl((yyvsp[(1) - (2)].declaration), (yyvsp[(2) - (2)].memberSpec)) ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2072 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.memberSpec) = new ast::A_MemberAccessSpec((yyvsp[(1) - (3)].accessSpec), (yyvsp[(3) - (3)].memberSpec)) ;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 2080 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = (yyvsp[(1) - (2)].declaration), Do(nullptr, (yyval.declaration)) ;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 2096 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = new ast::InitDeclaratorList((yyvsp[(1) - (1)].initDeclarator), nullptr) ;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2097 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = new ast::InitDeclaratorList((yyvsp[(3) - (3)].initDeclarator), (yyvsp[(1) - (3)].initDeclaratorList)) ;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2100 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = nullptr ;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 2104 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclarator) = new ast::InitDeclarator((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].initializer)) ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2105 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclarator) = new ast::InitDeclarator(new ast::A_BitfieldDeclarator((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp))); g_scopeStack2.pop(); ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2106 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclarator) = new ast::InitDeclarator(new ast::A_BitfieldDeclarator((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp))); g_scopeStack2.pop(); ;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 2109 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.memberSpec) = nullptr ;}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 2113 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initializer) = nullptr ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2114 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initializer) = new ast::Initializer((yyvsp[(2) - (2)].exp)); ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2119 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = nullptr ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2120 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = (yyvsp[(1) - (1)].initDeclaratorList);}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2123 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = new ast::InitDeclaratorList((yyvsp[(1) - (1)].initDeclarator), nullptr) ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2124 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = new ast::InitDeclaratorList((yyvsp[(3) - (3)].initDeclarator), (yyvsp[(1) - (3)].initDeclaratorList)) ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2139 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclarator) = new ast::InitDeclarator((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].initializer)) ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2140 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclarator) = new ast::InitDeclarator((yyvsp[(1) - (1)].declarator), nullptr) ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2143 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = new ast::InitDeclaratorList((yyvsp[(1) - (1)].initDeclarator), nullptr) ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2144 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = new ast::InitDeclaratorList((yyvsp[(3) - (3)].initDeclarator), (yyvsp[(1) - (3)].initDeclaratorList)) ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2147 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = nullptr ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2148 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclaratorList) = (yyvsp[(1) - (1)].initDeclaratorList);}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2151 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclarator) = new ast::InitDeclarator((yyvsp[(1) - (1)].declarator), nullptr) ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2152 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initDeclarator) = new ast::InitDeclarator((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].initializer)) ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2155 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initializer) = new ast::Initializer((yyvsp[(2) - (2)].exp)); ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2156 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.initializer) = new ast::Initializer((yyvsp[(3) - (4)].expList)); ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2164 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::InitClauseExp(Reverse((yyvsp[(2) - (4)].expList))); ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2165 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::InitClauseExp(NULL); ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2168 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(1) - (1)].exp), NULL); ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2169 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].expList)) ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2182 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.classHead) = new ast::A_ClassHead((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].classKey), (yyvsp[(2) - (3)].declspecList), (yyvsp[(3) - (3)].exp)); Do_class_specifier_head((yyval.classHead));;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2183 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.classHead) = new ast::A_ClassHead((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].classKey), (yyvsp[(2) - (3)].declspecList), (yyvsp[(3) - (3)].exp)); Do_class_specifier_head((yyval.classHead));;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2196 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = nullptr ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2200 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList((yyvsp[(1) - (1)].declspec), nullptr); ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2201 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspecList) = new ast::DeclSpecList((yyvsp[(2) - (2)].declspec), (yyvsp[(1) - (2)].declspecList)); ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2204 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declspec) = new ast::A_DeclSpecExtModifier((yylsp[(1) - (4)]), Reverse((yyvsp[(3) - (4)].declspecExtList))); ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2207 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp) ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2210 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = nullptr ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2214 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {	 (yyval.expList) = new ast::ExpressionList((yyvsp[(1) - (1)].exp), nullptr) ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2215 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(2) - (2)].exp), (yyvsp[(1) - (2)].expList)) ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2219 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_scopeStack.push(g_pScope);
							g_scopeStack.push(g_pScope2);

							ast::A_ClassDef* classdef = new ast::A_ClassDef((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].classHead), (yyvsp[(2) - (3)].baseSpecifierList), nullptr);
							g_classes.push(classdef);

							Do(classdef);

							g_pScope = g_pClass->m_pScope;
							g_pScope2 = g_pClass->m_pScope;

							g_pClassStack.push(g_pClass2);
							g_pClass2 = g_pClass;
						;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2235 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_pClass2 = g_pClassStack.top();
							g_pClassStack.pop();

							ast::A_ClassDef* classdef = g_classes.top();
							g_classes.pop();

							classdef->m_memberSpec = (yyvsp[(5) - (6)].memberSpec);

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

						//	ASSERT(g_pScope);
						//	g_pScope2 = g_pScope;
							(yyval.typespec) = classdef;

							ASSERT(g_scopeStack2.cont.size() == 0);
						;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2257 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_scopeStack.push(g_pScope);
							g_scopeStack.push(g_pScope2);

							ast::A_ClassDef* classdef = new ast::A_ClassDef((yylsp[(1) - (2)]), new ast::A_ClassHead((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].classKey), NULL, NULL), NULL, NULL);
							Do_class_specifier_head(classdef->m_head);

							g_classes.push(classdef);

							Do(classdef);

							g_pScope = g_pClass->m_pScope;
							g_pScope2 = g_pClass->m_pScope;

							g_pClassStack.push(g_pClass2);
							g_pClass2 = g_pClass;
						;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2275 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {
							g_pClass2 = g_pClassStack.top();
							g_pClassStack.pop();

							ast::A_ClassDef* classdef = g_classes.top();
							g_classes.pop();

							classdef->m_memberSpec = (yyvsp[(4) - (5)].memberSpec);

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

							ASSERT(g_pScope);
						//	g_pScope2 = g_pScope;

							(yyval.typespec) = classdef;

							ASSERT(g_scopeStack2.cont.size() == 0);
						;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2299 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.classKey) = ClassKey_class ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2300 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.classKey) = ClassKey_struct ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2301 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.classKey) = ClassKey_union ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2302 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.classKey) = ClassKey_interface ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2305 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.accessSpec) = AccessSpec_Private ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2306 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.accessSpec) = AccessSpec_Protected ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2307 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.accessSpec) = AccessSpec_Public ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2310 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.accessSpec) = AccessSpec_Unspecified ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2314 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typespec) = new ast::A_Enum((yylsp[(1) - (5)]), (yyvsp[(2) - (5)].id), NULL, (yyvsp[(4) - (5)].enumList)) ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2315 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typespec) = new ast::A_Enum((yylsp[(1) - (7)]), (yyvsp[(2) - (7)].id), (yyvsp[(4) - (7)].declspecList), (yyvsp[(6) - (7)].enumList)) ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2328 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.enumList) = new ast::EnumDefList((yyvsp[(1) - (1)].enumDef), NULL) ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2329 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.enumList) = (yyvsp[(1) - (2)].enumList) ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2330 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.enumList) = new ast::EnumDefList((yyvsp[(3) - (3)].enumDef), (yyvsp[(1) - (3)].enumList)) ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2333 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.enumList) = NULL ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2334 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.enumList) = (yyvsp[(1) - (1)].enumList) ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2337 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.enumDef) = new ast::EnumDefinition((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].id), NULL) ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2338 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.enumDef) = new ast::EnumDefinition((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2341 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_VOID ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2342 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_BOOL ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2343 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_CHAR ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2344 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_WCHAR_T ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2345 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_INT ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2346 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_SHORT ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2347 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_LONG ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2348 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_SIGNED ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2349 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_UNSIGNED ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2350 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_FLOAT ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2351 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A_DOUBLE ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2352 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A___INT8 ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2353 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A___INT16 ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 2354 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A___INT32 ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2355 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A___INT64 ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 2356 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A___FLOAT32 ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2357 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.simpleTypeSpec) = ast::A___FLOAT64 ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 2362 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (4)]), '[', (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].exp)) ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 2365 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::CallExp((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].expList)) ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 2373 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::InitExp((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].expList)) ;}
    break;

  case 443:

/* Line 1455 of yacc.c  */
#line 2374 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::InitBasicExp((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].simpleTypeSpec), (yyvsp[(3) - (4)].expList)) ;}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 2376 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_PostopExp((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].exp), '++') ;}
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 2377 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_PostopExp((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].exp), '--') ;}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 2379 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '.', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 2380 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '->', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 2382 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '.', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); g_scopeStack2.pop(); ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 2383 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '->', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); g_scopeStack2.pop(); ;}
    break;

  case 450:

/* Line 1455 of yacc.c  */
#line 2385 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::StaticCastExp((yyvsp[(3) - (7)].typeId), (yyvsp[(6) - (7)].exp)); ;}
    break;

  case 451:

/* Line 1455 of yacc.c  */
#line 2386 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::DynamicCastExp((yyvsp[(3) - (7)].typeId), (yyvsp[(6) - (7)].exp)); ;}
    break;

  case 452:

/* Line 1455 of yacc.c  */
#line 2387 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::ConstCastExp((yyvsp[(3) - (7)].typeId), (yyvsp[(6) - (7)].exp)); ;}
    break;

  case 453:

/* Line 1455 of yacc.c  */
#line 2388 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::ReinterpretCastExp((yyvsp[(3) - (7)].typeId), (yyvsp[(6) - (7)].exp)); ;}
    break;

  case 454:

/* Line 1455 of yacc.c  */
#line 2389 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::TypeidExp((yyvsp[(3) - (4)].exp)); ;}
    break;

  case 455:

/* Line 1455 of yacc.c  */
#line 2390 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::TypeidExp((yyvsp[(3) - (4)].typeId)); ;}
    break;

  case 456:

/* Line 1455 of yacc.c  */
#line 2393 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(1) - (1)].exp), NULL) ;}
    break;

  case 457:

/* Line 1455 of yacc.c  */
#line 2394 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].expList)) ;}
    break;

  case 458:

/* Line 1455 of yacc.c  */
#line 2397 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = NULL ;}
    break;

  case 460:

/* Line 1455 of yacc.c  */
#line 2401 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = NULL ;}
    break;

  case 462:

/* Line 1455 of yacc.c  */
#line 2405 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(1) - (1)].exp), NULL) ;}
    break;

  case 463:

/* Line 1455 of yacc.c  */
#line 2406 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList(new ast::TypeExp((yyvsp[(1) - (1)].typeId)), NULL) ;}
    break;

  case 464:

/* Line 1455 of yacc.c  */
#line 2407 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = new ast::ExpressionList((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].expList)) ;}
    break;

  case 466:

/* Line 1455 of yacc.c  */
#line 2411 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '++', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 467:

/* Line 1455 of yacc.c  */
#line 2412 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '--', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 468:

/* Line 1455 of yacc.c  */
#line 2413 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '*', (yyvsp[(2) - (2)].exp));}
    break;

  case 469:

/* Line 1455 of yacc.c  */
#line 2414 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '&', (yyvsp[(2) - (2)].exp));}
    break;

  case 470:

/* Line 1455 of yacc.c  */
#line 2415 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '+', (yyvsp[(2) - (2)].exp));}
    break;

  case 471:

/* Line 1455 of yacc.c  */
#line 2416 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '-', (yyvsp[(2) - (2)].exp));}
    break;

  case 472:

/* Line 1455 of yacc.c  */
#line 2417 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '!', (yyvsp[(2) - (2)].exp));}
    break;

  case 473:

/* Line 1455 of yacc.c  */
#line 2418 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '~', (yyvsp[(2) - (2)].exp));}
    break;

  case 474:

/* Line 1455 of yacc.c  */
#line 2420 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::SizeofExp((yyvsp[(2) - (2)].exp)) ;}
    break;

  case 475:

/* Line 1455 of yacc.c  */
#line 2421 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::SizeofTypeExp((yyvsp[(3) - (4)].typeId)) ;}
    break;

  case 477:

/* Line 1455 of yacc.c  */
#line 2423 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '::', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 479:

/* Line 1455 of yacc.c  */
#line 2425 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_UnopExp((yylsp[(1) - (2)]), '::', (yyvsp[(2) - (2)].exp)) ;}
    break;

  case 480:

/* Line 1455 of yacc.c  */
#line 2428 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::NewExp(Reverse((yyvsp[(2) - (4)].expList)), (yyvsp[(3) - (4)].typeId), Reverse((yyvsp[(4) - (4)].expList))); ;}
    break;

  case 481:

/* Line 1455 of yacc.c  */
#line 2432 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = (yyvsp[(2) - (3)].expList) ;}
    break;

  case 482:

/* Line 1455 of yacc.c  */
#line 2435 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = NULL ;}
    break;

  case 484:

/* Line 1455 of yacc.c  */
#line 2439 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.typeId) = new ast::A_TypeId((yyvsp[(1) - (1)].declspecList), NULL/*$2*/) ;}
    break;

  case 485:

/* Line 1455 of yacc.c  */
#line 2455 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = (yyvsp[(2) - (3)].expList) ;}
    break;

  case 486:

/* Line 1455 of yacc.c  */
#line 2458 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.expList) = NULL ;}
    break;

  case 488:

/* Line 1455 of yacc.c  */
#line 2462 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::DeleteExp((yyvsp[(2) - (2)].exp)) ;}
    break;

  case 489:

/* Line 1455 of yacc.c  */
#line 2463 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::DeleteExp((yyvsp[(4) - (4)].exp)) ;}
    break;

  case 491:

/* Line 1455 of yacc.c  */
#line 2467 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_CastExp((yyvsp[(2) - (4)].typeId), (yyvsp[(4) - (4)].exp)) ;}
    break;

  case 496:

/* Line 1455 of yacc.c  */
#line 2476 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '*', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 497:

/* Line 1455 of yacc.c  */
#line 2477 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '/', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 498:

/* Line 1455 of yacc.c  */
#line 2478 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '%', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 500:

/* Line 1455 of yacc.c  */
#line 2482 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '+', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 501:

/* Line 1455 of yacc.c  */
#line 2483 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '-', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 503:

/* Line 1455 of yacc.c  */
#line 2487 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '<<', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 504:

/* Line 1455 of yacc.c  */
#line 2488 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '>>', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 506:

/* Line 1455 of yacc.c  */
#line 2492 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '<', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 507:

/* Line 1455 of yacc.c  */
#line 2493 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '>', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 508:

/* Line 1455 of yacc.c  */
#line 2494 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '<=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 509:

/* Line 1455 of yacc.c  */
#line 2495 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '>=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 511:

/* Line 1455 of yacc.c  */
#line 2499 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '==', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 512:

/* Line 1455 of yacc.c  */
#line 2500 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '!=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 514:

/* Line 1455 of yacc.c  */
#line 2504 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '&', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 516:

/* Line 1455 of yacc.c  */
#line 2508 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '^', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 518:

/* Line 1455 of yacc.c  */
#line 2512 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '|', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 520:

/* Line 1455 of yacc.c  */
#line 2516 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '&&', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 522:

/* Line 1455 of yacc.c  */
#line 2520 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '||', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 524:

/* Line 1455 of yacc.c  */
#line 2524 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (5)]), '?', (yyvsp[(1) - (5)].exp), ast::A_BinopExp((yylsp[(3) - (5)]), ':', (yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].exp))) ;}
    break;

  case 525:

/* Line 1455 of yacc.c  */
#line 2527 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '=' ;}
    break;

  case 526:

/* Line 1455 of yacc.c  */
#line 2528 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '+=' ;}
    break;

  case 527:

/* Line 1455 of yacc.c  */
#line 2529 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '-=' ;}
    break;

  case 528:

/* Line 1455 of yacc.c  */
#line 2530 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '|=' ;}
    break;

  case 529:

/* Line 1455 of yacc.c  */
#line 2531 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '^=' ;}
    break;

  case 530:

/* Line 1455 of yacc.c  */
#line 2532 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '&=' ;}
    break;

  case 531:

/* Line 1455 of yacc.c  */
#line 2533 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '*=' ;}
    break;

  case 532:

/* Line 1455 of yacc.c  */
#line 2534 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '/=' ;}
    break;

  case 533:

/* Line 1455 of yacc.c  */
#line 2535 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '%=' ;}
    break;

  case 534:

/* Line 1455 of yacc.c  */
#line 2536 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '<<=' ;}
    break;

  case 535:

/* Line 1455 of yacc.c  */
#line 2537 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.num) = '>>=' ;}
    break;

  case 537:

/* Line 1455 of yacc.c  */
#line 2541 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), (yyvsp[(2) - (3)].num), (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 539:

/* Line 1455 of yacc.c  */
#line 2545 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = NULL ;}
    break;

  case 541:

/* Line 1455 of yacc.c  */
#line 2549 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = new ast::ThrowExp((yyvsp[(2) - (2)].exp)) ;}
    break;

  case 543:

/* Line 1455 of yacc.c  */
#line 2553 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), ',', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 544:

/* Line 1455 of yacc.c  */
#line 2556 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = NULL ;}
    break;

  case 547:

/* Line 1455 of yacc.c  */
#line 2563 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = NULL ;}
    break;

  case 550:

/* Line 1455 of yacc.c  */
#line 2570 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '<', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 2572 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '<=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 2573 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '>=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 2577 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '==', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 2578 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '!=', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 2582 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '&', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 2586 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '^', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 2590 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (3)]), '|', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)) ;}
    break;

  case 567:

/* Line 1455 of yacc.c  */
#line 2602 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.exp) = ast::A_BinopExp((yylsp[(1) - (5)]), '?', (yyvsp[(1) - (5)].exp), ast::A_BinopExp((yylsp[(3) - (5)]), ':', (yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].exp))) ;}
    break;

  case 569:

/* Line 1455 of yacc.c  */
#line 2608 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateArgumentList) = new ast::A_TemplateArgumentList((yyvsp[(1) - (1)].templateArgument), nullptr) ;}
    break;

  case 570:

/* Line 1455 of yacc.c  */
#line 2609 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateArgumentList) = new ast::A_TemplateArgumentList((yyvsp[(3) - (3)].templateArgument), (yyvsp[(1) - (3)].templateArgumentList)) ;}
    break;

  case 571:

/* Line 1455 of yacc.c  */
#line 2612 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateArgumentList) = nullptr ;}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 2616 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateArgument) = new ast::A_TemplateArgument(NULL, (yyvsp[(1) - (1)].exp)) ;}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 2617 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.templateArgument) = new ast::A_TemplateArgument((yyvsp[(1) - (1)].typeId), nullptr) ;}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 2620 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.id) = NULL ;}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 2627 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.baseSpecifierList) = Reverse((yyvsp[(2) - (2)].baseSpecifierList)) ;}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 2630 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.baseSpecifierList) = NULL ;}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 2634 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.baseSpecifierList) = new ast::A_BaseSpecifierList((yyvsp[(1) - (1)].baseSpecifier), NULL) ;}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 2635 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.baseSpecifierList) = new ast::A_BaseSpecifierList((yyvsp[(3) - (3)].baseSpecifier), (yyvsp[(1) - (3)].baseSpecifierList)) ;}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 2642 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {	(yyval.baseSpecifier) = new ast::A_BaseSpecifier((yyvsp[(1) - (1)].exp), AccessSpec_Unspecified, 0); ;}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 2643 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {	(yyval.baseSpecifier) = new ast::A_BaseSpecifier((yyvsp[(2) - (2)].exp), (yyvsp[(1) - (2)].accessSpec), 0);	;}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 2644 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {	(yyval.baseSpecifier) = new ast::A_BaseSpecifier((yyvsp[(3) - (3)].exp), (yyvsp[(2) - (3)].accessSpec), 1);	;}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 2645 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {	(yyval.baseSpecifier) = new ast::A_BaseSpecifier((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].accessSpec), 2);	;}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 2650 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = NULL ;}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 2664 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.declaration) = new ast::AsmDefinition((yylsp[(1) - (5)]), (yyvsp[(3) - (5)].string_literal)) ;}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 2667 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::CaseStm((yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].stm)) ;}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 2668 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::DefaultStm((yyvsp[(3) - (3)].stm)) ;}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 2669 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {g_scopeStack2.pop();;}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 2669 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::LabelStm((yyvsp[(1) - (5)].id), (yyvsp[(5) - (5)].stm)); ;}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 2670 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    {g_scopeStack2.pop();;}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 2670 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::LabelStm((yyvsp[(1) - (5)].id), (yyvsp[(5) - (5)].stm)); ;}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 2673 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::ContinueStm() ;}
    break;

  case 604:

/* Line 1455 of yacc.c  */
#line 2674 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::BreakStm() ;}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 2675 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::GotoStm((yyvsp[(2) - (3)].id)) ;}
    break;

  case 606:

/* Line 1455 of yacc.c  */
#line 2679 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::IfStm((yyvsp[(3) - (5)].cond), (yyvsp[(5) - (5)].stm), NULL) ;}
    break;

  case 607:

/* Line 1455 of yacc.c  */
#line 2680 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::IfStm((yyvsp[(3) - (7)].cond), (yyvsp[(5) - (7)].stm), (yyvsp[(7) - (7)].stm)) ;}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 2681 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::SwitchStm((yyvsp[(3) - (5)].cond), (yyvsp[(5) - (5)].stm)) ;}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 2684 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.cond) = new ast::Condition((yyvsp[(1) - (1)].exp)) ;}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 2685 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.cond) = new ast::Condition((yyvsp[(1) - (4)].declspecList), (yyvsp[(2) - (4)].declarator), (yyvsp[(4) - (4)].exp)); ;}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 2688 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::WhileStm((yylsp[(1) - (5)]), (yylsp[(5) - (5)]), (yyvsp[(3) - (5)].cond), (yyvsp[(5) - (5)].stm)) ;}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 2689 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::DoWhileStm((yyvsp[(2) - (7)].stm), (yyvsp[(5) - (7)].exp)) ;}
    break;

  case 613:

/* Line 1455 of yacc.c  */
#line 2690 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::ForStm(NULL, (yyvsp[(4) - (8)].exp), (yyvsp[(6) - (8)].exp), (yyvsp[(8) - (8)].stm)) ;}
    break;

  case 614:

/* Line 1455 of yacc.c  */
#line 2691 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::ForStm(new ast::A_ExpOrDecl((yyvsp[(3) - (9)].exp), NULL), (yyvsp[(5) - (9)].exp), (yyvsp[(7) - (9)].exp), (yyvsp[(9) - (9)].stm)) ;}
    break;

  case 615:

/* Line 1455 of yacc.c  */
#line 2692 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::ForStm(new ast::A_ExpOrDecl(NULL, new ast::A_SimpleDeclaration((yylsp[(3) - (10)]), (yyvsp[(3) - (10)].declspecList), Reverse((yyvsp[(4) - (10)].initDeclaratorList)))), (yyvsp[(6) - (10)].exp), (yyvsp[(8) - (10)].exp), (yyvsp[(10) - (10)].stm)) ;}
    break;

  case 616:

/* Line 1455 of yacc.c  */
#line 2695 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::A_DeclarationStm(new ast::A_SimpleDeclaration((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].declspecList), Reverse((yyvsp[(2) - (3)].initDeclaratorList)))); ;}
    break;

  case 617:

/* Line 1455 of yacc.c  */
#line 2696 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::A_DeclarationStm((yyvsp[(1) - (1)].declaration)) ;}
    break;

  case 618:

/* Line 1455 of yacc.c  */
#line 2700 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::A_ExpStm((yyvsp[(1) - (2)].exp)) ;}
    break;

  case 619:

/* Line 1455 of yacc.c  */
#line 2703 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::ReturnStm() ;}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 2704 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stm) = new ast::ReturnStm((yyvsp[(2) - (3)].exp)) ;}
    break;

  case 621:

/* Line 1455 of yacc.c  */
#line 2707 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stmList) = new ast::A_StmList((yyvsp[(1) - (1)].stm), NULL) ;}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 2708 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"
    { (yyval.stmList) = new ast::A_StmList((yyvsp[(1) - (2)].stm), (yyvsp[(2) - (2)].stmList)) ;}
    break;



/* Line 1455 of yacc.c  */
#line 7689 "cpp_exp_parse.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 2821 "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\src\\CodeComp\\cpp_exp_parse.y"



