// WebDocument.cpp : Implementation of CWebDocument
#include "stdafx.h"
#include "WebEditor.h"
#include "WebDocument.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CWebDocument

STDMETHODIMP CWebDocument::NewDocument()
{
	m_textDocument->put_data(SysAllocString(L""));
	m_pathName = L"";

	return S_OK;
}

STDMETHODIMP CWebDocument::LoadDocument(BSTR pathName, VARIANT_BOOL *success)
{
	m_textDocument->load(pathName, success);
	m_pathName = pathName;

	return S_OK;
}

STDMETHODIMP CWebDocument::LoadDocumentByteArray(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success)
{
	return m_textDocument->loadByteArray(dataArray, success);
}

STDMETHODIMP CWebDocument::ShowViews()
{
	return E_NOTIMPL;
	return S_OK;
}

STDMETHODIMP CWebDocument::get_filePath(BSTR *pVal)
{
	*pVal = SysAllocString(m_pathName);
	return S_OK;
}

STDMETHODIMP CWebDocument::put_filePath(BSTR newVal)
{
	m_pathName = newVal;
	return S_OK;
}

STDMETHODIMP CWebDocument::get_textDocument(ITextDocument **pVal)
{
	*pVal = m_textDocument;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CWebDocument::put_textDocument(ITextDocument *newVal)
{
	m_textDocument = newVal;
	return S_OK;
}

STDMETHODIMP CWebDocument::Save(VARIANT_BOOL *success)
{
	return SaveDocument(m_pathName, success);
}

STDMETHODIMP CWebDocument::SaveDocument(BSTR pathName, VARIANT_BOOL *success)
{
	FILE* fp = fopen(_bstr_t(pathName), "w");
	if (fp)
	{
		BSTR data;
		m_textDocument->get_data(&data);

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
		}

		fclose(fp);

		m_pathName = pathName;
	}

	return S_OK;
}

#endif