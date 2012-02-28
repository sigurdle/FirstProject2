#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

NamedType::NamedType()
{
	m_ownerScope = NULL;
	m_typelib = NULL;
}

NamedType::NamedType(StringIn name) : m_name(name)
{
}

bool NamedType::IsConst() const
{
	return false;
}

bool NamedType::IsVolatile() const
{
	return false;
}

bool NamedType::Equals(const Object* other) const
{
// TODO: Better explain
// hm... We depend on that there is only one type with one name
// because of hash...

	if (this == other) return true;

	return false;
}

NamespaceType* NamedType::get_ParentNamespace()
{
	if (m_ownerScope)
		return m_ownerScope->m_pNamespace;
	else
		return NULL;
}

String NamedType::get_Name() const
{
	return m_name;
}

String NamedType::get_QName() const
{
	return m_qname;
}

// static
NamedType* NamedType::CreateFromArchive(TypeArchive& ar, uint32 id, TypeLib* typelib, StringIn qname)
{
	//ASSERT(typelib->m_loaded);
	/*
	if (!typelib->m_loaded)
	{
		typelib->m_loaded = true;

		char fullname[260];

		_makepath(fullname, "C:", "\\mmstudio\\Win32\\bin\\debug", typelib->m_typeinfo_filename->c_str(), "typeinfo");

		IO::FileByteStream file(new StringA(fullname), IO::FileMode_Read);
		TypeArchive ar2(TypeArchive::Mode_Load, &file);
		ar2.m_pGlobalNamespace = ar.m_pGlobalNamespace;
		ar2.m_bSortedDecls = ar.m_bSortedDecls;
		ar2.m_typestuff = ar.m_typestuff;

		ar2 >> ar2.m_typelib;

		uint ntypelibs;
		ar2 >> ntypelibs;
		for (uint i = 0; i < ntypelibs; i++)
		{
			TypeLib* typelib;
			ar2 >> typelib;
		}

		Namespace* pNamespace;
		ar2 >> pNamespace;

		uint ntypes;
		ar2 >> ntypes;

		for (i = 0; i < ntypes; i++)
		{
			NamedType* type;
			ar2 >> type;

			typelib->m_alltypes.insert(map<StringA*, NamedType*, Ref_Less<StringA> >::value_type(type->m_qname, type));
		}
	}
	*/

//	map<StringA*, NamedType*, Ref_Less<StringA> >::iterator it = typelib->m_typesByName.find(qname);

	NamedType* pobj = typelib->FindNamedType(qname);
	if (pobj == NULL)
	{
		/*
		char buffer[1024];
		sprintf_s(buffer, "'%S' imports '%S', but couldn't find type '%s'\n", ar.m_typelib->m_typeinfo_filename->c_str(), typelib->m_typeinfo_filename->c_str(), qname->c_str());
	//	throw std::exception(buffer);
		printf(buffer);
		*/

		DebugTrace(__FILE__ <<  paren(__LINE__) << " : TODO; FIX BUG HERE\n");

	//	ASSERT(0);
		ar.m_typeLoad.push_back(NULL);

		return NULL;
	}
	else
	{

	//	ar.m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pobj));
		if (ar.m_typeLoad.size() < id+1) ar.m_typeLoad.resize(id+1);
		ar.m_typeLoad[id] = pobj;
	//	ASSERT(ar.m_typeLoad.size() == id);

		return pobj;
	}
}

void NamedType::Load(TypeArchive& ar)
{
//	ar >> m_typelib;

	ar >> m_sourcefile;
	if (m_sourcefile)
	{
		m_sourcefile_it = m_sourcefile->Add(this);
	}

	m_name = ar.LoadIdentifier();

	/*
	if (*m_name == "Listener")
	{
		MessageBeep(-1);
	}
	*/

	NamespaceType* parent;
	ar >> parent;

	if (parent)
	{
		/*
		if (Namespace* pParentNamespace = dynamic_cast<Namespace*>(parent))
			m_pOwnerScope = pParentNamespace->m_pScope;
		else if (ClassType* pParentClass = dynamic_cast<ClassType*>(parent))
		*/
			m_ownerScope = parent->m_pScope;
		//	VERIFY(m_ownerScope->m_decls.find(m_name) != m_ownerScope->m_decls.end());
	/*	else
			VERIFY(0);
			*/
	}
	else
		m_ownerScope = NULL;
}

/*
LFCEXT void Store(TypeArchive& ar, CppSourceFile* p)
{
	ar << p->m_pathname;
}

LFCEXT void Load(TypeArchive& ar, CppSourceFile* p)
{
	ar >> p->m_pathname;
}
*/

void NamedType::Store(TypeArchive& ar) const
{
//	ar << m_typelib;
	ar << m_sourcefile;

	ar.StoreIdentifier(m_name);

	// _TemplateArgType has scope that doesn't belong to namespacetype

	if (m_ownerScope && m_ownerScope->m_pNamespace)
	{
		ar << m_ownerScope->m_pNamespace;
	}

#if 0
	if (m_ownerScope/* && m_ownerScope->m_pNamespace*/)
	{
		ASSERT(m_ownerScope->m_pNamespace);
		ar << m_ownerScope->m_pNamespace;
	}
#endif
	else
	{
		ar << (TypeSerializable*)NULL;
	}
}

}	// System
