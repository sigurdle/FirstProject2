#include "stdafx.h"
#include "LFC.h"
#include "Type.h"

namespace System
{

TypeLib::TypeLib()
{
	m_id = 0;
	m_typeinfo_filename = nullptr;
}

TypeSerializable::Class_Type TypeLib::GetSerializableType() const
{
	return Class_TypeLib;
}

NamedType* TypeLib::FindNamedType(StringIn qname)
{
	ASSERT(this);

	auto it = m_typesByName.find(qname);
	if (it != m_typesByName.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

void TypeLib::Load(TypeArchive& ar)
{
	ar >> m_typeinfo_filename;

	ASSERT(ar.m_typestuff->m_typelibs.find(m_typeinfo_filename) == ar.m_typestuff->m_typelibs.end());

	ar.m_typestuff->m_typelibs.insert(TypeStuff::typelibs::value_type(m_typeinfo_filename, this));

	uint ntypelibs;
	ar >> ntypelibs;
	for (uint i = 0; i < ntypelibs; ++i)
	{
		String name;
		ar >> name;

		// Check that it's not alreay imported
		// Look in same directory as this typeinfo
		char dirname[260];
		char pathname[260];
		char filename[260];
		char extname[260];
		_splitpath_s(CString(ar.m_pathname).c_str(), dirname, pathname, filename, extname);

//			_makepath(fullname, "C:", "\\mmstudio\\bin\\Win32\\debug", typelib->m_typeinfo_filename->c_str(), "typeinfo");
		char fullpath2[512];
		_makepath_s(fullpath2, dirname, pathname, CString(name).c_str(), "typeinfo");

		char fullpath[512];
		_fullpath(fullpath, fullpath2, 512);

		TypeLib* typelib;

		auto it = ar.m_typestuff->m_typelibs_fullpath.find(fullpath);
		if (it != ar.m_typestuff->m_typelibs_fullpath.end())
		{
			DebugTrace("warning: typelib " << fullpath << " already imported (ignored)\n");
			typelib = it->second;
		}
		else
		{
			typelib = new TypeLib;
			typelib->m_typeinfo_filename = name;

			ar.m_typestuff->m_typelibs_fullpath.insert(TypeStuff::typelibs::value_type(fullpath, typelib));

			String fullnamestr = string_copy(fullpath);
			IO::FileStream file(fullnamestr, IO::FileMode_Open, IO::FileAccess_Read);
			/*
			if (file == null)
			{
				raise(Exception("Failed to load " + fullnamestr));
			}
			*/

			TypeArchive ar2(TypeArchive::Mode_Load, &file, fullnamestr);
			ar2.m_pGlobalNamespace = ar.m_pGlobalNamespace;
			ar2.m_bSortedDecls = ar.m_bSortedDecls;
			ar2.m_typestuff = ar.m_typestuff;

			ar2.m_typelib = typelib;
			ar2.ReadHeader();
			ar2.MapObject(typelib);
			typelib->Load(ar2);
		}
		/*
		else
		{
			typelib = (*it).second;
		}
		*/

		ar.MapObject(typelib);

		m_typelibimports.push_back(typelib);
	}

	uint nfileparts;
	ar >> nfileparts;
	for (uint i = 0; i < nfileparts; ++i)
	{
		String name;
		ar >> name;

		String parentname;
		ar >> parentname;

		String fullname;
		if (parentname.GetLength())
			fullname = parentname + "/" + name;
		else
			fullname = name;

		auto it = ar.m_typestuff->m_files.find(fullname);
		if (it == ar.m_typestuff->m_files.end())
		{
			FilePart* part = new FilePart;
			ar.MapObject(part);
			part->m_name = name;
			part->m_fullname = fullname;

			// Find parent
		//	map<String, FilePart*>::iterator parent_it;
			if (parentname.GetLength())
			{
				auto parent_it = ar.m_typestuff->m_files.find(parentname);
				ASSERT(parent_it != ar.m_typestuff->m_files.end());

				part->m_parent = parent_it->second;
				part->m_parent_it = part->m_parent->m_children.m_list.insert(part->m_parent->m_children.m_list.end(), part);
			}

			ar.m_typestuff->m_files.insert(map<String, FilePart*>::value_type(part->m_fullname, part));
			ar.m_typestuff->m_fileparts.insert(multimap<String, FilePart*>::value_type(part->m_name, part));
		}
		else
		{
			ar.MapObject(it->second);
		}
	}

	uint nsourcefiles;
	ar >> nsourcefiles;
	for (uint i = 0; i < nsourcefiles; ++i)
	{
//		String pathname;
//		ar >> pathname;

		FilePart* filepart;
		ar >> filepart;

		CppSourceFile*& sourcefile = ar.m_typestuff->m_sourcefiles[filepart->m_fullname];
		if (sourcefile == NULL)
		{
			sourcefile = new CppSourceFile;
			sourcefile->m_filepart = filepart;
			ar.MapObject(sourcefile);
		}

//		CppSourceFile*& sourcefile = ar.m_typestuff->m_sourcefiles[pathname];
//		if (sourcefile == NULL)

		/*
		map<String, FilePart*>::iterator it = ar.m_typestuff->m_files.find(parentname);

		CppSourceFile*& sourcefile = ar.m_typestuff->m_sourcefiles[pathname];
		if (sourcefile == NULL)
		{
			sourcefile = new CppSourceFile;
			sourcefile->m_filepart = pathname;
			ar.MapObject(sourcefile);
		}
		*/
	}

	Namespace* pNamespace;
	ar >> pNamespace;

	uint ntypes;
	ar >> ntypes;

	m_types.reserve(ntypes);

	for (uint i = 0; i < ntypes; ++i)
	{
		NamedType* type;
		ar >> type;

		m_types.push_back(type);
		m_typesByName.insert(map<String, NamedType*>::value_type(type->m_qname, type));
	}

	uint nglobals;
	ar >> nglobals;
	m_globals.reserve(nglobals);
	for (uint i = 0; i < nglobals; ++i)
	{
		Declarator* decl;
		ar >> decl;

		m_globals.push_back(decl);
	}
}

void TypeLib::Store(TypeArchive& ar) const
{
	ASSERT(0);
	VERIFY(m_typeinfo_filename);
//	ar << m_id;
	ar << m_typeinfo_filename;
}

}	// System
