// LXSLTemplate.h : Declaration of the CLXSLTemplate

#ifndef __LXSLTEMPLATE_H_
#define __LXSLTEMPLATE_H_

//#include "resource.h"       // main symbols

#if 0

#if 0//_WINDOWS
#import "C:\\winnt\\system32\\msxml4.dll"
//#import "C:/windows/system/msxml4.dll"
#endif

/////////////////////////////////////////////////////////////////////////////
// CLXSLTemplate
class CLXSLTemplate : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CLXSLTemplate, &CLSID_LXSLTemplate>,
	public ILXSLTemplate
{
public:
	CTOR CLXSLTemplate()
	{
	}

	int FinalConstruct()
	{
#if 0//_WINDOWS
		HRESULT hr;

		hr = m_mstemplate.CreateInstance(L"Msxml2.XSLTemplate.4.0");
		if (FAILED(hr)) return hr;
#endif

		return 0;
	}

	Node* m_stylesheet;
#if 0//_WINDOWS
	MSXML2::IXMLDOMNodePtr m_msstylesheet;

	MSXML2::IXSLTemplatePtr m_mstemplate;
#endif

DECLARE_REGISTRY_RESOURCEID(IDR_LXSLTEMPLATE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXSLTemplate)
	COM_INTERFACE_ENTRY(ILXSLTemplate)
END_COM_MAP()

// ILXSLTemplate
public:
	STDMETHOD(createProcessor)(/*[out,retval]*/ ILXSLProcessor* *pVal);
	STDMETHOD(get_stylesheet)(/*[out, retval]*/ ILDOMNode* *pVal);
	STDMETHOD(putref_stylesheet)(/*[in]*/ ILDOMNode* newVal);
};

#endif //__LXSLTEMPLATE_H_

#endif