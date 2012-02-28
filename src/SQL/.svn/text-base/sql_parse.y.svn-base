%{

#define YYERROR_VERBOSE

int sql_lex();
void sql_error (/*YYLTYPE *llocp,*/ char const *s);

void parse_xpath();

extern Stm* g_stm;

%}

%locations
%name-prefix="sql_"

%union{
int num;
char* id;
char* string_literal;
Exp* exp;
ExpList* explist;
Stm* stm;
IdList* idlist;
TableElementList* table_element_list;
ColumnDef* column_def;
DataType* data_type;
FromConstructor* from_constructor;
Identity* identity;
SequenceGeneratorOptionList* seq_gen_options;
SequenceGeneratorOption* seq_gen_option;
AlterTableAction* alter_table_action;
QualifiedName* qname;
XMLTypeModifier* XML_type_modifier;
PrimaryXMLTypeModifier primary_XML_type_modifier;
}

%token <string_literal> STRING_LITERAL
%token <num> INTEGER_LITERAL
%token <id> IDENTIFIER
%token SELECT_KW
%token DELETE_KW
%token INSERT_KW
%token ALTER_KW
%token COLUMN_KW
%token INTO_KW
%token VALUES_KW
%token GENERATED_KW
%token ALWAYS_KW
%token IDENTITY_KW
%token INCREMENT_KW
%token MAXVALUE_KW
%token XMLEXISTS_KW
%token VALID_KW
%token NULL_KW
%token IS_KW
%token BY_KW
%token NO_KW
%token AS_KW
%token UNDER_KW
%token TYPE_KW
%token DEFAULT_KW
%token START_KW
%token WITH_KW
%token ADD_KW
%token FROM_KW
%token JOIN_KW
%token INNER_KW
%token OUTER_KW
%token LEFT_KW
%token RIGHT_KW
%token FULL_KW
%token ON_KW
%token WHERE_KW
%token TRUE_KW
%token FALSE_KW
%token UNKNOWN_KW
%token OR_KW
%token AND_KW
%token MOD_KW
%token NOT_KW
%token CREATE_KW
%token TABLE_KW
%token SMALLINT_KW
%token INTEGER_KW
%token INT_KW
%token BIGINT_KW
%token CHAR_KW
%token CHARACTER_KW
%token VARYING_KW
%token VARCHAR_KW
%token XML_KW
%token XMLDOCUMENT_KW
%token LEQ
%token GEQ
%token EQUAL
%token NOT_EQUAL

/*
%type <exp> primary_expression
%type <exp> unary_expression
%type <exp> multiplicative_expression
%type <exp> additive_expression
%type <exp> relational_expression
%type <exp> equality_expression
%type <exp> and_expression
%type <exp> or_expression
%type <exp> expression
*/

%type <stm> stm
%type <stm> statement
%type <stm> select_statement
%type <stm> insert_statement
%type <stm> delete_statement
%type <stm> table_definition
%type <stm> alter_table_statement
%type <stm> user_defined_type_definition

%type <exp> where_criteria
%type <exp> where_criteria_opt

%type <idlist> select_item_seq

%type <id> identifier
%type <id> select_item
%type <id> table_reference
%type <id> table_factor

%type <alter_table_action> alter_table_action

%type <idlist> table_reference_seq
%type <idlist> column_name_list
%type <table_element_list> table_element_list
%type <table_element_list> table_contents_source
%type <column_def> table_element
%type <column_def> column_definition
%type <data_type> data_type
%type <data_type> predefined_type
%type <data_type> exact_numeric_type
%type <data_type> character_string_type
%type <data_type> XML_type

%type <exp> unsigned_literal
%type <exp> unsigned_numeric_literal
%type <exp> general_literal
%type <exp> character_string_literal
%type <exp> unsigned_value_specification
%type <exp> row_value_special_case
%type <exp> contextually_typed_row_value_expression
%type <exp> nonparenthesized_value_expression_primary
%type <explist> contextually_typed_row_value_expression_list
%type <explist> contextually_typed_table_value_constructor

%type <from_constructor> from_constructor

%type <identity> column_definition_clause_opt
%type <identity> column_definition_clause
%type <identity> identity_column_specification

