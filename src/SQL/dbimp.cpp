#include "stdafx.h"
#include "SQL.h"
#include "dbimp.h"

#include "sql_a.h"

//#include "../XPath/XPath.h"

namespace System
{
namespace sql
{

class Db;

class DbField : public IField
{
public:
	DbField(DbFieldDef* def, DbTable* pTable) : m_refcount(0)
	{
	//	buffer = NULL;

		m_def = def;
		m_pTable = pTable;
	}

	DbFieldDef* m_def;
	DbTable* m_pTable;

	virtual IFieldDef* GetDef();

	union
	{
		char int8_val;
		short int16_val;
		long int32_val;
		__int64 int64_val;
		float float32_val;
		double float64_val;

		struct
		{
			__int64 offset;
			unsigned long size;
		}
		varsize;
	}
	u;

	ULONG m_refcount;

	ULONG AddRef()
	{
		return ++m_refcount;
	}

	ULONG Release()
	{
		ASSERT(m_refcount > 0);
		--m_refcount;
		if (m_refcount == 0)
		{
			delete this;
			return 0;
		}
		return m_refcount;
	}

	Variant GetValue() override;

	virtual void SetValue(const Variant& v) override
	{
		u.int32_val = v.u.int32_val;
	}

	virtual void SetString(StringIn str) override
	{
		ASSERT(0);
	}

	void SetData(const void* data, unsigned long length) override;

	const uint8* GetData() override;

	unsigned long GetSize() const override
	{
		return u.varsize.size;
	}

	void Write(Stream& stream);
	void Read(Stream& stream);

protected:

//	IBuffer* buffer;
};

class DbRecord : public IRecord
{
public:
	DbRecord(DbTable* pTable) : m_refcount(0)
	{
		m_pTable = pTable;
		m_flags = 0;
	}

	ULONG m_refcount;

	ULONG AddRef()
	{
		m_refcount++;
		/*
		if (m_refcount == 1)
		{
			m_fields = new DbField*[m_pTable->m_fields.size()];

			for (int i = 0; i < m_pTable->m_fields.size(); i++)
			{
				m_fields[i] = new DbField(m_pTable->m_fields[i], m_pTable);
				m_fields[i]->AddRef();
			}
		}
		*/

		return m_refcount;
	}

	ULONG Release();

	virtual IRecord* Next();
	virtual IRecord* Prev();

	virtual unsigned int GetCount();

	virtual IField* GetField(unsigned int index);
	virtual IField* GetField(StringIn name);

	virtual void Write();

	uint32 m_flags;
	uint32 m_index;
	DbTable* m_pTable;
	DbField** m_fields;
};

class DbFieldDef : public Object, public IFieldDef
{
public:

	virtual String GetName()
	{
		return m_name;
	}

	virtual TableFieldType GetType()
	{
		return m_type;
	}

	virtual FieldOptions GetOptions()
	{
		return m_options;
	}

	String m_name;
	TableFieldType m_type;
	FieldOptions m_options;
};

class DbTable : public Object, public ITable
{
public:
	DbTable(Db* db) : m_refcount(0)
	{
		m_db = db;
	}

	ULONG AddRef()
	{
		m_refcount++;
		return m_refcount;
	}

	ULONG Release()
	{
		ASSERT(m_refcount > 0);
		m_refcount--;
		if (m_refcount == 0)
		{
			delete this;
			return 0;
		}
		return m_refcount;
	}

	void Create();
	void Open();

	virtual void Close();

	virtual void DeleteRecord(IRecord* pRecord);

	unsigned int GetFieldCount()
	{
		return m_fields.GetSize();
	}

	virtual IFieldDef* GetField(unsigned int index)
	{
		if (index < m_fields.size())
		{
			return m_fields[index];
		}
		else
		{
			return NULL;
		}
	}

	virtual int GetFieldIndex(StringIn name)
	{
		return m_fieldsmap[name]-1;
	}

	virtual IFieldDef* GetField(StringIn name)
	{
		int index = m_fieldsmap[name]-1;
		if (index == -1)
			return NULL;
		return m_fields[index];
	}

	virtual void AddField(StringIn name, TableFieldType type, const FieldOptions& options)
	{
		DbFieldDef* pField = new DbFieldDef;
	//	pField->AddRef();

		pField->m_name = name;
		pField->m_type = type;
		pField->m_options = options;

		m_fields.Add(pField);
		m_fieldsmap[name] = m_fields.GetSize();

		UpdateRecordSize();
	}

