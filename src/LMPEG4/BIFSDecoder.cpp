#include "stdafx.h"
#include "LMPEG4.h"
/*
#include "BIFSDecoder.h"

#include "MP4File.h"
#include "MP4Track.h"

#include "BIFSDec.h"
*/

//using namespace System;

/*
#define LX3DEXT __declspec(dllimport)
#include "../LX3D/LX3DScene.h"
*/

//#include "LScriptEngine.h"

namespace System
{
using namespace IO;

//int GetNBits(int range);

namespace MediaShow
{

///////////////////////////////////////////////////////////////////////////
// CBIFSDecoder::COutputPin

ErrorCode CBIFSDecoder::COutputPin::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
	if (pVal == NULL) throw -1;//return E_POINTER;
	if (unit == TimeFormat_ref)
	{
		Mpeg4::Track* pTrack = GetFilter()->m_pDec->m_pTrack;
		*pVal = TIME_SCALE * pTrack->m_mediaHeader.m_duration / pTrack->m_mediaHeader.m_timeScale;
	}
	else if (unit == TimeFormat_frame)
	{
		VERIFY(0);
		return Error;
	}
	else
	{
		ASSERT(0);
		return Error;
	}

	return Success;
}

ErrorCode CBIFSDecoder::COutputPin::GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
{
	if (pVal == NULL) throw (int)Error_NullPointerArgument;

	if (unit == TimeFormat_ref)
	{
		Mpeg4::BIFSDec* pDec = GetFilter()->m_pDec;

		*pVal = TIME_SCALE * pDec->m_currentPosition / pDec->m_pTrack->m_mediaHeader.m_timeScale;
	}
	else if (unit == TimeFormat_frame)
	{
		VERIFY(0);
		return Error;
	}
	else
	{
		ASSERT(0);
		return Error;
	}

	return Success;
}

CBIFSDecoder::CBIFSDecoder()
{
	m_threadId = 0L;
	m_hThread = NULL;

	m_pInputPin = new CInputPin;
	m_pInputPin->m_id = WSTR("Input");
	m_pInputPin->m_pFilter = this;
	AddPin(m_pInputPin);

	m_pOutputPin = new COutputPin;
	m_pOutputPin->m_id = WSTR("Scene Output");
	m_pOutputPin->m_pFilter = this;
	AddPin(m_pOutputPin);
}

CBIFSDecoder::~CBIFSDecoder()
{
}

ErrorCode CBIFSDecoder::ReadBIFSCommandFrame(Stream& stream)
{
	System::IO::CBitStream32 bitstream(new IO::CByteStream(stream));

	bool bContinue;

	do
	{
		// Command
		int code = bitstream.getnbits(2);

		switch (code)
		{
		case 0:	// Insert
			{
				if (m_pDec->m_scene)
				{
					m_pDec->InsertionCommand(&bitstream);
				}
				else
				{
					ASSERT(0);
					return Error;
				}
				m_pOutputPin->m_pInputPin->Receive(NULL);
			}
			break;

		case 1:	// Delete
			{
				if (m_pDec->m_scene)
				{
					ASSERT(0);
					MessageBeep(-1);
				}
				else
				{
					ASSERT(0);
					return Error;
				}
				m_pOutputPin->m_pInputPin->Receive(NULL);
			}
			break;

		case 2:	// Replace
			{
				if (m_pDec->m_scene)
				{
					m_pDec->ReplacementCommand(&bitstream);
				}
				else
				{
					ASSERT(0);
					return Error;
				}
				m_pOutputPin->m_pInputPin->Receive(NULL);
			}
			break;

		case 3:	// Scene Replace
			{
				m_pDec->ResetDefs();
				/*
				if (m_scene)
				{
					m_scene.Release();
				}
				*/

				IMediaSample* sample;
				m_pOutputPin->m_pAllocator->GetBuffer(0, &sample);

				LSampleData sampledata;
				sample->LockBits(&sampledata);
				m_pDec->m_scene = reinterpret_cast<x3d::Scene*>(sampledata.idata);

				ErrorCode hr = m_pDec->ReadScene(&bitstream);

				m_pOutputPin->m_pInputPin->Receive(sample);
				//if (hr != S_OK)

				/*
				ErrorCode hr = m_scene.CoCreateInstance(CLSID_LX3DScene);
				if (SUCCEEDED(hr))
				{
					CComQIPtr<ILBIFSScene>(m_scene)->setBIFSContext(m_pOutputPin);

					ErrorCode hr = ReadScene(&bitstream);
				}
				else
					return hr;
					*/
			}
			break;
		}

		bContinue = bitstream.getbit();
	}
	while (bContinue);

	return Success;
}

void CBIFSDecoder::SeekFrame(long frame)
{
	if (frame < 0) frame = 0;

	long total = (long)m_pDec->m_pTrack->m_samples.size();
	if (frame > total-1) frame = total-1;

	long from;

	if (frame >= m_pDec->m_currentFrame)
	{
		for (from = frame; from > m_pDec->m_currentFrame; from--)
		{
			if (m_pDec->m_pTrack->m_sampleflags == NULL || m_pDec->m_pTrack->m_sampleflags[from])
			{
				/*
				if (m_pCurrentVOP)
				{
					delete m_pCurrentVOP;
					m_pCurrentVOP = NULL;
				}
				*/
				break;
			}
		}
	}
	else
	{
		/*
		if (m_pCurrentVOP)
		{
			delete m_pCurrentVOP;
			m_pCurrentVOP = NULL;
		}
		*/

		for (from = frame; from > 0; from--)
		{
			if (m_pDec->m_pTrack->m_sampleflags[from])
				break;
		}
	}

//	for (int i = m_pDec->m_currentFrame+1; i <= frame; i++)
	for (uint i = from; i <= frame; i++)
	{
		if (i == m_pDec->m_currentFrame)
			continue;

		m_pDec->m_stream.Seek(m_pDec->m_pTrack->m_samples[i].m_fileOffset, IO::STREAM_SEEK_SET);
		ReadBIFSCommandFrame(m_pDec->m_stream);
	}

	m_pDec->m_currentFrame = frame;
}

ErrorCode CBIFSDecoder::COutputPin::Seek(TimeUnit unit, LONGLONG t)
{
	// TODO
	if (unit == TimeFormat_ref)
	{
//		m_pFilter->m_pDec->m_currentPosition = t * m_pFilter->m_pDec->m_pTrack->m_mediaHeader.m_timeScale;
		LONGLONG t2 = 0;

		Mpeg4::Track* pTrack = GetFilter()->m_pDec->m_pTrack;

		int i;
		for (i = 0; i < pTrack->m_samples.GetSize(); i++)
		{
			LONGLONG duration = TIME_SCALE * pTrack->m_samples[i].m_duration / pTrack->m_mediaHeader.m_timeScale;

			if (t <= t2+duration)
				break;

			t2 += duration;
		}

		GetFilter()->m_pDec->m_currentPosition = t2;
		GetFilter()->SeekFrame(i);
	}
	else if (unit == TimeFormat_frame)
	{
		VERIFY(0);
	}
	else
	{
		ASSERT(0);
		return Error;
	}

	return Success;
}

ErrorCode CBIFSDecoder::COutputPin::FindODById(int ODid, System::Object* *pVal)
{
	if (pVal == NULL) return Error_NullPointerArgument;
	*pVal = NULL;

	ASSERT(0);

#if 0
	for (int i = 0; i < m_pFilter->m_pTrack->m_pMovie->m_od.GetSize(); i++)
	{
		CObjectDescriptor* pOD = m_pFilter->m_pTrack->m_pMovie->m_od[i];

		if (pOD->m_ObjectDescriptorID == ODid)
		{
			WORD refIndex = pOD->m_refIndex;
			if (refIndex > 0)	// 0 is allowed
			{
				if (refIndex <= pOD->m_pTrack->m_mpod.GetSize())
				{
					DWORD trackID = pOD->m_pTrack->m_mpod[refIndex-1];

					CTrack* pTrack = m_pFilter->m_pTrack->m_pMovie->GetTrackById(trackID);
					if (pTrack)
					{
						ASSERT(0);
#if 0
						*pVal = pTrack->m_sampleDescriptions[0]->m_decoder;
#endif
						//if (*pVal) (*pVal)->AddRef();
					}
				}
				else
					return E_FAIL;
			}

			return S_OK;
		}
	}
#endif
	return Success;
}

#if 0
/////////////////////////////////////////////////////////////////////////////
// CBIFSDecoder

sysstring ReadString(CBitStream* pBitStream);

enum
{
Anchor,// 0000001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AnimationStream,// 0000010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Appearance,// 0000011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
AudioBuffer,// 0000100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
AudioClip,// 0000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
AudioDelay,// 0000110 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
AudioFX,// 0000111 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioMix,// 0001000 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioSource,// 0001001 3 DEF bits 3 IN bits 3 OUT bits 1 DYN bits
AudioSwitch,// 0001010 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Background,// 0001011 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
Background2D,// 0001100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Billboard,// 0001101 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Bitmap,// 0001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Box,// 0001111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Circle,// 0010000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Collision,// 0010001 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Color,// 0010010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ColorInterpolator,// 0010011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CompositeTexture2D,// 0010100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
CompositeTexture3D,// 0010101 3 DEF bits 4 IN bits 3 OUT bits 0 DYN bits
Conditional,// 0010110 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Cone,// 0010111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Coordinate,// 0011000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Coordinate2D,// 0011001 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
CoordinateInterpolator,// 0011010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CoordinateInterpolator2D,// 0011011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Curve2D,// 0011100 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Cylinder,// 0011101 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
CylinderSensor,// 0011110 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
DirectionalLight,// 0011111 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
DiscSensor,// 0100000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
ElevationGrid,// 0100001 4 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Expression,// 0100010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Extrusion,// 0100011 4 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
Face,// 0100100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
FaceDefMesh,// 0100101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
FaceDefTables,// 0100110 2 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
FaceDefTransform,// 0100111 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
FAP,// 0101000 7 DEF bits 7 IN bits 7 OUT bits 0 DYN bits
FDP,// 0101001 3 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
FIT,// 0101010 4 DEF bits 4 IN bits 4 OUT bits 0 DYN bits
Fog,// 0101011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
FontStyle,// 0101100 4 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Form,// 0101101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Group,// 0101110 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
ImageTexture,// 0101111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
IndexedFaceSet,// 0110000 4 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedFaceSet2D,// 0110001 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedLineSet,// 0110010 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
IndexedLineSet2D,// 0110011 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Inline,// 0110100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
LOD,// 0110101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Layer2D,// 0110110 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
Layer3D,// 0110111 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Layout,// 0111000 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
LineProperties,// 0111001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
ListeningPoint,// 0111010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
Material,// 0111011 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Material2D,// 0111100 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
MovieTexture,// 0111101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
NavigationInfo,// 0111110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Normal,// 0111111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
NormalInterpolator,// 1000000 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
OrderedGroup,// 1000001 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
OrientationInterpolator,// 1000010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PixelTexture,// 1000011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
PlaneSensor,// 1000100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PlaneSensor2D,// 1000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PointLight,// 1000110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
PointSet,// 1000111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
PointSet2D,// 1001000 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
PositionInterpolator,// 1001001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PositionInterpolator2D,// 1001010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ProximitySensor2D,// 1001011 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
ProximitySensor,// 1001100 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
kQuantizationParameter,// 1001101 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
bifsRectangle,// 1001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ScalarInterpolator,// 1001111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Script,// 1010000 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Shape,// 1010001 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Sound,// 1010010 4 DEF bits 4 IN bits 4 OUT bits 3 DYN bits
Sound2D,// 1010011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
Sphere,// 1010100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
SphereSensor,// 1010101 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
SpotLight,// 1010110 4 DEF bits 4 IN bits 4 OUT bits 4 DYN bits
Switch,// 1010111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TermCap,// 1011000 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Text,// 1011001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
TextureCoordinate,// 1011010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
TextureTransform,// 1011011 2 DEF bits 2 IN bits 2 OUT bits 2 DYN bits
TimeSensor,// 1011100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
TouchSensor,// 1011101 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
Transform,// 1011110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Transform2D,// 1011111 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Valuator,// 1100000 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
Viewpoint,// 1100001 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
VisibilitySensor,// 1100010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
Viseme,// 1100011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
WorldInfo
};

// Fields

Field AppearanceFields[] =
{
	{L"material", BIFS_SFMaterialNode,					1, 1, 1, 0,		0, 0,		-1, -1},
	{L"texture", BIFS_SFTextureNode,						1, 1, 1, 0,		0, 0,		-1, -1},
	{L"textureTransform", BIFS_SFTextureTransform,	1, 1, 1, 0,		0, 0,		-1, -1},
	NULL
};

Field AudioSourceFields[] =
{
	{L"addChildren", BIFS_MFAudioNode,				0, 1, 0, 0,		0, 0,			-1, -1},
	{L"removeChildren", BIFS_MFAudioNode,			0, 1, 0, 0,		0, 0,			-1, -1},
	{L"children", BIFS_MFAudioNode,					1, 1, 1, 0,		0, 0,			-1, -1},
	{L"url", BIFS_MFURL,									1, 1, 1, 0,		0, 0,			-1, -1},
	{L"pitch", BIFS_SFFloat,							1, 1, 1, 1,		0, LONG_MAX, 0, -1},
	{L"speed", BIFS_SFFloat,							1, 1, 1, 1,		0, LONG_MAX, 0, -1},
	{L"startTime", BIFS_SFTime,						1, 1, 1, 0,		0, 0,			-1, -1},
	{L"stopTime", BIFS_SFTime,							1, 1, 1, 0,		0, 0,			-1, -1},
	{L"numChan", BIFS_SFInt32,							1, 0, 0, 0,		0, 255,		13, 8},
	{L"phaseGroup", BIFS_MFInt32,						1, 0, 0, 0,		0, 255,		13, 8},
	NULL
};

Field Background2DFields[] =
{
	{L"set_bind", BIFS_SFBool,		0, 1, 0, 0,		0, 0,		-1, -1},
	{L"backColor", BIFS_SFColor,	1, 1, 1, 0,		0, 1,		4, -1},
	{L"url", BIFS_MFURL,				1, 1, 1, 0,		0, 0,		-1, -1},
	{L"isBound", BIFS_SFBool,		0, 0, 1, 0,		0, 0,		-1, -1},
	NULL,
};

Field BitmapFields[] =
{
	{L"scale", BIFS_SFVec2f,	1/*??*/,0,0,0,			0,0,	12,-1},
	NULL
};

Field CircleFields[] =
{
	{L"radius", BIFS_SFFloat,	1/*??*/,0,0,0,			0,FLT_MAX,	12,-1},
	NULL
};

Field ConditionalFields[] =
{
	{L"activate", BIFS_SFBool,				0,1,0,0,			0,0,		-1,-1},
	{L"reverseActivate", BIFS_SFBool,	0,1,0,0,			0,0,		-1,-1},
	{L"buffer", BIFS_SFCommandBuffer,	1/*??*/,1,0,0,	0,0,		-1,-1},
	{L"isActive", BIFS_SFBool,				0,0,1,0,			0,0,		-1,-1},
	NULL
};

Field Coordinate2DFields[] =
{
	{L"point", BIFS_MFVec2f, 1/*in the spec there's nothing there??*/, 0, 0, 0,		-FLT_MAX, FLT_MAX,		2, -1},
	NULL
};

Field Curve2DFields[] =
{
	{L"point", BIFS_SFCoordinate2DNode,	1, 1, 1, 0,		0, 0,		-1, -1},
	{L"fineness", BIFS_SFFloat,			1, 1, 1, 0,		0, 1,		0, -1},
	{L"type", BIFS_MFInt32,					1, 1, 1, 0,		0, 3,		13, 2},
	NULL
};

Field DirectionalLightFields[] =
{
	{L"ambientIntensity", BIFS_SFFloat,	1, 1, 1, 1,		0,1,		4, -1},
	{L"color", BIFS_SFColor,				1, 1, 1, 1,		0,1,		4, -1},
	{L"direction", BIFS_SFVec3f,			1, 1, 1, 1,		0,0,		9, -1},
	{L"intensity", BIFS_SFFloat,			1, 1, 1, 1,		0,1,		4, -1},
	{L"on", BIFS_SFBool,						1, 1, 1, 0,		0,0,		-1, -1},
	NULL,
};

Field FontStyleFields[] =
{
	{L"family", BIFS_MFString,			1, 0, 0, 0,		0,0,			-1,-1},
	{L"horizontal", BIFS_SFBool,		1, 0, 0, 0,		0,0,			-1,-1},
	{L"justify", BIFS_MFString,		1, 0, 0, 0,		0,0,			-1,-1},
	{L"language", BIFS_SFString,		1, 0, 0, 0,		0,0,			-1,-1},
	{L"leftToRight", BIFS_SFBool,		1, 0, 0, 0,		0,0,			-1,-1},
	{L"size", BIFS_SFFloat,				1, 0, 0, 0,		0,FLT_MAX,	11,-1},
	{L"spacing", BIFS_SFFloat,			1, 0, 0, 0,		0,FLT_MAX,	11,-1},
	{L"style", BIFS_SFString,			1, 0, 0, 0,		0,0,			-1,-1},
	{L"topToBottom", BIFS_SFBool,		1, 0, 0, 0,		0,0,			-1,-1},
	NULL
};

Field FormFields[] =
{
	{L"addChildren", BIFS_MF2DNode,				0,1,0,0,			0,0,			-1,-1},
	{L"removeChildren", BIFS_MF2DNode,			0,1,0,0,			0,0,			-1,-1},
	{L"children", BIFS_MF2DNode,					1,1,1,0,			0,0,			-1,-1},
	{L"size", BIFS_SFVec2f,							1,1,1,0,			0,FLT_MAX,	12,-1},
	{L"groups", BIFS_MFInt32,						1,1,1,0,			-1, 1022,	13,10},
	{L"constraints", BIFS_MFString,				1,1,1,0,			0,0,			-1,-1},
	{L"groupsIndex", BIFS_MFInt32,				1,1,1,0,			-1, 1022,	13,10},
	NULL
};

Field GroupFields[] =
{
	{L"addChildren", BIFS_MF3DNode,		0,1,0,0,					0,0,			-1,-1},
	{L"removeChildren", BIFS_MF3DNode,	0,1,0,0,					0,0,			-1,-1},
	{L"children", BIFS_MF3DNode,			1/*??*/,1,0,0,			0,0,			-1,-1},
	NULL
};

Field ImageTextureFields[] =
{
	{L"url", BIFS_MFURL,			1, 0, 0, 0,		0,0,	-1,-1},
	{L"repeatS", BIFS_SFBool,	1, 0, 0, 0,		0,0,	-1,-1},
	{L"repeatT", BIFS_SFBool,	1, 0, 0, 0,		0,0,	-1,-1},
	NULL
};

Field IndexedFaceSet2DFields[] =
{
	{L"set_colorIndex", BIFS_MFInt32,				0, 1, 0, 0,		0,0,			-1, -1},
	{L"set_coordIndex", BIFS_MFInt32,				0, 1, 0, 0,		0,0,			-1, -1},
	{L"set_texCoordIndex", BIFS_MFInt32,			0, 1, 0, 0,		0,0,			-1, -1},
	{L"color", BIFS_SFColorNode,						1, 1, 1, 0,		0,0,			-1, -1},
	{L"coord", BIFS_SFCoordinate2DNode,				1, 1, 1, 0,		0,0,			-1, -1},
	{L"texCoord", BIFS_SFTextureCoordinateNode,	1, 1, 1, 0,		0,0,			-1, -1},
	{L"colorIndex", BIFS_MFInt32,						1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	{L"colorPerVertex", BIFS_SFBool,					1, 0, 0, 0,		0,0,			-1, -1},
	{L"convex", BIFS_SFBool,							1, 0, 0, 0,		0,0,			-1, -1},
	{L"coordIndex", BIFS_MFInt32,						1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	{L"texCoordIndex", BIFS_MFInt32,					1, 0, 0, 0,		0,LONG_MAX,	14, -1},

	NULL,
};

Field IndexedLineSet2DFields[] =
{
	{L"set_colorIndex", BIFS_MFInt32,			0, 1, 0, 0,		0,0,			-1, -1},
	{L"set_coordIndex", BIFS_MFInt32,			0, 1, 0, 0,		0,0,			-1, -1},
	{L"color", BIFS_SFColorNode,					1, 1, 1, 0,		0,0,			-1, -1},
	{L"coord", BIFS_SFCoordinate2DNode,			1, 1, 1, 0,		0,0,			-1, -1},
	{L"colorIndex", BIFS_MFInt32,					1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	{L"colorPerVertex", BIFS_SFBool,				1, 0, 0, 0,		0,0,			-1, -1},
	{L"coordIndex", BIFS_MFInt32,					1, 0, 0, 0,		0,LONG_MAX,	14, -1},
	NULL
};

Field LinePropertiesFields[] =
{
	{L"lineColor", BIFS_SFColor,			1, 1, 1, 1,		0,1,			4, -1},
	{L"lineStyle", BIFS_SFInt32,			1, 1, 1, 0,		0,5,			13, 3},
	{L"width", BIFS_SFFloat,				1, 1, 1, 1,		0,FLT_MAX,	12, -1},
	NULL,
};

Field Material2DFields[] =
{
	{L"emissiveColor", BIFS_SFColor,				1, 1, 1, 1,		0,1,		4, -1},
	{L"filled", BIFS_SFBool,						1, 1, 1, 0,		0,0,		-1, -1},
	{L"lineProps", BIFS_SFLinePropertiesNode,	1, 1, 1, 0,		0,0,		-1, -1},
	{L"transparency", BIFS_SFFloat,				1, 1, 1, 1,		0,1,		4, -1},
	NULL
};

Field MovieTextureFields[] =
{
	{L"loop", BIFS_SFBool,					1, 1, 1, 0,		0,0,						-1,-1},
	{L"speed", BIFS_SFFloat,				1, 1, 1, 0,		-FLT_MAX,FLT_MAX,		0,-1},
	{L"startTime", BIFS_SFTime,			1, 1, 1, 0,		-FLT_MAX,FLT_MAX,		-1,-1},
	{L"stopTime", BIFS_SFTime,				1, 1, 1, 0,		-FLT_MAX,FLT_MAX,		-1,-1},
	{L"url", BIFS_MFURL,						1, 1, 1, 0,		0,0,						-1,-1},
	{L"repeatS", BIFS_SFBool,				1, 0, 0, 0,		0,0,						-1,-1},
	{L"repeatT", BIFS_SFBool,				1, 0, 0, 0,		0,0,						-1,-1},
	{L"duration_changed", BIFS_SFTime,	0, 0, 1, 0,		0,0,						-1,-1},
	{L"isActive", BIFS_SFBool,				0, 0, 1, 0,		0,0						-1,-1},
	NULL
};

Field OrderedGroupFields[] =
{
	{L"addChildren", BIFS_MF3DNode,		0, 1, 0, 0,			0,0,			-1, -1},
	{L"removeChildren", BIFS_MF3DNode,	0, 1, 0, 0,			0,0,			-1, -1},
	{L"children", BIFS_MF3DNode,			1, 1, 1, 0, 		0,0,			-1, -1},
	{L"order", BIFS_MFFloat,				1, 1, 1, 0,			0,FLT_MAX,	3, -1},
	NULL
};

Field PositionInterpolator2DFields[] =
{
	{L"set_fraction", BIFS_SFFloat,		0,1,0,0,			0,0,						-1,-1},
	{L"key", BIFS_MFFloat,					1,1,1,0,			0,1,						8,-1},
	{L"keyValue", BIFS_MFVec2f,			1,1,1,0,			-FLT_MAX,FLT_MAX,		2,-1},
	{L"value_changed", BIFS_SFVec2f,		0,0,1,0,			0,0,						-1,-1},
	NULL
};

Field QuantizationParameterFields[] =
{
	{L"isLocal", BIFS_SFBool,						1, 0, 0, 0,		0,0,					-1, -1},

	{L"position3DQuant", BIFS_SFBool,			1, 0, 0, 0,		0,0,					-1, -1},
	{L"position3DMin", BIFS_SFVec3f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"position3DMax", BIFS_SFVec3f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"position3DNbBits", BIFS_SFInt32,			1, 0, 0, 0,		0, 31,				13, 5},

	{L"position2DQuant", BIFS_SFBool,			1, 0, 0, 0,		0,0,					-1, -1},
	{L"position2DMin", BIFS_SFVec2f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"position2DMax", BIFS_SFVec2f,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"position2DNbBits", BIFS_SFInt32,			1, 0, 0, 0,		0, 31,				13, 5},

	{L"drawOrderQuant", BIFS_SFBool,				1, 0, 0, 0,		0,0,					-1, -1},
	{L"drawOrderMin", BIFS_SFFloat,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"drawOrderMax", BIFS_SFFloat,				1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"drawOrderNbBits", BIFS_SFInt32,			1, 0, 0, 0,		0, 31,				13, 5},

	{L"colorQuant", BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{L"colorMin", BIFS_SFFloat,					1, 0, 0, 0,		0,1,					0, -1},
	{L"colorMax", BIFS_SFFloat,					1, 0, 0, 0,		0,1,					0, -1},
	{L"colorNbBits", BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{L"textureCoordinateQuant", BIFS_SFBool,	1, 0, 0, 0,		0,0,					-1, -1},
	{L"textureCoordinateMin", BIFS_SFFloat,	1, 0, 0, 0,		0,1,					0, -1},
	{L"textureCoordinateMax", BIFS_SFFloat,	1, 0, 0, 0,		0,1,					0, -1},
	{L"textureCoordinateNbBits", BIFS_SFInt32,1, 0, 0, 0,		0,31,					13, 5},

	{L"angleQuant", BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{L"angleMin", BIFS_SFFloat,					1, 0, 0, 0,		0,	6.2831853f,		0, -1},
	{L"angleMax", BIFS_SFFloat,					1, 0, 0, 0,		0,	6.2831853f,		0, -1},
	{L"angleNbBits", BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{L"scaleQuant", BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{L"scaleMin", BIFS_SFFloat,					1, 0, 0, 0,		0,FLT_MAX,			0, -1},
	{L"scaleMax", BIFS_SFFloat,					1, 0, 0, 0,		0,FLT_MAX,			0, -1},
	{L"scaleNbBits", BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{L"keyQuant", BIFS_SFBool,						1, 0, 0, 0,		0,0,					-1, -1},
	{L"keyMin", BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"keyMax", BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"keyNbBits", BIFS_SFInt32,					1, 0, 0, 0,		0,31,					13, 5},

	{L"normalQuant", BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{L"normalNbBits", BIFS_SFInt32,				1, 0, 0, 0,		0,31,					13, 5},

	{L"sizeQuant", BIFS_SFBool,					1, 0, 0, 0,		0,0,					-1, -1},
	{L"sizeMin", BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"sizeMax", BIFS_SFFloat,						1, 0, 0, 0,		-FLT_MAX,FLT_MAX,	0, -1},
	{L"sizeNbBits", BIFS_SFInt32,					1, 0, 0, 0,		0,31,					13, 5},

	{L"useEfficientCoding", BIFS_SFBool,		1, 0, 0, 0,		0,0,					-1, -1},
	NULL
};

Field RectangleFields[] =
{
	{L"size", BIFS_SFVec2f,		1/*??*/, 0, 0, 0,		0, FLT_MAX,		12, -1},
	NULL
};

Field ScriptFields[] =
{
	{L"url", BIFS_MFScript,				1,0,0,0,		0,0,		-1,-1},
	{L"directOutput", BIFS_SFBool,	1,0,0,0,		0,0,		-1,-1},
	{L"mustEvaluate", BIFS_SFBool,	1,0,0,0,		0,0,		-1,-1},
	NULL
};

Field ShapeFields[] =
{
	{L"appearance", BIFS_SFAppearanceNode,		1, 1, 1, 0,		0,0,		-1, -1},
	{L"geometry",  BIFS_SFGeometryNode,			1, 1, 1, 0,		0,0,		-1, -1},
	NULL,
};

Field Sound2DFields[] =
{
	{L"intensity", BIFS_SFFloat,		1, 1, 1, 1,		0,1,					4, -1},
	{L"location", BIFS_SFVec2f,		1, 1, 1, 1,		-FLT_MAX,FLT_MAX,	4, -1},
	{L"source", BIFS_SFAudioNode,		1, 1, 1, 0,		0,0,					-1, -1},
	{L"spatialize", BIFS_SFBool,		1, 0, 0, 0,		0,0,					-1, -1},
	NULL
};

Field SpotLightFields[] =
{
	{L"ambientIntensity", BIFS_SFFloat,		1,1,1,1,	0, 1,						4,-1},
	{L"attenuation", BIFS_SFVec3f,			1,1,1,1, 0, FLT_MAX,				11,-1},
	{L"beamWidth", BIFS_SFFloat,				1,1,1,1, 0, 1.5707963f,			6,-1},
	{L"color", BIFS_SFColor,					1,1,1,1, 0, 1,						4,-1},
	{L"cutOffAngle", BIFS_SFFloat,			1,1,1,1, 0, 1.5707963f,			6,-1},
	{L"direction", BIFS_SFVec3f,				1,1,1,1, -FLT_MAX, +FLT_MAX,	9,-1},
	{L"intensity", BIFS_SFFloat,				1,1,1,1, 0, 1,						4,-1},
	{L"location", BIFS_SFVec3f,				1,1,1,1, -FLT_MAX, +FLT_MAX,	1,-1},
	{L"on", BIFS_SFBool,							1,1,1,0, 0,0,						-1,-1},
	{L"radius", BIFS_SFFloat,					1,1,1,1,	0, +FLT_MAX,			11,-1},
	NULL
};

Field SwitchFields[] =
{
	{L"choice", BIFS_MF3DNode,			1, 1, 1, 0,		0,0,			-1, -1},
	{L"whichChoice", BIFS_SFInt32,	1, 1, 1, 0,		-1,1022,		13, 10},
	NULL
};

Field TextFields[] =
{
	{L"string", BIFS_MFString,					1, 1, 1, 0,		0,0,			-1,-1},
	{L"length", BIFS_MFFloat,					1, 1, 1, 1,		0,FLT_MAX,	7,-1},
	{L"fontStyle", BIFS_SFFontStyleNode,	1, 1, 1, 0,		0,0,			-1,-1},
	{L"maxExtent", BIFS_SFFloat,				1, 1, 1, 1,		0,FLT_MAX,	7,-1},
	NULL
};

Field TimeSensorFields[] =
{
	{L"cycleInterval", BIFS_SFTime,		1,1,1,0,		0,FLT_MAX,			-1,-1},
	{L"enabled", BIFS_SFBool,				1,1,1,0,		0,0,					-1,-1},
	{L"loop", BIFS_SFBool,					1,1,1,0,		0,0,					-1,-1},
	{L"startTime", BIFS_SFTime,			1,1,1,0,		-FLT_MAX,FLT_MAX,	-1,-1},
	{L"stopTime", BIFS_SFTime,				1,1,1,0,		-FLT_MAX,FLT_MAX,	-1,-1},
	{L"cycleTime", BIFS_SFTime,			0,0,1,0,		0,0,					-1,-1},
	{L"fraction_changed", BIFS_SFFloat,	0,0,1,0,		0,0,					-1,-1},
	{L"isActive", BIFS_SFBool,				0,0,1,0,		0,0,					-1,-1},
	{L"time", BIFS_SFTime,					0,0,1,0,		0,0,					-1,-1},
	NULL
};

Field Transform2DFields[] =
{
	{L"addChildren", BIFS_MF2DNode,				0, 1, 0, 0,		0,0,					-1, -1},
	{L"removeChildren", BIFS_MF2DNode,			0, 1, 0, 0,		0,0,					-1, -1},
	{L"children", BIFS_MF2DNode,					1, 1, 1, 0,		0,0,					-1, -1},
	{L"center", BIFS_SFVec2f,						1, 1, 1, 1,		-FLT_MAX,FLT_MAX,	2, -1},
	{L"rotationAngle", BIFS_SFFloat,				1, 1, 1, 1,		0,6.2831853f,		6, -1},
	{L"scale", BIFS_SFVec2f,						1, 1, 1, 1,		0,FLT_MAX,			7, -1},
	{L"scaleOrientation", BIFS_SFFloat,			1, 1, 1, 1,		0,6.2831853f,		6, -1},
	{L"translation", BIFS_SFVec2f,				1, 1, 1, 1,		-FLT_MAX,FLT_MAX,	2, -1},
	NULL
};

Field ValuatorFields[] =
{
	{L"inSFBool", BIFS_SFBool,				0,1,0,0,			0,0,						-1,-1},
	{L"inSFColor", BIFS_SFColor,			0,1,0,0,			0,0,						-1,-1},
	{L"inMFColor", BIFS_MFColor,			0,1,0,0,			0,0,						-1,-1},
	{L"inSFFloat", BIFS_SFFloat,			0,1,0,0,			0,0,						-1,-1},
	{L"inMFFloat", BIFS_MFFloat,			0,1,0,0,			0,0,						-1,-1},
	{L"inSFInt32", BIFS_SFInt32,			0,1,0,0,			0,0,						-1,-1},
	{L"inMFInt32", BIFS_MFInt32,			0,1,0,0,			0,0,						-1,-1},
	{L"inSFRotation", BIFS_SFRotation,	0,1,0,0,			0,0,						-1,-1},
	{L"inMFRotation", BIFS_MFRotation,	0,1,0,0,			0,0,						-1,-1},
	{L"inSFString", BIFS_SFString,		0,1,0,0,			0,0,						-1,-1},
	{L"inMFString", BIFS_MFString,		0,1,0,0,			0,0,						-1,-1},
	{L"inSFTime", BIFS_SFTime,				0,1,0,0,			0,0,						-1,-1},
	{L"inSFVec2f", BIFS_SFVec2f,			0,1,0,0,			0,0,						-1,-1},
	{L"inMFVec2f", BIFS_MFVec2f,			0,1,0,0,			0,0,						-1,-1},
	{L"inSFVec3f", BIFS_SFVec3f,			0,1,0,0,			0,0,						-1,-1},
	{L"inMFVec3f", BIFS_MFVec3f,			0,1,0,0,			0,0,						-1,-1},
	{L"outSFBool", BIFS_SFBool,			0,0,1,0,			0,0,						-1,-1},
	{L"outSFColor", BIFS_SFColor,			0,0,1,0,			0,0,						-1,-1},
	{L"outMFColor", BIFS_MFColor,			0,0,1,0,			0,0,						-1,-1},
	{L"outSFFloat", BIFS_SFFloat,			0,0,1,0,			0,0,						-1,-1},
	{L"outMFFloat", BIFS_MFFloat,			0,0,1,0,			0,0,						-1,-1},
	{L"outSFInt32", BIFS_SFInt32,			0,0,1,0,			0,0,						-1,-1},
	{L"outMFInt32", BIFS_MFInt32,			0,0,1,0,			0,0,						-1,-1},
	{L"outSFRotation", BIFS_SFRotation,	0,0,1,0,			0,0,						-1,-1},
	{L"outMFRotation", BIFS_MFRotation,	0,0,1,0,			0,0,						-1,-1},
	{L"outSFString", BIFS_SFString,		0,0,1,0,			0,0,						-1,-1},
	{L"outMFString", BIFS_MFString,		0,0,1,0,			0,0,						-1,-1},
	{L"outSFTime", BIFS_SFTime,			0,0,1,0,			0,0,						-1,-1},
	{L"outSFVec2f", BIFS_SFVec2f,			0,0,1,0,			0,0,						-1,-1},
	{L"outMFVec2f", BIFS_MFVec2f,			0,0,1,0,			0,0,						-1,-1},
	{L"outSFVec3f", BIFS_SFVec3f,			0,0,1,0,			0,0,						-1,-1},
	{L"outMFVec3f", BIFS_MFVec3f,			0,0,1,0,			0,0,						-1,-1},
	{L"Factor1", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Factor2", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Factor3", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Factor4", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Offset1", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Offset2", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Offset3", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Offset4", BIFS_SFFloat,				1,1,1,0,			-FLT_MAX,FLT_MAX,		0,-1},
	{L"Sum", BIFS_SFBool,					1,1,1,0,			0,0,						-1,-1},
	NULL
};

Field WorldInfoFields[] =
{
	{L"info", BIFS_MFString,		1, 0, 0, 0,		0, 0, -1,-1},
	{L"title", BIFS_SFString,		1, 0, 0, 0,		0, 0, -1,-1},
	NULL
};

// Nodes

Node nodes[] =
{
L"Anchor", NULL, // 0000001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
L"AnimationStream", NULL,// 0000010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"Appearance", AppearanceFields,// 0000011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"AudioBuffer", NULL,// 0000100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
L"AudioClip", NULL,// 0000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"AudioDelay", NULL,// 0000110 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
L"AudioFX", NULL,// 0000111 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
L"AudioMix", NULL,// 0001000 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
L"AudioSource", AudioSourceFields,// 0001001 3 DEF bits 3 IN bits 3 OUT bits 1 DYN bits
L"AudioSwitch", NULL,// 0001010 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
L"Background", NULL,// 0001011 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
L"Background2D", Background2DFields,// 0001100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"Billboard", NULL,// 0001101 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
L"Bitmap", BitmapFields,// 0001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Box", NULL,// 0001111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Circle", CircleFields,// 0010000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Collision", NULL,// 0010001 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"Color", NULL,// 0010010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"ColorInterpolator", NULL,// 0010011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"CompositeTexture2D", NULL,// 0010100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"CompositeTexture3D", NULL,// 0010101 3 DEF bits 4 IN bits 3 OUT bits 0 DYN bits
L"Conditional", ConditionalFields,// 0010110 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
L"Cone", NULL,// 0010111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Coordinate", NULL,// 0011000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Coordinate2D", Coordinate2DFields,// 0011001 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"CoordinateInterpolator", NULL,// 0011010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"CoordinateInterpolator2D", NULL,// 0011011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"Curve2D", Curve2DFields,// 0011100 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"Cylinder", NULL,// 0011101 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"CylinderSensor", NULL,// 0011110 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
L"DirectionalLight", DirectionalLightFields,// 0011111 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
L"DiscSensor", NULL,// 0100000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"ElevationGrid", NULL,// 0100001 4 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"Expression", NULL,// 0100010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"Extrusion", NULL,// 0100011 4 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
L"Face", NULL,// 0100100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"FaceDefMesh", NULL,// 0100101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"FaceDefTables", NULL,// 0100110 2 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"FaceDefTransform", NULL,// 0100111 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"FAP", NULL,// 0101000 7 DEF bits 7 IN bits 7 OUT bits 0 DYN bits
L"FDP", NULL,// 0101001 3 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"FIT", NULL,// 0101010 4 DEF bits 4 IN bits 4 OUT bits 0 DYN bits
L"Fog", NULL,// 0101011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
L"FontStyle", FontStyleFields,// 0101100 4 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Form", FormFields,// 0101101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"Group", GroupFields,// 0101110 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
L"ImageTexture", ImageTextureFields,// 0101111 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"IndexedFaceSet", NULL,// 0110000 4 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
L"IndexedFaceSet2D", IndexedFaceSet2DFields,// 0110001 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
L"IndexedLineSet", NULL,// 0110010 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
L"IndexedLineSet2D", IndexedLineSet2DFields,// 0110011 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
L"Inline", NULL,// 0110100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"LOD", NULL,// 0110101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Layer2D", NULL,// 0110110 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
L"Layer3D", NULL,// 0110111 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"Layout", NULL,// 0111000 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
L"LinePropertiesBIFS", LinePropertiesFields,// 0111001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
L"ListeningPoint", NULL,// 0111010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
L"Material", NULL,// 0111011 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
L"Material2D", Material2DFields,// 0111100 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
L"MovieTexture", MovieTextureFields,// 0111101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"NavigationInfo", NULL,// 0111110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"Normal", NULL,// 0111111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"NormalInterpolator", NULL,// 1000000 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"OrderedGroup", OrderedGroupFields,// 1000001 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
L"OrientationInterpolator", NULL,// 1000010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"PixelTexture", NULL,// 1000011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"PlaneSensor", NULL,// 1000100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"PlaneSensor2D", NULL,// 1000101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"PointLight", NULL,// 1000110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
L"PointSet", NULL,// 1000111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"PointSet2D", NULL,// 1001000 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"PositionInterpolator", NULL,// 1001001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"PositionInterpolator2D", PositionInterpolator2DFields,// 1001010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"ProximitySensor2D", NULL,// 1001011 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
L"ProximitySensor", NULL,// 1001100 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
L"QuantizationParameter", QuantizationParameterFields,// 1001101 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Rectangle", RectangleFields,// 1001110 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"ScalarInterpolator", NULL,// 1001111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"Script", ScriptFields,// 1010000 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"Shape", ShapeFields,// 1010001 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"Sound", NULL,// 1010010 4 DEF bits 4 IN bits 4 OUT bits 3 DYN bits
L"Sound2D", Sound2DFields,// 1010011 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
L"Sphere", NULL,// 1010100 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"SphereSensor", NULL,// 1010101 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
L"SpotLight", SpotLightFields,// 1010110 4 DEF bits 4 IN bits 4 OUT bits 4 DYN bits
L"Switch", SwitchFields,// 1010111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"TermCap", NULL,// 1011000 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"Text", TextFields,// 1011001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
L"TextureCoordinate", NULL,// 1011010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
L"TextureTransform", NULL,// 1011011 2 DEF bits 2 IN bits 2 OUT bits 2 DYN bits
L"TimeSensor", TimeSensorFields,// 1011100 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
L"TouchSensor", NULL,// 1011101 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
L"Transform", NULL,// 1011110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
L"Transform2D", Transform2DFields,// 1011111 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
L"Valuator", ValuatorFields,// 1100000 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
L"Viewpoint", NULL,// 1100001 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
L"VisibilitySensor", NULL,// 1100010 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
L"Viseme", NULL,// 1100011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"WorldInfo", WorldInfoFields,
};

enum
{
PROTO,
AcousticMaterial,
AcousticScene,
ApplicationWindow,
BAP,
BDP,
Body,
BodyDefTable,
BodySegmentConnectionHint,
DirectiveSound,
Hierarchical3DMesh,
MaterialKey,
PerceptualParameters,
};

Node nodesExt[] =
{
NULL, NULL,//PROTO 0001
L"AcousticMaterial", NULL,// 0010 4 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
L"AcousticScene", NULL,// 0011 3 DEF bits 1 IN bits 1 OUT bits 1 DYN bits
L"ApplicationWindow", NULL,// 0100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"BAP", NULL,// 0101 9 DEF bits 9 IN bits 9 OUT bits 0 DYN bits
L"BDP", NULL,// 0110 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"Body", NULL,// 0111 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"BodyDefTable", NULL,// 1000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
L"BodySegmentConnectionHint", NULL,// 1001 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
L"DirectiveSound", NULL,// 1010 4 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
L"Hierarchical3DMesh", NULL,// 1011 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
L"MaterialKey", NULL,// 1100 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
L"PerceptualParameters", NULL,// 1101 5 DEF bits 5 IN bits 5 OUT bits 5 DYN bits
};

NodeDataTypeNode SFTopNodeNodes[] =
{
Group, 0, 2, 0,// OUT bits 0 DYN bits
Layer2D, 2, 3, 2,// OUT bits 0 DYN bits
Layer3D, 3, 3, 3,// OUT bits 0 DYN bits
OrderedGroup, 1, 2, 1,// OUT bits 0 DYN bits
};

NodeDataTypeNode SF2DNodeNodes[] =
{
Anchor,							2, 3, 2,// 00001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AnimationStream,				3, 3, 3,// 00010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Background2D,					1, 2, 2,// 00011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ColorInterpolator,			1, 2, 2,// 00100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Conditional,					0, 2, 1,// 00101 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
CoordinateInterpolator2D,	1, 2, 2,// 00110 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
DiscSensor,						3, 3, 3,// 00111 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Face,								3, 3, 3,// 01000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Form,								3, 3, 3,// 01001 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Group,							0, 2,	0,// 01010 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
Inline,							0, 0, 0,// 01011 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
LOD,								2, 0, 0,// 01100 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Layer2D,							2, 3,	2,// 01101 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
Layer3D,							3, 3, 3,// 01110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Layout,							4, 4, 4,// 01111 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
OrderedGroup,					1, 2, 1,// 10000 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
PlaneSensor2D,					3, 3, 3,// 10001 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PositionInterpolator2D,		1, 2, 2,// 10010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ProximitySensor2D,			2, 2, 3,// 10011 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
kQuantizationParameter,		6, 0, 0,// 10100 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ScalarInterpolator,			1, 2, 2,// 10101 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Script,							2, 0, 0,// 10110 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Shape,							1, 1, 1,// 10111 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Sound2D,							2, 2, 2,// 11000 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
Switch,							1, 1, 1,// 11001 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TermCap,							0, 1, 1,// 11010 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TimeSensor,						3, 3, 4,// 11011 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
TouchSensor,					0, 0, 3,// 11100 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
Transform2D,					3, 3, 3,// 11101 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Valuator,						4, 5, 5,// 11110 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
WorldInfo,						1, 0, 0,// 11111 1 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SF3DNodeNodes[] =
{
Anchor,							2, 3, 2,// 000001 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AnimationStream,				3, 3, 3,// 000010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Background,						4, 4, 4,// 000011 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
Background2D,					1, 2, 2,// 000100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Billboard,						1, 2, 1,// 000101 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
Collision,						2, 2, 2,// 000110 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ColorInterpolator,			1, 2, 2,// 000111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Conditional,					0, 2, 1,// 001000 0 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
CoordinateInterpolator,		1, 2, 2,// 001001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CoordinateInterpolator2D,	1, 2, 2,// 001010 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
CylinderSensor,				3, 3, 4,// 001011 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
DirectionalLight,				3, 3, 3,// 001100 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
DiscSensor,						3, 3, 3,// 001101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Face,								3, 3, 3,// 001110 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Fog,								2, 2, 2,// 001111 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
Form,								3, 3, 3,// 010000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Group,							0, 2, 0,// 010001 0 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
Inline,							0, 0, 0,// 010010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
LOD,								2, 0, 0,// 010011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Layer2D,							2, 3, 2,// 010100 2 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
Layer3D,							3, 3, 3,// 010101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Layout,							4, 4, 4,// 010110 4 DEF bits 4 IN bits 4 OUT bits 2 DYN bits
ListeningPoint,				2, 2, 3,// 010111 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
NavigationInfo,				3, 3, 3,// 011000 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
NormalInterpolator,			1, 2, 2,// 011001 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
OrderedGroup,					1, 2, 1,// 011010 1 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
OrientationInterpolator,	1, 2, 2,// 011011 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PlaneSensor,					3, 3, 3,// 011100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PlaneSensor2D,					3, 3, 3,// 011101 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PointLight,						3, 3, 3,// 011110 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
PositionInterpolator,		1, 2, 2,// 011111 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
PositionInterpolator2D,		1, 2, 2,// 100000 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
ProximitySensor2D,			2, 2, 3,// 100001 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
ProximitySensor,				2, 2, 3,// 100010 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
kQuantizationParameter,		6, 0, 0,// 100011 6 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ScalarInterpolator,			1, 2, 2,// 100100 1 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Script,							2, 0, 0,// 100101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Shape,							1, 1, 1,// 100110 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
Sound,							4, 4, 4,// 100111 4 DEF bits 4 IN bits 4 OUT bits 3 DYN bits
Sound2D,							2, 2, 2,// 101000 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
SphereSensor,					2, 2, 3,// 101001 2 DEF bits 2 IN bits 3 OUT bits 0 DYN bits
SpotLight,						4, 4, 4,// 101010 4 DEF bits 4 IN bits 4 OUT bits 4 DYN bits
Switch,							1, 1, 1,// 101011 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TermCap,							0, 1, 1,// 101100 0 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
TimeSensor,						3, 3, 4,// 101101 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
TouchSensor,					0, 0, 3,// 101110 0 DEF bits 0 IN bits 3 OUT bits 0 DYN bits
Transform,						3, 3, 3,// 101111 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Transform2D,					3, 3, 3,// 110000 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Valuator,						4, 5, 5,// 110001 4 DEF bits 5 IN bits 5 OUT bits 0 DYN bits
Viewpoint,						3, 3, 3,// 110010 3 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
VisibilitySensor,				2, 2, 3,// 110011 2 DEF bits 2 IN bits 3 OUT bits 1 DYN bits
WorldInfo,						1, 0, 0,// 110100 1 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFAppearanceNodes[] =
{
Appearance, 2, 2, 2,//1 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
};

NodeDataTypeNode SFGeometryNodes[] =
{
Bitmap,				0, 0, 0,// 00001 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Box,					0, 0, 0,// 00010 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Circle,				0, 0, 0,// 00011 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Cone,					2, 0, 0,// 00100 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Curve2D,				2, 2, 2,// 00101 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Cylinder,			3, 0, 0,// 00110 3 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
ElevationGrid,		4, 2, 2,// 00111 4 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
Extrusion,			4, 2, 0,// 01000 4 DEF bits 2 IN bits 0 OUT bits 0 DYN bits
IndexedFaceSet,	4, 3, 2,// 01001 4 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedFaceSet2D, 3, 3, 2,// 01010 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
IndexedLineSet,	3, 2, 1,// 01011 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
IndexedLineSet2D, 3, 2, 1,// 01100 3 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
PointSet,			1, 1, 1,// 01101 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
PointSet2D,			1, 1, 1,// 01110 1 DEF bits 1 IN bits 1 OUT bits 0 DYN bits
bifsRectangle,		0, 0, 0,// 01111 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Sphere,				0, 0, 0,// 10000 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
Text,					2, 2, 2,// 10001 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
};

NodeDataTypeNode SFMaterialNodes[] =
{
Material,		3, 3, 3,// 01 3 DEF bits 3 IN bits 3 OUT bits 3 DYN bits
Material2D,		2, 2, 2,// 10 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
};

NodeDataTypeNode SFTextureNodeNodes[] =
{
CompositeTexture2D,	3, 3, 3,// 001 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
CompositeTexture3D,	3, 4, 3,// 010 3 DEF bits 4 IN bits 3 OUT bits 0 DYN bits
ImageTexture,			2, 0, 0,// 011 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
MovieTexture,			3, 3, 3,// 100 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
PixelTexture,			2, 0, 0,// 101 2 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFLinePropertiesNodeNodes[] =
{
LineProperties,	2, 2, 2,//1 2 DEF bits 2 IN bits 2 OUT bits 1 DYN bits
};

NodeDataTypeNode SFCoordinate2DNodeNodes[] =
{
Coordinate2D,		0, 0, 0,// 1 0 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFAudioNodeNodes[] =
{
AudioBuffer,		3, 3, 4,// 001 3 DEF bits 3 IN bits 4 OUT bits 0 DYN bits
AudioClip,			3, 3, 3,// 010 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
AudioDelay,			2, 2, 1,// 011 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
AudioFX,				3, 3, 2,// 100 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioMix,			3, 3, 2,// 101 3 DEF bits 3 IN bits 2 OUT bits 0 DYN bits
AudioSource,		3, 3, 3,// 110 3 DEF bits 3 IN bits 3 OUT bits 1 DYN bits
AudioSwitch,		2, 2, 1,// 111 2 DEF bits 2 IN bits 1 OUT bits 0 DYN bits
};

NodeDataTypeNode SFColorNodeNodes[] =
{
Color,				0, 0, 0// 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFTextureCoordinateNodeNodes[] =
{
TextureCoordinate, 0, 0, 0,// 0 OUT bits 0 DYN bits
};

NodeDataTypeNode SFFontStyleNodeNodes[] =
{
FontStyle, 4, 0, 0,// 4 DEF bits 0 IN bits 0 OUT bits 0 DYN bits
};

NodeDataType nodeDataTypes[] =
{
	-1, NULL, //BIFS_MFBool, 
	-1, NULL, //BIFS_MFColor, 
	-1, NULL, //BIFS_MFColorRGBA,
	-1, NULL, //BIFS_MFDouble,
	-1, NULL, //BIFS_MFFloat, 
	-1, NULL, //BIFS_MFImage, 
	-1, NULL, //BIFS_MFInt32, 
	-1, NULL, //BIFS_MFNode, 
	-1, NULL, //BIFS_MFRotation, 
	-1, NULL, //BIFS_MFString, 
	-1, NULL, //BIFS_MFTime, 
	-1, NULL, //BIFS_MFVec2d, 
	-1, NULL, //BIFS_MFVec2f, 
	-1, NULL, //BIFS_MFVec3d, 
	-1, NULL, //BIFS_MFVec3f, 

	-1, NULL, //BIFS_MFURL
	-1, NULL, //BIFS_MFCommandBuffer
	-1, NULL, //BIFS_MFScript
	-1, NULL, //BIFS_MFTopNode,
	-1, NULL, //BIFS_MF2DNode,
	-1, NULL, //BIFS_MF3DNode,
	-1, NULL, //BIFS_MFAppearanceNode,
	-1, NULL, //BIFS_MFGeometryNode,
	-1, NULL, //BIFS_MFMaterialNode,
	-1, NULL, //BIFS_MFTextureNode,
	-1, NULL, //BIFS_MFTextureTransform,
	-1, NULL, //BIFS_MFLinePropertiesNode
	-1, NULL, //BIFS_MFCoordinate2DNode
	-1, NULL, //BIFS_MFAudioNode
	-1, NULL, //BIFS_MFColorNode
	-1, NULL, //BIFS_MFTextureCoordinateNode
	-1, NULL, //BIFS_MFFontStyleNode

	-1, NULL, //BIFS_SFBool, 
	-1, NULL, //BIFS_SFColor, 
	-1, NULL, //BIFS_SFColorRGBA, 
	-1, NULL, //BIFS_SFDouble, 
	-1, NULL, //BIFS_SFFloat, 
	-1, NULL, //BIFS_SFImage, 
	-1, NULL, //BIFS_SFInt32, 
	-1, NULL, //BIFS_SFNode, 
	-1, NULL, //BIFS_SFRotation, 
	-1, NULL, //BIFS_SFString, 
	-1, NULL, //BIFS_SFTime, 
	-1, NULL, //BIFS_SFVec2d, 
	-1, NULL, //BIFS_SFVec2f, 
	-1, NULL, //BIFS_SFVec3d, 
	-1, NULL, //BIFS_SFVec3f,

	-1, NULL, //BIFS_SFURL
	-1, NULL, //BIFS_SFCommandBuffer
	-1, NULL, //BIFS_SFScript
	3/*nbits*/, SFTopNodeNodes,
	5/*nbits*/, SF2DNodeNodes,
	6/*nbits*/, SF3DNodeNodes,
	1/*nbits*/, SFAppearanceNodes,
	5/*nbits*/, SFGeometryNodes,
	2/*nbits*/, SFMaterialNodes,
	3/*nbits*/, SFTextureNodeNodes,
	-1, NULL, //BIFS_SFTextureTransform,
	1/*nbits*/, SFLinePropertiesNodeNodes,
	1/*nbits*/, SFCoordinate2DNodeNodes,
	3/*nbits*/, SFAudioNodeNodes,
	1/*nbits*/, SFColorNodeNodes,
	1/*nbits*/, SFTextureCoordinateNodeNodes,
	1/*nbits*/, SFFontStyleNodeNodes,
};

// EXT

NodeDataTypeNode SF2DNodeExtNodes[] =
{
-1, //PROTO 01
ApplicationWindow,// 10 3 DEF bits 3 IN bits 3 OUT bits 0 DYN bits
Body// 11 2 DEF bits 2 IN bits 2 OUT bits N bits
};

NodeDataTypeNode SF3DNodeExtNodes[] =
{
-1,//PROTO 001
AcousticScene,// 010 3 DEF bits 1 IN bits 1 OUT bits 1 DYN bits
Body,// 011 2 DEF bits 2 IN bits 2 OUT bits 0 DYN bits
DirectiveSound,// 100 4 DEF bits 3 IN bits 3 OUT bits 2 DYN bits
Hierarchical3DMesh,// 101 1 DEF bits 1 IN bits 1 OUT bits bits};
};

NodeDataType nodeDataTypesExt[] =
{
	-1, NULL, //BIFS_MFBool, 
	-1, NULL, //BIFS_MFColor, 
	-1, NULL, //BIFS_MFColorRGBA,
	-1, NULL, //BIFS_MFDouble,
	-1, NULL, //BIFS_MFFloat, 
	-1, NULL, //BIFS_MFImage, 
	-1, NULL, //BIFS_MFInt32, 
	-1, NULL, //BIFS_MFNode, 
	-1, NULL, //BIFS_MFRotation, 
	-1, NULL, //BIFS_MFString, 
	-1, NULL, //BIFS_MFTime, 
	-1, NULL, //BIFS_MFVec2d, 
	-1, NULL, //BIFS_MFVec2f, 
	-1, NULL, //BIFS_MFVec3d, 
	-1, NULL, //BIFS_MFVec3f, 

	-1, NULL, //BIFS_MFURL
	-1, NULL, //BIFS_MFTopNode,
	-1, NULL, //BIFS_MF2DNode,
	-1, NULL, //BIFS_MF3DNode,
	-1, NULL, //BIFS_MFAppearanceNode,
	-1, NULL, //BIFS_MFGeometryNode,
	-1, NULL, //BIFS_MFMaterialNode,
	-1, NULL, //BIFS_MFTextureNode,
	-1, NULL, //BIFS_MFTextureTransform,
	-1, NULL, //BIFS_MFLinePropertiesNode
	-1, NULL, //BIFS_MFCoordinate2DNode
	-1, NULL, //BIFS_MFAudioNode
	-1, NULL, //BIFS_MFColorNode
	-1, NULL, //BIFS_MFTextureCoordinateNode

	-1, NULL, //BIFS_SFBool, 
	-1, NULL, //BIFS_SFColor, 
	-1, NULL, //BIFS_SFColorRGBA, 
	-1, NULL, //BIFS_SFDouble, 
	-1, NULL, //BIFS_SFFloat, 
	-1, NULL, //BIFS_SFImage, 
	-1, NULL, //BIFS_SFInt32, 
	-1, NULL, //BIFS_SFNode, 
	-1, NULL, //BIFS_SFRotation, 
	-1, NULL, //BIFS_SFString, 
	-1, NULL, //BIFS_SFTime, 
	-1, NULL, //BIFS_SFVec2d, 
	-1, NULL, //BIFS_SFVec2f, 
	-1, NULL, //BIFS_SFVec3d, 
	-1, NULL, //BIFS_SFVec3f,

	-1, NULL, //BIFS_MFURL
	-1/*nbits*/, NULL,//SFTopNodeNodes,
	2/*nbits*/, SF2DNodeExtNodes,
	3/*nbits*/, SF3DNodeExtNodes,

	-1/*nbits*/, NULL,//SFAppearanceNodes,
	-1/*nbits*/, NULL,//SFGeometryNodes,
	-1/*nbits*/, NULL,//SFMaterialNodes,
	-1/*nbits*/, NULL,//SFTextureNodeNodes,
	-1, NULL, //BIFS_SFTextureTransform,
	-1/*nbits*/, NULL,//SFLinePropertiesNodeNodes,
	-1/*nbits*/, NULL,//SFCoordinate2DNodeNodes,
	-1/*nbits*/, NULL,//SFAudioNodeNodes,
	-1/*nbits*/, NULL,//SFColorNodeNodes,
	-1/*nbits*/, NULL,//SFTextureCoordinateNodeNodes,
};

/*
Returns the nodeType of the node indexed by localNodeType in the node data type table. The nodeType of a
node is its index in the SFWorldNode NDT Table.
*/
int GetNodeType(int nodeDataType, int localNodeType)
{
	return nodeDataTypes[nodeDataType].nodes[localNodeType-1].index;
}

int GetExtNodeType(int nodeDataType, int extlocalNodeType)
{
	return nodeDataTypesExt[nodeDataType].nodes[extlocalNodeType-1].index;
}

/*
Returns the number of bits used to index the nodes of the matching node data type table (this number is indicated
in the last column of the first row of the node data type table).
*/
int GetNDTnbBits(int nodeDataType)
{
	return nodeDataTypes[nodeDataType].nbits;
}

int GetNDTnbBitsExt(int nodeDataType)
{
	return nodeDataTypesExt[nodeDataType].nbits;
}

////////////////////////////////////////////////////

/*
Table 19 - Quantization Categories
Category Description
0 None
1 3D position
2 2D positions
3 Drawing order
4 SFColor
5 Texture Coordinate
6 Angle
7 Scale
8 Interpolator keys
9 Normals
10 Rotations
11 Object Size 3D (1)
12 Object Size 2D (2)
13 Linear Scalar Quantization
14 CoordIndex
15 Reserved

*/

// use double for Vmin and Vmax to get higher precision in the calculations

int quantize(double Vmin, double Vmax, float v, int Nb)
{
	return (int)(((v - Vmin) / (Vmax - Vmin)) * ((2<<Nb) -1));
}

float invQuantize(double Vmin, double Vmax, int vq, int Nb)
{
//	return Vmin + vq * ((Vmax - Vmin) / ((1<<(max(Nb,1))) -1));
	return Vmin + vq * ((Vmax - Vmin) / (pow(2,max(Nb,1)) -1));
}

void ReadQuantizedField(CBitStream* pBitStream, CFieldData& fieldData, int comps, int vq[])
{
	switch (fieldData.field->quantType)
	{
	case 9:
		{
			int direction = pBitStream->getbit();
		}
		break;

	case 10:
		{
			int orientation = pBitStream->getnbits(2);
		}
		break;
	}

	/*
	for (int i = 0; i < getNbComp(field);i++)
	{
		int(field.nbBits) vq[i]
	}
	*/
	for (int i = 0; i < comps; i++)
	{
		//int(field.nbBits) vq[i]
		vq[i] = pBitStream->getnbits(fieldData.nbBits);
	}
}

float ReadEfficientFloat(CBitStream* pBitStream)
{
	ASSERT(0);

	int mantissaLength = pBitStream->getnbits(4);
	if (mantissaLength != 0)
	{
#if 0
		int exponentLength = pBitStream->getnbits(3);
		int mantissaSign = pBitStream->getbit();
		int mantissa = pBitStream->getnbits(mantissaLength-1);

		int exponentSign;
		int exponent;

		if (exponentLength != 0)
		{
			exponentSign = pBitStream->getbit();
			exponent = pBitStream->getnbits(exponentLength-1);
		}
		else
		{
			exponent = 0;
		}

		(1-2*mantissaSign)*(pow(2, mantissaLength-1)+mantissa) * pow(2, (1-2*exponentSign)*(pow(2, exponentLength-1)+exponent));
#endif
	return 0;
	}
	else
	{
		return 0;
	}
}

class number
{
public:
	number(int v)
	{
	}

	number(float v)
	{
	}

	union
	{
		int intv;
		float floatv;
	}
	value;
};

number ReadNumber(CBitStream* pBitStream)
{
	int isInteger = pBitStream->getbit();
	if (isInteger)
	{
		int numbits = pBitStream->getnbits(5);  // number of bits the integer is represented
		long value = pBitStream->getnbits(numbits);// integer value

		return value;
	}
	else
	{
		int floatChar = pBitStream->getnbits(4); // 0-9, ., E,-, END_SYMBOL
		while (floatChar!= 13/*END_SYMBOL*/)
		{
			floatChar = pBitStream->getnbits(4);
		}
		return (long)0;	// TODO
	}
}

float ReadGenericFloat(CBitStream* pBitStream, BOOL useEfficientCoding)
{
	if (!useEfficientCoding)
	{
		DWORD value = pBitStream->getnbits(32);
		float fvalue = *(float*)&value;

		return fvalue;
	}
	else
	{
		ASSERT(0);
	//	EfficientFloat value;
		return 0;
	}
}

void ReadSFBool(CBitStream* pBitStream, bool* pVal)
{
	ASSERT(pVal != NULL);
	*pVal = pBitStream->getbit();
}

void ReadSFInt32(CBitStream* pBitStream, CFieldData& fieldData, long* pVal)
{
	ASSERT(pVal != NULL);
	if (fieldData.isQuantized)
	{
		int vq[1];
		ReadQuantizedField(pBitStream, fieldData, 1, vq);

		*pVal = fieldData.intMin[0] + vq[0];

		ASSERT(*pVal >= fieldData.field->m && *pVal <= fieldData.field->M);

#if 0
		*pVal = invQuantize(fieldData.floatMin[0], fieldData.floatMax[0], vq[0], fieldData.nbBits);
#endif
	}
	else
	{
		*pVal = pBitStream->getnbits(32);
	}

//	TRACE("int32: %d\n", *pVal);
}

void ReadSFFloat(CBitStream* pBitStream, CFieldData& field, float* pVal)//FieldData field)
{
	ASSERT(pVal != NULL);
	if (field.isQuantized)
	{
		ASSERT(0);
	//	QuantizedField qvalue(field);
	}
	else
	{
		*pVal = ReadGenericFloat(pBitStream, field.useEfficientCoding);
	//	TRACE("float: %g\n", *pVal);
	}
}

void ReadSFTime(CBitStream* pBitStream, CFieldData& field, double* pVal)//FieldData field)
{
	ASSERT(pVal != NULL);
	__int64 intvalue = pBitStream->getlonglong();
	*pVal = *(double*)&intvalue;
}

void ReadSFVec2f(CBitStream* pBitStream, CFieldData& fieldData, float value[2])
{
	ASSERT(value != NULL);

	if (fieldData.isQuantized)
	{
		int vq[2];
		ReadQuantizedField(pBitStream, fieldData, 2, vq);

		value[0] = invQuantize(fieldData.floatMin[0], fieldData.floatMax[0], vq[0], fieldData.nbBits);
		value[1] = invQuantize(fieldData.floatMin[1], fieldData.floatMax[1], vq[1], fieldData.nbBits);
	}
	else
	{
		value[0] = ReadGenericFloat(pBitStream, fieldData.useEfficientCoding);
		value[1] = ReadGenericFloat(pBitStream, fieldData.useEfficientCoding);
	}

	//TRACE("vec2f: %g, %g\n", value[0], value[1]);
}

void ReadSFVec3f(CBitStream* pBitStream, CFieldData& field, float value[3])
{
	ASSERT(value != NULL);

	if (field.isQuantized)
	{
		ASSERT(0);
		//ReadQuantizedField(pBitStream, field);
	}
	else
	{
		value[0] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[1] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[2] = ReadGenericFloat(pBitStream, field.useEfficientCoding);

	//	TRACE("vec2f: %g, %g, %g\n", value[0], value[1], value[2]);
	}
}

void ReadSFColor(CBitStream* pBitStream, CFieldData& field, float value[3])
{
	ASSERT(value != NULL);

	if (field.isQuantized)
	{
		ASSERT(0);
		//QuantizedField qvalue(field);
	}
	else
	{
		value[0] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[1] = ReadGenericFloat(pBitStream, field.useEfficientCoding);
		value[2] = ReadGenericFloat(pBitStream, field.useEfficientCoding);

		TRACE("color: %g, %g, %g\n", value[0], value[1], value[2]);
	}
}

void ReadSFString(CBitStream* pBitStream, CFieldData& field)
{
	int lengthBits = pBitStream->getnbits(5);
	if (lengthBits > 0)
	{
		int length = pBitStream->getnbits(lengthBits);

		//char(8) value[length];
		for (int i = 0; i < length; i++)
		{
			pBitStream->getnbits(8);
		}
	}
}

void ReadSFUrl(CBitStream* pBitStream, CFieldData& field, long* pODid)
{
	int isOD = pBitStream->getbit();
	if (isOD)
	{
		*pODid = pBitStream->getnbits(10);
	}
	else
	{
		*pODid = 0;
		ReadSFString(pBitStream, field);//SFString urlValue;
	}
}

void ReadSFCommandBuffer(CBitStream* pBitStream)
{
	int lengthBits = pBitStream->getnbits(5);
	int length = pBitStream->getnbits(lengthBits);
	for (int i = 0; i < length; i++)
	{
		BYTE value = pBitStream->getnbits(8);//bit(8) value[length];
	}
}

/*
Table 33 - Field Types for Script fields and PROTO fields.
fieldType value Field type
0bx000000 SFBool
0bx000001 SFFloat
0bx000010 SFTime
0bx000011 SFInt32
0bx000100 SFString
0bx000101 SFVec3f
0bx000110 FVec2f
0bx000111 SFColor
0bx001000 SFRotation
0bx001001 SFImage
0bx001010 SFNode
0bx100000 MFBool
0bx100001 MFFloat
0bx100010 MFTime
0bx100011 MFInt32
0bx100100 MFString
0bx100101 MFVec3f
0bx100110 MFVec2f
0bx100111 MFColor
0bx101000 MFRotation
0bx101001 MFImage
0bx101010 MFNode
*/
BIFSFieldType BIFSFieldTypes[] =
{
	BIFS_MFBool,
	BIFS_MFFloat,
	BIFS_MFTime,
	BIFS_MFInt32,
	BIFS_MFString,
	BIFS_MFVec3f,
	BIFS_MFVec2f,
	BIFS_MFColor,
	BIFS_MFRotation,
	BIFS_MFImage,
	BIFS_MFNode,
	/*
	BIFS_MFBool,
	BIFS_MFFloat,
	BIFS_MFTime,
	BIFS_MFInt32,
	BIFS_MFString,
	BIFS_MFVec3f,
	BIFS_MFVec2f,
	BIFS_MFColor,
	BIFS_MFRotation,
	BIFS_MFImage,
	BIFS_MFNode,
	*/
};

FieldType FieldTypes[] =
{
	MFBool,
	MFFloat,
	MFTime,
	MFInt32,
	MFString,
	MFVec3f,
	MFVec2f,
	MFColor,
	MFRotation,
	MFImage,
	MFNode,
	/*
	MFBool,
	MFFloat,
	MFTime,
	MFInt32,
	MFString,
	MFVec3f,
	MFVec2f,
	MFColor,
	MFRotation,
	MFImage,
	MFNode,
	*/
};

#if 0
void CBIFSDecoder::ReadScriptField(CBitStream* pBitStream, CScriptNode& scriptNode, CNodeData& nodeData)
{
	int eventType = pBitStream->getnbits(2);	// 0, 1, and 2 representing fields, eventIns and eventOuts,
	int fieldType = pBitStream->getnbits(6);
	CWCharString fieldName = ReadString(pBitStream);//String;

	if (eventType == 0)
	{
		scriptNode.m_INFields++;
		scriptNode.m_OUTFields++;
	}
	else if (eventType == 1)
	{
		scriptNode.m_INFields++;
	}
	else if (eventType == 2)
	{
		scriptNode.m_OUTFields++;
	}

	if (eventType == 0/*FIELD*/)
	{
		int hasInitialValue = pBitStream->getbit();
		if (hasInitialValue)
		{
#if 0
			NodeData node = makeNode(ScriptNodeType);
			Field(node.field[fieldType]) value;
#endif
			Field field;
			field.name = fieldName;

			field.fieldType = BIFSFieldTypes[fieldType & ~0x20];
			if (!(fieldType & 0x20))	// SF
				field.fieldType = (BIFSFieldType)((int)field.fieldType + (int)BIFS_SFBool);

			FieldType ftype = FieldTypes[fieldType & ~0x20];
			if (!(fieldType & 0x20))	// SF
				ftype = (FieldType)((int)ftype + (int)SFBool);

			CFieldData fieldData;
			fieldData.field = &field;

			CComPtr<ILX3DField> x3dfield;
			CComQIPtr<ILX3DScriptNode>(nodeData.x3dnode)->createField(fieldName, ftype, &x3dfield);

			ReadField(pBitStream, nodeData, fieldData, x3dfield, NULL, FALSE);
		}
	}

	if (TRUE)
	{
		CIdentifier identifier;
		identifier.m_name = fieldName;
		scriptNode.m_identifiers.Add(identifier);
	}
}

void CBIFSDecoder::ReadScriptFieldsListDescription(CBitStream* pBitStream, CScriptNode& scriptNode, CNodeData& nodeData)
{
	int endFlag = pBitStream->getbit(); // List description of the fields
	while (!endFlag)
	{
		ReadScriptField(pBitStream, scriptNode, nodeData);
		endFlag = pBitStream->getbit();//bit(1) endFlag;
	}
}

void CBIFSDecoder::ReadScriptFieldsVectorDescription(CBitStream* pBitStream, CScriptNode& scriptNode, CNodeData& nodeData)
{
	int fieldBits = pBitStream->getnbits(4); // Number of bits for number of fields

	int numFields = pBitStream->getnbits(fieldBits); // Number of fields in the script
	for (int i = 0; i < numFields; i++)
	{
		ReadScriptField(pBitStream, scriptNode, nodeData);
	}
}

sysstring CBIFSDecoder::ReadIdentifier(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int received = pBitStream->getbit();
	if (received)
	{
		int num = GetNBits(scriptNode.m_identifiers.GetSize());
		int identifierCode = pBitStream->getnbits(num);// identifierCode // num is calculated by counting

		ASSERT(identifierCode < scriptNode.m_identifiers.GetSize());

	// number of distinguished identifiers
	// received so far
		TRACE("identifier reuse: %d\n", identifierCode);

		return scriptNode.m_identifiers[identifierCode].m_name;
	}
	else
	{
		CIdentifier identifier;
		identifier.m_name = ReadString(pBitStream);
		scriptNode.m_identifiers.Add(identifier);

		TRACE("identifier: %S\n", (BSTR)identifier.m_name);

		return identifier.m_name;
	}
}

void CBIFSDecoder::ReadArguments(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int hasArgument = pBitStream->getbit();

	while (hasArgument)
	{
		ReadIdentifier(pBitStream, scriptNode);/// identifier;
		hasArgument = pBitStream->getbit();
	}
}

enum
{
	ifStatementType = 0,
	forStatementType = 1,
	whileStatementType = 2,
	returnStatementType = 3,
	compoundExpressionType = 4,
	breakStatementType = 5,
	continueStatementType = 6,
	switchStatementType = 7,
};

void CBIFSDecoder::ReadParams(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int hasParam = pBitStream->getbit();
	while(hasParam)
	{
		ReadExpression(pBitStream, scriptNode);// expression;
		hasParam = pBitStream->getbit();
	}
}

/*
curvedExpressionType=0:
The expression consists of a compoundExpression.
NegativeExpressionType=1:
An expression shall be evaluated and the value returned shall be negated.
NotExpressionType=2:
An expression shall be evaluated and its returned value shall be logically negated (empty values return nonempty,
zero values return non-zero, and vice-versa).
OnescompExpressionType=3:
An expression shall be evaluated numerically (string values will yield an undefined result) and the value returned
shall be bitwise negated.
IncrementExpressionType=4:
An expression shall be evaluated numerically (string values will yield an undefined result) and the value returned
shall incremented by 1.
DecrementExpressionType=5:
An expression shall be evaluated numerically (string values will yield an undefined result) and the value returned
shall be decremented by 1.
PostIncrementExpressionType=6:
An expression shall be evaluated numerically (string values will yield an undefined result) and its returned value
shall be incremented by 1. The returned value of this expression shall be the value prior to the increment being
applied.
PostDecrementExpressionType=7:
An expression shall be evaluated numerically (string values will yield an undefined result) and its returned value
shall be decremented by 1. The returned value of this expression shall be the value prior to the decrement being
applied.
ConditionExpressionType=8:
Three expressions shall be evaluated. If the first expression returns a non-zero or non-empty value, then the
returned value of this expression shall be the value of the second expression. Otherwise, the returned value of
this expression shall be the value of the third expression.
StringExpressonType=9:
The expression contains a string.
NumberExpressionType=10:
The expression is a number.
VariableExpressionType=11:
Licensed to /SIGURD LERSTAD
ISO Store order #: 575943/Downloaded: 2003-12-28
Single user licence only, copying and networking prohibited
ISO/IEC 14496-1:2001(E)
© ISO/IEC 2001 – All rights reserved 123
The expression is a variable and shall return the value held by the variable determined by identifier.
FunctionCallExpressionType=12:
An identifier determines which function shall be evaluated. The params shall be passed to the function
by value. The returned value of the expression shall be the value returned by the function in its
returnStatement.
ObjectConstructExpressionType=13:
A new object shall be created (using a ‘new’ statement in the script) and the object shall be held in the variable
determined by identifier. A list of params shall be passed to any constructors that exist for the object.
ObjectMemberAccessExpressionType=14:
A member variable of an object shall be accessed and the returned value of the expression shall be the value in
this member variable. Normally, the first expression will evaluate to a node in the scene graph (which is
accessed through a script variable). This means that the first expression will normally evaluate to an
identifier reference. The following identifier will then refer to a field of the node.
ObjectMethodCallExpressionType=15:
A method of an object shall be evaluated. The first expression shall evaluate to an object. The following
identifier shall specify a method of this object. The following params shall be passed to the method. The value
of this expression shall be the value returned by the method.
ArrayDereferenceExpressionType=16:
The expression shall be an array element reference. The first expression shall evaluate to an array reference.
The following compoundExpression shall evaluate to a number that shall then be used to index the array. The
returned value of this expression shall be the value held in the referenced array element.
The following binary operands evaluate two expressions and return a value based on a binary operation of these
two expressions. The binary operation and value of expressionType is listed below for each binary operation.
Unless explicitely stated, a string value for either of the expressions will yield an undefined result.
BinaryOperand(=) = 17:
The first expression shall evaluate to an identifier which shall be assigned the value of the second
expression.
BinaryOperand(+=) = 18:
The first expression shall evaluate to an identifier. If the value held by the variable is numerical, the variable
value shall be incremented by the value of the second expression, which shall also evaluate to a numerical
value. If the variable is a string, then its new value shall be its original value with the second expression (which
shall be a string) appended.
BinaryOperand(-=) = 19:
The first expression shall evaluate to an identifier whose value shall be decremented by the value of the
second expression.
BinaryOperand(*=) = 20:
The first expression shall evaluate to an identifier whose value shall be set to its current value multiplied by
the value of the second expression.
BinaryOperand(/=) = 21:
The first expression shall evaluate to an identifier whose value shall be set to its current value divided by
the value of the second expression.
BinaryOperand(%=) = 22:
The first expression shall evaluate to an identifier whose value shall be set to its current value modulo the
value of the second expression. The expressions shall both evaluate to integer values.
BinaryOperand(&=) = 23:
The first expression shall evaluate to an identifier whose value shall be set to its current value logically
bitwise ANDed with the value of the second expression.
BinaryOperand(|=) = 24:
Licensed to /SIGURD LERSTAD
ISO Store order #: 575943/Downloaded: 2003-12-28
Single user licence only, copying and networking prohibited
ISO/IEC 14496-1:2001(E)
124 © ISO/IEC 2001 – All rights reserved
The first expression shall evaluate to an identifier whose value shall be set to its current value logically
bitwise ORed with the value of the second expression.
BinaryOperand(^=) = 25:
The first expression shall evaluate to an identifier whose value shall be set to its current value logically
bitwise EXCLUSIVE-ORed with the value of the second expression.
BinaryOperand(<<=) = 26:
The first expression shall evaluate to an identifier whose value shall be set to its current value bitwise
shifted to the left a number of bits specified by the second expression.
BinaryOperand(>>=) = 27:
The first expression shall evaluate to an identifier whose value shall be set to its current value bitwise
shifted to the right a number of bits specified by the second expression.
BinaryOperand(>>>=) = 28:
The first expression shall evaluate to an identifier whose value shall be set to its current value bitwise
shifted to the right (with the least significant bits looped) a number of bits specified by the second expression.
BinaryOperand(==) = 29:
This expression shall return a non-zero value when the first and second expression are identical. Otherwise, the
result of this expression shall be zero.
BinaryOperand(!=) = 30:
This expression shall return a non-zero value when the first and second expression are not identical. Otherwise,
the result of this expression shall be zero.
BinaryOperand(<) = 31:
This expression shall return a non-zero value when the first expression is numerically or lexicographically less
than the second. Otherwise, the result of this expression shall be zero.
BinaryOperand(<=) = 32:
This expression shall return a non-zero value when the first expression is numerically or lexicographically less
than or equal to the second. Otherwise, the result of this expression shall be zero.
BinaryOperand(>) = 33:
This expression shall return a non-zero value when the first expression is numerically or lexicographically greater
than the second. Otherwise, the result of this expression shall be zero.
BinaryOperan(>=) = 34:
This expression shall return a non-zero value when the first expression is numerically or lexicographically greater
than or equal to the second. Otherwise, the result of this expression shall be zero.
BinaryOperand(+) = 35:
This expression shall return the sum of the first and second expressions. If both expressions are strings, then
the result shall be the first string concatenated with the second.
BinaryOperand(-) = 36:
This expression shall return the difference of the first and second expressions.
BinaryOperand(*) = 37:
This expression shall return the product of the first and second expressions.
BinaryOperand(/) = 38:
This expression shall returns the quotient of the first and second expressions.
BinaryOperand(%) = 39:
This expression shall return the value of the first expression modulo the second expression.
BinaryOperand(&&) = 40:
This expression shall return the logical AND of the first and second expressions.
BinaryOperand(||) = 41:
Licensed to /SIGURD LERSTAD
ISO Store order #: 575943/Downloaded: 2003-12-28
Single user licence only, copying and networking prohibited
ISO/IEC 14496-1:2001(E)
This expression shall return the logical OR of the first and second expressions.
BinaryOperand(&) = 42:
This expression shall return the logical bitwise AND of the first and second expressions.
BinaryOperand(|) = 43:
This expression shall return the logical bitwise OR of the first and second expressions.
BinaryOperand(^) = 44:
This expression shall return the logical bitwise XOR of the first and second expressions.
BinaryOperand(<<) = 45:
This expression shall return the value of the first expression shifted to the left by the number of bits specified as
the value of the second expression.
BinaryOperand(>>) = 46:
Returns the value of the first expression shifted to the right by the number of bits specified as the value of the
second expression.
BinaryOperand(>>>) = 47:
This expression shall return the value of the first expression shifted to the right (with the least significant bit
looped to the most significant bit) by the number of bits specified as the value of the second expression.
*/

NODEP CBIFSDecoder::ReadExpression(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int expressionType = pBitStream->getnbits(6);

	switch (expressionType)
	{
	case 0://curvedExpressionType: // (compoundExpression)
		{
			ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
		}
		break;
		
	case 1://negativeExpressionType: // -expression
	case 2://notExpressionType: // !expression
	case 3://onescompExpressionType: // ~expression
	case 4://incrementExpressionType: // ++expression
	case 5://decrementExpressionType: // --expression
	case 6://postIncrementExpressionType: // expression++
	case 7://postDecrementExpressionType: // expression--
		{
			ReadExpression(pBitStream, scriptNode);// expression;
		}
		break;
		
	case 8://conditionExpressionType: // expression ? expression : expression
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadExpression(pBitStream, scriptNode);// Expression expression;
		}
		break;
		
	case 9://stringExpressonType:
		{
			//String string;
			NODEP np = allocnode();
			np->e_token = SCON2;
			CWCharString str = ReadString(pBitStream);
			np->e.vu.bstrval = str.copyBSTR();
			
			return np;
		}
		break;
		
	case 10://numberExpressionType:
		{
			NODEP np = allocnode();
			
			_variant_t number = ReadNumber(pBitStream);
			
			if (number.vt == VT_I4)
			{
				np->e_token = ICON;
				np->e_ival = number.lVal;
			}
			else if (number.vt == VT_R8)
			{
				np->e_token = FCON;
				np->e_ival = number.dblVal;
			}
			else
				ASSERT(0);
			
			return np;
		}
		break;
		
	case 11://variableExpressionType:
		{
			ReadIdentifier(pBitStream, scriptNode);// identifier;
		}
		break;
		
	case 12://functionCallExpressionType:
	case 13://objectConstructExpressionType:
		{
			ReadIdentifier(pBitStream, scriptNode);// identifier;
			ReadParams(pBitStream, scriptNode);// params;
		}
		break;
		
	case 14://objectMemberAccessExpressionType:
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadIdentifier(pBitStream, scriptNode);// identifier;
		}
		break;
		
	case 15://objectMethodCallExpressionType:
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadIdentifier(pBitStream, scriptNode);// identifier;
			ReadParams(pBitStream, scriptNode);// params;
		}
		break;
		
	case 16://arrayDereferenceExpressionType:
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
		}
		break;
		
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		// =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=, >>>=,
		// ==, !=, <, <=, >, >=, +, -, *, /, %, &&, ||, &, |,
		// ^, <<, >>, >>>
		{
			ReadExpression(pBitStream, scriptNode);// expression;
			ReadExpression(pBitStream, scriptNode);// expression;
		}
		break;
		
	default:
		{
			MessageBeep(-1);
			//	ReadExpression(pBitStream, scriptNode);// expression;
		}
		break;
	}
	
	return NULL;
}

/*
A CompoundExpression is a list of expressions, terminated when hasExpression has value 0. The value of
the compound expression shall be the value of the last evaluated expression.
*/
NODEP CBIFSDecoder::ReadCompoundExpression(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	NODEP np = allocnode();

	int hasExpression;
	do
	{
		NODEP left = ReadExpression(pBitStream, scriptNode);// expression;

		// Npt sure about this
		np->e.left = left;
		np = left;

		hasExpression = pBitStream->getbit();
	}
	while (hasExpression);

	return np;
}

void CBIFSDecoder::ReadOptionalExpression(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int hasCompoundExpression = pBitStream->getbit();
	if (hasCompoundExpression)
	{
		ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
	}
}

void CBIFSDecoder::ReadIFStatement(CBitStream* pBitStream, CScriptNode& scriptNode, CIfStatement& stmt)
{
	stmt.test_expr = ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
	ReadStatementBlock(pBitStream, scriptNode, stmt.m_if_block);// statementBlock;

	int hasELSEStatement = pBitStream->getbit();
	if (hasELSEStatement)
	{
		ReadStatementBlock(pBitStream, scriptNode, stmt.m_else_block);// statementBlock;
	}
}

void CBIFSDecoder::ReadFORStatement(CBitStream* pBitStream, CScriptNode& scriptNode, CForStatement& stmt)
{
	ReadOptionalExpression(pBitStream, scriptNode);// optionalExpression;
	ReadOptionalExpression(pBitStream, scriptNode);// optionalExpression;
	ReadOptionalExpression(pBitStream, scriptNode);// optionalExpression;

	ReadStatementBlock(pBitStream, scriptNode, stmt.m_block);// statementBlock;
}

void CBIFSDecoder::ReadRETURNStatement(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int returnValue = pBitStream->getbit();
	if (returnValue)
	{
		ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
	}
}

CStatement* CBIFSDecoder::ReadStatement(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int statementType = pBitStream->getnbits(3);

	switch (statementType)
	{
	case ifStatementType:
		{
			CIfStatement* pIf = new CIfStatement;

			ReadIFStatement(pBitStream, scriptNode, *pIf);// ifStatement;

			return pIf;
		}
		break;

	case forStatementType:
		{
			CForStatement* pFor = new CForStatement;

			ReadFORStatement(pBitStream, scriptNode, *pFor);// forStatement;

			return pFor;
		}
		break;

	case whileStatementType:
		{
			ASSERT(0);
			MessageBeep(-1);
//		WHILEStatement whileStatement;
		}
		break;

	case returnStatementType:
		{
			ReadRETURNStatement(pBitStream, scriptNode);// returnStatement;
		}
		break;

	case compoundExpressionType:
		{
			ReadCompoundExpression(pBitStream, scriptNode);// compoundExpression;
		}
		break;

	case breakStatementType:
	case continueStatementType:
		{
			MessageBeep(-1);
		}
		break;

	case switchStatementType:
		{
			ASSERT(0);
			MessageBeep(-1);
//			SWITCHStatement switchStatement;
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

void CBIFSDecoder::ReadStatementBlock(CBitStream* pBitStream, CScriptNode& scriptNode, CStatementBlock& statementBlock)
{
	int isCompoundStatement = pBitStream->getbit();

	if (isCompoundStatement)
	{
		int hasStatement = pBitStream->getbit();
		while (hasStatement)
		{
			CStatement* pStatement = ReadStatement(pBitStream, scriptNode);// statement;
			ASSERT(pStatement);
			statementBlock.m_stmts.AddTail(pStatement);

			hasStatement = pBitStream->getbit();
		}
	}
	else
	{
		CStatement* pStatement = ReadStatement(pBitStream, scriptNode);// statement;
		ASSERT(pStatement);
		statementBlock.m_stmts.AddTail(pStatement);
	}
}

void CBIFSDecoder::ReadFunction(CBitStream* pBitStream, CScriptNode& scriptNode, CScriptItem* pItem)
{
	pItem->m_name = ReadIdentifier(pBitStream, scriptNode);// identifier;

	CComObject<CLScriptFunction>* pFunction;
	CComObject<CLScriptFunction>::CreateInstance(&pFunction);
	pFunction->AddRef();

	pItem->m_disp = pFunction;

	ReadArguments(pBitStream, scriptNode);// arguments;

	ReadStatementBlock(pBitStream, scriptNode, pFunction->m_stmts);// statementBlock;
}

void CBIFSDecoder::ReadEncodedScript(CBitStream* pBitStream, CScriptNode& scriptNode)
{
	int hasFunction = pBitStream->getbit();
	while (hasFunction)
	{
		CScriptItem* pItem = new CScriptItem;

		ReadFunction(pBitStream, scriptNode, pItem);// function;

		scriptNode.m_pEngine->m_pDispatch->m_items.Add(pItem);

		hasFunction = pBitStream->getbit();
	}
}
#endif

void CBIFSDecoder::ReadSFScript(CBitStream* pBitStream, CNodeData& nodeData)
{
	CScriptNode scriptNode;
	scriptNode.m_INFields = 0;
	scriptNode.m_OUTFields = 0;

	ASSERT(0);
#if 0
	int isListDescription = pBitStream->getbit();//bit(1);
	if (isListDescription)
	{
		ReadScriptFieldsListDescription(pBitStream, scriptNode, nodeData);
	}
	else
	{
		ReadScriptFieldsVectorDescription(pBitStream, scriptNode, nodeData);
	}

	nodeData.nINbits = GetNBits(scriptNode.m_INFields);
	nodeData.nOUTbits = GetNBits(scriptNode.m_OUTFields);

//	INbits = GetNBits(scriptNode.m_INFields);
//	OUTbits = GetNBits(scriptNode.m_OUTFields);

	int reserved = pBitStream->getbit();//const bit(1) reserved=1;
	ASSERT(reserved == 1);

	ReadEncodedScript(pBitStream, scriptNode);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CBIFSDecoder

void CBIFSDecoder::ReadChildNode(CBitStream* pBitStream, CFieldData& field, int fieldType, CLX3DField* x3dfield, QuantizationParameter* lqp, bool lqp_deep, CLX3DNode* *pVal)
{
	CLX3DNode* x3dnode;
	ReadSFNode(pBitStream, fieldType, lqp, lqp_deep, &x3dnode);

	dynamic_cast<CLMFNode*>(x3dfield)->append1Value(x3dnode);

	*pVal = x3dnode;
}

void CBIFSDecoder::ReadSFField(CBitStream* pBitStream, CNodeData& nodeData, CFieldData& field, int fieldType, CLX3DField* x3dfield, QuantizationParameter* lqp, bool lqp_deep)
{
	bool sf = (field.field->fieldType >= BIFS_SFBool);

//	HRESULT_throw hr(S_OK);

	switch (fieldType)
	{
	case BIFS_SFNode:	// ??
	case BIFS_SF2DNode:
	case BIFS_SF3DNode:
	case BIFS_SFAppearanceNode:
	case BIFS_SFGeometryNode:
	case BIFS_SFMaterialNode:
	case BIFS_SFTextureNode:
	case BIFS_SFTextureTransform:	// Why doesn't this end with Node ???
	case BIFS_SFLinePropertiesNode:
	case BIFS_SFCoordinate2DNode:
	case BIFS_SFAudioNode:
	case BIFS_SFFontStyleNode:
		{
			CLX3DNode* x3dnode;
			ReadSFNode(pBitStream, fieldType, lqp, lqp_deep, &x3dnode);

			if (sf)
				dynamic_cast<CLSFNode*>(x3dfield)->setValue(x3dnode);
			else
				dynamic_cast<CLMFNode*>(x3dfield)->append1Value(x3dnode);
		}
		break;

	case BIFS_SFBool:
		{
			bool value;
			ReadSFBool(pBitStream, &value);

			if (sf)
				dynamic_cast<CLSFBool*>(x3dfield)->setValue(value);
			else
				dynamic_cast<CLMFBool*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFInt32:
		{
			long value;
			ReadSFInt32(pBitStream, field, &value);

			if (sf)
				dynamic_cast<CLSFInt32*>(x3dfield)->setValue(value);
			else
				dynamic_cast<CLMFInt32*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFFloat:
		{
			float value;
			ReadSFFloat(pBitStream, field, &value);

			if (sf)
				dynamic_cast<CLSFFloat*>(x3dfield)->setValue(value);
			else
				dynamic_cast<CLMFFloat*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFTime:
		{
			double value;
			ReadSFTime(pBitStream, field, &value);

			if (sf)
				dynamic_cast<CLSFTime*>(x3dfield)->setValue(value);
			else
				ASSERT(0);//dynamic_cast<CLMFTime*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec2f:
		{
			float value[2];
			ReadSFVec2f(pBitStream, field, value);

			if (sf)
				dynamic_cast<CLSFVec2f*>(x3dfield)->setValue(value);
			else
				dynamic_cast<CLMFVec2f*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec3f:
		{
			float value[3];
			ReadSFVec3f(pBitStream, field, value);

			if (sf)
				dynamic_cast<CLSFVec3f*>(x3dfield)->setValue(value);
			else
				dynamic_cast<CLMFVec3f*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFColor:
		{
			float value[3];
			ReadSFColor(pBitStream, field, value);

			if (sf)
				dynamic_cast<CLSFColor*>(x3dfield)->setValue(value);
			else
				dynamic_cast<CLMFColor*>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFString:
		{
			ReadSFString(pBitStream, field);

			// TODO
		}
		break;

	case BIFS_SFURL:
		{
			long ODid;
			ReadSFUrl(pBitStream, field, &ODid);

			if (sf)
				ASSERT(0);//hr = CComQIPtr<ILSFURL>(x3dfield)->setValue(ODid, NULL);
			else
				dynamic_cast<CLMFURL*>(x3dfield)->append1Value(ODid, NULL);
		}
		break;

	case BIFS_SFCommandBuffer:
		{
			ReadSFCommandBuffer(pBitStream);
			// TODO
		}
		break;

	case BIFS_SFScript:
		{
			ReadSFScript(pBitStream, nodeData);
			//SFScript scriptValue();
			// TODO
		}
		break;

	default:
		ASSERT(0);
		throw L"TODO: Unimplemented parsing of field type";
	}
}

void CBIFSDecoder::ReplaceSFField(CBitStream* pBitStream, CFieldData& field, int fieldType, CLX3DField* x3dfield, QuantizationParameter* lqp, bool lqp_deep, int where)
{
	BOOL sf = (field.field->fieldType >= BIFS_SFBool);

	HRESULT_throw hr(S_OK);

	switch (fieldType)
	{
	case BIFS_SFNode:	// ??
	case BIFS_SF2DNode:
	case BIFS_SF3DNode:
	case BIFS_SFAppearanceNode:
	case BIFS_SFGeometryNode:
	case BIFS_SFMaterialNode:
	case BIFS_SFLinePropertiesNode:
	case BIFS_SFCoordinate2DNode:
	case BIFS_SFAudioNode:
		{
			CLX3DNode* x3dnode;
			ReadSFNode(pBitStream, fieldType, lqp, lqp_deep, &x3dnode);

#if 0
			if (sf)
				hr = CComQIPtr<ILSFNode>(x3dfield)->setValue(x3dnode);
			else
#endif
				dynamic_cast<CLMFNode*>(x3dfield)->set1Value(0, x3dnode);
		}
		break;

#if 0
	case BIFS_SFBool:
		{
			VARIANT_BOOL value;
			ReadSFBool(pBitStream, &value);

			if (sf)
				hr = CComQIPtr<ILSFBool>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFBool>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFInt32:
		{
			long value;
			ReadSFInt32(pBitStream, field, &value);

			if (sf)
				hr = CComQIPtr<ILSFInt32>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFInt32>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFFloat:
		{
			float value;
			ReadSFFloat(pBitStream, field, &value);

			if (sf)
				hr = CComQIPtr<ILSFFloat>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFFloat>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec2f:
		{
			float value[2];
			ReadSFVec2f(pBitStream, field, value);

			if (sf)
				hr = CComQIPtr<ILSFVec2f>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFVec2f>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFVec3f:
		{
			float value[3];
			ReadSFVec3f(pBitStream, field, value);

			if (sf)
				hr = CComQIPtr<ILSFVec3f>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFVec3f>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFColor:
		{
			float value[3];
			ReadSFColor(pBitStream, field, value);

			if (sf)
				hr = CComQIPtr<ILSFColor>(x3dfield)->setValue(value);
			else
				hr = CComQIPtr<ILMFColor>(x3dfield)->append1Value(value);
		}
		break;

	case BIFS_SFURL:
		{
			ReadSFUrl(pBitStream, field);
		}
		break;
#endif

	default:
		ASSERT(0);
		throw L"TODO: Unimplemented parsing of field type";
	}
}

void CBIFSDecoder::ReadMFListDescription(CBitStream* pBitStream, CNodeData& nodeData, CFieldData& fieldData, CLX3DField* x3dfield, QuantizationParameter* lqp, bool lqp_deep)
{
	if (!wcscmp(fieldData.field->name, L"children"))
	{
		while (!pBitStream->getbit())
		{
			if (lqp && !lqp_deep)
			{
				if (lqp->getIsLocal())	// Means that it only applies to one sibling
				{
					lqp = NULL;
				}
			}

			CLX3DNode* x3dnode;
			ReadChildNode(pBitStream, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep, &x3dnode);

			QuantizationParameter* qp = dynamic_cast<QuantizationParameter*>(x3dnode);
			if (qp)
			{
				lqp = qp;
				lqp_deep = false;
			}
		}
	}
	else
	{
		while (!pBitStream->getbit())
		{
			ReadSFField(pBitStream, nodeData, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep);	// fieldtype from MF to SF
		}
	}
}

void CBIFSDecoder::ReadMFVectorDescription(CBitStream* pBitStream, CNodeData& nodeData, CFieldData& fieldData, CLX3DField* x3dfield, QuantizationParameter* lqp, bool lqp_deep)
{
	int NbBits = pBitStream->getnbits(5);
	int numberOfFields = pBitStream->getnbits(NbBits);

	if (!wcscmp(fieldData.field->name, L"children"))
	{
		for (int i = 0; i < numberOfFields; i++)
		{
			if (lqp && !lqp_deep)
			{
				if (lqp->getIsLocal())	// Means that it only applies to one sibling
				{
					lqp = NULL;
				}
			}

			CLX3DNode* x3dnode;
			ReadChildNode(pBitStream, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep, &x3dnode);

			QuantizationParameter* qp = dynamic_cast<QuantizationParameter*>(x3dnode);
			if (qp)
			{
				lqp = qp;
				lqp_deep = FALSE;
			}
		}
	}
	else
	{
		for (int i = 0; i < numberOfFields; i++)
		{
			ReadSFField(pBitStream, nodeData, fieldData, (int)fieldData.field->fieldType + (int)BIFS_SFBool, x3dfield, lqp, lqp_deep);	// fieldtype from MF to SF
		}
	}
}

void CBIFSDecoder::ReadMFField(CBitStream* pBitStream, CNodeData& nodeData, CFieldData& field, CLX3DField* x3dfield, QuantizationParameter* lqp, bool lqp_deep)
{
	int reserved = pBitStream->getbit();
	if (!reserved)
	{
		int isListDescription = pBitStream->getbit();
		if (isListDescription)
		{
			ReadMFListDescription(pBitStream, nodeData, field, x3dfield, lqp, lqp_deep);
		}
		else
		{
			ReadMFVectorDescription(pBitStream, nodeData, field, x3dfield, lqp, lqp_deep);
		}
	}
	else
		ASSERT(0);
}

void CBIFSDecoder::ReadField(CBitStream* pBitStream, CNodeData& nodeData, CFieldData& fieldData, CLX3DField* x3dfield, QuantizationParameter* lqp, bool lqp_deep)
{
	fieldData.isQuantized = FALSE;// is set to true when the three following conditions are met :
	if (lqp != NULL)
	{
		if (fieldData.field->quantType > 0)//!= 0)
		{
			VARIANT_BOOL quant = VARIANT_FALSE;

			switch (fieldData.field->quantType)
			{
			case 2:
				{
					lqp->getPosition2DQuant(&quant);
				}
				break;

			case 4:
				{
					lqp->getColorQuant(&quant);
				}
				break;

			case 12:
				{
					lqp->getSizeQuant(&quant);
				}
				break;

			case 13:
			case 14:
			case 15:
				{
					quant = VARIANT_TRUE;
				}
				break;

			default:
				ASSERT(0);
			}

			if (quant)
			{
				fieldData.isQuantized = TRUE;

				/*
				quantType nbBits
				1 lqp.position3DNbBits
				2 lqp.position2DNbBits
				3 lqp.drawOrderNbBits
				4 lqp.colorNbBits
				5 lqp.textureCoordinateNbBits
				6 lqp.angleNbBits
				7 lqp.scaleNbBits
				8 lqp.keyNbBits
				9,10 lqp.normalNbBits
				11,12 lqp.sizeNbBits
				13 fct.defaultNbBits
				14 This value is set according to the number
				of points received in the last received
				coord field of the node. Let N that number,
				then:
				. . ) ( log Ceil nbBits 2 N .
				where the function Ceil returns the
				smallest integer greater than its argument
				15 0
				*/

				switch (fieldData.field->quantType)
				{
				case 2:
					{
						lqp->getPosition2DNbBits(&fieldData.nbBits);
					}
					break;

				case 4:
					{
						lqp->getColorNbBits(&fieldData.nbBits);
					}
					break;

				case 11:
				case 12:
					{
						lqp->getSizeNbBits(&fieldData.nbBits);
					}
					break;

				case 13:
					{
						fieldData.nbBits = fieldData.field->defaultNbBits;
					}
					break;

				case 15:
					{
						fieldData.nbBits = 0;
					}
					break;

				default:
					ASSERT(0);
				}

				// floatMin
				switch (fieldData.field->quantType)
				{
				case 2:
					{
						lqp->getPosition2DMin(fieldData.floatMin);
					}
					break;

				case 11:
				case 12:
					{
						if (fieldData.field->fieldType == BIFS_SFFloat)
						{
							lqp->getSizeMin(&fieldData.floatMin[0]);
						}
						else if (fieldData.field->fieldType == BIFS_SFVec2f)
						{
							lqp->getSizeMin(&fieldData.floatMin[0]);
							lqp->getSizeMin(&fieldData.floatMin[1]);
						}
						else if (fieldData.field->fieldType == BIFS_SFVec3f)
						{
							lqp->getSizeMin(&fieldData.floatMin[0]);
							lqp->getSizeMin(&fieldData.floatMin[1]);
							lqp->getSizeMin(&fieldData.floatMin[2]);
						}
						else
							ASSERT(0);
					}
					break;

				case 13:
				case 14:
				case 15:
					{
						/* ??
						NULL
							floatMin[0] = 0;
							floatMin[1] = 0;
							floatMin[2] = 0;
							floatMin[3] = 0;
							*/
					}
					break;

				default:
					ASSERT(0);
				}

				// floatMax
				switch (fieldData.field->quantType)
				{
				case 2:
					{
						lqp->getPosition2DMax(fieldData.floatMax);
					}
					break;

				case 11:
				case 12:
					{
						if (fieldData.field->fieldType == BIFS_SFFloat)
						{
							lqp->getSizeMax(&fieldData.floatMax[0]);
						}
						else if (fieldData.field->fieldType == BIFS_SFVec2f)
						{
							lqp->getSizeMax(&fieldData.floatMax[0]);
							lqp->getSizeMax(&fieldData.floatMax[1]);
						}
						else if (fieldData.field->fieldType == BIFS_SFVec3f)
						{
							lqp->getSizeMax(&fieldData.floatMax[0]);
							lqp->getSizeMax(&fieldData.floatMax[1]);
							lqp->getSizeMax(&fieldData.floatMax[2]);
						}
						else
							ASSERT(0);
					}
					break;

				case 13:
				case 14:
				case 15:
					{
						/* ??
						NULL
							floatMin[0] = 0;
							floatMin[1] = 0;
							floatMin[2] = 0;
							floatMin[3] = 0;
							*/
					}
					break;

				default:
					ASSERT(0);
				}

				// intMin
				switch (fieldData.field->quantType)
				{
				case 13:
				case 14:
					{
						fieldData.intMin[0] = fieldData.field->m;
					}
					break;

				default:
					{
					// NULL???
					}
					break;
				}
			}
		}
	/*
	.lqp!=0 (there is a QuantizationParameter node in the scope of the field)
	.quantType !=0 (the field value is of a type that may be quantized), and
	.the following condition is met for the relevant quantization type:
		quantType Condition
		1 lqp.position3DQuant == TRUE
		2 lqp.position2DQuant == TRUE
		3 lqp.drawOrderQuant == TRUE
		4 lqp.colorQuant == TRUE
		5 lqp.textureCoordinateQuant == TRUE
		6 lqp.angleQuant == TRUE
		7 lqp.scaleQuant == TRUE
		8 lqp.keyQuant == TRUE
		9 lqp.normalQuant == TRUE
		10 lqp.normalQuant == TRUE
		11 lqp.sizeQuant == TRUE
		12 lqp.sizeQuant == TRUE
		13 Always TRUE
		14 Always TRUE
		15 Always TRUE
*/
	}

	ASSERT(x3dfield);

	if (fieldData.field->fieldType >= BIFS_SFBool)
		ReadSFField(pBitStream, nodeData, fieldData, fieldData.field->fieldType, x3dfield, lqp, lqp_deep);
	else
		ReadMFField(pBitStream, nodeData, fieldData, x3dfield, lqp, lqp_deep);
}

void CBIFSDecoder::ReadMaskNodeDescription(CBitStream* pBitStream, CNodeData* nodeData, QuantizationParameter* lqp, bool lqp_deep)
{
#if 0	// TODO have this
	if (node.protoData != null)
	{
		for (i=0; i<node.numALLfields; i++)
		{
			bit(1) Mask;
			if (Mask)
			{
				bit(1) isedField;
				if (isedField)
				{
					unsigned int(node.proto.nALLbits) protoField;
				}
				else
				{
					Field value(node.field[i]]);
				}
			}
		}
	}
	else
#endif
	{ //regular list of fields – not from a PROTO
		//for (int i = 0; i < node->numDEFfields; i++)
		int i = 0;
		while (nodeData->node->fields[i].name)
		{
			if (nodeData->node->fields[i].bDef)
			{
				//if (node->fields[i].
				int Mask = pBitStream->getbit();
				if (Mask)
				{
					CLX3DField* x3dfield = nodeData->x3dnode->getField(nodeData->node->fields[i].name);
					if (x3dfield == NULL)
					{
						ASSERT(0);
						throw L"Couldn't get field on node";
					}

					// TODO
					//Field value(node.field[node.def2all[i]]);
					TRACE("\tfield: %S:%S\n", nodeData->node->nodeName, nodeData->node->fields[i].name);

					CFieldData fieldData;
					fieldData.field = &nodeData->node->fields[i];

					ReadField(pBitStream, *nodeData, fieldData, x3dfield, lqp, lqp_deep);
				}
			}

			i++;
		}
		//ASSERT(node->fields[i].name);	// Couldn't find field?
	}
}

void CBIFSDecoder::ReadListNodeDescription(CBitStream* pBitStream, CNodeData* nodeData, QuantizationParameter* lqp, bool lqp_deep)
{
	while (!pBitStream->getbit())
	{
#if 0	// TODO
		if (node.protoData != null )
		{
			bit(1) isedField;
			if (isedField){
				bit(node.nALLbits) fieldRef;
				bit(node.proto.nALLbits) protoField;
			} else {
				bit(node.nDEFbits) fieldRef;
				Field value(node.field[node.def2all[fieldRef]]);
			}
		}
		else
#endif
		{
//			Node* node = nodeData.node;//&nodes[GetNodeType(nodeDataType, localNodeType)];

			int nDEFbits = nodeDataTypes[nodeData->nodeDataType].nodes[nodeData->localNodeType-1].nDEFbits;

			int fieldRef;
			if (nDEFbits)
				fieldRef = pBitStream->getnbits(nDEFbits);
			else
				fieldRef = 0;

			int n = 0;
			int i = 0;
			while (nodeData->node->fields[i].name)
			{
				if (nodeData->node->fields[i].bDef)
				{
					if (fieldRef == n)
					{
						CLX3DField* x3dfield = nodeData->x3dnode->getField(nodeData->node->fields[i].name);
						if (x3dfield == NULL)
						{
							ASSERT(0);
							throw L"Couldn't get field on node";
						}

						TRACE("\tfield: %S:%S\n", nodeData->node->nodeName, nodeData->node->fields[i].name);

						CFieldData fieldData;
						fieldData.field = &nodeData->node->fields[i];

						ReadField(pBitStream, *nodeData, fieldData, x3dfield, lqp, lqp_deep);
						break;
					}
					n++;
				//	Field value(node.field[node.def2all[fieldRef]]);
				}
				i++;
			}
			ASSERT(nodeData->node->fields[i].name);	// Couldn't find field?
		}
	}
}

void CBIFSDecoder::ReadSFNode(CBitStream* pBitStream, int nodeDataType, QuantizationParameter* lqp, bool lqp_deep, CLX3DNode* *pVal)
{
	ASSERT(pVal != NULL);
	*pVal = NULL;

	int isReused = pBitStream->getbit();
	if (isReused)
	{
		int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
		TRACE("USE %d\n", nodeID);

		CNodeDef* pDef = FindNode(nodeID);
		if (pDef)
		{
			*pVal = pDef->nodeData->x3dnode;
		}
		else
		{
		// ???
	//		ASSERT(0);
	//		throw L"USE of undefined DEF";
		}
	}
	else
	{
		CNodeData* nodeData = new CNodeData;
		nodeData->nodeDataType = nodeDataType;
		nodeData->localNodeType = pBitStream->getnbits(GetNDTnbBits(nodeDataType));

		int nodeType;
		int extLocalNodeType = 0;

		CLX3DNode* x3dnode;

		if (nodeData->localNodeType == 0)
		{
			//return;
			throw (ErrorCode)S_FALSE;

			extLocalNodeType = pBitStream->getnbits(6/*GetNDTnbBitsExt(nodeDataType)*/);
			if (extLocalNodeType == 1)
			{
				ASSERT(0);
				int PROTOnodeType = pBitStream->getnbits(m_pBIFSConfig->PROTOIDbits);
#if 0
				nodeType = GetPROTONodeType(PROTODataType,PROTOnodeType)
#endif
			}
			else if (extLocalNodeType > 1)
			{
				nodeType = GetExtNodeType(nodeDataType, extLocalNodeType);
			}
			else
				ASSERT(0);
		}
		else
		{
			nodeType = GetNodeType(nodeData->nodeDataType, nodeData->localNodeType);

			TRACE("node: %S", nodes[nodeType].nodeName);

			x3dnode = m_scene->createNode(nodes[nodeType].nodeName);
			ASSERT(x3dnode != NULL);
			if (x3dnode == NULL)
			{
				ASSERT(0);
				throw L"Couldn't create node";
			}

			nodeData->x3dnode = x3dnode;

			nodeData->nINbits = nodeDataTypes[nodeData->nodeDataType].nodes[nodeData->localNodeType-1].nINbits;
			nodeData->nOUTbits = nodeDataTypes[nodeData->nodeDataType].nodes[nodeData->localNodeType-1].nOUTbits;

			nodeData->node = &nodes[nodeType];

			*pVal = x3dnode;
		}

		int isUpdateable = pBitStream->getbit();
		if (isUpdateable)
		{
			CNodeDef* pDef = new CNodeDef;
			//pDef->m_nodeDataType = nodeData.nodeDataType;
			//pDef->m_localNodeType = nodeData.localNodeType;

			pDef->m_nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
			TRACE(" DEF %d", pDef->m_nodeID);

			//pDef->m_nodeDataType = &nodeDataTypes[nodeDataType].nodes[localNodeType-1];
			//pDef->m_x3dnode = x3dnode;
			pDef->nodeData = nodeData;
			m_defs.Add(pDef);

			if (m_USENAMES)
			{
				sysstring name = ReadString(pBitStream);
			}
		}
		TRACE("\n");

		if (	(extLocalNodeType == 0) &&
				(nodeType == IndexedFaceSet) &&
				(m_pBIFSConfig->use3DmeshCoding == 1))
		{
			ASSERT(0);
	#if 0
			Mesh3D mnode;
	#endif
		}
		else
		{
			int MaskAccess = pBitStream->getbit();
			if (MaskAccess)
			{
				ReadMaskNodeDescription(pBitStream, nodeData, lqp, TRUE);
			}
			else
			{
				ReadListNodeDescription(pBitStream, nodeData, lqp, TRUE);
			}
		}
	}
}

// Commands

ErrorCode CBIFSDecoder::IndexedValueInsertion(CBitStream* pBitStream)
{
	int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);

	CNodeDef* pDef = FindNode(nodeID);
	ASSERT(pDef);

//	NodeUpdateField node=GetNodeFromID(nodeID);

	int inID = pBitStream->getnbits(nodeDataTypes[pDef->nodeData->nodeDataType].nodes[pDef->nodeData->localNodeType-1].nINbits);
	int insertionPosition = pBitStream->getnbits(2);

	int nodeType = GetNodeType(pDef->nodeData->nodeDataType, pDef->nodeData->localNodeType);
	Field* fields = nodes[nodeType].fields;
	int j = 0;
	int i = 0;
	while (fields[i].name)
	{
		if (fields[i].bIn)
		{
			if (inID == j)
			{
				break;
			}
			j++;
		}
		i++;
	}
	Field* field = &fields[j];
	if (field->name == NULL)
	{
		TRACE("Trying to insert a value into a non-input field");
		ASSERT(0);
		return E_FAIL;
	}

	if (field->fieldType >= BIFS_SFBool)
	{
		TRACE("Trying to insert a value into a single valued field");
		ASSERT(0);
		return E_FAIL;
	}

	CLX3DField* x3dfield = pDef->nodeData->x3dnode->getField(field->name);
	if (x3dfield == NULL)
	{
		TRACE("Couldn't find field on node");
		ASSERT(0);
		return E_FAIL;
	}

	switch (insertionPosition)
	{
	case 0: // insertion at a specified position
		{
			WORD position = pBitStream->getnbits(16);

			//SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 2: // insertion at the beginning of the field
		{
			ASSERT(0);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 3: // insertion at the end of the field
		{
			//CNodeData nodeData;
			//nodeData.x3dnode = pDef->m_x3dnode;

			CFieldData fieldData;
			fieldData.field = field;
			ReadSFField(pBitStream, *pDef->nodeData, fieldData, (int)field->fieldType + (int)BIFS_SFBool, x3dfield, NULL, false);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;
	}

	return S_OK;
}

ErrorCode CBIFSDecoder::FieldReplacement(CBitStream* pBitStream)
{
//	bit(BIFSConfiguration.nodeIDbits) nodeID ;
	int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
//	NodeData node = GetNodeFromID(nodeID);
	CNodeDef* pDef = FindNode(nodeID);
	ASSERT(pDef);
	if (pDef == NULL)
		return E_FAIL;

//	int(node.nINbits) inID;
	int inID = pBitStream->getnbits(nodeDataTypes[pDef->nodeData->nodeDataType].nodes[pDef->nodeData->localNodeType-1].nINbits);

	int nodeType = GetNodeType(pDef->nodeData->nodeDataType, pDef->nodeData->localNodeType);
	Field* fields = nodes[nodeType].fields;
	int j = 0;
	int i = 0;
	while (fields[i].name)
	{
		if (fields[i].bIn)
		{
			if (inID == j)
			{
				break;
			}
			j++;
		}
		i++;
	}
	Field* field = &fields[j];
	if (field->name == NULL)
	{
		TRACE("Trying to insert a value into a non-input field");
		ASSERT(0);
		return E_FAIL;
	}

	CLX3DField* x3dfield = pDef->nodeData->x3dnode->getField(field->name);
	if (x3dfield == NULL)
	{
		TRACE("Couldn't find field on node");
		ASSERT(0);
		return E_FAIL;
	}

	//CNodeData nodeData;
	//nodeData.x3dnode = pDef->m_x3dnode;

	CFieldData fieldData;
	fieldData.field = field;
	ReadField(pBitStream, *pDef->nodeData, fieldData, x3dfield, NULL, FALSE);

#if 0
	Field value(node.field[node.in2all[inID]]);
#endif

	return S_OK;
}

ErrorCode CBIFSDecoder::IndexedValueReplacement(CBitStream* pBitStream)
{
	int nodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);

//	NodeData node = GetNodeFromID(nodeID);
	CNodeDef* pDef = FindNode(nodeID);
	ASSERT(pDef);

	int inID = pBitStream->getnbits(nodeDataTypes[pDef->nodeData->nodeDataType].nodes[pDef->nodeData->localNodeType-1].nINbits);
	//int inID = (node.nINbits);
	int replacementPosition = pBitStream->getnbits(2);

	int nodeType = GetNodeType(pDef->nodeData->nodeDataType, pDef->nodeData->localNodeType);
	Field* fields = nodes[nodeType].fields;
	int j = 0;
	int i = 0;
	while (fields[i].name)
	{
		if (fields[i].bIn)
		{
			if (inID == j)
			{
				break;
			}
			j++;
		}
		i++;
	}
	Field* field = &fields[j];
	if (field->name == NULL)
	{
		TRACE("Trying to insert a value into a non-input field");
		ASSERT(0);
		return E_FAIL;
	}

	if (field->fieldType >= BIFS_SFBool)
	{
		TRACE("Trying to replace a value into a single valued field");
		ASSERT(0);
		return E_FAIL;
	}

	CLX3DField* x3dfield = pDef->nodeData->x3dnode->getField(field->name);
	if (x3dfield == NULL)
	{
		TRACE("Couldn't find field on node");
		ASSERT(0);
		return E_FAIL;
	}

	switch (replacementPosition)
	{
	case 0: // replacement at a specified position
		{
			int position = pBitStream->getnbits(16);

			ASSERT(0);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 2: // replacement at the beginning of the field
		{
			CFieldData fieldData;
			fieldData.field = field;
			ReplaceSFField(pBitStream, fieldData, (int)field->fieldType + (int)BIFS_SFBool, x3dfield, NULL, FALSE, 0);

			//	SFField value(node.field[node.in2all[inID]]);
		}
		break;

	case 3: // replacement at the end of the field
		{
			ASSERT(0);
			//SFField value(node.field[node.in2all[inID]]);
		}
		break;
	}

	return S_OK;
}

void CBIFSDecoder::ReadROUTE(CBitStream* pBitStream)
{
	int isUpdateable = pBitStream->getbit();
	if (isUpdateable)
	{
		int routeID = pBitStream->getnbits(m_pBIFSConfig->routeIDbits);
		if (m_USENAMES)
		{
			sysstring routeName = ReadString(pBitStream);
		}
	}

	int outNodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
	CNodeDef* pOutNodeDef = FindNode(outNodeID);
	//if (nodeDataTypes[pOutNodeDef->m_nodeDataType].nodes[pOutNodeDef->m_localNodeType-1].nOUTbits)
	{
		int outFieldRef = pBitStream->getnbits(pOutNodeDef->nodeData->nOUTbits);
	}
//	NodeData nodeOUT = GetNodeFromID(outNodeID);
	//int outFieldRef = pOutNodeDef->int(nodeOUT.nOUTbits);

	int inNodeID = pBitStream->getnbits(m_pBIFSConfig->nodeIDbits);
	CNodeDef* pInNodeDef = FindNode(inNodeID);
	//NodeData nodeIN = GetNodeFromID(inNodeID);
	//int(nodeIN.nINbits) inFieldRef;
	//if (nodeDataTypes[pInNodeDef->m_nodeDataType].nodes[pInNodeDef->m_localNodeType-1].nINbits > 0)

	{
	//	int inFieldRef = pBitStream->getnbits(nodeDataTypes[pInNodeDef->m_nodeDataType].nodes[pInNodeDef->m_localNodeType-1].nINbits);
		int inFieldRef = pBitStream->getnbits(pInNodeDef->nodeData->nINbits);
	}
}

ErrorCode CBIFSDecoder::ReadScene(CBitStream* pBitStream)
{
	CLMFNode* rootNodes = m_scene->getRootNodes();

	try
	{
		int reserved = pBitStream->getnbits(6);// reserved;
		m_USENAMES = pBitStream->getnbits(1);// USENAMES;

	//	PROTOlist protos;
		while (pBitStream->getbit() == 1)
		{
			ASSERT(0);
			//PROTOdeclaration() proto;
		}

		//SFNode nodes(SFTopNode);
		CLX3DNode* x3dnode;
		try
		{
			ReadSFNode(pBitStream, BIFS_SFTopNode, NULL, FALSE, &x3dnode);
		}
		catch (int err)
		{
		}

		if (x3dnode)
		{
			rootNodes->append1Value(x3dnode);
		}

		int hasROUTEs = pBitStream->getbit();
		if (hasROUTEs)
		{
			int ListDescription = pBitStream->getbit();
			if (ListDescription)
			{
				//ListROUTEs lroutes();
				int moreROUTEs;
				do
				{
					ReadROUTE(pBitStream);// route();
					moreROUTEs = pBitStream->getbit();
				}
				while (moreROUTEs);
			}
			else
			{
				//VectorROUTEs vroutes();
				int nBits = pBitStream->getnbits(5);
				int length = pBitStream->getnbits(nBits);
				for (int i = 0; i < length; i++)
				{
					ReadROUTE(pBitStream);// route[length]();
				}
			}
		}
	}
	catch (ErrorCode hr)
	{
		return hr;
	}

	return S_OK;
}

void InsertionCommand(CBitStream* pBitStream, CBIFSDecoder* m_pBIFSScene)
{
	HRESULT_throw hr(S_OK);

	int parameterType = pBitStream->getnbits(2);

	switch (parameterType)
	{
	case 0:
		{
			ASSERT(0);
//			NodeInsertion nodeInsert();
		}
		break;

	case 1:	// Not an option
		{
			ASSERT(0);
			// Which one of the two below ??
			throw L"Unrecognized BIFS Insertion parameter";
			//hr = E_FAIL;
		}
		break;

	case 2:
		{
			hr = m_pBIFSScene->IndexedValueInsertion(pBitStream);
//			IndexedValueInsertion idxInsert();
		}
		break;

	case 3:
		{
			ASSERT(0);
//			ROUTEInsertion ROUTEInsert();
		}
		break ;
	}
}

void ReplacementCommand(CBitStream* pBitStream, CBIFSDecoder* m_pBIFSScene)
{
	HRESULT_throw hr(S_OK);

	int parameterType = pBitStream->getnbits(2);

	switch (parameterType)
	{
	case 0:
		{
			ASSERT(0);
		//	NodeReplacement nodeReplace();
		}
		break;

	case 1:
		{
		//	FieldReplacement fieldReplace();
			m_pBIFSScene->FieldReplacement(pBitStream);
		}
		break;

	case 2:
		{
			//ASSERT(0);
			//IndexedValueReplacement idxReplace();
			m_pBIFSScene->IndexedValueReplacement(pBitStream);
		}
		break;

	case 3:
		{
			ASSERT(0);
			//ROUTEReplacement ROUTEReplace();
		}
		break;
	}
}

ErrorCode CBIFSDecoder::ReadBIFSCommandFrame(System::IO::CByteStream* stream)
{
	CBitStream bitstream(stream);

	BOOL bContinue;
	do
	{
		// Command
		int code = bitstream.getnbits(2);

		switch (code)
		{
		case 0:	// Insert
			{
				if (m_scene)
				{
					InsertionCommand(&bitstream, this);
				}
				else
				{
					ASSERT(0);
					return E_FAIL;
				}
			}
			break;

		case 1:	// Delete
			{
				if (m_scene)
				{
					ASSERT(0);
					MessageBeep(-1);
				}
				else
				{
					ASSERT(0);
					return E_FAIL;
				}
			}
			break;

		case 2:	// Replace
			{
				if (m_scene)
				{
					ReplacementCommand(&bitstream, this);
				}
				else
				{
					ASSERT(0);
					return E_FAIL;
				}
			}
			break;

		case 3:	// Scene Replace
			{
				/*
				if (m_scene)
				{
					m_scene.Release();
				}
				*/

				ASSERT(0);
#if 0
				CComPtr<ILMediaSample> sample;
				m_pOutputPin->m_pAllocator->GetBuffer(0, &sample);

				ErrorCode hr = m_scene.CoCreateInstance(CLSID_LX3DScene);
				if (SUCCEEDED(hr))
				{
					CComQIPtr<ILBIFSScene>(m_scene)->setBIFSContext(m_pOutputPin);

					ErrorCode hr = ReadScene(&bitstream);
				}
				else
					return hr;
#endif
			}
			break;
		}

		bContinue = bitstream.getbit();
	}
	while (bContinue);

	return S_OK;
}
#endif

// ILMediaFilter

static DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
	//CoInitialize(NULL);

	ErrorCode hr;

//	EnterCriticalSection(&pFilter->m_pLock);

	CBIFSDecoder* p = (CBIFSDecoder*)lpParameter;

	//CComQIPtr<ILMemInputPin> memInput = p->m_pOutputPin->m_connectedTo;
	//if (memInput)
	{
//		CComObject<CBIFSDecoder::CLBIFSSample>* sample;
//		CComObject<CBIFSDecoder::CLBIFSSample>::CreateInstance(&sample);
//		sample->AddRef();

	//	IBIFSSample* sample;
		IMediaSample* sample;
		p->m_pOutputPin->m_pAllocator->GetBuffer(0, &sample);

#if 0
		if (pVideo->m_sample == NULL)
		{
			pVideo->m_allocator->GetBuffer(0, (ILMediaSample**)&pVideo->m_sample);
		}
#endif

		p->m_pDec->m_stream.Seek(p->m_pDec->m_pTrack->m_chunks[0].m_offset, IO::STREAM_SEEK_SET);

		double t = 0;
		p->m_pDec->m_currentPosition = 0;

		for (int i = 0; i < p->m_pDec->m_pTrack->m_samples.GetSize(); i++)
		{
			p->m_pDec->m_currentFrame = i;

			p->ReadBIFSCommandFrame(p->m_pDec->m_stream);
#if 0
			sample->m_scene = p->m_scene;
#endif

			LONGLONG t = (LONGLONG)1 * p->m_pDec->m_currentPosition / p->m_pDec->m_pTrack->m_mediaHeader.m_timeScale;

			LONGLONG duration = p->m_pDec->m_pTrack->m_samples[i].m_duration / p->m_pDec->m_pTrack->m_mediaHeader.m_timeScale;
			LONGLONG timeStart = t;
			LONGLONG timeEnd = t+duration;
			sample->SetTime(&timeStart, &timeEnd);

			p->m_pDec->m_currentPosition += p->m_pDec->m_pTrack->m_samples[i].m_duration;

			hr = p->m_pOutputPin->m_pInputPin->Receive(sample);
			if (hr != Success_True)
			{
				break;
			}
		}
	}

	if (hr >= 0)	// Don't send this if the downstream filter failed in Receive?
		p->m_pOutputPin->ConnectedTo()->EndOfStream();

//	CoUninitialize();

	return 0;
}

ErrorCode CBIFSDecoder::Run(LONGLONG tStart)
{
	m_criticalSection.Lock();

	m_state = State_Running;
	m_tStart = tStart;

	m_criticalSection.Unlock();

	if (m_pOutputPin->ConnectedTo() == NULL)	// Not connected ??
		return Success;

	ASSERT(0);
#if 0
	m_hThread = CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(CBIFSDecoder*)this, 0, &m_threadId);
#endif
//	WaitForSingleObject(m_hThread, INFINITE);

#if 0
	m_hAudioThread = CreateThread(NULL, NULL, RunningAudioThreadProc, (LPVOID)this, 0, &m_audioThreadId);
#endif

//	RunningAudioThreadProc(this);

	return Success;
}

}	// Media
}
