%{

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

     %}

//%glr-parser
%locations
%name-prefix="cpp_exp_"

%union {
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
}

%token EXP_TOKEN
%token DECLS_TOKEN

%token <id> IDENTIFIER
%token <id> identifier_lparen

%type <id> identifier

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
%token <doubleValue> DOUBLE_LITERAL

%token <string_literal> IMPORT_KW

%token <id> TEMPLATE_NAME

%token ATTRIBUTE_KW

%token <exp> THIS_KW

%type <num> assignment_operator

%type <exp2> prim
%type <exp2List> primlist
%type <exp2List> primlist_opt

%type <num> operator

%type <id> identifier_opt
%type <id> id
%type <id> id_ctor
%type <exp> typename_id
%type <exp> template_id_with_args

%type <exp> q_typename_id
%type <exp> q_template_id

%type <exp> p_typename_id

%type <simpleTypeSpec> basic_type

%type <initializer> initializer

%type <exp> initializer_clause
%type <expList> initializer_list

%type <initializer> constant_initializer_opt

%type <templateArgument> template_argument
%type <templateArgumentList> template_argument_list
%type <templateArgumentList> template_argument_list_opt

%type <expList> ctor_initializer
%type <expList> ctor_initializer_opt
%type <expList> mem_initializer_list
%type <exp> mem_initializer
%type <exp> mem_initializer_id

%type <expList> attribute_specification_list_opt
%type <expList> attribute_specification_list
%type <exp> attribute_specification

%type <typeId> type_id

%type <exp> base_class_name

%type <exp> conversion_function_id
%type <exp> conversion_nested_id
%type <exp> operator_function_id

%type <templateParameter> template_parameter_declaration
%type <declspecList> template_parameter_declaration1
%type <declspecList> template_parameter_declaration2
%type <declspecList> parameter_declaration1
%type <declspecList> parameter_declaration3
%type <declspecList> parameter_declaration4

%type <declspec> decltype_specifier

%type <declspecExt> declspec_item
%type <declspecExtList> declspeclist
%type <declspecExtList> declspeclist_opt

%type <enumList> enumerator_list
%type <enumList> enumerator_list_opt
%type <enumDef> enumerator_definition

%type <exp> throw_expression
%type <exp> new_expression
%type <exp> delete_expression
%type <exp> constant_expression
%type <exp> constant_expression_opt
%type <exp> expression
%type <exp> expression_opt
%type <exp> conditional_expression
%type <exp> assignment_expression
%type <exp> assignment_expression_opt
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

%type <exp> template_argument_constant_expression
%type <exp> template_argument_conditional_expression
%type <exp> template_argument_logical_or_expression
%type <exp> template_argument_logical_and_expression
%type <exp> template_argument_inclusive_or_expression
%type <exp> template_argument_exclusive_or_expression
%type <exp> template_argument_and_expression
%type <exp> template_argument_equality_expression
%type <exp> template_argument_relational_expression

%type <classHead> class_head

//%type <exp> id_expression
%type <exp> postfix_expression
%type <exp> primary_expression

%type <exp> scoped_id
%type <exp> type_scoped_id
%type <exp> non_type_scoped_id

%type <exp> p_type_scoped_id

%type <exp> q_type_nested_id
%type <exp> q_type_scoped_id

//%type <exp> ctor_id

%type <exp> dtor_id
%type <exp> dtor_nested_id
%type <exp> dtor_scoped_id

%type <exp> p_type_nested_id

%type <exp> declarator_nested_id

%type <exp> type_nested_id
%type <exp> non_type_nested_id
%type <expList> expression_list
%type <expList> expression_list_opt
%type <expList> expression_or_type_list
%type <expList> expression_or_type_list_opt

%type <expList> new_initializer
%type <expList> new_initializer_opt

%type <expList> new_placement
%type <expList> new_placement_opt

%type <exp> p_non_type_scoped_id
%type <exp> p_non_type_nested_id

%type <initDeclarator> statement_declarator

%type <initDeclarator> init_declarator
%type <initDeclarator> q_init_declarator
%type <initDeclaratorList> init_declarator_list
%type <initDeclaratorList> init_declarator_list_opt

%type <initDeclaratorList> statement_declarator_list
%type <initDeclaratorList> statement_declarator_list_opt

%type <initDeclaratorList> q_init_declarator_list
%type <initDeclaratorList> q_init_declarator_list_opt

%type <declarator> abstract_declarator
%type <declarator> abstract_declarator_opt
%type <directDeclarator> direct_abstract_declarator

%type <declarator> new_declarator
%type <declarator> new_declarator_opt
%type <directDeclarator> direct_new_declarator

%type <declaration> template_declaration
%type <declaration> member_template_declaration

%type <templateParameterList> template_parameter_list
%type <templateParameter> template_parameter
%type <templateParameter> type_parameter

%type <typeId> parameter_declaration
%type <typeIdList> parameter_declaration_list
%type <typeIdList> parameter_declaration_list_opt
%type <paramDecls> parameter_declaration_clause

%type <declspecList> class_specifier_ext_list
%type <declspecList> class_specifier_ext_list_opt
%type <declspec> class_specifier_ext

%type <declspecList> cv_qualifier_seq
%type <declspecList> cv_qualifier_seq_opt

%type <memberSpec> member_specification
%type <memberSpec> member_specification_opt
%type <declaration> member_declaration
%type <declaration> member_declaration_decl

%type <declaratorList> member_declarator_list
%type <declaratorList> member_declarator_list_opt
%type <declarator> member_declarator

%type <initDeclaratorList> q_member_declarator_list
%type <initDeclaratorList> q_member_declarator_list_opt
%type <initDeclarator> q_member_declarator

%type <declarator> conversion_declarator
%type <declarator> conversion_declarator_opt

%type <declspecList> conversion_type_id
%type <declspecList> conversion_type_id2

%type <typespec> enum_specifier
%type <typespec> class_specifier
%type <typespec> cv_qualifier

%type <typeId> new_type_id

%type <id> class_name
%type <baseSpecifier> base_specifier
%type <baseSpecifierList> base_specifier_list
%type <baseSpecifierList> base_clause
%type <baseSpecifierList> base_clause_opt

%type <accessSpec> access_specifier
%type <accessSpec> access_specifier_opt

%type <declaration> declaration
%type <declaration> static_assert_declaration

%type <stm> statement
%type <stm> selection_statement
%type <stm> iteration_statement
%type <stm> return_statement
%type <stm> jump_statement
%type <stm> labeled_statement
%type <compoundstm> compound_statement
%type <stm> expression_statement
%type <stm> declaration_statement
%type <compoundstm> function_body
%type <stmList> statement_seq
%type <stmList> statement_seq_opt
%type <cond> condition

%type <declaration> linkage_specification

%type <declaration> namespace_definition
%type <declaration> named_namespace_definition
%type <declaration> function_definition
%type <declaration> asm_definition
%type <declaration> member_function_definition
%type <declaration> simple_declaration
%type <declspecList> simple_declaration2
%type <declspecList> simple_declaration3

%type <declaration> _simple_declaration
%type <declspecList> _simple_declaration2
%type <declspecList> _simple_declaration3

%type <declaration> _member_declaration

%type <declspecList> q_simple_declaration2
%type <declspecList> q_simple_declaration2_opt

%type <declspecList> basic_type_seq
%type <declspecList> basic_type_seq2

%type <declspec> elaborated_type_specifier

%type <declarationList> declaration_seq
%type <declarationList> declaration_seq_opt
%type <declarationList> translation_unit

%type <classKey> class_key;

%type <declarator> declarator
%type <directDeclarator> direct_declarator
%type <num> ptr_operator
%type <num> cc_qualifier

%type <declarator> member_declarator_
%type <directDeclarator> direct_member_declarator_

%type <declarator> conversion_function_declarator
%type <directDeclarator> direct_conversion_function_declarator

%type <declarator> q_declarator
%type <directDeclarator> q_direct_declarator

%type <declarator> _q_member_declarator
%type <directDeclarator> q_member_direct_declarator

%token NTA
%token YTA
%token YTT
%token NTY
%token <pScope> YTY
%token CTORN

%nonassoc SHIFT_THERE
%nonassoc TWO_COLON ELSE_KW

     %%

start:	/*EXP_TOKEN*/ expression { g_exp = $1 }
	/*	|	declaration */
		|	DECLS_TOKEN translation_unit	{ translation_unit = $2; }
;

/*
expression_or_declaration:	declaration
									{
										$$ = new ast::A_ExpOrDecl(NULL, $1); m_g_exp_or_decl = $$;
										YYACCEPT
									}
									|	expression
									{
										$$ = new ast::A_ExpOrDecl($1, NULL); m_g_exp_or_decl = $$;
										YYACCEPT
									}
									| ';'
									{
										$$ = NULL; YYACCEPT
									}
;
*/

translation_unit:	 declaration_seq_opt {	$$ = $1; 	}
;

ident: IDENTIFIER YTY
;

ident2: IDENTIFIER NTY
;

/*
test_name:	ident
			|	ident TWO_COLON test_name
			|	ident2
			|	ident2 TWO_COLON test_name
;
*/

declaration_seq: declaration { $$ = new ast::DeclarationList($1, NULL) }
					| declaration_seq declaration { $$ = new ast::DeclarationList($2, $1) }
;

declaration_seq_opt:	{ $$ = NULL }
						|	declaration_seq
;

export_opt:	/*empty*/
			|	EXPORT_KW
;

static_assert_declaration:	STATIC_ASSERT_KW '(' expression ',' STRING_LITERAL ')' ';' { $$ = new StaticAssertDeclaration(@1, $3, $5) }
;

declaration:	IMPORT_KW /*STRING_LITERAL*/
	{
		DoImport($1);
	 $$ = new ImportDeclaration(@1, $1)
	 }
				|	'#' STRING_LITERAL			{ $$ = new PragmaDeclaration(@1, $2) }	
				|	attribute_specification_list_opt _simple_declaration ';'		{ $$ = $2; Do($1, $$); }
				|	attribute_specification_list_opt function_definition			{ $$ = $2; Do($1, $$) }
				|	attribute_specification_list_opt linkage_specification { $$ = $2; }
				|	namespace_definition { $$ = $1; }
				|	template_declaration { $$ = $1; }
				|	static_assert_declaration
;

