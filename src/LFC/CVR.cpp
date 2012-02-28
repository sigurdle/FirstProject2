#include "stdafx.h"
#include "LFC.h"

namespace System
{

ULONG_PTR CVR::LookupSymbol(StringIn name)
{
	multimap<String, ULONG_PTR>::iterator it = m_symbols.find(name);
	if (it != m_symbols.end())
	{
		return (*it).second;
	}
	else
		return 0;
}

Type* CVR::CreatePointerType(Type_type type, Type* pPointerTo)
{
	if (type == type_reference)
	{
		ReferenceType* pType;
		ReferenceTypes::iterator it = m_reference_Types.find(pPointerTo);
		if (it != m_reference_Types.end())
		{
			pType = (*it).second;
		}
		else
		{
			pType = new ReferenceType(pPointerTo);
			m_reference_Types.insert(ReferenceTypes::value_type(pPointerTo, pType));
		}

		return pType;
	}
	else //if (type == type_pointer)
	{
		PointerType* pType;
		PointerTypes::iterator it = m_pointer_Types.find(pPointerTo);
		if (it != m_pointer_Types.end())
		{
			pType = (*it).second;
		}
		else
		{
			pType = new PointerType(pPointerTo);
			m_pointer_Types.insert(PointerTypes::value_type(pPointerTo, pType));
		}

		return pType;
	}
}

String CVR::CreateString(const char* str)
{
	stringmap_t::iterator it = m_strings.find(str);
	if (it != m_strings.end())
	{
		return (*it).second;
	}
	else
	{
		String str2(str);
		m_strings.insert(stringmap_t::value_type(str2, str2));
		return str2;
	}
}

NamedType* CVR::LookupNamedType(StringIn name)
{
	map<String, NamedType*>::iterator it = m_namedTypes.find(name);
	if (it != m_namedTypes.end())
		return (*it).second;
	else
		return NULL;
}

void CVR::OnSymbol(StringIn name, ULONG_PTR address, ULONG_PTR dwData)
{
	/*
	if (strstr(name->c_str(), "type_info"))
	{
		printf("%s %d\n", name->c_str(), address);
	}
	*/

	m_symbols.insert(map<StringIn, ULONG_PTR>::value_type(name, address));
}

void CVR::OnType(StringIn qname, NamedType* type, ULONG_PTR dwData)
{
	ASSERT(type != NULL);
//	type->userdata.dwData = dwData;
	//type->AddRef();
	/*
	if (strstr(qname->c_str(), "StringT<"))
	{
		MessageBeep(-1);
	}
	*/


	/*
	if (*type->m_qname == "rb_tree<System::StringT<char,System::__gc_allocator> *,DebugSymbol *,Ref_Less<System::StringT<char,System::__gc_allocator> >,std_allocator,0>::iterator")
	{
		MessageBeep(-1);
	}
	*/

	ASSERT(m_namedTypes.find(type->m_qname) == m_namedTypes.end());

	m_namedTypes[type->m_qname] = type;
}

/*
void CVR::OnProc(StringA name, Scope* proc, uint32 dwData)
{
	m_procs.insert(multimap<StringA, Scope*>::value_type(name, proc));
}
*/

Scope* CVR::OnProc(Scope* pScope, StringIn name, Type* type, ULONG_PTR startAddress, ULONG_PTR endAddress, ULONG_PTR dwData)
{
	if (type != NULL)
	{
		IO::StringWriter strbuilder;
		strbuilder << name;
		type->Write(strbuilder);

		String str = strbuilder.str();

		if (m_procs.find(str) == m_procs.end())
		{
			m_procs.insert(map<String, ULONG_PTR>::value_type(str, startAddress));
			m_procs2.insert(multimap<String, TypeAddress>::value_type(name, TypeAddress(type, startAddress)));
		}
	}

	return NULL;
}

Scope* CVR::End(Scope* pScope)
{
	return NULL;
}

void CVR::OnData(StringIn name, Type* pType, ULONG_PTR address, ULONG_PTR dwData)
{
	//m_data.insert(map<StringA, DataSymbol*>::value_type(name, data));

	/*
	if (pType)
	{
		StringBuilderA strbuilder;
		pType->Write(strbuilder);

		TRACE("%s\n", strbuilder.DetachToString()->c_str());
	}
	TRACE("%s\n", name->c_str());
	MessageBeep(-1);
	*/
}

}
