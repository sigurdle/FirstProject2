%{

//#define YYERROR_VERBOSE

#define YYMAXDEPTH	80000

struct PP_TokenList;

extern PP_TokenList* tlist;

bool bLastTok = false;

int GetString(int delimiter, bool bWide/*, CToken& token*/)
{
	int line = pPP2->m_pFile->m_line;

	IO::StringWriter strbuilder;

	int c2;
	while (!pPP2->_eof())
	{
		//CToken* ptok = pPP->GetToken4();
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
		strbuilder << (char)c2;
	}

	if (c2 != delimiter)
	{
		char msg[256];
		sprintf_s(msg, "expected end of string, started on line(%d)", line);
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

	cpp_lval.string_literal = dynamic_cast<StringA*>(strbuilder.str().m_stringObject);
	cpp_lval.string_literal->IncRef();

	return STRING_LITERAL;
}

static int cpp_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/)
{
	if (!bLastTok)
		pPP2->_GetToken();
	else
		bLastTok = false;

	yylloc.first_line = pPP2->m_pFile->m_line;
	yylloc.first_column = pPP2->m_pFile->m_column;
	yylloc.filename = /*dynamic_cast<StringA*>*/(pPP2->m_pFile->m_filepath.m_stringObject);

#if 0
	while (pPP2->curtokpp->type == CToken::tok_space ||
		(pPP2->curtokpp->type == CToken::tok_symbol && pPP2->curtokpp->symbol == '\n'))
	{
		yylloc.first_line = pPP2->m_pFile->m_line;
		pPP2->GetToken();
	//	yylpos.first_line = pPP2->m_location.m_line;
	}
#endif

	if (pPP2->curtokpp->GetKind() == CToken::tok_ident)
	{
		kwmap::iterator it = kwm.find(String(pPP2->curtokpp->m_astr));
		if (it != kwm.end())
		{
			return (*it).second;
		}
		else
		{
			cpp_lval.id = pPP2->curtokpp->m_astr;//ident.ident;
			return IDENTIFIER;
		}

		/*
		int kw;
		if (kwm.Lookup(ckw(pPP2->curtokpp->ident.ident), kw))
			return kw;
		else
		{
			cpp_lval.id = pPP2->curtokpp->ident.ident;
			return IDENTIFIER;
		}
		*/
	}
	else if (pPP2->curtokpp->GetKind() == CToken::tok_integer)
	{
		cpp_lval.num = pPP2->curtokpp->intval;
		return INTEGER_LITERAL;
	}
	else if (pPP2->curtokpp->GetKind() == CToken::tok_double)
	{
		cpp_lval.double_num = pPP2->curtokpp->double64;
		return DOUBLE_LITERAL;
	}
	else if (pPP2->curtokpp->GetKind() == CToken::tok_string_literal)
	{
		cpp_lval.string_literal = pPP2->curtokpp->m_astr;
		return STRING_LITERAL;
	}
	else if (pPP2->curtokpp->GetKind() == CToken::tok_import)
	{
		cpp_lval.string_literal = pPP2->curtokpp->m_astr;
		return IMPORT_KW;
	}
	else if (pPP2->curtokpp->GetKind() == CToken::tok_char_literal)
	{
		cpp_lval.num = pPP2->curtokpp->intval;
		return CHAR_LITERAL;
	}
	else if (pPP2->curtokpp->GetKind() == CToken::tok_char ||
				pPP2->curtokpp->GetKind() == CToken::tok_symbol)
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
		else if (pPP2->curtokpp->symbol == '^')
		{
			return BITXOR;
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
			return IDENTIFIER;
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

ast::A_Stm* stmtMerge (YYSTYPE& x0, YYSTYPE& x1);
//ast::A_Declaration* Merge (YYSTYPE& x0, YYSTYPE& x1);

//ast::A_TemplateArgument* template_argument_merge (YYSTYPE& x0, YYSTYPE& x1);

ast::DeclarationList* translation_unit;

ast::Expression2List* g_primlist;

//ast::A_Type* gType;


     %}

//%glr-parser
%locations
%name-prefix="cpp_"

%union {
__int64 num;
double double_num;
System::StringA* id;
System::StringA* string_literal;
ast::A_ClassKey classKey;
ast::A_ClassHead* classHead;
AccessSpec accessSpec;
ast::DeclSpecifierKeyword declSpecifierKeyword;
ast::A_MemberSpec* memberSpec;
//ast::A_Condition* cond;
ast::Expression* exp;
ast::ExpressionList* expList;

ast::Expression2* exp2;
ast::Expression2List* exp2List;

ast::A_Stm* stm;
ast::CompoundStm* compoundstm;
ast::A_StmList* stmList;
ast::A_Declarator* declarator;
ast::A_DirectDeclarator* directDeclarator;
ast::Declaration* declaration;
ast::DeclarationList* declarationList;
ast::A_DeclaratorList* declaratorList;
//ast::A_TypeSpec* typespec;
ast::A_TypeId* typeId;
ast::A_TypeIdList* typeIdList;
/*ast::A_TypeSpecList* typespecList;*/

ast::TemplateParameter* templateParameter;
ast::TemplateParameterList* templateParameterList;

//ast::A_TemplateArgument* templateArgument;
ast::A_TemplateArgumentList* templateArgumentList;

ast::A_DeclSpec* declspec;
ast::A_DeclSpec* typespec;
ast::DeclSpecList* declspecList;
ast::ParameterDeclarations* paramDecls;
ast::EnumDefinition* enumDef;
ast::EnumDefList* enumList;
ast::A_BaseSpecifierList* baseSpecifierList;
ast::BasicTypeSpecifier simpleTypeSpec;
}

%token EXP_TOKEN
%token DECLS_TOKEN

%token <id> IDENTIFIER
%token <id> identifier_lparen

%token PLUSPLUS
%token MINUSMINUS
%token ARROW
%token EQUAL
%token NOT_EQUAL
%token ASSIGN_PLUS
%token ASSIGN_MINUS
%token ASSIGN_OR
%token ASSIGN_XOR
%token ASSIGN_AND
%token ASSIGN_MUL
%token ASSIGN_DIV
%token ASSIGN_MOD
%token ASSIGN_LSHIFT
%token ASSIGN_RSHIFT
%token LEQ
%token GEQ
%token STAR
%token BITAND
%token BITOR
%token BITXOR
%token LAND
%token LOR
%token DOT_STAR
%token ARROW_STAR

%token NAMESPACE_KW
%token USING_KW
%token EXTERN_KW
%token IF_KW
%token ELSE_KW
%token SWITCH_KW
%token CASE_KW
%token DEFAULT_KW
%token GOTO_KW
%token BREAK_KW
%token CONTINUE_KW
%token FOR_KW
%token DO_KW
%token WHILE_KW
%token CONST_KW
%token VOLATILE_KW
%token TYPEDEF_KW
%token TYPENAME_KW
%token ENUM_KW
%token CLASS_KW
%token STRUCT_KW
%token UNION_KW
%token PRIVATE_KW
%token PROTECTED_KW
%token PUBLIC_KW
%token AUTO_KW
%token REGISTER_KW
%token STATIC_KW
%token MUTABLE_KW
%token INLINE_KW
%token VIRTUAL_KW
%token EXPLICIT_KW
%token FRIEND_KW
%token FALSE_KW
%token TRUE_KW
%token STATIC_ASSERT_KW
%token STATIC_CAST_KW
%token REINTERPRET_CAST_KW
%token DYNAMIC_CAST_KW
%token CONST_CAST_KW
%token RETURN_KW
%token TRY_KW
%token THROW_KW
%token CATCH_KW
%token CHAR_KW
%token WCHAR_T_KW
%token BOOL_KW
%token SHORT_KW
%token INT_KW
%token INTERFACE_KW
%token LONG_KW
%token SIGNED_KW
%token UNSIGNED_KW
%token FLOAT_KW
%token DOUBLE_KW
%token VOID_KW
%token TEMPLATE_KW
%token EXPORT_KW
%token NULLPTR_KW
%token CONSTEXPR_KW
%token DECLTYPE_KW
%token __FLOAT32_KW
%token __FLOAT64_KW
%token __INT8_KW
%token __INT16_KW
%token __INT32_KW
%token __INT64_KW
%token __INT128_KW
%token __CDECL_KW
%token __STDCALL_KW
%token __FASTCALL_KW
%token __DECLSPEC_KW
%token __ASM_KW
//%token __SAVEDS_KW
//%token __INTERRUPT_KW
//%token __CHIP_KW

%token LSHIFT
%token RSHIFT
%token TWO_COLON
%token THREE_DOTS
%token NEW_KW
%token DELETE_KW
%token OPERATOR_KW
%token SIZEOF_KW
%token TYPEID_KW
%token <string_literal> STRING_LITERAL
%token <string_literal> LSTRING_LITERAL
%token <num> CHAR_LITERAL
%token <num> INTEGER_LITERAL
%token <double_num> DOUBLE_LITERAL

%token <string_literal> IMPORT_KW

%token <id> TEMPLATE_NAME

%token ATTRIBUTE_KW

%token <exp> THIS_KW

%type <exp2> prim
%type <exp2List> primlist
%type <exp2List> primlist_opt

%type <exp2> template_argument_prim
%type <exp2List> template_argument_primlist

%type <exp2> case_prim
%type <exp2List> case_primlist

%type <num> ptr_operator
%type <num> cc_qualifier

%type <exp> base_specifier
%type <id> class_name
%type <baseSpecifierList> base_specifier_list
%type <baseSpecifierList> base_clause
%type <baseSpecifierList> base_clause_opt

%type <id> identifier_opt
%type <exp> id

%type <simpleTypeSpec> basic_type

%type <exp2List> template_argument
%type <templateArgumentList> template_argument_list
%type <templateArgumentList> template_argument_list_opt

//%type <exp> qualified_id
%type <exp> unqualified_id
%type <exp> nested_name_specifier
%type <exp> base_class_name

%type <exp> conversion_function_id

%type <exp> operator_function_id

%type <num> _operator

%type <templateParameterList> template_parameter_list
%type <templateParameter> template_parameter
%type <templateParameter> type_parameter
%type <templateParameter> template_parameter_declaration
%type <declspecList> template_parameter_declaration1
%type <declspecList> template_parameter_declaration2

%type <enumList> enumerator_list
%type <enumList> enumerator_list_opt
%type <enumDef> enumerator_definition
%type <exp> constant_expression
%type <exp> constant_expression_opt
%type <exp> expression
%type <exp> conditional_expression
%type <exp> assignment_expression
%type <exp> logical_or_expression
%type <exp> logical_and_expression
%type <exp> inclusive_or_expression
%type <exp> exclusive_or_expression
%type <exp> and_expression
%type <exp> equality_expression
%type <exp> relational_expression
%type <exp> shift_expression
%type <exp> additive_expression
%type <exp> multiplicative_expression
%type <exp> pm_expression
%type <exp> cast_expression
%type <exp> unary_expression
%type <exp> literal

%type <classHead> class_head

//%type <exp> id_expression
%type <exp> postfix_expression
%type <exp> primary_expression

%type <exp> scoped_id
%type <exp> scoped_id2
%type <exp> nested_id

%type <expList> expression_list
%type <expList> expression_list_opt;

//%type <id> class_name;

%type <declarator> declarator
//%type <declarator> sub_declarator
%type <declarator> init_declarator
%type <directDeclarator> direct_declarator
/*
%type <directDeclarator> direct_declarator1
%type <directDeclarator> direct_declarator2
*/
//%type <directDeclarator> sub_direct_declarator
%type <declaratorList> init_declarator_list
%type <declaratorList> init_declarator_list_opt
%type <declarator> abstract_declarator
%type <declarator> abstract_declarator_opt
%type <directDeclarator> direct_abstract_declarator
%type <directDeclarator> direct_abstract_declarator_opt

%type <typeId> parameter_declaration
%type <typeIdList> parameter_declaration_list
%type <typeIdList> parameter_declaration_list_opt
%type <paramDecls> parameter_declaration_clause

//%type <declspecList> parameter_declaration_decl

//%type <exp> declarator_id;

%type <declSpecifierKeyword> storage_class_specifier
%type <declSpecifierKeyword> function_specifier
%type <declspec> decl_specifier
//%type <declspec> decl_specifier2
//%type <declspec> decl_specifier_with_type
//%type <declspec> decl_specifier_with_class
%type <declspecList> cv_qualifier_seq
%type <declspecList> cv_qualifier_seq_opt
//%type <declspecList> decl_specifier_seq_with_type
//%type <declspecList> decl_specifier_seq_with_class
//%type <declspecList> decl_specifier_seq_with_class_opt



%type <declspecList> simple_type_specifier_seq

//%type <declspec> decl_specifier_seq_except_type
//%type <declspec> decl_specifier_seq_except_type_seq
/*%type <declspec> decl_specifier2*/
%type <declspecList> decl_specifier_seq
//%type <declspecList> decl_specifier_seq2
//%type <declspecList> decl_specifier_seq_opt
/*%type <declspecList> decl_specifier_seq2_opt*/

%type <accessSpec> access_specifier
%type <accessSpec> access_specifier_opt

%type <memberSpec> member_specification
%type <memberSpec> member_specification_opt
%type <declaration> member_declaration
%type <declaration> member_declaration_decl
//%type <declspecList> member_declaration_decl2
//%type <declspecList> member_declaration_decl3
%type <declaratorList> member_declarator_list
%type <declaratorList> member_declarator_list_opt
%type <declarator> member_declarator

%type <declarator> conversion_declarator
%type <declarator> conversion_declarator_opt

%type <declspecList> conversion_type_id
%type <declspecList> conversion_type_id2

%type <typespec> type_specifier
//%type <typespec> type_specifier2
//%type <typespec> elaborated_type_specifier
%type <typespec> enum_specifier
%type <typespec> class_specifier
//%type <typespec> class_head
%type <typespec> simple_type_specifier2
%type <typespec> cv_qualifier

%type <typeId> type_id

%type <stm> statement
%type <stm> labeled_statement
%type <stm> selection_statement
%type <stm> iteration_statement
%type <stm> return_statement
%type <stm> jump_statement
%type <stm> expression_or_declaration
%type <compoundstm> compound_statement
%type <stm> expression_statement
%type <stm> declaration_statement
%type <compoundstm> function_body

%type <stmList> statement_seq

%type <exp2List> condition
%type <exp2List> condition_opt
%type <declaration> declaration;
%type <declaration> linkage_specification
%type <declaration> namespace_definition
%type <declaration> template_declaration
%type <declaration> explicit_specialization
%type <declaration> using_declaration

%type <declaration> using_directive

%type <declaration> named_namespace_definition
%type <declaration> function_definition
/*%type <declaration> function_definition2*/
%type <declaration> block_declaration
%type <declaration> simple_declaration
%type <declspecList> simple_declaration2
%type <declspecList> simple_declaration3
%type <declspecList> simple_declaration4

%type <declspec> elaborate_type


%type <declspecList> type_id1
%type <declspecList> type_id2
%type <declspecList> type_id3

/*
%type <declspecList> function_definition2
%type <declspecList> function_definition3
%type <declspecList> function_definition4
*/

%type <declspecList> parameter_declaration1
%type <declspecList> parameter_declaration3
%type <declspecList> parameter_declaration4

%type <declarationList> declaration_seq;
%type <declarationList> declaration_seq_opt;

//%type <declarationList> translation_unit;

%type <exp2List> translation_unit;

%type <classKey> class_key;

%token NTA
%token YTA
%token YTT
%token NTY
%token YTY
%token CTORN

%nonassoc SHIFT_THERE
%nonassoc TWO_COLON ELSE_KW

     %%

translation_unit:

		primlist { $$ = $1; g_primlist = $$;	}

		/*	declaration_seq_opt {	$$ = $1; translation_unit = $$;	}
*/
;

/* Expressions */

literal: FALSE_KW	 { $$ = ast::A_BoolExp(0) }
		|	TRUE_KW	 { $$ = ast::A_BoolExp(1) }
		|	INTEGER_LITERAL { $$ = ast::A_Int32Exp($1) }
		|	DOUBLE_LITERAL { $$ = ast::A_DoubleExp($1) }
		|	STRING_LITERAL { $$ = ast::A_StringExp($1) }
		|	LSTRING_LITERAL { $$ = ast::A_LStringExp($1) }
		|	CHAR_LITERAL { $$ = new ast::A_CharLiteralExp($1) }
;

primary_expression:	literal
						|	THIS_KW
						|	'(' expression ')' { $$ = $2}
						|	scoped_id
;

/*
id_expression:	IDENTIFIER { $$ = ast::A_IdExp($1) }
				|	qualified_id
;
*/

operator_function_id:	OPERATOR_KW _operator { $$ = ast::A_OperatorExp(@1, $2) }
								/*OPERATOR_KW _operator '<' template-argument-listopt '>'*/
;

_operator:	'~' { $$ = '~' }
			|	NEW_KW		{ $$ = 'new' }
			|	DELETE_KW	{ $$ = 'del' }
			|	'=' { $$ = '=' }
			|	'!' { $$ = '!' }
			|	'>' { $$ = '>' }
			|	'<' { $$ = '<' }
			|	'+' { $$ = '+' }
			|	'-' { $$ = '-' }
			|	STAR { $$ = '*' }
			|	'/' { $$ = '/' }
			|	'%' { $$ = '%' }
			|	BITOR { $$ = '|' }
			|	BITAND { $$ = '&' }
			|	BITXOR { $$ = '^' }
			|	EQUAL { $$ = '==' }
			|	NOT_EQUAL { $$ = '!=' }
			|	LEQ { $$ = '<=' }
			|	GEQ { $$ = '>=' }
			|	PLUSPLUS { $$ = '++' }
			|	MINUSMINUS { $$ = '--' }
			|	LSHIFT { $$ = '<<' }
			|	RSHIFT { $$ = '>>' }
			|	ASSIGN_PLUS { $$ = '+=' }
			|	ASSIGN_MINUS { $$ = '-=' }
			|	ASSIGN_MUL { $$ = '*=' }
			|	ASSIGN_DIV { $$ = '/=' }
			|	ASSIGN_MOD { $$ = '%=' }
			|	ASSIGN_LSHIFT { $$ = '<<=' }
			|	ASSIGN_RSHIFT { $$ = '>>=' }
			|	ASSIGN_OR { $$ = '|=' }
			|	ASSIGN_AND { $$ = '&=' }
			|	ASSIGN_XOR { $$ = '^=' }
			|	ARROW { $$ = '->' }
			|	'[' ']' { $$ = '[]' }
			|	'(' ')' { $$ = '()' }
;

template_opt:	/*empty*/
				|	TEMPLATE_KW
;

unqualified_id:	nested_name_specifier	{ /*$$ = ast::A_IdExp($1)*/ }
					|	operator_function_id
				/*	|	conversion_function_id*/
				/*	|	'~' IDENTIFIER */
				/*	|	template_id {}*/
;

/*
qualified_id:	TWO_COLON nested_name_specifier templateopt unqualified_id {}
				|	nested_name_specifier template_opt unqualified_id { / }

				|	TWO_COLON IDENTIFIER {}
				|	TWO_COLON operator_function_id {}
			 :: template-id
;
*/

/*
qualified_id:	nested_name_specifier templateopt unqualified_id {}
				|	TWO_COLON IDENTIFIER {}
	:: operator-function-id
	:: template-id
;
*/

TWO_COLON_opt:	/*empty*/
				|	TWO_COLON
;

conversion_function_id:	OPERATOR_KW conversion_type_id conversion_declarator_opt	{ $$ = ast::A_ConversionExp(new ast::A_TypeId($2, $3)) }
;

conversion_type_id:	CONST_KW conversion_type_id { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
						|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
						|	basic_type conversion_type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
						|	scoped_id2	{ $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), NULL) }
;

conversion_type_id2:	CONST_KW	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
						|	CONST_KW conversion_type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
						|	basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
						|	basic_type conversion_type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
;

conversion_declarator:	ptr_operator conversion_declarator_opt	{ $$ = new ast::A_PtrDeclarator($1, $2) }
;

conversion_declarator_opt:
								|	conversion_declarator
;

/*
nested_name_specifier:	type_name TWO_COLON nested_name_specifier_opt {  }
							|	type_name TWO_COLON TEMPLATE_KW nested_name_specifier
;
*/

id:	IDENTIFIER	%prec SHIFT_THERE { $$ = ast::A_TemplateId($1, NULL) }      /* Maximise length */
	|	IDENTIFIER '<' template_argument_list_opt '>' { $$ = ast::A_TemplateId($1, $3) }
;

/*
id_scope:	id TWO_COLON
;
*/

nested_id:	id  %prec SHIFT_THERE   {	 $$ = ast::A_BinopExp(@1, '::', $1, NULL) }    /* Maximise length */
			|	operator_function_id		{	 $$ = ast::A_BinopExp(@1, '::', $1, NULL) }
			|	'~' IDENTIFIER { $$ = ast::A_BinopExp(@1, '::', ast::A_UnopExp(@1, '~', ast::A_IdExp($2)), NULL) }
		/*	|	nested_id TWO_COLON id	{	 $$ = ast::A_BinopExp(@1, '::', $1, $3) } */
			|	id TWO_COLON nested_id	{	 $$ = ast::A_BinopExp(@1, '::', $1, $3) }
			|	id TWO_COLON STAR nested_id	{ $$ = NULL }	// TODO
;

global_scope: TWO_COLON
;

scoped_id:	nested_id
			|	global_scope nested_id { $$ = $2 }
			|	conversion_function_id { $$ = ast::A_BinopExp(@1, '::', $1, NULL) }
;

scoped_id2:	nested_id
			|	global_scope nested_id
;

nested_name_specifier:	IDENTIFIER TWO_COLON
						/*	|	id_scope nested_name_specifier*/
;

nested_name_specifier_opt:	/*empty*/
								|	nested_name_specifier
;

postfix_expression:	primary_expression	%dprec 1

						|	postfix_expression '[' expression ']' %dprec 2{  } 
						|	postfix_expression '(' expression_list_opt ')'	%dprec 2		{ $$ = ast::A_CallExp(@1, $1, $3) }
						|	basic_type '(' expression_list_opt ')'	%dprec 2	
						|	postfix_expression PLUSPLUS { $$ = NULL }	%dprec 2
						|	postfix_expression MINUSMINUS { $$ = NULL }	%dprec 2
						|	postfix_expression '.' /*template_opt*/ scoped_id %dprec 2 {  }
						|	postfix_expression ARROW /*template_opt*/ scoped_id %dprec 2 {  }						
						|	STATIC_CAST_KW '<' type_id '>' '(' expression ')'
						|	DYNAMIC_CAST_KW '<' type_id '>' '(' expression ')'
;

expression_list:	assignment_expression %dprec 1{ $$ = new ast::A_ExpList($1, NULL) }
					|	expression_list ',' assignment_expression %dprec 2 { $$ = new ast::A_ExpList($3, $1) }
;

expression_list_opt:	/*empty*/ { $$ = NULL }
						|	expression_list
;

unary_expression:	postfix_expression	 %dprec 1
					|	PLUSPLUS cast_expression  %dprec 2{ $$ = ast::A_UnopExp(@1, '++', $2) }
					|	MINUSMINUS cast_expression   %dprec 2{ $$ = ast::A_UnopExp(@1, '--', $2) }
					|	STAR cast_expression  %dprec 2{ $$ = ast::A_UnopExp(@1, '*', $2)}
					|	BITAND cast_expression  %dprec 2{ $$ = ast::A_UnopExp(@1, '&', $2)}
					|	'+' cast_expression  %dprec 2{ $$ = ast::A_UnopExp(@1, '+', $2)}
					|	'-' cast_expression  %dprec 2{ $$ = ast::A_UnopExp(@1, '-', $2)}
					|	'!' cast_expression  %dprec 2{ $$ = ast::A_UnopExp(@1, '!', $2)}
				/*	|	'~' cast_expression %dprec 2 { $$ = ast::A_UnopExp(@1, '~', $2)} */
					|	SIZEOF_KW unary_expression %dprec 2
					|	SIZEOF_KW '(' type_id ')' %dprec 3
					|	new_expression new_declarator_opt new_initializer_opt	
					|	delete_expression %dprec 2
;

new_expression:	TWO_COLON_opt NEW_KW new_placement_opt new_type_id /*new_initializer_opt*/
				/*	|	TWO_COLON_opt NEW_KW new_placement_opt '(' type_id ')' new_initializer_opt*/
;

new_placement:	'(' expression_list ')'
;

new_placement_opt:
						|	new_placement
;

new_type_id:	CONST_KW new_type_id
				|	basic_type new_type_id2
				|	scoped_id
;

after_opt:
			|	after	%prec SHIFT_THERE
;

after: '<' template_parameter_list '>'
;

new_type_id2:	CONST_KW new_type_id2
				|	basic_type new_type_id2
;

new_declarator:	ptr_operator new_declarator_opt
					|	direct_new_declarator
;

new_declarator_opt:
						|	new_declarator
;

direct_new_declarator:	'[' expression ']'
							|	direct_new_declarator '[' constant_expression ']'
;

new_initializer:	'(' expression_list_opt ')'
;

new_initializer_opt:
						|	new_initializer
;

delete_expression:	TWO_COLON_opt DELETE_KW cast_expression
						|	TWO_COLON_opt DELETE_KW '[' ']' cast_expression
;

cast_expression:	unary_expression	%dprec 1
					|	'(' type_id ')' cast_expression %dprec 2 {  } 
;

pm_expression:	cast_expression %dprec 1
				|	pm_expression DOT_STAR cast_expression %dprec 2
				|	pm_expression ARROW_STAR cast_expression %dprec 2
;

multiplicative_expression:		pm_expression %dprec 1
								|		multiplicative_expression STAR pm_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '*', $1, $3) }
								|		multiplicative_expression '/' pm_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '/', $1, $3) }
								|		multiplicative_expression '%' pm_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '%', $1, $3) }
