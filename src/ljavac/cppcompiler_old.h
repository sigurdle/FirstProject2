#ifndef __CPPCOMPILER_H_
#define __CPPCOMPILER_H_

#define ASSERT(x) ATLASSERT(x)
#define ASSERT_VALID(x)

#if 0
#include "..\Utils\UPtrList.h"
#endif

#include "../Utils/utempl.h"
#include "../Utils/UMap.h"

class ckw
{
public:
	char* str;

	inline ckw()
	{
		str = NULL;
	}

	inline ckw(char* _str)
	{
		str = _str;
	}

	inline ckw& operator = (const ckw& other)
	{
		str = other.str;
		return *this;
	}
};

inline bool operator == (const ckw& a, const ckw& b)
{
	return !strcmp(a.str, b.str);
}

/*
template<> inline UINT AFXAPI HashKey<char*> (char* key)
{
	return HashKey((LPCTSTR)key);
}
*/

template<> inline UINT AFXAPI HashKey<ckw&> (ckw& key)
{
	UINT nHash = 0;
	const char* str = key.str;
	while (*str)
		nHash = (nHash<<5) + nHash + *str++;
	return nHash;
}

//typedef std::map<std::string,int> kwmap;
typedef CUMap<ckw, ckw&, int, int> kwmap;

#define sizeof_pointer	4

#include "token.h"
#include "preprocessor.h"

enum A_ClassKey
{
	A_CLASSKEY_CLASS,
	A_CLASSKEY_STRUCT,
	A_CLASSKEY_UNION,
};

class CTExpression;

class CTStatement;

class T_Declarator;

struct Temp_label;


//typedef T_stmList_ *T_stmList;


namespace cpp
{
enum
{
	KW_VOID,
	KW_CHAR,
	KW_INT,
	KW_SHORT,
	KW_LONG,
	KW_SIGNED,
	KW_UNSIGNED,
	KW_RETURN,
	KW_IF,
	KW_ELSE,
	KW_CLASS,
	KW_STRUCT,
	KW_UNION,
	KW_ENUM,
	KW_BOOL,
	KW_WCHAR_T,
	KW_FLOAT,
	KW_DOUBLE,
	KW_AUTO,
	KW_REGISTER,
	KW_STATIC,
	KW_EXTERN,
	KW_MUTABLE,
	KW_INLINE,
	KW_VIRTUAL,
	KW_EXPLICIT,
	KW_SIZEOF,
	KW_CONST,
	KW_VOLATILE,
	KW_DYNAMIC_CAST,
	KW_STATIC_CAST,
	KW_REINTERPRET_CAST,
	KW_CONST_CAST,
	KW_TYPEDEF,
	KW_ASM,
	KW___ASM,
	KW_NAMESPACE,
	KW_USING,
	KW_TRY,
	KW_EXPORT,
	KW_TEMPLATE,
	KW_OPERATOR,
	KW_FRIEND,
	KW_WHILE,
	KW_DO,
	KW_SWITCH,
	KW_CASE,
	KW_DEFAULT,
	KW_BREAK,
	KW_CONTINUE,
	KW_GOTO,
	KW_PRIVATE,
	KW_PROTECTED,
	KW_PUBLIC,
	KW_FOR,
	KW_THIS,
	KW_TYPENAME,
	KW_NEW,
	KW_DELETE,
	KW_TRUE,
	KW_FALSE,
	KW___CDECL,
	KW___STDCALL,
	KW___INT64,
	KW___DECLSPEC,
};

class CType;
class CDeclarator;
class CDeclaratorReference;
class CScope;

class CNamedType
{
public:
	std::string m_name;
	PP::CFileLocation m_location;
};

#if 0
class CExpression
{
public:
	CExpression(/*CScope* pScope */)
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
	CType* m_pType;
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
			CType* m_pType;
		}
		cast;
	};

//	CScope* m_pScope;

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

class CDeclarator;

class CCPPCompiler;

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

	CScope* m_pScope;
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

	CScope* m_pIfScope;

	CExpression* m_testexpr;
	CCompoundStatement* m_substmt;
	CCompoundStatement* m_elsestmt;
};

/*
class CCaseLabel
{
public:
	CExpression* m_pExpr;
};
*/

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

	CScope* m_pSwitchScope;

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

class CClass;
class CTemplate;
class CFunction;
class CNamedType;

#define MODF_SIGNED		64
#define MODF_UNSIGNED	128
#define MODF_SHORT		256
#define MODF_LONG			512

enum CType_type
{
	type_invalid = -1,

	type_void = 0,
	type_bool = 1,

	type_char = 2,
	type_signed_char = 2 | MODF_SIGNED,
	type_unsigned_char = 2 | MODF_UNSIGNED,

	type_wchar = 3,

// signed int and int are interchangeable (maybe not according to standard ?)
	type_int = 4,
	type_short_int = 4 | MODF_SHORT,
	type_long_int = 4 | MODF_LONG,

