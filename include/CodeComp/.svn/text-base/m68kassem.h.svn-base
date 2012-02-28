#ifndef __m68kassem_h_
#define __m68kassem_h_

#include "LFC/disasm.h"

namespace System
{

//namespace cpp
//{
class Temp_label;
class Temp_temp;
class m68koperand;
class m68kinstr;

class CodeCompExt m68kContext : public MContext
{
public:
};

#ifndef __LERSTAD__

class m68koperand
{
public:
	enum
	{
		K_IMM,
		K_NAME,
		K_DATAREG,
		K_ADDRREG,
		K_DATAREG_TEMP,
		K_ADDRREG_TEMP,
		K_INDIRECT,
		K_INDIRECT_REG,
		K_INDIRECT_TEMP,
		K_INDIRECT_POSTINC,
		K_INDIRECT_PREDEC,
		K_INDIRECT_DISPLACEMENT,
		K_INDIRECT_INDEX,
	}
	kind;

	union
	{
		long imm32;

		Temp_label* name;

		uint8 reg;
		Temp_temp** temp;

		m68koperand* indirect;

		struct //_displacment
		{
			short disp16;
			Temp_temp** areg;
		}
		displacement;

		struct //_index
		{
			int8 disp;
			Temp_temp** reg;
			Temp_temp** ext_reg;
			uint8 ext_factor;
		}
		index;
	};
};

class m68kinstr : public MInstruction
{
public:
	enum tykind
	{
		K_MOVE,
		K_MOVEM,
		K_MOVEQ,
		K_SUBQ,
		K_ADD,
		K_SUB,
		K_MULS,
		K_MULU,
		K_DIVS,
		K_OR,
		K_EOR,
		K_AND,
		K_ANDI,
		K_JSR,
		K_BSR,
		K_JMP,
		K_Bcc,
		K_SET,
		K_LINK,
		K_UNLK,
		K_CMP,
		K_CLR,
		K_LEA,
		K_CHK,
		K_EXG,
		K_RTS,
		K_RTR,
		K_RTE,
		K_TRAP,
		K_PEA,
		K_EXT,
		K_NEG,
		K_NEGX,
		K_SWAP,
		K_TST,
		K_DBcc,
		K_BTST,
		K_BCHG,
		K_BCLR,
		K_BSET,
		K_ASR,
		K_ROXR,
		K_ADDX,
		K_SUBX,
		K_SUBI,
		K_LSHIFT
	}
	kind;

	CTOR m68kinstr()
	{
		two.src = NULL;
		two.dst = NULL;
	}

	union
	{
		m68koperand* op;

		struct// _two
		{
			m68koperand* src;
			m68koperand* dst;
			int size;
		}
		two;

		struct //_dbcc
		{
			uint8 condition;
			Temp_temp** dn;
			Temp_label* displacement;
		}
		dbcc;

		struct //_lshift
		{
			m68koperand* src;
			m68koperand* dst;
			int size;
			bool dr : 1;
		}
		lshift;

		struct //_muls
		{
			m68koperand* src;
			Temp_temp** dl_reg;
			Temp_temp** dh_reg;
		}
		muls;

		struct //_divs
		{
			m68koperand* src;
			Temp_temp** q_reg;
			Temp_temp** r_reg;
		}
		divs;

		struct //_clr
		{
			m68koperand* operand;
			int size;
		}
		clr;

		struct //_link
		{
			m68koperand* reg;
			long offset;
		}
		link;

		struct //_subi
		{
			int size;
			long src;
			m68koperand* dst;
		}
		subi;

		struct //_bcc
		{
			uint8 condition;
			Temp_label* displacement;
		}
		bcc;

		struct //_andi
		{
			long src;
			m68koperand* dst;
			int size;
		}
		andi;

		struct //_set
		{
			uint8 condition;
			m68koperand* dst;
		}
		set;

		struct //_moveq
		{
			Temp_temp** dreg;
			int8 data;
		}
		moveq;

		struct //_subq
		{
			m68koperand* dst;
			int8 data;
		}
		subq;

