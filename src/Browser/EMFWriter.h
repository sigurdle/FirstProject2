#pragma once

#include "wmf.h"

namespace System
{
namespace wmf
{

class EMFWriter
{
public:
	CTOR EMFWriter()
	{
		m_recs = 0;
		m_handles = 0;
	}

	int m_recs;
	int m_handles;

void WriteSetMapMode(System::IO::ISequentialByteStream* stream, uint32 mode);
void WriteSetWindowOrgEx(System::IO::ISequentialByteStream* stream, int32 x, int32 y);
void WriteSetWindowExtEx(System::IO::ISequentialByteStream* stream, int32 cx, int32 cy);
void WriteSetViewportOrgEx(System::IO::ISequentialByteStream* stream, int32 x, int32 y);
void WriteSetViewportExtEx(System::IO::ISequentialByteStream* stream, int32 cx, int32 cy);
void WriteDeleteObject(System::IO::ISequentialByteStream* stream, uint32 n);
void WriteSelectObject(System::IO::ISequentialByteStream* stream, uint32 n);
void WriteSetBkMode(System::IO::ISequentialByteStream* stream, uint32 imode);
void WriteCreatePen(System::IO::ISequentialByteStream* stream, uint32 n, const LOGPEN& lp);
void WriteCreateBrushIndirect(System::IO::ISequentialByteStream* stream, uint32 n, const LOGBRUSH& lb);
void WriteSetWorldTransform(System::IO::ISequentialByteStream* stream, const XFORM &xform);
void WriteSetWorldTransform(System::IO::ISequentialByteStream* stream, const LDraw::matrix3f& transform);
void WriteModifyWorldTransform(System::IO::ISequentialByteStream* stream, const XFORM& xform, uint32 iMode = MWT_LEFTMULTIPLY);
void WriteModifyWorldTransform(System::IO::ISequentialByteStream* stream, const LDraw::matrix3f& transform, uint32 iMode = MWT_LEFTMULTIPLY);
void WritePolygon(System::IO::ISequentialByteStream* stream, const LDraw::BBoxi& bounds, uint cpts, const LDraw::PointF* points);
void WriteRectangle(System::IO::ISequentialByteStream* stream, const LDraw::BBoxi& bounds);
void WriteRectangle(System::IO::ISequentialByteStream* stream, const LDraw::RectF& bounds);
void WriteExtCreateFontIndirectW(System::IO::ISequentialByteStream* stream, const EXTLOGFONTW &lf, uint32 index);
void WriteExtCreateFontIndirectW(System::IO::ISequentialByteStream* stream, LDraw::Font* font, uint32 index);
void WriteExtTextOutA(System::IO::ISequentialByteStream* stream, System::StringA* text, int32 x, int32 y, uint32 iGraphicsMode);
void WriteEOF(System::IO::ISequentialByteStream* stream);
void WriteCommands(System::IO::ISequentialByteStream* stream, const LDraw::matrix3f& startTransform, LDraw::Commands* commands);
};

}	// wmf
}	// System
