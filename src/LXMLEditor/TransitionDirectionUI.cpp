#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "TransitionDirectionUI.h"

#include "../LSMILTransitions/LSMILTransitions.h"
#include "../LSMILTransitions/LSMILTransitionFactory.h"
#pragma comment(lib, "../LSMILTransitions/Debug/LSMILTransitions.lib")

//#define IDB_BITMAPB                     296
//#define IDB_BITMAPA                     297

namespace System
{
namespace LXmlEdit
{

static LDraw::PointI ptTop[3] =
{
	LDraw::PointI(-4, 0),
	LDraw::PointI(4, 0),
	LDraw::PointI(0, -8)
};

static LDraw::PointI ptBottom[3] =
{
	LDraw::PointI(-4, 0),
	LDraw::PointI(4, 0),
	LDraw::PointI(0, 8)
};

static LDraw::PointI ptLeft[3] =
{
	LDraw::PointI(0, -4),
	LDraw::PointI(0, 4),
	LDraw::PointI(-8, 0)
};

static LDraw::PointI ptRight[3] =
{
	LDraw::PointI(0, -4),
	LDraw::PointI(0, 4),
	LDraw::PointI(8, 0)
};

static LDraw::PointI ptTopLeft[3] =
{
	LDraw::PointI(-8, 0),
	LDraw::PointI(0, -8),
	LDraw::PointI(0, 0)
};

static LDraw::PointI ptTopRight[3] =
{
	LDraw::PointI(0, -8),
	LDraw::PointI(8, 0),
	LDraw::PointI(0, 0)
};

static LDraw::PointI ptBottomLeft[3] =
{
	LDraw::PointI(-8, 0),
	LDraw::PointI(0, 8),
	LDraw::PointI(0, 0)
};

static LDraw::PointI ptBottomRight[3] =
{
	LDraw::PointI(8, 0),
	LDraw::PointI(0, 8),
	LDraw::PointI(0, 0)
};

bool CTimerWnd::ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult)
{
#if 0
	if (uMsg == WM_TIMER)
	{
		m_pUI->Invalidate();

		double duration = 4;	// seconds
		m_pUI->m_progress += (100.0/1000.0) / duration;
		if (m_pUI->m_progress > 1) m_pUI->m_progress = 0;

		return true;
	}
#endif
	return false;
}

#if 0
/////////////////////////////////////////////////////////////////////////////
// CTimerWnd
LRESULT CTimerWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
#endif
	return 0;
}

#endif


CTransitionDirectionUI::CTransitionDirectionUI()
{
	m_progress = 0;
	m_bitCorners = 0;
	m_arrowFlags = 0;
	m_flags = 0;
	m_reverse = false;

#if 0
//	RECT rc = {0,0,0,0};
	m_timerWnd.Create(NULL, MSWindows::Rect()/*LDraw::BBox(0,0,0,0)*/, NULL, WS_DISABLED);
	m_timerWnd.m_pUI = this;
	m_timerWnd.SetTimer(1, 100);
#endif
}

CTransitionDirectionUI::~CTransitionDirectionUI()
{
}

void CTransitionDirectionUI::OnRender(UI::Graphics* pGraphics)
{
//	LDraw::CRect& rc = *(CRect*)di.prcBounds;
//	HDC hDC = di.hdcDraw;

//	FillSolidRect(hDC, &rc, GetSysColor(COLOR_BTNFACE));

	LDraw::SizeD size = get_ActualSize();

	double uiwidth = size.Height;
	double uiheight = size.Height;

	double cx = uiwidth/2;
	double cy = uiheight/2;

	LDraw::SolidBrush* hBNorm = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));
	LDraw::SolidBrush* hBHilight = new LDraw::SolidBrush(LDraw::Color(255, 0, 0));

	//HBRUSH hOldBrush = (HBRUSH)GetCurrentObject(hDC, OBJ_BRUSH);

