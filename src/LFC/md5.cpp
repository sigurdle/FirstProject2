#include "stdafx.h"
#include "LFC.h"
#include "MD5.h"

namespace System
{
namespace Crypt
{

MD5::MD5()
{
	A = 0x67452301;
	B = 0xefcdab89;
	C = 0x98badcfe;
	D = 0x10325476;
}
	
// Returns false if this is the last block, true otherwise
bool MD5::ReadBlock(uint8 block[64])
{
	ULONG blockSize = 64;
	ULONG nRead = m_stream->Read(block, blockSize);
	if (nRead < blockSize)	// Reached end of stream, pad with at least one bit and add length
	{
		ULONGLONG streamBitLength = m_stream->Seek(0, System::IO::STREAM_SEEK_CUR) * 8;

		ASSERT(nRead < 55);

		// We work on hole bytes only, and padding with at least one bit
		// also means we pad with at least one byte

		ULONG padded = (nRead + 64) & ~63;
		block[nRead] = 0x80;	// pad with bit 7 set
		// rest with zeroes
		for (uint i = nRead+1; i < padded-8; i++)
		{
			block[i] = 0;
		}

		// then a 64bit length (in bits) of the stream
		block[56] = streamBitLength;
		block[57] = streamBitLength>>8;
		block[58] = streamBitLength>>16;
		block[59] = streamBitLength>>24;
		block[60] = streamBitLength>>32;
		block[61] = streamBitLength>>40;
		block[62] = streamBitLength>>48;
		block[63] = streamBitLength>>56;

		return false;
	}

	return true;
}

#define FF(a, b, c, d, k, s, i) a = b + ROTATE_LEFT((a + F(b,c,d) + X[k] + i), s)
#define GG(a,b,c,d, k, s, i) 	a = b + ROTATE_LEFT((a + G(b,c,d) + X[k] + i), s)
#define HH(a,b,c,d, k, s, i) a = b + ROTATE_LEFT((a + H(b,c,d) + X[k] + i), s)
#define II(a,b,c,d, k, s, i) a = b + ROTATE_LEFT((a + I(b,c,d) + X[k] + i), s)

// Returns false if this is the last block, true otherwise
bool MD5::block()
{
	uint32 X[16];
	bool more = ReadBlock((uint8*)X);

	uint32 AA = A;
	uint32 BB = B;
	uint32 CC = C;
	uint32 DD = D;
	
	FF(A,B,C,D,  0,  7,  0xd76aa478);
	FF(D,A,B,C,  1, 12,  0xe8c7b756);
	FF(C,D,A,B,  2, 17,  0x242070db);
	FF(B,C,D,A,  3, 22,  0xc1bdceee);
	FF(A,B,C,D,  4,  7,  0xf57c0faf);
	FF(D,A,B,C,  5, 12,  0x4787c62a);
	FF(C,D,A,B,  6, 17,  0xa8304613);
	FF(B,C,D,A,  7, 22,  0xfd469501);
	FF(A,B,C,D,  8,  7,  0x698098d8);
	FF(D,A,B,C,  9, 12, 0x8b44f7af);
	FF(C,D,A,B, 10, 17, 0xffff5bb1);
	FF(B,C,D,A, 11, 22, 0x895cd7be);
	FF(A,B,C,D, 12,  7, 0x6b901122);
	FF(D,A,B,C, 13, 12, 0xfd987193);
	FF(C,D,A,B, 14, 17, 0xa679438e);
	FF(B,C,D,A, 15, 22, 0x49b40821);

	GG(A,B,C,D,  1,  5, 0xf61e2562);
	GG(D,A,B,C,  6,  9, 0xc040b340);
	GG(C,D,A,B, 11, 14, 0x265e5a51);
	GG(B,C,D,A,  0, 20, 0xe9b6c7aa);
	GG(A,B,C,D,  5,  5, 0xd62f105d);
	GG(D,A,B,C, 10,  9, 0x2441453);
	GG(C,D,A,B, 15, 14, 0xd8a1e681);
	GG(B,C,D,A,  4, 20, 0xe7d3fbc8);
	GG(A,B,C,D,  9,  5, 0x21e1cde6);
	GG(D,A,B,C, 14,  9, 0xc33707d6);
	GG(C,D,A,B,  3, 14, 0xf4d50d87);
	GG(B,C,D,A,  8, 20, 0x455a14ed);
	GG(A,B,C,D, 13,  5, 0xa9e3e905);
	GG(D,A,B,C,  2,  9, 0xfcefa3f8);
	GG(C,D,A,B,  7, 14, 0x676f02d9);
	GG(B,C,D,A, 12, 20, 0x8d2a4c8a);

	HH(A,B,C,D,  5,  4, 0xfffa3942);
	HH(D,A,B,C,  8, 11, 0x8771f681);
	HH(C,D,A,B, 11, 16, 0x6d9d6122);
	HH(B,C,D,A, 14, 23, 0xfde5380c);
	HH(A,B,C,D,  1,  4, 0xa4beea44);
	HH(D,A,B,C,  4, 11, 0x4bdecfa9);
	HH(C,D,A,B,  7, 16, 0xf6bb4b60);
	HH(B,C,D,A, 10, 23, 0xbebfbc70);
	HH(A,B,C,D, 13,  4, 0x289b7ec6);
	HH(D,A,B,C,  0, 11, 0xeaa127fa);
	HH(C,D,A,B,  3, 16, 0xd4ef3085);
	HH(B,C,D,A,  6, 23, 0x4881d05);
	HH(A,B,C,D,  9,  4, 0xd9d4d039);
	HH(D,A,B,C, 12, 11, 0xe6db99e5);
	HH(C,D,A,B, 15, 16, 0x1fa27cf8);
	HH(B,C,D,A,  2, 23, 0xc4ac5665);

	II(A,B,C,D,  0,  6, 0xf4292244);
	II(D,A,B,C,  7, 10, 0x432aff97);
	II(C,D,A,B, 14, 15, 0xab9423a7);
	II(B,C,D,A,  5, 21, 0xfc93a039);
	II(A,B,C,D, 12,  6, 0x655b59c3);
	II(D,A,B,C,  3, 10, 0x8f0ccc92);
	II(C,D,A,B, 10, 15, 0xffeff47d);
	II(B,C,D,A,  1, 21, 0x85845dd1);
	II(A,B,C,D,  8,  6, 0x6fa87e4f);
	II(D,A,B,C, 15, 10, 0xfe2ce6e0);
	II(C,D,A,B,  6, 15, 0xa3014314);
	II(B,C,D,A, 13, 21, 0x4e0811a1);
	II(A,B,C,D,  4,  6, 0xf7537e82);
	II(D,A,B,C, 11, 10, 0xbd3af235);
	II(C,D,A,B,  2, 15, 0x2ad7d2bb);
	II(B,C,D,A,  9, 21, 0xeb86d391);

	A += AA;
	B += BB;
	C += CC;
	D += DD;

	return more;
}

void MD5::process()
{
	while (block())
		;
}

void MD5::GetDigest(uint32 buffer[4]) const
{
	buffer[0] = A;
	buffer[1] = B;
	buffer[2] = C;
	buffer[3] = D;
}

}
}
