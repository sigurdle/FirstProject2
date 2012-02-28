#include "stdafx.h"
#include "wmf.h"

#include "../include/windows_header.h"

namespace System
{
namespace wmf
{

using namespace System::IO;

/*
OBJ_PEN Returns the current selected pen. 
OBJ_BRUSH Returns the current selected brush. 
OBJ_PAL Returns the current selected palette. 
OBJ_FONT Returns the current selected font. 
OBJ_BITMAP 
*/


struct DIBBITBLTRECORD
{
//    uint32   Size;             /* Total size of the record in WORDs */
//    WORD    Function;         /* Function number (0x0940) */
    uint16    RasterOp;         /* High-order word for the raster operation */
    uint16    YSrcOrigin;       /* Y-coordinate of the source origin */
    uint16    XSrcOrigin;       /* X-coordinate of the source origin */
    uint16    YDest;            /* Destination width */
    uint16    XDest;            /* Destination height */
    uint16    YDestOrigin;      /* Y-coordinate of the destination origin */
    uint16    XDestOrigin;      /* X-coordinate of the destination origin */
};

struct DIBSTRETCHBLTRECORD_16
{
//    uint32   Size;             /* Total size of the record in WORDs */
//    WORD    Function;         /* Function number (0x0940) */
    uint16    RasterOp;
    uint16    SrcHeight;
    uint16    SrcWidth;
    uint16    SrcY;
    uint16    SrcX;
    uint16    DestHeight;
    uint16    DestWidth;
    uint16    DestY;
    uint16    DestX;
} ;

struct emf_STRETCHDIBITS
{
	LDraw::BBoxi rclBounds; 
	int32  xDest; 
	int32  yDest; 
	int32  xSrc; 
	int32  ySrc; 
	int32  cxSrc; 
	int32  cySrc;
	uint32 offBmiSrc;
	uint32 cbBmiSrc; 
	uint32 offBitsSrc; 
	uint32 cbBitsSrc; 
	uint32 iUsageSrc; 
	uint32 dwRop; 
	int32  cxDest; 
	int32  cyDest; 
};

#if 0
struct DIBBITMAP32
{
    uint32   Width;            /* Width of bitmap in pixels */
    uint32   Height;           /* Height of bitmap in scan lines */
    uint32   BytesPerLine;     /* Number of bytes in each scan line */
    WORD    NumColorPlanes;   /* Number of color planes in the bitmap */
    WORD    BitsPerPixel;     /* Number of bits in each pixel */
    uint32   Compression;      /* Compression type */
    uint32   SizeImage;        /* Size of bitmap in bytes */
    LONG    XPelsPerMeter;    /* Width of image in pixels per meter */
    LONG    YPelsPerMeter;    /* Height of image in pixels per meter */
    uint32   ClrUsed;          /* Number of colors used */
    uint32   ClrImportant;     /* Number of important colors */
 //   RGBQUAD Bitmap[];         /* Bitmap data */
};

struct DIBBITMAP
{
    uint32   Width;            /* Width of bitmap in pixels */
    uint32   Height;           /* Height of bitmap in scan lines */
    uint32   BytesPerLine;     /* Number of bytes in each scan line */
    WORD    NumColorPlanes;   /* Number of color planes in the bitmap */
    WORD    BitsPerPixel;     /* Number of bits in each pixel */
    uint32   Compression;      /* Compression type */
    uint32   SizeImage;        /* Size of bitmap in bytes */
    long    XPelsPerMeter;    /* Width of image in pixels per meter */
    long    YPelsPerMeter;    /* Height of image in pixels per meter */
    WORD   ClrUsed;          /* Number of colors used */
    WORD   ClrImportant;     /* Number of important colors */
 //   RGBQUAD Bitmap[];         /* Bitmap data */
};
#endif

MetafileLoader::MetafileLoader()
{
	// ???
	m_pCurPen = NULL;
	m_pCurBrush = NULL;
	m_pCurFont = NULL;

	m_textColor = 0;
	m_bBeginPath = false;
}

LDraw::PointF MetafileLoader::LPToDP(int Lx, int Ly)
{
	/*
	GetWindowOrgEx(hDC, &WO);

	GetWindowExtEx(hDC, &WE);

	GetViewportOrgEx(hDC, &VO);

	GetViewportExtEx(hDC, &VE);
	*/

	LDraw::PointF pt;

	pt.X = ((double)(Lx - WO.X) * (double)VE.Width / (double)WE.Width) + VO.X;
	pt.Y = ((double)(Ly - WO.Y) * (double)VE.Height / (double)WE.Height) + VO.Y;

	return pt;

	/*
	POINT pt;
	pt.x = Lx;
	pt.y = Ly;
	LPtoDP(hDC, &pt, 1);

	*px = pt.x;
	*py = pt.y;
	*/
}

void MetafileLoader::Load(ISequentialByteStream* pStream)
{
	uint32 dword;
	pStream->Read(&dword, 4);

	if (dword == 0x9AC6CDD7)	// Aldus placeable metafile
	{
		PLACEABLEMETAFILEHEADER pwmf;
		pwmf.Key = dword;
		pStream->Read(((uint8*)&pwmf)+4, sizeof pwmf - 4);

		m_rect.X = pwmf.Left;// / 20.0;
		m_rect.Y = pwmf.Top;// / 20.0;
		m_rect.Width = (pwmf.Right - pwmf.Left);// / 20.0;
		m_rect.Height = (pwmf.Bottom - pwmf.Top);// / 20.0;

		// ??
		SetViewportOrg(m_rect.X, m_rect.Y);
		SetViewportExt(m_rect.Width, m_rect.Height);

		pStream->Read(&dword, 4);
	}

	WMFHEADER wmfheader;
	*(uint32*)&wmfheader = dword;

	if ((wmfheader.FileType == 0 || wmfheader.FileType == 1) && wmfheader.HeaderSize == 9)
	{
		pCommands = new LDraw::Commands;

		pStream->Read(((uint8*)&wmfheader)+4, sizeof wmfheader - 4);

		m_numOfObjects = wmfheader.NumOfObjects;

		m_objects = new Object*[wmfheader.NumOfObjects];
		std::memset(m_objects, 0, sizeof(Object*) * wmfheader.NumOfObjects);

		bool bDone = false;

		do
		{
			LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

			WMFRECORD record;
			pStream->Read(&record, sizeof record);

			ASSERT(record.Size >= 3);

			switch (record.Function)
			{
			case wmfSetMapMode:
				{
					uint16 mode;
					pStream->Read(&mode, 2);
					// MM_ANISOTROPIC

					TRACE("wmfSetMapMode %d\n", mode);

					SetMapMode(mode);
				}
				break;

			case wmfSetWindowOrg:
				{
					short y;
					short x;
					pStream->Read(&y, 2);
					pStream->Read(&x, 2);

					TRACE("wmfSetWindowOrg(%d,%d)\n", x, y);

				//	WO.X = x / 20.0;// * (pixelsPerInch / 72);
				//	WO.Y = y / 20.0;// * (pixelsPerInch / 72);
					SetWindowOrg(x, y);

					/*
				//	pCmd = new ScaleTransformCommand;
					LDraw::TranslateTransformCommand* pCmd = new LDraw::TranslateTransformCommand;

					pCmd->m_dx = x / 20.0;
					pCmd->m_dy = y / 20.0;

					pCommands->AddCommand(pCmd);
					*/
				}
				break;

			case wmfSetWindowExt:
				{
					short cy;
					short cx;
					pStream->Read(&cy, 2);
					pStream->Read(&cx, 2);

					TRACE("wmfSetWindowExt(%d,%d)\n", cx, cy);

					/*
					LDraw::ScaleTransformCommand* pCmd = new LDraw::ScaleTransformCommand;

					pCmd->m_sx = 1;
					pCmd->m_sy = -1;

					pCommands->AddCommand(pCmd);
					*/
				//	WE.Width = cx / 20.0;// * (pixelsPerInch / 72);
				//	WE.Height = cy / 20.0;// * (pixelsPerInch / 72);
					SetWindowExt(cx, cy);
				}
				break;

			case wmfCreatePenIndirect:
				{
					TRACE("wmfCreatePenIndirect\n");
					LOGPEN_16 logpen;
					pStream->Read(&logpen, sizeof logpen);

					LOGPEN lp;
					lp.lopnStyle = logpen.lopnStyle;
					lp.lopnWidth = logpen.lopnWidth;
					lp.lopnColor = logpen.lopnColor;

					for (int i = 0; i < m_numOfObjects; i++)
					{
						if (m_objects[i] == NULL)
						{
							CreatePenIndirect(i, lp);
							break;
						}
					}
				}
				break;

			case wmfCreateBrushIndirect:
				{
					TRACE("wmfCreateBrushIndirect\n");
					LOGBRUSH_16 lb16;
					pStream->Read(&lb16, sizeof lb16);

					LOGBRUSH lb;
					lb.lbStyle = lb16.lbStyle;
					lb.lbColor = lb16.lbColor;
					lb.lbHatch = lb16.lbHatch;

					for (int i = 0; i < m_numOfObjects; i++)
					{
						if (m_objects[i] == NULL)
						{
							CreateBrushIndirect(i, lb);
							break;
						}
					}
				}
				break;

			case wmfCreateFontIndirect:
				{
					TRACE("wmfCreateFontIndirect\n");

					LOGFONT_16 lf;
					pStream->Read(&lf, sizeof lf);

				//	wmfObjectFont* pObject = new wmfObjectFont;
				//	pObject->m_pFont = new LDraw::Font(ConvertA2S(lf.lfFaceName), -lf.lfHeight);

					for (int i = 0; i < wmfheader.NumOfObjects; i++)
					{
						if (m_objects[i] == NULL)
						{
							CreateFontIndirect(i, lf);
							break;
						}
					}
				}
				break;

			case wmfSelectObject:
				{
					TRACE("wmfSelectObject\n");

					uint16 n;
					pStream->Read(&n, 2);

					SelectObject(n);
				}
				break;

			case wmfDeleteObject:
				{
					TRACE("wmfDeleteObject\n");
					uint16 n;
					pStream->Read(&n, 2);

					DeleteObject(n);
				}
				break;

			case wmfSetPolyFillMode:
				{
					TRACE("wmfSetPolyFillMode\n");
				}
				break;

			case wmfSetBkMode:
				{
					TRACE("wmfSetBkMode\n");
				}
				break;

			case wmfSetROP2:
				{
					TRACE("wmfSetROP2\n");
				}
				break;

			case wmfSetTextColor:
				{
					TRACE("wmfSetTextColor\n");

					COLORREF textColor;
					pStream->Read(&textColor, 4);

					SetTextColor(textColor);
				}
				break;

			case wmfRectangle:
				{
					TRACE("wmfRectangle\n");

					short left;
					short top;
					short right;
					short bottom;

					pStream->Read(&bottom, 2);
					pStream->Read(&right, 2);
					pStream->Read(&top, 2);
					pStream->Read(&left, 2);

					ASSERT(0);
#if 0

					LDraw::FillRectangleFCommand* pCmd = new LDraw::FillRectangleFCommand(m_pCurBrush->m_pBrush, LDraw::RectF(left, top, right-left, bottom-top));
				/*	if (m_pCurBrush->m_pBrush)
						pCmd->m_brush = m_pCurBrush->m_pBrush;

					pCmd->m_rect.X = left;
					pCmd->m_rect.Y = top;
					pCmd->m_rect.Width = right-left;
					pCmd->m_rect.Height = bottom-top;
					*/

					pCommands->AddCommand(pCmd);
#endif
				}
				break;

			case wmfPolygon:
				{
					TRACE("wmfPolygon\n");

					ASSERT(0);
#if 0

					uint16 npoints;
					pStream->Read(&npoints, 2);

				//	uint32 npoints = (record.Size - 3)*2 / 4;

					LDraw::FillPolygonFCommand* pCmd = new LDraw::FillPolygonFCommand;
					if (m_pCurBrush->m_pBrush)
						pCmd->m_brush = m_pCurBrush->m_pBrush;

					for (int i = 0; i < npoints; i++)
					{
						short x;
						short y;

						pStream->Read(&x, 2);
						pStream->Read(&y, 2);

						pCmd->m_points.Add(LPToDP(x /* * (pixelsPerInch / 72)*/, y/* * (pixelsPerInch / 72)*/));
					}

					pCommands->AddCommand(pCmd);
#endif
				}
				break;

			case wmfExtTextOut:
				{
					TRACE("wmfExtTextOut\n");

					short x;
					short y;
					uint16 length;
					uint16 options;

					pStream->Read(&y, 2);
					pStream->Read(&x, 2);
					pStream->Read(&length, 2);
					pStream->Read(&options, 2);

					uint16 size = 8;

					if (options != 0)
					{
						// TODO: ETO_CLIPPED or ETO_OPAQUE 

						short left;
						short top;
						short right;
						short bottom;
						pStream->Read(&left, 2);
						pStream->Read(&top, 2);
						pStream->Read(&right, 2);
						pStream->Read(&bottom, 2);

						size += 8;
					}

					StringA* string;
					ASSERT(0);
#if 0
					string.MakeRoom(length);
#endif
					pStream->Read(string->begin(), length);
					size += length;

					if (length & 1)
					{
						pStream->Seek(1, System::IO::STREAM_SEEK_CUR);
						size++;
					}

					int* distances = NULL;

					int dxsize = (record.Size-3)*2 - size;
					if ((dxsize>>1) == length)
					{
						distances = new int[length];
						pStream->Read(distances, dxsize);

						for (int i = 0; i < length; i++)
						{
							uint16 distance;
							pStream->Read(&distance, 2);
							distances[i] = distance;
						}
					}

					ExtTextOut(x, y, string, distances);

					delete[] distances;
				}
				break;

			case wmfDibStretchBlt:
				{
					TRACE("wmfDibStretchBlt\n");

					DIBSTRETCHBLTRECORD_16 stretchblt;
					pStream->Read(&stretchblt.RasterOp, 2);
					pStream->Read(&stretchblt.RasterOp, 2);
					pStream->Read(&stretchblt.SrcHeight, 2);
					pStream->Read(&stretchblt.SrcWidth, 2);
					pStream->Read(&stretchblt.SrcY, 2);
					pStream->Read(&stretchblt.SrcX, 2);
					pStream->Read(&stretchblt.DestHeight, 2);
					pStream->Read(&stretchblt.DestWidth, 2);
					pStream->Read(&stretchblt.DestY, 2);
					pStream->Read(&stretchblt.DestX, 2);

					LDraw::Bitmap* bitmap = ReadDib(pStream);

					StretchDIBits(stretchblt.DestX, stretchblt.DestY, stretchblt.DestWidth, stretchblt.DestHeight, stretchblt.SrcX, stretchblt.SrcY, stretchblt.SrcWidth, stretchblt.SrcHeight, bitmap);

					/*
					pCmd->m_destRect.X = stretchblt.DestX;
					pCmd->m_destRect.Y = stretchblt.DestY;
					pCmd->m_destRect.Width = stretchblt.DestWidth;
					pCmd->m_destRect.Height = stretchblt.DestHeight;

					pCmd->m_srcX = stretchblt.SrcX;
					pCmd->m_srcY = stretchblt.SrcY;
					pCmd->m_srcWidth = stretchblt.SrcWidth;
					pCmd->m_srcHeight = stretchblt.SrcHeight;
					*/
				}
				break;

			case 0:
				bDone = true;
				break;

			default:
				TRACE("0x%x size: %d\n", record.Function, record.Size);
				break;
			}

			LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
			if (cur > start + record.Size * 2)
			{
				TRACE("WMF, Read past record size\n");
				break;
			}

			pStream->Seek(start + record.Size * 2, System::IO::STREAM_SEEK_SET);
		}
		while (!bDone);
	}
	else if (dword == emfHEADER)	// Could be EMF
	{
		pCommands = new LDraw::Commands;

		EMFHEADER emfheader;
		emfheader.RecordType = dword;
		pStream->Read(((uint8*)&emfheader)+4, sizeof emfheader - 4);
		if (emfheader.RecordSize >= sizeof emfheader)
		{
			if (emfheader.Signature == 0x464D4520)
			{
				/*
				m_rect.X = emfheader.FrameLeft;
				m_rect.Y = emfheader.FrameTop;
				m_rect.Width = (emfheader.FrameRight - emfheader.FrameLeft);
				m_rect.Height = (emfheader.FrameBottom - emfheader.FrameTop);
				*/

				m_rect.X = emfheader.BoundsLeft;
				m_rect.Y = emfheader.BoundsTop;
				m_rect.Width = (emfheader.BoundsRight - emfheader.BoundsLeft);
				m_rect.Height = (emfheader.BoundsBottom - emfheader.BoundsTop);

				pStream->Seek(emfheader.RecordSize - sizeof(emfheader), System::IO::STREAM_SEEK_CUR);

				m_numOfObjects = emfheader.NumOfHandles;

				m_objects = new Object*[emfheader.NumOfHandles];
				std::memset(m_objects, 0, sizeof(Object*) * emfheader.NumOfHandles);

				m_path = new LDraw::GraphicsPathF;

				bool bDone = false;

				do
				{
					LONGLONG start = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);

					EMFRECORD record;
					if (pStream->Read(&record, sizeof record) != sizeof record)
					{
						break;
					}

					ASSERT(record.Size >= 8);

					switch (record.Function)
					{
					case emfSETMAPMODE:
						{
							uint32 mode;
							pStream->Read(&mode, 4);

							TRACE("emfSETMAPMODE %d\n", mode);

							SetMapMode(mode);
						}
						break;

					case emfSETWINDOWORGEX:
						{
							long x;
							long y;
							pStream->Read(&x, 4);
							pStream->Read(&y, 4);

							SetWindowOrg(x, y);

							TRACE("emfSETWINDOWORGEX %d, %d\n", x, y);
						}
						break;

					case emfSETWINDOWEXTEX:
						{
							long cx;
							long cy;
							pStream->Read(&cx, 4);
							pStream->Read(&cy, 4);

							SetWindowExt(cx, cy);

							TRACE("emfSETWINDOWEXTEX %d, %d\n", cx, cy);
						}
						break;

					case emfSETVIEWPORTORGEX:
						{
							long x;
							long y;
							pStream->Read(&x, 4);
							pStream->Read(&y, 4);

							SetViewportOrg(x, y);

							TRACE("emfSETVIEWPORTORGEX %d, %d\n", x, y);
						}
						break;

					case emfSETVIEWPORTEXTEX:
						{
							long cx;
							long cy;
							pStream->Read(&cx, 4);
							pStream->Read(&cy, 4);

							SetViewportExt(cx, cy);

							TRACE("emfSETVIEWPORTEXTEX %d, %d\n", cx, cy);

#if 0
							LDraw::Matrix3f* transform = LDraw::Matrix3f::GetScale((double)VE.Width / WE.Width, (double)VE.Height / WE.Height);
#endif

						}
						break;

					case emfSETWORLDTRANSFORM:
						{
							TRACE("emfSETWORLDTRANSFORM\n");

							XFORM xform;
							pStream->Read(&xform, sizeof xform);

							LDraw::Matrix3f* transform = new LDraw::Matrix3f(xform.eM11, xform.eM12, xform.eM21, xform.eM22, xform.eDx, xform.eDy);

							LDraw::SetTransformCommand* pCmd = new LDraw::SetTransformCommand(transform);
							pCommands->AddCommand(pCmd);
						}
						break;

					case emfMODIFYWORLDTRANSFORM:
						{
							TRACE("emfMODIFYWORLDTRANSFORM\n");

							XFORM xform;
							uint32 iMode;

							pStream->Read(&xform, sizeof xform);
							pStream->Read(&iMode, 4);

							ASSERT(0);
#if 0

							LDraw::Matrix3f* transform2(xform.eM11, xform.eM12, xform.eM21, xform.eM22, xform.eDx, xform.eDy);
							
							LDraw::Matrix3f* transform = LDraw::Matrix3f::GetScale((double)VE.Width / WE.Width, (double)VE.Height / WE.Height);
							transform->Multiply(transform2);

							switch (iMode)
							{
							case MWT_IDENTITY:
								{
									ASSERT(0);
								}
								break;

							case MWT_LEFTMULTIPLY:
								{
									LDraw::MultiplyTransformCommand* pCmd = new LDraw::MultiplyTransformCommand;
									pCmd->m_transform = transform;
									pCommands->AddCommand(pCmd);
								}
								break;

							case MWT_RIGHTMULTIPLY:
								{
									ASSERT(0);
								}
								break;

							default:
								TRACE("Unsupported ModifyWorldTransform mode\n");
								ASSERT(0);
								THROW(-1);
							}
#endif
						}
						break;

					case emfSETPOLYFILLMODE:
						{
							TRACE("TODO emfSETPOLYFILLMODE\n");
						}
						break;

					case emfSETBKMODE:
						{
							TRACE("TODO emfSETBKMODE\n");
						}
						break;

					case emfSETTEXTCOLOR:
						{
							TRACE("emfSETTEXTCOLOR\n");

							COLORREF color;
							pStream->Read(&color, 4);

							SetTextColor(color);
						}
						break;

					case emfSETTEXTALIGN:
						{
							TRACE("emfSETTEXTALIGN\n");

							uint32 fMode;
							pStream->Read(&fMode, 4);

							SetTextAlign(fMode);
						}
						break;

					case emfSETMITERLIMIT:
						{
							TRACE("emfSETTEXTALIGN\n");

							float limit;
							pStream->Read(&limit, 4);

							SetMiterLimit(limit);
						}
						break;

					case emfCREATEPEN:
						{
							uint32 index;
							pStream->Read(&index, 4);

							LOGPEN lp;
							pStream->Read(&lp, sizeof(lp));

							CreatePenIndirect(index, lp);
						}
						break;

					case emfEXTCREATEPEN:
						{
							TRACE("emfEXTCREATEPEN\n");

							uint32 index;
							pStream->Read(&index, 4);

							uint32     offBmi; 
						   uint32     cbBmi; 
							uint32     offBits; 
							uint32     cbBits; 

							pStream->Read(&offBmi, 4);
							pStream->Read(&cbBmi, 4);
							pStream->Read(&offBits, 4);
							pStream->Read(&cbBits, 4);

							EXTLOGPEN lp;
							pStream->Read(&lp, 24);
							CreatePenIndirect(index, lp);
						}
						break;

					case emfCREATEBRUSHINDIRECT:
						{
							TRACE("emfCREATEBRUSHINDIRECT\n");

							uint32 index;
							pStream->Read(&index, 4);

							LOGBRUSH lb;
							pStream->Read(&lb, sizeof lb);
							CreateBrushIndirect(index, lb);
						}
						break;

					case emfEXTCREATEFONTINDIRECTW:
						{
							TRACE("emfEXTCREATEFONTINDIRECTW\n");

							uint32 index;
							pStream->Read(&index, 4);

							LOGFONTW lf;
							pStream->Read(&lf, sizeof lf);
							CreateFontIndirect(index, lf);
						}
						break;

					case emfSELECTOBJECT:
						{
							TRACE("emfSELECTOBJECT\n");

							uint32 n;
							pStream->Read(&n, 4);

							SelectObject(n);
						}
						break;

					case emfDELETEOBJECT:
						{
							TRACE("emfDELETEOBJECT\n");

							uint32 n;
							pStream->Read(&n, 4);

							DeleteObject(n);
						}
						break;

					case emfBEGINPATH:
						{
							TRACE("emfBEGINPATH\n");
							m_bBeginPath = true;
						}
						break;

					case emfENDPATH:
						{
							TRACE("emfENDPATH\n");
							m_bBeginPath = false;
						}
						break;

					case emfFILLPATH:
						{
							TRACE("emfFILLPATH\n");

							FillPath();
						}
						break;

					case emfMOVETOEX:
						{
							long x;
							long y;

							pStream->Read(&x, 4);
							pStream->Read(&y, 4);

							TRACE("emfMOVETOEX %d, %d\n", x, y);

							MoveTo(x, y);
						}
						break;

					case emfLINETO:
						{
							TRACE("TODO emfLINETO\n");
						}
						break;

					case emfPOLYBEZIERTO16:
						{
							TRACE("emfPOLYBEZIERTO16\n");

							LDraw::BBoxi rect;
							pStream->Read(&rect, sizeof rect);

							uint32 count;
							pStream->Read(&count, 4);

							for (int i = 0; i < count; i += 3)
							{
								short x1;
								short y1;
								short x2;
								short y2;
								short x3;
								short y3;

								pStream->Read(&x1, 2);
								pStream->Read(&y1, 2);
								pStream->Read(&x2, 2);
								pStream->Read(&y2, 2);
								pStream->Read(&x3, 2);
								pStream->Read(&y3, 2);

								m_path->AddBezier(LPToDP(x1, y1), LPToDP(x2, y2), LPToDP(x3, y3));
							}
						}
						break;

					case emfPOLYPOLYLINE16:
						{
							TRACE("emfPOLYPOLYLINE16\n");

							LDraw::BBoxi rect;
							pStream->Read(&rect, sizeof rect);

							uint32 npolys;
							pStream->Read(&npolys, 4);

							uint32 cpts;
							pStream->Read(&cpts, 4);

							for (int j = 0; j < npolys; j++)
							{
								uint32 ncount;
								pStream->Read(&ncount, 4);
							}

							for (int i = 0; i < cpts; i++)
							{
								short x;
								short y;

								pStream->Read(&x, 2);
								pStream->Read(&y, 2);

								if (i == 0)
									m_path->AddMove(LPToDP(x, y));
								else
									m_path->AddLine(LPToDP(x, y));
							}

							if (!m_bBeginPath)
							{
								LDraw::DrawPathCommand* pCmd = new LDraw::DrawPathCommand;
								if (m_pCurPen->m_pPen)
									pCmd->m_pen = m_pCurPen->m_pPen;

								pCmd->m_path = m_path;

								pCommands->AddCommand(pCmd);

								m_path = new LDraw::GraphicsPathF;
							}
						}
						break;

					case emfPOLYGON16:	// untested
						{
							TRACE("emfPOLYGON16\n");

							LDraw::BBoxi rect;
							pStream->Read(&rect, sizeof rect);

							uint32 cpts;
							pStream->Read(&cpts, 4);

							for (int i = 0; i < cpts; i++)
							{
								short x;
								short y;

								pStream->Read(&x, 2);
								pStream->Read(&y, 2);

								if (i == 0)
									m_path->AddMove(LPToDP(x, y));
								else
									m_path->AddLine(LPToDP(x, y));
							}

							if (!m_bBeginPath)
							{
								LDraw::FillPathFCommand* pCmd = new LDraw::FillPathFCommand;
								if (m_pCurBrush->m_pBrush)
									pCmd->m_brush = m_pCurBrush->m_pBrush;

								pCmd->m_path = m_path;

								pCommands->AddCommand(pCmd);

								m_path = new LDraw::GraphicsPathF;
							}
						}
						break;

					case emfPOLYPOLYGON16:
						{
							TRACE("emfPOLYPOLYGON16\n");

							LDraw::BBoxi rect;
							pStream->Read(&rect, sizeof rect);

							uint32 npolys;
							pStream->Read(&npolys, 4);

							uint32 cpts;
							pStream->Read(&cpts, 4);

							for (int j = 0; j < npolys; j++)
							{
								uint32 ncount;
								pStream->Read(&ncount, 4);
							}

							for (int i = 0; i < cpts; i++)
							{
								short x;
								short y;

								pStream->Read(&x, 2);
								pStream->Read(&y, 2);

								if (i == 0)
									m_path->AddMove(LPToDP(x, y));
								else
									m_path->AddLine(LPToDP(x, y));
							}

							if (!m_bBeginPath)
							{
								LDraw::FillPathFCommand* pCmd = new LDraw::FillPathFCommand;
								if (m_pCurBrush->m_pBrush)
									pCmd->m_brush = m_pCurBrush->m_pBrush;

								pCmd->m_path = m_path;

								pCommands->AddCommand(pCmd);

								m_path = new LDraw::GraphicsPathF;
							}
						}
						break;

					case emfEXTTEXTOUTA:
						{
							TRACE("emfEXTTEXTOUTA\n");

							LDraw::BBoxi bounds;
							pStream->Read(&bounds, sizeof bounds);

							uint32 iGraphicsMode;
							pStream->Read(&iGraphicsMode, 4);

							if (iGraphicsMode != GM_COMPATIBLE && iGraphicsMode != GM_ADVANCED)
							{
								TRACE("Unrecognized iGraphicsMode value(%d)\n", iGraphicsMode);
								ASSERT(0);
								THROW(-1);
							}

							//if (iGraphicsMode == GM_COMPATIBLE)
							{
								float exScale;
								float eyScale;

								pStream->Read(&exScale, 4);
								pStream->Read(&eyScale, 4);
							}

							long x;
							long y;
							uint32 length;
							uint32 offString;
							uint32 options;

							pStream->Read(&x, 4);
							pStream->Read(&y, 4);
							pStream->Read(&length, 4);
							pStream->Read(&offString, 4);
							pStream->Read(&options, 4);

							uint16 size = 16;

						//	if (options != 0)
							{
								// TODO: ETO_CLIPPED or ETO_OPAQUE 

								long left;
								long top;
								long right;
								long bottom;
								pStream->Read(&left, 4);
								pStream->Read(&top, 4);
								pStream->Read(&right, 4);
								pStream->Read(&bottom, 4);

								size += 16;
							}

							uint32 offdx;
							pStream->Read(&offdx, 4);

							pStream->Seek(start + offString, System::IO::STREAM_SEEK_SET);

							//LDraw::DrawStringACommand* pCmd = new LDraw::DrawStringACommand;

							StringA* string;
							ASSERT(0);
#if 0
							string.MakeRoom(length);
#endif

							pStream->Read(string->begin(), length);
							size += length;

							/*
							if (length & 1)
							{
								pStream->Seek(1, System::IO::STREAM_SEEK_CUR);
								size++;
							}
							*/

						//	pCmd->m_brush = LDraw::SolidBrush(LDraw::Color::FromCOLORREF(m_textColor));
						//	if (m_pCurFont->m_pFont)
						//		pCmd->m_font = *m_pCurFont->m_pFont;


						//	pCmd->m_point.Y = y;//LPToDP(x, y);
						//	pCmd->m_point.X = x;

						//	pCommands->AddCommand(pCmd);

							int* distances = NULL;

							ExtTextOut(x, y, string, distances);

							delete[] distances;
						}
						break;

					case emfSTRETCHDIBITS:
						{
							TRACE("emfSTRETCHDIBITS\n");

							emf_STRETCHDIBITS dib;
							pStream->Read(&dib, sizeof dib);

							dib.offBmiSrc;
							dib.offBitsSrc;

							pStream->Seek(start + dib.offBmiSrc, System::IO::STREAM_SEEK_SET);

							LDraw::Bitmap* bitmap = ReadDib(pStream);

							StretchDIBits(dib.xDest, dib.yDest, dib.cxDest, dib.cyDest, dib.xSrc, dib.ySrc, dib.cxSrc, dib.cySrc, bitmap);
						}
						break;

					case emfEOF:
						bDone = true;
						break;

					default:
						TRACE("%d size: %d\n", record.Function, record.Size);
						break;
					}

					LONGLONG cur = pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
					if (cur > start + record.Size)
					{
						TRACE("EMF, Read past record size\n");
						break;
					}

					pStream->Seek(start + record.Size, System::IO::STREAM_SEEK_SET);
				}
				while (!bDone);
			}
		}
	}
}

LDraw::Bitmap* MetafileLoader::ReadDib(ISequentialByteStream* pStream)
{
	MSWindows::BITMAPINFOHEADER bmi;
	pStream->Read(&bmi, sizeof bmi);

	if (bmi.biSize < 40)
		return NULL;

	int width = bmi.biWidth;

	LDraw::Bitmap* bitmap = new LDraw::Bitmap(width, bmi.biHeight, LDraw::PixelFormat_t::RGBAP_32);

	int rowbytes = ROWBYTES_DWORD(width, bmi.biBitCount);

	uint8* rowdata = new uint8[rowbytes];

	int numcolors;
	
	if (bmi.biClrUsed > 0)
		numcolors = bmi.biClrUsed;
	else if (bmi.biBitCount <= 8)
		numcolors = 1<<bmi.biBitCount;
	else
		numcolors = 0;

	LDraw::PixelRGBAP_32* palette = new LDraw::PixelRGBAP_32[numcolors];

	for (int i = 0; i < numcolors; i++)
	{
		MSWindows::tagRGBQUAD quad;
		pStream->Read(&quad, sizeof(MSWindows::tagRGBQUAD));

		palette[i].a = 255;
		palette[i].r = quad.rgbRed;
		palette[i].g = quad.rgbGreen;
		palette[i].b = quad.rgbBlue;
	}

	LDraw::BitmapData bitmapData;
	bitmap->LockBits(NULL, LDraw::ImageLockModeWrite, &bitmapData);

	for (int y = 0; y < bmi.biHeight; y++)
	{
		pStream->Read(rowdata, rowbytes);

		LDraw::PixelRGBAP_32* dest = (LDraw::PixelRGBAP_32*)((uint8*)bitmapData.Scan0 + bitmapData.Stride*(bmi.biHeight - y - 1));

		if (bmi.biBitCount == 32)
		{
			uint8* src = rowdata;

			for (int x = 0; x < width; x++)
			{
				dest->a = 255;
				dest->r = src[2];
				dest->g = src[1];
				dest->b = src[0];

				dest++;
				src += 4;
			}
		}
		else if (bmi.biBitCount == 24)
		{
			uint8* src = rowdata;

			for (int x = 0; x < width; x++)
			{
				dest->a = 255;
				dest->r = src[2];
				dest->g = src[1];
				dest->b = src[0];

				dest++;
				src += 3;
			}
		}
		else if (bmi.biBitCount == 8)
		{
			uint8* src = rowdata;

			for (int x = 0; x < width; x++)
			{
				*dest = palette[*src];

				dest++;
				src++;
			}
		}
		else if (bmi.biBitCount == 1)
		{
			uint8* src = rowdata;

			int width2 = width >> 3;

			int x;
			for (x = 0; x < width2; x++)
			{
				uint8 byte = *src++;

				uint8 index;

				index = (byte>>7) & 1;
				*dest++ = palette[index];

				index = (byte>>6) & 1;
				*dest++ = palette[index];

				index = (byte>>5) & 1;
				*dest++ = palette[index];

				index = (byte>>4) & 1;
				*dest++ = palette[index];

				index = (byte>>3) & 1;
				*dest++ = palette[index];

				index = (byte>>2) & 1;
				*dest++ = palette[index];

				index = (byte>>1) & 1;
				*dest++ = palette[index];

				index = (byte) & 1;
				*dest++ = palette[index];
			}

		// TODO, This is untested

			int left = width - (width2<<3);
			uint8 byte = *src++;

			for (; x < left; x++)
			{
				int index = (byte>>7) & 1;
				*dest++ = palette[index];
				byte <<= 1;
			}
		}
		else
		{
			// TODO
			ASSERT(0);
		}
	}

	bitmap->UnlockBits(&bitmapData);

	delete[] rowdata;
	delete[] palette;

	return bitmap;
}

#define OBJ_PEN             1
#define OBJ_BRUSH           2
#define OBJ_DC              3
#define OBJ_METADC          4
#define OBJ_PAL             5
#define OBJ_FONT            6
#define OBJ_BITMAP          7
#define OBJ_REGION          8
#define OBJ_METAFILE        9
#define OBJ_MEMDC           10
#define OBJ_EXTPEN          11
#define OBJ_ENHMETADC       12
#define OBJ_ENHMETAFILE     13
#define OBJ_COLORSPACE      14

void MetafileLoader::SelectObject(int n)
{
	if (n < 1 || n >= m_numOfObjects)
	{
		TRACE("SelectObject out of bounds\n");
		ASSERT(0);
		THROW(-1);
	}

	if (m_objects[n] == NULL)
	{
		TRACE("SelectObject NULL object\n");
		ASSERT(0);
		THROW(-1);
	}

	if (m_objects[n]->m_type == OBJ_PEN)
	{
		m_pCurPen = (ObjectPen*)m_objects[n];
	}
	else if (m_objects[n]->m_type == OBJ_BRUSH)
	{
		m_pCurBrush = (ObjectBrush*)m_objects[n];
	}
	else if (m_objects[n]->m_type == OBJ_FONT)
	{
		m_pCurFont = (ObjectFont*)m_objects[n];
	}
	else
		ASSERT(0);
}

void MetafileLoader::DeleteObject(int n)
{
	if (n < 0 || n >= m_numOfObjects)
	{
		TRACE("DeleteObject out of bounds\n");
		ASSERT(0);
		THROW(-1);
	}

	if (m_objects[n] == NULL)
	{
		TRACE("DeleteObject NULL object\n");
		ASSERT(0);
		THROW(-1);
	}

	delete m_objects[n];
	m_objects[n] = NULL;
}

#define GetRValue(rgb)      ((uint8)(rgb))
#define GetGValue(rgb)      ((uint8)(((uint16)(rgb)) >> 8))
#define GetBValue(rgb)      ((uint8)((rgb)>>16))

void MetafileLoader::CreatePenIndirect(int index, const LOGPEN& lp)
{
	ObjectPen* pPen = new ObjectPen;
	pPen->m_pPen = new LDraw::Pen(LDraw::Color(GetRValue(lp.lopnColor), GetGValue(lp.lopnColor), GetBValue(lp.lopnColor)), lp.lopnWidth);

	m_objects[index] = pPen;
}

void MetafileLoader::CreatePenIndirect(int index, const EXTLOGPEN& lp)
{
	ObjectPen* pPen = new ObjectPen;
	pPen->m_pPen = new LDraw::Pen(LDraw::Color(GetRValue(lp.elpColor), GetGValue(lp.elpColor), GetBValue(lp.elpColor)), lp.elpWidth);

	m_objects[index] = pPen;
}

void MetafileLoader::CreateBrushIndirect(int index, const LOGBRUSH& lb)
{
	ObjectBrush* pBrush = new ObjectBrush;
	pBrush->m_pBrush = new LDraw::SolidBrush(LDraw::Color(GetRValue(lb.lbColor), GetGValue(lb.lbColor), GetBValue(lb.lbColor)));

	m_objects[index] = pBrush;
}

void MetafileLoader::CreateFontIndirect(int index, const LOGFONT_16& lf)
{
	ObjectFont* pObject = new ObjectFont;
	pObject->m_pFont = new LDraw::Font(new StringA(string_copy(lf.lfFaceName)), -lf.lfHeight);

	m_objects[index] = pObject;
}

void MetafileLoader::CreateFontIndirect(int index, const LOGFONTA& lf)
{
	ObjectFont* pObject = new ObjectFont;
	pObject->m_pFont = new LDraw::Font(new StringA(string_copy(lf.lfFaceName)), -lf.lfHeight);

	m_objects[index] = pObject;
}

void MetafileLoader::CreateFontIndirect(int index, const LOGFONTW& lf)
{
	ObjectFont* pObject = new ObjectFont;
	pObject->m_pFont = new LDraw::Font(new StringW(string_copy(lf.lfFaceName)), -lf.lfHeight);

	m_objects[index] = pObject;
}

void MetafileLoader::SetMapMode(int mapmode)
{
}

void MetafileLoader::SetWindowOrg(int x, int y)
{
	WO.X = x;
	WO.Y = y;
}

void MetafileLoader::SetWindowExt(int cx, int cy)
{
	WE.Width = cx;
	WE.Height = cy;
}

void MetafileLoader::SetViewportOrg(int x, int y)
{
	VO.X = x;
	VO.Y = y;
}

void MetafileLoader::SetViewportExt(int cx, int cy)
{
	VE.Width = cx;
	VE.Height = cy;
}

void MetafileLoader::SetTextColor(COLORREF color)
{
	m_textColor = color;
}

void MetafileLoader::SetTextAlign(uint32 textAlign)
{
	m_textAlign = textAlign;
}

void MetafileLoader::SetMiterLimit(float miterLimit)
{
	m_miterLimit = miterLimit;
}

void MetafileLoader::MoveTo(int x, int y)
{
	m_curx = x;
	m_cury = y;

	if (m_bBeginPath)
	{
		m_path->AddMove(LPToDP(x, y));
	}
}

#define TA_LEFT                      0
#define TA_RIGHT                     2
#define TA_CENTER                    6

#define TA_TOP                       0
#define TA_BOTTOM                    8
#define TA_BASELINE                  24

void MetafileLoader::ExtTextOut(int x, int y, StringA* string, const int* distances)
{
	LDraw::DrawStringAPointCommand* pCmd = new LDraw::DrawStringAPointCommand;

	pCmd->m_string = string;

	if (m_pCurFont->m_pFont)
		pCmd->m_font = m_pCurFont->m_pFont;

	if (m_textAlign & TA_BASELINE)
	{
		y -= pCmd->m_font->GetCellAscent();
	}
	else if (m_textAlign & TA_BOTTOM)
	{
	}
	else if (m_textAlign & TA_TOP)
	{
	}

	//pCmd->m_point.X += bounds.left;

	if (m_textAlign & TA_CENTER)
	{
	}
	else if (m_textAlign & TA_LEFT)
	{
	}
	else if (m_textAlign & TA_RIGHT)
	{
	}

	pCmd->m_point.X = x;
	pCmd->m_point.Y = y;

	pCmd->m_brush = new LDraw::SolidBrush(LDraw::Color(GetRValue(m_textColor), GetGValue(m_textColor), GetBValue(m_textColor)));

	if (distances)
	{
		pCmd->m_distances = new float[string->Length()];
		for (int i = 0; i < string->Length(); i++)
		{
			pCmd->m_distances[i] = distances[i];
		}
	}

	pCommands->AddCommand(pCmd);
}

void MetafileLoader::FillPath()
{
	LDraw::FillPathFCommand* pCmd = new LDraw::FillPathFCommand;
	if (m_pCurBrush->m_pBrush)
		pCmd->m_brush = m_pCurBrush->m_pBrush;

	pCmd->m_path = m_path;

	pCommands->AddCommand(pCmd);

	m_path->Reset();
}

void MetafileLoader::StretchDIBits(int destX, int destY, int destWidth, int destHeight, int srcX, int srcY, int srcWidth, int srcHeight, LDraw::Bitmap* bitmap)
{
	LDraw::DrawImageRectCommand* pCmd = new LDraw::DrawImageRectCommand;

	pCmd->m_destRect.X = destX;
	pCmd->m_destRect.Y = destY;
	pCmd->m_destRect.Width = destWidth;
	pCmd->m_destRect.Height = destHeight;

	pCmd->m_srcX = srcX;
	pCmd->m_srcY = srcY;
	pCmd->m_srcWidth = srcWidth;
	pCmd->m_srcHeight = srcHeight;

	pCmd->m_bitmap = bitmap;

	pCommands->AddCommand(pCmd);
}

}	// wmf
}	// System
