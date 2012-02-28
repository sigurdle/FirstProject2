#include "StdAfx.h"

// Global stuff

void fput8(FILE* fp, BYTE v);
void fput16(FILE* fp, WORD v);
void fput32(FILE* fp, DWORD v);

extern int m_try;
void __cdecl jwarn(const char* msg, ...);
void __cdecl jerror(const char* msg, ...);
void __cdecl jfatalerror(const char* msg, ...);

static FILE* fpin;
static FILE* fileout;

int _getc(FILE*)
{
	int c = fgetc(fpin);
	if (c == '\n')
	{
	//	m_line++;
	}
	return c;
}

void _ungetc(int c, FILE*)
{
	if (c == '\n')
	{
	//	m_line--;
	}
	ungetc(c, fpin);
}

static void SkipSpaces()
{
	int c;
	while (isspace(c = _getc(fpin)))
		;
	_ungetc(c, fpin);
}

void eatchar(FILE* fp, int c)
{
	int c2 = getc(fp);
	if (c != c2)
	{
		printf("Expected %c\n", c);
		exit(1);
	}
}

////////////////////////////////////////////////

#include "../COFFPE/JavaClassFile.h"

////////////////////////////////////////////////
// Java tokens

#include "token.h"

#define KWF_ClassModifier	1
#define KWF_FieldModifier	2
#define KWF_MethodModifier	4
#define KWF_NumericType		8

enum
{
KW_ABSTRACT,
KW_PUBLIC,
KW_PROTECTED,
KW_PRIVATE,
KW_STATIC,
KW_FINAL,
KW_STRICTFP,
KW_CLASS,
KW_IF,
KW_IMPORT,
KW_EXTENDS,
KW_TRANSIENT,
KW_VOLATILE,
KW_BOOLEAN,
KW_VOID,
KW_BYTE,
KW_SHORT,
KW_INT,
KW_LONG,
KW_CHAR,
KW_FLOAT,
KW_DOUBLE,
KW_ELSE,
KW_RETURN,
KW_TRUE,
KW_FALSE,
KW_NULL,
KW_DO,
KW_FOR,
KW_WHILE,
KW_SWITCH,
KW_CASE,
KW_DEFAULT,
KW_SUPER,
};

static Keyword Keywords[] =
{
	"abstract",		KW_ABSTRACT, KWF_ClassModifier | KWF_MethodModifier,
	"public",		KW_PUBLIC, KWF_ClassModifier | KWF_FieldModifier | KWF_MethodModifier,
	"protected",	KW_PROTECTED, KWF_ClassModifier | KWF_FieldModifier | KWF_MethodModifier,
	"private",		KW_PRIVATE, KWF_ClassModifier | KWF_FieldModifier | KWF_MethodModifier,
	"static",		KW_STATIC, KWF_ClassModifier | KWF_FieldModifier | KWF_MethodModifier,
	"final",			KW_FINAL, KWF_ClassModifier | KWF_FieldModifier | KWF_MethodModifier,
	"strictfp",		KW_STRICTFP, KWF_ClassModifier,
	"transient",	KW_TRANSIENT, KWF_FieldModifier,
	"volatile",		KW_VOLATILE, KWF_FieldModifier,
	"class",			KW_CLASS, 0,
	"if",				KW_IF, 0,
	"import",		KW_IMPORT, 0,
	"extends",		KW_EXTENDS, 0,
	"boolean",		KW_BOOLEAN, 0,
	"void",			KW_VOID, 0,
	"byte",			KW_BYTE, KWF_NumericType,
	"short",			KW_SHORT, KWF_NumericType,
	"int",			KW_INT, KWF_NumericType,
	"long",			KW_LONG, KWF_NumericType,
	"char",			KW_CHAR, KWF_NumericType,
	"float",			KW_FLOAT, KWF_NumericType,
	"double",		KW_DOUBLE, KWF_NumericType,
	"else",			KW_ELSE, 0,
	"return",		KW_RETURN, 0,
	"true",			KW_TRUE, 0,
	"false",			KW_FALSE, 0,
	"null",			KW_NULL, 0,
	"do",				KW_DO, 0,
	"for",			KW_FOR, 0,
	"while",			KW_WHILE, 0,
	"switch",		KW_SWITCH, 0,
	"case",			KW_CASE, 0,
	"default",		KW_DEFAULT, 0,
	"super",			KW_SUPER, 0,
	NULL
};

static Keyword* IsKeyword(const char* name)
{
	int i = 0;
	while (Keywords[i].name)
	{
		if (!strcmp(name, Keywords[i].name))
		{
			return &Keywords[i];
		}
		i++;
	}
	return NULL;
}

#define NTOKENS	100

static CToken tokens[NTOKENS];

static CToken* curtok = tokens;
static int ntoken = 0;

static int savestack[100];
static int nsave = 0;

static void save()
{
	if (nsave > 100)
	{
		jfatalerror("INTERNAL ERROR: stack overflow\n");
	}
	savestack[nsave] = ntoken;
	nsave++;
}

static void restore()
{
	nsave--;
	int count = ntoken - savestack[nsave];
	ntoken -= count;
	curtok -= count;
	if (curtok < tokens)
		curtok += 9;
}

static CToken* GetToken()
{
	SkipSpaces();

	curtok++;
	ntoken++;

	if (curtok > tokens+NTOKENS-1)
	{
		curtok = tokens;
	}

	CToken token;

	int c = fgetc(fpin);

	if (isalpha(c))
	{
		std::string ident;
		ident += c;
		while (!feof(fpin))
		{
			c = fgetc(fpin);
			if (!(isalnum(c) || c == '_'))
			{
				ungetc(c, fpin);
				break;
			}

			ident += c;
		}

		Keyword* pkw;
		if (pkw = IsKeyword(ident.c_str()))
		{
			token.type = CToken::tok_keyword;
			token.pkw = pkw;
		}
		else
		{
			token.type = CToken::tok_ident;
			token.identlen = ident.length();
			token.ident = strdup(ident.c_str());
		}
	}
	else if (c >= '0' && c <= '9')
	{
		long int32 = c - '0';
		while (!feof(fpin))
		{
			c = fgetc(fpin);
			if (!(c >= '0' && c <= '9'))
			{
				ungetc(c, fpin);
				break;
			}

			int32 *= 10;
			int32 += c - '0';
		}

		token.type = CToken::tok_integer;
		token.int32 = int32;
	}
	else if (c == '{' ||
				c == '}' ||
				c == '(' ||
				c == ')' ||
				c == '[' ||
				c == ']' ||
				c == ',' ||
				c == ';' ||

				c == '*' ||
				c == '/' ||
				c == '%')
	{
		token.type = CToken::tok_symbol;
		token.symbol = c;
	}
	else if (c == '!')
	{
		int c2 = fgetc(fpin);
		if (c2 == '=')	// !=
		{
			token.type = CToken::tok_symbol;
			token.symbol = (c<<8) | c2;
		}
		else
		{
			ungetc(c2, fpin);
			token.type = CToken::tok_symbol;
			token.symbol = c;
		}
	}
	else if (c == '+' || c == '-' || c == '=' || c == '&' || c == '|')
	{
		int c2 = fgetc(fpin);
		if (c2 == c)	// ++ , -- , ==, '&&', '||'
		{
			token.type = CToken::tok_symbol;
			token.symbol = (c<<8) | c;
		}
		else
		{
			ungetc(c2, fpin);
			token.type = CToken::tok_symbol;
			token.symbol = c;
		}
	}

	//if (tokens.size() > 10)
		//tokens.pop_back();
//	memmove(&tokens[1], &tokens[0], 9*sizeof(CToken));

	//tokens.insert(tokens.begin(), token);
	//tokens[0] = token;
	*curtok = token;

	return curtok;
}

