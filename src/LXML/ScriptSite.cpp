#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#if 0

#include "ScriptSite.h"

#include "LDOMDocumentImpl.h"
//#include "LHTMLActiveDocument.h"
//#include "LHTMLDocumentView.h"

#if 0
#include "LHTMLWindow.h"
#endif

// Script Site

void CScriptSite::FinalRelease()
{
	if (m_activeScript)
	{
		m_activeScript->Close();
		m_activeScript->SetScriptSite(NULL);

		m_activeScript.Release();
		m_pScriptDisp.Release();
	}
}

STDMETHODIMP CScriptSite::GetLCID( 
														/* [out] */ LCID __RPC_FAR *plcid)
{
	return E_NOTIMPL;	// Use default locale
}

STDMETHODIMP CScriptSite::GetItemInfo( 
															 /* [in] */ LPCOLESTR pstrName,
															 /* [in] */ DWORD dwReturnMask,
															 /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiunkItem,
															 /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppti)
{
	if (dwReturnMask & SCRIPTINFO_IUNKNOWN) *ppiunkItem = NULL;
	if (dwReturnMask & SCRIPTINFO_ITYPEINFO) *ppti = NULL;

	if (!wcscmp(pstrName, L"globalobject"))
	{
		//IUnknown* unk;
	//	m_pFrame->m_pHTMLWindowImpl->QueryInterface(IID_IMMSXHTMLWindow, (void**)&unk);
//		m_pFrame->m_pHTMLWindowImpl->QueryInterface(IID_IUnknown, (void**)&unk);

		//m_pFrame->m_spScriptSite->QueryInterface(IID_IUnknown, (void**)&unk);

		if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
		{
			//ASSERT(static_cast<CLHTMLActiveDocument*>(m_pDocument->m_acDocument)->m_pWindow);
			//if (m_pWindow->m_pWindow)
			{
				*ppiunkItem = m_pGlobalObject;
				//*ppiunkItem = static_cast<CLHTMLActiveDocument*>(m_pDocument->m_acDocument)->m_pWindow->GetUnknown();
				(*ppiunkItem)->AddRef();
			}
			/*
			else
				return TYPE_E_ELEMENTNOTFOUND;
				*/
		}

		if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
		{
			ASSERT(0);
			//IDispatchImpl<DispILHTMLWindow, &IID_DispILHTMLWindow, &LIBID_LHTMLLib>::GetTypeInfo(0, 0, ppti);
		}

		return S_OK;
	}
#if 0
	else if (!wcscmp(pstrName, L"globalwindow2"))
	{
		CComPtr<IUnknown> unk;
		m_pFrame->m_pHTMLWindowImpl->QueryInterface(IID_IUnknown, (void**)&unk);

		if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
		{
			*ppiunkItem = unk;
			(*ppiunkItem)->AddRef();
		}

		if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
		{
			CComQIPtr<IProvideClassInfo2> classinfo = unk;
			ASSERT(classinfo != NULL);
			if (classinfo)
			{
				classinfo->GetClassInfo(ppti);
				ASSERT(*ppti);
			}

//			m_pFrame->m_pHTMLWindowImpl->GetTypeInfo(0, 0, ppti);
		}

		return S_OK;
	}
	else
	{
		for (int i = 0; i < m_pFrame->m_namedItems.GetSize(); i++)
		{
			if (!wcsicmp(m_pFrame->m_namedItems[i].m_name, pstrName))
			{
				CComQIPtr<ILHTMLElement> htmlelement = m_pFrame->m_namedItems[i].m_pDisp;
				if (htmlelement)
				{
					BSTR btagName;
					htmlelement->get_tagName(&btagName);
					_bstr_t tagName = _bstr_t(btagName, false);

					if (!wcsicmp(tagName, L"object"))
					{
						CHTMPObject* pObject = (CHTMPObject*)m_pFrame->m_htmTree->FindDOMElement(htmlelement);

						IUnknown* unk = pObject->m_pControl->m_spUnknown;

						if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
						{
							*ppiunkItem = unk;
							(*ppiunkItem)->AddRef();
						}

						if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
						{
							CComQIPtr<IProvideClassInfo2> classinfo = unk;
							if (classinfo)
							{
								classinfo->GetClassInfo(ppti);
								ASSERT(*ppti);
							}
						}
					}
					else
					{
						CComPtr<IUnknown> unk;
						m_pFrame->m_namedItems[i].m_pDisp->QueryInterface(IID_IUnknown, (void**)&unk);

						if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
						{
							*ppiunkItem = unk;
							(*ppiunkItem)->AddRef();
						}

						if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
						{
							CComQIPtr<IProvideClassInfo2> classinfo = unk;
							if (classinfo)
							{
								classinfo->GetClassInfo(ppti);
								ASSERT(*ppti);
							}
						}
					}
				}
				else
				{
					IUnknown* unk;
					m_pFrame->m_namedItems[i].m_pDisp->QueryInterface(IID_IUnknown, (void**)&unk);

					if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
					{
						*ppiunkItem = unk;
					//	(*ppiunkItem)->AddRef();
					}

					if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
					{
						CComQIPtr<IProvideClassInfo2> classinfo = unk;
						if (classinfo)
						{
							classinfo->GetClassInfo(ppti);
							ASSERT(*ppti);
						}
					}
				}

				return S_OK;
			}
		}
	}
#endif

	return TYPE_E_ELEMENTNOTFOUND;
}

