#ifndef IFF_h
#define IFF_h

#include "LMedia/LMedia.h"	// TODO, split up

#ifndef IFFEXT
#define IFFEXT DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace MediaShow
{

class CAudioChunk
{
public:
	CAudioChunk()
	{
		m_soundDataOffset = 0;
		m_soundDataLength = 0;
		m_nSamples = 0;
	}

	ULONGLONG m_soundDataOffset;
	ULONG m_soundDataLength;
	ULONG m_nSamples;
};

}	// MediaShow
}

#endif	// IFF_h
