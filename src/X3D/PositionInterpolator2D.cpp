#include "stdafx.h"
#include "X3D2.h"
#include "PositionInterpolator2D.h"

namespace System
{
namespace x3d
{

NodeType* PositionInterpolator2D::GetNodeType()
{
	static X3DFieldDefinition* PositionInterpolator2DFields[] =
	{
		&X3DFieldDefinition("keyValue", FieldType_MFVec2f, SAIFieldAccess_inputOutput,-1),
		&X3DFieldDefinition("value_changed", FieldType_SFVec2f, SAIFieldAccess_outputOnly,-1),
		/*
		SFFloat [in]     set_fraction     (-8,8)
		MFFloat [in,out] key           [] (-8,8)
		MFVec2f [in,out] keyValue      [] (-8,8)
		SFVec2f [out]    value_changed
		*/
	};

	static NodeType nodeType("PositionInterpolator2D", typeid(PositionInterpolator2D), PositionInterpolator2DFields, _countof(PositionInterpolator2DFields));
	return &nodeType;
}

PositionInterpolator2D::PositionInterpolator2D() : X3DInterpolatorNode(GetNodeType())
{
// Cache pointers to relevant fields
//	m_key = static_cast<MFFloat*>(getField(WSTR("key")));
	m_keyValue = static_cast<MFVec2f*>(getField(WSTR("keyValue")));
//	m_setFraction = static_cast<SFFloat*>(getField(WSTR("set_fraction")));
	m_valueChanged = static_cast<SFVec2f*>(getField(WSTR("value_changed")));
}

PositionInterpolator2D::~PositionInterpolator2D()
{
}

void PositionInterpolator2D::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();

		int numkeys = m_key->get_size();
		int numvalues = m_keyValue->get_size();

		if (numkeys == numvalues)
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

			gm::vector2f& v0 = m_keyValue->m_items[left];
			gm::vector2f& v1 = m_keyValue->m_items[right];

			m_valueChanged->m_value[0] = v0[0] + (v1[0] - v0[0])*t;
			m_valueChanged->m_value[1] = v0[1] + (v1[1] - v0[1])*t;

			Change(m_valueChanged);
		}
	}
}

}	// x3d
}
