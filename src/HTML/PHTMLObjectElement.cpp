#include "stdafx.h"
#include "HTML2.h"

#if 0

#include "PHTMLObjectElement.h"
#include "LHTMLObjectElement.h"

#include "LBoxWindow.h"
#include "LXMLDocumentView.h"
#include "HTMContext.h"
#include "PBlockBox.h"

//#include "ActiveXContainer.h"

class CActiveXEvent
{
public:
	_bstr_t	m_name;
	DISPID	m_memberid;
};

class CActiveXDispEvent : public IDispatch
{
public:
///	GUID m_libid; // used for dynamic case
	IID m_iid; // used for dynamic case
	DWORD	m_dwCookie;
	CArray<CActiveXEvent*, CActiveXEvent*> m_events;

	CActiveXDispEvent()
	{
		m_dwCookie = 0;	// 0xff ??
	}

	STDMETHOD(QueryInterface)(REFIID riid, void ** ppvObject)
	{
		if (::InlineIsEqualGUID(riid, m_iid) || 
			InlineIsEqualUnknown(riid) ||
			::InlineIsEqualGUID(riid, IID_IDispatch) ||
			::InlineIsEqualGUID(riid, m_iid))
		{
			if (ppvObject == NULL)
				return E_POINTER;
			*ppvObject = this;
			AddRef();
/*
#ifdef _ATL_DEBUG_INTERFACES
			_Module.AddThunk((IUnknown**)ppvObject, _T("IDispEventImpl"), riid);
#endif // _ATL_DEBUG_INTERFACES
			*/
			return S_OK;
		}
		else
			return E_NOINTERFACE;
	}

	// These are here only to support use in non-COM objects	
	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return 1;
	}
	virtual ULONG STDMETHODCALLTYPE Release()
	{
		return 1;
	}

	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)
	{return E_NOTIMPL;}

	STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
	{return E_NOTIMPL;}

	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid)
	{return E_NOTIMPL;}

	STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid,
		LCID lcid, WORD /*wFlags*/, DISPPARAMS* pdispparams, VARIANT* pvarResult,
		EXCEPINFO* /*pexcepinfo*/, UINT* /*puArgErr*/)
	{
		CActiveXEvent* pEvent = NULL;

		for (int i = 0; i < m_events.GetSize(); i++)
		{
			if (m_events[i]->m_memberid == dispidMember)
			{
				pEvent = m_events[i];
				break;
			}
		}

		if (pEvent)
		{

		}

		return S_OK;
	}
};

/*
BOOL CCOMObjectBase::IsDataSource()
{
	CComQIPtr<IDispatch> pDisp = m_spUnknown;

	ITypeInfo* pTInfo;
	HRESULT hr = pDisp->GetTypeInfo(0, NULL, &pTInfo);

	TYPEATTR* pType;
	pTInfo->GetTypeAttr(&pType);

	for (int i = 0; i < pType->cFuncs; i++)
	{
		FUNCDESC* pFuncDesc = NULL;
		if (SUCCEEDED(pTInfo->GetFuncDesc(i, &pFuncDesc)))
		{
			BSTR bname;
			UINT pcNames;
			pTInfo->GetNames(pFuncDesc->memid, &bname, 1, &pcNames);
			_bstr_t name = _bstr_t(bname, FALSE);

			if (!wcscmp(name, L"msDataSourceObject"))
			{
				m_msDataSourceObjectDispID
				SysFreeString(varargs[0].bstrVal);
				SysFreeString(varargs[0].bstrVal);
			}

			pTInfo->ReleaseFuncDesc(pFuncDesc);

			if (dataSource != NULL) break;
		}
	}

	pTInfo->Release();
}
*/

#if 0
IUnknown* CCOMObjectBase::GetDataSourceUnknown()
{
	IUnknown* dataSource = NULL;

	CComQIPtr<IDispatch> pDisp = m_spUnknown;
	ATLASSERT(pDisp != NULL);

	ITypeInfo* pTInfo;
	HRESULT hr = pDisp->GetTypeInfo(0, NULL, &pTInfo);
	if (SUCCEEDED(hr))
	{
		DISPID	memid = -3900;

		DISPPARAMS dispparams;
		VARIANTARG varargs[1];
		dispparams.cArgs = 1;
		dispparams.cNamedArgs = 0;
		dispparams.rgvarg = varargs;
		dispparams.rgdispidNamedArgs = NULL;

		VariantInit(&varargs[0]);
		varargs[0].vt = VT_BSTR;
		varargs[0].bstrVal = SysAllocString(L"");

		VARIANT varresult;
		VariantInit(&varresult);

		EXCEPINFO	excepinfo;
		UINT argErr;
		HRESULT hr = pDisp->Invoke(memid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparams, &varresult, &excepinfo, &argErr);
		if (SUCCEEDED(hr))
		{
			dataSource = varresult.punkVal;
		}

		SysFreeString(varargs[0].bstrVal);

		pTInfo->Release();
	}

	return dataSource;
}
#endif

