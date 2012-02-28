#include "stdafx.h"
#include "X3D2.h"
#include "SpotLight.h"

namespace System
{
namespace x3d
{

NodeType* SpotLight::GetNodeType()
{
	static X3DFieldDefinition* SpotLightFields[] =
	{
		&X3DFieldDefinition("ambientIntensity", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("attenuation", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("beamWidth", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("color", FieldType_SFColor, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("cutOffAngle", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("direction", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("intensity", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("location", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("on", FieldType_SFBool, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("radius", FieldType_SFFloat, SAIFieldAccess_inputOutput,-1),
		/*
		SFFloat [in,out] ambientIntensity 0        [0,1]
		SFVec3f [in,out] attenuation      1 0 0    [0,8)
		SFFloat [in,out] beamWidth        p/2      (0,p/2]
		SFColor [in,out] color            1 1 1    [0,1]
		SFFloat [in,out] cutOffAngle      p/4      (0,p/2]
		SFVec3f [in,out] direction        0 0 -1   (-8,8)
		SFFloat [in,out] intensity        1        [0,1]
		SFVec3f [in,out] location         0 0 0    (-8,8)
		SFBool  [in,out] on               TRUE
		SFFloat [in,out] radius           100      [0,8)
		*/
	};

	static NodeType nodeType(WSTR("SpotLight"), typeid(SpotLight), SpotLightFields, _countof(SpotLightFields), X3DLightNode::GetNodeType());
	return &nodeType;
}

SpotLight::SpotLight() : X3DLightNode(GetNodeType(), true/*globalDefault*/)
{
	// Set default values
	m_radius->m_value = 100;
}

void SpotLight::PreDraw(X3DDrawContext* pDC)
{
	if (!getGlobal() && getOn())
	{
		// TODO
	}
}

}	// x3d
}
