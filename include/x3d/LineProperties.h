#ifndef x3d_LineProperties_h
#define x3d_LineProperties_h

namespace System
{
namespace x3d
{

class X3DEXT LineProperties : 
	public X3DAppearanceChildNode
{
public:
	CTOR LineProperties();

	static NodeType s_nodeType;
};

}	// x3d
}

#endif // x3d_LineProperties_h
