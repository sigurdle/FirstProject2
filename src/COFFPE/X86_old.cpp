#include "StdAfx.h"
#include "X86.h"

//extern "C" void test();

typedef int (*x86_func)(CX86Context* c);

int x86_notimpl(CX86Context* c)
{
//	c->out += sprintf(c->out, "\top not implemented");
//	c->pc++;
	return 0;
}

char* RegName_rd[] =
{
	"EAX",
	"ECX",
	"EDX",
	"EBX",
	"ESP",
	"EBP",
	"ESI",
	"EDI",
};

static char r32[16];
static char rm32[512];
static BYTE RM;
static BYTE Reg;
static BYTE Mod;
static long disp32;

void get_rm(CX86Context* c)
{
	BYTE ModRM =  *c->pc++;
	RM = ModRM & 0x7;
	Reg = (ModRM>>3) & 0x7;
	Mod = (ModRM>>6);
}


void do_rm(CX86Context* c)
{
	switch (Mod)
	{
	case 0:
		{
			if (RM == 5)
			{
				disp32 = *(DWORD*)c->pc;
				c->pc += 4;

				sprintf(r32, "%s", RegName_rd[Reg]);
				sprintf(rm32, "dword ptr ds:[0%8.8Xh]", /*RegName_rd[RM],*/ disp32);
			}
			else
			{
			//	ATLASSERT(0);
				sprintf(r32, "%s", RegName_rd[Reg]);
				sprintf(rm32, "[%s]", RegName_rd[RM]);
			}
		}
		break;

	case 1:
		{
			char disp8 = *c->pc++;
			sprintf(r32, "%s", RegName_rd[Reg]);
			sprintf(rm32, "%s+%d", RegName_rd[RM], disp8);
		}
		break;

	case 2:
		{
			long disp32 = *(DWORD*)c->pc;
			c->pc += 4;

			sprintf(r32, "%s", RegName_rd[Reg]);
			sprintf(rm32, "%s+%d", RegName_rd[RM], disp32);
		}
		break;

	case 3:
		{
			sprintf(r32, "%s", RegName_rd[Reg]);
			sprintf(rm32, "%s", RegName_rd[RM]);
		}
		break;
	}
}

void rm(CX86Context* c)
{
	get_rm(c);
	do_rm(c);
}

/////////////////////////////////////////////////////

int x86_add_rm8_r8(CX86Context* c)
{
	c->pc++;
	rm(c);
	// TODO, print as 8bit
	c->out += sprintf(c->out, "add\t%s,%s", rm32, r32);
	return 0;
}

int x86_add_rm32_r32(CX86Context* c)
{
	c->pc++;
	rm(c);
	c->out += sprintf(c->out, "add\t%s,%s", rm32, r32);
	return 0;
}

