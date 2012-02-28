#ifndef __MPEGBitStream_h__
#define __MPEGBitStream_h__

namespace System
{
namespace MediaShow
{

class BitStreamEx : public IO::CBitStream32
{
public:
	CTOR BitStreamEx(IO::CByteStream* byteStream) : IO::CBitStream32(byteStream)
	{
	}

	int next_start_code()
	{
		// Make it byte-aligned
		if (getnbits(m_bitcnt & 7) != 0)
		{
			TRACE("warning %s(%d)\n", __FILE__, __LINE__);
		//	THROW(-1);
		}

		int n24;
		while ((n24 = looknbits(24)) != 0x1)
		{
			//ungetbits(24);
			int byteval = getnbits(8);
			if (byteval != 0)
			{
				TRACE("warning %s(%d)\n", __FILE__, __LINE__);
			//	THROW(-1);
			}
		}

		getnbits(24);
		ASSERT(n24 == 0x1);
		m_next_code = 0x100 | getnbits(8);

		return m_next_code;
	}

	int m_next_code;

	/*
	int getvariablebits(vtab2 table[], int maxlen = 32)
	{
		int len = 0;
		int value = 0;
		vtab2* p = table;

		ASSERT(p->len);

		do
		{
			value <<= 1;

			value |= (int)getbit();
			len++;

			while (p->len == len)
			{
				if (p->mask == value)
					return p->index;

				p++;
			}
		}
		while (p->len);

		throw -2;
		//ATLASSERT(0);
		return -1;
	}
*/
	void getmarkerbit()
	{
		int bit = getbit();
		if (bit != 1)
		{
			TRACE("marker bit != 1\n");
		}
		ASSERT(bit == 1);
	}
};

#if 0
class CBitStream
{
public:
	CBitStream(ILByteStream* byteStream)
	{
		m_byteStream = byteStream;
		m_bitcnt = 8;
		m_countBits = 0;
	}

	ULONGLONG m_countBits;

	BYTE m_curbyte;
	//ULONG m_bitpos;
	int m_bitcnt;

	ISequentialByteStream* m_byteStream;

//	CComPtr<IStream> m_stream;

#if 0
	HRESULT Read( 
            /* [length_is][size_is][out] */ void *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead)
	{
		/*
		CopyMemory(pv, m_buffer + m_pos, cb);
		m_pos += cb;
		if (pcbRead)
			*pcbRead = cb;
		return S_OK;
		*/

		return m_stream->Read(pv, cb, pcbRead);
	}

	HRESULT Seek(
            /* [in] */ LARGE_INTEGER dlibMove,
            /* [in] */ DWORD dwOrigin,
            /* [out] */ ULARGE_INTEGER *plibNewPosition)
	{
		/*
		if (dwOrigin == STREAM_SEEK_SET)
			m_pos = dlibMove.QuadPart;
		else if (dwOrigin == STREAM_SEEK_CUR)
			m_pos += dlibMove.QuadPart;
		else
			m_pos = m_size + dlibMove.QuadPart;

		if (plibNewPosition)
			(*plibNewPosition).QuadPart = m_pos;

		return S_OK;
*/
		return m_stream->Seek(dlibMove, dwOrigin, plibNewPosition);
	}
#endif

	int getbit()
	{
		if (m_bitcnt == 8)
		{
			ULONG nRead;
			HRESULT hr = m_byteStream->Read(&m_curbyte, 1, &nRead);
			if (nRead < 1)
				THROW(-1);

			m_bitcnt = 0;
		}

		int bit = (m_curbyte >> (7-m_bitcnt)) & 0x1;

		m_bitcnt++;

		m_countBits++;

		return bit;
	}

	void getmarkerbit()
	{
		int bit = getbit();
		if (bit != 1)
		{
			ATLTRACE("marker bit != 1\n");
		}
		ATLASSERT(bit == 1);
	}

	void ungetbits(int nbits)
	{
		HRESULT hr;

		for (int i = 0; i < nbits; i++)
		{
			m_bitcnt--;

			if (m_bitcnt == 0)
			{
				LARGE_INTEGER li;
				li.QuadPart = -1;
				hr = m_byteStream->Seek(li, STREAM_SEEK_CUR, NULL);
				if (FAILED(hr))
					THROW(-1);

				m_bitcnt = 8;
			}
		}

		if (m_bitcnt < 8)
		{
			LARGE_INTEGER li;
			li.QuadPart = -1;
			HRESULT hr = m_byteStream->Seek(li, STREAM_SEEK_CUR, NULL);
			if (FAILED(hr))
				THROW(-1);

			ULONG nRead;
			hr = m_byteStream->Read(&m_curbyte, 1, &nRead);
			if (nRead < 1)
				THROW(-1);
		}

		m_countBits -= nbits;
	}

	int getnbits2(int nbits)
	{
		int value = 0;

		for (int i = 0; i < nbits; i++)
		{
			value <<= 1;
			if (getbit()) value |= 1;
		}

		return value;
	}

	int getnbits(int nbits)
	{
		ATLASSERT(nbits <= 32);

		int value = 0;

		//if (nbits < 8)
		{
			return getnbits2(nbits);
		}
		/*
		else
		{
			int cnt = 8-m_bitcnt;

		// finish the current byte
			value = m_curbyte >> m_bitcnt;
			m_bitcnt = 8;
		
			value |= getnbits2(nbits - cnt) << cnt;
		}

		return value;
		*/
	}

	void align()
	{
		m_bitcnt = 8;
	}

	int getvariablebits(vtab2 table[], int maxlen = 32)
	{
		int len = 0;
		DWORD value = 0;
		vtab2* p = table;

		ATLASSERT(p->len);

		do
		{
			value <<= 1;

			value |= getbit();
			len++;

			while (p->len == len)
			{
				if (p->mask == value)
					return p->index;

				p++;
			}
		}
		while (p->len);

		throw -2;
		//ATLASSERT(0);
		return -1;
	}

	bool is_byte_aligned()
	{
		return (m_bitcnt == 8);
	}
#if 0
	void find_next_start_code()
	{
		int n24;
		while ((n24 = getnbits(24)) != 0x1)
		{
			ungetbits(16);
		}

		m_next_code = 0x100 | getnbits(8);
	}
#endif

	void next_start_code()
	{
	// TODO, read all bits with one call to getnbits() to make it byte-aligned
		while (!is_byte_aligned())
		{
			int bit = getbit();
			if (bit != 0)
				THROW(-1);
		}

		int n24;
		while ((n24 = getnbits(24)) != 0x1)
		{
			ungetbits(24);
			int byte = getnbits(8);
			if (byte != 0)
				THROW(-1);
		}

		ATLASSERT(n24 == 0x1);
		m_next_code = 0x100 | getnbits(8);
	}

	int m_next_code;
};
#endif

}	// Media
}

#endif // __MPEGBitStream_h__
