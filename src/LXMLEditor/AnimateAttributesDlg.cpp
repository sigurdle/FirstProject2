#include "stdafx.h"
#include "LXMLEditor2.h"
#include "AnimateAttributesDlg.h"

//#include "..\OleDataObject.h"

#include "CSSProperty.h"

#include "EXMLDocument.h"	// TODO remove
#include "EXMLViewGroup.h"	// TODO remove
#include "EXMLLayoutView.h"	// TODO remove
#include "SVGBehavior.h"	// TODO remove
#include "SmilTimeGraphView.h"// TODO remove

#if 0

/////////////////////////////////////////////////////////////////////////////
// CAnimateAttributesDlg

LRESULT CAnimateAttributesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CAnimateAttributesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	IDispEventImpl<2, CAnimateAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

	OnViewGroupSelectionChanged();

	return 0;
}

LRESULT CAnimateAttributesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	IDispEventImpl<2, CAnimateAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();
	m_targetElement.Release();

	IDispEventImpl<1, CAnimateAttributesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CAnimateAttributesDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	HFONT hOldFont = dc.SelectFont(hFont);

	dc.SetBkMode(TRANSPARENT);

	if (dc.IntersectClipRect(&m_areaRect) > NULLREGION)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		dc.SetViewportOrg(m_areaRect.left, m_areaRect.top-scrollposY*m_itemHeight);

		if (m_targetElement)
		{
			int y = 0;

			for (int i = 0; i < m_attributes.size(); i++)
			{
				WCHAR* attributeType = m_attributes[i].m_attributeType;
				WCHAR* attributeName = m_attributes[i].m_attributeName;

				CString str;
				if (attributeType)
					str.Format("%S:%S", attributeType, attributeName);
				else
					str.Format("%S", attributeName);

				dc.TextOut(0, y, str);

				y += m_itemHeight;
			}
		}
	}

	dc.SelectFont(hOldFont);

	return 0;
}

LRESULT CAnimateAttributesDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);
	point.x -= m_areaRect.left;
	point.y -= m_areaRect.top;
	point.y += scrollposY*m_itemHeight;

	if (m_targetElement)
	{
		int index = point.y / 18;

		if (index >= 0 && index < m_attributes.size())
		{
			m_index = index;

#if 0
			CComPtr<ILSMILXMLAttr> attr;
			m_targetElement->animatableXMLAttrItem(index, &attr);

			CComBSTR namespaceURI;
			attr->get_name(&namespaceURI);

			CComBSTR attributeName;
			attr->get_name(&attributeName);

			CComObject<COleDataObject>* pDataObject;
			CComObject<COleDataObject>::CreateInstance(&pDataObject);
			if (pDataObject)
			{
				pDataObject->AddRef();

				CMyDropSource*  pDropSource = new CMyDropSource;

				CComBSTR xmltext;

				xmltext = L"<animate attributeType=\"XML\" attributeName=\"";
				xmltext += attributeName;
				xmltext += L"\"/>";

				HGLOBAL hData = GlobalAlloc(GMEM_SHARE, (xmltext.Length()+1)*2);
				if (hData)
				{
					WCHAR* pData = (WCHAR*)GlobalLock(hData);
					if (pData)
					{
						CopyMemory(pData, (BSTR)xmltext, (xmltext.Length()+1)*2);

						GlobalUnlock(pData);

						STGMEDIUM stgm;
						stgm.tymed = TYMED_HGLOBAL;
						stgm.pUnkForRelease = NULL;
						stgm.hGlobal = hData;

						FORMATETC etc = { CF_UNICODETEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
						pDataObject->SetData(&etc, &stgm, FALSE/*TRUE*/ /*fRelese*/);

						DWORD dropEffect = 0;
						if (::DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY/* | DROPEFFECT_MOVE*/, &dropEffect) == DRAGDROP_S_DROP)
						{
						}
					}

					GlobalFree(hData);
				}

				pDataObject->Release();
			}
#endif
		}
	}

	return 0;
}

