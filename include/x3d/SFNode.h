#ifndef x3d_SFNode_h
#define x3d_SFNode_h

namespace System
{
namespace x3d
{

class X3DEXT SFNode : public X3DField
{
public:
	CTOR SFNode(X3DNode* ownerNode);
	CTOR SFNode(X3DFieldDefinition* def, X3DNode* ownerNode);

	static const FieldType fieldtype = FieldType_SFNode;
	typedef X3DNode* value_t;

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	virtual void CopyFrom(X3DField* pFrom);

	// TODO, not

	virtual X3DNode* getValue() const = 0;

	virtual void setValue(X3DPrototypeInstance* proto) = 0;

	virtual void setX3DNode(X3DNode* node) = 0;

//	X3DNode* m_value;
//	virtual X3DNode* getValue() const = 0;
};

template<class T, class T2 = T> class TypedSFNode : public SFNode
{
public:

	CTOR TypedSFNode(X3DNode* ownerNode) : SFNode(ownerNode)
	{
	}

	CTOR TypedSFNode(TypedX3DFieldDefinition<TypedSFNode<T> >* fieldDef, X3DNode* ownerNode) : SFNode(fieldDef, ownerNode)
	{
	}

	virtual T2 getValue() const
	{
		return m_value;
	}

	void setValue(T node)
	{
		m_value = node;
		m_ownerNode->OnFieldChanged(this);
	}

	virtual void setValue(X3DPrototypeInstance* proto)
	{
		// TODO
		ASSERT(0);
	}

	virtual void setX3DNode(X3DNode* node)
	{
		T value = dynamic_cast<T>(node);
		ASSERT(value);
		m_value = value;
		m_ownerNode->OnFieldChanged(this);
	}

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream)
	{
		if (m_value)
		{
			if (m_value->getDefName() != nullptr)
			{
				stream << "USE " << m_value->getDefName();
			}
			else
			{
				m_value->WriteVRML(stream);
			}
		}
		else
		{
			stream << "NULL";
		}

		return stream;
	}

	typedef T value_t;

public:

	T m_value;
};

}	// x3d
}

#endif // x3d_SFNode_h
