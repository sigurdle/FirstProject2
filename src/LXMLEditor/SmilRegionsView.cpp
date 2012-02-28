// SmilRegionsView.cpp : Implementation of CSmilRegionsView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SmilRegionsView.h"

//IMPORTEXPORT ILDOMElement* GetElementByTagName(ILDOMNode* parentNode, BSTR tagName, BOOL bDeep = TRUE);
//IMPORTEXPORT ILDOMElement* GetElementByTagNameNS(ILDOMNode* parentNode, BSTR ns, BSTR tagName, BOOL bDeep = TRUE);

//#include "Element.h"

//ILDOMElement* FindByTagName(ILDOMNode* parent, BSTR tagName, BOOL bDeep = TRUE);

namespace System
{
namespace LXmlEdit
{

#if 0
class CSmilRegion : public CElement
{
public:
	int m_left;
	int m_top;
	int m_width;
	int m_height;

	CSmilRegion(ILDOMNode* domElement);

	void OnUpdate(ILDOMEvent* evt);
};

class CSmilLayout : public CElement
{
public:
	CSmilLayout(ILDOMNode* domElement) : CElement(domElement)
	{
	}

	void BuildRegions();
};

void CSmilLayout::BuildRegions()
{
	ATLASSERT(0);
#if 0
	CComQIPtr<ILDOMElement> element = m_domElement;

	CComQIPtr<ILDOMNode> child;
	element->get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);
		if (nodeType == NODE_ELEMENT)
		{
			BSTR btagName;
			child->get_nodeName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"region"))
			{
				CSmilRegion* pRegion = new CSmilRegion(child);
				AddChildTail(pRegion);
			}
		}

		CComQIPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif
}

CSmilRegion::CSmilRegion(ILDOMNode* domElement) : CElement(domElement)
{
	m_left = m_top = m_width = m_height = 0;

	CComQIPtr<ILDOMElement> element = domElement;

	BSTR bvalue;
	_bstr_t value;

	element->getAttribute(L"left", &bvalue);
	value = _bstr_t(bvalue, false);
	if (value.length() > 0) m_left = atof(value);

	element->getAttribute(L"top", &bvalue);
	value = _bstr_t(bvalue, false);
	if (value.length() > 0) m_top = atof(value);

	element->getAttribute(L"width", &bvalue);
	value = _bstr_t(bvalue, false);
	if (value.length() > 0) m_width = atof(value);

	element->getAttribute(L"height", &bvalue);
	value = _bstr_t(bvalue, false);
	if (value.length() > 0) m_height = atof(value);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmilRegionsView

long CSmilRegionsView::OnCreate()
{
	ASSERT(0);
#if 0
	CComPtr<IEXMLDocument> edocument;
	m_viewGroup->get_eXMLDocument(&edocument);

	CComPtr<ILDOMDocument> domdocument;
	edocument->get_DOMDocument(&domdocument);

	CComPtr<ILDOMElement> documentElement;
	domdocument->get_documentElement(&documentElement);

	CComPtr<ILDOMElement> head = GetElementByTagName(documentElement, L"head", FALSE);
	if (head)
	{
		CComPtr<ILDOMElement> layout = GetElementByTagName(head, L"layout", FALSE);
		if (layout)
		{
			m_layoutElement = GetElementByTagName(layout, L"root-layout", FALSE);
		}
	}

#if 0
	delete m_layout;
	m_layout = NULL;

	CComPtr<ILDOMDocument> document;
	m_document->get_DOMDocument(&document);

	CComQIPtr<ILSMILDocument> smilDocument = document;

	if (smilDocument)
	{
		CComQIPtr<ILDOMElement> documentElement;
		smilDocument->get_documentElement(&documentElement);

		if (documentElement)
		{
			ILDOMElement* head = FindByTagName(documentElement, L"head", FALSE);
			if (head)
			{
				ILDOMElement* layout = FindByTagName(head, L"layout", FALSE);
				if (layout)
				{
					m_layout = new CSmilLayout(layout);
					m_layout->BuildRegions();
				}
			}
		}
	}
#endif
#endif
	return 0;
}

void DrawRegionElements(MSWindows::HDC hDC, Web::Element* parentElement)
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMNode> node;
	parentElement->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILSMILRegionElement> region = node;
		if (region)
		{
			CComQIPtr<ILSMILElementLayout> layout = region;

			CComBSTR bstrwidth;
			region->getAttribute(L"width", &bstrwidth);

			CComBSTR bstrheight;
			region->getAttribute(L"height", &bstrheight);

			CComBSTR bstrleft;
			region->getAttribute(L"left", &bstrleft);

			CComBSTR bstrtop;
			region->getAttribute(L"top", &bstrtop);

			long left = _variant_t(bstrleft);
			long top = _variant_t(bstrtop);
			long width = _variant_t(bstrwidth);
			long height = _variant_t(bstrheight);

			Draw3DRect(hDC, left, top, width, height, 0, 0);

			DrawRegionElements(hDC, region);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}

void DrawLayoutElement(MSWindows::HDC hDC, Web::Element* element)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSMILElementLayout> layout = element;

	long width;
	layout->get_width(&width);

	long height;
	layout->get_height(&height);

	long x = 0;
	long y = 0;

	Draw3DRect(hDC, x, y, width, height, 0, 0);

	CComPtr<ILDOMNode> parentNode;
	element->get_parentNode(&parentNode);
	CComQIPtr<ILDOMElement> parentElement = parentNode;

	/*
	CComPtr<ILDOMNode> node;
	parentElement->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILSMILRegionElement> region = node;
		if (region)
		{
			DrawRegionElement(hDC
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
*/
	DrawRegionElements(hDC, parentElement);
#endif
}

