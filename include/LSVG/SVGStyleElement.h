#ifndef Web_SVGStyleElement_h
#define Web_SVGStyleElement_h

//#include "resource.h"       // main symbols

//#include "LSVGTransformableImpl.h" ??
//#include "LSVGStylableImpl.h"
//#include "LSVGLangSpaceImpl.h"

//#include "AnimationTarget.h"

namespace System
{
namespace Web
{

class SVGEXT SVGStyleElement : 

	public SVGElement,
	public LinkStyleStyleImpl,//<SVGStyleElement>,
//	public SVGTransformableImpl<SVGStyleElement, ILSVGTransformable>,
//	public SVGStylableImpl<SVGStyleElement, ILSVGStylable>,
//	public SVGLangSpaceImpl<SVGStyleElement>,
	public ElementEditVALImpl<SVGStyleElement>,

//	public CLSMILAnimationTargetImpl<SVGStyleElement>,

	protected CNotifyGetImpl<SVGStyleElement>,
	protected CNotifySendImpl<SVGStyleElement>
{
public:
	CTOR SVGStyleElement(NamedNodeMap* attributes);
#if 0
// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
		if (m_cssreentrancy == 0)
		{
			m_cssreentrancy++;

		// If the textnode's text changed, update the stylesheet
			{
			// The first text child contains the source of the stylesheet
			//	CComPtr<ILDOMNode> firstchild;
			//	get_firstChild(&firstchild);
			//	CComQIPtr<ILDOMCharacterData> chardata = firstchild;
			//	if (chardata)
				{
					sysstring data = get_textContent();

					m_styleSheet->set_cssText(data);
				}
			}
	
			m_cssreentrancy--;
		}

		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}
#endif

// EventTarget
	virtual ErrorCode dispatchEvent2(/*[in]*/ Event * evt, /*[in]*/ bool bCapture, /*[out,retval]*/ bool * doDefault)
	{
		ASSERT(0);
		return 0;
#if 0
		CComStringW type;
		evt->get_type(&type);

		LDOMEventPhaseType phase;
		evt->get_eventPhase(&phase);
		if (phase == AT_TARGET)
		{
			if (!wcscmp(type, L"DOMNodeInsertedIntoDocument"))
			{
				CComQIPtr<ILDocumentStyle> documentStyle = m_ownerDocument;
				if (documentStyle)
				{
					CComPtr<ILStyleSheetList> styleSheetList;
					documentStyle->get_styleSheets(&styleSheetList);

					styleSheetList->append(m_styleSheet);
				}
			}
			else if (!wcscmp(type, L"DOMNodeRemovedFromDocument"))
			{
				CComQIPtr<ILDocumentStyle> documentStyle = m_ownerDocument;
				if (documentStyle)
				{
					//CComPtr<ILStyleSheetList> styleSheetList;
					//documentStyle->get_styleSheets(&styleSheetList);

					documentStyle->removeStyleSheet(m_styleSheet);
				}
			}
		}

		return CLDOMEventTargetImpl<SVGStyleElement>::dispatchEvent2(evt, bCapture, doDefault);
#endif
	}

#if 0
	STDMETHODIMP addedtodocument()
	{
		ASSERT(m_ownerDocument);

		CComQIPtr<ILDocumentStyle> documentStyle = m_ownerDocument;
		if (documentStyle)
		{
			CComPtr<ILStyleSheetList> styleSheetList;
			documentStyle->get_styleSheets(&styleSheetList);

			styleSheetList->append(m_styleSheet);
		}

		return S_OK;
	}
	STDMETHODIMP removedfromdocument()
	{
		return S_OK;
	}
#endif

	String get_xmlspace();
	void set_xmlspace(StringIn newVal);
	String get_type();
	void set_type(StringIn newVal);
	String get_media();
	void set_media(StringIn newVal);
	String get_title();
	void set_title(StringIn newVal);
};

}	// Web
}

#endif // Web_SVGStyleElement_h