	type_unsigned_int = 4 | MODF_UNSIGNED,
	type_unsigned_short_int = 4 | MODF_UNSIGNED | MODF_SHORT,
	type_unsigned_long_int = 4 | MODF_UNSIGNED | MODF_LONG,

	type_long_long = 5,
	type_unsigned_long_long = 5 | MODF_UNSIGNED,

	type_float = 6,
	type_double = 7,
	type_long_double = 7 | MODF_LONG,

	type_enum = 8,
	type_class  = 9,
	type_pointer = 10,
	type_reference = 11,
	type_array = 12,
	type_function = 13,
	type_templateinst = 14,
	type_cv = 15,
	type_pm = 16,
	type_typename = 17,
	type_typedef = 20,
};

class CType
{
public:
	CType(CType_type type = type_invalid, unsigned long size = -1)
	{
		m_type = type;
		m_sizeof = size;

		m_lvalue = true;	// ??

		m_pClass = NULL;
		m_pPointerTo = NULL;

		m_bConst = false;
		m_bVolatile = false;
	}

	bool m_lvalue;	// ??

	CType_type m_type;

	unsigned short	m_bConst : 1,
						m_bVolatile : 1;

	unsigned long m_sizeof;

	std::vector<unsigned long> m_arrayDims;

	union
	{
		CClass* m_pClass;	// If this type defines a class
		CType* m_pPointerTo;
		CFunction* m_pFunction;
		CNamedType* m_pNamedType;
		CDeclarator* m_pDeclarator;
		CExpression* m_pNestedNameSpecifier;

		struct
		{
			CType* m_pType;
			CClass* m_pClass;
		}
		pm;
	};

	std::vector<CType*> m_ArgTypes;	// template instantiation parameters

	unsigned int get_sizeof();

	// Shallow copy
	CType* Clone();

	/*
	int GetPointerLevel()
	{
		int level = 0;
		CType* pType = this;
		while (pType->m_type == type_pointer)
		{
			level++;

			ATLASSERT(pType->m_pPointerTo);
			pType = pType->m_pPointerTo;
		}

		return level;
	}
	*/

	//BOOL IsEqual(CType* pOther, BOOL bCheckQualification = TRUE);

	CType* GetType();

	BOOL IsConst();
	BOOL IsVolatile();

	BOOL IsEqual(CType* pOther, BOOL bConst = FALSE, BOOL bOtherConst = FALSE);
	int GetClassKey();
	CClass* GetClass();
	std::string toString();
};

class CDeclarator;

/*
class CMember
{
public:
	CMember()
	{
		m_offset = -1;
		m_pDeclarator = NULL;
	}

	int m_offset;
	CDeclarator* m_pDeclarator;

	BOOL IsEqual(CMember* pOther);
};
*/

class CFunction
{
public:
	CFunction()
	{
		m_thiscall = FALSE;
		m_funcspec = -1;
		m_bVarArg = false;
		//m_pBody = NULL;
		m_pReturnType = NULL;

		m_stackSize = 0;
	}

	CType* m_pReturnType;
	BOOL m_thiscall;
	int m_funcspec;
	std::vector<CDeclarator*> m_parameters;
	BOOL m_bVarArg;
	unsigned int m_stackSize;

	std::string ArgsToString();

	BOOL IsEqual(CFunction* pOther);
	void Evaluate(CCPPCompiler* pCompiler, CDeclarator* pFunctionDecl);

// libcall
	class libcall
	{
	public:
		libcall()
		{
			m_offset = 0;
		}
		std::string m_basename;
		short m_offset;
		short m_tagcall;
	}
	m_libcall;
};

class CDeclarator : public CNamedType
{
public:
	CDeclarator()
	{
		m_pType = NULL;
		m_pBody = NULL;

		m_referenced = false;
		m_defined = false;
		m_localVar = false;

		m_pInitializerExpr = NULL;
		m_linkage = -1;
		m_storageClassKW = -1;
#if 0	// Had this
//		m_spOffset = -1;
#endif

		m_offset = 0;

//		m_symbolIndex = 0;

		m_pOwnerScope = NULL;

		m_tempLabel = NULL;
	}

	Temp_label* m_tempLabel;

	std::string m_mangledName;

	CScope* m_pOwnerScope;	// pointer back to scope that owns this declaration

	short m_localVar;
	bool m_referenced : 1;
	bool m_defined : 1;
//	int m_symbolIndex;

	int m_linkage;
	int m_storageClassKW;
	CType* m_pType;
//#if 0
//	int m_spOffset;
//#endif

	int m_offset;	// offset if this is a member of a struct/class

	union
	{
		CExpression* m_pInitializerExpr;
	//	CFunctionBody* m_pBody;
		T_Declarator* m_pBody;
		//CToken* m_stringtok;
		struct
		{
			char* data;
			int len;
		}
		m_string;
	};
//	std::vector<CTStatement*> m_statementList;
//	T_stmList_ *m_statementList;

// libcall
	class libcall
	{
	public:
		libcall()
		{
			m_reg = -1;
		}
		int m_reg;
	}
	m_libcall;

//
	std::string MangleName();
	BOOL IsEqual(CDeclarator* pOther);
	std::string toString();
};