		struct //_ext
		{
			Temp_temp** dn;
			uint8 opmode;
		}
		ext;

		uint8 trap;
		uint16 uint_16;
	};
};

#endif

CodeCompExt m68koperand* m68k_IMM(long imm32);
CodeCompExt m68koperand* m68k_NAME(Temp_label* name);
CodeCompExt m68koperand* m68k_DATAREG(uint8 reg);
CodeCompExt m68koperand* m68k_DATAREG(Temp_temp** temp);
CodeCompExt m68koperand* m68k_ADDRREG(uint8 reg);
CodeCompExt m68koperand* m68k_INDIRECT(Temp_temp** temp);
CodeCompExt m68koperand* m68k_INDIRECT(m68koperand* op);
CodeCompExt m68koperand* m68k_INDIRECT_DISPLACEMENT(Temp_temp** areg, short disp16);
CodeCompExt m68koperand* m68k_INDIRECT_PREDEC(Temp_temp** areg);
CodeCompExt m68koperand* m68k_INDIRECT_INDEX(uint8 disp, Temp_temp** reg, Temp_temp** ext_reg, uint8 ext_factor);

CodeCompExt m68kinstr* m68k_MOVE(m68koperand* src, m68koperand* dst, int size);
CodeCompExt m68kinstr* m68k_MOVEQ(int8 data, Temp_temp** dreg);
CodeCompExt m68kinstr* m68k_SUBQ(int8 data, m68koperand* dst);
CodeCompExt m68kinstr* m68k_CLR(m68koperand* op, int size);
CodeCompExt m68kinstr* m68k_LEA(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_PEA(m68koperand* src);
CodeCompExt m68kinstr* m68k_ADD(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_ADDX(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_SUB(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_SUBX(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_SUBI(long src, m68koperand* dst, int size);
CodeCompExt m68kinstr* m68k_MULS(m68koperand* src, Temp_temp** dl_reg, Temp_temp** dh_reg);
CodeCompExt m68kinstr* m68k_DIVS(m68koperand* src, Temp_temp** q_reg, Temp_temp** r_reg);
CodeCompExt m68kinstr* m68k_MULU(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_OR(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_AND(m68koperand* src, m68koperand* dst);
CodeCompExt m68kinstr* m68k_ANDI(long src, m68koperand* dst, int size);
CodeCompExt m68kinstr* m68k_LINK(m68koperand* reg, long offset);
CodeCompExt m68kinstr* m68k_UNLK(m68koperand* reg);
CodeCompExt m68kinstr* m68k_SET(uint8 condition, m68koperand* dst);
CodeCompExt m68kinstr* m68k_CMP(m68koperand* src0, m68koperand* src1);
CodeCompExt m68kinstr* m68k_TST(m68koperand* op);
CodeCompExt m68kinstr* m68k_EXT(Temp_temp** op, uint8 opmode);
CodeCompExt m68kinstr* m68k_JSR(m68koperand* op);
CodeCompExt m68kinstr* m68k_RTS();
CodeCompExt m68kinstr* m68k_DBcc(uint8 condition, Temp_temp** dn, Temp_label* displacement);
CodeCompExt m68kinstr* m68k_Bcc(uint8 condition, Temp_label* displacement);
CodeCompExt m68kinstr* m68k_ASR(m68koperand* reg);
CodeCompExt m68kinstr* m68k_LSHIFT(bool dr, m68koperand* src, m68koperand* dst, int size);
CodeCompExt m68kinstr* m68k_ROXR(m68koperand* reg);
CodeCompExt m68kinstr* m68k_NEG(m68koperand* op);
CodeCompExt m68kinstr* m68k_NEGX(m68koperand* op);

CodeCompExt m68kinstr* disasm_m68k(m68kContext* c);

//CodeCompExt std::ostream& operator << (std::ostream& stream, const m68kinstr* instr);
CodeCompExt String toString(const m68kinstr* instr);

//}	// cpp
}	// System

#endif // __m68kassem_h_
