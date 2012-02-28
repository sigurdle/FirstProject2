#include "stdafx.h"
#include "X3D2.h"
#include "MFVec3f.h"

namespace System
{
namespace x3d
{

MFVec3f::MFVec3f(TypedX3DFieldDefinition<MFVec3f>* fieldDef, X3DNode* ownerNode) : X3DArrayField(fieldDef, ownerNode), m_items(fieldDef->getDefaultValue())
{
}

Vec3f MFVec3f::get1Value(size_t index) const
{
	if (index >= m_items.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	return m_items[index];
}

void MFVec3f::append1Value(Vec3f value)
{
	m_items.push_back(value);
}

void MFVec3f::CopyFrom(X3DField* pFrom)
{
	MFVec3f* mfvec = static_cast<MFVec3f*>(pFrom);

	m_items.SetSize(mfvec->m_items.GetSize());

	for (size_t i = 0; i < mfvec->m_items.GetSize(); ++i)
	{
		m_items[i] = mfvec->m_items[i];
	}
}

IO::TextWriter& MFVec3f::WriteValuesToStream(IO::TextWriter& stream)
{
	for (size_t i = 0; i < m_items.size(); ++i)
	{
		if (i > 0) stream << ',';
		stream << m_items[i][0] << ' ' << m_items[i][1] << ' ' << m_items[i][2];
	}

	return stream;
}

}	// x3d
}	// System
