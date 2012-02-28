// ASGraphCtl.cpp : Implementation of CASGraphCtl

#include "stdafx.h"
#include "ASEditCtlsMod.h"
//#include "..\UIT\UIT.h"

#include "ASGraphCtl.h"

#include "..\OleDataObject.h"

COLORREF selectedColor = RGB(160, 160, 240);


/////////////////////////////////////////////////////////////////////////////
// CASGraphCtl

//class CDTDDesignDefinition;

#include "ASDesignObject.h"



class CDTDDesignContentModel;

#include "ASDesignDefinition.h"
#include "ASDesignAttribute.h"
#include "ASDesignContentModel.h"
#include "ASDesignElementDefinitionRoot.h"


/////////////////////////////////////////////////////////////////////////////
// CASGraphCtl

#if 0
LRESULT CASGraphCtl::OnEditChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CDTDDesignSchemaNode* pNode = (CDTDDesignSchemaNode*)m_wndEdit.GetWindowLong(/*m_hWndEdit,*/ GWL_USERDATA);

	HDC hDC = CreateCompatibleDC(NULL);

	/*
	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
	*/

	pNode->OnEditChange(hDC/*, m_pTree*/);

	//SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	Invalidate();
//	OnSize();

	return 0;
}

LRESULT CASGraphCtl::OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CDTDDesignSchemaNode* pNode = (CDTDDesignSchemaNode*)m_wndEdit.GetWindowLong(/*m_hWndEdit,*/ GWL_USERDATA);

	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
		pNode->EndEdit();
		//m_hWndEdit = NULL;

		ATLASSERT(m_wndEdit.m_hWnd == NULL);

		/*
		if (uMsg == WM_KEYDOWN)
			return 0;
			*/

		return 0;
	}
	else
	{
		return m_wndEdit.DefWindowProc(uMsg, wParam, lParam);
	}
}
#endif

void CASGraphCtl::OnRender3(LDraw::Graphics* pGraphics)
{
	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, m_computedSize.Width, m_computedSize.Height);
#if 0
	RECT& rc = *(RECT*)di.prcBounds;

	HDC hDC = di.hdcDraw;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int state = SaveDC(hDC);

	Rectangle(hDC, m_areaRect.left-1, m_areaRect.top-1, m_areaRect.right+1, m_areaRect.bottom+1);

	if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
	{
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 100, 100, NULL);
		SetWindowOrgEx(hDC, 0, 0, NULL);
		SetViewportExtEx(hDC, 10*m_magnify, 10*m_magnify, NULL);
		SetViewportOrgEx(hDC, -scrollposX, -scrollposY, NULL);

		SetBkMode(hDC, TRANSPARENT);
		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

		if (m_pRoot)
		{
			POINT oldOrg;
			OffsetWindowOrgEx(hDC, -m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top, &oldOrg);
#endif

		//	pGraphics->TranslateTransform(-m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top);
			m_pRoot->OnRender(pGraphics);

#if 0
			SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}

		SelectObject(hDC, hOldFont);
	}

	RestoreDC(hDC, state);
#endif
}

LRESULT CASGraphCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnButtonDown(wParam, lParam, 0, FALSE);
	return 0;
}

LRESULT CASGraphCtl::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnButtonDown(wParam, lParam, 0, TRUE);
	return 0;
}

LRESULT CASGraphCtl::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnButtonDown(wParam, lParam, 1, FALSE);
	return 0;
}

