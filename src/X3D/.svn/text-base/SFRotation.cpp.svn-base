#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFRotation::SFRotation(X3DNode* ownerNode) : X3DField(ownerNode)
{
}

SFRotation::SFRotation(X3DNode* ownerNode, Rotation value) : X3DField(ownerNode), m_value(value)
{
}

SFRotation::SFRotation(TypedX3DFieldDefinition<SFRotation>* fieldDef, X3DNode* ownerNode) : X3DField(fieldDef, ownerNode)
{
}

// virtual
void SFRotation::CopyFrom(X3DField* pFrom)
{
	m_value = static_cast<SFRotation*>(pFrom)->m_value;
}

Rotation SFRotation::getValue() const
{
	return m_value;
}

void SFRotation::getValue(/*[in, out]*/ float value[4]) const
{
	value[0] = m_value.m_axis[0];
	value[1] = m_value.m_axis[1];
	value[2] = m_value.m_axis[2];
	value[3] = m_value.m_angle;
}

void SFRotation::setValue(float const value[4])
{
	m_value.m_axis[0] = value[0];
	m_value.m_axis[1] = value[1];
	m_value.m_axis[2] = value[2];
	m_value.m_angle = value[3];

	getOwnerNode()->OnFieldChanged(this);
}

void SFRotation::setValue(Rotation value)
{
	m_value = value;
	getOwnerNode()->OnFieldChanged(this);
}

IO::TextWriter& SFRotation::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value.m_angle << ' ';
	stream << m_value.m_axis[0] << ' ' << m_value.m_axis[1] << ' ' << m_value.m_axis[2];
	return stream;
}

}	// x3d
}
