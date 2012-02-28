#include "stdafx.h"
#include "Browser.h"
#include "../LFC/RIFF.h"
#include "../LXUI/UndoManager.h"

#include "MusicModule.h"

#if WIN32
#include "HGlobalStream.h"
#endif	// WIN32

#include "../LVOC/VOCLoader.h"
#pragma comment(lib, "../../lib/Win32/Debug/LVOC.lib")

//extern DECLSPEC_DLLIMPORT long g_locked;
//extern DECLSPEC_DLLIMPORT long g_locked2;

#define nTotalSamples	(44100*2)*12

namespace System
{
using namespace IO;
using namespace UI;

inline double Frac(double v)
{
	return v - ((int)v);
}

inline signed char getsbyte(ISequentialByteStream* stream)
{
	signed char v;
	ULONG nRead = stream->Read(&v, 1);
	if (nRead != 1) THROW(-1);
	return v;
}

inline uint8 getbyte(ISequentialByteStream* stream)
{
	uint8 v;
	ULONG nRead = stream->Read(&v, 1);
	if (nRead != 1) THROW(-1);
	return v;
}

inline uint8 getubyte(ISequentialByteStream* stream)
{
	uint8 v;
	ULONG nRead = stream->Read(&v, 1);
	if (nRead != 1) THROW(-1);
	return v;
}

inline short getshort(ISequentialByteStream* stream)
{
	short v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return BigEndian16(v);
}

inline uint16 getushort(ISequentialByteStream* stream)
{
	uint16 v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return BigEndian16(v);
}

inline long getlong(ISequentialByteStream* stream)
{
	long v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return BigEndian32(v);
}

inline uint32 getulong(ISequentialByteStream* stream)
{
	uint32 v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return BigEndian32(v);
}

inline LONGLONG getlonglong(ISequentialByteStream* stream)
{
	return ((LONGLONG)getlong(stream)<<32) | getlong(stream);
}

inline short le_getshort(ISequentialByteStream* stream)
{
	short v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return LittleEndian16(v);
}

inline uint16 le_getushort(ISequentialByteStream* stream)
{
	uint16 v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return LittleEndian16(v);
}

inline long le_getlong(ISequentialByteStream* stream)
{
	long v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return LittleEndian32(v);
}

inline uint32 le_getulong(ISequentialByteStream* stream)
{
	uint32 v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return LittleEndian32(v);
}

inline void skip(ISequentialByteStream* stream, ULONG nbytes)
{
	stream->Seek(nbytes, System::IO::STREAM_SEEK_CUR);
}

/*
Octave 0:1712,1616,1525,1440,1357,1281,1209,1141,1077,1017, 961, 907
Octave 1: 856, 808, 762, 720, 678, 640, 604, 570, 538, 508, 480, 453
Octave 2: 428, 404, 381, 360, 339, 320, 302, 285, 269, 254, 240, 226
Octave 3: 214, 202, 190, 180, 170, 160, 151, 143, 135, 127, 120, 113
Octave 4: 107, 101,  95,  90,  85,  80,  76,  71,  67,  64,  60,  57
*/

char* OctaveNotes[12] =
{
	"C",
	"C#",
	"D",
	"D#",
	"E",
	"F",
	"F#",
	"G",
	"G#",
	"A",
	"A#",
	"B",
};

ErrorCode ReadWAVE(ISequentialByteStream* stream, Riff::CChunk& parent, Wave* *ppWave)
{
	ULONG nRead;

	*ppWave = NULL;
	Wave* pWave = new Wave;

	while (stream->Seek(0, System::IO::STREAM_SEEK_CUR) < parent.m_pos+parent.m_size)
	{
		Riff::CChunk ck;
		if (ck.Descend(stream) != Success)
			break;

		if (ck.m_id == mmioFOURCC('f','m','t',' '))
		{
			if (ck.m_size < sizeof(MSWindows::PCMWAVEFORMAT))
			{
				TRACE("fmt chunk is too small");
				return Error;
			}

			MSWindows::WAVEFORMATEX wfx;
			stream->Read(&wfx, sizeof(wfx));

			pWave->m_wfx = new MSWindows::WAVEFORMATEX;
			*pWave->m_wfx = wfx;

			/*
			m_fmtsize = ck.m_size;
			m_fmtbuffer = malloc(m_fmtsize);
			if (m_fmtbuffer == NULL)
			{
				return E_OUTOFMEMORY;
			}

			m_stream->Read(m_fmtbuffer, m_fmtsize, &nRead);
			*/
		}
		else if (ck.m_id == mmioFOURCC('d','a','t','a'))
		{
			pWave->m_data = new uint8[ck.m_size];
			stream->Read(pWave->m_data, ck.m_size);
			pWave->m_nsamples = ck.m_size / pWave->m_wfx->nBlockAlign;
		}

		ck.Ascend(stream);
	}

	*ppWave = pWave;

	return Success;
}

MusicModule::MusicModule()
{
	for (uint ch = 0; ch < 32; ch++)
	{
		m_channelEnabled[ch] = true;
	}
}

MusicModuleReader::MusicModuleReader()
{
	m_pModule = NULL;
}

MusicModuleReader::MusicModuleReader(StringA* filename)
{
	Load(filename);
}

MusicModuleReader::MusicModuleReader(StringW* filename)
{
	Load(filename);
}

MusicModuleReader::MusicModuleReader(IO::ISequentialByteStream* stream)
{
	Load(stream);
}

void MusicModuleReader::Load(StringA* filename)
{
	FileByteStream stream(filename);
	Load(&stream);
	stream.Close();
}

void MusicModuleReader::Load(StringW* filename)
{
	FileByteStream stream(filename);
	Load(&stream);
	stream.Close();
}

uint8 MusicModuleReader::GETBYTE(IO::ISequentialByteStream* stream)
{
	if (nstacked)
	{
		nstacked = 0;
		return stackedbyte;
	}
	return getubyte(stream);
}

void MusicModuleReader::Load(ISequentialByteStream* stream)
{

	//m_pMusicModule->ReadMIDI(stream);

	for (int n = 0; n < 4; n++)
	{
		int ret;

		switch (n)
		{
		case 0:
			ret = ReadImpulseTracker(stream);
			break;

		case 1:
			ret = ReadXM(stream);
			break;

		case 2:
			ret = Read669(stream);
			break;

		case 3:
			ret = ReadMOD(stream);
			break;
		}

		if (ret >= 0)
			break;

		stream->Seek(0, System::IO::STREAM_SEEK_SET);
	}
}

int MusicModuleReader::ReadMIDI(ISequentialByteStream* stream)
{
	ULONG sig;
	sig = getulong(stream);
	if (sig != 0x4D546864)
		return -1;

	sig = getulong(stream);
	if (sig != 0x00000006)
		return -1;

	uint16 format = getushort(stream);
	uint16 ntracks = getushort(stream);
	uint16 ticksPerQNote = getushort(stream);

	Pattern* pPattern = new Pattern;
	pPattern->rows = 0;
	pPattern->notes = new Note*[16];
	for (int i = 0; i < 16; i++)
	{
		pPattern->notes[i] = new Note[8000];
	}

	m_pModule->m_songlength = 1;
	m_pModule->m_patternOrder[0] = 0;
	m_pModule->m_patterns.push_back(pPattern);

	while (1)
	{
		nstacked = 0;
		TRY
		{
			ULONG ID = getulong(stream);
			ULONG size = getulong(stream);
			ULONG start = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
			if (ID == 0x4D54726B)
			{
				uint8 prevcommand = 0;

				while (stream->Seek(0, System::IO::STREAM_SEEK_CUR) < start + size)
				{
					// Read delta time
					uint8 bytevalue;
					bytevalue = getubyte(stream);
					ULONG deltaTime = bytevalue & ~0x80;
					while (bytevalue & 0x80)
					{
						deltaTime <<= 7;
						bytevalue = getubyte(stream);
						deltaTime |= bytevalue & ~0x80;
					}

					uint8 command = getubyte(stream);
					if (!(command & 0x80))
					{
						stackedbyte = command;
						nstacked = 1;
						command = prevcommand;
					}
					ASSERT(command & 0x80);

					prevcommand = command;

					if (command == 0xff)
					{
						command = GETBYTE(stream);
						uint8 n = GETBYTE(stream);
						stream->Seek(n, System::IO::STREAM_SEEK_CUR);

						TRACE("0xff %x\n", command);
					}
					else
					{
						uint8 channel = command & 0x0F;
						switch (command & 0xF0)
						{
						case 0x80:
							{
								uint8 nn = GETBYTE(stream);
								uint8 vv = GETBYTE(stream);
								TRACE("0x80\n");
							}
							break;

						case 0x90:
							{
								uint8 nn = GETBYTE(stream);
								uint8 vv = GETBYTE(stream);

								TRACE("NOTE ON channel: %d, note: %d, velocity: %d\n", channel, nn, vv);
							}
							break;

						case 0xA0:
							{
								uint8 nn = GETBYTE(stream);
								uint8 vv = GETBYTE(stream);
								TRACE("0xA0\n");
							}
							break;

						case 0xB0:
							{
								uint8 cc = GETBYTE(stream);
								uint8 vv = GETBYTE(stream);
								TRACE("0xB0\n");
							}
							break;

						case 0xC0:
							{
								// Program (patch) change    pp=new program number
								uint8 pp = GETBYTE(stream);
								TRACE("0xC0\n");
							}
							break;

						case 0xD0:
							{
								uint8 cc = GETBYTE(stream);
								TRACE("0xD0\n");
							}
							break;

						case 0xE0:
							{
								uint8 bb = GETBYTE(stream);
								uint8 tt = GETBYTE(stream);
								TRACE("0xE0\n");
							}
							break;

						case 0xF0:	// Manufacturer's ID
							{
								TRACE("0xF0\n");
								if (command == 242)
								{
									getubyte(stream);
									getubyte(stream);
								}
								else if (command == 243)
								{
									getubyte(stream);
								}
							}
							break;

						default:
							ASSERT(0);
						}
					}
				}
			//	stream->Seek(size, System::IO::STREAM_SEEK_CUR);
			}
		}
		CATCH(int)
		{
			break;
		}
		break;
	}
	return 0;
}

int MusicModuleReader::ReadXM(ISequentialByteStream* stream)
{
	char ID[17];
	if (stream->Read(ID, 17) != 17)
		return -1;
	if (std::memcmp(ID, "Extended Module: ", 17))
		return -1;

	m_pModule = new MusicModule;

	stream->Read(m_pModule->m_name, 20);
	m_pModule->m_name[20] = 0;
	char b = getbyte(stream);
	if (b != 0x1a)
		return -1;

	char TrackerName[20];
	stream->Read(TrackerName, 20);

	uint16 version = le_getushort(stream);

	ULONG headersize = le_getulong(stream);

	m_pModule->m_songlength = le_getushort(stream);
	if (m_pModule->m_songlength > 256)
	{
		TRACE("warning: songlength field larger than 256\n");
		m_pModule->m_songlength = 256;
	}
	m_pModule->m_restartPosition = le_getushort(stream);
	m_pModule->m_nchannels = le_getushort(stream);
	if (m_pModule->m_nchannels > 32)
	{
		TRACE("error: channels field larger than 32\n");
		return -1;
	}
	uint16 npatterns = le_getushort(stream);
	if (npatterns > 256)
	{
		TRACE("warning: patterns exceed 256\n");
	}
	uint16 ninstruments = le_getushort(stream);
	if (ninstruments > 128)
	{
		TRACE("warning: instruments exceed 128\n");
	}
	uint16 flags = le_getushort(stream);
	if ((flags & 1) == 0)	// amiga frequence table
		m_pModule->m_linearFreq = false;
	else	// linear frequency
		m_pModule->m_linearFreq = true;

	m_pModule->m_linearFreq = true;

	m_pModule->m_defaultTempo = le_getushort(stream);
	m_pModule->m_defaultBPM = le_getushort(stream);	// Beats Per Minute

	int i;
	for (i = 0; i < 256; i++)
	{
		m_pModule->m_patternOrder[i] = getubyte(stream);
	}

	for (i = 0; i < npatterns; i++)
	{
		Pattern* pPattern = new Pattern;
		pPattern->notes = new Note*[m_pModule->m_nchannels];

		ULONG headerlength = le_getulong(stream);
	//	ULONG headerlength = getulong(stream);
		//getushort(stream);
		uint8 packingtype = getubyte(stream);
		if (packingtype != 0)
			return -1;

		uint16 rows = le_getushort(stream);
		uint16 packedsize = le_getushort(stream);
		LONG start = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
	//	skip(stream, 1);	// ??

		/*
		if (rows != 64)
		{
			MessageBeep(-1);
		}
		*/

		pPattern->rows = rows;

		m_pModule->m_patterns.push_back(pPattern);

		for (int ch = 0; ch < m_pModule->m_nchannels; ch++)
		{
			pPattern->notes[ch] = new Note[rows];
		}

		for (int row = 0; row < rows; row++)
		{
			for (int ch = 0; ch < m_pModule->m_nchannels; ch++)
			{
				Note& note = pPattern->notes[ch][row];

				uint8 val = getubyte(stream);
				if (val & 128)	// high bit set
				{
					if (val & 1)
					{
						note.note = getubyte(stream);
					//	note.period = 10*12*16*4 - note.note*16*4/* - FineTune/2*/;
					//	long Frequency = 8363*pow(2, ((6*12*16*4 - note.period) / (12*16*4)));
						//ASSERT(note.note <= 96);
					}
					else
						note.note = 0;

					if (val & 2)
					{
						note.instrument = getubyte(stream);
					}
					else
						note.instrument = 0;

					if (val & 4)
					{
						note.volume = getubyte(stream);
					}

					if (val & 8)	// effect type
					{
						note.effect = getubyte(stream);
					}

					if (val & 16)	// effect parameter
					{
						note.effectparms = getubyte(stream);
					}
				}
				else
				{
					note.note = val;

					note.instrument = getubyte(stream);
					note.volume = getubyte(stream);
					note.effect = getubyte(stream);
					note.effectparms = getubyte(stream);
				}

				if (note.note > 97)
				{
					TRACE("warning: note value exceeds 97\n");
					note.note = 97;
				}

				if (note.note == 97)	// key off
				{
					note.note = 255;	// internal value
				}
			}
		}

		LONG cur = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur - start > packedsize)
		{
			TRACE("Error: pattern packedSize too short\n");
		//	return -1;
		}
		stream->Seek(start + packedsize, System::IO::STREAM_SEEK_SET);
	}