void CASGraphCtl::OnButtonDown(WPARAM wParam, LPARAM lParam, int iButton, BOOL bDblClk)
{
	ATLASSERT(0);
#if 0
	if (m_wndEdit.m_hWnd)
	{
		CDTDDesignSchemaNode* pNode = (CDTDDesignSchemaNode*)m_wndEdit.GetWindowLong(/*m_hWndEdit,*/ GWL_USERDATA);
		pNode->EndEdit();
		//m_hWndEdit = NULL;
	}

	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_pRoot)
	{
		CPoint pt = point;
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

		if (bDblClk)
		{
			MessageBeep(-1);
		}

		bool bSize = false;
		CDTDDesignSchemaNode* pNode = m_pRoot->OnClick(pt, bDblClk, bSize);

		if (pNode)
		{
			if (bSize)
			{
				HDC hDC = CreateCompatibleDC(NULL);
				SetMapMode(hDC, MM_ANISOTROPIC);
				SetWindowExtEx(hDC, 10, 10, NULL);
				SetViewportExtEx(hDC, 1, 1, NULL);
				HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

				m_pRoot->Size(hDC);
				m_pRoot->m_outerRect = m_pRoot->m_innerRect;

				SelectObject(hDC, hOldFont);
				DeleteDC(hDC);

				OnSize();
			}
			else
			{
				m_pActiveItem = pNode;

				Fire_OnActivateASObject(m_pActiveItem);

				if (!bDblClk)
				{
					CArray<IASObject*,IASObject*> items;

					CDTDDesignContentModel* pParent = NULL;

					_ASObjectType nodeType;
					pNode->m_asObject->get_asNodeType(&nodeType);
					if (nodeType == AS_ATTRIBUTE_DECLARATION)
					{
						CASAttribute* pAttr = (CASAttribute*)pNode;

					// TODO
						items.Add(pAttr->m_asObject);
					}
					else
					{
						pParent = (CDTDDesignContentModel*)pNode->m_pParent;
						if (pParent)
						{
							for (int i = 0; i < pParent->m_defs.GetSize(); i++)
							{
								CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)pParent->m_defs[i];
								if (pItem->m_bSelected)
								{
									ATLASSERT(pItem->m_asObject);
									items.Add(pItem->m_asObject);
								}
							}
						}
					}

					if (items.GetSize() > 0)
					{
						CComObject<COleDataObject>* dataObject;
						CComObject<COleDataObject>::CreateInstance(&dataObject);
						if (dataObject)
						{
							dataObject->AddRef();

							UINT nFormat = RegisterClipboardFormat("ASGraph-Item");

							HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(void*)*items.GetSize() + sizeof(int));
							if (hData)
							{
								void** p = (void**)GlobalLock(hData);

								p[0] = (void*)items.GetSize();
								for (int i = 0; i < items.GetSize(); i++)
								{
									p[1+i] = items[i];
								}

								GlobalUnlock(hData);

								CMyDropSource*  dropSource = new CMyDropSource;

								STGMEDIUM stgm;
								stgm.tymed = TYMED_HGLOBAL;
								stgm.pUnkForRelease = NULL;
								stgm.hGlobal = hData;

								FORMATETC etc = { nFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
								dataObject->SetData(&etc, &stgm, FALSE/*TRUE*/);

								DWORD dropEffect = 0;
								HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

								if (hr == DRAGDROP_S_DROP)
								{
									if (dropEffect & DROPEFFECT_MOVE)
									{
										m_pActiveItem = NULL;	// TODO ??

										if (nodeType == AS_ATTRIBUTE_DECLARATION)
										{
										}
										else
										{
											for (int i = 0; i < items.GetSize(); i++)
											{
												pParent->m_asCM->removeSubModel(items[i]);
											}

	#if 0
										// Rebuild parent
											{
												for (int i = 0; i < pParent->m_defs.GetSize(); i++)
												{
													delete pParent->m_defs[i];
												}
												pParent->m_defs.RemoveAll();
											}
											pParent->Build();
	#endif
										}

										//
	#if 0
										HDC hDC = CreateCompatibleDC(NULL);
										SetMapMode(hDC, MM_ANISOTROPIC);
										SetWindowExtEx(hDC, 10, 10, NULL);
										SetViewportExtEx(hDC, 1, 1, NULL);
										HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

										//pDef->OnSize(hDC);
										m_pRoot->Size(hDC);
										m_pRoot->m_outerRect = m_pRoot->m_innerRect;

										SelectObject(hDC, hOldFont);
										DeleteDC(hDC);
	#endif
									}
								}

								GlobalFree(hData);
							}

							dataObject->Release();
						}
					}
				}
			}

			Invalidate();
		}
	}
