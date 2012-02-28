// TransparencyDlg.cpp : Implementation of CTransparencyDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "TransparencyDlg.h"
#include "PDDocumentView.h"

#include "PDObjectSelected.h"

/////////////////////////////////////////////////////////////////////////////
// CTransparencyDlg

STDMETHODIMP CTransparencyDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITransparencyDlg
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

int CTransparencyDlg::FinalConstruct()
{
	HRESULT hr;

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_TRANSPARENCY, &m_menu);

	return S_OK;
}

LRESULT CTransparencyDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	::GetWindowRect(GetDlgItem(IDC_TRANSP_THUMBNAIL), &m_thumbRect);
	ScreenToClient(&m_thumbRect);

	int middle = (m_thumbRect.Width()-4)/2;

	m_bitmapRect = CRect(m_thumbRect.left+2, m_thumbRect.top+2, m_thumbRect.left + 2 + middle-5, m_thumbRect.bottom-2);
	m_maskRect = CRect(m_thumbRect.left+2+middle+5, m_thumbRect.top+2, m_thumbRect.right-2, m_thumbRect.bottom-2);

	return 0;
}

LRESULT CTransparencyDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	return 0;
}

void CTransparencyDlg::SetFromTargetView()
{
	m_objectWithOpacityMask = NULL;
	m_bHasOpacityMask = 0;

	if (m_view)
	{
		if (m_view->m_targetObjects.GetSize() > 0)
		{
			//m_bHasOpacityMask = -2;

			// Get mask
			for (int i = 0; i < m_view->m_targetObjects.GetSize(); i++)
			{
				CComQIPtr<IPDObjectWithOpacityMask> objectWithOpacityMask2 = m_view->m_targetObjects[i]->m_object;
				if (objectWithOpacityMask2)
				{
					CComPtr<IPDObjectGroup> opacityMaskGroup2;
					objectWithOpacityMask2->get_opacityMaskGroup(&opacityMaskGroup2);

					if (i == 0)
					{
						m_bHasOpacityMask = (opacityMaskGroup2 != NULL);
						m_objectWithOpacityMask = objectWithOpacityMask2;
					}
					else if (m_bHasOpacityMask != (opacityMaskGroup2 != NULL))
					{
						m_bHasOpacityMask = -2;
						m_objectWithOpacityMask = NULL;
						break;
					}
				}
			}
		}
	}
}

