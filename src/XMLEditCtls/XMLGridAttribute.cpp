#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridAttribute.h"

#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

//////////////////////////////////////////////////////////////////////
// CGridAttribute

// virtual
void CGridAttribute::BuildChildren()
{
	LXmlEdit::Attr* attr = dynamic_cast<LXmlEdit::Attr*>(m_domNode);

	m_icon = new UI::TextString(WSTR("="));
	AddRChild(m_icon);

	m_nodeNameEdit = new UI::TextEdit(attr->get_nodeName());
	AddRChild(m_nodeNameEdit);

	m_childNodes = new ChildNodes;
	AddRChild(m_childNodes);

	LXmlEdit::Node* child = m_domNode->get_firstChild();
	while (child != NULL)
	{
		Web::NodeType nodeType = child->get_nodeType();

		CGridNode* pChild = m_pUI->CreateGridNode(child);

		m_childNodes->m_items.push_back(pChild);
		m_childNodes->AddRChild(pChild);

		child = child->get_nextSibling();
	}
}

LDraw::SizeD CGridAttribute::OnMeasure(LDraw::SizeD availSize)
{
	m_icon->Measure(LDraw::SizeD(0, availSize.Height));
	m_nodeNameEdit->Measure(LDraw::SizeD(60, 0));
	m_childNodes->Measure(LDraw::SizeD(availSize.Width-60, 0));

	LDraw::SizeD desiredSize;
	desiredSize.Width = m_nodeNameEdit->get_DesiredSize().Width;
	desiredSize.Height = m_nodeNameEdit->get_DesiredSize().Height;

//	if (m_childNodes->get_Visibility() != Collapsed)
	{
		desiredSize.Width += m_childNodes->get_DesiredSize().Width;
		desiredSize.Height = MAX(desiredSize.Height, m_childNodes->get_DesiredSize().Height);
	}

	desiredSize.Width += m_icon->get_DesiredSize().Width;

	return desiredSize;
}

void CGridAttribute::OnArrange(LDraw::SizeD finalSize)
{
	m_icon->Arrange(LDraw::RectD(0, 0, m_icon->get_DesiredSize().Width, finalSize.Height));
	//m_icon->SetLayoutOffset(0, 0);

	m_nodeNameEdit->Arrange(LDraw::RectD(m_icon->get_ActualSize().Width, 0, 60, m_nodeNameEdit->get_DesiredSize().Height));
	//m_nodeNameEdit->SetLayoutOffset(m_icon->get_ActualSize().Width, 0);

	m_childNodes->Arrange(LDraw::RectD(m_icon->get_ActualSize().Width+60, 0, finalSize.Width-60, m_childNodes->get_DesiredSize().Height));
	//m_childNodes->SetLayoutOffset(m_icon->get_ActualSize().Width+60, 0);
}

// virtual
void CGridAttribute::BuildXML(System::IO::ISequentialByteStream* stream)
{
	ASSERT(0);
}

// virtual
void CGridAttribute::BuildXML(System::StringBuilderW& stream)
{
	ASSERT(0);
#if 0
	ATLASSERT(sizeof(_LDOMNodeType) == 4);
	_LDOMNodeType nodeType = LNODE_ATTRIBUTE;
	stream->Write(&nodeType, 4, NULL);

	CComBSTR(GetNodeName().c_str()).WriteToStream(stream);

// Children (including attributes)
	int nchildren = m_childList.GetCount();
	//if (TRUE)
//		nchildren -= 1;

	ULONG cb;
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

/*
// virtual
sysstring CGridAttribute::BuildXML()
{
	ATLASSERT(0);
	sysstring str = GetNodeName();
	str += L"=\"";
#if 0

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pItem = (CGridItem*)m_childList.GetNext(pos);
		sysstring str2 = pItem->BuildXML();
		str += str2;
	}

	str += L"\"";
#endif
	return str;
}
*/

#if 0
//virtual
void CGridAttribute::SizeContent(HDC hDC, int width)
{
	ATLASSERT(0);
#if 0
	int y = 0;
// Child elements
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);
		pChild->Size(hDC, width);

		//ATLASSERT(pChild->m_size.cx > 0);
		//maxx = max(maxx, pChild->m_size.cx);

		pChild->m_pos.X = m_childrenIndent;

		y += pChild->m_desiredSize.Height;
	}

	m_desiredSize.Height = max(m_desiredSize.Height, y);

#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	sysstring name = GetNodeName();

	if (width < 10) width = 10;

	{
		CRect rc(0, 0, 0, 0);
		DrawText(hDC, name, name.length(), &rc, DT_CALCRECT | DT_SINGLELINE | DT_EDITCONTROL/* | DT_WORDBREAK*/);

		m_size.cy = rc.bottom;
	}
#endif

	/*
	sysstring value = GetValue();

	CRect rc(0, 0, width-2, 0);
	ATLASSERT(rc.Width() >= 0);
	DrawText(hDC, value, value.length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

	m_size.cx = max(width, rc.Width());
	m_size.cy = max(m_size.cy, rc.Height());

	m_size.cy += 2;

	m_contentRect = CRect(0, 0, m_size.cx, m_size.cy);
*/
#endif
}
#endif