static void UngetToken()
{
	curtok--;
	if (curtok < tokens)
	{
		curtok = tokens+NTOKENS-1;
	}

	//	jfatalerror("INTERNAL ERROR: (Token overflow)\n");
	//}
}

static void EatSymbol(int c)
{
	if (curtok->type != CToken::tok_symbol || curtok->symbol != c)
	{
		jerror("Expected another character\n");
	}
	GetToken();
}

static CToken* Identifier()
{
	CToken* token = curtok;
	if (curtok->type != CToken::tok_ident)
	{
		jerror("Expected Identifier\n");
	}
	GetToken();

	return token;
}

////////////////////////////////////////////////////////////////////////////////////////
// Java parsing

void ImportStatement()
{
	SkipSpaces();

	while (!feof(fpin))
	{
		int c = fgetc(fpin);

		if (c == '.')
		{
			int c = fgetc(fpin);
			if (c == '*')
			{
				break;
			}
			else
			{
				ungetc(c, fpin);
			}
		}
		else
		{
			if (!isalnum(c))
			{
				ungetc(c, fpin);
				break;
			}
		}
	}

	eatchar(fpin, ';');
}

class node
{
public:
	node()
	{
		left = NULL;
		right = NULL;
	}

	~node()
	{
		delete left;
		delete right;
	}

	CToken tok;
	node* left;
	node* right;
};

enum
{
	STMT_IF,
	STMT_RETURN,
	STMT_EXPRESSION,
};

class CStatement
{
public:
	int m_type;
};

class CExprStatement : public CStatement
{
public:
	CExprStatement()
	{
		m_type = STMT_EXPRESSION;
		m_expr = NULL;
	}

	node* m_expr;
};

class CReturnStatement : public CStatement
{
public:
	CReturnStatement()
	{
		m_type = STMT_RETURN;
		m_expr = NULL;
	}

	node* m_expr;
};

class CIfStatement : public CStatement
{
public:
	CIfStatement()
	{
		m_type = STMT_IF;
		m_testexpr = NULL;
		m_substmt = NULL;
		m_elsestmt = NULL;
	}

	node* m_testexpr;
	CStatement* m_substmt;
	CStatement* m_elsestmt;
};

class CDeclarator
{
public:
	std::string m_name;
	std::string m_typeString;
};

class CMethod
{
public:
	CMethod()
	{
		m_access_flags = 0;
	}

	WORD m_access_flags;
	WORD m_name_index;
	WORD m_descriptor_index;

	std::string m_resultTypeString;

	std::string m_name;
	std::vector<CDeclarator*> m_parameters;
	std::vector<CStatement*> m_statements;
};

class CClass
{
public:
	CClass()
	{
		m_access_flags = 0;
		m_interfaces_count = 0;
	}

	WORD m_access_flags;
	WORD m_interfaces_count;

	std::string m_name;
	std::vector<CMethod*> m_methods;
};

// gen

void push_iconst(int value)
{
	switch (value)
	{
	case -1:
		fput8(fileout, JOP_iconst_m1);
		break;
		
	case 0:
		fput8(fileout, JOP_iconst_0);
		break;
		
	case 1:
		fput8(fileout, JOP_iconst_1);
		break;
		
	case 2:
		fput8(fileout, JOP_iconst_2);
		break;
		
	case 3:
		fput8(fileout, JOP_iconst_3);
		break;
		
	case 4:
		fput8(fileout, JOP_iconst_4);
		break;
		
	case 5:
		fput8(fileout, JOP_iconst_5);
		break;
		
	default:
		if (value >= -128 && value <= 127)
		{
			fput8(fileout, JOP_bipush);
			fput8(fileout, value);
		}
		else
		{
			fput8(fileout, JOP_sipush);
			fput16(fileout, value);
		}
		break;
	}
}

_variant_t evaluate(node* node)
{
	if (node->tok.type == CToken::tok_integer)
	{
		return _variant_t((long)node->tok.int32);
	}
	else if (node->tok.symbol == '=')
	{
		// left must be lvalue
	}
	else
	{
		_variant_t left = evaluate(node->left);
		_variant_t right = evaluate(node->right);

		if (node->tok.symbol == '==')
		{
			return (long)left == (long)right;
		}
		else if (node->tok.symbol == '+')
		{
			return (long)left + (long)right;
		}
		else if (node->tok.symbol == '-')
		{
			return (long)left - (long)right;
		}
		else if (node->tok.symbol == '*')
		{
			return (long)left * (long)right;
		}
		else if (node->tok.symbol == '/')
		{
			return (long)left / (long)right;
		}
		else if (node->tok.symbol == '%')
		{
			return (long)left % (long)right;
		}
	}
	return (long)0;
}

char* opstrings[] =
{
	"nop",
	"aconst_null",
	"iconst_m1",
	"iconst_0",
	"iconst_1",
	"iconst_2",
	"iconst_3",
	"iconst_4",
	"iconst_5",
	"lconst_0",
	"lconst_1",
	"fconst_0",
	"fconst_1",
	"fconst_2",
	"dconst_0",
	"dconst_1",
	"bipush",
	"sipush",
	"ldc",
	"ldc_w",
	"ldc2_w",
	"iload",
	"lload",
	"fload",
	"dload",
	"aload",
	"iload_0",
	"iload_1",
	"iload_2",
	"iload_3",
	"lload_0",
	"lload_1",
	"lload_2",
	"lload_3",
	"fload_0",
	"fload_1",
	"fload_2",
	"fload_3",
	"dload_0",
	"dload_1",
	"dload_2",
	"dload_3",
	"aload_0",
	"aload_1",
	"aload_2",
	"aload_3",
	"iaload",
	"laload",
	"faload",
	"daload",
	"aaload",
	"baload",
	"caload",
	"saload",
	"istore",
	"lstore",
	"fstore",
	"dstore",
	"astore",
	"istore_0",
	"istore_1",
	"istore_2",
	"istore_3",
	"lstore_0",
	"lstore_1",
	"lstore_2",
	"lstore_3",
	"fstore_0",
	"fstore_1",
	"fstore_2",
	"fstore_3",
	"dstore_0",
	"dstore_1",
	"dstore_2",
	"dstore_3",
	"astore_0",
	"astore_1",
	"astore_2",
	"astore_3",
	"iastore",
	"lastore",
	"fastore",
	"dastore",
	"aastore",
	"bastore",
	"castore",
	"sastore",
	"pop",
	"pop2",
	"dup",
	"dup_x1",
	"dup_x2",
	"dup2",
	"dup2_x1",
	"dup2_x2",
	"swap",
	"iadd",
	"ladd",
	"fadd",
	"dadd",
	"isub",
	"lsub",
	"fsub",
	"dsub",
	"imul",
	"lmul",
	"fmul",
	"dmul",
	"idiv",
	"ldiv",
	"fdiv",
	"ddiv",
	"irem",
	"lrem",
	"frem",
	"drem",
	"ineg",
	"lneg",
	"fneg",
	"dneg",
	"ishl",
	"lshl",
	"ishr",
	"lshr",
	"iushr",
	"lushr",
	"iand",
	"land",
	"ior",
	"lor",
	"ixor",
	"lxor",
	"iinc",
	"i2l",
	"i2f",
	"i2d",
	"l2i",
	"l2f",
	"l2d",
	"f2i",
	"f2l",
	"f2d",
	"d2i",
	"d2l",
	"d2f",
	"i2b",
	"i2c",
	"i2s",
	"lcmp",
	"fcmpl",
	"fcmpg",
	"dcmpl",
	"dcmpg",
	"ifeq",
	"ifne",
	"iflt",
	"ifge",
	"ifgt",
	"ifle",
	"if_icmpeq",
	"if_icmpne",
	"if_icmplt",
	"if_icmpge",
	"if_icmpgt",
	"if_icmple",
	"if_acmpeq",
	"if_acmpne",
	"goto",
	"jsr",
	"ret",
	"tableswitch",
	"lookupswitch",
	"ireturn",
	"lreturn",
	"freturn",
	"dreturn",
	"areturn",
	"return",
	"getstatic",
	"putstatic",
	"getfield",
	"putfield",
	"invokevirtual",
	"invokespecial",
	"invokestatic",
	"invokeinterface",
	NULL,//"xxxunusedxxx1",
	"new",
	"newarray",
	"anewarray",
	"arraylength",
	"athrow",
	"checkcast",
	"instanceof",
	"monitorenter",
	"monitorexit",
	"wide",
	"multianewarray",
	"ifnull",
	"ifnonnull",
	"goto_w",
	"jsr_w",
};

