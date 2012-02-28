#include "stdafx.h"

#include "CodeComp/ir.h"

#include "ecmascript_ast.h"

#include "ActionScript.h"

namespace System
{
namespace ecma
{
struct yy_buffer_state;
yy_buffer_state* ecmascript_scan_string(const char* str);
#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/CodeComp.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/CodeComp.lib")
#endif

using namespace ActionScripting;

int ecmascriptparse();

extern A_ElemList* g_program;

/*
class PoolString
{
public:
	PoolString(StringA* str)
	{
		m_str = str;
		m_strw = NULL;
	}
	StringA* m_str;
	StringW* m_strw;
};
*/

//ActionScript::ActionContext* as_context;

//using namespace cpp;

#if 0
class T_Exp;
class Temp_label;

class T_Stm
{
public:
	T_Stm()
	{
//		kind = 0;
		seq.left = NULL;
		seq.right = NULL;
	}

	enum
	{
		T_LBRAC = 1,
		T_RBRAC,
		T_LSYM,
		T_LABEL,

		T_EXPR = 64,
		T_SEQ,
		T_JUMP,
		T_CJUMP,
		T_MOVE,
		T_ZERO,
	}
	kind;

	int m_line_pos;

	union
	{
		CDeclarator* declarator;

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
		}
		jump;

		struct
		{
			int m_spOffset;
			int m_length;
		}
		zero;

		T_Exp* expr;

		Temp_label* label;
	};
};

class T_Exp
{
public:
	T_Exp()
	{
		binop.left = NULL;
		binop.right = NULL;
//		call.m_pBaseDeclarator = NULL;	// libcall

#if 0
		m_pDeclaratorRef = NULL;
#endif
	}

#define T_IMMEDIATE	64

	enum
	{
		T_MEM = 1,
		T_BINOP = 2,
		T_UNOP = 3,
		T_TEMP = 4,
		T_ESEQ = 5,
		T_CALL = 6,
		T_CONST = 7 | T_IMMEDIATE,
		T_NAME = 8 | T_IMMEDIATE,

		//
		T_MEMBER
	}
	kind;

#if 0
	CDeclaratorReference* m_pDeclaratorRef;	// Used if tok ident
#endif

//	long m_spOffset;

	union
	{
		struct
		{
			long int32;
#if 0
			//FRelocation* reloc;
			RelocConst* reloc;//CDeclarator* pDeclarator;
#endif
		}
		const_int;

		struct
		{
			int op;
			T_Exp* expr;
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

#if 0
		struct
		{
			T_Exp* f;
//			CDeclaratorReference* m_pBaseDeclarator;	// libcall
			ExpList* args;
		}
		call;
#endif

		struct
		{
			Temp_label* label;
		}
		name;

		struct
		{
			T_Exp* mem;
			int size;
		}
		mem;

#if 0
		Temp_temp* temp;
#endif
	};
};

struct T_stmList
{
	T_stmList()
	{
	}

	T_stmList(T_Stm* _head, T_stmList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	T_Stm* head;
	T_stmList* tail;
};

#endif

// munch

void push_string(StringA* str, vector<as_instr*>& instrs, ActionContext* as_context, map<String, uint16>& pool)
{
	map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(str);
	if (it == pool.end())
	{
		it = pool.insert(map<String, uint16>::value_type(str, as_context->m_constantPool.size())).first;
		as_context->m_constantPool.push_back(ActionScripting::StkElt(str));
	}
	uint16 index = (*it).second;

	as_instr* p = new as_instr;
	p->data.push_back(0x96);	// push
	//if (ActionCode >= 0x80)
	{
		uint16 length = 1 + 2;
		p->data.push_back(length & 0xFF);
		p->data.push_back(length >> 8);
	}

	p->data.push_back(9);	// string
	p->data.push_back(index & 0xFF);
	p->data.push_back(index >> 8);
	instrs.push_back(p);
}

void munchStm(T_Stm* s, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16> & pool);

void munchExp(T_Exp* e, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16> & pool)
{
	switch (e->kind)
	{
	case T_Exp::T_ESEQ:
		{
			munchStm(e->eseq.s, instrs, as_context, pool);
			munchExp(e->eseq.e, instrs, as_context, pool);
		}
		break;

	case T_Exp::T_NULL:
		{
			as_instr* p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}

			p->data.push_back(2);	// null

			instrs.push_back(p);
		}
		break;

	case T_Exp::T_CONST:
		{
			TRACE("Push %d\n", e->const_int.int32);

			as_instr* p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1 + 4;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}

			p->data.push_back(7);	// int32
			p->data.push_back(e->const_int.int32 & 0xFF);
			p->data.push_back((e->const_int.int32>>8) & 0xFF);
			p->data.push_back((e->const_int.int32>>16) & 0xFF);
			p->data.push_back((e->const_int.int32>>24) & 0xFF);

			instrs.push_back(p);
		}
		break;

