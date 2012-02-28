%{

#define YYERROR_VERBOSE

int formula_lex();
void formula_error (/*YYLTYPE *llocp,*/ char const *s);

extern sql_A_Stm* g_stm;

%}

%locations
%name-prefix="formula_"

%union{
int num;
char* id;
char* string_literal;
A_Exp* exp;
//A_Stm* stm;
//A_IdList* idlist;
}

%token <string_literal> STRING_LITERAL
%token <num> INTEGER_LITERAL
%token <id> identifier
%token OR_KW
%token AND_KW
%token MOD_KW
%token NOT_KW
%token LEQ
%token GEQ
%token EQUAL
%token NOT_EQUAL

%type <exp> primary_expression
%type <exp> unary_expression
%type <exp> multiplicative_expression
%type <exp> additive_expression
%type <exp> relational_expression
%type <exp> equality_expression
%type <exp> and_expression
%type <exp> or_expression
%type <exp> expression


%%

expression: or_expression
;

primary_expression: identifier						{ $$ = A_Id($1) }
						|	identifier '.' identifier	{ $$ = A_Binop('.', A_Id($1), A_Id($3)) }
						|	INTEGER_LITERAL				{ $$ = A_Const($1) }
						|	STRING_LITERAL					{ $$ = A_Const($1) }
						|	'(' expression ')'			{ $$ = $2 }
;

unary_expression:	primary_expression
					|	'-' primary_expression		{ $$ = A_Unop('-', $2) }
					|	NOT_KW primary_expression	{ $$ = A_Unop('!', $2) }
;

multiplicative_expression:		unary_expression
								|		multiplicative_expression '*' unary_expression		{ $$ = A_Binop('*', $1, $3) }
								|		multiplicative_expression '/' unary_expression		{ $$ = A_Binop('/', $1, $3) }
								|		multiplicative_expression MOD_KW unary_expression	{ $$ = A_Binop('%', $1, $3) }
;

additive_expression:	multiplicative_expression
						|	additive_expression '+' multiplicative_expression	{ $$ = A_Binop('+', $1, $3) }
						|	additive_expression '-' multiplicative_expression	{ $$ = A_Binop('-', $1, $3) }
;

relational_expression:	additive_expression
							|	relational_expression '<' additive_expression	{ $$ = A_Binop('>', $1, $3) }
							|	relational_expression '>' additive_expression	{ $$ = A_Binop('<', $1, $3) }
							|	relational_expression LEQ additive_expression	{ $$ = A_Binop('<=', $1, $3) }
							|	relational_expression GEQ additive_expression	{ $$ = A_Binop('>=', $1, $3) }
;

equality_expression:	relational_expression
					|	equality_expression EQUAL relational_expression			{ $$ = A_Binop('==', $1, $3) }
					|	equality_expression NOT_EQUAL relational_expression	{ $$ = A_Binop('!=', $1, $3) }
;

and_expression:	equality_expression
					|	and_expression AND_KW equality_expression					{ $$ = A_Binop('&&', $1, $3) }
;

or_expression: and_expression
				|	or_expression OR_KW and_expression								{ $$ = A_Binop('||', $1, $3) }
;

%%
