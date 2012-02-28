%{

//struct PP_TokenList;

//extern PP_TokenList* tlist;

//extern PP::CPreprocessor* pPP2;
extern kwmap kwm;

extern A_Exp* g_exp;

//BOOL bLastTok = FALSE;

int GetString(int delimiter, bool bWide/*, CToken& token*/);
#if 0
{
	int line = pPP2->m_pFile->m_line;

	std::string str;

	int c2;
	while (!pPP2->_eof())
	{
		//PP::CToken* ptok = pPP->GetToken4();
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
		str += c2;
	}

	if (c2 != delimiter)
	{
		char msg[256];
		sprintf(msg, "expected end of string, started on line(%d)", line);
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

//	token.stringlen = str.length();
	cpp_lval.string_literal = strdup(str.c_str());

//	*curtok = token;

	return STRING_LITERAL;
}
#endif

int cpp_exp_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/);

#if 0
static int cpp_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/)
{
	if (!bLastTok)
		pPP2->GetToken();
	else
		bLastTok = FALSE;

	while (pPP2->curtokpp->type == PP::CToken::tok_space ||
		(pPP2->curtokpp->type == PP::CToken::tok_symbol && pPP2->curtokpp->symbol == '\n'))
	{
		pPP2->GetToken();
	}

	if (pPP2->curtokpp->type == PP::CToken::tok_ident)
	{
	//	kwmap::iterator i = kwm.find(pPP2->curtokpp->ident);
	//	if (i != kwm.end())
	//		return (*i).second;
		int kw;
		if (kwm.Lookup(ckw(pPP2->curtokpp->ident), kw))
			return kw;

	#if 0
		if (!strcmp(pPP2->curtokpp->ident, "void"))
		{
			return VOID_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "char"))
		{
			return CHAR_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "int"))
		{
			return INT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "float"))
		{
			return FLOAT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "double"))
		{
			return DOUBLE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "short"))
		{
			return SHORT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "long"))
		{
			return LONG_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__int64"))
		{
			return __INT64_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "signed"))
		{
			return SIGNED_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "unsigned"))
		{
			return UNSIGNED_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "const"))
		{
			return CONST_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "volatile"))
		{
			return VOLATILE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "extern"))
		{
			return EXTERN_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "static"))
		{
			return STATIC_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "auto"))
		{
			return AUTO_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "register"))
		{
			return REGISTER_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "enum"))
		{
			return ENUM_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "class"))
		{
			return CLASS_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "struct"))
		{
			return STRUCT_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "union"))
		{
			return UNION_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "typedef"))
		{
			return TYPEDEF_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "inline"))
		{
			return INLINE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "virtual"))
		{
			return VIRTUAL_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__cdecl"))
		{
			return __CDECL_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__stdcall"))
		{
			return __STDCALL_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__declspec"))
		{
			return __DECLSPEC_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "__asm"))
		{
			return __ASM_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "if"))
		{
			return IF_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "else"))
		{
			return ELSE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "while"))
		{
			return WHILE_KW;
		}
		else if (!strcmp(pPP2->curtokpp->ident, "typename"))
		{
			return TYPENAME_KW;
		}
		#endif
		else
		{
			cpp_lval.id = pPP2->curtokpp->ident;
			return identifier;
		}
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_integer)
	{
		cpp_lval.num = pPP2->curtokpp->int32;
		return INTEGER_LITERAL;
	}
	else if (pPP2->curtokpp->type == PP::CToken::tok_char ||
				pPP2->curtokpp->type == PP::CToken::tok_symbol)
	{
		int c = pPP2->curtokpp->symbol;

		if (c == '\'')
		{
			ASSERT(0);
		//	return GetCharacter(c, FALSE, token);
		}
		else if (c == '\"')
		{
			return GetString(c, FALSE/*, token*/);
		}
		else if (pPP2->curtokpp->symbol == '<<')
		{
			return LSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '>>')
		{
			return RSHIFT;
		}
		else if (pPP2->curtokpp->symbol == '...')
		{
			return THREE_DOTS;
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
			return identifier;
		}
	}
	else
		ASSERT(0);
