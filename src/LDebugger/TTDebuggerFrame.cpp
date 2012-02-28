#include "stdafx.h"
#include "LDebugger.h"
#include "resource.h"

#ifdef AMIGA
#define new DEBUG_NEW
#endif

#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

/*
#if WIN32

#define Array var
#include <windows.h>
#include <psapi.h>
#undef Array
#endif
  */

//#include "mainfrm.h"
#include "TTDebuggerFrame.h"

namespace System
{

using namespace std;
using namespace UI;
using namespace IO;

namespace Debugger
{
void DrawYellowArrow(UI::Graphics* pGraphics, double midy);
void DrawBreakpoint(UI::Graphics* pGraphics, double midy);
}

__live_object_ptr<LType::TTFontFile> m_pFile;
__live_object_ptr<LType::TTFont> m_pTTFont;
LType::Glyph2* pGlyph2;
__live_object_ptr<LType::VM> vm;

void FontInstructions::next()
{
	uint8 instr_code = *pc;
	(this->*ttfuncs[instr_code])();
}

GlyphPreview::GlyphPreview(TTDebuggerFrame* pFrame)
{
	m_pFrame = pFrame;
}

void GlyphPreview::OnRender(UI::Graphics* pGraphics)
{
	//ASSERT(0);
#if 0
	pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color::White), 0, 0, m_computedSize.Width, m_computedSize.Height);

	/*
	{
		for (int y = -9; y < 1; y++)
		{
		//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Blue), 5*24, (14+y)*24, 10*25, (1.f/24)*24);
			dc.FillSolidRect(5*30, (14+y)*30, 10*30, (1.f/24)*30, RGB(190, 190, 255));
		}
	}

	{
		for (int x = 0; x < 10; x++)
		{
		//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Blue), (5+x)*24, (14-10)*24, (1.f/24)*24, 10*24);
			dc.FillSolidRect((5+x)*30, (14-10)*30, (1.f/24)*30, 10*30, RGB(190, 190, 255));
		}
	}
	*/

//	LDraw::DrawString(dc, "!", 1, font, LDraw::PointF(5, 14), transform);
//	LDraw::DrawString(dc, "=", 1, font, LDraw::PointF(5, 14), transform);

//	font->FindGlyph(

	//LType::Glyph* pGlyph = ::m_pTTFont->NormalizeGlyph(pGlyph2, vm->flags/*pGlyph2->data.flags*/, vm->newpoints[1], pGlyph2->data.endPtsOfContours, pGlyph2->Desc.numberOfContours);
	LType::Glyph* pGlyph = ::m_pTTFont->NormalizeGlyph(pGlyph2, vm->flags, vm->newpoints[1], vm->endPtsOfContours, vm->glyphDesc->numberOfContours);
	if (pGlyph)
	{
		LDraw::Bitmap* bitmap = new LDraw::Bitmap(ceil(14), ceil(14), LDraw::PixelFormat_t::RGBAP_32);

		{
			LDraw::GraphicsO g(bitmap);

		//	double ascent = ::m_pTTFont->GetFile()->GetCellAscent() / 2048.0;
		//	g.TranslateTransform(0, ascent);
		//	g.ScaleTransform(1.0/64.0, 1.0/64.0);

			LDraw::GraphicsPathF* pPath = pGlyph->pPath->Clone();

				pPath->Transform(LDraw::Matrix::GetScale(1, -1));
				bool bUseOutline = false;
				if (!bUseOutline)
				{
					pPath->Transform(LDraw::Matrix::GetScale(1/64.0, 1/64.0));
					double ascent = 8;//GetCellAscent();
					pPath->Transform(LDraw::Matrix::GetTranslate(0, ascent));
				}
				double mx[4];
				LDraw::CalculatePathBounds(pPath->m_p->m_types.GetData(), pPath->m_p->m_points.GetData(), pPath->m_p->m_types.GetSize(), mx);
				/*
				pGlyph->minX = mx[0];
				pGlyph->minY = mx[1];
				pGlyph->maxX = mx[2];
				pGlyph->maxY = mx[3];
				*/

		/*

		LDraw::BBox bounds;
		bounds.top = pGlyph->minY;
		bounds.bottom = pGlyph->maxY;

		int addx = 0;//m_transform[2][0];
		int addy = 0;//m_transform[2][1];

		bounds.top += addy;
		bounds.bottom += addy;
		*/

			g.FillPath(LDraw::SolidBrush(LDraw::Color::White), pPath);
		//g.FillScans2(, pGlyph->m_scanlines, bbounds, 1,
		}

		{
			LDraw::Matrix mat;
			
			mat.Scale(20, 20);
			mat.Translate(0, 14);// * mat;
			mat.Scale(1.0/64.0, 1.0/64.0);// * mat;
			mat.Scale(1, -1);// * mat;

			LDraw::Matrix oldTransform = pGraphics->GetTransform();
			pGraphics->MultiplyTransform(mat);

			pGraphics->FillPath(LDraw::SolidBrush(LDraw::Color::Black), pGlyph->pPath);

			pGraphics->SetTransform(oldTransform);
		}

		{
			LDraw::Matrix mat;
			
			mat.Scale(20, 20);
			mat.Translate(0, 6);// * mat;
			mat.Scale(1.0/64.0, 1.0/64.0);// * mat;
			//mat = gmMatrix3::scale(1, -1) * mat;

			LDraw::Matrix oldTransform = pGraphics->GetTransform();
			pGraphics->MultiplyTransform(mat);

			{
				for (int y = 0; y < bitmap->GetHeight(); y++)
				{
					for (int x = 0; x < bitmap->GetWidth(); x++)
					{
						if (bitmap->GetPixel(x, y) != 0)
						{
							pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(160, 240, 230, 0)), x*64.0, y*64.0, 64, 64);
						}
					}
				}
			}

			pGraphics->SetTransform(oldTransform);
		}

		{
			LDraw::Matrix mat;
			
			mat.Scale(20, 20);
			mat.Translate(0, 14);// * mat;
			mat.Scale(1.0/64.0, 1.0/64.0);// * mat;
			mat.Scale(1, -1);// * mat;

			LDraw::Matrix oldTransform = pGraphics->GetTransform();
			pGraphics->MultiplyTransform(mat);

			{
				for (int x = 0; x < 14; x++)
				{
					pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(255, 255, 60, 230)), x*64.0+32, 0, (1.0f*64/20), 10*20*64);
				}

				for (int y = 0; y < 14; y++)
				{
					pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(255, 255, 60, 230)), 0, y*64.0+32, 10*20*64, (1.0f*64/20));
				}
			}

			pGraphics->SetTransform(oldTransform);
		}

		{
			LDraw::gmMatrix3f mat;
	
			LDraw::SolidBrush red(LDraw::Color(200, 60, 60));
			LDraw::SolidBrush gray(LDraw::Color(140, 140, 140));

			mat = LDraw::gmMatrix3f::getIdentity();
			mat = LDraw::gmMatrix3f::getScale(20, 20) * mat;
			mat = LDraw::gmMatrix3f::getTranslate(0, 14) * mat;
			mat = LDraw::gmMatrix3f::getScale(1.0/64.0, 1.0/64.0) * mat;
			mat = LDraw::gmMatrix3f::getScale(1, -1) * mat;

			int n = 0;
			for (int c = 0; c < pGlyph2->Desc.numberOfContours; c++)
			{
				for (; n <= pGlyph2->data.endPtsOfContours[c]; n++)
				{
					//gmVector2 xpt = mat.transform(gmVector2(pGlyph2->data.points[n].X, pGlyph2->data.points[n].Y));
					LDraw::gmVector2f xpt = mat.transform(LDraw::gmVector2f(vm->newpoints[1][n].X, vm->newpoints[1][n].Y));

					if (pGlyph2->data.flags[n] & 1)	// on-curve
					{
					//	dc.SelectPen(red);
						pGraphics->FillRectangle(red, xpt[0]-2, xpt[1]-2, 5, 5);
					}
					else
					{
					//	dc.SelectPen(gray);
						pGraphics->FillEllipse(gray, xpt[0]-1, xpt[1]-1, 4, 4);
					}
				}
			}
		}

