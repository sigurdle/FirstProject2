#include "stdafx.h"
#include "HTML2.h"
#include "HTMLCanvasElement.h"

namespace System
{

namespace Web
{

HTMLCanvasElement::HTMLCanvasElement(NamedNodeMap* attributes) : HTMLElement(new PElementBase(this), attributes)
{
//	SetAllValues(this);
}

HTMLCanvasElement::~HTMLCanvasElement()
{
}

unsigned int HTMLCanvasElement::get_width()
{
	ASSERT(0);
	return 0;
}

unsigned int HTMLCanvasElement::get_height()
{
	ASSERT(0);
	return 0;
}

Object* HTMLCanvasElement::getContext(StringIn contextId)
{
	return getContext(contextId, NULL);
}

Object* HTMLCanvasElement::getContext(StringIn contextId, Object* contextAttributes)
{
	if (contextId == "webgl")
	{
		if (m_context2d)
		{
		}

		if (m_webglContext == NULL)
		{
			m_webglContext = new WebGLRenderingContext(this);
		}

		m_currentContext = m_webglContext;
		return m_webglContext;
	}
	else if (contextId == "2d")
	{
		if (m_webglContext)
		{
		}

		if (m_context2d == NULL)
		{
			m_context2d = new CanvasRenderingContext2D(this);
		}

		m_currentContext = m_context2d;
		return m_context2d;
	}
	else
	{
		return NULL;
	}
}

gm::Sizei HTMLCanvasElement::GetImageSize()
{
	return gm::Sizei(get_width(), get_height());
}

}	// Web
}	// System
