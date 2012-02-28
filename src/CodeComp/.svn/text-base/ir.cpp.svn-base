#include "stdafx.h"
//#include "a_tree.h"
#include "ir.h"

namespace System
{
using namespace std;

int Temp_temp::count = 0;

//CExpression* Reduce2(CExpression* pExpr, Scope* pScope);

//_Type* GetType(A_DeclSpecList* declspecList, CGlobal* pGlobal, Scope* pScope);

Temp_temp::Temp_temp()
{
//	int count = 0;

	name = new char[32];
	sprintf_s(name, 32, "t%d", count);
	m_n = -1;//count;
	m_a = 0;

	m_second = NULL;
	m_aux = NULL;

	m_dn = 0;
	m_an = 0;

	m_precolored = false;
	count++;

	m_size = 4;

//	m_refcount = 0;

	m_exp = NULL;

	m_alias = NULL;
}

Temp_temp::Temp_temp(const char* _name, int n)
{
	m_precolored = true;
	name = _strdup(_name);
	m_n = n;

	m_a = 0;

	m_second = NULL;

	m_dn = 0;
	m_an = 0;

	m_alias = NULL;

	m_size = 4;
}

Temp_label::Temp_label()
{
	m_n = 0;//count;

//	count++;

//	m_pos = -1;
	m_spOffset = -1;
	m_symbolIndex = 0;
	m_defined = false;
}

T_Stm* T_Label(Temp_label* label, int line/* = -1*/)
{
//	printf("T_Label 0x%x\n", label);

	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_LABEL;
	p->label = label;
	p->m_line_pos = line;

	return p;
}

T_Stm* T_LSym(T_Declarator* declarator)
{
	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_LSYM;
	p->declarator = declarator;

	return p;
}

T_Exp* T_ConstBoolExp(bool value)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_CONST_BOOL;
	p->const_bool.value = value;
	p->m_size = 1;

	return p;
}

T_Exp* T_ConstExp(int32 int32val)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_CONST_INT32;
	p->const_int.int32Val = int32val;
	p->m_size = 4;

	return p;
}

T_Exp* T_Const64Exp(int64 int64val)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_CONST_INT64;
	p->const_int.int64Val = int64val;
	p->m_size = 8;

	return p;
}

T_Exp* T_ConstFloatExp(float float32val)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_CONST_FLOAT;
	p->const_float.float32 = float32val;
	p->m_size = 4;
//	p->const_int.reloc = NULL;
//	p->const_int.reloc = NULL;

	return p;
}

T_Exp* T_ConstDoubleExp(double float64val)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_CONST_DOUBLE;
	p->const_double.float64 = float64val;
	p->m_size = 8;
//	p->const_int.reloc = NULL;
//	p->const_int.reloc = NULL;

	return p;
}

T_Exp* T_Variable(char* name)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_VARIABLE;
	p->variable = name;

	return p;
}

T_Exp* T_Temp(Temp_temp** temp)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_TEMP;
	p->temp = temp;

	return p;
}

T_Exp* T_Name(Temp_label* label)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_NAME;
	p->name.label = label;

	return p;
}

T_Exp* T_Mem(T_Exp* e, unsigned int size)
{
// TODO, have this check	ASSERT(size >= 0);

//	ASSERT(size == 1 || size == 2 || size == 4);	// TODO remove

	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_MEM;
	p->mem.mem = e;
	p->mem.size = size;

	return p;
}

T_Exp* T_Call(T_Exp* f, ArgList* args)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_CALL;
	p->call.f = f;
	p->call.args = args;

	return p;
}

T_Exp* T_AddressOf(T_Exp* e)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_ADDRESSOF;
	p->addressof = e;

	return p;
}

#if 0
T_Exp* T_Addr(T_Exp* e)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_ADDR;
	p->addr = e;

	return p;
}
#endif

T_Exp* T_Exp::Clone() const
{
	switch (kind)
	{
	case T_BINOP:
		{
			T_Exp* e = T_BinopExp(binop.op, binop.left->Clone(), binop.right->Clone());
			e->m_size = m_size;
			return e;
		}
		break;

	case T_UNOP:
		{
			T_Exp* e = T_UnopExp(unop.op, unop.exp->Clone());
			e->m_size = m_size;
			return e;
		}
		break;

	case T_TEMP:
		{
			T_Exp* e = T_Temp(temp);
			e->m_size = m_size;
			return e;
		}
		break;

	case T_MEM:
		{
			T_Exp* e = T_Mem(mem.mem, mem.size);
			e->m_size = m_size;
			return e;
		}
		break;

	case T_CONST:
		{
			T_Exp* e = T_ConstExp(const_int.int32Val);
			e->m_size = m_size;
			return e;
		}
		break;

	default:
		ASSERT(0);
	}
	return NULL;
}

