#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridNode.h"
#include "XMLGridNotWellformed.h"

#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::Rect* rc, LDraw::Color clr);

//////////////////////////////////
// CGridNotWellformed

//virtual
void CGridNotWellformed::BuildXML(System::StringBuilderW& stream)
{
	Web::NodeType nodeType = m_domNode->get_nodeType();

	/*
	if (nodeType == LNODE_CDATA_SECTION)
	{
		return L"<![CDATA[" + GetValue() + L"]]>";
	}
	else if (nodeType == LNODE_COMMENT)
	{
		return L"<!--" + GetValue() + L"-->";
	}
	else
	*/
	{
		stream << *GetValue();
	}
}

// virtual
void CGridNotWellformed::BuildXML(System::IO::ISequentialByteStream* stream)
{
	Web::NodeType nodeType = m_domNode->get_nodeType();

	ASSERT(sizeof(nodeType) == 4);
	stream->Write(&nodeType, 4);

	ASSERT(0);
#if 0
	CComBSTR((BSTR)GetValue()).WriteToStream(stream);
#endif
}

System::StringW* CGridNotWellformed::GetValue()
{
	ASSERT(0);
	return NULL;
#if 0
	CComQIPtr<ILDOMNotWellformed> node = m_domNode;
	ATLASSERT(node);

	BSTR bvalue;
	node->get_data(&bvalue);
	return sysstring(bvalue, false);
#endif
}

//virtual
void CGridNotWellformed::OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree)
{
	ASSERT(0);
#if 0
	m_bEditChanged = TRUE;

	m_pTree->Size(hDC, m_pTree->m_size.cx);

	::SetWindowPos(m_hWndEdit, NULL, 0, 0, m_size.cx+2, m_size.cy+2, SWP_NOMOVE);
#endif
}

//virtual
void CGridNotWellformed::Size(MSWindows::HDC hDC, int width)
{
	ASSERT(0);
#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	sysstring value;
	
	if (m_hWndEdit)
	{
		int len = ::GetWindowTextLength(m_hWndEdit);
		TCHAR* buf = new TCHAR[len+1];

		::GetWindowText(m_hWndEdit, buf, len+1);

		value = buf;
		delete buf;
	}
	else
	{
		value = GetValue();
	}

	//m_size.cx = 20;

	int left = 0;

	if (width < 2) width = 2;

	//if (width > 0)
	{
		CRect rc(0, 0, width-left-2, 0);
		ATLASSERT(rc.Width() >= 0);
		DrawText(hDC, value, value.length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

		m_size.cx = max(width, rc.Width()+left);
		if (m_size.cx < 20) m_size.cx = 20;
		m_size.cy = rc.Height()+2;
	}
	/*
	else if (width == -1)	// Optimal width
	{
		CRect rc(0, 0, 0, 0);
		DrawText(hDC, value, value.length(), &rc, DT_CALCRECT);

		m_size.cx = rc.Width();
		m_size.cy = rc.Height();
	}
	*/
#endif
}

//virtual
void CGridNotWellformed::Draw(MSWindows::HDC hDC, bool bSelected)
{
	ASSERT(0);
#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	if (m_selected) bSelected = TRUE;

	sysstring value = GetValue();

	int left = 0;
	CRect trect(0, left, m_size.cx, m_size.cy);

	FillSolidRect(hDC, 0, 0, m_size.cx, m_size.cy, bSelected? RGB(138, 200, 235): RGB(255, 255, 255));
	DrawTopLeft(hDC, &trect, RGB(200, 200, 200));

	trect.InflateRect(-1, -1);
	DrawText(hDC, value, value.length(), &trect, DT_EDITCONTROL | DT_WORDBREAK);
#endif
}

// virtual
int CGridNotWellformed::HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal)
{
	*pVal = NULL;

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
int CGridNotWellformed::Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal)
{
	ASSERT(0);
#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	*pVal = NULL;

	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx && point.y < m_size.cy)
	{
		if (bDblClk)
		{
			POINT org;
			GetViewportOrgEx(hDC, &org);

			ATLASSERT(m_bEditChanged == false);

			m_hWndEdit = CreateWindowEx(0, "edit", GetValue(), WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE,
				org.x-1, org.y-1, m_size.cx+2, m_size.cy+2, m_pUI->m_hWnd, (HMENU)1, _Module.m_hInst, NULL);

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
	return 0;
}

//virtual
void CGridNotWellformed::EndEdit(/*CXMLGridCtl* pUI*/)
{
	ASSERT(0);
#if 0
	if (m_bEditChanged)
	{
		m_bEditChanged = false;

		CComQIPtr<ILDOMNotWellformed> node = m_domNode;
		ATLASSERT(node);

		CComPtr<ILDOMDocument> ownerDocument;
		node->get_ownerDocument(&ownerDocument);

		CComPtr<ILDOMNode> parentNode;
		node->get_parentNode(&parentNode);

		ATLASSERT(m_hWndEdit);

		int len = ::GetWindowTextLength(m_hWndEdit);
		TCHAR* buf = new TCHAR[len+1];

		::GetWindowText(m_hWndEdit, buf, len+1);

		m_pUI->m_wndEdit.DestroyWindow();
		m_hWndEdit = NULL;

		CComPtr<ILDOMDocumentFragment> fragment;
		ownerDocument->parseFragment(sysstring(buf), parentNode, &fragment);
		if (fragment)
		{
			CComPtr<ILDOMNode> replacedChild;
			parentNode->replaceChild(fragment, node, &replacedChild);
		}
		else
		{
			node->put_data(sysstring(buf));
		}

		delete buf;
	}
	else
	{
		m_pUI->m_wndEdit.DestroyWindow();
		m_hWndEdit = NULL;
	}
#endif
}

}
