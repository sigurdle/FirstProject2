#include "stdafx.h"

#include "../CodeComp/AOut.h"
#include "../Include/AmigaHunkParser.h"
#include "../Include/ArchFile.h"

#include "../CodeComp/CreateObjectFileParser.h"

#include <stdlib.h>

extern "C" int entrypoint_hook(unsigned char* address, char* str, int len);

namespace System
{
using namespace std;
using namespace IO;

class OFile
{
public:
	uint8* m_textdata;
	ULONG m_textsize;

	uint8* m_datadata;
	ULONG m_datasize;

	uint8* m_bssdata;
	ULONG m_bsssize;
};

class OFile2
{
public:
	OFile2()
	{
		m_file = NULL;
		m_pLoaded = NULL;
		m_bloadedSymbols = false;
	}

	OFile* m_pLoaded;
	bool m_bloadedSymbols;

	System::StringA* m_afilename;
	System::StringA* m_ofilename;
	System::IO::ISequentialByteStream* m_file;
};

class GlobalSymbol
{
public:
	GlobalSymbol()
	{
		ResolvedValue = 0;
		m_pIndirect = NULL;

		m_pOFile = NULL;

		m_word = NULL;

		Value = 0;
	}

//	char* importDLL;
//	int ordinalHint;
//	char* publicName;

	System::StringA* m_name;

	GlobalSymbol* m_pIndirect;

	uint16 n_type;

	long Value;

	long ResolvedValue;

	ULONG* m_word;

//	nlist* refs;
//	std::vector<DWORD> refs;

//	std::string m_filename;
//	ULONG m_fileoffset;
	OFile2* m_pOFile;

	char defined;
};

typedef map<System::StringA*, GlobalSymbol*, Ref_Less<System::StringA> > gsymmap_t;

/*
class SetSymbol
{
public:
	SetSymbol()
	{
		ResolvedAddress = 0;
	}

	unsigned char   n_type;
	unsigned long   n_value;
	ISequentialByteStream* m_file;
	ULONG ResolvedAddress;
};
*/

typedef map<System::StringA*, vector<GlobalSymbol*>, Ref_Less<System::StringA> > symsetmap_t;

class Linker
{
public:

	CTOR Linker()
	{
		m_undefinedReferenceCount = 0;
	}

	uint8* m_textdata;
	ULONG m_textsize;

	void pass1();
	void Pass1_ObjectFile(System::StringA* afilename, System::StringA* ofilename, System::IO::ISequentialByteStream* file);
	OFile* LoadObjectFile(OFile2* ofile);
	OFile* LoadObjectFile2(OFile2* ofile);
	void Relocate(int nsection, const char* sectionname, uint8* data, ObjectFileParser* parser, OFile2* pOFile2, OFile* pOFile);
	void Relocate2(int nsection, const char* sectionname, uint8* data, ObjectFileParser* parser, OFile2* pOFile2, OFile* pOFile);

	void sets();

	ULONG m_undefinedReferenceCount;

	vector<System::StringA*> m_files;
	gsymmap_t globsyms;

	symsetmap_t m_symbolSets;

	vector<OFile2*> m_objectFiles;

