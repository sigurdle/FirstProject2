#include "stdafx.h"
#include "codegen_x86.h"
#include "x86assem.h"

//namespace cpp
//{
/*
void CCodeGenx86::mov_rm32_imm32(AS_instr* instr, int Mod, int RM, long displacement, long imm32)
{
	instr->putbyte(0xC7);
	amode(instr, Mod, RM, displacement);
	instr->putbytes(&imm32, 4);
}
*/

namespace System
{

extern Temp_temp* eax;
extern Temp_temp* ecx;
extern Temp_temp* edx;
extern Temp_temp* ebx;
extern Temp_temp* esp;
extern Temp_temp* ebp;

#if 0

//using namespace cpp;

uint8 MakeSIB(uint8 scale, uint8 index, uint8 base)
{
	return base | (index>>3) | (scale >> 6);
}

void CCodeGenx86::amode(AS_instr* instr, int r32, int Mod, int RM, uint8 SIB, long displacement)
{
//	BYTE Mod;

	/*
	if (displacement == 0)
		Mod = 3;
	else
		Mod = 1;
		*/

	uint8 ModRM = RM | (r32<<3) | (Mod<<6);
	instr->putbyte(ModRM);

	if ((Mod < 3) && (RM == 4))
	{
		instr->putbyte(SIB);
	}

	if (Mod == 1)
	{
		instr->putbyte(displacement);
	}
	else if (Mod == 2)
	{
		instr->putbytes(&displacement, 4);
	}
	else if (Mod == 0 && RM == 5)
	{
		instr->putbytes(&displacement, 4);
	}
}

void amode(FILE* fileout, int r32, int Mod, int RM, uint8 SIB = -1, long displacement = -1)
{
//	BYTE Mod;

	/*
	if (displacement == 0)
		Mod = 3;
	else
		Mod = 1;
		*/

	uint8 ModRM = RM | (r32<<3) | (Mod<<6);
	fputc(ModRM, fileout);

	if ((Mod < 3) && (RM == 4))
	{
		fputc(SIB, fileout);
	}

	if (Mod == 1)
	{
		fputc(displacement, fileout);
	}
	else if (Mod == 2)
	{
		fwrite(&displacement, 1, 4, fileout);
	}
	else if (Mod == 0 && RM == 5)
	{
		fwrite(&displacement, 1, 4, fileout);
	}
}

void assem(x86instr* assem, CFunctionCode* pFun, FILE* fileout)
{
	if (assem->size_prefix)
	{
		fputc(0x66, fileout);
	}

	if (assem)
	{
		switch (assem->kind)
		{
		case x86instr::K_NEG:
			{
				if (assem->op0->kind == x86addr::K_TEMP)
				{
					fputc(0xF7, fileout);
					ASSERT(assem->op0->temp->getn() >= 0);
					amode(fileout, 3, 3, assem->op0->temp->getn());
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_NOT:
			{
				if (assem->op0->kind == x86addr::K_TEMP)
				{
					fputc(0xF7, fileout);
					amode(fileout, 2, 3, assem->op0->temp->getn());
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_DIV:
			{
				if (assem->op0->kind == x86addr::K_TEMP)
				{
					fputc(0xF7, fileout);
					amode(fileout, 6, 3, assem->op0->temp->getn());
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_IDIV:
			{
				if (assem->op0->kind == x86addr::K_TEMP)
				{
					fputc(0xF7, fileout);
					amode(fileout, 7, 3, assem->op0->temp->getn());
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_TEST:
			{
				if (assem->mov.dst->kind == x86addr::K_TEMP)
				{
					/*
					if (assem->mov.src->kind == x86addr::K_IMM)
					{
						fputc(0xF6 + assem->mov.w, fileout);
						amode(fileout, assem->mov.dst->temp->m_n, 0, assem->mov.src->temp->m_n);
					}
					else*/ if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						fputc(0x84 + assem->mov.w, fileout);
						amode(fileout, assem->mov.src->temp->getn(), 3, assem->mov.dst->temp->getn());
					}
					else
						ASSERT(0);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_AND:
			{
				if (assem->mov.dst->kind == x86addr::K_TEMP)
				{
					if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						fputc(0x22 + assem->mov.w, fileout);
						amode(fileout, assem->mov.dst->temp->m_n, 3, assem->mov.src->temp->m_n);
					}
					else
						ASSERT(0);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_XOR:
			{
				if (assem->mov.dst->kind == x86addr::K_TEMP)
				{
					if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						fputc(0x32 + assem->mov.w, fileout);
						amode(fileout, assem->mov.dst->temp->getn(), 3, assem->mov.src->temp->getn());
					}
					else
						ASSERT(0);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_SETcc:
			{
				if (assem->setcc.dst->kind == x86addr::K_TEMP)
				{
					fputc(0x0F, fileout);
					fputc(assem->setcc.op, fileout);
					amode(fileout, 2, 3, assem->setcc.dst->temp->getn());
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_ADD:
			{
				if (assem->mov.dst->kind == x86addr::K_TEMP)
				{
					ASSERT(assem->mov.dst->temp->getn() >= 0);

					if (assem->mov.src->kind == x86addr::K_IMM)
					{
						fputc(0x81, fileout);

						amode(fileout, 0, 3, assem->mov.dst->temp->getn());
						fwrite(&assem->mov.src->imm32, 1, 4, fileout);
					}
					else if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						fputc(0x02+1, fileout);
						amode(fileout, assem->mov.dst->temp->getn(), 3, assem->mov.src->temp->getn());
					}
					else
						ASSERT(0);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_SUB:
			{
				if (assem->mov.src->kind == x86addr::K_IMM)
				{
					if (assem->mov.dst->kind == x86addr::K_TEMP)
					{
						fputc(0x81, fileout);
						amode(fileout, 5, 3, assem->mov.dst->temp->m_n);
						fwrite(&assem->mov.src->imm32, 1, 4, fileout);
					}
					else if (assem->mov.dst->kind == x86addr::K_REG)
					{
						fputc(0x81, fileout);
						amode(fileout, 5, 3, assem->mov.dst->reg);
						fwrite(&assem->mov.src->imm32, 1, 4, fileout);
					}
					else
						ASSERT(0);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_SHL:
			{
				if (assem->mov.dst->kind == x86addr::K_TEMP)
				{
					if (assem->mov.src->kind == x86addr::K_IMM)
					{
						if (assem->mov.src->imm8 == 1)
						{
							fputc(0xD1, fileout);
							amode(fileout, 4, 3, assem->mov.dst->temp->getn());
						}
						else
						{
							fputc(0xC1, fileout);
							amode(fileout, 4, 3, assem->mov.dst->temp->m_n);
							fwrite(&assem->mov.src->imm8, 1, 1, fileout);
						}
					}
					/*
					else if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						fputc(0x01, fileout);
						amode(fileout, assem->mov.src->temp->m_n, 3, assem->mov.dst->temp->m_n);
					//	fwrite(&assem->mov.src->imm32, 1, 4, fileout);
					}
					*/
					else
						ASSERT(0);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_MOV:
			{
				if (assem->mov.dst->kind == x86addr::K_TEMP)
				{
					ASSERT(assem->mov.dst->temp->getn() >= 0);

					if (assem->mov.src->kind == x86addr::K_IMM)
					{
						if (assem->mov.w == 0)
						{
							fputc(0xB0 + assem->mov.dst->temp->getn(), fileout);
							fwrite(&assem->mov.src->imm32, 1, 1, fileout);
						}
						else
						{
							fputc(0xB8 + assem->mov.dst->temp->getn(), fileout);
						//	amode(fileout, 0/*R32*/, 2/*Mod*/, /*RM*/, -1/*SIB*/);
						//	fwrite(&assem->mov.dst->rm.displacement, 1, 4, fileout);
							if (assem->size_prefix)
								fwrite(&assem->mov.src->imm32, 1, 2, fileout);
							else
								fwrite(&assem->mov.src->imm32, 1, 4, fileout);
						}
					}
					else if (assem->mov.src->kind == x86addr::K_RM)
					{
						fputc(0x8A + assem->mov.w, fileout);
						amode(fileout, assem->mov.dst->temp->getn()/*R32*/, 2/*Mod*/, assem->mov.src->temp->getn()/*RM*/, -1/*SIB*/, assem->mov.src->rm.displacement);
					//	fwrite(&assem->mov.dst->rm.displacement, 1, 4, fileout);
					//	fwrite(&assem->mov.src->imm32, 1, 4, fileout);
					}
					else if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						fputc(0x8A + assem->mov.w, fileout);
						amode(fileout, assem->mov.dst->temp->getn(), 3/*Mod*/, assem->mov.src->temp->getn()/*RM*/);
					}
					else
						ASSERT(0);
				}
				else if (assem->mov.dst->kind == x86addr::K_RM)
				{
					if (assem->mov.src->kind == x86addr::K_IMM)
					{
						fputc(0xC6 + assem->mov.w, fileout);
						amode(fileout, 0/*R32*/, 2/*Mod*/, assem->mov.dst->rm.temp->getn()/*RM*/, -1/*SIB*/, assem->mov.dst->rm.displacement);
					//	fwrite(&assem->mov.dst->rm.displacement, 1, 4, fileout);
						if (assem->size_prefix)
							fwrite(&assem->mov.src->imm32, 1, 2, fileout);
						else
							fwrite(&assem->mov.src->imm32, 1, 4, fileout);
					}
					else if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						ASSERT(assem->mov.src->temp->getn() >= 0);

						fputc(0x88 + assem->mov.w, fileout);
						amode(fileout, assem->mov.src->temp->getn()/*R32*/, 2/*Mod*/, assem->mov.dst->temp->getn()/*RM*/, -1/*SIB*/, assem->mov.dst->rm.displacement);
					}
					else
						ASSERT(0);
				}
				else if (assem->mov.dst->kind == x86addr::K_REG && assem->mov.src->kind == x86addr::K_REG)
				{
					fputc(0x8A + assem->mov.w, fileout);
					amode(fileout, assem->mov.dst->reg, 3/*Mod*/, assem->mov.src->reg/*RM*/);
				}
#if 0
				else if (assem->mov.dst->kind == x86addr::K_REG && assem->mov.src->kind == x86addr::K_RM)
				{
					fputc(0x8B, fileout);
					amode(fileout, assem->mov.dst->reg, assem->mov.src->rm.Mod, assem->mov.src->rm.RM/*, displacement*/);
				}
				else if (assem->mov.dst->kind == x86addr::K_TEMP && assem->mov.src->kind == x86addr::K_RM)
				{
					fputc(0x8B, fileout);
					amode(fileout, assem->mov.dst->temp->m_n, assem->mov.src->rm.Mod, assem->mov.src->rm.RM/*, displacement*/);
				}
#endif
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_MOVSX:
			{
				if (assem->mov.dst->kind == x86addr::K_TEMP)
				{
					if (assem->mov.src->kind == x86addr::K_TEMP)
					{
						fputc(0x0F, fileout);
						fputc(0xBE + assem->mov.w, fileout);
						amode(fileout, assem->mov.dst->temp->getn(), 3/*Mod*/, assem->mov.src->temp->getn()/*RM*/);
					}
					else if (assem->mov.src->kind == x86addr::K_RM)
					{
						fputc(0x0F, fileout);
						fputc(0xBE + assem->mov.w, fileout);
						amode(fileout, assem->mov.dst->temp->getn()/*R32*/, 2/*Mod*/, assem->mov.src->temp->getn()/*RM*/, -1/*SIB*/, assem->mov.src->rm.displacement);
					//	fwrite(&assem->mov.dst->rm.displacement, 1, 4, fileout);
					//	fwrite(&assem->mov.src->imm32, 1, 4, fileout);
					}
					else
						ASSERT(0);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_IMUL:
			{
				fputc(0x0f, fileout);
				fputc(0xaf, fileout);

				amode(fileout, assem->imul.dst->temp->m_n, 3/*Mod*/, assem->imul.src->temp->m_n/*RM*/);

			}
			break;

		case x86instr::K_PUSH:
			{
				if (assem->op0->kind == x86addr::K_IMM)
				{
					fputc(0x68, fileout);
					fwrite(&assem->op0->imm32, 1, 4, fileout);
				}
				else if (assem->op0->kind == x86addr::K_REG)
				{
					fputc(0x50+assem->op0->reg, fileout);
				}
				else if (assem->op0->kind == x86addr::K_TEMP)
				{
					fputc(0x50+assem->op0->temp->m_n, fileout);
				}
				else if (assem->op0->kind == x86addr::K_NAME)
				{
					fputc(0x68, fileout);

					FRelocation* pReloc = new FRelocation;
					pReloc->VirtualAddress = ftell(fileout);
					//pReloc->SymbolTableIndex = assem->push->name->m_symbolIndex;//f->const_int.reloc->pDeclarator->m_symbolIndex;
					pReloc->tempLabel = assem->op0->name;
					pFun->AddRelocation(pReloc);

					long value = 0;
					fwrite(&value, 1, 4, fileout);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_POP:
			{
				if (assem->op0->kind == x86addr::K_REG)
				{
					fputc(0x58+assem->op0->reg, fileout);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_CALL:
			{
				if (true)	// Relative
				{
					fputc(0xE8, fileout);
					//::amode(fileout, 2/*r32*/, 0/*Mod*/, 5/*RM*/, -1, 0);
					long address = 0;
					fwrite(&address, 1, 4, fileout);

					FRelocation* pReloc = new FRelocation;
					pReloc->VirtualAddress = ftell(fileout)-4;
			//		pReloc->SymbolTableIndex = assem->call->name->m_symbolIndex;//f->const_int.reloc->pDeclarator->m_symbolIndex;
					pReloc->tempLabel = assem->op0->name;

	#if 0
					pReloc->pRelocConst = f->const_int.reloc;
	#endif
					pFun->AddRelocation(pReloc);
				}
				else
				{
					// call r/m32
					fputc(0xFF, fileout);
					ASSERT(0);
#if 0
					::amode(fileout, 2/*r32*/, 0/*Mod*/, 5/*RM*/, -1, 0);
#endif
					FRelocation* pReloc = new FRelocation;
					pReloc->VirtualAddress = ftell(fileout)-4;
			//		pReloc->SymbolTableIndex = assem->call->name->m_symbolIndex;//f->const_int.reloc->pDeclarator->m_symbolIndex;
					pReloc->tempLabel = assem->op0->name;

	#if 0
					pReloc->pRelocConst = f->const_int.reloc;
	#endif
					pFun->AddRelocation(pReloc);

				//	long v = 0;
				//	fwrite(&v, 1, 4, fileout);
				}
			}
			break;

		case x86instr::K_CMP:
			{
				if (assem->cmp.src->kind == x86addr::K_IMM)
				{
					fputc(0x80 + assem->cmp.w, fileout);
					amode(fileout, 7, 3, assem->cmp.dst->temp->m_n);
					fwrite(&assem->mov.src->imm32, 1, 4, fileout);
				}
				else if (assem->cmp.src->kind == x86addr::K_TEMP)
				{
					fputc(0x3A + assem->cmp.w, fileout);
					amode(fileout, assem->cmp.dst->temp->m_n/*7*/, 3, assem->cmp.src->temp->m_n);
				}
				else
					ASSERT(0);
			}
			break;

		case x86instr::K_Jcc:
			{
				ASSERT(assem->jcc.label);

				fputc(0x0f, fileout);
				fputc(assem->jcc.op, fileout);
				fwrite(&assem->jcc.label->m_spOffset, 1, 4, fileout);

				pFun->m_labels.push_back(RelativeLabel(ftell(fileout)-4, assem->jcc.label));
			}
			break;

		case x86instr::K_JMP:
			{
				fputc(0xe9, fileout);	// jmp rel32
				fwrite(&assem->op0->name->m_spOffset, 1, 4, fileout);
				pFun->m_labels.push_back(RelativeLabel(ftell(fileout)-4, assem->op0->name));
			}
			break;

		case x86instr::K_RET:
			{
				fputc(0xC3, fileout);	// RET (near return)
			}
			break;

		default:
			ASSERT(0);
		}
	}
}

void CCodeGenx86::Function_Prologue(CFunctionCode* pFun)
{
	//pFun->emit(AS_Line(s->m_line_pos));

	pFun->emit(AS_Oper(x86_PUSH(x86_REG(5)), NULL, NULL));
	pFun->emit(AS_Oper(x86_MOV(x86_REG(5), x86_REG(4), 4), NULL, NULL));
	pFun->emit(AS_Oper(x86_SUB(x86_REG(4), x86_IMM(68)), NULL, NULL));

	/*
	AS_instr* instr;

	instr = AS_Oper(NULL, NULL, NULL);
	instr->putbyte(0x50+5);	// push	ebp
	emit(instr);

	instr = AS_Oper(NULL, NULL, NULL);
	mov_r32_rm32(instr, 5, 3,4);	// // mov	ebp,esp
	emit(instr);
	*/
}

void CCodeGenx86::Function_Epilogue(CFunctionCode* pFun)
{
	pFun->emit(AS_Oper(x86_MOV(x86_REG(4), x86_REG(5)), NULL, NULL));	// mov esp,ebp
	pFun->emit(AS_Oper(x86_POP(x86_REG(5)), NULL, NULL));	// pop ebp
	pFun->emit(AS_Oper(x86_RET(), NULL, NULL));
	/*
	AS_instr* instr;

	instr = AS_Oper(NULL, NULL, NULL);
	instr->putbyte(0x58+5);	// pop ebp
	emit(instr);

	instr = AS_Oper(NULL, NULL, NULL);
	instr->putbyte(0xC3);	// RET (near return)	// TODO, only if it's not done explicitly
	emit(instr);
	*/
}

Temp_temp** CCodeGenx86::munchExpression(CFunctionCode* pFun, T_Exp* e)
{
	switch (e->kind)
	{
	case T_Exp::T_MEM:
		{
			if (e->mem.mem->kind == T_Exp::T_CONST)
			{
				Temp_temp** r = new Temp_temp*;
				*r = new Temp_temp;

				(*r)->m_exp = e;
			//	r->m_n = x86_reg++;

			// mov r32,r/m32

				AS_instr* instr = AS_Oper(NULL, new Temp_tempList(NULL, NULL), new Temp_tempList(NULL, NULL));
				instr->putbyte(0x8B);
				amode(instr, r->m_dn, 0, 5, -1, e->mem.mem->const_int.int32);

#if 0
				if (e->mem->const_int.reloc)
				{
					FRelocation* pReloc = new FRelocation;
					pReloc->VirtualAddress = ftell(fileout)-4;
					pReloc->SymbolTableIndex = e->mem->const_int.reloc->pDeclarator->m_symbolIndex;
					pReloc->pRelocConst = e->mem->const_int.reloc;
					pFun->AddRelocation(pReloc);
				}
#endif

				pFun->emit(instr);

				return r;
			}
			else if (e->mem.mem->kind == T_Exp::T_BINOP)
			{
				if (e->mem.mem->binop.right->kind == T_Exp::T_CONST)
				{
					Temp_temp* r1 = munchExpression(pFun, e->mem.mem->binop.left);

				//	ASSERT(r1->m_size == e->mem.size);

					Temp_temp* r = new Temp_temp;
					r->m_exp = e;

					r->m_size = e->mem.size;
				//	r->m_n = x86_reg++;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_RM(r1, e->mem.mem->binop.right->const_int.int32), r->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));

					return r;
				}
				else
					ASSERT(0);
			}
			else
				ASSERT(0);
		}
		break;

	case T_Exp::T_BINOP:
		{
			Temp_temp* r = new Temp_temp;
			r->m_exp = e;
		//	r->name = (char*)malloc(64);
		//	sprintf(r->name, "t%d", x86_reg);
		//	r->m_n = x86_reg++;

			switch (e->binop.op)
			{
			case '+':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					
#if 0
					if (e->binop.right->kind & T_IMMEDIATE)
					{
						AS_instr* instr;
						
						// mov r32,r/m32
						instr = AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL));
						//	instr->putbyte(0x8B);
						//	amode(instr, r->m_dn, 3, r1->m_dn);
						
						pFun->emit(instr);
						
						// add r/m32,imm32
						instr = AS_Oper(x86_ADD(x86_TEMP(r), x86_IMM(e->binop.right)), new Temp_tempList(r, NULL), NULL);
						//	instr->putbyte(0x81);
						//	amode(instr, 0, 3, r->m_dn);
						//	instr->putbytes(&e->binop.right->const_int.int32, 4);
						
						pFun->emit(instr);
						
						/*
						if (dst->mem->const_int.reloc)
						{
						FRelocation* pReloc = new FRelocation;
						pReloc->VirtualAddress = ftell(fileout)-4;
						pReloc->SymbolTableIndex = dst->mem->const_int.reloc->pDeclarator->m_symbolIndex;
						pReloc->pRelocConst = dst->mem->const_int.reloc;
						pFun->AddRelocation(pReloc);
						}
						*/
						
						return r;
					}
					else
#endif
					{
						Temp_temp* r2 = munchExpression(pFun, e->binop.right);

						ASSERT(r1->m_size == r2->m_size);
	
						r->m_size = r1->m_size;
						
						//	TODO
						//AS_instr* instr;
						
						// mov r32,r/m32
						pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r2)), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
						pFun->emit(AS_Oper(x86_ADD(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
						//	instr->putbyte(0x8B);
						//	amode(instr, r->m_dn, 3, r1->m_dn);
						
						//	pFun->emit(instr);
						
						/*
						// add r/m32,imm32
						instr = AS_Oper(NULL, new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL));
						instr->putbyte(0x81);
						amode(instr, 0, 3, r->m_dn);
						instr->putbytes(&e->binop.right->const_int.int32, 4);
						
						  pFun->emit(instr);
						  
							 r->m_dn = 1;
						*/
						return r;
					}
				}
				break;
				
			case '*':
				{
				/*
				if (e->binop.right->kind & T_IMMEDIATE)
				{
				ASSERT(0);
				
				  // use three operand form
				  
					 Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					 Temp_temp* r2 = munchExpression(pFun, e->binop.right);
					 }
					 else
					*/
					{
						Temp_temp* r1 = munchExpression(pFun, e->binop.left);
						Temp_temp* r2 = munchExpression(pFun, e->binop.right);

						ASSERT(r1->m_size == r2->m_size);

						r->m_size = r1->m_size;
						
						// mov r32,r/m32
						
						pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r2)), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
						pFun->emit(AS_Oper(x86_IMUL(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					}
				}
				break;
				
			case 'udiv':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					Temp_temp* r2 = munchExpression(pFun, e->binop.right);

					ASSERT(r1->m_size == r2->m_size);

					r->m_size = r1->m_size;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(eax), x86_TEMP(r1)), new Temp_tempList(eax, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(x86_XOR(x86_TEMP(edx), x86_TEMP(edx)), new Temp_tempList(edx, NULL), NULL));
					pFun->emit(AS_Oper(x86_DIV(x86_TEMP(r2)), new Temp_tempList(eax, new Temp_tempList(edx, NULL)), new Temp_tempList(r2, NULL)));

					// eax:edx
					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(eax)), new Temp_tempList(r, NULL), new Temp_tempList(eax, NULL)));
				}
				break;

			case 'sdiv':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					Temp_temp* r2 = munchExpression(pFun, e->binop.right);

					ASSERT(r1->m_size == r2->m_size);

					r->m_size = r1->m_size;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(eax), x86_TEMP(r1)), new Temp_tempList(eax, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(x86_XOR(x86_TEMP(edx), x86_TEMP(edx)), new Temp_tempList(edx, NULL), NULL));
					pFun->emit(AS_Oper(x86_IDIV(x86_TEMP(r2)), new Temp_tempList(eax, new Temp_tempList(edx, NULL)), new Temp_tempList(r2, NULL)));

					// eax:edx
					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(eax)), new Temp_tempList(r, NULL), new Temp_tempList(eax, NULL)));
				}
				break;

			case 'umod':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					Temp_temp* r2 = munchExpression(pFun, e->binop.right);

					ASSERT(r1->m_size == r2->m_size);

					r->m_size = r1->m_size;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(eax), x86_TEMP(r1)), new Temp_tempList(eax, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(x86_XOR(x86_TEMP(edx), x86_TEMP(edx)), new Temp_tempList(edx, NULL), NULL));
					pFun->emit(AS_Oper(x86_DIV(x86_TEMP(r2)), new Temp_tempList(eax, new Temp_tempList(edx, NULL)), new Temp_tempList(r2, NULL)));

					// eax:edx
					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(edx)), new Temp_tempList(r, NULL), new Temp_tempList(eax, NULL)));
				}
				break;

			case 'smod':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					Temp_temp* r2 = munchExpression(pFun, e->binop.right);

					ASSERT(r1->m_size == r2->m_size);

					r->m_size = r1->m_size;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(eax), x86_TEMP(r1)), new Temp_tempList(eax, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(x86_XOR(x86_TEMP(edx), x86_TEMP(edx)), new Temp_tempList(edx, NULL), NULL));
					pFun->emit(AS_Oper(x86_IDIV(x86_TEMP(r2)), new Temp_tempList(eax, new Temp_tempList(edx, NULL)), new Temp_tempList(r2, NULL)));

					// eax:edx
					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(edx)), new Temp_tempList(r, NULL), new Temp_tempList(eax, NULL)));
				}
				break;

			case '|':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					Temp_temp* r2 = munchExpression(pFun, e->binop.right);

					ASSERT(r1->m_size == r2->m_size);

					r->m_size = r1->m_size;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(x86_OR(x86_TEMP(r), x86_TEMP(r2)), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				}
				break;

			case '&':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					Temp_temp* r2 = munchExpression(pFun, e->binop.right);

					ASSERT(r1->m_size == r2->m_size);

					r->m_size = r1->m_size;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r1), r->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(x86_AND(x86_TEMP(r), x86_TEMP(r2), r->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				}
				break;

			case '^':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);
					Temp_temp* r2 = munchExpression(pFun, e->binop.right);

					ASSERT(r1->m_size == r2->m_size);

					r->m_size = r1->m_size;

					pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r1), r->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
					pFun->emit(AS_Oper(x86_XOR(x86_TEMP(r), x86_TEMP(r2), r->m_size), new Temp_tempList(r, NULL), new Temp_tempList(r2, NULL)));
				}
				break;

			case 'shl':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);

					if (e->binop.right->kind & T_IMMEDIATE)
					{
						//Temp_temp* r2 = munchExpression(pFun, e->binop.right);

						VERIFY(e->binop.right->const_int.int32 >= 0);

						pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
						if (e->binop.right->const_int.int32 != 0)
						{
							pFun->emit(AS_Oper(x86_SHL(x86_TEMP(r), x86_IMM(e->binop.right->const_int.int32)), new Temp_tempList(r, NULL), NULL));
						}
					}
					else
					{
						ASSERT(0);
					}
				}
				break;

			case 'shr':
				{
					if (e->binop.right->kind & T_IMMEDIATE)
					{
						VERIFY(e->binop.right->const_int.int32 >= 0);

						/*
						if (e->binop.right->const_int.int32 == 8)
						{
							pFun->emit(AS_Oper(x86_MOV(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
						}
						else
						*/
							ASSERT(0);
					}
					else
						ASSERT(0);
				}
				break;

			case 'sar':
				{
					ASSERT(0);
				}
				break;

			case '==':
			case '!=':
			case '>':
			case '<':
			case '>=':
			case '<=':
				{
					Temp_temp* r1 = munchExpression(pFun, e->binop.left);

					if (e->binop.right->kind == T_Exp::T_CONST)
					{
						// cmp r/m32,imm32

						AS_instr* instr = AS_Oper(x86_CMP(x86_TEMP(r1), x86_IMM(e->binop.right->const_int.int32)),
							/*destination*/NULL, new Temp_tempList(r1, NULL));

						pFun->emit(instr);
					}
					else
					{
						Temp_temp* r2 = munchExpression(pFun, e->binop.right);

						ASSERT(0);
					}

					int op;

					switch (e->binop.op)
					{
					case '<': op = 0x92; break;
					case '==': op = 0x94; break;
					case '!=': op = 0x95; break;
					case '<=': op = 0x96; break;
					case '>': op = 0x97; break;
					case '>=': op = 0x9D; break;
					default:
						ASSERT(0);
					}

					AS_instr* instr;

					/*
					// Treat xor r,r like move
					if (
					instr = AS_Move(x86_XOR(x86_TEMP(r), x86_TEMP(r)), new Temp_tempList(r, NULL), NULL);
					pFun->emit(instr);
					*/

					instr = AS_Move(x86_SETcc(op, x86_TEMP(r)), new Temp_tempList(r, NULL), NULL);
					r->m_size = 1;
					pFun->emit(instr);
				}
				break;
				
			default:
				ASSERT(0);
			}