LRESULT CAnimateAttributesDlg::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);
	point.x -= m_areaRect.left;
	point.y -= m_areaRect.top;
	point.y += scrollposY*m_itemHeight;

	if (m_index >= 0 && m_index < m_attributes.size())
	{
		if ((static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_pActiveTimeGraphElement == NULL) ||
			(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_pActiveTimeGraphElement->m_parent) == NULL)
		{
			MessageBox("You must select where you want to place the animation in the TimeGraphView", "LXMLEditor", MB_OK);
			return 0;
		}

		ILDOMElement* targetElement = m_targetElement;

		CComBSTR targetElementId;

		if (targetElement != m_viewGroup->m_pActiveTimeGraphElement->m_parent->m_domElement)
		{
			m_viewGroup->m_pDocument->SetElementID(targetElement, &targetElementId);
			if (targetElementId.Length() == 0)
			{
				return 0;
			}
		}

	/*
		CComPtr<ILSMILXMLAttr> attr;
		m_targetElement->animatableXMLAttrItem(m_index, &attr);

		CComBSTR namespaceURI;
		attr->get_name(&namespaceURI);

		CComBSTR attributeName;
		attr->get_name(&attributeName);
		*/

		CComPtr<IEXMLDocument> eDocument = m_viewGroup->get_eXMLDocument();

		CComPtr<ILDOMDocument> document;
		eDocument->get_DOMDocument(&document);

		CComQIPtr<ILDOMElement> documentElement = document->get_documentElement();
		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
		xtras/ASSERT(svgsvgElement != NULL);	// TODO

		CComBSTR namespaceURI = NULL;
		CComBSTR attributeType = m_attributes[m_index].m_attributeType;
		CComBSTR attributeName = m_attributes[m_index].m_attributeName;

		CComPtr<ILDOMElement> animationElement;

		if (m_attributes[m_index].m_flags == ANIMATEMOTION)
		{
			document->createElement(L"animateMotion", &animationElement);

			animationElement->setAttribute(L"path", L"M0,0 L40,40");
		}
		else if (m_attributes[m_index].m_flags == ANIMATETRANSFORM)
		{
			document->createElement(L"animateTransform", &animationElement);

			HMENU hMenu;
			hMenu = CreatePopupMenu();

			AppendMenu(hMenu, MF_STRING, 1, _T("Translate"));
			AppendMenu(hMenu, MF_STRING, 2, _T("Rotate"));
			AppendMenu(hMenu, MF_STRING, 3, _T("Scale"));
			AppendMenu(hMenu, MF_STRING, 4, _T("SkewX"));
			AppendMenu(hMenu, MF_STRING, 5, _T("SkewY"));
	//		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

			CPoint point(point.x, point.y);
			::ClientToScreen(m_hWnd, &point);

			UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

			DestroyMenu(hMenu);

			if (nID > 0)
			{
				switch (nID)
				{
				case 1:
					{
						animationElement->setAttribute(L"type", L"translate");
						animationElement->setAttribute(L"values", L"0,0;60,0");
					}
					break;

				case 2:
					{
						animationElement->setAttribute(L"type", L"rotate");
						animationElement->setAttribute(L"values", L"0;45");
					}
					break;
				
				case 3:
					{
						animationElement->setAttribute(L"type", L"scale");
					}
					break;
				
				case 4:
					{
						animationElement->setAttribute(L"type", L"skewX");
					}
					break;
				
				case 5:
					{
						animationElement->setAttribute(L"type", L"skewY");
					}
					break;
				}
			}

			animationElement->setAttribute(L"additive", L"sum");

			animationElement->setAttribute(L"keyTimes", L"0;1");
		}
		else
		{
			document->createElement(L"animate", &animationElement);

			CComBSTR value;

			if (!wcscmp(attributeType, L"XML"))
			{
				targetElement->getAttributeNS(namespaceURI, attributeName, &value);
			}
			else
			{
				CComPtr<ILHTMLWindow> window;
				static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_layoutView->m_pBehavior->GetHTMLWindow(&window);

				CComQIPtr<ILDOMViewCSS> cssView = window;

				CComPtr<ILCSSStyleDeclaration> style;
				cssView->getComputedStyle(targetElement, NULL, &style);

				style->getPropertyValue(attributeName, &value);
			}

			CComBSTR values;
			values = value;
			values += L";";
			values += value;

			animationElement->setAttribute(L"keyTimes", L"0;1");
			animationElement->setAttribute(L"values", values);
		}

		if (attributeType) animationElement->setAttribute(L"attributeType", attributeType);
		animationElement->setAttribute(L"attributeName", attributeName);

		{
			CComQIPtr<ILElementTime> parentElementTime = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_pActiveTimeGraphElement->m_parent->m_domElement;

			double t;
			parentElementTime->get_simpleTime(&t);

			WCHAR buf[64];
			swprintf(buf, L"%g", t);

			animationElement->setAttribute(L"begin", buf);
		}

		animationElement->setAttribute(L"dur", L"60");

	//	animationElement->setAttribute(L"from", L"0");
	//	animationElement->setAttribute(L"to", L"120");

		if (targetElementId.Length())
			animationElement->setAttribute(L"targetElement", targetElementId);

		static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_pActiveTimeGraphElement->m_parent->m_domElement->insertBefore(animationElement, CComVariant(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_pActiveTimeGraphElement->m_domElement), NULL);

	//	element->appendChild(animationElement, NULL);
	}
