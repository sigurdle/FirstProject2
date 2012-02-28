#include "stdafx.h"
#include "X3D2.h"
#include "SplineScalarInterpolator.h"

namespace System
{
namespace x3d
{

//IMP_X3DFIELD0(SplineScalarInterpolator, MFFloat, keyValue, inputOutput)
//IMP_X3DFIELD0(SplineScalarInterpolator, SFFloat, value_changed, outputOnly)

IMP_X3DFIELD0(SplineScalarInterpolator, SFBool, closed, inputOutput)
IMP_X3DFIELD0(SplineScalarInterpolator, SFBool, normalizeVelocity, inputOutput)
IMP_X3DFIELD0(SplineScalarInterpolator, SFFloat, value_changed, outputOnly)
IMP_X3DFIELD0(SplineScalarInterpolator, MFFloat, keyValue, inputOutput)
IMP_X3DFIELD0(SplineScalarInterpolator, MFFloat, keyVelocity, inputOutput)

NodeType* SplineScalarInterpolator::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_keyValueFieldDef(),
		get_value_changedFieldDef(),
		get_closedFieldDef(),
		get_normalizeVelocityFieldDef(),
		get_keyVelocityFieldDef(),
	};

	static NodeType nodeType(WSTR("SplineScalarInterpolator"), typeid(SplineScalarInterpolator), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

SplineScalarInterpolator::SplineScalarInterpolator() : X3DInterpolatorNode(GetNodeType())
{
}

void SplineScalarInterpolator::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();
		int numkeys = m_key->m_items.GetSize();
		int numvalues = m_keyValue->m_items.GetSize();

		MFFloat* keyVelocity = getKeyVelocityField();

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

			float t0;
			float t1;

			if (keyVelocity->get_size() == 2)
			{
				t0 = keyVelocity->get1Value(0);
				t1 = keyVelocity->get1Value(1);
			}
			else if (keyVelocity->get_size() == numvalues)
			{
				t0 = keyVelocity->get1Value(left);
				t1 = keyVelocity->get1Value(right);
			}

#if 0
			LDraw::matrix4f::catmullromBasis(
matrix4f(-1,  3, -3,  1,
		    2, -5,  4, -1,
		   -1,  0,  1,  0,
		    0,  2,  0,  0);

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
#endif
		}
	}

	baseClass::OnFieldChanged(pField);
}

}	// x3d
}
