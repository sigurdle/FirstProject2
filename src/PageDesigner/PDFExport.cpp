#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDFExport.h"

#include "PDContentText.h"

_bstr_t stripspaces(BSTR s);

void DoBoxes(LPDFLib::IPDFEText* pText, CPDFEFont* pFont, /*ASFixedMatrix* mat,*/ CBox* pBox, IPDMatrix* matpdf, RectD pageRect)
{
#if 0
	if (pBox->m_type == 3)	// Element Box
	{
		CPDFEFont* pFont = new CPDFEFont;
		PDEFontAttrs fattrs;
	//	fattrs.name = "Times-Roman";
		fattrs.name = (char*)stripspaces(pBox->m_pElement->m_fontFamily);
		fattrs.type = "TrueType";
		pFont->Create(&fattrs);

		for (int i = 0; i < pBox->m_children.GetSize(); i++)
		{
			DoBoxes(pText, pFont, /*mat,*/ pBox->m_children[i], matpdf, pageRect);
		}
	}
	/*
	else if (pBox->m_type == 2)	// Line Box
	{
		Gdiplus::RectF rc = pBox->GetAbsInnerRect();

		ASFixedMatrix mat;
		mat.a = 1;					mat.b = 0;
		mat.c = 0;					mat.d = 1;
		mat.h = rc.X*65536.0;	mat.v = rc.Y*65536.0;

		for (int i = 0; i < pBox->m_children.GetSize(); i++)
		{
			DoBoxes(pText, pFont, mat, pBox->m_children[i]);
		}
	}
	*/
	else if (pBox->m_type == 10)	// Word
	{
		CWordBox* pWord = (CWordBox*)pBox;
		Gdiplus::RectF rc = pBox->GetAbsInnerRect();

		ASFixedMatrix mat;
		mat.a = 1;				mat.b = 0;
		mat.c = 0;				mat.d = 1;
		mat.h = rc.X;
//		mat.v = (pageHeight-rc.GetBottom())*65536.0;

		CLineBox* pLine = (CLineBox*)pBox->m_parent->m_parent;
		Gdiplus::RectF linebox = pLine->GetAbsInnerRect();
		mat.v = (pageRect.Height-(linebox.Y+pLine->m_maxascent));

		PDETextState tstate;
		tstate.fontSize = ConvertSpecifiedValueToUserUnit(UNIT_PT, pBox->m_parent->m_pElement->m_fontSize)*65536.0;

		pText->Add(0, 0, pWord->m_text, pWord->m_text.length(), pFont, NULL, &tstate, &mat, NULL);
	}
	else
	{
		for (int i = 0; i < pBox->m_children.GetSize(); i++)
		{
			DoBoxes(pText, pFont, /*mat,*/ pBox->m_children[i], matpdf, pageRect);
		}
	}
#endif
}

void CPDFExport::SaveObjectContentText(LPDFLib::IPDFEContent* pContent, IPDContentText* pdcontentText, IPDMatrix* matpdf, RectD pageRect)
{
	CPDContentText* pContentText = static_cast<CPDContentText*>(pdcontentText);

	LPDFLib::IPDFETextPtr pText;// = new CPDFEText;

	/*
	ASFixedMatrix mat;
	mat.a = 1;	mat.b = 0;
	mat.c = 0;	mat.d = 1;
	mat.h = 0;	mat.v = 0;
	*/

	DoBoxes(pText, NULL, /*&mat,*/ pContentText->m_pBox, matpdf, pageRect);

	pContent->AddElem(pContent->GetNumElems()-1, pText);	// insert at end
}

