#include "stdafx.h"
#include "LFC.h"
#include "VCMangler.h"

#if 0

http://en.wikipedia.org/wiki/Microsoft_Visual_C%2B%2B_Name_Mangling


or..

This page explains the specific manner in which the Microsoft Visual C++ series of compilers mangle symbol names.


MangledName ::=
    '?' OperatorName '@' TypeCode
    '?' QualifiedName '@' TypeCode

OperatorName ::=
    OperatorCode QualifiedName

QualifiedName ::=
    Identifier +

Identifier ::=
    string '@'
    '0'-'9' /* reference to previously used identifier */

OperatorCode ::=
    '?0'            /* myclass::myclass                                         unary */
    '?1'            /* myclass::~myclass                                        unary */
    '?2'            /* myclass::operator new                                          */
    '?3'            /* myclass::operator delete                                       */
    '?4'            /* myclass::operator=                                      binary */
    '?5'            /* myclass::operator>>                                     binary */
    '?6'            /* myclass::operator<<                                     binary */
    '?7'            /* myclass::operator!                                       unary */
    '?8'            /* myclass::operator==                                     binary */
    '?9'            /* myclass::operator!=                                     binary */
    '?D'            /* myclass::operator*                                      binary */
    '?E'            /* myclass::operator++                                      unary */
    '?F'            /* myclass::operator--                                      unary */
    '?G'            /* myclass::operator-                                      binary */
    '?H'            /* myclass::operator+                                      binary */
    '?I'            /* myclass::operator&                                      binary */
    '?J'            /* myclass::operator->*                                    binary */
    '?K'            /* myclass::operator/                                      binary */
    '?L'            /* myclass::operator%                                      binary */
    '?M'            /* myclass::operator<                                      binary */
    '?N'            /* myclass::operator<=                                     binary */
    '?O'            /* myclass::operator>                                      binary */
    '?P'            /* myclass::operator>=                                     binary */
    '?Q'            /* myclass::operator,                                      binary */
    '?R'            /*    operator ()                                                  */
    '?S'            /* myclass::operator~                                       unary */
    '?T'            /* myclass::operator^                                      binary */
    '?U'            /* myclass::operator|                                      binary */
    '?V'            /*      operator &&                                               */
    '?W'            /* myclass::operator||                                     binary */
    '?X'            /* myclass::operator*=                                     binary */
    '?Y'            /* myclass::operator+=                                     binary */
    '?Z'            /* myclass::operator-=                                     binary */
    '?_0'           /* myclass::myclass/=                                      binary */
    '?_1'           /* myclass::myclass%=                                      binary */
    '?_2'           /* myclass::operator>>=                                    binary */
    '?_3'           /* myclass::operator<<=                                    binary */
    '?_4'           /* myclass::operator&=                                     binary */
    '?_5'           /* myclass::operator|=                                     binary */
    '?_6'           /* myclass::operator^=                                     binary */
    '?_7'           /* myclass::`vftable'                                             */
    '?_R0?AV'       /* myclass `RTTI Type Descriptor'                                 */
    '?_R1A@?0A@EA@' /* myclass::`RTTI Base Class Descriptor at (0,-1,0,64)'           */
    '?_R2'          /* myclass::`RTTI Base Class vector'                               */
    '?_R3'          /* myclass::`RTTI Class Hierarchy Descriptor'                     */
    '?_R4'          /* myclass::`RTTI Complete Object Locator'                        */
    '?_U'           /* myclass::operator new[]                                        */
    '?_V'           /* myclass::operator delete[]                                     */

TypeCode ::=
    'Y' FunctionType /* global function */
    'Q' FunctionType /* public method */
    'I' FunctionType /* protected method */
    'A' FunctionType /* private method */
    'S' FunctionType /* public class method */
    'K' FunctionType /* protected class method */
    'C' FunctionType /* private class method */
    '2' DataType StorageClass
    '3' DataType StorageClass

FunctionType ::=
    CallingConvention ReturnValue ArgumentList StorageClass

CallingConvention ::=
    'A'  /* __cdecl    */
    'G'  /* __stdcall  */
    'I'  /* __fastcall */
    'AA' /* __cdecl for methods ('this' in stack)*/
    'AE' /* __thiscall ('this' in ECX)*/

ReturnValue ::=
    'X'  /* void */
    DataType

ArgumentList ::=
    'X'  /* void */
    DataType+
    DataType+ '@'  /* __cdecl, without vararg */
    DataType+ 'Z'  /* __cdecl, with vararg */

DataType ::=
    SimpleDataType
    PointerDataType

SimpleDataType ::=
    'C'  /* signed char      */
    'D'  /* char             */
    'E'  /* unsigned char    */
    'F'  /* short            */
    'G'  /* unsigned short   */
    'H'  /* int              */
    'I'  /* unsigned int     */
    'J'  /* long             */
    'K'  /* unsigned long    */
    'M'  /* float            */
    'N'  /* double           */
    'O'  /* long double      */
    'U'  /* struct           */ QualifiedName '@'
    'T'  /* union            */ QualifiedName '@'
    'V'  /* class            */ QualifiedName '@'
    '_J' /* __int64          */
    '_K' /* unsigned __int64 */
    '_N' /* bool             */
    '_W' /* __wchar_t        */

PointerDataType ::=
    ReferenceOrPointer Pointer* 'A|B|C' (SimpleDataType | 'X')
    ReferenceOrPointer Pointer* '6' FunctionType
    '0'-'9' /* reference to previously used PointerDataType */

ReferenceOrPointer ::=
    'A' /* reference to */
    'P' /* pointer to */
    'Q' /* const pointer to */
    'R' /* volatile pointer to */

Pointer ::=
    'AP' /* pointer to */
    'BQ' /* const pointer to */
    'CR' /* volatile pointer to */