class CDeclaratorReferenceList
{
public:
	CDeclaratorReferenceList(CDeclaratorReference* _head, CDeclaratorReferenceList* _tail)
	{
		ATLASSERT(_head);

		head = _head;
		tail = _tail;
	}

	CDeclaratorReference* head;
	CDeclaratorReferenceList* tail;
};

class CDeclaratorReference
{
public:
	CDeclaratorReference(CDeclarator* pDeclarator)
	{
		m_pDeclarator = pDeclarator;
	}

	CDeclarator* m_pDeclarator;
};

class CNamespace;

typedef std::map<std::string,CNamespace*> namespacemap;
typedef std::map<std::string, CType*> typemap;
typedef std::map<std::string, int> identvaluemap;
typedef std::multimap<std::string, CDeclaratorReference*> declsmap;	// strings need not be
typedef std::vector<CDeclaratorReference*> declsvector;

class CClass;

/*
class CIDExpression
{
public:
	CIDExpression()
	{
		m_pExpr = NULL;
	}

	CExpression* m_pExpr;
};
*/

class CIDExpressions
{
public:
	std::vector<CExpression*> m_v;
};

class CCPPCompiler;

class CTemplateParameter
{
public:
	enum
	{
		Type_type,
		Type_declaration,
	}
	m_type;

	std::string m_name;

	union
	{
		CType* m_pType;
		CDeclarator* m_pDeclarator;
	};
};

class CTemplate
{
public:
	CTemplate()
	{
		m_pScope = NULL;

		m_pClass = NULL;
		m_pDeclarator = NULL;
	}

	std::vector<CTemplateParameter*> m_parameters;

	CClass* m_pClass;
	CDeclarator* m_pDeclarator;

	CScope* m_pScope;
};

typedef std::map<std::string, CTemplate*> templatemap;

class CScope
{
public:
	CScope()
	{
		m_pParentScope = NULL;

		m_pClass = NULL;
		m_pTemplate = NULL;

#if 0
		m_spOffset = 0L;
		m_stackSize = 0L;
#endif
	}

	~CScope()
	{
		if (m_pParentScope)
		{
			/*
			for (int i = 0; i < m_pIDExprs->m_v.size(); i++)
			{
				m_pParentScope->m_pIDExprs->m_v.push_back(m_pIDExprs->m_v[i]);
			}
			*/
		}

	}

	CScope* m_pParentScope;
	std::vector<CScope*> m_subScopes;

	DWORD m_startAddress;
	DWORD m_endAddress;

	CTemplate* m_pTemplate;	// This scope belongs to this template
	CClass* m_pClass;	// This scope belongs to this class

#if 0
	ULONG m_spOffset;
	ULONG m_stackSize;
#endif

	typemap m_types;
	namespacemap m_namespaces;
	declsmap m_decls;
	declsvector m_orderedDecls;
	identvaluemap m_identvalues;
	//templatemap m_templates;

	CExpression* GetIdentValue(const char* name, CScope* pScope)
	{
		identvaluemap::iterator enumi = m_identvalues.find(name);
		if (enumi != m_identvalues.end())
		{
			CExpression* pExpr = new CExpression;
			pExpr->tok.type = CToken::tok_integer;
			pExpr->tok.int32 = (*enumi).second;

			return pExpr;
		}
		else
		{
			if (m_pParentScope)
			{
				return m_pParentScope->GetIdentValue(name, pScope);
			}
			return NULL;
		}
	}

	void AddType(CCPPCompiler* pCompiler, CType* pType);

	CType* GetType(const char* name)
	{
		ATLASSERT(name);
		ATLASSERT(name[0]);

		typemap::iterator i = m_types.find(name);
		if (i != m_types.end())
		{
			return (*i).second;
		}
		else
		{
			if (m_pParentScope)
			{
				return m_pParentScope->GetType(name);
			}
			return NULL;
		}
	}

#if 0
	CTemplate* GetTemplate(const char* name)
	{
		ATLASSERT(name);
		ATLASSERT(name[0]);

		templatemap::iterator i = m_templates.find(name);
		if (i != m_templates.end())
		{
			return (*i).second;
		}
		else
		{
			if (m_pParentScope)
			{
				return m_pParentScope->GetTemplate(name);
			}
			return NULL;
		}
	}
#endif

	void AddReferenceDeclarator(CDeclaratorReference* pDeclaratorRef)
	{
		ATLASSERT(pDeclaratorRef);
	//	ATLASSERT(pDeclarator->m_name.length());

		declsmap::iterator decli = m_decls.insert(declsmap::value_type(pDeclaratorRef->m_pDeclarator->m_name, pDeclaratorRef));
	}

	void AddDeclarator(CDeclaratorReference* pDeclaratorRef)
	{
		ATLASSERT(pDeclaratorRef);
	//	ATLASSERT(pDeclarator->m_name.length());

		declsmap::iterator decli = m_decls.insert(declsmap::value_type(pDeclaratorRef->m_pDeclarator->m_name, pDeclaratorRef));
	//	pDeclaratorRef->m_pDeclarator->m_referenced = 2;
		pDeclaratorRef->m_pDeclarator->m_defined = true;
		m_orderedDecls.push_back(pDeclaratorRef);
	}

