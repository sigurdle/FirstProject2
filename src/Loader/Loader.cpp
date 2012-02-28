#include "stdafx.h"

#include <stdlib.h>

#include "../CodeComp/AOut.h"
#include "../Include/AmigaHunkParser.h"
#include "../Include/ArchFile.h"

#include "../CodeComp/CreateObjectFileParser.h"

#if AMIGA
#include "../amiga_header.h"
#endif

#include "../LFC/Linker.h"
#include "../LFC/NameMangler.h"

using namespace System;
using namespace System::IO;

extern "C" int entrypoint_hook(unsigned char* address, char* str, int len);

#pragma comment(lib, "../LFC/Debug/LFC.lib")

char* cmdline = "";

Linker linker;

namespace System
{
	extern LFCEXT Heap* heap;
}

int main(int argc, char* argv[])
{
	printf("main()\n");

#if WIN32
	linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/ncrt0.o"));
	//linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/main.o"));
	linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/OBJ/Browser/Browser.o"));
	linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/OBJ/Browser/BrowserFrame.o"));
	linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/libui.a"));
	linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/libdraw.a"));
	linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/libxmlparse.a"));
	linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/liblfc.a"));
	linker.m_files.push_back(new StringA("C:/cygwin/usr/local/amiga/lib/gcc/m68k-amigaos/3.4.0/libgcc.a"));
	linker.m_files.push_back(new StringA("C:/cygwin/usr/local/amiga/m68k-amigaos/lib/libstdc++.a"));
	linker.m_files.push_back(new StringA("C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libm.a"));
	linker.m_files.push_back(new StringA("C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libnix.a"));
	linker.m_files.push_back(new StringA("C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libnixmain.a"));
//	linker.m_files.push_back(new StringA("C:/cygwin/usr/local/amiga/m68k-amigaos/lib/libamiga.a"));
	linker.m_files.push_back(new StringA("C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libstubs.a"));
#else


	if (true)
	{
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/ncrt0.o"));
	//	linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/main.o"));

		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/LDebugger.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/mainfrm.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/SourceEdit.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/SourceEditFrame.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/DisassemblyWnd.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/WatchWnd.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/CallStackWnd.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/FileDialog.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/LDebugger/DebugSession.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libui.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libdraw.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libxmlparse.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libcode.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/liblfc.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/usr/local/amiga/lib/gcc/m68k-amigaos/3.4.0/libgcc.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/usr/local/amiga/m68k-amigaos/lib/libstdc++.a"));

		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libm.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libnix.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libnixmain.a"));
	//	linker.m_files.push_back(new StringA("WinHD_C:/cygwin/usr/local/amiga/m68k-amigaos/lib/libamiga.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libstubs.a"));
	}
	else
	{
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/ncrt0.o"));
	//	linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/main.o"));

		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/Browser/Browser.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/OBJ/Browser/BrowserFrame.o"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libui.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libdraw.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libxmlparse.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/libcode.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/liblfc.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/usr/local/amiga/lib/gcc/m68k-amigaos/3.4.0/libgcc.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/usr/local/amiga/m68k-amigaos/lib/libstdc++.a"));

		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libm.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libnix.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libnixmain.a"));
	//	linker.m_files.push_back(new StringA("WinHD_C:/cygwin/usr/local/amiga/m68k-amigaos/lib/libamiga.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libm020/libnix/libstubs.a"));

		/*
		linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/ncrt0.o"));
		linker.m_files.push_back(new StringA("WINHD_C:/MMStudio/Amiga68k/main.o"));
		linker.m_files.push_back(new StringA("WINHD_C:/cygwin/home/Sigurd Lerstad/lib/libnix/libnix.a"));
		linker.m_files.push_back(new StringA("WINHD_C:/cygwin/home/Sigurd Lerstad/lib/libnix/libnixmain.a"));
		linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libnix/libstubs.a"));
		*/
	}
#endif

	printf("pass1\n");
	linker.pass1();

/*
	GlobalSymbol* pSymbol = linker.m_globsyms[new StringA("_main")];
	pSymbol->m_defined = true;
	pSymbol->ResolvedValue = (DWORD)MyMain;
*/
//	linker.AddSymbol(new StringA("_main"), (DWORD)MyMain);

	printf("loading first object file\n");
#if 1
	linker.LoadObjectFile(linker.m_objectFiles[0]);
	if (true)
	{
		for (int i = 1; i < linker.m_objectFiles.size(); i++)
		{
			printf("loading %d object file\n", i);
			linker.LoadObjectFile(linker.m_objectFiles[i]);
		}
	}

	printf("Here\n");
	TRACE("\n\n");

	{
		for (int i = 0; i < linker.m_loadedObjectFiles.size(); i++)
		{
			OFile2* ofile = linker.m_loadedObjectFiles[i];

			if (ofile->m_afilename)
				TRACE("%s:%s\n", ofile->m_afilename->c_str(), ofile->m_ofilename->c_str());
			else
				TRACE("%s\n", ofile->m_ofilename->c_str());
		}
	}
#endif

	printf("before sets\n");

	linker.sets();

	printf("LoadObjectfile2\n");

	OFile* pOFile = linker.LoadObjectFile2(linker.m_objectFiles[0]);

	if (true)
	{
		for (int i = 1; i < linker.m_objectFiles.size(); i++)
		{
			linker.LoadObjectFile2(linker.m_objectFiles[i]);
		}
	}

