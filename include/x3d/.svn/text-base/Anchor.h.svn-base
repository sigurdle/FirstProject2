#ifndef x3d_Anchor_h
#define x3d_Anchor_h

namespace System
{
namespace x3d
{

class X3DEXT Anchor :
	public X3DGroupingNode,
	public RenderImplImpl
{
public:
	CTOR Anchor();
	~Anchor();

	virtual void Draw(X3DDrawContext* pDC);
	virtual void DrawOverlay(X3DDrawContext* pDC);

	static NodeType* GetNodeType();
	static NodeType* nodeType;

	/*
	MFNode* get_children()
	{
		return m_children;
	}
	*/

	/*
protected:

	MFNode* m_children;
	*/

private:

	MFString* m_url;
};

}	// x3d
}

#endif // x3d_Anchor_h
