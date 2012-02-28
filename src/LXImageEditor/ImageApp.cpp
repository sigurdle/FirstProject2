#include "stdafx.h"
#include "LXImageEditor.h"

#include "ImageApp.h"

namespace System
{
namespace ImageEdit
{

#if 0
#include "ImageToolsDlg.h"
#include "BrushDlg.h"
#include "BrushTipShapeDlg.h"
#include "ImageLayersDlg.h"
#include "ImageObjectsDlg.h"
#include "ImageColorDlg.h"
#endif

#define PREC 16
#define PRECMASK    ((1<<PREC)-1)

void SubPixelSample(ImageDef* inImage, long xpos, long ypos, LDraw::PixelRGBAP_32* dest)
{
	uint8* imageBits = (uint8*)inImage->Scan0;
	int imageRowBytes = inImage->Stride;

	int srcx = xpos>>PREC;
	int srcy = ypos>>PREC;

/*
	if ((srcx < 0) ||
		(srcy < 0) ||
		(srcx > inImage->width-1) ||
		(srcy > inImage->height-1))
	{
		dest->alpha = 0;
		return 1;
	}
*/

	LDraw::PixelRGBAP_32* v11;
	LDraw::PixelRGBAP_32* v12;
	LDraw::PixelRGBAP_32* v21;
	LDraw::PixelRGBAP_32* v22;

	v11 = (LDraw::PixelRGBAP_32*)(imageBits + srcy*imageRowBytes + srcx*4);

//	if (srcx > inImage->width-2)
//		v12 = v11;
//	else
		v12 = (LDraw::PixelRGBAP_32*)((uint8*)v11 + 4);

//	if (srcy > inImage->height-2)
//		v21 = v11;
//	else
		v21 = (LDraw::PixelRGBAP_32*)((uint8*)v11 + imageRowBytes);

//	if (srcx > inImage->width-2)
//		v22 = v21;
//	else
		v22 = (LDraw::PixelRGBAP_32*)((uint8*)v21 + 4);

	LDraw::PixelRGBAP_32 v1;
	LDraw::PixelRGBAP_32 v2;

	v1.a = v11->a + ((((short)v12->a - v11->a) * (xpos & PRECMASK)) >> PREC);
	v1.r = v11->r + ((((short)v12->r - v11->r) * (xpos & PRECMASK)) >> PREC);
	v1.g = v11->g + ((((short)v12->g - v11->g) * (xpos & PRECMASK)) >> PREC);
	v1.b = v11->b + ((((short)v12->b - v11->b) * (xpos & PRECMASK)) >> PREC);
	
	v2.a = v21->a + ((((short)v22->a - v21->a) * (xpos & PRECMASK)) >> PREC);
	v2.r = v21->r + ((((short)v22->r - v21->r) * (xpos & PRECMASK)) >> PREC);
	v2.g = v21->g + ((((short)v22->g - v21->g) * (xpos & PRECMASK)) >> PREC);
	v2.b = v21->b + ((((short)v22->b - v21->b) * (xpos & PRECMASK)) >> PREC);
	
	dest->a = v1.a + ((((short)v2.a - v1.a) * (ypos & PRECMASK)) >> PREC);
	dest->r = v1.r + ((((short)v2.r - v1.r) * (ypos & PRECMASK)) >> PREC);
	dest->g = v1.g + ((((short)v2.g - v1.g) * (ypos & PRECMASK)) >> PREC);
	dest->b = v1.b + ((((short)v2.b - v1.b) * (ypos & PRECMASK)) >> PREC);
}

#if 0
void SetSubPixelSample(ImageDef* inImage, long xpos, long ypos, LDraw::PixelRGBAP_32* p)
{
	LPBYTE imageBits = (LPBYTE)inImage->Scan0;
	int imageRowBytes = inImage->Stride;

	int srcx = xpos>>PREC;
	int srcy = ypos>>PREC;

/*
	if ((srcx < 0) ||
		(srcy < 0) ||
		(srcx > inImage->width-1) ||
		(srcy > inImage->height-1))
	{
		dest->alpha = 0;
		return 1;
	}
*/

	LDraw::PixelRGBAP_32* v11;
	LDraw::PixelRGBAP_32* v12;
	LDraw::PixelRGBAP_32* v21;
	LDraw::PixelRGBAP_32* v22;

	v11 = (LDraw::PixelRGBAP_32*)(imageBits + srcy*imageRowBytes + srcx*4);

//	if (srcx > inImage->width-2)
//		v12 = v11;
//	else
		v12 = (LDraw::PixelRGBAP_32*)((LPBYTE)v11 + 4);

//	if (srcy > inImage->height-2)
//		v21 = v11;
//	else
		v21 = (LDraw::PixelRGBAP_32*)((LPBYTE)v11 + imageRowBytes);

//	if (srcx > inImage->width-2)
//		v22 = v21;
//	else
		v22 = (LDraw::PixelRGBAP_32*)((LPBYTE)v21 + 4);

	v11->alpha = v11->alpha + ((((short)p->alpha - v11->alpha) * (xpos & PRECMASK)) >> PREC);
	v11->red = v11->red + ((((short)p->red - v11->red) * (xpos & PRECMASK)) >> PREC);
	v11->green = v11->green + ((((short)p->green - v11->green) * (xpos & PRECMASK)) >> PREC);
	v11->blue = v11->blue + ((((short)p->blue - v11->blue) * (xpos & PRECMASK)) >> PREC);

	v12->alpha = v12->alpha + ((((short)p->alpha - v12->alpha) * (xpos & PRECMASK)) >> PREC);
	v12->red = v12->red + ((((short)p->red - v12->red) * (xpos & PRECMASK)) >> PREC);
	v12->green = v12->green + ((((short)p->green - v12->green) * (xpos & PRECMASK)) >> PREC);
	v12->blue = v12->blue + ((((short)p->blue - v12->blue) * (xpos & PRECMASK)) >> PREC);

	LDraw::PixelRGBAP_32 v1;
	LDraw::PixelRGBAP_32 v2;

	v1.alpha = v11->alpha + ((((short)v12->alpha - v11->alpha) * (xpos & PRECMASK)) >> PREC);
	v1.red = v11->red + ((((short)v12->red - v11->red) * (xpos & PRECMASK)) >> PREC);
	v1.green = v11->green + ((((short)v12->green - v11->green) * (xpos & PRECMASK)) >> PREC);
	v1.blue = v11->blue + ((((short)v12->blue - v11->blue) * (xpos & PRECMASK)) >> PREC);

	v2.alpha = v21->alpha + ((((short)v22->alpha - v21->alpha) * (xpos & PRECMASK)) >> PREC);
	v2.red = v21->red + ((((short)v22->red - v21->red) * (xpos & PRECMASK)) >> PREC);
	v2.green = v21->green + ((((short)v22->green - v21->green) * (xpos & PRECMASK)) >> PREC);
	v2.blue = v21->blue + ((((short)v22->blue - v21->blue) * (xpos & PRECMASK)) >> PREC);

	dest->alpha = v1.alpha + ((((short)v2.alpha - v1.alpha) * (ypos & PRECMASK)) >> PREC);
	dest->red = v1.red + ((((short)v2.red - v1.red) * (ypos & PRECMASK)) >> PREC);
	dest->green = v1.green + ((((short)v2.green - v1.green) * (ypos & PRECMASK)) >> PREC);
	dest->blue = v1.blue + ((((short)v2.blue - v1.blue) * (ypos & PRECMASK)) >> PREC);
}
#endif

//////////////////////////////////////////////////

class CPaintMethodNormal : public IPaintMethod
{
public:
	LONG FilterRect(LPPFILTERRECORD r)
	{
		if (!r->brushImage) return -1;

		int left = r->uRect.X;
		int top = r->uRect.Y;
		int right = r->uRect.GetRight();
		int bottom = r->uRect.GetBottom();

		int brushy = r->boffset_y;

		for (int y = top; y <= bottom; y++, brushy++)
		{
			LDraw::PixelRGBAP_32* outPixel = (LDraw::PixelRGBAP_32*)((uint8*)r->outImage->Scan0 + r->outImage->Stride*brushy + r->boffset_x*4);
			LDraw::PixelRGBAP_32* brushPixel = (LDraw::PixelRGBAP_32*)((uint8*)r->brushImage->Scan0 + r->brushImage->Stride*brushy + r->boffset_x*4);

			for (int x = left; x <= right; x++)
			{
			//	ASSERT(!IsBadWritePtr(outPixel, 4) && !IsBadWritePtr(brushPixel, 4));

				outPixel->r = brushPixel->r;
				outPixel->g = brushPixel->g;
				outPixel->b = brushPixel->b;
				outPixel->a = 255;

				outPixel++;
				brushPixel++;
			}
		}

		return 0;
	}

};

class CPaintMethodErase : public IPaintMethod
{
public:
	LONG FilterRect(LPPFILTERRECORD r)
	{
		int left = r->uRect.X;
		int top = r->uRect.Y;
		int right = r->uRect.GetRight();
		int bottom = r->uRect.GetBottom();

		long eraseTo = 0;
	//	r->layer->GetParamTags(r->paramID[0], (PARAM_POPUP_Value), &eraseTo, (TAG_DONE));

		int brushy = r->boffset_y;

		bool bDepth = (r->inDepth && r->outDepth);

		if ((eraseTo == 0) || (r->bgImage == NULL))	// Erase to Transparent
		{
			for (int y = top; y <= bottom; y++, brushy++)
			{
				LDraw::PixelRGBAP_32* outPixel = (LDraw::PixelRGBAP_32*)((uint8*)r->outImage->Scan0 + r->outImage->Stride*brushy + r->boffset_x*4);

				for (int x = left; x <= right; x++)
				{
					outPixel->a = 0;
					outPixel++;
				}

				if (bDepth)
				{
					uint16* outDepth = (uint16*)((uint8*)r->outDepth->Scan0 + r->outDepth->Stride*brushy + r->boffset_x*2);

					for (int x = left; x <= right; x++)
					{
						*outDepth++ = 0;
					}
				}
			}
		}
#if 0
		else if (eraseTo == 1)	// Erase To background
		{
			for (int y = top; y <= bottom; y++, brushy++)
			{
				LDraw::PixelRGBAP_32* bgPixel = (LDraw::PixelRGBAP_32*)(r->bgImage->data + r->bgImage->rowbytes*y + left*4);
				LDraw::PixelRGBAP_32* outPixel = (LDraw::PixelRGBAP_32*)(r->outImage->data + r->outImage->rowbytes*brushy + r->boffset_x*4);

				for (int x = left; x <= right; x++)
				{
					*outPixel = *bgPixel;

					bgPixel++;
					outPixel++;
				}
			}
		}
#endif

		return 0;
	}
};

class CPaintMethodSmear : public IPaintMethod
{
public:
	LONG FilterRect(LPPFILTERRECORD r)
	{
		bool bDepth = (r->inDepth && r->outDepth);

		int diffx = r->dx;
		int diffy = r->dy;

		int left = r->uRect.X;
		int top = r->uRect.Y;
		int right = r->uRect.GetRight();
		int bottom = r->uRect.GetBottom();

		int brushy = r->boffset_y;

		int iny = top-diffy;

		for (int y = top; y <= bottom; y++, brushy++, iny++)
		{
			int inx = left-diffx;

			LDraw::PixelRGBAP_32* inPixel = (LDraw::PixelRGBAP_32*)((uint8*)r->inImage->Scan0 + r->inImage->Stride*iny + inx*4);
			LDraw::PixelRGBAP_32* outPixel = (LDraw::PixelRGBAP_32*)((uint8*)r->outImage->Scan0 + r->outImage->Stride*brushy + r->boffset_x*4);

			uint16 * inDepth, * outDepth;
			if (bDepth)
			{
				inDepth = (uint16*)((uint8*)r->inDepth->Scan0 + r->inDepth->Stride*iny + inx*2);
				outDepth = (uint16*)((uint8*)r->outDepth->Scan0 + r->outDepth->Stride*brushy + r->boffset_x*2);
			}

			if ((iny >= 0 && iny < r->sourceHeight))
			{
				for (int x = left; x <= right; x++, inx++)
				{
					if ((inx >= 0 && inx < r->sourceWidth))
					{
						*outPixel = *inPixel;
						if (bDepth) *outDepth = *inDepth;
					}
					else
					{
						outPixel->a = 0;
						if (bDepth) *outDepth = 0;
					}

					inPixel++;
					outPixel++;

					inDepth++;
					outDepth++;
				}
			}
			else
			{
				for (int x = left; x <= right; x++, inx++)
				{
					outPixel->a = 0;
					outPixel++;

					if (bDepth)
					{
						*outDepth = 0;
						outDepth++;
					}
				}
			}
		}

		return 0;
	}
};

class CPaintMethodBulge : public IPaintMethod
{
public:
	long FilterRect(LPPFILTERRECORD r)
	{
		int left = r->uRect.X;
		int top = r->uRect.Y;
		int right = r->uRect.GetRight();
		int bottom = r->uRect.GetBottom();

		long lcx = (left + (right-left)/2);// <<16;
		long lcy = (top + (bottom-top)/2);// <<16;
		long size = (right-left)/2;// <<16;;
		//long strength = (long)(160*65536);
		//long langle = 0;
		/*
		long brightness = 0;

		brightness >>= 16;
		*/

		double cx = lcx / (long)r->x_sampling;
		double cy = lcy / (long)r->y_sampling;
		int radius = size / (long)r->x_sampling;
		double dstrength = 1.1;//(strength/65536.0)/100.0;

		/*
		double dlangle = (langle>>16) * (M_PI/180);

		while (dlangle < 0) dlangle += 2*M_PI;
		while (dlangle >= 2*M_PI) dlangle -= 2*M_PI;
		*/

		bool bDepth = (r->outDepth && r->inDepth);

		int radius2 = radius*radius;

		int brushy = r->boffset_y;

		for (int y = top; y <= bottom; y++, brushy++)
		{
	//		LDraw::PixelRGBAP_32* out = (LDraw::PixelRGBAP_32*)(r->outImage->data + r->outImage->rowbytes*brushy + r->boffset_x*4);
	//		LDraw::PixelRGBAP_32* brushPixel = (LDraw::PixelRGBAP_32*)(r->brushImage->data + r->brushImage->rowbytes*brushy + r->boffset_x*4);

			LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)((uint8*)r->inImage->Scan0 + r->inImage->Stride*y + left*4);
			LDraw::PixelRGBAP_32* out = (LDraw::PixelRGBAP_32*)((uint8*)r->outImage->Scan0 + r->outImage->Stride*brushy + r->boffset_x*4);

			for (int x = left; x <= right; x++)
	/*
			LPWORD outd, ind;
			if (bDepth)
			{
				outd = (LPWORD)(r->outDepth->data + r->outDepth->rowbytes*y + left*2);
				ind = (LPWORD)(r->inDepth->data + r->inDepth->rowbytes*y + left*2);
			}
	*/
	//		for (int x = left; x <= right; x++)
			{
				int dx = (int)(x-cx);
				int dy = (int)(y-cy);

				int _distance = dx*dx + dy*dy;

				if (_distance < radius2)
				{
					double distance = sqrt((double)_distance);

					if (distance == 0.0) distance = 0.001;

					double newdistance = pow(distance/radius, dstrength)*radius;
					ASSERT((newdistance >= 0) && (newdistance <= radius));

					double dnx = cx + (dx * newdistance) / distance;
					double dny = cy + (dy * newdistance) / distance;

					int nx = (int)(dnx);
					int ny = (int)(dny);

					if ((nx >= 0) && (ny >= 0) &&
						(nx < r->inImage->Width-1) && (ny < r->inImage->Height-1))
					{
						LDraw::PixelRGBAP_32	in2;

						SubPixelSample(r->inImage, (long)(dnx*65536), (long)(dny*65536), &in2);

						*out = in2;
							/*
							out->red = min(max(in2.red+off, 0), 255);
							out->green = min(max(in2.green+off, 0), 255);
							out->blue = min(max(in2.blue+off, 0), 255);
							out->alpha = in2.alpha;
							*/
	/*
							if (bDepth)	// Depth
							{
								WORD ind2;
								r->inDepth->SubPixelSampleGRAY16((long)(dnx*65536), (long)(dny*65536), &ind2);

								*outd = ind2;
							}
	*/				
					}
					else
						out->a = 0;
				}
				else
				{
					*out = *in;
				//	if (bDepth) *outd = *ind;
				}

				in++;
				out++;

			//	ind++;
			//	outd++;
			}
		}

