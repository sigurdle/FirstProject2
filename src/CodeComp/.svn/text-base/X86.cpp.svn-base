#include "stdafx.h"

#include "ir.h"

#include "X86.h"
#include "x86assem.h"

namespace System
{

//#include <sstream>

//namespace cpp
//{

/////////////////////////////////////////////////////

char* RegName_rd[] =
{
	"eax",
	"ecx",
	"edx",
	"ebx",
	"esp",
	"ebp",
	"esi",
	"edi",
};

CodeCompExt IO::TextWriter& operator << (IO::TextWriter& stream, const x86addr* addr)
{
	ASSERT(0);
#if 0
	switch (addr->kind)
	{
	case x86addr::K_BRACKET:
		{
			stream << "[";
			stream << addr->bracket;
			stream << "]";
		}
		break;

	case x86addr::K_BRACKET_DISPLACE:
		{
			stream << "[";
			stream << addr->bracket_displace.addr;

			if (addr->bracket_displace.displacement < 0)
				stream << addr->bracket_displace.displacement;
			else
				stream << "+" << addr->bracket_displace.displacement;

			stream << "]";
		}
		break;

	case x86addr::K_REG:
		{
			ASSERT(addr->reg >= 0 && addr->reg < 8);
			stream << RegName_rd[addr->reg];
		}
		break;

	case x86addr::K_IMM:
		{
			stream << addr->imm32;
		}
		break;
	}
#endif
	return stream;
}

IO::TextWriter& operator << (IO::TextWriter& stream, x86instr::tykind kind)
{
	switch (kind)
	{
	case x86instr::K_SCAS:
		{
			stream << "scas";
		}
		break;

	case x86instr::K_MOVS:
		{
			stream << "movs";
		}
		break;

	case x86instr::K_MOVZX:
		{
			stream << "movzx";
		}
		break;

	case x86instr::K_MOVSX:
		{
			stream << "movsx";
		}
		break;

	case x86instr::K_INC:
		{
			stream << "inc";
		}
		break;

	case x86instr::K_DEC:
		{
			stream << "dec";
		}
		break;

	case x86instr::K_NEG:
		{
			stream << "neg";
		}
		break;

	case x86instr::K_NOT:
		{
			stream << "not";
		}
		break;

	case x86instr::K_CALL:
		{
			stream << "call";
		}
		break;

	case x86instr::K_JMP:
		{
			stream << "jmp";
		}
		break;

	case x86instr::K_Jcc:
		{
			stream << "jcc";
		}
		break;

	case x86instr::K_SBB:
		{
			stream << "sbb";
		}
		break;

	case x86instr::K_ADC:
		{
			stream << "adc";
		}
		break;

	case x86instr::K_ADD:
		{
			stream << "add";
		}
		break;

	case x86instr::K_SUB:
		{
			stream << "sub";
		}
		break;

	case x86instr::K_DIV:
		{
			stream << "div";
		}
		break;

	case x86instr::K_TEST:
		{
			stream << "test";
		}
		break;

	case x86instr::K_CMP:
		{
			stream << "cmp";
		}
		break;

	case x86instr::K_XCHG:
		{
			stream << "xchg";
		}
		break;

	case x86instr::K_MOV:
		{
			stream << "mov";
		}
		break;

	case x86instr::K_LEA:
		{
			stream << "lea";
		}
		break;

	case x86instr::K_INT:
		{
			stream << "int";
		}
		break;

	case x86instr::K_AND:
		{
			stream << "and";
		}
		break;

	case x86instr::K_OR:
		{
			stream << "or";
		}
		break;

	case x86instr::K_XOR:
		{
			stream << "xor";
		}
		break;

	case x86instr::K_PUSH:
		{
			stream << "push";
		}
		break;

	case x86instr::K_POP:
		{
			stream << "pop";
		}
		break;

	case x86instr::K_ROR:
		{
			stream << "ror";
		}
		break;

	case x86instr::K_SHL:
		{
			stream << "shl";
		}
		break;

	case x86instr::K_SHR:
		{
			stream << "shr";
		}
		break;

	case x86instr::K_SAR:
		{
			stream << "sar";
		}
		break;

	case x86instr::K_LEAVE:
		{
			stream << "leave";
		}
		break;

	case x86instr::K_RET:
		{
			stream << "ret";
		}
		break;

	case x86instr::K_RET_IMM16:
		{
			stream << "ret";
		}
		break;

	case x86instr::K_STOS:
		{
			stream << "stos";
		}
		break;

	case x86instr::K_REP:
		{
			stream << "rep";
		}
		break;

	case x86instr::K_SYSENTER:
		{
			stream << "sysenter";
		}
		break;

	case x86instr::K_NOP:	// Really same as XCHG eax,eax, but this carries more semantics
		{
			stream << "nop";
		}
		break;

	default:
		ASSERT(0);
	}

	return stream;
}

IO::TextWriter& operator << (IO::TextWriter& stream, const x86instr* instr)
{
	ASSERT(0);
#if 0
	stream << instr->kind;

	if (instr->kind == x86instr::K_REP)
	{
		stream << " ";
		stream << instr->instr;
	}
	else
	{
		stream << "\t";

		switch (instr->kind)
		{
		case x86instr::K_INC:
		case x86instr::K_DEC:
		case x86instr::K_NEG:
		case x86instr::K_NOT:
		case x86instr::K_CALL:
		case x86instr::K_PUSH:
		case x86instr::K_POP:
			{
				stream << instr->op0;
			}
			break;

		case x86instr::K_JMP:
			{
				stream << instr->op0;
			}
			break;

		case x86instr::K_Jcc:
			{
				stream << (int)instr->data8;
			}
			break;

		case x86instr::K_SBB:
		case x86instr::K_ADC:
		case x86instr::K_ADD:
		case x86instr::K_SUB:
		case x86instr::K_DIV:
		case x86instr::K_TEST:
		case x86instr::K_CMP:
		case x86instr::K_MOV:
		case x86instr::K_LEA:
		case x86instr::K_AND:
		case x86instr::K_OR:
		case x86instr::K_XOR:
		case x86instr::K_ROR:
		case x86instr::K_SHL:
		case x86instr::K_SHR:
		case x86instr::K_SAR:
		case x86instr::K_XCHG:
		case x86instr::K_MOVZX:
		case x86instr::K_MOVSX:
			{
				stream << instr->mov.dst;
				stream << ",";
				stream << instr->mov.src;
			}
			break;

		case x86instr::K_INT:
			{
				stream << (int)(unsigned char)instr->data8;
			}
			break;

		case x86instr::K_RET_IMM16:
			{
				stream << instr->integer;
			}
			break;

		case x86instr::K_LEAVE:
		case x86instr::K_RET:
		case x86instr::K_STOS:
		case x86instr::K_SCAS:
		case x86instr::K_MOVS:
		case x86instr::K_SYSENTER:
		case x86instr::K_NOP:	// Really same as XCHG eax,eax, but this carries more semantics
			{
			}
			break;

		default:
			ASSERT(0);
		}
	}
#endif
	return stream;
}

CodeCompExt String toString(const x86instr* instr)
{
	IO::StringWriter stream;
	stream << instr;

	return stream.str();
}

/////////////////////////////////////////////////////

typedef x86instr* (*x86_func)(X86Context* c);

static char r32[16];
static char rm32[512];

struct _rm
{
uint8 RM;
uint8 Reg;
uint8 Mod;
};

//long disp32;

_rm get_rm(X86Context* c)
{
	_rm rm;

	uint8 ModRM =  *c->pc++;
	rm.RM = ModRM & 0x7;
	rm.Reg = (ModRM>>3) & 0x7;
	rm.Mod = (ModRM>>6);

	return rm;
}

x86addr* do_rm(X86Context* c, _rm rm)
{
	switch (rm.Mod)
	{
	case 0:
		{
			if (rm.RM == 5)
			{
				long disp;

				/*
				if (c->operand_size == 2)
				{
					disp = *(short*)c->pc;
					c->pc += 2;
				}
				else if (c->operand_size == 4)
				*/
				{
					disp = *(long*)c->pc;
					c->pc += 4;
				}
				//else
				//	ASSERT(0);

		//		sprintf(r32, "%s", RegName_rd[Reg]);
			//	sprintf(rm32, "dword ptr ds:[0%8.8Xh]", /*RegName_rd[RM],*/ disp32);
				return x86_BRACKET_DISPLACE(x86_REG(rm.RM), disp);
			}
			else if (rm.RM == 4)
			{
				uint8 SIB = *c->pc; c->pc += 1;
				return x86_REG(rm.RM);
			}
			else
			{
			//	ASSERT(0);
			//	sprintf(r32, "%s", RegName_rd[Reg]);
			//	sprintf(rm32, "[%s]", RegName_rd[RM]);

				return x86_BRACKET(x86_REG(rm.RM));
			}
		}
		break;

	case 1:
		{
			if (rm.RM == 4)
			{
				uint8 SIB = *c->pc; c->pc += 1;
			}

			char disp8 = *c->pc++;
		//	sprintf(r32, "%s", RegName_rd[Reg]);
		
		//	sprintf(rm32, "%s+%d", RegName_rd[RM], disp8);
			//x86expr*
			//ASSERT(0);
			return x86_BRACKET_DISPLACE(x86_REG(rm.RM), disp8);
		}
		break;

	case 2:
		{
			if (rm.RM == 4)
			{
				uint8 SIB = *c->pc; c->pc += 1;
			}

			long disp;
			
			/*
			if (c->operand_size == 2)
			{
				disp = *(short*)c->pc;
				c->pc += 2;
			}
			else if (c->operand_size == 4)
			*/
			{
				disp = *(long*)c->pc;
				c->pc += 4;
			}
			//else
			//	ASSERT(0);

		//	sprintf(r32, "%s", RegName_rd[Reg]);
		//	sprintf(rm32, "%s+%d", RegName_rd[RM], disp32);
			return x86_BRACKET_DISPLACE(x86_REG(rm.RM), disp);
		}
		break;

	case 3:
		{
		//	sprintf(r32, "%s", RegName_rd[Reg]);
		//	sprintf(rm32, "%s", RegName_rd[RM]);
			return x86_REG(rm.RM);
		}
		break;
	}
	ASSERT(0);
	return NULL;
}

int8 get_imm8(X86Context* c)
{
	int8 value = *c->pc++;
	return value;
}

long get_imm(X86Context* c)
{
	ASSERT(c->operand_size == 2 || c->operand_size == 4);

	if (c->operand_size == 2)
	{
		short value = *(short*)c->pc;
		c->pc += 2;
		return value;
	}
	else
	{
		long value = *(long*)c->pc;
		c->pc += 4;
		return value;
	}
}

x86instr* x86_notimpl(X86Context* c)
{
//	c->out += sprintf(c->out, "\top not implemented");
//	c->pc++;
	return NULL;
}

x86instr* x86_add_rm8_r8(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
// TODO, print as 8bit
	return x86_ADD(do_rm(c, rm), x86_REG(rm.Reg));
//	c->out += sprintf(c->out, "add\t%s,%s", rm32, r32);
//	return 0;
}

x86instr* x86_80_r8_imm8(X86Context* c)
{
	uint8* revert = c->pc;

	c->pc++;
	_rm rm = get_rm(c);
	char data = *(char*)c->pc; c->pc += 1;
	
	switch (rm.Reg)
	{
	case 0:
		{
			return x86_ADD(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	case 1:
		{
			return x86_OR(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	case 2:
		{
			return x86_ADC(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	case 3:
		{
			return x86_SBB(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	case 4:
		{
			return x86_AND(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	case 5:
		{
			return x86_SUB(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	case 6:
		{
			return x86_XOR(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	case 7:
		{
			return x86_CMP(do_rm(c, rm), x86_IMM(data));
		}
		break;
		
	default:
		ASSERT(0);
	}

	return 0;
}

x86instr* x86_add_rm32_r32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_ADD(do_rm(c, rm), x86_REG(rm.Reg));
//	c->out += sprintf(c->out, "add\t%s,%s", rm32, r32);
//	return 0;
}

x86instr* x86_or_rm32_r32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_OR(do_rm(c, rm), x86_REG(rm.Reg));
}

x86instr* x86_nop(X86Context* c)	// Really same as XCHG eax,eax, but this carries more semantics
{
	c->pc++;
	return x86_NOP();
}

x86instr* x86_xchg_eax_r32(X86Context* c)
{
	char rd = *c->pc++ - 0x90;
	return x86_XCHG(x86_REG(0), x86_REG(rd));
}

x86instr* x86_add(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	/*
	BYTE ModRM =  *c->pc++;
	BYTE RM = ModRM & 0x7;
	BYTE Reg = (ModRM>>3) & 0x7;
	BYTE Mod = (ModRM>>6);
	*/

//	c->out += sprintf(c->out, "add\t%s,%s", r32, rm32);
	return x86_ADD(x86_REG(rm.Reg), do_rm(c, rm));

#if 0
	switch (Mod)
	{
	case 1:
		{
			char disp8 = *c->pc++;
			printf("%s,%s+%d", RegName_rd[Reg], RegName_rd[RM], disp8);
		}
		break;

	case 2:
		{
			long disp32 = *(DWORD*)c->pc;
			c->pc += 4;

			printf("%s,%s+%d", RegName_rd[Reg], RegName_rd[RM], disp32);
		}
		break;

	case 3:
		printf("%s,%s", RegName_rd[Reg], RegName_rd[RM]);
		break;
	}
#endif

	return 0;
}

x86instr* x86_cmp_al_imm8(X86Context* c)
{
	c->pc++;
	return x86_CMP(x86_REG(0), x86_IMM(get_imm8(c)));
}

x86instr* x86_cmp_eax_imm32(X86Context* c)
{
	c->pc++;
	return x86_CMP(x86_REG(0), x86_IMM(get_imm(c)));
}

x86instr* x86_or_al_imm8(X86Context* c)
{
	c->pc++;
	char value = *c->pc++;
	return x86_OR(x86_REG(0), x86_IMM(value));

//	c->out += sprintf(c->out, "or\tAL,%d", value);
	return 0;
}

x86instr* x86_sub_r32_rm32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_SUB(x86_REG(rm.Reg), do_rm(c, rm));
}

x86instr* x86_or_r32_rm32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_OR(x86_REG(rm.Reg), do_rm(c, rm));
//	c->out += sprintf(c->out, "or\t%s,%s", r32, rm32);

	return 0;
}

x86instr* x86_sbb_r32_rm32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
//	c->out += sprintf(c->out, "sbb\t%s,%s", r32, rm32);
	return x86_SBB(x86_REG(rm.Reg), do_rm(c, rm));

	return 0;
}

x86instr* x86_sbb_rm32_r32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
//	c->out += sprintf(c->out, "sbb\t%s,%s", r32, rm32);
	return x86_SBB(do_rm(c, rm), x86_REG(rm.Reg));

	return 0;
}

x86instr* x86_xor_rm8_r8(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_XOR(do_rm(c, rm), x86_REG(rm.Reg));
	// TODO, print out as 8bit ?
//	c->out += sprintf(c->out, "xor\t%s,%s", r32, rm32);

	return 0;
}

x86instr* x86_xor_r8_rm8(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_XOR(x86_REG(rm.Reg), do_rm(c, rm));
}

x86instr* x86_xor_r32_rm32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_XOR(x86_REG(rm.Reg), do_rm(c, rm));
}

x86instr* x86_and_al_imm8(X86Context* c)
{
	c->pc++;
	char value = *c->pc++;

	return x86_AND(x86_REG(0), x86_IMM(value));
//	c->out += sprintf(c->out, "and\tAL,%d", value);
	return 0;
}

x86instr* x86_or_eax_imm32(X86Context* c)
{
	c->pc++;
	long value = get_imm(c);

	return x86_OR(x86_REG(0), x86_IMM(value));

//	c->out += sprintf(c->out, "or\tEAX,%d", value);
	return 0;
}

x86instr* x86_D1(X86Context* c)
{
	uint8* reset = c->pc;
	c->pc++;
	_rm rm = get_rm(c);
	if (rm.Reg == 4)
	{
		return x86_SHL(do_rm(c, rm), x86_IMM(1));
//		c->out += sprintf(c->out, "shl\t%s", rm32);
	}
	else if (rm.Reg == 5)
	{
		return x86_SHR(do_rm(c, rm), x86_IMM(1));
//		c->out += sprintf(c->out, "shr\t%s", rm32);
	}
	else if (rm.Reg == 7)
	{
		return x86_SAR(do_rm(c, rm), x86_IMM(1));
//		c->out += sprintf(c->out, "shr\t%s", rm32);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}

	return 0;
}

x86instr* x86_scas_m8(X86Context* c)
{
	c->pc++;
//	c->out += sprintf(c->out, "scasb\t");
	return x86_instr(x86instr::K_SCAS);
	return 0;
}

x86instr* x86_scas_m32(X86Context* c)
{
	c->pc++;
	if (true)
		return x86_instr(x86instr::K_SCAS);
//		c->out += sprintf(c->out, "scasd\t");
	else
		return x86_instr(x86instr::K_SCAS);
//		c->out += sprintf(c->out, "scasw\t");
	return 0;
}

x86instr* x86_adc_al_imm8(X86Context* c)
{
	c->pc++;
	char imm8 = *(char*)c->pc; c->pc += 1;

	return x86_ADC(x86_REG(0), x86_IMM(imm8));
}

x86instr* x86_adc_eax_imm32(X86Context* c)
{
	c->pc++;
	long imm32 = get_imm(c);

	return x86_ADC(x86_REG(0), x86_IMM(imm32));
}

x86instr* x86_C1(X86Context* c)
{
	uint8* reset = c->pc;

	c->pc++;
	_rm rm = get_rm(c);
	if (rm.Reg == 1)
	{
		x86addr* dst = do_rm(c, rm);
		char imm8 = *(char*)c->pc; c->pc += 1;
		return x86_ROR(dst, x86_IMM(imm8));
//		c->out += sprintf(c->out, "ror\t%s,%d", rm32, imm8);
	}
	else if (rm.Reg == 4)
	{
		x86addr* dst = do_rm(c, rm);
		char imm8 = *(char*)c->pc; c->pc += 1;
		return x86_SHL(dst, x86_IMM(imm8));

//		c->out += sprintf(c->out, "shl\t%s,%d", rm32, imm8);
	}
	else if (rm.Reg == 5)
	{
		x86addr* dst = do_rm(c, rm);
		char imm8 = *(char*)c->pc; c->pc += 1;
		return x86_SHR(dst, x86_IMM(imm8));

//		c->out += sprintf(c->out, "shr\t%s,%d", rm32, imm8);
	}
	else if (rm.Reg == 7)
	{
		x86addr* dst = do_rm(c, rm);
		char imm8 = *(char*)c->pc; c->pc += 1;
		return x86_SAR(dst, x86_IMM(imm8));

//		c->out += sprintf(c->out, "sar\t%s,%d", rm32, imm8);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}

	return 0;
}

x86instr* x86_add_r32_imm32(X86Context* c)
{
	uint8* reset = c->pc;

	c->pc++;
	_rm rm = get_rm(c);
	x86addr* dst = do_rm(c, rm);
	long imm32 = get_imm(c);
	if (rm.Reg == 0)
	{
		return x86_ADD(dst, x86_IMM(imm32));
	}
	else if (rm.Reg == 1)
	{
		return x86_ADC(dst, x86_IMM(imm32));
	}
	else if (rm.Reg == 4)
	{
		return x86_AND(dst, x86_IMM(imm32));
	}
	else if (rm.Reg == 5)
	{
		return x86_SUB(dst, x86_IMM(imm32));
	}
	else if (rm.Reg == 7)
	{
		return x86_CMP(dst, x86_IMM(imm32));
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}
	return 0;
}

x86instr* x86_and_eax_imm32(X86Context* c)
{
	c->pc++;
	long imm32 = get_imm(c);

//	c->out += sprintf(c->out, "and\tEAX,%d", imm32);
	return x86_AND(x86_REG(0), x86_IMM(imm32));
	return 0;
}

x86instr* x86_push_r(X86Context* c)
{
	int reg = *c->pc - 0x50;
//	c->out += sprintf(c->out, "push\t");
//	c->out += sprintf(c->out, "%s", RegName_rd[reg]);
	c->pc++;

	return x86_PUSH(x86_REG(reg));
}

x86instr* x86_push_imm8(X86Context* c)
{
	c->pc++;
	char value = *c->pc++;

//	c->out += sprintf(c->out, "push\t");
//	c->out += sprintf(c->out, "%d", value);
	return x86_PUSH(x86_IMM(value));

//	return 0;
}

x86instr* x86_push_imm32(X86Context* c)
{
	c->pc++;
	long value = *(long*)c->pc;
	c->pc += 4;

//	c->out += sprintf(c->out, "push\t");
//	c->out += sprintf(c->out, "%d", value);
	return x86_PUSH(x86_IMM(value));

	return 0;
}

x86instr* x86_pop_r(X86Context* c)
{
	int reg = *c->pc - 0x58;
//	c->out += sprintf(c->out, "pop\t");
//	c->out += sprintf(c->out, "%s", RegName_rd[reg]);

	c->pc++;
	return x86_POP(x86_REG(reg));
	return 0;
}

x86instr* x86_sub_xor_cmp(X86Context* c)
{
	uint8* revert = c->pc;

	c->pc++;
	_rm rm = get_rm(c);

	int8 imm8 = *c->pc++;

	switch (rm.Reg)
	{
	case 0:
		{
			return x86_ADD(do_rm(c, rm), x86_IMM(imm8));
//			c->out += sprintf(c->out, "add\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 1:
		{
			return x86_OR(do_rm(c, rm), x86_IMM(imm8));
			
//			c->out += sprintf(c->out, "or\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 2:
		{
			return x86_ADC(do_rm(c, rm), x86_IMM(imm8));
			//do_rm(c);
			
//			c->out += sprintf(c->out, "adc\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 3:
		{
			return x86_SBB(do_rm(c, rm), x86_IMM(imm8));
		//	do_rm(c);
			
//			c->out += sprintf(c->out, "sbb\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 4:
		{
			return x86_AND(do_rm(c, rm), x86_IMM(imm8));
			//do_rm(c);
			
//			c->out += sprintf(c->out, "and\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 5:
		{
//			do_rm(c);
			return x86_SUB(do_rm(c, rm), x86_IMM(imm8));
			
//			c->out += sprintf(c->out, "sub\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;
		
	case 6:
		{
			return x86_XOR(do_rm(c, rm), x86_IMM(imm8));
		//	do_rm(c);
			
//			c->out += sprintf(c->out, "xor\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;
		
	case 7:
		{
			return x86_CMP(do_rm(c, rm), x86_IMM(imm8));
//			do_rm(c);
			
//			c->out += sprintf(c->out, "cmp\t");
//			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;
		
	default:
		{
			c->pc = revert;
			return x86_notimpl(c);
		}
		break;
	}

	return 0;
}

x86instr* x86_stos_m32(X86Context* c)
{
	c->pc++;
	return x86_instr(x86instr::K_STOS);
//	c->out += sprintf(c->out, "stos\tm32");

	return 0;
}

x86instr* x86_test_rm8_r8(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_TEST(do_rm(c, rm), x86_REG(rm.Reg), 1);
}

x86instr* x86_test_rm32_r32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_TEST(do_rm(c, rm), x86_REG(rm.Reg), 4);
}

x86instr* x86_mov_r8_rm8(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);

// TODO, show as 8-bit
//	c->out += sprintf(c->out, "mov\t%s,%s", r32, rm32);

	return 0;
}

x86instr* x86_mov_r32_rm32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);

	//c->out += sprintf(c->out, "mov\t%s,%s", r32, rm32);
	return x86_MOV(x86_REG(rm.Reg), do_rm(c, rm));

	return 0;
}

x86instr* x86_mov_rm32_r32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);

//	c->out += sprintf(c->out, "mov\t%s,%s", rm32, r32);
	return x86_MOV(do_rm(c, rm), x86_REG(rm.Reg));

	return 0;
}

x86instr* x86_mov_r32_imm32(X86Context* c)
{
	int r32 = *c->pc - 0xB8;
	c->pc++;

	uint32 imm32 = get_imm(c);

//	c->out += sprintf(c->out, "mov\t");
//	c->out += sprintf(c->out,"%s,%X", RegName_rd[r32], imm32);
	return x86_MOV(x86_REG(r32), x86_IMM(imm32));
	return 0;
}

x86instr* x86_mov_rm8_imm8(X86Context* c)
{
	uint8* reset = c->pc;

	c->pc++;
	_rm rm = get_rm(c);
	if (rm.Reg == 0)
	{
		x86addr* dst = do_rm(c, rm);
		x86addr* src = x86_IMM(get_imm8(c));
		return x86_MOV(dst, src);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}
}

x86instr* x86_mov_rm32_imm32(X86Context* c)
{
	uint8* reset = c->pc;

	c->pc++;
	_rm rm = get_rm(c);
	if (rm.Reg == 0)
	{
		x86addr* dst = do_rm(c, rm);
		long imm = get_imm(c);
		return x86_MOV(dst, x86_IMM(imm));
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}
}

x86instr* x86_lea(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	/*
	BYTE ModRM =  *c->pc++;
	BYTE RM = ModRM & 0x7;
	BYTE Reg = (ModRM>>3) & 0x7;
	BYTE Mod = (ModRM>>6);
	//if (TRUE)
	BYTE SIB = *c->pc++;
	*/

//	c->out += sprintf(c->out, "lea\t");
//	c->out += sprintf(c->out, "%s,[%s]", RegName_rd[Reg], RegName_rd[RM]);

	return x86_LEA(x86_REG(rm.Reg), do_rm(c, rm));
}

x86instr* x86_rep(X86Context* c)
{
	c->pc++;

	ASSERT(0);

//	c->out += sprintf(c->out, "rep ");

	uint8 n = *c->pc++;
	if (n == 0xAB)
	{
//		c->out += sprintf(c->out, "stos");
	}

	return 0;
}

x86instr* x86_cmp_rm32_r32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_CMP(do_rm(c, rm), x86_REG(rm.Reg));
}

x86instr* x86_cmp_r32_rm32(X86Context* c)
{
	c->pc++;
	_rm rm = get_rm(c);
	return x86_CMP(x86_REG(rm.Reg), do_rm(c, rm));
}

x86instr* x86_call(X86Context* c)
{
	c->pc++;
	long offset = *(long*)c->pc;
	c->pc += 4;

	return x86_CALL(x86_IMM(offset));

//	c->out += sprintf(c->out, "call\t");
//	printf("%d", 0x400000 + c->start - c->pc + offset);

	return 0;
}

x86instr* x86_jmp_rel8(X86Context* c)
{
	c->pc++;
	char offset = *(char*)c->pc; c->pc += 1;

	return x86_JMP(x86_IMM(offset));
//	c->out += sprintf(c->out, "jmp\t");
//	printf("%d", 0x400000 + c->start - c->pc + offset);

	return 0;
}

x86instr* x86_jmp_rel32(X86Context* c)
{
	c->pc++;
	long offset = *(long*)c->pc; c->pc += 4;

	return x86_JMP(x86_IMM(offset));

//	c->out += sprintf(c->out, "jmp\t");
//	printf("%d", 0x400000 + c->start - c->pc + offset);

	return 0;
}

x86instr* x86_dec_rd(X86Context* c)
{
	uint8 rd = *c->pc - 0x48; c->pc += 1;
	return x86_DEC(x86_REG(rd));
}

x86instr* x86_FF(X86Context* c)
{
	uint8* reset = c->pc;
	c->pc++;

	_rm rm = get_rm(c);
	if (rm.Reg == 0)
	{
//		do_rm(c);
//		c->out += sprintf(c->out, "inc\t%s", rm32);
		return x86_INC(do_rm(c, rm));
	}
	else if (rm.Reg == 1)
	{
//		do_rm(c);
//		c->out += sprintf(c->out, "dec\t%s", rm32);
		return x86_DEC(do_rm(c, rm));
	}
	else if (rm.Reg == 2)
	{
//		do_rm(c);
//		c->out += sprintf(c->out, "call\t%s", rm32);
		return x86_CALL(do_rm(c, rm));
	}
	else if (rm.Reg == 3)
	{
		return x86_CALL(do_rm(c, rm));
//		do_rm(c);
//		c->out += sprintf(c->out, "call\tm16:32 - %s", rm32);
	}
	else if (rm.Reg == 4)
	{
		return x86_JMP(do_rm(c, rm));
//		do_rm(c);
//		c->out += sprintf(c->out, "jmp\t%s", rm32);
	}
	else if (rm.Reg == 5)
	{
		return x86_JMP(do_rm(c, rm));
//		do_rm(c);
//		c->out += sprintf(c->out, "jmp m16:32\t%s", rm32);
	}
	else if (rm.Reg == 6)
	{
		return x86_PUSH(do_rm(c, rm));
	//	do_rm(c);
//		c->out += sprintf(c->out, "push\t%s", rm32);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}

	return 0;
}

x86instr* x86_ret(X86Context* c)
{
	c->pc++;
	return x86_RET();
//	c->out += sprintf(c->out, "ret");
	return 0;
}

x86instr* x86_ret_imm16(X86Context* c)
{
	c->pc++;
	short imm16 = *(short*)c->pc; c->pc += 2;
//	c->out += sprintf(c->out, "ret\t%d", imm16);

	return x86_RET_IMM16(imm16);
//	ASSERT(0);

	return 0;
}

x86instr* x86_leave(X86Context* c)
{
	c->pc++;
//	c->out += sprintf(c->out, "leave");
	return x86_LEAVE();
	return 0;
}

x86instr* x86_int3(X86Context* c)
{
	c->pc++;
//	c->out += sprintf(c->out, "int\t3");
	return x86_INT(3);
	return 0;
}

x86instr* x86_movoffs(X86Context* c)
{
	c->pc++;
	long data = *(long*)c->pc;
	c->pc += 4;
	return x86_MOV(x86_REG(0), x86_IMM(data));

//	c->out += sprintf(c->out, "mov\tEAX,%d", data);
	return 0;
}

x86instr* x86_mov_moffs8(X86Context* c)
{
	c->pc++;
	long offset = *(long*)c->pc; c->pc += 4;

	return x86_MOV(x86_IMM(offset), x86_REG(0));
}

x86instr* x86_mov_moffs32(X86Context* c)
{
	c->pc++;
	long offset = *(long*)c->pc; c->pc += 4;

	return x86_MOV(x86_IMM(offset), x86_REG(0));
}

x86instr* x86_jb_rel8(X86Context* c)
{
	c->pc++;
	return x86_Jcc(get_imm8(c));
}

x86instr* x86_jz_rel8(X86Context* c)
{
	c->pc++;
	return x86_Jcc(get_imm8(c));
}

x86instr* x86_jl_rel8(X86Context* c)
{
	c->pc++;
	int8 data = *(int8*)c->pc; c->pc += 1;
	return x86_Jcc(data);

//	c->out += sprintf(c->out, "jl\t%d", data);
	return 0;
}

x86instr* x86_jne_rel8(X86Context* c)
{
	c->pc++;
	int8 data = *(int8*)c->pc; c->pc += 1;
	return x86_Jcc(data);
}

x86instr* x86_ja_rel8(X86Context* c)
{
	c->pc++;
	int8 data = *(int8*)c->pc; c->pc += 1;
	return x86_Jcc(data);
}

x86instr* x86_jg_rel8(X86Context* c)
{
	c->pc++;
	int8 data = *(int8*)c->pc; c->pc += 1;
	return x86_Jcc(data);
}

x86instr* x86_jge_rel8(X86Context* c)
{
	c->pc++;
	int8 data = *(int8*)c->pc; c->pc += 1;
	return x86_Jcc(data);
}

x86instr* x86_jle_rel8(X86Context* c)
{
	c->pc++;
	int8 data = *(int8*)c->pc; c->pc += 1;
	return x86_Jcc(data);
}

x86instr* x86_jp_rel8(X86Context* c)
{
	c->pc++;
	int8 data = *(int8*)c->pc; c->pc += 1;
	return x86_Jcc(data);

//	c->out += sprintf(c->out, "jp\t%d", data);
	return 0;
}

x86instr* x86_0F(X86Context* c)
{
	c->pc++;
	uint8 op = *c->pc++;

	switch (op)
	{
	case 0x34:
		{
			return x86_instr(x86instr::K_SYSENTER);
		}
		break;

	case 0xB7:
		{
			_rm rm = get_rm(c);
			return x86_MOVZX(x86_REG(rm.Reg), do_rm(c, rm), 0);
		}
		break;
		
	case 0xBC:
		{
			_rm rm = get_rm(c);
			do_rm(c, rm);
			return x86_instr(x86instr::K_BSF);
			//		c->out += sprintf(c->out, "bsf\t%s,%s", r32, rm32);
		}
		break;
		
	case 0xBE:
		{
			_rm rm = get_rm(c);
			return x86_MOVSX(x86_REG(rm.Reg), do_rm(c, rm), 0);
		}
		break;

	case 0xBF:
		{
			_rm rm = get_rm(c);
			return x86_MOVSX(x86_REG(rm.Reg), do_rm(c, rm), 1);
		}
		break;

	case 0x82:	// JB
		{
			return x86_Jcc(get_imm(c));
		}
		break;

	case 0x84:	// JE
		{
			return x86_Jcc(get_imm(c));
		}
		break;

	case 0x85:	// JNE
		{
			return x86_Jcc(get_imm(c));
		}
		break;

	case 0x86:	// JBE
		{
			return x86_Jcc(get_imm(c));
		}
		break;

	case 0x87:	// JA
		{
			return x86_Jcc(get_imm(c));
		}
		break;

	case 0x8C:	// JL
		{
			return x86_Jcc(get_imm(c));
		}
		break;
		
	default:
		{
			c->pc -= 2;
			return x86_notimpl(c);
		}
	}
	ASSERT(0);
	return NULL;
}

x86instr* x86_C0(X86Context* c)
{
	uint8* revert = c->pc;
	c->pc++;
	_rm rm = get_rm(c);
	if (rm.Reg == 4)
	{
		x86addr* dst = do_rm(c, rm);
		char imm8 = *c->pc++;
//		c->out += sprintf(c->out, "shl\tr/m,%d", imm8);
		return x86_SHL(dst, x86_IMM(imm8));
	}
	else if (rm.Reg == 5)
	{
		x86addr* dst = do_rm(c, rm);
		char imm8 = *c->pc++;
//		c->out += sprintf(c->out, "shr\tr/m,%d", imm8);
		return x86_SHR(dst, x86_IMM(imm8));
	}
	else
	{
		c->pc = revert;
		return x86_notimpl(c);
	}

	return 0;
}

x86instr* x86_div_test(X86Context* c)
{
	uint8* revert = c->pc;

	c->pc++;
	_rm rm = get_rm(c);
	if (rm.Reg == 0)
	{
		x86addr* addr = do_rm(c, rm);
		long data = *(long*)c->pc; c->pc += 4;
//		c->out += sprintf(c->out, "test\t%s,%d", rm32, data);
		return x86_TEST(addr, x86_IMM(data), 0);
	}
	else if (rm.Reg == 2)
	{
		return x86_NOT(do_rm(c, rm));
//		c->out += sprintf(c->out, "not\t%s", rm32);
	}
	else if (rm.Reg == 3)
	{
//		do_rm(c);
//		c->out += sprintf(c->out, "neg\t%s", rm32);
		return x86_NEG(do_rm(c, rm));
	}
	else if (rm.Reg == 6)
	{
		x86addr* dst = do_rm(c, rm);
		long data = *(long*)c->pc; c->pc += 4;
		return x86_DIV(dst);//, x86_IMM(data));
//		c->out += sprintf(c->out, "div\t%s,%d", rm32, data);
	}
	else
	{
		c->pc = revert;
		return x86_notimpl(c);
	}
	return 0;
}

x86instr* x86_movs_8(X86Context* c)
{
	c->pc++;
	return x86_instr(x86instr::K_MOVS);
}

x86instr* x86_movs_32(X86Context* c)
{
	c->pc++;
	return x86_instr(x86instr::K_MOVS);
}

struct
{
	x86_func func;
	void* reserved;
}
x86_ops[256] =
{
	x86_add_rm8_r8, NULL,
	x86_add_rm32_r32, NULL,
	x86_add, NULL,
	x86_add, NULL,
	x86_add, NULL,
	x86_add, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_or_rm32_r32, NULL,
	x86_notimpl, NULL, // 10
	x86_or_r32_rm32, NULL,
	x86_or_al_imm8, NULL,
	x86_or_eax_imm32, NULL,
	x86_notimpl, NULL,
	x86_0F, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_adc_al_imm8, NULL,	// 20
	x86_adc_eax_imm32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_sbb_rm32_r32, NULL,
	x86_notimpl, NULL,
	x86_sbb_r32_rm32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL, // 30
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_and_al_imm8, NULL,
	x86_and_eax_imm32, NULL,	// 37
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 40
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_sub_r32_rm32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_xor_rm8_r8, NULL,
	x86_notimpl, NULL,
	x86_xor_r8_rm8, NULL,	// 50
	x86_xor_r32_rm32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_cmp_rm32_r32, NULL,
	x86_notimpl, NULL,
	x86_cmp_r32_rm32, NULL,
	x86_cmp_al_imm8, NULL,	// 60
	x86_cmp_eax_imm32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 70
	x86_notimpl, NULL,
	x86_dec_rd, NULL,
	x86_dec_rd, NULL,
	x86_dec_rd, NULL,
	x86_dec_rd, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,

	x86_push_r, NULL, // 80
	x86_push_r, NULL,
	x86_push_r, NULL,
	x86_push_r, NULL,
	x86_push_r, NULL,
	x86_push_r, NULL,
	x86_push_r, NULL,
	x86_push_r, NULL,
	x86_pop_r, NULL,	// 88
	x86_pop_r, NULL,
	x86_pop_r, NULL,
	x86_pop_r, NULL,
	x86_pop_r, NULL,
	x86_pop_r, NULL,
	x86_pop_r, NULL,
	x86_pop_r, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 100
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_push_imm32, NULL,
	x86_notimpl, NULL,
	x86_push_imm8, NULL,	// 106
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_jb_rel8, NULL,
	x86_notimpl, NULL,
	x86_jz_rel8, NULL,
	x86_jne_rel8, NULL,	// 117
	x86_notimpl, NULL,
	x86_ja_rel8, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_jp_rel8, NULL,
	x86_notimpl, NULL,
	x86_jl_rel8, NULL,	// 124
	x86_jge_rel8, NULL,
	x86_jle_rel8, NULL,
	x86_jg_rel8, NULL,
	x86_80_r8_imm8, NULL,	// 128
	x86_add_r32_imm32, NULL,
	x86_notimpl, NULL,
	x86_sub_xor_cmp, NULL,	// 131
	x86_test_rm8_r8, NULL,
	x86_test_rm32_r32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_mov_rm32_r32, NULL,
	x86_mov_r8_rm8, NULL,
	x86_mov_r32_rm32, NULL,	// 139
	x86_notimpl, NULL,
	x86_lea, NULL,	// 141
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_nop, NULL,	// Really same as XCHG eax,eax, but this carries more semantics
	x86_xchg_eax_r32, NULL,
	x86_xchg_eax_r32, NULL,
	x86_xchg_eax_r32, NULL,
	x86_xchg_eax_r32, NULL,
	x86_xchg_eax_r32, NULL,
	x86_xchg_eax_r32, NULL,
	x86_xchg_eax_r32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_movoffs, NULL,	// 161
	x86_mov_moffs8, NULL,
	x86_mov_moffs32, NULL,
	x86_movs_8, NULL,
	x86_movs_32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 170
	x86_stos_m32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_scas_m8, NULL,
	x86_scas_m32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 180
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_mov_r32_imm32, NULL,	// 0xB8
	x86_mov_r32_imm32, NULL,
	x86_mov_r32_imm32, NULL,
	x86_mov_r32_imm32, NULL,
	x86_mov_r32_imm32, NULL,
	x86_mov_r32_imm32, NULL,
	x86_mov_r32_imm32, NULL,
	x86_mov_r32_imm32, NULL,
	x86_C0, NULL,
	x86_C1, NULL,
	x86_ret_imm16, NULL,
	x86_ret, NULL,			// 195
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_mov_rm8_imm8, NULL,
	x86_mov_rm32_imm32, NULL,
	x86_notimpl, NULL,	// 200
	x86_leave, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_int3, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_D1, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 220
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_call, NULL,	// 232
	x86_jmp_rel32, NULL,
	x86_notimpl, NULL,
	x86_jmp_rel8, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 240
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_rep, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_div_test, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_FF, NULL,
};

x86instr* disasm_x86(X86Context* c)
{
	c->operand_size = 4;

	int group1 = 0;
	int group2 = 0;
	int group3 = 0;
	int group4 = 0;

	while (1)
	{
		bool bDone = false;

		uint8 byte = *c->pc;
		switch (byte)
		{
		case 0xF0:
		case 0xF2:
		case 0xF3:
		{
			ASSERT(group1 == 0);
			group1 = byte;
		}
		break;

		case 0x2E:
		case 0x36:
		case 0x3E:
		case 0x26:
		case 0x64:
		case 0x65:
			{
				ASSERT(group2 == 0);
				group2 = byte;
			}
			break;

		case 0x66:
			{
				ASSERT(group3 == 0);
				group3 = byte;
				c->operand_size = 2;	// word
			}
			break;

		case 0x67:
			{
				ASSERT(group4 == 0);
				group4 = byte;
			}
			break;

		default:
			bDone = true;
		}

		if (bDone)
			break;

		c->pc++;
	}

//	printf("%7.7d\t", c.pc - code + base);
//	printf("%6.6x\t", c->pc - code + base);
	x86instr* instr = x86_ops[*c->pc].func(c);

	if (group1 == 0xF3)
	{
		return x86_REP(instr);
	}
	else
		return instr;
}

void ReadCode_x86(ULONG_PTR base, uint8* code, long size)
{
#if 0
	printf("\n");
//	test();

	X86Context c;
	c.start = code;
	c.pc = code;
	BYTE* end = code + size;

	while (c.pc < end)
	{
//		disasm_x86
		printf("\n");
	}
#endif
}

//}	// cpp

}	// System
