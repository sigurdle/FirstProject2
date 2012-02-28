#ifndef x3d_Background2D_h
#define x3d_Background2D_h

namespace System
{
namespace x3d
{

class X3DEXT Background2D :	// BIFS MPEG4
	public X3DBackgroundNode
{
public:
	CTOR Background2D();

	X3DSFIELD(SFColor, backColor, BackColor)

	X3DNODE(Background2D, X3DBackgroundNode)
};

}	// x3d
}	// System

#endif // x3d_Background2D_h
