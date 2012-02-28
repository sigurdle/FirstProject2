%{

#include "lfc/lfc.h"
#include "ecmascript_ast.h"

#define YYERROR_VERBOSE

int ecmascriptlex();
void ecmascripterror (/*YYLTYPE *llocp,*/ char const *s);

//A_ElemList* g_program;

%}

// c++
//%skeleton "lalr1.cc"
//%define namespace "System::ecma"

%locations
%name-prefix="ecmascript"

%union{
int num;
char* id;
char* string_literal;
A_Exp* exp;
A_Stm* stm;
A_StmList* stm_list;
A_Function* fun;
A_Elem* elem;
A_ElemList* elem_list;
A_VarDecl* vardecl;
A_VarDeclList* vardecl_list;
A_ExpList* exp_list;
A_IdentifierList* id_list;
}

%token <string_literal> STRING_LITERAL
%token <num> INTEGER_LITERAL
%token <id> IDENTIFIER
%token NULL_KW
%token TRUE_KW
%token FALSE_KW
%token THIS_KW
%token NEW_KW
%token DELETE_KW
%token FUNCTION_KW
%token RETURN_KW
%token VOID_KW
%token IF_KW
%token ELSE_KW
%token VAR_KW
%token DO_KW
%token WHILE_KW
%token FOR_KW
%token BREAK_KW
%token CONTINUE_KW
%token IN_KW
%token TYPEOF_KW
%token PLUSPLUS
%token MINUSMINUS
%token LOGICAL_OR
%token LOGICAL_AND
%token EQUALEQUAL
%token LEQ
%token GEQ

%type <num> AssignmentOperator

%type <id> Identifier
%type <exp> Literal
%type <exp> NullLiteral
%type <exp> BooleanLiteral
%type <exp> NumericLiteral
%type <exp> StringLiteral
%type <exp> PrimaryExpression
%type <exp> PostfixExpression
%type <exp> UnaryExpression
%type <exp> LeftHandSideExpression
%type <exp> MemberExpression
%type <exp> NewExpression
%type <exp> CallExpression
%type <exp> MultiplicativeExpression
%type <exp> AdditiveExpression
%type <exp> RelationalExpression
%type <exp> LogicalANDExpression
%type <exp> LogicalORExpression
%type <exp> ConditionalExpression
%type <exp> AssignmentExpression
%type <exp> Expression
%type <exp> Expression_opt
%type <exp_list> Arguments
%type <exp_list> ArgumentList
%type <stm> Statement
%type <stm> Block
%type <stm> ExpressionStatement
%type <stm> IfStatement
%type <stm> ReturnStatement
%type <stm> VariableStatement
%type <stm> IterationStatement
%type <stm_list> StatementList
%type <stm_list> StatementList_opt
%type <id_list> FormalParameterList
%type <id_list> FormalParameterList_opt

%type <vardecl> VariableDeclaration
%type <vardecl_list> VariableDeclarationList

%type <fun> FunctionDeclaration

%type <elem> SourceElement

%type <elem_list> FunctionBody
%type <elem_list> SourceElements

%type <elem_list> Program

%%

Program:	SourceElements	{ $$ = $1; /*g_program = $1*/ }
;

Identifier:	IDENTIFIER
;

Identifier_opt:	/* empty */
					|	Identifier
;

Literal:	NullLiteral
		|	BooleanLiteral
		|	NumericLiteral
		|	StringLiteral
;

NullLiteral:	NULL_KW { $$ = A_NullExp() }
;

BooleanLiteral:	TRUE_KW { $$ = A_BoolExp(true) }
					|	FALSE_KW { $$ = A_BoolExp(false) }
;

NumericLiteral:	INTEGER_LITERAL { $$ = A_Int32Exp($1) }
/*
	DecimalLiteral
	HexIntegerLiteral
	DecimalLiteral :: See 7.8.3
	DecimalIntegerLiteral . DecimalDigitsopt ExponentPartopt
	. DecimalDigits ExponentPartopt
	DecimalIntegerLiteral ExponentPartopt
	*/
;