%type <seq_gen_options> sequence_generator_options_opt
%type <seq_gen_options> sequence_generator_options
%type <seq_gen_options> common_sequence_generator_options

%type <seq_gen_option> common_sequence_generator_option
%type <seq_gen_option> sequence_generator_start_with_option
%type <seq_gen_option> sequence_generator_increment_by_option
%type <seq_gen_option> sequence_generator_maxvalue_option

%type <qname> subtype_clause
%type <qname> subtype_clause_opt

%type <qname> user_defined_type_name
//%type <qname> schema_name
//%type <id> catalog_name

%type <primary_XML_type_modifier> primary_XML_type_modifier
%type <XML_type_modifier> XML_type_modifier

%nonassoc predicate

%%

stm: statement { $$ = $1; g_stm = $$ }
;

statement:	select_statement
			|	insert_statement
			|	delete_statement
			|	table_definition
			|	alter_table_statement
			|	user_defined_type_definition
;

identifier:	IDENTIFIER
;

user_defined_type_definition: CREATE_KW TYPE_KW
								user_defined_type_name
								subtype_clause_opt
								as_representation_opt								
								{
									$$ = new UserDefinedTypeDefStm($3, $4)
								}
;

user_defined_type_name:	identifier	{ $$ = new QualifiedName(NULL, $1) }
							|	user_defined_type_name '.' identifier	{ $$ = new QualifiedName($1, $3) }
;

/*
schema_name:	identifier	{ $$ = new QualifiedName(NULL, $1) }
				|	identifier '.' identifier	{ $$ = new QualifiedName($1, $3) }
;

catalog_name: identifier
;
*/

subtype_clause_opt:	{ $$ = NULL }
						|	subtype_clause
;

subtype_clause:	UNDER_KW user_defined_type_name	{ $$ = $2 }
;

as_representation_opt:
							|	as_representation
;

as_representation:	AS_KW representation
;

representation:	predefined_type
					|	'(' member_list ')'
;

member_list:	member
				|	member_list ',' member
;

member:	attribute_definition
;

attribute_definition:	identifier data_type
;

alter_table_statement: ALTER_KW TABLE_KW identifier alter_table_action	{ $$ = new AlterTableStm($3, $4) }
;

alter_table_action:	ADD_KW COLUMN_opt	column_definition { $$ = new AddColumnAlterTableAction($3) }
;

COLUMN_opt:
			|	COLUMN_KW
;

table_definition:	CREATE_KW /* table scope */ TABLE_KW identifier
	table_contents_source
	{
		$$ = new TableDefStm($3, $4)
	}
;

table_contents_source: '(' table_element_list ')' { $$ = Reverse($2) }
;

table_element_list:	table_element	{ $$ = new TableElementList($1, NULL) }
						|	table_element_list ',' table_element { $$ = new TableElementList($3, $1) }
;

table_element:	column_definition
;

column_definition:	identifier data_type
							column_definition_clause_opt
							{ $$ = new ColumnDef($1, $2, $3) }
;

column_definition_clause_opt:	{ $$ = NULL }
								|	column_definition_clause
;

column_definition_clause:	default_clause
								|	identity_column_specification
							/*	|	generation_clause*/
;

identity_column_specification:	GENERATED_KW ALWAYS_KW /*| BY DEFAULT*/ AS_KW IDENTITY_KW
											sequence_generator_options_opt
											{ $$ = new Identity($5) }
;

sequence_generator_options_opt:	{ $$ = NULL }
										|	sequence_generator_options
;

sequence_generator_options:	'(' common_sequence_generator_options ')'	{ $$ = $2 }
;

common_sequence_generator_options:	common_sequence_generator_option	{ $$ = new SequenceGeneratorOptionList($1, NULL) }
											|	common_sequence_generator_options common_sequence_generator_option		{ $$ = new SequenceGeneratorOptionList($2, $1) }
;

common_sequence_generator_option:	sequence_generator_start_with_option
											|	sequence_generator_increment_by_option
											|	sequence_generator_maxvalue_option
;