	for (i = 0; i < ninstruments; i++)
	{
		LONG start = stream->Seek(0, System::IO::STREAM_SEEK_CUR);

		ULONG instrument_size = le_getulong(stream);
		Instrument* pInstr = new Instrument;
		stream->Read(pInstr->name, 22);
		pInstr->name[22] = 0;

		uint8 type = getbyte(stream);
		uint16 nsamples = le_getushort(stream);

		if (nsamples > 0)
		{
			ULONG sampleheadersize = le_getulong(stream);
			if (sampleheadersize != 40)
			{
				TRACE("TODO\n");
			}

			uint8 noteSample[96];
			stream->Read(noteSample, 96);	// sample numbers for all notes
			skip(stream, 48);
			skip(stream, 48);
			skip(stream, 16);
		//	skip(stream, 22);	// reserved

			LONG cur = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
		//	ASSERT(cur-start == instrument_size);
			stream->Seek(start + instrument_size, System::IO::STREAM_SEEK_SET);

			vector<InstrumentSample*> samples;

			{
				for (int j = 0; j < nsamples; j++)
				{
					InstrumentSample* pSample = new InstrumentSample;

					pSample->sampleLength = le_getulong(stream);
					pSample->repeatPoint = le_getulong(stream);
					pSample->repeatLength = le_getulong(stream);
					pSample->volume = getubyte(stream);
					pSample->finetune = getsbyte(stream);
					uint8 type = getubyte(stream);
					if (type & 4)
						pSample->bitsPerSample = 16;
					else
						pSample->bitsPerSample = 8;

					getubyte(stream);	// panning
					pSample->relativenote = getsbyte(stream);	// relative note number
					//ASSERT(relativenote == 0);
					getubyte(stream);	// reserved
					stream->Read(pSample->name, 22);
					pSample->name[22] = 0;

					pInstr->samples.push_back(pSample);
					samples.push_back(pSample);
				}
			}

			{
				for (int j = 0; j < 96; j++)
				{
					pInstr->noteSample[j] = pInstr->samples[noteSample[j]];
				}
			}

			{
				for (int j = 0; j < nsamples; j++)
				{
					if (samples[j]->sampleLength)
					{
						samples[j]->data = new uint8[samples[j]->sampleLength+1];
						char* p = (char*)samples[j]->data;
						stream->Read(p, samples[j]->sampleLength);
						p[samples[j]->sampleLength] = 0;

						char old = 0;

						for (int s = 0; s < samples[j]->sampleLength; s++)
						{
							char value = p[s]+old;
							p[s] = value;
							old = value;
						}
					}
				}
			}
		}
		else
		{
		//	ULONG sampleheadersize = le_getulong(stream);	// ??
		// LONG cur = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
		//	ASSERT(cur-start == instrument_size);	//

			stream->Seek(start + instrument_size, System::IO::STREAM_SEEK_SET);
		}

		m_pModule->m_instruments.push_back(pInstr);
	}

	return 0;
}

int MusicModuleReader::ReadImpulseTracker(ISequentialByteStream* stream)
{
	ULONG sig = getulong(stream);
	if (sig != 'IMPM')
		return -1;

	m_pModule = new MusicModule;

	char name[26];
	stream->Read(name, 26);

	m_pModule->m_linearFreq = 1;

	uint16 philight = getushort(stream);

	uint16 OrdNum = le_getushort(stream);
	uint16 InsNum = le_getushort(stream);
	uint16 SmpNum = le_getushort(stream);
	uint16 PatNum = le_getushort(stream);
	uint16 Cwtv = le_getushort(stream);
	uint16 Cmwt = le_getushort(stream);
	uint16 Flags = le_getushort(stream);
	uint16 Special = le_getushort(stream);

	if (PatNum > 256)
	{
		TRACE("warning: Number of patterns exceeded 256\n");
		PatNum = 256;
	}

	uint8 GV = getubyte(stream);
	uint8 MV = getubyte(stream);
	uint8 IS = getubyte(stream);
	uint8 IT = getubyte(stream);
	uint8 Sep = getubyte(stream);
	uint8 PWD = getubyte(stream);
	uint16 MsgLgth = le_getushort(stream);
	uint16 MessageOffset = le_getushort(stream);
	skip(stream, 6); // Reserved

	m_pModule->m_defaultTempo = IS;
	m_pModule->m_defaultBPM = IT;

	int i;

	uint8 channelPan[64];
	for (i = 0; i < 64; i++)
	{
		channelPan[i] = getubyte(stream);
	}

	uint8 channelVolume[64];
	for (i = 0; i < 64; i++)
	{
		channelVolume[i] = getubyte(stream);
	}

	for (i = 0; i < OrdNum; i++)
	{
		m_pModule->m_patternOrder[i] = getubyte(stream);
	}

	m_pModule->m_songlength = OrdNum;

	long* InsOffset = new long[InsNum];
	for (i = 0; i < InsNum; i++)
	{
		InsOffset[i] = le_getulong(stream);
	}

	long* SmpOffset = new long[SmpNum];
	for (i = 0; i < SmpNum; i++)
	{
		SmpOffset[i] = le_getulong(stream);
	}

	long* PatOffset = new long[PatNum];
	for (i = 0; i < PatNum; i++)
	{
		PatOffset[i] = le_getulong(stream);
	}

	vector<InstrumentSample*> m_samples;

	for (i = 0; i < SmpNum; i++)
	{
		stream->Seek(SmpOffset[i], System::IO::STREAM_SEEK_SET);
		ULONG sig = getulong(stream);

		if (sig != 'IMPS')
			return -1;

		char dosfilename[12];
		stream->Read(dosfilename, 12);
		if (getubyte(stream) != 0)
		{
			TRACE("warning: expected '\0' after dos filename in sample file\n");
		}

		InstrumentSample* pSample = new InstrumentSample;
		uint8 globalvolume = getubyte(stream);	// global volume
		uint8 flags = getubyte(stream);
		pSample->volume = getubyte(stream);	// defalt volume
		stream->Read(pSample->name, 26);
		uint8 Cvt = getubyte(stream);
		uint8 DfP = getubyte(stream);

		pSample->sampleLength = le_getulong(stream);
		pSample->repeatPoint = le_getulong(stream);
		pSample->repeatLength = le_getulong(stream) - pSample->repeatPoint;
		uint32 C5Speed = le_getulong(stream);
		uint32 SusLBeg = le_getulong(stream);
		uint32 SusLEnd = le_getulong(stream);

		uint32 offset = le_getulong(stream);

		stream->Seek(offset, System::IO::STREAM_SEEK_SET);

		if (flags & 2)
		{
			pSample->bitsPerSample = 16;
			pSample->data = (uint8*)new short[pSample->sampleLength+1];
			((short*)pSample->data)[pSample->sampleLength] = 0;
		}
		else
		{
			pSample->bitsPerSample = 8;
			pSample->data = (uint8*)new signed char[pSample->sampleLength+1];
			((signed char*)pSample->data)[pSample->sampleLength] = 0;
		}

		if (flags & 8)	// compressed
		{
			return -1;
		}
		else
		{
			stream->Read(pSample->data, pSample->sampleLength * pSample->bitsPerSample / 8);
		}

		m_samples.push_back(pSample);
	}

	for (i = 0; i < InsNum; i++)
	{
		stream->Seek(InsOffset[i], System::IO::STREAM_SEEK_SET);
		ULONG sig = getulong(stream);

		if (sig != 'IMPI')
			return -1;

		char dosfilename[12];
		stream->Read(dosfilename, 12);
		if (getubyte(stream) != 0)
		{
			TRACE("warning: expected '\0' after dos filename in instrument file\n");
		}

		Instrument* pInstrument = new Instrument;

		uint8 Flg = getubyte(stream);
		uint8 VLS = getubyte(stream);
		uint8 VLE = getubyte(stream);
		uint8 SLS = getubyte(stream);
		uint8 SLE = getubyte(stream);
		getubyte(stream);
		getubyte(stream);
		uint16 FadeOut = le_getushort(stream);
		uint8 NNA = getubyte(stream);
		uint8 DNC = getubyte(stream);
		uint16 TrkVers = le_getushort(stream);
		uint8 NoS = getubyte(stream);
		getubyte(stream);

		stream->Read(pInstrument->name, 26);

		skip(stream, 6);

	//	long cur = stream->Seek(0, System::IO::STREAM_SEEK_CUR);

		map<InstrumentSample*,bool> samples;

		for (int j = 0; j < 120;  j++)
		{
			uint8 note = getubyte(stream);
			ASSERT(note < 120);
			uint8 sample = getubyte(stream);
			ASSERT(sample < 100);

			if (sample > 0)
			{
				samples[m_samples[sample-1]] = true;

				pInstrument->noteSample[note] = m_samples[sample-1];
			}
		}

		map<InstrumentSample*,bool>::iterator it = samples.begin();
		while (it != samples.end())
		{
			pInstrument->samples.push_back((*it).first);
			++it;
		}

		if (Cmwt < 200)
		{
			ASSERT(0);
			// TODO
		}
		else
		{
			// TODO
		}

		m_pModule->m_instruments.push_back(pInstrument);

	}

	m_pModule->m_nchannels = 64;

	for (i = 0; i < PatNum; i++)
	{
		stream->Seek(PatOffset[i], System::IO::STREAM_SEEK_SET);

		uint16 Length = le_getushort(stream);
		uint16 Rows = le_getushort(stream);
		skip(stream, 4);

		Pattern* pPattern = new Pattern;
		pPattern->rows = Rows;

		pPattern->notes = new Note*[64];

		for (int ch = 0; ch < 64; ch++)
		{
			pPattern->notes[ch] = new Note[Rows];
		}

		uint8 lastnote[64] = {0};
		uint8 lastinstrument[64] = {0};
		uint8 lastmaskvariable[64] = {0};

		for (int row = 0; row < Rows; row++)
		{
			while (1)
			{
				uint8 channelvariable = getubyte(stream);
				if (channelvariable == 0)	// End of row
					break;

				uint8 Channel = (channelvariable-1) & 63;
				uint8 maskvariable;
				if (channelvariable & 128)
				{
					maskvariable = getubyte(stream);
					lastmaskvariable[Channel] = maskvariable;
				}
				else
					maskvariable = lastmaskvariable[Channel];

				Note& note = pPattern->notes[Channel][row];

				if (maskvariable & 1)
				{
					note.note = getubyte(stream);
				}

				if (maskvariable & 2)
				{
					note.instrument = getubyte(stream);
					if (note.instrument > m_pModule->m_instruments.size())
					{
						ASSERT(0);
					}
				}

				if (maskvariable & 4)
				{
					uint8 volpan = getubyte(stream);
				}

				if (maskvariable & 8)
				{
					uint8 command = getubyte(stream);
					uint8 parm = getubyte(stream);
				}

				if (maskvariable & 16)
				{
					note.note = lastnote[Channel];
				}
				else
				{
					lastnote[Channel] = note.note;
				}

				if (maskvariable & 32)
				{
					note.instrument = lastinstrument[Channel];
				}
				else
				{
					lastinstrument[Channel] = note.instrument;
				}
			}
		}

		ULONG cur = stream->Seek(0, System::IO::STREAM_SEEK_CUR);

		ASSERT(cur-PatOffset[i] == Length+8);

		m_pModule->m_patterns.push_back(pPattern);
	}

	return 0;
}

int MusicModuleReader::ReadMOD(ISequentialByteStream* stream)
{
	stream->Seek(1080, System::IO::STREAM_SEEK_SET);
	ULONG signature = getulong(stream);
	int ninstruments;
//		int nchannels;

	if (signature == ('M.K.') || signature == ('M!K!') || signature == ('FLT4') || signature == ('FLT8') || signature == ('4CHN') || signature == ('6CHN') || signature == ('8CHN'))
	{
		m_pModule = new MusicModule;

		ninstruments = 31;

		if (signature == ('8CHN') || signature == ('FLT8'))
			m_pModule->m_nchannels = 8;
		else if (signature == ('6CHN'))
			m_pModule->m_nchannels = 6;
		else
			m_pModule->m_nchannels = 4;
	}
	else
	{
		// TODO, some better recognission of format
		m_pModule = new MusicModule;

		ninstruments = 15;
		m_pModule->m_nchannels = 4;
	}

	m_pModule->m_defaultTempo = 6;
	m_pModule->m_defaultBPM = 125;

	stream->Seek(0, System::IO::STREAM_SEEK_SET);

	stream->Read(m_pModule->m_name, 20);
	m_pModule->m_name[20] = 0;

	for (int i = 0; i < ninstruments; i++)
	{
		Instrument* pInstr = new Instrument;

		stream->Read(pInstr->name, 22);
		pInstr->name[22] = 0;

		InstrumentSample* pSample = new InstrumentSample;

		{
			for (int i = 0; i < 120; i++)
			{
				pInstr->noteSample[i] = pSample;
			}
		}

		pInstr->samples.push_back(pSample);

		ULONG sampleLength = getushort(stream);
		sampleLength <<= 1;

		pSample->sampleLength = sampleLength;

		uint8 value = getubyte(stream);
		uint8 finetune = value & 0xF;
	//	ASSERT(finetune == 0);

		pSample->volume = getubyte(stream);

		if (/*pSample->volume < 0 ||*/ pSample->volume > 64)
		{
			TRACE("Warning: Volume out of range\n");
			//return -1;
			pSample->volume = 64;
		}

		pSample->repeatPoint = getushort(stream);
		pSample->repeatPoint <<= 1;

		if (pSample->repeatPoint > pSample->sampleLength)
		{
			TRACE("Warning: repeatPoint is past sample length\n");
		//	return -1;
			pSample->repeatPoint = pSample->sampleLength;
		}

		pSample->repeatLength = getushort(stream);
		pSample->repeatLength <<= 1;

		m_pModule->m_instruments.push_back(pInstr);
	}

	m_pModule->m_songlength = getubyte(stream);
	getbyte(stream);

	//uint8 pattern[128];

	int npatterns = 0;

	{
		for (int i = 0; i < 128; i++)
		{
			m_pModule->m_patternOrder[i] = getubyte(stream);
			npatterns = MAX(npatterns, m_pModule->m_patternOrder[i]);
		}
	}
	npatterns++;

	if (ninstruments > 15)
	{
		skip(stream, 4);
	}

	// pattern data
	{
		for (int i = 0; i < npatterns; i++)
		{
			Pattern* pPattern = new Pattern;
			pPattern->rows = 64;
			pPattern->notes = new Note*[m_pModule->m_nchannels];

			for (int ch = 0; ch < m_pModule->m_nchannels; ch++)
			{
				pPattern->notes[ch] = new Note[64];
			}

			for (int i = 0; i < 64; i++)
			{
				for (int ch = 0; ch < m_pModule->m_nchannels; ch++)
				{
					uint8 data[4];
					stream->Read(data, 4);

					Note& note = pPattern->notes[ch][i];

					note.instrument = (data[0] & 0xF0) | (data[2]>>4);
					note.period = ((data[0] & 0x0F)<<8) | data[1];
					// TODO, derive note.note from note.period
					if (note.instrument)
						note.note = 1;
					else
						note.note = 0;

					note.effect = data[2] & 0x0F;
					note.effectparms = data[3];
				}
			}

			m_pModule->m_patterns.push_back(pPattern);
		}
	}

	{
		for (int i = 0; i < ninstruments; i++)
		{
			Instrument* pInstr = m_pModule->m_instruments[i];
			if (pInstr->samples[0]->sampleLength)
			{
				// Reserve silent samples past end for linear/cubic interpolation
				pInstr->samples[0]->data = new uint8[pInstr->samples[0]->sampleLength+3];
				pInstr->samples[0]->data[pInstr->samples[0]->sampleLength+0] = 0;
				pInstr->samples[0]->data[pInstr->samples[0]->sampleLength+1] = 0;
				pInstr->samples[0]->data[pInstr->samples[0]->sampleLength+2] = 0;

				stream->Read(pInstr->samples[0]->data, pInstr->samples[0]->sampleLength);
#if 0//WIN32	// signed -> unsigned
				uint8* p = pInstr->data;
				for (int n = 0; n < pInstr->samples[0]->sampleLength; n++)
				{
					*p++ += 128;
				}
#endif
			}
		}
	}

	return 0;
}

