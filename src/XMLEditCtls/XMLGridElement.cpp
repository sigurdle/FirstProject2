#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridCtl.h"
#include "XMLGridElement.h"

#include "XMLGridAttribute.h"
#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

//////////////////////////////////////////////////////////////////////
// CGridElement

CGridAttribute* CGridElement::FindAttribute(System::StringW* name)
{
	list<CGridAttribute*>::iterator pos = m_attributeList.begin();
	while (pos != m_attributeList.end())
	{
		CGridAttribute* pAttr = *pos;//(CGridAttribute*)m_attributeList.GetNext(pos);
		++pos;

		if (*pAttr->GetNodeName() == *name)
		{
			return pAttr;
		}
	}

	return NULL;
}

// virtual
void CGridElement::BuildXML(System::IO::ISequentialByteStream* stream)
{
	ULONG cb;

	ASSERT(sizeof(Web::NodeType) == 4);
	Web::NodeType nodeType = Web::NODE_ELEMENT;
	stream->Write(&nodeType, 4);

	ASSERT(0);
#if 0

	CComBSTR((BSTR)GetNodeName()).WriteToStream(stream);

//	int nattributes = m_attributeList.GetCount();
//	stream->Write(&n, 4, &cb);

// We write the number of attributes
	int nattributes = m_attributeList.GetCount();
	stream->Write(&nattributes, 4, &cb);

// Children (including attributes)
	int nchildren = m_childList.GetCount();
	if (TRUE)
		nchildren -= 1;

	stream->Write(&nchildren, 4, &cb);

// Children
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pItem = (CGridItem*)m_childList.GetNext(pos);

		pItem->BuildXML(stream);
	}
#endif
}

// virtual
void CGridElement::BuildXML(System::StringBuilderW& stream)
{
	stream << L"<";
	stream << *GetNodeName();

	int n = 0;
	list<CGridAttribute*>::iterator pos = m_attributeList.begin();//GetHeadPosition();
	while (pos != m_attributeList.end())
	{
		CGridItem* pItem = *pos;//(CGridItem*)m_attributeList.GetNext(pos);
		++pos;

		stream << L" ";
		pItem->BuildXML(stream);

		n++;
	}

	if (!m_nodeList.empty())
	{
		stream << L">\n";

		list<CGridItem*>::iterator pos = m_nodeList.begin();//GetHeadPosition();
		while (pos != m_nodeList.end())
		{
			CGridItem* pItem = *pos;//(CGridItem*)m_nodeList.GetNext(pos);
			++pos;

			pItem->BuildXML(stream);
		}

		stream << L"</" << *GetNodeName() << L">\n";
	}
	else
	{
		stream << L"/>\n";
	}
}

void CGridElement::handleEvent(System::Event* evt)
{
	System::StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (evt->get_target() == m_expandButton && *type == L"click")
		{
			evt->stopPropagation();
			m_childNodes->set_Visibility(m_childNodes->get_Visibility() != UI::Visible? UI::Visible: UI::Collapsed);
			//InvalidateMeasure();

		//	Measure(LDraw::SizeD(0, 0));
		}
	}
}

void CGridElement::RebuildChildList()
{
//	m_childList.RemoveAll();

	m_childNodes = new ChildNodes;
	AddRChild(m_childNodes);

	{
		list<CGridAttribute*>::iterator pos = m_attributeList.begin();//GetHeadPosition();
		while (pos != m_attributeList.end())
		{
			CGridItem* pItem = *pos;//(CGridItem*)m_attributeList.GetNext(pos);
			++pos;

			m_childNodes->AddRChild(pItem);
			m_childNodes->m_items.push_back(pItem);
		}
	}

	{

		list<CGridItem*>::iterator pos = m_nodeList.begin();//GetHeadPosition();
		while (pos != m_nodeList.end())
		{
			CGridItem* pItem = *pos;//(CGridItem*)m_nodeList.GetNext(pos);
			++pos;

			m_childNodes->AddRChild(pItem);
			m_childNodes->m_items.push_back(pItem);
		}
	}
}

