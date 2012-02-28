#include "StdAfx.h"
#include "../LFC/disasm.h"
#include "../CodeComp/cpp_ast.h"
#include "../CodeComp/cpp_translate.h"
#include "../CodeComp/codegen.h"
#include "../CodeComp/link.h"

#include <time.h>

#include "../CodeComp/AOut.h"
#include "../include/coff.h"
#include "../include/doshunks.h"
#include "../Include/mach_o.h"
#include "../include/ArchFile.h"
#include "../include/FileReader.h"
#include "../include/CodeView.h"
#include "../include/Microsoft/cvinfo.h"
//#include "../include/stab.h"

#include "../LFC/debug.h"

void fput8(FILE* fp, BYTE v);
void fput16(FILE* fp, WORD v);
void fput32(FILE* fp, DWORD v);

void fw(FILE* file, short v)
{
	fwrite(&v, 1, 2, file);
}

void fl(FILE* file, long v)
{
	fwrite(&v, 1, 4, file);
}

void Write32(FILE* fp, DWORD filepointer, long value)
{
	long oldpos = ftell(fp);
	fseek(fp, filepointer, SEEK_SET);
	fwrite(&value, 1, 4, fp);
	fseek(fp, oldpos, SEEK_SET);
}

static BYTE MSDOS_Stub[128] =
{
0x4d,
 0x5a,
 0x90,
 0x00,
 0x03,
 0x00,
 0x00,
 0x00,
 
0x04,
 0x00,
 0x00,
 0x00,
 0xFF,
 0xFF,
 0x00,
 0x00,
 
0xb8,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 
0x40,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 
0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 
0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 
0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 
0x00,
 0x00,
 0x00,
 0x00,

 0x80/*128*/, 0x0, 0x0, 0x0,	//lfanew
 
0x0e,
 0x1f,
 0xba,
 0x0e,
 0x00,
 0xb4,
 0x09,
 0xcd,
 
0x21,
 0xb8,
 0x01,
 0x4c,
 0xcd,
 0x21,
 0x54,
 0x68,
 
0x69,
 0x73,
 0x20,
 0x70,
 0x72,
 0x6f,
 0x67,
 0x72,
 
0x61,
 0x6d,
 0x20,
 0x63,
 0x61,
 0x6e,
 0x6e,
 0x6f,
 
0x74,
 0x20,
 0x62,
 0x65,
 0x20,
 0x72,
 0x75,
 0x6e,
 
0x20,
 0x69,
 0x6e,
 0x20,
 0x44,
 0x4f,
 0x53,
 0x20,
 
0x6d,
 0x6f,
 0x64,
 0x65,
 0x2e,
 0x0d,
 0x0d,
 0x0a,
 
0x24,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
 0x00,
};

DWORD FilePointerToRVA(IMAGE_SECTION_HEADER* pSection, FILE* fp)
{
	long filepos = ftell(fp);
	return pSection->VirtualAddress + filepos - pSection->PointerToRawData;
}

DWORD FilePointerToRVA(IMAGE_SECTION_HEADER* pSection, long filepos)
{
	return pSection->VirtualAddress + filepos - pSection->PointerToRawData;
}

void WriteImportLookupTable(IMAGE_SECTION_HEADER* pSection, gsymmap& syms, FILE* fileout)
{
	long fpImportLookupTable = ftell(fileout);
	{
		fseek(fileout, 4*syms.size(), SEEK_CUR);	// Make room
		/*
		{
			DWORD dword = 0;	// end the lookup table
			fwrite(&dword, 1, 4, fileout);
		}
		*/

		{
			DWORD dword = 0;	// end the lookup table
			fwrite(&dword, 1, 4, fileout);
		}
	}

	int i = 0;
	gsymmap::iterator symi = syms.begin();
	while (symi != syms.end())
	{
		// Import by name
		Write32(fileout, fpImportLookupTable+i*4, FilePointerToRVA(pSection, fileout));

		WORD hint = 0;
		fwrite(&hint, 1, 2, fileout);
		char* name = (*symi).second->publicName;
		fwrite(name, strlen(name)+1, 1, fileout);

		++symi;
		i++;
	}
}

long align(FILE* fileout, long alignment)
{
	long pos = ftell(fileout);
	long pointer = (pos+alignment-1) / alignment * alignment;
	while (pos < pointer)
	{
		fputc(0, fileout);
		pos++;
	}

	return pointer;
}

class CCodeView
{
public:
	CCodeView()
	{
		dirheader = NULL;
		//ndirentries = 0;
	}

	long base;

	IMAGE_FILE_HEADER* pHeader;
	IMAGE_SECTION_HEADER** Section;

	MemDirHeader* dirheader;
//	OMFDirEntry* direntries[16];
//	int ndirentries;

	CArray<const _Type*, const _Type*> m_types;
	map<const _Type*, int> m_typesmap;

	static int GetTypeInd(const _Type* pType);

	MemDirHeader* AddDirHeader(IMAGE_FILE_HEADER* _pHeader, IMAGE_SECTION_HEADER* _Section[]);
	OMFDirEntry* AddModule(MemDirHeader* dirheader, int iMod, const char* name);
	OMFDirEntry* AddSegMap(MemDirHeader* dirheader);
	OMFDirEntry* AddGlobalSym(MemDirHeader* dirheader);
	OMFDirEntry* AddStaticSym(MemDirHeader* dirheader);
	OMFDirEntry* AddGlobalTypes(MemDirHeader* dirheader);
	OMFDirEntry* AddAlignSym(MemDirHeader* dirheader, int iMod);
	OMFDirEntry* AddSourceModule(MemDirHeader* dirheader, int iMod);
	OMFDirEntry* AddPublicSym(MemDirHeader* dirheader);
	OMFDirEntry* AddGlobalPub(MemDirHeader* dirheader);
	OMFDirEntry* AddFileIndex(MemDirHeader* dirheader);
	unsigned WritePublicSymbolSymbol32(	unsigned short seg, unsigned long offset,
											char * pszSymbol, FILE* file);

	void WriteScopeChildren(FILE* file, long startsym, ULONG pParent, Scope* pScope);

//	int MakeCodeView(IMAGE_FILE_HEADER* pHeader, IMAGE_SECTION_HEADER* Section[]);

	void WriteCodeView(FILE* file, MemDirHeader* pdirheader);
	void WriteDirHeader(FILE* file, MemDirHeader* pdirheader);
	void WriteSubSection(FILE* file, OMFDirEntry* direntry);
	void WriteModule(FILE* file, OMFModule* pModule);
	void WriteSegMap(FILE* file, OMFSegMap* segmap);
	void WriteSourceModule(FILE* file, OMFSourceModule* pSourceModule);
	void WritePublicSym(FILE* file);
	void WriteGlobalPub(FILE* file);
	void WriteGlobalSym(FILE* file);
	void WriteStaticSym(FILE* file);
	void WriteGlobalTypes(FILE* file);
	void WriteAlignSym(FILE* file);
//	void WriteSourceFile(FILE* file, OMFSourceFile* pSourceFile);
	void WriteFileIndex(FILE* fileout);
};

#define byt_toupper(b)      (b & 0xDF) 
#define dwrd_toupper(dw)    (dw & 0xDFDFDFDF)  
DWORD DWordXorLrl( char *szSym )  
/*++  Routine Description:
      This function will take an ascii character string and generate     a hash for that string.  The hash algorithm is the CV NB09 hash     algorithm.

		Arguments: 
		szSym   		- a character pointer, the first char is the string length  

		Return Value:
      The generated hash value. 
--*/  
{     
	char                *pName = szSym+1;
	int                 cb =  *szSym;
	char                *pch;
	char                c;
	DWORD               hash = 0, ulEnd = 0;
	DWORD UNALIGNED     *pul;
	// Replace all "::" with "__" for hashing purposes
	c = *(pName+cb);
	*(pName+cb) = '\0';
	pch = strstr( pName, "::" );
	if ( pch )
	{         
		*pch++ = '_';
		*pch   = '_';
	}
	*(pName+cb) = c;
	// If we're standard call, skip the trailing @999
	pch = pName + cb - 1;
	while (isdigit(*pch))
	{
		pch--;
	}
	if (*pch == '@')
	{    
		cb = pch - pName; 
	}    
	// If we're fastcall, skip the leading '@'
	if (*pName == '@')
	{
		pName++;    
		cb--;    
	}   
   // Calculate the odd byte hash.
	while (cb & 3) 
	{
		ulEnd |= byt_toupper (pName[cb-1]);
		ulEnd <<=8;     
		cb--;    
	}   
   pul = (DWORD UNALIGNED *)pName;
	// calculate the dword hash for the remaining
	while (cb) 
	{ 
		hash ^= dwrd_toupper(*pul);
		hash = _lrotl (hash, 4); 
		pul++;      
		cb -=4; 
	}    
	// or in the remainder 
	hash ^= ulEnd;  
	return hash;
}                              

MemDirHeader* CCodeView::AddDirHeader(IMAGE_FILE_HEADER* _pHeader, IMAGE_SECTION_HEADER* _Section[])
{
	pHeader = _pHeader;
	Section = _Section;

	dirheader = new MemDirHeader;
	dirheader->dirheader.cbDirHeader = sizeof(OMFDirHeader);
	dirheader->dirheader.cbDirEntry = sizeof(OMFDirEntry);
	dirheader->dirheader.cDir = 0;
	dirheader->dirheader.lfoNextDir = 0;
	dirheader->dirheader.flags = 0;
//	fseek(dbgfile, sizeof(OMFDirHeader), SEEK_CUR);	// Make room
	return dirheader;
}

OMFDirEntry* CCodeView::AddModule(MemDirHeader* dirheader, int iMod, const char* name)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstModule;
	direntry->iMod = iMod;
//	direntry[0].cb = sizeof(OMFModule) + sizeof(OMFSegDesc)*Header.NumberOfSections + sizeof(g_szModuleName);
//	direntry->lfo = ftell(dbgfile) - base;
	{
		direntry->module = new OMFModule;
		direntry->module->cSeg = pHeader->NumberOfSections;
		direntry->module->Style[0] = 'C';
		direntry->module->Style[1] = 'V';
		direntry->module->pName = strdup(name);
	//	fwrite(&module, 1, offsetof(OMFModule, SegInfo), dbgfile);
#if 0
		//
		// Initialize and write an OMFSegDesc for each executable section
		//
		for ( unsigned i = 0; i < pHeader->NumberOfSections; i++ )
		{
			OMFSegDesc omfsegdesc;

    		omfsegdesc.Seg = i+1;
    		omfsegdesc.pad = 0;
    		omfsegdesc.Off = 0;
    		omfsegdesc.cbSeg = Section[i]->Misc.VirtualSize;

			fwrite( &omfsegdesc, sizeof(omfsegdesc), 1, dbgfile);
		}

		// Subsection ends with the name of the module
		fwrite( g_szModuleName, sizeof(g_szModuleName), 1, dbgfile);
#endif
	}

	return direntry;
}

OMFDirEntry* CCodeView::AddPublicSym(MemDirHeader* dirheader)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstPublicSym;
	direntry->iMod = 0xFFFF;
//	direntry->sourceModule = new OMFSourceModule;
//	direntry->sourceModule->cFile = 1;
//	direntry->sourceModule->cSeg = 1;	// TODO

	return direntry;
}

OMFDirEntry* CCodeView::AddGlobalPub(MemDirHeader* dirheader)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstGlobalPub;
	direntry->iMod = 0xFFFF;
//	direntry->sourceModule = new OMFSourceModule;
//	direntry->sourceModule->cFile = 1;
//	direntry->sourceModule->cSeg = 1;	// TODO

	return direntry;
}

OMFDirEntry* CCodeView::AddGlobalTypes(MemDirHeader* dirheader)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstGlobalTypes;
	direntry->iMod = 0xFFFF;
//	direntry->sourceModule = new OMFSourceModule;
//	direntry->sourceModule->cFile = 1;
//	direntry->sourceModule->cSeg = 1;	// TODO

	return direntry;
}

OMFDirEntry* CCodeView::AddGlobalSym(MemDirHeader* dirheader)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstGlobalSym;
	direntry->iMod = 0xFFFF;
//	direntry->sourceModule = new OMFSourceModule;
//	direntry->sourceModule->cFile = 1;
//	direntry->sourceModule->cSeg = 1;	// TODO

	return direntry;
}

OMFDirEntry* CCodeView::AddStaticSym(MemDirHeader* dirheader)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstStaticSym;
	direntry->iMod = 0xFFFF;
//	direntry->sourceModule = new OMFSourceModule;
//	direntry->sourceModule->cFile = 1;
//	direntry->sourceModule->cSeg = 1;	// TODO

	return direntry;
}

OMFDirEntry* CCodeView::AddAlignSym(MemDirHeader* dirheader, int iMod)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstAlignSym;
	direntry->iMod = iMod;
//	direntry->sourceModule = new OMFSourceModule;
//	direntry->sourceModule->cFile = 1;
//	direntry->sourceModule->cSeg = 1;	// TODO

	return direntry;
}

OMFDirEntry* CCodeView::AddSourceModule(MemDirHeader* dirheader, int iMod)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstSrcModule;
	direntry->iMod = iMod;
	direntry->sourceModule = new OMFSourceModule;
	direntry->sourceModule->cFile = 1;
	direntry->sourceModule->cSeg = 1;	// TODO

	return direntry;
}

OMFDirEntry* CCodeView::AddFileIndex(MemDirHeader* dirheader)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstFileIndex;
	direntry->iMod = 0xFFFF;
	/*
	direntry->sourceModule = new OMFSourceModule;
	direntry->sourceModule->cFile = 1;
	direntry->sourceModule->cSeg = 1;	// TODO
	*/

	return direntry;
}

OMFDirEntry* CCodeView::AddSegMap(MemDirHeader* dirheader)
{
	OMFDirEntry* direntry = new OMFDirEntry;

	dirheader->pDirs[dirheader->dirheader.cDir] = direntry;
	dirheader->dirheader.cDir++;

	direntry->SubSection = sstSegMap;
	direntry->iMod = 0xFFFF;
	direntry->segmap = new OMFSegMap;
	direntry->segmap->cSeg = pHeader->NumberOfSections;
	direntry->segmap->cSegLog = pHeader->NumberOfSections;

	return direntry;
}

unsigned CCodeView::WritePublicSymbolSymbol32(	unsigned short seg, unsigned long offset,
											char * pszSymbol, FILE* file)
{
	BYTE buffer[512] = {0};

	PUBSYM32* pPubSym32 = (PUBSYM32*)buffer;

	DWORD cbSymbol = lstrlen( pszSymbol );
	DWORD realRecordLen = sizeof(PUBSYM32) + cbSymbol;
	realRecordLen = (realRecordLen+3) & ~3;

	pPubSym32->reclen = realRecordLen-2;//;//(unsigned short)(realRecordLen - 2);
	pPubSym32->rectyp = S_PUB32;
	pPubSym32->off = offset;
	pPubSym32->seg = seg;
	pPubSym32->typind = 0;
	pPubSym32->name[0] = (unsigned char)cbSymbol;
	lstrcpy( (PSTR)&pPubSym32->name[1], pszSymbol );
	
#if 0
	fseek( 	pFile,
			g_CVInfoOffset + g_lfoGlobalPub + g_cbPublicSymbols,
			SEEK_SET );
#endif

	fwrite( pPubSym32, realRecordLen, 1, file );
	
	return realRecordLen;
}