	uint8* bss;
};

void Linker::Relocate(int nsection, const char* sectionname, uint8* data, ObjectFileParser* parser, OFile2* pOFile2, OFile* pOFile)
{
	int nrelocs = parser->GetNumberOfRelocations(nsection);
	for (int i = 0; i < nrelocs; i++)
	{
		Relocation* pReloc = parser->GetRelocation(nsection, i);

		if (pReloc->r_extern)
		{

			ObjectSymbol* pSymbol = parser->GetSymbol(pReloc->r_symbolnum);

			GlobalSymbol* globsym = globsyms[new StringA(string_copy(pSymbol->n_name))];

			if (globsym == NULL)
			{
				printf("globsym == NULL\n");
				exit(0);
			}

			/*
			if (globsym->defined == 0 && globsym->Value != 0)	// Create a bss entry for it
			{
				uint8* bssdata = new uint8[globsym->Value];
				memset(bssdata, 0, globsym->Value);

				globsym->defined = 1;
				globsym->ResolvedValue = (ULONG)bssdata;
			}
			*/

			/*
			if ((pSymbol->n_type & N_TYPE) == N_SETV)
			{
				TRACE("SetV %d\n", pSymbol->n_value);
			}
			*/

#if 0
			globsym->m_refs.push_back(pOFile2);
#endif
			/*
			if (!globsym->defined)
			{
				printf("%s:%s(.%s+0x%x): undefined reference to %s\n", pOFile2->m_afilename.c_str(), pOFile2->m_ofilename.c_str(), sectionname, pReloc->r_address, pSymbol->n_name);
				TRACE("%s:%s(.%s+0x%x): undefined reference to %s\n", pOFile2->m_afilename.c_str(), pOFile2->m_ofilename.c_str(), sectionname, pReloc->r_address, pSymbol->n_name);

				continue;
			}
			*/

			if (globsym->m_pIndirect)
			{
				if (globsym->m_pIndirect->ResolvedValue == 0)
				{
					//FileByteStream file(globsym->m_stream);
					LoadObjectFile(globsym->m_pIndirect->m_pOFile);
				}

				globsym->ResolvedValue = globsym->m_pIndirect->ResolvedValue;
			}
			else
			{
				if (globsym->m_pOFile)
				{
				//	if (globsym->ResolvedValue == 0)
					{
						//FileByteStream file(globsym->m_stream);
						LoadObjectFile(globsym->m_pOFile);
					}
				}
			}

			/*
			if (globsym->ResolvedValue == 0)
			{
				TRACE("\n");
				ASSERT(globsym->ResolvedValue);
			}
			*/
			/*
			if (globsym->ResolvedValue == 0)
			{
				globsym->m_stream->Seek(0, System::IO::STREAM_SEEK_SET);
				//FileByteStream file(globsym->m_stream);
				LoadObjectFile(globsym->m_stream);
			}
			*/

#if 0
//				if ((pReloc->r_symbolnum & N_TYPE) == N_TEXT)
			{
				*(DWORD*)(data + pReloc->r_address) = globsym->ResolvedValue;
			}
#endif
/*				else if ((pReloc->r_symbolnum & N_TYPE) == N_DATA)
			{
				*(DWORD*)(textdata + pReloc->r_address) = pSymbol->Value;
			}
*/
#if 0
			gsymmap_t::iterator gsym = l2g[pReloc->r_symbolnum];
			if (gsym != NULL)
			{
				std::string name = (*gsym).first;

				/*
				for (int j = 0; j < m_objfiles.size(); j++)
				{
				}
				*/

				//*(DWORD*)(textdata + pReloc->r_address) = 0;
				DWORD _Offset = ftell(fileout) + pReloc->r_address;
				(*gsym).second->refs.push_back(_Offset);
			}
#endif

			/*
			Linker::symbolmap::iterator symboli = symbols.find(pSymbol->n_name);
			if (symboli == symbols.end())
			{
				printf("Unresolved external symbol '%s'\n", pSymbol->n_name);
			}
			*/
		}
		else
		{
			//ObjectSymbol* pSymbol = pOFile->GetSymbol(pReloc->r_symbolnum);

			/*
			if ((pReloc->r_symbolnum & N_TYPE) == N_TEXT)
			{
				*(DWORD*)(data + pReloc->r_address) += (long)pOFile->m_textdata;//windowsHeader.ImageBase + pSectionText->VirtualAddress;
			}
			else if ((pReloc->r_symbolnum & N_TYPE) == N_DATA)
			{
				*(DWORD*)(data + pReloc->r_address) += -pOFile->m_textsize + (long)pOFile->m_datadata;//windowsHeader.ImageBase + pSectionData->VirtualAddress;
			}
			else if ((pReloc->r_symbolnum & N_TYPE) == N_BSS)
			{
				*(DWORD*)(data + pReloc->r_address) += -pOFile->m_textsize - pOFile->m_datasize + (long)pOFile->m_bssdata;//windowsHeader.ImageBase + pSectionData->VirtualAddress;
			}
			else
				ASSERT(0);
			*/
		}

	//	(DWORD*)(code + reloc->r_address);
	//	TRACE("reloc address: %d\n", reloc->r_address);
		//if (reloc->r_symbolnum < 5)
		{
		//	TRACE("%s=%d\n", parser.m_nlistSymbols[reloc->r_symbolnum].n_un.n_name, parser.m_nlistSymbols[reloc->r_symbolnum].n_value);
		}
	}
}

void Linker::Relocate2(int nsection, const char* sectionname, uint8* data, ObjectFileParser* parser, OFile2* pOFile2, OFile* pOFile)
{
	int nrelocs = parser->GetNumberOfRelocations(nsection);
	for (int i = 0; i < nrelocs; i++)
	{
		Relocation* pReloc = parser->GetRelocation(nsection, i);

		if (pReloc->r_extern)
		{

			ObjectSymbol* pSymbol = parser->GetSymbol(pReloc->r_symbolnum);
		if (!strcmp(pSymbol->n_name, "___dosname"))
			{
				TRACE("");
			}

			GlobalSymbol* globsym = globsyms[new StringA(string_copy(pSymbol->n_name))];

			if (globsym == NULL)
			{
				printf("globsym == NULL\n");
				exit(0);
			}

			if (globsym->ResolvedValue == 0)
			{
				if (/*globsym->defined == 0 &&*/ globsym->Value != 0)	// Create a bss entry for it
				{
					uint8* bssdata = new uint8[globsym->Value];
					memset(bssdata, 0, globsym->Value);

					globsym->defined = 1;
					globsym->ResolvedValue = (ULONG)bssdata;
				}
			}

			/*
			if ((pSymbol->n_type & N_TYPE) == N_SETV)
			{
				TRACE("SetV %d\n", pSymbol->n_value);
			}
			*/

			if (!globsym->defined)
			{
				printf("%s:%s(.%s+0x%x): undefined reference to %s\n", pOFile2->m_afilename->c_str(), pOFile2->m_ofilename->c_str(), sectionname, pReloc->r_address, pSymbol->n_name);
				TRACE("%s:%s(.%s+0x%x): undefined reference to %s\n", pOFile2->m_afilename->c_str(), pOFile2->m_ofilename->c_str(), sectionname, pReloc->r_address, pSymbol->n_name);

				m_undefinedReferenceCount++;

				continue;
			}

			if (globsym->m_pIndirect)
			{
			//	if (globsym->m_pIndirect->ResolvedValue == 0)
				{
					//FileByteStream file(globsym->m_stream);
					LoadObjectFile2(globsym->m_pIndirect->m_pOFile);
				}

				globsym->ResolvedValue = globsym->m_pIndirect->ResolvedValue;
			}
			else
			{
				if (globsym->m_pOFile)
			//	if (globsym->ResolvedValue == 0)
				{
					//FileByteStream file(globsym->m_stream);
					LoadObjectFile2(globsym->m_pOFile);
				}
			}

			if (globsym->ResolvedValue == 0)
			{
				TRACE("warning: unresolved %s\n", globsym->m_name->c_str());
				//ASSERT(globsym->ResolvedValue);
			}
			/*
			if (globsym->ResolvedValue == 0)
			{
				globsym->m_stream->Seek(0, System::IO::STREAM_SEEK_SET);
				//FileByteStream file(globsym->m_stream);
				LoadObjectFile(globsym->m_stream);
			}
			*/

//				if ((pReloc->r_symbolnum & N_TYPE) == N_TEXT)
			{
				uint32 oldaddress = BigEndian32(*(uint32*)(data + pReloc->r_address));
				uint32* address = (uint32*)(data + pReloc->r_address);

				*address += globsym->ResolvedValue;
			}
/*				else if ((pReloc->r_symbolnum & N_TYPE) == N_DATA)
			{
				*(DWORD*)(textdata + pReloc->r_address) = pSymbol->Value;
			}
*/
#if 0
			gsymmap_t::iterator gsym = l2g[pReloc->r_symbolnum];
			if (gsym != NULL)
			{
				std::string name = (*gsym).first;

				/*
				for (int j = 0; j < m_objfiles.size(); j++)
				{
				}
				*/

				//*(DWORD*)(textdata + pReloc->r_address) = 0;
				DWORD _Offset = ftell(fileout) + pReloc->r_address;
				(*gsym).second->refs.push_back(_Offset);
			}
#endif

			/*
			Linker::symbolmap::iterator symboli = symbols.find(pSymbol->n_name);
			if (symboli == symbols.end())
			{
				printf("Unresolved external symbol '%s'\n", pSymbol->n_name);
			}
			*/
		}
		else
		{
			//ObjectSymbol* pSymbol = pOFile->GetSymbol(pReloc->r_symbolnum);

			if ((pReloc->r_symbolnum & N_TYPE) == N_TEXT)
			{
				*(uint32*)(data + pReloc->r_address) += (long)pOFile->m_textdata;//windowsHeader.ImageBase + pSectionText->VirtualAddress;
			}
			else if ((pReloc->r_symbolnum & N_TYPE) == N_DATA)
			{
				*(uint32*)(data + pReloc->r_address) += -pOFile->m_textsize + (long)pOFile->m_datadata;//windowsHeader.ImageBase + pSectionData->VirtualAddress;
			}
			else if ((pReloc->r_symbolnum & N_TYPE) == N_BSS)
			{
				*(uint32*)(data + pReloc->r_address) += -pOFile->m_textsize - pOFile->m_datasize + (long)pOFile->m_bssdata;//windowsHeader.ImageBase + pSectionData->VirtualAddress;
			}
			else
				ASSERT(0);

		}
	}
}

OFile* Linker::LoadObjectFile(OFile2* ofile)
{
	if (ofile->m_bloadedSymbols)
		return NULL;

	ofile->m_bloadedSymbols = true;

	ofile->m_file->Seek(0, System::IO::STREAM_SEEK_SET);
	ObjectFileParser* parser = CreateObjectFileParser(ofile->m_file);

	parser->Read(ofile->m_file);

	int nsymbols = parser->GetNumberOfSymbols();

//	gsymmap::iterator* l2g = new gsymmap::iterator[nsymbols];

	GlobalSymbol* indr = NULL;

	for (int i = 0; i < nsymbols; i++)
	{

		ObjectSymbol* pSymbol = parser->GetSymbol(i);

		GlobalSymbol* globsym = globsyms[new StringA(string_copy(pSymbol->n_name))];

		if (!strcmp(pSymbol->n_name, "___ltdf2"))
		{
			TRACE("");
		}

		if (globsym == NULL)
		{
		//	ASSERT(0);
			globsym = new GlobalSymbol;
			globsym->m_name = new StringA(string_copy(pSymbol->n_name));
		//	globsym->n_type = 
		//	globsym->defined = true;
		//	globsym->m_pOFile = ofile;
			globsyms[globsym->m_name] = globsym;
		}

		if ((pSymbol->n_type & N_TYPE) != N_UNDF/* || ((pSymbol->n_type & N_EXT) && (pSymbol->n_value > 0))*/)
		{
		//	globsym->Value = pSymbol->n_value;
		//	globsym->n_type = pSymbol->n_type;

			globsym->defined = true;

#if 0
			if ((pSymbol->n_type & N_TYPE) == N_ABS)
			{
				globsym->ResolvedValue = pSymbol->n_value;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_TEXT)
			{
				globsym->ResolvedValue = (long)pOFile->m_textdata + pSymbol->n_value;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_DATA)
			{
				globsym->ResolvedValue = (long)pOFile->m_datadata + pSymbol->n_value;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_BSS)
			{
				globsym->ResolvedValue = (long)pOFile->m_bssdata + bssoffset;
				bssoffset += pSymbol->n_value;
			}
#endif
			if (	(pSymbol->n_type & N_TYPE) == N_SETA ||
					(pSymbol->n_type & N_TYPE) == N_SETD ||
					(pSymbol->n_type & N_TYPE) == N_SETB ||
					(pSymbol->n_type & N_TYPE) == N_SETT)
			{
				GlobalSymbol* setsymbol = new GlobalSymbol;
				setsymbol->n_type = pSymbol->n_type;
				setsymbol->Value = pSymbol->n_value;
				setsymbol->m_pOFile = ofile;
				m_symbolSets[new StringA(string_copy(pSymbol->n_name))].Add(setsymbol);

				/*
				GlobalSymbol* globsym = globsyms[pSymbol->n_name];
				if (globsym == NULL)
				{
					globsym = new GlobalSymbol;
					globsyms[pSymbol->n_name] = globsym;
				}
				*/

			//	globsym->m_name = pSymbol->n_name;
				globsym->n_type = pSymbol->n_type;
				globsym->Value = pSymbol->n_value;
				//globsym->defined = true;
				globsym->m_pOFile = ofile;

			//	globsym->m_stream = file;
			}
	
#if 0
			else if ((pSymbol->n_type & N_TYPE) == N_SETA)
			{
				m_symbolSets
				/*
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = pSymbol->n_value;
				*(long*)(globsym->ResolvedValue)++;
				*/
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETT)
			{
				MessageBeep(-1);
				/*
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = (long)pOFile->m_textdata + pSymbol->n_value;
				long* p = (long*)(globsym->ResolvedValue);
				*p += 1;
				*/
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETD)
			{
				/*
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = (long)pOFile->m_textdata + pSymbol->n_value;
				long* p = (long*)(globsym->ResolvedValue);
				*p += 1;
				*/
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETB)
			{
				/*
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = (long)pOFile->m_bssdata + bssoffset;
				long* p = (long*)(globsym->ResolvedValue);
				*p += 1;
				bssoffset += pSymbol->n_value;
				*/
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETV)
			{
				/*
				globsym->ResolvedValue = 1;//m_setaddress;
				TRACE("SetV %d\n", pSymbol->n_value);
				*/
			}
#endif
#if 0
			else if ((pSymbol->n_type & N_TYPE) == N_INDR)
			{
				//globsym->ResolvedValue = 1;
				TRACE("%d\n", pSymbol->n_value);
			}
			else if ((pSymbol->n_type & N_EXT) && pSymbol->n_value > 0)
			{
				//ASSERT();

				// Allocate space in bss (TODO, improve)
			//	globsym->ResolvedValue = 1;

				uint8* bssdata = new uint8[pSymbol->n_value];
				memset(bssdata, 0, globsym->Value);

				globsym->defined = 1;
				globsym->ResolvedValue = (ULONG)bssdata;
			}
			else
			{
				TRACE("Unknown type(%d) of symbol %s\n", (pSymbol->n_type & N_TYPE), pSymbol->n_name);
				printf("Unknown type(%d) of symbol %s\n", (pSymbol->n_type & N_TYPE), pSymbol->n_name);
				;//ASSERT(0);
			}
#endif
		}
		else if ((pSymbol->n_type & N_EXT) && (pSymbol->n_value > 0))
		{
			globsym->Value = MAX(globsym->Value, pSymbol->n_value);
		}

		if (indr)
		{
			indr->m_pIndirect = globsym;
		}

		if ((pSymbol->n_type & N_TYPE) == N_INDR)
			indr = globsym;
		else
			indr = NULL;
	}

	Relocate(0, "text", NULL/*oFile->m_textdata*/, parser, ofile, NULL/*pOFile*/);
	Relocate(1, "data", NULL/*File->m_datadata*/, parser, ofile, NULL/*pOFile*/);

	return NULL;//pOFile;
}

OFile* Linker::LoadObjectFile2(OFile2* ofile)
{
	if (ofile->m_pLoaded)
		return ofile->m_pLoaded;

	if (ofile->m_afilename->Length()) TRACE("%s:", ofile->m_afilename->c_str());
	TRACE("%s\n", ofile->m_ofilename->c_str());

//	ASSERT(ofile->m_pLoaded);

	OFile* pOFile = new OFile;

	ofile->m_pLoaded = pOFile;

	ofile->m_file->Seek(0, System::IO::STREAM_SEEK_SET);
	ObjectFileParser* parser = CreateObjectFileParser(ofile->m_file);

	parser->Read(ofile->m_file);

	int numberOfSections = parser->GetNumberOfSections();

	//OFile* pOFile = ofile->m_pLoaded;

//	ofile->m_pLoaded = pOFile;

//	for (int i = 0; i < numberOfSections; i++)
//		;

	pOFile->m_textsize = parser->GetDataSize(0);
	pOFile->m_textdata = parser->GetData(0);

//	printf("textsize: %d\n", pOFile->m_textsize);

	pOFile->m_datasize = parser->GetDataSize(1);
	pOFile->m_datadata = parser->GetData(1);

//	printf("datasize: %d\n", pOFile->m_datasize);

	pOFile->m_bsssize = parser->GetDataSize(2);
	pOFile->m_bssdata = new uint8[pOFile->m_bsssize];
	memset(pOFile->m_bssdata, 0, pOFile->m_bsssize);

	ULONG bssoffset = 0;

	int nsymbols = parser->GetNumberOfSymbols();

//	gsymmap::iterator* l2g = new gsymmap::iterator[nsymbols];

	for (int i = 0; i < nsymbols; i++)
	{
	//	const char* symbolname = NULL;
	//	Linker::CSymbol symbol;
	//	symbols.insert(Linker::symbolmap::value_type(symbolname, symbol));

		ObjectSymbol* pSymbol = parser->GetSymbol(i);

		GlobalSymbol* globsym = globsyms[new StringA(string_copy(pSymbol->n_name))];

		if ((pSymbol->n_type & N_TYPE) != N_UNDF)
		{
			if ((pSymbol->n_type & N_TYPE) == N_ABS)
			{
			//	ASSERT(globsym->ResolvedValue == 0);
				globsym->ResolvedValue = pSymbol->n_value;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_TEXT)
			{
			//	ASSERT(globsym->ResolvedValue == 0);
				globsym->ResolvedValue = (long)pOFile->m_textdata + pSymbol->n_value;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_DATA)
			{
			//	ASSERT(globsym->ResolvedValue == 0);
				globsym->ResolvedValue = (long)pOFile->m_datadata + pSymbol->n_value;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_BSS)
			{
			//	ASSERT(globsym->ResolvedValue == 0);
				globsym->ResolvedValue = (long)pOFile->m_bssdata + bssoffset;
				bssoffset += pSymbol->n_value;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETA)
			{
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = pSymbol->n_value;
				long* p = (long*)(globsym->ResolvedValue);
				*p += 1;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETT)
			{
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = (long)pOFile->m_textdata + pSymbol->n_value;
				long* p = (long*)(globsym->ResolvedValue);
				*p += 1;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETD)
			{
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = (long)pOFile->m_datadata + pSymbol->n_value;
				long* p = (long*)(globsym->ResolvedValue);
				*p += 1;
			}
			else if ((pSymbol->n_type & N_TYPE) == N_SETB)
			{
				ASSERT(globsym->ResolvedValue);
				*globsym->m_word++ = (long)pOFile->m_bssdata + bssoffset;
				long* p = (long*)(globsym->ResolvedValue);
				*p += 1;
				bssoffset += pSymbol->n_value;
			}
		}
	}

	Relocate2(0, "text", pOFile->m_textdata, parser, ofile, pOFile);
	Relocate2(1, "data", pOFile->m_datadata, parser, ofile, pOFile);

	return pOFile;
}

void Linker::Pass1_ObjectFile(StringA* afilename, StringA* ofilename, ISequentialByteStream* file)
{
	OFile2* ofile = new OFile2;
	ofile->m_afilename = afilename;
	ofile->m_ofilename = ofilename;
	ofile->m_file = file;

	m_objectFiles.Add(ofile);

	AOutParser parser;
	parser.Read(file);

	AOutParser* pOFile = &parser;

	int nsymbols = pOFile->GetNumberOfSymbols();

	//gsymmap::iterator* l2g = new gsymmap::iterator[nsymbols];

//	GlobalSymbol* indr = NULL;

	for (int i = 0; i < nsymbols; i++)
	{
	//	const char* symbolname = NULL;
	//	Linker::CSymbol symbol;
	//	symbols.insert(Linker::symbolmap::value_type(symbolname, symbol));

		ObjectSymbol* pSymbol = pOFile->GetSymbol(i);

	//	printf("%s\n", pSymbol->n_name);

		if (pSymbol->n_type & N_STAB)
		{
			TRACE("\n");
		}
		else //if ((pSymbol->n_type & N_TYPE) != N_UNDF)
	//	if (!(pSymbol->n_type & (1<<4)))	// !extern
		{
		//	TRACE("%s, %d\n", pSymbol->n_name, pSymbol->n_type);

			if (	(pSymbol->n_type & N_TYPE) == N_SETA ||
					(pSymbol->n_type & N_TYPE) == N_SETD ||
					(pSymbol->n_type & N_TYPE) == N_SETB ||
					(pSymbol->n_type & N_TYPE) == N_SETT)
			{
				/*
				GlobalSymbol* setsymbol = new GlobalSymbol;
				setsymbol->n_type = pSymbol->n_type;
				setsymbol->Value = pSymbol->n_value;
				setsymbol->m_pOFile = ofile;
				m_symbolSets[pSymbol->n_name].push_back(setsymbol);

				GlobalSymbol* globsym = globsyms[pSymbol->n_name];
				if (globsym == NULL)
				{
					globsym = new GlobalSymbol;
					globsyms[pSymbol->n_name] = globsym;
				}

				globsym->m_name = pSymbol->n_name;
				globsym->n_type = pSymbol->n_type;
				globsym->Value = pSymbol->n_value;
				globsym->defined = true;
				globsym->m_pOFile = ofile;

			//	globsym->m_stream = file;
				*/
			}
			else
			{
				GlobalSymbol* globsym;
				gsymmap_t::iterator symboli = globsyms.find(new StringA(string_copy(pSymbol->n_name)));
				if (symboli == globsyms.end())
				{
				//	pSymbol->n_type
					globsym = new GlobalSymbol;
					globsym->m_name = new StringA(string_copy(pSymbol->n_name));

					if ((pSymbol->n_type & N_TYPE) != N_UNDF/* || ((pSymbol->n_type & N_EXT) && pSymbol->n_value > 0)*/)
					{
						globsym->m_pOFile = ofile;
					}

					/*
					if ((pSymbol->n_type & N_EXT) && pSymbol->n_value > 0)
					{
						globsym->Value = MAX(globsym->Value, pSymbol->n_value);
					}
					*/

					globsym->defined = (pSymbol->n_type & N_TYPE) != N_UNDF;
	#if 0
					globsym->m_filename = filename;
	#endif
				//	globsym->m_fileoffset = 0;

					globsym->n_type = pSymbol->n_type;
				//	globsym->Value = pSymbol->n_value;
				//	globsym->ordinalHint = importHeader.OrdinalHint;
				//	globsym->importDLL = importDLL;
				//	globsym->publicName = strdup(publicName.c_str());

				//	printf("%d/%s/%s\n", importHeader.OrdinalHint, importName, importDLL);

					globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
				}
				else
				{
					globsym = (*symboli).second;
					if (globsym->defined)
					{
						if ((pSymbol->n_type & N_TYPE) != N_UNDF)
						{
							TRACE("multiple defined symbol %s\n", pSymbol->n_name);
							printf("multiple defined symbol %s\n", pSymbol->n_name);
						}
					}
					else
					{
						globsym->defined = (pSymbol->n_type & N_TYPE) != N_UNDF;
						globsym->n_type = pSymbol->n_type;
					//	globsym->Value = MAX(globsym->Value, pSymbol->n_value);

						if ((pSymbol->n_type & N_TYPE) != N_UNDF)
						{
							globsym->m_pOFile = ofile;
						}
					}
				}

				/*
				if (indr)
				{
					indr->m_pIndirect = globsym;
				}

				if ((pSymbol->n_type & N_TYPE) == N_INDR)
					indr = globsym;
				else
					indr = NULL;
				*/
			}
		}
	}

	m_textsize = 4096*10;//m_symbolSets.size()*4;
	m_textdata = new uint8[m_textsize];
	memset(m_textdata, 0, m_textsize);
}

void Linker::pass1()
{
	for (int i = 0; i < m_files.GetSize(); i++)
	{
		StringA* filename = m_files[i];
		int len = filename->Length();

		printf("opening %s\n", filename->c_str());
		FileByteStream* file = new FileByteStream(filename);

		if (filename->c_str()[len-1] == 'a')
		{
			ArchFile arch;
			arch.Read(file);

			if (false)
			{
				for (int i = 0; i < arch.m_members.size(); i++)
				{
					file->Seek(arch.m_members[i].Offset, System::IO::STREAM_SEEK_SET);
					uint8* data = new uint8[arch.m_members[i].Size];
					file->Read(data, arch.m_members[i].Size);
					MemoryByteStream* mem = new MemoryByteStream(data, arch.m_members[i].Size);
				//	mem->AddRef();
					Pass1_ObjectFile(filename, arch.m_members[i].name, mem);
				//	delete[] data;
				}
			}
			else
			{
#if 1
				map<ULONG,int> offsetmap;
				vector<OFile2*> objectfiles;
				{
					for (int i = 0; i < arch.m_members.size(); i++)
					{
						TRACE("%s: %s %d, %d\n", filename->c_str(), arch.m_members[i].name->c_str(), arch.m_members[i].Offset, arch.m_members[i].Size);

						offsetmap[arch.m_members[i].Offset] = i;

						file->Seek(arch.m_members[i].Offset, System::IO::STREAM_SEEK_SET);

						uint8* data = new uint8[arch.m_members[i].Size];
						file->Read(data, arch.m_members[i].Size);
						MemoryByteStream* mem = new MemoryByteStream(data, arch.m_members[i].Size);

						OFile2* ofile = new OFile2;
						ofile->m_afilename = filename;
						ofile->m_ofilename = arch.m_members[i].name;
						ofile->m_file = mem;

						objectfiles.Add(ofile);

						//Pass1_ObjectFile(filename, arch.m_members[i].name, mem);

						m_objectFiles.Add(ofile);
					//	delete[] data;
					}
				}

				for (int i = 0; i < arch.m_nsymboldefs; i++)
				{
					const char* symname = arch.m_strbuffer + arch.m_symdefs[i].nameindex;
					//TRACE("%d\n", );

					int index = offsetmap[arch.m_symdefs[i].fileoffset+sizeof(ArchiveHeader)];

					gsymmap_t::iterator symboli = globsyms.find(new StringA(string_copy(symname)));
					if (symboli == globsyms.end())
					{
					//	pSymbol->n_type
						GlobalSymbol* globsym = new GlobalSymbol;

					//	globsym->m_filename = filename;
					//	globsym->m_fileoffset = arch.m_symdefs[i].fileoffset;

						globsym->m_name = new StringA(string_copy(symname));
						globsym->m_pOFile = objectfiles[index];

						TRACE("%s:%s\n", globsym->m_pOFile->m_ofilename->c_str(), symname);

					//	globsym->Value = 0;
						globsym->defined = true;	// ??
					//	globsym->ordinalHint = importHeader.OrdinalHint;
					//	globsym->importDLL = importDLL;
					//	globsym->publicName = strdup(publicName.c_str());

					//	printf("%d/%s/%s\n", importHeader.OrdinalHint, importName, importDLL);

						globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
					}
					else
					{
						GlobalSymbol* globsym = (*symboli).second;

						if (globsym->defined)
						{
							printf("multiple defined symbol %s\n", symname);
							TRACE("multiple defined symbol %s\n", symname);
							//ASSERT(0);	// TODO remove
						}
						else
						{
							globsym->m_pOFile = objectfiles[index];
							globsym->defined = true;
						}
					}
				}
#endif
			}
		}
		else if (filename->c_str()[len-1] == 'o')
		{
			Pass1_ObjectFile(NULL, filename, file);
		}
	}
}

/*
void Linker::set()
{
}
*/

void Linker::sets()
{
	ULONG* word = (ULONG*)m_textdata;

	symsetmap_t::iterator it = m_symbolSets.begin();
	while (it != m_symbolSets.end())
	{
		int count = (*it).second.size();

		GlobalSymbol* globsym = globsyms[(*it).first];
		globsym->ResolvedValue = (long)word;
	//	long nsize = (*it).second.size();

		*word++ = 0;
		globsym->m_word = word;


		/*
		TRACE("%s - %d\n", (*it).first.c_str(), nsize);

		for (int i = 0; i < nsize; i++)
		{
			GlobalSymbol* symbol = (*it).second[i];
			//if (symbol
		//	globsym->ResolvedValue = address;//(ULONG)word;
		//	ASSERT(globsym->ResolvedValue);

			if (symbol->ResolvedAddress == 0)
			{
//				LoadObjectFile(symbol->m_pOFile);
			//	symbol.m_file
			}

		//	*word++ = symbol.n_value;
		}
		*/

		word += count;	// Make room (TODO)
		word++;	// null terminated ??

		++it;
	}
}

char* cmdline = "";

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("Usage:\n");
		printf("loader objectfile\n");
		return -10;
	}

	Linker linker;

	for (int i = 1; i < argc; i++)
	{
		linker.m_files.Add(new StringA(string_copy(argv[i])));
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

	return 0;
}

}