int MusicModuleReader::Read669(ISequentialByteStream* stream)
{
	uint16 marker;
	marker = getushort(stream);
	if (marker != 'if' && marker != 'JN')
	{
		return -1;
	}

	m_pModule = new MusicModule;

	char message[108];
	stream->Read(message, 108);

	uint8 nsamples = getubyte(stream);
	uint8 npatterns = getubyte(stream);
	if (npatterns > 128)
	{
		TRACE("Error: npatterns exceeded 128\n");
		return -1;
	}

	getubyte(stream);

	int i;

	for (i = 0; i < 128; i++)
	{
		m_pModule->m_patternOrder[i] = getubyte(stream);
	}

	for (i = 0; i < 128; i++)
	{
		m_pModule->m_patternTempo[i] = getubyte(stream);
	}

	for (i = 0; i < 128; i++)
	{
		m_pModule->m_patternBreak[i] = getubyte(stream);
		if (m_pModule->m_patternBreak[i] > 64)
			return -1;
	}

	for (i = 0; i < nsamples; i++)
	{
		Instrument* pInstr = new Instrument;

		char name[14];
		stream->Read(name, 13);
		name[13] = 0;
		strcpy_s(pInstr->name, name);

		uint32 sampleLength = le_getulong(stream);
		uint32 repeatPoint = le_getulong(stream);
		uint32 repeatLength = le_getulong(stream);

		InstrumentSample* pSample = new InstrumentSample;
		strcpy_s(pSample->name, "(unnamed)");
		pSample->bitsPerSample = 8;
		pSample->sampleLength = sampleLength;
		pSample->repeatPoint = repeatPoint;
		pSample->repeatLength = repeatLength;

		pInstr->samples.push_back(pSample);

		m_pModule->m_instruments.push_back(pInstr);
	}

	m_pModule->m_nchannels = 8;
	m_pModule->m_linearFreq = 1;
	m_pModule->m_defaultTempo = 6;
	m_pModule->m_defaultBPM = 125;

	for (i = 0; i < npatterns; i++)
	{
		Pattern* pPattern = new Pattern;
		pPattern->rows = m_pModule->m_patternBreak[i]+1;
		pPattern->notes = new Note*[8];

		for (int ch = 0; ch < 8; ch++)
		{
			pPattern->notes[ch] = new Note[64];
		}

		m_pModule->m_patterns.push_back(pPattern);

		for (int row = 0; row < 64; row++)
		{
			for (int ch = 0; ch < 8; ch++)
			{
				uint8 data[3];
				stream->Read(data, 3);

				Note& note = pPattern->notes[ch][row];

				if (data[0] == 0xfe)	// no note, only volume change 
				{
					note.note = 0;
				}
				else if (data[0] == 0xff)	// no note or volume change
				{
					note.note = 0;
				}
				else
				{
					note.note = 12+(data[0]>>2)+1;
					note.instrument = ((data[0] & 3)<<4) | (data[1]>>4) + 1;
					ASSERT(note.instrument <= nsamples);
				}
			}
		}
	}

	for (i = 0; i < nsamples; i++)
	{
		InstrumentSample* pSample = *m_pModule->m_instruments[i]->samples.begin();

		pSample->data = new uint8[pSample->sampleLength+1];	// +1 because of bilinear
		stream->Read(pSample->data, pSample->sampleLength);
		pSample->data[pSample->sampleLength] = 0;

		// unsigned -> signed
		char* p = (char*)pSample->data;
		for (int s = 0; s < pSample->sampleLength; s++)
		{
			*p += 128;
			p++;
		}
	}

	return 0;
}

////////////////////////////////////////////
// MusicModuleView

MusicModuleView::MusicModuleView()
{
	m_pCanvas = NULL;
	m_pMusicModule = NULL;

	m_pPatternView = NULL;
	m_pScopeView = NULL;

	m_hEvent1 = NULL;
	m_hEventPop1 = NULL;

	m_hEvent2 = NULL;
	m_hEventPop2 = NULL;

	m_hEvent3 = NULL;
	m_hEventPop3 = NULL;
}

void MusicModuleView::SetModule(MusicModule* pMusicModule)
{
	m_pMusicModule = pMusicModule;
	/*
	m_mixlock.Init();
		m_lock2.Init();
		m_lock3.Init();
		*/

	wo = NULL;

	m_masterSamplesPerSec = 44100;

	m_sampleCounter = 0;
#if 0
	//for (i = 0; i < ninstruments; i++)
	nsamples = m_pMusicModule->m_instruments[0]->sampleLength;
	data = new uint8[m_pMusicModule->m_instruments[0]->sampleLength];
	stream->Read(data, m_pMusicModule->m_instruments[0]->sampleLength);
#if WIN32
	for (i = 0; i < nsamples; i++)
	{
		data[i] += 128;
	}
#endif
	wfx.nBlockAlign = 1;
	wfx.wBitsPerSample = 8;
	wfx.nSamplesPerSec = 8000;
	wfx.nAvgBytesPerSec = 8000;
#endif

	UI::DockPanel* panel = new UI::DockPanel;

	{
		InstrumentsView* pInstrView = new InstrumentsView;
		pInstrView->m_p = this;

		ScrollViewer* pScroller = new ScrollViewer;
		pScroller->set_Content(pInstrView);

		pScroller->set_Height(200);
	//	UI::DockPanel::put_Dock(m_pScroller, UI::DockPanel::Fill);
	//	panel->AddRChild(pScroller);
		DockPanel::SetDock(pScroller, DockPanel::Top);
		panel->get_Children()->Add(pScroller);
	}

	{
		m_pScopeView = new ScopeView;
		m_pScopeView->m_p = this;

		DockPanel::SetDock(m_pScopeView, DockPanel::Top);
		panel->get_Children()->Add(m_pScopeView);
	}

	{
		m_pPatternView = new PatternView;
		m_pPatternView->m_p = this;

		m_pScroller = new ScrollViewer;
		m_pScroller->set_Content(m_pPatternView);

		UI::DockPanel::SetDock(m_pScroller, UI::DockPanel::Fill);
		panel->get_Children()->Add(m_pScroller);
	}

	set_VisualTree(panel);

	//stream->Release();
}

MSWindows::DWORD WINAPI MusicModuleView::ThreadFunc1(void* lpParameter)
{
	((MusicModuleView*)lpParameter)->m_pPatternView->Func1();

	return 0;
}

MSWindows::DWORD WINAPI MusicModuleView::ThreadFunc2(void* lpParameter)
{
	((MusicModuleView*)lpParameter)->m_pScopeView->Func2();

	return 0;
}

// static
MSWindows::DWORD WINAPI MusicModuleView::ThreadFunc3(void* lpParameter)
{
#if 1
	((MusicModuleView*)lpParameter)->Func3();
#else

	__live_object_ptr<MusicModuleView> view = (MusicModuleView*)lpParameter;

	while (1)
	{
		MSWindows::WaitForSingleObject(view->m_hEvent3, INFINITE);

	//	MSWindows::InterlockedIncrement(&g_locked);
	//	while (g_locked2) MSWindows::Sleep(1);

		view->Func3();

	//	MSWindows::InterlockedDecrement(&g_locked);
	}
#endif

	return 0;
}

