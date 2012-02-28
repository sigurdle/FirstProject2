#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(WorldInfo, MFString, info, initializeOnly)
IMP_X3DFIELD0(WorldInfo, SFString, title, initializeOnly)

NodeType* WorldInfo::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_infoFieldDef(),
		get_titleFieldDef(),
	};

	static NodeType nodeType(WSTR("WorldInfo"), typeid(WorldInfo), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* WorldInfo::nodeType(GetNodeType());

WorldInfo::WorldInfo() : X3DInfoNode(GetNodeType()),
	m_info(new MFString(get_infoFieldDef(), this)),
	m_title(new SFString(get_titleFieldDef(), this))
{
}

}	// x3d
}	// System
