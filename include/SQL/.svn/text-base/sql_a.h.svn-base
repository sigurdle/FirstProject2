#pragma once

namespace System
{
namespace sql
{
namespace ast
{

class DataType;
class ColumnDef;

class Exp
{
public:
	enum
	{
		K_ID,
		K_CONST_INT32,
		K_CONST_STRING,
		K_BINOP,
		K_UNOP,
	}
	kind;

	union
	{
		struct
		{
			char* name;
		}
		ID;

		/*
		struct
		{
			char* p;
			int len;
		}
		STRING;
		*/

		long int32;

		struct
		{
			int op;
			Exp* node;
		}
		UNOP;

		struct
		{
			int op;
			Exp* left;
			Exp* right;
		}
		BINOP;
	}
	u;
};

class CharLiteralExp : public Exp
{
public:
	CTOR CharLiteralExp(const char* value)
	{
		kind = K_CONST_STRING;
		m_value = value;
	}

	String m_value;
};

class ExpList
{
public:
	CTOR ExpList(Exp* _head, ExpList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	Exp* head;
	ExpList* tail;
};

class IdList
{
public:
	CTOR IdList(const char* _head, IdList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	String head;
	IdList* tail;
};

class Stm : public Object
{
public:
	enum Kind
	{
		K_SELECT,
		K_INSERT,
		K_DELETE,
		K_TABLEDEF,
		K_ALTER_TABLE,
		K_USERDEFINED_TYPEDEF,
	};

	virtual Kind GetKind() const = 0;
};

class SelectStm : public Stm
{
public:
	CTOR SelectStm(IdList* columns, IdList* from, Exp* whereCriteria);

	virtual Kind GetKind() const
	{
		return K_SELECT;
	}

	IdList* m_columns;
	IdList* m_from;
	Exp* m_whereCriteria;
};

class FromConstructor
{
public:

	FromConstructor(IdList* columns, ExpList* values)
	{
		m_columns = columns;
		m_values = values;
	}

	IdList* m_columns;
	ExpList* m_values;
};

class InsertStm : public Stm
{
public:
	CTOR InsertStm(const char* target, FromConstructor* constructor)
	{
		m_target = target;
		m_constructor = constructor;
	}

	virtual Kind GetKind() const
	{
		return K_INSERT;
	}

	String m_target;
	FromConstructor* m_constructor;
};

class DeleteStm : public Stm
{
public:
	CTOR DeleteStm(const char* from, Exp* whereCriteria);

	virtual Kind GetKind() const
	{
		return K_DELETE;
	}

	String m_from;
	Exp* m_whereCriteria;
};

class QualifiedName : public Object
{
public:
	QualifiedName(QualifiedName* left, const char* name)
	{
		m_left = left;
		m_name = name;
	}

	QualifiedName* m_left;
	String m_name;
};

class UserDefinedTypeDefStm : public Stm
{
public:
	CTOR UserDefinedTypeDefStm(QualifiedName* name, QualifiedName* subType)
	{
		m_name = name;
		m_subType = subType;
	}

	virtual Kind GetKind() const
	{
		return K_USERDEFINED_TYPEDEF;
	}

	QualifiedName* m_name;
	QualifiedName* m_subType;
};

class AlterTableAction : public Object
{
public:
};

class AddColumnAlterTableAction : public AlterTableAction
{
public:
	CTOR AddColumnAlterTableAction(ColumnDef* columndef)
	{
		m_columndef = columndef;
	}

	ColumnDef* m_columndef;
};

class AlterTableStm : public Stm
{
public:
	CTOR AlterTableStm(const char* table_name, AlterTableAction* action)
	{
		m_table_name = table_name;
		m_action = action;
	}

	virtual Kind GetKind() const
	{
		return K_ALTER_TABLE;
	}

	String m_table_name;
	AlterTableAction* m_action;
};

class DataType : public Object
{
public:
	enum Kind
	{
		NUMERIC,
		CHAR,
		CHAR_VARYING,
		VARCHAR,
		XML,
	};

	virtual Kind GetKind() const = 0;
};

enum PrimaryXMLTypeModifier
{
	MODIFIER_DOCUMENT,
	MODIFIER_CONTENT,
	MODIFIER_SEQUENCE
};

class XMLTypeModifier : public Object
{
public:

	XMLTypeModifier(PrimaryXMLTypeModifier primary)
	{
		m_primary = primary;
	}

