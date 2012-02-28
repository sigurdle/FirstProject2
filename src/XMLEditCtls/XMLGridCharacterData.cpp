#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridNode.h"
#include "XMLGridCharacterData.h"

#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

//////////////////////////////////
// CGridCharacterData

CGridCharacterData::CGridCharacterData(LXmlEdit::Node* node)
{
	m_domNode = node;
	m_charData = dynamic_cast<LXmlEdit::CharacterData*>(m_domNode);

	m_minWidth = 10;

	m_edit = new UI::TextEdit;
	m_edit->set_WordWrap(true);
	m_edit->set_TextDocument(this);

	dynamic_cast<System::EventTargetImpl*>(node)->addEventListener(WSTR("TextChanged"), this, false);
	dynamic_cast<System::EventTargetImpl*>(node)->addEventListener(WSTR("TextInserted"), this, false);
	dynamic_cast<System::EventTargetImpl*>(node)->addEventListener(WSTR("TextDeleted"), this, false);

	set_VisualTree(m_edit);
}

void CGridCharacterData::handleEvent(System::Event* evt)
{
	System::StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (evt->get_target() == dynamic_cast<System::EventTargetImpl*>(m_domNode))
		{
			if (*type == L"TextChanged")
			{
				evt->stopPropagation();

				LXmlEdit::MutationEvent* mutEvt = dynamic_cast<LXmlEdit::MutationEvent*>(evt);

				System::TextDataEvent* evt2 = new System::TextDataEvent;
				evt2->m_offset = mutEvt->m_offset;
				evt2->m_len = mutEvt->m_len;
				evt2->InitEvent(WSTR("TextChanged"), false, false);
				dispatchEvent(evt2);
				
				return;
			}
			else if (*type == L"TextInserted")
			{
				evt->stopPropagation();

				LXmlEdit::MutationEvent* mutEvt = dynamic_cast<LXmlEdit::MutationEvent*>(evt);

				System::TextDataEvent* evt2 = new System::TextDataEvent;
				evt2->m_offset = mutEvt->m_offset;
				evt2->m_len = mutEvt->m_len;
				evt2->InitEvent(WSTR("TextInserted"), false, false);
				dispatchEvent(evt2);
				
				return;
			}
			else if (*type == L"TextDeleted")
			{
				evt->stopPropagation();

				LXmlEdit::MutationEvent* mutEvt = dynamic_cast<LXmlEdit::MutationEvent*>(evt);

				System::TextDataEvent* evt2 = new System::TextDataEvent;
				evt2->m_offset = mutEvt->m_offset;
				evt2->m_len = mutEvt->m_len;
				evt2->InitEvent(WSTR("TextDeleted"), false, false);
				dispatchEvent(evt2);
				
				return;
			}
		}
	}

	Control::handleEvent(evt);
}

//virtual
void CGridCharacterData::BuildXML(System::StringBuilderW& stream)
{
	Web::NodeType nodeType = m_domNode->get_nodeType();

	if (nodeType == Web::NODE_CDATA_SECTION)
	{
		stream << L"<![CDATA[";
		stream << *GetValue();
		stream << L"]]>";
	}
	else if (nodeType == Web::NODE_COMMENT)
	{
		stream << L"<!--";
		stream << *GetValue();
		stream << L"-->";
	}
	else
	{
		stream << *GetValue();
	}
}

// virtual
void CGridCharacterData::BuildXML(System::IO::ISequentialByteStream* stream)
{
	Web::NodeType nodeType = m_domNode->get_nodeType();

	ASSERT(sizeof(nodeType) == 4);
	stream->Write(&nodeType, 4);

	ASSERT(0);
#if 0
	CComBSTR((BSTR)GetValue()).WriteToStream(stream);
#endif
}

System::StringW* CGridCharacterData::GetValue()
{
	LXmlEdit::CharacterData* node = dynamic_cast<LXmlEdit::CharacterData*>(m_domNode);
	ASSERT(node);

	return node->get_data();
}

//virtual
void CGridCharacterData::OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree)
{
	ASSERT(0);
#if 0
	m_bEditChanged = TRUE;

	Size(hDC, 0);

	if (m_parent)
		m_parent->RecalculateParentSize(hDC);

	//m_pTree->Size(hDC, m_pTree->m_size.cx);

	::SetWindowPos(m_hWndEdit, NULL, 0, 0, m_size.cx+2, m_size.cy+2, SWP_NOMOVE);
#endif
}

#if 0
void CGridCharacterData::OnRender2(LDraw::Graphics* pGraphics)
{
	sysstring value = GetValue();
	pGraphics->DrawString(value.c_str(), value.length(), GetFont(), LDraw::RectF(0, 0, m_computedSize.Width, m_computedSize.Height), &LDraw::SolidBrush(LDraw::Color(0,0,0)));
}
#endif

#if 0
//virtual
void CGridCharacterData::CalculateBoundsAndChildren(LDraw::SizeD availSize)
{
	LDraw::Graphics graphics;
	sysstring value = GetValue();
	m_desiredSize.Width = graphics.MeasureString(value.c_str(), value.length(), GetFont());
	m_desiredSize.Height = GetFont()->GetSize();
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

	//int left = 0;

	//if (width < 2) width = 2;

	//if (width > 0)
	{
		CRect rc(0, 0, width, 0);
		ATLASSERT(rc.Width() >= 0);
		DrawText(hDC, value, value.length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

		m_size.cx = max(width, rc.Width()+2);
#if 0
		if (m_size.cx < 20) m_size.cx = 20;
#endif
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
#endif

//virtual
void CGridCharacterData::Draw(MSWindows::HDC hDC, bool bSelected)
{
	ASSERT(0);
#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	if (m_selected) bSelected = TRUE;

	sysstring value = GetValue();

	CRect trect(0, 0, m_size.cx, m_size.cy);

	FillSolidRect(hDC, 0, 0, m_size.cx, m_size.cy, bSelected? RGB(138, 200, 235): RGB(255, 255, 255));
	DrawTopLeft(hDC, &trect, RGB(200, 200, 200));

	trect.InflateRect(-1, -1);
	DrawText(hDC, value, value.length(), &trect, DT_EDITCONTROL | DT_WORDBREAK);
#endif
}

// virtual
int CGridCharacterData::HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal)
{
	ASSERT(0);
#if 0
	*pVal = NULL;

	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx && point.y < m_size.cy)
	{
		*pVal = this;
		return 1;
	}
#endif
	return 0;
}

//virtual
int CGridCharacterData::Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal)
{
	ASSERT(0);
#if 0
	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

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
void CGridCharacterData::EndEdit(/*CXMLGridCtl* pUI*/)
{
	ASSERT(0);
#if 0
	if (m_bEditChanged)
	{
		CComQIPtr<ILDOMCharacterData> node = m_domNode;
		ATLASSERT(node);

		ATLASSERT(m_hWndEdit);

		int len = ::GetWindowTextLength(m_hWndEdit);
		TCHAR* buf = new TCHAR[len+1];
		::GetWindowText(m_hWndEdit, buf, len+1);
		sysstring data = buf;
		delete buf;

		CComBSTR olddata;
		node->get_data(&olddata);

		if (wcscmp(data, olddata))
		{
			node->put_data(data);
		}

		m_bEditChanged = false;
	}

	m_pUI->m_wndEdit.DestroyWindow();
	m_hWndEdit = NULL;
#endif
}


}