linkage_specification:	EXTERN_KW STRING_LITERAL '{' declaration_seq_opt '}' { $$ = new ast::LinkageDeclaration(@1, $2, $4) }
					|	EXTERN_KW STRING_LITERAL declaration { $$ = new ast::LinkageDeclaration(@1, $2, new ast::DeclarationList($3, NULL)) }
;

namespace_definition:	named_namespace_definition
						/*	|	unnamed_namespace_definition*/
;

identifier:	IDENTIFIER/* NTY
			|	IDENTIFIER YTY
			*/
;

named_namespace_definition:	NAMESPACE_KW identifier
	{
		ast::NamespaceDefinition* nsdef = new ast::NamespaceDefinition(@1, $2, NULL);
		g_templates.push(nsdef);

		g_scopeStack.push(g_pScope);
	//	g_scopeStack.push(g_pScope2);

		Do(NULL, nsdef);
	}
	'{' declaration_seq_opt '}'
	{
		ast::NamespaceDefinition* nsdef = (ast::NamespaceDefinition*)g_templates.top();

		g_templates.pop();
		nsdef->m_declarationList = Reverse($5);

	//	g_pScope2 = g_scopeStack.top();
	//	ASSERT(g_pScope2);
	//	g_scopeStack.pop();

		g_pScope = g_scopeStack.top();
		ASSERT(g_pScope);
		g_scopeStack.pop();

		g_pScope2 = g_pScope;

		$$ = nsdef;
	}
;

unnamed_namespace_definition:	NAMESPACE_KW '{' declaration_seq_opt '}'
;

template_declaration:	export_opt TEMPLATE_KW '<'
{
	$<declaration>$ = new ast::TemplateDeclaration(@2, NULL, NULL);
	g_templates.push($<declaration>$);
	DoTp((ast::TemplateDeclaration*)$<declaration>$);

	g_scopeStack.push(g_pScope);
	g_scopeStack.push(g_pScope2);
}
template_parameter_list '>'
{
	ast::TemplateDeclaration* td = (ast::TemplateDeclaration*)g_templates.top();
	td->m_params = Reverse($5);
}
declaration
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

	td->m_decl = $8;
	$$ = td;
}
;

member_template_declaration:	export_opt TEMPLATE_KW '<'
{
	$<declaration>$ = new ast::TemplateDeclaration(@2, NULL, NULL);
	g_templates.push($<declaration>$);
	DoTp((ast::TemplateDeclaration*)$<declaration>$);

	g_scopeStack.push(g_pScope);
	g_scopeStack.push(g_pScope2);
}
template_parameter_list '>'
{
	ast::TemplateDeclaration* td = (ast::TemplateDeclaration*)g_templates.top();
	td->m_params = Reverse($5);
/*
	$$ = new ast::A_TemplateDeclaration($4, NULL);
	g_templates.push($$);

	g_scopeStack.push(g_pScope2);

	DoTp((ast::TemplateDeclaration*)$$)
	*/
}
member_declaration
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

	td->m_decl = $8;
	$$ = td;
}
;

template_parameter_list:	template_parameter	{ $$ = new ast::TemplateParameterList($1, NULL) }
								|	template_parameter_list ',' template_parameter { $$ = new ast::TemplateParameterList($3, $1) }
;

template_parameter:	type_parameter	{ $$ = $1; Do_TParam($$); }
						|	template_parameter_declaration	{ $$ = $1; Do_TParam($$); }
						|	template_parameter_declaration '=' literal { $$ = $1; Do_TParam($$, $3); }
;

type_parameter:	CLASS_KW identifier_opt { $$ = new ast::TypeTemplateParameter($2, NULL) }
					|	CLASS_KW identifier_opt '=' type_id { $$ = new ast::TypeTemplateParameter($2, $4) }
					|	TYPENAME_KW identifier_opt	{ $$ = new ast::TypeTemplateParameter($2, NULL) }
					|	TYPENAME_KW	identifier_opt '=' type_id { $$ = new ast::TypeTemplateParameter($2, $4) }
					|	TEMPLATE_KW '<' template_parameter_list '>' CLASS_KW identifier_opt
;

template_parameter_declaration: template_parameter_declaration1 declarator	{ $$ = new ast::DeclaratorTemplateParameter($1, $2) }
;

template_parameter_declaration1:	CONST_KW template_parameter_declaration1 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
										|	basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
										|	basic_type template_parameter_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;

template_parameter_declaration2:	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
										|	basic_type template_parameter_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;

declarator:	direct_declarator  {$$ = new ast::A_DirectDeclaratorDeclarator(@1, $1) }
			|	ptr_operator declarator	{ $$ = new ast::A_PtrDeclarator(@1, $1, $2) }
;

direct_declarator:	non_type_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() }
						|	'(' declarator ')' { $$ = ast::A_DeclaratorDirectDeclarator(@2, $2) } 
						|	direct_declarator '('
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
						}

						parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt
						{
							g_lastScope = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

						//	g_pScope2 = g_pScope;

							$$ = ast::A_DirectDeclaratorParen($1, $4, $6);
						}
						|	direct_declarator '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3) }
;

member_declarator_:	direct_member_declarator_  {$$ = new ast::A_DirectDeclaratorDeclarator(@1, $1) }
						|	ptr_operator member_declarator_	{ $$ = new ast::A_PtrDeclarator($1, $2) }
;

direct_member_declarator_:	non_type_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() }
						|	type_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() }
						|	'(' member_declarator_ ')' { $$ = ast::A_DeclaratorDirectDeclarator(@2, $2) } 
						|	direct_member_declarator_ '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { $$ = ast::A_DirectDeclaratorParen($1, $3, $5) }
						|	direct_member_declarator_ '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3) }
;

conversion_function_declarator:	direct_conversion_function_declarator  {$$ = new ast::A_DirectDeclaratorDeclarator(@1, $1) }
;

direct_conversion_function_declarator:	conversion_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() }
						|	'(' conversion_function_declarator ')' { $$ = ast::A_DeclaratorDirectDeclarator(@2, $2) } 
						|	direct_conversion_function_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { $$ = ast::A_DirectDeclaratorParen($1, $3, $5) }
						|	direct_conversion_function_declarator '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3) }
;

q_declarator:	q_direct_declarator  {$$ = new ast::A_DirectDeclaratorDeclarator(@1, $1); }
				|	ptr_operator q_declarator	{ $$ = new ast::A_PtrDeclarator(@1, $1, $2) }
				|	declarator_nested_id STAR { g_scopeStack2.pop(); } q_declarator
				{
					$$ = new ast::A_PtrDeclarator(@1, '.*', $4, $1);
				}
;

q_direct_declarator:	p_non_type_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() }
						|	declarator_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() }
						|	'(' q_declarator ')' { $$ = ast::A_DeclaratorDirectDeclarator(@2, $2) } 
						|	q_direct_declarator here
						parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt
						{
							g_lastScope = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

						//	g_pScope2 = g_pScope;

							$$ = ast::A_DirectDeclaratorParen($1, $3, $5);
						}
						|	q_direct_declarator '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3); }
;

_q_member_declarator:	q_member_direct_declarator  {$$ = new ast::A_DirectDeclaratorDeclarator(@1, $1); }
							|	ptr_operator _q_member_declarator	{ $$ = new ast::A_PtrDeclarator(@1, $1, $2) }
							|	declarator_nested_id STAR { g_scopeStack2.pop(); } _q_member_declarator
							{
								$$ = new ast::A_PtrDeclarator(@1, '.*', $4, $1);
							}
;

q_member_direct_declarator:	p_non_type_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() }
						|	declarator_nested_id { $$ = ast::A_DirectDeclaratorId(@1, $1); g_scopeStack2.pop() } 
						|	'(' _q_member_declarator ')' { $$ = ast::A_DeclaratorDirectDeclarator(@2, $2) } 
						|	q_member_direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { $$ = ast::A_DirectDeclaratorParen($1, $3, $5); }
						|	q_member_direct_declarator '[' constant_expression_opt ']' { $$ = ast::A_DirectDeclaratorArray($1, $3); }
;

type_id_list:	type_id
				|	type_id_list ',' type_id
;

type_id_list_opt:	/*empty*/
					|	type_id_list
;

exception_specification: THROW_KW '(' type_id_list_opt ')'
;

exception_specification_opt:
									|	exception_specification
;

ptr_operator:	cc_qualifier
				|	STAR /*cv_qualifier_seq_opt*/		{ $$ = '*' }
				|	STAR CONST_KW			{ $$ = '*' }	// TODO
				|	BITAND /*cv_cc_qualifier*/		{ $$ = '&' }
				|	LAND /*cv_cc_qualifier*/		{ $$ = '&&' }
;

cc_qualifier:	__CDECL_KW	{ $$ = 'c'; }
			|	__STDCALL_KW	{ $$ = 's'; }
			|	__FASTCALL_KW	{ $$ = 'f'; }
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

parameter_declaration_clause:	parameter_declaration_list_opt { $$ = new ast::ParameterDeclarations($1, false) }
							|	parameter_declaration_list ',' THREE_DOTS { $$ = new ast::ParameterDeclarations($1, true) }
;

parameter_declaration_list:	parameter_declaration { $$ = new ast::A_TypeIdList($1, NULL) }
						|	parameter_declaration_list ',' parameter_declaration { $$ = new ast::A_TypeIdList($3, $1) }
;

parameter_declaration_list_opt:	{ $$ = NULL }
							|	parameter_declaration_list
;

parameter_declaration:	parameter_declaration1 abstract_declarator_opt { $$ = new ast::A_TypeId($1, $2) }
					|	parameter_declaration1 abstract_declarator_opt '=' assignment_expression { $$ = new ast::A_TypeId($1, $2) }
					|	parameter_declaration1 declarator { $$ = new ast::A_TypeId($1, $2) }
					|	parameter_declaration1 declarator '=' assignment_expression { $$ = new ast::A_TypeId($1, $2, $4) }
;

parameter_declaration1:	CONST_KW parameter_declaration1 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
					|	VOLATILE_KW parameter_declaration1 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
					|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
					|	basic_type parameter_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
					|	elaborated_type_specifier { $$ = new ast::DeclSpecList($1, NULL) }
					|	q_type_scoped_id { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), NULL) }
					|	q_type_scoped_id parameter_declaration4 { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), $2) }
					|	__DECLSPEC_KW '(' declspeclist_opt ')' parameter_declaration1 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecExtModifier(@1, Reverse($3)), $5) }
					|	decltype_specifier { $$ = new ast::DeclSpecList($1, NULL) }
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

