// SMILLayoutsDlg.cpp : Implementation of CSMILLayoutsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "SMILLayoutsDlg.h"

//LXMLEXT ILDOMElement* GetElementByTagName(ILDOMNode* parentNode, BSTR tagName, BOOL bDeep = TRUE);
//LXMLEXT ILDOMElement* GetElementByTagNameNS(ILDOMNode* parentNode, BSTR ns, BSTR tagName, BOOL bDeep = TRUE);

#if 0

/////////////////////////////////////////////////////////////////////////////
// CSMILLayoutsDlg

int CSMILLayoutsDlg::FinalConstruct()
{
	HRESULT hr;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->FindMenu(IDR_SMILLAYOUTSDLG, &m_menu);

	return 0;
}

LRESULT CSMILLayoutsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	m_horz->CreateControl(thiswnd, 0, 0, SBS_HORZ | WS_VISIBLE, 0, 0, 0, 0, NULL);
//	m_vert->CreateControl(thiswnd, 0, 0, SBS_VERT | WS_VISIBLE, 0, 0, 0, 0, NULL);
/*
	m_expandedBitmap = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_EXPANDED));

	m_hFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
*/
	/*
	if (m_document)
	{
		IDispEventImpl<3, CWETimelineUI, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);
	}
	*/

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CSMILLayoutsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	/*
	if (m_document)
	{
		IDispEventImpl<3, CWETimelineUI, &DIID__IWebXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
	}
	*/

	return 0;
}

void CSMILLayoutsDlg::BuildItems()
{
	m_layouts.RemoveAll();

	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		CComPtr<ILDOMDocument> domdocument;
		edocument->get_DOMDocument(&domdocument);

		CComQIPtr<ILSMILDocument> smildocument = domdocument;
		if (smildocument)
		{
			CComPtr<ILDOMElement> documentElement;
			smildocument->get_documentElement(&documentElement);

			if (documentElement)
			{
				CComPtr<ILDOMElement> head = GetElementByTagName(documentElement, L"head", FALSE);
				if (head)
				{
					CComPtr<ILDOMElement> layout = GetElementByTagName(head, L"layout", FALSE);
					if (layout)
					{
						CComPtr<ILDOMNode> child;
						layout->get_firstChild(&child);
						while (child)
						{
							CComQIPtr<ILDOMElement> element = child;
							if (element)
							{
								CComBSTR tagName;
								element->get_tagName(&tagName);

								if (!wcscmp(tagName, L"root-layout"))
								{
									m_layouts.Add(element);
								}
								else if (!wcscmp(tagName, L"topLayout"))
								{
									m_layouts.Add(element);
								}
							}

							CComPtr<ILDOMNode> nextSibling;
							child->get_nextSibling(&nextSibling);
							child = nextSibling;
						}
					}
				}
			}
		}
	}
}

LRESULT CSMILLayoutsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_viewGroup)
	{
		int y = 0;
		int x = 0;

		for (int i = 0; i < m_layouts.GetSize(); i++)
		{
			CComBSTR tagName;
			m_layouts[i]->get_tagName(&tagName);

			dc.TextOut(x, y, _bstr_t(tagName), tagName.Length());

			y += 18;
		}
	}

	return 0;
}

LRESULT CSMILLayoutsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_viewGroup)
	{
		int index = point.y/18;

		if (index >= 0 && index < m_layouts.GetSize())
		{
			CComPtr<IEXMLDocument> edocument;
			m_viewGroup->get_eXMLDocument(&edocument);

			CComPtr<IEElement> eelement;
			edocument->GetEElementFromDOMElement(m_layouts[index], &eelement);

			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->ActivateElement(eelement, 0, &selectedElement);
		}
	}

	return 0;
}

HRESULT __stdcall CSMILLayoutsDlg::OnDOMEvent(ILDOMEvent* evt)
{
	BuildItems();
	//OnSize();
	InvalidateRect(NULL, TRUE);
	return S_OK;
}

STDMETHODIMP CSMILLayoutsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		if (m_viewGroup != NULL)
		{
			CComPtr<IEXMLDocument> document = m_viewGroup->get_eXMLDocument();

			IDispEventImpl<3, CSMILLayoutsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
		}

		m_viewGroup = viewGroup;

		CComPtr<IEXMLDocument> document;
		m_viewGroup->get_eXMLDocument(&document);

		IDispEventImpl<3, CSMILLayoutsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);

		*cookie = 1;

		BuildItems();

		if (m_hWnd)
		{
//			OnSize();
			Invalidate();
		}
	}

	return S_OK;
}

STDMETHODIMP CSMILLayoutsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	if (IsUnknownEqualUnknown(object, m_viewGroup))
	{
		if (m_viewGroup != NULL)
		{
			CComPtr<IEXMLDocument> document;
			m_viewGroup->get_eXMLDocument(&document);

			IDispEventImpl<3, CSMILLayoutsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
		}

		BuildItems();

		if (m_hWnd)
		{
//			OnSize();
			Invalidate();
		}
	}

	return S_OK;
}

BEGIN_CMD_MAP(CSMILLayoutsDlg)
END_CMD_MAP()

#if 0
// ICommandTarget
STDMETHODIMP CSMILLayoutsDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	CComQIPtr<ICommandTarget> target;
	
// Try viewgroup first
	target = m_viewGroup;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

// Then try us
//	return ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
}
#endif

#endif