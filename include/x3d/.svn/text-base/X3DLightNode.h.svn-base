#ifndef x3d_X3DLightNode_h
#define x3d_X3DLightNode_h

namespace System
{
namespace x3d
{

class X3DEXT X3DLightNode : public X3DChildNode
{
public:

	X3DSFIELD(SFBool, on, On)
	X3DSFIELD(SFBool, global, Global)
	X3DSFIELD(SFColor, color, Color)
	X3DSFIELD(SFFloat, intensity, Intensity)
	X3DSFIELD(SFFloat, ambientIntensity, AmbientIntensity)

	X3DNODE_ABSTRACT(X3DLightNode, X3DChildNode)

	virtual uint32 GetLights() override
	{
		return 1;
	}

protected:

	CTOR X3DLightNode(NodeType* nodeType, bool globalDefault);
};

}
}

#endif // x3d_X3DLightNode_h
