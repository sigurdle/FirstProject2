// XMLGridCtl.cpp : Implementation of CXMLGridCtl

#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridCtl.h"

#include "XMLGridNode.h"
#include "XMLGridDocument.h"
#include "XMLGridDocType.h"
#include "XMLGridElement.h"
#include "XMLGridAttribute.h"
#include "XMLGridCharacterData.h"
#include "XMLGridEntityReference.h"
#include "XMLGridProcessingInstruction.h"
#include "XMLGridNotWellformed.h"
#include "XMLGridTable.h"

#include "..\OleDataObject.h"
//#include "..\UIT\UIT.h"

#if 0
class COleDataObjectWrapper
{
protected:
	LPDATAOBJECT m_pDataObject;

public:
	void Attach(LPDATAOBJECT dataObject)
	{
		m_pDataObject = dataObject;
	}
	
	HGLOBAL GetGlobalData(UINT nClipboardFormat)
	{
		FORMATETC fetc = {0};
		fetc.cfFormat = nClipboardFormat;
		fetc.tymed = TYMED_HGLOBAL;
		fetc.dwAspect = DVASPECT_CONTENT;
		fetc.lindex = -1;			//	give me all

		STGMEDIUM medium = {0};
		medium.tymed = TYMED_HGLOBAL;

		HRESULT hr = m_pDataObject->GetData(&fetc, &medium);
		if (SUCCEEDED(hr))
		{
			return medium.hGlobal;
		}

		return NULL;
	}
};
#endif

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr)
{
	/*
	HPEN hPen = CreatePen(PS_SOLID, 1, clr);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	MoveToEx(hDC, rc->left, rc->bottom-1, NULL);
	LineTo(hDC, rc->left, rc->top);
	LineTo(hDC, rc->right, rc->top);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	*/
};

void DrawBottomRight(UI::Graphics* pGraphics, const LDraw::RectD& rc, LDraw::Color clr)
{
//	HPEN hPen = CreatePen(PS_SOLID, 1, clr);
//	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	pGraphics->FillRectangle(new LDraw::SolidBrush(clr), rc.GetLeft(), rc.GetBottom(), rc.Width, 1);
	pGraphics->FillRectangle(new LDraw::SolidBrush(clr), rc.GetRight(), rc.GetTop(), 1, rc.Height);

//	MoveToEx(hDC, rc->left, rc->bottom, NULL);
//	LineTo(hDC, rc->right, rc->bottom);
//	LineTo(hDC, rc->right, rc->top-1);

//	SelectObject(hDC, hOldPen);
//	DeleteObject(hPen);
};

/////////////////////////////////////////////////////////////////////////////

#if 0
STDMETHODIMP CFontNotifyImpl::OnChanged(DISPID dispid)
{
	ATLTRACE(_T("OnChanged sink: %x\n"),this);
	m_pParent->FireViewChange();
	return S_OK;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CXMLGridCtl

CXMLGridCtl::CXMLGridCtl()// : m_wndEdit(NULL, this, 1)
{
	//m_bWindowOnly = TRUE;

	m_pTree = NULL;
	m_dragging = 0;
	m_pElement = NULL;

	m_pActiveItem = NULL;
	m_pLastFocus = NULL;
	m_commonAncestor = NULL;

	m_pDragOverItem = NULL;
	m_pDragParentItem = NULL;
	m_pDragBeforeItem = NULL;

#if 0
	m_buttonRect.SetRectEmpty();
#endif

	m_userKey = NULL;

//	ATLASSERT(m_wndEdit.m_hWnd == NULL);

//	m_pFontNotifySink = NULL;

//	m_hFont[0] = NULL;
//	m_hFont[1] = NULL;
//	m_hFont[2] = NULL;

	//m_hWndEdit = NULL;
}

#if 0
int CXMLGridCtl::FinalConstruct()
{
	m_horz.CoCreateInstance(CLSID_UIScrollBar);
	m_horz->put_direction(0);

	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);

	GUID guid;
	::CoCreateGuid(&guid);
	::StringFromCLSID(guid, &m_userKey);

	CComObject<CFontNotifyImpl>::CreateInstance(&m_pFontNotifySink);
	m_pFontNotifySink->AddRef();
	m_pFontNotifySink->SetParent(this);

	return S_OK;
}

void CXMLGridCtl::FinalRelease()
{
	if (m_pFontNotifySink)
	{
		m_pFontNotifySink->Release();
		m_pFontNotifySink = NULL;
	}

	if (m_userKey)
	{
		::CoTaskMemFree(m_userKey);
		m_userKey = NULL;
	}
}
#endif

#if 0
LRESULT CXMLGridCtl::OnEditChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CGridItem* pNode = (CGridItem*)m_wndEdit.GetWindowLong(/*m_hWndEdit,*/ GWL_USERDATA);

	HDC hDC = CreateCompatibleDC(NULL);

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	pNode->OnEditChange(hDC, m_pTree);

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	Invalidate();
	OnSize();

	return 0;
}

LRESULT CXMLGridCtl::OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CGridItem* pNode = (CGridItem*)m_wndEdit.GetWindowLong(/*m_hWndEdit,*/ GWL_USERDATA);

	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
		pNode->EndEdit(/*this*/);
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

STDMETHODIMP CXMLGridCtl::DisplayAsTable()
{
	if (m_pActiveItem)
	{
		CGridElement* pActiveElement = (CGridElement*)m_pActiveItem;

		sysstring tagName = pActiveElement->GetNodeName();

		CGridContainer* pParent = m_pActiveItem->m_parent;

		CComObject<CGridTable>* pTable;
		CComObject<CGridTable>::CreateInstance(&pTable);
		pTable->AddRef();
		pTable->m_pUI = this;

		pTable->m_name = tagName;

		UPOSITION pos = pParent->m_childList.Find(m_pActiveItem);

	// Find the first sibling with same tagName
		UPOSITION firstPos = pos;

		UPOSITION pos2 = firstPos;
		m_pActiveItem->m_parent->m_childList.GetPrev(pos2);
		while (pos2)
		{
			UPOSITION pos3 = pos2;
			CGridElement* pNode2 = (CGridElement*)pParent->m_childList.GetPrev(pos2);

			BSTR btagName2;
			pNode2->m_domNode->get_nodeName(&btagName2);
			sysstring tagName2 = sysstring(btagName2, false);

			if (wcscmp(tagName, tagName2))
				break;

			firstPos = pos3;
		}

		pos2 = firstPos;
		UPOSITION afterLast = NULL;
		while (pos2)
		{
			afterLast = pos2;
			CGridElement* pNode2 = (CGridElement*)pParent->m_childList.GetNext(pos2);

			BSTR btagName2;
			pNode2->m_domNode->get_nodeName(&btagName2);
			sysstring tagName2 = sysstring(btagName2, false);

			if (wcscmp(tagName, tagName2))
				break;

		// Remove from previous parent
			pParent->m_childList.RemoveAt(afterLast);

		// Add as child on table
			pNode2->m_parent = pTable;
			pTable->m_childList.AddTail(pNode2);
		}

		pTable->BuildAttrDecls();

		pTable->m_parent = pParent;
		if (pos2)
			pParent->m_childList.InsertBefore(afterLast, pTable);
		else
			pParent->m_childList.AddTail(pTable);

		HDC hDC = CreateCompatibleDC(NULL);

		CComQIPtr<IFont> font = m_pFont;
		HFONT hFont;
		font->get_hFont(&hFont);

		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
		m_pTree->SizeContent(hDC, m_pTree->m_size.cx);
		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);

		OnSize();
		Invalidate();
	}

	return S_OK;
}
#endif

