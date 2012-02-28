#include "stdafx.h"
#include "X3D2.h"
#include "AudioClip.h"

// TODO remove
#include "LVOC/VOCLoader.h"
#pragma comment(lib, "LVOC.lib")

namespace System
{
namespace x3d
{

IMP_X3DFIELD0(AudioClip, MFString, url, inputOutput)
IMP_X3DFIELD0(AudioClip, SFFloat, duration_changed, outputOnly)

NodeType* AudioClip::GetNodeType()
{
//	static X3DFieldDefinition url(WSTR("url"), FieldType_MFString, SAIFieldAccess_inputOutput, offsetof(AudioClip, m_url));
//	static X3DFieldDefinition duration_changed(WSTR("duration_changed"), FieldType_SFFloat, SAIFieldAccess_outputOnly, offsetof(AudioClip, m_duration_changed));

	static X3DFieldDefinition* AudioClipFields[] =
	{
		get_urlFieldDef(),
		get_duration_changedFieldDef(),
		/*
		SFString [in,out] description      ""
		SFBool   [in,out] loop             FALSE
		SFNode   [in,out] metadata         NULL  [X3DMetadataObject]
		SFTime   [in,out] pauseTime        0     (-8,8)
		SFFloat  [in,out] pitch            1.0   (0,8)
		SFTime   [in,out] resumeTime       0     (-8,8)
		SFTime   [in,out] startTime        0     (-8,8)
		SFTime   [in,out] stopTime         0     (-8,8)
		MFString [in,out] url              []    [urn]
		SFTime   [out]    duration_changed
		SFTime   [out]    elapsedTime
		SFBool   [out]    isActive
		SFBool   [out]    isPaused
	  */
	};

	static NodeType nodeType("AudioClip", typeid(AudioClip), AudioClipFields, _countof(AudioClipFields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* AudioClip::nodeType(GetNodeType());

AudioClip::AudioClip() : X3DSoundSourceNode(GetNodeType())
{
}

void AudioClip::AddSoundNode(X3DSoundNode* pSound)
{
	m_sounds.Add(pSound);

	LoadFile();
}

bool AudioClip::LoadFile()
{
	size_t count = m_url->get_size();
	for (size_t i = 0; i < count; ++i)
	{
		if (LoadFile(m_url->get1Value(i)))
			return true;
	}

	return false;
}

void AudioClip::RemoveSoundNode(X3DSoundNode* pSound)
{
	m_sounds.erase(m_sounds.find(pSound));
}

void AudioClip::OnFieldChanged(X3DField* field)
{
	if (field == m_pitch)
	{
		for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it)
		{
		//	(*it)->AudioClipPitchChanged();
		}
	}
	else if (field == m_url)
	{
		if (m_wave)
		{
		//	delete m_audioData;
		}

		m_triedLoad = false;
		LoadFile();

		for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it)
		{
			(*it)->SoundSourceUrlChanged();
		}
	}
	else
	{
		baseClass::OnFieldChanged(field);
	}
}

void AudioClip::setUrl(StringIn url)
{
	m_url->clear();
	m_url->append1Value(url);
}

bool AudioClip::LoadFile(StringIn url)
{
	if (m_triedLoad)
	{
		return false;
	}

	m_triedLoad = true;

	/*
	UrlBinding binding;
	Stream stream = binding.BindToObject(url, NULL);
	if (stream == null)
	{
		return false;
	}

	MediaShow::VOCLoader loader;
	loader.Open(stream);

	loader.ReadFormatSignature();
	loader.ReadHeader();

	m_audioBytes = loader.m_nSamples * loader.m_wfx.nBlockAlign;

	m_wfx = loader.m_wfx;
	m_wfx.cbSize = sizeof(WAVEFORMATEX);

	m_audioData = new byte[m_audioBytes];
	loader.ReadSamples(m_audioData, loader.m_nSamples);
	*/
	m_wave = Gui::WaveformData::FromFile(url);

	m_duration_changed->setValue((double)m_wave->m_nsamples / m_wave->get_Format().nSamplesPerSec);

	return 0;
}

}	// x3d
}	// System
