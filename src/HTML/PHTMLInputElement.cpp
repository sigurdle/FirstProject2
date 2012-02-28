#include "stdafx.h"
#include "HTML2.h"

#if 0

#include "PHTMLInputElement.h"

//#include "LHTMLWindow.h"
#include "LBoxWindow.h"
#include "LXMLDocumentView.h"

//#include "LHTMLDocumentView.h"

#include "HTMContext.h"
#include "PBlockBox.h"

CHTMPInput::CHTMPInput()
{
	m_pControl = NULL;
	m_reentrance = 0;
}

CHTMPInput::~CHTMPInput()
{
	if (m_pControl)
	{
		m_pControl->IDispEventImpl<1, CInputObjectBase, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_pControl->m_spUnknown);

		m_pControl->ReleaseAll();
		m_pControl->Release();
		m_pControl = NULL;
	}
}

_bstr_t CHTMPInput::GetAttributeType()
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

	BSTR btype;
	element->getAttribute(L"type", &btype);
	_bstr_t str_type = _bstr_t(btype, false);
	if (str_type.length() == 0) str_type = L"text";

	return str_type;
}

_bstr_t CHTMPInput::GetAttributeValue()
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

	BSTR bvalue;
	element->getAttribute(L"value", &bvalue);
	_bstr_t str_value = _bstr_t(bvalue, false);
	if (str_value.length() == 0) str_value = L"";

	return str_value;
}

long CHTMPInput::GetAttributeSize()
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

	BSTR bsize;
	element->getAttribute(L"size", &bsize);
	_bstr_t str_size = _bstr_t(bsize, false);
	if (str_size.length() == 0)
		return 0;
	else
		return atol(str_size);
}

void CHTMPInput::CalculateDimensions(CHTMCalcContext* pC)
{
	CHTMPElement::CalculateDimensions(pC);

	CComQIPtr<ILHTMLElement> element = m_pNode;

	long size = GetAttributeSize();

	if (size > 0)
	{
		m_specifiedWidth = m_computedWidth = max(size*14, 14);
	}
	else
	{
		_bstr_t type = GetAttributeType();
		_bstr_t value = GetAttributeValue();

		if (!wcsicmp(type, L"button"))
		{
			//SIZE size;
			//GetTextExtentPoint32(pC->m_hDC, value, value.length(), &size);

			Gdiplus::RectF size;
			pC->m_pGraphics->MeasureString(value, value.length(), m_computedFontFamily[0]->GetGdipFont(), Gdiplus::PointF(0,0), &size);

			m_specifiedWidth = m_computedWidth = size.Width;

			m_specifiedHeight += 8;	// Make room for button border
			m_computedHeight += 8;
		}
		else if (!wcsicmp(type, L"checkbox"))
		{
			m_specifiedWidth = m_computedWidth = 18;
		}
		else	// text
		{
			m_specifiedWidth = m_computedWidth = 20;//max(size*14, 32);
		}
	}

	m_specifiedHeight = m_computedHeight = 18;
//	m_size = m_minsize;
}

void CHTMPInput::OnSetAttribute(BSTR attrName)
{
	if (m_reentrance == 0)
	{
		m_reentrance++;

		CComQIPtr<ILHTMLElement> element = m_pNode;

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

		m_reentrance--;
	}
}

HRESULT __stdcall CInputObjectBase::OnChange()
{
	ASSERT(m_pPElement);

	if (m_pPElement->m_reentrance == 0)
	{
		m_pPElement->m_reentrance++;

		CComQIPtr<IUIEdit> edit = m_spUnknown;

		BSTR text;
		edit->GetText(&text);

		CComQIPtr<ILDOMElement> element = m_pPElement->m_pNode;
		element->setAttribute(L"value", text);

		SysFreeString(text);

		CComQIPtr<ILDOMDocument> document;
		m_pPElement->m_pNode->get_ownerDocument(&document);

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

		m_pPElement->m_reentrance--;
	}

	return S_OK;
}

HRESULT __stdcall CInputObjectBase::OnClick()
{
	ASSERT(m_pPElement);

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
	evt->initUIEvent(L"click",
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

void CHTMPInput::CreateControls(CHTMContext* pC)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLElement> element = m_pNode;

	if (pC->m_pUI)
	{
		_bstr_t str_type = GetAttributeType();

		if (!m_pControl)
		{
			_bstr_t value = GetAttributeValue();

			m_pControl = new CInputObject;
			m_pControl->m_pPElement = this;
			m_pControl->AddRef();
			m_pControl->m_hWnd = m_pWindow->m_pUI->m_hWnd;
			m_pControl->m_pWindow = m_pWindow;

#if 0
			if (!wcsicmp(str_type, L"button"))
			{
				m_pControl->m_spUnknown.CoCreateInstance(CLSID_UIButton);
				CComQIPtr<IUIButton> button = m_pControl->m_spUnknown;
				button->set_type(0);

				m_pControl->Connect(FALSE, NULL);
				m_pControl->ActivateAx();

				m_pControl->IDispEventImpl<2, CInputObjectBase, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_pControl->m_spUnknown);

				if (value.length() > 0)
				{
					button->put_text(value);
				}
			}
			else if (!wcsicmp(str_type, L"checkbox"))
			{
				m_pControl->m_spUnknown.CoCreateInstance(CLSID_UIButton);
				CComQIPtr<IUIButton> button = m_pControl->m_spUnknown;
				button->put_type(1);

				m_pControl->Connect(FALSE, NULL);
				m_pControl->ActivateAx();

				m_pControl->IDispEventImpl<2, CInputObjectBase, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_pControl->m_spUnknown);

				if (value.length() > 0)
				{
					//button->put_text(value);
				}
			}
			else
#endif
			{
				m_pControl->m_spUnknown.CoCreateInstance(CLSID_UIEdit);
				CComQIPtr<IUIEdit> edit = m_pControl->m_spUnknown;

				m_pControl->Connect(FALSE, NULL);
				m_pControl->ActivateAx();

				m_pControl->IDispEventImpl<1, CInputObjectBase, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_pControl->m_spUnknown);

				if (value.length() > 0)
				{
					edit->SetText(value);
				}
			}
		}
	}
#endif
}

void CHTMPInput::PlaceControls(HWND hWndParent, CHTMContext* /* pC*/)
{
	ASSERT(0);
#if 0
	if (m_pControl)
	{
		Gdiplus::Rect rcPos = m_pBox->GetAbsInnerRect();
		CRect rcClip = rcPos;

		GetVisibleRect(rcPos, rcClip);

		//rcPos.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);
		//rcClip.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);

		m_pControl->OnSize(rcPos, rcClip);
	}
#endif
}

void CHTMPInput::Draw(CHTMRenderContext* pC)
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

BOOL CHTMPInput::OnButtonDown(CComObject<CHTMLWindow>* pFrame, POINT point)
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