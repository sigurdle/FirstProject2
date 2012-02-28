#include "stdafx.h"
#include "Browser.h"
#include "msodrawing.h"
#include "SpreadSheet.h"

#include "../LFC/ZLIBDecoder.h"

#include "../LJPEG/JFIF.h"

#include "wmf.h"

namespace System
{

extern float pixelsPerInch;

using namespace IO;

namespace MSODrawing
{

void Shape::OnRender(UI::Graphics* pGraphics)
{
	if (m_path != NULL)
	{
	//	pGraphics->DrawPath(&LDraw::Pen(m_strokeColor, m_strokeWidth), &m_path);
		pGraphics->FillPath(new LDraw::SolidBrush(m_pSheet->m_pWorkbook->GetColor(m_fillColor).m_rgb), m_path);
	}

	if (m_pText)
	{
		double tx = 0;

		int charIndex = 0;
		StringW* str = m_pText->m_str;
		const WCHAR* pstr = str->c_str();

		Font* pFont;

		int colorIndex;
		PaletteEntry color;

		int runIndex = 0;
		while (charIndex < str->Length())
		{
			pFont = m_pSheet->m_pWorkbook->m_fonts[m_pText->m_textRuns[runIndex].fontIndex];
			colorIndex = pFont->m_colorIndex;
			color = m_pSheet->m_pWorkbook->GetColor(colorIndex);

			int runlength;

			runlength = m_pText->m_textRuns[runIndex+1].charIndex - charIndex;	// Up to the next run

			LDraw::Font* font = pFont->GetFont();
			float ascent = font->GetCellAscent();
			float size = font->GetSize();

			float ty = 0;

			/*
			if (pXF->m_vertAlign == Excel::VA_Bottom)
				ty = rowBaselineY - ascent;
			else if (pXF->m_vertAlign == Excel::VA_Top)
				ty = 0;
			else if (pXF->m_vertAlign == Excel::VA_Center)
				ty = (height)/2 + pCell->m_maxascent/2 - ascent;
			else
				ASSERT(0);
				*/

			for (int i = 0; i < runlength; i++)
			{
				if (pstr[i] == '\n')
				{
					//ASSERT(pstr[++i] == '\n');
					ty += 16;
					tx = 0;
				}
				else
				{
					pGraphics->DrawString(&pstr[i], 1, font, LDraw::PointF(tx, ty), new LDraw::SolidBrush(color.m_rgb));
					tx += pGraphics->MeasureString(&pstr[i], 1, font);
				}
			}

			//if (runIndex < pContent->m_textRuns.size())
			{

				runIndex++;

			//	tx += pGraphics->MeasureString(pstr, runlength, &font);
				pstr += runlength;
			}

			charIndex += runlength;
		}

	}
}

void DrawingLoader::ReadOPT(ISequentialByteStream* pStream, const MSOFBH& record, PropertyList* options)
{
	TRACE("msofbtOPT\n");

	LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	ULONG nentries = record.inst;
	ULONG bloboffset = 0;

	FOPTE* opte = new FOPTE[nentries];

	for (int i = 0; i < nentries; i++)
	{
		pStream->Read(&opte[i], sizeof(FOPTE));
		TRACE("%d =", opte[i].key.pid);

		PropertyEntry* pEntry = new PropertyEntry;
		pEntry->value = opte[i].op;

		if (opte[i].key.fComplex)
		{
			TRACE("complex length: %d\n", opte[i].op);

			pEntry->offset = bloboffset;

			bloboffset += 6 + opte[i].op;
		}
		else if (opte[i].key.fBid)
		{
			TRACE("BLIP id\n");
		}
		else
		{
			TRACE("%d\n", opte[i].op);
		}

		options->m_entries[opte[i].key.pid] = pEntry;

		ULONG cur = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		ASSERT(cur - start <= record.cbLength);
	}

	ULONG cur = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	options->m_blobsize = record.cbLength - (cur-start);
	if (options->m_blobsize)
	{
		options->m_blobdata = new uint8[options->m_blobsize];
		pStream->Read(options->m_blobdata, options->m_blobsize);
	}

	delete[] opte;
}

void ReadTxo(StringEntry* pTXO, ISequentialByteStream* pStream)
{
	ASSERT(0);
#if 0

	Excel::RECORDHEADER record;
	ULONG nRead = pStream->Read(&record, sizeof(record));

	if (record.id != Excel::ID_TXO)
	{
		ASSERT(0);
		THROW(-1);
	}

	TRACE("TXO %d\n", record.size);

	uint16 grbit;
	pStream->Read(&grbit, 2);

	uint16 rot;
	pStream->Read(&rot, 2);

	uint8 reserved[6];
	pStream->Read(reserved, 6);

	uint16 cchText;
	pStream->Read(&cchText, 2);

	uint16 cbRuns;
	pStream->Read(&cbRuns, 2);

	pStream->Read(reserved, 4);

//	pStream->Seek(pos + record.size, System::IO::STREAM_SEEK_SET);

	pStream->Read(&record, sizeof record);

	uint8 flags;
	pStream->Read(&flags, 1);
	if (flags & 1)
	{
		for (int i = 0; i < cchText; i++)
		{
			WCHAR c;
			pStream->Read(&c, 2);

			pTXO->m_str += c;
		}
	}
	else
	{
		for (int i = 0; i < cchText; i++)
		{
			char c;
			pStream->Read(&c, 1);

			pTXO->m_str += c;
		}
	}

	pStream->Read(&record, sizeof record);

//	ULONG	pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	cbRuns >>= 3;

	for (int i = 0; i < cbRuns; i++)
	{
		TextRun run;
		pStream->Read(&run.charIndex, 2);

		uint16 ifnt;
		pStream->Read(&ifnt, 2);
		ASSERT(ifnt != 4);
		if (ifnt > 4)	// Skip the fourth index
			ifnt--;

		run.fontIndex = ifnt;

		pTXO->m_textRuns.Add(run);

		uint32 reserved;
		pStream->Read(&reserved, 4);
	}
#endif
}

UI::UIElement* DrawingLoader::SpContainer(ISequentialByteStream* pStream, ULONG length)
{
	LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	int shapeType = -1;
	FSP fsp;
	ClientAnchor* pClientAnchor = NULL;
	PropertyList* options = NULL;
	StringEntry* pTXO = NULL;

	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < start+length)
	{
		MSOFBH record;
		if (pStream->Read(&record, sizeof record) != sizeof record)
		{
			ASSERT(0);
		}

		ULONG pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.fbt == msofbtSpgr)	// Present if group
		{
			TRACE("msofbtSpgr\n");

			FSPGR fspgr;
			pStream->Read(&fspgr, sizeof fspgr);
		}
		else if (record.fbt == msofbtSp)	// shape type
		{
			pStream->Read(&fsp, sizeof(fsp));

			TRACE("msofbtSp type: %d, spid: %d, flags: 0x%x\n", record.inst, fsp.spid, fsp.grfPersistent);

			shapeType = record.inst;

			switch (shapeType)
			{
			case msosptMin:
				{
					TRACE("Min\n");
				}
				break;

			case msosptLine:
				{
					TRACE("Line\n");
				}
				break;

			case msosptEllipse:
				{
					TRACE("Line\n");
				}
				break;

			case msosptPictureFrame:
				{
					TRACE("PictureFrame\n");
				}
				break;

			case msosptTextBox:
				{
					TRACE("TextBox\n");
				}
				break;

			default:
				ASSERT(0);
			}
		}
		else if (record.fbt == msofbtChildAnchor)	// location of the shape (relative to parent)
		{
			TRACE("msofbtChildAnchor size(%d)\n", record.cbLength);
			LDraw::BBoxi bbox;

			pStream->Read(&bbox, sizeof bbox);
		}
		else if (record.fbt == msofbtClientAnchor)	// location of the shape (in a host specific format)
		{
			TRACE("msofbtClientAnchor size(%d)\n", record.cbLength);

			if (pClientAnchor)
			{
				TRACE("Duplicate Client Anchor record\n");
				delete pClientAnchor;
			}

			pClientAnchor = new ClientAnchor;

			pStream->Read(pClientAnchor, sizeof ClientAnchor);
		}
		else if (record.fbt == msofbtClientData)
		{
			TRACE("msofbtClientData size(%d)\n", record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);

			/*
			RECORDHEADER record;
			pStream->Read(&record, sizeof(record));

		case ID_OBJ:
			{
				TRACE("OBJ %d\n", record.size);
				
				while (1)
				{
					RECORDHEADER record;
					pStream->Read(&record, sizeof(record));
					
					ULONG pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
					
					if (record.id == 0)
						break;
					
					if (record.id == 0x15)	// ftCmo
					{
						uint16 ot;
						pStream->Read(&ot, 2);
					}
					
					pStream->Seek(pos + record.size, System::IO::STREAM_SEEK_SET);
				}
			}
			break;
			*/

		}
		else if (record.fbt == msofbtTextbox)
		{
			TRACE("msofbtTextbox size(%d)\n", record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);

		}
		else if (record.fbt == msofbtClientTextbox)
		{
			TRACE("msofbtClientTextbox size(%d)\n", record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);

			ULONG pos2 = m_posmap[pos];
			m_pContainerStream->Seek(pos2, System::IO::STREAM_SEEK_SET);

			pTXO = new StringEntry;
			ReadTxo(pTXO, m_pContainerStream);
		}
		else if (record.fbt == msofbtOPT)
		{
			options = new PropertyList;
			ReadOPT(pStream, record, options);
		}
		else
		{
			TRACE("0x%x\n", record.fbt);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);
		}

		LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (cur != pos+record.cbLength)
		{
			ASSERT(0);
		}

		pStream->Seek(pos + record.cbLength, System::IO::STREAM_SEEK_SET);
	}

	TopShape* pVisual;

	if (shapeType == msosptPictureFrame)
	{
		PictureFrame* pPicture = new PictureFrame;
		pVisual = pPicture;

		ULONG pib = options->m_entries[Prop_pib]->value;

		ASSERT(pib > 0);

		m_blips->m_items.SetSize(MAX(m_blips->m_items.GetSize(), pib));
		pPicture->m_pBlip = m_blips->m_items[pib-1];
		if (pPicture->m_pBlip == NULL)
		{
			pPicture->m_pBlip = new Blip;
			m_blips->m_items[pib-1] = pPicture->m_pBlip;
		}
	}
	else
	{
		Shape* pShape = new Shape;
		pVisual = pShape;

		if (options)
		{
			PropertyEntry* pText = options->m_entries[Prop_lTxid];
			if (pText)
			{
				pShape->m_pText = pTXO;
			}

			long lineWidthEMU;
			PropertyEntry* pLineWidth = options->m_entries[Prop_lineWidth];
			if (pLineWidth)
				lineWidthEMU = pLineWidth->value;
			else
				lineWidthEMU = 9525;

			pShape->m_strokeWidth = (lineWidthEMU / 12700.0f) * (pixelsPerInch / 72.0f);

			{
				COLORREF color = options->m_entries[Prop_lineColor]->value;
				//pShape->m_strokeColor = LDraw::Color::FromCOLORREF(color);
			}

			{
				PropertyEntry* p = options->m_entries[Prop_fillColor];
				if (p)
				{
					pShape->m_fillColor = (p->value & 0xFF) - 8;
				}
			}

			PropertyEntry* pVertices = options->m_entries[Prop_pVertices];
			if (pVertices)
			{
				uint16* p = (uint16*)(options->m_blobdata + pVertices->offset);
				uint16 numElements = *p++;
				uint16 allocedElements = *p++;
				short elementSize = *p++;

				//uint16 numElements = pVertices->value / 4;

				short* plong = (short*)p;

				PropertyEntry* pSegmentInfo = options->m_entries[Prop_pSegmentInfo];
			//	uint8* segment;
				if (pSegmentInfo)
				{
					uint16* p = (uint16*)(options->m_blobdata + pSegmentInfo->offset);
					uint16 numElements = *p++;
					uint16 allocedElements = *p++;
					uint16 elementSize = *p++;
					//uint16* p = (uint8*)p;

					for (int i = 0; i < numElements; i++)
					{
						uint16 nTmp = *p++;

						int nCount = ( nTmp & 0xfff );

						switch (nTmp >> 12)
						{
							case 0x0://nCommand = EnhancedCustomShapeSegmentCommand::LINETO; if ( !nCount ) nCount = 1; break;
								{
									short x = *plong++;
									short y = *plong++;

									pShape->m_path->AddLine(x, y);
								}
								break;

							case 0x2:
								{
									short x = *plong++;
									short y = *plong++;
									short x2 = *plong++;
									short y2 = *plong++;
									short x3 = *plong++;
									short y3 = *plong++;
									pShape->m_path->AddBezier(x, y, x2, y2, x3, y3);
								}
								break;

							case 0x4:
								{
									short x = *plong++;
									short y = *plong++;

									pShape->m_path->AddMove(x, y);
								}
								break;

							case 0x8: //nCommand = EnhancedCustomShapeSegmentCommand::ENDSUBPATH; nCount = 0; break;
								{
								}
								break;

							case 0xa:
							case 0xb:
								{
									/*
									switch ( ( nTmp >> 8 ) & 0xf )
									{
										case 0x0:
										{
										//	nCommand = EnhancedCustomShapeSegmentCommand::LINETO;
										//	if ( !nCount )
										//		nCount = 1;

											short x = *plong++;
											short y = *plong++;

											pShape->m_path.AddLine(x, y);
										}
										break;

										default:
											ASSERT(0);
									}
									*/
								}
								break;

							default:
								ASSERT(0);
						}
		

						/*
						if (segment[1] == 0x40)	// polygon start
						{
							segment += 2;
						}
						else if (segment[1] == 0xad)
						{
							short x = *plong++;
							short y = *plong++;

							pShape->m_path.AddMove(x, y);
							segment += 2;
						}
						else if (segment[1] == 0x20)
						{
							short x = *plong++;
							short y = *plong++;
							short x2 = *plong++;
							short y2 = *plong++;
							short x3 = *plong++;
							short y3 = *plong++;
							pShape->m_path.AddBezier(x, y, x2, y2, x3, y3);
							segment += 2;
							i += 2;
						}
						else
						{
							short x = *plong++;
							short y = *plong++;

							pShape->m_path.AddLine(x, y);
						}
						*/
					}
				}
				else
				{
					for (int i = 0; i < numElements; i++)
					{
						short x = *plong++;
						short y = *plong++;

						if (i == 0)
							pShape->m_path->AddMove(x, y);
						else
							pShape->m_path->AddLine(x, y);
					}
				}
			}

			delete options;
		}
	}

	if (pClientAnchor)
	{
		TopShape* pTopShape = pVisual;
		pTopShape->col1 = pClientAnchor->col1;
		pTopShape->row1 = pClientAnchor->row1;

		pTopShape->col2 = pClientAnchor->col2;
		pTopShape->row2 = pClientAnchor->row2;

		pTopShape->dx1 = pClientAnchor->dx1 / 1024.0;
		pTopShape->dy1 = pClientAnchor->dy1 / 256.0;

		pTopShape->dx2 = pClientAnchor->dx2 / 1024.0;
		pTopShape->dy2 = pClientAnchor->dy2 / 256.0;

		//pTopShape->put_VisualTree(pVisual);

		delete pClientAnchor;

		return pTopShape;
	}

	return NULL;
}

