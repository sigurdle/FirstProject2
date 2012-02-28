#include "stdafx.h"
#include "ZLIBDeflate.h"

//#include <algorithm>

namespace System
{
using namespace IO;

int Inflate::BitStream::GetCode(titem* items, int ncodes)
{
	int code = 0;
	int len = 0;
	while (len < 16)
	{
/*
Huffman codes are packed starting with the most-
significant bit of the code
*/
		code <<= 1;
		code |= (int)getbit();
		len++;

		for (int i = 0; i < ncodes; i++)
		{
			if (items[i].Len == len &&
				items[i].Code == code)
			{
				return i;
			//	return items[i].Code;
			}
		}
	}
	ASSERT(0);
	return -1;
}

bool Inflate::BitStream::getbit()
{
	if (m_bitcnt == 8)
	{
		ReadByte(&m_curbyte);

		m_bitcnt = 0;
	}

/*
Data elements are packed into bytes in order of
increasing bit number within the byte, i.e., starting
with the least-significant bit of the byte
*/
	bool bit = (m_curbyte >> (m_bitcnt)) & 0x1;

	m_bitcnt++;

	return bit;
}

int Inflate::BitStream::getnbits(int nbits)
{
	ASSERT(nbits > 0);
	ASSERT(nbits <= 32);

	/*
	Data elements other than Huffman codes are packed
	starting with the least-significant bit of the data
	element
	*/

	if (true)
	{
		int value = 0;

		int i = 0;
		// Current byte
		if (m_bitcnt < 8)
		{
			int n = std::min(nbits, 8-m_bitcnt);
			value = (m_curbyte>>m_bitcnt) & ((1<<n)-1);
			m_bitcnt += n;
			//nbits -= n;
			i += n;
		}

		while (i < nbits)
		{
			ASSERT(m_bitcnt == 8);
			ReadByte(&m_curbyte);
			m_bitcnt = 0;

			int n = std::min(nbits-i, 8);

			value |= (m_curbyte & ((1<<n)-1))<<i;

			m_bitcnt += n;
			i += n;
		}
		/*

		for (int i = 0; i < nbits; i++)
		{
			bool bit = getbit();
			value |= bit<<i;
		}
		*/
		return value;
	}
	else
	{
		int value = 0;

		for (int i = 0; i < nbits; i++)
		{
			bool bit = getbit();
			value |= bit<<i;
		}

		return value;
	}
}

inline void Inflate::BitStream::byte_align()
{
	m_bitcnt = 8;
}

Inflate::Inflate(IO::Stream* byteStream, ubyte compressionInfo, ULONG totalSize)
{
	m_bitstream = new BitStream(byteStream);

	m_inflatedSize = 0L;
	m_readSize = 0L;
	m_totalSize = totalSize;
	m_bdone = false;

	Init(compressionInfo);
	start_block();
}

Inflate::~Inflate()
{
	delete m_bitstream;
}

void ComputeCodes(Inflate::titem* tree, int max_bits, int max_code)
{
	int bl_count[32] = {0};

//	Count the number of codes for each code length
	for (int i = 0; i < max_code; i++)
	{
		ASSERT(tree[i].Len <= 15);
		bl_count[tree[i].Len]++;
	}

	int next_code[32];

	int code = 0;
	bl_count[0] = 0;
	for (int bits = 1; bits < max_bits; ++bits)
	{
		code = (code + bl_count[bits-1]) << 1;
		next_code[bits] = code;
	}

	// Assign codes
	for (int n = 0;  n < max_code; n++)
	{
		int len = tree[n].Len;
		if (len != 0)
		{
			tree[n].Code = next_code[len];
			next_code[len]++;
		}
	}
}

void Inflate::Init(ubyte compressionInfo)
{
	m_windowSizeBits = compressionInfo+8;
	m_windowSize = 1<<m_windowSizeBits;

	m_windowBuffer = new uint8[m_windowSize];

	m_outptr = m_windowBuffer;
	m_readptr = m_outptr;
}

void Inflate::start_block()
{
	// block header
	m_bfinal = m_bitstream->getbit();
	int btype = m_bitstream->getnbits(2);

	if (btype == 0)	// no compression
	{
		ASSERT(0);
	}
	else
	{
		m_litlenCodes = new titem[288];
		m_distCodes = new titem[30];

		if (btype == 2)	// dynamic huffman codes
		{
			int hlit = m_bitstream->getnbits(5);
			int hdist = m_bitstream->getnbits(5);
			int hclen = m_bitstream->getnbits(4);

			int order[] =
			{
				16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
			};

			titem* tree = new titem[19];
			std::memset(tree, 0, sizeof(titem)*19);
			for (int i = 0; i < hclen+4; i++)
			{
				tree[order[i]].Len = m_bitstream->getnbits(3);
			}
			ComputeCodes(tree, 8, 19);

			int count = (hlit + hdist + 258);
			titem* ttree = new titem[count];

			int i2 = 0;
			while (i2 < count)
			{
				int len = m_bitstream->GetCode(tree, 19/*hclen+4*/);
				if (len < 16)
				{
					ttree[i2++].Len = len;
				}
				else if (len == 16)
				{
					ASSERT(i2 > 0);
					int repeat = m_bitstream->getnbits(2) + 3;
					for (int n = 0; n < repeat; n++)
					{
						ttree[i2].Len = ttree[i2-1].Len;
						i2++;
					}
				}
				else if (len == 17)
				{
					int length = m_bitstream->getnbits(3)+3;
					for (int n = 0; n < length; n++)
					{
						ttree[i2++].Len = 0;
					}
				}
				else if (len == 18)
				{
					int length = m_bitstream->getnbits(7)+11;
					for (int n = 0; n < length; n++)
					{
						ttree[i2++].Len = 0;
					}
				}
				else
				{
					ASSERT(0);
				}
			}

			memset(m_litlenCodes, 0, sizeof(titem)*288);
			memcpy(m_litlenCodes, ttree, (hlit+257)*sizeof(titem));

			memset(m_distCodes, 0, sizeof(titem)*30);
			memcpy(m_distCodes, ttree+(hlit+257), (hdist+1)*sizeof(titem));
		}
		else	// fixed huffman codes
		{
			int i = 0;

			for (; i < 144; i++)	m_litlenCodes[i].Len = 8;
			for (; i < 256; i++)	m_litlenCodes[i].Len = 9;
			for (; i < 280; i++)	m_litlenCodes[i].Len = 7;
			for (; i < 288; i++)	m_litlenCodes[i].Len = 8;

			for (i = 0; i < 30; i++) m_distCodes[i].Len = 5;
		}

		ComputeCodes(m_litlenCodes, 32, 288);
		ComputeCodes(m_distCodes, 32, 30);
	}
}

unsigned char LitLenExtraBits[] =
{
	0,0,0,0,0,0,0,0,
	1,1,1,1,
	2,2,2,2,
	3,3,3,3,
	4,4,4,4,
	5,5,5,5,
	0
};

int LitLenBase[] =
{
	3, 4, 5, 6, 7, 8, 9, 10,
	11, 13, 15, 17,
	19, 23, 27, 31,
	35, 43, 51, 59,
	67, 83, 99, 115,
	131, 163, 195, 227,
	258,
};

unsigned char DistExtraBits[] =
{
	0, 0, 0, 0,
	1, 1,
	2, 2,
	3, 3,
	4, 4,
	5, 5,
	6, 6,
	7, 7,
	8, 8,
	9, 9,
	10, 10,
	11, 11,
	12, 12,
	13, 13,
};

int DistBase[] =
{
	1, 2, 3, 4,
	5,
	7,
	9,
	13,
	17,
	25,
	33,
	49,
	65,
	97,
	129,
	193,
	257,
	385,
	513,
	769,
	1025,
	1537,
	2049,
	3073,
	4097,
	6145,
	8193,
	12289,
	16385,
	24577
};

bool Inflate::InflateNextCode()
{
	int litlen = m_bitstream->GetCode(m_litlenCodes, 286);
	while (litlen == 256)	// end of block
	{
		if (m_bfinal)
		{
			return true;
		}
		start_block();
		litlen = m_bitstream->GetCode(m_litlenCodes, 286);
	}

	if (litlen < 256)	// literal
	{
		if (m_outptr == m_windowBuffer+m_windowSize)
			m_outptr = m_windowBuffer;

		*m_outptr++ = litlen;
		m_inflatedSize++;
	}
	else	// length
	{
		int index = litlen - 257;
		int length = LitLenBase[index];
		if (int extraBits = LitLenExtraBits[index])
			length += m_bitstream->getnbits(extraBits);

		int distcode = m_bitstream->GetCode(m_distCodes, 30);
		int distance = DistBase[distcode];

		if (int extraBits = DistExtraBits[distcode])
			distance += m_bitstream->getnbits(extraBits);

		if (distance > m_inflatedSize)
		{
			raise(Exception(L"Inflate corrupt"));
		}

		for (int n = 0; n < length; n++)
		{
			uint8* srcptr = m_outptr - distance;
			if (srcptr < m_windowBuffer) srcptr += m_windowSize;

			if (m_outptr == m_windowBuffer+m_windowSize)
				m_outptr = m_windowBuffer;

			*m_outptr++ = *srcptr;
		}
		m_inflatedSize += length;
	}

	return false;
}

size_t Inflate::Read(void* pv, size_t cb)
{
	if (m_bdone) return 0;

	uint8* p = (uint8*)pv;

	ULONG i;

	for (i = 0; i < cb; i++)
	{
		if (m_inflatedSize == m_readSize)
		{
			m_bdone = InflateNextCode();
		}

		if (m_bdone)
			return i;

		ASSERT(m_readSize < m_inflatedSize);

		if (m_readptr == m_windowBuffer+m_windowSize)
			m_readptr = m_windowBuffer;

		*p++ = *m_readptr++;
		m_readSize++;
	}

	return i;
}

uint64 Inflate::Seek(LONGLONG offset, IO::SeekOrigin origin)
{
	unsigned long abspos;

	if (origin == STREAM_SEEK_CUR)
	{
		abspos = m_readSize + offset;
	}
	else if (origin == STREAM_SEEK_SET)
	{
		abspos = offset;
	}
	else if (origin == STREAM_SEEK_END)
	{
		if (m_totalSize == -1)
		{
			// Unknown uncompressedSize, determine it by reading to the end
			m_totalSize = m_readSize;
			ULONG n;
			do
			{
				uint8 buffer[256];
				n = Read(buffer, 256);
				m_totalSize += n;
			}
			while (n == 256);
		}

		abspos = m_totalSize + offset;
	}
	else
	{
		raise(ArgumentException());
	}

	if (abspos < m_readSize)	// Backward
	{
		long diff = m_readSize - abspos;

		if (diff > m_windowSize)
		{
			raise(ZLIBException("Seeked to far backwards"));
		}

		m_readptr -= diff;
		if (m_readptr < m_windowBuffer) m_readptr += m_windowSize;
		m_readSize = abspos;
	}
	else	// Forward
	{
		for (size_t i = m_readSize; i < abspos; ++i)
		{
			uint8 b;
			if (Read(&b, 1) != 1)
				break;
		}
	}

	return m_readSize;
}

uint64 Inflate::GetSize()
{
	if (m_totalSize == ~0)
	{
		raise(Exception(L"unknown size"));
	}

	return m_totalSize;
}

size_t Inflate::Write(const void* pv, size_t nbytes)
{
	raise(Exception("Write not implemented"));
	return 0;
}

}	// System
