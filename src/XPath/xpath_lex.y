%{

#include "xpath_parse.tab.h"

#define PREFIX //pp_lloc.first_line = yylineno;

%}

DIGIT    [0-9]
ID       [A-Za-z_][A-Za-z_0-9-]*

%option yylineno

%%

[0-9]+		{	PREFIX
					xpath_lval.num = atol(yytext);
					return INTEGER_LITERAL;
				}

"\"".*"\""	{	PREFIX 
					xpath_lval.string_literal = (new System::ImmutableString<wchar_t>(string_copyw(yytext, strlen(yytext))));
					return STRING_LITERAL;
				}

"empty-sequence"	{ PREFIX return EMPTY_SEQUENCE_KW; }

"/>"		{ PREFIX return EMPTY_ELEMENT; }
"</"		{ PREFIX return ELEMENT_END; }

"::"		{ PREFIX return TWO_COLON; }
"//"		{ PREFIX return TWO_SLASH; }
".."		{ PREFIX return TWO_PUNCT; }
"and"		{ PREFIX return AND; }
"or"		{ PREFIX return OR; }
"div"		{ PREFIX return DIV; }
"idiv"	{ PREFIX return IDIV; }
"mod"		{ PREFIX return MOD; }
"*"		{ PREFIX return '*'; }
"="		{ PREFIX return EQ; }
"!="		{ PREFIX return NEQ; }
">"		{ PREFIX return '>'; }
"<"		{ PREFIX return '<'; }
"-"		{ PREFIX return '-'; }
"!"		{ PREFIX return '!'; }
"["		{ PREFIX return '['; }
"]"		{ PREFIX return ']'; }
"("		{ PREFIX return '('; }
")"		{ PREFIX return ')'; }
":"		{ PREFIX return ':'; }
"+"		{ PREFIX return '+'; }
"/"		{ PREFIX return '/'; }
","		{ PREFIX return ','; }
"."		{ PREFIX return '.'; }

"element" { PREFIX return ELEMENT_KW; }
"instance" { PREFIX return INSTANCE_KW; }
"of" { PREFIX return OF_KW; }

"ancestor"				{ PREFIX xpath_lval.num = 0; return AxisName; }
"ancestor-or-self"	{ PREFIX xpath_lval.num = 1; return AxisName; }
"attribute"				{ PREFIX xpath_lval.num = 2; return AxisName; }
"child"					{ PREFIX xpath_lval.num = 3; return AxisName; }
"descendant"			{ PREFIX xpath_lval.num = 4; return AxisName; }
"descendant-or-self"	{ PREFIX xpath_lval.num = 5; return AxisName; }
"following"				{ PREFIX xpath_lval.num = 6; return AxisName; }
"following-sibling"	{ PREFIX xpath_lval.num = 7; return AxisName; }
"namespace"				{ PREFIX xpath_lval.num = 8; return AxisName; }
"parent"					{ PREFIX xpath_lval.num = 9; return AxisName; }
"preceding"				{ PREFIX xpath_lval.num = 10; return AxisName; }
"preceding-sibling"	{ PREFIX xpath_lval.num = 11; return AxisName; }
"self"					{ PREFIX xpath_lval.num = 12; return AxisName; }

{ID}		{  PREFIX xpath_lval.id = (new ImmutableString<wchar_t>(string_copyw(yytext, strlen(yytext)))); return NCName; }

"-"		{ PREFIX return '-'; }

%%
