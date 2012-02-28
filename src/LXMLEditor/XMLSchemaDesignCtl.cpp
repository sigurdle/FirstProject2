#include "stdafx.h"
#include "LXMLEditor2.h"
#include "XMLSchemaDesignCtl.h"

#include "SchemaDiagramView.h"

namespace System
{
namespace LXmlEdit
{
#if 0
LRESULT CXMLSchemaDesignCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_asGraph.CoCreateInstance(CLSID_ASGraphCtl);

	m_asGraph->put_asModel(m_pSchema->m_asModel);

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axasGraph.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axasGraph.AttachControl(m_asGraph, &p);


/*

	CComQIPtr<IASNamedObjectMap> elementMap;
	m_pSchema->m_asModel->get_elementDeclarations(&elementMap);

	CComQIPtr<IASElementDeclaration> rootElement;
	elementMap->item(0, (IASObject**)&rootElement);

	m_asGraph->put_asRootObject(rootElement);
*/
	return 0;
}

LRESULT CXMLSchemaDesignCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CXMLSchemaDesignCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axasGraph.MoveWindow(0, 0, client.right, client.bottom, TRUE);
	return 0;
}
#endif

BEGIN_CMD_MAP(CXMLSchemaDesignCtl)
/*
	CMD_HANDLER(ID_VIEW_ZOOMOUT, OnViewZoomout)
	CMD_HANDLER(ID_VIEW_ZOOMIN, OnViewZoomin)
*/
END_CMD_MAP()

#if 0
#include "XMLSchema.h"

#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

static COLORREF selectedColor = RGB(160, 160, 240);

