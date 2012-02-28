#ifndef __TRANSLATE_H_
#define __TRANSLATE_H_

#ifndef CodeCompExt
#define CodeCompExt DECLSPEC_DLLIMPORT
#endif

namespace System
{

//class CGlobal;

class T_Declarator;

class CodeCompExt Temp_label
{
public:
	CTOR Temp_label();

	bool m_defined : 1;

	int m_spOffset;
	int m_symbolIndex;
	int m_n;

//	ULONG m_pos;
//	std::vector<DWORD> m_branches;
};

struct Temp_labelList
{
	CTOR Temp_labelList(Temp_label* _head, Temp_labelList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	Temp_label* head;
	Temp_labelList* tail;
};

class T_Exp;

class CodeCompExt Temp_temp
{
public:

	CTOR Temp_temp();
	CTOR Temp_temp(const char* _name, int n);

	Temp_temp* getalias()
	{
		if (m_alias)
			return m_alias->getalias();
		else
			return this;
	}

	int getn() const
	{
		if (m_alias)
			return m_alias->getn();
		else
			return m_n;
	}

	char* name;

	Temp_temp* m_alias;

	Temp_temp** m_second;
	Temp_temp** m_aux;

	T_Exp* m_exp;

	int m_n;

	int m_a;

	int m_dn;
	int m_an;

	int m_size;

//	int m_refcount;

	bool m_precolored;

	static int count;
};

class T_Exp;
class Temp_tempList;
class C_stmListList;
class T_StmList;

class expRefList
{
public:
	CTOR expRefList(T_Exp** _head, expRefList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	T_Exp** head;
	expRefList* tail;
};

class A_IdentifierList
{
public:
	CTOR A_IdentifierList(StringIn _head, A_IdentifierList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	String head;
	A_IdentifierList* tail;
};

class T_Stm : public Object
{
public:
	CTOR T_Stm(C_stmListList* block = NULL)
	{
		m_line_pos = -1;
//		kind = 0;
		seq.left = NULL;
		seq.right = NULL;

		m_block = block;

/*
		m_dst = NULL;
		m_src[0] = NULL;
		m_src[1] = NULL;
*/	}

	enum
	{
		T_NULL = 0,
		T_LBRAC = 1,
		T_RBRAC,
		T_LSYM,
		T_LABEL,

		T_EXP = 64,
		T_SEQ,
		T_JUMP,
		T_CJUMP,
		T_MOVE,
		T_ZERO,

		T_FUN,
		T_VAR,
		T_RETURN
	}
	kind;

	C_stmListList* m_block;

	int m_line_pos;

//	Temp_tempList* m_dst;
//	Temp_tempList* m_src[2];

	struct
	{
		T_Declarator* declarator;

		struct
		{
			T_Stm* left;
			T_Stm* right;
		}
		seq;

		struct
		{
			T_Exp* left;
			T_Exp* right;
		}
		move;

		struct
		{
			int relop;
			T_Exp* left;
			T_Exp* right;
			Temp_label* t;
			Temp_label* f;
		}
		cjump;

		struct
		{
			T_Exp* exp;
			Temp_labelList* labels;
		}
		jump;

		struct
		{
			int m_spOffset;
			int m_length;
		}
		zero;

		T_Exp* exp;

		Temp_label* label;

		struct
		{
			uint16 name;
		}
		var;

		struct
		{
			String m_name;
			A_IdentifierList* m_formals;
			T_StmList* m_body;
		}
		fun;
	};
};

class T_StmList
{
public:
	CTOR T_StmList(T_Stm* _head, T_StmList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	T_Stm* head;
	T_StmList* tail;
};

class C_stmListListList;

class C_stmListList
{
public:
	CTOR C_stmListList(T_StmList* _head)
	{
		succ = NULL;
		pred = NULL;
		children = NULL;

		head = _head;
	}

	C_stmListListList* children;

	C_stmListListList* succ;
	C_stmListListList* pred;

	T_StmList* head;
};

class C_stmListListList
{
public:
	CTOR C_stmListListList(C_stmListList* _head, C_stmListListList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	C_stmListList* head;
	C_stmListListList* tail;
};

class C_block
{
public:
	C_stmListListList* stmLists;

	map<Temp_label*, C_stmListList*> labels;

//	map<C_stmListList*, C_stmListListList*> prev;

//	Temp_label* label;
};

class CodeCompExt ExpList
{
public:
	CTOR ExpList(T_Exp* _head, ExpList* _tail)
	{
		head = _head;
		tail = _tail;
	//	reg = -1;
	}

