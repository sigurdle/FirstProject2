#include "stdafx.h"
#include "X3D2.h"
#include "ProximitySensor.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* ProximitySensorFields[] =
{
	&X3DFieldDefinition("center", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("enabled", FieldType_SFBool, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("enterTime", FieldType_SFTime, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("exitTime", FieldType_SFTime, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("isActive", FieldType_SFBool, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("size", FieldType_SFVec3f, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("orientation_changed", FieldType_SFRotation, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("position_changed", FieldType_SFVec3f, SAIFieldAccess_outputOnly,-1),
	/*
	SFVec3f    [in,out] center                   0 0 0 (-8,8)
	SFBool     [in,out] enabled                  TRUE
	SFNode     [in,out] metadata                 NULL  [X3DMetadataObject]
	SFVec3f    [in,out] size                     0 0 0 [0,8)
	SFTime     [out]    enterTime
	SFTime     [out]    exitTime
	SFVec3f    [out]    centerOfRotation_changed
	SFBool     [out]    isActive
	SFRotation [out]    orientation_changed
	SFVec3f    [out]    position_changed
	*/
};

NodeType ProximitySensor::s_nodeType(WSTR("ProximitySensor"), typeid(ProximitySensor), ProximitySensorFields, _countof(ProximitySensorFields));

ProximitySensor::ProximitySensor() : X3DEnvironmentalSensorNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_center = static_cast<SFVec3f*>(getField(WSTR("center")));
	m_size = static_cast<SFVec3f*>(getField(WSTR("size")));
	m_enterTime = static_cast<SFTime*>(getField(WSTR("enterTime")));
	m_exitTime = static_cast<SFTime*>(getField(WSTR("exitTime")));
	m_isActive = static_cast<SFBool*>(getField(WSTR("isActive")));
	m_orientation_changed = static_cast<SFRotation*>(getField(WSTR("orientation_changed")));
	m_position_changed = static_cast<SFVec3f*>(getField(WSTR("position_changed")));
	// TODO m_centerOfRotation_changed

// Set default values
	m_center->m_value[0] = m_center->m_value[1] = m_center->m_value[2] = 0;
	m_size->m_value[0] = m_size->m_value[1] = m_size->m_value[2] = 0;
}

ProximitySensor::~ProximitySensor()
{
}

}	// x3d
}
