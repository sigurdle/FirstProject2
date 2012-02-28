%{

#define PREFIX //pp_lloc.first_line = yylineno;

%}

DIGIT    [0-9]
HEX		[0-9a-fA-F]
ID       [a-z_][a-z_0-9]*

%option yylineno

%%

[0-9]+		{	PREFIX
					sql_lval.num = atol(yytext);
					return INTEGER_LITERAL;
				}

\"[^\n"]*\"	{	PREFIX 
					int len = strlen(yytext);
					sql_lval.string_literal = (char*)malloc(len-1);
					memcpy(sql_lval.string_literal, yytext+1, len-2);
					sql_lval.string_literal[len-2] = 0;
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

SELECT {  PREFIX return SELECT_KW; }
DELETE {  PREFIX return DELETE_KW; }
INSERT {  PREFIX return INSERT_KW; }
INTO {  PREFIX return INTO_KW; }
VALUES {  PREFIX return VALUES_KW; }
AS {  PREFIX return AS_KW; }
FROM {  PREFIX return FROM_KW; }
JOIN {  PREFIX return JOIN_KW; }
INNER {  PREFIX return INNER_KW; }
OUTER {  PREFIX return OUTER_KW; }
LEFT {  PREFIX return LEFT_KW; }
RIGHT {  PREFIX return RIGHT_KW; }
FULL {  PREFIX return FULL_KW; }
ON {  PREFIX return ON_KW; }
WHERE {  PREFIX return WHERE_KW; }
GENERATED {  PREFIX return GENERATED_KW; }
ALWAYS {  PREFIX return ALWAYS_KW; }
IDENTITY {  PREFIX return IDENTITY_KW; }
DEFAULT {  PREFIX return DEFAULT_KW; }
UNDER {  PREFIX return UNDER_KW; }
TYPE {  PREFIX return TYPE_KW; }
ALTER {  PREFIX return ALTER_KW; }
ADD {  PREFIX return ADD_KW; }
COLUMN {  PREFIX return COLUMN_KW; }
START {  PREFIX return START_KW; }
WITH {  PREFIX return WITH_KW; }
INCREMENT {  PREFIX return INCREMENT_KW; }
MAXVALUE {  PREFIX return MAXVALUE_KW; }
NO {  PREFIX return NO_KW; }
BY {  PREFIX return BY_KW; }
AND {  PREFIX return AND_KW; }
OR {  PREFIX return OR_KW; }
NOT {  PREFIX return NOT_KW; }
CREATE {  PREFIX return CREATE_KW; }
TABLE {  PREFIX return TABLE_KW; }
SMALLINT {  PREFIX return SMALLINT_KW; }
INTEGER {  PREFIX return INTEGER_KW; }
INT {  PREFIX return INT_KW; }
BIGINT {  PREFIX return BIGINT_KW; }
CHAR {  PREFIX return CHAR_KW; }
CHARACTER {  PREFIX return CHARACTER_KW; }
VARYING {  PREFIX return VARYING_KW; }
VARCHAR {  PREFIX return VARCHAR_KW; }
VALID {  PREFIX return VALID_KW; }
IS {  PREFIX return IS_KW; }
NULL {  PREFIX return NULL_KW; }
XML {  PREFIX return XML_KW; }
XMLDOCUMENT {  PREFIX return XMLDOCUMENT_KW; }
XMLEXISTS_KW	{  PREFIX return XMLEXISTS_KW; }

{ID}		{  PREFIX sql_lval.id = strdup(yytext); return IDENTIFIER;}

%%
