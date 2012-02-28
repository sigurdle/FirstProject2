#include "stdafx.h"
#include "X3D2.h"
#include "CoordinateInterpolator.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* CoordinateInterpolatorFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("key", FieldType_MFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("keyValue", FieldType_MFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("set_fraction", FieldType_SFFloat, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("value_changed", FieldType_MFVec3f, SAIFieldAccess_outputOnly,-1),
	/*
	SFFloat [in]     set_fraction       (-8,8)
	MFFloat [in,out] key           []   (-8,8)
	MFVec3f [in,out] keyValue      []   (-8,8)
	SFNode  [in,out] metadata      NULL [X3DMetadataObject]
	MFVec3f [out]    value_changed
	*/
};

NodeType CoordinateInterpolator::s_nodeType(WSTR("CoordinateInterpolator"), typeid(CoordinateInterpolator), CoordinateInterpolatorFields, _countof(CoordinateInterpolatorFields));

CoordinateInterpolator::CoordinateInterpolator() : X3DInterpolatorNode(&s_nodeType)
{
}

void CoordinateInterpolator::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();

		MFFloat* key = m_key;
		MFVec3f* keyValue = m_keyValue;

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

				m_valueChanged->m_items.SetSize(count);

				for (int i = 0; i < count; i++)
				{
					m_valueChanged->m_items[i] = keyValue->m_items[leftoffset+i] + (keyValue->m_items[rightoffset+i] - keyValue->m_items[leftoffset+i])*t;
				}
			}

			Change(m_valueChanged);
		}
	}
}

}	// x3d
}
