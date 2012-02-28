namespace System
{
namespace x3d
{

class X3DEXT Matrix4VertexAttribute : public X3DVertexAttributeNode
{
public:
	CTOR Matrix4VertexAttribute();

	static NodeType s_nodeType;

/*
  SFNode     [in,out] metadata NULL [X3DMetadataObject]
  MFMatrix4f [in,out] value    []   (-?,?)
  SFString   []       name     ""
*/

	MFMatrix4f* m_value;
};

}	// x3d
}
