#include "stdafx.h"
#include "LFC.h"

#include "../CodeComp/AOut.h"
#include "../Include/AmigaHunkParser.h"
#include "../Include/ArchFile.h"

//#include "../CodeComp/CreateObjectFileParser.h"

#include "Linker.h"

namespace System
{

using namespace System::IO;


#if 1
void Linker::Relocate(int nsection, const char* sectionname, ObjectFileParser* parser, OFile2* pOFile2)
{
	int nrelocs = parser->GetNumberOfRelocations(nsection);
	for (int i = 0; i < nrelocs; i++)
	{
		Relocation* pReloc = parser->GetRelocation(nsection, i);

		if (pReloc->r_extern)
		{

			ObjectSymbol* pSymbol = parser->GetSymbol(pReloc->r_symbolnum);

			Symbol* sym = pOFile2->m_symbols[pReloc->r_symbolnum];
			GlobalSymbol* globsym = sym->m_globsym;//m_globsyms[new StringA(pSymbol->n_name)];

			if (globsym == NULL)
			{
				printf("globsym == NULL\n");
				VERIFY(0);//exit(0);
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

			if (globsym->m_syms.size())
			{
				Symbol* sym = globsym->m_syms[0];

				if (sym->m_pIndirect)
				{
					//if (globsym->m_pIndirect->m_syms[0]->ResolvedValue == 0)
					{
						//FileByteStream file(globsym->m_stream);
						LoadObjectFile(sym->m_pIndirect->m_pOFile);
					}

					//ASSERT(globsym->m_pIndirect->ResolvedValue == 0);	// Not yet
					//globsym->ResolvedValue = globsym->m_pIndirect->ResolvedValue;
				}
				else
				{
					{
					//	if (globsym->ResolvedValue == 0)
						{
							//FileByteStream file(globsym->m_stream);
							LoadObjectFile(sym->m_pOFile);
						}
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
#endif

#if 1
void Linker::LoadObjectFile(OFile2* ofile)
{
	if (ofile->m_bloadedSymbols)
		return;// NULL;

	m_loadedObjectFiles.push_back(ofile);

	ofile->m_bloadedSymbols = true;

#if 1
	ofile->m_file->Seek(0, System::IO::STREAM_SEEK_SET);

//	ObjectFileParser* parser = CreateObjectFileParser(ofile->m_file);
	AOutParser* parser = new AOutParser;

	parser->Read(ofile->m_file);

	int nsymbols = parser->GetNumberOfSymbols();

//	gsymmap::iterator* l2g = new gsymmap::iterator[nsymbols];

	Symbol* indr = NULL;

	for (int i = 0; i < nsymbols; i++)
	{
		ObjectSymbol* pSymbol = parser->GetSymbol(i);
		Symbol* sym = ofile->m_symbols[i];

		if (!(pSymbol->n_type & N_STAB))
		{
			//gsymmap_t::iterator symit = m_globsyms.find(new StringA(pSymbol->n_name));

			GlobalSymbol* globsym = sym->m_globsym;

			/*
			if (symit == m_globsyms.end())
				ASSERT(0);//globsym = NULL;
			else
				globsym = (*symit).second;
				*/

			/*

			if (globsym == NULL)
			{
				ASSERT(0);
				globsym = new GlobalSymbol;
				globsym->m_name = new StringA(pSymbol->n_name);
			//	globsym->n_type = 
			//	globsym->defined = true;
			//	globsym->m_pOFile = ofile;
				m_globsyms[globsym->m_name] = globsym;
			}
			*/

			if ((pSymbol->n_type & N_TYPE) != N_UNDF/* || ((pSymbol->n_type & N_EXT) && (pSymbol->n_value > 0))*/)
			{

				if (	(pSymbol->n_type & N_TYPE) == N_SETA ||
						(pSymbol->n_type & N_TYPE) == N_SETD ||
						(pSymbol->n_type & N_TYPE) == N_SETB ||
						(pSymbol->n_type & N_TYPE) == N_SETT)
				{
#if 0
					ASSERT(0);
					GlobalSymbol* setsymbol = new GlobalSymbol;
					setsymbol->n_type = pSymbol->n_type;
					setsymbol->Value = pSymbol->n_value;
					setsymbol->m_pOFile = ofile;
					ASSERT(m_symbolSets.find(globsym) != m_symbolSets.end());
#endif
					m_symbolSets[globsym].push_back(sym);

				//	globsym->m_stream = file;
				}
		
			}
#if 0
			else if ((pSymbol->n_type & N_EXT) && (pSymbol->n_value > 0))
			{
				ASSERT(globsym);

				ASSERT(globsym->Value >= pSymbol->n_value);

				//globsym->Value = MAX(globsym->Value, pSymbol->n_value);
			}
#endif
			if (indr)
			{
				indr->m_pIndirect = sym;
			}

			if ((pSymbol->n_type & N_TYPE) == N_INDR)
				indr = sym;
			else
				indr = NULL;
		}
	}

	Relocate(0, "text", parser, ofile);
	Relocate(1, "data", parser, ofile);
#endif

//	return NULL;//pOFile;
}
#endif

void Linker::AddSymbol(StringA* symname, DWORD Value)
{
	ASSERT(0);
#if 0
	GlobalSymbol* globsym = new GlobalSymbol;

	globsym->m_name = symname;
	globsym->Value = Value;
	globsym->ResolvedValue = Value;

	m_globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
#endif
}

void Linker::Relocate2(int nsection, const char* sectionname, uint8* data, ObjectFileParser* parser, OFile2* pOFile2, OFile* pOFile)
{
	int nrelocs = parser->GetNumberOfRelocations(nsection);
	for (int i = 0; i < nrelocs; i++)
	{
		Relocation* pReloc = parser->GetRelocation(nsection, i);

		if (pReloc->r_extern)
		{
			Symbol* sym = pOFile2->m_symbols[pReloc->r_symbolnum];
			GlobalSymbol* globsym = sym->m_globsym;

			if (!globsym->m_defined)
			{
				printf("%s:%s(.%s+0x%x): undefined reference to %s\n", pOFile2->m_afilename? pOFile2->m_afilename->c_str(): NULL, pOFile2->m_ofilename->c_str(), sectionname, pReloc->r_address, globsym->m_name->c_str());
				TRACE("%s:%s(.%s+0x%x): undefined reference to %s\n", pOFile2->m_afilename? pOFile2->m_afilename->c_str(): NULL, pOFile2->m_ofilename->c_str(), sectionname, pReloc->r_address, globsym->m_name->c_str());

				m_undefinedReferenceCount++;

				continue;
			}

			ASSERT(globsym->m_syms.size());

			sym = globsym->m_syms[0];

			if (sym->m_pIndirect)
			{
				LoadObjectFile2(sym->m_pIndirect->m_globsym->m_syms[0]->m_pOFile);

				sym->ResolvedValue = sym->m_pIndirect->m_globsym->m_syms[0]->ResolvedValue;
				ASSERT(sym->ResolvedValue);
				globsym->setResolvedValue = sym->ResolvedValue;
			}
			else
			{
				LoadObjectFile2(sym->m_pOFile);

				ASSERT(sym->ResolvedValue);
				ASSERT(globsym->setResolvedValue == sym->ResolvedValue);
			}

			ASSERT(globsym->setResolvedValue);

			DWORD* address = (DWORD*)(data + pReloc->r_address);

			if (pReloc->r_pcrel)
			{
				ASSERT(globsym->setResolvedValue);
				*address = globsym->setResolvedValue - (DWORD)address;
			}
			else
			{
				ASSERT(globsym->setResolvedValue);
				*address += globsym->setResolvedValue;
			}
		}
		else
		{
			ASSERT(!pReloc->r_pcrel);	// TODO, not this restriction

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

		}
	}
}

OFile* Linker::LoadObjectFile2(OFile2* ofile)
{
	if (ofile->m_pLoaded)
		return ofile->m_pLoaded;

	/*
	if (strstr(ofile->m_ofilename->c_str(), "DependencyObject.o"))
	{
		MessageBeep(-1);
	}
	*/

//	if (ofile->m_afilename) TRACE("%s:", ofile->m_afilename->c_str());
//	TRACE("%s\n", ofile->m_ofilename->c_str());

//	ASSERT(ofile->m_pLoaded);

	OFile* pOFile = new OFile;

	ofile->m_pLoaded = pOFile;

	ofile->m_file->Seek(0, System::IO::STREAM_SEEK_SET);
//	ObjectFileParser* parser = CreateObjectFileParser(ofile->m_file);
	AOutParser* parser = new AOutParser;

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
	if (pOFile->m_bsssize > 0)
		pOFile->m_bssdata = new uint8[pOFile->m_bsssize];
	else
		pOFile->m_bssdata = NULL;

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
		Symbol* sym = ofile->m_symbols[i];

		if (sym)//!(pSymbol->n_type & N_STAB))
		{
			GlobalSymbol* globsym = sym->m_globsym;//m_globsyms[new StringA(pSymbol->n_name)];

			if ((pSymbol->n_type & N_TYPE) != N_UNDF)
			{
				if ((pSymbol->n_type & N_TYPE) == N_ABS)
				{
					ASSERT(sym->ResolvedValue == 0);
					sym->ResolvedValue = pSymbol->n_value;

					//	TRACE("%s, abs %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
					//	printf("%s, abs %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
					if (sym == globsym->m_syms[0])
					{
						ASSERT(globsym->setResolvedValue == 0);
						globsym->setResolvedValue = sym->ResolvedValue;
					}
				}
				else if ((pSymbol->n_type & N_TYPE) == N_TEXT)
				{
					//if (globsym->m_pOFile == ofile)
					{
						ASSERT(sym->ResolvedValue == 0);
						sym->ResolvedValue = (long)pOFile->m_textdata + pSymbol->n_value;

						//	TRACE("%s, text %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
						//	printf("%s, text %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
						if (sym == globsym->m_syms[0])
						{
							ASSERT(globsym->setResolvedValue == 0);
							globsym->setResolvedValue = sym->ResolvedValue;
						}
					}
				}
				else if ((pSymbol->n_type & N_TYPE) == N_DATA)
				{
					//if (globsym->m_pOFile == ofile)
					{
						ASSERT(sym->ResolvedValue == 0);
						sym->ResolvedValue = (long)pOFile->m_datadata + pSymbol->n_value;

						//	TRACE("%s, data %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
						//	printf("%s, data %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
						if (sym == globsym->m_syms[0])
						{
							ASSERT(globsym->setResolvedValue == 0);
							globsym->setResolvedValue = sym->ResolvedValue;
						}
					}
				}
				else if ((pSymbol->n_type & N_TYPE) == N_BSS)
				{
					//if (globsym->m_pOFile == ofile)
					{
						ASSERT(sym->ResolvedValue == 0);
						sym->ResolvedValue = (long)pOFile->m_bssdata + bssoffset;
						bssoffset += pSymbol->n_value;

					//	TRACE("%s, bss %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
					//	printf("%s, bss %s\n", ofile->m_ofilename->c_str(), globsym->m_name->c_str());
						if (sym == globsym->m_syms[0])
						{
							ASSERT(globsym->setResolvedValue == 0);
							globsym->setResolvedValue = sym->ResolvedValue;
						}
					}
				}
				else if ((pSymbol->n_type & N_TYPE) == N_SETA)
				{
					ASSERT(globsym->setResolvedValue);

					TRACE("%d, SETA %s\n", globsym->m_word, globsym->m_name->c_str());
					printf("%d, SETA %s\n", globsym->m_word, globsym->m_name->c_str());

					sym->ResolvedValue = globsym->setResolvedValue;
					*globsym->m_word++ = pSymbol->n_value;

					// Increase the count (at the first long address of the set)
					long* p = (long*)(globsym->setResolvedValue);
					*p += 1;
				}
				else if ((pSymbol->n_type & N_TYPE) == N_SETT)
				{
					ASSERT(globsym->setResolvedValue);

					TRACE("%d, SETT %s\n", globsym->m_word, globsym->m_name->c_str());
					printf("%d, SETT %s\n", globsym->m_word, globsym->m_name->c_str());

					sym->ResolvedValue = globsym->setResolvedValue;
					*globsym->m_word++ = (long)pOFile->m_textdata + pSymbol->n_value;

					// Increase the count (at the first long address of the set)
					long* p = (long*)(globsym->setResolvedValue);
					*p += 1;
				}
				else if ((pSymbol->n_type & N_TYPE) == N_SETD)
				{
					ASSERT(globsym->setResolvedValue);
					TRACE("%d, SETD %s\n", globsym->m_word, globsym->m_name->c_str());
					printf("%d, SETD %s\n", globsym->m_word, globsym->m_name->c_str());

					sym->ResolvedValue = globsym->setResolvedValue;
					*globsym->m_word++ = (long)pOFile->m_datadata + pSymbol->n_value;

					// Increase the count (at the first long address of the set)
					long* p = (long*)(globsym->setResolvedValue);
					*p += 1;
				}
				else if ((pSymbol->n_type & N_TYPE) == N_SETB)
				{
					ASSERT(globsym->setResolvedValue);

					TRACE("%d, SETB %s\n", globsym->m_word, globsym->m_name->c_str());
					printf("%d, SETB %s\n", globsym->m_word, globsym->m_name->c_str());

					sym->ResolvedValue = globsym->setResolvedValue;
					*globsym->m_word++ = (long)pOFile->m_bssdata + bssoffset;

					// Increase the count (at the first long address of the set)
					long* p = (long*)(globsym->setResolvedValue);
					*p += 1;

					bssoffset += pSymbol->n_value;
				}
			}
			else
			{
				if (sym->ResolvedValue == 0)
				{
					if (globsym->m_defined == 0 && globsym->Value != 0)	// Create a bss entry for it
					{
						uint8* bssdata = new uint8[globsym->Value];
						memset(bssdata, 0, globsym->Value);

						sym->ResolvedValue = (ULONG)bssdata;
						globsym->setResolvedValue = sym->ResolvedValue;

						globsym->m_defined = true;
						globsym->m_syms.push_back(sym);
					}
				}
			}
		}
	}

	Relocate2(0, "text", pOFile->m_textdata, parser, ofile, pOFile);
	Relocate2(1, "data", pOFile->m_datadata, parser, ofile, pOFile);

	return pOFile;
}

OFile2* Linker::Pass1_ObjectFile(StringA* afilename, StringA* ofilename, ISequentialByteStream* file)
{
	OFile2* ofile = new OFile2;
	ofile->m_afilename = afilename;
	ofile->m_ofilename = ofilename;
	ofile->m_file = file;

	Pass1_ObjectFile(ofile);

	return ofile;
}

void Linker::Pass1_ObjectFile(OFile2* ofile)
{
	AOutParser parser;
	parser.Read(ofile->m_file);

	/*
	if (!strcmp(ofile->m_ofilename->c_str(), "__init_list__.o"))
	{
		MessageBeep(-1);
	}
	*/

	//AOutParser* pOFile = &parser;

	int nsymbols = parser.GetNumberOfSymbols();

	//gsymmap::iterator* l2g = new gsymmap::iterator[nsymbols];

//	GlobalSymbol* indr = NULL;

	Symbol* indr = NULL;

	for (int i = 0; i < nsymbols; i++)
	{
	//	const char* symbolname = NULL;
	//	Linker::CSymbol symbol;
	//	symbols.insert(Linker::symbolmap::value_type(symbolname, symbol));

		ObjectSymbol* pSymbol = parser.GetSymbol(i);

		/*
		if (strstr(pSymbol->n_name, "cpucheck"))
		{
			MessageBeep(-1);
		}
		*/

	//	printf("%s\n", pSymbol->n_name);

		if (pSymbol->n_type & N_STAB)
		{
			ofile->m_symbols.push_back(NULL);		
			TRACE("\n");
		}
		else //if ((pSymbol->n_type & N_TYPE) != N_UNDF)
	//	if (!(pSymbol->n_type & (1<<4)))	// !extern
		{
		//	TRACE("%s, %d\n", pSymbol->n_name, pSymbol->n_type);

			/*
			if (!strcmp(pSymbol->n_name, "__ZTI9IAddChild"))
			{
				MessageBeep(-1);
			}
			*/

			Symbol* sym = new Symbol;

			{
/*
			if (	(pSymbol->n_type & N_TYPE) == N_SETA ||
					(pSymbol->n_type & N_TYPE) == N_SETD ||
					(pSymbol->n_type & N_TYPE) == N_SETB ||
					(pSymbol->n_type & N_TYPE) == N_SETT)
			{
				MessageBeep(-1);
			}
*/
				/*
				if (strstr(pSymbol->n_name, "gcc2_compiled"))
				{
					MessageBeep(-1);
				}
				*/
				StringA* symbolname = new StringA(pSymbol->n_name);
				GlobalSymbol* globsym;
				gsymmap_t::iterator symboli = m_globsyms.find(symbolname);
				if (symboli == m_globsyms.end())
				{
					globsym = new GlobalSymbol;
					globsym->m_name = symbolname;

					sym->m_globsym = globsym;
					sym->m_pOFile = ofile;
					ofile->m_symbols.push_back(sym);
					//globsym->m_syms.push_back(sym);

					if (	(pSymbol->n_type & N_TYPE) == N_SETA ||
							(pSymbol->n_type & N_TYPE) == N_SETD ||
							(pSymbol->n_type & N_TYPE) == N_SETB ||
							(pSymbol->n_type & N_TYPE) == N_SETT)
					{
					//	GlobalSymbol* symv = new GlobalSymbol;
#if 0
						globsym->n_type = N_SETV;
#endif

						globsym->m_defined = true;
						globsym->m_syms.push_back(sym);//m_pOFile = ofile;

						ASSERT(m_symbolSets.find(globsym) == m_symbolSets.end());
						m_symbolSets.insert(symsetmap_t::value_type(globsym, Array<Symbol*>()));
					}
					else
					{
						if ((pSymbol->n_type & N_TYPE) != N_UNDF/* || ((pSymbol->n_type & N_EXT) && pSymbol->n_value > 0)*/)
						{
							globsym->m_defined = true;
							globsym->m_syms.push_back(sym);//m_pOFile = ofile;
						}

						/*
						if ((pSymbol->n_type & N_EXT) && pSymbol->n_value > 0)
						{
							globsym->Value = MAX(globsym->Value, pSymbol->n_value);
						}
						*/

						globsym->Value = pSymbol->n_value;
						//globsym->m_defined = (pSymbol->n_type & N_TYPE) != N_UNDF;
		#if 0
						globsym->m_filename = filename;
		#endif
					//	globsym->m_fileoffset = 0;

#if 0
						globsym->n_type = pSymbol->n_type;
#endif
					//	globsym->Value = pSymbol->n_value;
					//	globsym->ordinalHint = importHeader.OrdinalHint;
					//	globsym->importDLL = importDLL;
					//	globsym->publicName = strdup(publicName.c_str());

					//	printf("%d/%s/%s\n", importHeader.OrdinalHint, importName, importDLL);
					}

					m_globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
				}
				else
				{
					globsym = (*symboli).second;

				//	Symbol* sym = new Symbol;
					sym->m_globsym = globsym;
					sym->m_pOFile = ofile;
					ofile->m_symbols.push_back(sym);
				//	globsym->m_syms.push_back(sym);

					if (!((pSymbol->n_type & N_TYPE) == N_SETA ||
							(pSymbol->n_type & N_TYPE) == N_SETD ||
							(pSymbol->n_type & N_TYPE) == N_SETB ||
							(pSymbol->n_type & N_TYPE) == N_SETT))
					{
						if (globsym->m_defined)
						{
							if ((pSymbol->n_type & N_TYPE) != N_UNDF)
							{
								globsym->m_syms.push_back(sym);

							//	if (!strcmp(globsym->m_name->c_str(), "__ZTI9IAddChild"))
							//	{
#if 1
								if (false)
								{
									if (ofile->m_afilename)
									{
										TRACE("%s:", ofile->m_afilename->c_str());
										printf("%s:", ofile->m_afilename->c_str());
									}
									TRACE("%s:", ofile->m_ofilename->c_str());
									printf("%s:", ofile->m_ofilename->c_str());

									TRACE("multiple defined symbol %s in , previous def here ", pSymbol->n_name);
									printf("multiple defined symbol %s in , previous def here ", pSymbol->n_name);

									if (globsym->m_syms.size())
									{
										if (globsym->m_syms[0]->m_pOFile->m_afilename)
										{
											TRACE("%s:", globsym->m_syms[0]->m_pOFile->m_afilename->c_str());
											printf("%s:", globsym->m_syms[0]->m_pOFile->m_afilename->c_str());
										}
										TRACE("%s\n", globsym->m_syms[0]->m_pOFile->m_ofilename->c_str());
										printf("%s\n", globsym->m_syms[0]->m_pOFile->m_ofilename->c_str());
									}
									else
									{
										printf("set\n");
										TRACE("set\n");
									}
								}
#endif
							//	}
							}
						}
						else
						{
							//globsym->m_defined = (pSymbol->n_type & N_TYPE) != N_UNDF;
#if 0
							globsym->n_type = pSymbol->n_type;
#endif

							if ((pSymbol->n_type & N_EXT) && pSymbol->n_value > 0)
							{
								globsym->Value = MAX(globsym->Value, pSymbol->n_value);
							}

						//	globsym->Value = MAX(globsym->Value, pSymbol->n_value);

							if ((pSymbol->n_type & N_TYPE) != N_UNDF)
							{
								globsym->m_defined = true;
								globsym->m_syms.push_back(sym);
#if 0
								globsym->m_pOFile = ofile;
#endif
							}
						}
					}
					else
					{
						if (((pSymbol->n_type & N_TYPE) == N_SETA ||
								(pSymbol->n_type & N_TYPE) == N_SETD ||
								(pSymbol->n_type & N_TYPE) == N_SETB ||
								(pSymbol->n_type & N_TYPE) == N_SETT))
						{
							if (globsym->m_defined)
							{
#if 0
								if (ofile->m_afilename)
								{
									TRACE("%s:", ofile->m_afilename->c_str());
									printf("%s:", ofile->m_afilename->c_str());
								}
								TRACE("%s:", ofile->m_ofilename->c_str());
								printf("%s:", ofile->m_ofilename->c_str());

								TRACE("multiple defined symbol %s in , previous def here ", pSymbol->n_name);
								printf("multiple defined symbol %s in , previous def here ", pSymbol->n_name);

								if (globsym->m_pOFile->m_afilename)
								{
									TRACE("%s:", globsym->m_pOFile->m_afilename->c_str());
									printf("%s:", globsym->m_pOFile->m_afilename->c_str());
								}
								TRACE("%s\n", globsym->m_pOFile->m_ofilename->c_str());
								printf("%s\n", globsym->m_pOFile->m_ofilename->c_str());
#endif
								globsym->m_syms.push_back(sym);	// ??
							}
							else
							{
								globsym->m_defined = true;
								globsym->m_syms.push_back(sym);

#if 0
								globsym->n_type = N_SETV;
#endif

								ASSERT(m_symbolSets.find(globsym) == m_symbolSets.end());
								m_symbolSets.insert(symsetmap_t::value_type(globsym, Array<Symbol*>()));
							}
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
			if (indr)
			{
				indr->m_pIndirect = sym;
			}

			if ((pSymbol->n_type & N_TYPE) == N_INDR)
				indr = sym;
			else
				indr = NULL;
		}
	}
}

#if 0
void Linker::Pass1_ArchiveObjectFile(OFile2* ofile, gsymmap_t archsyms)
{
	if (ofile->m_bAdded)
		return;

	ofile->m_bAdded = true;

	m_objectFiles.Add(ofile);

	AOutParser parser;
	parser.Read(ofile->m_file);
	int nsymbols = parser.GetNumberOfSymbols();
	for (int i = 0; i < nsymbols; i++)
	{
		ObjectSymbol* pSymbol = parser.GetSymbol(i);

		if (pSymbol->n_type & N_STAB)
		{
			TRACE("\n");
		}
		else
		{
			/*
			if (	(pSymbol->n_type & N_TYPE) == N_SETA ||
					(pSymbol->n_type & N_TYPE) == N_SETD ||
					(pSymbol->n_type & N_TYPE) == N_SETB ||
					(pSymbol->n_type & N_TYPE) == N_SETT)
			{
			}
			else
			*/
			{
				StringA* symbolname = new StringA(pSymbol->n_name);
			//	GlobalSymbol* globsym;
				gsymmap_t::iterator symbolit = m_globsyms.find(symbolname);
				if (symbolit == m_globsyms.end())
				{
					symbolit = archsyms.find(symbolname);
					if (symbolit != archsyms.end())
					{
						ASSERT((*symbolit).second->m_defined);
						m_globsyms.insert(gsymmap_t::value_type((*symbolit).second->m_name, (*symbolit).second));

						Pass1_ArchiveObjectFile((*symbolit).second->m_pOFile, archsyms);
					}
					else
					{
						GlobalSymbol* globsym = new GlobalSymbol;
						globsym->m_name = symbolname;

						if (	(pSymbol->n_type & N_TYPE) == N_SETA ||
								(pSymbol->n_type & N_TYPE) == N_SETD ||
								(pSymbol->n_type & N_TYPE) == N_SETB ||
								(pSymbol->n_type & N_TYPE) == N_SETT)
						{
						//	GlobalSymbol* symv = new GlobalSymbol;
							globsym->n_type = N_SETV;

							m_symbolSets.insert(symsetmap_t::value_type(globsym, Array<GlobalSymbol*>()));
						}
						else
						{
							if ((pSymbol->n_type & N_TYPE) != N_UNDF)
							{
								globsym->m_pOFile = ofile;
							}

							globsym->m_defined = (pSymbol->n_type & N_TYPE) != N_UNDF;

							globsym->n_type = pSymbol->n_type;
						}

						m_globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
					}
				}
			}
		}
	}
}
#endif

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

			/*
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
			*/
			{

				// TODO. doesn't need to load all object files in archive
				map<ULONG,int> offsetmap;
				Array<OFile2*> objectfiles;
				{
					for (int i = 0; i < arch.m_members.size(); i++)
					{
					//	TRACE("%s: %s %d, %d\n", filename->c_str(), arch.m_members[i].name->c_str(), arch.m_members[i].Offset, arch.m_members[i].Size);

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

					//	m_objectFiles.Add(ofile);
					//	delete[] data;
					}
				}

				//gsymmap_t archsyms;

#if 0
				{
					for (int i = 0; i < arch.m_nsymboldefs; i++)
					{
						const char* symname = arch.m_strbuffer + arch.m_symdefs[i].nameindex;

						int index = offsetmap[arch.m_symdefs[i].fileoffset+sizeof(ArchiveHeader)];

						OFile2* ofile = objectfiles[index];

						if (strstr(symname, "cpucheck"))
						{
							/*
							file->Seek(arch.m_members[i].Offset, System::IO::STREAM_SEEK_SET);

							uint8* data = new uint8[arch.m_members[i].Size];
							file->Read(data, arch.m_members[i].Size);
							MemoryByteStream* mem = new MemoryByteStream(data, arch.m_members[i].Size);
*/
							Pass1_ObjectFile(ofile);
						}

						GlobalSymbol* globsym = new GlobalSymbol;
						globsym->m_name = new StringA(symname);
						//globsym->m_pOFile = ofile;
						globsym->m_defined = true;

						//archsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
					}
				}
#endif

#if 0
				// Scan through symbols to find symbols that so far have been referenced but not defined

				{
					for (int i = 0; i < arch.m_nsymboldefs; i++)
					{
						const char* symname = arch.m_strbuffer + arch.m_symdefs[i].nameindex;

					//	TRACE("%s\n", symname);

						int index = offsetmap[arch.m_symdefs[i].fileoffset+sizeof(ArchiveHeader)];

						StringA* symbolname = new StringA(symname);

						gsymmap_t::iterator symbolit = m_globsyms.find(symbolname);
						if (symbolit != m_globsyms.end())
						{
							GlobalSymbol* globsym = (*symbolit).second;

							if (!globsym->m_defined)
							{
								OFile2* ofile = objectfiles[index];

								globsym->m_defined = true;
								globsym->m_pOFile = ofile;
								ASSERT(globsym->m_pOFile);

								Pass1_ArchiveObjectFile(ofile, archsyms);

								//Pass1_ObjectFile(ofile->m_afilename, ofile->m_ofilename, ofile->m_file);
							//	/*OFile2* ofile2 =*/ Pass1_ObjectFile(ofile->m_afilename, ofile->m_ofilename, ofile->m_file, globsyms);

								// ??
							//	m_objectFiles.Add(globsym->m_pOFile);
							}
						}
					}
				}
#endif
#if 0

				// Another pass
				{
					for (int i = 0; i < arch.m_nsymboldefs; i++)
					{
						const char* symname = arch.m_strbuffer + arch.m_symdefs[i].nameindex;

						int index = offsetmap[arch.m_symdefs[i].fileoffset+sizeof(ArchiveHeader)];

						StringA* symbolname = new StringA(symname);

						gsymmap_t::iterator symbolit = m_globsyms.find(symbolname);
						if (symbolit == m_globsyms.end())
						{
							GlobalSymbol* globsym = new GlobalSymbol;

							globsym->m_name = symbolname;
							globsym->m_pOFile = objectfiles[index];

							globsym->defined = true;

							m_globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
						}
						else
						{
							GlobalSymbol* globsym = (*symbolit).second;

							ASSERT(globsym->defined);	// Should've been done in previous

							/*
							if (!globsym->defined)
							{
								OFile2* ofile = objectfiles[index];

								globsym->defined = true;
								globsym->m_pOFile = ofile;
								ASSERT(globsym->m_pOFile);
							}
							*/
						}
					}
				}
#endif

				//map<ULONG,int> offsetmap;
			//	Array<OFile2*> objectfiles;
				map<StringA*,OFile2*, Ref_Less<StringA> > members;
				{
					for (int i = 0; i < arch.m_members.size(); i++)
					{
					//	TRACE("%s: %s %d, %d\n", filename->c_str(), arch.m_members[i].name->c_str(), arch.m_members[i].Offset, arch.m_members[i].Size);

						//offsetmap[arch.m_members[i].Offset] = i;

						file->Seek(arch.m_members[i].Offset, System::IO::STREAM_SEEK_SET);

						uint8* data = new uint8[arch.m_members[i].Size];
						file->Read(data, arch.m_members[i].Size);
						MemoryByteStream* mem = new MemoryByteStream(data, arch.m_members[i].Size);

						/*
						ASSERT(members.find(arch.m_members[i].name) == members.end());

						if (strstr(arch.m_members[i].name->c_str(), "dos"))
						{
							MessageBeep(-1);
						}
						*/

						OFile2* ofile = new OFile2;
						ofile->m_afilename = filename;
						ofile->m_ofilename = arch.m_members[i].name;
						ofile->m_file = mem;

						members[ofile->m_ofilename] = ofile;

					//	objectfiles.Add(ofile);

						Pass1_ObjectFile(ofile);
						m_objectFiles.Add(ofile);

#if 0
						{
							AOutParser parser;
							parser.Read(ofile->m_file);
							int nsymbols = parser.GetNumberOfSymbols();
							for (int i = 0; i < nsymbols; i++)
							{
								ObjectSymbol* pSymbol = parser.GetSymbol(i);

								TRACE("%s\n", pSymbol->n_name);

								StringA* symbolname = new StringA(pSymbol->n_name);

								gsymmap_t::iterator symbolit = m_globsyms.find(symbolname);
								if (symbolit == m_globsyms.end())
								{
								//	pSymbol->n_type
									GlobalSymbol* globsym = new GlobalSymbol;

								//	globsym->m_filename = filename;
								//	globsym->m_fileoffset = arch.m_symdefs[i].fileoffset;

									globsym->m_name = symbolname;
									globsym->m_pOFile = objectfiles[index];

								//	TRACE("%s:%s\n", globsym->m_pOFile->m_ofilename->c_str(), symname);

								//	globsym->Value = 0;
									globsym->m_defined = true;	// ??
								//	globsym->ordinalHint = importHeader.OrdinalHint;
								//	globsym->importDLL = importDLL;
								//	globsym->publicName = strdup(publicName.c_str());

								//	printf("%d/%s/%s\n", importHeader.OrdinalHint, importName, importDLL);

									m_globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
								}
								else
								{
									GlobalSymbol* globsym = (*symbolit).second;

									if (globsym->m_defined)
									{
										printf("multiple defined symbol %s\n", symname);
										TRACE("multiple defined symbol %s\n", symname);
										//ASSERT(0);	// TODO remove
									}
									else
									{
										globsym->m_pOFile = objectfiles[index];
										globsym->m_defined = true;
										//m_objectFiles.Add(ofile);
									}
								}
							}
						}
#endif

					//	m_objectFiles.Add(ofile);
					//	delete[] data;
					}
				}
				for (int i = 0; i < arch.m_nsymboldefs; i++)
				{
					const char* symname = arch.m_strbuffer + arch.m_symdefs[i].nameindex;
					//TRACE("%d\n", );
					if (strstr(symname, "cpucheck"))
					{
						MessageBeep(-1);
					}
				}
#if 0

					int index = offsetmap[arch.m_symdefs[i].fileoffset+sizeof(ArchiveHeader)];

					StringA* symbolname = new StringA(symname);

					gsymmap_t::iterator symbolit = m_globsyms.find(symbolname);
					if (symbolit == m_globsyms.end())
					{
					//	pSymbol->n_type
						GlobalSymbol* globsym = new GlobalSymbol;

					//	globsym->m_filename = filename;
					//	globsym->m_fileoffset = arch.m_symdefs[i].fileoffset;

						globsym->m_name = symbolname;
						globsym->m_pOFile = objectfiles[index];

					//	TRACE("%s:%s\n", globsym->m_pOFile->m_ofilename->c_str(), symname);

					//	globsym->Value = 0;
						globsym->m_defined = true;	// ??
					//	globsym->ordinalHint = importHeader.OrdinalHint;
					//	globsym->importDLL = importDLL;
					//	globsym->publicName = strdup(publicName.c_str());

					//	printf("%d/%s/%s\n", importHeader.OrdinalHint, importName, importDLL);

						m_globsyms.insert(gsymmap_t::value_type(globsym->m_name, globsym));
					}
					else
					{
						GlobalSymbol* globsym = (*symbolit).second;

						if (globsym->m_defined)
						{
							printf("multiple defined symbol %s\n", symname);
							TRACE("multiple defined symbol %s\n", symname);
							//ASSERT(0);	// TODO remove
						}
						else
						{
							globsym->m_pOFile = objectfiles[index];
							globsym->m_defined = true;
							//m_objectFiles.Add(ofile);
						}
					}
				}
#endif
			}
		}
		else if (filename->c_str()[len-1] == 'o')
		{
			OFile2* ofile = Pass1_ObjectFile(NULL, filename, file);
			m_objectFiles.Add(ofile);
		}

		//file->Close();
	}

	m_textsize = 4096*10;//m_symbolSets.size()*4;
	m_textdata = new uint8[m_textsize];
	memset(m_textdata, 0, m_textsize);
}

/*
void Linker::set()
{
}
*/

void Linker::sets()
{
	// N_SETV symbol points

	/*
The address of the set is made into an N_SETV symbol
whose name is the same as the name of the set.
This symbol acts like a N_DATA global symbol
in that it can satisfy undefined external references.  */

	ULONG* word = (ULONG*)m_textdata;

	symsetmap_t::iterator it = m_symbolSets.begin();
	while (it != m_symbolSets.end())
	{
		GlobalSymbol* globsym = (*it).first;

		int count = (*it).second.size();

		//GlobalSymbol* globsym = m_globsyms[(*it).first];
		globsym->setResolvedValue = (long)word;
	//	long nsize = (*it).second.size();

		TRACE("%d %s %d\n", globsym->setResolvedValue, globsym->m_name->c_str(), count);
		printf("%d %s %d\n", globsym->setResolvedValue, globsym->m_name->c_str(), count);

		*word++ = 0;	// initialize count
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
		*word++ = 0;	// null terminated

		++it;
	}
}

}	// System