LRESULT CTransparencyDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_view)
	{
		Gdiplus::Graphics hdcgraphics(dc.m_hDC);

		if (m_view->m_targetObjects.GetSize() > 0)
		{
			CComPtr<IPDObjectGroup> opacityMaskGroup;

			if (m_objectWithOpacityMask)
			{
				m_objectWithOpacityMask->get_opacityMaskGroup(&opacityMaskGroup);
			}

		// Get mask bounding box
			RectD maskBoundingBox;
			maskBoundingBox.X = 999999;
			maskBoundingBox.Y = 999999;
			maskBoundingBox.Width = -999999;
			maskBoundingBox.Height = -999999;

			if (opacityMaskGroup)
			{
				CComQIPtr<IPDObjectTransformable> groupTransformable = opacityMaskGroup;
				groupTransformable->get_bounds(&maskBoundingBox);
			}

			// Get objects bounding box
			RectD objectsBoundingBox = m_view->m_objectsBoundingBox;	// TODO

			// Get the union bounding box of object(s) and mask
			Gdiplus::RectF boundingBox;

			Gdiplus::RectF::Union(boundingBox,
				Gdiplus::RectF(maskBoundingBox.X, maskBoundingBox.Y, maskBoundingBox.Width, maskBoundingBox.Height),
				Gdiplus::RectF(objectsBoundingBox.X, objectsBoundingBox.Y, objectsBoundingBox.Width, objectsBoundingBox.Height));

			{
				if (boundingBox.Width > 0 && boundingBox.Height > 0)
				{
					int width = m_bitmapRect.Width();
					int height = boundingBox.Height * width/boundingBox.Width;
					if (height > m_bitmapRect.Height())
					{
						height = m_bitmapRect.Height();
						width = boundingBox.Width * height/boundingBox.Height;
					}
					ATLASSERT(width <= m_bitmapRect.Width());

					double magnify = width/boundingBox.Width;

					double left = (m_bitmapRect.Width()-width)/2;
					double top = (m_bitmapRect.Height()-height)/2;

					Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(m_bitmapRect.Width(), m_bitmapRect.Height(), PixelFormat32bppARGB);
				//	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
					if (pBitmap)
					{
						{
							Gdiplus::Graphics graphics(pBitmap);

							Gdiplus::Rect gdipBitmapRect(0, 0, m_bitmapRect.Width(), m_bitmapRect.Height());

						// Paint background
							if (m_view->m_bViewTransparencyGrid)
							{
								CComQIPtr<IPDDocumentSettings> documentSettings = m_view->m_document;
								long gridSizeX;
								long gridSizeY;
								OLE_COLOR gridColor0;
								OLE_COLOR gridColor1;

								documentSettings->get_transpGridSizeX(&gridSizeX);
								documentSettings->get_transpGridSizeY(&gridSizeY);
								documentSettings->get_transpGridColor0(&gridColor0);
								documentSettings->get_transpGridColor1(&gridColor1);

								Gdiplus::SolidBrush brush0(Gdiplus::Color(GetRValue(gridColor0), GetGValue(gridColor0), GetBValue(gridColor0)));
								Gdiplus::SolidBrush brush1(Gdiplus::Color(GetRValue(gridColor1), GetGValue(gridColor1), GetBValue(gridColor1)));

								Gdiplus::Bitmap gridbitmap(gridSizeX*2, gridSizeY*2);
								{
									Gdiplus::Graphics graphics(&gridbitmap);

									graphics.FillRectangle(&brush0, 0, 0, gridSizeX, gridSizeY);
									graphics.FillRectangle(&brush1, gridSizeX, 0, gridSizeX, gridSizeY);
									graphics.FillRectangle(&brush1, 0, gridSizeY, gridSizeX, gridSizeY);
									graphics.FillRectangle(&brush0, gridSizeX, gridSizeY, gridSizeX, gridSizeY);
								}

								Gdiplus::TextureBrush tbrush(&gridbitmap, Gdiplus::WrapModeTile/*, Gdiplus::Rect(0, 0, gridSizeX*2, gridSizeY*2)*/);

								graphics.FillRectangle(&tbrush, gdipBitmapRect);
							}
							else
							{
								graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255)), gdipBitmapRect);
							}

						//
							CComPtr<IPDRenderer> renderer;
							renderer.CoCreateInstance(CLSID_PDRenderer);
							renderer->put_targetHDC((HDC)&graphics);
							renderer->put_magnify(magnify);

							graphics.TranslateTransform(left, top);

							graphics.ScaleTransform(magnify, magnify);
							graphics.TranslateTransform(-boundingBox.X, -boundingBox.Y);

							for (int i = 0; i < m_view->m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_view->m_targetObjects[i];
								CComQIPtr<IPDObject> object = pObject->m_object;
								if (object)
								{
									renderer->RenderObject(object);
								}
							}
						}

						hdcgraphics.DrawImage(pBitmap, m_bitmapRect.left, m_bitmapRect.top/*, width, height*/);

						delete pBitmap;
					}
				}
			}

			if (m_bHasOpacityMask == -2)
			{
				dc.DrawText("?", 1, &m_maskRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			else if (opacityMaskGroup)
			{
				{
					HBITMAP hBmLink = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_OPACITYMASKLINKED));
					HDC hBmDC = CreateCompatibleDC(NULL);
					HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBmDC, hBmLink);
		
					BITMAP bm;
					GetObject(hBmLink, sizeof(bm), &bm);

					dc.BitBlt(
						m_thumbRect.left + (m_thumbRect.Width()-bm.bmWidth)/2,
						m_thumbRect.top + (m_thumbRect.Height()-bm.bmHeight)/2,
						bm.bmWidth, bm.bmHeight,
						hBmDC,
						0, 0,
						SRCCOPY);

					SelectObject(hBmDC, hOldBitmap);
					DeleteDC(hBmDC);

					DeleteObject(hBmLink);
				}

				if (boundingBox.Width > 0 && boundingBox.Height > 0)
				{
					int width = m_maskRect.Width();
					int height = boundingBox.Height * width/boundingBox.Width;
					if (height > m_maskRect.Height())
					{
						height = m_maskRect.Height();
						width = boundingBox.Width * height/boundingBox.Height;
					}
					ATLASSERT(width <= m_maskRect.Width());

					double magnify = width/boundingBox.Width;

					Gdiplus::Bitmap* pMask = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
					if (pMask)
					{
						{
							Gdiplus::Graphics graphics(pMask);

							CComPtr<IPDRenderer> renderer;
							renderer.CoCreateInstance(CLSID_PDRenderer);
							renderer->put_targetHDC((HDC)&graphics);
							renderer->put_magnify(magnify);

							graphics.ScaleTransform(magnify, magnify);
							graphics.TranslateTransform(-boundingBox.X, -boundingBox.Y);

							renderer->RenderObject(opacityMaskGroup);
						}

						{
							Gdiplus::BitmapData maskData;
							pMask->LockBits(
								&Gdiplus::Rect(0, 0, width, height),
								Gdiplus::ImageLockModeWrite,
								PixelFormat32bppARGB,
								&maskData);

							for (int y = 0; y < maskData.Height; y++)
							{
								ARGBPixel* maskPixel = (ARGBPixel*)((BYTE*)maskData.Scan0+maskData.Stride*y);

								for (int x = 0; x < maskData.Width; x++)
								{
									int maskOpacity = 255 - (int)maskPixel->alpha*((maskPixel->red + maskPixel->green + maskPixel->blue)/3)/255;

									BYTE opacity = maskPixel->alpha*maskOpacity/255;

									maskPixel->alpha = 255;
									maskPixel->red = opacity;
									maskPixel->green = opacity;
									maskPixel->blue = opacity;

									maskPixel++;
								}
							}

							pMask->UnlockBits(&maskData);
						}

						hdcgraphics.DrawImage(pMask, m_maskRect.left, m_maskRect.top, width, height);

						delete pMask;
					}
				}
			}
		}

	// Draw rect around if we're editing bitmap or mask
		{
			Gdiplus::Pen pen(Gdiplus::Color(0, 0, 0), 1);

			if (m_view->m_activeGroup == NULL)
			{
				hdcgraphics.DrawRectangle(&pen, Gdiplus::Rect(m_bitmapRect.left-1, m_bitmapRect.top-1, m_bitmapRect.Width()+1, m_bitmapRect.Height()+1));
			}
			else
			{
				hdcgraphics.DrawRectangle(&pen, Gdiplus::Rect(m_maskRect.left-1, m_maskRect.top-1, m_maskRect.Width()+1, m_maskRect.Height()+1));
			}
		}
	}

	return 0;
}

