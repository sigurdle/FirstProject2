#include "stdafx.h"
#include "X3D2.h"
#include "MFString.h"

namespace System
{
namespace x3d
{

MFString::MFString(X3DNode* ownerNode) : X3DArrayField(ownerNode)
{
}

MFString::MFString(TypedX3DFieldDefinition<MFString>* fieldDef, X3DNode* ownerNode) : X3DArrayField(fieldDef, ownerNode),
	m_items(fieldDef->getDefaultValue())
{
}

MFString::MFString(X3DFieldDefinition* def, X3DNode* ownerNode, StringIn item0) : X3DArrayField(def, ownerNode)
{
	m_items.push_back(item0);
}

MFString::MFString(X3DFieldDefinition* def, X3DNode* ownerNode, StringIn item0, StringIn item1) : X3DArrayField(def, ownerNode)
{
	m_items.push_back(item0);
	m_items.push_back(item1);
}

IO::TextWriter& MFString::WriteValuesToStream(IO::TextWriter& stream)
{
	for (uint i = 0; i < m_items.size(); ++i)
	{
		if (i > 0) stream << ',';
		stream << "\"" << m_items[i] << "\"";
	}

	return stream;
}

void MFString::CopyFrom(X3DField* pFrom)
{
	ASSERT(m_items.GetSize() == 0);

	for (unsigned int i = 0; i < static_cast<MFString*>(pFrom)->m_items.GetSize(); i++)
	{
		String from = static_cast<MFString*>(pFrom)->m_items[i];

		m_items.Add(from);
	}
}

void MFString::clear()
{
	if (m_items.size() > 0)
	{
		m_items.clear();
		getOwnerNode()->OnFieldChanged(this);
	}
}

void MFString::append1Value(StringIn value)
{
	m_items.push_back(value);
	getOwnerNode()->OnFieldChanged(this);
}

String MFString::get1Value(size_t index)
{
	if (index >= m_items.GetSize()) raise(ArgumentOutOfRangeException());
	return m_items[index];
}

}	// x3d
}	// System
