#ifndef __PSMILElementImpl_h__
#define __PSMILElementImpl_h__

namespace System
{
namespace Web
{

class HTMLEXT PSMILElement : public PElementBase
{
public:
	CTOR PSMILElement(Element* element) : PElementBase(element)
	{
	}

	virtual void BuildChildren();

	virtual void Render(Graphics::Bitmap* pBgBitmap, Gui::ManagedRetainedRenderContext pGraphics, double scaleX, double scaleY)
	{
	}
};

}	// Web
}

#endif // __PSMILElementImpl_h__