T_Exp* T_UnopExp(int op, T_Exp* e)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_UNOP;
	p->unop.op = op;
	p->unop.exp = e;

	return p;
}

T_Exp* T_BinopExp(int op, T_Exp* e1, T_Exp* e2)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_BINOP;
	p->binop.op = op;
	p->binop.left = e1;
	p->binop.right = e2;

	return p;
}

T_Exp* T_ESeq(T_Stm* s, T_Exp* e)
{
	T_Exp* p = new T_Exp;
	p->kind = T_Exp::T_ESEQ;
	p->eseq.s = s;
	p->eseq.e = e;

	return p;
}

T_Stm* T_MoveStm(T_Exp* e1, T_Exp* e2)
{
	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_MOVE;
	p->move.left = e1;
	p->move.right = e2;

	return p;
}

T_Stm* T_ExpStm(T_Exp* e)
{
	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_EXP;
	p->exp = e;

	return p;
}

T_Stm* T_LBrac()
{
	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_LBRAC;

	return p;
}

T_Stm* T_RBrac()
{
	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_RBRAC;

	return p;
}

T_Stm* T_Seq(T_Stm* s1, T_Stm* s2)
{
	ASSERT(s1);
	ASSERT(s2);

	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_SEQ;
	p->seq.left = s1;
	p->seq.right = s2;

	return p;
}

T_Stm* T_CJumpStm(int relop, T_Exp* left, T_Exp* right, Temp_label* t, Temp_label* f)
{
	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_CJUMP;
	p->cjump.relop = relop;
	p->cjump.left = left;
	p->cjump.right = right;
	p->cjump.t = t;
	p->cjump.f = f;

	return p;
}

T_Stm* T_JumpStm(T_Exp* exp, Temp_labelList* labels, int line)
{
	T_Stm* p = new T_Stm;
	p->kind = T_Stm::T_JUMP;
	p->jump.exp = exp;
	p->jump.labels = labels;
	p->m_line_pos = line;

	return p;
}

Tr_Exp* Tr_Ex(T_Exp* ex, Type* pType)
{
	Tr_Exp* p = new Tr_Exp;
	p->kind = Tr_Exp::Tr_ex;
	p->ex = ex;
	p->m_pType = pType;

	return p;
}

CodeCompExt Tr_Exp* Tr_Nx(T_Stm* nx)
{
	Tr_Exp* p = new Tr_Exp;
	p->kind = Tr_Exp::Tr_nx;
	p->nx = nx;

	return p;
}

Tr_Exp* Tr_Cx(PatchList* trues, PatchList* falses, T_Stm* stm)
{
	Tr_Exp* p = new Tr_Exp;
	p->kind = Tr_Exp::Tr_cx;
	p->cx.stm = stm;
	p->cx.trues = trues;
	p->cx.falses = falses;

	return p;
}

/*
void doPatch(patchList* tList, Temp_label* label)
{
	for (; tList; tList=tList->tail)
	{
		*(tList->head) = label;
	}
}
*/

void PatchTrue(PatchList* tList, Temp_label* label)
{
	for (; tList; tList=tList->tail)
	{
		tList->head->cjump.t = label;
	}
}

void PatchFalse(PatchList* tList, Temp_label* label)
{
	for (; tList; tList=tList->tail)
	{
		tList->head->cjump.f = label;
	}
}