		return 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// CImageApp

CImageApp::CImageApp()
{
	m_pActiveTool = NULL;
//		m_activeTool = ID_IMAGETOOL_SELECT;

	m_pActivePaintMethod = NULL;
	m_brushSize = 10;
	m_pActiveBrushTip = NULL;

	{
		{
			CPaintMethod* p = new CPaintMethod;
			p->m_name = WSTR("Normal");
			p->m_method = new CPaintMethodNormal;
			m_paintMethods.Add(p);
		}

		{
			CPaintMethod* p = new CPaintMethod;
			p->m_name = WSTR("Erase");
			p->m_method = new CPaintMethodErase;
			m_paintMethods.Add(p);
		}

		{
			CPaintMethod* p = new CPaintMethod;
			p->m_name = WSTR("Smear");
			p->m_method = new CPaintMethodSmear;
			m_paintMethods.Add(p);
		}

		{
			CPaintMethod* p = new CPaintMethod;
			p->m_name = WSTR("Bulge");
			p->m_method = new CPaintMethodBulge;
			m_paintMethods.Add(p);
		}
	}

	{
		{
			CCircularBrushTip* p = new CCircularBrushTip;

			m_customBrushTips.Add(p);

			m_pActiveBrushTip = p;
		}

		{
			CCustomBrushTip* pCustom = new CCustomBrushTip;
			pCustom->m_filename = WSTR("C:\\Documents and Settings\\Administrator.MMSTUDIO.000\\My Documents\\My Pictures\\brush1.png");

			m_customBrushTips.Add(pCustom);

		}

		{
			{
				CImageBrush* p = new CImageBrush;
				p->m_brushSize = 1;
				p->m_pBrushTip = m_customBrushTips[0];
				p->m_pMethod = m_paintMethods[0];
				m_brushes.Add(p);
			}

			{
				CImageBrush* p = new CImageBrush;
				p->m_brushSize = 3;
				p->m_pBrushTip = m_customBrushTips[0];
				p->m_pMethod = m_paintMethods[0];
				m_brushes.Add(p);
			}

			{
				CImageBrush* p = new CImageBrush;
				p->m_brushSize = 5;
				p->m_pBrushTip = m_customBrushTips[0];
				p->m_pMethod = m_paintMethods[0];
				m_brushes.Add(p);
			}

			{
				CImageBrush* p = new CImageBrush;
				p->m_brushSize = 9;
				p->m_pBrushTip = m_customBrushTips[0];
				p->m_pMethod = m_paintMethods[0];
				m_brushes.Add(p);
			}

			{
				CImageBrush* p = new CImageBrush;
				p->m_brushSize = 13;
				p->m_pBrushTip = m_customBrushTips[0];
				p->m_pMethod = m_paintMethods[0];
				m_brushes.Add(p);
			}

			{
				CImageBrush* p = new CImageBrush;
				p->m_brushSize = 19;
				p->m_pBrushTip = m_customBrushTips[0];
				p->m_pMethod = m_paintMethods[0];
				m_brushes.Add(p);
			}

			{
				CImageBrush* p = new CImageBrush;
				p->m_brushSize = 32;
				p->m_pBrushTip = m_customBrushTips[1];
				p->m_pMethod = m_paintMethods[0];
				m_brushes.Add(p);
			}
		}
	}
}

/*
STDMETHODIMP CImageApp::SetUIManager(IUIManager* newVal)
{
	m_uiManager = newVal;

	return S_OK;
}
*/

#if 0
STDMETHODIMP CImageApp::CreateDlg(UINT nID, IUIDlg* *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	switch (nID)
	{
	case 70:
		{
			CComPtr<IUIMenuDlg> menuDlg;
			m_uiManager->CreateMenuDlg(&menuDlg);

			CComPtr<IMenuItem> menuItem;
			m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_MAINFRAME, &menuItem);

			CComPtr<IMenuItem> menuItem0 = menuItem;
			//menuItem->GetSubMenu(0, &menuItem0);

			menuDlg->InitMenu(menuItem0, this/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);

			(*pVal = menuDlg)->AddRef();
		}
		break;

	case 100:
		{
			CComObject<CImageToolsDlg>* p;
			CComObject<CImageToolsDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
		}
		break;

	case 101:
		{
			CComObject<CBrushDlg>* p;
			CComObject<CBrushDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
		}
		break;

	case 102:
		{
			CComObject<CImageLayersDlg>* p;
			CComObject<CImageLayersDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				p->m_app = this;
			}
		}
		break;