//		dc.SelectPen(hOldPen);

		delete bitmap;

		delete pGlyph;
	}

	{
		LDraw::Font font(L"Courier New", 14);
		pGraphics->DrawString("G", font, LDraw::PointF(0,0), LDraw::SolidBrush(LDraw::Color(0,0,0)));
	}
#endif
}

void GlyphPreview::OnMouseMove(UI::MouseEventArgs* args)
{
	m_pFrame->get_InfoWin()->RemoveChildren();

	LDraw::PointD point = args->GetPosition(this);//ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());
	//LDraw::PointD point(pointXY->get_X(), pointXY->get_Y());

	LDraw::matrix3f mat = LDraw::matrix3f::getIdentity();
	mat = LDraw::matrix3f::getScale(20, 20) * mat;
	mat = LDraw::matrix3f::getTranslate(0, 12) * mat;
	mat = LDraw::matrix3f::getScale(1.0/64.0, 1.0/64.0) * mat;
	mat = LDraw::matrix3f::getScale(1, -1) * mat;

	int y = 0;

	int n = 0;
	for (int c = 0; c < pGlyph2->Desc.numberOfContours; c++)
	{
		for (; n <= pGlyph2->data.endPtsOfContours[c]; n++)
		{
			LDraw::vector2f xpt = mat.transform(LDraw::vector2f(vm->newpoints[1][n].X, vm->newpoints[1][n].Y));

			if (fabs(point.X - xpt[0]) < 2 && fabs(point.Y - xpt[1]) < 2)
			{
				WCHAR str[256];
				swprintf_s(str, L"%d(%.2f,%.2f)", n, vm->newpoints[1][n].X / 64.0, vm->newpoints[1][n].Y / 64.0);
				//pGraphics->DrawText(16, 16+y, str, strlen(str));
				m_pFrame->get_InfoWin()->AddChild(new TextString(new StringW(string_copy(str))));

				if (vm->orgpoints[1][n].X != vm->orgpoints[1][n].X ||
					vm->orgpoints[1][n].Y != vm->orgpoints[1][n].Y)
				{
					WCHAR str[256];
					swprintf_s(str, L"%d(%.2f,%.2f)", n, vm->orgpoints[1][n].X / 64.0, vm->orgpoints[1][n].Y / 64.0);
					//dc.TextOut(80, 16+y, str, strlen(str));
					m_pFrame->get_InfoWin()->get_Children()->Add(new TextString(new StringW(string_copy(str))));
				}

				m_pFrame->get_InfoWin()->InvalidateMeasure();
			//	y += 14;
			}
			/*
			if (pGlyph2->data.flags[n] & 1)	// on-curve
			{
				dc.SelectPen(red);
				dc.Rectangle(xpt[0]-2, xpt[1]-2, xpt[0]+3, xpt[1]+3);
			}
			else
			{
				dc.SelectPen(gray);
				dc.Ellipse(xpt[0]-1, xpt[1]-1, xpt[0]+3, xpt[1]+3);
			}
			*/
		}
	}
}

#if 0
void GlyphPreview::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousemove)
		{
			OnMouseMove(dynamic_cast<MouseEvent*>(evt));
		}
	}
}
#endif

TTInstructionsControl::TTInstructionsControl()
{
	m_frame = NULL;
	m_instructions = NULL;
	m_pScroller = NULL;
}

void TTInstructionsControl::Update()
{
	if (vm->pc >= m_instructions->m_start && vm->pc < m_instructions->m_start + m_instructions->m_length)
	{
		int offset = vm->pc - m_instructions->m_start;

		int i;
		for (i = 0; i < m_instructions->m_instructions.size(); i++)
		{
			if (offset <= m_instructions->m_instructions[i]->m_offset)
				break;
		}

		double y = i * get_FontSize();
		m_pScroller->MakeVisible(LDraw::RectD(0, y, 0/*m_computedSize.Width*/, get_FontSize()));

		Invalidate();
	}
}

#if 0
void TTInstructionsControl::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			int line = point.Y / get_FontSize();

			TTInstruction* tti = m_instructions->m_instructions[line];

			uint8* addr = m_instructions->m_start + tti->m_offset;

			ttbreakpointmap_t::iterator ttbi = m_instructions->m_breakpoints.find(tti->m_offset);
			ttbreakpointaddrmap_t::iterator ttbaddri = m_frame->m_breakpoints.find(addr);
			if (ttbi == m_instructions->m_breakpoints.end())
			{
				uint8 oldbyte = *addr;
				m_instructions->m_breakpoints.insert(ttbreakpointmap_t::value_type(tti->m_offset, true));
				
				m_frame->m_breakpoints.insert(ttbreakpointaddrmap_t::value_type(addr, oldbyte));

				*addr = 0x4f;	// DEBUG instruction
			}
			else
			{
				*addr = (*ttbi).second;	// Restore old instruction
				VERIFY(0);
#if 0	// TODO, have this
				m_instructions->m_breakpoints.erase(ttbi);
				m_frame->m_breakpoints.erase(ttbaddri);
#endif
			}

			Invalidate();
		}
	}
}
#endif

LDraw::SizeD TTInstructionsControl::MeasureOverride(LDraw::SizeD availSize)
{
	return LDraw::SizeD(640/*TODO*/, m_instructions->m_instructions.size() * get_FontSize());
}

void TTInstructionsControl::OnRender(UI::Graphics* pGraphics)
{
	pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255,255,255)), 0, 0, m_computedSize.Width, m_computedSize.Height);

	double lineHeight = get_FontSize();
	double spaceWidth = pGraphics->MeasureString(" ", 1, GetFont());

//	uint8* programStart;

	/*
	// TODO prepProgram
	if (vm->pc >= pGlyph2->instructionsData && vm->pc <= pGlyph2->instructionsData+pGlyph2->instructionsLength)
		programStart = pGlyph2->instructionsData;
	else
		programStart = ::m_pTTFont->GetFamily()->m_fontPrgData;
		*/

	if (true)
	{
		StringA** strs = (StringA**)alloca(sizeof(StringA*)*m_instructions->m_instructions.size()*2);
	//	unsigned int lens = (unsigned int*)alloca(m_instructions->m_instructions.size()*2);
		LDraw::PointF* points = (LDraw::PointF*)alloca(sizeof(LDraw::PointF)*m_instructions->m_instructions.size()*2);

		LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(0,0,0));

		double y = 0;
		for (int i = 0; i < m_instructions->m_instructions.size(); i++)
		{
			TTInstruction* tti = m_instructions->m_instructions[i];

			/*
			WCHAR buf[16];
			swprintf_s(buf, L"%d", tti->m_offset);
			pGraphics->DrawString(buf, strlen(buf), GetFont(), LDraw::PointF(12, y), new LDraw::SolidBrush(LDraw::Color(0,0,0)));
			*/

			strs[i] = tti->m_name;
			points[i] = LDraw::PointF(12 + spaceWidth*7 + tti->m_level*spaceWidth*2, y);
		//	pGraphics->DrawString(tti->m_name, GetFont(), LDraw::PointF(12 + spaceWidth*7 + tti->m_level*spaceWidth*2, y), new LDraw::SolidBrush(LDraw::Color(0,0,0)));

			uint8* addr = m_instructions->m_start + tti->m_offset;

			if (*addr == 0x4f)
			{
				Debugger::DrawBreakpoint(pGraphics, y+lineHeight/2);
			}

			if ((vm->pc - m_instructions->m_start) == tti->m_offset)
			{
				Debugger::DrawYellowArrow(pGraphics, y+lineHeight/2);
			}

			y += lineHeight;
		}

		pGraphics->DrawStrings(strs, GetFont(), points, brush, m_instructions->m_instructions.size());
	}
	else
	{
		double y = 0;
		for (int i = 0; i < m_instructions->m_instructions.size(); i++)
		{
			TTInstruction* tti = m_instructions->m_instructions[i];

			/*
			char buf[16];
			sprintf_s(buf, "%d", tti->m_offset);
			pGraphics->DrawString(buf, strlen(buf), GetFont(), LDraw::PointF(12, y), new LDraw::SolidBrush(LDraw::Color(0,0,0)));
*/

			pGraphics->DrawString(tti->m_name, GetFont(), LDraw::PointF(12 + spaceWidth*7 + tti->m_level*spaceWidth*2, y), new LDraw::SolidBrush(LDraw::Color(0,0,0)));

			uint8* addr = m_instructions->m_start + tti->m_offset;

			if (*addr == 0x4f)
			{
				Debugger::DrawBreakpoint(pGraphics, y+lineHeight/2);
			}

			if ((vm->pc - m_instructions->m_start) == tti->m_offset)
			{
				Debugger::DrawYellowArrow(pGraphics, y+lineHeight/2);
			}

			y += lineHeight;
		}
	}
}

