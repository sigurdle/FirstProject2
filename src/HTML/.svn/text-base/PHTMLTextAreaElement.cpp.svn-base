#include "stdafx.h"
#include "HTML2.h"

#include "PHTMLTextAreaElement.h"

//#include "LHTMLWindow.h"

//#include "LHTMLDocumentView.h"

#include "../LXML/HTMContext.h"
//#include "PBlockBox.h"

namespace System
{
namespace Web
{

CHTMPTextArea::CHTMPTextArea(HTMLElement* element) : PHTMLElement(element)
{
//	m_pControl = NULL;
}

CHTMPTextArea::~CHTMPTextArea()
{
	/*
	if (m_pControl)
	{
		m_pControl->IDispEventImpl<1, CTextAreaObjectBase, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_pControl->m_spUnknown);

		m_pControl->ReleaseAll();
		m_pControl->Release();
		m_pControl = NULL;
	}
	*/
}

#if 0
long CHTMPTextArea::GetAttributeCols()
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

	BSTR bsize;
	element->getAttribute(L"cols", &bsize);
	_bstr_t str_size = _bstr_t(bsize, false);
	if (str_size.length() == 0)
		return 0;
	else
		return atol(str_size);
}

long CHTMPTextArea::GetAttributeRows()
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

	BSTR bsize;
	element->getAttribute(L"rows", &bsize);
	_bstr_t str_size = _bstr_t(bsize, false);
	if (str_size.length() == 0)
		return 0;
	else
		return atol(str_size);
}
#endif

void CHTMPTextArea::CalculateDimensions(CHTMCalcContext* pC)
{
	PHTMLElement::CalculateDimensions(pC);

	/*
	CComQIPtr<ILHTMLElement> element = m_pNode;

	long cols = GetAttributeCols();
	long rows = GetAttributeRows();

	m_specifiedWidth = m_computedWidth = max(cols*14, 14);
	m_specifiedHeight = m_computedHeight = max(rows*14, 14);
	*/
}

void CHTMPTextArea::OnSetAttribute(System::StringW* attrName)
{
//	CComQIPtr<ILHTMLElement> element = m_pNode;

/*
	if (!wcsicmp(attrName, L"value"))
	{
		if (m_pControl)
		{
			BSTR bvalue;
			element->getAttribute(L"value", &bvalue);
			_bstr_t value = _bstr_t(bvalue, false);
			if (value.length() == 0) value = L"";

			CComQIPtr<IUIEdit> edit = m_pControl->m_spUnknown;
			edit->SetText(value);
		}
	}
*/
}

#if 0
HRESULT __stdcall CTextAreaObjectBase::OnChange()
{
	ASSERT(m_pPElement);

	CComQIPtr<IUIEdit> edit = m_spUnknown;

	BSTR text;
	edit->GetText(&text);

	CComQIPtr<ILDOMElement> element = m_pPElement->m_pNode;
	element->setAttribute(L"value", text);

	SysFreeString(text);

	CComQIPtr<ILDOMDocument> document;
	m_pPElement->m_pNode->get_ownerDocument(&document);

//	m_documentContainer->get_document(&document);

	CComQIPtr<ILDOMElement> documentElement;
	document->get_documentElement(&documentElement);
/*
clientX and clientY parameters for mouse events represent viewport
coordinates for the corresponding 'svg' element.

relatedNode is the corresponding outermost 'svg' element
*/
	CComQIPtr<ILDOMDocumentEvent> documentEvent = document;
	ASSERT(documentEvent != NULL);

	CComQIPtr<ILDOMEventTarget> relatedTarget = documentElement;//m_pDocument->GetSvgElement()->m_domElement;
	ASSERT(relatedTarget != NULL);

	CComQIPtr<ILDOMUIEvent> evt;
	documentEvent->createEvent(L"UIEvents", (ILDOMEvent**)&evt);
	evt->initUIEvent(L"change",
		TRUE,	// bubbles
		TRUE,	// cancelable
		NULL,	// viewArg
		0		// detail
		/*
		point.x, point.y,	// screen
		point.x, point.y, // client,
		(nFlags & MK_CONTROL)? TRUE: FALSE,
		(nFlags & MK_SHIFT)? TRUE: FALSE,
		(nFlags & MK_ALT)? TRUE: FALSE,
		0,	// meta
		iButton,
		relatedTarget
		*/
		);

#if 0
	m_pWindow->m_eventObj = evt;
#endif

	CComQIPtr<ILDOMEventTarget> target = m_pPElement->m_pNode;

	bool doDefault;
	target->dispatchEvent(evt, &doDefault);

	return S_OK;
}
#endif

#if 0
void CHTMPTextArea::CreateControls(CHTMContext* pC)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLElement> element = m_pNode;

	if (pC->m_pUI)
	{
		if (!m_pControl)
		{
			//_bstr_t value = GetAttributeValue();

			m_pControl = new CTextAreaObject;
			m_pControl->m_pPElement = this;
			m_pControl->AddRef();
			m_pControl->m_hWnd = m_pWindow->m_pUI->m_hWnd;
			m_pControl->m_pWindow = m_pWindow;

			{
				m_pControl->m_spUnknown.CoCreateInstance(CLSID_UIEdit);
				CComQIPtr<IUIEdit> edit = m_pControl->m_spUnknown;

				m_pControl->Connect(FALSE, NULL);
				m_pControl->ActivateAx();

				m_pControl->IDispEventImpl<1, CTextAreaObjectBase, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_pControl->m_spUnknown);

				/*
				if (value.length() > 0)
				{
					edit->SetText(value);
				}
				*/
			}
		}
	}
#endif
}

void CHTMPTextArea::PlaceControls(HWND hWndParent, CHTMContext* /* pC*/)
{
	ASSERT(0);
#if 0
	if (m_pControl)
	{
		if (m_pBox)
		{
			CRect rcPos = m_pBox->GetAbsInnerRect();
			CRect rcClip = rcPos;

			GetVisibleRect(rcPos, rcClip);

			//rcPos.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);
			//rcClip.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);

			m_pControl->OnSize(rcPos, rcClip);
		}
	}
#endif
}

void CHTMPTextArea::Draw(CHTMRenderContext* pC)
{
	if (m_pControl && m_pControl->m_spViewObject)
	{
		if (m_pControl->m_bWindowless)
		{
			DVASPECTINFO	dv;
			dv.cb = sizeof(dv);
			dv.dwFlags = 0;

			HDC hDC = pC->m_pGraphics->GetHDC();

			HRESULT hr = m_pControl->m_spViewObject->Draw(DVASPECT_CONTENT, -1, &dv, NULL, NULL,
				hDC,
				NULL,//&rectl,
				NULL,//&rectl,
				NULL,	// continueDraw
				0 // value to pass to callback function
				);

			pC->m_pGraphics->ReleaseHDC(hDC);
		}
	}
}

BOOL CHTMPTextArea::OnButtonDown(POINT point, CPElement* *pVal)
{
	ASSERT(0);
#if 0
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
#endif
	return FALSE;
}
#endif

}	// Web
}
