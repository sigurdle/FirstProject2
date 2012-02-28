// ElementAttrsDlg.cpp : Implementation of CElementAttrsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ElementAttrsDlg.h"

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

#include "EXMLDocument.h"

#if 0
// Just saving this
#if 0

					HRESULT hr;
					CComQIPtr<IDispatch> pDisp;
					
					// get the dispatch interface to the engine and call the procedure named "Main"
					hr = pas->GetScriptDispatch(0, &pDisp);
					LPOLESTR szMain = OLESTR("SetElement");
					DISPID dispid;
					hr = pDisp->GetIDsOfNames(IID_NULL, &szMain, 1, LOCALE_SYSTEM_DEFAULT/*9*/, &dispid);
					
					DISPPARAMS dispparams;
					VARIANTARG varargs[1];
					dispparams.cArgs = 1;
					dispparams.cNamedArgs = 0;
					dispparams.rgvarg = varargs;

					CComQIPtr<IDispatch> iel = m_pElement->m_domElement;
					
					dispparams.rgvarg[0].vt = VT_DISPATCH;
					dispparams.rgvarg[0].pdispVal = iel;
					
					hr = pDisp->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD,
						&dispparams, 0, 0, 0);
#endif

/////////////////////////////////////////////////////////////////////////////
// CElementAttrsDlg

static int m_itemHeight = 16;
static int m_indentX = 14;

#include "EElement.h"

CElementAttrsDlg::CElementAttrsDlg()
{
	m_app = NULL;
	m_edit = NULL;
	m_font = NULL;
	m_pElement = NULL;

	m_splitx = 400;
}

CElementAttrsDlg::~CElementAttrsDlg()
{
}

void __stdcall CElementAttrsDlg::OnViewGroupSelectionChanged()
{
	ATLASSERT(0);
#if 0
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	m_attributes.RemoveAll();

	if (selectedElement)
	{
		IEElement* eElement = selectedElement->get_eElement();

		LXML::Element* element = eElement->get_domElement();

		CComQIPtr<ILElementEditAS> elementAS = element;
		if (elementAS)
		{
			CComQIPtr<IASNamedObjectMap> attlist;
			elementAS->getAttributeList(&attlist);

			if (attlist)
			{
				long length;
				attlist->get_length(&length);

				for (unsigned long i = 0; i < length; i++)
				{
					CComQIPtr<IASAttributeDeclaration> attdecl;
					attlist->item(i, (IASObject**)&attdecl);

					BSTR name;
					attdecl->get_nodeName(&name);

					CAttrItem* pItem = new CAttrItem;
					pItem->m_name = _bstr_t(name, false);
					pItem->m_attdecl = attdecl;

				//	pItem->m_pAttr = m_pElement->m_domElement->getAttributeNode(pTagAttr->m_attrName);
					m_attributes.Add(pItem);
				}
			}
		}
	}

	OnSize();
	InvalidateRect(NULL, TRUE);
#endif
}

STDMETHODIMP CElementAttrsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;

	if (viewGroup)
	{
		EndEdit();

		m_viewGroup = viewGroup;

		IDispEventImpl<4, CElementAttrsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);
		/*
		if (m_pElement)
		{
		// Don't listen to this document events anymore
			CComQIPtr<IEXMLDocument> webDocument;
			m_pElement->m_pDocument->QueryInterface(IID_IEXMLDocument, (void**)&webDocument);
			IDispEventImpl<2, CElementAttrsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(webDocument);
		}
		*/

		OnViewGroupSelectionChanged();
	
		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CElementAttrsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	IDispEventImpl<4, CElementAttrsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();

	EndEdit();

	m_attributes.RemoveAll();

	OnSize();
	InvalidateRect(NULL, TRUE);