void emit_op(BYTE op)
{
	//printf("%s", opstrings[op]);
	fput8(fileout, op);
}

int m_pos;

void branch()
{
	m_pos = ftell(fileout) - 1;
	fput16(fileout, 0);
}

void branch_to()
{
	long pos = ftell(fileout);
	fseek(fileout, m_pos+1, SEEK_SET);
	short offset = pos - m_pos;
//	fput16(fileout, offset);
	fseek(fileout, pos, SEEK_SET);
}

//int stackargs;	// number of values currently pushed on the stack

// returns the number of arguments that we've pushed on the stack
int emit_expr(node* node)
{
	if (node->tok.type == CToken::tok_integer)
	{
		push_iconst(node->tok.int32);
		return 1;
	}
	else if (node->tok.type == CToken::tok_keyword)
	{
		if (node->tok.pkw->n == KW_TRUE)
			push_iconst(1);
		else if (node->tok.pkw->n == KW_FALSE)
			push_iconst(0);

		return 1;
	}
	else if (node->tok.type == CToken::tok_ident)
	{
		emit_op(JOP_iload_0);
		return 1;
	}
	else if (node->tok.symbol == '=')
	{
		BYTE local_variable_index = 0;

		// push value2
		if (emit_expr(node->right) != 1)
			jfatalerror("Error in expression\n");

		// left must be lvalue
		emit_op(JOP_istore);
		fput8(fileout, local_variable_index);

		return 0;
	}
	else if (node->tok.symbol == '==' ||
				node->tok.symbol == '!=' ||
				node->tok.symbol == '<' ||
				node->tok.symbol == '>' ||
				node->tok.symbol == '<=' ||
				node->tok.symbol == '>=')
	{
		if (emit_expr(node->left) != 1)
			jerror("Expected value\n");

		if (emit_expr(node->right) != 1)
			jerror("Expected value\n");

	// Note, we emit the opposite op codes
		switch (node->tok.symbol)
		{
		case '==':
			emit_op(JOP_if_icmpne);
			break;
			
		case '!=':
			emit_op(JOP_if_icmpeq);
			break;

		case '<':
			emit_op(JOP_if_icmpgt);
			break;

		case '>':
			emit_op(JOP_if_icmplt);
			break;

		case '<=':
			emit_op(JOP_if_icmpge);
			break;

		case '>=':
			emit_op(JOP_if_icmple);
			break;
		}

		branch();
		return 2;
	}
	else if (node->tok.symbol == '&&')
	{
	// In the short-circuit approach the operators AND and OR are defined to have
	// semantic meanings such that:

	// A AND B       means      IF A THEN B ELSE FALSE END
   // A OR  B       means      IF A THEN TRUE ELSE B END

		if (emit_expr(node->left) != 2)
		{
			jerror("Expected boolean expression\n");
		}

	//	emit_op(JOP_if_icmpne);	// if left expr evaluates to false, skip right expression
	//	branch();

		branch_to();
		if (emit_expr(node->right) != 2)
		{
			jerror("Expected boolean expression\n");
		}

		return 2;
	}
	else if (node->tok.symbol == '||')
	{
		emit_expr(node->left);
	//	emit_op(JOP_if_icmpne);	// if left expr evaluates to true, skip right expression
	//	printf("\n");

		emit_expr(node->right);
	//	emit_op(JOP_if_icmpne);
	//	printf("\n");
	}
	else if (node->tok.symbol == '+' || node->tok.symbol == '-' || node->tok.symbol == '*' || node->tok.symbol == '/')
	{
		// push value1
		if (emit_expr(node->left) != 1)
			jfatalerror("Error in expression\n");
		
		// push value2
		if (emit_expr(node->right) != 1)
			jfatalerror("Error in expression\n");
		
		switch (node->tok.symbol)
		{
		case '+':
			{
				emit_op(JOP_iadd);
			}
			break;
			
		case '-':
			{
				emit_op(JOP_isub);
			}
			break;
			
		case '*':
			{
				emit_op(JOP_imul);
			}
			break;
			
		case '/':
			{
				emit_op(JOP_isub);
			}
			break;
		}

		return 1;
	}
	return 0;
}

void emit_stmt(CStatement* pstmt)
{
	if (pstmt->m_type == STMT_EXPRESSION)
	{
		CExprStatement* pExprStmt = (CExprStatement*)pstmt;

		if (emit_expr(pExprStmt->m_expr) != 0)
		{
			jfatalerror("Expression is not allowed as a statement here\n");
		}
	}
	else if (pstmt->m_type == STMT_IF)
	{
		CIfStatement* pifstmt = (CIfStatement*)pstmt;

		if (emit_expr(pifstmt->m_testexpr) != 2)
		{
			jerror("Expected boolean expression\n");
		}
		emit_stmt(pifstmt->m_substmt);

		branch_to();
		if (pifstmt->m_elsestmt)
			emit_stmt(pifstmt->m_elsestmt);
	}
	else if (pstmt->m_type == STMT_RETURN)
	{
		CReturnStatement* preturnstmt = (CReturnStatement*)pstmt;

		if (preturnstmt->m_expr)
		{
			if (emit_expr(preturnstmt->m_expr) == 2)
			{
				emit_op(JOP_iconst_1);
				emit_op(JOP_goto);
				fput16(fileout, 0);

				branch_to();
				emit_op(JOP_iconst_0);
			}

			emit_op(JOP_ireturn);
		}
		else
		{
			emit_op(JOP_return);
		}
	}
}

