%{

#include "cpp_parse.tab.h"

#define PREFIX //pp_lloc.first_line = yylineno;

/*
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

#define YY_INPUT(buf,result,max_size) mygetc(buf, result, max_size)
*/

%}

DIGIT    [0-9]
ID       [a-z_][a-z_0-9]*

%option yylineno

%%

[0-9]+		{	PREFIX
					cpp_lval.num = atol(yytext);
					return INTEGER_LITERAL;
				}

L"\"".*"\"" {	PREFIX 
					cpp_lval.string_literal = strdup(yytext);
					return LSTRING_LITERAL;
				}

"\"".*"\""	{	PREFIX 
					cpp_lval.string_literal = strdup(yytext);
					return STRING_LITERAL;
				}

"\n" { return '\n'; }

"..."	{ PREFIX return THREE_DOTS; }
"::"	{ PREFIX return TWO_COLON; }
"++"	{ PREFIX return PLUSPLUS; }
"--"	{ PREFIX return MINUSMINUS; }
"->"	{ PREFIX return ARROW; }
"=="	{ PREFIX return EQUAL; }
"!="	{ PREFIX return NOT_EQUAL; }
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

char {  PREFIX return CHAR_KW; }
wchar_t {  PREFIX return WCHAR_T_KW; }
bool {  PREFIX return BOOL_KW; }
short {  PREFIX return SHORT_KW; }
int {  PREFIX return INT_KW; }
long {  PREFIX return LONG_KW; }
signed {  PREFIX return SIGNED_KW; }
unsigned {  PREFIX return UNSIGNED_KW; }
float {  PREFIX return FLOAT_KW; }
double {  PREFIX return DOUBLE_KW; }
void        {  PREFIX return VOID_KW; }

static_cast {  PREFIX return STATIC_CAST_KW; }
reinterpret_cast {  PREFIX return REINTERPRET_CAST_KW; }
dynamic_cast {  PREFIX return DYNAMIC_CAST_KW; }
const_cast {  PREFIX return CONST_CAST_KW; }

if        {  PREFIX return IF_KW; }
else        {  PREFIX return ELSE_KW; }
switch      {  PREFIX return SWITCH_KW; }
for        {  PREFIX return FOR_KW; }
do        {  PREFIX return DO_KW; }
while        {  PREFIX return WHILE_KW; }
sizeof        {  PREFIX return SIZEOF_KW; }
typedef        {  PREFIX return TYPEDEF_KW; }
class        { PREFIX return CLASS_KW; }
struct        {  PREFIX return STRUCT_KW; }
union        {  PREFIX return UNION_KW; }

const|volatile	{ PREFIX return 14;}

namespace { PREFIX return NAMESPACE_KW;}
extern { PREFIX return EXTERN_KW;}
this { PREFIX return THIS_KW;}
private { PREFIX return PRIVATE_KW;}
protected { PREFIX return PROTECTED_KW;}
public { PREFIX return PUBLIC_KW;}
auto {  PREFIX return AUTO_KW; }
register {  PREFIX return REGISTER_KW; }
static {  PREFIX return STATIC_KW; }
mutable {  PREFIX return MUTABLE_KW; }
inline {  PREFIX return INLINE_KW; }
virtual {  PREFIX return VIRTUAL_KW; }
explicit {  PREFIX return EXPLICIT_KW; }
friend {  PREFIX return FRIEND_KW; }
true {  PREFIX return TRUE_KW; }
false {  PREFIX return FALSE_KW; }

{ID}		{  PREFIX cpp_lval.id = strdup(yytext); return identifier;}
{ID}"("	{  PREFIX cpp_lval.id = strdup(yytext); return identifier_lparen;}

%%
