#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFVec2f::SFVec2f(const SFVec2f& other) : X3DField(other), m_value(other.getValue())
{
}

SFVec2f::SFVec2f(X3DNode* ownerNode, Vec2f value) : X3DField(ownerNode), m_value(value)
{
}

SFVec2f::SFVec2f(X3DFieldDefinition* fieldDef, X3DNode* ownerNode, Vec2f value) : X3DField(fieldDef, ownerNode), m_value(value)
{
}

IO::TextWriter& SFVec2f::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value[0] << ' ' << m_value[1];
	return stream;
}

}	// x3d
}	// System