abstract_declarator:		direct_abstract_declarator { $$ = new ast::A_DirectDeclaratorDeclarator(@1, $1) }
					|	ptr_operator abstract_declarator_opt { $$ = new ast::A_PtrDeclarator(@1, $1, $2) }
;

abstract_declarator_opt:	/*empty*/ { $$ = NULL }
						|	abstract_declarator
;

direct_abstract_declarator:		direct_abstract_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { $$ = ast::A_DirectDeclaratorParen($1, $3, $5) }
							|	direct_abstract_declarator '[' constant_expression_opt ']'  { $$ = ast::A_DirectDeclaratorArray($1, $3) }
							|	'(' parameter_declaration_clause ')' cv_qualifier_seq_opt exception_specification_opt { ast::A_DirectDeclaratorParen(NULL, $2, $4) }
							|	'[' constant_expression_opt ']'  { $$ = ast::A_DirectDeclaratorArray(NULL, $2) }
							|	'(' abstract_declarator ')' { $$ = ast::A_DeclaratorDirectDeclarator(@2, $2) }
;

/* Expressions */

literal:		FALSE_KW	 { $$ = ast::A_BoolExp(0) }
		|	TRUE_KW	 { $$ = ast::A_BoolExp(1) }
		|	INTEGER_LITERAL { $$ = ast::A_Int32Exp($1) }
		|	DOUBLE_LITERAL { $$ = ast::A_DoubleExp($1) }
		|	STRING_LITERAL { $$ = ast::A_StringExp($1) }
		|	LSTRING_LITERAL { $$ = ast::A_LStringExp($1) }
		|	CHAR_LITERAL { $$ = new ast::CharLiteralExp($1) }
		|	NULLPTR_KW { $$ = new ast::NullLiteralExp() }
;

primary_expression:	literal
						|	THIS_KW	{ $$ = ast::A_ThisExp() }
						|	'(' expression ')' { $$ = $2}
						|	non_type_scoped_id
;

/*
id_expression:	IDENTIFIER { $$ = ast::A_IdExp($1) }
				|	qualified_id
;
*/

template_opt:	/*empty*/
				|	TEMPLATE_KW
;

TWO_COLON_opt:	/*empty*/
				|	TWO_COLON
;

decltype_specifier:	DECLTYPE_KW '(' expression ')'	{ $$ = new ast::DeclType(@1, $3) }

id:	IDENTIFIER /* %prec SHIFT_THERE */
		{
			StringA* identifier = $1;

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
						ptoken = new ast::Expression2List(new ast::Expression2(@1/*cpp_exp_lloc*/, NTY), ptoken);
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
				if (*$$ == *g_pClass2->m_name)
				{
					ptoken = new ast::Expression2List(new ast::Expression2(cpp_exp_lloc, CTORN), ptoken);
				//	g_scopeStack2.pop();
				}
			}

			$$ = identifier;
		}
;

id_ctor:	id CTORN
;

template_id_with_args: id YTT '<'
		{
		g_scopeStack2Stack.push(g_scopeStack2);
		g_scopeStack2.cont.clear();
		}
	
		template_argument_list_opt '>'
		{
		g_scopeStack2 = g_scopeStack2Stack.top();
		g_scopeStack2Stack.pop();

		$$ = ast::A_TemplateId($1, $5);
		}
|
		id_ctor YTT '<'
		{
		g_scopeStack2Stack.push(g_scopeStack2);
		g_scopeStack2.cont.clear();
		}
	
		template_argument_list_opt '>'
		{
		g_scopeStack2 = g_scopeStack2Stack.top();
		g_scopeStack2Stack.pop();

		$$ = ast::A_TemplateId($1, $5);
		}
;

q_template_id:	id YTT { $$ = ast::A_TemplateId($1, nullptr); }
			|	id_ctor YTT { $$ = ast::A_TemplateId($1, nullptr); }
			|	template_id_with_args
;

/*
ctor_id: id_ctor YTY
			{
			$$ = ast::A_TemplateId($1, NULL);
			g_scopeStack2.pop();
			}
		|	id_ctor YTT
			{
			$$ = ast::A_TemplateId($1, NULL);
			g_scopeStack2.pop();
			}
;
*/

typename_id:		id YTY { $$ = ast::A_TemplateId($1, nullptr); }
			|	id_ctor YTY	{ $$ = ast::A_TemplateId($1, nullptr); }
			|	q_template_id	/*template_id_with_args*/
;

p_typename_id: /*id NTY	{ $$ = ast::A_TemplateId($1, nullptr) }
				|*/	id YTT	{ $$ = ast::A_TemplateId($1, nullptr) }
				|	typename_id
				|	'~' id YTY	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, NULL)); }
				|	'~' id NTY	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, NULL)); }
				|	'~' id YTT	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, NULL)); }
;

q_typename_id: id YTY { $$ = ast::A_TemplateId($1, NULL); }
				|	id_ctor YTY 	{ $$ = ast::A_TemplateId($1, NULL); }
				|	q_template_id
;

q_type_nested_id:	q_typename_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, NULL)
						}
					|	typename_id TWO_COLON type_nested_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, $3);

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_lastScope = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						}
;

/*
ctor_id: id CTOR YTY		{ $$ = ast::A_TemplateId($1, NULL); }
;
*/

dtor_id:		'~' id NTY	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, nullptr)); }
		|	'~' id YTY	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, nullptr)); }
		|	'~' id YTT	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, nullptr)); }
		|	'~' id CTORN NTY	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, nullptr)); }
		|	'~' id CTORN YTY	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, nullptr)); }
		|	'~' id CTORN YTT	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, nullptr)); }
;

dtor_nested_id:	dtor_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, nullptr)
						}
					|	typename_id TWO_COLON dtor_nested_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, $3);

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_lastScope = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						}
;

dtor_scoped_id:	dtor_nested_id
				{
				g_scopeStack2.pop();
				}
;

p_type_nested_id:	p_typename_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, nullptr)
						}
					|	typename_id TWO_COLON p_type_nested_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, $3);

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_lastScope = g_scopeStack2.top();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						}
;

non_type_nested_id:	id NTY /*  %prec SHIFT_THERE*/ { $$ = ast::A_BinopExp(@1, '::', ast::A_TemplateId($1, NULL), NULL); }
				/*	|	'~' id NTY	{ $$ = ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, NULL)) } */

			|	operator_function_id { $$ = ast::A_BinopExp(@1, '::', $1, NULL); }
		/*	|	conversion_function_id { $$ = ast::A_BinopExp(@1, '::', $1, NULL); }*/
			|	typename_id TWO_COLON non_type_nested_id
				{
					$$ = ast::A_BinopExp(@1, '::', $1, $3);

					Scope* top = g_scopeStack2.top();
					g_scopeStack2.pop();

					g_lastScope = g_scopeStack2.top();
					g_scopeStack2.pop();

					g_scopeStack2.push(top);
				}
;

conversion_nested_id:	conversion_function_id { $$ = ast::A_BinopExp(@1, '::', $1, NULL); }
							|	typename_id TWO_COLON conversion_nested_id
								{
									$$ = ast::A_BinopExp(@1, '::', $1, $3);

									Scope* top = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_lastScope = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_scopeStack2.push(top);
								}
;

p_non_type_nested_id:	id NTY /*  %prec SHIFT_THERE*/ { $$ = ast::A_BinopExp(@1, '::', ast::A_TemplateId($1, NULL), NULL); }
							|	'~' id NTY	{ $$ = ast::A_BinopExp(@1, '::', ast::A_UnopExp(@1, '~', ast::A_TemplateId($2, NULL)), NULL); }

							|	operator_function_id { $$ = ast::A_BinopExp(@1, '::', $1, NULL); }
						/*	|	conversion_function_id { $$ = ast::A_BinopExp(@1, '::', $1, NULL); } */

							|	typename_id TWO_COLON p_non_type_nested_id
								{
									$$ = ast::A_BinopExp(@1, '::', $1, $3);

									Scope* top = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_lastScope = g_scopeStack2.top();
									g_scopeStack2.pop();

									g_scopeStack2.push(top);
								}
;

/*
either_type_nested_id:	id NTY
							|	type_nested_id
;
*/

operator:	NEW_KW	{ $$ = 'new' }
			|	DELETE_KW	{ $$ = 'del' }
			|	NEW_KW '[' ']'		{ $$ = 'new[' }
			|	DELETE_KW '[' ']'		{ $$ = 'del[' }
			|	'='	{ $$ = '=' }
			|	'<'	{ $$ = '<' }
			|	'>'	{ $$ = '>' }
			|	'+'	{ $$ = '+' }
			|	'-'	{ $$ = '-' }
			|	'/'	{ $$ = '/' }
			|	'%'	{ $$ = '%' }
			|	'!'	{ $$ = '!' }
			|	'~'	{ $$ = '~' }
			|	EQUAL	{ $$ = '==' }
			|	NOT_EQUAL	{ $$ = '!=' }
			|	LEQ	{ $$ = '<=' }
			|	GEQ	{ $$ = '>=' }
			|	'(' ')'	{ $$ = '()' }
			|	'[' ']'	{ $$ = '[]' }
			|	PLUSPLUS	{ $$ = '++' }
			|	MINUSMINUS	{ $$ = '--' }
			|	BITOR	{ $$ = '|' }
			|	BITXOR	{ $$ = '^' }
			|	BITAND	{ $$ = '&' }
			|	STAR	{ $$ = '*' }
			|	ARROW	{ $$ = '->' }
			|	LSHIFT	{ $$ = '<<' }
			|	RSHIFT	{ $$ = '>>' }
			|	ASSIGN_OR	{ $$ = '|=' }
			|	ASSIGN_XOR	{ $$ = '^=' }
			|	ASSIGN_AND	{ $$ = '&=' }
			|	ASSIGN_LSHIFT	{ $$ = '<<=' }
			|	ASSIGN_RSHIFT	{ $$ = '>>=' }
			|	ASSIGN_PLUS	{ $$ = '+=' }
			|	ASSIGN_MINUS	{ $$ = '-=' }
			|	ASSIGN_MUL	{ $$ = '*=' }
			|	ASSIGN_DIV	{ $$ = '/=' }
			|	ASSIGN_MOD	{ $$ = '%=' }
;

