// LinksDlg.cpp : Implementation of CLinksDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "LinksDlg.h"

static CSize ThumbSizes[] =
{
	CSize(16, 16),	// None
	CSize(24, 24),
	CSize(38, 38),
	CSize(54, 54),
};

/////////////////////////////////////////////////////////////////////////////
// CLinksDlg

int CLinksDlg::FinalConstruct()
{
	HRESULT hr;

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_LINKS, &m_menu);

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);

	return S_OK;
}

STDMETHODIMP CLinksDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILinksDlg
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

LRESULT CLinksDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_document)
	{
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		LOGFONT lf;
		GetObject(hFont, sizeof(lf), &lf);
		lf.lfWeight = FW_BOLD;

		HFONT hFontSelected = CreateFontIndirect(&lf);
		HFONT hOldFont = dc.GetCurrentFont();

		long scrollposY; m_vert->get_pos(&scrollposY);

		if (dc.IntersectClipRect(m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
		{
			CPoint oldOrg = dc.SetViewportOrg(m_areaRect.left, m_areaRect.top - scrollposY);

			CComPtr<IObjectMap> images;
			m_document->get_images(&images);

			long nimages;
			images->get_length(&nimages);

			int y = 0;

			for (int i = 0; i < nimages; i++)
			{
				CComPtr<IPDImage> image;
				images->item(i, (IUnknown**)&image);

				BSTR bpathName;
				image->get_pathName(&bpathName);
				_bstr_t pathName = _bstr_t(bpathName, false);

				LPTSTR fileName = NULL;
				if (pathName.length()) fileName = PathFindFileName(pathName);

				CRect itemrect(0, y, m_areaRect.Width(), y+ThumbSizes[m_thumbSize].cy);

				if (m_thumbSize > 0)
				{
					Gdiplus::Image* pImage;
					image->get_privateImage((DWORD*)&pImage);
					if (pImage)
					{
						Gdiplus::Graphics graphics(dc.m_hDC);

						int width;
						int height;

						width = ThumbSizes[m_thumbSize].cx;
						height = pImage->GetHeight() * width/pImage->GetWidth();

						if (height > ThumbSizes[m_thumbSize].cy)
						{
							height = ThumbSizes[m_thumbSize].cy;
							width = pImage->GetWidth() * height/pImage->GetHeight();
						}

						int left = (ThumbSizes[m_thumbSize].cx-width)/2;
						int top = (ThumbSizes[m_thumbSize].cy-height)/2;

						graphics.DrawImage(pImage, itemrect.left+left, itemrect.top+top, width, height);
					}
				}

				if (fileName)
				{
					CRect trect = itemrect;
					trect.left += ThumbSizes[m_thumbSize].cx+4;

					dc.SelectFont(hFont);
					dc.DrawText(fileName, _tcslen(fileName), &trect, DT_SINGLELINE | DT_VCENTER | DT_PATH_ELLIPSIS);
				}

				y += ThumbSizes[m_thumbSize].cy;
			}

			dc.SetViewportOrg(oldOrg);
		}

		dc.SelectFont(hOldFont);

		DeleteObject(hFont);
		DeleteObject(hFontSelected);
	}

	return 0;
}

LRESULT CLinksDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CLinksDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CLinksDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CLinksDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CLinksDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	Invalidate();
	return 0;
}

void CLinksDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.InflateRect(-1, -1);

	long nimages = 0;

	if (m_document)
	{
		CComPtr<IObjectMap> images;
		m_document->get_images(&images);

		images->get_length(&nimages);
	}

	int height = nimages*ThumbSizes[m_thumbSize].cy;

	if (height > m_areaRect.Height())
	{
		m_areaRect.right -= 16;

		m_axvert.MoveWindow(m_areaRect.right, 0, 16, m_areaRect.bottom);
		m_vert->SetInfo(0, height, m_areaRect.Height());
	}
	else
	{
		m_axvert.MoveWindow(0, 0, 0, 0);
		m_vert->SetInfo(0, 0, m_areaRect.Height());
	}
}

STDMETHODIMP CLinksDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocument> document = object;
	if (document)
	{
		m_document = document;
		CComQIPtr<INotifySend> cp = m_document;
		{
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		*cookie = 1;

		if (m_hWnd)
		{
			OnSize();
			Invalidate();
		}
	}

	return S_OK;
}

STDMETHODIMP CLinksDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	if (IsUnknownEqualUnknown(object, m_document))
	{
		CComQIPtr<INotifySend> cp = m_document;
		cp->Unadvise(this);
		m_document.Release();

		if (m_hWnd)
		{
			OnSize();
			Invalidate();
		}
	}

	return S_OK;
}

HRESULT __stdcall CLinksDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &m_areaRect, &m_areaRect);

	return S_OK;
}

BEGIN_CMD_MAP(CLinksDlg)
	CMD_HANDLER(ID_LINKS_PALETTEOPTIONS, OnLinksPaletteOptions)
END_CMD_MAP()

#include "LinksOptionsDlg.h"

LRESULT CLinksDlg::OnLinksPaletteOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CLinksOptionsDlg dlg;
	dlg.m_thumbSize = m_thumbSize;

	if (dlg.DoModal(GetMainHwnd()) == IDOK)
	{
		m_thumbSize = dlg.m_thumbSize;

		OnSize();
		Invalidate();
	}

	return 0;
}