// GPV[] Get Projection Vector
void FontInstructions::tt_gpv()
{
	TTInstr(ASTR("Get Projection Vector"));
	pc++;
}

// SFVTPV[] Set Freedom Vector To Projection Vector
void FontInstructions::tt_sfvtpv()
{
	TTInstr(ASTR("Set Freedom Vector To Projection Vector"));
	pc++;
}

// SDPVTL[a] Set Dual Projection Vector To Line
void FontInstructions::tt_sdpvtl()
{
	int a = *pc - 0x86;
	TTInstr(ASTR("Set Dual Projection Vector To Line"));
	pc++;
}

// ALIGNRP[] ALIGN to Reference Point
void FontInstructions::tt_alignrp()
{
	TTInstr(ASTR("Align to Reference Point"));
	pc++;
}

// JMPR[] JuMP Relative
void FontInstructions::tt_jmpr()
{
	TTInstr(ASTR("Jump relative"));
	pc++;
}

// JROF[] Jump Relative On False
void FontInstructions::tt_jrof()
{
	TTInstr(ASTR("Jump relative on False"));
	pc++;
}

// SDB[] Set Delta Base in the graphics state
void FontInstructions::tt_sdb()
{
	TTInstr(ASTR("Set Delta Base in the graphics state"));
	pc++;
}

// WCVTP[] Write Control Value Table in Pixel units
void FontInstructions::tt_wcvtp()
{
	TTInstr(ASTR("Write Control Value Table in Pixel units"));
	pc++;
}

//MPPEM[] Measure Pixels Per EM
void FontInstructions::tt_mppem()
{
	TTInstr(ASTR("Measure Pixels Per EM"));
	pc++;
}

void FontInstructions::tt_npushb()
{
	TTInstr(ASTR("Push"));
	pc++;

	uint8 n = *pc++;
	while (n > 0)
	{
		uint8 value = *pc++;

	//	LOG(" %d", value);
		n--;
	}
}

void FontInstructions::tt_npushw()
{
	TTInstr(ASTR("Push"));
	pc++;

	uint8 n = *pc++;
	while (n > 0)
	{
		int16 value = (int)pc[0]<<8 | pc[1];

	//	LOG(" %d", value);

		pc += 2;
	//	vm->push(value);
		n--;
	}
}

void FontInstructions::tt_pushb()
{
	TTInstr(ASTR("Push"));
	uint8 n = *pc - 0xB0;
	pc++;
	n += 1;
	while (n > 0)
	{
		//LOG(" %d", *vm->pc);

		(uint8)*pc++;
		//vm->push();
		n--;
	}
}

void FontInstructions::tt_pushw()
{
	TTInstr(ASTR("Push"));
	uint8 n = *pc - 0xB8;
	pc++;
	n += 1;
	while (n > 0)
	{
		int16 value = (int)pc[0]<<8 | pc[1];

		pc += 2;
		n--;
	}
}

// POP[] POP top stack element
void FontInstructions::tt_pop()
{
	TTInstr(ASTR("Pop"));
	pc++;
}

// SPVTL[a] Set Projection Vector To Line
void FontInstructions::tt_spvtl()
{
	uint a = *pc - 0x6;
	TTInstr(ASTR("Set Projection Vector To Line"));
	pc++;
}

// SFVTL[a] Set Freedom Vector To Line
void FontInstructions::tt_sfvtl()
{
	uint a = *pc - 0x8;
	TTInstr(ASTR("Set Freedom Vector To Line"));
	pc++;
}

// SFVTCA[a] Set Freedom Vector to Coordinate Axis
void FontInstructions::tt_sfvtca()
{
	uint8 a = *pc - 0x4;
	TTInstr(ASTR("Set Freedom Vector to Coordinate Axis "));
	pc++;
}

// SVTCA[a] Set freedom and projection Vectors To Coordinate Axis
void FontInstructions::tt_svtca()
{
	uint8 a = *pc - 0x0;
	TTInstr(ASTR("Set freedom and projection Vectors To Coordinate Axis"));
	pc++;
}

// SPVFS[] Set Projection Vector From Stack
void FontInstructions::tt_spvfs()
{
	TTInstr(ASTR("Set Projection Vector From Stack"));
	pc++;
}

// Set Projection Vector To Coordinate Axis
void FontInstructions::tt_spvtca()
{
	uint8 a = *pc - 0x02;
	TTInstr(ASTR("Set Projection Vector To Coordinate Axis"));
	pc++;
}

// SCANCTRL[] SCAN conversion ConTRoL
void FontInstructions::tt_scanctrl()
{
	TTInstr(ASTR("Scan conversion control"));
	pc++;
}

void FontInstructions::tt_call()
{
	TTInstr(ASTR("Call"));
	pc++;
}

// LOOPCALL[] LOOP and CALL function
void FontInstructions::tt_loopcall()
{
	TTInstr(ASTR("Loop call"));
	pc++;
}

void FontInstructions::tt_fdef()
{
	TTInstr(ASTR("Function Definition"));
	pc++;
	m_iflevel++;
	/*
	if (vm->m_pFamily->m_functions.size() >= vm->m_pFamily->m_maxp.maxFunctionDefs)
	{
		LOG("number of fdefs exceed number specified in maxp table");
		throw -1;
	}

	uint32 f = vm->pop();

	LOG("fdef %d", f);

	TTFun* pFun = new TTFun;
	pFun->m_data = vm->pc;

	vm->m_pFamily->m_functions.insert(tyfunmap::value_type(f, pFun));

	while (1)
	{
		uint8 instr_code = *vm->pc;
		if (instr_code == 0x2D)	// endf
			break;
		
		skip_next(vm);
	}
	pFun->m_size = vm->pc - pFun->m_data;

	ASSERT(*vm->pc == 0x2D);
	*/
}

void FontInstructions::tt_endf()
{
	m_iflevel--;
	TTInstr(ASTR("End Function"));
	pc++;
}

// GTEQ[] Greater Than or EQual
void FontInstructions::tt_gteq()
{
	TTInstr(ASTR("Greater Than or Equal"));
	pc++;
}

// LTEQ[] Less Than or EQual
void FontInstructions::tt_lteq()
{
	TTInstr(ASTR("Less Than or Equal"));
	pc++;
}

StringA tt_eq_str(true, "Equal");
StringA tt_lt_str(true, "Less Than");

// EQ[] EQual
void FontInstructions::tt_eq()
{
	TTInstr(&tt_eq_str);
	pc++;
}

// LT[] Less Than
void FontInstructions::tt_lt()
{
	TTInstr(&tt_lt_str);
	pc++;
}

StringA tt_gt_str(true, "Greater Than");

// GT[] Greater Than
void FontInstructions::tt_gt()
{
	TTInstr(&tt_gt_str);
	pc++;
}

StringA tt_and_str(true, "Logical And");

// AND[] logical AND
void FontInstructions::tt_and()
{
	TTInstr(&tt_and_str);
	pc++;
}

// OR[] logical OR
void FontInstructions::tt_or()
{
	TTInstr(ASTR("Logical Or"));
	pc++;
}

// DIV[] DIVide
void FontInstructions::tt_div()
{
	TTInstr(ASTR("Divide"));
	pc++;
}

// MUL[] MULtiply
void FontInstructions::tt_mul()
{
	TTInstr(ASTR("Multiply"));
	pc++;
}

// ADD[] ADD
void FontInstructions::tt_add()
{
	TTInstr(ASTR("Add"));
	pc++;
}

// SUB[] SUBtract
void FontInstructions::tt_sub()
{
	TTInstr(ASTR("Subtract"));
	pc++;
}

