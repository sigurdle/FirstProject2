#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#if 0

#include "EStyleElement.h"

#include "ECSSDocument.h"

//////////////////////////////////////////////////////////////////////////
// CEStyleElement

int CEStyleElement::FinalConstruct()
{
	HRESULT hr;

	hr = CEElementImpl<IEElement>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CComObject<CECSSDocument>::CreateInstance(&m_pCSSDocument);
	if (FAILED(hr)) return hr;
	m_pCSSDocument->AddRef();

	return 0;
}

void CEStyleElement::FinalRelease()
{
	if (m_pCSSDocument)
	{
		m_pCSSDocument->Release();
		m_pCSSDocument = NULL;
	}

	CEElementImpl<IEElement>::FinalRelease();
}

#endif