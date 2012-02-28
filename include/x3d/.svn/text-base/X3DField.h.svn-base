namespace System
{
namespace x3d
{

class X3DEXT X3DField : public Object
{
public:
	CTOR X3DField(const X3DField& other);
	CTOR X3DField(X3DNode* ownerNode);
	CTOR X3DField(X3DFieldDefinition* fieldDef, X3DNode* ownerNode);
	~X3DField();

	virtual FieldType getFieldType() const throw () = 0;

	virtual IO::TextWriter& WriteToStream(IO::TextWriter& stream)
	{
		stream << getFieldName();
		stream << ' ';
		WriteValueToStream(stream);
		return stream;
	}

	String getValueAsString()
	{
		IO::StringWriter stream;
		WriteValueToStream(stream);
		return stream.str();
	}

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) = 0;

	virtual void CopyFrom(X3DField* pFrom) = 0;

	X3DNode* getOwnerNode() const throw ()
	{
		return m_ownerNode;
	}

	virtual bool isWritable();
	virtual bool isReadable();

	String getFieldName() const throw ();

	vector<Route*> m_outputRoutes;
	Route* m_inputRoute;

	X3DFieldDefinition* m_fieldDef;

	SAIFieldAccess m_fieldAccess;
	String m_is;	// For proto
	String m_fieldName;

	static X3DField* CreateFieldOfType(FieldType fieldType, X3DNode* ownerNode);

protected:

	friend class X3DNode;
	friend class VRMLLoader;
	friend class SAIProtoDeclaration;

//	friend X3DField* CreateFieldOfType(FieldType fieldType, X3DNode* ownerNode);

	X3DNode* m_ownerNode;
};

}	// x3d
}	// System
