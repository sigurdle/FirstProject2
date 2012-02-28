#ifndef x3d_Switch_h
#define x3d_Switch_h

namespace System
{
namespace x3d
{

class X3DEXT Switch :
	public X3DGroupingNode,
	public RenderImplImpl
{
public:
	CTOR Switch();

	virtual void Draw(X3DDrawContext* pDC);

	X3DSFIELD(SFInt32, whichChoice, WhichChoice)

	X3DNODE(Switch, X3DGroupingNode)
};

}	// x3d
}

#endif // x3d_Switch_h
