#include "stdafx.h"
#include "CodeComp.h"

#include "java_parse.h"
#include "java_translate.h"
#include "codegen_java.h"
#include "preprocessor.h"

#include "LFC/VCMapFileParser.h"
#include "LFC/VCMangler.h"

namespace System
{

CodeCompExt int MakeTypes(StringIn argv1, StringIn argv2)
{
	cpp::Options options;
	options.m_x64 = argv2.Find("x64") != String::npos;
	options.m_exeType = 2;	// Win32
	options.m_defines = "WIN32;UNICODE;_FORCENAMELESSUNION";

//	options.m_includeDirs = "D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\include\\;";
	//						"D:\\Users\\Sigurd\\Documents\\VSProjects\\FirstProject2\\include2\\;";

	options.m_includeDirs = "..\\..\\..\\include\\;"
							"..\\..\\..\\include2\\;"
							"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.0\\Include\\";

	cpp::CGlobal* pGlobal = new cpp::CGlobal;
	pGlobal->m_options = &options;
	pGlobal->m_typestuff = new TypeStuff;
	pGlobal->m_typelib = new TypeLib;
	pGlobal->m_typelib->m_typeinfo_filename = FilePath(argv2).get_Name();

	Std::get_Out() << "Opening file " << argv1 << "\n";
	int error = cpp::cpp_compile(pGlobal, argv1, argv2, &options);
	if (error != 0)
	{
		return -1;
	}

	Std::get_Out() << "ntypes " << pGlobal->m_alltypes.size() << "\n";

//	char typeinfofilename[256];
//	strcpy_s(typeinfofilename, argv2);
//	strcpy(typeinfofilename, argv[3]);
//	strcat(typeinfofilename, ".typeinfo");

//	String arfilename = string_copy(argv2);
	IO::FileStream file(argv2, IO::FileMode_Create, IO::FileAccess_Write);
	{
	/*
	if (!file.IsHandleValid())
	{
	//	Std::Out << "Failed to open file (code:" << file->GetLastStatus() << ")" << arfilename << "\n";
		Std::Out << "Failed to open file " << argv2 << "\n";
		return 1;
	}
	*/
	TypeArchive ar(TypeArchive::Mode_Store, &file, argv2);

	ar.m_typestuff = pGlobal->m_typestuff;
	ar.m_typelib = pGlobal->m_typelib;

	ar.WriteHeader();

	ar.MapObject(pGlobal->m_typelib);

	ar << pGlobal->m_typelib->m_typeinfo_filename;

#if 0
	{
		map<StringA*, Type*, Ref_Less<StringA> > types;

		for (int i = 0; i < pGlobal->m_alltypes.GetSize(); i++)
		{
			NamedType* pType = pGlobal->m_alltypes[i];

			BufferImp<char> buffer;
			StringBuilderA strbuilder = StringBuilderA(&buffer);
			strbuilder << "??_R0?A";	// `RTTI Type Descriptor'

			VCMangler mangler;
			mangler.m_n++;

			mangler.MangleType(pType, strbuilder);
			strbuilder << "@8";

			StringA* name = buffer.DetachToString();

			types.insert(map<StringA*, Type*, Ref_Less<StringA> >::value_type(name, pType));
		}
	}


	{
		map<StringA*, ULONG_PTR, Ref_Less<StringA>/*, __gc_allocator*/>::iterator it = mapreceiver.m_symbols.begin();
		while (it != mapreceiver.m_symbols.end())
		{
			if (strncmp((*it).first->c_str(), "??_R0?A", 7) == 0)
			{
				ULONG_PTR typedesc_address = (*it).second - mapreceiver.m_load_address;
			}

			++it;
		}
	}
#endif

	ar << pGlobal->m_typestuff->m_typelibs.size();
	for (auto it = pGlobal->m_typestuff->m_typelibs.begin(); it != pGlobal->m_typestuff->m_typelibs.end(); ++it)
	{
		ASSERT(*(*it).second->m_typeinfo_filename != *ar.m_typelib->m_typeinfo_filename);

		ar.MapObject((*it).second);
		ar << it->second->m_typeinfo_filename;
	}

	ar << pGlobal->m_files.size();
	for (auto it = pGlobal->m_files.begin(); it != pGlobal->m_files.end(); ++it)
	{
		ar.MapObject(it->second);
		ar << it->second->m_name;
		if (it->second->m_parent)
			ar << it->second->m_parent->m_fullname;
		else
			ar << String(nullptr);
	}

	ar << pGlobal->m_sourceFiles.size();
	for (auto it = pGlobal->m_sourceFiles.begin(); it != pGlobal->m_sourceFiles.end(); ++it)
	{
		ar.MapObject(it->second);
		ar << it->second->m_filepart;
		/*
		Store(ar, it->second);
		*/
	}

	ar << pGlobal->m_namespace;

	ar << pGlobal->m_alltypes.GetSize();

	for (NamedType** it = pGlobal->m_alltypes.begin(); it != pGlobal->m_alltypes.end(); ++it)
	{
		NamedType* pType = *it;
		VERIFY((*it)->m_typelib == ar.m_typelib);
		ar << (*it);
	}

	uint count = 0;
	for (Declarator** decl_it = pGlobal->m_globals.begin(); decl_it != pGlobal->m_globals.end(); ++decl_it)
	{
		if ((*decl_it)->m_pType->get_Kind() == type_function)
		{
			++count;
		}
	}

	ar << count;
	for (Declarator** decl_it = pGlobal->m_globals.begin(); decl_it != pGlobal->m_globals.end(); ++decl_it)
	{
		if ((*decl_it)->m_pType->get_Kind() == type_function)
		{
			ar << (*decl_it);
		}
	}

#if 0
	for (int i = 0; i < pGlobal->m_alltypes.GetSize(); i++)
	{
		NamedType* pType = pGlobal->m_alltypes[i];

		BufferImp<char> buffer;
		StringBuilderA strbuilder = StringBuilderA(&buffer);
		strbuilder << "??_R0?A";	// `RTTI Type Descriptor'

		VCMangler mangler;
		mangler.m_n++;

		mangler.MangleType(pType, strbuilder);
		strbuilder << "@8";

		StringA* name = buffer.DetachToString();

//		TRACE("%s", pType->get_QName()->c_str());

		if (pType->get_Kind() != type_typedef)
		{	// +	m_str	0x12913da8 "??_R0?AV?$red_black_node@PAV?$StringT@GV__gc_allocator@System@@@System@@PAVFontFamilyStyles@LDraw@1@@System@@@8"
			map<StringA*, ULONG_PTR, Ref_Less<StringA>/*, __gc_allocator*/>::iterator it2 = mapreceiver.m_symbols.find(name);
			if (it2 != mapreceiver.m_symbols.end())
			{
				printf("%s\n", pType->m_qname->c_str());

				ULONG_PTR typedesc_address = (*it2).second - mapreceiver.m_load_address;

				ar << typedesc_address;
			}
			else
			{
				ar << (ULONG_PTR)0;
			}
		}
		else
		{
			ar << (ULONG_PTR)0;
		}
	}
#endif

	{
		int indefines = 0;
		ar << indefines;
	}

	{
		ar << (uint32)pGlobal->m_PP->m_defines.size();

		PP::macromap::iterator it = pGlobal->m_PP->m_defines.begin();

		while (it != pGlobal->m_PP->m_defines.end())
		{
			ar << (*it).second;

			++it;
		}
	}

	ar << ar.m_crc;

	file.Seek(4, IO::STREAM_SEEK_SET);
	ar << (uint32)ar.m_typeSave.size();
	ar << (uint32)ar.m_stringSave.size();
	ar << (uint32)ar.m_declSave.size();
//	file->Close();
	}

	return 0;
}

}	// System