void DrawingLoader::SpgrContainer(ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual)
{
	LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < start+length)
	{
		MSOFBH record;
		if (pStream->Read(&record, sizeof record) != sizeof record)
		{
			ASSERT(0);
		}

		ULONG pos = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.fbt == msofbtSpContainer)
		{
			TRACE("msofbtSpContainer size(%d)\n", record.cbLength);
			UI::UIElement* pShape = SpContainer(pStream, record.cbLength);

			if (pVisual && pShape)
			{
				if (false)
				{
					UI::EditTransform* pTransformer = new UI::EditTransform;

					pTransformer->set_Content(pShape);

					ASSERT(0);
#if 0
					pVisual->AddRChild(pTransformer);
#endif
				}
				else
				{
					ASSERT(0);
#if 0
					pVisual->AddRChild(pShape);
#endif
				}
			}
		}
		else
		{
			TRACE("0x%x, size: %d\n", record.fbt, record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);
		}

		LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur != pos+record.cbLength)
		{
//			THROW(-1);
			ASSERT(0);
		}

		pStream->Seek(pos + record.cbLength, System::IO::STREAM_SEEK_SET);
	}
}

void DrawingLoader::DgContainer(ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual)
{
	LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < start+length)
	{
		MSOFBH record;
		if (pStream->Read(&record, sizeof record) != sizeof record)
		{
			ASSERT(0);
		}

		LONGLONG pos = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.fbt == msofbtDg)
		{
			TRACE("msofbtDg size(%d)\n", record.cbLength);

			FDG fdg;
			pStream->Read(&fdg, sizeof(fdg));
		}
		else if (record.fbt == msofbtColorScheme)
		{
			TRACE("msofbtColorScheme\n");
		}
		else if (record.fbt == msofbtSpgrContainer)
		{
			TRACE("msofbtSpgrContainer size(%d)\n", record.cbLength);
			SpgrContainer(pStream, record.cbLength, pVisual);
		}
		else
		{
			TRACE("0x%x, size: %d\n", record.fbt, record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);
		}

		LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur != pos+record.cbLength)
		{
			ASSERT(0);
		}

		pStream->Seek(pos + record.cbLength, System::IO::STREAM_SEEK_SET);
	}
}


