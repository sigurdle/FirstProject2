#include "stdafx.h"
#include "Browser.h"

#if WIN32
#include "../LPDF/LPDF.h"

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LPDF.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LPDF.lib")
#endif
#endif

namespace System
{
using namespace IO;

#if WIN32
namespace PDF
{

class TextObject
{
public:
	TextObject()
	{
		m_transform = LDraw::Matrix3f::GetIdentity();
		m_linetransform = LDraw::Matrix3f::GetIdentity();
	}

	__release<LDraw::Matrix3f> m_transform;
	__release<LDraw::Matrix3f> m_linetransform;
};

double GetNumberValue(CPDFCosObj* pObj)
{
	if (dynamic_cast<PDF::CPDFCosInteger*>(pObj))
		return dynamic_cast<PDF::CPDFCosInteger*>(pObj)->GetValue();
	else
		return dynamic_cast<PDF::CPDFCosReal*>(pObj)->GetValue();
}

}	// PDF

void RenderContent(PDF::CPDFCosDoc& doc, PDF::CPDFCosDict* pResources, LDraw::Commands* pCommands)
{
	PDF::CPDFCosDict* pFontDict = dynamic_cast<PDF::CPDFCosDict*>(pResources->CosDictGet(ASTR("Font")));
	PDF::CPDFCosDict* pXObjectDict = dynamic_cast<PDF::CPDFCosDict*>(pResources->CosDictGet(ASTR("XObject")));
	PDF::CPDFCosDict* pExtGStateDict = dynamic_cast<PDF::CPDFCosDict*>(pResources->CosDictGet(ASTR("ExtGState")));

	vector<PDF::CosObject> operands;

	std::fscanf(doc.m_fp, "\r\n ");

	__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;
	LDraw::Color strokeColor;
	LDraw::Color fillColor;
	LDraw::Font* font;
	__release<LDraw::Matrix3f> m_transform(LDraw::Matrix3f::GetIdentity());
	PDF::TextObject* pTextObject = NULL;

	int x_level = 0;

	while (!feof(doc.m_fp))
	{
		int c = std::fgetc(doc.m_fp);
		if (std::isalpha(c))	// operator
		{
			uint32 op;//[256];
			//char* p = op;
			//*p++ = c;
			op = c;
			//int n = 1;
			while (1)
			{
				c = std::fgetc(doc.m_fp);
				if (!std::isalpha(c) && c != '*')
				{
					std::ungetc(c, doc.m_fp);
					break;
				}

			//	*p++ = c;
				op <<= 8;
				op |= c;
			}
			//*p = 0;

			if (op == 'BT')	// begin text object
			{
				ASSERT(operands.GetSize() == 0);

				pTextObject = new PDF::TextObject;
			}
			else if (op == 'ET')	// end text object
			{
				ASSERT(operands.GetSize() == 0);

				ASSERT(pTextObject);
				delete pTextObject;
				pTextObject = NULL;
			}
			else if (op == 'Tf')	// font and font size
			{
				ASSERT(operands.GetSize() == 2);

				double size = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[1]);

#if 0
				PDF::CPDFCosName* fontName = dynamic_cast<PDF::CPDFCosName*>((PDF::CPDFCosObj*)operands[0]);
				PDF::CPDFCosDict* pFont = dynamic_cast<PDF::CPDFCosDict*>(pFontDict->CosDictGet(fontName->GetValue()));

				PDF::CPDFCosDict* pFontDescriptor = dynamic_cast<PDF::CPDFCosDict*>(pFont->CosDictGet("FontDescriptor"));
				if (pFontDescriptor)
				{
					PDF::CPDFCosStream* pFontFile2 = dynamic_cast<PDF::CPDFCosStream*>(pFontDescriptor->CosDictGet("FontFile2"));

					/*
					{
						ISequentialByteStream* pStream = pFontFile2->OpenStream();

						ISequentialByteStream* file = new ByteStreamWriter("c:/font_temp");
						file->AddRef();

						StreamCopy(file, pStream);

						file->Release();
					}
					{
						LType::FontFile* m_pFile = new LType::FontFile();

						m_pFile->m_fp = fopen("c:/font_temp", "rb");
						if (m_pFile->m_fp)
						{
							m_pFile->Init2();
							fclose(m_pFile->m_fp);
							m_pFile->m_fp = NULL;
						}
					}
					*/
				}
#endif

				font = new LDraw::Font(WSTR("Arial"), size);
			}
			else if (op == 'cm')	// current transformation matrix
			{
				ASSERT(operands.GetSize() == 6);
				double a = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0]);
				double b = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[1]);
				double c = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[2]);
				double d = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[3]);
				double e = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[4]);
				double f = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[5]);

				__release<LDraw::Matrix3f> transform = new LDraw::Matrix3f(a, b, c, d, e, f);
				m_transform = *transform * *m_transform;
			}
			else if (op == 'Tm')	// text matrix
			{
				ASSERT(operands.GetSize() == 6);
				double a = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0]);
				double b = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[1]);
				double c = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[2]);
				double d = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[3]);
				double e = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[4]);
				double f = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[5]);

				pTextObject->m_transform = new LDraw::Matrix3f(a, b, c, d, e, f);
				pTextObject->m_linetransform = pTextObject->m_transform;
			}
			else if (op == 'Tc')	// character spacing
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'Tw')	// word spacing
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'Ts')	// text rise
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'Tr')	// text rendering mode
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'Td')	// move to start of next line
			{
				ASSERT(operands.GetSize() == 2);
				// tx, ty

				double tx = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0]);
				double ty = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[1]);

				pTextObject->m_transform = pTextObject->m_linetransform;
				pTextObject->m_transform = *LDraw::Matrix3f::GetTranslate(tx, ty) * *pTextObject->m_transform;
				pTextObject->m_linetransform = pTextObject->m_transform;
			}
			else if (op == 'TD')	// move to start of next line
			{
				// TODO -ty TL

				ASSERT(operands.GetSize() == 2);
				// tx, ty

				double tx = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0]);
				double ty = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[1]);

				pTextObject->m_transform = pTextObject->m_linetransform;
				pTextObject->m_transform->Translate(tx, ty);
				pTextObject->m_linetransform = pTextObject->m_transform;
			}
			else if (op == 'T*')	// move to start of next line
			{
				ASSERT(operands.GetSize() == 0);

				double tx = 0;
				double ty = -font->GetSize();	// TODO leading in graphics state

				pTextObject->m_transform = pTextObject->m_linetransform;
				pTextObject->m_transform->Translate(tx, ty);
				pTextObject->m_linetransform = pTextObject->m_transform;
			}
			else if (op == 'Tj')	// show a text string
			{
				ASSERT(operands.GetSize() == 1);
				PDF::CPDFCosString* pString = dynamic_cast<PDF::CPDFCosString*>((PDF::CPDFCosObj*)operands[0]);

				TRACE("Tj %s\n", pString->GetValue()->c_str());

				pCommands->AddCommand(new LDraw::PushTransformCommand());

				pCommands->AddCommand(new LDraw::MultiplyTransformCommand(pTextObject->m_transform));
				pCommands->AddCommand(new LDraw::ScaleTransformCommand(1, -1));

				{
					LDraw::DrawStringAPointCommand* pCommand = new LDraw::DrawStringAPointCommand;

					ASSERT(0);
#if 0
					pCommand->m_brush = new LDraw::SolidBrush(fillColor);
					pCommand->m_string = pString->GetValue();
					pCommand->m_font = font;//LDraw::Font(L"Arial", 1);

					UI::Graphics graphics(new LDraw::GraphicsO());
					graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);
					double tx = graphics.MeasureString(pCommand->m_string->c_str(), pCommand->m_string->Length(), pCommand->m_font);

					if (pTextObject->m_transform->m_refcount > 1)
						pTextObject->m_transform = new LDraw::Matrix3f(pTextObject->m_transform->m_matrix);
					pTextObject->m_transform->Translate(tx, 0);

					pCommands->AddCommand(pCommand);
#endif
				}

			//	pCommands->AddCommand(new LDraw::SetTransformCommand(LDraw::Matrix3f::GetIdentity()));
				pCommands->AddCommand(new LDraw::PopTransformCommand());
			}
			else if (op == 'TJ')	// show an array of text strings
			{
				ASSERT(operands.GetSize() == 1);
				PDF::CPDFCosArray* pArray = dynamic_cast<PDF::CPDFCosArray*>((PDF::CPDFCosObj*)operands[0]);

				int nitems = pArray->GetLength();
				for (int i = 0; i < nitems; i++)
				{
					PDF::CPDFCosObj* pObj = pArray->GetItem(i);
					PDF::CPDFCosString* pString = dynamic_cast<PDF::CPDFCosString*>(pObj);
					if (pString)
					{
						StringA* string = pString->GetValue();

						pCommands->AddCommand(new LDraw::MultiplyTransformCommand(pTextObject->m_transform));
						pCommands->AddCommand(new LDraw::ScaleTransformCommand(1, -1));

						{
							ASSERT(0);
#if 0
							LDraw::DrawStringAPointCommand* pCommand = new LDraw::DrawStringAPointCommand;

							pCommand->m_brush = new LDraw::SolidBrush(fillColor);
							pCommand->m_string = pString->GetValue();
							pCommand->m_font = font;

							UI::Graphics graphics(new LDraw::GraphicsO());
							graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);
							double tx = graphics.MeasureString(pCommand->m_string->c_str(), pCommand->m_string->Length(), pCommand->m_font);

							pTextObject->m_transform->Translate(tx, 0);

							pCommands->AddCommand(pCommand);
#endif
						}

						pCommands->AddCommand(new LDraw::SetTransformCommand(LDraw::Matrix3f::GetIdentity()));

					}
					else
					{
						double number = PDF::GetNumberValue(pObj);

						pTextObject->m_transform->Translate(-number / 1000, 0);
						//double tx = graphics.MeasureString(pCommand->m_string.c_str(), pCommand->m_string.length(), &pCommand->m_font);
					}

					//TRACE("Tj %s\n", pString->GetValue().c_str());
				}
			}
			else if (op == 'SCN')	// stroking color
			{
				ASSERT(operands.GetSize() == 3);
			}
			else if (op == 'scn')	// non-stroking color
			{
				ASSERT(operands.GetSize() == 3);

				fillColor = LDraw::Color(	PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0])*255,
													PDF::GetNumberValue((PDF::CPDFCosObj*)operands[1])*255,
													PDF::GetNumberValue((PDF::CPDFCosObj*)operands[2])*255);
			}
			else if (op == 'g')	// set gray level for fill
			{
				ASSERT(operands.GetSize() == 1);
				fillColor = LDraw::Color(	PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0])*255,
													PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0])*255,
													PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0])*255);
			}
			else if (op == 'CS')	// color space for stroked color
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'cs')	// color space for non-stroking color
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'gs')	// graphics state
			{
				ASSERT(operands.GetSize() == 1);

				StringA* name = dynamic_cast<PDF::CPDFCosName*>((PDF::CPDFCosObj*)operands[0])->GetValue();
				PDF::CPDFCosObj* pGS = pExtGStateDict->CosDictGet(name);
			}
			else if (op == 'j')	// set line join
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'J')	// set line cap
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'M')	// set miter limit
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'w')	// set line width
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'd')	// set dash
			{
				ASSERT(operands.GetSize() == 2);

				// dashArray, dashPhase

			}
			else if (op == 'm')	// move to
			{
				ASSERT(operands.GetSize() == 2);
				TRACE("moveto\n");
			}
			else if (op == 'l')	// line to
			{
				ASSERT(operands.GetSize() == 2);
				TRACE("lineto\n");
			}
			else if (op == 'h')	// close subpath
			{
				ASSERT(operands.GetSize() == 0);
				TRACE("close\n");
			}
			else if (op == 're')	// rectangle
			{
				ASSERT(operands.GetSize() == 4);
				TRACE("rectangle\n");

				double x = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[0]);
				double y = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[1]);
				double width = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[2]);
				double height = PDF::GetNumberValue((PDF::CPDFCosObj*)operands[3]);

				path->AddRectangle(LDraw::RectF(x, y, width, height));
			}
			else if (op == 'f' ||	// fill path with nonzero winding rule
						op == 'F')	// for compatibility
			{
				ASSERT(operands.GetSize() == 0);
				TRACE("fill\n");

				LDraw::FillPathFCommand* pCommand = new LDraw::FillPathFCommand;

				pCommand->m_path = path;
				pCommand->m_brush = new LDraw::SolidBrush(fillColor);

				pCommands->AddCommand(pCommand);

				path = new LDraw::GraphicsPathF;//->Reset();
			}
			else if (op == 'f*')	// fill path with even-odd rule
			{
				// TODO even-odd

				ASSERT(operands.GetSize() == 0);
				TRACE("fill\n");

				LDraw::FillPathFCommand* pCommand = new LDraw::FillPathFCommand;

				pCommand->m_path = path;
				pCommand->m_brush = new LDraw::SolidBrush(fillColor);

				pCommands->AddCommand(pCommand);

				path = new LDraw::GraphicsPathF;
				//path->Reset();
			}
			else if (op == 'S')	// stroke the path
			{
				ASSERT(operands.GetSize() == 0);
				TRACE("stroke\n");
			}
			else if (op == 's')	// close and stroke the path
			{
				ASSERT(operands.GetSize() == 0);
				TRACE("close & stroke\n");
			}
			else if (op == 'i')	// set flatness tolerance
			{
				ASSERT(operands.GetSize() == 1);
			}
			else if (op == 'q')	// push graphics state
			{
				ASSERT(operands.GetSize() == 0);
				// TODO
				TRACE("q TODO\n");
			}
			else if (op == 'Q')	// pop graphics state
			{
				ASSERT(operands.GetSize() == 0);
				// TODO
				TRACE("Q TODO\n");
			}
			else if (op == 'W')	// Modify the current clipping path by intersecting it with the current path, using the nonzero winding number rule
			{
				ASSERT(operands.GetSize() == 0);
				// TODO
				// path.Reset(); ??
				TRACE("W TODO\n");
			}
			else if (op == 'W*')	// Modify the current clipping path by intersecting it with the current path, using the evenodd rule
			{
				ASSERT(operands.GetSize() == 0);
				// TODO
				// path.Reset(); ??
				TRACE("W* TODO\n");
			}
			else if (op == 'ri')	// set color rendering intent
			{
				ASSERT(operands.GetSize() == 1);
				TRACE("ri TODO\n");
			}
			else if (op == 'n')	// no-op painting path
			{
				ASSERT(operands.GetSize() == 0);
				//path->Reset();	// ??
				path = new LDraw::GraphicsPathF;	// ??
			}
			else if (op == 'Do')	// Draw XObject (external object)
			{
				ASSERT(operands.GetSize() == 1);

				PDF::CPDFCosName* xobjectName = dynamic_cast<PDF::CPDFCosName*>((PDF::CPDFCosObj*)operands[0]);
				if (xobjectName)
				{
					PDF::CPDFCosObj* pObj = pXObjectDict->CosDictGet(xobjectName->GetValue());
					PDF::CPDFCosStream* pStream = dynamic_cast<PDF::CPDFCosStream*>(pObj);
					if (pStream)
					{
						PDF::CPDFCosName* pSubtype = dynamic_cast<PDF::CPDFCosName*>(pStream->m_attributesDict->CosDictGet(ASTR("Subtype")));
						if (pSubtype && *pSubtype->GetValue() == "Image")
						{
							PDF::CPDFCosInteger* pWidth = dynamic_cast<PDF::CPDFCosInteger*>(pStream->m_attributesDict->CosDictGet(ASTR("Width")));
							PDF::CPDFCosInteger* pHeight = dynamic_cast<PDF::CPDFCosInteger*>(pStream->m_attributesDict->CosDictGet(ASTR("Height")));
							PDF::CPDFCosInteger* pBitsPerComponent = dynamic_cast<PDF::CPDFCosInteger*>(pStream->m_attributesDict->CosDictGet(ASTR("BitsPerComponent")));
							PDF::CPDFCosObj* pColorSpace = dynamic_cast<PDF::CPDFCosObj*>(pStream->m_attributesDict->CosDictGet(ASTR("ColorSpace")));

							uint8 (*palette)[3] = NULL;

							if (PDF::CPDFCosArray* p = dynamic_cast<PDF::CPDFCosArray*>(pColorSpace))
							{
								PDF::CPDFCosName* pName = dynamic_cast<PDF::CPDFCosName*>(p->GetItem(0));
								if (*pName->GetValue() == "Indexed")
								{
									PDF::CPDFCosInteger* pHival = dynamic_cast<PDF::CPDFCosInteger*>(p->GetItem(2));
									ASSERT(pHival);

									int hival = pHival->GetValue();

									palette = new uint8[hival+1][3];

									PDF::CPDFCosObj* pLookup = p->GetItem(3);
									if (PDF::CPDFCosString* pString = dynamic_cast<PDF::CPDFCosString*>(pLookup))
									{
										StringA* value = pString->GetValue();
										const char* p = value->c_str();
										ASSERT(value->Length() == (hival+1)*3);

										for (int i = 0; i <= hival; i++)
										{
											palette[i][0] = *p++;
											palette[i][1] = *p++;
											palette[i][2] = *p++;
										}
									}
									else if (PDF::CPDFCosStream* p = dynamic_cast<PDF::CPDFCosStream*>(pLookup))
									{
										ISequentialByteStream* pS = p->OpenStream();

										for (int i = 0; i <= hival; i++)
										{
											pS->Read(palette[i], 3);
										}
									}
								}
							}

							ISequentialByteStream* pS = pStream->OpenStream();

							long width = pWidth->GetValue();
							long height = pHeight->GetValue();

							LDraw::Bitmap* bitmap = new LDraw::Bitmap(width, height, LDraw::PixelFormat_t::RGB_24);

							LDraw::BitmapData bitmapData;
							bitmap->LockBits(NULL, LDraw::ImageLockModeWrite, &bitmapData);

							for (int y = 0; y < height; y++)
							{
								uint8* dest = (uint8*)bitmapData.Scan0 + bitmapData.Stride*y;

								for (int x = 0; x < width; x++)
								{
									uint8 c;
									pS->Read(&c, 1);

								//	dest[0] = 255;
									dest[0] = palette[c][2];
									dest[1] = palette[c][1];
									dest[2] = palette[c][0];

									dest += 3;
								}
							}

							bitmap->UnlockBits(&bitmapData);

							pCommands->AddCommand(new LDraw::PushTransformCommand());

							pCommands->AddCommand(new LDraw::MultiplyTransformCommand(m_transform));
							pCommands->AddCommand(new LDraw::ScaleTransformCommand(1, -1));

							pCommands->AddCommand(new LDraw::DrawImageRectCommand(bitmap, LDraw::RectF(0, -1, 1, 1)));

							pCommands->AddCommand(new LDraw::PopTransformCommand());
						//	pCommands->AddCommand(new LDraw::SetTransformCommand(LDraw::Matrix3f::GetIdentity()));

							/*
							PDF::CPDFCosObj* pObj = pStream->m_attributesDict->CosDictGet("Filter");
							if (PDF::CPDFCosName* pName = dynamic_cast<PDF::CPDFCosName*>(pObj))
							{
								//pName->GetValue();
							}
							else
							{
								ASSERT(0);
							}
							*/
						}
					}
				}
			}
			else if (op == 'BX')
			{
				ASSERT(operands.GetSize() == 0);
				x_level++;
			}
			else if (op == 'EX')
			{
				ASSERT(x_level > 0);
				ASSERT(operands.GetSize() == 0);
				x_level--;
			}
			else if (op == 'BMC')
			{
				ASSERT(operands.GetSize() == 1);
			//	x_level++;
			}
			else if (op == 'BDC')
			{
				ASSERT(operands.GetSize() == 2);
			//	x_level++;
			}
			else if (op == 'EMC')
			{
			//	ASSERT(x_level > 0);
				ASSERT(operands.GetSize() == 0);
			//	x_level--;
			}
			else
			{
				TRACE("%4.4s\n", (char*)&op);//.c_str());
				//ASSERT(0);
			}

			operands.RemoveAll();
		}
		else
		{
			std::ungetc(c, doc.m_fp);

			PDF::CosObject obj = doc.ReadObject2(doc.m_fp);

			operands.Add(obj);
		}

		std::fscanf(doc.m_fp, "\r\n ");
	}
}

#endif

}