#if 0
//virtual
void CGridAttribute::Size(HDC hDC, int width)
{
	sysstring nodeName = m_domNode->get_nodeName();

	ATLASSERT(0);
#if 0

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect rc(0,0,0,0);
	DrawText(hDC, sysstring(nodeName), nodeName.Length(), &rc, DT_CALCRECT | DT_SINGLELINE);

	m_nameHeight = rc.Height();

	width = max(width, m_childrenIndent+rc.Width());
	width -= m_childrenIndent;

	m_size.cx = width;
	m_size.cy = 0;

	if (TRUE)//m_expanded)
	{
		SizeContent(hDC, width);
	}

	/*
	SizeContent(hDC, width-80);

	m_size.cx += 80;
	m_contentRect.OffsetRect(80, 0);
	*/

	m_size.cx += m_childrenIndent;
	m_size.cy = max(m_nameHeight, m_size.cy);
#endif
}

// virtual
void CGridAttribute::DrawContent(HDC hDC, BOOL bSelected)
{
	ATLASSERT(0);
#if 0
// Same as GridElement
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
#if 0

	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	if (m_selected) bSelected = TRUE;

	sysstring value = GetValue();

	CRect valuerect = m_contentRect;//(m_attrNameWidth, 0, /*m_attrNameWidth*/m_size.cx, m_size.cy);
	//DrawTopLeft(hDC, &valuerect, RGB(200, 200, 200));

	valuerect.left++;
	valuerect.top++;

	if (bSelected)
		FillSolidRect(hDC, &valuerect, RGB(138, 200, 235));

	DrawText(hDC, value, value.length(), &valuerect, DT_WORDBREAK | DT_EDITCONTROL);
#endif
#endif
}

// virtual
void CGridAttribute::Draw(HDC hDC, BOOL bSelected)
{
	ATLASSERT(0);
#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_AttributeName]);

	if (m_selected) bSelected = TRUE;

	if (bSelected)
//		FillSolidRect(hDC, &rect, RGB(138, 200, 235));
		FillSolidRect(hDC, 0, 0, m_size.cx, m_size.cy, RGB(138, 200, 235));

//	DrawTopLeft(hDC, &CRect(0, 0, m_size.cx, m_size.cy), RGB(200,200,200));

	CRect rect(0, 0, m_childrenIndent, m_size.cy);
	DrawTopLeft(hDC, &rect, RGB(200, 200, 200));

//	rect.left++;
//	rect.top++;

//
	CRect iconrect(16+0, 1+0, 16+16, m_size.cy);
	SetTextColor(hDC, RGB(200, 0, 0));
	DrawText(hDC, "=", 1, &iconrect, DT_SINGLELINE | /*DT_VCENTER |*/ DT_CENTER);

//
	sysstring nodeName = GetNodeName();
	CRect trect(16+16, 1+0, m_childrenIndent, m_size.cy);
	SetTextColor(hDC, RGB(0, 0, 0));
	DrawText(hDC, nodeName, nodeName.length(), &trect, DT_SINGLELINE | DT_END_ELLIPSIS);

#if 0
	CRect valuerect(m_childrenIndent, 0, /*m_attrNameWidth*/m_size.cx, m_size.cy);
	DrawTopLeft(hDC, &valuerect, RGB(200, 200, 200));
#endif
//	valuerect.InflateRect(-1, -1);
//	DrawText(hDC, value, value.length(), &valuerect, DT_WORDBREAK | DT_EDITCONTROL);

	if (TRUE)//m_expanded)
	{
		POINT oldOrg;
		OffsetViewportOrgEx(hDC, m_childrenIndent, 0/*m_nameHeight*/, &oldOrg);

		DrawContent(hDC, bSelected);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	}
#endif
}
#endif

// virtual
int CGridAttribute::ClickContent(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem** pVal)
{
	ASSERT(0);
#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

#if 0
	if (point.x >= 0 && point.y >= 0 && point.x < m_contentRect.Width() && point.y < m_contentRect.Height())
	{
		if (bDblClk)
		{
			POINT org;
			GetViewportOrgEx(hDC, &org);

			ATLASSERT(m_bEditChanged == false);

			m_hWndEdit = CreateWindowEx(0, "edit", GetNodeName(), WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE,
				org.x-1/* + attrNameWidth*/, org.y-1, m_contentRect.Width()+2/*-attrNameWidth*/, m_contentRect.Height()+2, m_pUI->m_hWnd, (HMENU)1, _Module.m_hInst, NULL);

			m_pUI->m_wndEdit.SubclassWindow(m_hWndEdit);

			if (m_hWndEdit)
			{
				::SetWindowLong(m_hWndEdit, GWL_USERDATA, (long)this);

				HFONT hFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
				SendMessage(m_hWndEdit, WM_SETFONT, (WPARAM)hFont, 0);

				SendMessage(m_hWndEdit, EM_SETSEL, 0, -1);
				SetFocus(m_hWndEdit);
			}
		}

		*pVal = this;
		return 1;
	}
#endif
#endif
	return 0;
}

// virtual
int CGridAttribute::HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal)
{
	ASSERT(0);
#if 0
	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx && point.y < m_size.cy)
	{
		*pVal = this;
		return 1;
	}
#endif
	return 0;
}

//virtual
int CGridAttribute::Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal)
{
	*pVal = NULL;

	ASSERT(0);
#if 0

	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx && point.y < m_size.cy)
	{
		if (point.x < m_childrenIndent)
		{
		}
		else
		{
			CPoint contentpoint = point;
			contentpoint.x -= m_childrenIndent;

			CPoint oldOrg;
			OffsetViewportOrgEx(hDC, m_childrenIndent, 0, &oldOrg);

			int nClick = ClickContent(hDC, contentpoint, nFlags, bDblClk, pVal);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			if (*pVal)
				return nClick;
		}

		*pVal = this;
		return 1;
	}
#endif
	return 0;
}

}