#endif

	return -1;
}
#endif

void cpp_exp_error (/*YYLTYPE *llocp,*/ char const *s);
#define YYERROR_VERBOSE

#define yyfalse	0
#define yytrue		1

union YYSTYPE;

     %}

%glr-parser
%locations
%name-prefix="cpp_exp_"

%union {
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
}

%token <id> identifier
%type <id> identifier_opt
%token PLUSPLUS
%token MINUSMINUS
%token ARROW

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
%token LONG_KW
%token SIGNED_KW
%token UNSIGNED_KW
%token FLOAT_KW
%token DOUBLE_KW
%token VOID_KW
%token __INT64_KW
%token __CDECL_KW
%token __STDCALL_KW
%token __DECLSPEC_KW
%token __ASM_KW
%token __SAVEDS_KW
%token __INTERRUPT_KW
%token __CHIP_KW

%token LSHIFT
%token RSHIFT
%token TWO_COLON
%token THREE_DOTS
%token NEW_KW
%token DELETE_KW
%token OPERATOR_KW
%token <exp> SIZEOF_KW
%token <string_literal> STRING_LITERAL
%token <string_literal> LSTRING_LITERAL
%token <num> INTEGER_LITERAL

%token <exp> THIS_KW

%type <exp> qualified_id
%type <exp> unqualified_id
%type <exp> nested_name_specifier

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

%type <exp> id_expression postfix_expression primary_expression

%type <expList> expression_list
%type <expList> expression_list_opt;

%type <id> class_name;

%type <declarator> declarator
%type <declarator> init_declarator
%type <directDeclarator> direct_declarator
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

%type <declspecList> parameter_declaration_decl

%type <exp> declarator_id;

%type <declSpecifierKeyword> storage_class_specifier;
%type <declSpecifierKeyword> function_specifier;
%type <declspec> decl_specifier;
%type <declspec> decl_specifier2;
%type <declspecList> decl_specifier_seq;
%type <declspecList> decl_specifier_seq2;
%type <declspecList> decl_specifier_seq_opt;
%type <declspecList> decl_specifier_seq2_opt;

%type <declspecList> type_specifier_seq;
%type <declspecList> type_specifier_seq2;
%type <declspecList> type_specifier_seq2_opt;

%type <accessSpec> access_specifier;
%type <accessSpec> access_specifier_opt;

%type <memberSpec> member_specification
%type <memberSpec> member_specification_opt
%type <declaration> member_declaration;
%type <declaration> member_declaration_decl
%type <declaratorList> member_declarator_list
%type <declarator> member_declarator

%type <typespec> type_specifier
%type <typespec> type_specifier2
%type <typespec> elaborated_type_specifier
%type <typespec> enum_specifier
%type <typespec> class_specifier
%type <typespec> class_head
%type <typespec> simple_type_specifier
/*%type <typespec> simple_type_specifier2;*/
%type <typespec> cv_qualifier

%type <typeId> type_id

%type <classKey> class_key;

     %%

/* Expressions */

expression:	conditional_expression { g_exp = $1 }
;

conditional_expression:	logical_or_expression
				/*			|	logical_or_expression '?' expression ':' assignment_expression*/
;

literal: FALSE_KW	 { $$ = A_BoolExp(0) }
		|	TRUE_KW	 { $$ = A_BoolExp(1) }
		|	INTEGER_LITERAL { $$ = A_Int32Exp($1) }
		|	STRING_LITERAL { $$ = A_StringExp($1) }
		|	LSTRING_LITERAL { $$ = A_LStringExp($1) }
;

primary_expression:	literal
						|	THIS_KW
						|	'(' expression ')' { $$ = $2}
						|	id_expression
;

id_expression:	unqualified_id
				|	qualified_id
;

unqualified_id:/*	identifier	{ $$ = A_IdExp($1) }*/
/*	operator-function-id
	conversion-function-id
*/
					/*	'~' class_name { $$ = A_UnopExp('~', A_IdExp(@2,$2)) }
					|*/	template_id {}
