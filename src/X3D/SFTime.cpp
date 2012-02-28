#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFTime::SFTime(X3DNode* ownerNode, double value) : X3DField(ownerNode), m_value(value)
{
}

SFTime::SFTime(TypedX3DFieldDefinition<SFTime>* fieldDef, X3DNode* ownerNode) : X3DField(fieldDef, ownerNode), m_value(fieldDef->getDefaultValue())
{
}

void SFTime::setValue(double newVal)
{
	m_value = newVal;
	getOwnerNode()->OnFieldChanged(this);
}

IO::TextWriter& SFTime::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value;
	return stream;
}

// virtual
void SFTime::CopyFrom(X3DField* pFrom)
{
	m_value = static_cast<SFTime*>(pFrom)->m_value;
}

}	// x3d
}	// System
