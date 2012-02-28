#include "stdafx.h"
#include "X3D2.h"
#include "TouchSensor.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* TouchSensorFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("description", FieldType_SFString, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("enabled", FieldType_SFBool, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("hitNormal_changed", FieldType_SFVec3f, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("hitPoint_changed", FieldType_SFVec3f, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("hitTexCoord_changed", FieldType_SFVec2f, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("isActive", FieldType_SFBool, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("isOver", FieldType_SFBool, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("touchTime", FieldType_SFTime, SAIFieldAccess_outputOnly,-1),
	/*
	SFString [in,out] description         ""
	SFBool   [in,out] enabled             TRUE
	SFVec3f  [out]    hitNormal_changed
	SFVec3f  [out]    hitPoint_changed
	SFVec2f  [out]    hitTexCoord_changed
	SFBool   [out]    isActive
	SFBool   [out]    isOver
	SFTime   [out]    touchTime
	*/
};

NodeType TouchSensor::s_nodeType(WSTR("TouchSensor"), typeid(TouchSensor), TouchSensorFields, _countof(TouchSensorFields));

TouchSensor::TouchSensor() : X3DTouchSensorNode(&s_nodeType)
{
// Set default values
	m_enabled->m_value = true;
}

TouchSensor::~TouchSensor()
{
}

void TouchSensor::setIsOver(bool isOver)
{
	m_isOver->setValue(isOver);
}

void TouchSensor::PreDraw(X3DDrawContext* pDC)
{
	if (m_enabled->m_value)
	{
		ASSERT(0);
#if 0
		pDC->m_pGraphics3D->PushName(pDC->m_namedNodes.GetSize());

	//LoadName(++pDC->m_nName);
		pDC->m_namedNodes.Add(this);
		//glLoadName(++pDC->m_nName);
#endif
	}
}

}	// x3d
}
