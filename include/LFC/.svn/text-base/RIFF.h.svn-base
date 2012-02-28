#ifndef __RIFF_h__
#define __RIFF_h__

#ifndef RIFFExt
#define RIFFExt DECLSPEC_DLLIMPORT
#endif

#ifdef __LERSTAD__
#define MAKEFOURCC(ch0, ch1, ch2, ch3) ((uint32)(uint8)(ch0) | ((uint32)(uint8)(ch1) << 8) | ((uint32)(uint8)(ch2) << 16) | ((uint32)(uint8)(ch3) << 24 ))
#endif

/* MMIO macros */
#define mmioFOURCC(ch0, ch1, ch2, ch3)  MAKEFOURCC(ch0, ch1, ch2, ch3)

namespace System
{
namespace Riff
{

class RIFFExt CChunk
{
public:
	CTOR CChunk();

	int Create(IO::Stream& stream);
	int Descend(IO::Stream& stream);
	int Ascend(IO::Stream& stream);

	uint32 m_id;
	uint32 m_size;
	uint32 m_grpid;
	uint32 m_dwFlags;
	LONGLONG m_pos;
};

}	// Riff
}

#endif // __RIFF_h__