void MusicModuleView::Func3()
{
#if WIN32

	while (1)
	{
		MSWindows::WaitForSingleObject(m_hEvent3, INFINITE);

		while (!m_pScopeView->m_masterQueue.empty())
		{
#if 0
			uint8* channelCopy[64];
			m_lock3.Lock();
			for (int i = 0; i < m_pMusicModule->m_nchannels; i++)
			{
				channelCopy[i] = m_pScopeView->m_masterCopy[i].front();
				m_pScopeView->m_masterCopy[i].pop();
			}

			/*
			uint8* masterCopy = m_pPatternView->m_masterCopy.front();
			m_pPatternView->m_masterCopy.pop();
			*/
			ULONG masterLength = m_pScopeView->m_masterLength.front();
			m_pScopeView->m_masterLength.pop();

			m_lock3.Unlock();
			SetEvent(m_hEventPop3);

#endif
			m_lock3.Lock();
			DataSample* sample = m_pScopeView->m_masterQueue.front();
			m_pScopeView->m_masterQueue.pop();
			m_lock3.Unlock();
			MSWindows::SetEvent(m_hEventPop3);
			ULONG masterLength = sample->length*4;

			// Mix channels into master data
			m_mixlock.Lock();
			int16* clippedData = new int16[masterLength/4*2];
			m_pScopeView->MixChannels(masterLength/4, 4, (short**)sample->copy/*channelCopy*/, clippedData);

		//	wo->Receive(masterCopy, masterLength);
		//	delete masterCopy;

			{
				ULONG ActualDataLength = masterLength;
				ULONG nbytesSoFar = 0;
				while (nbytesSoFar < ActualDataLength)
				{
					ULONG nbytes;


				// Try to fill the rest of the buffer (either the first or second buffer)
			/*
					if (m_dwOffset < m_dwBufferBytes)	// first buffer
						nbytes = m_dwBufferBytes-m_dwOffset;
					else		// second buffer
						nbytes = m_dwBufferBytes*2-m_dwOffset;
			*/
					ULONG upper = ((wo->m_dwOffset+wo->m_dwBufferBytes) / wo->m_dwBufferBytes)*wo->m_dwBufferBytes;
					nbytes = upper - wo->m_dwOffset;

				// Limit it to what is available/left in sample
					if (nbytes > ActualDataLength - nbytesSoFar)
					{
						nbytes = ActualDataLength - nbytesSoFar;
					}

			//		DWORD dwbuffer1;
			//		LPBYTE buffer1;

			//		DWORD dwbuffer2;
			//		LPBYTE buffer2;

			//#endif

					if (true)
					{
						uint8* buffer1 = wo->m_buffer + wo->m_dwOffset;
						uint32 dwbuffer1 = nbytes;

						std::memcpy(buffer1, ((uint8*)clippedData)+nbytesSoFar, dwbuffer1);

						for (int i = 0; i < 4; i++)
						{
							uint8* buffer1 = ((uint8*)m__channeldata[i]) + wo->m_dwOffset/2;
							uint32 dwbuffer1 = nbytes/2;

							std::memcpy(buffer1, ((uint8*)clippedData)+nbytesSoFar/2, dwbuffer1);
						}

						nbytesSoFar += dwbuffer1;
					}
#if 0
					else
					{
						hr = m_dsBuffer8->Lock(m_dwOffset, nbytes, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
						if (SUCCEEDED(hr))
						{
							ASSERT(dwbuffer1 == nbytes);

							ASSERT(!IsBadWritePtr(buffer1, dwbuffer1));
							ASSERT(!IsBadReadPtr(idata+nbytesSoFar, dwbuffer1));

							ASSERT(nbytesSoFar+dwbuffer1 <= ActualDataLength);

							memcpy(buffer1, idata+nbytesSoFar, dwbuffer1);
							nbytesSoFar += dwbuffer1;

							ASSERT(buffer2 == NULL);
							/*
							if (buffer2)
							{
								CopyMemory(buffer2, pSample->m_pointer+nbytesSoFar, dwbuffer2);
								nbytesSoFar += dwbuffer2;
							}
							*/

							m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
						}
						else
							ASSERT(0);
					}
#endif

					wo->m_dwOffset += nbytes;

				//	ASSERT(m_dwOffset <= 2*m_dwBufferBytes);

					if (wo->m_dwOffset == wo->m_nbuffers*wo->m_dwBufferBytes)
						wo->m_dwOffset = 0;	// Wrap around to first buffer

					if ((wo->m_dwOffset % wo->m_dwBufferBytes) == 0)	// A buffer has been completely filled
				//	if (wo->m_dwOffset == 0)	// A buffer has been completely filled
					{
						if (true)
						{
							if (!wo->m_bReady)
							{
							//	if (wo->m_dwOffset == 0)	// A buffer has been completely filled
								{
									MSWindows::waveOutPause(wo->m_hwo);

									wo->m_bReady = true;
									for (unsigned int i = 0; i < wo->m_nbuffers; i++)
									{
										MSWindows::MMRESULT result = MSWindows::waveOutWrite(wo->m_hwo, &wo->m_whdr[i], sizeof(MSWindows::WAVEHDR));
										ASSERT(result == 0);
									}

									MSWindows::waveOutRestart(wo->m_hwo);
										/*
									// This one isn't filled yet, but it'll probably be filled by the time buffer 0 is done (and this one starts automatically)
									result = waveOutWrite(wo->m_hwo, &wo->m_whdr[1], sizeof(WAVEHDR));
									ASSERT(result == 0);
									*/

									if (!wo->m_bRunning)
									{
										MSWindows::SetEvent(wo->m_hPauseEvent);
									}
								}
							}
							else
							{
								MSWindows::WaitForSingleObject(wo->m_hEvent[0], INFINITE);

								/*
								waveOutWrite(wo->m_hwo, &wo->m_whdr[wo->m_nbuffer], sizeof(WAVEHDR));
								wo->m_nbuffer++;
								if (wo->m_nbuffer == wo->m_nbuffers)
								{
									wo->m_nbuffer = 0;
								}
								*/

#if 0
								waveOutWrite(wo->m_hwo, &wo->m_whdr[wo->m_nbuffer], sizeof(WAVEHDR));
								wo->m_nbuffer++;
								if (wo->m_nbuffer == wo->m_nbuffers)
								{
									wo->m_nbuffer = 0;
								}
#endif
							}
						}
					}
				}
			}

			delete[] clippedData;
			m_mixlock.Unlock();
			/*
			{
				for (int i = 0; i < m_pMusicModule->m_nchannels; i++)
				{
					delete channelCopy[i];
				}
			}
			*/
			sample->Release();
		}
	}
#else
	ASSERT(0);
#endif
}

// static
MSWindows::DWORD WINAPI MusicModuleView::ThreadFunc(void* lpParameter)
{
	((MusicModuleView*)lpParameter)->Func();

	return 0;
}

void MusicModuleView::Func()
{
//	QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);

	MSWindows::WAVEFORMATEX wfx;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 2;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
	wfx.nSamplesPerSec = m_masterSamplesPerSec;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	wfx.cbSize = 0;

	wo = new MediaShow::WaveOutput;
	wo->Init();
//	wo->SetWindow(NULL);

	wo->SetFormat(&wfx);

	// TODO
	m__channeldata[0] = new short[nTotalSamples];
	m__channeldata[1] = new short[nTotalSamples];
	m__channeldata[2] = new short[nTotalSamples];
	m__channeldata[3] = new short[nTotalSamples];
	m__channeldata[4] = new short[nTotalSamples];
	m__channeldata[5] = new short[nTotalSamples];
	m__channeldata[6] = new short[nTotalSamples];
	m__channeldata[7] = new short[nTotalSamples];

	wo->Run();

	double amiga_clockRate;
	
	if (true)	// PAL
		amiga_clockRate = 7093789.2;
	else	// NTSC
		amiga_clockRate = 7159090.5;

//	uint8 m_channel[256];

	uint8 cinstrument[64];
	long cvolume[64];
	long endVolume[64];
	long startVolume[64];
//	int cperiod[64];
	int startPeriod[64];
	int endPeriod[64];

	int minPeriod[64];
	int maxPeriod[64];

	uint8 vibratoWaveform[64];

	uint cnsample[64];
	//Instrument* cinstr[64];
	uint csamplelength[64];

	float* waveform[3];
	float vibrato_amplitude[64] = {0};
	float vibrato_cyclesPerDivision[64] = {0};
	int vibrato_[64] = {0};
	int vibrato_add[64] = {0};
	int vibratoRate[64] = {0};
	bool vibrato_effect[64] = {0};

	const unsigned int VibratoWaveSamples = 1024*12;

	{
		waveform[0] = new float[VibratoWaveSamples];
		waveform[1] = new float[VibratoWaveSamples];
		waveform[2] = new float[VibratoWaveSamples];

		double freq = 2*M_PI / VibratoWaveSamples;
		for (int n = 0; n < VibratoWaveSamples; n++)
		{
		//	waveform[0][n] = sin((n-VibratoWaveSamples/2) * freq);
			waveform[0][n] = sin(n * freq);
		}
	}

	{
		for (int ch = 0; ch < m_pMusicModule->m_nchannels; ch++)
		{
			cinstrument[ch] = 0;
			cvolume[ch] = 256<<9;
			endVolume[ch] = 256;
			startVolume[ch] = 256;
	//		cperiod[ch] = 0;
			cnsample[ch] = 0;
		//	cinstr[ch] = NULL;

			vibratoWaveform[ch] = 0;	// 0=sine (default)
		}
	}

	int samplesPerFrame = 256;
//	int samplesPerFrame = 512;

//	memset(m_masterData, 0, samplesPerFrame*8);

	// TODO, rename mi to something better
//	ULONG mi = 0;

	int ticksPerDivision = m_pMusicModule->m_defaultTempo;
	int beatsPerMinute = m_pMusicModule->m_defaultBPM;
	m_divisionsPerMinute = 24 * beatsPerMinute / ticksPerDivision;

//	QueryPerformanceCounter((LARGE_INTEGER*)&startCounter);

	m_pScopeView->m_masterData = new int32[nTotalSamples*2];

	int songpos = 0;
	int division = 0;

//	HRESULT hr = wo->GetDDSoundBuffer()->Play(0, 0, DSBPLAY_LOOPING);
//	ASSERT(SUCCEEDED(hr));

	const unsigned int masterSamplesPerMinute = 60*m_masterSamplesPerSec;

	LONGLONG totalSamples = 0;

	while (songpos < m_pMusicModule->m_songlength)
	{
		Pattern* pPattern = m_pMusicModule->m_patterns[m_pMusicModule->m_patternOrder[songpos]];

		if (false)	// 669
		{
			ticksPerDivision = m_pMusicModule->m_patternTempo[m_pMusicModule->m_patternOrder[songpos]];//m_pMusicModule->m_defaultTempo;
	//	int beatsPerMinute = m_pMusicModule->m_defaultBPM;
			m_divisionsPerMinute = 24 * beatsPerMinute / ticksPerDivision;
		}

		ULONG startSample = totalSamples;
		if (false)
		{
			SongPosition _songpos;
			_songpos.songpos = songpos;
			_songpos.divpos = division;
			_songpos.samples = startSample;
			m_pPatternView->ReceiveSongPos(_songpos);
		}

		// setup default values for next, effects might override these
		int nextdivision = division + 1;
		int nextsongpos = songpos;
		if (nextdivision >= pPattern->rows)
		{
			nextdivision = 0;
			nextsongpos++;
		}


		{

#if 0
			if (m_pPatternView->m_currentSongPos != songpos)
			{
				m_pPatternView->m_currentSongPos = songpos;
				m_pPatternView->Invalidate();
			}

			m_pPatternView->m_currentDivision = division;
			m_pScroller->MakeVisible(LDraw::RectD(0, m_pPatternView->m_currentDivision*font.GetSize(), 0, font.GetSize()));
#endif
			{
				for (int ch = 0; ch < m_pMusicModule->m_nchannels; ch++)
				{
				//	bool oscillate = false;
					vibrato_effect[ch] = 0;

					const Note& note = pPattern->notes[ch][division];

					if (note.instrument)
					{
						cinstrument[ch] = note.instrument;
					}

					minPeriod[ch] = 113;
					maxPeriod[ch] = 856;

					int period;
					if (false)	// XM
					{
#if 0
						int realnote = (note.note-1) + pSample->relativenote;

						// ??
						if (!m_pMusicModule->m_linearFreq)	// amiga
						{
							short PeriodTab[12*8] = {
						  907,900,894,887,881,875,868,862,856,850,844,838,832,826,820,814,
						  808,802,796,791,785,779,774,768,762,757,752,746,741,736,730,725,
						  720,715,709,704,699,694,689,684,678,675,670,665,660,655,651,646,
						  640,636,632,628,623,619,614,610,604,601,597,592,588,584,580,575,
						  570,567,563,559,555,551,547,543,538,535,532,528,524,520,516,513,
						  508,505,502,498,494,491,487,484,480,477,474,470,467,463,460,457};

//								  ASSERT(pSample->finetune == 0);

						  //int n = note.note-1;
							int period = (PeriodTab[(realnote % 12)*8 + pSample->finetune/16]*(1-Frac(pSample->finetune/16.0)) +
										 PeriodTab[(realnote % 12)*8 + pSample->finetune/16+1]*(Frac(pSample->finetune/16.0)))
										*16/(1<<(realnote / 12));

						//	period = PeriodTab[n];

						 // (The period is interpolated for finer finetune values)

							period = period;
							long Frequency = 8363*1712/period;
						}
						else	// linear
						{
						//	realnote = (note.note-1) + pSample->relativenote;
							period = 10*12*16*4 - realnote*16*4 - pSample->finetune/2;
						}
#endif
					}
					else	// Standard MOD
					{
						period = note.period;
					}

					if (note.note > 0 && note.note <= 120 && cinstrument[ch])
					{
						ASSERT(cinstrument[ch]);
						Instrument* pInstr = m_pMusicModule->m_instruments[cinstrument[ch]-1];

						ASSERT(pInstr->samples.size());
					//	if (pInstr->samples.size())
					//	if (note.note <= 120)
						{
							InstrumentSample* pSample = pInstr->noteSample[note.note-1];
							startVolume[ch] = pSample->volume<<2;
							endVolume[ch] = startVolume[ch];

							cvolume[ch] = endVolume[ch]<<16;

						}

						if (true)	// retrigger
						{
							vibrato_[ch] = 0;
						}

						if (note.effect != 3)
						{
							startPeriod[ch] = period;
							endPeriod[ch] = startPeriod[ch];
						}
					}

					switch (note.effect)
					{
					case 0:
						{
							if (note.effectparms != 0)
							{
							/*
			[0]: Arpeggio
				  Where [0][x][y] means "play note, note+x semitones, note+y
				  semitones, then return to original note". The fluctuations are
				  carried out evenly spaced in one pattern division. They are usually
				  used to simulate chords, but this doesn't work too well. They are
				  also used to produce heavy vibrato. A major chord is when x=4, y=7.
				  A minor chord is when x=3, y=7.
				  */
						//	ASSERT(note.effect == 0);	// TODO
							//ASSERT(0);

								ASSERT(0);
							}
						}
						break;

					case 1:	// Slide up (period)
						{
							// smoothly decrease the period of current sample by x*16+y after each tick in the division
						//	int x = (note.effectparms>>4);
						//	int y = note.effectparms&0xF;

							endPeriod[ch] = startPeriod[ch] - (ticksPerDivision-1) * (int)note.effectparms/*(x*16 + y)*/;
						//	if (endPeriod[ch] < 113)	// You cannot slide beyond the note B3
						//		endPeriod[ch] = 113;
						}
						break;

					case 2:	// Slide down (period)
						{
							// smoothly increase the period of current sample by x*16+y after each tick in the division
						//	int x = (note.effectparms>>4);
						//	int y = note.effectparms&0xF;

							endPeriod[ch] = startPeriod[ch] + (ticksPerDivision-1) * (int)note.effectparms;//(x*16 + y);
						//	if (endPeriod[ch] > 856)	// You cannot slide beyond the note C1
						//		endPeriod[ch] = 856;
						}
						break;

					case 3:	// Slide to note
						{
							/*
     Where [3][x][y] means "smoothly change the period of current sample
     by x*16+y after each tick in the division, never sliding beyond
     current period". The period-length in this channel's division is a
     parameter to this effect, and hence is not played. Sliding to a
     note is similar to effects [1] and [2], but the slide will not go
     beyond the given period, and the direction is implied by that
     period. If x and y are both 0, then the old slide will continue.
	  */

							ASSERT(note.effectparms);	// TODO
							if (note.effectparms)
							{
								/*
								if (note.note > 0 && note.note <= 120 && cinstrument[ch])
								{
									ASSERT(0);
								}
*/

								if (period < startPeriod[ch])	// slide up
								{
									endPeriod[ch] = startPeriod[ch] - (ticksPerDivision-1) * (int)note.effectparms;
									minPeriod[ch] = period;
								}
								else	// slide down
								{
									endPeriod[ch] = startPeriod[ch] + (ticksPerDivision-1) * (int)note.effectparms;
									maxPeriod[ch] = period;
								}
							}
						}
						break;

					case 4:
						{
						// vibrato
						/*
						  Where [4][x][y] means "oscillate the sample pitch using a
						  particular waveform with amplitude y/16 semitones, such that (x *
						  ticks)/64 cycles occur in the division". The waveform is set using
						  effect [14][4]. By placing vibrato effects on consecutive
						  divisions, the vibrato effect can be maintained. If either x or y
						  are 0, then the old vibrato values will be used.
						  */

							vibrato_effect[ch] = true;

							int x = (note.effectparms>>4);
							int y = note.effectparms&0xF;

							unsigned int samplesPerDivision = masterSamplesPerMinute / m_divisionsPerMinute;

							if (x != 0)
							{
								vibrato_cyclesPerDivision[ch] = (x*ticksPerDivision)/64.0;
							}

							if (y != 0)
							{
								vibrato_amplitude[ch] = y/32.0;// * 1.0595;
							//	float amplitude = y * 1.0595;
							}

						//	vibratoRate = (samplesPerDivision * cyclesPerDivision) / 1024;

						//	int samplesPerCycle = (LONGLONG)m_masterSamplesPerSec * samplesPerDivision / cyclesPerDivision;
						//	vibratoRate = samplesPerCycle / 1024;

							vibratoRate[ch] = VibratoWaveSamples * vibrato_cyclesPerDivision[ch] * m_masterSamplesPerSec / samplesPerDivision;
							//vibratoRate /= 10;
							//	oscillate = true;

						//	ASSERT(VibratoWaveSamples*cyclesPerDivision * m_masterSamplesPerSec == samplesPerDivision * vibratoRate);

						}
						break;

					case 6:	// Continue 'Vibrato', but also do Volume slide
						{
							// TODO
							ASSERT(0);
						}
						break;

					case 8:	// set panning
						{
							// TODO
							ASSERT(0);
						}
						break;

					case 9:	// Set sample offset
						{
							// TODO
							ASSERT(0);
						}
						break;

					case 10: // Volume slide
						{
							int x = note.effectparms>>4;
							int y = note.effectparms&0xF;

							if (x)
							{
								// slide volume up x*(ticks-1) ignore y

								endVolume[ch] = startVolume[ch] + (x*(ticksPerDivision-1)<<2);
								if (endVolume[ch] > 256) endVolume[ch] = 256;
							}
							else if (y)
							{
								// slide volume down y*(ticks-1)

								endVolume[ch] = startVolume[ch] - (y*(ticksPerDivision-1)<<2);
								if (endVolume[ch] < 0) endVolume[ch] = 0;
							}
						}
						break;

					case 11:	// Position Jump
						{
							// TODO
							ASSERT(0);
						}
						break;

					case 12:	// Set volume
						{
							int volume = (int)note.effectparms<<2;
							startVolume[ch] = volume;
							endVolume[ch] = volume;
							cvolume[ch] = volume<<16;
						}
						break;

					case 13:	// pattern break
						{
							// stop the pattern after this division and continue the song at the next pattern at division x*10+y"
							int x = note.effectparms>>4;
							int y = note.effectparms&0xF;

							nextsongpos++;
							nextdivision = x*10 + y;
						}
						break;

					case 14:
						{
							int x = note.effectparms>>4;
							int y = note.effectparms&0xF;

							if (x == 4)	// Set vibrato waveform
							{
								// Untested
								bool retrigger = (y>>2)&1;
								vibratoWaveform[ch] = y&3;
							}
							else if (x == 6) // Loop pattern
							{
/*
     Where [14][6][x] means "set the start of a loop to this division if
     x is 0, otherwise after this division, jump back to the start of a
     loop and play it another x times before continuing". If the start
     of the loop was not set, it will default to the start of the
     current pattern. Hence 'loop pattern' cannot be performed across
     multiple patterns. Note that loops do not support nesting, and you
     may generate an infinite loop if you try to nest 'loop pattern's.							
	  */

								ASSERT(0);	// TODO

								if (y == 0)
								{
								}
								else
								{
								}
							}
							else if (x == 9)// Retrigger sample
							{
								// TODO
								ASSERT(0);
							}
							else if (x == 13)// Note delay
							{
								// TODO
								ASSERT(0);
							}
							else
								ASSERT(0);
						}
						break;

					case 15:	// set speed
						{
							int z = note.effectparms;//(note.effectparms>>4) | (note.effectparms&0xF);
							if (z == 0) z = 1;

							if (z <= 32)
							{
								// set ticks/division to z
								ticksPerDivision = z;
							}
							else
							{
								// set beats/minute to z
								beatsPerMinute = z;
							}

							m_divisionsPerMinute = 24 * beatsPerMinute / ticksPerDivision;
						}
						break;

					case 16:	// Set Global volume (XM only)
						{
							// TODO
							ASSERT(0);
						}
						break;

					default:
						ASSERT(0);
					}
				}
			}

			{
				for (int ch = 0; ch < m_pMusicModule->m_nchannels; ch++)
				{
					const Note& note = pPattern->notes[ch][division];

					if (note.instrument)	// Done above ???
					{
					//	Instrument* pInstr = m_pMusicModule->m_instruments[note.instrument-1];

						cinstrument[ch] = note.instrument;
					}

					if (note.note && cinstrument[ch])
					{
					//	cperiod[ch] = note.period;
					//	cinstr[ch] = m_pMusicModule->m_instruments[csample[ch]-1];

						// Reset sample start and repeat

						cnsample[ch] = 0;
		//				csamplelength[ch] = cinstr[ch]->samples[0]->sampleLength;

						Instrument* pInstr = m_pMusicModule->m_instruments[cinstrument[ch]-1];

						ASSERT(pInstr->samples.size());
					//	if (pInstr->samples.size())
						{
							if (note.note == 255)// key off
							{
								csamplelength[ch] = 0;	// This will do it ??
							}
							else if (note.note <= 120)
							{
								InstrumentSample* pSample = pInstr->noteSample[note.note-1];
								csamplelength[ch] = pSample->sampleLength;
							}
						}
					}
				}
			}

			unsigned int samplesPerDivision = masterSamplesPerMinute / m_divisionsPerMinute;

			unsigned int divisionSamplesSoFar = 0;
			while (divisionSamplesSoFar < samplesPerDivision)
			{
				// TODO, rename mi to something better
			//	unsigned int frameStart = mi;

				// First set it to the end of the division
				unsigned int samplesToProcess = samplesPerDivision - divisionSamplesSoFar;

				// Then cut the division into frames
				if (samplesToProcess > samplesPerFrame)
				{
					samplesToProcess = samplesPerFrame;
				}

				DataSample* datasample = new DataSample;
				datasample->AddRef();

				for (int ch = 0; ch < m_pMusicModule->m_nchannels; ch++)
				{
					int jj = totalSamples;

					int16* channelData = (int16*)MSWindows::HeapAlloc(MSWindows::GetProcessHeap(), 0, samplesPerFrame*2);
					std::memset(channelData, 0, 2*samplesToProcess);
					datasample->copy[ch] = (uint8*)channelData;

					if (cinstrument[ch]/* && cvolume[ch]*/)
					{
						Instrument* pInstr = m_pMusicModule->m_instruments[cinstrument[ch]-1];

						int cperiod;
						
						{
							cperiod = startPeriod[ch] + (endPeriod[ch] - startPeriod[ch]) * (LONGLONG)divisionSamplesSoFar / samplesPerDivision;

							if (cperiod < minPeriod[ch]) cperiod = minPeriod[ch];
							else if (cperiod > maxPeriod[ch]) cperiod = maxPeriod[ch];
						}

						/*
						if (oscillate)	// oscillate
						{
							cperiod = cperiod + waveform[ch][divisionSamplesSoFar * 1024 / samplesPerDivision];
						}
						*/

					//	unsigned int samplerate = amiga_clockRate / (cperiod*2);	// TODO, explain
						LONGLONG samplerate = amiga_clockRate / (cperiod*2);	// TODO, explain
						if (false)	// xm files
						{
							if (!m_pMusicModule->m_linearFreq)	// amiga
								samplerate = 8363*1712/cperiod;//Period;
							else	// linear
								samplerate = 8363*pow(2, ((6*12*16*4 - cperiod) / (double)(12*16*4)));
						}

						float* pwaveform = waveform[vibratoWaveform[ch]];

						if (vibrato_effect[ch])	// oscillate
						{
							int vibrato2 = (vibratoRate[ch] * vibrato_[ch]) / m_masterSamplesPerSec;
						//	int vibrato2 = (vibratoRate * vibrato_) / samplerate;

							float v = pwaveform[vibrato2 & (VibratoWaveSamples-1)] * vibrato_amplitude[ch];
						//	float v = waveform[ch][(divisionSamplesSoFar * 1024 / samplesPerDivision) & 1023] * vibrato_amplitude;
							if (v >= 0)
							{
								double multiply = pow(2, v);
						//		samplerate *= multiply;
							}
							else
							{
								double divide = pow(2, fabs(v));
						//		samplerate /= divide;
							}
						}

						vibrato_[ch] += samplesToProcess;

#define BITS	11
#define MASK	((LONGLONG)1<<BITS)

					//	unsigned int perSample = (samplerate<<BITS) / m_masterSamplesPerSec;
						LONGLONG perSample = (samplerate<<BITS) / m_masterSamplesPerSec;
						unsigned int k2 = cnsample[ch];

						int perVolume = ((endVolume[ch] - startVolume[ch])<<16) / (int)samplesPerDivision;//destLen;
					//	long volume = cvolume[ch];/* << 2*/;
						int volume = ((startVolume[ch]<<16) + (((LONGLONG)endVolume[ch]-startVolume[ch])<<16) * (LONGLONG)divisionSamplesSoFar / (LONGLONG)samplesPerDivision);
					//	volume = v;
						ASSERT(volume >= 0);
						ASSERT(volume <= (256<<16));

					//	if (perVolume < 0)
					//		volume += 256;

						if (pInstr->samples.size())
						{
							int8* sampledata = (int8*)pInstr->samples[0]->data;

							for (unsigned int n = 0; n < samplesToProcess; n++)
							{
								unsigned int k = k2>>BITS;

							//	if (vibrato_effect[ch])
								{
									int gg = (jj+n);
									float t = (float)gg / m_masterSamplesPerSec;

									k = k + (int)((pwaveform[(int)(t * VibratoWaveSamples) & (VibratoWaveSamples-1)]+1)*2000);
								}

								k = k % (pInstr->samples[0]->repeatPoint + pInstr->samples[0]->repeatLength);

								/*
								ASSERT(k >= 0);

								if (k >= csamplelength[ch])
								{
									unsigned int past = k % csamplelength[ch];
									if (pInstr->samples[0]->repeatLength > 2)
									{
										k2 = (pInstr->samples[0]->repeatPoint+past)<<BITS;
										k = k2>>BITS;
										csamplelength[ch] = pInstr->samples[0]->repeatPoint + pInstr->samples[0]->repeatLength;
									}
									else
										break;
								}
								*/

								// linear interpolation
								int value = sampledata[k] + (((sampledata[k+1] - sampledata[k]) * (k2 & (MASK-1))) >> BITS);
								int value2 = value * (volume>>16) * 3 / 4/*TODO, depends on number of channels*/;

								ASSERT(value2 <= 32767);
								ASSERT(value2 >= -32768);

								channelData[n] = (short)value2;

#if 0
								mi++;
#endif
								/*
								if (mi > 100000000)
								{
									ASSERT(0);
									mi = 0;
								}
								*/

								volume += perVolume;
								k2 += perSample;

								ASSERT(volume >= 0);
								ASSERT(volume <= (256<<16));
							}
						}
					//	if (volume < 0)
					//		volume = 0;
						cnsample[ch] = k2;
						cvolume[ch] = volume;//endVolume[ch];
						ASSERT(volume >= 0);
						ASSERT(volume <= (256<<16));

						/*
						m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
						*/

						//wo->Stop();
					}

				//	m_pScopeView->Receive(ch, (uint8*)channelData, samplesToProcess*2);
				}

			//	Sleep(60 * 1000 / m_divisionsPerMinute);
			//	LONGLONG counter;
			//	QueryPerformanceCounter((LARGE_INTEGER*)&counter);

				datasample->length = samplesToProcess;//*2;

				m_pScopeView->ReceiveMaster(datasample);//samplesToProcess*wfx.nBlockAlign);
				datasample->Release();

#if 0
				{
					m_pScopeView->ReceiveMaster(samplesToProcess*wfx.nBlockAlign);
				//	wo->Receive((uint8*)clippedData, samplesToProcess*wfx.nBlockAlign);
				}
#endif

#if 0
				{
					DWORD dwbuffer1;
					LPBYTE buffer1;

					DWORD dwbuffer2;
					LPBYTE buffer2;

					IDirectSoundBuffer8* m_dsBuffer8 = wo->GetDDSoundBuffer();

					ULONG Offset = frameStart*wfx.nBlockAlign;
					ULONG nbytes = samplesPerFrame*wfx.nBlockAlign;

					HRESULT hr = m_dsBuffer8->Lock(Offset, nbytes, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
					if (SUCCEEDED(hr))
					{
						//MessageBeep(-1);

					//	ASSERT(dwbuffer1 == nbytes);

					//	ASSERT(!IsBadWritePtr(buffer1, dwbuffer1));
					//	ASSERT(!IsBadReadPtr(idata+nbytesSoFar, dwbuffer1));

					//	ASSERT(nbytesSoFar+dwbuffer1 <= ActualDataLength);

						memcpy(buffer1, ((uint8*)m_masterData) + frameStart*wfx.nBlockAlign, dwbuffer1);
						if (buffer2)
						{
							memcpy(buffer2, ((uint8*)m_masterData) + frameStart*wfx.nBlockAlign + dwbuffer1, dwbuffer2);
						}
					//	nbytesSoFar += dwbuffer1;

					//	ASSERT(buffer2 == NULL);
						/*
						if (buffer2)
						{
							CopyMemory(buffer2, pSample->m_pointer+nbytesSoFar, dwbuffer2);
							nbytesSoFar += dwbuffer2;
						}
						*/

						m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
					}
					else
						ASSERT(0);

					//LONGLONG delay = (counter - startCounter);

					if (d == 0)
					{
						HRESULT hr = wo->GetDDSoundBuffer()->Play(0, 0, DSBPLAY_LOOPING);
						ASSERT(SUCCEEDED(hr));
					}

					//if (d >= 1)
					{
						DWORD dwCurrentPlayCursor;
						DWORD dwCurrentWriteCursor;
						hr = m_dsBuffer8->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);
						ASSERT(SUCCEEDED(hr));

					//	ASSERT(dwCurrentWriteCursor < (divisionStart + samplesPerDivision));

						// Wait for the completion of the previous division, not the one we've just done, but the one before that
						LONG uDelay = ((LONG)divisionStart - (LONG)(dwCurrentPlayCursor / wfx.nBlockAlign)) * 1000 / wfx.nSamplesPerSec;
						if (uDelay > 0)
						{
							// Wait
							HANDLE hEvent = CreateEvent(NULL, false, false, NULL);
							//Sleep(samplesPerDivision * 1000 / wfx.nSamplesPerSec);
							timeSetEvent(uDelay, 0, (LPTIMECALLBACK)hEvent, 0, TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);
							WaitForSingleObject(hEvent, INFINITE);
							CloseHandle(hEvent);
						}
					}
				}
#endif

			//	mi = divisionStart + samplesPerDivision;//(60 * masterSampleRate / m_divisionsPerMinute);//*1.03;
#if 0			
				mi = frameStart + samplesToProcess;
#endif
		//		divisionStart2 = divisionStart;

			//	minutes += minutesPerFrame;
			//	divisionTime += minutesPerFrame;

				divisionSamplesSoFar += samplesToProcess;
				totalSamples += samplesToProcess;
			}

			for (int ch = 0; ch < m_pMusicModule->m_nchannels; ch++)
			{
				startVolume[ch] = endVolume[ch];
				startPeriod[ch] = endPeriod[ch];
			}
		}

		division = nextdivision;
		songpos = nextsongpos;
	}

	TRACE("Song done\n");

#if WIN32
	//Sleep(80 * 1000);
#endif
}

void MusicModuleView::OnMouseDown(UI::MouseButtonEventArgs* args)
{
	//return;
	/*
	if (true)
	{
		WaveformView* ctl = new WaveformView(pFile);//MPEGFrames
		ctl->m_pCanvas = m_pCanvas;
		IViewOf* pView = ctl;

		m_views.push_back(pView);

		ChildWindow* pWindow = new ChildWindow;
		pWindow->put_Width(Length(200, Length::UnitAbsolute));
		pWindow->put_Height(Length(200, Length::UnitAbsolute));

		pWindow->put_Content(dynamic_cast<Control*>(pView));

		pWindow->put_TitleText(OLESTR("Test"));

		m_m_pWindowContainer->AddChild(pWindow);
	}
	else
	*/
	{

#if WIN32
		{
			m_hEvent1 = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_hEventPop1 = MSWindows::CreateEventA(NULL, false, false, NULL);
			MSWindows::DWORD threadID;
			MSWindows::CreateThread(NULL, 0, ThreadFunc1, this, 0, &threadID);
		}

		{
			m_hEvent2 = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_hEventPop2 = MSWindows::CreateEventA(NULL, false, false, NULL);
			MSWindows::DWORD threadID;
			MSWindows::CreateThread(NULL, 0, ThreadFunc2, this, 0, &threadID);
		}

		{
			m_hEvent3 = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_hEventPop3 = MSWindows::CreateEventA(NULL, false, false, NULL);
			MSWindows::DWORD threadID;
			MSWindows::CreateThread(NULL, 0, ThreadFunc3, this, 0, &threadID);
		}

		MSWindows::DWORD threadID;
		HANDLE hThread = MSWindows::CreateThread(NULL, 0, ThreadFunc, this, 0, &threadID);
	//	SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
//			timeSetEvent(0, 0, ThreadFunc, this, TIME_ONESHOT | TIME_CALLBACK_FUNCTION);
#else
		ASSERT(0);
#endif
	}
}

DataSample::DataSample()
{
	m_refcount = 0;

	for (int i = 0; i < 64; i++)
	{
		copy[i] = NULL;
	}
}

DataSample::~DataSample()
{
	for (int i = 0; i < 64; i++)
	{
		delete[] copy[i];
	}
}

unsigned int DataSample::AddRef()
{
	return MSWindows::InterlockedIncrement((long*)&m_refcount);
//	m_refcount++;
//	return m_refcount;
}

unsigned int DataSample::Release()
{
	long refcount = MSWindows::InterlockedDecrement((long*)&m_refcount);
	//m_refcount--;
	if (refcount == 0)
	{
		for (int i = 0; i < 64; i++)
		{
			if (copy[i])
			{
				MSWindows::HeapFree(MSWindows::GetProcessHeap(), 0, copy[i]);
				copy[0] = 0;
			}
		}
	}
	return 0;
}

ScopeView::ScopeView()
{
	m_p = NULL;

//	m_scopeSeconds = 0.07;
	m_scopeSeconds = 0.02;

	m_scopeSamples = 44100*m_scopeSeconds;
	m_sofar = 0;
	m_sampleSoFar = 0;

	//m_pixelWidth = 56;
	m_pixelWidth = 128;
	m_buffer = new int16[m_pixelWidth];

	m_masterData = NULL;

	for (int i = 0; i < 64; i++)
	{
		m_channelBuffer[i] = new int16[m_scopeSamples];
		std::memset(m_channelBuffer[i], 0, m_scopeSamples*sizeof(int16));
	}
}

void ScopeView::MixChannels(ULONG samplesToProcess, int nchannels, short* m_channelData[], short* clippedData)
{
	std::memset(m_masterData, 0, 8*samplesToProcess);

	for (int ch = 0; ch < m_p->m_pMusicModule->m_nchannels; ch++)
	{
		if (m_p->m_pMusicModule->m_channelEnabled[ch])
		{
			uint32 m = 0;
			int16* channelData = m_channelData[ch];

			if (ch == 0 || ch == 3)
			{
				for (int n = 0; n < samplesToProcess; n++)
				{
					int32 v = m_masterData[m*2+0] + channelData[n];

					m_masterData[m*2+0] = v;
					m++;
				}
			}
			else
			{
				for (int n = 0; n < samplesToProcess; n++)
				{
					int32 v = m_masterData[m*2+1] + channelData[n];

					m_masterData[m*2+1] = v;
					m++;
				}
			}
		}
	}

	// Clip
	{
		uint32 len = samplesToProcess*2;
		int32* p = m_masterData;

		int16* dest = clippedData;
		for (ULONG i = 0; i < len; i++)
		{
			int32 v = *p++;

			if (v > 32767) v = 32767;
			else if (v < -32768) v = -32768;

			*dest++ = v;
		}
	}
}

void ScopeView::ReceiveMaster(DataSample* sample/*ULONG datalength*/)
{
#if WIN32
//	ULONG samplesToProcess = datalength / 4;
	ULONG samplesToProcess = sample->length;// / 4;


	{
		/*
		while (m_channelLength.size() > 50)
		{
			WaitForSingleObject(m_p->m_hEventPop2, INFINITE);
		}
		*/
		m_p->m_lock2.Lock();

#if 0
		for (int ch = 0; ch < m_p->m_pMusicModule->m_nchannels; ch++)
		{
#if 0
			uint8* copy = new uint8[datalength / 2];
			memcpy(copy, (uint8*)m_channelData[ch], datalength / 2);
			m_channelCopy[ch].push(copy/*(uint8*)m_channelData[ch]*/);
#endif

		}
		m_channelLength.push(datalength / 2);
#endif

		sample->AddRef();
		m_channelQueue.push(sample);

		m_p->m_lock2.Unlock();
		MSWindows::SetEvent(m_p->m_hEvent2);
	}

	{
		while (m_masterQueue.size() > 10)
		{
			MSWindows::WaitForSingleObject(m_p->m_hEventPop3, INFINITE);
		}
//				m_masterCopy.push((uint8*)clippedData);
		m_p->m_lock3.Lock();
#if 0
		for (int ch = 0; ch < m_p->m_pMusicModule->m_nchannels; ch++)
		{
			m_masterCopy[ch].push((uint8*)m_channelData[ch]);
		}
		m_masterLength.push(datalength);
#endif
		sample->AddRef();
		m_masterQueue.push(sample);

		m_p->m_lock3.Unlock();

		MSWindows::SetEvent(m_p->m_hEvent3);
	}
#else
	ASSERT(0);
#endif
}

void ScopeView::Func2()
{
#if WIN32
	HANDLE hEvent = MSWindows::CreateEventA(NULL, false, false, NULL);

	while (1)
	{
		MSWindows::WaitForSingleObject(m_p->m_hEvent2, INFINITE);
		while (!m_channelQueue.empty())
		{
			m_p->m_lock2.Lock();
			DataSample* sample = m_channelQueue.front();
			m_channelQueue.pop();

			/*
			ULONG channellength = m_channelLength.front();
			m_channelLength.pop();
			uint8* channelCopy[64];
			for (int i = 0; i < m_p->m_pMusicModule->m_nchannels; i++)
			{
				channelCopy[i] = m_channelCopy[i].front();
				m_channelCopy[i].pop();
			}
			*/
			m_p->m_lock2.Unlock();

			MSWindows::SetEvent(m_p->m_hEventPop2);

			/*
		//	LONGLONG dwCurrentPlayCursor = wo->GetCurrentPlayCursor();
			DWORD dwCurrentPlayCursor;
			DWORD dwCurrentWriteCursor;
			HRESULT hr = wo->GetDDSoundBuffer()->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);
			ASSERT(SUCCEEDED(hr));
			*/

			ULONG sofar = 0;

			while (sofar < sample->length)
			{
				ULONG nsamples = 4096;
				if (sofar + nsamples > sample->length)
				{
					nsamples = sample->length - sofar;
				}

				m_lock.Lock();

				// Shift the old scope data, and add the new data
				for (int ch = 0; ch < m_p->m_pMusicModule->m_nchannels; ch++)
				{
					//uint8* data = channelCopy[ch];
					uint8* data = sample->copy[ch];

					std::memmove(m_channelBuffer[ch], m_channelBuffer[ch]+nsamples, (m_scopeSamples-nsamples)*2);
					std::memcpy(m_channelBuffer[ch]+m_scopeSamples-nsamples, (short*)data + sofar, nsamples*2);
				}

				m_lock.Unlock();

				m_p->m_sampleCounter += nsamples;

				LONG samplesSoFar = m_sampleSoFar;
				LONG uDelay;

#if 0
				if (false)
				{
					LONGLONG counter;
					QueryPerformanceCounter((LARGE_INTEGER*)&counter);

					// Wait for it
				//	m_pPatternView->m_lock.Lock();
				//	LONG uDelay = ((LONG)samplesSoFar - (LONG)(dwCurrentPlayCursor)) * 1000 / 44100/*wfx.nSamplesPerSec*/;
					uDelay = (samplesSoFar - ((double)(counter-startCounter)/m_freq * 44100)) * 1000 / 44100;
				//	m_pPatternView->m_lock.Unlock();
				}
				else
#endif
				{
					LONG dwCurrentPlayCursor = m_p->wo->GetCurrentPlayCursor();
					while (dwCurrentPlayCursor == 0)
					{
						MSWindows::Sleep(100);
						dwCurrentPlayCursor = m_p->wo->GetCurrentPlayCursor();
					}

					uDelay = ((LONG)samplesSoFar - (LONG)(dwCurrentPlayCursor)) * 1000 / 44100/*wfx.nSamplesPerSec*/;
				}

	//			TRACE("%d - %d = %d\n", (LONG)samplesSoFar, (LONG)dwCurrentPlayCursor/4, uDelay);
				if (uDelay > 0)
				{
					// Wait
					//Sleep(samplesPerDivision * 1000 / wfx.nSamplesPerSec);
					MSWindows::timeSetEvent(uDelay, 0, (MSWindows::LPTIMECALLBACK)hEvent, 0, TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);
					MSWindows::WaitForSingleObject(hEvent, INFINITE);
				}

				//if (m_p->m_sampleCounter >= 256*4)
				if (m_p->m_sampleCounter >= 256*4)
				{
					m_p->m_sampleCounter = 0;
					InvalidateRender();
				}

				sofar += nsamples;
				m_sampleSoFar += nsamples;
			}

			sample->Release();

		}
	}

	MSWindows::CloseHandle(hEvent);
#else
	ASSERT(0);
#endif
}

LDraw::SizeD ScopeView::MeasureOverride(LDraw::SizeD availSize)
{
	return LDraw::SizeD((m_pixelWidth+4)*m_p->m_pMusicModule->m_nchannels, m_pixelWidth);
//	return LDraw::SizeD((m_pixelWidth+4)*m_p->m_pMusicModule->m_nchannels, m_pixelWidth*3);
}

void ScopeView::OnRender(Graphics* pGraphics)
{
//	return;

	if (true)
	{
		LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
	//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

		LONGLONG samplesPerPixel = (m_scopeSeconds * ((LONGLONG)m_p->m_masterSamplesPerSec<<16)) / (double)(m_pixelWidth);

		int x = 0;

		int pixelLeft = 0;
		int pixelRight = m_pixelWidth;

		LONGLONG left = 0;
		LONGLONG right = m_scopeSamples<<16;

		m_lock.Lock();

		pGraphics->TranslateTransform(0.5, 0.5);

		for (int ch = 0; ch < m_p->m_pMusicModule->m_nchannels; ch++)
		{
			pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, m_pixelWidth, m_computedSize.Height);

			if (m_p->m_pMusicModule->m_channelEnabled[ch])
			{
				LDraw::GraphicsPathF* path = new LDraw::GraphicsPathF;
				LONGLONG i;

				for (i = left; i < right; i += samplesPerPixel)
				{
					short* p = m_channelBuffer[ch] + (i>>16);

					int n = (i-left) / (samplesPerPixel);

				//	minbuffer[n] = 0;
				//	maxbuffer[n] = 0;
					m_buffer[n] = *p;

					for (int j = 0; j < (samplesPerPixel>>16); j++)
					{
					//	minbuffer[n] = min(minbuffer[n], *p);
					//	maxbuffer[n] = max(maxbuffer[n], *p);
						m_buffer[n] = (m_buffer[n] + *p) / 2;
						p++;
					}
				}

				{
					i = pixelLeft;
					//path.AddMove(i, m_computedSize.Height/2);
					for (; i < pixelRight; i++)
					{
						int y = m_buffer[i-pixelLeft];
						if (i == 0)
						{
							path->AddMove(i, m_computedSize.Height/2 + y*m_computedSize.Height / 65536);
						}
						else
						{
							path->AddLine(i, m_computedSize.Height/2 + y*m_computedSize.Height / 65536);
						}

						//path.AddLine(i+1/*/16.0*/, m_computedSize.Height/2 + maxbuffer[i-pixelLeft]*m_computedSize.Height / 65536);
					}
				//	path.AddLine(i, m_computedSize.Height/2);
				//	path.AddLine(pixelLeft, m_computedSize.Height/2);
				}

#if 0
				{
					i = pixelLeft;
					path.AddMove(i, m_computedSize.Height/2);
					for (; i < pixelRight; i++)
					{
						path.AddLine(i, m_computedSize.Height/2 + maxbuffer[i-pixelLeft]*m_computedSize.Height / 65536);
						path.AddLine(i+1/*/16.0*/, m_computedSize.Height/2 + maxbuffer[i-pixelLeft]*m_computedSize.Height / 65536);
					}
					path.AddLine(i, m_computedSize.Height/2);
					path.AddLine(pixelLeft, m_computedSize.Height/2);
				}

			//	path.AddRectangle(0, 0, 200, 20);

				{
					i = pixelLeft;
					path.AddMove(i, m_computedSize.Height/2);
					for (; i < pixelRight; i++)
					{
						path.AddLine(i, m_computedSize.Height/2 + minbuffer[i-pixelLeft]*m_computedSize.Height / 65536);
						path.AddLine(i+1, m_computedSize.Height/2 + minbuffer[i-pixelLeft]*m_computedSize.Height / 65536);
					}
					path.AddLine(i, m_computedSize.Height/2);
					path.AddLine(pixelLeft, m_computedSize.Height/2);
				}
#endif

				/*
				{
					i = pixelLeft;
					path.AddMove(i, m_computedSize.Height/2);
					for (; i < pixelRight; i++)
					{
						path.AddLine(i, m_computedSize.Height/2 + minbuffer[i-pixelLeft]*m_computedSize.Height / 256);
					}
					path.AddLine(i, m_computedSize.Height/2);
					path.AddLine(left, m_computedSize.Height/2);
					pGraphics->FillPath(&brush, &path);
				}
				*/
				/*
				{
					i = right;
					path.AddMove(i, m_computedSize.Height/2);
					i--;
					for (; i > left; i--)
					{
						path.AddLine(i, m_computedSize.Height/2 + minbuffer[i-left]*m_computedSize.Height / 256);
					}
					path.AddLine(i, m_computedSize.Height/2);
					path.AddLine(right, m_computedSize.Height/2);

					pGraphics->FillPath(&brush, &path);
				}
				*/
#if 0
				if (false)
				{
					LDraw::SolidBrush brush(LDraw::Color(0, 0/*200*/, 0));
					if (false)
					{
						LDraw::SolidBrush shadowbrush(LDraw::Color(0, 0/*200*/, 0));
						pGraphics->TranslateTransform(1, 1);
						pGraphics->FillPath(shadowbrush, &path);
						pGraphics->TranslateTransform(-1, -1);
					}
				//	pGraphics->FillPath(&brush, &path);
				}
				else
#endif
				{
#if 0
					if (false)	// shadow
					{
						LDraw::Pen pen(LDraw::Color(0, 0, 0), 0.6);
						pen.SetLineJoin(LDraw::LineJoinBevel);
						pGraphics->TranslateTransform(1, 1);
						pGraphics->DrawPath(pen, &path);
						pGraphics->TranslateTransform(-1, -1);
					}
#endif
					LDraw::Pen* pen = new LDraw::Pen(LDraw::Color(0, 0, 0), 1);
					pen->SetLineJoin(LDraw::LineJoinBevel);
					pGraphics->DrawPath(pen, path);
				}
			}
			else
			{
			}

			x += m_pixelWidth;
			pGraphics->TranslateTransform(m_pixelWidth+4, 0);
		}

	//	delete minbuffer;
	//	delete maxbuffer;
	//	delete buffer;

		m_lock.Unlock();

		pGraphics->SetSmoothingMode(oldSmoothingMode);
	}
}