;

/*
qualified_id:	TWO_COLON nested_name_specifier templateopt unqualified_id {}
				|	nested_name_specifier templateopt unqualified_id { $$ = $1 }
			/*	|	TWO_COLON identifier {}
	:: operator-function-id
	:: template-id
;
*/

qualified_id:	nested_name_specifier /*templateopt unqualified_id*/ {}
			/*	|	TWO_COLON identifier {}*/
	/*
	:: operator-function-id
	:: template-id
	*/
;

nested_name_specifier:	identifier { $$ = A_IdExp(@1, $1) }
							|	nested_name_specifier TWO_COLON identifier { $$ = A_BinopExp(@1, '::', $1, A_IdExp(@3, $3)) }
/*
							|	class_or_namespace_name TWO_COLON template nested-name-specifier
							*/
;

postfix_expression:	primary_expression
						|	postfix_expression '(' expression_list_opt ')' { $$ = A_CallExp(@1, $1, $3) } 
						|	postfix_expression PLUSPLUS { ASSERT(0) }
						|	postfix_expression MINUSMINUS { ASSERT(0) }
						|	postfix_expression '.' /*template_opt*/ id_expression { $$ = A_BinopExp(@1, '.', $1, $3) }
						|	postfix_expression ARROW /*template_opt*/ id_expression { $$ = A_BinopExp(@1, '->', $1, $3) }
					/*	|	STATIC_CAST_KW '<' type_id '>' '(' expression ')' */
;

expression_list:	assignment_expression { $$ = new A_ExpList($1, NULL) }
					|	expression_list ',' assignment_expression { $$ = new A_ExpList($3, $1) }
;

expression_list_opt:	/*empty*/ { $$ = NULL }
						|	expression_list
;

/*
multiplicative_expression:	postfix_expression
								|	multiplicative_expression '*' postfix_expression	{ $$ = A_BinopExp('*', $1, $3) }
								|	multiplicative_expression multiplicative_operator postfix_expression 	{ $$ = A_BinopExp('/', $1, $3) }
;

additive_expression:	multiplicative_expression
						|	additive_expression additive_operator multiplicative_expression
;
*/

unary_expression:	postfix_expression
					|	PLUSPLUS cast_expression { $$ = A_UnopExp(@1, '++', $2) }
					|	MINUSMINUS cast_expression  { $$ = A_UnopExp(@1, '--', $2) }
					|	'*' cast_expression { $$ = A_UnopExp(@1, '*', $2)}
					|	'&' cast_expression { $$ = A_UnopExp(@1, '&', $2)}
					|	'+' cast_expression { $$ = A_UnopExp(@1, '+', $2)}
					|	'-' cast_expression { $$ = A_UnopExp(@1, '-', $2)}
					|	'!' cast_expression { $$ = A_UnopExp(@1, '!', $2)}
					|	'~' cast_expression { $$ = A_UnopExp(@1, '~', $2)}
					|	SIZEOF_KW unary_expression {ASSERT(0)}
					|	SIZEOF_KW '(' type_id ')' {ASSERT(0)}
					/*
new-expression
delete-expression
*/
;

cast_expression:	unary_expression	%dprec 1
					|	'(' type_id ')' cast_expression %dprec 2 { $$ = A_CastExp($2, $4) }
;

pm_expression:
	cast_expression
/*	pm-expression .* cast-expression
	pm-expression ->* cast-expression
*/
;

multiplicative_expression:		pm_expression
								|		multiplicative_expression '*' pm_expression { $$ = A_BinopExp(@1, '*', $1, $3) }
								|		multiplicative_expression '/' pm_expression { $$ = A_BinopExp(@1, '/', $1, $3) }
								|		multiplicative_expression '%' pm_expression { $$ = A_BinopExp(@1, '%', $1, $3) }
;

