#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFInt32::SFInt32(X3DFieldDefinition* fieldDef, X3DNode* ownerNode, int32 value) : X3DField(ownerNode), m_value(value)
{
}

void SFInt32::setValue(int32 newVal)
{
	m_value = newVal;
	getOwnerNode()->OnFieldChanged(this);
}

IO::TextWriter& SFInt32::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value;
	return stream;
}

}	// x3d
}