	virtual unsigned int GetCount();

	virtual IRecord* NewRecord();

	virtual IRecord* Begin();
	virtual IRecord* End();
	virtual IRecord* GetRecord(unsigned int index);

	vector<DbFieldDef*> m_fields;
	map<String, int> m_fieldsmap;

protected:

	friend DbField;
	friend DbRecord;

	void UpdateRecordSize();

	ULONG m_recordSize;

	vector<DbRecord*> m_rows;

	ULONG m_refcount;

	String m_name;

//	std::string m_filename;
//	std::string m_mode;

//	Buffer* fp0;
	File* sh1;
	File* fp1;
	//Buffer* fp2;

	Db* m_db;

	friend class Db;
};

class Db : public Object, public IDatabase
{
public:
	Db()// : m_refcount(0)
	{
#if 0
		m_bufferManager = NULL;
#endif
	}

	void Open(const char* filename, const char* mode);

	/*
	ULONG AddRef()
	{
		return Object::AddRef();
	}

	ULONG Release()
	{
		return _Object::Release();
	}
	*/

	virtual ITable* NewTable(StringIn name);

	virtual ITable* GetTable(long index);

	virtual ITable* GetTable(StringIn name)
	{
		int index = m_tablesmap[name]-1;
		if (index == -1)
			return NULL;

		return GetTable(index);
	}

#if 0
	IBufferManager* m_bufferManager;
	BufferStream* m_sysStream;
	File* m_sysFile;
#endif

	String m_filename;
	String m_mode;

	vector<DbTable*> m_tables;
	map<String,int> m_tablesmap;

	//ULONG m_refcount;

};

///////////////////////////////////////
// 2

class Db2Table;

class Db2FieldDef : public Object, public IFieldDef
{
public:
	Db2FieldDef()
	{
		m_sequenceNumber = 1;
		m_incrementBy = 1;
	}

	virtual String GetName()
	{
		return m_name;
	}

	virtual TableFieldType GetType()
	{
		return m_type;
	}

	virtual FieldOptions GetOptions()
	{
		return m_options;
	}

	String m_name;
	TableFieldType m_type;
	FieldOptions m_options;
	LONGLONG m_sequenceNumber;
	LONGLONG m_incrementBy;
};

class Db2Field : public IField
{
public:
	Db2Field(Db2FieldDef* def, Db2Table* pTable) : m_refcount(0)
	{
	//	buffer = NULL;

		m_def = def;
		m_pTable = pTable;

		m_string = NULL;
		m_xmlNodeList = NULL;
	}

	Db2FieldDef* m_def;
	Db2Table* m_pTable;

	virtual IFieldDef* GetDef()
	{
		return m_def;
	}

	union
	{
		char int8_val;
		short int16_val;
		long int32_val;
		__int64 int64_val;
		float float32_val;
		double float64_val;

		/*
		struct
		{
			__int64 offset;
			unsigned long size;
		}
		varsize;
		*/
	}
	u;

	String m_string;
	XPath::DataList* m_xmlNodeList;

	ULONG m_refcount;

	ULONG AddRef()
	{
		m_refcount++;
		return m_refcount;
	}

	ULONG Release()
	{
		ASSERT(m_refcount > 0);
		m_refcount--;
		if (m_refcount == 0)
		{
			delete this;
			return 0;
		}
		return m_refcount;
	}

	Variant GetValue();

	virtual void SetValue(const Variant& v)
	{
		switch (v.kind)
		{
		case VARKIND_STRINGW:
			m_string = (StringObject*)v.m_pObject;
			break;

		case VARKIND_INT32:
			u.int32_val = v.u.int32_val;
			break;

		default:
			ASSERT(0);
			//u.int32_val = v.u.int32_val;
		}
	}

	void SetString(StringIn str)
	{
		ASSERT(0);
	}

	void SetData(const void* data, unsigned long length)
	{
		ASSERT(0);
	}

	const uint8* GetData()
	{
		ASSERT(0);
		return NULL;
	}

