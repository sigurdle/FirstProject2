#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

void MFVec2f::CopyFrom(X3DField* pFrom)
{
	m_items.RemoveAll();

	for (unsigned int i = 0; i < static_cast<MFVec2f*>(pFrom)->m_items.GetSize(); i++)
	{
		gm::vector2f v = static_cast<MFVec2f*>(pFrom)->m_items[i];
		m_items.Add(v);
	}
}

IO::TextWriter& MFVec2f::WriteValuesToStream(IO::TextWriter& stream)
{
	for (uint i = 0; i < m_items.size(); ++i)
	{
		if (i > 0) stream << ',';
		stream << m_items[i][0] << ' ' << m_items[i][1];
	}

	return stream;
}

void MFVec2f::append1Value(const float value[2])
{
	m_items.Add(gm::vector2f(value[0], value[1]));
}

}	// x3d
}	// System