additive_expression:	multiplicative_expression
						|	additive_expression '+' multiplicative_expression { $$ = A_BinopExp(@2, '+', $1, $3) }
						|	additive_expression '-' multiplicative_expression { $$ = A_BinopExp(@2, '-', $1, $3) }
;

shift_expression:	additive_expression
					|	shift_expression LSHIFT additive_expression { $$ = A_BinopExp(@2, '<<', $1, $3) }
					|	shift_expression RSHIFT additive_expression { $$ = A_BinopExp(@2, '>>', $1, $3) }
;

relational_expression:	shift_expression
							|	relational_expression '<' shift_expression { $$ = A_BinopExp(@2, '<', $1, $3) }
							|	relational_expression '>' shift_expression { $$ = A_BinopExp(@2, '>', $1, $3) }
	/*
	relational-expression <= shift-expression
	relational-expression >= shift-expression
	*/
;

equality_expression:
	relational_expression
/*	equality-expression == relational-expression
	equality-expression != relational-expression
*/
;

and_expression:	equality_expression
					|	and_expression '&' equality_expression { $$ = A_BinopExp(@2, '&', $1, $3) }
;

exclusive_or_expression:	and_expression
								|	exclusive_or_expression 'ˆ' and_expression { $$ = A_BinopExp(@2, '^', $1, $3) }
;

inclusive_or_expression:	exclusive_or_expression
								|	inclusive_or_expression '|' exclusive_or_expression { $$ = A_BinopExp(@2, '|', $1, $3) }
;

logical_and_expression:	inclusive_or_expression
/*logical-and-expression && inclusive-or-expression*/
;

logical_or_expression: logical_and_expression
;

assignment_operator:	'='
;

assignment_expression:	conditional_expression
							|	logical_or_expression assignment_operator assignment_expression { $$ = A_BinopExp(@2, '=', $1, $3) }
							/*|	throw-expression*/
;

/*
expression:	assignment_expression
			|	expression ',' assignment_expression {  }
;
*/

constant_expression:	conditional_expression
;

constant_expression_opt:	/*empty*/ { $$ = NULL }
								|	conditional_expression
;

/* Statements */

decl_specifier:
						FRIEND_KW { $$ = A_DeclSpecifier(A_FRIEND) }
					|	TYPEDEF_KW { $$ = A_DeclSpecifier(A_TYPEDEF) }
					|	storage_class_specifier { $$ = A_DeclSpecifier($1) }
					|	function_specifier { $$ = A_DeclSpecifier($1) }
					|	type_specifier { $$ = $1 }
;

decl_specifier2:
						FRIEND_KW { $$ = A_DeclSpecifier(A_FRIEND) }
					|	TYPEDEF_KW { $$ = A_DeclSpecifier(A_TYPEDEF) }
					|	storage_class_specifier { $$ = A_DeclSpecifier($1) }
					|	function_specifier { $$ = A_DeclSpecifier($1) }
					|	type_specifier2 {$$ = $1 }
;

storage_class_specifier:	AUTO_KW { $$ = A_AUTO }
								|	REGISTER_KW { $$ = A_REGISTER }
								|	STATIC_KW { $$ = A_STATIC }
								|	EXTERN_KW { $$ = A_EXTERN }
								|	MUTABLE_KW { $$ = A_MUTABLE }
								|	__DECLSPEC_KW '(' identifier ')' { /*TODO*/$$ = A_DECLSPEC }
;

function_specifier:	INLINE_KW
								{
								$$ = A_INLINE
								}
						|	VIRTUAL_KW { $$ = A_VIRTUAL }
						|	EXPLICIT_KW { $$ = A_EXPLICIT }
;

decl_specifier_seq:	decl_specifier								{ $$ = new A_DeclSpecList($1, NULL) }
						|	decl_specifier_seq decl_specifier	{ $$ = new A_DeclSpecList($2, $1) }
;

decl_specifier_seq2:	decl_specifier2								{ $$ = new A_DeclSpecList($1, NULL) }
						|	decl_specifier_seq2 decl_specifier2	{ $$ = new A_DeclSpecList($2, $1) }
;