	PrimaryXMLTypeModifier m_primary;
};

class XMLDataType : public DataType
{
public:
	XMLDataType(XMLTypeModifier* typeModifier)
	{
		m_typeModifier = typeModifier;
	}

	virtual Kind GetKind() const
	{
		return XML;
	}

	XMLTypeModifier* m_typeModifier;
};

class NumericDataType : public DataType
{
public:

	virtual Kind GetKind() const
	{
		return NUMERIC;
	}
};

class CharDataType : public DataType
{
public:
	CTOR CharDataType(unsigned int length)
	{
		m_length = length;
	}

	virtual Kind GetKind() const
	{
		return CHAR;
	}

	unsigned int m_length;
};

class CharVaryingDataType : public DataType
{
public:
	CTOR CharVaryingDataType(unsigned int length)
	{
		m_length = length;
	}

	virtual Kind GetKind() const
	{
		return CHAR_VARYING;
	}

	unsigned int m_length;
};

class VarCharDataType : public DataType
{
public:
	CTOR VarCharDataType(unsigned int length)
	{
		m_length = length;
	}

	virtual Kind GetKind() const
	{
		return VARCHAR;
	}

	unsigned int m_length;
};

class SequenceGeneratorOption : public Object
{
public:
	enum Kind
	{
		START_WITH,
		INCREMENT_BY,
		MAXVALUE,
		NO_MAXVALUE,
	};

	virtual Kind GetKind() const = 0;
};

class StartWithSequenceGeneratorOption : public SequenceGeneratorOption
{
public:
	CTOR StartWithSequenceGeneratorOption(long value)
	{
		m_value = value;
	}

	virtual Kind GetKind() const
	{
		return START_WITH;
	}

	long m_value;
};

class IncrementBySequenceGeneratorOption : public SequenceGeneratorOption
{
public:
	CTOR IncrementBySequenceGeneratorOption(LONGLONG value)
	{
		m_value = value;
	}

	virtual Kind GetKind() const
	{
		return INCREMENT_BY;
	}

	LONGLONG m_value;
};

class MaxValueSequenceGeneratorOption : public SequenceGeneratorOption
{
public:
	CTOR MaxValueSequenceGeneratorOption(LONGLONG value)
	{
		m_value = value;
	}

	virtual Kind GetKind() const
	{
		return MAXVALUE;
	}

	LONGLONG m_value;
};

class NoMaxValueSequenceGeneratorOption : public SequenceGeneratorOption
{
public:
	CTOR NoMaxValueSequenceGeneratorOption()
	{
	}

	virtual Kind GetKind() const
	{
		return NO_MAXVALUE;
	}
};

class SequenceGeneratorOptionList
{
public:
	CTOR SequenceGeneratorOptionList(SequenceGeneratorOption* _head, SequenceGeneratorOptionList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	SequenceGeneratorOption* head;
	SequenceGeneratorOptionList* tail;
};

class Identity : public Object
{
public:
	Identity(SequenceGeneratorOptionList* sequenceGeneratorOptionList)
	{
		m_sequenceGeneratorOptionList = sequenceGeneratorOptionList;
	}

	SequenceGeneratorOptionList* m_sequenceGeneratorOptionList;
};

class ColumnDef : public Object
{
public:

	CTOR ColumnDef(const char* name, DataType* dataType, Identity* identity)
	{
		m_name = name;
		m_dataType = dataType;
		m_identity = identity;
	}

	String m_name;
	DataType* m_dataType;
	Identity* m_identity;
};

class TableElementList
{
public:
	CTOR TableElementList(ColumnDef* _head, TableElementList* _tail)
	{
		head = _head;
		tail = _tail;
	}

	ColumnDef* head;
	TableElementList* tail;
};

class TableDefStm : public Stm
{
public:
	CTOR TableDefStm(const char* name, TableElementList* elementList)
	{
		m_name = name;
		m_elementList = elementList;
	}

	virtual Kind GetKind() const
	{
		return K_TABLEDEF;
	}

	String m_name;
	TableElementList* m_elementList;
};

Exp* sql_A_Id(const char* name);
Exp* sql_A_Const(long int32);
//sql_A_Exp* sql_A_Const(const char* string);
Exp* sql_A_Unop(int op, Exp* node);
Exp* sql_A_Binop(int op, Exp* left, Exp* right);

}	// ast
}	// sql
}	// System
