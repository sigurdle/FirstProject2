#include "stdafx.h"
#include "LFC.h"
#include "CodeViewDebugInfo.h"

namespace System
{

using namespace std;
using namespace CodeView;

class LFCEXT BitfieldType : public Type
{
public:
	CTOR BitfieldType(Type* pType, uint8 position, uint8 length)
	{
		m_pType = pType;
		m_position = position;
		m_length = length;
	}

	virtual Type_type get_Kind() const
	{
		return type_bitfield;
	}

	virtual bool IsConst() const
	{
		return m_pType->IsConst();
	}
	virtual bool IsVolatile() const
	{
		return m_pType->IsVolatile();
	}

	virtual Type* Clone() const
	{
		ASSERT(0);
		return nullptr;
	}

	virtual String ToString() const
	{
		ASSERT(0);
		return nullptr;
	}

	virtual IO::TextWriter& Write(IO::TextWriter& stream) const
	{
		ASSERT(0);
		return stream;
	}

	virtual uint get_sizeof(uint sizeofptr = 0) const
	{
		ASSERT(0);
		return ~0;
	}

	virtual Class_Type GetSerializableType() const
	{
		ASSERT(0);
		THROW(-1);
	//	return 0;
	}

	virtual void Load(TypeArchive& ar)
	{
		ASSERT(0);
		THROW(-1);
	}

	virtual void Store(TypeArchive& ar) const
	{
		ASSERT(0);
		THROW(-1);
	}

