#include "stdafx.h"
#include "SQL.h"
#include "dbsql.h"

#include "sql_a.h"

namespace System
{
namespace sql
{
namespace ast
{
#include "sql_parse.tab.h"
}
}
}

namespace System
{
namespace sql
{

class T_Exp
{
public:
	T_Exp()
	{
		if (kind == K_CONST_STRINGW)
		{
			if (u.m_pString)
			{
				u.m_pString = NULL;
			}
		}
	}

	enum
	{
		K_CONST_INT32,
		K_CONST_STRINGW,
		K_BINOP,
		K_FIELDREF,
	}
	kind;

	union
	{
		long int32;

		StringObject* m_pString;

		struct
		{
			int op;
			T_Exp* left;
			T_Exp* right;
		}
		BINOP;

		struct
		{
			int table_index;
			int field_index;
		}
		FIELDREF;
	}
	u;
};

class ResultVariant
{
public:
	ResultVariant()
	{
		kind = K_EMPTY;
	}

	ResultVariant(bool int32_val)
	{
		kind = K_INT32;
		u.int32_val = int32_val;
	}

	ResultVariant(long int32_val)
	{
		kind = K_INT32;
		u.int32_val = int32_val;
	}

	ResultVariant(StringIn str)
	{
		kind = K_STRINGW;
		m_pString = str._stringObject();
	}

	ResultVariant(const Variant& v)
	{
		switch (v.kind)
		{
		case VARKIND_INT32:
			{
				kind = K_INT32;
				u.int32_val = v.u.int32_val;
			}
			break;

		case VARKIND_STRINGW:
			{
				kind = K_STRINGW;
#if 0
				u.m_pObject = v.m_pObject;
#endif
				ASSERT(0);
			}
			break;

		default:
			ASSERT(0);
		}
	}

	~ResultVariant()
	{
		if (kind == K_STRINGW)
		{
			/*
			if (u.m_pStringA)
			{
				u.m_pStringA->Release();
			}
			*/
		}
	}

	enum
	{
		K_EMPTY,
		K_BOOL,
		K_INT32,
		K_STRINGW,
	}
	kind;

	union
	{
		int int32_val;
	}
	u;

	StringObject* m_pString;

	operator long () const
	{
		ASSERT(kind == K_INT32);
		return u.int32_val;
	}

	bool operator == (const ResultVariant& other) const
	{
		if (kind != other.kind)
		{
			return false;
		}

		switch (kind)
		{
		case K_INT32:
			return u.int32_val == other.u.int32_val;
		
		case K_STRINGW:
			{
				return String(m_pString) == String(other.m_pString);
			}
			break;

		default:
			ASSERT(0);
		}

		return false;
	}

	bool operator != (const ResultVariant& other) const
	{
		return !(*this == other);
	}

	bool operator && (const ResultVariant& other) const
	{
		ASSERT(kind == K_INT32);
		ASSERT(other.kind == K_INT32);

		return u.int32_val && other.u.int32_val;
	}

	bool operator || (const ResultVariant& other) const
	{
		ASSERT(kind == K_INT32);
		ASSERT(other.kind == K_INT32);

		return u.int32_val || other.u.int32_val;
	}
};

//void sql_switch_to_buffer(yy_buffer_state*);
//int sql_lex();

namespace ast
{
struct yy_buffer_state;

yy_buffer_state* sql__scan_string(const char* str);

int sql_parse();

Stm* g_stm;
}

class RecordSetFieldDef : public IFieldDef
{
public:

	virtual TableFieldType GetType()
	{
		return m_type;
	}
	virtual String GetName()
	{
		return m_name;
	}

	virtual FieldOptions GetOptions()
	{
		return m_options;
	}

	String m_name;
	TableFieldType m_type;
	int m_table_index;
	int m_field_index;
	FieldOptions m_options;

};

class RecordSetField : public IField
{
public:
	RecordSetField() : m_refcount(0)
	{
	}

	RecordSetFieldDef* m_def;

	Field m_pField;

	ULONG m_refcount;

