#include "stdafx.h"
#include "HGlobalStream.h"

#include "../include/windows_header.h"

namespace System
{

HGlobalStream::HGlobalStream()
{
	m_hGlobal = MSWindows::GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, 0);
	m_pos = 0;
	m_size = 0;
}

HGlobalStream::HGlobalStream(HGLOBAL hGlobal)
{
	m_hGlobal = hGlobal;
	m_pos = 0;
	m_size = 0;
}

HGlobalStream::~HGlobalStream()
{
	if (m_hGlobal)
	{
		MSWindows::GlobalFree(m_hGlobal);
	}
}

void* HGlobalStream::GetData()
{
	return MSWindows::GlobalLock(m_hGlobal);
}

ULONG HGlobalStream::Write(const void* pv, ULONG cb)
{
	if (m_hGlobal == NULL)
	{
		THROW(-1);
	}

	if (m_pos < 0)
	{
		THROW(-1);
	}

	if (m_pos + cb > MSWindows::GlobalSize(m_hGlobal))
	{
		m_hGlobal = MSWindows::GlobalReAlloc(m_hGlobal, (m_pos + cb + 511) & ~511, 0);
	}
	
	uint8* p = (uint8*)MSWindows::GlobalLock(m_hGlobal);
	if (p)
	{
		std::memcpy(p + m_pos, pv, cb);
		m_size = MAX(m_size, m_pos + cb);

		MSWindows::GlobalUnlock(m_hGlobal);

		m_pos += cb;
		return cb;
	}
	else
		return 0;
}

}
