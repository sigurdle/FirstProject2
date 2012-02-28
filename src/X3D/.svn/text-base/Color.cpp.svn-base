#include "stdafx.h"
#include "X3D2.h"
#include "Color.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(Color, MFColor, color, inputOutput)

NodeType* Color::GetNodeType()
{
	static X3DFieldDefinition* ColorFields[] =
	{
		get_colorFieldDef(),
	};

	static NodeType nodeType(WSTR("Color"), typeid(Color), ColorFields, _countof(ColorFields), baseClass::GetNodeType());
	return &nodeType;
}

Color::Color() : X3DColorNode(GetNodeType())
{
}

}	// x3d
}