operator_function_id:	OPERATOR_KW operator	{ $$ = ast::A_OperatorExp(@1, $2); g_scopeStack2.push(NULL); }
						/*	|	OPERATOR_KW NEW_KW '[' ']'	{ $$ = NULL; } */
						/* |	OPERATOR_KW operator '<' template_argument_list_opt '>' */
;

type_nested_id:	typename_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, NULL)
						}
					|	typename_id TWO_COLON type_nested_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, $3);

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						}
;

declarator_nested_id:	typename_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, NULL)
						}
					|	typename_id TWO_COLON
						{
							$$ = ast::A_BinopExp(@1, '::', $1, ast::A_BinopExp(@2, '::', NULL, NULL));
						}
					|	typename_id TWO_COLON type_nested_id
						{
							$$ = ast::A_BinopExp(@1, '::', $1, $3);

							Scope* top = g_scopeStack2.top();
							g_scopeStack2.pop();
							g_scopeStack2.pop();

							g_scopeStack2.push(top);
						}
;

/*
global_scope: TWO_COLON
;
*/

p_type_scoped_id:	p_type_nested_id
					{
						$$ = $1;
						g_scopeStack2.pop();
					}
					|	TWO_COLON p_type_nested_id
					{
						ASSERT(0);
						$$ = ast::A_BinopExp(@1, '::', nullptr, $2)
					}
				/*	| conversion_function_id */
;

type_scoped_id:	type_nested_id
					{
						$$ = $1;
						g_scopeStack2.pop();
					}
					|	TWO_COLON type_nested_id
					{
						ASSERT(0);
						$$ = ast::A_BinopExp(@1, '::', NULL, $2)
					} 
		/*	|	global_scope nested_id { $$ = $2 }*/
		/*	|	conversion_function_id*/
;

q_type_scoped_id:	q_type_nested_id
					{
						$$ = $1;
						g_scopeStack2.pop();
					}
				/*	|	TWO_COLON q_type_nested_id { $$ = ast::A_BinopExp(@1, '::', NULL, $2) } */
		/*	|	global_scope nested_id { $$ = $2 }*/
		/*	|	conversion_function_id*/
;

non_type_scoped_id:	non_type_nested_id
							{
								$$ = $1;
								g_scopeStack2.pop();
							}
						|	TWO_COLON non_type_nested_id
							{
								$$ = ast::A_BinopExp(@1, '::', NULL, $2);
								g_scopeStack2.pop();
							}
		/*	|	conversion_function_id*/

;

p_non_type_scoped_id:	p_non_type_nested_id
							{
								$$ = $1;
								g_scopeStack2.pop();
							}
						|	TWO_COLON p_non_type_nested_id
							{
								$$ = ast::A_BinopExp(@1, '::', NULL, $2);
								g_scopeStack2.pop();
							}
		/*	|	conversion_function_id*/

;

nested_name_specifier:	IDENTIFIER TWO_COLON
						/*	|	id_scope nested_name_specifier*/
;

nested_name_specifier_opt:	/*empty*/
								|	nested_name_specifier
;

conversion_function_id:	OPERATOR_KW
{
	g_scopeStack2Stack.push(g_scopeStack2);
	g_scopeStack2.cont.clear();
}
conversion_type_id conversion_declarator_opt
{
	g_scopeStack2 = g_scopeStack2Stack.top();
	g_scopeStack2Stack.pop();

	$$ = new ast::ConversionExp(new ast::A_TypeId($3, $4)); g_scopeStack2.push(NULL);
}
;

conversion_type_id:	CONST_KW conversion_type_id { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
						|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
						|	basic_type conversion_type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
						|	type_scoped_id	{ $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), NULL) }
;

conversion_type_id2:	CONST_KW	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
						|	CONST_KW conversion_type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
						|	basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
						|	basic_type conversion_type_id2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
;

/*
conversion_type_id:
						|	type_scoped_id
;
*/

conversion_declarator:	ptr_operator conversion_declarator_opt	{ $$ = new ast::A_PtrDeclarator(@1, $1, $2) }
;

conversion_declarator_opt:	{ $$ = NULL }
								|	conversion_declarator
;

type_id:	simple_declaration2 abstract_declarator_opt	{ $$ = new ast::A_TypeId($1, $2) }
;

function_definition:	q_simple_declaration2_opt p_non_type_scoped_id here parameter_declaration_clause ')' exception_specification_opt ctor_initializer_opt
{
								g_lastScope = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope2 = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope = g_scopeStack.top();
								g_scopeStack.pop();
}
function_body
							{
								$$ = new ast::FunDefDecl(@1, $1, new ast::A_DirectDeclaratorDeclarator(@1, ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId(@2, $2), $4, NULL)), $7, $9);
							//	LOG("ctor/dtor\n");
							}
							|	q_simple_declaration2_opt basic_type_seq q_declarator function_body
							{
								$$ = new ast::FunDefDecl(@3, Reverse($1, $2), $3, NULL, $4);
							//	LOG("basic_type\n");
							}
							|	q_simple_declaration2_opt elaborated_type_specifier q_declarator function_body
							{
								$$ = new ast::FunDefDecl(@3, Reverse($1, new ast::DeclSpecList($2, NULL)), $3, NULL, $4);
							//	LOG("elaborated\n");
							}
							|	q_simple_declaration2_opt type_scoped_id q_declarator function_body
							{
								$$ = new ast::FunDefDecl(@3, Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3, NULL, $4);
							//	LOG("type\n");
							}
							|	q_simple_declaration2_opt conversion_function_declarator function_body
							{
								$$ = new ast::FunDefDecl(@2, Reverse($1), $2, NULL, $3);
							}

/*
							|	q_simple_declaration2_opt type_scoped_id OPERATOR_KW NEW_KW function_body
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}

							|	q_simple_declaration2_opt type_scoped_id OPERATOR_KW NEW_KW '[' ']' function_body
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}
*/
;

member_function_definition:
							q_simple_declaration2_opt basic_type_seq _q_member_declarator function_body
							{
								$$ = new ast::FunDefDecl(@1, Reverse($1, $2), $3, NULL, $4);
							//	LOG("basic_type\n");
							}
							|	q_simple_declaration2_opt elaborated_type_specifier _q_member_declarator function_body
							{
								$$ = new ast::FunDefDecl(@1, Reverse($1, new ast::DeclSpecList($2, NULL)), $3, NULL, $4);
							//	LOG("elaborated\n");
							}
							|	q_simple_declaration2_opt q_type_scoped_id _q_member_declarator function_body
							{
								$$ = new ast::FunDefDecl(@1, Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3, NULL, $4);
							//	LOG("type\n");
							}
							|	q_simple_declaration2_opt conversion_function_declarator function_body
							{
								$$ = new ast::FunDefDecl(@1, Reverse($1), $2, NULL, $3);
							//	LOG("type\n");
							}
							|	q_simple_declaration2_opt '<' q_type_scoped_id '(' parameter_declaration_clause ')' exception_specification_opt ctor_initializer_opt function_body
							{
								$$ = new ast::FunDefDecl(@2, $1, new ast::A_DirectDeclaratorDeclarator(@1, ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId(@3, $3), $5, NULL)), $8, $9);
							//	LOG("ctor\n");
								ASSERT(g_scopeStack2.cont.size() == 0);
								
							}
							|	q_simple_declaration2_opt dtor_scoped_id '(' parameter_declaration_clause ')' exception_specification_opt ctor_initializer_opt function_body
							{
								$$ = new ast::FunDefDecl(@1, $1, new ast::A_DirectDeclaratorDeclarator(@1, ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId(@2, $2), $4, NULL)), $7, $8);
							//	LOG("ctor\n");
							}

/*
							|	q_simple_declaration2_opt q_type_scoped_id OPERATOR_KW NEW_KW function_body
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}

							|	q_simple_declaration2_opt q_type_scoped_id OPERATOR_KW NEW_KW '[' ']' function_body
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}
*/;

ctor_initializer: ':' mem_initializer_list	{ $$ = $2 }
;

mem_initializer_list:	mem_initializer	{ $$ = new ast::ExpressionList($1, nullptr); }
					|	mem_initializer_list ',' mem_initializer 	{ $$ = new ast::ExpressionList($3, $1); }
;

mem_initializer:		mem_initializer_id '(' expression_list_opt ')'	{ $$ = new ast::CallExp(@1, $1, $3) }

mem_initializer_id:	non_type_scoped_id
				|	type_scoped_id
;

ctor_initializer_opt:	{ $$ = nullptr }
					|	ctor_initializer
;

function_body: '{'
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
					}
					statement_seq_opt '}'
					{
						g_pScope2 = g_scopeStack.top();
						g_scopeStack.pop();

						g_pScope = g_scopeStack.top();
						g_scopeStack.pop();
					}
					{ $$ = new ast::CompoundStm(@1, @4, $3) }
;

compound_statement:	'{' statement_seq_opt '}' { $$ = new ast::CompoundStm(@1, @3, $2) }
;

statement_seq_opt:	{ $$ = NULL }
						|	statement_seq
;

simple_declaration:	simple_declaration2 declarator/*init_declarator_list_opt*/	{ $$ = new ast::A_SimpleDeclaration(NULL/*$1*/, NULL/*$2*/) }
					/*	|	type_scoped_id*/
;

here:	'('
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

						}
;