// MAX[] MAXimum of top two stack elements
void FontInstructions::tt_max()
{
	TTInstr(ASTR("Maximum"));
	pc++;
}

// MIN[] MINimum of top two stack elements
void FontInstructions::tt_min()
{
	TTInstr(ASTR("Minimum"));
	pc++;
}

// SWAP[] SWAP the top two elements on the stack
void FontInstructions::tt_swap()
{
	TTInstr(ASTR("Swap"));
	pc++;
}

// WS[] Write Store
void FontInstructions::tt_ws()
{
	TTInstr(ASTR("Write Store"));
	pc++;
}

// RS[] Read Store
void FontInstructions::tt_rs()
{
	TTInstr(ASTR("Read Store"));
	pc++;
}

// ABS[] ABSolute value
void FontInstructions::tt_abs()
{
	TTInstr(ASTR("Absolute value"));
	pc++;
}

// FLIPRGON[] FLIP RanGe ON
void FontInstructions::tt_fliprgon()
{
	TTInstr(ASTR("Flip Range On"));
	pc++;
}

// RTG[] Round To Grid
void FontInstructions::tt_rtg()
{
	TTInstr(ASTR("Round To Grid"));
	pc++;
}

// RTHG[] Round To Half Grid
void FontInstructions::tt_rthg()
{
	TTInstr(ASTR("Round To Half Grid"));
	pc++;
}

// RDTG[] Round Down To Grid
void FontInstructions::tt_rdtg()
{
	TTInstr(ASTR("Round Down To Grid"));
	pc++;
}

// RTDG[] Round To Double Grid
void FontInstructions::tt_rtdg()
{
	TTInstr(ASTR("Round To Double Grid"));
	pc++;
}

// MDRP[abcde] Move Direct Relative Point
void FontInstructions::tt_mdrp()
{
	int a = (*pc) & 16;
	int b = ((*pc)>>3) & 1;
	int c = ((*pc)>>2) & 1;
	int de = (*pc) & 3;

	TTInstr(ASTR("Move Direct Relative Point"));
	pc++;
}

// MSIRP[a] Move Stack Indirect Relative Point
void FontInstructions::tt_msirp()
{
	uint8 a = *pc - 0x3A;
	TTInstr(ASTR("Move Stack Indirect Relative Point"));
	pc++;
}

// MIRP[abcde] Move Indirect Relative Point
void FontInstructions::tt_mirp()
{
	int a = (*pc) & 16;
	int b = ((*pc)>>3) & 1;
	int c = ((*pc)>>2) & 1;
	int de = (*pc) & 3;
	TTInstr(ASTR("Move Indirect Relative Point"));
	pc++;
}

// IF[] IF test
void FontInstructions::tt_if()
{
	TTInstr(ASTR("If"));
	pc++;
	m_iflevel++;
}

// RCVT[] Read Control Value Table entry
void FontInstructions::tt_rcvt()
{
	TTInstr(ASTR("Read Control Value Table Entry"));
	pc++;
}

// MD[a] Measure Distance
void FontInstructions::tt_md()
{
	uint8 a = *pc - 0x49;
	TTInstr(ASTR("Measure Distance"));
	pc++;
}

// GC[a] Get Coordinate projected onto the projection vector
void FontInstructions::tt_gc()
{
	uint8 a = *pc - 0x46;
	TTInstr(ASTR("Get Coordinate projected onto the projection vector"));
	pc++;
}

// DUP[] DUPlicate top stack element
void FontInstructions::tt_dup()
{
	TTInstr(ASTR("Duplicate top stack element"));
	pc++;
}

// CINDEX[] Copy the INDEXed element to the top of the stack
void FontInstructions::tt_cindex()
{
	TTInstr(ASTR("Copy the indexed element to the top of the stack"));
	pc++;
}

// MINDEX[] Move the INDEXed element to the top of the stack
void FontInstructions::tt_mindex()
{
	TTInstr(ASTR("Move the indexed element to the top of the stack"));
	pc++;
}

// ROLL[] ROLL the top three stack elements
void FontInstructions::tt_roll()
{
	TTInstr(ASTR("Roll the top three stack elements"));
	pc++;
}

// SMD[] Set Minimum Distance
void FontInstructions::tt_smd()
{
	TTInstr(ASTR("Set Minimum Distance"));
	pc++;
}

// SCFS[] Sets Coordinate From the Stack using projection vector and freedom vector
void FontInstructions::tt_scfs()
{
	TTInstr(ASTR("Set Coordinate From the Stack"));
	pc++;
}

// ISECT[] moves point p to the InterSECTion of two lines
void FontInstructions::tt_isect()
{
	TTInstr(ASTR("Move point to intersection of two lines"));
	pc++;
}

// WCVTF[] Write Control Value Table in Funits
void FontInstructions::tt_wcvtf()
{
	TTInstr(ASTR("Write Control Value Table in Funits"));
	pc++;
}

// SRP0[] Set Reference Point 0
void FontInstructions::tt_srp0()
{
	TTInstr(ASTR("Set Reference Point 0"));
	pc++;
}

// SRP1[] Set Reference Point 1
void FontInstructions::tt_srp1()
{
	TTInstr(ASTR("Set Reference Point 1"));
	pc++;
}

// SRP2[] Set Reference Point 2
void FontInstructions::tt_srp2()
{
	TTInstr(ASTR("Set Reference Point 2"));
	pc++;
}

// SZP0[] Set Zone Pointer 0
void FontInstructions::tt_szp0()
{
	TTInstr(ASTR("Set Zone Pointer 0"));
	pc++;
}

// SZP1[] Set Zone Pointer 1
void FontInstructions::tt_szp1()
{
	TTInstr(ASTR("Set Zone Pointer 1"));
	pc++;
}

// SZP2[] Set Zone Pointer 2
void FontInstructions::tt_szp2()
{
	TTInstr(ASTR("Set Zone Pointer 2"));
	pc++;
}

// SZPS[] Set Zone PointerS
void FontInstructions::tt_szps()
{
	TTInstr(ASTR("Set Zone Pointers"));
	pc++;
}

void FontInstructions::tt_else()
{
	TTInstr(ASTR("Else"));
	pc++;
	if (m_iflevel == 0)
	{
	//	LOG("else without matching if");
		ASSERT(0);
		throw -1;
	}
}

void FontInstructions::tt_eif()
{
	if (m_iflevel > 0)
	{
		m_iflevel--;
	}
	else
	{
	//	LOG("eif without matching if");
		ASSERT(0);
		throw -1;
	}
	TTInstr(ASTR("End If"));
	pc++;
}

// SFVFS[] Set Freedom Vector From Stack
void FontInstructions::tt_sfvfs()
{
	TTInstr(ASTR("Set Freedom Vector From Stack"));
	pc++;
}

// NEG[] NEGate
void FontInstructions::tt_neg()
{
	TTInstr(ASTR("Negate"));
	pc++;
}

// NOT[] logical NOT
void FontInstructions::tt_not()
{
	TTInstr(ASTR("Logical Not"));
	pc++;
}

// SCANTYPE[] SCANTYPE
void FontInstructions::tt_scantype()
{
	TTInstr(ASTR("Scantype"));
	pc++;
}

// MIAP[a] Move Indirect Absolute Point
void FontInstructions::tt_miap()
{
	int a = *pc - 0x3E;
	TTInstr(ASTR("Move Indirect Absolute Point"));
	pc++;
}

//MDAP[a] Move Direct Absolute Point
void FontInstructions::tt_mdap()
{
	int a = *pc - 0x2E;
	TTInstr(ASTR("Move Direct Absolute Point"));
	pc++;
}

// IP[] Interpolate Point
void FontInstructions::tt_ip()
{
	TTInstr(ASTR("Interpolate Point"));
	pc++;
}

// IUP[a] Interpolate Untouched Points through the outline
void FontInstructions::tt_iup()
{
	TTInstr(ASTR("Interpolate Untouched Points"));
	pc++;
}

// SCVTCI[] Set Control Value Table Cut-In
void FontInstructions::tt_scvtci()
{
	TTInstr(ASTR("Set Control Value Table Cut-In"));
	pc++;
}

