%{

#define PREFIX //pp_lloc.first_line = yylineno;

%}

DIGIT    [0-9]
HEX		[0-9a-fA-F]
ID       [a-z_][a-z_0-9]*

%option yylineno

%%

[0-9]+		{	PREFIX
					formula_lval.num = atol(yytext);
					return INTEGER_LITERAL;
				}

"\"".*"\""	{	PREFIX 
					int len = strlen(yytext);
					formula_lval.string_literal = (char*)malloc(len-1);
					memcpy(formula_lval.string_literal, yytext+1, len-2);
					formula_lval.string_literal[len-2] = 0;
					return STRING_LITERAL;
				}

"\n" { return '\n'; }

"<>"|"!="	{ PREFIX return NOT_EQUAL;}
">="	{ PREFIX return GEQ; }
"<="	{ PREFIX return LEQ; }
"="	{ PREFIX return EQUAL; }
"*"	{ PREFIX return '*'; }
">"	{ PREFIX return '>'; }
"<"	{ PREFIX return '<'; }
"-"	{ PREFIX return '-'; }
"("	{ PREFIX return '('; }
")"	{ PREFIX return ')'; }
"+"	{ PREFIX return '+'; }
"-"	{ PREFIX return '-'; }
"/"	{ PREFIX return '/'; }
"%"	{ PREFIX return '%'; }
","	{ PREFIX return ','; }
"."	{ PREFIX return '.'; }

{ID}		{  PREFIX formula_lval.id = strdup(yytext); return identifier;}

%%
