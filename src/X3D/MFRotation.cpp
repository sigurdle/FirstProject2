#include "stdafx.h"
#include "X3D2.h"
#include "MFRotation.h"

namespace System
{
namespace x3d
{

MFRotation::MFRotation(X3DNode* ownerNode) : X3DArrayField(ownerNode)
{
}

void MFRotation::CopyFrom(X3DField* pFrom)
{
	MFRotation* mf = static_cast<MFRotation*>(pFrom);

	m_items.SetSize(mf->m_items.GetSize());

	for (size_t i = 0; i < mf->m_items.GetSize(); ++i)
	{
		m_items[i] = mf->m_items[i];
	}
}

AxisAngle MFRotation::get1Value(size_t index)
{
	if (index >= m_items.size()) raise(ArgumentOutOfRangeException());
	return m_items[index];
}

void MFRotation::set1Value(size_t index, const AxisAngle& value)
{
	if (index >= m_items.size()) raise(ArgumentOutOfRangeException());
	m_items[index] = value;
}

void MFRotation::append1Value(const float value[4])
{
	if (value == NULL) raise(ArgumentNullException());

	m_items.Add(AxisAngle(value[0], value[1], value[2], value[3]));
}

void MFRotation::append1Value(const AxisAngle& value)
{
	m_items.Add(AxisAngle(value));
}

size_t MFRotation::get_size() const
{
	return m_items.GetSize();
}

}	// x3d
}	// System