;

additive_expression:	multiplicative_expression %dprec 1
						|	additive_expression '+' multiplicative_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '+', $1, $3) }
						|	additive_expression '-' multiplicative_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '-', $1, $3) }
;

shift_expression:	additive_expression %dprec 1
					|	shift_expression LSHIFT additive_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '<<', $1, $3) }
					|	shift_expression RSHIFT additive_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '>>', $1, $3) }
;

relational_expression:	shift_expression %dprec 1
							|	relational_expression '<' shift_expression  %dprec 2 { $$ = ast::A_BinopExp(@1, '<', $1, $3) }
							|	relational_expression '>' shift_expression  %dprec 2 { $$ = ast::A_BinopExp(@1, '>', $1, $3) }
							|	relational_expression LEQ shift_expression %dprec 4 { $$ = ast::A_BinopExp(@1, '<=', $1, $3) }
							|	relational_expression GEQ shift_expression %dprec 5 { $$ = ast::A_BinopExp(@1, '>=', $1, $3) }
;

equality_expression:	relational_expression  %dprec 1
					|	equality_expression EQUAL relational_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '==', $1, $3) }
					|	equality_expression NOT_EQUAL relational_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '!=', $1, $3) }
;

and_expression:	equality_expression	%dprec 1
					|	and_expression BITAND equality_expression 	%dprec 2 { $$ = ast::A_BinopExp(@1, '&', $1, $3) }