	Type* m_pType;
	uint8 m_position;
	uint8 m_length;
};

//#define MyTrace	printf
#define MyTrace

/*
								case sstGlobalTypes:
									{
										printf("SubSection: %s(%x)\n", str, direntry->SubSection);

										OMFGlobalTypes* pGlobalTypes = (OMFGlobalTypes*)(p+direntry->lfo);

										char* p = ((char*)pGlobalTypes) + 8 + pGlobalTypes->cTypes*4;
										for (int i = 0; i < pGlobalTypes->cTypes; i++)
										{
											TYPTYPE* typ = (TYPTYPE*)(p + pGlobalTypes->typeOffset[i]);
											*/
/*
Type* CodeViewDebugInfo::LookupNamedType(StringA name)
{
	return m_namedTypes[name];
}

Scope* CodeViewDebugInfo::LookupProc(StringA name)
{
	return m_procs[name];
}
*/

int GetNumeric(const uint8** pp)
{
	const uint8* p = *pp;

	int num = *(uint16*)p;
	p += 2;
	if (num >= LF_NUMERIC)
	{
		switch (num)
		{
		case LF_CHAR:
			num = *(char*)p;
			p++;
			break;

		case LF_SHORT:
			num = *(short*)p;
			p += 2;
			break;

		case LF_USHORT:
			num = *(unsigned short*)p;
			p += 2;
			break;

		case LF_LONG:
			num = *(long*)p;
			p += 4;
			break;

		case LF_ULONG:
			num = *(unsigned long*)p;
			p += 4;
			break;

		default:
			ASSERT(0);
		}
	}

	*pp = p;

	return num;
}

CodeViewDebugInfo::CodeViewDebugInfo(uint8* data, System::Scope* _pGlobalScope) :
	m_data(data),
	m_pGlobalScope(_pGlobalScope),
	m_pOMFGlobalTypes(NULL)
{
}

void CodeViewDebugInfo::FieldList(TYPTYPE* typ, ClassType* pClass, ULONG_PTR dwData)
{
	const char* p = ((const char*)m_pOMFGlobalTypes) + 8 + m_pOMFGlobalTypes->cTypes*4;

	const uint8* p1 = ((const uint8*)typ)+2;
	const uint8* p2 = p1;

	MyTrace("LF_FIELDLIST_32\n");
//	lfList* lf = (lfList*)p2;
//	int n = ((int*)p2)[0];
	//int n = ((int*)lf->data)[0];

	p2 += 2;

	while (p2 < p1 + typ->len)
	{
		uint16  leaf = *(uint16*)p2;

		const uint8* _p2 = p2;

		switch (leaf)
		{
		case LF_BCLASS_32:
			{
				lfBClass_32* lf = (lfBClass_32*)p2;

				System::Type* pBaseClassType = GetType(lf->index, dwData);

				BaseClass* baseclass = new BaseClass;
				baseclass->m_pClass = pBaseClassType->AsClass();
				p2 += sizeof(lfBClass_32);

				baseclass->m_offset = GetNumeric(&p2);

				pClass->m_bases.push_back(baseclass);
			}
			break;

			/*
		case LF_BCLASS_32:
			{
				lfBClass_32* lf = (lfBClass_32*)p2;
				
				p2 += sizeof(lfBClass_32);
				p2 += 2;	// ??
				
			}
			break;
			*/
			
		case LF_VBCLASS_32:
		case LF_IVBCLASS_32:
			{
				lfVBClass_32* lf = (lfVBClass_32*)p2;

				GetType(lf->index, dwData);
				GetType(lf->vbptr, dwData);
				p2 += sizeof(lfVBClass_32);
				p2 += 2;// virtual base pointer offset from address point
				p2 += 2;// followed by virtual base offset from vbtable
			}
			break;

		case LF_NESTTYPE_32:
			{
				lfNestType_32* lf = (lfNestType_32*)p2;
				
				p2 += sizeof(lfNestType_32)-1;
				uint8 namelen = *p2++;
				
				char Name[256];
				memcpy(Name, p2, namelen);
				Name[namelen] = 0;
				MyTrace("%s\n", Name);
				
				p2 += namelen;

				Type* pType = GetType(lf->index, dwData);
			}
			break;

		case LF_METHOD_32:
			{
				lfMethod* lf = (lfMethod*)p2;
				
				char name[256];
				uint8 namelen = lf->Name[0];
				memcpy(name, &lf->Name[1], namelen);
				name[namelen] = 0;
				String namestring = m_pReceiver->CreateString(name);
			
				TYPTYPE* typ2 = (TYPTYPE*)(p + m_pOMFGlobalTypes->typeOffset[lf->mList - 0x1000]);
				if (typ2->leaf == LF_METHODLIST_32)
				{
					const uint8* p2 = (const uint8*)((lfMethodList*)&typ2->leaf)->mList;
					for (int i = 0; i < lf->count; i++)
					{
						mlMethod_32* lf = (mlMethod_32*)p2;

						Declarator* pdecl = new Declarator;

						pdecl->m_pOwnerScope = pClass->m_pScope;

						p2 += sizeof(mlMethod_32);

						if (lf->attr.mprop == CV_MTintro ||
							lf->attr.mprop == CV_MTpureintro)
						{
							pdecl->m_virtual = true;
							pdecl->m_offset = *(ULONG*)p2;
							p2 += 4;
						}
						else if (lf->attr.mprop == CV_MTvirtual)
						{
							pdecl->m_virtual = true;
						}
						else if (lf->attr.mprop == CV_MTstatic)
						{
							pdecl->m_static = true;
						}
						/*
						else if (lf->attr.mprop == CV_MTfriend)
						{
						}
						*/

						pdecl->m_pType = GetType(lf->index, dwData);
						ASSERT(pdecl->m_pType != NULL);
						pdecl->m_name = namestring;
						pClass->m_pScope->AddDeclarator(pdecl);
					}
				}

				p2 += sizeof(lfMethod) + namelen;
			}
			break;
			
		case LF_ONEMETHOD_32:
			{
				lfOneMethod* lf = (lfOneMethod*)p2;

				p2 += sizeof(lfOneMethod);

				Declarator* pdecl = new Declarator;

				pdecl->m_pOwnerScope = pClass->m_pScope;

				if (lf->attr.mprop == CV_MTintro ||
					lf->attr.mprop == CV_MTpureintro)
				{
					pdecl->m_virtual = true;
					pdecl->m_offset = *(ULONG*)p2;
					p2 += 4;
				}
				else if (lf->attr.mprop == CV_MTvirtual)
				{
					pdecl->m_virtual = true;
				}
				else if (lf->attr.mprop == CV_MTstatic)
				{
					pdecl->m_static = true;
				}
				/*
				else if (lf->attr.mprop == CV_MTfriend)
				{
				}
				*/
				
				uint8 namelen = *p2++;
				
				char name[256];
				memcpy(name, p2, namelen);
				name[namelen] = 0;
				MyTrace("%s\n", name);

				/*
				if (!strcmp(name, "~CHTMFlowContext"))
				{
					MessageBeep(-1);
				}
				*/
				
				p2 += namelen;

				pdecl->m_pType = GetType(lf->index, dwData);
				ASSERT(pdecl->m_pType != NULL);
				ASSERT(pdecl->m_pType->get_Kind() != type_bitfield);
				/*
				if (pdecl->m_pType->get_Kind() != type_bitfield)
				{
					BitfieldType* p = (BitfieldType*)pdecl->m_pType;
					//pdecl->
					// TODO
					pdecl->m_pType = p->m_pType;
					ASSERT(pdecl->m_pType != NULL);
				}
				*/

				pdecl->m_name = m_pReceiver->CreateString(name);
				pClass->m_pScope->AddDeclarator(pdecl);

				/*
				for (int i = 0; i < pdecl->m_pType->m_pFunction->m_parameters.size(); i++)
				{
					pdecl->m_pType->m_pFunction->m_parameters[i].m_pTypepDecl->m_pType->m_typerefs.Add(pType);
				}
				*/
			}
			break;
			
		case LF_MEMBER_32:
			{
				lfMember_32* lf = (lfMember_32*)p2;
				
				p2 += sizeof(lfMember_32);
				
				// TODO, variable length ??
			//	uint16 offset = *(uint16*)p2;

				int offset = GetNumeric(&p2);
			//	p2 += 2;
				
				uint8 namelen = *p2++;
				
				char name[256];
				memcpy(name, p2, namelen);
				name[namelen] = 0;
				//MyTrace("%s\n", name);

				/*
				if (!strcmp(name, "m_orderedDecls"))
				{
					MessageBeep(-1);
				}
				*/
				
				p2 += namelen;

				Declarator* pdecl = new Declarator();
				pdecl->m_pOwnerScope = pClass->m_pScope;

				if (lf->index)
				{
					pdecl->m_pType = GetType(lf->index, dwData);
					ASSERT(pdecl->m_pType != NULL);
					if (pdecl->m_pType->get_Kind() == type_bitfield)
					{
						BitfieldType* p = (BitfieldType*)pdecl->m_pType;
						//pdecl->
						// TODO
						pdecl->m_pType = p->m_pType;
						ASSERT(pdecl->m_pType != NULL);
					}
				}

				/*
				if (pdecl->m_pType == NULL)
				{
					pdecl->m_pType = GetType(lf->index, dwData);
				}
				*/
				pdecl->m_name = m_pReceiver->CreateString(name);
				pdecl->m_offset = offset;
				pClass->m_pScope->AddDeclarator(pdecl);
			}
			break;
			
		case LF_STMEMBER_32:
			{
				lfSTMember_32* lf = (lfSTMember_32*)p2;
				
				p2 += sizeof(lfSTMember_32) -1;
				
				uint8 namelen = *p2++;
				
				char Name[256];
				memcpy(Name, p2, namelen);
				Name[namelen] = 0;
				MyTrace("%s\n", Name);
				
				p2 += namelen;
			}
			break;
			
		case LF_VFUNCTAB_32:
			{
				lfVFuncTab_32* lf = (lfVFuncTab_32*)p2;
				p2 += sizeof(lfVFuncTab_32);

				GetType(lf->type, dwData);
			}
			break;
			
		default:
			{
				ASSERT(0);
			}
		}

		// align on dword
		ptrdiff_t len = (p2 - _p2);
		p2 += ((len + 3) & ~3) - len;
	}
}

System::Type* CodeViewDebugInfo::GetType(int typind, ULONG_PTR dwData)
{
	if (typind == 0) return NULL;

	if (typind < 0x1000)
	{
		System::Type* pType = NULL;

		switch (typind & 0xFF)
		{
		case T_BOOL08:
			{
				pType = &System::Types::type_bool;
			}
			break;

		case T_VOID:
			{
				pType = System::Types::get_void();
			}
			break;

		case T_CHAR:
			{
				pType = &System::Types::type_signed_char;
			}
			break;

		case T_UCHAR:
			{
				pType = &System::Types::type_unsigned_char;
			}
			break;

		case T_RCHAR:
			{
				pType = &System::Types::type_char;
			}
			break;

		case T_INT4:
			{
				pType = &System::Types::type_int;
			}
			break;

		case T_UINT4:
			{
				pType = &System::Types::type_unsigned_int;
			}
			break;

		case T_SHORT:
			{
				pType = &System::Types::type_short;
			}
			break;

		case T_USHORT:
			{
				pType = &System::Types::type_unsigned_short;
			}
			break;

		case T_LONG:
			{
				pType = &System::Types::type_long;
			}
			break;

		case T_ULONG:
			{
				pType = &System::Types::type_unsigned_long;
			}
			break;

		case T_QUAD:
			{
				pType = &System::Types::type_long_long;
			}
			break;

		case T_UQUAD:
			{
				pType = &System::Types::type_unsigned_long_long;
			}
			break;

		case LF_ENUMERATE:
			{
				// ??
				pType = &System::Types::type_int;
			}
			break;

		case T_REAL32:
			{
				pType = &System::Types::type_float;
			}
			break;

		case T_REAL64:
			{
				pType = &System::Types::type_double;
			}
			break;

		case T_REAL80:
			{
				pType = &System::Types::type_long_double;
			}
			break;

		case T_REAL128:
			{
				pType = &System::Types::type_float128;
			}
			break;

		default:
			ASSERT(0);
		}

		if (CV_MODE(typind) != 0)	// Some kind of pointer
		{
		//	pType = new PointerType(type_pointer, pType);
			pType = m_pReceiver->CreatePointerType(type_pointer, pType);
		}

		return pType;
	}
	else if (typind >= 0x1000)
	{
		const char* p = ((const char*)m_pOMFGlobalTypes) + 8 + m_pOMFGlobalTypes->cTypes*4;

		int index;
		/*
		if (typind >= 0x8000)
		{
			index = typind - 0x8000;
		}
		else
		*/
		{
			index = typind - 0x1000;
			if (m_pTypes[index] != NULL)
				return m_pTypes[index];
		}

		System::Type* pType = NULL;

		TYPTYPE* typ = (TYPTYPE*)(p + m_pOMFGlobalTypes->typeOffset[index]);
		//int leaf = typ->leaf;
	
//		ASSERT(index < LF_NUMERIC);

		unsigned char* p1 = ((unsigned char*)typ)+2;
		const unsigned char* p2 = p1;

		/*
		if (leaf >= 0x8000)
		{
			leaf -= 0x8000;
		}
		else
		{
			// ??
		//	leaf -= 0x1000;
		}
		*/

		switch (typ->leaf)
		{
			case LF_PROCEDURE_32:
			{
				lfProc* lf = (lfProc*)p2;
			//	printf("params: %d, arglist: %d", lf->parmcount, lf->arglist);

				pType = new FunctionType();
				pType->AsFunction()->m_pReturnType = GetType(lf->rvtype, dwData);

				if (lf->arglist >= 0x1000)
				{
					TYPTYPE* typ2 = (TYPTYPE*)(p + m_pOMFGlobalTypes->typeOffset[lf->arglist-0x1000]);
					if (typ2->leaf == LF_ARGLIST_32)
					{
						lfArgList_32* lf = (lfArgList_32*)&typ2->leaf;

						for (int i = 0; i < lf->count; i++)
						{
							Declarator* pDecl = new Declarator;
							if (lf->arg[i] == 0)
							{
								ASSERT(i == lf->count-1);
								pType->AsFunction()->m_parameters.m_bVarArg = true;
							}
							else
							{
							//	pDecl->m_pType = GetType(lf->arg[i], dwData);
							//	ASSERT(pDecl->m_pType != NULL);

								FunctionParameters::Param param;
								param.m_pType = GetType(lf->arg[i], dwData);
								ASSERT(param.m_pType != NULL);
								pType->AsFunction()->m_parameters.m_parameters.push_back(param);
							}
						}
					}
				}
			}
			break;

		case LF_MFUNCTION_32:
			{
				lfMFunc* lf = (lfMFunc*)p2;

				FunctionType* pFunction = new FunctionType;
				pType = pFunction;
				pFunction->m_pReturnType = GetType(lf->rvtype, dwData);

				Type* thistype = GetType(lf->thistype, dwData);
				if (thistype)
				{
					if (thistype->get_Kind() == type_cv)
					{
						ASSERT(thistype->GetPointerTo()->get_Kind() == type_pointer);

						pFunction->m_bConst = thistype->GetPointerTo()->GetPointerTo()->IsConst();
						pFunction->m_bVolatile = thistype->GetPointerTo()->GetPointerTo()->IsVolatile();
						/*
						if (pFunction->m_bConst)
						{
							MessageBeep(-1);
						}

						if (pFunction->m_bVolatile)
						{
							MessageBeep(-1);
						}
						*/
					}
					/*
					else if (thistype->get_Kind() == type_pointer)
					{
						pFunction->m_bConst = thistype->GetPointerTo()->IsConst();
						pFunction->m_bVolatile = thistype->GetPointerTo()->IsVolatile();
					}
					*/
					else
						ASSERT(0);
				}

				switch (lf->calltype)
				{
				case CV_CALL_NEAR_C:
					pFunction->m_funcspec = CallType_cdecl;
					break;

				case CV_CALL_NEAR_STD:
					pFunction->m_funcspec = CallType_stdcall;
					break;

				case CV_CALL_NEAR_FAST:
					pFunction->m_funcspec = CallType_fastcall;
					break;

				case CV_CALL_THISCALL:
					pFunction->m_funcspec = CallType_thiscall;
					break;

				default:
					ASSERT(0);
				}

				if (lf->arglist >= 0x1000)
				{
					TYPTYPE* typ2 = (TYPTYPE*)(p + m_pOMFGlobalTypes->typeOffset[lf->arglist-0x1000]);
					if (typ2->leaf == LF_ARGLIST_32)
					{
						lfArgList_32* lf = (lfArgList_32*)&typ2->leaf;

						if (lf->count > 0)
						{
							int count;
							if (lf->arg[lf->count-1] == 0)
							{
								pFunction->m_parameters.m_bVarArg = true;
								count = lf->count-1;
							}
							else
							{
								count = lf->count;
							}

							pFunction->m_parameters.m_parameters.reserve(count);

							for (int i = 0; i < count; i++)
							{
							//	CDeclarator* pDecl = new CDeclarator;
								if (lf->arg[i])	// hmm.. ??
								/*
								if ( == 0)
								{
									ASSERT(i == lf->count-1);
								}
								else
								*/
								{
									VERIFY(lf->arg[i]);

								//	pDecl->m_pType = GetType(lf->arg[i], dwData);
								//	VERIFY(pDecl->m_pType != NULL);
									FunctionParameters::Param param;
									param.m_pType = GetType(lf->arg[i], dwData);
									VERIFY(param.m_pType != NULL);

									pFunction->m_parameters.m_parameters.push_back(param);
								}
							}
						}
					}
				}
			}
			break;

		case LF_ENUM_32:
			{
				lfEnum_32* lf = (lfEnum_32*)p2;
				
				char name[256];
				strncpy_s(name, (char*)&lf->Name[1], lf->Name[0]);
				name[lf->Name[0]] = 0;
				
				EnumType* pEnum = new EnumType;
				pEnum->m_qname = string_copy(name);
				{
					const char* p = name;
					while (const char* p2 = strstr(p, "::"))
					{
						p = p2 + 2;
					}
					pEnum->m_name = m_pReceiver->CreateString(p);
				}

				TYPTYPE* typ2 = (TYPTYPE*)(p + m_pOMFGlobalTypes->typeOffset[lf->field-0x1000]);
				if (typ2->leaf == LF_FIELDLIST_32)
				{
					const uint8* p2 = (uint8*)typ2;
					p2 += 4;

					pEnum->m_deflist.reserve(lf->count);

				//	while (p2 < p1 + typ->len)
					for (int i = 0; i < lf->count; ++i)
					{
						const uint8* p1 = p2;
						uint16  leaf = *(uint16*)p2;

						if (leaf == LF_ENUMERATE)
						{
							lfEnumerate* lf = (lfEnumerate*)p2;
							p2 += sizeof(lfEnumerate);

							int value = GetNumeric(&p2);
							/*
							long value = *(uint16*)lf->value;
							p2 += 2;

							if (value >= LF_NUMERIC)
							{
								switch (value)
								{
								case LF_CHAR:
									value = *(char*)p2;
									p2++;
									break;

								case LF_SHORT:
									value = *(short*)p2;
									p2 += 2;
									break;

								case LF_USHORT:
									value = *(unsigned short*)p2;
									p2 += 2;
									break;

								case LF_LONG:
									value = (long)*p2;
									p2 += 4;
									break;

								case LF_ULONG:
									value = *(unsigned long*)p2;
									p2 += 4;
									break;

								default:
									ASSERT(0);
								}
							}
							*/

							uint8 namelen = *p2++;
							char name[256];
							memcpy(name, p2, namelen);
							name[namelen] = 0;
							p2 += namelen;

							//EnumDef def = ;
							pEnum->m_deflist.push_back(EnumDef(m_pReceiver->CreateString(name), value));

							ptrdiff_t len = p2 - p1;
							p2 = p1 + ((len+3) & ~3);
						}
					}
				}

				if (name[0])
				{
					NamedType* pType2 = m_pReceiver->LookupNamedType(pEnum->m_qname);
					if (pType2)
					{
						if (!pEnum->Type::Equals(*pType2))
						{
							MessageBoxA(NULL, "enum differed", "", MB_OK);
						}
					//	pEnum->Release();
						pType = pType2;
					}
					else
					{
						m_pReceiver->OnType(pEnum->m_qname, pEnum, dwData);
						pType = pEnum;
					}
				}
				else
					pType = pEnum;
			}
			break;

		case LF_DIMCONU:
			{
				lfDimCon* lf = (lfDimCon*)p2;

			//	std::printf("[%d]", lf->rank);
			}
			break;

		case LF_BITFIELD:
			{
				lfBitfield* lf = (lfBitfield*)p2;

			//	std::printf(": %d", lf->length);
			}
			break;

		case LF_MODIFIER_32:
			{
				lfModifier_32* lf = (lfModifier_32*)p2;

				pType = new ModifierType(GetType(lf->type, dwData), lf->attr.MOD_const, lf->attr.MOD_volatile);

				/*
				if (lf->attr.MOD_const)
					((CVType*)pType)->m_bConst = true;

				if (lf->attr.MOD_volatile)
					((CVType*)pType)->m_bVolatile = true;
					*/
			}
			break;

		case LF_POINTER_32:
			{
				lfPointer32* lf = (lfPointer32*)p2;

				Type* pPointerTo = GetType(lf->index, dwData);

				//ASSERT(lf->attr.isflat32);

				if (lf->attr.ptrmode == CV_PTR_MODE_PTR)
				{
					pType = m_pReceiver->CreatePointerType(type_pointer, pPointerTo);
				}
				else if (lf->attr.ptrmode == CV_PTR_MODE_REF)
				{
					pType = m_pReceiver->CreatePointerType(type_reference, pPointerTo);
				}
				else if (lf->attr.ptrmode == CV_PTR_MODE_PMEM)
				{
					// TODO
					ASSERT(0);
				}
				else if (lf->attr.ptrmode == CV_PTR_MODE_PMFUNC)
				{
					ClassType* pClass = (ClassType*)GetType(lf->pmclass, dwData);
					ASSERT(pClass->get_Kind() == type_class);

					PointerMemberType* p = new PointerMemberType(pPointerTo, pClass);
					p->m_sizeof = 16;
					pType = p;
				}
				else
					ASSERT(0);

				if (lf->attr.isconst || lf->attr.isvolatile)
				{
					pType = new ModifierType(pType, lf->attr.isconst, lf->attr.isvolatile);
				//	((CVType*)pType)->m_bConst = lf->attr.isconst;
				//	((CVType*)pType)->m_bVolatile = lf->attr.isvolatile;
				}

			//	return pType;
			}
			break;

		case LF_ARRAY_32:
			{
				lfArray* lf = (lfArray*)p2;
				ArrayType* pArrayType = new ArrayType();

				pArrayType->m_pElemType = GetType(lf->elemtype, dwData);

				Type* idxtype = GetType(lf->idxtype, dwData);
				//ASSERT(idxtype->GetKind() == type_int);

				if (pArrayType->m_pElemType->get_sizeof() == 0)
				{
					/*
					std::fprintf(stdout, "kind: %d\n", pArrayType->m_pElemType->get_Kind());
					if (pArrayType->m_pElemType->get_Kind() == type_class)
					{
						if (((ClassType*)pArrayType->m_pElemType)->m_def)
							std::fprintf(stdout, "defined\n");
						else
							std::fprintf(stdout, "not defined\n");

						std::fprintf(stdout, "%s\n", ((NamedType*)pArrayType->m_pElemType)->get_Name()->c_str());
					}
					std::fflush(stdout);
					*/
					raise(Exception(L"pArrayType->m_pElemType->get_sizeof() == 0"));
				}

				p2 += sizeof(lfArray);
				int size = GetNumeric(&p2);
				pArrayType->m_nElemCount = (unsigned int)(size / pArrayType->m_pElemType->get_sizeof());
				ASSERT(size == pArrayType->m_nElemCount * pArrayType->m_pElemType->get_sizeof());

				uint8 namelen = *p2++;
				char name[256];
				strncpy_s(name, (char*)p2, namelen);
				name[namelen] = 0;

				pType = pArrayType;
			}
			break;

		case LF_CLASS_32:
		case LF_STRUCTURE_32:
			{
				lfClass_32* lf = (lfClass_32*)p2;

				char name[256];
				strncpy_s(name, (char*)&lf->name[1], lf->name[0]);
				name[lf->name[0]] = 0;

				/*
				if (!strcmp(name, "System::HeapRecord"))
				{
					MessageBeep(-1);
				}
				*/

				String classqname = name;
				String classname;
				{
					const char* p = name;
					const char* p2 = p;

					while (*p)
					{
						if (p[0] == '<')
						{
							int open = 1;
							p++;
							while (*p)
							{
								if (*p == '<')
								{
									p++;
									open++;
								}
								else if (*p == '>')
								{
									p++;
									open--;
									if (open == 0)
										break;
								}
								else
									p++;
							}
						}
						else if (p[0] == ':' && p[1] == ':')
						{
							p += 2;
							p2 = p;
						}
						else
							p++;
					}
					classname = p2;
				}

				NamedType* pType2 = m_pReceiver->LookupNamedType(classqname);


				/*
				if (pType2)
				{
					pType = pType2;
					pClass = pType2->m_pClass;
				}
				else
					*/
				if (lf->property.fwdref)
				{
					if (pType2 == NULL)
					{
						ClassType* pClass = new ClassType;

						pClass->m_name = classname;
						pClass->m_qname = classqname;

						pClass->m_sizeof = lf->structlen;
						if (typ->leaf == LF_CLASS_32)
							pClass->m_kwType = ClassKey_class;
						else
							pClass->m_kwType = ClassKey_struct;

						//pClass->m_bVT = -1;	// This means forward reference
						pClass->m_def = false;

						m_pReceiver->OnType(pClass->m_qname, pClass, dwData);

						pType = pClass;
					}
					else
					{
						pType = pType2;
					}

					m_pTypes[index/*typind*/] = pType;
				}
				else
				{
					ClassType* pClass = NULL;

					if (pType2)
					{
						if (pType2->get_Kind() != type_class)
						{
					//		pType2 = NULL;
						}
					}

					if (pType2 && pType2->get_Kind() == type_class)	// If previous definition
					{
						if (pType2->AsClass()->m_def == false)	// If the previous definition was a forward reference
						{
							pClass = pType2->AsClass();	// Read into the previous forward reference
							//pType = pClass;
						}
						else
						{
						// Create a new class, read into it and compare with previous definition
							if (false)
							{
								pClass = new ClassType;
								pClass->m_name = classname;
								pClass->m_qname = classqname;
							}
						}

						pType = pType2;
						m_pTypes[index/*typind*/] = pType2;
					}
					else
					{
						pClass = new ClassType;	// No previous definition, create a new class
						pClass->m_name = classname;
						pClass->m_qname = classqname;

						if (typ->leaf == LF_CLASS_32)
							pClass->m_kwType = ClassKey_class;
						else
							pClass->m_kwType = ClassKey_struct;

						pType = pClass;
						m_pTypes[index/*typind*/] = pClass;

						if (pType2 == NULL)
						{
							m_pReceiver->OnType(pClass->m_qname, pClass, dwData);
						}
					}

					if (pClass)
					{
						pClass->m_def = true;
						pClass->m_sizeof = lf->structlen;

						/*
						if (*pClass->m_name == "HTMLGenericElement")
						{
							MessageBeep(-1);
						}
						*/

						if (lf->vshape)
						{
							pClass->m_bVT = true;
						}
						else
						{
							pClass->m_bVT = false;
						}

						if (lf->field)
						{
							TYPTYPE* typ2 = (TYPTYPE*)(p + m_pOMFGlobalTypes->typeOffset[lf->field - 0x1000]);

							if (typ2->leaf == LF_FIELDLIST_32)
							{
								FieldList(typ2, pClass, dwData);
							}
						}

						if (lf->derived)
						{
							TYPTYPE* typ2 = (TYPTYPE*)(p + m_pOMFGlobalTypes->typeOffset[lf->derived-0x1000]);

							if (typ2->leaf == LF_DERIVED_32)
							{
								lfDerived_32* lf = (lfDerived_32*)&typ2->leaf;

								for (int i = 0; i < lf->count; i++)
								{
									Type* pType = GetType(lf->drvdcls[i], dwData);
									VERIFY(pType->get_Kind() == type_class);
								//	VERIFY(((ClassType*)pType.m_p)->m_bVT != -1);

									pClass->m_derived.push_back(pType->AsClass());
								}
							}
						}

						//pType2 = m_pReceiver->LookupNamedType(pClass->m_qname);

						if (pType2 && pClass != pType2)	// Previous definition
						{
							if (true)
							{
#if 0
								if (!pType2->Equals(*(Type*)pClass))
								{
									StringA* str1 = pType->ToString();
									StringA* str2 = pType2->ToString();

									//pType2->Equals(*(Type*)pClass.m_p);

									/*
									if (*pType->GetClass()->m_qname == "_OVERLAPPED")
									{
										MessageBeep(-1);
									}
									*/

								//	__live_object_ptr<StringA> msg = new StringA("Duplicate class definition for " + *pType->GetClass()->m_qname + " not equal");
									BufferImp<char> buffer;
									StringBuilderA strbuilder(&buffer);
									strbuilder << "Duplicate class definition for " << *pType->GetClass()->m_qname << " not equal";
								//	MessageBoxA(NULL, msg.c_str(), NULL, MB_OK);//pType2->IsEqual(pType);
									TRACE("%s\n", buffer.DetachToString()->c_str());

									//pType2->Equals(*(Type*)pClass.m_p);

									pType = pClass;	// If they're not equal
								}
#endif
							}

							ClassType* pClass2 = pType2->AsClass();
							for (uint i = 0; i < pClass->m_derived.size(); i++)
							{
								pClass2->m_derived.push_back(pClass->m_derived[i]);
							}

							// Delete this new definition and instead use the old definition

						//	pType->Release();
							//pType = pType2;
						}
						else
						{
	#if 0
							m_pReceiver->OnType(pClass->m_qname, pClass, dwData);
	#endif
							
							//	pType = pType2;
						}
					}
				}
			}
			break;
	
		case LF_UNION_32:
			{
				lfUnion32* lf = (lfUnion32*)p2;
				const uint8* p = p2 + offsetof(lfUnion32, data);
				unsigned int size = GetNumeric(&p);
				uint8 namelen = *p++;
				char name[256];
				strncpy_s(name, (char*)p, namelen);
				name[namelen] = 0;

				String classqname = name;
				String classname;
				{
					const char* p = name;
					const char* p2 = p;

					while (*p)
					{
						if (p[0] == '<')
						{
							int open = 1;
							p++;
							while (*p)
							{
								if (*p == '<')
								{
									p++;
									open++;
								}
								else if (*p == '>')
								{
									p++;
									open--;
									if (open == 0)
										break;
								}
								else
									p++;
							}
						}
						else if (p[0] == ':' && p[1] == ':')
						{
							p += 2;
							p2 = p;
						}
						else
							p++;
					}
					classname = p2;
				}

				//NamedType* pType2 = m_pReceiver->LookupNamedType(classqname);

				ClassType* pClassType = new ClassType;
				pClassType->m_name = classname;
				pClassType->m_qname = classqname;
				pClassType->m_kwType = ClassKey_union;
				pClassType->m_sizeof = size;

				pType = pClassType;
			}
			break;

		case LF_VTSHAPE:
			{
				lfVTShape* lf = (lfVTShape*)p2;

				uint8* p = lf->desc;
				for (int i = 0; i < lf->count; i++)
				{
					if (i & 1)
					{
						uint8 v = (*p) & 0xF;
						p++;
						ASSERT(v == CV_VTS_near32);
					}
					else
					{
						uint8 v = (*p)>>4;
						ASSERT(v == CV_VTS_near32);
					}
				}
			}
			break;

		case LF_BITFIELD_32:
			{
				lfBitfield32* lf = (lfBitfield32*)p2;

				Type* pBitfieldType = GetType(lf->type, dwData);

				pType = new BitfieldType(pBitfieldType, lf->position, lf->length);
			}
			break;

		default:
			ASSERT(0);
		}
		m_pTypes[index/*typind*/] = pType;

		return pType;
	}

	ASSERT(0);
	return NULL;
}

#define SIGNATURE_NB11	0x3131424e

int CodeViewDebugInfo::Parse(ObjectFileParser* pImage, IDebugInfoReceiver* pReceiver, ULONG_PTR dwData)
{
	COFFParser* m_pImage = (COFFParser*)pImage;

	m_pReceiver = pReceiver;

	uint8* p = m_data;
	uint32* signature = (uint32*)p;
	if (*signature != SIGNATURE_NB11)
	{
		return -1;
	}

	DebugTraceLn("CodeViewDebugInfo::Parse - SIGNATURE_NB11");

	uint32 offset;

	offset = *(uint32*)(m_data+4);
	while (offset)
	{
		OMFDirHeader* dirheader = (OMFDirHeader*)(p+offset);
		OMFDirEntry* direntry = (OMFDirEntry*)(dirheader+1);

		for (uint i = 0; i < dirheader->cDir; ++i)
		{
			switch (direntry->SubSection)
			{
			case sstGlobalTypes:
				{
					ASSERT(m_pOMFGlobalTypes == NULL);
					if (m_pOMFGlobalTypes != NULL) throw -1;

					m_pOMFGlobalTypes = (OMFGlobalTypes*)(p+direntry->lfo);

					m_pTypes.resize(m_pOMFGlobalTypes->cTypes);
					//memset(m_pTypes, 0, sizeof(Type*) * (m_pOMFGlobalTypes->cTypes));

			//		m_TypeRecursive = new int[m_pOMFGlobalTypes->cTypes];
			//		memset(m_TypeRecursive, 0, sizeof(int)*m_pOMFGlobalTypes->cTypes);
				}
				break;
			}
			direntry++;
		}

		offset = dirheader->lfoNextDir;
	}

	offset = *(uint32*)(m_data+4);
	while (offset)
	{
		OMFDirHeader* dirheader = (OMFDirHeader*)(p+offset);
		OMFDirEntry* direntry = (OMFDirEntry*)(dirheader+1);

		/*
		for (int i = 0; i < dirheader->cDir; i++)
		{
			switch (direntry->SubSection)
			{
			case sstGlobalTypes:
				{
					ATLASSERT(m_pGlobalTypes == NULL);
					if (m_pGlobalTypes != NULL) throw -1;

					m_pGlobalTypes = (OMFGlobalTypes*)(p+direntry->lfo);

					m_pTypes = new Type*[m_pGlobalTypes->cTypes];
				}
				break;
			}
			direntry++;
		}
		*/

		for (uint i = 0; i < dirheader->cDir; ++i)
		{
		//	printf("SubSection: %s(%x)\n", str, direntry->SubSection);

			switch (direntry->SubSection)
			{
			case sstSrcModule:
				{
					OMFSourceModule* pSourceModule = (OMFSourceModule*)(p+direntry->lfo);
					for (int i = 0; i < pSourceModule->cFile; ++i)
					{
						SourceFile* sourceFile = new SourceFile;
						
						//	printf("%d\n", pSourceModule->baseSrcFile[i]);
						OMFSourceFile* pSourceFile = (OMFSourceFile*)((char*)pSourceModule + pSourceModule->baseSrcFile[i]);
						char* p = ((char*)pSourceFile) + 4;
						for (uint j = 0; j < pSourceFile->cSeg; ++j)
						{
							OMFSourceLine* pSourceLine = (OMFSourceLine*)((char*)pSourceModule + pSourceFile->baseSrcLn[j]);
							p += 4;

							uint32 *offset = (uint32*)((char*)pSourceLine + 4);
							uint16* lineNbr = (uint16*)((char*)pSourceLine + 4 + pSourceLine->cLnOff*4);

							for (uint k = 0; k < pSourceLine->cLnOff; ++k)
							{
								sourceFile->m_lines.Add(SourceFile::SourceLine(offset[k] + 0x401000, lineNbr[k]));
								//	printf("offset: %d\n", offset[k]);
							}
							/*
							for (k = 0; k < pSourceLine->cLnOff; k++)
							{
							//	printf("lineNbr: %d\n", lineNbr[k]);
							}
							*/
						}
						
						for (int j = 0; j < pSourceFile->cSeg; j++)
						{
							uint32 start = *(uint32*)p; p += 4;
							uint32 end = *(uint32*)p; p += 4;
							
							MyTrace("%X - %X\t", start, end);
							
							// TODO
							start += 0x401000;
							end += 0x401000;
							
							sourceFile->m_segments.Add(SourceFile::Segment(start, end));
						}
						
						/*
						for (j = 0; j < pSourceFile->cSeg; j++)
						{
						WORD segment = *(WORD*)p; p += 2;
						}
						*/
						//											WORD cfName = *(WORD*)p; p += 2;
						uint8 cfName = *(uint8*)p; p += 1;
						//	char* name = (char*)p;

						char name[256];
						strncpy_s(name, p, cfName);
						name[cfName] = 0;

						p += cfName;
						//	printf("filename: %s\n", name);
						sourceFile->m_filename = string_copy(name);
						
					//	DebugTraceLn(sourceFile->m_filename);
						
						/*ctx->m_pDebugInfo->*/m_sourceFiles.Add(sourceFile);
					}
				}
				break;
				
			case sstStaticSym:
			case sstGlobalSym:
			case sstGlobalPub:
				{
					//	printf("SubSection: %s(%x)\n", str, direntry->SubSection);
					
					OMFSymHash* pSymHash = (OMFSymHash*)(p+direntry->lfo);
					
					uint8* start = (uint8*)(pSymHash+1);
					SYMTYPE* pSym = (SYMTYPE*)start;
					
					while ((uint8*)pSym < start + pSymHash->cbSymbol)
					{
						//SYMTYPE* pSym = (SYMTYPE*)p;
						//	int rectyp = ;
						//	if (rectyp & 0x1000) rectyp &= ~0x1000;
						//	ATLASSERT(rectyp > 0);
						switch (pSym->rectyp)
						{
						case S_PROCREF:
						case S_DATAREF:
							{
								REFSYM* pRefSym = (REFSYM*)pSym;
								
								if (pSym->rectyp == S_PROCREF)
									;//MyTrace("procref");
								else
									;//MyTrace("dataref");
								
								//MyTrace(": imod %d, sumName: %d, ibSym: %d\n", pRefSym->imod, pRefSym->sumName, pRefSym->ibSym);
								
								uint8* proc = (m_data + pRefSym->ibSym);
								
								//	LPBYTE name = (LPBYTE)pSym + pSym->reclen;
								//	length += (*name + 1 + 3) & ~3;
							}
							break;
							
						case S_UDT_32:
							{
								uint32 flags = 1;

								if (flags & 1)
								{
									UDTSYM32* pUdt = (UDTSYM32*)pSym;
									
									char name[258];
									strncpy_s(name, (char*)&pUdt->name[1], (uint8)pUdt->name[0]);
									name[(uint8)pUdt->name[0]] = 0;
									
									Type* pType = GetType(pUdt->typind, dwData);
								}

							//	MyTrace("udt:\t%s - typind: %d\n", name, pUdt->typind);
							}
							break;
							
						case S_CONSTANT_32:
							{
								CONSTSYM32* pConstSym = (CONSTSYM32*)pSym;
								
								char name[258];
								strncpy_s(name, (char*)&pConstSym->name[1], (uint8)pConstSym->name[0]);
								name[(uint8)pConstSym->name[0]] = 0;
								
							//	MyTrace("constant:\t%s - typind: %d, value: %d \n", name, pConstSym->typind, pConstSym->value);
							}
							break;
							
						case S_PUB_32:
							{
								DATASYM_32* pPubSym = (DATASYM_32*)pSym;
								
								char name[258];
								strncpy_s(name, (char*)&pPubSym->name[1], (uint8)pPubSym->name[0]);
								name[(uint8)pPubSym->name[0]] = 0;
								

								IMAGE_SECTION_HEADER *pSection = &m_pImage->m_SectionHeader[pPubSym->seg-1];
								uint32 address = m_pImage->m_loadAddress + pSection->VirtualAddress + pPubSym->off;
#if 0							
								//	printf("pub32:\t%s - off: %X, seg: %d, typind: %d\n", name, pPubSym->off, pPubSym->seg, pPubSym->typind);
								DebugSymbol* pDebugSymbol = new DebugSymbol(name, address);
								
#if 0
								pModule->symbols.insert(tysymbolmap_address::value_type(address, pDebugSymbol));
#endif

								symbols.insert(tysymbolmap_address::value_type(address, pDebugSymbol));
								
								ASSERT(pDebugSymbol->m_name.Length());
							//	symbols_name.insert(tysymbolmap_name::value_type(pDebugSymbol->m_name, pDebugSymbol));
								//if (strstr(name, "get_"))
								{
									//Sleep(0);
									MyTrace("%s\n", name);
									if (pPubSym->typind)
										GetType(pPubSym->typind);
								}

								symbols_name[pDebugSymbol->m_name] = pDebugSymbol;
#endif
								m_pReceiver->OnSymbol(name, address, dwData);
							}
							break;
							/*
							
							  case S_REGISTER:
							  {
							  REGSYM* pRegSym = (REGSYM*)pSym;
							  
								 char name[258];
								 strncpy(name, (char*)&pRegSym->name[1], pRegSym->name[0]);
								 name[pRegSym->name[0]] = 0;
								 
									printf("reg:\t%s - %d - %d\n", name, pRegSym->reg, pRegSym->typind);
									}
									break;
									
									  case S_UDT:
									  {
									  ATLASSERT(0);
									  }
									  break;
									  
										 case S_OBJNAME:
										 {
										 OBJNAMESYM* pOSym = (OBJNAMESYM*)pSym;
										 
											char name[258];
											strncpy(name, (char*)&pOSym->name[1], pOSym->name[0]);
											name[pOSym->name[0]] = 0;
											
											  printf("S_OBJNAME\n");
											  }
											  break;
							*/
							
						case S_ALIGN:
							{
								//	printf("S_ALIGN\n");
							}
							break;
							
						default:
							{
								printf("rectyp: %x\n", pSym->rectyp);
								//	PUBSYM32* pPubSym = (PUBSYM32*)p;
							ASSERT(0);
							}
							break;
						}
							
						pSym = NextSym(pSym);
					}
				}
				break;

			case sstAlignSym:
				{
					Scope* pCurrentScope = m_pGlobalScope;

					uint8* start = (p+direntry->lfo);
					SYMTYPE* pSym = (SYMTYPE*)(p+4+direntry->lfo);

				//	pSym = NextSym(pSym);
					while ((uint8*)pSym < start+direntry->cb)
					{
						switch (pSym->rectyp)
						{
						case S_UDT_32:
							{
								if (true)
								{
									UDTSYM32* pUdt = (UDTSYM32*)pSym;
									
									char name[256];
									strncpy_s(name, (char*)&pUdt->name[1], pUdt->name[0]);
									name[pUdt->name[0]] = 0;
									
									System::Type* pType = GetType(pUdt->typind, dwData);
								}
							//	TRACE("udt:\t%s - typind: %d\n", name, pUdt->typind);
							}
							break;

						case S_CONSTANT_32:
							{
								CONSTSYM32* pConstSym = (CONSTSYM32*)pSym;
								
								char name[258];
								strncpy_s(name, (char*)&pConstSym->name[1], pConstSym->name[0]);
								name[pConstSym->name[0]] = 0;
								
								MyTrace("constant:\t%s - typind: %d, value: %d \n", name, pConstSym->typind, pConstSym->value);
							}
							break;

							/*
						case S_COMPILE:
							{
								CompileSym((CFLAGSYM*)pSym);
							}
							break;
							*/

						case S_GDATA_32:
						case S_LDATA_32:
							{
								uint32 flags = 1;

								if (flags & 1)
								{
									DATASYM_32* pDataSym = (DATASYM_32*)pSym;

									char name[256];
									strncpy_s(name, (char*)pDataSym->name+1, pDataSym->name[0]);
									name[pDataSym->name[0]] = 0;

									/*
									if (strstr(name, "UI::Visual"))
									{
										TRACE("%s\n", name);
									}
									*/

									//DataSymbol* data = new DataSymbol;

									IMAGE_SECTION_HEADER *pSection = &m_pImage->m_SectionHeader[pDataSym->seg-1];
									uint32 /*data->m_*/ address = m_pImage->m_loadAddress + pSection->VirtualAddress + pDataSym->off;

									Type* pType = GetType(pDataSym->typind, dwData);

									m_pReceiver->OnData(name, pType, address, dwData);
								}
							}
							break;

						case S_GPROC_32:
						case S_LPROC_32:
							{
								uint32 flags = 1;

								if (flags & 1)
								{
									PROCSYM_32* pProcSym = (PROCSYM_32*)pSym;

									char name[256];
									strncpy_s(name, (char*)pProcSym->name+1, pProcSym->name[0]);
									name[pProcSym->name[0]] = 0;

									Type* pType = NULL;
									if (pProcSym->typind)
									{
										pType = GetType(pProcSym->typind, dwData);
										if (pType == NULL)
										{
										//	Type* pType = GetType(pProcSym->typind, dwData);
										}
										ASSERT(pType->get_Kind() == type_function);
									}

									/*
									if (!strcmp(name, "Object2"))
									{
										MessageBeep(-1);
									}
									*/

									//MyTrace("%s: %s\n", pSym->rectyp == S_GPROC_32? "GPROC": "LPROC", name);

									//Scope* pScope = new Scope;
									IMAGE_SECTION_HEADER *pSection = &m_pImage->m_SectionHeader[pProcSym->seg-1];
									uint32 /*pScope->m_*/ startAddress = m_pImage->m_loadAddress + pSection->VirtualAddress + pProcSym->off;
									uint32 /*pScope->m_*/ endAddress = /*pScope->m_*/ startAddress + pProcSym->len;

									/*
									pCurrentScope->m_subScopes.Add(pScope);
									pScope->m_pParentScope = pCurrentScope;
									pCurrentScope = pScope;

									pScope->m_pType = pType;
									*/

									//if (pType)
									{
									//	m_pReceiver->OnProc(name, pScope, dwData);
										pCurrentScope = m_pReceiver->OnProc(pCurrentScope, name, pType, /*pScope->m_*/startAddress, endAddress, dwData);
									}
								}
							}
							break;

						case S_THUNK32:
							{
								THUNKSYM32* pThunkSym = (THUNKSYM32*)pSym;

								char name[256];
								strncpy_s(name, (char*)pThunkSym->name+1, pThunkSym->name[0]);
								name[pThunkSym->name[0]] = 0;

								if (pCurrentScope)
								{
								// TODO, callback
									Scope* pScope = new Scope;
									IMAGE_SECTION_HEADER *pSection = &m_pImage->m_SectionHeader[pThunkSym->seg-1];
									pScope->m_startAddress = m_pImage->m_loadAddress + pSection->VirtualAddress + pThunkSym->off;
									pScope->m_endAddress = pScope->m_startAddress + pThunkSym->len;

									pCurrentScope->m_subScopes.Add(pScope);
									pScope->m_pParentScope = pCurrentScope;
									pCurrentScope = pScope;

							//	m_procs[name] = pScope;
#if 0
								m_pReceiver->OnProc(name, pScope, dwData);
#endif
								}
							}
							break;

						case S_BLOCK32:
							{
								BLOCKSYM32* pBlockSym = (BLOCKSYM32*)pSym;
							//	printf("off: %d, len: %d", pBlockSym->off, pBlockSym->len);

								if (pCurrentScope)
								{
									Scope* pScope = new Scope;
									pScope->m_startAddress = pCurrentScope->m_startAddress + pBlockSym->off;
									pScope->m_endAddress = pScope->m_startAddress + pBlockSym->len;

									pCurrentScope->m_subScopes.Add(pScope);
									pScope->m_pParentScope = pCurrentScope;
									pCurrentScope = pScope;
								}
							}
							break;

						case S_BPREL_32:
							{
								BPRELSYM_32* pRelSym = (BPRELSYM_32*)pSym;

								if (pCurrentScope)
								{
								//	char name[258];
								//	strncpy_s(name, (char*)pRelSym->name, pRelSym->namelen);
								//	name[pRelSym->namelen] = 0;

								//	printf("%s, [ebp%+d]\n", name, pRelSym->off);

									Declarator* pDecl = new Declarator;
								//	pDecl->m_pType = new Type(type_int, 4);
									pDecl->m_pType = GetType(pRelSym->typind, dwData);
									pDecl->m_name = StringData((char*)pRelSym->name, pRelSym->namelen);
									pDecl->m_localVar = true;
									pDecl->m_offset = pRelSym->off;

									pCurrentScope->m_decls.insert(declsmap::value_type(pDecl->m_name, pDecl));
								}
							}
							break;

						case S_OBJNAME:
							{
								OBJNAMESYM* pObjSym = (OBJNAMESYM*)pSym;

								uint8 len = (uint8)pObjSym->name[0];
								char name[258];
								strncpy_s(name, (char*)pObjSym->name+1, len);
								name[len] = 0;

							//	TRACE("%s\n", name);
							}
							break;

  /*
						case S_OBJNAME:	// path to object filename
							{
							//	MyTrace("ObjName: len %d\n", pSym->reclen);
							}
							break;
							*/

						case S_END:
							{
								pCurrentScope = m_pReceiver->End(pCurrentScope);
								/*
								pCurrentScope = pCurrentScope->m_pParentScope;
								ASSERT(pCurrentScope);
								*/
							}
							break;

						case S_COMPILE:	// Compile flags symbol
							{
							//	MyTrace("Compile: len %d\n", pSym->reclen);
							}
							break;

						case S_LABEL32:	// code label
							{
							//	MyTrace("Label: len %d\n", pSym->reclen);
								LABELSYM32* label = (LABELSYM32*)pSym;
							}
							break;

						case S_SSEARCH:
							{
								MyTrace("StartSearch: len %d\n", pSym->reclen);
							}
							break;

						case 0x1013:	// Unknown
							{
							}
							break;

						default:
					;//		ASSERT(0);
							MyTrace("unknown: 0x%x, %d\n", pSym->rectyp, pSym->reclen);
						}

						pSym = NextSym(pSym);
					}

					ASSERT(pCurrentScope == m_pGlobalScope);
					if (pCurrentScope != m_pGlobalScope)
					{
						MessageBoxA(NULL, "pCurrentScope != pGlobalScope", "", MB_OK);
					}
				}
				break;

				default:
				;//	ASSERT(0);
			}

			direntry++;
		}

		offset = dirheader->lfoNextDir;
	}

	return 0;
}

Scope* CodeViewDebugInfo::GetScope()
{
	return m_pGlobalScope;
}

}	// System
