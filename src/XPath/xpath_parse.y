%{

void xpath_error (/*YYLTYPE *llocp,*/ char const *s);
int xpath_lex(/*YYSTYPE *lvalp, YYLTYPE *llocp*/);

extern Exp* g_exp;

#define YYERROR_VERBOSE

#define yyfalse	0
#define yytrue		1

union YYSTYPE;

     %}

/* %glr-parser*/
%locations
%name-prefix="xpath_"

%union {
int num;
System::StringW* id;
System::StringW* string_literal;
Exp* exp;
Step* step;
StepList* steps;
ExpList* expList;
QName* qname;
NodeTest* nodetest;
}

%token <num> INTEGER_LITERAL
%token <string_literal> STRING_LITERAL
%token identifier
%token TWO_COLON
%token TWO_PUNCT
%token TWO_SLASH
%token <id> NCName
%token AxisName
%token OR
%token AND
%token EQ
%token NEQ
%token LTEQ
%token GTEQ
%token DIV
%token IDIV
%token MOD
%token ELEMENT_KW
%token INSTANCE_KW
%token OF_KW
%token EMPTY_SEQUENCE_KW
%token EMPTY_ELEMENT
%token ELEMENT_END

%type <qname> QName
%type <qname> QNameOrWildcard
%type <qname> Wildcard
%type <nodetest> NodeTest
%type <nodetest> NameTest
%type <nodetest> KindTest

%type <nodetest> SequenceType	// TODO
%type <nodetest> ItemType	// TODO

%type <steps> LocationPath
%type <steps> AbsoluteLocationPath
%type <steps> RelativeLocationPath
%type <step> StepExpr
%type <step> AxisStep
%type <step> FilterExpr
%type <exp> Number
%type <exp> ContextItemExpr
%type <exp> FunctionCall
%type <exp> PathExpr
%type <exp> Expr
%type <exp> ExprSingle
%type <exp> OrExpr
%type <exp> AndExpr
%type <exp> EqualityExpr
%type <exp> RelationalExpr
%type <exp> AdditiveExpr
%type <exp> MultiplicativeExpr
%type <exp> InstanceofExpr
%type <exp> TreatExpr
%type <exp> CastableExpr
%type <exp> CastExpr
%type <exp> UnaryExpr
%type <exp> UnionExpr
%type <exp> PrimaryExpr
%type <exp> PredicateExpr
%type <exp> Predicate
%type <expList> ExprList
%type <expList> Predicates
%type <expList> Predicates_opt

%type <num> AxisSpecifier
%type <num> AxisName

%type <exp> XPath

     %%

XPath:	Expr { $$ = $1; g_exp = $$; YYACCEPT }
	/*	|	Expr ')' { $$ = $1; g_exp = $$; YYACCEPT } */
;

Expr: ExprSingle			{ $$ = $1 }
	|	Expr ',' ExprSingle	{ $$ = new BinopExp($1, ',', $3) }
;

ExprSingle:	OrExpr
;

LocationPath:	RelativeLocationPath
			/*	|	AbsoluteLocationPath*/
;

AbsoluteLocationPath:  '/' RelativeLocationPath/*_opt*/
							/*	| AbbreviatedAbsoluteLocationPath*/
;

RelativeLocationPath:   StepExpr { $$ = new StepList($1, NULL) }
							|	StepExpr '/'	RelativeLocationPath { $$ = new StepList($1, $3) }
						/*	|	AbbreviatedRelativeLocationPath*/
;

/*
RelativeLocationPath_opt:
								| RelativeLocationPath
;
*/

AbbreviatedAbsoluteLocationPath:	TWO_SLASH RelativeLocationPath
;

AbbreviatedRelativeLocationPath:   RelativeLocationPath TWO_SLASH StepExpr
;

AbbreviatedStep:	'.'
				   |	TWO_PUNCT
;

AbbreviatedAxisSpecifier:
								|	'@'
;

StepExpr:	AxisStep
			|	FilterExpr
;

AxisStep:	AxisSpecifier NodeTest Predicates_opt { $$ = new AxisStep($1, $2, Reverse($3)) }
/*	|	AbbreviatedStep*/
;

AxisSpecifier:	AxisName TWO_COLON
			/*	|	AbbreviatedAxisSpecifier*/

Predicates:	Predicate { $$ = new ExpList($1, NULL) }
			|	Predicates Predicate { $$ = new ExpList($2, $1) }
;

Predicates_opt: { $$ = NULL }
				|	Predicates
;

NodeTest:	NameTest
			|	KindTest
			/*
			|	NodeType '(' ')'
			|	'processing-instruction' '(' Literal ')'  
			*/
;

KindTest:	ELEMENT_KW '(' ')'									{ $$ = new ElementNodeTest(NULL, nullptr) }
			|	ELEMENT_KW '(' QNameOrWildcard')'				{ $$ = new ElementNodeTest($3, nullptr) }
			|	ELEMENT_KW '(' QNameOrWildcard ',' QName ')'	{ $$ = new ElementNodeTest($3, $5) }
;

NameTest:	Wildcard	{ $$ = new NameNodeTest($1) }
			|	QName	{ $$ = new NameNodeTest($1) }
;

QNameOrWildcard:	'*'	{ $$ = nullptr }
					|	QName
;

Wildcard:	'*'				{ $$ = NULL }
			|	NCName ':' '*'	{ $$ = new QName($1, &star_str) }
			|	'*' ':' NCName	{ $$ = new QName(&star_str, $3) }
