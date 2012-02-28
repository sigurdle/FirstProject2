// WEUndoMoveObjects.cpp : Implementation of CWEUndoMoveObjects
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "WEUndoMoveObjects.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"

#if 0
ILDOMNode* GetElementFromUniqID(ILDOMNode* parent, GUID& guid)
{
	GUID uniqGUID;
	parent->get_uniqID(&uniqGUID);
	if (uniqGUID == guid) return parent;
	
// Try children
	CComPtr<ILDOMNode> child;
	parent->get_firstChild(&child);
	while (child)
	{
		//
		ILDOMNode* pFound = GetElementFromUniqID(child, guid);
		if (pFound)
			return pFound;
		
		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CWEUndoMoveObjects

STDMETHODIMP CWEUndoMoveObjects::GetDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
{
	*pBstr = SysAllocString(L"Move Objects");
	return S_OK;
}

STDMETHODIMP CWEUndoMoveObjects::GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID)
{
//	*pClsid = CLSID_WEUndoMoveObjects;
	*plID = 0;

	return S_OK;
}

STDMETHODIMP CWEUndoMoveObjects::OnNextAdd(void)
{
	return S_OK;
}

STDMETHODIMP CWEUndoMoveObjects::Do(IOleUndoManager __RPC_FAR *pUndoManager)
{
	CComPtr<ILDOMDocument> document;
	m_pDocument->get_DOMDocument(&document);

	CComQIPtr<ILDOMElement> documentElement;
	document->get_documentElement(&documentElement);

	if (m_bRedo)
	{
		CWEUndoSourceLast::Do(pUndoManager);

		for (int i = 0; i < m_targetElements.GetSize(); i++)
		{
			CComQIPtr<ILDOMElement> pDOMElement = GetElementFromUniqID(documentElement, m_targetElements[i]);
			if (pDOMElement)
			{
				CComPtr<IEElement> eElement;
				m_pDocument->GetEElementFromDOMElement(pDOMElement, &eElement);

				CComPtr<IESelectedElement> selectedElement;
				m_pDocument->m_viewGroups[0]->ActivateElement(eElement, MK_SHIFT, &selectedElement);

				selectedElement->Move(NULL, m_deltas[i].X, m_deltas[i].Y);
			}
		}

#if 0
		for (int i = 0; i < m_targetElements.GetSize(); i++)
		{
			ILDOMNode* pDOMElement = GetElementFromUniqID(documentElement, m_targetElements[i]);
			if (pDOMElement)
			{
				CElementImpl* pElement = m_pDocument->m_pTree->FindDOMElement(pDOMElement);
				if (pElement)
				{
					pElement->Move(m_dx, m_dy);
				}
			}
		}
#endif
	}
	else	// Undo
	{
		for (int i = 0; i < m_targetElements.GetSize(); i++)
		{
			CComQIPtr<ILDOMElement> pDOMElement = GetElementFromUniqID(documentElement, m_targetElements[i]);
			if (pDOMElement)
			{
				CComPtr<IEElement> eElement;
				m_pDocument->GetEElementFromDOMElement(pDOMElement, &eElement);

				CComPtr<IESelectedElement> selectedElement;
				m_pDocument->m_viewGroups[0]->ActivateElement(eElement, MK_SHIFT, &selectedElement);

				selectedElement->Move(NULL, -m_deltas[i].X, -m_deltas[i].Y);
			}
		}

		CWEUndoSourceLast::Do(pUndoManager);
	}

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);

	return S_OK;
}

#endif