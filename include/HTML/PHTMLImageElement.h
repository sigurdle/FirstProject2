#ifndef Web_PHTMLImageElement_h
#define Web_PHTMLImageElement_h

namespace System
{
namespace Web
{

class HTMLEXT PHTMLImageElement : public PHTMLElement
{
public:

	CTOR PHTMLImageElement(HTMLImageElement* element);
	~PHTMLImageElement();

	//virtual BOOL OnButtonDown(POINT point, LXML::CPElement* *pVal);
	virtual void Draw(CHTMRenderContext* pC);
//	virtual void CalculateDimensions(LXML::CHTMCalcContext* pC);

	gm::SizeD GetIntrinsicSize();

	virtual bool HasDistributableChildren();
};

}	// Web
}

#endif // Web_PHTMLImageElement_h