CodeCompExt T_Exp* unEx(Tr_Exp* e)
{
	switch (e->kind)
	{
	case Tr_Exp::Tr_ex:
		return e->ex;

	case Tr_Exp::Tr_nx:
		{
			switch (e->nx->kind)
			{
			case T_Stm::T_MOVE:
				return T_ESeq(e->nx, e->nx->move.left);
			
			default:
				return T_ESeq(e->nx, T_ConstExp(0));
			}
		}
		break;

	case Tr_Exp::Tr_cx:
		{
			if (true && e->cx.stm->kind == T_Stm::T_CJUMP)
			{
				return T_BinopExp(e->cx.stm->cjump.relop, e->cx.stm->cjump.left, e->cx.stm->cjump.right);
			}
			else
			{
				Temp_temp** r = new Temp_temp*;
				Temp_label* t = new Temp_label;
				Temp_label* f = new Temp_label;

				PatchTrue(e->cx.trues, t);
				PatchFalse(e->cx.falses, f);

				return T_ESeq(T_MoveStm(T_Temp(r), T_ConstExp(0)),
							T_ESeq(e->cx.stm,
								T_ESeq(T_Label(t),
									T_ESeq(T_MoveStm(T_Temp(r), T_ConstExp(1)),
										T_ESeq(T_Label(f),
											T_Temp(r))))));
			}
		}
		break;
	}
	ASSERT(0);
	return NULL;
}

CodeCompExt T_Stm* unNx(Tr_Exp* e)
{
	ASSERT(e);

	switch (e->kind)
	{
	case Tr_Exp::Tr_nx:
		return e->nx;

	case Tr_Exp::Tr_ex:
		return T_ExpStm(e->ex);

	case Tr_Exp::Tr_cx:
		// convert the cjump statement to a sequence of statements for the left and right expression
		return T_Seq(T_ExpStm(e->cx.stm->cjump.left), T_ExpStm(e->cx.stm->cjump.right));
	}
	ASSERT(0);
	return NULL;
}

Cx unCx(Tr_Exp* e)
{
	switch (e->kind)
	{
	case Tr_Exp::Tr_ex:
		{
		//	Temp_label* t = new Temp_label;
		//	Temp_label* f = new Temp_label;

			// TODO treat CONST specially

			T_Stm* s = T_CJumpStm('!=', e->ex, T_ConstExp(0), NULL/*t*/, NULL/*f*/);
			Cx cx;
			cx.trues = new PatchList(s/*->cjump.t*/, NULL);
			cx.falses = new PatchList(s/*->cjump.f*/, NULL);
			cx.stm = s;
			return cx;

		//	return Tr_Cx(new patchList(&s->cjump.t, NULL), new patchList(&s->cjump.f, NULL), s)->cx;
			//return Tr_Cx(NULL, NULL, s)->cx;
		}
		break;

	case Tr_Exp::Tr_nx:	// Shouldn't happen
		ASSERT(0);
	}

	ASSERT(e->kind == Tr_Exp::Tr_cx);
	return e->cx;
}

/*
void te()
{
	int x = 6;
}
*/


bool isNop(T_Stm* x)
{
	return x->kind == T_Stm::T_EXP && x->exp->kind == T_Exp::T_CONST;
}

//T_Exp* CCPPCompiler::TransStatement(CStatement* pstmt)
//{
//}

struct stmExp
{
	stmExp(T_Stm* _s, T_Exp* _e)
	{
		s = _s;
		e = _e;
	}
	T_Stm* s;
	T_Exp* e;
};

bool commute(T_Stm* x, T_Exp* y)
{
	return isNop(x) || y->kind == T_Exp::T_NAME || y->kind == T_Exp::T_CONST;
}

stmExp do_exp(T_Exp* exp);

T_Stm* reorder(expRefList* rlist)
{
	if (!rlist) return T_ExpStm(T_ConstExp(0)); /* nop */

	stmExp hd = do_exp(*rlist->head);
	T_Stm* s = reorder(rlist->tail);
	if (commute(s,hd.e))
	{
		*rlist->head=hd.e;
		return seq(hd.s,s);
	}
	else
	{
		Temp_temp** t = new Temp_temp*;
		*t = new Temp_temp;

		*rlist->head = T_Temp(t);
		return seq(hd.s, seq(T_MoveStm(T_Temp(t),hd.e), s));
	}
}

