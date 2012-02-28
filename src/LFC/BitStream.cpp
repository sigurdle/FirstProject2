#include "stdafx.h"
#include "LFC.h"
#include "BitStream.h"

namespace System
{
namespace IO
{

CByteStream::CByteStream(Stream* byteStream) :
	m_refcount(0),
	m_byteStream(byteStream)
{
	m_bytepos = m_byteStream->GetPosition();
	m_nstacked = 0;
}

ULONG CByteStream::AddRef()
{
	++m_refcount;
	return m_refcount;
}

ULONG CByteStream::Release()
{
	ASSERT(m_refcount > 0);
	--m_refcount;
	if (m_refcount == 0)
	{
		delete this;
		return 0;
	}
	return m_refcount;
}

int CByteStream::getbyte(uint32* p)
{
	if (m_nstacked > 0)
	{
		m_nstacked--;
		*p = BigEndian32(m_oldc[(m_bytepos++) & 0x1FFF]);
		return 0;
	}

	// Buffer less than buffer size (allows some space left for seeking backwards a few bytes),
	// and don't overflow the buffer
	int cb = MIN(0x1000, 0x2000-(m_bytepos & 0x1FFF));

	size_t nRead = m_byteStream->Read(&m_oldc[m_bytepos & 0x1FFF], cb<<2) >> 2;
//	m_oldc[m_bytepos & 0x1FFF] = BigEndian32(m_oldc[m_bytepos & 0x1FFF]);
	if (nRead == 0)
		return -1;
	m_nstacked = nRead-1;

	*p = BigEndian32(m_oldc[(m_bytepos++) & 0x1FFF]);
	return 0;
}

LONGLONG CByteStream::Seek(LONGLONG move, ULONG origin)
{
	LONGLONG abs;
	switch (origin)
	{
	case System::IO::STREAM_SEEK_SET:
		abs = move;
		break;

	case System::IO::STREAM_SEEK_END:
		ASSERT(0);
		break;

	case System::IO::STREAM_SEEK_CUR:
		abs = m_bytepos + move;
		break;

	default:
		raise(ArgumentException());
	}

	if (abs >= m_bytepos)
	{
		if (abs < m_bytepos+m_nstacked)
		{
			m_nstacked = m_bytepos+m_nstacked - abs;
			m_bytepos = abs;
		}
		else
		{
			m_bytepos = m_byteStream->Seek(abs<<2, System::IO::STREAM_SEEK_SET) >> 2;
			m_nstacked = 0;	// reset this
		}
	}
	else
	{
		m_bytepos = m_byteStream->Seek(abs<<2, System::IO::STREAM_SEEK_SET) >> 2;
		m_nstacked = 0;	// reset this
	}

	return m_bytepos;
}

CBitStream32::CBitStream32(CByteStream* byteStream) : m_byteStream(byteStream)
{
	m_bitcnt = 0;
	m_countBits = 0;
	m_bitstreamSize = 0;
}

CBitStream32::~CBitStream32()
{
}

bool CBitStream32::getbit()
{
	if (m_bitcnt == 0)
	{
		m_curbyte = getbyte();
		m_bitcnt = 32;
	}

	--m_bitcnt;

	bool bit = (m_curbyte >> (m_bitcnt)) & 0x1;

	++m_countBits;

	return bit;
}

int CBitStream32::getnbits(int nbits)
{
	ASSERT(nbits <= 32);

	m_countBits += nbits;

	int value = 0;

	// Finish the current byte
	if (m_bitcnt > 0)
	{
		int n = MIN(nbits, m_bitcnt);
		value = (m_curbyte>>(m_bitcnt-n)) & ((1<<n)-1);
		nbits -= n;
		m_bitcnt -= n;
	}

	while (nbits)
	{
		m_bitcnt = 32;
		int n = MIN(nbits, 32);
		m_curbyte = getbyte();
		value <<= n;
		value |= (m_curbyte>>(32-n)) & ((1<<n)-1);
		nbits -= n;
		m_bitcnt -= n;
	}
	ASSERT(m_bitcnt >= 0 && m_bitcnt < 32);

	return value;
}

void CBitStream32::ungetbits(int nbits)
{
	ASSERT(nbits >= 0);

	m_countBits -= nbits;

	if (nbits < 32-m_bitcnt)
	{
		m_bitcnt += nbits;
		ASSERT(m_bitcnt < 32);
	}
	else
	{
	// first back up current byte
		nbits -= 32-m_bitcnt;
		m_bitcnt = 32;

		while (nbits)
		{
			m_bitcnt = 0;
			int n = MIN(nbits, 32);
			ungetbyte();
			m_curbyte = BigEndian32(m_byteStream->m_oldc[(m_byteStream->m_bytepos-1) & 0x1FFF]);
			nbits -= n;
			m_bitcnt += n;
		}

		if (m_bitcnt == 32)
		{
			m_bitcnt = 0;
			ungetbyte();
			m_curbyte = BigEndian32(m_byteStream->m_oldc[(m_byteStream->m_bytepos-1) & 0x1FFF]);
		}
	}
}

int CBitStream32::looknbits(int nbits)
{
	ASSERT(nbits <= 32);

	int value = 0;

	// Finish the current byte
	if (m_bitcnt > 0)
	{
		int n = MIN(nbits, m_bitcnt);
		value = (m_curbyte>>(m_bitcnt-n)) & ((1<<n)-1);
		nbits -= n;
	}

	int nbytes = 0;
	while (nbits)
	{
		int n = MIN(nbits, 32);
		uint32 curbyte;
		int f = m_byteStream->getbyte(&curbyte);
		value <<= n;

		if (f != -1)
		{
			value |= (curbyte>>(32-n)) & ((1<<n)-1);
			nbytes++;
		}
		/*
		else
		{
			ungetbytes(nbytes);
			return value;
		}
		*/

		nbits -= n;
	}

	ungetbytes(nbytes);

	return value;
}

bool CBitStream32::checknbits_zero(int nbits)
{
	// Finish the current byte
	if (m_bitcnt > 0)
	{
		int n = MIN(nbits, m_bitcnt);
		if ((m_curbyte>>(m_bitcnt-n)) & ((1<<n)-1))
			return false;
		nbits -= n;
	}

	int nbytes = 0;
	while (nbits)
	{
		int n = MIN(nbits, 32);
		uint32 curbyte = getbyte();
		nbytes++;
		if ((curbyte>>(32-n)) & ((1<<n)-1))
		{
			ungetbytes(nbytes);
			return false;
		}
		nbits -= n;
	}

	ungetbytes(nbytes);

	return true;
}

void CBitStream32::skipnbits(int nbits)
{
	m_countBits += nbits;

	if (m_bitcnt >= nbits)
	{
		m_bitcnt -= nbits;
	}
	else
	{
		if (m_bitcnt > 0)
		{
			nbits -= m_bitcnt;
			m_bitcnt = 0;
		}

		while (nbits)
		{
			ASSERT(m_bitcnt == 0);
			m_bitcnt = 32;
			int n = MIN(nbits, 32);
			m_curbyte = getbyte();
			m_bitcnt -= n;
			nbits -= n;
		}
	}
}

void CBitStream32::SetBytePos(ULONGLONG pos)
{
	m_bitcnt = 0;
	m_byteStream->Seek(pos >> 2, System::IO::STREAM_SEEK_SET);
	skipnbits((pos & 3) << 3);
}

GetByteStream::GetByteStream(Stream* byteStream) : m_byteStream(byteStream)
{
}

}	// IO
}	// System
