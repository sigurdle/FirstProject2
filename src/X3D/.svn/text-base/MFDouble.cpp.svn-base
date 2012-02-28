#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

void MFDouble::CopyFrom(X3DField* pFrom)
{
	ASSERT(0);
}

double MFDouble::get1Value(size_t index) const
{
	if (index >= m_items.GetSize()) raise(ArgumentOutOfRangeException());

	return m_items[index];
}

void MFDouble::set1Value(size_t index, double newVal)
{
	if (index >= m_items.GetSize()) raise(ArgumentOutOfRangeException());

	m_items[index] = newVal;
	// TODO event
}

void MFDouble::append1Value(double value)
{
	m_items.Add(value);
	// TODO event
}

}	// x3d
}	// System