;

exclusive_or_expression:	and_expression %dprec 1
								|	exclusive_or_expression BITXOR and_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '^', $1, $3) }
;

inclusive_or_expression:	exclusive_or_expression %dprec 1
								|	inclusive_or_expression BITOR exclusive_or_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '|', $1, $3) }
;

logical_and_expression:	inclusive_or_expression %dprec 1
							|	logical_and_expression LAND inclusive_or_expression %dprec 2
;

logical_or_expression: logical_and_expression %dprec 1
							|	logical_or_expression LOR logical_and_expression %dprec 2
;

conditional_expression:	logical_or_expression %dprec 1
							|	logical_or_expression '?' expression ':' assignment_expression  %dprec 2{ $$ = ast::A_BinopExp(@1, '?', $1, ast::A_BinopExp(@3, ':', $3, $5)) }
;

assignment_operator:	'='
						|	ASSIGN_PLUS
						|	ASSIGN_MINUS
						|	ASSIGN_OR
						|	ASSIGN_XOR
						|	ASSIGN_AND
						|	ASSIGN_MUL
						|	ASSIGN_DIV
						|	ASSIGN_MOD
						|	ASSIGN_LSHIFT
						|	ASSIGN_RSHIFT
;

assignment_expression:	conditional_expression	%dprec 1
							|	logical_or_expression assignment_operator assignment_expression	%dprec 2 { $$ = ast::A_BinopExp(@1, '=', $1, $3) }
						/*	|	throw_expression*/
;

assignment_expression_opt:
								|	assignment_expression
;

throw_expression: THROW_KW assignment_expression_opt
;

expression:	assignment_expression	%dprec 1
			|	expression ',' assignment_expression	%dprec 2 { $$ = ast::A_BinopExp(@1, ',', $1, $3) }
;

expression_opt:
					|	expression
;

constant_expression:	conditional_expression
;

constant_expression_opt:	/*empty*/ { $$ = NULL }
								|	conditional_expression
;

/* Statements */
statement:	expression_or_declaration
			|	labeled_statement
			|	compound_statement
			|	selection_statement
			|	iteration_statement
			|	jump_statement
			|	return_statement
			/*
			|	try_block
			*/
;

labeled_statement:	CASE_KW case_primlist /*prim_conditional_expression*/ /*constant_expression*/ ':' statement	{ $$ = new ast::A_CaseStm($2, $4) }
						|	DEFAULT_KW ':' statement	{ $$ = new ast::A_DefaultStm($3) }
						|	IDENTIFIER ':' statement	{ $$ = new ast::A_LabelStm($1, $3) }
;

/*
prim_conditional_expression:	case_primlist
							|	logical_or_expression '?' expression ':' assignment_expression  { $$ = ast::A_BinopExp(@1, '?', $1, ast::A_BinopExp(@3, ':', $3, $5)) }
;
*/

try_block:	TRY_KW compound_statement handler_seq
;

handler_seq:	handler
				|	handler handler_seq
;

handler:	CATCH_KW '(' exception_declaration ')' compound_statement
;

exception_declaration:	type_specifier declarator %dprec 1
						/*	|	type_specifier type_specifier declarator %dprec 2
							|	type_specifier abstract_declarator %dprec 3
							|	type_specifier type_specifier abstract_declarator %dprec 4
							|	type_specifier %dprec 5
							|	type_specifier type_specifier %dprec 6
							*/
							|	THREE_DOTS
;

/*
TODO %merge <stmtMerge>
*/

jump_statement:	CONTINUE_KW ';'	{ $$ = new ast::A_ContinueStm() }
					|	BREAK_KW ';'	{ $$ = new ast::A_BreakStm() }
					|	GOTO_KW IDENTIFIER ';' { $$ = new ast::A_GotoStm($2) }
;

case_prim:	FALSE_KW	 { $$ = new ast::Expression2(@1, FALSE_KW) }
	|	TRUE_KW	 { $$ = new ast::Expression2(@1, TRUE_KW) }
	|	INTEGER_LITERAL { $$ = new ast::Expression2(@1, INTEGER_LITERAL, $1) }
	|	DOUBLE_LITERAL	{ $$ = new ast::Expression2(@1, DOUBLE_LITERAL, $1) }
	|	STRING_LITERAL { $$ = new ast::Expression2(@1, STRING_LITERAL, $1) }
	|	LSTRING_LITERAL { $$ = new ast::Expression2(@1, LSTRING_LITERAL) }
	|	CHAR_LITERAL { $$ = new ast::Expression2(@1, CHAR_LITERAL, $1) }
	|	TWO_COLON	{ $$ = new ast::Expression2(@1, TWO_COLON) }
	|	IDENTIFIER	{ $$ = new ast::Expression2(@1, IDENTIFIER, $1) }
	|	THIS_KW	{ $$ = new ast::Expression2(@1, THIS_KW) }
	|	NEW_KW	{ $$ = new ast::Expression2(@1, NEW_KW) }
	|	DELETE_KW	{ $$ = new ast::Expression2(@1, DELETE_KW) }
	|	OPERATOR_KW	{ $$ = new ast::Expression2(@1, OPERATOR_KW) }
	|	STRUCT_KW	{ $$ = new ast::Expression2(@1, STRUCT_KW) }
	|	CLASS_KW	{ $$ = new ast::Expression2(@1, CLASS_KW) }
	|	UNION_KW	{ $$ = new ast::Expression2(@1, UNION_KW) }
	|	INTERFACE_KW	{ $$ = new ast::Expression2(@1, INTERFACE_KW) }
	|	ENUM_KW	{ $$ = new ast::Expression2(@1, ENUM_KW) }
	|	CONST_KW	{ $$ = new ast::Expression2(@1, CONST_KW) }
	|	VOLATILE_KW	{ $$ = new ast::Expression2(@1, VOLATILE_KW) }
	|	TYPEDEF_KW	{ $$ = new ast::Expression2(@1, TYPEDEF_KW) }
	|	INLINE_KW	{ $$ = new ast::Expression2(@1, INLINE_KW) }
	|	TYPENAME_KW	{ $$ = new ast::Expression2(@1, TYPENAME_KW) }

	|	CHAR_KW		{ $$ = new ast::Expression2(@1, CHAR_KW) }
	|	WCHAR_T_KW		{ $$ = new ast::Expression2(@1, WCHAR_T_KW) }
	|	BOOL_KW		{ $$ = new ast::Expression2(@1, BOOL_KW) }
	|	INT_KW		{ $$ = new ast::Expression2(@1, INT_KW) }
	|	SHORT_KW		{ $$ = new ast::Expression2(@1, SHORT_KW) }
	|	LONG_KW		{ $$ = new ast::Expression2(@1, LONG_KW) }
	|	SIGNED_KW		{ $$ = new ast::Expression2(@1, SIGNED_KW) }
	|	UNSIGNED_KW		{ $$ = new ast::Expression2(@1, UNSIGNED_KW) }
	|	FLOAT_KW		{ $$ = new ast::Expression2(@1, FLOAT_KW) }
	|	DOUBLE_KW		{ $$ = new ast::Expression2(@1, DOUBLE_KW) }
	|	VOID_KW		{ $$ = new ast::Expression2(@1, VOID_KW) }

	|	RETURN_KW		{ $$ = new ast::Expression2(@1, RETURN_KW) }

	|	ATTRIBUTE_KW		{ $$ = new ast::Expression2(@1, ATTRIBUTE_KW) }

	|	'(' ')'			{ $$ = new ast::Expression2(@1, '(') }
	|	'(' primlist ')'	{ $$ = new ast::Expression2(@1, '(', $2) }
	|	'['	{ $$ = new ast::Expression2(@1, '[') }
	|	']'	{ $$ = new ast::Expression2(@1, ']') }
	|	'{'	{ $$ = new ast::Expression2(@1, '{') }
	|	'}'	{ $$ = new ast::Expression2(@1, '}') }
	/*
	|	'('				{ $$ = new ast::Expression2(@1, '(') }
	|	')'				{ $$ = new ast::Expression2(@1, ')') }
	|	'['				{ $$ = new ast::Expression2(@1, '[') }
	|	']'				{ $$ = new ast::Expression2(@1, ']') }
	*/
