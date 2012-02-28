#include "stdafx.h"
#include "X3D2.h"
#include "MFColor.h"

namespace System
{
namespace x3d
{

MFColor::MFColor(X3DNode* ownerNode) : X3DArrayField(ownerNode)
{
}

MFColor::MFColor(TypedX3DFieldDefinition<MFColor>* fieldDef, X3DNode* ownerNode) :
	X3DArrayField(fieldDef, ownerNode),
	m_items(fieldDef->getDefaultValue())
{
}

void MFColor::CopyFrom(X3DField* pFrom)
{
	MFColor* mf = static_cast<MFColor*>(pFrom);

	m_items.SetSize(mf->m_items.GetSize());

	for (size_t i = 0; i < mf->m_items.size(); ++i)
	{
		m_items[i] = mf->m_items[i];
	}
}

Vec3f MFColor::get1Value(size_t index) const throw (ArgumentOutOfRangeException*)
{
	if (index >= m_items.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	return m_items[index];
}

void MFColor::set1Value(size_t index, Vec3f value) throw (ArgumentOutOfRangeException*)
{
	if (index >= m_items.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	m_items[index] = value;
	getOwnerNode()->OnFieldChanged(this);
}

void MFColor::append1Value(Vec3f value)
{
	if (value == NULL)
		raise(ArgumentNullException());

	m_items.push_back(value);
	getOwnerNode()->OnFieldChanged(this);
}

/*
void MFColor::append1Value(const float value[3])
{
	if (value == NULL)
		raise(ArgumentNullException());

	m_items.push_back(Vec3f(value[0], value[1], value[2]));

	getOwnerNode()->OnFieldChanged(this);
}
*/

IO::TextWriter& MFColor::WriteValuesToStream(IO::TextWriter& stream)
{
	for (uint i = 0; i < m_items.size(); ++i)
	{
		Vec3f value = m_items[i];
		if (i > 0) stream << ',';
		stream << value[0] << " " << value[1] << " " << value[2];
	}

	return stream;
}

// X3DArrayField
size_t MFColor::get_size() const
{
	return m_items.GetSize();
}

}	// x3d
}	// System