_simple_declaration:	q_simple_declaration2_opt p_non_type_scoped_id here parameter_declaration_clause ')' exception_specification_opt
							{
								g_lastScope = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope2 = g_scopeStack.top();
								g_scopeStack.pop();

								g_pScope = g_scopeStack.top();
								g_scopeStack.pop();

								//g_pScope2 = g_pScope;

								$$ = new ast::A_SimpleDeclaration($1? @1: @2, $1, new ast::InitDeclaratorList(new ast::InitDeclarator(new ast::A_DirectDeclaratorDeclarator(@1, ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId(@2, $2), $4, NULL))), NULL));
								LOG("ctor/dtor\n");
							}
							|	q_simple_declaration2_opt basic_type_seq q_init_declarator_list_opt
							{
								$$ = new ast::A_SimpleDeclaration($1? @1: @2, Reverse($1, $2), $3);
							//	LOG("basic_type\n");
							}
							|	q_simple_declaration2_opt elaborated_type_specifier q_init_declarator_list_opt
							{
								$$ = new ast::A_SimpleDeclaration($1? @1: @2, Reverse($1, new ast::DeclSpecList($2, NULL)), $3);
							//	LOG("elaborated\n");
							}
							|	q_simple_declaration2_opt type_scoped_id q_init_declarator_list_opt
							{
								$$ = new ast::A_SimpleDeclaration($1? @1: @2, Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
							//	LOG("type\n");
							}
/*
							|	q_simple_declaration2_opt type_scoped_id OPERATOR_KW NEW_KW
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}

							|	q_simple_declaration2_opt type_scoped_id OPERATOR_KW NEW_KW '[' ']'
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}
*/;

_member_declaration:	q_simple_declaration2_opt basic_type_seq q_member_declarator_list
							{
								$$ = new ast::A_SimpleDeclaration(@1, Reverse($1, $2), Reverse($3));
							//	LOG("basic_type\n");
							}
							|	q_simple_declaration2_opt elaborated_type_specifier q_member_declarator_list_opt
							{
								$$ = new ast::A_SimpleDeclaration(@1, Reverse($1, new ast::DeclSpecList($2, NULL)), Reverse($3));
							//	LOG("elaborated\n");
							}
							|	q_simple_declaration2_opt q_type_scoped_id q_member_declarator_list
							{
								$$ = new ast::A_SimpleDeclaration(@1, Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), Reverse($3));
							//	LOG("type\n");
							}
							|	q_simple_declaration2_opt conversion_function_declarator
							{
								$$ = new ast::A_SimpleDeclaration(@1, Reverse($1), new ast::InitDeclaratorList(new ast::InitDeclarator($2), NULL));
							}
							|	q_simple_declaration2_opt '<' q_type_scoped_id '(' parameter_declaration_clause ')' exception_specification_opt
							{
								$$ = new ast::A_SimpleDeclaration(@1, $1, new ast::InitDeclaratorList(new ast::InitDeclarator(new ast::A_DirectDeclaratorDeclarator(@1, ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId(@2, $3), $5, NULL))), NULL));
							//	LOG("ctor\n");
							}
							|	q_simple_declaration2_opt dtor_scoped_id '(' parameter_declaration_clause ')' exception_specification_opt
							{
								$$ = new ast::A_SimpleDeclaration(@1, $1, new ast::InitDeclaratorList(new ast::InitDeclarator(new ast::A_DirectDeclaratorDeclarator(@1, ast::A_DirectDeclaratorParen(ast::A_DirectDeclaratorId(@2, $2), $4, NULL))), NULL));
							//	LOG("ctor\n");
							}

/*
							|	q_simple_declaration2_opt q_type_scoped_id OPERATOR_KW NEW_KW
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}

							|	q_simple_declaration2_opt q_type_scoped_id OPERATOR_KW NEW_KW '[' ']'
							{
							//	$$ = new ast::A_SimpleDeclaration(Reverse($1, new ast::DeclSpecList(new ast::A_NameType(@2, $2), NULL)), $3);
								LOG("type\n");
							}
*/
;

basic_type_seq:	basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
					|	basic_type basic_type_seq2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;

basic_type_seq2:		basic_type	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
				|	basic_type basic_type_seq2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
				|	CONST_KW	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
				|	CONST_KW basic_type_seq2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
				|	VOLATILE_KW	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), NULL) }
				|	VOLATILE_KW basic_type_seq2	{ $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
;

q_simple_declaration2_opt:	{ $$ = nullptr }
						|	q_simple_declaration2
;

q_simple_declaration2:	CONST_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), NULL) }
					|	VOLATILE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), NULL) }
					|	INLINE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), NULL) }
					|	VIRTUAL_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), NULL) }
					|	STATIC_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), NULL) }
					|	TYPEDEF_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), NULL) }
					|	CONSTEXPR_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONSTEXPR), NULL) }
					|	EXTERN_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXTERN), NULL) }
					|	EXPLICIT_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXPLICIT), NULL) }
					|	FRIEND_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_FRIEND), NULL) }
					|	__DECLSPEC_KW '(' declspeclist_opt ')' { $$ = new ast::DeclSpecList(new ast::A_DeclSpecExtModifier(@1, Reverse($3)), NULL) }
					|	q_simple_declaration2 CONST_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $1) }
					|	q_simple_declaration2 VOLATILE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $1) }
					|	q_simple_declaration2 INLINE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $1) }
					|	q_simple_declaration2 VIRTUAL_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), $1) }
					|	q_simple_declaration2 STATIC_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), $1) }
					|	q_simple_declaration2 TYPEDEF_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $1) }
					|	q_simple_declaration2 CONSTEXPR_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONSTEXPR), $1) }
					|	q_simple_declaration2 EXTERN_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXTERN), $1) }
					|	q_simple_declaration2 EXPLICIT_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXPLICIT), $1) }
					|	q_simple_declaration2 FRIEND_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_FRIEND), $1) }
					|	q_simple_declaration2 __DECLSPEC_KW '(' declspeclist_opt ')' { $$ = new ast::DeclSpecList(new ast::A_DeclSpecExtModifier(@1, Reverse($4)), $1) }
;

declspec_item:	IDENTIFIER	{ $$ = new ast::A_DeclSpecExt($1) }
			|	IDENTIFIER '(' INTEGER_LITERAL ')' { $$ = new ast::A_DeclSpecExt($1, $3) }

declspeclist:	declspec_item	{ $$ = new ast::A_DeclSpecExtList($1, nullptr); }
			|	declspeclist declspec_item	{ $$ = new ast::A_DeclSpecExtList($2, $1); }
;

declspeclist_opt:	{ $$ = nullptr }
				|	declspeclist
;

_simple_declaration2:	CONST_KW _simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
					|	VOLATILE_KW _simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
					|	TYPEDEF_KW _simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
				/*	|	INLINE_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), NULL) }  */
					|	INLINE_KW _simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
				/*	|	VIRTUAL_KW { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), NULL) } */
					|	VIRTUAL_KW _simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VIRTUAL), $2) }
					|	EXTERN_KW _simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXTERN), $2) }
					|	STATIC_KW _simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), $2) }
					|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
					|	basic_type _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
				/*	|	elaborated_type_specifier { $$ = new ast::DeclSpecList($1, nullptr) } */
				/*	|	elaborate_type simple_declaration4  { $$ = new ast::DeclSpecList($1, $2) }
					*/
					|	type_scoped_id { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), NULL) }
				/*	|	scoped_id simple_declaration4 { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), $2) }*/
;

_simple_declaration3:	CONST_KW _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
					|	VOLATILE_KW _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
					|	TYPEDEF_KW _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
					|	CONSTEXPR_KW _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::CONSTEXPR_KW), $2) }
					|	INLINE_KW _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
					|	EXTERN_KW _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXTERN), $2) }
					|	STATIC_KW _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), $2) }
					|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), NULL) }
					|	basic_type _simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;

simple_declaration2:		CONST_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
					|	VOLATILE_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
					|	TYPEDEF_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
					|	CONSTEXPR_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONSTEXPR), $2) }
					|	INLINE_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
					|	EXTERN_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXTERN), $2) }
					|	STATIC_KW simple_declaration2 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), $2) }
					|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), nullptr) }
					|	basic_type simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
					|	elaborated_type_specifier { $$ = new ast::DeclSpecList($1, nullptr) }
				/*	|	elaborate_type simple_declaration4  { $$ = new ast::DeclSpecList($1, $2) }
					*/
					|	type_scoped_id { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), nullptr) }
				/*	|	scoped_id simple_declaration4 { $$ = new ast::DeclSpecList(new ast::A_NameType(@1, $1), $2) }*/
;

simple_declaration3:		CONST_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_CONST), $2) }
					|	VOLATILE_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_VOLATILE), $2) }
					|	TYPEDEF_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_TYPEDEF), $2) }
					|	INLINE_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_INLINE), $2) }
					|	EXTERN_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_EXTERN), $2) }
					|	STATIC_KW simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecModifier(@1, ast::A_STATIC), $2) }
					|	basic_type { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), nullptr) }
					|	basic_type simple_declaration3 { $$ = new ast::DeclSpecList(new ast::A_DeclSpecBasicType(@1, $1), $2) }
;


elaborated_type_specifier:	class_specifier
						|	enum_specifier
						|	TYPENAME_KW scoped_id
						{
							$$ = new ast::A_NameType(@1, $2);
						}
						|	class_head
						{
							$$ = new ast::A_Class(@1, $1);
							g_pClass = nullptr;	// ??
						//	Do_elaborated_class((ast::A_Class*)$$)
						}
;

member_specification:	member_declaration member_specification_opt { $$ = new ast::A_MemberDecl($1, $2) }
					|	access_specifier ':' member_specification_opt { $$ = new ast::A_MemberAccessSpec($1, $3) }
;

member_declaration:	member_declaration_decl
				|	member_function_definition
				|	member_template_declaration
;

member_declaration_decl:	_member_declaration ';'	{ $$ = $1, Do(nullptr, $$) }
;

member_declarator_list:	member_declarator { $$ = new ast::A_DeclaratorList($1, nullptr) }
					|	member_declarator_list ',' member_declarator { $$ = new ast::A_DeclaratorList($3, $1) }
;

member_declarator_list_opt:	{ $$ = nullptr }
						|	member_declarator_list
;

member_declarator:	member_declarator_ constant_initializer_opt
						|	non_type_nested_id ':' constant_expression { $$ = new ast::A_BitfieldDeclarator($1, $3); g_scopeStack2.pop(); }
						|	type_nested_id ':' constant_expression { $$ = new ast::A_BitfieldDeclarator($1, $3); g_scopeStack2.pop(); }
;

q_member_declarator_list:	q_member_declarator { $$ = new ast::InitDeclaratorList($1, nullptr) }
						|	q_member_declarator_list ',' q_member_declarator { $$ = new ast::InitDeclaratorList($3, $1) }
;

q_member_declarator_list_opt:	{ $$ = nullptr }
							|	q_member_declarator_list
;

q_member_declarator:	_q_member_declarator constant_initializer_opt { $$ = new ast::InitDeclarator($1, $2) }
						|	non_type_nested_id ':' constant_expression { $$ = new ast::InitDeclarator(new ast::A_BitfieldDeclarator(@1, $1, $3)); g_scopeStack2.pop(); }
						|	type_nested_id ':' constant_expression { $$ = new ast::InitDeclarator(new ast::A_BitfieldDeclarator(@1, $1, $3)); g_scopeStack2.pop(); }