			// TODO
			return r;
		}
		break;

	case T_Exp::T_UNOP:
		{
			if (e->unop.op == '-')
			{
				Temp_temp* r = new Temp_temp;
				r->m_exp = e;
				r->m_size = 4;

				Temp_temp* r1 = munchExpression(pFun, e->unop.exp);

				pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Oper(x86_NEG(x86_TEMP(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));

				return r;
			}
			else if (e->unop.op == '~')
			{
				Temp_temp* r = new Temp_temp;
				r->m_exp = e;
				r->m_size = 4;

				Temp_temp* r1 = munchExpression(pFun, e->unop.exp);

				pFun->emit(AS_Move(x86_MOV(x86_TEMP(r), x86_TEMP(r1)), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL)));
				pFun->emit(AS_Oper(x86_NOT(x86_TEMP(r)), new Temp_tempList(r, NULL), new Temp_tempList(r, NULL)));

				return r;
			}

			else if (e->unop.op == 'se')
			{
				Temp_temp* r = new Temp_temp;
				r->m_exp = e;
				r->m_size = 4;

				if (e->unop.exp->kind == T_Exp::T_MEM &&
					e->unop.exp->mem.mem->kind == T_Exp::T_BINOP &&
					e->unop.exp->mem.mem->binop.op == '+' &&
					e->unop.exp->mem.mem->binop.right->kind == T_Exp::T_CONST)
				{
					Temp_temp* r1 = munchExpression(pFun, e->unop.exp->mem.mem->binop.left);

					// byte -> dword
					AS_instr* instr = AS_Oper(x86_MOVSX(x86_TEMP(r), x86_RM(r1, e->unop.exp->mem.mem->binop.right->const_int.int32), 0), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL));
					pFun->emit(instr);
				}
				else
				{
					Temp_temp* r1 = munchExpression(pFun, e->unop.exp);

					// byte -> dword
					AS_instr* instr = AS_Oper(x86_MOVSX(x86_TEMP(r), x86_TEMP(r1), 0), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL));
					pFun->emit(instr);
				}

				return r;
			}
			else if (e->unop.op == 'ze')
			{
				Temp_temp* r = new Temp_temp;
				r->m_exp = e;
				r->m_size = 4;

				Temp_temp* r1 = munchExpression(pFun, e->unop.exp);

				// byte -> dword

				AS_instr* instr = AS_Oper(x86_MOVZX(x86_TEMP(r), x86_TEMP(r1), 0), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL));
				pFun->emit(instr);

				return r;
			}
			else if (e->unop.op == 'trun')
			{
				Temp_temp* r1 = munchExpression(pFun, e->unop.exp);

				return r1;
				/*
				Temp_temp* r = new Temp_temp;
				r->m_size = 1;	// TODO

				// byte -> dword

				AS_instr* instr = AS_Oper(x86_MOV(x86_TEMP(r), x86_TEMP(r1), 0), new Temp_tempList(r, NULL), new Temp_tempList(r1, NULL));
				pFun->emit(instr);

				return r;
				*/
			}

			else
				ASSERT(0);
		}
		break;

	case T_Exp::T_CALL:
		{
			Temp_temp* r = new Temp_temp;
			// push arguments on stack
			ArgList* pExprR = e->call.args;
		
			int stackSize = 0;

			while (pExprR)
			{
			//	cpp::CExpression* pArgExpr = pExprR->expr;
				T_Exp* pTExpr = pExprR->head;

				if (pTExpr->kind & T_IMMEDIATE/*== T_Exp::T_CONST*/)
				{
					// push imm32
					AS_instr* instr = AS_Oper(x86_PUSH(x86_IMM(pTExpr)), NULL, NULL);
#if 0
					instr->putbyte(0x68);
				//	amode(instr, 0, 3, r->m_dn);
				//	instr->putbytes(&e->binop.right->const_int.int32, 4);

					//putc(0x68, fileout);	// push imm32
					if (pTExpr->const_int.reloc)
					{
						FRelocation* pReloc = new FRelocation;
						pReloc->VirtualAddress = ftell(fileout);
						pReloc->SymbolTableIndex = pTExpr->const_int.reloc->pDeclarator->m_symbolIndex;
						pReloc->pRelocConst = pTExpr->const_int.reloc;
						pFun->AddRelocation(pReloc);
					}
#endif

					//fwrite(&pTExpr->const_int.int32, 1, 4, fileout);
			//		instr->putbytes(&pTExpr->const_int.int32, 4);

					pFun->emit(instr);
				}
				else
				{
					Temp_temp* r = munchExpression(pFun, pTExpr);
					pFun->emit(AS_Oper(x86_PUSH(x86_TEMP(r)), NULL, new Temp_tempList(r, NULL)));
				}

				pExprR = pExprR->tail;
			}

			T_Exp* f;
			if (e->call.f->kind == T_Exp::T_MEM)
				f = e->call.f->mem.mem;
			else
				f = e->call.f;

			AS_instr* instr = AS_Oper(x86_CALL(x86_IMM(f)), NULL, NULL);
		//	instr->putbyte(0xFF);	// // call rm32
		//	amode(instr, 2/*r32*/, 0/*Mod*/, 5/*RM*/);

			//
			//	putc(0xE8, fileout);	// call
			/*
			putc(0xFF, fileout);	// call rm32
			
			BYTE Mod = 0;
			BYTE RM = 5;
			BYTE Reg = 2;	// ?? what's this for ??
			BYTE ModRM = RM | (Reg<<3) | (Mod<<6);
			putc(ModRM, fileout);
			*/
#if 0
			if (pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex == 0)
			{
				int nargsSize = 4*4;
				
				char symbolName[256];
				sprintf(symbolName, "__imp__%s@%d", pExpr->m_pDeclaratorRef->m_pDeclarator->m_name.c_str(), nargsSize);
				//	sprintf(symbolName, "_abcd", pExpr->m_pDeclarator->m_name.c_str(), nargsSize);
				
				FSymbol* pSymbol;
				pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex = pFunc->m_ofile->AddSymbol(symbolName, &pSymbol);
				
				pSymbol->Type = 0x20;	// function
				pSymbol->SectionNumber = 0;	// not defined in this object file
				pSymbol->StorageClass = IMAGE_SYM_CLASS_EXTERNAL;
			}
#endif
#if 0	
			FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
			
			ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
			ImageReloc->SymbolTableIndex = pExpr->left->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;
	//		ImageReloc->SymbolTableIndex = pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;	// reference to name of function being called
			//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
			ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
#endif
			long offset = 0;

#if 0
			if (f->const_int.reloc)
			{
				FRelocation* pReloc = new FRelocation;
				pReloc->VirtualAddress = ftell(fileout);
				pReloc->SymbolTableIndex = f->const_int.reloc->pDeclarator->m_symbolIndex;
				pReloc->pRelocConst = f->const_int.reloc;
				pFun->AddRelocation(pReloc);

				long v = 0;
				fwrite(&v, 1, 4, fileout);
			}
			else
			{
				instr->putbytes(&f->const_int.int32, 4);
				//fwrite(&f->const_int.int32, 1, 4, fileout);
			}
#endif

			pFun->emit(instr);

			return r;
		}
		break;

		case T_Exp::T_CONST:
		{
			Temp_temp* r = new Temp_temp;
			r->m_exp = e;
			r->m_size = e->m_size;

			pFun->emit(AS_Oper(x86_MOV(x86_TEMP(r), x86_IMM(e->const_int.int32), r->m_size), new Temp_tempList(r, NULL), NULL));

			return r;
		}
		break;

		case T_Exp::T_TEMP:
		{
			return *e->temp;
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

void CCodeGenx86::munchStatement(CFunctionCode* pFun, T_Stm* s)
{
	if (s->kind >= 64 || s->kind == T_Stm::T_LABEL)	// ??
	{
		if (s->m_line_pos != -1)
		{
			if (s->m_line_pos != m_line)
			{
				pFun->emit(AS_Line(s->m_line_pos));
				m_line = s->m_line_pos;
			}
		}
	}

	switch (s->kind)
	{
	case T_Stm::T_MOVE:
		{
			printf("move\n");

			T_Exp* dst = s->move.left;
			T_Exp* src = s->move.right;

			if (dst->kind == T_Exp::T_MEM)
			{
				if (dst->mem.mem->kind == T_Exp::T_CONST)
				{
					if (src->kind == T_Exp::T_CONST)
					{
					// mov r/m32,imm32

						AS_instr* instr = AS_Oper(NULL, NULL/*d*/, NULL/*s*/);
						instr->putbyte(0xC7);
						amode(instr, 0, 0, 5, -1, dst->mem.mem->const_int.int32);

						// TODO
						/*
						if (dst->mem->const_int.reloc)
						{
							FRelocation* pReloc = new FRelocation;
							pReloc->VirtualAddress = ftell(fileout)-4;
							pReloc->SymbolTableIndex = dst->mem->const_int.reloc->pDeclarator->m_symbolIndex;
							pReloc->pRelocConst = dst->mem->const_int.reloc;
							pFun->AddRelocation(pReloc);
						}
						*/

						instr->putbytes(&src->const_int.int32, 4);

						pFun->emit(instr);
					}
					else
					{
						Temp_temp* r2 = munchExpression(pFun, src);

					// mov r/m32,r32

						AS_instr* instr = AS_Oper(NULL, NULL, new Temp_tempList(r2, NULL));
						instr->putbyte(0x89);
						amode(instr, r2->m_dn, 0, 5, -1, dst->mem.mem->const_int.int32);

#if 0
						if (dst->mem->const_int.reloc)
						{
							FRelocation* pReloc = new FRelocation;
							pReloc->VirtualAddress = ftell(fileout)-4;
							pReloc->SymbolTableIndex = dst->mem->const_int.reloc->pDeclarator->m_symbolIndex;
							pReloc->pRelocConst = dst->mem->const_int.reloc;
							pFun->AddRelocation(pReloc);
						}
#endif

						pFun->emit(instr);
					}
				}
				else if (dst->mem.mem->kind == T_Exp::T_BINOP &&
							dst->mem.mem->binop.op == '+' &&
							dst->mem.mem->binop.right->kind == T_Exp::T_CONST)
				{
					Temp_temp* r1 = munchExpression(pFun, dst->mem.mem->binop.left);

					if (src->kind & T_IMMEDIATE)
					{
						pFun->emit(AS_Oper(x86_MOV(x86_RM(r1, dst->mem.mem->binop.right->const_int.int32), x86_IMM(src), dst->mem.size), NULL, new Temp_tempList(r1, NULL)));
					//	pFun->emit(AS_Oper(x86_MOV(x86_RM(r1, dst->mem.mem->binop.right->const_int.int32), x86_IMM(src), dst->mem.size), NULL, NULL));
					}
					else
					{
						/*
						if (src->kind == T_Exp::T_UNOP && src->unop.op == 'se')
						{
							Temp_temp* r2 = munchExpression(pFun, src->unop.exp);
							ASSERT(dst->mem.size > r2->m_size);

							pFun->emit(AS_Move(x86_MOVSX(x86_RM(r1, dst->mem.mem->binop.right->const_int.int32), x86_TEMP(r2), dst->mem.size), new Temp_tempList(r1, NULL), new Temp_tempList(r2, NULL)));
						}
						else if (src->kind == T_Exp::T_UNOP && src->unop.op == 'ze')
						{
							ASSERT(0);
						}
						else
						*/
						{
							Temp_temp* r2 = munchExpression(pFun, src);
							ASSERT(dst->mem.size <= r2->m_size);

							pFun->emit(AS_Oper(x86_MOV(x86_RM(r1, dst->mem.mem->binop.right->const_int.int32), x86_TEMP(r2), dst->mem.size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
						//	pFun->emit(AS_Oper(x86_MOV(x86_RM(r1, dst->mem.mem->binop.right->const_int.int32), x86_TEMP(r2), dst->mem.size), NULL, new Temp_tempList(r2, NULL)));
						}
					}
				}
				else
				{
					ASSERT(0);
				}
			}
			else if (dst->kind == T_Exp::T_TEMP)
			{
				if (src->kind == T_Exp::T_CONST)
				{
					int32 immvalue = src->const_int.int32;

					AS_instr* instr = AS_Oper(x86_MOV(x86_TEMP(dst->temp), x86_IMM(immvalue), dst->temp->m_size), new Temp_tempList(dst->temp, NULL), NULL);
					pFun->emit(instr);
				}
				else if (src->kind == T_Exp::T_UNOP && src->unop.op == 'se')
				{
					if (src->unop.exp->kind == T_Exp::T_MEM &&
						src->unop.exp->mem.mem->kind == T_Exp::T_BINOP &&
						src->unop.exp->mem.mem->binop.op == '+' &&
						src->unop.exp->mem.mem->binop.right->kind == T_Exp::T_CONST)
					{
						Temp_temp* r1 = munchExpression(pFun, src->unop.exp->mem.mem->binop.left);

						// byte -> dword
						AS_instr* instr = AS_Oper(x86_MOVSX(x86_TEMP(dst->temp), x86_RM(r1, src->unop.exp->mem.mem->binop.right->const_int.int32), 0), new Temp_tempList(dst->temp, NULL), new Temp_tempList(r1, NULL));
						pFun->emit(instr);
					}
					else
					{
						Temp_temp* r = munchExpression(pFun, src->unop.exp);

						//if (r->m_size == 1)	// byte -> dword
						{
							AS_instr* instr = AS_Oper(x86_MOVSX(x86_TEMP(dst->temp), x86_TEMP(r), r->m_size), new Temp_tempList(dst->temp, NULL), new Temp_tempList(r, NULL));
							pFun->emit(instr);
						}
						/*
						else if (r->m_size == 2)	// word -> dword
						{
							AS_instr* instr = AS_Oper(x86_MOVSX(x86_TEMP(dst->temp), x86_TEMP(r), 1), new Temp_tempList(dst->temp, NULL), new Temp_tempList(r, NULL));
							pFun->emit(instr);
						}
						else
							ASSERT(0);
							*/
					}
				}
				else if (src->kind == T_Exp::T_UNOP && src->unop.op == 'ze')
				{
					ASSERT(0);
				}
				else
				{
					Temp_temp* r = munchExpression(pFun, src);

					ASSERT(dst->temp->m_size <= r->m_size);

					AS_instr* instr = AS_Move(x86_MOV(x86_TEMP(dst->temp), x86_TEMP(r), dst->temp->m_size), new Temp_tempList(dst->temp, NULL), new Temp_tempList(r, NULL));
					pFun->emit(instr);
				}
			}
			else
			{
				ASSERT(0);
			}
		}
		break;

	case T_Stm::T_JUMP:
		{
			printf("jump");
			if (s->jump.exp->kind == T_Exp::T_NAME)
			{
				pFun->emit(AS_Oper(x86_JMP(x86_NAME(s->jump.exp->name.label)), NULL, NULL,
					new AS_Targets(s->jump.labels)));

					/*
				putc(0xe9, fileout);	// jmp rel32

				s->jump.exp->name.label->m_branches.push_back(ftell(fileout));

				printf(" %d", s->jump.exp->name.label->m_n);

				long offset = 0;
				if (s->jump.exp->name.label->m_pos != -1)
				{
					offset = s->jump.exp->name.label->m_pos - ftell(fileout);
				}

				fwrite(&offset, 4, 1, fileout);
				*/
			}
			else
			{
				ASSERT(0);
			}

			printf("\n");
		}
		break;

	case T_Stm::T_CJUMP:
		{
			printf("cjump");

			ASSERT(s->cjump.t);
			ASSERT(s->cjump.f);

			if (s->cjump.right->kind == T_Exp::T_CONST/* && r1->m_dn != -1*/)
			{
				if (s->cjump.right->const_int.int32 == 0)
				{
					if (s->cjump.left->kind == T_Exp::T_BINOP && s->cjump.left->binop.op == '&')
					{
						Temp_temp* r1 = munchExpression(pFun, s->cjump.left->binop.left);
						Temp_temp* r2 = munchExpression(pFun, s->cjump.left->binop.right);

						ASSERT(r1->m_size == r2->m_size);

						AS_instr* instr = AS_Oper(x86_TEST(x86_TEMP(r1), x86_TEMP(r2), r1->m_size), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL)));
						pFun->emit(instr);
					}
					else
					{
						Temp_temp* r1 = munchExpression(pFun, s->cjump.left);

						AS_instr* instr = AS_Oper(x86_TEST(x86_TEMP(r1), x86_TEMP(r1), r1->m_size), NULL, new Temp_tempList(r1, NULL));
						pFun->emit(instr);
					}
				}
				else
				{
					Temp_temp* r1 = munchExpression(pFun, s->cjump.left);

					// cmp r/m32,imm32

					AS_instr* instr = AS_Oper(x86_CMP(x86_TEMP(r1), x86_IMM(s->cjump.right->const_int.int32)),
						/*destination*/NULL, new Temp_tempList(r1, NULL));
				//	instr->putbyte(0x81);
				//	amode(instr, 7, 3,r1->m_dn);

					//instr->putbytes(&s->cjump.right->const_int.int32, 4);

	#if 0
					putc(0x81, fileout);
					amode(7, 3,r1->m_dn);
					fwrite(&s->cjump.right->const_int.int32, 4, 1, fileout);
	#endif
					pFun->emit(instr);

				//	cmpi(s->cjump.right->const_int.int32, 2/*size*/, 0,r1->m_dn);
				}
			}
			else if (s->cjump.left->kind == T_Exp::T_CONST)
			{
				ASSERT(0);	// TODO
			}
			else
			{
				Temp_temp* r1 = munchExpression(pFun, s->cjump.left);
				Temp_temp* r2 = munchExpression(pFun, s->cjump.right);

				AS_instr* instr = AS_Oper(x86_CMP(x86_TEMP(r1), x86_TEMP(r2)), NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL)));
				pFun->emit(instr);

#if 0
					emit(AS_Oper("cmp", NULL, new Temp_tempList(r1, new Temp_tempList(r2, NULL))));
				emit(AS_Oper("BCC", NULL, NULL));

			/*
				if ((pExpr->left->m_pType->get_sizeof() == 2) ||
					(pExpr->right->m_pType->get_sizeof() == 2))
				{
					((CCodeGen68*)this)->cmp(dreg0, CMPOP_DN_WORD, 0,dreg1);
				}
				else
					*/
				{
					ASSERT(r2->m_dn != -1);
					if (r1->m_dn != -1)
						cmp(r1->m_dn, CMPOP_DN_LONG, 0,r2->m_dn);
					else
						cmp(r1->m_an-8, CMPOP_AN_LONG, 0,r2->m_dn);
				}

				de(r2);
#endif
			}

			//AS_instr* instr = AS_Oper(x86_Jcc);

			// Note, we emit the opposite op codes
			switch (s->cjump.relop)
			{
			case '==':
				{
				// jne rel32
				//	instr->putbyte(0x0f);
				//	instr->putbyte(0x85);
					pFun->emit(AS_Oper(x86_Jcc(0x84, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));
				}
				break;

			case '!=':
				{
				//bcc(COND_EQ);//emit_op(JOP_if_icmpeq);
					pFun->emit(AS_Oper(x86_Jcc(0x85, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));
				}
				break;
					
			case '<':
				{
					pFun->emit(AS_Oper(x86_Jcc(0x82, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));

			//	bcc(COND_GE);
			//	emit_op(JOP_if_icmpgt);
				}
				break;
					
			case '>':
				{
					pFun->emit(AS_Oper(x86_Jcc(0x87, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));

			//	bcc(COND_LE);
			//	emit_op(JOP_if_icmplt);
				}
				break;
					
			case '<=':
				{
					pFun->emit(AS_Oper(x86_Jcc(0x8E, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));

					//bcc(COND_GT);	//emit_op(JOP_if_icmpge);
				}
				break;
					
			case '>=':
				{
					pFun->emit(AS_Oper(x86_Jcc(0x8D, s->cjump.t), NULL, NULL,
						new AS_Targets(new Temp_labelList(s->cjump.t, new Temp_labelList(s->cjump.f, NULL)))));

				//bcc(COND_LT);	//emit_op(JOP_if_icmple);
				}
				break;

			default:
				ASSERT(0);
			}

		//	ASSERT(0);
#if 0
			s->cjump.f->m_branches.push_back(ftell(fileout));
			printf(" t=%d, f=%d", s->cjump.t->m_n, s->cjump.f->m_n);

			long offset = 0;
			fwrite(&offset, 4, 1, fileout);
#endif

#if 0
			de(r1);
#endif
			printf("\n");
		}
		break;

	case T_Stm::T_EXP:
		{
			munchExpression(pFun, s->expr);
		}
		break;

	///

	case T_Stm::T_LBRAC:
		{
			pFun->emit(AS_LBrac());
		}
		break;

	case T_Stm::T_RBRAC:
		{
			pFun->emit(AS_RBrac());
		}
		break;

	case T_Stm::T_LSYM:
		{
			pFun->emit(AS_LSym(s->declarator));
		}
		break;

	case T_Stm::T_LABEL:
		{
			printf("label %d\n", s->label->m_n);

		//	ASSERT(0);
			pFun->emit(AS_Label(s->label));
#if 0
			ASSERT(s->label->m_pos == -1);
#endif
			MessageBeep(-1);
			// TODO
#if 0
			s->label->m_pos = ftell(fileout);
			FlushLabel(s->label);
#endif
		}
		break;

	default:
		ASSERT(0);
	}
}

// virtual
void CCodeGenx86::WriteStatement(CFunctionCode* pFun, T_Stm* s)
{
	munchStatement(pFun, s);
}

#endif

//}	// cpp
}
