namespace System
{
namespace x3d
{

class X3DEXT X3DShapeNode : public X3DChildNode
{
protected:
	CTOR X3DShapeNode(NodeType* nodeType) : X3DChildNode(nodeType)
	{
	}

public:

	virtual X3DGeometryNode* getGeometry() = 0;
	virtual void setGeometry(X3DGeometryNode *node) = 0;

	virtual void setAppearance(X3DAppearanceNode *node) = 0;

	static NodeType* GetNodeType();
};

}	// x3d
}