static void DrawExpanded(HDC hDC, int x, int y, BOOL bExpanded)
{
	CRect rect(x-60, y-60, x+60, y+60);

	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	if (bExpanded)
	{
		DrawText(hDC, "-", 1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		DrawText(hDC, "+", 1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

class CDesignDefinition;

class CDesignSchemaNode
{
public:
	CDesignSchemaNode()
	{
		m_pParent = NULL;

		m_bExpanded = false;
		m_bSelected = false;

		m_outerRect.SetRectEmpty();
		m_innerRect.SetRectEmpty();

		m_pNode = NULL;
	}


	CDesignSchemaNode* m_pParent;

	CSchemaNode* m_pNode;

	CRect m_innerRect;
	CRect m_outerRect;

	bool m_bExpanded;
	bool m_bSelected;

	virtual void DeselectAll()
	{
	}

	virtual void DrawDesign(HDC hDC)
	{
	}

	virtual CDesignSchemaNode* OnClick(POINT pt, bool& bSize)
	{
		bSize = false;
		return NULL;
	}

	virtual void OnSize(HDC hDC)
	{
	}

	virtual void Build(CSchemaNode* pNode)
	{
	}
};

class CDesignModelGroup : public CDesignSchemaNode
{
public:
	CArray<CDesignDefinition*,CDesignDefinition*> m_defs;

	virtual void DeselectAll();

	virtual void Build(CSchemaNode* pNode);
	virtual void DrawDesign(HDC hDC);
	virtual void OnSize(HDC hDC);
	virtual CDesignSchemaNode* OnClick(POINT pt, bool& bSize);
};

class CDesignDefinition : public CDesignSchemaNode
{
protected:
	CDesignModelGroup* m_pModelGroup;
	int m_width;

public:
	CDesignDefinition()
	{
		m_pModelGroup = NULL;
	}
};

class CDesignTypeDefinition : public CDesignDefinition
{
public:
};

class CDesignComplexTypeDefinition : public CDesignTypeDefinition
{
public:
	virtual void DrawDesign(HDC hDC);
	virtual CDesignSchemaNode* OnClick(POINT pt, bool& bSize);
	virtual void OnSize(HDC hDC);
	virtual void Build(CSchemaNode* pNode);
};

class CDesignGlobalElementDefinition : public CDesignDefinition
{
public:
	CDesignGlobalElementDefinition()
	{
		m_pTypeDefinition = NULL;
	}

	CDesignTypeDefinition* m_pTypeDefinition;

	virtual void DrawDesign(HDC hDC);
};

class CDesignElementDefinition : public CDesignTypeDefinition
{
public:
	virtual void Build(CSchemaNode* pNode);
	virtual void DrawDesign(HDC hDC);
	virtual void OnSize(HDC hDC);
	virtual CDesignSchemaNode* OnClick(POINT pt, bool& bSize);
};

////////////////////////////////////////////////
// CDesignModelGroup

// virtual
void CDesignModelGroup::DeselectAll()
{
	for (int i = 0; i < m_defs.GetSize(); i++)
	{
		m_defs[i]->m_bSelected = false;
	}
}

//virtual
void CDesignModelGroup::Build(CSchemaNode* pNode)
{
	m_pNode = pNode;

	CModelGroup* pModelGroup = (CModelGroup*)pNode;

	for (int i = 0; i < pModelGroup->m_defs.m_defs.GetSize(); i++)
	{
		CDefinition* pDef = pModelGroup->m_defs.m_defs[i];
		if (!wcscmp(pDef->GetDefType(), L"element"))
		{
			CDesignElementDefinition* pD = new CDesignElementDefinition;
			pD->Build(pDef);
			pD->m_pParent = this;
			m_defs.Add(pD);
		}
		else if (!wcscmp(pDef->GetDefType(), L"sequence") ||
					!wcscmp(pDef->GetDefType(), L"choice"))
		{
			CDesignModelGroup* pD = new CDesignModelGroup;
			pD->m_pParent = this;
			pD->Build(pDef);
		}
	}
}

//virtual
void CDesignModelGroup::OnSize(HDC hDC)
{
	m_innerRect.SetRect(0, -100, 300+60, 100+40);

	if (m_bExpanded)
	{
		if (m_defs.GetSize() == 1)
		{
			CDesignDefinition* pDef = m_defs[0];
			pDef->m_outerRect.OffsetRect(300+60+80+100, 0);
			m_innerRect.UnionRect(&m_innerRect, &pDef->m_outerRect);
		}
		else
		{
			int height = 0;

			for (int i = 0; i < m_defs.GetSize(); i++)
			{
				CDesignDefinition* pDef = m_defs[i];
				pDef->OnSize(hDC);
				pDef->m_outerRect = pDef->m_innerRect;

				height += pDef->m_innerRect.Height();
			}

			int y = -(height/2);

			for (i = 0; i < m_defs.GetSize(); i++)
			{
				CDesignDefinition* pDef = m_defs[i];

				y -= pDef->m_innerRect.top;

				pDef->m_outerRect.OffsetRect(300+60+80+100, y);
				m_innerRect.UnionRect(&m_innerRect, &pDef->m_outerRect);

				y += pDef->m_innerRect.bottom;
			}
		}
	}
}

//virtual
void CDesignModelGroup::DrawDesign(HDC hDC)
{
//	Rectangle(hDC, 0, 0, m_rect.Width(), m_rect.Height());

	POINT oldOrg;
	OffsetWindowOrgEx(hDC, 0, m_innerRect.top, &oldOrg);

	POINT pt[] =
	{
		40, -100,
		260, -100,
		300, -60,
		300, 60,
		260, 100,
		40, 100,
		00, 60,
		00, -60,
	};

	{ // Shadow
		HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
		HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 192));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		POINT oldOrg;
		OffsetWindowOrgEx(hDC, -40, -40, &oldOrg);

		Polygon(hDC, pt, 8);

		SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);

		DeleteObject(hBrush);
	}

	HBRUSH hBrush;
	if (m_bSelected)
		hBrush = CreateSolidBrush(selectedColor);
	else
		hBrush = CreateSolidBrush(RGB(255, 255, 255));

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Polygon(hDC, pt, 8);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	if (1)	// Sequence
	{
		MoveToEx(hDC, 20, 0, NULL);
		LineTo(hDC, 280, 0);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

		Rectangle(hDC, 150-20, -20, 150+20, 20);
		Rectangle(hDC, 100-20, -20, 100+20, 20);
		Rectangle(hDC, 200-20, -20, 200+20, 20);

		SelectObject(hDC, hOldBrush);
	}

	DrawExpanded(hDC, 300, 0, m_bExpanded);

	if (m_bExpanded)
	{
		int n = m_defs.GetSize();
		if (n)
		{
			MoveToEx(hDC, 300+60, 0, NULL);
			LineTo(hDC, 300+60+80, 0);

			MoveToEx(hDC, 300+60+80, m_defs[0]->m_outerRect.top - m_defs[0]->m_innerRect.top, NULL);
			LineTo(hDC, 300+60+80, m_defs[n-1]->m_outerRect.top - m_defs[n-1]->m_innerRect.top);

			for (int i = 0; i < m_defs.GetSize(); i++)
			{
				CDesignDefinition* pDef = m_defs[i];

				POINT oldOrg;
				OffsetWindowOrgEx(hDC, -pDef->m_outerRect.left, -pDef->m_outerRect.top, &oldOrg);

				MoveToEx(hDC, -100, -pDef->m_innerRect.top, NULL);
				LineTo(hDC, 0, -pDef->m_innerRect.top);

				pDef->DrawDesign(hDC);

				SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			}
		}
	}

	SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
}

//virtual
CDesignSchemaNode* CDesignModelGroup::OnClick(POINT point, bool& bSize)
{
	POINT pt = point;
	pt.y += m_innerRect.top;

	CRect r(0, -40, 300, 40);
	CRect rexp(300-40, -40, 300+40, 40);

	if (rexp.PtInRect(pt))
	{
		m_bExpanded = !m_bExpanded;
		bSize = true;
		return this;
	}
	else if (r.PtInRect(pt))
	{
		m_bSelected = true;
		return this;
	}
	else
	{
		if (m_bExpanded)
		{
			for (int i = 0; i < m_defs.GetSize(); i++)
			{
				CDesignDefinition* pDef = m_defs[i];

				POINT pt2 = pt;
				pt2.x -= pDef->m_outerRect.left;
				pt2.y -= pDef->m_outerRect.top;

				CDesignSchemaNode* p = pDef->OnClick(pt2, bSize);
				if (p)
					return p;
			}
		}
	}

	return NULL;
}

//////////////////////////////////////////
// CDesignComplexTypeDefinition

//virtual
void CDesignComplexTypeDefinition::Build(CSchemaNode* pNode)
{
	m_pNode = pNode;

	ATLASSERT(m_pModelGroup == NULL);

	CComplexTypeDefinition* pComDef = (CComplexTypeDefinition*)m_pNode;
	if (pComDef->m_pContent)
	{
		m_pModelGroup = new CDesignModelGroup;
		m_pModelGroup->m_pParent = this;

		CComplexContentType* pContent = (CComplexContentType*)pComDef->m_pContent;

		m_pModelGroup->Build(pContent->m_pModelGroup);
	}
}

// virtual
void CDesignComplexTypeDefinition::OnSize(HDC hDC)
{
	CComplexTypeDefinition* pNode = (CComplexTypeDefinition*)m_pNode;
	CComQIPtr<IDOMElement> element = pNode->m_element;

	BSTR bname;
	element->getAttribute(L"name", &bname);
	_bstr_t name = _bstr_t(bname, false);

	SIZE size;
	GetTextExtentPoint32(hDC, name, name.length(), &size);

	m_width = size.cx + 180;
	m_innerRect.SetRect(0, -100, m_width+60, 100+40);

	if (m_pModelGroup)
	{
		if (m_bExpanded)
		{
			m_pModelGroup->OnSize(hDC);
			m_pModelGroup->m_outerRect = m_pModelGroup->m_innerRect;
			m_pModelGroup->m_outerRect.OffsetRect(m_width+120, 0);

			m_innerRect.UnionRect(&m_innerRect, &m_pModelGroup->m_outerRect);
		}
	}
}

//virtual
void CDesignComplexTypeDefinition::DrawDesign(HDC hDC)
{
	CComplexTypeDefinition* pNode = (CComplexTypeDefinition*)m_pNode;
	CComQIPtr<IDOMElement> element = pNode->m_element;

	POINT oldOrg;
	OffsetWindowOrgEx(hDC, 0, m_innerRect.top, &oldOrg);

//	Rectangle(hDC, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	POINT pt[] =
	{
		40, -100,
		m_width, -100,
		m_width, 100,
		40, 100,
		0, 60,
		0, -60
	};

	{ // Shadow
		HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
		HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 192));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		POINT oldOrg;
		OffsetWindowOrgEx(hDC, -40, -40, &oldOrg);

		Polygon(hDC, pt, 6);

		SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);

		DeleteObject(hBrush);
	}

	HBRUSH hBrush;
	if (m_bSelected)
		hBrush = CreateSolidBrush(selectedColor);
	else
		hBrush = CreateSolidBrush(RGB(255, 255, 255));

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Polygon(hDC, pt, 6);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	BSTR bname;
	element->getAttribute(L"name", &bname);
	_bstr_t name = _bstr_t(bname, false);
	
	CRect trect(0, -100, m_width, 100);
	trect.InflateRect(1, 1);
	DrawText(hDC, name, name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (m_pModelGroup)
	{
		DrawExpanded(hDC, m_width, 0, m_bExpanded);

		if (m_bExpanded)
		{
			MoveToEx(hDC, m_width+60, 0, NULL);
			LineTo(hDC, m_width+120, 0);

			POINT oldOrg;
			OffsetWindowOrgEx(hDC, -m_pModelGroup->m_outerRect.left, -m_pModelGroup->m_outerRect.top, &oldOrg);

			m_pModelGroup->DrawDesign(hDC);

			SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}
	}

	SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
}