int x86_add(CX86Context* c)
{
	c->pc++;
	rm(c);
	/*
	BYTE ModRM =  *c->pc++;
	BYTE RM = ModRM & 0x7;
	BYTE Reg = (ModRM>>3) & 0x7;
	BYTE Mod = (ModRM>>6);
	*/

	c->out += sprintf(c->out, "add\t%s,%s", r32, rm32);

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

int x86_or_al_imm8(CX86Context* c)
{
	c->pc++;
	char value = *c->pc++;

	c->out += sprintf(c->out, "or\tAL,%d", value);
	return 0;
}

int x86_or_r32_rm32(CX86Context* c)
{
	c->pc++;
	rm(c);
	c->out += sprintf(c->out, "or\t%s,%s", r32, rm32);

	return 0;
}

int x86_sbb_r32_rm32(CX86Context* c)
{
	c->pc++;
	rm(c);
	c->out += sprintf(c->out, "sbb\t%s,%s", r32, rm32);

	return 0;
}

int x86_xor_rm8_r8(CX86Context* c)
{
	c->pc++;
	rm(c);
	// TODO, print out as 8bit ?
	c->out += sprintf(c->out, "xor\t%s,%s", r32, rm32);

	return 0;
}

int x86_xor_r32_rm32(CX86Context* c)
{
	c->pc++;
	rm(c);
	c->out += sprintf(c->out, "xor\t%s,%s", r32, rm32);

	return 0;
}

int x86_and_al_imm8(CX86Context* c)
{
	c->pc++;
	char value = *c->pc++;

	c->out += sprintf(c->out, "and\tAL,%d", value);
	return 0;
}

int x86_or_eax_imm32(CX86Context* c)
{
	c->pc++;
	long value = *(long*)c->pc;
	c->pc += 4;

	c->out += sprintf(c->out, "or\tEAX,%d", value);
	return 0;
}

int x86_shl_shr(CX86Context* c)
{
	BYTE* reset = c->pc;
	c->pc++;
	get_rm(c);
	if (Reg == 4)
	{
		do_rm(c);
		c->out += sprintf(c->out, "shl\t%s", rm32);
	}
	else if (Reg == 5)
	{
		do_rm(c);
		c->out += sprintf(c->out, "shr\t%s", rm32);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}

	return 0;
}

int x86_scas_m8(CX86Context* c)
{
	c->pc++;
	c->out += sprintf(c->out, "scasb\t");
	return 0;
}

int x86_scas_m32(CX86Context* c)
{
	c->pc++;
	if (TRUE)
		c->out += sprintf(c->out, "scasd\t");
	else
		c->out += sprintf(c->out, "scasw\t");
	return 0;
}

int x86_adc(CX86Context* c)
{
	c->pc++;
	c->out += sprintf(c->out, "adc\t");
	return 0;
}

int x86_add_r8_imm8(CX86Context* c)
{
	c->pc++;
	get_rm(c);
	char data = *(char*)c->pc; c->pc += 1;
	c->out += sprintf(c->out, "add\t%s,%d", RegName_rd[Reg], data);
	return 0;
}

int x86_C1(CX86Context* c)
{
	BYTE* reset = c->pc;

	c->pc++;
	get_rm(c);
	if (Reg == 1)
	{
		do_rm(c);
		char imm8 = *(char*)c->pc; c->pc += 1;

		c->out += sprintf(c->out, "ror\t%s,%d", rm32, imm8);
	}
	else if (Reg == 4)
	{
		do_rm(c);
		char imm8 = *(char*)c->pc; c->pc += 1;

		c->out += sprintf(c->out, "shl\t%s,%d", rm32, imm8);
	}
	else if (Reg == 5)
	{
		do_rm(c);
		char imm8 = *(char*)c->pc; c->pc += 1;

		c->out += sprintf(c->out, "shr\t%s,%d", rm32, imm8);
	}
	else if (Reg == 7)
	{
		do_rm(c);
		char imm8 = *(char*)c->pc; c->pc += 1;

		c->out += sprintf(c->out, "sar\t%s,%d", rm32, imm8);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}

	return 0;
}

int x86_add_r32_imm32(CX86Context* c)
{
	BYTE* reset = c->pc;

	c->pc++;
	get_rm(c);
	if (Reg == 0)
	{
		do_rm(c);
		long imm32 = *(long*)c->pc; c->pc += 4;

		c->out += sprintf(c->out, "add\t%s,%d", rm32, imm32);
	}
	else if (Reg == 1)
	{
		do_rm(c);
		long imm32 = *(long*)c->pc; c->pc += 4;

		c->out += sprintf(c->out, "adc\t%s,%d", rm32, imm32);
	}
	else if (Reg == 4)
	{
		do_rm(c);
		long imm32 = *(long*)c->pc; c->pc += 4;

		c->out += sprintf(c->out, "and\t%s,%d", rm32, imm32);
	}
	else if (Reg == 5)
	{
		do_rm(c);
		long imm32 = *(long*)c->pc; c->pc += 4;

		c->out += sprintf(c->out, "sub\t%s,%d", rm32, imm32);
	}
	else if (Reg == 7)
	{
		do_rm(c);
		long imm32 = *(long*)c->pc; c->pc += 4;

		c->out += sprintf(c->out, "cmp\t%s,%d", rm32, imm32);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}
	return 0;
}

int x86_and_eax_imm32(CX86Context* c)
{
	c->pc++;
	long imm32 = *(long*)c->pc; c->pc += 4;

	c->out += sprintf(c->out, "and\tEAX,%d", imm32);
	return 0;
}

int x86_push_r(CX86Context* c)
{
	int reg = *c->pc - 0x50;
	c->out += sprintf(c->out, "push\t");
	c->out += sprintf(c->out, "%s", RegName_rd[reg]);

	c->pc++;
	return 0;
}

int x86_push_imm8(CX86Context* c)
{
	c->pc++;
	char value = *c->pc++;

	c->out += sprintf(c->out, "push\t");
	c->out += sprintf(c->out, "%d", value);

	return 0;
}

int x86_push_imm32(CX86Context* c)
{
	c->pc++;
	long value = *(long*)c->pc;
	c->pc += 4;

	c->out += sprintf(c->out, "push\t");
	c->out += sprintf(c->out, "%d", value);

	return 0;
}

int x86_pop_r(CX86Context* c)
{
	int reg = *c->pc - 0x58;
	c->out += sprintf(c->out, "pop\t");
	c->out += sprintf(c->out, "%s", RegName_rd[reg]);

	c->pc++;
	return 0;
}

int x86_sub_xor_cmp(CX86Context* c)
{
	BYTE* revert = c->pc;

	c->pc++;
	get_rm(c);

	BYTE imm8 = *c->pc++;

	switch (Reg)
	{
	case 0:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "add\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 1:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "or\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 2:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "adc\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 3:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "sbb\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 4:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "and\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;

	case 5:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "sub\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;
		
	case 6:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "xor\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
		}
		break;
		
	case 7:
		{
			do_rm(c);
			
			c->out += sprintf(c->out, "cmp\t");
			c->out += sprintf(c->out, "%s,%x", rm32, imm8);
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

int x86_stos_m32(CX86Context* c)
{
	c->pc++;
	c->out += sprintf(c->out, "stos\tm32");

	return 0;
}


int x86_test_rm32_r32(CX86Context* c)
{
	c->pc++;
	rm(c);

	c->out += sprintf(c->out, "test\t%s,%s", rm32, r32);

	return 0;
}

int x86_mov_r8_rm8(CX86Context* c)
{
	c->pc++;
	rm(c);

// TODO, show as 8-bit
	c->out += sprintf(c->out, "mov\t%s,%s", r32, rm32);

	return 0;
}

int x86_mov_r32_rm32(CX86Context* c)
{
	c->pc++;
	rm(c);

	c->out += sprintf(c->out, "mov\t%s,%s", r32, rm32);

	return 0;
}

int x86_mov_rm32_r32(CX86Context* c)
{
	c->pc++;
	rm(c);

	c->out += sprintf(c->out, "mov\t%s,%s", rm32, r32);

	return 0;
}

int x86_mov_r32_imm32(CX86Context* c)
{
	int r32 = *c->pc - 0xB8;
	c->pc++;

	DWORD imm32 = *(DWORD*)c->pc;
	c->pc += 4;

	c->out += sprintf(c->out, "mov\t");
	c->out += sprintf(c->out,"%s,%X", RegName_rd[r32], imm32);

	return 0;
}

int x86_mov_rm32_imm32(CX86Context* c)
{
	c->pc++;
	rm(c);
	if (Reg == 0)
	{
		DWORD imm32 = *(DWORD*)c->pc;
		c->pc += 4;

		c->out += sprintf(c->out, "mov\t%s,%d", rm32, imm32);

		return 0;
	}

	return -1;
}

int x86_lea(CX86Context* c)
{
	c->pc++;
	BYTE ModRM =  *c->pc++;
	BYTE RM = ModRM & 0x7;
	BYTE Reg = (ModRM>>3) & 0x7;
	BYTE Mod = (ModRM>>6);
	//if (TRUE)
	BYTE SIB = *c->pc++;

	c->out += sprintf(c->out, "lea\t");
	c->out += sprintf(c->out, "%s,[%s]", RegName_rd[Reg], RegName_rd[RM]);

	return 0;
}

int x86_rep(CX86Context* c)
{
	c->pc++;

	c->out += sprintf(c->out, "rep ");

	BYTE n = *c->pc++;
	if (n == 0xAB)
	{
		c->out += sprintf(c->out, "stos");
	}

	return 0;
}

int x86_cmp_r32_rm32(CX86Context* c)
{
	c->pc++;
	rm(c);

	c->out += sprintf(c->out, "cmp\t%s,%s", r32, rm32);

	return 0;
}

int x86_call(CX86Context* c)
{
	c->pc++;
	long offset = *(long*)c->pc;
	c->pc += 4;

	c->out += sprintf(c->out, "call\t");
//	printf("%d", 0x400000 + c->start - c->pc + offset);

	return 0;
}

int x86_jmp_rel8(CX86Context* c)
{
	c->pc++;
	char offset = *(char*)c->pc;
	c->pc += 4;

	c->out += sprintf(c->out, "jmp\t");
//	printf("%d", 0x400000 + c->start - c->pc + offset);

	return 0;
}

int x86_jmp_rel32(CX86Context* c)
{
	c->pc++;
	long offset = *(long*)c->pc;
	c->pc += 4;

	c->out += sprintf(c->out, "jmp\t");
//	printf("%d", 0x400000 + c->start - c->pc + offset);

	return 0;
}

int x86_FF(CX86Context* c)
{
	BYTE* reset = c->pc;
	c->pc++;

	get_rm(c);
	if (Reg == 0)
	{
		do_rm(c);
		c->out += sprintf(c->out, "inc\t%s", rm32);
	}
	else if (Reg == 1)
	{
		do_rm(c);
		c->out += sprintf(c->out, "dec\t%s", rm32);
	}
	else if (Reg == 2)
	{
		do_rm(c);
		c->out += sprintf(c->out, "call\t%s", rm32);
	}
	else if (Reg == 3)
	{
		do_rm(c);
		c->out += sprintf(c->out, "call\tm16:32 - %s", rm32);
	}
	else if (Reg == 4)
	{
		do_rm(c);
		c->out += sprintf(c->out, "jmp\t%s", rm32);
	}
	else if (Reg == 5)
	{
		do_rm(c);
		c->out += sprintf(c->out, "jmp m16:32\t%s", rm32);
	}
	else if (Reg == 6)
	{
		do_rm(c);
		c->out += sprintf(c->out, "push\t%s", rm32);
	}
	else
	{
		c->pc = reset;
		return x86_notimpl(c);
	}

	return 0;
}

int x86_ret(CX86Context* c)
{
	c->pc++;
	c->out += sprintf(c->out, "ret");
	return 0;
}

int x86_ret_imm16(CX86Context* c)
{
	c->pc++;
	short imm16 = *(short*)c->pc; c->pc += 2;
	c->out += sprintf(c->out, "ret\t%d", imm16);

	return 0;
}

int x86_leave(CX86Context* c)
{
	c->pc++;
	c->out += sprintf(c->out, "leave");
	return 0;
}

int x86_int3(CX86Context* c)
{
	c->pc++;
	c->out += sprintf(c->out, "int\t3");
	return 0;
}

int x86_movoffs(CX86Context* c)
{
	c->pc++;
	long data = *(long*)c->pc;
	c->pc += 4;

	c->out += sprintf(c->out, "mov\tEAX,%d", data);
	return 0;
}

int x86_mov_moffs8(CX86Context* c)
{
	c->pc++;
	char data = *(char*)c->pc; c->pc += 1;

	c->out += sprintf(c->out, "mov moffs\t%d,AL", data);
	return 0;
}

int x86_mov_moffs32(CX86Context* c)
{
	c->pc++;
	long data = *(long*)c->pc; c->pc += 4;

	c->out += sprintf(c->out, "mov moffs\t%d,EAX", data);
	return 0;
}

int x86_jz_rel8(CX86Context* c)
{
	c->pc++;
	char data = *(char*)c->pc; c->pc += 1;

	c->out += sprintf(c->out, "jz\t%d", data);
	return 0;
}

int x86_jl_rel8(CX86Context* c)
{
	c->pc++;
	char data = *(char*)c->pc; c->pc += 1;

	c->out += sprintf(c->out, "jl\t%d", data);
	return 0;
}

int x86_jne_rel8(CX86Context* c)
{
	c->pc++;
	char data = *(char*)c->pc; c->pc += 1;

	c->out += sprintf(c->out, "jne\t%d", data);
	return 0;
}

int x86_jge_rel8(CX86Context* c)
{
	c->pc++;
	char data = *(char*)c->pc; c->pc += 1;

	c->out += sprintf(c->out, "jge\t%d", data);
	return 0;
}

int x86_jp_rel8(CX86Context* c)
{
	c->pc++;
	char data = *(char*)c->pc; c->pc += 1;

	c->out += sprintf(c->out, "jp\t%d", data);
	return 0;
}

int x86_0F(CX86Context* c)
{
	if (c->pc[1] == 0xBC)
	{
		c->pc += 2;

		rm(c);
		c->out += sprintf(c->out, "bsf\t%s,%s", r32, rm32);
	}
	else if (c->pc[1] == 0xBE)
	{
		c->pc += 2;

		rm(c);
		c->out += sprintf(c->out, "movsx\t%s,%s", r32, rm32);
	}
	else if (c->pc[1] == 0x85)
	{
		c->pc += 2;

		long rel32 = *(long*)c->pc; c->pc += 4;
		c->out += sprintf(c->out, "jne\t%d", rel32);
	}
	else if (c->pc[1] == 0x87)
	{
		c->pc += 2;

		long rel32 = *(long*)c->pc; c->pc += 4;
		c->out += sprintf(c->out, "ja\t%d", rel32);
	}
	else
	{
		return x86_notimpl(c);
	}
	return 0;
}

int x86_C0(CX86Context* c)
{
	BYTE* revert = c->pc;
	c->pc++;
	get_rm(c);
	if (Reg == 4)
	{
		do_rm(c);
		char imm8 = *c->pc++;
		c->out += sprintf(c->out, "shl\tr/m,%d", imm8);
	}
	else if (Reg == 5)
	{
		do_rm(c);
		char imm8 = *c->pc++;
		c->out += sprintf(c->out, "shr\tr/m,%d", imm8);
	}
	else
	{
		c->pc = revert;
		return x86_notimpl(c);
	}

	return 0;
}

int x86_div_test(CX86Context* c)
{
	BYTE* revert = c->pc;

	c->pc++;
	get_rm(c);
	if (Reg == 0)
	{
		do_rm(c);
		long data = *(long*)c->pc; c->pc += 4;
		c->out += sprintf(c->out, "test\t%s,%d", rm32, data);
	}
	else if (Reg == 2)
	{
		do_rm(c);
		c->out += sprintf(c->out, "not\t%s", rm32);
	}
	else if (Reg == 3)
	{
		do_rm(c);
		c->out += sprintf(c->out, "neg\t%s", rm32);
	}
	else if (Reg == 6)
	{
		do_rm(c);
		long data = *(long*)c->pc; c->pc += 4;
		c->out += sprintf(c->out, "div\t%s,%d", rm32, data);
	}
	else
	{
		c->pc = revert;
		return x86_notimpl(c);
	}
	return 0;
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
	x86_notimpl, NULL,
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
	x86_adc, NULL,	// 20
	x86_adc, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
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
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_xor_rm8_r8, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,	// 50
	x86_xor_r32_rm32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_cmp_r32_rm32, NULL,
	x86_notimpl, NULL,	// 60
	x86_notimpl, NULL,
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
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
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
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_jz_rel8, NULL,
	x86_jne_rel8, NULL,	// 117
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_jp_rel8, NULL,
	x86_notimpl, NULL,
	x86_jl_rel8, NULL,	// 124
	x86_jge_rel8, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_add_r8_imm8, NULL,	// 128
	x86_add_r32_imm32, NULL,
	x86_notimpl, NULL,
	x86_sub_xor_cmp, NULL,	// 131
	x86_notimpl, NULL,
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
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_movoffs, NULL,	// 161
	x86_mov_moffs8, NULL,
	x86_mov_moffs32, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
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
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_C0, NULL,
	x86_C1, NULL,
	x86_ret_imm16, NULL,
	x86_ret, NULL,			// 195
	x86_notimpl, NULL,
	x86_notimpl, NULL,
	x86_notimpl, NULL,
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
	x86_shl_shr, NULL,
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

int disasm_x86(CX86Context* c)
{
	while (1)
	{
		BOOL bDone = FALSE;

		BYTE byte = *c->pc;
		switch (byte)
		{
		case 0xF0:
		case 0xF2:
		case 0xF3:
		{
		}
		break;

		case 0x2E:
		case 0x36:
		case 0x3E:
		case 0x26:
		case 0x64:
		case 0x65:
	//	case 0x2E:
	//	case 0x3E:
			{
			}
			break;

		case 0x66:
			{
			}
			break;

		case 0x67:
			{
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
	x86_ops[*c->pc].func(c);

	return 0;
}

void ReadCode_x86(DWORD base, BYTE* code, long size)
{
#if 0
	printf("\n");
//	test();

	CX86Context c;
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
