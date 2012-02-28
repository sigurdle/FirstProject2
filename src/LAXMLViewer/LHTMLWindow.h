#pragma once

#include "resource.h"

#include "LHTMLCP.h"

class COleClientItem;
class CLHTMLDialog;
class LDOMViewCSS;
class CPHTMElement;
class CPSVGElementImpl;	// TODO, replace with CPSVGSVGElement
class CPSMILElement;
class CPSMILLayoutElement;
class CFODisplay;
class CHTMTimerWindow;
class CLSVGMatrix;
class CHTMLWindow;
class CXMLDocumentView;

#include "LDOMViewCSS.h"
#include "PNode.h"
#include "PElement.h"
//#include "..\UIT.h"	// TODO Am I/Should I use this here ??

#if 0	// Huh ???

class IMPORTEXPORT CColorProfiles
{
public:
	CComBSTR name;
	ILSVGColorProfileElement* m_element;
};
#endif

class CTimer
{
public:
	virtual ~CTimer()
	{
	}

	long m_nIDEvent;
	long m_nTimerID;
	bool m_bTimeout;

	CComPtr<IDispatch> m_disp;

	virtual void ProcessTimer(/*CHTMLWindow* pFrame*/)
	{
		DISPPARAMS dispparams;
		//VARIANTARG varargs[1];
		dispparams.cArgs = 0;
		dispparams.cNamedArgs = 0;
		dispparams.rgvarg = NULL;//varargs;

		/*
		dispparams.rgvarg[0].vt = VT_DISPATCH;
		dispparams.rgvarg[0].pdispVal = evt;
		*/

		DISPID dispid = 0;
		HRESULT hr = m_disp->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD,
			&dispparams, 0, 0, 0);
	}
};

class CLHTMLActiveDocument;
//class CLHTMLDocumentView;


//class CHTMLWindow;

#include "LXMLDocumentView.h"
#include "LBoxWindow.h"

class ATL_NO_VTABLE CLHTMLWindow :
	public ILHTMLWindow,
//	public CProxy_ILHTMLWindowEvents< CLHTMLWindow >
//	public IDispEventImpl<2, CHTMLWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<3, CHTMLWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IConnectionPointContainerImpl<CHTMLWindow>,
	public CMessageMap
{
public:
	CLHTMLWindow();
	~CLHTMLWindow();

	int FinalConstruct();
	void FinalRelease();

	CLHTMLActiveDocument* m_pAddin;

	CComPtr<ILDOMDocument> m_document;

	CContainedWindow m_cwnd;
	HWND m_hWnd;

	long m_nIDEvent;
	CArray<CTimer*,CTimer*> m_timers;

	CComObject<CHTMLWindow>* m_pCanvas;

	VARIANT_BOOL m_closed;

BEGIN_MSG_MAP(CHTMLWindow)
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:

	STDMETHOD(get_self)(ILHTMLWindow **pVal);
	STDMETHOD(close)();
	STDMETHOD(get_closed)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_parent)(/*[out, retval]*/ ILHTMLWindow* *pVal);

// ILHTMLFramesCollection
	STDMETHOD(get_length)(/*[out, retval]*/ long *pVal)
	{
		return E_NOTIMPL;
	//	return m_frames->get_length(pVal);
	}

	STDMETHOD(item)(/*[in]*/ VARIANT* pvarIndex, /*[out,retval]*/ VARIANT* pvarResult)
	{
		return E_NOTIMPL;
	//	return m_frames->item(pvarIndex, pvarResult);
	}

// ILHTMLWindow
	STDMETHOD(get_frames)(/*[out, retval]*/ ILHTMLFramesCollection* *pVal)
	{
		return S_OK;
	}
	STDMETHOD(open)(/*[in]*/ BSTR url, /*[in]*/ BSTR name, /*[in]*/ BSTR features, /*[in]*/ VARIANT_BOOL replace, /*[out,retval]*/ ILHTMLWindow **pomWindowResult);
	STDMETHOD(showModalDialog)(/*[in]*/ BSTR dialog, /*[in]*/ VARIANT *varArgIn, /*[in]*/ VARIANT *varOptions, /*[out,retval]*/ VARIANT *varArgOut);

	STDMETHOD(get_event)(/*[out, retval]*/ ILDOMEvent* *pVal)
	{
		return S_OK;
	}
	STDMETHOD(get_status)(BSTR *p);
	STDMETHOD(put_status)(BSTR v);

	STDMETHOD(get_document)(ILDOMDocument* * pVal);
	STDMETHOD(get_svgDocument)(/*[out, retval]*/ ILSVGDocument* *pVal);
	STDMETHOD(get_innerHeight)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_innerWidth)(/*[out, retval]*/ long *pVal);

	STDMETHOD(setTimeout)(VARIANT* expression, LONG msec, VARIANT * language, LONG * timerID);
	STDMETHOD(clearTimeout)(LONG timerID);
	STDMETHOD(setInterval)(VARIANT* expression, LONG msec, VARIANT * language, LONG * timerID);
	STDMETHOD(clearInterval)(LONG timerID);
	STDMETHOD(alert)(BSTR message);
	STDMETHOD(confirm)(BSTR message, VARIANT_BOOL * confirmed);
	STDMETHOD(prompt)(BSTR message, BSTR defstr, VARIANT * textdata);
	STDMETHOD(parseXML)(/*[in]*/ BSTR source, /*[in]*/ ILDOMDocument* document, /*[out,retval]*/ ILDOMDocumentFragment* *pVal);
	STDMETHOD(printNode)(/*[in]*/ ILDOMNode* node, /*[out,retval]*/ BSTR* pVal);
	STDMETHOD(get_screen)(/*[out, retval]*/ IHTMLScreen* *pVal);

