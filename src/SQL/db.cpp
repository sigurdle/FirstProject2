#include "stdafx.h"
#include "SQL.h"
#include "db.h"

namespace System
{
namespace sql
{

//ITable* OpenTable(const char* name, const char* access);
IDatabase* OpenDb(const char* name, const char* access);

// Field

Field::Field()
{
	m_p = NULL;
}

Field::~Field()
{
	/*
	if (m_p)
	{
		m_p->Release();
	}
	*/
}

Field& Field::operator = (const Field& other)
{
	IField* old = m_p;
	m_p = other.m_p;

	/*
	if (m_p)
	{
		m_p->AddRef();
	}

	if (old)
	{
		old->Release();
	}
	*/

	return *this;
}

String Field::GetString() const
{
	Variant v = m_p->GetValue();
	if (v.kind == VARKIND_STRINGA)
	{
		return (System::StringA*)v.m_pObject;
	}
	else
	{
		THROW(-1);
		ASSERT(0);
	}
	return NULL;//System::StringA();
}

unsigned int FieldCollection::Length() const
{
	ASSERT(0);
	return 0;
	//return m_ownerRecord->GetFieldCount();
}

Field FieldCollection::operator [] (unsigned int index)
{
	return m_ownerRecord->GetField(index);
}

Field FieldCollection::operator [] (StringIn name)
{
	return m_ownerRecord->GetField(name);
}

/*
long FieldCollection::GetFieldIndex(const sysstring& name)
{
	return m_ownerRecord->GetFieldIndex(name);
}
*/

// Record

Record::Record(const Record& other) : m_fields(this)
{
	m_p = other.m_p;
//	m_p->AddRef();
}

Record::~Record()
{
/*
	if (m_p)
	{
		m_p->Release();
	}
	*/
}

Field Record::operator [] (StringIn name)
{
	return Field(m_p->GetField(name));
}

Field Record::operator [] (unsigned int index)
{
	return Field(m_p->GetField(index));
}

const Field Record::operator [] (StringIn name) const
{
	return Field(m_p->GetField(name));
}

const Field Record::operator [] (unsigned int index) const
{
	return Field(m_p->GetField(index));
}

Field Record::GetField(unsigned int index)
{
	return Field(m_p->GetField(index));
}

Field Record::GetField(StringIn name)
{
	return Field(m_p->GetField(name));
}

// Table

Table::Table()
{
	m_p = NULL;
}

Table::Table(ITable* pTable)
{
	m_p = pTable;
	/*
	if (m_p)
	{
		m_p->AddRef();
	}
	*/
}

Table::Table(const Table& other)
{
	m_p = other.m_p;
	/*
	if (m_p)
	{
		m_p->AddRef();
	}
	*/
}

Table::~Table()
{
	/*
	if (m_p)
	{
		m_p->Release();
	}
	*/
}

Table& Table::operator = (const Table& other)
{
	ITable* old = m_p;
	m_p = other.m_p;

	/*
	if (m_p)
	{
		m_p->AddRef();
	}

	if (old)
	{
		old->Release();
	}
	*/

	return *this;
}

// Database

Database::Database()
{
	m_p = NULL;
}

Database::Database(const char* name, const char* access)
{
	m_p = OpenDb(name, access);
}

Database::~Database()
{
	/*
	if (m_p)
	{
		m_p->Release();
	}
	*/
}

class _Command
{
public:
	_Command() : m_refcount(0)
	{
	}

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
};

Command::Command()
{
}

Command::Command(const char* command)
{
}

Command::~Command()
{
	if (m_p)
	{
		m_p->Release();
	}
}

ITable* Execute(const char* command);


}
}
