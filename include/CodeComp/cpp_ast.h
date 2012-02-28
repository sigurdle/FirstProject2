#ifndef cpp_ast_h
#define cpp_ast_h

#ifndef CodeCompExt
#define CodeCompExt DECLSPEC_DLLIMPORT
#endif

// TODO
#define OutputError(filename, linenumber, msg)	DebugTrace(filename << "(" << linenumber << ")" << msg)

namespace System
{
namespace cpp
{
class CGlobal;
}

#if 0
#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	StringObject* filename;
} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	  (Current).filename  = YYRHSLOC (Rhs, N).filename;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	  (Current).filename = YYRHSLOC (Rhs, 0).filename;		\
	}								\
    while (0)
#endif

#if 0

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;	\
  Current.filename  = Rhs[N].filename;
#endif

#endif

typedef map<String, int> kwmap;

//#define sizeof_pointer	4

class T_Declarator;
class Temp_label;

namespace cpp
{

namespace ast
{
	/*
class LFCEXT FunctionParameters
{
public:
	CTOR FunctionParameters();

	Array<CDeclarator*, __gc_allocator> m_parameters;
	bool m_bVarArg;

	bool Equals(const FunctionParameters & other) const;

	StringA * ToString() const;
	void Write(System::StringBuilderA & stream) const;
};

class LFCEXT FunctionType : public _CVType // ??//Type
{
public:
	CTOR FunctionType();

	virtual Type_type GetKind() const
	{
		return type_function;
	}

	virtual StringA * ToString() const;
	virtual void Write(System::StringBuilderA & stream) const;
	virtual unsigned int get_sizeof() const;

	virtual uint8 GetSerializableType() const;
	virtual void Load(TypeArchive & stream);
	virtual void Store(TypeArchive & stream) const;

	bool Equals(const FunctionType & other) const;

	virtual Type * Clone() const;

	virtual bool IsConst() const;
	virtual bool IsVolatile() const;

	TemplateParams* m_pTemplateParams;

	Type * m_pReturnType;
	bool m_thiscall;
	int m_funcspec;
	unsigned int m_stackSize;

	FunctionParameters m_parameters;

// libcall
	class libcall
	{
	public:
		inline CTOR libcall()
		{
			m_basename = NULL;
			m_offset = 0;
		}
		StringA* m_basename;
		short m_offset;
		short m_tagcall;
	}
	m_libcall;
};
*/

class A_TypeIdList;
class A_TemplateArgumentList;

typedef System::ClassKey A_ClassKey;


#if 0
class CExpression
{
public:
	CExpression(/*Scope* pScope */)
	{
//		m_lvalue = true;
		left = NULL;
		right = NULL;
//		third = NULL;
#if 0
		m_pType = NULL;
#endif
		m_pDeclaratorRef = NULL;
	//	m_pMember = NULL;

		//m_pScope = pScope;

		m_pBaseDeclarator = NULL;	// libcall
	}

	CToken tok;

//	bool m_lvalue;
#if 0
	Type* m_pType;
#endif
	CDeclaratorReference* m_pDeclaratorRef;	// Used if tok ident

	CDeclaratorReference* m_pBaseDeclarator;	// libcall
//	int m_baseOffset;

//	CMember* m_pMember;

#if 0
	long m_spOffset;	// EBP offset
#endif

	struct
	{
		CExpression* left;
		CExpression* right;
	};

	union
	{
		struct
		{
			Type* m_pType;
		}
		cast;
	};

//	Scope* m_pScope;

	PP::CFileLocation m_location;

//	BOOL IsEqual(CExpression* pOther);
};
#endif

/*
class CTStatementList
{
public:
	CTExpression* m_head;
	CTExpression* m_tail;
};
*/

//class CDeclarator;

//class CCPPCompiler;

/*
class CStatement
{
public:
	virtual ~CStatement()
	{
	}

	enum
	{
		STMT_IF,
		STMT_WHILE,
		STMT_SWITCH,
		STMT_RETURN,
		STMT_BREAK,
		STMT_EXPRESSION,
		STMT_COMPOUND,
		STMT_ZERO,
		STMT_CASE,
		STMT_DEFAULT,
	}
	m_type;

	virtual void Evaluate(CCPPCompiler* pCompiler, CDeclarator* pFunctionDecl)
	{
	}

	PP::CFileLocation m_location;
};

struct CStatementList
{
	CStatementList(CStatement* _head, CStatementList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	CStatement* head;
	CStatementList* tail;
};

class CLabelStatement : public CStatement
{
public:
	CStatement* m_statement;
};

class CCaseStatement : public CLabelStatement
{
public:
	//CExpression* m_pExpr;
	int m_value;
};

class CZeroStatement : public CStatement
{
public:
	CZeroStatement()
	{
		m_type = STMT_ZERO;
		m_length = 0;
	}

	long m_spOffset;
	DWORD m_length;
};

class CFunctionBody
{
public:
	CFunctionBody()
	{
		m_pScope = NULL;
	}

	Scope* m_pScope;
	std::vector<CStatement*> m_statements;

	void Evaluate(CCPPCompiler* pCompiler, CDeclarator* pFunctionDecl);
};

class CCompoundStatement : public CStatement
{
public:
	CCompoundStatement()
	{
		m_type = STMT_COMPOUND;
		m_pBlock = NULL;
	}

	~CCompoundStatement()
	{
		if (m_pBlock)
		{
			delete m_pBlock;
			m_pBlock = NULL;
		}
	}

	CFunctionBody* m_pBlock;
};

class CReturnStatement : public CStatement
{
public:
	CReturnStatement()
	{
		m_type = STMT_RETURN;
		m_expr = NULL;
	}

	CExpression* m_expr;

	virtual void Evaluate(CCPPCompiler* pCompiler, CDeclarator* pFunctionDecl);
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

		m_pIfScope = NULL;
	}

	Scope* m_pIfScope;

	CExpression* m_testexpr;
	CCompoundStatement* m_substmt;
	CCompoundStatement* m_elsestmt;
};
*/

/*
class CCaseLabel
{
public:
	CExpression* m_pExpr;
};
*/

/*
class CSwitchStatement : public CStatement
{
public:
	CSwitchStatement()
	{
		m_type = STMT_SWITCH;
		m_testexpr = NULL;
		m_statement = NULL;

		m_pSwitchScope = NULL;
	}

//	std::vector<CCaseLabel*> m_cases;
//	CCaseLabel* m_default;

	Scope* m_pSwitchScope;

	CExpression* m_testexpr;
//	CCompoundStatement* m_statement;
	CStatement* m_statement;
};

class CWhileStatement : public CStatement
{
public:
	CWhileStatement()
	{
		m_type = STMT_WHILE;
		m_testexpr = NULL;
		m_substmt = NULL;
	}

	CExpression* m_testexpr;
	CStatement* m_substmt;
};

class CExpressionStatement : public CStatement
{
public:
	CExpressionStatement()
	{
		m_type = STMT_EXPRESSION;
		m_pExpr = NULL;
	}

	CExpression* m_pExpr;
};
*/

/*
class CodeCompExt CDeclaratorReferenceList
{
public:
	CDeclaratorReferenceList(System::CDeclaratorReference* _head, CDeclaratorReferenceList* _tail)
	{
		ASSERT(_head);

		head = _head;
		tail = _tail;
	}

	System::CDeclaratorReference* head;
	CDeclaratorReferenceList* tail;
};
*/

class A_DirectDeclarator;
class A_Declarator;
class A_DeclaratorList;
class InitDeclarator;
class InitDeclaratorList;
class Declaration;
class DeclarationList;
class A_StmList;
class A_TypeId;
class ExpressionList;
class A_SimpleDeclaration;
class Expression2List;
class DeclSpecList;

class Expression;
class A_ExpOrDecl;

/*
enum A_AccessSpec
{
	A_ACCESS_UNSPECIFIED,
	A_ACCESS_PRIVATE,
	A_ACCESS_PROTECTED,
	A_ACCESS_PUBLIC,
};
*/

enum BasicTypeSpecifier
{
	A_VOID,
	A_CHAR,
	A_WCHAR_T,
	A_BOOL,
	A_SHORT,
	A_INT,
	A___INT8,
	A___INT16,
	A___INT32,
	A___INT64,
	A_LONG,
	A_SIGNED,
	A_UNSIGNED,
	A_FLOAT,
	A_DOUBLE,
	A___FLOAT32,
	A___FLOAT64,
};

enum DeclSpecifierKeyword
{
	A_CONST = 16,
	A_VOLATILE,

