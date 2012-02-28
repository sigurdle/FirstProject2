#include "stdafx.h"
#include "LAXMLViewer.h"
//#include "LXDocumentViewer.h"
//#include "LHTML.h"
#include "..\LXML\LXML2.h"
//#include "..\LHTML\LHTML2.h"

#include "LHTMLWindow.h"

#include "LHTMLActiveDocument.h"
//#include "LHTMLDocumentView.h"
#include "..\LXML\ScriptSite.h"

#include "..\LXML\LDOMDocumentImpl.h"
#include "..\LXML\LDOMElementImpl.h"

//////////////////////////////////////////////////////////////////////////////////
// CLHTMLWindow

CLHTMLWindow::CLHTMLWindow() : m_cwnd("static", this, 1)
{
	m_hWnd = NULL;

	m_closed = VARIANT_FALSE;

	m_pCanvas = NULL;

	// for setInterval and setTimeout
	m_nIDEvent = 1;
}

int CLHTMLWindow::FinalConstruct()
{
	CComObject<CHTMLWindow>::CreateInstance(&m_pCanvas);
	m_pCanvas->AddRef();
	return 0;
}

void CLHTMLWindow::FinalRelease()
{
	if (m_pCanvas)
	{
		m_pCanvas->Free();
		m_pCanvas->Release();
		m_pCanvas = NULL;
	}
}

CLHTMLWindow::~CLHTMLWindow()
{
	ATLASSERT(m_timers.GetSize() == 0);

	/// ????
	if (m_cwnd.m_hWnd)
	{
		m_cwnd.DestroyWindow();
	}
}

