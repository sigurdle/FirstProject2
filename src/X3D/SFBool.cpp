#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

SFBool::SFBool(X3DNode* ownerNode, bool value) : X3DField(ownerNode), m_value(value)
{
}

SFBool::SFBool(TypedX3DFieldDefinition<SFBool>* fieldDef, X3DNode* ownerNode) : X3DField(fieldDef, ownerNode), m_value(fieldDef->getDefaultValue())
{
}

SFBool::SFBool(TypedX3DFieldDefinition<SFBool>* fieldDef, X3DNode* ownerNode, bool value) : X3DField(fieldDef, ownerNode), m_value(value)
{
}

IO::TextWriter& SFBool::WriteValueToStream(IO::TextWriter& stream)
{
	stream << (m_value? "TRUE": "FALSE");
	return stream;
}

// virtual
void SFBool::CopyFrom(X3DField* pFrom)
{
	m_value = static_cast<SFBool*>(pFrom)->m_value;
}

void SFBool::setValue(bool newVal)
{
	m_value = newVal;
	m_ownerNode->OnFieldChanged(this);
}

}	// x3d
}
