// TextData.cpp : Implementation of CTextData
#include "stdafx.h"
#include "TextDataMod.h"
#include "TextData.h"

/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */

static int gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */

/* ===========================================================================
     Read a byte from a gz_stream; update next_in and avail_in. Return EOF
   for end of file.
   IN assertion: the stream s has been sucessfully opened for reading.
*/
int get_byte(gz_stream *s)
{
	if (s->z_eof) return EOF;
	if (s->stream.avail_in == 0)
	{
		errno = 0;
		s->file->Read(s->inbuf, s->bufsize, (ULONG*)&s->stream.avail_in);
		if (s->stream.avail_in == 0)
		{
			s->z_eof = 1;
			//if (ferror(s->file)) s->z_err = Z_ERRNO;
			return EOF;
		}
		s->stream.next_in = s->inbuf;
	}
	s->stream.avail_in--;
	return *(s->stream.next_in)++;
}

/* ===========================================================================
      Check the gzip header of a gz_stream opened for reading. Set the stream
    mode to transparent if the gzip magic header is not present; set s->err
    to Z_DATA_ERROR if the magic header is present but the rest of the header
    is incorrect.
    IN assertion: the stream s has already been created sucessfully;
       s->stream.avail_in is zero for the first time, but may be non-zero
       for concatenated .gz files.
*/

void check_header(gz_stream *s)
{
    int method; /* method byte */
    int flags;  /* flags byte */
    uInt len;
    int c;

    /* Check the gzip magic header */
    for (len = 0; len < 2; len++) {
	c = get_byte(s);
	if (c != gz_magic[len]) {
	    if (len != 0) s->stream.avail_in++, s->stream.next_in--;
	    if (c != EOF) {
		s->stream.avail_in++, s->stream.next_in--;
		s->transparent = 1;
	    }
	    s->z_err = s->stream.avail_in != 0 ? Z_OK : Z_STREAM_END;
	    return;
	}
    }
    method = get_byte(s);
    flags = get_byte(s);
    if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
	s->z_err = Z_DATA_ERROR;
	return;
    }

    /* Discard time, xflags and OS code: */
    for (len = 0; len < 6; len++) (void)get_byte(s);

    if ((flags & EXTRA_FIELD) != 0) { /* skip the extra field */
	len  =  (uInt)get_byte(s);
	len += ((uInt)get_byte(s))<<8;
	/* len is garbage if EOF but the loop below will quit anyway */
	while (len-- != 0 && get_byte(s) != EOF) ;
    }
    if ((flags & ORIG_NAME) != 0) { /* skip the original file name */
	while ((c = get_byte(s)) != 0 && c != EOF) ;
    }
    if ((flags & COMMENT) != 0) {   /* skip the .gz file comment */
	while ((c = get_byte(s)) != 0 && c != EOF) ;
    }
    if ((flags & HEAD_CRC) != 0) {  /* skip the header crc */
	for (len = 0; len < 2; len++) (void)get_byte(s);
    }
    s->z_err = s->z_eof ? Z_DATA_ERROR : Z_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTextData

