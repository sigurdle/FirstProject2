#ifndef __db_h__
#define __db_h__

//#include "../LFC/BufferManager.h"
//#include "LFC/Variant.h"

namespace System
{
namespace sql
{

namespace ast
{
class Stm;
class SelectStm;
class InsertStm;
class TableDefStm;
}

class IRecord;
class IField;

class Record;

class TableFieldType
{
public:

	enum Kind
	{
		FTyp_Byte = 1,
		FTyp_Short = 2,
		FTyp_Long = 3,
		FTyp_Double = 4,
		FTyp_ShortDate = 5,
		FTyp_Char,
		FTyp_CharVarying,
		FTyp_VarChar,
	//	FTyp_VarString = 10 | 512,
	//	FTyp_VarWString = 11 | 512,
		FTyp_VarBinary = 12 | 512,

		// XML Types
		FTyp_XML_Sequence,

		FTyp_XML_DocumentAny,
		FTyp_XML_DocumentUntyped,
		FTyp_XML_DocumentXMLSchema,

		FTyp_XML_ContentAny,
		FTyp_XML_ContentUntyped,
		FTyp_XML_ContentXMLSchema,
	};

	Kind m_kind;
	unsigned int m_length;
};

class FieldOptions
{
public:
	bool m_identity;
	bool m_sequenceGenerate;
	LONGLONG m_startWith;
	LONGLONG m_incrementBy;
	LONGLONG m_maxValue;
};

class IFieldDef
{
public:
	virtual TableFieldType GetType() = 0;
	virtual String GetName() = 0;
	virtual FieldOptions GetOptions() = 0;
};

class ITable
{
public:

//	virtual ULONG AddRef() = 0;
//	virtual ULONG Release() = 0;

	virtual unsigned int GetFieldCount() = 0;
	virtual int GetFieldIndex(StringIn name) = 0;
	virtual IFieldDef* GetField(unsigned int index) = 0;
	virtual IFieldDef* GetField(StringIn name) = 0;
	virtual IRecord* NewRecord() = 0;
	virtual IRecord* GetRecord(unsigned int index) = 0;
	virtual IRecord* Begin() = 0;
	virtual IRecord* End() = 0;
	virtual unsigned int GetCount() = 0;
	virtual void AddField(StringIn name, TableFieldType type, const FieldOptions& options) = 0;
	virtual void Close() = 0;
	virtual void DeleteRecord(IRecord* pRecord) = 0;
};

class IField
{
public:
//	virtual ULONG AddRef() = 0;
//	virtual ULONG Release() = 0;

	virtual IFieldDef* GetDef() = 0;
	virtual Variant GetValue() = 0;
	virtual void SetValue(const Variant& v) = 0;
	virtual void SetData(const void* data, unsigned long length) = 0;
	virtual void SetString(StringIn str) = 0;
	virtual const uint8* GetData() = 0;
	virtual unsigned long GetSize() const = 0;
};

class IRecord
{
public:
//	virtual ULONG AddRef() = 0;
//	virtual ULONG Release() = 0;

	virtual unsigned int GetCount() = 0;
	virtual IField* GetField(unsigned int index) = 0;
	virtual IField* GetField(StringIn name) = 0;
	virtual IRecord* Next() = 0;
	virtual IRecord* Prev() = 0;

	virtual void Write() = 0;
};

class IDatabase
{
public:
//	virtual ULONG AddRef() = 0;
//	virtual ULONG Release() = 0;

	virtual ITable* NewTable(StringIn name) = 0;
	virtual ITable* GetTable(unsigned int index) = 0;
	virtual ITable* GetTable(StringIn name) = 0;

//	virtual void CreateTable(ast::TableDefStm* stm) = 0;
};

/*
class IRecordPtr
{
public:

	virtual ULONG AddRef() = 0;
	virtual ULONG Release() = 0;
	virtual void Next() = 0;
	virtual void Prev() = 0;
	virtual IRecord* GetRecord() = 0;
	virtual ITable* GetTable() = 0;
};
*/

class SQLEXT Field
{
public:

	CTOR Field();
	CTOR Field(const Field& other);
	~Field();

	IFieldDef* GetDef()
	{
		return m_p->GetDef();
	}

	System::Variant GetValue()
	{
		return m_p->GetValue();
	}

	String GetString() const;

	void SetValue(const Variant& v)
	{
		m_p->SetValue(v);
	}
	void SetData(const void* data, unsigned long length)
	{
		m_p->SetData(data, length);
	}
	void SetString(StringIn str)
	{
		m_p->SetString(str);
	}
	/*
	void SetData(System::StringA* str)
	{
		m_p->SetData(str->c_str(), str->Length());
	}
	*/
	const uint8* GetData()
	{
		return m_p->GetData();
	}
	unsigned long GetSize() const
	{
		return m_p->GetSize();
	}

	Field& operator = (const Field& other);

protected:

	Field(IField* p)
	{
		m_p = p;

		/*
		if (m_p)
		{
			m_p->AddRef();
		}
		*/
	}