	CScope* GetScope(const char* name);
	CScope* GetScope2(const char* name);
	CDeclaratorReference* GetDeclarator(const char* name);
};

class CNamespace
{
public:
	CNamespace* m_pParentNamespace;

	std::string m_name;
	CScope* m_pScope;
};

// ??
class CBaseClass
{
public:
	CBaseClass()
	{
		m_offset = 0;
		m_pClass = NULL;
	}

	unsigned int m_offset;
	CClass* m_pClass;
};

class CClass : public CNamedType
{
public:

	CClass(/*CType* pType*/)
	{
#if 0
		m_pType = pType;
#endif

		m_pIDExprs = new CIDExpressions;

		m_checkingEquality = 0;
		m_sizeof = -1;

		m_pTemplate = NULL;

		m_pScope = T_Scope();
		m_pScope->m_pClass = this;
	}

	~CClass()
	{
		if (m_pIDExprs)
		{
			delete m_pIDExprs;
			m_pIDExprs = NULL;
		}

		if (m_pScope)
		{
			delete m_pScope;
			m_pScope = NULL;
		}
	}

	void Evaluate();

	CTemplate* m_pTemplate;

	CIDExpressions* m_pIDExprs;

#if 0
	CType* m_pType;
#endif

	CScope* m_pScope;

	short m_checkingEquality;

	A_ClassKey m_kwType;
#if 0
	std::vector<CMember*> m_members;	// TODO remove ??
#endif

	CScope* GetScope(const char* name);
	CDeclaratorReference* GetDeclarator(const char* name);

	unsigned int m_sizeof;

	//std::vector<CClass*> m_bases;
	std::vector<CBaseClass> m_bases;

#if 0
	CMember* GetMember(const char* name)
	{
		ATLASSERT(this);

		for (int i = 0; i < m_members.size(); i++)
		{
			CMember* pMember = m_members[i];
			if (!strcmp(pMember->m_pDeclarator->m_name.c_str(), name))
			{
				return pMember;
			}
		}

		return NULL;
	}
#endif

	unsigned int get_sizeof();

	unsigned int GetOffset(CClass* pClass);

	BOOL IsEqual(CClass* pOther);

	CClass* Clone(CType* pType);
};

class CTypedef : public CNamedType
{
public:
	CTypedef()
	{
		m_pDeclarator = NULL;
	}

	CDeclarator* m_pDeclarator;
};

/*
class CSymbol
{
public:
	std::string m_name;
};
*/

class CGlobal
{
public:

	CNamespace* m_pNamespace;

	//std::vector<CDeclarator*> m_declarations;

//	templatemap m_templates;

	std::vector<CDeclaratorReference*> m_globals;
	std::vector<CDeclaratorReference*> m_references;
	std::vector<CDeclarator*> m_strings;
};

class CCPPCompiler;

class CTypeSpecifiers
{
public:
	CTypeSpecifiers()
	{
		m_pType = NULL;

		m_typeKW = -1;
		m_size = 0;
		m_sign = 0;
		m_bConst = false;
		m_bVolatile = false;

		m_bSimpleTypeSpecified = false;
	}

	bool m_bSimpleTypeSpecified;

	CType* m_pType;
	int m_typeKW;	// -1 unspecified, void,bool,char,int,float,double
	int m_size;	// 0=unspecified,1=short,2=long
	int m_sign;	// 0=unspecified,1=signed, -1=unsigned
	bool m_bConst;
	bool m_bVolatile;

	CType* GetType(CCPPCompiler* pCompiler);
};

class CDeclSpecifiers
{
public:
	CDeclSpecifiers()
	{
		functionSpecifierKW = -1;
		storageClassKW = -1;
	}

	int functionSpecifierKW;
	int storageClassKW;
	CTypeSpecifiers m_type;
};

/*
class CSave
{
public:
	std::stack<CToken> m_tokStack;
};
*/

#if 0
class CCPPCompiler : public CCompiler
{
public:

	CCPPCompiler()
	{
//		gSave = NULL;
	}

	CGlobal* pGlobal;
	PP::CPreprocessor* pPP;

	std::stack<CToken> m_tokStack;
//	CSave* gSave;

	std::stack<CToken> m_tokStack2;
	void Restore(int n);

//	void Restore(CSave* gSave2);

	CToken* ConvertToken(PP::CToken* tokpp);
	CToken* GetString(int delimiter, BOOL bWide, CToken& token);
	CToken* GetCharacter(int delimiter, BOOL bWide, CToken& token);
	CToken* GetToken();
	void EatSymbol(int c);

	CType* InstantiateTemplateType(std::vector<CType*>& ArgTypes, CType* pType);

//	CTExpression* ConvertExpressionType(CExpression* pExpr, CType* p2Type, BOOL b2Const = FALSE);
	CScope* GetScope(CScope* pScope, CExpression* pExpr);