STDMETHODIMP CScriptSite::GetDocVersionString( 
																		/* [out] */ BSTR __RPC_FAR *pbstrVersion)
{
	MessageBox(NULL, "", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CScriptSite::OnScriptTerminate( 
																	 /* [in] */ const VARIANT __RPC_FAR *pvarResult,
																	 /* [in] */ const EXCEPINFO __RPC_FAR *pexcepinfo)
{
	MessageBox(NULL, "", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CScriptSite::OnStateChange(/* [in] */ SCRIPTSTATE ssScriptState)
{
//	MessageBox(NULL, "", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CScriptSite::OnScriptError( 
																/* [in] */ IActiveScriptError __RPC_FAR *pscripterror)
{
//	ASSERT(0);
	DWORD dwSourceContext;
	ULONG ulLineNumber;
	LONG ichCharPosition;

	pscripterror->GetSourcePosition(&dwSourceContext, &ulLineNumber, &ichCharPosition);

	EXCEPINFO	excepinfo = {0};
	pscripterror->GetExceptionInfo(&excepinfo);

	if (!excepinfo.bstrDescription)
	{
		if (excepinfo.pfnDeferredFillIn)
		{
			excepinfo.pfnDeferredFillIn(&excepinfo);
		}
	}

	CUString str;
	str.Format(

		"Error in script\n"
		"line: %d, column: %d\n"
		"%S",

		ulLineNumber, ichCharPosition,
		excepinfo.bstrDescription);

	MessageBox(NULL, str, "MMStudio", MB_OK);

	return S_OK;
}

STDMETHODIMP CScriptSite::OnEnterScript( void)
{
//	MessageBox(NULL, "OnEnterScript", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CScriptSite::OnLeaveScript( void)
{
//	MessageBox(NULL, "OnLeaveScript", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CScriptSite::GetWindow(/* [out] */ HWND __RPC_FAR *phwnd)
{
	*phwnd = m_hWnd;
#if 0	// TODO Have this
	if (static_cast<CLHTMLActiveDocument*>(m_pDocument->m_acDocument)->m_view)
		*phwnd = static_cast<CLHTMLActiveDocument*>(m_pDocument->m_acDocument)->m_view->m_hWnd;
	else
		static_cast<CLHTMLActiveDocument*>(m_pDocument->m_acDocument)->m_spInPlaceSite->GetWindow(phwnd);
#endif

	return S_OK;
}

STDMETHODIMP CScriptSite::EnableModeless(/* [in] */ BOOL fEnable)
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IActiveScriptSiteDebug 
STDMETHODIMP CScriptSite::GetDocumentContextFromPosition(/*[in]*/ DWORD dwSourceContext,/*[in]*/
	ULONG uCharacterOffset,/*[in]*/ ULONG uNumChars,/*[out]*/ IDebugDocumentContext
	**ppsc) 
{ 	
	if (!ppsc) return E_POINTER; 
	*ppsc = NULL; 
	if (!m_debugDocumentHelper) return E_UNEXPECTED; 
	
	// every running document has a special "cookie" associated with it. 
	// this code assumes only 1 document with a cookie value stored in 
	// m_dwDocCookie. It then asks the helper interface IDebugDocumentHelper 
	// to convert from a character offset to a document context interface. 
	ULONG ulStartPos = 0;

	HRESULT hr = m_debugDocumentHelper->GetScriptBlockInfo(
		dwSourceContext/*m_dwDocCookie*/, NULL, &ulStartPos, NULL); 

	if (SUCCEEDED(hr))
	{
		return m_debugDocumentHelper->CreateDebugDocumentContext(ulStartPos + uCharacterOffset, uNumChars, ppsc);
	}
	return hr;
}

STDMETHODIMP CScriptSite::GetApplication(/*[out]*/ IDebugApplication **ppda)
{ 
	if (!ppda) return E_POINTER;
	*ppda = NULL; 
	if (!m_debugApp) return E_UNEXPECTED; 
	
	// return the IDebugApplication interface we created earlier.
	return m_debugApp.CopyTo( ppda ); 
} 

STDMETHODIMP CScriptSite::GetRootApplicationNode(/*[out]*/ IDebugApplicationNode
	**ppdanRoot) 
{ 
	// since we only have 1 document, we can safely return NULL here. 
	if ( !ppdanRoot ) return E_POINTER;
	*ppdanRoot = NULL;
	return S_OK;
}

STDMETHODIMP CScriptSite::OnScriptErrorDebug(/*[in]*/ IActiveScriptErrorDebug
	*pErrorDebug,/*[out]*/ BOOL *pfEnterDebugger,/*[out]*/ BOOL *pfCallOnScriptErrorWhenContinuing)
{ 
	// do something like query the IActiveScriptErrorDebug interface for more
	// info on what kind of error occurred.
	*pfEnterDebugger=TRUE;
	*pfCallOnScriptErrorWhenContinuing=TRUE;
	return S_OK; 
}

/////////////////////////////////////////////////////////////////////////////
// IApplicationDebugger 

STDMETHODIMP CScriptSite::QueryAlive(void)
{
	return S_OK;
}

STDMETHODIMP CScriptSite::CreateInstanceAtDebugger(/*[in]*/ REFCLSID rclsid,/*[in]*/ IUnknown *pUnkOuter,/*[in]*/ DWORD
	dwClsContext,/*[in]*/ REFIID riid,/*[out,iid_is(riid)]*/ IUnknown **ppvObject)
{ 
	return CoCreateInstance( rclsid,pUnkOuter,dwClsContext,riid,(void**)ppvObject	); 
} 

STDMETHODIMP CScriptSite::onDebugOutput(/*[in]*/ LPCOLESTR pstr ) 
{ 
	// do something such as pass the text on to the debugger GUI for display.
	return S_OK; 
} 

STDMETHODIMP CScriptSite::onHandleBreakPoint(/*[in]*/ IRemoteDebugApplicationThread *prpt,/*[in]*/ BREAKREASON br,/*[in]*/
	IActiveScriptErrorDebug *pError) 
{ 
	// do something such as notify the GUI that a breakpoint has occurred. 
	// be sure to hang on to the IRemoteDebugApplicationThread interface if you 
	// want to query the thread for the call stack, variables, etc. 
	// this is probably where the bulk of your code/logic will go.. 
	return S_OK; 
} 

STDMETHODIMP CScriptSite::onClose() 
{ 
	return S_OK;
}

STDMETHODIMP CScriptSite::onDebuggerEvent(/* [in] */ REFIID riid, /* [in] */ IUnknown __RPC_FAR *punk)
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IDebugSessionProvider 
STDMETHODIMP CScriptSite::StartDebugSession(/*[in]*/ IRemoteDebugApplication* pApp) 
{ 
	return pApp->ConnectDebugger(this);
} 

#endif