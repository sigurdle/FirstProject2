#include "stdafx.h"

#include "HGlobalStream.h"
#include "../SWF/swf.h"

namespace System
{
using namespace IO;

void swfWriteCommands(ISequentialByteStream* stream, LDraw::Matrix3f* startTransform, LDraw::Commands* commands, uint16* id)
{
#if WIN32
	LDraw::Matrix3f* transform = startTransform;
	//transform.Identity();

//	LDraw::Command* pCommand = commands->GetHead();
	LDraw::Command* pEnd = commands->GetTail()->m_pNext;
	LDraw::Command* pCommand = pEnd->m_pNext;

//	int count = commands->GetCount();
	//for (int i = 0; i < count; i++)
	while (pCommand != pEnd)
	{
	//	LDraw::Command* pCommand = commands->GetItem(i);

		if (LDraw::RenderCommandsCommand* p = dynamic_cast<LDraw::RenderCommandsCommand*>(pCommand))
		{
			if (p->m_commands)
			{
				swfWriteCommands(stream, transform, p->m_commands, id);
			}
		}
		else if (LDraw::TranslateTransformCommand* p = dynamic_cast<LDraw::TranslateTransformCommand*>(pCommand))
		{
			/*
			XFORM xform;
			xform.eM11 = 1;
			xform.eM12 = 0;
			xform.eM21 = 0;
			xform.eM22 = 1;
			xform.eDx = p->m_dx;
			xform.eDy = p->m_dy;

			WriteModifyWorldTransform(stream, xform);
			*/
			transform->Translate(p->m_dx, p->m_dy);
		}
		else if (LDraw::MultiplyTransformCommand* p = dynamic_cast<LDraw::MultiplyTransformCommand*>(pCommand))
		{
			//WriteModifyWorldTransform(stream, p->m_transform);
			transform->Multiply(p->m_transform);
		}
		else if (LDraw::SetTransformCommand* p = dynamic_cast<LDraw::SetTransformCommand*>(pCommand))
		{
			/*
			// TODO, write the combined value
			WriteSetWorldTransform(stream, startTransform);
			WriteModifyWorldTransform(stream, p->m_transform);
			*/

			ASSERT(0);
#if 0

			transform = startTransform;
			transform.Multiply(p->m_transform);
#endif
		}
		else if (LDraw::FillPolygonFCommand* p = dynamic_cast<LDraw::FillPolygonFCommand*>(pCommand))
		{
			__release<LDraw::SolidBrush> brush = (LDraw::SolidBrush*)p->m_brush.m_p;
			LDraw::Color color = brush->GetColor();

#if 0
			wmfLOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(color.GetR(), color.GetG(), color.GetB());

			WriteCreateBrushIndirect(stream, 2, lb);
			WriteSelectObject(stream, 1);	// NULL_PEN
			WriteSelectObject(stream, 2);
			m_handles = MAX(2, m_handles);

			LDraw::BBox rect(0,0,0,0);

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

			WriteDeleteObject(stream, 2);
#endif

			{
				ASSERT(0);
#if 0
				HGlobalStream stream2;
				SWF::ShapeCharacter* shape = new SWF::ShapeCharacter;
				shape->SetCharacterID(*id);

				shape->m_fillStyles.Add(new SWF::FillStyle(SWF::RGBAColor(color.GetR(), color.GetG(), color.GetB(), color.GetA())));

				int startx = p->m_points[0].X*20;
				int starty = p->m_points[0].Y*20;
				shape->MoveTo(startx, starty);
				int minx = startx;
				int miny = starty;
				int maxx = startx;
				int maxy = starty;

				int x;
				int y;
				for (int i = 1; i < p->m_points.GetSize(); i++)
				{
					x = p->m_points[i].X*20;
					y = p->m_points[i].Y*20;
					minx = MIN(minx, x);
					miny = MIN(miny, y);
					maxx = MAX(maxx, x);
					maxy = MAX(maxy, y);

					shape->LineTo(x, y);
				}
				if (x != startx || y != starty)
				{
					shape->LineTo(startx, starty);
				}
				/*
				shape.MoveTo(0, 0);
				shape.LineTo(100*20, 50*20);
				shape.LineTo(50*20, 100*20);
				shape.LineTo(0, 0);
				*/
				shape->SetBounds(SWF::Rect(minx, maxx, miny, maxy));

				SWF::WriteDefineShape(&stream2, 3, shape);

				SWF::Tag tag;
				tag.Code = SWF::Tag::DefineShape3;
				tag.Length = stream2.GetSize();

				SWF::WriteTagHeader(stream, tag);
				stream->Write(stream2.GetData(), tag.Length);
#endif
			}

			{
				HGlobalStream* stream2 = new HGlobalStream;
				SWF::BitStreamO bitstream(stream2);

				enum PlaceFlags
				{
					PlaceFlagHasClipActions = 1<<7,
					PlaceFlagHasClipDepth = 1<<6,
					PlaceFlagHasName = 1<<5,
					PlaceFlagHasRatio = 1<<4,
					PlaceFlagHasColorTransform = 1<<3,
					PlaceFlagHasMatrix = 1<<2,
					PlaceFlagHasCharacter = 1<<1,
					PlaceFlagMove = 1<<0,
				};

				uint8 flags = PlaceFlagHasCharacter | PlaceFlagHasMatrix;

				bitstream.putbyte(flags);

				bitstream.putshort(*id);	// Depth
				if (PlaceFlagHasCharacter)
				{
					bitstream.putshort(*id);	// Character
				}

			//	double m[2][3];
			//	transform.Get(m);

				if (flags & PlaceFlagHasMatrix)
				{
					float m[3][2];
					transform->Get(m);
					SWF::WriteMatrix(&bitstream, 1, 0, 0, 1, m[2][0]*20, m[2][1]*20);
				}
				bitstream.byte_align();

				SWF::Tag tag;
				tag.Code = SWF::Tag::PlaceObject2;
				tag.Length = stream2->GetSize();
				SWF::WriteTagHeader(stream, tag);
				stream->Write(stream2->GetData(), tag.Length);
			}

			(*id)++;
		}

		pCommand = pCommand->m_pNext;
	}
#else
	ASSERT(0);
#endif
}

}
