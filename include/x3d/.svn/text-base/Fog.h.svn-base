#ifndef x3d_Fog_h
#define x3d_Fog_h

namespace System
{
namespace x3d
{

class X3DEXT Fog : public X3DBindableNode, public X3DFogObject
{
public:
	CTOR Fog();

	void Apply(X3DDrawContext* pDC);

	X3DSFIELD(SFFloat, visibilityRange, VisibilityRange)
	X3DSFIELD(SFColor, color, Color)
	X3DSFIELD(SFString, fogType, FogType)

	X3DNODE(Fog, X3DBindableNode)
};

}	// x3d
}	// System

#endif // x3d_Fog_h