	A_TYPEDEF,
	A_FRIEND,
	A_AUTO,
	A_REGISTER,
	A_EXTERN,
	A_STATIC,
	A_MUTABLE,
	A_DECLSPEC,	// TODO

	A_INLINE,
	A_VIRTUAL,
	A_EXPLICIT,
	A_CONSTEXPR,
};

class Expression2 : public Object
{
public:
	CTOR Expression2(const YYLTYPE& pos, int token) :
		m_linepos(pos.first_line),
		m_column(pos.first_column),
		m_filename(pos.filename)
	{
		m_token = token;

		m_primlist = NULL;
	}

	CTOR Expression2(const YYLTYPE& pos, int token, LONGLONG value) :
		m_linepos(pos.first_line),
		m_column(pos.first_column),
		m_filename(pos.filename)
	{
		m_token = token;

		m_primlist = NULL;
		u.m_int32 = value;
	}

	CTOR Expression2(const YYLTYPE& pos, int token, float value)
	{
		m_linepos = pos.first_line;
		m_column = pos.first_column;
		m_filename = pos.filename;

		m_token = token;

		m_primlist = NULL;
		u.m_float = value;
	}

	CTOR Expression2(const YYLTYPE& pos, int token, double value)
	{
		m_linepos = pos.first_line;
		m_filename = pos.filename;

		m_token = token;

		m_primlist = NULL;
		u.m_double = value;
	}

	CTOR Expression2(const YYLTYPE& pos, int token, System::StringA* value) :
		m_linepos(pos.first_line),
		m_column(pos.first_column),
		m_filename(pos.filename)
	{
		m_token = token;

		m_primlist = NULL;
		m_string = value;
		if (m_string) m_string->IncRef();
	}

	CTOR Expression2(const YYLTYPE& pos, int token, Expression2List* value)
	{
		m_linepos = pos.first_line;
		m_column = pos.first_column;
		m_filename = pos.filename;

		m_token = token;
		m_primlist = value;
	}

	CTOR Expression2(const YYLTYPE& pos, int token, System::Scope* value)
	{
		m_linepos = pos.first_line;
		m_column = pos.first_column;
		m_filename = pos.filename;

		m_token = token;

		m_primlist = NULL;
		m_pScope = value;
	}

	int m_token;

	union
	{
		LONGLONG m_int32;
		float m_float;
		double m_double;
	}
	u;

	StringA* m_string;
	Expression2List* m_primlist;
	//ExpressionList* m_explist;
	System::Scope* m_pScope;

	String m_filename;
	int m_linepos;
	int m_column;
};

class A_ExpOrDecl : public Object
{
public:
	CTOR A_ExpOrDecl(Expression* exp, ast::Declaration* decl)
	{
		m_exp = exp;
		m_decl = decl;
	}

	Expression* m_exp;
	ast::Declaration* m_decl;
};

class CodeCompExt Expression : public Object
{
public:

	CTOR Expression() : m_line_pos(-1)
	{
	}

	CTOR Expression(const YYLTYPE& pos) :
		m_filename(pos.filename),
		m_line_pos(pos.first_line)
	{
	}

	enum Kind
	{
		A_BINOP,
		A_UNOP,
		A_ID,
		A_BOOL,
		A_STRING,
		A_LSTRING,
		A_CHAR_LITERAL,
		A_NULLPTR,
		A_INT32,
		A_UINT32,
		A_INT64,
		A_UINT64,
		A_FLOAT,
		A_DOUBLE,
		A_CAST,
		A_STATIC_CAST,
		A_DYNAMIC_CAST,
		A_CONST_CAST,
		A_REINTERPRET_CAST,
		A_TYPEID,
		A_CALL,
		A_INIT,
		A_INITBASIC,
		A_THIS,
		A_POSTOP,
		A_THROW,

		A_TYPE,

		A_NEW,
		A_DELETE,

		A_SIZEOF,
		A_SIZEOF_TYPE,

		A_OPERATOR,
		A_CONVERSION,
		A_TEMPLATEID,
		A_INITCLAUSE
	};

	virtual Kind GetKind() const
	{
		return kind;
	}

	Kind kind;	// TODO remove
	String m_filename;
	int m_line_pos;

	struct // union
	{
		struct
		{
			System::StringA* id;
			A_TemplateArgumentList* params;
		}
		templateid;

		struct
		{
			int op;
			Expression* left;
			Expression* right;
		}
		binop;

		struct
		{
			int op;
			Expression* exp;
		}
		unop;

		ExpressionList* m_new_placement;

		union
		{
			bool boolValue;
			int _operator;
			int int32;
			int int32Val;
			uint32 uint32Val;
			LONGLONG int64Val;
			ULONGLONG uint64Val;
			float floatValue;
			double doubleValue;
		//	float float32;
		//	double float64;

			float float32Val;
			double float64Val;
		}
		u;
	};
};

class CodeCompExt NewExp : public Expression
{
public:
	CTOR NewExp(ExpressionList* placement, A_TypeId* typeId, ExpressionList* init);

	virtual Kind GetKind() const
	{
		return A_NEW;
	}

	A_TypeId* m_typeId;
	ExpressionList* m_args;
};

class CodeCompExt CallExp : public Expression
{
public:
	CTOR CallExp(const YYLTYPE& pos, Expression* left, ExpressionList* args) : Expression(pos),
		m_left(left),
		m_args(Reverse(args))
	{
		kind = A_CALL;
	}

	virtual Kind GetKind() const
	{
		return A_CALL;
	}

	Expression* m_left;
	ExpressionList* m_args;
};

class CodeCompExt TypeExp : public Expression
{
public:
	CTOR TypeExp(A_TypeId* typeId) :
		m_typeId(typeId)
	{
	}

	virtual Kind GetKind() const
	{
		return A_TYPE;
	}