#if 0
T_Stm* reorder(expRefList* rlist)
{

	T_Stm* s = NULL;//
	expRefList* re = rlist;
	while (re)
	{
		stmExp stmexp = do_exp(*re->head);

//		if (stmexp.e->kind == T_Exp::T_ESEQ)
		{
			if (s)
				s = seq(s, stmexp.s);
			else
				s = stmexp.s;

			*(re->head) = stmexp.e;
		}

		//stmexp.s
#if 0
		if ((*re->head)->kind == T_ESEQ)
		{
			T_Stm* s2 = (*re->head)->eseq.s;
			*re->head = (*re->head)->eseq.e;
			//s2->seq.right = s;
			if (s)
				s = seq(s, s2);
			else
				s = s2;
		}
#endif
		re = re->tail;
	}

	if (s == NULL)
		s = T_Expr(T_Const(0));
	return s;

	/*
	if (rlist)
	{
		if ((*rlist->head)->kind == T_ESEQ)
		{
			T_Stm* s = (*rlist->head)->eseq.s;
			*rlist->head = (*rlist->head)->eseq.e;
			return s;
		}
	}
	*/

	return T_Expr(T_Const(0));
}

#endif

expRefList* get_call_rlist(T_Exp* exp)
{
	expRefList* reflist = NULL;

	ArgList* args = exp->call.args;
	while (args)
	{
		reflist = new expRefList(&args->head, reflist);
		args = args->tail;
	}

	return reflist;
}

stmExp do_exp(T_Exp* exp)
{
	switch (exp->kind)
	{
	case T_Exp::T_BINOP:
		return stmExp(reorder(new expRefList(&exp->binop.left, new expRefList(&exp->binop.right, NULL))), exp);

	case T_Exp::T_UNOP:
		return stmExp(reorder(new expRefList(&exp->unop.exp, NULL)), exp);

	case T_Exp::T_MEM:
		return stmExp(reorder(new expRefList(&exp->mem.mem, NULL)), exp);

	case T_Exp::T_ESEQ:
		{
			struct stmExp x = do_exp(exp->eseq.e);
			return stmExp(seq(do_stm(exp->eseq.s), x.s), x.e);
		}
		break;

	case T_Exp::T_CALL:
		{
			return stmExp(reorder(get_call_rlist(exp)), exp);
		}
		break;

	default:
		return stmExp(reorder(NULL), exp);
	}
}

T_Stm* seq(T_Stm* x, T_Stm* y)
{
	ASSERT(x);
	ASSERT(y);

	if (isNop(x)) return y;
	if (isNop(y)) return x;
	return T_Seq(x, y);
}

T_Stm* do_stm(T_Stm* stm)
{
	ASSERT(stm);

	switch (stm->kind)
	{
	case T_Stm::T_SEQ:
		{
			T_Stm* s1 = do_stm(stm->seq.left);
			T_Stm* s2 = do_stm(stm->seq.right);
			return seq(s1, s2);
		}
		break;

	case T_Stm::T_CJUMP:
		{
			return seq(reorder(new expRefList(&stm->cjump.left, new expRefList(&stm->cjump.right, NULL))), stm);
		}
		break;

	case T_Stm::T_MOVE:
		{
			if (stm->move.left->kind == T_Exp::T_TEMP)
			{
				return seq(reorder(new expRefList(&stm->move.right, NULL)), stm);
			}
			else if (stm->move.left->kind == T_Exp::T_VARIABLE)
			{
				return seq(reorder(new expRefList(&stm->move.right, NULL)), stm);
			}
			else if (stm->move.left->kind == T_Exp::T_MEM)
			{
				return seq(reorder(new expRefList(&stm->move.left->mem.mem, new expRefList(&stm->move.right, NULL))), stm);
			}
			else
				ASSERT(0);
		}
		break;

	case T_Stm::T_EXP:
		{
			if (stm->exp->kind == T_Exp::T_CALL)
				return seq(reorder(get_call_rlist(stm->exp)), stm);

			return seq(reorder(new expRefList(&stm->exp, NULL)), stm);
		}
		break;

	default:
		return stm;
	}
	ASSERT(0);
	return NULL;
}

T_StmList* linear(T_Stm* stm, T_StmList* right)
{
	if (stm->kind == T_Stm::T_SEQ)
	{
		return linear(stm->seq.left, linear(stm->seq.right, right));
	}
	else
	{
		return new T_StmList(stm, right);
	}
}

T_StmList* linearize(T_Stm* stm)
{
	return linear(do_stm(stm), NULL);
}