/*	|	STATIC_CAST_KW*/
/*	|	DYNAMIC_CAST_KW*/
	|	STATIC_CAST_KW { $$ = new ast::Expression2(@1, STATIC_CAST_KW) } // '<' type_id '>' '(' expression ')'
	|	DYNAMIC_CAST_KW { $$ = new ast::Expression2(@1, DYNAMIC_CAST_KW) } // '<' type_id '>' '(' expression ')'
	|	SIZEOF_KW { $$ = new ast::Expression2(@1, SIZEOF_KW) }
	|	'<'	{ $$ = new ast::Expression2(@1, '<') }
	|	'>'	{ $$ = new ast::Expression2(@1, '>') }
	|	'+'	{ $$ = new ast::Expression2(@1, '+') }
	|	'-'	{ $$ = new ast::Expression2(@1, '-') }
	|	'/'	{ $$ = new ast::Expression2(@1, '/') }
	|	'%'	{ $$ = new ast::Expression2(@1, '%') }
	|	'='	{ $$ = new ast::Expression2(@1, '=') }
	|	'~'	{ $$ = new ast::Expression2(@1, '~') }
	|	'?'	{ $$ = new ast::Expression2(@1, '?') }
/*	|	':'	{ $$ = new ast::Expression2(@1, ':') } */
	|	'!'	{ $$ = new ast::Expression2(@1, '!') }
	|	EQUAL	{ $$ = new ast::Expression2(@1, EQUAL) }
	|	NOT_EQUAL	{ $$ = new ast::Expression2(@1, NOT_EQUAL) }
	|	LEQ	{ $$ = new ast::Expression2(@1, LEQ) }
	|	GEQ	{ $$ = new ast::Expression2(@1, GEQ) }
	|	','	{ $$ = new ast::Expression2(@1, ',') }
	|	'.'	{ $$ = new ast::Expression2(@1, '.') }

	|	'@'
	{
	$$ = new ast::Expression2(@1, '#')
	}

	|	LSHIFT	{ $$ = new ast::Expression2(@1, LSHIFT) }
	|	RSHIFT	{ $$ = new ast::Expression2(@1, RSHIFT) }
	|	LOR	{ $$ = new ast::Expression2(@1, LOR) }
	|	LAND	{ $$ = new ast::Expression2(@1, LAND) }
	|	BITOR	{ $$ = new ast::Expression2(@1, BITOR) }
	|	BITAND	{ $$ = new ast::Expression2(@1, BITAND) }
	|	BITXOR	{ $$ = new ast::Expression2(@1, BITXOR) }
	|	ARROW	{ $$ = new ast::Expression2(@1, ARROW) }
	|	STAR	{ $$ = new ast::Expression2(@1, STAR) }
	|	PLUSPLUS	{ $$ = new ast::Expression2(@1, PLUSPLUS) }
	|	MINUSMINUS	{ $$ = new ast::Expression2(@1, MINUSMINUS) }
	|	ASSIGN_PLUS	{ $$ = new ast::Expression2(@1, ASSIGN_PLUS) }
	|	ASSIGN_MINUS	{ $$ = new ast::Expression2(@1, ASSIGN_MINUS) }
	|	ASSIGN_MUL	{ $$ = new ast::Expression2(@1, ASSIGN_MUL) }
	|	ASSIGN_DIV	{ $$ = new ast::Expression2(@1, ASSIGN_DIV) }
	|	ASSIGN_MOD	{ $$ = new ast::Expression2(@1, ASSIGN_MOD) }
;

case_primlist:	case_prim				{ $$ = new ast::Expression2List($1, NULL) }
			|	case_primlist	case_prim { $$ = new ast::Expression2List($2, $1) }
;

prim:	FALSE_KW	 { $$ = new ast::Expression2(@1, FALSE_KW) }
	|	TRUE_KW	 { $$ = new ast::Expression2(@1, TRUE_KW) }
	|	INTEGER_LITERAL { $$ = new ast::Expression2(@1, INTEGER_LITERAL, $1) }
	|	DOUBLE_LITERAL	{ $$ = new ast::Expression2(@1, DOUBLE_LITERAL, $1) }
	|	STRING_LITERAL	{ $$ = new ast::Expression2(@1, STRING_LITERAL, $1)	}
	|	LSTRING_LITERAL { $$ = new ast::Expression2(@1, LSTRING_LITERAL) }
	|	CHAR_LITERAL	{ $$ = new ast::Expression2(@1, CHAR_LITERAL, $1) }
	|	TWO_COLON	{ $$ = new ast::Expression2(@1, TWO_COLON) }
	|	IMPORT_KW
	{
	  $$ = new ast::Expression2(@1, IMPORT_KW, $1)
	}
	|	IDENTIFIER
		{
		 $$ = new ast::Expression2(@1, IDENTIFIER, $1)
		 }
	|	THIS_KW	{ $$ = new ast::Expression2(@1, THIS_KW) }
	|	NEW_KW	{ $$ = new ast::Expression2(@1, NEW_KW) }
	|	DELETE_KW	{ $$ = new ast::Expression2(@1, DELETE_KW) }
	|	OPERATOR_KW	{ $$ = new ast::Expression2(@1, OPERATOR_KW) }
	|	STRUCT_KW	{ $$ = new ast::Expression2(@1, STRUCT_KW) }
	|	CLASS_KW	{ $$ = new ast::Expression2(@1, CLASS_KW) }
	|	UNION_KW	{ $$ = new ast::Expression2(@1, UNION_KW) }
	|	INTERFACE_KW	{ $$ = new ast::Expression2(@1, INTERFACE_KW) }
	|	ENUM_KW	{ $$ = new ast::Expression2(@1, ENUM_KW) }
	|	CONST_KW	{ $$ = new ast::Expression2(@1, CONST_KW) }
	|	VOLATILE_KW	{ $$ = new ast::Expression2(@1, VOLATILE_KW) }
	|	TYPEDEF_KW	{ $$ = new ast::Expression2(@1, TYPEDEF_KW) }
	|	INLINE_KW	{ $$ = new ast::Expression2(@1, INLINE_KW) }
	|	VIRTUAL_KW	{ $$ = new ast::Expression2(@1, VIRTUAL_KW) }
	|	STATIC_KW	{ $$ = new ast::Expression2(@1, STATIC_KW) }
	|	EXPLICIT_KW	{ $$ = new ast::Expression2(@1, EXPLICIT_KW) }
	|	FRIEND_KW	{ $$ = new ast::Expression2(@1, FRIEND_KW) }

	|	ATTRIBUTE_KW		{ $$ = new ast::Expression2(@1, ATTRIBUTE_KW) }

	|	__ASM_KW	{ $$ = new ast::Expression2(@1, __ASM_KW) }

	|	__CDECL_KW	{ $$ = new ast::Expression2(@1, __CDECL_KW) }
	|	__STDCALL_KW	{ $$ = new ast::Expression2(@1, __STDCALL_KW) }
	|	__FASTCALL_KW	{ $$ = new ast::Expression2(@1, __FASTCALL_KW) }
	|	__DECLSPEC_KW	{ $$ = new ast::Expression2(@1, __DECLSPEC_KW) }

	|	THREE_DOTS	{ $$ = new ast::Expression2(@1, THREE_DOTS) }

	|	DO_KW		{ $$ = new ast::Expression2(@1, DO_KW) }
	|	WHILE_KW		{ $$ = new ast::Expression2(@1, WHILE_KW) }
	|	SWITCH_KW		{ $$ = new ast::Expression2(@1, SWITCH_KW) }
	|	IF_KW		{ $$ = new ast::Expression2(@1, IF_KW) }
	|	ELSE_KW		{ $$ = new ast::Expression2(@1, ELSE_KW) }
	|	FOR_KW		{ $$ = new ast::Expression2(@1, FOR_KW) }
	|	RETURN_KW		{ $$ = new ast::Expression2(@1, RETURN_KW) }
	|	BREAK_KW		{ $$ = new ast::Expression2(@1, BREAK_KW) }
	|	CONTINUE_KW		{ $$ = new ast::Expression2(@1, CONTINUE_KW) }
	|	CASE_KW		{ $$ = new ast::Expression2(@1, CASE_KW) }
	|	DEFAULT_KW		{ $$ = new ast::Expression2(@1, DEFAULT_KW) }
	|	GOTO_KW		{ $$ = new ast::Expression2(@1, GOTO_KW) }

	|	THROW_KW	{ $$ = new ast::Expression2(@1, THROW_KW) }
	|	NAMESPACE_KW	{ $$ = new ast::Expression2(@1, NAMESPACE_KW) }
	|	EXTERN_KW	{ $$ = new ast::Expression2(@1, EXTERN_KW) }

	|	CHAR_KW		{ $$ = new ast::Expression2(@1, CHAR_KW) }
	|	WCHAR_T_KW		{ $$ = new ast::Expression2(@1, WCHAR_T_KW) }
	|	BOOL_KW		{ $$ = new ast::Expression2(@1, BOOL_KW) }
	|	INT_KW		{ $$ = new ast::Expression2(@1, INT_KW) }
	|	SHORT_KW		{ $$ = new ast::Expression2(@1, SHORT_KW) }
	|	LONG_KW		{ $$ = new ast::Expression2(@1, LONG_KW) }
	|	SIGNED_KW		{ $$ = new ast::Expression2(@1, SIGNED_KW) }
	|	UNSIGNED_KW		{ $$ = new ast::Expression2(@1, UNSIGNED_KW) }
	|	FLOAT_KW		{ $$ = new ast::Expression2(@1, FLOAT_KW) }
	|	DOUBLE_KW		{ $$ = new ast::Expression2(@1, DOUBLE_KW) }
	|	VOID_KW		{ $$ = new ast::Expression2(@1, VOID_KW) }
	|	__INT8_KW		{ $$ = new ast::Expression2(@1, __INT8_KW) }
	|	__INT16_KW		{ $$ = new ast::Expression2(@1, __INT16_KW) }
	|	__INT32_KW		{ $$ = new ast::Expression2(@1, __INT32_KW) }
	|	__INT64_KW		{ $$ = new ast::Expression2(@1, __INT64_KW) }

	|	__FLOAT32_KW		{ $$ = new ast::Expression2(@1, __FLOAT32_KW) }
	|	__FLOAT64_KW		{ $$ = new ast::Expression2(@1, __FLOAT64_KW) }

	|	PUBLIC_KW		{ $$ = new ast::Expression2(@1, PUBLIC_KW) }
	|	PROTECTED_KW		{ $$ = new ast::Expression2(@1, PROTECTED_KW) }
	|	PRIVATE_KW		{ $$ = new ast::Expression2(@1, PRIVATE_KW) }

	|	TEMPLATE_KW		{ $$ = new ast::Expression2(@1, TEMPLATE_KW) }

	|	TYPENAME_KW	{ $$ = new ast::Expression2(@1, TYPENAME_KW) }

	|	DECLTYPE_KW	{ $$ = new ast::Expression2(@1, DECLTYPE_KW) }
	|	NULLPTR_KW	{ $$ = new ast::Expression2(@1, NULLPTR_KW) }


	|	';'				{ $$ = new ast::Expression2(@1, ';') }
