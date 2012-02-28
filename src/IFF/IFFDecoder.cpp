// IFFDecoder.cpp : Implementation of CIFFDecoder
#include "stdafx.h"
#include "IFF.h"
#include "IFFDecoder.h"

//using namespace System;
//using namespace System::IO;

/*
 GetClassFile() patterns

FORMxxxxILBM
464F524D00000000494C424D

FORMxxxxANIM
464F524D00000000414E494D

FORMxxxx8SVX
464F524D0000000038535658

FORMxxxxAIFF
464F524D0000000041494646

*/

#include "IFFFormILBM.h"
#include "IFFFormANIM.h"
#include "IFFForm8SVX.h"
#include "IFFFormAIFF.h"

/////////////////////////////////////////////////////////////////////////////
// CIFFDecoder::CInputPin

#if 0	// Had this
STDMETHODIMP CIFFDecoder::CInputPin::ReceiveConnection(ILPin* pConnector, ILMediaType* pMediaType)
{
	HRESULT hr = S_OK;

	CLPinImpl::ReceiveConnection(pConnector, pMediaType);

	CComQIPtr<ILByteStream> stream = m_connectedTo;

	m_pFilter->m_pOutputPin->m_stream = stream;

	hr = m_pFilter->Open();

	return hr;
}
#endif

