#ifndef __x86assem_h_
#define __x86assem_h_

#ifndef CodeCompExt
#define CodeCompExt	DECLSPEC_DLLIMPORT
#endif

///////////////////////////////////////////////////////////////
// x86 assem

#include "LFC/disasm.h"

//#include "cppcompiler.h"
//#include "translate.h"

//namespace cpp
//{
namespace System
{

class Temp_label;
class Temp_temp;
class T_Exp;

class x86addr
{
public:
	enum
	{
		K_REG,
		K_RM,
		K_IMM,
		K_NAME,
		K_TEMP,
		K_BRACKET,
		K_BRACKET_DISPLACE,
	}
	kind;

	union
	{
		uint8 reg;
		int8 imm8;
		long imm32;
		Temp_label* name;
		Temp_temp* temp;
		x86addr* bracket;
		struct //_rm
		{
			Temp_temp* temp;
			int displacement;
		}
		rm;

		struct //_bracket_displace
		{
			x86addr* addr;
			int displacement;
		}
		bracket_displace;
	};
};

class x86instr : public MInstruction
{
public:
	enum tykind
	{
		K_ADD,
		K_ADC,
		K_SUB,
		K_NEG,
		K_NOT,
		K_MOV,
		K_CALL,
		K_RET,
		K_RET_IMM16,
		K_PUSH,
		K_POP,
		K_DIV,
		K_IDIV,
		K_AND,
		K_OR,
		K_XOR,
		K_LEA,
		K_SBB,
		K_CMP,
		K_INT,
		K_LEAVE,
		K_INC,
		K_DEC,
		K_JMP,
		K_Jcc,
		K_SETcc,
		K_BSF,
		K_MOVSX,
		K_STOS,
		K_ROR,
		K_SHL,
		K_SHR,
		K_SAR,
		K_TEST,
		K_SCAS,
		K_MOVZX,
		K_MOVS,
		K_REP,
		K_XCHG,
		K_IMUL,
		K_IMUL3,
		K_SYSENTER,
		K_NOP,	// really same as XCHG eax,eax, but this carries more semantics
	}
	kind;

	CTOR x86instr()
	{
		size_prefix = 0;
	}

	bool size_prefix : 1;

	union
	{
		struct //_mov
		{
			x86addr* dst;
			x86addr* src;
			bool w : 1;
		}
		mov;

		struct //_cmp
		{
			x86addr* dst;
			x86addr* src;
			bool w : 1;
		}
		cmp;

		struct //_jcc
		{
			uint8 op;
			Temp_label* label;
		}
		jcc;

		struct //_setcc
		{
			uint8 op;
			x86addr* dst;
		}
		setcc;

		struct //_imul
		{
			x86addr* dst;
			x86addr* src;
			long src2;
		}
		imul;

		x86instr* instr;

	//	x86addr* push;
	//	x86addr* pop;
	//	x86addr* call;
	//	x86addr* neg;
		x86addr* op0;
		int integer;
		int8 data8;
	};
};

inline x86instr* x86_instr(x86instr::tykind kind)
{
	x86instr* p = new x86instr;
	p->kind = kind;
	return p;
}

x86instr* x86_PUSH(x86addr* push);
x86instr* x86_POP(x86addr* pop);
x86instr* x86_MOV(x86addr* dst, x86addr* src, int w = 4);
x86instr* x86_IMUL(x86addr* dst, x86addr* src);
x86instr* x86_IMUL(x86addr* dst, x86addr* src1, long src2);
x86instr* x86_LEA(x86addr* dst, x86addr* src);
x86instr* x86_ADD(x86addr* dst, x86addr* src);
x86instr* x86_ADC(x86addr* dst, x86addr* src);
x86instr* x86_SUB(x86addr* dst, x86addr* src);
x86instr* x86_AND(x86addr* dst, x86addr* src, int w = 4);
x86instr* x86_OR(x86addr* dst, x86addr* src, int w = 4);
x86instr* x86_XOR(x86addr* dst, x86addr* src, int w = 4);
x86instr* x86_CMP(x86addr* dst, x86addr* src);
x86instr* x86_ROR(x86addr* dst, x86addr* src);
x86instr* x86_SHL(x86addr* dst, x86addr* src);
x86instr* x86_SHR(x86addr* dst, x86addr* src);
x86instr* x86_SAR(x86addr* dst, x86addr* src);
x86instr* x86_TEST(x86addr* dst, x86addr* src, int w);
x86instr* x86_SBB(x86addr* dst, x86addr* src);
x86instr* x86_DIV(x86addr* src);
x86instr* x86_IDIV(x86addr* src);
x86instr* x86_XCHG(x86addr* dst, x86addr* src);
x86instr* x86_MOVZX(x86addr* dst, x86addr* src, int w);
x86instr* x86_MOVSX(x86addr* dst, x86addr* src, int w);
x86instr* x86_NEG(x86addr* neg);
x86instr* x86_NOT(x86addr* neg);
x86instr* x86_CALL(x86addr* call);
x86instr* x86_INC(x86addr* addr);
x86instr* x86_DEC(x86addr* addr);
x86instr* x86_JMP(x86addr* addr);
x86instr* x86_Jcc(int8 rel8);
x86instr* x86_Jcc(long rel32);
x86instr* x86_Jcc(uint8 op, Temp_label* label);
x86instr* x86_SETcc(int op, x86addr* dst);
x86instr* x86_LEAVE();
x86instr* x86_RET();
x86instr* x86_RET_IMM16(short imm16);
x86instr* x86_INT(int8 imm8);
x86instr* x86_REP(x86instr* instr);
x86instr* x86_NOP();

x86addr* x86_NAME(Temp_label* label);
x86addr* x86_IMM(T_Exp* pTExpr);
x86addr* x86_IMM(long imm32);
x86addr* x86_REG(uint8 reg);
x86addr* x86_TEMP(Temp_temp* temp);
x86addr* x86_RM(Temp_temp* temp, int displacement);
x86addr* x86_BRACKET(x86addr* addr);
x86addr* x86_BRACKET_DISPLACE(x86addr* addr, long displacement);

//CodeCompExt std::iostream& operator << (std::iostream& stream, const x86instr::tykind kind);
//CodeCompExt std::iostream& operator << (std::iostream& stream, const x86instr* instr);
//CodeCompExt std::iostream& operator << (std::iostream& stream, const x86addr* addr);

CodeCompExt String toString(const x86instr* instr);

//}	// cpp
}

#endif // __x86assem_h_
