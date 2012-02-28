#include "stdafx.h"
#include "ASEditCtlsMod.h"
#include "ASDesignContentModel.h"
#include "ASGraphCtl.h"

extern COLORREF selectedColor;
//void DrawExpanded(LDraw::Graphics* pGraphics, int x, int y, BOOL bExpanded);

//////////////////////////////////////////////////////////////////////////
// CDTDDesignContentModel

void CDTDDesignContentModel::DrawExpanded(LDraw::Graphics* pGraphics, int x, int y, BOOL bExpanded)
{
	LDraw::BBox rect(x-6, y-6, x+6, y+6);

	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255,255,255)), rect.left, rect.top, rect.Width(), rect.Height());
	pGraphics->DrawRectangle(&LDraw::Pen(LDraw::Color(0,0,0)), rect.left, rect.top, rect.Width(), rect.Height());
	if (bExpanded)
	{
		pGraphics->DrawString("-", 1, GetFont(), LDraw::PointF(rect.left, rect.top), &LDraw::SolidBrush(LDraw::Color(0,0,0)));
	}
	else
	{
		pGraphics->DrawString("+", 1, GetFont(), LDraw::PointF(rect.left, rect.top), &LDraw::SolidBrush(LDraw::Color(0,0,0)));
//		DrawText(hDC, "+", 1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

// virtual
void CDTDDesignContentModel::EndEdit()
{
	ATLASSERT(0);

#if 0
	if (m_bEditChanged)
	{
	//	CComQIPtr<ILDOMAttr> node = m_domElement;
	//	ATLASSERT(node);

		ATLASSERT(::IsWindow(m_hWndEdit));

		int len = ::GetWindowTextLength(m_hWndEdit);
		TCHAR* buf = new TCHAR[len+1];

		::GetWindowText(m_hWndEdit, buf, len+1);

		m_asElement->put_nodeName(_bstr_t(buf));

		delete buf;

		m_bEditChanged = false;
	}

	ATLASSERT(0);
#if 0
	m_pCtl->m_wndEdit.DestroyWindow();
	m_hWndEdit = NULL;
#endif
#endif
}

void CDTDDesignContentModel::Setup()
{
#if 0
	ATLASSERT(0);
	CComPtr<IUnknown> p;
	m_asObject->setUserData(m_pCtl->m_key, GetUnknown(), this, &p);
#endif
}

void CDTDDesignContentModel::Build()
{
//	ASContentModelTypeOp op;
//	m_asCM->get_listOperator(&op);

	BuildAttributes();

	if (m_asElement != NULL/*op == AS_NONE*/)
	{
		ATLASSERT(m_pDesignCM == NULL);
		ATLASSERT(m_asElement);

#if 0
		IASDataTypeDeclaration* dataType = m_asElement->get_elementDataType();
#endif
		/*
		if (dataType)
		{
			return dataType->get_asCM(pVal);
		}
		*/

		IASContentModel* asCM = m_asElement->get_asCM();

		if (asCM != NULL)
		{
			m_pDesignCM = new CDTDDesignContentModel;

			m_pDesignCM->m_pCtl = m_pCtl;
			m_pDesignCM->m_asObject = asCM;
			m_pDesignCM->m_asCM = asCM;
			m_pDesignCM->m_pParent = this;
			m_pDesignCM->Setup();

			AddRChild(m_pDesignCM);
			m_pDesignCM->SetOwnerWindow(get_OwnerWindow());
		}
	}
	else
	{
		ATLASSERT(m_defs.GetSize() == 0);
	//	m_asCM = dynamic_cast<IASDeclaration*>(m_asObject)->get_asCM();
		ATLASSERT(m_asCM);

		IASObjectList* subModels = m_asCM->get_subModels();

		long nsubModels = subModels->get_length();

		for (long i = 0; i < nsubModels; i++)
		{
			IASObject* subObject = subModels->item(i);

			_ASObjectType type = subObject->get_asNodeType();

			if (type == AS_ELEMENT_DECLARATION)	// element
			{
				IASElementDeclaration* asElement = dynamic_cast<IASElementDeclaration*>(subObject);
				/*
				CDTDDesignElementDefinition* pD = new CDTDDesignElementDefinition;
				pD->m_pParent = this;
				pD->m_asElement = asElement;
				m_defs.Add(pD);
				*/

				//CComQIPtr<IASContentModel> asCM = subObject;
				CDTDDesignContentModel* pD = new CDTDDesignContentModel;

				pD->m_pCtl = m_pCtl;
				pD->m_asObject = subObject;
				pD->m_pParent = this;
				pD->m_asCM = NULL;//m_asCM;
				pD->m_asElement = asElement;
				pD->Setup();
				m_defs.Add(pD);
				AddRChild(pD);
				pD->SetOwnerWindow(get_OwnerWindow());
			}
			else if (type == AS_CONTENTMODEL)	// choice|seq|all
			{
				IASContentModel* asCM = dynamic_cast<IASContentModel*>(subObject);

				_ASContentModelTypeOp op = asCM->get_listOperator();
				if (op == AS_NONE)
				{
					IASObjectList* ssubModels = asCM->get_subModels();

					IASObject* ssubObject = ssubModels->item(0);
					IASElementDeclaration* asElement = dynamic_cast<IASElementDeclaration*>(ssubObject);

					CDTDDesignContentModel* pD = new CDTDDesignContentModel;

					pD->m_pCtl = m_pCtl;
					pD->m_asObject = subObject;	// ??
					pD->m_pParent = this;
					pD->m_asCM = asCM;
					pD->m_asElement = asElement;
					pD->Setup();
					m_defs.Add(pD);
					AddRChild(pD);
					pD->SetOwnerWindow(get_OwnerWindow());
				}
				else
				{
					CDTDDesignContentModel* pD = new CDTDDesignContentModel;
					pD->m_pCtl = m_pCtl;
					pD->m_asObject = subObject;
					pD->m_pParent = this;
					pD->m_asCM = asCM;
					pD->Setup();
					m_defs.Add(pD);
					AddRChild(pD);
					pD->SetOwnerWindow(get_OwnerWindow());
				}
			}
			else
				ATLASSERT(0);
		}

		if (false)	// Empty definition for the sake of appending
		{
			CASDesignEmptyObject* pD = new CASDesignEmptyObject;
			pD->m_pCtl = m_pCtl;
			pD->m_pParent = this;
			m_defs.Add(pD);
			AddRChild(pD);
			pD->SetOwnerWindow(get_OwnerWindow());
		}
	}
}

void CDTDDesignContentModel::CalculateBoundsAndChildren(LDraw::SizeD)
{
//	ASContentModelTypeOp op;
//	m_asCM->get_listOperator(&op);

	long minOccurs = 1;
	long maxOccurs = 1;

	if (m_asCM)
	{
		minOccurs = m_asCM->get_minOccurs();
		maxOccurs = m_asCM->get_maxOccurs();
	}

	if (m_asElement != NULL)
	{
		sysstring name = m_asElement->get_nodeName();

		LDraw::Graphics graphics;
	//	SIZE size;
	//	GetTextExtentPoint32(hDC, name, name.length(), &size);
		LDraw::SizeD size;
		size.Width = graphics.MeasureString(name.c_str(), name.length(), GetFont());

		m_width = size.Width + 18;

		if ((unsigned long)maxOccurs <= 1)
		{
			m_innerRect.SetRect(0, -10, m_width+10, 10+4);
		}
		else
		{
			m_innerRect.SetRect(0, -10, 3+m_width+10, 3+10+4);
			m_innerRect.bottom += 13; // make room for "min...max"
		}

		if (m_bAttributesExpanded)
		{
			m_innerRect.InflateRect(0, 0, 0, m_attributes.GetSize()*(16+2));

			m_width = max(m_width, 8+60);
		}

		if (m_pDesignCM)
		{
			if (m_bExpanded)
			{
				m_pDesignCM->Measure(LDraw::SizeD(0,0));//Size(hDC);

				m_pDesignCM->m_outerRect = m_pDesignCM->m_innerRect;
				m_pDesignCM->m_outerRect.OffsetRect(m_width+12, 0);

#if 0
				m_pDesignCM->m_outerRect.InflateRect(0, 20, 0, 0);	// ??
#endif
				LDraw::BBox rc = m_innerRect;
				m_innerRect.UnionRect(&rc, &m_pDesignCM->m_outerRect);

			}
		}

		ATLASSERT(m_width > 0);
	}
	else
	{
		m_width = 36;//+80;

		if ((unsigned long)maxOccurs <= 1)
		{
			m_innerRect.SetRect(0, -10, 36+8, 10+4);
		}
		else
		{
			m_innerRect.SetRect(0, -10, 36+8, 3+10+4);
			m_innerRect.bottom += 13; // make room for "min...max"
		}

		//m_innerRect.top -= 200;

		if (m_bExpanded)
		{
			double height = 0;

			for (int i = 0; i < m_defs.GetSize(); i++)
			{
				CDTDDesignDefinition* pDef = m_defs[i];
				pDef->Measure(LDraw::SizeD(0,0));
				pDef->m_outerRect = pDef->m_innerRect;

				height += pDef->m_innerRect.Height();
			}

			height += 4*(m_defs.GetSize()-1);	// Have some space between

			if (m_defs.GetSize() == 1)
			{
				CDTDDesignDefinition* pDef = m_defs[0];
				pDef->m_outerRect.OffsetRect(36+8+8+10, 0);
				m_innerRect.UnionRect(&m_innerRect, &pDef->m_outerRect);
			}
			else
			{
				double y = -(height/2);

				for (i = 0; i < m_defs.GetSize(); i++)
				{
					CDTDDesignDefinition* pDef = m_defs[i];

					y -= pDef->m_innerRect.top;

					pDef->m_outerRect.OffsetRect(36+8+8+10, y);
					m_innerRect.UnionRect(&m_innerRect, &pDef->m_outerRect);
					y += pDef->m_innerRect.bottom;

					y += 4;
				}
			}
		}
	}

	m_desiredSize.Width = m_innerRect.Width();
	m_desiredSize.Height = m_innerRect.Height();
}

void CDTDDesignContentModel::OnArrange(LDraw::SizeD finalSize)
{
	if (m_pDesignCM)
	{
		m_pDesignCM->Arrange(m_pDesignCM->m_desiredSize);
		m_pDesignCM->SetLayoutOffset(m_pDesignCM->m_outerRect.left - m_innerRect.left, m_pDesignCM->m_outerRect.top - m_innerRect.top);
	}
	else
	{
		for (int i = 0; i < m_defs.GetSize(); i++)
		{
			CDTDDesignDefinition* def = m_defs[i];

			def->Arrange(def->m_desiredSize);
			def->SetLayoutOffset(def->m_outerRect.left - def->m_innerRect.left, def->m_outerRect.top - def->m_innerRect.top);
		}
	}

	m_expandedBBox.X = m_innerRect.left;
	m_expandedBBox.Y = m_innerRect.top;
	m_expandedBBox.Width = m_innerRect.Width();
	m_expandedBBox.Height = m_innerRect.Height();
}

//virtual
void CDTDDesignContentModel::OnRender3(LDraw::Graphics* pGraphics)
{
//	Rectangle(hDC, 0, 0, m_rect.Width(), m_rect.Height());

//	ASContentModelTypeOp op;
//	m_asCM->get_listOperator(&op);

	long minOccurs = 1;
	long maxOccurs = 1;

	if (m_asCM)
	{
		minOccurs = m_asCM->get_minOccurs();
		maxOccurs = m_asCM->get_maxOccurs();
	}

//	POINT oldOrg;
//	OffsetWindowOrgEx(hDC, 0, m_innerRect.top, &oldOrg);

	LDraw::PointF* pt;
	int npoints;

	LDraw::PointF pt2[] =
	{
		LDraw::PointF(0, -10),
		LDraw::PointF(m_width, -10),
		LDraw::PointF(m_width, 10),
		LDraw::PointF(0, 10),
		LDraw::PointF(0, -10)
	};

	LDraw::PointF pt3[] =
	{
		LDraw::PointF(4, -10),
		LDraw::PointF(32, -10),
		LDraw::PointF(36, -6),
		LDraw::PointF(36, 6),
		LDraw::PointF(32, 10),
		LDraw::PointF(4, 10),
		LDraw::PointF(0, 6),
		LDraw::PointF(0, -6),
	};

	if (m_asElement != NULL)
	{
		if (m_bExpanded)
		{
			if (m_pDesignCM)
			{
				LDraw::BBox rect = m_pDesignCM->m_outerRect;

#if 0
				rect.left -= 40;
#endif
			//	CPen pen;
			//	pen.CreatePen(PS_DASH, 1, RGB(0,0,0));
			//	CBrush brush;
			//	brush.CreateSolidBrush(RGB(255, 255, 192));

			//	HPEN hOldPen = (HPEN)SelectObject(hDC, pen);
			//	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, brush);

#if 0
				pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 192)), rect.left, rect.top, rect.Width(), rect.Height());
				LDraw::Pen dashpen(LDraw::Color(0, 0, 0), 2);
				float dashes[] = {5, 5};
				dashpen.SetDashPattern(dashes, 2);
				pGraphics->DrawRectangle(&dashpen, rect.left, rect.top, rect.Width(), rect.Height());
#endif
			//	SelectObject(hDC, hOldPen);
			//	SelectObject(hDC, hOldBrush);
			}
		}

		pt = pt2;
		npoints = 5;
	}
	else
	{
		pt = pt3;
		npoints = 8;
	}