	case 103:
		{
			CComObject<CImageObjectsDlg>* p;
			CComObject<CImageObjectsDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
		}
		break;

	case 104:
		{
			CComObject<CImageColorDlg>* p;
			CComObject<CImageColorDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
		}
		break;

	case 105:
		{
			CComObject<CBrushTipShapeDlg>* p;
			CComObject<CBrushTipShapeDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
		}
		break;
	}
	return 0;
}
#endif

#if 0
STDMETHODIMP CImageApp::OnCreateFrame()
{
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	{
		CComPtr<IUIMenuDlg> menuDlg;
		m_uiManager->CreateMenuDlg(&menuDlg);

		CComPtr<IMenuItem> menuItem;
		m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_MAINFRAME, &menuItem);

		CComPtr<IMenuItem> menuItem0 = menuItem;
		//menuItem->GetSubMenu(0, &menuItem0);

		menuDlg->InitMenu(menuItem0, this/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(L"MenuBar", NULL, menuDlg, &dlgsite);

		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}

#if 0
	{
		CComPtr<IUIRegisteredDlg> rdlg;
		m_uiManager->RegisterDlg(70/*TODO?IDR_MAINFRAME*/, L"Menubar", 0, &rdlg);

		CComPtr<IUIDlg> dlg;
		rdlg->CreateDlg(&dlg);

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(dlg, &dlgsite);

		CComQIPtr<IUIFrame> frame = m_frame;
		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}

	{
		CComPtr<IUIDlgSheet> sheet;
		m_uiManager->CreateDlgSheet(NULL, &sheet);
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			m_uiManager->RegisterDlg(100, L"Tools", 0, &rdlg);
			sheet->AddPage(rdlg, NULL);
		}

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(sheet, &dlgsite);

		CComQIPtr<IUIFrame> frame = m_frame;
		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}