#if 0
	CComQIPtr<IEElement> element = object;

	if (element)
	{
		if (element == m_pElement)
		{
			EndEdit();

			m_attributes.RemoveAll();

		// Don't listen to this document events anymore
			CComQIPtr<IEXMLDocument> webDocument = m_pElement->m_pDocument;
			IDispEventImpl<2, CElementAttrsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(webDocument);

			m_pElement = NULL;

			OnSize();
			InvalidateRect(NULL, TRUE);
		}
	}
#endif

	return S_OK;
}

HRESULT __stdcall CElementAttrsDlg::OnDOMEvent(ILDOMEvent* evt)
{
	if (m_pElement)
	{
		HWND hwnd;
		get_hwnd(&hwnd);

		if (hwnd)
		{
			InvalidateRect(&m_areaRect, TRUE);
		}
	}

	return S_OK;
}

void __stdcall CElementAttrsDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	if (m_edit)
	{
		CRect wrect;
		::GetWindowRect(m_edit, &wrect);
		ScreenToClient((LPPOINT)&wrect.left);
		ScreenToClient((LPPOINT)&wrect.right);
		::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
	}

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);

	HWND hwnd;
	get_hwnd(&hwnd);

	::ScrollWindow(hwnd, 0, oldPos-pos, &rect, &rect);
}

void CElementAttrsDlg::EndEdit()
{
	if (m_edit)
	{
		ATLASSERT(m_pActiveItem);

		CComQIPtr<ILDOMElement> element = m_pElement->m_domElement;

		char text[1024];
		::GetWindowText(m_edit, text, sizeof(text));

		CAttrItem* pItem = (CAttrItem*)m_pActiveItem;

		BSTR bvalue;
		element->getAttribute(pItem->m_name, &bvalue);
		_bstr_t value = _bstr_t(bvalue, false);

		if (value.length() == 0) value = L"";

		if (wcscmp(value, _bstr_t(text)) != 0)
		{
			if (lstrlen(text) > 0)
				element->setAttribute(pItem->m_name, _bstr_t(text));
			else
				element->removeAttribute(pItem->m_name);
		}

		/*
		//	pItem->m_pAttr = m_pElement->m_domElement->getAttributeNode(pItem->m_pTagAttr->m_attrName);
		}
		else if (m_pActiveItem->m_type == 3)	// CSS
		{
			CCSSItem* pItem = (CCSSItem*)m_pActiveItem;

			CComQIPtr<ISVGStylable> stylable = m_pElement->m_domElement;
			CComQIPtr<IMMSXHTMLElement> htmlelement = m_pElement->m_domElement;

			CComQIPtr<IDOMCSSStyleDeclaration> style;

			if (stylable)
				stylable->get_style(&style);
			else if (htmlelement)
				htmlelement->get_style(&style);

			BSTR boldtext;
			style->getPropertyValue(pItem->m_pTagAttr->m_attrName, &boldtext);
			_bstr_t oldtext = _bstr_t(boldtext, false);
			if (oldtext.length() == 0) oldtext = L"";

			if (wcscmp(oldtext, _bstr_t(text)))
			{
				if (lstrlen(text) > 0)
				{
					style->setProperty(pItem->m_pTagAttr->m_attrName, _bstr_t(text), L"");
				}
				else
				{
					style->removeProperty(pItem->m_pTagAttr->m_attrName, NULL);
				}
			}
		}
		*/

		::DestroyWindow(m_edit);
		m_edit = NULL;
	}
}