void CXMLGridCtl::OnRender(UI::Graphics* pGraphics)
{
#if 0
	HDC hDC = di.hdcDraw;

	int state = SaveDC(hDC);

	IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
#endif

	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, m_computedSize.Width, m_computedSize.Height);

	if (m_pTree)
	{
		m_pTree->DrawContent(NULL, false);
		DrawBottomRight(pGraphics, LDraw::RectD(0, 0, m_pTree->m_computedSize.Width, m_pTree->m_computedSize.Height), LDraw::Color(200, 200, 200));
	}

#if 0
	RestoreDC(hDC, state);

	if (m_pDragOverItem)
	{
		int oldR2 = SetROP2(hDC, R2_XORPEN);

		DrawInsertionMarker(hDC);

		SetROP2(hDC, oldR2);
	}
#endif
}

#if 0
void __stdcall CXMLGridCtl::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	CRect	rect = m_areaRect;

	m_horz->put_pos(pos);
	ScrollWindow(oldPos-pos, 0, &rect, &rect);

	if (m_wndEdit.m_hWnd)
	{
		CRect rect;
		m_wndEdit.GetWindowRect(&rect);
		ScreenToClient(&rect);

		m_wndEdit.SetWindowPos(NULL, rect.left + oldPos-pos, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
}

void __stdcall CXMLGridCtl::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);

	if (m_wndEdit.m_hWnd)
	{
		CRect rect;
		m_wndEdit.GetWindowRect(&rect);
		ScreenToClient(&rect);

		m_wndEdit.SetWindowPos(NULL, rect.left, rect.top + oldPos-pos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
}

void CXMLGridCtl::CreateFonts()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_hFont[i])
		{
			DeleteObject(m_hFont[i]);
			m_hFont[i] = NULL;
		}
	}

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	LOGFONT lf;
	GetObject(hFont, sizeof(lf), &lf);

	lf.lfWeight = FW_BOLD;
	m_hFont[Font_ElementName] = CreateFontIndirect(&lf);

	lf.lfWeight = FW_BOLD;
	m_hFont[Font_AttributeName] = CreateFontIndirect(&lf);

	lf.lfWeight = FW_NORMAL;
	m_hFont[Font_Content] = CreateFontIndirect(&lf);
}

LRESULT CXMLGridCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);
	IDispEventImpl<1, CXMLGridCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<2, CXMLGridCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	if (m_document)
	{
		// Add listeners
		/*
		IDispEventImpl<3, CXMLGridCtl, &DIID__ILDOMDocumentContainerEvents, &LIBID_SVGLib, 1, 0>::DispEventAdvise(m_documentContainer);

		CComQIPtr<ILDOMDocument> domdocument;
		m_documentContainer->get_document(&domdocument);

		cnt_setDocument(domdocument);
		*/

		InitTree();
	}

	CreateFonts();

	::RegisterDragDrop(m_hWnd, this);

	return 0;
}

LRESULT CXMLGridCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RevokeDragDrop(m_hWnd);	// Revoke base class

	IDispEventImpl<1, CXMLGridCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, CXMLGridCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	// TODO, remove listeners
	/*
	if (m_documentContainer)
	{
		IDispEventImpl<3, CXMLGridCtl, &DIID__ILDOMDocumentContainerEvents, &LIBID_SVGLib, 1, 0>::DispEventUnadvise(m_documentContainer);
	}
	*/

	return 0;
}

long CXMLGridCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();

	return 0;
}

void CXMLGridCtl::OnSize()
{
	CRect client;
	GetClientRect(&client);

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	int maxx = 0;
	int maxy = 0;

	if (m_pTree)
	{
		maxx = m_pTree->m_size.cx;
		maxy = m_pTree->m_size.cy;
	}

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right;
	m_areaRect.bottom = client.bottom;

	BOOL bVertSB = FALSE;
	BOOL bHorzSB = FALSE;

	if (maxx > m_areaRect.right)
	{
		m_areaRect.bottom -= sbHeight;
		bHorzSB = TRUE;
	}

	if (maxy > m_areaRect.bottom)
	{
		m_areaRect.right -= sbWidth;
		bVertSB = TRUE;
	}

	if (!bHorzSB)
	{
		if (maxx > m_areaRect.right)
		{
			m_areaRect.bottom -= sbHeight;
			bHorzSB = TRUE;
		}
	}

	if (bVertSB)
	{
		m_vert->SetInfo(0, maxy, m_areaRect.Height());

		m_axvert.MoveWindow(m_areaRect.right, 0, sbWidth, m_areaRect.Height());
		m_axvert.ShowWindow(SW_SHOW);
	}
	else
	{
		m_vert->SetInfo(0, 0, 0);
		m_axvert.ShowWindow(SW_HIDE);
	}

	if (bHorzSB)
	{
		m_horz->SetInfo(0, maxx, m_areaRect.Width());

		m_axhorz.MoveWindow(0, m_areaRect.bottom, m_areaRect.Width(), sbHeight);
		m_axhorz.ShowWindow(SW_SHOW);
	}
	else
	{
		m_horz->SetInfo(0, 0, 0);
		m_axhorz.ShowWindow(SW_HIDE);
	}
}

CGridContainer* FindCommonAncestor(CGridItem* node1, CGridItem* node2)
{
//	CComPtr<ILDOMNode> parentNode1;
//	node1->get_parentNode(&parentNode1);

	CArray<CGridContainer*,CGridContainer*> arr1;
	CArray<CGridContainer*,CGridContainer*> arr2;

	{
		CGridContainer* parentNode = node1->m_parent;
		//node1->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr1.Add(parentNode);

			parentNode = parentNode->m_parent;
		}
	}

	{
		CGridContainer* parentNode = node2->m_parent;
		//node2->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr2.Add(parentNode);

			parentNode = parentNode->m_parent;
		}
	}

	for (int i = 0; i < arr1.GetSize(); i++)
	{
		for (int j = 0; j < arr2.GetSize(); j++)
		{
			if (arr1[i] == arr2[j])
				return arr1[i];
		}
	}

	ATLASSERT(0); //???? if the container(s) is the document, then this will be validly NULL
	return NULL;
}

