#include "stdafx.h"
#include "LXUI.h"

#include <cwchar>

#if AMIGA
#include "../amiga_header.h"
#endif

#if AMIGA

#include <proto/commodities.h>

void SetCursorPos(int X, int Y)
{
//	printf("SetCursor(%d, %d)\n", X, Y);

	/*
	IEPointerPixel ipp;
	ipp.iepp_Screen = g_Screen;
	ipp.iepp_Position.X = X;
	ipp.iepp_Position.Y = Y;
	*/

	InputEvent evt;
	memset(&evt, 0, sizeof(evt));
	evt.ie_Class = IECLASS_POINTERPOS;//IECLASS_NEWPOINTERPOS;
	evt.ie_SubClass = 0;//IESUBCLASS_PIXEL;
	evt.ie_EventAddress = NULL;//&ipp;
	evt.ie_X = X;
	evt.ie_Y = Y;

	ASSERT(0);
#if 0
	AddIEvents(&evt);
#endif
}

#endif

#if 0
#include "LXUIFrameContent.h"
// TODO, REMOVE
void CLXUIFrameContent::Free()
{
	ASSERT(0);
}
#endif

namespace System
{

UIEXT int IdentNameToIndex(const OLECHAR* ident, const OLECHAR* idents[])
{
	int i = 0;
	while (idents[i] != NULL)
	{
#if _WINDOWS
		if (!_wcsicmp(ident, idents[i]))
#elif AMIGA
			if (!std::strcmp(ident, idents[i]))
#endif
		{
			return i;
		}

		i++;
	}

	return -1;
}

}

#if AMIGA

#if 0

extern FILE* fplog2;

void LOG2(const char* s);


#endif

#endif

/*
LONG InterlockedIncrement(LONG* lpAddend)
{
	return ++(*lpAddend);
}

LONG InterlockedDecrement(LONG* lpAddend)
{
	return --(*lpAddend);
}
*/

namespace System
{
namespace UI
{
////////////////////////////
// CDocumentSheet

#if 0
void CDocumentSheet::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	if (*type == *WSTR("DLGActivate"))
	{
		MessageBeep((UINT)-1);
	//	m_pViewGroup->OnActivate(TRUE);
	}
	else if (*type == *WSTR("DLGDeactivate"))
	{
		MessageBeep((UINT)-1);
	//	m_pViewGroup->OnActivate(FALSE);
	}
}
#endif

/*
STDMETHODIMP CDocumentSheet::OnDlgActivate(BOOL bActive)
{
	return S_OK;
}

#include "EXMLViewGroup.h"

STDMETHODIMP CDocumentSheet::OnDlgClose()
{
	CArray<IEViewGroup*,IEViewGroup*> list;
	for (int i = 0; i < m_groups.GetSize(); i++)
	{
		list.Add(m_groups[i]);
	}

	for (i = 0; i < list.GetSize(); i++)
	{
		if (list[i]->OnDlgClose() == S_FALSE)
			return S_OK;
	}

	return S_OK;
}

void CDocumentSheet::RemoveViewGroup(IEViewGroup* viewGroup)
{
	ASSERT(0);
#if 0
	CComPtr<IUIDlgSite> dlgSite;
	m_sheet->GetDlgSite(&dlgSite);

	CComPtr<IUIDockBar> dockBar;
	dockBar = dlgSite->m_pDockBar;//GetDockBar(&dockBar);

	for (int i = 0; i < m_groups.GetSize(); i++)
	{
		if (m_groups[i] == viewGroup)
		{
			dockBar->RemoveControlBar(dlgSite);

			m_groups.RemoveAt(i);

#ifdef _DEBUG	// There can't be the same viewgroup
			for (; i < m_groups.GetSize(); i++)
			{
				if (m_groups[i] == viewGroup)
				{
					ASSERT(0);
				}
			}
#endif
			return;
		}
	}

	ASSERT(0);	// viewGroup not found in list, error
#endif
}
*/

#if 0
KeyEvent::KeyEvent()
{
	bAlt = 0;
	bControl = 0;
	bShift = 0;
}

CharEvent::CharEvent()
{
	bAlt = 0;
	bControl = 0;
	bShift = 0;
}

QueryCursorEvent::QueryCursorEvent()
{
	m_Cursor = NULL;
}

void QueryCursorEvent::InitQueryCursorEvent(StringW* eventType, double ScreenX, double ScreenY)
{
	InitEvent(eventType, true, true);

	m_ScreenX = ScreenX;
	m_ScreenY = ScreenY;
}
#endif

////////////////////////////
// CViewSheet

#if 0
void CViewSheet::handleEvent(Event* evt)
{
	ASSERT(0);
#if 0
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"DLGActivate"))
	{
		m_pViewGroup->OnActivate(TRUE);
	}
	else if (!wcscmp(type, L"DLGDeactivate"))
	{
		m_pViewGroup->OnActivate(FALSE);
	}
