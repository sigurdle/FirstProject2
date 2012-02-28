#ifndef __SMIL_PSMILRegionElement_h__
#define __SMIL_PSMILRegionElement_h__

#include "PSMILElement.h"

namespace System
{
namespace Web
{

class HTMLEXT PSMILRegionElement :
	public PSMILElement
{
public:

	virtual void Render(Graphics::Bitmap* pBgBitmap, Gui::ManagedRetainedRenderContext, double scaleX, double scaleY);
};

}	// Web
}

#endif // __SMIL_PSMILRegionElement_h__
