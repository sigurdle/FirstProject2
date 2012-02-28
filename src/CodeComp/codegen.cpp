#include "stdafx.h"
#include "codegen.h"

namespace System
{
using namespace std;

#if 0
// no B declared here
class X;
template<class T> class Y {
class Z; // forward declaration of member class
void f() {
X* a1; // declare pointer to X
T* a2; // declare pointer to T
Y* a3; // declare pointer to Y<T>
Z* a4; // declare pointer to Z
typedef typename T::A TA;
TA* a5; // declare pointer to T’s A
typename T::A* a6; // declare pointer to T’s A
T::A* a7; // T::A is not a type name:
// multiply T::A by a7; ill-formed,
// no visible declaration of a7
B* a8; // B is not a type name:
// multiply B by a8; ill-formed,
// no visible declarations of B and a8
}
};
#endif

/*
class test
{
public:
	class u
	{
	};

	class base0
	{
	public:
		static int x;
	};

	class base1
	{
	public:
		static int x;
	};

	class base2 : public base1
	{
	public:
	};

	class base3 : public base2
	{
	public:
	};

	class test2 : public base3
	{
		int get();
	};
};

int test::test2::get()
{
	return base0::x;
}
*/

/*
int(*test)();
int(test2)();

int i,
*pi,
f(),
*fpi(int),
(*pif)(const char*, const char*),
(*fpif(int))(int);
*/
//int k = test;
//int l = test2;

/*
void getn(int ***func(int));


void h()
{
	getn(1);
}
*/

//static FILE* fileout;	// TODO, remove

void fput8(FILE* fp, uint8 v);
void fput16(FILE* fp, uint16 v);
void fput32(FILE* fp, uint32 v);

//namespace cpp
//{

//////////////////////////////////////////////////////////////////////////////
// x86 code generation


void CCodeGenerator::FlushLabel(Temp_label* pLabel)
{
	ASSERT(0);
#if 0
//	CLabel* pLabel = m_labelStack.top();
//	m_labelStack.pop();

	ULONG pos = ftell(fileout);

	ASSERT(pLabel->m_pos != -1);

	for (int i = 0; i < pLabel->m_branches.size(); i++)
	{
		DWORD broffset = pLabel->m_branches[i];
		fseek(fileout, broffset, SEEK_SET);
		
		if (FALSE)
		{
			short offset = pLabel->m_pos - broffset;
			fput16(fileout, offset/*-2*/);
		}
		else
		{
			long offset = (pLabel->m_pos - broffset) - 4;
			fwrite(&offset, 4, 1, fileout);
		}
	}

	fseek(fileout, pos, SEEK_SET);
	pLabel->m_branches.clear();
//	delete pLabel;
#endif
}

#if 0
void CCodeGenerator::Function(FILE* fp, CFunctionCode* pFunc)
{
	reg = 0;/*EAX*/

//	dreg = 0;
//	areg = 0;

	m_fileout = fp;
	pFunc->m_spOffset = 0;

	Function_Prologue(pFunc);

#if 0
	for (int i = 0; i < pFunc->m_pBody->m_statements.size(); i++)
	{
		WriteStatement(pFunc, pFunc->m_pBody->m_statements[i]);
	}
#endif

	Function_Epilogue(pFunc);
}
#endif

//////////////////////////////////////////////

CodeCompExt AS_instr* AS_Source(const char* filename)
{
	AS_instr* inst = new AS_instr;

	inst->kind = AS_instr::I_SO;
	inst->filename = _strdup(filename);

	return inst;
}

CodeCompExt AS_instr* AS_Line(int line_pos)
{
	AS_instr* inst = new AS_instr;

	inst->kind = AS_instr::I_LINE;
	inst->LINE.num = line_pos;

	return inst;
}

CodeCompExt AS_instr* AS_LBrac()
{
	AS_instr* inst = new AS_instr;

	inst->kind = AS_instr::I_LBRAC;

	return inst;
}

CodeCompExt AS_instr* AS_RBrac()
{
	AS_instr* inst = new AS_instr;

	inst->kind = AS_instr::I_RBRAC;

	return inst;
}

CodeCompExt AS_instr* AS_LSym(T_Declarator* declarator)
{
	AS_instr* inst = new AS_instr;

	inst->kind = AS_instr::I_LSYM;
	inst->fun = declarator;

	return inst;
}

CodeCompExt AS_instr* AS_Align(int nbytes)
{
	AS_instr* inst = new AS_instr;

	inst->kind = AS_instr::I_ALIGN;
	//inst->fun = declarator;

	return inst;
}

CodeCompExt AS_instr* AS_Fun(T_Declarator* declarator)
{
	AS_instr* inst = new AS_instr;

	inst->kind = AS_instr::I_FUN;
	inst->fun = declarator;

	return inst;
}

CodeCompExt AS_instr* AS_Oper(MInstruction* assem, Temp_tempList* d, Temp_tempList* s, AS_Targets* jumps)
{
	//ASSERT(assem);

//	ASSERT(d || s);

	AS_instr* inst = new AS_instr;

	inst->assem = assem;
	inst->kind = AS_instr::I_OPER;
	inst->OPER.dst = d;
	inst->OPER.src = s;
	inst->OPER.jumps = jumps;

	return inst;
}

CodeCompExt AS_instr* AS_Move(MInstruction* assem, Temp_tempList* d, Temp_tempList* s)
{
	ASSERT(d);
	ASSERT(d->tail == NULL);

	ASSERT(s);
	ASSERT(s->tail == NULL);

	ASSERT(assem);

	AS_instr* inst = new AS_instr;

	inst->assem = assem;
	inst->kind = AS_instr::I_MOVE;
	inst->MOVE.dst = d;
	inst->MOVE.src = s;

	return inst;
}

CodeCompExt AS_instr* AS_Label(Temp_label* label)
{
	ASSERT(label);

	AS_instr* inst = new AS_instr;
	inst->kind = AS_instr::I_LABEL;
//	inst->LABEL.assem = assem;
	inst->LABEL.label = label;

	return inst;
}

CodeCompExt AS_instr* AS_Data(uint8* buffer, long size)
{
	AS_instr* inst = new AS_instr;
	inst->kind = AS_instr::I_DATA;
	inst->DATA.buffer = buffer;
	inst->DATA.size = size;

	return inst;
}

CodeCompExt AS_instr* AS_Data2(T_ExpList* explist)
{
	AS_instr* inst = new AS_instr;
	inst->kind = AS_instr::I_DATA2;
	inst->explist = explist;

	return inst;
}

//AS_instrList* instrList = NULL;

void CFunctionCode::emit(AS_instr* inst)
{
	if (instrListTail)
	{
		instrListTail->tail = new AS_instrList(inst, NULL);
		instrListTail = instrListTail->tail;
	}
	else
	{
		instrList = new AS_instrList(inst, NULL);
		instrListTail = instrList;
	}

	switch(inst->kind)
	{
	case AS_instr::I_LABEL:
		{
		//	printf("%s:\n", inst->LABEL.assem);
		}
		break;

	case AS_instr::I_OPER:
		//printf("%s ", inst->OPER.assem);

		Temp_tempList* p;
		
		p = inst->OPER.src;
		while (p)
		{
		//	printf("r%d ", p->temp->m_n);
			p = p->tail;
		}

		//printf(" -> ");

		p = inst->OPER.dst;
		while (p)
		{
		//	printf("r%d ", p->temp->m_n);
			p = p->tail;
		}

		break;

	case AS_instr::I_MOVE:
		//printf("%s\n", inst->MOVE.assem);
		break;
	}

	//printf("\n");
}

//fwrite_const32

#if 0
ea(char* p)
{
	if (*p == #)
	{
	}
	if (*p == 'd' || *p == 'D')
	{
	}
	else if (*p == 'a' || *p == 'A')
	{
	}
	else if (*p == '(')
	{
	}
}
#endif


//int Temp_temp::count = 0;
//int Temp_label::count = 0;

///////////////////////////////////////////////////////////////////////////
// CCodeGenx86

#if 0
void CCodeGenx86::mov_r32_imm32(int rd, long value)
{
	if (FALSE)
	{
		printf("\tMOV\t%s,%d\n", RegName_r32[rd], value);
	}
	else
	{
		putc(0xB8+rd, fileout);
		fwrite(&value, 1, 4, fileout);
	}
}
#endif


#if 0
void CCodeGenx86::amode(int r32, int RM, long displacement)
{
	if (TRUE)
	{
		BYTE DestReg = r32;
		BYTE Mod;
		
		if (displacement == 0)
			Mod = 3;
		else
			Mod = 1;

		BYTE ModRM = RM | (DestReg<<3) | (Mod<<6);
		putc(ModRM, fileout);

		if (Mod == 1)//displacement)
		{
			putc(displacement, fileout);
		}
		else if (Mod == 2)
		{
			fwrite(&displacement, 4, 1, fileout);
		}
		else if (Mod == 0 && RM == 5)
		{
			fwrite(&displacement, 4, 1, fileout);
		}
	}
	else
	{
		ASSERT(0);
	}
}
#endif

#if 0
void CCodeGenx86::mov_r32_rm32(AS_instr* instr, int r32, int Mod, int RM, long displacement)
{
	instr->putbyte(0x8B);
	//if ((unsigned)displacement < 256)
	amode(instr, r32, Mod, RM, displacement);
}

void CCodeGenx86::lea_r32_rm32_disp(AS_instr* instr, int r32, int RM, long displacement)
{
	instr->putbyte(0x8D);
	//if ((unsigned)displacement < 256)
	amode(instr, r32, RM, displacement);
}
#endif

//long _D[8];
//long _A[8];

//int relocs

#if 0
void CCodeGenx86::push_imm(long value)
{
	/*	// ????
	if (value >= -128 && value <= 127)
	{
		putc(0x6A, fileout);	// push imm8
		putc(value, fileout);
	}
	else
	*/
	{
		putc(0x68, fileout);	// push imm32
		fwrite(&value, 1, 4, fileout);
	}
}

void CCodeGenx86::or_imm(int reg, long value)
{
	ASSERT(reg == 0);

	if (value >= -128 && value <= 127)
	{
		putc(0x0C, fileout);	// or AL,imm8
		putc(value, fileout);
	}
	else
	{
		putc(0x0D, fileout);	// or EAX,imm8
		fwrite(&value, 1, 4, fileout);
	}
}
#endif



#if 0
struct x86instrList
{
	x86instrList(x86instr* _head, x86instrList* _tail)
	{
		ASSERT(_head);
		ASSERT(_tail);

		head = _head;
		tail = _tail;
	}

	x86instr* head;
	x86instrList* tail;
};

x86instrList* instructions;
#endif

static int x86_reg = 0;

#if 0
void x86Assem(x86instrList* il)
{
	if (il->tail)
}
#endif




//}	// cpp
}
