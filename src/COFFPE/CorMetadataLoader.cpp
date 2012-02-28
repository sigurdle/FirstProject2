#include "StdAfx.h"

#include "../include/coff.h"

/*
#define Array var
#include <windows.h>
#undef Array
*/

#ifndef __IMAGE_COR20_HEADER_DEFINED__
#define __IMAGE_COR20_HEADER_DEFINED__

typedef enum ReplacesCorHdrNumericDefines
{
// COM+ Header entry point flags.
    COMIMAGE_FLAGS_ILONLY               =0x00000001,
    COMIMAGE_FLAGS_32BITREQUIRED        =0x00000002,
    COMIMAGE_FLAGS_IL_LIBRARY           =0x00000004,
    COMIMAGE_FLAGS_STRONGNAMESIGNED     =0x00000008,
    COMIMAGE_FLAGS_TRACKDEBUGDATA       =0x00010000,

// Version flags for image.
    COR_VERSION_MAJOR_V2                =2,
    COR_VERSION_MAJOR                   =COR_VERSION_MAJOR_V2,
    COR_VERSION_MINOR                   =0,
    COR_DELETED_NAME_LENGTH             =8,
    COR_VTABLEGAP_NAME_LENGTH           =8,

// Maximum size of a NativeType descriptor.
    NATIVE_TYPE_MAX_CB                  =1,   
    COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE=0xFF,

// #defines for the MIH FLAGS
    IMAGE_COR_MIH_METHODRVA             =0x01,
    IMAGE_COR_MIH_EHRVA                 =0x02,    
    IMAGE_COR_MIH_BASICBLOCK            =0x08,

// V-table constants
    COR_VTABLE_32BIT                    =0x01,          // V-table slots are 32-bits in size.   
    COR_VTABLE_64BIT                    =0x02,          // V-table slots are 64-bits in size.   
    COR_VTABLE_FROM_UNMANAGED           =0x04,          // If set, transition from unmanaged.
    COR_VTABLE_CALL_MOST_DERIVED        =0x10,          // Call most derived method described by

// EATJ constants
    IMAGE_COR_EATJ_THUNK_SIZE           =32,            // Size of a jump thunk reserved range.

// Max name lengths    
    //@todo: Change to unlimited name lengths.
    MAX_CLASS_NAME                      =1024,
    MAX_PACKAGE_NAME                    =1024,
} ReplacesCorHdrNumericDefines;

// COM+ 2.0 header structure.
typedef struct IMAGE_COR20_HEADER
{
    // Header versioning
    DWORD                   cb;              
    uint16                    MajorRuntimeVersion;
    uint16                    MinorRuntimeVersion;
    
    // Symbol table and startup information
    IMAGE_DATA_DIRECTORY    MetaData;        
    DWORD                   Flags;           
    DWORD                   EntryPointToken;
    
    // Binding information
    IMAGE_DATA_DIRECTORY    Resources;
    IMAGE_DATA_DIRECTORY    StrongNameSignature;

    // Regular fixup and binding information
    IMAGE_DATA_DIRECTORY    CodeManagerTable;
    IMAGE_DATA_DIRECTORY    VTableFixups;
    IMAGE_DATA_DIRECTORY    ExportAddressTableJumps;

    // Precompiled image info (internal use only - set to zero)
    IMAGE_DATA_DIRECTORY    ManagedNativeHeader;
    
} IMAGE_COR20_HEADER, *PIMAGE_COR20_HEADER;

#endif // __IMAGE_COR20_HEADER_DEFINED__

struct STREAM_HEADER
{
	DWORD Offset;//									 Memory offset to start of this stream from start of the metadata root (see clause 23.2.1)
	DWORD	 Size;//									 Size of this stream in bytes, shall be a multiple of 4.
//	 Name
//	 Name of the stream as null terminated variable length array of ASCII characters, padded with \0 characters 
};

struct STREAM_TILDE
{
	DWORD Reserved;// Reserved, always 0 (see Section 23.1).
	uint8 MajorVersion;// Major version of table schemata, always 1 (see Section 23.1).
	uint8 MinorVersion;// Minor version of table schemata, always 0 (see Section 23.1).
	uint8 HeapSizes;// Bit vector for heap sizes.
	uint8 Reserved2;// Reserved, always 1 (see Section 23.1).
	LONGLONG Valid;// Bit vector of present tables, let n be the number of bits that are 1.
	LONGLONG Sorted;// Bit vector of sorted tables
}; 

class CStream
{
public:
	STREAM_HEADER m_streamHeader;
	char m_Name[256];
};

// Signature stuff

#define ELEMENT_TYPE_END 0x00// Marks end of a list
#define ELEMENT_TYPE_VOID  0x01
#define ELEMENT_TYPE_BOOLEAN  0x02
#define ELEMENT_TYPE_CHAR  0x03
#define ELEMENT_TYPE_I1  0x04
#define ELEMENT_TYPE_U1  0x05
#define ELEMENT_TYPE_I2  0x06
#define ELEMENT_TYPE_U2  0x07
#define ELEMENT_TYPE_I4	 0x08
#define ELEMENT_TYPE_U4  0x09
#define ELEMENT_TYPE_I8  0x0a
#define ELEMENT_TYPE_U8  0x0b
#define ELEMENT_TYPE_R4 0x0c
#define ELEMENT_TYPE_R8 0x0d
#define ELEMENT_TYPE_STRING  0x0e
#define ELEMENT_TYPE_PTR    0x0f// Followed by <type> token
#define ELEMENT_TYPE_BYREF  0x10// Followed by <type> token
#define ELEMENT_TYPE_VALUETYPE  0x11// Followed by <type> token
#define ELEMENT_TYPE_CLASS  0x12// Followed by <type> token
#define ELEMENT_TYPE_ARRAY  0x14// <type> <rank> <boundsCount> <bound1> … <loCount> <lo1> …
#define ELEMENT_TYPE_TYPEDBYREF 0x16
#define ELEMENT_TYPE_I 0x18// System.IntPtr