	unsigned long GetSize() const
	{
		return 0;//u.varsize.size;
	}

//	void Write(BufferStream& stream);
//	void Read(BufferStream& stream);

protected:

//	IBuffer* buffer;
};

Variant Db2Field::GetValue()
{
	switch (m_def->m_type.m_kind)
	{
	case TableFieldType::FTyp_Long:
	case TableFieldType::FTyp_ShortDate:
		return Variant(u.int32_val);

	case TableFieldType::FTyp_Char:
		return Variant(m_string);//(char*)GetData(), GetSize());

		/*
	case TableFieldType::FTyp_VarChar:
		return Variant((char*)GetData(), GetSize());
		*/
	default:
		ASSERT(0);
	}

	return Variant();
}

class Db2Record : public IRecord
{
public:
	Db2Record(Db2Table* pTable) : m_refcount(0)
	{
		m_pTable = pTable;
		m_flags = 0;
	}

	ULONG m_refcount;

	ULONG AddRef()
	{
		m_refcount++;
		/*
		if (m_refcount == 1)
		{
			m_fields = new DbField*[m_pTable->m_fields.size()];

			for (int i = 0; i < m_pTable->m_fields.size(); i++)
			{
				m_fields[i] = new DbField(m_pTable->m_fields[i], m_pTable);
				m_fields[i]->AddRef();
			}
		}
		*/

		return m_refcount;
	}

	ULONG Release();

	virtual IRecord* Next();
	virtual IRecord* Prev();

	virtual unsigned int GetCount();

	virtual IField* GetField(unsigned int index);
	virtual IField* GetField(StringIn name);

	virtual void Write();

	uint32 m_flags;
	uint32 m_index;
	Db2Table* m_pTable;
	Db2Field** m_fields;
};

class Db2Table : public ITable
{
public:
	virtual unsigned int GetFieldCount()
	{
		return m_fields.GetSize();
	}

	virtual int GetFieldIndex(StringIn name)
	{
		map<String, int>::iterator it = m_fieldsmap.find(name);
		if (it == m_fieldsmap.end())
			return -1;

		return (*it).second;
	}

	virtual IFieldDef* GetField(unsigned int index)
	{
		if (index < m_fields.size())
		{
			return m_fields[index];
		}
		else
		{
			return NULL;
		}
	}

	virtual IFieldDef* GetField(StringIn name)
	{
		map<String, int>::iterator it = m_fieldsmap.find(name);
		if (it == m_fieldsmap.end())
			return NULL;

		return m_fields[it->second];
	}

	virtual IRecord* NewRecord()
	{
		Db2Record* pRecord = new Db2Record(this);
		pRecord->AddRef();

		pRecord->m_fields = new Db2Field*[m_fields.GetSize()];

		//fseek(fp1, index * m_recordSize, SEEK_SET);

		//	Ptr<char*> ptr(fp1) + index * m_recordSize;

		for (int i = 0; i < m_fields.size(); i++)
		{
			pRecord->m_fields[i] = new Db2Field(m_fields[i], this);
			pRecord->m_fields[i]->AddRef();

			if (m_fields[i]->m_options.m_identity)
			{
				pRecord->m_fields[i]->SetValue((int)m_fields[i]->m_sequenceNumber);
				m_fields[i]->m_sequenceNumber += m_fields[i]->m_incrementBy;
			}
		}

		pRecord->m_index = m_rows.GetSize();
		m_rows.Add(pRecord);

		return pRecord;
	}

	virtual IRecord* GetRecord(unsigned int index)
	{
		return m_rows[index];
	}

	virtual IRecord* Begin()
	{
		return m_rows[0];
	}

	virtual IRecord* End()
	{
		return NULL;//m_rows[m_row.size()-1];
	}

	virtual unsigned int GetCount()
	{
		return m_rows.size();
	}

	virtual void AddField(StringIn name, TableFieldType type, const FieldOptions& options)
	{
		Db2FieldDef* def = new Db2FieldDef;
		def->m_name = name;
		def->m_type = type;
		def->m_options = options;

		def->m_sequenceNumber = options.m_startWith;
		def->m_incrementBy = options.m_incrementBy;

		m_fieldsmap[name] = m_fields.size();
		m_fields.push_back(def);
	}

	virtual void Close()
	{
		return;
	}

	virtual void DeleteRecord(IRecord* pRecord)
	{
		return;
	}

	String m_name;
	vector<Db2FieldDef*> m_fields;
	map<String, int> m_fieldsmap;

	vector<Db2Record*> m_rows;
};

class Db2 : public Object, public IDatabase
{
public:
	Db2()// : m_refcount(0)
	{
	}

	void Open(const char* filename, const char* mode)
	{
	}

