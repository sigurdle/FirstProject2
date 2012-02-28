// LSVGElement.h : Declaration of the CLSVGElement

#ifndef __LSVGELEMENT_H_
#define __LSVGELEMENT_H_

#include "resource.h"       // main symbols

#include "LSVGElementImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CLSVGElement
class ATL_NO_VTABLE CLSVGElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLSVGElement, &CLSID_LSVGElement>,
	public CLSVGElementImpl<ILSVGElement>
{
public:
	CLSVGElement()
	{
		m_pElement = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;
		
		hr = CoCreateInstance (CLSID_LDOMElement, GetControllingUnknown(), CLSCTX_ALL, IID_IUnknown, (void **)&m_pElement);
		if (FAILED (hr)) return E_NOINTERFACE;

		return S_OK;
	}

	void FinalRelease()
	{
		if (m_pElement != NULL)
			m_pElement->Release();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LSVGELEMENT)
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLSVGElement)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMElement)
	COM_INTERFACE_ENTRY(ILSVGElement)
END_COM_MAP()

// ILSVGElement
public:
};

#endif //__LSVGELEMENT_H_
