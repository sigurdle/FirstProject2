%{

#define PREFIX //pp_lloc.first_line = yylineno;

%}

DIGIT    [0-9]
HEX		[0-9a-fA-F]
ID       [a-z_][a-z_0-9]*

%option yylineno

%%

"\n" { PREFIX return '\n'; }
"\r" {  }

[0-9]+		{	PREFIX
					m68kasmlval.num = atol(yytext);
					return INTEGER_LITERAL;
				}

"\"".*"\""	{	PREFIX 
					int len = strlen(yytext);
					m68kasmlval.string_literal = (char*)malloc(len-1);
					memcpy(m68kasmlval.string_literal, yytext+1, len-2);
					m68kasmlval.string_literal[len-2] = 0;
					return STRING_LITERAL;
				}

"("	{ PREFIX return '('; }
")"	{ PREFIX return ')'; }
"-"	{ PREFIX return '-'; }
"+"	{ PREFIX return '+'; }
"*"	{ PREFIX return '*'; }
"/"	{ PREFIX return '/'; }
","	{ PREFIX return ','; }
"."	{ PREFIX return '.'; }
"@"	{ PREFIX return '@'; }

{ID}		{  PREFIX m68kasmlval.id = _strdup(yytext); return IDENTIFIER;}

%%