#if 0
	{ // Shadow
		HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
		HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 192));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		POINT oldOrg;
		OffsetWindowOrgEx(hDC, (DWORD)maxOccurs > 1? -70: -40, (DWORD)maxOccurs > 1? -70: -40, &oldOrg);

		Polygon(hDC, pt, npoints);

		SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);

		DeleteObject(hBrush);
	}
#endif

	{
#if 0
		HBRUSH hBrush;
		if (m_bSelected)
			hBrush = CreateSolidBrush(selectedColor);
		else
			hBrush = CreateSolidBrush(RGB(255, 255, 255));

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
#endif

		if ((unsigned long)maxOccurs <= 1)
		{
		//	HPEN hPen = CreatePen((minOccurs == 0)? PS_DOT: PS_SOLID, 1, RGB(0, 0, 0));
		//	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
			LDraw::Pen pen(LDraw::Color(0,0,0), 2);
			if (minOccurs == 0)
			{
				float dashes[] = {3, 3};
				pen.SetDashPattern(dashes, 2);
			}

			pGraphics->FillPolygon(&LDraw::SolidBrush(LDraw::Color(255,255,255)), pt, npoints);
			pGraphics->DrawPolygon(&pen, pt, npoints);

#if 0
			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
#endif
		}
		else // maxOccurs > 1
		{
#if 0
			HPEN hPen = CreatePen((minOccurs == 0)? PS_DOT: PS_SOLID, 1, RGB(0, 0, 0));
			HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

			POINT oldOrg;
			OffsetWindowOrgEx(hDC, -30, -30, &oldOrg);
			Polygon(hDC, pt, npoints);
			SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, &oldOrg);

			Polygon(hDC, pt, npoints);

			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
#endif
			pGraphics->FillPolygon(&LDraw::SolidBrush(LDraw::Color(255,255,255)), pt, npoints);
			pGraphics->DrawPolygon(&LDraw::Pen(LDraw::Color(0,0,0), 2), pt, npoints);
		}