void emit_method_code(CMethod* pMethod)
{
	if (pMethod->m_name == "<init>")	// TODO, don't have this here
	{
		emit_op(JOP_aload_0);
		emit_op(JOP_invokespecial);
		fput16(fileout, 8);	// Methodref index
		emit_op(JOP_return);
	}
	else
	{
//		stackargs = pMethod->m_parameters.size();

		for (int i = 0; i < pMethod->m_statements.size(); i++)
		{
			emit_stmt(pMethod->m_statements[i]);
		}
	}
}

void emit_method(CMethod* pMethod)
{
	WORD max_stack = 2;	// TODO
   WORD max_locals = 1;	// TODO
	DWORD code_length = 0;	// Unknown at this time

	fput16(fileout, max_stack);
	fput16(fileout, max_locals);
	fput32(fileout, code_length);

	long pos = ftell(fileout);
	emit_method_code(pMethod);

// Write code length
	long pos2 = ftell(fileout);
	fseek(fileout, pos-4, SEEK_SET);
	fput32(fileout, pos2-pos);
	fseek(fileout, pos2, SEEK_SET);

	/*
    	u2 exception_table_length;
    	{    	u2 start_pc;
    	      	u2 end_pc;
    	      	u2  handler_pc;
    	      	u2  catch_type;
    	}	exception_table[exception_table_length];
		*/
	WORD exception_table_length = 0;
	fput16(fileout, exception_table_length);

	/*
    	u2 attributes_count;
    	attribute_info attributes[attributes_count];
	 */
	WORD attributes_count = 0;
	fput16(fileout, attributes_count);
}

/////////////////////////////////////////////////////////////////
// Expressions

node* Expression();
node* UnaryExpression();
node* Primary();

/*
Literal: 
	IntegerLiteral
	FloatingPointLiteral
	BooleanLiteral
	CharacterLiteral
	StringLiteral
	NullLiteral
*/
node* Literal()
{
	if (curtok->type == CToken::tok_integer)
	{
		node* pnode = new node;
		pnode->tok = *curtok;
		GetToken();
		return pnode;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_TRUE)
	{
		node* pnode = new node;
		pnode->tok.type = CToken::tok_integer;
		pnode->tok.int32 = 1;

		GetToken();
		return pnode;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_FALSE)
	{
		node* pnode = new node;
		pnode->tok.type = CToken::tok_integer;
		pnode->tok.int32 = 0;

		GetToken();
		return pnode;
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_NULL)
	{
		node* pnode = new node;
		pnode->tok.type = CToken::tok_integer;
		pnode->tok.int32 = 0;

		GetToken();
		return pnode;
	}
	else
	{
		return NULL;
	}
}

/*
MethodInvocation:
	MethodName ( ArgumentListopt )
	Primary . Identifier ( ArgumentListopt )
	super . Identifier ( ArgumentListopt )
	ClassName . super . Identifier ( ArgumentListopt )

*/
void MethodInvocation()
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_SUPER)
	{
		jerror("super not yet supported");
	}
}

/*
PrimaryNoNewArray:
	Literal
	Type . class 
	void . class 
	this
	ClassName.this
	( Expression )
	ClassInstanceCreationExpression
	FieldAccess
	MethodInvocation
	ArrayAccess
*/
node* PrimaryNoNewArray()
{
	if (curtok->symbol == '(')
	{
		GetToken();
		node* pnode = Expression();
		EatSymbol(')');
		return pnode;
	}
	else
	{
		return Literal();
	}
}

/*
Primary:
	PrimaryNoNewArray
	ArrayCreationExpression
*/
node* Primary()
{
	return PrimaryNoNewArray();
}

// These group left to right