	T_Exp* head;
	ExpList* tail;
};

class CodeCompExt ArgList
{
public:
	CTOR ArgList(T_Exp* _head, ArgList* _tail)
	{
		head = _head;
		tail = _tail;
		reg = NULL;
	}

	T_Exp* head;
	Temp_temp** reg;
	ArgList* tail;
};

/*
class PhiArg
{
public:
	PhiArg(C_stmListList* _pred, Temp_temp** _temp)
	{
		pred = _pred;
		temp = _temp;
	}

	C_stmListList* pred;
	Temp_temp** temp;
};
*/

class CodeCompExt T_Exp : public Object
{
public:
	CTOR T_Exp()
	{
		binop.left = NULL;
		binop.right = NULL;
//		call.m_pBaseDeclarator = NULL;	// libcall

		m_pDeclaratorRef = NULL;

		m_result = NULL;

/*		m_dst = NULL;
		m_src[0] = NULL;
		m_src[1] = NULL;
*/	}

//	Temp_tempList* m_dst;
//	Temp_tempList* m_src[2];

	T_Exp* Clone() const;

	Temp_temp** m_result;

#define T_IMMEDIATE	32

	enum Kind
	{
		T_MEM = 1,
		T_BINOP = 2,
		T_UNOP = 3,
		T_TEMP = 4,
		T_ESEQ = 5,
		T_CALL = 6,
		T_ADDRESSOF = 7,
		T_PHI = 9,

		//
		T_NEW = 10,
		T_MEMBER = 11,
		T_VARIABLE = 12,
		T_FUNCTION = 13,
		T_STRING = 14,
		T_STRINGW = 15,
		T_NULL = 16,
		T_UNDEFINED = 17,

		T_CONST_BOOL = 32 | T_IMMEDIATE,
		T_CONST = 33 | T_IMMEDIATE, T_CONST_INT32 = 33 | T_IMMEDIATE,
		T_CONST_INT64 = 34 | T_IMMEDIATE,
		T_CONST_FLOAT = 35 | T_IMMEDIATE,
		T_CONST_DOUBLE = 36 | T_IMMEDIATE,
		T_NAME = 37 | T_IMMEDIATE,
		T_OBJECT = 38 | T_IMMEDIATE,
	};

	virtual Kind GetKind()	// TODO abstract
	{
		return kind;
	}

	Kind kind;	// TODO remove

	Declarator* m_pDeclaratorRef;	// Used if tok ident

//	long m_spOffset;
	int m_size;

	union
	{

		char* variable;

		T_Exp* addressof;	// must be T_VARIABLE			

		struct
		{
			uint32 int32Val;
			uint64 int64Val;
#if 0
			//FRelocation* reloc;
			RelocConst* reloc;//cpp::CDeclarator* pDeclarator;
#endif
		}
		const_int;

		struct
		{
			bool value;
		}
		const_bool;

		union
		{
			float float32;
			uint32 intbits;
#if 0
			//FRelocation* reloc;
			RelocConst* reloc;//cpp::CDeclarator* pDeclarator;
#endif
		}
		const_float;

		union
		{
			double float64;
			uint64 intbits;
#if 0
			//FRelocation* reloc;
			RelocConst* reloc;//cpp::CDeclarator* pDeclarator;
#endif
		}
		const_double;

		struct
		{
			int op;
			T_Exp* exp;
		//	int size;	// used for se/ze
		}
		unop;

		struct
		{
			int op;
			T_Exp* left;
			T_Exp* right;
		}
		binop;

		struct
		{
			T_Stm* s;
			T_Exp* e;
		}
		eseq;

		struct
		{
			T_Exp* f;
//			cpp::CDeclaratorReference* m_pBaseDeclarator;	// libcall
			ArgList* args;
		}
		call;

		struct
		{
			Temp_label* label;
		}
		name;

		struct
		{
			T_Exp* mem;
			unsigned int size;
		}
		mem;

		struct
		{
			T_Exp* left;
			System::StringA* right;
		}
		member;

		Temp_temp** temp;
		struct
		{
			C_stmListListList* preds;
			Temp_tempList* temps;
		}
		phi;
	};
};

class CodeCompExt T_NullExp : public T_Exp
{
public:
	CTOR T_NullExp()
	{
		kind = T_NULL;
	}
};

class CodeCompExt T_ObjectExp : public T_Exp
{
public:
	CTOR T_ObjectExp(Object* _object)
	{
		kind = T_OBJECT;
		m_object = _object;
	}