VARIANT_BOOL CTextData::loadBuffer(BYTE* data, long size)
{
	WORD texttype = 0;

	if (!(size & 1))	// Odd-sized files are never unicode
	{
		if (size >= 2)
		{
			BYTE b1 = data[0];
			BYTE b2 = data[1];

			WORD b12 = (b1) | (b2<<8);

			if (b12 == 0xfeff || b12 == 0xfffe)
			{
				texttype = b12;
			}
		}
	}

	if (texttype == 0)	// ansi 8-bit
	{
		BSTR bstr = SysAllocStringLen(NULL, size);
		if (bstr)
		{
			int j = 0;
			int pos = 0;
			while (pos < size)
			{
				int c = data[pos++];
				if (c != '\r')
					bstr[j++] = c;
			}

			m_textData = SysAllocStringLen(bstr, j);
			SysFreeString(bstr);

			return VARIANT_TRUE;
		}
	}
	else if (texttype == 0xfeff)	// unicode 16-bit
	{
		int nwchars = (size-2)/2;
		BSTR bstr = SysAllocStringLen(NULL, nwchars);
		if (bstr)
		{
			int j = 0;
		//	WCHAR ch;

			WCHAR* wdata = (WCHAR*)data;
			wdata++;
			int pos = 0;

			while (pos < nwchars)
			{
				WCHAR ch = wdata[pos++];
				if (ch != '\r')
					bstr[j++] = ch;
			}

			m_textData = SysAllocStringLen(bstr, j);
			SysFreeString(bstr);

			return VARIANT_TRUE;
		}
	}
	else if (texttype == 0xfffe)	// unicode big endian 16-bit
	{
		int nwchars = (size-2)/2;
		BSTR bstr = SysAllocStringLen(NULL, nwchars);
		if (bstr)
		{
			int j = 0;
		//	WCHAR ch;

			WCHAR* wdata = (WCHAR*)data;
			wdata++;
			int pos = 0;

			while (pos < nwchars)
			{
				WCHAR ch = wdata[pos++];
				ch = (ch>>8) | (ch<<8);	// swap bytes
				if (ch != '\r')
					bstr[j++] = ch;
			}

			m_textData = SysAllocStringLen(bstr, j);
			SysFreeString(bstr);

			return VARIANT_TRUE;
		}
	}
	else
		ATLASSERT(0);

	return VARIANT_FALSE;
}

//////////////////////////
/// IBindStatusCallback

STDMETHODIMP CTextData::OnStartBinding( 
													/* [in] */ DWORD dwReserved,
													/* [in] */ IBinding __RPC_FAR *pib)
{
	return S_OK;
}

STDMETHODIMP CTextData::GetPriority(/* [out] */ LONG __RPC_FAR *pnPriority)
{
	return S_OK;
}

STDMETHODIMP CTextData::OnLowResource(/* [in] */ DWORD reserved)
{
	return S_OK;
}

STDMETHODIMP CTextData::OnProgress( 
											  /* [in] */ ULONG ulProgress,
											  /* [in] */ ULONG ulProgressMax,
											  /* [in] */ ULONG ulStatusCode,
											  /* [in] */ LPCWSTR szStatusText)
{
	return S_OK;
}

STDMETHODIMP CTextData::OnStopBinding( 
												  /* [in] */ HRESULT hresult,
												  /* [unique][in] */ LPCWSTR szError)
{
	return S_OK;
}

STDMETHODIMP CTextData::GetBindInfo( 
												/* [out] */ DWORD __RPC_FAR *grfBINDF,
												/* [unique][out][in] */ BINDINFO __RPC_FAR *pbindinfo)
{
	DWORD cbSize = pbindinfo->cbSize;        
	memset(pbindinfo,0,cbSize);
	pbindinfo->cbSize = cbSize;

	*grfBINDF = 0;
//	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

//	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

	return S_OK;
}

HRESULT CTextData::ReadStream(IStream* stm, DWORD dwSize, ULONG* pdwRead)
{
	if (m_gz.inbuf)
	{
		free(m_gz.inbuf);
		m_gz.inbuf = NULL;
	}

	//DWORD dwSize = dwSizeTotal - m_bufferlen;

	m_gz.inbuf = (BYTE*)malloc(dwSize);
	m_gz.bufsize = dwSize;
	if (m_gz.inbuf == NULL)
	{
		return E_OUTOFMEMORY;
	}

	ULONG dwRead;
	stm->Read(m_gz.inbuf, dwSize, &dwRead);
	*pdwRead = dwRead;

	m_gz.stream.next_in = m_gz.inbuf;
	m_gz.stream.avail_in = dwRead;

	if (m_bufferdata == NULL)	// First time
	{
		m_bufferdata = (BYTE*)malloc(0);

		if (dwSize > 0)
			check_header(&m_gz); /* skip the .gz header */
	}

	if (m_gz.transparent)
	{
		m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + dwRead);
		if (m_bufferdata == NULL)
		{
			return E_OUTOFMEMORY;
		}

		memcpy(m_bufferdata+m_bufferlen, m_gz.inbuf, dwRead);

		m_bufferlen += dwRead;
	}
	else
	{
		while (m_gz.stream.avail_in > 0)
		{
			m_gz.stream.avail_out = 1024;
			m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + 1024);
			if (m_bufferdata == NULL)
			{
				return E_OUTOFMEMORY;
			}

			m_gz.stream.next_out = m_bufferdata+m_bufferlen;

			m_gz.z_err = inflate(&m_gz.stream, Z_NO_FLUSH);
			
			if (m_gz.z_err < 0)
			{
				return E_FAIL;
			}

			m_bufferlen = m_gz.stream.total_out;

			if (m_gz.z_err == Z_STREAM_END)
			{
		    /* Check CRC and original size */
		    //m_gz->crc = crc32(m_gz->crc, start, (uInt)(m_gz.stream.next_out - start));

			 return S_OK;
			}

			/*
			if (zresult != 0)
				return S_OK;
				*/
		}
	}

	free(m_gz.inbuf);
	m_gz.inbuf = NULL;

	return S_OK;
}

