#include "stdafx.h"
#include "EMFWriter.h"

namespace System
{
namespace wmf
{

void EMFWriter::WriteSetMapMode(IO::ISequentialByteStream* stream, uint32 mode)
{
	m_recs++;
	uint32 RecordType = emfSETMAPMODE;
	uint32 RecordSize = 8+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&mode, 4);
}

void EMFWriter::WriteSetWindowOrgEx(IO::ISequentialByteStream* stream, int32 x, int32 y)
{
	m_recs++;
	uint32 RecordType = emfSETWINDOWORGEX;
	uint32 RecordSize = 8+4+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&x, 4);
	stream->Write(&y, 4);
}

void EMFWriter::WriteSetWindowExtEx(IO::ISequentialByteStream* stream, int32 cx, int32 cy)
{
	m_recs++;
	uint32 RecordType = emfSETWINDOWEXTEX;
	uint32 RecordSize = 8+4+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&cx, 4);
	stream->Write(&cy, 4);
}

void EMFWriter::WriteSetViewportOrgEx(IO::ISequentialByteStream* stream, int x, int y)
{
	m_recs++;
	uint32 RecordType = emfSETVIEWPORTORGEX;
	uint32 RecordSize = 8+4+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&x, 4);
	stream->Write(&y, 4);
}

void EMFWriter::WriteSetViewportExtEx(IO::ISequentialByteStream* stream, int cx, int cy)
{
	m_recs++;
	uint32 RecordType = emfSETVIEWPORTEXTEX;
	uint32 RecordSize = 8+4+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&cx, 4);
	stream->Write(&cy, 4);
}

void EMFWriter::WriteDeleteObject(IO::ISequentialByteStream* stream, uint32 n)
{
	m_recs++;
	uint32 RecordType = emfDELETEOBJECT;
	uint32 RecordSize = 8+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&n, 4);
}

void EMFWriter::WriteSelectObject(IO::ISequentialByteStream* stream, uint32 n)
{
	m_recs++;
	uint32 RecordType = emfSELECTOBJECT;
	uint32 RecordSize = 8+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&n, 4);
}

void EMFWriter::WriteSetBkMode(IO::ISequentialByteStream* stream, uint32 imode)
{
	m_recs++;
	uint32 RecordType = emfSETBKMODE;
	uint32 RecordSize = 8+4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&imode, 4);
}

void EMFWriter::WriteCreatePen(IO::ISequentialByteStream* stream, uint32 n, const LOGPEN& lp)
{
	m_recs++;
	uint32 RecordType = emfCREATEPEN;
	uint32 RecordSize = 8+4 + sizeof(lp);
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&n, 4);

	stream->Write(&lp, sizeof(lp));
}

void EMFWriter::WriteCreateBrushIndirect(IO::ISequentialByteStream* stream, uint32 n, const LOGBRUSH& lb)
{
	m_recs++;
	uint32 RecordType = emfCREATEBRUSHINDIRECT;
	uint32 RecordSize = 8+4 + sizeof(lb);
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&n, 4);

	stream->Write(&lb, sizeof(lb));
}

void EMFWriter::WriteSetWorldTransform(IO::ISequentialByteStream* stream, const XFORM &xform)
{
	m_recs++;
	uint32 RecordType = emfSETWORLDTRANSFORM;
	uint32 RecordSize = 8 + sizeof(XFORM);
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&xform, sizeof xform);
}

void EMFWriter::WriteSetWorldTransform(IO::ISequentialByteStream* stream, const LDraw::matrix3f& m)
{
//	float m[3][2];
//	transform->Get(m);

	XFORM xform;
	xform.eM11 = m[0][0];
	xform.eM12 = m[0][1];
	xform.eM21 = m[1][0];
	xform.eM22 = m[1][1];
	xform.eDx = m[2][0];
	xform.eDy = m[2][1];

	WriteSetWorldTransform(stream, xform);
}

void EMFWriter::WriteModifyWorldTransform(IO::ISequentialByteStream* stream, const XFORM& xform, uint32 iMode)
{
	m_recs++;
	uint32 RecordType = emfMODIFYWORLDTRANSFORM;
	uint32 RecordSize = 8 + 4 + sizeof(XFORM);
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&xform, sizeof xform);
	stream->Write(&iMode, 4);
}

