#include "stdafx.h"
#include "X3D2.h"
#include "OrientationInterpolator.h"

namespace System
{
namespace x3d
{

NodeType* OrientationInterpolator::nodeType(GetNodeType());

NodeType* OrientationInterpolator::GetNodeType()
{
	static X3DFieldDefinition keyValue("keyValue", FieldType_MFRotation, SAIFieldAccess_inputOutput, offsetof(OrientationInterpolator, m_keyValue));
	static X3DFieldDefinition value_changed("value_changed", FieldType_SFRotation, SAIFieldAccess_outputOnly, offsetof(OrientationInterpolator, m_valueChanged));

	static X3DFieldDefinition* OrientationInterpolatorFields[] =
	{
		&keyValue,
		&value_changed,
	};

	static NodeType nodeType("OrientationInterpolator", typeid(OrientationInterpolator), OrientationInterpolatorFields, _countof(OrientationInterpolatorFields), X3DInterpolatorNode::GetNodeType());
	return &nodeType;
}

OrientationInterpolator::OrientationInterpolator() : X3DInterpolatorNode(GetNodeType())
{
}

void OrientationInterpolator::OnFieldChanged(X3DField* pField)
{
	if (pField == getSetFractionField())
	{
		float fraction = getSetFraction();

		ASSERT(fraction >= 0 && fraction <= 1);

		//MFFloat* key = static_cast<MFFloat*>(m_key);
		//MFRotation* keyValue = static_cast<MFRotation*>(m_keyValue);

		int numkeys = m_key->m_items.size();
		int numvalues = m_keyValue->m_items.size();

		if (numkeys == numvalues)
		{
			int left = -1;
			int right = -1;

			for (int i = 0; i < numkeys; ++i)
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
			ASSERT(t >= 0 && t <= 1);

			AxisAngle pV0 = m_keyValue->m_items[left];
			AxisAngle pV1 = m_keyValue->m_items[right];
			pV0.m_axis.normalize();
			pV1.m_axis.normalize();

			Quat4d q0 = pV0.ToQuat();
			Quat4d q1 = pV1.ToQuat();

#if 0
			double h0, a0, b0;
			QuaternionToEuler(q0, &h0, &a0, &b0);

			double h1, a1, b1;
			QuaternionToEuler(q1, &h1, &a1, &b1);

			double h = h0 + (h1-h0)*t;
			double a = a0 + (a1-a0)*t;
			double b = b0 + (b1-b0)*t;

			Quat4d q = EulerToQuaternion(h, a, b);
			/*
			Quat4d q(
				q0.x + (q1.x-q0.x)*t,
				q0.y + (q1.y-q0.y)*t,
				q0.z + (q1.z-q0.z)*t,
				q0.w + (q1.w-q0.w)*t);
				*/
#endif

			Quat4d q;
			slerp(t, &q0, &q1, &q, 0);

			m_valueChanged->m_value = q.ToAxisAngle();
		//	m_valueChanged->m_value.m_axis.normalize();

#if 0
			double elevation0 = asin(pV0.m_v[2]);
			if (cos(elevation0) == 0) MessageBeep(-1);
			double azimuth0 = acos(pV0.m_v[0] / cos(elevation0));

			double elevation1 = asin(pV1.m_v[2]);
			if (cos(elevation1) == 0) MessageBeep(-1);
			double azimuth1 = acos(pV1.m_v[0] / cos(elevation1));

			double elevation = elevation0 + (elevation1 - elevation0)*t;
			double azimuth = azimuth0 + (azimuth1 - azimuth0)*t;

			m_valueChanged->m_value.m_v[0] = cos(azimuth) * cos(elevation);
			m_valueChanged->m_value.m_v[1] = sin(azimuth) * cos(elevation);
			m_valueChanged->m_value.m_v[2] = sin(elevation);

			m_valueChanged->m_value.m_v.normalize();

			m_valueChanged->m_value.m_a = pV0.m_a + (pV1.m_a - pV0.m_a)*t;

			//m_valueChanged->m_v.m_v = pV1.m_v;
			//m_valueChanged->m_v.m_a = pV1.m_a;
#endif

		//	TRACE("%f\n", m_valueChanged->m_value.m_angle * 180/M_PI);

			Change(m_valueChanged);
		}
	}

	baseClass::OnFieldChanged(pField);
}

}	// x3d
}
