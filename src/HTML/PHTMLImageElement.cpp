#include "stdafx.h"
#include "HTML2.h"

namespace System
{
namespace Web
{

PHTMLImageElement::PHTMLImageElement(HTMLImageElement* element) : PHTMLElement(element)
{
}

PHTMLImageElement::~PHTMLImageElement()
{
}

//virtual
bool PHTMLImageElement::HasDistributableChildren()
{
	return false;
}

#if 0
//virtual
void PHTMLImageElement::CalculateDimensions(LXML::CHTMCalcContext* pC)
{
#if 0
	GetCSSProperties(pC);
#endif

	HTMLImageElement* pElement = static_cast<HTMLImageElement*>(m_pNode);

#if 0
	LDraw::Size size = pElement->GetImageSize();

// TODO
	if (size.Width >= 0)
		m_specifiedWidth = m_computedWidth = size.Width;
	else
		m_specifiedWidth = m_computedWidth = 32;

	if (size.Height >= 0)
		m_specifiedHeight = m_computedHeight = size.Height;
	else
		m_specifiedHeight = m_computedHeight = 32;
#endif
}
#endif

gm::SizeD PHTMLImageElement::GetIntrinsicSize()
{
	HTMLImageElement* pElement = static_cast<HTMLImageElement*>(m_pNode);

	CImage* pImage = pElement->GetImage();

	if (pImage)
	{
		Graphics::Bitmap* bitmap = pImage->m_bitmap;
		if (bitmap != NULL)
		{
			return gm::SizeD(bitmap->GetWidth(), bitmap->GetHeight());
		}
	}

	return gm::SizeD(-1, -1);
}

//virtual
void PHTMLImageElement::Draw(CHTMRenderContext* pC)
{
	HTMLImageElement* pElement = static_cast<HTMLImageElement*>(m_pNode);

	if (m_pBox)
	{
		//pC->m_outerPos.X += m_pBox->m_outerRect.X;
		//pC->m_outerPos.Y += m_outerRect.Y;

	//	Gdiplus::Rect trect = m_pBox->GetAbsInnerRect();
	//	Gdiplus::RectF trect = m_pBox->m_innerRect;
	//	trect.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);
		gm::RectF trect = m_pBox->m_innerRect;//GetAbsInnerRect();
		//trect.Offset(-trect.X, -trect.Y);

		CImage* pImage = pElement->GetImage();

		if (pImage)
		{
			CriticalSectionLock lock(pImage->m_lock);

			Graphics::Bitmap* bitmap = pImage->m_bitmap;
			if (bitmap != NULL)
		//	if (pGdipImage/* && pGdipImage->GetLastStatus() == 0*/)
			{
			//	Gdiplus::ImageAttributes imageAttributes;

				ASSERT(0);
#if 0
				pC->m_pGraphics->DrawImage(bitmap,
					trect,
					0, 0, bitmap->GetWidth(), bitmap->GetHeight()/*,
					Gdiplus::UnitPixel, &imageAttributes, NULL, NULL*/);
#endif
			}
		}

#if 0
		if (pC->m_bInSelection)
		{
			Gdiplus::HatchBrush brush(Gdiplus::HatchStyle50Percent, Gdiplus::Color(0, 0, 0, 0), Gdiplus::Color(128, 128, 128));

			pC->m_pGraphics->FillRectangle(&brush, trect);
		}
#endif

#if 0
		if (m_pWindow->m_cursorItem == this)
		{
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

			HBRUSH hOldBrush = (HBRUSH)SelectObject(pC->m_hDC, GetStockObject(NULL_BRUSH));
			HPEN hOldPen = (HPEN)SelectObject(pC->m_hDC, hPen);
			int oldR2 = SetROP2(pC->m_hDC, R2_NOTXORPEN);

			Rectangle(pC->m_hDC, trect.left, trect.top, trect.right, trect.bottom);

			Rectangle(pC->m_hDC, trect.left, trect.top, trect.left+6, trect.top+6);
			Rectangle(pC->m_hDC, trect.left, trect.bottom-6, trect.left+6, trect.bottom);
			Rectangle(pC->m_hDC, trect.right-6, trect.top, trect.right, trect.top+6);
			Rectangle(pC->m_hDC, trect.right-6, trect.bottom-6, trect.right, trect.bottom);

			SetROP2(pC->m_hDC, oldR2);
			SelectObject(pC->m_hDC, hOldPen);
			SelectObject(pC->m_hDC, hOldBrush);

			DeleteObject(hPen);
		}
#endif

	//	pC->m_outerPos.X -= m_outerRect.X;
	//	pC->m_outerPos.Y -= m_outerRect.Y;
	}
}

#if 0
BOOL PHTMLImageElement::OnButtonDown(POINT point, CPElement* *pVal)
{
	Gdiplus::RectF trect = m_pBox->GetAbsInnerRect();

//	TRACE("%d, %d, %d, %d\n", point.x, point.y, trect.right, trect.bottom);

	if ((point.x > trect.GetRight()-8) && (point.y > trect.GetBottom()-8))
	{
		CRect nrect(trect.X, trect.Y, trect.GetRight(), trect.GetBottom());

		ASSERT(0);
#if 0

		HWND hwnd = m_pWindow->m_pUI->m_hWnd;

		HDC hDC = GetDC(hwnd);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		BOOL bLoop = TRUE;
		::SetCapture(hwnd);

		MSG msg;
		while (bLoop && GetMessage(&msg, hwnd, 0, 0))
		{
			TranslateMessage(&msg);

			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				{
					POINT abspoint;
					abspoint.x = (short)LOWORD(msg.lParam);
					abspoint.y = (short)HIWORD(msg.lParam);

					POINT relpoint = abspoint;
					relpoint.x -= m_pWindow->m_client.left;
					relpoint.y -= m_pWindow->m_client.top;
				//	relpoint.x -= trect.left;
				//	relpoint.y -= trect.top;

				// Erase old rect
					Rectangle(hDC, nrect.left, nrect.top, nrect.right, nrect.bottom);

					nrect.right = relpoint.x;
					nrect.bottom = relpoint.y;

				// Draw new rect
					Rectangle(hDC, nrect.left, nrect.top, nrect.right, nrect.bottom);
				}
				break;

			case WM_LBUTTONUP:
				bLoop = FALSE;
				break;
			}
		}

		ReleaseCapture();

		CComQIPtr<ILHTMLElement> element = m_pNode;
		TCHAR buf[64];

		sprintf(buf, "%d", nrect.Width());
		element->setAttribute(L"width", _bstr_t(buf));

		sprintf(buf, "%d", nrect.Height());
		element->setAttribute(L"height", _bstr_t(buf));

		SetROP2(hDC, oldR2);
		SelectObject(hDC, hOldPen);
		DeleteObject(hPen);
		SelectObject(hDC, hOldBrush);
		ReleaseDC(hwnd, hDC);

		return TRUE;
#endif
	}

	return FALSE;
}
#endif

}	// Web
}
