#include "stdafx.h"
#include "IFFParser.h"

namespace System
{

/////////////////////////////////////////////////////////////////////
// IFFParser

IFFParser::IFFParser(System::IO::ISequentialByteStream* stream)
{
	ASSERT(stream);
	m_stream = stream;
}

#if 0
IFFRESULT IFFParser::IFFErrorText(IFFRESULT errorcode, LPTSTR lpszDesc, DWORD cbDesc)
{
// Range-check the errorcode
//	if ((errorcode < IFF_BASE) errorcode = IFFERR_UNKNOWN;

	static LPTSTR errormsg[] =
	{
		"IFF - End of file, you should never see this",
		"IFF - End of context, you should never see this",
		"IFF - Unknown error, report to author",
		"IFF - Corrupted file",
		"IFF - Read/Write Error",
		"IFF - Not enough memory",
		"IFF - Client error, report to author",
		"IFF - Unknown compression",
	};

	return sprintf(lpszDesc, "%.*s", cbDesc-1, errormsg[-(errorcode-IFF_BASE)]);
}
#endif

LONGLONG IFFParser::SetFilePos(LONGLONG move, IO::SeekOrigin origin)
{
	return m_stream->Seek(move, origin);
}

IFFRESULT IFFParser::IFFDescendChunk(IFFCHUNK* lpck)
{
	lpck->flags = 0;	// Read

	ULONG	len = IFFReadChunkBytes(lpck, IFFCHUNKSIZE);

	if (len == 0)
		return IFF_EOF;
	else if (len != IFFCHUNKSIZE)
		return IFFERR_READWRITE;

	lpck->ckID = BigEndian32(lpck->ckID);
	lpck->ckSize = BigEndian32(lpck->ckSize);

	lpck->dataOffset = SetFilePos(0, IO::STREAM_SEEK_CUR);
	lpck->grpID = 0;

	if (lpck->ckID == ID_FORM)
	{
		if (IFFReadChunkBytes(&lpck->grpID, sizeof(ID)) != sizeof(ID))
			return IFFERR_READWRITE;
		lpck->grpID = BigEndian32(lpck->grpID);
		return IFF_EOC;
	}

	return IFF_OK;
}

LONG IFFParser::IFFCreateChunk(IFFCHUNK* lpck)
{
	lpck->flags = 1;	// Created

	IFFCHUNK ck;
	ck.ckID = BigEndian32(lpck->ckID);
	ck.ckSize = BigEndian32(lpck->ckSize);

	m_stream->Write(&ck, IFFCHUNKSIZE);
	lpck->dataOffset = SetFilePos(0, IO::STREAM_SEEK_CUR);

	if (lpck->ckID == ID_FORM)
	{
		ULONG grpID = BigEndian32(lpck->grpID);
		m_stream->Write(&grpID, 4);
	}

	return IFF_OK;
}

IFFRESULT IFFParser::IFFAscendChunk(IFFCHUNK* lpck)
{
	ULONGLONG pos;
	pos = SetFilePos(0, IO::STREAM_SEEK_CUR);	// Current position

	if (lpck->flags == 0)
	{
		int32 offset = lpck->ckSize-(pos-lpck->dataOffset);

		if (lpck->ckSize & 1) offset++;	// Word-aligned chunks

		/*if (*/SetFilePos(offset, IO::STREAM_SEEK_CUR);// == 0xffffffff)
		/*
			return IFFERR_READWRITE;
		else
			return IFF_OK;
			*/
	}
	else
	{
		uint32 cksize = pos - lpck->dataOffset;

		if (lpck->ckSize == 0)	// Unknown size data at time of chunk creation
		{
			lpck->ckSize = cksize;
			cksize = BigEndian32(cksize);

			SetFilePos(lpck->dataOffset-4, IO::STREAM_SEEK_SET);
			IFFWriteChunkBytes(&cksize, 4);	// Write the chunk length

			SetFilePos(pos, IO::STREAM_SEEK_SET);
		}

		if (cksize & 1)
		{
			uint8 padbyte = 0;
			IFFWriteChunkBytes(&padbyte, 1);
		}
	}

	return IFF_OK;
}

uint32 IFFParser::IFFReadChunkBytes(void* lpBuffer, uint32 nBytes)
{
	return m_stream->Read(lpBuffer, nBytes);
}

uint32 IFFParser::IFFWriteChunkBytes(const void* lpBuffer, uint32 nBytes)
{
	return m_stream->Write(lpBuffer, nBytes);
}

}
