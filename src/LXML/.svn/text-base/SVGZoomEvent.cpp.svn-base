#include "stdafx.h"
#include "LXML2.h"
#include "SVGZoomEvent.h"

namespace System
{
namespace Web
{

ZoomEvent::ZoomEvent()
{
	m_zoomRectScreen = NULL;
	m_previousTranslate = NULL;
	m_newTranslate = NULL;
}

ZoomEvent::~ZoomEvent()
{
}

	/*
int CLSVGZoomEvent::FinalConstruct()
{
	CComObject<CLSVGRect>::CreateInstance(&m_zoomRectScreen);
	m_zoomRectScreen->AddRef();

	CComObject<CLSVGPoint>::CreateInstance(&m_previousTranslate);
	m_previousTranslate->AddRef();

	CComObject<CLSVGPoint>::CreateInstance(&m_newTranslate);
	m_newTranslate->AddRef();

	return S_OK;
}

void CLSVGZoomEvent::FinalRelease()
{
	m_zoomRectScreen->Release();
	m_zoomRectScreen = NULL;

	m_previousTranslate->Release();
	m_previousTranslate = NULL;

	m_newTranslate->Release();
	m_newTranslate = NULL;
}
*/

const SVGRect* ZoomEvent::get_zoomRectScreen() const
{
	return m_zoomRectScreen;
}

double ZoomEvent::get_previousScale() const
{
	return m_previousScale;
}

const SVGPoint* ZoomEvent::get_previousTranslate() const
{
	return m_previousTranslate;
}

double ZoomEvent::get_newScale() const
{
	return m_newScale;
}

const SVGPoint* ZoomEvent::get_newTranslate() const
{
	return m_newTranslate;
}

}	// Web
}	// System
