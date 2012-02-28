#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridCtl.h"

#include "XMLGridTable.h"
#include "XMLGridElement.h"
#include "XMLGridAttribute.h"

void DrawTopLeft(HDC hDC, LDraw::RectI rc, LDraw::Color clr);

///////////////////////////////////
// CGridTable

void CGridTable::BuildXML(System::StringBuilderW& str)
{
	ASSERT(0);
#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridElement* pElement = (CGridElement*)m_childList.GetNext(pos);

		sysstring str2 = pElement->BuildXML();

		str += str2;
	}
#endif
	return str;
}

// virtual
void CGridTable::BuildSelectedXML(System::StringBuilderW& stream)
{
	ASSERT(0);
#if 0
	CArray<CGridElement*,CGridElement*> selectedElements;

// Find out wether multiple rows (elements) are selected
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

		BOOL bSelected = pChild->IsSelected(TRUE/*bDeep*/);
		if (bSelected)
			selectedElements.Add(pChild);
	}

	if (selectedElements.GetSize() > 0)
	{
		if (selectedElements.GetSize() > 1)
		{
		// When multiple rows (elements) are selected, we wrap all of the
		// columns in <elementname/>

			for (int i = 0; i < selectedElements.GetSize(); i++)
			{
				CGridElement* pChild = selectedElements[i];

				str += L"<" + pChild->GetNodeName() + L" ";

				//
				for (int i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);

					if (pNode)
					{
						if (pNode->IsSelected(TRUE))
						{
							sysstring str2 = pNode->BuildXML();

							str += str2;
						}
					}
				}

				str += L">\n</" + pChild->GetNodeName() + L">\n";
			}
		}
		else
		{
		// When only one row (element) is selected, we don't necessarily wrap
		// the columns in <elementname/>

			CGridElement* pChild = selectedElements[0];

			if (pChild->m_selected)
				str += L"<" + pChild->GetNodeName() + L" ";

			//
			for (int i = 0; i < m_nodeDecls.GetSize(); i++)
			{
				CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);

				if (pNode)
				{
					if (pNode->IsSelected(TRUE))
					{
						sysstring str2 = pNode->BuildXML();

						str += str2;
					}
				}
			}

			if (pChild->m_selected)
				str += L">\n</" + pChild->GetNodeName() + L">\n";
		}
	}
#endif
}

// virtual
void CGridTable::BuildSelectedXML(IStream* stream)
{
	CArray<CGridElement*,CGridElement*> selectedElements;

	ATLASSERT(0);
#if 0
// Find out wether multiple rows (elements) are selected
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

		BOOL bSelected = pChild->IsSelected(TRUE/*bDeep*/);
		if (bSelected)
			selectedElements.Add(pChild);
	}

	if (selectedElements.GetSize() > 0)
	{
		if (selectedElements.GetSize() > 1)
		{
		// When multiple rows (elements) are selected, we wrap all of the
		// columns in <elementname/>

			for (int i = 0; i < selectedElements.GetSize(); i++)
			{
				CGridElement* pChild = selectedElements[i];

				//str += L"<" + pChild->GetNodeName() + L" ";

				//
				for (int i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);

					if (pNode)
					{
						if (pNode->IsSelected(TRUE))
						{
							//sysstring str2 = pNode->BuildXML();

							pNode->BuildXML(stream);
						}
					}
				}

			//	str += L">\n</" + pChild->GetNodeName() + L">\n";
			}
		}
		else
		{
		// When only one row (element) is selected, we don't necessarily wrap
		// the columns in <elementname/>

			CGridElement* pChild = selectedElements[0];

		//	if (pChild->m_selected)
		//		str += L"<" + pChild->GetNodeName() + L" ";

			//
			for (int i = 0; i < m_nodeDecls.GetSize(); i++)
			{
				CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);

				if (pNode)
				{
					if (pNode->IsSelected(TRUE))
					{
					//	sysstring str2 = pNode->BuildXML();
					//	str += str2;
						pNode->BuildXML(stream);
					}
				}
			}

			//if (pChild->m_selected)
			//	str += L">\n</" + pChild->GetNodeName() + L">\n";
		}
	}
#endif
}