#if 0
void CElementAttrsDlg::EndEdit()
{
	if (m_edit)
	{
		ATLASSERT(m_pActiveItem);

		char text[1024];
		GetWindowText(m_edit, text, sizeof(text));

		if (m_pActiveItem->m_type == 2)	// XML
		{
			CAttrItem* pItem = (CAttrItem*)m_pActiveItem;

			_bstr_t value = m_pElement->m_domElement->getAttribute(pItem->m_pTagAttr->m_attrName);
			if (value.length() == 0) value = L"";

			if (wcscmp(value, _bstr_t(text)) != 0)
			{
				if (lstrlen(text) > 0)
					m_pElement->m_domElement->setAttribute(pItem->m_pTagAttr->m_attrName, text);
				else
					m_pElement->m_domElement->removeAttribute(pItem->m_pTagAttr->m_attrName);
			}

		//	pItem->m_pAttr = m_pElement->m_domElement->getAttributeNode(pItem->m_pTagAttr->m_attrName);
		}
		else if (m_pActiveItem->m_type == 3)	// CSS
		{
			CCSSItem* pItem = (CCSSItem*)m_pActiveItem;

			SVGLib::ISVGStylablePtr stylable = m_pElement->m_domElement;

			_bstr_t oldtext = stylable->style->getPropertyValue(pItem->m_pTagAttr->m_attrName);
			if (oldtext.length() == 0) oldtext = L"";

			if (wcscmp(oldtext, _bstr_t(text)))
			{
				if (lstrlen(text) > 0)
				{
					stylable->style->setProperty(pItem->m_pTagAttr->m_attrName, text, L"");
				}
				else
				{
					stylable->style->removeProperty(pItem->m_pTagAttr->m_attrName);
				}
			}
		}

		::DestroyWindow(m_edit);
		m_edit = NULL;
	}
}

void CElementAttrsDlg::handleEvent(SVGLib::IDOMEvent* evt)
{
	if (m_pElement)
	{
		if (GetHwnd())
		{
			InvalidateRect(&m_areaRect);
		}
	}
}
#endif