#endif
}
#endif

/*
STDMETHODIMP CViewSheet::OnDlgActivate(BOOL bActivate)
{
	return S_OK;
}

STDMETHODIMP CViewSheet::OnDlgClose()
{
	m_pViewGroup->OnClose();
	return S_OK;
}
*/

///////////////////////////////////
// CViewGroup

void CViewGroup::Activate(bool bActivate)
{
	ASSERT(0);
#if 0
	if (bActivate)
	{
		for (int i = 0; i < m_dialogs.GetSize(); i++)
		{
			ILXUIElement* parentNode;
			m_dialogs[i]->get_parentNode(&parentNode);

			ILXUIElement* parentNode2;
			parentNode->get_parentNode(&parentNode2);

			CComQIPtr<ILXUISheetElement>(parentNode2)->setActivePage(CComVariant(parentNode));

			/*
			CComPtr<IUIDlgSite> dlgSite;
			m_dialogs[i]->GetDlgSite(&dlgSite);

			if (CComQIPtr<IUIDlgSheet>(dlgSite->m_pDockBar))
				CComQIPtr<IUIDlgSheet>(dlgSite->m_pDockBar)->SetActivePage(dlgSite);
				*/
		}
	}
	else
	{
		for (int i = 0; i < m_dialogs.GetSize(); i++)
		{
			ILXUIElement* parentNode;
			m_dialogs[i]->get_parentNode(&parentNode);

			ILXUIElement* parentNode2;
			parentNode->get_parentNode(&parentNode2);

			CComQIPtr<ILXUISheetElement>(parentNode2)->setActivePage(CComVariant(/*NULL*/));

#if 0
			CComPtr<ILDOMNode> parentNode;
			m_dialogs[i]->get_parentNode(&parentNode);

			CComQIPtr<ILXUISheetElement>(parentNode)->setActivePage(CComVariant(/*NULL*/));
			/*
			CComPtr<IUIDlgSite> dlgSite;
			m_dialogs[i]->GetDlgSite(&dlgSite);

			if (CComQIPtr<IUIDlgSheet>(dlgSite->m_pDockBar))
				CComQIPtr<IUIDlgSheet>(dlgSite->m_pDockBar)->SetActivePage(NULL);
				*/
#endif
		}
/*
		for (int i = 0; i < m_viewDialogs.GetSize(); i++)
		{
			m_viewDialogs[i]->m_sheet->SetActivePage(NULL);
		}
		*/
	}
#endif
}

Graphics::Graphics()
{
	m_p = NULL;
#if 0
	m_clip2 = LDraw::RectF(0, 0, 0xffffff, 0xffffff);
	m_invalidRegion = NULL;
#endif
}

Graphics::Graphics(LDraw::Graphics2D* p)
{
	m_p = p;
#if 0
	m_clip2 = LDraw::RectF(0, 0, 0xffffff, 0xffffff);
	m_invalidRegion = NULL;
#endif
}

Graphics::~Graphics()
{
}

/*
Graphics::Graphics(const LDraw::Graphics& other) : LDraw::Graphics(other)
{
	m_clip2 = LDraw::RectF(0, 0, 0xffffff, 0xffffff);
}
*/

/*
Graphics::Graphics(const Graphics& other)
{
	m_p = other.m_p;
	if (m_p)
	{
		m_p->AddRef();
	}
}

Graphics::Graphics(Graphics2D* p)
{
	m_p = p;
	if (m_p)
	{
		m_p->AddRef();
	}
}

Graphics::~Graphics()
{
	if (m_p)
	{
		m_p->Release();
	}
}

Graphics& Graphics::operator = (const Graphics& other)
{
	GraphicsBase* old = m_p;
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
	if (old) old->Release();
	return *this;
}
*/