#endif
	return 0;
}

LRESULT CAnimateAttributesDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
// Insert an animation element as a child of the animation target
	if (m_targetElement)
	{
		long nattrs;
		m_targetElement->get_animatableXMLAttrsCount(&nattrs);

		CComQIPtr<ILDOMNode> node = m_targetElement;

		CComPtr<ILDOMDocument> document;
		node->get_ownerDocument(&document);

		if (m_index >= 0 && m_index < nattrs)
		{
			CComPtr<ILSMILXMLAttr> attr;
			m_targetElement->animatableXMLAttrItem(m_index, &attr);

			CComBSTR namespaceURI;
			attr->get_name(&namespaceURI);

			CComBSTR attributeName;
			attr->get_name(&attributeName);

			CComPtr<ILDOMElement> animationElement;
			document->createElement(L"animate", &animationElement);

			animationElement->setAttribute(L"attributeType", L"XML");
			animationElement->setAttribute(L"attributeName", attributeName);

			node->appendChild(animationElement, NULL);
		}
	}
#endif

	return 0;
}

void CAnimateAttributesDlg::ResetVScrollBar()
{
	int visible = (m_areaRect.Height()+m_itemHeight-1)/m_itemHeight;

	m_vert->SetInfo(0, m_attributes.size(), visible);
}

LRESULT CAnimateAttributesDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right-16;
	m_areaRect.bottom = client.bottom;

	m_axvert.MoveWindow(m_areaRect.right, m_areaRect.top, 16, m_areaRect.Height(), TRUE);

	ResetVScrollBar();

	Invalidate();

	return 0;
}

void __stdcall CAnimateAttributesDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	/*
	if (m_edit)
	{
		CRect wrect;
		::GetWindowRect(m_edit, &wrect);
		ScreenToClient((LPPOINT)&wrect.left);
		ScreenToClient((LPPOINT)&wrect.right);
		::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
	}
	*/

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);

	ScrollWindow(0, (oldPos-pos)*m_itemHeight, &rect, &rect);
}