	Object* m_object;
};

class CodeCompExt T_FunctionExp : public T_Exp
{
public:
	CTOR T_FunctionExp(A_IdentifierList* formals, T_StmList* body) : m_formals(formals), m_body(body)
	{
		kind = T_FUNCTION;
	}

	virtual Kind GetKind()	// TODO abstract
	{
		return T_FUNCTION;
	}

	A_IdentifierList* m_formals;
	T_StmList* m_body;
};

class CodeCompExt T_NewExp : public T_Exp
{
public:
	CTOR T_NewExp(T_Exp* f, ArgList* args)
	{
		kind = T_NEW;
		call.f = f;
		call.args = args;
	}
};

class CodeCompExt T_StringExp : public T_Exp
{
public:
	CTOR T_StringExp(StringIn str) : m_string(str)
	{
		kind = T_STRING;
	}

	String m_string;
};

class CodeCompExt T_StringWExp : public T_Exp
{
public:
	CTOR T_StringWExp(StringIn str) : m_stringw(str)
	{
		kind = T_STRINGW;
	}

	String m_stringw;
};

class CodeCompExt T_VariableExp : public T_Exp
{
public:
	CTOR T_VariableExp(StringIn str)
	{
		kind = T_VARIABLE;
		m_identifier = str;
	}

	String m_identifier;
};

class CodeCompExt T_MemberExp : public T_Exp
{
public:

	CTOR T_MemberExp(T_Exp* left, StringIn right)
	{
		kind = T_MEMBER;
		m_left = left;
		m_right = right;
	}

	T_Exp* m_left;
	String m_right;
};

class CodeCompExt T_ExpList
{
public:
	CTOR T_ExpList(T_Exp* _head, T_ExpList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	T_Exp* head;
	T_ExpList* tail;
};

/*
struct patchList
{
	patchList(Temp_label **_head,	patchList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	Temp_label **head;
	patchList* tail;
};
*/

class CodeCompExt T_Phi : public T_Exp
{
public:
	CTOR T_Phi(C_stmListListList* _preds, Temp_tempList* _temps)
	{
		kind = T_PHI;
		phi.preds = _preds;
		phi.temps = _temps;
	}
};

class PatchList
{
public:
	CTOR PatchList(T_Stm* _head,	PatchList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	T_Stm *head;
	PatchList* tail;
};

struct Cx
{
	PatchList* trues;
	PatchList* falses;
	T_Stm* stm;
//	T_Stm* cjump;
};

class CodeCompExt Tr_Exp
{
public:
	CTOR Tr_Exp()
	{
		m_pType = NULL;
	}

	enum { Tr_ex, Tr_nx, Tr_cx} kind;

	System::Type* m_pType;

	union
	{
		T_Exp* ex;
		T_Stm* nx;
		Cx cx;
	};
};

typedef vector<System::StringA*> filevectortype;

struct F_access
{
	enum {inFrame, inReg} kind;
	union
	{
		int offset;
		Temp_temp* reg;
	};
};

class T_Frame
{
public:
};

class LabelRef
{
public:
	CTOR LabelRef()
	{
		m_label = NULL;
	}

	Temp_label* m_label;
};

class T_Data
{
public:

	Temp_label* m_label;

	ubyte* m_data;
	size_t m_len;
};

class T_Declarator
{
public:
	CTOR T_Declarator()
	{
		//m_symbolIndex = 0;
		type = function;

		m_spOffset = -1;
		m_stackSize = 0;

		m_statementList = NULL;
	}

	enum
	{
		data,
		function
	}
	type;

	//int m_symbolIndex;
//	int m_spOffset;
	System::Declarator* m_pDeclarator;
//	cpp::CExpression* m_pExpr;

	T_ExpList* m_texplist;

	map<System::Declarator*, Temp_temp*> temps;
	map<System::Declarator*, T_Exp*> decls2;
	map<System::Declarator*, bool> decls;

	vector<T_Data*> m_data;

	int m_first_line;
	int m_last_line;

	Temp_label* m_tempLabel;

	Temp_label* epilogue_label;
	T_StmList* m_statementList;

	//char m_mangledName[512];
	int m_linkage;

	int m_stackSize;
	int m_spOffset;

	map<String, LabelRef*> m_labels;

