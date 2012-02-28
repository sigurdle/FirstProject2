// LHTMLDialog.h : Declaration of the CLHTMLDialog

#pragma once

#include "LHTMLWindow.h"

class ATL_NO_VTABLE CLHTMLDialog :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchExImpl<CLHTMLWindow, DispILHTMLWindow, &IID_DispILHTMLWindow, &LIBID_LHTMLLib>,
	public IProvideClassInfo2Impl<&CLSID_LHTMLWindow, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib>,

	public ILHTMLWindow,
	public ILHTMLDialog
	//public CLHTMLWindow
{
public:
	CLHTMLDialog()
	{
		m_pHTMLWindow = NULL;

		VariantInit(&m_returnValue);
		VariantInit(&m_dialogArguments);
	}

	int FinalConstruct()
	{
		HRESULT hr;
		
		hr = CComObject<CLHTMLWindow2>::CreateInstance(&m_pHTMLWindow);
		if (FAILED(hr)) return hr;
		m_pHTMLWindow->AddRef();

		return 0;
	}

	void FinalRelease()
	{
		if (m_pHTMLWindow)
		{
			m_pHTMLWindow->Release();
			m_pHTMLWindow = NULL;
		}
	}

	VARIANT m_returnValue;
	VARIANT m_dialogArguments;

	// Try it like this (containment instead of inheritance)
	CComObject<CLHTMLWindow2>* m_pHTMLWindow;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHTMLDialog)
/*
	COM_INTERFACE_ENTRY(ILDOMAbstractView)
	COM_INTERFACE_ENTRY(ILDOMViewCSS)
	*/
	COM_INTERFACE_ENTRY(ILHTMLWindow)
	COM_INTERFACE_ENTRY(ILHTMLDialog)

	/*
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	*/
//
#if 0
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IDispatchEx)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
#endif

END_COM_MAP()

public:
// ILHTMLDialog
	STDMETHOD(get_dialogHeight)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogHeight)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogWidth)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogWidth)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogTop)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogTop)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogLeft)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogLeft)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_returnValue)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_returnValue)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogArguments)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogArguments)(/*[in]*/ VARIANT newVal);

// ILHTMLFramesCollection
	STDMETHOD(get_length)(/*[out, retval]*/ long *pVal)
	{
		return m_pHTMLWindow->get_length(pVal);
	}
	STDMETHOD(item)(/*[in]*/ VARIANT* pvarIndex, /*[out,retval]*/ VARIANT* pvarResult)
	{
		return m_pHTMLWindow->item(pvarIndex, pvarResult);
	}
