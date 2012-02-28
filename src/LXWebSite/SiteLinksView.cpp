// SiteLinksView.cpp : Implementation of CSiteLinksView
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "SiteLinksView.h"

//#include "Element.h"

#include "WebSite.h"

class CLinkableFile
{
public:
	CLinkableFile(/*CSiteFile* pSiteFile*/)
	{
		//m_pSiteFile = pSiteFile;
		m_fromFile = NULL;

		m_bInExpanded = FALSE;
		m_bOutExpanded = FALSE;

		m_largeIconIndex = -1;
		m_rect.SetRectEmpty();

		m_dbid = 0L;
	}

	~CLinkableFile()
	{
		FreeInLinks();
		FreeOutLinks();
	}

	DWORD m_dbid;
	CLinkableFile* m_fromFile;

	CSiteLinksView* m_linksView;

	//CSiteFile* m_pSiteFile;

	BYTE m_bInExpanded;
	BYTE m_bOutExpanded;

	CUPtrList m_inLinks;
	CUPtrList m_outLinks;

	CRect m_rect;

	int m_largeIconIndex;

	void FreeInLinks();
	void FreeOutLinks();

	void BuildLinks(CSiteLinksView* pView, BOOL bIn, BOOL bOut);
	void Draw(HDC hDC, BOOL bIn, BOOL bOut);
	void Size(BOOL bIn, BOOL bOut);

	BOOL Click(/*HDC hDC,*/ POINT point);
};

void CLinkableFile::FreeInLinks()
{
	UPOSITION pos = m_inLinks.GetHeadPosition();
	while (pos)
	{
		CLinkableFile* pLink = (CLinkableFile*)m_inLinks.GetNext(pos);
		delete pLink;
	}

	m_inLinks.RemoveAll();
}

void CLinkableFile::FreeOutLinks()
{
	UPOSITION pos = m_outLinks.GetHeadPosition();
	while (pos)
	{
		CLinkableFile* pLink = (CLinkableFile*)m_outLinks.GetNext(pos);
		delete pLink;
	}

	m_outLinks.RemoveAll();
}

