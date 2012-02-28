#ifndef Web_PSVGElement_h
#define Web_PSVGElement_h

namespace System
{
namespace Web
{

class SVGEXT GlyphRun : public Object
{
public:
	CTOR GlyphRun();
	~GlyphRun();

	void Render(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, PSVGFontElement* pSVGFont, double m_computedFontSize, Gui::Brush* pFillBrush, Gui::StrokeStyle* pStrokePen, float strokeWidth);

//	FontDef* m_pFontDef;
	IDWriteFontFace* m_dwriteFontFace;

//	LDraw::GraphicsPathF m_GraphicsPathF;	// for m_seglist, hm..
//	SVGPathSegList* m_seglist;
	PSVGElement* m_pGlyphRoot;

	double m_scale;
	double m_charWidth;
	gm::PointD m_position;
	double m_rotation;

	float m_emSize;

	double m_descent;

	CGlyphGroup* m_group;

	uint16 m_glyphIndex;
	//float m_glyphAdvances;
	DWRITE_GLYPH_OFFSET m_glyphOffset;
};

typedef GlyphRun CGlyph;

class SVGEXT CGlyphGroup : public Object
{
public:
	CTOR CGlyphGroup()
	{
		m_extent = 0;
		m_extent2 = 0;
	}

//	int m_start;
//	int m_count;
	vector<CGlyph*> m_glyphs;

	double m_extent;
	double m_extent2;
};

class SVGEXT TextLayoutContext : public Object
{
public:

	void AlignChunk(PElementBase* pPElement);

	gm::PointD initialPos;

	gm::PointD curpos;
	vector<CGlyph*> chunk;
};

class SVGEXT PSVGElement : public PElementBase
{
public:
	CTOR PSVGElement(SVGElement* element);
	~PSVGElement();

	virtual Graphics::Bitmap* GetBitmap(Gui::RenderContext* renderContext, int m_scaledWidth, int m_scaledHeight, double m_scaleX, double m_scaleY);

	virtual void InvalidateBounds();

	virtual void BuildChildren();
	virtual void BuildRenderableChildren();

	PSVGElement* GetViewportElement();

	virtual Style::IStyleDeclaration* get_inlineStyle(uint index) override;

	virtual void RemoveChildren()
	{
		m_childListRender.RemoveAll();

#ifndef __LERSTAD__
		PElementBase::RemoveChildren();
#endif
	}

	Gui::Brush* GetStrokeBrush(double opacity, double scaleX, double scaleY);
	Gui::Brush* GetFillBrush(double opacity, double scaleX, double scaleY);

	list<PElementBase*>::iterator AddReferencingElement(PElementBase* pPElement);

	virtual void ReferenceInvalid(PElementBase/*PSVGElement*/ * pPElement);

	/*
/// Mask

	void Mask(LDraw::Bitmap* pBitmap, LDraw::RectF filterRect, double scaleX, double scaleY, LDraw::SmoothingMode smoothingMode);
	LDraw::Bitmap* GetOpacityMaskBitmap(LDraw::RectF filterRect, double scaleX, double scaleY, LDraw::SmoothingMode smoothingMode);
	void ProcessMaskBitmap(LDraw::Bitmap* pMask, LDraw::Bitmap* pBitmap);

///
	*/

	virtual void CalculateBounds();
	virtual void CalculateBoundsAndChildren();

	double LengthToUserUnits(ISVGLength* length, double percentageOf);

	void CalculateScale(gm::Matrix3d* matrix);

	gm::RectD CalculateRenderableChildrenBoundingBox();
	gm::RectD CalculateRenderableChildrenFilterRect();

	void Render(CHTMRenderContext* pC, Gui::RenderContext* renderContext, double scaleX, double scaleY);

	void RenderChildren(CHTMRenderContext* pC, Gui::RenderContext* renderContext, double scaleX, double scaleY);

	void FreeCachedBitmap();

	virtual void CalculateDimensions(CHTMCalcContext* pC);
	virtual void OnAttrChanged(Attr* attr);

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual void RenderSelection(CHTMRenderContext* pC);

	void RenderSelection2(CHTMRenderContext* pC);
/*
	virtual void RenderPathToGraphics(UI::Graphics* pGraphics)
	{
		// Not all elements need to implement this
	}
*/
	virtual void RenderPath(Gui::Geometry* pGraphicsPathF)
	{
		// Not all elements need to implement this
	}

	virtual PSVGElement* HitTestElement(gm::Matrix3d* matrix, gm::PointD pt);
	PSVGElement* HitTestChildren(gm::Matrix3d* matrix, gm::PointD pt);

	bool HitTest(double x, double y)
	{
		return HitTest(x, y, m_computedPointerEvents);
	}

	gm::Matrix3d* m_animateMotionMatrix;

	virtual gm::Matrix3d* GetLocalAnimatedMatrix()	// Matrix applied to this element
	{
		return gm::Matrix3d::GetIdentity();
	}

	virtual gm::Matrix3d* GetViewBoxMatrix()	// Matrix applied to children of this element
	{
		return gm::Matrix3d::GetIdentity();
	}

	virtual void OnResetAnimVals()
	{
		m_animateMotionMatrix = gm::Matrix3d::GetIdentity();
	}

	gm::Matrix3d* GetScreenCTM();
	gm::Matrix3d* GetScreenCTM2();

