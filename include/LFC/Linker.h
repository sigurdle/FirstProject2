#ifndef System_Linker_h
#define System_Linker_h

namespace System
{

class ObjectFileParser;

class OFile2;
class GlobalSymbol;

class Symbol : public Object
{
public:
	CTOR Symbol()
	{
		m_globsym = NULL;
		ResolvedValue = 0;
		m_pIndirect = NULL;
	}

	OFile2* m_pOFile;
	GlobalSymbol* m_globsym;
	long ResolvedValue;
	Symbol* m_pIndirect;
};

class OFile : public Object
{
public:
	uint8* m_textdata;
	ULONG m_textsize;

	uint8* m_datadata;
	ULONG m_datasize;

	uint8* m_bssdata;
	ULONG m_bsssize;
};

class LFCEXT OFile2 : public System::Object
{
public:
	CTOR OFile2()
	{
		m_file = NULL;
		m_pLoaded = NULL;
		m_bloadedSymbols = false;
	}

	OFile* m_pLoaded;
	bool m_bloadedSymbols;

	vector<Symbol*> m_symbols;

	System::StringA* m_afilename;
	System::StringA* m_ofilename;
	System::IO::ISequentialByteStream* m_file;
};

class LFCEXT GlobalSymbol : public System::Object
{
public:
	CTOR GlobalSymbol()
	{
	//	m_pIndirect = NULL;

	//	m_pOFile = NULL;

		m_word = NULL;

		Value = 0;
		setResolvedValue = 0;

		m_defined = false;
	}

//	char* importDLL;
//	int ordinalHint;
//	char* publicName;

	System::StringA* m_name;

#if 0
	GlobalSymbol* m_pIndirect;
#endif

//	uint16 n_type;

	long Value;

	ULONG setResolvedValue;
	ULONG* m_word;

//	nlist* refs;
//	std::vector<DWORD> refs;

//	std::string m_filename;
//	ULONG m_fileoffset;
	//template class LFCEXT ::vector<Symbol*>;
	vector<Symbol*> m_syms;

	char m_defined;
};

typedef map<String, GlobalSymbol*> gsymmap_t;

/*
class SetSymbol
{
public:
	SetSymbol()
	{
		ResolvedAddress = 0;
	}

	unsigned char   n_type;
	unsigned long   n_value;
	ISequentialByteStream* m_file;
	ULONG ResolvedAddress;
};
*/

typedef map<GlobalSymbol* /*the SETV symbol*/, vector<Symbol*> /* the SET[ATDB] symbols*/> symsetmap_t;

class LFCEXT Linker
{
public:

	CTOR Linker()
	{
		m_undefinedReferenceCount = 0;
	}

	void pass1();

	void Pass1_ObjectFile(OFile2* ofile);

	OFile2* Pass1_ObjectFile(System::StringA* afilename, System::StringA* ofilename, System::IO::ISequentialByteStream* file);

	void LoadObjectFile(OFile2* ofile);
	void Relocate(int nsection, const char* sectionname, ObjectFileParser* parser, OFile2* pOFile2);

	OFile* LoadObjectFile2(OFile2* ofile);
	void Relocate2(int nsection, const char* sectionname, uint8* data, ObjectFileParser* parser, OFile2* pOFile2, OFile* pOFile);

	void sets();

	void AddSymbol(StringA* symname, ULONG Value);

public:

	uint8* m_textdata;
	ULONG m_textsize;

	ULONG m_undefinedReferenceCount;
	vector<System::StringA*> m_files;
	gsymmap_t m_globsyms;

	symsetmap_t m_symbolSets;

	vector<OFile2*> m_loadedObjectFiles;
	vector<OFile2*> m_objectFiles;
};

}	// System

#endif // System_Linker_h
