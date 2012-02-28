// XMLGridView.cpp : Implementation of CXMLGridView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XMLGridView.h"

#include "EXMLDocument.h"	// TODO remove?
#include "EXMLViewGroup.h"
#include "LXMLEditorApp.h"	// TODO remove?

#if 0
/////////////////////////////////////////////////////////////////////////////
// CXMLGridView

STDMETHODIMP CXMLGridView::get_document(IEXMLDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_viewGroup->m_pDocument;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

LRESULT CXMLGridView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComPtr<ILXMLEditorApp> application;
	m_viewGroup->m_pDocument->get_Application(&application);

	IDispEventImpl<4, CXMLGridView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(application);

	CRect rc(0,0,0,0);
	IUnknown* p;
	m_axXmlGrid.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axXmlGrid.AttachControl(m_XmlGrid, &p);
	IDispEventImpl<1, CXMLGridView, &DIID__IXMLGridCtlEvents, &LIBID_XMLEDITCTLSLib, 1, 0>::DispEventAdvise(m_XmlGrid);

	CComQIPtr<ILDOMDocument> domdocument;
	m_viewGroup->m_pDocument->get_DOMDocument(&domdocument);

	m_XmlGrid->put_xmlDocument(domdocument);

	OnPrefsChange();

	return 0;
}

LRESULT CXMLGridView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComPtr<ILXMLEditorApp> application;
	m_viewGroup->m_pDocument->get_Application(&application);

	IDispEventImpl<1, CXMLGridView, &DIID__IXMLGridCtlEvents, &LIBID_XMLEDITCTLSLib, 1, 0>::DispEventUnadvise(m_XmlGrid);

	IDispEventImpl<4, CXMLGridView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(application);

	return 0;
}

LRESULT CXMLGridView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();

	return 0;
}

void CXMLGridView::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_axXmlGrid.MoveWindow(0, 0, client.right, client.bottom, TRUE);
}

void __stdcall CXMLGridView::OnSelectNode(IUnknown* node)
{
	CComQIPtr<ILDOMElement> element = node;
	if (element)
	{
// TODO
//		ATLASSERT(0);
#if 0
		((CESvgDocument*)m_document.p)->SetTargetElement(((CESvgDocument*)m_document.p)->m_pTree->FindDOMElement(element), 0);
#endif
	}
}

STDMETHODIMP CXMLGridView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	if (bActivate)
	{
		//uiManager->ActivateObject(NULL, m_document);
		//uiManager->ActivateObject(m_document, m_viewGroup);
		uiManager->ActivateObject(m_viewGroup, GetUnknown());
	}
	else
	{
		uiManager->DeactivateObject(GetUnknown());
		//uiManager->DeactivateObject(m_viewGroup);
		//uiManager->DeactivateObject(m_document);
	}
#endif
	return S_OK;
}

void __stdcall CXMLGridView::OnPrefsChange()
{
	CFormatWindow* pWindow = static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->RegisterFormatWindow(L"XML Grid");
	ATLASSERT(pWindow);

	{
		HDC hDC = ::GetDC(NULL);

		_bstr_t faceName = pWindow->m_lf.lfFaceName;
		FONTDESC	fd;
		fd.cbSizeofstruct = sizeof(fd);
		fd.lpstrName = faceName;////*/L"Courier";
		fd.cySize.int64 = -10000*MulDiv(pWindow->m_lf.lfHeight, 72, GetDeviceCaps(hDC, LOGPIXELSY));
		fd.sWeight = 0;
		fd.sCharset = 0;
		fd.fItalic = FALSE;
		fd.fUnderline = FALSE;
		fd.fStrikethrough = FALSE;

		::ReleaseDC(NULL, hDC);

		CComPtr<IFontDisp> font;
		HRESULT hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&font);
		m_XmlGrid->put_Font(font);
	}

	/*
	{
		COLORREF fgColor, bgColor;

		pWindow->GetFormatColorValues(L"Text Selection", &fgColor, &bgColor);
		m_edit->SetStyle(-1, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Text", &fgColor, &bgColor);
		m_edit->SetStyle(0, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Element Name", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_ELEMENT_NAME, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Attribute Name", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_ATTRIBUTE_NAME, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Attribute Value", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_ATTRIBUTE_VALUE, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Tag Delimiter", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_TAG_DELIMITER, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Comment", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_COMMENT, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"XML Operator", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_XML_OPERATOR, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script Keyword", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_KEYWORD, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script String", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_STRING, fgColor, bgColor);

		pWindow->GetFormatColorValues(L"Script Comment", &fgColor, &bgColor);
		m_edit->SetStyle(COLOR_JSCRIPT_COMMENT, fgColor, bgColor);
	}
	*/
}

#if 0
// ICommandTarget
STDMETHODIMP CXMLGridView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;

// Try viewgroup
	target = m_viewGroup;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CXMLGridView)
// Edit
	CMD_HANDLER(ID_EDIT_COPY, OnEditCopy)
	CMD_HANDLER(ID_EDIT_PASTE, OnEditPaste)
	CMD_UPDATE(ID_EDIT_PASTE, OnEditPasteUpdate)
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditClear)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditClearUpdate)