/*

Author-Time Discovery of Path Properties

Authoring tools and other containers will want to know exactly which control properties are, in fact, data path properties as well as the type of data that should be referenced through each property. This allows the authoring tool to effectively enumerate data paths and retrieve their current values, which is useful when the authoring tool needs to update any such properties to perform link management. 

First, to determine if any particular control has any path properties, the authoring tool should perform the following actions: 

Retrieve the control's type information for its coclass either through IProvideClassInfo::GetClassInfo or from the type library directly. These methods result in anITypeInfo interface for that part of the type library. 
Call ITypeInfo::QueryInterface(IID_ITypeInfo2, &pITypeInfo2) to retrieve the interface necessary to read custom attributes. If this interface does not exist, the container has to assume that no path properties exist. 
Call pITypeInfo2->GetCustData(GUID_HasPathProperties, &va) to retrieve the value of the custom attribute into theVARIANT in va. If this function fails, or if the value in va is empty or zero, the control has no path properties. 
Having this knowledge in hand, the authoring tool can then enumerate the properties in any of the control's incoming interfaces and check if those properties are data paths using the following procedure. These steps assume that pTI2 is the ITypeinfo2 pointer to one of the control's interface or dispinterface entries (available through theITypeInfo of the control's coclass): 

Get the count of the functions in the interface using pTI2->GetTypeAttr which returns a TYPEATTR whose cFuncs field has the number of function. Call pTI2->ReleaseTypeAttr when finished. 
Iterate in a for loop where the index counter (index) begins at zero and counts to cFuncs-1 (cFuncs is from step 1) through the functions. 
For each function, call pTI2->GetFuncCustData(index, GUID_PathProperty, &va) to attempt to read the custom path property attribute's value into the VARIANT va. 
If the GetFuncCustData call fails, or if the contents of va are empty, this property is not a data path. On success, the property is a data path and the value in va will be the description of the MIME type. 
To determine the dispID of the property, call pTI2->GetFuncDesc and look in the FUNCDESC structure for the memid field, which is the dispID. Be sure to call pTI2->ReleaseFuncDesc when done with the FUNCDESC structure. 
For optimization purposes, one can count the number of path properties found so far and exit the loop early if that number matches the value that was read from the GUID_HasPathProperties in the steps used to determine if the control had any paths. 
Once the loop is complete, the authoring tool will have a list of dispIDs (which may have some duplicates) for all the control's data path properties. The authoring tool can use pTI2->GetNames with these dispIDs to retrieve text names for those properties. 
What then does a tool do with such knowledge of paths and their data types? There are three general scenarios: 

If the authoring tool is interactive, it might be able to display the data browsing UI based on the data format associated with any given path property. That is, if the tool knows that a path property uses the MIME type given in the value of the GUID_PathProperty attribute and that tool has a UI that can browse for that type, the tool can enable a "..." button in its property browser UI that invokes a File/Open type of dialog box when pressed. The user then selects a file and the name of that data file is assigned to the path property. 
If the authoring tool is automatic, it uses other available information (for example, a data repository) to determine the source of any particular piece of data. Knowing the format that the control needs for a data path allows such a tool to find some appropriate data, create a path name for it, and assign that name to the control. 
When the authoring tool publishes a document to an Internet site, it will want to check for any dependencies on outside data—that is, it will want to check for any control properties that reference data outside the document. The authoring tool can then check whether that path will be valid at run time and if not, it can choose to relocate the data to an accessible location and assign a new path to the control before saving that control. This is necessary, for example, when a control references a file on the local file system when the document is being placed on an Internet site. 

 */

