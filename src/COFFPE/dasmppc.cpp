#include "StdAfx.h"

#include "../Include/stab.h"

#include "../LFC/disasm.h"

//#include <sstream>

using namespace System;

namespace cpp
{

class ppcinstr : public MInstruction
{
public:
	enum Kind
	{
		K_tdi,
		K_twi,
		K_mulli,
		K_subfic,
		K_cmpli,
		K_cmpi,
		K_addic,
		K_addic_,
		K_addi,
		K_addis,
		K_bc,
		K_sc,
		K_b,
		K_mcrf,
		K_bclr,
		K_rfid,
		K_crnor,
		K_crandc,
		K_isync,
		K_crxor,
		K_crnand,
		K_crand,
		K_creqv,
		K_crorc,
		K_cror,
		K_bcctr,
		K_rlwimi,
		K_rlwinm,
		K_rlwnm,
		K_ori,
		K_oris,
		K_xori,
		K_xoris,
		K_andi_,
		K_andis_,
		K_rldicl,
		K_rldicr,
		K_rldic,
		K_rldimi,
		K_rldcl,
		K_rldcr,
		K_cmp,
		K_tw,
		K_subfco,
		K_mulhdu,
		K_addco,
		K_mulhwu,
		K_mfcr,
		K_mfocrf,
		K_lwarx,
		K_ldx,
		K_lwzx,
		K_slw,
		K_cntlzw,
		K_sld,
		K_and,
		K_cmpl,
		K_subf,
		K_ldux,
		K_dcbst,
		K_lwzux,
		K_cntlzd,
		K_andc,
		K_td,
		K_mulhd,
		K_mulhw,
		K_mfmsr,
		K_ldarx,
		K_dcbf,
		K_lbzx,
		K_neg,
		K_lbzux,
		K_nor,
		K_subfe,
		K_adde,
		K_mtcrf,
		K_mtocrf,
		K_mtmsr,
		K_stdx,
		K_stwcx_,
		K_stwx,
		K_mtmsrd,
		K_stdux,
		K_stwux,
		K_subfze,
		K_addze,
		K_mtsr,
		K_stdcx_,
		K_stbx,
		K_subfme,
		K_mulld,
		K_addme,
		K_mullw,
		K_mtsrin,
		K_dcbtst,
		K_stbux,
		K_add,
		K_dcbt,
		K_lhzx,

		K_eqv,
		K_tlbie,
		K_eciwx,
		K_lhzux,
		K_xor,
		K_mfspr,
		K_lwax,
		K_lhax,
		K_tlbia,
		K_mftb,
		K_lwaux,
		K_slbmte,
		K_sthx,
		K_orc,
		K_sradi,
		K_slbie,
		K_ecowx,
		K_sthux,
		K_or,
		K_divdu,
		K_divwu,
		K_mtspr,
		K_nand,
		K_divd,
		K_divw,
		K_slbia,
		K_mcrxr,
		K_lswx,
		K_lwbrx,
		K_lfsx,
		K_srw,
		K_srd,
		K_tlbsync,
		K_lfsux,
		K_mfsr,
		K_lswi,
		K_sync,
		K_lfdx,
		K_lfdux,
		K_mfsrin,
		K_stswx,
		K_stwbrx,
		K_stfsx,
		K_stfsux,
		K_stswi,
		K_stfdx,
		K_stfdux,
		K_lhbrx,
		K_sraw,
		K_srad,
		K_srawi,
		K_slbmfev,
		K_eieio,
		K_slbmfee,
		K_sthbrx,
		K_extsh,
		K_extsb,
		K_icbi,

		K_stfiwx,
		K_extsw,
		K_dcbz,
		K_lwz,
		K_lwzu,
		K_lbz,
		K_lbzu,
		K_stw,
		K_stwu,
		K_stb,
		K_stbu,
		K_lhz,
		K_lhzu,
		K_lha,
		K_lhau,
		K_sth,
		K_sthu,
		K_lmw,
		K_stmw,
		K_lfs,
		K_lfsu,
	}
	kind;

	ppcinstr(Kind _kind)
	{
		kind = _kind;
	}

	union
	{
		struct
		{
			uint8 RT;
			uint8 RA;
			short word;
		}
		D;

		struct
		{
			uint8 RT;
			uint8 RA;
			uint8 SR;
		}
		X_SR;
	};
};

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

ppcinstr* Form_Invalid_Function(DWORD dword)
{
	printf("Invalid");
	return NULL;
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
				printf("tw\ttrap word");
			}
			break;

		case 444:
			{
				printf("or");
			}
			break;

		case 339:
			{
				printf("mfspr");
			}
			break;

		default:
			printf("TODO");
		}
	}
	else
	{
		printf("Form_Invalid_Function");
	}
#endif
	return 0;
}