	CScope* GetNestedScope(CScope* pScope, CExpression* pExpr);

//	CType* ExpressionType(CExpression* pExpr, CScope* /* pScope*/);
	CExpression* unqualified_id(CScope* pScope);
	CExpression* id_expression(CClass* pNamespace, CScope* pScope);
	CExpression* literal(CScope* pScope);
	CExpression* primary_expression(CClass* pNamespace, CScope* pScope);
	CExpression* cast_expression(CClass* pNamespace, CScope* pScope);
	CExpression* expression_list(CClass* pNamespace, CScope* pScope);
	CExpression* postfix_expression(CClass* pNamespace, CScope* pScope);
	CExpression* unary_expression(CClass* pNamespace, CScope* pScope);
	CExpression* pm_expression(CClass* pNamespace, CScope* pScope);
	CExpression* multiplicative_expression(CClass* pNamespace, CScope* pScope);
	CExpression* additive_expression(CClass* pNamespace, CScope* pScope);
	CExpression* shift_expression(CClass* pNamespace, CScope* pScope);
	CExpression* relational_expression(CClass* pNamespace, CScope* pScope);
	CExpression* equality_expression(CClass* pNamespace, CScope* pScope);
	CExpression* and_expression(CClass* pNamespace, CScope* pScope);
	CExpression* exclusive_or_expression(CClass* pNamespace, CScope* pScope);
	CExpression* inclusive_or_expression(CClass* pNamespace, CScope* pScope);
	CExpression* logical_and_expression(CClass* pNamespace, CScope* pScope);
	CExpression* logical_or_expression(CClass* pNamespace, CScope* pScope);
//	CExpression* conditional_expression(CClass* pNamespace, CScope* pScope);
	CExpression* assignment_expression(CClass* pNamespace, CScope* pScope);
	CExpression* constant_expression(CClass* pNamespace, CScope* pScope);
	CExpression* expression(CClass* pNamespace, CScope* pScope);
	CExpression* nested_name_specifier(CScope* pScope);

//	CExpression* Reduce2(CExpression* pExpr, CScope* pScope);

	/////////////////////////
	////////////////////////

	CDeclarator* member_declarator(CClass* pClass, CDeclSpecifiers& declspecs, CClass* pInnermostClass, CScope* pScope);
	void member_declaration(CClass* pClass, CClass* pInnermostClass, CScope* pScope);
	void member_specification(CClass* pClass, CClass* pInnermostClass, CScope* pScope);

	CStatement* statement(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CScope* pScope);
	void statement_seq(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CFunctionBody* pFunctionBody, CScope* pScope);
	void compound_statement(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CFunctionBody* pFunctionBody, CScope* pScope);
	CCompoundStatement* compound_statement(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CScope* pScope);

	CType* ReplaceType(std::vector<CType*>& ArgTypes, CType* pType);

	BOOL simple_type_specifier(CTypeSpecifiers& typespecs, CScope* pScope);
	void base_specifier_list(CClass* pClass, CScope* pScope);

	void enumerator_definition(CClass* pInnermostClass, CScope* pScope, int& counter);
	void enumerator_list(CClass* pInnermostClass, CScope* pScope);
	BOOL type_specifier(CTypeSpecifiers& typespecs, CClass* pInnermostClass, CScope* pScope);
	BOOL decl_specifier_seq(CClass* pNamespace, CScope* pScope, CDeclSpecifiers& declspecs, bool& bTypedef);

	CExpression* declarator_id(CClass* pInnermostClass, CScope* pScope);

	CExpression* initialize(CExpression* dst, CExpression* pInitializerExpr, CType* pType, CCompoundStatement* pCompoundStmt);

	CDeclarator* parameter_declaration(CClass* pInnermostClass, CScope* pScope);
	void parameter_declaration_list(CFunction* pFunction, CClass* pNamespace, CScope* pScope);
	void parameter_declaration_clause(CFunction* pFunction, CClass* pNamespace, CScope* pScope);
	CType* type_specifier_seq(CClass* pNamespace, CScope* pScope);
	CType* abstract_declarator(CType* pType);
	CType* type_id(CClass* pNamespace, CScope* pScope);
	CType* direct_declarator(CDeclarator* pDeclarator, CType* pType, CClass* pInnermostClass, CScope* pScope);
	void typedef_declarator(CDeclarator* pDeclarator, CScope* pScope);
	BOOL nontypedef_declarator(CDeclarator* pDeclarator, CClass* pInnermostClass, CScope* pScope);
	void init_declarator_list(CScope* pScope);
	CType* declarator(CDeclarator* pDeclarator, CType* pType, CClass* pInnermostClass, CScope* pScope);
	CTemplateParameter* template_parameter(CClass* pInnermostClass, CScope* pScope);
	void function_body(CGlobal* pGlobal, CClass* pInnermostClass, CDeclarator* pFunctionDecl, CFunctionBody* pFunctionBody, CScope* pScope);
//	BOOL ctor_initializer();
	void asm_definition();
//	void linkage_specification(CGlobal* pGlobal, CClass* pNamespace, CScope* pScope);
	void namespace_body(CGlobal* pGlobal, CClass* pNamespace, CScope* pScope, int linkage);
	CExpression* initializer_clause(/*CDeclarator* pDeclarator,*/ CClass* pInnermostClass, CScope* pScope);
	BOOL simple_declaration_or_function_definition(CGlobal* pGlobal, CClass* pInnermostClass, CScope* pScope, int linkage, int storageClassKW, CTemplate* pTemplate);
	void template_declaration(CClass* pInnermostClass, CScope* pScope);
	BOOL declaration(CGlobal* pGlobal, CClass* pInnermostClass, CScope* pScope, int linkage, CTemplate* pTemplate = NULL);