LRESULT CTransparencyDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_view)
	{
		if (m_thumbRect.PtInRect(point))
		{
			int middle = m_thumbRect.left + m_thumbRect.Width()/2;

			if (point.x < middle-5)	// bitmap
			{
				m_view->m_activeGroup = NULL;
			}
			else if (point.x > middle+5)	// mask
			{
				if (m_objectWithOpacityMask)
				{
					CComPtr<IPDObjectGroup> opacityMaskGroup;
					m_objectWithOpacityMask->get_opacityMaskGroup(&opacityMaskGroup);

					m_view->m_activeGroup = opacityMaskGroup;
				}
			}
			else	// Link
			{
			}

			InvalidateRect(&m_thumbRect);
		}
	}

	return 0;
}

void CTransparencyDlg::OnSize()
{
}

LRESULT CTransparencyDlg::OnOpacityChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR buf[64];
	GetDlgItemText(IDC_TRANSP_OPACITY, buf, sizeof(buf));
	double opacity = atof(buf)/100;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDOpacityAndBlendMode> objectOpacity = m_targetObjects[i];
		if (objectOpacity)
		{
			objectOpacity->put_opacity(opacity);
		}
	}

	return 0;
}

void CTransparencyDlg::SetControlValues()
{
	double opacity = tomUndefined;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDOpacityAndBlendMode> objectOpacity = m_targetObjects[i];
		if (objectOpacity)
		{
			double opacity2;
			objectOpacity->get_opacity(&opacity2);

			if (i == 0)
			{
				opacity = opacity2;
			}
			else if (opacity != opacity2)
			{
				opacity = tomUndefined;
				break;
			}
		}
	}

	if (opacity != tomUndefined)
	{
		TCHAR buf[64];
		sprintf(buf, _T("%g"), opacity*100);
		SetDlgItemText(IDC_TRANSP_OPACITY, buf);
	}
	else
	{
		SetDlgItemText(IDC_TRANSP_OPACITY, _T(""));
	}
}