	/*
	ULONG AddRef()
	{
		return Object::AddRef();
	}

	ULONG Release()
	{
		return _Object::Release();
	}
	*/

	virtual ITable* NewTable(StringIn name)
	{
		Db2Table* table = new Db2Table;
		table->m_name = name;

		m_tables.push_back(table);
		m_tablesmap[name] = m_tables.size();

		return table;
	}

	virtual ITable* GetTable(unsigned int index)
	{
		return m_tables[index];
	}

	virtual ITable* GetTable(StringIn name)
	{
		int index = m_tablesmap[name]-1;
		if (index == -1)
			return NULL;

		return GetTable(index);
	}

#if 0
	virtual void CreateTable(ast::TableDefStm* stm)
	{
		//fwrite(m_tablesfp

		Db2Table* table = new Db2Table;
		table->m_name = stm->m_name;

		ast::TableElementList* elemlist = stm->m_elementList;
		while (elemlist)
		{
			ast::ColumnDef* columndef = elemlist->head;

		//	fwrite(
			Db2FieldDef* fdef = new Db2FieldDef;
			fdef->m_name = columndef->m_name;
			fdef->m_type = columndef->m_dataType->GetKind();

			table->m_fields.push_back(fdef);

			elemlist = elemlist->tail;
		}

		{
			char tablename[600];
			sprintf(tablename, "C:/mmstudio/database/%s.schema", stm->m_name->ToStringA()->c_str());

			FILE* fp = fopen(tablename, "wb");

			for (int i = 0; i < table->m_fields.size(); i++)
			{
				WCHAR name[128] = {0};
				wcscpy(name, table->m_fields[i]->m_name->c_str());

				fwrite(name, 128, 2, fp);
			}

			fclose(fp);
		}

		{
			char tablename[600];
			sprintf(tablename, "C:/mmstudio/database/%s.rows", stm->m_name->ToStringA()->c_str());

			FILE* fp = fopen(tablename, "wb");
			fclose(fp);
		}
	}
#endif

//	IBufferManager* m_bufferManager;
//	BufferStream* m_sysStream;

	FILE* m_tablesfp;

	String m_filename;
	String m_mode;

	vector<Db2Table*> m_tables;
	map<String,int> m_tablesmap;

	//ULONG m_refcount;