	void declaration_seq(CGlobal* pGlobal, CClass* pInnermostClass, CScope* pScope, int linkage);
	void translation_unit(CGlobal* pGlobal, PP::CPreprocessor* argPP);

// CCompiler
	virtual void OnPragma();
};
#endif

}

/*
struct A_Declarator
{
	cpp::CType* m_pType;
	char* id;
};

struct A_DecList
{
};
*/

struct YYLTYPE;

struct A_DirectDeclarator;
struct A_Declarator;
struct A_DeclaratorList;
struct A_Declaration;
struct A_DeclarationList;
struct A_StmList;
struct A_TypeId;
struct A_ExpList;

struct A_Exp
{
	enum
	{
		A_BINOP,
		A_UNOP,
		A_ID,
		A_BOOL,
		A_STRING,
		A_LSTRING,
		A_INT32,
		A_INT64,
		A_CAST,
		A_CALL,
	}
	kind;

	union
	{
		struct
		{
			int op;
			A_Exp* left;
			A_Exp* right;
		}
		binop;

		struct
		{
			int op;
			A_Exp* exp;
		}
		unop;

		struct
		{
			A_TypeId* typeId;
			A_Exp* exp;
		}
		cast;

		struct
		{
			A_Exp* left;
			A_ExpList* args;
		}
		call;

		int boolValue;

		char* id;
		char* string;
		long int32;
		__int64 int64;
	};

	int line_pos;
};

struct A_ExpList
{
	A_ExpList(A_Exp* _head, A_ExpList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_Exp* head;
	A_ExpList* tail;
};

struct A_Condition
{
};

struct A_Stm
{
	enum
	{
		A_INVALID = -1,
		A_IF,
		A_SWITCH,
		A_EXP,
		A_DECLARATION,
		A_EXP_OR_DECLARATION,
		A_COMPOUND,
	}
	kind;

	A_Stm()
	{
		kind = A_INVALID;
	}

	union
	{
		struct
		{
			A_Condition* cond;
			A_Stm* stm;
			A_Stm* elseStm;
		}
		IF;

		struct
		{
			A_Condition* cond;
			A_Stm* stm;
		}
		SWITCH;

		struct
		{
			A_Exp* exp;
			A_Declaration* declaration;
		}
		EXP_OR_DECL;

		A_Exp* exp;
		A_Declaration* declaration;
		A_StmList* compound;
	};
};

struct A_StmList
{
	A_StmList(A_Stm* stm, A_StmList* stmList)
	{
		head = stm;
		tail = stmList;
	}

	A_Stm* head;
	A_StmList* tail;
};

inline const char* A_ClassKeyName(A_ClassKey classKey)
{
	return classKey==A_CLASSKEY_CLASS? "class": classKey==A_CLASSKEY_STRUCT? "struct": "union";
}

enum A_AccessSpec
{
	A_ACCESS_PRIVATE,
	A_ACCESS_PROTECTED,
	A_ACCESS_PUBLIC,
};

enum A_SimpleTypeSpecifier
{
	A_CHAR,
	A_WCHAR_T,
	A_BOOL,
	A_SHORT,
	A_INT,
	A___INT64,
	A_LONG,
	A_SIGNED,
	A_UNSIGNED,
	A_FLOAT,
	A_DOUBLE,
	A_VOID,

	A_CONST,
	A_VOLATILE,
};

enum A_DeclSpecifierKeyword
{
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
};

struct A_MemberSpec
{
	enum
	{
		A_MEMBER_DECL,
		A_ACCESS_SPEC,
	}
	kind;

	union
	{
		A_Declaration* declaration;
		A_AccessSpec accessSpec;
	};

	A_MemberSpec* next;
};

struct A_TypeSpec
{
//	cpp::CType_type kind;
//	A_Type* pointerTo;
//	bool bConst;
//	bool bVolatile;
	enum
	{
		A_NAME,
		A_SIMPLE,
		A_ENUM,
		A_CLASS,
		A_CLASSDEF,
	}
	kind;

	union
	{
		A_SimpleTypeSpecifier simple;

		char* name;

		struct
		{
			char* name;
		}
		ENUM;

		struct
		{
			A_ClassKey classKey;
			char* name;
			int line_pos;
		}
		CLASS;