/*	|	'(' ')'			{ $$ = new ast::Expression2(@1, '(') } */
/*	|	'(' primlist ')'	{ $$ = new ast::Expression2(@1, '(', $2) } */

	|	'('	{ $$ = new ast::Expression2(@1, '(') }
	|	')'	{ $$ = new ast::Expression2(@1, ')') }
	|	'['	{ $$ = new ast::Expression2(@1, '[') }
	|	']'	{ $$ = new ast::Expression2(@1, ']') }
	|	'{'	{ $$ = new ast::Expression2(@1, '{') }
	|	'}'	{ $$ = new ast::Expression2(@1, '}') }
	|	STATIC_CAST_KW { $$ = new ast::Expression2(@1, STATIC_CAST_KW) }
	|	DYNAMIC_CAST_KW { $$ = new ast::Expression2(@1, DYNAMIC_CAST_KW) }
	|	REINTERPRET_CAST_KW { $$ = new ast::Expression2(@1, REINTERPRET_CAST_KW) }
	|	CONST_CAST_KW { $$ = new ast::Expression2(@1, CONST_CAST_KW) }
	|	SIZEOF_KW { $$ = new ast::Expression2(@1, SIZEOF_KW) }
	|	TYPEID_KW { $$ = new ast::Expression2(@1, TYPEID_KW) }
	|	'<'	{ $$ = new ast::Expression2(@1, '<') }
	|	'>'	{ $$ = new ast::Expression2(@1, '>') }
	|	'+'	{ $$ = new ast::Expression2(@1, '+') }
	|	'-'	{ $$ = new ast::Expression2(@1, '-') }
	|	'/'	{ $$ = new ast::Expression2(@1, '/') }
	|	'%'	{ $$ = new ast::Expression2(@1, '%') }
	|	'='	{ $$ = new ast::Expression2(@1, '=') }
	|	'~'	{ $$ = new ast::Expression2(@1, '~') }
	|	'?'	{ $$ = new ast::Expression2(@1, '?') }
	|	':'	{ $$ = new ast::Expression2(@1, ':') }
	|	'!'	{ $$ = new ast::Expression2(@1, '!') }
	|	EQUAL	{ $$ = new ast::Expression2(@1, EQUAL) }
	|	NOT_EQUAL	{ $$ = new ast::Expression2(@1, NOT_EQUAL) }
	|	LEQ	{ $$ = new ast::Expression2(@1, LEQ) }
	|	GEQ	{ $$ = new ast::Expression2(@1, GEQ) }
	|	','	{ $$ = new ast::Expression2(@1, ',') }
	|	'.'	{ $$ = new ast::Expression2(@1, '.') }

	|	'@'
	{
	$$ = new ast::Expression2(@1, '#')
	}

	|	LSHIFT	{ $$ = new ast::Expression2(@1, LSHIFT) }
	|	RSHIFT	{ $$ = new ast::Expression2(@1, RSHIFT) }
	|	LOR	{ $$ = new ast::Expression2(@1, LOR) }
	|	LAND	{ $$ = new ast::Expression2(@1, LAND) }
	|	BITOR	{ $$ = new ast::Expression2(@1, BITOR) }
	|	BITAND	{ $$ = new ast::Expression2(@1, BITAND) }
	|	BITXOR	{ $$ = new ast::Expression2(@1, BITXOR) }
	|	ARROW	{ $$ = new ast::Expression2(@1, ARROW) }
	|	STAR	{ $$ = new ast::Expression2(@1, STAR) }
	|	PLUSPLUS	{ $$ = new ast::Expression2(@1, PLUSPLUS) }
	|	MINUSMINUS	{ $$ = new ast::Expression2(@1, MINUSMINUS) }
	|	ASSIGN_PLUS	{ $$ = new ast::Expression2(@1, ASSIGN_PLUS) }
	|	ASSIGN_MINUS	{ $$ = new ast::Expression2(@1, ASSIGN_MINUS) }
	|	ASSIGN_MUL	{ $$ = new ast::Expression2(@1, ASSIGN_MUL) }
	|	ASSIGN_DIV	{ $$ = new ast::Expression2(@1, ASSIGN_DIV) }
	|	ASSIGN_MOD	{ $$ = new ast::Expression2(@1, ASSIGN_MOD) }
	|	ASSIGN_OR	{ $$ = new ast::Expression2(@1, ASSIGN_OR) }
	|	ASSIGN_XOR	{ $$ = new ast::Expression2(@1, ASSIGN_XOR) }
	|	ASSIGN_AND	{ $$ = new ast::Expression2(@1, ASSIGN_AND) }
	|	ASSIGN_LSHIFT	{ $$ = new ast::Expression2(@1, ASSIGN_LSHIFT) }
	|	ASSIGN_RSHIFT	{ $$ = new ast::Expression2(@1, ASSIGN_RSHIFT) }
;

template_argument_prim:	FALSE_KW	 { $$ = new ast::Expression2(@1, FALSE_KW) }
	|	TRUE_KW	 { $$ = new ast::Expression2(@1, TRUE_KW) }
	|	INTEGER_LITERAL { $$ = new ast::Expression2(@1, INTEGER_LITERAL, $1) }
	|	DOUBLE_LITERAL	{ $$ = new ast::Expression2(@1, DOUBLE_LITERAL, $1) }
	|	STRING_LITERAL	{ $$ = new ast::Expression2(@1, STRING_LITERAL, $1)	}
	|	LSTRING_LITERAL { $$ = new ast::Expression2(@1, LSTRING_LITERAL) }
	|	CHAR_LITERAL	{ $$ = new ast::Expression2(@1, CHAR_LITERAL, $1) }
	|	TWO_COLON	{ $$ = new ast::Expression2(@1, TWO_COLON) }
	|	IDENTIFIER	{ $$ = new ast::Expression2(@1, IDENTIFIER, $1) }
	|	THIS_KW	{ $$ = new ast::Expression2(@1, THIS_KW) }
	|	NEW_KW	{ $$ = new ast::Expression2(@1, NEW_KW) }
	|	DELETE_KW	{ $$ = new ast::Expression2(@1, DELETE_KW) }
	|	OPERATOR_KW	{ $$ = new ast::Expression2(@1, OPERATOR_KW) }
	|	STRUCT_KW	{ $$ = new ast::Expression2(@1, STRUCT_KW) }
	|	CLASS_KW	{ $$ = new ast::Expression2(@1, CLASS_KW) }
	|	UNION_KW	{ $$ = new ast::Expression2(@1, UNION_KW) }
	|	INTERFACE_KW	{ $$ = new ast::Expression2(@1, INTERFACE_KW) }
	|	ENUM_KW	{ $$ = new ast::Expression2(@1, ENUM_KW) }
	|	CONST_KW	{ $$ = new ast::Expression2(@1, CONST_KW) }
	|	VOLATILE_KW	{ $$ = new ast::Expression2(@1, VOLATILE_KW) }
	|	TYPEDEF_KW	{ $$ = new ast::Expression2(@1, TYPEDEF_KW) }

	|	THROW_KW	{ $$ = new ast::Expression2(@1, THROW_KW) }

	|	CHAR_KW		{ $$ = new ast::Expression2(@1, CHAR_KW) }
	|	WCHAR_T_KW		{ $$ = new ast::Expression2(@1, WCHAR_T_KW) }
	|	BOOL_KW		{ $$ = new ast::Expression2(@1, BOOL_KW) }
	|	INT_KW		{ $$ = new ast::Expression2(@1, INT_KW) }
	|	SHORT_KW		{ $$ = new ast::Expression2(@1, SHORT_KW) }
	|	LONG_KW		{ $$ = new ast::Expression2(@1, LONG_KW) }
	|	SIGNED_KW		{ $$ = new ast::Expression2(@1, SIGNED_KW) }
	|	UNSIGNED_KW		{ $$ = new ast::Expression2(@1, UNSIGNED_KW) }
	|	FLOAT_KW		{ $$ = new ast::Expression2(@1, FLOAT_KW) }
	|	DOUBLE_KW		{ $$ = new ast::Expression2(@1, DOUBLE_KW) }
	|	VOID_KW		{ $$ = new ast::Expression2(@1, VOID_KW) }

	|	'(' ')'			{ $$ = new ast::Expression2(@1, '(') }
	|	'(' primlist ')'	{ $$ = new ast::Expression2(@1, '(', $2) }
	|	'['	{ $$ = new ast::Expression2(@1, '[') }
	|	']'	{ $$ = new ast::Expression2(@1, ']') }
	/*
	|	'('				{ $$ = new ast::Expression2(@1, '(') }
	|	')'				{ $$ = new ast::Expression2(@1, ')') }
	|	'['				{ $$ = new ast::Expression2(@1, '[') }
	|	']'				{ $$ = new ast::Expression2(@1, ']') }
	*/
/*	|	STATIC_CAST_KW*/
/*	|	DYNAMIC_CAST_KW*/
	|	STATIC_CAST_KW { $$ = new ast::Expression2(@1, STATIC_CAST_KW) } // '<' type_id '>' '(' expression ')'
	|	DYNAMIC_CAST_KW { $$ = new ast::Expression2(@1, DYNAMIC_CAST_KW) } // '<' type_id '>' '(' expression ')'
	|	REINTERPRET_CAST_KW { $$ = new ast::Expression2(@1, REINTERPRET_CAST_KW) } // '<' type_id '>' '(' expression ')'
	|	CONST_CAST_KW { $$ = new ast::Expression2(@1, CONST_CAST_KW) } // '<' type_id '>' '(' expression ')'
	|	SIZEOF_KW { $$ = new ast::Expression2(@1, SIZEOF_KW) }
/*	|	'<'	{ $$ = new ast::Expression2(@1, '<') } */
	|	'>'	{ $$ = new ast::Expression2(@1, '>') }
	|	'+'	{ $$ = new ast::Expression2(@1, '+') }
	|	'-'	{ $$ = new ast::Expression2(@1, '-') }
	|	'/'	{ $$ = new ast::Expression2(@1, '/') }
	|	'%'	{ $$ = new ast::Expression2(@1, '%') }
	|	'='	{ $$ = new ast::Expression2(@1, '=') }
	|	'~'	{ $$ = new ast::Expression2(@1, '~') }
	|	'?'	{ $$ = new ast::Expression2(@1, '?') }
	|	':'	{ $$ = new ast::Expression2(@1, ':') }
	|	'!'	{ $$ = new ast::Expression2(@1, '!') }
	|	EQUAL	{ $$ = new ast::Expression2(@1, EQUAL) }
	|	NOT_EQUAL	{ $$ = new ast::Expression2(@1, NOT_EQUAL) }
	|	LEQ	{ $$ = new ast::Expression2(@1, LEQ) }
	|	GEQ	{ $$ = new ast::Expression2(@1, GEQ) }
/*	|	','	{ $$ = new ast::Expression2(@1, ',') } */
	|	'.'	{ $$ = new ast::Expression2(@1, '.') }
	|	LSHIFT	{ $$ = new ast::Expression2(@1, LSHIFT) }
	|	RSHIFT	{ $$ = new ast::Expression2(@1, RSHIFT) }
	|	LOR	{ $$ = new ast::Expression2(@1, LOR) }
	|	LAND	{ $$ = new ast::Expression2(@1, LAND) }
	|	BITOR	{ $$ = new ast::Expression2(@1, BITOR) }
	|	BITAND	{ $$ = new ast::Expression2(@1, BITAND) }
	|	BITXOR	{ $$ = new ast::Expression2(@1, BITXOR) }
	|	ARROW	{ $$ = new ast::Expression2(@1, ARROW) }
	|	STAR	{ $$ = new ast::Expression2(@1, STAR) }
	|	PLUSPLUS	{ $$ = new ast::Expression2(@1, PLUSPLUS) }
	|	MINUSMINUS	{ $$ = new ast::Expression2(@1, MINUSMINUS) }
	|	ASSIGN_PLUS	{ $$ = new ast::Expression2(@1, ASSIGN_PLUS) }
	|	ASSIGN_MINUS	{ $$ = new ast::Expression2(@1, ASSIGN_MINUS) }
	|	ASSIGN_MUL	{ $$ = new ast::Expression2(@1, ASSIGN_MUL) }
	|	ASSIGN_DIV	{ $$ = new ast::Expression2(@1, ASSIGN_DIV) }
	|	ASSIGN_MOD	{ $$ = new ast::Expression2(@1, ASSIGN_MOD) }
	|	ASSIGN_LSHIFT	{ $$ = new ast::Expression2(@1, ASSIGN_LSHIFT) }
	|	ASSIGN_RSHIFT	{ $$ = new ast::Expression2(@1, ASSIGN_RSHIFT) }
;

template_argument_primlist: template_argument_prim	{ $$ = new ast::Expression2List($1, NULL) }
									|	template_argument_primlist template_argument_prim	{ $$ = new ast::Expression2List($2, $1) }

primlist:	prim				{ $$ = new ast::Expression2List($1, NULL) }
			|	primlist	prim { $$ = new ast::Expression2List($2, $1) }
;

primlist_opt:	{$$ = NULL}
				|	primlist
;

expression_or_declaration:	primlist ';'	{ $$ = new ast::A_PrimListStm($1) }
;

expression_statement:	expression ';'	{ $$ = new ast::A_ExpStm($1) }
;