#if 0
		if ((unsigned long)maxOccurs > 1)
		{
		// write min/max occur
			
			HFONT hFont = CreateFont(120, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Symbol");
			HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

			CUString smaxOccurs;
			if ((int)maxOccurs < 0) smaxOccurs = "¥";	// infinity symbol
			else smaxOccurs.Format("%d", maxOccurs);

			CUString str;
			str.Format("%d¼%s", minOccurs, smaxOccurs);
			TextOut(hDC, 40, 160, str, str.GetLength());

			SelectObject(hDC, hOldFont);
			DeleteObject(hFont);
		}
#endif

#if 0
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);
#endif
	}

	if (m_asElement != NULL/*op == AS_NONE*/)
//	if (op == AS_NONE)
	{
#if 0
		DrawAttributes(hDC);
#endif
		ATLASSERT(m_width > 0);

		sysstring name = m_asElement->get_nodeName();

		LDraw::RectF trect(0, -10, m_width, 20);
		trect.Inflate(-1, -1);
		pGraphics->DrawString(name.c_str(), name.length(), GetFont(), trect, &LDraw::SolidBrush(LDraw::Color(0,0,0)));

		if (m_pDesignCM)
		{
			DrawExpanded(pGraphics, m_width, 0, m_bExpanded);
			if (m_bExpanded)
			{
#if 0
				MoveToEx(hDC, m_width+60, 0, NULL);
				LineTo(hDC, m_width+120, 0);

				int top = 0;

				if (TRUE)
				{
					top = 200;

					CRect trect = m_pDesignCM->m_outerRect;
					trect.bottom = trect.top+top;
					trect.InflateRect(-10,-10);

					{	// TODO have differently
						CComPtr<ILDOMElement> element;
						m_asElement->GetElement(&element);
						if (element)
						{
							CComBSTR type;
							element->getAttribute(L"type", &type);

							int oldBk = SetBkMode(hDC, TRANSPARENT);
							DrawText(hDC, _bstr_t(type), type.Length(), &trect, DT_SINGLELINE | DT_VCENTER);
							SetBkMode(hDC, oldBk);
						}
					}
				}

				POINT oldOrg;
				OffsetWindowOrgEx(hDC, -m_pDesignCM->m_outerRect.left, -(m_pDesignCM->m_outerRect.top+top), &oldOrg);

				m_pDesignCM->DrawDesign(hDC);

				SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
#endif
				m_pDesignCM->OnRender(pGraphics);
			}
		}
	}
	else
	{
		ASContentModelTypeOp op = m_asCM->get_listOperator();

		if (op == AS_SEQUENCE)
		{
			pGraphics->DrawLine(&LDraw::Pen(LDraw::Color::Black), 4, 0, 32, 0);

		//	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Black), 12-2, -2, 4, 4);
			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Black), 18-2, -2, 4, 4);
			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Black), 24-2, -2, 4, 4);

		//	SelectObject(hDC, hOldBrush);
		}
		else if (op == AS_CHOICE)
		{
#if 0
			MoveToEx(hDC, 30, 0, NULL);
			LineTo(hDC, 90, 0);
			LineTo(hDC, 140, -50);

		//
			MoveToEx(hDC, 270, -50, NULL);
			LineTo(hDC, 270, 50);

		//
			MoveToEx(hDC, 270, -50, NULL);
			LineTo(hDC, 210, -50);

			MoveToEx(hDC, 320, 0, NULL);
			LineTo(hDC, 210, 0);

			MoveToEx(hDC, 270, 50, NULL);
			LineTo(hDC, 210, 50);

			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

			Rectangle(hDC, 180-20, -50-20, 180+20, -50+20);
			Rectangle(hDC, 180-20, -20, 180+20, 20);
			Rectangle(hDC, 180-20, 50-20, 180+20, 50+20);

			SelectObject(hDC, hOldBrush);
#endif
		}
		else if (op == AS_ALL)
		{
#if 0
			MoveToEx(hDC, 90, -50, NULL);
			LineTo(hDC, 90, 50);

			MoveToEx(hDC, 270, -50, NULL);
			LineTo(hDC, 270, 50);

		//
			MoveToEx(hDC, 90, -50, NULL);
			LineTo(hDC, 150-5, -50);

			MoveToEx(hDC, 40, 0, NULL);
			LineTo(hDC, 150-5, 0);

			MoveToEx(hDC, 90, 50, NULL);
			LineTo(hDC, 150-5, 50);

		//
			MoveToEx(hDC, 270, -50, NULL);
			LineTo(hDC, 210, -50);

			MoveToEx(hDC, 320, 0, NULL);
			LineTo(hDC, 210, 0);

			MoveToEx(hDC, 270, 50, NULL);
			LineTo(hDC, 210, 50);

		//
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

			Rectangle(hDC, 180-20, -50-20, 180+20, -50+20);
			Rectangle(hDC, 180-20, -20, 180+20, 20);
			Rectangle(hDC, 180-20, 50-20, 180+20, 50+20);

			SelectObject(hDC, hOldBrush);
#endif
		}
		else
			ATLASSERT(0);

		if (m_bExpanded)
		{
			int n = m_defs.GetSize();
			if (n)
			{
				pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(0,0,0), 2), 36+8, 0, 36+8+8, 0);
