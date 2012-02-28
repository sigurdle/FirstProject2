#ifndef __TEXTEVENT_H__
#define __TEXTEVENT_H__

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class CLTextEvent : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public UIEvent//Impl<IDispatchExImpl<CLTextEvent, ILTextEvent, &IID_ILTextEvent, &LIBID_LXMLLib> >
{
public:
	CTOR CLTextEvent();

	uint8 m_modifier[DOM_VK_F24+1];

	long m_keyVal;
	long m_virtKeyVal;

#if 0
// ILTextEvent
public:
	STDMETHOD(get_outputString)(/*[out,retval]*/ BSTR* pVal);
	STDMETHOD(get_keyVal)(/*[out,retval]*/ long* pVal);
	STDMETHOD(get_virtKeyVal)(/*[out,retval]*/ long* pVal);
	STDMETHOD(get_visibleOutputGenerated)(/*[out,retval]*/ bool* pVal);
	STDMETHOD(get_numPad)(/*[out,retval]*/ bool* pVal);

	STDMETHOD(checkModifier)(/*[in]*/ long modifier, /*[out,retval]*/ bool* pVal);
	STDMETHOD(initModifier)(/*[in]*/ long modifier, /*[in]*/ bool value);

	STDMETHOD(initTextEvent)(
								   /*[in]*/ BSTR typeArg,
                                   /*[in]*/ bool canBubbleArg,
                                   /*[in]*/ bool cancelableArg,
                                   /*[in]*/ ILDOMAbstractView* viewArg,
                                   /*[in]*/ long detailArg,
                                   /*[in]*/ BSTR outputStringArg,
                                   /*[in]*/ long keyValArg,
                                   /*[in]*/ long virtKeyValArg,
                                   /*[in]*/ bool visibleOutputGeneratedArg,
                                   /*[in]*/ bool numPadArg);

	STDMETHOD(initTextEventNS)(
						   		   /*[in]*/ BSTR namespaceURI,
								   /*[in]*/ BSTR typeArg,
                                   /*[in]*/ bool canBubbleArg,
                                   /*[in]*/ bool cancelableArg,
                                   /*[in]*/ ILDOMAbstractView* viewArg,
                                   /*[in]*/ long detailArg,
                                   /*[in]*/ BSTR outputStringArg,
                                   /*[in]*/ long keyValArg,
                                   /*[in]*/ long virtKeyValArg,
                                   /*[in]*/ bool visibleOutputGeneratedArg,
                                   /*[in]*/ bool numPadArg);
#endif
};

}	// w3c
}

#endif // __TEXTEVENT_H__