//	POINT oldorg;
//	GetViewportOrgEx(hDC, &oldorg);

	//LDraw::Matrix3f oldTransform = pGraphics->PushTransform();

	if (m_bitCorners & bitTop)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitTop)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(cx, 8);
		pGraphics->FillPolygon((m_arrowFlags & bitTop)? hBHilight: hBNorm, ptTop, 3);
		pGraphics->PopTransform();//(oldTransform);
	}

	if (m_bitCorners & bitBottom)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitBottom)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(cx, uiheight-8);
		pGraphics->FillPolygon((m_arrowFlags & bitBottom)? hBHilight: hBNorm, ptBottom, 3);
		pGraphics->PopTransform();//oldTransform);
	}

	if (m_bitCorners & bitLeft)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitLeft)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(8, cy);
		pGraphics->FillPolygon((m_arrowFlags & bitLeft)? hBHilight: hBNorm, ptLeft, 3);
		pGraphics->PopTransform();//oldTransform);
	}

	if (m_bitCorners & bitRight)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitRight)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(uiwidth-8, cy);
		pGraphics->FillPolygon((m_arrowFlags & bitRight)? hBHilight: hBNorm, ptRight, 3);
		pGraphics->PopTransform();//oldTransform);
	}

	if (m_bitCorners & bitUpperLeft)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitUpperLeft)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(8, 8);
		pGraphics->FillPolygon((m_arrowFlags & bitUpperLeft)? hBHilight: hBNorm, ptTopLeft, 3);
		pGraphics->PopTransform();//oldTransform);
	}

	if (m_bitCorners & bitUpperRight)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitUpperRight)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(uiwidth-8, 8);
		pGraphics->FillPolygon((m_arrowFlags & bitUpperRight)? hBHilight: hBNorm, ptTopRight, 3);
		pGraphics->PopTransform();//oldTransform);
	}

	if (m_bitCorners & bitLowerLeft)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitLowerLeft)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(8, uiheight-8);
		pGraphics->FillPolygon((m_arrowFlags & bitLowerLeft)? hBHilight: hBNorm, ptBottomLeft, 3);
		pGraphics->PopTransform();//oldTransform);
	}

	if (m_bitCorners & bitLowerRight)
	{
		pGraphics->PushTransform();
	//	SelectObject(hDC, (m_arrowFlags & bitLowerRight)? hBHilight: hBNorm);
		pGraphics->TranslateTransform(uiwidth-8, uiheight-8);
		pGraphics->FillPolygon((m_arrowFlags & bitLowerRight)? hBHilight: hBNorm, ptBottomRight, 3);
		pGraphics->PopTransform();//oldTransform);
	}

//	SelectObject(hDC, hOldBrush);
//	DeleteObject(hBNorm);
//	DeleteObject(hBHilight);
//	SetViewportOrgEx(hDC, oldorg.x, oldorg.y, NULL);

	if (m_type->Length())
	{
		LDraw::RectI mediaRect(0, 0, size.Height, size.Height);
		mediaRect.Inflate(-8, -8);

		LDraw::Bitmap* pBitmapA;
		LDraw::Bitmap* pBitmapB;
		double progress;

		if (!m_reverse)
		{
			pBitmapA = m_bitmap[0];//new LDraw::Bitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAPA));
			pBitmapB = m_bitmap[1];//new LDraw::Bitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAPB));
			progress = m_progress;
		}
		else
		{
			pBitmapA = m_bitmap[1];//new LDraw::Bitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAPB));
			pBitmapB = m_bitmap[0];//new LDraw::Bitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAPA));
			progress = 1-m_progress;
		}

		LDraw::Bitmap* pResultBitmap = new LDraw::Bitmap((int)mediaRect.Width, (int)mediaRect.Height, LDraw::PixelFormat_t::RGB_32);
		if (pResultBitmap)
		{
			SMILTransitionFactory* transitionFactory = new SMILTransitionFactory;
			//transitionFactory.CoCreateInstance(CLSID_LSMILTransitionFactory);
			if (transitionFactory)
			{
				/*
				_RectD rectA;
				rectA.X = 0;
				rectA.Y = 0;
				rectA.Width = pBitmapA->GetWidth();
				rectA.Height = pBitmapA->GetHeight();

				_RectD rectB;
				rectB.X = 0;
				rectB.Y = 0;
				rectB.Width = pBitmapB->GetWidth();
				rectB.Height = pBitmapB->GetHeight();

				_RectD rect;
				rect.X = 0;
				rect.Y = 0;
				rect.Width = mediaRect.Width;
				rect.Height = mediaRect.Height;
				*/

				ISMILTransition* transition;
				transitionFactory->FindTransition(m_type, m_subtype, &transition);
				if (transition)
				{
					transitionFactory->ProcessTransition(transition,
						m_horzRepeat, m_vertRepeat,
						0, 0,
						progress,
						/*rectA,*/ pBitmapA,
						/*rectB,*/ pBitmapB,
						/*rect,*/ pResultBitmap);
				}

				//LDraw::Graphics graphics(hDC);

				pGraphics->DrawImage(pResultBitmap,
					mediaRect,
					0, 0, mediaRect.Width, mediaRect.Height/*,
					LDraw::UnitPixel*/);
			}

			//delete pResultBitmap;
		}

	//	delete pBitmapA;
	//	delete pBitmapB;
	}
}

void CTransitionDirectionUI::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() !=  System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
			evt->stopPropagation();
			OnLButtonDown(dynamic_cast<UI::MouseEvent*>(evt));
		}
	}
}

void CTransitionDirectionUI::OnLButtonDown(UI::MouseEvent* evt)
{
	LDraw::PointD pt = ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());