// virtual
void CGridTable::BuildXML(IStream* stream)
{
	ATLASSERT(0);
#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridElement* pElement = (CGridElement*)m_childList.GetNext(pos);

		pElement->BuildXML(stream);
	}
#endif
}

CGridNode* CGridNodeDecl::FindElementNode(CGridElement* pElement)
{
	for (int i = 0; i < m_nodes.GetSize(); i++)
	{
		if (m_nodes[i]->m_parent == pElement)
			return m_nodes[i];
	}

	return NULL;
}

// virtual
void CGridTable::Draw(HDC hDC, BOOL bSelected)
{
	ATLASSERT(0);
#if 0
	if (m_selected) bSelected = TRUE;

	if (bSelected)
		FillSolidRect(hDC, 0, 0, m_size.cx, m_size.cy, RGB(138, 200, 235));

	CRect fullrect(0, 0, m_size.cx, m_size.cy);
	DrawTopLeft(hDC, &fullrect, RGB(200, 200, 200));

	sysstring tagName = GetNodeName();

	SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

	CRect trect(16, 0, m_size.cx, 16);

	CUString str;
	str.Format("%S (%d)", (BSTR)tagName, m_childList.GetCount());
	DrawText(hDC, str, str.GetLength(), &trect, DT_SINGLELINE);

	DrawExpand(hDC, FALSE);

	if (m_expanded)
	{
		int x = 20;
		int y = 16;

		FillSolidRect(hDC, x, y, 20, 16, bSelected? RGB(138, 200, 235): RGB(255, 255, 200));

		FillSolidRect(hDC, x+20, y, m_size.cx-x-20, 16, RGB(255, 255, 200));
		FillSolidRect(hDC, x, y+16, 20, m_size.cy-y-16, RGB(255, 255, 200));

		HPEN hGrayPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hGrayPen);

		MoveToEx(hDC, 20, y, NULL);
		LineTo(hDC, m_size.cx, y);

		SelectObject(hDC, m_pUI->m_hFont[Font_AttributeName]);

		MoveToEx(hDC, 20, 16, NULL);
		LineTo(hDC, 20, m_size.cy);

		int i;

		x = 20+20;
		for (i = 0; i < m_nodeDecls.GetSize(); i++)
		{
			MoveToEx(hDC, x, 16, NULL);
			LineTo(hDC, x, m_size.cy);

			x += m_nodeDecls[i]->m_width;
		}

	// Draw titles
		x = 20+20;
		for (i = 0; i < m_nodeDecls.GetSize(); i++)
		{
			BOOL bSelected2 = bSelected || m_nodeDecls[i]->m_selected;

			CRect fullrect(1+x, 1+y, x+m_nodeDecls[i]->m_width, y+16);

			CRect iconrect = fullrect;
			iconrect.right = iconrect.left + 16;

			CRect trect = fullrect;
			trect.left += 16;

			if (bSelected2)
			{
				FillSolidRect(hDC, &fullrect, RGB(138, 200, 235));
			}

			if (m_nodeDecls[i]->m_nodeType == LNODE_ATTRIBUTE)
			{
				SetTextColor(hDC, RGB(200, 0, 0));
				DrawText(hDC, "=", 1, &iconrect, DT_VCENTER | DT_SINGLELINE);
			}
			else// if (m_nodeDecls[i]->m_nodeType == LNODE_ELEMENT)
			{
				SetTextColor(hDC, RGB(200, 0, 0));
				SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);
				DrawText(hDC, "<>", 2, &iconrect, DT_VCENTER | DT_SINGLELINE);
			}

			SetTextColor(hDC, RGB(0, 0, 0));
			DrawText(hDC, m_nodeDecls[i]->m_name, m_nodeDecls[i]->m_name.length(), &trect, DT_SINGLELINE | DT_END_ELLIPSIS);

			if (m_nodeDecls[i]->m_selected)
			{
				CRect columnRect(x, y, x+m_nodeDecls[i]->m_width+1, m_size.cy);
				DrawFocusRect(hDC, &columnRect);
			}

			x += m_nodeDecls[i]->m_width;
		}

		y += 16;

		int nchild = 0;
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

			MoveToEx(hDC, 20, y, NULL);
			LineTo(hDC, m_size.cx, y);

			int x = 20;

			CRect rrect(x+1, y+1, x+20, y+pChild->m_size.cy);

			BOOL bSelected2 = bSelected || pChild->m_selected;

			if (bSelected2)
			{
				FillSolidRect(hDC, &rrect, RGB(138, 200, 235));
			}

			rrect.right -= 2;

			SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

			CUString str;
			str.Format("%d", nchild+1);
			DrawText(hDC, str, str.GetLength(), &rrect, DT_SINGLELINE | DT_VCENTER | DT_RIGHT);

			x += 20;

			for (int i = 0; i < m_nodeDecls.GetSize(); i++)
			{
				CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);
				if (pNode)
				{
					bool bSelected2 = bSelected || pChild->m_selected || m_nodeDecls[i]->m_selected;

					if (bSelected2)
					{
						CRect rc(x+1, y+1, x+m_nodeDecls[i]->m_width, y+pChild->m_size.cy);
						FillSolidRect(hDC, &rc, RGB(138, 200, 235));
					}
					
					POINT oldOrg;
					OffsetViewportOrgEx(hDC, x, y, &oldOrg);

					pNode->DrawContent(hDC, bSelected2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
				}

				x += m_nodeDecls[i]->m_width;
			}

			y += pChild->m_size.cy;

			nchild++;
		}

		SelectObject(hDC, hOldPen);
		DeleteObject(hGrayPen);
	}