	ULONG AddRef()
	{
		++m_refcount;
		return m_refcount;
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

	virtual IFieldDef* GetDef()
	{
		return m_def;
	}

	virtual Variant GetValue()
	{
		return m_pField.GetValue();
	}
	virtual void SetValue(const Variant& v)
	{
		ASSERT(0);
	}
	virtual void SetString(StringIn str)
	{
		ASSERT(0);
	}

	virtual void SetData(const void* data, unsigned long length)
	{
		ASSERT(0);
	}

	virtual const uint8* GetData()
	{
		return m_pField.GetData();
	}

	virtual unsigned long GetSize() const
	{
		return m_pField.GetSize();
	}

	virtual void Write()
	{
		ASSERT(0);
	}

	/*
	virtual void Read()
	{
		ASSERT(0);
	}
	*/
};

class RecordSet;

class RecordSetRecord : public IRecord
{
public:
	RecordSetRecord() : m_refcount(0)
	{
	}

	ULONG m_refcount;

	ULONG AddRef()
	{
		++m_refcount;
		return m_refcount;
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

	RecordSet* m_pTable;

	vector<RecordSetField*> m_fields;

	virtual unsigned int GetCount();
	virtual IField* GetField(unsigned int index)
	{
		return m_fields[index];
	}
	virtual IField* GetField(StringIn name);

	virtual void Write()
	{
		ASSERT(0);
	}

	virtual void Delete()
	{
		ASSERT(0);
	}

	virtual IRecord* Next();
	virtual IRecord* Prev();

	virtual ITable* GetTable();
};

struct FIELDVALUEREF_t
{
	int table_index;
	int record_index;
	int field_index;
};

class Context
{
public:
	vector<Table> g_tables;

	bool ResolveFieldName(StringIn fieldname, int& table_index, int& field_index);
	T_Exp* translate(ast::Exp* exp);
	ResultVariant evaluate(Record* ppRecord, T_Exp* exp);
};

class RecordSet : public Context, public ITable
{
public:
	RecordSet() : m_refcount(0)
	{
	}

	ULONG m_refcount;

