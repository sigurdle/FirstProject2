// COFFPE.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"

#pragma comment(lib, "../LFC/Debug/LFC.lib")

#pragma comment(lib, "../CodeComp/Debug/CodeComp.lib")

#include "../CodeComp/JavaClassFileLoader.h"
#include "XPCOMTypeLib.h"
#include "../Include/a_out.h"
#include "../Include/coff.h"
#include "../Include/stab.h"
#include "../Include/AmigaHunkParser.h"
#include "../include/CodeView.h"
#include "../include/Microsoft/cvinfo.h"

#include "../CodeComp/AOut.h"

#include "../Include/FileReader.h"

#include "../CodeComp/X86.h"

//#include <iostream>

//#include <winnt.h>

#include "../LFC/asn.h"

#include "../LFC/Certificate.h"

using namespace System;
using namespace System::CodeView;
using namespace System::IO;

typedef struct _IMAGE_RESOURCE_DIRECTORY {
    DWORD   Characteristics;
    DWORD   TimeDateStamp;
    uint16    MajorVersion;
    uint16   MinorVersion;
    uint16    NumberOfNamedEntries;
    uint16    NumberOfIdEntries;
//  IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[];
} IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

#define IMAGE_RESOURCE_NAME_IS_STRING        0x80000000
#define IMAGE_RESOURCE_DATA_IS_DIRECTORY     0x80000000
//
// Each directory contains the 32-bit Name of the entry and an offset,
// relative to the beginning of the resource directory of the data associated
// with this directory entry.  If the name of the entry is an actual text
// string instead of an integer Id, then the high order bit of the name field
// is set to one and the low order 31-bits are an offset, relative to the
// beginning of the resource directory of the string, which is of type
// IMAGE_RESOURCE_DIRECTORY_STRING.  Otherwise the high bit is clear and the
// low-order 16-bits are the integer Id that identify this resource directory
// entry. If the directory entry is yet another resource directory (i.e. a
// subdirectory), then the high order bit of the offset field will be
// set to indicate this.  Otherwise the high bit is clear and the offset
// field points to a resource data entry.
//

typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY {
    union {
        struct {
            DWORD NameOffset:31;
            DWORD NameIsString:1;
        };
        DWORD   Name;
        uint16    Id;
    };
    union {
        DWORD   OffsetToData;
        struct {
            DWORD   OffsetToDirectory:31;
            DWORD   DataIsDirectory:1;
        };
    };
} IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

//
// Each resource data entry describes a leaf node in the resource directory
// tree.  It contains an offset, relative to the beginning of the resource
// directory of the data for the resource, a size field that gives the number
// of bytes of data at that offset, a CodePage that should be used when
// decoding code point values within the resource data.  Typically for new
// applications the code page would be the unicode code page.
//

typedef struct _IMAGE_RESOURCE_DATA_ENTRY {
    DWORD   OffsetToData;
    DWORD   Size;
    DWORD   CodePage;
    DWORD   Reserved;
} IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;

struct WIN_CERTIFICATE
{    // Standard WIN_CERTIFICATE fields (8 bytes) 
   DWORD dwLength;
	uint16 wRevision;
	uint16 wCertificateType;    // = WIN_CERT_TYPE_PKCS1_SIGN    // WIN_CERT_TYPE_PKCS1_SIGN fields follow
//	DWORD cbSignedData;    // optional signed attributes
//	BYTE bSignedData[MAX_WIN_CERT_SIGN_DATA_LEN];
//	BYTE bSign[MAX_RSA_KEY_BITS/8]; // PKCS1 signature
};

//
// Debug Format
//

typedef struct _IMAGE_DEBUG_DIRECTORY {
    DWORD   Characteristics;
    DWORD   TimeDateStamp;
    uint16    MajorVersion;
    uint16    MinorVersion;
    DWORD   Type;
    DWORD   SizeOfData;
    DWORD   AddressOfRawData;
    DWORD   PointerToRawData;
} IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

#define FRAME_FPO       0
#define FRAME_TRAP      1
#define FRAME_TSS       2
#define FRAME_NONFPO    3

typedef struct _FPO_DATA {
    DWORD       ulOffStart;             // offset 1st byte of function code
    DWORD       cbProcSize;             // # bytes in function
    DWORD       cdwLocals;              // # bytes in locals/4
    uint16        cdwParams;              // # bytes in params/4
    uint16        cbProlog : 8;           // # bytes in prolog
    uint16        cbRegs   : 3;           // # regs saved
    uint16        fHasSEH  : 1;           // TRUE if SEH in func
    uint16        fUseBP   : 1;           // TRUE if EBP has been allocated
    uint16        reserved : 1;           // reserved for future use
    uint16        cbFrame  : 2;           // frame type
} FPO_DATA, *PFPO_DATA;
#define SIZEOF_RFPO_DATA 16

#define IMAGE_DEBUG_MISC_EXENAME    1

typedef struct _IMAGE_DEBUG_MISC {
    DWORD       DataType;               // type of misc data, see defines
    DWORD       Length;                 // total length of record, rounded to four
                                        // byte multiple.
    uint8     Unicode;                // TRUE if data is unicode string
    uint8        Reserved[ 3 ];
    uint8        Data[ 1 ];              // Actual data
} IMAGE_DEBUG_MISC, *PIMAGE_DEBUG_MISC;

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

#define IMAGE_FILE_RELOCS_STRIPPED           0x0001  // Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE          0x0002  // File is executable  (i.e. no unresolved externel references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED        0x0004  // Line nunbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED       0x0008  // Local symbols stripped from file.
#define IMAGE_FILE_AGGRESIVE_WS_TRIM         0x0010  // Agressively trim working set
#define IMAGE_FILE_LARGE_ADDRESS_AWARE       0x0020  // App can handle >2gb addresses
#define IMAGE_FILE_BYTES_REVERSED_LO         0x0080  // Bytes of machine word are reversed.
#define IMAGE_FILE_32BIT_MACHINE             0x0100  // 32 bit word machine.
#define IMAGE_FILE_DEBUG_STRIPPED            0x0200  // Debugging info stripped from file in .DBG file
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP   0x0400  // If Image is on removable media, copy and run from the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP         0x0800  // If Image is on Net, copy and run from the swap file.
#define IMAGE_FILE_SYSTEM                    0x1000  // System File.
#define IMAGE_FILE_DLL                       0x2000  // File is a DLL.
#define IMAGE_FILE_UP_SYSTEM_ONLY            0x4000  // File should only be run on a UP machine
#define IMAGE_FILE_BYTES_REVERSED_HI         0x8000  // Bytes of machine word are reversed.

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

namespace Security
{

void ReadContentInfo(ISequentialByteStream* stream);

#if 0
void ReadAlgorithmIdentifier(ISequentialByteStream* stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	if (tag.Kind != 16) throw -1;	// SEQUENCE
	{
		/*std::vector<ULONG> algoritm =*/ ASN::ReadObjectIdentifier(stream);
	}
	ASN::AscendTag(&tag, stream);

//	ASN::ReadObjectIdentifier(stream);	// ??
}
#endif

void ReadSignerInfo(ISequentialByteStream* stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	if (tag.Kind != 16) throw -1;
	long version = ASN::ReadInteger(stream);
}

void ReadExtendedCertificatesAndCertificates(ISequentialByteStream* stream)
{
//	ReadSignerInfo(stream);

//	ASN::Tag tag;
//	ASN::ReadTag(stream, &tag);
//	if (tag.Kind != 17) throw -1;

	ReadCertificate(stream);
}

void ReadSignedData(ISequentialByteStream* stream)
{
	ASN::Tag tag;
//	ASN::ReadTag(stream, &tag);

	ASN::ReadTag(stream, &tag);
	if (tag.Kind != 16) throw -1;

	long version = ASN::ReadInteger(stream);
	{
		ASN::ReadTag(stream, &tag);
		if (tag.Kind != 17) throw -1;
		while (1)
		{
			if (stream->Seek(0, System::IO::STREAM_SEEK_CUR) >= tag.start+tag.Length)
				break;

			ReadAlgorithmIdentifier(stream);
		}
		if (stream->Seek(0, System::IO::STREAM_SEEK_CUR) != tag.start+tag.Length)
			throw -1;

	}
	ASN::AscendTag(&tag, stream);

//	ReadContentInfo(stream);
	{
		ASN::ReadTag(stream, &tag);
		if (tag.Kind != 16) throw -1;
		ASN::AscendTag(&tag, stream);
	}

	{
		ASN::Tag tag;
		ASN::ReadTag(stream, &tag);
		if (tag.Kind == 0)
		{
			ReadExtendedCertificatesAndCertificates(stream);
		}
		else
			throw -1;
	}
}

void ReadContentInfo(ISequentialByteStream* stream)
{
	ASN::Tag tag;
	ASN::ReadTag(stream, &tag);
	if (tag.Kind != 16) throw -1;
	Array<ULONG> contentType = ASN::ReadObjectIdentifier(stream);
//	ASN::AscendTag(&tag, stream);

	if (contentType.size() != 7) throw -1;

	if (contentType[0] != 1) throw -1;
	if (contentType[1] != 2) throw -1;
	if (contentType[2] != 840) throw -1;
	if (contentType[3] != 113549) throw -1;
   if (contentType[4] != 1) throw -1;
	if (contentType[5] != 7) throw -1;

	ASN::ReadExplicitTag(stream, 0);

	if (contentType[6] == 1)
	{
		// data
	}
	else if (contentType[6] == 2)
	{
		ReadSignedData(stream);
	}
	else if (contentType[6] == 3)
	{
	//envelopedData OBJECT IDENTIFIER ::= { pkcs-7 3 }
	}
	else if (contentType[6] == 4)
	{
 //  signedAndEnvelopedData OBJECT IDENTIFIER ::=
   //   { pkcs-7 4 }
	}
	else if (contentType[6] == 5)
	{
	//   digestedData OBJECT IDENTIFIER ::= { pkcs-7 5 }
	}
	else if (contentType[6] == 6)
	{
 //  encryptedData OBJECT IDENTIFIER ::= { pkcs-7 6 }
	}
}

}	// Security

//extern char	xsbuf[128], *xsptr;
//extern char	msbuf[128],	*msptr;

/*
// Seems to be undefined in WinNT.h
#define IMAGE_FILE_MACHINE_M68K	0x268

#define IMAGE_FILE_AGGRESSIVE_WS_TRIM 0x10
*/

template<class T> class filepointer
{
public:
	filepointer()
	{
		m_fp = NULL;
		m_offset = -1;
		bRead = false;
	}

	FILE* m_fp;
	long m_offset;
	T t;
	bool bRead;

	void Read()
	{
		if (!bRead)
		{
			long oldpos = ftell(m_fp);
			fseek(m_fp, m_offset, SEEK_SET);
			fread(&t, sizeof(t), 1, m_fp);
			fseek(m_fp, oldpos, SEEK_SET);
			bRead = true;
		}
	}

	operator long ()
	{
		return m_offset+1;
	}

	operator = (long address)
	{
		if (address == NULL)
		{
			m_fp = NULL;
			m_offset == -1;
		}
		else
			ASSERT(0);
	}

	operator = (FILE* fp)
	{
		m_fp = fp;
		m_offset = ftell(fp);
	}

	T& operator * ()
	{
		Read();
		return t;
	}

	T* operator -> ()
	{
		Read();
		return &t;
	}

	filepointer<T> operator + (int offset)
	{
		filepointer<T> tt;
		tt.m_fp = m_fp;
		tt.m_offset = m_offset + sizeof(T)*offset;
		return tt;
	}
};

