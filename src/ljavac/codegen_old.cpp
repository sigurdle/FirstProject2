int CCodeGenerator::emit_expr2(CFunctionCode* pFunc, cpp::CExpression* pExpr, ea *pDestEA)
{
	ASSERT(0);
#if 0
	if (pExpr->tok.type == CToken::tok_integer ||
		pExpr->tok.type == CToken::tok_double)
	{
		pDestEA->m_mode = 7;
		pDestEA->m_reg = 4;
		pDestEA->m_value = pExpr->tok.int32;

		return 1;
	}
	else if (pExpr->tok.type == CToken::tok_ident)
	{
		if (TRUE)	// 68000
		{
			if (pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex == 0)	// local variable
			{
				if (pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset < 0)
				{
					printf("");
				}

				pDestEA->m_mode = 1;
				pDestEA->m_reg = AllocAddrRegister()-8;

				ea _ea(5,5);	// n(a5)
			//	_ea.m_value = -pExpr->m_pDeclaratorRef->m_pDeclarator->m_pType->get_sizeof() - (pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset+pFunc->m_spOffset);
				_ea.m_value = -pExpr->m_pType->get_sizeof() - (pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset+pFunc->m_spOffset);

				if (_ea.m_mode != pDestEA->m_mode ||
					_ea.m_reg != pDestEA->m_reg ||
					_ea.m_lea != pDestEA->m_lea ||
					_ea.m_value != pDestEA->m_value)
				{
					//if (pDestEA->m_lea)
					{
#if 0
						if (pDestEA->m_mode == 1)
						{
							((CCodeGen68*)this)->lea(pDestEA->m_reg, _ea.m_mode,_ea.m_reg);

							fput16(fileout, _ea.m_value);
						}
						else
#endif
						{
							int dreg = AllocDataRegister();
							((CCodeGen68*)this)->moveq(_ea.m_value, dreg);
							((CCodeGen68*)this)->add(2/*L ea+dn -> dn*/, dreg, 1,5);	// a5,dn
							pDestEA->m_reg = dreg;
							pDestEA->m_mode = 1;
							((CCodeGen68*)this)->move(SIZE_L, 0,dreg, pDestEA->m_mode,pDestEA->m_reg);

#if 0
							if (pDestEA->m_mode == 4)	// -(An)
							{
								((CCodeGen68*)this)->move(SIZE_L, 0,dreg, pDestEA->m_mode,pDestEA->m_reg);
							}
							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, pDestEA->m_value);
							}
#endif
							FreeRegister(dreg);
						}
					}
#if 0
					else
					{
						ULONG size = pExpr->m_pType->get_sizeof();
						if (size == 1)
							((CCodeGen68*)this)->move(SIZE_B, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else if (size == 2)
							((CCodeGen68*)this)->move(SIZE_W, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else if (size == 4)
							((CCodeGen68*)this)->move(SIZE_L, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else
						{
							printf("unsupported sizeof");
							ASSERT(0);
						}

						fput16(fileout, _ea.m_value);
						if (pDestEA->m_mode == 5)
						{
							fput16(fileout, pDestEA->m_value);
						}
					}
#endif
				}
			}
			else	// global variable
			{
			//	((CCodeGen68*)this)->move(SIZE_L, 0,--dreg, 1,dreg);	// move #0,an
			//	dreg++;
				((CCodeGen68*)this)->move(SIZE_L, 7,1, pDestEA->m_mode,pDestEA->m_reg);	// move $,dn
			//	dreg++;

				FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
				ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
				ImageReloc->SymbolTableIndex = pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;//TODO symbolIndex;//pExpr->m_pDeclarator->m_symbolIndex-1;	// reference to name of function being called
			//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
				ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;

				fput32(fileout, pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset+pFunc->m_spOffset);
			//	fput32(fileout, 0);

				pFunc->AddRelocation(ImageReloc);
			}
		}

		return 1;
	}
	else if (pExpr->tok.type == CToken::tok_symbol)
	{
		switch (pExpr->tok.symbol)
		{
		case (DWORD)'('|('U'<<8):	// cast-expression
			{
				return emit_expr2(pFunc, pExpr->right, pDestEA);
			}
			break;

		case '.':
			{
				// object.member
				// pExpr->left = object
				// pExpr->right = member
				
				//	if (emit_expr(pExpr->right) != 1)
				//		printf("Error in expression\n");
				//	BYTE indexRegister = reg-1;
				
			//	cpp::CMember* pMember = pExpr->right->m_pMember;
			//	int offset = pMember->m_offset;
				cpp::CDeclarator* pDeclarator = pExpr->right->m_pDeclaratorRef->m_pDeclarator;
				
				if (TRUE)	// 68000
				{
					// evaluate base
					ea base;//(1,AllocAddrRegister()-8);
					base.m_lea = true;

					if (emit_expr2(pFunc, pExpr->left, &base) != 1)
						printf("Error in expression\n");
						
			
#if 0
					if (pValue)
					{
						ASSERT(0);

						ea dest(5,base.m_reg);
						if (pDeclarator->m_pType->get_sizeof() == 1)
						{
							((CCodeGen68*)this)->move(SIZE_B, pValue->m_mode,pValue->m_reg, dest.m_mode,dest.m_reg);
						}
						else if (pDeclarator->m_pType->get_sizeof() == 2)
						{
							((CCodeGen68*)this)->move(SIZE_W, pValue->m_mode,pValue->m_reg, dest.m_mode,dest.m_reg);
						}
						else if (pDeclarator->m_pType->get_sizeof() == 4)
						{
							((CCodeGen68*)this)->move(SIZE_L, pValue->m_mode,pValue->m_reg, dest.m_mode,dest.m_reg);
						}
						else
							ASSERT(0);
					
						fput16(fileout, pDeclarator->m_spOffset);
					}
					else
#endif
					{
						// Experimental, evaluate code for calculating address of member

						if (TRUE)
						{
							//((CCodeGen68*)this)->move(pDeclarator->m_spOffset, 2/*long*/);

							if (pDeclarator->m_spOffset > 0)
							{
								if (pDeclarator->m_spOffset > 8)
								{
									// dn + ea -> ea
									// ea = #<data>
									((CCodeGen68*)this)->add(3/* an word*/, base.m_reg, 7,4);
									fput16(fileout, pDeclarator->m_spOffset);


									// dn + ea -> ea
								//	((CCodeGen68*)this)->add(3/* an word*/, base.m_reg, pDestEA->m_mode,pDestEA->m_reg);
									//((CCodeGen68*)this)->addi(pDeclarator->m_spOffset, 2/*long*/, base.m_mode, base.m_reg);
								}
								else
									((CCodeGen68*)this)->addq(pDeclarator->m_spOffset, 2/*long*/, base.m_mode, base.m_reg);
							}

//#if 0	// huh
							pDestEA->m_mode = base.m_mode;	// an
							pDestEA->m_reg = base.m_reg;//AllocAddrRegister()-8;

						//	((CCodeGen68*)this)->move(SIZE_L, base.m_mode, base.m_reg, pDestEA->m_mode,pDestEA->m_reg);
//#endif
#if 0
							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, pDestEA->m_value);
							}
#endif
						}
						else
						{
							ea src(5,base.m_reg);

							unsigned int _sizeof = pDeclarator->m_pType->get_sizeof();

							if (_sizeof == 1)
							{
								((CCodeGen68*)this)->move(SIZE_B, src.m_mode,src.m_reg, pDestEA->m_mode,pDestEA->m_reg);
							}
							else if (_sizeof == 2)
							{
								((CCodeGen68*)this)->move(SIZE_W, src.m_mode,src.m_reg, pDestEA->m_mode,pDestEA->m_reg);
							}
							else if (_sizeof == 4)
							{
								((CCodeGen68*)this)->move(SIZE_L, src.m_mode,src.m_reg, pDestEA->m_mode,pDestEA->m_reg);
							}
							else
								ASSERT(0);
						
							fput16(fileout, pDeclarator->m_spOffset);
							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, (short)pDestEA->m_value);
							}
						}
					}
					FreeRegister(base.m_reg+8);
				}
				else
				{
	#if 0
					// This will emit expression for base
					if (emit_expr(pFunc, pExpr->left/*, mov*/) != 1)
						printf("Error in expression\n");
					//BYTE baseRegister = reg-1;
					
					if (mov)
					{
						putc(0x8B, fileout);	// mov
					}
					else
					{
						putc(0x8D, fileout);	// lea
					}
					
					BYTE DestReg = 0;	// EAX
					BYTE Mod = 1;	// 8-bit displacement
					BYTE RM = reg-1;
					//BYTE scale = 0;	// *1
					
					BYTE ModRM = RM | (DestReg<<3) | (Mod<<6);
					//BYTE SIB = baseRegister | (indexRegister<<3) | (scale<<6);
					
					putc(ModRM, fileout);
					//putc(SIB, fileout);
					putc(offset, fileout);
	#endif
				}
				
				return 1;
			}
			break;
		}
	}
