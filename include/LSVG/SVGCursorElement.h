#ifndef Web_SVGCursorElement_h
#define Web_SVGCursorElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGCursorElement : 

	public SVGElement,
	public SVGURIReferenceImpl<SVGCursorElement>,
//	public SVGTransformableImpl<SVGCursorElement>,
	public SVGStylableImpl<SVGCursorElement>,
	public SVGLangSpaceImpl<SVGCursorElement>,
//	public CLElementEditASImpl<SVGCursorElement>,
	public ElementEditVALImpl<SVGCursorElement>,
	//public SMILAnimationTargetImpl<SVGCursorElement>,
	public CSVGRenderElementImpl<SVGCursorElement>

//	protected CNotifyGetImpl<SVGCursorElement>,
//	protected CNotifySendImpl<SVGCursorElement>
{
public:
	CTOR SVGCursorElement();
	CTOR SVGCursorElement(NamedNodeMap* attributes);

	CImage* GetImage();
	HCURSOR GetCursor();

	ISVGAnimatedLength* get_x();
	ISVGAnimatedLength* get_y();

protected:

	ErrorCode Load();

	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;

//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_x;
//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_y;

	CImage* m_pImage;	// Raster image, JPEG/PNG etc.
	HCURSOR m_hCursor;

	bool m_bTriedLoaded;
};

}	// Web
}

#endif // w3c_SVGCursorElement_h
