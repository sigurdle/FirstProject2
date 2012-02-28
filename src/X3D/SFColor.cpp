#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFColor::SFColor(X3DNode* ownerNode) : X3DField(ownerNode)
{
}

SFColor::SFColor(TypedX3DFieldDefinition<SFColor>* fieldDef, X3DNode* ownerNode) : X3DField(fieldDef, ownerNode), m_value(fieldDef->getDefaultValue())
{
}

SFColor::SFColor(TypedX3DFieldDefinition<SFColor>* fieldDef, X3DNode* ownerNode, Vec3f value) : X3DField(fieldDef, ownerNode), m_value(value)
{
}

void SFColor::setValue(/*[in]*/ const float value[3])
{
	m_value[0] = value[0];
	m_value[1] = value[1];
	m_value[2] = value[2];

	m_ownerNode->OnFieldChanged(this);
}

void SFColor::setValue(Vec3f value)
{
	m_value = value;
	m_ownerNode->OnFieldChanged(this);
}

// virtual
void SFColor::CopyFrom(X3DField* pFrom)
{
	m_value[0] = static_cast<SFColor*>(pFrom)->m_value[0];
	m_value[1] = static_cast<SFColor*>(pFrom)->m_value[1];
	m_value[2] = static_cast<SFColor*>(pFrom)->m_value[2];
}

IO::TextWriter& SFColor::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value[0] << ' ' << m_value[1] << ' ' << m_value[2];
	return stream;
}

}	// x3d
}
