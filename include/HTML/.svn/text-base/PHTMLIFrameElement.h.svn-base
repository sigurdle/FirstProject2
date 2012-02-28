#ifndef __PHTMLIFrameElement_h__
#define __PHTMLIFrameElement_h__

#include "HTMPElement.h"

namespace System
{
namespace Web
{

class CHTMFrame;

class CPHTMLIFrameElement :
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CHTMPElement
{
public:

	CTOR CPHTMLIFrameElement();
	~CPHTMLIFrameElement();

	CHTMFrame* m_pContainer;

	virtual void PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC);

//	virtual BOOL OnButtonDown(POINT point, CPElement* *pVal);
//	virtual void Draw(CHTMRenderContext* pC);
//	virtual void CalculateDimensions(CHTMCalcContext* pC);
//	virtual BOOL HasDistributableChildren();

};

}
}

#endif // __PHTMLIFrameElement_h__
