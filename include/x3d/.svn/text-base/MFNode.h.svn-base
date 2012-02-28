#ifndef x3d_MFNode_h
#define x3d_MFNode_h

namespace System
{
namespace x3d
{

class X3DEXT MFNode : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFNode;

	CTOR MFNode(X3DNode* ownerNode);
	CTOR MFNode(X3DFieldDefinition* fieldDef, X3DNode* owner) : X3DArrayField(fieldDef, owner)
	{
	}

	virtual FieldType getFieldType() const
	{
		return fieldtype;
	}

	virtual const Type_Info& GetTypeOfNode()
	{
		return typeid(X3DNode);
	}

	virtual IO::TextWriter& WriteValuesToStream(IO::TextWriter& stream) override;

	virtual void CopyFrom(X3DField* pFrom);

	virtual X3DNode* get1Value(size_t index) throw (ArgumentOutOfRangeException*);
	virtual void set1Value(size_t index, X3DNode* newVal) throw (ArgumentOutOfRangeException*);
	virtual void append1Value(X3DNode* node);

// X3DArrayField
	virtual size_t get_size() const throw()
	{
		return m_items.GetSize();
	}

public:

	friend class VRMLLoader;

	inline uint32 GetLights() const
	{
		return m_nLights;
	}

	vector<X3DNode*> m_items;

protected:

	uint32 m_nLights;
	uint32 m_nViewpoints;
};

template<class TYPE> class TypedMFNode : public MFNode
{
public:

	typedef vector<TYPE> value_t;

	CTOR TypedMFNode(TypedX3DFieldDefinition<TypedMFNode<TYPE> >* fieldDef, X3DNode* owner) : MFNode(fieldDef, owner)
	{
	}

	virtual const Type_Info& GetTypeOfNode()
	{
		return typeid(TYPE);
	}

	inline void append1Value(TYPE* node)
	{
		MFNode::append1Value(node);
	}

	virtual void append1Value(X3DNode* node)
	{
		if (dynamic_cast<TYPE>(node) == NULL) raise(Exception("Wrong node type"));
		MFNode::append1Value(node);
	}
};

}	// x3d

template<class TYPE> IO::TextWriter& WriteToStream(IO::TextWriter& writer, const x3d::TypedMFNode<TYPE>* mfnode);

}	// System

#endif // x3d_MFNode_h
