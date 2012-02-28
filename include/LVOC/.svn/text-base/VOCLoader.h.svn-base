#ifndef __VOCLOADER_H_
#define __VOCLOADER_H_

#ifndef VOCEXT
#define VOCEXT DECLSPEC_DLLIMPORT
#endif

#include "vocfmt.h"

namespace System
{
namespace MediaShow
{

interface IWaveReader
{
	virtual size_t ReadSamples(ubyte* dest, size_t nSamples) = 0;
};

class VOCEXT VOCLoader : public Object, public IWaveReader
{
public:

	CTOR VOCLoader();
	~VOCLoader();

	virtual void Open(IO::Stream* stream);
	virtual ErrorCode ReadFormatSignature();
	virtual ErrorCode_Bool ReadHeader();
	virtual size_t ReadSamples(ubyte* dest, size_t nSamples) override;

	VOCHEADER m_hdr;
	uint32 m_nSamples;
	uint32 m_nPos;
	WAVEFORMATEX m_wfx;
	int m_compression;

protected:

	_Ptr<IO::Stream> m_stream;
};

}	// Media
}	// System

#endif // __VOCLOADER_H_