ppcinstr* Form_31_Function(DWORD dword)
{
//	BYTE opcd = dword & 0x3f;
	uint8 opcd = dword >> 26;//& 0x3f;
	if (opcd == 31)
	{
		short xo = (dword >> 1) & 0x3ff;

		switch (xo)
		{
		case 4:
			{
				printf("tw\ttrap word");
				return new ppcinstr(ppcinstr::K_tw);
			}
			break;

		case 339:
			{
				return new ppcinstr(ppcinstr::K_mfspr);
			//	printf("mfspr");
			//	return NULL;
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
			printf("TODO");
			return NULL;
		}
	}
	else
	{
		printf("Form_Invalid_Function");
	}
	return 0;
}

ppcinstr* Form_D_Function(DWORD dword)
{
	uint8 opcd = dword >> 26;//& 0x3f;
//	BYTE opcd = dword & 0x3f;
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
			return new ppcinstr(ppcinstr::K_addi);
		}
		break;

	case 15:
		{
			return new ppcinstr(ppcinstr::K_addis);
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
		printf("%s\t\t", opcd_table[opcd].mnem);
	}
	else
	{
		if (opcd == FORM_XL)
		{
			switch (opcd)
			{
			default:
				printf("-\t\t");
			}
		}
		else
		{
			printf("-\t\t");
		}
	}

	printf("%d,%d,%d", RT, RA, D);
#endif

	return 0;
}

ppcinstr* Form_B_Function(DWORD dword)
{
	printf("B");
	return 0;
}

ppcinstr* Form_SC_Function(DWORD dword)
{
	printf("SC");
	return 0;
}

ppcinstr* Form_I_Function(DWORD dword)
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

//	printf("I");
	return 0;
}

ppcinstr* Form_XL_Function(DWORD dword)
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
				printf("blr\tbranch always");
				if (LK)
					printf(", and put return address in LR");
			}
			else
			*/
			{
				printf("bclr[l]");
				if (LK)
					printf(", and put return address in LR");
				return new ppcinstr(ppcinstr::K_bclr);
			}
		}
		break;

	case 18:
		return new ppcinstr(ppcinstr::K_rfid);
		break;

	default:
		printf("Invalid");
	}

	return 0;
}

ppcinstr* Form_M_Function(DWORD dword)
{
	printf("M");
	return 0;
}

FormFunction FormFunctions[] =
{
	Form_Invalid_Function,
	Form_D_Function,
	Form_B_Function,
	Form_SC_Function,
	Form_I_Function,
	Form_XL_Function,
	Form_M_Function,
	Form_31_Function,
};

PPC_DWORD opcd_table[64] =
{
	FORM_Invalid, NULL,
	FORM_Invalid, NULL,
	FORM_D, "tdi",
	FORM_D, "twi",
	FORM_Invalid, NULL,
	FORM_Invalid, NULL,
	FORM_Invalid, NULL,
	FORM_D, "mulli",
	FORM_D, "subfic",
	FORM_Invalid, NULL,
	FORM_D, "cmpli",
	FORM_D, "cmpi",
	FORM_D, "addic",
	FORM_D, "addic.",
	FORM_D, "addi",
	FORM_D, "addis",
	FORM_B, "bc",
	FORM_SC, "sc",
	FORM_I, "b",
	FORM_XL,	 NULL,// 19
	FORM_M, "rlwimi",
	FORM_M, "rlwinm",
	FORM_Invalid, NULL,
	FORM_M, "rlwnm",
	FORM_D, "ori",// OR Immediate
	FORM_D, "oris",// OR Immediate Shifted
	FORM_D, "xori",// XOR Immediate
	FORM_D, "xoris",// XOR Immediate Shifted
	FORM_D, "andi.",// AND Immediate
	FORM_D, "andis.",// AND Immediate Shifted};
	FORM_Invalid, NULL,
	FORM_31, NULL,
	FORM_D, "lwz",// Load Word and Zero
	FORM_D, "lwzu",// Load Word and Zero with Update
	FORM_D, "lbz",// Load Byte and Zero
	FORM_D, "lbzu",// Load Byte and Zero with Update
	FORM_D, "stw",// Store Word	// 36
	FORM_D, "stwu",// Store Word with Update
	FORM_D, "stb",// Store Byte
	FORM_D, "stbu",// Store Byte with Update
	FORM_D, "lhz",// Load Halfword and Zero
	FORM_D, "lhzu",// Load Halfword and Zero with Update
	FORM_D, "lha",// Load Halfword Algebraic
	FORM_D, "lhau",// Load Halfword Algebraic with Update
	FORM_D, "sth",// Store Halfword
	FORM_D, "sthu",// Store Halfword with Update
	FORM_D, "lmw",// Load Multiple Word
	FORM_D, "stmw",// Store Multiple Word
	FORM_D, "lfs",// Load Floating-Point Single
	FORM_D, "lfsu",// Load Floating-Point Single with Update
	FORM_D, "lfd",// Load Floating-Point Double
	FORM_D, "lfdu",// Load Floating-Point Double with Update
	FORM_D, "stfs",// Store Floating-Point Single
	FORM_D, "stfsu",// Store Floating-Point Single with Update};
};

StringA* toString(ppcinstr* p)
{
	ASSERT(0);
	return NULL;
#if 0
	std::stringstream out;

	out << names[p->kind];

	out << "\t";

	switch (p->kind)
	{
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

	return out.str();
#endif
}

void dasm_powerpc(uint8* text, ULONG addr, ULONG size, int nsymbols, nlist* Symbols)
{
	ASSERT(0);
#if 0
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
					printf("%s:\n", pSymbol->n_un.n_name);
				//	break;
				}
			}
		}

		printf("%8.8X\t", dword);

	//	BYTE opcd = dword & 0x3f;
		BYTE opcd = dword >> 26;//& 0x3f;

		ppcinstr* instr = FormFunctions[opcd_table[opcd].form](dword);

		if (instr)
		{
			std::string str = toString(instr);
			printf("%s", str.c_str());
		}

		printf("\n");

		pc += 4;
	}

#endif
}

}	// cpp