void CCodeView::WriteCodeView(FILE* file, MemDirHeader* pdirheader)
{
//	long endpos;
	base = ftell(file);
	fwrite("NB09", 1, 4, file);

	long offset = ftell(file) - base + 4;
	fwrite(&offset, 1, 4, file);

	WriteDirHeader(file, pdirheader);
}

void CCodeView::WriteDirHeader(FILE* file, MemDirHeader* pdirheader)
{
	fwrite(&pdirheader->dirheader, sizeof(OMFDirHeader), 1, file);

	long fp = ftell(file);
	fseek(file, pdirheader->dirheader.cDir * pdirheader->dirheader.cbDirEntry, SEEK_CUR);	// Make room

	int i;

	for (i = 0; i < pdirheader->dirheader.cDir; i++)
	{
		OMFDirEntry* direntry = pdirheader->pDirs[i];

		long fp = ftell(file);
		WriteSubSection(file, direntry);
		direntry->cb = ftell(file) - fp;
	}

	long oldpos = ftell(file);
	fseek(file, fp, SEEK_SET);
	for (i = 0; i < pdirheader->dirheader.cDir; i++)
	{
		OMFDirEntry* direntry = pdirheader->pDirs[i];
		fwrite(direntry, pdirheader->dirheader.cbDirEntry, 1, file);
	}
	fseek(file, oldpos, SEEK_SET);
}

void CCodeView::WriteSubSection(FILE* file, OMFDirEntry* direntry)
{
	long lfo = ftell(file) - base;

	switch (direntry->SubSection)
	{
	case sstModule:
		{
			WriteModule(file, direntry->module);
		}
		break;

	case sstSegMap:
		{
			WriteSegMap(file, direntry->segmap);
		}
		break;

	case sstSrcModule:
		{
			WriteSourceModule(file, direntry->sourceModule);
		}
		break;

	case sstPublicSym:
		{
			WritePublicSym(file);
		}
		break;

	case sstGlobalPub:
		{
			WriteGlobalPub(file);
		}
		break;

	case sstGlobalSym:
		{
			WriteGlobalSym(file);
		}
		break;

	case sstStaticSym:
		{
			WriteStaticSym(file);
		}
		break;

	case sstGlobalTypes:
		{
			WriteGlobalTypes(file);
		}
		break;

	case sstAlignSym:
		{
			WriteAlignSym(file);
		}
		break;

	case sstFileIndex:
		{
			WriteFileIndex(file);
		}
		break;

	default:
		ASSERT(0);
	}

	direntry->lfo = lfo;
}

void CCodeView::WritePublicSym(FILE* file)
{
	OMFSymHash omfSymHash;
	omfSymHash.symhash = 0;		// No symbol or address hash tables...
	omfSymHash.addrhash = 0;
	omfSymHash.cbHSym = 0;
	omfSymHash.cbHAddr = 0;

	fseek(file, sizeof(OMFSymHash), SEEK_CUR);	// Make room

	int fp = ftell(file);
	/*int g_cbPublicSymbols = 0;*/
	/*g_cbPublicSymbols +=*/ WritePublicSymbolSymbol32(1, 0x1000, "_main", file);
	/*g_cbPublicSymbols +=*/ WritePublicSymbolSymbol32(1, 0x0, "_mai2", file);
	/*g_cbPublicSymbols +=*/ WritePublicSymbolSymbol32(1, 0x401000, "_mai3", file);
	/*g_cbPublicSymbols +=*/ WritePublicSymbolSymbol32(1, 0x400000, "_mai4", file);

	long fp2 = ftell(file);
	omfSymHash.cbSymbol = fp2 - fp;

	fseek(file, fp-sizeof(OMFSymHash), SEEK_SET);
	fwrite(&omfSymHash, sizeof(OMFSymHash), 1, file);

	fseek(file, fp2, SEEK_SET);
}

void CCodeView::WriteGlobalSym(FILE* file)
{
	if (1)
						{
							FILE* f = fopen("C:/sstGlobalSym", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, file);

							return;
						}
}

void CCodeView::WriteStaticSym(FILE* file)
{
	if (1)
						{
							FILE* f = fopen("C:/sstStaticSym", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, file);

							return;
						}
}

// TODO

DebugInfo* pDebugInfo;

class TypType
{
public:
	ULONG fpos;
};

void descend(TypType* typ, FILE* file)
{
	typ->fpos = ftell(file);
	fseek(file, 2, SEEK_CUR);
}

uint16 ascend(TypType typ, FILE* file)
{
	long fpos = ftell(file);
	uint16 len = fpos - typ.fpos;
	uint16 typlen = (len+3) & ~3;	// align on dword
	while (len < typlen)
	{
		fputc(0, file);
		len++;
	}
	fpos = typ.fpos + typlen;

	fseek(file, typ.fpos, SEEK_SET);
	typlen -= 2;
	fwrite(&typlen, 1, 2, file);

	fseek(file, fpos, SEEK_SET);

	return typlen;
}

int CCodeView::GetTypeInd(const _Type* pType)
{
	pType = pType->Normalized();

	switch (pType->m_type)
	{
	case type_pointer:
		{
			int typind = GetTypeInd(pType->GetPointerTo());
			if (typind)
			{
				return typind | 0x400;
			}
		}
		break;
		
	case type_void:
		return T_VOID;
		
	case type_bool:
		return T_BOOL08;
		
	case type_char:
		//	return T_RCHAR;	// treat it as really a char instead of a byte
		return T_CHAR;
		
	case type_signed_char:
		return T_CHAR;
		
	case type_unsigned_char:
		return T_UCHAR;
		
	case type_wchar:
		return T_WCHAR;
		
	case type_int:
		return T_INT4;
		
	case type_unsigned_int:
		return T_UINT4;
		
	case type_short_int:
		return T_INT2;
		
	case type_unsigned_short_int:
		return T_UINT2;
		
	case type_long_int:
		return T_LONG;
		
	case type_unsigned_long_int:
		return T_ULONG;
		
	case type_long_long:
		return T_QUAD;
		
	case type_unsigned_long_long:
		return T_UQUAD;
		
	case type_float:
		return T_REAL32;
		
	case type_double:
		return T_REAL64;
	}
	
	return 0;
}

void CCodeView::WriteGlobalTypes(FILE* file)
{
	if (0)
						{
							FILE* f = fopen("C:/sstGlobalTypes", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, file);

							return;
						}

	OMFGlobalTypes gi;
	gi.flags.sig = 2;
	gi.flags.unused = 0;
	gi.cTypes = m_types.size();

	fwrite(&gi, 1, 8, file);

	uint32* typeOffset = new uint32[m_types.size()];
	long fpos = ftell(file);

	fseek(file, 4*gi.cTypes, SEEK_CUR);	// Make room

	long offsetStart = ftell(file);

	for (int i = 0; i < m_types.size(); i++)
	{
		const _Type* pType = m_types[i];

		TypType start;
		descend(&start, file);
		typeOffset[i] = start.fpos - offsetStart;

		switch (pType->m_type)
		{
			/*
		case cpp::type_void:
		case cpp::type_char:
		case cpp::type_signed_char:
		case cpp::type_unsigned_char:
		case cpp::type_int:
		case cpp::type_short_int:
		case cpp::type_long_int:
		case cpp::type_signed_int:
		case cpp::type_signed_short_int:
		case cpp::type_signed_long_int:
		case cpp::type_unsigned_int:
		case cpp::type_unsigned_short_int:
		case cpp::type_signed_long_int:
			break;
			*/

			case type_function:
			{
				lfProc typ;
				typ.leaf = LF_PROCEDURE;
				typ.rvtype = T_INT4;
				typ.calltype = CV_CALL_NEAR_C;
				typ.reserved = 0;
				typ.parmcount = 0;
				typ.arglist = 0;
				fwrite(&typ, 1, sizeof(typ), file);
			}
			break;

			case type_class:
			{
				if (pType->GetClass()->m_kwType == A_CLASSKEY_UNION)
				{
					// TODO
					ASSERT(0);
				}
				else
				{
					lfClass_32 typ;

					if (pType->GetClass()->m_kwType == A_CLASSKEY_CLASS)
						typ.leaf = LF_CLASS;
					else
						typ.leaf = LF_STRUCTURE;

					typ.count = 0;
					typ.field = 0;
					typ.property.packed = 0;
					typ.property.ctor = 0;
					typ.property.ovlops = 0;
					typ.property.isnested = 0;
					typ.property.cnested = 0;
					typ.property.opassign = 0;
					typ.property.opcast = 0;
					typ.property.fwdref = 0;
					typ.property.scoped = 0;
					typ.property.reserved = 0;
					typ.derived = 0;
					typ.vshape = 0;
					typ.structlen = pType->get_sizeof();

					typ.name[0] = pType->GetClass()->m_name.length();
					fwrite(&typ, 1, sizeof(typ), file);
					fwrite(pType->GetClass()->m_name.c_str(), 1, pType->GetClass()->m_name.length(), file);
				}
			}
			break;

			case type_enum:
			{
				lfEnum_32 typ;
				typ.leaf = LF_ENUM;
				typ.count = 0;
				typ.utype = T_INT4;
				typ.field = 0;

				typ.property.packed = 0;
				typ.property.ctor = 0;
				typ.property.ovlops = 0;
				typ.property.isnested = 0;
				typ.property.cnested = 0;
				typ.property.opassign = 0;
				typ.property.opcast = 0;
				typ.property.fwdref = 0;
				typ.property.scoped = 0;
				typ.property.reserved = 0;

				typ.Name[0] = ((EnumType*)pType)->m_name.Length();
				fwrite(&typ, 1, sizeof(typ), file);
				fwrite(((EnumType*)pType)->m_name.c_str(), 1, ((EnumType*)pType)->m_name.Length(), file);
			}
			break;

		default:
			ASSERT(0);
		}

		ascend(start, file);
	}

	fpos = ftell(file);
	fseek(file, fpos, SEEK_SET);
	fwrite(typeOffset, 1, 4*gi.cTypes, file);
	fseek(file, fpos, SEEK_SET);

	delete [] typeOffset;
}

void CCodeView::WriteModule(FILE* file, OMFModule* pModule)
{
	if (0)
						{
							FILE* f = fopen("C:/sstModule1", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, file);

							return;
						}

	fwrite(pModule, offsetof(OMFModule, SegInfo), 1, file);
	//
	// Initialize and write an OMFSegDesc for each executable section
	//
	for ( unsigned i = 0; i < 1/*pHeader->NumberOfSections*/; i++ )
	{
		OMFSegDesc omfsegdesc;

    	omfsegdesc.Seg = i+1;
    	omfsegdesc.pad = 0;
    	omfsegdesc.Off = 0;
    	omfsegdesc.cbSeg = Section[i]->Misc.VirtualSize;

		fwrite( &omfsegdesc, sizeof(omfsegdesc), 1, file);
	}

	// Subsection ends with the name of the module
	int len = 1 + strlen(pModule->pName);
	int paddedlen = (len+3) & ~3;
	fputc(len, file);
	fwrite(pModule->pName, len, 1, file);
	BYTE pad[3] = {0};
	fwrite(pad, paddedlen-len, 1, file);
}

void CCodeView::WriteSegMap(FILE* file, OMFSegMap* pSegMap)
{
	if (0)
						{
							FILE* f = fopen("C:/sstSegMap", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, file);

							return;
						}

	fwrite(pSegMap, sizeof(OMFSegMap)/* + pSegMap->cSeg*sizeof(OMFSegMapDesc)*/, 1, file);
	//
	// Initialize and write an OMFSegMapDesc for each executable section
	//
	for (int i = 0; i < pHeader->NumberOfSections; i++ )
	{
		OMFSegMapDesc omfSegMapDesc;

    	//omfSegMapDesc.flags = 0;
		omfSegMapDesc.f.fRead        = (USHORT) (Section[i]->Characteristics & IMAGE_SCN_MEM_READ) ==    IMAGE_SCN_MEM_READ;
		omfSegMapDesc.f.fWrite       = (USHORT) (Section[i]->Characteristics & IMAGE_SCN_MEM_WRITE) ==   IMAGE_SCN_MEM_WRITE;
		omfSegMapDesc.f.fExecute     = (USHORT) (Section[i]->Characteristics & IMAGE_SCN_MEM_EXECUTE) == IMAGE_SCN_MEM_EXECUTE;
		omfSegMapDesc.f.f32Bit       = 1;
		omfSegMapDesc.f.fAbs         = 0;
		omfSegMapDesc.f.fSel         = 1;
		omfSegMapDesc.f.fGroup       = 0;

    	omfSegMapDesc.ovl = 0;
    	omfSegMapDesc.group = 0;
    	omfSegMapDesc.frame = i+1;
    	omfSegMapDesc.iSegName = 0xFFFF;
    	omfSegMapDesc.iClassName = 0xFFFF;
    	omfSegMapDesc.offset = 0;
    	omfSegMapDesc.cbSeg = Section[i]->Misc.VirtualSize;
		
		fwrite(&omfSegMapDesc, sizeof(OMFSegMapDesc), 1, file);
	}

		OMFSegMapDesc omfSegMapDesc;

    	//omfSegMapDesc.flags = 0;
		omfSegMapDesc.f.fRead        = 0;//(USHORT) (Section[i]->Characteristics & IMAGE_SCN_MEM_READ) ==    IMAGE_SCN_MEM_READ;
		omfSegMapDesc.f.fWrite       = 0;//(USHORT) (Section[i]->Characteristics & IMAGE_SCN_MEM_WRITE) ==   IMAGE_SCN_MEM_WRITE;
		omfSegMapDesc.f.fExecute     = 0;//(USHORT) (Section[i]->Characteristics & IMAGE_SCN_MEM_EXECUTE) == IMAGE_SCN_MEM_EXECUTE;
		omfSegMapDesc.f.f32Bit       = 1;
		omfSegMapDesc.f.fAbs         = 1;
		omfSegMapDesc.f.fSel         = 0;
		omfSegMapDesc.f.fGroup       = 0;

    	omfSegMapDesc.ovl = 0;
    	omfSegMapDesc.group = 0;
    	omfSegMapDesc.frame = 0;
    	omfSegMapDesc.iSegName = 0xFFFF;
    	omfSegMapDesc.iClassName = 0xFFFF;
    	omfSegMapDesc.offset = 0;
    	omfSegMapDesc.cbSeg = 0xffffffff;//Section[i]->Misc.VirtualSize;
		
		fwrite(&omfSegMapDesc, sizeof(OMFSegMapDesc), 1, file);
}