	F_access* allocLocal(System::Declarator* pDeclarator)
	{
		ASSERT(0);
		return NULL;
#if 0
		if (pDeclarator->m_pType->m_bVolatile || pDeclarator->m_pType->get_sizeof() > 4)
		{
			F_access* faccess = new F_access;
			faccess->kind = F_access::inFrame;

			ASSERT(0);
#if 0
			faccess->offset = -pDeclarator->m_pType->get_sizeof() - pDeclarator->m_spOffset;
#endif
			m_stackSize += pDeclarator->m_pType->get_sizeof();

			return faccess;
		}
		else
		{
			F_access* faccess = new F_access;
			faccess->kind = F_access::inReg;
		//	faccess
			
			return faccess;
		}
#endif
	}
};

typedef map<Declarator*, T_Declarator*> t1_t;	// TODO, eventually remove

class CCodeGenerator;
class CObjectFile;

class CTLabelStatement
{
public:
	Temp_label* label;
	T_Stm* stm;
};

class CTCase : public CTLabelStatement
{
public:
	int m_value;
};

struct CTCaseList
{
	CTOR CTCaseList(CTCase* _head, CTCaseList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	CTCase* head;
	CTCaseList* tail;
};

class CTSwitch
{
public:
	CTOR CTSwitch()
	{
		tcaseList = NULL;
		default_stm = NULL;
	}

	CTCaseList* tcaseList;
	CTLabelStatement* default_stm;
};

CodeCompExt Tr_Exp* Tr_Cx(PatchList* trues, PatchList* falses, T_Stm* stm);//,  T_Stm* cjump = NULL);
CodeCompExt Tr_Exp* Tr_Ex(T_Exp* ex, System::Type* pType = NULL);
CodeCompExt Tr_Exp* Tr_Nx(T_Stm* nx);
CodeCompExt T_Exp* unEx(Tr_Exp* e);
CodeCompExt T_Stm* unNx(Tr_Exp* e);
CodeCompExt T_Stm* T_LSym(T_Declarator* declarator);
CodeCompExt T_Stm* T_ExpStm(T_Exp* e);
CodeCompExt T_Stm* T_LBrac();
CodeCompExt T_Stm* T_RBrac();
CodeCompExt T_Stm* T_Seq(T_Stm* s1, T_Stm* s2);
CodeCompExt T_Stm* T_Label(Temp_label* label, int line = -1);

CodeCompExt T_Stm* T_MoveStm(T_Exp* e1, T_Exp* e2);
CodeCompExt T_Stm* T_CJumpStm(int relop, T_Exp* left, T_Exp* right, Temp_label* t, Temp_label* f);
CodeCompExt T_Stm* T_JumpStm(T_Exp* exp, Temp_labelList* labels, int line = -1);

struct __float80__
{
	uint8 b[10];
};

CodeCompExt T_Exp* T_ESeq(T_Stm* s, T_Exp* e);
CodeCompExt T_Exp* T_BinopExp(int op, T_Exp* e1, T_Exp* e2);
CodeCompExt T_Exp* T_UnopExp(int op, T_Exp* e);
CodeCompExt T_Exp* T_ConstBoolExp(bool value);
CodeCompExt T_Exp* T_ConstExp(int32 value);
CodeCompExt T_Exp* T_Const64Exp(int64 value);
CodeCompExt T_Exp* T_ConstFloatExp(float value);
CodeCompExt T_Exp* T_ConstDoubleExp(double value);
CodeCompExt T_Exp* T_ConstLongDoubleExp(__float80__ value);
CodeCompExt T_Exp* T_Mem(T_Exp* e, unsigned int size);
CodeCompExt T_Exp* T_Temp(Temp_temp** temp);
CodeCompExt T_Exp* T_Name(Temp_label* label);
CodeCompExt T_Exp* T_Call(T_Exp* f, ArgList* args = NULL);
CodeCompExt T_Exp* T_AddressOf(T_Exp* e);

CodeCompExt struct Cx unCx(Tr_Exp* e);
CodeCompExt void PatchTrue(PatchList* tList, Temp_label* label);
CodeCompExt void PatchFalse(PatchList* tList, Temp_label* label);

//Tr_Exp* /*CCompileFile::*/ConvertExpressionType(Tr_Exp* pExpr, const Type* p2Type, bool b2Const = false);

CodeCompExt T_Stm* seq(T_Stm* x, T_Stm* y);
CodeCompExt T_Stm* do_stm(T_Stm* stm);
CodeCompExt T_StmList* linear(T_Stm* stm, T_StmList* right);
CodeCompExt T_StmList* linearize(T_Stm* stm);

C_block C_basicBlocks(T_StmList* stmList, Temp_label* label);

T_StmList* C_traceSchedule(C_block block);

class ICompileCallbacks
{
public:
	virtual void OnNamedType(System::NamedType* pType) = 0;
};

}	// System

#endif // __TRANSLATE_H_
