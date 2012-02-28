// LMathMLImplementation.h : Declaration of the CLMathMLImplementation

#ifndef __LMATHMLIMPLEMENTATION_H_
#define __LMATHMLIMPLEMENTATION_H_

#include "resource.h"       // main symbols

#include "LXMLImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CLMathMLImplementation
class ATL_NO_VTABLE CLMathMLImplementation : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLMathMLImplementation, &CLSID_LMathMLImplementation>,
	public ILXMLImplementation
	//public ILMathMLImplementation
{
public:
	CLMathMLImplementation()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LMATHMLIMPLEMENTATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLMathMLImplementation)
	COM_INTERFACE_ENTRY(ILXMLImplementation)
	//COM_INTERFACE_ENTRY(ILMathMLImplementation)
END_COM_MAP()

// ILMathMLImplementation
public:
	STDMETHOD(CreateElement)(BSTR namespaceURI, BSTR tagName, ILDOMElement* *pVal);
	STDMETHOD(CreateViewElement)(ILDOMElement* element, CXMLDocumentView* pView, IUnknown* *pVal);
};

#endif //__LMATHMLIMPLEMENTATION_H_