STDMETHODIMP CTextData::OnDataAvailable( 
													 /* [in] */ DWORD grfBSCF,
													 /* [in] */ DWORD dwSizeTotal,
													 /* [in] */ FORMATETC __RPC_FAR *pformatetc,
													 /* [in] */ STGMEDIUM __RPC_FAR *pstgmed)
{
	DWORD dwSize = dwSizeTotal - m_nReadInput;

	ULONG nRead;
	HRESULT hr = ReadStream(pstgmed->pstm, dwSize, &nRead);
	if (FAILED(hr))
		return hr;

	m_nReadInput += nRead;

	return hr;
}

STDMETHODIMP CTextData::OnObjectAvailable( 
														/* [in] */ REFIID riid,
														/* [iid_is][in] */ IUnknown __RPC_FAR *punk)
{
	return E_NOTIMPL;
}

//////////////////////
/*
void CTextData::OnData(CBindStatusCallback<CTextData>* pbsc, BYTE* pBytes, DWORD dwSize)
{
	if (pBytes)
	{
		m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + dwSize);
		if (m_bufferdata)
		{
			MessageBeep(-1);
			CopyMemory(m_bufferdata+m_bufferlen, pBytes, dwSize);
			m_bufferlen += dwSize;
		}
	}
	else
	{
		SetEvent(m_hEvent);
	}
}
*/

// IPersistStream

STDMETHODIMP CTextData::Load(/* [unique][in] */ IStream *pStm)
{
	m_nReadInput = 0;

	m_bufferlen = 0;
	m_bufferdata = NULL;

	memset(&m_gz, 0, sizeof(m_gz));
	inflateInit2(&m_gz.stream, -MAX_WBITS);

	DWORD bufsize = 32768;

	while (1)
	{
		ULONG dwRead;
		ReadStream(pStm, bufsize, &dwRead);

		m_nReadInput += dwRead;
 
		if (dwRead < bufsize)
			break;
	}

	inflateEnd(&m_gz.stream);
	free(m_gz.inbuf);
	m_gz.inbuf = NULL;

	loadBuffer(m_bufferdata, m_bufferlen);

	return S_OK;

#if 0
	m_bufferlen = 0;
	m_bufferdata = (BYTE*)malloc(0);

	while (1)
	{
		m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + 1024);

		ULONG dwRead;
		pStm->Read(m_bufferdata+m_bufferlen, 1024, &dwRead);

		m_bufferlen += dwRead;

		if (dwRead < 1024)
			break;
	}

	loadBuffer(m_bufferdata, m_bufferlen);
#endif

	return S_OK;
}