;

member_specification_opt: { $$ = nullptr }
						| member_specification
;

constant_initializer_opt:	{ $$ = nullptr }
						|	'=' constant_expression	{ $$ = new ast::Initializer($2); }
;

/*Declarators*/

statement_declarator_list_opt:	{ $$ = nullptr }
							|	statement_declarator_list { $$ = $1}
;

statement_declarator_list:	statement_declarator { $$ = new ast::InitDeclaratorList($1, nullptr) }
						|	statement_declarator_list ',' statement_declarator { $$ = new ast::InitDeclaratorList($3, $1) }
;

init_declarator_list:	init_declarator { $$ = new ast::InitDeclaratorList($1, nullptr) }
					|	init_declarator_list ',' init_declarator { $$ = new ast::InitDeclaratorList($3, $1) }
;

init_declarator_list_opt:	{ $$ = nullptr }
						|	init_declarator_list { $$ = $1}
;

init_declarator:	declarator
					|	declarator initializer
;

statement_declarator:	_q_member_declarator initializer	{ $$ = new ast::InitDeclarator($1, $2) }
					|	_q_member_declarator{ $$ = new ast::InitDeclarator($1, nullptr) }
;

q_init_declarator_list:	q_init_declarator { $$ = new ast::InitDeclaratorList($1, nullptr) }
					|	q_init_declarator_list ',' q_init_declarator { $$ = new ast::InitDeclaratorList($3, $1) }
;

q_init_declarator_list_opt:	{ $$ = nullptr }
						|	q_init_declarator_list { $$ = $1}
;

q_init_declarator:	q_declarator	{ $$ = new ast::InitDeclarator($1, nullptr) }
				|	q_declarator initializer	{ $$ = new ast::InitDeclarator($1, $2) }
;

initializer:	'=' initializer_clause	{ $$ = new ast::Initializer($2); }
				|	BITAND '(' expression_list ')'	{ $$ = new ast::Initializer($3); }
;

COMMA_opt:	/*empty*/
			|	','
;

initializer_clause:	assignment_expression
						|	'{' initializer_list COMMA_opt '}'	{ $$ = new ast::InitClauseExp(Reverse($2)); }
						|	'{' '}'	{ $$ = new ast::InitClauseExp(NULL); }
;

initializer_list:		initializer_clause	{ $$ = new ast::ExpressionList($1, NULL); }
						|	initializer_list ',' initializer_clause	{ $$ = new ast::ExpressionList($3, $1) }
;

scoped_id:	type_scoped_id
			|	non_type_scoped_id
;

/*Classes*/

class_name: IDENTIFIER
			|	template_id_with_args
;

class_head:	class_key class_specifier_ext_list_opt non_type_scoped_id	{ $$ = new ast::A_ClassHead(@1, $1, $2, $3); Do_class_specifier_head($$);}
		|	class_key class_specifier_ext_list_opt q_type_scoped_id	{ $$ = new ast::A_ClassHead(@1, $1, $2, $3); Do_class_specifier_head($$);}
;

/*
class_head:		class_key { $$ = new ast::A_ClassHead(@1, $1, NULL, NULL) }
				|	class_head2 base_clause_opt
				{
				$$ = new ast::A_ClassHead(@1, $1, $2, $3);
				Do($$);
				}
;
*/

class_specifier_ext_list_opt:	{ $$ = nullptr }
							|	class_specifier_ext_list
;

class_specifier_ext_list:	class_specifier_ext		{ $$ = new ast::DeclSpecList($1, nullptr); }
						|	class_specifier_ext_list class_specifier_ext	{ $$ = new ast::DeclSpecList($2, $1); }
;

class_specifier_ext: __DECLSPEC_KW '(' declspeclist_opt ')' { $$ = new ast::A_DeclSpecExtModifier(@1, Reverse($3)); }
;

attribute_specification:	'[' mem_initializer ']' { $$ = $2 }
;

attribute_specification_list_opt:	{ $$ = nullptr }
								|	attribute_specification_list
;

attribute_specification_list:	attribute_specification	{	 $$ = new ast::ExpressionList($1, nullptr) }
									|	attribute_specification_list attribute_specification	{ $$ = new ast::ExpressionList($2, $1) }
;

class_specifier:	class_head base_clause_opt '{'
						{
							g_scopeStack.push(g_pScope);
							g_scopeStack.push(g_pScope2);

							ast::A_ClassDef* classdef = new ast::A_ClassDef(@1, $1, $2, nullptr);
							g_classes.push(classdef);

							Do(classdef);

							g_pScope = g_pClass->m_pScope;
							g_pScope2 = g_pClass->m_pScope;

							g_pClassStack.push(g_pClass2);
							g_pClass2 = g_pClass;
						}
						member_specification_opt '}'
						{
							g_pClass2 = g_pClassStack.top();
							g_pClassStack.pop();

							ast::A_ClassDef* classdef = g_classes.top();
							g_classes.pop();

							classdef->m_memberSpec = $5;

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

						//	ASSERT(g_pScope);
						//	g_pScope2 = g_pScope;
							$$ = classdef;

							ASSERT(g_scopeStack2.cont.size() == 0);
						}
						|	class_key '{'
						{
							g_scopeStack.push(g_pScope);
							g_scopeStack.push(g_pScope2);

							ast::A_ClassDef* classdef = new ast::A_ClassDef(@1, new ast::A_ClassHead(@1, $1, NULL, NULL), NULL, NULL);
							Do_class_specifier_head(classdef->m_head);

							g_classes.push(classdef);

							Do(classdef);

							g_pScope = g_pClass->m_pScope;
							g_pScope2 = g_pClass->m_pScope;

							g_pClassStack.push(g_pClass2);
							g_pClass2 = g_pClass;
						}
						member_specification_opt '}'
						{
							g_pClass2 = g_pClassStack.top();
							g_pClassStack.pop();

							ast::A_ClassDef* classdef = g_classes.top();
							g_classes.pop();

							classdef->m_memberSpec = $4;

							g_pScope2 = g_scopeStack.top();
							g_scopeStack.pop();

							g_pScope = g_scopeStack.top();
							g_scopeStack.pop();

							ASSERT(g_pScope);
						//	g_pScope2 = g_pScope;

							$$ = classdef;

							ASSERT(g_scopeStack2.cont.size() == 0);
						}
;

class_key:	CLASS_KW { $$ = ClassKey_class }
		|	STRUCT_KW { $$ = ClassKey_struct }
		|	UNION_KW { $$ = ClassKey_union }
		|	INTERFACE_KW { $$ = ClassKey_interface }
;

access_specifier:	PRIVATE_KW { $$ = AccessSpec_Private }
				|	PROTECTED_KW { $$ = AccessSpec_Protected }
				|	PUBLIC_KW { $$ = AccessSpec_Public }
;

access_specifier_opt:	{ $$ = AccessSpec_Unspecified }
						|	access_specifier
;

enum_specifier:	ENUM_KW identifier_opt '{' enumerator_list_opt '}' { $$ = new ast::A_Enum(@1, $2, NULL, $4) }
			|	ENUM_KW identifier_opt ':' basic_type_seq '{' enumerator_list_opt '}' { $$ = new ast::A_Enum(@1, $2, $4, $6) }
/*			|	ENUM_KW IDENTIFIER TODO enum_base_opt { $$ = NULL }*/
;

/*
enum_base_opt: { $$ = NULL }
			|	enum_base
;

enum_base: ':' simple_declaration2
;
*/

enumerator_list:	enumerator_definition { $$ = new ast::EnumDefList($1, NULL) }
					|	enumerator_list ',' { $$ = $1 }
					|	enumerator_list ',' enumerator_definition { $$ = new ast::EnumDefList($3, $1) }
;

enumerator_list_opt:	{ $$ = NULL }
						|	enumerator_list { $$ = $1 }
;

enumerator_definition:	IDENTIFIER { $$ = new ast::EnumDefinition(@1, $1, NULL) }
							|	IDENTIFIER '=' constant_expression { $$ = new ast::EnumDefinition(@1, $1, $3) }
;

basic_type:	VOID_KW	{ $$ = ast::A_VOID }
			|	BOOL_KW	{ $$ = ast::A_BOOL }
			|	CHAR_KW	{ $$ = ast::A_CHAR }
			|	WCHAR_T_KW	{ $$ = ast::A_WCHAR_T }
			|	INT_KW	{ $$ = ast::A_INT }
			|	SHORT_KW	{ $$ = ast::A_SHORT }
			|	LONG_KW	{ $$ = ast::A_LONG }
			|	SIGNED_KW	{ $$ = ast::A_SIGNED }
			|	UNSIGNED_KW	{ $$ = ast::A_UNSIGNED }
			|	FLOAT_KW	{ $$ = ast::A_FLOAT }
			|	DOUBLE_KW	{ $$ = ast::A_DOUBLE }
			|	__INT8_KW	{ $$ = ast::A___INT8 }
			|	__INT16_KW	{ $$ = ast::A___INT16 }
			|	__INT32_KW	{ $$ = ast::A___INT32 }
			|	__INT64_KW	{ $$ = ast::A___INT64 }
			|	__FLOAT32_KW	{ $$ = ast::A___FLOAT32 }
			|	__FLOAT64_KW	{ $$ = ast::A___FLOAT64 }
;

