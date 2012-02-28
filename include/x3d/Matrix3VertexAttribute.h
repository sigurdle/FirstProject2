namespace System
{
namespace x3d
{

class X3DEXT Matrix3VertexAttribute : public X3DVertexAttributeNode
{
public:
	CTOR Matrix3VertexAttribute();

	static NodeType s_nodeType;

/*
  SFNode     [in,out] metadata NULL [X3DMetadataObject]
  MFMatrix3f [in,out] value    []   (-?,?)
  SFString   []       name     ""
*/

	MFMatrix3f* m_value;
};

}	// x3d
}