static char* ElementTypeString[] =
{
"void",
"boolean",
"char",
"int8",
"unsigned int8",
"int16",
"unsigned int16",
"int32",
"unsigned int32",
"int64",
"unsigned int64",
"float32",
"float64",
"string",
};

 /*
    ELEMENT_TYPE_U 
 0x19
 System.UIntPtr
 
    ELEMENT_TYPE_FNPTR
 0x1b
 Followed by full method signature
 
    ELEMENT_TYPE_OBJECT
 0x1c
 System.Object
 
    ELEMENT_TYPE_SZARRAY
 0x1d
 Single-dim array with 0 lower bound
 */

#define ELEMENT_TYPE_CMOD_REQD 0x1f// Required modifier : followed by a TypeDef or TypeRef token
#define ELEMENT_TYPE_CMOD_OPT 0x20// Optional modifier : followed by a TypeDef or TypeRef token
 /*
    ELEMENT_TYPE_INTERNAL
 0x21
 Implemented within the CLI
 
 
  
  
 
    ELEMENT_TYPE_MODIFIER 
 0x40
 Or’d with following element types
 
    ELEMENT_TYPE_SENTINEL
 0x41
 Sentinel for varargs method signature
 
    ELEMENT_TYPE_PINNED
 0x45
 Denotes a local variable that points at a pinned object
 */

/*
Visibility attributes
 
VisibilityMask     
 0x00000007
 Use this mask to retrieve visibility information
 
NotPublic          
 0x00000000
 Class has no public scope
 
Public             
 0x00000001
 Class has public scope
 
NestedPublic       
 0x00000002
 Class is nested with public visibility
 
NestedPrivate      
 0x00000003
 Class is nested with private visibility
 
NestedFamily       
 0x00000004
 Class is nested with family visibility
 
NestedAssembly     
 0x00000005
 Class is nested with assembly visibility
 
NestedFamANDAssem  
 0x00000006
 Class is nested with family and assembly visibility
 
NestedFamORAssem   
 0x00000007
 Class is nested with family or assembly visibility
 
Class layout attributes
 
LayoutMask         
 0x00000018
 Use this mask to retrieve class layout information
 
AutoLayout         
 0x00000000
 Class fields are auto-laid out
 
SequentialLayout   
 0x00000008
 Class fields are laid out sequentially
 
ExplicitLayout     
 0x00000010
 Layout is supplied explicitly
 
Class semantics attributes
*/
#define ClassSemanticsMask    0x00000020 // Use this mask to retrive class semantics information
#define Class                0x00000000 // Type is a class
#define Interface             0x00000020 // Type is an interface
 /*
Special semantics in addition to class semantics
 */
#define Abstract       0x00000080// Class is abstract
#define Sealed         0x00000100// Class cannot be extended
#define SpecialName    0x00000400// Class name is special

/*
Implementation Attributes
 
Import                
 0x00001000
 Class/Interface is imported
 
Serializable          
 0x00002000
 Class is serializable
 
String formatting Attributes
 
StringFormatMask      
 0x00030000
 Use this mask to retrieve string information for native interop
 
AnsiClass             
 0x00000000
 LPSTR is interpreted as ANSI
 
UnicodeClass          
 0x00010000
 LPSTR is interpreted as Unicode
 
AutoClass             
 0x00020000
 LPSTR is interpreted automatically
 
Class Initialization Attributes
 
BeforeFieldInit       
 0x00100000
 Initialize the class before first static field access
 
Additional Flags
 
RTSpecialName    
 0x00000800
 CLI provides 'special' behavior, depending upon the name of the Type
 
HasSecurity      
 0x00040000
 Type has security associate with it
 */

//Flags for Params [ParamAttributes]
#define In 0x0001// Param is [In]    
#define Out 0x0002// Param is [out]   
#define Optional 0x0004 //Param is optional    
#define HasDefault 0x1000// Param has default value
#define HasFieldMarshal 0x2000// Param has FieldMarshal
#define Unused 0xcfe0// Reserved: shall be zero in a conforming implementation
 

class CParam
{
public:
	uint16 Flags;
	char NameString[256];
};

class CMethod
{
public:
	DWORD RVA;// (a 4 byte constant)
	uint16 ImplFlags;// (a 2 byte bitmask of type MethodImplAttributes, clause 22.1.9)
	uint16 Flags;// (a 2 byte bitmask of type MethodAttribute, clause 22.1.9)
	uint16 ParamList;
	char NameString[256];

	CParam* pParams;
	int ParamCount;
};

class CMemberRef
{
public:
	DWORD ClassIndex;
	DWORD SignatureIndex;
	char NameString[256];
};

#define MemberAccessMask 0x0007
#define Compilercontrolled 0x0000// Member not referenceable
#define Private 0x0001// Accessible only by the parent type
#define FamANDAssem 0x0002// Accessible by sub-types only in this Assembly
#define Assem 0x0003// Accessibly by anyone in the Assembly
#define Family 0x0004// Accessible only by type and sub-types
#define FamORAssem 0x0005// Accessibly by sub-types anywhere, plus anyone in assembly
#define Public 0x0006// Accessibly by anyone who has visibility to this scope
 
#define Static 0x0010// Defined on type, else per instance
#define Final 0x0020// Method may not be overridden
#define Virtual 0x0040// Method is virtual
#define HideBySig 0x0080// Method hides by name+sig, else just by name
 

class CTypeRef
{
public:
	uint16 ResolutionScope;// (index into Module, ModuleRef, AssemblyRef or TypeRef tables, or null; more precisely, a ResolutionScope coded index)
	uint16 NameIndex;// (index into String heap)
	uint16 NamespaceIndex;// (index into String heap)

	char NameString[256];
	char NamespaceString[256];
};

class CTypeDef
{
public:
	DWORD Flags;
	char NameString[256];
	char NamespaceString[256];

	uint16 MethodList;

	CMethod* pMethods;
	int CountMethods;

	char* ExtendsName;
};

class CAssemblyRef
{
public:
	char NameString[256];
};

class CMetadata
{
public:
	long metadataRootPos;
	CStream* Streams;

	CTypeRef* pTypeRefTab;
	CTypeDef* pTypeDefTab;
	CMethod* pMethodTab;
	CParam* pParamTab;
	CMemberRef* pMemberRefTab;
	CAssemblyRef* pAssemblyRefTab;
};