void EMFWriter::WriteModifyWorldTransform(IO::ISequentialByteStream* stream, const LDraw::matrix3f& m, uint32 iMode)
{
//	float m[3][2];
//	transform->Get(m);

	XFORM xform;
	xform.eM11 = m[0][0];
	xform.eM12 = m[0][1];
	xform.eM21 = m[1][0];
	xform.eM22 = m[1][1];
	xform.eDx = m[2][0];
	xform.eDy = m[2][1];

	WriteModifyWorldTransform(stream, xform, iMode);
}

void EMFWriter::WritePolygon(IO::ISequentialByteStream* stream, const LDraw::BBoxi& bounds, uint cpts, const LDraw::PointF* points)
{
	m_recs++;
	uint32 RecordType = emfPOLYGON16;
	uint32 RecordSize = 8 + 16 + 4 + cpts*4;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&bounds, sizeof bounds);

	stream->Write(&cpts, 4);

	{
		for (uint i = 0; i < cpts; i++)
		{
			short x = points[i].X;
			short y = points[i].Y;

			stream->Write(&x, 2);
			stream->Write(&y, 2);
		}
	}
}

void EMFWriter::WriteRectangle(IO::ISequentialByteStream* stream, const LDraw::BBoxi& bounds)
{
	m_recs++;
	uint32 RecordType = emfRECTANGLE;
	uint32 RecordSize = 8 + 16;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&bounds, 16);
}

void EMFWriter::WriteRectangle(IO::ISequentialByteStream* stream, const LDraw::RectF& bounds)
{
	LDraw::BBoxi bbox(bounds.X, bounds.Y, bounds.GetRight(), bounds.GetBottom());
	WriteRectangle(stream, bbox);
}

void EMFWriter::WriteExtCreateFontIndirectW(IO::ISequentialByteStream* stream, const EXTLOGFONTW &lf, uint32 index)
{
	m_recs++;
	uint32 RecordType = emfEXTCREATEFONTINDIRECTW;
	uint32 RecordSize = 8 + 4 + sizeof(lf) + 2;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	stream->Write(&index, 4);
	stream->Write(&lf, sizeof(lf));

	// dword align
	uint16 pad = 0;
	stream->Write(&pad, 2);
}

void EMFWriter::WriteExtCreateFontIndirectW(IO::ISequentialByteStream* stream, LDraw::Font* font, uint32 index)
{
	EXTLOGFONTW lf = {0};
	lf.elfLogFont.lfHeight = font->GetSize();	// TODO
	lf.elfLogFont.lfWeight = FW_NORMAL;
	lf.elfLogFont.lfCharSet = ANSI_CHARSET;
	lf.elfLogFont.lfPitchAndFamily = DEFAULT_PITCH;
	std::wcscpy(lf.elfLogFont.lfFaceName, font->GetFamily()->GetName()->c_str());
//	wcscpy(lf.elfFullName, font.GetFamily().GetName().c_str());

	WriteExtCreateFontIndirectW(stream, lf, index);
}

void EMFWriter::WriteExtTextOutA(IO::ISequentialByteStream* stream, StringA* text, int32 x, int32 y, uint32 iGraphicsMode)
{
	m_recs++;
	uint32 RecordType = emfEXTTEXTOUTA;
	uint32 RecordSize = 8 + 16 + 4 + 8 + 20 + 16 + 4 + text->Length();
	uint32 PaddedRecordSize = (RecordSize+3) & ~3;
	stream->Write(&RecordType, 4);
	stream->Write(&PaddedRecordSize, 4);

	LDraw::BBoxi bounds(0,0,0,0);
	stream->Write(&bounds, sizeof bounds);
	stream->Write(&iGraphicsMode, 4);
	float exScale = 1;
	float eyScale = 1;
	stream->Write(&exScale, 4);
	stream->Write(&eyScale, 4);

	uint32 length = text->Length();
	uint32 offString = 8 + 16 + 4 + 8 + 20 + 16 + 4;
	uint32 options = 0;

	stream->Write(&x, 4);
	stream->Write(&y, 4);
	stream->Write(&length, 4);
	stream->Write(&offString, 4);
	stream->Write(&options, 4);

	uint16 size = 16;

//	if (options != 0)
	{
		// TODO: ETO_CLIPPED or ETO_OPAQUE 

		int32 left = 0;
		int32 top = 0;
		int32 right = 0;
		int32 bottom = 0;
		stream->Write(&left, 4);
		stream->Write(&top, 4);
		stream->Write(&right, 4);
		stream->Write(&bottom, 4);

		size += 16;
	}

	uint32 offdx = 0;
	stream->Write(&offdx, 4);

	stream->Write(text->c_str(), text->Length());

	ULONG pad = 0;
	stream->Write(&pad, PaddedRecordSize - RecordSize);
}