BOOL Select(CGridItem* pContainer, CGridItem* start, CGridItem* end, BOOL bSelected)
{
	UPOSITION pos = pContainer->m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pNode = (CGridItem*)pContainer->m_childList.GetNext(pos);

		if (!bSelected)
		{
			if (pNode == start)
			{
				bSelected = TRUE;
			}
		}

		BOOL bSelected2 = Select(pNode, start, end, bSelected);

		if (bSelected && !bSelected2)
			return bSelected2;

		if (bSelected && bSelected2)
		{
			pNode->m_selected = bSelected;
		}

		bSelected = bSelected2;

		if (bSelected)
		{
			if (pNode == end)
			{
				bSelected = FALSE;
			}
		}
	}

	return bSelected;
}
#endif

#if 0
void CXMLGridCtl::Select(CGridItem* start, CGridItem* end)
{
	m_commonAncestor = FindCommonAncestor(start, end);

	bool bSelect = FALSE;

	::Select(m_commonAncestor, start, end, bSelect);

/*
	UPOSITION startPos;
	start->m_parent->m_childList.Find(start);

	UPOSITION pos = startPos;
	while (pos)
	{
		CGridNode* pNode = (CGridNode*)start->m_parent->m_childList.GetNext(pos);
		pNode->m_selected = true;
	}
	*/
}

LRESULT CXMLGridCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_wndEdit.m_hWnd)
	{
		CGridItem* pNode = (CGridItem*)m_wndEdit.GetWindowLong(/*m_hWndEdit,*/ GWL_USERDATA);
		pNode->EndEdit(/*this*/);
		//m_hWndEdit = NULL;
	}

	SetFocus();

	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	point.x += scrollposX;
	point.y += scrollposY;

	if (!m_dragging)
	{
		if (m_pTree)
		{
			HDC hDC = GetDC();
			HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

			POINT oldOrg;
			SetViewportOrgEx(hDC, -scrollposX, -scrollposY, &oldOrg);

			CGridItem* pNode;
			int nClick = m_pTree->ClickContent(hDC, point, nFlags, FALSE, &pNode);

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			SelectObject(hDC, hOldFont);
			ReleaseDC(hDC);

			if (nClick == 1)
			{
				if (m_pLastFocus == NULL)
				{
					m_pLastFocus = pNode;
				}

				if (nFlags & MK_SHIFT)
				{
					if (m_commonAncestor)
					{
						m_commonAncestor->Deselect();
					}

					Select(m_pLastFocus, pNode);

					m_pActiveItem = pNode;

					InvalidateRect(NULL, TRUE);
				}
				else
				{
					SelectItem(pNode);

					InvalidateRect(NULL, TRUE);
				//	UpdateWindow();

#if 0	// Have this
					CComObject<COleDataObject>* pDataObject;
					CComObject<COleDataObject>::CreateInstance(&pDataObject);
					if (pDataObject)
					{
						pDataObject->AddRef();

						CMyDropSource*  pDropSource = new CMyDropSource;

						CComPtr<IStream> stream;
						HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE/*deleteOnRelease*/, &stream);

						m_commonAncestor->BuildSelectedXML(stream);

						HGLOBAL hData;
						::GetHGlobalFromStream(stream, &hData);
						if (hData)
						{
							STGMEDIUM stgm;
							stgm.tymed = TYMED_HGLOBAL;
							stgm.pUnkForRelease = NULL;
							stgm.hGlobal = hData;

							UINT nFormat = RegisterClipboardFormat("LXMLGrid");

							FORMATETC etc = { nFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
							pDataObject->SetData(&etc, &stgm, FALSE/*TRUE*/ /*fRelese*/);

							DWORD dropEffect = 0;
							if (::DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect) == DRAGDROP_S_DROP)
							{
								if (dropEffect & DROPEFFECT_MOVE)
								{
									DeleteSelected(m_commonAncestor);
								}
							}
						}

						GlobalFree(hData);

						pDataObject->Release();
					}
#endif
				}

				if (m_pActiveItem)
				{

					//m_pActiveNode->m_selected = true;

#if 0
					Fire_OnSelectNode(((CGridElement*)m_pActiveNode)->m_domElement);
#endif
				}
			}

		//	OnSize();	// TODO remove, don't always do this
		}
	}

	return 0;
}

LRESULT CXMLGridCtl::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	point.x += scrollposX;
	point.y += scrollposY;

	if (m_pActiveItem)
	{
		HDC hDC = GetDC();

		CComQIPtr<IFont> font = m_pFont;
		HFONT hFont;
		font->get_hFont(&hFont);

		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

		POINT oldOrg;
		SetViewportOrgEx(hDC, -scrollposX, -scrollposY, &oldOrg);

		CGridItem* pNode;
		int nClick = m_pTree->ClickContent(hDC, point, nFlags, TRUE, &pNode);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		SelectObject(hDC, hOldFont);
		ReleaseDC(hDC);
	}

	return 0;
}

long CXMLGridCtl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_dragging = 0;
		ReleaseCapture();
	}

	return 0;
}

long CXMLGridCtl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	point.x += scrollposX;
	point.y += scrollposY;

/*
	if (m_dragging)
	{
		if (PtInRect(&m_buttonRect, point))
		{
			m_pElement->m_expanded = !m_pElement->m_expanded;
			m_pElement->DownSize();

			OnSize();
		}
	}
*/

	return 0;
}

void CXMLGridCtl::InitTree()
{
	if (m_pTree)
	{
		delete m_pTree;
		m_pTree = NULL;
	}

	if (m_document)
	{
		CGridNode* pElement;
		CreateGridNode(m_document, &pElement);
		//CComObject<CGridElement>* pElement;
		//CComObject<CGridElement>::CreateInstance(&pElement);
		if (pElement)
		{
		//	pElement->AddRef();
		//	pElement->m_pUI = this;
		//	pElement->m_domNode = m_document;

		//	pElement->m_domNode->setUserData(m_userKey, pElement, NULL, NULL);

			pElement->BuildChildren();

			m_pTree = (CGridContainerNode*)pElement;
			m_pTree->m_expanded = TRUE;
		}

		HDC hDC = CreateCompatibleDC(NULL);

		CComQIPtr<IFont> font = m_pFont;
		HFONT hFont;
		font->get_hFont(&hFont);

		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
		m_pTree->SizeContent(hDC, 0);
	//	m_pTree->SizeContent(hDC, 0);
		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
	}
}

HRESULT CXMLGridCtl::FireOnChanged(DISPID dispID)
{
	CreateFonts();

	if (m_hWnd)
	{
		//CComQIPtr<IFont> font = m_pFont;
		//HFONT hFont;
		//font->get_hFont(&hFont);

		HDC hDC = CreateCompatibleDC(NULL);
		HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);//SelectObject(hDC, hFont);
		m_pTree->SizeContent(hDC, m_pTree->m_size.cx);
		SelectObject(hDC, hOldFont);

	//	Invalidate();

		DeleteDC(hDC);
	}

	return S_OK;// TODO ??CComControlBase::FireOnChanged(GetUnknown(), dispID);
}