void GetString(FILE* fp, CMetadata* pMD, DWORD Index, char* String)
{
	long pos = ftell(fp);
	fseek(fp, pMD->metadataRootPos + pMD->Streams[1/*String*/].m_streamHeader.Offset + Index, SEEK_SET);

	int k = 0;
	while (1)
	{
		int c = getc(fp);
		String[k++] = c;
		if (c == 0)
			break;
	}

	fseek(fp, pos, SEEK_SET);
}

DWORD GetUserString(FILE* fp, CMetadata* pMD, DWORD Index, WCHAR* *data)
{
	long pos = ftell(fp);
	fseek(fp, pMD->metadataRootPos + pMD->Streams[2/*US*/].m_streamHeader.Offset + Index, SEEK_SET);

	DWORD length;

	uint8 bs;
	fread(&bs, 1, 1, fp);
	if (!(bs & 0x80))
	{
		length = bs;
	}
	else
	{
		bs &= ~0x80;

		if (!(bs & 0x40))
		{
			uint8 x;
			fread(&x, 1, 1, fp);
			length = (bs<<8) + x;
		}
		else
		{
			bs &= ~0x40;

			uint8 x[3];
			fread(x, 3, 1, fp);
			length = (bs<<24) + (x[0]<<16) + (x[1]<<8) + (x[2]);
		}
	}

	*data = new WCHAR[length/2+1];
	fread(*data, length, 1, fp);
	(*data)[length/2] = 0;

	fseek(fp, pos, SEEK_SET);

	return length;
}

DWORD GetCompressedValue(uint8** pp)
{
	uint8* p = *pp;
	DWORD value;

	uint8 bs = *p++;
	if (!(bs & 0x80))
	{
		value = bs;
	}
	else
	{
		bs &= ~0x80;

		if (!(bs & 0x40))
		{
			uint8 x;
			//fread(&x, 1, 1, fp);
			x = *p++;
			value = (bs<<8) + x;
		}
		else
		{
			bs &= ~0x40;

			uint8 x[3];
			//fread(x, 3, 1, fp);
			x[0] = *p++;
			x[1] = *p++;
			x[2] = *p++;
			value = (bs<<24) + (x[0]<<16) + (x[1]<<8) + (x[2]);
		}
	}

	*pp = p;

	return value;
}

DWORD ReadBlob(FILE* fp, long metadataRootPos, CStream* Streams, DWORD Index, uint8* *data)
{
	long pos = ftell(fp);
	fseek(fp, metadataRootPos + Streams[4/*Blob*/].m_streamHeader.Offset + Index, SEEK_SET);

	DWORD length;

	uint8 bs;
	fread(&bs, 1, 1, fp);
	if (!(bs & 0x80))
	{
		length = bs;
	}
	else
	{
		bs &= ~0x80;

		if (!(bs & 0x40))
		{
			uint8 x;
			fread(&x, 1, 1, fp);
			length = (bs<<8) + x;
		}
		else
		{
			bs &= ~0x40;

			uint8 x[3];
			fread(x, 3, 1, fp);
			length = (bs<<24) + (x[0]<<16) + (x[1]<<8) + (x[2]);
		}
	}

	*data = new uint8[length];
	fread(*data, length, 1, fp);

	fseek(fp, pos, SEEK_SET);

	return length;
}

#define HASTHIS 0x20//, used to encode the keyword instance in the calling convention, see Section 14.3
#define EXPLICITTHIS 0x40//, used to encode the keyword explicit in the calling convention, see Section 14.3
#define DEFAULT 0x0//, used to encode the keyword default in the calling convention, see Section 14.3
#define VARARG 0x5//, used to encode the keyword vararg in the calling convention, see Section 14.3

class CILContext
{
public:
	uint8* code;
	uint8* p;

	FILE* fp;
//	long metadataRootPos;
//	CStream* metadataStreams;
	CMetadata* pMD;
};

typedef int (*op_func)(CILContext* c);

int op_notimpl(CILContext* c)
{
	printf("\top not implemented");
	c->p++;
	return 0;
}

int op_nop(CILContext* c)
{
	c->p++;
	return 0;
}

int op_break(CILContext* c)
{
	return 0;
}

int op_ldarg_0(CILContext* c)
{
	c->p++;
	return 0;
}

int op_ldarg_1(CILContext* c)
{
	c->p++;
	return 0;
}

int op_ldarg_2(CILContext* c)
{
	c->p++;
	return 0;
}

int op_ldarg_3(CILContext* c)
{
	c->p++;
	return 0;
}

int op_ldloc_0(CILContext* c)
{
	c->p++;
	return 0;
}

int op_stloc_0(CILContext* c)
{
	c->p++;
	return 0;
}

int op_stloc_s(CILContext* c)
{
	c->p++;
	uint8 indx = *c->p++;
	return 0;
}

int op_ldc_i4_0(CILContext* c)
{
	c->p++;
	return 0;
}

int op_ldstr(CILContext* c)
{
	c->p += 1;

	DWORD stringIndex = *(DWORD*)c->p;
	c->p += 4;

	stringIndex &= ~0x70000000;	// clear 3 high bits ?

	WCHAR* String;
	GetUserString(c->fp, c->pMD, stringIndex, &String);

	printf("\"%S\"", String);

	delete String;

	return 0;
}

void signatureGetCallingConvention(uint8** pp)
{
	uint8* p = *pp;

	// Calling convention
	uint8 type = *p++;
	if (type & HASTHIS)			printf("instance ");
	if (type & EXPLICITTHIS)	printf("explicit ");
	if (type & DEFAULT)			printf("default ");
	if (type & VARARG)			printf("vararg ");

	*pp = p;
}

void signatureGetParam(uint8** pp)
{
	uint8 * p = *pp;

	int CMOD = GetCompressedValue(&p);

	printf("%s", ElementTypeString[(CMOD & 0xf)-1]);

	if (CMOD & (ELEMENT_TYPE_CMOD_OPT | ELEMENT_TYPE_CMOD_REQD))
	{
		if (CMOD & ELEMENT_TYPE_CMOD_OPT)
			printf("optional ");
		else if (CMOD == ELEMENT_TYPE_CMOD_REQD)
			printf("required ");

	//	int TypeDefOrRefEncoded = GetCompressedValue(&p);
	}

	*pp = p;
}