StringLiteral:	STRING_LITERAL {
		$$ = new A_StringExp(new System::StringA(string_copy($1)));

/*
	int len = strlen($1);
	System::StringW* str = new System::StringW(NULL, len);
	for (int i = 0; i < len; i++)
	{
		str->begin()[i] = ($1)[i];
	}
		$$ = new A_StringWExp(str);
		*/
	}

PrimaryExpression:	THIS_KW { $$ = A_IdExp("this") }
						|	Identifier { $$ = A_IdExp($1) }
						|	Literal
					/*	|	ArrayLiteral
						|	ObjectLiteral */
						|	'(' Expression ')' { $$ = $2 }
;

AssignmentOperator:	'='	{ $$ = '=' }
;

LeftHandSideExpression:	NewExpression
							|	CallExpression
;

MemberExpression:	PrimaryExpression
					|	FunctionExpression
					|	MemberExpression '[' Expression ']'		{ ASSERT(0) }
					|	MemberExpression '.' Identifier
					{
						$$ = A_MemberExp($1, (new System::StringA(string_copy($3)))/*->ToStringW()*/)
					}
					|	NEW_KW MemberExpression Arguments		{ $$ = new A_NewExp($2, $3) }
;

NewExpression:	MemberExpression
				|	NEW_KW NewExpression { $$ = A_UnopExp('new', $2) }
;

CallExpression:	MemberExpression Arguments		{ $$ = new A_CallExp($1, $2) }
					|	CallExpression Arguments	{ $$ = new A_CallExp($1, $2) }
					|	CallExpression '[' Expression ']'	{ ASSERT(0) }
					|	CallExpression '.' Identifier	{ $$ = A_MemberExp($1, new System::StringA(string_copy($3))) }
;

Arguments:	'(' ')'	{ $$ = NULL }
			|	'(' ArgumentList ')'	{ $$ = Reverse($2) }
;

ArgumentList:	AssignmentExpression	{ $$ = new A_ExpList($1, NULL) }
				|	ArgumentList ',' AssignmentExpression	{ $$ = new A_ExpList($3, $1) }
;

PostfixExpression:	LeftHandSideExpression
						|	LeftHandSideExpression /*[no LineTerminator here]*/ PLUSPLUS	{ $$ = A_UnopExp('_++', $1) }
						|	LeftHandSideExpression /*[no LineTerminator here]*/ MINUSMINUS	{ $$ = A_UnopExp('_--', $1) }
;

UnaryExpression:	PostfixExpression
					|	DELETE_KW UnaryExpression		{ $$ = A_UnopExp('dele', $2) }
					|	VOID_KW UnaryExpression			{ $$ = A_UnopExp('void', $2) }
					|	TYPEOF_KW UnaryExpression		{ $$ = A_UnopExp('type', $2) }
					|	PLUSPLUS UnaryExpression		{ $$ = A_UnopExp('++', $2) }
					|	MINUSMINUS UnaryExpression		{ $$ = A_UnopExp('--', $2) }
					|	'+' UnaryExpression		{ $$ = A_UnopExp('+', $2) }
					|	'-' UnaryExpression		{ $$ = A_UnopExp('-', $2) }
					|	'~' UnaryExpression		{ $$ = A_UnopExp('~', $2) }
					|	'!' UnaryExpression		{ $$ = A_UnopExp('!', $2) }
;

MultiplicativeExpression:	UnaryExpression
;

AdditiveExpression:	MultiplicativeExpression
						|	AdditiveExpression '+' MultiplicativeExpression	{ $$ = A_BinopExp('+', $1, $3) }
						|	AdditiveExpression '-' MultiplicativeExpression	{ $$ = A_BinopExp('-', $1, $3) }
;

RelationalExpression:	AdditiveExpression
							|	RelationalExpression '<' AdditiveExpression	{ $$ = A_BinopExp('<', $1, $3) }
							|	RelationalExpression '>' AdditiveExpression	{ $$ = A_BinopExp('>', $1, $3) }
							|	RelationalExpression LEQ AdditiveExpression	{ $$ = A_BinopExp('<=', $1, $3) }
							|	RelationalExpression GEQ AdditiveExpression	{ $$ = A_BinopExp('>=', $1, $3) }
;

LogicalANDExpression:	RelationalExpression
;