C_block C_basicBlocks(T_StmList* stmList, Temp_label* donelabel)
{
	//printf("**************\n");

	{
		T_StmList* stm = stmList;

		while (stm)
		{
			switch (stm->head->kind)
			{
			case T_Stm::T_LABEL:
				printf("label: %x", stm->head->label);
				break;

			case T_Stm::T_JUMP:
				printf("\tjump %x", stm->head->jump.labels->head);
				break;

			case T_Stm::T_CJUMP:
				printf("\tcjump t:%x f:%x", stm->head->cjump.t, stm->head->cjump.f);
				break;

			default:
				printf("\tstm");
			}

		//	printf("\n");

			stm = stm->tail;
		}
	}

//	printf("**************\n");

	C_block block;
//	block.label = new Temp_label;

//	block.stmLists = new C_stmListList(stmList, NULL);;

	C_stmListListList* curblock = NULL;
	C_stmListListList* prevblock = NULL;

	T_StmList* curstm = stmList;
	T_StmList* prevstm = NULL;
	while (curstm)
	{
		T_StmList* nextstm = curstm->tail;

		if (curstm->head->kind == T_Stm::T_LABEL)
		{
			if (prevstm)	// end previous block
			{
				prevstm->tail = NULL;
			}

			curblock = new C_stmListListList(new C_stmListList(curstm), prevblock);	// begin new block

			curstm->head->m_block = curblock->head;

			block.labels[curstm->head->label] = curblock->head;

			prevblock = curblock;
		}
		else if (curstm->head->kind == T_Stm::T_JUMP ||
					curstm->head->kind == T_Stm::T_CJUMP)
		{
			//curblock = new C_stmListList(curstm->tail, curblock);	// begin new block
			if (curblock == NULL)
				curblock = new C_stmListListList(new C_stmListList(curstm), prevblock);

			curstm->head->m_block = curblock->head;

	// end this block
			curstm->tail = NULL;

			// begin new block
			prevblock = curblock;
			curblock = NULL;//new C_stmListList(curstm, curblock);
		}
		else
		{
			if (curblock == NULL)
				curblock = new C_stmListListList(new C_stmListList(curstm), prevblock);

			curstm->head->m_block = curblock->head;

			prevblock = curblock;
		}

		prevstm = curstm;
		curstm = nextstm;
	}

	if (curblock == NULL)
		curblock = new C_stmListListList(new C_stmListList(prevstm), prevblock);

//	block.stmLists = new CstmList

	block.stmLists = curblock;

//	block.stmLists = new C_stmListList(new T_StmList(T_Label(donelabel), NULL), block.stmLists);

	// In reverse order

	if (true)
	{
		curblock = block.stmLists;

		T_StmList* prevblock = NULL;//curblock->head;
		//curblock = curblock->tail;

		while (curblock)
		{
			T_StmList* stm = curblock->head->head;

			if (stm->head->kind != T_Stm::T_LABEL)
			{
				curblock->head->head = new T_StmList(T_Label(new Temp_label()), curblock->head->head);

				curblock->head->head->head->m_block = curblock->head;

				ASSERT(curblock->head->head->head->kind == T_Stm::T_LABEL);
				block.labels[curblock->head->head->head->label] = curblock->head;
			}

			while (stm->tail)
			{
				stm = stm->tail;
			}

		// if the block doesn't end in a jump, append a jump pointing to the beginning of this block
			if (stm->head->kind != T_Stm::T_JUMP &&
				stm->head->kind != T_Stm::T_CJUMP)
			{
				if (prevblock)
				//if (curblock->tail)
				{
					ASSERT(curblock->head->head->head->kind == T_Stm::T_LABEL);
					stm->tail = new T_StmList(T_JumpStm(T_Name(prevblock->head->label), new Temp_labelList(prevblock->head->label, NULL)), NULL);
				}
				else
				{
					stm->tail = new T_StmList(T_JumpStm(T_Name(donelabel), new Temp_labelList(donelabel, NULL)), NULL);
				}

				stm->tail->head->m_block = curblock->head;
			}

			prevblock = curblock->head->head;
			curblock = curblock->tail;
		}
	}


//	block.stmLists = Reverse(block.stmLists);

	{
		printf("**************************\n");

		printf("label: %x\n\n", donelabel);

		curblock = block.stmLists;

		while (curblock)
		{
			T_StmList* stm = curblock->head->head;

			while (stm)
			{
				switch (stm->head->kind)
				{
				case T_Stm::T_LABEL:
					printf("label: %x", stm->head->label);
					break;

				case T_Stm::T_JUMP:
					printf("\tjump %x", stm->head->jump.labels->head);
					break;

				case T_Stm::T_CJUMP:
					printf("\tcjump t:%x f:%x", stm->head->cjump.t, stm->head->cjump.f);
					break;

				default:
					printf("\tstm");
				}

			//	printf("\n");

				stm = stm->tail;
			}

		//	printf("\n");
		//	printf("\n");

			curblock = curblock->tail;
		}
	}

	return block;
}

