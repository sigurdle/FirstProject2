#pragma once

#include "IFFParser.h"

namespace System
{
namespace MediaShow
{

class CIFFILBM : public Object
{
public:

	CTOR CIFFILBM()
	{
		m_pIFFParser = NULL;

		m_numCrng = 0;
		m_camg = 0;
		memset(&m_bmhd, 0, sizeof(m_bmhd));
		memset(m_planes0, 0, 4*33);
	}

	IFFParser* m_pIFFParser;

	BitMapHeader		m_bmhd;
	ColorRange			m_crng[8];
	uint16				m_numCrng;
	uint32					m_camg;	// Amiga display modes
	ColorRegister		m_colors[256];
	int					m_numcolors;

	uint	m_planeSize;
	uint8* m_planes0[33];

	IFFRESULT ReadBODY(ULONG ckSize);

	IFFRESULT BMHDChunk(IFFCHUNK* ck);
	IFFRESULT CAMGChunk(IFFCHUNK* ck);
	IFFRESULT CMAPChunk(IFFCHUNK* ck);
	IFFRESULT BODYChunk(IFFCHUNK* ck);

	void PlanarToChunky(uint8 **planes, IMediaSample* sample);
};

class CAnimFrame : public Object
{
public:
	CTOR CAnimFrame()
	{
		memset(&m_anhd, 0, sizeof(m_anhd));

		fileOffset = 0;	// Unused?

		m_cmapPos = 0;
		m_cmapSize = 0;

		m_bodyPos = 0;
		m_bodySize = 0;

		m_dltaPos = 0;
		m_dltaSize = 0;
	}

	LONGLONG m_timeStart;
	LONGLONG m_timeDur;

	AnimationHeader m_anhd;

	ULONG fileOffset;	// Unused?

	ULONG m_cmapPos;
	ULONG m_cmapSize;

	ULONG m_bodyPos;
	ULONG m_bodySize;

	ULONG m_dltaPos;
	ULONG m_dltaSize;

	list<CAudioChunk*> m_audioChunks;
};

class SEQDATA
{
public:

	CTOR SEQDATA();

	uint8* m_planes1[33];
	uint8** m_cPlanes;
	uint8** m_cPlanes2;
	int m_currentFrame;
};

/*
class IFFAnimAudio
{
public:

	CTOR IFFAnimAudio();

};
*/
class IFFANIM : public CIFFILBM, public SEQDATA
{
public:

	void Init();
	void InitAudio();

	IFFRESULT ReadILBMForm(CAnimFrame* f, bool bInitRead);

	ErrorCode SeekFrame(int frame);
	IFFRESULT ReadDLTA(CAnimFrame* f, uint32 ckSize);
	ErrorCode ReadFrameData(CAnimFrame* f);

	list<CAnimFrame*> m_frameList;

//	IFFAnimAudio* m_pAudio;

	AnimSoundHeader m_sxhd;
	uint16 m_nChannels;
	uint16 m_nBlockAlign;

	ULONG m_nSamples;

	list<CAudioChunk*> m_audioChunks;

	//SEQDATA* m_seqdata;
};

}	// MediaShow
}	// System
