#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFVec3f::SFVec3f(X3DNode* owner) : X3DField(NULL, owner)
{
}

SFVec3f::SFVec3f(TypedX3DFieldDefinition<SFVec3f>* def, X3DNode* owner, Vec3f value) : X3DField(def, owner), m_value(value)
{
}

SFVec3f::SFVec3f(TypedX3DFieldDefinition<SFVec3f>* def, X3DNode* owner) : X3DField(def, owner), m_value(def->getDefaultValue())
{
}

void SFVec3f::setValue(Vec3f value)
{
	m_value = value;
	getOwnerNode()->OnFieldChanged(this);
}

void SFVec3f::setValue(float x, float y, float z)
{
	m_value[0] = x;
	m_value[1] = y;
	m_value[2] = z;
	getOwnerNode()->OnFieldChanged(this);
}

IO::TextWriter& SFVec3f::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value[0] << ' ' << m_value[1] << ' ' << m_value[2];
	return stream;
}

}	// x3d
}