//	point.x = (short)LOWORD(lParam);
//	point.y = (short)HIWORD(lParam);

//	CRect client = m_rcPos;
//	CPoint pt = point;
//	pt.x -= client.left;
//	pt.y -= client.top;

	LDraw::SizeD client = get_ActualSize();

	int uiwidth = client.Height;//Width;
	int uiheight = client.Height;

	int cx = uiwidth/2;
	int cy = uiheight/2;

	uint8 arrowFlags = 0;
	bool bOpposite = m_flags & (1<<0);

	if ((m_bitCorners & bitUpperLeft) && pt.X < 8 && pt.Y < 8)
	{
		arrowFlags = bitUpperLeft;
		if (bOpposite) arrowFlags |= bitLowerRight;
	}
	else if ((m_bitCorners & bitLowerLeft) && pt.X < 8 && pt.Y > uiheight-8)
	{
		arrowFlags = bitLowerLeft;
		if (bOpposite) arrowFlags |= bitUpperRight;
	}
	else if ((m_bitCorners & bitUpperRight) && pt.X > uiwidth-8 && pt.Y < 8)
	{
		arrowFlags = bitUpperRight;
		if (bOpposite) arrowFlags |= bitLowerLeft;
	}
	else if ((m_bitCorners & bitLowerRight) && pt.X > uiwidth-8 && pt.Y > uiheight-8)
	{
		arrowFlags = bitLowerRight;
		if (bOpposite) arrowFlags |= bitUpperLeft;
	}
	else if ((m_bitCorners & bitTop) && abs(pt.X-cx) < 4 && pt.Y < 8)
	{
		arrowFlags = bitTop;
		if (bOpposite) arrowFlags |= bitBottom;
	}
	else if ((m_bitCorners & bitBottom) && abs(pt.X-cx) < 4 && pt.Y > uiheight-8)
	{
		arrowFlags = bitBottom;
		if (bOpposite) arrowFlags |= bitTop;
	}
	else if ((m_bitCorners & bitLeft) && pt.X < 8 && abs(pt.Y-cy) < 4)
	{
		arrowFlags = bitLeft;
		if (bOpposite) arrowFlags |= bitRight;
	}
	else if ((m_bitCorners & bitRight) && pt.X > uiwidth-8 && abs(pt.Y-cy) < 4)
	{
		arrowFlags = bitRight;
		if (bOpposite) arrowFlags |= bitLeft;
	}

	if (arrowFlags)
	{
		if (true)//prplugin->bExclusiveCorners)	// Exclusive
		{
			m_arrowFlags = arrowFlags;
		}
		else	// Toggle
		{
			/*
			if ((*(effectHandle))->arrowFlags & arrowFlags)
			{
				(*(effectHandle))->arrowFlags &= ~arrowFlags;
			}
			else
			{
				(*(effectHandle))->arrowFlags |= arrowFlags;
			}
			*/
		}

	//	m_pLayer->FindParam('dir ', 0)->UpdateParamRect(NULL);

		{
		ArrowFlagsEvent* evt = new ArrowFlagsEvent;
		evt->InitEvent(WSTR("ArrowFlagsChanged"), true, true);
		evt->arrowFlags = m_arrowFlags;
		dispatchEvent(evt);
#if 0
		Fire_OnChanged(m_arrowFlags);
#endif
		}

		Invalidate();
	}
}

ErrorCode CTransitionDirectionUI::get_bitCorners(long *pVal)
{
	*pVal = m_bitCorners;
	return Success;
}

ErrorCode CTransitionDirectionUI::set_bitCorners(long newVal)
{
	m_bitCorners = (uint8)newVal;

	Invalidate();
	return Success;
}

long CTransitionDirectionUI::get_arrowFlags()
{
	return m_arrowFlags;
}

void CTransitionDirectionUI::set_arrowFlags(long newVal)
{
	m_arrowFlags = (uint8)newVal;

	Invalidate();
}

ErrorCode CTransitionDirectionUI::get_flags(long *pVal)
{
	*pVal = m_flags;
	return Success;
}

ErrorCode CTransitionDirectionUI::set_flags(long newVal)
{
	m_flags = (uint8)newVal;

	Invalidate();

	return Success;
}

ErrorCode CTransitionDirectionUI::SetTransition(System::StringW* type, System::StringW* subtype, long horzRepeat, long vertRepeat, long borderWidth, LDraw::Color borderColor)
{
	m_type = type;
	m_subtype = subtype;
	m_horzRepeat = horzRepeat;
	m_vertRepeat = vertRepeat;

	Invalidate();

	return Success;
}


bool CTransitionDirectionUI::get_reverse()
{
	return m_reverse;
}

void CTransitionDirectionUI::set_reverse(bool newVal)
{
	m_reverse = newVal;
	Invalidate();
}

}	// LXmlEdit
}
