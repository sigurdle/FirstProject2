#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridNode.h"
#include "XMLGridProcessingInstruction.h"

#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

//////////////////////////////////
// CGridProcessingInstruction

/*
//virtual
System::StringW* CGridProcessingInstruction::BuildXML()
{
	LDOMNodeType nodeType = m_domNode->get_nodeType();

	if (nodeType == LNODE_CDATA_SECTION)
	{
		return WSTR("<![CDATA[" + GetValue() + L"]]>");
	}
	else if (nodeType == LNODE_COMMENT)
	{
		return WSTR("<!--" + GetValue() + L"-->");
	}
	else
	{
		return GetValue();
	}
}
*/

// virtual
void CGridProcessingInstruction::BuildXML(System::StringBuilderW& stream)
{
	Web::NodeType nodeType = m_domNode->get_nodeType();

	ASSERT(0);
#if 0

	CComQIPtr<ILDOMProcessingInstruction> pi = m_domNode;

	ATLASSERT(sizeof(_LDOMNodeType) == 4);
	stream->Write(&nodeType, 4, NULL);

	CComBSTR target;
	pi->get_target(&target);

	CComBSTR data;
	pi->get_data(&data);

	target.WriteToStream(stream);
	data.WriteToStream(stream);
#endif
}

System::StringW* CGridProcessingInstruction::GetValue()
{
	return NULL;//sysstring();
#if 0
	CComQIPtr<ILDOMProcessingInstruction> pi = m_domNode;
	ATLASSERT(pi);

	BSTR bvalue;
	pi->get_data(&bvalue);
	return sysstring(bvalue, false);
#endif
}

//virtual
void CGridProcessingInstruction::OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree)
{
	ASSERT(0);
#if 0
	m_bEditChanged = TRUE;

	m_pTree->Size(hDC, m_pTree->m_size.cx);

	::SetWindowPos(m_hWndEdit, NULL, 0, 0, m_size.cx+2, m_size.cy+2, SWP_NOMOVE);
#endif
}

//virtual
void CGridProcessingInstruction::Size(MSWindows::HDC hDC, int width)
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

	m_size.cx += 90;
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
void CGridProcessingInstruction::Draw(MSWindows::HDC hDC, bool bSelected)
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	CComQIPtr<ILDOMProcessingInstruction> pi = m_domNode;

	if (m_selected) bSelected = TRUE;

	{
		CComBSTR target;
		pi->get_target(&target);

		CRect trect(0, 0, 90, m_size.cy);

		FillSolidRect(hDC, 0, 0, 90, m_size.cy, bSelected? RGB(138, 200, 235): RGB(255, 255, 255));
		DrawTopLeft(hDC, &trect, RGB(200, 200, 200));

		trect.InflateRect(-1, -1);

		SelectObject(hDC, m_pUI->m_hFont[Font_AttributeName]);

		SetTextColor(hDC, RGB(0, 160, 0));
		DrawText(hDC, "<?", 2, &trect, DT_SINGLELINE);

		trect.left += 16;
		SetTextColor(hDC, RGB(0, 0, 0));
		DrawText(hDC, W2A(target), target.Length(), &trect, DT_SINGLELINE);
	}

	{
		SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

		CComBSTR data;
		pi->get_data(&data);

		CRect trect(90, 0, m_size.cx, m_size.cy);

		FillSolidRect(hDC, &trect, bSelected? RGB(138, 200, 235): RGB(255, 255, 255));
		DrawTopLeft(hDC, &trect, RGB(200, 200, 200));

		trect.InflateRect(-1, -1);
		DrawText(hDC, W2A(data), data.Length(), &trect, DT_EDITCONTROL | DT_WORDBREAK);
	}
#endif
}

// virtual
int CGridProcessingInstruction::HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal)
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
int CGridProcessingInstruction::Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal)
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
				90+org.x-1, org.y-1, m_size.cx+2-90, m_size.cy+2, m_pUI->m_hWnd, (HMENU)1, _Module.m_hInst, NULL);

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
void CGridProcessingInstruction::EndEdit(/*CXMLGridCtl* pUI*/)
{
	ASSERT(0);
#if 0
	if (m_bEditChanged)
	{
		CComQIPtr<ILDOMProcessingInstruction> pi = m_domNode;
		ATLASSERT(pi);

		ATLASSERT(m_hWndEdit);

		int len = ::GetWindowTextLength(m_hWndEdit);
		TCHAR* buf = new TCHAR[len+1];

		::GetWindowText(m_hWndEdit, buf, len+1);

		pi->put_data(sysstring(buf));

		delete buf;

		m_bEditChanged = false;
	}

	m_pUI->m_wndEdit.DestroyWindow();
	m_hWndEdit = NULL;
#endif
}

}