	A_TypeId* m_typeId;
};

class CodeCompExt CastExpression : public Expression
{
public:
	A_TypeId* m_typeId;
	Expression* m_exp;
};

class CodeCompExt StaticCastExp : public CastExpression
{
public:
	CTOR StaticCastExp(A_TypeId* typeId, Expression* exp)
	{
		m_typeId = typeId;
		m_exp = exp;
	}

	virtual Kind GetKind() const
	{
		return A_STATIC_CAST;
	}
};

class CodeCompExt DynamicCastExp : public CastExpression
{
public:
	CTOR DynamicCastExp(A_TypeId* typeId, Expression* exp)
	{
		m_typeId = typeId;
		m_exp = exp;
	}

	virtual Kind GetKind() const
	{
		return A_DYNAMIC_CAST;
	}
};

class CodeCompExt ConstCastExp : public CastExpression
{
public:
	CTOR ConstCastExp(A_TypeId* typeId, Expression* exp)
	{
		m_typeId = typeId;
		m_exp = exp;
	}

	virtual Kind GetKind() const
	{
		return A_CONST_CAST;
	}
};

class CodeCompExt ReinterpretCastExp : public CastExpression
{
public:
	CTOR ReinterpretCastExp(A_TypeId* typeId, Expression* exp)
	{
		m_typeId = typeId;
		m_exp = exp;
	}

	virtual Kind GetKind() const
	{
		return A_REINTERPRET_CAST;
	}
};

class CodeCompExt TypeidExp : public Expression
{
public:
	CTOR TypeidExp(A_TypeId* typeId)
	{
		m_typeId = typeId;
		m_exp = NULL;
	}

	CTOR TypeidExp(Expression* exp)
	{
		m_exp = exp;
		m_typeId = NULL;
	}

	virtual Kind GetKind() const
	{
		return A_TYPEID;
	}

	A_TypeId* m_typeId;
	Expression* m_exp;
};

class CodeCompExt SizeofTypeExp : public Expression
{
public:
	CTOR SizeofTypeExp(A_TypeId* pTypeId)
	{
		kind = Expression::A_SIZEOF_TYPE;
		m_typeId = pTypeId;
	}

	A_TypeId* m_typeId;
};

class CodeCompExt SizeofExp : public Expression
{
public:
	CTOR SizeofExp(Expression* exp)
	{
		kind = A_SIZEOF;
		m_exp = exp;
	}

	virtual Kind GetKind() const
	{
		return A_SIZEOF;
	}

	Expression* m_exp;
};

class CodeCompExt ConversionExp : public Expression
{
public:
	CTOR ConversionExp(A_TypeId* typeId)
	{
		kind = A_CONVERSION;
	//	p->line_pos = pos.first_line;
		m_typeId = typeId;
	}

	virtual Kind GetKind() const
	{
		return A_CONVERSION;
	}

	A_TypeId* m_typeId;
};

class CodeCompExt ThrowExp : public Expression
{
public:

	CTOR ThrowExp(Expression* exp)
	{
		m_exp = exp;
	}

	virtual Kind GetKind() const
	{
		return A_THROW;
	}

	Expression* m_exp;
};

class CodeCompExt InitExp : public Expression
{
public:

	CTOR InitExp(const YYLTYPE& pos, Expression* f, ExpressionList* args) : Expression(pos)
	{
	#if 0	// TODO, have this
		ASSERT(f);
	#endif

		kind = A_INIT;

		m_left = f;
		m_args = Reverse(args);
	}

	virtual Kind GetKind() const
	{
		return A_INIT;
	}

	Expression* m_left;
	ExpressionList* m_args;
};

class CodeCompExt InitBasicExp : public Expression
{
public:
	CTOR InitBasicExp(const YYLTYPE& pos, BasicTypeSpecifier type, ExpressionList* args) : Expression(pos)
	{
	#if 0	// TODO, have this
		ASSERT(f);
	#endif

		kind = Expression::A_INITBASIC;

		m_type = type;
		m_args = Reverse(args);
	}

	virtual Kind GetKind() const
	{
		return A_INITBASIC;
	}

	BasicTypeSpecifier m_type;
	ExpressionList* m_args;
};

class CodeCompExt CharLiteralExp : public Expression
{
public:
	CTOR CharLiteralExp(uint32 value)
	{
		u.int32 = value;
	}

	virtual Kind GetKind() const override
	{
		return A_CHAR_LITERAL;
	}
};

class CodeCompExt NullLiteralExp : public Expression
{
public:
	virtual Kind GetKind() const override
	{
		return A_NULLPTR;
	}
};

class CodeCompExt DeleteExp : public Expression
{
public:
	CTOR DeleteExp(Expression* exp)
	{
		unop.exp = exp;
	}

	virtual Kind GetKind() const override
	{
		return A_DELETE;
	}
};

class CodeCompExt InitClauseExp : public Expression
{
public:
	CTOR InitClauseExp(ExpressionList* expList) : m_args(expList)
	{
	}

	virtual Kind GetKind() const override
	{
		return A_INITCLAUSE;
	}

	ExpressionList* m_args;
};

class CodeCompExt ExpressionList : public System::Object
{
public:

	CTOR ExpressionList(Expression* _head, ExpressionList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	Expression* head;
	ExpressionList* tail;
};

class CodeCompExt Expression2List : public Object
{
public:

	CTOR Expression2List(Expression2* _head, Expression2List* _tail) : head(_head), tail(_tail)
	{
	}

	Expression2* head;
	Expression2List* tail;
};

class CodeCompExt Condition : public Object
{
public:
	CTOR Condition(DeclSpecList* declspecList, A_Declarator* declarator, Expression* exp) :
		m_declspecList(declspecList),
		m_declarator(declarator),
		m_exp(exp)
	{
	}

	CTOR Condition(Expression* exp) :
		m_declspecList(NULL),
		m_declarator(NULL),
		m_exp(exp)
	{
	}

	DeclSpecList* m_declspecList;
	A_Declarator* m_declarator;
	Expression* m_exp;
};

class CodeCompExt A_Stm : public Object
{
public:

	enum Kind
	{
		A_IF,
		A_SWITCH,
		A_WHILE,
		A_DOWHILE,
		A_FOR,
		A_RETURN,
		A_GOTO,
		A_CONTINUE,
		A_BREAK,
		A_EXP,
		A_DECLARATION,
		A_COMPOUND,
		A_PRIMLIST,
		A_LABEL,
		A_DEFAULT,
		A_CASE,
	};

	virtual Kind GetKind() const = 0;

	CTOR A_Stm()
	{
		m_last_line = -1;
	}

	int m_last_line;

//	int m_line;
};

/*
class CodeCompExt A_IfStm_Pass1 : public A_Stm
{
public:

	A_IfStm_Pass1(Expression2List* cond, A_Stm* stm, A_Stm* elseStm);

	virtual Kind GetKind() const
	{
		return A_IF;
	}

	Expression2List* m_cond;
	A_Stm* m_stm;
	A_Stm* m_elseStm;
};
*/

class CodeCompExt IfStm : public A_Stm
{
public:

	CTOR IfStm(Expression2List* cond, A_Stm* stm, A_Stm* elseStm);
	CTOR IfStm(Condition* cond, A_Stm* stm, A_Stm* elseStm);