//virtual
CDesignSchemaNode* CDesignComplexTypeDefinition::OnClick(POINT point, bool& bSize)
{
	POINT pt = point;
	pt.y += m_innerRect.top;

	CRect r(0, -40, m_width+40, 40);
	CRect rexp(m_width-40, -40, m_width+40, 40);

	if (rexp.PtInRect(pt))
	{
		m_bExpanded = !m_bExpanded;
		bSize = true;
		return this;
	}
	else if (r.PtInRect(pt))
	{
		m_bSelected = true;
		return this;
	}
	else
	{
		if (m_bExpanded)
		{
			if (m_pModelGroup)
			{
				POINT pt2 = pt;
				pt2.x -= m_pModelGroup->m_outerRect.left;
				pt2.y -= m_pModelGroup->m_outerRect.top;

				return m_pModelGroup->OnClick(pt2, bSize);
			}
		}
	}

	return NULL;
}

/////////////////////////////////////////////
// CDesignElementDefinition

//virtual
void CDesignElementDefinition::Build(CSchemaNode* pNode)
{
	m_pNode = pNode;
	CElementDefinition* pElDef = (CElementDefinition*)m_pNode;
	CTypeDefinition* pDef = pElDef->GetTypeDefinition();
	if (pDef)
	{
		if (!wcscmp(pDef->GetDefType(), L"complexType"))
		{
			CComplexTypeDefinition* pComDef = (CComplexTypeDefinition*)pDef;
			if (pComDef->m_pContent)
			{
				m_pModelGroup = new CDesignModelGroup;
				m_pModelGroup->m_pParent = this;
				CComplexContentType* pContent = (CComplexContentType*)pComDef->m_pContent;

				m_pModelGroup->Build(pContent->m_pModelGroup);
			}
		}
	}
}