/*
void Graphics::TranslateTransform(float x, float y)
{
	//MultiplyTransform(Matrix::Translate(x, y));
	Matrix transform = GetTransform();
	transform.SetTranslate(x, y));
	SetTransform(transform);
}

void Graphics::ScaleTransform(float sx, float sy)
{
	Matrix transform = GetTransform();
//	MultiplyTransform(Matrix::Scale(sx, sy));
	transform.SetTranslate(x, y));
	SetTransform(transform);
}

void Graphics::RotateTransform(float angle)
{
	Matrix transform = GetTransform();
//	MultiplyTransform(Matrix::Rotate(angle));
	SetTransform(transform);
}
*/

void Graphics::PushTransform()
{
	if (m_p)
	m_p->PushTransform();
}

void Graphics::PopTransform()
{
	if (m_p)
	m_p->PopTransform();
}

void Graphics::PushClip()
{
	if (m_p)
	m_p->PushClip();
}

void Graphics::PopClip()
{
	if (m_p)
	m_p->PopClip();
}

void Graphics::MultiplyColorTransform(const LDraw::ColorMatrixF& colorMatrix)
{
	m_p->MultiplyColorTransform(colorMatrix);
}

void Graphics::SetLookupTables(const LDraw::LookupTables& luts)
{
	m_p->SetLookupTables(luts);
}

void Graphics::RenderCommands(LDraw::Commands* commands)
{
	m_p->RenderCommands(commands);
}

void Graphics::DrawImage(LDraw::Bitmap* bitmap, const LDraw::RectF& destRect, float srcX, float srcY, float srcWidth, float srcHeight, LDraw::WrapMode wrapMode, const LDraw::ColorMatrixF* colorMatrix)
{
	m_p->DrawImage(bitmap, destRect, srcX, srcY, srcWidth, srcHeight, wrapMode, colorMatrix);
}

void Graphics::DrawImage(LDraw::Bitmap* bitmap, const LDraw::PointF destPoints[3], float srcX, float srcY, float srcWidth, float srcHeight, LDraw::WrapMode wrapMode, const LDraw::ColorMatrixF* colorMatrix)
{
	m_p->DrawImage(bitmap, destPoints, srcX, srcY, srcWidth, srcHeight, wrapMode, colorMatrix);
}

void Graphics::DrawImage(LDraw::Bitmap* bitmap, float x, float y, LDraw::WrapMode wrapMode, const LDraw::ColorMatrixF* colorMatrix)
{
	if (bitmap == NULL)
		THROW(-1);

	int width = bitmap->GetWidth();
	int height = bitmap->GetHeight();

	DrawImage(bitmap, LDraw::RectF(x, y, width, height), 0, 0, width, height, wrapMode, colorMatrix);
}

void Graphics::DrawImage(LDraw::Bitmap* bitmap, const LDraw::RectI& destRect, float srcX, float srcY, float srcWidth, float srcHeight, LDraw::WrapMode wrapMode, const LDraw::ColorMatrixF* colorMatrix)
{
	LDraw::RectF destRectF(destRect.X, destRect.Y, destRect.Width, destRect.Height);
	DrawImage(bitmap, destRectF, srcX, srcY, srcWidth, srcHeight, wrapMode, colorMatrix);
}

void Graphics::DrawImage(LDraw::Bitmap* bitmap, const LDraw::RectD& destRect, float srcX, float srcY, float srcWidth, float srcHeight, LDraw::WrapMode wrapMode, const LDraw::ColorMatrixF* colorMatrix)
{
	LDraw::RectF destRectF(destRect.X, destRect.Y, destRect.Width, destRect.Height);
	DrawImage(bitmap, destRectF, srcX, srcY, srcWidth, srcHeight, wrapMode, colorMatrix);
}

void Graphics::DrawLine(LDraw::Pen* pPen, LDraw::PointI start, LDraw::PointI end)
{
	DrawLine(pPen, start.X, start.Y, end.X, end.Y);
}

void Graphics::DrawLine(LDraw::Pen* pPen, LDraw::PointF start, LDraw::PointF end)
{
	DrawLine(pPen, start.X, start.Y, end.X, end.Y);
}

void Graphics::DrawLine(LDraw::Pen* pPen, const LDraw::PointD& start, const LDraw::PointD& end)
{
	DrawLine(pPen, start.X, start.Y, end.X, end.Y);
}

void Graphics::DrawLine(LDraw::Pen* pPen, float x1, float y1, float x2, float y2)
{
	/*
//	GraphicsPathF path;
//	path.AddMove(x1, y1);
//	path.AddLine(x2, y2);

	LDraw::PointF pts[] =
	{
		LDraw::PointF(x1, y1),
		LDraw::PointF(x2, y2),
	};

	DrawPolygon(pPen, pts, 2);
	*/
	m_p->DrawLine(pPen, x1, y1, x2, y2);
}