	case T_Exp::T_STRING:
		{
			push_string(e->string, instrs, as_context, pool);
			/*
			map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(e->string);
			if (it == pool.end())
			{
				it = pool.insert(map<StringA*, uint16, Ref_Less<StringA> >::value_type(e->string, as_context->m_constantPool.size())).first;
				as_context->m_constantPool.push_back(ActionScript::StkElt(*e->identifier));
			}

			uint16 index = (*it).second;

			as_instr* p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1 + 2;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}

			p->data.push_back(16);	// string
			p->data.push_back(index & 0xFF);
			p->data.push_back(index >> 8);
			instrs.push_back(p);
			*/
		}
		break;

	case T_Exp::T_BINOP:
		{
			munchExp(e->binop.left, instrs, as_context, pool);
			munchExp(e->binop.right, instrs, as_context, pool);

			switch (e->binop.op)
			{
			case '<':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x48);	// ActionLess2
					instrs.push_back(p);
				}
				break;

			case '>':
				{
					as_instr* p = new as_instr;
					p->data.push_back(0x67);	// ActionGreater
					instrs.push_back(p);
				}
				break;

			case '+':
				{
					as_instr* p = new as_instr;
				//	p->data.push_back(0x0A);	// ActionAdd
					p->data.push_back(0x47);	// ActionAdd2
					instrs.push_back(p);
				}
				break;

				/*
			case '-':
				{
					TRACE("Subtract\n");
				}
				break;

			case '*':
				{
					TRACE("Multiply\n");
				}
				break;

			case '/':
				{
					TRACE("Divide\n");
				}
				break;
				*/

			default:
				ASSERT(0);
			}
		}
		break;

	case T_Exp::T_MEM:
		{
			if (e->mem.mem->kind == T_Exp::T_MEMBER)
			{
				TRACE("GetMember\n");

				munchExp(e->mem.mem->member.left, instrs, as_context, pool);
				push_string(e->mem.mem->member.right, instrs, as_context, pool);

				{
					as_instr* p = new as_instr;
					p->data.push_back(0x4E);	// GetMember
					instrs.push_back(p);
				}
			}
			else if (e->mem.mem->kind == T_Exp::T_VARIABLE)
			{
			//	TRACE("Push '%s'\n", e->mem.mem->identifier);
			//	TRACE("GetVariable\n");
				as_instr* p;
				
				push_string(e->mem.mem->string, instrs, as_context, pool);
				/*
				{
					map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(e->mem.mem->string);
					if (it == pool.end())
					{
						it = pool.insert(map<StringA*, uint16, Ref_Less<StringA> >::value_type(e->string, as_context->m_constantPool.size())).first;
						as_context->m_constantPool.push_back(ActionScript::StkElt(*e->identifier));
					}

					uint16 index = (*it).second;

					p = new as_instr;
					p->data.push_back(0x96);	// push
					//if (ActionCode >= 0x80)
					{
						uint16 length = 1 + 2;
						p->data.push_back(length & 0xFF);
						p->data.push_back(length >> 8);
					}

					p->data.push_back(9);	// string
					p->data.push_back(index & 0xFF);
					p->data.push_back(index >> 8);
					instrs.push_back(p);
				}
				*/

				{
					p = new as_instr;
					p->data.push_back(0x1C);	// GetVariable
					instrs.push_back(p);
				}
			}
			else
				ASSERT(0);
		}
		break;