LRESULT CElementAttrsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	HWND hwnd;
	get_hwnd(&hwnd);

	long scrollposY; m_vert->get_pos(&scrollposY);

	EndEdit();

	int index = (point.y+scrollposY) / m_itemHeight;
	if (index >= 0 && index < m_attributes.GetSize())
	{
		CAttrItem* pItem = m_attributes[index];

		/*
		int i = 0;
		C2Obj* pParentItem = m_attrTree;
		UPOSITION pos = pParentItem->GetHeadPosition();
		int nextlevel = 0;
		while (pos)
		{
			int level = nextlevel;
			CAttrItem* pItem2 = (CAttrItem*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			if (i == index)
			{
				pItem = pItem2;
				break;
			}

			i++;
		}
		*/

		if (m_pActiveItem != pItem)
		{
			m_pActiveItem = pItem;
			InvalidateRect(NULL, TRUE);
		}

#if 0
		if (m_pElement)
		{
			if (m_pActiveItem)
				m_pElement->m_pDocument->m_pActiveAttr = m_pActiveItem->m_pTagAttr;
			else
				m_pElement->m_pDocument->m_pActiveAttr = NULL;
		}
#endif

		CRect client;
		GetClientRect(&client);

	//	if (pItem && (pItem->m_type > 1))
		{
			if (point.x > m_splitx)
			{
#if 0
				switch (pItem->m_pTagAttr->m_attrType)
				{
				case ATYP_NUMBER:
				case ATYP_TEXT:
				case ATYP_URL:
#endif
					{
						int top = index*m_itemHeight;
						int left = m_splitx+1;
			
						BSTR benumAttr;
						pItem->m_attdecl->get_enumAttr(&benumAttr);
						_bstr_t enumAttr = _bstr_t(benumAttr, false);
						if (enumAttr.length())
						{
							m_edit = CreateWindowEx(0, "combobox", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | CBS_SORT | CBS_AUTOHSCROLL | CBS_DROPDOWN,
								left, top - scrollposY, m_areaRect.right - left, m_itemHeight-1+80, hwnd, (HMENU)1, _Module.m_hInst, NULL);

							BSTR p = (BSTR)enumAttr;
							TCHAR v[256];
							int n = 0;

							while (*p)
							{
								if (*p == L'|')
								{
									if (n > 0)
									{
										::SendMessage(m_edit, CB_ADDSTRING, 0, (LPARAM)v);
										n = 0;
									}
									p++;
								}

								while (iswspace(*p)) p++;
								if (*p == 0) break;

								v[n++] = *p++;
								v[n] = 0;	// null-terminate
							}

							if (n > 0) ::SendMessage(m_edit, CB_ADDSTRING, 0, (LPARAM)v);
						}
						else
						{
							m_edit = CreateWindowEx(0, "edit", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
								left, top - scrollposY, m_areaRect.right - left, m_itemHeight-1, hwnd, (HMENU)1, _Module.m_hInst, NULL);
						}

						SendMessage(m_edit, WM_SETFONT, (WPARAM)(HFONT)m_font, 0);

						CComQIPtr<ILDOMElement> element = m_pElement->m_domElement;

					//	if (pItem->m_type == 2)	// XML
						{
							//CAttrItem* pAttrItem = (CAttrItem*)pItem;

							BSTR bvalue;
							element->getAttribute(pItem->m_name, &bvalue);
							_bstr_t value = _bstr_t(bvalue, false);

							if (value.length() > 0) ::SetWindowText(m_edit, value);
						//	if (pAttrItem->m_pAttr) SetWindowText(m_edit, pAttrItem->m_pAttr->value);
						}
#if 0
						else if (pItem->m_type == 3)	// CSS
						{
							CCSSItem* pCSSItem = (CCSSItem*)pItem;

							CComQIPtr<ISVGStylable> stylable = element;
							CComQIPtr<IMMSXHTMLElement> htmlelement = element;

							CComQIPtr<IDOMCSSStyleDeclaration> style;

							if (stylable)
								stylable->get_style(&style);
							else if (htmlelement)
								htmlelement->get_style(&style);

							if (style)
							{
								BSTR btext;
								style->getPropertyValue(pCSSItem->m_pTagAttr->m_attrName, &btext);
								_bstr_t text = _bstr_t(btext, false);

								if ((BSTR)text != NULL) ::SetWindowText(m_edit, text);
							}
						}
#endif

						::SendMessage(m_edit, EM_SETSEL, 0, -1);
						::SetFocus(m_edit);
					}
#if 0
					break;
					
				case ATYP_COLOR:
					{
	/*					CHTMLColorDlg	dlg;
						
						COLORREF ref;
						if (pItem->m_pAttr)
							ref = ConvertColor(pItem->m_pAttr->m_value);
						else
							ref = 0;
						
						dlg.m_red = GetRValue(ref);
						dlg.m_green = GetGValue(ref);
						dlg.m_blue = GetBValue(ref);
						
						if (dlg.DoModal() == IDOK)
						{
							int red = dlg.m_red;
							int green = dlg.m_green;
							int blue = dlg.m_blue;
							
							char text[64];
							sprintf(text, "#%2.2x%2.2x%2.2x", red, green, blue);
							
							m_pElement->SetAttrValue(pItem->m_pTagAttr->m_attrName, text);
							
							if (m_pDocument)
							{
								m_pDocument->UpdateAllViews();
							}
						}
					*/
					}
					break;
				}
#endif
			}
		}
	}
#endif

	return 0;
}

void CElementAttrsDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);
	int cx = client.right;
	int cy = client.bottom;

	//if (m_attrTree)
	{
		int height = m_attributes.GetSize()*m_itemHeight;

		/*
		C2Obj* pParentItem = m_attrTree;
		UPOSITION pos = pParentItem->GetHeadPosition();
		int nextlevel = 0;

		while (pos)
		{
			int level = nextlevel;
			CAttrItem* pItem = (CAttrItem*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			height += m_itemHeight;
		}
		*/

//		int count = m_attrTree->m_childList.GetCount();

		m_areaRect.left = 0;
		m_areaRect.top = 0;
		m_areaRect.bottom = client.bottom;

		if (client.bottom > height)
		{
			m_areaRect.right = client.right;
			m_axvert.ShowWindow(SW_HIDE);

			m_vert->put_pos(0);
		}
		else
		{
			m_areaRect.right = client.right-16;

			m_axvert.ShowWindow(SW_SHOW);
			m_axvert.MoveWindow(m_areaRect.right, 0, 16, client.bottom, TRUE);

			m_vert->SetInfo(0, height, client.bottom);
		}
	}
