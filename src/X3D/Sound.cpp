#include "stdafx.h"
#include "X3D2.h"
#include "Sound.h"

#include "AudioClip.h"

#pragma comment(lib, "x3daudio.lib")

namespace System
{

namespace Gui
{
GUIEXT XAUDIO2_DEVICE_DETAILS deviceDetails;
GUIEXT X3DAUDIO_HANDLE X3DInstance;
}

namespace x3d
{

NodeType* Sound::nodeType(GetNodeType());

TypedX3DFieldDefinition<SFVec3f>* Sound::get_locationFieldDef()
{
	static TypedX3DFieldDefinition<SFVec3f> location("location", SAIFieldAccess_inputOutput, offsetof(Sound, m_location));
	return &location;
}

TypedX3DFieldDefinition<SFVec3f>* Sound::get_directionFieldDef()
{
	static TypedX3DFieldDefinition<SFVec3f> direction("direction", SAIFieldAccess_inputOutput, offsetof(Sound, m_direction));
	return &direction;
}

TypedX3DFieldDefinition<SFFloat>* Sound::get_intensityFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> intensity("intensity", SAIFieldAccess_inputOutput, offsetof(Sound, m_intensity));
	return &intensity;
}

TypedX3DFieldDefinition<SFFloat>* Sound::get_maxBackFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> maxBack("maxBack", SAIFieldAccess_inputOutput, offsetof(Sound, m_maxBack));
	return &maxBack;
}

TypedX3DFieldDefinition<SFFloat>* Sound::get_maxFrontFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> maxFront("maxFront", SAIFieldAccess_inputOutput, offsetof(Sound, m_maxFront));
	return &maxFront;
}

TypedX3DFieldDefinition<SFFloat>* Sound::get_minBackFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> minBack("minBack", SAIFieldAccess_inputOutput, offsetof(Sound, m_minBack));
	return &minBack;
}

TypedX3DFieldDefinition<SFFloat>* Sound::get_minFrontFieldDef()
{
	static TypedX3DFieldDefinition<SFFloat> minFront("minFront", SAIFieldAccess_inputOutput, offsetof(Sound, m_minFront));
	return &minFront;
}

NodeType* Sound::GetNodeType()
{
	static X3DFieldDefinition source("source", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Sound, m_source));

	static X3DFieldDefinition* SoundFields[] =
	{
		get_locationFieldDef(),
		get_directionFieldDef(),
		get_intensityFieldDef(),
		&source,
		get_maxBackFieldDef(),
		get_maxFrontFieldDef(),
		get_minBackFieldDef(),
		get_minFrontFieldDef(),
		/*
		SFVec3f [in,out] direction  0 0 1 (-8,8)
		SFFloat [in,out] intensity  1     [0,1]
		SFVec3f [in,out] location   0 0 0 (-8,8)
		SFFloat [in,out] maxBack    10    [0,8)
		SFFloat [in,out] maxFront   10    [0,8)
		SFNode  [in,out] metadata   NULL  [X3DMetadataObject]
		SFFloat [in,out] minBack    1     [0,8)
		SFFloat [in,out] minFront   1     [0,8)
		SFFloat [in,out] priority   0     [0,1]
		SFNode  [in,out] source     NULL  [X3DSoundSourceNode]
		SFBool  []       spatialize TRUE
		*/
	};

	static NodeType nodeType(WSTR("Sound"), typeid(Sound), SoundFields, _countof(SoundFields), X3DSoundNode::GetNodeType());
	return &nodeType;
}

Sound::Sound() : X3DSoundNode(GetNodeType()),

	m_direction(new SFVec3f(get_directionFieldDef(), this, Vec3f(0.0f, 0.0f, 1.0f))),
	m_intensity(new SFFloat(get_intensityFieldDef(), this, 1.0f)),
	m_maxBack(new SFFloat(get_maxBackFieldDef(), this, 10)),
	m_maxFront(new SFFloat(get_maxFrontFieldDef(), this, 10)),
	m_minBack(new SFFloat(get_minBackFieldDef(), this, 1)),
	m_minFront(new SFFloat(get_minFrontFieldDef(), this, 1)),

	m_bPlaying(false)
{
}

Sound::~Sound()
{
	if (m_reverbEffect)
		m_reverbEffect->Release();
}

void Sound::SoundSourceUrlChanged()
{
	if (m_sourceVoice)
	{
		m_sourceVoice->Stop();
	}

	Play();
}

void Sound::DoTime(double gt)
{
//	ASSERT(0);
#if 0
	if (m_source->m_value)
	{
		// Add us the audioclips list of sounds
		for (int i = 0; i < static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.GetSize(); i++)
		{
			if (static_cast<CLAudioClip*>(m_source->m_value)->m_sounds[i] == this)
				break;
		}

		if (i == static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.GetSize())
		{
			static_cast<CLAudioClip*>(m_source->m_value)->Add(this);
		}

		if (!bRunning)
		{
		//	m_hThread = CreateThread(NULL, NULL, AudioRunProc, (LPVOID)(COutputPin*)this, 0, &m_threadId);

			bRunning = TRUE;
			static_cast<CLAudioClip*>(m_source->m_value)->m_pAudioFilter->m_pFilterGraph->Stop();
			static_cast<CLAudioClip*>(m_source->m_value)->m_pAudioFilter->m_pFilterGraph->Run();	// Loop ???
		}
	}



	/*
/if (m_source->m_value)
	{
		static_cast<CLAudioClip*>(m_source->m_value)->Init()
		m_source
	}
	*/
#endif
}

