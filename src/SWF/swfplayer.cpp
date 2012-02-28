#include "stdafx.h"
#include "swf.h"
#include "swfplayer.h"
#include "swfdecoder.h"

//#include "_Movie.h"

#include "../include/windows_header.h"

namespace System
{
namespace SWF
{

Player::Player()
{
	m_OverButton = NULL;
}

Player::~Player()
{
}

Movie* Player::GetMovie() const
{
	return m_movie;
}

void Player::SetMovie(Movie* movie)
{
	if (m_movie != movie)
	{
		m_movie = movie;

		m_movie->SetMember(ASTR("_parent"), System::ActionScripting::StkElt(static_cast<Object*>(this)));

		m_placedMovie = new PlacedCharacter;
	//	m_placedMovie->m_character = Object2(movie);

		Invalidate();
	}
}

class Wind : public MSWindows::WindowImpl//<Wind>
{
public:

	Player* m_player;

	virtual bool ProcessWindowMessage(MSWindows::HWND hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult/*, DWORD dwMsgMapID*/ )
	{
		if (uMsg == WM_TIMER)
		{
			m_player->OnAdvance();
			return true;
		}
		return false;
	}
};

void Player::OnAdvance()
{
	if (m_placedMovie->m_currentFrame < m_movie->GetFrameCount()-1)
	{
		m_placedMovie->m_gotoFrame++;
		OnAdvance(m_movie, m_placedMovie);
	}
}

/*
void Player::AdvanceFrame(_Timeline* timeline)
{
	Tag tag;
	m_decoder->BeginTag(&tag);

	if (tag.Code == Tag::ShowFrame)	// End of frame
		break;

	LONGLONG startpos = decoder->Seek(0);

	decoder->ParseTimelineTag(tag, timeline, &m_movie);

	decoder->Seek(startpos + tag.Length, System::IO::STREAM_SEEK_SET);
}
*/

void Player::OnAdvance(Timeline* timeline, PlacedCharacter* placed)
{
	while (placed->m_gotoFrame != placed->m_currentFrame/*pSprite->m_DecodedFrameCount*/)//< pSprite->GetFrameCount())
//	if (placed->m_currentFrame < pSprite->GetFrameCount())
	{
//		MessageBeep(-1);

		ASSERT(timeline->m_frames.GetSize() > placed->m_gotoFrame+1);
		Frame* pFrame = timeline->m_frames[placed->m_gotoFrame];
		m_decoder->Seek(pFrame->m_streamPos, System::IO::STREAM_SEEK_SET);

		placed->m_currentFrame = placed->m_gotoFrame;
		pFrame->m_doActions.RemoveAll();

		while (1)
		{
			Tag tag;
			m_decoder->BeginTag(&tag);

			if (tag.Code == 0)	// End tag
				break;

			if (tag.Code == Tag::ShowFrame)
				break;

			LONGLONG startpos = m_decoder->Seek(0);

			m_decoder->ExecuteTimelineTag(tag, timeline, pFrame, m_movie);

			m_decoder->Seek(startpos + tag.Length, System::IO::STREAM_SEEK_SET);
		}
		{
			// Perform accumulated DoAction tags for this frame
			pFrame->DoActions(placed);
		}
	}

	OnAdvanceChildren(timeline);
}

void Player::OnAdvanceChildren(Timeline* timeline)
{
	for (int i = 0; i < 65536; i++)
	{
		PlacedCharacter* placed = timeline->GetPlacedCharacterAtDepth(i);
		if (placed)
		{
		//	Character def = m_movie.GetCharacter(placed->m_CharacterID);
			Character* def = placed->m_character;

			Sprite* sprite = dynamic_cast<Sprite*>(def);
			if (sprite != NULL)
			{
			//	placed->m_currentFrame = 2;

				OnAdvance(sprite, placed);

				//	pSprite->m_DecodedFrameCount++;
				//	placed->m_currentFrame++;
				//	pSprite->m_DecodedFrameCount = placed->m_currentFrame;
			}
		}
	}

	Invalidate();
}

void Player::Play()
{
	while (1)
	{
		Tag tag;
		m_decoder->BeginTag(&tag);

		if (tag.Code == 0)	// End tag
			break;

		LONGLONG startpos = m_decoder->Seek(0);

		m_decoder->ParseMovieTag(tag, m_movie);

		long cur = m_decoder->Seek(0);
		if (cur > startpos + tag.Length)
		{
			ASSERT(0);
		}

		m_decoder->Seek(startpos + tag.Length, System::IO::STREAM_SEEK_SET);
	}

	m_pWind = new Wind;
	m_pWind->m_player = this;
	//RECT rc;
	//SetRectEmpty(&rc);
	m_pWind->Create(NULL, LDraw::RectI(), NULL, WS_POPUP);

	m_pWind->SetTimer(1, 1000 / (m_movie->GetFrameRate() / 256.0));
}

void Player::RenderShape(const ShapeData* shape, LDraw::Brush* brush, UI::Graphics* pGraphics)
{
	LDraw::GraphicsPathF* path;
	const LDraw::PointI* points = shape->m_points.GetData();

	long curX = 0;
	long curY = 0;

	for (int i = 0; i < shape->m_types.GetSize(); i++)
	{
		if (shape->m_types[i] == 0)
		{
			/*
			if (i > 0)
			{
				path.CloseFigure();
			}
			*/

			path->AddMove(points->X, points->Y);
			curX = points->X;
			curY = points->Y;
			points++;
		}
		else if (shape->m_types[i] == 1)
		{
			path->AddLine(points->X, points->Y);
			curX = points->X;
			curY = points->Y;
			points++;
		}
		else
		{
			/*
			LDraw::PointD cubic[4];
			LDraw::PointD quad[3];
			quad[0].X = curX;
			quad[0].Y = curY;
			quad[1].X = points[0].X;
			quad[1].Y = points[0].Y;
			quad[2].X = points[1].X;
			quad[2].Y = points[1].Y;

			LDraw::MakeBezierFromQBSpline(cubic, quad);

			path.AddBezier(
				cubic[1].X, cubic[1].Y,
				cubic[2].X, cubic[2].Y,
				cubic[3].X, cubic[3].Y);
			*/
			
			path->AddBezier2(points[0].X, points[0].Y, points[1].X, points[1].Y);

			curX = points[1].X;
			curY = points[1].Y;

			points += 2;

		}
	}

	if (shape->m_fillStyles.GetSize() > 0)
	{
		FillStyle* fillStyle = shape->m_fillStyles[0];

		if (fillStyle->GetType() == 0)
		{
			brush = new LDraw::SolidBrush(fillStyle->GetColor());
		}
		else if (fillStyle->GetFillType() & 0x40)
		{
			BitmapCharacter* bitmapCharacter = fillStyle->GetBitmapCharacter();

			/*
			LDraw::BitmapData bitmapdata;
			bitmapdata.Width = bitmapCharacter.GetWidth();
			bitmapdata.Height = bitmapCharacter.GetHeight();
			bitmapdata.PixelFormat = LDraw::PixelFormat_t::RGBAP_32;
			bitmapdata.Scan0 = bitmapCharacter.GetBits();
			bitmapdata.Stride = bitmapCharacter.GetRowBytes();
			*/

			LDraw::Bitmap* bitmap = new LDraw::Bitmap(
				bitmapCharacter->GetWidth(),
				bitmapCharacter->GetHeight(),
				bitmapCharacter->GetRowBytes(),
				LDraw::PixelFormat_t::RGBAP_32,
				bitmapCharacter->GetBits());

			LDraw::TextureBrush* textureBrush = new LDraw::TextureBrush(bitmap);
			textureBrush->ScaleTransform(20, 20);

			brush = textureBrush;
		}
	}

	pGraphics->FillPath(brush, path);
}

void Player::RenderShape(ShapeCharacter* shape, UI::Graphics* pGraphics)
{
	RenderShape(shape, NULL, pGraphics);
}

/*
void Player::RenderBitmap(BitmapCharacter bitmapCharacter, LDraw::Graphics* pGraphics)
{
	LDraw::BitmapData bitmapdata;
	bitmapdata.Width = bitmapCharacter.GetWidth();
	bitmapdata.Height = bitmapCharacter.GetWidth();
	bitmapdata.PixelFormat = RGB_32;
	bitmapdata.Scan0 = bitmapCharacter.GetBits();
	bitmapdata.Stride = bitmapCharacter.GetRowBytes();

	LDraw::Bitmap bitmap(bitmapdata);

	pGraphics->DrawImage(&bitmap, 0, 0);
}
*/

void Player::RenderText(TextCharacter* pText, const ColorTransform& colorTransform, UI::Graphics* pGraphics)
{
	//TextCharacter::_TextCharacter* pText = (TextCharacter::_TextCharacter*)textCharacter.m_p;

	for (int i = 0; i < pText->m_runs.GetSize(); i++)
	{
		GlyphRun* pRun = pText->m_runs[i];

		double x = pRun->m_XOffset;

		for (int j = 0; j < pRun->m_glyphs.GetSize(); j++)
		{
			/*LDraw::Matrix3f oldTransform =*/ pGraphics->PushTransform();

			RGBAColor color = pRun->m_color;

			color.Red = (color.Red * colorTransform.MulR) / 256 + colorTransform.AddR;
			color.Green = (color.Green * colorTransform.MulR) / 256 + colorTransform.AddG;
			color.Blue = (color.Blue * colorTransform.MulR) / 256 + colorTransform.AddB;
			color.Alpha = (color.Alpha * colorTransform.MulR) / 256 + colorTransform.AddA;

			pGraphics->TranslateTransform(x, pRun->m_YOffset);
			pGraphics->ScaleTransform(pRun->m_fontHeight / 1024.0, pRun->m_fontHeight / 1024.0);
			RenderShape(pRun->m_font->GetGlyph(pRun->m_glyphs[j]), new LDraw::SolidBrush(color), pGraphics);

			pGraphics->PopTransform();//oldTransform);

			x += pRun->m_widths[j];
		}
	}
}

void Player::Render(Timeline* timeline, const ColorTransform& colorTransform, UI::Graphics* pGraphics)
{
	for (int i = 0; i < 65536; i++)
	{
		PlacedCharacter* placed = timeline->GetPlacedCharacterAtDepth(i);
		if (placed)
		{
		//	Character def = m_movie.GetCharacter(placed->m_CharacterID);
			Character* def = placed->m_character;

			/*LDraw::Matrix3f oldTransform =*/ pGraphics->PushTransform();

			pGraphics->MultiplyTransform(placed->m_transform);

			ShapeCharacter* shape = dynamic_cast<ShapeCharacter*>(def);
			if (shape != NULL)
			{
				RenderShape(shape, pGraphics);
			}

			TextCharacter* text = dynamic_cast<TextCharacter*>(def);
			if (text != NULL)
			{
				RenderText(text, colorTransform * placed->m_colorTransform, pGraphics);
			}

			Sprite* sprite = dynamic_cast<Sprite*>(def);
			if (sprite != NULL)
			{
				Render(sprite, placed->m_colorTransform, pGraphics);
			}

			/*
			BitmapCharacter bitmap = def;
			if (bitmap != NULL)
			{
				RenderBitmap(bitmap, pGraphics);
			}
			*/

			pGraphics->PopTransform();//oldTransform);
		}
	}
}

PlacedCharacter* Player::HitTest(Timeline* timeline, LDraw::PointD point, LDraw::Matrix3f* transform)
{
	for (int i = 65536-1; i >= 0; i--)
	{
		PlacedCharacter* placed = timeline->GetPlacedCharacterAtDepth(i);
		if (placed)
		{
		//	Character def = m_movie.GetCharacter(placed->m_CharacterID);
			Character* def = placed->m_character;

	//		LDraw::Matrix oldTransform = pGraphics->GetTransform();

			transform->Multiply(placed->m_transform);
			//pGraphics->MultiplyTransform(placed->m_transform);

#if 0
			ShapeCharacter shape = def;
			if (shape != NULL)
			{
				LDraw::Matrix itransform = transform;
				itransform.Inverse();

				LDraw::PointD xpt = itransform.Transform(point);

				Rect bounds;
				shape.GetBounds(&bounds);

				if (xpt.X >= bounds.Xmin && xpt.Y >= bounds.Ymin && xpt.X < bounds.Xmax && xpt.Y < bounds.Ymax)
				{
					return placed;
				}
				
			//	HitTestShape(shape, pGraphics);
			}
#endif
			ButtonCharacter* button = dynamic_cast<ButtonCharacter*>(def);
			if (button != NULL)
			{
				//ButtonCharacter* pButton = (ButtonCharacter::_ButtonCharacter*)button.m_p;

				for (int i = 0; i < button->m_HitTest.GetSize(); i++)
				{
					ShapeCharacter* shape = button->m_HitTest[i]->m_shape;

					Rect bounds;
					shape->GetBounds(&bounds);

					LDraw::Matrix3f* itransform = transform->GetInverse();
					LDraw::PointD xpt = itransform->Transform(point);

					if (xpt.X >= bounds.Xmin && xpt.Y >= bounds.Ymin && xpt.X < bounds.Xmax && xpt.Y < bounds.Ymax)
					{
						return placed;
					}
				}
				
			//	HitTestShape(shape, pGraphics);
			}

			/*
			TextCharacter text = def;
			if (text != NULL)
			{
				RenderText(text, colorTransform * placed->m_colorTransform, pGraphics);
			}
*/
			Sprite* sprite = dynamic_cast<Sprite*>(def);
			if (sprite != NULL)
			{
				PlacedCharacter* placed = HitTest(sprite, point, transform);
				if (placed)
					return placed;
			}

			/*
			BitmapCharacter bitmap = def;
			if (bitmap != NULL)
			{
				RenderBitmap(bitmap, pGraphics);
			}
			*/

		//	pGraphics->SetTransform(oldTransform);
		}
	}

	return NULL;
}

LDraw::SizeD Player::OnMeasure(LDraw::SizeD availSize)
{
	Rect FrameSize = m_movie->GetFrameSize();
	return LDraw::SizeD(FrameSize.Xmax / 20.0, FrameSize.Ymax / 20.0);
}

void Player::OnRender(UI::Graphics* pGraphics)
{
	if (m_movie->HasBackgroundColor())
	{
		LDraw::SolidBrush* backgroundBrush = new LDraw::SolidBrush(m_movie->GetBackgroundColor());
		pGraphics->FillRectangle(backgroundBrush, 0, 0, m_computedSize.Width, m_computedSize.Height);
	}

	pGraphics->ScaleTransform(1/20.0, 1/20.0);	// swf twips are 1/20 of a pixel

	LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
	if (false)
	{
		pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);
	}