// virtual
void CGridElement::BuildChildren()
{
	LXmlEdit::Element* element = dynamic_cast<LXmlEdit::Element*>(m_domNode);

	m_expandButton = new UI::Button(new UI::TextString(WSTR("V")));
	AddRChild(m_expandButton);

	m_icon = new UI::TextString(WSTR("<"));
	AddRChild(m_icon);

	m_nodeNameEdit = new UI::TextEdit(element->get_nodeName());
	AddRChild(m_nodeNameEdit);

	LXmlEdit::NamedNodeMap* attributes = element->get_attributes();

	unsigned long length = attributes->get_length();
	for (unsigned long i = 0; i < length; i++)
	{
		LXmlEdit::Attr* attr = dynamic_cast<LXmlEdit::Attr*>(attributes->item(i));

		CGridAttribute* pChild = (CGridAttribute*)m_pUI->CreateGridNode(attr);

		pChild->BuildChildren();

		m_attributeList.push_back(pChild);
	}

	LXmlEdit::Node* child = m_domNode->get_firstChild();
	while (child != NULL)
	{
		Web::NodeType nodeType = child->get_nodeType();

		//if (nodeType == LNODE_DOCUMENT_TYPE)
		{
			CGridNode* pChild = m_pUI->CreateGridNode(child);

			pChild->BuildChildren();

			m_nodeList.push_back(pChild);
		}

		child = child->get_nextSibling();
	}

	if (true)
	{
		CGridEmpty* pEmpty = new CGridEmpty;
		m_nodeList.push_back(pEmpty);
	}

	RebuildChildList();
}

LDraw::SizeD CGridElement::OnMeasure(LDraw::SizeD availSize)
{
	m_expandButton->Measure(LDraw::SizeD(0, availSize.Height));
	m_icon->Measure(LDraw::SizeD(0, availSize.Height));
	m_nodeNameEdit->Measure(LDraw::SizeD(availSize.Width-10, 0));
	m_childNodes->Measure(LDraw::SizeD(availSize.Width-10, 0));

	LDraw::SizeD desiredSize;
	desiredSize.Width = m_nodeNameEdit->get_DesiredSize().Width;
	desiredSize.Height = m_nodeNameEdit->get_DesiredSize().Height;

	if (m_childNodes->get_Visibility() != UI::Collapsed)
	{
		desiredSize.Width = MAX(desiredSize.Width, m_childNodes->get_DesiredSize().Width);
		desiredSize.Height += m_childNodes->get_DesiredSize().Height;
	}

	desiredSize.Width += m_expandButton->get_DesiredSize().Width;
	desiredSize.Width += m_icon->get_DesiredSize().Width;

	return desiredSize;
}

void CGridElement::OnArrange(LDraw::SizeD finalSize)
{
	m_expandButton->Arrange(LDraw::RectD(0, 0, m_expandButton->get_DesiredSize().Width, finalSize.Height));
	//m_expandButton->SetLayoutOffset(0, 0);

	m_icon->Arrange(LDraw::RectD(m_expandButton->get_ActualSize().Width, 0, m_icon->get_DesiredSize().Width, finalSize.Height));
	//m_icon->SetLayoutOffset(m_expandButton->get_ActualSize().Width, 0);

	m_nodeNameEdit->Arrange(LDraw::RectD(m_expandButton->get_ActualSize().Width + m_icon->get_ActualSize().Width, 0, finalSize.Width, m_nodeNameEdit->get_DesiredSize().Height));
	//m_nodeNameEdit->SetLayoutOffset(m_expandButton->get_ActualSize().Width + m_icon->get_ActualSize().Width, 0);

	m_childNodes->Arrange(LDraw::RectD(m_expandButton->get_ActualSize().Width, m_nodeNameEdit->get_ActualSize().Height, finalSize.Width-10, m_childNodes->get_DesiredSize().Height));
	//m_childNodes->SetLayoutOffset(m_expandButton->get_ActualSize().Width, m_nodeNameEdit->get_ActualSize().Height);
}

// virtual
// Size this node and it's children
#if 0
void CGridElement::Size(HDC hDC, int width)
{
	ATLASSERT(0);
	CComBSTR nodeName;

	if (m_hWndEdit)
	{
		int len = ::GetWindowTextLength(m_hWndEdit);
		TCHAR* buf = new TCHAR[len+1];

		::GetWindowText(m_hWndEdit, buf, len+1);

		nodeName = sysstring(buf);
		delete buf;
	}
	else
	{
		m_domNode->get_nodeName(&nodeName);
	}

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect rc(0,0,0,0);
	DrawText(hDC, sysstring(nodeName), nodeName.Length(), &rc, DT_CALCRECT | DT_SINGLELINE);

	m_nameHeight = rc.Height();

	width = max(width, m_childrenIndent/*20*/+rc.Width());
	width -= m_childrenIndent;//20;

	m_size.cy = 0;

	if (m_expanded)
	{
		SizeContent(hDC, width);
	}
	else
	{
		m_size.cx = width;
	}

	int y = m_nameHeight;
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

		pChild->m_pos.x = m_childrenIndent;
		pChild->m_pos.y = y;

		y += pChild->m_size.cy;
	}

	m_size.cx += m_childrenIndent;//20;
	m_size.cy += m_nameHeight;
}
#endif