#if 0
				MoveToEx(hDC, 360+80, 0, NULL);
				LineTo(hDC, 360+80+80, 0);
#endif

				pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(0,0,0), 2),
					36+8+8, m_defs[0]->m_outerRect.top - m_defs[0]->m_innerRect.top,
					36+8+8, m_defs[n-1]->m_outerRect.top - m_defs[n-1]->m_innerRect.top);
#if 0
				MoveToEx(hDC, 360+80+80, m_defs[0]->m_outerRect.top - m_defs[0]->m_innerRect.top, NULL);
				LineTo(hDC, 360+80+80, m_defs[n-1]->m_outerRect.top - m_defs[n-1]->m_innerRect.top);
#endif

				for (int i = 0; i < m_defs.GetSize(); i++)
				{
					CDTDDesignDefinition* pDef = m_defs[i];

					pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(0,0,0), 2),
						pDef->m_outerRect.left -10, pDef->m_outerRect.top -pDef->m_innerRect.top,
						pDef->m_outerRect.left, pDef->m_outerRect.top -pDef->m_innerRect.top);

#if 0
					POINT oldOrg;
					OffsetWindowOrgEx(hDC, -pDef->m_outerRect.left, -pDef->m_outerRect.top, &oldOrg);
					MoveToEx(hDC, -100, -pDef->m_innerRect.top, NULL);
					LineTo(hDC, 0, -pDef->m_innerRect.top);