statement_seq:	statement { $$ = new ast::A_StmList($1, NULL) }
				|	statement statement_seq { $$ = new ast::A_StmList($1, $2) }
;

/* This will give a shift/reduce conflict, the default is shift, and that's okay here */
selection_statement:	IF_KW '(' condition ')' statement { $$ = new ast::A_IfStm($3, $5, NULL) }
						|	IF_KW '(' condition ')' statement ELSE_KW statement { $$ = new ast::A_IfStm($3, $5, $7) }
						|	SWITCH_KW '(' condition ')' statement { $$ = new ast::A_SwitchStm($3, $5) }
;

condition:	primlist/*expression*/
		/*	|	type_specifier_seq declarator '=' assignment_expression { $$ = new ast::A_Condition }*/
;

condition_opt:	/*empty*/
				|	condition
;

iteration_statement:	WHILE_KW '(' condition ')' statement { $$ = new ast::A_WhileStm($3, $5) }
						|	DO_KW statement WHILE_KW '(' primlist ')' ';' { $$ = new ast::A_DoWhileStm($2, $5) }
						|	FOR_KW '(' primlist_opt ';' primlist_opt ';' primlist_opt ')' statement { $$ = new ast::A_ForStm($3, $5, $7, $9) }
;

return_statement: RETURN_KW ';' { $$ = new ast::A_ReturnStm() }
					|	RETURN_KW primlist/*expression*/ ';' { $$ = new ast::A_ReturnStm($2) }
;


declaration_statement:	block_declaration { $$ = new ast::A_DeclarationStm($1) }
;

/* Declarations */


declaration_seq: declaration { $$ = new ast::A_DeclarationList($1, NULL) }
					| declaration declaration_seq { $$ = new ast::A_DeclarationList($1, $2) }
;

/*
declaration_seq: declaration { $$ = new ast::A_DeclarationList($1, NULL) }
					| declaration_seq declaration { $$ = new ast::A_DeclarationList($2, $1) }
;
*/

declaration_seq_opt:	/*empty*/ { $$ = NULL }
						|	declaration_seq { $$ = $1 }
;

declaration:	block_declaration
				|	function_definition
				|	linkage_specification
				|	explicit_specialization
				|	namespace_definition
				|	template_declaration
;

export_opt:	/*empty*/
			|	EXPORT_KW
;

template_declaration:	export_opt TEMPLATE_KW '<' template_parameter_list '>' declaration	{ $$ = new ast::A_TemplateDeclaration($4, $6) }
;

template_parameter_list:	template_parameter	{ $$ = new ast::A_TemplateParameterList($1, NULL) }
								|	template_parameter_list ',' template_parameter { $$ = new ast::A_TemplateParameterList($3, $1) }
;

template_parameter:	type_parameter
						|	template_parameter_declaration
;

TYPENAME_KW_opt:
					|	TYPENAME_KW
;

type_parameter:	CLASS_KW identifier_opt { $$ = new ast::A_TypeTemplateParameter($2, NULL) }
					|	CLASS_KW identifier_opt '=' type_id { $$ = new ast::A_TypeTemplateParameter($2, $4) }
					|	TYPENAME_KW identifier_opt	{ $$ = new ast::A_TypeTemplateParameter($2, NULL) }
					|	TYPENAME_KW	identifier_opt '=' type_id { $$ = new ast::A_TypeTemplateParameter($2, $4) }
					|	TEMPLATE_KW '<' template_parameter_list '>' CLASS_KW identifier_opt
				/*	|	TEMPLATE_KW '<' template_parameter_list '>' CLASS_KW identifier_opt '=' id_expression */
				/*	|	basic_type identifier_opt { $$ = new ast::A_TemplateParameter($2, NULL) } */
;

template_parameter_declaration: template_parameter_declaration1 declarator	{ $$ = new ast::A_DeclaratorTemplateParameter($1, $2) }
;

template_parameter_declaration1:	CONST_KW template_parameter_declaration1 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
										|	basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
										|	basic_type template_parameter_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;

template_parameter_declaration2:	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
										|	basic_type template_parameter_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;

template_id:	template_name '<' template_argument_list_opt '>'
;

template_name:	IDENTIFIER
;

template_argument_list:	template_argument	{ $$ = new ast::A_TemplateArgumentList($1, NULL) }
							|	template_argument_list ',' template_argument { $$ = new ast::A_TemplateArgumentList($3, $1) }
;

template_argument_list_opt:	{ $$ = NULL }
									|	template_argument_list
;

template_argument: template_argument_primlist	/*assignment_expression	%merge <template_argument_merge> { $$ = new ast::A_TemplateArgument(NULL, $1) }
						|	type_id						%merge <template_argument_merge> { $$ = new ast::A_TemplateArgument($1, NULL) }
						*/
					/*	|	id_expression	%dprec 3*/
;

/*
explicit-instantiation:
template declaration
*/

explicit_specialization:	TEMPLATE_KW '<' '>' declaration	{ $$ = NULL }
;

linkage_specification:	EXTERN_KW STRING_LITERAL '{' declaration_seq_opt '}' { $$ = new ast::A_LinkageDeclaration($2, $4) }
							|	EXTERN_KW STRING_LITERAL declaration { $$ = new ast::A_LinkageDeclaration($2, new ast::A_DeclarationList($3, NULL)) }
;

namespace_definition:	named_namespace_definition
						/*	|	unnamed_namespace_definition*/
;

named_namespace_definition:	NAMESPACE_KW IDENTIFIER '{' declaration_seq_opt '}' { $$ = new ast::A_NamespaceDefinition($2, $4) }
;

unnamed_namespace_definition:	NAMESPACE_KW '{' declaration_seq_opt '}'
;

block_declaration:	simple_declaration
						|	using_declaration
						|	using_directive
						|	__ASM_KW	{
										pPP2->GetToken();

										if ((pPP2->curtokpp->type == CToken::tok_char || pPP2->curtokpp->type == CToken::tok_symbol) && pPP2->curtokpp->symbol == '{')
										{
											pPP2->GetToken();

											while (!pPP2->_eof())
											{
												if ((pPP2->curtokpp->type == CToken::tok_char || pPP2->curtokpp->type == CToken::tok_symbol) && pPP2->curtokpp->symbol == '}')
													break;

												pPP2->GetToken();
											}
											pPP2->EatSymbol('}');
										}
										else
										{
											while (!pPP2->_eof())
											{
												if ((pPP2->curtokpp->type == CToken::tok_symbol || pPP2->curtokpp->type == CToken::tok_char) && pPP2->curtokpp->symbol == '}')
												{
													bLastTok = true;
													break;
												}

												if ((pPP2->curtokpp->type == CToken::tok_symbol || pPP2->curtokpp->type == CToken::tok_char) && pPP2->curtokpp->symbol == ';')
													break;

												if (pPP2->curtokpp->type == CToken::tok_symbol && pPP2->curtokpp->symbol == '\n')
													break;

												pPP2->GetToken();
											}
										}

										$$ = NULL;
									}
;

typename_opt:	/*empty*/
				|	TYPENAME_KW
;

using_declaration:	USING_KW typename_opt  unqualified_id ';' { $$ = NULL }
					/*	|	USING_KW typename_opt nested_name_specifier unqualified_id ';' { $$ = NULL }
						|	USING_KW TWO_COLON unqualified_id ';' { $$ = NULL }
						*/
;

using_directive:	USING_KW NAMESPACE_KW scoped_id ';'	{ $$ = new ast::A_UsingDirectiveDeclaration($3) }
;

simple_declaration:	simple_declaration2 init_declarator_list_opt ';' { $$ = new ast::A_SimpleDeclaration($1, $2) }
;

simple_declaration2:	CONST_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
						|	VOLATILE_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
						|	TYPEDEF_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
						|	INLINE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), NULL) }
						|	INLINE_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
						|	EXTERN_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXTERN), $2) }
						|	STATIC_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), $2) }
						|	VIRTUAL_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), NULL) }
						|	VIRTUAL_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), $2) }
						|	EXPLICIT_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXPLICIT), NULL) }
						|	EXPLICIT_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXPLICIT), $2) }
						|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
						|	basic_type simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
						|	elaborate_type { $$ = new ast::DeclSpecList($1, NULL) }
						|	elaborate_type simple_declaration4  { $$ = new ast::DeclSpecList($1, $2) }
						|	scoped_id { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), NULL) }
					/*	|	scoped_id simple_declaration4 { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), $2) } */
;

simple_declaration3:	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
						|	basic_type simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
						|	CONST_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
						|	CONST_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
						|	VOLATILE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), NULL) }
						|	VOLATILE_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
						|	TYPEDEF_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), NULL) }
						|	TYPEDEF_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
						|	INLINE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), NULL) }
						|	INLINE_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
;

simple_declaration4:	/*CONST_KW simple_declaration4 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
						|	VOLATILE_KW simple_declaration4 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
						
						|*/	TYPEDEF_KW simple_declaration4 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
						|	INLINE_KW simple_declaration4 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
						|	CONST_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
						|	VOLATILE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), NULL) }
						|	TYPEDEF_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), NULL) }
						|	INLINE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), NULL) }
;

elaborate_type:	class_specifier
					|	enum_specifier
;

basic_type:	VOID_KW { $$ = ast::A_VOID }
			|	BOOL_KW{ $$ = ast::A_BOOL }
			|	CHAR_KW{ $$ = ast::A_CHAR }
			|	WCHAR_T_KW{ $$ = ast::A_WCHAR_T }
			|	INT_KW{ $$ = ast::A_INT }
			|	SHORT_KW{ $$ = ast::A_SHORT }
			|	LONG_KW{ $$ = ast::A_LONG }
			|	SIGNED_KW{ $$ = ast::A_SIGNED }
			|	UNSIGNED_KW{ $$ = ast::A_UNSIGNED }
			|	FLOAT_KW{ $$ = ast::A_FLOAT }
			|	DOUBLE_KW{ $$ = ast::A_DOUBLE }
;

///

type_specifier2:	nested_name_specifier
					|	CHAR_KW
;

/*
decl_specifier_or_declarator:	decl_specifier %dprec 2
									|	declarator %dprec 1
;

decl_specifier_or_declarator_seq:	decl_specifier_or_declarator
											|	decl_specifier_or_declarator_seq decl_specifier_or_declarator
;
*/

decl_specifier_seq:	decl_specifier { $$ = new ast::DeclSpecList($1, NULL) }
						|	decl_specifier_seq decl_specifier { $$ = new ast::DeclSpecList($2, $1) }
;

decl_specifier_seq_opt:
						|	decl_specifier_seq
;

decl_specifier:	/*nested_name_specifier { printf("decl %s ", $1); }*/
					/*	storage_class_specifier { $$ = NULL }
					|*/	type_specifier
					|	function_specifier { $$ = NULL }
					|	FRIEND_KW { $$ = NULL }
					|	TYPEDEF_KW { $$ = NULL }
;

_decl_specifier:	_type_specifier
/*
					|	function_specifier
					|	FRIEND_KW
					|	TYPEDEF_KW
					*/
;

storage_class_specifier:	AUTO_KW { $$ = ast::A_AUTO }
								|	REGISTER_KW { $$ = ast::A_REGISTER }
								|	STATIC_KW { $$ = ast::A_STATIC }
							/*	|	EXTERN_KW { $$ = ast::A_EXTERN } */
								|	MUTABLE_KW { $$ = ast::A_MUTABLE }
								|	__DECLSPEC_KW '(' IDENTIFIER ')' { /*TODO*/$$ = ast::A_DECLSPEC }
;

function_specifier:	INLINE_KW { $$ = ast::A_INLINE }
						|	VIRTUAL_KW { $$ = ast::A_VIRTUAL }
						|	EXPLICIT_KW { $$ = ast::A_EXPLICIT }
;

/*
decl_specifier_seq:	decl_specifier								{ $$ = new ast::DeclSpecList($1, NULL) }
						|	decl_specifier_seq decl_specifier	{ $$ = new ast::DeclSpecList($2, $1) }
;
*/