STDMETHODIMP CTransparencyDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocumentView> view = object;
	if (view)
	{
		ATLASSERT(m_view == NULL);	// Assume only one active view at a time
		m_view = static_cast<CComObject<CPDDocumentView>*>(view.p);
		m_view->AddRef();
//		IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_view->m_document);

		{
			CComQIPtr<INotifySend> cp = m_view->m_document;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		SetFromTargetView();

		if (m_hWnd)
		{
			OnSize();
			InvalidateRect(&m_thumbRect);
		}

		*cookie = 1;
	}
	else
	{
		CComQIPtr<IPDOpacityAndBlendMode> objectOpacity = object;
		if (objectOpacity)
		{
			m_targetObjects.Add(objectOpacity.Detach());
			*cookie = 1;
		}
	}

	SetControlValues();

	return S_OK;
}

STDMETHODIMP CTransparencyDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	if (IsUnknownEqualUnknown((IPDDocumentView*)m_view, object))
	{
		ATLASSERT(cookie == 1);
		ATLASSERT(m_view != NULL);

	//	DeselectAll();

		CComQIPtr<INotifySend> cp = m_view->m_document;
		cp->Unadvise(this);

	//	IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_view->m_document);
		m_view->Release();
		m_view = NULL;

		SetFromTargetView();

		if (m_hWnd)
		{
			OnSize();
			InvalidateRect(&m_thumbRect);
		}
	}
	else
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(object, m_targetObjects[i]))
			{
				m_targetObjects[i]->Release();
				m_targetObjects.RemoveAt(i);
				break;
			}
		}
	}

	SetControlValues();

	return S_OK;
}

// ICommandTarget
STDMETHODIMP CTransparencyDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try view
	CComQIPtr<ICommandTarget> view = m_view;
	if (view) view->OnCmdMsg(nID, nCode, pCmdUI, bHandled);

	return S_OK;
}

BEGIN_CMD_MAP(CTransparencyDlg)
//	CMD_HANDLER(ID_LINKS_PALETTEOPTIONS, OnLinksPaletteOptions)
END_CMD_MAP()

/*
#include "LinksOptionsDlg.h"

LRESULT CLinksDlg::OnLinksPaletteOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CLinksOptionsDlg dlg;
	dlg.m_thumbSize = m_thumbSize;

	if (dlg.DoModal(GetMainHwnd()) == IDOK)
	{
		m_thumbSize = dlg.m_thumbSize;

		Invalidate();
	}

	return 0;
}
*/