sequence_generator_start_with_option: START_KW WITH_KW INTEGER_LITERAL /*<sequence generator start value> */
													{ $$ = new StartWithSequenceGeneratorOption($3) }
;

sequence_generator_increment_by_option:	INCREMENT_KW BY_KW INTEGER_LITERAL /*<sequence generator increment> */
													{ $$ = new IncrementBySequenceGeneratorOption($3) }
;

sequence_generator_maxvalue_option:	MAXVALUE_KW INTEGER_LITERAL /* <sequence generator max value> */	{ $$ = new MaxValueSequenceGeneratorOption($2) }
											|	NO_KW MAXVALUE_KW	{ $$ = new NoMaxValueSequenceGeneratorOption() }
;

default_clause:	DEFAULT_KW
;

data_type:	predefined_type
;

predefined_type:	character_string_type
					|	exact_numeric_type
					|	XML_type
;

XML_type:	XML_KW	{ $$ = new XMLDataType(NULL) }
			|	XML_KW '(' XML_type_modifier ')'		{ $$ = new XMLDataType($3) }
;

XML_type_modifier:	primary_XML_type_modifier	{ $$ = new XMLTypeModifier($1) }
						|	primary_XML_type_modifier '(' secondary_XML_type_modifier ')'	{ $$ = new XMLTypeModifier($1) }
;

primary_XML_type_modifier:	IDENTIFIER
/*
DOCUMENT
| CONTENT
| SEQUENCE
*/

									{
										if (!stricmp($1, "DOCUMENT"))
											$$ = MODIFIER_DOCUMENT;
										else if (!stricmp($1, "CONTENT"))
											$$ = MODIFIER_CONTENT;
										else if (!stricmp($1, "SEQUENCE"))
											$$ = MODIFIER_SEQUENCE;
										else
											YYERROR;
									}
;

secondary_XML_type_modifier:	IDENTIFIER
/*
ANY
| UNTYPED
| XMLSCHEMA <XML valid according to what> [ <XML valid element clause> ]*/
;

character_string_type:	CHAR_KW '(' INTEGER_LITERAL ')'		{ $$ = new CharDataType($3) }
							|	CHARACTER_KW '(' INTEGER_LITERAL ')'	{ $$ = new CharDataType($3) }
							|	CHAR_KW VARYING_KW '(' INTEGER_LITERAL ')'	{ $$ = new CharVaryingDataType($4) }
							|	CHARACTER_KW VARYING_KW '(' INTEGER_LITERAL ')' { $$ = new CharVaryingDataType($4) }
							|	VARCHAR_KW '(' INTEGER_LITERAL ')' { $$ = new VarCharDataType($3) }
;

exact_numeric_type:	SMALLINT_KW		{ $$ = new NumericDataType() }
						|	INTEGER_KW		{ $$ = new NumericDataType() }
						|	INT_KW		{ $$ = new NumericDataType() }
						|	BIGINT_KW		{ $$ = new NumericDataType() }
;

insert_statement:	INSERT_KW INTO_KW identifier from_constructor	{ $$ = new InsertStm($3, $4) }
;

from_constructor:	'(' column_name_list ')' contextually_typed_table_value_constructor { $$ = new FromConstructor(Reverse($2), Reverse($4)) }
;

contextually_typed_table_value_constructor: VALUES_KW contextually_typed_row_value_expression_list	{ $$ = $2 }
;

contextually_typed_row_value_expression_list:	contextually_typed_row_value_expression	{ $$ = new ExpList($1, NULL) }
															|	contextually_typed_row_value_expression_list ',' contextually_typed_row_value_expression	{ $$ = new ExpList($3, $1) }
;

contextually_typed_row_value_expression:	row_value_special_case
													|	contextually_typed_row_value_constructor
;

row_value_special_case: nonparenthesized_value_expression_primary
;

contextually_typed_row_value_constructor:	common_value_expression
												/*	|	boolean_value_expression */
;

value_expression_primary:	parenthesized_value_expression
								|	nonparenthesized_value_expression_primary
;

parenthesized_value_expression: '(' value_expression ')'
;

value_expression:	common_value_expression
					|	boolean_value_expression
				/*	| <row value expression>
					*/
;