postfix_expression:	primary_expression

						|	postfix_expression '[' expression ']' { $$ = ast::A_BinopExp(@1, '[', $1, $3) } 

					//	|	postfix_expression '(' expression_list_opt ')'	{ $$ = ast::A_CallExp(@1, $1, $3) }
						|	postfix_expression '(' expression_or_type_list_opt ')'	{ $$ = new ast::CallExp(@1, $1, $3) }

						/* covered by the above
						|	type_scoped_id '(' expression_list_opt ')'
						{
						LOG("Yrlloe\n");
						}
						*/
						|	type_scoped_id '(' expression_list_opt ')'{ $$ = new ast::InitExp(@1, $1, $3) }
						|	basic_type '(' expression_list_opt ')'{ $$ = new ast::InitBasicExp(@1, $1, $3) }

						|	postfix_expression PLUSPLUS { $$ = ast::A_PostopExp(@1, $1, '++') }
						|	postfix_expression MINUSMINUS { $$ = ast::A_PostopExp(@1, $1, '--') }

						|	postfix_expression '.' /*template_opt*/ scoped_id  { $$ = ast::A_BinopExp(@1, '.', $1, $3) }
						|	postfix_expression ARROW /*template_opt*/ scoped_id  { $$ = ast::A_BinopExp(@1, '->', $1, $3) }

						|	postfix_expression '.' /*template_opt*/ dtor_nested_id  { $$ = ast::A_BinopExp(@1, '.', $1, $3); g_scopeStack2.pop(); }
						|	postfix_expression ARROW /*template_opt*/ dtor_nested_id  { $$ = ast::A_BinopExp(@1, '->', $1, $3); g_scopeStack2.pop(); }

						|	STATIC_CAST_KW '<' type_id '>' '(' expression ')'	{ $$ = new ast::StaticCastExp($3, $6); }
						|	DYNAMIC_CAST_KW '<' type_id '>' '(' expression ')'	{ $$ = new ast::DynamicCastExp($3, $6); }
						|	CONST_CAST_KW '<' type_id '>' '(' expression ')'	{ $$ = new ast::ConstCastExp($3, $6); }
						|	REINTERPRET_CAST_KW '<' type_id '>' '(' expression ')'	{ $$ = new ast::ReinterpretCastExp($3, $6); }
						|	TYPEID_KW '(' expression ')'	{ $$ = new ast::TypeidExp($3); }
						|	TYPEID_KW '(' type_id ')'	{ $$ = new ast::TypeidExp($3); }
;

expression_list:	assignment_expression { $$ = new ast::ExpressionList($1, NULL) }
					|	expression_list ',' assignment_expression  { $$ = new ast::ExpressionList($3, $1) }
;

expression_list_opt:	{ $$ = NULL }
						|	expression_list
;

expression_or_type_list_opt:	{ $$ = NULL }
									|	expression_or_type_list
;

expression_or_type_list:	assignment_expression { $$ = new ast::ExpressionList($1, NULL) }
								|	type_id	{ $$ = new ast::ExpressionList(new ast::TypeExp($1), NULL) }
								|	expression_list ',' assignment_expression { $$ = new ast::ExpressionList($3, $1) }
;

unary_expression:	postfix_expression
					|	PLUSPLUS cast_expression { $$ = ast::A_UnopExp(@1, '++', $2) }
					|	MINUSMINUS cast_expression { $$ = ast::A_UnopExp(@1, '--', $2) }
					|	STAR cast_expression { $$ = ast::A_UnopExp(@1, '*', $2)}
					|	BITAND cast_expression { $$ = ast::A_UnopExp(@1, '&', $2)}
					|	'+' cast_expression { $$ = ast::A_UnopExp(@1, '+', $2)}
					|	'-' cast_expression { $$ = ast::A_UnopExp(@1, '-', $2)}
					|	'!' cast_expression { $$ = ast::A_UnopExp(@1, '!', $2)}
					|	'~' cast_expression { $$ = ast::A_UnopExp(@1, '~', $2)}
				/*	|	'~' id YTY { $$ = ast::A_UnopExp(@1, '~', $2)} */
					|	SIZEOF_KW unary_expression { $$ = new ast::SizeofExp($2) }
					|	SIZEOF_KW '(' type_id ')' { $$ = new ast::SizeofTypeExp($3) }
					|	new_expression
					|	TWO_COLON new_expression	{ $$ = ast::A_UnopExp(@1, '::', $2) }
					|	delete_expression
					|	TWO_COLON delete_expression	{ $$ = ast::A_UnopExp(@1, '::', $2) }
;

new_expression:	NEW_KW new_placement_opt new_type_id new_initializer_opt	{ $$ = new ast::NewExp(Reverse($2), $3, Reverse($4)); }
				/*	|	TWO_COLON_opt NEW_KW new_placement_opt '(' type_id ')' new_initializer_opt*/
;

new_placement:	'(' expression_list ')'	{ $$ = $2 }
;

new_placement_opt:	{ $$ = NULL }
						|	new_placement
;

new_type_id:	simple_declaration2 /*new_declarator_opt*/	{ $$ = new ast::A_TypeId($1, NULL/*$2*/) }
;

new_declarator:	direct_new_declarator	 { $$ = new ast::A_DirectDeclaratorDeclarator(@1, $1) }
					|	ptr_operator new_declarator_opt	 { $$ = new ast::A_PtrDeclarator($1, $2) }
					
;

new_declarator_opt:	{ $$ = NULL }
						|	new_declarator
;

direct_new_declarator:	'[' expression ']'
							|	direct_new_declarator '[' constant_expression ']'
;

new_initializer:	'(' expression_list_opt ')'	{ $$ = $2 }
;

new_initializer_opt:	{ $$ = NULL }
						|	new_initializer
;

delete_expression:	DELETE_KW cast_expression	{ $$ = new ast::DeleteExp($2) }
						|	DELETE_KW '[' ']' cast_expression { $$ = new ast::DeleteExp($4) }
;

cast_expression:	unary_expression
					|	'(' type_id ')' cast_expression	{ $$ = ast::A_CastExp($2, $4) }
;

pm_expression:	cast_expression
				|	pm_expression DOT_STAR cast_expression
				|	pm_expression ARROW_STAR cast_expression 
;

multiplicative_expression:		pm_expression
								|		multiplicative_expression STAR pm_expression { $$ = ast::A_BinopExp(@1, '*', $1, $3) }
								|		multiplicative_expression '/' pm_expression { $$ = ast::A_BinopExp(@1, '/', $1, $3) }
								|		multiplicative_expression '%' pm_expression { $$ = ast::A_BinopExp(@1, '%', $1, $3) }
;

additive_expression:	multiplicative_expression
						|	additive_expression '+' multiplicative_expression { $$ = ast::A_BinopExp(@1, '+', $1, $3) }
						|	additive_expression '-' multiplicative_expression { $$ = ast::A_BinopExp(@1, '-', $1, $3) }
;

shift_expression:	additive_expression
					|	shift_expression LSHIFT additive_expression { $$ = ast::A_BinopExp(@1, '<<', $1, $3) }
					|	shift_expression RSHIFT additive_expression { $$ = ast::A_BinopExp(@1, '>>', $1, $3) }
;

relational_expression:	shift_expression 
							|	relational_expression '<' shift_expression { $$ = ast::A_BinopExp(@1, '<', $1, $3) }
							|	relational_expression '>' shift_expression { $$ = ast::A_BinopExp(@1, '>', $1, $3) }
							|	relational_expression LEQ shift_expression { $$ = ast::A_BinopExp(@1, '<=', $1, $3) }
							|	relational_expression GEQ shift_expression { $$ = ast::A_BinopExp(@1, '>=', $1, $3) }
;

equality_expression:	relational_expression
						|	equality_expression EQUAL relational_expression { $$ = ast::A_BinopExp(@1, '==', $1, $3) }
						|	equality_expression NOT_EQUAL relational_expression { $$ = ast::A_BinopExp(@1, '!=', $1, $3) }
;

and_expression:	equality_expression
					|	and_expression BITAND equality_expression { $$ = ast::A_BinopExp(@1, '&', $1, $3) }
;

exclusive_or_expression:	and_expression
								|	exclusive_or_expression BITXOR and_expression { $$ = ast::A_BinopExp(@1, '^', $1, $3) }
;

inclusive_or_expression:	exclusive_or_expression
								|	inclusive_or_expression BITOR exclusive_or_expression { $$ = ast::A_BinopExp(@1, '|', $1, $3) }
;

logical_and_expression:	inclusive_or_expression
							|	logical_and_expression LAND inclusive_or_expression	{ $$ = ast::A_BinopExp(@1, '&&', $1, $3) }
;

logical_or_expression: logical_and_expression
							|	logical_or_expression LOR logical_and_expression	{ $$ = ast::A_BinopExp(@1, '||', $1, $3) }
;

conditional_expression:	logical_or_expression
							|	logical_or_expression '?' expression ':' assignment_expression { $$ = ast::A_BinopExp(@1, '?', $1, ast::A_BinopExp(@3, ':', $3, $5)) }
;

assignment_operator:	'='	{ $$ = '=' }
						|	ASSIGN_PLUS	{ $$ = '+=' }
						|	ASSIGN_MINUS	{ $$ = '-=' }
						|	ASSIGN_OR	{ $$ = '|=' }
						|	ASSIGN_XOR	{ $$ = '^=' }
						|	ASSIGN_AND	{ $$ = '&=' }
						|	ASSIGN_MUL	{ $$ = '*=' }
						|	ASSIGN_DIV	{ $$ = '/=' }
						|	ASSIGN_MOD	{ $$ = '%=' }
						|	ASSIGN_LSHIFT	{ $$ = '<<=' }
						|	ASSIGN_RSHIFT	{ $$ = '>>=' }
;

assignment_expression:	conditional_expression
							|	logical_or_expression assignment_operator assignment_expression { $$ = ast::A_BinopExp(@1, $2, $1, $3) }
							|	throw_expression
;

assignment_expression_opt:	{ $$ = NULL }
								|	assignment_expression
;

throw_expression: THROW_KW assignment_expression_opt	{ $$ = new ast::ThrowExp($2) }
;

expression:	assignment_expression
			|	expression ',' assignment_expression { $$ = ast::A_BinopExp(@1, ',', $1, $3) }
;

expression_opt:	{ $$ = NULL }
					|	expression
;

constant_expression:	conditional_expression
;

constant_expression_opt:	{ $$ = NULL }
								|	conditional_expression
;

/*******/

template_argument_relational_expression:	shift_expression 
							|	template_argument_relational_expression '<' shift_expression { $$ = ast::A_BinopExp(@1, '<', $1, $3) }
						/*	|	relational_expression '>' shift_expression { $$ = ast::A_BinopExp(@1, '>', $1, $3) } */
							|	template_argument_relational_expression LEQ shift_expression { $$ = ast::A_BinopExp(@1, '<=', $1, $3) }
							|	template_argument_relational_expression GEQ shift_expression { $$ = ast::A_BinopExp(@1, '>=', $1, $3) }
;

template_argument_equality_expression:	template_argument_relational_expression
						|	template_argument_equality_expression EQUAL template_argument_relational_expression { $$ = ast::A_BinopExp(@1, '==', $1, $3) }
						|	template_argument_equality_expression NOT_EQUAL template_argument_relational_expression { $$ = ast::A_BinopExp(@1, '!=', $1, $3) }
