#include "stdafx.h"
#include "X3D2.h"
#include "CoordinateInterpolator2D.h"

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(CoordinateInterpolator2D, MFVec2f, keyValue, inputOutput)
IMP_X3DFIELD0(CoordinateInterpolator2D, MFVec2f, value_changed, inputOutput)

NodeType* CoordinateInterpolator2D::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		get_keyValueFieldDef(),
		get_value_changedFieldDef(),
	};

	static NodeType nodeType("CoordinateInterpolator2D", typeid(CoordinateInterpolator2D), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* CoordinateInterpolator2D::nodeType(GetNodeType());

CoordinateInterpolator2D::CoordinateInterpolator2D() : X3DInterpolatorNode(GetNodeType())
{
}

void CoordinateInterpolator2D::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();

		MFFloat* key = m_key;
		MFVec2f* keyValue = m_keyValue;

		int numkeys = key->m_items.GetSize();
		int numvalues = keyValue->m_items.GetSize();

		int count = numvalues / numkeys;

		if (numkeys*count == numvalues)	// must be an integer multiple
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
			double t;

			if (left != right)
			{
				t = (double)(fraction - key->m_items[left]) / (key->m_items[right] - key->m_items[left]);
			}
			else	// left = right
			{
				t = 0;
			}

			{
				int leftoffset = left*count;
				int rightoffset = right*count;

				m_value_changed->m_items.SetSize(count);

				for (int i = 0; i < count; i++)
				{
					m_value_changed->m_items[i] = keyValue->m_items[leftoffset+i] + (keyValue->m_items[rightoffset+i] - keyValue->m_items[leftoffset+i])*t;
				}
			}

			Change(m_value_changed);
		}
	}

	baseClass::OnFieldChanged(pField);
}

}	// x3d
}