/*
MultiplicativeExpression:
	UnaryExpression
	MultiplicativeExpression * UnaryExpression
	MultiplicativeExpression / UnaryExpression
	MultiplicativeExpression % UnaryExpression
*/
node* MultiplicativeExpression()
{
	node* pExpr = UnaryExpression();
	while (curtok->type == CToken::tok_symbol && (curtok->symbol == '*' || curtok->symbol == '/' || curtok->symbol == '%'))
	{
		node* pExpr2 = new node;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = UnaryExpression();

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
AdditiveExpression:
	MultiplicativeExpression
	AdditiveExpression + MultiplicativeExpression
	AdditiveExpression - MultiplicativeExpression
*/
node* AdditiveExpression()
{
	node* pExpr = MultiplicativeExpression();

	while (curtok->type == CToken::tok_symbol && (curtok->symbol == '+' || curtok->symbol == '-'))
	{
		node* pExpr2 = new node;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = MultiplicativeExpression();

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
ShiftExpression:
	AdditiveExpression
	ShiftExpression << AdditiveExpression
	ShiftExpression >> AdditiveExpression
	ShiftExpression >>> AdditiveExpression
*/
node* ShiftExpression()
{
	// TODO
	return AdditiveExpression();
	/*
	node* left = AdditiveExpression();

	if (curtok->symbol == '+' ||
		curtok->symbol == '-')
	{
		GetToken();

		node* pn = new node;
		pn->left = left;
		pn->right = MultiplicativeExpression();

		return pn;
	}
	else
	{
		return left;
	}
	*/
}

/*
RelationalExpression:
	ShiftExpression
	RelationalExpression < ShiftExpression
	RelationalExpression > ShiftExpression
	RelationalExpression <= ShiftExpression
	RelationalExpression >= ShiftExpression
	RelationalExpression instanceof ReferenceType
*/
node* RelationalExpression()
{
	// TODO
	return ShiftExpression();
}

/*
EqualityExpression:
	RelationalExpression
	EqualityExpression == RelationalExpression
	EqualityExpression != RelationalExpression
*/
node* EqualityExpression()
{
	node* pExpr = RelationalExpression();
	while (curtok->type == CToken::tok_symbol && (curtok->symbol == '==' || curtok->symbol == '!='))
	{
		node* pExpr2 = new node;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = RelationalExpression();

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
AndExpression:
	EqualityExpression
	AndExpression & EqualityExpression
*/
node* AndExpression()
{
	// TODO
	return EqualityExpression();
}

/*
ExclusiveOrExpression:
	AndExpression
	ExclusiveOrExpression ^ AndExpression
*/
node* ExclusiveOrExpression()
{
	return AndExpression();
}

/*
InclusiveOrExpression:
	ExclusiveOrExpression
	InclusiveOrExpression | ExclusiveOrExpression
*/
node* InclusiveOrExpression()
{
	return ExclusiveOrExpression();
}
/*
ConditionalAndExpression:
	InclusiveOrExpression
	ConditionalAndExpression && InclusiveOrExpression
*/
node* ConditionalAndExpression()
{
	node* pExpr = InclusiveOrExpression();
	while (curtok->type == CToken::tok_symbol && (curtok->symbol == '&&'))
	{
		node* pExpr2 = new node;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = InclusiveOrExpression();

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
ConditionalOrExpression:
	ConditionalAndExpression
	ConditionalOrExpression || ConditionalAndExpression
*/
node* ConditionalOrExpression()
{
	node* pExpr = ConditionalAndExpression();
	while (curtok->type == CToken::tok_symbol && (curtok->symbol == '||'))
	{
		node* pExpr2 = new node;
		pExpr2->tok = *curtok;
		GetToken();

		pExpr2->left = pExpr;
		pExpr2->right = ConditionalAndExpression();

		pExpr = pExpr2;
	}

	return pExpr;
}

/*
ConditionalExpression:
	ConditionalOrExpression
	ConditionalOrExpression ? Expression : ConditionalExpression
*/
node* ConditionalExpression()
{
	node* expr = ConditionalOrExpression();

	if (curtok->type == CToken::tok_symbol && curtok->symbol == '?')
	{
		GetToken();

	// TODO create '?' node

		node* pexpr = Expression();
		EatSymbol(':');
		return ConditionalExpression();
	}
	else
		return expr;
}

/*
LeftHandSide:
	ExpressionName
	FieldAccess
	ArrayAccess
	*/
void LeftHandSide()
{
}

/*
Assignment:
	LeftHandSide AssignmentOperator AssignmentExpression

AssignmentOperator: one of
	= *= /= %= += -= <<= >>= >>>= &= ^= |=
*/
void Assignment()
{
}

/*
AssignmentExpression:
	ConditionalExpression
	Assignment
	*/
node* AssignmentExpression()
{
	// TODO
	return ConditionalExpression();
}

/*
An Expression is any assignment expression:

Expression:
	AssignmentExpression
*/
node* Expression()
{
	return AssignmentExpression();
}

/*
PostfixExpression:
	Primary
	ExpressionName
	PostIncrementExpression
	PostDecrementExpression
*/
node* PostfixExpression()
{
	if (curtok->type == CToken::tok_ident)	// ExpressionName
	{
		node* pn = new node;
		pn->tok = *curtok;
		GetToken();

		return pn;
	}
	else
	{
		return Primary();
	}
}

// These group right to left

/*
PreIncrementExpression:
	++ UnaryExpression

PreDecrementExpression:
	-- UnaryExpression

UnaryExpressionNotPlusMinus:
	PostfixExpression
	~ UnaryExpression
	! UnaryExpression
	CastExpression

*/
node* UnaryExpressionNotPlusMinus()
{
	// TODO
	return PostfixExpression();
}

/*
UnaryExpression:
	PreIncrementExpression
	PreDecrementExpression
	+ UnaryExpression
	- UnaryExpression
	UnaryExpressionNotPlusMinus
*/

node* UnaryExpression()
{
	if (curtok->type == CToken::tok_symbol && curtok->symbol == '+')
	{
		GetToken();

		node* pnode = new node;
		pnode->right = UnaryExpression();
		return pnode;
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '-')
	{
		GetToken();

		node* pnode = new node;
		pnode->right = UnaryExpression();
		return pnode;
	}
	/*
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '++')
	{
		GetToken();
		UnaryExpression();
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '--')
	{
		GetToken();
		UnaryExpression();
	}
	else if (curtok->type == CToken::tok_symbol && curtok->symbol == '!')
	{
		// ! UnaryExpression
		GetToken();
		UnaryExpression();
	}
	*/
	else
	{
		return UnaryExpressionNotPlusMinus();
	}
}

//////////////////////////////////////////////////////////////////
// Statements

CClass* ClassDeclaration();
CStatement* Statement(CMethod* pMethod);
node* Expression();

/*
WhileStatement:
	while ( Expression ) Statement

WhileStatementNoShortIf:
	while ( Expression ) StatementNoShortIf
*/
CStatement* WhileStatement(CMethod* pMethod)
{
	if (curtok->type != CToken::tok_keyword || curtok->pkw->n != KW_WHILE)
	{
		jerror("Not a while statement\n");
	}
	GetToken();
//	printf("while(");

	EatSymbol('(');
	node* exprnode = Expression();
	EatSymbol(')');

//	printf(")\n");

	Statement(pMethod);

	return NULL;
}

/*
ForStatement:
	for ( ForInitopt ; Expressionopt ; ForUpdateopt )
		Statement

ForStatementNoShortIf:
	for ( ForInitopt ; Expressionopt ; ForUpdateopt )
		StatementNoShortIf

ForInit:
	StatementExpressionList
	LocalVariableDeclaration

ForUpdate:
	StatementExpressionList

StatementExpressionList:
	StatementExpression
	StatementExpressionList , StatementExpression
*/
CStatement* ForStatement(CMethod* pMethod)
{
	if (curtok->type != CToken::tok_keyword || curtok->pkw->n != KW_FOR)
	{
		jerror("Not a for statement\n");
	}
	GetToken();
	printf("for()\n");
	/*
	EatSymbol('(');
	EatSymbol(';');
	EatSymbol(';');
	EatSymbol(')');
	*/

	return NULL;
}

/*
SwitchBlockStatementGroups:
	SwitchBlockStatementGroup
	SwitchBlockStatementGroups SwitchBlockStatementGroup

SwitchBlockStatementGroup:
	SwitchLabels BlockStatements

SwitchLabels:
	SwitchLabel
	SwitchLabels SwitchLabel

SwitchLabel:
	case ConstantExpression :
	default :
*/

/*
SwitchBlock:
	{ SwitchBlockStatementGroupsopt SwitchLabelsopt }
*/
void SwitchBlock(CStatement* pStmt)
{
	EatSymbol('{');

	while (curtok->type == CToken::tok_keyword && (curtok->pkw->n == KW_CASE || curtok->pkw->n == KW_DEFAULT))
	{
	}
//	BlockStatements(pMethod);

	EatSymbol('}');
}
/*
SwitchStatement:
	switch ( Expression ) SwitchBlock
*/

CStatement* SwitchStatement(CMethod* pMethod)
{
	if (curtok->type != CToken::tok_keyword || curtok->pkw->n != KW_SWITCH)
	{
		jerror("Not a switch statement\n");
	}
	GetToken();

	EatSymbol('(');
	Expression();
	EatSymbol(')');

	SwitchBlock(NULL);

	return NULL;
}

/*
IfThenStatement:
	if ( Expression ) Statement
*/

/*
IfThenElseStatement:
	if ( Expression ) StatementNoShortIf else Statement
*/

/*
IfThenElseStatementNoShortIf:
	if ( Expression ) StatementNoShortIf else StatementNoShortIf
*/

CStatement* IfStatement(CMethod* pMethod)
{
	if (curtok->type != CToken::tok_keyword || curtok->pkw->n != KW_IF)
	{
		jerror("Not an if statement\n");
	}
	GetToken();

	CIfStatement* pstmt = new CIfStatement;

	EatSymbol('(');
	pstmt->m_testexpr = Expression();
	EatSymbol(')');

	pstmt->m_substmt = Statement(pMethod);

	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_ELSE)
	{
		GetToken();
		//printf("else\n");

		pstmt->m_elsestmt = Statement(pMethod);
	}

	return pstmt;
}

/*
ReturnStatement:
	return Expressionopt ;
*/
CStatement* ReturnStatement(CMethod* pMethod)
{
	if (curtok->type != CToken::tok_keyword || curtok->pkw->n != KW_RETURN)
	{
		jerror("Not a return statement\n");
	}
	GetToken();

	CReturnStatement* pstmt = new CReturnStatement;

	if (curtok->type != CToken::tok_symbol || curtok->symbol != ';')
	{
		jerror("void method can't return a value\n");
		pstmt->m_expr = Expression();
	}
	else
	{
		if (pMethod->m_resultTypeString != "V")
		{
			jerror("Expected a return expression\n");
		}
	}

	EatSymbol(';');

	return pstmt;
}

/*
StatementWithoutTrailingSubstatement:
	Block
	EmptyStatement
	ExpressionStatement
	SwitchStatement
	DoStatement
	BreakStatement
	ContinueStatement
	ReturnStatement
	SynchronizedStatement
	ThrowStatement
	TryStatement
*/

/*
Statement:
	StatementWithoutTrailingSubstatement
	LabeledStatement
	IfThenStatement
	IfThenElseStatement
	WhileStatement
	ForStatement
*/

CStatement* Statement(CMethod* pMethod)
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_IF)
	{
		return IfStatement(pMethod);
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_RETURN)
	{
		return ReturnStatement(pMethod);
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_FOR)
	{
		return ForStatement(pMethod);
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_WHILE)
	{
		return WhileStatement(pMethod);
	}
	else if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_SWITCH)
	{
		return SwitchStatement(pMethod);
	}
	else
	{
		// Try as expression statement
		CExprStatement* pStmt = new CExprStatement;
		pStmt->m_expr = Expression();
		EatSymbol(';');
		return pStmt;

		//jfatalerror("Not a statement\n");
	}

	/*
	node* pnode = Expression();

	_variant_t value = evaluate(pnode);

	printf("value = %d\n", (long)value);
	*/
	return NULL;
}

/*
BlockStatement:
	LocalVariableDeclarationStatement
	ClassDeclaration
	Statement
*/

void BlockStatement(CMethod* pMethod)
{
	CStatement* pStmt = Statement(pMethod);

	pMethod->m_statements.push_back(pStmt);


	/*
	m_try++;
	CToken* save = curtok;

	try
	{
		ClassDeclaration();
		m_try--;
		return;
	}
	catch(int)
	{
		curtok = save;
	}

	m_try--;

	jerror("Error\n");
	*/
}

/*
BlockStatements:
	BlockStatement
	BlockStatements BlockStatement
*/

void BlockStatementsopt(CMethod* pMethod)
{
	while (!feof(fpin))
	{
		if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
		{
			return;
		}

		BlockStatement(pMethod);
	}

	GetToken();
}

/*
Block:
	{ BlockStatementsopt }
*/
void Block(CMethod* pMethod)
{
	EatSymbol('{');
	//printf("{");

	BlockStatementsopt(pMethod);

	EatSymbol('}');
	//printf("}");
}
/*
IntegralType: one of
	byte short int long char
*/

/*
FloatingPointType: one of
	float double
*/
/*
NumericType:
	IntegralType
	FloatingPointType
*/
std::string NumericType()
{
	if (curtok->type == CToken::tok_keyword && (curtok->pkw->flags & KWF_NumericType))
	{
		CToken* t = curtok;
		GetToken();

		switch (t->pkw->n)
		{
		case KW_BYTE:			return "B";
		case KW_CHAR:			return "C";
		case KW_DOUBLE:		return "D";
		case KW_FLOAT:			return "E";
		case KW_INT:			return "I";
		case KW_LONG:			return "J";
		case KW_SHORT:			return "S";
		default:
			ATLASSERT(0);
		}
	}

	jerror("Invalid numeric type\n");
	return "";
}

/*
PrimitiveType:
	NumericType
	boolean
	*/
std::string PrimitiveType()
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_BOOLEAN)
	{
		GetToken();
		return "Z";
	}
	else
	{
		return NumericType();
	}

	jerror("Invalid Primitive Type\n");
}

std::string Type()
{
	m_try++;

	save();

	try
	{
		std::string type = PrimitiveType();
		m_try--;
		nsave--;
		return type;
	}
	catch(int n)
	{
		restore();
	}

	/*
	try
	{
		ReferenceType();
		m_try--;
		return;
	}
	catch(int)
	{
	}
	*/

	nsave--;
	m_try--;

	jfatalerror("Invalid Type\n");
	return "";
}

/*
 Checks for an optional 'extends ClassType'
 On return, cursor is at the next token to be processed
*/
void Superopt()
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_EXTENDS)
	{
		GetToken();
		CToken* idtok = Identifier();	// TODO ClassType(fp);
		printf(" extends %s", idtok->ident);
	}
}

