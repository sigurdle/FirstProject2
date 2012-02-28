#include "StdAfx.h"
#include "LFC.h"
#include "../Include/COFF.h"
#include "CodeViewDebugInfo.h"

using namespace std;
using namespace System;
using namespace System::IO;

#define IMAGE_DOS_SIGNATURE                 0x5A4D      // MZ
#define IMAGE_OS2_SIGNATURE                 0x454E      // NE
#define IMAGE_OS2_SIGNATURE_LE              0x454C      // LE
#define IMAGE_VXD_SIGNATURE                 0x454C      // LE
#define IMAGE_NT_SIGNATURE                  0x00004550  // PE00

#define IMAGE_FILE_MACHINE_UNKNOWN           0
#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
#define IMAGE_FILE_MACHINE_R3000             0x0162  // MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000             0x0166  // MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000            0x0168  // MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2         0x0169  // MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA             0x0184  // Alpha_AXP
#define IMAGE_FILE_MACHINE_SH3               0x01a2  // SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3DSP            0x01a3
#define IMAGE_FILE_MACHINE_SH3E              0x01a4  // SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4               0x01a6  // SH4 little-endian
#define IMAGE_FILE_MACHINE_SH5               0x01a8  // SH5
#define IMAGE_FILE_MACHINE_ARM               0x01c0  // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB             0x01c2
#define IMAGE_FILE_MACHINE_AM33              0x01d3
#define IMAGE_FILE_MACHINE_POWERPC           0x01F0  // IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_POWERPCFP         0x01f1
#define IMAGE_FILE_MACHINE_IA64              0x0200  // Intel 64
#define IMAGE_FILE_MACHINE_MIPS16            0x0266  // MIPS
#define IMAGE_FILE_MACHINE_ALPHA64           0x0284  // ALPHA64
#define IMAGE_FILE_MACHINE_MIPSFPU           0x0366  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16         0x0466  // MIPS
#define IMAGE_FILE_MACHINE_AXP64             IMAGE_FILE_MACHINE_ALPHA64
#define IMAGE_FILE_MACHINE_TRICORE           0x0520  // Infineon
#define IMAGE_FILE_MACHINE_CEF               0x0CEF
#define IMAGE_FILE_MACHINE_EBC               0x0EBC  // EFI Byte Code
#define IMAGE_FILE_MACHINE_AMD64             0x8664  // AMD64 (K8)
#define IMAGE_FILE_MACHINE_M32R              0x9041  // M32R little-endian
#define IMAGE_FILE_MACHINE_CEE               0xC0EE

// Directory Entries

#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
//      IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor

//
// Debug Format
//

#ifdef __LERSTAD__
typedef struct _IMAGE_DEBUG_DIRECTORY {
    uint32   Characteristics;
    uint32   TimeDateStamp;
    uint16    MajorVersion;
    uint16    MinorVersion;
    uint32   Type;
    uint32   SizeOfData;
    uint32   AddressOfRawData;
    uint32   PointerToRawData;
} IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

#define IMAGE_DEBUG_TYPE_UNKNOWN          0
#define IMAGE_DEBUG_TYPE_COFF             1
#define IMAGE_DEBUG_TYPE_CODEVIEW         2
#define IMAGE_DEBUG_TYPE_FPO              3
#define IMAGE_DEBUG_TYPE_MISC             4
#define IMAGE_DEBUG_TYPE_EXCEPTION        5
#define IMAGE_DEBUG_TYPE_FIXUP            6
#define IMAGE_DEBUG_TYPE_OMAP_TO_SRC      7
#define IMAGE_DEBUG_TYPE_OMAP_FROM_SRC    8
#define IMAGE_DEBUG_TYPE_BORLAND          9
#define IMAGE_DEBUG_TYPE_RESERVED10       10
#define IMAGE_DEBUG_TYPE_CLSID            11
#endif