#endif
}

#if 0
long CASGraphCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_hFont = CreateFont(140, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Arial");

	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);

	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	::RegisterDragDrop(m_hWnd, this);

#if 0
	m_menuWnd.Create(m_hWnd, CRect(0, 0, 80, 120), NULL, WS_CHILD | WS_VISIBLE | WS_CAPTION, 0, 0);
#endif

	return 0;
}

LRESULT CASGraphCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::RevokeDragDrop(m_hWnd);

	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}

	return 0;
}

long CASGraphCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(&m_areaRect);

	return 0;
}

void CASGraphCtl::OnSize()
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

void __stdcall CASGraphCtl::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	CRect rect = m_areaRect;

	m_horz->put_pos(pos);
	ScrollWindow(oldPos-pos, 0, &rect, &rect);
}

void __stdcall CASGraphCtl::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect rect = m_areaRect;

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

HRESULT LoadMenu(int nResourceID, IMenuItem** pVal)
{
	HMENU hMenu = ::LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResourceID));

	if (hMenu)
	{
		CComObject<CMenuItem>* pMenu;
		CComObject<CMenuItem>::CreateInstance(&pMenu);
		if (pMenu)
		{
			pMenu->AddRef();

			BOOL b;
			pMenu->BuildFromHMenu(hMenu, &b);

			*pVal = pMenu;
		}

		DestroyMenu(hMenu);
	}

	return S_OK;
}

LRESULT CASGraphCtl::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CComPtr<IMenuItem> menu;

	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;

		if (pItem->m_asElement)
			LoadMenu(IDR_ASELEMENT, &menu);
		else if (pItem->m_asCM)
			LoadMenu(IDR_ASCONTENTMODEL, &menu);
	}

	if (menu)
	{
		CComPtr<IMenuItem> menu0;
		menu->GetSubMenu(0, &menu0);

		if (menu0)
		{
			long selectedID;
			menu0->PopupMenu(this, point, 0, &selectedID);
		}
	}

	return 0;
}
#endif

/*
STDMETHODIMP CASGraphCtl::get_undoManager(IOleUndoManager **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_undoManager;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CASGraphCtl::put_undoManager(IOleUndoManager *newVal)
{
	m_undoManager = newVal;
	return S_OK;
}
*/

IASModel* CASGraphCtl::get_asModel() const
{
	return m_asModel;
}

void CASGraphCtl::put_asModel(IASModel* newVal)
{
	m_asModel = newVal;
}

#if 0
STDMETHODIMP CASGraphCtl::get_asRootObject(IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_asDefinition;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

void CASGraphCtl::put_asRootObject(IASDeclaration *newVal)
{
	if (m_pRoot)
	{
		delete m_pRoot;
		m_pRoot = NULL;
	}

	m_asDefinition = newVal;

	if (m_asDefinition != NULL)
	{
//		CComObject<CDTDDesignElementDefinitionRoot>::CreateInstance(&m_pRoot);
		m_pRoot = new CDTDDesignContentModel;
//		m_pRoot->AddRef();
		m_pRoot->m_pCtl = this;
		m_pRoot->m_asObject = m_asDefinition;
		m_pRoot->m_asElement = dynamic_cast<IASDeclaration*>(m_asDefinition);
	//	m_pRoot->m_asDefinition = m_asDefinition;
		m_pRoot->Setup();
		m_pRoot->Build();

		AddRChild(m_pRoot);
#if 0
		HDC hDC = CreateCompatibleDC(NULL);
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 10, 10, NULL);
		SetViewportExtEx(hDC, 1, 1, NULL);
		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

		m_pRoot->Size(hDC);
		m_pRoot->m_outerRect = m_pRoot->m_innerRect;

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
#endif
	}

	/*
	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}
	*/
	InvalidateMeasure();
}