// GETINFO[] GET INFOrmation
void FontInstructions::tt_getinfo()
{
	TTInstr(ASTR("Get Information"));
	pc++;
}

// ROFF[] Round OFF
void FontInstructions::tt_roff()
{
	TTInstr(ASTR("Round Off"));
	pc++;
}

// SROUND[] Super ROUND
void FontInstructions::tt_sround()
{
	TTInstr(ASTR("Super Round"));
	pc++;
}

// ROUND[ab] ROUND value
void FontInstructions::tt_round()
{
	TTInstr(ASTR("Round"));
	pc++;
}

// INSTCTRL[ ] INSTRuction execution ConTRoL
void FontInstructions::tt_instctrl()
{
	TTInstr(ASTR("Instruction exection control"));
	pc++;
}

// SLOOP[] Set LOOP variable
void FontInstructions::tt_sloop()
{
	TTInstr(ASTR("Set Loop"));
	pc++;
}

// FLIPOFF[] set the auto FLIP Boolean to OFF
void FontInstructions::tt_flipoff()
{
	TTInstr(ASTR("Set Auto flip off"));
	pc++;
}

// FLIPON[] set the auto FLIP Boolean to ON
void FontInstructions::tt_flipon()
{
	TTInstr(ASTR("Set Auto flip on"));
	pc++;
}

// DELTAP1[] DELTA exception P1
void FontInstructions::tt_deltap1()
{
	TTInstr(ASTR("Delta exception P1"));
	pc++;
}

// DELTAP2[] DELTA exception P2
void FontInstructions::tt_deltap2()
{
	TTInstr(ASTR("Delta exception P2"));
	pc++;
}

// DELTAP3[] DELTA exception P3
void FontInstructions::tt_deltap3()
{
	TTInstr(ASTR("Delta exception P3"));
	pc++;
}

// DELTAC1[] DELTA exception C1
void FontInstructions::tt_deltac1()
{
	TTInstr(ASTR("Delta exception C1"));
	pc++;
}

// DELTAC2[] DELTA exception C2
void FontInstructions::tt_deltac2()
{
	TTInstr(ASTR("Delta exception C2"));
	pc++;
}

// DELTAC3[] DELTA exception C3
void FontInstructions::tt_deltac3()
{
	TTInstr(ASTR("Delta exception C3"));
	pc++;
}

// SHP[a] SHift Point using reference point
void FontInstructions::tt_shp()
{
	TTInstr(ASTR("Shift Point using reference point"));
	pc++;
}

// SHC[a] SHift Contour using reference point
void FontInstructions::tt_shc()
{
	TTInstr(ASTR("Shift Contour using reference point"));
	pc++;
}

// SHPIX[] SHift point by a PIXel amount
void FontInstructions::tt_shpix()
{
	TTInstr(ASTR("Shift point by pixel amount"));
	pc++;
}

// SHPIX[] SHift point by a PIXel amount
void FontInstructions::tt_notimpl()
{
	TTInstr(ASTR("Unknown instruction"));
	pc++;
}

tyttfunc FontInstructions::ttfuncs[256] =
{
	&FontInstructions::tt_svtca,	// SVTCA[a] Set freedom and projection Vectors To Coordinate Axis
	&FontInstructions::tt_svtca,
	&FontInstructions::tt_spvtca,	// SPVTCA[a] Set Projection Vector To Coordinate Axis
	&FontInstructions::tt_spvtca,
	&FontInstructions::tt_sfvtca,	// SFVTCA[a] Set Freedom Vector to Coordinate Axis
	&FontInstructions::tt_sfvtca,
	&FontInstructions::tt_spvtl,	// SPVTL[a] Set Projection Vector To Line
	&FontInstructions::tt_spvtl,
	&FontInstructions::tt_sfvtl,	// SFVTL[a] Set Freedom Vector To Line
	&FontInstructions::tt_sfvtl,
	&FontInstructions::tt_spvfs,	// SPVFS[] Set Projection Vector From Stack
	&FontInstructions::tt_sfvfs,	// SFVFS[] Set Freedom Vector From Stack
	&FontInstructions::tt_gpv,	// GPV[] Get Projection Vector
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_sfvtpv,	// SFVTPV[] Set Freedom Vector To Projection Vector
	&FontInstructions::tt_isect,	// ISECT[] moves point p to the InterSECTion of two lines
	&FontInstructions::tt_srp0,	// SRP0[] Set Reference Point 0
	&FontInstructions::tt_srp1,	// SRP1[] Set Reference Point 1
	&FontInstructions::tt_srp2,	// SRP2[] Set Reference Point 2
	&FontInstructions::tt_szp0,	// SZP0[] Set Zone Pointer 0
	&FontInstructions::tt_szp1, // 20 // SZP1[] Set Zone Pointer 1
	&FontInstructions::tt_szp2,	// SZP2[] Set Zone Pointer 2
	&FontInstructions::tt_szps,	// SZPS[] Set Zone PointerS
	&FontInstructions::tt_sloop,	// SLOOP[] Set LOOP variable
	&FontInstructions::tt_rtg,	// RTG[] Round To Grid
	&FontInstructions::tt_rthg,	// RTHG[] Round To Half Grid
	&FontInstructions::tt_smd,	// SMD[] Set Minimum Distance
	&FontInstructions::tt_else,
	&FontInstructions::tt_jmpr,	// JMPR[] JuMP Relative
	&FontInstructions::tt_scvtci,	// SCVTCI[] Set Control Value Table Cut-In
	&FontInstructions::tt_notimpl, // 30
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_dup,	// DUP[] DUPlicate top stack element
	&FontInstructions::tt_pop,	// POP[] POP top stack element
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_swap,	// SWAP[] SWAP the top two elements on the stack
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_cindex,	// CINDEX[] Copy the INDEXed element to the top of the stack
	&FontInstructions::tt_mindex,		// MINDEX[] Move the INDEXed element to the top of the stack
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl, // 40
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_loopcall,	// LOOPCALL[] LOOP and CALL function
	&FontInstructions::tt_call,
	&FontInstructions::tt_fdef,
	&FontInstructions::tt_endf,
	&FontInstructions::tt_mdap,		// MDAP[a] Move Direct Absolute Point
	&FontInstructions::tt_mdap,		// MDAP[a] Move Direct Absolute Point
	&FontInstructions::tt_iup,		// IUP[a] Interpolate Untouched Points through the outline
	&FontInstructions::tt_iup,
	&FontInstructions::tt_shp,		// SHP[a] SHift Point using reference point
	&FontInstructions::tt_shp,
	&FontInstructions::tt_shc,		// SHC[a] SHift Contour using reference point
	&FontInstructions::tt_shc,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_shpix,	// SHPIX[] SHift point by a PIXel amount
	&FontInstructions::tt_ip,		// IP[] Interpolate Point
	&FontInstructions::tt_msirp,	// MSIRP[a] Move Stack Indirect Relative Point
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_alignrp, // 60	// ALIGNRP[] ALIGN to Reference Point
	&FontInstructions::tt_rtdg,		// RTDG[] Round To Double Grid
	&FontInstructions::tt_miap,		// MIAP[a] Move Indirect Absolute Point
	&FontInstructions::tt_miap,		// MIAP[a] Move Indirect Absolute Point
	&FontInstructions::tt_npushb,	// 64
	&FontInstructions::tt_npushw,
	&FontInstructions::tt_ws,		// WS[] Write Store
	&FontInstructions::tt_rs,		// RS[] Read Store
	&FontInstructions::tt_wcvtp,	// // WCVTP[] Write Control Value Table in Pixel units
	&FontInstructions::tt_rcvt,		// RCVT[] Read Control Value Table entry
	&FontInstructions::tt_gc,		// 70 // GC[a] Get Coordinate projected onto the projection vector
	&FontInstructions::tt_gc,
	&FontInstructions::tt_scfs,	// SCFS[] Sets Coordinate From the Stack using projection vector and freedom vector
	&FontInstructions::tt_md,	// MD[a] Measure Distance
	&FontInstructions::tt_md,
	&FontInstructions::tt_mppem,	// MPPEM[] Measure Pixels Per EM
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_flipon,	// FLIPON[] set the auto FLIP Boolean to ON
	&FontInstructions::tt_flipoff,	// FLIPOFF[] set the auto FLIP Boolean to OFF
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_lt,	// LT[] Less Than
	&FontInstructions::tt_lteq,	// LTEQ[] Less Than or EQual
	&FontInstructions::tt_gt,	// GT[] Greater Than
	&FontInstructions::tt_gteq, // GTEQ[] Greater Than or EQual
	&FontInstructions::tt_eq,	// EQ[] EQual
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_if,	// IF[] IF test
	&FontInstructions::tt_eif,
	&FontInstructions::tt_and,	// AND[] logical AND
	&FontInstructions::tt_or,	// OR[] logical OR
	&FontInstructions::tt_not,	// // NOT[] logical NOT
	&FontInstructions::tt_deltap1,	// DELTAP1[] DELTA exception P1
	&FontInstructions::tt_sdb,	// // SDB[] Set Delta Base in the graphics state
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_add,	// ADD[] ADD
	&FontInstructions::tt_sub,	// SUB[] SUBtract
	&FontInstructions::tt_div,	// DIV[] DIVide
	&FontInstructions::tt_mul,	// MUL[] MULtiply
	&FontInstructions::tt_abs, // 100 ABS[] ABSolute value
	&FontInstructions::tt_neg,	// NEG[] NEGate
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_round,	// ROUND[ab] ROUND value
	&FontInstructions::tt_round,
	&FontInstructions::tt_round,
	&FontInstructions::tt_round,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl, // 110
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_wcvtf,	// WCVTF[] Write Control Value Table in Funits
	&FontInstructions::tt_deltap2,	// DELTAP2[] DELTA exception P2
	&FontInstructions::tt_deltap3,	// DELTAP3[] DELTA exception P3
	&FontInstructions::tt_deltac1,	// DELTAC1[] DELTA exception C1
	&FontInstructions::tt_deltac2,	// DELTAC2[] DELTA exception C2
	&FontInstructions::tt_deltac3,	// DELTAC3[] DELTA exception C3
	&FontInstructions::tt_sround,	// SROUND[] Super ROUND
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl, // 120
	&FontInstructions::tt_jrof,	// JROF[] Jump Relative On False
	&FontInstructions::tt_roff,	// ROFF[] Round OFF
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_rdtg,	// RDTG[] Round Down To Grid
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_fliprgon,	// FLIPRGON[] FLIP RanGe ON
	&FontInstructions::tt_notimpl, // 130
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_scanctrl,
	&FontInstructions::tt_sdpvtl,	// SDPVTL[a] Set Dual Projection Vector To Line
	&FontInstructions::tt_sdpvtl,
	&FontInstructions::tt_getinfo,	// GETINFO[] GET INFOrmation	
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_roll,	// ROLL[] ROLL the top three stack elements
	&FontInstructions::tt_max,	// MAX[] MAXimum of top two stack elements
	&FontInstructions::tt_min, // MIN[] MINimum of top two stack elements
	&FontInstructions::tt_scantype,	// SCANTYPE[] SCANTYPE
	&FontInstructions::tt_instctrl,	// INSTCTRL[ ] INSTRuction execution ConTRoL
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl, // 150
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl, // 160
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl, // 170
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_notimpl,
	&FontInstructions::tt_pushb,
	&FontInstructions::tt_pushb,
	&FontInstructions::tt_pushb,
	&FontInstructions::tt_pushb,
	&FontInstructions::tt_pushb, // 180
	&FontInstructions::tt_pushb,
	&FontInstructions::tt_pushb,
	&FontInstructions::tt_pushb,
	&FontInstructions::tt_pushw, // 184
	&FontInstructions::tt_pushw,
	&FontInstructions::tt_pushw,
	&FontInstructions::tt_pushw,
	&FontInstructions::tt_pushw,
	&FontInstructions::tt_pushw,
	&FontInstructions::tt_pushw,	// 190
	&FontInstructions::tt_pushw,
	&FontInstructions::tt_mdrp,	// MDRP[abcde] Move Direct Relative Point
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,	// 200
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,	// 210
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,	// 220
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mdrp,
	&FontInstructions::tt_mirp,	// MIRP[abcde] Move Indirect Relative Point
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,	// 230
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,	// 240
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
	&FontInstructions::tt_mirp,
};

