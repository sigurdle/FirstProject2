#include "stdafx.h"
#include "HTML2.h"

#include "HTMLScreen.h"

/////////////////////////////////////////////////////////////////////////////
// CLHTMLScreen

#if 0
// HTMLScreen
STDMETHODIMP CLHTMLScreen::get_colorDepth( 
   /* [out][retval] */ long *p)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::put_bufferDepth( 
   /* [in] */ long v)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::get_bufferDepth( 
   /* [out][retval] */ long *p)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::get_width( 
   /* [out][retval] */ long *p)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::get_height( 
   /* [out][retval] */ long *p)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::put_updateInterval( 
   /* [in] */ long v)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::get_updateInterval( 
   /* [out][retval] */ long *p)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::get_availHeight( 
   /* [out][retval] */ long *p)
{
	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::get_availWidth( 
   /* [out][retval] */ long *p)
{
	//GetSystemMetrics(

	return E_NOTIMPL;
}

STDMETHODIMP CLHTMLScreen::get_fontSmoothingEnabled( 
   /* [out][retval] */ VARIANT_BOOL *p)
{
	ATLASSERT(p != NULL);
	if (p == NULL) return E_POINTER;

	BOOL vParam;
	SystemParametersInfo(SPI_GETFONTSMOOTHING, NULL, (PVOID)&vParam, 0);
	*p = vParam? VARIANT_TRUE: VARIANT_FALSE;

	return S_OK;
}

// IHTMLScreen2
STDMETHODIMP CLHTMLScreen::get_logicalXDPI(/* [out][retval] */ long *p)
{
	if (p == NULL) return E_POINTER;
	*p = GetDeviceCaps(NULL, LOGPIXELSX);
	return S_OK;
}
        
STDMETHODIMP CLHTMLScreen::get_logicalYDPI(/* [out][retval] */ long *p)
{
	if (p == NULL) return E_POINTER;
	*p = GetDeviceCaps(NULL, LOGPIXELSX);
	return S_OK;
}

#endif