#endif
}

// virtual
void CGridTable::Size(HDC hDC, int width)
{
	ATLASSERT(0);
#if 0
	int y = 16;
	int x = 20+20;

	if (m_expanded)
	{
		y = 16;

		for (int i = 0; i < m_nodeDecls.GetSize()-1; i++)
		{
			x += m_nodeDecls[i]->m_width;
		}

	// Last column stretches to fill width
		m_nodeDecls[i]->m_width = width - x;
		if (m_nodeDecls[i]->m_width < 20) m_nodeDecls[i]->m_width = 20;

		x += m_nodeDecls[i]->m_width;

		y += 16;

		{
		// Size the nodes and get the largest width of the nodes
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

				for (i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);
					if (pNode)
					{
						pNode->SizeContent(hDC, m_nodeDecls[i]->m_width);
						m_nodeDecls[i]->m_width = max(m_nodeDecls[i]->m_width, pNode->m_size.cx);
					}
				}
			}

		// Size the nodes and get height of largest attribute
			pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

				int maxy = 0;

				for (i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);
					if (pNode)
					{
						pNode->SizeContent(hDC, m_nodeDecls[i]->m_width);

						maxy = max(maxy, pNode->m_size.cy);
					}
				}

			// Set all nodes to same height
				for (i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);
					if (pNode)
					{
						pNode->m_size.cy = maxy;
					}
				}

				pChild->m_size.cy = maxy;

				y += pChild->m_size.cy;
			}
		}

		x = 20+20;
		for (i = 0; i < m_nodeDecls.GetSize(); i++)
		{
			x += m_nodeDecls[i]->m_width;
		}
	}

	m_size.cy = y;
	m_size.cx = x;
#endif
}

// virtual
void CGridTable::RecalculateParentSize(HDC hDC)
{
#if 0
	int y = 16;
	int x = 20+20;

	if (m_expanded)
	{
		y = 16;

		for (int i = 0; i < m_nodeDecls.GetSize()-1; i++)
		{
			x += m_nodeDecls[i]->m_width;
		}

	// Last column stretches to fill width
		m_nodeDecls[i]->m_width = width - x;
		if (m_nodeDecls[i]->m_width < 20) m_nodeDecls[i]->m_width = 20;

		x += m_nodeDecls[i]->m_width;

		y += 16;

		{
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

				for (i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);
					if (pNode)
					{
						m_nodeDecls[i]->m_width = max(m_nodeDecls[i]->m_width, pNode->m_size.cx);
					}
				}
			}

		// Size the nodes and get height of largest attribute
			pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

				int maxy = 0;

				for (i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);
					if (pNode)
					{
						maxy = max(maxy, pNode->m_size.cy);
					}
				}

				y += pChild->m_size.cy;
			}
		}

		x = 20+20;
		for (i = 0; i < m_nodeDecls.GetSize(); i++)
		{
			x += m_nodeDecls[i]->m_width;
		}
	}

	m_size.cy = y;
	m_size.cx = x;