void CCodeView::WriteFileIndex(FILE* fileout)
{
	if (0)
						{
							FILE* f = fopen("C:/sstFileIndex", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, fileout);

							return;
						}

	OMFFileIndex fileindex;
	fileindex.cMod = 1;
	fileindex.cRef = 1;

	uint16 ModStart[1] = {0};
	uint16 cRefCnt[1] = {1};
	uint32 NameRef[1] = {0};

	char* filename = "C:\\test.cpp";

//	char* Names[] = (NameRef + fileindex->cRef);

	fwrite(&fileindex, 1, 4, fileout);
	fwrite(ModStart, 1, fileindex.cMod*2, fileout);
	fwrite(cRefCnt, 1, fileindex.cMod*2, fileout);
	fwrite(NameRef, 1, fileindex.cRef*4, fileout);
	fputc(strlen(filename), fileout);
	fwrite(filename, 1, strlen(filename), fileout);

}

ULONG descend(SYMTYPE* symtyp, FILE* file)
{
	symtyp->reclen = 0;

	ULONG start = ftell(file);
//	fseek(file, 4, SEEK_CUR);
	return start;
}

void ascend(ULONG start, SYMTYPE* symtyp, FILE* file)
{
	long fpos = ftell(file);
	int len = fpos - start;
	symtyp->reclen = (len+3) & ~3;	// align on dword
	while (len < symtyp->reclen)
	{
		fputc(0, file);
		len++;
	}
	fpos = start + symtyp->reclen;

	fseek(file, start, SEEK_SET);
	symtyp->reclen -= 2;
	fwrite(&symtyp->reclen, 1, 2, file);

	fseek(file, fpos, SEEK_SET);
}

void CCodeView::WriteGlobalPub(FILE* file)
{
	if (1)
						{
							FILE* f = fopen("C:/sstGlobalPub", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, file);

							return;
						}
}

void CCodeView::WriteScopeChildren(FILE* file, long startsym, ULONG pParent, Scope* pScope)
{
	for (int i = 0; i < pScope->m_subScopes.size(); i++)
	{
		Scope* pScope2 = pScope->m_subScopes[i];

		if (pScope2->m_pType && pScope2->m_pType->m_type == type_function)
		{
			int n = pScope2->m_subScopes.size();
			ASSERT(n == 1);

			_Type* pType = pScope2->m_pType;

			PROCSYM_32 sym;
			ULONG start = descend((SYMTYPE*)&sym, file);
			{
				const char* name = pScope2->m_name.c_str();

				sym.rectyp = S_GPROC_32;
				sym.pParent = pParent;
				sym.pEnd = 0;	// Update later
				sym.pNext = 0;
				sym.seg = 1;
				sym.off = pScope2->m_startAddress;
				sym.len = pScope2->m_endAddress - pScope2->m_startAddress;
				sym.DbgStart = 0;	// TODO
				sym.DbgEnd = sym.len;	// TODO
//				sym.typind = 0x1000 + 0;
				sym.flags.bAll = 1;
				sym.namelen = strlen(name);

				int typind = GetTypeInd(pType);
				if (typind)
				{
					sym.typind = typind;
				}
				else
				{
					typind = m_typesmap[pType];

					if (typind == 0)
					{
						m_types.Add(pType);
						typind = m_types.size();
						m_typesmap[pType] = typind;
					}

					sym.typind = typind | 0x1000;
				}

				fwrite(&sym, 1, sizeof(PROCSYM_32), file);
				fwrite(name, 1, sym.namelen, file);

				ascend(start, (SYMTYPE*)&sym, file);
			}

			declsmap::iterator it = pScope2->m_decls.begin();
			while (it != pScope2->m_decls.end())
			{
				CDeclarator* pdecl = (*it).second->m_pDeclarator;
				ASSERT(0);	// TODO
			}

			WriteScopeChildren(file, startsym, start-startsym/*pParent*/, pScope2);

			{
				SYMTYPE endsym;
				endsym.rectyp = S_END;
				ULONG start = descend((SYMTYPE*)&endsym, file);
				sym.pEnd = start - startsym;
				fwrite(&endsym, 1, sizeof(SYMTYPE), file);
				ascend(start, (SYMTYPE*)&endsym, file);
			}

			// Update pEnd field
			Write32(file, start+offsetof(PROCSYM_32, pEnd), sym.pEnd);
		}
		else	// Normal block
		{
			BLOCKSYM32 sym;
			ULONG start = descend((SYMTYPE*)&sym, file);
			{
				sym.rectyp = S_BLOCK32;
				sym.pParent = pParent;
				sym.pEnd = 0;	// Update later
				sym.off = pScope2->m_startAddress;
				sym.len = pScope2->m_endAddress - pScope2->m_startAddress;
				sym.seg = 1;
				sym.name[0] = 0;	// 0-length name
				fwrite(&sym, 1, sizeof(BLOCKSYM32), file);

				ascend(start, (SYMTYPE*)&sym, file);
			}

			declsmap::const_iterator it = pScope2->m_decls.begin();

			int size = pScope2->GetDeclarationCount();
			CDeclarator** pdecls = new CDeclarator*[size];
			pScope2->GetDeclarations(pdecls);

			for (int i = 0; i < size; i++)
			{
				const CDeclarator* pdecl = pdecls[i];

				const _Type* pType = pdecl->m_pType->Normalized();

				BPRELSYM_32 sym;
				sym.rectyp = S_BPREL_32;
				ULONG start = descend((SYMTYPE*)&sym, file);

				int typind = GetTypeInd(pType);
				if (typind)
				{
					sym.typind = typind;
				}
				else
				{
					typind = m_typesmap[pType];

					if (typind == 0)
					{
						m_types.Add(pType);
						typind = m_types.size();
						m_typesmap[pType] = typind;
					}

					sym.typind = typind | 0x1000;
				}

				sym.off = pdecl->m_offset;
				sym.namelen = pdecl->m_name.length();
				
				fwrite(&sym, 1, sizeof(sym), file);
				fwrite(pdecl->m_name.c_str(), 1, pdecl->m_name.length(), file);

				ascend(start, (SYMTYPE*)&sym, file);
			}
			delete [] pdecls;

			WriteScopeChildren(file, startsym, start-startsym/*pParent*/, pScope2);

			{
				SYMTYPE endsym;
				endsym.rectyp = S_END;
				ULONG start = descend((SYMTYPE*)&endsym, file);
				sym.pEnd = start - startsym;
				fwrite(&endsym, 1, sizeof(SYMTYPE), file);
				ascend(start, (SYMTYPE*)&endsym, file);
			}

			// Update pEnd field
			Write32(file, start+offsetof(BLOCKSYM32, pEnd), sym.pEnd);
		}
	}
}

void CCodeView::WriteAlignSym(FILE* file)
{
	if (0)
						{
							FILE* f = fopen("C:/sstAlignSym1", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, file);

							return;
						}

	long startsym = ftell(file);

	// Empty record ??
	fw(file, 2);
	fw(file, 0);

	Scope* pScope = pDebugInfo->GetScope();

	WriteScopeChildren(file, startsym, 0/*pParent*/, pScope);
}

void CCodeView::WriteSourceModule(FILE* fileout, OMFSourceModule* pSourceModule)
{
	if (0)
						{
							FILE* f = fopen("C:/sstSrcModule1", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, fileout);

							return;
						}

	long direntryfpos = ftell(fileout);

	OMFSourceModule srcModule;
	long baseSrcFile[1];

	srcModule.cFile = 1;
	srcModule.cSeg = 1;
	baseSrcFile[0] = 4 + srcModule.cFile*4 + srcModule.cSeg*8 + srcModule.cSeg*2 + 2;

	fwrite(&srcModule, 1, 4, fileout);
	fwrite(baseSrcFile, 1, srcModule.cFile*4, fileout);

	// Write the start/end pairs
	for (int i = 0; i < pSourceModule->cSeg; i++)
	{
		fl(fileout, 0);	// start
		fl(fileout, 91);	// end
	}

	// Write the segment numbers
	for (i = 0; i < pSourceModule->cSeg; i++)
	{
		fw(fileout, 1);	// nseg
	}

	fw(fileout, 0);	// pad to dword

	SourceFile* pSourceFile = pDebugInfo->m_sourceFiles[0];

	for (int nfile = 0; nfile < 1; nfile++)
	{
		OMFSourceFile srcFile;

		srcFile.cSeg = pSourceFile->GetSegmentCount();
		srcFile.reserved = 0;
		fwrite(&srcFile, 1, 4, fileout);

		long fpos = ftell(fileout);
		fseek(fileout, srcFile.cSeg*4, SEEK_CUR);	// Make room for srcLines array

		for (int nseg = 0; nseg < srcFile.cSeg; nseg++)
		{
			ULONG startAddress;
			ULONG endAddress;

			pSourceFile->GetSegmentAddress(nseg, &startAddress, &endAddress);

			/*
			SourceFile::Segment seg = pSourceFile->m_segments[nseg];
			*/

			fwrite(&startAddress, 1, 4, fileout);
			fwrite(&endAddress, 1, 4, fileout);
		}

		// Filename
		uint8 name[256];
		name[0] = pSourceFile->m_filename.length();
		strcpy((char*)name+1, pSourceFile->m_filename.c_str());
		fwrite(name, 1, name[0]+1, fileout);

		// src lines
		srcFile.baseSrcLn[0] = ftell(fileout) - direntryfpos;
		for (nseg = 0; nseg < srcFile.cSeg; nseg++)
		{
			OMFSourceLine lines;
			lines.Seg = 1;
			lines.cLnOff = pSourceFile->m_lines.GetSize();
			fwrite(&lines, 1, 4, fileout);

			for (int i = 0; i < lines.cLnOff; i++)
			{
				fwrite(&pSourceFile->m_lines[i].m_address, 1, 4, fileout);
			}

			for (i = 0; i < lines.cLnOff; i++)
			{
				uint16 line = pSourceFile->m_lines[i].m_line + 1;
				fwrite(&line, 1, 2, fileout);
			}
		}

		// Update srclines array
		long fpos2 = ftell(fileout);
		fseek(fileout, fpos, SEEK_SET);
		fwrite(srcFile.baseSrcLn, 1, 4*srcFile.cSeg, fileout);

		fseek(fileout, fpos2, SEEK_SET);
	}

#if 0
	long sourceModuleBase = ftell(file);
//	fwrite(pSourceModule, offsetof(OMFSourceModule, baseSrcFile), 1, file);
	fseek(file, offsetof(OMFSourceModule, baseSrcFile), SEEK_CUR);	// Make room

	/*
	for (int i = 0; i < pSourceModule->cFile; i++)
	{
		long value = 0;	// relative to us ?
		fwrite(&value, 1, 4, file);
	}
	*/
	fseek(file, pSourceModule->cFile*4, SEEK_CUR);	// Make room

	int i;

	// Write the start/end pairs
	for (i = 0; i < pSourceModule->cSeg; i++)
	{
		fw(file, 0);	// start
		fw(file, 0);	// end
	}

	// Write the segment numbers
	for (i = 0; i < pSourceModule->cSeg; i++)
	{
		fw(file, 0);	// nseg
	}

	// align to dword
	fw(file, 0);

	char* filename = "C:\\test.cpp";

	// Write OMFSourceFile
	{
		pSourceModule->baseSrcFile[0] = ftell(file) - sourceModuleBase;

		long sourceFileBase = ftell(file);
		OMFSourceFile sourceFile = {0};
		sourceFile.cSeg = 1;
		sourceFile.cFName = strlen(filename);

		fwrite(&sourceFile, offsetof(OMFSourceFile, baseSrcLn), 1, file);

		fseek(file, sourceFile.cSeg*4, SEEK_CUR);	// Make room for baseSrcLn

	// Write the start/end pairs
		for (i = 0; i < sourceFile.cSeg; i++)
		{
			fw(file, 0);	// start
			fw(file, 0);	// end
		}

		// Write the segment numbers
		for (i = 0; i < sourceFile.cSeg; i++)
		{
			fw(file, 0);	// nseg
		}
	#if 0
		//
		SrcLine = (OMFSourceLine*) lpb;
		SrcLine->Seg = (USHORT)si[i].seg[k].num;
		SrcLine->cLnOff = (USHORT) si[i].seg[k].cbLines;
		pilSave = pil;
		lpdw = (LPDWORD) (lpb + 4);
		for (j=0; j<SrcLine->cLnOff; j++)
		{     
			*lpdw++ = 0x1000/*pil->Type.VirtualAddress*/ - si[i].seg[k].va;
			pil++;            
		}            

		lps = (PUSHORT) lpdw;
		pil = pilSave;
		for (j=0; j<SrcLine->cLnOff; j++)
		{
			*lps++ = pil->Linenumber;
			pil++;
		}
	#endif

		fw(file, sourceFile.cFName);
		fwrite(filename, sourceFile.cFName, 1, file);

		long baseSrcLn[1];

		//  write the line numbers 
		for (int i = 0; i < sourceFile.cSeg; i++)
		{
			baseSrcLn[i] = ftell(file) - sourceModuleBase;
			OMFSourceLine srcLine;
			srcLine.Seg = 0;
			srcLine.cLnOff = 1;
			fwrite(&srcLine, offsetof(OMFSourceLine, offset), 1, file);
			fl(file, 0);//	DWORD offset = 0;
			fw(file, 0);//WORD linenumber = 0;

			Write32(file, sourceFileBase + offsetof(OMFSourceFile, baseSrcLn)+i*4, baseSrcLn[i]);
		}
		//fseek(
	}	// OMFSourceFile

	long oldpos = ftell(file);

	fseek(file, sourceModuleBase, SEEK_SET);
	fwrite(pSourceModule, offsetof(OMFSourceModule, baseSrcFile)+pSourceModule->cFile*4, 1, file);

	fseek(file, oldpos, SEEK_SET);
#endif
}