	virtual Kind GetKind() const
	{
		return A_IF;
	}

	Object* m_cond;
	/*
	union
	{
	ExpressionOrDecl* m_cond;
	Expression2List* m_cond;
	}
	*/

	A_Stm* m_stm;
	A_Stm* m_elseStm;
};

/*
class CodeCompExt A_SwitchStm_Pass1 : public A_Stm
{
public:

	A_SwitchStm_Pass1(Expression2List* cond, A_Stm* stm);

	virtual Kind GetKind() const
	{
		return A_SWITCH;
	}

	Expression2List* m_cond;
	A_Stm* m_stm;
};
*/

class CodeCompExt SwitchStm : public A_Stm
{
public:

	CTOR SwitchStm(Expression2List* cond, A_Stm* stm);
	CTOR SwitchStm(Condition* cond, A_Stm* stm);

	virtual Kind GetKind() const
	{
		return A_SWITCH;
	}

	Object* m_cond;
	A_Stm* m_stm;
};

/*
class CodeCompExt A_CaseStm_Pass1 : public A_Stm
{
public:


	virtual Kind GetKind() const
	{
		return A_CASE;
	}

	Expression2List* m_exp;
	A_Stm* m_stm;
};
*/

class CodeCompExt CaseStm : public A_Stm
{
public:

	CTOR CaseStm(Expression2List* exp, A_Stm* stm);
	CTOR CaseStm(Expression* exp, A_Stm* stm);

	virtual Kind GetKind() const
	{
		return A_CASE;
	}

	Object* m_exp;
/*
	union
	{
	Expression2List* m_exp;
	Expression* m_exp;
	}
*/
	A_Stm* m_stm;
};

class CodeCompExt DefaultStm : public A_Stm
{
public:

	CTOR DefaultStm(A_Stm* stm);

	virtual Kind GetKind() const
	{
		return A_DEFAULT;
	}

	A_Stm* m_stm;
};

/*
class CodeCompExt A_WhileStm_Pass1 : public A_Stm
{
public:


	virtual Kind GetKind() const
	{
		return A_WHILE;
	}

	Expression2List* m_cond;
	A_Stm* m_stm;
};
*/

class CodeCompExt WhileStm : public A_Stm
{
public:

	CTOR WhileStm(Expression2List* cond, A_Stm* stm);
	CTOR WhileStm(const YYLTYPE& first_pos, const YYLTYPE& last_pos, Condition* cond, A_Stm* stm);

	virtual Kind GetKind() const
	{
		return A_WHILE;
	}

	Object* m_cond;
	A_Stm* m_stm;

//	int m_last_line;
};

/*
class CodeCompExt A_DoWhileStm_Pass1 : public A_Stm
{
public:


	virtual Kind GetKind() const
	{
		return A_DOWHILE;
	}

	A_Stm* m_stm;
	Expression2List* m_exp;
};
*/

class CodeCompExt DoWhileStm : public A_Stm
{
public:

	CTOR DoWhileStm(A_Stm* stm, Expression2List* exp);
	CTOR DoWhileStm(A_Stm* stm, Expression* exp);

	virtual Kind GetKind() const
	{
		return A_DOWHILE;
	}

	A_Stm* m_stm;
	Object* m_exp;
	/*
	union
	{
		Expression* m_exp;
		Expression2List* m_exp;
	}
	*/
};

/*
class CodeCompExt A_ForStm_Pass1 : public A_Stm
{
public:


	virtual Kind GetKind() const
	{
		return A_FOR;
	}

	Expression2List* m_init;
	Expression2List* m_cond;
	Expression2List* m_exp;
	A_Stm* m_stm;
};
*/

class CodeCompExt ForStm : public A_Stm
{
public:

	CTOR ForStm(Expression2List* init, Expression2List* cond, Expression2List* exp, A_Stm* stm)
	{
		m_init = init;
		m_cond = cond;
		m_exp = exp;
		m_stm = stm;

		m_line_pos = -1;
	}

	CTOR ForStm(A_ExpOrDecl* init, Expression* cond, Expression* exp, A_Stm* stm)
	{
		m_init = init;
		m_cond = cond;
		m_exp = exp;
		m_stm = stm;

		m_line_pos = -1;
	}

	virtual Kind GetKind() const
	{
		return A_FOR;
	}

	Object* m_init;
	Object* m_cond;
	Object* m_exp;
	A_Stm* m_stm;

	int m_line_pos;
};

class CodeCompExt LabelStm : public A_Stm
{
public:
	CTOR LabelStm(String name, A_Stm* stm)
	{
		m_name = name;
		m_stm = stm;
	}

	virtual Kind GetKind() const
	{
		return A_LABEL;
	}

	String m_name;
	A_Stm* m_stm;
};

class CodeCompExt GotoStm : public A_Stm
{
public:
	CTOR GotoStm(String name)
	{
		m_name = name;
	}

	virtual Kind GetKind() const
	{
		return A_GOTO;
	}

	String m_name;
};

class CodeCompExt ReturnStm : public A_Stm
{
public:

	CTOR ReturnStm();
	CTOR ReturnStm(Expression2List* exp);
	CTOR ReturnStm(Expression* exp);

	virtual Kind GetKind() const
	{
		return A_RETURN;
	}

	Object* m_exp;
	/*
	union
	{
		Expression2List* m_exp;
		Expression* m_exp;
	}
	*/
};

/*
class CodeCompExt A_ReturnStm : public A_Stm
{
public:

	A_ReturnStm(Expression* exp);

	virtual Kind GetKind() const
	{
		return A_RETURN;
	}

};
*/

class CodeCompExt ContinueStm : public A_Stm
{
public:

	CTOR ContinueStm()
	{
	}

	virtual Kind GetKind() const
	{
		return A_CONTINUE;
	}
};

class CodeCompExt BreakStm : public A_Stm
{
public:

	CTOR BreakStm()
	{
	}

	virtual Kind GetKind() const
	{
		return A_BREAK;
	}
};

class CodeCompExt A_DeclarationStm : public A_Stm
{
public:

	CTOR A_DeclarationStm(ast::Declaration* declaration);

	virtual Kind GetKind() const
	{
		return A_DECLARATION;
	}

	Declaration* m_declaration;
};

class CodeCompExt A_ExpStm : public A_Stm
{
public:

	CTOR A_ExpStm(Expression* exp);

	virtual Kind GetKind() const
	{
		return A_EXP;
	}

	Expression* m_exp;
};

class CodeCompExt CompoundStm : public A_Stm
{
public:

	CTOR CompoundStm(const YYLTYPE& first_pos, const YYLTYPE& last_pos, A_StmList* stmList);

	virtual Kind GetKind() const
	{
		return A_COMPOUND;
	}

	String first_filename;
	String last_filename;
	int m_first_line;

	A_StmList* m_stmList;
};

/*
class CodeCompExt ExpressionOrDeclStm : public A_Stm
{
public:

	ExpressionOrDeclStm(Expression* exp, A_Declaration* declaration);

	virtual Kind GetKind() const
	{
		return Expression_OR_DECLARATION;
	}

	Expression* m_exp;
	A_Declaration* m_declaration;
};
*/

class CodeCompExt A_PrimListStm : public A_Stm
{
public:

	CTOR A_PrimListStm(Expression2List* primlist)
	{
		m_primlist = primlist;
	}

	virtual Kind GetKind() const
	{
		return A_PRIMLIST;
	}

	Expression2List* m_primlist;
};

class CodeCompExt A_StmList : public Object
{
public:

	CTOR A_StmList(A_Stm* stm, A_StmList* stmList)
	{
		head = stm;
		tail = stmList;
	}

	A_Stm* head;
	A_StmList* tail;
};

class CodeCompExt A_MemberSpec : public Object
{
public:

	CTOR A_MemberSpec()
	{
	}

	CTOR A_MemberSpec(A_MemberSpec* next) : m_next(next)
	{
	}

	enum Kind
	{
		A_MEMBER_DECL,
		A_ACCESS_SPEC,
	};

	virtual Kind GetKind() = 0;

	A_MemberSpec* m_next;
};

class CodeCompExt A_MemberDecl : public A_MemberSpec
{
public:
	CTOR A_MemberDecl(Declaration* declaration, A_MemberSpec* next);

	virtual Kind GetKind()
	{
		return A_MEMBER_DECL;
	}

	Declaration* m_declaration;
};

class CodeCompExt A_MemberAccessSpec : public A_MemberSpec
{
public:
	CTOR A_MemberAccessSpec(AccessSpec accessSpec, A_MemberSpec* next);

	virtual Kind GetKind()
	{
		return A_ACCESS_SPEC;
	}

	AccessSpec m_accessSpec;
};

class CodeCompExt EnumDefinition : public Object
{
public:

	CTOR EnumDefinition(const YYLTYPE& first_pos, String name, Expression* exp);

	String m_name;
	Expression* m_exp;

	String m_filename;
	int m_line;
	int m_column;
};

class CodeCompExt EnumDefList : public Object
{
public:
	CTOR EnumDefList(EnumDefinition* _head, EnumDefList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	EnumDefinition* head;
	EnumDefList* tail;
};

/*
class CodeCompExt A_DeclSpec
{
//	Type_type kind;
//	A_Type* pointerTo;
//	bool bConst;
//	bool bVolatile;
	enum
	{
	}
	kind;

	union
	{
	};
};
*/

class CodeCompExt A_BaseSpecifier : public Object
{
public:
	CTOR A_BaseSpecifier(Expression* id, AccessSpec accessSpec, uint8 virtualpos)
	{
		m_id = id;
		m_accessSpec = accessSpec;
		m_virtualpos = virtualpos;
	}

	Expression* m_id;
	AccessSpec m_accessSpec;
	uint8 m_virtualpos;
};

class CodeCompExt A_BaseSpecifierList : public Object
{
public:
	CTOR A_BaseSpecifierList(A_BaseSpecifier * _head, A_BaseSpecifierList* _tail)
	{
		ASSERT(_head);

		head = _head;
		tail = _tail;
	}

	A_BaseSpecifier* head;
	A_BaseSpecifierList* tail;
};

class CodeCompExt A_ClassHead : public Object
{
public:
	CTOR A_ClassHead(const YYLTYPE& pos, A_ClassKey classKey, DeclSpecList* declspecList, Expression* name) :

		m_filename(pos.filename),
		m_line_pos(pos.first_line),
		m_column(pos.first_column),

		m_classKey(classKey),
		m_declspecList(declspecList),
		m_name(name)
	{
	}

	A_ClassKey m_classKey;
	DeclSpecList* m_declspecList;
	Expression* m_name;

	String m_filename;
	int m_line_pos;
	int m_column;
};

class CodeCompExt A_DeclSpec : public Object
{
public:
	CTOR A_DeclSpec(const YYLTYPE& pos) :
		m_filename(pos.filename),
		m_line_pos(pos.first_line),
		m_column(pos.first_column)
	{
//		ASSERT(pos.filename);
	}

	enum Kind
	{
		A_TYPE_NAME,
		A_TYPE_ENUM,
		A_TYPE_CLASS,
		A_TYPE_CLASSDEF,
		A_TYPE_MODIFIER,
		A_TYPE_DECLSPECEXT,
		A_TYPE_BASIC,
		A_DECLTYPE,
	};

	virtual Kind GetKind() const = 0;

	String m_filename;
	int m_line_pos;
	int m_column;
};

class CodeCompExt A_NameType : public A_DeclSpec
{
public:
	CTOR A_NameType(const YYLTYPE& pos, Expression* name);

	virtual Kind GetKind() const override
	{
		return A_TYPE_NAME;
	}

	Expression* m_name;
};

class CodeCompExt A_Enum : public A_DeclSpec
{
public:
	CTOR A_Enum(const YYLTYPE& pos, String name, DeclSpecList* baseType, EnumDefList* deflist);

	virtual Kind GetKind() const override
	{
		return A_TYPE_ENUM;
	}

	String m_name;
	DeclSpecList* m_baseType;
	EnumDefList* m_deflist;
};

class CodeCompExt A_Class : public A_DeclSpec
{
public:
	CTOR A_Class(const YYLTYPE& pos, A_ClassHead* head/*A_ClassKey classKey, Expression * name*/);

	virtual Kind GetKind() const override
	{
		return A_TYPE_CLASS;
	}

	A_ClassHead* m_head;
};

class CodeCompExt A_ClassDef : public A_DeclSpec
{
public:
	CTOR A_ClassDef(const YYLTYPE& pos, A_ClassHead* head, A_BaseSpecifierList* baseList, A_MemberSpec* memberSpec);

	virtual Kind GetKind() const override
	{
		return A_TYPE_CLASSDEF;
	}

	A_ClassHead* m_head;
	A_BaseSpecifierList* m_baseList;
	A_MemberSpec* m_memberSpec;
};

class CodeCompExt A_DeclSpecModifier : public A_DeclSpec
{
public:
	CTOR A_DeclSpecModifier(const YYLTYPE& pos, DeclSpecifierKeyword modifier);

	virtual Kind GetKind() const override
	{
		return A_TYPE_MODIFIER;
	}

	DeclSpecifierKeyword m_modifier;
};

class CodeCompExt A_DeclSpecExt : public Object
{
public:
	CTOR A_DeclSpecExt(StringIn id)
	{
		m_id = id;
	}

	CTOR A_DeclSpecExt(StringIn id, int arg)
	{
		m_id = id;
		m_arg = arg;
	}

	String m_id;
	int m_arg;
};

class CodeCompExt A_DeclSpecExtList : public System::Object
{
public:

	CTOR A_DeclSpecExtList(A_DeclSpecExt* _head, A_DeclSpecExtList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_DeclSpecExt* head;
	A_DeclSpecExtList* tail;
};

class CodeCompExt A_DeclSpecExtModifier : public A_DeclSpec
{
public:
	CTOR A_DeclSpecExtModifier(const YYLTYPE& pos, A_DeclSpecExtList* extlist) : A_DeclSpec(pos)
	{
		m_extlist = extlist;
	}

	virtual Kind GetKind() const override
	{
		return A_TYPE_DECLSPECEXT;
	}