//virtual
void CDesignElementDefinition::OnSize(HDC hDC)
{
	CElementDefinition* pElDef = (CElementDefinition*)m_pNode;
	CComQIPtr<IDOMElement> element = m_pNode->m_element;

	_bstr_t name = pElDef->GetElementName();

	SIZE size;
	GetTextExtentPoint32(hDC, name, name.length(), &size);

	int minOccurs = pElDef->GetMinOccurs();
	int maxOccurs = pElDef->GetMaxOccurs();

	m_width = size.cx + 180;

	if (minOccurs == 0 && maxOccurs == 1)
	{
		m_innerRect.SetRect(0, -100, m_width+100, 100+40);
	}
	else if (minOccurs == 1 && maxOccurs == 1)
	{
		m_innerRect.SetRect(0, -100, m_width+100, 100+40);
	}
	else if (maxOccurs == -1 || maxOccurs > 1)
	{
		m_innerRect.SetRect(0, -100, 30+m_width+100, 30+100+40);
		m_innerRect.bottom += 120; // make room for "min...max"
	}

	if (m_pModelGroup)
	{
		if (m_bExpanded)
		{
			m_pModelGroup->OnSize(hDC);
			m_pModelGroup->m_outerRect = m_pModelGroup->m_innerRect;
			m_pModelGroup->m_outerRect.OffsetRect(m_width+120, 0);

			CRect rc = m_innerRect;
			m_innerRect.UnionRect(&rc, &m_pModelGroup->m_outerRect);
		}
	}
}

