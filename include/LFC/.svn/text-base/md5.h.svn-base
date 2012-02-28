#ifndef __MD5_H_
#define __MD5_H_

namespace System
{
namespace Crypt
{

class LFCEXT MD5
{
public:
	CTOR MD5();

	void process();
	void GetDigest(uint32 buffer[4]) const;

	_Ptr<IO::Stream> m_stream;

protected:

	// Returns false if this is the last block, true otherwise
	bool block();

	// Returns false if this is the last block, true otherwise
	bool ReadBlock(uint8 block[64]);

	static inline uint32 F(uint32 X, uint32 Y, uint32 Z)
	{
		return X & Y | ~X & Z;
	}

	static inline uint32 G(uint32 X, uint32 Y, uint32 Z)
	{
		return X & Z | Y & ~Z;
	}

	static inline uint32 H(uint32 X, uint32 Y, uint32 Z)
	{
		return X ^ Y ^ Z;
	}
 
	static inline uint32 I(uint32 X, uint32 Y, uint32 Z)
	{
		return Y ^ (X | ~Z);
	}

	/*
	MD5(ISequentialByteStream* stream)
	{
		m_stream = stream;
	}
	*/

	static inline uint32 ROTATE_LEFT(uint32 x, uint32 bits)
	{
		return (x<<bits) | (x>>(32-bits));
	}

	uint32 A;
	uint32 B;
	uint32 C;
	uint32 D;
};

}	// Crypt
}

#endif // __MD5_H_