StorageClass ::
    'A'  /* Normal Storage     */
    'B'  /* Volatile Storage   */
    'C'  /* Const Storage      */
    'Z'  /* Executable Storage */
#endif

namespace System
{

// static
int VCMangler::m_x64 = 0;

VCMangler::VCMangler() : m_names(less<TypeSerializable*>(), grow_allocator(m_buffer, 512))
{
	m_n = 0;
}

IO::TextWriter& VCMangler::WriteName(TypeSerializable* str, IO::TextWriter& strbuilder)
{
	/*
	map<TypeSerializable*, int, less<TypeSerializable*>, grow_allocator>::iterator it = m_names.find(str);
	if (it != m_names.end())
	{
		strbuilder << (*it).second;
	}
	else
	*/
	{
		String name;
		/*
		if (dynamic_cast<Namespace*>(str))
		{
			name = dynamic_cast<Namespace*>(str)->m_name;
		}
		else
		*/
		{
			name = dynamic_cast<NamedType*>(str)->m_name;
		}

		if (name)
		{
			strbuilder << name;
	//	else
	//		strbuilder << "__unknown";

			strbuilder << "@";
		}
	}

	return strbuilder;
}

IO::TextWriter& VCMangler::MangleNameName(Declarator* pDeclarator, IO::TextWriter& strbuilder)
{
//cdecl:
//?funcName @@YA retType params-list Z

	strbuilder << "?";
	strbuilder << pDeclarator->m_name;
	strbuilder << "@@YA";

	FunctionType* pFunction = pDeclarator->m_pType->AsFunction();

	// TODO; I don't understand this
	if (pFunction->m_pReturnType->get_Kind() == type_class ||
		pFunction->m_pReturnType->get_Kind() == type_enum)
	{
		strbuilder << "?A";	// Anonymous namespace ?
	}

	MangleType(pFunction->m_pReturnType, strbuilder);

	if (pFunction->m_parameters.m_parameters.size() == 0)
	{
		strbuilder << "X";
	}
	else
	{
		ASSERT(0);
	}

	strbuilder << "Z";

	return strbuilder;
}

void EncodeSigned(IO::TextWriter& stream, int num)
{
	if (num < 0)
	{
		stream << "?";
		num = -num;
	}

	if (num == 0)
	{
		stream << "@";
	}
	else if (num <= 10)
	{
		stream << char('0' + (num-1));
	}
	else
	{
		char buffer[32];
		char* p = buffer + 32;

		--p;
		*p = 0;

		while (num)
		{
			int k = num & 0xF;

			--p;
			*p = char('A' + k);

			num >>= 4;
		}

		stream << p;
		stream << "@";
	}
}

IO::TextWriter& VCMangler::MangleNameName(Scope* pScope, IO::TextWriter& strbuilder)
{
	if (pScope->m_pNamespace->AsClass())
	{
	//	m_names.insert(map<TypeSerializable*,int>::value_type(pScope->m_pClass, m_names.size()));
		auto it = m_names.find(pScope->m_pNamespace->AsClass());
		if (it != m_names.end())
		{
			strbuilder << it->second;
			if (pScope->m_pParentScope)
			{
				MangleNameName(pScope->m_pParentScope, strbuilder);
			}
		}
		else
		{
			m_names.insert(map<TypeSerializable*,int>::value_type(pScope->m_pNamespace->AsClass(), m_n));
			m_n++;

			if (pScope->m_pNamespace->AsClass()->m_pInstantiatedFromArgs && pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass == nullptr)
			{
				MessageBox(NULL, L"hm", L"hm", MB_OK);
				strbuilder << "BUG " << __FILE__ << '(' << __LINE__ << ") ";
				return strbuilder;
			}

			if (pScope->m_pNamespace->AsClass()->m_pInstantiatedFromArgs && pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass->m_pTemplateParams)
			{
				/*
				map<TypeSerializable*, int, less<TypeSerializable*>, grow_allocator>::iterator it = m_names.find(pScope->m_pClass->m_pInstantiatedFrom);
				if (it != m_names.end())
				{
					strbuilder << (*it).second;
				}
				else
				*/
				{
				//	m_names.insert(map<TypeSerializable*, int, less<TypeSerializable*>, grow_allocator>::value_type(pScope->m_pClass->m_pInstantiatedFrom, m_names.size()));
					// hm..
				//	m_n++;
					//m_names.insert(map<TypeSerializable*, int, less<TypeSerializable*>, grow_allocator>::value_type(NULL, m_names.size()));

					strbuilder << "?$";

					VCMangler mangler;
					mangler.m_n = 1;//m_n-1;	// ??

					WriteName(pScope->m_pNamespace->AsClass(), strbuilder);

					ClassType* pInstantiatedFromClass = pScope->m_pNamespace->AsClass()->m_pInstantiatedFromClass;
					ActualTemplateArgs* pInstantiatedFromArgs = pScope->m_pNamespace->AsClass()->m_pInstantiatedFromArgs;

					for (size_t i = 0; i < pInstantiatedFromArgs->m_items.size(); ++i)
					{
						ActualTemplateArg* pArg = pInstantiatedFromArgs->m_items[i];
						FormalTemplateArg* pFormalArg = pInstantiatedFromClass->m_pTemplateParams->m_items[i];

						if (pFormalArg->m_kind == TemplateParameter::Param_Type)
						{
							Type* pType = pArg->m_pType;
							if (pType)
								mangler.MangleType(pType, strbuilder);
							else
								strbuilder << "__BUG__" << __FILE__ << "(" << __LINE__ << ")";
						}
						else
						{
							strbuilder << "$0";
							EncodeSigned(strbuilder, pArg->m_value);
							/*
							// TODO here
							if (pArg->m_value == 0)
								strbuilder << "0";
							else
								strbuilder << "1";
								*/
						}
					}

					strbuilder << '@';
					if (pScope->m_pParentScope && pScope->m_pParentScope->m_pNamespace->m_name)
					{
						MangleNameName(pScope->m_pParentScope, strbuilder);
					}

					/*
					map<TypeSerializable*,int, less<TypeSerializable*>, grow_allocator>::iterator it = mangler.m_names.begin();
					while (it != mangler.m_names.end())
					{
						if (m_names.find((*it).first) == m_names.end())
						{
							m_names.insert(map<TypeSerializable*,int, less<TypeSerializable*>, grow_allocator>::value_type((*it).first, m_names.size()));
						}
						++it;
					}
					*/
				}
			}
			else
			{
				WriteName(pScope->m_pNamespace->AsClass(), strbuilder);
				ASSERT(pScope->m_pNamespace->m_ownerScope == pScope->m_pParentScope);

				if (pScope->m_pNamespace->m_ownerScope && pScope->m_pNamespace->m_ownerScope->m_pNamespace->m_name)
				{
					MangleNameName(pScope->m_pNamespace->m_ownerScope, strbuilder);
				}

				/*
				if (pScope->m_pParentScope && pScope->m_pParentScope->m_pNamespace->m_name)
				{
					MangleNameName(pScope->m_pParentScope, strbuilder);
				}
				*/
			}
		}
	}
	else
	{
		auto it = m_names.find(pScope->m_pNamespace);
		if (it != m_names.end())
		{
			strbuilder << it->second;

			if (pScope->m_pParentScope && pScope->m_pParentScope->m_pNamespace->m_name)
			{
				MangleNameName(pScope->m_pParentScope, strbuilder);
			}
		}
		else
		{
			m_names.insert(map<TypeSerializable*,int>::value_type(pScope->m_pNamespace, m_n));
			++m_n;

			WriteName(pScope->m_pNamespace, strbuilder);
			if (pScope->m_pParentScope && pScope->m_pParentScope->m_pNamespace->m_name)
			{
				MangleNameName(pScope->m_pParentScope, strbuilder);
			}
		}
	}

	return strbuilder;
}

IO::TextWriter& VCMangler::MangleType(Type* pType, IO::TextWriter& strbuilder)
{
	switch (pType->get_Kind())
	{
	case type_typedef:
		{
			Typedef* pTypedef = static_cast<Typedef*>(pType);

			if (pTypedef->m_pType == NULL)	// hm..
			{
				strbuilder << "typedefNULL";
				return strbuilder;
			}

#if 0
			if (pTypedef->m_ownerScope && pTypedef->m_ownerScope->m_pNamespace->GetClass())
			{
				strbuilder << "V";	// ??

			//	MangleType(pTypedef->m_pType, strbuilder);
				strbuilder << *pTypedef->m_name;

				strbuilder << '@';

				if (pTypedef->m_ownerScope && pTypedef->m_ownerScope->m_pNamespace->m_name)
				{
					MangleNameName(pTypedef->m_ownerScope, strbuilder);

					/*
					if (pTypedef->m_pOwnerScope->m_pClass)
					{
						MangleType(pTypedef->m_pOwnerScope->m_pClass, strbuilder);
					}
					*/
				}

				strbuilder << '@';
			}
			else
#endif
			{
				MangleType(pTypedef->m_pType, strbuilder);
			}
		}
		break;

	case type_templatearg:
		{
			// TODO, shouldn't happen
			strbuilder << "<arg>";
		}
		break;

#if 0
	case type_templateinst:
		{
			// TODO, shouldn't happen
			strbuilder << "<arginst>";
#if 0
			TemplatedClassType* pInst = (TemplatedClassType*)pType;
			
			if (pInst->m_pClass->m_kwType == CLASSKEY_CLASS)
				strbuilder << "V";
			else // CLASSKEY_STRUCT
				strbuilder << "U";

			strbuilder << "?$";
			
			MangleNameName2(pInst->m_pClass->m_qname, strbuilder);

			//strbuilder << "@";
		
			for (int i = 0; i < pInst->m_items.size(); i++)
			{
				Type* pArg = pInst->m_items[i];
				MangleType(pArg, strbuilder);
			//	strbuilder << "@";
			}
			
			strbuilder << "@";
			strbuilder << "@";
#endif
		}
		break;
#endif

	case type_class:
		{
			ClassType* pClassType = static_cast<ClassType*>(pType);

			if (pClassType->m_kwType == ClassKey_class)
				strbuilder << "V";
			else if (pClassType->m_kwType == ClassKey_struct || pClassType->m_kwType == ClassKey_interface)
				strbuilder << "U";
			else if (pClassType->m_kwType == ClassKey_union)
				strbuilder << "T";
			else
				ASSERT(0);

			/*
			map<Type*,int>::iterator it = m_pointers.find(pClassType);
			if (it != m_pointers.end())
			{
				strbuilder << "12";//(*it).second;
			}
			else
			*/
			{
				MangleNameName(pClassType->m_pScope, strbuilder);
			//	m_pointers.insert(map<Type*,int>::value_type(pClassType, m_pointers.size()));
			}

			strbuilder << '@';
		}
		break;
		
	case type_enum:
		{
			EnumType* pEnumType = static_cast<EnumType*>(pType);
			strbuilder << "W4";

			if (pEnumType->m_name)
				strbuilder << pEnumType->m_name;
			else
				strbuilder << "__unnamed";	// hmm ??

			strbuilder << '@';

			if (pEnumType->m_ownerScope)
			{
				MangleNameName(pEnumType->m_ownerScope, strbuilder);
			}

			strbuilder << '@';
		}
		break;

	case type_cv:
		{
			ModifierType* modifierType = dynamic_cast<ModifierType*>(pType);
			ASSERT(modifierType);

			if (modifierType->m_bConst)
			{
				strbuilder << 'B';
			}
			else
			{
				// TODO
				ASSERT(0);
			}

			if (modifierType->m_bVolatile)
			{
				// TODO
				ASSERT(0);
			}

			MangleType(modifierType->get_Type(), strbuilder);
			// TODO
		}
		break;

	case type_array:
		{
			ArrayType* arrayType = static_cast<ArrayType*>(pType);
			// ??

			strbuilder << 'P';	// pointer
			strbuilder << 'A';	// normal storage

			MangleType(arrayType->get_ElemType(), strbuilder);
		}
		break;

	case type_pointer:
		{
			strbuilder << 'P';	// pointer

			if (pType->GetPointerTo()->GetStripped())
			{
				if (pType->GetPointerTo()->GetStripped()->get_Kind() == type_function)
				{
					MangleType(pType->GetPointerTo(), strbuilder);
				}
				else
				{
					if (m_x64)
					{
						strbuilder << 'E';	// ??
					}

					if (pType->GetPointerTo()->get_Kind() != type_cv)
					{
						strbuilder << 'A';	// normal storage
					}

					MangleType(pType->GetPointerTo(), strbuilder);
				}
			}
			else
			{
				strbuilder << __FILE__ << paren(__LINE__) << " : __BUG__";
			}
		}
		break;
		
	case type_reference:
		{
			strbuilder << 'A';	// reference

			if (m_x64)
			{
				strbuilder << 'E';	// ??
			}

			if (pType->GetPointerTo()->get_Kind() == type_cv)
			{
				ModifierType* pModifierType = static_cast<ModifierType*>(pType->GetPointerTo());

				if (pModifierType->IsConst())
				{
					strbuilder << 'B';	// const
					MangleType(pModifierType->get_Type(), strbuilder);
				}
				else
				{
					strbuilder << 'A';	// normal storage
					MangleType(pModifierType->get_Type(), strbuilder);
				}
			}
			else
			{
				strbuilder << 'A';	// normal storage
				MangleType(pType->GetPointerTo(), strbuilder);
			}
		}
		break;

	case type_rvalue_reference:
		{
			strbuilder << "$$Q";

			/*
			if (m_x64)
			{
				strbuilder << 'E';	// ??
			}
			*/

			if (pType->GetPointerTo()->get_Kind() == type_cv)
			{
				ModifierType* pModifierType = static_cast<ModifierType*>(pType->GetPointerTo());

				if (pModifierType->IsConst())
				{
					strbuilder << 'B';	// const
					MangleType(pModifierType->get_Type(), strbuilder);
				}
				else
				{
					strbuilder << 'A';	// normal storage
					MangleType(pModifierType->get_Type(), strbuilder);
				}
			}
			else
			{
				strbuilder << 'A';	// normal storage
				MangleType(pType->GetPointerTo(), strbuilder);
			}
		}
		break;

	case type_pm:
		{
			PointerMemberType* pmf = static_cast<PointerMemberType*>(pType);

			strbuilder << 'P';	// pointer
			strbuilder << 'A';	// normal storage

			MangleType(pmf->m_pPointerTo, strbuilder);
		}
		break;

	case type_function:
		{
			FunctionType* pFunction = static_cast<FunctionType*>(pType);

			strbuilder << "6";
			strbuilder << "A";	// normal
			strbuilder << "X";
			MangleFunctionParameters(pFunction, strbuilder);
			strbuilder << "Z";
		}
		break;

	// basic types

	case type_null:					strbuilder << "Y";	break;	// ??

	case type_void:					strbuilder << "X";	break;
	case type_bool:					strbuilder << "_N";	break;
	case type_char:					strbuilder << 'D';	break;
	case type_signed_char:			strbuilder << 'C';	break;
	case type_unsigned_char:			strbuilder << 'E';	break;

	case type_wchar_t:				strbuilder << "_W";	break;

	case type_short:					strbuilder << 'F';	break;
	case type_unsigned_short:		strbuilder << 'G';	break;
	case type_int:					strbuilder << 'H';	break;
	case type_unsigned_int:			strbuilder << 'I';	break;
	case type_long:					strbuilder << 'J';	break;
	case type_unsigned_long:			strbuilder << 'K';	break;

	case type_float:					strbuilder << 'M';	break;
	case type_double:				strbuilder << 'N';	break;

	case type_long_double:			strbuilder << 'O';	break;

		/*
	case type_int8:					strbuilder << "_D";	break;
	case type_unsigned_int8:			strbuilder << "_E";	break;
	case type_int16:					strbuilder << "_F";	break;
	case type_unsigned_int16:		strbuilder << "_G";	break;
	case type_int32:					strbuilder << "_H";	break;
	case type_unsigned_int32:		strbuilder << "_I";	break;
	*/
	case type_long_long:				strbuilder << "_J";	break;
	case type_unsigned_long_long:	strbuilder << "_K";	break;
		/*
	case type_int128:				strbuilder << "_L";	break;
	case type_unsigned_int128:		strbuilder << "_M";	break;
	*/

	default:
		{
			VERIFY(0);
		}
	}

	return strbuilder;
}

LFCEXT IO::TextWriter& VCMangler::MangleFunctionParameters(FunctionType* pFun, IO::TextWriter& strbuilder)
{
	if (pFun->m_parameters.m_parameters.size())
	{
	//	map<Type*, int> argTypes;

		for (uint i = 0; i < pFun->m_parameters.m_parameters.size(); ++i)
		{
			Type* pArgType = pFun->m_parameters.m_parameters[i].m_pType->GetStripped();
			if (pArgType == NULL)
			{
				break;	// hmm..
			}

			Type_type type = pArgType->get_Kind();

			bool bShort =
				(type ==	type_void) ||
				(type ==	type_char) ||
				(type ==	type_signed_char) ||
				(type ==	type_unsigned_char) ||
				(type ==	type_short) ||
				(type ==	type_unsigned_short) ||
				(type ==	type_int) ||
				(type ==	type_unsigned_int) ||
				(type ==	type_long) ||
				(type ==	type_unsigned_long) ||
				(type ==	type_float) ||
				(type ==	type_double);

				/*
	case type_void:					strbuilder << "X";	break;
	case type_bool:					strbuilder << "_N";	break;
	case type_char:					strbuilder << 'D';	break;
	case type_signed_char:			strbuilder << 'C';	break;
	case type_unsigned_char:		strbuilder << 'E';	break;

	case type_wchar:					strbuilder << "_W";	break;
// VC 6.0
//	case type_wchar:					strbuilder << "G";	break;	// unsigned short

	case type_short_int:				strbuilder << 'F';	break;
	case type_unsigned_short_int:	strbuilder << 'G';	break;
	case type_int:						strbuilder << 'H';	break;
	case type_unsigned_int:			strbuilder << 'I';	break;
	case type_long_int:				strbuilder << 'J';	break;
	case type_unsigned_long_int:	strbuilder << 'K';	break;
	case type_long_long:				strbuilder << "_J";	break;
	case type_unsigned_long_long:	strbuilder << "_K";	break;
	case type_float:					strbuilder << 'M';	break;
	case type_double:					strbuilder << 'N';	break;
	*/

			map<Type*, int>::iterator it;

			if (!bShort &&
				(it = argTypes.find(pFun->m_parameters.m_parameters[i].m_pType)) != argTypes.end())
			{
				strbuilder << it->second;
			}
			else
			{
				MangleType(pFun->m_parameters.m_parameters[i].m_pType, strbuilder);
				if (!bShort)
				{
					argTypes.insert(map<Type*, int>::value_type(pFun->m_parameters.m_parameters[i].m_pType, argTypes.size()));
				}
			}
		}

		if (pFun->m_parameters.m_bVarArg)
		{
			// elipsis        Z (terminates argument list)
			strbuilder << "Z";
		}
		else
		{
			strbuilder << "@";
		}
	}
	else
	{
		strbuilder << "X";
	}

	return strbuilder;
}

// static
LFCEXT String VCMangler::MangleNameVC(ClassType* pClass, Declarator* decl, IO::TextWriter& strbuilder)
{
	VCMangler mangler;

	if (decl->m_pType->get_Kind() == type_function)
	{
		FunctionType* pFun = decl->m_pType->AsFunction();

		if (!decl->m_cpp_linkage)	// C linkage
		{
			strbuilder << '_';

			strbuilder << decl->m_name;

			if (pFun->m_funcspec == CallType_stdcall)
			{
				strbuilder << "@";
				strbuilder << pFun->GetStackSize(CallType_stdcall);
			}

			return strbuilder.ToString();
		}

		strbuilder << "?";


	// thiscall:
	//	?methodName @ className @@AAE retType param-list Z

	/*
	myclass::myclass          ?0
	myclass::~myclass         ?1
	myclass::operator new     ?2
	myclass::operator delete  ?3
	myclass::operator=        ?4
	myclass::operator+        ?H
	myclass::operator++       ?E

	*/

		int special = 0;
		if (pClass && decl->m_name == pClass->m_name)	// constructor
		{
			strbuilder << "?0";
			special = 1;
		}
		else if (pClass && decl->m_name.At(0) == '~')	// destructor
		{
			strbuilder << "?1";
			special = 1;
		}
		// TODO
		else if (pClass && decl->m_name == "operator new")	// operator new
		{
			strbuilder << "?2";
		}
		else if (pClass && decl->m_name == "operator_delete")	// operator delete
		{
			strbuilder << "?3";
		}
		else if (pClass && decl->m_name == "operator new[]")	// operator new[]
		{
			strbuilder << "?_U";
		}
		else if (pClass && decl->m_name == "operator_delete[]")	// operator delete[]
		{
			strbuilder << "?_V";
		}

		else if (decl->m_name == "operator=")
		{
			strbuilder << "?4";
		}
		else if (decl->m_name == "operator>>")
		{
			strbuilder << "?5";
		}
		else if (decl->m_name == "operator<<")
		{
			strbuilder << "?6";
		}
		else if (decl->m_name == "operator!")
		{
			strbuilder << "?7";
		}
		else if (decl->m_name == "operator==")
		{
			strbuilder << "?8";
		}
		else if (decl->m_name == "operator!=")
		{
			strbuilder << "?9";
		}
		else if (decl->m_name == "operator[]")
		{
			strbuilder << "?A";
		}
		else if (decl->m_name == "operator conversion")
		{
			strbuilder << "?B";
		}
		else if (decl->m_name == "operator->")
		{
			strbuilder << "?C";
		}
		else if (decl->m_name == "operator*")
		{
			strbuilder << "?D";
		}
		else if (decl->m_name == "operator++")
		{
			strbuilder << "?E";
		}
		else if (decl->m_name == "operator--")
		{
			strbuilder << "?F";
		}
		else if (decl->m_name == "operator-")
		{
			strbuilder << "?G";
		}
		else if (decl->m_name == "operator+")
		{
			strbuilder << "?H";
		}
		else if (decl->m_name == "operator&")
		{
			strbuilder << "?I";
		}
		else if (decl->m_name == "operator->*")
		{
			strbuilder << "?J";
		}
		else if (decl->m_name == "operator/")
		{
			strbuilder << "?K";
		}
		else if (decl->m_name == "operator%")
		{
			strbuilder << "?L";
		}
		else if (decl->m_name == "operator<")
		{
			strbuilder << "?M";
		}
		else if (decl->m_name == "operator<=")
		{
			strbuilder << "?N";
		}
		else if (decl->m_name == "operator>")
		{
			strbuilder << "?O";
		}
		else if (decl->m_name == "operator>=")
		{
			strbuilder << "?P";
		}
		else if (decl->m_name == "operator,")
		{
			strbuilder << "?Q";
		}
		else if (decl->m_name == "operator()")
		{
			strbuilder << "?R";
		}
		else if (decl->m_name == "operator~")
		{
			strbuilder << "?S";
		}
		else if (decl->m_name == "operator^")
		{
			strbuilder << "?T";
		}
		else if (decl->m_name == "operator|")
		{
			strbuilder << "?U";
		}
		else if (decl->m_name == "operator&&")
		{
			strbuilder << "?V";
		}
		else if (decl->m_name == "operator||")
		{
			strbuilder << "?W";
		}
		else if (decl->m_name == "operator*=")
		{
			strbuilder << "?X";
		}
		else if (decl->m_name == "operator+=")
		{
			strbuilder << "?Y";
		}
		else if (decl->m_name == "operator-=")
		{
			strbuilder << "?Z";
		}
		else if (decl->m_name == "operator/=")
		{
			strbuilder << "?_0";
		}
		else if (decl->m_name == "operator%=")
		{
			strbuilder << "?_1";
		}
		else if (decl->m_name == "operator>>=")
		{
			strbuilder << "?_2";
		}
		else if (decl->m_name == "operator<<=")
		{
			strbuilder << "?_3";
		}
		else if (decl->m_name == "operator&=")
		{
			strbuilder << "?_4";
		}
		else if (decl->m_name == "operator|=")
		{
			strbuilder << "?_5";
		}
		else if (decl->m_name == "operator^=")
		{
			strbuilder << "?_6";
		}
		else
		{
		//	special = 0;

			strbuilder << decl->m_name;
			strbuilder << "@";

			++mangler.m_n;	// TODO
		}

		if (pClass)
	//	if (decl->m_pOwnerScope)
		{
			mangler.MangleNameName(pClass->m_pScope, strbuilder);
		}

		strbuilder << "@";

		if (decl->get_IsStatic())
		{
			switch (decl->m_access)
			{
			case AccessSpec_Private:
				strbuilder << "C";
				break;

			case AccessSpec_Protected:
				strbuilder << "K";
				break;

			case AccessSpec_Public:
				strbuilder << "S";
				break;

			default:
				ASSERT(0);
			}

			strbuilder << "A";	// ??

#if 0
		if (pFun->m_funcspec == 4)	// thiscall
			strbuilder << "E";
		else if (pFun->m_funcspec == 1)	// cdecl
			strbuilder << "Y";
		else if (pFun->m_funcspec == 2)	// stdcall
			strbuilder << "G";
		else if (pFun->m_funcspec == 3)	// fastcall
			strbuilder << "F";
		else if (pFun->m_funcspec == 0)
			;//ASSERT(0);
		else
			ASSERT(0);
#endif
		}
		else if (decl->m_virtual)
		{
			switch (decl->m_access)
			{
				case AccessSpec_Private:
					strbuilder << "E";
					break;

				case AccessSpec_Protected:
					strbuilder << "M";
					break;

				case AccessSpec_Public:
					strbuilder << "U";
					break;

				default:
					ASSERT(0);
			}

			// ?????

			if (pFun->m_bConst)
				strbuilder << "B";
			else
				strbuilder << "A";

			if (pFun->m_funcspec == CallType_thiscall)
				strbuilder << "E";
			else if (pFun->m_funcspec == CallType_cdecl)
				strbuilder << "Y";
			else if (pFun->m_funcspec == CallType_stdcall)
				strbuilder << "G";
			else if (pFun->m_funcspec == CallType_fastcall)
				strbuilder << "F";
			else
				VERIFY(0);
		}
		else
		{
			switch (decl->m_access)
			{
				case AccessSpec_Private:
					strbuilder << "A";
					break;

				case AccessSpec_Protected:
					strbuilder << "I";
					break;

				case AccessSpec_Public:
					strbuilder << "Q";
					break;

				default:
					ASSERT(0);
					raise(Exception("Unspecifed AccessSpec"));
			}

			if (m_x64)
			{
				strbuilder << "E";
				strbuilder << "A";
				strbuilder << "A";
			}
			else
			{
				if (pFun->m_bConst)
					strbuilder << "B";
				else
					strbuilder << "A";

				if (pFun->m_funcspec == CallType_thiscall)
					strbuilder << "E";
				else if (pFun->m_funcspec == CallType_cdecl)
					strbuilder << "Y";
				else if (pFun->m_funcspec == CallType_stdcall)
					strbuilder << "G";
				else if (pFun->m_funcspec == CallType_fastcall)
					strbuilder << "I";
				else
					VERIFY(0);
			}
		}

	//	strbuilder << "@@AAE";

		// TODO
		if (special)
		{
#if 0
			if (decl->m_name == "operator=")
			{
				Type* pReturnType = pFun->m_pReturnType->GetStripped();
				if (pReturnType)
				{
					// TODO; I don't understand this
					if (pReturnType->get_Kind() == type_class ||
						pReturnType->get_Kind() == type_enum)
					{
						strbuilder << "?A";	// Anonymous namespace ?
					}

					mangler.MangleType(pFun->m_pReturnType, strbuilder);
				}
				else
				{
					// could be a destructor

					strbuilder << "X";	// void
				}

			}
			else
#endif
			strbuilder << "@";
		}
		else
		{
			// TODO, typedefs sometimes point to NULL

			Type* pReturnType = pFun->m_pReturnType->GetStripped();
			if (pReturnType)
			{
				// TODO; I don't understand this
				if (pReturnType->get_Kind() == type_class ||
					pReturnType->get_Kind() == type_enum)
				{
					strbuilder << "?A";	// Anonymous namespace ?
				}

				mangler.MangleType(pFun->m_pReturnType, strbuilder);
			}
			else
			{
				// could be a destructor

				strbuilder << "X";	// void
			}
		/*	else
			{
				strbuilder << "@";
			}
			*/
		}

		mangler.MangleFunctionParameters(pFun, strbuilder);

		strbuilder << "Z";
	}
	else	// not a function
	{
		strbuilder << "?";

		strbuilder << decl->m_name;
		strbuilder << "@";

		mangler.m_n++;	// TODO

		mangler.MangleNameName(pClass->m_pScope, strbuilder);

		strbuilder << "@";

		if (decl->get_IsStatic())
		{
			switch (decl->m_access)
			{
			case AccessSpec_Private:
				strbuilder << "0";
				break;

			case AccessSpec_Protected:
				strbuilder << "1";
				break;

			case AccessSpec_Public:
				strbuilder << "2";
				break;

			default:
				ASSERT(0);
			}
		}
		else
		{
			raise(Exception("TODO"));
		}

		mangler.MangleType(decl->m_pType, strbuilder);

		strbuilder << "A";	// storage class
	}

	return strbuilder.ToString();
}

// static
LFCEXT String VCMangler::MangleNameVC(Scope* pScope, Declarator* decl, IO::TextWriter& strbuilder)
{
	VCMangler mangler;

	if (decl->m_pType->get_Kind() == type_function)
	{
		FunctionType* pFun = decl->m_pType->AsFunction();
	// thiscall:
	//	?methodName @ className @@AAE retType param-list Z

		if (!decl->m_cpp_linkage)	// C linkage
		{
			strbuilder << '_';

			strbuilder << decl->m_name;

			if (pFun->m_funcspec == CallType_stdcall)
			{
				strbuilder << "@";
				strbuilder << pFun->GetStackSize(CallType_stdcall);
			}

			return strbuilder.ToString();
		}

		strbuilder << "?";

	/*
	myclass::myclass          ?0
	myclass::~myclass         ?1
	myclass::operator new     ?2
	myclass::operator delete  ?3
	myclass::operator=        ?4
	myclass::operator+        ?H
	myclass::operator++       ?E

	*/

#if 0
		if (pClass && decl->m_name == pClass->m_name)	// constructor
		{
			strbuilder << "?0";

		}
		else if (decl->m_name == "operator=")
		{
			strbuilder << "?4";
		}
		else
#endif
		{
			strbuilder << decl->m_name;
			strbuilder << "@";

			mangler.m_n++;	// TODO
		}

		if (pScope)
		{
			mangler.MangleNameName(pScope, strbuilder);
		}

		strbuilder << "@";

		/*
		if (decl->get_IsStatic())
		{
			strbuilder << "K";
		}
		else
		{
			strbuilder << "Q";

			if (pFun->m_bConst)
				strbuilder << "B";
			else
				strbuilder << "A";
		}
		*/

		if (m_x64)
		{
			strbuilder << "Y";
		}
		else
		{
			if (pFun->m_funcspec == CallType_thiscall)
				strbuilder << "E";
			else if (pFun->m_funcspec == CallType_cdecl)
				strbuilder << "Y";
			else if (pFun->m_funcspec == CallType_stdcall)
				strbuilder << "G";
			else if (pFun->m_funcspec == CallType_fastcall)
				strbuilder << "I";
		//	else if (pFun->m_funcspec == 0)	// TODO, shouldn't happen
		//		strbuilder << "Y";	// cdecl
			else
				ASSERT(0);
		}

		if (pFun->m_bConst)
			strbuilder << "B";
		else
			strbuilder << "A";

	//	strbuilder << "@@AAE";

#if 0
		// TODO
		if (pClass && decl->m_name == pClass->m_name)	// constructor
		{
			strbuilder << "@";
		}
		else
#endif
		{
			//ASSERT(pFun->m_pReturnType);

			if (pFun->m_pReturnType)
			{
				Type* pReturnType = pFun->m_pReturnType->GetStripped();
				// TODO; I don't understand this
				if (pReturnType->get_Kind() == type_class)
				{
					strbuilder << "?A";	// Anonymous namespace ?
				}

				mangler.MangleType(pReturnType, strbuilder);
			}
			else
			{
				// could be a destructor

				strbuilder << "X";	// void
			}
		/*	else
			{
				strbuilder << "@";
			}
			*/
		}

		mangler.MangleFunctionParameters(pFun, strbuilder);

		strbuilder << "Z";
	}
	else
	{
		strbuilder << "?";

		strbuilder << decl->m_name;
		strbuilder << "@";

		mangler.m_n++;	// TODO

		mangler.MangleNameName(pScope, strbuilder);

		strbuilder << "@";

		if (decl->get_IsStatic())
		{
			switch (decl->get_Access())
			{
			case AccessSpec_Private:
				strbuilder << "0";
				break;

			case AccessSpec_Protected:
				strbuilder << "1";
				break;

			case AccessSpec_Public:
				strbuilder << "2";
				break;

			default:
				ASSERT(0);
			}
		}
		else
		{
			ASSERT(0);
		}

		mangler.MangleType(decl->m_pType, strbuilder);

		strbuilder << "A";	// storage class
	}

	return strbuilder.ToString();
}

//////////// Demangler

NamedType* DemangleNameVC_Type2(Namespace* pGlobalNamespace, const char* &p)
{
	String name;

	while (*p && *p != '@')
	{
		name += *p++;
	}
	if (*p != '@')
	{
		raise(Exception("expected '@'"));
	}
	++p;

	if (*p != '@')
	{
		NamespaceType* pType2 = dynamic_cast<NamespaceType*>(DemangleNameVC_Type2(pGlobalNamespace, p));
		if (pType2 == nullptr) return nullptr;

		return pType2->m_pScope->m_types[name];
	}
	++p;

	return pGlobalNamespace->m_pScope->m_types[name];
}

Type* DemangleNameVC_Type(Namespace* pGlobalNamespace, bool x64, const char* &p)
{
	if (*p == 'Y')
	{
		p++;
		return Types::get_nullType();
	}
	else if (*p == 'X')
	{
		p++;
		return Types::get_void();
	}
	else if (p[0] == '_' && p[1] == 'N')
	{
		p += 2;
		return Types::get_bool();
	}
	else if (*p == 'D')
	{
		p++;
		return Types::get_char();
	}
	else if (*p == 'C')
	{
		p++;
		return Types::get_signed_char();
	}
	else if (*p == 'E')
	{
		p++;
		return Types::get_unsigned_char();
	}
	else if (p[0] == '_' && p[1] == 'W')
	{
		p += 2;
		return Types::get_wchar();
	}
	else if (*p == 'F')
	{
		p++;
		return Types::get_short();
	}
	else if (*p == 'G')
	{
		p++;
		return Types::get_unsigned_short();
	}
	else if (*p == 'H')
	{
		p++;
		return Types::get_int();
	}
	else if (*p == 'I')
	{
		p++;
		return Types::get_unsigned_int();
	}
	else if (*p == 'J')
	{
		p++;
		return Types::get_long();
	}
	else if (*p == 'K')
	{
		p++;
		return Types::get_unsigned_long();
	}
	else if (p[0] == '_' && p[1] == 'J')
	{
		p += 2;
		return Types::get_long_long();
	}
	else if (p[0] == '_' && p[1] == 'K')
	{
		p += 2;
		return Types::get_unsigned_long_long();
	}
	else if (*p == 'M')
	{
		p++;
		return Types::get_float();
	}
	else if (*p == 'N')
	{
		p++;
		return Types::get_double();
	}
	else if (*p == 'O')
	{
		p++;
		return Types::get_long_double();
	}
	else
	{
		/*if (*p == '?')
		{
		}
		*/
		if (*p == 'P')
		{
			p++;

			if (x64)
			{
				ASSERT(*p == 'E');
				++p;
			}

			ASSERT(*p == 'A');	// normal storage
			++p;

			Type* pType = DemangleNameVC_Type(pGlobalNamespace, x64, p);
			if (pType == nullptr) return nullptr;

			return pType->get_pointerToThis();
		}
		else if (*p == 'A')
		{
			p++;

			ASSERT(*p == 'A');
			p++;

			Type* pType = DemangleNameVC_Type(pGlobalNamespace, x64, p);
			if (pType == nullptr) return nullptr;

			return pType->get_referenceToThis();
		}
		else if (p[0] == '$' && p[1] == '$' && p[2] == 'Q')
		{
			++p;

			ASSERT(*p == 'A');
			++p;

			Type* pType = DemangleNameVC_Type(pGlobalNamespace, x64, p);
			if (pType == nullptr) return nullptr;

			return pType->get_rvalueReferenceToThis();
		}
		else if (*p == 'V' || *p == 'U' || *p == 'T')
		{
			++p;
			if (isdigit(*p)) return nullptr;

			if (*p == '?')
			{
				++p;
				if (*p != '$')
				{
					raise(Exception("error"));
				}

				++p;

				String name;
				while (*p && *p != '@')
				{
					name += *p++;
				}
				if (*p != '@')
				{
					raise(Exception("eoi - expected '@'"));
				}
				++p;

				ActualTemplateArgs* params = new ActualTemplateArgs;

				String params_str;
				while (*p != '@')
				{
					Type* paramType = DemangleNameVC_Type(pGlobalNamespace, x64, p);
					if (paramType == nullptr) return nullptr;

					ActualTemplateArg* arg = new ActualTemplateArg;
					arg->m_pType = paramType;
					params->Add(arg);

					if (params_str.GetLength()) params_str += ",";
					params_str += paramType->ToString();
				}

				if (*p != '@')
				{
					// error
					return nullptr;
				}
				++p;

				NamespaceType* pType1 = dynamic_cast<NamespaceType*>(DemangleNameVC_Type2(pGlobalNamespace, p));
				if (pType1 == nullptr) return nullptr;

				if (NamedType* pType2 = TypeDatabase::pD->LookupNamedType(pType1->ToString() + "::" + name + "<" + params_str + ">"))
				{
					return pType2;
				}

				ClassType* pTemplateClass = pType1->m_pScope->m_types.find(name)->second->AsClass();
				if (pTemplateClass == nullptr)
				{
					return nullptr;
				}

				if (pTemplateClass->m_pTemplateParams == nullptr)
				{
					raise(Exception(pTemplateClass->get_QName() + " is not a template class"));
				}

				return pTemplateClass->InstantiateTemplate(params);
#if 0
				cpp::TemplateArgs args;
				args.

				CGlobal* pGlobal = nullptr;
				ClassType* p = newInstantiateTemplate(nullptr, pGlobal, pTemplateClass, const TemplateArgs* pParams, int levels)

#endif
			}
			/*
			// TODO: with the '?
			else if (p[0] == '?' && p[1] == 'W' && p[2] == '4')
			{
				p += 3;

				NamedType* pNamedType = DemangleNameVC_Type2(pGlobalNamespace, p);
				if (pNamedType == NULL) return NULL;

				return pNamedType;
			}
			*/
			else
			{
				NamedType* pNamedType = DemangleNameVC_Type2(pGlobalNamespace, p);
				if (pNamedType == nullptr) return nullptr;

				return pNamedType;
			}
			++p;
		}

		return nullptr;
	}

	return nullptr;
}

LFCEXT Type* DemangleNameVC(Namespace* pGlobalNamespace, bool x64, const char* str)
{
	return DemangleNameVC_Type(pGlobalNamespace, x64, str);
}

/*
Type* DemangleNameVC_Type(Namespace* pGlobalNamespace, StringIn str)
{
	return DemangleNameVC_Type(pGlobalNamespace, str.c_str());
}
*/

/*
const Type_Info& t = typeid(test::M::someclass<float>*);
const Type_Info& t2 = typeid(test::someclass<float, float>*);
*/

}	// System
