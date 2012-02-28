%{

#define YYERROR_VERBOSE

int xfile_lex();
void xfile_error (/*YYLTYPE *llocp,*/ char const *s);

%}

%locations
%name-prefix="xfile_"

%union{
int intValue;
float floatValue;
StringA* pName;
Member* pMember;
DataType* pDatatype;
Template* pTemplate;
Dimension* pDimension;
}

%token TOKEN_OBRACE
%token TOKEN_CBRACE
%token TOKEN_OBRACKET
%token TOKEN_CBRACKET
%token TOKEN_OPAREN
%token TOKEN_CPAREN
%token TOKEN_CHAR
%token TOKEN_UCHAR
%token TOKEN_WORD
%token TOKEN_DWORD
%token TOKEN_SWORD
%token TOKEN_SDWORD
%token TOKEN_FLOAT
%token TOKEN_DOUBLE
%token TOKEN_CSTRING
%token TOKEN_LPSTR
%token TOKEN_GUID
%token TOKEN_TEMPLATE
%token TOKEN_ARRAY
%token TOKEN_SEMICOLON
%token TOKEN_COMMA
%token TOKEN_DOT
/*
%token TOKEN_INTEGER_LIST
%token TOKEN_FLOAT_LIST
*/

%token <floatValue> TOKEN_FNUM

%token <intValue> TOKEN_INTEGER
%token <pName> TOKEN_NAME
%token <pName> TOKEN_STRING

%type <pName> name
%type <pName> optional_name
%type <pDatatype> primitive_type
%type <pDatatype> array_data_type
%type <pMember> template_members
%type <pMember> primitive
%type <pMember> array
%type <pDimension> dimension_size
%type <pDimension> dimension_list	/* TODO */
%type <pDimension> dimension	/* TODO */
%type <pMember> template_reference
%type <pTemplate> template

%type <pDatatype> identifier

/*%type <exp> primary_expression*/


%%

file: templates objects
		| templates
;

templates: template					{ parser->AddTemplate($1) }
			|	templates template	{ parser->AddTemplate($2) }
;

objects: object
			|	object objects
;

template              : TOKEN_TEMPLATE name TOKEN_OBRACE
                            class_id
                            template_parts
                            TOKEN_CBRACE
									 {
									 $$ = x_Template($2);
									// for (int i = 0; i < parser->m_members.size(); i++)
									//	$$->m_members.push_back(parser->m_members[i]);
									 $$->m_members = parser->m_members;
									 parser->m_members.RemoveAll();
									 }
;
template_parts        : template_members_part TOKEN_OBRACKET
                        template_option_info
                        TOKEN_CBRACKET
                      | template_members_list
;
template_members_part : /* Empty */
                      | template_members_list
;
template_option_info  : ellipsis
                      | template_option_list
;
template_members_list :	template_members	{ parser->m_members.Add($1) }
                      | template_members_list template_members	{ parser->m_members.Add($2) }
;
template_members      : primitive
                      | array
                      | template_reference
;

primitive             : primitive_type optional_name TOKEN_SEMICOLON	{ $$ = x_Member($1, $2) }
;

array                 : TOKEN_ARRAY array_data_type name dimension_list TOKEN_SEMICOLON
							{ $$ = x_Member(DataType_Array($2, $4), $3) }
;

template_reference    : name optional_name TOKEN_SEMICOLON
								{
								$$ = x_Member(DataType_Name($1), $2)
								}
;
primitive_type        : TOKEN_WORD		{ $$ = DataType_Primitive(TOKEN_WORD) }
                      | TOKEN_DWORD		{ $$ = DataType_Primitive(TOKEN_DWORD) }
                      | TOKEN_FLOAT		{ $$ = DataType_Primitive(TOKEN_FLOAT) }
                      | TOKEN_DOUBLE	{ $$ = DataType_Primitive(TOKEN_DOUBLE) }
                      | TOKEN_CHAR		{ $$ = DataType_Primitive(TOKEN_CHAR) }
                      | TOKEN_UCHAR		{ $$ = DataType_Primitive(TOKEN_UCHAR) }
                      | TOKEN_SWORD		{ $$ = DataType_Primitive(TOKEN_SWORD) }
                      | TOKEN_SDWORD	{ $$ = DataType_Primitive(TOKEN_SDWORD) }
                      | TOKEN_LPSTR		{ $$ = DataType_Primitive(TOKEN_LPSTR) }
							 /*
                      | TOKEN_UNICODE
							 */
                      | TOKEN_CSTRING	{ $$ = DataType_Primitive(TOKEN_CSTRING) }
;

array_data_type       : primitive_type	{ $$ = $1 }
                      | name				{ $$ = DataType_Name($1) }
;
dimension_list        : dimension	{ $$ = $1 }
                      | dimension_list dimension	{ $$ = $2  }	/* TODO */
;
dimension             : TOKEN_OBRACKET dimension_size TOKEN_CBRACKET	{ $$ = $2 }
;
dimension_size        : TOKEN_INTEGER	{ $$ = Dimension_Integer($1) }
                      | name		{ $$ = Dimension_Name($1) }
;
template_option_list  : template_option_part
                      | template_option_list template_option_part
;
template_option_part  : name optional_class_id
;
name                  : TOKEN_NAME
;
optional_name         : /* Empty */	{ $$ = NULL }
                      | name
;
class_id              : TOKEN_GUID
;
optional_class_id     : /* Empty */
                      | class_id
;
ellipsis              : TOKEN_DOT TOKEN_DOT TOKEN_DOT
;


/**********************************************/

object                : identifier /*optional_name TOKEN_OBRACE
                            optional_class_id
                            data_parts_list
                            TOKEN_CBRACE
									 */
									 {
										Instance* pObject = parse_object($1);
									 parser->m_objects.Add(pObject);
									 }
;
data_parts_list       : data_parts_list_1
;

data_parts_list_1      : data_part
                      | data_parts_list data_part
;

data_part             : data_reference
                      | object
							 |	item
							 /*
                      | number_list
                      | float_list
                      | string_list
							 */
;

item:		TOKEN_INTEGER
		|	TOKEN_FNUM
		|	TOKEN_STRING
		|	list_separator
;	

/*
number_list           : TOKEN_INTEGER_LIST
;
float_list            : TOKEN_FLOAT_LIST
;
*/

string_list           : string_list_1 list_separator
;
string_list_1         : string
                      | string_list_1 list_separator string
;

list_separator        : TOKEN_COMMA
                      | TOKEN_SEMICOLON
;
string                : TOKEN_STRING
;

identifier            : name { $$ = DataType_Name($1) }
                      | primitive_type
;
data_reference        : TOKEN_OBRACE name optional_class_id TOKEN_CBRACE
;

%%