#if 0
void MusicModuleView::ScopeView::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			int ch = point.X / (m_pixelWidth+4);

			if (m_p->m_pMusicModule->m_channelEnabled[ch])
			{
				m_p->m_pMusicModule->m_channelEnabled[ch] = false;
			}
			else
			{
				m_p->m_pMusicModule->m_channelEnabled[ch] = true;
			}

#if 0
#if WIN32
			// ??
			LONGLONG playCursor = m_p->wo->GetCurrentPlayCursor();
			LONGLONG writeCursor = playCursor + 1000;	// A little ahead
			writeCursor %= nTotalSamples;
			writeCursor = (writeCursor/1000) * 1000;

			m_p->m_mixlock.Lock();
			ULONG offset = writeCursor;
			ULONG total = 0;
			for (int i = 0; i < m_p->wo->m_nbuffers; i++)
			{
				if (m_p->wo->m_whdr[i].dwFlags & WHDR_DONE)
				{
					MessageBeep(-1);
				}
			}
#else
			ASSERT(0);
#endif
			// ??
			/*
			while (total < nTotalSamples)
			{
				ULONG len = 1000;
				if (offset+len > nTotalSamples)
				{
					len = nTotalSamples - offset;
				}

				short* chdata[32];
				chdata[0] = m_p->m__channeldata[0] + offset;
				chdata[1] = m_p->m__channeldata[1] + offset;
				chdata[2] = m_p->m__channeldata[2] + offset;
				chdata[3] = m_p->m__channeldata[3] + offset;

				MixChannels(len, 4, chdata, (short*)m_p->wo->m_buffer + offset);

				offset += len;
				total += len;
				if (offset == nTotalSamples)	// Wrap around
					offset = 0;
			}
			*/

			m_p->m_mixlock.Unlock();