#if 0
MemDirHeader*  MakeCodeView(CCodeView* codeview, IMAGE_FILE_HEADER* _pHeader, IMAGE_SECTION_HEADER* _Section[])
{

	MemDirHeader* dirheader = codeview.AddDirHeader(_pHeader, _Section);
	OMFDirEntry* moduleentry = codeview.AddModule(dirheader, "test.obj");

	return dirheader;

#if 0
	if (dbgfile)
	{

		/*
		IMAGE_DEBUG_DIRECTORY idd = {0};
		idd.TimeDateStamp = pHeader->TimeDateStamp;
		idd.Type = IMAGE_DEBUG_TYPE_CODEVIEW;//IMAGE_DEBUG_TYPE_COFF;
		idd.AddressOfRawData = 0x0;//FilePointerToRVA(pSection, fileout) + sizeof(IMAGE_DEBUG_DIRECTORY);
		idd.SizeOfData = 0;//8+sizeof(OMFDirHeader);//sizeof(IMAGE_COFF_SYMBOLS_HEADER);
		int debugDirectoryOffset = ftell(dbgfile);
		fseek(dbgfile, sizeof(IMAGE_DEBUG_DIRECTORY), SEEK_CUR);	// Make room

		idd.PointerToRawData = ftell(dbgfile);//align(dbgfile, windowsHeader.FileAlignment);
*/

		long endpos;
		base = ftell(dbgfile);
		fwrite("NB09", 1, 4, dbgfile);

		long offset = ftell(dbgfile) - base + 4;
		fwrite(&offset, 1, 4, dbgfile);

		fwrite(&dirheader, 1, sizeof(dirheader), dbgfile);

		int direntryOffset = ftell(dbgfile);
	//	OMFDirEntry* direntries[16] = {0};
		//ndirentries = 0;

		fseek(dbgfile, sizeof(OMFDirEntry)*dirheader->dirheader.cDir, SEEK_CUR);	// Make room

		{
#if 0
			OMFDirEntry* direntry = new OMFDirEntry;
			direntries[ndirentries++] = direntry;

			char g_szModuleName[] = { '9', "BobIn2020" };	// Hardcoded length!

			direntry[0].SubSection = sstModule;
			direntry[0].iMod = 1;
		//	direntry[0].cb = sizeof(OMFModule) + sizeof(OMFSegDesc)*Header.NumberOfSections + sizeof(g_szModuleName);
			direntry[0].lfo = ftell(dbgfile) - base;
			{
				OMFModule module = {0};
				module.cSeg = pHeader->NumberOfSections;
			   module.Style[0] = 'C';
			   module.Style[1] = 'V';
				fwrite(&module, 1, offsetof(OMFModule, SegInfo), dbgfile);

				//
				// Initialize and write an OMFSegDesc for each executable section
				//
				for ( unsigned i = 0; i < pHeader->NumberOfSections; i++ )
				{
					OMFSegDesc omfsegdesc;

    				omfsegdesc.Seg = i+1;
    				omfsegdesc.pad = 0;
    				omfsegdesc.Off = 0;
    				omfsegdesc.cbSeg = Section[i]->Misc.VirtualSize;

					fwrite( &omfsegdesc, sizeof(omfsegdesc), 1, dbgfile);
				}

				// Subsection ends with the name of the module
				fwrite( g_szModuleName, sizeof(g_szModuleName), 1, dbgfile);
			}
			direntry[0].cb = (ftell(dbgfile)-base) - direntry[0].lfo;
#endif
		}

#if 0
		{
			OMFDirEntry* direntry = new OMFDirEntry;
			direntries[ndirentries++] = direntry;

			direntry[1].SubSection = sstSegMap;
			direntry[1].iMod = 0xFFFF;
			//direntry[1].cb = sizeof(OMFSegMap) + sizeof(OMFSegMapDesc)*Header.NumberOfSections;
			direntry[1].lfo = ftell(dbgfile) - base;
			{
				OMFSegMap segmap;
				segmap.cSeg = pHeader->NumberOfSections;
				segmap.cSegLog = pHeader->NumberOfSections;
				fwrite(&segmap, sizeof(OMFSegMap) + segmap.cSeg*sizeof(OMFSegMapDesc), 1, dbgfile);
				//
				// Initialize and write an OMFSegMapDesc for each executable section
				//
				for ( unsigned i = 0; i < pHeader->NumberOfSections; i++ )
				{
					OMFSegMapDesc omfSegMapDesc;

    				omfSegMapDesc.flags = 0;
    				omfSegMapDesc.ovl = 0;
    				omfSegMapDesc.group = 0;
    				omfSegMapDesc.frame = i+1;
    				omfSegMapDesc.iSegName = 0xFFFF;
    				omfSegMapDesc.iClassName = 0xFFFF;
    				omfSegMapDesc.offset = 0;
    				omfSegMapDesc.cbSeg = Section[i]->Misc.VirtualSize;
					
					fwrite(&omfSegMapDesc, sizeof(OMFSegMapDesc), 1, dbgfile);
				}
				direntry[1].cb = (ftell(dbgfile)-base) - direntry[1].lfo;
			}
		}

		{
			OMFDirEntry* direntry = new OMFDirEntry;
			direntries[ndirentries++] = direntry;

			direntry[2].SubSection = sstPublicSym;
			direntry[2].iMod = 1;
			long symHashOffset = ftell(dbgfile);
			direntry[2].lfo = ftell(dbgfile) - base;
			{
				OMFSymHash omfSymHash;
				omfSymHash.symhash = 0;		// No symbol or address hash tables...
				omfSymHash.addrhash = 0;
				omfSymHash.cbHSym = 0;
				omfSymHash.cbHAddr = 0;
				fseek(dbgfile, sizeof(OMFSymHash), SEEK_CUR);	// Make room

				int g_cbPublicSymbols = 0;

				g_cbPublicSymbols += AddPublicSymbolSymbol32(1, 0x1000, "_mai", dbgfile);
//dataSym->off = Symbol->Value -                      p->iptrs.sectionHdrs[Symbol->SectionNumber-1].VirtualAddress;

				endpos = ftell(dbgfile);

			// Update omfSymHash
				long oldpos = ftell(dbgfile);
				fseek(dbgfile, symHashOffset, SEEK_SET);
				omfSymHash.cbSymbol = g_cbPublicSymbols - sizeof(OMFSymHash);
				fwrite(&omfSymHash, sizeof(OMFSymHash), 1, dbgfile);
				fseek(dbgfile, oldpos, SEEK_SET);
			}
			direntry[2].cb = (ftell(dbgfile)-base) - direntry[2].lfo;
		}
#endif

#if 0
	// Update dirheaders

		OMFDirHeader* pdirheader = dirheader;
		while (pdirheader)
		{
			long dirHeaderOffset = ftell(dbgfile);
			fseek(dbgfile, sizeof(OMFDirHeader), SEEK_CUR);	// Make room

			pdirheader = pdirheader->NextDir;

			// Update dirheader
			fseek(dbgfile, dirHeaderOffset, SEEK_SET);
			fwrite(pdirheader, sizeof(OMFDirHeader), 1, dbgfile);
		}

	// Update direntries
		fseek(dbgfile, direntryOffset, SEEK_SET);
		fwrite(direntries, sizeof(OMFDirEntry)*dirheader.cDir, 1, dbgfile);

		fseek(dbgfile, endpos, SEEK_SET);
	}
#endif
#endif

	return 0;
}
#endif

int WriteDBG(FILE* dbgfile, IMAGE_FILE_HEADER* pHeader, WindowsHeader* pWindowsHeader, IMAGE_SECTION_HEADER* Section[])
{
	IMAGE_SEPARATE_DEBUG_HEADER imageDebugHeader = {0};
	imageDebugHeader.Signature = IMAGE_SEPARATE_DEBUG_SIGNATURE;
	imageDebugHeader.Characteristics = pHeader->Characteristics;// & ~IMAGE_FILE_DEBUG_STRIPPED;
	imageDebugHeader.Machine = pHeader->Machine;
	imageDebugHeader.NumberOfSections = pHeader->NumberOfSections;
	imageDebugHeader.TimeDateStamp = pHeader->TimeDateStamp;

	imageDebugHeader.SizeOfImage = pWindowsHeader->SizeOfImage;
	imageDebugHeader.ImageBase = pWindowsHeader->ImageBase;
	imageDebugHeader.CheckSum = pWindowsHeader->CheckSum;
	imageDebugHeader.SectionAlignment = pWindowsHeader->SectionAlignment;
	imageDebugHeader.Flags = 0;
	imageDebugHeader.DebugDirectorySize = sizeof(IMAGE_DEBUG_DIRECTORY);
	imageDebugHeader.ExportedNamesSize = 0;

	fwrite(&imageDebugHeader, 1, sizeof(imageDebugHeader), dbgfile);

// Copy section headers
	{
		for (int i = 0; i < pHeader->NumberOfSections; i++)
		{
			fwrite(Section[i], 1, sizeof(IMAGE_SECTION_HEADER), dbgfile);
		}
	}

#if 0
	MakeCodeView(pHeader, Section);
#endif

	return 0;
}

