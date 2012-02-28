#include "stdafx.h"
#include "CreateObjectFileParser.h"
#include "AOut.h"
#include "coff.h"
#include "stab.h"
#include "AmigaHunkParser.h"
#include "CodeView.h"
#include "Microsoft/cvinfo.h"

namespace System
{
using namespace std;
using namespace IO;

ObjectFileParser* CreateObjectFileParser(IO::Stream& pStream)
{
	uint32 buf[4];
	ULONG nread = pStream.Read(buf, 16);

	pStream.Seek(-16, IO::STREAM_SEEK_CUR);

#if 0
	if (nread >= 4 && buf[0] == BigEndian32(JAVA_MAGIC))
	{
#if 0
// "C:\FileFormatSpecs\MPEG4-XMT\C036555e Electornic inserts\systems\xmt\xmto\XmtO2A$1.class"

		CJavaClassFile javaclassfile;
		javaclassfile.Parse(fp);

		if (javaclassfile.m_access_flags & ACC_PUBLIC)
		{
			printf("public ");
		}

		if (javaclassfile.m_access_flags & ACC_INTERFACE)
		{
			ASSERT(javaclassfile.m_access_flags & ACC_ABSTRACT);
			printf("interface ");
		}
		else
		{
			printf("class ");
		}

		uint16 classNameIndex = javaclassfile.m_pool_array[javaclassfile.m_this_class-1].classData.name_index;
		BSTR className = javaclassfile.m_pool_array[classNameIndex-1].bstr;

		printf("%S", className);

		if (javaclassfile.m_super_class)
		{
			uint16 classNameIndex = javaclassfile.m_pool_array[javaclassfile.m_super_class-1].classData.name_index;
			BSTR className = javaclassfile.m_pool_array[classNameIndex-1].bstr;

			printf(" extends %S", className);
		}

		for (int i = 0; i < javaclassfile.m_interfaces_count; i++)
		{
			printf("\nimplements");
		}

		printf("\n{\n");

		for (i = 0; i < javaclassfile.m_fields_count; i++)
		{
			BSTR fieldDescriptor = javaclassfile.m_pool_array[javaclassfile.m_fields[i]->m_descriptor_index-1].bstr;
			printf("\t%S ", fieldDescriptor);

			BSTR fieldName = javaclassfile.m_pool_array[javaclassfile.m_fields[i]->m_name_index-1].bstr;
			printf("\t%S;\n", fieldName);
		}

		printf("\n");

		for (i = 0; i < javaclassfile.m_methods_count; i++)
		{
			BSTR methodName = javaclassfile.m_pool_array[javaclassfile.m_methods[i]->m_name_index-1].bstr;
			printf("\t%S", methodName);

			BSTR methodDescriptor = javaclassfile.m_pool_array[javaclassfile.m_methods[i]->m_descriptor_index-1].bstr;
			printf("\t%S", methodDescriptor);

			printf("\n");
		}

		printf("}\n");
#endif
	}
	else if (nread >= 16 && memcmp(buf, "XPCOM\nTypeLib\r\n\032", 16)==0)
	{
#if 0
//"C:\Program Files\Mozilla Firefox\components\browser.xpt"
		IXPTypeLib* pTypeLib;
		XPTypeLibParse(fp, &pTypeLib);
		if (pTypeLib)
		{
			long nifaces = pTypeLib->GetIFaceCount();

			for (int i = 0; i < nifaces; i++)
			{
				IXPIFaceInfo* pIFace;
				pTypeLib->GetIFace(i, &pIFace);

				CComBSTR name;
				pIFace->GetName(&name);

				printf("interface %S\n{\n", (BSTR)name);

				LPXPIFACEATTR ifaceattr;
				pIFace->GetIFaceAttr(&ifaceattr);

				for (int f = 0; f < ifaceattr->cFuncs; f++)
				{
					XPFUNCDESC* pFuncDesc;
					pIFace->GetFuncDesc(f, &pFuncDesc);
					if (pFuncDesc)
					{
						printf("\t%S()\n", pFuncDesc->name);

						pIFace->ReleaseFuncDesc(pFuncDesc);
					}
				}

				pIFace->ReleaseIFaceAttr(ifaceattr);

				printf("}\n");
			}

			delete pTypeLib;
		}
#endif
	}
	else
#endif
		if (nread >= 4 && BigEndian32(((HUNK_Header*)buf)->ID) == HUNK_HEADER)
	{
	//	printf("AmigaDOS Hunk\n");

		AmigaHunkParser* pParser = new AmigaHunkParser;

		return pParser;
#if 0

		fseek(fp, 0, SEEK_END);
		long filesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		HUNK_Header header;
		fread(&header, 1, sizeof(HUNK_Header), fp);

		int totalhunks = ENDIANLONG(header.num_hunks);
		int n = ENDIANLONG(header.pad0);
		int first = ENDIANLONG(header.pad2);
		int last = ENDIANLONG(header.pad3);

		printf("n: %d\n", n);
		printf("Number of HUNKS: %d\n", totalhunks);
		printf("first: %d\n", first);
		printf("last: %d\n", last);

		hunkvector Hunks;
		for (int i = 0; i < totalhunks; i++)
		{
			CHunk hunk;
			hunk.m_size = fget32(fp);

			Hunks.push_back(hunk);

			printf("\thunk size: %d bytes\n", hunk.m_size*4);
		}

		int nhunk = 0;
	//	for (i = 0; i < totalhunks; i++)

		while (1)
		{
		//	CHunk& hunk = Hunks[nhunk];

			ULONG hunk_ID = fget32(fp);
		//	if (hunk_ID == HUNK_END)
		//		break;

			char * str = GetHunkStr(hunk_ID);

			printf("%s\n", str);

			long pos = ftell(fp);
			if (pos >= filesize)
				break;

			if ((hunk_ID & ID_MASK) == HUNK_CODE)
			{
				ULONG codelongs = fget32(fp);
			//	ASSERT(codelongs == hunk.m_size);

				BYTE* data = new BYTE[codelongs*4];
				if (data)
				{
					fread(data, 1, codelongs*4, fp);

					ULONG size = min(codelongs*4, 4096);
					pass2_CODE(data, size, NULL);//0, NULL);
					delete [] data;
				}
			}
			else if ((hunk_ID & ID_MASK) == HUNK_RELOC32)
			{
				ULONG	offsets = fget32(fp);

				while (offsets)
				{
					ULONG hunk_number = fget32(fp);
					printf("hunk_number: %d\n", hunk_number);

					for (int i = 0; i < offsets; i++)
					{
						ULONG offset = fget32(fp);
					//	printf("\toffset: %d\n", offset);
					}

					offsets = fget32(fp);
				}
			}
			else if ((hunk_ID & ID_MASK) == HUNK_DATA)
			{
				ULONG longs = fget32(fp);
				fseek(fp, longs*4, SEEK_CUR);

				printf("\t%d bytes\n", longs*4);
			}
			else if ((hunk_ID & ID_MASK) == HUNK_SYMBOL)
			{
			//	ULONG longs = fget32(fp);
				ULONG	size = fget32(fp);//*hunk_ptr++;

				while (size)
				{
					printf("size: %d\n", size);
			#if 0
					struct SymbolNode	*symnode;

					if (symnode = malloc(sizeof(struct SymbolNode)))
					{
						symnode->SymPtr = hunk_ptr-1;
						AddTail((struct List *)&SymbolList, (struct Node *)symnode);
					}
			#endif
				//	long v = fget(fp);
					long s[2000];
					//s[0] = size;
					fread(s, size*4+4, 1, fp);
				//	fseek(fp, size*4, SEEK_CUR);

				//	fseek(fp, size*4, SEEK_CUR);

				//	long poff = ENDIANLONG(*s);
					long offset = ENDIANLONG(s[size]);
				//	long offset = fget32(fp);
					printf("%s / offset: %x\n", (char*)s, offset);

				//	fget32(fp);

				//	hunk_ptr += size;
				//	hunk_ptr++;

					size = fget32(fp);//*hunk_ptr++;
				}

			}
			else if ((hunk_ID & ID_MASK) == HUNK_BSS)
			{
				ULONG longs = fget32(fp);
			}
			else if ((hunk_ID & ID_MASK) == HUNK_DEBUG ||
					(hunk_ID & HUNKF_ADVISORY))	// Can be skipped
			{
				ULONG longs = fget32(fp);
				fseek(fp, longs*4, SEEK_CUR);

				printf("size: %d(%x)\n", longs*4, longs*4);
			}
			else
			{
				printf("Unrecognized hunk %x\n", hunk_ID);
			}
			/*
			else
			{
				ULONG longs = fget32(fp);
				fseek(fp, longs*4, SEEK_CUR);
			}
			*/

		//	fseek(fp, pos+4+Hunks[i].m_size*4, SEEK_SET);

#if 0
		//	ULONG size = fget32(fp);

			switch (hunk_ID & ID_MASK)
			{
			case HUNK_DREL8:
			case HUNK_DREL16:
			case HUNK_DREL32:
			case HUNK_RELOC8:
			case HUNK_RELOC16:
			case HUNK_RELOC32:
				hunk_ptr = pass1_RELOC(hunk_ID, hunk_ptr);
				break;
				
			case HUNK_EXT:
				hunk_ptr = pass1_EXT(hunk_ID, hunk_ptr);
				break;
				
			case HUNK_SYMBOL:
				hunk_ptr = pass1_SYMBOL(hunk_ID, hunk_ptr);
				break;
				
			case HUNK_UNIT:
			case HUNK_NAME:
			case HUNK_CODE:
			case HUNK_DATA:
			case HUNK_BSS:
			case HUNK_DEBUG:
				hunk_ptr = pass1_HUNK_X(hunk_ID, hunk_ptr);
				break;
				
			case HUNK_END:
				hunksofar++;
				break;
				
			default:
				if (hunk_ID & HUNKF_ADVISORY)	// Can be skipped
				{
					hunk_ptr = pass1_HUNK_X(hunk_ID, hunk_ptr);
				}
				else
				{
					fprintf(stderr, "Hunk not recognized: %8lX", hunk_ID & ID_MASK);
					hunk_ptr = NULL;	// End this loop
					error = 1;
				}
			}
#endif

		//	BYTE* buffer = new BYTE[size];
			/*
			if (buffer == NULL)
			{
				printf("Out of memory\n");
				return -1;
			}

			fread(buffer, 1, size, fp);
			*/
		//	ULONG	*hunk_start = hunk_ptr;
		//	ULONG	hunk_ID = *hunk_ptr++;
		}
#endif
	}
	else if (nread >= 16 && (
		N_GETMAGIC((exec*)buf) == A_MAGIC ||  /* 68020 */
		N_GETMAGIC((exec*)buf) == I_MAGIC ||  /* intel 386 */
		N_GETMAGIC((exec*)buf) == J_MAGIC ||  /* intel 960 */
		N_GETMAGIC((exec*)buf) == K_MAGIC ||  /* sparc */
		N_GETMAGIC((exec*)buf) == V_MAGIC ||  /* mips 3000 */
		N_GETMAGIC((exec*)buf) == X_MAGIC ||  /* att dsp 3210 */
		N_GETMAGIC((exec*)buf) == M_MAGIC ||  /* mips 4000 */
		N_GETMAGIC((exec*)buf) == D_MAGIC ||  /* amd 29000 */
		N_GETMAGIC((exec*)buf) == E_MAGIC ||  /* arm 7-something */
		N_GETMAGIC((exec*)buf) == Q_MAGIC ||  /* powerpc */
		N_GETMAGIC((exec*)buf) == N_MAGIC ||  /* mips 4000-le */
		N_GETMAGIC((exec*)buf) == L_MAGIC))  /* dec alpha */
	{
		AOutParser* pObjectFileParser = new AOutParser;
		return pObjectFileParser;

#if 0
		printf("a.out\n");
		pObjectFileParser->Read(fp);

		{
			ULONG TextSize = pObjectFileParser->GetTextSize();
			BYTE* TextData = pObjectFileParser->GetText();

			int cpu = pObjectFileParser->GetCPU();
			if (cpu == CPU_68K)
			{
#if 0
				pass2_CODE(TextData, TextSize, pObjectFileParser);//0, NULL);
#endif
			}
			else if (cpu == CPU_IX86)
			{
				ReadCode_x86(0, TextData, TextSize);
			}
			else
			{
				ASSERT(0);
			}
		}

		{
			ULONG DataSize = pObjectFileParser->GetDataSize();
			BYTE* DataData = pObjectFileParser->GetData();

			printf("Data Size: %d\n", DataSize);

			int nsymbols = pObjectFileParser->GetNumberOfSymbols();

			for (int datai = 0; datai < DataSize; datai++)
			{
				//ObjectSymbol* symnode = NULL;//symnode = FindSymbol(counter);
				{
					for (int i = 0; i < nsymbols; i++)
					{
						ObjectSymbol* pSymbol = pObjectFileParser->GetSymbol(i);

						if ((pSymbol->n_type & N_TYPE) == N_DATA)
						{
							if (pSymbol->n_value == datai)
							{
							//	symnode = pSymbol;//&Symbols[i];
								printf("\n%s:\n", pSymbol->n_name);
							//	break;
							}
						}
					}
				}

				//if (symnode)
				{
				//;printf("%.*s:\n", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
				}

				printf("%2.2X", DataData[datai]);
			}

			printf("\n");
		}

		int nsymbols = pObjectFileParser->GetNumberOfSymbols();

		{
			printf("Text Relocs:\n");

			int nrelocations = pObjectFileParser->GetNumberOfRelocations();

			for (int i = 0; i < nrelocations; i++)
			{
				Relocation* pRelocation = pObjectFileParser->GetRelocation(i);

				printf("\t");

				if (!pRelocation->r_extern)
				{
					if (pRelocation->r_symbolnum == N_TEXT)
					{
						printf("type: text\t");
					}
					else if (pRelocation->r_symbolnum == N_DATA)
					{
						printf("type: data\t");
					}
					else
					{
						printf("Unknown type\t");
					}
				}
				else
				{
					ObjectSymbol* pSymbol = pObjectFileParser->GetSymbol(pRelocation->r_symbolnum);
					if (pSymbol)
					{
						printf("symbol: %s(%d)\t", pSymbol->n_name, pRelocation->r_symbolnum);
					}
				}

				printf("addr: %d", pRelocation->r_address);

				printf("\n");
			}
		}

		{
			printf("Symbols:\n");

			int brace = 0;

			for (int i = 0; i < nsymbols; i++)
			{
				ObjectSymbol* pSymbol = pObjectFileParser->GetSymbol(i);

				if (pSymbol->n_type >= 0x20)
				{
					if (pSymbol->n_type == N_RBRAC)
					{
						brace--;
					}

					for (int j = 0; j < brace; j++)
						printf("  ");

					if (pSymbol->n_type == N_SO)
					{
						printf("SourceFile: %s / start address: %x\n", pSymbol->n_name, pSymbol->n_value);
					}
					else if (pSymbol->n_type == N_FUN)
					{
						printf("function %s / address: %x\n", pSymbol->n_name, pSymbol->n_value);

					// the start of the function is in the next N_SLINE symbol.
					}
					else if (pSymbol->n_type == N_LSYM)
					{
						printf("stack: %s\n", pSymbol->n_name);
					}
					else if (pSymbol->n_type == N_RSYM)
					{
						printf("register: %s\n", pSymbol->n_name);
					}
					else if (pSymbol->n_type == N_PSYM)
					{
						printf("parameter: %s\n", pSymbol->n_name);
					}
					else if (pSymbol->n_type == N_LBRAC)
					{
						brace++;
						printf("{\n");
					}
					else if (pSymbol->n_type == N_RBRAC)
					{
						printf("}\n");
					}
					else if (pSymbol->n_type == N_SLINE)
					{
						printf("line number: %d, address: %x\n", pSymbol->n_desc, pSymbol->n_value);
					}
					else
					{
						printf("unk stab: %x\n", pSymbol->n_type);
					}

					/*
					if (pSymbol->n_type != N_RSYM)
					{
						for (int j = 0; j < brace; j++)
							printf("  ");
					}
					*/
				}
				else
				{
					int external = pSymbol->n_type & N_EXT;
					int type = pSymbol->n_type & N_TYPE;
					char* strtype;
					if (type == N_TEXT)
						strtype = "text";
					else if (type == N_DATA)
						strtype = "data";
					else if (type == N_UNDF)
						strtype = "undefined";
					else
						ASSERT(0);

					printf("\ttype: %s\texternal: %d value: %d\t%s\n", strtype, external, pSymbol->n_value, pSymbol->n_name);
				}
			}
		}

		delete pObjectFileParser;
#endif
	}
	else if (nread >= 8 && memcmp(buf, "!<arch>\n", 8) == 0)
	{
		printf("Archive (Library) Format\n");

#if 0
		CArchFile arch;
		arch.Load(fp);
#endif
#if 0
		typedef map<std::string,DWORD> symbolmap;

		symbolmap symbols;

		BYTE signature[8];
		fread(signature, 1, 8, fp);

		int linkerMember = 0;

		while (!feof(fp))
		{
			ArchiveHeader header;
			if (fread(&header, 1, sizeof(header), fp) != sizeof(header))
			{
				break;
			}

			if (header.End[0] != 0x60 || header.End[1] != '\n')
			{
				printf("Corrupt file\n");
				return -1;
			}

			DWORD Size = header.GetHeaderSize();

			long startpos = ftell(fp);

			//printf("Member Name: %.16s\n", header.Name);

			if (header.Name[0] == '/')
			{
				if (header.Name[1] == '/')
				{
					printf("");
				}
				else
				{
					if (linkerMember == 0)
					{
						DWORD NumberOfSymbols = fget32(fp);
					//	fread(&NumberOfSymbols, 1, 4, fp);
						DWORD* Offsets = new DWORD[NumberOfSymbols];

						int i;

						for (i = 0; i < NumberOfSymbols; i++)
						{
							Offsets[i] = fget32(fp);//, 1, NumberOfSymbols*4, fp);
						}

						for (i = 0; i < NumberOfSymbols; i++)
						{
							StringA str;
							while (!feof(fp))
							{
								int c = fgetc(fp);
								if (c == 0)
									break;

								str += c;
							}
							printf("%s\n", str.c_str());

							symbols.insert(symbolmap::value_type(str, Offsets[i]));
						}

						linkerMember = 1;
					}
				}
			}

			if (ftell(fp) > startpos + Size)
			{
				printf("Read past archive member\n");
			}
			if (Size & 1) Size += 1;	// even
			fseek(fp, startpos + Size, SEEK_SET);
		}
#endif

#if 0
		symbolmap::iterator symi = symbols.find("__imp__MessageBoxA@16");
		if (symi != symbols.end())
		{
			DWORD Offset = (*symi).second;
			printf("%d", Offset);

			fseek(fp, Offset, SEEK_SET);

			ArchiveHeader header;
			if (fread(&header, 1, sizeof(header), fp) != sizeof(header))
			{
			//	break;
			}
			DWORD Size = header.GetHeaderSize();


			WORD Sig[2];
			fread(Sig, 1, 4, fp);

			if (Sig[0] == IMAGE_FILE_MACHINE_UNKNOWN && Sig[1] == 0xffff)
			{
				ImportHeader importHeader;
				fread(&importHeader, 1, sizeof(importHeader), fp);
				BYTE Type = importHeader.Flags & 0x3;
				BYTE NameType = (importHeader.Flags>>2)&0x7;

				char* data = new char[importHeader.SizeOfData];

				fread(data, 1, importHeader.SizeOfData, fp);

				char* importName = data;
				char* importDLL = data + strlen(data) + 1;
			}
			else
			{
				ASSERT(0);
			}
		}
#endif
	}
#if WIN32
	else if (nread >= 2 && *(uint16*)buf == IMAGE_DOS_SIGNATURE)
	{
		COFFParser* pImage = new COFFParser;

		return pImage;
	}
	else if (nread >= 2 && (
		*(uint16*)buf == IMAGE_FILE_MACHINE_UNKNOWN ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_ALPHA ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_ARM ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_ALPHA64 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_I386 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_IA64 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_M68K ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_MIPS16 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_MIPSFPU ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_MIPSFPU16 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_POWERPC ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_R3000 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_R4000 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_R10000 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_SH3 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_SH4 ||
		*(uint16*)buf == IMAGE_FILE_MACHINE_THUMB))
	{
		COFFParser* pImage = new COFFParser;

		return pImage;
	}
#endif
#if 0
	else if (nread >= 8 && (
		(((PEFContainerHeader*)buf)->tag1 == ENDIANLONG('Joy!')) &&
		(((PEFContainerHeader*)buf)->tag2 == ENDIANLONG('peff'))
		)
		)
	{
		ASSERT(0);
#if 0
		PEFContainerHeader pefh;
		fread(&pefh, 1, sizeof(pefh), fp);
		pefh.architecture = ENDIANLONG(pefh.architecture);
		pefh.sectionCount = ENDIANWORD(pefh.sectionCount);

		printf("PEFF (Mac)\n");

		if (pefh.architecture == 'pwpc')
			printf("pwpc");
		else if (pefh.architecture == 'm68k')
			printf("m68k");
		else
			printf("Unknown architecture");
		printf("\n");

		PEFSectionHeader** pSections = new PEFSectionHeader*[pefh.sectionCount];
		{
			for (int i = 0; i < pefh.sectionCount; i++)
			{
				PEFSectionHeader* pSection = new PEFSectionHeader;
				pSections[i] = pSection;
				fread(pSection, 1, sizeof(PEFSectionHeader), fp);

				pSection->nameOffset = ENDIANLONG(pSection->nameOffset);
				pSection->containerOffset = ENDIANLONG(pSection->containerOffset);
				pSection->unpackedSize = ENDIANLONG(pSection->unpackedSize);
			}
		}

		filesize -= pefh.sectionCount*sizeof(PEFSectionHeader) + sizeof(PEFContainerHeader);
		BYTE* filedata = new BYTE[filesize];
		fread(filedata, 1, filesize, fp);

		{
			for (int i = 0; i < pefh.sectionCount; i++)
			{
				PEFSectionHeader* pSection = pSections[i];

				printf("Section #%d", i+1);

				if (pSection->nameOffset != -1)
				{
					printf("%s", filedata + pSection->nameOffset);
				}
				printf("\n");

				switch (pSection->sectionKind)
				{
				case 0:
					{
						printf("Code\n");

						BYTE* textOffset = filedata - pefh.sectionCount*sizeof(PEFSectionHeader) - sizeof(PEFContainerHeader) + pSection->containerOffset;
						cpp::dasm_powerpc(textOffset, 0, min(pSection->unpackedSize, 50), 0, NULL);
						//fseek(fp, pSection->containerOffset, SEEK_SET);

					//	filedatapSection
					}
					break;

				default:
					printf("Unknown type");
				}
				
				printf("\n");
			}
		}
#endif
	}
#endif
	else if (nread >= 4 && (
		((char*)buf)[0] == 0x7f &&
		((char*)buf)[1] == 'E' &&
		((char*)buf)[2] == 'L' &&
		((char*)buf)[3] == 'F'))
	{
		ASSERT(0);
#if 0
		printf("ELF\n");

		CElfParser elf;

		nread = fread(elf.e_ident, 1, 16, fp);
		if (nread >= 16)
		{
			//char* e_ident = (char*)buf;

			printf("class: ");
			if (elf.e_ident[4] == 1)
				printf("32");
			else if (elf.e_ident[4] == 2)
				printf("64");
			else
				ASSERT(0);
			printf("bit\n");

			printf("data-encoding: ");
			if (elf.e_ident[5]==1)			printf("little endian\n");
			else if (elf.e_ident[5]==2)		printf("big endian");
			else
				ASSERT(0);
			printf("\n");

			printf("version: %d\n", elf.e_ident[6]);

			printf("osabi: ");//%d\n", e_ident[7]);
			if (elf.e_ident[7] == 0)//ELFOSABI_SYSV 0
				printf("System V ABI");
			else if (elf.e_ident[7] == 1) //ELFOSABI_HPUX 1
				printf("HP-UX operating system");
			else if (elf.e_ident[7] == 255)	// ELFOSABI_STANDALONE 255
				printf("Standalone (embedded) application");
			printf("\n");

			printf("abiversion: %d\n", elf.e_ident[8]);

			short e_type = elf.gethalf(fp);
			short e_machine = elf.gethalf(fp);
			long e_version = elf.getword(fp);
			long e_entry = elf.getword(fp);
			long e_phoff = elf.getword(fp);
			long e_shoff = elf.getword(fp);
			long e_flags = elf.getword(fp);
			short e_ehsize = elf.gethalf(fp);
			short e_phentsize = elf.gethalf(fp);
			short e_phnum = elf.gethalf(fp);
			short e_shentsize = elf.gethalf(fp);
			short e_shnum = elf.gethalf(fp);
			short e_shstrndx = elf.gethalf(fp);

			printf("type: ");
			switch (e_type)
			{
			case ET_REL:	printf("rel");	break;
			case ET_EXEC:	printf("exec");	break;
			case ET_DYN:	printf("dyn");	break;
			case ET_CORE:	printf("core");	break;
			}
			printf("\n");

			struct SectionHeader
			{
				long sh_name;
				long sh_type;
				long sh_flags;
				long sh_addr;
				long sh_offset;
				long sh_size;
			};

// sh_type
#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xffffffff

// sh_flags
#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MASKPROC 0xf0000000

			SectionHeader* sheader = new SectionHeader[e_shnum];

			for (int i = 0; i < e_shnum; i++)
			{
				fseek(fp, e_shoff + e_shentsize * i, SEEK_SET);

				sheader[i].sh_name = elf.getword(fp);
				sheader[i].sh_type = elf.getword(fp);
				sheader[i].sh_flags = elf.getword(fp);
				sheader[i].sh_addr = elf.getword(fp);
				sheader[i].sh_offset = elf.getword(fp);
				sheader[i].sh_size = elf.getword(fp);
			}

			fseek(fp, sheader[e_shstrndx].sh_offset, SEEK_SET);
			char* StringTable = new char[sheader[e_shstrndx].sh_size];

			fread(StringTable, sheader[e_shstrndx].sh_size, 1, fp);

			for (i = 0; i < e_shnum; i++)
			{
				printf("%s -", StringTable + sheader[i].sh_name);

				if (sheader[i].sh_flags & SHF_EXECINSTR)
				{
					unsigned long size = sheader[i].sh_size;

					BYTE* data = new BYTE[size];
					fseek(fp, sheader[i].sh_offset, SEEK_SET);
					fread(data, 1, size, fp);

					printf("code\n");
					cpp::dasm_powerpc(data, 0, size, 0, NULL);

					delete[] data;
				}

				printf("\n");
			}
#if 0
Elf64_Word e_version; /* Object file version */
Elf64_Addr e_entry; /* Entry point address */
Elf64_Off e_phoff; /* Program header offset */
Elf64_Off e_shoff; /* Section header offset */
Elf64_Word e_flags; /* Processor-specific flags */
Elf64_Half e_ehsize; /* ELF header size */
Elf64_Half e_phentsize; /* Size of program header entry */
Elf64_Half e_phnum; /* Number of program header entries */
Elf64_Half e_shentsize; /* Size of section header entry */
Elf64_Half e_shnum; /* Number of section header entries */
Elf64_Half e_shstrndx; /* Section name string table index */
#endif

		}
		else
		{
			printf("Corrupted file\n");
		}
#endif
	}
#if 0
	else if (((cpp::mach_header*)buf)->magic == BigEndian32(MH_MAGIC))
	{
		printf("Mach-O\n");

		return new cpp::MachOLoader();
//		macho(fp);
	}
#endif
	else
	{
		printf("Unknown object file format\n");
		fflush(stdout);
	}

	return NULL;
}

}
