#include "stdafx.h"
#include "X3D2.h"
#include "ScalarInterpolator.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(ScalarInterpolator, MFFloat, keyValue, inputOutput)
IMP_X3DFIELD0(ScalarInterpolator, SFFloat, value_changed, outputOnly)

NodeType* ScalarInterpolator::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_keyValueFieldDef(),
		get_value_changedFieldDef(),
		/*
		SFFloat [in]     set_fraction       (-8,8)
		MFFloat [in,out] key           []   (-8,8)
		MFFloat [in,out] keyValue      []   (-8,8)
		SFNode  [in,out] metadata      NULL [X3DMetadataObject]
		SFFloat [out]    value_changed
		*/
	};

	static NodeType nodeType(WSTR("ScalarInterpolator"), typeid(ScalarInterpolator), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

ScalarInterpolator::ScalarInterpolator() : X3DInterpolatorNode(GetNodeType())
{
}

void ScalarInterpolator::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();

		int numkeys = m_key->m_items.GetSize();
		int numvalues = m_keyValue->m_items.GetSize();

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
			double t;

			if (left != right)
			{
			//	t = (double)(fraction - static_cast<SFFloat*>(<ILSFFloat>(key->m_items[left]).p)->m_v) / (double)(static_cast<SFFloat*>(<ILSFFloat>(key->m_items[right]).p)->m_v - static_cast<SFFloat*>(<ILSFFloat>(key->m_items[left]).p)->m_v);
				t = (fraction - m_key->m_items[left]) / (m_key->m_items[right] - m_key->m_items[left]);
			}
			else	// left = right
			{
				t = 0;
			}

			float v0 = m_keyValue->m_items[left];
			float v1 = m_keyValue->m_items[right];

			m_value_changed->m_value = v0 + (v1 - v0)*t;

			Change(m_value_changed);
		}
	}

	baseClass::OnFieldChanged(pField);
}

}	// x3d
}