/*
VariableInitializer:
	Expression
	ArrayInitializer
*/

/*
VariableDeclaratorId:
	Identifier
	VariableDeclaratorId [ ]
*/
void VariableDeclaratorId(CDeclarator* declarator)
{
	CToken* idtok = Identifier();
	declarator->m_name = idtok->ident;

	while (curtok->type == CToken::tok_symbol && curtok->symbol == '[')
	{
		GetToken();
		EatSymbol(']');

		declarator->m_typeString = '[' + declarator->m_typeString;
	}
}

/*
VariableDeclarator:
	VariableDeclaratorId
	VariableDeclaratorId = VariableInitializer
*/
void VariableDeclarator(CDeclarator* pDeclarator)
{
	VariableDeclaratorId(pDeclarator);

	if (curtok->type == CToken::tok_symbol && curtok->symbol == '=')
	{
		GetToken();
		// TODO
		//VariableInitializer();
	}
}

/*
VariableDeclarators:
	VariableDeclarator
	VariableDeclarators , VariableDeclarator
*/
void VariableDeclarators(std::string typeString)
{
	do
	{
		CDeclarator* pDeclarator = new CDeclarator;

		pDeclarator->m_typeString = typeString;

		VariableDeclarator(pDeclarator);

		if (curtok->type != CToken::tok_symbol || curtok->symbol != ',')
		{
			break;
		}

		printf(", ");
		GetToken();
	}
	while (!feof(fpin));
}

/*
FieldModifiers:
	FieldModifier
	FieldModifiers FieldModifier

FieldModifier: one of
	public protected private
	static final transient volatile
*/
void FieldModifiersopt()
{
	do
	{
		if (curtok->type == CToken::tok_keyword)
		{
			if (!(curtok->pkw->flags & KWF_FieldModifier))
			{
				break;
			}
		}
		else
		{
			jerror("Expected keyword\n");
		}

//		WORD modf = 0;

		GetToken();
	}
	while (!feof(fpin));
}

/*
FieldDeclaration:
	FieldModifiersopt Type VariableDeclarators ;
*/
int FieldDeclaration()
{
	FieldModifiersopt();
	std::string typeString = Type();
	VariableDeclarators(typeString);

	EatSymbol(';');
	printf(";\n");

	return 0;

	/*
		if (token.type == CToken::tok_keyword)
	{
	}
	else if (token.type == CToken::tok_ident)
	{
	}
	*/
}

/*
ResultType:
	Type
	void
*/
void ResultType(CMethod* pMethod)
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_VOID)
	{
		GetToken();
		pMethod->m_resultTypeString = "V";
	}
	else
	{
		pMethod->m_resultTypeString = Type();
	}
}

/*
FormalParameter:
	finalopt Type VariableDeclaratorId
*/

