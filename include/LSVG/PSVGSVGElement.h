#ifndef w3c_PSVGSVGElement_h
#define w3c_PSVGSVGElement_h

//#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGSVGElement :
	public PSVGElement
#if 0
	public CLDOMViewCSSImpl<CXMLDocumentView>	// Still experimental
#endif
{
public:
	CTOR PSVGSVGElement(SVGSVGElement* element);

	virtual void SetViewportElement(PSVGElement* nearestViewportElement) override;

	gm::matrix3f CalculateViewBoxMatrix();

	virtual void CalculateBounds();

	virtual gm::RectD GetViewBox();

// CSS Box Model
	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);	// ??
//	virtual void BuildChildren();
	virtual bool HasDistributableChildren();	// ??

// TODO: rename this ??
	virtual void DistributeWithinBlock(CHTMFlowBlockContext* pC, double parentwidth);

//	virtual void CalculateBoundsAndChildren();
	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual void RenderSelection(CHTMRenderContext* pC);

//	virtual BOOL GetTextUnderPoint(PointD pt, CPNode** ppNode, long* poffset, double& distance);

//	virtual PSVGElement* HitTestElement(gmMatrix3 matrix, PointD pt);

	virtual gm::Matrix3d* GetLocalAnimatedMatrix();
//	virtual CComObject<SVGMatrix>* GetGlobalAnimatedMatrix();
//	virtual CComObject<SVGMatrix>* GetGlobalAnimatedMatrix2();

	double m_computedX;
	double m_computedY;
//	double m_computedWidth;	// Defined as CSS properties ??
//	double m_computedHeight;

	gm::matrix3f m_viewboxMatrix;
};

}	// Web
}	// System

#endif // Web_PSVGSVGElement_h