/*
	{
		GlobalSymbol* psym = linker.m_globsyms[new StringA("_DOSBase")];
		int x = *(long*)psym->ResolvedValue;
	}
*/
	printf("done\n");

	if (linker.m_undefinedReferenceCount)
	{
		printf("undefined reference count: %d\n", linker.m_undefinedReferenceCount);
		TRACE("undefined reference count: %d\n", linker.m_undefinedReferenceCount);
	}
	else
	{
#if AMIGA
		GlobalSymbol* sym = linker.m_globsyms[new StringA("_plinker")];
		ASSERT(sym);
		ASSERT(sym->m_syms.size());

		*(Linker**)sym->m_syms[0]->ResolvedValue = &linker;
#endif

#if WIN32
		/*
		{
			gsymmap_t::iterator it2 = linker.m_globsyms.begin();
			while (it2 != linker.m_globsyms.end())
			{
// "__ZTI14red_black_nodeIPN6System7StringAEPNS0_9NamespaceEE"

				GlobalSymbol* sym = (*it2).second;
				if (strstr(sym->m_name->c_str(), "TI") && strstr(sym->m_name->c_str(), "red_black_node") && strstr(sym->m_name->c_str(), "StringA"))
				{
					MessageBeep(-1);
				}

				++it2;
			}
		}
		*/

		TypeArchive* ar = new TypeArchive(TypeArchive::Mode_Load, new FileByteStream(new StringA("C:/test.typeinfo"), FileMode_Read));

		int ntypes;
		*ar >> ntypes;

		printf("%d\n", ntypes);

		for (int i = 0; i < ntypes; i++)
		{
			NamedType* pType;
			*ar >> pType;

			BufferImp<char> buffer;
			StringBuilderA strbuilder(&buffer);
			pType->Write(strbuilder);
			pType->m_qname = buffer.DetachToString();

			if (*pType->m_qname == "second_argument_type")
			{
				MessageBeep(-1);
			}

			//if (pType->m_qname)
			{
				StringBuilderA strbuilder(&buffer);
				strbuilder << "__ZTI";	// type info

				Mangler mangler;
				mangler.MangleType(pType, strbuilder);

				StringA* name = buffer.DetachToString();

				gsymmap_t::iterator it2 = linker.m_globsyms.find(name);
				//map<StringA*, DWORD, Ref_Less<StringA> >::iterator it2 = symbols.find(name);
				if (it2 != linker.m_globsyms.end())
				{
					GlobalSymbol* globsym = (*it2).second;

					//TRACE("%s\n", name->c_str());

					if (!strcmp(globsym->m_name->c_str(), "__ZTI9IAddChild"))
					{
						MessageBeep(-1);

					}

					for (int j = 0; j < globsym->m_syms.size(); j++)
					{
						Symbol* sym = globsym->m_syms[j];

					}

#if AMIGA
					__type_info2* ti = (__type_info2*)sym->ResolvedValue;
					printf("%s\n", ti->__type_name);

				//	int len = strlen(ti->__type_name);
						/*
						char* newname = malloc(len+1+4);
						strcpy(newname+4, ti->__type_name);
						ti->__type_name = newname+4;
						*(Type**)newname = pType;
						*/
#endif
#if 0
					TypeDescriptor* typedesc = (TypeDescriptor*)(*it2).second;

					//VERIFY(typedesc->_m_data == NULL);

					if (pType->GetKind() == type_class)
					{
						((ClassType*)pType)->m_typedesc = (Type_Info*)typedesc;
					}
					else if (pType->GetKind() == type_enum)
					{
						((EnumType*)pType)->m_typedesc = (Type_Info*)typedesc;
					}

					typedesc->_m_data = pType2;

					AddPersistentLiveRoot((Object**)&typedesc->_m_data);
#endif
				}
				else
				{
					TRACE("-----%s\n", name->c_str());
				}
			}
		}
#endif

	{
#if 1
		ULONG heapsize = heap->m_next - (heap->m_data);
#else
		ULONG heapsize = heap->m_next - (heap->m_data+heap->m_size);
#endif

		printf("heapsize: %f MB\n", heapsize / (1024.0*1024));
	}

	#if AMIGA

		printf("Calling");

		char* line = strdup("programname parameter0 parameter1");
		entrypoint_hook(pOFile->m_textdata, line, strlen(line));
	#endif
	}

#if 0
	if (argc <= 1)
	{
		printf("Usage:\n");
		printf("loader objectfile\n");
		return -10;
	}

	Linker linker;

	for (int i = 1; i < argc; i++)
	{
		linker.m_files.Add(new StringA(argv[i]));
	}

	printf("pass1...");
	linker.pass1();
//	linker.pass2();

	/*
	GlobalSymbol* globsym = linker.globsyms["_main2"];

	FileByteStream file(globsym->m_filename);
	linker.LoadObjectFile(file);

	printf("Calling...");
	((dllentrypoint)globsym->Value)();
	printf("done\n");
	*/

	printf("done\n");

	printf("loading...");
	fflush(stdout);

//	FileByteStream* file = new FileByteStream(linker.m_files[0]);
//	printf("sdfsdf\n");
//	fflush(stdout);
	linker.LoadObjectFile(linker.m_objectFiles[0]);

	linker.sets();

	OFile* pOFile = linker.LoadObjectFile2(linker.m_objectFiles[0]);

	printf("done\n");

	if (linker.m_undefinedReferenceCount)
	{
		printf("undefined reference count: %d\n", linker.m_undefinedReferenceCount);
		TRACE("undefined reference count: %d\n", linker.m_undefinedReferenceCount);
	}
	else
	{
	#if AMIGA
		char* line = strdup("programname parameter0 parameter1");
		entrypoint_hook(pOFile->m_textdata, line, strlen(line));
	#endif
	}
#endif

	return 0;
}