// Adobe SVG Viewer Extensions
	STDMETHOD(captureMouse)(/*[in]*/ VARIANT_BOOL bCapture);
	STDMETHOD(getSVGViewerVersion)(/*[out,retval]*/ BSTR* pVal);

// IDispatch
#if 0
	STDMETHOD(GetIDsOfNames)(
		REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid
	);

	STDMETHOD(Invoke)(
	  DISPID dispIdMember,
	  REFIID riid,
	  LCID lcid,
	  WORD wFlags,
	  DISPPARAMS FAR* pDispParams,
	  VARIANT FAR* pVarResult,
	  EXCEPINFO FAR* pExcepInfo,
	  unsigned int FAR* puArgErr
	);
#endif
};

class ATL_NO_VTABLE CLHTMLWindow2 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchExImpl<CLHTMLWindow2, DispILHTMLWindow, &IID_DispILHTMLWindow, &LIBID_LHTMLLib>,
	public IProvideClassInfo2Impl<&CLSID_LHTMLWindow, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib>,

	public CLHTMLWindow
{
public:

	int FinalConstruct()
	{
		return CLHTMLWindow::FinalConstruct();
	}

	void FinalRelease()
	{
		CLHTMLWindow::FinalRelease();
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHTMLWindow2)
/*
	COM_INTERFACE_ENTRY(ILDOMAbstractView)
	COM_INTERFACE_ENTRY(ILDOMViewCSS)
	*/
	COM_INTERFACE_ENTRY(ILHTMLWindow)

	/*
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	*/
//
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IDispatchEx)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)

#if 0
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#endif

END_COM_MAP()

#if 0
BEGIN_CONNECTION_POINT_MAP(CHTMLWindow)
	CONNECTION_POINT_ENTRY(DIID__ILHTMLWindowEvents)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CHTMLWindow)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(3, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
END_SINK_MAP()
#endif

	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);

public:
	STDMETHOD(get_self)(ILHTMLWindow **pVal)
	{
		return CLHTMLWindow::get_self(pVal);
	}
	STDMETHOD(close)()
	{
		return CLHTMLWindow::close();
	}
	STDMETHOD(get_closed)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		return CLHTMLWindow::get_closed(pVal);
	}
	STDMETHOD(get_parent)(/*[out, retval]*/ ILHTMLWindow* *pVal)
	{
		return CLHTMLWindow::get_parent(pVal);
	}
	STDMETHOD(get_status)(BSTR *p)
	{
		return CLHTMLWindow::get_status(p);
	}
	STDMETHOD(put_status)(BSTR v)
	{
		return CLHTMLWindow::put_status(v);
	}
	STDMETHOD(get_document)(ILDOMDocument* * pVal)
	{
		return CLHTMLWindow::get_document(pVal);
	}
	STDMETHOD(get_svgDocument)(/*[out, retval]*/ ILSVGDocument* *pVal)
	{
		return CLHTMLWindow::get_svgDocument(pVal);
	}
	STDMETHOD(get_innerHeight)(/*[out, retval]*/ long *pVal)
	{
		return CLHTMLWindow::get_innerHeight(pVal);
	}
	STDMETHOD(get_innerWidth)(/*[out, retval]*/ long *pVal)
	{
		return CLHTMLWindow::get_innerWidth(pVal);
	}
	STDMETHOD(setTimeout)(VARIANT* expression, LONG msec, VARIANT * language, LONG * timerID)
	{
		return CLHTMLWindow::setTimeout(expression, msec, language, timerID);
	}
	STDMETHOD(clearTimeout)(LONG timerID)
	{
		return CLHTMLWindow::clearTimeout(timerID);
	}
	STDMETHOD(setInterval)(VARIANT* expression, LONG msec, VARIANT * language, LONG * timerID)
	{
		return CLHTMLWindow::setInterval(expression, msec, language, timerID);
	}
	STDMETHOD(clearInterval)(LONG timerID)
	{
		return CLHTMLWindow::clearInterval(timerID);
	}
	STDMETHOD(alert)(BSTR message)
	{
		return CLHTMLWindow::alert(message);
	}
	STDMETHOD(confirm)(BSTR message, VARIANT_BOOL * confirmed)
	{
		return CLHTMLWindow::confirm(message, confirmed);
	}
	STDMETHOD(prompt)(BSTR message, BSTR defstr, VARIANT * textdata)
	{
		return CLHTMLWindow::prompt(message, defstr, textdata);
	}
	STDMETHOD(parseXML)(/*[in]*/ BSTR source, /*[in]*/ ILDOMDocument* document, /*[out,retval]*/ ILDOMDocumentFragment* *pVal)
	{
		return CLHTMLWindow::parseXML(source, document, pVal);
	}
	STDMETHOD(printNode)(/*[in]*/ ILDOMNode* node, /*[out,retval]*/ BSTR* pVal)
	{
		return CLHTMLWindow::printNode(node, pVal);
	}
	STDMETHOD(getSVGViewerVersion)(/*[out,retval]*/ BSTR* pVal)
	{
		return CLHTMLWindow::getSVGViewerVersion(pVal);
	}

// IDispatch
	STDMETHOD(GetIDsOfNames)(
		REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid
	);

	STDMETHOD(Invoke)(
	  DISPID dispIdMember,
	  REFIID riid,
	  LCID lcid,
	  WORD wFlags,
	  DISPPARAMS FAR* pDispParams,
	  VARIANT FAR* pVarResult,
	  EXCEPINFO FAR* pExcepInfo,
	  unsigned int FAR* puArgErr
	);
};


