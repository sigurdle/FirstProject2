#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosStream.h"

#include "../LFC/ZLIBDecoder.h"
#include "../LMedia/LZWDecoder.h"

using namespace System;
using namespace System::IO;

//#include "../zlib/zlib.h"
//#pragma comment(lib, "../../src/zlib/Debug/zlib.lib")

class LZWByteStreamDecoder : public Object, public IO::ISequentialByteStream
{
public:
	LZWByteStreamDecoder(ISequentialBitStream* stream) : m_decoder(stream, 8)
	{
		m_pos = 0;
		m_bdone = false;
	}

	LZWDecoder<1> m_decoder;
	LONGLONG m_pos;
	bool m_bdone;

	virtual ULONG Read(void* pv, ULONG cb)
	{
		if (m_bdone) return 0;

		uint8* pb = (uint8*)pv;

		ULONG n;
		for (n = 0; n < cb; n++)
		{
			int c = m_decoder.GetNextChar();

			if (c == -2)	// Error
			{
				ASSERT(0);
				throw -1;
			}
			else if (c == -1)	// End of stream
			{
				m_bdone = true;
				break;
			}

			*pb = (uint8)c;
			pb++;
		}

		m_pos += n;
		return n;
	}

	virtual ULONG Write(const void* pv, ULONG cb)
	{
		return 0;
	}

	virtual LONGLONG Seek(LONGLONG move, IO::SeekOrigin origin)
	{
		// TODO, improve
		return m_pos;
	}

	virtual LONGLONG GetSize()
	{
		throw -1;
		return -1;
	}

	virtual IO::ISequentialByteStream* Clone() const
	{
		throw -1;
		return 0;
	}
};

namespace System
{
namespace PDF
{

ULONG CPDFCosStream::Stream::Read(void* pv, ULONG cb)
{
	if (m_pos < 0) throw -1;

	if (m_pos + cb > m_length)
	{
		cb = m_length - m_pos;
	}

	std::fseek(m_pCosStream->m_pCosDoc->m_fp, m_pCosStream->m_start + m_pos, SEEK_SET);
	std::fread(pv, cb, 1, m_pCosStream->m_pCosDoc->m_fp);
	m_pos += cb;

	if (m_pos >= 650)
	{
		TRACE("");
	}

	return cb;
}

ULONG CPDFCosStream::Stream::Write(const void* pv, ULONG cb)
{
	throw -1;
	return 0;
}

LONGLONG CPDFCosStream::Stream::Seek(LONGLONG move, IO::SeekOrigin origin)
{
	LONG pos;
	if (origin == System::IO::STREAM_SEEK_SET)
	{
		pos = move;
	}
	else if (origin == System::IO::STREAM_SEEK_CUR)
	{
		pos = m_pos + move;
	}
	else if (origin == System::IO::STREAM_SEEK_END)
	{
		pos = m_length - move;
	}

	m_pos = pos;

	return m_pos;
}

LONGLONG CPDFCosStream::Stream::GetSize()
{
	return m_length;
}

ISequentialByteStream* CPDFCosStream::Stream::Clone() const
{
	throw -1;
	return NULL;
}

ISequentialByteStream* CPDFCosStream::OpenRawStream()
{
	CPDFCosInteger* pLength = dynamic_cast<CPDFCosInteger*>(m_attributesDict->CosDictGet(ASTR("Length")));
	if (pLength == NULL)
	{
		ASSERT(0);
		throw -1;
		return NULL;
	}

	Stream* pStream = new Stream;
	pStream->m_pCosStream = this;
	
	pStream->m_length = pLength->GetValue();
	return pStream;
}

class ASCII85Decode : public Object, public ISequentialByteStream
{
public:
	CTOR ASCII85Decode(ISequentialByteStream* stream)
	{
		m_stream = stream;

		m_outputPos = 0;
		m_readPos = 0;

		m_bfinal = false;
		m_bdone = false;
	}

	void Output(uint8 byte)
	{
		m_outputGroup[(m_outputPos++) & 3] = byte;
	}

	int ReadByte(uint8* pb)
	{
		if (m_readPos == m_outputPos)
		{
			if (m_bfinal) return 0;

			ReadGroup();
		}

		*pb = m_outputGroup[(m_readPos++) & 3];
		return 1;
	}

