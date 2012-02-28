#include "stdafx.h"
#include "HTML2.h"

#include "PHTMLSelectElement.h"

//#include "LHTMLWindow.h"

//#include "LHTMLDocumentView.h"

#include "../LXML/HTMContext.h"

#if 0

CHTMPSelect::CHTMPSelect()
{
	//m_pControl = NULL;
}

CHTMPSelect::~CHTMPSelect()
{
	/*
	if (m_pControl)
	{
		m_pControl->Release();
		m_pControl = NULL;
	}
	*/
}


void CHTMPSelect::TraverseOPTIONEntries()
{
	m_options.RemoveAll();

	CComQIPtr<ILHTMLElement> element = m_pNode;

	CComQIPtr<ILDOMNode> child;
	element->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> option = child;

		if (option)
		{
			BSTR btagName;
			option->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcsicmp(tagName, L"option"))
			{
				m_options.Add(option);
			}
		}

		CComQIPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}

long CHTMPSelect::GetAttributeSize()
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

	long lsize;

	BSTR bsize;
	element->getAttribute(L"size", &bsize);
	_bstr_t size = _bstr_t(bsize, false);
	if (size.length()) lsize = atol(size);
	else lsize = 1;

	return lsize;
}

BOOL CHTMPSelect::GetAttributeMultiple()
{
	return FALSE;
}

void CHTMPSelect::CalculateDimensions(CHTMCalcContext* pC)
{
#if 0	// TODO, removed this, I don't think this should be here?
	CHTMPElement::GetCSSProperties(pC);
#endif

	CComQIPtr<ILHTMLElement> element = m_pNode;

	TraverseOPTIONEntries();

	int maxx = 0;

	long lsize = GetAttributeSize();

	for (int i = 0; i < m_options.GetSize(); i++)
	{
		CComQIPtr<ILHTMLElement> pOption = m_options[i];//->m_pNode;

		//BSTR btext;
		//pOption->get_innerText(&btext);
		//_bstr_t text = _bstr_t(btext, false);
		_bstr_t text = L"Test";

		//SIZE size;
		//GetTextExtentPoint32(pC->m_hDC, (char*)text, text.length(), &size);

		Gdiplus::RectF size;
		pC->m_pGraphics->MeasureString(text, text.length(), m_computedFontFamily[0]->GetGdipFont(), Gdiplus::PointF(0,0), &size);

		maxx = max(maxx, size.Width);
	}

	maxx += 24;	// Make room for control borders

	if (lsize <= 1)
	{
		m_specifiedHeight = m_computedHeight = 18;
	}
	else
	{
		m_specifiedHeight = m_computedHeight = lsize*16;
	}

	m_specifiedWidth = m_computedWidth = maxx;
}

HRESULT __stdcall CSelectObjectBase::OnCurSelChange(long index)
{
	return S_OK;
}

void CHTMPSelect::CreateControls(CHTMContext* pC)
{
	ATLASSERT(0);
#if 0
	CComQIPtr<ILHTMLElement> element = m_pNode;

	if (pC->m_pUI)
	{
		CComQIPtr<IUIWnd> uiwnd;
		pC->m_pUI->QueryInterface(IID_IUIWnd, (void**)&uiwnd);

		if (!m_pControl)
		{
			if (TRUE)
			{
				m_pControl = new CSelectObject;
				m_pControl->m_pPElement = this;
				m_pControl->AddRef();
				m_pControl->m_hWnd = m_pFrame->m_pUI->m_hWnd;

				long lsize = GetAttributeSize();
				BOOL bMultiple = GetAttributeMultiple();

				if (lsize > 1 || bMultiple)
				{
					m_pControl->m_spUnknown.CoCreateInstance(CLSID_UIListControl);
				}
				else
				{
					m_pControl->m_spUnknown.CoCreateInstance(CLSID_UIComboBox);
				}

				m_pControl->Connect(FALSE, NULL);
				m_pControl->ActivateAx();

				//m_pControl->IDispEventImpl<1, CSelectObjectBase, &DIID__IUIComboBoxEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_pControl->m_combo);

				CComQIPtr<IUIListControl> list = m_pControl->m_spUnknown;
				CComQIPtr<IUIComboBox> combo = m_pControl->m_spUnknown;

				for (int i = 0; i < m_options.GetSize(); i++)
				{
					CComQIPtr<ILHTMLElement> pOption = m_options[i];//->m_pNode;

					BSTR btext;
					pOption->get_innerText(&btext);
					_bstr_t text = _bstr_t(btext, false);

					long index;
					if (list)
						list->AddString(text, &index);
					else
						combo->AddString(text, &index);
				}
			}
		}
	}
#endif
}

void CHTMPSelect::PlaceControls(HWND hWndParent, CHTMContext* /*pC*/)
{
//	ATLASSERT(0);
#if 0
	if (m_pControl)
	{
		CRect rcPos = m_pBox->GetAbsInnerRect();
		CRect rcClip = rcPos;

		GetVisibleRect(rcPos, rcClip);

		rcPos.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);
		rcClip.OffsetRect(m_pFrame->m_client.left, m_pFrame->m_client.top);

		m_pControl->OnSize(rcPos, rcClip);
	}
#endif
}

#endif
