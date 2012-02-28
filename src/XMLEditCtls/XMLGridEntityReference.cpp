#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridNode.h"
#include "XMLGridEntityReference.h"

#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

////////////////////////////////////////////////////////////////////////
// CGridEntityReferenceReference

// virtual
void CGridEntityReference::BuildXML(System::IO::ISequentialByteStream* stream)
{
	Web::NodeType nodeType = m_domNode->get_nodeType();

	ASSERT(sizeof(nodeType) == 4);
	stream->Write(&nodeType, 4);

	ASSERT(0);
#if 0
	CComBSTR nodeName;
	m_domNode->get_nodeName(&nodeName);

	nodeName.WriteToStream(stream);
#endif
}

// virtual
void CGridEntityReference::Size(MSWindows::HDC hDC, int width)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMEntityReference> entityRef = m_domNode;

	{
		CComBSTR value;
		entityRef->get_nodeName(&value);

		if (width < 10) width = 10;

		CRect rc(0, 0, width-2, 0);
		ATLASSERT(rc.Width() >= 0);
		DrawText(hDC, _bstr_t(value), value.Length(), &rc, DT_CALCRECT | DT_EDITCONTROL | DT_WORDBREAK);

		m_size.cx = max(width, rc.Width());
		m_size.cy = rc.Height()+2;
	}

	m_size.cx += 80;
//	m_contentRect.OffsetRect(80, 0);
#endif
}

// virtual
void CGridEntityReference::Draw(MSWindows::HDC hDC, bool bSelected)
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	CComQIPtr<ILDOMEntityReference> entityRef = m_domNode;

	CRect rc(0, 0, m_size.cx, m_size.cy);

	CComBSTR name;
	entityRef->get_nodeName(&name);

//	CComBSTR value;
//	entityRef->get_value(&value);

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect namerect(0, 0, 80, m_size.cy);
	DrawText(hDC, W2A(name), name.Length(), &namerect, DT_SINGLELINE);
	DrawTopLeft(hDC, &namerect, RGB(200,200,200));

//	SelectObject(hDC, m_pUI->m_hFont[Font_Content]);

	/*
	CRect valuerect(80, 0, m_size.cx, m_size.cy);
	DrawText(hDC, W2A(value), value.Length(), &valuerect, DT_WORDBREAK | DT_EDITCONTROL);
	DrawTopLeft(hDC, &valuerect, RGB(200,200,200));
	*/
#endif
}

}