decl_specifier_seq_opt: /*empty*/ { $$ = NULL }
							|	decl_specifier_seq
;

decl_specifier_seq2_opt: /*empty*/ { $$ = NULL }
							|	decl_specifier_seq2
;

simple_type_specifier:	CHAR_KW { $$ = A_SimpleType(A_CHAR) }
							|	WCHAR_T_KW { $$ = A_SimpleType(A_WCHAR_T) }
							|	BOOL_KW { $$ = A_SimpleType(A_BOOL) }
							|	SHORT_KW { $$ = A_SimpleType(A_SHORT) }
							|	INT_KW { $$ = A_SimpleType(A_INT) }
							|	__INT64_KW { $$ = A_SimpleType(A___INT64) }
							|	LONG_KW { $$ = A_SimpleType(A_LONG) }
							|	SIGNED_KW { $$ = A_SimpleType(A_SIGNED) }
							|	UNSIGNED_KW { $$ = A_SimpleType(A_UNSIGNED) }
							|	FLOAT_KW { $$ = A_SimpleType(A_FLOAT) }
							|	DOUBLE_KW { $$ = A_SimpleType(A_DOUBLE) }
							|	VOID_KW { $$ = A_SimpleType(A_VOID) }
;

/*
simple_type_specifier2: identifier { $$ = A_NameType($1) }
;
*/

type_specifier:	simple_type_specifier	{ $$ = $1 }
					|	elaborated_type_specifier { ASSERT(0) }
					|	class_specifier	{ $$ = $1 }
					|	enum_specifier { $$ = $1 }
					|	cv_qualifier	{ $$ = $1 }
;

type_specifier2:	/*elaborated_type_specifier {  }
					|	class_specifier	{ $$ = $1 }
					|*/	cv_qualifier	{ $$ = $1 }
;

elaborated_type_specifier: /*identifier {$$ = new A_Type}*/
									/*class_key nested_name_specifier*/
									TYPENAME_KW identifier/*nested_name_specifier*/ { ASSERT(0) }
;

enum_specifier: ENUM_KW identifier_opt '{' enumerator_list_opt '}' { $$ = A_Enum($2, NULL) }
;

identifier_opt:	/*empty*/ { $$ = NULL }
					|	identifier
;

enumerator_list:	enumerator_definition
					|	enumerator_list ','
					|	enumerator_list ',' enumerator_definition
;

enumerator_list_opt:	/*empty*/
						|	enumerator_list
;

enumerator_definition:	enumerator
							|	enumerator '=' constant_expression
;

enumerator:	identifier
;

/*Declarators*/

init_declarator_list:	init_declarator { $$ = new A_DeclaratorList($1, NULL) }
							|	init_declarator_list ',' init_declarator { $$ = new A_DeclaratorList($3, $1) }
;

init_declarator_list_opt:	/*empty*/ { $$ = NULL }
							|	init_declarator_list { $$ = $1}
;

init_declarator:	declarator /*initializeropt*/
;

declarator:	direct_declarator {$$ = A_DirectDeclaratorDeclarator($1) }
			|	ptr_operator declarator	{ $$ = A_PtrDeclarator($2) }
;

direct_declarator:	declarator_id { $$ = A_DirectDeclaratorId(@1, $1) }
						|	direct_declarator '(' parameter_declaration_clause ')' { $$ = A_DirectDeclaratorParen($1, $3) }
						|	direct_declarator '[' constant_expression_opt ']' { $$ = A_DirectDeclaratorArray($1, $3) }
						|	'(' declarator ')' { $$ = A_DirectDeclaratorDeclarator($2)/* printf("(declarator)")*/ }
;

declarator_id:	id_expression { $$ = $1}
			/*	|	identifier TWO_COLON nested_name_specifier {}*/
				|	TWO_COLON nested_name_specifier {}
;

type_id:	type_specifier_seq abstract_declarator_opt { $$ = new A_TypeId($1, $2) }
		|	nested_name_specifier type_specifier_seq2_opt abstract_declarator_opt { $$ = new A_TypeId(new A_DeclSpecList(A_NameType($1), $2), $3) }