	virtual bool HitTest(double x, double y, int pointerEvents)
	{
		return false;
	}

	void GetScreenBBoxFromPath(SVGPathSegList* seglist, gm::RectD* bbox);
	void GetScreenBBoxFromBounds(const gm::RectD& bounds, gm::RectD* bbox);

	virtual bool NeedOffscreenBitmap() const;

	virtual gm::RectD GetScreenBBox()
	{
		return gm::RectD(0,0,0,0);
	}

	virtual Gui::Brush* CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY)
	{
		return NULL;//LDraw::Brush();
	}

	Gui::Brush* GetBrush(CSVGPaint* pPaint, PSVGElement* pUriElement, double opacity, double scaleX, double scaleY);
	Gui::Brush* GetBrush(Gui::RenderTarget* rt, CSVGPaint* pPaint, PSVGElement* pUriElement, double opacity, double scaleX, double scaleY);

//	LDraw::Pen* GetPen(Gui::Brush* pBrush);

	void GetFillUriElement();
	void GetStrokeUriElement();
	void GetFilterElement();
	void GetMarkerStartElement();
	void GetMarkerEndElement();
	void GetMarkerMidElement();
	void GetMaskElement();
	void GetClipPathElement();

	void RemoveGlyphs()
	{
		for (unsigned int i = 0; i < m_glyphs.size(); i++)
		{
			CGlyph* pGlyph = m_glyphs[i];
			delete pGlyph;
		}
		m_glyphs.RemoveAll();
	}

	CGlyph* GetGlyphAtIndex(int& glyphnum);
	int GetNumberOfGlyphs();

//	BOOL GetTextUnderPoint2(PointD pt, CPNode** pNode, long* poffset, double& distance);
	bool GetTextUnderPoint(gm::matrix3d matrix, gm::PointD pt, PNode** ppNode, long* poffset, double& distance);

	virtual bool HitText(gm::matrix3d matrix, gm::PointD pt, PNode** ppNode, long* poffset)
	{
		return false;
	}

/*
	BOOL GetTextUnderPoint2(PointD pt, CPNode** pNode, long* poffset)
	{
		double d = 99999999;
		return GetTextUnderPoint2(pt, pNode, poffset, d);
	}
*/

	bool HitTestCharacters(gm::PointD pt, int pointerEvents, PNode** ppNode, long* poffset);

	virtual void LayoutText(TextLayoutContext* tlc, bool bDoX, bool bDoY);
	void LayoutGlyphs(vector<CGlyph*>& glyphs, TextLayoutContext* tlc, bool bDoX, bool bDoY, double& minx, double& miny, double& maxx, double& maxy);
	void TransformGlyphs();

	void RenderTextChildren(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen);

	virtual void SetViewportElement(PSVGElement* nearestViewportElement);

	void SetViewportElementChildren(PSVGElement* nearestViewportElement);

//	virtual void RenderSelection(CHTMRenderContext* pC);

	double m_scaleX;
	double m_scaleY;
	vector<PSVGElement*> m_childListRender;

	PSVGElement* m_nearestViewportElement;

	gm::RectD m_bounds;
	gm::RectD m_expandedBBox;
	gm::RectD m_filterRect;
	gm::RectD m_xbounds;
	Graphics::Bitmap* m_backgroundBitmap;

	Graphics::Bitmap* m_pCachedBitmap;
	Gui::Brush* m_pStrokeBrush;
	Gui::Brush* m_pFillBrush;
//	LDraw::Commands* m_pRenderCommands;

	ID2D1Brush* m_elementBrush;

	list<PElementBase*> m_referencingElements;	// Elements that are referencing us

// Computed CSS properties
	PSVGElement* m_pStrokeElement;
	PSVGElement* m_pFillElement;

	PSVGFilterElement* m_pFilterElement;
	list<PElementBase*>::iterator m_pFilterElementIt;

	PSVGMaskElement* m_pMaskElement;
	PSVGClipPathElement* m_pClipPathElement;
	PSVGMarkerElement* m_pMarkerStartElement;
	PSVGMarkerElement* m_pMarkerEndElement;
	PSVGMarkerElement* m_pMarkerMidElement;

	double m_textLength;
	vector<GlyphRun*> m_glyphs;
	int m_nCharCount;

	bool m_boundsValid : 1;
	bool m_renderValid : 1;
};

class SVGEXT PSVGTransformableElement : public PSVGElement
{
public:
	CTOR PSVGTransformableElement(SVGTransformableElement* element);

	virtual gm::Matrix3d* GetLocalAnimatedMatrix();	// Matrix applied to this element
};

class SVGEXT PSVGShapeElement : public PSVGTransformableElement
{
public:
	CTOR PSVGShapeElement(SVGTransformableElement* element);

//	virtual void CalculateBounds();
//	virtual void CalculateBounds2();
};

bool HitTestPath(PElementBase* pElement, Gui::Geometry* pGraphicsPathF, double x, double y, int pointerEvents);

class SVGEXT PSVGGenericElement : public PSVGElement
{
public:
	CTOR PSVGGenericElement(SVGElement* element) : PSVGElement(element)
	{
	}
};

class SVGEXT CPAnimateElement : public CPAnimationElementImpl
{
public:
	CTOR CPAnimateElement(Element* element) : CPAnimationElementImpl(element)
	{
	}
};

}	// Web
}	// System

#endif // Web_PSVGElement_h
