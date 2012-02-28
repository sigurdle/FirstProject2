#ifndef __ARCHFILE_H_
#define __ARCHFILE_H_

#include "objectfileparser.h"

namespace System
{

struct ImportHeader
{
	//	WORD Sig1;
	//	WORD Sig2;
	
	uint16 Version;//
	uint16 Machine;//	Number identifying type of target machine. See Section 3.3.1, “Machine Types, ” for more information.	   
	uint32 TimeDateStamp;//	Time and date the file was created.	   
	uint32 SizeOfData;//	Size of the strings following the header.	   
	uint16 OrdinalHint;//	Either the ordinal or the hint for the import, determined by the value in the Name Type field.	   
	uint16 Flags;
	/*
	2 bits	Type	The import type. See Section 8.2 Import Type for specific values and descriptions.	   
	3 bits	Name Type	The Import Name Type. See Section 8.3. Import Name Type for specific values and descriptions.	   
	11 bits	Reserved	Reserved. Must be zero.	 
	*/
};

 
// Name Type
#define IMPORT_ORDINAL				0	//The import is by ordinal. This indicates that the value in the Ordinal/Hint field of the Import Header is the import’s ordinal. If this constant is not specified, then the Ordinal/Hint field should always be interpreted as the import’s hint.	   
#define IMPORT_NAME					1	//The import name is identical to the public symbol name.	   
#define IMPORT_NAME_NOPREFIX		2	//The import name is the public symbol name, but skipping the leading ?, @, or optionally _.	   
#define IMPORT_NAME_UNDECORATE	3	//The import name is the public symbol name, but skipping the leading ?, @, or optionally _, and truncating at the first @.	 

struct CodeCompExt ArchiveHeader
{
	char Name[16];//	Name of archive member, with a slash (/) appended to terminate the name. If the first character is a slash, the name has a special interpretation, as described below.	   
	char Date[12];//	Date and time the archive member was created: ASCII decimal representation of the number of seconds since 1/1/1970 UCT.	   
	char UserID[6];//	ASCII decimal representation of the user ID.	   
	char GroupID[6];//	ASCII group representation of the group ID.	   
	char Mode[8];//	ASCII octal representation of the member’s file mode.	   
	char Size[10];//	ASCII decimal representation of the total size of the archive member, not including the size of the header.	   
	char End[2];// of Header	The two bytes in the C string “‘\n”.	 

	uint GetHeaderSize();
};

struct SYMDEF
{
	ULONG nameindex;
	ULONG fileoffset;
};

class CodeCompExt Member
{
public:
	String name;
	ULONG Offset;
	ULONG Size;
};

class CodeCompExt ArchFile : public SymbolFile
{
public:
	ArchFile();
	~ArchFile();

	typedef map<String, ULONG_PTR> symbolmap;

	typedef map<const char*,ULONG> symdefmap_t;

	symbolmap symbols;

	symdefmap_t m_symdefmap;

	vector<Member> m_members;

	ULONG m_nsymboldefs;
	SYMDEF* m_symdefs;
	char* m_strbuffer;

	virtual long Read(IO::Stream& pStream);
	virtual uint GetNumberOfSymbols();
};

}

#endif // __ARCHFILE_H_
