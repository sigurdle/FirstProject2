#include "stdafx.h"
#include "X3D2.h"
#include "PositionInterpolator.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(PositionInterpolator, MFVec3f, keyValue, inputOutput)
IMP_X3DFIELD0(PositionInterpolator, SFVec3f, value_changed, outputOnly)

NodeType* PositionInterpolator::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_keyValueFieldDef(),
		get_value_changedFieldDef(),
		/*
		SFFloat [in]     set_fraction     (-8,8)
		MFFloat [in,out] key           [] (-8,8)
		MFVec3f [in,out] keyValue      [] (-8,8)
		SFVec3f [out]    value_changed
		*/
	};

	static NodeType nodeType(WSTR("PositionInterpolator"), typeid(PositionInterpolator), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* PositionInterpolator::nodeType(GetNodeType());

PositionInterpolator::PositionInterpolator() : X3DInterpolatorNode(GetNodeType())
{
}

void PositionInterpolator::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();

		int numkeys = m_key->get_size();
		int numvalues = m_keyValue->get_size();

		if (numkeys == numvalues)	// must be an integer multiple
		{
			int left = -1;
			int right = -1;

			for (int i = 0; i < numkeys; i++)
			{
				if (m_key->m_items[i] <= fraction) left = i;
				else if (m_key->m_items[i] > fraction) break;
			}

			right = left+1;

			if (left < 0) left = 0;
			if (right > numkeys-1) right = numkeys-1;

			// Linear
			float t;

			if (left != right)
			{
				t = (fraction - m_key->m_items[left]) / (m_key->m_items[right] - m_key->m_items[left]);
			}
			else	// left = right
			{
				t = 0;
			}

			Vec3f v0 = m_keyValue->m_items[left];
			Vec3f v1 = m_keyValue->m_items[right];

			m_value_changed->m_value = v0 + (v1 - v0)*t;
		//	m_value_changed->m_value[1] = v0[1] + (v1[1] - v0[1])*t;
		//	m_value_changed->m_value[2] = v0[2] + (v1[2] - v0[2])*t;

			Change(m_value_changed);
		}
	}

	X3DInterpolatorNode::OnFieldChanged(pField);
}

}	// x3d
}
