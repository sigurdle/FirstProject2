#ifndef TypeArchive_h
#define TypeArchive_h

namespace System
{

class TypeLib;
class Namespace;
class TypeSerializable;
class Declarator;
class CppSourceFile;
class FilePart;

class LFCEXT TypeStuff : public Object
{
public:

//	FilePart* GetFilePart(StringIn parentname);

	typedef map<String, TypeLib*> typelibs;
	typelibs m_typelibs;
	map<String, TypeLib*> m_typelibs_fullpath;

	map<String, CppSourceFile*> m_sourcefiles;

	map<String, FilePart*> m_files;	// full path
	multimap<String, FilePart*> m_fileparts;	// parts

//	typedef map<StringA*, TypeLib*, Ref_Less<StringA> > typelibs;
//	typelibs m_typelibs;
};

class LFCEXT TypeArchive : public Object
{
public:

	enum Mode
	{
		Mode_Load,
		Mode_Store,
	};

	CTOR TypeArchive(Mode mode, StringIn pathname);
	CTOR TypeArchive(Mode mode, IO::Stream* stream, StringIn pathname);

	~TypeArchive();

	inline TypeArchive& operator >> (bool& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (bool value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (char& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (char value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (signed char& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (signed char value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (unsigned char& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (unsigned char value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (short& value)
	{
		m_p2 >> value;
	//	Read(&value, 2);
	//	value = BigEndian16(value);
		return *this;
	}

	inline TypeArchive& operator << (short value)
	{
	//	value = BigEndian16(value);
	//	Write(&value, 2);
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (unsigned short& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (unsigned short value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (int& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (int value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (unsigned int& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (unsigned int value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (long& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (long value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (unsigned long& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (unsigned long value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (int64& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator >> (uint64& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (int64 value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator << (uint64 value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (float& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (float value)
	{
		m_p << value;
		return *this;
	}

	inline TypeArchive& operator >> (double& value)
	{
		m_p2 >> value;
		return *this;
	}

	inline TypeArchive& operator << (double value)
	{
		m_p << value;
		return *this;
	}

	TypeArchive& operator >> (String& value);
	TypeArchive& operator << (const String& value);

//	TypeArchive& operator >> (StringW& value);
//	TypeArchive& operator << (const StringW& value);

	/*
	TypeArchive& operator >> (StringW & value);
	TypeArchive& operator << (StringW value);
	*/

	TypeArchive& operator >> (TypeSerializable* & object);
	TypeArchive& operator << (const TypeSerializable* object);

	TypeArchive& operator >> (Declarator* & object);
	TypeArchive& operator << (const Declarator* object);

	TypeArchive& operator >> (CppSourceFile* & object);
	TypeArchive& operator << (CppSourceFile* object);

	TypeArchive& operator >> (FilePart* & object);
	TypeArchive& operator << (const FilePart* object);

	void MapObject(TypeSerializable* object);
	void MapObject(const TypeSerializable* object);

	void MapObject(const Declarator* object);
	void MapObject(Declarator* object);

	void MapObject(CppSourceFile* object);
//	void MapObject(CppSourceFile* object);

	void MapObject(const FilePart* object);
	void MapObject(FilePart* object);

//	void Read(void* data, size_t count);
//	void Write(const void* data, size_t count);

	inline bool IsLoading() const
	{
		return !m_bIsStoring;
	}

	inline bool IsStoring() const
	{
		return m_bIsStoring;
	}

	inline IO::BinaryWriter& GetStream()
	{
		return m_p;
	}

	TypeSerializable* CreateType(uint8 classtype, TypeLib* typelib, StringIn qname, uint32 id);

	void StoreIdentifier(StringIn str);
	String LoadIdentifier();

	Namespace* m_pGlobalNamespace;
	bool m_bSortedDecls;

	TypeStuff* m_typestuff;
	TypeLib* m_typelib;

	void ReadHeader();
	void WriteHeader();

	StringVariant m_pathname;
//	uint32 m_id;
	uint32 m_crc;

public://protected:

	void Init();

	friend class NamedType;
	friend class EnumType;
	friend class Typedef;
	friend class ClassType;
	friend class Namespace;
	friend class TypeLib;

//	vector<NamedType*> m_namedTypes;

//	IO::Stream m_p;

	_Ptr<IO::BinaryWriter> m_p;
	_Ptr<IO::BinaryReader> m_p2;

	map<const TypeSerializable*, uint32> m_typeSave;
	vector<TypeSerializable*> m_typeLoad;

	map<const Declarator*, uint32> m_declSave;
	vector<Declarator*> m_declLoad;

	map<CppSourceFile*, uint32> m_objectSave;
	vector<CppSourceFile*> m_objectLoad;

	map<const FilePart*, uint32> m_filepartSave;
	vector<FilePart*> m_filepartLoad;

	map<String, uint32> m_stringSave;
	vector<String> m_stringLoad;

	bool m_bIsStoring;

protected:

	void UpdateCRC(const void* data, size_t length);

private:

	CTOR TypeArchive(const TypeArchive&);
	TypeArchive& operator = (const TypeArchive&);
};

}	// System

#endif // TypeArchive_h