/*
decl_specifier_seq2:	decl_specifier2								{ $$ = new ast::DeclSpecList($1, NULL) }
						|	decl_specifier_seq2 decl_specifier2	{ $$ = new ast::DeclSpecList($2, $1) }
;
*/

/*
decl_specifier_seq_opt: empty { $$ = NULL }
							|	decl_specifier_seq
;
*/

/*
decl_specifier_seq2_opt: { $$ = NULL }
							|	decl_specifier_seq2
;
*/

simple_type_specifier_seq:	simple_type_specifier2 { $$ = new ast::DeclSpecList($1, NULL) }
								|	simple_type_specifier_seq simple_type_specifier2 { $$ = new ast::DeclSpecList($2, $1) }
;

/*
type_name:	IDENTIFIER
			|	template_id
;
*/

simple_type_specifier2:	/*scoped_id
							|	*/ CHAR_KW { $$ = ast::A_SimpleType(ast::A_CHAR) }
							|	WCHAR_T_KW { $$ = ast::A_SimpleType(ast::A_WCHAR_T) }
							|	BOOL_KW { $$ = ast::A_SimpleType(ast::A_BOOL) }
							|	SHORT_KW { $$ = ast::A_SimpleType(ast::A_SHORT) }
							|	INT_KW { $$ = ast::A_SimpleType(ast::A_INT) }
							|	__INT64_KW { $$ = ast::A_SimpleType(ast::A___INT64) }
							|	LONG_KW { $$ = ast::A_SimpleType(ast::A_LONG) }
							|	SIGNED_KW { $$ = ast::A_SimpleType(ast::A_SIGNED) }
							|	UNSIGNED_KW { $$ = ast::A_SimpleType(ast::A_UNSIGNED) }
							|	FLOAT_KW { $$ = ast::A_SimpleType(ast::A_FLOAT) }
							|	DOUBLE_KW { $$ = ast::A_SimpleType(ast::A_DOUBLE) }
							|	VOID_KW { $$ = ast::A_SimpleType(ast::A_VOID) }
;

simple_type_specifier:	scoped_id
/*
							|	CHAR_KW
							|	WCHAR_T_KW
							|	BOOL_KW
							|	SHORT_KW 
							|	INT_KW 
							|	__INT64_KW 
							|	LONG_KW 
							|	SIGNED_KW 
							|	UNSIGNED_KW 
							|	FLOAT_KW 
							|	DOUBLE_KW 
							|	VOID_KW 
							*/
;

/*
simple_type_specifier2: IDENTIFIER { $$ = ast::A_NameType($1) }
;
*/

type_specifier:	simple_type_specifier2	{ $$ = NULL }
				/*	|	elaborated_type_specifier { $$ = NULL }
					|	class_specifier	{ $$ = $1 }
					|	enum_specifier { $$ = NULL }
					|	cv_qualifier	{ $$ = NULL }

*/
/*
					|	storage_class_specifier*/
;

_type_specifier:	simple_type_specifier
				/*	|	elaborated_type_specifier { $$ = NULL }
				*/
					|	class_specifier
					|	enum_specifier
					|	cv_qualifier
;

type_specifier_seq:	type_specifier
						|	type_specifier_seq type_specifier
;

/*
type_specifier2:	elaborated_type_specifier {  }
					|	class_specifier	{ $$ = $1 }
					|	cv_qualifier	{ $$ = $1 }
;
*/

elaborated_type_specifier: class_key scoped_id
							/*	|	class_key nested_name_specifier_opt template_opt template_id
								|	TYPENAME_KW IDENTIFIER <nested_name_specifier> { ASSERT(0) }*/
;

enum_specifier:	ENUM_KW identifier_opt '{' enumerator_list_opt '}' { $$ = new ast::A_Enum($2, $4) }
					|	ENUM_KW IDENTIFIER { $$ = NULL }
;

identifier_opt:	/*empty*/ { $$ = NULL }
					|	IDENTIFIER
;

enumerator_list:	enumerator_definition { $$ = new ast::A_EnumDefList($1, NULL) }
					|	enumerator_list ',' { $$ = $1 }
					|	enumerator_list ',' enumerator_definition { $$ = new ast::A_EnumDefList($3, $1) }
;

enumerator_list_opt:	/*empty*/ { $$ = NULL }
						|	enumerator_list { $$ = $1 }
;

enumerator_definition:	IDENTIFIER { $$ = new ast::A_EnumDefinition($1, NULL) }
							|	IDENTIFIER '=' constant_expression { $$ = new ast::A_EnumDefinition($1, $3) }
;

ctor_initializer: ':' mem_initializer_list
;

mem_initializer_list:	mem_initializer										%dprec 2
							|	mem_initializer ',' mem_initializer_list		%dprec 1
;

mem_initializer:	mem_initializer_id '(' expression_list_opt ')'

mem_initializer_id:	/*::opt nested-name-specifieropt class-name*/
							nested_name_specifier_opt class_name
;

ctor_initializer_opt:	/*empty*/
							|	ctor_initializer
;

function_definition:	simple_declaration2 declarator ctor_initializer_opt function_body { $$ = new ast::A_FunDef(@1, $1, $2, $4) }
						|	declarator ctor_initializer_opt function_body { $$ = new ast::A_FunDef(@1, NULL, $1, $3) }
;


function_try_block: TRY_KW /*ctor_initializer_opt function_body handler_seq*/
;

type_id_list:	type_id
				|	type_id_list ',' type_id
;

type_id_list_opt:	/*empty*/
					|	type_id_list
;

exception_specification: THROW_KW '(' type_id_list_opt ')'
;

exception_specification_opt:	/*empty*/
									|	exception_specification
;

/*
function_definition2:	decl_specifier_seq2_opt IDENTIFIER decl_specifier_seq2_opt declarator function_body
									{
										ast::DeclSpecList* declspec = new ast::DeclSpecList(ast::A_TypeSpecifier(ast::A_NameType($2)), $1);

										ast::DeclSpecList* dl = $3;
										while (dl)
										{
											declspec = new ast::DeclSpecList(dl->head, declspec);
											dl = dl->tail;
										}

										$$ = ast::A_FunDef(declspec, $4, $5)
									}
;
*/

function_body: compound_statement
;

compound_statement:	'{' '}'	{ $$ = new ast::A_CompoundStm(NULL) }
						|	'{' statement_seq '}' { $$ = new ast::A_CompoundStm($2) }
;

/*Declarators*/

init_declarator_list:	init_declarator { $$ = new ast::A_DeclaratorList($1, NULL) }
							|	init_declarator_list ',' init_declarator { $$ = new ast::A_DeclaratorList($3, $1) }
;

init_declarator_list_opt:	/*empty*/ { $$ = NULL }
							|	init_declarator_list { $$ = $1}
;

/* TODO */
init_declarator:	declarator	%dprec 1
					|	declarator initializer	%dprec 2
;

initializer_opt:	/*empty*/
					|	initializer
;

initializer:	'=' initializer_clause
				|	'(' expression_list ')'
;

COMMA_opt:	/*empty*/
			|	','
;

initializer_clause:	assignment_expression
						|	'{' initializer_list COMMA_opt '}'
						|	'{' '}'
;

initializer_list:		initializer_clause
						|	initializer_list ',' initializer_clause
;

declarator:	direct_declarator  {$$ = new ast::A_DirectDeclaratorDeclarator(@1, $1) }
			|	ptr_operator declarator	{ $$ = new ast::A_PtrDeclarator($1, $2) }
;

direct_declarator:	scoped_id
	{
	$$ = ast::A_DirectDeclaratorId(@1, $1) 
}
						|	direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt
						 {
						 $$ = ast::A_DirectDeclaratorParen($1, $3, $5)
						 }
						|	'(' declarator ')' 
						{ 
						$$ = ast::A_DeclaratorDirectDeclarator(@2, $2)
						 } 
						 
						|	direct_declarator '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3) }
;

/*
 There's a reduce/reduce ambiguity between the two using parantheses here 
direct_declarator1:	 declarator_id {  }
						|	'(' declarator ')' { $$ = ast::A_DirectDeclaratorDeclarator($2) }
						|	direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { $$ = ast::A_DirectDeclaratorParen($1, $3) }
						|	direct_declarator '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3) }
;

direct_declarator2:	 
;

sub_declarator:	sub_direct_declarator {$$ = ast::A_DirectDeclaratorDeclarator($1) }
					|	ptr_operator sub_declarator	{ $$ = ast::A_PtrDeclarator($2) }
					
					|	decl_specifier { }
					|	decl_specifier declarator	{ $$ = ast::A_PtrDeclarator($2) }
					
;
*/

/* There's a reduce/reduce ambiguity between the two using parantheses here 
/*
sub_direct_declarator:	declarator_id { $$ = ast::A_DirectDeclaratorId(@1, $1) }
						|	sub_direct_declarator '(' parameter_declaration_clause ')' { $$ = ast::A_DirectDeclaratorParen($1, $3) }
						|	sub_direct_declarator '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3) }
						|	'(' sub_declarator ')' { $$ = ast::A_DirectDeclaratorDeclarator($2) }
;
*/

/*
declarator_id:	id_expression {
$$ = $1
}
				|	TWO_COLON nested_name_specifier {}
;
*/

type_id:	type_id1 abstract_declarator_opt { $$ = new ast::A_TypeId($1, $2) }
;

type_id1:	CONST_KW type_id1	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
			|	VOLATILE_KW type_id1	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
			|	basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
			|	basic_type type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
			|	elaborate_type	{ $$ = new ast::DeclSpecList($1, NULL) }
			|	elaborate_type type_id3	{ $$ = new ast::DeclSpecList($1, $2) }
			|	TYPENAME_KW_opt scoped_id { $$ = new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL) }
			|	TYPENAME_KW_opt scoped_id type_id3 { $$ = new ast::DeclSpecList(new ast::A_NameType(@2, $2), $3) }
;

type_id2:	CONST_KW type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
			|	VOLATILE_KW type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
			|	basic_type type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
			|	CONST_KW	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
			|	VOLATILE_KW	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), NULL) }
			|	basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
;

type_id3:	CONST_KW type_id3	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
			|	CONST_KW	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
;

/*
type_specifier_seq:	type_specifier { $$ = new ast::DeclSpecList($1, NULL) }
						|	type_specifier_seq type_specifier  { $$ = new ast::DeclSpecList($2, $1) }
;
*/

/*
type_specifier_seq2:	type_specifier2 { $$ = new ast::DeclSpecList(ast::A_TypeSpecifier($1), NULL) }
						|	type_specifier_seq2 type_specifier2  { $$ = new ast::DeclSpecList(ast::A_TypeSpecifier($2), $1) }
;

type_specifier_seq2_opt:	
								|	type_specifier_seq2
;
*/

abstract_declarator:	direct_abstract_declarator {$$ = new ast::A_DirectDeclaratorDeclarator(@1, $1) }
						|	ptr_operator abstract_declarator_opt { $$ = new ast::A_PtrDeclarator($1, $2) }
;

abstract_declarator_opt:	/*empty*/ { $$ = NULL }
								|	abstract_declarator
;

direct_abstract_declarator:	/*scoped_id { $$ = ast::A_DirectDeclaratorId(@1, $1) }
									|*/	direct_abstract_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { $$ = ast::A_DirectDeclaratorParen($1, $3, $5) }
									|	direct_abstract_declarator '[' constant_expression_opt ']'  { $$ = ast::A_DirectDeclaratorArray($1, $3) }
									|	'(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { ast::A_DirectDeclaratorParen(NULL, $2, $4) }
									|	'[' constant_expression_opt ']'  { $$ = ast::A_DirectDeclaratorArray(NULL, $2) }
									|	'(' abstract_declarator ')' { $$ = ast::A_DeclaratorDirectDeclarator(@2, $2) }
;

direct_abstract_declarator_opt:	{ $$ = NULL }
										|	direct_abstract_declarator;
;