CDeclarator* FormalParameter(CMethod* pMethod)
{
	if (curtok->type == CToken::tok_keyword && curtok->pkw->n == KW_FINAL)
	{
		GetToken();
		//printf("final ");
	}

	CDeclarator* pDeclarator = new CDeclarator;
	pDeclarator->m_typeString = Type();
	VariableDeclaratorId(pDeclarator);

	return pDeclarator;
}

/*
FormalParameterList:
	FormalParameter
	FormalParameterList , FormalParameter
*/
void FormalParameterList(CMethod* pMethod)
{
	do
	{
		CDeclarator* pDeclarator = FormalParameter(pMethod);

		pMethod->m_parameters.push_back(pDeclarator);

		if (curtok->type != CToken::tok_symbol || curtok->symbol != ',')
		{
			break;
		}

		//printf(", ");
		GetToken();
	}
	while (!feof(fpin));
}

/*
MethodDeclarator:
	Identifer ( FormalParameterListopt )

*/
void MethodDeclarator(CMethod* pMethod)
{
	CToken* idtok = Identifier();
	pMethod->m_name = idtok->ident;

	EatSymbol('(');
	printf("(");

	if (curtok->symbol != ')')
	{
		FormalParameterList(pMethod);
	}

	EatSymbol(')');
	printf(")\n\n");
}

void MethodModifiersopt(CMethod* pMethod)
{
	WORD modf = 0;

	do
	{
		if (curtok->type == CToken::tok_keyword)
		{
			if (!(curtok->pkw->flags & KWF_MethodModifier))
			{
				break;
			}
		}
		else
		{
			jerror("Expected keyword\n");
		}

		switch (curtok->pkw->n)
		{
		case KW_ABSTRACT:
			break;
			
		case KW_PUBLIC:
			{
				if (modf & ACC_PUBLIC)
				{
					jerror("modifier public is specified more than once\n");
				}

				modf |= ACC_PUBLIC;
			}
			break;

		case KW_PROTECTED:
			break;

		case KW_PRIVATE:
			break;

		case KW_STATIC:
			modf |= ACC_STATIC;
			break;
		}

		GetToken();
	}
	while (!feof(fpin));

	pMethod->m_access_flags = modf;
}

/*
MethodHeader:
	MethodModifiersopt ResultType MethodDeclarator Throwsopt
*/
void MethodHeader(CMethod* pMethod)
{
	MethodModifiersopt(pMethod);
	ResultType(pMethod);
	MethodDeclarator(pMethod);
}

/*
MethodBody:
	Block 
	;
*/
void MethodBody(CMethod* pMethod)
{
	if (curtok->type == CToken::tok_symbol && curtok->symbol == ';')
	{
		printf(";");
		GetToken();
	}
	else
	{
		Block(pMethod);
	}
}

/*
MethodDeclaration:
	MethodHeader MethodBody
*/
CMethod* MethodDeclaration()
{
	CMethod* pMethod = new CMethod;

	MethodHeader(pMethod);
	MethodBody(pMethod);

	return pMethod;
}

/*
ClassMemberDeclaration:
	FieldDeclaration
	MethodDeclaration
	ClassDeclaration
	InterfaceDeclaration
	;			 
*/
void ClassMemberDeclaration(CClass* pClass)
{
	/*
	save();

	m_try++;

	try
	{
		FieldDeclaration();
		m_try--;
		nsave--;
		return;
	}
	catch(int n)
	{
		restore();
	}

	try
	{
	*/
		CMethod* pMethod = MethodDeclaration();

		pClass->m_methods.push_back(pMethod);
		/*
		m_try--;
		nsave--;
		return;
	}
	catch(int n)
	{
		restore();
	}

	try
	{
		ClassDeclaration();
		m_try--;
		nsave--;
		return;
	}
	catch(int n)
	{
		restore();
	}

	m_try--;
	nsave--;

	jfatalerror("Error\n");
	*/
}

/*
ClassBodyDeclaration:
	ClassMemberDeclaration
	InstanceInitializer
	StaticInitializer
	ConstructorDeclaration
*/

void ClassBodyDeclaration(CClass* pClass)
{
	ClassMemberDeclaration(pClass);

}

void ClassBodyDeclarationsopt(CClass* pClass)
{
	while (!feof(fpin))
	{
		if (curtok->type == CToken::tok_symbol && curtok->symbol == '}')
		{
			return;
		}

		ClassBodyDeclaration(pClass);
	}

	GetToken();
}

/*
ClassBody:
	{ ClassBodyDeclarationsopt }
*/
void ClassBody(CClass* pClass)
{
	EatSymbol('{');
	ClassBodyDeclarationsopt(pClass);
	EatSymbol('}');
}

void ClassModifiersopt(CClass* pClass)
{
	WORD modf = 0;

	do
	{
		if (curtok->type == CToken::tok_keyword)
		{
			if (!(curtok->pkw->flags & KWF_ClassModifier))
			{
				break;
			}
		}
		else
		{
			jerror("Expected keyword\n");
		}

		switch (curtok->pkw->n)
		{
		case KW_ABSTRACT:
			break;
			
		case KW_PUBLIC:
			{
				if (modf & ACC_PUBLIC)
				{
					jerror("modifier public is specified more than once\n");
				}

				modf |= ACC_PUBLIC;
			}
			break;

		case KW_PROTECTED:
			break;

		case KW_PRIVATE:
			break;

		case KW_STATIC:
			break;

		case KW_FINAL:
			{
				if (modf & ACC_FINAL)
				{
					jerror("modifier final is specified more than once\n");
				}

				modf |= ACC_FINAL;
			}
			break;

		case KW_STRICTFP:
			break;
		}

		GetToken();
	}
	while (!feof(fpin));

	pClass->m_access_flags = modf;
}

/*
ClassDeclaration:
	ClassModifiersopt class Identifier Superopt Interfacesopt ClassBody
*/
CClass* ClassDeclaration()
{
	CClass* pClass = new CClass;

	ClassModifiersopt(pClass);

	if (curtok->pkw->n != KW_CLASS)
	{
		jfatalerror("Not a class definition\n");
	}
	GetToken();

	CToken* idtok = Identifier();
	pClass->m_name = idtok->ident;

	Superopt();
//	Interfacesopt();

	if (TRUE)
	{
		CMethod* pMethod = new CMethod;
		pMethod->m_name = "<init>";
		pMethod->m_resultTypeString = "V";
		CReturnStatement* pStmt = new CReturnStatement;
		pMethod->m_statements.push_back(pStmt);

		pClass->m_methods.push_back(pMethod);
	}

	ClassBody(pClass);

	return pClass;
}

CClass* parse()
{
	CClass* pClass = NULL;

	while (!feof(fpin))
	{
		GetToken();

		if (curtok->type == CToken::tok_keyword)
		{
			if (curtok->pkw->n == KW_IMPORT)
			{
				ImportStatement();
			}
			else if ((curtok->pkw->flags & KWF_ClassModifier) || (curtok->pkw->n == KW_CLASS))
			{
				if (pClass)
				{
					jfatalerror("Can only have one class\n");
				}
				pClass = ClassDeclaration();
			}
		}
		else
			jerror("Unrecognized token");
	}

	return pClass;
}

///////////////////////////////////////////////////////////////
// Java class writer