const GUID GUID_PathProperty = { 0x0002DE80, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
const GUID GUID_HasPathProperties = {0x0002DE81, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

void CPHTMLObjectElement::GetObjectDataPaths()
{
	ATLASSERT(0);
#if 0
	CComQIPtr<IProvideClassInfo2> classinfo = m_pControl->m_spUnknown;

	if (classinfo)
	{
		ITypeInfo* pTInfo;
		HRESULT hr = classinfo->GetClassInfo(&pTInfo);

	// Needed to retrieve custom properties
		ITypeInfo2* pTInfo2;
		pTInfo->QueryInterface(IID_ITypeInfo2, (void**)&pTInfo2);
		if (pTInfo2)
		{
			VARIANT va;
			pTInfo2->GetCustData(GUID_HasPathProperties, &va);
			if (va.vt != VT_EMPTY)	// TODO, or zero
			{
				TYPEATTR* pType;
				pTInfo2->GetTypeAttr(&pType);

				for (int i = 0; i < pType->cFuncs; i++)
				{
					FUNCDESC* pFuncDesc = NULL;
					if (SUCCEEDED(pTInfo2->GetFuncDesc(i, &pFuncDesc)))
					{
						VARIANT pathdataVA;
						if (pTInfo2->GetFuncCustData(i, GUID_PathProperty, &pathdataVA) == S_OK)
						{
							if (pathdataVA.vt != VT_EMPTY)
							{
								ATLTRACE("dispid %d is a datapath\n", i);
							}
						}

						pTInfo2->ReleaseFuncDesc(pFuncDesc);
					}
				}

				pTInfo2->ReleaseTypeAttr(pType);
			}

			pTInfo2->Release();
		}

		pTInfo->Release();
	}
#endif
}

#if 0
void CHTMPObject::LoadObject()
{
	if (m_pControl)
	{
		delete m_pControl;
		m_pControl = NULL;
	}

	CComQIPtr<ILDOMElement> element = m_pNode;
	ATLASSERT(element != NULL);

}
#endif

#if 0
//virtual
void CHTMPObject::CalculateDimensions(CHTMCalcContext* pC)
{
#if 0	// TODO, removed this, I don't think this should be here?
	GetCSSProperties();
#endif

	CComQIPtr<ILDOMElement> pElement = m_pNode;

	if (m_pControl)
	{
		if (!m_pControl->m_hWnd)
		{
			ATLASSERT(0);
#if 0	// Had this
			ATLASSERT(m_pWindow->m_pUI->m_hWnd);
			m_pControl->m_hWnd = m_pWindow->m_pUI->m_hWnd;
#endif
			m_pControl->ActivateAx(/*FALSE, NULL*/);

			GetObjectDataPaths();

			CComPtr<IUnknown> dataSource = m_pControl->GetDataSourceUnknown();
			if (dataSource)
			{
				MessageBox(NULL, "datasource", "", MB_OK);
			}
		}

		if (m_pControl->m_hWnd)
		{
			m_computedWidth = m_specifiedWidth = m_pControl->m_pxSize.cx;//atol(pElement->getAttribute("WIDTH"));
			m_computedHeight = m_specifiedHeight = m_pControl->m_pxSize.cy;//atol(pElement->getAttribute("HEIGHT"));
		}

		{
			BSTR b;

			pElement->getAttribute(L"width", &b);
			_bstr_t strwidth = _bstr_t(b, false);

			pElement->getAttribute(L"height", &b);
			_bstr_t strheight = _bstr_t(b, false);

			if (strwidth.length()) m_computedWidth = m_specifiedWidth = atol(strwidth);
			if (strheight.length()) m_computedHeight = m_specifiedHeight = atol(strheight);
		}
	}
	else
	{
		m_computedWidth = m_specifiedWidth = 80;
		m_computedHeight = m_specifiedHeight = 80;
	}
}

void CPHTMLObjectElement::CreateControls(CHTMContext* pC)
{
}
#endif

void CPHTMLObjectElement::PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC)
{
	CLHTMLObjectElement* pElement = static_cast<CLHTMLObjectElement*>(m_pNode);

	if (m_pBox)
	{
		Gdiplus::RectF rcf = m_pBox->GetAbsInnerRect();

		if (pElement->m_pOleObjectSite == NULL)
		{
			pElement->Load();
		}

		if (pElement->m_pOleObjectSite)
		{
			CRect rcPos((int)rcf.X, (int)rcf.Y, (int)rcf.GetRight(), (int)rcf.GetBottom());
			CRect rcClip = rcPos;

			GetVisibleRect(rcPos, rcClip);

			if (pElement->m_pOleObjectSite->m_hWndParent == NULL)
			{
				pElement->m_pOleObjectSite->ActivateAx(hWndParent);
			}
			else
			{
				pElement->m_pOleObjectSite->m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, NULL, 0, NULL, NULL);
#if 0
				m_spOleObject->DoVerb(OLEIVERB_HIDE, NULL, spClientSite, 0, m_hWnd, &m_rcPos);
#endif
			}

			pElement->m_pOleObjectSite->OnSize(rcPos, rcClip);
		}
#if 0
		if (m_pControl)
		{

		rcPos.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);
			rcClip.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);
			m_pControl->OnSize(rcPos, rcClip);
		}
