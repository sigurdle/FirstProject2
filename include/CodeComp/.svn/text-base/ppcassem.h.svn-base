#ifndef __ppcassem_h_
#define __ppcassem_h_

#include "LFC/disasm.h"

namespace System
{
//namespace cpp
//{

class CodeCompExt ppcContext : public MContext
{
public:
};

class ppcinstr;

#ifndef __LERSTAD__

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

	CTOR ppcinstr(Kind _kind)
	{
		kind = _kind;
	}

	union
	{
		struct //_D
		{
			uint8 RT;
			uint8 RA;
			short word;
		}
		D;

		struct //_X_SR
		{
			uint8 RT;
			uint8 RA;
			uint8 SR;
		}
		X_SR;
	};
};

#endif

CodeCompExt ppcinstr* disasm_ppc(ppcContext* c);

//CodeCompExt std::ostream& operator << (std::ostream& stream, ppcinstr* instr);
CodeCompExt String toString(const ppcinstr* p);

//}	// cpp
}

#endif // __ppcassem_h_
