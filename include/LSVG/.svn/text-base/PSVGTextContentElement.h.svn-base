#ifndef Web_PSVGTextContentElement_h
#define Web_PSVGTextContentElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class PSVGText : public Object, public ITextNodeExt//CPTextNodeBase
{
public:
	CTOR PSVGText(PCharacterData* owner) :
		m_owner(owner),
		m_fontHeight(0)
	{
	}

	~PSVGText()
	{
		RemoveGlyphs();
	}

	void RemoveGlyphs()
	{
		for (uint i = 0; i < m_glyphs.GetSize(); ++i)
		{
			CGlyph* pGlyph = m_glyphs[i];
			delete pGlyph;
		}
		m_glyphs.RemoveAll();

		m_glyphGroups.RemoveAll();
	}

	void CalculateTextDimensions(CHTMCalcContext* pC, String text, int length);

	virtual bool GetCursorPosition(int cursorPos, gm::PointD* pos, double* pHeight, gm::matrix3d* pMat3);
	virtual void CalculateDimensions(CHTMCalcContext* pC) override;
	virtual void OnTextContentChanged();

public:

	double m_fontHeight;
	PCharacterData* m_owner;
	vector<CGlyph*> m_glyphs;
	vector<CGlyphGroup*> m_glyphGroups;
};

class PSVGTextContentElement :
//	public PSVGElement
	public PSVGTransformableElement
{
public:
	CTOR PSVGTextContentElement(SVGTransformableElement* element) : PSVGTransformableElement(element)
	{
//		m_nCharCount = 0;
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors) override;
//	virtual void BuildChildren();
//	virtual void CalculateDimensions(CHTMCalcContext* pC);
};

}	// Web
}	// System

#endif // Web_PSVGTextContentElement_h
