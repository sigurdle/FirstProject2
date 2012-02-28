#ifndef __LSVGSEQELEMENT_H_
#define __LSVGSEQELEMENT_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class SVGEXT SVGSeqElement : 

	public SVGElement,
//	public ElementTimeContainerImpl,//<CLSVGSeqElement>,
	public ElementEditVALImpl<SVGSeqElement>,
	public SVGTestsImpl<SVGSeqElement>,
	public CSVGRenderElementImpl<SVGSeqElement>,

//	public ILElementSequentialTimeContainer,
//	public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGSeqElement>,
	protected CNotifySendImpl<SVGSeqElement>
{
public:

	CTOR SVGSeqElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
	{
		m_timeContainerImpl = new ElementTimeContainerImpl(this);
	//	SetAllValues(this);	// ???
	}

	ElementTimeContainerImpl* m_timeContainerImpl;

#if 0
// EventTarget
	virtual HRESULT dispatchEvent2(/*[in]*/ ILDOMEvent * evt, /*[in]*/ VARIANT_BOOL bCapture, /*[out,retval]*/ VARIANT_BOOL * doDefault)
	{
		CComBSTR type;
		evt->get_type(&type);

		LDOMEventPhaseType phase;
		evt->get_eventPhase(&phase);
		if (phase == AT_TARGET)
		{
			if (!wcscmp(type, L"DOMNodeInsertedIntoDocument"))
			{
				// Timing stuff ?
				Init();
				Init2();
			}
			else if (!wcscmp(type, L"DOMNodeRemovedFromDocument"))
			{
				ATLASSERT(0);
			}
		}

		return CLDOMEventTargetImpl<T>::dispatchEvent2(evt, bCapture, doDefault);
	}
#endif

// ILSVGSeqElement
public:

	String get_timeContainer()
	{
		return WSTR("seq");
	}
};

}	// LSVG
}

#endif //__LSVGSEQELEMENT_H_
