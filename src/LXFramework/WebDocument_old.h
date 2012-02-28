// WebDocument.h : Declaration of the CWebDocument

#ifndef __WEBDOCUMENT_H_
#define __WEBDOCUMENT_H_

#if 0
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWebDocument
class ATL_NO_VTABLE CWebDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWebDocument, &CLSID_WebDocument>,
	public IConnectionPointContainerImpl<CWebDocument>,
	public IDispatchImpl<IWebDocument, &IID_IWebDocument, &LIBID_WEBEDITORLib>
{
public:
	CWebDocument()
	{
	}

	int FinalConstruct()
	{
		m_textDocument.CoCreateInstance(CLSID_TextDocument);

		return S_OK;
	}

	_bstr_t	m_pathName;
	CComQIPtr<ITextDocument> m_textDocument;

DECLARE_REGISTRY_RESOURCEID(IDR_WEBDOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWebDocument)
	COM_INTERFACE_ENTRY(IWebDocument)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CWebDocument)
END_CONNECTION_POINT_MAP()


// IWebDocument
public:
	STDMETHOD(NewDocument)();
	STDMETHOD(LoadDocument)(/*[in]*/ BSTR pathName, /*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(SaveDocument)(/*[in]*/ BSTR pathName, /*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(Save)(/*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(get_textDocument)(/*[out, retval]*/ ITextDocument* *pVal);
	STDMETHOD(put_textDocument)(/*[in]*/ ITextDocument* newVal);
	STDMETHOD(get_filePath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_filePath)(/*[in]*/ BSTR newVal);
	STDMETHOD(ShowViews)();
	STDMETHOD(get_undoManager)(/*[out, retval]*/ IOleUndoManager* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		return S_OK;
	}
};

#endif //__WEBDOCUMENT_H_
#endif