#ifndef x3d_Transform2D_h
#define x3d_Transform2D_h

namespace System
{
namespace x3d
{

class X3DEXT Transform2D :	// MPEG-4
	public X3DGroupingNode,
	//public X3DBoundedObject,

//	public X3DNode,
	public RenderImplImpl
{
public:
	CTOR Transform2D();

	virtual void Draw(X3DDrawContext* pDC);

	/*
	MFNode* get_children()
	{
		return m_children;
	}
	*/

	X3DNODE(Transform2D, X3DGroupingNode)

protected:
/*
P' = T * C * R * SR * S * -SR * -C * P

center           C
rotation         R
scale            S
scaleOrientation SR
translation      T
*/

	SFVec2f* m_C;
	SFFloat* m_R;
	SFVec2f* m_S;
	SFFloat* m_SR;
	SFVec2f* m_T;
//	MFNode* m_children;

};

}	// x3d
}	// System

#endif // x3d_Transform2D_h