#endif
	}
	else
	{
		if (pElement->m_pOleObjectSite)
		{
			if (pElement->m_pOleObjectSite->m_spOleObject)
			{
				pElement->m_pOleObjectSite->m_spOleObject->DoVerb(OLEIVERB_HIDE, NULL, NULL, 0, NULL, NULL);
			}
		}
	}
}

BOOL CALLBACK continueDraw(DWORD)
{
	return TRUE;
}

//virtual
void CPHTMLObjectElement::Draw(CHTMRenderContext* pC)
{
	Gdiplus::RectF trect = m_pBox->GetAbsInnerRect();

//	Draw3DRect(pC->m_hDC, &trect, RGB(80, 80, 80), RGB(20, 20, 20));

#if 0
	if (m_pControl)
	{
		if (m_pControl->m_hWnd && m_pControl->m_spViewObject)
		{
			if (m_pControl->m_bWindowless)
			{
				RECTL	rectl;
				rectl.left = m_pControl->m_rcPos.left;
				rectl.top = m_pControl->m_rcPos.top;
				rectl.right = m_pControl->m_rcPos.right;
				rectl.bottom = m_pControl->m_rcPos.bottom;

				DVASPECTINFO	dv;
				dv.cb = sizeof(dv);
				dv.dwFlags = 0;

				HDC hDC = pC->m_pGraphics->GetHDC();

				HRESULT hr = m_pControl->m_spViewObject->Draw(DVASPECT_CONTENT, -1, &dv, NULL, NULL,
					hDC,
					NULL,//&rectl,
					NULL,//&rectl,
					continueDraw,
					0 // value to pass to callback function
					);

				pC->m_pGraphics->ReleaseHDC(hDC);
			}
		}
	}
	else	// Broken image, show broken image bitmap
	{
#if 0
		HDC hDC = CreateCompatibleDC(NULL);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, pC->m_hBrokenImageBitmap);
		
		Draw3DRect(pC->m_hDC, &trect, RGB(200, 200, 200), RGB(100, 100, 100));

		BitBlt(
			pC->m_hDC, trect.left+2, trect.top+2, 16, 16,
			hDC, 0, 0, SRCCOPY);
		
		SelectObject(hDC, hOldBitmap);
		DeleteDC(hDC);
#endif
	}
#endif
}

#if 0
BOOL CPHTMLObjectElement::OnButtonDown(CComObject<CHTMLWindow>* pFrame, POINT point)
{
	Gdiplus::RectF trect = m_pBox->GetAbsInnerRect();
	if (trect.Contains(point.x, point.y))
	{
		if (m_pControl && m_pControl->m_spInPlaceObjectWindowless)
		{
			if (m_pControl->m_bWindowless)
			{
				WPARAM wparam = 0;
				LPARAM lparam = MAKELPARAM(point.x, point.y);

				LRESULT lresult = 0;

				HRESULT hr = m_pControl->m_spInPlaceObjectWindowless->OnWindowMessage(WM_LBUTTONDOWN, wparam, lparam, &lresult);
				if (hr == S_OK)
					return TRUE;
			}
		}
	}

	return FALSE;
}
#endif

#if 0	// TODO, have something like this

ButtonDown()
{
	if (m_spInPlaceObjectWindowless && m_bWindowless)
	{
		WPARAM wparam = 0;
		LPARAM lparam = MAKELPARAM(point.x, point.y);

		LRESULT lresult = 0;

		HRESULT hr = m_pOCItemCapture->m_spInPlaceObjectWindowless->OnWindowMessage(WM_MOUSEMOVE, wparam, lparam, &lresult);
		if (hr == S_OK) return;
	}
}

ButtonUp()
{
	if (m_pOCItemCapture->m_spInPlaceObjectWindowless && m_pOCItemCapture->m_bWindowless)
	{
		WPARAM wparam = 0;
		LPARAM lparam = MAKELPARAM(point.x, point.y);

		LRESULT lresult = 0;

		HRESULT hr = m_pOCItemCapture->m_spInPlaceObjectWindowless->OnWindowMessage(WM_LBUTTONUP, wparam, lparam, &lresult);
		if (hr == S_OK) return;
	}
}

#endif

#endif