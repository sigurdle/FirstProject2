%{

#define YYERROR_VERBOSE

int m68kasmlex();

void m68kasmerror (/*YYLTYPE *llocp,*/ char const *s);

//A_Class* g_CompilationUnit;

#define yyfalse	0
#define yytrue		1

%}

%locations
%name-prefix="m68kasm"

%union{
int num;
char* id;
char* string_literal;
}

%token <string_literal> STRING_LITERAL
%token <num> INTEGER_LITERAL
%token <id> IDENTIFIER

%%

lines:	line
		|	lines '\n' line

line:	IDENTIFIER ':'
	|	IDENTIFIER ':' instruction
	|	instruction
;

instruction:	IDENTIFIER expression_list_opt
;

primary:	INTEGER_LITERAL
		|	IDENTIFIER
;

multiplicative_expression: primary
;

additive_expression:	multiplicative_expression
						|	additive_expression '+' multiplicative_expression// { $$ = A_BinopExp(@1, '+', $1, $3) }
						|	additive_expression '-' multiplicative_expression// { $$ = A_BinopExp(@1, '-', $1, $3) }
;

expression:	primary
			|	primary '@' '(' additive_expression ')'
;

expression_list:	expression
					|	expression_list ',' expression

expression_list_opt:
						|	expression_list
;

%%
