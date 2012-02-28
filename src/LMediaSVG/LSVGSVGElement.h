// LSVGSVGElement.h : Declaration of the CLSVGSVGElement

#ifndef __LSVGSVGELEMENT_H_
#define __LSVGSVGELEMENT_H_

#include "resource.h"       // main symbols

#include "LSVGElementImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CLSVGSVGElement
class ATL_NO_VTABLE CLSVGSVGElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLSVGSVGElement, &CLSID_LSVGSVGElement>,
	public CLSVGElementImpl<ILSVGSVGElement>
{
public:
	CLSVGSVGElement()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LSVGSVGELEMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLSVGSVGElement)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMElement)
	COM_INTERFACE_ENTRY(ILSVGElement)
	COM_INTERFACE_ENTRY(ILSVGSVGElement)
END_COM_MAP()

// ILSVGSVGElement
public:
};

#endif //__LSVGSVGELEMENT_H_