// XML

	CMD_HANDLER(ID_XML_INSERT_ELEMENT, OnInsertElement)
	CMD_HANDLER(ID_XML_INSERT_ATTRIBUTE, OnInsertAttribute)
	CMD_HANDLER(ID_XML_INSERT_TEXT, OnInsertText)
	CMD_HANDLER(ID_XML_INSERT_CDATA, OnInsertCData)
	CMD_HANDLER(ID_XML_INSERT_COMMENT, OnInsertComment)
	CMD_HANDLER(ID_XML_INSERT_PROCESSINGINSTRUCTION, OnInsertProcessingInstruction)
	CMD_HANDLER(ID_XML_INSERT_DTDELEMENT, OnInsertDTDElement)

	CMD_HANDLER(ID_XML_TABLE_DISPLAYASTABLE, OnTableDisplayastable)
	CMD_UPDATE(ID_XML_TABLE_DISPLAYASTABLE, OnTableDisplayastableUpdate)
END_CMD_MAP()

LRESULT CXMLGridView::OnInsertElement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> document;
	m_viewGroup->m_pDocument->get_DOMDocument(&document);

	CComPtr<IXMLGridNode> activeParent;
	m_XmlGrid->get_ActiveParentNode(&activeParent);

	if (activeParent)
	{
		CComPtr<ILDOMNode> parentNode;
		activeParent->get_node((IUnknown**)&parentNode);

		CComPtr<IXMLGridNode> active;
		m_XmlGrid->get_ActiveNode(&active);

		if (active)
		{
			CComPtr<ILDOMNode> beforeNode;
			active->get_node((IUnknown**)&beforeNode);

			CComPtr<ILDOMElement> element;
			document->createElement(L"element", &element);

			if (element)
			{
				parentNode->insertBefore(element, _variant_t(beforeNode), NULL);

				CComPtr<IXMLGridNode> gridNode;
				m_XmlGrid->GetXMLNodeFromDOMNode(element, &gridNode);
				if (gridNode)
				{
					m_XmlGrid->SelectItem(gridNode);
				}
			}
		}
	}

	return 0;
}

LRESULT CXMLGridView::OnInsertAttribute(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> document;
	m_viewGroup->m_pDocument->get_DOMDocument(&document);

	CComPtr<IXMLGridNode> activeParent;
	m_XmlGrid->get_ActiveParentNode(&activeParent);

	if (activeParent)
	{
		CComPtr<ILDOMNode> parentNode;
		activeParent->get_node((IUnknown**)&parentNode);

		CComPtr<ILDOMNamedNodeMap> attributes;
		parentNode->get_attributes(&attributes);

		CComPtr<ILDOMAttr> attr;
		// Find unique attribute name
		int n = 0;
		do
		{
			WCHAR attrName[64];
			swprintf(attrName, L"attribute%d", n);

			attributes->getNamedItem(attrName, (ILDOMNode**)&attr);
			if (attr == NULL)
			{
				document->createAttribute(attrName, &attr);
				break;
			}
			attr.Release();

			n++;
		}
		while (1);

		if (attr)
		{
			CComPtr<ILDOMNode> p;
			attributes->setNamedItemNS(attr, &p);

			CComPtr<IXMLGridNode> gridNode;
			m_XmlGrid->GetXMLNodeFromDOMNode(attr, &gridNode);
			if (gridNode)
			{
				m_XmlGrid->SelectItem(gridNode);
			}
		}
	}

	return 0;
}

LRESULT CXMLGridView::OnInsertText(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CXMLGridView::OnInsertCData(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CXMLGridView::OnInsertComment(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CXMLGridView::OnInsertProcessingInstruction(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> document;
	m_viewGroup->m_pDocument->get_DOMDocument(&document);

	CComPtr<IXMLGridNode> activeParent;
	m_XmlGrid->get_ActiveParentNode(&activeParent);

	if (activeParent)
	{
		CComPtr<ILDOMNode> parentNode;
		activeParent->get_node((IUnknown**)&parentNode);

		CComPtr<IXMLGridNode> active;
		m_XmlGrid->get_ActiveNode(&active);

		if (active)
		{
			CComPtr<ILDOMNode> beforeNode;
			active->get_node((IUnknown**)&beforeNode);

			CComPtr<ILDOMProcessingInstruction> pi;
			document->createProcessingInstruction(L"target", NULL, &pi);

			if (pi)
			{
				parentNode->insertBefore(pi, _variant_t(beforeNode), NULL);
			}
		}
	}

	return 0;
}

LRESULT CXMLGridView::OnInsertDTDElement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> document;
	m_viewGroup->m_pDocument->get_DOMDocument(&document);

	CComPtr<ILDTDElement> dtdElement;
	document->createDTDElement(&dtdElement);

	document->appendChild(dtdElement, NULL);

	return 0;
}

LRESULT CXMLGridView::OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_XmlGrid->CopyXML();
	return 0;
}

LRESULT CXMLGridView::OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_XmlGrid->Paste();
	return 0;
}

void CXMLGridView::OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL bCanPaste;
	m_XmlGrid->CanPaste(&bCanPaste);

	pCmdUI->Enable(bCanPaste != VARIANT_FALSE);
}

LRESULT CXMLGridView::OnEditClear(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_XmlGrid->DeleteSelection();
	return 0;
}

void CXMLGridView::OnEditClearUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL bHasSelection;
	m_XmlGrid->HasSelection(&bHasSelection);

	pCmdUI->Enable(bHasSelection != VARIANT_FALSE);
}

LRESULT CXMLGridView::OnTableDisplayastable(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_XmlGrid->DisplayAsTable();
	return 0;
}

void CXMLGridView::OnTableDisplayastableUpdate(long iid, IUICmdUpdate* pCmdUI)
{
}

#endif