#include "stdafx.h"
#include "ZLIBDeflate.h"
#include "ZLIBDecoder.h"

namespace System
{
using namespace IO;

ZLIBEncoder::ZLIBEncoder()
{
	m_pos = 0;
	m_totalSize = 0;

	m_n = 0;
}

ZLIBEncoder::~ZLIBEncoder()
{
}

size_t ZLIBEncoder::Write(const void* pv, size_t cb)
{
	for (size_t i = 0; i < cb; ++i)
	{
		m_n += 1;

		while (m_n >= 3)	// process next 3 bytes
		{
			m_n -= 3;
		}
	}
	return 0;
}

uint64 ZLIBEncoder::Seek(int64 offset, SeekOrigin origin)
{
	return m_pos;
}

uint64 ZLIBEncoder::GetSize()
{
	return m_totalSize;
}

/*
ISequentialByteStream* ZLIBEncoder::Clone() const
{
	return NULL;
}
*/

}	// System