#endif

	return 0;
}

// returns the number of arguments that we've pushed on the stack
int CCodeGenerator::emit_expr(CFunctionCode* pFunc, cpp::CExpression* pExpr, ea *pDestEA, ea *pValue/*= NULL*/)
{
	ASSERT(0);
#if 0
	if (pExpr->tok.type == CToken::tok_integer ||
		pExpr->tok.type == CToken::tok_double)
	{
		if (TRUE)	// 68000
		{
			if (pDestEA)
			{
				ULONG size = pExpr->m_pType->get_sizeof();

				if (size == 1)
				{
					if (pExpr->tok.int32 != 0)
					{
						((CCodeGen68*)this)->move(SIZE_B, 7,4, pDestEA->m_mode,pDestEA->m_reg);
						fput16(fileout, (char)pExpr->tok.int32);
					}
					else
					{
						((CCodeGen68*)this)->clr(0, pDestEA->m_mode, pDestEA->m_reg);
					}

					if (pDestEA->m_mode == 5)
					{
						fput16(fileout, (short)pDestEA->m_value);
					}
				}
				else if (size == 2)
				{
					if (pExpr->tok.int32 != 0)
					{
						((CCodeGen68*)this)->move(SIZE_W, 7,4, pDestEA->m_mode,pDestEA->m_reg);
						fput16(fileout, (short)pExpr->tok.int32);
					}
					else
					{
						((CCodeGen68*)this)->clr(1, pDestEA->m_mode, pDestEA->m_reg);
					}

					if (pDestEA->m_mode == 5)
					{
						fput16(fileout, (short)pDestEA->m_value);
					}
				}
				else if (size == 4)
				{
					if (pExpr->tok.int32 != 0 || pDestEA->m_mode == 1)
					{
						((CCodeGen68*)this)->move(SIZE_L, 7,4, pDestEA->m_mode,pDestEA->m_reg);
						fput32(fileout, (long)pExpr->tok.int32);
					}
					else
					{
						((CCodeGen68*)this)->clr(2, pDestEA->m_mode, pDestEA->m_reg);
					}

					if (pDestEA->m_mode == 5)
					{
						fput16(fileout, (short)pDestEA->m_value);
					}
				}
				else if (size == 8)
				{
					if (pDestEA->m_mode == 5)
					{
						((CCodeGen68*)this)->move(SIZE_L, 7,4, pDestEA->m_mode,pDestEA->m_reg);
						fput32(fileout, ((DWORD*)&pExpr->tok.double64)[0]);
						fput16(fileout, (short)pDestEA->m_value);

						((CCodeGen68*)this)->move(SIZE_L, 7,4, pDestEA->m_mode,pDestEA->m_reg);
						fput32(fileout, ((DWORD*)&pExpr->tok.double64)[1]);
						fput16(fileout, (short)pDestEA->m_value+4);
					}
					else
					{
						ASSERT(0);
					}
				}
				else
				{
					printf("unsupported sizeof");
					ASSERT(0);
				}
			}
		}
		else
		{
			mov_r32_imm32(reg++, pExpr->tok.int32);
		}
		return 1;
	}
	else if (pExpr->tok.type == CToken::tok_string || pExpr->tok.type == CToken::tok_wstring)
	{
		if (TRUE)	// // 68000
		{
			if (pDestEA)
			{
				//int reg = pDestEA->m_reg;//dreg;//pExprR->m_pDeclarator->m_libcall.m_reg;
				//dreg++;
				//if (reg < 8)
				{
				//	BYTE dn = reg;
					((CCodeGen68*)this)->move(SIZE_L, 7,4, pDestEA->m_mode,pDestEA->m_reg);
				}
				/*
				else
				{
					BYTE an = reg-8;
					((CCodeGen68*)this)->move(SIZE_L, 7,4, 1,an);	// movea #,an
				//	fput32(fileout, pArgExpr->tok.int32);
				}
				*/

				{
					FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];

					ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
					ImageReloc->SymbolTableIndex = 0;//TODO symbolIndex;//pExpr->m_pDeclarator->m_symbolIndex-1;	// reference to name of function being called
					ImageReloc->pExpr = pExpr;
					ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
				//	ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;

					long offset = 0;
					fwrite(&offset, 1, 4, fileout);

					pFunc->AddRelocation(ImageReloc);
				}
			}
		}
		else
		{
			putc(0x68, fileout);	// push imm32
			//fwrite(&value, 1, 4, fileout);

#if 0
			IMAGE_SYMBOL* pSymbol;
			int symbolIndex = pFunc->m_ofile->AddSymbol("some_text", &pSymbol);
			pSymbol->SectionNumber = pFunc->m_ofile->AddSection(
#endif

			{
				FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];

				ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
				ImageReloc->SymbolTableIndex = 2;//TODO symbolIndex;//pExpr->m_pDeclarator->m_symbolIndex-1;	// reference to name of function being called
			//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
				ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;

				long offset = 0;
				fwrite(&offset, 1, 4, fileout);

				pFunc->AddRelocation(ImageReloc);
			}
		}

		/*
		if (TRUE)	// 68000
		{
			((CCodeGen68*)this)->move(SIZE_L, 7,4, 0,dreg);
			fput32(fileout, pExpr->tok.int32);
			dreg++;
		}
		else
		{
			mov_r32_imm32(reg++, pExpr->tok.int32);
		}
		*/
		return 1;
	}
	else if (pExpr->tok.type == CToken::tok_keyword && pExpr->tok.pkw->n == cpp::KW_THIS)
	{
		ea _ea(5,5);	// n(a5)
		_ea.m_value = 8;

		// ??
		if (_ea.m_mode != pDestEA->m_mode ||
			_ea.m_reg != pDestEA->m_reg ||
			_ea.m_lea != pDestEA->m_lea ||
			_ea.m_value != pDestEA->m_value)
		{
			if (pDestEA->m_lea)
			{
				if (pDestEA->m_mode == 4)	// -(An)
				{
					int dreg = AllocDataRegister();
					((CCodeGen68*)this)->moveq(_ea.m_value, dreg);
					((CCodeGen68*)this)->add(2/*L ea+dn -> dn*/, dreg, 1,5);	// a5,dn
					((CCodeGen68*)this)->move(SIZE_L, 0,dreg, pDestEA->m_mode,pDestEA->m_reg);
					FreeRegister(dreg);
				}
				else if (pDestEA->m_mode == 1)
				{
					((CCodeGen68*)this)->lea(pDestEA->m_reg, _ea.m_mode,_ea.m_reg);

					fput16(fileout, _ea.m_value);
				}
				else
					ASSERT(0);
			}
			else
			{
				ULONG size = pExpr->m_pType->get_sizeof();
				if (size == 1)
					((CCodeGen68*)this)->move(SIZE_B, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
				else if (size == 2)
					((CCodeGen68*)this)->move(SIZE_W, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
				else if (size == 4)
					((CCodeGen68*)this)->move(SIZE_L, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
				else
				{
					printf("unsupported sizeof");
					ASSERT(0);
				}

				fput16(fileout, _ea.m_value);
				if (pDestEA->m_mode == 5)
				{
					fput16(fileout, pDestEA->m_value);
				}
			}
		}

		return 1;
	}
#if 0
	else if (pExpr->tok.type == CToken::tok_keyword)
	{
		if (pExpr->tok.pkw->n == KW_TRUE)
			push_iconst(1);
		else if (pExpr->tok.pkw->n == KW_FALSE)
			push_iconst(0);

		return 1;
	}
#endif
	else if (pExpr->tok.type == CToken::tok_ident)
	{
		//int x;
		//x+1 = 4;

		if (TRUE)	// 68000
		{
			if (pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex == 0)	// local variable
			{
				if (pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset < 0)
				{
					printf("");
				}

				ea _ea(5,5);	// n(a5)
			//	_ea.m_value = -pExpr->m_pDeclaratorRef->m_pDeclarator->m_pType->get_sizeof() - (pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset+pFunc->m_spOffset);
				_ea.m_value = -pExpr->m_pType->get_sizeof() - (pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset+pFunc->m_spOffset);

				if (_ea.m_mode != pDestEA->m_mode ||
					_ea.m_reg != pDestEA->m_reg ||
					_ea.m_lea != pDestEA->m_lea ||
					_ea.m_value != pDestEA->m_value)
				{
					if (pDestEA->m_lea)
					{
						if (pDestEA->m_mode == 1)
						{
							((CCodeGen68*)this)->lea(pDestEA->m_reg, _ea.m_mode,_ea.m_reg);

							fput16(fileout, _ea.m_value);
						}
						else
						{
							int dreg = AllocDataRegister();
							((CCodeGen68*)this)->moveq(_ea.m_value, dreg);
							((CCodeGen68*)this)->add(2/*L ea+dn -> dn*/, dreg, 1,5);	// a5,dn

							//if (pDestEA->m_mode == 4)	// -(An)
							{
								((CCodeGen68*)this)->move(SIZE_L, 0,dreg, pDestEA->m_mode,pDestEA->m_reg);
							}
							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, pDestEA->m_value);
							}
							FreeRegister(dreg);
							//	((CCodeGen68*)this)->move(SIZE_L, 0,dreg, pDestEA->m_mode,pDestEA->m_reg);
							//}
							//else
							//	ASSERT(0);
						}
					}
					else
					{
						ULONG size = pExpr->m_pType->get_sizeof();
						if (size == 1)
							((CCodeGen68*)this)->move(SIZE_B, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else if (size == 2)
							((CCodeGen68*)this)->move(SIZE_W, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else if (size == 4)
							((CCodeGen68*)this)->move(SIZE_L, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else
						{
							printf("unsupported sizeof");
							ASSERT(0);
						}

						fput16(fileout, _ea.m_value);
						if (pDestEA->m_mode == 5)
						{
							fput16(fileout, pDestEA->m_value);
						}
					}
				}
			}
			else	// global variable
			{
			//	((CCodeGen68*)this)->move(SIZE_L, 0,--dreg, 1,dreg);	// move #0,an
			//	dreg++;
				((CCodeGen68*)this)->move(SIZE_L, 7,1, pDestEA->m_mode,pDestEA->m_reg);	// move $,dn
			//	dreg++;

				FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
				ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
				ImageReloc->SymbolTableIndex = pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;//TODO symbolIndex;//pExpr->m_pDeclarator->m_symbolIndex-1;	// reference to name of function being called
			//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
				ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;

				fput32(fileout, pExpr->m_pDeclaratorRef->m_pDeclarator->m_spOffset+pFunc->m_spOffset);
			//	fput32(fileout, 0);

				pFunc->AddRelocation(ImageReloc);
			}
		}
		else
		{
			ASSERT(0);
#if 0
			if (mov)
			{
				mov_r32_rm32_disp(reg++/*EAX*/, 5/*EBP*/, pExpr->m_pDeclarator->m_spOffset+pFunc->m_spOffset);
			}
			else	// lea
			{
				lea_r32_rm32_disp(reg++/*EAX*/, 5/*EBP*/, pExpr->m_pDeclarator->m_spOffset+pFunc->m_spOffset);
			}
#endif
		}

		return 1;
	}
	else if (pExpr->tok.type == CToken::tok_symbol)
	{
		switch (pExpr->tok.symbol)
		{
		case '(':	// function call
			{
				// push parameters in reverse order
				
				cpp::CExpression* pExprR = pExpr->right;
				
				int stackSize = 0;

				while (pExprR)
				{
					cpp::CExpression* pArgExpr = pExprR->left;
					
#if 0
					if (pArgExpr->tok.type == CToken::tok_integer)
					{
						if (TRUE)	// // 68000
						{
							int reg = pExprR->m_pDeclarator->m_libcall.m_reg;
							if (reg < 8)
							{
								BYTE dn = reg;
								((CCodeGen68*)this)->move(SIZE_L, 7,4, 0,dn);	// move.l #,dn
								fput32(fileout, pArgExpr->tok.int32);
							}
							else
							{
								BYTE an = reg-8;
								((CCodeGen68*)this)->move(SIZE_L, 7,4, 1,an);	// movea.l #,an
								fput32(fileout, pArgExpr->tok.int32);
							}
						}
						else
						{
							push_imm(pArgExpr->tok.int32);
						}
					}
					else if (pArgExpr->tok.type == CToken::tok_string)
					{
						if (m_processor_id == CPU_68020)
						{
							int reg = pExprR->m_pDeclarator->m_libcall.m_reg;
							if (reg < 8)
							{
								ASSERT(0);
								/*
								BYTE dn = reg;
								((CCodeGen68*)this)->move(SIZE_W, 7,4, 0,dn);
								fput16(fileout, pArgExpr->tok.int32);
								*/
							}
							else
							{
								BYTE an = reg-8;
								((CCodeGen68*)this)->move(SIZE_L, 7,4, 1,an);	// movea #0,an
								//	fput32(fileout, pArgExpr->tok.int32);
								
								{
									FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
									
									ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
									ImageReloc->SymbolTableIndex = -1;//TODO symbolIndex;//pExpr->m_pDeclarator->m_symbolIndex-1;	// reference to name of function being called
									ImageReloc->pExpr = pArgExpr;
									ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
									//	ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
									
									long offset = 0;
									fwrite(&offset, 1, 4, fileout);
									
									pFunc->m_ImageRelocation.push_back(ImageReloc);
								}
							}
						}
						else if (m_processor_id == CPU_IX86)
						{
#if 0
							putc(0x68, fileout);	// push imm32
							//fwrite(&value, 1, 4, fileout);
							
#if 0
							IMAGE_SYMBOL* pSymbol;
							int symbolIndex = pFunc->m_ofile->AddSymbol("some_text", &pSymbol);
							pSymbol->SectionNumber = pFunc->m_ofile->AddSection(
#endif
								
							{
								FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
								
								ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
								ImageReloc->SymbolTableIndex = 2;//TODO symbolIndex;//pExpr->m_pDeclarator->m_symbolIndex-1;	// reference to name of function being called
								//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
								ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
								
								long offset = 0;
								fwrite(&offset, 1, 4, fileout);
								
								pFunc->m_ImageRelocation.push_back(ImageReloc);
							}
#endif
						}
						else
							ASSERT(0);
					}
					else
#endif
					{
						if (m_processor_id == CPU_68020)
						{
							int destreg = -1;
							
							if (pExprR->m_pDeclaratorRef)
								destreg = pExprR->m_pDeclaratorRef->m_pDeclarator->m_libcall.m_reg;
							
							if (destreg != -1)	// place argument in a register
							{
								AllocAnyRegister(destreg);

								if (destreg < 8)
								{
									if (emit_expr(pFunc, pArgExpr, &ea(0, destreg)) != 1)
										printf("Error in expression\n");
									//dreg--;
								}
								else
								{
									if (emit_expr(pFunc, pArgExpr, &ea(1, destreg-8)) != 1)
										printf("Error in expression\n");
								}
							}
							else	// push argument on stack
							{
								stackSize += 4;
								ea _destea(4,7);	// -(a7)
								if (emit_expr(pFunc, pArgExpr, &_destea) != 1)
									printf("Error in expression\n");
							}

#if 0
							if (reg < 8)
							{
								BYTE dn = reg;
								if (dn != dreg)
								{
									((CCodeGen68*)this)->move(SIZE_L, 0,dreg, 0,dn);	// move dn,dn
								}
							}
							else
							{
								BYTE an = reg-8;
								((CCodeGen68*)this)->move(SIZE_L, 0,dreg, 1,an);	// movea dn,an
							}
#endif
						}
						else if (m_processor_id == CPU_IX86)
						{
						//	if (pArgExpr->tok.type == CToken::tok_integer)
								push_imm(0);
						//	else
						//		ASSERT(0);

#if 0
							ASSERT(0);
#if 0
							if (emit_expr(pFunc, pArgExpr) != 1)
								printf("Error in expression\n");
							
							reg--;
							if (reg == 0)
							{
								putc(0x50, fileout);	// push eax
							}
							else
							{
								ASSERT(0);
							}
#endif
#endif
						}
						else
							ASSERT(0);
					}
					
					pExprR = pExprR->right;
				}
				
				if (m_processor_id == CPU_68020)	// 68000
				{
					if (pExpr->left->m_pType->m_pFunction->m_libcall.m_offset != 0)	// libcall
					{
						((CCodeGen68*)this)->move(SIZE_L, 7,1, 1,areg_6);	// move $,a6
						{
							FRelocation* ImageReloc = new FRelocation;
							ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
							ImageReloc->SymbolTableIndex = pExpr->m_pBaseDeclarator->m_pDeclarator->m_symbolIndex;
							//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
							ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
							
							ASSERT(pExpr->m_pBaseDeclarator->m_pDeclarator->m_spOffset != -1);
							fput32(fileout, pExpr->m_pBaseDeclarator->m_pDeclarator->m_spOffset);
							
							pFunc->AddRelocation(ImageReloc);
						}
						
						// Address Register Indirect with Displacement
						((CCodeGen68*)this)->jsr(5/*mode*/, areg_6);
						fput16(fileout, pExpr->left->m_pType->m_pFunction->/*m_pDeclarator->*/m_libcall.m_offset);
					}
					else
					{
						((CCodeGen68*)this)->jsr(7,1);	// (xxx).L
						{
							FRelocation* ImageReloc = new FRelocation;
							ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
							ImageReloc->SymbolTableIndex = pExpr->left->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;
							//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
							ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
							
							fput32(fileout, 0);//pExpr->m_pBaseDeclarator->m_pDeclarator->m_spOffset);
							
							pFunc->AddRelocation(ImageReloc);
						}

						if (stackSize > 0)	// adjust stack pointer
						{
							if (stackSize <= 8)
							{
								((CCodeGen68*)this)->addq(stackSize, 2/*size*/,1,7);	// addq #stackSize,a7
							}
							else
							{
								((CCodeGen68*)this)->add(3/*word*/, 7/*a7*/, 7,4);	// adda #stackSize,a7
								fput16(fileout, stackSize);
							}
						}
					}
					
					if (pDestEA)
					{
						if (pDestEA->m_mode != 0 || pDestEA->m_reg != 0)
						{
							((CCodeGen68*)this)->move(SIZE_L, 0,0/*d0*/, pDestEA->m_mode, pDestEA->m_reg);	// move d0,dreg
							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, pDestEA->m_value);
							}
						}
					}
				}
				else if (m_processor_id == CPU_IX86)
				{
					//	putc(0xE8, fileout);	// call
					putc(0xFF, fileout);	// call rm32
					
					BYTE Mod = 0;
					BYTE RM = 5;
					BYTE Reg = 2;	// ?? what's this for ??
					BYTE ModRM = RM | (Reg<<3) | (Mod<<6);
					putc(ModRM, fileout);
					
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
					
					FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
					
					ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
					ImageReloc->SymbolTableIndex = pExpr->left->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;
			//		ImageReloc->SymbolTableIndex = pExpr->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;	// reference to name of function being called
					//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
					ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
					
					long offset = 0;
					fwrite(&offset, 1, 4, fileout);
				
					pFunc->AddRelocation(ImageReloc);
				}
				else
					ASSERT(0);

			// Free the registers used in arguments
				pExprR = pExpr->right;

				while (pExprR)
				{
					cpp::CExpression* pArgExpr = pExprR->left;

					int destreg = -1;
							
					if (pExprR->m_pDeclaratorRef)
						destreg = pExprR->m_pDeclaratorRef->m_pDeclarator->m_libcall.m_reg;
							
					if (destreg != -1)	// place argument in a register
					{
						FreeRegister(destreg);
					}

					pExprR = pExprR->right;
				}

				return 1;
			}
			break;
	
		case ((DWORD)'*'|('U'<<8)):	// Dereference right pExpr
			{
				ASSERT(pExpr->left == NULL);
				
				if (pDestEA->m_lea)
				{
					ea _ea(pDestEA->m_mode, pDestEA->m_reg);
					_ea.m_lea = false;

					if (emit_expr(pFunc, pExpr->right, &_ea) != 1)
						printf("Error in expression\n");

					return 1;
				}
				else
				{
					BYTE an = AllocAddrRegister()-8;
					ea _ea(1, an);
					int n;
					if ((n = emit_expr(pFunc, pExpr->right, &_ea)) != 1)
					{
						printf("Error in expression\n");
					}
					else
					{
						ea _ea(2,an);	// move (an)
						
						int _sizeof = pExpr->right->m_pType->GetType()->m_pPointerTo->get_sizeof();
						// movea
						if (_sizeof == 1)
							((CCodeGen68*)this)->move(SIZE_B, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else if (_sizeof == 2)
							((CCodeGen68*)this)->move(SIZE_W, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else if (_sizeof == 4)
							((CCodeGen68*)this)->move(SIZE_L, _ea.m_mode,_ea.m_reg, pDestEA->m_mode,pDestEA->m_reg);
						else
							ASSERT(0);
						
						//	areg--;
					}
					FreeRegister(an+8);
					
					return 1;
				}
			}
			break;
		
		case (DWORD)'('|('U'<<8):	// cast-expression
			{
				unsigned int _sizeof0 = pExpr->m_pType->GetType()->get_sizeof();
				unsigned int _sizeof1 = pExpr->right->m_pType->GetType()->get_sizeof();
				if (_sizeof0 == _sizeof1)
				{
					if (emit_expr(pFunc, pExpr->right, pDestEA) != 1)
						printf("Error in expression\n");
				}
				// sign extend
				else if (_sizeof0 == 2 && _sizeof1 == 1)
				{
					if (emit_expr(pFunc, pExpr->right, pDestEA) != 1)
						printf("Error in expression\n");

					ASSERT(pDestEA->m_mode == 0);	// data register

					((CCodeGen68*)this)->ext(pDestEA->m_reg, 2/*byte -> word*/);
				}
				else if (_sizeof0 == 4 && _sizeof1 == 2)
				{
					if (emit_expr(pFunc, pExpr->right, pDestEA) != 1)
						printf("Error in expression\n");

					ASSERT(pDestEA->m_mode == 0);	// data register

					((CCodeGen68*)this)->ext(pDestEA->m_reg, 3/*word -> long*/);
				}
				else if (_sizeof0 == 4 && _sizeof1 == 1)
				{
					if (emit_expr(pFunc, pExpr->right, pDestEA) != 1)
						printf("Error in expression\n");

					ASSERT(pDestEA->m_mode == 0);	// data register

					((CCodeGen68*)this)->ext(pDestEA->m_reg, 2/*byte -> word*/);
					((CCodeGen68*)this)->ext(pDestEA->m_reg, 3/*word -> long*/);
				}
				// truncate
				else if (_sizeof0 < _sizeof1)
				{
					//if (pDestEA->m_mode == 5)
					{
					//	ea dest(pDestEA->m_mode, pDestEA->m_reg);
					//	dest.m_value = pDestEA->m_value + 3;
						//CType* pExpr->right;
						cpp::CType* pOldType = pExpr->right->m_pType;
						//pFunc->m_spOffset = 3;

						pExpr->right->m_pType = pExpr->m_pType;

						if (emit_expr(pFunc, pExpr->right, pDestEA) != 1)
							printf("Error in expression\n");

					//	pFunc->m_spOffset = 0;
						pExpr->right->m_pType = pOldType;
					}
					/*
					else
					{
						ASSERT(0);
					}
					*/

					printf("");
				}
				else
				{
					ASSERT(0);
				}
			
				return 1;
			}
			break;

		case ((DWORD)'&'|('U'<<8)):	// Address-of right pExpr
			{
				ASSERT(pExpr->left == NULL);
				
				// TODO
				ea _ea(pDestEA->m_mode, pDestEA->m_reg);
				_ea.m_lea = true;
				_ea.m_value = pDestEA->m_value;
				if (emit_expr(pFunc, pExpr->right, &_ea) != 1)
					printf("Error in expression\n");
				
				return 1;
				
				/*
				ASSERT(pExpr->left == NULL);
				
				  if (emit_expr(pExpr->right) != 1)
				  printf("Error in expression\n");
				*/
				
				return 1;
			}
			break;
			
		case '.':
			{
				// object.member
				// pExpr->left = object
				// pExpr->right = member
				
				//	if (emit_expr(pExpr->right) != 1)
				//		printf("Error in expression\n");
				//	BYTE indexRegister = reg-1;
				
			//	cpp::CMember* pMember = pExpr->right->m_pMember;
			//	int offset = pMember->m_offset;
				cpp::CDeclarator* pDeclarator = pExpr->right->m_pDeclaratorRef->m_pDeclarator;
				
				if (TRUE)	// 68000
				{
					// evaluate base
					ea base(1,AllocAddrRegister()-8);
					base.m_lea = true;
					//if (_A[4] != (long)pExpr->left)
					{
						if (emit_expr(pFunc, pExpr->left, &base) != 1)
							printf("Error in expression\n");
						
						//	((CCodeGen68*)this)->lea(4, 1,4);
						//	_A[4] = (long)pExpr->left;
					}
			
					if (pValue)
					{
#if 0
						ASSERT(0);

						ea dest(5,base.m_reg);
						if (pDeclarator->m_pType->get_sizeof() == 1)
						{
							((CCodeGen68*)this)->move(SIZE_B, pValue->m_mode,pValue->m_reg, dest.m_mode,dest.m_reg);
						}
						else if (pDeclarator->m_pType->get_sizeof() == 2)
						{
							((CCodeGen68*)this)->move(SIZE_W, pValue->m_mode,pValue->m_reg, dest.m_mode,dest.m_reg);
						}
						else if (pDeclarator->m_pType->get_sizeof() == 4)
						{
							((CCodeGen68*)this)->move(SIZE_L, pValue->m_mode,pValue->m_reg, dest.m_mode,dest.m_reg);
						}
						else
							ASSERT(0);
					
						fput16(fileout, pDeclarator->m_spOffset);
#endif
					}
					else
					{
						// Experimental, evaluate code for calculating address of member

						if (TRUE)
						{
							//((CCodeGen68*)this)->move(pDeclarator->m_spOffset, 2/*long*/);

							if (pDeclarator->m_spOffset > 0)
							{
								if (pDeclarator->m_spOffset > 8)
								{
									// dn + ea -> ea
									// ea = #<data>
									((CCodeGen68*)this)->add(3/* an word*/, base.m_reg, 7,4);
									fput16(fileout, pDeclarator->m_spOffset);


									// dn + ea -> ea
								//	((CCodeGen68*)this)->add(3/* an word*/, base.m_reg, pDestEA->m_mode,pDestEA->m_reg);
									//((CCodeGen68*)this)->addi(pDeclarator->m_spOffset, 2/*long*/, base.m_mode, base.m_reg);
								}
								else
									((CCodeGen68*)this)->addq(pDeclarator->m_spOffset, 2/*long*/, base.m_mode, base.m_reg);
							}

							((CCodeGen68*)this)->move(SIZE_L, base.m_mode, base.m_reg, pDestEA->m_mode,pDestEA->m_reg);
							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, pDestEA->m_value);
							}
						}
						else
						{
							ea src(5,base.m_reg);

							unsigned int _sizeof = pDeclarator->m_pType->get_sizeof();

							if (_sizeof == 1)
							{
								((CCodeGen68*)this)->move(SIZE_B, src.m_mode,src.m_reg, pDestEA->m_mode,pDestEA->m_reg);
							}
							else if (_sizeof == 2)
							{
								((CCodeGen68*)this)->move(SIZE_W, src.m_mode,src.m_reg, pDestEA->m_mode,pDestEA->m_reg);
							}
							else if (_sizeof == 4)
							{
								((CCodeGen68*)this)->move(SIZE_L, src.m_mode,src.m_reg, pDestEA->m_mode,pDestEA->m_reg);
							}
							else
								ASSERT(0);
						
							fput16(fileout, pDeclarator->m_spOffset);
							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, (short)pDestEA->m_value);
							}
						}
					}
					FreeRegister(base.m_reg+8);
				}
				else
				{
	#if 0
					// This will emit expression for base
					if (emit_expr(pFunc, pExpr->left/*, mov*/) != 1)
						printf("Error in expression\n");
					//BYTE baseRegister = reg-1;
					
					if (mov)
					{
						putc(0x8B, fileout);	// mov
					}
					else
					{
						putc(0x8D, fileout);	// lea
					}
					
					BYTE DestReg = 0;	// EAX
					BYTE Mod = 1;	// 8-bit displacement
					BYTE RM = reg-1;
					//BYTE scale = 0;	// *1
					
					BYTE ModRM = RM | (DestReg<<3) | (Mod<<6);
					//BYTE SIB = baseRegister | (indexRegister<<3) | (scale<<6);
					
					putc(ModRM, fileout);
					//putc(SIB, fileout);
					putc(offset, fileout);
	#endif
				}
				
				return 1;
			}
			break;
			
		case '[':
			{
				ASSERT(0);
#if 0
				if (TRUE)
				{
					if (emit_expr(pFunc, pExpr->right, &ea(0,dreg++)) != 1)
						printf("Error in expression\n");

					cpp::CExpression* pLeft = new cpp::CExpression(pExpr->left->m_pScope);
					pLeft->tok = pExpr->left
					pLeft->m_pType = pExpr->left->m_pType->GetType()->m_pPointerTo;
					pLeft->left = pExpr->left->left;
					pLeft->right = pExpr->left->right;

					if (emit_expr(pFunc, pLeft, &ea(1,areg++)) != 1)
						printf("Error in expression\n");

					pLeft->left = NULL;
					pLeft->right = NULL;
					delete pLeft;

					int _sizeof = pExpr->right->m_pType->m_pPointerTo->get_sizeof();

					//ea _src(6/*extended*/,--areg);

					if (_sizeof == 4)
					{
						((CCodeGen68*)this)->move(SIZE_L, 6,--areg, pDestEA->m_mode,pDestEA->m_reg);
					}
					else
					{
						ASSERT(0);
					}

					BYTE disp = 0;
					int ext_reg = --dreg;
					int factor;

					if (_sizeof == 1)
						factor = 0;
					else if (_sizeof == 2)
						factor = 1;
					else if (_sizeof == 4)
						factor = 2;
					else if (_sizeof == 8)
						factor = 3;
					else
					{
						ASSERT(0);
					}

					int isize = 2;	// LONG

					//type:1, reg:3, isize:1, factor:2, pad:1, disp:8
					WORD ext = 0;
					ext |= disp;
					ext |= factor<<9;
					ext |= isize<<11;
					ext |= ext_reg<<12;
					fput16(fileout, ext);

					if (pDestEA->m_mode == 5)
					{
						fput16(fileout, (short)pDestEA->m_value);
					}
				}
				else
				{
	#if 0
				// Dereference with offset
				//	pExpr->left[pExpr->right];
				
				if (emit_expr(pFunc, pExpr->right) != 1)
					printf("Error in expression\n");
				BYTE indexRegister = reg-1;
				
				if (emit_expr(pFunc, pExpr->left) != 1)
					printf("Error in expression\n");
				BYTE baseRegister = reg-1;
				
				BYTE DestReg = 0;	// EAX
				BYTE Mod = 0;	// no displacement
				BYTE RM = 4;	// use SIB
				BYTE scale = 2;	// *4
				
				BYTE ModRM = RM | (DestReg<<3) | (Mod<<6);
				BYTE SIB = baseRegister | (indexRegister<<3) | (scale<<6);
				
				putc(0x8B, fileout);	// mov
				putc(ModRM, fileout);
				putc(SIB, fileout);
	#endif
				}
#endif
			}
			break;
			
		case '|':
			{
			}
			break;
			
		case '=':
			{
				ASSERT(pExpr->left);
				ASSERT(pExpr->right);
				
				if (TRUE)	// 68000
				{
					//if (pExpr->left->m_pDeclarator == NULL)
					if (pExpr->left->tok.type != CToken::tok_ident)
					{
						// evaluate right side
						ea src;//(0,4);	// d4
						if (emit_expr2(pFunc, pExpr->right, &src) != 1)
						{
							printf("Error in expression\n");
						}
						else
						{
							//ea _ea(5,5);	// n(a5)
							ea dest;
							if (emit_expr2(pFunc, pExpr->left, &dest) != 1)
								printf("Error in expression\n");

							unsigned int _sizeof = pExpr->m_pType->get_sizeof();

							if (_sizeof == 1)
							{
								((CCodeGen68*)this)->move(SIZE_B, src.m_mode,src.m_reg, dest.m_mode,dest.m_reg);
							}
							else if (_sizeof == 2)
							{
								((CCodeGen68*)this)->move(SIZE_W, src.m_mode,src.m_reg, dest.m_mode,dest.m_reg);
							}
							else if (_sizeof == 4)
							{
								if (dest.m_mode == 1)
								{
									((CCodeGen68*)this)->move(SIZE_L, src.m_mode,src.m_reg, 2,dest.m_reg);
								}
								else
								{
									((CCodeGen68*)this)->move(SIZE_L, src.m_mode,src.m_reg, dest.m_mode,dest.m_reg);
								}

								if (src.m_mode == 7 && src.m_reg == 4)
								{
									fput32(fileout, src.m_value);
								}
							}
							else
								ASSERT(0);
						}
					}
					else
					{
						if (pExpr->left->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex == 0)	// local variable
						{
							cpp::CDeclarator* pLeftDeclarator = pExpr->left->m_pDeclaratorRef->m_pDeclarator;
							long offset = -pLeftDeclarator->m_pType->get_sizeof() - (pLeftDeclarator->m_spOffset + pFunc->m_spOffset);
							//offset += pLeftDeclarator->m_pType->get_sizeof() - pExpr->right->m_pType->

							ea _ea(5,5);	// n(a5)
							_ea.m_value = offset;
							if (emit_expr(pFunc, pExpr->right, &_ea) != 1)
								printf("Error in expression\n");
						}
						else	// global variable
						{
							ea ea(7,1);
							if (emit_expr(pFunc, pExpr->right, &ea) != 1)
								printf("Error in expression\n");

							FRelocation* ImageReloc = new FRelocation;//&ofile->ImageRelocation[ofile->numberOfRelocations];
							ImageReloc->VirtualAddress = ftell(fileout);	// Address into the .text section
							ImageReloc->SymbolTableIndex = pExpr->left->m_pDeclaratorRef->m_pDeclarator->m_symbolIndex;//TODO symbolIndex;//pExpr->m_pDeclarator->m_symbolIndex-1;	// reference to name of function being called
							//	ImageReloc->Type = IMAGE_REL_I386_REL32;//IMAGE_REL_I386_ABSOLUTE;
							ImageReloc->Type = IMAGE_REL_I386_DIR32;//IMAGE_REL_I386_ABSOLUTE;
							
							fput32(fileout, pExpr->left->m_pDeclaratorRef->m_pDeclarator->m_spOffset);
							//	fput32(fileout, 0);
							
							pFunc->AddRelocation(ImageReloc);
						}
					}
				}
				else
				{
					reg--;
					
					fputc(0x89, fileout);	// /r MOV r/m32,r32 Move r32 to r/m32.
					amode(reg, 5/*EBP*/, pExpr->left->m_pDeclaratorRef->m_pDeclarator->m_spOffset);
				}
	#if 0
				if (emit_expr(pFunc, pExpr->left) != 1)
					printf("Error in expression\n");
	#endif
				
				//	putc(0x89, fileout);
				/*
				BYTE local_variable_index = 0;
				
				  // push value2
				  if (emit_expr(pExpr->right) != 1)
				  jfatalerror("Error in expression\n");
				  
					 // left must be lvalue
					 emit_op(JOP_istore);
					 fput8(fileout, local_variable_index);
				*/
				
				return 0;
			}
			break;
			
		case '==':
		case '!=':
		case '<':
		case '>':
		case '<=':
		case '>=':
			{
				int dreg0 = AllocDataRegister();
				if (emit_expr(pFunc, pExpr->left, &ea(0, dreg0)) != 1)
					printf("Expected value\n");
				
				int dreg1 = AllocDataRegister();
				if (emit_expr(pFunc, pExpr->right, &ea(0, dreg1)) != 1)
					printf("Expected value\n");
				
				if ((pExpr->left->m_pType->get_sizeof() == 2) ||
					(pExpr->right->m_pType->get_sizeof() == 2))
				{
					((CCodeGen68*)this)->cmp(dreg0, CMPOP_DN_WORD, 0,dreg1);
				}
				else
				{
					((CCodeGen68*)this)->cmp(dreg0, CMPOP_DN_LONG, 0,dreg1);
				}

				//dreg -= 2;
				FreeRegister(dreg0);
				FreeRegister(dreg1);

				// Note, we emit the opposite op codes
				switch (pExpr->tok.symbol)
				{
				case '==':
					((CCodeGen68*)this)->bcc(COND_NE);//JOP_if_icmpne);
					break;
					
				case '!=':
					((CCodeGen68*)this)->bcc(COND_EQ);//emit_op(JOP_if_icmpeq);
					break;
					
				case '<':
					((CCodeGen68*)this)->bcc(COND_GE);
				//	emit_op(JOP_if_icmpgt);
					break;
					
				case '>':
					((CCodeGen68*)this)->bcc(COND_LE);
				//	emit_op(JOP_if_icmplt);
					break;
					
				case '<=':
					((CCodeGen68*)this)->bcc(COND_GT);	//emit_op(JOP_if_icmpge);
					break;
					
				case '>=':
					((CCodeGen68*)this)->bcc(COND_LT);	//emit_op(JOP_if_icmple);
					break;

				default:
					ASSERT(0);
				}

				branch();
				short offset = 0;
				fput16(fileout, offset);

				return 2;
			}
			break;

			case '&&':
				{
					// In the short-circuit approach the operators AND and OR are defined to have
					// semantic meanings such that:

					// A AND B       means      IF A THEN B ELSE FALSE END
					// A OR  B       means      IF A THEN TRUE ELSE B END

					CLabel* else_label = new CLabel;
					m_labelStack.push(else_label);

					int dreg = 0;	// TODO
					if (emit_expr(pFunc, pExpr->left, &ea(0,dreg++)) != 2)
					{
						printf("Expected boolean expression\n");
					}
					m_labelStack.pop();

					//	emit_op(JOP_if_icmpne);	// if left expr evaluates to false, skip right expression
					//	branch();
					CLabel* end_label = new CLabel;
					((CCodeGen68*)this)->bcc(0);	// unconditional branch
					end_label->m_branches.push_back(ftell(fileout));
					fput16(fileout, 0);

					else_label->m_pos = GetCounter();
					FlushLabel(else_label);

				//	branch_to();
					if (emit_expr(pFunc, pExpr->right, &ea(0,dreg++)) != 2)
					{
						printf("Expected boolean expression\n");
					}
					end_label->m_pos = GetCounter();
					FlushLabel(end_label);

					return 2;
				}
				break;
					
		case '||':
			{
				ASSERT(0);
	#if 0
						emit_expr(pExpr->left);
						//	emit_op(JOP_if_icmpne);	// if left expr evaluates to true, skip right expression
						//	printf("\n");
						
						emit_expr(pExpr->right);
						//	emit_op(JOP_if_icmpne);
						//	printf("\n");
	#endif
			}
			break;

		case '?':
			{
				// TODO
				printf("codegen: TODO ? : ");
			}
			break;
					
		default:
			if (pExpr->tok.symbol == '+' ||
				pExpr->tok.symbol == '-' ||
				pExpr->tok.symbol == '*' ||
				pExpr->tok.symbol == '/' ||
				pExpr->tok.symbol == '%' ||
						
				pExpr->tok.symbol == '|' ||
				pExpr->tok.symbol == '&' ||
				pExpr->tok.symbol == '^' ||
						
				pExpr->tok.symbol == '<<' ||
				pExpr->tok.symbol == '>>' ||

				pExpr->tok.symbol == ((DWORD)'U'<<8|'!')
				)
			{
				switch (pExpr->tok.symbol)
				{
				case '+':
					{
						ASSERT(pDestEA);

						// If the destination is a data register, then
						// it cannot be specified by using the destination <ea> mode
						if (pDestEA->m_mode == 0)
						{
							if (emit_expr(pFunc, pExpr->left, pDestEA) != 1)
								printf("Error in expression\n");

							int dreg = AllocDataRegister();
							if (emit_expr(pFunc, pExpr->right, &ea(0, dreg)) != 1)
								printf("Error in expression\n");

							// add <ea> + <dn> -> <dn>
							if (pExpr->m_pType->GetType()->get_sizeof() == 1)
							{
								((CCodeGen68*)this)->add(0/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 2)
							{
								((CCodeGen68*)this)->add(1/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 4)
							{
								((CCodeGen68*)this)->add(2/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else
								ASSERT(0);

							FreeRegister(dreg);
						}
						else if (pDestEA->m_mode == 1)
						{
							if (emit_expr(pFunc, pExpr->left, pDestEA) != 1)
								printf("Error in expression\n");

							int dreg = AllocDataRegister();
							if (emit_expr(pFunc, pExpr->right, &ea(0, dreg)) != 1)
								printf("Error in expression\n");

#if 0
							// add <ea> + <dn> -> <dn>
							if (pExpr->m_pType->GetType()->get_sizeof() == 1)
							{
								((CCodeGen68*)this)->add(0/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 2)
							{
								((CCodeGen68*)this)->add(1/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 4)
							{
								((CCodeGen68*)this)->add(2/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else
								ASSERT(0);
#endif

							((CCodeGen68*)this)->add(7/*opmode*/, pDestEA->m_reg, 0, dreg);

							FreeRegister(dreg);
						}
						else
						{
							if (emit_expr(pFunc, pExpr->left, pDestEA) != 1)
								printf("Error in expression\n");

							int dreg = AllocDataRegister();
							if (emit_expr(pFunc, pExpr->right, &ea(0, dreg)) != 1)
								printf("Error in expression\n");

							// add <Dn> + <ea> -> <ea>
							unsigned int _sizeof = pExpr->m_pType->GetType()->get_sizeof();
							if (_sizeof == 1)
							{
								((CCodeGen68*)this)->add(4/*opmode*/, dreg, pDestEA->m_mode, pDestEA->m_reg);
							}
							else if (_sizeof == 2)
							{
								((CCodeGen68*)this)->add(5/*opmode*/, dreg, pDestEA->m_mode, pDestEA->m_reg);
							}
							else if (_sizeof == 4)
							{
								((CCodeGen68*)this)->add(6/*opmode*/, dreg, pDestEA->m_mode, pDestEA->m_reg);
							}
							else
								ASSERT(0);
//							//if (pDestEA->m_mode == 
//							((CCodeGen68*)this)->add(6/*opmode*/, dreg, pDestEA->m_mode, pDestEA->m_reg);

							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, pDestEA->m_value);
							}
							FreeRegister(dreg);
						}

						//add(pDestEA
#if 0
						putc(0x03, fileout);	// ADD
						amode(reg-2, reg-1);
						/*
						BYTE Reg = reg-2;
						BYTE Mod = 3;	// r32,r/m32
						BYTE RM = reg-1;
						BYTE ModRM = RM | (Reg<<3) | (Mod<<6);
						putc(ModRM, fileout);
						*/
						
						//add_r32_rm32_disp(0/*EAX*/, 5/*EBP*/, 8);
						
						//emit_op(JOP_iadd);
#endif
					}
					break;

				case '-':
					{
						ASSERT(pDestEA);

						// If the destination is a data register, then
						// it cannot be specified by using the destination <ea> mode
						if (pDestEA->m_mode == 0)
						{
							if (emit_expr(pFunc, pExpr->left, pDestEA) != 1)
								printf("Error in expression\n");

							int dreg = AllocDataRegister();
							if (emit_expr(pFunc, pExpr->right, &ea(0, dreg)) != 1)
								printf("Error in expression\n");

							// sub <dn> - <ea> -> <dn>
							if (pExpr->m_pType->GetType()->get_sizeof() == 1)
							{
								((CCodeGen68*)this)->sub(0/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 2)
							{
								((CCodeGen68*)this)->sub(1/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 4)
							{
								((CCodeGen68*)this)->sub(2/*opmode*/, pDestEA->m_reg, 0, dreg);
							}
							else
								ASSERT(0);

							FreeRegister(dreg);
						}
						else if (pDestEA->m_mode == 1)	// destination is address register
						{
							printf("INTERNAL ERROR\n");
							ASSERT(0);
						}
						else
						{
							if (emit_expr(pFunc, pExpr->left, pDestEA) != 1)
								printf("Error in expression\n");

							int dreg = AllocDataRegister();
							if (emit_expr(pFunc, pExpr->right, &ea(0, dreg)) != 1)
								printf("Error in expression\n");

							ea _ea(pDestEA->m_mode, pDestEA->m_reg);
							// This is to ensure that we don't predecrement twice
							if (pDestEA->m_mode == 4)	// -(an)
							{
								_ea.m_mode = 2;	// (an)
								_ea.m_reg = pDestEA->m_reg;
								_ea.m_lea = pDestEA->m_lea;
								_ea.m_value = pDestEA->m_value;
							}
							else
							{
								_ea = *pDestEA;
							}

							// sub <ea> - <Dn> -> <ea>
							if (pExpr->m_pType->GetType()->get_sizeof() == 1)
							{
								((CCodeGen68*)this)->sub(4/*opmode*/, dreg, _ea.m_mode, _ea.m_reg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 2)
							{
								((CCodeGen68*)this)->sub(5/*opmode*/, dreg, _ea.m_mode, _ea.m_reg);
							}
							else if (pExpr->m_pType->GetType()->get_sizeof() == 4)
							{
								((CCodeGen68*)this)->sub(6/*opmode*/, dreg, _ea.m_mode, _ea.m_reg);
							}
							else
								ASSERT(0);

							if (_ea.m_mode == 5)
							{
								fput16(fileout, _ea.m_value);
							}
							FreeRegister(dreg);
						}
					}
					break;
#if 0
					
				case '*':
					{
						//emit_op(JOP_imul);
					}
					break;
#endif
				case '/':
					{
						ASSERT(pDestEA);

						int dreg0 = AllocDataRegister();
						if (emit_expr(pFunc, pExpr->left, &ea(0, dreg0)) != 1)
							printf("Error in expression\n");

						int dreg1 = AllocDataRegister();
						if (emit_expr(pFunc, pExpr->right, &ea(0, dreg1)) != 1)
							printf("Error in expression\n");

						((CCodeGen68*)this)->divu(dreg0, 0,dreg1);

						if (pDestEA->m_mode != 0 || pDestEA->m_reg != dreg0)
						{
							ULONG size = pExpr->m_pType->get_sizeof();
							if (size == 1)
								((CCodeGen68*)this)->move(SIZE_B, 0,dreg0, pDestEA->m_mode,pDestEA->m_reg);
							else if (size == 2)
								((CCodeGen68*)this)->move(SIZE_W, 0,dreg0, pDestEA->m_mode,pDestEA->m_reg);
							else if (size == 4)
							{
								((CCodeGen68*)this)->ext(dreg0, 3/*word -> long*/);
								((CCodeGen68*)this)->move(SIZE_L, 0,dreg0, pDestEA->m_mode,pDestEA->m_reg);
							}
							else
							{
								printf("unsupported sizeof");
								ASSERT(0);
							}

							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, (short)pDestEA->m_value);
							}
						}
#if 0	// huh??
						else
						{
							((CCodeGen68*)this)->ext(dreg0, 3/*word -> long*/);
						}
#endif
						FreeRegister(dreg0);
						FreeRegister(dreg1);
					}
					break;

				case '%':
					{
						ASSERT(pDestEA);

						int dreg0 = AllocDataRegister();
						if (emit_expr(pFunc, pExpr->left, &ea(0, dreg0)) != 1)
							printf("Error in expression\n");

						int dreg1 = AllocDataRegister();
						if (emit_expr(pFunc, pExpr->right, &ea(0, dreg1)) != 1)
							printf("Error in expression\n");

						((CCodeGen68*)this)->divu(dreg0, 0,dreg1);

						{
							WORD word = 0xE008;

							int ir = 0;
							int size = 2;	// long
							int dr = 0;	// right
							word |= dreg0;
							word |= ir<<5;
							word |= size<<6;
							word |= dr<<8;
							word |= 0<<9;	// 8
							fput16(fileout, word);

							fput16(fileout, word);	// Do it twice
						}

						if (pDestEA->m_mode != 0 || pDestEA->m_reg != dreg0)
						{
							ULONG size = pExpr->m_pType->get_sizeof();
							if (size == 1)
								((CCodeGen68*)this)->move(SIZE_B, 0,dreg0, pDestEA->m_mode,pDestEA->m_reg);
							else if (size == 2)
								((CCodeGen68*)this)->move(SIZE_W, 0,dreg0, pDestEA->m_mode,pDestEA->m_reg);
							else if (size == 4)
								((CCodeGen68*)this)->move(SIZE_L, 0,dreg0, pDestEA->m_mode,pDestEA->m_reg);
							else
							{
								printf("unsupported sizeof");
								ASSERT(0);
							}

							if (pDestEA->m_mode == 5)
							{
								fput16(fileout, (short)pDestEA->m_value);
							}
						}
#if 0	// huh??
						else
						{
							((CCodeGen68*)this)->ext(dreg0, 3/*word -> long*/);
						}
#endif
						FreeRegister(dreg0);
						FreeRegister(dreg1);
					}
					break;

#if 0			
				case '|':
					{
						if (emit_expr(pFunc, pExpr->left) != 1)
							printf("Error in expression\n");
						
						if (pExpr->right->tok.type == CToken::tok_integer)
						{
							or_imm(reg, pExpr->right->tok.int32);
							
							return 1;
						}
						else
						{
							ASSERT(0);
						}
					}
					break;
#endif
	
				case ((DWORD)'U'<<8|'!'):
					{
						printf("");
					}
					break;

				default:
					ASSERT(0);
				}
				return 1;
			}
			else
			{
				ASSERT(0);
			}
		}
	}
	else
	{
		ASSERT(0);
	}
#endif	
	return 0;
}

#if 0
void CCodeGenerator::WriteStatement(CFunctionCode* pFunc, cpp::CTStatementn* pstmt)
{
	ASSERT(0);
#if 0
	if (pstmt->m_type == cpp::STMT_RETURN)
	{
		cpp::CReturnStatement* preturnstmt = (cpp::CReturnStatement*)pstmt;

		if (preturnstmt->m_expr)
		{
			// huh ???
			CLabel* else_label = new CLabel;
			m_labelStack.push(else_label);

			if (emit_expr(pFunc, preturnstmt->m_expr, &ea(0,0)/*d0*/) == 2)
			{
			//	emit_op(JOP_iconst_1);
			//	emit_op(JOP_goto);
			//	fput16(fileout, 0);

			//	branch_to();
			//	emit_op(JOP_iconst_0);
			}

			//putc(0xC3, fileout);	// RET (near return)

		// Jump to epilogue
			if (m_processor_id == 1)
			{
			}
			else	// x86
			{
				putc(0xEB, fileout);	// jmp short
				putc(0, fileout);	// 8-bit offset
			}
		}
		else
		{
			if (m_processor_id == 1)
			{
			}
			else	// x86
			{
				putc(0xC3, fileout);	// RET (near return)
			}
		}
	}
	else if (pstmt->m_type == cpp::STMT_IF)
	{
		cpp::CIfStatement* pIfStmt = (cpp::CIfStatement*)pstmt;

		CLabel* else_label = new CLabel;
		m_labelStack.push(else_label);
		if (emit_expr(pFunc, pIfStmt->m_testexpr, NULL) != 2)
		{
			printf("Expected boolean expression\n");
		}
		m_labelStack.pop();
		WriteStatement(pFunc, pIfStmt->m_substmt);

		CLabel* end_label = new CLabel;
		((CCodeGen68*)this)->bcc(0);	// unconditional branch
		end_label->m_branches.push_back(ftell(fileout));
		fput16(fileout, 0);
		
		else_label->m_pos = GetCounter();
		FlushLabel(else_label);

		if (pIfStmt->m_elsestmt)
		{
			WriteStatement(pFunc, pIfStmt->m_elsestmt);
		}
		end_label->m_pos = GetCounter();
		FlushLabel(end_label);
	}
	else if (pstmt->m_type == cpp::STMT_WHILE)
	{
		cpp::CWhileStatement* pWhileStmt = (cpp::CWhileStatement*)pstmt;

		CLabel* pWhileLabel = new CLabel;
		pWhileLabel->m_pos = GetCounter();

		CLabel* pEndLabel = new CLabel;
		m_labelStack.push(pEndLabel);
		if (emit_expr(pFunc, pWhileStmt->m_testexpr, NULL) != 2)
		{
			printf("Expected boolean expression\n");
		}
		WriteStatement(pFunc, pWhileStmt->m_substmt);

		((CCodeGen68*)this)->bcc(0);	// unconditional branch
		fput16(fileout, (int)pWhileLabel->m_pos - (int)GetCounter());

		pEndLabel->m_pos = GetCounter();
		FlushLabel(pEndLabel);
		m_labelStack.pop();
		delete pEndLabel;

#if 0
		((CCodeGen68*)this)->bcc(0);	// unconditional branch
		end_label->m_branches.push_back(ftell(fileout));
		fput16(fileout, 0);
		
		set_label(else_label);

		if (pIfStmt->m_elsestmt)
		{
		//	branch();
			WriteStatement(pFunc, pIfStmt->m_elsestmt);
		//	branch_to();
		}
		set_label(end_label);
#endif
	}
	/*
	else if (pstmt->m_type == cpp::STMT_FOR)
	{
		printf("");
	}
	*/
	else if (pstmt->m_type == cpp::STMT_EXPRESSION)
	{
		cpp::CExpressionStatement* pExprStmt = (cpp::CExpressionStatement*)pstmt;

		if (pExprStmt->m_pExpr)
		{
			emit_expr(pFunc, pExprStmt->m_pExpr, NULL);
		}
	}
	else if (pstmt->m_type == cpp::STMT_COMPOUND)
	{
		cpp::CCompoundStatement* pCompoundStmt = (cpp::CCompoundStatement*)pstmt;

	//	pFunc->m_spOffset = pCompoundStmt->m_pBlock->m_pScope->m_spOffset;

		for (int i = 0; i < pCompoundStmt->m_pBlock->m_statements.size(); i++)
		{
			WriteStatement(pFunc, pCompoundStmt->m_pBlock->m_statements[i]);
		}

		//pFunc->m_spOffset += 
	}
	else if (pstmt->m_type == cpp::STMT_ZERO)
	{
		cpp::CZeroStatement* pZeroStmt = (cpp::CZeroStatement*)pstmt;

		int dreg = AllocDataRegister();
		int areg = AllocAddrRegister()-8;
		((CCodeGen68*)this)->moveq(pZeroStmt->m_spOffset, dreg);
		((CCodeGen68*)this)->add(2/*L ea+dn -> dn*/, dreg, 1,5);	// a5,dn
		((CCodeGen68*)this)->move(SIZE_L, 0,dreg, 1,areg);
		FreeRegister(dreg);

		int offset = pZeroStmt->m_spOffset;
		int to = pZeroStmt->m_spOffset + pZeroStmt->m_length;

		if (offset & 1)
		{
			((CCodeGen68*)this)->clr(0, 3, areg);
			offset += 1;
		}

		if (offset < to)
		{
			if (offset & 2)
			{
				((CCodeGen68*)this)->clr(1, 3, areg);
				offset += 2;
			}

			while (offset < to)
			{
				if (to - offset == 1)
				{
					((CCodeGen68*)this)->clr(0, 3, areg);
					offset += 1;
				}
				else if (to - offset < 4)
				{
					((CCodeGen68*)this)->clr(1, 3, areg);
					offset += 2;
				}
				else
				{
					((CCodeGen68*)this)->clr(2, 3, areg);
					offset += 4;
				}
			}
		}
		FreeRegister(areg+8);
	}
	else
	{
		ASSERT(0);
	}
#endif
}
#endif
