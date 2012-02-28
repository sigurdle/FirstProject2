#ifndef x3d_Collision_h
#define x3d_Collision_h

namespace System
{
namespace x3d
{

class X3DEXT Collision :
	public X3DSensorNode,

	public RenderImplImpl
{
public:
	CTOR Collision();
	~Collision();

	virtual void Draw(X3DDrawContext* pDC);
	virtual void DrawOverlay(X3DDrawContext* pDC);

	MFNode* get_children() const
	{
		return m_children;
	}

	static NodeType* nodeType;
	static NodeType* GetNodeType();

protected:

	MFNode* m_children;
	TypedSFNode<X3DChildNode*>* m_proxy;
};

}	// x3d
}

#endif // x3d_Collision_h