void DrawingLoader::BSE(ISequentialByteStream* pStream, Blip* pBlip, int blip_instance, ULONG length)
{
	LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	ULONG n = 0;

	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < start+length)
	{
		MSOFBH record;
		if (pStream->Read(&record, sizeof record) != sizeof record)
		{
			ASSERT(0);
		}

		LONGLONG pos = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.fbt >= 0xf018 && record.fbt <= 0xf117)
		{
			TRACE("msofbtBlip size(%d)\n", record.cbLength);

			int blipType = record.fbt - 0xf018;
			int blip_signature = record.inst;

			/* The secondary, or data, UID - should always be set. */
			uint8  m_rgbUid[16];
			pStream->Read(m_rgbUid, 16);
			/* The primary UID - this defaults to 0, in which case the primary ID is
				that of the internal data. NOTE!: The primary UID is only saved to disk
				if (blip_instance ^ blip_signature == 1). Blip_instance is MSOFBH.inst and 
				blip_signature is one of the values defined in MSOBI */
			uint8 m_rgbUidPrimary[16]; // optional based on the above check
			if ((blip_instance ^ blip_signature) == 1)
			{
				pStream->Read(m_rgbUidPrimary, 16);
			}

			switch (blipType)
			{
			case msoblipWMF:
				{
					METAFILEHEADER hdr;
					pStream->Read(&hdr, sizeof hdr);

					if (hdr.m_fFilter != msofilterNone)
					{
						TRACE("Unsupported filter found in metafile blip %d\n", hdr.m_fFilter);
						ASSERT(0);
						THROW(-1);
					}

					if (hdr.m_fCompression == msocompressionDeflate)
					{
						ZLIBDecoder* stream = new ZLIBDecoder(pStream, hdr.m_cbSave);
					//	stream->AddRef();

					//	stream->start();
					//	stream->start_block();

						wmf::MetafileLoader wmfloader;

						pBlip->m_originalSize.Width = hdr.m_rcBounds.GetWidth() / 20.0;// * (pixelsPerInch / 72);
						pBlip->m_originalSize.Height = hdr.m_rcBounds.GetHeight() / 20.0;// * (pixelsPerInch / 72);

						wmfloader.SetViewportOrg(hdr.m_rcBounds.left / 20.0, hdr.m_rcBounds.top / 20.0);
						wmfloader.SetViewportExt(hdr.m_rcBounds.GetWidth() / 20.0, hdr.m_rcBounds.GetHeight() / 20.0);

						LDraw::TranslateTransformCommand* pCmd = new LDraw::TranslateTransformCommand;
						pCmd->m_dx = -hdr.m_rcBounds.left / 20.0;
						pCmd->m_dy = -hdr.m_rcBounds.top / 20.0;

						pBlip->m_commands->AddCommand(pCmd);

						wmfloader.pCommands = pBlip->m_commands;

						wmfloader.Load(stream);

					//	LDraw::PointF pt = wmfloader.LPToDP(0, 0);

					//	stream->Release();
					}
					else
					{
						TRACE("Unsupported compression found in metafile blip %d\n", hdr.m_fCompression);
						ASSERT(0);
						THROW(-1);
					}
				}
				break;

			case msoblipJPEG:
				{
					uint8 tag;
					pStream->Read(&tag, 1);

					Imaging::JPEGDecoder jpegFormat(pStream);

					if (jpegFormat.Read() == 0)
					{
						int height = jpegFormat.GetHeight();
						LDraw::Bitmap* bitmap = new LDraw::Bitmap(jpegFormat.GetWidth(), height, LDraw::PixelFormat_t::RGB_24);

						jpegFormat.StartScans();

						LDraw::BitmapData bitmapdata;
						bitmap->LockBits(NULL, LDraw::ImageLockModeWrite, &bitmapdata);

						for (int y = 0; y < height; y++)
						{
							uint8* dest = bitmapdata.Scan0 + bitmapdata.Stride*y;

							jpegFormat.NextScanline();
							jpegFormat.CopyScanline(dest+2, dest+1, dest+0, 3);
						}

						bitmap->UnlockBits(&bitmapdata);

						pBlip->m_bitmap = bitmap;
					}
					else
						ASSERT(0);
				}
				break;

			default:
				TRACE("Unknown blip type %d\n", blipType);
				ASSERT(0);
				THROW(-1);
			}
		}
		else
		{
			TRACE("0x%x, size: %d\n", record.fbt, record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);
		}

		LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur > pos+record.cbLength)
		{
			ASSERT(0);
		}

		pStream->Seek(pos + record.cbLength, System::IO::STREAM_SEEK_SET);
	}
}