TTDebuggerFrame::TTDebuggerFrame()
{

	m_breakpoints = new TTBreakpoints;

	/*
			if (false)	// Arial
			{
				// TODO remove
				m_pStorage[2] = 1;

			//	ASSERT(m_cvt[92] == -64);
				m_cvt[4] = 576;
				m_cvt[92] = -64;
			}
			else	// Courier
			{
			}

			//
			LOG("Glyph Instructions:\n");
			bGlyphProgram = true;

			VM* vm = SetupGlyphVM(pGlyph2);

			while (vm->next())
				;

			ASSERT(vm->m_stack.size() == 0);

			ATLTRACE("%d(%.2f %.2f)\n", 14, vm->newpoints[1][14].X / 64.0, vm->newpoints[1][14].Y / 64.0);
			ATLTRACE("%d(%.2f %.2f)\n", 27, vm->newpoints[1][27].X / 64.0, vm->newpoints[1][27].Y / 64.0);

			delete vm;

			Glyph* pGlyph = NormalizeGlyph(pGlyph2);
			if (pGlyph)
			{
				m_glyphshapes.insert(tyglyphshapemap::value_type(glyphIndex, pGlyph));
				return pGlyph;
			}
		*/

	set_Width(1000.0);
	set_Height(800.0);

#if 1
	DockPanel* p = new DockPanel;
	{

		{
#if 0
			CUIDockBar* pDockbar = new CUIDockBar;
			{
				pDockbar->set_Background(new SolidColorBrush(new Color(236, 233, 216)));
				{
					//Gripper* pGripper = new Gripper;
				//	pGripper->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(255, 0, 0)));
					{
						ToolBarPanel* pToolbar = new ToolBarPanel;
					//	pToolbar->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(0, 255, 0)));

						ASSERT(0);
#if 0
						{

							Menu* pMenu = new Menu(new TextString(WSTR("File")));
							{
								pMenu->AddItem(new TextString(WSTR("Open")), ID_FILE_OPEN);
								pMenu->AddItem(new TextString(WSTR("Save")));
								pMenu->AddItem(new TextString(WSTR("Open Program")), ID_FILE_OPENPROGRAM);
								{
									Menu* pMenu2 = new Menu(new TextString(WSTR("Debug")));
									pMenu2->AddItem(new TextString(WSTR("Go")), ID_DEBUG_GO);
									pMenu2->AddItem(new TextString(WSTR("Restart")), 32787+1);
									pMenu2->AddItem(new TextString(WSTR("Step Into")), ID_DEBUG_STEPINTO);
									pMenu2->AddItem(new TextString(WSTR("Step Back")), 32787+2);
									pMenu->AddMenuItem(pMenu2);
								}
								{
									Menu* pMenu2 = new Menu(new TextString(WSTR("Edit")));
									pMenu2->AddItem(new TextString(WSTR("Cut")), ID_EDIT_CUT);
									pMenu2->AddItem(new TextString(WSTR("Copy")), ID_EDIT_COPY);
									pMenu2->AddItem(new TextString(WSTR("Paste")), ID_EDIT_PASTE);
									pMenu->AddMenuItem(pMenu2);
								}
								/*
								{
									Menu* pMenu2 = new Menu(new TextString(WSTR("Prefs2")));
									pMenu2->AddItem(new TextString(WSTR("Local")));
									pMenu2->AddItem(new TextString(WSTR("Global")));
									pMenu2->AddItem(new TextString(WSTR("Something")));
									{
										Menu* pMenu3 = new Menu(new TextString(WSTR("Prefs3")));
										pMenu3->AddItem(new TextString(WSTR("Local")));
										pMenu3->AddItem(new TextString(WSTR("Global")));
										pMenu3->AddItem(new TextString(WSTR("Something")));
										pMenu2->AddMenuItem(pMenu3);
									}

									pMenu->AddMenuItem(pMenu2);
								}
								*/
								pMenu->AddSeparator();
								pMenu->AddItem(new TextString(WSTR("Exit")), ID_APP_EXIT);
							}
							pToolbar->get_Children()->Add(pMenu);
#if 0
							Menu* pMenu = new Menu;
							pMenu->put_VisualTree(new Button(new TextString(WSTR("File"))));
							{
							//	CLXUIBorder* pBorder = new CLXUIBorder;
							//	pBorder->put_BackgroundBrush(new SolidColorBrush(new Color(255, 255, 255)));

								DockPanel* pPanel = new DockPanel;
								pPanel->AddRChild(new Button(new TextString(WSTR("Open"))));
								pPanel->AddRChild(new Button(new TextString(WSTR("Save"))));
								pPanel->AddRChild(new Button(new TextString(WSTR("Save As"))));
								pPanel->AddRChild(new Button(new TextString(WSTR("Exit"))));

							//	pBorder->put_Content(pPanel);
								pMenu->put_PopupContent(pPanel);
							}
							pToolbar->AddRChild(pMenu);
#endif
						}
#endif

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(WSTR("Save")));
							pToolbar->get_Children()->Add(pButton);
						}

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(WSTR("Exit")));
							pToolbar->get_Children()->Add(pButton);
						}

						/*
						{
							TextString* pText = new TextString(WSTR("Button0"), font);
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(WSTR("Button1"), font);
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(WSTR("Button2"), font);
							pToolbar->AddRChild(pText);
						}
						*/

						//pGripper->put_Content(pToolbar);
						pDockbar->DockControlBar(pToolbar);
					}
					//pDockbar->DockControlBar(pGripper);
				}

				{
				//	Gripper* pGripper = new Gripper;
				//	pGripper->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(255, 0, 0)));
					{
						ToolBarPanel* pToolbar = new ToolBarPanel;
					//	pToolbar->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(0, 255, 0)));

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(WSTR("Cut")));
							pToolbar->get_Children()->Add(pButton);
						}

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(WSTR("Copy")));
							pToolbar->get_Children()->Add(pButton);
						}

						{
							Button* pButton = new Button;
							pButton->set_Content(new TextString(WSTR("Paste")));
							pToolbar->get_Children()->Add(pButton);
						}


				//		pGripper->put_Content(pToolbar);
						pDockbar->DockControlBar(pToolbar);
					}
				//	pDockbar->DockControlBar(pGripper);
				}

				/*
				{
					Toolbar* pToolbar = new Toolbar;
					{
						TextString* pText = new TextString(WSTR("Test0"), font);
						pToolbar->AddRChild(pText);
					}

					{
						TextString* pText = new TextString(WSTR("Test1"), font);
						pToolbar->AddRChild(pText);
					}

					{
						TextString* pText = new TextString(WSTR("Test2"), font);
						pToolbar->AddRChild(pText);
					}
					pDockbar->AddRChild(pToolbar);
				}
				*/
			}
			p->SetDock(pDockbar, DockPanel::Top);
			p->get_Children()->Add(pDockbar);