D3DXVECTOR3 transform(const D3DXMATRIX& matrix, Vec3f vec)
{
	D3DXVECTOR4 v;
	D3DXVec3Transform(&v, (D3DXVECTOR3*)&vec, &matrix);
	return *(D3DXVECTOR3*)&v;
}

void Sound::Draw(X3DDrawContext* pDC)
{
	if (!m_bPlaying)
	{
		m_bPlaying = true;
		Play();
	}

	XAUDIO2_DEVICE_DETAILS& deviceDetails = Gui::deviceDetails;

	int destChannels = 1;
	destChannels = deviceDetails.OutputFormat.Format.nChannels;

	AudioClip* source = dynamic_cast<AudioClip*>(m_currentSource);

	X3DAUDIO_EMITTER emitter = {0};
	emitter.ChannelCount = 1;//source->m_wfx.nChannels;
	emitter.CurveDistanceScaler = 10;//FLT_MIN;
	emitter.DopplerScaler = 1;

	X3DAUDIO_DSP_SETTINGS dspSettings = {0};
	FLOAT32* matrix = new FLOAT32[destChannels * 1];
	dspSettings.SrcChannelCount = source->m_wave->get_Format().nChannels;
	dspSettings.DstChannelCount = destChannels;
	dspSettings.pMatrixCoefficients = matrix;

	D3DXVECTOR3 emitterPosition = transform(pDC->m_renderContext->modelViewMatrix(), getLocation());
	D3DXVECTOR3 emitterVelocity(0, 0, 0);
	D3DXVECTOR3 emitterOrientTop(0, 1, 0);
	D3DXVECTOR3 emitterOrientFront(1, 0, 0);

	emitter.OrientFront = emitterOrientFront;
	emitter.OrientTop = emitterOrientTop;
	emitter.Position = emitterPosition;
	emitter.Velocity = emitterVelocity;
//	emitter.InnerRadius = 2.0f;
//	emitter.InnerRadiusAngle = X3DAUDIO_PI/4.0f;
	emitter.ChannelRadius = 1.0;

	X3DAudioCalculate(Gui::X3DInstance, &pDC->m_listener, &emitter,
		X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_REVERB,
		&dspSettings);

	m_sourceVoice->SetOutputMatrix(Gui::pMasteringVoice, source->m_wave->get_Format().nChannels, destChannels, dspSettings.pMatrixCoefficients);
	m_sourceVoice->SetFrequencyRatio(dspSettings.DopplerFactor);

	m_sourceVoice->SetOutputMatrix(m_submixVoice, 1, 1, &dspSettings.ReverbLevel);

    XAUDIO2_FILTER_PARAMETERS FilterParametersDirect = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI/6.0f * dspSettings.LPFDirectCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
	m_sourceVoice->SetOutputFilterParameters(Gui::pMasteringVoice, &FilterParametersDirect);

	XAUDIO2_FILTER_PARAMETERS FilterParametersReverb = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI/6.0f * dspSettings.LPFReverbCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
    m_sourceVoice->SetOutputFilterParameters(m_submixVoice, &FilterParametersReverb);

//	XAUDIO2_FILTER_PARAMETERS FilterParameters = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI/6.0f * DSPSettings.LPFDirectCoefficient), 1.0f };
//	m_sourceVoice->SetFilterParameters(&FilterParameters);

#if 0
	if (m_source->m_value)
	{
		// Add us the audioclips list of sounds
		for (int i = 0; i < static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.GetSize(); i++)
		{
			if (static_cast<CLAudioClip*>(m_source->m_value)->m_sounds[i] == this)
				break;
		}

		if (i == static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.GetSize())
		{
			static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.Add(this);
		}
	}
#endif
}

