#include "stdafx.h"
#include "X3D2.h"
#include "NavigationInfo.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD1(NavigationInfo, MFFloat, avatarSize, inputOutput, vector<float>(0.25f, 1.6f, 0.75f))
IMP_X3DFIELD1(NavigationInfo, SFBool, headlight, inputOutput, true)
IMP_X3DFIELD3(NavigationInfo, SFFloat, speed, inputOutput, 1.0f, 0.0f, FLT_MAX)
IMP_X3DFIELD1(NavigationInfo, MFString, type, inputOutput, vector<String>(L"WALK", L"ANY"))
IMP_X3DFIELD3(NavigationInfo, SFFloat, visibilityLimit, inputOutput, 0.0f, 0.0f, FLT_MAX)

NodeType* NavigationInfo::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_avatarSizeFieldDef(),
		get_headlightFieldDef(),
		get_speedFieldDef(),
		get_typeFieldDef(),
		get_visibilityLimitFieldDef(),
	};

	static NodeType nodeType(WSTR("NavigationInfo"), typeid(NavigationInfo), fields, _countof(fields), X3DBindableNode::GetNodeType());
	return &nodeType;
}

NodeType* NavigationInfo::nodeType(GetNodeType());

NavigationInfo::NavigationInfo() :
	X3DBindableNode(GetNodeType()),

	m_avatarSize(new MFFloat(get_avatarSizeFieldDef(), this)),
	m_headlight(new SFBool(get_headlightFieldDef(), this)),
	m_speed(new SFFloat(get_speedFieldDef(), this)),
	m_type(new MFString(get_typeFieldDef(), this))
{
}

}	// x3d
}