//virtual
void CDesignElementDefinition::DrawDesign(HDC hDC)
{
	CElementDefinition* pNode = (CElementDefinition*)m_pNode;

	CComQIPtr<IDOMElement> element = pNode->m_element;

//	Rectangle(hDC, 0, 0, m_rect.Width(), m_rect.Height());

	POINT oldOrg;
	OffsetWindowOrgEx(hDC, 0, m_innerRect.top, &oldOrg);

	int minOccurs = pNode->GetMinOccurs();
	DWORD maxOccurs = pNode->GetMaxOccurs();

	HPEN hPen;

	{ // Shadow
		HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
		HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 192));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		POINT oldOrg;
		OffsetWindowOrgEx(hDC, maxOccurs > 1? -70: -40, maxOccurs > 1? -70: -40, &oldOrg);

		Rectangle(hDC, 0, -100, m_width, 100);

		SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);

		DeleteObject(hBrush);
	}

	HBRUSH hBrush;
	if (m_bSelected)
		hBrush = CreateSolidBrush(selectedColor);
	else
		hBrush = CreateSolidBrush(RGB(255, 255, 255));

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	if (minOccurs == 0 && maxOccurs == 1)
	{
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

		Rectangle(hDC, 0, -100, m_width, 100);

		SelectObject(hDC, hOldPen);
		DeleteObject(hPen);
	}
	else if (minOccurs == 1 && maxOccurs == 1)
	{
		Rectangle(hDC, 0, -100, m_width, 100);
	}
	else if (maxOccurs > 1)
	{
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

		Rectangle(hDC, 30+0, 30+ -100, 30+m_width, 30+100);
		Rectangle(hDC, 0, -100, m_width, 100);

		SelectObject(hDC, hOldPen);
		DeleteObject(hPen);

	// write min/max occur
		
		HFONT hFont = CreateFont(120, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Symbol");
		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

		CUString smaxOccurs;
		if (maxOccurs == -1) smaxOccurs = "¥";	// infinity symbol
		else smaxOccurs.Format("%d", maxOccurs);

		CUString str;
		str.Format("%d¼%s", minOccurs, smaxOccurs);
		TextOut(hDC, 40, 150, str, str.GetLength());

		SelectObject(hDC, hOldFont);
		DeleteObject(hFont);
	}

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	if (pNode->IsRef())
	{
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

		POINT pt[] =
		{
			80, 20,
			80, 70,
			60, 50,
			30, 80,
			20, 70,
			50, 40,
			30, 20,
		};

		Polygon(hDC, pt, sizeof(pt)/sizeof(POINT));

		SelectObject(hDC, hOldBrush);
	}

	_bstr_t name = pNode->GetElementName();

	CRect trect(0, -100, m_width, 100);
	trect.InflateRect(1, 1);
	DrawText(hDC, name, name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (m_pModelGroup)
	{
		DrawExpanded(hDC, m_width, 0, m_bExpanded);

		if (m_bExpanded)
		{
			MoveToEx(hDC, m_width+60, 0, NULL);
			LineTo(hDC, m_width+120, 0);

			POINT oldOrg;
			OffsetWindowOrgEx(hDC, -m_pModelGroup->m_outerRect.left, -m_pModelGroup->m_outerRect.top, &oldOrg);

			m_pModelGroup->DrawDesign(hDC);

			SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}
	}

	SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
}

//virtual
CDesignSchemaNode* CDesignElementDefinition::OnClick(POINT point, bool& bSize)
{
	POINT pt = point;
	pt.y += m_innerRect.top;

	CRect r(0, -40, m_width, 40);
	CRect rexp(m_width-40, -40, m_width+40, 40);

	if (rexp.PtInRect(pt))
	{
		m_bExpanded = !m_bExpanded;
		bSize = true;
		return this;
	}
	else if (r.PtInRect(pt))
	{
		m_bSelected = true;
		return this;
	}
	else
	{
		if (m_bExpanded)
		{
			if (m_pModelGroup)
			{
				POINT pt2 = pt;
				pt2.x -= m_pModelGroup->m_outerRect.left;
				pt2.y -= m_pModelGroup->m_outerRect.top;

				return m_pModelGroup->OnClick(pt2, bSize);
			}
		}
	}

	return NULL;
}

///////////////////////////////////////
// CDesignGlobalElementDefinition

//virtual
void CDesignGlobalElementDefinition::DrawDesign(HDC hDC)
{
	CGlobalElementDefinition* pNode = (CGlobalElementDefinition*)m_pNode;
	CComQIPtr<IDOMElement> element = pNode->m_element;

/*
	int width = 80;

	m_innerRect = CRect(0, -10, width, 10);

	Rectangle(hDC, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	BSTR bname;
	element->getAttribute(L"name", &bname);
	_bstr_t name = _bstr_t(bname, false);
	DrawText(hDC, name, name.length(), &m_rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (m_pTypeDefinition)
	{
		POINT oldOrg;
		OffsetViewportOrgEx(hDC, width+4, 0, &oldOrg);

		m_pTypeDefinition->DrawDesign(hDC);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CXMLSchemaDesignCtl

long CXMLSchemaDesignCtl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = m_hWnd;
	ATLASSERT(IsWindow());

	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);
	ATLASSERT(hDC);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int state = SaveDC(hDC);

	Rectangle(hDC, m_areaRect.left-1, m_areaRect.top-1, m_areaRect.right+1, m_areaRect.bottom+1);

	if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
	{
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 10, 10, NULL);
		SetWindowOrgEx(hDC, 0, 0, NULL);
		SetViewportExtEx(hDC, 1*m_magnify, 1*m_magnify, NULL);
		SetViewportOrgEx(hDC, -scrollposX, -scrollposY, NULL);

		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

		if (m_pRoot)
		{
			POINT oldOrg;
			OffsetWindowOrgEx(hDC, -m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top, &oldOrg);

			m_pRoot->DrawDesign(hDC);

			SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}

		SelectObject(hDC, hOldFont);
	}

	RestoreDC(hDC, state);

	EndPaint(&ps);
	return 0;
}

long CXMLSchemaDesignCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_pRoot)
	{
		POINT pt = point;
		pt.x += scrollposX;
		pt.y += scrollposY;

		pt.x *= 10;
		pt.y *= 10;
		pt.x /= m_magnify;
		pt.y /= m_magnify;

		pt.x -= m_pRoot->m_outerRect.left;
		pt.y -= m_pRoot->m_outerRect.top;

		if (m_pActiveItem)
		{
			m_pActiveItem->m_bSelected = false;
			if (m_pActiveItem->m_pParent)
				m_pActiveItem->m_pParent->DeselectAll();
		}

		bool bSize = false;
		CDesignSchemaNode* pNode = m_pRoot->OnClick(pt, bSize);

		if (pNode)
		{
			if (bSize)
			{
				HDC hDC = CreateCompatibleDC(NULL);
				SetMapMode(hDC, MM_ANISOTROPIC);
				SetWindowExtEx(hDC, 10, 10, NULL);
				SetViewportExtEx(hDC, 1, 1, NULL);
				HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

				m_pRoot->OnSize(hDC);
				m_pRoot->m_outerRect = m_pRoot->m_innerRect;

				SelectObject(hDC, hOldFont);
				DeleteDC(hDC);

				OnSize();
			}
			else
			{
				m_pActiveItem = pNode;

#if 0
				HGLOBAL hData = BuildSelectedFilesClipboard();
				if (hData)
				{
					CMyDropSource*  dropSource = new CMyDropSource;
					CMyDataObject* dataObject = new CMyDataObject;

					STGMEDIUM	stg = {0};
					stg.tymed = TYMED_HGLOBAL;
					stg.hGlobal = hData;
					stg.pUnkForRelease = NULL;
					
					FORMATETC	etc = {0};
					etc.cfFormat = CF_HDROP;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
					etc.tymed = TYMED_HGLOBAL;
					etc.ptd = NULL;
					etc.dwAspect = DVASPECT_CONTENT;
					etc.lindex = -1;

					dataObject->SetData(&etc, &stg, TRUE);

					DWORD dropEffect = 0;
					HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

					if (hr == DRAGDROP_S_DROP)
					{
						if (dropEffect/* & DROPEFFECT_MOVE*/)
						{
						}
					}

					GlobalFree(hData);
				}