void CXMLGridCtl::DeleteSelected(CGridItem* pContainer)
{
	UPOSITION pos = pContainer->m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pNode = (CGridItem*)pContainer->m_childList.GetNext(pos);

		if (pNode->m_selected)
		{
			CComQIPtr<ILDOMAttr> attr = pNode->m_domNode;
			if (attr)
			{
				CComPtr<ILDOMElement> element;
				attr->get_ownerElement(&element);

				element->removeAttribute(pNode->GetNodeName());
			}
			else
			{
				CComPtr<ILDOMNode> parentNode;
				pNode->m_domNode->get_parentNode(&parentNode);

				parentNode->removeChild(pNode->m_domNode, NULL);
			}
		}
		else
		{
			DeleteSelected(pNode);
		}
	}
}

LRESULT CXMLGridCtl::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == VK_DELETE)
	{
		if (m_commonAncestor)
		{
			DeleteSelected(m_commonAncestor);
		}

#if 0
		if (m_pActiveNode)
		{
		//	CGridNode* pGridNode = static_cast<CGridNode*>(m_pActiveNode);

			CComPtr<ILDOMNode> parentNode;
			m_pActiveNode->m_domElement->get_parentNode(&parentNode);

			parentNode->removeChild(m_pActiveNode->m_domElement, NULL);
		}
#endif
	}

	return 0;
}
#endif

#if 0
HRESULT __stdcall CXMLGridCtl::cnt_beforesetDocument()
{
	delete m_pTree;
	m_pTree = NULL;

	return S_OK;
}

HRESULT __stdcall CXMLGridCtl::cnt_setDocument(ILDOMDocument* document)
{
	if (document)
	{

		InvalidateRect(NULL, TRUE);
		OnSize();
	}

	return S_OK;
}

HRESULT __stdcall CXMLGridCtl::cnt_insertedNode(ILDOMNode* node)
{
	ATLASSERT(m_pTree != NULL);

	CComQIPtr<ILDOMNode> parentNode;
	node->get_parentNode(&parentNode);

	CGridElement* pParent = m_pTree->FindDOMElement(parentNode);
	if (pParent)
	{
		ATLASSERT(pParent);
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CGridElement* pElement = pParent->BuildTree(element);
			pElement->Size();

			UPOSITION pos = pParent->m_childList.GetHeadPosition();

			CComQIPtr<ILDOMNode> child;
			element->get_previousSibling(&child);

			while (child != NULL)
			{
				if (pParent->FindDOMElement(child))
				{
					pParent->m_childList.GetNext(pos);
				}

				CComQIPtr<ILDOMNode> prevSibling;
				child->get_previousSibling(&prevSibling);
				child = prevSibling;
			}

			pElement->m_parent = pParent;
			if (pos)
				pParent->m_childList.InsertBefore(pos, pElement);
			else
				pParent->m_childList.AddTail(pElement);
		}
	}

	InvalidateRect(NULL, TRUE);
	OnSize();

	return S_OK;
}

HRESULT __stdcall CXMLGridCtl::cnt_beforeRemovedNode(ILDOMNode* node)
{
	return S_OK;
}

HRESULT __stdcall CXMLGridCtl::cnt_afterRemovedNode(ILDOMNode* node)
{
	return S_OK;
}

HRESULT __stdcall CXMLGridCtl::cnt_changedAttribute(ILDOMNode* node, BSTR attrName, short changeType, BSTR prevValue)
{
	return S_OK;
}

HRESULT __stdcall CXMLGridCtl::cnt_changedTextContentNode(ILDOMNode* node, BSTR oldvalue)
{
	return S_OK;
}
#endif

#if 0
STDMETHODIMP CXMLGridCtl::get_xmlDocument(IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::put_xmlDocument(IUnknown *newVal)
{
	if (m_document)
	{
		CComQIPtr<ILDOMEventTarget> eventTarget = m_document;

	// Capture
		eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
		eventTarget->removeEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
		eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
		eventTarget->removeEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
		eventTarget->removeEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
		eventTarget->removeEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);
	}

	m_document = newVal;

	InitTree();

	/*
	if (m_pTree)
	{
		HDC hDC = CreateCompatibleDC(NULL);
		HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));
		m_pTree->Size(hDC, 500);
		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
	}
	*/

	CComQIPtr<ILDOMEventTarget> eventTarget = m_document;

// Capture
	eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMNodeRemoved", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMAttrModified", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMCharacterDataModified", (ILDOMEventListener*)this, VARIANT_TRUE);
	eventTarget->addEventListener(L"DOMElementNameChanged", (ILDOMEventListener*)this, VARIANT_TRUE);

	if (m_hWnd)
	{
		InvalidateRect(NULL);
		OnSize();
	}


	/*
	if (m_documentContainer)
	{
		IDispEventImpl<3, CXMLGridCtl, &DIID__ILDOMDocumentContainerEvents, &LIBID_SVGLib, 1, 0>::DispEventUnadvise(m_documentContainer);
	}

	m_documentContainer = newVal;

	if (m_documentContainer)
	{
		IDispEventImpl<3, CXMLGridCtl, &DIID__ILDOMDocumentContainerEvents, &LIBID_SVGLib, 1, 0>::DispEventAdvise(m_documentContainer);

		CComQIPtr<ILDOMDocument> domdocument;
		m_documentContainer->get_document(&domdocument);

		cnt_setDocument(domdocument);
	}
*/
	return 0;
}

STDMETHODIMP CXMLGridCtl::get_dtdDocument(IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dtdDocument;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CXMLGridCtl::put_dtdDocument(IUnknown *newVal)
{
	ATLASSERT(0);
#if 0
	m_dtdDocument = newVal;

	if (m_dtdDocument)
	{
		CComObject<CGridDTDDocument>* pElement;
		CComObject<CGridDTDDocument>::CreateInstance(&pElement);
		if (pElement)
		{
			pElement->AddRef();
			pElement->m_pUI = this;
			pElement->m_object = m_dtdDocument;

			//pElement->m_domElement->setUserData(m_userKey, m_pTree, NULL, NULL);

			pElement->m_expanded = TRUE;

			pElement->BuildChildren();

			m_pTree = pElement;
		}

		HDC hDC = CreateCompatibleDC(NULL);

		CComQIPtr<IFont> font = m_pFont;
		HFONT hFont;
		font->get_hFont(&hFont);

		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
		m_pTree->Size/*Content*/(hDC, 0);
		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
	}
#endif

	return S_OK;
}
#endif

//virtual
void CGridItem::BuildSelectedXML(System::IO::ISequentialByteStream* stream)
{
	ASSERT(0);
#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pNode = (CGridItem*)m_childList.GetNext(pos);

		if (pNode->m_selected)
		{
			pNode->BuildXML(stream);
		}
		else
		{
			pNode->BuildSelectedXML(stream);
		}
	}
#endif
}

