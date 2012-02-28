#include "stdafx.h"
#include "LXML.h"
#include "TextEvent.h"

namespace System
{
namespace Web
{

CLTextEvent::CLTextEvent()
{
	m_keyVal = 0;
	m_virtKeyVal = 0;

	for (int i = 0; i < DOM_VK_F24+1; i++)
	{
		m_modifier[i] = 0;
	}
}

}	// Web
}

#if 0

/////////////////////////////////////////////////////////////////////////////
// CLTextEvent

STDMETHODIMP CLTextEvent::get_outputString(/*[out,retval]*/ BSTR* pVal)
{
	return S_OK;
}

STDMETHODIMP CLTextEvent::get_keyVal(/*[out,retval]*/ long* pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_keyVal;
	return S_OK;
}

STDMETHODIMP CLTextEvent::get_virtKeyVal(/*[out,retval]*/ long* pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_virtKeyVal;
	return S_OK;
}

STDMETHODIMP CLTextEvent::get_visibleOutputGenerated(/*[out,retval]*/ bool* pVal)
{
	return S_OK;
}

STDMETHODIMP CLTextEvent::get_numPad(/*[out,retval]*/ bool* pVal)
{
	return S_OK;
}

STDMETHODIMP CLTextEvent::checkModifier(/*[in]*/ long modifier, /*[out,retval]*/ bool* pVal)
{
	ASSERT(modifier >= 0 && modifier < DOM_VK_F24+1);
	if (modifier >= 0 && modifier < DOM_VK_F24+1)
	{
		*pVal = m_modifier[modifier]? VARIANT_TRUE: VARIANT_FALSE;
	}

	return S_OK;
}

STDMETHODIMP CLTextEvent::initModifier(/*[in]*/ long modifier, /*[in]*/ bool value)
{
	ASSERT(modifier >= 0 && modifier < DOM_VK_F24+1);

	if (modifier >= 0 && modifier < DOM_VK_F24+1)
	{
		m_modifier[modifier] = value != 0;
	}

	return S_OK;
}

STDMETHODIMP CLTextEvent::initTextEvent(
								/*[in]*/ BSTR typeArg,
                                /*[in]*/ bool canBubbleArg,
                                /*[in]*/ bool cancelableArg,
                                /*[in]*/ ILDOMAbstractView* viewArg,
                                /*[in]*/ long detailArg,
                                /*[in]*/ BSTR outputStringArg,
                                /*[in]*/ long keyValArg,
                                /*[in]*/ long virtKeyValArg,
                                /*[in]*/ bool visibleOutputGeneratedArg,
                                /*[in]*/ bool numPadArg)
{
	return initTextEventNS(NULL, typeArg, canBubbleArg, cancelableArg, viewArg, detailArg, outputStringArg, keyValArg, virtKeyValArg, visibleOutputGeneratedArg, numPadArg);
}


STDMETHODIMP CLTextEvent::initTextEventNS(
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
                                /*[in]*/ bool numPadArg)
{
// Call base event init
	CLDOMUIEventImpl<IDispatchExImpl<CLTextEvent, ILTextEvent, &IID_ILTextEvent, &LIBID_LXMLLib> >::initUIEvent(typeArg, canBubbleArg, cancelableArg, viewArg, detailArg);

	m_keyVal = keyValArg;
	m_virtKeyVal = virtKeyValArg;

	return S_OK;
}

#endif