char* I386_RelType[] =
{
	"ABSOLUTE",//         0x0000  // Reference is absolute, no relocation is necessary
	"DIR16",//            0x0001  // Direct 16-bit reference to the symbols virtual address
	"REL16",//            0x0002  // PC-relative 16-bit reference to the symbols virtual address
	NULL, // 3
	NULL,	// 4
	NULL,	// 5
	"DIR32",//            0x0006  // Direct 32-bit reference to the symbols virtual address
	"DIR32NB",//          0x0007  // Direct 32-bit reference to the symbols virtual address, base not included
	NULL,	// 8
	"SEG12",//            0x0009  // Direct 16-bit reference to the segment-selector bits of a 32-bit virtual address
	"SECTION",//          0x000A
	"SECREL",//           0x000B
	"TOKEN",//            0x000C  // clr token
	"SECREL7",//          0x000D  // 7 bit offset from base of section containing target
	NULL,	// 14(E)
	NULL,	// 15(F)
	NULL,	// 16
	NULL,	// 17
	NULL,	// 18
	NULL,	// 19
	"REL32",//            0x0014  // PC-relative 32-bit reference to the symbols virtual address
};

char* StorageClassString[256] =
{
"CLASS_NULL",//                0x0000
"CLASS_AUTOMATIC",//           0x0001
"CLASS_EXTERNAL",//            0x0002
"CLASS_STATIC",//              0x0003
"CLASS_REGISTER",//            0x0004
"CLASS_EXTERNAL_DEF",//        0x0005
"CLASS_LABEL",//               0x0006
"CLASS_UNDEFINED_LABEL",//     0x0007
"CLASS_MEMBER_OF_STRUCT",//    0x0008
"CLASS_ARGUMENT",//            0x0009
"CLASS_STRUCT_TAG",//          0x000A
"CLASS_MEMBER_OF_UNION",//     0x000B
"CLASS_UNION_TAG",//           0x000C
"CLASS_TYPE_DEFINITION",//     0x000D
"CLASS_UNDEFINED_STATIC",//    0x000E
"CLASS_ENUM_TAG",//            0x000F
"CLASS_MEMBER_OF_ENUM",//      0x0010
"CLASS_REGISTER_PARAM",//      0x0011
"CLASS_BIT_FIELD",//           0x0012

/*
#define IMAGE_SYM_CLASS_FAR_EXTERNAL        0x0044  //

#define IMAGE_SYM_CLASS_BLOCK               0x0064
#define IMAGE_SYM_CLASS_FUNCTION            0x0065
#define IMAGE_SYM_CLASS_END_OF_STRUCT       0x0066
#define IMAGE_SYM_CLASS_FILE                0x0067
// new
#define IMAGE_SYM_CLASS_SECTION             0x0068
#define IMAGE_SYM_CLASS_WEAK_EXTERNAL       0x0069

#define IMAGE_SYM_CLASS_CLR_TOKEN           0x006B
*/
};


struct METADATA_HEADER
{
	DWORD Signature;
};

/*
0
 4
 Signature
 Magic signature for physical metadata : 0x424A5342.
 
4
 2
 MajorVersion
 Major version, 1 (ignore on read)
 
6
 2
 MinorVersion
 Minor version, 0 (ignore on read) 
 
8
 4
 Reserved
 Reserved, always 0 (see Section 23.1).
 
12
 4
 Length
 Length of version string in bytes, say m.        
 
16
 m
 Version
 UTF8-encoded version string of length m (ignore on read)
 
16+m
  
  
 Padding to next 4 byte boundary, say x.
 
x
 2
 Flags
 Reserved, always 0 (see Section 23.1).
 
x+2
 2
 Streams
 Number of streams, say n.
 
x+4
  
 StreamHeaders
 Array of n StreamHdr structures.
 
*/

void ReadResourceTable(int level, long startpos, FILE* fp)
{
	IMAGE_RESOURCE_DIRECTORY ImageResourceDirectory;
	fread(&ImageResourceDirectory, sizeof(ImageResourceDirectory), 1, fp);

	int i;

	for (i = 0; i < ImageResourceDirectory.NumberOfNamedEntries+ImageResourceDirectory.NumberOfIdEntries; i++)
	{
		IMAGE_RESOURCE_DIRECTORY_ENTRY ImageResourceDirectoryEntry;
		fread(&ImageResourceDirectoryEntry, sizeof(ImageResourceDirectoryEntry), 1, fp);

		for (int j = 0; j < level; j++)
		{
			printf("\t");
		}

		if (ImageResourceDirectoryEntry.NameIsString)
		{
			long pos = ftell(fp);

			fseek(fp, startpos+ImageResourceDirectoryEntry.NameOffset, SEEK_SET);

			uint16 length;
			fread(&length, 2, 1, fp);
			WCHAR name[512];
			fread(name, length*2, 1, fp);
			name[length] = 0;

			fseek(fp, pos, SEEK_SET);

			printf("resource Name: %S", name);
		}
		else
		{
			printf("resource ID: %d", ImageResourceDirectoryEntry.Id);
		}

		printf("\n");

		if (ImageResourceDirectoryEntry.DataIsDirectory)
		{
			long pos = ftell(fp);
		
			fseek(fp, startpos+ImageResourceDirectoryEntry.OffsetToDirectory, SEEK_SET);

			ReadResourceTable(level+1, startpos, fp);

			fseek(fp, pos, SEEK_SET);
		}
		else	// leaf
		{
			long pos = ftell(fp);
		
			fseek(fp, startpos+ImageResourceDirectoryEntry.OffsetToData, SEEK_SET);

			IMAGE_RESOURCE_DATA_ENTRY ResourceDataEntry;
			fread(&ResourceDataEntry, sizeof(ResourceDataEntry), 1, fp);

			uint8* data = new uint8[ResourceDataEntry.Size];
			if (data)
			{
				fseek(fp, ResourceDataEntry.OffsetToData, SEEK_SET);
				fread(data, ResourceDataEntry.Size, 1, fp);

				delete data;
			}

			fseek(fp, pos, SEEK_SET);
		}
	}
}


#ifndef IMAGE_DOS_SIGNATURE

#define IMAGE_DOS_SIGNATURE                 0x4D5A      // MZ
#define IMAGE_OS2_SIGNATURE                 0x4E45      // NE
#define IMAGE_OS2_SIGNATURE_LE              0x4C45      // LE
#define IMAGE_NT_SIGNATURE                  0x50450000  // PE00

#endif

void CompileSym(CFLAGSYM* sym)
{
	char* str;

	switch (sym->machine)
	{
	case 0x00: str = "Intel 8080"; break;
	case 0x01: str = "Intel 8086"; break;
	case 0x02: str = "Intel 80286"; break;
	case 0x03: str = "Intel 80386"; break;
	case 0x04: str = "Intel 80486"; break;
	case 0x05: str = "Intel Pentium"; break;
	case 0x10: str = "MIPS R4000"; break;
	case 0x11: str = "Reserved for future MIPS processor"; break;
	case 0x12: str = "Reserved for future MIPS processor"; break;
	case 0x20: str = "MC68000"; break;
	case 0x21: str = "MC68010"; break;
	case 0x22: str = "MC68020"; break;
	case 0x23: str = "MC68030"; break;
	case 0x24: str = "MC68040"; break;
	case 0x30: str = "DEC Alpha"; break;
	default:
		str = "unknown";
	}

	printf("machine: %s / ", str);

	static const char* CVLanguage[7] =
	{
		"C",
		"C++",
		"Fortran",
		"Masm",
		"Pascal",
		"Basic",
		"COBOL",
	};

	if (sym->flags.language < 7)
	{
		printf("source language: %s / ", CVLanguage[sym->flags.language]);
	}
	else
	{
		printf("source language: unknown / ");
	}

	int len = sym->ver[0];
	char name[258];
	strncpy(name, (char*)sym->ver+1, len);
	name[len] = 0;
	printf("\n\tver: %s", name);

	printf("\n");
}

void CorMetadata(FILE* fp, IMAGE_SECTION_HEADER* SectionHeader);

