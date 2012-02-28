// LXSLProcessor.h : Declaration of the CLXSLProcessor

#ifndef __LXSLPROCESSOR_H_
#define __LXSLPROCESSOR_H_

//#include "resource.h"       // main symbols

#if 0
class CLXSLTemplate;

#if 0
#import "C:\\winnt\\system32\\msxml4.dll"
#endif

//#import "C:\Windows\SYSTEM\msxml4.dll"

/////////////////////////////////////////////////////////////////////////////
// CLXSLProcessor
class CLXSLProcessor : 
	public CComObjectRootEx<CComMultiThreadModel>,
//	public CComCoClass<CLXSLProcessor, &CLSID_LXSLProcessor>,
	public ILXSLProcessor
{
public:
	CLXSLProcessor()
	{
		m_ownerTemplate = NULL;
	}

	_variant_t m_input;
	CLXSLTemplate* m_ownerTemplate;

#if 0
	MSXML2::IXSLProcessorPtr m_msprocessor;
#endif

//DECLARE_REGISTRY_RESOURCEID(IDR_LXSLPROCESSOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXSLProcessor)
	COM_INTERFACE_ENTRY(ILXSLProcessor)
END_COM_MAP()

// ILXSLProcessor
public:
	STDMETHOD(transform)(/*[out,retval]*/ VARIANT_BOOL *pDone);
	STDMETHOD(get_output)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_output)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ownerTemplate)(/*[out, retval]*/ ILXSLTemplate* *pVal);
	STDMETHOD(get_input)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_input)(/*[in]*/ VARIANT newVal);
};

#endif //__LXSLPROCESSOR_H_

#endif