	ColorTransform colorTransform;
	Render(m_movie, colorTransform, pGraphics);

	pGraphics->SetSmoothingMode(oldSmoothingMode);
}

void Player::ExecuteScripts(PlacedCharacter* placed, ButtonCharacter* pButton, uint16 condMask)
{
	for (unsigned int i = 0; i < pButton->m_scripts.GetSize(); i++)
	{
		ButtonActionScript* pScript = pButton->m_scripts[i];
		if (pScript->m_cond & condMask)
		{
			System::ActionScripting::VM vm;
			vm.m_pFrame = new System::ActionScripting::StackFrame;
			vm.m_pFrame->m_pContext = pScript->m_context;
			vm.m_pFrame->m_instructionsData = pScript->m_data;
			vm.m_pFrame->m_instructionsLength = pScript->m_length;
			vm.m_pc = pScript->m_data;

			vm.m_pFrame->m_variables[ASTR("this")] = System::ActionScripting::StkElt(static_cast<Object*>(placed));//StringA("this");
			vm.m_pFrame->m_variables[ASTR("_root")] = System::ActionScripting::StkElt(static_cast<Object*>(this)/*m_movie.m_p*/);

			while (vm.next())
				;

			ASSERT(vm.m_stack.GetSize() == 0);
		}
	}
}

void Player::OnMouseMove(UI::MouseEventArgs* args)
{
	LDraw::PointD point = args->GetPosition(this);//ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());

	LDraw::Matrix3f* transform = LDraw::Matrix3f::GetScale(1/20.0, 1/20.0);
	PlacedCharacter* placed = HitTest(m_movie, point, transform);

	ButtonCharacter* button;
	if (placed)
	{
		button = dynamic_cast<ButtonCharacter*>(placed->m_character);
	}

	if (m_OverButton != placed)
	{
		if (m_OverButton != NULL)
		{
			ExecuteScripts(m_OverButton, (ButtonCharacter*)m_OverButton->m_character, CondOverUpToIdle);
		}

	//	if (button != NULL)
		{
			m_OverButton = placed;
		}

		if (m_OverButton != NULL)
		{
			ExecuteScripts(m_OverButton, (ButtonCharacter*)m_OverButton->m_character, CondIdleToOverUp);
		}

		Invalidate();
	}
}

void Player::OnButtonDown(UI::MouseButtonEventArgs* args)
{
	/*
	LDraw::PointD point = ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());

	LDraw::Matrix transform;
	transform.Scale(1/20.0, 1/20.0);
	PlacedCharacter* placed = HitTest(m_movie.m_p, point, transform);

	if (placed)
	{
		ButtonCharacter button = placed->m_character;
		if (button != NULL)
		{
			MessageBeep(-1);
		}
	}
	*/
}

void Player::OnButtonUp(UI::MouseButtonEventArgs* args)
{
	/*
	LDraw::PointD point = ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());

	LDraw::Matrix transform;
	transform.Scale(1/20.0, 1/20.0);
	PlacedCharacter* placed = HitTest(m_movie.m_p, point, transform);

	if (placed)
	{
		ButtonCharacter button = placed->m_character;
		if (button != NULL)
		{
			MessageBeep(-1);
		}
	}
	*/
}

#if 0
void Player::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
			evt->stopPropagation();
			OnButtonDown(dynamic_cast<UI::MouseEvent*>(evt));
		}
		else if (*evt->get_type() == L"mouseup")
		{
			evt->stopPropagation();
			OnButtonUp(dynamic_cast<UI::MouseEvent*>(evt));
		}
		else if (*evt->get_type() == L"mousemove")
		{
			evt->stopPropagation();
			OnMouseMove(dynamic_cast<UI::MouseEvent*>(evt));
		}
	}
}
#endif

}	// LSWF
}
