#include "stdafx.h"
#include "XPath.h"

#if 0

#include "libxml.h"
#include "libxml\xpath.h"

#include "XPathResult.h"

#include "XPathSetSnapshot.h"

void CXPathResult::FinalRelease()
{
#if 0	// Have this
	if ((obj->type == XPATH_NODESET) || (obj->type == XPATH_XSLT_TREE))
	{
		if (obj->boolval)
		{
			if (obj->user != NULL)
			{
				xmlFreeNodeList((ILDOMNode*) obj->user);
				xmlXPathFreeNodeSet(obj->nodesetval);
			}
			else if (obj->nodesetval != NULL)
				xmlXPathFreeValueTree(obj->nodesetval);
		}
		else
		{
			if (obj->nodesetval != NULL)
				xmlXPathFreeNodeSet(obj->nodesetval);
		}
#ifdef LIBXML_XPTR_ENABLED
	}
	else if (obj->type == XPATH_LOCATIONSET)
	{
		if (obj->user != NULL)
			xmlXPtrFreeLocationSet((xmlLocationSet *)obj->user);
#endif
	}
	else if (obj->type == XPATH_STRING)
	{
		if (obj->stringval != NULL)
			free(obj->stringval);
	}
	
#endif
}

STDMETHODIMP CXPathResult::get_resultType(LXPathResultType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = type;
	return S_OK;
}

STDMETHODIMP CXPathResult::get_numberValue(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = floatval;
	return S_OK;
}

STDMETHODIMP CXPathResult::get_stringValue(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	return S_OK;
}

STDMETHODIMP CXPathResult::get_booleanValue(bool *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = boolval? VARIANT_TRUE: VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CXPathResult::get_singleNodeValue(ILDOMNode* *pVal)
{
	return S_OK;
}

STDMETHODIMP CXPathResult::get_snapshotLength(/*[out, retval]*/ long *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	if (nodesetval)
		*pVal = nodesetval->nodeTab.GetSize();
	else
		*pVal = 0;

	return S_OK;
}

STDMETHODIMP CXPathResult::snapshotItem(/*[in]*/ long index, /*[out,retval]*/ ILDOMNode** pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	if (nodesetval)
	{
		if (index >= 0 && index < nodesetval->nodeTab.GetSize())
		{
			*pVal = nodesetval->nodeTab[index];
			(*pVal)->AddRef();
		}
	}

	return S_OK;
}

/*
STDMETHODIMP CXPathResult::getSetSnapshot(bool ordered, IXPathSetSnapshot** pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = nodesetval;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
*/

#endif