void DrawingLoader::BstoreContainer(ISequentialByteStream* pStream, ULONG length, ULONG count)
{
	LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	ULONG n = 0;

	m_blips->m_items.SetSize(count);

	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < start+length)
	//while (n < count)
	{
		if (n == count)
		{
			TRACE("Mismatch between count(%d) of blips and the size of the blip store\n", count);
		//	THROW(-1);
		//	ASSERT(0);
		}

		MSOFBH record;
		if (pStream->Read(&record, sizeof record) != sizeof record)
		{
			ASSERT(0);
		}

		LONGLONG pos = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.fbt == msofbtBSE)
		{
			TRACE("msofbtBSE size(%d)\n", record.cbLength);

			Blip* pBlip = m_blips->m_items[n];
			if (pBlip == NULL)
			{
				pBlip = new Blip;
				m_blips->m_items[n] = pBlip;
			}

			FBSE fbse;
			pStream->Read(&fbse, sizeof fbse);

			if (fbse.cbName)
			{
				WCHAR name[256];
				pStream->Read(name, fbse.cbName*2);
				name[255] = 0;
			}

			BSE(pStream, pBlip, record.inst, record.cbLength - sizeof fbse);
#if 0
			int blip_instance = record.inst;
		
			MSOFBH record2;
			pStream->Read(&record2, sizeof(record2));

			if (record2.fbt >= 0xf018 && record2.fbt <= 0xf117)
			{
				TRACE("msofbtBlip size(%d)\n", record2.cbLength);

				int blipType = record2.fbt - 0xf018;
				int blip_signature = record2.inst;

				/* The secondary, or data, UID - should always be set. */
				uint8  m_rgbUid[16];
				pStream->Read(m_rgbUid, 16);
				/* The primary UID - this defaults to 0, in which case the primary ID is
					that of the internal data. NOTE!: The primary UID is only saved to disk
					if (blip_instance ^ blip_signature == 1). Blip_instance is MSOFBH.inst and 
					blip_signature is one of the values defined in MSOBI */
				uint8 m_rgbUidPrimary[16]; // optional based on the above check
				if ((blip_instance ^ blip_signature) == 1)
				{
					pStream->Read(m_rgbUidPrimary, 16);
				}

				switch (blipType)
				{
				case msoblipJPEG:
					{
						uint8 tag;
						pStream->Read(&tag, 1);

						LMedia::JPEGDecoder jpegFormat(pStream);

						if (jpegFormat.Read() == 0)
						{
							int height = jpegFormat.GetHeight();
							LDraw::Bitmap bitmap(jpegFormat.GetWidth(), height, RGB_24);

							jpegFormat.StartScans();

							LDraw::BitmapData bitmapdata;
							bitmap.LockBits(NULL, LDraw::ImageLockModeWrite, &bitmapdata);

							for (int y = 0; y < height; y++)
							{
								jpegFormat.NextScanline();
							}

							bitmap.UnlockBits(&bitmapdata);
						}
						else
							ASSERT(0);
					}
					break;

				default:
					TRACE("Unknown blip type %d\n", blipType);
					ASSERT(0);
					THROW(-1);
				}
			}
			else
			{
				TRACE("Expected a blip type record\n");
				ASSERT(0);
				THROW(-1);
			}
#endif

			n++;
		}
		else
		{
			TRACE("0x%x, size: %d\n", record.fbt, record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);
		}

		LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur != pos+record.cbLength)
		{
			ASSERT(0);
		}

		pStream->Seek(pos + record.cbLength, System::IO::STREAM_SEEK_SET);
	}
}