common_value_expression:	numeric_value_expression
						/*		|	string_value_expression */
								|	XML_value_expression
;

numeric_value_expression:	term
								|	numeric_value_expression '+' term
								|	numeric_value_expression '-' term
;

term:	factor
	|	term '*' factor
	|	term '/' factor
;

factor:	numeric_primary
		|	'-' numeric_primary
		|	'+' numeric_primary
;

numeric_primary:	value_expression_primary
				/*	|	numeric_value_function */
;

nonparenthesized_value_expression_primary:	unsigned_value_specification
;

unsigned_value_specification:	unsigned_literal
;

unsigned_literal:	unsigned_numeric_literal
					|	general_literal
;

general_literal:	character_string_literal
;

unsigned_numeric_literal:	INTEGER_LITERAL	{ $$ = sql_A_Const($1) }
;

character_string_literal:	STRING_LITERAL	{ $$ = new CharLiteralExp($1) }
;

column_name_list:	identifier								{ $$ = new IdList($1, NULL) }
					|	column_name_list ',' identifier	{ $$ = new IdList($3, $1) }
;

select_statement:	SELECT_KW select_item_seq
						FROM_KW table_reference_seq
						where_criteria_opt
						{
						$$ = new SelectStm(Reverse($2), Reverse($4), $5)
						}
;

delete_statement:	DELETE_KW
						FROM_KW identifier
						where_criteria_opt
						{
						$$ = new DeleteStm($3, $4)
						}
;

select_item: identifier as_opt
;

select_item_seq:	select_item								{ $$ = new IdList($1, NULL) }
					|	select_item_seq ',' select_item	{ $$ = new IdList($3, $1) }
;

as_opt:
		|	AS_KW identifier
;

table_reference_seq: table_reference								{ $$ = new IdList($1, NULL) }
						|	table_reference_seq ',' table_reference	{ $$ = new IdList($3, $1) }
;

table_reference:	table_factor
					|	joined_table
;

table_factor: identifier
;

joined_table:	qualified_join
;

qualified_join:	table_reference join_type JOIN_KW table_reference join_specification
;

join_type:	INNER_KW
			|	LEFT_KW OUTER_opt
			|	RIGHT_KW OUTER_opt
			|	FULL_KW OUTER_opt
;

OUTER_opt:	/*empty*/
			|	OUTER_KW
;

join_specification: join_condition
					/*	|	named_columns_join */
;

join_condition: ON_KW search_condition /*{ $$ = $1 }*/
;

search_condition: boolean_value_expression
;

/*
primary_expression:	identifier						{ $$ = sql_A_Id($1) }
						|	identifier '.' identifier	{ $$ = sql_A_Binop('.', sql_A_Id($1), sql_A_Id($3)) }
						|	INTEGER_LITERAL				{ $$ = sql_A_Const($1) }
						|	STRING_LITERAL					{ $$ = new CharLiteralExp($1) }
						|	'(' expression ')'			{ $$ = $2 }
;

unary_expression:	primary_expression
					|	'-' primary_expression		{ $$ = sql_A_Unop('-', $2) }
					|	NOT_KW primary_expression	{ $$ = sql_A_Unop('!', $2) }
;

multiplicative_expression:		unary_expression
								|		multiplicative_expression '*' unary_expression		{ $$ = sql_A_Binop('*', $1, $3) }
								|		multiplicative_expression '/' unary_expression		{ $$ = sql_A_Binop('/', $1, $3) }
								|		multiplicative_expression MOD_KW unary_expression	{ $$ = sql_A_Binop('%', $1, $3) }
;

additive_expression:	multiplicative_expression
						|	additive_expression '+' multiplicative_expression	{ $$ = sql_A_Binop('+', $1, $3) }
						|	additive_expression '-' multiplicative_expression	{ $$ = sql_A_Binop('-', $1, $3) }
;

relational_expression:	additive_expression
							|	relational_expression '<' additive_expression	{ $$ = sql_A_Binop('>', $1, $3) }
							|	relational_expression '>' additive_expression	{ $$ = sql_A_Binop('<', $1, $3) }
							|	relational_expression LEQ additive_expression	{ $$ = sql_A_Binop('<=', $1, $3) }
							|	relational_expression GEQ additive_expression	{ $$ = sql_A_Binop('>=', $1, $3) }
;

equality_expression:	relational_expression
					|	equality_expression EQUAL relational_expression			{ $$ = sql_A_Binop('==', $1, $3) }
					|	equality_expression NOT_EQUAL relational_expression	{ $$ = sql_A_Binop('!=', $1, $3) }
;

and_expression:	equality_expression
					|	and_expression AND_KW equality_expression					{ $$ = sql_A_Binop('&&', $1, $3) }
;

or_expression: and_expression
				|	or_expression OR_KW and_expression								{ $$ = sql_A_Binop('||', $1, $3) }
;

expression: or_expression
;
*/

