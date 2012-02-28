#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#if 0

HRESULT createObjectNS(ILXUIDocument* document, BSTR namespaceURI, BSTR qualifiedName, REFIID riid, void** obp)
{
	*obp = NULL;
	CComPtr<IUnknown> unk;
	HRESULT hr = document->createObjectNS(namespaceURI, qualifiedName, &unk);
	if (FAILED(hr))
		return hr;
	return unk->QueryInterface(riid, obp);
}

#if 0
ILDOMElement* GetElementByTagName(ILDOMNode* parent, BSTR tagName, BOOL bDeep/* = FALSE*/)
{
	CComPtr<ILDOMNode> child;
	parent->get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == NODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;
			BSTR etagName;
			element->get_tagName(&etagName);

			if (!wcscmp(tagName, etagName))
			{
				SysFreeString(etagName);
				return element;
			}

			SysFreeString(etagName);

		// Recurse
			if (bDeep)
			{
				ILDOMElement* element2 = GetElementByTagName(element, tagName);
				if (element2 != NULL)
					return element2;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
}

ILDOMElement* GetElementByTagNameNS(ILDOMNode* parent, BSTR ns, BSTR tagName, BOOL bDeep/* = FALSE*/)
{
	CComPtr<ILDOMNode> child;
	parent->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
		if (element)
		{
			CComBSTR ens;
			element->get_namespaceURI(&ens);

			if (!cmpbstr(ens, ns))
			{
				CComBSTR etagName;
				element->get_localName(&etagName);
				if (SysStringLen(etagName) == 0)
				{
					etagName.Empty();
					element->get_tagName(&etagName);
				}

				if (!wcscmp(etagName, tagName))
				{
					return element;
				}
			}

		// Recurse
			if (bDeep)
			{
				CComPtr<ILDOMElement> element2 = GetElementByTagNameNS(element, ns, tagName, TRUE);
				if (element2 != NULL)
					return element2;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
}

// Compare two objects for equivalence
bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther)
{
	if (pThis == NULL && pOther == NULL)
		return true; // They are both NULL objects

	if (pThis == NULL || pOther == NULL)
		return false; // One is NULL the other is not

	CComPtr<IUnknown> punk1;
	CComPtr<IUnknown> punk2;
	pThis->QueryInterface(IID_IUnknown, (void**)&punk1);
	pOther->QueryInterface(IID_IUnknown, (void**)&punk2);
	return punk1 == punk2;
}
#endif

void AddCbString(HWND hWnd, TCHAR* text, DWORD dw)
{
	int index = SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)text);
	SendMessage(hWnd, CB_SETITEMDATA, index, dw);
}

void SetCbCurSel(HWND hWnd, DWORD dw)
{
	long count = SendMessage(hWnd, CB_GETCOUNT, 0, 0);

	for (int i = 0; i < count; i++)
	{
		DWORD dw2 = SendMessage(hWnd, CB_GETITEMDATA, i, 0);
		if (dw == dw2)
		{
			SendMessage(hWnd, CB_SETCURSEL, i, 0);
			return;
		}
	}

	SendMessage(hWnd, CB_SETCURSEL, -1, 0);
}

#endif