void __stdcall CAnimateAttributesDlg::OnViewGroupSelectionChanged()
{
	m_attributes.clear();

	IESelectedElement* selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	if (selectedElement)
	{
		IEElement* eElement;
		selectedElement->get_eElement(&eElement);

		LXML::Element* domelement = eElement->get_domElement();

		ILSMILAnimationTarget* targetElement = dynamic_cast<ILSMILAnimationTarget*>(domelement);

		if (targetElement)
		{
			m_targetElement = targetElement;

			CComBSTR namespaceURI;
			domelement->get_namespaceURI(&namespaceURI);

			CComBSTR tagName;
			domelement->get_localName(&tagName);
			if (tagName.Length() == 0)
			{
				tagName.Empty();
				domelement->get_tagName(&tagName);
			}

			if (!wcscmp(namespaceURI, L"http://www.w3.org/2000/svg"))
			{
				if (!wcscmp(tagName, L"svg"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"width", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"height", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"viewBox", SET | ANIMATE));
				}
				else if (!wcscmp(tagName, L"g"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"circle"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"cx", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"cy", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"r", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"ellipse"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"cx", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"cy", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"rx", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"ry", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"rect"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"width", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"height", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"image"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"width", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"height", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
					// TODO xlink:href
				}
				else if (!wcscmp(tagName, L"use"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"width", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"height", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
					// TODO xlink:href
				}
				else if (!wcscmp(tagName, L"video"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"width", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"height", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"line"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x1", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y1", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x2", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y2", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"path"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"d", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"polygon"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"points", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"polyline"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"points", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
			// text
				else if (!wcscmp(tagName, L"text"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"rotate", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"tspan"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"dx", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"dy", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"rotate", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"textPath"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"startOffset", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"transform", ANIMATETRANSFORM));
				}
			// gradient/pattern
				else if (!wcscmp(tagName, L"linearGradient"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x1", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y1", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"x2", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"y2", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"spreadMethod", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"gradientTransform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"radialGradient"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"cx", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"cy", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"spreadMethod", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"gradientTransform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"pattern"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"patternTransform", ANIMATETRANSFORM));
				}
				else if (!wcscmp(tagName, L"stop"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"offset", SET | ANIMATE));
				}
			// filters
				else if (!wcscmp(tagName, L"feGaussianBlur"))
				{
					m_attributes.push_back(AnimatableAttribute(L"XML", L"stdDeviation", SET | ANIMATE));
				}
			}
			else if (!wcscmp(namespaceURI, L"http://www.w3.org/2001/SMIL20/Language"))
			{
				if (!wcscmp(tagName, L"region"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"left", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"top", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"right", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"bottom", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"width", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"height", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"backgroundColor", SET | ANIMATECOLOR));
				}
				else if (
					!wcscmp(tagName, L"img") ||
					!wcscmp(tagName, L"video"))
				{
					m_attributes.push_back(AnimatableAttribute(NULL, L"motion", ANIMATEMOTION));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"left", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"top", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"right", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"bottom", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"width", SET | ANIMATE));
					m_attributes.push_back(AnimatableAttribute(L"XML", L"height", SET | ANIMATE));
				}
			}

			if (TRUE)	// CSS Properties
			{
				for (int i = 0; i < g_nCSSProperties; i++)
				{
					m_attributes.push_back(AnimatableAttribute(L"CSS", CSSProperties[i].m_name, SET | ANIMATE));
				}
			}
		}
	}

	if (m_hWnd)
	{
		ResetVScrollBar();
		Invalidate();
	}
}

#if 0
STDMETHODIMP CAnimateAttributesDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;

	if (viewGroup)
	{
//		CComPtr<IWebXMLDocument> edocument;
//		element->get_ownerDocument(&edocument);

		m_viewGroup = viewGroup;
		IDispEventImpl<2, CAnimateAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		OnViewGroupSelectionChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CAnimateAttributesDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	IDispEventImpl<2, CAnimateAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();

	m_targetElement.Release();

	return S_OK;
}
#endif

#endif