LogicalORExpression:	LogicalANDExpression
						|	LogicalORExpression LOGICAL_OR LogicalANDExpression	{ $$ = A_BinopExp('||', $1, $3) }
;

ConditionalExpression:	LogicalORExpression	/*TODO*/ { $$ = $1 }
;

AssignmentExpression:	ConditionalExpression
							|	LeftHandSideExpression AssignmentOperator AssignmentExpression	{ $$ = A_BinopExp($2, $1, $3) }
;

Expression:	AssignmentExpression
			|	Expression ',' AssignmentExpression
;

Expression_opt:	{ $$ = NULL }
					|	Expression
;

/* Statements */

Statement:	Block
			|	VariableStatement
/*
EmptyStatement
*/
			|	ExpressionStatement
			|	IfStatement
			|	IterationStatement
/*
ContinueStatement
BreakStatement
*/
			|	ReturnStatement
	/*
WithStatement
LabelledStatement
SwitchStatement
ThrowStatement
TryStatement
*/
;

ExpressionStatement: Expression ';'	{ $$ = new A_ExpStm($1) }
;

IfStatement:	IF_KW '(' Expression ')' Statement ELSE_KW Statement	{ $$ = new A_IfStm($3, $5, $7) }
				|	IF_KW '(' Expression ')' Statement	{ $$ = new A_IfStm($3, $5, NULL) }
;

IterationStatement:	DO_KW Statement WHILE_KW '(' Expression ')' ';'
						|	WHILE_KW '(' Expression ')' Statement
						|	FOR_KW '(' Expression /* NoInopt*/ ';' Expression_opt ';' Expression_opt ')' Statement
						{
							$$ = new A_ForStm($3, $5, $7, $9);
						}
						/*
for ( var VariableDeclarationListNoIn; Expressionopt ; Expressionopt ) Statement
for ( LeftHandSideExpression in Expression ) Statement
						|	FOR_KW ( VAR_KW VariableDeclarationNoIn IN_KW Expression ) Statement
*/
;

ReturnStatement: RETURN_KW /*[no LineTerminator here]*/ Expression_opt ';' { $$ = new A_ReturnStm($2) }
;

Block:	'{' StatementList_opt '}'	{ $$ = new A_CompoundStm($2) }
;

StatementList_opt:	{ $$ = NULL }
						|	StatementList
;

StatementList:	Statement	{ $$ = new A_StmList($1, NULL) }
				|	StatementList Statement	{ $$ = new A_StmList($2, $1) }
;

VariableStatement:	VAR_KW VariableDeclarationList ';'	{ $$ = new A_VarStm($2) }
;

VariableDeclarationList:	VariableDeclaration	{ $$ = new A_VarDeclList($1, NULL) }
								|	VariableDeclarationList ',' VariableDeclaration	{ $$ = new A_VarDeclList($3, $1) }
;

VariableDeclaration:	Identifier Initialiser_opt	{ $$ = new A_VarDecl($1) }
;

Initialiser_opt:	/* empty */
					|	Initialiser
;

Initialiser : '=' AssignmentExpression
;

EmptyStatement:	';'
;

/* Functions and Programs */

FunctionDeclaration:	FUNCTION_KW Identifier '(' FormalParameterList_opt ')' '{' FunctionBody '}'	{ $$ = new A_Function(new System::StringA(string_copy($2)), Reverse($4), $7) }
;

FunctionExpression:	FUNCTION_KW /*Identifier_opt*/ '(' FormalParameterList_opt ')' '{' FunctionBody '}'
;

FormalParameterList_opt:	//{ $$ = NULL }
								|	FormalParameterList
;

FormalParameterList: Identifier	{ $$ = new A_IdentifierList(new System::StringA(string_copy($1)), NULL) }
						|	FormalParameterList ',' Identifier	{ $$ = new A_IdentifierList(new System::StringA(string_copy($3)), $1) }
;

FunctionBody:	SourceElements
;

SourceElements:	SourceElement		{ $$ = new A_ElemList($1, NULL) }
					|	SourceElements SourceElement	{ $$ = new A_ElemList($2, $1) }
;

SourceElement:	Statement	{ $$ = A_StatementElem($1) }
				|	FunctionDeclaration	{ $$ = A_FunctionElem($1) }
;

%%