#endif
	if (m_parent)
	{
		m_parent->RecalculateParentSize(hDC);
	}
}

STDMETHODIMP CGridTable::DeselectRows()
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

		pChild->Deselect();

	//	pChild->m_selected = false;
	}

	m_pUI->Invalidate();

	return S_OK;
}

STDMETHODIMP CGridTable::DeselectColumns()
{
	for (int i = 0; i < m_nodeDecls.GetSize(); i++)
	{
		m_nodeDecls[i]->m_selected = false;
	}

	m_pUI->Invalidate();

	return S_OK;
}

//virtual
int CGridTable::Click(HDC hDC, POINT point, UINT nFlags, BOOL bDblClk, CGridItem* *pVal)
{
	ATLASSERT(0);
#if 0
	*pVal = NULL;

	POINT org;
	GetViewportOrgEx(hDC, &org);

	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx+2 && point.y < m_size.cy+2)
	{
		int nClick = CGridContainer::Click(hDC, point, nFlags, bDblClk, pVal);
		if (*pVal)
			return nClick;

		int x = 20+20;

		if (point.y > 16+16 && point.x > 20 && point.x < x)
		{
			// Clicked on Row header
			int y = 16;
			y += 16;

			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

				y += pChild->m_size.cy;

				if (point.y < y)
				{
					DeselectRows();
					DeselectColumns();

					pChild->m_selected = TRUE;
					m_pUI->Invalidate();

					*pVal = pChild;//this;
					return 1;
				}
			}
		}

		if (point.x > 20+20 && point.y > 16 && point.y < 32)	// Clicked on Column header
		{
			for (int i = 0; i < m_nodeDecls.GetSize(); i++)
			{
				x += m_nodeDecls[i]->m_width;

				if (abs(point.x-x) <= 2)
				{
					HWND hwnd = m_pUI->m_hWnd;

					m_pUI->SetCapture();

					CPoint oldpoint = point;

					BOOL bLoop = TRUE;
					MSG msg;
					while (bLoop && GetMessage(&msg, hwnd, 0, 0))
					{
						TranslateMessage(&msg);

						switch (msg.message)
						{
						case WM_LBUTTONUP:
							{
								bLoop = FALSE;
							}
							break;
							
						case WM_MOUSEMOVE:
							{
								CPoint point;
								point.x = (short)LOWORD(msg.lParam);
								point.y = (short)HIWORD(msg.lParam);

								point.x -= org.x;
								point.y -= org.y;

								m_nodeDecls[i]->m_width += (point.x-oldpoint.x);

								m_pUI->m_pTree->SizeContent(hDC, m_pUI->m_pTree->m_size.cx + (point.x-oldpoint.x));
								//Size(hDC, 20 + m_attrNameWidth pt.x);

								m_pUI->Invalidate();
								m_pUI->OnSize();

								oldpoint = point;
							}
							break;

						default:
							DispatchMessage(&msg);
							break;
						}
					}

					ReleaseCapture();

					*pVal = this;
					return 0;
				}
				else if (point.x < x)
				{
					// Clicked on column

					DeselectRows();
					DeselectColumns();

					int lastcol = m_iLastColumnFocus;
					int thiscol = i;

				//	m_nodeDecls[i]->m_selected = TRUE;
					for (int col = lastcol; col <= thiscol; col++)
					{
						m_nodeDecls[col]->m_selected = TRUE;

						//CGridNode* pNode = m_nodeDecls[col]->FindElementNode(pElement);

						/*
						if (pNode)
						{
							pNode->m_selected = true;
						}
						*/
					}

					m_pUI->Invalidate();

					*pVal = this;
					return 0;
				}
			}
		}

	// Click on children
		int y = 16;
		y += 16;

		if (point.x > 20+20 && point.y > y)
		{
			int nchild = 0;
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridElement* pChild = (CGridElement*)m_childList.GetNext(pos);

				int x = 20;
				x += 20;

				for (int i = 0; i < m_nodeDecls.GetSize(); i++)
				{
					CGridNode* pNode = m_nodeDecls[i]->FindElementNode(pChild);
					if (pNode)
					{
						POINT oldOrg;
						OffsetViewportOrgEx(hDC, x, y, &oldOrg);

						CPoint childpoint = point;
						childpoint.x -= x;
						childpoint.y -= y;

						int nClick = pNode->ClickContent(hDC, childpoint, nFlags, bDblClk, pVal);

						SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

						if (*pVal)
						{
							if (nClick == 1)
							{
								if (nFlags & MK_SHIFT)
								{
									int lastrow = m_iLastRowFocus;
									int thisrow = nchild;

									int lastcol = m_iLastColumnFocus;
									int thiscol = i;

									for (int row = lastrow; row <= thisrow; row++)
									{
										UPOSITION pos = m_childList.FindIndex(row);
										CGridElement* pElement = (CGridElement*)m_childList.GetAt(pos);

										for (int col = lastcol; col <= thiscol; col++)
										{
											CGridNode* pNode = m_nodeDecls[col]->FindElementNode(pElement);

											if (pNode)
											{
												pNode->m_selected = true;
											}
										}
									}

									//m_pUI->m_pLastFocus
								}
								else
								{
									DeselectRows();
									DeselectColumns();

									m_iLastRowFocus = nchild;
									m_iLastColumnFocus = i;

									m_pUI->m_pLastFocus = *pVal;

									(*pVal)->m_selected = TRUE;
								}

								m_pUI->Invalidate();
							}

							m_pUI->m_commonAncestor = m_parent;	// ??
							return 0;//nClick;
						}
					}

					x += m_nodeDecls[i]->m_width;
				}

				y += pChild->m_size.cy;

				nchild++;
			}
		}

	// Clicked on Table itself
		*pVal = this;
		return 1;
	}
