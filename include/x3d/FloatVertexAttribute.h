namespace System
{
namespace x3d
{

class X3DEXT FloatVertexAttribute : public X3DVertexAttributeNode
{
public:
	CTOR FloatVertexAttribute();

	int getNumComponents() const
	{
		return m_numComponents->getValue();
	}

	float getValue(unsigned int index) const throw(ArgumentOutOfRangeException)
	{
		return m_value->get1Value(index);
	}

	float getFloat(unsigned int index) const throw(ArgumentOutOfRangeException);
	void setFloat(unsigned int index, float value) throw(ArgumentOutOfRangeException);

	gm::vector2f getVec2(unsigned int index) const throw(ArgumentOutOfRangeException);
	void setVec2(unsigned int index, gm::vector2f value) throw(ArgumentOutOfRangeException);

	gm::vector3f getVec3(unsigned int index) const throw(ArgumentOutOfRangeException);
	void setVec3(unsigned int index, gm::vector3f value) throw(ArgumentOutOfRangeException);

	gm::vector4f getVec4(unsigned int index) const throw(ArgumentOutOfRangeException);
	void setVec4(unsigned int index, gm::vector4f value) throw(ArgumentOutOfRangeException);

	void setValue(unsigned int index, float value) throw(ArgumentOutOfRangeException);

	MFFloat* get_valueField() const
	{
		return m_value;
	}

	SFInt32* get_numComponentsField() const
	{
		return m_numComponents;
	}

	static NodeType* GetNodeType();
	static NodeType* nodeType;

private:

/*
	SFNode   [in,out] metadata      NULL [X3DMetadataObject]

	MFFloat  [in,out] value  		  []   (-?,?)
	SFString []       name          ""
	SFInt32  []       numComponents 4    [1..4]
*/
	MFFloat* m_value;
	SFInt32* m_numComponents;
};

}	// x3d
}