void Graphics::FillRectangle(LDraw::Brush* brush, const LDraw::RectI& rect)
{
	m_p->FillRectangle(brush, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::FillRectangle(LDraw::Brush* brush, const LDraw::RectF& rect)
{
	m_p->FillRectangle(brush, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::FillRectangle(LDraw::Brush* brush, const LDraw::RectD& rect)
{
	m_p->FillRectangle(brush, float(rect.X), float(rect.Y), float(rect.Width), float(rect.Height));
}

void Graphics::FillRectangle(LDraw::Brush* brush, float x, float y, float width, float height)
{
	m_p->FillRectangle(brush, x, y, width, height);
}

void Graphics::FillRectangles(LDraw::Brush* brush, const LDraw::RectI* rects, int count)
{
	while (count--)
	{
		FillRectangle(brush, *rects);
		rects++;
	}
}

void Graphics::FillRectangles(LDraw::Brush* brush, const LDraw::RectF* rects, int count)
{
	while (count--)
	{
		m_p->FillRectangle(brush, rects->X, rects->Y, rects->Width, rects->Height);
		rects++;
	}
}

void Graphics::FillRectangles(LDraw::Brush* brush, const LDraw::RectD* rects, int count)
{
	while (count--)
	{
		FillRectangle(brush, *rects);
		rects++;
	}
}

void Graphics::FillEllipse(LDraw::Brush* brush, const LDraw::RectI& rect)
{
	FillEllipse(brush, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::FillEllipse(LDraw::Brush* brush, const LDraw::RectF& rect)
{
	FillEllipse(brush, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::FillEllipse(LDraw::Brush* brush, LDraw::PointF corner, LDraw::SizeF size)
{
	FillEllipse(brush, corner.X, corner.Y, size.Width, size.Height);
}

void Graphics::FillEllipse(LDraw::Brush* brush, float x, float y, float width, float height)
{
	m_p->FillEllipse(brush, x, y, width, height);
	/*
	LDraw::GraphicsPathF* path = new LDraw::GraphicsPathF;
	path->AddEllipse(x, y, width, height);
	FillPath(brush, path);
	*/
}

void Graphics::DrawRectangle(LDraw::Pen* pPen, const LDraw::RectI& rect)
{
	m_p->DrawRectangle(pPen, float(rect.X), float(rect.Y), float(rect.Width), float(rect.Height));
}

void Graphics::DrawRectangle(LDraw::Pen* pPen, const LDraw::RectF& rect)
{
	m_p->DrawRectangle(pPen, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::DrawRectangle(LDraw::Pen* pPen, const LDraw::RectD& rect)
{
	m_p->DrawRectangle(pPen, float(rect.X), float(rect.Y), float(rect.Width), float(rect.Height));
}

void Graphics::DrawRectangle(LDraw::Pen* pPen, float x, float y, float width, float height)
{
	m_p->DrawRectangle(pPen, x, y, width, height);
}

void Graphics::DrawEllipse(LDraw::Pen* pPen, const LDraw::RectI& rect)
{
	DrawEllipse(pPen, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::DrawEllipse(LDraw::Pen* pPen, const LDraw::RectF& rect)
{
	DrawEllipse(pPen, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::DrawEllipse(LDraw::Pen* pPen, const LDraw::RectD& rect)
{
	DrawEllipse(pPen, rect.X, rect.Y, rect.Width, rect.Height);
}

void Graphics::DrawEllipse(LDraw::Pen* pPen, float x, float y, float width, float height)
{
	m_p->DrawEllipse(pPen, x, y, width, height);
}

void Graphics::DrawBezier(LDraw::Pen* pPen, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	ASSERT(0);
}

void Graphics::IntersectClip(const LDraw::RectI& rect)
{
	m_p->SetClip(rect, LDraw::CombineModeIntersect);
}

void Graphics::IntersectClip(const LDraw::RectD& rect)
{
	m_p->IntersectClip(rect);//.X, rect.Y, rect.Width, rect.Height);
}

/*
void Graphics::IntersectClip(const LDraw::RectF& rect)
{
	m_p->SetClip(rect, LDraw::CombineModeIntersect);
}

void Graphics::IntersectClip(const LDraw::RectD& rect)
{
	m_p->SetClip(rect, LDraw::CombineModeIntersect);
}
*/

void Graphics::IntersectClip(LDraw::Region* rgn)
{
	m_p->SetClip(rgn, LDraw::CombineModeIntersect);
}

/*
void Graphics::SetClip(const Rect& rect, CombineMode combineMode)
{
	SetClip(RectF(float(rect.X), float(rect.Y), float(rect.Width), float(rect.Height)), combineMode);
}

void Graphics::SetClip(const RectD& rect, CombineMode combineMode)
{
	SetClip(RectF(float(rect.X), float(rect.Y), float(rect.Width), float(rect.Height)), combineMode);
}

void Graphics::SetClip(GraphicsPathF* path, CombineMode combineMode)
{
	m_p->SetClip(path, combineMode);
}
*/

void Graphics::DrawGlyph(uint glyph, LDraw::Font* font, LDraw::PointF point, LDraw::Brush* brush)
{
	m_p->DrawGlyph(glyph, font, point, brush);
}

void Graphics::DrawString(StringA* str, LDraw::Font* font, LDraw::PointF point, LDraw::Brush* brush)
{
	m_p->DrawString(str, font, point, brush);
}

void Graphics::DrawString(StringW* str, LDraw::Font* font, LDraw::PointF point, LDraw::Brush* brush)
{
	m_p->DrawString(str, font, point, brush);
}

void Graphics::DrawString(const char* str, int len, LDraw::Font* font, LDraw::PointF point, LDraw::Brush* brush)
{
	m_p->DrawString(str, len, font, point, brush);
//	m_p->DrawString(new StringA(string_copy(str, len)), font, point, brush);
}

void Graphics::DrawString(const WCHAR* str, int len, LDraw::Font* font, LDraw::PointF point, LDraw::Brush* brush)
{
	m_p->DrawString(str, len, font, point, brush);
//	m_p->DrawString(new StringW(string_copy(str, len)), font, point, brush);
}

void Graphics::DrawString(const char* str, int len, LDraw::Font* font, const LDraw::RectF& rect, LDraw::Brush* brush)
{
	m_p->DrawString(new StringA(string_copy(str, len)), font, rect, brush);
}

void Graphics::DrawString(const WCHAR* str, int len, LDraw::Font* font, const LDraw::RectF& rect, LDraw::Brush* brush)
{
	m_p->DrawString(new StringW(string_copy(str, len)), font, rect, brush);
}

void Graphics::DrawString(StringA* str, LDraw::Font* font, const LDraw::RectF& rect, LDraw::Brush* pBrush)
{
	m_p->DrawString(str, font, rect, pBrush);
}

void Graphics::DrawString(StringW* str, LDraw::Font* font, const LDraw::RectF& rect, LDraw::Brush* pBrush)
{
	m_p->DrawString(str, font, rect, pBrush);
}

void Graphics::DrawStrings(System::StringA* const strs[], LDraw::Font* font, const LDraw::PointF* points, LDraw::Brush* brush, unsigned int count)
{
	m_p->DrawStrings(strs, font, points, brush, count);
}

void Graphics::DrawStrings(System::StringW* const strs[], LDraw::Font* font, const LDraw::PointF* points, LDraw::Brush* brush, unsigned int count)
{
	m_p->DrawStrings(strs, font, points, brush, count);
}

/*
void Graphics::DrawString(const void* str, bool bWide, int len, Font* pFont, PointF point, const Brush* pBrush)
{
	m_p->DrawString(str, bWide, len, pFont, point, pBrush);
}

void Graphics::DrawString(const void* str, bool bWide, int len, Font* pFont, const RectF& rect, const Brush* pBrush)
{
	m_p->DrawString(str, bWide, len, pFont, rect, pBrush);
}
*/

double Graphics::MeasureString(const char* str, int len, LDraw::Font* font) const
{
	return m_p->MeasureString(str, len, font);
}

/*
double Graphics::MeasureString(const char* str, int len, Font* pFont) const
{
	return m_p->MeasureString(str, len, pFont);
}
*/
double Graphics::MeasureString(const WCHAR* str, int len, LDraw::Font* font) const
{
	return m_p->MeasureString(str, len, font);
}

DependencyProperty* BitmapVisual::s_BitmapProperty = RegisterProperty(WSTR("Bitmap"), typeid(LDraw::Bitmap), typeid(BitmapVisual), NULL, PropertyMetaData(AffectsMeasure));

BitmapVisual::BitmapVisual()
{
}

}	// UI
}	// System