int CConfiguration::COFF_Pass2(FILE* fileout)
{
	bool bDebug = true;

	// MS-DOS Header

	DWORD* pdw = (DWORD*)&MSDOS_Stub[0x3c];

	if (fwrite(MSDOS_Stub, 1, 128, fileout) != 128)
	{
		printf("Write error");
		return -1;
	}

	if (fwrite("PE\0", 1, 4, fileout) != 4)
	{
		printf("Write error");
		return -1;
	}

	DWORD headerpos = ftell(fileout);
	fseek(fileout, sizeof(IMAGE_FILE_HEADER), SEEK_CUR);	// Make room for header

	IMAGE_FILE_HEADER Header;
	ASSERT(sizeof(IMAGE_FILE_HEADER) == IMAGE_SIZEOF_FILE_HEADER);

	memset(&Header, 0, sizeof(Header));
	Header.Machine = IMAGE_FILE_MACHINE_I386;
	Header.TimeDateStamp = time(NULL);
	Header.Characteristics =	
		
		IMAGE_FILE_RELOCS_STRIPPED |

		IMAGE_FILE_EXECUTABLE_IMAGE |
										IMAGE_FILE_32BIT_MACHINE |

	IMAGE_FILE_LINE_NUMS_STRIPPED |
IMAGE_FILE_LOCAL_SYMS_STRIPPED;


	//if (bDebug) // ??
	{
#if 0
		Header.Characteristics |= IMAGE_FILE_DEBUG_STRIPPED;
#endif
	//	Header.Characteristics |= IMAGE_FILE_LINE_NUMS_STRIPPED;
	//	Header.Characteristics |= IMAGE_FILE_LOCAL_SYMS_STRIPPED;
	}

// Optional header
	DWORD optionalHeaderPos = ftell(fileout);

	OptionalStandardHeader optionalStandardHeader;
	optionalStandardHeader.Magic = 0x10b;	// PE
	optionalStandardHeader.MajorLinkerVersion = 0;//	Linker major version number.
	optionalStandardHeader.MinorLinkerVersion = 0;//	Linker minor version number.
	optionalStandardHeader.SizeOfCode = 0x1000;//	Size of the code (text) section, or the sum of all code sections if there are multiple sections.
	optionalStandardHeader.SizeOfInitializedData = 0;//0x1000;//	Size of the initialized data section, or the sum of all such sections if there are multiple data sections.
	optionalStandardHeader.SizeOfUninitializedData = 0;//	Size of the uninitialized data section (BSS), or the sum of all such sections if there are multiple BSS sections.
	optionalStandardHeader.AddressOfEntryPoint = 0x1000;//	Address of entry point, relative to image base, when executable file is loaded into memory. For program images, this is the starting address. For device drivers, this is the address of the initialization function. An entry point is optional for DLLs. When none is present this field should be 0.
	optionalStandardHeader.BaseOfCode = 0x1000;//	Address, relative to image base, of beginning of code section, when loaded into memory.

	fwrite(&optionalStandardHeader, 1, sizeof(optionalStandardHeader), fileout);

	DWORD	BaseOfData = 0;//	Address, relative to image base, of beginning of data section, when loaded into memory.
	fwrite(&BaseOfData, 1, 4, fileout);

	WindowsHeader windowsHeader;

	if (TRUE)	// EXE
		windowsHeader.ImageBase = 0x400000;
	else	// DLL
		windowsHeader.ImageBase = 0x10000000;

	windowsHeader.SectionAlignment = 0x1000;//	Alignment (in bytes) of sections when loaded into memory. Must greater or equal to File Alignment. Default is the page size for the architecture.	   
	windowsHeader.FileAlignment = 0x1000;//	Alignment factor (in bytes) used to align the raw data of sections in the image file. The value should be a power of 2 between 512 and 64K inclusive. The default is 512. If the SectionAlignment is less than the architecture’s page size than this must match the SectionAlignment.	   
	windowsHeader.MajorOperatingSystemVersion = 4;//	Major version number of required OS.	   
	windowsHeader.MinorOperatingSystemVersion = 0;//	Minor version number of required OS.	   
	windowsHeader.MajorImageVersion = 0;//	Major version number of image.	   
	windowsHeader.MinorImageVersion = 0;//	Minor version number of image.	   
	windowsHeader.MajorSubsystemVersion = 4;//	Major version number of subsystem.	   
	windowsHeader.MinorSubsystemVersion = 0;//	Minor version number of subsystem.	   
	windowsHeader.Reserved = 0;
	windowsHeader.SizeOfImage = 0x0;//	Size, in bytes, of image, including all headers; must be a multiple of Section Alignment.	   
	windowsHeader.SizeOfHeaders = 0x1000;//	Combined size of MS-DOS stub, PE Header, and section headers rounded up to a multiple of FileAlignment.	   
	windowsHeader.CheckSum = 0;//	Image file checksum. The algorithm for computing is incorporated into IMAGHELP.DLL. The following are checked for validation at load time: all drivers, any DLL loaded at boot time, and any DLL that ends up in the server.	   
	windowsHeader.Subsystem = IMAGE_SUBSYSTEM_WINDOWS_CUI;//	Subsystem required to run this image. See “Windows NT Subsystem” below for more information.	   
	windowsHeader.DLLCharacteristics = 0;//	See “DLL Characteristics” below for more information.	   
	windowsHeader.SizeOfStackReserve = 0x100000;//	Size of stack to reserve. Only the Stack Commit Size is committed; the rest is made available one page at a time, until reserve size is reached.	   
	windowsHeader.SizeOfStackCommit = 0x1000;//	Size of stack to commit.	   
	windowsHeader.SizeOfHeapReserve = 0x100000;//	Size of local heap space to reserve. Only the Heap Commit Size is committed; the rest is made available one page at a time, until reserve size is reached.	   
	windowsHeader.SizeOfHeapCommit = 0x1000;//	Size of local heap space to commit.	   
	windowsHeader.LoaderFlags = 0;//	Obsolete.	   
	windowsHeader.NumberOfRvaAndSizes = 16;//	Number of data-dictionary entries in the remainder of the Optional Header. Each describes a location and size.	 
	fwrite(&windowsHeader, 1, sizeof(windowsHeader), fileout);

	windowsHeader.SizeOfImage += windowsHeader.SizeOfHeaders;

	IMAGE_DATA_DIRECTORY DataDirectory[16];
	memset(DataDirectory, 0, 16*sizeof(IMAGE_DATA_DIRECTORY));

	fseek(fileout, windowsHeader.NumberOfRvaAndSizes*sizeof(IMAGE_DATA_DIRECTORY), SEEK_CUR);	// Make room for data directories

	Header.SizeOfOptionalHeader = ftell(fileout) - optionalHeaderPos;

	// Make room for section headers
	long PointerToSections = ftell(fileout);

	IMAGE_SECTION_HEADER* Section[16];
	Header.NumberOfSections = 0;
	fseek(fileout, sizeof(IMAGE_SECTION_HEADER)*Header.NumberOfSections, SEEK_CUR);

	// .text section
	IMAGE_SECTION_HEADER* pSectionText = new IMAGE_SECTION_HEADER;
	CArray<IMAGE_RELOCATION*, IMAGE_RELOCATION*> pRelocations;
	{
		Section[Header.NumberOfSections] = pSectionText;
		Header.NumberOfSections++;

		memset(pSectionText, 0, sizeof(IMAGE_SECTION_HEADER));
		strcpy((char*)pSectionText->Name, ".text");
		pSectionText->VirtualAddress = 0x1000;
		pSectionText->Misc.VirtualSize = 0x1000;
		pSectionText->Characteristics = IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ;//0x60000020;

		pSectionText->NumberOfRelocations = 0;
	}
	IMAGE_SECTION_HEADER* pSectionData = NULL;
	if (FALSE)
	{
		// .data section
		pSectionData = new IMAGE_SECTION_HEADER;
		{
			Section[Header.NumberOfSections] = pSectionData;
			Header.NumberOfSections++;
			memset(pSectionData, 0, sizeof(IMAGE_SECTION_HEADER));
			strcpy((char*)pSectionData->Name, ".data");
			pSectionData->VirtualAddress = 0x2000;
			pSectionData->Misc.VirtualSize = 0x1000;
			pSectionData->Characteristics = IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_INITIALIZED_DATA;

			pSectionData->NumberOfRelocations = 0;
		}
	}

	/*
	pSourceFile = new SourceFile;
	pSourceFile->m_filename = "C:\\test.cpp";

	pSourceFile->m_segments.push_back(SourceFile::Segment(0, 70));
//	pSourceFile->m_lines.push_back(SourceFile::SourceLine(0, 14));
//	pSourceFile->m_lines.push_back(SourceFile::SourceLine(4, 15));
*/

	{
		for (int i = 0; i < objectfiles.size(); i++)
		{
			try
			{
				FileByteStream file(objectfiles[i]);//.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);//FILE* fpin = fopen(objectfiles[i].c_str(), "rb");

				ObjectFileParser* pOFile = new AOutParser;
				if (pOFile)
				{
					int scode = pOFile->Read(&file);
					if (scode == 0)
					{
						int nsymbols = pOFile->GetNumberOfSymbols();

						ASSERT(0);	// TODO
						pDebugInfo = pOFile->GetDebugInfo(NULL);

						gsymmap::iterator* l2g = new gsymmap::iterator[nsymbols];

						for (int i = 0; i < nsymbols; i++)
						{
						//	const char* symbolname = NULL;
						//	Linker::CSymbol symbol;
						//	symbols.insert(Linker::symbolmap::value_type(symbolname, symbol));

							ObjectSymbol* pSymbol = pOFile->GetSymbol(i);

							if (pSymbol->n_type & N_STAB)
							{
								/*
								if (pSymbol->n_type == N_SLINE)
								{
									pSourceFile->m_lines.push_back(SourceFile::SourceLine(pSymbol->n_value, pSymbol->n_desc+1));
								}
								*/
							}
						//	printf("%s\n", pSymbol->n_name);
						//	if ((pSymbol->n_type & N_TYPE) != N_UNDF)
							else
							{
							// Map local symbol to global symbol
								gsymmap::iterator symboli = globsyms.find(pSymbol->n_name);
								if (symboli == globsyms.end())
								{
									printf("undefined external symbol: %s\n", pSymbol->n_name);

									l2g[i] = NULL;
								//	printf("Multiple defined symbol '%s'\n", pSymbol->n_name);
								}
								else
								{
									l2g[i] = symboli;
									(*l2g[i]).second->Value = /*windowsHeader.ImageBase + pSection->VirtualAddress +*/ pSymbol->n_value;
									//	Linker::CSymbol symbol;
									//	symbols.insert(Linker::symbolmap::value_type(pSymbol->n_name, symbol));
								}
							}

						/*
							if ((pSymbol->n_type & N_TYPE) != N_UNDF)
							{
							}
							*/
						}

						/*
						{
							Pass(pOFile);
						}
						*/

						// text
						{
							long pos = ftell(fileout);
							pSectionText->PointerToRawData = (pos+windowsHeader.FileAlignment-1) / windowsHeader.FileAlignment * windowsHeader.FileAlignment;
							while (pos < pSectionText->PointerToRawData)
							{
								fputc(0, fileout);
								pos++;
							}

							int textsize = pOFile->GetDataSize(0);
							BYTE* textdata = pOFile->GetData(0);

							int nrelocs = pOFile->GetNumberOfRelocations(0);
							for (int i = 0; i < nrelocs; i++)
							{
								Relocation* pReloc = pOFile->GetRelocation(0, i);

								if (pReloc->r_extern)
								{
									ObjectSymbol* pSymbol = pOFile->GetSymbol(pReloc->r_symbolnum);

									gsymmap::iterator gsym = l2g[pReloc->r_symbolnum];
									if (gsym != NULL)
									{
										StringA name = (*gsym).first;

										/*
										for (int j = 0; j < m_objfiles.size(); j++)
										{
										}
										*/

										//*(DWORD*)(textdata + pReloc->r_address) = 0;
										DWORD _Offset = ftell(fileout) + pReloc->r_address;
										(*gsym).second->refs.Add(_Offset);
									}

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
										*(DWORD*)(textdata + pReloc->r_address) += windowsHeader.ImageBase + pSectionText->VirtualAddress;
									}
									else if ((pReloc->r_symbolnum & N_TYPE) == N_DATA)
									{
										*(DWORD*)(textdata + pReloc->r_address) += windowsHeader.ImageBase + pSectionData->VirtualAddress;
									}
									else
										ASSERT(0);
								}
							}

							fwrite(textdata, 1, textsize, fileout);

							pos = ftell(fileout);
							pSectionText->SizeOfRawData = (pos+windowsHeader.FileAlignment-1) / windowsHeader.FileAlignment * windowsHeader.FileAlignment - pSectionText->PointerToRawData;
							while (pos < pSectionText->PointerToRawData + pSectionText->SizeOfRawData)
							{
								fputc(0, fileout);
								pos++;
							}

							windowsHeader.SizeOfImage += pSectionText->SizeOfRawData;

						// relocations
							pos = ftell(fileout);
							if (pSectionText->NumberOfRelocations > 0)
							{
								pSectionText->PointerToRelocations = (pos+windowsHeader.FileAlignment-1) / windowsHeader.FileAlignment * windowsHeader.FileAlignment;
								
								for (int i = 0; i < pSectionText->NumberOfRelocations; i++)
								{
									fwrite(pRelocations[i], sizeof(IMAGE_RELOCATION), 1, fileout);
								}
							}
						}

						// .data section
						{
							ULONG datasize = pOFile->GetDataSize(1);
							if (datasize)
							{
								BaseOfData = 0x2000;	// TODO
								/*
								long pos = ftell(fileout);
								pSectionData->PointerToRawData = (pos+windowsHeader.FileAlignment-1) / windowsHeader.FileAlignment * windowsHeader.FileAlignment;
								while (pos < pSectionData->PointerToRawData)
								{
									fputc(0, fileout);
									pos++;
								}
								*/
								pSectionData->PointerToRawData = align(fileout, windowsHeader.FileAlignment);

								pSectionData->SizeOfRawData += datasize;

								// The data itself (TODO)
								for (int i = 0; i < datasize; i++)
								{
									fput8(fileout, 0);
								}

								pSectionData->SizeOfRawData = align(fileout, windowsHeader.FileAlignment) - pSectionData->PointerToRawData;
								/*
								pos = ftell(fileout);
								pSectionData->SizeOfRawData = (pos+windowsHeader.FileAlignment-1) / windowsHeader.FileAlignment * windowsHeader.FileAlignment - pSectionData->PointerToRawData;
								while (pos < pSectionData->PointerToRawData + pSectionData->SizeOfRawData)
								{
									fputc(0, fileout);
									pos++;
								}
								*/

								windowsHeader.SizeOfImage += pSectionData->SizeOfRawData;
							}

							// TODO, data relocations
						}
					}
					else
					{
						printf("Invalid object file : '%s'\n", objectfiles[i].c_str());
					}

#if 0	// TODO, have this
					delete pOFile;//->Release();
#endif
				}
			}
			catch(int)
			{
				printf("Couldn't open file '%s'\n", objectfiles[i].c_str());
			}
		}
	}

	// .idata section
	if (TRUE)
	{
		optionalStandardHeader.SizeOfInitializedData = 0x1000;

		IMAGE_SECTION_HEADER* pSection = new IMAGE_SECTION_HEADER;

		Section[Header.NumberOfSections] = pSection;
		Header.NumberOfSections++;

		memset(pSection, 0, sizeof(IMAGE_SECTION_HEADER));
		strcpy((char*)pSection->Name, ".idata");
		pSection->VirtualAddress = 0x2000;
		pSection->Misc.VirtualSize = 0x1000;
		pSection->Characteristics = IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_INITIALIZED_DATA;

		pSection->PointerToRawData = align(fileout, windowsHeader.FileAlignment);

		idmap importDirectoryMap;

		// Sort symbols by import DLL
		{
			gsymmap::iterator symi = globsyms.begin();
			while (symi != globsyms.end())
			{
				if ((*symi).second->refs.size())
				{
					pair<idmap::iterator, bool> id_bool = importDirectoryMap.insert(idmap::value_type((*symi).second->importDLL, gsymmap()));

					idmap::iterator id = id_bool.first;
					(*id).second.insert(gsymmap::value_type((*symi).first, (*symi).second));
				}

				++symi;
			}
		}

		// IMAGE_DIRECTORY_ENTRY_IMPORT
		DWORD fpDirectoryEntryImport = ftell(fileout);

		int importDirectoryMapSize = importDirectoryMap.size();
		IMAGE_IMPORT_DIRECTORY* importDirectory = new IMAGE_IMPORT_DIRECTORY[importDirectoryMapSize];
		memset(importDirectory, 0, sizeof(IMAGE_IMPORT_DIRECTORY)*importDirectoryMapSize);

		DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = FilePointerToRVA(pSection, fileout);
		DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = sizeof(IMAGE_IMPORT_DIRECTORY)*(importDirectoryMapSize);

		fseek(fileout, sizeof(IMAGE_IMPORT_DIRECTORY)*(importDirectoryMapSize+1), SEEK_CUR);	// Make room

		idmap::iterator idi;
		
		idi = importDirectoryMap.begin();
		for (int j = 0; j < importDirectoryMapSize; j++)
		{
			importDirectory[j].Name = FilePointerToRVA(pSection, fileout);//pSection->VirtualAddress + ftell(fileout) - pSection->PointerToRawData;
			fputs((*idi).first.c_str(), fileout);
			fputc(0, fileout);

			importDirectory[j].ImportLookupTable = FilePointerToRVA(pSection, fileout);
			//importDirectory[0].ImportAddressTable = 
			WriteImportLookupTable(pSection, (*idi).second, fileout);

			++idi;
		}

		DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = FilePointerToRVA(pSection, fileout);//->VirtualAddress;
		long pos = ftell(fileout);

		// IMAGE_DIRECTORY_ENTRY_IAT
		idi = importDirectoryMap.begin();
		for (j = 0; j < importDirectoryMapSize; j++)
		{
			gsymmap::iterator isym = (*idi).second.begin();
			int nsym = 0;
			while (isym != (*idi).second.end())
			{
				for (int i = 0; i < (*isym).second->refs.size(); i++)
				{
					DWORD fixupOffset = (*isym).second->refs[i];
					Write32(fileout,fixupOffset, windowsHeader.ImageBase + FilePointerToRVA(pSection, fileout) + nsym*4);
				}

				++isym;
				nsym++;
			}

			importDirectory[j].ImportAddressTable = FilePointerToRVA(pSection, fileout);
			WriteImportLookupTable(pSection, (*idi).second, fileout);

			++idi;
		}

		DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = ftell(fileout)-pos;

		{
			long oldpos = ftell(fileout);
			fseek(fileout, fpDirectoryEntryImport, SEEK_SET);
			fwrite(importDirectory, 1, sizeof(IMAGE_IMPORT_DIRECTORY)*(importDirectoryMapSize), fileout);

			// write an empty specifying the end
			IMAGE_IMPORT_DIRECTORY ide_empty;
			memset(&ide_empty, 0, sizeof(IMAGE_IMPORT_DIRECTORY));
			fwrite(&ide_empty, 1, sizeof(IMAGE_IMPORT_DIRECTORY), fileout);

			fseek(fileout, oldpos, SEEK_SET);
		}

		// IMAGE_DEBUG_TYPE_CODEVIEW
		if (false)
		{
			IMAGE_DEBUG_DIRECTORY idd = {0};
			idd.Type = IMAGE_DEBUG_TYPE_CODEVIEW;

			DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress = FilePointerToRVA(pSection, fileout);
			DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size = sizeof(idd);

			idd.PointerToRawData = ftell(fileout) + sizeof(idd);
			idd.AddressOfRawData = FilePointerToRVA(pSection, idd.PointerToRawData);

			fwrite(&idd, 1, sizeof(idd), fileout);

			unsigned long startOffset = ftell(fileout);

			fwrite("NB11", 1, 4, fileout);

			long dirOffset = ftell(fileout) - startOffset + 4;
			fwrite(&dirOffset, 1, 4, fileout);

			OMFDirHeader dirheader;
			dirheader.cbDirHeader = sizeof(OMFDirHeader);
			dirheader.cbDirEntry = 12;
			dirheader.cDir = 1;
			dirheader.lfoNextDir = 0;
			dirheader.flags = 0;

			SourceFile* pSourceFile = new SourceFile;
			pSourceFile->m_filename = "C:\\test.cpp";

			pSourceFile->m_segments.Add(SourceFile::Segment(0, 20));
			pSourceFile->m_lines.Add(SourceFile::SourceLine(0, 0));
			pSourceFile->m_lines.Add(SourceFile::SourceLine(4, 1));

			fwrite(&dirheader, 1, dirheader.cbDirHeader, fileout);

			// Make room for direntries
			fseek(fileout, dirheader.cDir * dirheader.cbDirEntry, SEEK_CUR);

			OMFDirEntry direntry[1];
			direntry[0].SubSection = sstSrcModule;
			direntry[0].iMod = 0;

			for (int i = 0; i < 1; i++)
			{
				long direntryfpos = ftell(fileout);
				direntry[i].lfo = direntryfpos - startOffset;

				OMFSourceModule srcModule;
				srcModule.cFile = 1;
				srcModule.cSeg = 0;
				srcModule.baseSrcFile[0] = 4+4/*ftell(fileout) - startOffset + 4*/;

				fwrite(&srcModule, 1, 4, fileout);

				fwrite(srcModule.baseSrcFile, 1, 4, fileout);

				for (int nfile = 0; nfile < 1; nfile++)
				{
					OMFSourceFile srcFile;
					srcFile.cSeg = pSourceFile->m_segments.GetSize();
					srcFile.reserved = 0;
					fwrite(&srcFile, 1, 4, fileout);

					long fpos = ftell(fileout);
					fseek(fileout, srcFile.cSeg*4, SEEK_CUR);	// Make room for srcLines array

					for (int nseg = 0; nseg < srcFile.cSeg; nseg++)
					{
						SourceFile::Segment seg = pSourceFile->m_segments[nseg];
						fwrite(&seg.m_startAddress, 1, 4, fileout);
						fwrite(&seg.m_endAddress, 1, 4, fileout);
					}

					// Filename
					uint8 name[256];
					name[0] = pSourceFile->m_filename.length();
					strcpy((char*)name+1, pSourceFile->m_filename.c_str());
					fwrite(name, 1, name[0]+1, fileout);

					// src lines
					srcFile.baseSrcLn[0] = ftell(fileout) - direntryfpos;
					for (nseg = 0; nseg < srcFile.cSeg; nseg++)
					{
						OMFSourceLine lines;
						lines.Seg = 0;
						lines.cLnOff = pSourceFile->m_lines.GetSize();
						fwrite(&lines, 1, 4, fileout);

						for (int i = 0; i < lines.cLnOff; i++)
						{
							fwrite(&pSourceFile->m_lines[i].m_address, 1, 4, fileout);
						}

						for (i = 0; i < lines.cLnOff; i++)
						{
							fwrite(&pSourceFile->m_lines[i].m_line, 1, 2, fileout);
						}
					}

					// Update srclines array
					long fpos2 = ftell(fileout);
					fseek(fileout, fpos, SEEK_SET);
					fwrite(srcFile.baseSrcLn, 1, 4*srcFile.cSeg, fileout);

					fseek(fileout, fpos2, SEEK_SET);
				}

				direntry[i].cb = (ftell(fileout) - startOffset) - direntry[i].lfo;
			}

			long fpos = ftell(fileout);

			// Update direntries
			fseek(fileout, startOffset + dirOffset + dirheader.cbDirHeader, SEEK_SET);
			for (i = 0; i < 1; i++)
			{
				fwrite(&direntry[i], 1, dirheader.cbDirEntry, fileout);
			}

			fseek(fileout, fpos, SEEK_SET);
		}

		pSection->SizeOfRawData = align(fileout, windowsHeader.FileAlignment) - pSection->PointerToRawData;

	//	DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = 0;
	//	DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = 0;

		windowsHeader.SizeOfImage += pSection->SizeOfRawData;
	}

	BOOL bCOFFDebug = FALSE;

	if (true)//TRUE)//bDebug)	// Debug Info
	{
		// .debug section
		IMAGE_SECTION_HEADER* pSection = new IMAGE_SECTION_HEADER;

		IMAGE_COFF_SYMBOLS_HEADER coffSymHeader = {0};
		long fpCoffSymHeader;
		{

			Section[Header.NumberOfSections] = pSection;
			Header.NumberOfSections++;

			memset(pSection, 0, sizeof(IMAGE_SECTION_HEADER));
			strcpy((char*)pSection->Name, ".rdata");
			pSection->VirtualAddress = 0x3000;
			pSection->Misc.VirtualSize = 0x30000;
			pSection->Characteristics = IMAGE_SCN_MEM_READ /*| IMAGE_SCN_MEM_WRITE*/ | IMAGE_SCN_CNT_INITIALIZED_DATA;

			optionalStandardHeader.SizeOfInitializedData += 0x30000;

			pSection->PointerToRawData = align(fileout, windowsHeader.FileAlignment);

			long pointerToDirectoryDebug = ftell(fileout);

			int count = 0;

			if (bCOFFDebug)	// COFF
				count++;

			count++;	// misc
			count++;	// codeview

			DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress = FilePointerToRVA(pSection, fileout);
			DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size = sizeof(IMAGE_DEBUG_DIRECTORY)*count;//ftell(fileout) - pSection->PointerToRawData;

			IMAGE_DEBUG_DIRECTORY DebugDirectories[4];
			IMAGE_DEBUG_DIRECTORY* pDirectoryDebug = DebugDirectories;

			fseek(fileout, sizeof(IMAGE_DEBUG_DIRECTORY) * count, SEEK_CUR);

			if (bCOFFDebug)	// COFF
			{
				IMAGE_DEBUG_DIRECTORY* idd = pDirectoryDebug++;
				idd->Type = /*IMAGE_DEBUG_TYPE_CODEVIEW;//*/IMAGE_DEBUG_TYPE_COFF;
				idd->PointerToRawData = ftell(fileout) + sizeof(IMAGE_DEBUG_DIRECTORY);
				idd->AddressOfRawData = FilePointerToRVA(pSection, fileout) + sizeof(IMAGE_DEBUG_DIRECTORY);
				idd->SizeOfData = sizeof(IMAGE_COFF_SYMBOLS_HEADER);
			//	fwrite(idd, sizeof(IMAGE_DEBUG_DIRECTORY), 1, fileout);

			// ??

			//	coffSymHeader.LvaToFirstSymbol =
				fpCoffSymHeader = ftell(fileout);
				fseek(fileout, sizeof(IMAGE_COFF_SYMBOLS_HEADER), SEEK_CUR);	// Make room
			}

			if (true)
			{

				char filename[260] = "C:\\testdev\\Win32\\test.exe";
				BYTE pad[3] = {0};

				int len = 260;//strlen(filename)+1;
				//int paddedlen = (len+3) & ~3;	// long align

				IMAGE_DEBUG_MISC idm = {0};
				idm.DataType = IMAGE_DEBUG_MISC_EXENAME;
				idm.Length = offsetof(IMAGE_DEBUG_MISC, Data) + len;//paddedlen;
				idm.Unicode = FALSE;

				IMAGE_DEBUG_DIRECTORY* idd = pDirectoryDebug++;
				idd->TimeDateStamp = Header.TimeDateStamp;
				idd->Type = IMAGE_DEBUG_TYPE_MISC;
				idd->PointerToRawData = ftell(fileout);// + sizeof(IMAGE_DEBUG_DIRECTORY);
				idd->AddressOfRawData = 0;//FilePointerToRVA(pSection, fileout);// + sizeof(IMAGE_DEBUG_DIRECTORY);
				idd->SizeOfData = idm.Length;
			//	fwrite(idd, sizeof(IMAGE_DEBUG_DIRECTORY), 1, fileout);

				fwrite(&idm, 1, offsetof(IMAGE_DEBUG_MISC, Data), fileout);
				fwrite(filename, 1, len, fileout);
				//fwrite(pad, paddedlen-len, 1, fileout);	// pad bytes
			}

			if (true)	// codeview inside EXE
			{
//				IMAGE_DEBUG_DIRECTORY idd = {0};
				IMAGE_DEBUG_DIRECTORY* idd = pDirectoryDebug++;
				idd->Type = IMAGE_DEBUG_TYPE_CODEVIEW;
				idd->TimeDateStamp = Header.TimeDateStamp;
			//	idd.PointerToRawData = ftell(fileout) + sizeof(IMAGE_DEBUG_DIRECTORY);
			//	idd.AddressOfRawData = FilePointerToRVA(pSection, fileout) + sizeof(IMAGE_DEBUG_DIRECTORY);
			//	idd.SizeOfData = sizeof(IMAGE_COFF_SYMBOLS_HEADER);
			//	fwrite(&idd, sizeof(IMAGE_DEBUG_DIRECTORY), 1, fileout);

				long directoryOffset = ftell(fileout);
			//	fseek(fileout, sizeof(IMAGE_DEBUG_DIRECTORY), SEEK_CUR);	// Make room

				idd->PointerToRawData = ftell(fileout);
				idd->AddressOfRawData = 0;//FilePointerToRVA(pSection, fileout);// + sizeof(IMAGE_DEBUG_DIRECTORY);

#if 0
				{
						{
							FILE* f = fopen("C:/data", "rb");
							fseek(f, 0, SEEK_END);
							long size = ftell(f);
							rewind(f);
							char* data = new char[size];
							fread(data, 1, size, f);
							fclose(f);

							fwrite(data, 1, size, fileout);
						}
				}
#endif
#if 0
				{
					unsigned long startOffset = ftell(fileout);

					fwrite("NB11", 1, 4, fileout);

					long dirOffset = ftell(fileout) - startOffset + 4;
					fwrite(&dirOffset, 1, 4, fileout);

					OMFDirHeader dirheader;
					dirheader.cbDirHeader = sizeof(OMFDirHeader);
					dirheader.cbDirEntry = 12;
					dirheader.cDir = 1;
					dirheader.lfoNextDir = 0;
					dirheader.flags = 0;

					SourceFile* pSourceFile = new SourceFile;
					pSourceFile->m_filename = "C:\\test.cpp";

					pSourceFile->m_segments.push_back(SourceFile::Segment(0, 20));
					pSourceFile->m_lines.push_back(SourceFile::SourceLine(0, 0));
					pSourceFile->m_lines.push_back(SourceFile::SourceLine(4, 1));

					fwrite(&dirheader, 1, dirheader.cbDirHeader, fileout);

					// Make room for direntries
					fseek(fileout, dirheader.cDir * dirheader.cbDirEntry, SEEK_CUR);

					OMFDirEntry direntry[1];
					direntry[0].SubSection = sstSrcModule;
					direntry[0].iMod = 0;

					for (int i = 0; i < 1; i++)
					{
						long direntryfpos = ftell(fileout);
						direntry[i].lfo = direntryfpos - startOffset;

						OMFSourceModule srcModule;
						srcModule.cFile = 1;
						srcModule.cSeg = 0;
						srcModule.baseSrcFile[0] = 4+4/*ftell(fileout) - startOffset + 4*/;

						fwrite(&srcModule, 1, 4, fileout);

						fwrite(srcModule.baseSrcFile, 1, 4, fileout);

						for (int nfile = 0; nfile < 1; nfile++)
						{
							OMFSourceFile srcFile;
							srcFile.cSeg = pSourceFile->m_segments.size();
							srcFile.reserved = 0;
							fwrite(&srcFile, 1, 4, fileout);

							long fpos = ftell(fileout);
							fseek(fileout, srcFile.cSeg*4, SEEK_CUR);	// Make room for srcLines array

							for (int nseg = 0; nseg < srcFile.cSeg; nseg++)
							{
								SourceFile::Segment seg = pSourceFile->m_segments[nseg];
								fwrite(&seg.m_startAddress, 1, 4, fileout);
								fwrite(&seg.m_endAddress, 1, 4, fileout);
							}

							// Filename
							uint8 name[256];
							name[0] = pSourceFile->m_filename.length();
							strcpy((char*)name+1, pSourceFile->m_filename.c_str());
							fwrite(name, 1, name[0]+1, fileout);

							// src lines
							srcFile.baseSrcLn[0] = ftell(fileout) - direntryfpos;
							for (nseg = 0; nseg < srcFile.cSeg; nseg++)
							{
								OMFSourceLine lines;
								lines.Seg = 0;
								lines.cLnOff = pSourceFile->m_lines.size();
								fwrite(&lines, 1, 4, fileout);

								for (int i = 0; i < lines.cLnOff; i++)
								{
									fwrite(&pSourceFile->m_lines[i].m_address, 1, 4, fileout);
								}

								for (i = 0; i < lines.cLnOff; i++)
								{
									fwrite(&pSourceFile->m_lines[i].m_line, 1, 2, fileout);
								}
							}

							// Update srclines array
							long fpos2 = ftell(fileout);
							fseek(fileout, fpos, SEEK_SET);
							fwrite(srcFile.baseSrcLn, 1, 4*srcFile.cSeg, fileout);

							fseek(fileout, fpos2, SEEK_SET);
						}

						direntry[i].cb = (ftell(fileout) - startOffset) - direntry[i].lfo;
					}

					long fpos = ftell(fileout);

					// Update direntries
					fseek(fileout, startOffset + dirOffset + dirheader.cbDirHeader, SEEK_SET);
					for (i = 0; i < 1; i++)
					{
						fwrite(&direntry[i], 1, dirheader.cbDirEntry, fileout);
					}

					fseek(fileout, fpos, SEEK_SET);
				}
#endif

				CCodeView codeview;
			//	MemDirHeader* dirheader = MakeCodeView(&Header, Section);

				MemDirHeader* dirheader = codeview.AddDirHeader(&Header, Section);
				OMFDirEntry* moduleEntry = codeview.AddModule(dirheader, 1, "test.obj");
				OMFDirEntry* alignSymEntry = codeview.AddAlignSym(dirheader, 1);
				OMFDirEntry* sourceModuleEntry = codeview.AddSourceModule(dirheader, 1);
			//	OMFDirEntry* publicEntry = codeview.AddPublicSym(dirheader);
				/*
				codeview.AddGlobalPub(dirheader);
				codeview.AddGlobalSym(dirheader);
				codeview.AddStaticSym(dirheader);
				*/
				codeview.AddGlobalTypes(dirheader);

				OMFDirEntry* segmapEntry = codeview.AddSegMap(dirheader);
				OMFDirEntry* fileindexEntry = codeview.AddFileIndex(dirheader);

				codeview.WriteCodeView(fileout, dirheader);

				idd->SizeOfData = ftell(fileout) - idd->PointerToRawData;

				/*
				long oldpos = ftell(fileout);
				fseek(fileout, directoryOffset, SEEK_SET);
				fwrite(idd, sizeof(idd), 1, fileout);
				fseek(fileout, oldpos, SEEK_SET);
				*/
			}

		// Update Debug directories
			long fpos = ftell(fileout);
			fseek(fileout, pointerToDirectoryDebug, SEEK_SET);
			fwrite(DebugDirectories, 1, sizeof(IMAGE_DEBUG_DIRECTORY) * count, fileout);
			fseek(fileout, fpos, SEEK_SET);
		}

	// Codeview in separate .dbg file



		if (bCOFFDebug)	// COFF in EXE file
		{
			// Line numbers
			{
				pSectionText->PointerToLinenumbers = ftell(fileout);
				pSectionText->NumberOfLinenumbers = 1;
				long Type = 2;	// Symbol Table Index
				long LineNumber = 0;
				fwrite(&Type, 1, 4, fileout);
				fwrite(&LineNumber, 1, 4, fileout);
			}
	//
			Header.PointerToSymbolTable = ftell(fileout);

			Header.NumberOfSymbols = 0;//globsyms.size();
		//	fseek(fileout, Header.PointerToSymbolTable, SEEK_SET);

		// Build Symbol Records

			CArray<IMAGE_SYMBOL*, IMAGE_SYMBOL*> symbolRecords;
			int sizeOfStringTable = 0;

			coffSymHeader.LvaToFirstSymbol = ftell(fileout);
			{
				IMAGE_SYMBOL* file = (IMAGE_SYMBOL*)calloc(sizeof(IMAGE_SYMBOL), 1);
				strcpy((char*)file->N.ShortName, ".file");
				file->SectionNumber = -1;
				file->StorageClass = IMAGE_SYM_CLASS_FILE;
				file->NumberOfAuxSymbols = 1;
				symbolRecords.Add(file);
				{
					IMAGE_AUX_SYMBOL* aux_symbol = (IMAGE_AUX_SYMBOL*)calloc(sizeof(IMAGE_AUX_SYMBOL), 1);
					memcpy(aux_symbol, "C:\\test.cpp", 11);
					symbolRecords.Add((IMAGE_SYMBOL*)aux_symbol);
				}
			}

			gsymmap::iterator symi = globsyms.begin();
			while (symi != globsyms.end())
			{
				GlobalSymbol* psym = (*symi).second;
				if (psym->defined == 1)
				{
					IMAGE_SYMBOL* image_symbol = (IMAGE_SYMBOL*)calloc(sizeof(IMAGE_SYMBOL), 1);

					int len = (*symi).first.length();
					if (len < 8)
					{
						strcpy((char*)image_symbol->N.ShortName, (*symi).first.c_str());
					}
					else
					{
						image_symbol->N.Name.Short = 0;
						image_symbol->N.Name.Long = sizeOfStringTable;
						sizeOfStringTable += len+1;
					}

				//	memcpy(image_symbol.N.ShortName, pSymbol->N.ShortName, 8);
					image_symbol->Value = psym->Value;
					image_symbol->SectionNumber = 1;// TODO pSymbol->SectionNumber;
					image_symbol->Type = 0x20;//IMAGE_REL_I386_DIR32;//pSymbol->Type;
					image_symbol->StorageClass = IMAGE_SYM_CLASS_EXTERNAL;//IMAGE_SYM_CLASS_FUNCTION;// TODO pSymbol->StorageClass;

				//	fwrite(&image_symbol, 1, sizeof(IMAGE_SYMBOL), fileout);
					symbolRecords.Add(image_symbol);

					if (image_symbol->Type == 0x20)	// Function
					{
						symbolRecords[symbolRecords.size()-1]->NumberOfAuxSymbols++;

						{
							IMAGE_AUX_SYMBOL* aux_symbol = (IMAGE_AUX_SYMBOL*)calloc(sizeof(IMAGE_AUX_SYMBOL), 1);;
							aux_symbol->Sym.TagIndex = symbolRecords.size()+1;	// index of .bf
							aux_symbol->Sym.FcnAry.Function.PointerToLinenumber = 0;
							aux_symbol->Sym.FcnAry.Function.PointerToNextFunction = 0;
							aux_symbol->Section.NumberOfLinenumbers = 0;
						
							symbolRecords.Add((IMAGE_SYMBOL*)aux_symbol);
						}

						// .bf
						{
							IMAGE_SYMBOL* bf = (IMAGE_SYMBOL*)calloc(sizeof(IMAGE_SYMBOL), 1);
							strcpy((char*)bf->N.ShortName, ".bf");
							bf->StorageClass = IMAGE_SYM_CLASS_FUNCTION;
							bf->NumberOfAuxSymbols = 1;
							symbolRecords.Add(bf);

							{
								IMAGE_AUX_SYMBOL* aux_symbol = (IMAGE_AUX_SYMBOL*)calloc(sizeof(IMAGE_AUX_SYMBOL), 1);
								aux_symbol->Sym.Misc.LnSz.Linenumber = 0;
								symbolRecords.Add((IMAGE_SYMBOL*)aux_symbol);
							}
						}

						// .lf
						{
							IMAGE_SYMBOL* lf = (IMAGE_SYMBOL*)calloc(sizeof(IMAGE_SYMBOL), 1);
							strcpy((char*)lf->N.ShortName, ".lf");
							lf->StorageClass = IMAGE_SYM_CLASS_FUNCTION;
							lf->Value = 1;	// Number of lines
							symbolRecords.Add(lf);
						}

						// .ef
						{
							IMAGE_SYMBOL* ef = (IMAGE_SYMBOL*)calloc(sizeof(IMAGE_SYMBOL), 1);
							strcpy((char*)ef->N.ShortName, ".ef");
							ef->StorageClass = IMAGE_SYM_CLASS_FUNCTION;
							ef->NumberOfAuxSymbols = 1;
							symbolRecords.Add(ef);

							{
								IMAGE_AUX_SYMBOL* aux_symbol = (IMAGE_AUX_SYMBOL*)calloc(sizeof(IMAGE_AUX_SYMBOL), 1);
								aux_symbol->Sym.Misc.LnSz.Linenumber = 1;
								symbolRecords.Add((IMAGE_SYMBOL*)aux_symbol);
							}
						}
					}

				}
				++symi;
			}

		// Write symbols
			Header.NumberOfSymbols = symbolRecords.GetSize();
			coffSymHeader.NumberOfSymbols = Header.NumberOfSymbols;
			for (int i = 0; i < symbolRecords.GetSize(); i++)
			{
				fwrite(symbolRecords[i], sizeof(IMAGE_SYMBOL), 1, fileout);
			}

		// Write Strings
			{
			//	long stringTableOffset = ftell(fileout);

				long v = sizeOfStringTable + 4;
				fwrite(&v, 1, 4, fileout);
	//			for (
	//			fwrite(m_StringTable, 1, sizeOfStringTable, fileout);
			}
		}

		pSection->SizeOfRawData = align(fileout, windowsHeader.FileAlignment) - pSection->PointerToRawData;

		/*
		pSection->SizeOfRawData = ftell(fileout) - pSection->PointerToRawData;

		long size = pSection->SizeOfRawData;
		while (size < pSection->Misc.VirtualSize)
		{
			fputc(0, fileout);
			size++;
		}
		*/

	//	pSection->SizeOfRawData = align(fileout, windowsHeader.FileAlignment) - pSection->PointerToRawData;
		windowsHeader.SizeOfImage += pSection->Misc.VirtualSize;

		if (bCOFFDebug)
		{
			long oldpos = ftell(fileout);
			fseek(fileout, fpCoffSymHeader, SEEK_SET);
			fwrite(&coffSymHeader, sizeof(IMAGE_COFF_SYMBOLS_HEADER), 1, fileout);
			fseek(fileout, oldpos, SEEK_SET);
		}
	}

