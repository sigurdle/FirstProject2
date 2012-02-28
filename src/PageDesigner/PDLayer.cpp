#include "stdafx.h"
//#include "ocidl.h"	// Added by ClassView
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDLayer.h"

#include "PDDocument.h"

/////////////////////////
// CPDLayer

STDMETHODIMP CPDLayer::get_name(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_name.copy();
	return S_OK;
}

STDMETHODIMP CPDLayer::put_name(BSTR newVal)
{
	if (wcscmp(m_name, newVal))
	{
		m_name = newVal;
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}

	return S_OK;
}

STDMETHODIMP CPDLayer::get_visible(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_visible;
	return S_OK;
}

STDMETHODIMP CPDLayer::put_visible(VARIANT_BOOL newVal)
{
	if (m_visible != newVal)
	{
		m_visible = newVal;
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}

	return S_OK;
}

STDMETHODIMP CPDLayer::get_locked(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_locked;
	return S_OK;
}

STDMETHODIMP CPDLayer::put_locked(VARIANT_BOOL newVal)
{
	if (m_locked != newVal)
	{
		m_locked = newVal;
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}

	return S_OK;
}

STDMETHODIMP CPDLayer::get_color(OLE_COLOR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_color;
	return S_OK;
}

STDMETHODIMP CPDLayer::put_color(OLE_COLOR newVal)
{
	if (m_color != newVal)
	{
		m_color = newVal;
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
//		if (m_pDocument) m_pDocument->Fire_LayerOptionsChanged(this);
	}

	return S_OK;
}

STDMETHODIMP CPDLayer::get_uniqId(GUID *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_uniqID;
	return S_OK;
}

STDMETHODIMP CPDLayer::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"name", _variant_t(m_name));
	node->putAttribute(L"color", _variant_t((long)m_color));
	node->putAttribute(L"locked", _variant_t(m_locked));
	node->putAttribute(L"visible", _variant_t(m_visible));

	return 0;
}

STDMETHODIMP CPDLayer::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	CComQIPtr<IPDDocument> document = pUnkExtra;
	m_pDocument = static_cast<CPDDocument*>((IPDDocument*)document.p);

	_variant_t v;

	node->getAttribute(L"name", &v);
	m_name = v;

	node->getAttribute(L"color", &v);
	m_color = (long)v;

	node->getAttribute(L"locked", &v);
	m_locked = v;

	node->getAttribute(L"visible", &v);
	m_visible = v;

	return S_OK;
}

STDMETHODIMP CPDLayer::get_nextSibling(IPDLayer **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nextSibling;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDLayer::get_previousSibling(IPDLayer **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_previousSibling;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDLayer::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDLayer;
	return S_OK;
}
