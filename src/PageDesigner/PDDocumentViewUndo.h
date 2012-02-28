#pragma once

#include "PDUndoUnitImpl.h"

//////////////////////////////////////////////////////////
// CUndoMoveObjects

class ATL_NO_VTABLE CUndoMoveObjects : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDUndoUnitImpl
{
public:
	CUndoMoveObjects()
	{
		//m_pDocument = NULL;
	}

	CComPtr<IPDDocument> m_document;//CPDDocument*	m_pDocument;

	GUID m_spreadGUID;
	CArray<GUID,GUID&> m_objectGuids;

	double m_dx;
	double m_dy;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUndoMoveObjects)
	COM_INTERFACE_ENTRY(IOleUndoUnit)
END_COM_MAP()

public:

// IOleUndoUnit
	STDMETHOD(GetDescription)(/* [out] */ BSTR __RPC_FAR *pBstr)
	{
		*pBstr = SysAllocString(L"Move Objects");
		return S_OK;
	}

	STDMETHOD(Do)(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
	{
		m_dx = -m_dx;
		m_dy = -m_dy;

		CComPtr<IPDSpread> spread;
		m_document->getSpreadByUniqId(m_spreadGUID, &spread);
		if (spread)
		{
			for (int i = 0; i < m_objectGuids.GetSize(); i++)
			{
				CComPtr<IPDObjectUnknown> object;
				spread->getObjectByUniqId(m_objectGuids[i], &object);

				CComQIPtr<IPDObjectTransformable> objectTransformable = object;
				if (objectTransformable)
				{
					objectTransformable->Move(m_dx, m_dy);
				}
			}
		}

		m_bRedo = !m_bRedo;
		pUndoManager->Add(this);

		return S_OK;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CUndoClearbjects

class ATL_NO_VTABLE CUndoClearObjects : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDUndoUnitImpl
{
public:
	CUndoClearObjects()
	{
		m_spreadGUID = GUID_NULL;
		m_pView = NULL;
	}

	CPDDocumentView* m_pView;
	CComPtr<IPDDocument> m_document;

	GUID m_spreadGUID;

	CArray<GUID,GUID> m_parentElements;
	CArray<GUID,GUID> m_beforeElements;
	CArray<GUID,GUID> m_targetElements;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUndoClearObjects)
	COM_INTERFACE_ENTRY(IOleUndoUnit)
END_COM_MAP()

	STDMETHOD(GetDescription)(/* [out] */ BSTR __RPC_FAR *pBstr)
	{
		*pBstr = SysAllocString(L"Clear Objects");
		return S_OK;
	}

	STDMETHOD(Do)(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
	{
		if (m_bRedo)
		{
			DWORD n = m_targetElements.GetSize();

		//	CWEUndoSourceLast::Do(pUndoManager);

			/*
			ATLASSERT(m_pStream == NULL);
		// Remember objects
			HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
			ATLASSERT(SUCCEEDED(hr));

			int i;

			m_pStream->Write(&n, 4, NULL);

			for (i = 0; i < n; i++)
			{
				IDOMNode* pDOMElement = GetElementFromUniqID(documentElement, m_targetElements[i]);
				if (pDOMElement)
				{
					CElement* pElement = m_pDocument->m_pTree->FindDOMElement(pDOMElement);
					if (pElement)
					{
						WriteElementToStream(m_pStream, domdocument, (IDOMElement*)pElement->m_domElement);
					}
				}
			}

			// Seek to beginning
			LARGE_INTEGER offset;
			offset.QuadPart = 0;
			m_pStream->Seek(offset, STREAM_SEEK_SET, NULL);
*/

			CComPtr<IPDSpread> spread;
			m_document->getSpreadByUniqId(m_spreadGUID, &spread);

		// Delete objects
			for (int i = 0; i < n; i++)
			{
				CComPtr<IPDObjectUnknown> object;
				spread->getObjectByUniqId(m_targetElements[i], &object);
				if (object)
				{
					CComPtr<IPDObjectUnknown> parentNode;
					object->get_parent(&parentNode);
					ATLASSERT(parentNode != NULL);

				//	CComQIPtr<IPDObjectWithChildren> parentWithChildren = parentNode;

					m_pView->DeselectPDObject(object);
					parentNode->removeObject(object);
				}
			}
		}
		else
		{
#if 0
			ATLASSERT(m_pStream != NULL);

			DWORD n;
			m_pStream->Read(&n, 4, NULL);

			for (int i = 0; i < n; i++)
			{
				CComQIPtr<IDOMElement> element;
				ReadElementFromStream(m_pStream, domdocument, &element);

				IDOMNode* parentNode = GetElementFromUniqID(documentElement, m_parentElements[i]);
				ATLASSERT(parentNode);

				if (m_beforeElements[i] != GUID_NULL)
				{
					IDOMNode* beforeNode = GetElementFromUniqID(documentElement, m_beforeElements[i]);
					ATLASSERT(beforeNode);
					parentNode->insertBefore(element, beforeNode, NULL);
				}
				else
				{
					parentNode->appendChild(element, NULL);
				}
			}

			m_pStream->Release();
			m_pStream = NULL;

		//	CWEUndoSourceLast::Do(pUndoManager);
#endif
		}

		m_bRedo = !m_bRedo;
		pUndoManager->Add(this);

		return S_OK;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CUndoGroupObjects

class ATL_NO_VTABLE CUndoGroupObjects : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDUndoUnitImpl
{
public:
	CUndoGroupObjects()
	{
		m_spreadGUID = GUID_NULL;
		m_groupGUID = GUID_NULL;
		m_parentgroupGUID = GUID_NULL;
		m_beforegroupGUID = GUID_NULL;

		m_pView = NULL;
	}

	GUID m_spreadGUID;
	CComPtr<IPDDocument> m_document;

	GUID	m_groupGUID;
	GUID	m_parentgroupGUID;
	GUID	m_beforegroupGUID;

	CArray<GUID,GUID> m_parentElements;
	CArray<GUID,GUID> m_beforeElements;
	CArray<GUID,GUID> m_targetElements;

	CPDDocumentView* m_pView;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUndoGroupObjects)
	COM_INTERFACE_ENTRY(IOleUndoUnit)
END_COM_MAP()

public:
	STDMETHOD(GetDescription)(/* [out] */ BSTR __RPC_FAR *pBstr)
	{
		*pBstr = SysAllocString(L"Group Objects");
		return S_OK;
	}

	HRESULT DoInitial(CPDDocumentView* pView, IOleUndoManager *pUndoManager)
	{
		m_pView = pView;

		CComQIPtr<IPDObject> object = pView->m_targetObjects[0]->m_object;

		CComPtr<IPDObjectGroup> pParent;
		object->get_parent((IPDObjectUnknown**)&pParent);

		ATLASSERT(pParent != NULL);

		/*
		{
			CComPtr<IPDObject> parentParent;
			pParent->get_parent(&parentParent);
			ATLASSERT(parentParent != NULL);
		}
		*/

		CArray <IPDObject*, IPDObject*> layers;

	// Build the array of selected objects (we don't use m_targetObjects since they aren't necessarily in order)
		{
			CComPtr<IObjectMap> children;
			pParent->get_children(&children);
			long count;
			children->get_length(&count);
			for (int i = 0; i < count; i++)
			{
				CComPtr<IPDObject> object;
				children->item(i, (IUnknown**)&object);

				if (pView->IsPDObjectSelected(object))
				{
				//	CComQIPtr<ISVGTransformable> transformable = pLayer->m_domElement;
				//	if (transformable != NULL)
					{
						layers.Add(object);
					}
				}
			}
		}

	// We insert the group where the last element is found
	// meaning, the topmost selected object decides where the
	// group is inserted

		CComPtr<IPDObjectUnknown> beforeNode;
		layers[layers.GetSize()-1]->get_nextSibling(&beforeNode);

	// Remember the parent node of the goup
		pParent->get_uniqId(&m_parentgroupGUID);
		ATLASSERT(m_parentgroupGUID != GUID_NULL);

	// Remember the before node of the group
		if (beforeNode)
		{
			beforeNode->get_uniqId(&m_beforegroupGUID);
		}
		else
		{
			m_beforegroupGUID = GUID_NULL;
		}

		for (int i = 0; i < layers.GetSize(); i++)
		{
			GUID guid;

		// Remember which node this had as parent
			CComPtr<IPDObjectGroup> parentNode;
			layers[i]->get_parent((IPDObjectUnknown**)&parentNode);
			parentNode->get_uniqId(&guid);
			m_parentElements.Add(guid);

		// Remember which node this was before
			CComPtr<IPDObjectUnknown> beforeNode;
			layers[i]->get_nextSibling(&beforeNode);
			if (beforeNode)
			{
				beforeNode->get_uniqId(&guid);
				m_beforeElements.Add(guid);
			}
			else
				m_beforeElements.Add(GUID_NULL);

			layers[i]->get_uniqId(&guid);
			m_targetElements.Add(guid);
		}

		::CoCreateGuid(&m_groupGUID);	// Create a unique GUID for the group

		m_bRedo = true;
		Do(pUndoManager);

	//	CElement* pGroupElement = m_pTree->FindDOMElement((IDOMNode*)pGroup);

		return S_OK;
	}

	STDMETHOD(Do)(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
	{
		CComPtr<IPDSpread> spread;
		m_document->getSpreadByUniqId(m_spreadGUID, &spread);

		if (m_bRedo)	// Redo (Group)
		{
//			CWEUndoSourceLast::Do(pUndoManager);

			CComPtr<IPDObjectGroup> pParent;
			spread->getObjectByUniqId(m_parentgroupGUID, (IPDObjectUnknown**)&pParent);
			if (pParent)
			{
				CComQIPtr<IPDObject> beforeNode;

				if (m_beforegroupGUID != GUID_NULL)
					spread->getObjectByUniqId(m_beforegroupGUID, (IPDObjectUnknown**)&beforeNode);

				CComPtr<IPDObjectGroup> group;
				m_document->createObjectGroup(m_groupGUID, &group);

				if (beforeNode)
					pParent->insertObjectBeforeObject(group, beforeNode);
				else
					pParent->appendObject(group);

				for (int i = 0; i < m_targetElements.GetSize(); i++)
				{
					CComPtr<IPDObject> pElement;
					spread->getObjectByUniqId(m_targetElements[i], (IPDObjectUnknown**)&pElement);
					group->appendObject(pElement);	// Insert At end
				}

				m_pView->SelectPDObject(group, 0, /*TODO, remember the selected points*/TRUE);
				//m_pDocument->SetTargetElement(m_pDocument->m_pTree->FindDOMElement(group), 0);
			}
			else
				MessageBox(GetMainHwnd(), "Parent doesn't exist", "PageDesigner", MB_OK | MB_ICONERROR);

			m_pView->Invalidate();
		}
		else	// Undo (Ungroup)
		{
#if 0
			m_pView->DeselectAll();
			m_pDocument->SetTargetElement(NULL, 0);

			CComQIPtr<IDOMElement> group = GetElementFromUniqID(documentElement, m_groupGUID);

			for (int i = m_targetElements.GetSize()-1; i >= 0; i--)
			{
				IDOMNode* element = GetElementFromUniqID(documentElement, m_targetElements[i]);

				IDOMNode* parentNode = GetElementFromUniqID(documentElement, m_parentElements[i]);
				ATLASSERT(parentNode);

				if (m_beforeElements[i] != GUID_NULL)
				{
					IDOMNode* beforeNode = GetElementFromUniqID(documentElement, m_beforeElements[i]);
					ATLASSERT(beforeNode);
					parentNode->insertBefore(element, beforeNode, NULL);
				}
				else
				{
					parentNode->appendChild(element, NULL);
				}

				m_pView->SelectPDObject(element, MK_SHIFT);
				//m_pDocument->SetTargetElement(m_pDocument->m_pTree->FindDOMElement(element), MK_SHIFT);
			}

		// Finally delete the group element
			CComQIPtr<IDOMNode> groupParentNode;
			group->get_parentNode(&groupParentNode);
			groupParentNode->removeChild(group, NULL);

//			CWEUndoSourceLast::Do(pUndoManager);
#endif
		}

		m_bRedo = !m_bRedo;
		pUndoManager->Add(this);

		return S_OK;
	}
};
