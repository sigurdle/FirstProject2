#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"
#include "PParentBox.h"

namespace System
{
namespace Web
{

CHTMParentBox::CHTMParentBox()
{
	m_type = 1;

//	m_bAnynomous = FALSE;	// TODO remove
}

CHTMParentBox::~CHTMParentBox()
{
#if 0
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		CHTMBoxItem* pBox = m_children[i];

		pBox->m_parentBox = NULL;
		pBox->Release();
		/*
		if (pBox->m_type != 3 && pBox->m_type != 4)	// Don't delete words
		{
			delete pBox;
		}
		*/
	}
	m_children.RemoveAll();
#endif
	DeleteChildBoxes();
}

// virtual
void CHTMParentBox::Destroy()
{
	DeleteChildBoxes();
	CHTMBoxItem::Destroy();
}

void CHTMParentBox::AddChildBox(CHTMBoxItem* pBox)
{
	ASSERT(pBox != this);
	ASSERT(this != NULL);
	ASSERT(pBox != NULL);
	ASSERT(pBox->m_parentBox == NULL);
	pBox->m_parentBox = this;

	pBox->AddRef();	// We hold a reference to our child boxes
	m_children.Add(pBox);

// TODO
	m_renderChildren.Add(pBox);
}

void CHTMParentBox::RemoveChildBox(CHTMBoxItem* pBox)
{
	int i;

	for (i = m_renderChildren.GetSize()-1; i >= 0; i--)
	{
		CHTMBoxItem* p = m_renderChildren[i];

		if (p == pBox)
		{
		//	ASSERT(&m_renderChildren[i] >= m_renderChildren.begin() &&
		//		&m_renderChildren[i] < m_renderChildren.end());
		//	m_renderChildren.erase(&m_renderChildren[i]);
			m_renderChildren.RemoveAt(i);
		}
	}

	for (i = m_children.GetSize()-1; i >= 0; i--)
	{
		CHTMBoxItem* p = m_children[i];

		if (p == pBox)
		{
			p->SetParentNULL();
			m_children.RemoveAt(i);//&m_children[i]);
			p->Release();	// We hold reference on our child boxes
			return;
		}
	}

	ASSERT(0);
}

void CHTMParentBox::DeleteChildBoxes()
{
	m_renderChildren.RemoveAll();

	for (int i = m_children.GetSize()-1; i >= 0; i--)
	{
		CHTMBoxItem* p = m_children[i];

		ASSERT(p->m_parentBox == this);

		p->m_parentBox = NULL;

		p->Destroy();

		//int n = m_children.GetSize();
		p->Release();

		//ASSERT(n == m_children.GetSize());
		/*
		p->SetParentNULL();
		m_children.RemoveAt(i);
		p->Release();
		*/
	}

	m_children.RemoveAll();
	ASSERT(m_children.GetSize() == 0);
}

gm::RectF CHTMParentBox::GetAbsInnerRect()
{
	gm::RectF abspos = m_innerRect;
	abspos.Translate(m_outerRect.X, m_outerRect.Y);

	CHTMParentBox* pParent = m_parentBox;
	while (pParent)
	{
		abspos.Translate(pParent->m_outerRect.X, pParent->m_outerRect.Y);
		abspos.Translate(pParent->m_innerRect.X, pParent->m_innerRect.Y);

		pParent = pParent->m_parentBox;
	}

	return abspos;
}

void CHTMParentBox::DrawOutline(CHTMRenderContext* pC)
{
#if 0
	Gdiplus::RectF outerRect = m_outerRect;
	outerRect.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);

	pC->m_outerPos.X += m_outerRect.X;
	pC->m_outerPos.Y += m_outerRect.Y;