;

QName:	NCName	{ $$ = new QName(nullptr, $1) }
		|	NCName ':' NCName	{ $$ = new QName($1, $3) }
;

Predicate: '[' PredicateExpr ']' { $$ = $2 }
;

PredicateExpr:	Expr
;

Number: INTEGER_LITERAL	{ $$ = NumberExp($1) }
;

PrimaryExpr:/*	VariableReference  
				|*/	'(' Expr ')' { $$ = $2 }
			/*	|	Literal*/
				|	Number
				|	ContextItemExpr
				|	FunctionCall
				|	Constructor
;

ExprList:	ExprSingle			{ $$ = new ExpList($1, NULL) }
			|	ExprList ',' ExprSingle	{ $$ = new ExpList($3, $1) }
;

FunctionCall: QName '(' ExprList ')' { $$ = new FunctionCallExp($1, Reverse($3)) }

ContextItemExpr: '.' { $$ = new ContextItemExp() }
;

Constructor:	DirectConstructor
;

DirectConstructor:	DirElemConstructor
/*						|	DirCommentConstructor
						|	DirPIConstructor 
*/
;

DirElemConstructor:	'<' QName DirAttributeList_opt EMPTY_ELEMENT
						|	'<' QName DirAttributeList_opt '>' DirElemContents ELEMENT_END QName '>'
;

DirAttributeList_opt:
							|	DirAttributeList
;

DirAttributeList:	DirAttribute
					|	DirAttributeList DirAttribute
;

DirAttribute:	QName EQ STRING_LITERAL
;

DirElemContents:	DirElemContent
					|	DirElemContents DirElemContent
;

DirElemContent:	DirectConstructor
;

OrExpr:	AndExpr  
		|	OrExpr OR AndExpr
;

AndExpr:    EqualityExpr				{ $$ = $1 }
		|		AndExpr AND EqualityExpr { $$ = new BinopExp($1, 'AND', $3) }
;

EqualityExpr:  RelationalExpr  
				|	EqualityExpr EQ RelationalExpr	{ $$ = new BinopExp($1, '=', $3) }
				|	EqualityExpr NEQ RelationalExpr	{ $$ = new BinopExp($1, '!=', $3) }

RelationalExpr:	AdditiveExpr  
					|	RelationalExpr '<' AdditiveExpr { $$ = new BinopExp($1, '<', $3) }
					|	RelationalExpr '>' AdditiveExpr { $$ = new BinopExp($1, '>', $3) }
					|	RelationalExpr LTEQ AdditiveExpr	{ $$ = new BinopExp($1, '<=', $3) }
					|	RelationalExpr GTEQ AdditiveExpr	{ $$ = new BinopExp($1, '>=', $3) }
;

AdditiveExpr:  MultiplicativeExpr
				|	AdditiveExpr '+' MultiplicativeExpr	{ $$ = new BinopExp($1, '+', $3) }
				|	AdditiveExpr '-' MultiplicativeExpr	{ $$ = new BinopExp($1, '-', $3) }
;

MultiplicativeExpr:	UnionExpr
						|	MultiplicativeExpr '*' UnionExpr	{ $$ = new BinopExp($1, '*', $3) }
						|	MultiplicativeExpr DIV UnionExpr	{ $$ = new BinopExp($1, 'div', $3) }
						|	MultiplicativeExpr IDIV UnionExpr	{ $$ = new BinopExp($1, 'idiv', $3) }
						|	MultiplicativeExpr MOD UnionExpr	{ $$ = new BinopExp($1, 'mod', $3) }
;

UnaryExpr:   ValueExpr
			|	'-' UnaryExpr	{ $$ = new UnopExp($2, '-') }
			|	'+' UnaryExpr	{ $$ = new UnopExp($2, '+') }
;

ValueExpr:	PathExpr
;

/*
UnionExpr:	
			|	UnionExpr '|' PathExpr	{ $$ = new BinopExp($1, '|', $3) }
;
*/

UnionExpr:	IntersectExceptExpr
		/*	|	UnionExpr '|' IntersectExceptExpr */
;

IntersectExceptExpr:	InstanceofExpr /*( ("intersect" | "except") InstanceofExpr )*  */
;

PathExpr:	LocationPath  { $$ = new PathExp($1)}
		/*	|	FilterExpr '/' RelativeLocationPath*/
		/*	|	FilterExpr
			|	FilterExpr TWO_SLASH RelativeLocationPath
*/
;

CastExpr:	UnaryExpr /*( "cast" "as" SingleType )?  */
;

CastableExpr:	CastExpr /*( "castable" "as" SingleType )? : */
;

TreatExpr:	CastableExpr /*( "treat" "as" SequenceType )? : */
;

InstanceofExpr:	TreatExpr
					|	TreatExpr INSTANCE_KW OF_KW SequenceType	{ $$ = new InstanceOfExp($1, $4) }
;

SequenceType:	EMPTY_SEQUENCE_KW '(' ')'	{ $$ = NULL }
				|	ItemType
				|	ItemType OccurrenceIndicator		{ ASSERT(0) }
;

ItemType:	KindTest	/* | ("item" '(' ')') | AtomicType */
;

OccurrenceIndicator:	'?'
						|	'*'
						|	'+'
;

AtomicType:	QName 
;

FilterExpr:	PrimaryExpr Predicates_opt	{ $$ = new FilterStep($1, Reverse($2)) }
;

     %%