parameter_declaration_clause:	parameter_declaration_list_opt { $$ = new ast::A_ParameterDeclarations($1, false) }
							/*		|	parameter_declaration_list_opt THREE_DOTS { $$ = new ast::A_ParameterDeclarations($1, true) }
							*/
									|	parameter_declaration_list ',' THREE_DOTS { $$ = new ast::A_ParameterDeclarations($1, true) }
;

three_dots_opt:	/*empty*/
					|	THREE_DOTS
;

parameter_declaration_list:	parameter_declaration { $$ = new ast::A_TypeIdList($1, NULL) }
									|	parameter_declaration_list ',' parameter_declaration { $$ = new ast::A_TypeIdList($3, $1) }
;

parameter_declaration_list_opt:	/*empty*/ { $$ = NULL }
										|	parameter_declaration_list
;

/*
parameter_declaration_decl:	decl_specifier_seq
;
*/

parameter_declaration:	parameter_declaration1 abstract_declarator_opt { $$ = new ast::A_TypeId($1, $2) }
							|	parameter_declaration1 abstract_declarator_opt '=' assignment_expression { $$ = new ast::A_TypeId($1, $2) }
							|	parameter_declaration1 declarator { $$ = new ast::A_TypeId($1, $2) }
							|	parameter_declaration1 declarator '=' assignment_expression { $$ = new ast::A_TypeId($1, $2) }
;

parameter_declaration1:	CONST_KW parameter_declaration1 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
							|	VOLATILE_KW parameter_declaration1 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
							|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
							|	basic_type parameter_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
							|	elaborate_type { $$ = new ast::DeclSpecList($1, NULL) }
							|	elaborate_type parameter_declaration4 { $$ = new ast::DeclSpecList($1, $2) }
							|	TYPENAME_KW_opt scoped_id { $$ = new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL) }
							|	TYPENAME_KW_opt scoped_id parameter_declaration4 { $$ = new ast::DeclSpecList(new ast::A_NameType(@2, $2), $3) }
;

parameter_declaration3:	basic_type parameter_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
							|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
							|	CONST_KW parameter_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
							|	VOLATILE_KW parameter_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
							|	CONST_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
							|	VOLATILE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
;

parameter_declaration4:	CONST_KW parameter_declaration4 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
							|	VOLATILE_KW parameter_declaration4 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
							|	CONST_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
							|	VOLATILE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), NULL) }
;

/*
abstract_parameter_declaration1:	CONST_KW abstract_parameter_declaration2
							|	VOLATILE_KW abstract_parameter_declaration2
							|	basic_type abstract_parameter_declaration3
							|	elaborate_type abstract_parameter_declaration4
							|	scoped_id abstract_parameter_declaration4
;

abstract_parameter_declaration2:	CONST_KW abstract_parameter_declaration2
							|	VOLATILE_KW abstract_parameter_declaration2
							|	basic_type abstract_parameter_declaration3
							|	elaborate_type abstract_parameter_declaration4
							|	scoped_id abstract_parameter_declaration4
;

abstract_parameter_declaration3:	
								basic_type abstract_parameter_declaration3
;

abstract_parameter_declaration4:	
								CONST_KW parameter_declaration4
							|	VOLATILE_KW parameter_declaration4
;
*/

ptr_operator:	cc_qualifier	{ $$ = $1 }
				|	STAR cv_qualifier_seq_opt		{ $$ = '*' }
				|	BITAND /*cv_cc_qualifier*/		{ $$ = '&' }
/*				|	cv_qualifier				*/
;

ptr_operator_in_declarator:	STAR cv_cc_qualifier_seq_opt /*cv_qualifier_seq_opt*/
				|	BITAND cv_cc_qualifier
/*				|	cv_qualifier
				|	TWO_COLON_opt nested_name_specifier STAR cv_qualifier_seq_opt
				*/
;

cc_qualifier:	__STDCALL_KW	{ $$ = 's'; }
				|	__CDECL_KW	{ $$ = 'c'; }
;

cv_qualifier:	CONST_KW { $$ = new ast::A_DeclSpecModifier(@1, ast::A_CONST) }
				|	VOLATILE_KW { $$ = new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE) }
;

cv_qualifier_seq:	cv_qualifier	{ $$ = new ast::DeclSpecList($1, NULL) }
					|	cv_qualifier cv_qualifier_seq { $$ = new ast::DeclSpecList($1, $2) }
;

cv_qualifier_seq_opt:	{ $$ = NULL }
							|	cv_qualifier_seq
;

cv_cc_qualifier:	CONST_KW
					|	VOLATILE_KW
					|	__CDECL_KW
					|	__STDCALL_KW
;

cv_cc_qualifier_seq:	cv_cc_qualifier
						|	cv_cc_qualifier cv_cc_qualifier_seq
;

cv_cc_qualifier_seq_opt:
							|	cv_cc_qualifier_seq
;

/*Classes*/

class_name: IDENTIFIER
			|	template_id
;

class_specifier:	class_key scoped_id { $$ = new ast::A_Class(@1, $1, $2) }
					|	class_head '{' member_specification_opt '}' { $$ = new ast::A_ClassDef(@1, $1, $3) }
;

class_key:	CLASS_KW { $$ = CLASSKEY_CLASS }
			|	STRUCT_KW { $$ = CLASSKEY_STRUCT }
			|	UNION_KW { $$ = CLASSKEY_UNION }
			|	INTERFACE_KW { $$ = CLASSKEY_INTERFACE }
;

access_specifier:	PRIVATE_KW { $$ = ast::A_ACCESS_PRIVATE }
					|	PROTECTED_KW { $$ = ast::A_ACCESS_PROTECTED }
					|	PUBLIC_KW { $$ = ast::A_ACCESS_PUBLIC }
;

access_specifier_opt:	/*empty*/ { $$ = ast::A_ACCESS_PROTECTED }
							|	access_specifier
;

class_head:		class_key { $$ = new ast::A_ClassHead(@1, $1, NULL, NULL) }
				|	class_key scoped_id base_clause_opt { $$ = new ast::A_ClassHead(@1, $1, $2, $3) }
			/*	|	class_key nested_name_specifier IDENTIFIER base_clause_opt
				|	class_key nested_name_specifier_opt template_id base_clause_opt
				*/
;

member_specification:	member_declaration member_specification_opt { $$ = new ast::A_MemberDecl($1, $2) }
							|	access_specifier ':' member_specification_opt { $$ = new ast::A_MemberAccessSpec($1, $3) }
;

member_declaration_decl:	member_declarator_list_opt ';'	{ $$ = new ast::A_SimpleDeclaration(NULL, $1) }
								|	simple_declaration2 /*member_declaration_decl2*/ member_declarator_list_opt ';'{ $$ = new ast::A_SimpleDeclaration($1, $2) }
;

/*
member_declaration_decl2:	CONST_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
								|	VOLATILE_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
								|	TYPEDEF_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
								|	INLINE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), NULL) }
								|	INLINE_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
								|	VIRTUAL_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), NULL) }
								|	VIRTUAL_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), $2) }
								|	EXPLICIT_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXPLICIT), NULL) }
								|	EXPLICIT_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXPLICIT), $2) }
								|	STATIC_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), $2) }
								|	FRIEND_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_FRIEND), $2) }

								|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
								|	basic_type member_declaration_decl3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }

								|	elaborate_type { $$ = new ast::DeclSpecList($1, NULL) }
							//	|	elaborate_type member_declaration_decl4
								|	TYPENAME_KW_opt scoped_id { $$ = new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL) }
							//	|	TYPENAME_KW_opt scoped_id member_declaration_decl4
;

member_declaration_decl3:	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
								|	basic_type member_declaration_decl3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;
*/

/*
member_declaration_decl:	member_declaration_decl2
;

member_declaration_decl2:	CONST_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(ast::A_DeclSpecModifier(ast::A_CONST), $2) }
								|	VOLATILE_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(ast::A_DeclSpecModifier(ast::A_VOLATILE), $2) }
								|	TYPEDEF_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(ast::A_DeclSpecModifier(ast::A_TYPEDEF), $2) }
								|	INLINE_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(ast::A_DeclSpecModifier(ast::A_INLINE), $2) }
								|	VIRTUAL_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(ast::A_DeclSpecModifier(ast::A_VIRTUAL), $2) }
								|	STATIC_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(ast::A_DeclSpecModifier(ast::A_STATIC), $2) }
								|	FRIEND_KW member_declaration_decl2 { $$ = new ast::DeclSpecList(ast::A_DeclSpecModifier(ast::A_FRIEND), $2) }

								|	basic_type { $$ = new ast::DeclSpecList(ast::A_DeclSpecBasicType($1), NULL) }
								|	basic_type member_declaration_decl3 { $$ = new ast::DeclSpecList(ast::A_DeclSpecBasicType($1), $2) }

								|	elaborate_type member_declaration_decl4
								|	TYPENAME_KW_opt scoped_id member_declaration_decl4
;

member_declaration_decl3:	member_declarator_list_opt ';'
								|	basic_type
								|	basic_type member_declaration_decl3
;

member_declaration_decl4:	member_declarator_list_opt ';'
								|	CONST_KW member_declaration_decl4
								|	VOLATILE_KW member_declaration_decl4
								|	TYPEDEF_KW member_declaration_decl4
								|	INLINE_KW member_declaration_decl4
;
*/

member_declaration:	member_declaration_decl
						|	function_definition
						|	template_declaration
;

member_declarator_list:	member_declarator { $$ = new ast::A_DeclaratorList($1, NULL) }
							|	member_declarator_list ',' member_declarator { $$ = new ast::A_DeclaratorList($3, $1) }
;

member_declarator_list_opt:
									|	member_declarator_list
;

member_declarator:	/*declarator pure_specifier_opt	Caught by the following rule
						|*/	declarator constant_initializer_opt
						|	scoped_id ':' constant_expression { $$ = NULL }
;

/*
pure_specifier: '=' INTEGER_LITERAL	{ ASSERT($2 == 0) }
;

pure_specifier_opt:	
						|	pure_specifier
;
*/

constant_initializer_opt:	/*empty*/
								|	'=' constant_expression
;

/*
member_declaration:
	declaration
;
*/

member_specification_opt: /*empty*/ { $$ = NULL }
								| member_specification
;

/* Derived Classes */

base_clause:	':' base_specifier_list { $$ = $2 }
;

base_clause_opt:	/*empty*/	{ $$ = NULL }
					|	base_clause
;

base_specifier_list:	base_specifier		{ $$ = new ast::A_BaseSpecifierList($1, NULL) }
						|	base_specifier ',' base_specifier_list { $$ = new ast::A_BaseSpecifierList($1, $3) }
;

base_class_name:	scoped_id
				/*	|	nested_name_specifier class_name { $$ = ast::A_BinopExp('::', $1, ast::A_IdExp($1)) }*/
;

base_specifier:	base_class_name	{$$ = $1}
					|	VIRTUAL_KW access_specifier_opt base_class_name		{	$$ = $3	}
					|	access_specifier virtual_opt base_class_name			{	$$ = $3	}
;

virtual_opt:	/*empty*/
				|	VIRTUAL_KW
;


     %%

static ast::Declaration* Merge (YYSTYPE& x0, YYSTYPE& x1)
{
	return ast::A_Declaration2(x0.declaration, x1.declaration);
}

#if 0
static ast::A_Stm*
     stmtMerge (YYSTYPE& x0, YYSTYPE& x1)
     {
	  //YYSTYPE ytype;
     //  printf ("<OR> ");
      // return ytype;

		ast::A_Stm* p = new ast::A_ExpOrDeclStm(x1.exp, x0.declaration);
		//p->kind = ast::A_Stm::ast::A_EXP_OR_DECLARATION;
		//p->EXP_OR_DECL.exp = x1.exp;
		//p->EXP_OR_DECL.declaration = x0.declaration;
		 return p;
     }
#endif

/*
static ast::A_TemplateArgument*
     template_argument_merge (YYSTYPE& x0, YYSTYPE& x1)
     {

		ast::A_TemplateArgument* p = new ast::A_TemplateArgument(x0.templateArgument->m_pTypeId, x1.templateArgument->m_pExp);
		 return p;
     }
*/