void Sound::Play()
{
	ASSERT(m_currentSource);

	XAUDIO2_DEVICE_DETAILS& deviceDetails = Gui::deviceDetails;

	AudioClip* source = dynamic_cast<AudioClip*>(m_currentSource);

	if (m_sourceVoice == nullptr)
	{
	   //
		// Create reverb effect
		//
		UINT32 flags = 0;
	#ifdef _DEBUG
		flags |= XAUDIO2FX_DEBUG;
	#endif

		XAudio2CreateReverb(&m_reverbEffect, flags);

	   // Performance tip: you need not run global FX with the sample number
		// of channels as the final mix.  For example, this sample runs
		// the reverb in mono mode, thus reducing CPU overhead.
		XAUDIO2_EFFECT_DESCRIPTOR effects[] =
		{
			{ m_reverbEffect, TRUE, 1 }
		};
		XAUDIO2_EFFECT_CHAIN effectChain = { _countof(effects), effects };

		Gui::pXAudio2->CreateSubmixVoice(&m_submixVoice,
			1,	// Input channels
			deviceDetails.OutputFormat.Format.nSamplesPerSec,	// Input sample rate
			0,	// Flags
			0,	// ProcessingStage
			nullptr,		// SendList
			&effectChain);

		XAUDIO2FX_REVERB_I3DL2_PARAMETERS g_PRESET_PARAMS[1] =
		{
			XAUDIO2FX_I3DL2_PRESET_FOREST
		};

		// Set default FX params
		XAUDIO2FX_REVERB_PARAMETERS native;
		ReverbConvertI3DL2ToNative(&g_PRESET_PARAMS[0], &native);
		m_submixVoice->SetEffectParameters(0, &native, sizeof(native));

			//
		// Play the wave using a source voice that sends to both the submix and mastering voices
		//
		XAUDIO2_SEND_DESCRIPTOR sendDescriptors[2];
		sendDescriptors[0].Flags = XAUDIO2_SEND_USEFILTER; // LPF direct-path
		sendDescriptors[0].pOutputVoice = Gui::pMasteringVoice;
		sendDescriptors[1].Flags = XAUDIO2_SEND_USEFILTER; // LPF reverb-path -- omit for better performance at the cost of less realistic occlusion
		sendDescriptors[1].pOutputVoice = m_submixVoice;
		const XAUDIO2_VOICE_SENDS sendList = { _countof(sendDescriptors), sendDescriptors };

		Gui::pXAudio2->CreateSourceVoice(&m_sourceVoice, &source->m_wave->get_Format(),
								 XAUDIO2_VOICE_USEFILTER, XAUDIO2_DEFAULT_FREQ_RATIO, nullptr, &sendList, nullptr);

#if 0
		XAUDIO2_SEND_DESCRIPTOR SFXSend[] =
		{
			{0/*XAUDIO2_SEND_USEFILTER*/, m_scene->m_submixVoice},
			{0/*XAUDIO2_SEND_USEFILTER*/, Gui::pMasteringVoice},
		};

		XAUDIO2_VOICE_SENDS SFXSendList = {_countof(SFXSend), SFXSend};
		Gui::pXAudio2->CreateSourceVoice(&m_sourceVoice, (WAVEFORMATEX*)&source->m_wfx,
									 XAUDIO2_VOICE_USEFILTER, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, &SFXSendList, NULL);
#endif
	}

	ASSERT(source->m_wave->m_audioBytes <= XAUDIO2_MAX_BUFFER_BYTES);

	XAUDIO2_BUFFER buffer;
	buffer.AudioBytes = source->m_wave->m_audioBytes;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopBegin = 0;
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopLength = 0;
	buffer.pAudioData = source->m_wave->m_audioData;
	buffer.pContext = nullptr;
	buffer.PlayBegin = 0;
	buffer.PlayLength = 0;

	float volume = getIntensity();	// TODO ??
	m_sourceVoice->SetVolume(volume);

	m_sourceVoice->SubmitSourceBuffer(&buffer);
	m_sourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
}

void Sound::OnFieldChanged(X3DField* field)
{
	if (field == m_intensity)
	{
		if (m_sourceVoice)
		{
			float volume = getIntensity();	// TODO ??
			m_sourceVoice->SetVolume(volume);
		}
	}

	baseClass::OnFieldChanged(field);
}

void Sound::DrawOverlay(X3DDrawContext* pDC)
{
	// TODO: not here
	if (m_selected)
	{
		pDC->m_renderContext->PushModelView(pDC->m_renderContext->modelViewMatrix() * MatrixTranslation(getLocation()));

		DrawAxis(pDC);

		pDC->m_renderContext->PopMatrix();
	//	pDC->m_renderContext->GetRT()->m_d3d10->m_device->OMSetDepthStencilState(depthStencilState, stencilRef);
	}
}

int Sound::HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest)
{
	D3DXVECTOR3 location(m_location->getValue());
//	D3DXVECTOR4 v;

//	D3DXVec3Transform(&v, &location, &modelView);

	D3DXVECTOR3 out;
	D3DXVec3Project(&out, &location, &vp, &projection, &view, &model);

	if (fabs(mousepos[0]-out.x) < 3 &&
		fabs(mousepos[1]-out.y) < 3)
	{
		hitTest->OnHit(this, type, *(Vec3f*)&out);
		return 1;
	}

	return 0;
}

/////////////////////////////////

X3DSoundSourceNode* X3DSoundNode::getSource()
{
	return m_source->getValue();
}

void X3DSoundNode::setSource(X3DSoundSourceNode* source)
{
	m_source->setValue(source);
}

void X3DSoundNode::OnFieldChanged(X3DField* field)
{
	if (field == m_source)
	{
		if (m_currentSource)
		{
			m_currentSource->RemoveSoundNode(this);
		}

		m_currentSource = m_source->getValue();
		m_currentSource->AddSoundNode(this);
	}

	baseClass::OnFieldChanged(field);
}

}	// x3d
}	// System