void CPDFExport::SavePath(LPDFLib::IPDFEPath* pPath, IPDPath* pdpath, IPDMatrix* matpdf, RectD pageRect)
{
	long nsubpaths;
	pdpath->get_subPathCount(&nsubpaths);

	for (int nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
	{
		CComPtr<IPDSubPath> subpath;
		pdpath->getSubPath(nsubpath, &subpath);

		VARIANT_BOOL closed;
		subpath->get_closed(&closed);

		long npoints;
		subpath->get_pointCount(&npoints);

		BezierPoint bpt0;
		subpath->getPoint(0, &bpt0);

		BezierPoint _bpt0 = bpt0;

		// move
		pPath->AddSegment(LPDFLib::kPDFEMoveTo,
			bpt0.x, bpt0.y,
			0, 0,
			0, 0);

		for (int i = 1; i < npoints; i++)
		{
			BezierPoint bpt;
			subpath->getPoint(i, &bpt);

		// cubic bezier
			pPath->AddSegment(LPDFLib::kPDFECurveTo,
				bpt0.x2, bpt0.y2,
				bpt.x1, bpt.y1,
				bpt.x, bpt.y);

			bpt0 = bpt;
		}

		if (closed)
		{
		// cubic bezier
			pPath->AddSegment(LPDFLib::kPDFECurveTo,
				bpt0.x2, bpt0.y2,
				_bpt0.x1, _bpt0.y1,
				_bpt0.x, _bpt0.y);

		// close
			pPath->AddSegment(LPDFLib::kPDFEClosePath,
				0, 0,
				0, 0,
				0, 0);
		}
	}

//	pPath->SetData(data.GetData(), data.GetSize()*4);
}

void CPDFExport::SaveObjectGraphic(LPDFLib::IPDFEContent* pContent, IPDContentGraphic* pdgraphic, IPDMatrix* matpdf, RectD pageRect)
{
	CComQIPtr<IPDObjectTransformable> pdxgraphic = pdgraphic;

	RectD bounds;
	pdxgraphic->getScreenBBox(&bounds);

	if (	(bounds.X < pageRect.X+pageRect.Width) &&
			(bounds.X+bounds.Width > pageRect.X))
	{
		CComPtr<IPDImage> image;
		pdgraphic->get_image(&image);

		double x,y;
		long width, height;

		pdgraphic->get_x(&x);
		pdgraphic->get_y(&y);
		image->get_width(&width);
		image->get_height(&height);

		CComPtr<IPDMatrix> omat0;
		pdxgraphic->get_transformMatrix(&omat0);

		CComPtr<IPDMatrix> mat0;
		mat0.CoCreateInstance(CLSID_PDMatrix);
		mat0->setScaleNonUniform(width, -height);

		CComPtr<IPDMatrix> mat1;
		mat0->translate(x, y+height, &mat1);

		CComPtr<IPDMatrix> mat2;
		mat1->multiply(omat0, &mat2);

		CComPtr<IPDMatrix> omat;
		mat2->multiply(matpdf, &omat);

	//
		LPDFLib::IPDFEMatrixPtr asmat;
		double a; omat->get_a(&a); asmat->a = a;
		double b; omat->get_b(&b); asmat->b = b;
		double c; omat->get_c(&c); asmat->c = c;
		double d; omat->get_d(&d); asmat->d = d;
		double e; omat->get_e(&e); asmat->e = e;
		double f; omat->get_f(&f); asmat->f = f;
/*		omat->get_a(&asmat.a);
		omat->get_b(&asmat.b);
		omat->get_c(&asmat.c);
		omat->get_d(&asmat.d);
		omat->get_e(&asmat.h);
		omat->get_f(&asmat.v);
*/
		LPDFLib::IPDFEImagePtr pImage;// = new CPDFEImage;

		LPDFLib::IPDFCosStream* pCosImage;
		image->GetProp(L"cos-image", (DWORD*)&pCosImage);
/*
		CComPtr<IPDMatrix> mat0;

		mat0.CoCreateInstance(CLSID_PDMatrix);
		mat0->setScaleNonUniform(width, height);

		CComPtr<IPDMatrix> mat;
		mat0->translate(x, pageRect.Height-(y+height), &mat);

		ASFixedMatrix asmat;
		mat->get_a(&asmat.a);
		mat->get_b(&asmat.b);
		mat->get_c(&asmat.c);
		mat->get_d(&asmat.d);
		mat->get_e(&asmat.h);
		mat->get_f(&asmat.v);
*/
		m_pdfdoc->CreateImageFromCosObj(pCosImage, asmat);

		pContent->AddElem(pContent->GetNumElems()-1, pImage);	// insert at end
	}
}

void CPDFExport::SaveObjectFrame(LPDFLib::IPDFEContent* pContent, IPDObjectFrame* pdframe, IPDMatrix* matpdf, RectD pageRect)
{
	CComQIPtr<IPDObjectTransformable> pdxframe = pdframe;

	RectD bounds;
	pdxframe->getScreenBBox(&bounds);

	if (	(bounds.X < pageRect.X+pageRect.Width) &&
			(bounds.X+bounds.Width > pageRect.X))
	{
		CComPtr<IPDPath> pdpath;
		pdframe->get_path(&pdpath);

		CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokefill = pdframe;

		CComPtr<IObjectMap> subobjects;
		strokefill->get_subObjects(&subobjects);

		long nsubobjects;
		subobjects->get_length(&nsubobjects);

		//bool bSimple = true;

		CComQIPtr<IPDObjectFill> fill;
		CComQIPtr<IPDObjectStroke> stroke;

		for (int i = 0; i < nsubobjects; i++)
		{
			CComPtr<IPDObjectWithBrush> withBrush;
			subobjects->item(i, (IUnknown**)&withBrush);

			PDObjectType objectType;
			withBrush->get_objectType(&objectType);

			CComPtr<IPDBrush> brush;
			withBrush->get_brush(&brush);

			if (i == 0 && objectType == PATH_FILL) fill = withBrush;
			else if (i == 1 && objectType == PATH_STROKE) stroke = withBrush;
		}

	#if 0
		if (bSimple)
		{
			CComPtr<ISVGPathElement> pathElement;
			m_svgdoc->createElement(L"path", (IDOMElement**)&pathElement);

			CComQIPtr<ISVGAnimatedPathData> pathdata = pathElement;

			CComPtr<ISVGPathSegList> seglist;
			pathdata->get_normalizedPathSegList(&seglist);

			SavePath(pdpath, pathElement, seglist);

			CComQIPtr<ISVGStylable> stylable = pathElement;
			CComPtr<IDOMCSSStyleDeclaration> style;
			stylable->get_style(&style);

			{
				CComPtr<IPDBrush> brush;
				fill->get_brush(&brush);

				CComPtr<IPDColor> color;
				brush->get_tintedRGBColor(&color);
				double red; color->getChannel(0, &red);
				double green; color->getChannel(1, &green);
				double blue; color->getChannel(2, &blue);

				//CComPtr<ISVGPaint> paint;
				//style->getPropertyCSSValue(L"fill", (ICSSValue**)&paint);

				WCHAR buf[64];
				swprintf(buf, L"#%2.2X%2.2X%2.2X", (int)red, (int)green, (int)blue);

				//paint->setPaint(SVG_PAINTTYPE_RGBCOLOR, NULL, buf, NULL);
				style->setProperty(L"fill", buf, L"");
			}

			group->appendChild(pathElement, NULL);
		}
		else
		{
		}
	#endif

		LPDFLib::IPDFEPathPtr pPath = m_pdfdoc->CreatePath();// = new CPDFEPath;
		SavePath(pPath, pdpath, matpdf, pageRect);

	// Matrix

	//
		CComPtr<IPDMatrix> omat0;
		pdxframe->get_transformMatrix(&omat0);

		CComPtr<IPDMatrix> omat;
		omat0->multiply(matpdf, &omat);

	//
		LPDFLib::IPDFEMatrixPtr asmat = m_pdfdoc->CreateMatrix();
		double a; omat->get_a(&a); asmat->a = a;
		double b; omat->get_b(&b); asmat->b = b;
		double c; omat->get_c(&c); asmat->c = c;
		double d; omat->get_d(&d); asmat->d = d;
		double e; omat->get_e(&e); asmat->e = e;
		double f; omat->get_f(&f); asmat->f = f;
		pPath->SetMatrix(asmat);

	// Stroke/Fill
		pPath->SetPaintOp(kPDFEStroke | kPDFEFill);

	// Graphic state
		CComQIPtr<IPDStrokeSettings> stroke2 = stroke;

		//LPDFLib::IPDFEExtGStatePtr extGState;
		LPDFLib::IPDFEGraphicStatePtr gstate = pPath->GetGState();

		double lineWidth;
		stroke2->get_strokeWeight(&lineWidth);
		gstate->lineWidth = lineWidth;

//		stroke2->get_strokeCap(&gstate.lineCap);
//		stroke2->get_strokeJoin(&gstate.lineJoin);
//		stroke2->get_strokeMiterLimit(&gstate.miterLimit);

	// Color
#if 0
		{
			// Stroke
			if (stroke)
			{
				CComPtr<IPDBrush> brush;
				stroke->get_brush(&brush);

				CComPtr<IPDColor> color;
				brush->get_tintedRGBColor(&color);

				double red;		color->getChannel(0, &red);
				double green;	color->getChannel(1, &green);
				double blue;	color->getChannel(2, &blue);

				gstate.strokeColorSpec.value.color[0] = red/255;
				gstate.strokeColorSpec.value.color[1] = green/255;
				gstate.strokeColorSpec.value.color[2] = blue/255;
			}
			// Fill
			if (fill)
			{
				CComPtr<IPDBrush> brush;
				fill->get_brush(&brush);

				CComPtr<IPDColor> color;
				brush->get_tintedRGBColor(&color);

				double red;		color->getChannel(0, &red);
				double green;	color->getChannel(1, &green);
				double blue;	color->getChannel(2, &blue);

				gstate.fillColorSpec.value.color[0] = red/255;
				gstate.fillColorSpec.value.color[1] = green/255;
				gstate.fillColorSpec.value.color[2] = blue/255;
			}
		}
#endif

#if 0
		CPDFEExtGState* pExtGState = new CPDFEExtGState;
		{
			LPDFLib::IPDFCosDictPtr pExtGStateDict = m_pdfdoc->GetCosDoc()->CosNewDict(VARIANT_TRUE);

			LPDFLib::IPDFCosNamePtr pType = m_pdfdoc->GetCosDoc()->CosNewName(VARIANT_FALSE, L"ExtGState");
			pExtGStateDict->CosDictPut(L"Type", pType);

			LPDFLib::IPDFCosBooleanPtr pAIS = m_pdfdoc->GetCosDoc()->CosNewBoolean(VARIANT_FALSE, false);
			pExtGStateDict->CosDictPut("AIS", pAIS);

			pExtGState->Create(pExtGStateDict);

			pExtGState->SetOpacityStroke(0.5);
		}

		gstate.extGState = pExtGState;
#endif
		pPath->SetGState(gstate);

	//
		pContent->AddElem(pContent->GetNumElems()-1, pPath);	// insert at end

	// Frame content
		CComPtr<IPDObject> content;
		pdframe->get_content(&content);
		if (content)
		{
			PDObjectType objectType;
			content->get_objectType(&objectType);

			if (objectType == CONTENT_TEXT)
			{
				CComQIPtr<IPDContentText> contentText = content;
				SaveObjectContentText(pContent, contentText, matpdf, pageRect);
			}
			else if (objectType == CONTENT_GRAPHIC)
			{
				CComQIPtr<IPDContentGraphic> pdgraphic = content;
				SaveObjectGraphic(pContent, pdgraphic, matpdf, pageRect);
			}
		}
	}
}

void CPDFExport::SaveObjectGroup(LPDFLib::IPDFEContent* pContent, IPDObjectGroup* pdgroup, IPDMatrix* matpdf, RectD pageRect)
{
	CComPtr<IObjectMap> children;
	pdgroup->get_children(&children);
	
	long nchildren;
	children->get_length(&nchildren);

	for (long i = 0; i < nchildren; i++)
	{
		CComPtr<IPDObject> object;
		children->item(i, (IUnknown**)&object);

		PDObjectType objectType;
		object->get_objectType(&objectType);

		if (objectType == OBJECT_GROUP)
		{
			CComQIPtr<IPDObjectGroup> pdgroup2 = object;
			SaveObjectGroup(pContent, pdgroup2, matpdf, pageRect);
		}
		else if (objectType == OBJECT_FRAME)
		{
			CComQIPtr<IPDObjectFrame> pdframe = object;

			SaveObjectFrame(pContent, pdframe, matpdf, pageRect);
		}
		else if (objectType == CONTENT_GRAPHIC)
		{
			CComQIPtr<IPDContentGraphic> pdgraphic = object;
			SaveObjectGraphic(pContent, pdgraphic, matpdf, pageRect);
		}
	}
}

HRESULT CPDFExport::Export(TCHAR* pathName, IPDDocument* pddoc)
{
	HRESULT hr = E_FAIL;

//	CPDFDoc* pDoc = new CPDFDoc;

//	pDoc.CreateInstance(__uuidof(pDoc));
	hr = m_pdfdoc.CreateInstance("LPDF.PDFPDDoc");

	if (m_pdfdoc)
	{
		if (SUCCEEDED(m_pdfdoc->Create()))
		{
			m_pddoc = pddoc;

	/*

Title// text string (Optional; PDF 1.1) The document’s title.
Author// text string (Optional) The name of the person who created the document.
Subject// text string (Optional; PDF 1.1) The subject of the document.
Keywords// text string (Optional; PDF 1.1) Keywords associated with the document.
Creator// text string (Optional) If the document was converted to PDF from another format, the
name of the application (for example, Adobe FrameMaker®) that created the
original document from which it was converted.
Producer// text string (Optional) If the document was converted to PDF from another format, the
name of the application (for example, Acrobat Distiller) that converted it to
PDF.
CreationDate// date (Optional) The date and time the document was created, in human-readable
form (see Section 3.8.2, “Dates”).
ModDate// date (Optional; PDF 1.1) The date and time the document was most recently
modi.ed, in human-readable form (see Section 3.8.2, “Dates”).
Trapped// name
  */
			m_pdfdoc->SetInfo(L"Title", L"Test PDF dokument");
			m_pdfdoc->SetInfo(L"Author", L"Sigurd Lerstad");
			m_pdfdoc->SetInfo(L"Creator", L"PageDesigner");
			m_pdfdoc->SetInfo(L"Producer", L"PageDesigner");
			//CreationDate
			//ModDate

		// Save images
			CComPtr<IObjectMap> images;
			m_pddoc->get_images(&images);

			long nimages;
			images->get_length(&nimages);

			for (int nimage = 0; nimage < nimages; nimage++)
			{
				CComPtr<IPDImage> image;
				images->item(nimage, (IUnknown**)&image);
				long width, height;
				image->get_width(&width);
				image->get_height(&height);

				LPDFLib::IPDFCosStreamPtr pCosImage = m_pdfdoc->GetCosDoc()->CosNewStream(VARIANT_TRUE, NULL);
				LPDFLib::IPDFCosDictPtr pDict = pCosImage->CosStreamDict();

				image->SetProp(L"cos-image", (DWORD)pCosImage);

				LPDFLib::IPDFCosNamePtr pType = m_pdfdoc->GetCosDoc()->CosNewName(VARIANT_FALSE, "XObject");
				pDict->CosDictPut(L"Type", pType);

				LPDFLib::IPDFCosNamePtr pSubtype = m_pdfdoc->GetCosDoc()->CosNewName(VARIANT_FALSE, "Image");
				pDict->CosDictPut(L"Subtype", pSubtype);

				LPDFLib::IPDFCosIntegerPtr pWidth = m_pdfdoc->GetCosDoc()->CosNewInteger(VARIANT_FALSE, width);
				pDict->CosDictPut(L"Width", pWidth);

				LPDFLib::IPDFCosIntegerPtr pHeight = m_pdfdoc->GetCosDoc()->CosNewInteger(VARIANT_FALSE, height);
				pDict->CosDictPut(L"Height", pHeight);

				LPDFLib::IPDFCosIntegerPtr pBitsPerComponent = m_pdfdoc->GetCosDoc()->CosNewInteger(VARIANT_FALSE, 8);
				pDict->CosDictPut(L"BitsPerComponent", pBitsPerComponent);

				LPDFLib::IPDFCosNamePtr pColorSpace = m_pdfdoc->GetCosDoc()->CosNewName(VARIANT_FALSE, L"DeviceRGB");
				pDict->CosDictPut(L"ColorSpace", pColorSpace);

				{
					LPDFLib::IPDFCosNamePtr pFilter = m_pdfdoc->GetCosDoc()->CosNewName(VARIANT_FALSE, L"ASCIIHexDecode");
					pDict->CosDictPut("Filter", pFilter);

					Gdiplus::Bitmap* pBitmap;
					image->get_privateImage((DWORD*)&pBitmap);

#if 0
					FILE* fp = pCosImage->OpenFStream("wb");
					if (fp)
					{
						Gdiplus::BitmapData bitmapData;
						pBitmap->LockBits(
							&Gdiplus::Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
							Gdiplus::ImageLockModeRead,
							PixelFormat24bppRGB,//PixelFormat32bppARGB,
							&bitmapData);

						for (int y = 0; y < bitmapData.Height; y++)
						{
							BYTE* src = (BYTE*)bitmapData.Scan0 + bitmapData.Stride*y;

							for (int x = 0; x < bitmapData.Width; x++)
							{
								fprintf(fp, "%2.2X%2.2X%2.2X", src[2], src[1], src[0]);
								src += 3;

								if (((y*bitmapData.Width+x) % 200) == 0)
								{
									fprintf(fp, "\r\n");
								}
							}
						}

						pBitmap->UnlockBits(&bitmapData);

						pCosImage->CloseFStream(fp);
					}
#endif
				}
			}

		// Save pages
			CComPtr<IObjectMap> pages;
			m_pddoc->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			double pageWidth;
			double pageHeight;
			m_pddoc->get_pageWidth(&pageWidth);
			m_pddoc->get_pageHeight(&pageHeight);

			for (int npage = 0; npage < npages; npage++)
			{
				CComPtr<IPDPage> page;
				pages->item(npage, (IUnknown**)&page);

				RectD mediaBox;
				mediaBox.X = 0;
				mediaBox.Y = 0;
				mediaBox.Width = pageWidth;
				mediaBox.Height = pageHeight;

				LPDFLib::IPDFPDPagePtr pPage;
				pPage = m_pdfdoc->CreatePage(npage, 0, 0, pageWidth, pageHeight);
				if (pPage)
				{
					LPDFLib::IPDFEContentPtr pContent;
					pContent = pPage->AcquirePDEContent();

					if (pContent)
					{
						RectD pageRect;
						page->getPageRect(&pageRect);

						CComPtr<IPDMatrix> matpdf;
						{
							CComPtr<IPDMatrix> mat0;
							mat0.CoCreateInstance(CLSID_PDMatrix);

							CComPtr<IPDMatrix> mat1;
							mat0->translate(-pageRect.X, 0, &mat1);

							CComPtr<IPDMatrix> mat2;
							mat1->scaleNonUniform(1, -1, &mat2);

							mat2->translate(0, pageRect.Height, &matpdf);
						}

					// Save objects
						CComPtr<IPDSpread> spread;
						page->get_ownerSpread(&spread);

						CComPtr<IObjectMap> layergroups;
						spread->get_layergroups(&layergroups);

						long nlayergroups;
						layergroups->get_length(&nlayergroups);
						for (long nlayergroup = 0; nlayergroup < nlayergroups; nlayergroup++)
						{
							CComPtr<IPDObjectGroup> pdgroup;
							layergroups->item(nlayergroup, (IUnknown**)&pdgroup);

							SaveObjectGroup(pContent, pdgroup, matpdf, pageRect);
						}

						pPage->ReleasePDEContent();
					}
				}
			}

			hr = m_pdfdoc->Save(pathName);
		}
	}

	return hr;
}