;

type_specifier_seq:	type_specifier { $$ = new A_DeclSpecList($1, NULL) }
						|	type_specifier_seq type_specifier  { $$ = new A_DeclSpecList($2, $1) }
;

type_specifier_seq2:	type_specifier2 { $$ = new A_DeclSpecList($1, NULL) }
						|	type_specifier_seq2 type_specifier2  { $$ = new A_DeclSpecList($2, $1) }
;

type_specifier_seq2_opt:	/*empty*/
								|	type_specifier_seq2
;

abstract_declarator:	direct_abstract_declarator {$$ = A_DirectDeclaratorDeclarator($1) }
						|	ptr_operator abstract_declarator_opt { $$ = A_PtrDeclarator($2) }
;

abstract_declarator_opt:	/*empty*/ { $$ = NULL }
								|	abstract_declarator
;

direct_abstract_declarator:	direct_abstract_declarator_opt '(' parameter_declaration_clause ')' cv_qualifier_seq_opt /*exception-specificationopt*/ { $$ = A_DirectDeclaratorParen($1, $3) }
									|	direct_abstract_declarator_opt '[' constant_expression_opt ']' { ASSERT(0) }
									|	'(' abstract_declarator ')' { $$ = A_DirectDeclaratorDeclarator($2) }
;

direct_abstract_declarator_opt:	/*empty*/ { $$ = NULL }
										|	direct_abstract_declarator;
;

parameter_declaration_clause:	parameter_declaration_list_opt { $$ = new A_ParameterDeclarations($1, false) }
									|	parameter_declaration_list_opt THREE_DOTS { $$ = new A_ParameterDeclarations($1, true) }
									|	parameter_declaration_list ',' THREE_DOTS { $$ = new A_ParameterDeclarations($1, true) }
;

three_dots_opt:	/*empty*/
					|	THREE_DOTS
;

parameter_declaration_list:	parameter_declaration { $$ = new A_TypeIdList($1, NULL) }
									|	parameter_declaration_list ',' parameter_declaration { $$ = new A_TypeIdList($3, $1) }
;

parameter_declaration_list_opt:	/*empty*/ { $$ = NULL }
										|	parameter_declaration_list
;

parameter_declaration_decl:	decl_specifier_seq 
									|	decl_specifier_seq2 identifier decl_specifier_seq2_opt
									/*
									{
										A_DeclSpecList* declspec = new A_DeclSpecList(A_TypeSpecifier(A_NameType($2)), $1);

										A_DeclSpecList* dl = $3;
										while (dl)
										{
											declspec = new A_DeclSpecList(dl->head, declspec);
											dl = dl->tail;
										}

										$$ = declspec;
									}
									*/
									|	identifier decl_specifier_seq2_opt { /*$$ = new A_DeclSpecList(A_TypeSpecifier(A_NameType($1)), $2)*/ }
;

parameter_declaration:	parameter_declaration_decl { $$ = new A_TypeId($1, NULL) }
							|	parameter_declaration_decl '=' assignment_expression { ASSERT(0) }
							|	parameter_declaration_decl declarator { $$ = new A_TypeId($1, $2) }
							|	parameter_declaration_decl declarator '=' assignment_expression { ASSERT(0) }
							|	parameter_declaration_decl abstract_declarator { $$ = new A_TypeId($1, $2) }
							|	parameter_declaration_decl abstract_declarator '=' assignment_expression { ASSERT(0) }
							/*
							|	decl_specifier_seq abstract_declarator_opt
							|	decl_specifier_seq abstract_declarator_opt '=' assignment_expression
							*/
;

ptr_operator:	'*'
				|	'*' cv_qualifier_seq
				|	cc_qualifier
				|	cc_qualifier cv_qualifier_seq
;

cc_qualifier:	__STDCALL_KW
				|	__CDECL_KW
;

cv_qualifier:	CONST_KW { $$ = A_SimpleType(A_CONST) }
				|	VOLATILE_KW { $$ = A_SimpleType(A_VOLATILE) }