		struct
		{
			A_ClassKey classKey;
			char* name;
			int line_pos;

			A_MemberSpec* memberSpec;
		}
		CLASSDEF;
	};
};

struct A_DeclSpec
{
	enum
	{
		A_KEYWORD,
		A_TYPE,
	}
	kind;

	union
	{
		A_DeclSpecifierKeyword keyword;
		A_TypeSpec* type;
	};
};

template<class T> struct List
{
	List(T* _head, List<T>* _tail)
	{
		head = _head;
		tail = _tail;
	}

	T* head;
	List<T>* tail;
};

class A_DeclSpecList
{
public:
	A_DeclSpecList(A_DeclSpec* _head, A_DeclSpecList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_DeclSpec* head;
	A_DeclSpecList* tail;
};

/*
struct A_TypeSpecList
{
	A_TypeSpecList(A_Type* _head, A_TypeSpecList* _tail)
	{
		ATLASSERT(_head);

		head = _head;
		tail = _tail;
	}

	A_Type* head;
	A_TypeSpecList* tail;
};
*/

struct A_Declaration
{
	enum
	{
		A_EXTERN_LINKAGE,
		A_NAMESPACE,
		A_FUNDEF,
		A_SIMPLE,
		A_DECLARATION2,
	}
	kind;

	union
	{
		struct
		{
			char* linkage;
			A_DeclarationList* declarationList;
		}
		extern_linkage;

		struct
		{
			A_DeclSpecList* declspecList;
			A_Declarator* declarator;
			A_StmList* stmList;
		}
		fundef;

		struct
		{
			A_DeclSpecList* declspecList;
			A_DeclaratorList* declaratorList;
		}
		simple;

		struct
		{
			A_Declaration* d1;
			A_Declaration* d2;
		}
		declaration2;
	};
};

struct A_TypeId
{
	A_TypeId(A_DeclSpecList* _declspecList, A_Declarator* _declarator)
	{
		ATLASSERT(_declspecList != NULL || _declarator != NULL);

		declspecList = _declspecList;
		declarator = _declarator;
	}

	A_DeclSpecList* declspecList;
	A_Declarator* declarator;
};

struct A_TypeIdList
{
	A_TypeIdList(A_TypeId* _head, A_TypeIdList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	A_TypeId* head;
	A_TypeIdList* tail;
};

struct A_ParameterDeclarations
{
	A_ParameterDeclarations(A_TypeIdList* _params, bool _varArgs)
	{
		params = _params;
		varArgs = _varArgs;
	}

	A_TypeIdList* params;
	bool varArgs;
};

struct A_Declarator
{
	enum
	{
		A_DIRECT_DECLARATOR,
		A_PTR
	}
	kind;

	union
	{
		A_Declarator* ptr;
		A_DirectDeclarator* directDeclarator;
	};

	cpp::CScope* Extract(cpp::CDeclarator* pDeclarator, cpp::CType* pType, cpp::CScope* pScope);
};

struct A_DirectDeclarator
{
	enum
	{
		A_DIRECT_DECLARATOR,
		A_DECLARATOR_ID,
		A_DECLARATOR,
	}
	kind;

	union _u
	{
		struct _directDeclarator
		{
			enum
			{
				A_PAREN,
				A_ARRAY,
			}
			kind;

			union
			{
				A_ParameterDeclarations* paramDecls;
				/*
				struct
				{
				}
				paren;
				*/
				A_Exp* array;
			};

			A_DirectDeclarator* directDeclarator;
		}
		directDeclarator;

		A_Declarator* declarator;

		A_Exp* declaratorId;
	}
	u;
	int line_pos;
};

struct A_DeclarationList
{
	A_DeclarationList(A_Declaration* declaration, A_DeclarationList* declarationList)
	{
		ATLASSERT(declaration);

		head = declaration;
		tail = declarationList;
	}

	A_Declaration* head;
	A_DeclarationList* tail;
};

struct A_DeclaratorList
{
	A_DeclaratorList(A_Declarator* declarator, A_DeclaratorList* declaratorList)
	{
	//	ATLASSERT(declarator); TODO, have this

		head = declarator;
		tail = declaratorList;
	}

