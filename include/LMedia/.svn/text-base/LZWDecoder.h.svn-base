#ifndef __LZWDECODER_H__
#define __LZWDECODER_H__

namespace System
{

class ISequentialBitStream
{
public:
	virtual int getnbits(int nbits) = 0;
};

class GIFBitStream : public ISequentialBitStream
{
public:
	CTOR GIFBitStream(IO::Stream* byteStream) :
		m_byteStream(byteStream)
	{
		m_bitcnt = 8;
	}

	void ReadByte(uint8* pv)
	{
		m_byteStream->Read(pv, 1);
		/*
		ULONG nRead;
		HRESULT hr = m_byteStream->Read(&m_curbyte, 1, &nRead);
		if (nRead < 1)
			THROW(-1);
			*/

			/*
		if (m_offset < m_length)
			*pv = m_data[m_offset++];
		else
			THROW(-1);
			*/
	}

	bool getbit()
	{
		if (m_bitcnt == 8)
		{
			ReadByte(&m_curbyte);

			m_bitcnt = 0;
		}

//		bool bit = (m_curbyte >> (7-m_bitcnt)) & 0x1;
		bool bit = (m_curbyte >> (m_bitcnt)) & 0x1;

		m_bitcnt++;

	//	m_countBits++;

		return bit;
	}

	int getnbits(int nbits)
	{
		ASSERT(nbits > 0);
		ASSERT(nbits <= 32);

		int value = 0;

		for (int i = 0; i < nbits; i++)
		{
			bool bit = getbit();
			value |= bit<<i;
//			value <<= 1;
//			if (bit) value |= 1;
		}

		return value;
	}

	/*
	long m_offset;
	BYTE* m_data;
	long m_length;
	*/
	_Ptr<IO::Stream> m_byteStream;

	uint8 m_curbyte;
	int m_bitcnt;
};

class TIFFBitStream : public ISequentialBitStream
{
public:
	CTOR TIFFBitStream(IO::Stream* byteStream) :
		m_byteStream(byteStream)
	{
		m_bitcnt = 8;
	}

	void ReadByte(uint8* pv)
	{
		m_byteStream->Read(pv, 1);
		/*
		ULONG nRead;
		HRESULT hr = m_byteStream->Read(&m_curbyte, 1, &nRead);
		if (nRead < 1)
			THROW(-1);
			*/

			/*
		if (m_offset < m_length)
			*pv = m_data[m_offset++];
		else
			THROW(-1);
			*/
	}

	bool getbit()
	{
		if (m_bitcnt == 8)
		{
			ReadByte(&m_curbyte);

			m_bitcnt = 0;
		}

		bool bit = (m_curbyte >> (7-m_bitcnt)) & 0x1;
//		bool bit = (m_curbyte >> (m_bitcnt)) & 0x1;

		m_bitcnt++;

	//	m_countBits++;

		return bit;
	}

	int getnbits(int nbits)
	{
		ASSERT(nbits > 0);
		ASSERT(nbits <= 32);

		int value = 0;

		for (int i = 0; i < nbits; i++)
		{
			bool bit = getbit();
//			value |= bit<<i;
			value <<= 1;
			if (bit) value |= 1;
		}

		return value;
	}

	/*
	long m_offset;
	BYTE* m_data;
	long m_length;
	*/
	_Ptr<IO::Stream> m_byteStream;

	uint8 m_curbyte;
	uint8 m_bitcnt;
};

// diff because of some slight difference in the GIF and TIFF LZW streams
template<int diff> class LZWDecoder
{
public:
	CTOR LZWDecoder(ISequentialBitStream* bitStream, int inputCodeSize) :
		m_bitStream(bitStream),
		m_input_code_size(inputCodeSize)
	{
		m_bufferPos = 0;
		m_strings = new LZWCodeString[1<<12];
		m_buffer = new uint8[4096];	// How big should this be ?

		// Initialize string table
		m_stringTableSize = (1<<m_input_code_size);
		for (int i = 0; i < m_stringTableSize; ++i)
		{
			m_strings[i].Prefix = -1;
			m_strings[i].Char = i;
		}

		m_ClearCode = m_stringTableSize;
		m_EoiCode = m_stringTableSize+1;
		m_stringTableSize += 2;

		m_codeBitSize = m_input_code_size+1;
	}

	~LZWDecoder()
	{
		delete [] m_strings;
	}

	struct LZWCodeString
	{
		short Prefix;
		uint8 Char;
	};

	int GetNextChar()
	{
		while (m_bufferPos == 0)
		{
			int code = GetNextCode();
			if (code == m_EoiCode)
				return -1;

			if (code == m_ClearCode)
			{
				m_codeBitSize = m_input_code_size+1;
				m_stringTableSize = (1<<m_input_code_size)+2;

				code = GetNextCode();
				if (code == m_EoiCode)
					return -1;

				WriteStringFromCode(code);

				m_oldCode = code;
			}
			else
			{
				if (code < m_stringTableSize)
				{
					WriteStringFromCode(code);

					m_strings[m_stringTableSize].Prefix = m_oldCode;

					// FirstChar
					int i = code;
					ASSERT(i < m_stringTableSize);
					while (m_strings[i].Prefix != -1)
					{
						ASSERT(i < m_stringTableSize);
						i = m_strings[i].Prefix;
					}

					m_strings[m_stringTableSize].Char = m_strings[i].Char;
					m_stringTableSize++;
					if (m_stringTableSize == (1<<m_codeBitSize)-diff)
					{
						if (m_codeBitSize < 12)
							m_codeBitSize++;
					}

					m_oldCode = code;
				}
				else if (code == m_stringTableSize)
				{
					// FirstChar
					short i = m_oldCode;
					ASSERT(i < m_stringTableSize);
					while (m_strings[i].Prefix != -1)
					{
						i = m_strings[i].Prefix;
						ASSERT(i < m_stringTableSize);
					}

					m_strings[m_stringTableSize].Prefix = m_oldCode;
					m_strings[m_stringTableSize].Char = m_strings[i].Char;

					WriteStringFromCode(m_stringTableSize);

					m_stringTableSize++;

					if (m_stringTableSize == (1<<m_codeBitSize)-diff)
					{
						if (m_codeBitSize < 12)
							m_codeBitSize++;
					}

					m_oldCode = code;
				}
				else	// Error
					return -2;
			}
		}

		return m_buffer[--m_bufferPos];
	}

protected:

	inline int GetNextCode()
	{
		return m_bitStream->getnbits(m_codeBitSize);
	}

	void WriteStringFromCode(int code)
	{
		short i = code;
		do
		{
		//	ASSERT(i < m_stringTableSize);
			m_buffer[m_bufferPos++] = m_strings[i].Char;
			i = m_strings[i].Prefix;
		}
		while (i != -1);
	}

	ISequentialBitStream* m_bitStream;
	LZWCodeString* m_strings;

	int m_input_code_size;
	int m_ClearCode;
	int m_EoiCode;

	int m_codeBitSize;
	int m_stringTableSize;

	int m_bufferPos;
	ubyte* m_buffer;
	short m_oldCode;
};

}	// System

#endif // __LZWDECODER_H__