#endif
		}

#if 0
		{
			CUIDockBar* pDockbar = new CUIDockBar;
			{
				pDockbar->set_Background(new SolidColorBrush(new Color(236, 233, 216)));
			}
			p->SetDock(pDockbar, DockPanel::Bottom);
			p->get_Children()->Add(pDockbar);
		}
#endif

		pCanvas = new ChildWindowContainer;
		{
			/*
			{
				CLXUIRectangle* pRect = new CLXUIRectangle();
				pRect->set_RectangleWidth(new Length(1, Length::UnitPercentage));
				pRect->set_RectangleHeight(new Length(1, Length::UnitPercentage));
				pRect->set_Fill(new SolidColorBrush(new Color(165, 160, 160), 1));

				pCanvas->AddRChild(pRect);
			}
			*/

			/*
			{
				CLXUIRectangle* pRect = new CLXUIRectangle();
				pRect->set_RectangleWidth(new Length(0.5, Length::UnitPercentage));
				pRect->set_RectangleHeight(new Length(0.5, Length::UnitPercentage));
				pRect->set_Fill(new SolidColorBrush(new Color(0, 255, 160), 1));

				pCanvas->AddRChild(pRect);
			}
			*/


			{
				ISequentialByteStream* fp = new FileByteStream(ASTR("c:/windows/fonts/cour.ttf"));
				if (fp)
				{
					m_pFile = new LType::TTFontFile;
					//m_pFile->m_fp = fp;

					m_pFile->Init2(fp);
					m_pTTFont = new LType::TTFont(m_pFile, 14);
					pGlyph2 = m_pTTFont->GetFile()->ParseGlyph(m_pTTFont->GetFile()->CharToGlyph('G'));

					vm = m_pTTFont->SetupGlyphVM(pGlyph2);

					m_nSteps = 0;

					if (false)
					{
						while (vm->next())
						{
							m_nSteps++;
						}
					}
				}
			}

			{
				m_fontProgramWin = new TTInstructionsControl;
				m_fontProgramWin->m_frame = m_breakpoints;
				m_fontProgramWin->m_instructions = new FontInstructions(m_pTTFont->GetFile()->m_fontPrgData, m_pTTFont->GetFile()->m_fontPrgLength);

				while (m_fontProgramWin->m_instructions->pc < m_pTTFont->GetFile()->m_fontPrgData+m_pTTFont->GetFile()->m_fontPrgLength)
				{
					m_fontProgramWin->m_instructions->next();
				}

				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//set_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//set_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(240);
				pWindow->set_Height(210);
				m_fontProgramWin->m_pScroller = new ScrollViewer;
				{
					m_fontProgramWin->m_pScroller->set_Content(m_fontProgramWin);
				}
				pWindow->set_Content(m_fontProgramWin->m_pScroller);
				pWindow->set_Title(WSTR("Font Program"));
				pCanvas->get_Items()->Add(pWindow);
			}

			{
				m_glyphProgramWin = new TTInstructionsControl;
				m_glyphProgramWin->m_frame = m_breakpoints;
				m_glyphProgramWin->m_instructions = new FontInstructions(pGlyph2->instructionsData, pGlyph2->instructionsLength);

				while (m_glyphProgramWin->m_instructions->pc < pGlyph2->instructionsData+pGlyph2->instructionsLength)
				{
					m_glyphProgramWin->m_instructions->next();
				}

				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//set_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//set_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(240);
				pWindow->set_Height(210);
				m_glyphProgramWin->m_pScroller = new ScrollViewer;
				{
					m_glyphProgramWin->m_pScroller->set_Content(m_glyphProgramWin);
				}
				pWindow->set_Content(m_glyphProgramWin->m_pScroller);
				pWindow->set_Title(WSTR("Glyph Program"));
				pCanvas->get_Items()->Add(pWindow);
			}

			{
				m_glyphPreviewWin = new GlyphPreview(this);
				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//set_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//set_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(240);
				pWindow->set_Height(210);
				pWindow->set_Content(m_glyphPreviewWin);
				pWindow->set_Title(WSTR("Glyph Preview"));
				pCanvas->get_Items()->Add(pWindow);
			}

			{
				m_stackWin = new TreeControl;
				m_stackWin->/*m_treeHeader->*/AddColumn(new TextString(WSTR("Index")));
				m_stackWin->/*m_treeHeader->*/AddColumn(new TextString(WSTR("Value")));
				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//set_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//set_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(240);
				pWindow->set_Height(210);
				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->set_Content(m_stackWin);
				}
				pWindow->set_Content(pScroller);
				pWindow->set_Title(WSTR("Stack"));
			//	pCanvas->get_Children()->Add(pWindow);
			}

			{
				m_cvtWin = new TreeControl;
				m_cvtWin->/*get_ColumnHeaderList()->*/AddColumn(new TextString(WSTR("Index")));
				m_cvtWin->/*get_ColumnHeaderList()->*/AddColumn(new TextString(WSTR("New Value")));
				m_cvtWin->/*get_ColumnHeaderList()->*/AddColumn(new TextString(WSTR("Original Value")));
				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//set_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//set_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(240);
				pWindow->set_Height(210);
				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->set_Content(m_cvtWin);
				}
				pWindow->set_Content(pScroller);
				pWindow->set_Title(WSTR("CVT"));
			//	pCanvas->get_Children()->Add(pWindow);
			}

			{
				m_infoWin = new DockPanel;
				ChildWindow* pWindow = new ChildWindow;
				pWindow->m_computedLeft = 80;//set_Left(pWindow, new Length(100, UnitAbsolute));
				pWindow->m_computedTop = 80;//set_Top(new Length(100, UnitAbsolute));
				pWindow->set_Width(240);
				pWindow->set_Height(210);
				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->set_Content(m_infoWin);
				}
				pWindow->set_Content(pScroller);
				pWindow->set_Title(WSTR("Info"));
			//	pCanvas->AddChild(pWindow);
			}
		}
		p->SetDock(pCanvas, DockPanel::Fill);
		p->get_Children()->Add(pCanvas);
	}
	set_Content(p);
	set_Title(WSTR("LTTDebugger"));