	case T_Exp::T_CALL:
		{
		//	munchExp(e->call.left->mem.mem->var);

			as_instr* p;

			int numArgs = 0;
			ArgList* args = e->call.args;
			while (args)
			{
				munchExp(args->head, instrs, as_context, pool);

				numArgs++;
				args = args->tail;
			}

			p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1 + 2;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}
			p->data.push_back(7);	// int32
			p->data.push_back(numArgs & 0xFF);
			p->data.push_back((numArgs >> 8) & 0xFF);
			p->data.push_back((numArgs >> 16) & 0xFF);
			p->data.push_back((numArgs >> 24) & 0xFF);
			instrs.push_back(p);

			if (e->call.f->mem.mem->kind == T_Exp::T_MEMBER)
			{
				// push object
				munchExp(e->call.f->mem.mem->member.left, instrs, as_context, pool);

				// push method name
				push_string(e->call.f->mem.mem->member.right, instrs, as_context, pool);
				/*
				//
				StringA* str = e->call.f->mem.mem->member.right;
				map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(str);
				if (it == pool.end())
				{
					it = pool.insert(map<StringA*, uint16, Ref_Less<StringA> >::value_type(str, as_context->m_constantPool.size())).first;
					as_context->m_constantPool.push_back(ActionScript::StkElt(*str));
				}

				uint16 name = (*it).second;

				//uint16 name = pool[e->call.f->mem.mem->member.right];
				p = new as_instr;
				p->data.push_back(0x96);	// push
				//if (ActionCode >= 0x80)
				{
					uint16 length = 1 + 2;
					p->data.push_back(length & 0xFF);
					p->data.push_back(length >> 8);
				}
				p->data.push_back(9);	// string
				p->data.push_back(name & 0xFF);
				p->data.push_back(name >> 8);
				instrs.push_back(p);
				*/

				p = new as_instr;
				p->data.push_back(0x52);	// ActionCallMethod
				instrs.push_back(p);
			}
			else
			{
				/*
				uint16 name = pool[e->call.f->mem.mem->string];
				p = new as_instr;
				p->data.push_back(0x96);	// push
				//if (ActionCode >= 0x80)
				{
					uint16 length = 1 + 2;
					p->data.push_back(length & 0xFF);
					p->data.push_back(length >> 8);
				}
				p->data.push_back(16);	// string
				p->data.push_back(name & 0xFF);
				p->data.push_back(name >> 8);
				instrs.push_back(p);
				*/
				push_string(e->call.f->mem.mem->string, instrs, as_context, pool);

				p = new as_instr;
				p->data.push_back(0x3D);	// ActionCallFunction
				instrs.push_back(p);
			}
		}
		break;

	case T_Exp::T_NEW:
		{
		//	munchExp(e->call.left->mem.mem->var);

			as_instr* p;

			int numArgs = 0;
			ArgList* args = e->call.args;
			while (args)
			{
				munchExp(args->head, instrs, as_context, pool);

				numArgs++;
				args = args->tail;
			}

			p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1 + 2;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}
			p->data.push_back(7);	// int32
			p->data.push_back(numArgs & 0xFF);
			p->data.push_back((numArgs >> 8) & 0xFF);
			p->data.push_back((numArgs >> 16) & 0xFF);
			p->data.push_back((numArgs >> 24) & 0xFF);
			instrs.push_back(p);

			ASSERT(e->call.f->mem.mem->kind == T_Exp::T_VARIABLE);

			push_string(e->call.f->mem.mem->string, instrs, as_context, pool);

			p = new as_instr;
			p->data.push_back(0x40);	// ActionNewObject
			instrs.push_back(p);