#if 0
// virtual
void CGridContainer::SizeContent(HDC hDC, int width)
{
	ATLASSERT(0);
#if 0
	m_size.cx = 0;
	int maxx = SizeChildren(hDC, width);
	ResizeChildren(hDC, maxx);
	CalculateChildrenSize();
#endif
}
#endif

//virtual
int CGridElement::HitTest(LDraw::PointD point, UINT nFlags, CGridItem* *pVal)
{
	*pVal = NULL;

	ASSERT(0);
#if 0

	CRect erect(2, 2, 12, m_size.cy-2);

//	POINT org;
//	GetViewportOrgEx(hDC, &org);

	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx+2 && point.y < m_size.cy+2)
	{
		int nClick = CGridContainer::HitTest(point, nFlags, pVal);
		if (*pVal)
			return nClick;

		//if (!bDblClk)
		{
			if (point.y >= m_nameHeight && point.y <= m_nameHeight+m_attributesHeight &&
						abs((20+m_attrNameWidth)-point.x) <= 2)
			{
				*pVal = this;
				return 1;
			}
		}
		{
			if (point.y < m_nameHeight)	// Edit tagName
			{
				*pVal = this;
				return 2;
			}
		}

		int y = m_nameHeight;

		if (m_expanded)
		{
			POINT childpoint = point;
			childpoint.y -= y;
			childpoint.x -= m_childrenIndent;

			//POINT oldOrg;
			//OffsetViewportOrgEx(hDC, 20, y, &oldOrg);
		//	OffsetViewportOrgEx(hDC, 0, 0, &oldOrg);

			int nClick = HitTestContent(childpoint, nFlags, pVal);

			//SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			if (*pVal)
				return nClick;
		}

		CRect fullRect(0, 0, m_size.cx, m_size.cy);
		if (fullRect.PtInRect(point))
		{
			*pVal = this;
			return 1;
		}
	}

	*pVal = NULL;
#endif
	return 0;
}

// virtual
int CGridElement::Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem** pVal)
{
	ASSERT(0);
#if 0
	*pVal = NULL;

	CRect erect(2, 2, 12, m_size.cy-2);

	POINT org;
	GetViewportOrgEx(hDC, &org);

	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx+2 && point.y < m_size.cy+2)
	{
		int nClick = CGridContainer::Click(hDC, point, nFlags, bDblClk, pVal);
		if (*pVal)
			return nClick;

		if (!bDblClk)
		{
			if (point.y >= m_nameHeight && /*point.y <= m_nameHeight+m_attributesHeight &&*/
						abs((/*20+*/m_childrenIndent)-point.x) <= 2)
			{
				HWND hwnd = m_pUI->m_hWnd;

				m_pUI->SetCapture();

				CPoint oldpoint = point;

				BOOL bLoop = TRUE;
				MSG msg;
				while (bLoop && GetMessage(&msg, hwnd, 0, 0))
				{
					TranslateMessage(&msg);

					switch (msg.message)
					{
					case WM_LBUTTONUP:
						{
							bLoop = FALSE;
						}
						break;
						
					case WM_MOUSEMOVE:
						{
							CPoint point;
							point.x = (short)LOWORD(msg.lParam);
							point.y = (short)HIWORD(msg.lParam);

							point.x -= org.x;
							point.y -= org.y;

							m_childrenIndent += (point.x-oldpoint.x);

							Size(hDC, 0);
							if (m_parent)
								m_parent->RecalculateParentSize(hDC);

							//m_pUI->m_pTree->Size(hDC, m_pUI->m_pTree->m_size.cx + (point.x-oldpoint.x));
							//SizeThis(hDC, 20 + m_attrNameWidth pt.x);

							m_pUI->Invalidate();
							m_pUI->OnSize();

							oldpoint = point;
						}
						break;

					default:
						DispatchMessage(&msg);
						break;
					}
				}

				ReleaseCapture();

				*pVal = this;
				return 0;
			}
		}
		else
		{
			if (point.y < m_nameHeight)	// Edit tagName
			{
				POINT org;
				GetViewportOrgEx(hDC, &org);

				ATLASSERT(m_bEditChanged == false);

				CComBSTR nodeName;
				m_domNode->get_nodeName(&nodeName);

				m_hWndEdit = CreateWindowEx(0, "edit", sysstring(nodeName), WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE,
					m_childrenIndent+org.x-1, org.y-1, m_size.cx-16+2, m_nameHeight+2, m_pUI->m_hWnd, (HMENU)1, _Module.m_hInst, NULL);

				m_pUI->m_wndEdit.SubclassWindow(m_hWndEdit);

				if (m_hWndEdit)
				{
					::SetWindowLong(m_hWndEdit, GWL_USERDATA, (long)this);

					HFONT hFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
					SendMessage(m_hWndEdit, WM_SETFONT, (WPARAM)hFont, 0);

					SendMessage(m_hWndEdit, EM_SETSEL, 0, -1);
					SetFocus(m_hWndEdit);
				}

				*pVal = this;
				return 0;
			}
		}

		int y = m_nameHeight;

		if (m_expanded)
		{
			POINT childpoint = point;
			childpoint.y -= y;
			childpoint.x -= m_childrenIndent;

			POINT oldOrg;
			OffsetViewportOrgEx(hDC, m_childrenIndent, y, &oldOrg);
		//	OffsetViewportOrgEx(hDC, 0, 0, &oldOrg);

			int nClick = ClickContent(hDC, childpoint, nFlags, bDblClk, pVal);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			if (*pVal)
				return nClick;
		}

		CRect fullRect(0, 0, m_size.cx, m_size.cy);
		if (fullRect.PtInRect(point))
		{
			*pVal = this;
			return 1;
		}
	}

	*pVal = NULL;
