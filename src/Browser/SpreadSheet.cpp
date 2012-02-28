#include "stdafx.h"
#include "Browser.h"
#include "SpreadSheet.h"
#include "OleCompoundFile.h"

namespace System
{
using namespace UI;

LDraw::Font* Font::GetFont()
{
	ASSERT(this);

	if (m_bDirty || m_font == NULL)
	{
		uint16 style = 0;
		if (m_bold) style |= 1;
		if (m_italic) style |= 2;
		m_font = new LDraw::Font(m_name, m_ptHeight * (96.0/*pixelsPerInch*/ / 72), style);
		m_bDirty = false;
	}

	return m_font;
}

void DrawBorder(UI::Graphics* pGraphics, LDraw::Color light_color, LDraw::Color dark_color, const LDraw::RectI& rect)
{
	{
		LDraw::PointF points[] =
		{
			LDraw::PointF(rect.X, rect.Y),
			LDraw::PointF(rect.X, rect.GetBottom()),
			LDraw::PointF(rect.X+1, rect.GetBottom()-1),
			LDraw::PointF(rect.X+1, rect.Y+1),
			LDraw::PointF(rect.GetRight()-1, rect.Y+1),
			LDraw::PointF(rect.GetRight(), rect.Y),
		};

		pGraphics->FillPolygon(new LDraw::SolidBrush(light_color), points, 6);
	}

	{
		LDraw::PointF points[] =
		{
			LDraw::PointF(rect.X, rect.GetBottom()),
			LDraw::PointF(rect.GetRight(), rect.GetBottom()),
			LDraw::PointF(rect.GetRight(), rect.GetTop()),
			LDraw::PointF(rect.GetRight()-1, rect.GetTop()+1),
			LDraw::PointF(rect.GetRight()-1, rect.GetBottom()-1),
			LDraw::PointF(rect.GetLeft()+1, rect.GetBottom()-1),
		};

		pGraphics->FillPolygon(new LDraw::SolidBrush(dark_color), points, 6);
	}
}

SpreadSheetControl::SpreadSheetControl()
{
	m_pSheet = NULL;

	m_selectionRange = LDraw::RectI(0, 0, 1, 1);

	m_dragging = 0;
}

LDraw::SizeD SpreadSheetControl::OnMeasure(LDraw::SizeD availSize)
{
	return LDraw::SizeD(10*m_pSheet->m_defColumnWidth, 22 + 10*m_pSheet->m_defRowHeight);
}

void SpreadSheetControl::OnArrange(LDraw::SizeD finalSize)
{
	ASSERT(0);
#if 0

	if (m_pSheet->m_pDrawingGroup)
	{
		int ncount = m_pSheet->m_pDrawingGroup->get_rchildList()->get_Size();
		for (int i = 0; i < ncount; i++)
		{
			MSODrawing::TopShape* pShape = dynamic_cast<MSODrawing::TopShape*>(m_pSheet->m_pDrawingGroup->get_rchildList()->Item(i));
			if (pShape)
			{
				pShape->m_pSheet = m_pSheet;	// TODO, not here

				LDraw::RectD topleftRect = GetCellRect(pShape->col1, pShape->row1);
				LDraw::RectD bottomrightRect = GetCellRect(pShape->col2, pShape->row2);

				LDraw::PointD topleft;
				topleft.X = topleftRect.X + topleftRect.Width * pShape->dx1;
				topleft.Y = topleftRect.Y + topleftRect.Height * pShape->dy1;

				LDraw::PointD bottomright;
				bottomright.X = bottomrightRect.X + bottomrightRect.Width * pShape->dx2;
				bottomright.Y = bottomrightRect.Y + bottomrightRect.Height * pShape->dy2;

				LDraw::SizeD size(bottomright.X - topleft.X, bottomright.Y - topleft.Y);

				pShape->Arrange(LDraw::RectD(topleft, size));
				//pShape->SetLayoutOffset(topleft.X, topleft.Y);
			}
		}
	}
#endif
}

LDraw::RectD SpreadSheetControl::GetCellRect(int ncol, int nrow)
{
	double x = 0;

	for (int col = 0; col < ncol; col++)
	{
		Column* pColumn = m_pSheet->m_columns[col];
		if (pColumn)
		{
			x += pColumn->GetPixelWidth();
		}
		else
			x += m_pSheet->m_defColumnWidth;
	}

	double y = 0;

	for (int row = 0; row < nrow; row++)
	{
		Row* pRow = m_pSheet->m_rows[row];
		if (pRow)
			y += pRow->GetPixelHeight();
		else
			y += m_pSheet->m_defRowHeight;
	}

	return LDraw::RectD(x, y, 80, 22);
}

void SpreadSheetControl::OnRender(Graphics* pGraphics)
{
	LDraw::Font* font = new LDraw::Font(WSTR("Arial"), 14);

	LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

	{
		pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 60, 20, m_computedSize.Width-60, m_computedSize.Height-20);
	}

//	double defwidth = 60;
//	double defheight = 20;