void CLinkableFile::BuildLinks(CSiteLinksView* pView, BOOL bIn, BOOL bOut)
{
	m_linksView = pView;

	CWebSite* pWebSite = ((CWebSite*)m_linksView->m_document.p);

	if (m_largeIconIndex == -1)
	{
		SHFILEINFO	sfi = {0};

		::SHGetFileInfo(
			(LPCTSTR)"c:\\test.html",//m_pSiteFile->GetFullPathName(),
			0,
			&sfi,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

		m_largeIconIndex = sfi.iIcon;
	}

	ADODB::_ConnectionPtr conn;
	pWebSite->m_webSite->GetDBConnection((IDispatch**)&conn);

	if (bIn || bOut)
	{
		// in links
		if (bIn)
		{
			WCHAR sql[256];
			swprintf(sql, L"SELECT file_id FROM links WHERE out_link_id = %d", m_dbid);
			_variant_t va;
			ADODB::_RecordsetPtr recordset = conn->Execute(sql, &va, ADODB::adCmdText);

			while (recordset->EndOfFile == false)
			{
				CLinkableFile* pLinkFile = new CLinkableFile;
				pLinkFile->m_dbid = recordset->Fields->Item[_bstr_t("file_id")]->Value.lVal;
				/*
				CSiteFile* pFile = (CSiteFile*)m_pSiteFile->m_pWebSite->m_pRootDir->FindItemByID(id, 2);
				ATLASSERT(pFile);
				ATLASSERT(pFile->m_dbid);
				*/

				pLinkFile->m_fromFile = this;
				m_inLinks.AddTail(pLinkFile);

				recordset->MoveNext();
			}
		}

		// out links
		if (bOut)
		{
			WCHAR sql[256];
			swprintf(sql, L"SELECT out_link_id FROM links WHERE file_id = %d", m_dbid);
			_variant_t va;
			ADODB::_RecordsetPtr recordset = conn->Execute(sql, &va, ADODB::adCmdText);

			while (recordset->EndOfFile == false)
			{
				CLinkableFile* pLinkFile = new CLinkableFile;
				pLinkFile->m_dbid = recordset->Fields->Item[_bstr_t("out_link_id")]->Value.lVal;
				/*
				CSiteFile* pFile = (CSiteFile*)m_pSiteFile->m_pWebSite->m_pRootDir->FindItemByID(id, 2);
				ATLASSERT(pFile);
				ATLASSERT(pFile->m_dbid);
				*/

				pLinkFile->m_fromFile = this;
				m_outLinks.AddTail(pLinkFile);

				recordset->MoveNext();
			}
		}
	}
}

static void DrawExpanded(HDC hDC, int x, int y, BOOL bExpanded)
{
	CRect rect(x-6, y-6, x+6, y+6);

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

void CLinkableFile::Size(BOOL bIn, BOOL bOut)
{
	SIZE iconSize;
	ImageList_GetIconSize(m_linksView->m_imgIconLarge, (int*)&iconSize.cx, (int*)&iconSize.cy);

	int width = 80;
	int height = (iconSize.cy+14);

	m_rect.SetRect(-width/2-2, -height/2-2, width/2+2, height/2+2);

	if (bIn)
	{
		int count = m_inLinks.GetCount();

		if (count) m_rect.left -= 18;

		if (m_bInExpanded)
		{
			int y = -(count-1)*(height+20)/2;

			UPOSITION pos = m_inLinks.GetHeadPosition();
			while (pos)
			{
				CLinkableFile* pLinkFile = (CLinkableFile*)m_inLinks.GetNext(pos);
				pLinkFile->Size(bIn, FALSE);

				CRect rect = pLinkFile->m_rect;
				rect.OffsetRect(-140, y);

				m_rect.UnionRect(&m_rect, &rect);

				y += (height+20);
			}
		}
	}

	if (bOut)
	{
		int count = m_outLinks.GetCount();

		if (count) m_rect.right += 18;

		if (m_bOutExpanded)
		{
			int y = -(count-1)*(height+20)/2;

			UPOSITION pos = m_outLinks.GetHeadPosition();
			while (pos)
			{
				CLinkableFile* pLinkFile = (CLinkableFile*)m_outLinks.GetNext(pos);
				pLinkFile->Size(FALSE, bOut);

				CRect rect = pLinkFile->m_rect;
				rect.OffsetRect(140, y);

				m_rect.UnionRect(&m_rect, &rect);

				y += (height+20);
			}
		}
	}
}

BOOL CLinkableFile::Click(/*HDC hDC,*/ POINT point)
{
	SIZE iconSize;
	ImageList_GetIconSize(m_linksView->m_imgIconLarge, (int*)&iconSize.cx, (int*)&iconSize.cy);

	int width = 80;
	int height = (iconSize.cy+14);

	if (m_inLinks.GetCount() > 0)
	{
		int left = -(width/2+10);
		int top = 0;
		CRect rect(left-6, top-6, left+6, top+6);

		if (PtInRect(&rect, point))
		{
			m_bInExpanded = !m_bInExpanded;

			UPOSITION pos = m_inLinks.GetHeadPosition();
			while (pos)
			{
				CLinkableFile* pLink = (CLinkableFile*)m_inLinks.GetNext(pos);

				if (m_bInExpanded)
				{
					pLink->BuildLinks(m_linksView, TRUE, FALSE);
				}
				else
				{
					pLink->FreeInLinks();
					pLink->m_bInExpanded = FALSE;
				}
			}

			return TRUE;
		}
	}

	if (m_outLinks.GetCount() > 0)
	{
		int left = +(width/2+10);
		int top = 0;
		CRect rect(left-6, top-6, left+6, top+6);

		if (PtInRect(&rect, point))
		{
			m_bOutExpanded = !m_bOutExpanded;
			UPOSITION pos = m_outLinks.GetHeadPosition();

			while (pos)
			{
				CLinkableFile* pLink = (CLinkableFile*)m_outLinks.GetNext(pos);

				if (m_bOutExpanded)
				{
					pLink->BuildLinks(m_linksView, FALSE, TRUE);
				}
				else
				{
					pLink->FreeOutLinks();
					pLink->m_bOutExpanded = FALSE;
				}
			}

			return TRUE;
		}
	}

	if (m_bInExpanded)
	{
		int count = m_inLinks.GetCount();

		int y = -(count-1)*(height+20)/2;

		UPOSITION pos = m_inLinks.GetHeadPosition();
		while (pos)
		{
			POINT pt = point;
			pt.x += 140;
			pt.y -= y;

			CLinkableFile* pLinkFile = (CLinkableFile*)m_inLinks.GetNext(pos);
			BOOL b = pLinkFile->Click(pt);
			if (b) return b;

			y += (height+20);
		}
	}

	if (m_bOutExpanded)
	{
		int count = m_outLinks.GetCount();

		int y = -(count-1)*(height+20)/2;

		UPOSITION pos = m_outLinks.GetHeadPosition();
		while (pos)
		{
			POINT pt = point;
			pt.x -= 140;
			pt.y -= y;

			CLinkableFile* pLinkFile = (CLinkableFile*)m_outLinks.GetNext(pos);
			BOOL b = pLinkFile->Click(pt);
			if (b) return b;

			y += (height+20);
		}
	}

	return FALSE;
}

void CLinkableFile::Draw(HDC hDC, BOOL bIn, BOOL bOut)
{
	SIZE iconSize;
	ImageList_GetIconSize(m_linksView->m_imgIconLarge, (int*)&iconSize.cx, (int*)&iconSize.cy);

	int width = 80;
	int height = (iconSize.cy+14);

	{
		int x = -(iconSize.cx)/2;
		int y = -(iconSize.cy+14)/2;

		ImageList_Draw(m_linksView->m_imgIconLarge, m_largeIconIndex, hDC, x, y, ILD_TRANSPARENT);
	}

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	CRect trect(-width/2, height/2-14, width/2, height/2);
#if 0
	DrawText(hDC, m_pSiteFile->m_wfd.cFileName, strlen(m_pSiteFile->m_wfd.cFileName), &trect, DT_SINGLELINE | DT_PATH_ELLIPSIS | DT_CENTER | DT_VCENTER);
#endif

	if (m_inLinks.GetCount()) DrawExpanded(hDC, -(width/2+10), 0, m_bInExpanded);
	if (m_outLinks.GetCount()) DrawExpanded(hDC, +(width/2+10), 0, m_bOutExpanded);

// Recurse

	if (bIn)
	{
		if (m_bInExpanded)
		{
			int count = m_inLinks.GetCount();

			int y = -(count-1)*(height+20)/2;

			UPOSITION pos = m_inLinks.GetHeadPosition();
			while (pos)
			{
				MoveToEx(hDC, -width/2-16, 0, NULL);
				LineTo(hDC, -140+width/2+0, y);

				POINT oldOrg;
				OffsetWindowOrgEx(hDC, 140, -y, &oldOrg);

				CLinkableFile* pLinkFile = (CLinkableFile*)m_inLinks.GetNext(pos);
				pLinkFile->Draw(hDC, bIn, FALSE);

				SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

				y += (height+20);
			}
		}
	}

	if (bOut)
	{
		if (m_bOutExpanded)
		{
			int count = m_outLinks.GetCount();

			int y = -(count-1)*(height+20)/2;

			UPOSITION pos = m_outLinks.GetHeadPosition();
			while (pos)
			{
				MoveToEx(hDC, width/2+16, 0, NULL);
				LineTo(hDC, 140-width/2-0, y);

				POINT oldOrg;
				OffsetWindowOrgEx(hDC, -140, -y, &oldOrg);

				CLinkableFile* pLinkFile = (CLinkableFile*)m_outLinks.GetNext(pos);
				pLinkFile->Draw(hDC, FALSE, bOut);

				SetWindowOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

				y += (height+20);
			}
		}
	}

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

/////////////////////////////////////////////////////////////////////////////
// CSiteLinksView

void __stdcall CSiteLinksView::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	HWND hwnd;
	get_hwnd(&hwnd);

	CRect rect = m_areaRect;

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

void __stdcall CSiteLinksView::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	HWND hwnd;
	get_hwnd(&hwnd);

	CRect rect = m_areaRect;

	m_horz->put_pos(pos);
	ScrollWindow(oldPos-pos, 0, &rect, &rect);
}

HRESULT __stdcall CSiteLinksView::OnOutLinksChanged(long file_id)
{
	ATLASSERT(0);
#if 0
	delete m_pRootFile;
	m_pRootFile = NULL;

	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	if (pWebSite->m_pFileHomepage)
	{
		m_pRootFile = new CLinkableFile(pWebSite->m_pFileHomepage);
		m_pRootFile->BuildLinks(this, TRUE, TRUE);
	}

	InvalidateRect(NULL, TRUE);
#endif

	return 0;
}

STDMETHODIMP CSiteLinksView::get_document(IWebSite **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CSiteLinksView::put_document(IWebSite *newVal)
{
	if (m_document)
		IDispEventImpl<3, CSiteLinksView, &DIID__IWebSiteEvents, &LIBID_LXWEBSITELib, 1, 0>::DispEventUnadvise(m_document);

	m_document = newVal;

	if (m_document)
		IDispEventImpl<3, CSiteLinksView, &DIID__IWebSiteEvents, &LIBID_LXWEBSITELib, 1, 0>::DispEventAdvise(m_document);

	return S_OK;
}

LRESULT CSiteLinksView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CSiteLinksView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);
	IDispEventImpl<2, CSiteLinksView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);

	SHFILEINFO	ssfi;	//get a handle to the system small icon list 

	m_imgIconLarge = (HIMAGELIST)::SHGetFileInfo(
		(LPCTSTR)_T("C:\\"),
		0,
		&ssfi, sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	unsigned long homepagefile_id;
	pWebSite->m_webSite->GetHomepageFileId(&homepagefile_id);
//	CSiteFile* pHomepage = (CSiteFile*)pWebSite->m_pRootDir->FindItemByID(homepagefile_id, 2);

	if (homepagefile_id)
	{
		m_pRootFile = new CLinkableFile;
		m_pRootFile->m_dbid = homepagefile_id;

		m_pRootFile->BuildLinks(this, TRUE, TRUE);
		m_pRootFile->Size(TRUE, TRUE);
	}

	return 0;
}

LRESULT CSiteLinksView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CSiteLinksView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	IDispEventImpl<2, CSiteLinksView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);

	if (m_document)
		IDispEventImpl<3, CSiteLinksView, &DIID__IWebSiteEvents, &LIBID_LXWEBSITELib, 1, 0>::DispEventUnadvise(m_document);

	return 0;
}

