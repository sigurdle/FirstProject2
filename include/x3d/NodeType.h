namespace System
{
namespace x3d
{

class X3DEXT NodeType : public Object
{
public:
	// a null nodeName must be passed for abstract nodeTypes (those named X3DxxxNode)
	CTOR NodeType(StringIn nodeName, const Type_Info& classType, X3DFieldDefinition** fields, uint count);
	CTOR NodeType(StringIn nodeName, const Type_Info& classType, X3DFieldDefinition** fields, uint count, NodeType* baseType);

	virtual String ToString() override;

	IO::TextWriter& WriteX3DDef(IO::TextWriter& stream);

	String get_name() const throw ()
	{
		return m_nodeName;
	}

	const Type_Info& get_TypeInfo() const throw ()
	{
		return m_classType;
	}

	X3DFieldDefinitions* getFieldDefinitions() const throw ()
	{
		return m_fieldDefinitions;
	}

	ClassType* GetClassType() const throw ()
	{
		return m_classType.GetType()->AsClass();
	}

	NodeType* GetBaseNodeType() const throw ();
	X3DNode* CreateNode() throw (Exception*);

	static NodeType* FindByName(StringIn nodeName) throw ();

protected:

	void Register();

//	vector<NodeType*> m_createdNodes;	// Have this ??

	friend class X3DNode;
	friend class X3DScene;

	String m_nodeName;
	const Type_Info& m_classType;
	X3DFieldDefinitions* m_fieldDefinitions;

	X3DFieldDefinition** m_fields;
	uint m_fieldCount;

	class Data
	{
	public:
		map<String, NodeType*> m_nodeTypeByName;
		vector<NodeType*> m_nodeTypes;
	};

	static Data* s_data;
};

}	// x3d
}	// System