	A_DeclSpecExtList* m_extlist;
};

class CodeCompExt A_DeclSpecBasicType : public A_DeclSpec
{
public:
	CTOR A_DeclSpecBasicType(const YYLTYPE& pos, BasicTypeSpecifier type);

	virtual Kind GetKind() const override
	{
		return A_TYPE_BASIC;
	}

	BasicTypeSpecifier m_basicType;
};

class CodeCompExt DeclType : public A_DeclSpec
{
public:
	CTOR DeclType(const YYLTYPE& pos, Expression* exp) : A_DeclSpec(pos), m_exp(exp)
	{
	}

	virtual Kind GetKind() const override
	{
		return A_DECLTYPE;
	}

	Expression* m_exp;
};

class CodeCompExt DeclSpecList : public Object
{
public:

	CTOR DeclSpecList(A_DeclSpec* _head, DeclSpecList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_DeclSpec* head;
	DeclSpecList* tail;
};

//CodeCompExt DeclSpecList* merge(DeclSpecList* a, DeclSpecList* b);

/*
struct DeclSpecList
{
	DeclSpecList(A_Type* _head, DeclSpecList* _tail)
	{
		ASSERT(_head);

		head = _head;
		tail = _tail;
	}

	A_Type* head;
	DeclSpecList* tail;
};
*/

class TemplateParameterList;

class CodeCompExt Declaration : public Object
{
public:
	/*
	CTOR Declaration()
	{
	}
	*/

	CTOR Declaration(const YYLTYPE& pos) :
		m_filename(pos.filename),
		m_line_pos(pos.first_line),
		m_column(pos.first_column)
	{
	}

	enum Kind
	{
		A_EXTERN_LINKAGE,
		A_NAMESPACE,
		A_FUNDEF,
		A_SIMPLE,
		A_TEMPLATE,
		A_DECLARATION2,	// ??
		A_USING_DIRECTIVE,
		A_ASM,
		A_PRAGMA,
		A_IMPORT,
		A_STATIC_ASSERT
	};

	virtual Kind GetKind() const = 0;

	ExpressionList* m_attributes;

	String m_filename;
	int m_line_pos;
	int m_column;
};

class CodeCompExt ImportDeclaration : public Declaration
{
public:

	CTOR ImportDeclaration(const YYLTYPE& pos, StringIn str) : Declaration(pos), m_str(str)
	{
	}

	virtual Kind GetKind() const override
	{
		return A_IMPORT;
	}

	String m_str;
};

class CodeCompExt PragmaDeclaration : public Declaration
{
public:
	CTOR PragmaDeclaration(const YYLTYPE& pos, StringIn str) : Declaration(pos), m_str(str)
	{
	}

	Kind GetKind() const override
	{
		return A_PRAGMA;
	}

	String m_str;
};

class CodeCompExt StaticAssertDeclaration : public Declaration
{
public:
	CTOR StaticAssertDeclaration(const YYLTYPE& pos, Expression* exp, StringIn message) : Declaration(pos),
		m_exp(exp),
		m_message(message)
	{
	}

	Kind GetKind() const override
	{
		return A_STATIC_ASSERT;
	}

	Expression* m_exp;
	String m_message;
};

class CodeCompExt AsmDefinition : public Declaration
{
public:
	CTOR AsmDefinition(const YYLTYPE& pos, StringIn str) : Declaration(pos), m_str(str)
	{
	}

	Kind GetKind() const override
	{
		return A_ASM;
	}

	String m_str;
};

class CodeCompExt UsingDirectiveDeclaration : public Declaration
{
public:
	CTOR UsingDirectiveDeclaration(const YYLTYPE& pos, Expression* name);

	Kind GetKind() const override
	{
		return A_USING_DIRECTIVE;
	}

	Expression* m_name;
};

class CodeCompExt LinkageDeclaration : public Declaration
{
public:
	CTOR LinkageDeclaration(const YYLTYPE& pos, StringIn linkage, DeclarationList* declarationList);

	Kind GetKind() const override
	{
		return A_EXTERN_LINKAGE;
	}

	String m_linkage;
	DeclarationList* m_declarationList;
};

class CodeCompExt NamespaceDefinition : public Declaration
{
public:
	CTOR NamespaceDefinition(const YYLTYPE& pos, StringIn name, DeclarationList* declarationList);

	Kind GetKind() const override
	{
		return A_NAMESPACE;
	}

	String m_name;
	DeclarationList* m_declarationList;
};

class CodeCompExt FunDefDecl : public Declaration
{
public:
	CTOR FunDefDecl(const YYLTYPE& pos, DeclSpecList* declspec, A_Declarator* declarator, ExpressionList* ctor_initializer, CompoundStm* stm);

	Kind GetKind() const override
	{
		return A_FUNDEF;
	}

	DeclSpecList* m_declspec;
	A_Declarator* m_declarator;
	ExpressionList* m_ctor_initializer;
	CompoundStm* m_body;
};

class CodeCompExt A_SimpleDeclaration : public Declaration
{
public:
	CTOR A_SimpleDeclaration(const YYLTYPE& pos, DeclSpecList* declspec, InitDeclaratorList* declaratorList);

	Kind GetKind() const override
	{
		return A_SIMPLE;
	}

	DeclSpecList* m_declspec;
	InitDeclaratorList* m_declaratorList;
};

class CodeCompExt TemplateDeclaration : public Declaration
{
public:
	CTOR TemplateDeclaration(const YYLTYPE& pos, TemplateParameterList* params, Declaration * decl);

	Kind GetKind() const override
	{
		return A_TEMPLATE;
	}

	TemplateParameterList* m_params;
	Declaration* m_decl;
};

class CodeCompExt TemplateParameter : public Object
{
public:

	enum Kind
	{
		A_ParamType,
		A_ParamDeclarator,
	};

	virtual Kind GetKind() const = 0;

	/*
	A_TemplateParameter(System::StringA* id, A_TypeId * typeId)
	{
		m_id = id;
		m_typeId = typeId;
	}
	System::StringA* m_id;
	A_TypeId* m_typeId;
	*/
};

class CodeCompExt TypeTemplateParameter : public TemplateParameter
{
public:
	CTOR TypeTemplateParameter(StringA* id, A_TypeId* typeId)
	{
		m_id = id;
		m_typeId = typeId;
	}

	virtual Kind GetKind() const override
	{
		return A_ParamType;
	}

	String m_id;
	A_TypeId* m_typeId;
};

class CodeCompExt DeclaratorTemplateParameter : public TemplateParameter
{
public:
	CTOR DeclaratorTemplateParameter(DeclSpecList* decls, A_Declarator* declarator)
	{
		m_decls = decls;
		m_declarator = declarator;
	}

	virtual Kind GetKind() const override
	{
		return A_ParamDeclarator;
	}

	DeclSpecList* m_decls;
	A_Declarator* m_declarator;
	Expression* m_defaultValue;
};

class CodeCompExt TemplateParameterList : public Object
{
public:

	CTOR TemplateParameterList(TemplateParameter* _head, TemplateParameterList * _tail)
	{
		head = _head;
		tail = _tail;
	}

	TemplateParameter * head;
	TemplateParameterList * tail;
};

class CodeCompExt A_TypeId : public Object
{
public:

	CTOR A_TypeId(DeclSpecList* _declspecList, A_Declarator* _declarator, Expression* def = NULL)
	{
	//	ASSERT(_declspecList != NULL || _declarator != NULL);

		m_declspecList = _declspecList;
		m_declarator = _declarator;
		m_def = def;
	}

	DeclSpecList* m_declspecList;
	A_Declarator* m_declarator;
	Expression* m_def;
};

class CodeCompExt A_TypeIdList : public Object
{
public:

	CTOR A_TypeIdList(A_TypeId* _head, A_TypeIdList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_TypeId* head;
	A_TypeIdList* tail;
};

class CodeCompExt A_TemplateArgument : public Object
{
public:
	CTOR A_TemplateArgument(A_TypeId* pTypeId, Expression* pExp)
	{
		/*
		if (pExp && pExp->GetKind() == Expression::A_BINOP)
		{
			if (!strcmp(pExp->binop.left->templateid.id->c_str(), "Text"))
			{
				MessageBeep(-1);
			}
		}
		*/

		ASSERT(pTypeId || pExp);

	//	ASSERT(typeid(*pTypeId) != typeid(DeclSpecList));
		m_pTypeId = pTypeId;
		m_pExp = pExp;
	}

	A_TypeId* m_pTypeId;
	Expression* m_pExp;
};

class CodeCompExt A_TemplateArgumentList : public Object
{
public:

	CTOR A_TemplateArgumentList(A_TemplateArgument* _head, A_TemplateArgumentList* _tail)
	{
		ASSERT(_head);

		head = _head;
		tail = _tail;
	}

	A_TemplateArgument * head;
	A_TemplateArgumentList* tail;
};

class CodeCompExt ParameterDeclarations : public Object
{
public:

	CTOR ParameterDeclarations(A_TypeIdList* _params, bool _varArgs)
	{
		params = Reverse(_params);
		varArgs = _varArgs;
	}

	A_TypeIdList* params;
	bool varArgs;
};

class CodeCompExt A_Declarator : public Object
{
public:

	/*
	enum
	{
		A_DIRECT_DECLARATOR,
		A_PTR
	}
	kind;
	*/

	CTOR A_Declarator(const YYLTYPE& pos) :
		m_filename(pos.filename),
		m_line_pos(pos.first_line),
		m_column_pos(pos.first_column)
	{
	}

	/*
	union
	{
		struct
		{
			int type;
			A_Declarator* declarator;
		}
		ptr;
		A_DirectDeclarator* directDeclarator;
	};
	*/

	System::Scope* Extract(System::Declarator* pDeclarator, System::Type* pType, System::Scope* pScope, System::Scope* pTScope, CGlobal* pGlobal);

	String m_filename;
	int m_line_pos;
	int m_column_pos;
};

class Initializer : public Object
{
public:
	CTOR Initializer(Expression* exp)
	{
		m_exp = exp;
		m_expList = NULL;
	}

	CTOR Initializer(ExpressionList* expList)
	{
		m_exp = NULL;
		m_expList = expList;
	}

	Expression* m_exp;
	ExpressionList* m_expList;
};

class InitDeclarator : public Object
{
public:
	CTOR InitDeclarator(A_Declarator* declarator, Initializer* initializer = NULL)
	{
		m_declarator = declarator;
		m_initializer = initializer;
	}

	A_Declarator* m_declarator;
	Initializer* m_initializer;
};

class A_BitfieldDeclarator : public A_Declarator
{
public:
	CTOR A_BitfieldDeclarator(const YYLTYPE& pos, Expression* id, Expression* exp) : A_Declarator(pos)
	{
		m_id = id;
		m_exp = exp;
	}

	Expression* m_id;
	Expression* m_exp;
};

class A_DirectDeclaratorDeclarator : public A_Declarator
{
public:
	CTOR A_DirectDeclaratorDeclarator(const YYLTYPE& pos, A_DirectDeclarator* directDeclarator) : A_Declarator(pos)
	{
	//	m_filename = pos.filename;
	//	m_line_pos = pos.first_line;

		//->kind = A_Declarator::A_DIRECT_DECLARATOR;
		m_directDeclarator = directDeclarator;
	}

	A_DirectDeclarator* m_directDeclarator;
};

class A_PtrDeclarator : public A_Declarator
{
public:

	CTOR A_PtrDeclarator(const YYLTYPE& pos, int type, A_Declarator* declarator, Expression* id = NULL) : A_Declarator(pos)
	{
		ASSERT(type);
		m_type = type;
		m_declarator = declarator;
		m_id = id;
	}

	Expression* m_id;
	int m_type;
	A_Declarator* m_declarator;
};

#ifndef __LERSTAD__

class CodeCompExt A_DirectDeclarator : public Object
{
public:

	enum Kind
	{
		A_DIRECT_DECLARATOR,
		A_DECLARATOR_ID,
		A_DECLARATOR,
	};

	Kind kind;

	String m_filename;
	int line_pos;
	int m_column_pos;

	struct _u	// union
	{
		struct _directDeclarator
		{
			enum
			{
				A_PAREN,
				A_ARRAY,
			}
			kind;

			struct	// union
			{
				struct
				{
					ParameterDeclarations* paramDecls;
					DeclSpecList* decls;
				};
				/*
				struct
				{
				}
				paren;
				*/
				Expression* array;
			};

			A_DirectDeclarator* directDeclarator;
		}
		directDeclarator;

		A_Declarator* declarator;

		Expression* declaratorId;
	}
	u;
};

#endif

class CodeCompExt DeclarationList : public Object
{
public:

	CTOR DeclarationList(Declaration* declaration, DeclarationList* declarationList)
	{
		//ASSERT(declaration);

		head = declaration;
		tail = declarationList;
	}

	Declaration* head;
	DeclarationList* tail;
};

class CodeCompExt A_DeclaratorList : public Object
{
public:

	CTOR A_DeclaratorList(A_Declarator* declarator, A_DeclaratorList* declaratorList)
	{
	//	ASSERT(declarator); TODO, have this

		head = declarator;
		tail = declaratorList;
	}

	A_Declarator* head;
	A_DeclaratorList* tail;
};

class CodeCompExt InitDeclaratorList : public Object
{
public:

	CTOR InitDeclaratorList(InitDeclarator* declarator, InitDeclaratorList* declaratorList)
	{
	//	ASSERT(declarator); TODO, have this

		head = declarator;
		tail = declaratorList;
	}

