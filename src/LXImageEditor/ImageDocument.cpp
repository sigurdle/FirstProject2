#include "stdafx.h"
#include "LXImageEditor.h"

#include "ImageDocument.h"
#include "EImageViewGroup.h"
#include "ImageView.h"
#include "ImageLayerGroup.h"
#include "ImageLayerBitmap.h"

#include "..\PageDesigner\psd.h"

namespace System
{
namespace ImageEdit
{

/////////////////////////////////////////////////////////////////////////////

	long BlurARGB(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, LDraw::BBoxi* rect, int featherx, int feathery)
{
	int left = rect->left;
	int top = rect->top;
	int right = rect->right;//inImage->width-1;//r->uRect.right;
	int bottom = rect->bottom;//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

	uint8 * tmask = (uint8*)new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width-1) right = width-1;
	if (bottom > height-1) bottom = height-1;

	int* filterx = new int[featherx*2+1];
	int* filtery = new int[feathery*2+1];

	int i;

	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}

	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}

	int m_alphabytesPerRow = width*4;

// Vertical
	for (int x = left; x <= right; x++)
	{
		uint8 * dest = (tmask + m_alphabytesPerRow*top + x*4);
		uint8 * src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4);

		for (int y = top; y <= bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8 * src2 = (src + top2*inImage->Stride);
	
			uint32	alpha = 0;
			uint32	red = 0;
			uint32	green = 0;
			uint32	blue = 0;

			int	num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				int	radius2 = filtery[y2];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += inImage->Stride;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			dest[3] = (uint8)(blue/num);

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y <= bottom; y++)
	{
		uint8 * src = (tmask + m_alphabytesPerRow*y + left*4);
		uint8 * dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x <= right; x++)
		{
			int	left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int	right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8 * src2 = (src + left2*4);

			uint32	alpha = 0;
			uint32	red = 0;
			uint32	green = 0;
			uint32	blue = 0;

			uint32	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				int	radius2 = filterx[x2+featherx];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += 4;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			dest[3] = (uint8)(blue/num);

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

static long Minimum(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, LDraw::BBoxi* rect, int featherx, int feathery)
{
	int	left = rect->left;
	int	top = rect->top;
	int	right = rect->right;//inImage->width-1;//r->uRect.right;
	int	bottom = rect->bottom;//inImage->height-1;//r->uRect.bottom;

	int	width = inImage->Width;//right-left+1;
	int	height = inImage->Height;//bottom-top+1;

	uint8 * tmask = new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width-1) right = width-1;
	if (bottom > height-1) bottom = height-1;

//	int i;

	int m_alphabytesPerRow = width*4;

// Vertical
	for (int x = left; x <= right; x++)
	{
		uint8 * dest = (tmask + m_alphabytesPerRow*top + x*4);
		uint8 * src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4);

		for (int y = top; y <= bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8 * src2 = (src + top2*inImage->Stride);
	
			uint32	alpha = 255;
			uint32	red = 255;
			uint32	green = 255;
			uint32	blue = 255;

		//	uint	num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				if (src2[0] < alpha) alpha = src2[0];
				if (src2[1] < red) red = src2[1];
				if (src2[2] < green) green = src2[2];
				if (src2[3] < blue) blue = src2[3];

				src2 += inImage->Stride;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y <= bottom; y++)
	{
		uint8 * src = (tmask + m_alphabytesPerRow*y + left*4);
		uint8 * dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x <= right; x++)
		{
			int	left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int	right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8 * src2 = (src + left2*4);

			uint32	alpha = 255;
			uint32	red = 255;
			uint32	green = 255;
			uint32	blue = 255;

		//	uint32	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				if (src2[0] < alpha) alpha = src2[0];
				if (src2[1] < red) red = src2[1];
				if (src2[2] < green) green = src2[2];
				if (src2[3] < blue) blue = src2[3];

				src2 += 4;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

static long Maximum(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, LDraw::BBoxi* rect, int featherx, int feathery)
{
	int	left = rect->left;
	int	top = rect->top;
	int	right = rect->right;//inImage->width-1;//r->uRect.right;
	int	bottom = rect->bottom;//inImage->height-1;//r->uRect.bottom;

	int	width = inImage->Width;//right-left+1;
	int	height = inImage->Height;//bottom-top+1;

	uint8 * tmask = new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width-1) right = width-1;
	if (bottom > height-1) bottom = height-1;

//	int i;

	int m_alphabytesPerRow = width*4;

// Vertical
	for (int x = left; x <= right; x++)
	{
		uint8 * dest = (tmask + m_alphabytesPerRow*top + x*4);
		uint8 * src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4);

		for (int y = top; y <= bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8 * src2 = (src + top2*inImage->Stride);
	
			uint32	alpha = 0;
			uint32	red = 0;
			uint32	green = 0;
			uint32	blue = 0;

		//	int	num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				if (src2[0] > alpha) alpha = src2[0];
				if (src2[1] > red) red = src2[1];
				if (src2[2] > green) green = src2[2];
				if (src2[3] > blue) blue = src2[3];

				src2 += inImage->Stride;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y <= bottom; y++)
	{
		uint8 * src = (tmask + m_alphabytesPerRow*y + left*4);
		uint8 * dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x <= right; x++)
		{
			int	left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int	right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8 * src2 = (src + left2*4);

			uint32	alpha = 0;
			uint32	red = 0;
			uint32	green = 0;
			uint32	blue = 0;

		//	uint32	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				if (src2[0] > alpha) alpha = src2[0];
				if (src2[1] > red) red = src2[1];
				if (src2[2] > green) green = src2[2];
				if (src2[3] > blue) blue = src2[3];

				src2 += 4;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CImageDocument

CImageDocument::CImageDocument()
{
	//m_activeTool = ID_IMAGETOOL_MAGICWAND;
	m_activeToolString = ASTR("CPaintbrushTool");//ID_IMAGETOOL_ELLIPTICALMARQUEE;

	m_pActiveTool = NULL;

	m_imageLayerGroup = NULL;
	m_width = m_height = 0;

	m_pBitmapSelection = NULL;
	m_groupSelection = NULL;

	m_imageLayerGroup = new CImageLayerGroup;

	m_color[0] = 0;
	m_color[1] = 0;
	m_color[2] = 0;
}

CImageDocument::~CImageDocument()
{
	if (m_imageLayerGroup)
	{
//		m_imageLayerGroup->Release();
		m_imageLayerGroup = NULL;
	}
}

CImageLayerGroup* CImageDocument::GetImageLayerGroup()
{
	return m_imageLayerGroup;
}

// IPersistFile

#if 0
STDMETHODIMP CImageDocument::IsDirty(void)
{
	return S_FALSE;
}

STDMETHODIMP CImageDocument::Load(/*[in]*/ LPCOLESTR pszFileName, /*[in]*/ DWORD dwMode)
{
	ASSERT(0);
	return E_FAIL;
#if 0
	CComPtr<IMoniker> moniker;
	ErrorCode hr = CreateURLMoniker(NULL, pszFileName, &moniker);
	if (SUCCEEDED(hr))
	{
		CComPtr<IBindCtx> ctx;
		CreateBindCtx(0, &ctx);

		return Load(TRUE, moniker, ctx, dwMode);
	}

	return hr;
#endif
}

// IPersistMoniker
#endif

ErrorCode CImageDocument::Load(StringW* filename)
{
	ErrorCode hr;

#if 0
	LPBC bindctx = pibc;

	CComPtr<IStream> stream;
	hr = pimkName->BindToStorage(bindctx, NULL, IID_IStream, (void**)&stream);
	if (SUCCEEDED(hr))
	{
		ErrorCode hr;
		CPSDFile* pPSDFile = new CPSDFile;
		if (pPSDFile)
		{
			if (SUCCEEDED(pPSDFile->Load(stream)))
			{
				PSDHEADER hdr;
				pPSDFile->GetFileInfo(&hdr);

				m_width = hdr.cols;
				m_height = hdr.rows;

				long nlayers;
				pPSDFile->GetNumLayers(&nlayers);

				for (int i = 0; i < nlayers; i++)
				{
					CComObject<CImageLayerBitmap>* pLayer;
					CComObject<CImageLayerBitmap>::CreateInstance(&pLayer);
					pLayer->AddRef();

					ILayer* pFileLayer;
					pPSDFile->GetNLayer(i, &pFileLayer);

					pLayer->GetName(&pLayer->m_name);

					LAYERINFO layerinfo;
					pFileLayer->GetLayerInfo(&layerinfo);

					int layerWidth = layerinfo.rect.right - layerinfo.rect.left;
					int layerHeight = layerinfo.rect.bottom - layerinfo.rect.top;
					pLayer->m_width = layerWidth;
					pLayer->m_height = layerHeight;

					pLayer->m_pBitmap = new LDraw::Bitmap(layerWidth, layerHeight, PixelFormat32bppARGB);
					if (pLayer->m_pBitmap)
					{
						LDraw::BitmapData bitmapData;
						if (pLayer->m_pBitmap->LockBits(
							&LDraw::RectI(0, 0, layerWidth, layerHeight),
							LDraw::ImageLockModeWrite,
							PixelFormat32bppARGB,
							&bitmapData) == LDraw::Ok)
						{
							// blue
							pFileLayer->ReadPSDLayerChannel(2, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+0);

							// green
							pFileLayer->ReadPSDLayerChannel(1, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+1);

							// red
							pFileLayer->ReadPSDLayerChannel(0, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+2);

							// alpha
							pFileLayer->ReadPSDLayerChannel(-1, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+3);

							pLayer->m_pBitmap->UnlockBits(&bitmapData);
						}

						pLayer->m_parentGroup = m_imageLayerGroup;
						m_imageLayerGroup->m_subLayers.Add(pLayer);
					}
				}

				hr = S_OK;
			}

			delete pPSDFile;
		}

		if (FAILED(hr))
#endif
		{
			CImageLayerBitmap* pLayer = new CImageLayerBitmap;

			Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
			loader->Load(filename);
			LDraw::Bitmap* pBitmap = loader->GetBitmap();//new LDraw::Bitmap(filename.c_str());
		//	LDraw::Bitmap* pBitmap = new LDraw::Bitmap(1000, 900);
			if (pBitmap->GetPixelFormat() != LDraw::PixelFormat_t::RGBAP_32)
			{
				pLayer->m_pBitmap = pBitmap->Clone(LDraw::PixelFormat_t::RGBAP_32);
				//delete pBitmap;
			}
			else
			{
				pLayer->m_pBitmap = pBitmap;
			}

			pLayer->m_pInitialBitmap = pLayer->m_pBitmap->Clone(LDraw::RectI(0, 0, pLayer->m_pBitmap->GetWidth(), pLayer->m_pBitmap->GetHeight()));//, RGBA_32/*PixelFormat32bppARGB*/);
			{
				LDraw::BitmapData bitmapData;
				pLayer->m_pBitmap->LockBits(
					&LDraw::RectI(0, 0, pLayer->m_pBitmap->GetWidth(), pLayer->m_pBitmap->GetHeight()),
					LDraw::ImageLockModeRead,
					/*PixelFormat32bppARGB,*/ &bitmapData);

				GetAlphaBounds(&bitmapData, &pLayer->m_alphaBounds);

				pLayer->m_pBitmap->UnlockBits(&bitmapData);
			}

			pLayer->m_name = WSTR("Layer 0");

			pLayer->m_width = pLayer->m_pBitmap->GetWidth();
			pLayer->m_height = pLayer->m_pBitmap->GetHeight();

			m_width = pLayer->m_pBitmap->GetWidth();
			m_height = pLayer->m_pBitmap->GetHeight();

			/*
			LDraw::BitmapData data;
			if (pBitmap->LockBits(
				&LDraw::RectI(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
				LDraw::ImageLockModeRead,
				PixelFormat32bppPARGB, &data) != 0)
			{
				ATLASSERT(0);
				return -1;
			}

			pBitmap->UnlockBits(&data);
			*/

			pLayer->m_parentGroup = m_imageLayerGroup;
			m_imageLayerGroup->m_subLayers.Add(pLayer);
		}
#if 0
	}
#endif
	return hr;
}

#if 0
STDMETHODIMP CImageDocument::Save(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ BOOL fRemember)
{
	return S_OK;
}

STDMETHODIMP CImageDocument::SaveCompleted(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc)
{
	return S_OK;
}

STDMETHODIMP CImageDocument::GetCurMoniker(/* [out] */ IMoniker **ppimkName)
{
	return S_OK;
}
#endif

#if 0
// IEDocument
STDMETHODIMP CImageDocument::ShowViews(ILXFrameworkFrame* pFrame)
{
#if 0
	CComObject<CEImageViewGroup>* viewGroup;
	CComObject<CEImageViewGroup>::CreateInstance(&viewGroup);
	if (viewGroup)
	{
		viewGroup->AddRef();

		pFrame->CreateViewGroupSite(viewGroup, &viewGroup->m_spViewGroupSite);

//		m_viewGroups.Add(viewGroup);


		{
		// Layout
			CComObject<CImageView>* layoutView;
			CComObject<CImageView>::CreateInstance(&layoutView);
			if (layoutView)
			{
			//	gApp->m_frame->FindMenu(IDR_IMAGEVIEW, &layoutView->m_menu);
				layoutView->m_document = this;
				/*

				layoutView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(layoutView);

				viewGroup->m_layoutView = layoutView;
				*/

				viewGroup->m_spViewGroupSite->AddView(layoutView);
			}
		}

		//child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);

//		child->UpdateFrameTitle();
	}
#endif

//	CComQIPtr<IUIMDIFrame> frame = pFrame;

	CComQIPtr<ILXAddin> addin = m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CComPtr<ILXFrameworkApp> app;
	lxframe->GetApp(&app);

	CComPtr<ILXUIDocument> appdocument;
	app->get_Document(&appdocument);

//	CComPtr<IUIManager> uiManager;
//	addinSite->GetUIManager((IUnknown**)&uiManager);

	CComObject<CImageView>* layoutView;
	CComObject<CImageView>::CreateInstance(&layoutView);
	if (layoutView)
	{
		CComPtr<ILXUIMDIFrameElement> mdiframe;
		lxframe->get_Element(&mdiframe);

		CComPtr<ILXUIElement> mdiclient;
		mdiframe->getMDIClient(&mdiclient);

		CComPtr<ILXUIElement> mdichild;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"mdichild", (ILDOMElement**)&mdichild);
		if (mdichild)
		{
			/*
			CComPtr<ILDOMElement> edit;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"winedit", &edit);
			edit->setAttribute(L"style", L"width: 60px;");
			mdichild->appendChild(edit, NULL);
			*/

			//mdichild->appendChild(text, NULL);

			CComPtr<ILDOMElement> canvasElement;
			appdocument->createElementNS(NULL, L"div", &canvasElement);
			//canvasElement->setAttribute(L"style", L"display: block; -moz-box-flex: 1;");
		//	canvasElement->setAttribute(L"style", L"display: block; background-color: red; height: 100px;");

			long cookie;
			canvasElement->addBehavior(L"namnam", &CComVariant(layoutView), &cookie);

			mdichild->appendChild(canvasElement, NULL);

			mdiclient->appendChild(mdichild, NULL);
		}

#if 0
		CComPtr<IMenuItem> menu;
		uiManager->FindMenu(_Module.GetResourceInstance(), IDR_IMAGEVIEW, &menu);
		layoutView->m_document = this;

		CComPtr<IUIDlgSite> dlgsite;
		uiManager->CreateDlgSite(NULL, menu, layoutView, &dlgsite);

		CComPtr<IUIMDIChild> childFrame;
		frame->CreateChildFrameDlgSite(dlgsite, &childFrame);
#endif
	}

	return S_OK;
}


STDMETHODIMP CImageDocument::Activate()
{
//	gApp->m_frame->MDIActivate(((CWebXMLViewGroup*)m_viewGroups[0])->m_hWnd);
	return S_OK;
}

STDMETHODIMP CImageDocument::get_undoManager(IUndoManager **pVal)
{
	return S_OK;
}
#endif

#if 0
BEGIN_CMD_MAP(CImageDocument)
	CMD_HANDLER(ID_SELECT_ALL, OnSelectAll)
	CMD_UPDATE(ID_SELECT_ALL, OnSelectAllUpdate)
	CMD_HANDLER(ID_SELECT_DESELECT, OnSelectDeselect)
	CMD_UPDATE(ID_SELECT_DESELECT, OnSelectDeselectUpdate)

	CMD_HANDLER(ID_SELECT_INVERSE, OnSelectInverse)
	CMD_UPDATE(ID_SELECT_INVERSE, OnSelectHasSelectionUpdate)

	CMD_HANDLER(ID_SELECT_FEATHER, OnSelectFeather)
	CMD_UPDATE(ID_SELECT_FEATHER, OnSelectHasSelectionUpdate)
	CMD_HANDLER(ID_SELECT_MODIFY_EXPAND, OnSelectExpand)
	CMD_UPDATE(ID_SELECT_MODIFY_EXPAND, OnSelectHasSelectionUpdate)
	CMD_HANDLER(ID_SELECT_MODIFY_CONTRACT, OnSelectContract)
	CMD_UPDATE(ID_SELECT_MODIFY_CONTRACT, OnSelectHasSelectionUpdate)

/*
	CMD_HANDLER(ID_VIEW_ZOOMIN, OnViewZoomIn)
	CMD_HANDLER(ID_VIEW_ZOOMOUT, OnViewZoomOut)
	CMD_HANDLER(ID_VIEW_ACTUALSIZE, OnViewActualSize)

	CMD_HANDLER(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecial)
	CMD_UPDATE(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecialUpdate)

	CMD_HANDLER(ID_INSERT_IMAGE, OnInsertImage)
	CMD_HANDLER(ID_TABLE_INSERT_TABLE, OnInsertTable)

	CMD_HANDLER(ID_OBJECT_CONVERTTOPATH, OnObjectConvertToPath)
	CMD_UPDATE(ID_OBJECT_CONVERTTOPATH, OnObjectConvertToPathUpdate)

	CMD_HANDLER(ID_OBJECT_EDITPAINT, OnEditPaint)
	CMD_HANDLER(ID_OBJECT_EDITMASK, OnObjectEditMask)
	CMD_HANDLER(ID_OBJECT_EDITCLIPPINGPATH, OnObjectEditClippingPath)
	CMD_HANDLER(ID_OBJECT_EDITFILTER, OnObjectEditFilter)
	CMD_UPDATE(ID_OBJECT_EDITPAINT, OnObjectEditPaintUpdate)
	CMD_UPDATE(ID_OBJECT_EDITMASK, OnObjectEditMaskUpdate)
	CMD_UPDATE(ID_OBJECT_EDITCLIPPINGPATH, OnObjectEditClippingPathUpdate)
	CMD_UPDATE(ID_OBJECT_EDITFILTER, OnObjectEditFilterUpdate)

	CMD_HANDLER(ID_VIEW_SHOWMARKUP, OnShowMarkup)
	CMD_UPDATE(ID_VIEW_SHOWMARKUP, OnShowMarkupUpdate)
	*/
END_CMD_MAP()
#endif

void CImageDocument::OnSelectAll(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled)
{
	if (m_pBitmapSelection == NULL)
	{
		m_pBitmapSelection = new LDraw::Bitmap(m_width, m_height, LDraw::PixelFormat_t::GRAY_8);

		m_groupSelection = new CGroupImageObject;
		//m_groupSelection->AddRef();
	}

	if (m_pBitmapSelection)
	{
		LDraw::BitmapData data;
		m_pBitmapSelection->LockBits(
			&LDraw::RectI(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()),
			LDraw::ImageLockModeWrite,
			/*PixelFormat32bppARGB,*/ &data);

		for (int y = 0; y < data.Height; y++)
		{
			LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)((uint8*)data.Scan0 + data.Stride*y);

			for (int x = 0; x < data.Width; x++)
			{
				p->a = 255;
				p->r = 255;
				p->g = 255;
				p->b = 255;
				p++;
			}
		}

		m_pBitmapSelection->UnlockBits(&data);
	}
}

/*
void CImageDocument::OnSelectAllUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
*/

void CImageDocument::OnSelectDeselect(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled)
{
	if (m_pBitmapSelection)
	{
	//	delete m_pBitmapSelection;
		m_pBitmapSelection = NULL;

	// TODO
	// UpdateAllViews();
	}
}

/*
void CImageDocument::OnSelectDeselectUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pBitmapSelection)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}
*/

void CImageDocument::OnSelectInverse(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled)
{
	if (m_pBitmapSelection)
	{
		LDraw::BitmapData data;
		m_pBitmapSelection->LockBits(
			&LDraw::RectI(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()),
			LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
			/*PixelFormat32bppARGB,*/ &data);

		for (int y = 0; y < data.Height; y++)
		{
			LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)((uint8*)data.Scan0 + data.Stride*y);

			for (int x = 0; x < data.Width; x++)
			{
				p->a = 255 - p->a;
				p++;
			}
		}

		m_pBitmapSelection->UnlockBits(&data);

		// TODO
	// UpdateAllViews();
	}
}