	{
		double x = 60;

	//	std::map<uint32, Column*>::iterator end = m_pSheet->m_columns.end();
	//	end--;
		int maxcol = 10;//(*end).first;

		for (int col = 0; col < maxcol; col++)
		{
			Column* pCol = m_pSheet->m_columns[col];

			double width;

			if (pCol)
				width = pCol->GetPixelWidth();
			else
				width = m_pSheet->m_defColumnWidth;

			LDraw::RectI rect(x, 0, width, 22);

			if (col >= m_selectionRange.GetLeft() && col < m_selectionRange.GetRight())
				pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(240, 190, 100)), rect);
			else
				pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(190, 190, 190)), rect);

			DrawBorder(pGraphics, LDraw::Color(255, 255, 255), LDraw::Color(0, 0, 0), rect);

			char buf[16];
			sprintf_s(buf, "%c", 'A' + col);

			pGraphics->DrawString(new StringA(string_copy(buf)), font, LDraw::PointF(x + 6, 3), new LDraw::SolidBrush(LDraw::Color(0, 0, 0)));

		//	pGraphics->FillRectangle

			x += rect.Width;//m_pSheet->m_columns[col]->m_width;
		}

		double y = 22;

		for (int row = 0; row < 10/*m_pSheet->m_rows.size()*/; row++)
		{
			Row* pRow = m_pSheet->m_rows[row];

			double height;

			if (pRow)
				height = pRow->GetPixelHeight();
			else
				height = m_pSheet->m_defRowHeight;

			LDraw::RectI rect(0, y, 60, height);

			if (row >= m_selectionRange.GetTop() && row < m_selectionRange.GetBottom())
				pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(240, 190, 100)), rect);
			else
				pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(190, 190, 190)), rect);

			DrawBorder(pGraphics, LDraw::Color(255, 255, 255), LDraw::Color(0, 0, 0), rect);

			char buf[32];
			std::sprintf(buf, "%d", row+1);

			pGraphics->DrawString(new StringA(string_copy(buf)), font, LDraw::PointF(6, y + 4), new LDraw::SolidBrush(LDraw::Color(0, 0, 0)));

			y += rect.Height;
		}
	}

	// Content
	{
		pGraphics->TranslateTransform(60, 22);

		double y = 0;

		for (int row = 0; row < 10/*m_pSheet->m_rows.size()*/; row++)
		{
			double x = 0;
			Row* pRow = m_pSheet->m_rows[row];

			double height;
			if (pRow)
				height = pRow->GetPixelHeight();
			else
				height = m_pSheet->m_defRowHeight;

			// Calculate the baseline of this row (TODO, do somewhere else)
			float rowBaselineY;
			if (pRow)
			{
				float maxdescent = 0;

				for (int col = 0; col < 10/*m_pSheet->m_columns.size()*/; col++)
				{
					Column* pColumn = m_pSheet->m_columns[col];

					Cell* pCell;
					pCell = pRow->m_cells[col];
					if (pCell)
					{
						ASSERT(pCell->m_xfIndex < m_pSheet->m_pWorkbook->m_XF.GetSize());
						Excel::XF* pXF = m_pSheet->m_pWorkbook->m_XF[pCell->m_xfIndex];

						int fontIndex = pXF->m_fontIndex;
						ASSERT(fontIndex < m_pSheet->m_pWorkbook->m_fonts.GetSize());

						Font* pFont = m_pSheet->m_pWorkbook->m_fonts[fontIndex];

						if (pCell->m_pStringContent)
						{
							StringEntry* pContent = pCell->m_pStringContent;

							{
								pCell->m_maxdescent = 0;
								int runIndex = 0;

								do
								{
									LDraw::Font* font = pFont->GetFont();
								//	float ascent = font.GetCellAscent();
									float ascent = font->GetCellAscent();
									float descent = font->GetCellDescent();
									float size = font->GetSize();

									pCell->m_maxascent = MAX(pCell->m_maxascent, ascent);
									pCell->m_maxdescent = MAX(pCell->m_maxdescent, descent);
									pCell->m_maxsize = MAX(pCell->m_maxsize, size);

									if (runIndex < pContent->m_textRuns.GetSize())
									{
										pFont = m_pSheet->m_pWorkbook->m_fonts[pContent->m_textRuns[runIndex].fontIndex];

										runIndex++;
									}
								}
								while (runIndex < pContent->m_textRuns.GetSize());
							}
						}

						if (pXF->m_vertAlign == Excel::VA_Bottom)
						{
							maxdescent = MAX(maxdescent, pCell->m_maxdescent);
						}
					}
				}

				rowBaselineY = height - maxdescent;
			}

			for (int col = 0; col < 10/*m_pSheet->m_columns.size()*/; col++)
			{
				Column* pColumn = m_pSheet->m_columns[col];

				Cell* pCell;
				if (pRow)
					pCell = pRow->m_cells[col];
				else
					pCell = NULL;

				double width;
				if (pColumn)
					width = pColumn->GetPixelWidth();
				else
					width = m_pSheet->m_defColumnWidth;

				pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(190, 190, 190)), x, y+height, width, 1);
				pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(190, 190, 190)), x+width, y, 1, height);

				if (pCell)
				{
					/*LDraw::Matrix3f oldTransform =*/ pGraphics->PushTransform();
					pGraphics->TranslateTransform(x+1, y+1);

					ASSERT(pCell->m_xfIndex < m_pSheet->m_pWorkbook->m_XF.GetSize());
					Excel::XF* pXF = m_pSheet->m_pWorkbook->m_XF[pCell->m_xfIndex];

					int fontIndex = pXF->m_fontIndex;
					ASSERT(fontIndex < m_pSheet->m_pWorkbook->m_fonts.GetSize());

					Font* pFont = m_pSheet->m_pWorkbook->m_fonts[fontIndex];

					int colorIndex = pFont->m_colorIndex;
					PaletteEntry color = m_pSheet->m_pWorkbook->GetColor(colorIndex);

					if (pCell->m_pStringContent)
					{
						StringEntry* pContent = pCell->m_pStringContent;

						double tx = 0;

						int charIndex = 0;
						StringW* str = pContent->m_str;
						const WCHAR* pstr = str->c_str();

						int runIndex = 0;
						while (charIndex < str->Length())
						{
							int runlength;

							if (runIndex < pContent->m_textRuns.GetSize())
								runlength = pContent->m_textRuns[runIndex].charIndex - charIndex;	// Up to the next run
							else
								runlength = str->Length() - charIndex;	// Rest of string

							LDraw::Font* font = pFont->GetFont();
							float ascent = font->GetCellAscent();
							float size = font->GetSize();

							float ty;

							if (pXF->m_vertAlign == Excel::VA_Bottom)
								ty = rowBaselineY - ascent;
							else if (pXF->m_vertAlign == Excel::VA_Top)
								ty = 0;
							else if (pXF->m_vertAlign == Excel::VA_Center)
								ty = (height)/2 + pCell->m_maxascent/2 - ascent;
							else
								ASSERT(0);

							pGraphics->DrawString(pstr, runlength, font, LDraw::PointF(tx, ty), new LDraw::SolidBrush(color.m_rgb));

							if (runIndex < pContent->m_textRuns.GetSize())
							{
								pFont = m_pSheet->m_pWorkbook->m_fonts[pContent->m_textRuns[runIndex].fontIndex];
								colorIndex = pFont->m_colorIndex;
								color = m_pSheet->m_pWorkbook->GetColor(colorIndex);

								runIndex++;

								tx += pGraphics->MeasureString(pstr, runlength, font);
								pstr += runlength;
							}

							charIndex += runlength;
						}
					}
					else
					{
						StringA* stringValue;// = m_formula.toString(col, row);//m_pSheet->m_rows[row]->m_cells[col]->m_stringValue;
						if (pCell->m_formula)
						{
							char buf[32];
							sprintf_s(buf, "%f", pCell->GetValue());

							stringValue = new StringA(string_copy(buf));
						}


						pGraphics->DrawString(stringValue, font, LDraw::PointF(0, 0), new LDraw::SolidBrush(color.m_rgb));
					}

					pGraphics->PopTransform();//oldTransform);
				}

				x += width;
			}

			y += height;
		}

		// TODO, RenderChildren
		if (m_pSheet->m_pDrawingGroup)
		{
			m_pSheet->m_pDrawingGroup->Render(pGraphics);
		}
	}

	pGraphics->SetSmoothingMode(oldSmoothingMode);
}

