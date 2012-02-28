#include "stdafx.h"
#include "DOK5.h"

// General stream functions

ULONG Read(IStream* stream, void* pv, ULONG cb)
{
	ULONG nRead;
	stream->Read(pv, cb, &nRead);
	return nRead;
}

ULONG Write(IStream* stream, void* pv, ULONG cb)
{
	ULONG nWritten;
	stream->Write(pv, cb, &nWritten);
	return nWritten;
}

ULONG GetPos(IStream* stream)
{
	ULARGE_INTEGER pos;
	LARGE_INTEGER li;
	li.QuadPart = 0;
	stream->Seek(li, STREAM_SEEK_CUR, &pos);
	return (ULONG)pos.QuadPart;
}

ULONG Seek(IStream* stream, LONG offset, DWORD dwOrigin)
{
	ULARGE_INTEGER pos;
	LARGE_INTEGER li;
	li.QuadPart = offset;
	HRESULT hr = stream->Seek(li, dwOrigin, &pos);
	if (FAILED(hr))
		return 0xffffffff;
	return (ULONG)pos.QuadPart;
}


//////////////////////////////////////////////////////////////
// DOK5 functions

long ReadVECTOR(IStream* pStream, float vf[3])
{
	DWORD	v[3];
	Read(pStream, v, 12);

	*((DWORD*)&vf[0]) = ENDIANLONG(v[0]);
	*((DWORD*)&vf[1]) = ENDIANLONG(v[1]);
	*((DWORD*)&vf[2]) = ENDIANLONG(v[2]);

	return 12;
}

long WriteVECTOR(IStream* pStream, float vf[3])
{
	DWORD	v[3];

	v[0] = *((DWORD*)&vf[0]);
	v[1] = *((DWORD*)&vf[1]);
	v[2] = *((DWORD*)&vf[2]);
 
	v[0] = ENDIANLONG(v[0]);
	v[1] = ENDIANLONG(v[1]);
	v[2] = ENDIANLONG(v[2]);

	Write(pStream, v, 12);

	return 12;
}

long ReadFLOAT(IStream* pStream, float* vf)
{
	DWORD	v;
	Read(pStream, &v, 4);
	*((DWORD*)vf) = ENDIANLONG(v);
	return 4;
}

long ReadTIME(IStream* pStream, TIME* t)
{
	DWORD	v[2];
	Read(pStream, v, 8);

	*((DWORD*)&t->nominator) = ENDIANLONG(v[0]);
	*((DWORD*)&t->denominator) = ENDIANLONG(v[1]);

	return 8;
}

long WriteFLOAT(IStream* pStream, float* vf)
{
	DWORD	v = ENDIANLONG(*((DWORD*)vf));
	Write(pStream, &v, 4);
	return 4;
}

LONG CreateChunk(IStream* pStream, CHUNKHDR* lpck)
{
	lpck->dwFlags = 1;	// Created

	DWORD v[2];
	v[0] = lpck->type + (lpck->level << 24);
	v[0] = ENDIANLONG(v[0]);
	v[1] = ENDIANLONG(lpck->size);	// Size

	Write(pStream, v, 8);
	lpck->offset = GetPos(pStream);

	return 4;
}

long WriteTIME(IStream* pStream, TIME* t)
{
	DWORD	v[2];

	v[0] = ENDIANLONG(*((DWORD*)&t->nominator));
	v[1] = ENDIANLONG(*((DWORD*)&t->denominator));

	Write(pStream, v, 8);

	return 8;
}

long ReadChunkHeader(IStream* pStream, CHUNKHDR* ckhdr)
{
	ckhdr->dwFlags = 0;

	LONG v[2];

	if (Read(pStream, v, 8) != 8) return 1;

	v[0] = ENDIANLONG(v[0]);
	v[1] = ENDIANLONG(v[1]);

	ckhdr->level = v[0] >> 24;
	ckhdr->type = v[0] - (ckhdr->level << 24);
	ckhdr->size = v[1];

	ckhdr->offset = GetPos(pStream);

	return 0;
}

long LeaveChunk(IStream* pStream, CHUNKHDR* lpck)
{
	DWORD pos = GetPos(pStream);

	if (lpck->dwFlags == 0)
	{
		LONG	offset = lpck->size - (pos - lpck->offset);
		if (Seek(pStream, offset, STREAM_SEEK_CUR) == 0xffffffff)
			return 1;
		else
			return 0;
	}
	else
	{
		DWORD	cksize = pos - lpck->offset;

		if (lpck->size == 0)	// Unknown size data at time of chunk creation
		{
			cksize = ENDIANLONG(cksize);

			Seek(pStream, lpck->offset - 4, STREAM_SEEK_SET);
			Write(pStream, &cksize, 4);	// Write the chunk length

			Seek(pStream, pos, STREAM_SEEK_SET);
		}

		return 0;
	}
}