// virtual
void CGridItem::BuildSelectedXML(System::StringBuilderW& stream)
{
	ASSERT(0);
#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pNode = (CGridItem*)m_childList.GetNext(pos);

		if (pNode->m_selected)
		{
			sysstring str2 = pNode->BuildXML();
			str += str2;
		}
		else
		{
			sysstring str2 = pNode->BuildSelectedXML();
			str += str2;
		}
	}
#endif
}

#if 0
CComBSTR StringFromXMLStream(IStream* stream)
{
	CComBSTR str;

	ULONG cb;

	_LDOMNodeType nodeType;
	stream->Read(&nodeType, 4, &cb);

	if (nodeType == LNODE_ATTRIBUTE)
	{
		CComBSTR name;
		name.ReadFromStream(stream);

		//CComPtr<ILDOMAttr> attr;
		//document->createAttribute(name, &attr);

		//CComBSTR value;
		//value.ReadFromStream(stream);

		//attr->put_value(value);

		str += name;
		str += L"=\"";

		int nchildren;
		stream->Read(&nchildren, 4, &cb);

		for (int i = 0; i < nchildren; i++)
		{
			CComBSTR str2 = StringFromXMLStream(stream);
			str += str2;
		}

		str += L"\"";
	}
	else if (nodeType == LNODE_TEXT)
	{
		CComBSTR data;
		data.ReadFromStream(stream);

		str += data;
	}
	else if (nodeType == LNODE_COMMENT)
	{
		CComBSTR data;
		data.ReadFromStream(stream);

		str += L"<!--";
		str += data;
		str += L"-->";
	}
	else if (nodeType == LNODE_CDATA_SECTION)
	{
		CComBSTR data;
		data.ReadFromStream(stream);

		str += L"<![CDATA[";
		str += data;
		str += L"]]>";
	}
	else if (nodeType == LNODE_ENTITY_REFERENCE)
	{
		CComBSTR name;
		name.ReadFromStream(stream);

		str += L"&";
		str += name;
		str += L";";
	}
	else if (nodeType == LNODE_ELEMENT)
	{
		CComBSTR name;
		name.ReadFromStream(stream);

		str += L"<";
		str += name;

		int nattributes;
		stream->Read(&nattributes, 4, &cb);

		int nchildren;
		stream->Read(&nchildren, 4, &cb);

		for (int i = 0; i < nattributes; i++)
		{
			CComBSTR str2 = StringFromXMLStream(stream);

			str += L" ";
			str += str2;
		}

		if (nchildren > nattributes)
		{
			str += L">\n";

			for (int i = nattributes; i < nchildren; i++)
			{
				CComBSTR str2 = StringFromXMLStream(stream);

				str += str2;
			}

			str += L"\n</";
			str += name;
			str += L">\n";
		}
		else
		{
			str += L"/>\n";
		}
	}
	else
		ATLASSERT(0);

	return str;
}

STDMETHODIMP CXMLGridCtl::CopyXML()
{
	if (m_commonAncestor)
	{
		CComPtr<IStream> stream;
		HRESULT hr = CreateStreamOnHGlobal(NULL, FALSE/*deleteOnRelease*/, &stream);

		m_commonAncestor->BuildSelectedXML(stream);

		LARGE_INTEGER li;
		li.QuadPart = 0;
		stream->Seek(li, STREAM_SEEK_SET, NULL);

		CComBSTR xmlString = StringFromXMLStream(stream);

		MessageBox(sysstring(xmlString), "", MB_OK);

		CComObject<COleDataObject>* dataObject;
		CComObject<COleDataObject>::CreateInstance(&dataObject);
		if (dataObject)
		{
			dataObject->AddRef();

			// Internal XML Grid format
			{
				HGLOBAL h;
				::GetHGlobalFromStream(stream, &h);

				STGMEDIUM stgm;
				stgm.tymed = TYMED_HGLOBAL;
				stgm.pUnkForRelease = NULL;
				stgm.hGlobal = h;

				UINT nFormat = RegisterClipboardFormat("LXMLGrid");

				FORMATETC etc =
				{
					nFormat,
					NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL
				};

				dataObject->SetData(&etc, &stgm, TRUE);
			}

			// Unicode Text format
			{
				HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, xmlString.Length()*2+2);
				if (h)
				{
					WCHAR* p = (WCHAR*)GlobalLock(h);
					if (p)
					{
						CopyMemory(p, (BSTR)xmlString, xmlString.Length()*2+2);

						GlobalUnlock(h);

						STGMEDIUM stgm;
						stgm.tymed = TYMED_HGLOBAL;
						stgm.pUnkForRelease = NULL;
						stgm.hGlobal = h;

						FORMATETC etc =
						{
							CF_UNICODETEXT,
							NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL
						};

						dataObject->SetData(&etc, &stgm, TRUE);
					}
				}
			}

			::OleSetClipboard(dataObject);

			dataObject->Release();
		}
	}

	return S_OK;
}

void CXMLGridCtl::Paste(ILDOMNode* parentNode, ILDOMNode* beforeNode, IStream* stream)
{
	ULONG cb;

	_LDOMNodeType nodeType;
	stream->Read(&nodeType, 4, &cb);

	if (nodeType == LNODE_ATTRIBUTE)
	{
		CComBSTR name;
		name.ReadFromStream(stream);

		//CComPtr<ILDOMAttr> attr;
		//document->createAttribute(name, &attr);

		CComBSTR value;
		value.ReadFromStream(stream);

		//attr->put_value(value);

		CComQIPtr<ILDOMElement> element = parentNode;
		if (element)
		{
			element->setAttribute(name, value);
		}
	}
	else if (nodeType == LNODE_TEXT)
	{
		CComBSTR data;
		data.ReadFromStream(stream);

		CComPtr<ILDOMText> node;
		m_document->createTextNode(data, &node);

		parentNode->insertBefore(node, CComVariant(beforeNode), NULL);
	}
	else if (nodeType == LNODE_COMMENT)
	{
		CComBSTR data;
		data.ReadFromStream(stream);

		CComPtr<ILDOMComment> node;
		m_document->createComment(data, &node);

		parentNode->insertBefore(node, CComVariant(beforeNode), NULL);
	}
	else if (nodeType == LNODE_CDATA_SECTION)
	{
		CComBSTR data;
		data.ReadFromStream(stream);

		CComPtr<ILDOMCDATASection> node;
		m_document->createCDATASection(data, &node);

		parentNode->insertBefore(node, CComVariant(beforeNode), NULL);
	}
	else if (nodeType == LNODE_ELEMENT)
	{
		CComBSTR name;
		name.ReadFromStream(stream);

		CComPtr<ILDOMElement> element;
		m_document->createElement(name, &element);

		int nattributes;
		stream->Read(&nattributes, 4, &cb);

		int nchildren;
		stream->Read(&nchildren, 4, &cb);

		for (int i = 0; i < nchildren; i++)
		{
			Paste(element, NULL, stream);
		}

		parentNode->insertBefore(element, CComVariant(beforeNode), NULL);
	}
	else if (nodeType == LNODE_ENTITY_REFERENCE)
	{
		CComBSTR name;
		name.ReadFromStream(stream);

		CComPtr<ILDOMEntityReference> node;
		m_document->createEntityReference(name, &node);
		if (node)
		{
			parentNode->insertBefore(node, CComVariant(beforeNode), NULL);
		}
	}
	else if (nodeType == LNODE_PROCESSING_INSTRUCTION)
	{
		CComBSTR target;
		target.ReadFromStream(stream);

		CComBSTR data;
		data.ReadFromStream(stream);

		CComPtr<ILDOMProcessingInstruction> pi;
		m_document->createProcessingInstruction(target, data, &pi);
		if (pi)
		{
			parentNode->insertBefore(pi, CComVariant(beforeNode), NULL);
		}
	}
	else if (nodeType == LNODE_NOT_WELLFORMED)
	{
		CComBSTR data;
		data.ReadFromStream(stream);

		CComPtr<ILDOMNotWellformed> node;
		m_document->createNotWellformed(data, &node);

		parentNode->insertBefore(node, CComVariant(beforeNode), NULL);
	}
	else
		ATLASSERT(0);
}