	{
		CComPtr<IUIDlgSheet> sheet;
		m_uiManager->CreateDlgSheet(NULL, &sheet);
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			m_uiManager->RegisterDlg(101, L"Brush", 0, &rdlg);
			sheet->AddPage(rdlg, NULL);
		}

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(sheet, &dlgsite);

		CComQIPtr<IUIFrame> frame = m_frame;
		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}

	{
		CComPtr<IUIDlgSheet> sheet;
		m_uiManager->CreateDlgSheet(NULL, &sheet);
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			m_uiManager->RegisterDlg(102, L"Layers", 0, &rdlg);
			sheet->AddPage(rdlg, NULL);
		}

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(sheet, &dlgsite);

		CComQIPtr<IUIFrame> frame = m_frame;
		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}

	{
		CComPtr<IUIDlgSheet> sheet;
		m_uiManager->CreateDlgSheet(NULL, &sheet);
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			m_uiManager->RegisterDlg(103, L"Objects", 0, &rdlg);
			sheet->AddPage(rdlg, NULL);
		}

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(sheet, &dlgsite);

		CComQIPtr<IUIFrame> frame = m_frame;
		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}

	{
		CComPtr<IUIDlgSheet> sheet;
		m_uiManager->CreateDlgSheet(NULL, &sheet);
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			m_uiManager->RegisterDlg(104, L"Color", 0, &rdlg);
			sheet->AddPage(rdlg, NULL);
		}

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(sheet, &dlgsite);

		CComQIPtr<IUIFrame> frame = m_frame;
		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}

	{
		CComPtr<IUIDlgSheet> sheet;
		m_uiManager->CreateDlgSheet(NULL, &sheet);
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			m_uiManager->RegisterDlg(105, L"Brush Tip Shape", 0, &rdlg);
			sheet->AddPage(rdlg, NULL);
		}

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(sheet, &dlgsite);

		CComQIPtr<IUIFrame> frame = m_frame;
		frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}