#if 0
void SpreadSheetControl::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			point.X -= 60;
			if (point.X >= 0)
			{
				double x = 0;

				int col;
				for (col = 0; col < m_pSheet->m_columns.size(); col++)
				{
					x += m_pSheet->m_columns[col]->GetPixelWidth();

					m_offset.X = x;

					if (fabs(point.X - x) < 4)
						break;
					if (point.X < x)
						break;
				}

				m_ncol = col;
			}

			point.Y -= 22;
			if (point.Y >= 0)
			{
				double y = 0;

				int row;
				for (row = 0; row < m_pSheet->m_rows.size(); row++)
				{
					y += m_pSheet->m_rows[row]->GetPixelHeight();

					m_offset.Y = y;

					if (fabs(point.Y - y) < 4)
						break;
					if (point.Y < y)
						break;
				}

				m_nrow = row;
			}

			if (point.X < 0 && point.Y < 0)
			{
			}
			else if (point.X < 0)
			{
			}
			else if (point.Y < 0)
			{
				m_dragging = 1;


			}
			else
			{
				Row* pRow = m_pSheet->m_rows[m_nrow];
				Cell* pCell = pRow->m_cells[m_ncol];

				ASSERT(0);
#if 0
				m_pFrame->m_edit->put_Text(ConvertA2S(pCell->m_stringValue));
#endif
			}
		}
		else if (*evt->get_type() == L"mouseup")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			if (m_dragging)
			{
				m_dragging = 0;
				ReleaseMouseCapture();
			}
		}
		else if (*evt->get_type() == L"mousemove")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			if (m_dragging)
			{
				double width = point.X - m_offset.X;
				if (width < 0)
					width = 0;

				m_pSheet->m_columns[m_ncol]->SetPixelWidth(width);

				Invalidate();
			}
		}
	}
}
#endif

}