#endif

			Invalidate();
		}
	}
}
#endif

void PatternView::Func1()
{
#if WIN32
	HANDLE hEvent = MSWindows::CreateEventA(NULL, false, false, NULL);

	//LDraw::Font font(OLESTR("Courier New"), 12);

	while (1)
	{
		MSWindows::WaitForSingleObject(m_p->m_hEvent1, INFINITE);
		while (!m_songpos.empty())
		{
			SongPosition songpos = m_songpos.front();
			m_songpos.pop();
			MSWindows::SetEvent(m_p->m_hEventPop1);

			LONG dwCurrentPlayCursor = m_p->wo->GetCurrentPlayCursor();
			while (dwCurrentPlayCursor == 0)
			{
				MSWindows::Sleep(100);
				dwCurrentPlayCursor = m_p->wo->GetCurrentPlayCursor();
			}

			LONG uDelay = ((LONG)songpos.samples - (LONG)(dwCurrentPlayCursor)) * 1000 / 44100/*wfx.nSamplesPerSec*/;

//			TRACE("%d - %d = %d\n", (LONG)samplesSoFar, (LONG)dwCurrentPlayCursor/4, uDelay);
			if (uDelay > 0)
			{
				// Wait
				//Sleep(samplesPerDivision * 1000 / wfx.nSamplesPerSec);
				MSWindows::timeSetEvent(uDelay, 0, (MSWindows::LPTIMECALLBACK)hEvent, 0, TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);
				MSWindows::WaitForSingleObject(hEvent, INFINITE);
			}

			m_currentSongPos = songpos.songpos;
			m_currentDivision = songpos.divpos;

			m_p->m_pScroller->MakeVisible(LDraw::RectD(0, m_currentDivision*GetFont()->GetSize(), 0, GetFont()->GetSize()));

			InvalidateRender();
		}
	}

	MSWindows::CloseHandle(hEvent);
#else
ASSERT(0);
#endif
}

void PatternView::ReceiveSongPos(SongPosition& songpos)
{
	m_songpos.push(songpos);
#if WIN32
	MSWindows::SetEvent(m_p->m_hEvent1);
#else
	ASSERT(0);
#endif
}

void PatternView::OnRender(Graphics* pGraphics)
{
	static StringA note_off_str(true, "___");
	static StringA no_note_str(true, "--");

	if (m_p->m_pMusicModule->m_songlength == 0)
		return;

	Pattern* pPattern = m_p->m_pMusicModule->m_patterns[m_p->m_pMusicModule->m_patternOrder[m_currentSongPos]];

	uint8 cinstrument[64] = {0};

	//pGraphics->TranslateTransform(0, 

//	LDraw::RectF clipbox;
//	pGraphics->GetClipBounds(&clipbox);

	/*static*/ LDraw::SolidBrush* bgBrush = new LDraw::SolidBrush(LDraw::Color(60, 90, 200));
	pGraphics->FillRectangle(bgBrush, 0, m_currentDivision*GetFont()->GetSize(), m_computedSize.Width, GetFont()->GetSize());

	/*static*/ LDraw::SolidBrush* textBrush = new LDraw::SolidBrush(LDraw::Color(0,0,0));

	float y = 0;
	for (int d = 0; d < pPattern->rows; d++)
	{
		float x = 0;

		//if ((y+GetFont()->GetSize()) > clipbox.Y && y < clipbox.GetBottom())
		{
			{
				char buf[4];
				sprintf_s(buf, "%2.2d", d);
				pGraphics->DrawString(buf, ~0, GetFont(), LDraw::PointF(x+0, y), textBrush);
			}

			for (int ch = 0; ch < m_p->m_pMusicModule->m_nchannels; ch++)
			{
				Note& note = pPattern->notes[ch][d];

				if (note.note)
				{
#if 0
					uint8 octave;

					if (note.period <= 107)
					{
						octave = 4;
					}
					else if (note.period <= 214)
					{
						octave = 3;
					}
					else if (note.period <= 428)
					{
						octave = 2;
					}
					else if (note.period <= 856)
					{
						octave = 1;
					}
					else
					{
						octave = 0;
					}
#endif

					cinstrument[ch] = note.instrument;

					if (note.note == 255)	// note off
					{
						pGraphics->DrawString(&note_off_str, GetFont(), LDraw::PointF(x+26, y), textBrush);
					}
					else
					{
						char buf[80];
						sprintf_s(buf, "%s", OctaveNotes[(note.note-1)%12]);
						pGraphics->DrawString(buf, ~0, GetFont(), LDraw::PointF(x+26, y), textBrush);

						int octave = (note.note-1)/12;
						sprintf_s(buf, "%d", octave);
						pGraphics->DrawString(buf, ~0, GetFont(), LDraw::PointF(x+40, y), textBrush);
					}

					{
						char buf[80];
						sprintf_s(buf, "%.2X", cinstrument[ch]);
						pGraphics->DrawString(buf, ~0, GetFont(), LDraw::PointF(x+50, y), textBrush);
					}
				}
				else
				{
					pGraphics->DrawString(&no_note_str, GetFont(), LDraw::PointF(x+50, y), textBrush);
				}

				{
					char buf[80];
					sprintf_s(buf, "%X%X%X", note.effect, (note.effectparms>>4), note.effectparms & 0xF);

					pGraphics->DrawString(buf, ~0, GetFont(), LDraw::PointF(x+70, y), textBrush);
				}

				x += 90;
			//	x += 120;
			}
		}

		y += GetFont()->GetSize();
	}
}

