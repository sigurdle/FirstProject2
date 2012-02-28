namespace System
{
namespace x3d
{

class X3DEXT X3DFieldDefinition :
	public Object,
	public IX3DFieldDefinition
{
public:

	CTOR X3DFieldDefinition(const char* name, SAIFieldAccess fieldAccess, int offset) :
		m_name(name),
	//	m_fieldType(fieldType),
		m_fieldAccess(fieldAccess),
		m_offset(offset)
	{
	}

	CTOR X3DFieldDefinition(const char* name, FieldType fieldType, SAIFieldAccess fieldAccess, int offset = -1) :
		m_name(name),
		m_fieldType(fieldType),
		m_fieldAccess(fieldAccess),
		m_offset(offset)
	{
	}

	String getName() override
	{
		return &m_name;
	}
	SAIFieldAccess getAccessType() override
	{
		return m_fieldAccess;
	}
	FieldType getFieldType() override
	{
		return m_fieldType;
	}
	String getFieldTypeString() override;

	virtual IO::TextWriter& WriteDefaultValue(IO::TextWriter& stream)
	{
		return stream;
	}

	virtual IO::TextWriter& WriteDomain(IO::TextWriter& stream)
	{
		return stream;
	}

protected:

	friend class NodeType;
	friend class X3DNode;

	ImmutableString<char> m_name;
	FieldType m_fieldType;
	SAIFieldAccess m_fieldAccess;
	int m_offset;
};

template<class T> class TypedX3DFieldDefinition : public X3DFieldDefinition
{
public:

#ifndef __LERSTAD__

	CTOR TypedX3DFieldDefinition(const char* name, SAIFieldAccess fieldAccess, int offset, typename T::value_t defaultValue = T::value_t()) :
		X3DFieldDefinition(name, T::fieldtype, fieldAccess, offset), m_defaultValue(defaultValue)
	{
	}

	CTOR TypedX3DFieldDefinition(const char* name, SAIFieldAccess fieldAccess, int offset, typename T::value_t defaultValue, typename T::value_t minValue, typename T::value_t maxValue) :
		X3DFieldDefinition(name, T::fieldtype, fieldAccess, offset),
		m_defaultValue(defaultValue),
		m_minValue(minValue),
		m_maxValue(maxValue)
	{
	}

	typename T::value_t getDefaultValue() const
	{
		return m_defaultValue;
	}

	/*
	typename T::value_t get_defaultValue() const
	{
		return m_defaultValue;
	}
	*/

	typename T::value_t getMinValue() const
	{
		return m_minValue;
	}

	typename T::value_t getMaxValue() const
	{
		return m_maxValue;
	}

	virtual IO::TextWriter& WriteDefaultValue(IO::TextWriter& stream)
	{
		stream << m_defaultValue;
		return stream;
	}

	virtual IO::TextWriter& WriteDomain(IO::TextWriter& stream)
	{
		stream << "NULL";
		return stream;
	}

protected:

	typename T::value_t m_defaultValue;
	typename T::value_t m_minValue;
	typename T::value_t m_maxValue;
#endif

};

}	// x3d
}	// System