int op_call(CILContext* c)
{
	c->p += 1;

	DWORD Method = *(DWORD*)c->p;	// methoddef or methodref
	c->p += 4;

	Method &= ~0x0a000000;
	//Method &= ~0x70000000;	// clear 3 high bits ?

	uint8* signatureData;
	DWORD length = ReadBlob(c->fp, c->pMD->metadataRootPos, c->pMD->Streams, c->pMD->pMemberRefTab[Method-1].SignatureIndex, &signatureData);
	uint8* signatureStream = signatureData;

	signatureGetCallingConvention(&signatureStream);

	DWORD paramCount = GetCompressedValue(&signatureStream);

	signatureGetParam(&signatureStream);
	printf(" ");

	DWORD ClassIndex = c->pMD->pMemberRefTab[Method-1].ClassIndex;
	uint8 Table = ClassIndex & 0x7;
	ClassIndex >>= 3;

	if (Table == 1)	// TypeRef
	{
		DWORD ResolutionScope = c->pMD->pTypeRefTab[ClassIndex-1].ResolutionScope;
		uint8 ResolutionScopeTable = ResolutionScope & 0x3;	// index into Module, ModuleRef, AssemblyRef or TypeRef tables, or null
		DWORD ResolutionScopeIndex = ResolutionScope >> 2;
		if (ResolutionScopeTable == 0)	// Module
		{
			printf("Unknown resolution scope");
		}
		else if (ResolutionScopeTable == 1)	// ModuleRef
		{
			printf("Unknown resolution scope");
		}
		else if (ResolutionScopeTable == 2)	// AssemblyRef
		{
			printf("[%s]", c->pMD->pAssemblyRefTab[ResolutionScopeIndex-1].NameString);
		}
		else	// TypeRef
		{
			printf("Unknown resolution scope");
		}

		printf("%s.%s::", c->pMD->pTypeRefTab[ClassIndex-1].NamespaceString, c->pMD->pTypeRefTab[ClassIndex-1].NameString);
	}
	else
	{
		printf("[Unknown Class]");
	}

	printf("%s", c->pMD->pMemberRefTab[Method-1].NameString);

	printf("(");

	for (int i = 0; i < paramCount; i++)
	{
		if (i > 0)
			printf(", ");

		signatureGetParam(&signatureStream);
	}

	printf(")");

	delete signatureData;

	return 0;
}

int op_ret(CILContext* c)
{
	c->p += 1;
	return 0;
}

int op_br_s(CILContext* c)
{
	c->p += 1;

	char target = *(char*)c->p;
	c->p += 1;

	printf("%4.4x", c->p-c->code+target);

	return 0;
}