;

template_argument_and_expression:	template_argument_equality_expression
											|	template_argument_and_expression BITAND template_argument_equality_expression { $$ = ast::A_BinopExp(@1, '&', $1, $3) }
;

template_argument_exclusive_or_expression:	template_argument_and_expression
														|	template_argument_exclusive_or_expression BITXOR template_argument_and_expression { $$ = ast::A_BinopExp(@1, '^', $1, $3) }
;

template_argument_inclusive_or_expression:	template_argument_exclusive_or_expression
														|	template_argument_inclusive_or_expression BITOR template_argument_exclusive_or_expression { $$ = ast::A_BinopExp(@1, '|', $1, $3) }
;

template_argument_logical_and_expression:	template_argument_inclusive_or_expression
													|	template_argument_logical_and_expression LAND template_argument_inclusive_or_expression
;

template_argument_logical_or_expression: template_argument_logical_and_expression
													|	template_argument_logical_or_expression LOR template_argument_logical_and_expression
;

template_argument_conditional_expression:	template_argument_logical_or_expression
							|	template_argument_logical_or_expression '?' expression ':' template_argument_constant_expression { $$ = ast::A_BinopExp(@1, '?', $1, ast::A_BinopExp(@3, ':', $3, $5)) }
;

template_argument_constant_expression:	template_argument_conditional_expression
;

template_argument_list:	template_argument	{ $$ = new ast::A_TemplateArgumentList($1, nullptr) }
					|	template_argument_list ',' template_argument { $$ = new ast::A_TemplateArgumentList($3, $1) }
;

template_argument_list_opt:	{ $$ = nullptr }
						|	template_argument_list
;

template_argument:	template_argument_constant_expression	{ $$ = new ast::A_TemplateArgument(NULL, $1) }
						|	type_id	{ $$ = new ast::A_TemplateArgument($1, nullptr) }
;

identifier_opt:	{ $$ = NULL }
					|	IDENTIFIER/* NTY
					|	IDENTIFIER YTY*/
;

/* Derived Classes */

base_clause:	':' base_specifier_list { $$ = Reverse($2) }
;

base_clause_opt:	{ $$ = NULL }
					|	base_clause
;

base_specifier_list:	base_specifier		{ $$ = new ast::A_BaseSpecifierList($1, NULL) }
						|	base_specifier_list ',' base_specifier { $$ = new ast::A_BaseSpecifierList($3, $1) }
;

base_class_name:	q_type_scoped_id
				/*	|	nested_name_specifier class_name { $$ = ast::A_BinopExp('::', $1, ast::A_IdExp($1)) }*/
;

base_specifier:	base_class_name												{	$$ = new ast::A_BaseSpecifier($1, AccessSpec_Unspecified, 0); }
					|	access_specifier base_class_name					{	$$ = new ast::A_BaseSpecifier($2, $1, 0);	}
					|	VIRTUAL_KW access_specifier_opt base_class_name		{	$$ = new ast::A_BaseSpecifier($3, $2, 1);	}
					|	access_specifier VIRTUAL_KW base_class_name			{	$$ = new ast::A_BaseSpecifier($3, $1, 2);	}
;

/* Statements */

statement:	';'	{ $$ = NULL }
			|	expression_statement
			|	declaration_statement
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

asm_definition:	__ASM_KW '(' STRING_LITERAL ')' ';'	{ $$ = new ast::AsmDefinition(@1, $3) }
;

labeled_statement:	CASE_KW constant_expression ':' statement	{ $$ = new ast::CaseStm($2, $4) }
						|	DEFAULT_KW ':' statement	{ $$ = new ast::DefaultStm($3) }
						|	id NTY ':' {g_scopeStack2.pop();} statement	{ $$ = new ast::LabelStm($1, $5); }
						|	id YTY ':' {g_scopeStack2.pop();} statement	{ $$ = new ast::LabelStm($1, $5); }
;

jump_statement:	CONTINUE_KW ';'	{ $$ = new ast::ContinueStm() }
					|	BREAK_KW ';'	{ $$ = new ast::BreakStm() }
					|	GOTO_KW IDENTIFIER ';' { $$ = new ast::GotoStm($2) }
;

/* This will give a shift/reduce conflict, the default is shift, and that's okay here */
selection_statement:	IF_KW '(' condition ')' statement { $$ = new ast::IfStm($3, $5, NULL) }
						|	IF_KW '(' condition ')' statement ELSE_KW statement { $$ = new ast::IfStm($3, $5, $7) }
						|	SWITCH_KW '(' condition ')' statement { $$ = new ast::SwitchStm($3, $5) }
;

condition:	expression	{ $$ = new ast::Condition($1) }
			|	simple_declaration2 /*type_specifier_seq*/ declarator '=' assignment_expression { $$ = new ast::Condition($1, $2, $4); }
;

iteration_statement:	WHILE_KW '(' condition ')' statement { $$ = new ast::WhileStm(@1, @5, $3, $5) }
						|	DO_KW statement WHILE_KW '(' expression ')' ';' { $$ = new ast::DoWhileStm($2, $5) }
						|	FOR_KW '(' ';' expression_opt ';' expression_opt ')' statement { $$ = new ast::ForStm(NULL, $4, $6, $8) }
						|	FOR_KW '(' expression ';' expression_opt ';' expression_opt ')' statement { $$ = new ast::ForStm(new ast::A_ExpOrDecl($3, NULL), $5, $7, $9) }
						|	FOR_KW '(' simple_declaration2 statement_declarator_list_opt ';' expression_opt ';' expression_opt ')' statement { $$ = new ast::ForStm(new ast::A_ExpOrDecl(NULL, new ast::A_SimpleDeclaration(@3, $3, Reverse($4))), $6, $8, $10) }
;

declaration_statement:	simple_declaration2 statement_declarator_list_opt ';'	{ $$ = new ast::A_DeclarationStm(new ast::A_SimpleDeclaration(@1, $1, Reverse($2))); }
							|	asm_definition	{ $$ = new ast::A_DeclarationStm($1) }

;

expression_statement:	expression ';'	{ $$ = new ast::A_ExpStm($1) }
;

return_statement: RETURN_KW ';' { $$ = new ast::ReturnStm() }
					|	RETURN_KW expression ';' { $$ = new ast::ReturnStm($2) }
;

statement_seq:	statement { $$ = new ast::A_StmList($1, NULL) }
				|	statement statement_seq { $$ = new ast::A_StmList($1, $2) }
;

/**/

prim:	FALSE_KW	 { $$ = new ast::Expression2(@1, FALSE_KW) }
	|	TRUE_KW	 { $$ = new ast::Expression2(@1, TRUE_KW) }
	|	INTEGER_LITERAL { $$ = new ast::Expression2(@1, INTEGER_LITERAL, $1) }
	|	DOUBLE_LITERAL	{ $$ = new ast::Expression2(@1, DOUBLE_LITERAL, $1) }
	|	STRING_LITERAL	{ $$ = new ast::Expression2(@1, STRING_LITERAL, $1)	}
	|	LSTRING_LITERAL { $$ = new ast::Expression2(@1, LSTRING_LITERAL) }
	|	CHAR_LITERAL	{ $$ = new ast::Expression2(@1, CHAR_LITERAL, $1) }
	|	TWO_COLON	{ $$ = new ast::Expression2(@1, TWO_COLON) }
	|	IDENTIFIER { $$ = new ast::Expression2(@1, IDENTIFIER, $1) }
	|	IDENTIFIER NTY	{ $$ = new ast::Expression2(@1, IDENTIFIER, $1) }
	|	IDENTIFIER YTY	{ $$ = new ast::Expression2(@1, IDENTIFIER, $1) }
	|	THIS_KW	{ $$ = new ast::Expression2(@1, THIS_KW) }
	|	NEW_KW	{ $$ = new ast::Expression2(@1, NEW_KW) }
	|	DELETE_KW	{ $$ = new ast::Expression2(@1, DELETE_KW) }
	|	OPERATOR_KW	{ $$ = new ast::Expression2(@1, OPERATOR_KW) }
	|	STRUCT_KW	{ $$ = new ast::Expression2(@1, STRUCT_KW) }
	|	CLASS_KW	{ $$ = new ast::Expression2(@1, CLASS_KW) }
	|	UNION_KW	{ $$ = new ast::Expression2(@1, UNION_KW) }
	|	ENUM_KW	{ $$ = new ast::Expression2(@1, ENUM_KW) }
	|	CONST_KW	{ $$ = new ast::Expression2(@1, CONST_KW) }
	|	VOLATILE_KW	{ $$ = new ast::Expression2(@1, VOLATILE_KW) }
	|	TYPEDEF_KW	{ $$ = new ast::Expression2(@1, TYPEDEF_KW) }

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

	|	PUBLIC_KW		{ $$ = new ast::Expression2(@1, PUBLIC_KW) }
	|	PROTECTED_KW		{ $$ = new ast::Expression2(@1, PROTECTED_KW) }
	|	PRIVATE_KW		{ $$ = new ast::Expression2(@1, PRIVATE_KW) }

	|	TEMPLATE_KW		{ $$ = new ast::Expression2(@1, TEMPLATE_KW) }

	|	';'				{ $$ = new ast::Expression2(@1, ';') }
	|	'(' ')'			{ $$ = new ast::Expression2(@1, '(') }
	|	'{' '}'			{ $$ = new ast::Expression2(@1, '{') }
	|	'(' primlist ')'	{ $$ = new ast::Expression2(@1, '(', $2) }
	|	'{' primlist '}'	{ $$ = new ast::Expression2(@1, '{', $2) }
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
	|	':'	{ $$ = new ast::Expression2(@1, ':') }
	|	'!'	{ $$ = new ast::Expression2(@1, '!') }
	|	EQUAL	{ $$ = new ast::Expression2(@1, EQUAL) }
	|	NOT_EQUAL	{ $$ = new ast::Expression2(@1, NOT_EQUAL) }
	|	LEQ	{ $$ = new ast::Expression2(@1, LEQ) }
	|	GEQ	{ $$ = new ast::Expression2(@1, GEQ) }
	|	','	{ $$ = new ast::Expression2(@1, ',') }
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

primlist:	prim				{ $$ = new ast::Expression2List($1, NULL) }
			|	primlist	prim { $$ = new ast::Expression2List($2, $1) }
;

primlist_opt:	{$$ = NULL}
				|	primlist
;

     %%