	//File* m_sysFile;
};

///////////////////////////////////////////////////////////////
// DbTable

void DbTable::UpdateRecordSize()
{
	m_recordSize = 0;

	for (int i = 0; i < m_fields.GetSize(); i++)
	{
		DbFieldDef* pField = m_fields[i];

		TableFieldType ftype = pField->GetType();

		if (ftype.m_kind & 512)
		{
			m_recordSize += 12;
		}
		else
			m_recordSize += 4;
	}
}

void DbTable::Create()
{

#if 0
	sh1 = new File;
	sh1->Create(m_db->m_bufferManager->AllocateBuffer(0));

	fp1 = new File;
	fp1->Create(m_db->m_bufferManager->AllocateBuffer(0));
#endif
}

void DbTable::Open()
{
	ASSERT(0);
#if 0
//	if (m_mode.find('r') != -1)
	{
//		std::string fname = std::string(filename) + "_sh";

//		FILE* fp = fopen(fname.c_str(), "rb");
//		if (fp)
		{
			// TODO
			StringStream stream;//(sh1);

			long count;
			stream >> count;
			//if (fread(&count, 1, 4, fp) != 4) THROW(-1);
			for (int i = 0; i < count; i++)
			{
				TableFieldType ftype;
			//	ASSERT(sizeof(TableFieldType) == 4);
				stream >> (int&)ftype.m_kind;
				stream >> ftype.m_length;
			//	if (fread(&ftype, 1, 4, fp) != 4) THROW(-1);

				/*
				if (ftype & 512)
				{
					m_recordSize += 12;
				}
				else
					m_recordSize += 4;
					*/

				String name;
				stream >> name;

				FieldOptions options;
				AddField(name, ftype, options);
			}
		//	fclose(fp);
		}

		/*
		BufferStream stream(m_bufferManager->GetSysBuffer());

		ULONGLONG id;
		stream >> id;

		fp1 = new File;
		fp1->Open(m_bufferManager->OpenBuffer(id));
		*/
	}
#if 0
	else
	{

	/*
	std::string n0 = std::string(filename) + "_flg";
	std::string n1 = std::string(filename) + "_idx";
	std::string n2 = std::string(filename) + "_var";
	*/

		m_sysStream = new BufferStream(m_bufferManager->GetSysBuffer());

		fp1 = new File;
		fp1->Create(m_bufferManager->AllocateBuffer(0));

		*m_sysStream << fp1->GetIdentity();
	//	BufferStream stream(m_sysBuffer);
	//	stream << fp1->GetIdentity();
	}

	/*
	fp0 = fopen(n0.c_str(), mode);

	fp1 = fopen(n1.c_str(), mode);
*/
#endif

//	if (m_db->m_mode.find('r') != -1)
	{
		ULONGLONG size = fp1->GetSize();

		int nrecords = size / m_recordSize;

		ASSERT((size / m_recordSize)*m_recordSize == size);

		for (int i = 0; i < nrecords; i++)
		{
			DbRecord* pRecord = new DbRecord(this);
			pRecord->m_index = i;

			m_rows.Add(pRecord);
		}
	}

//	fp2 = fopen(n2.c_str(), mode);
#endif
}

unsigned int DbTable::GetCount()
{
	return m_rows.GetSize();
	/*
	fseek(fp1, 0, SEEK_END);
	long size = ftell(fp1);
	rewind(fp1);

	ASSERT((size / m_recordSize)*m_recordSize == size);

	return size / m_recordSize;
	*/
}

void DbTable::Close()
{
	ASSERT(0);
#if 0
	if (m_db->m_mode.find('a') != -1)
	{
		//std::string fname = std::string(m_filename) + "_sh";

		//FILE* fp = fopen(fname.c_str(), "wb");

		BufferStream stream(sh1);

		long count = m_fields.GetSize();
		//fwrite(&count, 1, 4, fp);
		stream << count;
		for (int i = 0; i < count; i++)
		{
			//fwrite(&m_fields[i]->m_type, 4, 1, fp);
			stream << m_fields[i]->m_type;

			/*
			long size = m_fields[i]->m_name.length();
			stream << size;
			stream.Write(m_fields[i]->m_name.c_str(), size*2);
			*/
			stream << m_fields[i]->m_name;

		//	fwrite(&size, 1, 4, fp);
		//	fwrite(m_fields[i]->m_name.c_str(), 1, size*2, fp);
		}
		//fclose(fp);
	}

	fp1->Close();
//	fp2->Close();
#endif
}

IRecord* DbTable::NewRecord()
{
	DbRecord* pRecord = new DbRecord(this);
	pRecord->AddRef();

	pRecord->m_fields = new DbField*[m_fields.GetSize()];

	//fseek(fp1, index * m_recordSize, SEEK_SET);

	//	Ptr<char*> ptr(fp1) + index * m_recordSize;

	for (int i = 0; i < m_fields.GetSize(); i++)
	{
		pRecord->m_fields[i] = new DbField(m_fields[i], this);
		pRecord->m_fields[i]->AddRef();
	}

	pRecord->m_index = m_rows.GetSize();
	m_rows.Add(pRecord);

	return pRecord;
}

IRecord* DbTable::Begin()
{
	ASSERT(0);
	return NULL;
}

IRecord* DbTable::End()
{
	ASSERT(0);
	return NULL;
}

void DbTable::DeleteRecord(IRecord* _pRecord)
{
	DbRecord* pRecord = dynamic_cast<DbRecord*>(_pRecord);
	if (pRecord == NULL)
		THROW(-1);

	pRecord->m_flags |= 1;
}

IRecord* DbTable::GetRecord(unsigned int index)
{
	DbRecord* pRecord = m_rows[index];//new DbRecord(this);
	pRecord->AddRef();

	if (pRecord->m_refcount == 1)
	{
		pRecord->m_fields = new DbField*[m_fields.GetSize()];

		//fseek(fp1, index * m_recordSize, SEEK_SET);

		ASSERT(0);
#if 0

		BufferStream stream(fp1, m_recordSize * pRecord->m_index);

		for (int i = 0; i < m_fields.GetSize(); i++)
		{
			pRecord->m_fields[i] = new DbField(m_fields[i], this);
			pRecord->m_fields[i]->AddRef();

			pRecord->m_fields[i]->Read(stream);
		}
#endif
	}

	return pRecord;
}

/////////////////////////////////////////////////////////////
// DbField

#if 0
void DbField::Write(BufferStream& stream)
{
	if (m_def->m_type.m_kind & 512)	// varsize
	{
		stream << u.varsize.offset;
	//	*(Ptr<LONGLONG>)(ptr) = u.varsize.offset;
	//	ptr += 8;

		stream << u.varsize.size;
	//	*(Ptr<LONG>)(ptr) = u.varsize.offset;
	//	ptr += 4;

#if 0
		fwrite(&u.varsize.offset, 1, 8, m_table->fp1);
		fwrite(&u.varsize.size, 1, 4, m_table->fp1);
#endif
	}
	else if (m_def->m_type.m_kind == TableFieldType::FTyp_Long ||
				m_def->m_type.m_kind == TableFieldType::FTyp_ShortDate)
	{
		stream << u.int32_val;
#if 0
		fwrite(&u.int32, 1, 4, m_table->fp1);
#endif
	}
	else
		ASSERT(0);
}
#endif

Variant DbField::GetValue()
{
	switch (m_def->m_type.m_kind)
	{
	case TableFieldType::FTyp_Long:
	case TableFieldType::FTyp_ShortDate:
		return Variant(u.int32_val);

	case TableFieldType::FTyp_VarChar:
		return Variant((char*)GetData(), GetSize());
	}

	return Variant();
}

#if 0
void DbField::Read(BufferStream& stream)
{
	if (m_def->m_type.m_kind & 512)	// varsize
	{
		stream >> u.varsize.offset;
		stream >> u.varsize.size;

	//	if (fread(&u.varsize.offset, 1, 8, m_table->fp1) != 8) THROW(-1);
	//	if (fread(&u.varsize.size, 1, 4, m_table->fp1) != 4) THROW(-1);
	}
	else if (m_def->m_type.m_kind == TableFieldType::FTyp_Long ||
				m_def->m_type.m_kind == TableFieldType::FTyp_ShortDate)
	{
		stream >> u.int32_val;
		//fread(&u.int32, 1, 4, m_table->fp1);
	}
	else
		ASSERT(0);
}
#endif

const uint8* DbField::GetData()
{
	ASSERT(0);
	return NULL;
#if 0
	if (buffer == NULL)
	{
		buffer = m_pTable->m_db->m_bufferManager->OpenBuffer(u.varsize.offset);

	//	if (fseek(m_table->fp2, (unsigned long)u.varsize.offset, SEEK_SET) != 0) THROW(-1);
	//	if (fread(buffer, 1, u.varsize.size, m_table->fp2) != u.varsize.size) THROW(-1);
	}

	uint8* mem = (uint8*)myalloc(u.varsize.size, __FILE__, __LINE__);
	buffer->Read(mem, 0, u.varsize.size);

	return mem;
#endif
}

void DbField::SetData(const void* data, unsigned long length)
{
	/*
	if (buffer)
	{
		m_pTable->m_db->m_bufferManager->FreeBuffer(buffer);
	}
	*/
	ASSERT(0);
#if 0
	if (buffer == NULL)
	{
		buffer = m_pTable->m_db->m_bufferManager->AllocateBuffer(length);
	}

	buffer->Write(data, 0, length);

//	memcpy(Ptr<char>(buffer, 0), Ptr<char>(&MemBuffer(data, length), 0), length);
	u.varsize.offset = buffer->GetIdentity();
	u.varsize.size = length;
#endif

//	ASSERT(0);
#if 0

// Write it to disk here?
	u.varsize.offset = ftell(m_table->fp2);
	fwrite(buffer, 1, u.varsize.size, m_table->fp2);
#endif
}

IFieldDef* DbField::GetDef()
{
	return m_def;
}

////////////////////////////////////////////
// DbRecord

unsigned int DbRecord::GetCount()
{
	return m_pTable->m_fields.GetSize();
}

void DbRecord::Write()
{
	ASSERT(0);
#if 0
	BufferStream stream(m_pTable->fp1, m_pTable->m_recordSize * m_index);

	for (int i = 0; i < m_pTable->m_fields.GetSize(); i++)
	{
		m_fields[i]->Write(stream);
	}
#endif
}

ULONG DbRecord::Release()
{
	ASSERT(m_refcount > 0);
	--m_refcount;
	if (m_refcount == 0)
	{
		for (int i = 0; i < m_pTable->m_fields.GetSize(); i++)
		{
			m_fields[i]->Release();
		}
	}

	return m_refcount;
}

IRecord* DbRecord::Next()
{
	ASSERT(0);
	return NULL;
}

IRecord* DbRecord::Prev()
{
	ASSERT(0);
	return NULL;
}

IField* DbRecord::GetField(unsigned int index)
{
	return m_fields[index];
}

IField* DbRecord::GetField(StringIn name)
{
	return m_fields[m_pTable->GetFieldIndex(name)];
}

////////////////////////////////////////////
// Db2Record

unsigned int Db2Record::GetCount()
{
	return m_pTable->m_fields.GetSize();
}

void Db2Record::Write()
{
	/*
	BufferStream stream(m_pTable->fp1, m_pTable->m_recordSize * m_index);

	for (int i = 0; i < m_pTable->m_fields.GetSize(); i++)
	{
		m_fields[i]->Write(stream);
	}
	*/

	ASSERT(0);
}

ULONG Db2Record::Release()
{
	ASSERT(m_refcount > 0);
	m_refcount--;
	if (m_refcount == 0)
	{
		for (int i = 0; i < m_pTable->m_fields.GetSize(); i++)
		{
			m_fields[i]->Release();
		}
	}

	return m_refcount;
}

IRecord* Db2Record::Next()
{
	ASSERT(0);
	return NULL;
}

IRecord* Db2Record::Prev()
{
	ASSERT(0);
	return NULL;
}

IField* Db2Record::GetField(unsigned int index)
{
	return m_fields[index];
}

IField* Db2Record::GetField(StringIn name)
{
	return m_fields[m_pTable->GetFieldIndex(name)];
}

////////////////////////////////////////////////////////////////////////////////////
//

void Db::Open(const char* filename, const char* mode)
{
	m_filename = filename;
	m_mode = mode;

	ASSERT(0);
#if 0

	m_bufferManager = new BufferManager(filename, mode);

	//if (m_mode.find('r') != -1)
	{
		IBuffer* pBuffer = m_bufferManager->OpenBuffer(1);
		if (pBuffer)
		{
			m_sysFile = new File;
			m_sysFile->Open(pBuffer);

			m_sysStream = new BufferStream(m_sysFile);

			for (int i = 0; i < 2; i++)
			{
				ULONGLONG shid;
				ULONGLONG fpid;

				DbTable* pTable = new DbTable(this);

				*m_sysStream >> pTable->m_name;
				*m_sysStream >> shid;
				*m_sysStream >> fpid;

				m_tables.Add(pTable);
				m_tablesmap[pTable->m_name] = m_tables.GetSize();

				pTable->sh1 = new File;
				pTable->sh1->Open(m_bufferManager->OpenBuffer(shid));

				pTable->fp1 = new File;
				pTable->fp1->Open(m_bufferManager->OpenBuffer(fpid));

				pTable->Open();
			}
		}
		else
		{
			pBuffer = m_bufferManager->AllocateBuffer(0);

			m_sysFile = new File;
			m_sysFile->Open(pBuffer);

			m_sysStream = new BufferStream(m_sysFile);
		}
	}
	/*
	else
	{
		m_sysFile = new File;
		m_sysFile->Create(m_bufferManager->AllocateBuffer(0));

		m_sysStream = new BufferStream(m_sysFile);
	}
	*/
#endif
}

ITable* Db::NewTable(StringIn name)
{
	if (m_tablesmap[name] > 0)
		THROW(-1);

	DbTable* pTable = new DbTable(this);
	pTable->m_name = name;

	m_tables.Add(pTable);
	m_tablesmap[name] = m_tables.GetSize();

	pTable->Create();

	ASSERT(0);
#if 0

	*m_sysStream << pTable->m_name;
	*m_sysStream << pTable->sh1->GetIdentity();
	*m_sysStream << pTable->fp1->GetIdentity();
#endif

	return pTable;
}

ITable* Db::GetTable(long index)
{
	DbTable* pTable = m_tables[index];
	return pTable;
}

SQLEXT IDatabase* OpenDb(const char* name, const char* access)
{
	Db2* pDb = new Db2;
//	pDb->AddRef();
	pDb->Open(name, access);

#if 0

	Db* pDb = new Db;
//	pDb->AddRef();
	pDb->Open(name, access);

	/*
	if (std::string(access).find('a') != -1)
	{
		pTable->Append();
	}
	*/
#endif

	return pDb;

}

}
}
