#include "stdafx.h"
#include "ZLIBDeflate.h"

namespace System
{
namespace IO
{

ZLIBDecoder::ZLIBDecoder() : m_inflate(NULL)
{
}

ZLIBDecoder::ZLIBDecoder(IO::Stream* byteStream, uint64 totalSize/* = ~0*/)
{
	m_inflate = NULL;
	start(byteStream);
}

ZLIBDecoder::~ZLIBDecoder()
{
}

void ZLIBDecoder::start(IO::Stream* byteStream)
{
	uint8 cmf;
	byteStream->Read(&cmf, 1);

	uint8 flg;
	byteStream->Read(&flg, 1);

	uint8 compressionMethod = cmf & 0xf;
	uint8 compressionInfo = cmf >> 4;
	//uint8 fcheck = flg & 0xf;
	uint8 fdict = (flg >> 5) & 1;
	uint8 flevel = (flg >> 6);

	// cmf*256 + flg should be a multiple of 31
	if ((cmf*256 + flg) % 31)
	{
		raise(ZLIBException(L"Unknown compression method"));
	}

	if (fdict)
	{
		ASSERT(0);
	}

	if (compressionMethod == 8)
	{
		m_inflate = new Inflate(byteStream, compressionInfo);
	}
	else
	{
		raise(ZLIBException(L"Unknown compression method"));
	}
}

size_t ZLIBDecoder::Read(void* pv, size_t cb)
{
	return m_inflate->Read(pv, cb);
}

uint64 ZLIBDecoder::Seek(int64 offset, SeekOrigin origin)
{
	return m_inflate->Seek(offset, origin);
}

uint64 ZLIBDecoder::GetPosition()
{
	return m_inflate->GetPosition();
}

size_t ZLIBDecoder::Write(const void* pv, size_t cb)
{
	raise(ZLIBException("Readonly stream"));
	ASSERT(0);
	return 0;
}

uint64 ZLIBDecoder::GetSize()
{
	if (m_totalSize == ~0)
	{
		raise(ZLIBException("Unknown size"));
		ASSERT(0);
	}

	return m_totalSize;
}

ZLIBDecoder* ZLIBDecoder::CloneStream()
{
	raise(ZLIBException("ZLIBDecoder::Clone not implemented"));
	return NULL;
}

}	// IO
}	// System