#if 0
long CSmilRegionsView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	long scrollposX = 0;
	long scrollposY = 0;

	if (m_layoutElement)
	{
		DrawLayoutElement(dc.m_hDC, m_layoutElement);
		/*
		POINT oldOrg;
		SetViewportOrgEx(hDC, -scrollposX, -scrollposY, &oldOrg);
		UPOSITION pos = m_layout->m_childList.GetHeadPosition();
		while (pos)
		{
			CSmilRegion* pRegion = (CSmilRegion*)m_layout->m_childList.GetNext(pos);

			int left = pRegion->m_left;
			int top = pRegion->m_top;
			int width = pRegion->m_width;
			int height = pRegion->m_height;
			int right = left + width;
			int bottom = top + height;

			Rectangle(hDC, left, top, right, bottom);

			FillSolidRect(hDC, left, top, 8, 8, RGB(0,0,0));
			FillSolidRect(hDC, left+width/2-4, top, 8, 8, RGB(0,0,0));
			FillSolidRect(hDC, right-8, top, 8, 8, RGB(0,0,0));

			FillSolidRect(hDC, left, bottom-8, 8, 8, RGB(0,0,0));
			FillSolidRect(hDC, left+width/2-4, bottom-8, 8, 8, RGB(0,0,0));
			FillSolidRect(hDC, right-8, bottom-8, 8, 8, RGB(0,0,0));

			FillSolidRect(hDC, left, top+height/2-4, 8, 8, RGB(0,0,0));
			FillSolidRect(hDC, right-8, top+height/2-4, 8, 8, RGB(0,0,0));
		}

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		*/
	}

	return 0;
}
#endif

long CSmilRegionsView::OnLButtonDown()
{
#if 0
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX = 0;
	long scrollposY = 0;

	if (!m_dragging)
	{
		POINT pt = point;
		pt.x += scrollposX;
		pt.y += scrollposY;

		m_sizeing = 0;
		m_pActiveRegion = NULL;

		UPOSITION pos = m_layout->m_childList.GetHeadPosition();
		while (pos)
		{
			CSmilRegion* pRegion = (CSmilRegion*)m_layout->m_childList.GetNext(pos);

			int left = pRegion->m_left;
			int top = pRegion->m_top;
			int right = pRegion->m_left + pRegion->m_width;
			int bottom = pRegion->m_top + pRegion->m_height;

			if (pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom)
			{
				if (pt.x < left+8)
				{
					if (pt.y < top+8) m_sizeing = 2;
					else if (pt.y > bottom-8) m_sizeing = 3;
					else
						m_sizeing = 4;
				}
				else if (pt.x > right-8)
				{
					if (pt.y < top+8) m_sizeing = 5;
					else if (pt.y > bottom-8) m_sizeing = 6;
					else
						m_sizeing = 7;
				}
				else if (pt.y < top+8)
				{
					m_sizeing = 8;
				}
				else if (pt.y > bottom-8)
				{
					m_sizeing = 9;
				}
				else
				{
					m_sizeing = 1;	// Inside
				}

				if (m_sizeing)
				{
					m_pActiveRegion = pRegion;
					break;
				}
			}
		}

		if (m_sizeing)
		{
			m_dragging = 1;

			m_oldpt = pt;
			SetCapture();
		}
	}
#endif
	return 0;
}

#if 0
long CSmilRegionsView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}
#endif

long CSmilRegionsView::OnMouseMove()
{
#if 0
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX = 0;
	long scrollposY = 0;

	if (m_dragging)
	{
		POINT pt = point;
		pt.x += scrollposX;
		pt.y += scrollposY;

		int dx = pt.x - m_oldpt.x;
		int dy = pt.y - m_oldpt.y;

		int left = m_pActiveRegion->m_left;
		int top = m_pActiveRegion->m_top;
		int right = m_pActiveRegion->m_left + m_pActiveRegion->m_width;
		int bottom = m_pActiveRegion->m_top + m_pActiveRegion->m_height;

		if (m_sizeing == 1)
		{
			left += dx;
			top += dy;
			right += dx;
			bottom += dy;
		}
		else if (m_sizeing == 2)
		{
			left += dx;
			top += dy;
		}
		else if (m_sizeing == 3)
		{
			left += dx;
			bottom += dy;
		}
		else if (m_sizeing == 4)
		{
			left += dx;
		}
		else if (m_sizeing == 5)
		{
			right += dx;
			top += dy;
		}
		else if (m_sizeing == 6)
		{
			right += dx;
			bottom += dy;
		}
		else if (m_sizeing == 7)
		{
			right += dx;
		}
		else if (m_sizeing == 8)
		{
			top += dy;
		}
		else if (m_sizeing == 9)
		{
			bottom += dy;
		}

		m_oldpt = pt;

		TCHAR str[64];

		CComQIPtr<ILDOMElement> element = m_pActiveRegion->m_domElement;

		sprintf(str, "%d", left);
		element->setAttribute(L"left", _bstr_t(str));

		sprintf(str, "%d", top);
		element->setAttribute(L"top", _bstr_t(str));

		sprintf(str, "%d", right-left);
		element->setAttribute(L"width", _bstr_t(str));

		sprintf(str, "%d", bottom-top);
		element->setAttribute(L"height", _bstr_t(str));
	}
#endif
	return 0;
}

ErrorCode CSmilRegionsView::get_document(CEXMLDocument **pVal)
{
	*pVal = m_document;
	return Success;
}

ErrorCode CSmilRegionsView::set_document(CEXMLDocument *newVal)
{
	m_document = newVal;
	return Success;
}

}	// LXmlEdit
}