	void ReadGroup()
	{
		uint8 group[5];
		do
		{
			ULONG nRead = m_stream->Read(&group[0], 1);
			ASSERT(nRead == 1);
		}
		while (std::isspace(group[0]));

		if (group[0] == '~')
		{
			uint8 c;
			ULONG nRead = m_stream->Read(&c, 1);
			ASSERT(nRead == 1);
			ASSERT(c == '>');
			m_bfinal = true;
			return;
		}

		if (group[0] == 'z')	// special case
		{
			Output(0);
			Output(0);
			Output(0);
			Output(0);
		}
		else
		{
			ASSERT(group[0] >= 33 && group[0] <= 117);

			int n;

			for (n = 1; n < 5; n++)
			{
				do
				{
					ULONG nRead = m_stream->Read(&group[n], 1);
					ASSERT(nRead == 1);
				}
				while (std::isspace(group[n]));

				if (group[n] == '~')
					break;

				ASSERT(group[n] >= 33 && group[n] <= 117);
			}

			if (n < 5)
			{
				uint8 c;
				ULONG nRead = m_stream->Read(&c, 1);
				VERIFY(nRead == 1);
				VERIFY(c == '>');
				m_bfinal = true;
			}

			group[0] -= 33;
			group[1] -= 33;
			group[2] -= 33;
			group[3] -= 33;
			group[4] -= 33;

			uint32 dword = (uint32)group[0]*85*85*85*85 + (uint32)group[1]*85*85*85 + (uint32)group[2]*85*85 + (uint32)group[3]*85 + (uint32)group[4];

			if (n == 5)
			{
				Output(dword>>24);
				Output(dword>>16);
				Output(dword>>8);
				Output(dword>>0);
			}
			else if (n == 4)
			{
				Output(dword>>24);
				Output(dword>>16);
				Output(dword>>8);
			}
			else if (n == 3)
			{
				Output(dword>>24);
				Output(dword>>16);
			}
			else if (n == 1)
			{
				Output(dword>>24);
			}
		}
	}

	virtual ULONG Read(void* pv, ULONG cb)
	{
		if (m_bdone) return 0;

		uint8* pb = (uint8*)pv;

		ULONG n;
		for (n = 0; n < cb; n++)
		{
			if (ReadByte(pb) == 0)
			{
				m_bdone = true;
				return n;
			}

			pb++;
		}

		return n;
	}
	virtual ULONG Write(const void* pv, ULONG cb)
	{
		return 0;
	}
	virtual LONGLONG Seek(LONGLONG move, IO::SeekOrigin origin)
	{
		return 0;
	}
	virtual LONGLONG GetSize()
	{
		return 0;
	}

	virtual ISequentialByteStream* Clone() const
	{
		return NULL;
	}

protected:

	ISequentialByteStream* m_stream;

	uint8 m_outputGroup[4];
	ULONG m_outputPos;
	ULONG m_readPos;
	bool m_bfinal;
	bool m_bdone;
};

uint8 padding[32] =
{
0x28, 0xBF, 0x4E, 0x5E, 0x4E, 0x75, 0x8A, 0x41, 0x64, 0x00, 0x4E, 0x56, 0xFF, 0xFA, 0x01, 0x08,
0x2E, 0x2E, 0x00, 0xB6, 0xD0, 0x68, 0x3E, 0x80, 0x2F, 0x0C, 0xA9, 0xFE, 0x64, 0x53, 0x69, 0x7A,
};

/*
void CalculateEncryptionKey(StringA password, StringA O)
{


}
*/

class RC4
{
public:
	RC4(uint8* key, uint8 keylength)
	{
		// RC4
		{
			for (int i = 0; i < 256; i++)
			{
			  S[i] = i;
			}
		}

		{
			uint8 j = 0;
			for (int i = 0; i < 256; i++)
			{
				j = (j + S[i] + key[i % keylength]);// mod 256
				//swap(S[i],S[j]);
				/*
				S[i] ^= S[j];
				S[j] ^= S[i];
				S[i] ^= S[j];
				*/
				uint8 t = S[i];
				S[i] = S[j];
				S[j] = t;
			}
		}

		i = 0;
		j = 0;
	}

	uint8 k()
	{
		i = (i + 1);// mod 256
		j = (j + S[i]);// mod 256
		//swap(S[i],S[j])
		/*
		S[i] ^= S[j];
		S[j] ^= S[i];
		S[i] ^= S[j];
		*/
		uint8 t = S[i];
		S[i] = S[j];
		S[j] = t;

		return S[(S[i] + S[j]) & 255/* mod 256*/];
	}

