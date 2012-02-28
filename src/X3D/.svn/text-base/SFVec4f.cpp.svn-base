#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFVec4f::SFVec4f(X3DNode* owner) : X3DField(owner)
{
}

SFVec4f::SFVec4f(TypedX3DFieldDefinition<SFVec4f>* def, X3DNode* owner) : X3DField(def, owner), m_value(def->getDefaultValue())
{
}

SFVec4f::SFVec4f(TypedX3DFieldDefinition<SFVec4f>* def, X3DNode* owner, Vec4f value) : X3DField(def, owner), m_value(value)
{
}

void SFVec4f::setValue(Vec4f value)
{
	m_value = value;
	m_ownerNode->OnFieldChanged(this);
}

void SFVec4f::setValue(float x, float y, float z, float w)
{
	m_value[0] = x;
	m_value[1] = y;
	m_value[2] = z;
	m_value[3] = w;
	m_ownerNode->OnFieldChanged(this);
}

IO::TextWriter& SFVec4f::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value[0] << ' ' << m_value[1] << ' ' << m_value[2] << ' ' << m_value[3];
	return stream;
}

}	// x3d
}