#if 0
void MusicModuleView::PatternView::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
#if 0
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
#endif
		}
	}
}
#endif

class WaveformViewControl : public Control, public IViewOf
{
public:
	WaveformView* m_pViewable;

	static const type_info& GetType()
	{
		return typeid(WaveformView);
	}

	virtual Object* get_Viewable()
	{
		return m_pViewable;
	}

	virtual void set_Viewable(Object* pViewable)
	{
	}

	WaveformViewControl(WaveformView* pViewable)
	{
		m_pViewable = pViewable;

		DockPanel* panel = new DockPanel;

		{
			ScrollBar* scrollbar = new ScrollBar(Orientation_Horizontal);
			ASSERT(0);
			//scrollbar->SetInfo(0.01, 20, 1);
			scrollbar->set_Value(1);
			panel->get_Children()->Add(scrollbar);
		}

		set_VisualTree(panel);
	}

#if 0
	virtual void handleEvent(System::Event* evt)
	{
		if (evt->get_eventPhase() != System::CAPTURING_PHASE)
		{
			if (*evt->get_type() == L"scroll")
			{
				evt->stopPropagation();
				SliderEvent* sliderEvt = dynamic_cast<SliderEvent*>(evt);
				m_pViewable->m_ctl->m_freq = sliderEvt->m_pos;
#if 0//WIN32
				m_pViewable->m_ctl->wo->GetDDSoundBuffer()->SetFrequency(m_pViewable->m_ctl->m_wave->m_wfx->nSamplesPerSec*m_pViewable->m_ctl->m_freq);
#else
				ASSERT(0);
#endif
			}
		}
	}
#endif
};

WaveformView::WaveformView()
{
}

void WaveformView::SetFile(FileObject* pFile)
{
	m_undoManager = new UndoManager;	// ??

	m_pFile = pFile;

	MediaShow::VOCLoader* loader = new MediaShow::VOCLoader;

//	LMedia::MPEGAudioSequence* loader = new LMedia::MPEGAudioSequence;

	FileByteStream* stream;
	TRY
	{
#if WIN32

		stream = new FileByteStream(m_pFile->m_Fullname);
		//stream = new FileByteStream("C:/files/sounds/voc/complete.voc");
//		stream = new FileByteStream("C:/movies/mpeg_audio2/music064.mp2");
#else
		stream = new FileByteStream("WinHD_C:/files/sounds/voc/complete.voc");
#endif
	}
	CATCH(Exception* e)
	{
		TRACE("Couldn't open file");
		std::printf("Couldn't open file");
		stream = NULL;
	}

	if (stream)
	{
		MSWindows::WAVEFORMATEX wfx;
		uint8* data;
		ULONG nsamples;

		if (true)
		{
			loader->Open(stream);
			loader->ReadFormatSignature();
			loader->ReadHeader();

			data = new uint8[loader->m_nSamples * loader->m_wfx.nBlockAlign];

			loader->ReadSamples(data, loader->m_nSamples);

			nsamples = loader->m_nSamples;
			wfx = loader->m_wfx;
		}
		else if (false)
		{
			loader->Open(stream);

#if 0
			uint8* data = new uint8[1152*2*2*100];

			for (int i = 0; i < 100; i++)
			{
				loader->frame((short*)(data + 1152*4*i));
				loader->seek_sync();
			}
#endif
		}
		else
		{
//				FileByteStream* stream = new FileByteStream("C:/files/mods/CloseToTheEdge.mod");

		}

		m_zoomer = new HorizontalZoomer;
		m_zoomer->m_factor = 0.05;

		Wave* wave = new Wave;

		wave->m_wfx = new MSWindows::WAVEFORMATEX;
		wave->m_wfx->wFormatTag = 1;
		wave->m_wfx->nChannels = 1;
		wave->m_wfx->wBitsPerSample = wfx.wBitsPerSample;
		wave->m_wfx->nBlockAlign = wfx.nBlockAlign;
		wave->m_wfx->nSamplesPerSec = wfx.nSamplesPerSec;
		wave->m_wfx->nAvgBytesPerSec = wfx.nAvgBytesPerSec;
		wave->m_wfx->cbSize = 0;
		wave->m_nsamples = nsamples;
		wave->m_data = data;

		m_ctl = new WaveformElement;
		m_ctl->m_scale = m_zoomer->m_factor;
		m_ctl->m_wave = wave;
		m_zoomer->set_Child(m_ctl);

		delete loader;

		m_pScroller = new ScrollViewer;
		{
			m_pScroller->set_Content(m_zoomer);
		}

		set_VisualTree(m_pScroller);
	}
}

#if 0
void WaveformView::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"contextmenu")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			CLXUIMenuElement* menu = new CLXUIMenuElement();
			menu->SetRParent(this);
			menu->SetOwnerWindow(GetOwnerWindow());

			{
				menu->AddItem(new TextString(WSTR("Undo")), 100);
				menu->AddItem(new TextString(WSTR("Redo")), 101);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Cut")), 102);
				menu->AddItem(new TextString(WSTR("Copy")), 103);
				menu->AddItem(new TextString(WSTR("Paste")), 104);
				menu->AddItem(new TextString(WSTR("Delete")), 105);
				menu->AddItem(new TextString(WSTR("Trim")), 106);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("View All")), 114);
				menu->AddItem(new TextString(WSTR("View Selection")), 115);
				menu->AddItem(new TextString(WSTR("Zoom In")), 116);
				menu->AddItem(new TextString(WSTR("Zoom Out")), 117);
				menu->AddItem(new TextString(WSTR("1:1")), 118);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Mute")), 120);
				menu->AddItem(new TextString(WSTR("Insert Silence")), 121);
				menu->AddItem(new TextString(WSTR("Reverse")), 122);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Play / Stop")), 130);
				menu->AddItem(new TextString(WSTR("Controls")), 131);
			}

			/*
			menu->AddSeparator();
			menu->AddItem(new TextString(OLESTR("Insert/Remove Breakpoint")), ID_DEBUG_TOGGLEBREAKPOINT);
			*/

			menu->GetMenuPopup()->Popup(menu, LDraw::PointI(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));

		}
		else if (*evt->get_type() == L"command")
		{
			CommandInvokeEvent* cmdEvt = dynamic_cast<CommandInvokeEvent*>(evt);

			int cmdID = cmdEvt->get_Command() - 100;

			if (cmdID == 0)
			{
				m_undoManager->UndoTo(NULL);
			}
			else if (cmdID == 1)
			{
				m_undoManager->RedoTo(NULL);
			}
			else if (cmdID == 2)	// Cut
			{
			}
			else if (cmdID == 3)	// Copy
			{
#if WIN32
				if (MSWindows::OpenClipboard(NULL))
				{
					HGlobalStream* stream = new HGlobalStream;
				//	stream->AddRef();

					Riff::CChunk ck;
					ck.m_id = mmioFOURCC('R', 'I', 'F', 'F');
					ck.m_grpid = mmioFOURCC('W', 'A', 'V', 'E');
					ck.Create(stream);
					{
						MSWindows::WAVEFORMATEX wfx = *m_ctl->m_wave->m_wfx;

						Riff::CChunk ck2;
						ck2.m_id = mmioFOURCC('f', 'm', 't', ' ');
						ck2.m_size = sizeof(wfx);
						ck2.Create(stream);
						stream->Write(&wfx, sizeof(wfx));
						ck2.Ascend(stream);
					}
					{
						uint8 nBlockAlign = m_ctl->m_wave->m_wfx->nBlockAlign;
					
						Riff::CChunk ck2;
						ck2.m_id = mmioFOURCC('d', 'a', 't', 'a');
						ck2.m_size = (m_ctl->GetMarkEnd()-m_ctl->GetMarkStart())*nBlockAlign;
						ck2.Create(stream);
						stream->Write(m_ctl->m_wave->m_data + m_ctl->GetMarkStart()*nBlockAlign, (m_ctl->GetMarkEnd()-m_ctl->GetMarkStart())*nBlockAlign);
						ck2.Ascend(stream);
					}

					ck.Ascend(stream);

					MSWindows::SetClipboardData(CF_WAVE, stream->Detach());

				//	stream->Release();
					delete stream;

					MSWindows::CloseClipboard();
				}
#else
				ASSERT(0);
#endif
			}
			else if (cmdID == 4)	// Paste
			{
				Wave* pWave = NULL;

#if WIN32
				if (MSWindows::OpenClipboard(NULL))
				{
					/*
					UINT format = 0;
					while (format = EnumClipboardFormats(format))
					{
						char name[512];
						GetClipboardFormatName(format, name, 512);

						TRACE("%d = %s\n", format, name);
					}
					*/

					HANDLE h = MSWindows::GetClipboardData(CF_WAVE);
					if (h)
					{
						void* p = MSWindows::GlobalLock(h);

						MemoryByteStream* stream = new MemoryByteStream(p, MSWindows::GlobalSize(h));
					//	stream->AddRef();

						Riff::CChunk ck;
						ck.Descend(stream);

						if (ck.m_id == mmioFOURCC('R','I','F','F'))
						{
							if (ck.m_grpid == mmioFOURCC('W','A','V','E'))
							{
								ReadWAVE(stream, ck, &pWave);
							}
							else
							;//	return;// E_FAIL;	// Unknown formtype
						}
						else
						;//	return;// E_FAIL;	// Not a RIFF file

					//	stream->Release();

						MSWindows::GlobalUnlock(h);
					}

					MSWindows::CloseClipboard();
				}
#else
				ASSERT(0);
#endif

				if (pWave)
				{
					InsertUndo* pUndo = new InsertUndo;
					pUndo->m_pEdit = this;
					pUndo->m_bRedo = true;
					pUndo->m_startCharPos = m_ctl->GetMarkStart();
					pUndo->m_text = pWave->m_data;
					pUndo->m_len = pWave->m_nsamples;//m_ctl->GetMarkEnd() - m_ctl->GetMarkStart();

					pUndo->Do(m_undoManager);
				}
			}
			else if (cmdID == 5)	// Delete
			{
				InsertUndo* pUndo = new InsertUndo;
				pUndo->m_pEdit = this;
				pUndo->m_startCharPos = m_ctl->GetMarkStart();
				pUndo->m_len = m_ctl->GetMarkEnd() - m_ctl->GetMarkStart();

				pUndo->Do(m_undoManager);
			}
			else if (cmdID == 6)	// Trim
			{
				TrimUndo* pUndo = new TrimUndo;
				pUndo->m_pEdit = this;
				pUndo->m_bRedo = true;
				pUndo->m_leftSamples = m_ctl->GetMarkStart();
				pUndo->m_rightSamples = m_ctl->m_wave->m_nsamples - m_ctl->GetMarkEnd();
				pUndo->Do(m_undoManager);
			}
			else if (cmdID == 20)	// Mute
			{
				MuteUndo* pUndo = new MuteUndo;
				pUndo->m_pEdit = this;
				pUndo->m_bRedo = true;
				pUndo->m_startCharPos = m_ctl->GetMarkStart();
				pUndo->m_len = m_ctl->GetMarkEnd() - m_ctl->GetMarkStart();
				pUndo->Do(m_undoManager);
			}
			else if (cmdID == 21)	// Insert Silence
			{
				InsertSilenceUndo* pUndo = new InsertSilenceUndo;
				pUndo->m_pEdit = this;
				pUndo->m_bRedo = true;
				pUndo->m_startCharPos = m_ctl->GetMarkStart();
				pUndo->m_len = m_ctl->m_wave->m_wfx->nSamplesPerSec;	// 1 second m_ctl->GetMarkEnd() - m_ctl->GetMarkStart();
				pUndo->Do(m_undoManager);
			}
			else if (cmdID == 22)	// Reverse
			{
				ReverseUndo* pUndo = new ReverseUndo;
				pUndo->m_pEdit = this;
				pUndo->m_bRedo = true;
				pUndo->m_startCharPos = m_ctl->GetMarkStart();
				pUndo->m_len = m_ctl->GetMarkEnd() - m_ctl->GetMarkStart();
				pUndo->Do(m_undoManager);
			}
			else if (cmdID == 14)	// View All
			{
				m_zoomer->m_bViewAll = true;
				m_zoomer->InvalidateMeasure();
				//m_zoomer->InvalidateArrange();
			}
			else if (cmdID == 15)	// View Selection
			{
				m_zoomer->m_bViewAll = false;

				LONGLONG length = m_ctl->GetMarkEnd() - m_ctl->GetMarkStart();
				ASSERT(0);
#if 0
				m_zoomer->m_factor = m_pScroller->get_InnerSize().Width / length;
#endif

				m_pScroller->MakeVisible(LDraw::RectD(m_ctl->GetMarkStart()*m_zoomer->m_factor, 0, length*m_zoomer->m_factor, 0));

				m_zoomer->InvalidateMeasure();
			}
			else if (cmdID == 18)	// View 1:1
			{
				m_zoomer->m_bViewAll = false;
				m_zoomer->m_factor = 1;
				m_zoomer->InvalidateMeasure();
			}
			else if (cmdID == 30)	// Play / Stop
			{
				m_ctl->Stop();
			}
			else if (cmdID == 31)	// Controls
			{
				WaveformViewControl* ctl = new WaveformViewControl(this);
			//	ctl->m_pCanvas = m_pCanvas;
				IViewOf* pView = ctl;

				ASSERT(0);
#if 0
				m_views.push_back(pView);
#endif

				ChildWindow* pWindow = new ChildWindow;
				pWindow->set_Width(200);
				pWindow->set_Height(200);

				/*
				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->put_Content(dynamic_cast<Control*>(pView));
				}
				*/

				pWindow->set_Content(dynamic_cast<Control*>(pView));
				//	pWindow->put_Content(m_callStackWnd);

				pWindow->set_Title(WSTR("Test"));

		//	IVisualParent* pParent = GetRParent();
				m_pCanvas->AddChild(pWindow);
			}
		}
	}
}
#endif

System::StringW* WaveformView::TrimUndo::GetDescription()
{
	return WSTR("Trim");
}