where_criteria:	WHERE_KW search_condition { $$ = NULL/*$2*/ }
;

boolean_value_expression:	boolean_term
								|	boolean_value_expression OR_KW boolean_term
;

boolean_term:	boolean_factor
				|	boolean_term AND_KW boolean_factor
;

boolean_factor:	boolean_test
					|	NOT_KW boolean_test
;

boolean_test:	boolean_primary
				|	boolean_primary IS_KW NOT_opt truth_value
;

truth_value:	TRUE_KW
				|	FALSE_KW
				|	UNKNOWN_KW
;

boolean_primary:	/*predicate
					|*/	boolean_predicand
					|	XML_predicate
;

boolean_predicand:	parenthesized_boolean_value_expression
						|	nonparenthesized_value_expression_primary

					/* predicate */
						|	boolean_predicand comp_op row_value_predicand
					/*	|	boolean_predicand IS_KW NOT_opt NULL_KW */
					/*	|	common_value_expression comp_op row_value_predicand*/
;

parenthesized_boolean_value_expression:	'(' boolean_value_expression ')'
;

where_criteria_opt:	{ $$ = NULL }
						|	where_criteria
;

/*
predicate:
	comparison_predicate
	| <between predicate>
	| <in predicate>
	| <like predicate>
	| <similar predicate>
	| <null predicate>
	| <quantified comparison predicate>
	| <exists predicate>
	| <unique predicate>
	| <normalized predicate>
	| <match predicate>
	| <overlaps predicate>
	| <distinct predicate>
	| <member predicate>
	| <submultiset predicate>
	| <set predicate>
	| <type predicate>
;
*/

XML_predicate:
/*		XML_content_document_predicate */
		XML_exists_predicate
/*	|	XML_valid_predicate*/
;


comparison_predicate:	nonparenthesized_value_expression_primary/*row_value_predicand*/ comparison_predicate2
;

comparison_predicate2:	comp_op row_value_predicand
;

comp_op:	EQUAL
		|	NOT_EQUAL
/*
| <not equals operator>
| <less than operator>
| <greater than operator>
| <less than or equals operator>
| <greater than or equals operator>
*/
;

row_value_predicand:	nonparenthesized_value_expression_primary
					/*	|	row_value_constructor_predicand*/
;

/*
row_value_special_case:	nonparenthesized_value_expression_primary
;
*/

/*
row_value_constructor_predicand:	common_value_expression
										|	boolean_predicand
										| <explicit row value constructor>
;
*/

XML_content_document_predicate:	XML_value_expression IS_KW NOT_opt IDENTIFIER /* CONTENT | DOCUMENT */
;

NOT_opt:
		|	NOT_KW
;

XML_exists_predicate:	XMLEXISTS_KW '(' XQuery_expression /*[ <XML query argument list> ]*/ ')'

XML_valid_predicate:	XML_value_expression IS_KW NOT_opt VALID_KW
							IDENTIFIER	/* DOCUMENT | CONTENT | SEQUENCE */
/*[ <XML valid according to clause> ]*/
;

XQuery_expression:	/* TODO */
;

XML_value_function:	XML_document
;

XML_document:	XMLDOCUMENT_KW '(' { parse_xpath() }
/*[ <XML returning clause> ]*/ ')'
;

XML_value_expression:	XML_primary
;

XML_primary:	value_expression_primary
				|	XML_value_function
;

%%
