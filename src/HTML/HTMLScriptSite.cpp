#include "stdafx.h"

#if 0
#include "LHTML.h"
#include "LHTML2.h"

#include "HTMLScriptSite.h"

#include "LHTMLDocumentView.h"
#include "HTMControlFrameBase.h"

#include "LHTMLWindow.h"
#include "LHTMLDialog.h"

// IDispatch

STDMETHODIMP CHTMLScriptSiteBase::GetTypeInfoCount(unsigned int FAR *iTInfo)
{
	return m_pFrame->m_pScriptDisp->GetTypeInfoCount(iTInfo);
}

STDMETHODIMP CHTMLScriptSiteBase::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo)
{
	return m_pFrame->m_pScriptDisp->GetTypeInfo(iTInfo, lcid, ppTInfo);
}

// Script Site

STDMETHODIMP CHTMLScriptSiteBase::GetLCID( 
														/* [out] */ LCID __RPC_FAR *plcid)
{
	return E_NOTIMPL;	// Use default locale
}


#include "LHTML2.h"
#include "tag_Object.h"

#include "LHTMLDocumentView.h"
//#include "HTMControlFrameBase.h"

#if 0
#include "ActiveXContainer.h"
#endif

STDMETHODIMP CHTMLScriptSiteBase::GetItemInfo( 
															 /* [in] */ LPCOLESTR pstrName,
															 /* [in] */ DWORD dwReturnMask,
															 /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiunkItem,
															 /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppti)
{
	if (dwReturnMask & SCRIPTINFO_IUNKNOWN) *ppiunkItem = NULL;
	if (dwReturnMask & SCRIPTINFO_ITYPEINFO) *ppti = NULL;

	if (!wcscmp(pstrName, L"globalwindow"))
	{
		IUnknown* unk;
	//	m_pFrame->m_pHTMLWindowImpl->QueryInterface(IID_IMMSXHTMLWindow, (void**)&unk);
//		m_pFrame->m_pHTMLWindowImpl->QueryInterface(IID_IUnknown, (void**)&unk);

		m_pFrame->m_spScriptSite->QueryInterface(IID_IUnknown, (void**)&unk);

		if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
		{
			*ppiunkItem = unk;
			//(*ppiunkItem)->AddRef();	// ??
		}

		if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
		{
			ASSERT(0);
#if 0
			m_pFrame->m_pHTMLWindowImpl->GetTypeInfo(0, 0, ppti);
#endif
		}

		return S_OK;
	}
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

	return TYPE_E_ELEMENTNOTFOUND;
}

STDMETHODIMP CHTMLScriptSiteBase::GetDocVersionString( 
																		/* [out] */ BSTR __RPC_FAR *pbstrVersion)
{
	MessageBox(NULL, "", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CHTMLScriptSiteBase::OnScriptTerminate( 
																	 /* [in] */ const VARIANT __RPC_FAR *pvarResult,
																	 /* [in] */ const EXCEPINFO __RPC_FAR *pexcepinfo)
{
	MessageBox(NULL, "", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CHTMLScriptSiteBase::OnStateChange(/* [in] */ SCRIPTSTATE ssScriptState)
{
//	MessageBox(NULL, "", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CHTMLScriptSiteBase::OnScriptError( 
																/* [in] */ IActiveScriptError __RPC_FAR *pscripterror)
{
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

STDMETHODIMP CHTMLScriptSiteBase::OnEnterScript( void)
{
//	MessageBox(NULL, "OnEnterScript", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CHTMLScriptSiteBase::OnLeaveScript( void)
{
//	MessageBox(NULL, "OnLeaveScript", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CHTMLScriptSiteBase::GetWindow(/* [out] */ HWND __RPC_FAR *phwnd)
{
	*phwnd = m_pFrame->m_pUI->m_hWnd;
	return S_OK;
}

STDMETHODIMP CHTMLScriptSiteBase::EnableModeless(/* [in] */ BOOL fEnable)
{
	return S_OK;
}

/*
STDMETHODIMP CHTMFrameNode::showModalDialog(BSTR dialog, VARIANT *varArgIn, VARIANT *varOptions, VARIANT* varArgOut)
{
	// TODO: Add your implementation code here

	return S_OK;
}
*/

STDMETHODIMP CHTMLScriptSiteBase::get_frames(ILHTMLFramesCollection* *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}


//////////////////////

STDMETHODIMP CHTMLScriptSite::GetIDsOfNames(
		REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid
	)
{
	ASSERT(0);

	HRESULT hr = 0;
#if 0
	hr = m_pFrame->m_pHTMLWindowImpl->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);
	if (FAILED(hr)) hr = m_pFrame->m_pHTMLDialogImpl->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);
	if (FAILED(hr))
	{
		hr = m_pFrame->m_pScriptDisp->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);

		if (SUCCEEDED(hr))
		{
			if (*rgdispid < 100)
				ASSERT(0);
		}
	}
#endif
	return hr;
}

STDMETHODIMP CHTMLScriptSite::Invoke(
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
	ASSERT(0);
	HRESULT hr = 0;
#if 0

	hr = m_pFrame->m_pHTMLWindowImpl->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	if (FAILED(hr)) hr = m_pFrame->m_pHTMLDialogImpl->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	if (FAILED(hr)) hr = m_pFrame->m_pScriptDisp->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
#endif
	return hr;
}

STDMETHODIMP CHTMLScriptSite::setActiveElement(ILDOMElement *element)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CHTMLScriptSite::get_screen(IHTMLScreen **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CHTMLScriptSite::svgGetScreenBBox(ILSVGElement *element, ILSVGRect **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

#endif