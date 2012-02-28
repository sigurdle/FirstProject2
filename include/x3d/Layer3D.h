#ifndef x3d_Layer3D_h
#define x3d_Layer3D_h

namespace System
{
namespace x3d
{

// Part of MPEG-4
class Layer3D :	// MPEG-4
	public X3DGroupingNode, //	public X3DBoundedObject,

	public RenderImplImpl
{
public:
	CTOR Layer3D();

	virtual void Draw(X3DDrawContext* pDC);

	static NodeType s_nodeType;
};

}	// x3d
}

#endif // x3d_Layer3D_h