// ILHTMLWindow
	STDMETHOD(get_frames)(/*[out, retval]*/ ILHTMLFramesCollection* *pVal)
	{
		return m_pHTMLWindow->get_frames(pVal);
	}
	STDMETHOD(get_event)(/*[out, retval]*/ ILDOMEvent* *pVal)
	{
		return m_pHTMLWindow->get_event(pVal);
	}
	STDMETHOD(get_self)(ILHTMLWindow **pVal)
	{
		return m_pHTMLWindow->get_self(pVal);
	}
	STDMETHOD(close)()
	{
		return m_pHTMLWindow->close();
	}
	STDMETHOD(get_closed)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		return m_pHTMLWindow->get_closed(pVal);
	}
	STDMETHOD(get_parent)(/*[out, retval]*/ ILHTMLWindow* *pVal)
	{
		return m_pHTMLWindow->get_parent(pVal);
	}
	STDMETHOD(get_status)(BSTR *p)
	{
		return m_pHTMLWindow->get_status(p);
	}
	STDMETHOD(put_status)(BSTR v)
	{
		return m_pHTMLWindow->put_status(v);
	}
	STDMETHOD(get_document)(ILDOMDocument* * pVal)
	{
		return m_pHTMLWindow->get_document(pVal);
	}
	STDMETHOD(get_svgDocument)(/*[out, retval]*/ ILSVGDocument* *pVal)
	{
		return m_pHTMLWindow->get_svgDocument(pVal);
	}
	STDMETHOD(get_innerHeight)(/*[out, retval]*/ long *pVal)
	{
		return m_pHTMLWindow->get_innerHeight(pVal);
	}
	STDMETHOD(get_innerWidth)(/*[out, retval]*/ long *pVal)
	{
		return m_pHTMLWindow->get_innerWidth(pVal);
	}
	STDMETHOD(setTimeout)(VARIANT* expression, LONG msec, VARIANT * language, LONG * timerID)
	{
		return m_pHTMLWindow->setTimeout(expression, msec, language, timerID);
	}
	STDMETHOD(clearTimeout)(LONG timerID)
	{
		return m_pHTMLWindow->clearTimeout(timerID);
	}
	STDMETHOD(setInterval)(VARIANT* expression, LONG msec, VARIANT * language, LONG * timerID)
	{
		return m_pHTMLWindow->setInterval(expression, msec, language, timerID);
	}
	STDMETHOD(clearInterval)(LONG timerID)
	{
		return m_pHTMLWindow->clearInterval(timerID);
	}
	STDMETHOD(alert)(BSTR message)
	{
		return m_pHTMLWindow->alert(message);
	}
	STDMETHOD(confirm)(BSTR message, VARIANT_BOOL * confirmed)
	{
		return m_pHTMLWindow->confirm(message, confirmed);
	}
	STDMETHOD(prompt)(BSTR message, BSTR defstr, VARIANT * textdata)
	{
		return m_pHTMLWindow->prompt(message, defstr, textdata);
	}
	STDMETHOD(parseXML)(/*[in]*/ BSTR source, /*[in]*/ ILDOMDocument* document, /*[out,retval]*/ ILDOMDocumentFragment* *pVal)
	{
		return m_pHTMLWindow->parseXML(source, document, pVal);
	}
	STDMETHOD(printNode)(/*[in]*/ ILDOMNode* node, /*[out,retval]*/ BSTR* pVal)
	{
		return m_pHTMLWindow->printNode(node, pVal);
	}
	STDMETHOD(open)(/*[in]*/ BSTR url, /*[in]*/ BSTR name, /*[in]*/ BSTR features, /*[in]*/ VARIANT_BOOL replace, /*[out,retval]*/ ILHTMLWindow **pomWindowResult)
	{
		return m_pHTMLWindow->open(url, name, features, replace, pomWindowResult);
	}
	STDMETHOD(showModalDialog)(/*[in]*/ BSTR dialog, /*[in]*/ VARIANT *varArgIn, /*[in]*/ VARIANT *varOptions, /*[out,retval]*/ VARIANT *varArgOut)
	{
		return m_pHTMLWindow->showModalDialog(dialog, varArgIn, varOptions, varArgOut);
	}
	STDMETHOD(getSVGViewerVersion)(/*[out,retval]*/ BSTR* pVal)
	{
		return m_pHTMLWindow->getSVGViewerVersion(pVal);
	}
	STDMETHOD(captureMouse)(/*[in]*/ VARIANT_BOOL bCapture)
	{
		return m_pHTMLWindow->captureMouse(bCapture);
	}
};


#if 0

#ifndef __LHTMLDIALOG_H_
#define __LHTMLDIALOG_H_

#include "resource.h"       // main symbols

class CHTMFrame;

/////////////////////////////////////////////////////////////////////////////
// CMMSXHTMLDialog
class ATL_NO_VTABLE CLHTMLDialog : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMMSXHTMLDialog, &CLSID_MMSXHTMLDialog>,
	public IConnectionPointContainerImpl<CLHTMLDialog>,
	public ILHTMLDialog//IDispatchImpl<IMMSXHTMLDialog, &IID_IMMSXHTMLDialog, &LIBID_SVGLib>
{
public:
	CLHTMLDialog()
	{
		VariantInit(&m_returnValue);
		VariantInit(&m_dialogArguments);

		m_pFrame = NULL;
	}

	VARIANT m_returnValue;
	VARIANT m_dialogArguments;

	CHTMFrame*	m_pFrame;

//DECLARE_REGISTRY_RESOURCEID(IDR_MMSXHTMLDIALOG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHTMLDialog)
	COM_INTERFACE_ENTRY(ILHTMLDialog)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CLHTMLDialog)
END_CONNECTION_POINT_MAP()


// ILHTMLDialog
public:
	STDMETHOD(get_dialogHeight)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogHeight)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogWidth)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogWidth)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogTop)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogTop)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogLeft)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogLeft)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_returnValue)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_returnValue)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_dialogArguments)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_dialogArguments)(/*[in]*/ VARIANT newVal);
};

#endif //__LHTMLDIALOG_H_
#endif