// LXUIMenuBarElement.cpp : Implementation of CLXUIMenuBarElement
#include "stdafx.h"
#include "LXUI.h"
#include "LXUI2.h"
#include "LXUIMenuBarElement.h"

//////////////////////////////////////////////////////////////////////////
// CLXUIMenuBarElement

STDMETHODIMP CLXUIMenuBarElement::setMenu(/*[in]*/ VARIANT newVal)
{
	ATLASSERT(0);
#if 0
	if (newVal.vt == VT_UNKNOWN || newVal.vt == VT_DISPATCH)
	{
		CComQIPtr<ILXUIMenuElement> menu = newVal.punkVal;
		if (menu)
		{
			CComBSTR id;
			menu->getAttribute(L"id", &id);

			if (id.Length() == 0)
			{
				// TODO, create a unique identifier for the menu
				ATLASSERT(0);
				return E_FAIL;
			}

			// If the menu isn't yet part of the document, append it as a child of us
			CComPtr<ILDOMNode> parentNode;
			menu->get_parentNode(&parentNode);
			if (parentNode == NULL)
			{
				appendChild(menu, NULL);
			}

			setAttribute(L"href", id);	// Set us to point to the menu
		}
		else
			return E_INVALIDARG;
	}
	else
	{
		removeAttribute(L"href");
	}
#endif

	return S_OK;
}

STDMETHODIMP CLXUIMenuBarElement::get_Width(/*[out, retval]*/ ILXUILength* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_Width;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLXUIMenuBarElement::set_Width(/*[in]*/ ILXUILength* newVal)
{
	m_Width = newVal;
	return S_OK;
}

STDMETHODIMP CLXUIMenuBarElement::get_Height(/*[out, retval]*/ ILXUILength* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_Height;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLXUIMenuBarElement::set_Height(/*[in]*/ ILXUILength* newVal)
{
	m_Height = newVal;
	return S_OK;
}