// Update section headers
	{
		fseek(fileout, PointerToSections, SEEK_SET);
		for (int i = 0; i < Header.NumberOfSections; i++)
		{
			fwrite(Section[i], 1, sizeof(IMAGE_SECTION_HEADER), fileout);
		}
	}

	// Update Header
	{
		fseek(fileout, headerpos, SEEK_SET);
		fwrite(&Header, 1, sizeof(IMAGE_FILE_HEADER), fileout);
	}
	// Update Optional header and data directories
	{
		fwrite(&optionalStandardHeader, 1, sizeof(optionalStandardHeader), fileout);
//		DWORD	BaseOfData = 0x2000;//	Address, relative to image base, of beginning of data section, when loaded into memory.
		fwrite(&BaseOfData, 1, 4, fileout);
		fwrite(&windowsHeader, 1, sizeof(windowsHeader), fileout);

		for (int i = 0; i < windowsHeader.NumberOfRvaAndSizes; i++)
		{
			fwrite(&DataDirectory[i], 1, sizeof(IMAGE_DATA_DIRECTORY), fileout);
		}
	}

	fileout = NULL;

#if 0
	if (bDebug)
	{
		char dbgpathname[640];
		_makepath(dbgpathname, NULL, m_outputPathName.c_str(), "test", ".dbg");
		dbgfile = fopen(dbgpathname, "wb");
		if (dbgfile == NULL)
		{
			printf("Failed to create debug file '%s'\n", dbgpathname);
		}

		WriteCodeView(dbgfile);

		fclose(dbgfile);
		dbgfile = NULL;
	}