#endif
			}

			Invalidate();
		}
	}

	return 0;
}

long CXMLSchemaDesignCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_hFont = CreateFont(140, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Arial");

	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);

	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	return 0;
}

LRESULT CXMLSchemaDesignCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}

	return 0;
}

long CXMLSchemaDesignCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(&m_areaRect);

	return 0;
}

void CXMLSchemaDesignCtl::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int cx = client.Width();
	int cy = client.Height();

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	m_areaRect.SetRect(1, 1, cx-sbWidth-1, cy-sbHeight-1);

	if (m_pRoot)
	{
		m_axvert.MoveWindow(cx-sbWidth, 0, sbWidth, cy-sbHeight, TRUE);
		m_axhorz.MoveWindow(0, cy-sbHeight, cx-sbWidth, sbHeight, TRUE);

		int left = m_pRoot->m_outerRect.left*m_magnify/10;
		int right = m_pRoot->m_outerRect.right*m_magnify/10;

		int top = m_pRoot->m_outerRect.top*m_magnify/10;
		int bottom = m_pRoot->m_outerRect.bottom*m_magnify/10;

		int width = right-left;
		int height = bottom-top;

		if (m_areaRect.Height() > height)
		{
			m_vert->SetInfo(
				(top -(m_areaRect.Height()-height)/2),
				(top -(m_areaRect.Height()-height)/2),
				m_areaRect.Height());
		}
		else
		{
			m_vert->SetInfo(
				top,
				bottom,
				m_areaRect.Height());
		}

		if (m_areaRect.Width() > width)
		{
			m_horz->SetInfo(
				(left -(m_areaRect.Width()-width)/2),
				(left -(m_areaRect.Width()-width)/2),
				m_areaRect.Width());
		}
		else
		{
			m_horz->SetInfo(
				left,
				right,
				m_areaRect.Width());
		}
	}
}