#endif

//					pDef->DrawDesign(hDC);

#if 0
					SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
#endif
				}
			}
		}

		DrawExpanded(pGraphics, 38, 0, m_bExpanded);
	}

//	SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
}

void CDTDDesignContentModel::handleEvent(LXUIEvent* evt)
{
	sysstring type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == OLESTR("mousedown"))
		{
			evt->stopPropagation();

			CLXUIMouseEvent* mouseEvt = dynamic_cast<CLXUIMouseEvent*>(evt);
			OnButtonDown(mouseEvt);
		}
	}
}

void CDTDDesignContentModel::OnButtonDown(CLXUIMouseEvent* evt)
{
	Point* point = ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());
//	ASContentModelTypeOp op;
//	m_asCM->get_listOperator(&op);

	if (m_asElement != NULL)
	{
		LDraw::Point pt(point->get_X(), point->get_Y());
	//	pt.Y += m_innerRect.top;

		LDraw::RectD r(0, -4, m_width, 8);
		LDraw::RectD rexp(m_width-4, -4, 8, 8);
		LDraw::RectD raexp(0, -4, 8, 4);

		if (rexp.Contains(pt.X, pt.Y))
		{
			m_bExpanded = !m_bExpanded;

			if (m_bExpanded)
			{
				BuildChildren();
			}

		//	bSize = true;
		//	return this;
			InvalidateMeasure();
		}
#if 0
		else if (raexp.PtInRect(pt))
		{
			m_bAttributesExpanded = !m_bAttributesExpanded;

			bSize = true;
			return this;
		}
		else if (r.PtInRect(pt))
		{
			m_bSelected = true;

			if (bDblClk)
			{
				ATLASSERT(m_bEditChanged == false);

				BSTR bname;
				m_asElement->get_nodeName(&bname);
				_bstr_t name = _bstr_t(bname, false);

				CRect rect = GetAbsInnerRect();

				long scrollposX; m_pCtl->m_horz->get_pos(&scrollposX);
				long scrollposY; m_pCtl->m_vert->get_pos(&scrollposY);

				HDC hDC = CreateCompatibleDC(NULL);
				SetMapMode(hDC, MM_ANISOTROPIC);
				SetWindowExtEx(hDC, 100, 100, NULL);
				SetWindowOrgEx(hDC, 0, 0, NULL);
				SetViewportExtEx(hDC, 10*m_pCtl->m_magnify, 10*m_pCtl->m_magnify, NULL);
				SetViewportOrgEx(hDC, -scrollposX, -scrollposY, NULL);

			//	OffsetWindowOrgEx(hDC, m_pCtl->m_pRoot->m_outerRect.left, m_pCtl->m_pRoot->m_outerRect.top, NULL);

				HFONT hOldFont = (HFONT)SelectObject(hDC, m_pCtl->m_hFont);

				LPtoDP(hDC, (LPPOINT)&rect, 2);

				m_hWndEdit = CreateWindowEx(0, "edit", name, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE,
					rect.left-1, rect.top-1, rect.Width()+2, rect.Height()+2, m_pCtl->m_hWnd, (HMENU)1, _Module.m_hInst, NULL);

				m_pCtl->m_wndEdit.SubclassWindow(m_hWndEdit);

				if (m_hWndEdit)
				{
					::SetWindowLong(m_hWndEdit, GWL_USERDATA, (long)static_cast<CDTDDesignSchemaNode*>(this));

				//	HFONT hFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
				//	SendMessage(m_hWndEdit, WM_SETFONT, (WPARAM)hFont, 0);

					SendMessage(m_hWndEdit, EM_SETSEL, 0, -1);
					SetFocus(m_hWndEdit);
				}

				SelectObject(hDC, hOldFont);
				DeleteDC(hDC);
			}

			return this;
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

					if (m_asElement)
					{
						pt2.y -= 200;
					}

					return m_pDesignCM->OnClick(pt2, bDblClk, bSize);
				}
			}
		}
