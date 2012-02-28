#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

MFInt32::MFInt32(X3DNode* ownerNode) : X3DArrayField(ownerNode)
{
}

MFInt32::MFInt32(TypedX3DFieldDefinition<MFInt32>* fieldDef, X3DNode* ownerNode) : X3DArrayField(fieldDef, ownerNode)
{
}

int32 MFInt32::get1Value(size_t index) const throw(ArgumentOutOfRangeException*)
{
	if (index >= m_items.GetSize())
	{
		raise(ArgumentOutOfRangeException());
	}

	return m_items[index];
}

void MFInt32::append1Value(int32 value)
{
	m_items.Add(value);
}

IO::TextWriter& MFInt32::WriteValuesToStream(IO::TextWriter& stream)
{
	for (uint i = 0; i < m_items.size(); ++i)
	{
		if (i > 0) stream << ',';
		stream << m_items[i];
	}

	return stream;
}

// virtual
void MFInt32::CopyFrom(X3DField* pFrom)
{
	ASSERT(m_items.GetSize() == 0);

	for (size_t i = 0; i < static_cast<MFInt32*>(pFrom)->m_items.GetSize(); ++i)
	{
		int32 v = static_cast<MFInt32*>(pFrom)->m_items[i];
		m_items.Add(v);
	}
}

}	// x3d
}