#endif

#if 0
#endif

	return 0;
}

int CConfiguration::MachO_Pass2(FILE* fileout)
{
	fseek(fileout, sizeof(MachO::mach_header), SEEK_CUR);	// Make room for header

	MachO::mach_header header;
	header.magic = MH_MAGIC;
	header.cputype = MACHO_CPU_TYPE_POWERPC;
	header.cpusubtype = 0;
	header.filetype = MH_EXECUTE;
	header.ncmds = 0;
	header.flags = MH_NOUNDEFS | MH_DYLDLINK;
	long cmds_fpos = ftell(fileout);

	CArray<MachO::load_command*, MachO::load_command*> commands;

	{
		MachO::segment_command* pcmd = new MachO::segment_command;
		memset(pcmd, 0, sizeof(*pcmd));
		pcmd->cmd = LC_SEGMENT;
		pcmd->cmdsize = sizeof(MachO::segment_command);
		pcmd->vmaddr = 0;
		pcmd->vmsize = 4096;
		pcmd->flags = SG_NORELOC;
		strcpy(pcmd->segname, "__PAGEZERO");
		commands.Add((MachO::load_command*)pcmd);
	}

	MachO::section* text_section;
	{
		MachO::segment_command* pcmd = (MachO::segment_command*)new uint8[sizeof(MachO::segment_command) + sizeof(MachO::section)*1];
		memset(pcmd, 0, sizeof(*pcmd));
		pcmd->cmd = LC_SEGMENT;
		pcmd->cmdsize = sizeof(MachO::segment_command) + sizeof(MachO::section)*1;
		strcpy(pcmd->segname, "__TEXT");
		pcmd->fileoff = 0;
		pcmd->filesize = 4096;
		pcmd->vmaddr = 4096;
		pcmd->vmsize = 4096;
		pcmd->maxprot = 7;
		pcmd->initprot = 5;
		pcmd->flags = 0;//SG_NORELOC;

		pcmd->nsects = 1;

		/*
		fileoff: 0
		filesize: 4096
		vmaddr: 4096
		vmsize: 4096
		maxprot: 7
		initprot: 5
		flags: 0
		*/
		MachO::section* sect = (MachO::section*)(pcmd+1);
		text_section = sect;

		strcpy(sect->segname, "__TEXT");
		strcpy(sect->sectname, "__text");
	//	sect->addr = 4096 + 3092;
	//	sect->size = 4;
	//	sect->offset = 3092;
		sect->align = 2;
		sect->reloff = 0;
		sect->nreloc = 0;
		sect->flags = MACHO_S_REGULAR;
		sect->reserved1 = 0;
		sect->reserved2 = 0;

		commands.Add((MachO::load_command*)pcmd);
	}

	{
		MachO::segment_command* pcmd = (MachO::segment_command*)new uint8[sizeof(MachO::segment_command) + sizeof(MachO::section)*1];
		memset(pcmd, 0, sizeof(*pcmd));
		pcmd->cmd = LC_SEGMENT;
		pcmd->cmdsize = sizeof(MachO::segment_command) + sizeof(MachO::section)*1;
		strcpy(pcmd->segname, "__DATA");
		pcmd->fileoff = 4096;
		pcmd->filesize = 0;
		pcmd->vmaddr = 4096*2;
		pcmd->vmsize = 4096;
		pcmd->maxprot = 7;
		pcmd->initprot = 5;
		pcmd->flags = SG_NORELOC;

		pcmd->nsects = 1;

		MachO::section* sect = (MachO::section*)(pcmd+1);

		strcpy(sect->segname, "__DATA");
		strcpy(sect->sectname, "__data");
		sect->addr = 4096*2;
		sect->size = 0;
		sect->offset = 4096*2;
		sect->align = 2;
		sect->reloff = 0;
		sect->nreloc = 0;
		sect->flags = MACHO_S_REGULAR;
		sect->reserved1 = 0;
		sect->reserved2 = 0;

		commands.Add((MachO::load_command*)pcmd);
	}

	{
		char* loader = "/usr/lib/dyld";

		MachO::dylinker_command* pcmd = (MachO::dylinker_command*)new uint8[sizeof(MachO::dylinker_command) + strlen(loader)+1];
		pcmd->cmd = LC_LOAD_DYLINKER;
		pcmd->name.offset = sizeof(MachO::dylinker_command);
		pcmd->cmdsize = sizeof(MachO::dylinker_command) + strlen(loader) + 1;

		strcpy((char*)(pcmd+1), loader);
		commands.Add((MachO::load_command*)pcmd);
	}

	CArray<nlist*, nlist*> symbols;

	MachO::symtab_command* symtab_cmd;
	{
		nlist* n = new nlist;
		n->n_un.n_strx = 1;
		n->n_type = MACHO_SYMBOL_TYPE_N_SECT | MACHO_SYMBOL_N_EXT;
		n->n_other = 1;	// nsect
		n->n_desc = REFERENCE_FLAG_UNDEFINED_NON_LAZY;
		n->n_value = 4096 + 3092;

		symbols.Add(n);

		MachO::symtab_command* pcmd = new MachO::symtab_command;
		memset(pcmd, 0, sizeof(*pcmd));
		pcmd->cmd = LC_SYMTAB;
		pcmd->cmdsize = sizeof(MachO::symtab_command);
		pcmd->nsyms = symbols.size();
		pcmd->symoff = 3092 + 4096*2;
		pcmd->stroff = pcmd->symoff + pcmd->nsyms * sizeof(nlist);
		pcmd->strsize = 7;

		commands.Add((MachO::load_command*)pcmd);
		symtab_cmd = pcmd;
	}

	{
		MachO::thread_command* pcmd = (MachO::thread_command*)new uint8[sizeof(MachO::thread_command) + sizeof(MachO::MACHO_PPC_THREAD_STATE)];
		memset(pcmd, 0, sizeof(MachO::thread_command) + sizeof(MachO::MACHO_PPC_THREAD_STATE));
		pcmd->cmd = LC_UNIXTHREAD;
		pcmd->cmdsize = sizeof(MachO::thread_command) + sizeof(MachO::MACHO_PPC_THREAD_STATE);
		pcmd->flavor = FLAVOR_PPC_THREAD_STATE;
		pcmd->count = sizeof(MachO::MACHO_PPC_THREAD_STATE) / 4;
		MachO::MACHO_PPC_THREAD_STATE* state = (MachO::MACHO_PPC_THREAD_STATE*)(pcmd+1);
		state->srr0 = 4096+3092;

		commands.Add((MachO::load_command*)pcmd);
	}

	// Make room for sections
	{
		for (int i = 0; i < commands.GetSize(); i++)
		{
			MachO::load_command* command = commands[i];

			long cmdsize = (command->cmdsize + 3) & ~3;

			fseek(fileout, cmdsize, SEEK_CUR);
		}
	}

	header.sizeofcmds = ftell(fileout) - cmds_fpos;

	int fpos = ftell(fileout);
	while (fpos < 3092)
	{
		fput8(fileout, 0);
		fpos++;
	}

	text_section->addr = 4096 + 3092;
	text_section->size = 0;
	text_section->offset = ftell(fileout);//3092;

// test
//	fput32(fileout, 0x4E800020);	// blr
	//fput32(fileout, 0x7FE00008);	// trap
	//fpos += 4;
	// text data
	{
		for (int i = 0; i < objectfiles.size(); i++)
		{
			FILE* fpin = fopen(objectfiles[i].c_str(), "rb");
			if (fpin)
			{
				ObjectFileParser* pOFile = new AOutParser;
				if (pOFile)
				{
					ASSERT(0);
#if 0
					int scode = pOFile->Read(fpin);
					if (scode == 0)
					{
						int textsize = pOFile->GetTextSize();
						BYTE* textdata = pOFile->GetText();

						fwrite(textdata, textsize, 1, fileout);

						fpos += textsize;

						text_section->size += textsize;
					}
					else
					{
						printf("Invalid object file : '%s'\n", objectfiles[i].c_str());
					}
#endif
				}
			}
		}
	}

	while (fpos < 3092+4096)
	{
		fput8(fileout, 0);
		fpos++;
	}

// data
	while (fpos < 3092+4096+4096)
	{
		fput8(fileout, 0);
		fpos++;
	}

	symtab_cmd->symoff = ftell(fileout);

	// Symbols
	{
		for (int i = 0; i < symbols.size(); i++)
		{
			nlist* n = symbols[i];

			fput32(fileout, n->n_un.n_strx);
			fput8(fileout, n->n_type);
			fput8(fileout, n->n_other);	// sect
			fput16(fileout, n->n_desc);
			fput32(fileout, n->n_value);
		}
	}
	// Strings
	fwrite("\0start", 7, 1, fileout);

	// Write sections
	{
		fseek(fileout, sizeof(MachO::mach_header), SEEK_SET);

		for (int i = 0; i < commands.GetSize(); i++)
		{
			MachO::load_command* command = commands[i];

			long cmdsize = (command->cmdsize + 3) & ~3;

			fput32(fileout, command->cmd);
			fput32(fileout, cmdsize);

			if (command->cmd == LC_SEGMENT)
			{
				MachO::segment_command* pcmd = (MachO::segment_command*)command;

				fwrite(pcmd->segname, 16, 1, fileout);
				fput32(fileout, pcmd->vmaddr);
				fput32(fileout, pcmd->vmsize);
				fput32(fileout, pcmd->fileoff);
				fput32(fileout, pcmd->filesize);
				fput32(fileout, pcmd->maxprot);
				fput32(fileout, pcmd->initprot);
				fput32(fileout, pcmd->nsects);
				fput32(fileout, pcmd->flags);

				MachO::section* sections = (MachO::section*)(pcmd+1);

				{
					for (int i = 0; i < pcmd->nsects; i++)
					{
						fwrite(sections[i].sectname, 16, 1, fileout);
						fwrite(sections[i].segname, 16, 1, fileout);
						fput32(fileout, sections[i].addr);
						fput32(fileout, sections[i].size);
						fput32(fileout, sections[i].offset);
						fput32(fileout, sections[i].align);
						fput32(fileout, sections[i].reloff);
						fput32(fileout, sections[i].nreloc);
						fput32(fileout, sections[i].flags);
						fput32(fileout, sections[i].reserved1);
						fput32(fileout, sections[i].reserved2);
					}
				}
			}
			else if (command->cmd == LC_SYMTAB)
			{
				MachO::symtab_command* pcmd = (MachO::symtab_command*)command;
				fput32(fileout, pcmd->symoff);
				fput32(fileout, pcmd->nsyms);
				fput32(fileout, pcmd->stroff);
				fput32(fileout, pcmd->strsize);
			}
			else if (command->cmd == LC_LOAD_DYLINKER)
			{
				MachO::dylinker_command* pcmd = (MachO::dylinker_command*)command;

				fput32(fileout, pcmd->name.offset);
				fwrite(pcmd+1, pcmd->cmdsize-sizeof(MachO::dylinker_command), 1, fileout);
			}
			else if (command->cmd == LC_UNIXTHREAD)
			{
				MachO::thread_command* pcmd = (MachO::thread_command*)command;//new BYTE[sizeof(thread_command) + sizeof(MACHO_PPC_THREAD_STATE)];
				fput32(fileout, pcmd->flavor);
				fput32(fileout, pcmd->count);

				DWORD* state = (DWORD*)(pcmd+1);

				for (int i = 0; i < pcmd->count; i++)
				{
					fput32(fileout, state[i]);
				}
			}
			else
				ASSERT(0);

			for (int k = command->cmdsize; k < cmdsize; k++)
			{
				fput8(fileout, 0);
			}
		}
	}

	// Write header
	header.ncmds = commands.size();
	fseek(fileout, 0, SEEK_SET);
	fput32(fileout, header.magic);
	fput32(fileout, header.cputype);
	fput32(fileout, header.cpusubtype);
	fput32(fileout, header.filetype);
	fput32(fileout, header.ncmds);
	fput32(fileout, header.sizeofcmds);
	fput32(fileout, header.flags);

	return 0;
}

