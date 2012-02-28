%{

#define PREFIX //pp_lloc.first_line = yylineno;

%}

DIGIT    [0-9]
HEX		[0-9a-fA-F]
ID       [a-z_][a-z_0-9]*

%option yylineno

%%

"\n" {  }
"\r" {  }

[0-9]+		{	PREFIX
					javalval.num = atol(yytext);
					return INTEGER_LITERAL;
				}

"\"".*"\""	{	PREFIX 
					int len = strlen(yytext);
					javalval.string_literal = (char*)malloc(len-1);
					memcpy(javalval.string_literal, yytext+1, len-2);
					javalval.string_literal[len-2] = 0;
					return STRING_LITERAL;
				}

"++"	{ PREFIX return PLUSPLUS; }
"--"	{ PREFIX return MINUSMINUS; }
"||"	{ PREFIX return LOGICAL_OR; }
"&&"	{ PREFIX return LOGICAL_AND; }
"=="	{ PREFIX return EQUALEQUAL; }
"*"	{ PREFIX return '*'; }
">"	{ PREFIX return '>'; }
"<"	{ PREFIX return '<'; }
"+"	{ PREFIX return '+'; }
"-"	{ PREFIX return '-'; }
"!"	{ PREFIX return '!'; }
"~"	{ PREFIX return '~'; }
"("	{ PREFIX return '('; }
")"	{ PREFIX return ')'; }
"{"	{ PREFIX return '{'; }
"}"	{ PREFIX return '}'; }
"["	{ PREFIX return '['; }
"]"	{ PREFIX return ']'; }
"-"	{ PREFIX return '-'; }
"/"	{ PREFIX return '/'; }
"%"	{ PREFIX return '%'; }
","	{ PREFIX return ','; }
";"	{ PREFIX return ';'; }
"."	{ PREFIX return '.'; }
"="	{ PREFIX return '='; }

class {  PREFIX return CLASS_KW; }
null {  PREFIX return NULL_KW; }
true {  PREFIX return TRUE_KW; }
false {  PREFIX return FALSE_KW; }
new {  PREFIX return NEW_KW; }
delete {  PREFIX return DELETE_KW; }
void {  PREFIX return VOID_KW; }
this {  PREFIX return THIS_KW; }
return {  PREFIX return RETURN_KW; }
if {  PREFIX return IF_KW; }
else {  PREFIX return ELSE_KW; }
do {  PREFIX return DO_KW; }
while {  PREFIX return WHILE_KW; }
for {  PREFIX return FOR_KW; }
break {  PREFIX return BREAK_KW; }
continue {  PREFIX return CONTINUE_KW; }
static {  PREFIX return STATIC_KW; }
instanceof {  PREFIX return INSTANCEOF_KW; }

{ID}		{  PREFIX javalval.id = _strdup(yytext); return IDENTIFIER;}

%%