void CASGraphCtl::OnMeasure(LDraw::SizeD availSize)
{
	m_pRoot->Measure(LDraw::SizeD(0, 0));
	m_pRoot->m_outerRect = m_pRoot->m_innerRect;

	m_desiredSize.Width = m_pRoot->m_outerRect.Width();
	m_desiredSize.Height = m_pRoot->m_outerRect.Height();
}

void CASGraphCtl::OnArrange(LDraw::SizeD finalSize)
{
	m_pRoot->Arrange(m_pRoot->m_desiredSize);
	m_pRoot->SetLayoutOffset(-m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top);

	/*
	m_pRoot->m_outerRect = m_pRoot->m_innerRect;

	m_desiredSize.Width = m_pRoot->m_outerRect.Width();
	m_desiredSize.Height = m_pRoot->m_outerRect.Height();
	*/
}

#if 0
void CASGraphCtl::DrawInsertion(CDC& dc, CDTDDesignDefinition* pDef, CPoint pt)
{
	CRect rect = pDef->GetAbsInnerRect();

	rect.OffsetRect(-m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top);

	dc.BeginPath();

	dc.MoveTo(rect.left + pDef->m_width, rect.top + rect.Height()/2);
	dc.LineTo(rect.left + pDef->m_width+80+80, rect.top + rect.Height()/2);
	dc.LineTo(rect.left + pDef->m_width+80+80, pt.y);
	dc.LineTo(pt.x, pt.y);

	dc.EndPath();

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hOldPen = dc.SelectPen(pen);
	dc.WidenPath();
	dc.SelectPen(hOldPen);

	CRgn rgn;
	rgn.CreateFromPath(dc);

	{
		CBrush brush = CDC::GetHalftoneBrush();
		HBRUSH hBrushOld = dc.SelectBrush(brush);

		// draw into the update/new region
		dc.SelectClipRgn(rgn);
		CRect rect;
		dc.GetClipBox(&rect);
		hBrushOld = dc.SelectBrush(brush);
		dc.PatBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, PATINVERT);

		// cleanup DC
		//if(hBrushOld != NULL)
		dc.SelectBrush(hBrushOld);
		dc.SelectClipRgn(NULL);
	}
}
#endif

IASObject* GetNextSibling(IASObjectList* objectList, IASObject* object)
{
	long length = objectList->get_length();
	for (int i = 0; i < length; i++)
	{
		IASObject* o = objectList->item(i);
		if (o == object)
		{
			break;
		}
	}

	if (i < length-1)
	{
		IASObject* o = objectList->item(i+1);

		return o;
	}
	else
		return NULL;
}

#if 0
////////////////////////////////////
// IDropTarget
STDMETHODIMP CASGraphCtl::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	COleDataObjectWrapper dataObject;
	dataObject.Attach(pDataObject);

	HGLOBAL hData;
	if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("ASGraph-Item")))
	{
	}

	return S_OK;
}

STDMETHODIMP CASGraphCtl::DragOver(DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	CPoint point;
	point.x = ptl.x;
	point.y = ptl.y;

	ScreenToClient(&point);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_pRoot)
	{
		CPoint pt = point;
		pt.x += scrollposX;
		pt.y += scrollposY;

		pt.x *= 10;
		pt.y *= 10;
		pt.x /= m_magnify;
		pt.y /= m_magnify;

		pt.x -= m_pRoot->m_outerRect.left;
		pt.y -= m_pRoot->m_outerRect.top;

		CClientDC dc(m_hWnd);

		int state = dc.SaveDC();

		dc.SetMapMode(MM_ANISOTROPIC);
		dc.SetWindowExt(100, 100);
		dc.SetWindowOrg(0, 0);
		dc.SetViewportExt(10*m_magnify, 10*m_magnify);
		dc.SetViewportOrg(-scrollposX, -scrollposY);

		dc.OffsetWindowOrg(-m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top);

		dc.SetROP2(R2_NOT);

		if (m_pDef)
		{
			DrawInsertion(dc, m_pDef, m_oldpt);
			m_pDef = NULL;
		}

		CDTDDesignDefinition* pDef = m_pRoot->GetInsertion(pt, m_pBeforeDef);
		if (pDef)
		{
			DrawInsertion(dc, pDef, pt);

			m_pDef = pDef;

			if (grfKeyState & MK_CONTROL)
				*pdwEffect = DROPEFFECT_COPY;
			else
				*pdwEffect = DROPEFFECT_MOVE;
		}

		dc.RestoreDC(state);

		m_oldpt = pt;
	}

	return S_OK;
}