#if 0
			if (e->call.f->mem.mem->kind == T_Exp::T_MEMBER)
			{
				// push object
				munchExp(e->call.f->mem.mem->member.left, instrs, as_context);

				// push method name
				push_string(e->call.f->mem.mem->member.right, instrs, as_context);
				/*
				//
				StringA* str = e->call.f->mem.mem->member.right;
				map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(str);
				if (it == pool.end())
				{
					it = pool.insert(map<StringA*, uint16, Ref_Less<StringA> >::value_type(str, as_context->m_constantPool.size())).first;
					as_context->m_constantPool.push_back(ActionScript::StkElt(*str));
				}

				uint16 name = (*it).second;

				//uint16 name = pool[e->call.f->mem.mem->member.right];
				p = new as_instr;
				p->data.push_back(0x96);	// push
				//if (ActionCode >= 0x80)
				{
					uint16 length = 1 + 2;
					p->data.push_back(length & 0xFF);
					p->data.push_back(length >> 8);
				}
				p->data.push_back(9);	// string
				p->data.push_back(name & 0xFF);
				p->data.push_back(name >> 8);
				instrs.push_back(p);
				*/

				p = new as_instr;
				p->data.push_back(0x52);	// ActionCallMethod
				instrs.push_back(p);
			}
			else
			{
				/*
				uint16 name = pool[e->call.f->mem.mem->string];
				p = new as_instr;
				p->data.push_back(0x96);	// push
				//if (ActionCode >= 0x80)
				{
					uint16 length = 1 + 2;
					p->data.push_back(length & 0xFF);
					p->data.push_back(length >> 8);
				}
				p->data.push_back(16);	// string
				p->data.push_back(name & 0xFF);
				p->data.push_back(name >> 8);
				instrs.push_back(p);
				*/
				push_string(e->call.f->mem.mem->string, instrs, as_context);

				p = new as_instr;
				p->data.push_back(0x3D);	// ActionCallFunction
				instrs.push_back(p);
			}
#endif
		}
		break;

	default:
		ASSERT(0);
	}
}

//ActionContext* as_context;

void munch(T_StmList* stms, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16> & pool);

template<class list_t> size_t Count(list_t* listp)
{
	size_t count = 0;

	while (listp)
	{
		count++;
		listp = listp->tail;
	}

	return count;
}

void munchStm(T_Stm* s, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16> & pool)
{
	switch (s->kind)
	{
	case T_Stm::T_FUN:
		{
			as_instr* p;

			p = new as_instr;
			p->data.push_back(0x9B);	// DefineFunction
			//if (ActionCode >= 0x80)
			{
				p->data.push_back(0);
				p->data.push_back(0);
			}
			ULONG length = 0;
			{
				for (int i = 0; i < s->fun.m_name->Length(); i++)
				{
					p->data.push_back(s->fun.m_name->c_str()[i]);
				}
			}
			p->data.push_back(0);
			length += s->fun.m_name->Length() + 1;

			uint16 numParams = Count(s->fun.m_formals);
			p->data.push_back(numParams & 0xFF);
			p->data.push_back(numParams >> 8);
			length += 2;
			{
				A_IdentifierList* formals = s->fun.m_formals;
				while (formals)
				{
					for (int i = 0; i < formals->head->Length(); i++)
					{
						p->data.push_back(formals->head->c_str()[i]);
					}
					p->data.push_back(0);

					formals = formals->tail;
				}
			}

			vector<as_instr*> body;

			munch(s->fun.m_body, body, as_context, pool);

			ULONG codelength = 0;
			{
				for (int i = 0; i < body.size(); i++)
				{
					codelength += body[i]->data.size();
				}
			}
			length += codelength;

			p->data.push_back(codelength & 0xFF);
			p->data.push_back(codelength >> 8);
			length += 2;

			if (length >= 65536)
			{
				ASSERT(0);
				THROW(-1);
			}


			{
				for (int i = 0; i < body.size(); i++)
				{
					for (int j = 0; j < body[i]->data.size(); j++)
						p->data.push_back(body[i]->data[j]);
				}
			}

			p->data[1] = length & 0xFF;
			p->data[2] = length>>8;

			instrs.push_back(p);
		}
		break;

	case T_Stm::T_VAR:
		{
			as_instr* p;

			p = new as_instr;
			p->data.push_back(0x96);	// push
			//if (ActionCode >= 0x80)
			{
				uint16 length = 1 + 2;
				p->data.push_back(length & 0xFF);
				p->data.push_back(length >> 8);
			}
			p->data.push_back(9/*16*/);	// constant
			p->data.push_back(s->var.name & 0xFF);
			p->data.push_back(s->var.name >> 8);
			instrs.push_back(p);

			p = new as_instr;
			p->data.push_back(0x41);	// DefineLocal2
			instrs.push_back(p);
		}
		break;

	case T_Stm::T_MOVE:
		{
			T_Exp* dst = s->move.left;
			T_Exp* src = s->move.right;

			if (dst->kind == T_Exp::T_MEM)
			{
				if (dst->mem.mem->kind == T_Exp::T_VARIABLE)
				{
				//	TRACE("Push '%s'\n", dst->mem.mem->identifier);

					as_instr* p;

					/*
					p = new as_instr;
					p->data.push_back(0x96);	// push
					//if (ActionCode >= 0x80)
					{
						uint16 length = 1 + 2;
						p->data.push_back(length & 0xFF);
						p->data.push_back(length >> 8);
					}

					p->data.push_back(16);	// string

					uint16 index = pool[dst->mem.mem->string];
					p->data.push_back(index & 0xFF);
					p->data.push_back(index >> 8);
					instrs.push_back(p);
					*/
					push_string(dst->mem.mem->string, instrs, as_context, pool);

				//	TRACE("Push\n");
				//	TRACE("Push\n");

					munchExp(src, instrs, as_context, pool);

					p = new as_instr;
					p->data.push_back(0x1D);	// SetVariable
					instrs.push_back(p);

					TRACE("SetVariable\n");
				}
				else if (dst->mem.mem->kind == T_Exp::T_MEMBER)
				{
					as_instr* p;

					// object
					munchExp(dst->mem.mem->member.left, instrs, as_context, pool);

					// property name
					push_string(dst->mem.mem->member.right, instrs, as_context, pool);

					// value
					munchExp(src, instrs, as_context, pool);

					p = new as_instr;
					p->data.push_back(0x4F);	// SetMember
					instrs.push_back(p);

					TRACE("SetMember\n");
				}
				else
					ASSERT(0);
			}
			else
				ASSERT(0);
		}
		break;

	case T_Stm::T_EXP:
		{
			munchExp(s->exp, instrs, as_context, pool);
		}
		break;

	default:
		ASSERT(0);
	}
}

