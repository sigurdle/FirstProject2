// LHTMLDialog.cpp : Implementation of CLHTMLDialog
#include "stdafx.h"
#include "LAXMLViewer.h"

//#include "LXDocumentViewer.h"
//#include "..\LHTML\LHTML2.h"
#include "..\LXML\LXML2.h"
#include "LHTMLDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CLHTMLDialog

STDMETHODIMP CLHTMLDialog::get_dialogArguments(VARIANT *pVal)
{
	if (pVal == NULL) return E_POINTER;
	VariantCopy(pVal, &m_dialogArguments);
	return S_OK;
}

STDMETHODIMP CLHTMLDialog::put_dialogArguments(VARIANT newVal)
{
	m_dialogArguments = newVal;
	return S_OK;
}

STDMETHODIMP CLHTMLDialog::get_returnValue(VARIANT *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_returnValue;
	return S_OK;
}

STDMETHODIMP CLHTMLDialog::put_returnValue(VARIANT newVal)
{
	m_returnValue = newVal;
	return S_OK;
}

STDMETHODIMP CLHTMLDialog::get_dialogLeft(VARIANT *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLHTMLDialog::put_dialogLeft(VARIANT newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLHTMLDialog::get_dialogTop(VARIANT *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLHTMLDialog::put_dialogTop(VARIANT newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLHTMLDialog::get_dialogWidth(VARIANT *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLHTMLDialog::put_dialogWidth(VARIANT newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLHTMLDialog::get_dialogHeight(VARIANT *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLHTMLDialog::put_dialogHeight(VARIANT newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
