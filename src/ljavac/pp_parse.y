%{

int pp2_lex();

int pp_lex()
{
	int c = pp2_lex();
	while (c == ' ')
		c = pp2_lex();

	return c;
}

void pp_error (char const *s);
#define YYERROR_VERBOSE

#define yyfalse	0
#define yytrue		1

extern PP_Group* pp_file;

     %}

%glr-parser
%locations
%name-prefix="pp_"

%union {
int num;
char* id;
char* string_literal;
A_Exp* exp;
PP_Group *group;
PP_GroupPart *groupPart;
PP_Directive *directive;
PP_IfGroup* ifGroup;
PP_ElifGroups* elifGroups;
PP_Token token;
PP_TokenList* tokenList;
PP_IdentifierList* identifierList;
}

%token <id> identifier
%token <id> identifier_lparen
%token cv_qualifier	14
%token TWO_HASH
%token PLUSPLUS
%token MINUSMINUS
%token ARROW

%token PPINCLUDE_KW
%token PPIF_KW
%token PPELSE_KW
%token PPIFDEF_KW
%token PPIFNDEF_KW
%token PPELIF_KW
%token PPENDIF_KW
%token PPDEFINE_KW
%token PPUNDEF_KW
%token PPINCLUDE_KW
%token PPLINE_KW
%token PPERROR_KW
%token PPPRAGMA_KW

%type <token> preprocessing_token
%type <tokenList> pp_tokens
%type <tokenList> pp_tokens_opt
%type <tokenList> replacement_list
%type <group> group
%type <group> group_opt
%type <groupPart> group_part
%type <groupPart> control_line
%type <directive> elif_group
%type <ifGroup> if_group
%type <elifGroups> elif_groups
%type <elifGroups> elif_groups_opt
%type <group> else_group
%type <group> else_group_opt
%type <groupPart> if_section
%type <exp> pp_constant_expression
%type <identifierList> identifier_list
%type <identifierList> identifier_list_opt

%token TWO_COLON
%token THREE_DOTS
%token <exp> SIZEOF
%token <string_literal> STRING_LITERAL
%token <string_literal> LSTRING_LITERAL
%token <num> INTEGER_LITERAL

     %%

preprocessing_file:	group_opt { pp_file = $1 }
;

pp_constant_expression:	INTEGER_LITERAL { $$ = A_Int32Exp($1) }
;

group:	group_part { $$ = new PP_Group($1, NULL) }
		|	group_part group { $$ = new PP_Group($1, $2) }
;

group_opt:	/*empty*/ { $$ = NULL }
			|	group
;

new_line: '\n'
;

ws:	' '
	|	ws ' ';

ws_opt: /*empty*/
		|	ws;
;

group_part:	pp_tokens_opt new_line { $$ = PP_Tokens($1) }
			|	if_section { $$ = $1 }
			|	control_line { $$ = $1 }
;

if_section:	if_group elif_groups_opt else_group_opt endif_line { $$ = PP_IfSection($1, $2, $3) }
;

if_group:	'#' ws_opt PPIF_KW pp_constant_expression new_line group_opt { $$ = PP_If_Group($4, $6) }
			|	'#' ws_opt PPIFDEF_KW identifier new_line group_opt  { $$ = PP_IfDefGroup($4, $6) }
			|	'#' ws_opt PPIFNDEF_KW identifier new_line group_opt  { $$ = PP_IfNDefGroup($4, $6) }
;

elif_groups:	elif_group { $$ = new PP_ElifGroups($1, NULL) }
				|	elif_groups elif_group { $$ = new PP_ElifGroups($2, $1) }
;

elif_groups_opt:	/*empty*/ { $$ = NULL }
					|	elif_groups
;

elif_group:	'#' ws_opt PPELIF_KW pp_constant_expression new_line group_opt { $$ = PP_ElifGroup($4, $6) }
;

else_group:	'#' ws_opt PPELSE_KW new_line group_opt { $$ = $5 }
;

else_group_opt:	/*empty*/ { $$ = NULL }
					|	else_group
;

endif_line:	'#' ws_opt PPENDIF_KW new_line
;

control_line:
		'#' ws_opt PPINCLUDE_KW pp_tokens new_line { }
	|	'#' ws_opt PPDEFINE_KW identifier replacement_list new_line { $$ = PP_Define($4, false, NULL, $5) }
	|	'#' ws_opt PPDEFINE_KW identifier_lparen identifier_list_opt ')' replacement_list new_line { $$ = PP_Define($4, true, $5, $7) }
	|	'#' ws_opt PPUNDEF_KW identifier new_line { $$ = PP_Undef($4) }
/*
# line pp-tokens new-line
# error pp-tokensopt new-line
# pragma pp-tokensopt new-line
*/
	|	'#' ws_opt new_line {}
;

identifier_list:	identifier { $$ = new PP_IdentifierList($1, NULL) }
					|	identifier_list ',' identifier { $$ = new PP_IdentifierList($3, $1) }
;

identifier_list_opt:	/*empty*/ { $$ = NULL }
						|	identifier_list
;

preprocessing_token:
				'(' { $$ = PP_Char(@1, '(') }
			|	')' { $$ = PP_Char(@1, ')') }
			|	'[' { $$ = PP_Char(@1, '[') }
			|	']' { $$ = PP_Char(@1, ']') }
			|	'{' { $$ = PP_Char(@1, '{') }
			|	'}' { $$ = PP_Char(@1, '}') }
			|	'+' { $$ = PP_Char(@1, '+') }
			|	'-' { $$ = PP_Char(@1, '-') }
			|	'*' { $$ = PP_Char(@1, '*') }
			|	'/' { $$ = PP_Char(@1, '/') }
			|	'%' { $$ = PP_Char(@1, '%') }
			|	'&' { $$ = PP_Char(@1, '&') }
			|	'|' { $$ = PP_Char(@1, '|') }
			|	'!' { $$ = PP_Char(@1, '!') }
			|	'=' { $$ = PP_Char(@1, '=') }
			|	'<' { $$ = PP_Char(@1, '<') }
			|	'>' { $$ = PP_Char(@1, '>') }
			|	'.' { $$ = PP_Char(@1, '.') }
			|	';' { $$ = PP_Char(@1, ';') }
			|	TWO_HASH { $$ = PP_Char(@1, '##') }
			|	INTEGER_LITERAL { $$ = PP_Int32(@1, $1) }
			|	identifier { $$ = PP_Identifier(@1, $1) }
;

replacement_list:	pp_tokens_opt
;

pp_tokens:	identifier_lparen { $$ = new PP_TokenList(PP_Identifier(@1, $1), new PP_TokenList(PP_Char(@1, '('), NULL)) }
			|	preprocessing_token	{
			$$ = new PP_TokenList($1, NULL)
			 }
			|	pp_tokens preprocessing_token {
			
			$$ = new PP_TokenList($2, $1);
			 }
;

pp_tokens_opt: /*empty*/ { $$ = NULL }
				|	pp_tokens
;

     %%