#endif

	return S_OK;
}
#endif

#if 0
STDMETHODIMP CImageApp::BindToObjectMoniker(IMoniker* moniker, IBindCtx* bindctx, IUnknown* *pVal)
{
	HRESULT hr = 0;

	CComPtr<IUnknown> spUnknown;
	spUnknown.CoCreateInstance(CLSID_ImageDocument);

	CComQIPtr<IPersistMoniker> persist = spUnknown;
	persist->Load(TRUE, moniker, bindctx, 0);

	/*
	hr =  moniker->BindToObject(bindctx, NULL, IID_IUnknown, (void**)&spUnknown);
	if (SUCCEEDED(hr))
	{
		CComQIPtr<IEDocument> document = spUnknown;
		document->SetApp(this);
	}
	*/

	*pVal = spUnknown;
	if (*pVal) (*pVal)->AddRef();

	return hr;
}
#endif

#if 0
// ICommandTarget
STDMETHODIMP CImageApp::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	/*
// Try document
	CComQIPtr<ICommandTarget> target = m_document->GetUnknown();
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;
	*/

	return S_OK;
}
#endif

#if 0
BEGIN_CMD_MAP(CImageApp)

// File
//	CMD_HANDLER(ID_FILE_NEW, OnFileNew)
	CMD_HANDLER(ID_FILE_OPEN, OnFileOpen)

	CMD_HANDLER(ID_IMAGETOOL_SELECT, OnTool)
	CMD_HANDLER(ID_IMAGETOOL_RECTANGULARMARQUEE, OnTool)
	CMD_HANDLER(ID_IMAGETOOL_ELLIPTICALMARQUEE, OnTool)
	CMD_HANDLER(ID_IMAGETOOL_MAGICWAND, OnTool)
	CMD_HANDLER(ID_IMAGETOOL_PAINTBRUSH, OnTool)
	CMD_HANDLER(ID_IMAGETOOL_ELLIPSE, OnTool)

	CMD_UPDATE(ID_IMAGETOOL_SELECT, OnToolUpdate)
	CMD_UPDATE(ID_IMAGETOOL_RECTANGULARMARQUEE, OnToolUpdate)
	CMD_UPDATE(ID_IMAGETOOL_ELLIPTICALMARQUEE, OnToolUpdate)
	CMD_UPDATE(ID_IMAGETOOL_MAGICWAND, OnToolUpdate)
	CMD_UPDATE(ID_IMAGETOOL_PAINTBRUSH, OnToolUpdate)
	CMD_UPDATE(ID_IMAGETOOL_ELLIPSE, OnToolUpdate)
