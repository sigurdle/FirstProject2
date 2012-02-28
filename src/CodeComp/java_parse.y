%{

#define YYERROR_VERBOSE

int javalex();

void javaerror (/*YYLTYPE *llocp,*/ char const *s);

A_Class* g_CompilationUnit;

#define yyfalse	0
#define yytrue		1

%}

%glr-parser
%locations
%name-prefix="java"

%union{
int num;
char* id;
A_Ids* idlist;
char* string_literal;
A_Exp* exp;
A_ExpList* explist;
A_Stm* stm;
A_Stms* stms;
A_Class* classdecl;
A_ClassBodyDecl* classbodydecl;
A_ClassBodyDecls* classbodydecls;
A_Method* method;
}

%token <string_literal> STRING_LITERAL
%token <num> INTEGER_LITERAL
%token <id> IDENTIFIER
%token NULL_KW
%token TRUE_KW
%token FALSE_KW
%token INT_KW
%token FLOAT_KW
%token DOUBLE_KW
%token CLASS_KW
%token STATIC_KW
%token THIS_KW
%token NEW_KW
%token DELETE_KW
%token FUNCTION_KW
%token RETURN_KW
%token VOID_KW
%token IF_KW
%token ELSE_KW
%token DO_KW
%token WHILE_KW
%token FOR_KW
%token BREAK_KW
%token CONTINUE_KW
%token INSTANCEOF_KW
%token PLUSPLUS
%token MINUSMINUS
%token LOGICAL_OR
%token LOGICAL_AND
%token EQUALEQUAL

/*
%type <num> AssignmentOperator
*/

%type <id> Identifier

%type <idlist> QualifiedIdentifier
%type <exp> Literal
%type <exp> NullLiteral
%type <exp> BooleanLiteral
%type <exp> IntegerLiteral
%type <exp> Primary
//%type <exp> EqualityExpression
//%type <exp> AssignmentExpression
%type <exp> Expression
%type <exp> ParExpression

%type <explist> Arguments
%type <explist> Argument_list
%type <explist> Argument_list_opt

%type <stm> Statement
%type <stms> Block
%type <stm> BlockStatement
%type <stms> BlockStatements
%type <stm> ExpressionStatement
%type <stm> ReturnStatement

%type <classdecl> TypeDeclaration
%type <classdecl> ClassDeclaration
%type <classdecl> NormalClassDeclaration
%type <classdecl> CompilationUnit

%type <stms> MethodBody

%type <method> MethodOrFieldDecl
%type <classbodydecl> MemberDecl
%type <classbodydecl> ClassBodyDeclaration
%type <classbodydecls> ClassBody
%type <classbodydecls> ClassBodyDeclarations


%%

CompilationUnit: TypeDeclaration	{ g_CompilationUnit = $1 }
;

Identifier:	IDENTIFIER
;

QualifiedIdentifier:	Identifier	{ $$ = new A_Ids($1, NULL) }
						|	Identifier '.' QualifiedIdentifier	{ $$ = new A_Ids($1, $3) }
;

Literal:	IntegerLiteral
		|	BooleanLiteral
		|	NullLiteral
;

BooleanLiteral:	TRUE_KW	{ $$ = A_BoolExp(true) }
					|	FALSE_KW	{ $$ = A_BoolExp(false) }
;

NullLiteral:	NULL_KW	{ $$ = A_NullExp() }
;

IntegerLiteral:	INTEGER_LITERAL	{ $$ = A_Int32Exp($1) }
;

Primary:	Literal
		|	QualifiedIdentifier IdentifierSuffix_opt { /*$$ = A_QualifiedIdExp($1)*/ }
		|	ParExpression
		|	NonWildcardTypeArguments

;

IdentifierSuffix_opt:
						|	IdentifierSuffix
;

IdentifierSuffix:	Arguments
;

NonWildcardTypeArguments:
	'<' TypeList '>'
;

Type:	BasicType
	|	Identifier TypeArguments_opt
;

TypeArguments_opt:
					|	TypeArguments
;

TypeArgument:	Type
;

TypeArguments:	'<' TypeArgument_list '>'
;

TypeArgument_list:	TypeArgument
						|	TypeArgument_list ',' TypeArgument
;

Arguments:	'(' Argument_list_opt ')'	{ $$ = $2 }

Argument_list_opt:	{ $$ = NULL }
					|	Argument_list	{ $$ = $1 }
;