long CSiteLinksView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);

	CRect	client;
	GetClientRect(&client);

	int cx = client.Width();
	int cy = client.Height();

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

//	m_vert->MoveWindow(cx-sbWidth, 0, sbWidth, cy-sbHeight, TRUE);
//	m_horz->MoveWindow(0, cy-sbHeight, cx-sbWidth, sbHeight, TRUE);

	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CSiteLinksView::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int cx = client.Width();
	int cy = client.Height();

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	m_areaRect.SetRect(0, 0, cx-sbWidth, cy-sbHeight);

	if (m_pRootFile)
	{
		int left = m_pRootFile->m_rect.left*m_magnify;
		int right = m_pRootFile->m_rect.right*m_magnify;

		int top = m_pRootFile->m_rect.top*m_magnify;
		int bottom = m_pRootFile->m_rect.bottom*m_magnify;

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

long CSiteLinksView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	HWND hwnd; get_hwnd(&hwnd);
//	ATLASSERT(IsWindow(hwnd));

	PAINTSTRUCT ps;
	HDC hDC= BeginPaint(&ps);

	CRect	client;
	GetClientRect(&client);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_pRootFile)
	{
		int state = SaveDC(hDC);

		if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom) > NULLREGION)
		{
			SetMapMode(hDC, MM_ANISOTROPIC);
			SetWindowExtEx(hDC, 10000, 10000, NULL);
			SetWindowOrgEx(hDC, 0, 0, NULL);
			SetViewportExtEx(hDC, 10000*m_magnify, 10000*m_magnify, NULL);
			SetViewportOrgEx(hDC, -scrollposX, -scrollposY, NULL);

			HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

			m_pRootFile->Draw(hDC, TRUE, TRUE);

			SelectObject(hDC, hOldFont);
		}

		RestoreDC(hDC, state);
	}

	EndPaint(&ps);
	return 0;
}

