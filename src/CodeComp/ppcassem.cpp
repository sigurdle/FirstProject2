#include "stdafx.h"
#include "ppcassem.h"
#include "ir.h"

namespace std
{
#include <stdio.h>
}

namespace System
{
using namespace std;

#if WIN32
//#include <sstream>
#else	// for older versions of gcc
//#include <strstream>
#endif

//namespace cpp
//{


const char* names[] =
{
	"tdi",
	"twi",
	"mulli",
	"subfic",
	"cmpli",
	"cmpi",
	"addic",
	"addic.",
	"addi",
	"addis",
	"bc",
	"sc",
	"b",
	"mcrf",
	"bclr",
	"rfid",
	"crnor",
	"crandc",
	"isync",
	"crxor",
	"crnand",
	"crand",
	"creqv",
	"crorc",
	"cror",
	"bcctr",
	"rlwimi",
	"rlwinm",
	"rlwnm",
	"ori",
	"oris",
	"xori",
	"xoris",
	"andi_",
	"andis.",
	"rldicl",
	"rldicr",
	"rldic",
	"rldimi",
	"rldcl",
	"rldcr",
	"cmp",
	"tw",
	"subfco",
	"mulhdu",
	"addco",
	"mulhwu",
	"mfcr",
	"mfocrf",
	"lwarx",
	"ldx",
	"lwzx",
	"slw",
	"cntlzw",
	"sld",
	"and",
	"cmpl",
	"subf",
	"ldux",
	"dcbst",
	"lwzux",
	"cntlzd",
	"andc",
	"td",
	"mulhd",
	"mulhw",
	"mfmsr",
	"ldarx",
	"dcbf",
	"lbzx",
	"neg",
	"lbzux",
	"nor",
	"subfe",
	"adde",
	"mtcrf",
	"mtocrf",
	"mtmsr",
	"stdx",
	"stwcx.",
	"stwx",
	"mtmsrd",
	"stdux",
	"stwux",
	"subfze",
	"addze",
	"mtsr",
	"stdcx.",
	"stbx",
	"subfme",
	"mulld",
	"addme",
	"mullw",
	"mtsrin",
	"dcbtst",
	"stbux",
	"add",
	"dcbt",
	"lhzx",

	"eqv",
	"tlbie",
	"eciwx",
	"lhzux",
	"xor",
	"mfspr",
	"lwax",
	"lhax",
	"tlbia",
	"mftb",
	"lwaux",
	"slbmte",
	"sthx",
	"orc",
	"sradi",
	"slbie",
	"ecowx",
	"sthux",
	"or",
	"divdu",
	"divwu",
	"mtspr",
	"nand",
	"divd",
	"divw",
	"slbia",
	"mcrxr",
	"lswx",
	"lwbrx",
	"lfsx",
	"srw",
	"srd",
	"tlbsync",
	"lfsux",
	"mfsr",
	"lswi",
	"sync",
	"lfdx",
	"lfdux",
	"mfsrin",
	"stswx",
	"stwbrx",
	"stfsx",
	"stfsux",
	"stswi",
	"stfdx",
	"stfdux",
	"lhbrx",
	"sraw",
	"srad",
	"srawi",
	"slbmfev",
	"eieio",
	"slbmfee",
	"sthbrx",
	"extsh",
	"extsb",
	"icbi",

	"stfiwx",
	"extsw",
	"dcbz",
	"lwz",
	"lwzu",
	"lbz",
	"lbzu",
	"stw",
	"stwu",
	"stb",
	"stbu",
	"lhz",
	"lhzu",
	"lha",
	"lhau",
	"sth",
	"sthu",
	"lmw",
	"stmw",
	"lfs",
	"lfsu",
};

ppcinstr* D_(ppcinstr::Kind kind, uint8 RT, uint8 RA, short word)
{
	ppcinstr* p = new ppcinstr(kind);

	p->D.RT = RT;
	p->D.RA = RA;
	p->D.word = word;

	return p;
}

ppcinstr* X_SR(ppcinstr::Kind kind, uint8 RT, uint8 RA, uint8 SR)
{
	ppcinstr* p = new ppcinstr(kind);

	p->X_SR.RT = RT;
	p->X_SR.RA = RA;
	p->X_SR.SR = SR;

	return p;
}

typedef ppcinstr* (*FormFunction)(uint32 dword);

enum
{
	FORM_Invalid,
	FORM_D,
	FORM_B,
	FORM_SC,
	FORM_I,
	FORM_XL,
	FORM_M,
	FORM_31,
};

struct PPC_DWORD
{
	int form;
	char* mnem;
};

extern PPC_DWORD opcd_table[];

ppcinstr* Form_Invalid_Function(uint32 dword)
{
//	TRACE("Invalid");
	return nullptr;
#if 0
//	BYTE opcd = dword & 0x3f;
	BYTE opcd = dword >> 26;//& 0x3f;
	if (opcd == 31)
	{
		short xo = (dword >> 1) & 0x3ff;

		switch (xo)
		{
		case 4:
			{
				TRACE("tw\ttrap word");
			}
			break;

		case 444:
			{
				TRACE("or");
			}
			break;

		case 339:
			{
				TRACE("mfspr");
			}
			break;

		default:
			TRACE("TODO");
		}
	}
	else
	{
		TRACE("Form_Invalid_Function");
	}
#endif
	return 0;
}

ppcinstr* Form_31_Function(uint32 dword)
{
//	BYTE opcd = dword & 0x3f;
	uint8 opcd = dword >> 26;//& 0x3f;
	if (opcd == 31)
	{
		short xo = (dword >> 1) & 0x3ff;

		switch (xo)
		{
		case 0:
			{
				return new ppcinstr(ppcinstr::K_cmp);
			}
			break;

		case 4:
			{
			//	TRACE("tw\ttrap word");
				return new ppcinstr(ppcinstr::K_tw);
			}
			break;

		case 8:
			{
				return new ppcinstr(ppcinstr::K_subfco);
			}
			break;

		case 9:
			{
				return new ppcinstr(ppcinstr::K_mulhdu);
			}
			break;

		case 10:
			{
				return new ppcinstr(ppcinstr::K_addco);
			}
			break;

		case 11:
			{
				return new ppcinstr(ppcinstr::K_mulhwu);
			}
			break;

		case 19:
			{
				return new ppcinstr(ppcinstr::K_mfcr);
			}
			break;

		case 20:
			{
				return new ppcinstr(ppcinstr::K_lwarx);
			}
			break;

		case 21:
			{
				return new ppcinstr(ppcinstr::K_ldx);
			}
			break;

		case 23:
			{
				return new ppcinstr(ppcinstr::K_lwzx);
			}
			break;

		case 40:
			{
				return new ppcinstr(ppcinstr::K_subf);
			}
			break;

		case 266:
			{
				return new ppcinstr(ppcinstr::K_add);
			}
			break;

		case 339:
			{
				return new ppcinstr(ppcinstr::K_mfspr);
			}
			break;

		case 444:
			{
				uint8 RT = (dword >> 21) & 0x1f;
				uint8 SR = (dword >> 16) & 0x1f;
				uint8 RA = (dword >> 11) & 0x1f;

				return X_SR(ppcinstr::K_or, RT, RA, SR);
			//	return new ppcinstr(ppcinstr::K_or);
			}
			break;

		default:
		//	TRACE("xo: %d\n", xo);
			//fflush(stdout);
			return nullptr;
		}
	}
	else
	{
	//	TRACE("Form_Invalid_Function");
	}
	return 0;
}

ppcinstr* Form_D_Function(uint32 dword)
{
	uint8 opcd = dword >> 26;//& 0x3f;
//	uint8 opcd = dword & 0x3f;
	uint8 RT = (dword >> 21) & 0x1f;
	uint8 RA = (dword >> 16) & 0x1f;
	short D = (dword)&0xffff;

	switch (opcd)
	{
	case 2:
		{
			return new ppcinstr(ppcinstr::K_tdi);
		}
		break;

	case 3:
		{
			return new ppcinstr(ppcinstr::K_twi);
		}
		break;

	case 7:
		{
			return new ppcinstr(ppcinstr::K_mulli);
		}
		break;

	case 8:
		{
			return new ppcinstr(ppcinstr::K_subfic);
		}
		break;

	case 10:
		{
			return new ppcinstr(ppcinstr::K_cmpli);
		}
		break;

	case 11:
		{
			return new ppcinstr(ppcinstr::K_cmpi);
		}
		break;

	case 12:
		{
			return new ppcinstr(ppcinstr::K_addic);
		}
		break;

	case 13:
		{
			return new ppcinstr(ppcinstr::K_addic_);
		}
		break;

	case 14:
		{
			return D_(ppcinstr::K_addi, RT, RA, D);
		//	return new ppcinstr(ppcinstr::K_addi);
		}
		break;

	case 15:
		{
			return D_(ppcinstr::K_addi, RT, RA, D);
		//	return new ppcinstr(ppcinstr::K_addis);
		}
		break;

	case 24:
		{
			return new ppcinstr(ppcinstr::K_ori);
		}
		break;

	case 25:
		{
			return new ppcinstr(ppcinstr::K_oris);
		}
		break;

	case 26:
		{
			return new ppcinstr(ppcinstr::K_xori);
		}
		break;

	case 27:
		{
			return new ppcinstr(ppcinstr::K_xoris);
		}
		break;

	case 28:
		{
			return new ppcinstr(ppcinstr::K_andi_);
		}
		break;

	case 29:
		{
			return new ppcinstr(ppcinstr::K_andis_);
		}
		break;

	case 32:
		{
			return new ppcinstr(ppcinstr::K_lwz);
		}
		break;

	case 33:
		{
			return new ppcinstr(ppcinstr::K_lwzu);
		}
		break;

	case 34:
		{
			return new ppcinstr(ppcinstr::K_lbz);
		}
		break;

	case 35:
		{
			return new ppcinstr(ppcinstr::K_lbzu);
		}
		break;

	case 36:
		{
			return D_(ppcinstr::K_stw, RT, RA, D);
			//return new ppcinstr(ppcinstr::K_stw);
		}
		break;

	case 37:
		{
			return D_(ppcinstr::K_stwu, RT, RA, D);
		}
		break;

	case 38:
		{
			return new ppcinstr(ppcinstr::K_stb);
		}
		break;

	case 39:
		{
			return new ppcinstr(ppcinstr::K_stbu);
		}
		break;

	case 40:
		{
			return new ppcinstr(ppcinstr::K_lhz);
		}
		break;

	case 41:
		{
			return new ppcinstr(ppcinstr::K_lhzu);
		}
		break;

	case 42:
		{
			return new ppcinstr(ppcinstr::K_lha);
		}
		break;

	case 43:
		{
			return new ppcinstr(ppcinstr::K_lhau);
		}
		break;

	case 44:
		{
			return new ppcinstr(ppcinstr::K_sth);
		}
		break;

	case 45:
		{
			return new ppcinstr(ppcinstr::K_sthu);
		}
		break;

	case 46:
		{
			return new ppcinstr(ppcinstr::K_lmw);
		}
		break;

	case 47:
		{
			return new ppcinstr(ppcinstr::K_stmw);
		}
		break;

	case 48:
		{
			return new ppcinstr(ppcinstr::K_lfs);
		}
		break;
	}

#if 0
	if (opcd_table[opcd].mnem)
	{
		TRACE("%s\t\t", opcd_table[opcd].mnem);
	}
	else
	{
		if (opcd == FORM_XL)
		{
			switch (opcd)
			{
			default:
				TRACE("-\t\t");
			}
		}
		else
		{
			TRACE("-\t\t");
		}
	}

	TRACE("%d,%d,%d", RT, RA, D);
#endif

	return 0;
}

ppcinstr* Form_branch_Function(uint32 dword)
{
	return new ppcinstr(ppcinstr::K_bc);
}

ppcinstr* Form_SC_Function(uint32 dword)
{
//	TRACE("SC");
	return 0;
}

ppcinstr* Form_I_Function(uint32 dword)
{
	uint8 opcd = dword >> 26;

	switch (opcd)
	{
	case 18:
		{
			return new ppcinstr(ppcinstr::K_b);
		}
		break;
	default:
		ASSERT(0);
	}

//	TRACE("I");
	return 0;
}

ppcinstr* Form_XL_Function(uint32 dword)
{
	uint8 opcd = dword >> 26;
	uint8 bo = (dword >> 21) & 0x1f;
	uint8 bi = (dword >> 16) & 0x1f;
	short xo = (dword >> 1) & 0x3ff;
	uint8 LK = (dword >> 0) & 0x1;

	switch (xo)
	{
	case 0:
		return new ppcinstr(ppcinstr::K_mcrf);
		break;

	case 16:
		{
			/*
			if ((bo & 0x4) && (bo & 0x10))
			{
				TRACE("blr\tbranch always");
				if (LK)
					TRACE(", and put return address in LR");
			}
			else
			*/
			{
//				TRACE("bclr[l]");
				if (LK)
;//					TRACE(", and put return address in LR");
				return new ppcinstr(ppcinstr::K_bclr);
			}
		}
		break;

	case 18:
		return new ppcinstr(ppcinstr::K_rfid);
		break;

	default:
//		TRACE("Invalid");
		;
	}

	return 0;
}

ppcinstr* Form_M_Function(uint32 dword)
{
//	TRACE("M");
	return 0;
}

FormFunction FormFunctions[] =
{
	Form_Invalid_Function,
	Form_D_Function,
	Form_branch_Function,
	Form_SC_Function,
	Form_I_Function,
	Form_XL_Function,
	Form_M_Function,
	Form_31_Function,
};

PPC_DWORD opcd_table[64] =
{
	{FORM_Invalid, NULL},
	{FORM_Invalid, NULL},
	{FORM_D, "tdi"},
	{FORM_D, "twi"},
	{FORM_Invalid, NULL},
	{FORM_Invalid, NULL},
	{FORM_Invalid, NULL},
	{FORM_D, "mulli"},
	{FORM_D, "subfic"},
	{FORM_Invalid, NULL},
	{FORM_D, "cmpli"},
	{FORM_D, "cmpi"},
	{FORM_D, "addic"},
	{FORM_D, "addic."},
	{FORM_D, "addi"},
	{FORM_D, "addis"},
	{FORM_B, "bc"},
	{FORM_SC, "sc"},
	{FORM_I, "b"},
	{FORM_XL,	 NULL},// 19
	{FORM_M, "rlwimi"},
	{FORM_M, "rlwinm"},
	{FORM_Invalid, NULL},
	{FORM_M, "rlwnm"},
	{FORM_D, "ori"},// OR Immediate
	{FORM_D, "oris"},// OR Immediate Shifted
	{FORM_D, "xori"},// XOR Immediate
	{FORM_D, "xoris"},// XOR Immediate Shifted
	{FORM_D, "andi."},// AND Immediate
	{FORM_D, "andis."},// AND Immediate Shifted};
	{FORM_Invalid, NULL},
	{FORM_31, NULL},
	{FORM_D, "lwz"},// Load Word and Zero
	{FORM_D, "lwzu"},// Load Word and Zero with Update
	{FORM_D, "lbz"},// Load Byte and Zero
	{FORM_D, "lbzu"},// Load Byte and Zero with Update
	{FORM_D, "stw"},// Store Word	// 36
	{FORM_D, "stwu"},// Store Word with Update
	{FORM_D, "stb"},// Store Byte
	{FORM_D, "stbu"},// Store Byte with Update
	{FORM_D, "lhz"},// Load Halfword and Zero
	{FORM_D, "lhzu"},// Load Halfword and Zero with Update
	{FORM_D, "lha"},// Load Halfword Algebraic
	{FORM_D, "lhau"},// Load Halfword Algebraic with Update
	{FORM_D, "sth"},// Store Halfword
	{FORM_D, "sthu"},// Store Halfword with Update
	{FORM_D, "lmw"},// Load Multiple Word
	{FORM_D, "stmw"},// Store Multiple Word
	{FORM_D, "lfs"},// Load Floating-Point Single
	{FORM_D, "lfsu"},// Load Floating-Point Single with Update
	{FORM_D, "lfd"},// Load Floating-Point Double
	{FORM_D, "lfdu"},// Load Floating-Point Double with Update
	{FORM_D, "stfs"},// Store Floating-Point Single
	{FORM_D, "stfsu"},// Store Floating-Point Single with Update};
};

String toString(const ppcinstr* p)
{
	ASSERT(p != NULL);

	IO::StringWriter out;//(buffer, 256);

	ASSERT(p->kind >= 0 && p->kind < sizeof(names) / sizeof(char*));

	out << names[p->kind];

	out << "\t";

	switch (p->kind)
	{
	case ppcinstr::K_bc:
		{
		}
		break;

	case ppcinstr::K_addi:
		{
			out << "r" << (int)p->D.RT;
			out << ",";
			out << "r" << (int)p->D.RA;
			out << ",";
			out << p->D.word;
		}
		break;

	case ppcinstr::K_addis:
		{
			out << "r" << (int)p->D.RT;
			out << ",";
			out << "r" << (int)p->D.RA;
			out << ",";
			out << p->D.word;
		}
		break;

	case ppcinstr::K_stw:
	case ppcinstr::K_stwu:
		{
			out << "r" << (int)p->D.RT;
			out << ",";
			out << p->D.word << "(r" << (int)p->D.RA << ")";
		}
		break;

	case ppcinstr::K_or:
		{
			out << "r" << (int)p->X_SR.SR;
			out << ",";
			out << "r" << (int)p->X_SR.RT;
			out << ",";
			out << "r" << (int)p->X_SR.RA;
		}
		break;
	}

//	std::string str = out.str();
	return out.str();
}

CodeCompExt ppcinstr* disasm_ppc(ppcContext* c)
{
	uint32 dword = BigEndian32(*(uint32*)c->pc);
	uint8 opcd = dword >> 26;
	ppcinstr* instr = FormFunctions[opcd_table[opcd].form](dword);
	c->pc += 4;
	return instr;
}

#if 0
void dasm_powerpc(BYTE* text, ULONG addr, ULONG size, int nsymbols, nlist* Symbols)
{
	BYTE* end = text + size;
	BYTE *pc = text;

	while (pc < end)
	{
		DWORD dword = ENDIANLONG(*(DWORD*)pc);

		for (int i = 0; i < nsymbols; i++)
		{
			nlist* pSymbol = &Symbols[i];//ofile->GetSymbol(i);

			//if ((pSymbol->n_type & N_TYPE) == N_TEXT)
			{
				if (pSymbol->n_value-addr == pc-text)
				{
				//	symnode = pSymbol;//&Symbols[i];
					TRACE("%s:\n", pSymbol->n_un.n_name);
				//	break;
				}
			}
		}

		TRACE("%8.8X\t", dword);

	//	BYTE opcd = dword & 0x3f;
		BYTE opcd = dword >> 26;//& 0x3f;

		ppcinstr* instr = FormFunctions[opcd_table[opcd].form](dword);

		if (instr)
		{
			StringA str = toString(instr);
			TRACE("%s", str.c_str());
		}

		TRACE("\n");

		pc += 4;
	}
}
#endif

void assem(ppcinstr* assem, FILE* file)
{
}

}

//}	// cpp