#endif
	//	return NULL;
	}
	else
	{
		LDraw::Point pt(point->get_X(), point->get_Y());
		//POINT pt = point;
	//	pt.Y += m_innerRect.top;

		//CRect r(0, -40, 360, 40);
		LDraw::RectD rexp(38-4, -4, 8, 8);

		if (rexp.Contains(pt.X, pt.Y))
		{
			m_bExpanded = !m_bExpanded;

			if (m_bExpanded)
			{
				BuildChildren();
			}
			else
			{
				FreeChildren();
			}

			InvalidateMeasure();
		//	bSize = true;
		//	return this;
		}
#if 0
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
					CDTDDesignDefinition* pDef = m_defs[i];

					POINT pt2 = pt;
					pt2.x -= pDef->m_outerRect.left;
					pt2.y -= pDef->m_outerRect.top;

					CDTDDesignSchemaNode* p = pDef->OnClick(pt2, bDblClk, bSize);
					if (p)
						return p;
				}
			}
		}
#endif
	}
}

#if 0
STDMETHODIMP CDTDDesignContentModel::_handle(/*[in]*/ _ASUserDataHandleType operation,
                   /*[in]*/ BSTR key, 
                   /*[in]*/ IUnknown* data, 
                   /*[in]*/ IASObject* src, 
                   /*[in]*/ IASObject* dst)
{
	/*
	if (operation == ASNODE_RENAMED)
	{
	}
	else
	{
		*/
	if (FALSE)
	{
		// Rebuild
		{
			for (int i = 0; i < m_defs.GetSize(); i++)
			{
				m_defs[i]->Release();
			}
			m_defs.RemoveAll();
		}
		Build();
	}

	m_pCtl->UpdateView();

	return S_OK;
}
#endif

