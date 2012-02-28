namespace System
{
namespace x3d
{

class X3DEXT X3DAppearanceChildNode : public X3DNode
{
public:

	X3DNODE_ABSTRACT(X3DAppearanceChildNode, X3DNode)

protected:
	CTOR X3DAppearanceChildNode(NodeType* nodeType) : X3DNode(nodeType)
	{
	}
};

}	// x3d
}	// System
