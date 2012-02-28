#include "stdafx.h"
#include "X3D2.h"

namespace System
{
namespace x3d
{

inline double REMAINDER(double t, double d)
{
	return ((t) - (d)*floor((t)/(d)));
}

NodeType* TimeSensor::nodeType(GetNodeType());

NodeType* TimeSensor::GetNodeType()
{
	static X3DFieldDefinition cycleInterval("cycleInterval", FieldType_SFTime, SAIFieldAccess_inputOutput, offsetof(TimeSensor, m_cycleInterval));
	static X3DFieldDefinition cycleTime("cycleTime", FieldType_SFTime, SAIFieldAccess_outputOnly, offsetof(TimeSensor, m_cycleTime));
	static X3DFieldDefinition enabled("enabled", FieldType_SFBool, SAIFieldAccess_inputOutput, offsetof(TimeSensor, m_enabled));
	static X3DFieldDefinition fraction_changed("fraction_changed", FieldType_SFFloat, SAIFieldAccess_outputOnly, offsetof(TimeSensor, m_fractionChanged));

	static X3DFieldDefinition* fields[] =
	{
		&cycleInterval,
		&cycleTime,
		&enabled,
		&fraction_changed,
	};

	static NodeType nodeType(WSTR("TimeSensor"), typeid(TimeSensor), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

TimeSensor::TimeSensor() : X3DTimeDependentNode(GetNodeType()),
	m_cycleInterval(new SFTime(this, 1))
{
	/*
// Cache pointers to relevant fields
	m_cycleInterval = static_cast<SFTime*>(getField(WSTR("cycleInterval")));
	m_startTime = static_cast<SFTime*>(getField(WSTR("startTime")));
	m_stopTime = static_cast<SFTime*>(getField(WSTR("stopTime")));
	m_cycleTime = static_cast<SFTime*>(getField(WSTR("cycleTime")));
	m_fractionChanged = static_cast<SFFloat*>(getField(WSTR("fraction_changed")));
	m_loop = static_cast<SFBool*>(getField(WSTR("loop")));
	m_isActive = static_cast<SFBool*>(getField(WSTR("isActive")));
	*/

// Set default values
//	m_loop->m_value = false;
//	m_cycleInterval->m_value = 1;

	/*
	m_startTime->m_value = 0;
	m_stopTime->m_value = 0;
	m_cycleTime->m_value = 0;
	*/
}

void TimeSensor::DoTime(double gt)
{
	if (getIsActive() == false)
	{
	//	if (gt < m_stopTime->m_value)	// ??
		{
			if (gt >= getStartTime())
			{
			// Going from inactive to active

				getIsActiveField()->m_value = true;
				Change(getIsActiveField());

				m_cycleTime->m_value = gt;
				Change(m_cycleTime);
			}
		}
	}
	
	//else
	{
		if (getStopTime() > getStartTime())
		{
			if (gt > getStopTime())
			{
				getStartTimeField()->m_value = 99999999;	// indefinite
				getIsActiveField()->m_value = false;
				Change(getIsActiveField());
			}
		}

		if (getIsActive())
		{
			if (gt > m_cycleTime->m_value + m_cycleInterval->m_value)
			{
				// Past end, should we loop or stop?

				if (!getLoop())
				{
					// Going from active to inactive
					getStartTimeField()->m_value = Double::get_PositiveInfinity();	// indefinite
					getIsActiveField()->m_value = false;
					Change(getIsActiveField());
				}
				else	// begin a new cycle
				{
					m_cycleTime->m_value += m_cycleInterval->m_value;
					Change(m_cycleTime);
				}
			}
		}
	}

	if (getIsActive())
	{
		m_fractionChanged->m_value = REMAINDER(gt - getStartTime(), m_cycleInterval->m_value) / m_cycleInterval->m_value;
		Change(m_fractionChanged);
	}

	/*
//	if (m_fractionChanged->m_outputRoute)
	{
		X3DField* pDestField = <X3DNode>(m_fractionChanged->m_outputRoute->m_destinationNode)->getField(m_fractionChanged->m_outputRoute->m_destinationField);
	}
	*/
}

}	// x3d
}	// System
