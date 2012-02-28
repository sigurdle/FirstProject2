namespace System
{
namespace x3d
{

class X3DEXT TextureProperties : public X3DNode
{
public:
	CTOR TextureProperties();

	X3DSFIELD(SFColorRGBA, borderColor, BorderColor)
	X3DSFIELD(SFString, boundaryModeS, BoundaryModeS)
	X3DSFIELD(SFString, boundaryModeT, BoundaryModeT)
	X3DSFIELD(SFString, boundaryModeR, BoundaryModeR)
	X3DSFIELD(SFFloat, anisotropicDegree, AnisotropicDegree)
	X3DSFIELD(SFString, magnificationFilter, MagnificationFilter)
	X3DSFIELD(SFString, minificationFilter, MinificationFilter)
	X3DSFIELD(SFBool, generateMipMaps, GenerateMipMaps)

	X3DNODE(TextureProperties, X3DNode)
};

}
}
