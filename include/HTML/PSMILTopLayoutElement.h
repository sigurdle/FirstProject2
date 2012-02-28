#ifndef __PSMILTopLayoutElement_h__
#define __PSMILTopLayoutElement_h__

#include "PSMILLayoutElement.h"

namespace System
{
namespace Web
{

class HTMLEXT PSMILTopLayoutElement :
	public PSMILLayoutElement
{
public:

	virtual void Render(Graphics::Bitmap* pBgBitmap, Gui::ManagedRetainedRenderContext, double scaleX, double scaleY);

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

}	// Web
}

#endif // __PSMILTopLayoutElement_h__
