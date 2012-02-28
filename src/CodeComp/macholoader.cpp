#include "stdafx.h"
#include "macholoader.h"

namespace System
{
using namespace std;
using namespace IO;

namespace MachO
{

long MachOLoader::GetCPU()
{
	switch (m_header.cputype)
	{
	case MACHO_CPU_TYPE_MC680x0:	return CPU_M68K;
	case MACHO_CPU_TYPE_I386: return CPU_IX86;
	case MACHO_CPU_TYPE_POWERPC: return CPU_PPC;
	case MACHO_CPU_TYPE_SPARC: return CPU_SPARC;
	default:
		return CPU_UNKNOWN;
	}
}

uint MachOLoader::GetNumberOfSymbols()
{
	return m_nsymbols;
}

ObjectSymbol* MachOLoader::GetSymbol(uint index)
{
	return (ObjectSymbol*)&m_symbols[index];
}

uint MachOLoader::GetNumberOfSections()
{
	return m_sections.GetSize();
}

int MachOLoader::GetSection(uint nSection, SECTION* pSection)
{
	pSection->sectionHeader.VirtualAddress = m_sections[nSection]->addr;

	return 0;
}

long MachOLoader::Read(IO::Stream* stream)
{
	stream->Read(&m_header, sizeof(m_header));
	m_header.cputype = BigEndian32(m_header.cputype);
	m_header.cpusubtype = BigEndian32(m_header.cpusubtype);
	m_header.filetype = BigEndian32(m_header.filetype);
	m_header.ncmds = BigEndian32(m_header.ncmds);
	m_header.flags = BigEndian32(m_header.flags);

	for (int ncmd = 0; ncmd < m_header.ncmds; ncmd++)
	{
		long start = stream->Seek(0, System::IO::STREAM_SEEK_CUR);

		load_command load_cmd;
		stream->Read(&load_cmd, sizeof(load_command));
		load_cmd.cmd = BigEndian32(load_cmd.cmd);
		load_cmd.cmdsize = BigEndian32(load_cmd.cmdsize);

	//	ASSERT((load_cmd.cmdsize/4 * 4) == load_cmd.cmdsize);
		if (((load_cmd.cmdsize+3) & ~3) != load_cmd.cmdsize)
		{
			printf("Corrupt\n");
			return -1;
		}

		char* strcmdtype;
		switch (load_cmd.cmd)
		{
		case LC_SEGMENT:	strcmdtype = "file segment to be mapped";	break;
		case LC_SYMTAB:	strcmdtype = "link-edit stab symbol table info"; break;
		case LC_SYMSEG:	strcmdtype = "link-edit gdb symbol table info(obsolete)"; break;
		case LC_THREAD:	strcmdtype = "thread"; break;
		case LC_UNIXTHREAD:	strcmdtype = "UNIX thread (includes a stack)"; break;
		case LC_LOADFVMLIB:	strcmdtype = "load a fixed VM shared library"; break;
		case LC_IDFVMLIB:	strcmdtype = "fixed VM shared library id"; break;
		case LC_IDENT:	strcmdtype = "object identification information(obsolete)"; break;
		case LC_FVMFILE:	strcmdtype = "fixed VM file inclusion"; break;
		case LC_PREPAGE:	strcmdtype = "prepage"; break;
		case LC_DYSYMTAB:	strcmdtype = "desymtab"; break;
		case LC_LOAD_DYLIB:	strcmdtype = "load_dylib"; break;
		case LC_ID_DYLIB:	strcmdtype = "id_dylib"; break;
		case LC_LOAD_DYLINKER:	strcmdtype = "load_dylinker"; break;
		case LC_ID_DYLINKER:	strcmdtype = "id_dylinker"; break;
		case LC_PREBOUND_DYLIB:	strcmdtype = "prebound_dylib"; break;
		default:
			{
				static char str[64];
				sprintf_s(str, "Unknown %d", load_cmd.cmd);
				strcmdtype = str;
			}
		}

		printf("Command type: %s\n", strcmdtype);

		switch (load_cmd.cmd)
		{
		case LC_SEGMENT:
		{
			segment_command segment_cmd = {load_cmd.cmd, load_cmd.cmdsize};
			stream->Read(((uint8*)&segment_cmd) + 8, sizeof(segment_cmd)-8);

			segment_cmd.vmaddr = BigEndian32(segment_cmd.vmaddr);
			segment_cmd.vmsize = BigEndian32(segment_cmd.vmsize);
			segment_cmd.fileoff = BigEndian32(segment_cmd.fileoff);
			segment_cmd.filesize = BigEndian32(segment_cmd.filesize);
			segment_cmd.maxprot = BigEndian32(segment_cmd.maxprot);
			segment_cmd.initprot = BigEndian32(segment_cmd.initprot);
			segment_cmd.nsects = BigEndian32(segment_cmd.nsects);
			segment_cmd.flags = BigEndian32(segment_cmd.flags);

#if 0
			segments.push_back(segment_cmd);
#endif
			printf("Segment name: %.16s\n", segment_cmd.segname);
			printf("\tfileoff: %d\n", segment_cmd.fileoff);
			printf("\tfilesize: %d\n", segment_cmd.filesize);
			printf("\tvmaddr: %d\n", segment_cmd.vmaddr);
			printf("\tvmsize: %d\n", segment_cmd.vmsize);
			printf("\tmaxprot: %d\n", segment_cmd.maxprot);
			printf("\tinitprot: %d\n", segment_cmd.initprot);

			printf("\tflags: ");
			if (segment_cmd.flags & SG_HIGHVM) printf("HIGHVM ");
			if (segment_cmd.flags & SG_FVMLIB) printf("SG_FVMLIB ");
			if (segment_cmd.flags & SG_NORELOC) printf("SG_NORELOC ");
			if (segment_cmd.flags == 0) printf("0");
			printf("\n");

		//	sections = new section[segment_cmd.nsects];

			for (int i = 0; i < segment_cmd.nsects; i++)
			{
				section* psection = new section;

				m_sections.Add(psection);

				stream->Read(psection, sizeof(section));

				psection->addr = BigEndian32(psection->addr);
				psection->size = BigEndian32(psection->size);
				psection->offset = BigEndian32(psection->offset);
				psection->align = BigEndian32(psection->align);
				psection->flags = BigEndian32(psection->flags);
				psection->reserved1 = BigEndian32(psection->reserved1);
				psection->reserved2 = BigEndian32(psection->reserved2);

				printf("\tSection #%d, %.16s\n", i+1, psection->sectname);
				printf("\t\taddr: %d\n", psection->addr);
				printf("\t\tsize: %d\n", psection->size);
				printf("\t\toffset: %d\n", psection->offset);
				printf("\t\talign: 2^%d (%d)\n", psection->align, 1<<psection->align);
				printf("\t\treserved1: %d\n", psection->reserved1);
				printf("\t\treserved2: %d\n", psection->reserved2);

				printf("\t\ttype: ");
				int type = psection->flags & MACHO_SECTION_TYPE;
				switch (type)
				{
				case MACHO_S_REGULAR:						printf("REGULAR"); break;
				case MACHO_S_ZEROFILL:						printf("ZEROFILL"); break;
				case MACHO_S_CSTRING_LITERALS:			printf("CSTRING_LITERALS"); break;
				case MACHO_S_4BYTE_LITERALS:				printf("4BYTE_LITERALS"); break;
				case MACHO_S_8BYTE_LITERALS:				printf("8BYTE_LITERALS"); break;
				case MACHO_S_LITERAL_POINTERS:			printf("LITERAL_POINTERS"); break;
				case MACHO_S_NON_LAZY_SYMBOL_POINTERS:	printf("NON_LAZY_SYMBOL_POINTERS"); break;
				case MACHO_S_LAZY_SYMBOL_POINTERS:		printf("LAZY_SYMBOL_POINTERS"); break;
				case MACHO_S_SYMBOL_STUBS:					printf("SYMBOL_STUBS"); break;
				case MACHO_S_MOD_INIT_FUNC_POINTERS:	printf("MOD_INIT_FUNC_POINTERS"); break;
				default:
					printf("Unknown %d", type);
				}
				printf("\n");
			}

		//	fseek(fp, segment_cmd.fileoff, SEEK_SET);

			/*
			if (segment_cmd.fileoff > 0)
			{
				if (!strcmp(segment_cmd.segname, "__TEXT"))
				{
					if (TRUE)
					{
					}
					else
					{
						macho(fp);
					}
				}
			}
			*/
		}
		break;

		case LC_SYMTAB:
		{
//			fflush(stdout);

			symtab_command symtab_cmd = {load_cmd.cmd, load_cmd.cmdsize};
			stream->Read(((uint8*)&symtab_cmd) + 8, sizeof(symtab_cmd)-8);

			symtab_cmd.symoff = BigEndian32(symtab_cmd.symoff);
			symtab_cmd.nsyms = BigEndian32(symtab_cmd.nsyms);
			symtab_cmd.stroff = BigEndian32(symtab_cmd.stroff);
			symtab_cmd.strsize = BigEndian32(symtab_cmd.strsize);

			m_nsymbols = symtab_cmd.nsyms;

			printf("\tsymoff: %d\n", symtab_cmd.symoff);
			printf("\tstroff: %d\n", symtab_cmd.stroff);
			printf("\tstrsize: %d\n", symtab_cmd.strsize);

			//printf("\tSegment name: %16.16s\n", segment_cmd.segname);
		//	fseek(fp, symtab_cmd.stroff, SEEK_SET);
			m_symbols = new nlist[symtab_cmd.nsyms];
			long symoff = symtab_cmd.symoff;
			stream->Seek(symoff, System::IO::STREAM_SEEK_SET);
			stream->Read(m_symbols, sizeof(nlist)*symtab_cmd.nsyms);

			char* StringTable = new char[symtab_cmd.strsize];
			//0x2468
			int stroff = symtab_cmd.stroff;// - symtab_cmd.symoff;
			stream->Seek(stroff, System::IO::STREAM_SEEK_SET);
			stream->Read(StringTable, symtab_cmd.strsize);

			for (int i = 0; i < symtab_cmd.nsyms; i++)
			{
				nlist* n = &m_symbols[i];
				/*
				if (fread(n, 1, sizeof(nlist), fp) != sizeof(nlist))
				{
					printf("read error\n");
					return -1;
				}
				*/

				n->n_un.n_strx = BigEndian32(n->n_un.n_strx);
				n->n_desc = BigEndian16(n->n_value);
				n->n_value = BigEndian16(n->n_value);

				if (n->n_type & MACHO_SYMBOL_N_STAB)
				{
					printf("\tstab");
				}
				else
				{
				}

				if ((n->n_type & MACHO_SYMBOL_N_TYPE) == MACHO_SYMBOL_TYPE_N_UNDF)
				{
					printf("\tundefined in this module");
				}
				else if ((n->n_type & MACHO_SYMBOL_N_TYPE) == MACHO_SYMBOL_TYPE_N_ABS)
				{
					printf("\tabsolute");
				}
				else if ((n->n_type & MACHO_SYMBOL_N_TYPE) == MACHO_SYMBOL_TYPE_N_SECT)
				{
					printf("\tdefined in sect: %d", n->n_other);
				}
				else if ((n->n_type & MACHO_SYMBOL_N_TYPE) == MACHO_SYMBOL_TYPE_N_INDR)
				{
					printf("\tindr");
				}
				else if ((n->n_type & MACHO_SYMBOL_N_TYPE) == MACHO_SYMBOL_TYPE_N_PBUD)
				{
					printf("\tpbud");
				}

				if (n->n_type & MACHO_SYMBOL_N_EXT)
				{
					printf("\texternal");
				}

				if ((n->n_desc & REFERENCE_TYPE_MASK) == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
				{
					printf("\tundefined_non_lazy");
				}
				else if ((n->n_desc & REFERENCE_TYPE_MASK) == REFERENCE_FLAG_UNDEFINED_LAZY)
				{
					printf("\tundefined_lazy");
				}
				else if ((n->n_desc & REFERENCE_TYPE_MASK) == REFERENCE_FLAG_DEFINED)
				{
					printf("\tdefined");
				}
				else if ((n->n_desc & REFERENCE_TYPE_MASK) == REFERENCE_FLAG_PRIVATE_DEFINED)
				{
					printf("\tprivate_defined");
				}
				else if ((n->n_desc & REFERENCE_TYPE_MASK) == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
				{
					printf("\tprivate_undefined_none_lazy");
				}
				else if ((n->n_desc & REFERENCE_TYPE_MASK) == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
				{
					printf("\tprivate_undefined_lazy");
				}
				else
				{
					printf("\tunknown");
				}
				if (n->n_desc & REFERENCED_DYNAMICALLY)
					printf("\tREFERENCED_DYNAMICALLY");
				if (n->n_desc & N_DESC_DISCARDED)
					printf("\tN_DESC_DISCARDED");
				if (n->n_desc & N_WEAK_REF)
					printf("\tN_WEAK_REF");
				if (n->n_desc & N_WEAK_DEF)
					printf("\tN_WEAK_DEF");

				printf("\tvalue: %d", n->n_value);

				if (n->n_un.n_strx < 0 || n->n_un.n_strx >= symtab_cmd.strsize)
				{
					printf("???\n");
				//	return -1;
				}
				else
				{
					n->n_un.n_name = StringTable + n->n_un.n_strx;
					printf("\t%s", n->n_un.n_name);
				}
				printf("\n");
			}
		}
		break;

		case LC_DYSYMTAB:
			{
				dysymtab_command dysymtab_cmd = {load_cmd.cmd, load_cmd.cmdsize};
				stream->Read(((uint8*)&dysymtab_cmd) + 8, sizeof(dysymtab_cmd)-8);

				dysymtab_cmd.nlocalsym = BigEndian32(dysymtab_cmd.nlocalsym);
			}
			break;

		case LC_LOAD_DYLINKER:
			{
				long offset;
				stream->Read(&offset, 4);
				offset = BigEndian32(offset);

				stream->Seek(offset-12, System::IO::STREAM_SEEK_CUR);

				char* string = new char[load_cmd.cmdsize - 12];
				stream->Read(string, load_cmd.cmdsize - 12);

				printf("%s\n", string);
			}
			break;

		case LC_LOAD_DYLIB:
		case LC_ID_DYLIB:
			{
				long offset;
				stream->Read(&offset, 4);
				offset = BigEndian32(offset);

				stream->Seek(offset-12, System::IO::STREAM_SEEK_CUR);

				char* string = new char[load_cmd.cmdsize - 12];
				stream->Read(string, load_cmd.cmdsize - 12);

				printf("%s\n", string);
			}
			break;

		case LC_THREAD:
		case LC_UNIXTHREAD:
			{
#if 0
				thread_command thread_cmd = {load_cmd.cmd, load_cmd.cmdsize};
				thread_cmd.flavor = fget32(fp);
				thread_cmd.count = fget32(fp);

				printf("\tflavor: %d\n", thread_cmd.flavor);
				printf("\tcount: %d\n", thread_cmd.count);

				DWORD* thread_state = new DWORD[thread_cmd.count];

				fread(thread_state, thread_cmd.count*4, 1, fp);

				for (int i = 0; i < thread_cmd.count; i++)
				{
					thread_state[i] = BigEndian32(thread_state[i]);
					printf("%d (%x)\n", thread_state[i], thread_state[i]);
				}
#endif
			}
			break;
		}

		printf("\n");
		stream->Seek(start + load_cmd.cmdsize, System::IO::STREAM_SEEK_SET);
	}

	for (int i = 0; i < m_sections.GetSize(); i++)
	{
		if (/*!strcmp(segment_cmd.segname, "__TEXT") &&*/
			!strcmp(m_sections[i]->sectname, "__text"))
		{
			stream->Seek(m_sections[i]->offset, System::IO::STREAM_SEEK_SET);

			uint8* text = new uint8[m_sections[i]->size];
			stream->Read(text, m_sections[i]->size);
#if 0
			cpp::dasm_powerpc(text, m_sections[i]->addr, m_sections[i]->size, nsymbols, symbols);
#endif
		}
	}

	if (m_header.cputype == 18)	// powerpc
	{
	}
	else
	{
		ASSERT(0);
		return -1;
	}

	return 0;
}

DebugInfo* MachOLoader::GetDebugInfo(Scope* pGlobalScope)
{
	return NULL;
}

}	// MachO
}