long CSiteLinksView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	CRect	client;
	GetClientRect(&client);

	if (PtInRect(&m_areaRect, point))
	{
		if (m_pRootFile)
		{
			if (nFlags & MK_SHIFT)
			{
				if (!m_dragging)
				{
					m_startpt = point;
					m_startpt.x += scrollposX;
					m_startpt.y += scrollposY;

					m_dragging = 1;
					SetCapture();
				}
			}
			else
			{
				POINT pt = point;
				pt.x += scrollposX;
				pt.y += scrollposY;
				pt.x /= m_magnify;
				pt.y /= m_magnify;

				m_pRootFile->Click(pt);
				m_pRootFile->Size(TRUE, TRUE);

				OnSize();
				InvalidateRect(NULL, TRUE);
			}
		}
	}

	return 0;
}

long CSiteLinksView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd;
	get_hwnd(&hwnd);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_dragging)
	{
		HDC hDC = GetDC();
		IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
		POINT org;
		org.x = m_areaRect.left /*+ m_offset.x*/-scrollposX;
		org.y = m_areaRect.left /*+ m_offset.y*/-scrollposY;
		POINT oldOrg;
		SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

		double aspect = (double)m_areaRect.Height()/m_areaRect.Width();

	// Erase old zoomrect
		Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

		SelectObject(hDC, hOldBrush);
		SetROP2(hDC, oldR2);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		ReleaseDC(hDC);

		m_zoomRect.NormalizeRect();

		if (m_zoomRect.Width() <= 2 || m_zoomRect.Height() <= 2)
		{
			double x = m_startpt.x/m_magnify;
			double y = m_startpt.y/m_magnify;

		//	double docwidth = m_imageRect.Width();///m_magnify;
		//	double docheight = m_imageRect.Height();///m_magnify;

#if 0
			if (!(nFlags & MK_SHIFT/*MK_ALT*/))	// Zoom in
			{
				ZoomToRect2(
					x-m_imageRect.Width()/m_magnify/4.0,
					y-m_imageRect.Height()/m_magnify/4.0,
					x+m_imageRect.Width()/m_magnify/4.0,
					y+m_imageRect.Height()/m_magnify/4.0);
			}
			else	// Zoom out
			{
				ATLTRACE("Zoom out rect\n");

				ZoomToRect2(
					x-m_imageRect.Width()/m_magnify,
					y-m_imageRect.Height()/m_magnify,
					x+m_imageRect.Width()/m_magnify,
					y+m_imageRect.Height()/m_magnify);
			}
#endif
		}
		else
		{
			ZoomToRect2(
				m_zoomRect.left/m_magnify,
				m_zoomRect.top/m_magnify,
				m_zoomRect.right/m_magnify,
				m_zoomRect.bottom/m_magnify
				);
		}

		m_dragging = 0;
		ReleaseCapture();
	}
	return 0;
}