STDMETHODIMP CXMLGridCtl::Paste()
{
	UINT nFormat = RegisterClipboardFormat("LXMLGrid");

	CComPtr<IDataObject> d;
	::OleGetClipboard(&d);

	COleDataObjectWrapper dataObject;
	dataObject.Attach(d);

	HGLOBAL hData;

	CComPtr<ILDOMDocument> document = m_document;

	if (hData = dataObject.GetGlobalData(nFormat))
	{
		CComPtr<IStream> stream;
		HRESULT hr = CreateStreamOnHGlobal(hData, FALSE/*deleteOnRelease*/, &stream);

		if (m_pActiveItem)
		{
			if (m_pActiveItem->m_parent)
			{
				Paste(m_pActiveItem->m_parent->m_domNode, m_pActiveItem->m_domNode, stream);
			}
		}

		GlobalUnlock(hData);
	}

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::CanPaste(VARIANT_BOOL *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	BOOL b = IsClipboardFormatAvailable(RegisterClipboardFormat("LXMLGrid"));

	*pVal = b? VARIANT_TRUE: VARIANT_FALSE;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// IDropTarget

void CXMLGridCtl::DrawInsertionMarker(HDC hDC)
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	CRect rect = m_pDragOverItem->GetAbsRect();

	POINT oldOrg;
	SetViewportOrgEx(hDC, -scrollposX, -scrollposY, &oldOrg);

	FillSolidRect(hDC, rect.left, rect.top+rect.Height()*m_bDragBottom-1, rect.Width(), 3, RGB(255, 255, 255));

	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
}

STDMETHODIMP CXMLGridCtl::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, /*[in,out]*/DWORD * pdwEffect)
{
	m_dwDragEffect = DROPEFFECT_NONE;

	UINT nFormat = RegisterClipboardFormat("LXMLGrid");

	CComPtr<IEnumFORMATETC> enumfmt;
	pDataObject->EnumFormatEtc(DATADIR_GET, &enumfmt);

	FORMATETC fetc;
	DWORD fetched;
	while ((enumfmt->Next(1, &fetc, &fetched) == S_OK) && fetched)
	{
		if (fetc.cfFormat == nFormat)
			break;
	}

	if (fetc.cfFormat == nFormat)
	{
		FORMATETC fetc = {0};
		fetc.cfFormat = nFormat;
		fetc.tymed = TYMED_HGLOBAL;
		fetc.dwAspect = DVASPECT_CONTENT;
		fetc.lindex = -1;			//	give me all

		HRESULT hr = pDataObject->QueryGetData(&fetc);
		if (hr == S_OK)
		{
			m_dwDragEffect = *pdwEffect;	// Same as was passed in
		}
	}

	DragOver(grfKeyState, ptl, pdwEffect);

	*pdwEffect = m_dwDragEffect;
	return S_OK;
}

STDMETHODIMP CXMLGridCtl::DragOver(DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
//	CRect client;
//	GetClientRect(&client);

	CPoint point(ptl.x, ptl.y);
	ScreenToClient(&point);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	long minv; m_vert->get_minv(&minv);
	long maxv; m_vert->get_maxv(&maxv);
	long visible; m_vert->get_visible(&visible);

	if (point.y < 15)	// scroll up
	{
		long pos = scrollposY - (15-point.y);
		if (pos < minv) pos = minv;
		OnVertScroll(0, pos);
	}
	else if (point.y > m_areaRect.bottom-15)	// scroll down
	{
		long pos = scrollposY + (point.y - (m_areaRect.bottom-15));
		if (pos > maxv-visible) pos = maxv-visible;
		OnVertScroll(0, pos);
	}

	m_horz->get_pos(&scrollposX);
	m_vert->get_pos(&scrollposY);

	point.x += scrollposX;
	point.y += scrollposY;

	if (m_dwDragEffect)
	{
		if (grfKeyState & MK_CONTROL)
			m_dwDragEffect = DROPEFFECT_COPY;
		else
			m_dwDragEffect = DROPEFFECT_MOVE;

		*pdwEffect = m_dwDragEffect;

		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_XORPEN);

		if (m_pDragOverItem)
		{
			DrawInsertionMarker(hDC);

			m_pDragOverItem = NULL;
		}

		CGridItem* pNode;
		m_pTree->HitTestContent(point, 0, &pNode);

		if (pNode)
		{
			m_pDragOverItem = pNode;

			CRect rect = m_pDragOverItem->GetAbsRect();

			if (point.y > rect.top+rect.Height()/2)
			{
				m_bDragBottom = 1;
			}
			else
				m_bDragBottom = 0;

			DrawInsertionMarker(hDC);
		}

		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);
	}

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::DragLeave()
{
	HDC hDC = GetDC();
	int oldR2 = SetROP2(hDC, R2_XORPEN);

	if (m_pDragOverItem)
	{
		DrawInsertionMarker(hDC);

		m_pDragOverItem = NULL;
	}

	SetROP2(hDC, oldR2);
	ReleaseDC(hDC);

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	HDC hDC = GetDC();
	int oldR2 = SetROP2(hDC, R2_XORPEN);

	if (m_pDragOverItem)
	{
		CRect rect = m_pDragOverItem->GetAbsRect();

		FillSolidRect(hDC, rect.left, rect.top+rect.Height()*m_bDragBottom, rect.Width(), 3, RGB(255, 255, 255));
	}

	SetROP2(hDC, oldR2);
	ReleaseDC(hDC);

	if (m_pDragOverItem)
	{
		UINT nFormat = RegisterClipboardFormat("LXMLGrid");

		COleDataObjectWrapper dataObject;
		dataObject.Attach(pDataObject);

		HGLOBAL hData;

		//CComPtr<ILDOMDocument> document = m_document;

		if (hData = dataObject.GetGlobalData(nFormat))
		{
			CComPtr<IStream> stream;
			HRESULT hr = CreateStreamOnHGlobal(hData, FALSE/*deleteOnRelease*/, &stream);

			CComPtr<ILDOMNode> parentNode = m_pDragOverItem->m_parent->m_domNode;

			CComPtr<ILDOMNode> beforeNode;
			if (m_bDragBottom == 0)
				beforeNode = m_pDragOverItem->m_domNode;
			else
				m_pDragOverItem->m_domNode->get_nextSibling(&beforeNode);

			Paste(parentNode, beforeNode, stream);

			GlobalUnlock(hData);

			*pdwEffect = m_dwDragEffect;
		}

		m_pDragOverItem = NULL;
	}

	return S_OK;
}
#endif

