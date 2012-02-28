#ifndef x3d_Material2D_h
#define x3d_Material2D_h

namespace System
{
namespace x3d
{

class X3DEXT Material2D : 
	public X3DMaterialNode
{
public:
	CTOR Material2D();

	/*
	SFColor exposedField emissiveColor 0.8,0.8,0.8 
	SFBool exposedField filled FALSE 
	SFNode exposedField lineProps NULL 
	SFFloat exposedField transparency 0.0 
  */

	virtual int ApplyMaterial(X3DDrawContext* pDC) override;

	X3DSFIELD(SFColor, emissiveColor, EmissiveColor)
	X3DSFIELD(SFBool, filled, Filled)
//	X3DSFIELD(SFNode, lineProps, LineProps)
	X3DSFIELD(SFFloat, transparency, Transparency)

	static NodeType* GetNodeType();

private:

	static NodeType* nodeType;
};

}	// x3d
}

#endif // x3d_Material2D_h