struct
{
	op_func func;
	char* name;
}
ops[] =
{
	op_nop, "nop",
	op_break, "break",
	op_ldarg_0, "ldarg.0",
	op_ldarg_1, "ldarg.1",
	op_ldarg_2, "ldarg.2",
	op_ldarg_3, "ldarg.3",
	op_ldloc_0, "ldloc.0",
	op_notimpl, "ldloc.1",
	op_notimpl, "ldloc.2",
	op_notimpl, "ldloc.3",
	op_stloc_0, "stloc.0",
	op_notimpl, "stloc.1",
	op_notimpl, "stloc.2",
	op_notimpl, "stloc.3",
	op_notimpl, "ldarg.s",
	op_notimpl, "ldarga.s",
	op_notimpl, "starg.s",
	op_notimpl, "ldloc.s",
	op_notimpl, "ldloca.s",
	op_stloc_s, "stloc.s",
	op_notimpl, "ldnull",
	op_notimpl, "ldc.i4.m1",
	op_ldc_i4_0, "ldc.i4.0",
	op_notimpl, "ldc.i4.1",
	op_notimpl, "ldc.i4.2",
	op_notimpl, "ldc.i4.3",
	op_notimpl, "ldc.i4.4",
	op_notimpl, "ldc.i4.5",
	op_notimpl, "ldc.i4.6",
	op_notimpl, "ldc.i4.7",
	op_notimpl, "ldc.i4.8",
	op_notimpl, "ldc.i4.s",
	op_notimpl, "ldc.i4",
	op_notimpl, "ldc.i8",
	op_notimpl, "ldc.r4",
	op_notimpl, "ldc.r8",
	op_notimpl, "dup",
	op_notimpl, "pop",
	op_notimpl, "jmp",
	op_notimpl, NULL,
	op_call, "call",
	op_notimpl, "calli",
	op_ret, "ret",
	op_br_s, "br.s",
	op_notimpl, "brfalse.s",
	op_notimpl, "brtrue.s",
	op_notimpl, "beq.s",
	op_notimpl, "bge.s",
	op_notimpl, "bgt.s",
	op_notimpl, "ble.s",
	op_notimpl, "blt.s",
	op_notimpl, "bne.un.s",
	op_notimpl, "bge.un.s",
	op_notimpl, "bgt.un.s",
	op_notimpl, "ble.un.s",
	op_notimpl, "blt.un.s",
	op_notimpl, "br",
	op_notimpl, "brfalse",
	op_notimpl, "brtrue",
	op_notimpl, "beq",
	op_notimpl, "bge",
	op_notimpl, "bgt",
	op_notimpl, "ble",
	op_notimpl, "blt",
	op_notimpl, "bne.un",
	op_notimpl, "bge.un",
	op_notimpl, "bgt.un",
	op_notimpl, "ble.un",
	op_notimpl, "blt.un",
	op_notimpl, "switch",
	op_notimpl, "ldind.i1",
	op_notimpl, "ldind.u1",
	op_notimpl, "ldind.i2",
	op_notimpl, "ldind.u2",
	op_notimpl, "ldind.i4",
	op_notimpl, "ldind.u4",
	op_notimpl, "ldind.i8",
	op_notimpl, "ldind.i",
	op_notimpl, "ldind.r4",
	op_notimpl, "ldind.r8",
	op_notimpl, "ldind.ref",
	op_notimpl, "stind.ref",
	op_notimpl, "stind.i1",
	op_notimpl, "stind.i2",
	op_notimpl, "stind.i4",
	op_notimpl, "stind.i8",
	op_notimpl, "stind.r4",
	op_notimpl, "stind.r8",
	op_notimpl, "add",
	op_notimpl, "sub",
	op_notimpl, "mul",
	op_notimpl, "div",
	op_notimpl, "div.un",
	op_notimpl, "rem",
	op_notimpl, "rem.un",
	op_notimpl, "and",
	op_notimpl, "or",
	op_notimpl, "xor",
	op_notimpl, "shl",
	op_notimpl, "shr",
	op_notimpl, "shr.un",
	op_notimpl, "neg",
	op_notimpl, "not",
	op_notimpl, "conv.i1",
	op_notimpl, "conv.i2",
	op_notimpl, "conv.i4",
	op_notimpl, "conv.i8",
	op_notimpl, "conv.r4",
	op_notimpl, "conv.r8",
	op_notimpl, "conv.u4",
	op_notimpl, "conv.u8",
	op_notimpl, "callvirt",
	op_notimpl, "cpobj",
	op_notimpl, "ldobj",
	op_ldstr, "ldstr",
	op_notimpl, "newobj",
	op_notimpl, "castclass",
	op_notimpl, "isinst",
	op_notimpl, "conv.r.un",
	op_notimpl, "unbox",
	op_notimpl, "throw",
	op_notimpl, "ldfld",
	op_notimpl, "ldflda",
	op_notimpl, "stfld",
	op_notimpl, "ldsfld",
	op_notimpl, "ldsflda",
	op_notimpl, "stsfld",
	op_notimpl, "stobj",
	op_notimpl, "conv.ovf.i1.un",
	op_notimpl, "conv.ovf.i2.un",
	op_notimpl, "conv.ovf.i4.un",
	op_notimpl, "conv.ovf.i8.un",
	op_notimpl, "conv.ovf.u1.un",
	op_notimpl, "conv.ovf.u2.un",
	op_notimpl, "conv.ovf.u4.un",
	op_notimpl, "conv.ovf.u8.un",
	op_notimpl, "conv.ovf.i.un",
	op_notimpl, "conv.ovf.u.un",
	op_notimpl, "box",
	op_notimpl, "newarr",
	op_notimpl, "ldlen",
	op_notimpl, "ldelema",
	op_notimpl, "ldelem.i1",
	op_notimpl, "ldelem.u1",
	op_notimpl, "ldelem.i2",
	op_notimpl, "ldelem.u2",
	op_notimpl, "ldelem.i4",
	op_notimpl, "ldelem.u4",
	op_notimpl, "ldelem.i8",
	op_notimpl, "ldelem.i",
	op_notimpl, "ldelem.r4",
	op_notimpl, "ldelem.r8",
	op_notimpl, "ldelem.ref",
	op_notimpl, "stelem.i",
	op_notimpl, "stelem.i1",
	op_notimpl, "stelem.i2",
	op_notimpl, "stelem.i4",
	op_notimpl, "stelem.i8",
	op_notimpl, "stelem.r4",
	op_notimpl, "stelem.r8",
	op_notimpl, "stelem.ref",
	op_notimpl, "conv.ovf.i1",
	op_notimpl, "conv.ovf.u1",
	op_notimpl, "conv.ovf.i2",
	op_notimpl, "conv.ovf.u2",
	op_notimpl, "conv.ovf.i4",
	op_notimpl, "conv.ovf.u4",
	op_notimpl, "conv.ovf.i8",
	op_notimpl, "conv.ovf.u8",
	op_notimpl, "refanyval",
	op_notimpl, "ckfinite",
	op_notimpl, "mkrefany",
	op_notimpl, "ldtoken",
	op_notimpl, "conv.u2",
	op_notimpl, "conv.u1",
	op_notimpl, "conv.i",
	op_notimpl, "conv.ovf.i",
	op_notimpl, "conv.ovf.u",
	op_notimpl, "add.ovf",
	op_notimpl, "add.ovf.un",
	op_notimpl, "mul.ovf",
	op_notimpl, "mul.ovf.un",
	op_notimpl, "sub.ovf",
	op_notimpl, "sub.ovf.un",
	op_notimpl, "endfinally",
	op_notimpl, "leave",
	op_notimpl, "leave.s",
	op_notimpl, "stind.i",
	op_notimpl, "conv.u",
};

void decodeCIL(uint8* code, DWORD codeSize, FILE* fp, CMetadata* pMD)
{
	CILContext c;
	c.code = code;
	c.p = code;
	c.fp = fp;
	c.pMD = pMD;

	while (c.p < code+codeSize)
	{
		printf("%4.4x\t", c.p-code);

		if (*c.p == 0xfe)
		{
		}
		else
		{
			printf("%s\t\t", ops[*c.p].name);
			ops[*c.p].func(&c);
			printf("\n");
		}
	}
}