class CPoolItem
{
public:
	CPoolItem()
	{
		tag = 0;
		bstr = NULL;
	}

	~CPoolItem()
	{
		if (tag == CONSTANT_Utf8)
		{
		//	SysFreeString(bstr);
			bstr = NULL;
		}
	}

	BYTE tag;
	union
	{
		WORD uint16;

		DWORD uint32;

		BSTR bstr;

		struct
		{
			WORD class_index;
			WORD name_and_type_index;
		}
		methodRef;

		struct
		{
			WORD name_index;
		}
		classData;

		struct
		{
			WORD name_index;
			WORD descriptor_index;
		}
		nameAndType;
	};
};

class CPool
{
public:
	std::vector<CPoolItem> m_items;

	WORD AddUtf8(BSTR bstr)
	{
		CPoolItem item;
		item.tag = CONSTANT_Utf8;
		item.bstr = SysAllocString(bstr);
		m_items.push_back(item);

		printf("%S\n", m_items[m_items.size()-1].bstr);

		return m_items.size();
	}

	WORD AddClass(WORD name_index)
	{
		CPoolItem item;
		item.tag = CONSTANT_Class;
		item.classData.name_index = name_index;
		m_items.push_back(item);
		return m_items.size();
	}

	WORD AddMethodref(WORD class_index, WORD name_and_type_index)
	{
		CPoolItem item;
		item.tag = CONSTANT_Methodref;
		item.methodRef.class_index = class_index;
		item.methodRef.name_and_type_index = name_and_type_index;
		m_items.push_back(item);
		return m_items.size();
	}

	WORD AddNameAndType(WORD name_index, WORD descriptor_index)
	{
		CPoolItem item;
		item.tag = CONSTANT_NameAndType;
		item.nameAndType.name_index = name_index;
		item.nameAndType.descriptor_index = descriptor_index;
		m_items.push_back(item);
		return m_items.size();
	}
};

void SaveClass(FILE* fp, CClass* pClass)
{
	fput32(fileout, JAVA_MAGIC);
	fput16(fileout, 0);	// minor_version
	fput16(fileout, 46);	// major_version

	CPool constant_pool;

	// Build constant pool

	WORD this_class = constant_pool.AddClass(constant_pool.AddUtf8(CComBSTR(pClass->m_name.c_str())));
	WORD super_class = constant_pool.AddClass(constant_pool.AddUtf8(CComBSTR(L"java/lang/Object")));
	WORD name_and_type_index = constant_pool.AddNameAndType(constant_pool.AddUtf8(CComBSTR(L"<init>")), constant_pool.AddUtf8(CComBSTR(L"()V")));
	WORD methodRef = constant_pool.AddMethodref(super_class, name_and_type_index);

	// Add class methods
	{
		for (int i = 0; i < pClass->m_methods.size(); i++)
		{
			CMethod* pMethod = pClass->m_methods[i];

			std::string descriptor;
			descriptor += "(";
			for (int p = 0; p < pMethod->m_parameters.size(); p++)
			{
				descriptor += pMethod->m_parameters[p]->m_typeString;
			}
			descriptor += ")";
			descriptor += pMethod->m_resultTypeString;

			pMethod->m_name_index = constant_pool.AddUtf8(CComBSTR(pMethod->m_name.c_str()));
			pMethod->m_descriptor_index = constant_pool.AddUtf8(CComBSTR(descriptor.c_str()));
		}
	}

	// Add some strings that I'll use later
	WORD Code_name_index = constant_pool.AddUtf8(L"Code");

	/*
	for (int i = 0; i < pClass->m_methods.size(); i++)
	{
		CMethod* pMethod = pClass->m_methods[i];

		pMethod->m_method_name_index = constant_pool.AddUtf8(CComBSTR(pMethod->m_name.c_str()));
		pMethod->m_name_and_type_index = constant_pool.AddNameAndType(method_name_index, 0);

		constant_pool.AddMethodref(class_index, mame_and_type_index);
	}
	*/

// The value of the constant_pool_count item is equal to the number of entries in the constant_pool table plus one
	WORD constant_pool_count = constant_pool.m_items.size() + 1;
	fput16(fileout, constant_pool_count);

	// Write constant pool to file
	{
		for (int i = 0; i < constant_pool.m_items.size(); i++)
		{
			CPoolItem& item = constant_pool.m_items[i];

			fput8(fileout, item.tag);

			switch (item.tag)
			{
			case CONSTANT_Utf8:
				{
					_bstr_t str = item.bstr;
					WORD length = str.length();
					fput16(fileout, length);
					fwrite((const char*)str, 1, str.length(), fileout);
				}
				break;

			case CONSTANT_Class:
				{
					fput16(fileout, item.classData.name_index);
				}
				break;

			case CONSTANT_Methodref:
				{
					fput16(fileout, item.methodRef.class_index);
					fput16(fileout, item.methodRef.name_and_type_index);
				}
				break;

			case CONSTANT_NameAndType:
				{
					fput16(fileout, item.nameAndType.name_index);
					fput16(fileout, item.nameAndType.descriptor_index);
				}
				break;

			default:
				ATLASSERT(0);
			}
		}
	}

	fput16(fp, pClass->m_access_flags);
	fput16(fp, this_class);
	fput16(fp, super_class);
	fput16(fp, pClass->m_interfaces_count);
	{
		for (int i = 0; i < pClass->m_interfaces_count; i++)
		{
			ATLASSERT(0);	// TODO
		}
	}

	// Write class fields
	{
		WORD fields_count = 0;
		fput16(fileout, fields_count);
	}

	// Write class methods
	{
		fput16(fileout, pClass->m_methods.size());

		for (int i = 0; i < pClass->m_methods.size(); i++)
		{
			CMethod* pMethod = pClass->m_methods[i];

			fput16(fileout, pMethod->m_access_flags);
			fput16(fileout, pMethod->m_name_index);
			fput16(fileout, pMethod->m_descriptor_index);

			WORD attributes_count = 1;
			fput16(fileout, attributes_count);

			// Write 'Code' attribute
			{
				WORD attribute_name_index = Code_name_index;
				fput16(fileout, attribute_name_index);

				DWORD attribute_length = 0;	// Unknown at this time
				fput32(fileout, attribute_length);

				long pos = ftell(fileout);
				emit_method(pMethod);

			// Write attribute length
				long pos2 = ftell(fileout);
				fseek(fileout, pos-4, SEEK_SET);
				fput32(fileout, pos2-pos);
				fseek(fileout, pos2, SEEK_SET);
			}
		}
	}

	// Write class attributes
	{
		WORD attributes_count = 0;
		fput16(fileout, attributes_count);
    	//attribute_info attributes[attributes_count];
	}
}

int compile_java(const char* filepath, const char* fileoutpath)
{
	fpin = fopen(filepath, "rb");
	if (fpin)
	{
		fileout = fopen(fileoutpath, "wb");
		if (fileout)
		{
			CClass* pClass = NULL;
			try
			{
				pClass = parse();
			}
			catch(int n)
			{
			}

			SaveClass(fileout, pClass);

			fclose(fileout);
		}
		else
		{
			printf("Error in creating output file %s", fileoutpath);
		}

		fclose(fpin);
	}
	return 0;
}