STDMETHODIMP CASGraphCtl::DragLeave()
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	CClientDC dc(m_hWnd);

	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(100, 100);
	dc.SetWindowOrg(0, 0);
	dc.SetViewportExt(10*m_magnify, 10*m_magnify);
	dc.SetViewportOrg(-scrollposX, -scrollposY);

	dc.OffsetWindowOrg(-m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top);

	dc.SetROP2(R2_NOTXORPEN);

	if (m_pDef)
	{
		DrawInsertion(dc, m_pDef, m_oldpt);
		m_pDef = NULL;
	}

	return S_OK;
}

STDMETHODIMP CASGraphCtl::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	*pdwEffect = DROPEFFECT_NONE;

	if (m_pDef)
	{
		CClientDC dc(m_hWnd);

		dc.SetMapMode(MM_ANISOTROPIC);
		dc.SetWindowExt(100, 100);
		dc.SetWindowOrg(0, 0);
		dc.SetViewportExt(10*m_magnify, 10*m_magnify);
		dc.SetViewportOrg(-scrollposX, -scrollposY);

		dc.OffsetWindowOrg(-m_pRoot->m_outerRect.left, -m_pRoot->m_outerRect.top);

		dc.SetROP2(R2_NOTXORPEN);

		DrawInsertion(dc, m_pDef, m_oldpt);

	///
		/*
		CPoint point;
		point.x = pt.x;
		point.y = pt.y;
		ScreenToClient(&point);
		*/

		COleDataObjectWrapper dataObject;
		dataObject.Attach(pDataObject);

		HGLOBAL hData;
		if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("ASGraph-Item")))
		{
			void** p = (void**)GlobalLock(hData);
			if (p)
			{
				int nCount = (int)p[0];
				IASObject** pObjects = (IASObject**)&p[1];

				CDTDDesignContentModel* pDef = (CDTDDesignContentModel*)m_pDef;

				_ASObjectType nodeType;
				pObjects[0]->get_asNodeType(&nodeType);
				if (nodeType == AS_ATTRIBUTE_DECLARATION)
				{
					for (int i = 0; i < nCount; i++)
					{
						CComPtr<IASObject> asObject;
						pObjects[i]->cloneASObject(VARIANT_TRUE, &asObject);

						CComPtr<IASDataTypeDeclaration> dataType;
						pDef->m_asElement->get_elementDataType(&dataType);
						if (dataType)
						{
							CComQIPtr<IASComplexTypeDeclaration> complexType = dataType;
							if (complexType)
							{
							//	CComPtr<IASNamedObjectMap> attributes;
							//	complexType->get_ASAttributeDecls(&attributes);

							//	CComPtr<IASObject> p;
							//	attributes->setNamedItem(asObject, &p);
								complexType->addASAttributeDecl((IASAttributeDeclaration*)asObject.p);

								pDef->BuildAttributes();
							}
							else
							{
								MessageBox("Needs to create complexType", "", MB_OK);
							}
						}
						else
							MessageBox("No dataType", "", MB_OK);
					}

					if (grfKeyState & MK_CONTROL)
						*pdwEffect = DROPEFFECT_COPY;
					else
						*pdwEffect = DROPEFFECT_MOVE;
				}
				else
				{
					CComPtr<IASObjectList> objectList;
					pDef->m_asCM->get_subModels(&objectList);

					int n = 0;
					for (int i = 0; i < nCount; i++)
					{
						IASObject* nextObject = GetNextSibling(objectList, pObjects[i]);

						/*
						if (	(pObjects[i] != ((m_pBeforeDef)?m_pBeforeDef->m_asObject: NULL)) &&
								(nextObject != ((m_pBeforeDef)?m_pBeforeDef->m_asObject: NULL)))
						*/
						{
							MessageBeep(-1);

							CComPtr<IASObject> asObject;
							pObjects[i]->cloneASObject(VARIANT_TRUE, &asObject);

							if (pDef->m_asElement == NULL)
							{
								CComPtr<IASObject> result;
								pDef->m_asCM->insertBeforeSubModel(asObject, (m_pBeforeDef)?m_pBeforeDef->m_asObject: NULL, &result);
							}
							else
								ATLASSERT(0);

							n++;
						}
					}

					if (n)
					{
#if 0
						// Rebuild parent
						{
							for (int i = 0; i < pDef->m_defs.GetSize(); i++)
							{
								delete pDef->m_defs[i];
							}
							pDef->m_defs.RemoveAll();
						}
						pDef->Build();
#endif
					}

					if (grfKeyState & MK_CONTROL)
						*pdwEffect = DROPEFFECT_COPY;
					else
						*pdwEffect = DROPEFFECT_MOVE;
				}

				if (*pdwEffect)
				{
					// UpdateView();
				}

				GlobalUnlock(hData);
			}
		}

		m_pDef = NULL;
	}

	return S_OK;
}