void munch(T_StmList* stms, vector<as_instr*> & instrs, ActionContext* as_context, map<String, uint16> & pool)
{
	T_StmList* tail = stms;
	while (tail)
	{
		munchStm(tail->head, instrs, as_context, pool);

		tail = tail->tail;
	}
}

// translate

T_Exp* T_Variable(StringA* identifier)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_VARIABLE;
	p->identifier = identifier;
	return p;
}

T_Exp* T_Member(T_Exp* left, StringA* right)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_MEMBER;
	p->member.left = left;
	p->member.right = right;
	return p;
}

T_NullExp* Null = new T_NullExp;

Tr_Exp* TransExpression(A_Exp* exp, ActionContext* as_context)
{
	/*
	if (exp->kind == A_Exp::A_THIS)
	{
		Tr_Exp* pTExpr = Tr_Ex(T_Const(exp->int32));
	//	pTExpr->m_pType = new PrimitiveType(type_int);
		return pTExpr;
	}
	else
	*/
	if (exp->kind == A_Exp::A_ID)
	{
		StringA* str = (new StringA(string_copy(exp->id)));//->ToStringW();
		/*
		map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(str);
		if (it == pool.end())
		{
			it = pool.insert(map<StringA*, uint16, Ref_Less<StringA> >::value_type(str, as_context->m_constantPool.size())).first;
			as_context->m_constantPool.push_back(ActionScript::StkElt(*str));
		}
		*/

		return Tr_Ex(T_Mem(T_Variable(str), -1));
	}
	else if (exp->kind == A_Exp::A_INT32)
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(exp->int32));
	//	pTExpr->m_pType = new PrimitiveType(type_int);
		return pTExpr;
	}
	else if (exp->kind == A_Exp::A_BOOL)
	{
		Tr_Exp* pTExpr = Tr_Ex(T_ConstExp(exp->boolValue));
	//	pTExpr->m_pType = new PrimitiveType(type_bool);
		return pTExpr;
	}
	else if (exp->kind == A_Exp::A_NULL)
	{
		Tr_Exp* pTExpr = Tr_Ex(Null);
	//	pTExpr->m_pType = new PrimitiveType(type_int);
		return pTExpr;
	}
	else if (exp->kind == A_Exp::A_STRING)
	{
		Tr_Exp* pTExpr = Tr_Ex(new T_StringExp(exp->string));
	//	pTExpr->m_pType = new PrimitiveType(type_int);
		return pTExpr;
	}
	else if (exp->kind == A_Exp::A_STRINGW)
	{
		Tr_Exp* pTExpr = Tr_Ex(new T_StringWExp(exp->stringw));
	//	pTExpr->m_pType = new PrimitiveType(type_int);
		return pTExpr;
	}
	else if (exp->kind == A_Exp::A_MEMBER)
	{
		Tr_Exp* tleft = TransExpression(exp->member.left, as_context);
		if (tleft == NULL)
			return NULL;

		T_Exp* left = unEx(tleft);
		
//		ASSERT(left->kind == T_Exp::T_MEM);
//		left = left->mem.mem;

	//	T_Exp* setMember = new T_Exp;
	//	setMember->kind ) 
		Tr_Exp* tr;

		/*
		tr = Tr_Ex(
			T_Mem(
			T_Binop('+', left, T_Const(pRightDeclarator->m_offset)), pRightDeclarator->m_pType->GetType()->get_sizeof()));
			*/
//		ASSERT(0);
		return Tr_Ex(T_Mem(T_Member(left, exp->member.right), -1));

		return tr;
	}
	else if (exp->kind == A_Exp::A_NEW)
	{
		Tr_Exp* tleft = TransExpression(exp->call.left, as_context);
		if (tleft == NULL)
			return NULL;

		ArgList* targs = NULL;

		A_ExpList* args = exp->call.args;
		while (args)
		{
			Tr_Exp* tr = TransExpression(args->head, as_context);

			targs = new ArgList(unEx(tr), targs);

			args = args->tail;
		}

		T_Exp* left = unEx(tleft);

		return Tr_Ex(new T_NewExp(left, targs));
	}
	else if (exp->kind == A_Exp::A_CALL)
	{
		Tr_Exp* tleft = TransExpression(exp->call.left, as_context);
		if (tleft == NULL)
			return NULL;

		ArgList* targs = NULL;

		A_ExpList* args = exp->call.args;
		while (args)
		{
			Tr_Exp* tr = TransExpression(args->head, as_context);

			targs = new ArgList(unEx(tr), targs);

			args = args->tail;
		}

		T_Exp* left = unEx(tleft);

		/*
		if (exp->call.left->kind == A_MEMBER)
		{

		}
		else
		*/
		{
			return Tr_Ex(T_Call(left, targs));
		}
	}
	else if (exp->kind == A_Exp::A_UNOP)
	{
		switch (exp->unop.op)
		{
		case 'type':
			{
				ASSERT(0);
			}
			break;

		default:
			ASSERT(0);
		}
	}
	else if (exp->kind == A_Exp::A_BINOP)
	{
		switch (exp->binop.op)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '|':
		case '&':
		case '^':
		case '>':
		case '>=':
		case '<':
		case '<=':
			{
				Tr_Exp* left = TransExpression(/*frame, */exp->binop.left/*, pGlobal, pScope*/, as_context);
				Tr_Exp* right = TransExpression(/*frame, */exp->binop.right/*, pGlobal, pScope*/, as_context);

			//	if (left->m_pType && right->m_pType)
				{
					Tr_Exp* tr = Tr_Ex(T_BinopExp(exp->binop.op, unEx(left), unEx(right)));

					return tr;
				}

				return NULL;
			}
			break;

		case '=':
			{
				Tr_Exp* left = TransExpression(/*frame,*/ exp->binop.left, as_context);//, pGlobal, pScope);
				if (left == NULL)
				{
					return NULL;
				}
				else
				{
					Tr_Exp* right = TransExpression(/*frame,*/ exp->binop.right, as_context);//, pGlobal, pScope);

					if (right == NULL)
					{
						return NULL;
					}
					else
					{
					//	Tr_Exp* p = Tr_Ex(T_ESeq(T_MoveStm(left->ex, unEx(right)), left->ex));
						Tr_Exp* p = Tr_Nx(T_MoveStm(left->ex, unEx(right)));
					//	p->m_pType = left->m_pType;
						return p;
					}
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
	else
		ASSERT(0);

	return NULL;
}

T_Stm* TransStatement(A_Stm* stm, ActionContext* as_context, map<StringA*, uint16, Ref_Less<StringA> > & pool)
{
	switch (stm->GetKind())
	{
		/*
	case A_Stm::A_FUN:
		{
		}
		break;
		*/

	case A_Stm::A_VAR:
		{
			T_Stm* tstm = NULL;

			A_VarStm* varstm = (A_VarStm*)stm;
			A_VarDeclList* vardecls = varstm->m_vardecls;
			while (vardecls)
			{
				StringA* str = vardecls->head->m_identifier;
				map<StringA*, uint16, Ref_Less<StringA> >::iterator it = pool.find(str);
				if (it == pool.end())
				{
					it = pool.insert(map<StringA*, uint16, Ref_Less<StringA> >::value_type(str, as_context->m_constantPool.size())).first;
					as_context->m_constantPool.push_back(ActionScripting::StkElt(str));
				}

				uint16 name = (*it).second;

				T_Stm* tstm2 = new T_Stm;
				tstm2->kind = T_Stm::T_VAR;
				tstm2->var.name = name;

				if (tstm)
					tstm = T_Seq(tstm, tstm2);
				else
					tstm = tstm2;

				vardecls = vardecls->tail;
			}

			return tstm;
		}
		break;

	case A_Stm::A_EXP:
		{
			A_ExpStm* expstm = (A_ExpStm*)stm;

			Tr_Exp* tr = TransExpression(/*frame,*/ expstm->m_exp/*, pGlobal, pScope*/, as_context);
			
			if (tr == NULL)
				return NULL;
			
			T_Stm* t = unNx(tr);
			//	t->m_line_pos = stm->exp->line_pos;
			
			return t;
		}
		break;
		
	case A_Stm::A_IF:
		{
#if 0
			A_IfStm* ifstm = (A_IfStm*)stm;

			Tr_Exp* tr = TransExpression(/*frame,*/ stm->IF.cond/*, pGlobal, pScope*/, as_context);

			if (tr == NULL)
				return NULL;
#endif
			ASSERT(0);
			return NULL;
		}
		break;

	case A_Stm::A_FOR:
		{
			A_ForStm* forstm = (A_ForStm*)stm;

			Tr_Exp* for_init = TransExpression(/*frame,*/ forstm->m_init/*, pGlobal, pScope*/, as_context);
			Tr_Exp* for_cond = TransExpression(/*frame,*/ forstm->m_cond/*, pGlobal, pScope*/, as_context);
			Tr_Exp* for_exp = TransExpression(/*frame,*/ forstm->m_exp/*, pGlobal, pScope*/, as_context);

			Cx cx = unCx(for_cond);

			Temp_label* top = new Temp_label;
			Temp_label* contlabel = new Temp_label;
			Temp_label* t = new Temp_label;
			Temp_label* f = new Temp_label;

			PatchTrue(cx.trues, t);
			PatchFalse(cx.falses, f);

			T_Stm* for_stm = TransStatement(forstm->m_stm, as_context, pool);

			T_Stm* ts = T_Seq(unNx(for_init),
								T_Seq(T_Label(top),
									T_Seq(cx.stm,
										T_Seq(T_Label(t),
											T_Seq(for_stm,
												T_Seq(T_Label(contlabel),
													T_Seq(unNx(for_exp),
														T_Seq(T_JumpStm(T_Name(top), new Temp_labelList(top, NULL)),
															T_Label(f, forstm->m_last_line)))))))));

			/*
			return T_Seq(unEx(tr_init),
							T_Seq(top_label,
								T_Seq(for_stm,
									T_ESeq(for_exp,
										T_Seq(
											
											T_Jump(begin_label),
												f)))));
												*/

			return ts;
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

T_StmList* translate(A_ElemList* elems, ActionContext* as_context, map<String, uint16> & pool)
{
	T_StmList* slist = NULL;

	A_ElemList* tail = elems;
	while (tail)
	{
		if (tail->head->kind == A_Elem::A_FUNCTION)
		{
			T_Stm* stm = new T_Stm;
			stm->kind = T_Stm::T_FUN;
			stm->fun.m_name = tail->head->fun->m_id;
			stm->fun.m_formals = tail->head->fun->m_formals;
			stm->fun.m_body = translate(tail->head->fun->m_body, as_context, pool);

			slist = new T_StmList(stm, slist);
		}
		else
		{
			slist = new T_StmList(TransStatement(tail->head->stm, as_context, pool), slist);
		}

		tail = tail->tail;
	}

	return slist;
}

}
}