static String ErrorMsg[] =
{
	String(L"Unrecognized format"),
	String(L"Not enough memory"),
	String(L"Read error"),
	String(L"Size of optional header is too small"),
};

COFFParser::COFFParser()
{
	m_header = NULL;
	m_SectionHeader = NULL;
	m_windowsHeader = NULL;
	m_optionalStandardHeader = NULL;
	m_DataDirectory = NULL;
	m_pStringData = NULL;
	m_NameSymbols = NULL;
}

COFFParser::~COFFParser()
{
	delete[] m_fbuf;
}

ULONG COFFParser::RVA2FilePos(ULONG rva)
{
	int i;

	for (i = 0; i < m_header->NumberOfSections; i++)
	{
		if (m_SectionHeader[i].VirtualAddress <= rva &&
			m_SectionHeader[i].VirtualAddress + m_SectionHeader[i].Misc.VirtualSize > rva)
		{
			return m_SectionHeader[i].PointerToRawData + rva - m_SectionHeader[i].VirtualAddress;
		}
	}

	return -1;
}

int COFFParser::ImageNTSignature()
{
	uint16 magic = *(uint16*)m_fbuf;
//	fread(&magic, 2, 1, fp);
	if (magic == IMAGE_DOS_SIGNATURE)
	{
		uint32 PEOffset;
	//	fseek(fp, 0x3c, SEEK_SET);
	//	fread(&PEOffset, 4, 1, fp);
		PEOffset = *(uint32*)(m_fbuf + 0x3c);

		if (PEOffset > m_size-4-1)
		{
			return -1;
		}

		m_p = m_fbuf + PEOffset;
		uint32 signature = *(uint32*)(m_p); m_p += 4;

	//	fseek(fp, PEOffset, SEEK_SET);
	//	fread(&signature, 4, 1, fp);

		if (signature == IMAGE_NT_SIGNATURE)
		{
			return ParseCOFF();
		}
	}

	return -1;
}

long COFFParser::Read(IO::Stream* stream)
{
	m_size = stream->GetSize32();

	m_fbuf = new uint8[m_size];
	if (m_fbuf == NULL)
		return -2;
	m_p = m_fbuf;

	if (stream->Read(m_fbuf, m_size) != m_size)
		return -3;

	if (m_size >= 2 && *(uint16*)m_fbuf == IMAGE_DOS_SIGNATURE)
	{
		return ImageNTSignature();
	}
	else if ((m_size >= 2 && (
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_UNKNOWN ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_ALPHA ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_ARM ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_ALPHA64 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_I386 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_IA64 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_M68K ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_MIPS16 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_MIPSFPU ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_MIPSFPU16 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_POWERPC ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_R3000 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_R4000 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_R10000 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_SH3 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_SH4 ||
		*(uint16*)m_fbuf == IMAGE_FILE_MACHINE_THUMB)))
	{
		ParseCOFF();
	}

	return -1;
}

long COFFParser::GetFormat()
{
	return FORMAT_COFF;
}

long COFFParser::GetCPU()
{
	return -1;
}

uint COFFParser::GetNumberOfSymbols()
{
	return m_header->NumberOfSymbols;
}

uint COFFParser::GetNumberOfSections()
{
	return m_header->NumberOfSections;
}

int COFFParser::GetSection(uint nSection, SECTION* pSection)
{
	return 0;
}

String COFFParser::GetErrorMsg(long nError)
{
	return ErrorMsg[-nError-1];
}

uint8* COFFParser::GetData(uint nSection)
{
	return m_fbuf + m_SectionHeader[nSection].PointerToRawData;
	/*
	BYTE* text = new BYTE[exec_header.a_text];
	if (text == NULL)
	{
		return NULL;
	}

	fseek(m_fp, m_TextOffset, SEEK_SET);
	fread(text, 1, exec_header.a_text, m_fp);

	return text;
	*/
	return NULL;
}

ULONG COFFParser::GetDataSize(uint nSection)
{
	return m_SectionHeader[nSection].SizeOfRawData;
//	return exec_header.a_text;
}

