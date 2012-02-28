#include "stdafx.h"
#include "X3D2.h"
#include "AudioSource.h"

namespace System
{

namespace x3d
{

//IMP_X3DFIELD0(AudioSource, MFNode, addChildren"), FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
//&X3DFieldDefinition(WSTR("removeChildren"), FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
//IMP_X3DFIELD0(AudioSource, MFNode, children, inputOutput)
IMP_X3DFIELD1(AudioSource, SFFloat, speed, inputOutput, 1.0f)
IMP_X3DFIELD1(AudioSource, SFFloat, pitch, inputOutput, 1.0f)
//IMP_X3DFIELD1(AudioSource, SFTime, startTime, inputOutput, 0)
//IMP_X3DFIELD1(AudioSource, SFTime, stopTime, inputOutput, 0)
IMP_X3DFIELD0(AudioSource, MFString, url, inputOutput)

NodeType* AudioSource::GetNodeType()
{
	// MPEG4-BIFS
	static X3DFieldDefinition* fields[] =
	{
		get_speedFieldDef(),
		get_pitchFieldDef(),
	//	get_startTimeFieldDef(),
	//	get_stopTimeFieldDef(),
		get_urlFieldDef(),
		/*
		eventIn MFNode addChildren
		eventIn MFNode removeChildren
		exposedField MFNode children []
		exposedField MFString url []
		exposedField SFFloat pitch 1.0
		exposedField SFFloat speed 1.0
		exposedField SFTime startTime 0
		exposedField SFTime stopTime 0
		field SFInt32 numChan 1
		field MFInt32 phaseGroup []
		*/
	};

	static NodeType nodeType(WSTR("AudioSource"), typeid(AudioSource), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

AudioSource::AudioSource() : X3DSoundSourceNode(GetNodeType())
{
// Cache pointers to relevant fields
//	m_url = dynamic_cast<MFURL*>(getField(WSTR("url")));
	ASSERT(m_url);
}

}	// x3d
}
