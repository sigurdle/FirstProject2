#ifndef Web_SVGImageElement_h
#define Web_SVGImageElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGImageElement : 

	public SVGTransformableElement,
	public SVGURIReferenceImpl<SVGImageElement>,
	public SVGStylableImpl<SVGImageElement>,
	public SVGLangSpaceImpl<SVGImageElement>,
	public SVGTestsImpl<SVGImageElement>,
//	public ElementEditASImpl<SVGImageElement>,
	public ElementEditVALImpl<SVGImageElement>,
//	public SMILAnimationTargetImpl<SVGImageElement>,
	public CSVGRenderElementImpl<SVGImageElement>,

//	public IElementEditVAL,	// INodeEditVAL

	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>,
	protected AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>
{
public:
	CTOR SVGImageElement(NamedNodeMap* attributes);
	~SVGImageElement();

	ISVGAnimatedLength* get_x();
	ISVGAnimatedLength* get_y();
	ISVGAnimatedLength* get_width();
	ISVGAnimatedLength* get_height();
	ISVGAnimatedPreserveAspectRatio* get_preserveAspectRatio();
// SVG 1.2
	Document* getImageDocument();

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>& x_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>*>(this);
	}

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>& y_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>*>(this);
	}

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>& width_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>*>(this);
	}

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>& height_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>& preserveAspectRatio_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>*>(this);
	}

public:

	CImage* GetImage();
	CHTMLWindow* GetSVGDocumentView();

	/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/

protected:

	friend class PSVGImageElement;

	/*
	SVGAnimatedT<SVGImageElement, SVGAnimatedLength> m_x;
	SVGAnimatedT<SVGImageElement, SVGAnimatedLength> m_y;
	SVGAnimatedT<SVGImageElement, SVGAnimatedLength> m_width;
	SVGAnimatedT<SVGImageElement, SVGAnimatedLength> m_height;
	*/

	/*
	SVGAnimatedLength* m_x;
	static attr_vtable s_xCallbacks;
	friend void xBaseValChanged(Object* obj);
	StringW* xGetBaseValString();
	void xSetBaseValString();
	Object* xGetBaseValObject();
	void xSetAnimValObject(Object* value);

	SVGAnimatedLength* m_y;
	static attr_vtable s_yCallbacks;
	friend void yBaseValChanged(Object* obj);
	StringW* yGetBaseValString();
	void ySetBaseValString();
	Object* yGetBaseValObject();
	void ySetAnimValObject(Object* value);

	SVGAnimatedLength* m_width;
	static attr_vtable s_widthCallbacks;
	friend void widthBaseValChanged(Object* obj);
	StringW* widthGetBaseValString();
	void widthSetBaseValString();
	Object* widthGetBaseValObject();
	void widthSetAnimValObject(Object* value);

	SVGAnimatedLength* m_height;
	static attr_vtable s_heightCallbacks;
	friend void heightBaseValChanged(Object* obj);
	StringW* heightGetBaseValString();
	void heightSetBaseValString();
	Object* heightGetBaseValObject();
	void heightSetAnimValObject(Object* value);
*/

//	SVGAnimatedT<SVGImageElement, SVGAnimatedPreserveAspectRatio, 4> m_preserveAspectRatio;

	CImage* m_pImage;	// Raster image, JPEG/PNG etc.
	Document* m_document;
	CHTMLWindow* m_pSVGDocumentView;
	bool m_bTriedLoaded;

	ErrorCode Load();
};

}	// Web
}	// System

#endif // Web_SVGImageElement_h
