#ifndef System_Debug_h
#define System_Debug_h

namespace System
{

class LFCEXT SourceFile : public Object
{
public:

	class SourceLine
	{
	public:
		CTOR SourceLine(ULONG_PTR address, uint32 line) : m_address(address), m_line(line)
		{
		}

		ULONG_PTR m_address;
		uint32 m_line;
	};

	class Segment
	{
	public:
		CTOR Segment(ULONG_PTR startAddress = 0, ULONG_PTR endAddress = 0) : m_startAddress(startAddress), m_endAddress(endAddress)
		{
		}

		ULONG_PTR m_startAddress;
		ULONG_PTR m_endAddress;
	};

	CTOR SourceFile();
	~SourceFile();

	SourceFile* m_pParentFile;
	//std::vector<SourceFile*> sourceFiles;

	String m_filename;
//	std::vector<std::string> m_sourceLines;

	vector<Segment> m_segments;
	vector<SourceLine> m_lines;

	virtual uint GetSegmentCount();
	virtual void GetSegmentAddress(uint n, ULONG_PTR* pStartAddress, ULONG_PTR* pEndAddress);

	Object* m_userdata;

	/*
#if _WINDOWS
	std::vector<nlist*> m_stabvec;
	declmap m_stab;
#endif
	*/
};

class LFCEXT DebugSymbol : public Object
{
public:
	CTOR DebugSymbol(StringIn name, ULONG_PTR address) : m_name(name), m_address(address)
	{
	}

	ULONG_PTR m_address;
	String m_name;
};

typedef map<ULONG_PTR, DebugSymbol*> symbolmap_address_t;
typedef map<String, DebugSymbol*> symbolmap_name_t;

class ObjectFileParser;

interface IDebugInfoReceiver
{
	virtual NamedType*	LookupNamedType(StringIn name) abstract;
	virtual Type*		CreatePointerType(Type_type type, Type* pPointerTo) abstract;
	virtual void		OnSymbol(StringIn name, ULONG_PTR address, ULONG_PTR dwData) abstract;
	virtual void		OnType(StringIn name, NamedType* type, ULONG_PTR dwData) abstract;
	virtual Scope*		OnProc(Scope* pScope, StringIn name, Type* type, ULONG_PTR startAddress, ULONG_PTR endAddress, ULONG_PTR dwData) abstract;
	virtual Scope*		End(Scope* pScope) abstract;
	virtual void		OnData(StringIn name, Type* type, ULONG_PTR address, ULONG_PTR dwData) abstract;
	virtual String		CreateString(const char* str) abstract;
};

class LFCEXT DebugInfo : public Object
{
public:

	virtual DebugSymbol* LookupSymbol(ULONG_PTR address);
	virtual DebugSymbol* LookupSymbolByName(StringIn name);

	virtual Scope* GetScope() abstract;
	virtual int Parse(ObjectFileParser* pImage, IDebugInfoReceiver* receiver, ULONG_PTR dwData) abstract;

	/*
	virtual int GetSourceFiles() = 0;
	virtual SourceFile* GetSourceFile() = 0;
	virtual cpp::Scope* GetScope() = 0;
	*/

	symbolmap_address_t m_symbols;
	symbolmap_name_t m_symbols_name;
	vector<SourceFile*> m_sourceFiles;
};

class LFCEXT SourceLocation : public Object
{
public:
	CTOR SourceLocation() : m_file(NULL)
	{
	}

	SourceFile* m_file;
	int m_line;
};

}	// System

#endif // System_Debug_h