	ULONG AddRef()
	{
		++m_refcount;
		return m_refcount;
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

//	ITable* m_pTable;
	vector<RecordSetFieldDef*> m_fields;
	map<String, long> m_fieldsmap;

//	std::vector<Record> m_records; 

	vector<FIELDVALUEREF_t*> m_items;

	void evaluate(Record* ppRecord, int* pnrow, int ntable, T_Exp* texp);

	virtual void DeleteRecord(IRecord* pRecord)
	{
		ASSERT(0);
	}

	virtual void AddField(StringIn name, TableFieldType type, const FieldOptions& options)
	{
		ASSERT(0);
	}

	virtual unsigned int GetFieldCount()
	{
		return m_fields.GetSize();
	}

	virtual int GetFieldIndex(StringIn name)
	{
		return m_fieldsmap[name]-1;
	}

	virtual IFieldDef* GetField(unsigned int index)
	{
		if (index < m_fields.GetSize())
		{
			return m_fields[index];
		}
		else
			return NULL;
	}

	virtual IFieldDef* GetField(StringIn name)
	{
		long index = m_fieldsmap[name]-1;
		if (index == -1)
			return NULL;
		return m_fields[index];
	}
	virtual IRecord* NewRecord()
	{
		ASSERT(0);
		return NULL;
	}

	virtual IRecord* GetRecord(unsigned int index)
	{
		RecordSetRecord* pRecord = new RecordSetRecord;
		pRecord->AddRef();

		//return m_pTable->GetRecord(m_items[index]);

		for (int i = 0; i < m_fields.GetSize(); i++)
		{
			FIELDVALUEREF_t& ref = m_items[index][i];

			Record pRecord2 = g_tables[ref.table_index][ref.record_index];
		//	pRecord2->Seek(ref.record_index);
			Field pFromField = pRecord2.get_Fields()[ref.field_index];

			RecordSetField* pField = new RecordSetField;
			pField->m_def = m_fields[i];
			pField->m_pField = pFromField;

			pRecord->m_fields.Add(pField);
		}

		return pRecord;
	}

	virtual IRecord* Begin()
	{
		RecordSetRecord* pRecord = new RecordSetRecord;

		ASSERT(0);

		return pRecord;
	}

	virtual IRecord* End()
	{
		RecordSetRecord* pRecord = new RecordSetRecord;

		ASSERT(0);

		return pRecord;
	}

	virtual unsigned int GetCount()
	{
		return m_items.GetSize();
	}

	virtual void Close()
	{
		m_items.RemoveAll();
	}
};

ITable* RecordSetRecord::GetTable()
{
	return m_pTable;
}

IRecord* RecordSetRecord::Next()
{
	ASSERT(0);
	return NULL;
}

IRecord* RecordSetRecord::Prev()
{
	ASSERT(0);
	return NULL;
}

unsigned int RecordSetRecord::GetCount()
{
	return m_pTable->m_fields.GetSize();
}

IField* RecordSetRecord::GetField(StringIn name)
{
	return m_fields[m_pTable->GetFieldIndex(name)];
}

ResultVariant Context::evaluate(Record* ppRecord, T_Exp* exp)
{
	switch (exp->kind)
	{
	case T_Exp::K_CONST_INT32:
		{
			return ResultVariant(exp->u.int32);
		}
		break;

	case T_Exp::K_CONST_STRINGW:
		{
			return ResultVariant(StringIn(exp->u.m_pString));
		}
		break;

	case T_Exp::K_FIELDREF:
		{
			Record pRecord = ppRecord[exp->u.FIELDREF.table_index];

			Variant value = pRecord.get_Fields()[exp->u.FIELDREF.field_index].GetValue();

			return ResultVariant(value);
		}
		break;

	case T_Exp::K_BINOP:
		{
			ResultVariant left = evaluate(ppRecord, exp->u.BINOP.left);
			ResultVariant right = evaluate(ppRecord, exp->u.BINOP.right);

			switch (exp->u.BINOP.op)
			{
				case '==':
					{
						return left == right;
					}
					break;

				case '!=':
					{
						return left != right;
					}
					break;

				case '&&':
					{
						return left && right;
					}
					break;

				case '||':
					{
						return left || right;
					}
					break;

					/*
				case '>':
					{
						return left > right;
					}
					break;

				case '<':
					{
						return left < right;
					}
					break;

				case '>=':
					{
						return left >= right;
					}
					break;

				case '<=':
					{
						return left <= right;
					}
					break;

				case '+':
					{
						return left + right;
					}
					break;

				case '-':
					{
						return left - right;
					}
					break;
				*/
			}
		}
		break;

		/*
	case sql_A_Exp::K_ID:
		{
			return (long)pRecord->GetField(ConvertA2S(exp->u.ID.name))->GetValue();
		}
		break;
		*/
	}

	ASSERT(0);
	return ResultVariant();
}

bool Context::ResolveFieldName(StringIn fieldname, int& table_index, int& field_index)
{
	for (table_index = 0; table_index < g_tables.GetSize(); table_index++)
	{
		field_index = g_tables[table_index].GetFieldIndex(fieldname);
		if (field_index != -1)
		{
			break;
		}
	}

	if (field_index == -1)
	{
		DebugTrace("Unknown field name " << fieldname << "\n");
		return NULL;
	}

// Now check the rest of the tables to see if the field name appears in more than one table
	for (int table_index2 = table_index+1 ; table_index2 < g_tables.GetSize(); table_index2++)
	{
		int field_index = g_tables[table_index2].GetFieldIndex(fieldname);
		if (field_index != -1)
		{
			DebugTrace("field name " << fieldname << " was found in more than one table" << "\n");
			return false;
		}
	}

	return true;
}

T_Exp* Context::translate(ast::Exp* exp)
{
	switch (exp->kind)
	{
	case ast::Exp::K_CONST_INT32:
		{
			T_Exp* p = new T_Exp;
			p->kind = T_Exp::K_CONST_INT32;
			p->u.int32 = exp->u.int32;
			return p;
		}
		break;

	case ast::Exp::K_CONST_STRING:
		{
			T_Exp* p = new T_Exp;
			p->kind = T_Exp::K_CONST_STRINGW;
			p->u.m_pString = ((ast::CharLiteralExp*)exp)->m_value;//new StringA(exp->u.STRING.p, exp->u.STRING.len);
			//p->u.m_pStringA->AddRef();
			return p;
		}
		break;

	case ast::Exp::K_BINOP:
		{
			if (exp->u.BINOP.op == '.')
			{
				ASSERT(0);
			}
			else
			{
				T_Exp* p = new T_Exp;
				p->kind = T_Exp::K_BINOP;
				p->u.BINOP.op = exp->u.BINOP.op;
				p->u.BINOP.left = translate(exp->u.BINOP.left);
				p->u.BINOP.right = translate(exp->u.BINOP.right);
				return p;
			}
		}
		break;

	case ast::Exp::K_ID:
		{
			ast::IdList* from = ((ast::SelectStm*)ast::g_stm)->m_from;

			ASSERT(0);
#if 0

			int field_index;
			int table_index;


			if (ResolveFieldName(new StringW(exp->u.ID.name), table_index, field_index))
			{
				sql_T_Exp* p = new sql_T_Exp;
				p->kind = sql_T_Exp::K_FIELDREF;
				p->u.FIELDREF.table_index = table_index;
				p->u.FIELDREF.field_index = field_index;

				return p;
			}
#endif
		}
		break;
	}

	ASSERT(0);
	return 0;
}

void RecordSet::evaluate(Record* ppRecord, int* pnrow, int ntable, T_Exp* texp)
{
	if (ntable < g_tables.GetSize()-1)
	{
		int count = g_tables[ntable].GetCount();

	//	pRecordSet->m_records[ntable] = g_tables[ntable].Begin();

		for (int row = 0; row < count; ++row)
		{
			ppRecord[ntable] = g_tables[ntable][row];//g_tables[ntable]->GetRecord(row);
			pnrow[ntable] = row;
			evaluate(ppRecord, pnrow, ntable+1, texp);

			//pRecordSet->m_records[ntable]++;
		}
	}
	else
	{
		int count = g_tables[ntable].GetCount();
		for (int row = 0; row < count; ++row)
		{
			ppRecord[ntable] = g_tables[ntable][row];
			pnrow[ntable] = row;

			ResultVariant v = texp? Context::evaluate(ppRecord, texp): true;
			if (v.u.int32_val)
			{
				FIELDVALUEREF_t* ref = new FIELDVALUEREF_t[m_fields.GetSize()];

				for (int i = 0; i < m_fields.GetSize(); ++i)
				{
					ref[i].table_index = m_fields[i]->m_table_index;
					ref[i].record_index = pnrow[ref[i].table_index];//RecordSet->m_fields[i]->m_field_index;
					ref[i].field_index = m_fields[i]->m_field_index;
				}

				m_items.Add(ref);
			}
		}
	}
}

ITable* Database::Execute_SELECT(ast::SelectStm* stm)
{
	RecordSet* pRecordSet = new RecordSet;
	pRecordSet->AddRef();

	ast::IdList* from = stm->m_from;
	while (from)
	{
	//	std::string filename = std::string("C:/") + from->head;

		Table table = GetTable(from->head);

		pRecordSet->g_tables.Add(table);

		from = from->tail;
	}

	ast::IdList* idlist = stm->m_columns;
	while (idlist)
	{
		int field_index;
		int table_index;

		String name = idlist->head;//new StringW(idlist->head);

		if (!pRecordSet->ResolveFieldName(name, table_index, field_index))
		{
			return NULL;
		}

		RecordSetFieldDef* pFieldDef = new RecordSetFieldDef;
		pFieldDef->m_name = name;
		pFieldDef->m_type = pRecordSet->g_tables[table_index].GetField(field_index)->GetType();
		pFieldDef->m_table_index = table_index;
		pFieldDef->m_field_index = field_index;

		pRecordSet->m_fields.Add(pFieldDef);
		pRecordSet->m_fieldsmap[name] = pRecordSet->m_fields.GetSize();

		idlist = idlist->tail;
	}

	T_Exp* texp;
	if (stm->m_whereCriteria)
		texp = pRecordSet->translate(stm->m_whereCriteria);
	else
		texp = NULL;

	Record* ppRecord = new Record[pRecordSet->g_tables.GetSize()];
	int* pnrow = new int[pRecordSet->g_tables.GetSize()];

	pRecordSet->evaluate(ppRecord, pnrow, 0, texp);

	delete[] ppRecord;
	delete[] pnrow;

	return pRecordSet;
}

static ITable* Execute_DELETE(ast::DeleteStm* stm)
{
#if 0
	g_tables.clear();

	std::string filename = std::string("C:/") + stm->DELETE_stm.from;

	Table table(filename.c_str(), "rb");

	g_tables.push_back(table);

	sql_T_Exp* texp = translate(NULL, stm->DELETE_stm.whereCriteria);

	int count = table.GetCount();
	Record pRecord = table.Begin();
	for (int row = 0; row < count; row++)
	{
		ResultVariant v = evaluate(&pRecord, texp);
		if ((long)v)
		{
			ASSERT(0);
#if 0
			pRecord->Delete();
#endif
			TRACE("Deleted row %d\n", row);
		}
		pRecord++;
	}

	table.Close();

	g_tables.clear();
#endif
	return NULL;
}

void Database::Execute_TABLEDEF(ast::TableDefStm* stm)
{
//	FILE* fp = fopen(stm->m_name->ToStringA()->c_str(), "wb");
//	fclose(fp);

	ITable* table = m_p->NewTable(stm->m_name);

	ast::TableElementList* elemlist = stm->m_elementList;
	while (elemlist)
	{
		ast::ColumnDef* columndef = elemlist->head;

	//	fwrite(
		/*
		Db2FieldDef* fdef = new Db2FieldDef;
		fdef->m_name = columndef->m_name;
		fdef->m_type = columndef->m_dataType->GetKind();

		table->m_fields.push_back(fdef);
		*/
		TableFieldType datatype;
		switch (columndef->m_dataType->GetKind())
		{
		case ast::DataType::NUMERIC:
			datatype.m_kind = TableFieldType::FTyp_Long;
			break;

		case ast::DataType::CHAR:
			datatype.m_kind = TableFieldType::FTyp_Char;
			datatype.m_length = ((ast::CharDataType*)columndef->m_dataType)->m_length;
			break;

		case ast::DataType::CHAR_VARYING:
			datatype.m_kind = TableFieldType::FTyp_CharVarying;
			datatype.m_length = ((ast::CharVaryingDataType*)columndef->m_dataType)->m_length;
			break;

		case ast::DataType::VARCHAR:
			datatype.m_kind = TableFieldType::FTyp_VarChar;
			datatype.m_length = ((ast::VarCharDataType*)columndef->m_dataType)->m_length;
			break;
		}

		FieldOptions options;

		options.m_startWith = 1;
		options.m_incrementBy = 1;

		if (columndef->m_identity)
		{
			options.m_identity = true;

			ast::SequenceGeneratorOptionList* optionlist = columndef->m_identity->m_sequenceGeneratorOptionList;
			while (optionlist)
			{
				switch (optionlist->head->GetKind())
				{
				case ast::SequenceGeneratorOption::START_WITH:
					{
						options.m_startWith = ((ast::StartWithSequenceGeneratorOption*)optionlist->head)->m_value;
					}
					break;

				default:
					ASSERT(0);
				}

				optionlist = optionlist->tail;
			}
		}
		else
		{
			options.m_identity = false;
		}

		table->AddField(columndef->m_name, datatype, options);

		elemlist = elemlist->tail;
	}
}

template<class T> unsigned int count(T* l)
{
	unsigned int n = 0;
	while (l)
	{
		n++;
		l = l->tail;
	}

	return n;
}

void Database::Execute_INSERT(ast::InsertStm* stm)
{
	Table table = GetTable(stm->m_target);

	Record record = table.NewRecord();

	ast::IdList* columns = stm->m_constructor->m_columns;
	ast::ExpList* values = stm->m_constructor->m_values;

	unsigned int ncolumns = count(columns);
	unsigned int nvalues = count(values);

	if (ncolumns < nvalues)
	{
		printf("Too many values");
		return;
	}
	else if (ncolumns > nvalues)
	{
		printf("Too few values");
		return;
	}

	while (columns)
	{
		Variant value;
		IFieldDef* fielddef = table.GetField(columns->head);
		TableFieldType fieldtype = fielddef->GetType();

		switch (fieldtype.m_kind)
		{
		case TableFieldType::FTyp_Char:
			value = ((ast::CharLiteralExp*)values->head)->m_value;
			break;

		default:
			ASSERT(0);
		}

		Field field = record[columns->head];
		field.SetValue(value);

		columns = columns->tail;
		values = values->tail;
	}
}

Table Database::Execute(const char* command)
{
	ast::yy_buffer_state* state = ast::sql__scan_string(command);
	ast::g_stm = NULL;
	int error = ast::sql_parse();
	if (error != 0)
	{
		return NULL;
	}

	if (ast::g_stm)
	{
		switch (ast::g_stm->GetKind())
		{
		case ast::Stm::K_SELECT:
			{
				return Execute_SELECT((ast::SelectStm*)ast::g_stm);
			}
			break;

		case ast::Stm::K_INSERT:
			{
				Execute_INSERT((ast::InsertStm*)ast::g_stm);
			}
			break;

		case ast::Stm::K_DELETE:
			{
				return Execute_DELETE((ast::DeleteStm*)ast::g_stm);
			}
			break;

		case ast::Stm::K_TABLEDEF:
			{
				Execute_TABLEDEF((ast::TableDefStm*)ast::g_stm);
			}
			break;

		default:
			ASSERT(0);
		}
	}

	return NULL;
}

}
}