	if (m_pElement)
	{
		LDraw::GraphicsState hDCState = pC->m_pGraphics->Save();

		if (	(m_pElement->m_computedDisplay == Display_table) ||
				(m_pElement->m_computedDisplay == Display_inline_table))
		{
			{
				Gdiplus::RectF trect = GetAbsInnerRect();	// TODO
				trect.Inflate(-1, -1);
				pC->m_pGraphics->DrawRectangle(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0), 2), trect);
			}
		}
		else if (m_pElement->m_computedDisplay == Display_table_cell)
		{
			{
				Gdiplus::RectF trect = GetAbsInnerRect();	// TODO
				trect.Inflate(-3, -3);
				pC->m_pGraphics->DrawRectangle(&Gdiplus::Pen(Gdiplus::Color(255, 200, 0), 2), trect);
			}

			CHTMPElement* pRow = (CHTMPElement*)m_pElement->m_parent;
			while (pRow)
			{
				if (pRow->m_computedDisplay == Display_table_row)
				{
					break;
				}

				pRow = (CHTMPElement*)pRow->m_parent;
			}

			CHTMPElement* pTable = (CHTMPElement*)pRow->m_parent;
			while (pTable)
			{
				if (pTable->m_computedDisplay == Display_table ||
					pTable->m_computedDisplay == Display_inline_table)
				{
					break;
				}

				pTable = (CHTMPElement*)pTable->m_parent;
			}

			Gdiplus::RectF innerRect = GetAbsInnerRect();	// TODO

			Gdiplus::Font font(L"Arial", 10);

			/*
			WCHAR str_colspan[64];
			swprintf(str_colspan, L"colspan: %d", m_pElement->m_colspan);

			WCHAR str_rowspan[64];
			swprintf(str_rowspan, L"rowspan: %d", m_pElement->m_rowspan);

			pC->m_pGraphics->DrawString(str_colspan, wcslen(str_colspan), &font, Gdiplus::PointF(innerRect.X+6, innerRect.Y+6), &Gdiplus::SolidBrush(Gdiplus::Color(0,0,0)));
			pC->m_pGraphics->DrawString(str_rowspan, wcslen(str_rowspan), &font, Gdiplus::PointF(innerRect.X+6, innerRect.Y+24), &Gdiplus::SolidBrush(Gdiplus::Color(0,0,0)));
			*/

			WCHAR str_colindex[64];
			swprintf(str_colindex, L"%d,%d - %d,%d", m_pElement->m_columnIndex, m_pElement->m_nrow, m_pElement->m_colspan, m_pElement->m_rowspan);

			pC->m_pGraphics->DrawString(str_colindex, wcslen(str_colindex), &font, Gdiplus::PointF(innerRect.X+6, innerRect.Y+6), &Gdiplus::SolidBrush(Gdiplus::Color(255,0,0)));

			{
				WCHAR str[64];
				swprintf(str, L"colw: %g,%g,%g", pTable->m_tableColumns[m_pElement->m_columnIndex].m_minWidth, pTable->m_tableColumns[m_pElement->m_columnIndex].m_maxWidth, pTable->m_tableColumns[m_pElement->m_columnIndex].m_width);

				pC->m_pGraphics->DrawString(str, wcslen(str), &font, Gdiplus::PointF(innerRect.X+6, innerRect.Y+18), &Gdiplus::SolidBrush(Gdiplus::Color(255,0,0)));
			}

			/*
			Gdiplus::Rect rc;
			rc.Y = innerRect.Y;

			for (int y = 0; y < m_pElement->m_rowspan; y++)
			{
				rc.Height = pRow->m_height;
				rc.X = innerRect.X;

				for (int x = 0; x < m_pElement->m_colspan; x++)
				{
					rc.Width = pTable->m_tableColumns[m_pElement->m_columnIndex+x].m_width;

					Gdiplus::Rect rc2 = rc;
					rc2.Inflate(-6, -6);

					pC->m_pGraphics->DrawRectangle(&Gdiplus::Pen(Gdiplus::Color(0, 200, 255), 1), rc2);

					rc.X += rc.Width;
				}

				rc.Y += rc.Height;//pRow->m_height;

				pRow = (CHTMPElement*)pRow->GetNextNode();
			}
			*/
		}

		m_pElement->DoScroll(pC);

		pC->m_outerPos.X += m_innerRect.X;
		pC->m_outerPos.Y += m_innerRect.Y;

		for (int i = 0; i < m_children.GetSize(); i++)
		{
			CHTMBoxItem* pBox = m_children[i];
			if (pBox->m_type == 1)
			{
				((CHTMParentBox*)pBox)->DrawOutline(pC);
			}
		}

		pC->m_outerPos.X -= m_innerRect.X;
		pC->m_outerPos.Y -= m_innerRect.Y;

		pC->m_pGraphics->Restore(hDCState);
	}

	pC->m_outerPos.X -= m_outerRect.X;
	pC->m_outerPos.Y -= m_outerRect.Y;
#endif
}

}	// Web
}
