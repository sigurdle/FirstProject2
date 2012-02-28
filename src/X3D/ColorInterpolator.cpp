#include "stdafx.h"
#include "X3D2.h"
#include "ColorInterpolator.h"

namespace System
{
namespace x3d
{

TypedX3DFieldDefinition<MFColor>* ColorInterpolator::get_keyValueFieldDef()
{
	static TypedX3DFieldDefinition<MFColor> keyValue("keyValue", SAIFieldAccess_inputOutput, offsetof(ColorInterpolator, m_keyValue));
	return &keyValue;
}

TypedX3DFieldDefinition<SFColor>* ColorInterpolator::get_valueChangedFieldDef()
{
	static TypedX3DFieldDefinition<SFColor> value_changed("value_changed", SAIFieldAccess_outputOnly, offsetof(ColorInterpolator, m_valueChanged));
	return &value_changed;
}

NodeType* ColorInterpolator::GetNodeType()
{
	static X3DFieldDefinition* ColorInterpolatorFields[] =
	{
		get_keyValueFieldDef(),
		get_valueChangedFieldDef(),

		/*
		SFFloat [in]     set_fraction     (-8,8)
		MFFloat [in,out] key           [] (-8,8)
		MFColor [in,out] keyValue      [] [0,1]
		SFColor [out]    value_changed
		*/
	};

	static NodeType nodeType(WSTR("ColorInterpolator"), typeid(ColorInterpolator), ColorInterpolatorFields, _countof(ColorInterpolatorFields), X3DInterpolatorNode::GetNodeType());
	return &nodeType;
}

ColorInterpolator::ColorInterpolator() : X3DInterpolatorNode(GetNodeType())
{
}

void ColorInterpolator::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();

		MFFloat* key = m_key;
		MFColor* keyValue = m_keyValue;

		int numkeys = key->m_items.GetSize();
		int numvalues = keyValue->m_items.GetSize();

		if (numkeys == numvalues)
		{
			int left = -1;
			int right = -1;

			for (int i = 0; i < numkeys; i++)
			{
				if (key->m_items[i] <= fraction) left = i;
				else if (key->m_items[i] > fraction) break;
			}

			right = left+1;

			if (left < 0) left = 0;
			if (right > numkeys-1) right = numkeys-1;

			// Linear
			float t;

			if (left != right)
			{
				t = (float)(fraction - key->m_items[left]) / (key->m_items[right] - key->m_items[left]);
			}
			else	// left = right
			{
				t = 0;
			}

			gm::vector3f& v0 = keyValue->m_items[left];
			gm::vector3f& v1 = keyValue->m_items[right];

			static_cast<SFColor*>(m_valueChanged)->m_value[0] = v0[0] + (v1[0] - v0[0])*t;
			static_cast<SFColor*>(m_valueChanged)->m_value[1] = v0[1] + (v1[1] - v0[1])*t;
			static_cast<SFColor*>(m_valueChanged)->m_value[2] = v0[2] + (v1[2] - v0[2])*t;

			Change(m_valueChanged);
		}
	}

	X3DInterpolatorNode::OnFieldChanged(pField);
}

}	// x3d
}