void CorMetadata(FILE* fp, IMAGE_SECTION_HEADER* SectionHeader)
{
	IMAGE_COR20_HEADER corHeader;
	fread(&corHeader, sizeof(corHeader), 1, fp);

	// Metadata
	{
		long pos = ftell(fp);
		fseek(fp, SectionHeader[0].PointerToRawData + corHeader.MetaData.VirtualAddress - SectionHeader[0].VirtualAddress, SEEK_SET);

		struct METADATA_HEADER
		{
DWORD Signature;//					 Magic signature for physical metadata : 0x424A5342.

uint16	 MajorVersion;//				 Major version, 1 (ignore on read)
uint16	 MinorVersion;//				 Minor version, 0 (ignore on read) 

DWORD			 Reserved;// Reserved, always 0 (see Section 23.1).

DWORD		 Length;//					 Length of version string in bytes, say m.        

 /*
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
		};
		CMetadata* pMD = new CMetadata;
		
		METADATA_HEADER metaDataHeader;

		pMD->metadataRootPos = ftell(fp);

		fread(&metaDataHeader, sizeof(metaDataHeader), 1, fp);

		if (metaDataHeader.Signature == 0x424A5342)
		{
			char version[4095];
			fread(version, metaDataHeader.Length, 1, fp);
			fseek(fp, (metaDataHeader.Length+3)/4*4 - metaDataHeader.Length, SEEK_CUR);

			uint16 Flags;
			fread(&Flags, 2, 1, fp);

			uint16 StreamCount;
			fread(&StreamCount, 2, 1, fp);

			pMD->Streams = new CStream[StreamCount];

			for (int i = 0; i < StreamCount; i++)
			{
				fread(&pMD->Streams[i].m_streamHeader, sizeof(STREAM_HEADER), 1, fp);

				int j = 0;
				while (1)
				{
					int c = fgetc(fp);
					pMD->Streams[i].m_Name[j++] = c;
					if (c == 0)
						break;
				}

				fseek(fp, (j+3)/4*4 - j, SEEK_CUR);

				printf("\tStream: %s Size: %d\n", pMD->Streams[i].m_Name, pMD->Streams[i].m_streamHeader.Size);
			}

			//#~

			fseek(fp, pMD->metadataRootPos + pMD->Streams[0].m_streamHeader.Offset, SEEK_SET);
			{
				STREAM_TILDE tilde;
				fread(&tilde, sizeof(tilde), 1, fp);

				if (tilde.HeapSizes & 0x1)
					printf("#String is indexed with 4 bytes\n");
				else
					printf("#String is indexed with 2 bytes\n");

				if (tilde.HeapSizes & 0x2)
					printf("#GUID is indexed with 4 bytes\n");
				else
					printf("#GUID is indexed with 2 bytes\n");

				if (tilde.HeapSizes & 0x4)
					printf("#Blob is indexed with 4 bytes\n");
				else
					printf("#Blob is indexed with 2 bytes\n");

				DWORD numberOfTableRows[64] = {0};

				for (int i = 0; i < 64; i++)
				{
					if (tilde.Valid & ((LONGLONG)1<<i))
					{
						fread(&numberOfTableRows[i], 4, 1, fp);

						printf("\tNumber of rows for table %d(0x%x) = %d\n", i, i, numberOfTableRows[i]);
					}
				}

				pMD->pTypeRefTab = new CTypeRef[numberOfTableRows[1]];
				pMD->pTypeDefTab = new CTypeDef[numberOfTableRows[2]];
				pMD->pMethodTab = new CMethod[numberOfTableRows[6]];
				pMD->pParamTab = new CParam[numberOfTableRows[8]];
				pMD->pMemberRefTab = new CMemberRef[numberOfTableRows[10]];
				pMD->pAssemblyRefTab = new CAssemblyRef[numberOfTableRows[35]];

				//
				// Module : 0x0
				if (numberOfTableRows[0])
				{
					printf("Module Table:\n");

					for (int row = 0; row < numberOfTableRows[0]; row++)
					{
						uint16 Generation;// (2 byte value, reserved, shall be zero)
						uint16 Name;// (index into String heap)
						uint16 Mvid;//  (index into Guid heap; simply a Guid used to distinguish between two versions of the same module)
						uint16 EncId;// (index into Guid heap, reserved, shall be zero)
						uint16 EncBaseId;// (index into Guid heap, reserved, shall be zero)

						fread(&Generation, 2, 1, fp);
						fread(&Name, 2, 1, fp);
						fread(&Mvid, 2, 1, fp);
						fread(&EncId, 2, 1, fp);
						fread(&EncBaseId, 2, 1, fp);

						char NameString[256];
						GetString(fp, pMD, Name, NameString);

						printf("\t%s\n", NameString);
						printf("\n");
					}
				}

				//
				// TypeRef : 0x01
				if (numberOfTableRows[1])
				{
					printf("TypeRef Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[1]; row++)
					{
						uint16 ResolutionScope;// (index into Module, ModuleRef, AssemblyRef or TypeRef tables, or null; more precisely, a ResolutionScope coded index)
						uint16 NameIndex;// (index into String heap)
						uint16 NamespaceIndex;// (index into String heap)

						fread(&ResolutionScope, 2, 1, fp);
						fread(&NameIndex, 2, 1, fp);
						fread(&NamespaceIndex, 2, 1, fp);

						pMD->pTypeRefTab[row].ResolutionScope = ResolutionScope;
						pMD->pTypeRefTab[row].NameIndex = NameIndex;
						pMD->pTypeRefTab[row].NamespaceIndex = NamespaceIndex;
						GetString(fp, pMD, NameIndex, pMD->pTypeRefTab[row].NameString);
						GetString(fp, pMD, NamespaceIndex, pMD->pTypeRefTab[row].NamespaceString);

						printf("\tResolutionScope: %d\n", pMD->pTypeRefTab[row].ResolutionScope);
						printf("\tName: %s\n", pMD->pTypeRefTab[row].NameString);
						printf("\tNamespace: %s\n", pMD->pTypeRefTab[row].NamespaceString);
						printf("\n");
					}
				}

				//
				// TypeDef : 0x02
				if (numberOfTableRows[2])
				{
					printf("TypeDef Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[2]; row++)
					{
						//DWORD Flags;// (a 4 byte bitmask of type TypeAttributes, clause 22.1.14)
						uint16 Name;// (index into String heap)
						uint16 Namespace;// (index into String heap)

						fread(&pMD->pTypeDefTab[row].Flags, 4, 1, fp);
						fread(&Name, 2, 1, fp);
						fread(&Namespace, 2, 1, fp);

						uint16 Extends;
						fread(&Extends, 2, 1, fp);

						int ExtendsTag = Extends & 0x3;	// 2 bits
						Extends >>= 2;

						pMD->pTypeDefTab[row].ExtendsName = NULL;

						if (Extends)
						{
							if (ExtendsTag == 0)	// TypeRef
							{
							}
							else if (ExtendsTag == 1)	// TypeDef
							{
								pMD->pTypeDefTab[row].ExtendsName = pMD->pTypeRefTab[Extends-1].NameString;
							}
							else if (ExtendsTag == 2)	// TypeSpec
							{
							}
							else
								printf("Invalid value in file\n");
						}

						uint16 FieldList;
						fread(&FieldList, 2, 1, fp);

						uint16 MethodList;
						fread(&MethodList, 2, 1, fp);
						pMD->pTypeDefTab[row].MethodList = MethodList;

						GetString(fp, pMD, Name, pMD->pTypeDefTab[row].NameString);
						GetString(fp, pMD, Namespace, pMD->pTypeDefTab[row].NamespaceString);
					}
				}

				//
				// Method : 0x06
				if (numberOfTableRows[6])
				{
				//	printf("Method Table:\n");
				//	printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[6]; row++)
					{
					//	DWORD RVA;// (a 4 byte constant)
					//	WORD ImplFlags;// (a 2 byte bitmask of type MethodImplAttributes, clause 22.1.9)
					//	WORD Flags;// (a 2 byte bitmask of type MethodAttribute, clause 22.1.9)
						uint16 NameIndex;// (index into String heap)

						fread(&pMD->pMethodTab[row].RVA, 4, 1, fp);
						fread(&pMD->pMethodTab[row].ImplFlags, 2, 1, fp);
						fread(&pMD->pMethodTab[row].Flags, 2, 1, fp);
						fread(&NameIndex, 2, 1, fp);

						uint16 Signature;
						fread(&Signature, 2, 1, fp);

						//uint16 ParamList;
						fread(&pMD->pMethodTab[row].ParamList, 2, 1, fp);

						GetString(fp, pMD, NameIndex, pMD->pMethodTab[row].NameString);
					}
				}

				//
				// Param : 0x08
				if (numberOfTableRows[8])
				{
					printf("Param Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[8]; row++)
					{
						uint16 Sequence;
						uint16 NameIndex;

						fread(&pMD->pParamTab[row].Flags, 2, 1, fp);
						fread(&Sequence, 2, 1, fp);
						fread(&NameIndex, 2, 1, fp);

						GetString(fp, pMD, NameIndex, pMD->pParamTab[row].NameString);
					}
				}

				//
				// MemberRef : 0x0A
				if (numberOfTableRows[10])
				{
					printf("MemberRef Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[10]; row++)
					{
						uint16 ClassIndex;
						uint16 Name;
						uint16 SignatureIndex;
						fread(&ClassIndex, 2, 1, fp);
						fread(&Name, 2, 1, fp);
						fread(&SignatureIndex, 2, 1, fp);

						pMD->pMemberRefTab[row].SignatureIndex = SignatureIndex;
						pMD->pMemberRefTab[row].ClassIndex = ClassIndex;
						GetString(fp, pMD, Name, pMD->pMemberRefTab[row].NameString);

						uint8 which = ClassIndex & 0x7;
						ClassIndex >>= 3;

						printf("\t\t%s; Class: %d/%d\n", pMD->pMemberRefTab[row].NameString, which, ClassIndex);
					}
				}

				//
				// FieldLayout : 0x10
				if (numberOfTableRows[16])
				{
					printf("FieldLayout Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[16]; row++)
					{
						DWORD Offset;
						fread(&Offset, 4, 1, fp);

						uint16 Field;	// (index into the Field table)
						fread(&Field, 2, 1, fp);
					}
				}

				//
				// CustomAttribute : 0x0C
				if (numberOfTableRows[12])
				{
					printf("CustomAttribute Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[12]; row++)
					{
						uint16 Parent;// (index into any metadata table, except the CustomAttribute table itself; more precisely, a HasCustomAttribute coded index)
						uint16 Type;// (index into the Method or MethodRef table; more precisely, a CustomAttributeType coded index)
						uint16 Value;// (index into Blob heap)

						fread(&Parent, 2, 1, fp);
						fread(&Type, 2, 1, fp);
						fread(&Value, 2, 1, fp);
					}
				}

				// StandAloneSig : 0x11
				if (numberOfTableRows[17])
				{
					printf("StandAloneSig Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[17]; row++)
					{
						uint16 Signature; //(index into the Blob heap)

						fread(&Signature, 2, 1, fp);
					}
				}

				// Assembly : 0x20
				if (numberOfTableRows[32])
				{
					printf("Assembly Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[32]; row++)
					{
						DWORD HashAlgId;// (a 4 byte constant of type AssemblyHashAlgorithm, clause 22.1.1)
						uint16 MajorVersion;
						uint16 MinorVersion;
						uint16 BuildNumber;
						uint16 RevisionNumber;
						DWORD Flags;// (a 4 byte bitmask of type AssemblyFlags, clause 22.1.2)
						uint16 PublicKey;// (index into Blob heap)
						uint16 NameIndex;// (index into String heap)
						uint16 CultureIndex;// (index into String heap) 

						fread(&HashAlgId, 4, 1, fp);
						fread(&MajorVersion, 2, 1, fp);
						fread(&MinorVersion, 2, 1, fp);
						fread(&BuildNumber, 2, 1, fp);
						fread(&RevisionNumber, 2, 1, fp);
						fread(&Flags, 4, 1, fp);
						fread(&PublicKey, 2, 1, fp);
						fread(&NameIndex, 2, 1, fp);
						fread(&CultureIndex, 2, 1, fp);

						char NameString[256];
						GetString(fp, pMD, NameIndex, NameString);

						char CultureString[256];
						GetString(fp, pMD, CultureIndex, CultureString);

						printf("\t\tName: %s\n", NameString);
						printf("\t\tCulture: %s\n", CultureString);
					}
				}

				//
				// AssemblyRef : 0x23
				if (numberOfTableRows[35])
				{
					printf("AssemblyRef Table:\n");
					printf("\n");

					// Read all rows
					for (int row = 0; row < numberOfTableRows[35]; row++)
					{
						uint16 MajorVersion;
						uint16 MinorVersion;
						uint16 BuildNumber;
						uint16 RevisionNumber;
						DWORD Flags;

						fread(&MajorVersion, 2, 1, fp);
						fread(&MinorVersion, 2, 1, fp);
						fread(&BuildNumber, 2, 1, fp);
						fread(&RevisionNumber, 2, 1, fp);
						fread(&Flags, 4, 1, fp);

						uint16 PublicKeyOrToken;	// index into Blob heap – the public key or token that identifies the author of this Assembly
						fread(&PublicKeyOrToken, 2, 1, fp);

						uint16 NameIndex;
						fread(&NameIndex, 2, 1, fp);

						uint16 CultureIndex;
						fread(&CultureIndex, 2, 1, fp);

						uint16 HashValueIndex;
						fread(&HashValueIndex, 2, 1, fp);

						GetString(fp, pMD, NameIndex, pMD->pAssemblyRefTab[row].NameString);
					}
				}

				// Build params for all methods
				{
					for (int row = 0; row < numberOfTableRows[6]; row++)
					{
						pMD->pMethodTab[row].ParamCount = 0;

						if (pMD->pMethodTab[row].ParamList > 0)
						{
							pMD->pMethodTab[row].pParams = &pMD->pParamTab[pMD->pMethodTab[row].ParamList-1];
						
							for (int i = pMD->pMethodTab[row].ParamList-1; i < numberOfTableRows[8]; i++)
							{
								if (row < numberOfTableRows[6]-1)	// Check if next method stops this run of params
								{
									if (i == pMD->pMethodTab[row+1].ParamList-1)
									{
										break;
									}
								}

								pMD->pMethodTab[row].ParamCount++;
							}
						}
					}
				}

				//
				// Build methods for all typedefs
				{
					for (int row = 0; row < numberOfTableRows[2]; row++)
					{
						pMD->pTypeDefTab[row].CountMethods = 0;

						if (pMD->pTypeDefTab[row].MethodList > 0)
						{
							pMD->pTypeDefTab[row].pMethods = &pMD->pMethodTab[pMD->pTypeDefTab[row].MethodList-1];//.NameString
						
							for (int i = pMD->pTypeDefTab[row].MethodList-1; i < numberOfTableRows[6]; i++)
							{
								if (row < numberOfTableRows[2]-1)	// Check if next typedef stops this run of methods
								{
									if (i == pMD->pTypeDefTab[row+1].MethodList-1)
									{
										break;
									}
								}

								pMD->pTypeDefTab[row].CountMethods++;
							}
						}
					}
				}

				////
				{
					for (int row = 0; row < numberOfTableRows[2]; row++)
					{
						if ((pMD->pTypeDefTab[row].Flags & ClassSemanticsMask) == Class)
						{
							printf("\tClass");
							if (pMD->pTypeDefTab[row].Flags & Abstract)
								printf(" Abstract\n");
							if (pMD->pTypeDefTab[row].Flags & Sealed)
								printf(" Sealed\n");
							if (pMD->pTypeDefTab[row].Flags & SpecialName)
								printf(" SpecialName\n");
						}
						else
							printf("\tInterface");
						
						printf(" %s", pMD->pTypeDefTab[row].NameString);
						printf(" Extends %s", pMD->pTypeDefTab[row].ExtendsName);

						printf("\t{\n");

					// Methods
						for (int k = 0; k < pMD->pTypeDefTab[row].CountMethods; k++)
						{
							printf("\t\t");

							uint16 access = pMD->pTypeDefTab[row].pMethods[k].Flags & MemberAccessMask;
							if (access == Private)
								printf("private ");
							if (access == Public)
								printf("public ");

							if (pMD->pTypeDefTab[row].pMethods[k].Flags & Static)
								printf("static ");
							if (pMD->pTypeDefTab[row].pMethods[k].Flags & Final)
								printf("final ");
							if (pMD->pTypeDefTab[row].pMethods[k].Flags & Virtual)
								printf("virtual ");

							printf("%s(", pMD->pTypeDefTab[row].pMethods[k].NameString);

							for (int n = 0; n < pMD->pTypeDefTab[row].pMethods[k].ParamCount; n++)
							{
								if (n > 0)
									printf(", ");

								printf("[");

								if (pMD->pTypeDefTab[row].pMethods[k].pParams[n].Flags & In)
									printf("in");
								if (pMD->pTypeDefTab[row].pMethods[k].pParams[n].Flags & Out)
									printf("out");
								if (pMD->pTypeDefTab[row].pMethods[k].pParams[n].Flags & Optional)
									printf("optional");

								printf("] ");

								printf("%s", pMD->pTypeDefTab[row].pMethods[k].pParams[n].NameString);
							}

							printf(");\n");
						}

						printf("\t}\n"); 
						printf("\n");
					}
				}

				{
					for (int row = 0; row < numberOfTableRows[6]; row++)
					{
						printf("** %s **\n", pMD->pMethodTab[row].NameString);
						{
							long pos = ftell(fp);

							fseek(fp, SectionHeader[0].PointerToRawData + pMD->pMethodTab[row].RVA - 0x2000, SEEK_SET);

							uint8 MethodHeader;
							fread(&MethodHeader, 1, 1, fp);
							uint8 methodType = (MethodHeader & 0x7);	// 3 least significant bits

							DWORD CodeSize;

							if (methodType == 2)	// CorILMethod_TinyFormat
							{
								CodeSize = (MethodHeader >> 2);
							}
							else if (methodType == 3) // CorILMethod_FatFormat
							{
#define CorILMethod_MoreSects 0x8// More sections follow after this header (see Section 24.4.5).
#define CorILMethod_InitLocals 0x10// Call default constructor on all local variables.

								uint8 MethodHeader2;
								fread(&MethodHeader2, 1, 1, fp);

								uint8 sizeOfHeaderInDWORDS = MethodHeader2>>4;

							//	uint8 header[16];
							//	fread(&header, sizeOfHeaderInDWORDS*4, 1, fp);

								uint16 MaxStack;
								fread(&MaxStack, 2, 1, fp);

								fread(&CodeSize, 4, 1, fp);

								DWORD LocalVarSigTok;
								fread(&LocalVarSigTok, 4, 1, fp);
							}
							else
							{
								printf("Invalid method type");
							}

							uint8* code = new uint8[CodeSize];
							fread(code, CodeSize, 1, fp);

							decodeCIL(code, CodeSize, fp, pMD);

							delete code;

							fseek(fp, pos, SEEK_SET);
						}
					}
				}
			}

			printf("\n");
		}
		else
		{
			printf("Wrong metadata header signature\n");
		}

		fseek(fp, pos, SEEK_SET);
	} // Metadata
}