struct C_stm
{
	C_stm(T_StmList* stm)
	{
		m_stm = stm;
		m_marked = false;
	}
	T_StmList* m_stm;
	bool m_marked;
};

struct C_stmList
{
	C_stmList(C_stm* _head, C_stmList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	C_stm* head;
	C_stmList* tail;
};

map<Temp_label*, C_stm*> labelstm;

T_StmList* C_traceSchedule(C_block block)
{
	ASSERT(0);
	return NULL;
#if 0

	C_stmListList* stmLists = block.stmLists;

	C_stmList* Q = NULL;

	// Add to list
	while (stmLists)
	{
		ASSERT(stmLists->head->head->kind == T_Stm::T_LABEL);

		C_stm* cstm = new C_stm(stmLists->head);
		Q = new C_stmList(cstm, Q);

		labelstm[stmLists->head->head->label] = cstm;

		stmLists = stmLists->tail;
	}
	Q = Reverse(Q);

	T_StmList* t = NULL;

	while (Q)
	{
		// Start new empty trace
		C_stmList* T = NULL;

		C_stm* b = Q->head;

		Q = Q->tail;

		do
		{
			ASSERT(!b->m_marked);

			labelstm[b->m_stm->head->label] = NULL;
			b->m_marked = true;

			T = new C_stmList(b, T);

			T_StmList* secondlast = b->m_stm;
			ASSERT(secondlast->tail);

			while (secondlast->tail->tail)
			{
				secondlast = secondlast->tail;
			}

			T_StmList* last = secondlast->tail;

			if (last->head->kind == T_Stm::T_JUMP)
			{
				C_stm* l = labelstm[last->head->jump.labels->head];
				//ASSERT(!l->m_marked);

				if (last->head->jump.labels->tail == NULL)	// only one target label
				{
					/*
					if (l)
					{
						// remove jump
						// merge basic blocks
						secondlast->tail = l->m_stm->tail;
					}
					*/

					b = l;
				}
				else
					b = l;
			}
			else if (last->head->kind == T_Stm::T_CJUMP)
			{
				C_stm* l = labelstm[last->head->cjump.f];

				if (l)//->m_marked)
				{
					b = l;
				}
				else
				{
					l = labelstm[last->head->cjump.t];
					if (l)//->m_marked)
					{
						// TODO, reverse labels and condition

						b = l;
					}
					else
					{
						Temp_label* f = new Temp_label;

						last->tail = new T_StmList(T_Seq(T_Label(f),
											T_JumpStm(T_Name(last->head->cjump.f), new Temp_labelList(last->head->cjump.f, NULL))), NULL);
						last->head->cjump.f = f;

						b = NULL;
					}
				}
			}
			else
				ASSERT(0);

			while (Q && Q->head->m_marked)
			{
				Q = Q->tail;
			}
		}
		while (b);// && !b->m_marked)

		T = Reverse(T);

		while (T)
		{
			T_StmList* stmlist = T->head->m_stm;

			while (stmlist)
			{
				t = new T_StmList(stmlist->head, t);

				stmlist = stmlist->tail;
			}

			T = T->tail;
		}
	}

	return t;
#endif
}

#if 0

void adjust()
{
	T_Stm* laststm;

	// For any CJUMP followed by its true label, we switch the true and false labels and negate the condition
	if (laststm->kind == T_Stm::T_CJUMP &&
		laststm->cjump.t == )
	{
		Temp_label* t = laststm->cjump.t;
		laststm->cjump.t = laststm->cjump.f;
		laststm->cjump.f = t;

		switch (laststm->cjump.op)
		{
			case '=='	laststm->cjump.op = '!='; break;
			case '!='	laststm->cjump.op = '=='; break;
			case '<='	laststm->cjump.op = '>'; break;
			case '>='	laststm->cjump.op = '<'; break;
			case '<'		laststm->cjump.op = '>='; break;
			case '>'		laststm->cjump.op = '<='; break;
			default:
				ASSERT(0);
		}
	}
}
#endif

//}	// cpp
}