#endif
}

#if 0
void TTDebuggerFrame::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*type == L"command")
		{
			CommandInvokeEvent* cmdEvt = dynamic_cast<CommandInvokeEvent*>(evt);

#if 0
			if (cmdEvt->get_Command() == ID_FILE_OPEN)
			{
				OnFileOpen();
				return;
			}
			else if (cmdEvt->get_Command() == ID_FILE_OPENPROGRAM)
			{
				OnFileOpenProgram();
				return;
			}
#endif
			if (cmdEvt->get_Command() == ID_DEBUG_STEPINTO)
			{
				OnDebugStepInto();
				return;
			}
			else if (cmdEvt->get_Command() == 32787+2)
			{
				OnDebugStepBack();
				return;
			}
			else if (cmdEvt->get_Command() == ID_DEBUG_GO)
			{
				OnDebugGo();
				return;
			}
			else if (cmdEvt->get_Command() == 32787+1)
			{
				OnDebugGoBack();
				return;
			}
		}
#if 0
		else if (*type == L"click")
		{
			evt->stopPropagation();

			ResultsView* pResults = new ResultsView;

			sysstring searchString = m_searchEdit->GetText();

			pP2P->Search(searchString, static_cast<ISearchHitHandler*>(pResults));

			ChildWindow* pWindow = new ChildWindow;
			pWindow->put_Width(new Length(300, Length::UnitAbsolute));
			pWindow->put_Height(new Length(300, Length::UnitAbsolute));
			pWindow->put_Content(pResults);
			pWindow->put_TitleText(searchString);
			pWindow->SetOwnerWindow(pCanvas->get_OwnerWindow());
			pCanvas->AddChild(pWindow);
		}
#endif
		if (*type == L"keydown")
		{
			KeyEvent* keyEvt = dynamic_cast<KeyEvent*>(evt);

			if (keyEvt->vk == VK_F5 && !keyEvt->bControl && !keyEvt->bShift)
			{
				evt->stopPropagation();
				OnDebugGo();
			}
			else if (keyEvt->vk == VK_F10 && !keyEvt->bControl && !keyEvt->bShift)
			{
				evt->stopPropagation();
				OnDebugStepInto();
			}
			else if (keyEvt->vk == VK_F5 && keyEvt->bControl && keyEvt->bShift)
			{
				evt->stopPropagation();
				OnDebugGoBack();
			}
			else if (keyEvt->vk == VK_F10 && keyEvt->bControl && keyEvt->bShift)
			{
				evt->stopPropagation();
				OnDebugStepBack();
			}

			return;
		}
		else if (type == MouseEvent::mousedown)
		{
		//	OnDebugStepInto();
		}
	}

	CLXUIWindow::handleEvent(evt);
}
#endif

void TTDebuggerFrame::OnDebugGo()
{
	if (vm->m_ctx)
	{
		while (vm->m_ctx)
		{
			if (*vm->pc == 0x4f)
			{
				/*
				if (vm->pc >= m_glyphProgramWin->m_instructions->m_start && vm->pc <m_glyphProgramWin->m_instructions->m_start+m_glyphProgramWin->m_instructions->m_length)
				{
					uint16 offset = vm->pc - m_glyphProgramWin->m_instructions->m_start;
					tyttbreakpointmap::iterator ttii = m_glyphProgramWin->m_instructions->m_breakpoints.find(offset);

					*vm->pc = (*ttii).second.m_oldbyte;
				}
				else
				{
					uint16 offset = vm->pc - m_fontProgramWin->m_instructions->m_start;
					tyttbreakpointmap::iterator ttii = m_fontProgramWin->m_instructions->m_breakpoints.find(offset);

					*vm->pc = (*ttii).second.m_oldbyte;
				}
				*/

				//uint8 m_breakpointsuint16 offset = vm->pc - m_glyphProgramWin->m_instructions->m_start;
#if 0
				ttbreakpointaddrmap_t::iterator tti = m_breakpoints.find(vm->pc);

				uint8 oldbyte = (*tti).second;
				*vm->pc = oldbyte;
#endif
				break;
			}
			vm->next();
			m_nSteps++;
		}

		Update();
	}
}

void TTDebuggerFrame::OnDebugGoBack()
{
	delete vm;
	vm = m_pTTFont->SetupGlyphVM(pGlyph2);
	m_nSteps = 0;
	Update();
}

void TTDebuggerFrame::OnDebugStepInto()
{
	if (vm->m_ctx)
	{
		uint8* pc = vm->pc;
		bool bBreakpoint = *pc == 0x4f;
		if (bBreakpoint)
		{
			ttbreakpointaddrmap_t::iterator it = m_breakpoints->m_breakpoints.find(pc);
			*pc = (*it).second;
		}

		vm->next();
		m_nSteps++;

		if (bBreakpoint)
		{
			*pc = 0x4f;
		}

		Update();
	}
}

void TTDebuggerFrame::OnDebugStepBack()
{
	if (m_nSteps > 0)
	{
		delete vm;
		vm = m_pTTFont->SetupGlyphVM(pGlyph2);
		for (ULONG n = 0; n < m_nSteps-1; n++)
		{
			uint8* pc = vm->pc;
			bool bBreakpoint = *pc == 0x4f;
			if (bBreakpoint)
			{
				ttbreakpointaddrmap_t::iterator it = m_breakpoints->m_breakpoints.find(pc);
				*pc = (*it).second;
			}

			vm->next();

			if (bBreakpoint)
			{
				*pc = 0x4f;
			}
		}
		m_nSteps--;

		Update();
	}
}

void TTDebuggerFrame::Update()
{
	m_glyphProgramWin->Update();
	m_fontProgramWin->Update();
	m_glyphPreviewWin->Invalidate();

#if 0	// TODO, Have this
	{
		TreeItemChildren* Elements = new TreeItemChildren(m_cvtWin);

		for (int i = 0; i < ::m_pTTFont->GetFile()->m_cvtSize; i++)
		{
			TreeItem* item = new TreeItem(m_cvtWin);
			{
				{
					OLECHAR buf[32];
					swprintf(buf, L"%d", i);
					item->AppendColumnCell(new TextString(buf));
				}

				{
					OLECHAR buf[32];
					swprintf(buf, L"%d", ::m_pTTFont->m_cvt[i]);
					item->AppendColumnCell(new TextString(buf));
				}

				{
					OLECHAR buf[32];
					swprintf(buf, L"%d", ::m_pTTFont->GetFile()->m_cvt[i]);
					item->AppendColumnCell(new TextString(buf));
				}
			}
			Elements->AppendItem(item);
		}
		m_cvtWin->put_Children(Elements);
	}

	{
		TreeItemChildren* StackElements = new TreeItemChildren(m_stackWin);

		for (int i = vm->m_stack.size()-1; i >= 0; i--)
		{
			TreeItem* item = new TreeItem(m_stackWin);
			{
				OLECHAR buf[32];
				swprintf(buf, L"%d", i);
				item->AppendColumnCell(new TextString(buf));
			}
			{
				OLECHAR buf[32];
				swprintf(buf, L"%d", vm->m_stack[i]);
				item->AppendColumnCell(new TextString(buf));
			}

			StackElements->AppendItem(item);
		}

		m_stackWin->put_Children(StackElements);
	}
#endif
}

}