	uint8 S[256];
	uint8 i;
	uint8 j;
};

class DecryptByteStream : public Object, public ISequentialByteStream
{
public:
	CTOR DecryptByteStream(ISequentialByteStream* stream, ULONG objectId, ULONG genNumber, const uint8* encryptionKey, int encryptionKeyLen)
	{
		m_stream = stream;

		// prepare to append 5 bytes to the encryption key
		uint8* buf = new uint8[encryptionKeyLen + 5];
		std::memcpy(buf, encryptionKey, encryptionKeyLen);

		// append to the encryptionKey
		uint8* x = buf + encryptionKeyLen;

		x[0] = objectId>>0;
		x[1] = objectId>>8;
		x[2] = objectId>>16;
		x[3] = genNumber>>0;
		x[4] = genNumber>>8;
/*
		x[0] = objectId>>16;
		x[1] = objectId>>8;
		x[2] = objectId>>0;
		x[3] = genNumber>>8;
		x[4] = genNumber>>0;
*/
		uint8 key[16];

		Crypt::MD5 md5;
		md5.m_stream = new MemoryByteStream(buf, encryptionKeyLen+5);
		md5.process();
		md5.GetDigest((uint32*)key);
		const int keylength = MIN(encryptionKeyLen+5, 16);

		{
			// TODO, is this for debugging reasons ??

			std::FILE* fp = std::fopen("c:\\testdecrypt", "wb");
			if (fp)
			{
				std::fwrite(buf, 1, encryptionKeyLen+5, fp);
				std::fclose(fp);
			}
		}

		m_rc4 = new RC4(key, keylength);

		m_pos = 0;
	}

	RC4* m_rc4;

	ULONG m_pos;

	virtual ULONG Read(void* pv, ULONG cb)
	{
		uint8* pb = (uint8*)pv;

		ULONG n;
		for (n = 0; n < cb; n++)
		{
			uint8 c;
			if (m_stream->Read(&c, 1) == 0)
				break;

			/*
			i = (i + 1);// mod 256
			j = (j + S[i]);// mod 256
			//swap(S[i],S[j])
			S[i] ^= S[j];
			S[j] ^= S[i];
			S[i] ^= S[j];

			*pb = c ^ S[(S[i] + S[j]) & 255];
			*/
			*pb = c ^ m_rc4->k();

			pb++;
			m_pos++;
		}

		return n;
	}
	virtual ULONG Write(const void* pv, ULONG cb)
	{
		return 0;
	}
	virtual LONGLONG Seek(LONGLONG move, IO::SeekOrigin origin)
	{
		return 0;
	}
	virtual LONGLONG GetSize()
	{
		return 0;
	}

	virtual ISequentialByteStream* Clone() const
	{
		return NULL;
	}

protected:

	ISequentialByteStream* m_stream;
};

static ISequentialByteStream* Filter(CPDFCosName* pName, ISequentialByteStream* pStream)
{
	if (*pName->GetValue() == "FlateDecode")
	{
		ZLIBDecoder* pDecoder = new ZLIBDecoder(pStream);
	//	pDecoder->AddRef();
		return pDecoder;
	}
	else if (*pName->GetValue() == "LZWDecode")
	{
		LZWByteStreamDecoder* pDecoder = new LZWByteStreamDecoder(new TIFFBitStream(pStream));
	//	pDecoder->AddRef();
		return pDecoder;
	}
	else if (*pName->GetValue() == "ASCII85Decode")
	{
		ASCII85Decode* pDecoder = new ASCII85Decode(pStream);
	//	pDecoder->AddRef();
		return pDecoder;
	}
	else
	{
		ASSERT(0);
		throw -1;
		return NULL;
	}
}

ISequentialByteStream* CPDFCosStream::OpenStream()
{
	ISequentialByteStream* pStream = OpenRawStream();

	if (m_pCosDoc->m_pEncrypt)
	{
		PDF::CPDFCosString* pFirstID = dynamic_cast<PDF::CPDFCosString*>(m_pCosDoc->m_pID->GetItem(0));
		StringA* firstID = pFirstID->GetValue();

		PDF::CPDFCosString* pO = dynamic_cast<PDF::CPDFCosString*>(m_pCosDoc->m_pEncrypt->CosDictGet(ASTR("O")));
		ASSERT(pO->GetValue()->Length() == 32);

		PDF::CPDFCosString* pU = dynamic_cast<PDF::CPDFCosString*>(m_pCosDoc->m_pEncrypt->CosDictGet(ASTR("U")));
		ASSERT(pU->GetValue()->Length() == 32);
		StringA* U = pU->GetValue();

		PDF::CPDFCosInteger* pP = dynamic_cast<PDF::CPDFCosInteger*>(m_pCosDoc->m_pEncrypt->CosDictGet(ASTR("P")));

		char* password = NULL;
		int passwordlen = 0;

		// Compute encryption key

		uint8 buf[256];
		uint8* p = buf;

		std::memcpy(p, password, passwordlen);
		p += passwordlen;

		std::memcpy(p, padding, 32-passwordlen);
		p += 32-passwordlen;

		// O(wner) entry
		std::memcpy(p, pO->GetValue()->c_str(), 32);
		p += 32;

		uint32 P = pP->GetValue();

		// P entry (low order bytes first)
		*p++ = (uint32)P;
		*p++ = (uint32)P>>8;
		*p++ = (uint32)P>>16;
		*p++ = (uint32)P>>24;

		// First entry in ID dict
		std::memcpy(p, firstID->c_str(), firstID->Length());
		p += firstID->Length();

		uint8 encryptionKey[16];
		Crypt::MD5 md5;
		md5.m_stream = new IO::MemoryByteStream(buf, p-buf);
		md5.process();
		md5.GetDigest((uint32*)encryptionKey);

		// Authenticate user password
		{
			// Encrypt the 32-byte padding string
			RC4 rc4(encryptionKey, 5);
			uint8 tpadding[32];

			for (int i = 0; i < 32; i++)
			{
				tpadding[i] = padding[i] ^ rc4.k();
			}

			{
				for (int i = 0; i < 32; i++)
				{
					TRACE("%2.2x", tpadding[i]);
				}
				TRACE("\n");
			}

			{
				for (int i = 0; i < 32; i++)
				{
					TRACE("%2.2x", (uint8)U->c_str()[i]);
				}
				TRACE("\n");
			}

			/*
				If is equal to the value of the encryption dictionary’s U entry
				(comparing on the first 16 bytes in the case of Revision 3 or greater), the password
				supplied is the correct user password.
			*/
			if (std::memcmp(tpadding, U->c_str(), 32) != 0)
			{
				TRACE("Wrong password\n");
			}
		}

		DecryptByteStream* pDecoder = new DecryptByteStream(pStream, m_id, m_genNum, encryptionKey, 5);
		//pDecoder->AddRef();
		pStream = pDecoder;

#if 0
		if (false)
		{
			uint8* buf = new uint8[657];
			pDecoder->Read(buf, 657);

			uint8* dest = new uint8[100000];

			ULONG len = 100000;
			int err = uncompress(dest, &len, buf, 657);

			FILE* fp = fopen("C:\\uncompressed", "wb");
			fwrite(dest, len, 1, fp);
			fclose(fp);

			exit(1);
		}
#endif

	}

	CPDFCosObj* pFilter = m_attributesDict->CosDictGet(ASTR("Filter"));

	if (CPDFCosArray* pArray = dynamic_cast<CPDFCosArray*>(pFilter))
	{
		int length = pArray->GetLength();

		for (int i = 0; i < length; i++)
		{
			CPDFCosObj* pFilter = pArray->GetItem(i);
			CPDFCosName* pName = dynamic_cast<CPDFCosName*>(pFilter);
			if (pName)
			{
				pStream = Filter(pName, pStream);
			}
		}
	}
	else if (CPDFCosName* pName = dynamic_cast<CPDFCosName*>(pFilter))
	{
		pStream = Filter(pName, pStream);
	}

	return pStream;
}

//virtual
void CPDFCosStream::WriteToStream(std::FILE* fp)
{
	ASSERT(m_id);	// must be indirect
	ASSERT(m_attributesDict);

	if (m_id)
	{
		m_offset = std::ftell(fp);

		std::fprintf(fp, "%ld 0 obj\r\n", m_id);
	}

	static_cast<CPDFCosDict*>(m_attributesDict)->WriteToStream(fp);

	std::fprintf(fp, "stream\r\n");

	ASSERT(0);
#if 0
	if (m_filename.Length())
	{
		FILE* srcfp = fopen(m_filename.c_str(), "rb");
		if (srcfp)
		{
			fseek(srcfp, 0, SEEK_END);
			DWORD size = ftell(srcfp);
			fseek(srcfp, 0, SEEK_SET);

			BYTE buf[1024];

			long n = 0;
			while (n < size)
			{
				long nread = 1024;
				if (n+nread > size) nread = size-n;

				std::fread(buf, nread, 1, srcfp);
				std::fwrite(buf, nread, 1, fp);

				n += nread;
			}

			std::fclose(srcfp);
		}
	}
#endif

	std::fprintf(fp, "\r\nendstream\r\n");

	if (m_id)
	{
		std::fprintf(fp, "endobj\r\n");
	}
}

CPDFCosDict* CPDFCosStream::CosStreamDict()
{
	return m_attributesDict;
}

}
}