long CSiteLinksView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	HWND hwnd;
	get_hwnd(&hwnd);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	POINT pt = point;
	pt.x += scrollposX;
	pt.y += scrollposY;

	if (m_dragging == 1)
	{
		HDC hDC = GetDC();
		IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
		POINT org;
		org.x = m_areaRect.left /*+ m_offset.x*/-scrollposX;
		org.y = m_areaRect.left /*+ m_offset.y*/-scrollposY;
		POINT oldOrg;
		SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

	// Erase old zoomrect
		Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

		double aspect = (double)m_areaRect.Height()/m_areaRect.Width();

		m_zoomRect.left = m_startpt.x;
		m_zoomRect.top = m_startpt.y;
		if ((double)abs(pt.x-m_startpt.x)/m_areaRect.Width() > (double)abs(pt.y-m_startpt.y)/m_areaRect.Height())
		{
			double aspect = (double)m_areaRect.Height()/m_areaRect.Width();
			m_zoomRect.right = pt.x;
			m_zoomRect.bottom = m_startpt.y + (pt.x-m_startpt.x)*aspect;
		}
		else
		{
			double aspect = (double)m_areaRect.Width()/m_areaRect.Height();
			m_zoomRect.right = m_startpt.x + (pt.y-m_startpt.y)*aspect;
			m_zoomRect.bottom = pt.y;
		}

	// Draw new zoomrect
		Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

		SelectObject(hDC, hOldBrush);
		SetROP2(hDC, oldR2);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		ReleaseDC(hDC);
	}

	return 0;
}

