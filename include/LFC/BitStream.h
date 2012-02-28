#ifndef __BitStream_h_
#define __BitStream_h_

namespace System
{
namespace IO
{

class CBitStream32;

class LFCEXT CByteStream : public Object// : public ISequentialByteStream
{
public:
	CTOR CByteStream(Stream* byteStream);

	_Ptr<Stream> m_byteStream;
	ULONG m_refcount;

	ULONG AddRef();

	ULONG Release();

	LONGLONG GetSize()
	{
		THROW(-1);
		return -1;
	}

	virtual LONGLONG Seek(LONGLONG move, ULONG origin);

	/*
	ISequentialByteStream* Clone() const
	{
		ISequentialByteStream* p2 = m_byteStream->Clone();
		p2->Seek(-m_nstacked, System::IO::STREAM_SEEK_CUR);

		CByteStream* p = new CByteStream(p2);

		return p;
	}

	ULONG Read(void* pv, ULONG cb)
	{
		uint8* pb = (uint8*)pv;
		ULONG i;

		for (i = 0; i < cb; i++)
		{
			uint32 byte;
			int f = getbyte(&byte);
			if (f == -1) break;

			*pb++ = byte;
		}
		return i;
	}

	ULONG Write(const void* pv, ULONG cb)
	{
		THROW(-1);
		return 0;
	}
	*/

	int getbyte(uint32* p);

	inline void ungetbyte()
	{
		ASSERT(m_bytepos > 0);
		m_nstacked++;
		m_bytepos--;
	}

	inline void ungetbytes(int nbytes)
	{
		ASSERT(m_bytepos >= nbytes);
		m_nstacked += nbytes;
		m_bytepos -= nbytes;
	}

	inline LONGLONG GetPos() const
	{
		return m_bytepos;
	}

	ULONGLONG m_bytepos;

protected:

	int m_nstacked;
	uint32 m_oldc[0x2000];

	friend class CBitStream32;
};

class LFCEXT CBitStream32 : public Object
{
public:
	CTOR CBitStream32(CByteStream* byteStream);

	~CBitStream32();

	ULONGLONG m_countBits;

	void SetBytePos(ULONGLONG pos);

	LONGLONG GetBytePos() const
	{
		return (m_byteStream->m_bytepos<<2) - (m_bitcnt>>3);
	}

	LONGLONG GetBitPos() const
	{
		return (m_byteStream->m_bytepos<<5) - (m_bitcnt);
	}

	int looknbits(int nbits);
	void skipnbits(int nbits);
	bool checknbits_zero(int nbits);

	bool getbit();

	ULONGLONG m_bitstreamSize;

	bool eof()
	{
		if (m_countBits < m_bitstreamSize)
	//	if (((m_countBits+7)/8) < ((m_bitstreamSize+7)/8))
			return false;
		else
			return true;
	}

	void ungetbits(int nbits);

	int getnbits(int nbits);

	LONGLONG getlonglong()
	{
		return ((LONGLONG)getnbits(32)<<32) | (LONGLONG)getnbits(32);
	}

	inline void byte_align()
	{
		m_bitcnt &= ~7;
	}

	inline bool is_byte_aligned()
	{
		return ((m_bitcnt & 7) == 0);
	}

protected:

	int m_bitcnt;

	inline void ungetbyte()
	{
		m_byteStream->ungetbyte();
	}

	inline void ungetbytes(int nbytes)
	{
		m_byteStream->ungetbytes(nbytes);
	}

private:

	uint32 m_curbyte;
	CByteStream* m_byteStream;

	inline uint32 getbyte()
	{
		uint32 byt;
		int f = m_byteStream->getbyte(&byt);
		if (f == -1)
			raise(Exception(L"IO Error"));

		return byt;
	}
};

class LFCEXT GetByteStream
{
public:
	CTOR GetByteStream()
	{
	}

	CTOR GetByteStream(const GetByteStream& other) :
		m_byteStream(other.m_byteStream)
	{
	}

	CTOR GetByteStream(Stream* byteStream);

	inline uint8 getbyte()
	{
		uint8 byt;

		size_t nRead = m_byteStream->Read(&byt, 1);
		if (nRead != 1)
			raise(Exception(L"IO Error"));

		return byt;
	}

	_Ptr<Stream> m_byteStream;

private:

	GetByteStream& operator = (const GetByteStream&);
};

template<class getbyte_f> class BitStreamT
{
public:
	CTOR BitStreamT()
	{
		m_bitcnt = 0;
		m_countBits = 0;
		m_bitstreamSize = 0;
	}

	CTOR BitStreamT(const getbyte_f& gf) : m_getbyte(gf)
	{
		m_bitcnt = 0;
		m_countBits = 0;
		m_bitstreamSize = 0;
	}

	~BitStreamT()
	{
	}

	/*
	void SetBytePos(ULONGLONG pos);

	LONGLONG GetBytePos() const
	{
		return (m_byteStream->m_bytepos<<2) - (m_bitcnt>>3);
	}

	LONGLONG GetBitPos() const
	{
		return (m_byteStream->m_bytepos<<5) - (m_bitcnt);
	}
	*/

//	int looknbits(int nbits);
//	bool checknbits_zero(int nbits);

	LONGLONG getlonglong()
	{
		return ((LONGLONG)getnbits(32)<<32) | (LONGLONG)getnbits(32);
	}

	inline void byte_align()
	{
		m_bitcnt = 0;
	}

	inline bool is_byte_aligned()
	{
		return (m_bitcnt == 0);
	}

	bool getbit()
	{
		if (m_bitcnt == 0)
		{
			m_curbyte = /*static_cast<T*>(this)->*/m_getbyte.getbyte();
		//	if (m_byteStream->Read(&m_curbyte, 1) < 1)
		//		THROW(-1);

			m_bitcnt = 8;
		}

		m_bitcnt--;

		bool bit = (m_curbyte >> (m_bitcnt)) & 0x1;

		m_countBits++;

		return bit;
	}

	int getnbits(int nbits)
	{
		ASSERT(nbits <= 32);

		m_countBits += nbits;

		int value = 0;

		// Finish the current byte
		if (m_bitcnt > 0)
		{
			uint8 n = MIN(nbits, m_bitcnt);
			value = (m_curbyte>>(m_bitcnt-n)) & ((1<<n)-1);
			nbits -= n;
			m_bitcnt -= n;
		}

		while (nbits)
		{
			m_bitcnt = 8;
			uint8 n = MIN(nbits, 8);
			m_curbyte = /*static_cast<T*>(this)->*/m_getbyte.getbyte();
			value <<= n;
			value |= (m_curbyte>>(8-n)) & ((1<<n)-1);
			nbits -= n;
			m_bitcnt -= n;
		}
		ASSERT(/*m_bitcnt >= 0 && */ m_bitcnt < 8);

		return value;
	}

	ULONGLONG m_countBits;
	ULONGLONG m_bitstreamSize;

	getbyte_f m_getbyte;

private:

	uint8 m_bitcnt;
	uint8 m_curbyte;
};

class LFCEXT BitStream : public BitStreamT<GetByteStream>
{
public:
	CTOR BitStream(Stream* stream) : BitStreamT<GetByteStream>(stream)
	{
	}
};

}	// IO
}	// System

#endif // __BitStream_h_