#if 0
#include "FeatherSelectionDlg.h"
#include "ExpandSelectionDlg.h"
#include "ContractSelectionDlg.h"

LRESULT CImageDocument::OnSelectFeather(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pBitmapSelection)
	{
		CFeatherSelectionDlg dlg;
		dlg.m_radius = 1;

		if (dlg.DoModal() == IDOK)
		{
			LDraw::BitmapData data;
			m_pBitmapSelection->LockBits(
				&LDraw::RectI(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()),
				LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
				PixelFormat32bppARGB, &data);

			BlurARGB(&data, &data, &CRect(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()), dlg.m_radius, dlg.m_radius);

			m_pBitmapSelection->UnlockBits(&data);

		// TODO
		// UpdateAllViews();
		}
	}

	return 0;
}

LRESULT CImageDocument::OnSelectExpand(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pBitmapSelection)
	{
		CExpandSelectionDlg dlg;
		dlg.m_radius = 1;

		if (dlg.DoModal() == IDOK)
		{
			LDraw::BitmapData data;
			m_pBitmapSelection->LockBits(
				&LDraw::RectI(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()),
				LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
				PixelFormat32bppARGB, &data);

			Maximum(&data, &data, &CRect(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()), dlg.m_radius, dlg.m_radius);

			m_pBitmapSelection->UnlockBits(&data);

		// TODO
		// UpdateAllViews();
		}
	}

	return 0;
}

LRESULT CImageDocument::OnSelectContract(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pBitmapSelection)
	{
		CContractSelectionDlg dlg;
		dlg.m_radius = 1;

		if (dlg.DoModal() == IDOK)
		{
			LDraw::BitmapData data;
			m_pBitmapSelection->LockBits(
				&LDraw::RectI(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()),
				LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
				PixelFormat32bppARGB, &data);

			Minimum(&data, &data, &CRect(0, 0, m_pBitmapSelection->GetWidth(), m_pBitmapSelection->GetHeight()), dlg.m_radius, dlg.m_radius);

			m_pBitmapSelection->UnlockBits(&data);

		// TODO
		// UpdateAllViews();
		}
	}

	return 0;
}

void CImageDocument::OnSelectHasSelectionUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_pBitmapSelection)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}
#endif

}	// ImageEdit
}