namespace LMedia
{

/////////////////////////////////////////////////////////////////////////////
// CIFFDecoder

HRESULT CIFFDecoder::Open()
{
	IFFCHUNK	formck;// = *(LPIFFCHUNK)r->firstBytes;
	m_pOutputPin->IFFDescendChunk(&formck);

	if (formck.ckID != ID_FORM)
	{
		return E_FAIL;
	}

//	result = FORMAT_UNKNOWN;	// Assume unknown format

	ILBaseFilter* form;

	if (formck.grpID == ID_ANIM)
	{
		CIFFFormANIM* p = new CIFFFormANIM;
		form = p;	// This AddRefs
	}
	else if (formck.grpID == ID_ILBM)
	{
		CIFFFormILBM* p = new CIFFFormILBM;
		form = p;	// This AddRefs
	}
	else if (formck.grpID == ID_8SVX)
	{
		CIFFForm8SVX* p = new CIFFForm8SVX;
		form = p;	// This AddRefs
	}
	else if (formck.grpID == ID_AIFF)
	{
		CIFFFormAIFF* p = new CIFFFormAIFF;
		form = p;	// This AddRefs
	}
	else
	{
		goto cleanup;
	}

	if (form)
	{
		m_pFilterGraph->AddFilter(form);

		ATLASSERT(0);
#if 0
		CComPtr<ILPin> inpin;
		form->GetPin(0, &inpin);
		m_pOutputPin->Connect(inpin, NULL);
#endif
	}

cleanup:

#if 0
	if (result < IFF_EOC)
	{
	 	IFFErrorText(result, r->errorMsg, sizeof(r->errorMsg));
		result = PLUGIN_MSG;
	}
	else if (result <= IFF_BASE)
	{
		result = PLUGIN_OKAY;
	}

	return result;
#endif

	return S_OK;
}

/*
int GetBitCount(int imode)
{
	switch (imode)
	{
	case IMODE_MONO:		return 1;

	case IMODE_INDEXED4: return 4;

	case IMODE_INDEXED8: return 8;

	case IMODE_RGB15:
	case IMODE_RGB16:		return 1;

	case IMODE_RGB8:
	case IMODE_BGR8:		return 24;
	}

	return 0;
}
*/


IFFRESULT CIFFDecoder::COutputPin::IFFErrorText(IFFRESULT errorcode, LPTSTR lpszDesc, DWORD cbDesc)
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

HRESULT CIFFDecoder::COutputPin::SetFilePos(LARGE_INTEGER move, DWORD dwOrigin, ULARGE_INTEGER* newpos)
{
	return m_stream->Seek(move, dwOrigin, newpos);
}

IFFRESULT CIFFDecoder::COutputPin::IFFDescendChunk(LPIFFCHUNK lpck)
{
	lpck->dwFlags = 0;	// Read

	ULONG	len = IFFReadChunkBytes(lpck, IFFCHUNKSIZE);

	if (len == 0)
		return IFF_EOF;
	else if (len != IFFCHUNKSIZE)
		return IFFERR_READWRITE;

	lpck->ckSize = ENDIANLONG(lpck->ckSize);

	LARGE_INTEGER li;
	li.QuadPart = 0;
	lpck->dwDataOffset = SetFilePos(li, System::IO::STREAM_SEEK_CUR);
	lpck->grpID = 0;

	if (lpck->ckID == ID_FORM)
	{
		if (IFFReadChunkBytes(&lpck->grpID, sizeof(ID)) != sizeof(ID)) return IFFERR_READWRITE;
		return IFF_EOC;
	}

	return IFF_OK;
}

LONG CIFFDecoder::COutputPin::IFFCreateChunk(LPIFFCHUNK lpck)
{
#if 0
	lpck->dwFlags = 1;	// Created

	lpck->ckSize = ENDIANLONG(lpck->ckSize);

	g->WriteF(g->file, lpck, IFFCHUNKSIZE);
	lpck->dwDataOffset = g->SetFilePos(g->file, 0, System::IO::STREAM_SEEK_CUR);

	if (lpck->ckID == ID_FORM) g->WriteF(g->file, &lpck->grpID, 4);
#endif

	return IFF_OK;
}

IFFRESULT CIFFDecoder::COutputPin::IFFAscendChunk(LPIFFCHUNK lpck)
{
	LARGE_INTEGER li;
	li.QuadPart = 0;
	ULONGLONG pos;
	pos = SetFilePos(li, System::IO::STREAM_SEEK_CUR);	// Current postition

	if (lpck->dwFlags == 0)
	{
		LONG	offset = lpck->ckSize-(pos-lpck->dwDataOffset);

		if (lpck->ckSize & 1) offset++;	// Word-aligned chunks

		li.QuadPart = offset;
		/*if (*/SetFilePos(li, STREAM_SEEK_CUR);// == 0xffffffff)
		/*
			return IFFERR_READWRITE;
		else
			return IFF_OK;
			*/
	}
	else
	{
		BYTE	padbyte = 0;
		DWORD	cksize = pos-lpck->dwDataOffset;

		if (lpck->ckSize == 0)	// Unknown size data at time of chunk creation
		{
			lpck->ckSize = ENDIANLONG(cksize);

			LARGE_INTEGER li;
			li.QuadPart = lpck->dwDataOffset-4;
			SetFilePos(li, STREAM_SEEK_SET);
			IFFWriteChunkBytes(&lpck->ckSize, 4);	// Write the chunk length

			SetFilePos(*(LARGE_INTEGER*)&pos, STREAM_SEEK_SET);
		}

		if (cksize & 1) IFFWriteChunkBytes(&padbyte, 1);

	}

	return IFF_OK;
}

DWORD CIFFDecoder::COutputPin::IFFReadChunkBytes(LPVOID lpBuffer, DWORD dwBytes)
{
	ULONG nRead;
	m_stream->Read(lpBuffer, dwBytes, &nRead);
	return nRead;
}

DWORD CIFFDecoder::COutputPin::IFFWriteChunkBytes(LPVOID lpBuffer, DWORD dwBytes)
{
	ULONG nWritten = 0;
#if 0
	m_stream->Write(lpBuffer, dwBytes, &nWritten);
#endif
	return nWritten;
}

/////////////////////////////////////////////////////////////////////
// CIFFParser

CIFFParser::CIFFParser(ILByteStream* stream)
{
	ATLASSERT(stream);
	m_stream = stream;
}

IFFRESULT CIFFParser::IFFErrorText(IFFRESULT errorcode, LPTSTR lpszDesc, DWORD cbDesc)
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

HRESULT CIFFParser::SetFilePos(LARGE_INTEGER move, DWORD dwOrigin, ULARGE_INTEGER* newpos)
{
	return m_stream->Seek(move, dwOrigin, newpos);
}

IFFRESULT CIFFParser::IFFDescendChunk(LPIFFCHUNK lpck)
{
	lpck->dwFlags = 0;	// Read

	ULONG	len = IFFReadChunkBytes(lpck, IFFCHUNKSIZE);

	if (len == 0)
		return IFF_EOF;
	else if (len != IFFCHUNKSIZE)
		return IFFERR_READWRITE;

	lpck->ckSize = ENDIANLONG(lpck->ckSize);

	LARGE_INTEGER li;
	li.QuadPart = 0;
	lpck->dwDataOffset = SetFilePos(li, System::IO::STREAM_SEEK_CUR);
	lpck->grpID = 0;

	if (lpck->ckID == ID_FORM)
	{
		if (IFFReadChunkBytes(&lpck->grpID, sizeof(ID)) != sizeof(ID)) return IFFERR_READWRITE;
		return IFF_EOC;
	}

	return IFF_OK;
}

LONG CIFFParser::IFFCreateChunk(LPIFFCHUNK lpck)
{
#if 0
	lpck->dwFlags = 1;	// Created

	lpck->ckSize = ENDIANLONG(lpck->ckSize);

	g->WriteF(g->file, lpck, IFFCHUNKSIZE);
	lpck->dwDataOffset = g->SetFilePos(g->file, 0, System::IO::STREAM_SEEK_CUR);

	if (lpck->ckID == ID_FORM) g->WriteF(g->file, &lpck->grpID, 4);
#endif

	return IFF_OK;
}

IFFRESULT CIFFParser::IFFAscendChunk(LPIFFCHUNK lpck)
{
	LARGE_INTEGER li;
	li.QuadPart = 0;
	ULONGLONG pos;
	pos = SetFilePos(li, System::IO::STREAM_SEEK_CUR);	// Current postition

	if (lpck->dwFlags == 0)
	{
		LONG	offset = lpck->ckSize-(pos-lpck->dwDataOffset);

		if (lpck->ckSize & 1) offset++;	// Word-aligned chunks

		li.QuadPart = offset;
		/*if (*/SetFilePos(li, STREAM_SEEK_CUR);// == 0xffffffff)
		/*
			return IFFERR_READWRITE;
		else
			return IFF_OK;
			*/
	}
	else
	{
		BYTE	padbyte = 0;
		DWORD	cksize = pos-lpck->dwDataOffset;

		if (lpck->ckSize == 0)	// Unknown size data at time of chunk creation
		{
			lpck->ckSize = ENDIANLONG(cksize);

			LARGE_INTEGER li;
			li.QuadPart = lpck->dwDataOffset-4;
			SetFilePos(li, STREAM_SEEK_SET);
			IFFWriteChunkBytes(&lpck->ckSize, 4);	// Write the chunk length

			SetFilePos(*(LARGE_INTEGER*)&pos, STREAM_SEEK_SET);
		}

		if (cksize & 1) IFFWriteChunkBytes(&padbyte, 1);

	}

	return IFF_OK;
}

DWORD CIFFParser::IFFReadChunkBytes(LPVOID lpBuffer, DWORD dwBytes)
{
	ULONG nRead;
	m_stream->Read(lpBuffer, dwBytes, &nRead);
	return nRead;
}

DWORD CIFFParser::IFFWriteChunkBytes(LPVOID lpBuffer, DWORD dwBytes)
{
	ULONG nWritten = 0;
#if 0
	m_stream->Write(lpBuffer, dwBytes, &nWritten);
#endif
	return nWritten;
}

}	// LMedia