void CASGraphCtl::UpdateView()
{
	// Resize
	HDC hDC = CreateCompatibleDC(NULL);
	SetMapMode(hDC, MM_ANISOTROPIC);
	SetWindowExtEx(hDC, 10, 10, NULL);
	SetViewportExtEx(hDC, 1, 1, NULL);
	HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

	//pDef->OnSize(hDC);
	m_pRoot->Size(hDC);
	m_pRoot->m_outerRect = m_pRoot->m_innerRect;

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	Invalidate();
}
#endif

STDMETHODIMP CASGraphCtl::get_ActiveItem(CDTDDesignSchemaNode **pVal)
{
	*pVal = m_pActiveItem;
	return S_OK;
}

#if 0
STDMETHODIMP CASGraphCtl::putref_ActiveItem(IASDesignObject *newVal)
{
	ATLASSERT(0);
	return E_NOTIMPL;
}
#endif

////////////////////////////////////

#if 0
BEGIN_CMD_MAP(CASGraphCtl)
//	CMD_HANDLER(ID_VIEW_ZOOMOUT, OnViewZoomout)
//	CMD_HANDLER(ID_VIEW_ZOOMIN, OnViewZoomin)

	CMD_HANDLER(ID_ASGRAPH_CHANGEMODEL_SEQUENCE, OnASGraphChangeModelSequence)
	CMD_HANDLER(ID_ASGRAPH_CHANGEMODEL_CHOICE, OnASGraphChangeModelChoice)
	CMD_HANDLER(ID_ASGRAPH_CHANGEMODEL_ALL, OnASGraphChangeModelAll)
	CMD_HANDLER(ID_ASGRAPH_OPTIONAL, OnASGraphOptional)
	CMD_HANDLER(ID_ASGRAPH_UNBOUNDED, OnASGraphUnbounded)

	CMD_UPDATE(ID_ASGRAPH_CHANGEMODEL_SEQUENCE, OnASGraphChangeModelSequenceUpdate)
	CMD_UPDATE(ID_ASGRAPH_CHANGEMODEL_CHOICE, OnASGraphChangeModelChoiceUpdate)
	CMD_UPDATE(ID_ASGRAPH_CHANGEMODEL_ALL, OnASGraphChangeModelAllUpdate)

	CMD_UPDATE(ID_ASGRAPH_OPTIONAL, OnASGraphOptionalUpdate)
	CMD_UPDATE(ID_ASGRAPH_UNBOUNDED, OnASGraphUnboundedUpdate)