void EMFWriter::WriteEOF(IO::ISequentialByteStream* stream)
{
	m_recs++;
	uint32 RecordType = emfEOF;
	uint32 RecordSize = 8 + 12;
	stream->Write(&RecordType, 4);
	stream->Write(&RecordSize, 4);

	uint32 nPalEntries = 0;
	uint32 offPalEntries = 0;
	uint32 nSizeLast = RecordSize;

	stream->Write(&nPalEntries, 4);
	stream->Write(&offPalEntries, 4);
	stream->Write(&nSizeLast, 4);
}

void EMFWriter::WriteCommands(IO::ISequentialByteStream* stream, const LDraw::matrix3f& startTransform, LDraw::Commands* commands)
{
	LDraw::matrix3f transform = LDraw::matrix3f::getIdentity();

//	int count = commands->GetCount();
//	for (int i = 0; i < count; i++)

	LDraw::Command* pEnd = commands->GetTail()->m_pNext;
	LDraw::Command* pCommand = pEnd->m_pNext;

	while (pCommand != pEnd)
	{
	//	LDraw::Command* pCommand = commands->GetItem(i);

		if (LDraw::RenderCommandsCommand* p = dynamic_cast<LDraw::RenderCommandsCommand*>(pCommand))
		{
			if (p->m_commands)
			{
				WriteCommands(stream, transform, p->m_commands);
			}
		}
		else if (LDraw::TranslateTransformCommand* p = dynamic_cast<LDraw::TranslateTransformCommand*>(pCommand))
		{
			XFORM xform;
			xform.eM11 = 1;
			xform.eM12 = 0;
			xform.eM21 = 0;
			xform.eM22 = 1;
			xform.eDx = p->m_dx;
			xform.eDy = p->m_dy;

			WriteModifyWorldTransform(stream, xform);
			transform = LDraw::matrix3f::getTranslate(p->m_dx, p->m_dy) * transform;
		}
		else if (LDraw::MultiplyTransformCommand* p = dynamic_cast<LDraw::MultiplyTransformCommand*>(pCommand))
		{
			WriteModifyWorldTransform(stream, p->m_transform->m_matrix);
			transform = p->m_transform->m_matrix * transform;
		}
		else if (LDraw::SetTransformCommand* p = dynamic_cast<LDraw::SetTransformCommand*>(pCommand))
		{
			VERIFY(0);
#if 0

			// TODO, write the combined value
			WriteSetWorldTransform(stream, startTransform);
			WriteModifyWorldTransform(stream, p->m_transform->m_matrix);

			transform = startTransform;
			transform->Multiply(p->m_transform);
#endif
		}
		else if (LDraw::FillRectangleFCommand* p = dynamic_cast<LDraw::FillRectangleFCommand*>(pCommand))
		{
			ASSERT(0);
#if 0

			if (p->m_brush->GetBrushType() == LDraw::BrushTypeLinearGradient)
			{
				LDraw::LinearGradientBrush brush = *(LDraw::LinearGradientBrush*)&p->m_brush;
			}
			else  if (p->m_brush->GetBrushType() == LDraw::BrushTypeSolidColor)
			{
				LDraw::SolidBrush* brush = (LDraw::SolidBrush*)p->m_brush.m_p;
				LDraw::Color color = brush->GetColor();

				LOGBRUSH lb;
				lb.lbStyle = BS_SOLID;
				lb.lbColor = wmfRGB(color.GetR(), color.GetG(), color.GetB());

				WriteCreateBrushIndirect(stream, 2, lb);

				WriteSelectObject(stream, 1);	// NULL_PEN
				WriteSelectObject(stream, 2);

				WriteRectangle(stream, p->m_rect);

				m_handles = MAX(2, m_handles);
				WriteDeleteObject(stream, 2);
			}
#endif
		}
		else if (LDraw::FillPolygonFCommand* p = dynamic_cast<LDraw::FillPolygonFCommand*>(pCommand))
		{
			ASSERT(0);
#if 0
			LDraw::SolidBrush* brush = (LDraw::SolidBrush*)p->m_brush.m_p;
			LDraw::Color color = brush->GetColor();

			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = wmfRGB(color.GetR(), color.GetG(), color.GetB());

			WriteCreateBrushIndirect(stream, 2, lb);
			WriteSelectObject(stream, 1);	// NULL_PEN
			WriteSelectObject(stream, 2);
			m_handles = MAX(2, m_handles);

			LDraw::BBoxi rect(0,0,0,0);

			uint cpts = p->m_points.GetSize();
			
			if (cpts > 0)
			{
				rect.left = p->m_points[0].X;
				rect.top = p->m_points[0].Y;
				rect.right = rect.left;
				rect.bottom = rect.top;

				{
					for (int i = 1; i < cpts; i++)
					{
						rect.left = MIN(rect.left, p->m_points[i].X);
						rect.top = MIN(rect.top, p->m_points[i].Y);
						rect.right = MAX(rect.right, p->m_points[i].X);
						rect.bottom = MAX(rect.bottom, p->m_points[i].Y);
					}
				}
			}

			WritePolygon(stream, rect, cpts, p->m_points.GetData());

			WriteDeleteObject(stream, 2);
#endif
		}
		else if (LDraw::FillPathFCommand* p = dynamic_cast<LDraw::FillPathFCommand*>(pCommand))
		{
			/*
			LDraw::SolidBrush brush = *(LDraw::SolidBrush*)&p->m_brush;
			LDraw::Color color = brush.GetColor();

			wmfLOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(color.GetR(), color.GetG(), color.GetB());

			WriteCreateBrushIndirect(stream, 1, lb);
			WriteSelectObject(stream, 1);
			m_handles = MAX(1, m_handles);

			LDraw::BBoxi rect(0,0,0,0);

			DWORD cpts = p->m_points.size();
			
			if (cpts > 0)
			{
				rect.left = p->m_points[0].X;
				rect.top = p->m_points[0].Y;
				rect.right = rect.left;
				rect.bottom = rect.top;

				{
					for (int i = 1; i < cpts; i++)
					{
						rect.left = MIN(rect.left, p->m_points[i].X);
						rect.top = MIN(rect.top, p->m_points[i].Y);
						rect.right = MAX(rect.right, p->m_points[i].X);
						rect.bottom = MAX(rect.bottom, p->m_points[i].Y);
					}
				}
			}

			WritePolygon(stream, rect, cpts, p->m_points.begin());

			WriteDeleteObject(stream, 1);
			*/
		}
		else if (LDraw::SetClipRectCommand* p = dynamic_cast<LDraw::SetClipRectCommand*>(pCommand))
		{
			// TODO
		}
		else if (LDraw::SetClipRegionCommand* p = dynamic_cast<LDraw::SetClipRegionCommand*>(pCommand))
		{
			// TODO
		}
		else if (LDraw::DrawStringAPointCommand* p = dynamic_cast<LDraw::DrawStringAPointCommand*>(pCommand))
		{
			WriteExtCreateFontIndirectW(stream, p->m_font, 2);
			WriteSelectObject(stream, 2);
			WriteExtTextOutA(stream, p->m_string, p->m_point.X, p->m_point.Y, GM_COMPATIBLE);
			WriteDeleteObject(stream, 2);

			m_handles = MAX(2, m_handles);
		}
		else if (LDraw::DrawStringWRectCommand* p = dynamic_cast<LDraw::DrawStringWRectCommand*>(pCommand))
		{
			// TODO
		}
		else if (LDraw::SetSmoothingModeCommand* p = dynamic_cast<LDraw::SetSmoothingModeCommand*>(pCommand))
		{
			// Do nothing
		}
		else
		{
			ASSERT(0);
		}

		pCommand = pCommand->m_pNext;
	}
}

}	// wmf
}
