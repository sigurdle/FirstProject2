#ifndef x3d_Color_h
#define x3d_Color_h

namespace System
{
namespace x3d
{

class X3DEXT Color : 
	public X3DColorNode
{
public:
	CTOR Color();

	X3DMFIELD(MFColor, color, Color)

	X3DNODE(Color, X3DColorNode)
};

}	// x3d
}	// System

#endif // x3d_Color_h
