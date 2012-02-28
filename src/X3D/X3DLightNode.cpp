#include "stdafx.h"
#include "X3D2.h"
#include "X3DLightNode.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(X3DLightNode, SFBool, on, inputOutput, true);
IMP_X3DFIELD1(X3DLightNode, SFBool, global, inputOutput, true);
IMP_X3DFIELD3(X3DLightNode, SFFloat, ambientIntensity, inputOutput, 0, 0, 1)
IMP_X3DFIELD3(X3DLightNode, SFFloat, intensity, inputOutput, 1, 0, 1)
IMP_X3DFIELD1(X3DLightNode, SFColor, color, inputOutput, Vec3f(1,1,1))

NodeType* X3DLightNode::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_onFieldDef(),
		get_ambientIntensityFieldDef(),
		get_colorFieldDef(),
		get_globalFieldDef(),
		get_intensityFieldDef(),
	};

	static NodeType nodeType(nullptr, typeid(X3DLightNode), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

X3DLightNode::X3DLightNode(NodeType* nodeType, bool globalDefault) : X3DChildNode(nodeType),
	m_on(new SFBool(get_onFieldDef(), this)),
	m_global(new SFBool(get_globalFieldDef(), this, globalDefault)),
	m_ambientIntensity(new SFFloat(get_ambientIntensityFieldDef(), this)),
	m_intensity(new SFFloat(get_intensityFieldDef(), this)),
	m_color(new SFColor(get_colorFieldDef(), this))
{
}

}	// x3d
}
