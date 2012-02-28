%{

#include "pp_parse.tab.h"

#define PREFIX pp_lloc.first_line = yylineno;

void mygetc(char* buf, int& result, int max_size)
{
	int c = fgetc(yyin);
	if (c == '\\')
	{
		int c2 = fgetc(yyin);
		if (c2 == '\r')
		{
			c2 = fgetc(yyin);
			ATLASSERT(c2 == '\n');

			c = fgetc(yyin);
		}
		else
		{
			ungetc(c2, yyin);
		}
	}

	result = (c == EOF) ? YY_NULL : (buf[0] = c, 1);
}

//#define YY_INPUT(buf,result,max_size) mygetc(buf, result, max_size)

%}

DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z_0-9]*

%option yylineno

%s DEFINE

%%

"#" { return '#'; }

if  { PREFIX; return PPIF_KW; }
ifdef  { PREFIX; return PPIFDEF_KW; }
ifndef  { PREFIX; return PPIFNDEF_KW; }
endif  { PREFIX; return PPENDIF_KW; }
define  { PREFIX; return PPDEFINE_KW; }

[0-9]+		{	PREFIX
					pp_lval.num = atol(yytext);
					return INTEGER_LITERAL;
				}

"\"".*"\""	{	PREFIX 
					pp_lval.string_literal = strdup(yytext);
					return STRING_LITERAL;
				}

"\n" { BEGIN(0); return '\n'; }

"//"+.*"\n" {
	}

" "|"\t"|"\v"|"\f"+ { PREFIX return ' '; }

"##"  { PREFIX return TWO_HASH; }
"..."	{ PREFIX return THREE_DOTS; }
"::"	{ PREFIX return TWO_COLON; }
"++"	{ PREFIX return PLUSPLUS; }
"--"	{ PREFIX return MINUSMINUS; }
"->"	{ PREFIX return ARROW; }
"*"	{ PREFIX return '*'; }
"="	{ PREFIX return '='; }
">"	{ PREFIX return '>'; }
"<"	{ PREFIX return '<'; }
"-"	{ PREFIX return '-'; }
"!"	{ PREFIX return '!'; }
"~"	{ PREFIX return '~'; }
","	{ PREFIX return ','; }
"{"	{ PREFIX return '{'; }
"}"	{ PREFIX return '}'; }
";"	{ PREFIX return ';'; }
"["	{ PREFIX return '['; }
"]"	{ PREFIX return ']'; }
"("	{ PREFIX return '('; }
")"	{ PREFIX return ')'; }
"?"	{ PREFIX return '?'; }
":"	{ PREFIX return ':'; }
"+"	{ PREFIX return '+'; }
"-"	{ PREFIX return '-'; }
"/"	{ PREFIX return '/'; }
"%"	{ PREFIX return '%'; }
"."	{ PREFIX return '.'; }
"&"	{ PREFIX return '&'; }
"|"	{ PREFIX return '|'; }
"^"	{ PREFIX return '^'; }

{ID}		{  PREFIX pp_lval.id = strdup(yytext);
				return identifier;}

<DEFINE>{ID}"("	{
						PREFIX
						pp_lval.id = (char*)malloc(yyleng);
						strncpy(pp_lval.id, yytext, yyleng-1);
						pp_lval.id[yyleng-1] = 0;
						return identifier_lparen;
						}

%%
