#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFColorRGBA::SFColorRGBA(X3DNode* ownerNode) : X3DField(ownerNode)
{
}

SFColorRGBA::SFColorRGBA(X3DNode* ownerNode, Vec4f value) : X3DField(ownerNode), m_value(value)
{
}

void SFColorRGBA::setValue(Vec4f value)
{
	m_value = value;
	m_ownerNode->OnFieldChanged(this);
}

IO::TextWriter& SFColorRGBA::WriteValueToStream(IO::TextWriter& stream)
{
	return stream;
}

// virtual
void SFColorRGBA::CopyFrom(X3DField* pFrom)
{
	m_value[0] = static_cast<SFColorRGBA*>(pFrom)->m_value[0];
	m_value[1] = static_cast<SFColorRGBA*>(pFrom)->m_value[1];
	m_value[2] = static_cast<SFColorRGBA*>(pFrom)->m_value[2];
	m_value[3] = static_cast<SFColorRGBA*>(pFrom)->m_value[3];

	// m_ownerNode->OnFieldChanged(this);	// ??
}

}	// x3d
}
