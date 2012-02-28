%{

#define PREFIX //pp_lloc.first_line = yylineno;

%}

DIGIT    [0-9]
HEX		[0-9a-fA-F]
ID       [a-z_][a-z_0-9]*

%option yylineno

%%

"#"|"//" {
				int c;
				while ((c = yyinput()) != '\n')
				;
			}

"-"?{DIGIT}+	{	PREFIX
					xfile_lval.intValue = atol(yytext);
					return TOKEN_INTEGER;
				}

"-"?{DIGIT}+"."{DIGIT}*		{	PREFIX
									xfile_lval.floatValue = atof(yytext);
									return TOKEN_FNUM;
									}

"\"".*"\""	{	PREFIX 
					int len = strlen(yytext);
					xfile_lval.pName = new System::StringA(string_copy(yytext+1, len-2));//(char*)malloc(len-1);
				//	memcpy(xfile_lval.pName, yytext+1, len-2);
				//	xfile_lval.pName[len-2] = 0;
					return TOKEN_STRING;
				}

"\n"	{ xfile_lloc.first_line++; }

"{" { PREFIX return TOKEN_OBRACE; }
"}" { PREFIX return TOKEN_CBRACE; }
"[" { PREFIX return TOKEN_OBRACKET; }
"]" { PREFIX return TOKEN_CBRACKET; }
";" { PREFIX return TOKEN_SEMICOLON; }
"," { PREFIX return TOKEN_COMMA; }
"." { PREFIX return TOKEN_DOT; }

"<".+">" { PREFIX return TOKEN_GUID; }

template {  PREFIX return TOKEN_TEMPLATE; }
CHAR {  PREFIX return TOKEN_CHAR; }
UCHAR {  PREFIX return TOKEN_UCHAR; }
WORD {  PREFIX return TOKEN_WORD; }
SWORD {  PREFIX return TOKEN_SWORD; }
DWORD {  PREFIX return TOKEN_DWORD; }
SDWORD {  PREFIX return TOKEN_SDWORD; }
FLOAT {  PREFIX return TOKEN_FLOAT; }
DOUBLE {  PREFIX return TOKEN_DOUBLE; }
STRING {  PREFIX return TOKEN_CSTRING; }
array {  PREFIX return TOKEN_ARRAY; }

{ID}		{  PREFIX xfile_lval.pName = new StringA(string_copy(yytext)); return TOKEN_NAME;}

%%