STDMETHODIMP CLHTMLWindow::get_screen(IHTMLScreen **pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	ATLASSERT(0);

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::get_status(BSTR *p)
{
	return S_OK;
}

STDMETHODIMP CLHTMLWindow::put_status(BSTR v)
{
	return S_OK;
}

class CFeatures
{
public:
	class CFeature
	{
	public:
		CWCharString m_name;
		CWCharString m_value;
	};

	~CFeatures()
	{
	}

	std::vector<CFeature*> m_items;

	HRESULT ParseString(BSTR features)
	{
		WCHAR* p = features;

		while (iswspace(*p)) p++;

		while (*p)
		{
			CWCharString name;
			CWCharString value;

			while (*p)
			{
				if (!(iswalnum(*p) || *p == '_'))
				{
					break;
				}

				name += *p++;
			}

			while (iswspace(*p)) p++;

			if (*p != L'=') return E_INVALIDARG;

			while (iswspace(*p)) p++;

			while (*p)
			{
				if (*p == ',')
					break;

				value += *p;
				p++;
			}

			value.TrimRight();

			if (*p == L',') p++;

			while (iswspace(*p)) p++;

			CFeature* pFeature = new CFeature;

			pFeature->m_name = name;
			pFeature->m_value = value;

			m_items.push_back(pFeature);
		}

		return S_OK;
	}

	CFeature* GetFeature(WCHAR* name)
	{
		for (int i = 0; i < m_items.size(); i++)
		{
			if (wcscmp(m_items[i]->m_name, name))
			{
				return m_items[i];
			}
		}

		return NULL;
	}

	BOOL GetFeatureBoolValue(WCHAR* name, BOOL bDefault)
	{
		CFeature* pFeature = GetFeature(name);
		if (pFeature)
		{
			if (	!wcscmp(pFeature->m_value, L"1") || 
					!wcscmp(pFeature->m_value, L"yes"))
			{
				return TRUE;
			}
			else if (!wcscmp(pFeature->m_value, L"0") || 
						!wcscmp(pFeature->m_value, L"no"))
			{
				return FALSE;
			}
		}

		return bDefault;
	}
};

STDMETHODIMP CLHTMLWindow::open(/*[in]*/ BSTR url, /*[in]*/ BSTR name, /*[in]*/ BSTR features, /*[in]*/ VARIANT_BOOL replace, /*[out,retval]*/ ILHTMLWindow **pomWindowResult)
{
	HRESULT hr;

	CFeatures windowFeatures;
	hr = windowFeatures.ParseString(features);
	if (FAILED(hr)) return hr;

	BOOL bLocation = windowFeatures.GetFeatureBoolValue(L"location", TRUE);
	BOOL bMenubar = windowFeatures.GetFeatureBoolValue(L"menubar", TRUE);
	BOOL bResizable = windowFeatures.GetFeatureBoolValue(L"resizable", TRUE);
	BOOL bScrollbars = windowFeatures.GetFeatureBoolValue(L"scrollbars", TRUE);
	BOOL bStatus = windowFeatures.GetFeatureBoolValue(L"status", TRUE);
	BOOL bTitlebar = windowFeatures.GetFeatureBoolValue(L"titlebar", TRUE);
	BOOL bToolbar = windowFeatures.GetFeatureBoolValue(L"toolbar", TRUE);

	CComObject<CLHTMLWindow2>* pHTMLWindow;
	CComObject<CLHTMLWindow2>::CreateInstance(&pHTMLWindow);
	pHTMLWindow->AddRef();

	*pomWindowResult = pHTMLWindow;

	return S_OK;
}

#include "LHTMLDialog.h"

class CModalDialog :
	public CWindowImpl<CModalDialog>
{
public:
};

STDMETHODIMP CLHTMLWindow::showModalDialog(/*[in]*/ BSTR dialog, /*[in]*/ VARIANT *varArgIn, /*[in]*/ VARIANT *varOptions, /*[out,retval]*/ VARIANT *varArgOut)
{
	CComObject<CLHTMLDialog>* pHTMLDialog;
	CComObject<CLHTMLDialog>::CreateInstance(&pHTMLDialog);
	if (pHTMLDialog)
	{
		pHTMLDialog->AddRef();

#if 0
		CComPtr<ILDOMDocument> document;
		document.CoCreateInstance(&document);

		VARIANT_BOOL success;
		document->load(_variant_t(dialog), &success);
#endif

		pHTMLDialog->Release();
	}

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::close()
{
	ATLASSERT(0);
#if 0
	CComQIPtr<IServiceProvider> sp(m_pAddin->m_spAddinSite);
	if (sp)
	{
		CComPtr<IWebBrowser2> webBrowser;
		sp->QueryService(IID_IWebBrowserApp, IID_IWebBrowser2, (void**)&webBrowser);

		if (webBrowser)
		{
			HRESULT hr = webBrowser->Quit();
			if (hr == S_OK)
			{
				m_closed = VARIANT_TRUE;
			}
		}
	}
#endif

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::get_closed(/*[out, retval]*/ VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_closed;
	return TRUE;
}

STDMETHODIMP CLHTMLWindow::captureMouse(/*[in]*/ VARIANT_BOOL bCapture)
{
	ATLASSERT(0);
#if 0	// Have this
	if (bCapture)
	{
		m_pUI->SetCapture();
	}
	else
	{
		ReleaseCapture();
	}
#endif

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::get_innerWidth(long *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pCanvas->m_imageRect.Width();
	return S_OK;
}

STDMETHODIMP CLHTMLWindow::get_innerHeight(long *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pCanvas->m_imageRect.Height();
	return S_OK;
}

STDMETHODIMP CLHTMLWindow::parseXML(/*[in]*/ BSTR source, /*[in]*/ ILDOMDocument* document, /*[out,retval]*/ ILDOMDocumentFragment* *pVal)
{
	return document->parseFragment(source, NULL, pVal);
}

STDMETHODIMP CLHTMLWindow::printNode(/*[in]*/ ILDOMNode* node, /*[out,retval]*/ BSTR* pVal)
{
	return /*m_pView->*/m_document->saveXML(CComVariant(node), pVal);
}

STDMETHODIMP CLHTMLWindow::getSVGViewerVersion(/*[out,retval]*/ BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(L"LXViewer 0.85");	// TODO, put in string resource
	return S_OK;
}

LRESULT CLHTMLWindow::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int wTimerID = wParam;             // timer identifier 
	TIMERPROC* tmprc = (TIMERPROC*)lParam;  // address of timer callback 

	for (int i = 0; i < m_timers.GetSize(); i++)
	{
		CTimer* pTimer = m_timers[i];
		if (pTimer->m_nIDEvent == wTimerID)
		{
			if (pTimer->m_bTimeout)
			{
				m_cwnd.KillTimer(pTimer->m_nTimerID);
				m_timers.RemoveAt(i);
			}

			pTimer->ProcessTimer();//this);

			if (pTimer->m_bTimeout)
			{
				delete pTimer;
			}

			break;
		}
	}

	return 0;
}

STDMETHODIMP CLHTMLWindow::get_self(ILHTMLWindow **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = this;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLHTMLWindow::get_parent(/*[out, retval]*/ ILHTMLWindow* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	ATLASSERT(0);
#if 0	// Have something like this

	if (m_pFrame)
	{
		*pVal = m_pFrame->m_pParentWindow;
		if (*pVal) (*pVal)->AddRef();
	}
#endif

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::get_document(ILDOMDocument* * pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = /*m_pView->*/m_document;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLHTMLWindow::get_svgDocument(/*[out, retval]*/ ILSVGDocument* *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	CComQIPtr<ILSVGDocument> svgDocument = /*m_pView->*/m_document;
	*pVal = svgDocument.Detach();
	return S_OK;
}

STDMETHODIMP CLHTMLWindow::alert(BSTR message)
{
	USES_CONVERSION;

	HWND hwnd = m_hWnd;
#if 0
	if (m_pUI)
	{
		hwnd = m_pUI->m_hWnd;
	}
	else if (m_pActiveDocument->m_spInPlaceSite)
	{
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);
	}
#endif

	//if (hwnd)
	{
		::MessageBox(hwnd, W2A(message), "LXViewer", MB_OK);
	}

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::confirm(BSTR message, VARIANT_BOOL * confirmed)
{
	USES_CONVERSION;

	if (confirmed == NULL) return E_POINTER;

	*confirmed = VARIANT_FALSE;

	HWND hwnd = m_hWnd;
#if 0
	if (m_pUI)
		hwnd = m_pUI->m_hWnd;
	else
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);
#endif

	UINT nID = MessageBox(hwnd, W2A(message), "LXViewer", MB_OKCANCEL);
	if (nID == IDOK)
		*confirmed = VARIANT_TRUE;
	else
		*confirmed = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::prompt(BSTR message, BSTR defstr, VARIANT * textdata)
{
	return S_OK;
}

STDMETHODIMP CLHTMLWindow::setTimeout(VARIANT* expression, LONG msec, VARIANT * language, LONG * ptimerID)
{
	if (ptimerID == NULL) return E_POINTER;

	if (expression == NULL) return E_POINTER;
	if (expression->vt != VT_BSTR && expression->vt != VT_DISPATCH)
		return E_INVALIDARG;

	CTimer* pTimer = new CTimer;
	pTimer->m_bTimeout = true;
	pTimer->m_nIDEvent = ++m_nIDEvent;

	pTimer->m_nTimerID = m_cwnd.SetTimer(pTimer->m_nIDEvent, msec);
	*ptimerID = pTimer->m_nTimerID;

	m_timers.Add(pTimer);

	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = CComQIPtr<CLDOMDocumentImplImpl>(/*m_pView->*/m_document)->m_pScriptSite->m_activeScript;

	if (expression->vt == VT_BSTR)
	{
		HRESULT hr = activeScriptParseProcedure->ParseProcedureText(
			expression->bstrVal,	// code
			NULL,//L"",	// formal params
			NULL,	// procedure name
			NULL,	// item name
			NULL,	// punkContext
			NULL,	// delimiter
			0,	// dwSourceContextCookie
			0,	// start line number
			SCRIPTPROC_IMPLICIT_THIS,//SCRIPTTEXT_ISVISIBLE,// | SCRIPTTEXT_ISPERSISTENT,	// flags
			&pTimer->m_disp);
	}
	else if (expression->vt == VT_DISPATCH)
	{
		pTimer->m_disp = expression->pdispVal;
	}

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::setInterval(VARIANT* expression, LONG msec, VARIANT * language, LONG * ptimerID)
{
	if (ptimerID == NULL) return E_POINTER;

	if (expression == NULL) return E_POINTER;
	if (expression->vt != VT_BSTR && expression->vt != VT_DISPATCH)
		return E_INVALIDARG;

	CTimer* pTimer = new CTimer;
	pTimer->m_bTimeout = false;
	pTimer->m_nIDEvent = ++m_nIDEvent;

	pTimer->m_nTimerID = m_cwnd.SetTimer(pTimer->m_nIDEvent, msec);
	*ptimerID = pTimer->m_nTimerID;

	m_timers.Add(pTimer);

	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = CComQIPtr<CLDOMDocumentImplImpl>(/*m_pView->*/m_document)->m_pScriptSite->m_activeScript;

	if (expression->vt == VT_BSTR)
	{
		HRESULT hr = activeScriptParseProcedure->ParseProcedureText(
			expression->bstrVal,	// code
			NULL,//L"",	// formal params
			NULL,	// procedure name
			NULL,	// item name
			NULL,	// punkContext
			NULL,	// delimiter
			0,	// dwSourceContextCookie
			0,	// start line number
			SCRIPTPROC_IMPLICIT_THIS,//SCRIPTTEXT_ISVISIBLE,// | SCRIPTTEXT_ISPERSISTENT,	// flags
			&pTimer->m_disp);
	}
	else if (expression->vt == VT_DISPATCH)
	{
		pTimer->m_disp = expression->pdispVal;
	}

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::clearTimeout(LONG timerID)
{
	for (int i = 0; i < m_timers.GetSize(); i++)
	{
		if (m_timers[i]->m_nTimerID == timerID)
		{
			m_cwnd.KillTimer(m_timers[i]->m_nTimerID);
			delete m_timers[i];
			m_timers.RemoveAt(i);
			break;
		}
	}

	return S_OK;
}

STDMETHODIMP CLHTMLWindow::clearInterval(LONG timerID)
{
	for (int i = 0; i < m_timers.GetSize(); i++)
	{
		if (m_timers[i]->m_nTimerID == timerID)
		{
			m_cwnd.KillTimer(m_timers[i]->m_nTimerID);
			delete m_timers[i];
			m_timers.RemoveAt(i);
			break;
		}
	}

	return S_OK;
}

STDMETHODIMP CLHTMLWindow2::GetIDsOfNames(
		REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid
	)
{
	HRESULT hr;

	hr = IDispatchExImpl<CLHTMLWindow2, DispILHTMLWindow, &IID_DispILHTMLWindow, &LIBID_LHTMLLib>::GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);
	if (SUCCEEDED(hr))
	{
		return hr;
	}

	ATLASSERT(0);
#if 0	// TODO have this
	if (m_pActiveDocument->m_containerScriptDispatch)
	{
		hr = m_pActiveDocument->m_containerScriptDispatch->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);
		if (SUCCEEDED(hr))
		{
			ATLASSERT(rgdispid[0] >= 0);
			rgdispid[0] += 2000;
			return hr;
		}
	}
#endif

	return hr;

#if 0
	for (int i = 0; i < cNames; i++)
	{
		DISPID dispid;

		hr = IDispatchImpl<DispILHTMLWindow, &IID_DispILHTMLWindow, &LIBID_LHTMLLib>::GetIDsOfNames(riid, &rgszNames[i], 1, lcid, &dispid);
		if (SUCCEEDED(hr))
		{
			rgdispid[i] = dispid;
			continue;
		}

		hr = m_pActiveDocument->m_containerScriptDispatch->GetIDsOfNames(riid, &rgszNames[i], 1, lcid, &dispid);
		if (SUCCEEDED(hr))
		{
			ATLASSERT(dispid >= 0);
			rgdispid[i] = dispid+2000;
			continue;
		}
	}
#endif

#if 0
	hr = m_pFrame->m_pHTMLWindowImpl->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);
	if (FAILED(hr)) hr = m_pFrame->m_pHTMLDialogImpl->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);
	if (FAILED(hr))
	{
		hr = m_pFrame->m_pScriptDisp->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);

		if (SUCCEEDED(hr))
		{
			if (*rgdispid < 100)
				ATLASSERT(0);
		}
	}
#endif
	return hr;
}

STDMETHODIMP CLHTMLWindow2::Invoke(
	 DISPID dispIdMember,
	 REFIID riid,
	 LCID lcid,
	 WORD wFlags,
	 DISPPARAMS FAR* pDispParams,
	 VARIANT FAR* pVarResult,
	 EXCEPINFO FAR* pExcepInfo,
	 unsigned int FAR* puArgErr
	 )
{
	if (dispIdMember < 2000)
	{
		return IDispatchExImpl<CLHTMLWindow2, DispILHTMLWindow, &IID_DispILHTMLWindow, &LIBID_LHTMLLib>::Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	}
	else
	{
		// Delegate to script object of container
		ATLASSERT(0);
#if 0	// Had this
		if (m_pActiveDocument->m_containerScriptDispatch)
		{
			return m_pActiveDocument->m_containerScriptDispatch->Invoke(dispIdMember-2000, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
		}
#endif
	}

	return E_FAIL;

#if 0

	hr = m_pFrame->m_pHTMLWindowImpl->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	if (FAILED(hr)) hr = m_pFrame->m_pHTMLDialogImpl->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	if (FAILED(hr)) hr = m_pFrame->m_pScriptDisp->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
#endif
}
