#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFFloat::SFFloat(X3DNode* ownerNode, float value) : X3DField(ownerNode), m_value(value)
{
}

SFFloat::SFFloat(TypedX3DFieldDefinition<SFFloat>* fieldDef, X3DNode* ownerNode, float value) : X3DField(fieldDef, ownerNode), m_value(value)
{
}

SFFloat::SFFloat(TypedX3DFieldDefinition<SFFloat>* fieldDef, X3DNode* ownerNode) : X3DField(fieldDef, ownerNode), m_value(fieldDef->getDefaultValue())
{
}

void SFFloat::setValue(float newVal)
{
	m_value = newVal;
	getOwnerNode()->OnFieldChanged(this);
}

IO::TextWriter& SFFloat::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value;
	return stream;
}

}	// x3d
}