void WaveformView::TrimUndo::Do(IUndoManager* pUndoManager)
{
	uint8 nBlockAlign = m_pEdit->m_ctl->m_wave->m_wfx->nBlockAlign;

	if (m_bRedo)
	{
		m_pEdit->m_ctl->m_wave->m_data += m_leftSamples*nBlockAlign;
		m_pEdit->m_ctl->m_wave->m_nsamples -= m_rightSamples+m_leftSamples;
		m_pEdit->m_ctl->SetMarkStart(0);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->m_wave->m_nsamples);

		/*
	// Reinsert the text
	//	m_pEdit->InsertText(m_startCharPos, m_text, m_len);
		uint8* data = new uint8[(m_pEdit->m_ctl->m_nsamples + m_len)*nBlockAlign];
		memcpy(data, m_pEdit->m_ctl->m_data, m_startCharPos*nBlockAlign);
		memcpy(data + m_startCharPos*nBlockAlign, m_text, m_len*nBlockAlign);
		memcpy(data + (m_startCharPos+m_len)*nBlockAlign, m_pEdit->m_ctl->m_data + m_startCharPos*nBlockAlign, (m_pEdit->m_ctl->m_nsamples - m_startCharPos)*nBlockAlign);

		delete[] m_pEdit->m_ctl->m_data;
		m_pEdit->m_ctl->m_data = data;
		m_pEdit->m_ctl->m_nsamples += m_len;

	// Free the text
		delete m_text;
		m_text = NULL;

	//	m_pEdit->LocateCursor(m_startCharPos + m_len);
		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart()+m_len);
		*/
	}
	else	// Undo
	{
		m_pEdit->m_ctl->m_wave->m_data -= m_leftSamples*nBlockAlign;
		m_pEdit->m_ctl->m_wave->m_nsamples += m_rightSamples+m_leftSamples;
		m_pEdit->m_ctl->SetMarkStart(m_leftSamples);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->m_wave->m_nsamples - m_rightSamples);

#if 0
	// Remember the text
		ASSERT(m_text == NULL);
		m_text = new uint8[m_len*nBlockAlign];
		memcpy(m_text, m_pEdit->m_ctl->m_data + m_startCharPos*nBlockAlign, m_len*nBlockAlign);

		/*
		m_text = new OLECHAR[m_len];
		memcpy(m_text, m_pEdit->get_TextData() + m_startCharPos, m_len*sizeof(OLECHAR));
*/
	// Delete the text
	//	m_pEdit->DeleteText(m_startCharPos, m_len);
		uint8* data = new uint8[(m_pEdit->m_ctl->m_nsamples - m_len)*nBlockAlign];
		memcpy(data, m_pEdit->m_ctl->m_data, m_startCharPos*nBlockAlign);
		memcpy(data + m_startCharPos*nBlockAlign, m_pEdit->m_ctl->m_data + (m_startCharPos + m_len)*nBlockAlign, (m_pEdit->m_ctl->m_nsamples - m_startCharPos - m_len)*nBlockAlign);

		delete[] m_pEdit->m_ctl->m_data;
		m_pEdit->m_ctl->m_data = data;
		m_pEdit->m_ctl->m_nsamples -= m_len;

		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart());
		/*
		m_pEdit->LocateCursor(m_startCharPos);
		*/
#endif
	}

	m_pEdit->m_ctl->InvalidateMeasure();

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
}

System::StringW* WaveformView::InsertSilenceUndo::GetDescription()
{
	return WSTR("Insert Silence");
}

void WaveformView::InsertSilenceUndo::Do(IUndoManager* pUndoManager)
{
	uint8 nBlockAlign = m_pEdit->m_ctl->m_wave->m_wfx->nBlockAlign;

	if (m_bRedo)
	{
		/*
		m_pEdit->m_ctl->m_data += m_leftSamples*nBlockAlign;
		m_pEdit->m_ctl->m_nsamples -= m_rightSamples+m_leftSamples;
		m_pEdit->m_ctl->SetMarkStart(0);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->m_nsamples);
		*/

	// Reinsert silence
	//	m_pEdit->InsertText(m_startCharPos, m_text, m_len);
		uint8* data = new uint8[(m_pEdit->m_ctl->m_wave->m_nsamples + m_len)*nBlockAlign];
		std::memcpy(data, m_pEdit->m_ctl->m_wave->m_data, m_startCharPos*nBlockAlign);
		if (m_pEdit->m_ctl->m_wave->m_wfx->wBitsPerSample == 8)	// unsigned 8-bit
		{
			std::memset(data + m_startCharPos*nBlockAlign, 128, m_len*nBlockAlign);
		}
		else if (m_pEdit->m_ctl->m_wave->m_wfx->wBitsPerSample == 16)	// signed 16-bit
		{
			std::memset(data + m_startCharPos*nBlockAlign, 0, m_len*nBlockAlign);
		}

		std::memcpy(data + (m_startCharPos+m_len)*nBlockAlign, m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign, (m_pEdit->m_ctl->m_wave->m_nsamples - m_startCharPos)*nBlockAlign);

		delete[] m_pEdit->m_ctl->m_wave->m_data;
		m_pEdit->m_ctl->m_wave->m_data = data;
		m_pEdit->m_ctl->m_wave->m_nsamples += m_len;

	// Free the text
	//	delete m_text;
	//	m_text = NULL;

	//	m_pEdit->LocateCursor(m_startCharPos + m_len);
		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart()+m_len);
	}
	else	// Undo
	{

		/*
	// Remember the text
		ASSERT(m_text == NULL);
		m_text = new uint8[m_len*nBlockAlign];
		memcpy(m_text, m_pEdit->m_ctl->m_data + m_startCharPos*nBlockAlign, m_len*nBlockAlign);

		/*
		m_text = new OLECHAR[m_len];
		memcpy(m_text, m_pEdit->get_TextData() + m_startCharPos, m_len*sizeof(OLECHAR));
*/
	// Delete the text
	//	m_pEdit->DeleteText(m_startCharPos, m_len);
		uint8* data = new uint8[(m_pEdit->m_ctl->m_wave->m_nsamples - m_len)*nBlockAlign];
		std::memcpy(data, m_pEdit->m_ctl->m_wave->m_data, m_startCharPos*nBlockAlign);
		std::memcpy(data + m_startCharPos*nBlockAlign, m_pEdit->m_ctl->m_wave->m_data + (m_startCharPos + m_len)*nBlockAlign, (m_pEdit->m_ctl->m_wave->m_nsamples - m_startCharPos - m_len)*nBlockAlign);

		delete[] m_pEdit->m_ctl->m_wave->m_data;
		m_pEdit->m_ctl->m_wave->m_data = data;
		m_pEdit->m_ctl->m_wave->m_nsamples -= m_len;

		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart());
		/*
		m_pEdit->LocateCursor(m_startCharPos);
		*/
	}

	m_pEdit->m_ctl->InvalidateMeasure();

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
}

System::StringW* WaveformView::MuteUndo::GetDescription()
{
	return WSTR("Mute");
}

void WaveformView::MuteUndo::Do(IUndoManager* pUndoManager)
{
	uint8 nBlockAlign = m_pEdit->m_ctl->m_wave->m_wfx->nBlockAlign;

	if (m_bRedo)
	{
	// Remember the text
		ASSERT(m_text == NULL);
		m_text = new uint8[m_len*nBlockAlign];
		std::memcpy(m_text, m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign, m_len*nBlockAlign);

		// Mute
		if (m_pEdit->m_ctl->m_wave->m_wfx->wBitsPerSample == 8)	// unsigned 8-bit
		{
			std::memset(m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign, 128, m_len*nBlockAlign);
		}
		else if (m_pEdit->m_ctl->m_wave->m_wfx->wBitsPerSample == 16)	// signed 16-bit
		{
			std::memset(m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign, 0, m_len*nBlockAlign);
		}

		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart() + m_len);
	}
	else	// Undo
	{
		// Restore the data
		std::memcpy(m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign, m_text, m_len*nBlockAlign);

	// Free the text
		delete m_text;
		m_text = NULL;

		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart() + m_len);
	}

	m_pEdit->m_ctl->InvalidateMeasure();

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
}

System::StringW* WaveformView::InsertUndo::GetDescription()
{
	return WSTR("Undo");
}

void WaveformView::InsertUndo::Do(IUndoManager* pUndoManager)
{
	uint8 nBlockAlign = m_pEdit->m_ctl->m_wave->m_wfx->nBlockAlign;

	if (m_bRedo)
	{
	// Reinsert the text
	//	m_pEdit->InsertText(m_startCharPos, m_text, m_len);
		uint8* data = new uint8[(m_pEdit->m_ctl->m_wave->m_nsamples + m_len)*nBlockAlign];
		std::memcpy(data, m_pEdit->m_ctl->m_wave->m_data, m_startCharPos*nBlockAlign);
		std::memcpy(data + m_startCharPos*nBlockAlign, m_text, m_len*nBlockAlign);
		std::memcpy(data + (m_startCharPos+m_len)*nBlockAlign, m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign, (m_pEdit->m_ctl->m_wave->m_nsamples - m_startCharPos)*nBlockAlign);

		delete[] m_pEdit->m_ctl->m_wave->m_data;
		m_pEdit->m_ctl->m_wave->m_data = data;
		m_pEdit->m_ctl->m_wave->m_nsamples += m_len;

	// Free the text
		delete m_text;
		m_text = NULL;

	//	m_pEdit->LocateCursor(m_startCharPos + m_len);
		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart()+m_len);
	}
	else	// Undo
	{
	// Remember the text
		ASSERT(m_text == NULL);
		m_text = new uint8[m_len*nBlockAlign];
		std::memcpy(m_text, m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign, m_len*nBlockAlign);

		/*
		m_text = new OLECHAR[m_len];
		memcpy(m_text, m_pEdit->get_TextData() + m_startCharPos, m_len*sizeof(OLECHAR));
*/
	// Delete the text
	//	m_pEdit->DeleteText(m_startCharPos, m_len);
		uint8* data = new uint8[(m_pEdit->m_ctl->m_wave->m_nsamples - m_len)*nBlockAlign];
		std::memcpy(data, m_pEdit->m_ctl->m_wave->m_data, m_startCharPos*nBlockAlign);
		std::memcpy(data + m_startCharPos*nBlockAlign, m_pEdit->m_ctl->m_wave->m_data + (m_startCharPos + m_len)*nBlockAlign, (m_pEdit->m_ctl->m_wave->m_nsamples - m_startCharPos - m_len)*nBlockAlign);

		delete[] m_pEdit->m_ctl->m_wave->m_data;
		m_pEdit->m_ctl->m_wave->m_data = data;
		m_pEdit->m_ctl->m_wave->m_nsamples -= m_len;

		m_pEdit->m_ctl->SetMarkStart(m_startCharPos);
		m_pEdit->m_ctl->SetMarkEnd(m_pEdit->m_ctl->GetMarkStart());
		/*
		m_pEdit->LocateCursor(m_startCharPos);
		*/
	}

	m_pEdit->m_ctl->InvalidateMeasure();

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
}

System::StringW* WaveformView::ReverseUndo::GetDescription()
{
	return WSTR("Reverse");
}

void WaveformView::ReverseUndo::Do(IUndoManager* pUndoManager)
{
	uint8 nBlockAlign = m_pEdit->m_ctl->m_wave->m_wfx->nBlockAlign;

	if (m_pEdit->m_ctl->m_wave->m_wfx->wBitsPerSample == 8)	// unsigned 8-bit
	{
		uint8* data = m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign;

		ULONG hlen = m_len/2;

		for (int i = 0; i < hlen; i++)
		{
			data[i] ^= data[m_len-i-1];
			data[m_len-i-1] ^= data[i];
			data[i] ^= data[m_len-i-1];
		}
	}
	else if (m_pEdit->m_ctl->m_wave->m_wfx->wBitsPerSample == 16)	// signed 16-bit
	{
		short* data = (short*)(m_pEdit->m_ctl->m_wave->m_data + m_startCharPos*nBlockAlign);

		ULONG hlen = m_len/2;

		for (int i = 0; i < hlen; i++)
		{
			data[i] ^= data[m_len-i-1];
			data[m_len-i-1] ^= data[i];
			data[i] ^= data[m_len-i-1];
		}
	}

	m_pEdit->m_ctl->Invalidate();

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
}

void InstrumentsView::OnRender(Graphics* pGraphics)
{
	int y = 0;

	LDraw::SolidBrush* textBrush = new LDraw::SolidBrush(LDraw::Color(0,0,0));

	for (int i = 0; i < m_p->m_pMusicModule->m_instruments.size(); i++)
	{
		Instrument* instrument = m_p->m_pMusicModule->m_instruments[i];

		char buf[16];
		sprintf_s(buf, "%d", i+1);
	//	pGraphics->DrawString(new StringA(string_copy(buf)), GetFont(), LDraw::PointF(0, y), textBrush);
		pGraphics->DrawString(buf, ~0, GetFont(), LDraw::PointF(0, y), textBrush);

		pGraphics->DrawString(instrument->name, ~0, GetFont(), LDraw::PointF(80, y), textBrush);

		if (instrument->samples.size())
		{
			if (instrument->samples[0]->sampleLength)
			{
				sprintf_s(buf, "%d", instrument->samples[0]->sampleLength);
				double width = pGraphics->MeasureString(buf, std::strlen(buf), GetFont());
				pGraphics->DrawString(buf, ~0, GetFont(), LDraw::PointF(72-width, y), textBrush);
			}
		}

		y += GetFont()->GetSize();
	}
}

void InstrumentsView::OnMouseDown(MouseButtonEventArgs* args)
{
//	MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);
	Point point = args->GetPosition(this);//ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

	int index = point.Y / GetFont()->GetSize();

	Wave* wave = new Wave;
	wave->m_wfx = new MSWindows::WAVEFORMATEX;
	wave->m_wfx->wFormatTag = 1;
	wave->m_wfx->wBitsPerSample = 8;
	wave->m_wfx->nChannels = 1;
	wave->m_wfx->nBlockAlign = 1;
	wave->m_wfx->nSamplesPerSec = 6000;
	wave->m_wfx->nAvgBytesPerSec = wave->m_wfx->nSamplesPerSec * wave->m_wfx->nBlockAlign;
	wave->m_wfx->cbSize = 0;
	wave->m_nsamples = m_p->m_pMusicModule->m_instruments[index]->samples[0]->sampleLength;
	wave->m_data = m_p->m_pMusicModule->m_instruments[index]->samples[0]->data;

	WaveformView* pView = new WaveformView(wave);
	pView->m_pCanvas = m_p->m_pCanvas;

	Window* pWindow = new Window;
	pWindow->set_Width(500);
	pWindow->set_Height(200);

	pWindow->set_Content(pView);
	pWindow->set_Title(WSTR("Test"));
//	m_p->m_pCanvas->AddChild(pWindow);
	pWindow->Show();
}

WaveformView::WaveformView(Wave* wave)
{
	if (true)
	{
		m_ctl = new WaveformElement;
		m_ctl->m_scale = 1;//m_zoomer->m_factor;
		m_ctl->m_wave = wave;

		m_pScroller = new ScrollViewer;
		{
			m_pScroller->set_Content(m_ctl);
		}

		set_VisualTree(m_pScroller);
	}
	else
	{
		m_zoomer = new HorizontalZoomer;
		m_zoomer->m_factor = 0.05;

		m_ctl = new WaveformElement;
		m_ctl->m_scale = m_zoomer->m_factor;
		m_ctl->m_wave = wave;
		m_zoomer->set_Child(m_ctl);

		m_pScroller = new ScrollViewer;
		{
			m_pScroller->set_Content(m_zoomer);
		}

		set_VisualTree(m_pScroller);
	}
}

}