int ParseCOFF(COFFParser* pImage)
{

	/*
	if (fread(&header, 1, sizeof(header), fp) != sizeof(header))
		return -1;

	printf("Header\n");
	*/

	if (pImage->m_header->Machine == 0x14c)
	{
		printf("\tMachine: Intel 386 compatible\n");
	}
	else if (pImage->m_header->Machine == 0x268)
	{
		printf("\tMachine: Motorola 68000 series\n");
	}
	else
	{
		printf("\tUnknown machine type\n");
	}

	if (pImage->m_header->Characteristics & IMAGE_FILE_DLL)
	{
		printf("\tDLL\n");
	}
	else if (pImage->m_header->Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE)
	{
		printf("\tEXE\n");
	}
	else
	{
		printf("\tObject\n");
	}

	printf("\tNumber of Sections: %d\n", pImage->GetNumberOfSections());
	printf("\tNumber of Symbols: %d\n", pImage->GetNumberOfSymbols());
	printf("\tCharacteristics (0x%x)\n", pImage->m_header->Characteristics);

	if (pImage->m_header->Characteristics & IMAGE_FILE_RELOCS_STRIPPED) printf("IMAGE_FILE_RELOCS_STRIPPED\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) printf("IMAGE_FILE_EXECUTABLE_IMAGE\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_LINE_NUMS_STRIPPED) printf("IMAGE_FILE_LINE_NUMS_STRIPPED\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_LOCAL_SYMS_STRIPPED) printf("IMAGE_FILE_LOCAL_SYMS_STRIPPED\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_AGGRESSIVE_WS_TRIM) printf("IMAGE_FILE_AGGRESSIVE_WS_TRIM\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE) printf("IMAGE_FILE_LARGE_ADDRESS_AWARE\n");
//	if (pImage->header->Characteristics & IMAGE_FILE_16BIT_MACHINE) printf("IMAGE_FILE_16BIT_MACHINE\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_BYTES_REVERSED_LO) printf("IMAGE_FILE_BYTES_REVERSED_LO\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_32BIT_MACHINE) printf("IMAGE_FILE_32BIT_MACHINE\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_DEBUG_STRIPPED) printf("IMAGE_FILE_DEBUG_STRIPPED\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) printf("IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_SYSTEM) printf("IMAGE_FILE_SYSTEM\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_DLL) printf("IMAGE_FILE_DLL\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_UP_SYSTEM_ONLY) printf("IMAGE_FILE_UP_SYSTEM_ONLY\n");
	if (pImage->m_header->Characteristics & IMAGE_FILE_BYTES_REVERSED_HI) printf("IMAGE_FILE_BYTES_REVERSED_HI\n");

//	IMAGE_DATA_DIRECTORY* DataDirectory = NULL;

	if (pImage->m_optionalStandardHeader)
	{
		//long optionalHeaderStartPos = ftell(fp);

		/*
		if (header.SizeOfOptionalHeader < sizeof(OptionalStandardHeader))
		{
			printf("Size of optional header is too small");
			return -1;
		}
		*/
	//	OptionalStandardHeader optionalStandardHeader;
	//	if (fread(&optionalStandardHeader, 1, sizeof(optionalStandardHeader), fp) != sizeof(optionalStandardHeader))
	//		return -1;

		printf("\tTotal code size: 0x%x\n", pImage->m_optionalStandardHeader->SizeOfCode);
		printf("\tInitialized Data Size: 0x%x\n", pImage->m_optionalStandardHeader->SizeOfInitializedData);
		printf("\tUninitialized Data Size: 0x%x\n", pImage->m_optionalStandardHeader->SizeOfUninitializedData);
		printf("\tBase of Code: 0x%x\n", pImage->m_optionalStandardHeader->BaseOfCode);
		printf("\tAddress of EntryPoint: 0x%x\n", pImage->m_optionalStandardHeader->AddressOfEntryPoint);

		if (pImage->m_optionalStandardHeader->Magic == 0x10b)//	PE32
		{
		//	DWORD	BaseOfData;//	Address, relative to image base, of beginning of data section, when loaded into memory.
		//	fread(&BaseOfData, 4, 1, fp);

			printf("\tBase of Data: 0x%x\n", pImage->BaseOfData);

			WindowsHeader windowsHeader = *pImage->m_windowsHeader;
		//	fread(&windowsHeader, sizeof(windowsHeader), 1, fp);

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

#if 0
			DataDirectory = new IMAGE_DATA_DIRECTORY[windowsHeader.NumberOfRvaAndSizes];

			for (int i = 0; i < windowsHeader.NumberOfRvaAndSizes; i++)
			{
				//IMAGE_DATA_DIRECTORY imageDataDir;
				fread(&DataDirectory[i], sizeof(IMAGE_DATA_DIRECTORY), 1, fp);
			}
#endif
		}
		else if (pImage->m_optionalStandardHeader->Magic == 0x20b)//	PE32+
		{
			printf("PE32+\n");
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
	}

	{
		IMAGE_SYMBOL* psymbol = (IMAGE_SYMBOL*)(pImage->m_fbuf + pImage->m_header->PointerToSymbolTable);

		for (int i = 0; i < pImage->m_header->NumberOfSymbols; i++)
		{
		//	const char* name;

			printf("%d\t", i);

			IMAGE_SYMBOL* symbol = &psymbol[i];

			if (symbol->N.Name.Short)
			{
				printf("%.8s\t", symbol->N.ShortName);
				//Symbols[s].name = symbol.N.ShortName;
			}
			else if (symbol->N.Name.Long >= 4)
			{
				printf("%s\t", pImage->m_pStringData + symbol->N.Name.Long-4);

				//Symbols[s].name = StringData + symbol.N.Name.Long-4;
			}
			else
			{
				printf("Corrupt symbol table");
				//return -1;
			}

			printf("Value %d, SectionNumber %d, Type %d\t", symbol->Value, symbol->SectionNumber, symbol->Type);

			/*
			if (!strncmp((char*)symbol->N.ShortName, ".drectve", 8))
			{
				strcpy((char*)symbol->N.ShortName, "dummy");
			}

			if (!strncmp((char*)symbol->N.ShortName, "@comp.id", 8))
			{
				strcpy((char*)symbol->N.ShortName, "dummy");
			}

			if (symbol->StorageClass == IMAGE_SYM_CLASS_NULL)
			{
				strcpy((char*)symbol->N.ShortName, "dummy");
			}
			else
			*/
			if (symbol->StorageClass == IMAGE_SYM_CLASS_STATIC)
			{
				printf("Static\t");

				if (symbol->Value == 0)
				{
					printf("Section\n");

					const IMAGE_AUX_SYMBOL_SECTION* section = (const IMAGE_AUX_SYMBOL_SECTION*)(symbol+1);

					printf("\tLength: 0x%x\n", section->Length);
					printf("\tCheckSum: 0x%x\n", section->CheckSum);
					printf("\tNumber: 0x%x\n", section->Number);
					printf("\tSelection: 0x%x\n", section->Selection);

					/*
					strcpy((char*)symbol->N.ShortName, "dummy");
					symbol->StorageClass = IMAGE_SYM_CLASS_NULL;
					(symbol+1)->StorageClass = IMAGE_SYM_CLASS_NULL;
					*/
				}
				else
				{
				}
			}
			else if (symbol->StorageClass == IMAGE_SYM_CLASS_FILE)
			{
				printf("File\t");

				uint8* filename = new uint8[IMAGE_SIZEOF_SYMBOL * symbol->NumberOfAuxSymbols +1];
				memcpy(filename, symbol+1, IMAGE_SIZEOF_SYMBOL * symbol->NumberOfAuxSymbols);
				filename[IMAGE_SIZEOF_SYMBOL * symbol->NumberOfAuxSymbols] = 0;

				printf("%s", filename);

				delete filename;
				//s += symbol.NumberOfAuxSymbols;
			}
			else if (
				symbol->StorageClass == IMAGE_SYM_CLASS_EXTERNAL &&
				symbol->Type == 0x20 &&
				symbol->SectionNumber > 0)
			{
				printf("External Function\t");

				// function definition
				const IMAGE_AUX_SYMBOL_FUNCTION* function = (const IMAGE_AUX_SYMBOL_FUNCTION*)(symbol+1);

			}
			else if (symbol->StorageClass == IMAGE_SYM_CLASS_FUNCTION)
			{
				printf("Function\t");
			}

			printf("%d\n", symbol->NumberOfAuxSymbols);

			i += symbol->NumberOfAuxSymbols;

				printf("\n");
		}

		/*
		for (int i = 0; i < pImage->NumberOfNameSymbols; i++)
		{
			const COFFParser::SYMBOL* is = &pImage->NameSymbols[i];

			printf("%s\n", is->name);
		}
		*/
	}

#if 0
	struct SYMBOL
	{
		IMAGE_SYMBOL is;
		BYTE* name;		
	};

	SectionHeader = new IMAGE_SECTION_HEADER[header.NumberOfSections];
	SYMBOL* Symbols = new SYMBOL[header.NumberOfSymbols];
	BYTE* StringData = NULL;

	for (int j = 0; j < header.NumberOfSections; j++)
	{
		fread(&SectionHeader[j], sizeof(IMAGE_SECTION_HEADER), 1, fp);
	}

	if (header.PointerToSymbolTable)
	{
		printf("Symbols:\n");
		// The string table is right after all the symbols
		DWORD PointerToStringTable = header.PointerToSymbolTable + header.NumberOfSymbols * IMAGE_SIZEOF_SYMBOL;
		fseek(fp, PointerToStringTable, SEEK_SET);
		DWORD StringTableSize;
		fread(&StringTableSize, 1, 4, fp);	// This includes the 4byte size
		StringTableSize -= 4;
		StringData = NULL;
		if (StringTableSize > 0)
		{
			StringData = new BYTE[StringTableSize];
			if (StringData == NULL)
			{
				printf("Not enough memory\n");
				exit(1);
			}

			fread(StringData, 1, StringTableSize, fp);
		}

		fseek(fp, header.PointerToSymbolTable, SEEK_SET);
		for (int s = 0; s < header.NumberOfSymbols; s++)
		{
			IMAGE_SYMBOL& symbol = Symbols[s].is;

			fread(&symbol, sizeof(symbol), 1, fp);
			ASSERT(sizeof(symbol) == IMAGE_SIZEOF_SYMBOL);

			char* Type[] =
			{
 				"NULL", //IMAGE_SYM_DTYPE_NULL	0	No derived type; the symbol is a simple scalar variable. 	   
				"Pointer", //IMAGE_SYM_DTYPE_POINTER	1	Pointer to base type.	   
				"Functions", // IMAGE_SYM_DTYPE_FUNCTION	2	Function returning base type.	   
				"Array", //IMAGE_SYM_DTYPE_ARRAY	3	Array of base type.	 
			};

			printf("%d ", s);
			if (symbol.N.Name.Short)
			{
				printf("%.8s\t", symbol.N.ShortName);
				Symbols[s].name = symbol.N.ShortName;
			}
			else if (symbol.N.Name.Long >= 4)
			{
				printf("%s\t", StringData + symbol.N.Name.Long-4);

				Symbols[s].name = StringData + symbol.N.Name.Long-4;
			}
			else
			{
				printf("Corrupt symbol table");
				return -1;
			}

			printf(" Section Number: %d", symbol.SectionNumber);
			printf(" Type: %d/%s", symbol.Type&0xFF, Type[symbol.Type>>8]);
			printf(" Storage: %s", StorageClassString[symbol.StorageClass]);
			printf(" Value: %d", symbol.Value);

			printf("\n");

			if (s + symbol.NumberOfAuxSymbols >= header.NumberOfSymbols)
			{
				printf("Corrupt symbol table\n");
				return -1;
			}

			if (symbol.StorageClass == IMAGE_SYM_CLASS_FILE)
			{
				BYTE* filename = new BYTE[IMAGE_SIZEOF_SYMBOL * symbol.NumberOfAuxSymbols +1];
				fread(filename, 1, IMAGE_SIZEOF_SYMBOL * symbol.NumberOfAuxSymbols, fp);
				filename[IMAGE_SIZEOF_SYMBOL * symbol.NumberOfAuxSymbols] = 0;

				printf("\t%s\n", filename);

				delete filename;
				s += symbol.NumberOfAuxSymbols;
			}
			else
			{
				printf("aux: %d\n", symbol.NumberOfAuxSymbols);

				for (int a = 0; a < symbol.NumberOfAuxSymbols; a++)
				{
					BYTE aux[IMAGE_SIZEOF_SYMBOL];
					fread(aux, IMAGE_SIZEOF_SYMBOL, 1, fp);

					s++;
				}
			}
		}
	}
	printf("\n");
#endif

	{
		int nstabs = 0;
		uint8* code = NULL;
		filepointer<nlist> stab;
		/*filepointer<char>*/ char* stabstr;

		for (int j = 0; j < pImage->m_header->NumberOfSections; j++)
		{
			/*
			char SectionName[9];	// null-terminated section name
			strncpy(SectionName, (char*)SectionHeader[j].Name, 8);
			SectionName[8] = 0;
			*/

			printf("--- %d, Section %.8s\n", j+1, pImage->m_SectionHeader[j].Name);

			printf("\tVirtual Size: 0x%x\n", pImage->m_SectionHeader[j].Misc.VirtualSize);
			printf("\tVirtual Address: 0x%x\n", pImage->m_SectionHeader[j].VirtualAddress);
			printf("\tSize of Raw Data: 0x%x\n", pImage->m_SectionHeader[j].SizeOfRawData);
			printf("\tPointer To Raw Data: 0x%x\n", pImage->m_SectionHeader[j].PointerToRawData);
			printf("\tPointer To Line Numbers: 0x%x\n", pImage->m_SectionHeader[j].PointerToLinenumbers);
			printf("\tPointer To Relocations: 0x%x\n", pImage->m_SectionHeader[j].PointerToRelocations);
			printf("\tNumber Of Line Numbers: %d\n", pImage->m_SectionHeader[j].NumberOfLinenumbers);
			printf("\tNumber Of Relocations: %d\n", pImage->m_SectionHeader[j].NumberOfRelocations);
			printf("\tCharacteristics: 0x%x\n", pImage->m_SectionHeader[j].Characteristics);

			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_CNT_CODE) printf("\t\tCODE\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA) printf("\t\tINITIALIZED DATA\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA) printf("\t\tUNINITIALIZED DATA\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_LNK_REMOVE) printf("\t\tREMOVE\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_LNK_COMDAT) printf("\t\tCOMDATA\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_MEM_READ) printf("\t\tREAD\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_MEM_WRITE) printf("\t\tWRITE\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_MEM_EXECUTE) printf("\t\tEXECUTE\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_MEM_DISCARDABLE) printf("\t\tDISCARDABLE\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_LNK_INFO) printf("\t\tLNK_INFO\n");
			if (pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_ALIGN_1BYTES) printf("\t\tALIGN_1BYTES\n");
			printf("\n");

		//	pImage->SectionHeader[j].Characteristics &= ~IMAGE_SCN_LNK_INFO;
		//	pImage->SectionHeader[j].Characteristics &= ~IMAGE_SCN_ALIGN_1BYTES;

			/*
			if (!strncmp((char*)pImage->SectionHeader[j].Name, ".drectve", 8))
			{
				strcpy((char*)pImage->SectionHeader[j].Name, "dummy");
			}
			*/

			IMAGE_LINENUMBER* pLineNumbers = (IMAGE_LINENUMBER*)(pImage->m_fbuf + pImage->m_SectionHeader[j].PointerToLinenumbers);

			if (pImage->m_SectionHeader[j].PointerToLinenumbers)
			{
				for (int i = 0; i < pImage->m_SectionHeader[j].NumberOfLinenumbers; i++)
				{
					printf("%d %d\n", pLineNumbers[i].Type.VirtualAddress, pLineNumbers[i].Linenumber);
				}
			}

			if (pImage->m_SectionHeader[j].PointerToRelocations)
			{
				IMAGE_SYMBOL* Symbols = (IMAGE_SYMBOL*)(pImage->m_fbuf + pImage->m_header->PointerToSymbolTable);

				IMAGE_RELOCATION* pRelocations = (IMAGE_RELOCATION*)(pImage->m_fbuf + pImage->m_SectionHeader[j].PointerToRelocations);

				printf("Section Relocations:\n");
				for (int i = 0; i < pImage->m_SectionHeader[j].NumberOfRelocations; i++)
				{
					IMAGE_RELOCATION* ImageReloc = &pRelocations[i];

					if (ImageReloc->SymbolTableIndex >= pImage->m_header->NumberOfSymbols)
					{
						printf("Corrupt relocation table\n");
						return -1;
					}

				//	printf("  %s\t", Symbols[ImageReloc->SymbolTableIndex].name);
					printf("  %d\t", ImageReloc->SymbolTableIndex);
					printf("  %s ", I386_RelType[ImageReloc->Type]);
					printf("  address: %x\n", ImageReloc->VirtualAddress - pImage->m_SectionHeader[j].VirtualAddress);
				}
			}

#if 0
			fseek(fp, SectionHeader[j].PointerToRawData, SEEK_SET);
			DWORD size = SectionHeader[j].SizeOfRawData;

			long startpos = ftell(fp);

			if (!strncmp((const char*)SectionHeader[j]->Name, ".rsrc", 8))
			{
				ReadResourceTable(1, startpos, fp);
			}
			else if (!strncmp((const char*)SectionHeader[j].Name, ".text", 5))
			{
				code = new BYTE[size];
				if (code)
				{
					fread(code, size, 1, fp);

//#if 0
				//	ReadCode_x86(windowsHeader.ImageBase + SectionHeader[j].VirtualAddress, code, min(size, 236));
//#endif
				//	delete[] code;
				}
				else
				{
					printf("Not enough memory\n");
					exit(1);
				}
			}
			else if (!strncmp((const char*)SectionHeader[j].Name, ".reloc", 8))	// Image-only
			{
			}
			else if (!strncmp((const char*)SectionHeader[j].Name, ".drectve", 8))
			{
				//if (IMAGE_SCN_LNK_INFO )	// Ignore by linker if this isn't also set
				{
					char* string = new char[size+1];
					if (string == NULL)
					{
						printf("Not enough memory\n");
						exit(1);
					}

					fread(string, size, 1, fp);
					string[size] = 0;

					printf("Linker directives:\n%s\n", string);

					delete[] string;
				}
			}
#endif
			if (!strncmp((const char*)pImage->m_SectionHeader[j].Name, ".text", 8))
			{
				int size = pImage->GetDataSize(j);
				uint8* data = pImage->GetData(j);

				/*
				FILE* fp = fopen("C:/text", "wb");
				fwrite(data, size, 1, fp);
				fclose(fp);
				*/
			}
			else if (!strncmp((const char*)pImage->m_SectionHeader[j].Name, ".debug$S", 8))
			{
				// stream of CV4 symbol records (should only appear in object files)

			//	BYTE* data = new BYTE[size];
			//	fread(data, 1, size, fp);
				int size = pImage->GetDataSize(j);
				uint8* data = pImage->GetData(j);

				FILE* fp = fopen("C:/debugS", "wb");
				fwrite(data, size, 1, fp);
				fclose(fp);

			//	WORD count = ((WORD*)data)[0];
			//	WORD offset = ((WORD*)data)[1];
				uint8* p = data;//+4+offset;

			//	DWORD signature = *(DWORD*)p; p += 4;

				if (!(pImage->m_SectionHeader[j].Characteristics & IMAGE_SCN_LNK_COMDAT))
				{
					DWORD signature = *(DWORD*)p; p += 4;
					printf("signature: %d\n", signature);
				}

				//for (int i = 0; i < count; i++)
				while (p < data+size)
				{
					/*
					if (p >= data+size)
					{
						printf("oops");
						break;
					}
					*/
					uint16  reclen = ((uint16*)p)[0];         // Record length
					uint16  rectyp = ((uint16*)p)[1];        // S_LDATA32, S_GDATA32 or S_PUB32

					printf("rectyp: 0x%x, len: %d\t", rectyp, reclen);

					switch (rectyp)
					{
					case S_COMPILE:
						{
							CFLAGSYM* sym = (CFLAGSYM*)p;
							CompileSym(sym);
						}
						break;

					case S_OBJNAME:
						{
							OBJNAMESYM* sym = (OBJNAMESYM*)p;
							uint8 len = (uint8)sym->name[0];
							char name[258];
							strncpy(name, (char*)sym->name+1, len);
							name[len] = 0;

							printf("%d, %s", sym->signature, name);

							memcpy(sym->name+1, "Hello", 5);
						}
						break;

					case S_LABEL32:
						{
							LABELSYM32* sym = (LABELSYM32*)p;
							int len = sym->name[0];
							char name[258];
							strncpy(name, (char*)sym->name+1, len);
							name[len] = 0;
							printf("%s", name);
						}
						break;

					case S_BLOCK32:
						{
							BLOCKSYM32* sym = (BLOCKSYM32*)p;
							int len = sym->name[0];
							char name[258];
							strncpy(name, (char*)sym->name+1, len);
							name[len] = 0;
							printf("%s / len: %d", name, sym->len);
						}
						break;

					case S_GPROC_32:
						{
							PROCSYM_32* sym = (PROCSYM_32*)p;
							int len = sym->name[0];
							char name[258];
							strncpy(name, (char*)sym->name+1, len);
							name[len] = 0;
							printf("%s / len: %d", name, sym->len);

							printf("off offset: %x\n", (uint8*)&sym->off - data);

							sym->len = 20;
						}
						break;

					case S_BPREL_32:
						{
							BPRELSYM32* sym = (BPRELSYM32*)p;
							int len = sym->name[0];
							char name[258];
							strncpy(name, (char*)sym->name+1, len);
							name[len] = 0;
							printf("%s", name);
						}
						break;

					case S_UDT_32:
						{
							UDTSYM32* sym = (UDTSYM32*)p;
							int len = sym->name[0];
							char name[258];
							strncpy(name, (char*)sym->name+1, len);
							name[len] = 0;
							printf("%s", name);
						}
						break;

					case S_END:
						{
							printf("end");
						}
						break;
					}

					printf("\n");

					reclen += 2;
					//reclen = (reclen+3) & ~3;
					p += reclen;
				}

			}
			else if (!strncmp((const char*)pImage->m_SectionHeader[j].Name, ".debug$T", 8))
			{
				// stream of CV4 type records (should only appear in object files)

				int size = pImage->GetDataSize(j);
				uint8* data = pImage->GetData(j);

				FILE* fp = fopen("C:/debugT", "wb");
				fwrite(data, size, 1, fp);
				fclose(fp);

				uint8* p = data;

				DWORD signature = *(DWORD*)p; p += 4;
				printf("signature: %d\n", signature);

				while (p < data+size)
				{
					TYPTYPE* ty = (TYPTYPE*)p;

					printf("type: 0x%X, len: %d\n", ty->leaf, ty->len);

				//	WORD leaf = *(WORD*)p; p += 2;
					if (ty->leaf == LF_MODIFIER)
					{
						printf("modifier");
					}
					else if (ty->leaf == LF_POINTER)
					{
						printf("modifier");
					}
					else if (ty->leaf == LF_POINTER_32)
					{
						printf("pointer32");
						lfPointer32* lf = (lfPointer32*)(p+2);
					}
					else if (ty->leaf == LF_ARRAY)
					{
						printf("array");
					}
					else if (ty->leaf == LF_CLASS)
					{
						printf("class");
					}
					else if (ty->leaf == LF_PROCEDURE)
					{
						printf("procedure");
						lfProc* lf = (lfProc*)(p+2);
					}
					else if (ty->leaf == LF_PROCEDURE_32)
					{
						printf("procedure32");
						lfProc* lf = (lfProc*)(p+2);
					}
					else if (ty->leaf == LF_TYPESERVER)
					{
						lfTypeServer* server = (lfTypeServer*)(ty+1);
						printf("typeserver");
					}
					else if (ty->leaf == LF_ARGLIST_32)
					{
						printf("arglist\n");

						lfArgList_32* lf = (lfArgList_32*)(p+2);
					}
					printf("\n");

					p += ty->len+2;
				}

	//			delete [] data;
			}
#if 0
			else if (!strncmp((const char*)SectionHeader[j].Name, ".stab", 8))
			{
				stab = fp;

				nstabs = size / sizeof(nlist);

				/*
				BYTE* data = new BYTE[size];
				fread(data, 1, size, fp);

				BYTE* p = data;


				delete [] data;
				*/
			}
			else if (!strncmp((const char*)SectionHeader[j].Name, ".stabstr", 8))
			{
				stabstr = new char[size];
				fread(stabstr, size, 1, fp);
			}
			else
			{
				int len = min(size, 800);
				BYTE data[800];
				fread(data, 1, len, fp);

				for (int i = 0; i < len; i++)
				{
				//	if ((i % 80)) printf("\n");
				
					if (data[i] >= 30 && data[i] <= 127)
					{
						printf("%c", data[i]);
					}
					else
					{
						printf(".");
					}

				}
			}
#endif

		//	fseek(fp, pos, SEEK_SET);

			printf("\n\n");
		}

#if 0
		if (stab != NULL)
		{
			char* sourceFileName = NULL;
			for (int i = 0; i < nstabs; i++)
			{
			//	nlist* n = (nlist*)p;
				filepointer<nlist> pSymbol = stab + i;//(ObjectSymbol*)p;
				if (pSymbol->n_type == N_SO)
				{
					char* name = stabstr + pSymbol->n_un.n_strx;
				// If it ends with a slash, it's the directory where it was compiled, so keep searching
					if (name[strlen(name)-1] != '/')
					{
						sourceFileName = name;
						break;
					}
				}
			}

			std::vector<std::string> lines;
			if (sourceFileName)
			{
				FILE* sfp = fopen(sourceFileName, "r");

				std::string str;

				while (!feof(sfp))
				{
					int c = fgetc(sfp);

					str += c;

					if (c == '\n')
					{
						lines.push_back(str);
						str = "";
					}
				}
				if (str.length())
					lines.push_back(str);

				fclose(sfp);
			}

			int nstab = 0;

			CX86Context c;
			c.pc = code;
			DWORD last_fun_address = 0;
			DWORD line_address = 0;
			int start_line = 0;
			int end_line = 0;

			DWORD base = windowsHeader.ImageBase + SectionHeader[0/*TODO*/].VirtualAddress;
			while (c.pc < code+40)
			{
				// Collect the lines that precede the next intruction
				while ((nstab < nstabs) &&
					line_address <= (c.pc - code + base))
				{
					filepointer<nlist> pSymbol = stab + nstab;

					if (pSymbol->n_type == N_FUN)
					{
						last_fun_address = pSymbol->n_value;
					}
					else if (pSymbol->n_type == N_SLINE)
					{
						int address = last_fun_address + pSymbol->n_value;

						// If this lines address is past, we break out and come back
						// to it in the next iteration
						if (address > (c.pc - code + base))
							break;

						line_address = address;
						end_line = pSymbol->n_desc;
					}

					nstab++;
				}

				{
					for (int i = start_line; i < end_line; i++)
					{
						printf("%5.d: %s", i+1, lines[i].c_str());
					}
					start_line = end_line;
				}

				printf("%6.6x ", c.pc - code + base);

				BYTE* p = c.pc;

				printf("%x\t", *p);
				disasm_x86(&c);

				printf("\n");
			}

#if 0

			int brace = 0;

				if ((*pSymbol).n_type >= 0x20)
				{
					if (pSymbol->n_type == N_RBRAC)
					{
						brace--;
					}

					for (int j = 0; j < brace; j++)
						printf("  ");

					if (pSymbol->n_type == N_SO)
					{
						printf("SourceFile: %s / start address: %x\n", stabstr + pSymbol->n_un.n_strx, pSymbol->n_value);
					}
					else if (pSymbol->n_type == N_FUN)
					{
						printf("function %s / address: %x\n", stabstr + pSymbol->n_un.n_strx, pSymbol->n_value);

					// the start of the function is in the next N_SLINE symbol.
					}
					else if (pSymbol->n_type == N_LSYM)
					{
						printf("stack: %s\n", stabstr + pSymbol->n_un.n_strx);
					}
					else if (pSymbol->n_type == N_RSYM)
					{
						printf("register: %s\n", stabstr + pSymbol->n_un.n_strx);
					}
					else if (pSymbol->n_type == N_PSYM)
					{
						printf("parameter: %s\n", stabstr + pSymbol->n_un.n_strx);
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
				}
#endif

			//	p += sizeof(nlist);
		}
#endif
	}

	if (pImage->m_windowsHeader && pImage->m_windowsHeader->NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_SECURITY)
	{
		if (pImage->m_DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress)
		{
			printf("Security\n");

			//long pos = ftell(fp);

			DWORD fpos = pImage->RVA2FilePos(pImage->m_DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress);

			//pImage->m_fbuf + fpos;//fseek(fp, fpos, SEEK_SET);

			WIN_CERTIFICATE sec = *(WIN_CERTIFICATE*)(pImage->m_fbuf + fpos);

			MemoryByteStream* stream = new MemoryByteStream((uint8*)(pImage->m_fbuf+fpos+8), sec.dwLength);
			Security::ReadContentInfo(stream);

//			fseek(fp, 
		}
	}

#if 0
	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_EXPORT)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
		{
			printf("Exports\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_IMPORT)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)
		{
			printf("Imports\n");

			long pos = ftell(fp);

	//		long abspos = SectionHeader[i].PointerToRawData + DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - SectionHeader[i].VirtualAddress;

			DWORD fpos = RVA2FilePos(DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

			fseek(fp, fpos, SEEK_SET);

			do
			{
				IMAGE_IMPORT_DIRECTORY importTable;
				if (fread(&importTable, 1, sizeof(importTable), fp) != sizeof(importTable))
				{
					return -1;
				}

				if (importTable.ImportLookupTable == 0)
					break;

				long pos = ftell(fp);

				DWORD fpos;
				
				fpos = RVA2FilePos(importTable.Name);
				if (fpos == -1)
				{
					printf("Corrupted file");
					return -1;
				}

				fseek(fp, fpos, SEEK_SET);
				char name[512] = {0};
				fread(name, 50, 1, fp);
				printf("\tDLL %s\n", name);

				fpos = RVA2FilePos(importTable.ImportLookupTable);
				if (fpos == -1)
				{
					printf("Corrupted file");
					return -1;
				}
				fseek(fp, fpos, SEEK_SET);
				while (1)
				{
					DWORD dword;
					fread(&dword, 1,4, fp);
					if (dword == 0)
						break;

					if (dword & 0x80000000)
					{
						dword &= ~0x80000000;
						// ordinal
					}
					else
					{
						long pos = ftell(fp);

						fpos = RVA2FilePos(dword);

						fseek(fp, fpos, SEEK_SET);

						WORD hint;
						fread(&hint, 1, 2, fp);
						char name[512] = {0};
						fread(name, 50, 1, fp);
						printf("\t\t%s\n", name);

						fseek(fp, pos, SEEK_SET);
					}
				}

				fseek(fp, pos, SEEK_SET);
			}
			while (1);

			fseek(fp, pos, SEEK_SET);
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_RESOURCE)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress)
		{
			printf("Resource\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_EXCEPTION)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress)
		{
			printf("Exception\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_SECURITY)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress)
		{
			printf("Security\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_BASERELOC)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress)
		{
			printf("Basereloc\n");
		}
	}
#endif

	if (pImage->m_windowsHeader)
	{
		if (pImage->m_windowsHeader->NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_DEBUG)
		{
			if (pImage->m_DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress)
			{
				printf("Debug\n");

			//	long pos = ftell(fp);

				DWORD fpos = pImage->RVA2FilePos(pImage->m_DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress);

				long entries = pImage->m_DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size / sizeof(IMAGE_DEBUG_DIRECTORY);
			//	fseek(fp, fpos, SEEK_SET);

				IMAGE_DEBUG_DIRECTORY* directoryT = (IMAGE_DEBUG_DIRECTORY*)(pImage->m_fbuf + fpos);

				for (int i = 0; i < entries; i++)
				{
					IMAGE_DEBUG_DIRECTORY& directory = directoryT[i];
					//directory = m_fp + fpos + fread(&directory, 1, sizeof(IMAGE_DEBUG_DIRECTORY), fp);

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

					//fseek(fp, directory.PointerToRawData, SEEK_SET);

					uint8* data = pImage->m_fbuf + directory.PointerToRawData;//new BYTE[directory.SizeOfData];
					//fread(data, directory.SizeOfData, 1, fp);

					if (directory.Type == IMAGE_DEBUG_TYPE_FPO)
					{
						FPO_DATA* fpo = (FPO_DATA*)data;

						printf("SizeOfData: %d\n\n", directory.SizeOfData);

						printf("ulOffStart: %d\n", fpo->ulOffStart);             // offset 1st byte of function code
						 printf("cbProcSize: %d\n", fpo->cbProcSize);             // # bytes in function
						 printf("cdwLocals: %d\n", fpo->cdwLocals);              // # bytes in locals/4
						 printf("cdwParams: %d\n", fpo->cdwParams);              // # bytes in params/4
						 printf("cbProlog: %d\n", fpo->cbProlog);           // # bytes in prolog
						 printf("cbRegs: %d\n", fpo->cbRegs);           // # regs saved
						 printf("fHasSEH: %d\n", fpo->fHasSEH);           // TRUE if SEH in func
						 printf("fUseBP: %d\n", fpo->fUseBP);           // TRUE if EBP has been allocated
						 printf("reserved: %d\n", fpo->reserved);           // reserved for future use
						 printf("cbFrame: %d\n", fpo->cbFrame);           // frame type
					}
					else if (directory.Type == IMAGE_DEBUG_TYPE_MISC)
					{
						IMAGE_DEBUG_MISC* misc = (IMAGE_DEBUG_MISC*)data;

						printf("\n");
						if (misc->DataType == IMAGE_DEBUG_MISC_EXENAME)
							printf("DataType: IMAGE_DEBUG_MISC_EXENAME\n");
						else
							printf("DataType: %d\n", misc->DataType);
						printf("Length: %d\n", misc->Length);
						printf("Unicode: %d\n", misc->Unicode);
						printf("Data: %s\n", misc->Data);
					}
					else if (directory.Type == IMAGE_DEBUG_TYPE_CODEVIEW)
					{
						uint8* p = data;

						{
							FILE* f = fopen("C:/data", "wb");
							fwrite(data, directory.SizeOfData, 1, f);
							fclose(f);
						}

						char* signature = (char*)p;
						long offset = *(long*)(p+4);
						printf("%4.4s/%d", signature, offset);

						printf("\n");
						while (offset)
						{
							OMFDirHeader* dirheader = (OMFDirHeader*)(p+offset);
							printf("flags: %d\n", dirheader->flags);

							OMFDirEntry* direntry = (OMFDirEntry*)(dirheader+1);

							for (int i = 0; i < dirheader->cDir; i++)
							{
								char* str;

								switch (direntry->SubSection)
								{
								case sstModule: str = "sstModule"; break;
								case sstAlignSym: str = "sstAlignSym"; break;
								case sstSrcModule: str = "sstSrcModule"; break;
								case sstLibraries: str = "sstLibraries"; break;
								case sstGlobalSym: str = "sstGlobalSym"; break;
								case sstGlobalPub: str = "sstGlobalPub"; break;
								case sstGlobalTypes: str = "sstGlobalTypes"; break;
								case sstSegMap: str = "sstSegMap"; break;
								case sstFileIndex: str = "sstFileIndex"; break;
								case sstStaticSym: str = "sstStaticSym"; break;
								default:
									str = "unknown";
								}

								{
									char filepath[256];
									if (direntry->iMod != -1)
										sprintf(filepath, "C:\\%s%d", str, direntry->iMod);
									else
										sprintf(filepath, "C:\\%s", str);

									FILE* f = fopen(filepath, "wb");
									fwrite(p+direntry->lfo, direntry->cb, 1, f);
									fclose(f);
								}

								switch (direntry->SubSection)
								{
								case sstFileIndex:
									{
										printf("%s %d - ", str, direntry->iMod);

										OMFFileIndex* fileindex = (OMFFileIndex*)(p+direntry->lfo);
										uint16* ModStart = (uint16*)(fileindex+1);
										uint16* cRefCnt = ModStart + fileindex->cMod;
										uint32* NameRef = (uint32*)(cRefCnt + fileindex->cMod);
										char* Names = (char*)(NameRef + fileindex->cRef);

									}
									break;

								case sstSegMap:
									{
										printf("%s %d - ", str, direntry->iMod);

										OMFSegMap* segmap = (OMFSegMap*)(p+direntry->lfo);

										for (int i = 0; i < segmap->cSeg; i++)
										{
										//	if (segmap->rgDesc[i].f32Bit)
										//		printf("32bit\n");

											printf("----------------\n");
											printf("reserved0: %d\n", segmap->rgDesc[i].f.reserved0);
											printf("fGroup: %d\n", segmap->rgDesc[i].f.fGroup);
											printf("reserved1: %d\n", segmap->rgDesc[i].f.reserved1);
											printf("fAbs: %d\n", segmap->rgDesc[i].f.fAbs);
											printf("fSel: %d\n", segmap->rgDesc[i].f.fSel);
											printf("reserved2: %d\n", segmap->rgDesc[i].f.reserved2);
											printf("f32Bit: %d\n", segmap->rgDesc[i].f.f32Bit);
											printf("fExecute: %d\n", segmap->rgDesc[i].f.fExecute);
											printf("fWrite: %d\n", segmap->rgDesc[i].f.fWrite);
											printf("fRead: %d\n", segmap->rgDesc[i].f.fRead);

											printf("ovl: %d\n", segmap->rgDesc[i].ovl);
											printf("group: %d\n", segmap->rgDesc[i].group);
											printf("frame: %d\n", segmap->rgDesc[i].frame);
											printf("iSegName: %d\n", segmap->rgDesc[i].iSegName);
											printf("iClassName: %d\n", segmap->rgDesc[i].iClassName);
											printf("offset: %d(0x%x)\n", segmap->rgDesc[i].offset, segmap->rgDesc[i].offset);
											printf("cbSeg: %d(0x%x)\n", segmap->rgDesc[i].cbSeg, segmap->rgDesc[i].cbSeg);

										}

										//OMFSymHash* pSymHash = (OMFSymHash*)(p+direntry->lfo);
										printf("\n");
									}
									break;

								case sstAlignSym:
									{
										printf("%s %d - ", str, direntry->iMod);

										uint8* start = (p+direntry->lfo);
										SYMTYPE* pSym = (SYMTYPE*)(p+direntry->lfo);

									//	pSym = NextSym(pSym);
										while ((uint8*)pSym < start+direntry->cb)
										{
											printf("%d - ", (uint8*)pSym - start);

											switch (pSym->rectyp)
											{
											case S_COMPILE:
												{
													CompileSym((CFLAGSYM*)pSym);
												}
												break;

											case S_GPROC_32:
												{
													PROCSYM_32* pProcSym = (PROCSYM_32*)pSym;

													char name[258];
													strncpy(name, (char*)pProcSym->name+1, pProcSym->name[0]);
													name[pProcSym->name[0]] = 0;

													printf("S_GPROC_32 %s\n", name);
													printf("pParent: %d\n",  pProcSym->pParent);        // pointer to the parent
													printf("pEnd: %d\n",  pProcSym->pEnd);           // pointer to this blocks end
													printf("pNext: %d\n",  pProcSym->pNext);          // pointer to next symbol
													printf("len: %d\n",  pProcSym->len);            // Proc length
													printf("DbgStart: %d\n",  pProcSym->DbgStart);       // Debug start offset
													printf("DbgEnd: %d\n",  pProcSym->DbgEnd);         // Debug end offset
													printf("off: %d\n",  pProcSym->off);
													printf("seg: %d\n",  pProcSym->seg);
													printf("typind: %d\n",  pProcSym->typind);         // Type index
													printf("flags: %d\n",  pProcSym->flags.bAll);          // Proc flags

													printf("{\n");	// }
												}
												break;

											case S_THUNK32:
												{
													printf("thunk\n{\n");	// }
												}
												break;

											case S_BLOCK32:
												{
													BLOCKSYM32* pBlockSym = (BLOCKSYM32*)pSym;
													printf("pParent: %d\n",  pBlockSym->pParent);        // pointer to the parent
													printf("pEnd: %d\n",  pBlockSym->pEnd);           // pointer to this blocks end
													printf("off: %d\nlen: %d\n", pBlockSym->off, pBlockSym->len);
													printf(" {\n");	// }
												}
												break;

											case S_BPREL_32:
												{
													BPRELSYM_32* pRelSym = (BPRELSYM_32*)pSym;

													char name[258];
													strncpy(name, (char*)pRelSym->name, pRelSym->namelen);
													name[pRelSym->namelen] = 0;

													printf("%d %s, [ebp%+d]\n", pRelSym->typind, name, pRelSym->off);
												}
												break;

											case S_GDATA_32:
												{
													printf("data\n");
												}
												break;

											case S_OBJNAME:
												{
													OBJNAMESYM* pObjSym = (OBJNAMESYM*)pSym;

													uint8 len = (uint8)pObjSym->name[0];
													char name[258];
													strncpy(name, (char*)pObjSym->name+1, len);
													name[len] = 0;

													printf("%s\n", name);
												}
												break;

											case S_END:
												{
													// {
													printf("\n}\n");
												}
												break;

											default:
												printf("%x, %d\n", pSym->rectyp, pSym->reclen);
											}

											pSym = NextSym(pSym);
										}
										printf("\n");
									}
									break;

								case sstPublicSym:
									{
										ASSERT(0);
									}
									break;

								case sstStaticSym:
								case sstGlobalSym:
								case sstGlobalPub:
									{
										printf("%s %d - ", str, direntry->iMod);

										OMFSymHash* pSymHash = (OMFSymHash*)(p+direntry->lfo);

										uint8* start = (uint8*)(pSymHash+1);
										SYMTYPE* pSym = (SYMTYPE*)start;

										while ((uint8*)pSym < start + pSymHash->cbSymbol)
										{
											//SYMTYPE* pSym = (SYMTYPE*)p;
										//	int rectyp = ;
										//	if (rectyp & 0x1000) rectyp &= ~0x1000;
										//	ASSERT(rectyp > 0);
											switch (pSym->rectyp)
											{
											case S_PROCREF:
											case S_DATAREF:
												{
													REFSYM* pRefSym = (REFSYM*)pSym;

													if (pSym->rectyp == S_PROCREF)
													{
														printf("procref");

														PROCSYM* pProcSym = (PROCSYM*)((uint8*)start + pRefSym->ibSym);
													}
													else
														printf("dataref");
													
													printf(": imod %d, sumName: %d, ibSym: %d\n", pRefSym->imod, pRefSym->sumName, pRefSym->ibSym);

													uint8* proc = (data + pRefSym->ibSym);

												//	LPBYTE name = (LPBYTE)pSym + pSym->reclen;
												//	length += (*name + 1 + 3) & ~3;
												}
												break;

											case S_UDT_32:
												{
													UDTSYM32* pUdt = (UDTSYM32*)pSym;

													char name[258];
													strncpy(name, (char*)&pUdt->name[1], (uint8)pUdt->name[0]);
													name[(uint8)pUdt->name[0]] = 0;

													printf("udt:\t%s - typind: %d\n", name, pUdt->typind);
												}
												break;

											case S_CONSTANT_32:
												{
													CONSTSYM32* pConstSym = (CONSTSYM32*)pSym;

													char name[258];
													strncpy(name, (char*)&pConstSym->name[1], (uint8)pConstSym->name[0]);
													name[(uint8)pConstSym->name[0]] = 0;

													printf("constant:\t%s - typind: %d, value: %d \n", name, pConstSym->typind, pConstSym->value);
												}
												break;

											case S_PUB_32:
												{
													DATASYM_32* pPubSym = (DATASYM_32*)pSym;

													char name[258];
													strncpy(name, (char*)&pPubSym->name[1], (uint8)pPubSym->name[0]);
													name[(uint8)pPubSym->name[0]] = 0;

													printf("pub32:\t%s - off: %X, seg: %d, typind: %d\n", name, pPubSym->off, pPubSym->seg, pPubSym->typind);
												}
												break;
												/*

											case S_REGISTER:
												{
													REGSYM* pRegSym = (REGSYM*)pSym;

													char name[258];
													strncpy(name, (char*)&pRegSym->name[1], pRegSym->name[0]);
													name[pRegSym->name[0]] = 0;

													printf("reg:\t%s - %d - %d\n", name, pRegSym->reg, pRegSym->typind);
												}
												break;

											case S_UDT:
												{
													ASSERT(0);
												}
												break;

											case S_OBJNAME:
												{
													OBJNAMESYM* pOSym = (OBJNAMESYM*)pSym;

													char name[258];
													strncpy(name, (char*)&pOSym->name[1], pOSym->name[0]);
													name[pOSym->name[0]] = 0;

													printf("S_OBJNAME\n");
												}
												break;
*/

											case S_ALIGN:
												{
												//	printf("S_ALIGN\n");
												}
												break;

											default:
												{
													printf("rectyp: %x\n", pSym->rectyp);
												//	PUBSYM32* pPubSym = (PUBSYM32*)p;
												}
												break;
											}

											pSym = NextSym(pSym);
										}

									//	S_PUB32 pub;

									//	ATLTRACE("");
									printf("\n");
									}
									break;

								case sstGlobalTypes:
									{
										printf("%s %d - ", str, direntry->iMod);

										OMFGlobalTypes* pGlobalTypes = (OMFGlobalTypes*)(p+direntry->lfo);

										printf("sig: %d, unused: %d\n", pGlobalTypes->flags.sig, pGlobalTypes->flags.unused);

										char* p = ((char*)pGlobalTypes) + 8 + pGlobalTypes->cTypes*4;
										for (int i = 0; i < pGlobalTypes->cTypes; i++)
										{
											TYPTYPE* typ = (TYPTYPE*)(p + pGlobalTypes->typeOffset[i]);
										//	ATLTRACE("%X, %d\n", typ->leaf, typ->len);

										//	lfEasy* typ = (lfEasy*)(p + pGlobalTypes->typeOffset[i]);
											int index = typ->leaf;
											
											ASSERT(index < LF_NUMERIC);

											char* p2 = p + pGlobalTypes->typeOffset[i]+2;

											printf("%d(len:%d):", i, typ->len);

											if (index > 0x1000)
												index -= 0x1000;
											ASSERT(index > 0);
											switch (index)
											{
											case LF_LIST:
												{
													printf("list");
													lfList* lf = (lfList*)p2;

													p2 = (char*)(lf+1);

													if (i == 5)
													{
														for (int i = 0; i < 3; i++)
														{
															lfEnumerate* lfenum = (lfEnumerate*)p2;
															ASSERT(lfenum->leaf == LF_ENUMERATE);

															p2 += 4;
															short value = *(short*)p2; p2 += 2;
															uint8 namelen = *p2++;
															char buf[256];
															strncpy(buf, p2, namelen);
															buf[namelen] = 0;
															p2 += namelen;
															// dword align
															p2 += (((7+namelen)+3)&~3) - (7+namelen);

															printf("%s = %d\n", buf, value);
														}
														
													}
												}
												break;

											case LF_FIELDLIST:
												{
													printf("leaflist");
												}
												break;

											case LF_PROCEDURE:
												{
													lfProc* lf = (lfProc*)p2;
													printf("return_type: %d\n", lf->rvtype);
													printf("calltype: %d\n", lf->calltype);
													printf("params: %d\n", lf->parmcount);
													printf("arglist: %d\n", lf->arglist);
												}
												break;

											case LF_MFUNCTION:
												{
													lfMFunc* lf = (lfMFunc*)p2;
													TYPTYPE* typ2 = (TYPTYPE*)(p + pGlobalTypes->typeOffset[lf->arglist]);
													printf("member_function (return: %d)", lf->rvtype);
												}
												break;

											case LF_ENUM:
												{
													lfEnum_32* lf = (lfEnum_32*)p2;
													
													char name[258];
													strncpy(name, (char*)&lf->Name[1], (uint8)lf->Name[0]);
													name[(uint8)lf->Name[0]] = 0;
													
													printf("enum %s field: %x", name, lf->field);
												}
												break;

											case LF_ARRAY:
												{
													printf("[]");
												}
												break;

											case LF_DIMCONU:
												{
													lfDimCon* lf = (lfDimCon*)p2;

													printf("[%d]", lf->rank);
												}
												break;

											case LF_BITFIELD:
												{
													lfBitfield* lf = (lfBitfield*)p2;

													printf(": %d", lf->length);
												}
												break;

											case LF_MODIFIER:
												{
													lfModifier_32* lf = (lfModifier_32*)p2;

													if (lf->attr.MOD_const)
														printf(" const");

													if (lf->attr.MOD_volatile)
														printf(" volatile");
												}
												break;

											case LF_POINTER:
												{
													printf("*");
												}
												break;

											case LF_UNION:
												{
													printf("union\n");
												}
												break;

											case LF_CLASS:
											case LF_STRUCTURE:
												{
													lfClass_32* lf = (lfClass_32*)p2;

													char name[258];
													strncpy(name, (char*)&lf->name[1], (uint8)lf->name[0]);
													name[(uint8)lf->name[0]] = 0;

													if (index == LF_CLASS)
														printf("class");
													else
														printf("struct");

													printf(" %s {%d} sizeof(%d)", name, lf->count, lf->structlen);
												}
												break;
											
											case LF_ARGLIST:
												{
													printf("arglist");
												}
												break;

											default:
												{
													printf("typ_leaf: 0x%x", typ->leaf);
												}
											}
											printf("\n");
										}

									//	TYPTYPE* typ = (TYPTYPE*)p;

									//	printf(p);
									printf("\n");
									}
									break;

								case sstModule:
									{
										printf("%s %d - ", str, direntry->iMod);

										OMFModule* pModule = (OMFModule*)(p+direntry->lfo);

										printf("ovlNumber: %d, ", pModule->ovlNumber);
										printf("iLib: %d, ", pModule->iLib);
										printf("cSeg: %d, ", pModule->cSeg);
										printf("Style: %c%c, ", pModule->Style[0], pModule->Style[1]);

										uint8* p2 = (uint8*)pModule + offsetof(OMFModule, SegInfo);
										for (int i = 0; i < pModule->cSeg; i++)
										{
											p2 += sizeof(OMFSegDesc);
										}

										char name[258];
										strncpy(name, (char*)&p2[1], p2[0]);
										name[(uint8)p2[0]] = 0;

										printf("%s\n", name);
									}
									break;

								case sstSrcModule:
									{
										printf("%s %d - ", str, direntry->iMod);

										OMFSourceModule* pSourceModule = (OMFSourceModule*)(p+direntry->lfo);
										{
											printf("\n");
											uint8* p = (uint8*)pSourceModule + 4 + pSourceModule->cFile*4;
											for (int i = 0; i < pSourceModule->cSeg; i++)
											{
												uint32 start = *(uint32*)p; p += 4;
												uint32 end = *(uint32*)p; p += 4;

												printf("start/end: %x - %x\n", start, end);
											}
											for (i = 0; i < pSourceModule->cSeg; i++)
											{
												uint16 seg = *(uint16*)p; p += 2;
												printf("seg: %d\n", seg);
											}
										}
										for (int i = 0; i < pSourceModule->cFile; i++)
										{
										//	printf("%d\n", pSourceModule->baseSrcFile[i]);
											OMFSourceFile* pSourceFile = (OMFSourceFile*)((char*)pSourceModule + pSourceModule->baseSrcFile[i]);
											char* p = ((char*)pSourceFile) + 4;
											for (int j = 0; j < pSourceFile->cSeg; j++)
											{
												OMFSourceLine* pSourceLine = (OMFSourceLine*)((char*)pSourceModule + pSourceFile->baseSrcLn[j]);

												printf("Seg: %d\n", pSourceLine->Seg);

												p += 4;

												DWORD *offset = (DWORD*)((char*)pSourceLine + 4);
												for (int k = 0; k < pSourceLine->cLnOff; k++)
												{
													printf("offset: %d\n", offset[k]);
												}
												uint16* lineNbr = (uint16*)((char*)pSourceLine + 4 + pSourceLine->cLnOff*4);
												for (k = 0; k < pSourceLine->cLnOff; k++)
												{
													printf("lineNbr: %d\n", lineNbr[k]);
												}
											}

											for (j = 0; j < pSourceFile->cSeg; j++)
											{
												uint32 start = *(uint32*)p; p += 4;
												uint32 end = *(uint32*)p; p += 4;

												printf("start/end: %x - %x\n", start, end);
											}

											/*
											for (j = 0; j < pSourceFile->cSeg; j++)
											{
												WORD segment = *(WORD*)p; p += 2;
											}
											*/
//											WORD cfName = *(WORD*)p; p += 2;
											unsigned char cfName = *(unsigned char*)p; p += 1;
										//	char* name = (char*)p;

											char name[512];
											strncpy(name, p, cfName);
											name[cfName] = 0;

											p += cfName;
											printf("filename: %s\n", name);
										}
									}
									break;

								default:
									printf("%s %d - \n", str, direntry->iMod);
								}

								direntry++;
							}

							offset = dirheader->lfoNextDir;
						}
					}

				//	delete [] data;
					printf("\n");
				}

			//	fseek(fp, pos, SEEK_SET);
			}
		}
	}

#if 0
	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_ARCHITECTURE)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].VirtualAddress)
		{
			printf("Architecture / Copyright\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_GLOBALPTR)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].VirtualAddress)
		{
			printf("GlobalPtr\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_TLS)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress)
		{
			printf("TLS\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress)
		{
			printf("Load Config\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress)
		{
			printf("Bound Import\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_IAT)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress)
		{
			printf("IAT\n");

			long pos = ftell(fp);

			DWORD fpos = RVA2FilePos(DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress);

//			printf("%d\n", 0x400000 + DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress);
			if (fpos == -1)
			{
				printf("Corrupted file");
				return -1;
			}
			fseek(fp, fpos, SEEK_SET);
			int n = 0;
			while (1)
			{
				printf("\t%6.6x", windowsHeader.ImageBase + DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress + n*4);

				DWORD dword;
				fread(&dword, 1,4, fp);
				if (dword == 0)
					break;

				if (dword & 0x80000000)
				{
					dword &= ~0x80000000;
					// ordinal
				}
				else
				{
					long pos = ftell(fp);

					fpos = RVA2FilePos(dword);

					fseek(fp, fpos, SEEK_SET);

					WORD hint;
					fread(&hint, 1, 2, fp);
					char name[512] = {0};
					fread(name, 50, 1, fp);

				//	printf("%d", dword);

					printf("\t%s\n", name);

					fseek(fp, pos, SEEK_SET);
				}

				n++;
			}

			fseek(fp, pos, SEEK_SET);
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress)
		{
			printf("Delay Import\n");
		}
	}

	if (windowsHeader.NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR)
	{
		if (DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress)
		{
			printf("CLI Header\n");

			long pos = ftell(fp);
			unsigned long fpos = RVA2FilePos(DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress);
			fseek(fp, fpos, SEEK_SET);

			CorMetadata(fp, SectionHeader);

			fseek(fp, pos, SEEK_SET);
		}
	}

	if (StringData)
	{
		delete[] StringData;
	}
#endif

	return 0;
}

/*
int ImageNTSignature(FILE* fp)
{
	WORD magic;
	fread(&magic, 2, 1, fp);
	if (magic == IMAGE_DOS_SIGNATURE)
	{
		DWORD PEOffset;
		fseek(fp, 0x3c, SEEK_SET);
		fread(&PEOffset, 4, 1, fp);

		DWORD signature;
		fseek(fp, PEOffset, SEEK_SET);
		fread(&signature, 4, 1, fp);

		if (signature == IMAGE_NT_SIGNATURE)
		{
			return ParseCOFF(fp);
		}
	}

	return -1;
}
*/

///

/*
typedef struct _ELFHeader
{
	char ident[16];
}
ELFHeader;
*/

/*
#include "doshunks.h"

// Amiga HUNK
#define ID_MASK			0x0000FFFF

struct HUNK_Header
{
	ULONG	ID;	// HUNK_HEADER signature
	ULONG	pad0;
	ULONG	num_hunks;
	ULONG	pad2;
	ULONG	pad3;
};
*/

#include "../CodeComp/m68kassem.h"

//int read_a_out(FILE* fp);
char *GetHunkStr(ULONG id);
void pass2_CODE(uint8* text, ULONG size, ObjectFileParser* ofile);//int nsymbols, nlist* Symbols);

//extern TyCodeMapFunc CodeMapFunc[];

//extern struct myargs args;

// Global variables for decoding code hunks
extern uint16	opcode;
extern ULONG	counter;
extern uint8	*stream;

//extern char	xsbuf[], *xsptr;
//extern char	msbuf[],	*msptr;

// Prototypes

//int dasm(void);
//void ReadCode_x86(DWORD base, BYTE* code, long size);

uint16 fetch_w(void);
ULONG fetch_l(void);

void pass2_CODE(uint8* text, ULONG size, ObjectFileParser* ofile/*int nsymbols, nlist* Symbols*/)
{
	ASSERT(0);
#if 0
	ULONG nsymbols;
	if (ofile)
		nsymbols = ofile->GetNumberOfSymbols();
	else
		nsymbols = 0;

	char tabs[] = "\t\t\t\t\t\t\t\t";

	int start = 0;//48;//2162;
	counter = start;//48L;	// Program counter
	stream = (BYTE *)text+counter;//hunk_ptr;
	BYTE* endstream = stream+size;

	char xsbuf[64];
	char msbuf[64];

	//while (counter < size)
	while (stream < endstream)
	{
		xsptr = xsbuf;
		msptr = msbuf;

		//ObjectSymbol* symnode = NULL;//symnode = FindSymbol(counter);
		{
			for (int i = 0; i < nsymbols; i++)
			{
				ObjectSymbol* pSymbol = ofile->GetSymbol(i);

				if ((pSymbol->n_type & N_TYPE) == N_TEXT)
				{
					if (pSymbol->n_value == counter)
					{
					//	symnode = pSymbol;//&Symbols[i];
						printf("%s:\n", pSymbol->n_name);
					//	break;
					}
				}
			}
		}

	//	/*if (!args.nopc)*/ xsptr += sprintf(xsptr, "%06lX", counter);
		/*if (!args.nopc)*/ xsptr += sprintf(xsptr, "%06d", counter);

		opcode = fetch_w();								// Get the next opcode from the stream
		(CodeMapFunc[(opcode & 0xF000)>>12])();	// and decode it

		//if (args.nopc)
		if (FALSE)
		{
			/*
			if (symnode)
			{
				//;printf("%.*s:\n", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
				printf("%s:\n", symnode->n_name);
			}
			*/

			printf("\t%s\n", msbuf);
		}
		else
		{
			UWORD	tlen = 0-((xsptr-xsbuf)/8);
			//if (symnode) fprintf(out, "\t\t\t\t\t%.*s:\n", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
			/*
			if (symnode)
			{
				//;printf("%.*s:\n", (*symnode->SymPtr)<<2, symnode->SymPtr+1);
				printf("%s:\n", symnode->n_name);
			}
			*/

			printf("%s%.*s\t%s\n", xsbuf, tlen, tabs, msbuf);
		}
	}
#endif
}

#define ET_NONE 0	//No file type
#define ET_REL 1	//Relocatable object file
#define ET_EXEC 2	//Executable file
#define ET_DYN 3	//Shared object file
#define ET_CORE 4	//Core file
#define ET_LOOS 0xFE00	//Defines a range of object file types that is reserved for environment-specific use
#define ET_HIOS 0xFEFF
#define ET_LOPROC 0xFF00	//Defines a range of object file types that is reserved for processor-specific use
#define ET_HIPROC 0xFFFF

class CElfParser
{
public:
	char e_ident[16];

	short gethalf(FILE* fp)
	{
		short v;
		fread(&v, 2, 1, fp);

		if (e_ident[5]==1)
		{
			return v;
		}
		else
		{
			return BigEndian16(v);
		}
	}

	long getword(FILE* fp)
	{
		long v;
		fread(&v, 4, 1, fp);

		if (e_ident[5]==1)
		{
			return v;
		}
		else
		{
			return BigEndian32(v);
		}
	}
};

//namespace cpp
//{
void dasm_powerpc(uint8* text, ULONG addr, ULONG size, int nsymbols, nlist* Symbols);
//}

#include "../Include/peff.h"
#include "../CodeComp/macholoader.h"

Array<MachO::segment_command> segments;

unsigned long MachO_VM2FilePos(unsigned long vm)
{
	int i;

	for (i = 0; i < segments.GetSize(); i++)
	{
		if (segments[i].vmaddr <= vm &&
			segments[i].vmaddr + segments[i].vmsize > vm)
		{
			long offset = segments[i].fileoff + vm - segments[i].vmaddr;
			return offset;
		}
	}

	return -1;
}

//#include "macholoader.h"


void DisplayMachO(MachO::MachOLoader* macho)
{
	char* strcputype;
	switch (macho->m_header.cputype)
	{
	case MACHO_CPU_TYPE_MC680x0:	strcputype = "MC680x0"; break;
	case MACHO_CPU_TYPE_I386: strcputype = "I386"; break;
	case MACHO_CPU_TYPE_POWERPC: strcputype = "PowerPC"; break;
	default:
		strcputype = "Unknown";
	}

	printf("cputype: %s\n", strcputype);
	printf("cpusubtype: %d\n", macho->m_header.cpusubtype);

	char* strfiletype;
	switch (macho->m_header.filetype)
	{
	case MH_OBJECT:   strfiletype = "relocatable object file"; break;
	case MH_EXECUTE:  strfiletype = "executable object file"; break;
	case MH_FVMLIB:   strfiletype = "fixed vm shared library file"; break;
	case MH_CORE:		strfiletype = "core file"; break;
	case MH_PRELOAD:  strfiletype = "preloaded executable file"; break;
	default:				strfiletype = "Unknown";
	}
	printf("Filetype: %s\n", strfiletype);

	printf("header.flags:\n");
	DWORD flags = macho->m_header.flags;

	if (flags & MH_NOUNDEFS)
	{
		printf("\tMH_NOUNDEFS - object file has no undefined references\n");
		flags &= ~MH_NOUNDEFS;
	}
	
	if (flags & MH_INCRLINK)
	{
		printf("\tMH_INCRLINK - object file is the output of an incremental link against a base file\n");
		flags &= ~MH_INCRLINK;
	}
	
	if (flags & MH_DYLDLINK)
	{
		printf("\tMH_DYLDLINK - the object file is input for the dynamic linker and can't be staticly link edited again\n");
		flags &= ~MH_DYLDLINK;
	}

	if (flags & MH_BINDATLOAD)
	{
		printf("\tMH_BINDATLOAD - the object file's undefined references are bound by the dynamic linker when loaded\n");
		flags &= ~MH_BINDATLOAD;
	}

	if (flags & MH_PREBOUND)
	{
		printf("\tMH_PREBOUND - the file has it's dynamic undefined references prebound\n");
		flags &= ~MH_PREBOUND;
	}

	if (flags != 0)
	{
		printf("\tUnknown flags %d\n", flags);
	}

	printf("\n");
}

ObjectFileParser* CreateObjectFileParser(ISequentialByteStream* pStream)
{
//	fseek(fp, 0, SEEK_END);
//	long filesize = ftell(fp);
//	fseek(fp, 0, SEEK_SET);

	DWORD buf[4];
	int nread = pStream->Read(buf, 16);
	pStream->Seek(0, System::IO::STREAM_SEEK_SET);

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

		WORD classNameIndex = javaclassfile.m_pool_array[javaclassfile.m_this_class-1].classData.name_index;
		BSTR className = javaclassfile.m_pool_array[classNameIndex-1].bstr;

		printf("%S", className);

		if (javaclassfile.m_super_class)
		{
			WORD classNameIndex = javaclassfile.m_pool_array[javaclassfile.m_super_class-1].classData.name_index;
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
	else if (nread >= 4 && ENDIANLONG(((HUNK_Header*)buf)->ID) == HUNK_HEADER)
	{
		printf("AmigaDOS Hunk\n");

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
	else if (nread >= 4 && (
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
		//read_a_out(fp);
		AOutParser* pObjectFileParser = new AOutParser;

		printf("a.out\n");
	//	pObjectFileParser->Read(fp);

#if 0
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

		return pObjectFileParser;
	}
	else if (nread >= 8 && memcmp(buf, "!<arch>\n", 8) == 0)
	{
		printf("Archive (Library) Format\n");

#if 0
		CArchFile arch;
		arch.Load(fp);
#endif
#if 0
		typedef std::map<std::string,DWORD> symbolmap;

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
							std::string str;
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
	else if (nread >= 2 && *(uint16*)buf == IMAGE_DOS_SIGNATURE)
	{
		COFFParser* pImage = new COFFParser;

		return pImage;
	}
	else if (true || (nread >= 2 && (
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
		*(uint16*)buf == IMAGE_FILE_MACHINE_THUMB)))
	{
		COFFParser* pImage = new COFFParser;

		return pImage;
#if 0
		ParseCOFF(fp);
#endif
	}
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
	else if (((MachO::mach_header*)buf)->magic == BigEndian32(MH_MAGIC))
	{
		printf("Mach-O\n");

		return new MachO::MachOLoader();
//		macho(fp);
	}
	else
	{
	}

	return NULL;
}

extern "C"
{

typedef void* HMODULE;

__declspec(dllimport) HMODULE WINAPI GetModuleHandleA(
  LPCTSTR lpModuleName   // address of module name to return handle 
                         // for
);

__declspec(dllimport) HANDLE WINAPI GetStdHandle(
  DWORD nStdHandle   // input, output, or error device
);

#define STD_INPUT_HANDLE    (DWORD)-10
#define STD_OUTPUT_HANDLE   (DWORD)-11
#define STD_ERROR_HANDLE      (DWORD)-12

} 

int main(int argc, char* argv[])
{
	HMODULE h = GetModuleHandleA(NULL);

	
	h = GetStdHandle(STD_INPUT_HANDLE);
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	h = GetStdHandle(STD_ERROR_HANDLE);

	return 0;
	/*
	{
		derived* d = new derived;

		printf("x: %d\n", offsetof(derived, x));
		printf("y: %d\n", offsetof(derived, y));
		printf("z: %d\n", offsetof(derived, z));

		printf("%d\n", (long)(base*)d - (long)d);
		printf("%d\n", (long)(base2*)d - (long)d);
		printf("%d\n", (long)(derived*)d - (long)d);
		printf("\n\n");
	}
	*/

	if (argc < 2)
	{
		printf("Need one argument to a PE COFF file\n");
	}
	else
	{
	//	HANDLE hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		//FILE* fp = fopen(argv[1], "rb");
	//	if (hFile != INVALID_HANDLE_VALUE)
		try
		{
			FileByteStream file(new StringA(argv[1]));
			ObjectFileParser* pParser = CreateObjectFileParser(&file);
			if (pParser)
			{
				long nError = pParser->Read(&file);
				file.Close();

				if (COFFParser* pCOFFImage = dynamic_cast<COFFParser*>(pParser))
				{
					if (true)
					{
						FILE* fpout = fopen(argv[2], "wb");

						for (int i = 0; i < pCOFFImage->m_header->NumberOfSections; i++)
						{
						//	fseek(fpout, 0, SEEK_SET);
						//	fwrite(pCOFFImage->m_fbuf + pCOFFImage->m_SectionHeader[0].PointerToRawData, pCOFFImage->m_SectionHeader[0].SizeOfRawData, 1, fpout);

							fseek(fpout, pCOFFImage->m_SectionHeader[i].VirtualAddress - 0x1000, SEEK_SET);
							fwrite(pCOFFImage->m_fbuf + pCOFFImage->m_SectionHeader[i].PointerToRawData, pCOFFImage->m_SectionHeader[i].SizeOfRawData, 1, fpout);
						}

						fclose(fpout);
						return 0;
					}

					ParseCOFF(pCOFFImage);

					/*
					FILE* fp = fopen(argv[1], "wb");
					fwrite(pCOFFImage->m_fbuf, pCOFFImage->m_size, 1, fp);
					fclose(fp);
					*/
				}
				else if (AmigaHunkParser* pHunkParser = dynamic_cast<AmigaHunkParser*>(pParser))
				{
				//	printf("n: %d\n", n);
					printf("Number of HUNKS: %d\n", pHunkParser->header.num_hunks);
					printf("first: %d\n", pHunkParser->header.first);
					printf("last: %d\n", pHunkParser->header.last);

					uint32 size = pHunkParser->GetDataSize(0);
					uint8* code = pHunkParser->GetData(0);

					for (int i = 0; i < pHunkParser->nstabs; i++)
					{
						printf("%s\n", pHunkParser->stab[i].n_un.n_name);
					}
#if 0

					typedef std::multimap<uint32,ObjectSymbol*> symbolmap;

					symbolmap symbols;

					int numberOfSymbols = pHunkParser->GetNumberOfSymbols();
					for (int i = 0; i < numberOfSymbols; i++)
					{
						ObjectSymbol* pSymbol = pHunkParser->GetSymbol(i);

						symbols.insert(symbolmap::value_type(pSymbol->n_value, pSymbol));
					}

					m68kContext c;
					c.pc = code;
					while (c.pc < code + size)
					{
						xsptr = xsbuf;
						msptr = msbuf;

						symbolmap::iterator sit = symbols.find(c.pc - code);
						if (sit != symbols.end())
						{
							std::cout << (*sit).second->n_name << "\n";
						//	sit++;
						}

						uint8* pc = c.pc;
						m68kinstr* instr = disasm_m68k(&c);

						if (pc-c.pc == 0)
						{
							c.pc += 2;
						}

						char addr[64];
						sprintf(addr, "%6.6x", pc - code);
						std::cout << addr;
						std::cout << "\t";

						for (int k = 0; k < c.pc - pc; k++)
						{
							char c[3];
							sprintf(c, "%2.2x", *(pc + k));
							std::cout << c;
						}
						std::cout << "\t";

						if (instr)
						{
							std::cout << "\t\t";
							std::cout << instr;
						}
						std::cout << "\n";
					}

				//	for (int i = 0; i < i < pHunkParser->m_hunks.size(); i++)
				//	{
				//	}
#endif
				}
				else if (MachO::MachOLoader* pMachO = dynamic_cast<MachO::MachOLoader*>(pParser))
				{
					DisplayMachO(pMachO);
				}

				if (nError < 0)
				{
					StringA* strError = pParser->GetErrorMsg(nError);
					printf("%s\n", strError->c_str());
				}
			}
			else
			{
				printf("Unrecognized object file format\n");
			}
		}
		catch(int)
		{
			printf("Couldn't open file\n");
			return -1;
		}
	}

	return 0;
}