HRESULT __stdcall CXMLSchemaDesignCtl::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	CRect rect = m_areaRect;

	m_horz->put_pos(pos);
	ScrollWindow(oldPos-pos, 0, &rect, &rect);

	return S_OK;
}

HRESULT __stdcall CXMLSchemaDesignCtl::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect rect = m_areaRect;

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);

	return S_OK;
}

STDMETHODIMP CXMLSchemaDesignCtl::get_rootNode(IDOMNode **pVal)
{
	*pVal = m_rootNode;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CXMLSchemaDesignCtl::put_rootNode(IDOMNode *newVal)
{
	m_rootNode = newVal;
	for (int i = 0; i < m_pSchema->m_globalDefs.m_defs.GetSize(); i++)
	{
		if (m_pSchema->m_globalDefs.m_defs[i]->m_element == m_rootNode)
		{
			BSTR btagName;
			m_pSchema->m_globalDefs.m_defs[i]->m_element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"element"))
			{
				m_pRoot = new CDesignGlobalElementDefinition;
			}
			else if (!wcscmp(tagName, L"complexType"))
			{
				m_pRoot = new CDesignComplexTypeDefinition;
			}

			HDC hDC = CreateCompatibleDC(NULL);
			SetMapMode(hDC, MM_ANISOTROPIC);
			SetWindowExtEx(hDC, 10, 10, NULL);
			SetViewportExtEx(hDC, 1, 1, NULL);
			HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

			m_pRoot->Build((CDefinition*)m_pSchema->m_globalDefs.m_defs[i]);
			m_pRoot->OnSize(hDC);
			m_pRoot->m_outerRect = m_pRoot->m_innerRect;

			OnSize();

			SelectObject(hDC, hOldFont);
			DeleteDC(hDC);
			break;
		}
	}

	Invalidate();

	return S_OK;
}

LRESULT CXMLSchemaDesignCtl::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CComQIPtr<IUIManager> uiManager = gApp->m_frame;
#if 0
	CComQIPtr<IMenuItem> menu;
	uiManager->FindMenu(ID_SCHEMADESIGN, &menu);
	if (menu)
	{
		long selectedID;
		menu->PopupMenu(this, point, 0, &selectedID);
	}
#endif

	return 0;
}

void CXMLSchemaDesignCtl::OnViewZoomout(long iid)
{
	m_magnify /= 2;
	OnSize();
	InvalidateRect(&m_areaRect);
}

void CXMLSchemaDesignCtl::OnViewZoomin(long iid)
{
	m_magnify *= 2;
	OnSize();
	InvalidateRect(&m_areaRect);
}

#endif
}
}