	InitDeclarator* head;
	InitDeclaratorList* tail;
};

CodeCompExt Expression* A_ThisExp();
CodeCompExt Expression* A_BinopExp(const YYLTYPE& pos, int op, Expression* e1, Expression* e2);
CodeCompExt Expression* A_UnopExp(const YYLTYPE& pos, int op, Expression* e);
CodeCompExt Expression* A_PostopExp(const YYLTYPE& pos, Expression* e, int op);
CodeCompExt Expression* A_IdExp(StringIn id);
CodeCompExt Expression* A_IdExp(const YYLTYPE& pos, StringIn* id);
CodeCompExt Expression* A_StringExp(StringA* string);
CodeCompExt Expression* A_LStringExp(StringA* string);
CodeCompExt Expression* A_Int32Exp(int32 num);
CodeCompExt Expression* A_Int64Exp(int64 num);
CodeCompExt Expression* A_DoubleExp(double value);
CodeCompExt Expression* A_BoolExp(bool boolValue);
CodeCompExt Expression* A_CastExp(A_TypeId* typeId, Expression* exp);

CodeCompExt Expression* A_OperatorExp(const YYLTYPE& pos, int op);

//A_DeclaratorList* A_DeclaratorList(A_Declarator* declarator, A_DeclaratorList* declaratorList);

CodeCompExt ast::Declaration* A_Declaration2(ast::Declaration* d1, ast::Declaration* d2);
//CodeCompExt A_Declaration* A_ElaborateDeclaration(A_Declaration* d1, A_Declaration* d2);

CodeCompExt A_DirectDeclarator* A_DeclaratorDirectDeclarator(const YYLTYPE & pos, A_Declarator* declarator);

CodeCompExt A_DirectDeclarator* A_DirectDeclaratorId(const YYLTYPE & pos, Expression* id);
CodeCompExt A_DirectDeclarator* A_DirectDeclaratorParen(A_DirectDeclarator* directDeclarator, ParameterDeclarations* paramDecls, DeclSpecList * decls);
CodeCompExt A_DirectDeclarator* A_DirectDeclaratorArray(A_DirectDeclarator* directDeclarator, Expression* exp);

CodeCompExt Expression * A_TemplateId(System::StringA* id, A_TemplateArgumentList * params);

#if 0
//A_Dec* A_DecName(char*

class CodeCompExt PP_Token
{
public:

	enum
	{
		PP_CHAR,
		PP_INT32,
		PP_IDENTIFIER,
	}
	kind;

	union
	{
		char c;
		long int32;
		char* id;
	};

	int line_pos;

	System::StringA* toString();
};

class CodeCompExt PP_TokenList
{
public:

	CTOR PP_TokenList(PP_Token& _head, PP_TokenList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	PP_Token head;
	PP_TokenList* tail;
};

PP_Token PP_Char(YYLTYPE& pos, char c);
PP_Token PP_Int32(YYLTYPE& pos, long int32);
PP_Token PP_Identifier(YYLTYPE& pos, const char* id);

struct PP_Group;
struct PP_Directive;

class CodeCompExt PP_IdentifierList
{
public:

	PP_IdentifierList(const char* _head, PP_IdentifierList* _tail)
	{
		head = strdup(_head);
		tail = _tail;
	}

	char* head;
	PP_IdentifierList* tail;
};

struct CodeCompExt PP_ElifGroups
{
	PP_ElifGroups(PP_Directive* _head, PP_ElifGroups* _tail)
	{
		head = _head;
		tail = _tail;
	}

	PP_Directive* head;
	PP_ElifGroups* tail;
};

struct CodeCompExt PP_IfGroup
{
	enum
	{
		PP_IF,
		PP_IFDEF,
		PP_IFNDEF,
	}
	kind;

	union
	{
		Expression* exp;
		char* id;
	};

	PP_Group* group;
};

struct CodeCompExt PP_Directive
{
	enum
	{
//		PP_DEFINE,
		PP_ELIF,
//		PP_UNDEF,
		PP_INCLUDE,
		PP_LINE,
		PP_ERROR,
		PP_PRAGMA,
//		PP_IF_SECTION,
	}
	kind;

	union
	{

		struct
		{
			Expression* exp;
			PP_Group* group;
		}
		ELIF;
	};
};

struct CodeCompExt PP_GroupPart
{
	enum
	{
		PP_DEFINE,
		PP_UNDEF,
		PP_IF_SECTION,
		PP_DIRECTIVE,
		PP_TOKENS,
	}
	kind;

	union
	{
		struct
		{
			PP_IfGroup* ifGroup;
			PP_ElifGroups* elifGroups;
			PP_Group* elseGroup;
		}
		IF_SECTION;

		struct
		{
			char* id;
			PP_IdentifierList* argList;
			PP_TokenList* replacementList;
			bool bFunctionLike;
		}
		DEFINE;

		struct
		{
			char* id;
		}
		UNDEF;

		PP_Directive* directive;
		PP_TokenList* tokenList;
	};
};

struct CodeCompExt PP_Group
{
	PP_Group(PP_GroupPart* _part, PP_Group* _tail)
	{
		part = _part;
		tail = _tail;
	}

	PP_GroupPart* part;
	PP_Group* tail;
};

class CodeCompExt CDefine
{
public:
	CDefine()
	{
		m_bFunctionLike = false;
	}

	System::StringA* m_name;

	bool m_bFunctionLike;	// Even if m_params is empty, the macro could require empty parentheses
	Array<System::StringA*> m_argNames;

//	PP_IdentifierList* m_argNames;

//	std::string m_replacementString;

//	PP_TokenList* m_replacementList;
	CArray<PP_Token, PP_Token&> m_replacementList;

//	CFileLocation m_location;
	int m_line_pos;

	bool Equals(CDefine* pOther);
};

//typedef map<System::StringA*, CDefine*, Ref_Less<System::StringA> > macromap;

/*
PP_GroupPart* PP_Tokens(PP_TokenList* tokens);
PP_GroupPart* PP_IfSection(PP_IfGroup* ifGroup, PP_ElifGroups* elifGroups, PP_Group* elseGroup);
PP_GroupPart* PP_Define(const char* id, bool bFunctionLike, PP_IdentifierList* argList, PP_TokenList* replacementList);
PP_GroupPart* PP_Undef(const char* id);

PP_IfGroup* PP_If_Group(Expression* exp, PP_Group* group);
PP_IfGroup* PP_IfDefGroup(const char* id, PP_Group* group);
PP_IfGroup* PP_IfNDefGroup(const char* id, PP_Group* group);
PP_Directive* PP_ElifGroup(Expression* exp, PP_Group* group);
*/

#endif

CodeCompExt void Translate(DeclarationList* declarationList, cpp::CGlobal* pGlobal, System::Scope* pScope, System::Declarator* fun, int linkage);

CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_Declarator* declarator);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, Declaration* d);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, DeclarationList* declarationList);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_StmList* stmList);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, Expression* exp);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, ExpressionList* exp);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, DeclSpecList* declspecList);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, A_TypeId* typeId);
CodeCompExt IO::TextWriter& WriteToStream(IO::TextWriter& stream, InitDeclaratorList* dlist);

}	// ast

class TemplateArgs
{
public:
	CTOR TemplateArgs()
	{
		m_parent = NULL;
	}

	ActualTemplateArgs* m_pInstanceArgs;	// TODO rename to m_pInstanceArgs
	TemplateParams* m_pTemplateParams;
	const TemplateArgs* m_parent;

	System::Type* GetType(System::Type* pType) const;
};

class CodeCompExt CDeclaratorList : public Object
{
public:
	CTOR CDeclaratorList(System::Declarator* _head, CDeclaratorList* _tail)
	{
		ASSERT(_head);

		head = _head;
		tail = _tail;
	}

	System::Declarator* head;
	CDeclaratorList* tail;
};

}	// cpp
}	// System

#endif // cpp_ast_h