DebugInfo* COFFParser::GetDebugInfo(Scope* pGlobalScope)
{
	if (m_windowsHeader->NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_DEBUG)
	{
		if (m_DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress)
		{
			printf("Debug\n");

		//	long pos = ftell(fp);

			uint32 fpos = RVA2FilePos(m_DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress);

			long entries = m_DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size / sizeof(IMAGE_DEBUG_DIRECTORY);
		//	fseek(fp, fpos, SEEK_SET);

			IMAGE_DEBUG_DIRECTORY* directoryT = (IMAGE_DEBUG_DIRECTORY*)(m_fbuf + fpos);

			for (int i = 0; i < entries; i++)
			{
				IMAGE_DEBUG_DIRECTORY& directory = directoryT[i];
				//directory = m_fp + fpos + fread(&directory, 1, sizeof(IMAGE_DEBUG_DIRECTORY), fp);

				/*
				printf("\t");
				if (directory.Type == IMAGE_DEBUG_TYPE_COFF)
					printf("coff");
				else if (directory.Type == IMAGE_DEBUG_TYPE_CODEVIEW)
					printf("codeview");
				else if (directory.Type == IMAGE_DEBUG_TYPE_FPO)
					printf("fpo");
				else if (directory.Type == IMAGE_DEBUG_TYPE_MISC)
					printf("misc");
				else if (directory.Type == IMAGE_DEBUG_TYPE_EXCEPTION)
					printf("exception");
				else if (directory.Type == IMAGE_DEBUG_TYPE_FIXUP)
					printf("fixup");
				else
					printf("unknown");
				printf(" ");
				*/

				//fseek(fp, directory.PointerToRawData, SEEK_SET);

				uint8* data = m_fbuf + directory.PointerToRawData;//new BYTE[directory.SizeOfData];
				//fread(data, directory.SizeOfData, 1, fp);

				if (directory.Type == IMAGE_DEBUG_TYPE_CODEVIEW)
				{
					CodeViewDebugInfo* cvparser = new CodeViewDebugInfo(data, pGlobalScope);
				//	cvparser->m_data = data;
				//	cvparser->pGlobalScope = pGlobalScope;
				//	cvparser->Parse(data, this, m_pReceiver);

					return cvparser;
				}
			}

		//	fseek(fp, pos, SEEK_SET);
		}
	}

	return NULL;
}

/*
short Endian16(short x)
{
	return x;//BigEndian16(x);
}
*/

unsigned short Endian16(unsigned short x)
{
	return x;//BigEndian16(x);
}

/*
long Endian32(long x)
{
	return x;//BigEndian32(x);
}
*/

unsigned long Endian32(unsigned long x)
{
	return x;//BigEndian32(x);
}