END_CMD_MAP()
#endif

#if 0
LRESULT CASGraphCtl::OnViewZoomout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_magnify /= 2;
	OnSize();
	InvalidateRect(&m_areaRect);

	return 0;
}

LRESULT CASGraphCtl::OnViewZoomin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_magnify *= 2;
	OnSize();
	InvalidateRect(&m_areaRect);

	return 0;
}
#endif

LRESULT CASGraphCtl::OnASGraphChangeModelSequence(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		if (pItem->m_asElement == NULL)
		{
			_ASContentModelTypeOp op = pItem->Get_asCM()->get_listOperator();
			if (op != AS_SEQUENCE)
			{
				pItem->Get_asCM()->put_listOperator(AS_SEQUENCE);

				Invalidate();
			}
		}
	}

	return 0;
}

LRESULT CASGraphCtl::OnASGraphChangeModelChoice(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		if (pItem->m_asElement == NULL)
		{
			_ASContentModelTypeOp op = pItem->Get_asCM()->get_listOperator();
			if (op != AS_CHOICE)
			{
				pItem->Get_asCM()->put_listOperator(AS_CHOICE);

				Invalidate();
			}
		}
	}

	return 0;
}

LRESULT CASGraphCtl::OnASGraphChangeModelAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		if (pItem->m_asElement == NULL)
		{
			_ASContentModelTypeOp op = pItem->Get_asCM()->get_listOperator();
			if (op != AS_ALL)
			{
				pItem->Get_asCM()->put_listOperator(AS_ALL);

				Invalidate();
			}
		}
	}

	return 0;
}

void CASGraphCtl::OnASGraphChangeModelSequenceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		if (pItem->m_asElement == NULL)
		{
			_ASContentModelTypeOp op = pItem->Get_asCM()->get_listOperator();

			pCmdUI->SetCheck(op == AS_SEQUENCE);

			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

void CASGraphCtl::OnASGraphChangeModelChoiceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		if (pItem->m_asElement == NULL)
		{
			_ASContentModelTypeOp op = pItem->Get_asCM()->get_listOperator();

			pCmdUI->SetCheck(op == AS_CHOICE);

			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

void CASGraphCtl::OnASGraphChangeModelAllUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		if (pItem->m_asElement == NULL)
		{
			_ASContentModelTypeOp op = pItem->Get_asCM()->get_listOperator();

			pCmdUI->SetCheck(op == AS_ALL);

			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CASGraphCtl::OnASGraphOptional(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;

		if (pItem->IsOptional())
			pItem->RemoveOptionalUnbounded(m_asModel, true, false);
		else
			pItem->SetOptionalUnbounded(m_asModel, true, false);

		HDC hDC = CreateCompatibleDC(NULL);
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 10, 10, NULL);
		SetViewportExtEx(hDC, 1, 1, NULL);
		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

		m_pRoot->Size(hDC);
		m_pRoot->m_outerRect = m_pRoot->m_innerRect;

		OnSize();

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);

		Invalidate();
	}
#endif
	return 0;
}

LRESULT CASGraphCtl::OnASGraphUnbounded(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;

		if (pItem->IsUnbounded())
			pItem->RemoveOptionalUnbounded(m_asModel, false, true);
		else
			pItem->SetOptionalUnbounded(m_asModel, false, true);

		HDC hDC = CreateCompatibleDC(NULL);
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 10, 10, NULL);
		SetViewportExtEx(hDC, 1, 1, NULL);
		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);

		m_pRoot->Size(hDC);
		m_pRoot->m_outerRect = m_pRoot->m_innerRect;

		OnSize();

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);

		Invalidate();
	}
#endif

	return 0;
}

void CASGraphCtl::OnASGraphOptionalUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		pCmdUI->SetCheck(pItem->IsOptional());

		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

void CASGraphCtl::OnASGraphUnboundedUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pActiveItem)
	{
		CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)m_pActiveItem;
		pCmdUI->SetCheck(pItem->IsUnbounded());

		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}