void CSiteLinksView::ZoomToRect2(double left, double top, double right, double bottom)
{
#if 0
	CDblRect zoomRect;
	zoomRect.left = left;
	zoomRect.top = top;
	zoomRect.right = right;
	zoomRect.bottom = bottom;

	HWND hwnd;
	get_hwnd(&hwnd);

	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	CDblRect zrect;
	zrect.left = zoomRect.left;
	zrect.top = zoomRect.top;
	zrect.right = zoomRect.right;
	zrect.bottom = zoomRect.bottom;

	double oldmagnify = m_magnify;

//	m_magnify = (double)(pDocument->GetWidth()/**m_magnify*/)/zrect.Width();
	m_magnify = (double)(m_areaRect.Width()/**m_magnify*/)/zrect.Width();
//	m_magnifyMatrix->put_a(m_magnify);
//	m_magnifyMatrix->put_d(m_magnify);

	int cx = zrect.left*m_magnify;
	int cy = zrect.top*m_magnify;

	int animate = 1;

	if (animate == 1)
	{
	/*
		CRect orect;
		orect.left = scrollposX;
		orect.top = scrollposY;
		orect.right = scrollposX + m_imageRect.Width();
		orect.bottom = scrollposY + m_imageRect.Height();

		int total;

		double omagnify = m_magnify;
	*/

		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

		CDblRect imageRect;
		imageRect.left = m_areaRect.left;
		imageRect.top = m_areaRect.top;
		imageRect.right = m_areaRect.right;
		imageRect.bottom = m_areaRect.bottom;

		CDblRect orect;
		CDblRect zRect;

		if (m_magnify > oldmagnify) // Zoom in
		{
			orect = imageRect;
			zRect = zoomRect;

			zRect.left *= oldmagnify;
			zRect.top *= oldmagnify;
			zRect.right *= oldmagnify;
			zRect.bottom *= oldmagnify;
		
			zRect.left -= scrollposX;
			zRect.top -= scrollposY;
			zRect.right -= scrollposX;
			zRect.bottom -= scrollposY;
		}
		else
		{
			zRect = imageRect;
			orect = zoomRect;

			orect.left += scrollposX;
			orect.top += scrollposY;
			orect.right += scrollposX;
			orect.bottom += scrollposY;

			orect.left /= oldmagnify;
			orect.top /= oldmagnify;
			orect.right /= oldmagnify;
			orect.bottom /= oldmagnify;

		/*
			orect.left /= m_magnify;
			orect.top /= m_magnify;
			orect.right /= m_magnify;
			orect.bottom /= m_magnify;
		*/
		}

		CRect zrect2;
		int atotal = 60;

		for (int i = 0; i <= atotal; i++)
		{
			if (i > 0)
				Rectangle(hDC, zrect2.left, zrect2.top, zrect2.right, zrect2.bottom);

			zrect2.left = orect.left + (zRect.left-orect.left)*i/atotal;
			zrect2.top = orect.top + (zRect.top-orect.top)*i/atotal;
			zrect2.right = orect.right + (zRect.right-orect.right)*i/atotal;
			zrect2.bottom = orect.bottom + (zRect.bottom-orect.bottom)*i/atotal;

			Rectangle(hDC, zrect2.left, zrect2.top, zrect2.right, zrect2.bottom);

			Sleep(5);
		}

		SelectObject(hDC, hOldBrush);
		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);
	}

	{
		OnSize();

		m_horz->put_pos(cx);
		m_vert->put_pos(cy);

		InvalidateRect(NULL, TRUE);
		UpdateWindow();
	}
#endif
}

BEGIN_CMD_MAP(CSiteLinksView)
	//CMD_HANDLER(&ID_SITE_RESCAN, OnRescan)
END_CMD_MAP()