/*
	else
	{
//		m_vert->ShowWindow(SW_HIDE, NULL);
	}
	*/
}

long CElementAttrsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndEdit();
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

#if 0
void CElementAttrsDlg::SetElement(CElement* pElement)
{
	if (pElement != m_pElement)
	{
		EndEdit();

		if (m_attrTree)
		{
			delete m_attrTree;
			m_attrTree = NULL;
		}

		m_pElement = pElement;

		if (m_pElement)
		{
			CTag* pTag = NULL;
			for (int i = 0; i < gApp->m_tagArray.GetSize(); i++)
			{
				if (!strcmp(gApp->m_tagArray[i]->m_tagName, m_pElement->m_domElement->tagName))
				{
					pTag = gApp->m_tagArray[i];
					break;
				}
			}
			
			if (pTag)
			{
				m_attrTree = new CAttrItem;

				for (int i = 0; i < pTag->m_attrList.GetSize(); i++)
				{
					CTagAttr* pTagAttr = pTag->m_attrList[i];

					CAttrItem* pItem = new CAttrItem;
					pItem->m_pTagAttr = pTagAttr;

				//	pItem->m_pAttr = m_pElement->m_domElement->getAttributeNode(pTagAttr->m_attrName);
					m_attrTree->AddChildTail(pItem);
				}

				if (pTag->m_cssList.GetSize() > 0)
				{
					CAttrGroup* pStyleGroup = new CAttrGroup;
					pStyleGroup->m_name = "style";
					pStyleGroup->m_expanded = TRUE;

					for (int i = 0; i < pTag->m_cssList.GetSize(); i++)
					{
						CTagCSS* pTagAttr = pTag->m_cssList[i];

						CCSSItem* pItem = new CCSSItem;
						pItem->m_pTagAttr = pTagAttr;
						ATLASSERT(pItem->m_pTagAttr);

						pStyleGroup->AddChildTail(pItem);
					}

					m_attrTree->AddChildTail(pStyleGroup);
				}
			}
			else
			{
			/*
			m_attrTree = new CHTMAttrItem;
			
			  POSITION pos = m_pElement->m_attrList.GetHeadPosition();
			  while (pos)
			  {
			  CElementAttribute* pAttr = (CElementAttribute*)m_pElement->m_attrList.GetNext(pos);
			  CHTMAttrItem* pItem = new CHTMAttrItem;
			  pItem->m_pAttr = pAttr;
			  m_attrTree->AddChildTail(pItem);
			  }
				*/
			}
		}
		
		OnSize();
		InvalidateRect(NULL, TRUE);
	}
}

#endif

long CElementAttrsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	m_vert->CreateControl(thiswnd, 0, 0, SBS_VERT | WS_VISIBLE, 0, 0, 0, 0, NULL);

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<3, CElementAttrsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	m_font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->AddEventHandler(this);

	return 0;
}

long CElementAttrsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->RemoveEventHandler(this);

	IDispEventImpl<3, CElementAttrsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	if (m_font)
	{
		DeleteObject(m_font);
		m_font = NULL;
	}

	if (m_pElement)
	{
	// Don't listen to this document events anymore
		CComQIPtr<IEXMLDocument> webDocument = m_pElement->m_pDocument;
		IDispEventImpl<2, CElementAttrsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(webDocument);
	}

	return 0;
}

long CElementAttrsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	HFONT hOldFont = (HFONT)dc.SelectFont(m_font);

	CRect client;
	GetClientRect(&client);

	dc.SetBkMode(TRANSPARENT);

	dc.IntersectClipRect(m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);

	long scrollposY; m_vert->get_pos(&scrollposY);

	//if (m_attrTree)
	{
	//	CComQIPtr<ISVGStylable> stylable = m_pElement->m_domElement;
	//	CComQIPtr<IMMSXHTMLElement> htmlelement = m_pElement->m_domElement;

		dc.SetViewportOrg(0, -scrollposY, NULL);

		int y = 0;

		for (int i = 0; i < m_attributes.GetSize(); i++)
		{
			int level = 0;//nextlevel;
			CAttrItem* pItem = m_attributes[i];//(CAttrTypeItem*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			int x = 1+level*m_indentX;

			CRect rect(x, y, m_splitx, y+m_itemHeight-1);

			CRect icrect = rect;
			icrect.right = icrect.left+16;
			CRect nrect = rect;
			nrect.left += 16;
			CRect vrect(m_splitx, y, client.right, y+m_itemHeight-1);

			if (pItem == m_pActiveItem)
			{
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
				dc.FillSolidRect(&rect, GetSysColor(COLOR_HIGHLIGHT));
			}
			else
			{
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				dc.FillSolidRect(&rect, RGB(240, 240, 240));
			}

			/*
			if (pItem->m_type == 1)	// Group
			{
				_bstr_t text = pItem->m_name;
				DrawText(hDC, text, text.length(), &rect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
			}
			else
			*/
			{
				dc.SetTextColor(RGB(200, 0, 0));
				dc.DrawText("=", 1, &icrect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

				_bstr_t text = pItem->m_name;
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				dc.DrawText(text, text.length(), &nrect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

//				dc.FillSolidRect(&vrect, RGB(255, 255, 255));

#if 0
			//	if (pItem->m_type == 2)	// XML
				{
					CComQIPtr<ILDOMElement> element = m_pElement->m_domElement;

					BSTR bvalue;
					element->getAttribute(pItem->m_name, &bvalue);
					_bstr_t value = _bstr_t(bvalue, false);
					if (value.length() > 0)	// Existing value
					{
					//	_bstr_t text = pAttrItem->m_pAttr->value;
						dc.DrawText(value, value.length(), &vrect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
					}
					else
					{
					// TODO, write default value
					}
				}
#endif
			}

			y += m_itemHeight;

			dc.MoveTo(0, y-1);
			dc.LineTo(client.right, y-1);
		}

		dc.MoveTo(m_splitx, 0);
		dc.LineTo(m_splitx, y);
	}

	dc.SelectFont(hOldFont);

	return 0;
}

#if 0
void CElementAttrsDlg::OnScroll(UINT nSBCode, UINT nPos, CIUIScrollBar* pScrollBar)
{
	CRect client;
	GetClientRect(&client);

	if (pScrollBar->TOP() == m_vert->TOP())
	{
		SCROLLINFO	sif = {0};
		sif.cbSize = sizeof(sif);
		pScrollBar->GetScrollInfo(&sif, SIF_PAGE|SIF_RANGE);
		
		int minr = sif.nMin;
		int page = sif.nPage;
		int maxr = pScrollBar->GetScrollLimit();//sif.nMax;
		int oldPos = pScrollBar->GetScrollPos();
		int pos;
		
		switch (nSBCode)
		{
		case SB_LINEUP:			pos = oldPos-m_itemHeight;	break;
		case SB_LINEDOWN:			pos = oldPos+m_itemHeight;	break;
		case SB_PAGEUP:			pos = oldPos-page;	break;
		case SB_PAGEDOWN:			pos = oldPos+page;	break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:	pos = nPos; break;
		}
		
		if (nSBCode != SB_ENDSCROLL)
		{
			if (pos < minr) pos = minr;
			else if (pos > maxr) pos = maxr;

			if (m_edit)
			{
				CRect wrect;
				GetWindowRect(m_edit, &wrect);
				ScreenToClient(&wrect);
				::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
			}

			CRect	rect = m_areaRect;
			
			pScrollBar->SetScrollPos(pos, (nSBCode != SB_THUMBTRACK));
			ScrollWindow(GetHwnd(), 0, oldPos-pos, &rect, &rect);
		}
	}
}
#endif

#endif