#endif
	return 0;
}

LDraw::SizeD ChildNodes::OnMeasure(LDraw::SizeD availSize)
{
	double width = 0;
	double y = 0;

	for (int i = 0; i < m_items.size(); i++)
	{
		m_items[i]->Measure(LDraw::SizeD(availSize.Width, 0));
		width = MAX(width, m_items[i]->get_DesiredSize().Width);
		y += m_items[i]->get_DesiredSize().Height;
	}

	return LDraw::SizeD(width, y);
}

void ChildNodes::OnArrange(LDraw::SizeD finalSize)
{
	double y = 0;
	for (int i = 0; i < m_items.size(); i++)
	{
		m_items[i]->Arrange(LDraw::RectD(0, y, get_ActualSize().Width, m_items[i]->get_DesiredSize().Height));
		//m_items[i]->SetLayoutOffset(0, y);

		y += m_items[i]->get_ActualSize().Height;
	}
}

#if 0
void ChildNodes::OnRender2(LDraw::Graphics* pGraphics)
{
	int y = 0;

// Draw children
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		POINT oldOrg;
		OffsetViewportOrgEx(hDC, 0, y, &oldOrg);

		CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);
		pChild->Draw(hDC, bSelected);
		y += pChild->m_computedSize.Height;

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	}
}
#endif

#if 0
void CGridElement::Draw(HDC hDC, BOOL bSelected)
{
	ATLASSERT(0);
	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);
	int oldBk = SetBkMode(hDC, TRANSPARENT);

	if (m_selected) bSelected = TRUE;

	if (bSelected)
		FillSolidRect(hDC, 0, 0, m_size.cx, m_size.cy, RGB(138, 200, 235));

	DrawTopLeft(hDC, &CRect(0, 0, m_size.cx, m_size.cy), RGB(200,200,200));

//
	CRect iconrect(16+0, 1+0, 16+16, m_size.cy);
	//iconrect.InflateRect(-1, -1);
	SetTextColor(hDC, RGB(200, 0, 0));
	DrawText(hDC, "<", 2, &iconrect, DT_SINGLELINE | /*DT_VCENTER |*/ DT_CENTER);

//
	sysstring nodeName = GetNodeName();
	CRect trect(16+16, 0, m_size.cx-1, m_nameHeight);
	SetTextColor(hDC, RGB(0, 0, 0));
	DrawText(hDC, nodeName, nodeName.length(), &trect, DT_SINGLELINE | DT_END_ELLIPSIS);

	DrawExpand(hDC, FALSE);

	if (m_expanded)
	{
		POINT oldOrg;
		OffsetViewportOrgEx(hDC, m_childrenIndent, m_nameHeight, &oldOrg);

		DrawContent(hDC, bSelected);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	}

	SetBkMode(hDC, oldBk);
}
#endif

}