Argument_list: Expression	{ $$ = new A_ExpList($1, NULL) }
				|	Argument_list ',' Expression	{ $$ = new A_ExpList($3, $1) }
;

BasicType:	INT_KW
			|	FLOAT_KW
			|	DOUBLE_KW
;

TypeList:	Type
			|	TypeList ',' Type
;

/*
EqualityExpression:	PrimaryExpression
						|	EqualityExpression EQUALEQUAL PrimaryExpression	{ $$ = A_BinopExp('==', $1, $3) }
;
*/

/*
AssignmentExpression:	EqualityExpression
							|	PrimaryExpression '=' EqualityExpression	{ $$ = A_BinopExp('=', $1, $3) }
;
*/

PrefixOp:	'+'
			|	'-'
			|	'!'
			|	'~'
			|	PLUSPLUS
			|	MINUSMINUS
;

InfixOp:	'+'
		|	'-'
		|	'*'
		|	'/'
		|	'%'
		|	'<'
		|	'>'
		|	'&'
		|	'|'
		|	'^'
		|	LOGICAL_OR
		|	LOGICAL_AND
		|	EQUALEQUAL
;

ParExpression:	'(' Expression ')'	{ $$ = $2 }
;

Expression_Or_Type:	/*Expression
						|*/	Type
;

Expression3:	PrefixOp Expression3
				|	'(' Expression_Or_Type ')' Expression3
				|	Primary
;

Expression2:	Expression3
				|	Expression3 Expression2Rest
;

Expression2Rest:	Expression2Rest_part_list
					|	INSTANCEOF_KW Type
;

Expression2Rest_part: InfixOp Expression3/*	{ $$ = new Expression2Rest_part($1, $2)*/
;

Expression2Rest_part_list: Expression2Rest_part
								|	Expression2Rest_part_list Expression2Rest_part
;

Expression1:	Expression2
				|	Expression2 Expression1Rest
;

Expression1Rest: '?' Expression ':' Expression1
;

Expression:	Expression1
			|	Expression1 '=' Expression1
;

/* */

Statement:	ExpressionStatement ';'
			|	ReturnStatement
;

ExpressionStatement:	Expression	{ $$ = new A_ExpStm($1) }
;

ReturnStatement:	RETURN_KW ';'	{ $$ = new A_ReturnStm(NULL) }
					|	RETURN_KW Expression ';'	{ $$ = new A_ReturnStm($2) }
;

TypeDeclaration:	ClassDeclaration
				/*	|	InterfaceDeclaration */
;

ClassDeclaration:	NormalClassDeclaration
				/*	|	EnumDeclaration */
;

NormalClassDeclaration:	CLASS_KW Identifier ClassBody	{ $$ = A_ClassDecl($2, $3) }
;

Block:	'{' '}'						{ $$ = NULL }
		|	'{' BlockStatements '}'	{ $$ = $2 }
;

BlockStatements:	BlockStatement							{ $$ = new A_Stms($1, NULL) }
					|	BlockStatements BlockStatement	{ $$ = new A_Stms($2, $1) }
;

BlockStatement:	Statement
					|	Identifier ':' Statement	{ $$ = $3 }
;

ClassBody:	'{' '}'	{ $$ = NULL }
			|	'{' ClassBodyDeclarations '}'	{ $$ = $2 }
;

ClassBodyDeclaration:	';'					{ $$ = NULL }
							|	MemberDecl			{ $$ = $1 }
							|	Block					{ $$ = A_ClassBodyBlock(false, $1) }
							|	STATIC_KW Block	{ $$ = A_ClassBodyBlock(true, $2) }
;

ClassBodyDeclarations:	ClassBodyDeclaration	{ $$ = new A_ClassBodyDecls($1, NULL) }
							|	ClassBodyDeclarations ClassBodyDeclaration	{ $$ = new A_ClassBodyDecls($2, $1) }
;

MemberDecl:	MethodOrFieldDecl	{ $$ = A_ClassBodyMethod($1) }
			|	ClassDeclaration	{ $$ = A_ClassBodyClass($1) }
;

MethodReturnType:	Type
					|	VOID_KW
;

MethodOrFieldDecl:/*	Type Identifier VariableRest				{ $$ = NULL }
						|*/	MethodReturnType Identifier '(' FormalParameters ')' MethodBody	{ $$ = A_MethodDecl($2, $6) }
;

VariableRest:
;

FormalParameters:
;

MethodBody:	Block
;

%%