int COFFParser::ParseCOFF()
{
	m_header = (IMAGE_FILE_HEADER*)m_p;
	m_p += sizeof(IMAGE_FILE_HEADER);

	m_header->PointerToSymbolTable = Endian32(m_header->PointerToSymbolTable);
	m_header->NumberOfSymbols = Endian32(m_header->NumberOfSymbols);
	m_header->SizeOfOptionalHeader = Endian16(m_header->SizeOfOptionalHeader);
	m_header->NumberOfSections = Endian16(m_header->NumberOfSections);
	m_header->Characteristics = Endian16(m_header->Characteristics);

	if (m_header->SizeOfOptionalHeader > 0)
	{
		//long optionalHeaderStartPos = ftell(fp);

		if (m_header->SizeOfOptionalHeader < sizeof(OptionalStandardHeader))
		{
			return -4;
		}
		m_optionalStandardHeader = (OptionalStandardHeader*)m_p;
		m_p += sizeof(OptionalStandardHeader);
//		if (fread(&optionalStandardHeader, 1, sizeof(optionalStandardHeader), fp) != sizeof(optionalStandardHeader))
//			return -1;

		if (m_optionalStandardHeader->Magic == 0x10b)//	PE32
		{
			BaseOfData = *(uint32*)m_p; m_p += 4;//	Address, relative to image base, of beginning of data section, when loaded into memory.
			//fread(&BaseOfData, 4, 1, fp);

			//printf("\tBase of Data: 0x%x\n", BaseOfData);

			m_windowsHeader = (WindowsHeader*)m_p; m_p += sizeof(WindowsHeader);
			//fread(&windowsHeader, sizeof(windowsHeader), 1, fp);

			/*
			printf("ImageBase: 0x%x\n", windowsHeader.ImageBase);
			printf("SectionAlignment: 0x%x\n", windowsHeader.SectionAlignment);
			printf("FileAlignment: 0x%x\n", windowsHeader.FileAlignment);
			printf("MajorOperatingSystemVersion: 0x%x\n", windowsHeader.MajorOperatingSystemVersion);
			printf("MinorOperatingSystemVersion: 0x%x\n", windowsHeader.MinorOperatingSystemVersion);
			printf("MajorImageVersion: 0x%x\n", windowsHeader.MajorImageVersion);
			printf("MinorImageVersion: 0x%x\n", windowsHeader.MinorImageVersion);
			printf("MajorSubsystemVersion: 0x%x\n", windowsHeader.MajorSubsystemVersion);
			printf("MinorSubsystemVersion: 0x%x\n", windowsHeader.MinorSubsystemVersion);
			printf("Reserved: 0x%x\n", windowsHeader.Reserved);
			printf("SizeOfImage: 0x%x\n", windowsHeader.SizeOfImage);
			printf("SizeOfHeaders: 0x%x\n", windowsHeader.SizeOfHeaders);
			printf("CheckSum: 0x%x\n", windowsHeader.CheckSum);
			//printf("0x%x", windowsHeader.Subsystem);
			if (windowsHeader.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_GUI)
				printf("\tSubsystem: Windows GUI\n");
			else if (windowsHeader.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI)
				printf("\tSubsystem: Windows Character\n");
			else
				printf("\tSubsystem: Unknown\n");
			printf("DLLCharacteristics: 0x%x\n", windowsHeader.DLLCharacteristics);
			printf("SizeOfStackReserve: 0x%x\n", windowsHeader.SizeOfStackReserve);
			printf("SizeOfStackCommit: 0x%x\n", windowsHeader.SizeOfStackCommit);
			printf("SizeOfHeapReserve: 0x%x\n", windowsHeader.SizeOfHeapReserve);
			printf("SizeOfHeapCommit: 0x%x\n", windowsHeader.SizeOfHeapCommit);
			printf("windowsHeader.LoaderFlags: 0x%x\n", windowsHeader.LoaderFlags);
			printf("NumberOfRvaAndSizes: 0x%x\n", windowsHeader.NumberOfRvaAndSizes);

		//	printf("\tImageBase: 0x%x\n", windowsHeader.ImageBase);
		//	printf("\tNumber of Data Directories: %d\n", windowsHeader.NumberOfRvaAndSizes);
*/
			m_DataDirectory = (IMAGE_DATA_DIRECTORY*)m_p;//new IMAGE_DATA_DIRECTORY[windowsHeader.NumberOfRvaAndSizes];

			m_p += sizeof(IMAGE_DATA_DIRECTORY) * m_windowsHeader->NumberOfRvaAndSizes;
/*
			for (int i = 0; i < windowsHeader.NumberOfRvaAndSizes; i++)
			{
				//IMAGE_DATA_DIRECTORY imageDataDir;
				fread(&DataDirectory[i], sizeof(IMAGE_DATA_DIRECTORY), 1, fp);
			}
			*/
		}
		else if (m_optionalStandardHeader->Magic == 0x20b)//	PE32+
		{
			//printf("PE32+\n");
		}

#if 0
		long pos = ftell(fp);
		if (pos > optionalHeaderStartPos + header.SizeOfOptionalHeader)
		{
			printf("Corrupted file format");
			return -1;
		}
		if (fseek(fp, optionalHeaderStartPos + header.SizeOfOptionalHeader,SEEK_SET) != 0)
			return -1;
#endif
		m_p = (uint8*)m_optionalStandardHeader + m_header->SizeOfOptionalHeader;
	}

//	SectionHeader = new IMAGE_SECTION_HEADER[header.NumberOfSections];

	m_SectionHeader = (IMAGE_SECTION_HEADER*)m_p;

	for (int j = 0; j < m_header->NumberOfSections; ++j)
	{
		//fread(&SectionHeader[j], sizeof(IMAGE_SECTION_HEADER), 1, fp);

		m_SectionHeader[j].Misc.VirtualSize = Endian32(m_SectionHeader[j].Misc.VirtualSize);
		m_SectionHeader[j].VirtualAddress = Endian32(m_SectionHeader[j].VirtualAddress);
		m_SectionHeader[j].SizeOfRawData = Endian32(m_SectionHeader[j].SizeOfRawData);
		m_SectionHeader[j].PointerToRawData = Endian32(m_SectionHeader[j].PointerToRawData);
		m_SectionHeader[j].PointerToRelocations = Endian32(m_SectionHeader[j].PointerToRelocations);
		m_SectionHeader[j].PointerToLinenumbers = Endian32(m_SectionHeader[j].PointerToLinenumbers);
		m_SectionHeader[j].NumberOfRelocations = Endian16(m_SectionHeader[j].NumberOfRelocations);
	}

	m_NameSymbols = NULL;
	m_NumberOfNameSymbols = 0;
	if (m_header->PointerToSymbolTable)
	{
		//printf("Symbols:\n");
		// The string table is right after all the symbols
		uint32 PointerToStringTable = m_header->PointerToSymbolTable + m_header->NumberOfSymbols * IMAGE_SIZEOF_SYMBOL;
	//	fseek(fp, PointerToStringTable, SEEK_SET);
	//	uint32 StringTableSize;
	//	fread(&StringTableSize, 1, 4, fp);	// This includes the 4byte size
	//	StringTableSize -= 4;
	//	StringData = NULL;

		if (PointerToStringTable > m_size/*-4*/)
		{
			return -1;
		}

		uint8* p  = m_fbuf + PointerToStringTable;

		m_StringTableSize = Endian32(*(uint32*)p);
		m_StringTableSize -= 4;
		m_pStringData = (char*)(p+4);

		IMAGE_SYMBOL* pSymbolTable = (IMAGE_SYMBOL*)(m_fbuf + m_header->PointerToSymbolTable);
		for (unsigned int s = 0; s < m_header->NumberOfSymbols; ++s)
		{
			IMAGE_SYMBOL* symbol = &pSymbolTable[s];
			s += symbol->NumberOfAuxSymbols;
			m_NumberOfNameSymbols++;
		}

		m_NameSymbols = new SYMBOL[m_NumberOfNameSymbols];

		int n = 0;
		for (unsigned int s = 0; s < m_header->NumberOfSymbols; ++s)
		{
			IMAGE_SYMBOL* symbol = &pSymbolTable[s];
		//	symbol->N.Name.Long = Endian32(symbol->N.Name.Long);
			m_NameSymbols[n].is = symbol;

			if (symbol->N.Name.Short)
			{
				char name[9];
				strncpy_s(name, (char*)symbol->N.ShortName, 8);
				name[8] = 0;

				m_NameSymbols[n].name = _strdup(name);
			}
			else if (symbol->N.Name.Long >= 4)
			{
				m_NameSymbols[n].name = m_pStringData + symbol->N.Name.Long-4;
			}
			else
			{
				//printf("Corrupt symbol table");
				return -1;
			}

			n += 1;
			s += symbol->NumberOfAuxSymbols;
		}
	}

	return 0;
}