void CDTDDesignContentModel::SetOptionalUnbounded(IASModel* asModel, bool bOptional, bool bUnbounded)
{
	ATLASSERT(0);
#if 0
	if (m_asCM == NULL)
	{
		// Wrap a ContentModel around the Element
		IASContentModel* asCM = asModel->createASContentModel(bOptional? 0: 1, bUnbounded? 0xffffffff/*AS_UNBOUNDED*/: 1, AS_NONE);
		if (asCM != NULL)
		{
			CDTDDesignDefinition* pParent = (CDTDDesignContentModel*)m_pParent;
			pParent->Get_asCM()->replacesubModel(m_asElement, asCM);

			unsigned long length;
			asCM->appendsubModel(m_asElement, &length);

			m_asCM = asCM;
		}
	}
	else
	{
		if (bOptional) m_asCM->put_minOccurs(0);
		if (bUnbounded) m_asCM->put_maxOccurs(0xffffffff/*AS_UNBOUNDED*/);
	}

	asModel->FireModelChanged();
#endif
}

void CDTDDesignContentModel::RemoveOptionalUnbounded(IASModel* asModel, bool bOptional, bool bUnbounded)
{
	ATLASSERT(m_asCM != NULL);

	if (bOptional) m_asCM->put_minOccurs(1);
	if (bUnbounded) m_asCM->put_maxOccurs(1);

	if (m_asElement)
	{
		long minOccurs;
		long maxOccurs;
		minOccurs = m_asCM->get_minOccurs();
		maxOccurs = m_asCM->get_maxOccurs();

		if (minOccurs == 1 && maxOccurs == 1)
		{
		// Unwrap the Content model around the element
			CDTDDesignDefinition* pParent = (CDTDDesignContentModel*)m_pParent;
			pParent->Get_asCM()->replacesubModel(m_asCM, m_asElement);

		// Release the content model
			delete m_asCM;
			m_asCM = NULL;
		}
	}

//	asModel->FireModelChanged();
}

// virtual
void CDTDDesignContentModel::DeselectAll()
{
	for (int i = 0; i < m_defs.GetSize(); i++)
	{
		m_defs[i]->m_bSelected = false;
	}
}

#if 0
STDMETHODIMP CDTDDesignContentModel::SetOptionalUnbounded(bool bOptional, bool bUnbounded)
{
	SetOptionalUnbounded(m_pCtl->m_asModel, bOptional, bUnbounded);
	return S_OK;
}

STDMETHODIMP CDTDDesignContentModel::RemoveOptionalUnbounded(bool bOptional, bool bUnbounded)
{
	RemoveOptionalUnbounded(m_pCtl->m_asModel, bOptional, bUnbounded);
	return S_OK;
}
#endif