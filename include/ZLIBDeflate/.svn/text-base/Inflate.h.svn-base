#ifndef Inflate_h
#define Inflate_h

namespace System
{
namespace IO
{

class ZLIBEXT Inflate : public IO::Stream
{
public:

	struct titem
	{
		int Code;
		int Len;
	};

	class BitStream
	{
	public:
		CTOR BitStream(IO::Stream* byteStream) : m_byteStream(byteStream), m_bitcnt(8)
		{
		}

		void ReadByte(uint8* pv)
		{
			if (m_byteStream->Read(pv, 1) == 0)
			{
				raise(SystemException(L"EOF"));	// TODO
			}
		}

		int GetCode(titem* items, int ncodes);
		bool getbit();
		int getnbits(int nbits);
		inline void byte_align();

		_Ptr<IO::Stream> m_byteStream;

		byte m_curbyte;
		uint8 m_bitcnt;
	};

	CTOR Inflate(IO::Stream* byteStream, uint8 compressionInfo, ULONG uncompressedSize = -1);
	virtual ~Inflate();

	virtual size_t Read(void* pv, size_t cb) override;
	virtual uint64 Seek(int64 offset, SeekOrigin origin) override;
	virtual uint64 GetSize() override;

	virtual size_t Write(const void* pv, size_t cb) override;

	virtual bool CanSeek() override
	{
		return false;
	}

	virtual bool CanRead() override
	{
		return true;
	}

	virtual bool CanWrite() override
	{
		return false;
	}

	virtual uint64 GetPosition() override
	{
		return m_readSize;
	}

	BitStream* get_BitStream() const
	{
		return m_bitstream;
	}

protected:

	void start_block();
	void Init(ubyte compressionInfo);
	bool InflateNextCode();

	titem* m_litlenCodes;	// Combined literals / lengths
	titem* m_distCodes;

	ubyte* m_windowBuffer;

	ubyte* m_outptr;
	ubyte* m_readptr;

	BitStream* m_bitstream;

	uint64 m_totalSize;

	// TODO: uint64 ?
	size_t m_inflatedSize;
	size_t m_readSize;

	int m_windowSizeBits;	// window size in bits
	int m_windowSize;

	bool m_bfinal;	// true if the current block the final block
	bool m_bdone;
};

}	// IO
}	// System

#endif // Inflate_h