CGridNode* CXMLGridCtl::CreateGridNode(LXmlEdit::Node* node)
{
	Web::NodeType nodeType = node->get_nodeType();

	switch (nodeType)
	{
#if 0
	case NODE_DOCUMENT:
		{
			CGridDocument* pChild = new CGridDocument;
			pChild->m_pUI = this;
			pChild->m_domNode = node;
			pChild->m_domNode->setUserData(m_userKey, pChild, NULL, NULL);
			
			*pVal = pChild;
		}
		break;
#endif
	case Web::NODE_DOCUMENT_TYPE:
		{
			CGridDocType* pChild = new CGridDocType;
			pChild->m_pUI = this;
			pChild->m_domNode = node;
		//	pChild->m_domNode->setUserData(m_userKey, pChild, NULL, NULL);
			
			return pChild;
		}
		break;

	case Web::NODE_ATTRIBUTE:
		{
			CGridAttribute* pAttr = new CGridAttribute;
			pAttr->m_pUI = this;
			pAttr->m_domNode = node;
		//	pAttr->m_domNode->setUserData(m_userKey, pAttr, NULL, NULL);
			
			return pAttr;
		}
		break;

	case Web::NODE_ELEMENT:
		{
			CGridElement* pChild = new CGridElement;
			pChild->m_pUI = this;
			pChild->m_domNode = node;
		//	pChild->m_domNode->setUserData(m_userKey, pChild, NULL, NULL);
			
			return pChild;
		}
		break;

	case Web::NODE_TEXT:
	case Web::NODE_COMMENT:
	case Web::NODE_CDATA_SECTION:
		{
			CGridCharacterData* pChild = new CGridCharacterData(node);
			pChild->m_pUI = this;
		//	pChild->m_domNode = node;
		//	pChild->m_domNode->setUserData(m_userKey, pChild, NULL, NULL);
			
			return pChild;
		}
		break;
		
#if 0
	case NODE_PROCESSING_INSTRUCTION:
		{
			CComObject<CGridProcessingInstruction>* pChild;
			CComObject<CGridProcessingInstruction>::CreateInstance(&pChild);
			pChild->AddRef();
			pChild->m_pUI = this;
			pChild->m_domNode = node;
			pChild->m_domNode->setUserData(m_userKey, pChild, NULL, NULL);
			
			*pVal = pChild;
		}
		break;
		
	case NODE_ENTITY_REFERENCE:
		{
			CComObject<CGridEntityReference>* pChild;
			CComObject<CGridEntityReference>::CreateInstance(&pChild);
			pChild->AddRef();
			pChild->m_pUI = this;
			pChild->m_domNode = node;
			pChild->m_domNode->setUserData(m_userKey, pChild, NULL, NULL);
			
			*pVal = pChild;
		}
		break;
		
	case NODE_NOT_WELLFORMED:
		{
			//CComQIPtr<ILDOMCharacterData> chardata = child;
			//if (chardata)
			{
				CComObject<CGridNotWellformed>* pChild;
				CComObject<CGridNotWellformed>::CreateInstance(&pChild);
				pChild->AddRef();
				pChild->m_pUI = this;
				pChild->m_domNode = node;
				pChild->m_domNode->setUserData(m_userKey, pChild, NULL, NULL);
				
				*pVal = pChild;
			}
		}
		break;
#endif
	}
	return NULL;
}

