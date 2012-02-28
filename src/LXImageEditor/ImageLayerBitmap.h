#ifndef __IMAGELAYERBITMAP_H_
#define __IMAGELAYERBITMAP_H_

//#include "resource.h"       // main symbols

//#include "ImageDocument.h"	// TODO remove
//#include "ImageApp.h"	// TODO remove

namespace System
{
namespace ImageEdit
{

class CPaintMethod;

class CImageObject
{
public:
	LDraw::RectI m_imageRect;
	LDraw::Bitmap* m_imageBitmap;
};

class ImageEditorExt CStrokeObject : public UI::Control, public CImageObject
{
public:
	CTOR CStrokeObject()
	{
		m_pBrushTip = NULL;

		m_effectRecord = NULL;
		m_pMethod = NULL;

		m_pBrushBitmap = NULL;
	}

	~CStrokeObject()
	{
		if (m_pBrushTip)
		{
			m_pBrushTip->m_refcount--;
		}
	}

	virtual void OnRender(UI::Graphics* pGraphics);

	LPPFILTERRECORD m_effectRecord;
	CPaintMethod* m_pMethod;

	LDraw::Bitmap* m_pBrushBitmap;	// TODO, have an array of cached variants of this bitmap
	double m_brushSize;
	uint8 m_color[3];

	CBrushTip* m_pBrushTip;
	vector<LDraw::PointD> m_points;

	LDraw::RectI m_clipRect;
	LDraw::RectI m_updateRect;

	void BltBrush(
		ImageDef* inImage,
		ImageDef* inDepth,
		ImageDef* outImage,
		double px, double py,
		const int opacity,
		const int grain,
		ImageDef* brushImage,
		ImageDef* paperImage,
		LDraw::RectI* lpclip,
		LDraw::RectI* lprect);

	void SetBrush(
		double x, double y,
		ImageDef* inImage,
		ImageDef* inDepth,
		ImageDef* outImage);

	bool BeginBrushStroke(double scaleX, double scaleY);
	void EndBrushStroke();

	void Render(LDraw::Bitmap* pBitmap, double scaleX, double scaleY);
};

class CGroupImageObject/* :
	public IGroupImageObject*/
{
public:
	vector<CStrokeObject*> m_objects;
};

class CImageLayerBitmap : 
	public ImageLayerUnknown
{
public:
	CTOR CImageLayerBitmap();

//	int FinalConstruct();
//	void FinalRelease();

	CImageLayerGroup* m_parentGroup;
	IImageDocument* m_document;

	System::StringW* m_name;

	LDraw::Bitmap* m_pInitialBitmap;

	LDraw::Bitmap* m_pBitmap;
	LDraw::Bitmap* m_pBitmapDepth;
	CGroupImageObject* m_group;

	LDraw::Bitmap* m_pBitmapMask;
	CGroupImageObject* m_groupMask;

	CGroupImageObject* m_groupClipPath;
	LDraw::Bitmap* m_pBitmapClipPath;	// Used??

	LDraw::Bitmap* m_pBitmapFinal;

	LDraw::RectI m_alphaBounds;

	LDraw::matrix3f m_matrix;
	double m_scaleX;
	double m_scaleY;

	long m_width;
	long m_height;

	CLayerEffect* m_effects[16];

	void CalculateScale(LDraw::RectD& expandedRect, LDraw::matrix3f& matrix)
	{
		LDraw::PointF ptxy;
		ptxy.X = expandedRect.X;
		ptxy.Y = expandedRect.Y;

		LDraw::PointF ptx;
		ptx.X = expandedRect.X+expandedRect.Width;
		ptx.Y = expandedRect.Y;

		LDraw::PointF pty;
		pty.X = expandedRect.X;
		pty.Y = expandedRect.Y+expandedRect.Height;

		/*
		objectCtm->m_matrix->transformPoint(&ptxy, &ptxy);
		objectCtm->transformPoint(&ptx, &ptx);
		objectCtm->transformPoint(&pty, &pty);
		*/

	//	ptxy = objectCtm->m_matrix.transform(gmVector2(ptxy.X, ptxy.Y));
	//	ptx = objectCtm->m_matrix.transform(gmVector2(ptx.X, ptx.Y));
	//	pty = objectCtm->m_matrix.transform(gmVector2(pty.X, pty.Y));

		ptxy = matrix.transform(ptxy);
		ptx = matrix.transform(ptx);
		pty = matrix.transform(pty);

		double dx, dy;

		dx = ptx.X-ptxy.X;
		dy = ptx.Y-ptxy.Y;
		m_scaleX = sqrt(dx*dx + dy*dy) / expandedRect.Width;

		dx = pty.X-ptxy.X;
		dy = pty.Y-ptxy.Y;
		m_scaleY = sqrt(dx*dx + dy*dy) / expandedRect.Height;
	}

	void Render();

// IImageLayerBitmap
public:
	CGroupImageObject* GetGroupObject();
	CGroupImageObject* GetMaskGroupObject();
	CGroupImageObject* GetClipPathGroupObject();

// IImageLayerUnknown
	System::StringW* GetName();
	ImageLayerType GetLayerType()
	{
		return LAYERTYPE_BITMAP;
	}
};

}	// ImageEdit
}

#endif //__ImageLayer_H_
