#ifndef x3d_LOD_h
#define x3d_LOD_h

namespace System
{
namespace x3d
{

class X3DEXT LOD :
	public X3DGroupingNode,
	//public X3DBoundedObject,

	public RenderImplImpl
{
public:
	CTOR LOD();

	virtual void Draw(X3DDrawContext* pDC);

//	X3DMFIELD(MFNode, level, Level)
	X3DMFIELD(MFFloat, range, Range)
	X3DSFIELD(SFVec3f, center, Center)

	X3DNODE(X3DGroupingNode, X3DGroupingNode)

	/*
	MFNode* get_children()
	{
		return m_children;
	}
	*/

	/*
public:

	MFNode* m_children;
	*/
};

}	// x3d
}	// System

#endif // x3d_LOD_h