#if 0
// ILDOMEventListener
STDMETHODIMP CXMLGridCtl::handleEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"DOMNodeInserted"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComPtr<ILDOMNode> parentNode;
		node->get_parentNode(&parentNode);

		CComPtr<IXMLGridNode> xmlparentNode;
		parentNode->getUserData(m_userKey, (IUnknown**)&xmlparentNode);
		CGridContainerNode* pParentNode = (CGridContainerNode*)xmlparentNode.p;

		CGridNode* pNode;
		CreateGridNode(node, &pNode);
		if (pNode)
		{
			pNode->m_parent = pParentNode;

			pNode->BuildChildren();

			if (pParentNode->GetNodeType() == LNODE_DOCUMENT)
			{
				CGridDocument* pParentDocument = static_cast<CGridDocument*>(pParentNode);
				UPOSITION pos = pParentDocument->m_childList.GetHeadPosition();

				CComPtr<ILDOMNode> child;
				parentNode->get_firstChild(&child);

				while (child)
				{
					if (child == node/*targetNode*/)
						break;

					if (pos)
					{
						UPOSITION pos2 = pos;
						CGridItem* pChild = (CGridItem*)pParentDocument->m_childList.GetNext(pos2);
						ATLASSERT(pChild->m_domNode != node/*element*/);
						if (pChild->m_domNode == child)
						{
							pos = pos2;	// Okay, advance pos
						}
					}

					CComPtr<ILDOMNode> nextSibling;
					child->get_nextSibling(&nextSibling);
					child = nextSibling;
				}

				if (pos)
					pParentDocument->m_childList.InsertBefore(pos, pNode);
				else
					pParentDocument->m_childList.AddTail(pNode);
			}
			else
			{
				CGridElement* pParentElement = static_cast<CGridElement*>(pParentNode);
				UPOSITION pos = pParentElement->m_nodeList.GetHeadPosition();

				CComPtr<ILDOMNode> child;
				parentNode->get_firstChild(&child);

				while (child)
				{
					if (child == node/*targetNode*/)
						break;

					if (pos)
					{
						UPOSITION pos2 = pos;
						CGridItem* pChild = (CGridItem*)pParentElement->m_nodeList.GetNext(pos2);
						ATLASSERT(pChild->m_domNode != node/*element*/);
						if (pChild->m_domNode == child)
						{
							pos = pos2;	// Okay, advance pos
						}
					}

					CComPtr<ILDOMNode> nextSibling;
					child->get_nextSibling(&nextSibling);
					child = nextSibling;
				}

				if (pos)
					pParentElement->m_nodeList.InsertBefore(pos, pNode);
				else
					pParentElement->m_nodeList.AddTail(pNode);

				pParentElement->RebuildChildList();
			}

		// Resize
			HDC hDC = CreateCompatibleDC(NULL);
			HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

			pNode->Size(hDC, 0);
			pParentNode->RecalculateParentSize(hDC);

			SelectObject(hDC, hOldFont);
			DeleteDC(hDC);

			Invalidate();
			OnSize();
		}
	}
	else if (!wcscmp(type, L"DOMNodeRemoved")/* ||
		!wcscmp(type, L"DOMNodeRemovedFromDocument")*/)
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComPtr<IXMLGridNode> gridNode;
		node->getUserData(m_userKey, (IUnknown**)&gridNode);
		if (gridNode)
		{
			CGridElement* pParent = static_cast<CGridElement*>(static_cast<CGridNode*>(gridNode.p)->m_parent);

			UPOSITION pos;

			pos = pParent->m_childList.Find(gridNode);
			pParent->m_childList.RemoveAt(pos);

			pos = pParent->m_nodeList.Find(gridNode);
			pParent->m_nodeList.RemoveAt(pos);

			static_cast<CGridItem*>(gridNode.p)->Release();

			// Resize parent
			{
				HDC hDC = CreateCompatibleDC(NULL);
				HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

				pParent->RecalculateParentSize(hDC);

				SelectObject(hDC, hOldFont);
				DeleteDC(hDC);
			}

			Invalidate();
			OnSize();
		}
	}
	else if (!wcscmp(type, L"DOMAttrModified"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		_LDOMAttrChangeType attrChangeType;
		mut->get_attrChange(&attrChangeType);

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComPtr<ILDOMNode> attrNode;
		mut->get_relatedNode(&attrNode);
		CComQIPtr<ILDOMAttr> attr = attrNode;

		if (attrChangeType == CHANGE_MODIFICATION)
		{
			CComPtr<IXMLGridNode> gridNode;
			attrNode->getUserData(m_userKey, (IUnknown**)&gridNode);
			if (gridNode)
			{
				CGridElement* pParent = (CGridElement*)static_cast<CGridAttribute*>(gridNode.p)->m_parent;

				static_cast<CGridAttribute*>(gridNode.p)->RemoveChildren();
				static_cast<CGridAttribute*>(gridNode.p)->BuildChildren();

			// Resize
				HDC hDC = CreateCompatibleDC(NULL);
				HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

				static_cast<CGridAttribute*>(gridNode.p)->Size(hDC, static_cast<CGridAttribute*>(gridNode.p)->m_size.cx);
				pParent->RecalculateParentSize(hDC);

				SelectObject(hDC, hOldFont);
				DeleteDC(hDC);

				Invalidate();
				OnSize();
			}
		}
		else if (attrChangeType == CHANGE_ADDITION)
		{
			CComPtr<IXMLGridNode> gridElement;
			node->getUserData(m_userKey, (IUnknown**)&gridElement);
			CGridElement* pGridElement = static_cast<CGridElement*>(gridElement.p);

			CGridNode* pGridAttribute;
			CreateGridNode(attrNode, &pGridAttribute);
			if (pGridAttribute)
			{
				pGridAttribute->m_parent = pGridElement;

				pGridAttribute->BuildChildren();

				CComPtr<ILDOMNamedNodeMap> attributes;
				node->get_attributes(&attributes);

				long nattributes;
				attributes->get_length(&nattributes);

				UPOSITION pos = pGridElement->m_attributeList.GetHeadPosition();

				for (int i = 0; i < nattributes; i++)
				{
					CComPtr<ILDOMNode> child;
					attributes->item(i, &child);

					if (child == attrNode)
						break;

					if (pos)
					{
						UPOSITION pos2 = pos;
						pos = pos2;
					}
				}

				if (pos)
					pGridElement->m_attributeList.InsertBefore(pos, pGridAttribute);
				else
					pGridElement->m_attributeList.AddTail(pGridAttribute);

				pGridElement->RebuildChildList();

				// Resize
				{
					HDC hDC = CreateCompatibleDC(NULL);
					HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

					pGridAttribute->Size(hDC, 0);
					pGridElement->RecalculateParentSize(hDC);

					SelectObject(hDC, hOldFont);
					DeleteDC(hDC);
				}

				Invalidate();
				OnSize();
			}
		}
		else if (attrChangeType == CHANGE_REMOVAL)
		{
			CComPtr<IXMLGridNode> gridNode;
			attrNode->getUserData(m_userKey, (IUnknown**)&gridNode);
			if (gridNode)
			{
				CGridElement* pParent = (CGridElement*)static_cast<CGridAttribute*>(gridNode.p)->m_parent;

				UPOSITION pos;

				pos = pParent->m_childList.Find(gridNode.p);
				pParent->m_childList.RemoveAt(pos);

				pos = pParent->m_attributeList.Find(gridNode.p);
				pParent->m_attributeList.RemoveAt(pos);

				(CGridElement*)static_cast<CGridAttribute*>(gridNode.p)->Release();

				// Resize parent
				{
					HDC hDC = CreateCompatibleDC(NULL);
					HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

					pParent->RecalculateParentSize(hDC);

					SelectObject(hDC, hOldFont);
					DeleteDC(hDC);
				}

				Invalidate();
				OnSize();
			}
		}

		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::get_ActiveItem(IXMLGridItem **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pActiveItem;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CXMLGridCtl::get_ActiveParentNode(IXMLGridNode **pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_pActiveItem)
	{
		*pVal = m_pActiveItem->m_parent;
		if (*pVal) (*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::get_ActiveNode(IXMLGridNode **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	if (m_pActiveItem)
	{
		CComQIPtr<IXMLGridNode> node = m_pActiveItem;
		*pVal = node;
		if (*pVal) (*pVal)->AddRef();
	}

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::DeleteSelection()
{
	if (m_commonAncestor)
	{
		DeleteSelected(m_commonAncestor);
	}

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::HasSelection(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_commonAncestor && m_pActiveItem)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::SelectItem(IXMLGridItem *item)
{
	CGridItem* pItem = (CGridItem*)item;
	if (m_commonAncestor)
	{
		m_commonAncestor->Deselect();
	}

	m_pActiveItem = pItem;
	m_pLastFocus = pItem;
	m_commonAncestor = pItem->m_parent;

	m_pActiveItem->m_selected = true;

	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CXMLGridCtl::GetXMLNodeFromDOMNode(IUnknown* nodeUnk, IXMLGridNode* *pVal)
{
	CComQIPtr<ILDOMNode> node = nodeUnk;
	if (node == NULL) return E_INVALIDARG;

	return node->getUserData(m_userKey, (IUnknown**)pVal);
}

#endif

}