// IPersistMoniker
STDMETHODIMP CTextData::Load( 
      /* [in] */ BOOL fFullyAvailable,
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc,
      /* [in] */ DWORD grfMode)
{
	HRESULT hr;

	CComPtr<IBindCtx> bindctx = pibc;
//	hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
//	if (SUCCEEDED(hr))
	{
		LPOLESTR displayName;
		pimkName->GetDisplayName(pibc, NULL, &displayName);
		m_url = displayName;
		CoTaskMemFree(displayName);

		CComPtr<IBindStatusCallback> oldcallback;
		hr = RegisterBindStatusCallback(bindctx, this, &oldcallback, 0);
		if (SUCCEEDED(hr))
		{
			m_bufferlen = 0;
			m_bufferdata = NULL;

			m_nReadInput = 0;

			memset(&m_gz, 0, sizeof(m_gz));
			inflateInit2(&m_gz.stream, -MAX_WBITS);

			CComPtr<IStream> stream;
			hr = pimkName->BindToStorage(bindctx, NULL, IID_IStream, (void**)&stream);

			inflateEnd(&m_gz.stream);
			free(m_gz.inbuf);
			m_gz.inbuf = NULL;

			if (SUCCEEDED(hr))
			{
				loadBuffer(m_bufferdata, m_bufferlen);

				return S_OK;
			}
		}
	}

	return hr;
}

STDMETHODIMP CTextData::Save( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pbc,
      /* [in] */ BOOL fRemember)
{
	  return S_OK;
}
  
STDMETHODIMP CTextData::SaveCompleted( 
      /* [in] */ IMoniker *pimkName,
      /* [in] */ LPBC pibc)
{
	  return S_OK;
}
  
  STDMETHODIMP CTextData::GetCurMoniker( 
      /* [out] */ IMoniker **ppimkName)
{
	  return S_OK;
}

//////

STDMETHODIMP CTextData::load(BSTR pathName)
{
	if (m_textData)
	{
		SysFreeString(m_textData);
		m_textData = NULL;
	}

	m_bufferlen = 0;
	m_bufferdata = NULL;

	CComPtr<IMoniker> moniker;
	HRESULT hr;

	hr = CreateURLMoniker(NULL, pathName, &moniker);
	if (SUCCEEDED(hr))
	{
		CComPtr<IBindCtx> bindctx;
		hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
		if (SUCCEEDED(hr))
		{
			CComPtr<IBindStatusCallback> oldcallback;
			hr = RegisterBindStatusCallback(bindctx, this, &oldcallback, 0);
			if (SUCCEEDED(hr))
			{
				m_bufferlen = 0;
				m_bufferdata = NULL;

				m_nReadInput = 0;

				memset(&m_gz, 0, sizeof(m_gz));
				inflateInit2(&m_gz.stream, -MAX_WBITS);

				CComPtr<IStream> stream;
				hr = moniker->BindToStorage(bindctx, NULL, IID_IStream, (void**)&stream);

				inflateEnd(&m_gz.stream);
				free(m_gz.inbuf);
				m_gz.inbuf = NULL;

				if (SUCCEEDED(hr))
				{
					loadBuffer(m_bufferdata, m_bufferlen);
				}

				/*
				m_bufferlen = 0;
				m_bufferdata = NULL;//(BYTE*)malloc(0);

				CComPtr<IStream> stream;
				hr = moniker->BindToStorage(bindctx, NULL, IID_IStream, (void**)&stream);
				if (SUCCEEDED(hr))
				{
					*success = loadBuffer(m_bufferdata, m_bufferlen);
				}
				*/
			}
		}
	}

	m_url = pathName;// ?? what if the real url isn't the same
							// maybe loading from cache or something

	return hr;
}

STDMETHODIMP CTextData::loadByteArray(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success)
{
	if (success == NULL) return E_POINTER;

	*success = VARIANT_FALSE;

	BYTE* data;
	HRESULT hr = SafeArrayAccessData(dataArray, (void**)&data);
	if (SUCCEEDED(hr))
	{
		*success = loadBuffer(data, dataArray->rgsabound[0].cElements);
		SafeArrayUnaccessData(dataArray);
	}

	return S_OK;
}

STDMETHODIMP CTextData::get_data(BSTR *pVal)
{
	*pVal = m_textData;
	return S_OK;
}

