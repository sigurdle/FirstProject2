#include "stdafx.h"
#include "ASEditCtlsMod.h"
#include "ASGraphCtl.h"
#include "ASDesignElementDefinitionRoot.h"
#include "ASDesignContentModel.h"
#include "ASDesignAttribute.h"

extern COLORREF selectedColor;
//void DrawExpanded(HDC hDC, int x, int y, BOOL bExpanded);

#if 0
/////////////////////////////////////////////
// CDesignElementDefinitionRoot

// virtual
void CDTDDesignElementDefinitionRoot::BuildChildren()
{
	if (m_pDesignCM)
		m_pDesignCM->Build();
}

// virtual
IASContentModel* CDTDDesignElementDefinitionRoot::Get_asCM()
{
	return m_asDefinition->get_asCM();
}

// virtual
CDTDDesignDefinition* CDTDDesignElementDefinitionRoot::GetInsertion(LDraw::Point point, CDTDDesignDefinition* & pBefore)
{
	CPoint pt = point;
	pt.x -= m_pDesignCM->m_outerRect.left;
//	pt.y -= m_pDesignCM->m_outerRect.top;

	return m_pDesignCM->GetInsertion(pt, pBefore);
}

// virtual
void CDTDDesignElementDefinitionRoot::Build()
{
	ATLASSERT(m_asDefinition);

	BuildAttributes();

	CComQIPtr<IASContentModel> asCM;
	m_asDefinition->get_asCM(&asCM);

	if (asCM != NULL)
	{
		CComObject<CDTDDesignContentModel>::CreateInstance(&m_pDesignCM);
		m_pDesignCM->AddRef();
		m_pDesignCM->m_pCtl = m_pCtl;
		m_pDesignCM->m_asCM = asCM;
		m_pDesignCM->m_asObject = asCM;
		m_pDesignCM->m_pParent = this;
		m_pDesignCM->Setup();
	}
}

//virtual
void CDTDDesignElementDefinitionRoot::Size(HDC hDC)
{
	BSTR bname;
	m_asDefinition->get_nodeName(&bname);
	_bstr_t name = _bstr_t(bname, false);

	SIZE size;
	GetTextExtentPoint32(hDC, name, name.length(), &size);

	m_width = size.cx + 180;

	m_innerRect.SetRect(0, -100, m_width+100, 100+40);

	if (m_pDesignCM)
	{
		if (m_bExpanded)
		{
			m_pDesignCM->Size(hDC);
			m_pDesignCM->m_outerRect = m_pDesignCM->m_innerRect;
			m_pDesignCM->m_outerRect.OffsetRect(m_width+120, 0);

			CRect rc = m_innerRect;
			m_innerRect.UnionRect(&rc, &m_pDesignCM->m_outerRect);
		}
	}
}

//virtual
void CDTDDesignElementDefinitionRoot::DrawDesign(HDC hDC)
{
	ATLASSERT(m_width > 0);

	POINT oldOrg;
	OffsetWindowOrgEx(hDC, 0, m_innerRect.top, &oldOrg);

	if (TRUE)
	{
		if (m_bExpanded)
		{
			if (m_pDesignCM)
			{
				CRect rect = m_pDesignCM->m_outerRect;

				rect.left -= 40;
				CPen pen;
				pen.CreatePen(PS_DASH, 1, RGB(0,0,0));

				CBrush brush;
				brush.CreateSolidBrush(RGB(255, 255, 192));

				HPEN hOldPen = (HPEN)SelectObject(hDC, pen);
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, brush);

				Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

				SelectObject(hDC, hOldPen);
				SelectObject(hDC, hOldBrush);
			}
		}
	}

//	HPEN hPen;

	{ // Shadow
		HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
		HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 192));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		POINT oldOrg;
		OffsetWindowOrgEx(hDC, -40, -40, &oldOrg);

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

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	BSTR bname;
	m_asDefinition->get_nodeName(&bname);
	_bstr_t name = _bstr_t(bname, false);

	CRect trect(0, -100, m_width, 100);
	trect.InflateRect(1, 1);
	DrawText(hDC, name, name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	DrawAttributes(hDC);

	if (m_pDesignCM)
	{
		DrawExpanded(hDC, m_width, 0, m_bExpanded);

		if (m_bExpanded)
		{
			MoveToEx(hDC, m_width+60, 0, NULL);
			LineTo(hDC, m_width+120, 0);

			POINT oldOrg;
			OffsetWindowOrgEx(hDC, -m_pDesignCM->m_outerRect.left, -m_pDesignCM->m_outerRect.top, &oldOrg);

			m_pDesignCM->DrawDesign(hDC);

			SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}
	}

	SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
}

//virtual
CDTDDesignSchemaNode* CDTDDesignElementDefinitionRoot::OnClick(POINT point, BOOL bDblClk, bool& bSize)
{
	POINT pt = point;
	pt.y += m_innerRect.top;

	CRect r(0, -40, m_width, 40);
	CRect rexp(m_width-40, -40, m_width+40, 40);
	CRect raexp(0, -40, 80, 40);

	CRect rattrs(80, 100+40, 80+600, 100+40+m_attributes.GetSize()*(160+20));

	if (rexp.PtInRect(pt))
	{
		m_bExpanded = !m_bExpanded;

		if (m_bExpanded)
		{
			BuildChildren();
		}

		bSize = true;
		return this;
	}
	else if (raexp.PtInRect(pt))
	{
		m_bAttributesExpanded = !m_bAttributesExpanded;

		bSize = true;
		return this;
	}
	else if (r.PtInRect(pt))
	{
		m_bSelected = true;
		return this;
	}
	else if (m_bAttributesExpanded && rattrs.PtInRect(pt))
	{
		int index = (pt.y - 100+40)/(160+20);
		if (index >= 0 && index < m_attributes.GetSize())
		{
			return m_attributes[index];
		}
	}
	else
	{
		if (m_bExpanded)
		{
			if (m_pDesignCM)
			{
				POINT pt2 = pt;
				pt2.x -= m_pDesignCM->m_outerRect.left;
				pt2.y -= m_pDesignCM->m_outerRect.top;

				return m_pDesignCM->OnClick(pt2, bDblClk, bSize);
			}
		}
	}

	return NULL;
}

#endif