int CConfiguration::AmigaHunk_Pass2(FILE* fileout)
{
	int num_hunks = 2;
	fput32(fileout, HUNK_HEADER);
	fput32(fileout, 0);	// names ?
	fput32(fileout, num_hunks);
	fput32(fileout, 0);	// first hunk to load ?
	fput32(fileout, num_hunks-1);	// last hunk to load ?

	ULONG* hunkSizes = new ULONG[num_hunks];

	// Make room for ULONG*num_hunks
	fseek(fileout, 4*num_hunks, SEEK_CUR);

	for (int i = 0; i < objectfiles.size(); i++)
	{
		FileByteStream* fpin = new FileByteStream(objectfiles[i].c_str());
		if (fpin)
		{
			ObjectFileParser* pOFile = new AOutParser;
			if (pOFile)
			{
				int scode = pOFile->Read(fpin);
				if (scode == 0)
				{
					// Hunk 0 (Code/Reloc32)
					{
						int textsize = pOFile->GetDataSize(0);
						uint8* textdata = pOFile->GetData(0);

						int longsize = (textsize+3)/4;

						hunkSizes[0] = longsize;

						fput32(fileout, HUNK_CODE);
						fput32(fileout, longsize);

						long textpos = ftell(fileout);
						fwrite(textdata, 1, textsize, fileout);

						BYTE pad[3] = {0};
						fwrite(pad, 1, (longsize*4)-textsize, fileout);

						/*
						{
							Pass(pOFile);
						}
						*/

						{
							int nrelocs = pOFile->GetNumberOfRelocations(0);

							fput32(fileout, HUNK_RELOC32);

							{
								CArray<DWORD, DWORD> relocs;

								for (int i = 0; i < nrelocs; i++)
								{
									Relocation* pReloc = pOFile->GetRelocation(0, i);

									if (pReloc->r_extern)
									{
										ASSERT(0);

										ObjectSymbol* pSymbol = pOFile->GetSymbol(pReloc->r_symbolnum);
										//if (pSymbol->SectionNumber == 0
										if ((pSymbol->n_type & N_TYPE) == N_TEXT)
										{
											relocs.Add(pReloc->r_address);
										}
										ASSERT(0);
#if 0

										Linker::symbolmap::iterator symboli = symbols.find(pSymbol->n_name);
										if (symboli == symbols.end())
										{
											printf("Unresolved external symbol '%s'\n", pSymbol->n_name);
										}
#endif
									}
									else
									{
										if ((pReloc->r_symbolnum & N_TYPE) == N_TEXT)
										{
											relocs.Add(pReloc->r_address);
										}
									}
								}

								if (relocs.size() > 0)
								{
									fput32(fileout, relocs.size());
									fput32(fileout, 0);	// hunk number (TEXT hunk)
									for (int i = 0; i < relocs.size(); i++)
									{
										fput32(fileout, relocs[i]);
									}
								}
							}

							{
								CArray<DWORD, DWORD> relocs;

								for (int i = 0; i < nrelocs; i++)
								{
									Relocation* pReloc = pOFile->GetRelocation(0, i);

									if (pReloc->r_extern)
									{
										ASSERT(0);

										ObjectSymbol* pSymbol = pOFile->GetSymbol(pReloc->r_symbolnum);
										//if (pSymbol->SectionNumber == 1
										if ((pSymbol->n_type & N_TYPE) == N_DATA)
										{
											relocs.Add(pReloc->r_address);
										}
									}
									else
									{
										if ((pReloc->r_symbolnum & N_TYPE) == N_DATA)
										{
											relocs.Add(pReloc->r_address);
										}
									}
								}
								if (relocs.size() > 0)
								{
									fput32(fileout, relocs.size());
									fput32(fileout, 1);	// hunk number (DATA hunk)
									for (int i = 0; i < relocs.size(); i++)
									{
										fput32(fileout, relocs[i]);
									}

									long pos = ftell(fileout);
									// 
									for (i = 0; i < relocs.size(); i++)
									{
										fseek(fileout, textpos + relocs[i], SEEK_SET);
										long value;

										value = BigEndian32(*(long*)(textdata + relocs[i]));//fread(&value, 4, 1, fileout);
										value -= textsize;
										fput32(fileout, value);	// write it back
									}

									fseek(fileout, pos, SEEK_SET);
								}
							}

#if 0
							for (int i = 0; i < nrelocs; i++)
							{
							//	const char* symbolname = NULL;
							//	Linker::CSymbol symbol;
							//	symbols.insert(Linker::symbolmap::value_type(symbolname, symbol));
								Relocation* pReloc = pOFile->GetRelocation(i);

								fput32(fileout, pReloc->r_address);
								
							//	pReloc->r_symbolnum;

								//printf("%s\n", pSymbol->n_name);
							}
#endif

							fput32(fileout, 0/*nrelocs*/);
						}
						fput32(fileout, HUNK_END);	// End of hunk 0
					}

				// Hunk 1 (Data)
					{
						ULONG datasize = pOFile->GetDataSize(1);

						ULONG longs = (datasize+3)/4;
						fput32(fileout, HUNK_DATA);
						fput32(fileout, longs);

						// The data itself
						for (int i = 0; i < longs*4; i++)
						{
							fput8(fileout, 0);
						}

						fput32(fileout, HUNK_END);	// End of hunk 1

						hunkSizes[1] = longs;
					}
				}
				else
				{
					printf("Invalid object file : '%s'\n", objectfiles[i].c_str());
				}

				delete pOFile;//->Release();
			}

			delete fpin;
		}
		else
		{
			printf("Couldn't open file '%s'\n", objectfiles[i].c_str());
		}
	}

	// Update hunk_sizes
	fseek(fileout, 20, SEEK_SET);	// right past hunk header
	for (i = 0; i < num_hunks; i++)
	{
		fput32(fileout, hunkSizes[i]);
	}

	return 0;
}

int CConfiguration::Pass1()
{
	Array<StringA> m_libpaths;
	m_libpaths.Add("C:\\program files\\microsoft sdk\\lib");

	for (int i = 0; i < objectfiles.size(); i++)
	{
		FileByteStream* file;
		try
		{
			file = new FileByteStream(objectfiles[i]);//.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		}
		catch(int)
		{
			file = NULL;

			for (int j = 0; j < m_libpaths.GetSize(); j++)
			{
				char buf[512];
				sprintf(buf, "%s\\%s", m_libpaths[j].c_str(), objectfiles[i].c_str());
			//	fpin = fopen(buf, "rb");
				try
				{
					file = new FileByteStream(buf);
					break;
				}
				catch(int)
				{
					file = NULL;
				}
			}
		}

		if (file)
		{
			ArchFile arch;
			if (arch.Read(file) >= 0)
			{
				ArchFile::symbolmap::iterator symi = arch.symbols.begin();
				while (symi != arch.symbols.end())
				{
					StringA name = (*symi).first;

					DWORD Offset = (*symi).second;
				//	printf("%d", Offset);

					//fseek(fpin, Offset, SEEK_SET);
					file->Seek(Offset, STREAM_SEEK_SET);

					ArchiveHeader header;
					if (file->Read(&header, sizeof(header)) != sizeof(header))
					{
					//	break;
					}
					DWORD Size = header.GetHeaderSize();

					WORD Sig[2];
					file->Read(Sig, 4);

					if (Sig[0] == IMAGE_FILE_MACHINE_UNKNOWN && Sig[1] == 0xffff)
					{
						ImportHeader importHeader;
						file->Read(&importHeader, sizeof(importHeader));
						BYTE Type = importHeader.Flags & 0x3;
						BYTE NameType = (importHeader.Flags>>2)&0x7;

						char* data = new char[importHeader.SizeOfData];

						file->Read(data, importHeader.SizeOfData);

						char* importName = data;
						char* importDLL = data + strlen(data) + 1;

						StringA publicName;

						if (NameType == IMPORT_ORDINAL)
						{
							ASSERT(0);
						}
						else if (NameType == IMPORT_NAME_NOPREFIX)
						{
							char* p = importName;
							if (*p == '@' || *p == '?' || *p == '_')
							{
								p++;
							}

							publicName = p;
						}
						else if (NameType == IMPORT_NAME_UNDECORATE)
						{
							char* p = importName;
							if (*p == '@' || *p == '?' || *p == '_')
							{
								p++;
							}

							while (*p)
							{
								if (*p == '@') break;
								publicName += *p;
								p++;
							}
						}
						else
							ASSERT(0);

						GlobalSymbol* globsym = new GlobalSymbol;

						globsym->defined = -1;
						globsym->ordinalHint = importHeader.OrdinalHint;
						globsym->importDLL = importDLL;
						globsym->publicName = strdup(publicName.c_str());

					//	printf("%d/%s/%s\n", importHeader.OrdinalHint, importName, importDLL);
			
						globsyms.insert(gsymmap::value_type(importName, globsym));
					}

					++symi;
				}
			}
			else
			{
				file->Seek(0, STREAM_SEEK_SET);	// rewind

				ObjectFileParser* pOFile = new AOutParser;
				if (pOFile)
				{
					int scode = pOFile->Read(file);
					if (scode == 0)
					{
						int nsymbols = pOFile->GetNumberOfSymbols();

						//gsymmap::iterator* l2g = new gsymmap::iterator[nsymbols];

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
							else if ((pSymbol->n_type & N_TYPE) != N_UNDF)
						//	if (!(pSymbol->n_type & (1<<4)))	// !extern
							{
								gsymmap::iterator symboli = globsyms.find(pSymbol->n_name);
								if (symboli == globsyms.end())
								{
								//	pSymbol->n_type
									GlobalSymbol* globsym = new GlobalSymbol;

									globsym->defined = true;
								//	globsym->ordinalHint = importHeader.OrdinalHint;
								//	globsym->importDLL = importDLL;
								//	globsym->publicName = strdup(publicName.c_str());

								//	printf("%d/%s/%s\n", importHeader.OrdinalHint, importName, importDLL);
					
									globsyms.insert(gsymmap::value_type(pSymbol->n_name, globsym));
								}
								else
								{
									printf("multiple defined symbol %s\n", pSymbol->n_name);
								}
							}
						}
					}
					delete pOFile;
				}
			}
		}
		else
		{
			printf("failed to open file %s\n", objectfiles[i].c_str());
		}
	}

	return 0;
}

int CConfiguration::Link(FILE* fileout)
{
	printf("Linking...\n");

	Pass1();

	if (m_exeType == 1)	// Amiga Hunk
	{
		AmigaHunk_Pass2(fileout);
	}
	else if (m_exeType == 2)	// COFF EXE
	{
		COFF_Pass2(fileout);
	}
	else if (m_exeType == 3)	// Mach-O
	{
		return MachO_Pass2(fileout);
	}
	else
		ASSERT(0);

	return 0;
}