STDMETHODIMP CTextData::put_data(BSTR newVal)
{
	if (m_lockCount == 0)
	{
		if (m_textData) SysFreeString(m_textData);

		m_textData = newVal;

		Fire_contentchanged();
	}

	return S_OK;
}

STDMETHODIMP CTextData::setData(BSTR data)
{
	if (m_lockCount == 0)
	{
		if (m_textData) SysFreeString(m_textData);
		m_textData = SysAllocString(data);

		Fire_contentchanged();
	}

	return S_OK;
}

STDMETHODIMP CTextData::get_len(long *pVal)
{
	*pVal = SysStringLen(m_textData);//m_textLen;
	return S_OK;
}

STDMETHODIMP CTextData::insertText(long offset, BSTR data, long len)
{
	if (m_lockCount == 0)
	{
		if (len > 0)
		{
			int oldlen = SysStringLen(m_textData);
			ATLASSERT(offset <= oldlen);

			BSTR newdata = SysAllocStringLen(NULL, oldlen+len);

			memcpy(newdata, m_textData, offset*2);
			memcpy(newdata + offset, data, len*2);
			memcpy(newdata + offset + len, m_textData + offset, (oldlen - offset)*2);

			SysFreeString(m_textData);
			m_textData = newdata;

			Fire_insertedtext(offset, len);
		}
	}

	return S_OK;
}

STDMETHODIMP CTextData::deleteText(long offset, long len)
{
	if (len > 0)
	{
		if (m_lockCount == 0)
		{
			int oldlen = SysStringLen(m_textData);
			ATLASSERT(offset+len <= oldlen);

			BSTR newdata = SysAllocStringLen(NULL, oldlen-len);
			memcpy(newdata, m_textData, offset*2);
			memcpy(newdata+offset, m_textData + offset + len, (oldlen - offset - len)*2);

			SysFreeString(m_textData);
			m_textData = newdata;

			Fire_deletedtext(offset, len);
		}
	}

	return S_OK;
}

STDMETHODIMP CTextData::replaceText(long offset, long deletelen, BSTR data)
{
	if (m_lockCount == 0)
	{
		int len = data? wcslen(data): 0;

		deleteText(offset, deletelen);
		insertText(offset, data, len);
		/*
		int oldlen = SysStringLen(m_textData);

		BSTR newdata = SysAllocStringLen(NULL, oldlen - deletelen + len);
		memcpy(newdata, m_textData, offset*2);
		memcpy(newdata + offset, data, len*2);
		memcpy(newdata + offset + len, m_textData + offset + deletelen, (oldlen - deletelen - offset)*2);

		SysFreeString(m_textData);
		m_textData = newdata;

		//??
		//ATLASSERT(0);
	//	Fire_deletedtext(offset, deletelen);
		Fire_insertedtext(offset, len);
		*/
	}

	return S_OK;
}

STDMETHODIMP CTextData::lockData(long *lockcount)
{
	m_lockCount++;
	if (lockcount) *lockcount = m_lockCount;
	return S_OK;
}

STDMETHODIMP CTextData::unlockData(long *lockcount)
{
	m_lockCount--;
	if (lockcount) *lockcount = m_lockCount;
	return S_OK;
}

STDMETHODIMP CTextData::get_url(BSTR *pVal)
{
	*pVal = SysAllocString(m_url);
	return S_OK;
}

STDMETHODIMP CTextData::put_url(BSTR newVal)
{
	m_url = newVal;
	return S_OK;
}

STDMETHODIMP CTextData::save(BSTR pathName)
{
	HRESULT hr = E_FAIL;

	FILE* fp = fopen(_bstr_t(pathName), "w");
	if (fp)
	{
		BSTR data = m_textData;

		int len = SysStringLen(data);

		BYTE* data8 = (BYTE*)malloc(len);
		if (data8)
		{
			for (int i = 0; i < len; i++)
			{
				data8[i] = (BYTE)data[i];
			}

			fwrite(data8, 1, len, fp);

			free(data8);

			hr = S_OK;
		}

		fclose(fp);

		m_url = pathName;
	}

	return S_OK;
}