#endif
	return 0;
}

CGridAttrDecl* CGridTable::FindAttrDecl(const sysstring& name)
{
	for (int i = 0; i < m_attrDecls.GetSize(); i++)
	{
		if (!wcscmp(m_attrDecls[i]->m_name.c_str(), name.c_str()))
		{
			return static_cast<CGridAttrDecl*>(m_attrDecls[i]);
		}
	}

	return NULL;
}

void CGridTable::BuildAttrDecls()
{
// Attribute nodes
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridElement* pElement = (CGridElement*)m_childList.GetNext(pos);

		UPOSITION pos2 = pElement->m_attributeList.GetHeadPosition();
		while (pos2)
		{
			CGridAttribute* pAttr = (CGridAttribute*)pElement->m_attributeList.GetNext(pos2);

			CGridAttrDecl* pAttrDecl = FindAttrDecl(pAttr->GetNodeName());
			if (!pAttrDecl)
			{
				pAttrDecl = new CGridAttrDecl;

				pAttrDecl->m_name = pAttr->GetNodeName();
				m_attrDecls.Add(pAttrDecl);
				m_nodeDecls.Add(pAttrDecl);
			}

			pAttrDecl->m_nodes.Add(pAttr);
		}
	}

// sub-nodes
	CArray<UPOSITION,UPOSITION> positions;

	pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridElement* pElement = (CGridElement*)m_childList.GetNext(pos);
		positions.Add(pElement->m_nodeList.GetHeadPosition());
	}

	bool bContinue = true;
	while (bContinue)
	{
		bContinue = false;

		int nchild = 0;
		pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CGridElement* pElement = (CGridElement*)m_childList.GetNext(pos);

			if (positions[nchild])
			{
				bContinue = true;
				CGridNode* pNode = (CGridNode*)pElement->m_nodeList.GetNext(positions[nchild]);

				sysstring nodeName = pNode->GetNodeName();

				CGridElementDecl* pNodeDecl = NULL;

				for (int i = nchild; i < m_nodeDecls.GetSize(); i++)
				{
					if (!wcscmp(nodeName.c_str(), m_nodeDecls[i]->m_name.c_str()))
					{
						pNodeDecl = static_cast<CGridElementDecl*>(m_nodeDecls[i]);
						break;
					}
				}

				if (!pNodeDecl)
				{
					pNodeDecl = new CGridElementDecl;

					pNodeDecl->m_name = nodeName;
					m_nodeDecls.Add(pNodeDecl);
				}

				pNodeDecl->m_nodes.Add(pNode);
			}

			nchild++;
		}
	}
}
