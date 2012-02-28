#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#include "DTDDocument.h"
#include "LDTDElement.h"

#if 0
#include "ASDTDModel.h"
#endif

//#include "LDOMComment.h"

#include "DTDParser.h"

namespace System
{
namespace Web
{

CDTDObjectImpl::CDTDObjectImpl()
{
}

///////////////////////////////////////////////////////////////////
// CDTDDocument

#if 0
STDMETHODIMP CDTDDocument::parseTextData(ITextData *textData, bool *pVal)
{
	ASSERT(0);
#if 0
	if (textData == NULL) return E_INVALIDARG;

	textData->get_data(&m_textData);

	Parse();
#endif

	return S_OK;
}

STDMETHODIMP CDTDDocument::get_errorHandler(/*[out, retval]*/ ILDOMErrorHandler* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_errorHandler;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CDTDDocument::set_errorHandler(/*[in]*/ ILDOMErrorHandler* newVal)
{
	m_errorHandler = newVal;
	return S_OK;
}
#endif


String CAttlist::get_name() const
{
	return m_name;
}

void CAttlist::set_name(StringIn name)
{
	m_name = name;
}

/*
STDMETHODIMP CEntity::get_nodeType(LDOMNodeType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = DTD_ENTITY;
	return S_OK;
}

STDMETHODIMP CAttlist::get_nodeType(LDOMNodeType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = DTD_ATTLIST;
	return S_OK;
}

STDMETHODIMP CNotation::get_nodeType(LDOMNodeType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = DTD_NOTATION;
	return S_OK;
}
*/

#if 0
STDMETHODIMP CDTDDocument::get_nodeType(LDOMNodeType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	ASSERT(0);
	//*pVal = DTD_DOCUMENT;
	return S_OK;
}
#endif

String CEntity::get_name() const
{
	return m_name;
}

void CEntity::set_name(StringIn name)
{
	m_name = name;
}

String CEntity::get_value() const
{
	return m_value;
}

void CEntity::set_value(StringIn value)
{
	m_value = value;
}

//////////////////////////////////////////////////////////////////////////
// DTDDocument

DTDDocument::DTDDocument()
{
}

DTDDocument::~DTDDocument()
{
}

/*
int CDTDDocument::FinalConstruct()
{
	HRESULT hr;
	
	hr = CLDOMDocumentImpl<CDTDDocument>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CLDocumentCSSImpl<CDTDDocument>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CLDOMDocumentRangeImpl<CDTDDocument>::FinalConstruct();
	if (FAILED(hr)) return hr;

	return 0;
}

void CDTDDocument::FinalRelease()
{
	if (m_pASModel)
	{
		m_pASModel->Release();
		m_pASModel = NULL;
	}
	CLDOMDocumentRangeImpl<CDTDDocument>::FinalRelease();
	CLDocumentCSSImpl<CDTDDocument>::FinalRelease();
	CLDOMDocumentImpl<CDTDDocument>::FinalRelease();
}
*/

#if 0
STDMETHODIMP CDTDDocument::get_asModel(/*[out, retval]*/ IASModel* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pASModel;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

CEntity* DTDDocument::GetEntityByName(StringIn name)
{
	for (int i = 0; i < m_entityList.GetSize(); i++)
	{
		CEntity* pEntity = m_entityList[i];

		if (name == pEntity->m_name)
		{
			return pEntity;
		}
	}

	return NULL;
}

CLDTDElement* DTDDocument::GetElementByName(StringIn ns, StringIn name)
{
	for (int i = 0; i < m_elementList.GetSize(); i++)
	{
		CLDTDElement* pElement = m_elementList[i];

		if (ns == pElement->m_ns && name == pElement->m_name)
		{
			return pElement;
		}
	}

	return NULL;
}

/*
CAttlist* CDTDDocument::GetAttlistByName(BSTR ns, BSTR name)
{
	for (int i = 0; i < m_attlistList.GetSize(); i++)
	{
		if (!wcscmp(ns, m_attlistList[i]->m_ns) &&
			!wcscmp(name, m_attlistList[i]->m_name))
		{
			return m_attlistList[i];
		}
	}

	return NULL;
}
*/

void DTDDocument::Load(StringIn url)
{
	ASSERT(0);
#if 0
	CDTDParser parser;
	parser.m_dtdDocument = this;
	parser.loadURL(url);
#endif
}

}	// Web
}
