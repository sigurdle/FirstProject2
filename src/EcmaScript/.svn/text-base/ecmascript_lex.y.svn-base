%{

//#include "stdafx.h"

#define PREFIX //pp_lloc.first_line = yylineno;
//#undef _SECURE_SCL

%}

DIGIT    [0-9]
HEX		[0-9a-fA-F]
ID       [a-zA-Z_][a-zA-Z_0-9]*

%option yylineno

%%

"//" {
				int c;
				while ((c = yyinput()) != '\n')
				;
			}

"/*" {
				while (1)
				{
					int c;
					
					while ((c = yyinput()) != '*' && c != EOF)
						;
					
					if (c == '*')
					{
						while ((c = yyinput()) == '*')
							;

						if (c == '/')
							break;
					
						if (c == EOF)
						{
							//error("EOF in comment");
							break;
						}
					}
					else if (c == EOF)
					{
						//error("EOF in comment");
						break;
					}
				}
			}

"\n" {  }
"\r" {  }

 {DIGIT}+	{	PREFIX
				ecmascriptlval.int_literal = atol(yytext);
				return INTEGER_LITERAL;
			}

0x{HEX}+	{	PREFIX
				sscanf(yytext, "0x%x", &ecmascriptlval.int_literal);
				return INTEGER_LITERAL;
			}

{DIGIT}+"."{DIGIT}*		{	PREFIX
						ecmascriptlval.float64_literal = atof(yytext);
						return FLOAT_LITERAL;
					}

\"[^\n"]*\"		{	PREFIX 
					int len = strlen(yytext);
					ecmascriptlval.string_literal = (char*)malloc(len-1);
					memcpy(ecmascriptlval.string_literal, yytext+1, len-2);
					ecmascriptlval.string_literal[len-2] = 0;
					return STRING_LITERAL;
				}

"++"	{ PREFIX return PLUSPLUS; }
"--"	{ PREFIX return MINUSMINUS; }
"||"	{ PREFIX return LOGICAL_OR; }
"&&"	{ PREFIX return LOGICAL_AND; }
"=="	{ PREFIX return EQUALEQUAL; }
">="	{ PREFIX return LEQ; }
"<="	{ PREFIX return GEQ; }
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
"/"	{ PREFIX return '/'; }
"%"	{ PREFIX return '%'; }
","	{ PREFIX return ','; }
";"	{ PREFIX return ';'; }
"."	{ PREFIX return '.'; }
"="	{ PREFIX return '='; }

null {  PREFIX return NULL_KW; }
true {  PREFIX return TRUE_KW; }
false {  PREFIX return FALSE_KW; }
new {  PREFIX return NEW_KW; }
delete {  PREFIX return DELETE_KW; }
void {  PREFIX return VOID_KW; }
this {  PREFIX return THIS_KW; }
function {  PREFIX return FUNCTION_KW; }
return {  PREFIX return RETURN_KW; }
if {  PREFIX return IF_KW; }
else {  PREFIX return ELSE_KW; }
var {  PREFIX return VAR_KW; }
do {  PREFIX return DO_KW; }
while {  PREFIX return WHILE_KW; }
for {  PREFIX return FOR_KW; }
break {  PREFIX return BREAK_KW; }
continue {  PREFIX return CONTINUE_KW; }
in {  PREFIX return IN_KW; }
typeof {  PREFIX return TYPEOF_KW; }
try {  PREFIX return TRY_KW; }
catch {  PREFIX return CATCH_KW; }
throw {  PREFIX return THROW_KW; }

{ID}		{  PREFIX
				ecmascriptlval.id = _strdup(yytext);
				return IDENTIFIER;
			}

%%