;

cv_qualifier_seq:	cv_qualifier
					|	cv_qualifier cv_qualifier_seq
;

cv_qualifier_seq_opt:	/*empty*/
							|	cv_qualifier_seq;

/*Classes*/

class_name: identifier
			|	template_id { ASSERT(0) }
;

class_specifier:	class_key identifier { $$ = A_Class(@1, $1, $2) }
					|	class_head '{' member_specification_opt '}' { $$ = $1; $$->CLASSDEF.memberSpec = $3 }
;

class_key:	CLASS_KW { $$ = A_CLASSKEY_CLASS }
			|	STRUCT_KW { $$ = A_CLASSKEY_STRUCT }
			|	UNION_KW { $$ = A_CLASSKEY_UNION }
;

access_specifier:	PRIVATE_KW { $$ = A_ACCESS_PRIVATE }
					|	PROTECTED_KW { $$ = A_ACCESS_PROTECTED }
					|	PUBLIC_KW { $$ = A_ACCESS_PUBLIC }
;

access_specifier_opt:	/*empty*/ { $$ = A_ACCESS_PROTECTED }
							|	access_specifier
;

class_head:		class_key { /*$$ = A_ClassDef(@1, $1, NULL)*/ }
				|	class_key identifier base_clause_opt { /*$$ = A_ClassDef(@1, $1, $2)*/ }
				/*
					class_key nested-name-specifier identifier base-clauseopt
					class_key nested-name-specifieropt template-id base-clauseopt
					*/
;

member_specification:	member_declaration member_specification_opt { $$ = A_MemberDecl($1, $2) }
							|	access_specifier ':' member_specification_opt { $$ = A_MemberAccessSpec($1, $3) }
;

member_declaration_decl:	';' { ASSERT(0) }
								|	decl_specifier_seq ';' { $$ = A_SimpleDeclaration($1, NULL) }
								|	decl_specifier_seq member_declarator_list ';' { $$ = A_SimpleDeclaration($1, $2) }
							/*	|	decl_specifier_seq2_opt identifier ';' { $$ = A_SimpleDeclaration(new A_DeclSpecList(A_NameType($2), $1), NULL) }
								|	decl_specifier_seq2_opt identifier decl_specifier_seq2 ';'
									{ ASSERT(0) }*/
								|	decl_specifier_seq2_opt identifier decl_specifier_seq2_opt member_declarator_list ';'
									/*{ $$ = A_SimpleDeclaration(new A_DeclSpecList(A_NameType($2), $1), $4) }*/
;

member_declaration:	member_declaration_decl
					/*	|	function_definition ';' {ASSERT(0)}*/
					/*	|	function_definition {ASSERT(0)}*/
						/*
						|	::opt nested-name-specifier templateopt unqualified-id ;
						|	using-declaration
						|	template-declaration
						*/
;

member_declarator_list:	member_declarator { $$ = new A_DeclaratorList($1, NULL) }
							|	member_declarator_list ',' member_declarator { $$ = new A_DeclaratorList($3, $1) }
;

member_declarator_list_opt:	/*empty*/
									|	member_declarator_list
;

member_declarator:	/*declarator pure_specifier_opt
						|*/	declarator constant_initializer_opt
						|	identifier_opt ':' constant_expression { $$ = NULL }
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

base_clause:	':' base_specifier_list
;

base_clause_opt:	/*empty*/
					|	base_clause
;	

base_specifier_list:	base_specifier
						|	base_specifier_list ',' base_specifier
;

base_specifier:
						/*::opt nested-name-specifieropt*/ class_name
					|	VIRTUAL_KW access_specifier_opt /*::opt nested-name-specifieropt*/ class_name
					|	access_specifier virtual_opt /*::opt nested-name-specifieropt*/ class_name
;

virtual_opt:	/*empty*/
				|	VIRTUAL_KW
;

/* Templates */

template_id:	template_name '<' /*template-argument-listopt*/ '>'
;

template_name: identifier
;

     %%

