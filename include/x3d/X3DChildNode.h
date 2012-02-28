namespace System
{
namespace x3d
{

class X3DEXT X3DChildNode : public X3DNode
{
protected:
	CTOR X3DChildNode(NodeType* nodeType);

public:

	static NodeType* GetNodeType();
};

}	// x3d
}	// System
