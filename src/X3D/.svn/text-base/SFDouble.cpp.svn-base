#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFDouble::SFDouble(X3DNode* ownerNode) : X3DField(ownerNode)
{
	m_value = 0;
}

SFDouble::SFDouble(X3DNode* ownerNode, double value) : X3DField(ownerNode), m_value(value)
{
}

// virtual
void SFDouble::CopyFrom(X3DField* pFrom)
{
	m_value = static_cast<SFDouble*>(pFrom)->m_value;
}

void SFDouble::setValue(double newVal)
{
	m_value = newVal;
	m_ownerNode->OnFieldChanged(this);
}


IO::TextWriter& SFDouble::WriteValueToStream(IO::TextWriter& stream)
{
	stream << m_value;
	return stream;
}

}	// x3d
}
