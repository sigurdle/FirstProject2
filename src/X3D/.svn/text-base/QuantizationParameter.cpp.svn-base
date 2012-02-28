#include "stdafx.h"
#include "X3D2.h"
#include "QuantizationParameter.h"

#include <cfloat>

namespace System
{
namespace x3d
{

X3DFieldDefinition* QuantizationParameterFields[] =
{
	&X3DFieldDefinition("colorMin", FieldType_SFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("colorMax", FieldType_SFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("colorNbBits", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("colorQuant", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("isLocal", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("position2DMin", FieldType_SFVec2f, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("position2DMax", FieldType_SFVec2f, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("position2DNbBits", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("position2DQuant", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("sizeMin", FieldType_SFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("sizeMax", FieldType_SFFloat, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("sizeNbBits", FieldType_SFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("sizeQuant", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),

	/*
	field SFBool isLocal FALSE
	field SFBool position3DQuant FALSE
	field SFVec3f position3DMin -., -., -.
	field SFVec3f position3DMax +., +., +.
	field SFInt32 position3DNbBits 16
	field SFBool position2DQuant FALSE
	field SFVec2f position2DMin -., -.
	field SFVec2f position2DMax +., +.
	field SFInt32 position2DNbBits 16
	field SFBool drawOrderQuant TRUE
	field SFVec3f drawOrderMin -.
	field SFVec3f drawOrderMax +.
	field SFInt32 drawOrderNbBits 8
	field SFBool colorQuant TRUE
	field SFFloat colorMin 0.0
	field SFFloat colorMax 1.0
	field SFInt32 colorNbBits 8
	field SFBool textureCoordinateQuant TRUE
	field SFFloat textureCoordinateMin 0.0
	field SFFloat textureCoordinateMax 1.0
	field SFInt32 textureCoordinateNbBits 16
	field SFBool angleQuant TRUE
	field SFFloat angleMin 0.0
	field SFFloat angleMax 2¶
	field SFInt32 angleNbBits 16
	field SFBool scaleQuant FALSE
	field SFFloat scaleMin 0.0
	field SFFloat scaleMax +.
	field SFInt32 scaleNbBits 8
	field SFBool keyQuant TRUE
	field SFFloat keyMin 0.0
	field SFFloat keyMax 1.0
	field SFInt32 keyNbBits 8
	field SFBool normalQuant TRUE
	field SFInt32 normalNbBits 8
	field SFBool sizeQuant FALSE
	field SFFloat sizeMin 0.0
	field SFFloat sizeMax +.
	field SFInt32 sizeNbBits 8
	field SFBool useEfficientCoding FALSE
	*/
};

NodeType QuantizationParameter::s_nodeType(WSTR("QuantizationParameter"), typeid(QuantizationParameter), QuantizationParameterFields, _countof(QuantizationParameterFields));

QuantizationParameter::QuantizationParameter() : X3DChildNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_isLocal = static_cast<SFBool*>(getField(WSTR("isLocal")));

	m_position2DQuant = static_cast<SFBool*>(getField(WSTR("position2DQuant")));
	m_position2DMin = static_cast<SFVec2f*>(getField(WSTR("position2DMin")));
	m_position2DMax = static_cast<SFVec2f*>(getField(WSTR("position2DMax")));
	m_position2DNbBits = static_cast<SFInt32*>(getField(WSTR("position2DNbBits")));

	m_colorQuant = static_cast<SFBool*>(getField(WSTR("colorQuant")));
	m_colorMin = static_cast<SFFloat*>(getField(WSTR("colorMin")));
	m_colorMax = static_cast<SFFloat*>(getField(WSTR("colorMax")));
	m_colorNbBits = static_cast<SFInt32*>(getField(WSTR("colorNbBits")));

	m_sizeQuant = static_cast<SFBool*>(getField(WSTR("sizeQuant")));
	m_sizeMin = static_cast<SFFloat*>(getField(WSTR("sizeMin")));
	m_sizeMax = static_cast<SFFloat*>(getField(WSTR("sizeMax")));
	m_sizeNbBits = static_cast<SFInt32*>(getField(WSTR("sizeNbBits")));

// Set defaults
	m_isLocal->m_value = false;

	m_position2DQuant->m_value = false;
	// TODO min,max (+- infinite, how to express?)
	m_position2DMin->m_value[0] = FLT_MIN;
	m_position2DMin->m_value[1] = FLT_MIN;
	m_position2DMax->m_value[0] = FLT_MAX;
	m_position2DMax->m_value[1] = FLT_MAX;
	m_position2DNbBits->m_value = 16;

	m_colorQuant->m_value = true;
	m_colorMin->m_value = 0;
	m_colorMax->m_value = 1;
	m_colorNbBits->m_value = 8;

	m_sizeQuant->m_value = false;
	m_sizeMin->m_value = 0;
	//m_sizeMax->m_value = 1; ????
	m_sizeNbBits->m_value = 8;
}

QuantizationParameter::~QuantizationParameter()
{
}

}	// x3d
}
