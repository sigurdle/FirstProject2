#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

IO::TextWriter& MFFloat::WriteValuesToStream(IO::TextWriter& stream)
{
	uint nitems = m_items.size();
	for (uint i = 0; i < nitems; ++i)
	{
		if (i > 0) stream << ',';
		stream << m_items[i];
	}

	return stream;
}

void MFFloat::CopyFrom(X3DField* pFrom)
{
	MFFloat* mf = static_cast<MFFloat*>(pFrom);

	m_items.SetSize(mf->m_items.GetSize());

	for (size_t i = 0; i < mf->m_items.GetSize(); ++i)
	{
		m_items[i] = mf->m_items[i];
	}
}

float MFFloat::get1Value(size_t index) const
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
		return 0;
	}
}

void MFFloat::set1Value(size_t index, float newVal)
{
	if (index < m_items.GetSize())
	{
		m_items[index] = newVal;
		// TODO event
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

void MFFloat::append1Value(float value)
{
	m_items.Add(value);
	// TODO event
}

}	// x3d
}	// System