	A_Declarator* head;
	A_DeclaratorList* tail;
};

A_Exp* A_BinopExp(YYLTYPE& pos, int op, A_Exp* e1, A_Exp* e2);
A_Exp* A_UnopExp(int op, A_Exp* e);
A_Exp* A_IdExp(const char* id);
A_Exp* A_IdExp(YYLTYPE& pos, const char* id);
A_Exp* A_StringExp(const char* string);
A_Exp* A_LStringExp(const char* string);
A_Exp* A_Int32Exp(long num);
A_Exp* A_BoolExp(int boolValue);
A_Exp* A_CastExp(A_TypeId* typeId, A_Exp* exp);
A_Exp* A_CallExp(A_Exp* f, A_ExpList* args);

A_Stm* A_DeclarationStm(A_Declaration* declaration);
A_Stm* A_IfStm(A_Condition* cond, A_Stm* stm, A_Stm* elseStm);
A_Stm* A_SwitchStm(A_Condition* cond, A_Stm* stm);
A_Stm* A_CompoundStm(A_StmList* stmList);
A_Stm* A_ExpStm(A_Exp* exp);

A_Declarator* A_PtrDeclarator(A_Declarator* declarator);
//A_DeclaratorList* A_DeclaratorList(A_Declarator* declarator, A_DeclaratorList* declaratorList);

A_Declaration* A_LinkageDeclaration(const char* linkage, A_DeclarationList* declarationList);
A_Declaration* A_FunDef(A_DeclSpecList* declspecList, A_Declarator* declarator, A_Stm* stm);
A_Declaration* A_SimpleDeclaration(A_DeclSpecList* declspecList, A_DeclaratorList* declaratorList);
A_Declaration* A_Declaration2(A_Declaration* d1, A_Declaration* d2);
//A_DeclarationList* A_DeclarationList(A_Declaration* declaration, A_DeclarationList* declarationList);

A_Declarator* A_DirectDeclaratorDeclarator(A_DirectDeclarator* directDeclarator);
A_DirectDeclarator* A_DirectDeclaratorDeclarator(A_Declarator* declarator);
A_DirectDeclarator* A_DirectDeclaratorId(YYLTYPE& pos, A_Exp* id);
A_DirectDeclarator* A_DirectDeclaratorParen(A_DirectDeclarator* directDeclarator, A_ParameterDeclarations* paramDecls);
A_DirectDeclarator* A_DirectDeclaratorArray(A_DirectDeclarator* directDeclarator, A_Exp* exp);

A_TypeSpec* A_NameType(const char* name);
A_TypeSpec* A_SimpleType(A_SimpleTypeSpecifier simpleType);
A_TypeSpec* A_Enum(const char* name);
A_TypeSpec* A_Class(YYLTYPE& pos, A_ClassKey classKey, const char* name);
A_TypeSpec* A_ClassDef(YYLTYPE& pos, A_ClassKey classKey, const char* name/*, A_MemberSpec* memberSpec*/);

A_DeclSpec* A_TypeSpecifier(A_TypeSpec* type);
A_DeclSpec* A_DeclSpecifier(A_DeclSpecifierKeyword declSpecifier);

A_MemberSpec* A_MemberDecl(A_Declaration* declaration, A_MemberSpec* next);
A_MemberSpec* A_MemberAccessSpec(A_AccessSpec accessSpec, A_MemberSpec* next);

//A_Dec* A_DecName(char*

struct PP_Token
{
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

	std::string toString();
};

struct PP_TokenList
{
	PP_TokenList(PP_Token& _head, PP_TokenList* _tail)
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

struct PP_IdentifierList
{
	PP_IdentifierList(const char* _head, PP_IdentifierList* _tail)
	{
		head = strdup(_head);
		tail = _tail;
	}

	char* head;
	PP_IdentifierList* tail;
};

struct PP_ElifGroups
{
	PP_ElifGroups(PP_Directive* _head, PP_ElifGroups* _tail)
	{
		head = _head;
		tail = _tail;
	}

	PP_Directive* head;
	PP_ElifGroups* tail;
};

struct PP_IfGroup
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
		A_Exp* exp;
		char* id;
	};

	PP_Group* group;
};

struct PP_Directive
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
			A_Exp* exp;
			PP_Group* group;
		}
		ELIF;
	};
};

struct PP_GroupPart
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

struct PP_Group
{
	PP_Group(PP_GroupPart* _part, PP_Group* _tail)
	{
		part = _part;
		tail = _tail;
	}

	PP_GroupPart* part;
	PP_Group* tail;
};

class CDefine
{
public:
	CDefine()
	{
		m_bFunctionLike = false;
	}

	std::string m_name;

	BOOL m_bFunctionLike;	// Even if m_params is empty, the macro could require empty parentheses
	std::vector<std::string> m_argNames;

//	PP_IdentifierList* m_argNames;

//	std::string m_replacementString;

//	PP_TokenList* m_replacementList;
	std::vector<PP_Token> m_replacementList;

//	CFileLocation m_location;
	int m_line_pos;

	BOOL IsEqual(CDefine* pOther);
};

typedef std::map<std::string, CDefine*> macromap;

PP_GroupPart* PP_Tokens(PP_TokenList* tokens);
PP_GroupPart* PP_IfSection(PP_IfGroup* ifGroup, PP_ElifGroups* elifGroups, PP_Group* elseGroup);
PP_GroupPart* PP_Define(const char* id, bool bFunctionLike, PP_IdentifierList* argList, PP_TokenList* replacementList);
PP_GroupPart* PP_Undef(const char* id);

PP_IfGroup* PP_If_Group(A_Exp* exp, PP_Group* group);
PP_IfGroup* PP_IfDefGroup(const char* id, PP_Group* group);
PP_IfGroup* PP_IfNDefGroup(const char* id, PP_Group* group);
PP_Directive* PP_ElifGroup(A_Exp* exp, PP_Group* group);

#endif // __CPPCOMPILER_H_
