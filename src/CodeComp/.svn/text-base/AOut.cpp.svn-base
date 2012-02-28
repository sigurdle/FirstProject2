#include "stdafx.h"

#include "AOut.h"

namespace System
{
using namespace IO;

/*
template<int f> class ff
{
public:

};

ff<(8 > 8)>;
*/

// a.out

AOutParser::AOutParser()
{
	m_numberOfSections = 0;
	m_nsymbols = 0;

	m_pDebugInfo = NULL;
}

AOutParser::~AOutParser()
{
#if 0
	delete m_pDebugInfo;
#endif
}

/*
int AOutParser::Release()
{
	delete this;
	return 0;
}
*/

long AOutParser::GetFormat()
{
	return FORMAT_AOUT;
}

long AOutParser::GetCPU()
{
	switch (N_GETMAGIC(&exec_header))
	{
	case A_MAGIC: return CPU_M68K; break;
	case I_MAGIC: return CPU_IX86; break;
//	case J_MAGIC: printf("intel 960"); break;
	case K_MAGIC: return CPU_SPARC; break;
//	case V_MAGIC: printf("mips 3000"); break;
//	case X_MAGIC: printf("att dsp 3210"); break;
//	case M_MAGIC: printf("mips 4000"); break;
//	case D_MAGIC: printf("amd 29000"); break;
//	case E_MAGIC: printf("arm 7-something"); break;
	case Q_MAGIC: return CPU_PPC; break;
//	case N_MAGIC: printf("mips 4000-le"); break;
//	case L_MAGIC: printf("dec alpha"); break;
	default: return CPU_UNKNOWN;//printf("Unknown");
	}
}

uint AOutParser::GetNumberOfSections()
{
	return m_numberOfSections;
}

uint8* AOutParser::GetData(uint nSection)
{
//	nSection = m_Sections[nSection];

	if (nSection == 0)
	{
		uint8* buf = new uint8[exec_header.a_text];
		if (buf == NULL)
		{
			return NULL;
		}

		m_pStream->Seek(m_TextOffset, System::IO::STREAM_SEEK_SET);
		m_pStream->Read(buf, exec_header.a_text);

		return buf;
	}
	else if (nSection == 1)
	{
		uint8* buf = new uint8[exec_header.a_data];
		if (buf == NULL)
		{
			return NULL;
		}

		m_pStream->Seek(m_DataOffset, IO::STREAM_SEEK_SET);
		m_pStream->Read(buf, exec_header.a_data);

		return buf;
	}

	return NULL;
}

ULONG AOutParser::GetDataSize(uint nSection)
{
//	nSection = m_Sections[nSection];

	if (nSection == 0)
	{
		return exec_header.a_text;
	}
	else if (nSection == 1)
	{
		return exec_header.a_data;
	}
	else if (nSection == 2)
	{
		return exec_header.a_bss;
	}
	else
		return 0;
}

uint AOutParser::GetNumberOfSymbols()
{
	return m_nsymbols;
}

/*
CSymbol* CAOutParser::GetSymbol(int index)
{
	return NULL;
}
*/
ObjectSymbol* AOutParser::GetSymbol(uint index)
{
	if (index < m_nsymbols)
	{
		return (ObjectSymbol*)&m_nlistSymbols[index];
	}
	else
	{
		return NULL;
	}
}

uint AOutParser::GetNumberOfRelocations(uint nSection)
{
//	if (nSection >= 0 && nSection < m_numberOfSections)
	{
//		nSection = m_Sections[nSection];

		if (nSection == 0)
		{
			return exec_header.a_trsize / sizeof(relocation_info);
		}
		else if (nSection == 1)
		{
			return exec_header.a_drsize / sizeof(relocation_info);
		}
		else
			return 0;
	}
//	else
//		return -1;
}

Relocation* AOutParser::GetRelocation(uint nSection, int index)
{
	if (nSection == 0)
	{
		return (Relocation*)&m_tr[index];
	}
	else if (nSection == 1)
	{
		return (Relocation*)&m_dr[index];
	}
	else
	{
		ASSERT(0);
		return NULL;
	}
}

long AOutParser::Read(Stream* stream)
{
	m_pStream = stream;

	ULONG filesize = stream->GetSize();

	if (stream->Read(&exec_header, sizeof(exec)) != sizeof(exec))
	{
//		printf("AOut read error\n");
		return -1;
	}

	switch (N_GETMAGIC(&exec_header))
	{
	case A_MAGIC:
		//printf("68020");
		break;
	case I_MAGIC:
		//printf("intel 386");
		break;

	case J_MAGIC:// printf("intel 960"); break;
	case K_MAGIC:// printf("sparc"); break;
	case V_MAGIC:// printf("mips 3000"); break;
	case X_MAGIC:// printf("att dsp 3210"); break;
	case M_MAGIC:// printf("mips 4000"); break;
	case D_MAGIC:// printf("amd 29000"); break;
	case E_MAGIC:// printf("arm 7-something"); break;
	case Q_MAGIC:// printf("powerpc"); break;
	case N_MAGIC:// printf("mips 4000-le"); break;
	case L_MAGIC:// printf("dec alpha"); break;
		break;

	default:
//		printf("AOut: Unknown magic\n");
		return -2;
	}

	exec_header.a_text = BigEndian32(exec_header.a_text);
	exec_header.a_data = BigEndian32(exec_header.a_data);
	exec_header.a_bss = BigEndian32(exec_header.a_bss);
	exec_header.a_trsize = BigEndian32(exec_header.a_trsize);
	exec_header.a_drsize = BigEndian32(exec_header.a_drsize);
	exec_header.a_syms = BigEndian32(exec_header.a_syms);

	m_numberOfSections = 0;
	m_Sections[0] = -1;
	m_Sections[1] = -1;
	m_Sections[2] = -1;
	if (exec_header.a_text) m_Sections[m_numberOfSections++] = 0;
	if (exec_header.a_data) m_Sections[m_numberOfSections++] = 1;
	if (exec_header.a_bss) m_Sections[m_numberOfSections++] = 2;

	m_nsymbols = exec_header.a_syms / sizeof(nlist);

#if 0
	printf("text size: %d\n", exec_header.a_text);
	printf("data size: %d\n", exec_header.a_data);
	printf("bss size: %d\n", exec_header.a_bss);
	printf("text reloc size: %d\n", exec_header.a_trsize);
	printf("data reloc size: %d\n", exec_header.a_drsize);
	printf("symbol size: %d\n", exec_header.a_syms);
	printf("number of symbols: %d\n", nsymbols);
#endif

	m_TextOffset = sizeof(exec);
	m_DataOffset = sizeof(exec) + exec_header.a_text;
	m_TextRelocOffset = m_DataOffset + exec_header.a_data;
	m_DataRelocOffset = m_TextRelocOffset + exec_header.a_trsize;
	m_SymbolTableOffset = m_DataRelocOffset + exec_header.a_drsize;
	m_StringTableOffset = m_SymbolTableOffset + exec_header.a_syms;

	{
		int count = exec_header.a_trsize / sizeof(relocation_info);

	//	fprintf(stdout, "nrelocs: %d\n", count);

		if (count)
		{
			stream->Seek(m_TextRelocOffset, System::IO::STREAM_SEEK_SET);

			m_tr = new Relocation[count];

			for (int i = 0; i < count; i++)
			{
				relocation_info relocinfo;// = &m_tr[i];
				stream->Read(&relocinfo, sizeof(relocation_info));

				m_tr[i].r_address = BigEndian32(relocinfo.r_address);
			//	((DWORD*)&relocinfo)[1] = BigEndian32(((DWORD*)&relocinfo)[1]);

			//	fprintf(stdout, "r_address: %d, ", m_tr[i].r_address);

				uint8* bf = (uint8*)(((uint32*)&relocinfo)+1);

				bool r_pcrel = (bf[3] >> 7) & 0x1;
				int r_length = (bf[3] >> 5) & 0x3;
				bool r_extern = (bf[3] >> 4) & 0x1;
				bool r_baserel = (bf[3] >> 3) & 0x1;
				bool r_jmptable = (bf[3] >> 2) & 0x1;
				bool r_relative = (bf[3] >> 1) & 0x1;
				bool r_copy = (bf[3] >> 0) & 0x1;

				// TODO, support other values on these
				VERIFY(r_length == 2);
				VERIFY(r_baserel == 0);
				VERIFY(r_jmptable == 0);
				VERIFY(r_relative == 0);
				VERIFY(r_copy == 0);

				m_tr[i].r_extern = r_extern;
				m_tr[i].r_pcrel = r_pcrel;

	//TRACE("pcrel: %d, baserel: %d, relative: %d, copy: %d\n", r_pcrel, r_baserel, r_relative, r_copy);

				uint32 symbolnum = (bf[0]<<16) | (bf[1]<<8) | (bf[2]);

				//printf("symbolnum: %d, r_baserel: %d, r_extern: %d\n", symbolnum, r_baserel, r_extern);

			//	relocinfo->r_symbolnum = symbolnum;	// hm..
				m_tr[i].r_symbolnum = symbolnum;

			//	fprintf(stdout, "symbolnum: %d", m_tr[i].r_symbolnum);

			//	printf("Text Reloc(addr=%d, symbol=%d)\n", relocinfo->r_address - m_TextOffset, symbolnum);

			//	fprintf(stdout, "\n");
			}
		}
	}

	{
		int count = exec_header.a_drsize / sizeof(relocation_info);

	//	fprintf(stdout, "nrelocs: %d\n", count);

		if (count)
		{
			stream->Seek(m_DataRelocOffset, System::IO::STREAM_SEEK_SET);

			m_dr = new Relocation[count];

			for (int i = 0; i < count; i++)
			{
				relocation_info relocinfo;// = &m_tr[i];
				stream->Read(&relocinfo, sizeof(relocation_info));

				m_dr[i].r_address = BigEndian32(relocinfo.r_address);
			//	((DWORD*)&relocinfo)[1] = BigEndian32(((DWORD*)&relocinfo)[1]);

			//	fprintf(stdout, "r_address: %d, ", m_tr[i].r_address);

				uint8* bf = (uint8*)(((uint32*)&relocinfo)+1);

				bool r_pcrel = (bf[3] >> 7) & 0x1;
				int r_length = (bf[3] >> 5) & 0x3;
				bool r_extern = (bf[3] >> 4) & 0x1;;
				bool r_baserel = (bf[3] >> 3) & 0x1;
				bool r_jmptable = (bf[3] >> 2) & 0x1;
				bool r_relative = (bf[3] >> 1) & 0x1;
				bool r_copy = (bf[3] >> 0) & 0x1;
				
			//	ASSERT(r_pcrel == 0);
				ASSERT(r_length == 2);
				ASSERT(r_baserel == 0);
				ASSERT(r_jmptable == 0);
				ASSERT(r_relative == 0);
				ASSERT(r_copy == 0);

				m_dr[i].r_extern = r_extern;
				m_dr[i].r_pcrel = r_pcrel;

	//TRACE("pcrel: %d, baserel: %d, relative: %d, copy: %d\n", r_pcrel, r_baserel, r_relative, r_copy);

				uint32 symbolnum = (bf[0]<<16) | (bf[1]<<8) | (bf[2]);

				//printf("symbolnum: %d, r_baserel: %d, r_extern: %d\n", symbolnum, r_baserel, r_extern);

			//	relocinfo->r_symbolnum = symbolnum;	// hm..
				m_dr[i].r_symbolnum = symbolnum;

			//	fprintf(stdout, "symbolnum: %d", m_tr[i].r_symbolnum);

			//	printf("Text Reloc(addr=%d, symbol=%d)\n", relocinfo->r_address - m_TextOffset, symbolnum);

			//	fprintf(stdout, "\n");
			}
		}
	}

	// Symbols
	if (m_nsymbols)
	{
		m_nlistSymbols = new nlist[m_nsymbols];

		long StringTableLen = filesize - m_StringTableOffset;

		stream->position = m_StringTableOffset;
		m_StringData = new char[StringTableLen];
		int n = stream->Read(m_StringData, StringTableLen);
		ASSERT(n == StringTableLen);

		stream->position = m_SymbolTableOffset;
		for (int i = 0; i < m_nsymbols; i++)
		{
			nlist& symbol = m_nlistSymbols[i];

			stream->Read(&symbol, sizeof(nlist));
			symbol.n_un.n_strx = BigEndian32(symbol.n_un.n_strx);
			symbol.n_value = BigEndian32(symbol.n_value);
			symbol.n_desc = BigEndian16(symbol.n_desc);

			// Convert offset into string table to pointer
			symbol.n_un.n_name = m_StringData + symbol.n_un.n_strx;

			if ((symbol.n_type & N_TYPE) == N_DATA)
			{
				symbol.n_value -= exec_header.a_text;
			}

			/*

			printf("%d, %s, value=%d, type=%d", i+1, symbol.n_un.n_name, symbol.n_value, symbol.n_type);
			printf("\n");
			*/
		}
	}

#if 0
	{
		uint8* text = new uint8[exec_header.a_text];
		if (text == NULL)
		{
			printf("Out of memory");
			return -1;
		}

		fseek(fp, m_TextOffset, SEEK_SET);
		fread(text, 1, exec_header.a_text, fp);

		// Text Code
		if (N_GETMAGIC(&exec_header) == A_MAGIC)	// // 68020
		{
			pass2_CODE(text, exec_header.a_text, m_nsymbols, Symbols);
		}
		else if (N_GETMAGIC(&exec_header) == I_MAGIC)	// intel 386
		{
			ReadCode_x86(text, exec_header.a_text);
		}
		else if (N_GETMAGIC(&exec_header) == Q_MAGIC)	// powerpc
		{
			dasm_powerpc(text, exec_header.a_text);
		}
		else
		{
		}

		delete[] text;
	}
#endif

	return 0;
}

DebugInfo* AOutParser::GetDebugInfo(Scope* pGlobalScope)
{
#if 0	// TODO
	if (m_pDebugInfo == NULL)
	{
		m_pDebugInfo = new StabDebugInfo;
		m_pDebugInfo->m_pGlobalScope = pGlobalScope;
		m_pDebugInfo->FromStab(0, m_nlistSymbols, m_nsymbols);
	}
#endif

	return m_pDebugInfo;
}

}