	IField* m_p;

	friend class Record;
};

class SQLEXT FieldCollection
{
public:

	unsigned int Length() const;
	Field operator [] (unsigned int index);
	Field operator [] (StringIn name);
//	long GetFieldIndex(const sysstring& name);

protected:

	CTOR FieldCollection(Record* ownerRecord)
	{
		m_ownerRecord = ownerRecord;
	}

	Record* m_ownerRecord;

	friend class Record;
};

class SQLEXT Record
{
public:

	CTOR Record() : m_fields(this)
	{
		m_p = NULL;
	}

	FieldCollection m_fields;

	CTOR Record(const Record& other);
	~Record();

	FieldCollection get_Fields()
	{
		return m_fields;
	}

	void Update()
	{
		m_p->Write();
	}

	Record operator ++(int)	// postfix
	{
#ifndef __LERSTAD__
		Record old(m_p);
#endif
		m_p = m_p->Next();
	//	old.m_p->Release();
		return old;
	}

	Record operator --(int)	// postfix
	{
#ifndef __LERSTAD__
		Record old(m_p);
#endif
		m_p = m_p->Prev();
	//	old.m_p->Release();
		return old;
	}

	Field operator [] (StringIn name);
	Field operator [] (unsigned int index);
	const Field operator [] (StringIn name) const;
	const Field operator [] (unsigned int index) const;

protected:

	Field GetField(unsigned int index);
	Field GetField(StringIn name);
	unsigned int GetFieldCount();

	IRecord* m_p;

	CTOR Record(IRecord* p) : m_fields(this)
	{
		m_p = p;

		/*
		if (m_p)
		{
			m_p->AddRef();
		}
		*/
	}

	friend class Table;
	friend class FieldCollection;
};

/*
class LFCEXT RecordPtr
{
public:
	RecordPtr(const RecordPtr& other)
	{
		m_p = other.m_p;
		m_p->AddRef();
	}

	~RecordPtr()
	{
		m_p->Release();
	}

	RecordPtr operator [] (long index)
	{
		return RecordPtr(m_p->GetTable()->GetRecord(index));
	}

	RecordPtr operator ++(int)	// postfix
	{
		RecordPtr old(*this);
		m_p->Next();
		return old;
	}

	RecordPtr operator --(int)	// postfix
	{
		RecordPtr old(*this);
		m_p->Prev();
		return old;
	}

	Record operator * ()
	{
		return Record(m_p->GetRecord());
	}

protected:

	RecordPtr(IRecordPtr* p)
	{
		m_p = p;
		m_p->AddRef();
	}

	IRecordPtr* m_p;

	friend class Table;
};
*/

class SQLEXT Table
{
public:
	CTOR Table();
	CTOR Table(ITable* pTable);
	CTOR Table(const Table& other);
	~Table();

	void AddField(StringIn name, TableFieldType type, const FieldOptions& options)
	{
		m_p->AddField(name, type, options);
	}

	long GetCount() const
	{
		return m_p->GetCount();
	}

	virtual long GetFieldCount()
	{
		return m_p->GetFieldCount();
	}

	Record NewRecord()
	{
		return Record(m_p->NewRecord());
	}

	void DeleteRecord(Record record);

	Record operator [] (unsigned int index)
	{
		return Record(m_p->GetRecord(index));
	}

	int GetFieldIndex(StringIn name)
	{
		return m_p->GetFieldIndex(name);
	}

	virtual IFieldDef* GetField(unsigned int index)
	{
		return m_p->GetField(index);
	}
	virtual IFieldDef* GetField(StringIn name)
	{
		return m_p->GetField(name);
	}

	Record Begin()
	{
		return Record(m_p->Begin());
	}

	Record End()
	{
		return Record(m_p->End());
	}

	void Close()
	{
		m_p->Close();
	}

	Table& operator = (const Table& other);

	bool operator == (const Table& other) const
	{
		return m_p == other.m_p;
	}

	bool operator != (const Table& other) const
	{
		return !(*this == other);
	}

protected:

	ITable* m_p;
};

class _Command;

class SQLEXT Command
{
public:

	CTOR Command();
	CTOR Command(const char* command);
	~Command();

protected:

	_Command* m_p;
};

class SQLEXT Database
{
public:
	CTOR Database();
	CTOR Database(const char* name, const char* access);
	~Database();

	Table NewTable(StringIn name)
	{
		return Table(m_p->NewTable(name));
	}

	Table GetTable(long index)
	{
		return Table(m_p->GetTable(index));
	}

	Table GetTable(StringIn name)
	{
		return Table(m_p->GetTable(name));
	}

	Table Execute(const char* command);
	Table Execute(sql::Command* command);

protected:

	ITable* Execute_SELECT(ast::SelectStm* stm);
	void Execute_TABLEDEF(ast::TableDefStm* stm);
	void Execute_INSERT(ast::InsertStm* stm);

	IDatabase* m_p;
};

}
}

#endif // __db_h__