void DrawingLoader::DggContainer(ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual)
{
	LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < start+length)
	{
		MSOFBH record;
		if (pStream->Read(&record, sizeof record) != sizeof record)
		{
			ASSERT(0);
		}

		LONGLONG pos = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.fbt == msofbtDgg)
		{
			TRACE("msofbtDgg size(%d)\n", record.cbLength);

			FDGG fdgg;
			pStream->Read(&fdgg, sizeof fdgg);

			for (int i = 1; i < fdgg.cidcl; i++)
			{
				FIDCL idcl;
				pStream->Read(&idcl, sizeof idcl);
			}
		}
		else if (record.fbt == msofbtOPT)
		{
			PropertyList* options = new PropertyList;
			ReadOPT(pStream, record, options);
		}
		else if (record.fbt == msofbtBstoreContainer)
		{
			TRACE("msofbtBstoreContainer size(%d)\n", record.cbLength);
			BstoreContainer(pStream, record.cbLength, record.inst);
		}
		else
		{
			TRACE("0x%x, size: %d\n", record.fbt, record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);
		}

		LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur != pos+record.cbLength)
		{
			ASSERT(0);
		}

		pStream->Seek(pos + record.cbLength, System::IO::STREAM_SEEK_SET);
	}
}

void DrawingLoader::Drawing(ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual)
{
	LONGLONG start = (ULONG)pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

	while (pStream->Seek(0, System::IO::STREAM_SEEK_CUR) < start+length)
	{
		MSOFBH record;
		pStream->Read(&record, sizeof(record));

		LONGLONG pos = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

		if (record.fbt == msofbtDgContainer)
		{
			TRACE("msofbtDgContainer size(%d)\n", record.cbLength);
			DgContainer(pStream, record.cbLength, pVisual);
		}
		else if (record.fbt == msofbtDggContainer)
		{
			TRACE("msofbtDggContainer size(%d)\n", record.cbLength);
			DggContainer(pStream, record.cbLength, pVisual);
		}
		else if (record.fbt == msofbtColorScheme)
		{
			TRACE("msofbtColorScheme size(%d)\n", record.cbLength);
			ASSERT(0);
		}
		else
		{
			TRACE("0x%x, size: %d\n", record.fbt, record.cbLength);
			pStream->Seek(record.cbLength, System::IO::STREAM_SEEK_CUR);
		}

		LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur != pos+record.cbLength)
		{
			ASSERT(0);
		}

		pStream->Seek(pos + record.cbLength, System::IO::STREAM_SEEK_SET);
	}
}

}	// MSODrawing
}	// System
