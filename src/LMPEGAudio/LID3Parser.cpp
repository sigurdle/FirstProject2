// LID3Parser.cpp : Implementation of CLID3Parser
#include "stdafx.h"
#include "LMPEGAudio.h"
#include "LID3Parser.h"

/////////////////////////////////////////////////////////////////////////////
// CLID3Parser

HRESULT CLID3Parser::CInputPin::CompleteConnect(ILPin *pPin)
{
	HRESULT hr;
	hr = CLBasePinImpl::CompleteConnect(pPin);
	if (FAILED(hr)) return hr;

	ULONG nRead;
	BYTE tag[3];
	m_stream->Read(tag, 3, &nRead);
	if (nRead != 3)
	{
		return E_FAIL;
	}

	// "ID3"
	if (tag[0] != 0x49 ||
		tag[1] != 0x44 ||
		tag[2] != 0x33)
	{
		return E_FAIL;
	}

	CBitStream bitstream(m_stream);

	BYTE major = bitstream.readinteger(8);
	BYTE minor = bitstream.readinteger(8);

	if (major > 4)
		return E_FAIL;

	BYTE flags = bitstream.readinteger(8);

	BYTE size[4];
	size[0] = bitstream.readinteger(8);
	size[1] = bitstream.readinteger(8);
	size[2] = bitstream.readinteger(8);
	size[3] = bitstream.readinteger(8);

	DWORD size4 = (DWORD)size[3] | ((DWORD)size[2]<<7) | ((DWORD)size[1]<<14) | ((DWORD)size[0]<<21);

	m_dataOffset = 10+size4;

	LARGE_INTEGER li;
	li.QuadPart = m_dataOffset;
	m_stream->Seek(li, STREAM_SEEK_SET, NULL);

	return S_OK;
}
