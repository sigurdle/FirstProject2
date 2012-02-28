#include "stdafx.h"
#include "LFC.h"

namespace System
{

// static
Namespace* Namespace::CreateFromArchive(TypeArchive& ar, uint32 id)
{
	/*
	Namespace* p = new Namespace;
	if (ar.m_typeLoad.size() <= id) ar.m_typeLoad.resize(id+1);
	ar.m_typeLoad[id] = p;
	p->Load(ar);
	return p;
*/

	TypeLib* typelib;
	ar >> typelib;
	ASSERT(typelib == nullptr);

	CppSourceFile* sourcefile;
	ar >> sourcefile;

	String name = ar.LoadIdentifier();

	size_t tsize = ar.m_typeLoad.size();

	// parent must already have been loaded, or it will screw up m_typeLoad array
	Namespace* parent;
	ar >> parent;

	Namespace* pNamespace = nullptr;

	if (name == nullptr)
	{
		pNamespace = ar.m_pGlobalNamespace;
		ASSERT(parent == nullptr);
	}

	if (parent)
	{
		namespacemap::iterator it = parent->m_pScope->m_namespaces.find(name);
		if (it != parent->m_pScope->m_namespaces.end())
		{
			pNamespace = it->second;
		}
	}

	if (pNamespace == nullptr)
	{
		pNamespace = new Namespace;
		pNamespace->m_name = name;

		ar >> pNamespace->m_sourcefile;
		ASSERT(pNamespace->m_sourcefile == nullptr);

		IO::StringWriter stream;
		pNamespace->Write(stream);
		pNamespace->m_qname = stream.str();

		ASSERT(ar.m_typelib);
		ar.m_typelib->m_namespaces.push_back(pNamespace);

		if (parent)
		{
			pNamespace->m_ownerScope = parent->m_pScope;
			pNamespace->m_pScope->m_pParentScope = parent->m_pScope;

			parent->m_pScope->m_types.insert(map<String,NamedType*>::value_type(name, pNamespace));
			parent->m_pScope->m_namespaces.insert(namespacemap::value_type(name, pNamespace));
		}
	}

//	ar.m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pNamespace));
	ASSERT(ar.m_typeLoad.size() == tsize);
	ar.m_typeLoad.push_back(pNamespace);
	ASSERT(ar.m_typeLoad.size() == id);

	pNamespace->Load2(ar);

	/*
	for (int i = 0; i < n; i++)
	{
		Namespace* p;
		ar >> p;

		pNamespace->m_pScope->
	}
	*/

	/*
	for (int i = 0; i < parent->m_pScope->m_orderedDecls.size(); i++)
	{
		CDeclarator
		if (
	}

		pNamespace = parent->m_pScope->FindNamespaceByName(ar.m_pScope->m_pNamespace, name);
	}
	if (pNamespace == NULL)
		pNamespace = new Namespace;
		*/

	return pNamespace;
	/*
	Namespace* pobj = new Namespace;
	pobj->m_name = name;
	//pobj->m_qname = qname;
//	pobj->Load(ar);
*/
}

// static
Namespace* Namespace::CreateFromArchive(TypeArchive& ar, TypeLib* typelib, StringIn qname, uint32 id)
{
	/*
	Namespace* p = new Namespace;
	if (ar.m_typeLoad.size() <= id) ar.m_typeLoad.resize(id+1);
	ar.m_typeLoad[id] = p;
	p->Load(ar);
	return p;
*/

//	TypeLib* typelib;
//	ar >> typelib;
//	ASSERT(typelib == NULL);

	CppSourceFile* sourcefile;
	ar >> sourcefile;

	String name = ar.LoadIdentifier();

	/*size_t tsize =*/ ar.m_typeLoad.size();

	// parent must already have been loaded, or it will screw up m_typeLoad array
	Namespace* parent;
	ar >> parent;

	Namespace* pNamespace = nullptr;

	if (name == nullptr)
	{
		pNamespace = ar.m_pGlobalNamespace;
		ASSERT(parent == NULL);
	}

	if (parent)
	{
		namespacemap::iterator it = parent->m_pScope->m_namespaces.find(name);
		if (it != parent->m_pScope->m_namespaces.end())
		{
			pNamespace = (*it).second;
		}
	}

	if (pNamespace == nullptr)
	{
		pNamespace = new Namespace;
		pNamespace->m_name = name;

//		ar >> pNamespace->m_sourcefile;
//		ASSERT(pNamespace->m_sourcefile == NULL);

		IO::StringWriter stream;
		pNamespace->Write(stream);
		pNamespace->m_qname = stream.str();

		ASSERT(ar.m_typelib);
		ar.m_typelib->m_namespaces.push_back(pNamespace);

		if (parent)
		{
			pNamespace->m_ownerScope = parent->m_pScope;
			pNamespace->m_pScope->m_pParentScope = parent->m_pScope;

			parent->m_pScope->m_types.insert(map<String,NamedType*>::value_type(name, pNamespace));
			parent->m_pScope->m_namespaces.insert(namespacemap::value_type(name, pNamespace));
		}
	}

	ar.m_typeLoad[id-1] = pNamespace;

	/*
//	ar.m_objectmapLoad.insert(map<uint32, TypeSerializable*>::value_type(id, pNamespace));
	ASSERT(ar.m_typeLoad.size() == tsize);
	ar.m_typeLoad.push_back(pNamespace);
	ASSERT(ar.m_typeLoad.size() == id);
*/

	pNamespace->Load2(ar);

	/*
	for (int i = 0; i < n; i++)
	{
		Namespace* p;
		ar >> p;

		pNamespace->m_pScope->
	}
	*/

	/*
	for (int i = 0; i < parent->m_pScope->m_orderedDecls.size(); i++)
	{
		CDeclarator
		if (
	}

		pNamespace = parent->m_pScope->FindNamespaceByName(ar.m_pScope->m_pNamespace, name);
	}
	if (pNamespace == NULL)
		pNamespace = new Namespace;
		*/

	return pNamespace;
	/*
	Namespace* pobj = new Namespace;
	pobj->m_name = name;
	//pobj->m_qname = qname;
//	pobj->Load(ar);
*/
}

void Namespace::Load2(TypeArchive& ar)
{
	{
		unsigned int ndecls;
		ar >> ndecls;

		if (false)	// ??
			m_pScope->m_orderedDecls.reserve(ndecls);

		bool bMember = get_Kind() == type_class;

		for (unsigned int i = 0; i < ndecls; ++i)
		{
			Declarator* decl = new Declarator;
			ar.MapObject(decl);
			decl->Load(bMember, ar);

			m_pScope->m_decls.insert(declsmap::value_type(decl->m_name, decl));

			if (ar.m_bSortedDecls)
			{
			//	m_pScope->m_decls.insert(declsmap::value_type(decl->m_name, decl));
				if (decl->m_typedef)
				{
					m_pScope->m_types.insert(typemap::value_type(decl->m_name, (NamedType*)decl->m_pType));
				}
			}

			decl->m_pOwnerScope = m_pScope;
			m_pScope->m_orderedDecls.push_back(decl);
		}
	}
}

String Namespace::ToString()
{
	IO::StringWriter strbuilder;
	Write(strbuilder);
	return strbuilder.str();
}

void Namespace::Load(TypeArchive& ar)
{
	NamespaceType::Load(ar);

	Load2(ar);
}

void Namespace::Store(TypeArchive& ar) const
{
	NamespaceType::Store(ar);

	/*
	if (*m_name == "System")
	{
		MessageBeep(-1);
	}
	*/

	{
		ar << m_pScope->m_orderedDecls.GetSize();

		/*
		// constructors first
		{
			for (int i = 0; i < m_pScope->m_orderedDecls.GetSize(); i++)
			{
				if (m_pScope->m_orderedDecls[i]->m_pDeclarator->m_name == m_name)
				{
					m_pScope->m_orderedDecls[i]->m_pDeclarator->Store(ar);
				}
			}
		}
		*/

		{
			bool bMember = get_Kind() == type_class;

			for (unsigned int i = 0; i < m_pScope->m_orderedDecls.GetSize(); i++)
			{
			//	if (m_pScope->m_orderedDecls[i]->m_pDeclarator->m_name != m_name)
				{
					ar.MapObject(m_pScope->m_orderedDecls[i]);
					m_pScope->m_orderedDecls[i]->Store(bMember, ar);
				}
			}
		}
	}

	/*
	{
		ar << (uint32)m_pScope->m_namespaces.size();

		namespacemap::iterator it = m_pScope->m_namespaces.begin();
		while (it != m_pScope->m_namespaces.end())
		{
			ar << (*it).second;

			++it;
		}
	}
	*/
}

}	// System
