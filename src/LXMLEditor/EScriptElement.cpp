#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EScriptElement.h"

#include "EScriptDocument.h"

#if 0

//////////////////////////////////////////////////////////////////////////
// CEScriptElement

int CEScriptElement::FinalConstruct()
{
	HRESULT hr;

	hr = CEElementImpl<IEElement>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CComObject<CEScriptDocument>::CreateInstance(&m_pScriptDocument);
	if (FAILED(hr)) return hr;
	m_pScriptDocument->AddRef();

	return 0;
}

void CEScriptElement::FinalRelease()
{
	if (m_pScriptDocument)
	{
		m_pScriptDocument->Release();
		m_pScriptDocument = NULL;
	}

	CEElementImpl<IEElement>::FinalRelease();
}

#endif