END_CMD_MAP()
#endif

void CImageApp::OnFileOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
#if 0
	USES_CONVERSION;

	//CComPtr<ILXFrameworkFrame> lxframe;
	//m_spAddinSite->GetFrame(&lxframe);

	HWND hWnd = NULL;
	//lxframe->GetWindow(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"PhotoShop (*.psd)\0*.psd\0"
												"IFF (*.iff)\0*.iff\0"
												"JPEG (*.jpg,*.jpeg)\0*.jpg;*.jpeg\0"
												"GIF (*.gif)\0*.gif\0"
												"PNG (*.png)\0*.png\0"
												"TIFF (*.tif,*.tiff)\0*.tif;*.tiff\0"
												"PCX (*.pcx)\0*.pcx\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;//sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	
	if (GetOpenFileName(&ofn))
	{
		//CComQIPtr<IEFrame> eframe = lxframe;

		CComPtr<IEDocument> document;
		HRESULT hr = document.CoCreateInstance(CLSID_ImageDocument);
		if (SUCCEEDED(hr))
		{
			CComQIPtr<IPersistFile> persistFile = document;
			hr = persistFile->Load(A2W(sbuffer), STGM_READ);
			if (SUCCEEDED(hr))
			{
				document->SetApp(this);
#if 0
				document->ShowViews(lxframe);
#endif
			}
		}

		document.Detach();	// TODO, add in a list

		if (FAILED(hr))
		{
			MessageBox(hWnd, "Failed to load document", "LXImageEditor", MB_OK);
		}
	}

#endif
}

void CImageApp::OnTool(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled)
{
}

#if 0
void CImageApp::OnToolUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	if (m_pActiveTool)
	{
		pCmdUI->SetCheck(iid == m_pActiveTool->m_nID);
	}
}
#endif

}
}
